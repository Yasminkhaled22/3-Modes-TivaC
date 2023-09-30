#ifndef STD_TYPES
#define STD_TYPES
/*
*Task1
*/
typedef unsigned char       uint8;
typedef signed char         int8;
typedef unsigned short      uint16;
typedef signed short        int16;
typedef unsigned long       uint32;
typedef signed long         int32;
//typedef unsigned long long  uint32;
//typedef signed long long    int32;
typedef int*                int32_ptr;
typedef unsigned int*       uint32_ptr;
typedef char*               int16_ptr;
typedef unsigned char*      uint16_ptr;

#define LOGIC_HIGH        (1u)
#define LOGIC_LOW         (0u)
#define NULL_PTR ((void*)0)
/*
*What is the difference between using the typedef for type definition and using the #define forthe same cause ?
using pointers with #define is defined for the first variable only unlike typedef.
*/

/*
Task2
define X as a 10 using the #define macro definition. Create also a global variable that is
anint y. Then write down the differences between the X and why in the following points:
*/
/*
*When are they resolved in the build process? 
x in preprocessor stage, y in compiler
 
* Where is each one of them stored?
x in program code in ROM, y in RAM

* How can each of them be used in the code? Which of them could be altered and why?
x replaced every time by 10(text replacement), y can be altered through the code

*/
#endif
