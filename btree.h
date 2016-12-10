/**
@file btree.h
@author Burg, Christopher N., Garrett Kamrath, Jesse Babcock, Dayitwa Shrestha, Sanam Lama, Kapil Joshi
@date December 9, 2016
@version revision 1.2

@brief B+Tree File operations

@details
The B+ Tree class represents all operations assoicated with a B+Tree. 
It works almost entirely off disk, only keeping the root and its current working node
in memory. Can insert and build a tree off a sorted sequence set.
*/
#pragma once
#ifndef BTREE_H
#define BTREE_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int keyMax = 6;				//maximum keys in a tree node
const int keyMin = keyMax / 2;		//minimum number of keys in a node
const int keyMax1 = keyMax + 1;

const int keySize = 4;				//key size of record, or first field
const int keySize1 = keySize + 1;

const int dataSize = 4;				//size of the 2nd field
const int dataSize1 = dataSize + 1;

const long nullPointer = -1L;		//empty pointer
const int NULLCHAR = '\0';			//end of string

//contains the record fields.
typedef char keyType[keySize1];
typedef char dataType[dataSize1];
typedef struct
{
	keyType KeyField;
	dataType DataField;
} itemType;

//contains the keys and the character offset pointers
typedef struct
{
	int keyCount;               //keys held in node
	itemType Key[keyMax];		//holds the record data
	long charOffset[keyMax1];   //charcter offsets or fake pointers
} treeNode;

class BTree
{
private:
	
	long Root;       // root char offset
	long nodeNum;   // number of b+tree nodes
	int nodeSize;    // bytes per node
	treeNode workingNode;   //in memory working node
	fstream workingFile;   // B+tree file
	long itemNum;      // number of items in tree
	char rwMode;      // r or w mode for b+tree

	/**
	* @brief reads branches of B+ tree, debug code
	* @pre a built tree
	* @post travels down the tree branch
	* @param rootPointer points to the root
	* @param lastPointer points to the previous node
	* @return void
	*/
	void checkTree(long rootPointer, keyType & lastPointer); //debug

	/**
	* @brief finds a key in a node
	* @pre a B+tree has nodes
	* @post finds or doesnt find the desired key
	* @param targetKey the desired key
	* @param location index of where the target key was found
	* @return bool
	*/
	bool searchNode(const keyType targetKey, int & location) const;
	
	/**
	* @brief finds a key in a node
	* @pre a B+tree has nodes
	* @post desired node updated
	* @param newItem item being added to the node
	* @param rightPointer points to rightmost child
	* @param node the node being added to
	* @param location node index to add a new item into
	* @return bool
	*/
	void addItem(const itemType & newItem, long rightPointer, treeNode & node, int location);

	/**
	* @brief splits nodes full of keys
	* @pre a B+tree has a full node
	* @post nodes split
	* @param splitNode item that needs splitting
	* @param rightChild points to current right child
	* @param rootPointer current root pointer
	* @param addIndex node index to add a new item into
	* @param newItem item being added to the node
	* @param newRightPointer points to new rightmost child
	* @return void
	*/
	void split(const itemType & splitNode, long rightChild,
		long rootPointer, int addIndex, itemType & newItem,long & newRightPointer);

	/**
	* @brief splits nodes full of keys
	* @pre a B+tree has a full node
	* @post nodes split
	* @param addNewItem item to be inserted into node
	* @param rootPointer current root pointer
	* @param moveToParent boolean if true sends key to parent
	* @param newItem item being added to the parent node if spit
	* @param rightPointer points to new rightmost child
	* @return void
	*/
	void pushDown(const itemType & addNewItem, long rootPointer,
		bool & moveToParent, itemType & newItem, long & rightPointer);

public:
	/**
	* @brief constructor for the B+tree
	* @pre a file to read from
	* @post makes a B+tree object
	* @param  mode read or write.
	* @param fileName working file to read/write from
	* @return void
	*/
	BTree(char mode, char * fileName);
	
	/**
	* @brief destroys B+tree object and writes final contents to file
	* @pre a B+tree object
	* @post destroys a B+tree object
	* @return void
	*/
	~BTree(void);
	
	/**
	* @brief inserts a new key into the tree
	* @pre a B+tree object
	* @post adds the key into the tree
	* @param  addKeykey to be added to the tree
	* @return bool
	*/
	bool insert(const itemType & addKey);

	/**
	* @brief searches for a key in the tree
	* @pre a B+tree object
	* @post finds the key
	* @param  searchKey key that needs to be found
	* @param  foundNode node where the key was found.
	* @return bool
	*/
	bool retrieve(keyType searchKey, itemType & foundNode);

	/**
	* @brief prints the contents of the whole tree
	* @pre a B+tree object
	* @post everything printedd to console
	* @return void
	*/
	void dump(void);   //debug
	
	/**
	* @brief prints root node location
	* @pre a B+tree object
	* @post prints root location
	* @return void
	*/
	void printTreeRoot() {cout << "Root is B+tree node number: " << Root << endl;}
};

#endif