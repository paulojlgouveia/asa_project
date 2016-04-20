
#include <iostream>

// #include "Solution.hpp"
// #include "Search.hpp"
#include "Graph.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "Johnson.h"


int main () {
	int V = 0, F=0, E = 0;
	int temp = -1;
	Graph* graph;
// 	Solution solution;
// 	std::vector<int>* deslocationCost = new std::vector<int>();
	
	int **deslocationCost;
	
	std::cin >> V;
	std::cin >> F;
	std::cin >> E;
	

	for(int t=0; t<F; t++) {
		std::cin >> temp;
// 		deslocationCost->push_back(temp-1);
	}
	
	graph = new Graph(V, E);
	std::cout << graph << std::endl;
	
// 	std::cout << "Dijkstra" << std::endl;
// 	Dijkstra::run(graph, 1);
// 	std::cout << graph << std::endl;

// 	std::cout << "BellmanFord" << std::endl;
// 	BellmanFord::run(graph, 1);
// 	std::cout << graph << std::endl;

	std::cout << "Johnson" << std::endl;
	deslocationCost = Johnson::run(graph);
	std::cout << graph << std::endl;
	
	
	for(int u = 1; u < graph->getNumberOfNodes(); u++) {

		std::cout << u << "| \t";
		for(int v = 1; v < graph->getNumberOfNodes(); v++){
			std::cout << deslocationCost[u][v] << " \t";
		}
		std::cout << std::endl;
	}	
	
	
	
	
	
// 	solution = Search::function(graph, deslocationCost);
// 	std::cout << solution.articulationNodes << std::endl;
// 	std::cout << solution.minId << " " << solution.maxId << std::endl;

// 	delete(deslocationCost);
	delete(graph);
	return 0;
	
}


/*

http://acm.ist.utl.pt/~mooshak/

User: al095
Password: yDDsFk

*/

