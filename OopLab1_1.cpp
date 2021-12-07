//«Нечесні» гральні кості з кількістю граней N=2, 4, 6, 8, 10, 12, 20. Грані помічено 
//числами від 1 до N. Для кожної грані задається ймовірність випадіння (число від 0 до 1).
//Обчислення всіх можливих сум для заданого набору костей (набір може містити довільну 
//кількість костей з однаковими чи різними гранями та однаковими чи різними ймовірностями) 
//та ймовірність випадіння кожної з них.
//+ порівняння двох наборів за очікуваною сумою значень граней


#include <iostream>
#include <vector>
#include "Dice.h"

int main()
{
	srand(time(NULL));
	Dice a = Random();
	Dice b = Random();
	Dice c = Random();
	Dice d = Random();
	a.print();
	b.print();
	c.print();
	d.print();
	std::vector<Dice> first_set = { a,b };
	std::vector<Dice> second_set = { c,d };
	AllSum(first_set, 1);
	AllSum(second_set, 1);
}