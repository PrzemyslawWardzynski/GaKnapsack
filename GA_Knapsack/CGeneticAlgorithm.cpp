#include "CGeneticAlgorithm.h"
#include <iostream>
#include <random>
using namespace std;


CIndividual::CIndividual(int iNumberOfItems)
{
	pi_genotype = new int[iNumberOfItems];
	i_genotype_length = iNumberOfItems;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 1);
	for (int ii = 0; ii < i_genotype_length; ii++)
	{
		pi_genotype[ii] = dis(gen);
	}
}

CIndividual::CIndividual(CIndividual & cOther)
{
	i_genotype_length = cOther.i_genotype_length;
	pi_genotype = new int[i_genotype_length];
	for (int ii = 0; ii < i_genotype_length; ii++)
	{
		pi_genotype[ii] = cOther.pi_genotype[ii];
	}
	
}

CIndividual::~CIndividual()
{
	delete[] pi_genotype;
}

void CIndividual::vCross(CIndividual & cOther, CIndividual & crossChild1, CIndividual & crossChild2)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, i_genotype_length-1);

	int i_pivot = dis(gen);

	for (int ii = 0; ii < i_pivot; ii++)
	{
		crossChild1.pi_genotype[ii] = this->pi_genotype[ii];
		crossChild2.pi_genotype[ii] = cOther.pi_genotype[ii];
	}
	for (int ii = i_pivot; ii < i_genotype_length; ii++)
	{
		crossChild1.pi_genotype[ii] = cOther.pi_genotype[ii];
		crossChild2.pi_genotype[ii] = this->pi_genotype[ii];
	}
	
}

void CIndividual::vModCross(CIndividual & cOther, CIndividual & crossChild1, CIndividual & crossChild2)
{

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, i_genotype_length - 1);

	int i_pivot1 = dis(gen);
	int i_pivot2 = dis(gen);
	if (i_pivot1 > i_pivot2)
	{
		int i_tmp = i_pivot1;
		i_pivot1 = i_pivot2;
		i_pivot2 = i_tmp;
	}

	for (int ii = 0; ii < i_pivot1; ii++)
	{
		crossChild1.pi_genotype[ii] =this->pi_genotype[ii] ;
		crossChild2.pi_genotype[ii] =cOther.pi_genotype[ii] ;
	}
	for (int ii = i_pivot1; ii < i_pivot2; ii++)
	{
		crossChild1.pi_genotype[ii] = cOther.pi_genotype[ii];
		crossChild2.pi_genotype[ii] = this->pi_genotype[ii];
	}
	for (int ii = i_pivot2; ii < i_genotype_length; ii++)
	{
		crossChild1.pi_genotype[ii] = this->pi_genotype[ii];
		crossChild2.pi_genotype[ii] = cOther.pi_genotype[ii];
	}


	cout << "siema";
}



void CIndividual::vMutate(double dMutProb)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0, 1.0);
	for (int ii = 0; ii < i_genotype_length; ii++)
	{
		if (dis(gen) < dMutProb)
		{
			(pi_genotype[ii] == 0) ? pi_genotype[ii] = 1 : pi_genotype[ii] = 0;
		}
	}
}

int CIndividual::iGetFitness(CKnapsackProblem* pcKnapsack)
{
	return pcKnapsack->iGetValue(pi_genotype);
}

void CIndividual::vShow()
{
	for (int ii = 0; ii < i_genotype_length; ii++)
	{
		cout << pi_genotype[ii];
	}
	cout << endl;
}



