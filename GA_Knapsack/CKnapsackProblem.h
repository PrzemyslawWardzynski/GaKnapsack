#pragma once
#include <vector>
class CKnapsackProblem
{
public:
	CKnapsackProblem(int iNumberOfItems, int iMaxWeight, std::vector<std::pair<int, int>>* vItems);
	~CKnapsackProblem();
	int iGetValue(int* piGenotype);
	int iGetNumberOfItems() { return i_number_of_items;}
	bool bGetInvalidParamatersFlag() { return b_invalid_parameters; }
private:
	int i_number_of_items;
	int i_max_weight;
	bool b_invalid_parameters;
	std::vector<std::pair<int, int>> v_items;

};

