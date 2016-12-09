#ifndef BTREEBLOCK_H_INCLUDED
#define BTREEBLOCK_H_INCLUDED

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
class BTreeBlock
{
private:
   vector<ItemType> block; // blco
   vector<int> children;
   int parentBlock, blockSize, lastFilePos;

public:
   BTreeBlock(const int& blockSize);  //default constructor

   /**
   @pre
   @post
   @param
   @return
   */

   void setParentBlock(const int& prntBlock);
   void setBlockItem(const ItemType& item);
   void setChildItem(const int& item);
   void setLastFilePos(const int& pos);
   int getParentBlock() const;
   int getBlockSize() const;
   int getChildrenVecSize() const;
   int getLastFilePos() const;
   ItemType getBlockItem(const ItemType& key) const;
   int getChildPos(const int& pos) const;
   vector<int> getChildVec () const;
   vector<ItemType> getBlock() const;
   void writeToFile(ostream& os, const Record& object, const int& pos);
   void writeEmptyBlock(ostream& os, int pos);
}; // end Node

template<class ItemType>
BTreeBlock<ItemType>::BTreeBlock(const int& blckSize)
{
    blockSize = blckSize;
} // end default constructor

template<class ItemType>
void BTreeBlock<ItemType>::writeEmptyBlock(ostream& os, int pos)
{
    string initKey = "-", initCharPos = "0";
    initKey.resize(4, '-');
    initCharPos.resize(8, '0');
    os.seekp(pos);

    for(int index = 0; index < blockSize; index++)
    {
        if (index == blockSize - 1)
            os << initKey << '|';
        else
            os << initKey << ',';
    }

    os << initCharPos << '^';

    for(int index = 0; index < blockSize; index++)
    {
        os << initCharPos << ':';
    }

    os << endl;
}

template<class ItemType>
void BTreeBlock<ItemType>::writeToFile(ostream& os, const Record& object, const int& pos)
{
    os.seekp(pos);

    os << object;
}

template<class ItemType>
void BTreeBlock<ItemType>::setParentBlock(const int& prntBlock)
{
    parentBlock = prntBlock;
}

template<class ItemType>
void BTreeBlock<ItemType>::setBlockItem(const ItemType& item)
{
    block.push_back(item);
}

template<class ItemType>
void BTreeBlock<ItemType>::setChildItem(const int& item)
{
    children.push_back(item);
}

template<class ItemType>
void BTreeBlock<ItemType>::setLastFilePos(const int& pos)
{
    lastFilePos = pos;
}

template<class ItemType>
int BTreeBlock<ItemType>::getParentBlock() const
{
    return parentBlock;
}

template<class ItemType>
int BTreeBlock<ItemType>::getLastFilePos() const
{
    return lastFilePos;
}

template<class ItemType>
ItemType BTreeBlock<ItemType>::getBlockItem(const ItemType& key) const
{
    for (int index = 0; index < block.size(); index++)
    {
        if(key == block[index])
            return block[index];
    }
}

template<class ItemType>
int BTreeBlock<ItemType>::getChildPos(const int& pos) const
{
    if(!children.empty())
        return children[pos];
}

template<class ItemType>
int BTreeBlock<ItemType>::getBlockSize() const
{
   return block.size();
}

template<class ItemType>
int BTreeBlock<ItemType>::getChildrenVecSize() const
{
   return children.size();
}

template<class ItemType>
vector<ItemType> BTreeBlock<ItemType>::getBlock() const
{
    return block;
}

template<class ItemType>
vector<int> BTreeBlock<ItemType>::getChildVec() const
{
    return children;
}

#endif // BTREEBLOCK_H_INCLUDED
