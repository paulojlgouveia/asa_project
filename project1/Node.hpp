#ifndef __NODE_H__
#define __NODE_H__

#include <iostream> 
#include <list>


class Node {
	int _id;
	std::list<Node*>* _adj;		// pointer because passable without copy
	int _adj_size; 				// in c++98 getting list size is lenear (solved with iterator)
	bool _visited;
	
	bool _active;				// used for N dfs
	
	Node* _parent;				// used to search articulation nodes
	int _discovery;
	int _low;

	
public:
	
	Node(int id) :	_id(id), _adj_size(0), _visited(false),
					_active(true),
					_parent(NULL), _discovery(-1), _low(-1) {
						
		_adj = new std::list<Node*>();
	}
	
	virtual ~Node() { delete(_adj); }
	
	
/*getters*/

	int getId() const { return _id; }
	std::list<Node*>* getAdjacenciesList() const { return _adj; }
	int getAdjacenciesSize() const { return _adj_size; }
	bool visited() const { return _visited; }
	
	int isActive() const { return _active; }
	
	Node* getParent() const { return _parent; }
	int getDiscoveryTime() const { return _discovery; }
	int getLow() const { return _low; }
	
	
/*setters*/

	void setID(int id) { _id = id; }
	void visit() { _visited = true; }
	void resetVisit() { _visited = false; }
	
	void enable() { _active = true; }
	void disable() { _active = false; }
	
	void setParent(Node* parent) { _parent = parent; }
	void setDiscoveryTime(int dt) { _discovery = dt; }
	void setLow(int low) { _low = low; }
	
	
/*modifiers*/

	void connect(Node* adjacent) {
		_adj->push_front(adjacent);
		_adj_size++;
	}
	
	
	
/*operators*/

	friend std::ostream &operator<<(std::ostream &out, const Node *node) {
				
		std::list<Node*>* adj = node->getAdjacenciesList();
		std::list<Node*>::iterator adj_iter;
		
		out << node->getId() << "|" << node->isActive() << ":   ";
		
		for(adj_iter=adj->begin(); adj_iter!=adj->end(); adj_iter++) {
			if(adj_iter != adj->begin())
				out << " ,  ";
			out << (*adj_iter)->getId();
			out << "|" << (*adj_iter)->isActive();
		}
		
		return out;
	}



};


#endif
