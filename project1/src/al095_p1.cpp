
#include <iostream>

#include "Search.hpp"
#include "Graph.hpp"
#include "Solution.hpp"


 int main () {
	 
	int V = 0, E = 0;	
	Graph* g;
	Solution result;
	
	std::cin >> V;
	std::cin >> E;
	
	g = new Graph(V, E);

	result = Search::findArticulationNodes(g);

	std::cout << result.artNodesCounter << std::endl;
	std::cout << result.minID << " "<< result.maxID << std::endl;

	delete(g);
	return 0;
}


/*

http://acm.ist.utl.pt/~mooshak/

User: al095
Password: yDDsFk

*/


