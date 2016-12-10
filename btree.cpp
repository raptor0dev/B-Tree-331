/**
@file btree.cpp
@author Burg, Christopher N., Garrett Kamrath, Jesse Babcock, Dayitwa Shrestha, Sanam Lama, Kapil Joshi
@date December 9, 2016
@version revision 1.2

@brief B+Tree File operations

@details
The B+ Tree class represents all operations assoicated with a B+Tree.
It works almost entirely off disk, only keeping the root and its current working node
in memory. Can insert and build a tree off a sorted sequence set.
*/
#include "btree.h"
#include <iostream>
#include "SequenceSet.h"
using namespace std;

void BTree::dump(void)
{
	int k;
	long p;
	printTreeRoot();

	for (p = 0; p <= nodeNum; p++)
	{
		if (p % 4 == 3)
		{
			cout << "enter for more nodes";
			cin.get();
		}

		workingFile.seekg(p * nodeSize, ios::beg);
		workingFile.read(reinterpret_cast <char *> (&workingNode), nodeSize);

		if (p == 0)
		{
			cout << "Node 0 is the header, contains:" << endl;
			cout << "   items in the node = " << workingNode.charOffset[0] << endl;
			cout << "   number of nodes = " << workingNode.charOffset[1] << endl;
			cout << "   root = " << workingNode.charOffset[2] << endl;
		}
		else
		{
			cout << " node number " << p <<" info"<< endl;
			cout << "   keyNum: " << workingNode.keyCount << endl;

			cout << "   key values: ";
			for (k = 0; k < workingNode.keyCount; k++)
			{
				cout << workingNode.Key[k].KeyField << " ";
			}

			cout << endl << "   Branch Nodes: ";
			for (k = 0; k <= workingNode.keyCount; k++)
			{
				cout << workingNode.charOffset[k] << " ";
			}
			cout << endl << endl;
		}
	}
}

void BTree::checkTree(long rootPointer, keyType & lastPointer)
{
	treeNode Node;
	int k;

	if (rootPointer == nullPointer)
	{
		return;
	}

	workingFile.seekg(rootPointer * nodeSize, ios::beg);
	workingFile.read(reinterpret_cast <char *> (&Node), nodeSize); //fancy magic
	for (k = 0; k < Node.keyCount; k++)
	{
		checkTree(Node.charOffset[k], lastPointer);
		if ((lastPointer[0] != '*') && (strcmp(lastPointer, Node.Key[k].KeyField) >= 0))
		{
			cout << "Check has found a problem in node " <<rootPointer <<
				" index " << k << " key " << Node.Key[k].KeyField << endl;
			dump();
			exit(1);
		}
		strcpy_s(lastPointer, Node.Key[k].KeyField);
	}
	checkTree(Node.charOffset[Node.keyCount], lastPointer);
}

BTree::BTree(char mode, char * fileName)
{
	rwMode = mode;
	nodeSize = sizeof(treeNode);

	if (mode == 'r')
	{
		workingFile.open(fileName, ios::in | ios::binary);
		if (workingFile.fail())
		{
			cout << "Input file cannot be opened" << endl;
		}

		//initializes header info to 0/null if cant read
		workingFile.read(reinterpret_cast <char *> (&workingNode), nodeSize);
		if (workingFile.fail())
		{ 
			itemNum = 0;
			nodeNum = 0;
			Root = nullPointer;
		}
		else   //node at 0 is header info
		{
			itemNum = workingNode.charOffset[0];
			nodeNum = workingNode.charOffset[1];
			Root = workingNode.charOffset[2];
		}
	}
	else if (mode == 'w')
	{
		workingFile.open(fileName, ios::in | ios::out | ios::trunc |ios::binary);
		if (workingFile.fail())
		{
			cout << "Input file failed to open" << endl;
		}

		Root = nullPointer;
		itemNum = 0;
		nodeNum = 0; 
		workingNode.charOffset[0] = itemNum;
		workingNode.charOffset[1] = nodeNum;
		workingNode.charOffset[2] = Root;
		workingFile.seekp(0, ios::beg);
		workingFile.write(reinterpret_cast <char *> (&workingNode), nodeSize);
	}
	else
	{
		cout << "wrong write/read mode" << endl;
	}
}

BTree::~BTree(void)
{
	//writes header info
	if (rwMode == 'w')
	{
		workingNode.charOffset[0] = itemNum;
		workingNode.charOffset[1] = nodeNum;
		workingNode.charOffset[2] = Root;
		workingFile.seekp(0, ios::beg);
		workingFile.write(reinterpret_cast <char *> (&workingNode), nodeSize);
	}
	workingFile.close();
}

bool BTree::searchNode(const keyType targetKey,int & Location) const
{
	bool Found;
	Found = false;

	if (strcmp(targetKey, workingNode.Key[0].KeyField) < 0)
	{
		Location = -1;
	}
	else
	{ 
		Location = workingNode.keyCount - 1;
		while ((strcmp(targetKey, workingNode.Key[Location].KeyField) < 0) && (Location > 0))
		{
			Location--;
		}
		if (strcmp(targetKey, workingNode.Key[Location].KeyField) == 0)
		{
			Found = true;
		}
	}
	return Found;
}

