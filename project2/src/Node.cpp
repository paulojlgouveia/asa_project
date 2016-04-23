
#include <climits>
#include "Node.h"
//MERGE_START

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
	if(getPathCost() < 99999)
		return getPathCost() - source->getH() + getH();
	return getPathCost();
}


 
//MERGE_END
 	




