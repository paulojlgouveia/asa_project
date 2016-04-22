#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>

#include "Edge.h"
#include "Node.h"

//MERGE_START
class Graph {
	int _vertices;					// number of vertices
	int _edges;						// number of edges
 	std::vector<Node*> *_nodes;		// list of nodes
	
	
public:
	
// constructors
	Graph(int V, int E) : _vertices(V+1), _edges(E) {
		int node1=0, node2=0, weight=0;
// 		int removed = 0;
		_nodes = new std::vector<Node*>();
// 		_nodes->reserve(_vertices);
		
		for(int t = 0; t < _vertices; t++)
			_nodes->push_back(new Node(t));
		
		//read edges from stdin
		for(int t = 0; t < _edges; t++) {
			std::cin >> node1;
			std::cin >> node2;
			std::cin >> weight;
			
			//connect nodes (index = id - 1)
// 			(*_nodes)[node1-1]->connect((*_nodes)[node2 - 1], weight);
			
// 			if(node1 == node2)
// 				removed++;
// 			else
				_nodes->at(node1)->connect(_nodes->at(node2), weight);
// 				_nodes->at(node2)->connect(_nodes->at(node1), weight);
		}
		
// 		_edges -= removed;
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
	int getNumberOfEdges() const { return _edges; }
	std::vector<Node*>* getNodesArray() const { return _nodes; }
	Node* getNodeAt(int index) const { return _nodes->at(index); }

	
// methods
	void resetVisited() {
		for(int t = 0; t <= _vertices; t++)
			(*_nodes)[t]->setVisited(false);
	}

	bool allVisited() const {
		for(int t = 0; t <= _vertices; t++)
			if((*_nodes)[t]->visited() == false)
				return false;
		return true;
	}
	
	
		
// operators
	friend std::ostream &operator<<(std::ostream &out, const Graph *graph) {
		
  		out << std::endl;
		for(int t=0; t<graph->getNumberOfNodes(); t++) {
			out << graph->getNodeAt(t) << std::endl;
		}
		
 		return out;
 	}
	
	

};
//MERGE_END


#endif

