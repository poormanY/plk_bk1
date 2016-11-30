// Define.h

#ifndef _DEFINE_H_
#define _DEFINE_H_

//////////////////////////////////////////////////

typedef   signed	   char S08;
typedef unsigned	   char U08;
typedef   signed short int  S16;
typedef unsigned short int  U16;
typedef   signed long  int  S32;
typedef unsigned long  int  U32;
typedef   signed long  long S64;
typedef unsigned long  long U64;

#ifndef true
#define true   1u
#define false  0u
#endif //true

#ifndef _hi
#define _hi	1u
#define _lo	0u
#endif //_hi

#ifndef TOF
#define TOF     bit
#endif

#endif // _DEFINE_H_
