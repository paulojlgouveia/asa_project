#ifndef __NODE_H__
#define __NODE_H__

#include <iostream> 
#include <vector>

class Node {
	int _id;
	std::vector<Node*> _connections;
	
public:
	
	Node(int id) : _id(id) {}
	
	virtual ~Node() {}
	
	
	int getId() const { return _id; }
	
	int getNumberOfConnections() const { return _connections.size(); }
	
	Node* getNodeAt(int index) const { return _connections[index]; }
	
	
	void connect(Node* node) {
		std::cout << "adding to " << _id << " connection to " << node->getId() << std::endl;
		_connections.push_back(node);
	}
	
	
	friend std::ostream &operator<<(std::ostream &out, const Node *node) {
		out << node->getId() << ":  ";
		
		for(int t=0; t<node->getNumberOfConnections(); t++) {
			if(t>0)
				out << ",  ";
			out << node->getNodeAt(t)->getId();
		}
		
		return out;
	}

};


#endif
