#ifndef __NODE_H__
#define __NODE_H__

// #include <iostream> 

class Node {
	int _id;
	
public:
	
	Node(int id) : _id(id) {}
	
	virtual ~Node() {}
	
	int getId() const { return _id; }
	
	void setId(int id) { _id = id; }
	
	
	friend std::ostream &operator<<(std::ostream &o, const Node &nd) {
		o << "id: " << nd.getId();
		return o;
	}
	
};

#endif