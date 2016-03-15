#include <iostream>

#include "Search.hpp"
#include "Graph.hpp"

void update(int* min, int* max, int id) {
	if(*min == -1 || *max == -1)	*min = *max = id;
	else if(id < *min)				*min = id;
	else if(id > *max)				*max = id;
}

 int main () {
	std::cout << std::endl;
	
	int N = 0, E = 0;
	int min = -1, max = -1, crucial = 0;
	
	Graph* g;
	//Node* node;
	
	
	std::cin >> N;
	std::cout << "nodes: " << N << std::endl;
	std::cin >> E;
	std::cout << "conections: " << E << std::endl;
	
	g = new Graph(N, E);
	
	Search::dfs(g->getNodeAt(0));
	
	std::cout << g << std::endl;
	
	std::cout << crucial << std::endl;
	std::cout << min << " "<< max << std::endl;	

	delete(g);
	std::cout << std::endl;
	return 0;
}
