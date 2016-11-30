/***************************************************************************
 *
 * Created July, 2005
 * Modified Sept, 2015
 * File : HIGHT_MCU.c
 *
 * Description : Modificated HIGHT for MCU
 *
 **************************************************************************/

/*************** Header files *********************************************/
#include "StdAfx.h"
#include "HIGHT_MCU.h"

/*************** Macros ***************************************************/

/*************** Global Variables *****************************************/
U16 uRandomNumber;
U16 uMcuCount;
U08 arbRoundKey[40];
U08 arbUserKey[16] = {0xBD, 0x70, 0x4C, 0x6B, 0x23, 0x3E, 0x81, 0x35,
                        0x59, 0x73, 0x57, 0x9A, 0xE8, 0xF2, 0xD6, 0x3E};

static U08 Delta[32] = {
    0x5A,0x6D,0x36,0x1B,0x0D,0x06,0x03,0x41,
    0x60,0x30,0x18,0x4C,0x66,0x33,0x59,0x2C,
    0x56,0x2B,0x15,0x4A,0x65,0x72,0x39,0x1C,
    0x4E,0x67,0x73,0x79,0x3C,0x5E,0x6F,0x37};

void HIGHT_KeySched(U08 *pbUserKey, U08 *pbRoundKey)
{
    U08 i,j;

    for(i = 0; i < 4; i++)
    {
        pbRoundKey[i  ] = pbUserKey[i+12];
        pbRoundKey[i+4] = pbUserKey[i   ];
    }

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 8; j++)
        {
            pbRoundKey[8+16*i+j  ] = (U08)(pbUserKey[(j-1)&7    ] + Delta[16*i+j  ]);
            pbRoundKey[8+16*i+j+8] = (U08)(pbUserKey[((j-1)&7)+8] + Delta[16*i+j+8]);
        }
    }
}

/*************** Encryption*************************************************/
#if 0
// Round Function F0, F1
U08 HIGHT_F0(U08 x)
{
    U16 uX0;

    uX0 = (((x<<1)&0x00FF) ^ (((x<<1)&0xFF00)>>8))
         ^(((x<<2)&0x00FF) ^ (((x<<2)&0xFF00)>>8))
         ^(((x<<7)&0x00FF) ^ (((x<<7)&0xFF00)>>8));

    return (U08)uX0;
}

U08 HIGHT_F1(U08 x)
{
    U16 uX1;

    uX1 = (((x<<3)&0x00FF) ^ (((x<<3)&0xFF00)>>8))
         ^(((x<<4)&0x00FF) ^ (((x<<4)&0xFF00)>>8))
         ^(((x<<6)&0x00FF) ^ (((x<<6)&0xFF00)>>8));

    return (U08)uX1;
}
#endif

void JTP_Encrypt(U08 *pbRoundKey, U08 *pbData, U16 uLen)
{
    U08 bBlockNum;
    U08 i;
    
    bBlockNum = (uLen-1)>>3;
    bBlockNum += 1;
    
    for (i = 0; i < bBlockNum; i++)
    {
        HIGHT_Encrypt(pbRoundKey, pbData+(i<<3));        
    }
}

void JTP_Decrypt(U08 *pbRoundKey, U08 *pbData, U16 uLen)
{
    U08 bBlockNum;
    U08 i;
    bBlockNum = (uLen-1)>>3;
    bBlockNum += 1;
    
    for (i = 0; i < bBlockNum; i++)
    {
        HIGHT_Decrypt(pbRoundKey, pbData+(i<<3));        
    }   
    
}

