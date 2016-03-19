#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <iostream>
#include <stack>
#include <list>
#include "Graph.hpp"
#include "Solution.hpp"

//MERGE_START
class Search {
	
public:
	// updates solution values (struct solution)
	static void updateSolution(Solution* solution, int id) {
		solution->articulationNodes++;
		
		if(solution->minId == -1 || solution->maxId == -1)
			solution->minId = solution->maxId = id;
		else if(id < solution->minId)
			solution->minId = id;
		else if(id > solution->maxId)
			solution->maxId = id;
	}
	
	// finds articulation nodes and returns solution
	static Solution findArticulationNodes(Graph* graph) {
		int time = 0;
		Node* node;
		Solution solution;
		std::vector<bool>* artNodes = new std::vector<bool>(graph->getNumberOfNodes());
			
		for(int t = 0; t < graph->getNumberOfNodes(); t++) {
			node = graph->getNodeAt(t);
			if(!node->visited())
				Search::articulationPoints(graph, node, artNodes, &time);	
		}

		for(int t = 0; t < graph->getNumberOfNodes(); t++) {
			if((*artNodes)[t] == true) {
				Search::updateSolution(&solution, (t + 1));
			}
		}
		
		delete(artNodes);		
		return solution;
	}
	
	// find articulation nodes, algorithm main loop (recursive)
	static void articulationPoints(Graph* graph, Node* parentNode, std::vector<bool>* artNodes, int* time) {
		int successors = 0;
		Node* successorNode;
		std::list<Node*>::iterator adjIterator;
		std::list<Node*>* adjList = parentNode->getAdjacenciesList();
		
		(*time)++;
		parentNode->setVisited(true);
		parentNode->setDiscoveryTime(*time);
		parentNode->setLow(*time);
		
		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
			successorNode = *adjIterator;	// get iterator current node (code simplification)
			
			if(!successorNode->visited()) {
				successors++;
				successorNode->setParent(parentNode);
				
				articulationPoints(graph, successorNode, artNodes, time);
				
				// correct parent's _low value
				if(successorNode->getLow() < parentNode->getLow())
					parentNode->setLow(successorNode->getLow());
				
				// parentNode is articulation node if:
				
				// 1- parentNode is the root of dfs tree and has two or more successors
				if(parentNode->getParent() == NULL && successors >= 2) {
					(*artNodes)[parentNode->getId() - 1] = true;
				}

				// 2- parentNode is not root,
				// and low value of one of its successors is higher than discovery value of parentNode
				if(parentNode->getParent() != NULL && successorNode->getLow() >= parentNode->getDiscoveryTime()) {
					(*artNodes)[parentNode->getId() - 1] = true;
				}

			} else {
				if(successorNode != parentNode->getParent())
				// if node was already visited update low and discovery points
					if(successorNode->getDiscoveryTime() < parentNode->getLow())
						parentNode->setLow(successorNode->getDiscoveryTime());
			}
		}
	}
};
//MERGE_END

#endif






