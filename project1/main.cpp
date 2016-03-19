
#include <iostream>

#include "Search.hpp"
#include "Graph.hpp"


void update(int* min, int* max, int id) {
	if(*min == -1 || *max == -1)	*min = *max = id;
	else if(id < *min)				*min = id;
	else if(id > *max)				*max = id;
}


 int main () {
	 
	int V = 0, E = 0;
	int min = -1, max = -1, crucial = 0;
	
	Graph* g;
	Node* node;
	
	std::cin >> V;
	std::cin >> E;
	
	g = new Graph(V, E);

	
/****************************** with articulation nodes *****************************/

	// create heap to store articulation nodes, geting min and max = log(v)
	// just store ids, pointer to be passed as argument
	std::list<int>* artNodes = new std::list<int>();
	
	int time = 0;
	for(int t=0; t<V; t++) {
		node = g->getNodeAt(t);
		if(!node->visited())
			Search::articulationPoints(g, node, artNodes, &time);	
	}
	
	
	if(!artNodes->empty()) {
		// check for improvments with heap
// 		crucial = artNodes->size();
		
		int temp = -1, offset = 0;	// FIXME artNodes has duplicate values
		std::list<int>::iterator l_iter;
		for(l_iter=artNodes->begin(); l_iter!=artNodes->end(); l_iter++) {
			if(temp == (*l_iter)) offset++;
			else{
				temp = (*l_iter);
				update(&min, &max, (*l_iter));
			}
		}
		
		crucial = artNodes->size() - offset;
	
		for(l_iter=artNodes->begin(); l_iter!=artNodes->end(); l_iter++)
				std::cout << (*l_iter) << std::endl;
		
		std::cout << std::endl;

	}
		
	delete(artNodes);

/************************************************************************************/
	
	
	
/************************************ with N dfs ************************************/

// 	for(int t=0; t<V; t++) {		
// 		node = g->getNodeAt(t);
// 		node->disable();
// 		
// // 		std::cout << "- " << t << " -" << g << std::endl;
// 				
// 		if (t>0)
// 			Search::dfs(g->getNodeAt(0));
// 		else
// 			Search::dfs(g->getNodeAt(1));
// 		
// 		if (!g->allVisited()) {
// 			update(&min, &max, node->getId());
// 			crucial++;
// 		}
// 		
// 		node->enable();
// 		g->resetVisited();
// 	}
	
/************************************************************************************/

	
	std::cout << crucial << std::endl;
	std::cout << min << " "<< max << std::endl;	

	delete(g);
	return 0;
}


/*

http://acm.ist.utl.pt/~mooshak/

User: al095
Password: yDDsFk

*/


