#ifndef __EDGE_H__
#define __EDGE_H__

#include <iostream> 

// #include "Node.h"

class Node;


class Edge {
	
	Node* _next;
	int _weight;

	
public:

// constructors
	Edge(Node* next, int weight);
// destructors
	virtual ~Edge();
	
	
// getters
	Node* getNext() const ;
	int getWeight() const ;
	

// setters
	void setNext(Node* next) ;
	void setWeight(int weight) ;
	
	
// operators
// 	inline friend std::ostream &operator<<(std::ostream &out, const Edge* edge) {
//   		out << edge->getNext()->getId() << "|" << edge->getWeight();
//   		return out;
// 	}

};



#endif


