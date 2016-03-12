
#include <iostream>

#include "Graph.hpp" 
#include "Graph2.hpp"


 int main () {
	std::cout << std::endl;
	
	int N = 0;
	int E = 0;
	
	std::cin >> N;
	std::cout << "nodes: " << N << std::endl;
	std::cin >> E;
	std::cout << "conections: " << E << std::endl;
	
	Graph* graph = new Graph(N);
	Graph* copy = new Graph(graph);

// 	Graph2* graph = new Graph2(N);
// 	Graph2* copy = new Graph2(graph);

	

// 	loop							-> O(N)	-> 
// 		disable one node at a time		-> O(1)		if kept as variable each iteration just t++ 
// 		DFS								-> O(N+E)
// 		check if all nodes visited		-> O(N)
// 		if not, node is crucial			-> O(1)
// 			update variables
// 	write variables to std::cout
//	
//	worst case E==N -> O(N) * ( 2*O(1) + O(2*N) + O(N)) = O(N^2)
	
	
	
	std::cout << graph;
	std::cout << copy;
	
	delete(graph);
	delete(copy);
	std::cout << std::endl;
	return 0;
 }
