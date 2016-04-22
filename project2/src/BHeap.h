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
	
	void fixUp(int nodeIndex) {
		Node *temp;
		int parentIndex;
		
		if (nodeIndex != 0) {
			parentIndex = getParentIndex(nodeIndex);
			if (_data[parentIndex]->getPathCost() > _data[nodeIndex]->getPathCost()) {
				temp = _data[parentIndex];
				_data[parentIndex] = _data[nodeIndex];
				_data[nodeIndex] = temp;
				fixUp(parentIndex);
			}
		}
	}
	
	void fixDown(int nodeIndex) {
		Node *temp;
		int leftChildIndex, rightChildIndex, minIndex;
		
		leftChildIndex = getLeftChildIndex(nodeIndex);
		rightChildIndex = getRightChildIndex(nodeIndex);
		
		if(rightChildIndex >= _heapSize) {
			if(leftChildIndex >= _heapSize)
				return;
			else
				minIndex = leftChildIndex;
		} else {
			if(_data[leftChildIndex]->getPathCost() <= _data[rightChildIndex]->getPathCost())
				minIndex = leftChildIndex;
			else
				minIndex = rightChildIndex;
		}
		
		if(_data[nodeIndex]->getPathCost() > _data[minIndex]->getPathCost()) {
			temp = _data[minIndex];
			_data[minIndex] = _data[nodeIndex];
			_data[nodeIndex] = temp;
			fixDown(minIndex);
		}
	}
	
	void minHipify() {
// 		Node *temp;
// 		int leftChildIndex, rightChildIndex, minIndex;
// 		
// 		leftChildIndex = getLeftChildIndex(nodeIndex);
// 		rightChildIndex = getRightChildIndex(nodeIndex);
// 		
// 		Node *temp;
// 		int leftChildIndex, rightChildIndex, minIndex;
// 		
// 		
// 		
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
	
	Node* getMinimum() {
		if (isEmpty()) {
			std::cout  << std::endl << "Heap is empty" << std::endl;
			throw std::string("Heap is empty");
		} else
			return _data[0];
	}

	void removeMinimum() {
		if(isEmpty()) {
			std::cout  << std::endl << "Heap is empty" << std::endl;
			throw std::string("Heap is empty");
		} else {
			_data[0] = _data[_heapSize - 1];
// 			_data[_heapSize-1] = NULL;
			_heapSize--;
// 			if (_heapSize > 0)
// 				fixDown(0);
			minHeapify();
		}
	}
	
	void insert(Node* node) {
		if (_heapSize == _arraySize) {
			std::cout  << std::endl << "Heap's underlying storage is overflow" << std::endl;
			throw std::string("Heap's underlying storage is overflow");
		} else {
			_heapSize++;
			_data[_heapSize - 1] = node;
			fixUp(_heapSize - 1);
		}
	}
	
	
	friend std::ostream &operator<<(std::ostream &out, const BMinHeap *heap) {
		out << std::endl;
		out << "heap size: " << heap->size() << std::endl;
		out << "max heap size: " << heap->capacity() << std::endl;
		
  		for(int t=0; t<heap->size(); t++)
 			out << heap->at(t)->getPathCost() << " ";
 		
 		return out;
 	}
	
	friend std::ostream &operator<<(std::ostream &out, const BMinHeap &heap) {
		out << std::endl;
		out << "heap size: " << heap.size() << std::endl;
		out << "max heap size: " << heap.capacity() << std::endl;
		
  		for(int t=0; t<heap.size(); t++)
			out << heap.at(t)->getPathCost() << " ";
 		
 		return out;
 	}

};

//MERGE_END



#endif



