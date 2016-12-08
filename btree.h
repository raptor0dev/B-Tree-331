#pragma once
// btree.h

#ifndef BTREE_H
#define BTREE_H

template <class keyType>
class BTree;

//#include "btnode.h"
//#include "recfile.h"
//#include "fixfld.h"
//#include "indbuff.h"
#include "SequenceSet.h"
using namespace std;
// btree needs to be able to pack, unpack, read and
// 	write index records
// 	also, handle the insert, delete, split, merge,
//	growth of the tree
//	a pool of nodes will be managed
//	keep at least a branch of the tree in memory
//	

template <class keyType>
class BTree
{
private:

	int Height; // height of tree
	int Order; // order of tree
	int PoolSize;

	SequenceSet root;

public:
	BTree(int order, SequenceSet r, int keySize = sizeof(keyType));
	~BTree();
	int Insert(const keyType key, const int recAddr);
	int Remove(const keyType key, const int recAddr = -1);
	int Search(const keyType key, const int recAddr = -1);

};

#endif /* end of BPT_H */