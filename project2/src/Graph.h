#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>

#include "Node.h"


class Graph {
	int _vertices;					// number of vertices
	int _edges;						// number of edges
 	std::vector<Node*> _nodes;		// list of nodes
	
	
public:
	
// constructors
	Graph(int V, int E);
	
// destructors
	virtual ~Graph();
	
// getters
	int getNumberOfNodes() const ;
	int getNumberOfEdges() const ;
	std::vector<Node*> getNodesArray() const ;
	Node* getNodeAt(int index) const ;

// methods
	void resetVisited();
	bool allVisited() const ;
	
	
	
// operators
	friend std::ostream &operator<<(std::ostream &out, const Graph *graph);
	
	
};

#endif
