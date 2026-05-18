/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_crc.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H76x_78x_CRC_H__
#define __N32H76x_78x_CRC_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

#include "n32h76x_78x.h"

typedef struct
{
    uint32_t GeneratingPolynomial;      /* Set CRC generating polynomial as a 7, 8, 16 or 32-bit long value for a polynomial degree
                                           respectively equal to 7, 8, 16 or 32. This field is written in normal,
                                           representation e.g., for a polynomial of degree 7, X^7 + X^6 + X^5 + X^2 + 1
                                           is written 0x65.  */
    uint32_t CRCLength;                 /* This parameter is a value of ref CRC_Polynomial_Sizes and indicates CRC length.
                                           Value can be either one of
                                           arg ref CRC_POLYLENGTH_32B                  (32-bit CRC),
                                           arg ref CRC_POLYLENGTH_16B                  (16-bit CRC),
                                           arg ref CRC_POLYLENGTH_8B                   (8-bit CRC),
                                           arg ref CRC_POLYLENGTH_7B                   (7-bit CRC). */
    uint32_t InitValue;                 /* Init value to initiate CRC computation. No need to specify it if DefaultInitValueUse
                                           is set to DEFAULT_INIT_VALUE_ENABLE.   */
    uint32_t InputDataByteInversionMode;    /* This parameter is a value of ref CRC Input Data Byte Reverse and specifies input data byte inversion mode.
                                           Can be either one of the following values
                                           arg ref CRC_INDATA_BYTE_REVERSE_NONE       no input data inversion
                                           arg ref CRC_INDATA_BYTE_REVERSE_HALFWORD   halfword-wise inversion,0x1A2B3C4D becomes 0x2B1A4D3C
                                           arg ref CRC_INDATA_BYTE_REVERSE_WORD       word-wise inversion, 0x1A2B3C4D becomes 0x4D3C2B1A */
    uint32_t InputDataBitInversionMode;    /* This parameter is a value of ref CRC Input Data Bit Reverse and specifies input data inversion mode.
                                           Can be either one of the following values
                                           arg ref CRC_INDATA_BIT_REVERSE_NONE       no input data inversion
                                           arg ref CRC_INDATA_BIT_REVERSE_BYTE       byte-wise inversion, 0x1A2B3C4D becomes 0x58D43CB2
                                           arg ref CRC_INDATA_BIT_REVERSE_HALFWORD   halfword-wise inversion,0x1A2B3C4D becomes 0xD458B23C
                                           arg ref CRC_INDATA_BIT_REVERSE_WORD       word-wise inversion, 0x1A2B3C4D becomes 0xB23CD458 */
    uint32_t OutputDataInversionMode;   /* This parameter is a value of ref CRC Output Data Reverse and specifies output data (i.e. CRC) inversion mode.
                                            Can be either
                                            arg ref CRC_OUTPUTDATA_INVERSION_DISABLE   no CRC inversion,
                                            arg ref CRC_OUTPUTDATA_INVERSION_ENABLE    CRC 0x11223344 is converted into 0x22CC4488 */
    uint32_t InputDataXor;              /* This parameter is used to set CRC_DR XOR calculation value before CRC calculation. */

    uint32_t OutputDataXor;             /*  This parameter is used to set CRC_DR XOR calculation value after CRC calculation.  */
} CRC_InitType;

/**  CRC_Default_Polynomial_Value   Default CRC generating polynomial **/
#define DEFAULT_CRC32_POLY      ((uint32_t)0x04C11DB7U) /*  X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + X^10 +X^8 + X^7 + X^5 + X^4 + X^2+ X +1 */

/** CRC_Default_InitValue    Default CRC computation initialization value */
#define DEFAULT_CRC_INITVALUE   ((uint32_t)0xFFFFFFFFU) /* Initial CRC default value */

