#ifndef __NODE_H__
#define __NODE_H__

#include <iostream> 
#include <list>

//MERGE_START
class Node {
	int _id;						// node id
	int _adjSize; 					// size of adjacencies list
	int _discoveryTime;				// time in which the node was discovered (used during search)
	int _low;						// used to fing backedges (used during search)
	bool _visited;					// marks the node as visited (used during search)

	Node* _parent;					// points to parent (used during search)
	std::list<Node*>* _adjList;		// list of adjacent nodes

// constructors
public:
	Node(int id) : _id(id), _adjSize(0), _discoveryTime(-1),
				   _low(-1), _visited(false), _parent(NULL) {
		
		_adjList = new std::list<Node*>();
	}

// destructors
public:
	virtual ~Node() { delete(_adjList); }
	
	
// getters
public:
	int getId() const { return _id; }
	int getAdjacenciesSize() const { return _adjSize; }
	int getDiscoveryTime() const { return _discoveryTime; }
	int getLow() const { return _low; }
	bool visited() const { return _visited; }
	
	Node* getParent() const { return _parent; }
	std::list<Node*>* getAdjacenciesList() const { return _adjList; }
	
// setters
public:
	void setId(int id) { _id = id; }
	void setVisited(bool visited) { _visited = visited; }	
	void setDiscoveryTime(int time) { _discoveryTime = time; }
	void setLow(int low) { _low = low; }

	void setParent(Node* parent) { _parent = parent; }	
	
// methods
public:
	void connect(Node* adjacent) {
		_adjList->push_front(adjacent);
		_adjSize++;
	}
};
//MERGE_END

#endif
