#include "CKnapsackProblem.h"
using namespace std;



CKnapsackProblem::CKnapsackProblem(int iNumberOfItems, int iMaxWeight, vector<pair<int, int>>* vItems)
{
	if (iNumberOfItems <= 0 || iMaxWeight <= 0 || vItems == NULL) b_invalid_parameters = true;
	else
	{
		b_invalid_parameters = false;
		i_number_of_items = iNumberOfItems;
		i_max_weight = iMaxWeight;

		for (int ii = 0; ii < vItems->size(); ii++)
		{
			v_items.push_back(make_pair((*vItems)[ii].first, (*vItems)[ii].second));
		}
	}
}


CKnapsackProblem::~CKnapsackProblem()
{
}

int CKnapsackProblem::iGetValue(int *piGenotype)
{
	int i_value = 0;
	int i_weight = 0;
	for (int ii = 0; ii < i_number_of_items; ii++) 
	{
		if (piGenotype[ii] == 1)
		{
			i_value += v_items[ii].first;
			i_weight += v_items[ii].second;

		}
	}
	return (i_weight<=i_max_weight) ? i_value : 0;
}
