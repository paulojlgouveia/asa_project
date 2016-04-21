#ifndef __JOHNSON_H__
#define __JOHNSON_H__

#include <iostream>
#include "Graph.h"
#include "Node.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

//MERGE_START
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
	
	
	static void copyCostToH(Graph *graph) {
		Node *node;
		
		for(int t=0; t<graph->getNumberOfNodes(); t++) {
			node = graph->getNodeAt(t);
			node->setH(node->getPathCost());
		}
	}
	
	
	
public:

	static int **run(Graph *graph, std::vector<int> *subsidiaries){
		
		int F = subsidiaries->size();
		int **deslocationCost = new int*[F];
		for(int i=0; i<F; i++) {
			deslocationCost[i] = new int[graph->getNumberOfNodes()];
		}
		
		connectSource(graph);
		BellmanFord::run(graph, 0);
		disconnectSource(graph);
// 		std::cout << graph << std::endl;
		
		copyCostToH(graph);
		for(int t = 1; t < graph->getNumberOfNodes(); t++){
			graph->getNodeAt(t)->reweightEdges();
		}

// 		std::cout << "before dijkstra " << graph << std::endl;	

		
		for(int u = 0; u < F; u++) {
			Dijkstra::run(graph, subsidiaries->at(u));
// 			std::cout << "after dijkstra " << graph << std::endl;

			for(int v = 1; v < graph->getNumberOfNodes(); v++){
				deslocationCost[u][v] = graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(u));
			}
		}
		
		return deslocationCost;
	}

	
};
//MERGE_END


#endif


