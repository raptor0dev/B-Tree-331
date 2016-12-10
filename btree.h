// btree.h
#pragma once
#ifndef BTREE_H
#define BTREE_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int MaxKeys = 6;   // maximum keys in a tree node
const int MaxKeysPlusOne = MaxKeys + 1;
const int MinKeys = MaxKeys/2;    //minimum number of trees in a node
const long NilPtr = -1L;   // the L indicates a long int
const int KeyFieldMax = 4;

const int KFMaxPlus1 = KeyFieldMax + 1;
const int DataFieldMax = 4;
const int DFMaxPlus1 = DataFieldMax + 1;
const int NULLCHAR = '\0';  // NULL character used to mark end of a string
typedef char KeyFieldType[KFMaxPlus1];
typedef char DataFieldType[DFMaxPlus1];
typedef struct
{
	KeyFieldType KeyField;
	DataFieldType DataField;
} ItemType;

typedef struct
{
	int Count;               // Number of keys stored in the current node
	ItemType Key[MaxKeys];   // Warning: indexing starts at 0, not 1
	long Branch[MaxKeysPlusOne];   // Fake pointers to child nodes
} NodeType;

class BTree
{
private:
	/**
	* @brief mutator function for idNum
	* @brief sets the Idnum to the private integer variable to be used in the program
	* @post sets idNum
	* @param num the idNum to be set of type of integer
	* @return void
	*
	*/
	void checkSubtree(long Current, KeyFieldType & Last); // for debugging
	bool searchNode(const KeyFieldType Target, int & location) const;
	void addItem(const ItemType & NewItem, long NewRight,
		NodeType & Node, int Location);
	void split(const ItemType & CurrentItem, long CurrentRight,
		long CurrentRoot, int Location, ItemType & NewItem,
		long & NewRight);
	void pushDown(const ItemType & CurrentItem, long CurrentRoot,
		bool & MoveUp, ItemType & NewItem, long & NewRight);
	long Root;       // fake pointer to the root node
	long NumNodes;   // number of nodes in the B-tree
	int NodeSize;    // number of bytes per node
	NodeType CurrentNode;   // storage for current node being worked on
	fstream DataFile;   // the file stream for the table data
	long NumItems;      // number of records of type ItemType in the table
	char OpenMode;      // r or w (read or write) mode for the table

public:
	BTree(char Mode, char * FileName);
	~BTree(void);
	bool insert(const ItemType & Item);
	bool retrieve(KeyFieldType SearchKey, ItemType & Item);

	void dump(void);   // for debugging only - could be removed
	void check(void);   // for debugging only
	void printTreeRoot() {cout << "Root is B+tree node number: " << Root << endl;}

};

#endif /* end of BPT_H */