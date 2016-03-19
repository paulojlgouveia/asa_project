/**********************************************/
/** Grupo: al095							 **/					
/** Paulo Jorge Louseiro Gouveia, 75657		 **/
/** Daniel Machado de Castro Figueira, 75694 **/
/**********************************************/

#include <iostream> 
#include <list>
#include <vector>
#include <stack>


/*************************** Structures ***************************/

// structure representing the solution of our problem
struct Solution {
	int minId;
	int maxId;
	int articulationNodes;
	
	Solution(): minId(-1), maxId(-1), articulationNodes(0) {}
	~Solution() {}
};


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


class Graph {
	int _vertices;					// number of vertices
	int _edges;						// number of edges
 	std::vector<Node*> _nodes;		// list of nodes
	
// constructors
public:
	Graph(int V, int E) : _vertices(V), _edges(E) {
		int node1=0, node2=0;
		
		for(int t = 1; t <= V; t++)
			_nodes.push_back(new Node(t));
		
		//read edges from stdin
		for(int t = 0; t < _edges; t++) {
			std::cin >> node1;
			std::cin >> node2;
							
			//connect nodes (index = id - 1)
			_nodes[node1-1]->connect(_nodes[node2 - 1]);
			_nodes[node2-1]->connect(_nodes[node1 - 1]);
		}	
	}

// destructors
public:
	virtual ~Graph() {
		for(int t = 0; t < _vertices; t++)
			delete(_nodes[t]);
	}
	
// getters
public:
	int getNumberOfNodes() const { return _vertices; }
	int getNumberOfEdges() const { return _edges; }
	std::vector<Node*> getNodesArray() const { return _nodes; }
	Node* getNodeAt(int index) const { return _nodes[index]; }

// methods
public:
	void resetVisited() {
		for(int t = 0; t < _vertices; t++)
			_nodes[t]->setVisited(false);
	}

	bool allVisited() const {
		for(int t = 0; t < _vertices; t++)
			if(_nodes[t]->visited() == false)
				return false;
		return true;
	}
};


/*************************** Algorithm Implementation ***************************/

class Search {
	
public:
	// updates solution values (struct solution)
	static void updateSolution(Solution* solution, int id) {
		solution->articulationNodes++;
		
		if(solution->minId == -1 || solution->maxId == -1)
			solution->minId = solution->maxId = id;
		else if(id < solution->minId)
			solution->minId = id;
		else if(id > solution->maxId)
			solution->maxId = id;
	}
	
	// finds articulation nodes and returns solution
	static Solution findArticulationNodes(Graph* graph) {
		int time = 0;
		Node* node;
		Solution solution;
		std::vector<bool>* artNodes = new std::vector<bool>(graph->getNumberOfNodes());
			
		for(int t = 0; t < graph->getNumberOfNodes(); t++) {
			node = graph->getNodeAt(t);
			if(!node->visited())
				Search::articulationPoints(graph, node, artNodes, &time);	
		}

		for(int t = 0; t < graph->getNumberOfNodes(); t++) {
			if((*artNodes)[t] == true) {
				Search::updateSolution(&solution, (t + 1));
			}
		}
		
		delete(artNodes);		
		return solution;
	}
	
	// find articulation nodes, algorithm main loop (recursive)
	static void articulationPoints(Graph* graph, Node* parentNode, std::vector<bool>* artNodes, int* time) {
		int successors = 0;
		Node* successorNode;
		std::list<Node*>::iterator adjIterator;
		std::list<Node*>* adjList = parentNode->getAdjacenciesList();
		
		(*time)++;
		parentNode->setVisited(true);
		parentNode->setDiscoveryTime(*time);
		parentNode->setLow(*time);
		
		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
			successorNode = *adjIterator;	// get iterator current node (code simplification)
			
			if(!successorNode->visited()) {
				successors++;
				successorNode->setParent(parentNode);
				
				articulationPoints(graph, successorNode, artNodes, time);
				
				// correct parent's _low value
				if(successorNode->getLow() < parentNode->getLow())
					parentNode->setLow(successorNode->getLow());
				
				// parentNode is articulation node if:
				
				// 1- parentNode is the root of dfs tree and has two or more successors
				if(parentNode->getParent() == NULL && successors >= 2) {
					(*artNodes)[parentNode->getId() - 1] = true;
				}

				// 2- parentNode is not root,
				// and low value of one of its successors is higher than discovery value of parentNode
				if(parentNode->getParent() != NULL && successorNode->getLow() >= parentNode->getDiscoveryTime()) {
					(*artNodes)[parentNode->getId() - 1] = true;
				}

			} else {
				if(successorNode != parentNode->getParent())
				// if node was already visited update low and discovery points
					if(successorNode->getDiscoveryTime() < parentNode->getLow())
						parentNode->setLow(successorNode->getDiscoveryTime());
			}
		}
	}
};


/*************************** Main Function ***************************/

 int main () {
	int V = 0, E = 0;	
	Graph* graph;
	Solution solution;
	
	std::cin >> V;
	std::cin >> E;
	
	graph = new Graph(V, E);
	solution = Search::findArticulationNodes(graph);

	std::cout << solution.articulationNodes << std::endl;
	std::cout << solution.minId << " "<< solution.maxId << std::endl;

	delete(graph);
	return 0;
}
