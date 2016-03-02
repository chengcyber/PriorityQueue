/*
 * File: pqheap.cpp
 * -------------------
 * This file implements the priority queque class as heap,
 * something like heap-sort to ensure the max element is the root node.
 */

#include "pqueue.h"
#include "genlib.h"
#include <iostream>

using namespace std;

template <typename EleType>
int orginalCompare(EleType &e1, EleType &e2)
{
	if(e1 == e2) return 0;
	if(e1 < e2) return -1;
	if(e1 > e2) return 1;
}

/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqlist looks like this:
 	Vector<int> heap;
 	void heapinserted();
 	void heapremoved(int father);
 	void swap(Vector<int> &vec, int x, int y);
 */

template <typename EleType>
PQueue<EleType>::PQueue()
{
	cmp = orginalCompare;
}
template <typename EleType>
PQueue<EleType>::PQueue(compare cmp)
{
	this->cmp = cmp;
}
template <typename EleType>
PQueue<EleType>::~PQueue()
{
	delete cmp;
}
template <typename EleType>
bool PQueue<EleType>::isEmpty()
{
	return heap.isEmpty();
}
template <typename EleType>
int PQueue<EleType>::size()
{
	return heap.size();
}
template <typename EleType>
void PQueue<EleType>::enqueue(EleType newValue)
{

	if(heap.isEmpty())
		heap.add(newValue);
	else {
		heap.add(newValue);
		heapinserted();
	}

}
template <typename EleType>
EleType PQueue<EleType>::dequeueMax()
{
	if(heap.isEmpty())
		Error("Tried to dequeue max from an empty pqueue!");

	EleType value = heap[0];
	heap[0] = heap[heap.size() - 1];
	heap.removeAt(heap.size() - 1);
	heapremoved(1);
	return value;
}
template <typename EleType>
int PQueue<EleType>::bytesUsed()
{
	return sizeof(*this) + heap.bytesUsed();
}
template <typename EleType>
string PQueue<EleType>::implementationName()
{
	return "sorted heap";
}
template <typename EleType>
void PQueue<EleType>::printDebuggingInfo()
{
	cout << "------------------ START DEBUG INFO ------------------" << endl;
	cout << "Pqueue contains " << heap.size() << " entries" << endl;
	for (int i = 0; i < heap.size(); i++) 
		cout << heap[i] << " ";
	cout << endl;
	cout << "------------------ END DEBUG INFO ------------------" << endl;
}
template <typename EleType>
void PQueue<EleType>::heapinserted()
{
	int child = heap.size();
	while(true) {
		int father = child / 2 ;
		if(heap[child - 1] > heap[father - 1]) 
			swap(heap, father - 1, child - 1);
		child = father;
		if(child == 1) break;
	}
}
template <typename EleType>
void PQueue<EleType>::heapremoved(int father)
{
	int left = 2 * father;
	int right = 2 * father + 1;
	if (left > heap.size() || right > heap.size()) return;
	if(left == heap.size()) {
		if(heap[father - 1] > heap[left - 1]) {
			swap(heap, father, left);
			heapremoved(left);
		}
	} else {
		if(heap[left - 1] >= heap[right - 1]) {
			if(heap[father - 1] < heap[left - 1]) {
				swap(heap, father - 1, left - 1);
				heapremoved(left);
			}
		}
		else {
			if(heap[father - 1] < heap[right - 1]) {
				swap(heap, father - 1, right - 1);
				heapremoved(right);
			}
		}
	}
}
template <typename EleType>
void PQueue<EleType>::swap(Vector<EleType> &vec, int x, int y) {
	EleType tmp = vec[x];
	vec[x] = vec[y];
	vec[y] = tmp;
}