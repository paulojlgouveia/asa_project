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
		Node* node;
		
		stack.push(startNode);
		
		while(stack.size() != 0){
			node = stack.top();
			node->visit();
			stack.pop();
			
			std::cout << node->getId() << std::endl;

			for(Connection* child : node->getConnections()){
				if (!child->getNext()->visited())
					stack.push(child->getNext());
			}
		}
	}
	
	static void bfs(Graph* g) {
		std::cout << std::endl << "breadth first search" << std::endl << std::endl;
	}
};

#endif
