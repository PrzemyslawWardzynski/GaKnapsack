#pragma once
#include "CKnapsackProblem.h"
class CIndividual
{
public:
	CIndividual(int iNumberOfItems);
	CIndividual(CIndividual& cOther);
	~CIndividual();
	void vCross(CIndividual& cOther, CIndividual& crossChild1, CIndividual& crossChild2);
	void vModCross(CIndividual& cOther, CIndividual& crossChild1, CIndividual& crossChild2);
	void vMutate(double dMutProb);
	int iGetFitness(CKnapsackProblem* pcKnapsack);
	int* piGetGenotype() { return pi_genotype; }
	void vShow();
private:
	int* pi_genotype;
	int i_genotype_length;
};

class CGeneticAlgorithm
{
public:
	static const int MAX_ITERATIONS;
	CGeneticAlgorithm(int iPopSize, double dCrossProb, double dMutProb, CKnapsackProblem* pcKnapsack);
	~CGeneticAlgorithm();
	void vRun();
	CIndividual* pcGetBestResult();
	bool bGetInvalidParametersFlag() { return b_invalid_parameters; }
private:
	void vCopyBestGenotype(CIndividual* cOther);
	int i_pop_size;
	double d_cross_prob;
	double d_mut_prob;
	CKnapsackProblem* pc_knapsack;
	CIndividual* pc_best_result;
	bool b_invalid_parameters;
};



