#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <iostream>
#include <stack>

#include "Graph.hpp"


class Search {
	
public:
	
	Search() {}
	~Search() {}
	
/*algorithms*/
	
	//Iterative DFS
	static void dfs(Node *startNode) {
		std::stack<Node*> stack;
		Node* currentNode;
		
		stack.push(startNode);
		
		while (stack.size() != 0){
			currentNode = stack.top();
			currentNode->visit();
			stack.pop();
			
			std::cout << currentNode->getId() << std::endl;

			for(Node* node : currentNode->getActiveNodes())
				stack.push(node);
		}
	}
	
	static void bfs(Graph* g) {
		std::cout << std::endl << "breadth first search" << std::endl << std::endl;
	}
};

#endif
