#include "btree.h"
#include <iostream>
const int LineMax = KeyFieldMax + DFMaxPlus1;
using namespace std;
typedef char StringType[LineMax];


/* Given:  InputFile   A file stream already opened for input on a text file.
Task:   To read in a Word and its Definition from one line of this file.
Return: Word        In char array form, the word read in.
Definition  In char array form, the definition read in.
*/
void ReadLine(ifstream& InputFile, KeyFieldType Word,DataFieldType Definition)
{
	char Line[LineMax];
	int k, ch;

	InputFile.getline(Line, LineMax);   // will read the newline char

	for (k = 0; k < KeyFieldMax; k++)
		Word[k] = Line[k];
	Word[KeyFieldMax] = NULLCHAR;

	for (k = 0; k < DataFieldMax; k++)
	{
		ch = Line[KeyFieldMax + k];
		if (ch == '\n')
			break;
		Definition[k] = ch;
	}
	Definition[k] = NULLCHAR;
}


/* Given:  InputFile   A file stream already opened for input.
Task:   To read the data from InputFile and load it into the Table.
Return: Table       The B-tree table containing the data.
*/
void Load(ifstream & InputFile, BTTableClass & Table)
{
	ItemType Item;
	int Count;

	Count = 0;
	ReadLine(InputFile, Item.KeyField, Item.DataField);

	while (!InputFile.fail())
	{
		Table.Insert(Item);
		ReadLine(InputFile, Item.KeyField, Item.DataField);
	}
}


int main(void)
{
	ifstream Source;
	BTTableClass BTTable('w', "superbtree.txt");

	Source.open("inputFwdSort.txt", ios::in);
	//Source.open("btree.txt", ios::in);
	if (Source.fail())
	{
		cerr << "ERROR: Unable to open file btree.txt" << endl;
		exit(1);
	}

	Load(Source, BTTable);
	Source.close();
	BTTable.Dump();
	BTTable.printTreeRoot();
	int x;
	cin >> x;

	return 0;
}