
#include <iostream> 
#include <vector>
#include <stack>
#include <list>


/************************************ structures ****************************************/

// solution container
struct Solution {
	int minID;
	int maxID;
	int artNodesCounter;
	
	Solution(): minID(-1), maxID(-1), artNodesCounter(0) {}
	~Solution() {}
};


class Node {
	int _id;
	std::list<Node*>* _adj;		// pointer because passable without copy
	int _adj_size; 				// in c++98 getting list size is lenear (solved with iterator)
	bool _visited;
		
	Node* _parent;
	int _discovery;
	int _low;

	
public:
	
	Node(int id) :	_id(id), _adj_size(0), _visited(false),
					_parent(NULL), _discovery(-1), _low(-1) {
						
		_adj = new std::list<Node*>();
	}
	
	virtual ~Node() { delete(_adj); }
	
	
/*getters*/
	int getId() const { return _id; }
	std::list<Node*>* getAdjacenciesList() const { return _adj; }
	int getAdjacenciesSize() const { return _adj_size; }
	bool visited() const { return _visited; }
		
	Node* getParent() const { return _parent; }
	int getDiscoveryTime() const { return _discovery; }
	int getLow() const { return _low; }
	
	
/*setters*/
	void setID(int id) { _id = id; }
	void visit() { _visited = true; }
	void resetVisit() { _visited = false; }
	
	void setParent(Node* parent) { _parent = parent; }
	void setDiscoveryTime(int dt) { _discovery = dt; }
	void setLow(int low) { _low = low; }
	
	
/*modifiers*/
	void connect(Node* adjacent) {
		_adj->push_front(adjacent);
		_adj_size++;
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

// no setters, once built graph cannot be changed

};



/********************************* search algorithm *************************************/

class Search {

public:
	static void updateSolution(Solution* result, int id) {
		
		result->artNodesCounter++;
		
		if(result->minID == -1 || result->maxID == -1)
			result->minID = result->maxID = id;
		
		else if(id < result->minID)
			result->minID = id;
		
		else if(id > result->maxID)
			result->maxID = id;
	}
	
	
	static Solution findArticulationNodes(Graph* g) {
		
		// maybe create heap to store articulation nodes, geting min and max = log(v)
		std::vector<bool>* artNodes = new std::vector<bool>(g->getNumberOfNodes());
		Node* node;
		Solution result;
			
		int time = 0;
		for(int t=0; t<g->getNumberOfNodes(); t++) {
			node = g->getNodeAt(t);
			if(!node->visited())
				Search::articulationPoints(g, node, artNodes, &time);	
		}

		for(int t=0; t<g->getNumberOfNodes(); t++) {
			if((*artNodes)[t] == true) {
				Search::updateSolution(&result, (t+1));
			}
		}
		
		delete(artNodes);		
		return result;
	}
	
// recursive
	static void articulationPoints(Graph* g, Node* parentNode, std::vector<bool>* artNodes, int* time) {
		
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
				
				// 1- parentNode is the root of dfs tree and has two or more successors
				if(parentNode->getParent() == NULL && successors >= 2) {
					(*artNodes)[parentNode->getId()-1] = true;
				}

				// 2- parentNode is not root,
				// and low value of one of its successors is higher than discovery value of parentNode
				if(parentNode->getParent() != NULL && successorNode->getLow() >= parentNode->getDiscoveryTime()) {
					(*artNodes)[parentNode->getId()-1] = true;
				}

			} else {
				if(successorNode != parentNode->getParent())
					if(successorNode->getDiscoveryTime() < parentNode->getLow())
						parentNode->setLow(successorNode->getDiscoveryTime());
			}
		}
	}
};



/*************************************** main *******************************************/

 int main () {
	int V = 0, E = 0;	
	Graph* g;
	Solution solution;
	
	std::cin >> V;
	std::cin >> E;
	
	g = new Graph(V, E);

	result = Search::findArticulationNodes(g);

	std::cout << result.artNodesCounter << std::endl;
	std::cout << result.minID << " "<< result.maxID << std::endl;

	delete(g);
	return 0;
}





