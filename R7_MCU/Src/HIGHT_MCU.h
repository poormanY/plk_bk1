/***************************************************************************
 *
 * File : HIGHT_MCU.h
 *
 * Description : header file for HIGHT_MCU.c
 *
 **************************************************************************/

#ifndef _HIGHT_H_
#define _HIGHT_H_

#include "define.h"
/*************** Header files *********************************************/


/*************** Definitions **********************************************/

#define CT_LITTLE_ENDIAN

/*************** Constants ************************************************/

/*************** Macros ***************************************************/
////
#define ROTL_BYTE(x, n) ( (U08)((x) << (n)) | (U32)((x) >> (8-(n))) )
#define ROTR_BYTE(x, n) ( (U08)((x) >> (n)) | (U32)((x) << (8-(n))) )

#if defined(_MSC_VER)
    #define ROTL_DWORD(x, n) _lrotl((x), (n))
    #define ROTR_DWORD(x, n) _lrotr((x), (n))
#else
    #define ROTL_DWORD(x, n) ( (U32)((x) << (n)) | (U32)((x) >> (32-(n))) )
    #define ROTR_DWORD(x, n) ( (U32)((x) >> (n)) | (U32)((x) << (32-(n))) )
#endif

////    reverse the byte order of DWORD(DWORD:4-bytes integer).
#define ENDIAN_REVERSE_DWORD(dwS)   ( (ROTL_DWORD((dwS),  8) & 0x00ff00ff)  \
                                    | (ROTL_DWORD((dwS), 24) & 0xff00ff00) )

////
#if defined(CT_BIG_ENDIAN)      ////    Big-Endian machine
    #define BIG_B2D(B, D)       D = *(U32 *)(B)
    #define BIG_D2B(D, B)       *(U32 *)(B) = (U32)(D)
    #define LITTLE_B2D(B, D)    D = ENDIAN_REVERSE_DWORD(*(U32 *)(B))
    #define LITTLE_D2B(D, B)    *(U32 *)(B) = ENDIAN_REVERSE_DWORD(D)
#elif defined(CT_LITTLE_ENDIAN) ////    Little-Endian machine
    #define BIG_B2D(B, D)       D = ENDIAN_REVERSE_DWORD(*(U32 *)(B))
    #define BIG_D2B(D, B)       *(U32 *)(B) = ENDIAN_REVERSE_DWORD(D)
    #define LITTLE_B2D(B, D)    D = *(U32 *)(B)
    #define LITTLE_D2B(D, B)    *(U32 *)(B) = (U32)(D)
#else
    #error ERROR : Invalid DataChangeType
#endif

#if defined(_MSC_VER)
    #define INLINE  _inline
#else
    #define INLINE  inline
#endif

/*************** New Data Types *******************************************/
#define U08    unsigned char       //  1-byte data type
#define U16    unsigned short int  //  2-byte data type
#define U32    unsigned long      //  4-byte data type
/*************** Prototypes ***********************************************/
void HIGHT_KeySched(U08 *pbUserKey, U08 *pbRoundKey);
void HIGHT_Encrypt(U08 *pbRoundKey, U08 *pbData);
void HIGHT_Decrypt(U08 *pbRoundKey, U08 *pbData);
//U08 HIGHT_F0(U08 x);
//U08 HIGHT_F1(U08 x);
void JTP_Encrypt(U08 *pbRoundKey, U08 *pbData, U16 uLen);
void JTP_Decrypt(U08 *pbRoundKey, U08 *pbData, U16 uLen);

extern U16 uRandomNumber;
extern U16 bCount;
extern U08 pbRoundKey[40];
extern U08 pbUserKey[16];

#endif  /* _HIGHT_H_ */