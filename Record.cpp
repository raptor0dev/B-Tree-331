#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Record.h"

using namespace std;

Record::Record()
{
    //ctor
}

void Record::setName(const string& nameStr)
{
    name = nameStr;
}

void Record::setIdNum(const int& num)
{
    idNum = num;
}

string Record::getName() const
{
    return name;
}

int Record::getIdNum() const
{
    return idNum;
}

int Record::getNameCharSize() const
{
    return nameCharSize;
}

int Record::getIdNumCharSize() const
{
    return idNumCharSize;
}

int Record::getRecordSize() const
{
    return nameCharSize + idNumCharSize + 2;
}

// extract front of file
void Record::extractFileFront(ifstream& is)
{
    string nameBuffer, idNumBuffer;
    getline(is, nameBuffer, ',');
    getline(is, idNumBuffer, '|');
    nameCharSize = nameBuffer.size();
    idNumCharSize = idNumBuffer.size();
    name = nameBuffer;
    idNum = atoi(idNumBuffer.c_str());
}

// is: file stream obj, charPos: position in file to extract from, type: field to extract
void Record::extractFileFieldByPos(ifstream& is, int charPos, string type)
{
    string nameBuffer, idNumBuffer;

    if (type == "name")  // name field
    {
        is.seekg(charPos);  // position to extract from
        getline(is, nameBuffer, ','); // get chars up to delim
        nameCharSize = nameBuffer.size(); // char keyCount extracted
        name = nameBuffer; // set name field
    }
    else if (type == "idNum")  // idNum field
    {
        is.seekg(charPos);
        getline(is, idNumBuffer, '|');
        idNumCharSize = idNumBuffer.size();
        idNum = atoi(idNumBuffer.c_str());
    }
    else
        cout << "Use name or idNum" << endl;
}

// is: file stream obj, charPos: position in file to extract from
void Record::extractFileRecByPos(ifstream& is, int charPos)
{
    string nameBuffer, idNumBuffer; //string to hold each field
    is.seekg(charPos);
    getline(is, nameBuffer, ','); //get string field
    getline(is, idNumBuffer, '|'); //get int field
    nameCharSize = nameBuffer.size(); //store size
    idNumCharSize = idNumBuffer.size();
    name = nameBuffer;
    idNum = atoi(idNumBuffer.c_str());  //covert idNum to int
}
void Record::setRunNum(const int &runNum)
{
    runNumber = runNum;
}

int Record::getRunNum() const
{
    return runNumber;
}
// insert into file
ostream& operator<<(ostream& os, const Record& object)
{
    os << object.name << ',';
    os << object.idNum << '|';
    return os;
}

//RECOBJGETFIELD is a macro from type.h that does the following code based on compiler
//option of INT or STRING
//string: RECOBJGETFIELD = getName()
//int: RECOBJGETFIELD = getIdNum()
//overload < for minheap comparison
bool operator < (const Record &r1, const Record &r2){

    if (r1.RECOBJGETFIELD < r2.RECOBJGETFIELD)
        return true;
    else
        return false;
}

//overload > op for priority queue
bool operator > (const Record &r1, const Record &r2){

    if (r1.RECOBJGETFIELD > r2.RECOBJGETFIELD)
        return true;
    else
        return false;
}
