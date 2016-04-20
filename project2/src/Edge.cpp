
#include <iostream>

#include "Edge.h"

//MERGE_START
// constructors
Edge::Edge(Node* next, int weight) : _next(next), _weight(weight) { }

// destructors
Edge::~Edge() { }
	
	
// getters
Node* Edge::getNext() const { return _next; }
int Edge::getWeight() const { return _weight; }
	

// setters
void Edge::setNext(Node* next) { _next = next; }
void Edge::setWeight(int weight) { _weight = weight; }
//MERGE_END


	
	