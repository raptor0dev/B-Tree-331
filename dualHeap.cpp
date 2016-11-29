/**
@file dualHeap.cpp
@author Burg, Christopher N. Jesse Babcock Garrett Kamrath
Dayitwa Shrestha, Sanam Lama, Kapil Joshi
@date Monday, November 21, 2016
@version revision 1.2

@brief implementation file of dualHeap

*/

#include "dualHeap.h"
#include <string>
#include <sstream>

using namespace std;

dualHeap::dualHeap(const vector<Record> &vectorObj)
{
	for (int index = 0; index < vectorObj.size(); index++)
    {
        heaparray[index] = vectorObj[index];
    }
    heapDirection = true;	//true->active left end|false->active right end
	activeCount = SIZE;		//active heap size
	pendingCount = 0;		//pending heap size
	flipCount = 0;
	index = 0;

}

dualHeap::dualHeap()
{
	heapDirection = true;	//true->active left end|false->active right end
	activeCount = SIZE;		//active heap size
	pendingCount = 0;		//pending heap size
	flipCount = 0;
	index = 0;
}

array<Record, SIZE> dualHeap::getHeapArray() const
{
    return heaparray;
}

void dualHeap::Heapify()
{
	int length = activeCount;
	if (heapDirection == true)		//active root on left side
    {
        for (int i = length - 1; i >= 0; --i)
        {
            sortDown(i);
        }
    }
    else							//active root on right side
    {
        for (int i = heaparray.size() - length; i <= SIZE - 1; ++i)
        {
            sortDown(i);
        }
    }
}

void dualHeap::sortDown(int index)
{
	if (heapDirection == true)		//active root on left side
	{
		int length = activeCount;
		int leftChildIndex = 2 * index + 1;
		int rightChildIndex = 2 * index + 2;

		if (leftChildIndex >= length)
			return; //index is a leaf

		int minIndex = index;

        //RECOBJGETFIELD is a macro from type.h that does the following code based on compiler
        //option of INT or STRING
        //string: RECOBJGETFIELD = getName()
        //int: RECOBJGETFIELD = getIdNum()
		if (heaparray[index].RECOBJGETFIELD > heaparray[leftChildIndex].RECOBJGETFIELD) //comp
		{
			minIndex = leftChildIndex;
		}
		if ((rightChildIndex < length) && (heaparray[minIndex].RECOBJGETFIELD > heaparray[rightChildIndex].RECOBJGETFIELD)) //comp
		{
			minIndex = rightChildIndex;
		}
		if (minIndex != index)
		{
			//need to swap
			Record temp = heaparray[index];
			heaparray[index] = heaparray[minIndex];
			heaparray[minIndex] = temp;
			sortDown(minIndex);
		}

	}
	else							//active root on right side
	{
		int length = heaparray.size() - activeCount - 1;
		int leftChildIndex = (SIZE - 1) - ((2 * (heaparray.size() - 1 - index)) + 1);
		int rightChildIndex = (SIZE - 1) - ((2 * (heaparray.size() - 1 - index)) + 2);

		if (leftChildIndex <= length)
            return;
		int minIndex = index;

        //RECOBJGETFIELD is a macro from type.h that does the following code based on compiler
        //option of INT or STRING
        //string: RECOBJGETFIELD = getName()
        //int: RECOBJGETFIELD = getIdNum()
		if (heaparray[index].RECOBJGETFIELD > heaparray[leftChildIndex].RECOBJGETFIELD) //comp
		{
			minIndex = leftChildIndex;
		}

		if ((rightChildIndex > length) && (heaparray[minIndex].RECOBJGETFIELD > heaparray[rightChildIndex].RECOBJGETFIELD)) //comp
		{
			minIndex = rightChildIndex;
		}

		if (minIndex != index)
		{
			//need to swap
			Record temp = heaparray[index];
			heaparray[index] = heaparray[minIndex];
			heaparray[minIndex] = temp;
			sortDown(minIndex);
		}

	}
}

void dualHeap::sortUp(int index)
{
	if (heapDirection == true)		//active root on left side
	{
		if (index >= activeCount)	//pending side
		{
			if (index == heaparray.size()-1)
				return;

            //RECOBJGETFIELD is a macro from type.h that does the following code based on compiler
            //option of INT or STRING
            //string: RECOBJGETFIELD = getName()
            //int: RECOBJGETFIELD = getIdNum()
			int parentIndex = index + (int)ceil(((heaparray.size() - index) / 2));

			if (heaparray[parentIndex].RECOBJGETFIELD > heaparray[index].RECOBJGETFIELD) //comp
			{
				Record temp = heaparray[parentIndex];
				heaparray[parentIndex] = heaparray[index];
				heaparray[index] = temp;
				sortUp(parentIndex);
			}
		}
		else					//active side
		{
			if (index == 0)
				return;
			int parentIndex = (index - 1) / 2;

			if (heaparray[parentIndex].RECOBJGETFIELD > heaparray[index].RECOBJGETFIELD) //comp
			{
				Record temp = heaparray[parentIndex];
				heaparray[parentIndex] = heaparray[index];
				heaparray[index] = temp;
				sortUp(parentIndex);
			}
		}
	}
	else							//active root on right side
	{
		if (index <= (pendingCount - 1))
		{                                   //pending side
			if (index == 0)
                return;

			int parentIndex = (index - 1) / 2;

			if (heaparray[parentIndex].RECOBJGETFIELD > heaparray[index].RECOBJGETFIELD) //comp
			{
				Record temp = heaparray[parentIndex];
				heaparray[parentIndex] = heaparray[index];
				heaparray[index] = temp;
				sortUp(parentIndex);
			}
		}
		else						//active side
		{
			if (index == heaparray.size() - 1)
                return;

			int parentIndex = index + (int)ceil(((heaparray.size() - index) / 2));

			if (heaparray[parentIndex].RECOBJGETFIELD > heaparray[index].RECOBJGETFIELD) //comp
			{
				Record temp = heaparray[parentIndex];
				heaparray[parentIndex] = heaparray[index];
				heaparray[index] = temp;
				sortUp(parentIndex);
			}
		}
	}
}

