#ifndef __BELLMANFORD_H__
#define __BELLMANFORD_H__

#include <iostream>
#include <climits>
#include "Dijkstra.h"
#include "Graph.h"
#include "Node.h"

class BellmanFord {
	
	static void initializeSingleSource(Graph* graph, Node* s) {
		for (int t = 1; t < graph->getNumberOfNodes(); t++)
			graph->getNodeAt(t)->setPathCost(INT_MAX);
		s->setPathCost(0);
	}
	

	static void relax(Node *u, Node *v, int weight){
		if(v->getPathCost() > (u->getPathCost() + weight)) {
			v->setPathCost(u->getPathCost() + weight);
			v->setParent(u);
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
		
		for (int t = 1; t < graph->getNumberOfNodes(); t++){
			u = graph->getNodeAt(t);
			adjList = u->getAdjacenciesList();
			
			for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
				v = (*adjIterator)->getNext();
				weight = (*adjIterator)->getWeight();
				relax(u, v, weight);
			}
		}
		
		// doesn't check for negative loops since there's no need
	}
};


#endif



