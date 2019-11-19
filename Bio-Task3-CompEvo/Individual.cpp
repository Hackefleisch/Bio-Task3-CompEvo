#include "Individual.h"
#include <math.h>



Individual::Individual(int in_wordCount, int in_wordLength, std::mt19937* in_rng, std::uniform_real_distribution<float>* in_rnd){

	rng = in_rng;
	rnd = in_rnd;
	wordCount = in_wordCount;
	wordLength = in_wordLength;

	for(int i = 0; i < wordCount*wordLength; i++){
		float randomNum = (*rnd)(*rng);
		if(randomNum < 0.5f){

			dna.push_back(true);

		} else{

			dna.push_back(false);

		}

	}

	CalcGenes();
	CalcFitness();

}

float Individual::GetFitness() const{
	return fitness;
}

std::string Individual::GetDescription() const{
	std::string str = "";
	for(int g : genes){
		str += std::to_string(g) + " ";
	}
	str += "- " + std::to_string(fitness);
	return str;
}

void Individual::CalcGenes(){

	for(int i = 0; i < wordCount; i++){
		int gene = 0;
		for(int j = 0; j < wordLength; j++){
			if(dna.at(i*wordLength + j)){
				gene += int(std::pow(2.0f, wordLength - 1 - j));
			}
		}
		genes.push_back(gene);
	}

}

void Individual::CalcFitness(){

	float v = 0;
	for(int& g : genes){
		v += g;
	}
	v /= wordCount;

	fitness = 24 - std::pow(v - 24, 2) / 24;

}


