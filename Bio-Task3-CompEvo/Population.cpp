#include "Population.h"
#include <algorithm>
#include <iostream>



Population::Population(int wordCount, int wordLength, unsigned int in_popSize, std::mt19937* in_rng, std::uniform_real_distribution<float>* in_rnd){

	popSize = in_popSize;
	rng = in_rng;
	rnd = in_rnd;

	pop.reserve(popSize);

	for(unsigned int i = 0; i < popSize; i++){
		pop.emplace_back(wordCount, wordLength, rng, rnd);
		float fitness = pop.at(i).GetFitness();
		totalFitness += fitness;
		if(fitness > bestFitness){
			bestFitness = fitness;
			bestIndividualIndex = i;
		}
	}

}

Population::Population(const Population& prePop, float crossOverRate, float mutationRate){

	generation = prePop.generation + 1;
	popSize = prePop.popSize;
	rng = prePop.rng;
	rnd = prePop.rnd;
	pop.reserve(popSize);

	std::vector<float> rouletteWheel;
	rouletteWheel.reserve(popSize);

	rouletteWheel.push_back(prePop.pop.at(0).GetFitness() / prePop.totalFitness);

	for(unsigned int i = 1; i < popSize; i++){
		rouletteWheel.push_back(rouletteWheel.at(i - 1) + prePop.pop.at(i).GetFitness() / prePop.totalFitness);
	}

	while(pop.size() < popSize){
		float randomNum = (*rnd)(*rng);
		int parentIndex1 = 0;
		while(rouletteWheel.at(parentIndex1) < randomNum){
			parentIndex1++;
		}

		randomNum = (*rnd)(*rng);
		int parentIndex2 = 0;
		while(rouletteWheel.at(parentIndex2) < randomNum){
			parentIndex2++;
		}

		pop.emplace_back(prePop.GetIndividual(parentIndex1), prePop.GetIndividual(parentIndex2), crossOverRate, mutationRate, true);
		float fitness = pop.back().GetFitness();
		totalFitness += fitness;
		if(fitness > bestFitness){
			bestFitness = fitness;
			bestIndividualIndex = pop.size() - 1;
		}
		pop.emplace_back(prePop.GetIndividual(parentIndex1), prePop.GetIndividual(parentIndex2), crossOverRate, mutationRate, false);
		fitness = pop.back().GetFitness();
		totalFitness += fitness;
		if(fitness > bestFitness){
			bestFitness = fitness;
			bestIndividualIndex = pop.size() - 1;
		}
	}

}

const Individual& Population::GetIndividual(int index) const{
	return pop.at(index);
}

void Population::PrintReport() const{

	std::cout << generation << ". generation - mean: " << totalFitness / popSize << " best: " << pop.at(bestIndividualIndex).GetDescription() << std::endl;

}


