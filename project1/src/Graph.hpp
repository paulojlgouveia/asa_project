#ifndef __GRAPH2_H__
#define __GRAPH2_H__

#include <iostream>
#include <vector>

#include "Node.hpp"

//MERGE_START
class Graph {
	int _vertices;					// number of vertices
	int _edges;						// number of edges
 	std::vector<Node*> _nodes;		// list of nodes
	
// constructors
public:
	Graph(int V, int E) : _vertices(V), _edges(E) {
		int node1=0, node2=0;
		
		for(int t = 1; t <= V; t++)
			_nodes.push_back(new Node(t));
		
		//read edges from stdin
		for(int t = 0; t < _edges; t++) {
			std::cin >> node1;
			std::cin >> node2;
							
			//connect nodes (index = id - 1)
			_nodes[node1-1]->connect(_nodes[node2 - 1]);
			_nodes[node2-1]->connect(_nodes[node1 - 1]);
		}	
	}

// destructors
public:
	virtual ~Graph() {
		for(int t = 0; t < _vertices; t++)
			delete(_nodes[t]);
	}
	
// getters
public:
	int getNumberOfNodes() const { return _vertices; }
	int getNumberOfEdges() const { return _edges; }
	std::vector<Node*> getNodesArray() const { return _nodes; }
	Node* getNodeAt(int index) const { return _nodes[index]; }

// methods
public:
	void resetVisited() {
		for(int t = 0; t < _vertices; t++)
			_nodes[t]->setVisited(false);
	}

	bool allVisited() const {
		for(int t = 0; t < _vertices; t++)
			if(_nodes[t]->visited() == false)
				return false;
		return true;
	}
};
//MERGE_END

#endif
