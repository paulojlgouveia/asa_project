
/**********************************************/
/** Grupo: al095							 **/
/** Paulo Jorge Louseiro Gouveia, 75657		 **/
/** Daniel Machado de Castro Figueira, 75694 **/
/**********************************************/

#include <iostream>
#include <vector>
#include <stack>
#include <list>

//Declaration and Implementation of some classes are done separately
//in order to prevent problems with mutual dependencies

/*************************** Data Structures Declaration ***************************/

class Node;

class Edge {
	int _weight;
	Node* _next;

public:
// constructors
	Edge(Node* next, int weight) : _weight(weight), _next(next) { }
	
// destructors
	virtual ~Edge() { }
	
// getters
	Node* getNext() const ;
	int getWeight() const ;
	
// setters
	void setNext(Node* next) ;
	void setWeight(int weight) ;

};


class Node {
	int _h;
	int _pathCost;
	int _heapIndex;
	int _adjSize;
	std::list<Edge*>* _adjList;
	
public:

// constructors
	Node() : _h(99999), _pathCost(99999), _heapIndex(-1), _adjSize(0) {
		_adjList = new std::list<Edge*>();
	}

// destructors
	virtual ~Node() {
		deleteAdjacencies();
	}
	void clearAdjacencies();
	void deleteAdjacencies();
	
// getters
	int getAdjacenciesSize() const { return _adjSize; }
	int getPathCost() const { return _pathCost; }
	int getH() const { return _h; }
	std::list<Edge*>* getAdjacenciesList() const { return _adjList; }
	int getHeapIndex() const { return _heapIndex; }
	
// setters
	void setPathCost(int cost) { _pathCost = cost; }
	void setH(int h) { _h = h; }
	void setHeapIndex(int index) { _heapIndex = index; }
	
// methods
	void connect(Node* adjacent, int weight);
	void reweightEdges();
	int getReweightPathCost(Node *source);
};


/*************************** Data Structures Implementation ***************************/


// Edge Methods
Node* Edge::getNext() const { return _next; }
int Edge::getWeight() const { return _weight; }
void Edge::setNext(Node* next) { _next = next; }
void Edge::setWeight(int weight) { _weight = weight; }

// Node Methods
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
	return 99999;
}

//Graph (definition & implementation)
class Graph {
	int _vertices;
 	std::vector<Node*> *_nodes;
	std::vector<Node*> *_Edges;
	
public:
// constructors
	Graph(int V, int E) : _vertices(V+1) {
		int node1=0, node2=0, weight=0;
		_nodes = new std::vector<Node*>();
		
		for(int t = 0; t < _vertices; t++)
			_nodes->push_back(new Node());
		
		//read edges from stdin
		for(int t = 0; t < E; t++) {
			std::cin >> node1;
			std::cin >> node2;
			std::cin >> weight;
			
			//connect nodes (index = id - 1)
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
	std::vector<Node*>* getNodesArray() const { return _nodes; }
	Node* getNodeAt(int index) const { return _nodes->at(index); }
};


//Binary Heap (definition & implementation)
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
		delete[] _data;
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
};


// Solution (definition & implementation)
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


/*************************** Algorithm Auxiliary Functions ***************************/

void initializeSingleSource(Graph* graph, Node* s) {
	for (int t = 0; t < graph->getNumberOfNodes(); t++) {
		graph->getNodeAt(t)->setPathCost(99999);
	}
	s->setPathCost(0);
}

static void relax(Node *u, Node *v, int weight){
	if(v->getPathCost() > (u->getPathCost() + weight)) {
		v->setPathCost(u->getPathCost() + weight);
	}
}

void relaxAndUpdateQueue(Node *u, Node *v, int weight, BMinHeap *Q){
	if(v->getPathCost() > (u->getPathCost() + weight)) {
		v->setPathCost(u->getPathCost() + weight);
		Q->decreaseKey(v->getHeapIndex());
	}
}

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


/*************************** Algorithm Implementations ***************************/


// runs bellman-ford algorithm starting at node with given id
void BellmanFord(Graph *graph, int id){
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


void Dijkstra(Graph* graph, Node* s) {
	Node *node1, *node2;
	int weight;
	
	initializeSingleSource(graph, s);
	
	BMinHeap* Q = new BMinHeap(graph->getNumberOfNodes());
	
	for(int t=1; t<graph->getNumberOfNodes();t++)
		Q->insert(graph->getNodeAt(t));

	std::list<Edge*>::iterator adjIterator;
	std::list<Edge*>* adjList;
	
	while(Q->size() > 0) {
		node1 = Q->extractMin();

		adjList = node1->getAdjacenciesList();
		for(adjIterator = adjList->begin(); adjIterator != adjList->end(); adjIterator++) {
			node2 = (*adjIterator)->getNext();
			weight = (*adjIterator)->getWeight();
			
			relaxAndUpdateQueue(node1, node2, weight, Q);
		}
	}
	
	delete(Q);
}


static void Johnson(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){
	
	int V = graph->getNumberOfNodes();
 	int F = subsidiaries->size();
 	int *aux = new int[V];
	Node *source;
 	int tempCost = 99999;
	
 	connectSource(graph);
 	BellmanFord(graph, 0);
 	disconnectSource(graph);
	
 	copyCostToH(graph);
 	for(int t = 1; t < V; t++){
 		graph->getNodeAt(t)->reweightEdges();
 	}
	
 	for(int u = 0; u < F; u++) {
		source = graph->getNodeAt(subsidiaries->at(u));
 		Dijkstra(graph, source);
		
 		for(int v = 0; v < V; v++){
			if(aux[v] < 99999)
				aux[v] += graph->getNodeAt(v)->getReweightPathCost(source);
			else
				aux[v] = 99999;
 		}
 	}
 	
	for(int v = 0; v < V; v++) {
	
		if(aux[v] < tempCost){
			tempCost = aux[v];
			answer->location = v;
			answer->totalLoss = tempCost;
		}
	}
	
 	for(int u = 0; u < F; u++) {
		source = graph->getNodeAt(subsidiaries->at(u));
		Dijkstra(graph, source);
		
		answer->deslocationCost[u] = graph->getNodeAt(answer->location)->getReweightPathCost(source);
		
		if(answer->deslocationCost[u] >= 99999) {
			answer->totalLoss = 99999;
			break;
		}
 	}
	
	delete[] aux;
}


/*************************** Main Function ***************************/


int main () {
	int V = 0, F=0, E = 0;
	int temp = -1;
	Graph *graph;
	Solution *solution;
	std::vector<int> *subsidiaries = new std::vector<int>();
	
	// build data structures from strandart input
	std::cin >> V;
	std::cin >> F;
	std::cin >> E;

	for(int t=0; t<F; t++) {
	 	std::cin >> temp;
		subsidiaries->push_back(temp);
	}
	
	solution = new Solution(F);
	graph = new Graph(V, E);
	
	// run Johnson algotithm
	Johnson(graph, subsidiaries, solution);

	// print solution to standart output
	solution->print();
	
	// free used memory
	delete(subsidiaries);
	delete(solution);
	delete(graph);
	
	return 0;
}


