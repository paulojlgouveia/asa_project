#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>

#include "Edge.h"
#include "Node.h"

//MERGE_START

class Graph {
	int _vertices;					// number of vertices
 	std::vector<Node*> *_nodes;		// list of nodes
	
public:
	
// constructors
	Graph(int V, int E) : _vertices(V+1) {
		int node1=0, node2=0, weight=0;
		_nodes = new std::vector<Node*>();
		
		for(int t = 0; t < _vertices; t++)
			_nodes->push_back(new Node());
		
		//read edges from stdin
		for(int t = 0; t < E; t++) {
			std::cin >> node1;
			std::cin >> node2;
			std::cin >> weight;
			
			//connect nodes (index = id - 1)
			_nodes->at(node1)->connect(_nodes->at(node2), weight);
		}
	}

// destructors
	~Graph() {
		for(int t = 0; t < _vertices; t++) {
			delete(_nodes->at(t));
		}
		
		delete(_nodes);
	}
	
// getters
	int getNumberOfNodes() const { return _vertices; }
	std::vector<Node*>* getNodesArray() const { return _nodes; }
	Node* getNodeAt(int index) const { return _nodes->at(index); }



};

//MERGE_END


#endif

