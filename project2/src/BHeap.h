#ifndef __BINARYHEAP_H__
#define __BINARYHEAP_H__

#include <iostream>
#include <algorithm>
#include <vector>


// template <class T>
class BHeap {

private:
	std::vector<Node*> _heap;


	static bool compareFunction(const Node *a, const Node *b) {
		return (a->getPathCost() >= b->getPathCost());
	}
	
	
public:
	
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
	
	
	
	void pop_back() { _heap.pop_back(); }
	
	
// operators
	friend std::ostream &operator<<(std::ostream &out, const BHeap *heap) {
		
  		for(int t=0; t<heap->size(); t++) {
 			out << heap->getNodeAt(t)->getId() << " ";		 
 		}
 		
 		out << std::endl;
 		
 		return out;	
 	}
	
	
	
	
/*

// 	Max-Heapify(A, i)
// 		l ← Left(i)
// 		r ← Right(i)
// 		if l ≤ heap-size[A] and A[l] > A[i]
// 			then largest ← l
// 			else largest ← i
// 		if r ≤ heap-size[A] and A[r ] > A[largest]
// 			then largest ← r
// 		if largest = i
// 			then exchange A[i] ↔ A[largest]
// 				 Max-Heapify(A, largest)
	
	void maxHeapify(int index) {
		int l = -1, r = -1, largest = -1;
		
		if(l <= heap->size() && heap[l]->getPathCost() > heap[i]->getPathCost()) {
			largest = l;
		} else {
			largest = i;
		}
		
		if(l <= heap->size() && heap[r]->getPathCost() > heap[largest]->getPathCost()) {
			largest = r;
		}
		
		if(largest == i) {
			Node *temp = heap[i];
			heap[i] = heap[largest];
			heap[largest] = temp;
			
			maxHeapify(largest);
		}

	}

	
// 	Build-Max-Heap(A)
// 		heap-size[A] ← length[A]
// 		for i ← length[A]/2 downto 1
// 			do Max-Heapify(A, i)

	void buildMaxHeap() {
		for(int t=heap->size()/2; i>=1; i--)
			maxHeapify(t);
	}
	
	T *extractMax() {
		
	}

	T *extractMin() {
		
	}

	
// 	Heap-Sort(A)
// 		Build-Max-Heap(A)
// 		for i ← length[A] downto 2
// 			do  exchange A[1] ↔ A[i]
// 				heap-size[A] ← heap-size[A] − 1
// 				Max-Heapify(A, 1)
	
	void sort() {
		buildMaxHeap();
		for(int t=heap->size(); t>=2; t--){
			Node *temp = heap[0];
			heap[i] = heap[largest];
			heap[largest] = temp;
			
			maxHeapify(largest);
		}
	}


*/


};


#endif














/*

#ifndef __BINARYHEAP_H__
#define __BINARYHEAP_H__

#include <vector>
#include <iterator>
#include <cmath>

// Assume min heap
template <class T>
class BinaryHeap {
	
private:
	unsigned long heap_size_;
	std::vector<T> data_;
	// typedef typename std::vector<T>size_type heap_size_;
	void SiftUp(unsigned long node);
	void SiftDown(unsigned long node);

public:
	BinaryHeap(unsigned long num_elements);
	BinaryHeap();
	~BinaryHeap() {}

	// Misc Operations (using STL namimg).
	unsigned long count() { return heap_size_;}  // Get count of objects.
	void clear();                      // clear the object for reuse.

	// Main operations allowed by the data structure.
	template <class I>
	int Heapify(I start, I end);
	const T FindXtrma();
	const T ExtractXtrma();
	void Insert(const T& data);   // Insert(key)
	void Delete(unsigned long element);     // Delete(element)
	void IncreaseKey(unsigned long element, const T& change);
	void DecreaseKey(unsigned long element, const T& change);
	unsigned long get_size(){return(heap_size_);}
	// void Merge(class &Heap); 
};

#endif




//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __BHEAP_H__
#define __BHEAP_H__
#include <iostream>
#include <string>

using namespace std;
template<class T>

class BHeap {
	
private:
	const int DEFAULT_SIZE;
	T *data;  //array of data in the heap
	int m_count; //count the number of element in the heap
	int m_capacity; //to indicate the current capacity in the heap
	bool sorted; //boolean variable to test whether it is sorted
	
	
public:
	BHeap() : DEFAULT_SIZE(100) {
		data = new T[DEFAULT_SIZE];
		m_capacity = DEFAULT_SIZE;
		m_count = 0;
	}
	
	~BHeap() {
		delete [] data;
	}
	
	int size() const {
		return m_count;
	}

	bool isEmpty() const {
		return m_count == 0;
	}

	void setCapacity(int newCapacity) {
		if ( newCapacity > m_capacity) {
			//allocate new capacity
			T *newData = new T[newCapacity];
			memcpy_s(newData, newCapacity, data, m_count);
			m_capacity = newCapacity;
			//copy old data to new data
			data = newData;
			
			delete [] newData;
		}
	
	}

	void Add(T item);
	void DownHeap();
	void UpHeap();

	T Peek();
	T Remove();
	
	
private:
	
	int Child1(int idx){
		return (idx << 1) + 1;  //Child 1 index = (2 * parentIndex) + 1
	}
	
	int Child2(int idx){
		return (idx << 1) + 2;  //Child 2 index = (2 * parentIndex ) +2
	}
	
	int Parent(int idx){
		return (idx - 1 ) >> 1; //Parent index = (childIndex -1 ) / 2
	}
	
	//void EnsureSort();
};


#endif

*/
