/**
@file dualHeap.h
@author Burg, Christopher N. Jesse Babcock Garrett Kamrath
Dayitwa Shrestha, Sanam Lama, Kapil Joshi
@date Monday, November 21, 2016
@version revision 1.2

@brief Class represents back to back min heap operations.

@details
The dual heap class is two min heaps that are back to back
and implemented by a single array. The heaps are the active and pending heaps.
Its array structure starts like this: [(root)active heap ->|<-pending heap(root)]
New elements are heapified onto the active side until it is full at ten elements.
Afterwards when a new element is addded the active heap is popped.
The popped value is compared to the incoming pushed value.
If it is larger then the pooped value it is heapified onto the active heap.
If it is smaller than the popped value it is heapified onto the pending heap side
and the active heap size is decremented by one and pending size is incremented by one.
When the pending side takes up the entire array it turns into the active heap
and the pending side is now the left side of the array and size 0.
*/

#pragma once
#ifndef DUALHEAP_H
#define DUALHEAP_H
#include <array>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>
#include <fstream>
#include "type.h"
#include "Record.h"
using namespace std;

#define SIZE 10	//size of dual heap

//TYPEDEF  //typedef macro for Item

class dualHeap
{
private:

	array<Record, SIZE> heaparray;
	bool heapDirection;
	int activeCount;
	int pendingCount;
	int flipCount;
	int index;

	/**
	* @brief moves the root down the tree to make it a min heap
	* @pre given the index of the node to move
	* @post tree is made into a min heap
	* @param index of a node in the tree
	* @return void
	*/
	void sortDown(int index);

	/**
	* @brief moves the leaf up the tree to make it a min heap
	* @pre given the index of the node to move
	* @post tree is made into a min heap
	* @param index of a node in the heap
	* @return void
	*/
	void sortUp(int index);

public:
	/**
	* @brief dual heap constructor
	*/
    dualHeap(const vector<Record> &vectorObj);

	/**
	* @brief dual heap constructor
	*/
	dualHeap();

	/**
	* @brief heapifies the min heap
	* @pre have a non empty heap.
	* @post heap becomes a min heap
	* @return void
	*/
    void Heapify();

	/**
	* @brief pops the root of the active heap off the tree
	* @pre have a non-empty tree
	* @post root is popped and heap is reheapified.
	* @return void
	*/
	void active_heap_pop();

	/**
	* @brief pushes a new item onto the root of the active heap
	* @pre has a valid item to push onto the heap
	* @post the pushed value is put into its right place in the min heap
	* @param pushValue is the item being added to the heap
	* @return void
	*/
	void active_heap_push(const Record &pushValue);

	/**
	* @brief pushes a new item onto the root of the pending heap
	* @pre has a valid item to push onto the heap
	* @post the pushed value is put into its right place in the min heap
	* @param pushValue is the item being added to the heap
	* @return void
	*/
	void pending_heap_push(const Record &pushValue);

	/**
	* @brief flips the heap directions. pending becomes the active heap and active the pending heap.
	* @pre have a full pending heap
	* @post pending becomes a full active heap and pending becomes an empty heap
	* @return void
	*/
	void directionFlip();

	/**
	* @brief returns the root of the active heap
	* @pre have a non-empty heap
	* @post returns the root value
	* @return Item root
	*/
	Record getRoot();

	/**
	* @brief prints out the heap contents
	* @pre have a heap
	* @post prints heap contents to the console
	* @return void
	*/
	void printHeap();

	/**
	* @brief prints out the heap contents to a log file
	* @pre have a heap
	* @post prints heap contents to the log file
	* @param logfile is the item being added to the heap
	* @return void
	*/
    void printHeapToFile(ofstream &logfile);

	/**
	* @brief returns a copy of the heap
	* @pre have a non empty heap
	* @post heap copy returned
	* @return heap copy
	*/
    array<Record, SIZE> getHeapArray() const;

	/**
	* @brief returns the number active elements
	* @pre
	* @post returns activeCount
	* @return returns activeCount
	*/
	int getActiveCount() const;

	/**
	* @brief returns the number of pending elements
	* @pre
	* @post returns pendingCount
	* @return returns pendingCount
	*/
	int getPendingCount() const;

	/**
	* @brief sets the active count of the heap
	* @pre have a heap
	* @post activeCount is set
	* @param activeVal is the number activeCount is set to
	* @return void
	*/
	void setActiveCount(const int &activeVal);

	/**
	* @brief sets the pending count of the heap
	* @pre have a heap
	* @post pendingCount is set
	* @param pendingVal is the number pendingCount is set to
	* @return void
	*/
	void setPendingCount(const int &pendingVal);

	/**
	* @brief returns the number of times the direction flag has been switched
	* @pre have a heap
	* @post flipCount is returned
	* @return int
	*/
	int getFlipCount() const;
};

//#include "dualHeap.cpp"
#endif
