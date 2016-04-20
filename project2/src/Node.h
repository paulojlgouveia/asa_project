#ifndef __NODE_H__
#define __NODE_H__

#include <iostream> 
#include <list>

#include "Edge.h"

// class Edge;


class Node {
	int _id;						// node id
	int _adjSize; 					// size of adjacencies list (because of c++98)
	
	int _pathCost;

	bool _visited;
	Node* _parent;					// points to parent (used during search)
	std::list<Edge*>* _adjList;		// list of adjacent nodes

	
public:

// constructors
	Node(int id);

// destructors
	virtual ~Node();
	
	void clearAdjacencies();
	void deleteAdjacencies();
	
// getters
	int getId() const { return _id; }
	int getAdjacenciesSize() const { return _adjSize; }
	int getPathCost() const { return _pathCost; }
	
	bool visited() const { return _visited; }
	Node* getParent() const { return _parent; }
	std::list<Edge*>* getAdjacenciesList() const { return _adjList; }
	
	
// setters
	void setId(int id) ;
	void setPathCost(int cost);
	
	void setVisited(bool visited);
	void setParent(Node* parent);	
	
	
// methods
	void connect(Node* adjacent, int weight);
	
	
// operators
	friend std::ostream &operator<<(std::ostream &out, const Node *node);

	
};


#endif


