
#include "Graph.h"

	
// constructors
	Graph::Graph(int V, int E) : _vertices(V), _edges(E) {
		int node1=0, node2=0, weight=0;
		
		for(int t = 1; t <= V; t++)
			_nodes.push_back(new Node(t));
		
		//read edges from stdin
		for(int t = 0; t < _edges; t++) {
			std::cin >> node1;
			std::cin >> node2;
			std::cin >> weight,
			
			//connect nodes (index = id - 1)
			_nodes[node1-1]->connect(_nodes[node2 - 1], weight);
		}	
	}

	
// destructors
	Graph::~Graph() {
		for(int t = 0; t < _vertices; t++)
			delete(_nodes[t]);
	}
	
	
// getters
	int Graph::getNumberOfNodes() const { return _vertices; }
	int Graph::getNumberOfEdges() const { return _edges; }
	std::vector<Node*> Graph::getNodesArray() const { return _nodes; }
	Node* Graph::getNodeAt(int index) const { return _nodes[index]; }

	
// methods
	void Graph::resetVisited() {
		for(int t = 0; t < _vertices; t++)
			_nodes[t]->setVisited(false);
	}

	bool Graph::allVisited() const {
		for(int t = 0; t < _vertices; t++)
			if(_nodes[t]->visited() == false)
				return false;
		return true;
	}
	
	
		
// operators
	std::ostream &operator<<(std::ostream &out, const Graph *graph) {
		
  		out << std::endl;
  		for(int t=0; t<graph->getNumberOfNodes(); t++) {
 			out << graph->getNodeAt(t) << std::endl;		 
 		}
 		
 		return out;	
 	}
	
	



