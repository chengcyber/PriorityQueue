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

/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqlist looks like this:
 	Vector<int> heap;
 	void heapinserted();
 	void heapremoved(int father);
 	void swap(Vector<int> &vec, int x, int y);
 */


PQueue::PQueue()
{

}

PQueue::~PQueue()
{

}

bool PQueue::isEmpty()
{
	return heap.isEmpty();
}

int PQueue::size()
{
	return heap.size();
}

void PQueue::enqueue(int newValue)
{

	if(heap.isEmpty())
		heap.add(newValue);
	else {
		heap.add(newValue);
		heapinserted();
	}

}

int PQueue::dequeueMax()
{
	if(heap.isEmpty())
		Error("Tried to dequeue max from an empty pqueue!");

	int value = heap[0];
	heap[0] = heap[heap.size() - 1];
	heap.removeAt(heap.size() - 1);
	heapremoved(1);
	return value;
}

int PQueue::bytesUsed()
{
	return sizeof(*this) + heap.bytesUsed();
}

string PQueue::implementationName()
{
	return "sorted heap";
}

void PQueue::printDebuggingInfo()
{
	cout << "------------------ START DEBUG INFO ------------------" << endl;
	cout << "Pqueue contains " << heap.size() << " entries" << endl;
	for (int i = 0; i < heap.size(); i++) 
		cout << heap[i] << " ";
	cout << endl;
	cout << "------------------ END DEBUG INFO ------------------" << endl;
}

void PQueue::heapinserted()
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
void PQueue::heapremoved(int father)
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

void PQueue::swap(Vector<int> &vec, int x, int y) {
	int tmp = vec[x];
	vec[x] = vec[y];
	vec[y] = tmp;
}