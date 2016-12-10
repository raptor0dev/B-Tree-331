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

template<class itemType>
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
   void setBlockItem(const itemType& item);
   int getAvailList() const;
   int getSequenceHead() const;
   int getBTreeHead() const;
   int getPrevBlock() const;
   int getNextBlock() const;
   int getParentBlock() const;
   int getBlockSize() const;
   itemType getBlockItem(const itemType& key, const string& type) const;
   Record getBlockRecord(const int& pos) const;
   vector<itemType> getBlock() const;
   void writeToFile(ostream& os, const Record& object, const int& pos);
   void writeEmptyBlock(ostream& os, int pos);
}; // end Node

template<class itemType>
SequenceSet<itemType>::SequenceSet(ostream& os, const int& blckSize)
{
    blockSize = blckSize;
    string initInt = "0";
    initInt.resize(8, '0');
    os.seekp(0);
    os << initInt << ',' << initInt << ',' << initInt << '|' << endl;
    writeEmptyBlock(os, os.tellp());
} // end default constructor

template<class itemType>
void SequenceSet<itemType>::writeEmptyBlock(ostream& os, int pos)
{
    string initString = "-", initInt = "0", initCharPos = "0";
    initString.resize(4, '-');
    initInt.resize(4, '0');
    initCharPos.resize(8, '0');
    os.seekp(pos);

    for(int index = 0; index <= blockSize; index++)
    {
        os << initString << "," << initInt << "|";
    }
    os << initCharPos << '^' << initCharPos << '<' << initCharPos << '>' << "00#" << endl;
}

template<class itemType>
void SequenceSet<itemType>::writeToFile(ostream& os, const Record& object, const int& pos)
{
    os.seekp(pos);
    os << object;
}

template<class itemType>
void SequenceSet<itemType>::setAvailList(ostream& os, string availValue)
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

template<class itemType>
void SequenceSet<itemType>::setSequenceHead(ostream& os, string seqHead)
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


template<class itemType>
void SequenceSet<itemType>::setBTreeHead(ostream& os, string bTHead)
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

template<class itemType>
void SequenceSet<itemType>::setPrevBlock(const int& prvBlock)
{
   prevBlock = prvBlock;
}

template<class itemType>
void SequenceSet<itemType>::setNextBlock(const int& nxtBlock)
{
    nextBlock = nxtBlock;
}

template<class itemType>
void SequenceSet<itemType>::setParentBlock(const int& prntBlock)
{
    parentBlock = prntBlock;
}

template<class itemType>
void SequenceSet<itemType>::setBlockItem(const itemType& item)
{
    block.push_back(item);
}

template<class itemType>
int SequenceSet<itemType>::getAvailList() const
{
   return availList;
}

template<class itemType>
int SequenceSet<itemType>::getSequenceHead() const
{
   return sequenceHead;
}

template<class itemType>
int SequenceSet<itemType>::getBTreeHead() const
{
   return bTreeHead;
}

template<class itemType>
int SequenceSet<itemType>::getPrevBlock() const
{
    return prevBlock;
}

template<class itemType>
int SequenceSet<itemType>::getNextBlock() const
{
    return nextBlock;
}

template<class itemType>
int SequenceSet<itemType>::getParentBlock() const
{
    return parentBlock;
}

template<class itemType>
itemType SequenceSet<itemType>::getBlockItem(const itemType& key, const string& type) const
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

template<class itemType>
Record SequenceSet<itemType>::getBlockRecord(const int& pos) const
{
    return block[pos];
}


template<class itemType>
int SequenceSet<itemType>::getBlockSize() const
{
   return block.size();
}

template<class itemType>
vector<itemType> SequenceSet<itemType>::getBlock() const
{
    return block;
}

#endif // SEQUENCESET_H_INCLUDED
