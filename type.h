/**
@file type.h
@author jesse babcock Burg, Christopher N, Garrett Kamrath
Dayitwa Shrestha, Sanam Lama, Kapil Joshi
@date Monday, November 14, 2016
@version revision 1.1

@brief macros to replace sections of code based on compile time option of INT and STRING

@details  The program must sort by int or string. Several sections of code depend on comparing or storing based on data type.
RECOBJGETFIELD is replaced by either getName() or getIdNum().
*/

#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED
#if STRING
    #define RECOBJGETFIELD getName()
#endif // STRING

#if INT
    #define RECOBJGETFIELD getIdNum()
#endif // INT
#endif // TYPE_H_INCLUDED
