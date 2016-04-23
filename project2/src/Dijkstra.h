#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include <iostream>
#include <climits>
#include <stack>
#include <queue>
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

	static void relax(Node *u, Node *v, int weight, BMinHeap *Q){
		
		if(v->getPathCost() > (u->getPathCost() + weight)) {
			v->setPathCost(u->getPathCost() + weight);
			v->setParent(u);
			Q->decreaseKey(v->getHeapIndex());

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
// 			std::cout  << std::endl << "Q: " << Q;
			node1 = Q->extractMin();
// 			std::cout << std::endl << "removed " << node1->getId() << std::endl;
			
			adjList = node1->getAdjacenciesList();
			for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
				node2 = (*adjIterator)->getNext();
				weight = (*adjIterator)->getWeight();
				
				relax(node1, node2, weight, Q);
			}
		}
		
		delete(Q);
	}

	
};
//MERGE_END

#endif








