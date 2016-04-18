#ifndef __NODE_H__
#define __NODE_H__

#include <iostream> 
#include <list>

#include "Edge.h"

// class Edge;


class Node {
	int _id;						// node id
	int _adjSize; 					// size of adjacencies list (because of c++98)
	int _discoveryTime;				// time in which the node was discovered (used during search)
	int _low;						// used to fing backedges (used during search)
	bool _visited;					// marks the node as visited (used during search)

	Node* _parent;					// points to parent (used during search)
	std::list<Edge*>* _adjList;		// list of adjacent nodes

	
public:

// constructors
	Node(int id);

// destructors
	virtual ~Node();
	
// getters
	int getId() const ;
	int getAdjacenciesSize() const ;
	int getDiscoveryTime() const ;
	int getLow() const ;
	bool visited() const ;
	Node* getParent() const ;
	std::list<Edge*>* getAdjacenciesList() const ;
	
	
// setters
	void setId(int id) ;
	void setVisited(bool visited);
	void setDiscoveryTime(int time);
	void setLow(int low);
	void setParent(Node* parent);	
	
	
// methods
	void connect(Node* adjacent, int weight);
	
	
// operators
	friend std::ostream &operator<<(std::ostream &out, const Node *node);

	
};


#endif


