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
   vector<ItemType> block; //
   vector<int> children;
   int prevBlock, nextBlock, parentBlock, blockSize;
   int availList, sequenceHead, bTreeHead;

public:
   SequenceSet(ostream& os, const int& blockSize);  //default constructor

   /**Set item
   @pre anItem must be passed
   @post sets item equal to anItem
   @param anItem is data to be stored
   */
   void setPosition(ostream& os, string Value, int offSet, string Type);
   void setAvailList(ostream& os, string availValue);
   void setSequenceHead(ostream& os, string seqHead);
   void setBTreeHead(ostream& os, string bTHead);
   void setPrevBlock(const int& prvBlock);
   void setNextBlock(const int& nxtBlock);
   void setParentBlock(const int& prntBlock);
   void setBlockItem(const ItemType& item);
   void setChildItem(const int& item);
   int getAvailList() const;
   int getSequenceHead() const;
   int getBTreeHead() const;
   int getPrevBlock() const;
   int getNextBlock() const;
   int getParentBlock() const;
   int getBlockSize() const;
   int getChildrenVecSize() const;
   ItemType getBlockItem(const ItemType& key, const string& type) const;
   Record getBlockRecord(const int& pos) const;
   int getChildPos(const int& pos) const;
   vector<int> getChildVec () const;
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
    os << initInt << ',' << initInt << ',' << initInt << '|';
    writeEmptyBlock(os, 28);
} // end default constructor

template<class ItemType>
void SequenceSet<ItemType>::writeEmptyBlock(ostream& os, int pos)
{
    int charPos = pos;
    string initString = "-", initInt = "0", initCharPos = "0";
    initString.resize(4, '-');
    initInt.resize(4, '0');
    initCharPos.resize(8, '0');

    for(int index = 0; index < blockSize; index++)
    {
        os.seekp(charPos);
        os << initString << ',' << initInt << '|';
        charPos += 10;
    }

    os << initCharPos << '^' << initCharPos << '<' << initCharPos << '>';
}

template<class ItemType>
void SequenceSet<ItemType>::writeToFile(ostream& os, const Record& object, const int& pos)
{
    os.seekp(pos);
    os << object;
}

/*
template<class ItemType>
SequenceSet<ItemType>::SequenceSet(const ItemType& anItem) : item(anItem),
                 next(NULL), prev(NULL)
{
} // end constructor

template<class ItemType>
SequenceSet<ItemType>::SequenceSet(const ItemType& anItem, SequenceSet<ItemType>* nextNodePtr,
                 SequenceSet<ItemType>* prevNodePtr) : item(anItem), next(nextNodePtr),
                 prev(prevNodePtr)
{
} // end constructor
*/
template<class ItemType>
void SequenceSet<ItemType>::setPosition(ostream& os, string Value, int offSet, string Type)
{
    string temp;
    temp = Value;
    string tempzero;
    int strsize = 8 - temp.length();

    if(Type ==  "Parent")
    {
        if(strsize !=0)
        {
            for(int i =0; i < strsize; i++)
            {
                tempzero += "0";
            }
        }
        temp = tempzero + temp;
        os.seekp(offSet);
        os << temp;
    }
    else if(Type == "Next")
    {
        if(strsize !=0)
        {
            for(int i =0; i < strsize; i++)
            {
                tempzero += "0";
            }
        }
        temp = tempzero + temp;
        os.seekp(offSet);
        os << temp;
    }
    else if(Type == "Prev")
    {
        if(strsize !=0)
        {
            for(int i =0; i < strsize; i++)
            {
                tempzero += "0";
            }
        }
        temp = tempzero + temp;
        os.seekp(offSet);
        os << temp;
    }
    else if(Type == "Avail")
    {
        availList = atoi(Value.c_str());
        if(strsize !=0)
        {
            for(int i =0; i < strsize; i++)
            {
                tempzero += "0";
            }
        }
        temp = tempzero + temp;
        os.seekp(offSet);
        os << temp;
    }

    else if(Type == "SeqSet")
    {
        sequenceHead = atoi(Value.c_str());
        if(strsize !=0)
        {
            for(int i =0; i < strsize; i++)
            {
                tempzero += "0";
            }
        }
        temp = tempzero + temp;
        os.seekp(offSet);
        os << temp;
    }

    else if(Type == "BTree")
    {
        bTreeHead = atoi(Value.c_str());
        if(strsize !=0)
        {
            for(int i =0; i < strsize; i++)
            {
                tempzero += "0";
            }
        }
        temp = tempzero + temp;
        os.seekp(offSet);
        os << temp;
    }

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
void SequenceSet<ItemType>::setChildItem(const int& item)
{
    children.push_back(item);
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
int SequenceSet<ItemType>::getChildPos(const int& pos) const
{
    if(!children.empty())
        return children[pos];
}

template<class ItemType>
int SequenceSet<ItemType>::getBlockSize() const
{
   return block.size();
}

template<class ItemType>
int SequenceSet<ItemType>::getChildrenVecSize() const
{
   return children.size();
}

template<class ItemType>
vector<ItemType> SequenceSet<ItemType>::getBlock() const
{
    return block;
}

template<class ItemType>
vector<int> SequenceSet<ItemType>::getChildVec() const
{
    return children;
}
//#include "SequenceSet.cpp"

#endif // SEQUENCESET_H_INCLUDED
