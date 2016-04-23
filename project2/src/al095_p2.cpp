
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

};




/*************************** src/Node.h ***************************/

class Node {
	int _adjSize; 					// size of adjacencies list (because of c++98)
	std::list<Edge*>* _adjList;		// list of adjacent nodes
	
	int _pathCost;
	int _h;
	
	int _heapIndex;
	
	
public:

// constructors
	Node() : _adjSize(0), _pathCost(99999), _heapIndex(-1) {
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


 


/*************************** src/Graph.h ***************************/

class Graph {
	int _vertices;					// number of vertices
 	std::vector<Node*> *_nodes;		// list of nodes
	
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
// 		delete(_data);
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


// 	friend std::ostream &operator<<(std::ostream &out, const BMinHeap *heap) {
// 		out << std::endl;
// 		out << "heap size: " << heap->size() << std::endl;
// 		out << "max heap size: " << heap->capacity() << std::endl;
// 		
//   		for(int t=0; t<heap->size(); t++) {
// // 			out << heap->at(t)->getPathCost() << " ";
// 			out << heap->at(t)->getHeapIndex() << ",";
// 			out << heap->at(t)->getId() << "  ";
// 		}
//  		
//  		return out;
//  	}
 	
 	
};


// class BMinHeap {
// // 	Node **_data;
// 	std::vector<Node*> _data;
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
// 	void swap(int a, int b) {
// 		Node *temp = _data[a];
// 		_data[a] = _data[b];
// 		_data[b] = temp;
// 		_data[a]->setHeapIndex(a);
// 		_data[b]->setHeapIndex(b);
// 	}
// 		
// 	void fixUp(int nodeIndex) {
// 		int parentIndex;
// 		
// 		if (nodeIndex != 0) {
// 			parentIndex = getParentIndex(nodeIndex);
// 			if (_data[parentIndex]->getPathCost() > _data[nodeIndex]->getPathCost()) {
// 				swap(parentIndex, nodeIndex);
// 				fixUp(parentIndex);
// 			}
// 		}
// 	}
// 	
// 	void fixDown(unsigned int nodeIndex) {		
// 		unsigned int leftChildIndex, rightChildIndex, minIndex;
// 		int leftChildWeight, rightChildWeight, minWeight;
// 		
// 		if(nodeIndex < _data.size()) {			
// 			minIndex = nodeIndex;
// 			minWeight = _data[nodeIndex]->getPathCost();
// 			
// 			leftChildIndex = getLeftChildIndex(nodeIndex);
// 			if(leftChildIndex < _data.size()) {
// 				leftChildWeight = _data[leftChildIndex]->getPathCost();
// 				if(leftChildWeight < minWeight) {
// 					minIndex = leftChildIndex;
// 					minWeight = _data[minIndex]->getPathCost();
// 				}
// 			}
// 			
// 			rightChildIndex = getRightChildIndex(nodeIndex);
// 			if(rightChildIndex < _data.size() ) {
// 				rightChildWeight = _data[rightChildIndex]->getPathCost();
// 				if(rightChildWeight < minWeight) {
// 					minIndex = rightChildIndex;
// 				}
// 			}
// 			
// 			if(minIndex != nodeIndex) {
// 				swap(nodeIndex, minIndex);
// 				fixDown(minIndex);
// 			}
// 		}
// 	}
// 	
// public:
// 	BMinHeap(int size) {
// 		_data.reserve(size/4);
// 		_arraySize = _data.capacity();
// 	}
// 	
// 	~BMinHeap() {
// // 		delete(_data);
// 	}
// 	
// 	bool isEmpty() { return (_data.size() == 0); }
// 	int size() const { return _data.size(); }
// 	int capacity() const { return _data.capacity(); }
// 	Node* at(int index) const { return _data[index]; }
// 	
// 
// 	
// 	void insert(Node* node) {
// 		_data.push_back(node);
// 		node->setHeapIndex(_data.size()-1);
// 		fixUp(_data.size()-1);
// 	}
// 	
// 	Node* extractMin() {
// 		if (_data.size() > 0) {
// 			Node *min = _data[0];
// 			swap(0, _data.size()-1);
// 			_data.pop_back();
// 			fixDown(0);
// 			return min;
// 		} else {
// 			std::cout  << std::endl << "empty" << std::endl;
// 			throw std::string("empty");
// 		}
// 	}
// 	
// 	void decreaseKey(int index) {
// 		while(index > 0 && _data[getParentIndex(index)]->getPathCost() > _data[index]->getPathCost()) {
// 			swap(getParentIndex(index), index);
// 			index = getParentIndex(index);
// 		}
// 	}
// 
// 
// 	friend std::ostream &operator<<(std::ostream &out, const BMinHeap *heap) {
// 		out << std::endl;
// 		out << "heap size: " << heap->size() << std::endl;
// 		out << "max heap size: " << heap->capacity() << std::endl;
// 		
//   		for(int t=0; t<heap->size(); t++) {
// // 			out << heap->at(t)->getPathCost() << " ";
// 			out << heap->at(t)->getHeapIndex() << ",";
// 			out << heap->at(t)->getId() << "  ";
// 		}
//  		
//  		return out;
//  	}
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

	static void initializeSingleSource(Graph* graph, Node* s) {
		for (int t = 0; t < graph->getNumberOfNodes(); t++) {
			graph->getNodeAt(t)->setPathCost(99999);
		}
		s->setPathCost(0);
	}

	static void relax(Node *u, Node *v, int weight, BMinHeap *Q){
		
		if(v->getPathCost() > (u->getPathCost() + weight)) {
			v->setPathCost(u->getPathCost() + weight);
			Q->decreaseKey(v->getHeapIndex());
		}
	}



	static void run(Graph* graph, int index) {
		run(graph, graph->getNodeAt(index));
	}


	static void run(Graph* graph, Node* s) {
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
				
				relax(node1, node2, weight, Q);
			}
		}
		
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
	// corrigi frees e descomentei esta, comentei a outra para submeter
	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){

		int F = subsidiaries->size();
		int tempCost;
		
		int **aux_deslocationCost = new int*[F];
		int *temp, *aux = new int[F];
		
		for(int i=0; i<F; i++) {
			aux_deslocationCost[i] = new int[graph->getNumberOfNodes()];
		}

		connectSource(graph);
		BellmanFord::run(graph, 0);
		disconnectSource(graph);
// 		std::cout << graph << std::endl;

		copyCostToH(graph);
		for(int t = 1; t < graph->getNumberOfNodes(); t++){
			graph->getNodeAt(t)->reweightEdges();
		}

		// std::cout << "before dijkstra " << graph << std::endl;


		for(int u = 0; u < F; u++) {
			Dijkstra::run(graph, subsidiaries->at(u));
// 			std::cout << "after dijkstra " << graph << std::endl;

			for(int v = 1; v < graph->getNumberOfNodes(); v++){
				aux_deslocationCost[u][v] = graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
			}
		}
		
		for(int v = 1; v < graph->getNumberOfNodes(); v++){
			tempCost = 0;
			
			for(int u = 0; u < F; u++) {
				tempCost += aux_deslocationCost[u][v];
			}
			
			if(tempCost < answer->totalLoss) {
				answer->totalLoss = tempCost;
				answer->location = v;
				
				for(int u = 0; u < F; u++)
					aux[u] = aux_deslocationCost[u][v];
				
				temp = aux;
				aux = answer->deslocationCost;
				answer->deslocationCost = temp;
			}
		}
		
		for(int t=0; t<F; t++)
			delete[] aux_deslocationCost[t];
		delete[] aux_deslocationCost;
		
		delete[] aux;
	}
	
