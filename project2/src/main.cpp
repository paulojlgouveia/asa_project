
#include <iostream>

// #include "Solution.hpp"
// #include "Search.hpp"
#include "Graph.h"
#include "Dijkstra.h"


int main () {
	int V = 0, F=0, E = 0;
	int temp = -1;
	Graph* graph;
// 	Solution solution;
	std::vector<int>* startNodes = new std::vector<int>();
	
	std::cin >> V;
	std::cin >> F;
	std::cin >> E;
	
	for(int t=0; t<F; t++) {
		std::cin >> temp;
		startNodes->push_back(temp-1);
	}
	
	graph = new Graph(V, E);
	std::cout << graph << std::endl;

	
	Dijkstra::run(graph, 3);
	std::cout << graph << std::endl;

	
	
// 	solution = Search::function(graph, startNodes);
// 	std::cout << solution.articulationNodes << std::endl;
// 	std::cout << solution.minId << " " << solution.maxId << std::endl;
	

	delete(startNodes);
	delete(graph);
	return 0;
	
}


/*

http://acm.ist.utl.pt/~mooshak/

User: al095
Password: yDDsFk

*/

