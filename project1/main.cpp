
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
	
	Graph* g ;
	Node* node;
	
	
	std::cin >> N;
	std::cout << "nodes: " << N << std::endl;
	std::cin >> E;
	std::cout << "conections: " << E << std::endl;
	
	g = new Graph(N);
	
	for(int t=0; t<N; t++) {
		node = g->getNodeAt(t);
		node->disable();
		
		Search::dfs(g);
		
		if(!g->allVisited()) {
			update(&min, &max, node->getId());
			crucial++;
		} else
			std::cout << t << " all visited" << std::endl;
		
		node->enable();
	}
	
	
// 	loop							-> O(N)	-> 
// 		disable one node at a time		-> O(1)		if kept as variable each iteration just t++ 
// 		DFS								-> O(N+E)
// 		check if all nodes visited		-> O(N)
// 		if not, node is crucial			-> O(1)
// 			update variables
// 	write variables to std::cout
//	
//	worst case E==N -> O(N) * ( 2*O(1) + O(2*N) + O(N)) = O(N^2)
		
		

	std::cout << g << std::endl;
	
	std::cout << crucial << std::endl;
	std::cout << min << " "<< max << std::endl;	

	delete(g);
	std::cout << std::endl;
	return 0;
 }