void BTree::addItem(const itemType & newItem, long rightPointer,
	treeNode & node, int location)
{
	int j;

	for (j = node.keyCount; j > location; j--)
	{
		node.Key[j] = node.Key[j - 1];
		node.charOffset[j + 1] = node.charOffset[j];
	}

	node.Key[location] = newItem;
	node.charOffset[location + 1] = rightPointer;
	node.keyCount++;
}

void BTree::split(const itemType & splitNode, long rightChild,
	long rootPointer, int addIndex, itemType & newItem, long & newRightPointer)
{
	int j, Median;
	treeNode RightNode;

	if (addIndex < keyMin)
	{
		Median = keyMin;
	}
	else
	{
		Median = keyMin + 1;
	}

	workingFile.seekg(rootPointer * nodeSize, ios::beg);
	workingFile.read(reinterpret_cast <char *> (&workingNode), nodeSize);

	for (j = Median; j < keyMax; j++)
	{  // move half of the items to the new right node
		RightNode.Key[j - Median] = workingNode.Key[j];
		RightNode.charOffset[j - Median + 1] = workingNode.charOffset[j + 1];
	}

	RightNode.keyCount = keyMax - Median;
	workingNode.keyCount = Median;   // is then incremented by AddItem

	if (addIndex < keyMin)
	{
		addItem(splitNode, rightChild, workingNode, addIndex + 1);
	}
	else
	{
		addItem(splitNode, rightChild, RightNode,
			addIndex - Median + 1);
	}

	newItem = workingNode.Key[workingNode.keyCount - 1];
	RightNode.charOffset[0] = workingNode.charOffset[workingNode.keyCount];
	workingNode.keyCount--;

	workingFile.seekp(rootPointer * nodeSize, ios::beg);
	workingFile.write(reinterpret_cast <char *> (&workingNode), nodeSize);

	nodeNum++;
	newRightPointer = nodeNum;
	workingFile.seekp(newRightPointer * nodeSize, ios::beg);
	workingFile.write(reinterpret_cast <char *> (&RightNode), nodeSize);

}

void BTree::pushDown(const itemType & addNewItem, long rootPointer,
	bool & moveToParent, itemType & newItem, long & rightPointer)
{
	int Location;

	if (rootPointer == nullPointer)   // base case
	{ 
		moveToParent = true;
		newItem = addNewItem;
		rightPointer = nullPointer;
	}
	else   //recursive case
	{
		workingFile.seekg(rootPointer * nodeSize, ios::beg);
		workingFile.read(reinterpret_cast <char *> (&workingNode), nodeSize);

		if (searchNode(addNewItem.KeyField, Location))
			cout << "Error: attempt to put a duplicate into B-tree" << endl;

		pushDown(addNewItem, workingNode.charOffset[Location + 1], moveToParent, newItem, rightPointer);

		if (moveToParent)
		{
			workingFile.seekg(rootPointer * nodeSize, ios::beg);
			workingFile.read(reinterpret_cast <char *> (&workingNode), nodeSize);

			if (workingNode.keyCount < keyMax)
			{
				moveToParent = false;
				addItem(newItem, rightPointer, workingNode, Location + 1);
				workingFile.seekp(rootPointer * nodeSize, ios::beg);
				workingFile.write(reinterpret_cast <char *> (&workingNode), nodeSize);
			}
			else
			{
				moveToParent = true;
				split(newItem, rightPointer, rootPointer, Location, newItem, rightPointer);
			}
		}
	}
}

bool BTree::insert(const itemType & addKey)
{
	bool moveToParent;
	long rightPointer;
	itemType newItem;

	pushDown(addKey, Root, moveToParent, newItem, rightPointer);

	if (moveToParent)   // create a new root node
	{
		workingNode.keyCount = 1;
		workingNode.Key[0] = newItem;
		workingNode.charOffset[0] = Root;
		workingNode.charOffset[1] = rightPointer;
		nodeNum++;
		Root = nodeNum;
		workingFile.seekp(nodeNum * nodeSize, ios::beg);
		workingFile.write(reinterpret_cast <char *> (&workingNode), nodeSize);
	}
	itemNum++;
	return true;
}

bool BTree::retrieve(keyType searchKey, itemType & foundNode)
{
	long currentRoot;
	int index;
	bool found;

	found = false;
	currentRoot = Root;

	while ((currentRoot != nullPointer) && (!found))
	{
		workingFile.seekg(currentRoot * nodeSize, ios::beg);
		workingFile.read(reinterpret_cast <char *> (&workingNode), nodeSize);

		if (searchNode(searchKey, index))
		{
			found = true;
			foundNode = workingNode.Key[index];
		}
		else
		{
			currentRoot = workingNode.charOffset[index + 1];
		}
	}
	return found;
}