#ifndef __GRAPH2_H__
#define __GRAPH2_H__

#include <iostream>
#include <vector>

#include "Node.hpp"

class Graph {
	
	int _verticies;
	int _edges;
	
 	std::vector<Node*> _nodes;
	
public:
	
	Graph(int V, int E) : _verticies(V), _edges(E) {
		int one=0, two=0;
		int t;
		
		// vector of pointers, requires initialization
		for(t=1; t<=V; t++)
			_nodes.push_back(new Node(t));
		
		// read edges from stdin and connect nodes
		for(t=0; t<_edges; t++) {
			std::cin >> one;
			std::cin >> two;
							
			_nodes[one-1]->connect(_nodes[two-1]);	// vector starts at index 0
			_nodes[two-1]->connect(_nodes[one-1]);	// file starts at 1
		}	
	}
	
	virtual ~Graph() {
		for(int t=0; t<_verticies; t++)
			delete(_nodes[t]);
	}
	
	
/*getters*/

	int getNumberOfNodes() const { return _verticies; }
	int getNumberOfEdges() const { return _edges; }
	std::vector<Node*> getNodesArray() const { return _nodes; }
	
	Node* getNodeAt(int index) const { return _nodes[index]; }
	
	bool allVisited() const {
		for(int t=0; t<_verticies; t++)
			if(_nodes[t]->visited() == false)
				return false;

		return true;
	}
	
	
/*modifiers*/

	void resetVisited() {
		for(int t=0; t<_verticies; t++)
			_nodes[t]->resetVisit();
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
