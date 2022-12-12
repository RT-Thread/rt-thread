////////////////////////////////////////////////////////////////////////////////
/// @file:   dtype.h
/// @author  AE TEAM
/// @brief   Define the data types to be used in the project, including the function
///          library and application code. Use the data types defined in this file.
////////////////////////////////////////////////////////////////////////////////
#ifndef __DTYPE_H
#define __DTYPE_H     //This is done to avoid including the header file repeatedly in the same file


//Defines the read and write characteristics of data, which is often used for storage limits of peripheral registers
#ifndef __I
#define     __I     volatile const    //only read
#endif
#ifndef __O
#define     __O     volatile          //only write
#endif
#ifndef __IO
#define     __IO    volatile          //read write
#endif

//Common data type definitions

typedef unsigned char  int8u;         //haven't symbol8 bit integer variable
typedef signed   char  int8s;         //have symbol8 bit integer variable
typedef unsigned short int16u;        //haven't symbol16 bit integer variable
typedef signed   short int16s;        //have symbol16 bit integer variable
typedef unsigned int   int32u;        //haven't symbol32 bit integer variable
typedef signed   int   int32s;        //have symbol32 bit integer variable
typedef float          fp32;          //Single-precision floating-point number (32-bit length)
typedef double         fp64;          //Double-precision floating-point number (64-bit length)

#endif  //__DTYPE_H
