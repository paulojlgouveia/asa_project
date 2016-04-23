
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
	int _heapIndex;
	
	
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
	int getHeapIndex() const { return _heapIndex; }
	
// setters
	void setId(int id) { _id = id; }
	void setPathCost(int cost) { _pathCost = cost; }
	void setH(int h) { _h = h; }
	
	void setVisited(bool visited) { _visited = visited; }
	void setParent(Node* parent) { _parent = parent; }
	void setHeapIndex(int index) { _heapIndex = index; }

	
// methods
	void connect(Node* adjacent, int weight);
	void reweightEdges();
	int getReweightPathCost(Node *source);

	
// operators
	friend std::ostream &operator<<(std::ostream &out, const Node *node);

// 	friend bool operator<(const Node& first, const Node& second) {
// 		return ( first.getPathCost() < second.getPathCost() );
// 	}
// 	
// 	friend bool operator<(const Node *first, const Node *second) {
// 		return ( first->getPathCost() < second->getPathCost() );
// 	}
	
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
Node::Node(int id) : _id(id), _adjSize(0), _pathCost(99999), _visited(false), _parent(NULL), _heapIndex(-1) {
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
	if(getPathCost() < 99999)
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
// 		int removed = 0;
		_nodes = new std::vector<Node*>();
// 		_nodes->reserve(_vertices);
		
		for(int t = 0; t < _vertices; t++)
			_nodes->push_back(new Node(t));
		
		//read edges from stdin
		for(int t = 0; t < _edges; t++) {
			std::cin >> node1;
			std::cin >> node2;
			std::cin >> weight;
			
			//connect nodes (index = id - 1)
// 			(*_nodes)[node1-1]->connect((*_nodes)[node2 - 1], weight);
			
// 			if(node1 == node2)
// 				removed++;
// 			else
				_nodes->at(node1)->connect(_nodes->at(node2), weight);
// 				_nodes->at(node2)->connect(_nodes->at(node1), weight);
		}
		
// 		_edges -= removed;
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



class BMinHeap {
	Node **_data;
	int _heapSize;
	int _arraySize;

	int getLeftChildIndex(int nodeIndex) {
		return 2 * nodeIndex + 1;
	}

	int getRightChildIndex(int nodeIndex) {
		return 2 * nodeIndex + 2;
	}

	int getParentIndex(int nodeIndex) {
		return (nodeIndex - 1) / 2;
	}
	
	void swap(int a, int b) {
		Node *temp = _data[a];
		_data[a] = _data[b];
		_data[b] = temp;
		
		_data[a]->setHeapIndex(a);
		_data[b]->setHeapIndex(b);
		
	}
	
public:
	BMinHeap(int size) {
		_data = new Node*[size];
		_heapSize = 0;
		_arraySize = size;
	}
	
	~BMinHeap() {
		delete(_data);
// 		delete[] _data;
	}
	
	bool isEmpty() { return (_heapSize == 0); }
	int size() const { return _heapSize; }
	int capacity() const { return _arraySize; }
	Node* at(int index) const { return _data[index]; }
	
	
	void fixUp(int nodeIndex) {
		int parentIndex;
		
		if (nodeIndex != 0) {
			parentIndex = getParentIndex(nodeIndex);
			if (_data[parentIndex]->getPathCost() > _data[nodeIndex]->getPathCost()) {
				swap(parentIndex, nodeIndex);
				fixUp(parentIndex);
			}
		}
	}
	
	void fixDown(int nodeIndex) {		
		int leftChildIndex, rightChildIndex, minIndex;
		int leftChildWeight, rightChildWeight, minWeight;
		
		if(nodeIndex < _heapSize) {			
			minIndex = nodeIndex;
			minWeight = _data[nodeIndex]->getPathCost();
			
			leftChildIndex = getLeftChildIndex(nodeIndex);
			if(leftChildIndex < _heapSize) {
				leftChildWeight = _data[leftChildIndex]->getPathCost();
				if(leftChildWeight < minWeight) {
					minIndex = leftChildIndex;
					minWeight = _data[minIndex]->getPathCost();
				}
			}
			
			rightChildIndex = getRightChildIndex(nodeIndex);
			if(rightChildIndex < _heapSize ) {
				rightChildWeight = _data[rightChildIndex]->getPathCost();
				if(rightChildWeight < minWeight) {
					minIndex = rightChildIndex;
				}
			}
			
			if(minIndex != nodeIndex) {
				swap(nodeIndex, minIndex);
				fixDown(minIndex);
			}
		}
	}
	
	void insert(Node* node) {
		if (_heapSize == _arraySize) {
			std::cout  << std::endl << "Heap's underlying storage is overflow" << std::endl;
			throw std::string("Heap's underlying storage is overflow");
		} else {
			_heapSize++;
			_data[_heapSize - 1] = node;
			node->setHeapIndex(_heapSize-1);
			fixUp(_heapSize - 1);
		}
	}
	
	Node* extractMin() {
		if (_heapSize > 0) {
			Node *min = _data[0];
// 			_data[0] = _data[_heapSize -1];
// 			_data[0]->setHeapIndex(0);
			swap(0, _heapSize-1);
			
			_heapSize--;
			fixDown(0);
			return min;
		} else {
			std::cout  << std::endl << "empty" << std::endl;
			throw std::string("empty");
		}
	}
	
	void decreaseKey(int index) {
		while(index > 0 && _data[getParentIndex(index)]->getPathCost() > _data[index]->getPathCost()) {
			swap(getParentIndex(index), index);
			index = getParentIndex(index);
		}
	}


	friend std::ostream &operator<<(std::ostream &out, const BMinHeap *heap) {
		out << std::endl;
		out << "heap size: " << heap->size() << std::endl;
		out << "max heap size: " << heap->capacity() << std::endl;
		
  		for(int t=0; t<heap->size(); t++) {
// 			out << heap->at(t)->getPathCost() << " ";
			out << heap->at(t)->getHeapIndex() << ",";
			out << heap->at(t)->getId() << "  ";
		}
 		
 		return out;
 	}
 	
 	
};







// class BMinHeap {
// 	Node **_data;
// 	int _heapSize;
// 	int _arraySize;
// 
// 	int getLeftChildIndex(int nodeIndex) {
// 		return 2 * nodeIndex + 1;
// 	}
// 
// 	int getRightChildIndex(int nodeIndex) {
// 		return 2 * nodeIndex + 2;
// 	}
// 
// 	int getParentIndex(int nodeIndex) {
// 		return (nodeIndex - 1) / 2;
// 	}
// 	
// public:
// 	void fixUp(int nodeIndex) {
// 		Node *temp;
// 		int parentIndex;
// 		
// 		if (nodeIndex != 0) {
// 			parentIndex = getParentIndex(nodeIndex);
// 			if (_data[parentIndex]->getPathCost() > _data[nodeIndex]->getPathCost()) {
// 				temp = _data[parentIndex];
// 				_data[parentIndex] = _data[nodeIndex];
// 				_data[nodeIndex] = temp;
// 					_data[parentIndex]->setHeapIndex(nodeIndex);
// 					_data[nodeIndex]->setHeapIndex(parentIndex);
// 				fixUp(parentIndex);
// 			}
// 		}
// 	}
// 	
// 	void fixDown(int nodeIndex) {
// 		Node *temp;
// 		int leftChildIndex, rightChildIndex, minIndex;
// 		
// 		leftChildIndex = getLeftChildIndex(nodeIndex);
// 		rightChildIndex = getRightChildIndex(nodeIndex);
// 		
// 		if(rightChildIndex >= _heapSize) {
// 			if(leftChildIndex >= _heapSize)
// 				return;
// 			else
// 				minIndex = leftChildIndex;
// 		} else {
// 			if(_data[leftChildIndex]->getPathCost() <= _data[rightChildIndex]->getPathCost())
// 				minIndex = leftChildIndex;
// 			else
// 				minIndex = rightChildIndex;
// 		}
// 		
// 		if(_data[nodeIndex]->getPathCost() > _data[minIndex]->getPathCost()) {
// 			temp = _data[minIndex];
// 			_data[minIndex] = _data[nodeIndex];
// 			_data[nodeIndex] = temp;
// 				_data[minIndex]->setHeapIndex(nodeIndex);
// 				_data[nodeIndex]->setHeapIndex(minIndex);
// 			fixDown(minIndex);
// 		}
// 	}
// 	
// 	void minHeapify(int nodeIndex) {
// 		Node *temp;
// 		int leftChildIndex, rightChildIndex, minIndex;
// 		int leftChildWeight, rightChildWeight, minWeight;
// 		
// 		leftChildIndex = getLeftChildIndex(nodeIndex);
// 		rightChildIndex = getRightChildIndex(nodeIndex);
// 		minIndex = nodeIndex;
// 		
// 		leftChildWeight = _data[leftChildIndex]->getPathCost();
// 		rightChildWeight = _data[rightChildIndex]->getPathCost();
// 		minWeight = _data[nodeIndex]->getPathCost();
// 		
// 		if(leftChildIndex < _heapSize && leftChildWeight < minWeight) {
// 			minIndex = leftChildIndex;
// 			minWeight = _data[minIndex]->getPathCost();
// 		}
// 		
// 		
// 		if(rightChildIndex < _heapSize && rightChildWeight < minWeight) {
// 			minIndex = rightChildIndex;
// 		}
// 		
// 		if(minIndex != nodeIndex) {
// 			temp = _data[minIndex];
// 			_data[minIndex] = _data[nodeIndex];
// 			_data[nodeIndex] = temp;
// 			minHeapify(minIndex);
// 		}
// 	}
// 	
// 
// 
// 	BMinHeap(int size) {
// 		_data = new Node*[size];
// 		_heapSize = 0;
// 		_arraySize = size;
// 	}
// 	
// 	~BMinHeap() {
// 		delete[] _data;
// 	}
// 	
// 	bool isEmpty() { return (_heapSize == 0); }
// 	int size() const { return _heapSize; }
// 	int capacity() const { return _arraySize; }
// 	Node* at(int index) const { return _data[index]; }
// 	
// 	Node* getMinimum() {
// 		if (isEmpty()) {
// 			std::cout  << std::endl << "Heap is empty" << std::endl;
// 			throw std::string("Heap is empty");
// 		} else {
// 			return _data[0];
// 		}
// 	}
// 
// 	void removeMinimum() {
// 		if(isEmpty()) {
// 			std::cout  << std::endl << "Heap is empty" << std::endl;
// 			throw std::string("Heap is empty");
// 		} else {
// 			_data[0] = _data[_heapSize - 1];
// // 			_data[_heapSize-1] = NULL;
// 			_heapSize--;
// 			if (_heapSize > 0)
// 				fixDown(0);
// 		}
// 	}
// 	
// 	
// 	void buildHeap() {
// 		for(int t=(_heapSize-1)/2; t>0; t--)
// 			minHeapify(t);
// 	}
// 	
// 	
// 	void modify(int index) {
// 		Node *temp;
// 		while(index > 0 && _data[getParentIndex(index)]->getPathCost() > _data[index]->getPathCost()) {
// 			temp = _data[getParentIndex(index)];
// 			_data[getParentIndex(index)] = _data[index];
// 			_data[index] = temp;
// 				_data[getParentIndex(index)]->setHeapIndex(index);
// 				_data[index]->setHeapIndex(getParentIndex(index));
// 			
// 			index = getParentIndex(index);
// 		}
// 	}
// 	
// 	
// 	Node* extractMin() {
// 		Node *min = _data[0];
// 		_data[0] = _data[_heapSize -1];
// 		_heapSize--;
// 		minHeapify(0);
// 		return min;
// 	}
// 	
// 
// 	
// 	void insert(Node* node) {
// 		if (_heapSize == _arraySize) {
// 			std::cout  << std::endl << "Heap's underlying storage is overflow" << std::endl;
// 			throw std::string("Heap's underlying storage is overflow");
// 		} else {
// 			_heapSize++;
// 			_data[_heapSize - 1] = node;
// 			fixUp(_heapSize - 1);
// 		}
// 	}
// 	
// 	
// 	friend std::ostream &operator<<(std::ostream &out, const BMinHeap *heap) {
// 		out << std::endl;
// 		out << "heap size: " << heap->size() << std::endl;
// 		out << "max heap size: " << heap->capacity() << std::endl;
// 		
//   		for(int t=0; t<heap->size(); t++)
//  			out << heap->at(t)->getPathCost() << " ";
//  		
//  		return out;
//  	}
// 	
// 	friend std::ostream &operator<<(std::ostream &out, const BMinHeap &heap) {
// 		out << std::endl;
// 		out << "heap size: " << heap.size() << std::endl;
// 		out << "max heap size: " << heap.capacity() << std::endl;
// 		
//   		for(int t=0; t<heap.size(); t++)
// 			out << heap.at(t)->getPathCost() << " ";
//  		
//  		return out;
//  	}
// 
// };








/*************************** src/Solution.h ***************************/



// structure representing the solution of the problem
struct Solution {
	int location;
	int totalLoss;
	int *deslocationCost;
	int subsidiariesCount;
	
	Solution(int size): location(-1), totalLoss(99999), subsidiariesCount(size) {
		deslocationCost = new int[size];
		for(int i=0; i<size; i++)
			deslocationCost[i] = 99999;
	}
	
	~Solution() {
		delete[] deslocationCost;
	}
	
	
	void print() {
		for(int t=0; t<subsidiariesCount; t++)
				if(deslocationCost[t] >= 99999)
					totalLoss = 99999;
		
		
		if(totalLoss < 99999) {
			std::cout << location << " " << totalLoss << std::endl;
			for(int t=0; t<subsidiariesCount; t++)
				std::cout << deslocationCost[t] << " ";
		} else {
			std::cout << "N";
		}
		
		std::cout << std::endl;
	}
	
};



/*************************** src/Dijkstra.h ***************************/

class Dijkstra {
	
public:
// 	static void updateSolution(Solution* solution) {}

	static void initializeSingleSource(Graph* graph, Node* s) {
		for (int t = 0; t < graph->getNumberOfNodes(); t++) {
			graph->getNodeAt(t)->setPathCost(99999);
			graph->getNodeAt(t)->setParent(NULL);
			graph->getNodeAt(t)->setVisited(false);
		}
		s->setPathCost(0);
	}

	static void relax(Node *u, Node *v, int weight, BMinHeap *Q){
		
		if(v->getPathCost() > (u->getPathCost() + weight)) {
			v->setPathCost(u->getPathCost() + weight);
			v->setParent(u);
			Q->decreaseKey(v->getHeapIndex());
		}
			v->setVisited(true);
	}


	static void run(Graph* graph, int index, BMinHeap* Q) {
		run(graph, graph->getNodeAt(index), Q);
	}


	static void run(Graph* graph, Node* s, BMinHeap* Q) {
		Node *node1, *node2;
		int weight;
		
		initializeSingleSource(graph, s);
		
// 		BMinHeap* Q = new BMinHeap(graph->getNumberOfNodes());
// 		for(int t=1; t<graph->getNumberOfNodes();t++)
// 			Q->insert(graph->getNodeAt(t));

		std::list<Edge*>::iterator adjIterator;
		std::list<Edge*>* adjList;
		
		while(Q->size() > 0) {			
// 			std::cout  << std::endl << "Q: " << Q;
			node1 = Q->extractMin();
// 			std::cout << std::endl << "removed " << node1->getId() << std::endl;
			
			adjList = node1->getAdjacenciesList();
			for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
				node2 = (*adjIterator)->getNext();
				weight = (*adjIterator)->getWeight();
				
				relax(node1, node2, weight, Q);
			}
		}
		
// 		delete(Q);
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
		
		// look for negative loops
		for (int t = 0; t < graph->getNumberOfNodes(); t++){
			// loop through all edges
			for (int i = 0; i < graph->getNumberOfNodes(); i++){
				u = graph->getNodeAt(i);
				adjList = u->getAdjacenciesList();
				
				for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
					v = (*adjIterator)->getNext();
					weight = (*adjIterator)->getWeight();
					if(v->getPathCost() > weight + u->getPathCost())
						throw std::string("NEGATIVE LOOP !!!");
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

		graph->getNodeAt(0)->clearAdjacencies();
	}
	
	
	static void copyCostToH(Graph *graph) {
		Node *node;
		
		for(int t=0; t<graph->getNumberOfNodes(); t++) {
			node = graph->getNodeAt(t);
			node->setH(node->getPathCost());
		}
	}
	
	static int getBestLocation(int *deslocationCost, int V) {
		int min_location = 99999;
		int min_cost = 99999;
		
		for(int v = 0; v < V; v++){
			if(deslocationCost[v] < min_cost){
				min_cost = deslocationCost[v];
				min_location = v;
			}
		}
		return min_location;
	}
	
	
public:
// 	// corrigi frees e descomentei esta, comentei a outra para submeter
// 	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){
// 
// 		int F = subsidiaries->size();
// 		int tempCost;
// 		
// 		int **deslocationCost = new int*[F];
// 		int *temp, *aux = new int[F];
// 		
// 		for(int i=0; i<F; i++) {
// 			deslocationCost[i] = new int[graph->getNumberOfNodes()];
// 		}
// 
// 		connectSource(graph);
// 		BellmanFord::run(graph, 0);
// 		disconnectSource(graph);
// // 		std::cout << graph << std::endl;
// 
// 		copyCostToH(graph);
// 		for(int t = 1; t < graph->getNumberOfNodes(); t++){
// 			graph->getNodeAt(t)->reweightEdges();
// 		}
// 
// 		// std::cout << "before dijkstra " << graph << std::endl;
// 
// 
// 		for(int u = 0; u < F; u++) {
// 			Dijkstra::run(graph, subsidiaries->at(u));
// // 			std::cout << "after dijkstra " << graph << std::endl;
// 
// 			for(int v = 1; v < graph->getNumberOfNodes(); v++){
// 				deslocationCost[u][v] = graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
// 			}
// 		}
// 		
// 		for(int v = 1; v < graph->getNumberOfNodes(); v++){
// 			tempCost = 0;
// 			
// 			for(int u = 0; u < F; u++) {
// 				tempCost += deslocationCost[u][v];
// 			}
// 			
// 			if(tempCost < answer->totalLoss) {
// 				answer->totalLoss = tempCost;
// 				answer->location = v;
// 				
// 				for(int u = 0; u < F; u++)
// 					aux[u] = deslocationCost[u][v];
// 				
// 				temp = aux;
// 				aux = answer->deslocationCost;
// 				answer->deslocationCost = temp;
// 			}
// 		}
// 		
// 		for(int t=0; t<F; t++)
// 			delete[] deslocationCost[t];
// 		delete[] deslocationCost;
// 		
// 		delete[] aux;
// 	}
	
 	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){
		std::list<int>::iterator listIterator;
 
		int V = graph->getNumberOfNodes();
 		int F = subsidiaries->size();
 		int *deslocationCost = new int[V];
 		int bestLocation;
		
		BMinHeap* Q = new BMinHeap(graph->getNumberOfNodes());
// 		for(int t=1; t<graph->getNumberOfNodes();t++)
// 			Q->insert(graph->getNodeAt(t));
 
 		connectSource(graph);
 		BellmanFord::run(graph, 0);
 		disconnectSource(graph);
  
 		copyCostToH(graph);
 		for(int t = 1; t < V; t++){
 			graph->getNodeAt(t)->reweightEdges();
 			deslocationCost[t] = 0;
 		}

 		for(int u = 0; u < F; u++) {
			for(int t=1; t<graph->getNumberOfNodes();t++)
				Q->insert(graph->getNodeAt(t));
			
 			Dijkstra::run(graph, subsidiaries->at(u), Q);
 
 			for(int v = 0; v < V; v++){
				if(deslocationCost[v] != 99999)
					deslocationCost[v] += graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
				else
					deslocationCost[v] = 99999;
 			}
 		}
 		
 		bestLocation = getBestLocation(deslocationCost, V);
 	
 		//Check if best location is valid *FIXME*
 		
 		answer->totalLoss = deslocationCost[bestLocation];
		answer->location = bestLocation;
 	
 		for(int u = 0; u < F; u++) {
			for(int t=1; t<graph->getNumberOfNodes();t++)
				Q->insert(graph->getNodeAt(t));
			
			Dijkstra::run(graph, subsidiaries->at(u), Q);
			answer->deslocationCost[u] = graph->getNodeAt(bestLocation)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
 		}
 		
 		delete[] deslocationCost;
 		
		delete(Q);
 	}




// 	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){
// 
// 		int F = subsidiaries->size(), temp_loss = 0;
// 
// 		int *aux, *temp = new int[F];
// 		for(int i=0; i<F; i++)
// 			temp[i] = 99999;
// 
// 		connectSource(graph);
// 		BellmanFord::run(graph, 0);
// 		disconnectSource(graph);
// // 		std::cout << graph << std::endl;
// 
// 		copyCostToH(graph);
// 		for(int t = 1; t < graph->getNumberOfNodes(); t++){
// 			graph->getNodeAt(t)->reweightEdges();
// 		}
// 
// // 		std::cout << "before dijkstra " << graph << std::endl;
// 
// 		for(int v = 1; v < graph->getNumberOfNodes(); v++){
// 
// 			for(int u = 0; u < F; u++) {
// 				Dijkstra::run(graph, subsidiaries->at(u));		// unnecessary runs of dijkstra
// // 				std::cout << "after dijkstra " << graph << std::endl;
// 
// 				temp[u] = graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
// 			}
// 
// 			temp_loss = 0;
// 			for(int u = 0; u < F; u++)
// 				temp_loss = temp_loss + temp[u];
// 
// // 			std::cout << v << ": " << temp_loss << std::endl;
// 
// 			if(temp_loss < answer->totalLoss) {
// 				answer->totalLoss = temp_loss;
// 				answer->location = v;
// 
// 				aux = temp;
// 				temp = answer->deslocationCost;
// 				answer->deslocationCost = aux;
// 			}
// 		}
// 
// // 		std::cout << std::endl;
// 
// 		delete[] temp;
// 	}

};



/*************************** src/main.cpp ***************************/


int main () {
	int V = 0, F=0, E = 0;
	int temp = -1;
	Graph* graph;
	std::vector<int>* subsidiaries = new std::vector<int>();
	
	Solution * solution;
	
	std::cin >> V;
	std::cin >> F;
	std::cin >> E;
	

	for(int t=0; t<F; t++) {
		std::cin >> temp;
		subsidiaries->push_back(temp);
	}
	
	solution = new Solution(F);
	graph = new Graph(V, E);

// 	std::cout << graph << std::endl;
	
	Johnson::run(graph, subsidiaries, solution);
	solution->print();
	
	// free memory
	delete(subsidiaries);
	delete(solution);
	delete(graph);
	return 0;
	
}

