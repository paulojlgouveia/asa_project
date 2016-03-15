#ifndef __GRAPH2_H__
#define __GRAPH2_H__
#include <iostream>
#include <vector>

#include "Node.hpp"

class Graph {
	
	std::vector<Node*> _nodes; 
	
public:
	
	Graph(int N, int E) {
		int one=0, two=0, t;
		
		for(t=1; t<=N; t++)
			_nodes.push_back(new Node(t));
		
		for(t=1; t<E; t++) {
			std::cin >> one;
			std::cin >> two;
			
			_nodes[one-1]->addActiveNode(_nodes[two-1]);	// vector starts at index 0
			_nodes[two-1]->addActiveNode(_nodes[one-1]);	// file starts at 1
		}
	}
	
	Graph(Graph* graph) {
		for(Node* nd : graph->getNodes())
			_nodes.push_back(new Node(nd));
	}
	
	virtual ~Graph() {
		for(unsigned t=0; t<_nodes.size(); t++)
			delete(_nodes[t]);
	}
	
/*getters*/

	std::vector<Node*> getNodes() const { return _nodes; }

	int getNumberOfNodes() const { return _nodes.size(); }
	
	Node* getNodeAt(int index) const { return _nodes[index]; }
	
	bool allVisited() {
		for(Node* node : _nodes)
			if(node->visited() == false)
				return false;
		
		return true;
	}
	
/*operators*/
	
	friend std::ostream &operator<<(std::ostream &out, const Graph *graph) {
		out << std::endl;
		for(int t=0; t < graph->getNumberOfNodes(); t++) {
			out << graph->getNodeAt(t) << std::endl;
		}
		
		return out;
	}
	
};

#endif
