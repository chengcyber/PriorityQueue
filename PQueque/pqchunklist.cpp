/*
 * File: pqchunklist.cpp
 * -------------------
 * This file implementes the Class PQueue with a chunklist, which is a hybird
 * strategy between array and linked list. Each chunk is a constant size of array,
 * and contains a pointer to the next linked element.
 */

#include "pqueue.h"
#include "genlib.h"
#include <iostream>
#include "vector.h"

using namespace std;

const int chunkMaxSize = 100;

/*
 * Implementation notes: PQueue Class
 * ----------------------------------
 * the private section for the pqchunklist looks like this:
 	struct Cell {
		Vector<int> chunk;
		Cell *next;
  	}
  	Cell *head;

  	void expandChunk(Cell *cl);
 */

/*
 * Implementation notes: constructor
 * ----------------------------------
 * When the head is NULL, the pqueue is empty.
 */
PQueue::PQueue()
{
	head = NULL;
}

PQueue::~PQueue()
{
	while(head != NULL) {
		Cell *next = head->next;
		delete head;
		head = next;
	}

}

bool PQueue::isEmpty()
{
	return (head == NULL);
}

int PQueue::size()
{
	int count = 0;
	for(Cell *cur = head; cur != NULL; cur = cur->next) {
		count += cur->chunk.size();
	}
	return count;
}

void PQueue::enqueue(int newElem)
{
	

	if(isEmpty()) {
		head = new Cell;
		// Vector<int> chunk;
		// newOne->chunk = chunk;
		head->next = NULL;
		head->chunk.add(newElem);
	} else {
		Cell *cp = NULL;
		int index;
		for (Cell *cur = head; cur != NULL; cur = cur->next) {
			for(index = 0; index < cur->chunk.size(); index++) {
				if(newElem > cur->chunk[index]) {
					cp = cur;
					break;
				}
			}
			if (cp != NULL) break;
			if (cur->next == cp) cp = cur;
		}
		if(cp->chunk.size() == chunkMaxSize) {
			expandChunk(cp);
			if (index > chunkMaxSize / 2) {
				index -= chunkMaxSize / 2;
				cp = cp->next;
			}
		} 

		cp->chunk.insertAt(index, newElem);
	}


}

int PQueue::dequeueMax()
{
	if(isEmpty())
		Error("Tried to dequeue max from an empty pqueue!");

	Cell *cur = head;
	int value = cur->chunk[0];
	cur->chunk.removeAt(0);
	if(cur->chunk.size() == 0) {
		head = head->next;
		delete cur;
	}
	return value;
}

int PQueue::bytesUsed()
{
	int total = sizeof(*this);
	for (Cell *cur = head; cur != NULL; cur = cur->next)
		total += cur->chunk.bytesUsed();
	return total;
}

string PQueue::implementationName()
{
	return "sorted chunk list";
}

void PQueue::printDebuggingInfo()
{
	int cnt_cell = 0;

	cout << "------------------ START DEBUG INFO ------------------" << endl;
	for (Cell *cur = head; cur != NULL; cur = cur->next) {
		for (int i = 0; i < cur->chunk.size(); i++) {
       cout << "Cell #" << cnt_cell << " (at address " << cur << ") val #" << i << " = " 
    		<< cur->chunk[i] << " next = " << cur->next << endl;
    	}
    	cnt_cell++;
	}
	cout << "------------------ END DEBUG INFO ------------------" << endl;
}

void PQueue::expandChunk(Cell *cl) 
{
	Cell *cl2 = new Cell;
	int halfSize = chunkMaxSize / 2;
	for(int i = halfSize; i < chunkMaxSize; i++) {
		cl2->chunk.add(cl->chunk[halfSize]);
		cl->chunk.removeAt(halfSize);
	}
	cl2->next = cl->next;
	cl->next = cl2;
}