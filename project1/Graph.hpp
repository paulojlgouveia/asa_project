#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>

#include "Node.hpp"

class Graph {
	
	std::vector<Node*> _nodes; 
	
public:
	
	Graph (int N) {
		
		int one=0, two=0, t;
		
		for(t=1; t<=N; t++)
			_nodes.push_back(new Node(t));
		
		for(t=1; t<N; t++) {
			std::cin >> one;
			std::cin >> two;
			
			std::cout << std::endl << t << ": " << "connecting " << one << " and " << two << std::endl;
			
			_nodes[one-1]->connect(_nodes[two-1]);	// vector starts at index 0
			_nodes[two-1]->connect(_nodes[one-1]);	// file starts at 1

		}
	}
	
	virtual ~Graph() {
		for(unsigned t=0; t<=_nodes.size(); t++)
			delete(_nodes[t]);
	}
	
	
	int getNumberOfNodes() const { return _nodes.size(); }
	
	Node* getNodeAt(int index) const { return _nodes[index]; }
	
	
	friend std::ostream &operator<<(std::ostream &out, const Graph *graph) {
		out << std::endl;
		for(int t=0; t<graph->getNumberOfNodes(); t++) {
			out << graph->getNodeAt(t) << std::endl;
		}
		
		return out;
	}
	
};

#endif
