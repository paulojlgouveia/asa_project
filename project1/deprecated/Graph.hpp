#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>

#include "Node.hpp"


// graph with only one connection per connection (from lowest to highest nodes)
class Graph {
	
	std::vector<Node*> _nodes; 
	
public:
	
	Graph(int N) {
		int one=0, two=0, t;
		
		for(t=1; t<=N; t++)
			_nodes.push_back(new Node(t));
		
		for(t=1; t<N; t++) {
			std::cin >> one;
			std::cin >> two;
			
			if(one<=two)
				_nodes[one-1]->connect(_nodes[two-1]);
			else
				_nodes[two-1]->connect(_nodes[one-1]);
		}
	}
	
	Graph(Graph* graph) {
		for(int i=1; i<=graph->getNumberOfNodes(); i++)
			_nodes.push_back(new Node(i));
		
		for(int i=0; i<graph->getNumberOfNodes(); i++)
			for(int j=0; j<graph->getNodeAt(i)->getNumberOfConnections(); j++)
				_nodes[i]->connect(_nodes[graph->getNodeAt(i)->getConnectionAt(j)->getNext()->getId()-1]);
	}
	
	virtual ~Graph() {
		for(unsigned t=0; t<_nodes.size(); t++)
			delete(_nodes[t]);
	}
	
	
/*getters*/
	
	int getNumberOfNodes() const { return _nodes.size(); }
	
	Node* getNodeAt(int index) const { return _nodes[index]; }
	
	bool allVisited() const {
		for(Node* node : _nodes)
			if(node->visited() == false)
				return false;
		
		return true;
	}
	
	
/*operators*/

	friend std::ostream &operator<<(std::ostream &out, const Graph *graph) {
		out << std::endl;
		for(int t=0; t<graph->getNumberOfNodes(); t++) {
			out << graph->getNodeAt(t) << std::endl;
		}
		
		return out;
	}
	
};

#endif
