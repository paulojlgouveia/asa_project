#ifndef __BELLMANFORD_H__
#define __BELLMANFORD_H__

#include <iostream>
#include "Graph.h"
#include "Node.h"

//MERGE_START
class BellmanFord {
	
	static void initializeSingleSource(Graph* graph, Node* s) {
		for (int t = 0; t < graph->getNumberOfNodes(); t++)
			graph->getNodeAt(t)->setPathCost(99999);
		s->setPathCost(0);
	}
	

	static void relax(Node *u, Node *v, int weight){
		if(v->getPathCost() > (u->getPathCost() + weight)) {
			v->setPathCost(u->getPathCost() + weight);
		}
	}
	
public:
	
	// runs bellman-ford algorithm starting at node with given id
	static void run(Graph *graph, int id){
		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList;
		Node *u;
		Node *v;
		int weight;
		
		initializeSingleSource(graph, graph->getNodeAt(id)); //by default source index is zero
		
		// do V-1 iterations
		for (int t = 0; t < graph->getNumberOfNodes(); t++){
		
			// loop through all edges
			for (int i = 0; i < graph->getNumberOfNodes(); i++){
				
				u = graph->getNodeAt(i);
				adjList = u->getAdjacenciesList();
				
				for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
					v = (*adjIterator)->getNext();
					weight = (*adjIterator)->getWeight();
					relax(u, v, weight);
				}
			}
		}
		
		// look for negative loops
		for (int t = 0; t < graph->getNumberOfNodes(); t++){
			// loop through all edges
			for (int i = 0; i < graph->getNumberOfNodes(); i++){
				u = graph->getNodeAt(i);
				adjList = u->getAdjacenciesList();
				
				for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
					v = (*adjIterator)->getNext();
					weight = (*adjIterator)->getWeight();
					if(v->getPathCost() > weight + u->getPathCost())
						throw std::string("NEGATIVE LOOP !!!");
				}
			}
		}
		
		
		// doesn't check for negative loops since there's no need
	}
};
//MERGE_END

#endif



