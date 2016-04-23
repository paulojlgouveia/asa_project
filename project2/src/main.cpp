#include <iostream>

#include "Graph.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "Johnson.h"
#include "Solution.h"

//MERGE_START

int main () {
	int V = 0, F=0, E = 0;
	int temp = -1;
// 	Graph graph;
	std::vector<int>* subsidiaries = new std::vector<int>();
	Solution *solution;
	
	std::cin >> V;
	std::cin >> F;
	std::cin >> E;

	for(int t=0; t<F; t++) {
	 	std::cin >> temp;
		subsidiaries->push_back(temp);
	}
	
	solution = new Solution(F);
	Graph graph = Graph(V, E);

// 	std::cout << graph << std::endl;
	
	Johnson::run(&graph, subsidiaries, solution);
	solution->print();
	
	// free memory
	delete(subsidiaries);
	delete(solution);
// 	delete(graph);
	return 0;
	
}

//MERGE_END


/*

http://acm.ist.utl.pt/~mooshak/

User: al095
Password: 4SbKJ6

*/

