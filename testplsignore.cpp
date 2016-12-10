#include "btree.h"
#include <iostream>
using namespace std;

void read(ifstream & sequenceSet, KeyFieldType key, DataFieldType field2)
{
	sequenceSet.get(key, KeyFieldMax+1);
	sequenceSet.get();
	sequenceSet.get(field2, DataFieldMax+1);
	sequenceSet.get();
	//cout << "word " << Word << endl;
	//cout << "data " << Definition << endl;
	//cout << endl;
}

/* Given:  InputFile   A file stream already opened for input.
Task:   To read the data from InputFile and load it into the Table.
Return: Table       The B-tree table containing the data.
*/
/**
* @brief builds the tree from a sorted input file.
* @pre have 
* @post builds the entire B+ tree
* @param sequenceSet The file to build the tree from
* @param tree The BTree object to build into
* @return void
*/
void loadTree(ifstream & sequenceSet,BTree & tree)
{
	ItemType Item;
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