#pragma once
#include <iostream>
#include <cassert>
#include <map>  
#include <time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------
class Dice
{
public:
	Dice() {
		number_of_sides = 0;
		probability_for_side = new double[0];
	}
	Dice(int number_of_sides, double* probability_for_side) {
		assert((number_of_sides > 0) && "- number of sides");
		this->number_of_sides = number_of_sides;

		this->probability_for_side = new double[number_of_sides];
		double sum_for_checking = 0;
		for (int i = 0; i < number_of_sides; i++)
		{
			assert(probability_for_side[i] >= 0 && "- probability");
			this->probability_for_side[i] = probability_for_side[i];
			sum_for_checking += probability_for_side[i];
		}
		assert(abs(sum_for_checking - 1) < 0.0001 && "Sum != to 1");
	};

	Dice(const Dice& other) {
		this->number_of_sides = other.number_of_sides;
		this->probability_for_side = new double[other.number_of_sides];
		for (int i = 0; i < this->number_of_sides; i++)
		{
			this->probability_for_side[i] = other.probability_for_side[i];
		}
	}

	Dice operator = (const Dice& other) {
		this->number_of_sides = other.number_of_sides;
		this->probability_for_side = new double[other.number_of_sides];
		for (int i = 0; i < this->number_of_sides; i++)
		{
			this->probability_for_side[i] = other.probability_for_side[i];
		}
		return *this;
	}
	Dice(Dice& other) {
		this->number_of_sides = other.number_of_sides;
		this->probability_for_side = new double[other.number_of_sides];
		for (int i = 0; i < this->number_of_sides; i++)
		{
			this->probability_for_side[i] = other.probability_for_side[i];
		}

	}


	~Dice() {
		delete[] probability_for_side;
	};
	int get_number() {
		return number_of_sides;
	}
	double* SideProbability() {
		return probability_for_side;
	}
	void print() {
		std::cout << " n = " << this->number_of_sides << ", probability = {";
		for (int i = 0; i < this->number_of_sides - 1; i++)
		{
			std::cout << " p_" << i << " = " << this->probability_for_side[i] << ",";
		}
		std::cout << " p_" << (this->number_of_sides - 1) << " = " << this->probability_for_side[this->number_of_sides - 1] << "}" << std::endl;
	}
private:
	int number_of_sides;
	double* probability_for_side;
};
//------------------------------------------------------------------------------------------------------------------------------------------------
Dice Random() {
	int possible_numbers[] = { 2,4,6,8,10,12,20 };
	int n = possible_numbers[rand() % 7];
	double* probabilities = new double[n];
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		probabilities[i] = (rand() % 1001);
		sum += probabilities[i];
	}
	if (sum == 0)
	{
		probabilities[0] = 1;
		sum = 1;
	}
	for (int i = 0; i < n; i++)
	{
		probabilities[i] = probabilities[i] / sum;
	}
	Dice new_dice(n, probabilities);
	delete[]probabilities;

	return new_dice;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void AllCombSum(std::map<int, double>& result, std::vector <Dice>& dices, int sum = 0, double properties = 1, int current_index = 0) {
	if (current_index == dices.size())
	{
		if (properties != 0)
		{
			if (result.count(sum))
			{
				result[sum] += properties;
			}
			else {
				result.insert(std::make_pair(sum, properties));
			}
		}
		return;
	}
	else {

		for (int i = 0; i < dices[current_index].get_number(); i++)
		{
			if (dices[current_index].SideProbability()[i] == 0) {
				continue;
			}
			AllCombSum(result, dices, sum + (i + 1), properties * (dices[current_index].SideProbability()[i]), current_index + 1);

		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------
std::map <int, double> AllSum(std::vector <Dice>& dices, bool print = 0) {
	std::map <int, double> result;
	AllCombSum(result, dices);
	if (print)
	{
		std::map <int, double> ::iterator it = result.begin();
		for (int i = 0; it != result.end(); it++, i++) {  
			std::cout << i << ") sum " << it->first << ", probability " << it->second << std::endl;
		}
	}
	return result;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void Compare(std::vector <Dice>& dices_1, std::vector <Dice>& dices_2) {
	std::map<int, double> sums_1 = AllSum(dices_1);
	std::map<int, double> sums_2 = AllSum(dices_2);
	std::map<int, double>::iterator iter_1 = sums_1.begin(), iter_2 = sums_2.begin();
	int e = 0;
	while ((iter_1 != sums_1.end()) || (iter_2 != sums_2.end())) {
		if ((iter_1 == sums_1.end()))
		{
			std::cout << "sum = " << iter_2->first << " has higer on " << iter_2->second << " probability in second set" << std::endl;
			iter_2++;
			continue;
		}
		if (iter_2 == sums_2.end())
		{
			std::cout << "sum = " << iter_1->first << " has higer on " << iter_1->second << " probability in first set" << std::endl;
			iter_1++;
			continue;
		}
		if (iter_1->first > iter_2->first)
		{
			std::cout << "sum = " << iter_2->first << " has higer on " << iter_2->second << " probability in second set" << std::endl;
			iter_2++;
			continue;
		}
		if (iter_1->first < iter_2->first)
		{
			std::cout << "sum = " << iter_1->first << " has higer on " << iter_1->second << " probability in first set" << std::endl;
			iter_1++;
			continue;
		}
		if (iter_1->first == iter_2->first)
		{
			if (iter_1->second == iter_2->second)
			{
				std::cout << "sum = " << iter_1->first << " has same probability in two sets" << std::endl;
			}
			else {
				std::cout << "sum = " << iter_1->first << " has higer on " << abs(iter_1->second - iter_2->second) << " probability in ";
				if (iter_1->second > iter_2->second)
				{
					std::cout << "first set" << std::endl;
				}
				else {
					std::cout << "second set" << std::endl;
				}
			}
			iter_1++;
			iter_2++;
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------