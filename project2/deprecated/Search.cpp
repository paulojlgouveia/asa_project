#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <iostream>
#include <stack>
#include <list>
#include "Graph.hpp"
#include "Solution.hpp"

class Search {
	
public:
	static void updateSolution(Solution* solution);
	static Solution function(Graph* graph);
};

#endif






