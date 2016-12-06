/**@file DNode.h
Specification file for DNode class*/

#ifndef DNODE_H
#define DNODE_H

#include <cstddef>
#include "Record.h"
#include "type.h"

using namespace std;

template<class ItemType>
class DNode
{
private:
   //ItemType        item; // A data item
   vector<ItemType> block;
   int prevBlock,nextBlock, parentBlock;

   DNode<ItemType>* next; // Pointer to next node
   DNode<ItemType>* prev;

public:
   DNode();  //default constructor
   //DNode(const ItemType& anItem);  //parameterized constructor
   //DNode(const ItemType& anItem, DNode<ItemType>* nextNodePtr,
         //DNode<ItemType>* prevNodePtr);  //parameterized constructor

   /**Set item
   @pre anItem must be passed
   @post sets item equal to anItem
   @param anItem is data to be stored
   */
   void setItem(const ItemType& anItem);

   /**Set next
   @pre nextNodePtr must be passed
   @post sets next equal to nextNodePtr
   @param nextNodePtr is pointer to be stored
   */
   void setNext(DNode<ItemType>* nextNodePtr);

   /**Set prev
   @pre prevNodePtr must be passed
   @post sets prev equal to  prevNodePtr
   @param prevNodePtr is pointer to be stored
   @return
   */
   void setPrev(DNode<ItemType>* prevNodePtr);

   /**Returns item
   @post gets item
   @return item is returned
   */
   ItemType getItem() const;

   /**Returns pointer to next node
   @post gets next
   @return next is returned as pointer to next node
   */
   DNode<ItemType>* getNext() const;

   /**Returns pointer to previous node
   @post gets prev
   @return prev is returned as pointer to previous node
   */
   DNode<ItemType>* getPrev() const;

   void setPrevBlock(const int& prvBlock);
   void setNextBlock(const int& nxtBlock);
   void setParent(const int& prntBlock);
   void setBlockItem(const ItemType& item);
   int getPrevBlock() const;
   int getNextBlock() const;
   int getParentBlock() const;
   int getBlockSize() const;
   ItemType getBlockItem(const ItemType& key) const;
   vector<ItemType> getBlock() const;


}; // end Node



template<class ItemType>
DNode<ItemType>::DNode() : next(NULL), prev(NULL)
{
} // end default constructor

/*
template<class ItemType>
DNode<ItemType>::DNode(const ItemType& anItem) : item(anItem),
                 next(NULL), prev(NULL)
{
} // end constructor

template<class ItemType>
DNode<ItemType>::DNode(const ItemType& anItem, DNode<ItemType>* nextNodePtr,
                 DNode<ItemType>* prevNodePtr) : item(anItem), next(nextNodePtr),
                 prev(prevNodePtr)
{
} // end constructor
*/

template<class ItemType>
void DNode<ItemType>::setItem(const ItemType& anItem)
{
   item = anItem;
   //block.push_back(anItem);
} // end setItem

template<class ItemType>
void DNode<ItemType>::setNext(DNode<ItemType>* nextNodePtr)
{
   next = nextNodePtr;
} // end setNext

template<class ItemType>
void DNode<ItemType>::setPrev(DNode<ItemType>* prevNodePtr)
{
   prev = prevNodePtr;
} // end setNext

template<class ItemType>
ItemType DNode<ItemType>::getItem(int position) const
{
   return item;
   //return vector<position>;
} // end getItem

template<class ItemType>
DNode<ItemType>* DNode<ItemType>::getNext() const
{
   return next;
}

template<class ItemType>
DNode<ItemType>* DNode<ItemType>::getPrev() const
{
   return prev;
}

template<class ItemType>
void DNode<ItemType>::setPrevBlock(const int& prvBlock)
{

}

template<class ItemType>
void DNode<ItemType>::setNextBlock(const int& nxtBlock)
{

}

template<class ItemType>
void DNode<ItemType>::setParent(const int& prntBlock)
{

}

template<class ItemType>
void DNode<ItemType>::setBlockItem(const ItemType& item)
{

}

template<class ItemType>
int DNode<ItemType>::getPrevBlock() const
{

}

template<class ItemType>
int DNode<ItemType>::getNextBlock() const

template<class ItemType>
int DNode<ItemType>::getParentBlock() const

template<class ItemType>
int DNode<ItemType>::getBlockSize() const

template<class ItemType>
ItemType DNode<ItemType>::getBlockItem(const ItemType& key) const


template<class ItemType>
int DNode<ItemType>::getBlockSize() const
{
   return block.size();
} // end setNext

//#include "DNode.cpp"
#endif // DNODE_H
