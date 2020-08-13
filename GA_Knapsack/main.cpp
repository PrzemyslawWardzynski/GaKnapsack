#include "CGeneticAlgorithm.h"
#include "CKnapsackProblem.h"
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

const string INVALID_KNAPSACK_PARAMETERS = "Invalid Knapsack parameters!";
const string INVALID_GEN_ALG_PARAMETERS = "Invalid Genetic Algorithm parameters!";

int main()
{
	
	vector<pair<int, int>> v_values_and_weights;
	/*
	v_values_and_weights.push_back(make_pair(5, 4));
	v_values_and_weights.push_back(make_pair(1, 1));
	v_values_and_weights.push_back(make_pair(4, 3));
	v_values_and_weights.push_back(make_pair(3, 2));
	*/
	v_values_and_weights.push_back(make_pair(10, 9));
	v_values_and_weights.push_back(make_pair(7, 12));
	v_values_and_weights.push_back(make_pair(1, 2));
	v_values_and_weights.push_back(make_pair(3, 7));
	v_values_and_weights.push_back(make_pair(2, 5));
	int iMaxWeight = 15;
	int i_pop_size = 4;
	double d_cross_prob = 0.6;
	double d_mut_prob = 0.7;
	CKnapsackProblem c_knapsack(v_values_and_weights.size(), 15, &v_values_and_weights);
	if (c_knapsack.bGetInvalidParamatersFlag() != true)
	{
		CGeneticAlgorithm c_GA(i_pop_size, d_cross_prob, d_mut_prob, &c_knapsack);
		if (c_GA.bGetInvalidParametersFlag() != true)
		{
			c_GA.vRun();
			cout << "BEST RESULT: "; c_GA.pcGetBestResult()->vShow();
			cout << "FITNESS: " << c_GA.pcGetBestResult()->iGetFitness(&c_knapsack);
		}
		else
		{
			cout << INVALID_GEN_ALG_PARAMETERS << endl;
		}
	}
	else
	{
		cout << INVALID_KNAPSACK_PARAMETERS << endl;
	}
	_getch();
}