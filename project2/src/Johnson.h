#ifndef __JOHNSON_H__
#define __JOHNSON_H__

#include <iostream>
#include "Graph.h"
#include "Node.h"
#include "BellmanFord.h"

class Johnson {
	
	static void connectSource(Graph *graph) {
		for(int t=1; t<graph->getNumberOfNodes(); t++)
			graph->getNodeAt(0)->connect(graph->getNodeAt(t), 0);
	}
	
	static void disconnectSource(Graph *graph) {
// 		std::list<Edge*>::iterator adjIterator;
// 		std::list<Edge*>* adjList = (graph->getNodeAt(0))->getAdjacenciesList();
// 		
// 		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
// 			delete(*adjIterator);
// 		}
	
		graph->getNodeAt(0)->clearAdjacencies();
	}
	
	
public:

	static void run(Graph *graph){		
		connectSource(graph);
		BellmanFord::run(graph, 0);
		disconnectSource(graph);
		
	}

	
};



#endif


