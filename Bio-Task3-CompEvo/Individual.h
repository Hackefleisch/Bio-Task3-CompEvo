#pragma once

#include <vector>
#include <random>
#include <string>

class Individual{
public:
	Individual(int in_wordCount, int in_wordLength, std::mt19937* in_rng, std::uniform_real_distribution<float>* in_rnd);
	Individual() = delete;
	float GetFitness() const;
	std::string GetDescription() const;
private:
	void CalcGenes();
	void CalcFitness();
private:
	int wordCount;
	int wordLength;
	std::vector<bool> dna;
	std::vector<int> genes;
	float fitness = 0.0f;
	std::mt19937* rng;
	std::uniform_real_distribution<float>* rnd;
};

