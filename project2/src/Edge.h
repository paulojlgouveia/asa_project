#ifndef __EDGE_H__
#define __EDGE_H__

#include <iostream>

// #include "Node.h"

//MERGE_START

class Node;

class Edge {
	
	Node* _next;
	int _weight;
	Edge* _right;


public:
// constructors
	Edge(Node* next, int weight) : _next(next), _weight(weight), _right(NULL) { }
	
// destructors
	virtual ~Edge() { }
	
// getters
	Node* getNext() const ;
	int getWeight() const ;
	
// setters
	void setNext(Node* next) ;
	void setWeight(int weight) ;

};


//MERGE_END


#endif


