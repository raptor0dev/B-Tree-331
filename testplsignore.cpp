#include "btree.h"
#include <iostream>
using namespace std;

/**
* @brief reads in a record from the file
* @pre have a file to read in.
* @post prepares a nodes contents
* @param sequenceSet The file to build the tree from
* @param key the value it sorts by
* @param field2 the other field.
* @return void
*/
void read(ifstream & sequenceSet, keyType key, dataType field2)
{
	sequenceSet.get(key, keySize+1);
	sequenceSet.get();
	sequenceSet.get(field2, dataSize+1);
	sequenceSet.get();
}

/**
* @brief builds the tree from a sorted input file.
* @pre have a file to read in.
* @post builds the entire B+ tree
* @param sequenceSet The file to build the tree from
* @param tree The BTree object to build into
* @return void
*/
void loadTree(ifstream & sequenceSet,BTree & tree)
{
	itemType Item;
	read(sequenceSet, Item.KeyField, Item.DataField);

	while (!sequenceSet.fail())
	{
		tree.insert(Item);
		read(sequenceSet, Item.KeyField, Item.DataField);
	}
}

int main(void)
{
	ifstream sortedInput;
	BTree mainTree('w', "outputTree.txt");

	sortedInput.open("testsort.txt", ios::in);
	if (sortedInput.fail())
	{
		cout << "Error: unable to open file btree.txt" << endl;
		exit(1);
	}
	loadTree(sortedInput, mainTree);
	sortedInput.close();
	mainTree.dump();

	int x;
	cin >> x;
	return 0;
}