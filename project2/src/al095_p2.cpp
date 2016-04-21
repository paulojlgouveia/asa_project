
/*************************** src/Header.h ***************************/

/**********************************************/
/** Grupo: al095							 **/
/** Paulo Jorge Louseiro Gouveia, 75657		 **/
/** Daniel Machado de Castro Figueira, 75694 **/
/**********************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <list>



/*************************** src/Edge.h ***************************/


class Node;

class Edge {
	
	Node* _next;
	int _weight;


public:

// constructors
	Edge(Node* next, int weight);
// destructors
	virtual ~Edge();
	
	
// getters
	Node* getNext() const ;
	int getWeight() const ;
	

// setters
	void setNext(Node* next) ;
	void setWeight(int weight) ;

	
// operators
// 	inline friend std::ostream &operator<<(std::ostream &out, const Edge* edge) {
//   		out << edge->getNext()->getId() << "|" << edge->getWeight();
//   		return out;
// 	}

};


/*************************** src/Node.h ***************************/

class Node {
	int _id;						// node id
	int _adjSize; 					// size of adjacencies list (because of c++98)
	
	int _pathCost;
	int _h;

	bool _visited;
	Node* _parent;					// points to parent (used during search)
	std::list<Edge*>* _adjList;		// list of adjacent nodes

	
public:

// constructors
	Node(int id);

// destructors
	virtual ~Node();
	
	void clearAdjacencies();
	void deleteAdjacencies();
	
// getters
	int getId() const { return _id; }
	int getAdjacenciesSize() const { return _adjSize; }
	int getPathCost() const { return _pathCost; }
	int getH() const { return _h; }
	
	bool visited() const { return _visited; }
	Node* getParent() const { return _parent; }
	std::list<Edge*>* getAdjacenciesList() const { return _adjList; }
	
	
// setters
	void setId(int id) { _id = id; }
	void setPathCost(int cost) { _pathCost = cost; }
	void setH(int h) { _h = h; }
	
	void setVisited(bool visited) { _visited = visited; }
	void setParent(Node* parent) { _parent = parent; }
	
	
// methods
	void connect(Node* adjacent, int weight);
	void reweightEdges();
	int getReweightPathCost(Node *source);

	
// operators
	friend std::ostream &operator<<(std::ostream &out, const Node *node);

	
};


/*************************** src/Edge.cpp ***************************/

// constructors
Edge::Edge(Node* next, int weight) : _next(next), _weight(weight) { }

// destructors
Edge::~Edge() { }
	
	
// getters
Node* Edge::getNext() const { return _next; }
int Edge::getWeight() const { return _weight; }
	

// setters
void Edge::setNext(Node* next) { _next = next; }
void Edge::setWeight(int weight) { _weight = weight; }


/*************************** src/Node.cpp ***************************/

// constructors
Node::Node(int id) : _id(id), _adjSize(0), _pathCost(99999), _visited(false), _parent(NULL) {
	_adjList = new std::list<Edge*>();
}

// destructors
Node::~Node() {
	deleteAdjacencies();
}


void Node::deleteAdjacencies() {
	std::list<Edge*>::iterator adjIterator;
	std::list<Edge*>* adjList = getAdjacenciesList();


	for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
		delete(*adjIterator);
	}

	delete(_adjList);
}

void Node::clearAdjacencies() {
	deleteAdjacencies();
	_adjList = new std::list<Edge*>();
}


// methods
void Node::connect(Node* adjacent, int weight) {
	Edge* edge = new Edge(adjacent, weight);
	
	_adjList->push_front(edge);
	_adjSize++;
}


void Node::reweightEdges() {
	std::list<Edge*>::iterator adjIterator;
	std::list<Edge*>* adjList = getAdjacenciesList();
	Edge *edge;

	for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
		edge = (*adjIterator);
		
		edge->setWeight(edge->getWeight() + getH() - edge->getNext()->getH());
	}
}

int Node::getReweightPathCost(Node *source) {
	if(getPathCost() != 99999)
		return getPathCost() - source->getH() + getH();
	return getPathCost();
}




// operators
std::ostream &operator<<(std::ostream &out, const Node *node) {
	
	std::list<Edge*>::iterator adjIterator;
	std::list<Edge*>* adjList = node->getAdjacenciesList();
	
  	out << node->getId() << " (" << node->getPathCost() << "|" << node->getH() << "):   ";
	
	for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
 		if(adjIterator != adjList->begin())
 			out << " ,  ";
 		out << (*adjIterator)->getNext()->getId();
 		out << "|" << (*adjIterator)->getWeight();
	}
	
 	return out;
 }


