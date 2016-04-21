#include <iostream>

#include "Graph.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "Johnson.h"

//MERGE_START

void printSolution(int **deslocationCost, std::vector<int>* subsidiaries, int V) {
	
	int location = 0, total_loss = 0, loss = 99999, new_loss;
	int v = 1;
	unsigned int u = 0;
	bool possible = true;
	
	for(v = 1; v < V; v++) {
		new_loss = 0;
		for(u = 0; u < subsidiaries->size(); u++) {
			new_loss = new_loss + deslocationCost[u][v];
		}
		
		if(new_loss < loss) {
			subsidiaries->at(u-1) = deslocationCost[u-1][v];
			location = v;
			loss = new_loss;
		}

	}
	
	for(unsigned int t=0; t<subsidiaries->size(); t++) {
		loss = deslocationCost[t][location];
		
		if(loss == 99999) {
			possible = false;
			break;
		}
		
		total_loss += loss;
	}
	
	if(possible) {
		std::cout << location << " " << total_loss << std::endl;
		for(unsigned int t=0; t<subsidiaries->size(); t++) 
			std::cout << deslocationCost[t][location] << " ";
	} else {
		std::cout << "N";
	}
	
	std::cout << std::endl;
}

int main () {
	int V = 0, F=0, E = 0;
	int temp = -1;
	Graph* graph;
	std::vector<int>* subsidiaries = new std::vector<int>();
	
	int **deslocationCost;
	
	std::cin >> V;
	std::cin >> F;
	std::cin >> E;
	

	for(int t=0; t<F; t++) {
		std::cin >> temp;
		subsidiaries->push_back(temp);
	}

	graph = new Graph(V, E);
// 	std::cout << graph << std::endl;
	
// 	std::cout << "Dijkstra" << std::endl;
// 	Dijkstra::run(graph, 1);
// 	std::cout << graph << std::endl;

// 	std::cout << "BellmanFord" << std::endl;
// 	BellmanFord::run(graph, 1);
// 	std::cout << graph << std::endl;

// 	std::cout << "Johnson" << std::endl;
	deslocationCost = Johnson::run(graph, subsidiaries);
// 	std::cout << graph << std::endl;
// 	
// 	std::cout << "\t1 \t2 \t3 \t4 \t5 \t6" << std::endl;
// 	std::cout << "  ----------------------------------------------------" << std::endl;
// 	for(unsigned int u = 0; u < subsidiaries->size(); u++) {
// 		std::cout << u << "| \t";
// 		for(int v = 1; v < graph->getNumberOfNodes(); v++){
// 			std::cout << deslocationCost[u][v] << " \t";
// 		}
// 		std::cout << std::endl;
// 	}
// 	std::cout << std::endl;
	
	printSolution(deslocationCost, subsidiaries, graph->getNumberOfNodes());
	
	// free memory
	for(int i=0; i<F; i++)
		delete[] deslocationCost[i];
	delete[] deslocationCost;
	
	delete(subsidiaries);

	delete(graph);
	return 0;
	
}
//MERGE_END


/*

http://acm.ist.utl.pt/~mooshak/

User: al095
Password: yDDsFk

*/