void dualHeap::active_heap_push(const Record &pushValue)
{
    if (heapDirection == true)		//active root on left side
    {
        int length = activeCount;
        heaparray[length - 1] = pushValue;
    }
    else							//active root on right side
    {
        int length = activeCount;
        heaparray[heaparray.size() - length] = pushValue;
    }
}

void dualHeap::pending_heap_push(const Record &pushValue)
{
	activeCount--;
	pendingCount++;
    if (heapDirection == true)		//active root on left side
    {
        int length = pendingCount;
        heaparray[heaparray.size() - length] = pushValue;
        sortUp(heaparray.size() - length);
    }
    else							//active root on right side
    {
        int length = pendingCount;
        heaparray[length - 1] = pushValue;
        sortUp(length - 1);
    }
}

Record dualHeap::getRoot()
{
	if (heapDirection == true)		//active root on left side
	{
		return heaparray[0];
	}
	else							//active root on right side
	{
		return heaparray[heaparray.size() - 1];
	}
}

void dualHeap::active_heap_pop()
{
	int length = activeCount;

	if (length == 0)				//root is a leaf
	{
		return;
	}
	if (heapDirection == true)		//active root on left side
	{
		heaparray[0] = heaparray[length - 1];
	}
	else							//active root on right side
	{
		heaparray[heaparray.size() - 1] = heaparray[heaparray.size() - length];
	}
}

void dualHeap::printHeap()
{
	cout << endl;
	cout << "heap contents" << endl;
	for (int i = 0; i < heaparray.size(); i++)
	{
		cout << " " << heaparray[i];
	}
	cout << endl;
	cout << "detailed heap contents" << endl;
	if (heapDirection == true)
	{
		cout << "active contents" << endl;
		for (int i = 0; i < activeCount; i++)
		{
			cout << " " << heaparray[i];
		}
		cout << endl;
		cout << "pending contents" << endl;
		for (int j = 0; j < pendingCount; j++)
		{
			cout << " " << heaparray[heaparray.size() - j - 1];
		}
		cout << endl;
	}
	else
	{
		cout << "active contents" << endl;
		for (int i = 0; i < activeCount; i++)
		{
			cout << " " << heaparray[heaparray.size() - i - 1];
		}
		cout << endl;
		cout << "pending contents" << endl;
		for (int j = 0; j < pendingCount; j++)
		{
			cout << " " << heaparray[j];
		}
		cout << endl;
	}
	cout << endl;
}

void dualHeap::printHeapToFile(ofstream &logfile)
{
	logfile << endl;
	logfile << "heap contents" << endl;
	for (int i = 0; i < heaparray.size(); i++)
	{
		logfile << " " << heaparray[i];
	}
	logfile << endl;
	logfile << "detailed heap contents" << endl;
	if (heapDirection == true)
	{
		logfile << "active contents" << endl;
		for (int i = 0; i < activeCount; i++)
		{
			logfile << " " << heaparray[i];
		}
		logfile << endl;
		logfile << "pending contents" << endl;
		for (int j = 0; j < pendingCount; j++)
		{
			logfile << " " << heaparray[heaparray.size() - j - 1];
		}
		logfile << endl;
	}
	else
	{
		logfile << "active contents" << endl;
		for (int i = 0; i < activeCount; i++)
		{
			logfile << " " << heaparray[heaparray.size() - i - 1];
		}
		logfile << endl;
		logfile << "pending contents" << endl;
		for (int j = 0; j < pendingCount; j++)
		{
			logfile << " " << heaparray[j];
		}
		logfile << endl;
	}
	logfile << endl;
}

void dualHeap::directionFlip()
{
	if (heapDirection == true)
	{
		heapDirection = false;
	}
	else
	{
		heapDirection = true;
	}

	activeCount = SIZE;
	pendingCount = 0;
	flipCount++;
}

int dualHeap::getActiveCount() const
{
	return activeCount;
}

int dualHeap::getPendingCount() const
{
	return pendingCount;
}

void dualHeap::setActiveCount(const int &activeVal)
{
    activeCount = activeVal;
}

void dualHeap::setPendingCount(const int &pendingVal)
{
    pendingCount = pendingVal;
}

int dualHeap::getFlipCount() const
{
    return flipCount;
}
