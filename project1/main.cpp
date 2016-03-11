#include <iostream> 
#include <string> //not sure if needed

#include "Graph.hpp" 
 
 int main () {
	std::cout << std::endl;
	
	int N = 0;
	int aux = 0;
	
	std::cin >> N;
	std::cout << "nodes: " << N << std::endl;
	std::cin >> aux;	// discard number of connections
	std::cout << "conections: " << aux << std::endl << std::endl;

	
// 	// just to check if working because this consumes the input
// 	for(int t=1; t<N; t++) {
// 		std::cin >> one;
// 		std::cin >> two;
// 		
// 		std::cout << t << ":  " << one << "\t" << two << " " << std::endl;
// 	}
	
	
	Graph* graph = new Graph(N);
	
	std::cout << graph;

	delete(graph);
	
	std::cout << std::endl;
	return 0;
 }
