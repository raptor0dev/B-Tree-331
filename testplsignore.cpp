#include "btree.h"
#include <iostream>
//const int LineMax = KeyFieldMax +1 + DFMaxPlus1;
using namespace std;

void Read(ifstream & InputFile, KeyFieldType Word, DataFieldType Definition)
{
	InputFile.get(Word, KeyFieldMax+1);
	InputFile.get();
	InputFile.get(Definition, DataFieldMax+1);
	InputFile.get();
	//cout << "word " << Word << endl;
	//cout << "data " << Definition << endl;
	//cout << endl;
}

/* Given:  InputFile   A file stream already opened for input.
Task:   To read the data from InputFile and load it into the Table.
Return: Table       The B-tree table containing the data.
*/
void Load(ifstream & InputFile, BTTableClass & Table)
{
	ItemType Item;
	Read(InputFile, Item.KeyField, Item.DataField);

	while (!InputFile.fail())
	{
		Table.Insert(Item);
		Read(InputFile, Item.KeyField, Item.DataField);
	}
}

int main(void)
{
	ifstream sortedInput;
	BTTableClass BTTable('w', "superbtree.txt");

	sortedInput.open("testsort.txt", ios::in);
	if (sortedInput.fail())
	{
		cerr << "ERROR: Unable to open file btree.txt" << endl;
		exit(1);
	}
	Load(sortedInput, BTTable);
	sortedInput.close();
	BTTable.Dump();
	BTTable.printTreeRoot();

	int x;
	cin >> x;
	return 0;
}