/*************************** src/Graph.h ***************************/

class Graph {
	int _vertices;					// number of vertices
	int _edges;						// number of edges
 	std::vector<Node*> *_nodes;		// list of nodes
	
	
public:
	
// constructors
	Graph(int V, int E) : _vertices(V+1), _edges(E) {
		int node1=0, node2=0, weight=0;
		
		_nodes = new std::vector<Node*>();
// 		_nodes->reserve(_vertices);
		
		for(int t = 0; t < _vertices; t++)
			_nodes->push_back(new Node(t));
		
		//read edges from stdin
		for(int t = 0; t < _edges; t++) {
			std::cin >> node1;
			std::cin >> node2;
			std::cin >> weight,
			
			//connect nodes (index = id - 1)
// 			(*_nodes)[node1-1]->connect((*_nodes)[node2 - 1], weight);
			_nodes->at(node1)->connect(_nodes->at(node2), weight);
		}
	}

	
// destructors
	~Graph() {
		for(int t = 0; t < _vertices; t++) {
			delete(_nodes->at(t));
		}
		
		delete(_nodes);
	}
	
	
// getters
	int getNumberOfNodes() const { return _vertices; }
	int getNumberOfEdges() const { return _edges; }
	std::vector<Node*>* getNodesArray() const { return _nodes; }
	Node* getNodeAt(int index) const { return _nodes->at(index); }

	
// methods
	void resetVisited() {
		for(int t = 0; t <= _vertices; t++)
			(*_nodes)[t]->setVisited(false);
	}

	bool allVisited() const {
		for(int t = 0; t <= _vertices; t++)
			if((*_nodes)[t]->visited() == false)
				return false;
		return true;
	}
	
	
		
// operators
	friend std::ostream &operator<<(std::ostream &out, const Graph *graph) {
		
  		out << std::endl;
  		for(int t=0; t<graph->getNumberOfNodes(); t++) {
 			out << graph->getNodeAt(t) << std::endl;
 		}
 		
 		return out;
 	}
	
	

};


/*************************** src/BHeap.h ***************************/


// template <class T>
class BHeap {

private:
	std::vector<Node*> _heap;


	static bool compareFunction(const Node *a, const Node *b) {
		return (a->getPathCost() >= b->getPathCost());
	}
	
	
public:
	
	BHeap() { }
	
	BHeap(std::vector<Node*> *vector) {
		int size = vector->size();
		
// 		_heap = new std::vector<Node*>();							// O(1)
		
// 		_heap.reserve(size);										// O(1)
// 		for(int t=0; t<size; t++) {									// O(N)
// 			_heap[t] = vector->at(t);
// 		}
		
		for(int t=0; t<size; t++) {									// O(N)
			_heap.push_back(vector->at(t));
		}
				
// 		std::make_heap(_heap.begin(), _heap.end(), compareFunction);		// O(3*N)
		std::sort(_heap.begin(), _heap.end(), compareFunction);				// O(N*log(N))
	}
	
	virtual ~BHeap() {
// 		delete(_heap);
	}
	
	
	void sort() {
// 		std::make_heap(v.begin(),v.end(), compareFunction);		// O(3*N)
		std::sort(_heap.begin(), _heap.end(), compareFunction);		// O(N*log(N))
	}
	
	
	Node* getMaximum() const { return _heap[0]; }
	Node* getMinimum() const { return _heap[_heap.size()-1]; }
	
	Node* getNodeAt(int index) const { return _heap.at(index); }
	int size() const { return _heap.size(); }
	
	
	void push_back(Node *node) {
		_heap.push_back(node);
		std::sort(_heap.begin(), _heap.end(), compareFunction);		// O(N*log(N))
	}
	
	void pop_back() {
		_heap.pop_back();
		std::sort(_heap.begin(), _heap.end(), compareFunction);		// O(N*log(N))
	}
	
	
// operators
	friend std::ostream &operator<<(std::ostream &out, const BHeap *heap) {
		
  		for(int t=0; t<heap->size(); t++) {
 			out << heap->getNodeAt(t)->getId() << " ";
 		}
 		
 		out << std::endl;
 		
 		return out;
 	}
};


/*************************** src/Dijkstra.h ***************************/

