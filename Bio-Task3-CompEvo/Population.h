#pragma once

#include "Individual.h"

#include <vector>
#include <map>

class Population{
public:
	Population(int wordCount, int wordLength, unsigned int in_popSize, std::mt19937* in_rng, std::uniform_real_distribution<float>* in_rnd);
	Population(const Population& prePop, float crossOverRate, float mutationRate);
	Population() = delete;
	const Individual& GetIndividual(int index) const;
	void PrintReport() const;
	const Individual& GetBestIndividual() const;
	std::map<std::string, int>& SpeciesCount() const;
	int GetPopSize() const;
private:
	std::vector<Individual> pop;
	unsigned int popSize;
	std::mt19937* rng;
	std::uniform_real_distribution<float>* rnd;
	float totalFitness = 0.0f;
	float bestFitness = 0.0f;
	unsigned int bestIndividualIndex = 0;
	int generation = 0;
};

