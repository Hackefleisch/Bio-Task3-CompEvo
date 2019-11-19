#pragma once

#include "Individual.h"

#include <vector>

class Population{
public:
	Population(int wordCount, int wordLength, int in_popSize, std::mt19937* in_rng, std::uniform_real_distribution<float>* in_rnd);
	Population() = delete;
	const Individual& GetIndividual(int index) const;
private:
	std::vector<Individual> pop;
	int popSize;
	std::mt19937* rng;
	std::uniform_real_distribution<float>* rnd;
};

