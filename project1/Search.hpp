#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <iostream>
#include <stack>
#include <list>

#include "Graph.hpp"

class Search {
	
public:
	
	Search() {}
	~Search() {}
	
/*algorithms*/
	
	// iterative DFS
	static void dfs(Node *startNode) {
		std::stack<Node*> stack;
		std::list<Node*>* adj;
		
		std::list<Node*>::iterator adj_iter;
		Node* node;

		stack.push(startNode);
		
		while(stack.size() != 0){
			node = stack.top();
			node->visit();
			stack.pop();

			adj = node->getAdjacenciesList();

			for(adj_iter=adj->begin(); adj_iter!=adj->end(); adj_iter++) {
				if (!(*adj_iter)->visited())
						if(node->isActive())
							stack.push(*adj_iter);
			}
		}
	}

	
	// recursive
	static void articulationPoints(Graph* g, Node* parentNode, std::list<int>* artNodes, int* time) {
		
		int successors = 0;
		
		(*time)++;
		parentNode->visit();
		
// 		std::cout << parentNode->getId() << std::endl;

		
		parentNode->setDiscoveryTime(*time);
		parentNode->setLow(*time);
		
		std::list<Node*>* adj = parentNode->getAdjacenciesList();
		std::list<Node*>::iterator adj_iter;
		Node* successorNode;
		
		for(adj_iter=adj->begin(); adj_iter!=adj->end(); adj_iter++) {
			successorNode = *adj_iter;	// convert iterator to pointer just to make code simpler
			
			if(!successorNode->visited()) {
				successors++;
				successorNode->setParent(parentNode);
				
				articulationPoints(g, successorNode, artNodes, time);
				
				//correct _low values
				if(successorNode->getLow() < parentNode->getLow())
					parentNode->setLow(successorNode->getLow());
				
				
				// parentNode is articulation node if:
				
				// 1- parentNode is the root of dfs tree and has two or more successors
				
				if(parentNode->getParent() == NULL && successors >= 2) {
					artNodes->push_back(parentNode->getId());
// 					std::cout << "condition 1: " << successorNode->getId()
// 						<< " -> " << parentNode->getId() << std::endl;
				}

				// 2- parentNode is not root,
				// and low value of one of its successors is higher than discovery value of parentNode
				
				if(parentNode->getParent() != NULL && successorNode->getLow() > parentNode->getDiscoveryTime()) {
					artNodes->push_back(parentNode->getId());
// 					std::cout << "condition 2: " << successorNode->getId()
// 						<< " -> " << parentNode->getId() << std::endl;
				}

			} else {
				if(successorNode != parentNode->getParent())
					if(successorNode->getDiscoveryTime() < parentNode->getLow())
						parentNode->setLow(successorNode->getDiscoveryTime());
			}
			
		}
	
	}
	
	
};


#endif






