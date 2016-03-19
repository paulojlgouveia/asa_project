 

#include <iostream>
#include <vector>
#include <stack>
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
	
// 	Node(int id) : _id(id), _adj_size(0), _visited(false), _active(true) {
// 		_adj = new std::list<Node*>();
// 	}
	
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


class Graph {
	
	int _verticies;
	int _edges;
	
 	std::vector<Node*> _nodes;
	
public:
	
	Graph(int V, int E) : _verticies(V), _edges(E) {
		int one=0, two=0;
		int t;
		
		// vector of pointers, requires initialization
		for(t=1; t<=V; t++)
			_nodes.push_back(new Node(t));
		
		// read edges from stdin and connect nodes
		for(t=0; t<_edges; t++) {
			std::cin >> one;
			std::cin >> two;
							
			_nodes[one-1]->connect(_nodes[two-1]);	// vector starts at index 0
			_nodes[two-1]->connect(_nodes[one-1]);	// file starts at 1
		}	
	}
	
	virtual ~Graph() {
		for(int t=0; t<_verticies; t++)
			delete(_nodes[t]);
	}
	
	
/*getters*/

	int getNumberOfNodes() const { return _verticies; }
	int getNumberOfEdges() const { return _edges; }
	std::vector<Node*> getNodesArray() const { return _nodes; }
	
	Node* getNodeAt(int index) const { return _nodes[index]; }
	
	bool allVisited() const {
		for(int t=0; t<_verticies; t++)
			if(_nodes[t]->visited() == false)
				return false;

		return true;
	}
	
	
/*modifiers*/

	void resetVisited() {
		for(int t=0; t<_verticies; t++)
			_nodes[t]->resetVisit();
	}
	

/*operators*/
	
	friend std::ostream &operator<<(std::ostream &out, const Graph *graph) {
		out << std::endl;
		for(int t=0; t<graph->getNumberOfNodes(); t++) {
			out << graph->getNodeAt(t) << std::endl;
		}
		
		return out;
	}

};



class Search {
	
public:
	
	Search() {}
	~Search() {}
	
/*algorithms*/
	
	// iterative DFS
	static void dfs(Node *startNode) {
		std::stack<Node*> stack;
		std::list<Node*>* adj;
		
		std::list<Node*>::iterator adj_iter;
		Node* node;

		stack.push(startNode);
		
		while(stack.size() != 0){
			node = stack.top();
			node->visit();
			stack.pop();

			adj = node->getAdjacenciesList();

			for(adj_iter=adj->begin(); adj_iter!=adj->end(); adj_iter++) {
				if (!(*adj_iter)->visited())
						if(node->isActive())
							stack.push(*adj_iter);
			}
		}
	}

	
	// recursive
	static void articulationPoints(Graph* g, Node* parentNode, std::list<int>* artNodes, int* time) {
		
		int successors = 0;
		
		(*time)++;
		parentNode->visit();
		
		parentNode->setDiscoveryTime(*time);
		parentNode->setLow(*time);
		
		std::list<Node*>* adj = parentNode->getAdjacenciesList();
		std::list<Node*>::iterator adj_iter;
		Node* successorNode;
		
		for(adj_iter=adj->begin(); adj_iter!=adj->end(); adj_iter++) {
			successorNode = *adj_iter;	// convert iterator to pointer just to make code simpler
			
			if(!successorNode->visited()) {
				successors++;
				successorNode->setParent(parentNode);
				
				articulationPoints(g, successorNode, artNodes, time);
				
				//correct _low values
				if(successorNode->getLow() < parentNode->getLow())
					parentNode->setLow(successorNode->getLow());
				
				
				// parentNode is articulation node if:
				
				// 1- parentNode is the root of dfs tree and has two or more successors.
				if (parentNode->getParent() == NULL && successors >= 2)
					artNodes->push_back(parentNode->getId());

				// 2- parentNode is not root,
				// and low value of one of its successors is higher than discovery value of parentNode
				
				if (parentNode->getParent() != NULL && successorNode->getLow() > parentNode->getDiscoveryTime())
					artNodes->push_back(parentNode->getId());

			} else {
				if(successorNode != parentNode->getParent())
					if(successorNode->getDiscoveryTime() < parentNode->getLow())
						parentNode->setLow(successorNode->getDiscoveryTime());
			}
			
		}
	
	}
		
};


void update(int* min, int* max, int id) {
	if(*min == -1 || *max == -1)	*min = *max = id;
	else if(id < *min)				*min = id;
	else if(id > *max)				*max = id;
}


 int main () {
	 
	int V = 0, E = 0;
	int min = -1, max = -1, crucial = 0;
	
	Graph* g;
	Node* node;
	
	std::cin >> V;
	std::cin >> E;
	
	g = new Graph(V, E);

	
/****************************** with articulation nodes *****************************/

	// create heap to store articulation nodes, geting min and max = log(v)
	// just store ids, pointer to be passed as argument
	std::list<int>* artNodes = new std::list<int>();
	
	int time = 0;
	for(int t=0; t<V; t++) {
		node = g->getNodeAt(t);
		if(!node->visited())
			Search::articulationPoints(g, node, artNodes, &time);	
	}
	
	
	if(!artNodes->empty()) {
		// check for improvments with heap
// 		crucial = artNodes->size();
		
		int temp = -1, offset = 0;	// FIXME artNodes has duplicate values
		std::list<int>::iterator l_iter;
		for(l_iter=artNodes->begin(); l_iter!=artNodes->end(); l_iter++) {
			if(temp == (*l_iter)) offset++;
			else{
				temp = (*l_iter);
				update(&min, &max, (*l_iter));
			}
		}
		
		crucial = artNodes->size() - offset;

		

	}
		
	delete(artNodes);

/************************************************************************************/
	
	
	
/************************************ with N dfs ************************************/

// 	for(int t=0; t<V; t++) {		
// 		node = g->getNodeAt(t);
// 		node->disable();
// 						
// 		if (t>0)
// 			Search::dfs(g->getNodeAt(0));
// 		else
// 			Search::dfs(g->getNodeAt(1));
// 		
// 		if (!g->allVisited()) {
// 			update(&min, &max, node->getId());
// 			crucial++;
// 		}
// 		
// 		node->enable();
// 		g->resetVisited();
// 	}
	
/************************************************************************************/

	
	std::cout << crucial << std::endl;
	std::cout << min << " "<< max << std::endl;	

	delete(g);
	return 0;
}






















