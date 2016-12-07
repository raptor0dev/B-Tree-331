/**
@file main.cpp
@author jesse babcock Garrett Kamrath Burg, Christopher N.
Dayitwa Shrestha, Sanam Lama, Kapil Joshi
@date Monday, November 14, 2016
@version revision 1.1

@brief main.cpp coordinates entire program

@details
Main.cpp coordinates the execution of Record.cpp, Record.h, type.h
CreateInputFile.h, dualHeap.h, and dualHeap.cpp. The first part asks the user what input
file they would like to use. Forward sort, backward sort, partial sort, or random input creates
a random number of fixed length records controlled by NUM_OF_RECORDS into input.txt. The
records from this file are added to a min heap that creates sorted runs within
sortedrun.txt. This file is passed into a priority queue that does a k way tournament
that sorts everything into ascending order in sorted.txt. The data type to sort is
based on a compile time option of INT or STRING that uses macros in type.h to replace
sections of code. A log of statistics is output to log.txt. Various statements are
displayed to the console indicating execution of the program.
*/

#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <array>
#include <vector>
#include <time.h> //for random generated input file and execution time
#include <queue>
#include "Record.h"   //include to create record obj and file ops
#include "CreateInputFile.h" //include to create input file
#include "dualHeap.h"  //include for dual heap
#include "type.h"   //macros that replace sections of code based on data type
#include "DNode.h"
#include "DLinkedList.h"
//#include <PrecondViolatedExcep.h>

using namespace std;

clock_t tStart = clock(); //keep track of execution time
int found = 0, charPos = 0, numOfBytes = 0, writtenRecords = 0, writtenRecords2 = 0, runSizeIndex = 0;
Record oldRec; //last written record
vector<int> sortedRunPos; //vector to store starting positions of each run
vector<int> runSize;    //# of records in each run

/** @brief store char positions of sorted runs
 * @pre
 * @post position of sorted run if new list is made
 * @param newRec last written record to file sortedrun.txt of type record
 *
 * @return int returns 1 if found new run else 0
 */
int sortedRunUpdate(const Record & newRec)
{

    int foundList = 0;
    //RECOBJGETFIELD is a macro from type.h that does the following code based on compiler
    //option of INT or STRING
    //string: RECOBJGETFIELD = getName()
    //int: RECOBJGETFIELD = getIdNum()
    if (oldRec.RECOBJGETFIELD > newRec.RECOBJGETFIELD)
    {
        sortedRunPos.push_back(charPos);
        foundList = 1;
    }
    return foundList;
}

/** @brief keep track of various stats
 *
 * @param poppedRecVar last popped rec from minheap of type record
 * @return void
 *
 */
void updateStats(const Record &poppedRecVar)
{
    if(writtenRecords > 0)
        found = sortedRunUpdate(poppedRecVar);

    if(found == 0)
    {
        runSize[runSizeIndex]++;
    }
    else
    {
        runSizeIndex++;
        runSize.push_back(1);
    }

    numOfBytes += poppedRecVar.getRecordSize(); //num of bytes written
    charPos += poppedRecVar.getRecordSize();  //size of last written rec
    oldRec = poppedRecVar; //popped rec from minheap
    writtenRecords++; //# of written recs
}