//  	static void run(Graph *graph, std::vector<int> *subsidiaries, Solution *answer){
// 		std::list<int>::iterator listIterator;
//  
// 		int V = graph->getNumberOfNodes();
//  		int F = subsidiaries->size();
//  		int *aux_deslocationCost = new int[V];
//  		int bestLocation;
//  
//  		connectSource(graph);
//  		BellmanFord::run(graph, 0);
//  		disconnectSource(graph);
//   
//  		copyCostToH(graph);
//  		for(int t = 1; t < V; t++){
//  			graph->getNodeAt(t)->reweightEdges();
//  			aux_deslocationCost[t] = 0;
//  		}
// 
//  		for(int u = 0; u < F; u++) {
//  			Dijkstra::run(graph, subsidiaries->at(u));
//  
//  			for(int v = 0; v < V; v++){
// 				if(aux_deslocationCost[v] != 99999)
// 					aux_deslocationCost[v] += graph->getNodeAt(v)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
// 				else
// 					aux_deslocationCost[v] = 99999;
//  			}
//  		}
//  		
//  		bestLocation = getBestLocation(aux_deslocationCost, V);
//  	
//  		//Check if best location is valid *FIXME*
//  		
//  		answer->totalLoss = aux_deslocationCost[bestLocation];
// 		answer->location = bestLocation;
//  	
//  		for(int u = 0; u < F; u++) {
// 			Dijkstra::run(graph, subsidiaries->at(u));
// 			answer->deslocationCost[u] = graph->getNodeAt(bestLocation)->getReweightPathCost(graph->getNodeAt(subsidiaries->at(u)));
//  		}
//  		 		
// 		delete[] aux_deslocationCost;	
// 	}




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

