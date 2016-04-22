#ifndef __JOHNSON_H__
#define __JOHNSON_H__

#include <iostream>
#include "Graph.h"
#include "Node.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "Solution.h"


//MERGE_START

class Johnson {
	
	static void connectSource(Graph *graph) {
		for(int t=1; t<graph->getNumberOfNodes(); t++)
			graph->getNodeAt(0)->connect(graph->getNodeAt(t), 0);
	}
	
	static void disconnectSource(Graph *graph) {

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

/*	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){

		int F = subsidiaries->size();
		int tempCost;
		
		int **deslocationCost = new int*[F];
		int *aux = new int[F];
		
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

		// std::cout << "before dijkstra " << graph << std::endl;


		for(int u = 0; u < F; u++) {
			Dijkstra::run(graph, subsidiaries->at(u));
// 			std::cout << "after dijkstra " << graph << std::endl;

			for(int v = 1; v < graph->getNumberOfNodes(); v++){
				deslocationCost[u][v] = graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(u));
			}
		}
		
		for(int v = 1; v < graph->getNumberOfNodes(); v++){
			tempCost = 0;
			
			for(int u = 0; u < F; u++) {
				tempCost += deslocationCost[u][v];
			}
			
			if(tempCost < answer->totalLoss) {
				answer->totalLoss = tempCost;
				answer->location = v;
				
				for(int u = 0; u < F; u++)
					aux[u] = deslocationCost[u][v];
				
				answer->deslocationCost = aux;
			}
		}
	}*/

	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){
		
		int F = subsidiaries->size(), temp_loss = 0;
		
		int *aux, *temp = new int[F];
		for(int i=0; i<F; i++)
			temp[i] = 99999;
		
		connectSource(graph);
		BellmanFord::run(graph, 0);
		disconnectSource(graph);
// 		std::cout << graph << std::endl;
		
		copyCostToH(graph);
		for(int t = 1; t < graph->getNumberOfNodes(); t++){
			graph->getNodeAt(t)->reweightEdges();
		}

// 		std::cout << "before dijkstra " << graph << std::endl;

		for(int v = 1; v < graph->getNumberOfNodes(); v++){
			
			for(int u = 0; u < F; u++) {
				Dijkstra::run(graph, subsidiaries->at(u));		// unnecessary runs of dijkstra
// 				std::cout << "after dijkstra " << graph << std::endl;
				
				temp[u] = graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(u));
			}
			
			temp_loss = 0;
			
			for(int u = 0; u < F; u++)
				temp_loss = temp_loss + temp[u];
			
			std::cout << v << ": " << temp_loss << std::endl;
			
			if(temp_loss < answer->totalLoss) {
				answer->totalLoss = temp_loss;
				answer->location = v;
				
				aux = temp;
				temp = answer->deslocationCost;
				answer->deslocationCost = aux;
			}
		}
		
		std::cout << std::endl;

		delete[] temp;
	}

};
//MERGE_END


#endif


