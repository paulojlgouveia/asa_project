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
	
	static int getBestLocation(int *deslocationCost, int V) {
		int min_location = 99999;
		int min_cost = 99999;
		
		for(int v = 0; v < V; v++){
			if(deslocationCost[v] < min_cost){
				min_cost = deslocationCost[v];
				min_location = v;
			}
		}
		return min_location;
	}
	
	
public:
	// corrigi frees e descomentei esta, comentei a outra para submeter
	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){

		int F = subsidiaries->size();
		int tempCost;
		
		int **aux_deslocationCost = new int*[F];
		int *temp, *aux = new int[F];
		
		for(int i=0; i<F; i++) {
			aux_deslocationCost[i] = new int[graph->getNumberOfNodes()];
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
				aux_deslocationCost[u][v] = graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
			}
		}
		
		for(int v = 1; v < graph->getNumberOfNodes(); v++){
			tempCost = 0;
			
			for(int u = 0; u < F; u++) {
				tempCost += aux_deslocationCost[u][v];
			}
			
			if(tempCost < answer->totalLoss) {
				answer->totalLoss = tempCost;
				answer->location = v;
				
				for(int u = 0; u < F; u++)
					aux[u] = aux_deslocationCost[u][v];
				
				temp = aux;
				aux = answer->deslocationCost;
				answer->deslocationCost = temp;
			}
		}
		
		for(int t=0; t<F; t++)
			delete[] aux_deslocationCost[t];
		delete[] aux_deslocationCost;
		
		delete[] aux;
	}
	
//  	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){
// 		std::list<int>::iterator listIterator;
//  
// 		int V = graph->getNumberOfNodes();
//  		int F = subsidiaries->size();
//  		int *aux_deslocationCost = new int[V];
//  		int bestLocation;
//  
//  		connectSource(graph);
//  		BellmanFord::run(graph, 0);
//  		disconnectSource(graph);
//   
//  		copyCostToH(graph);
//  		for(int t = 1; t < V; t++){
//  			graph->getNodeAt(t)->reweightEdges();
//  			aux_deslocationCost[t] = 0;
//  		}
// 
//  		for(int u = 0; u < F; u++) {
//  			Dijkstra::run(graph, subsidiaries->at(u));
//  
//  			for(int v = 0; v < V; v++){
// 				if(aux_deslocationCost[v] != 99999)
// 					aux_deslocationCost[v] += graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
// 				else
// 					aux_deslocationCost[v] = 99999;
//  			}
//  		}
//  		
//  		bestLocation = getBestLocation(aux_deslocationCost, V);
//  	
//  		//Check if best location is valid *FIXME*
//  		
//  		answer->totalLoss = aux_deslocationCost[bestLocation];
// 		answer->location = bestLocation;
//  	
//  		for(int u = 0; u < F; u++) {
// 			Dijkstra::run(graph, subsidiaries->at(u));
// 			answer->deslocationCost[u] = graph->getNodeAt(bestLocation)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
//  		}
//  		 		
// 		delete[] aux_deslocationCost;	
// 	}




// 	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){
// 
// 		int F = subsidiaries->size(), temp_loss = 0;
// 
// 		int *aux, *temp = new int[F];
// 		for(int i=0; i<F; i++)
// 			temp[i] = 99999;
// 
// 		connectSource(graph);
// 		BellmanFord::run(graph, 0);
// 		disconnectSource(graph);
// // 		std::cout << graph << std::endl;
// 
// 		copyCostToH(graph);
// 		for(int t = 1; t < graph->getNumberOfNodes(); t++){
// 			graph->getNodeAt(t)->reweightEdges();
// 		}
// 
// // 		std::cout << "before dijkstra " << graph << std::endl;
// 
// 		for(int v = 1; v < graph->getNumberOfNodes(); v++){
// 
// 			for(int u = 0; u < F; u++) {
// 				Dijkstra::run(graph, subsidiaries->at(u));		// unnecessary runs of dijkstra
// // 				std::cout << "after dijkstra " << graph << std::endl;
// 
// 				temp[u] = graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
// 			}
// 
// 			temp_loss = 0;
// 			for(int u = 0; u < F; u++)
// 				temp_loss = temp_loss + temp[u];
// 
// // 			std::cout << v << ": " << temp_loss << std::endl;
// 
// 			if(temp_loss < answer->totalLoss) {
// 				answer->totalLoss = temp_loss;
// 				answer->location = v;
// 
// 				aux = temp;
// 				temp = answer->deslocationCost;
// 				answer->deslocationCost = aux;
// 			}
// 		}
// 
// // 		std::cout << std::endl;
// 
// 		delete[] temp;
// 	}

};

//MERGE_END



//  	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){
// 		std::list<int>::iterator listIterator;
//  
// 		int V = graph->getNumberOfNodes();
//  		int F = subsidiaries->size();
//  		int *deslocationCost = new int[V];
//  		int bestLocation;
// 		
// 		BMinHeap* Q = new BMinHeap(graph->getNumberOfNodes());
// // 		for(int t=1; t<graph->getNumberOfNodes();t++)
// // 			Q->insert(graph->getNodeAt(t));
//  
//  		connectSource(graph);
//  		BellmanFord::run(graph, 0);
//  		disconnectSource(graph);
//   
//  		copyCostToH(graph);
//  		for(int t = 1; t < V; t++){
//  			graph->getNodeAt(t)->reweightEdges();
//  			deslocationCost[t] = 0;
//  		}
// 
//  		for(int u = 0; u < F; u++) {
// 			for(int t=1; t<graph->getNumberOfNodes();t++)
// 				Q->insert(graph->getNodeAt(t));
// 			
//  			Dijkstra::run(graph, subsidiaries->at(u), Q);
//  
//  			for(int v = 0; v < V; v++){
// 				if(deslocationCost[v] != 99999)
// 					deslocationCost[v] += graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
// 				else
// 					deslocationCost[v] = 99999;
//  			}
//  		}
//  		
//  		bestLocation = getBestLocation(deslocationCost, V);
//  	
//  		//Check if best location is valid *FIXME*
//  		
//  		answer->totalLoss = deslocationCost[bestLocation];
// 		answer->location = bestLocation;
//  	
//  		for(int u = 0; u < F; u++) {
// 			for(int t=1; t<graph->getNumberOfNodes();t++)
// 				Q->insert(graph->getNodeAt(t));
// 			
// 			Dijkstra::run(graph, subsidiaries->at(u), Q);
// 			answer->deslocationCost[u] = graph->getNodeAt(bestLocation)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
//  		}
//  		
//  		delete[] deslocationCost;
//  		
// 		delete(Q);
//  	}





#endif


