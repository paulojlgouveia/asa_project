#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <list>

#include "Edge.h"

// class Edge;

//MERGE_START
class Node {
	int _adjSize; 					// size of adjacencies list (because of c++98)
	std::list<Edge*>* _adjList;		// list of adjacent nodes
	
	int _pathCost;
	int _h;
	
	int _heapIndex;
	
	
public:

// constructors
	Node() : _adjSize(0), _pathCost(99999), _heapIndex(-1) {
		_adjList = new std::list<Edge*>();
	}

// destructors
	virtual ~Node() {
	deleteAdjacencies();
}
	
	void clearAdjacencies();
	void deleteAdjacencies();
	
// getters
	int getAdjacenciesSize() const { return _adjSize; }
	int getPathCost() const { return _pathCost; }
	int getH() const { return _h; }

	std::list<Edge*>* getAdjacenciesList() const { return _adjList; }
	int getHeapIndex() const { return _heapIndex; }
	
// setters
	void setPathCost(int cost) { _pathCost = cost; }
	void setH(int h) { _h = h; }
	
	void setHeapIndex(int index) { _heapIndex = index; }
	
	
// methods
	void connect(Node* adjacent, int weight);
	void reweightEdges();
	int getReweightPathCost(Node *source);


};

//MERGE_END

#endif


