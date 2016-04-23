#ifndef __BINARYMINHEAP_H__
#define __BINARYMINHEAP_H__

#include <iostream>
#include "Node.h"

//MERGE_START

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



//MERGE_END



#endif



