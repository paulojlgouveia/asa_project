#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include <iostream>
#include <climits>
#include <stack>
#include <list>
#include "Graph.h"
#include "Node.h"
#include "BHeap.h"

// #include "Solution.h"

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
	}


// 	Dijkstra(G, w , s)
// 		Initialize-Single-Source(G , s)
// 		S ← 0 /
// 		Q ← V [G]	✄ Fila de Prioridade
//
// 		while Q = 0 /
// 			do u ← Extract-Min(Q)
// 				S ← S ∪ {u }
// 				for each v ∈ Adj [u]
// 					do Relax(u, v , w )		✄ Actualização de Q

	static void run(Graph* graph, int index) {
		run(graph, graph->getNodeAt(index));
	}

	static void run(Graph* graph, Node* s) {
		
		std::cout << "s: " << s->getId()<< std::endl;

		Node *node1, *node2;
		int weight;
		
// 		std::list<Node*>* S = new std::list<Node*>();
		
// 		BHeap* Q = new BHeap(graph->getNodesArray());
		BHeap* Q = new BHeap();
		Q->push_back(s);

		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList;
		
		initializeSingleSource(graph, s);

		while(Q->size() > 0) {

// 			std::cout << "Q: " << Q;
 			node1 = Q->getMinimum();
			Q->pop_back();
// 			std::cout << "extracted from Q: " << node1->getId() << std::endl<< std::endl;

// 			S->push_front(node1);
			
			adjList = node1->getAdjacenciesList();
			for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
				node2 = (*adjIterator)->getNext();
				weight = (*adjIterator)->getWeight();
				
				if(node2->getParent() == NULL)
					Q->push_back(node2);
				
				relax(node1, node2, weight);
					
			}
		}
		
// 		delete(S);
		delete(Q);
	}
	
};
//MERGE_END

#endif








