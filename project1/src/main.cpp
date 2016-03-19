
#include <iostream>

#include "Search.hpp"
#include "Graph.hpp"
#include "Solution.hpp"

//MERGE_START
 int main () {
	int V = 0, E = 0;	
	Graph* graph;
	Solution solution;
	
	std::cin >> V;
	std::cin >> E;
	
	graph = new Graph(V, E);
	solution = Search::findArticulationNodes(graph);

	std::cout << solution.articulationNodes << std::endl;
	std::cout << solution.minId << " "<< solution.maxId << std::endl;

	delete(graph);
	return 0;
}
//MERGE_END

/*

http://acm.ist.utl.pt/~mooshak/

User: al095
Password: yDDsFk

*/

