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

	static int **run(Graph *graph){
		
// 		int deslocationCost[graph->getNumberOfNodes()][graph->getNumberOfNodes()];
		
		
		int V = graph->getNumberOfNodes();
		int **deslocationCost = new int*[V];
		for(int i=0; i<V; i++) {
			deslocationCost[i] = new int[V];
		}
		
		
		
		connectSource(graph);
		BellmanFord::run(graph, 0);
		disconnectSource(graph);
		std::cout << graph << std::endl;
		
		copyCostToH(graph);
		for(int t = 1; t < graph->getNumberOfNodes(); t++){
			graph->getNodeAt(t)->reweightEdges();
		}
		
		std::cout << graph << std::endl;
		
// 		for(int u = 1; u < 2; u++) {
		for(int u = 1; u < graph->getNumberOfNodes(); u++) {
			Dijkstra::run(graph, u);
			std::cout << graph << std::endl;

			for(int v = 1; v < graph->getNumberOfNodes(); v++){
				deslocationCost[u][v] = graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(u));
			}
		}
		
		return deslocationCost;
	}

	
};
//MERGE_END


#endif


