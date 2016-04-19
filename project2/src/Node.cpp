
#include <climits>
#include "Node.h"

// constructors
	Node::Node(int id) : _id(id), _adjSize(0), _pathCost(INT_MAX), _visited(false), _parent(NULL) {
		_adjList = new std::list<Edge*>();
	}

// destructors
	Node::~Node() {
		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList = getAdjacenciesList();
		
		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
			delete(*adjIterator);
		}
		
		delete(_adjList);
	}
	
	
// setters
	void Node::setId(int id) { _id = id; }
	void Node::setPathCost(int cost) { _pathCost = cost; }

	
	void Node::setVisited(bool visited) { _visited = visited; }	
	void Node::setParent(Node* parent) { _parent = parent; }	
	
	
// methods
	void Node::connect(Node* adjacent, int weight) {
		Edge* edge = new Edge(adjacent, weight);
		
		_adjList->push_front(edge);
		_adjSize++;
	}
	
	
// operators
	std::ostream &operator<<(std::ostream &out, const Node *node) {
		
		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList = node->getAdjacenciesList();
		
  		out << node->getId() << " (" << node->getPathCost() << "):   ";
		
		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
 			if(adjIterator != adjList->begin())
 				out << " ,  ";
 			out << (*adjIterator)->getNext()->getId();
 			out << "|" << (*adjIterator)->getWeight();
		}
		
 		return out;
 	}
 	
 	




