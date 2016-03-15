#ifndef __NODE_H__
#define __NODE_H__

#include <iostream> 
#include <vector>

class Node {
	int _id;
	bool _visited;
	std::vector<Node*> _activeNodes;
	std::vector<Node*> _inactiveNodes;
	
public:
	
	Node(int id) : _id(id), _visited(false) {}
	
	Node(Node* node) : _id(node->getId()), _visited(node->visited()) {
		for (Node* nd : node->getActiveNodes())
			addActiveNode(nd);
			
		for (Node* nd : node->getInactiveNodes())
			addInactiveNode(nd);
	}
	
	virtual ~Node() {}
	
/*getters*/

	int getId() const { return _id; }
	
	bool visited() const { return _visited; }
	
	std::vector<Node*> getActiveNodes() { return _activeNodes; }
	std::vector<Node*> getInactiveNodes() { return _inactiveNodes; }
	
	int getActiveNodesNumber() const { return _activeNodes.size(); }
	int getInactiveNodesNumber() const { return _inactiveNodes.size(); }
	
	Node* getActiveNodeAt(int index) const { return _activeNodes[index]; }
	Node* getInactiveNodeAt(int index) const { return _inactiveNodes[index]; }
	
/*setters*/
	
	void visit() { _visited = true; }
	void resetVisit() { _visited = false; }
	
/*modifiers*/

	void addActiveNode(Node* node) {
		_activeNodes.push_back(node);
	}
	
	void addInactiveNode(Node* node) {
		_inactiveNodes.push_back(node);
	}
	
	void deactivate(Node* node) {
		for (int i = 0; i < getActiveNodesNumber(); i++){
			if (node == getActiveNodeAt(i)) {
				_inactiveNodes.push_back(getActiveNodeAt(i));
				_activeNodes.erase(_activeNodes.begin() + i);
			}
		}
	}
	
	void reactivate(Node* node) {
		for (int i = 0; i < getInactiveNodesNumber(); i++){
			if (node == getInactiveNodeAt(i)) {
				_activeNodes.push_back(getInactiveNodeAt(i));
				_inactiveNodes.erase(_inactiveNodes.begin() + i);
			}
		}
	}
	
/*operators*/

	friend std::ostream &operator<<(std::ostream &out, const Node *node) {
		out << node->getId() << ":   ";
		
		for (Node* nd : node->getActiveNodes())
			out << nd->getId() << " ";
			
		for (Node* nd : node->getActiveNodes())
			out << "(" << nd->getId() << ") ";
		
		return out;
	}
};


#endif
