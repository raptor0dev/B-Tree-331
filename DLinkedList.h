//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** ADT list: Link-based implementation.
    Listing 9-2.
    @file DLinkedList.h */

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "ListInterface.h"
#include "DNode.h"
#include "PrecondViolatedExcep.h"
#include "Record.h"
#include "type.h"
#include <cassert>

#define nullptr NULL

using namespace std;

template<class ItemType>
class DLinkedList// : public ListInterface<ItemType>
{
private:
   DNode<ItemType>* headPtr; // Pointer to first DNode in the chain;
                            // (contains the first entry in the list)
   int itemCount;           // Current count of list items

   // Locates a specified DNode in this linked list.
   // @pre  position is the number of the desired DNode;
   //       position >= 1 and position <= itemCount.
   // @post  The DNode is found and a pointer to it is returned.
   // @param position  The number of the DNode to locate.
   // @return  A pointer to the DNode at the given position.
   DNode<ItemType>* getDNodeAt(int position) const;

public:
   DLinkedList();
   DLinkedList(const DLinkedList<ItemType>& aList);
   //~DLinkedList();

   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType& newEntry);
   bool remove(int position);
   void clear();
   bool addItemToBlock(int newPosition, const Record& newRecord);
   bool removeItemFromBlock(ItemType Key);

   /** @throw PrecondViolatedExcep if position < 1 or
                                      position > getLength(). */
   ItemType getEntry(int position) const throw(PrecondViolatedExcep);

   /** @throw PrecondViolatedExcep if position < 1 or
                                      position > getLength(). */
   void setEntry(int position, const ItemType& newEntry)
                               throw(PrecondViolatedExcep);
}; // end DLinkedList

template<class ItemType>
DLinkedList<ItemType>::DLinkedList() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
DLinkedList<ItemType>::DLinkedList(const DLinkedList<ItemType>& aList) : itemCount(aList.itemCount)
{
   DNode<ItemType>* origChainPtr = aList.headPtr;  // Points to DNodes in original chain

   if (origChainPtr == nullptr)
      headPtr = nullptr;  // Original list is empty
   else
   {
      // Copy first DNode
      headPtr = new DNode<ItemType>();
      headPtr->setItem(origChainPtr->getItem());

      // Copy remaining DNodes
      DNode<ItemType>* newChainPtr = headPtr;     // Points to last DNode in new chain
      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();

         // Create a new DNode containing the next item
         DNode<ItemType>* newDNodePtr = new DNode<ItemType>(nextItem);

         // Link new DNode to end of new chain
         newChainPtr->setNext(newDNodePtr);

         // Advance pointer to new last DNode
         newChainPtr = newChainPtr->getNext();
         origChainPtr = origChainPtr->getNext();
      }  // end while

      newChainPtr->setNext(nullptr);           // Flag end of chain
   }  // end if
}  // end copy constructor

/*template<class ItemType>
DLinkedList<ItemType>::~DLinkedList()
{
   clear();
}  // end destructor*/

template<class ItemType>
bool DLinkedList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int DLinkedList<ItemType>::getLength() const
{
   return itemCount;
}  // end getLength

template<class ItemType>
bool DLinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
   if (ableToInsert)
   {
      // Create a new DNode containing the new entry
      DNode<ItemType>* newDNodePtr = new DNode<ItemType>(newEntry);

      // Attach new DNode to chain
      if (newPosition == 1)
      {
         // Insert new DNode at beginning of chain
         newDNodePtr->setNext(headPtr);
         //newDNodePtr->setPrev(nullptr);
         if (itemCount != 0)
            headPtr->setPrev(newDNodePtr);
         headPtr = newDNodePtr;
      }
      else
      {
         // Find DNode that will be before new DNode
         DNode<ItemType>* tempPtr = getDNodeAt(newPosition - 1);

         // Insert new DNode after DNode to which tempPtr points
         newDNodePtr->setNext(tempPtr->getNext());
         newDNodePtr->setPrev(tempPtr);
         tempPtr->setNext(newDNodePtr);

         tempPtr = newDNodePtr->getNext();
         if (newDNodePtr->getNext() != nullptr)
            tempPtr->setPrev(newDNodePtr);
      }  // end if

      itemCount++;  // Increase count of entries
   }  // end if

   return ableToInsert;
}  // end insert

template<class ItemType>
bool DLinkedList<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      DNode<ItemType>* curPtr = nullptr;
      if (position == 1)
      {
         // Remove the first DNode in the chain
         curPtr = headPtr; // Save pointer to DNode
         headPtr = headPtr->getNext();
         //headPtr->setPrev(nullptr);
      }
      else
      {
         // Find DNode that is before the one to delete
         DNode<ItemType>* prevPtr = getDNodeAt(position - 1);

         // Point to DNode to delete
         curPtr = prevPtr->getNext();
         DNode<ItemType>* nextNodePtr = curPtr->getNext();
         // Disconnect indicated DNode from chain by connecting the
         // prior DNode with the one after

         prevPtr->setNext(curPtr->getNext());
         nextNodePtr->setPrev(curPtr->getPrev());

      }  // end if

      // Return DNode to system
      curPtr->setNext(nullptr);
      curPtr->setPrev(nullptr);
      delete curPtr;
      curPtr = nullptr;

      itemCount--;  // Decrease count of entries
   }  // end if

   return ableToRemove;
}  // end remove

template<class ItemType>
void DLinkedList<ItemType>::clear()
{
   while (!isEmpty())
      remove(1);
}  // end clear

template<class ItemType>
ItemType DLinkedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      DNode<ItemType>* DNodePtr = getDNodeAt(position);
      return DNodePtr->getItem();
   }
   else
   {
      string message = "getEntry() called with an empty list or ";
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message));
   }  // end if
}  // end getEntry

template<class ItemType>
void DLinkedList<ItemType>::setEntry(int position, const ItemType& newEntry) throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
      DNode<ItemType>* DNodePtr = getDNodeAt(position);
      DNodePtr->setItem(newEntry);
   }
   else
   {
      string message = "setEntry() called with an invalid position.";
      throw(PrecondViolatedExcep(message));
   }  // end if
}  // end setEntry

template<class ItemType>
DNode<ItemType>* DLinkedList<ItemType>::getDNodeAt(int position) const
{
   // Debugging check of precondition
   assert( (position >= 1) && (position <= itemCount) );

   // Count from the beginning of the chain
   DNode<ItemType>* curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
      curPtr = curPtr->getNext();

   return curPtr;
}  // end getDNodeAt

//#include "DLinkedList.cpp"
#endif
