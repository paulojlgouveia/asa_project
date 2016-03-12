#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <iostream> 
#include <vector>

class Node;	// avoid circular dependencies


class Connection {
	Node* _next;
	bool _active;
	
	
public:
	
	Connection(Node* next) : _next(next), _active(true) {}
	
	virtual ~Connection() {}
	
	
	int isActive() const { return _active; }
	
	Node* getNext() const { return _next; }
	
	
	void enable() { _active = true; }
	
	void disable() { _active = false; }
	
	
// 	friend std::ostream &operator<<(std::ostream &out, const Connection* connection) {
// 		out << connection->getNext()->getId() << "|" << connection->isActive();
// 		return out;
// 	}

};


#endif
