#ifndef __NODE_H__
#define __NODE_H__

#include <iostream> 
#include <vector>

#include "Connection.hpp" 


class Node {
	int _id;
	std::vector<Connection*> _connections;
	bool _visited;
	
	
public:
	
	Node(int id) : _id(id), _visited(false) {}
	
	virtual ~Node() {
		for(unsigned t=0; t<_connections.size(); t++)
			delete(_connections[t]);
	}
	
	
	int getId() const { return _id; }
	
	bool visited() const { return _visited; }
	
	int getNumberOfConnections() const { return _connections.size(); }
	
	Connection* getConnectionAt(int index) const { return _connections[index]; }
	
	
	void visit() { _visited = true; }
	
	void resetVisit() { _visited = false; }
	
	void connect(Node* node) {
		_connections.push_back(new Connection(node));
	}
	
	
	friend std::ostream &operator<<(std::ostream &out, const Node *node) {
		out << node->getId() << ":   ";
		
		for(int t=0; t<node->getNumberOfConnections(); t++) {
			if(t>0)
				out << " ,  ";
			out << node->getConnectionAt(t)->getNext()->getId();
			out << "|" << node->getConnectionAt(t)->isActive();
		}
		
		return out;
	}

};


#endif
