#include <random>
#include <iostream>
#include <vector>
#include <fstream>

#include "Population.h"

std::string CreateBarGraph(Population pop){
	std::string str;

	str += "<link href=\"Final_pop.css\" rel=\"stylesheet\" type=\"text / css\">\n\n";

	str += "<ul class = \"bar-graph\">\n";
	str += "	<li class = \"bar-graph-axis\">\n";
	str += "		<div class = \"bar-graph-label\">100%</div>\n";
	str += "		<div class = \"bar-graph-label\">80%</div>\n";
	str += "		<div class = \"bar-graph-label\">60%</div>\n";
	str += "		<div class = \"bar-graph-label\">40%</div>\n";
	str += "		<div class = \"bar-graph-label\">20%</div>\n";
	str += "		<div class = \"bar-graph-label\">0%</div>\n";
	str += "	</li>\n";

	// Enter data here
	int restCounter = 0;
	for(const std::pair<std::string, int>& it: pop.SpeciesCount()){
		std::string id = it.first;
		int num = it.second;
		float percent = float(num) / pop.GetPopSize();
		if(percent <= 0.01f){
			restCounter += num;
		} else{
			int total = int(percent * 100);
			str += "	<li class=\"bar secondary\" style=\"height: " + std::to_string(total) + "%;\" title=\"" + id + "\">\n";
			str += "		<div class=\"percent\">" + std::to_string(total) + "<span>%</span></div>\n";
			str += "		<div class=\"description\">" + id + "</div>\n";
			str += "	</li>\n";
		}
	}

	if(restCounter > 0){
		float percent = float(restCounter) / pop.GetPopSize();
		int total = int(percent * 100);
		str += "	<li class=\"bar secondary\" style=\"height: " + std::to_string(total) + "%;\" title=\"" + "Rest" + "\">\n";
		str += "		<div class=\"percent\">" + std::to_string(total) + "<span>%</span></div>\n";
		str += "		<div class=\"description\">Rest</div>\n";
		str += "	</li>\n";
	}

	str += "</ul>\n\n";


	str += "<h1>Results</h1>\n";
	str += "<p>mean: " + std::to_string(pop.GetTotalFitness() / pop.GetPopSize()) + "</p>\n";
	str += "<p>best individual: " + pop.GetBestIndividual().GetDescription() + "</p>\n";
	str += "<p></p>";

	return str;
}

int main(){

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> rnd(0.0f, 1.0f);

	float crossoverRate = 1.0f / 4000;
	float mutationRate = 1.0f / 8000;

	Population oldPop(5, 6, 50, &rng, &rnd);
	Population currentPop(oldPop, crossoverRate, mutationRate);
	for(int i = 0; i < 250; i++){
		oldPop.PrintReport();
		if(oldPop.GetBestIndividual().GetFitness() == 24.0f){
			break;
		}
		oldPop = currentPop;
		currentPop = Population(oldPop, crossoverRate, mutationRate);
	}

	oldPop.SpeciesCount();

	std::ofstream output;
	output.open("Final_pop.html");
	output << CreateBarGraph(oldPop);
	output.close();

	system("pause");
	return 0;
}