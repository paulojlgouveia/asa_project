
#include <climits>
#include "Node.h"

// constructors
	Node::Node(int id) : _id(id), _adjSize(0), _pathCost(INT_MAX), _visited(false), _parent(NULL) {
		_adjList = new std::list<Edge*>();
	}

// destructors
	Node::~Node() {
		deleteAdjacencies();
	}
	
	
	void Node::deleteAdjacencies() {
		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList = getAdjacenciesList();
		
		
		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
			delete(*adjIterator);
		}
		
		delete(_adjList);
	}
	
	void Node::clearAdjacencies() {
		deleteAdjacencies();
		_adjList = new std::list<Edge*>();
	}
	
	
// methods
	void Node::connect(Node* adjacent, int weight) {
		Edge* edge = new Edge(adjacent, weight);
		
		_adjList->push_front(edge);
		_adjSize++;
	}
	

	void Node::reweightEdges() {
		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList = getAdjacenciesList();
		Edge *edge;	
	
		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
			edge = (*adjIterator);
			
			edge->setWeight(edge->getWeight() + getH() - edge->getNext()->getH());
		}
	}

	int Node::getReweightPathCost(Node *source) {
		if(getPathCost() != 99999)
			return getPathCost() - source->getH() + getH();
		return getPathCost();
	}

	
	
	
// operators
	std::ostream &operator<<(std::ostream &out, const Node *node) {
		
		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList = node->getAdjacenciesList();
		
  		out << node->getId() << " (" << node->getPathCost() << "|" << node->getH() << "):   ";
		
		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
 			if(adjIterator != adjList->begin())
 				out << " ,  ";
 			out << (*adjIterator)->getNext()->getId();
 			out << "|" << (*adjIterator)->getWeight();
		}
		
 		return out;
 	}
 	
 	




