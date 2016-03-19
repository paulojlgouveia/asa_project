#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <iostream>
#include <stack>
#include <list>

#include "Graph.hpp"
#include "Solution.hpp"

class Search {

public:
	
	Search() {}
	~Search() {}
	
	static void updateSolution(Solution* result, int id) {
		
		result->artNodesCounter++;
		
		if(result->minID == -1 || result->maxID == -1)
			result->minID = result->maxID = id;
		
		else if(id < result->minID)
			result->minID = id;
		
		else if(id > result->maxID)
			result->maxID = id;
	}
	
	
	static Solution findArticulationNodes(Graph* g) {
		
		return Search::findArticulationNodes_tarjan_modified(g);
// 		return findArticulationNodes_standard_dfs(g);

	}
	
	
/*********************** with tarjan modified *****************************/
	
	static Solution findArticulationNodes_tarjan_modified(Graph* g) {

		// maybe create heap to store articulation nodes, geting min and max = log(v)
		std::vector<bool>* artNodes = new std::vector<bool>(g->getNumberOfNodes());
		Node* node;
		Solution result;
			
		int time = 0;
		for(int t=0; t<g->getNumberOfNodes(); t++) {
			node = g->getNodeAt(t);
			if(!node->visited())
				Search::articulationPoints(g, node, artNodes, &time);	
		}

		for(int t=0; t<g->getNumberOfNodes(); t++) {
			if((*artNodes)[t] == true) {
				Search::updateSolution(&result, (t+1));
			}
		}
		
		delete(artNodes);		
		return result;
	}
	
	
	// recursive
	static void articulationPoints(Graph* g, Node* parentNode, std::vector<bool>* artNodes, int* time) {
		
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
// 					artNodes->push_back(parentNode->getId());
					(*artNodes)[parentNode->getId()-1] = true;
				}

				// 2- parentNode is not root,
				// and low value of one of its successors is higher than discovery value of parentNode
				
				if(parentNode->getParent() != NULL && successorNode->getLow() > parentNode->getDiscoveryTime()) {
// 					artNodes->push_back(parentNode->getId());
					(*artNodes)[parentNode->getId()-1] = true;
				}

			} else {
				if(successorNode != parentNode->getParent())
					if(successorNode->getDiscoveryTime() < parentNode->getLow())
						parentNode->setLow(successorNode->getDiscoveryTime());
			}
			
		}
	
	}
	
	
/******************************* with N dfs *******************************/

	static Solution findArticulationNodes_standard_dfs(Graph* g) {
		
		Node* node;
		Solution result;
		
		for(int t=0; t<g->getNumberOfNodes(); t++) {		
			node = g->getNodeAt(t);
			node->disable();
								
			if (t>0)
				Search::dfs(g->getNodeAt(0));
			else
				Search::dfs(g->getNodeAt(1));
			
			if (!g->allVisited()) {
				Search::updateSolution(&result, node->getId());
			}
			
			node->enable();
			g->resetVisited();
		}
		
		return result;
	}
	
	
/*auxilary funtions*/
	
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


	
	
	
	
	
	
};


#endif