class Dijkstra {
	
public:
// 	static void updateSolution(Solution* solution) {}

	
// 	Initialize-Single-Source(G, s)
// 		for each v ∈ V [G]
// 			do	d[v ] ← ∞
// 				π[v ] ← NIL
// 		d [s] ← 0

	static void initializeSingleSource(Graph* graph, Node* s) {
		for (int t = 0; t < graph->getNumberOfNodes(); t++) {
			graph->getNodeAt(t)->setPathCost(99999);
			graph->getNodeAt(t)->setParent(NULL);
		}
		s->setPathCost(0);
	}


// 	Relax(u , v , w )
// 		if d [v ] > d [u] + w (u, v )
// 			then	d [v ] ← d [u ] + w (u , v )
// 					π[v ] ← u

	static void relax(Node *u, Node *v, int weight){
		
		if(v->getPathCost() > (u->getPathCost() + weight)) {
			v->setPathCost(u->getPathCost() + weight);
			v->setParent(u);
		}
	}


// 	Dijkstra(G, w , s)
// 		Initialize-Single-Source(G , s)
// 		S ← 0 /
// 		Q ← V [G]	✄ Fila de Prioridade
//
// 		while Q = 0 /
// 			do u ← Extract-Min(Q)
// 				S ← S ∪ {u }
// 				for each v ∈ Adj [u]
// 					do Relax(u, v , w )		✄ Actualização de Q

	static void run(Graph* graph, int index) {
		run(graph, graph->getNodeAt(index));
	}

	static void run(Graph* graph, Node* s) {
		
		std::cout << "s: " << s->getId()<< std::endl;

		Node *node1, *node2;
		int weight;
		
// 		std::list<Node*>* S = new std::list<Node*>();
		
// 		BHeap* Q = new BHeap(graph->getNodesArray());
		BHeap* Q = new BHeap();
		Q->push_back(s);

		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList;
		
		initializeSingleSource(graph, s);

		while(Q->size() > 0) {

// 			std::cout << "Q: " << Q;
 			node1 = Q->getMinimum();
			Q->pop_back();
// 			std::cout << "extracted from Q: " << node1->getId() << std::endl<< std::endl;

// 			S->push_front(node1);
			
			adjList = node1->getAdjacenciesList();
			for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
				node2 = (*adjIterator)->getNext();
				weight = (*adjIterator)->getWeight();
				
				if(node2->getParent() == NULL)
					Q->push_back(node2);
				
				relax(node1, node2, weight);
					
			}
		}
		
// 		delete(S);
		delete(Q);
	}
	
};


/*************************** src/BellmanFord.h ***************************/

class BellmanFord {
	
	static void initializeSingleSource(Graph* graph, Node* s) {
		for (int t = 0; t < graph->getNumberOfNodes(); t++)
			graph->getNodeAt(t)->setPathCost(99999);
		s->setPathCost(0);
	}
	

	static void relax(Node *u, Node *v, int weight){
		if(v->getPathCost() > (u->getPathCost() + weight)) {
			v->setPathCost(u->getPathCost() + weight);
			v->setParent(u);
		}
	}
	
public:
	
	// runs bellman-ford algorithm starting at node with given id
	static void run(Graph *graph, int id){
		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList;
		Node *u;
		Node *v;
		int weight;
		
		initializeSingleSource(graph, graph->getNodeAt(id)); //by default source index is zero
		
		// do V-1 iterations
		for (int t = 0; t < graph->getNumberOfNodes(); t++){
		
			// loop through all edges
			for (int i = 0; i < graph->getNumberOfNodes(); i++){
				u = graph->getNodeAt(i);
				adjList = u->getAdjacenciesList();
				
				for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
					v = (*adjIterator)->getNext();
					weight = (*adjIterator)->getWeight();
					relax(u, v, weight);
				}
			}
			
		}
		
		// doesn't check for negative loops since there's no need
	}
};


/*************************** src/Johnson.h ***************************/

class Johnson {
	
	static void connectSource(Graph *graph) {
		for(int t=1; t<graph->getNumberOfNodes(); t++)
			graph->getNodeAt(0)->connect(graph->getNodeAt(t), 0);
	}
	
