#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <iostream>

#include "Graph.hpp"


class Search {
	
public:
	
	Search() {}
	~Search() {}
	
/*algorithms*/
	
	static void dfs(Graph* g) {
		std::cout << std::endl << "deep first search" << std::endl << std::endl;
	}
	
	static void bfs(Graph* g) {
		std::cout << std::endl << "breadth first search" << std::endl << std::endl;
	}
};

#endif
