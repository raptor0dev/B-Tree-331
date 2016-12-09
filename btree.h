// btree.h
#pragma once
#ifndef BTREE_H
#define BTREE_H

#include <fstream>
#include <iostream>
using namespace std;

const int MaxKeys = 11;   // max number of keys in a node
const int MaxKeysPlusOne = MaxKeys + 1;
const int MinKeys = 5;    // min number of keys in a node
const long NilPtr = -1L;   // the L indicates a long int
const int KeyFieldMax = 12;

const int KFMaxPlus1 = KeyFieldMax + 1;
const int DataFieldMax = 36;
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

class BTTableClass
{
private:
	void CheckSubtree(long Current, KeyFieldType & Last); // for debugging
	bool SearchNode(const KeyFieldType Target, int & location) const;
	void AddItem(const ItemType & NewItem, long NewRight,
		NodeType & Node, int Location);
	void Split(const ItemType & CurrentItem, long CurrentRight,
		long CurrentRoot, int Location, ItemType & NewItem,
		long & NewRight);
	void PushDown(const ItemType & CurrentItem, long CurrentRoot,
		bool & MoveUp, ItemType & NewItem, long & NewRight);
	long Root;       // fake pointer to the root node
	long NumNodes;   // number of nodes in the B-tree
	int NodeSize;    // number of bytes per node
	NodeType CurrentNode;   // storage for current node being worked on
	fstream DataFile;   // the file stream for the table data
	long NumItems;      // number of records of type ItemType in the table
	char OpenMode;      // r or w (read or write) mode for the table

public:
	BTTableClass(char Mode, char * FileName);
	~BTTableClass(void);
	bool Empty(void) const;
	bool Insert(const ItemType & Item);
	bool Retrieve(KeyFieldType SearchKey, ItemType & Item);

	void Dump(void);   // for debugging only - could be removed
	void Check(void);   // for debugging only
	void printTreeRoot() {cout << "Root: " << Root << endl;}

};

#endif /* end of BPT_H */