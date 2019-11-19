#include "Population.h"



Population::Population(int wordCount, int wordLength, int in_popSize, std::mt19937* in_rng, std::uniform_real_distribution<float>* in_rnd){

	popSize = in_popSize;
	rng = in_rng;
	rnd = in_rnd;

	for(int i = 0; i < popSize; i++){
		pop.emplace_back(wordCount, wordLength, rng, rnd);
	}

}