int main(int argc, char *argv[])
{
    // part 1 variables and data structures
    Record recObj, poppedRec; //record objs
    int numOfRuns = 0; //num of runs
    int aveRecSize, gigabyte = 1073741824, NUM_OF_RECORDS = 0, sortedRunInput;
    char input; //input file to use
    bool flag = true; //cont loop
    vector<Record> recordVector; // hold rec objs in vector
    vector<int> runPositions;   // char positions from sortedRunPositions.txt
    vector<int> currSizeVec;  // hold curr written records for a run
    array<Record, SIZE> heaparrayCopy;  // copy heaparray when EOF on input.txt
    priority_queue<Record, vector<Record>, greater<Record> > pqObj; //priority queue to sort rec
    ifstream ifs; //ifs stream obj

    //menu for user to decide what list to sort
    do{
        cout << "What type of list to sort?" << endl;
        cout << "Randomly sorted: Enter 'r'" << endl;
        cout << "Forward sorted: Enter 'f'" << endl;
        cout << "Backward sorted: Enter 'b'" << endl;
        cout << "Partially sorted: Enter 'p'" << endl;
        cin >> input;
        input = (char)tolower(input);

        //input file to use
        switch (input)
        {
            case 'r':
                cout << "Enter number of records to make: ";
                cin >> NUM_OF_RECORDS;
                createInputFile(NUM_OF_RECORDS); // create input file
                ifs.open("input.txt");  // input stream for file
                flag = false;
                break;
            case 'f':
                ifs.open("inputFwdSort.txt");  // forward sorted
                NUM_OF_RECORDS = 26;
                flag = false;
                break;
            case 'b':
                ifs.open("inputBackSort.txt"); // backwards sorted
                NUM_OF_RECORDS = 26;
                flag = false;
                break;
            case 'p':
                ifs.open("inputPartSort.txt"); // partially sorted
                NUM_OF_RECORDS = 26;
                flag = false;
                break;
            default:
                cout << "Invalid input. Please reenter your choice." << endl;

        }
    }while(flag);
    flag = true;

    ofstream ofs("sortedrun.txt"); // output stream for file

    sortedRunPos.push_back(0);  // add 1st sorted run pos
    runSize.push_back(0);

    cout << endl << "Starting program" << endl;
    cout << "List is sorted by strings or integers depending on compiler option" << endl;
    cout << "of STRING or INT. type.h contains macros for both types" << endl;
    cout << endl << "Reading in records from file" << endl;

    //initialize minheap
    for (int index = 0; index < SIZE; index++)
    {
        recObj.extractFileFront(ifs);
        recordVector.push_back(recObj);
    }

    dualHeap minHeap(recordVector);  // create minHeap
    minHeap.Heapify();

    cout << "Creating sorted runs in min heap" << endl;
    cout << "Writing sorted runs to sortedrun.txt" << endl;

    //pop record from minheap and store in sortedrun.txt
    while (ifs.peek() != EOF)
    {
        poppedRec = minHeap.getRoot(); //get root of minheap

        ofs << poppedRec;  //write record to file
        minHeap.active_heap_pop(); //pop from minheap
        recObj.extractFileFront(ifs);  // extract new record from input, pop on minheap
        updateStats(poppedRec);

        // push to active or pending heap
        if (poppedRec < recObj)
        {
            minHeap.active_heap_push(recObj);
        }
        else
        {
            minHeap.pending_heap_push(recObj);
        }
        minHeap.Heapify(); //heapify

        //change directions if pending is full
        if(minHeap.getPendingCount() == SIZE)
        {
            minHeap.directionFlip();
            minHeap.Heapify();
        }
    }

    // pop remaining active
    if(minHeap.getActiveCount() > 0)
    {
        int activeVal = minHeap.getActiveCount();
        while (minHeap.getActiveCount() > 1)
        {
            poppedRec = minHeap.getRoot(); //get root of minheap
            ofs << poppedRec;   //write to file
            updateStats(poppedRec);

            //popping from minheap doesn't reduce count. have to force
            minHeap.setActiveCount(activeVal--);
            minHeap.active_heap_pop();
            minHeap.Heapify();
        }
    }

    // pop remaining pending. make pending->active to pop off
    if (minHeap.getPendingCount() > 0)
    {
        //convert pending into active
        int activeVal = minHeap.getPendingCount();
        minHeap.directionFlip();
        while (minHeap.getActiveCount() > 1)
        {
            poppedRec = minHeap.getRoot(); //get root of minheap
            ofs << poppedRec;              //write to file
            updateStats(poppedRec);

            //popping from minheap doesn't reduce count. have to force
            minHeap.setActiveCount(activeVal--);
            minHeap.active_heap_pop();
            minHeap.Heapify();
        }
    }

    cout << endl << "Total records from input file: " << NUM_OF_RECORDS << endl;
    cout << "Total sorted runs written to sortedrun.txt: " << runSize.size() << endl;
    cout << "Total written records to sortedrun.txt: " << writtenRecords << endl;
    cout << "Each sorted run in sortedrun.txt is monotonically ordered" << endl;

    ifs.close(); // close input stream
    ifs.clear();
    ofs.close(); // close file stream
    ofs.clear();

    ofs.open("sortedRunPositions.txt");

    //store begin of each sorted run in sortedRunPositions
    cout << endl << "Writing beginning of each sorted run to sortedRunPositions.txt" << endl;
    for (int index = 0; index < sortedRunPos.size(); index++)
    {
        if (index == sortedRunPos.size() - 1)
            ofs << sortedRunPos[index];
        else
            ofs << sortedRunPos[index]  << " ";
    }

    ofs.close();
    ofs.clear();

    ofs.open("sorted.txt"); //file of sorted rec
    ifstream ifssorted("sortedrun.txt"); //file of sorted runs
    ifs.open("sortedRunPositions.txt"); //file of begin run positions

    int minValue = runSize[0], maxValue = runSize[0], minIndex = 0, maxIndex = 0;
    int aveRunSize = 0;

    // find smallest and largest runs
    for (int index = 1; index < runSize.size(); index++)
    {
        if(runSize[index] < minValue)
        {
            minValue = runSize[index];
            minIndex = index;
        }
        if(runSize[index] > maxValue)
        {
            maxValue = runSize[index];
            maxIndex = index;
        }

    }

    //display # of recs in runs
    do{
        cout << "Would you like to see # of records per run? yes: Enter 'y' or no: Enter 'n'" << endl;
        cin >> input;
        input = (char)tolower(input);

        if (input == 'y' || input == 'n')
            flag = false;
        else
            cout << "Invalid input. Please reenter your choice." << endl;
    }while(flag);

    // output # of records in each run
    for (int index = 0; index < runSize.size(); index++)
    {
        if (input == 'y')
            cout << "run # " << index << ". # of records: " << runSize[index] << endl;
        currSizeVec.push_back(0);
    }

    aveRunSize = NUM_OF_RECORDS / runSize.size();
    cout << "smallest run: " << minIndex << " " << "# of records in smallest: " << runSize[minIndex] << endl;
    cout << "largest run: " << maxIndex << " " << "# of records in largest: " << runSize[maxIndex] << endl;
    cout << "ave run size: " << aveRunSize << endl;
    cout << "total num of runs: " << runSize.size() << endl;

    //store sorted run positions in file
    cout << "Reading in sorted run positions from sortedRunPositions.txt" << endl;

    // read in starting positions of each run from file sortedRunPositions.txt
    int runNum = 0;
    while(ifs.peek() != EOF)
    {
        ifs >> sortedRunInput; // read in starting position of a run
        recObj.extractFileRecByPos(ifssorted, sortedRunInput);  // extract 1st record of a run from file sortedrun.txt using position from prev line
        runPositions.push_back(sortedRunInput); // store curr position of each run in vector. index 0 = starting position of run 1...
        recObj.setRunNum(runNum);
        pqObj.push(recObj); // add field to priority queue
        runNum++;
    }

    cout << endl;
    ifs.close();
    ifs.clear();
    ifssorted.seekg(0); //reset stream

    cout << "Sorting records in priority queue" << endl;
    cout << "Writing records to sortedrun.txt in ascending order" << endl;
    while (!pqObj.empty())
    {
        recObj = pqObj.top(); // get field in PQ
        pqObj.pop(); //remove field from PQ
        runNum = recObj.getRunNum();
        ofs << recObj;  // write out found record to file sorted.txt
        writtenRecords2++;          // keep track of written records to sorted.txt
        currSizeVec[runNum]++;       // increment # of records written for that run
        runPositions[runNum] += recObj.getRecordSize(); // move to next record in current run

        if (currSizeVec[runNum] < runSize[runNum])
        {
            recObj.extractFileRecByPos(ifssorted, runPositions[runNum]); // get next rec in that run
            recObj.setRunNum(runNum); // run num of rec
            pqObj.push(recObj);   // push that field into PQ
        }
        ifssorted.seekg(0); // reset to begin of file
    }

    ifssorted.close(); // close sortedrun.txt
    ofs.close();       // close sorted.txt

    cout << endl;

    aveRecSize = numOfBytes / writtenRecords;
    numOfRuns = sortedRunPos.size();

    cout << "Creating statistics in log.txt" << endl;
    ofs.open("log.txt");
    ofs << "input file choosen from: input.txt, inputFwdSort.txt, inputBackSort.txt, or inputPartSort.txt" << '\n';
    ofs << "Sorted records file: sorted.txt" << '\n';
    ofs << "smallest run: " << minIndex << " " << "# of records in smallest: " << runSize[minIndex] << endl;
    ofs << "largest run: " << maxIndex << " " << "# of records in largest: " << runSize[maxIndex] << endl;
    ofs << "ave run size: " << aveRunSize << endl;
    ofs << "Average record size in bytes: " << aveRecSize << '\n';
    ofs << "Number of records per 1 GB of RAM: " << gigabyte / aveRecSize << '\n';
    ofs << "Number of records in sorted.txt: " << writtenRecords << '\n';
    ofs << "Number of runs in sortedrun.txt. Run # start at 0 and end at n-1: " << numOfRuns << '\n';
    ofs.close();

    cout << "Total written records to sorted.txt: " << writtenRecords2 << endl;
    cout << "Total bytes written to sorted.txt: " << numOfBytes << endl;
    cout << "Average size of each record in bytes: " << aveRecSize << endl;
    cout << endl << "The following files were created in the same directory as main.cpp" << endl;
	cout << "input file choosen from: input.txt, inputFwdSort.txt, inputBackSort.txt, or inputPartSort.txt" << endl;
    cout << "sortedrun.txt - sorted runs of records for priority queue" << endl;
    cout << "sortedRunPositions.txt - starting position of each sorted run in sortedrun.txt" << endl;
    cout << "sorted.txt - the final sorted list in ascending order of strings or integers" << endl;
    cout << "log.txt - a log of different statistics" << endl;
    printf("Program execution time: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    /** sequential set **/
    ifs.open("sorted.txt");

    while (ifs.peek() != EOF)
    {

    }

	return 0;
}
