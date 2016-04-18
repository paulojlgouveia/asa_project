
// #include "Edge.h"
#include "Node.h"

// constructors
	Node::Node(int id) : _id(id), _adjSize(0), _discoveryTime(-1), _low(-1), _visited(false), _parent(NULL) {
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
	
	
// getters
	int Node::getId() const { return _id; }
	int Node::getAdjacenciesSize() const { return _adjSize; }
	int Node::getDiscoveryTime() const { return _discoveryTime; }
	int Node::getLow() const { return _low; }
	bool Node::visited() const { return _visited; }
	Node* Node::getParent() const { return _parent; }
	std::list<Edge*>* Node::getAdjacenciesList() const { return _adjList; }
	
	
// setters
	void Node::setId(int id) { _id = id; }
	void Node::setVisited(bool visited) { _visited = visited; }	
	void Node::setDiscoveryTime(int time) { _discoveryTime = time; }
	void Node::setLow(int low) { _low = low; }
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
		
  		out << node->getId() << ":   ";
		
		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
 			if(adjIterator != adjList->begin())
 				out << " ,  ";
 			out << (*adjIterator)->getNext()->getId();
 			out << "|" << (*adjIterator)->getWeight();
		}
		
 		return out;
 	}
 	
 	




