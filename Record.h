/**
@file Record.h
@author Burg, Christopher N. jesse babcock Garrett Kamrath
Dayitwa Shrestha, Sanam Lama, Kapil Joshi
@date November 14, 2016
@version revision 1.1

@brief Record class definition and specification file

@details
The record class helps keep track of string and integer field values of a record. Several functions help set various variables while others
access them.  There are 3 ways to read from a file with extractFileFront, extractFileRecByPos, and extractFileFieldByPos. 3 overloaded methods
use friend access to provide operations of <<, <, and >.  The sizes of fields and records are stored to help with file extraction.
*/

#ifndef RECORD_H
#define RECORD_H

#include <fstream>
#include <iostream>
#include <string>
#include "type.h"
using namespace std;

class Record
{
    private:
        string name;  // name field var
        int idNum, nameCharSize, idNumCharSize, runNumber;  //idNum field var, char size for field vars, and run num rec came from

    public:
        /**
         * @brief constructor
         */
        Record();

        /**
         * @brief mutator function for name
         * @brief sets the name to the private string variable to be used in the program
         * @post sets name
         * @param nameStr the name to be set of type string
         * @return void
         *
         */
        void setName(const string& nameStr);

        /**
         * @brief mutator function for idNum
         * @brief sets the Idnum to the private integer variable to be used in the program
         * @post sets idNum
         * @param num the idNum to be set of type of integer
         * @return void
         *
         */
        void setIdNum(const int& num);

        /** @brief store run num in runNumber var
         * @post runNumber is stored
         * @param runNum the integer to be stored
         * @return void
         *
         */
        void setRunNum(const int &runNum);

        /**
         * @brief returns the value stored in name
         * @post returns name
         * @return string type of name
         */
        string getName() const;

        /**
         * @brief return the value assigned in idNum
         * @post returns idNum
         * @return int type of idNum
         */
        int getIdNum() const;

        /**
         * @brief returns the size of the string name
         * @post returns nameCharSize
         * @return int size of nameCharsize
         */
        int getNameCharSize() const;

        /**
         * @brief returns the size of integer ID Number
         * @post returns idNumCharSize
         * @return int size of idNumCharSize
         */
        int getIdNumCharSize() const;

        /**
         * @brief  returns char size of record
		 * @post returns recordsize
         * @return int type of recordsize
         */
        int getRecordSize() const;

        /** @brief accessor method for runNumber var
         *
         * @post runNumber is returned
         * @return int type of runNumber
         *
         */
        int getRunNum() const;

        /**
         * @brief extract front rec of file. gets fields separated with two delimiters (“,” and “|”), through
		 * @brief use of filehandle also calculates the size of name and ID Number
         * @post stores field vars name and idNum in rec obj
         *
         * @param is input file of type ifstream
         * @return void
         */
        void extractFileFront(ifstream& is);

        /**
         * @brief extract rec from file by position
         * @post stores field vars name and idNum in rec obj
         * @param charPos pos to read from file of type int
         * @param is input file of type ifstream
         * @return void
         */
        void extractFileRecByPos(ifstream& is, int charPos);

        /**
         * @brief extract field from file by position
         * @post stores field var rec obj
         * @param charPos pos to read from file of type int
         * @param is input file of type ifstream
         * @param type field to retrieve of type string
         * @return void
         */
        void extractFileFieldByPos(ifstream& is, int charPos, string type);

        /**
         * @brief write to a file by overloading insertion operator
         * @post rec obj is written to file
         * @param os output file to write of type ostream
         * @param object the rec obj to write out of type record
         * @return ostream return output file stream
         */
        friend ostream& operator<<(ostream& os, const Record& object);

        /** @brief overload < op to use in minheap comparison
         * @post returns if r1 is < r2
         * @param r1 1st rec to compare of type record
         * @param r2 12nd rec to compare of type record
         * @return true if less than else false
         *
         */
        friend bool operator<(const Record &r1, const Record &r2);

        /** @brief overload > op to use in priority queue comparison
         * @post returns if r1 is > r2
         * @param r1 1st rec to compare of type record
         * @param r2 12nd rec to compare of type record
         * @return true if greater than else false
         *
         */
        friend bool operator>(const Record &r1, const Record &r2);
};
//#include "Record.cpp"
#endif // RECORD_H
