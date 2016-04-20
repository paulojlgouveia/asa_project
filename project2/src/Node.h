#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <list>

#include "Edge.h"

// class Edge;

//MERGE_START
class Node {
	int _id;						// node id
	int _adjSize; 					// size of adjacencies list (because of c++98)
	
	int _pathCost;
	int _h;

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
	int getH() const { return _h; }
	
	bool visited() const { return _visited; }
	Node* getParent() const { return _parent; }
	std::list<Edge*>* getAdjacenciesList() const { return _adjList; }
	
	
// setters
	void setId(int id) { _id = id; }
	void setPathCost(int cost) { _pathCost = cost; }
	void setH(int h) { _h = h; }
	
	void setVisited(bool visited) { _visited = visited; }
	void setParent(Node* parent) { _parent = parent; }
	
	
// methods
	void connect(Node* adjacent, int weight);
	void reweightEdges();
	int getReweightPathCost(Node *source);

	
// operators
	friend std::ostream &operator<<(std::ostream &out, const Node *node);

	
};
//MERGE_END

#endif


