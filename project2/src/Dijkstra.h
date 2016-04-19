#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <iostream>
#include <algorithm>
#include <stack>
#include <list>
#include "Graph.h"
// #include "Solution.h"

class Search {
	
public:
// 	static void updateSolution(Solution* solution) {}

	
// 	Initialize-Single-Source(G, s)
// 		for each v ∈ V [G]
// 			do	d[v ] ← ∞
// 				π[v ] ← NIL
// 		d [s] ← 0

	static void initializeSingleSource(Graph* graph, Node* s) {
		
	}


// 	Relax(u , v , w )
// 		if d [v ] > d [u] + w (u, v )
// 			then	d [v ] ← d [u ] + w (u , v )
// 					π[v ] ← u

	static void relax(Node* node1, Node* node2, int weight) {
		
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

	static void run(Graph* graph, Node* s) {
		Node *node1, *node2;
		int weight;
		
		std::list<Node*>* S = new std::list<Node*>();
		
// 		Heap<Node*>* Q = new Heap<Node*>(graph->getNodesArray());
		std::vector<Node*>* Q = new std::vector<Node*>();
		for(int t=0; t<graph->getNumberOfNodes(); t++)
			S->push_back(graph->getNodeAt(t));
		std::make_heap (Q->begin(), Q->end());
		
		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList;
		
		initializeSingleSource(graph, s);
		
		while(Q->size() > 0) {
			node1 = Q->getMin();
			S->push_front(node1);
			
			adjList = node1->getAdjacenciesList();
			for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {	
				node2 = (*adjIterator)->getNext();
				weight = (*adjIterator)->getWeight();
				relax(node1, node2, weight);
				// FIXME update heap
				
			}
		}
	}
	
};



#endif








