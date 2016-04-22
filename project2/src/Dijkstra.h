#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include <iostream>
#include <climits>
#include <stack>
#include <list>
#include "Graph.h"
#include "Node.h"
#include "BHeap.h"

#include <unistd.h>

//MERGE_START
class Dijkstra {
	
public:
// 	static void updateSolution(Solution* solution) {}

	
// 	Initialize-Single-Source(G, s)
// 		for each v ∈ V [G]
// 			do	d[v ] ← ∞
// 				π[v ] ← NIL
// 		d [s] ← 0

	static void initializeSingleSource(Graph* graph, Node* s) {
		for (int t = 0; t < graph->getNumberOfNodes(); t++) {
			graph->getNodeAt(t)->setPathCost(99999);
			graph->getNodeAt(t)->setParent(NULL);
			graph->getNodeAt(t)->setVisited(false);
		}
		s->setPathCost(0);
	}


// 	Relax(u , v , w )
// 		if d [v ] > d [u] + w (u, v )
// 			then	d [v ] ← d [u ] + w (u , v )
// 					π[v ] ← u

	static void relax(Node *u, Node *v, int weight){
		
		if(v->getPathCost() > (u->getPathCost() + weight)) {
			v->setPathCost(u->getPathCost() + weight);
			v->setParent(u);
		}
			v->setVisited(true);
	}


// 	Dijkstra(G, w , s)
// 		Initialize-Single-Source(G , s)
// 		S ← 0 /
// 		Q ← V [G]	✄ Fila de Prioridade
//
// 		while Q != 0
// 			do u ← Extract-Min(Q)
// 				S ← S ∪ {u }
// 				for each v ∈ Adj [u]
// 					do Relax(u, v , w )		✄ Actualização de Q

	static void run(Graph* graph, int index) {
		run(graph, graph->getNodeAt(index));
	}

// 	static void run(Graph* graph, Node* s) {
// 		
// 		std::cout << std::endl<< std::endl<< "s: " << s->getId() << std::endl;
// 
// 		Node *node1, *node2;
// 		int weight;
// 		
// // 		std::list<Node*>* S = new std::list<Node*>();
// 		
// 		BMinHeap* Q = new BMinHeap(graph->getNumberOfNodes());
// 		Q->insert(s);
// 
// 		std::list<Edge*>::iterator adjIterator;
// 		std::list<Edge*>* adjList;
// 		
// 		initializeSingleSource(graph, s);
// 
// 		while(Q->size() > 0) {
// 
// // 			std::cout  << std::endl << "Q: " << Q;
//  			node1 = Q->getMinimum();
// 			Q->removeMinimum();
// 			node1->setVisited(true);
// // 			std::cout << std::endl << "removed "<< node1->getId() << std::endl;
// 
// 			
// 			adjList = node1->getAdjacenciesList();
// 			for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
// 				node2 = (*adjIterator)->getNext();
// 				weight = (*adjIterator)->getWeight();
// 				
// // 				std::cout << node2->getId() << "\t";
// 
// // 				if(node2->getParent() == NULL)
// 				if(!node2->visited())
// 					Q->insert(node2);
// 				
// 				relax(node1, node2, weight);
// // 				usleep(5000);
// 			}
// 		}
// 		
// 		std::cout << graph << std::endl;
// 		
// // 		delete(S);
// 		delete(Q);
// 	}
	
	
// 	static void run(Graph* graph, Node* s) {
// 		
// // 		std::cout << std::endl<< "s: " << s->getId() << std::endl;
// 
// 		Node *node1, *node2;
// 		int weight;
// 		
// // 		std::list<Node*>* S = new std::list<Node*>();
// 		
// 		initializeSingleSource(graph, s);
// 		
// 		BMinHeap* Q = new BMinHeap(graph->getNumberOfNodes());
// // 		Q->insert(s);
// 		for(int t=1; t<graph->getNumberOfNodes();t++)
// // 			if(graph->getNodeAt(t) != s)
// 				Q->insert(graph->getNodeAt(t));
// 		
// 
// 		std::list<Edge*>::iterator adjIterator;
// 		std::list<Edge*>* adjList;
// 		
// 
// 		while(Q->size() > 0) {
// 
// // 			std::cout  << std::endl << "Q: " << Q;
//  			node1 = Q->getMinimum();
// 			Q->removeMinimum();
// // 			node1->setVisited(true);
// // 			std::cout << std::endl << "removed "<< node1->getId() << std::endl;
// 
// 			
// 			adjList = node1->getAdjacenciesList();
// 			for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
// 				node2 = (*adjIterator)->getNext();
// 				weight = (*adjIterator)->getWeight();
// 				
// // 				std::cout << node2->getId() << "\t";
// 
// // 				if(node2->getParent() == NULL)
// // 				if(!node2->visited())
// // 					Q->insert(node2);
// 				
// 				relax(node1, node2, weight);
// 			}
// 		}
// 		
// // 		std::cout << graph << std::endl;
// 		
// // 		delete(S);
// 		delete(Q);
// 	}


	static bool compare_nocase (const Node* first, const Node* second) {
		return ( first->getPathCost() < second->getPathCost() );
	}

	

	static void run(Graph* graph, Node* s) {
		Node *node1, *node2;
		int weight;
		
		initializeSingleSource(graph, s);
		
		BMinHeap* Q = new BMinHeap(graph->getNumberOfNodes());
		for(int t=1; t<graph->getNumberOfNodes();t++)
			Q->insert(graph->getNodeAt(t));
		
		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList;
		
		while(Q->size() > 0) {
			std::cout  << std::endl << "Q: " << Q << std::endl;
			
			node1 = Q->getMinimum();
			Q->removeMinimum();
			
			adjList = node1->getAdjacenciesList();
			for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
				node2 = (*adjIterator)->getNext();
				weight = (*adjIterator)->getWeight();
				
				relax(node1, node2, weight);
			}
		}
		
		delete(Q);
	}
	
	
	
};
//MERGE_END

#endif








