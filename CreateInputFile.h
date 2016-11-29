/**
@file CreateInputFile.h
@author jesse babcock Burg, Christopher N, Garrett Kamrath
Dayitwa Shrestha, Sanam Lama, Kapil Joshi
@date Monday, November 14, 2016
@version revision 1.1

@brief creates a randomly sorted input file

@details  A random input file using records of size numOfRecords is generated.  The string name field
is fixed at 4 chars and makes a string of random alpha chars.  Int idNum is 4 chars in length
and takes a random value from 1000 - 9999.
*/

#ifndef CREATEINPUTFILE_H_INCLUDED
#define CREATEINPUTFILE_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include "Record.h"
#include <time.h>
using namespace std;

/** @brief create a random string name field of size 4 chars
 *
 * @param len length of string of type int
 * @param arrayPtr char ptr to an array
 *
 */
void createName(char *arrayPtr, const int len)
{
    static const char alphanum[] =
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        arrayPtr[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    arrayPtr[len] = 0;
}

/** @brief create a random input file of records
 *
 * @post input file is made
 * @param numOfRecords num of recs to make of type int
 *
 */
void createInputFile(int numOfRecords)
{
    srand (time(NULL)); //seed rand generator
    int randNum, randNameLen;;
    Record r1;
    char name[40];
    ofstream ofs("input.txt"); // output file

    //create each rec obj
    for (int index = 0; index < numOfRecords; index++)
    {
        randNameLen = 4; //string length
        randNum= rand() % 8999 + 1000; //random idNum
        createName(name, randNameLen);
        r1.setName(name);
        r1.setIdNum(randNum);
        ofs << r1;  //write to file
    }
    ofs.close();
    ofs.clear();
}


#endif // CREATEINPUTFILE_H_INCLUDED