void HIGHT_Encrypt(U08 *pbRoundKey, U08 *pbData)
{
    U16 XX[8];

    // First Round
    XX[1] = pbData[1];
    XX[3] = pbData[3];
    XX[5] = pbData[5];
    XX[7] = pbData[7];

    XX[0] = (pbData[0] + pbRoundKey[0]) & 0xFF;
    XX[2] = (pbData[2] ^ pbRoundKey[1]) & 0xFF;
    XX[4] = (pbData[4] + pbRoundKey[2]) & 0xFF;
    XX[6] = (pbData[6] ^ pbRoundKey[3]) & 0xFF;

    // Encryption Round
    #define HIGHT_ENC(k, i0, i1, i2, i3, i4, i5, i6, i7){                   \
        XX[i0] = (XX[i0] ^ (XX[i1] + pbRoundKey[4*k+3])) & 0xFF;    \
        XX[i2] = (XX[i2] + (XX[i3] ^ pbRoundKey[4*k+2])) & 0xFF;    \
        XX[i4] = (XX[i4] ^ (XX[i5] + pbRoundKey[4*k+1])) & 0xFF;    \
        XX[i6] = (XX[i6] + (XX[i7] ^ pbRoundKey[4*k+0])) & 0xFF;    \
    }

	HIGHT_ENC( 2,  7,6,5,4,3,2,1,0);
    HIGHT_ENC( 3,  6,5,4,3,2,1,0,7);
    HIGHT_ENC( 4,  5,4,3,2,1,0,7,6);
    HIGHT_ENC( 5,  4,3,2,1,0,7,6,5);
    HIGHT_ENC( 6,  3,2,1,0,7,6,5,4);
    HIGHT_ENC( 7,  2,1,0,7,6,5,4,3);
    HIGHT_ENC( 8,  1,0,7,6,5,4,3,2);
    HIGHT_ENC( 9,  0,7,6,5,4,3,2,1);

    // Final Round
    pbData[1] = (U08) XX[2];
    pbData[3] = (U08) XX[4];
    pbData[5] = (U08) XX[6];
    pbData[7] = (U08) XX[0];

    pbData[0] = (U08) (XX[1] + pbRoundKey[4]);
    pbData[2] = (U08) (XX[3] ^ pbRoundKey[5]);
    pbData[4] = (U08) (XX[5] + pbRoundKey[6]);
    pbData[6] = (U08) (XX[7] ^ pbRoundKey[7]);
}

/***************Decryption *************************************************/

// Same as encrypt, except that round keys are applied in reverse order

void HIGHT_Decrypt(U08 *pbRoundKey, U08 *pbData)
{
    U16 XX[8];

    XX[2] = (U08) pbData[1];
    XX[4] = (U08) pbData[3];
    XX[6] = (U08) pbData[5];
    XX[0] = (U08) pbData[7];

    XX[1] = (U08) (pbData[0] - pbRoundKey[4]);
    XX[3] = (U08) (pbData[2] ^ pbRoundKey[5]);
    XX[5] = (U08) (pbData[4] - pbRoundKey[6]);
    XX[7] = (U08) (pbData[6] ^ pbRoundKey[7]);

    #define HIGHT_DEC(k, i0, i1, i2, i3, i4, i5, i6, i7){                   \
        XX[i1] = (XX[i1] - (XX[i2] ^ pbRoundKey[4*k+2])) & 0xFF;    \
        XX[i3] = (XX[i3] ^ (XX[i4] + pbRoundKey[4*k+1])) & 0xFF;    \
        XX[i5] = (XX[i5] - (XX[i6] ^ pbRoundKey[4*k+0])) & 0xFF;    \
        XX[i7] = (XX[i7] ^ (XX[i0] + pbRoundKey[4*k+3])) & 0xFF;    \
    }

    HIGHT_DEC( 9,  7,6,5,4,3,2,1,0);
    HIGHT_DEC( 8,  0,7,6,5,4,3,2,1);
    HIGHT_DEC( 7,  1,0,7,6,5,4,3,2);
    HIGHT_DEC( 6,  2,1,0,7,6,5,4,3);
    HIGHT_DEC( 5,  3,2,1,0,7,6,5,4);
    HIGHT_DEC( 4,  4,3,2,1,0,7,6,5);
    HIGHT_DEC( 3,  5,4,3,2,1,0,7,6);
    HIGHT_DEC( 2,  6,5,4,3,2,1,0,7);

    // Final Round
    pbData[1] = (U08) (XX[1]);
    pbData[3] = (U08) (XX[3]);
    pbData[5] = (U08) (XX[5]);
    pbData[7] = (U08) (XX[7]);

    pbData[0] = (U08) (XX[0] - pbRoundKey[0]);
    pbData[2] = (U08) (XX[2] ^ pbRoundKey[1]);
    pbData[4] = (U08) (XX[4] - pbRoundKey[2]);
    pbData[6] = (U08) (XX[6] ^ pbRoundKey[3]);
}

/*************** END OF FILE **********************************************/