#include <random>
#include <iostream>
#include <vector>

#include "Population.h"

int main(){

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> rnd(0.0f, 1.0f);
	
	Population pop(5, 6, 100, &rng, &rnd);
	Population pop2(pop, 0.02, 0.033333);

	system("pause");
	return 0;
}