/** CRC_Polynomial_Sizes Polynomial sizes to configure the peripheral */
#define CRC_POLYLENGTH_32B                  ((uint32_t)0x00000000U) /* Resort to a 32-bit long generating polynomial */
#define CRC_POLYLENGTH_16B                  (CRC_CTRL_POLYSIZE_0)   /* Resort to a 16-bit long generating polynomial */
#define CRC_POLYLENGTH_8B                   (CRC_CTRL_POLYSIZE_1)   /* Resort to a 8-bit long generating polynomial  */
#define CRC_POLYLENGTH_7B                   (CRC_CTRL_POLYSIZE)     /* Resort to a 7-bit long generating polynomial  */

/** CRC Input Data Byte Reverse */
#define CRC_INDATA_BYTE_REVERSE_NONE        ((uint32_t)0x00000000U) /* Input Data Byte order not affected */
#define CRC_INDATA_BYTE_REVERSE_HALFWORD    (CRC_CTRL_BYTEENDIAN_1) /* Input Data Byte reversal done by half-word */
#define CRC_INDATA_BYTE_REVERSE_WORD        (CRC_CTRL_BYTEENDIAN)   /* Input Data Byte reversal done by word */

/** CRC Input Data Bit Reverse */
#define CRC_INDATA_BIT_REVERSE_NONE         ((uint32_t)0x00000000U) /* Input Data bit order not affected */
#define CRC_INDATA_BIT_REVERSE_BYTE         (CRC_CTRL_REVIN_0)      /* Input Data bit reversal done by byte */
#define CRC_INDATA_BIT_REVERSE_HALFWORD     (CRC_CTRL_REVIN_1)      /* Input Data bit reversal done by half-word */
#define CRC_INDATA_BIT_REVERSE_WORD         (CRC_CTRL_REVIN_1 \
                                            |CRC_CTRL_REVIN_0)      /* Input Data bit reversal done by word */

/** CRC Output Data Reverse */
#define CRC_OUTDATA_REVERSE_NONE            ((uint32_t)0x00000000U) /* Output Data bit order not affected */
#define CRC_OUTDATA_REVERSE_BIT             (CRC_CTRL_REVOUT)       /* Output Data bit reversal done by bit */

/** CRC_Input_Buffer_Format Input Buffer Format */
#define CRC_INPUTDATA_FORMAT_BYTES          ((uint32_t)0x00000001U) /* Input data in byte format      */
#define CRC_INPUTDATA_FORMAT_HALFWORDS      ((uint32_t)0x00000002U) /* Input data in half-word format */
#define CRC_INPUTDATA_FORMAT_WORDS          ((uint32_t)0x00000003U) /* Input data in word format      */


void CRC_ResetCalculation(void);
void CRC_DeInit(void);
void CRC_SetInputByteOrder(uint32_t ReverseMode);
void CRC_SetInputBitOrder(uint32_t ReverseMode);
void CRC_SetOutputBitOrder(uint32_t ReverseMode);
void CRC_SetInputDataXor(uint32_t xor_value);
void CRC_SetOutputDataXor(uint32_t xor_value);
void CRC_SetInitialData(uint32_t InitCrc);
void CRC_SetPolynomialCoef(uint32_t PolynomCoef);
void CRC_SetPolynomialSize(uint32_t PolySize);

void CRC_StructInit(CRC_InitType *CRC_InitStruct);
void CRC_Init(CRC_InitType *CRC_InitStruct);
uint32_t CRC_Calculate(uint32_t InputDataFormat, void *pBuffer, uint32_t BufferLength);
uint32_t CRC_Accumulate(uint32_t InputDataFormat, void *pBuffer, uint32_t BufferLength);
uint32_t CRC_GetLRC(void);
uint32_t CRC_GetIDAT(void);
void CRC_WriteIDAT(uint32_t Idat);


#ifdef __cplusplus
}
#endif

#endif /* __n32h76x_78x_CRC_H__ */