const int CGeneticAlgorithm::MAX_ITERATIONS = 100;
CGeneticAlgorithm::CGeneticAlgorithm(int iPopSize, double dCrossProb, double dMutProb, CKnapsackProblem* pcKnapsack)
{
	if (iPopSize <= 0 || pcKnapsack == NULL) b_invalid_parameters = true;
	else
	{
		b_invalid_parameters = false;
		i_pop_size = iPopSize;
		d_cross_prob = dCrossProb;
		d_mut_prob = dMutProb;
		pc_knapsack = pcKnapsack;
		pc_best_result = new CIndividual(pc_knapsack->iGetNumberOfItems());
	}
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{
	if(pc_best_result != NULL) delete pc_best_result;
}

void CGeneticAlgorithm::vRun()
{

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis_choose_individual(0, i_pop_size - 1);
	uniform_real_distribution<> dis_cross_and_mutate(0.0, 1.0);

	vector<CIndividual*> v_population;
	vector<CIndividual*> v_next_population;

	for (int ii = 0; ii < i_pop_size; ii++)
	{
		v_population.push_back(new CIndividual(pc_knapsack->iGetNumberOfItems()));
	}

	int i_best_result = 0;
	for (int ii = 0; ii < MAX_ITERATIONS; ii++)
	{
	
		int i_best_result_index = i_pop_size;

		for (int ii = 0; ii < v_population.size(); ii++)
		{
			//v_population[ii]->vShow();
			
			int i_result = v_population[ii]->iGetFitness(pc_knapsack);

			if (i_result > i_best_result)
			{
				i_best_result = i_result;
				i_best_result_index = ii;
				
			}
		}
		if(i_best_result_index < i_pop_size) vCopyBestGenotype(v_population[i_best_result_index]);
	
		while (v_next_population.size() < v_population.size())
		{
			CIndividual* pc_parent1 = v_population[dis_choose_individual(gen)];
			CIndividual* pc_chosen_parent_1 = v_population[dis_choose_individual(gen)];
			CIndividual* pc_parent2 = v_population[dis_choose_individual(gen)];
			CIndividual* pc_chosen_parent_2 = v_population[dis_choose_individual(gen)];

			if (pc_parent1->iGetFitness(pc_knapsack) > pc_chosen_parent_1->iGetFitness(pc_knapsack)) pc_chosen_parent_1 = pc_parent1;
			if (pc_parent2->iGetFitness(pc_knapsack) > pc_chosen_parent_2->iGetFitness(pc_knapsack)) pc_chosen_parent_2 = pc_parent2;

			if (dis_cross_and_mutate(gen) < d_cross_prob)
			{
				CIndividual* pc_child1 = new CIndividual(pc_knapsack->iGetNumberOfItems());
				CIndividual* pc_child2 = new CIndividual(pc_knapsack->iGetNumberOfItems());

				//pc_chosen_parent_1->vCross(*pc_chosen_parent_2, *pc_child1, *pc_child2);
				pc_chosen_parent_1->vModCross(*pc_chosen_parent_2, *pc_child1, *pc_child2);
				v_next_population.push_back(pc_child1);
				v_next_population.push_back(pc_child2);
			}
			else
			{
				v_next_population.push_back(new CIndividual(*pc_chosen_parent_1));
				v_next_population.push_back(new CIndividual(*pc_chosen_parent_2));
			}
		}

		for (int ii = 0; ii < v_population.size(); ii++)
		{
			v_next_population[ii]->vMutate(d_mut_prob);
			delete v_population[ii];
		}
		v_population.clear();
	
		for (int ii = 0; ii < v_next_population.size(); ii++)
		{
			v_population.push_back(v_next_population[ii]);
		}
		v_next_population.clear();
	}

	for (int ii = 0; ii < v_population.size(); ii++)
	{
		delete v_population[ii];
	}
	
}

CIndividual* CGeneticAlgorithm::pcGetBestResult()
{
	return pc_best_result;
}

void CGeneticAlgorithm::vCopyBestGenotype(CIndividual* cOther)
{
	for (int ii = 0; ii < pc_knapsack->iGetNumberOfItems(); ii++)
	{
		pc_best_result->piGetGenotype()[ii] = cOther->piGetGenotype()[ii];
	}
}
