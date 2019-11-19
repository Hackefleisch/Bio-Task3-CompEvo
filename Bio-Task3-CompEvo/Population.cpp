#include "Population.h"
#include <algorithm>



Population::Population(int wordCount, int wordLength, int in_popSize, std::mt19937* in_rng, std::uniform_real_distribution<float>* in_rnd){

	popSize = in_popSize;
	rng = in_rng;
	rnd = in_rnd;

	pop.reserve(popSize);

	for(int i = 0; i < popSize; i++){
		pop.emplace_back(wordCount, wordLength, rng, rnd);
		totalFitness += pop.at(i).GetFitness();
	}

}

Population::Population(const Population prePop, float crossOverRate, float mutationRate){

	popSize = prePop.popSize;
	rng = prePop.rng;
	rnd = prePop.rnd;
	pop.reserve(popSize);

	std::vector<float> rouletteWheel;
	rouletteWheel.reserve(popSize);

	rouletteWheel.push_back(prePop.pop.at(0).GetFitness() / prePop.totalFitness);

	for(int i = 1; i < popSize; i++){
		rouletteWheel.push_back(rouletteWheel.at(i - 1) + prePop.pop.at(i).GetFitness() / prePop.totalFitness);
	}

}

const Individual& Population::GetIndividual(int index) const{
	return pop.at(index);
}


