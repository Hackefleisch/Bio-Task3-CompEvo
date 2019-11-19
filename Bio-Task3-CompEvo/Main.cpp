#include <random>
#include <iostream>
#include <vector>

#include "Individual.h"

int main(){

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> rnd(0.0f, 1.0f);

	std::vector<Individual> pop;
	for(int i = 0; i < 15; i++){
		pop.emplace_back(5, 6, &rng, &rnd);
	}

	for(Individual i : pop){
		std::cout << i.GetDescription() << std::endl;
	}

	system("pause");
	return 0;
}