	static void disconnectSource(Graph *graph) {
// 		std::list<Edge*>::iterator adjIterator;
// 		std::list<Edge*>* adjList = (graph->getNodeAt(0))->getAdjacenciesList();
//
// 		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
// 			delete(*adjIterator);
// 		}
	
		graph->getNodeAt(0)->clearAdjacencies();
	}
	
	
	static void copyCostToH(Graph *graph) {
		Node *node;
		
		for(int t=0; t<graph->getNumberOfNodes(); t++) {
			node = graph->getNodeAt(t);
			node->setH(node->getPathCost());
		}
	}
	
	
	
public:

	static int **run(Graph *graph, std::vector<int> *subsidiaries){
		
		int F = subsidiaries->size();
		int **deslocationCost = new int*[F];
		for(int i=0; i<F; i++) {
			deslocationCost[i] = new int[graph->getNumberOfNodes()];
		}
		
		connectSource(graph);
		BellmanFord::run(graph, 0);
		disconnectSource(graph);
// 		std::cout << graph << std::endl;
		
		copyCostToH(graph);
		for(int t = 1; t < graph->getNumberOfNodes(); t++){
			graph->getNodeAt(t)->reweightEdges();
		}

// 		std::cout << "before dijkstra " << graph << std::endl;	

		
		for(int u = 0; u < F; u++) {
			Dijkstra::run(graph, subsidiaries->at(u));
// 			std::cout << "after dijkstra " << graph << std::endl;

			for(int v = 1; v < graph->getNumberOfNodes(); v++){
				deslocationCost[u][v] = graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(u));
			}
		}
		
		return deslocationCost;
	}

	
};


/*************************** src/main.cpp ***************************/


void printSolution(int **deslocationCost, std::vector<int>* subsidiaries, int V) {
	
	int location = 0, total_loss = 0, loss = 99999, new_loss;
	int v = 1;
	unsigned int u = 0;
	bool possible = true;
	
	for(v = 1; v < V; v++) {
		new_loss = 0;
		for(u = 0; u < subsidiaries->size(); u++) {
			new_loss = new_loss + deslocationCost[u][v];
		}
		
		if(new_loss < loss) {
			subsidiaries->at(u-1) = deslocationCost[u-1][v];
			location = v;
			loss = new_loss;
		}

	}
	
	for(unsigned int t=0; t<subsidiaries->size(); t++) {
		loss = deslocationCost[t][location];
		
		if(loss == 99999) {
			possible = false;
			break;
		}
		
		total_loss += loss;
	}
	
	if(possible) {
		std::cout << location << " " << total_loss << std::endl;
		for(unsigned int t=0; t<subsidiaries->size(); t++) 
			std::cout << deslocationCost[t][location] << " ";
	} else {
		std::cout << "N";
	}
	
	std::cout << std::endl;
}

int main () {
	int V = 0, F=0, E = 0;
	int temp = -1;
	Graph* graph;
	std::vector<int>* subsidiaries = new std::vector<int>();
	
	int **deslocationCost;
	
	std::cin >> V;
	std::cin >> F;
	std::cin >> E;
	

	for(int t=0; t<F; t++) {
		std::cin >> temp;
		subsidiaries->push_back(temp);
	}

	graph = new Graph(V, E);
// 	std::cout << graph << std::endl;
	
// 	std::cout << "Dijkstra" << std::endl;
// 	Dijkstra::run(graph, 1);
// 	std::cout << graph << std::endl;

// 	std::cout << "BellmanFord" << std::endl;
// 	BellmanFord::run(graph, 1);
// 	std::cout << graph << std::endl;

// 	std::cout << "Johnson" << std::endl;
	deslocationCost = Johnson::run(graph, subsidiaries);
// 	std::cout << graph << std::endl;
// 	
// 	std::cout << "\t1 \t2 \t3 \t4 \t5 \t6" << std::endl;
// 	std::cout << "  ----------------------------------------------------" << std::endl;
// 	for(unsigned int u = 0; u < subsidiaries->size(); u++) {
// 		std::cout << u << "| \t";
// 		for(int v = 1; v < graph->getNumberOfNodes(); v++){
// 			std::cout << deslocationCost[u][v] << " \t";
// 		}
// 		std::cout << std::endl;
// 	}
// 	std::cout << std::endl;
	
	printSolution(deslocationCost, subsidiaries, graph->getNumberOfNodes());
	
	// free memory
	for(int i=0; i<F; i++)
		delete[] deslocationCost[i];
	delete[] deslocationCost;
	
	delete(subsidiaries);

	delete(graph);
	return 0;
	
}

