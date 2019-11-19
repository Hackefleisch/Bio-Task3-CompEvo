#include <random>
#include <iostream>
#include <vector>

#include "Population.h"

int main(){

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> rnd(0.0f, 1.0f);

	float crossoverRate = 1.0f / 1000;
	float mutationRate = 1.0f / 3000;

	Population oldPop(5, 6, 100, &rng, &rnd);
	Population currentPop(oldPop, crossoverRate, mutationRate);
	for(int i = 0; i < 100; i++){
		oldPop.PrintReport();
		if(oldPop.GetBestIndividual().GetFitness() == 24.0f){
			break;
		}
		oldPop = currentPop;
		currentPop = Population(oldPop, crossoverRate, mutationRate);
	}

	system("pause");
	return 0;
}