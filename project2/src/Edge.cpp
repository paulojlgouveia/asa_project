
#include <iostream>

#include "Edge.h"

//MERGE_START

	
// getters
Node* Edge::getNext() const { return _next; }
int Edge::getWeight() const { return _weight; }
	

// setters
void Edge::setNext(Node* next) { _next = next; }
void Edge::setWeight(int weight) { _weight = weight; }
//MERGE_END


	
	