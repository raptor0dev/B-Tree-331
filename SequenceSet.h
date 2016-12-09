#ifndef SEQUENCESET_H_INCLUDED
#define SEQUENCESET_H_INCLUDED

//#include <cstddef>
//#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "Record.h"
#include "type.h"

using namespace std;

template<class ItemType>
class SequenceSet
{
private:
   vector<Record> block; // blco
   int prevBlock, nextBlock, parentBlock, blockSize, lastFilePos;
   int availList, sequenceHead, bTreeHead;

public:
   SequenceSet(ostream& os, const int& blockSize);  //default constructor

   /**
   @pre
   @post
   @param
   @return
   */

   void setAvailList(ostream& os, string availValue);
   void setSequenceHead(ostream& os, string seqHead);
   void setBTreeHead(ostream& os, string bTHead);
   void setPrevBlock(const int& prvBlock);
   void setNextBlock(const int& nxtBlock);
   void setParentBlock(const int& prntBlock);
   void setBlockItem(const ItemType& item);
   int getAvailList() const;
   int getSequenceHead() const;
   int getBTreeHead() const;
   int getPrevBlock() const;
   int getNextBlock() const;
   int getParentBlock() const;
   int getBlockSize() const;
   ItemType getBlockItem(const ItemType& key, const string& type) const;
   Record getBlockRecord(const int& pos) const;
   vector<ItemType> getBlock() const;
   void writeToFile(ostream& os, const Record& object, const int& pos);
   void writeEmptyBlock(ostream& os, int pos);
}; // end Node

template<class ItemType>
SequenceSet<ItemType>::SequenceSet(ostream& os, const int& blckSize)
{
    blockSize = blckSize;
    string initInt = "0";
    initInt.resize(8, '0');
    os.seekp(0);
    os << initInt << ',' << initInt << ',' << initInt << '|' << endl;
    writeEmptyBlock(os, os.tellp());
} // end default constructor

template<class ItemType>
void SequenceSet<ItemType>::writeEmptyBlock(ostream& os, int pos)
{
    string initString = "-", initInt = "0", initCharPos = "0";
    initString.resize(4, '-');
    initInt.resize(4, '0');
    initCharPos.resize(8, '0');
    os.seekp(pos);

    for(int index = 0; index < blockSize; index++)
    {
        os << initString << "," << initInt << "|";
    }
    os << initCharPos << '^' << initCharPos << '<' << initCharPos << '>' << endl;
}

template<class ItemType>
void SequenceSet<ItemType>::writeToFile(ostream& os, const Record& object, const int& pos)
{
    os.seekp(pos);
    os << object;
}

template<class ItemType>
void SequenceSet<ItemType>::setAvailList(ostream& os, string availValue)
{
   string temp;
   temp = availValue;
   availList = atoi(availValue.c_str());
   int strsize = 8 - temp.length();
   string tempzero;
   if(strsize !=0)
   {
       for(int i =0; i < strsize; i++)
       {
           tempzero += "0";
       }
   }
   temp = tempzero + temp;
   os.seekp(0);
   os << temp;
   //cout << temp << endl;
}

template<class ItemType>
void SequenceSet<ItemType>::setSequenceHead(ostream& os, string seqHead)
{

   string temp;
   temp = seqHead;
   sequenceHead = atoi(seqHead.c_str());
   int strsize = 8 - temp.length();
   string tempzero;
   if(strsize !=0)
   {
       for(int i =0; i < strsize; i++)
       {
           tempzero += "0";
       }
   }
   temp = tempzero + temp;
   os.seekp(9);
   os << temp;
   //cout << temp << endl;
}


template<class ItemType>
void SequenceSet<ItemType>::setBTreeHead(ostream& os, string bTHead)
{
   string temp;
   temp = bTHead;
   bTreeHead = atoi(bTHead.c_str());
   int strsize = 8 - temp.length();
   string tempzero;
   if(strsize !=0)
   {
       for(int i =0; i < strsize; i++)
       {
           tempzero += "0";
       }
   }
   temp = tempzero + temp;
   os.seekp(18);
   os << temp;
   //cout << temp << endl;
}

template<class ItemType>
void SequenceSet<ItemType>::setPrevBlock(const int& prvBlock)
{
   prevBlock = prvBlock;
}

template<class ItemType>
void SequenceSet<ItemType>::setNextBlock(const int& nxtBlock)
{
    nextBlock = nxtBlock;
}

template<class ItemType>
void SequenceSet<ItemType>::setParentBlock(const int& prntBlock)
{
    parentBlock = prntBlock;
}

template<class ItemType>
void SequenceSet<ItemType>::setBlockItem(const ItemType& item)
{
    block.push_back(item);
}

template<class ItemType>
int SequenceSet<ItemType>::getAvailList() const
{
   return availList;
}

template<class ItemType>
int SequenceSet<ItemType>::getSequenceHead() const
{
   return sequenceHead;
}

template<class ItemType>
int SequenceSet<ItemType>::getBTreeHead() const
{
   return bTreeHead;
}

template<class ItemType>
int SequenceSet<ItemType>::getPrevBlock() const
{
    return prevBlock;
}

template<class ItemType>
int SequenceSet<ItemType>::getNextBlock() const
{
    return nextBlock;
}

template<class ItemType>
int SequenceSet<ItemType>::getParentBlock() const
{
    return parentBlock;
}

template<class ItemType>
ItemType SequenceSet<ItemType>::getBlockItem(const ItemType& key, const string& type) const
{
    for (int index = 0; index < block.size(); index++)
    {
        if (type == "key")
        {
            if(key == block[index])
            {
                return block[index];
            }
        }
        else if(type == "record")
        {
            if(key == block[index].RECOBJGETFIELD)
            {
                return block[index];
            }
        }
        else
            cout << "Invalid parameter" << endl;
    }
}

template<class ItemType>
Record SequenceSet<ItemType>::getBlockRecord(const int& pos) const
{
    return block[pos];
}


template<class ItemType>
int SequenceSet<ItemType>::getBlockSize() const
{
   return block.size();
}

template<class ItemType>
vector<ItemType> SequenceSet<ItemType>::getBlock() const
{
    return block;
}

#endif // SEQUENCESET_H_INCLUDED
