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
 * @file n32h76x_78x_crc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_crc.h"
#include "n32h76x_78x_rcc.h"

/**
*\*\name    CRC_ResetCalculation.
*\*\fun     Reset the CRC calculation unit.
*\*\param   none
*\*\return  none
*\*\note    It also set the Data Register to the value stored in the CRC_INIT register.
**/
void CRC_ResetCalculation(void)
{
    CRC->CTRL |= CRC_CTRL_RESET;

    while((CRC->CTRL  & CRC_CTRL_RESET) != 0U)
    {
    }
}


/**
*\*\name   CRC_DeInit.
*\*\fun    Reset the CRC registers to their default values.
*\*\param  none
*\*\return none
**/
void CRC_DeInit(void)
{
    RCC_EnableAHB5PeriphReset2(RCC_AHB5_PERIPHRST_CRC);
}


/**
*\*\name   CRC_SetInputByteOrder.
*\*\fun    Configure the reversal of the byte order of the input data.
*\*\param  ReverseMode This parameter can be one of the following values:
*\*\         - CRC_INDATA_BYTE_REVERSE_NONE
*\*\         - CRC_INDATA_BYTE_REVERSE_HALFWORD
*\*\         - CRC_INDATA_BYTE_REVERSE_WORD
*\*\return None
**/
void CRC_SetInputByteOrder(uint32_t ReverseMode)
{
    CRC->CTRL = ((CRC->CTRL & (~CRC_CTRL_BYTEENDIAN)) | ReverseMode);
}

/**
*\*\name   CRC_SetInputBitOrder.
*\*\fun    Configure the reversal of the bit order of the input data
*\*\param  ReverseMode This parameter can be one of the following values:
*\*\         - CRC_INDATA_BIT_REVERSE_NONE
*\*\         - CRC_INDATA_BIT_REVERSE_BYTE
*\*\         - CRC_INDATA_BIT_REVERSE_HALFWORD
*\*\         - CRC_INDATA_BIT_REVERSE_WORD
*\*\return None
**/
void CRC_SetInputBitOrder(uint32_t ReverseMode)
{
    CRC->CTRL = ((CRC->CTRL & (~CRC_CTRL_REVIN)) | ReverseMode);
}

/**
*\*\name   CRC_SetOutputBitOrder.
*\*\fun    Configure the reversal of the bit order of the Output data
*\*\param  ReverseMode This parameter can be one of the following values:
*\*\         - CRC_OUTDATA_REVERSE_NONE
*\*\         - CRC_OUTDATA_REVERSE_BIT
*\*\return None
**/
void CRC_SetOutputBitOrder(uint32_t ReverseMode)
{
    CRC->CTRL = ((CRC->CTRL & (~CRC_CTRL_REVOUT)) | ReverseMode);
}

/**
*\*\name   CRC_SetInputDataXor.
*\*\fun    Configure the CRC_DAT XOR calculation value before CRC calculation.
*\*\param  xor_value: 32-bit data to be writting into CRC_INXORDAT register.
*\*\return None
**/
void CRC_SetInputDataXor(uint32_t xor_value)
{
    CRC->INXORDAT = xor_value;
}

/**
*\*\name   CRC_SetOutputDataXor.
*\*\fun    Configure the CRC_DAT XOR calculation value after CRC calculation.
*\*\param  xor_value: 32-bit data to be writting into CRC_OUTXORDAT register
*\*\return None
**/
void CRC_SetOutputDataXor(uint32_t xor_value)
{
    CRC->OUTXORDAT = xor_value;
}

/**
*\*\name   CRC_SetInitialData.
*\*\fun    Initialize the Programmable initial CRC value.
*\*\param  InitCrc: 32-bit data to be writting into CRC_INIT register
*\*\return None
**/
void CRC_SetInitialData(uint32_t InitCrc)
{
    CRC->INIT = InitCrc;
}

/**
*\*\name   CRC_SetPolynomialCoef.
*\*\fun    Initialize the Programmable polynomial value
*\*\        (coefficients of the polynomial to be used for CRC calculation).
*\*\param  PolynomCoef Value to be writting into CRC_POL register
*\*\return None
**/
void CRC_SetPolynomialCoef(uint32_t PolynomCoef)
{
    CRC->POL = PolynomCoef;
}

/**
*\*\name   CRC_SetPolynomialSize.
*\*\fun    Configure size of the polynomial.
*\*\param  PolySize This parameter can be one of the following values:
*\*\         - CRC_POLYLENGTH_32B
*\*\         - CRC_POLYLENGTH_16B
*\*\         - CRC_POLYLENGTH_8B
*\*\         - CRC_POLYLENGTH_7B
*\*\return None
**/
void CRC_SetPolynomialSize(uint32_t PolySize)
{
    CRC->CTRL = ((CRC->CTRL & (~CRC_CTRL_POLYSIZE)) | PolySize);
}

/**
*\*\name   CRC_GetLRC.
*\*\fun    Return the computed LRC value.
*\*\param  None
*\*\return The computed LRC value
  */
uint32_t CRC_GetLRC(void)
{
    uint32_t temp;

    temp = CRC->LRC;
    return temp;
}

/**
*\*\name   CRC_GetIDAT.
*\*\fun    Return the data in independent data register.
*\*\param  None
*\*\return Data in independent data register.
**/
uint32_t CRC_GetIDAT(void)
{
    uint32_t temp;

    temp = CRC->IDAT;
    return temp;
}

/**
*\*\name   CRC_WriteIDAT.
*\*\fun    Write independent data register.
*\*\param  Idat : Value to be programmed in independent register
*\*\return None
**/
void CRC_WriteIDAT(uint32_t Idat)
{
    CRC->IDAT = Idat;
}

/**
*\*\name    CRC_Init.
*\*\fun     Initialize the CRC according to the specified parameters in the CRC_InitType.
*\*\param   CRC_InitStruct :
*\*\          - GeneratingPolynomial: The coefficients of the polynomial.
*\*\          - CRCLength
*\*\             - CRC_POLYLENGTH_32B
*\*\             - CRC_POLYLENGTH_16B
*\*\             - CRC_POLYLENGTH_8B
*\*\             - CRC_POLYLENGTH_7B
*\*\          - InitValue: 32-bit data
*\*\          - InputDataByteInversionMode
*\*\             - CRC_INDATA_BYTE_REVERSE_NONE
*\*\             - CRC_INDATA_BYTE_REVERSE_HALFWORD
*\*\             - CRC_INDATA_BYTE_REVERSE_WORD
*\*\          - InputDataBitInversionMode
*\*\             - CRC_INDATA_BIT_REVERSE_NONE
*\*\             - CRC_INDATA_BIT_REVERSE_BYTE
*\*\             - CRC_INDATA_BIT_REVERSE_HALFWORD
*\*\             - CRC_INDATA_BIT_REVERSE_WORD
*\*\          - OutputDataInversionMode
*\*\             - CRC_OUTPUTDATA_INVERSION_DISABLE
*\*\             - CRC_OUTPUTDATA_INVERSION_ENABLE
*\*\          - InputDataXor: 32-bit data
*\*\          - OutputDataXor: 32-bit data
*\*\return none
**/
void CRC_Init(CRC_InitType *CRC_InitStruct)
{
    /* Set generating polynomial defined by user */
    CRC_SetPolynomialSize(CRC_InitStruct->CRCLength);
    CRC_SetPolynomialCoef(CRC_InitStruct->GeneratingPolynomial);

    /* Set initial value defined by user */
    CRC_SetInitialData(CRC_InitStruct->InitValue);

    /* Set input data byte inversion mode */
    CRC_SetInputByteOrder(CRC_InitStruct->InputDataByteInversionMode);
    /* Set input data bit inversion mode */
    CRC_SetInputBitOrder(CRC_InitStruct->InputDataBitInversionMode);
    /* Set output data inversion mode */
    CRC_SetOutputBitOrder(CRC_InitStruct->OutputDataInversionMode);

    /* Set input data xor mode */
    CRC_SetInputDataXor(CRC_InitStruct->InputDataXor);
    /* Set output data xor mode */
    CRC_SetOutputDataXor(CRC_InitStruct->OutputDataXor);
}

/**
*\*\name   CRC_StructInit.
*\*\fun    Initialize the CRC structure
*\*\param  CRC_InitStruct
*\*\          - GeneratingPolynomial
*\*\          - CRCLength
*\*\          - InitValue
*\*\          - InputDataByteInversionMode
*\*\          - InputDataBitInversionMode
*\*\          - OutputDataInversionMode
*\*\          - InputDataXor
*\*\          - OutputDataXor
*\*\return none
**/
void CRC_StructInit(CRC_InitType *CRC_InitStruct)
{
    CRC_InitStruct->CRCLength = CRC_POLYLENGTH_32B;
    CRC_InitStruct->GeneratingPolynomial = DEFAULT_CRC32_POLY;
    CRC_InitStruct->InitValue = DEFAULT_CRC_INITVALUE;
    CRC_InitStruct->InputDataByteInversionMode = CRC_INDATA_BYTE_REVERSE_NONE;
    CRC_InitStruct->InputDataBitInversionMode = CRC_INDATA_BIT_REVERSE_NONE;
    CRC_InitStruct->OutputDataInversionMode = CRC_OUTDATA_REVERSE_NONE;
    CRC_InitStruct->InputDataXor = 0x00000000;
    CRC_InitStruct->OutputDataXor = 0x00000000;
}


/**
*\*\name   CRC_Handle_8
*\*\fun    Enter 8-bit input data to the CRC calculator.
*\*\param  pBuffer pointer to the input data buffer
*\*\param  BufferLength input data buffer length,count in Bytes
*\*\return 32-bit CRC result
*\*\note   If CRC length is shorter than 32-bits,LSBs is used.
**/
static uint32_t CRC_Handle_8( uint8_t *pBuffer, uint32_t BufferLength)
{
    uint32_t i;
    uint16_t data;
    __IO uint16_t *pReg;

    /* Processing time optimization: 4 bytes are entered in a row with a single word write,
     * last bytes must be carefully fed to the CRC calculator to ensure a correct type
     * handling by the peripheral */
    for (i = 0U; i < (BufferLength / 4U); i++)
    {
        CRC->DAT = ((uint32_t)pBuffer[4U * i] << 24U)         | \
                   ((uint32_t)pBuffer[(4U * i) + 1U] << 16U) | \
                   ((uint32_t)pBuffer[(4U * i) + 2U] << 8U)  | \
                   (uint32_t)pBuffer[(4U * i) + 3U];
    }

    /* last bytes specific handling */
    if ((BufferLength % 4U) != 0U)
    {
        if ((BufferLength % 4U) == 1U)
        {
            *(__IO uint8_t *)(__IO void *)(&CRC->DAT) = pBuffer[4U * i];         /* Derogation MisraC2012 R.11.5 */
        }

        if ((BufferLength % 4U) == 2U)
        {
            data = ((uint16_t)(pBuffer[4U * i]) << 8U) | (uint16_t)pBuffer[(4U * i) + 1U];
            pReg = (__IO uint16_t *)(__IO void *)(&CRC->DAT);                    /* Derogation MisraC2012 R.11.5 */
            *pReg = data;
        }

        if ((BufferLength % 4U) == 3U)
        {
            data = ((uint16_t)(pBuffer[4U * i]) << 8U) | (uint16_t)pBuffer[(4U * i) + 1U];
            pReg = (__IO uint16_t *)(__IO void *)(&CRC->DAT);                    /* Derogation MisraC2012 R.11.5 */
            *pReg = data;

            *(__IO uint8_t *)(__IO void *)(&CRC->DAT) = pBuffer[(4U * i) + 2U];  /* Derogation MisraC2012 R.11.5 */
        }
    }

    /* Return the CRC computed value */
    return CRC->DAT;
}

/**
*\*\name   CRC_Handle_16
*\*\fun    Enter 16-bit input data to the CRC calculator.
*\*\param  pBuffer pointer to the input data buffer
*\*\param  BufferLength input data buffer length,count in Half-words
*\*\return 32-bit CRC result
*\*\note   If CRC length is shorter than 32-bits,LSBS is used.
**/
static uint32_t CRC_Handle_16(uint16_t *pBuffer, uint32_t BufferLength)
{
    uint32_t i;  /* input data buffer index */
    __IO uint16_t *pReg;

    /* Processing time optimization: 2 HalfWords are entered in a row with a single word write,
     * in case of odd length, last HalfWord must be carefully fed to the CRC calculator to ensure
     * a correct type handling by the peripheral */
    for (i = 0U; i < (BufferLength / 2U); i++)
    {
        CRC->DAT = ((uint32_t)pBuffer[2U * i] << 16U) | (uint32_t)pBuffer[(2U * i) + 1U];
    }

    if ((BufferLength % 2U) != 0U)
    {
        pReg = (__IO uint16_t *)(__IO void *)(&CRC->DAT);                 /* Derogation MisraC2012 R.11.5 */
        *pReg = pBuffer[2U * i];
    }

    /* Return the CRC computed value */
    return CRC->DAT;
}

/**
*\*\name   CRC_Accumulate
*\*\fun    Compute the 7, 8, 16 or 32-bit CRC value of an 8, 16 or 32-bit data buffer
*\*\       starting with the previously computed CRC result as initialization value.
*\*\param  InputDataFormat
*\*\          - CRC_INPUTDATA_FORMAT_WORDS
*\*\          - CRC_INPUTDATA_FORMAT_BYTES
*\*\          - CRC_INPUTDATA_FORMAT_HALFWORDS
*\*\param  pBuffer pointer to the input data buffer, exact input data format is
*\*\        provided by InputDataFormat.
*\*\param  BufferLength input data buffer length,and:
*\*\          - if InputDataFormat is CRC_INPUTDATA_FORMAT_WORDS,count in words(32bit)
*\*\          - if InputDataFormat is CRC_INPUTDATA_FORMAT_BYTES,count in bytes(8bit)
*\*\          - if InputDataFormat is CRC_INPUTDATA_FORMAT_HALFWORDS,count in half-words(16bit)
*\*\return 32-bit CRC result
*\*\note   If the length of CRC result is shorter than 32-bits,only LSB is used.
**/
uint32_t CRC_Accumulate(uint32_t InputDataFormat, void *pBuffer, uint32_t BufferLength)
{
    uint32_t i;
    uint32_t temp = 0U;
    uint32_t *pWord;

    switch (InputDataFormat)
    {
        case CRC_INPUTDATA_FORMAT_WORDS:
            pWord = (uint32_t *)pBuffer;

            /* Enter 32-bit input data to the CRC calculator */
            for (i = 0U; i < BufferLength; i++)
            {
                CRC->DAT = pWord[i];
            }

            temp = CRC->DAT;
            break;

        case CRC_INPUTDATA_FORMAT_BYTES:
            /* Specific 8-bit input data handling  */
            temp = CRC_Handle_8((uint8_t *)pBuffer, BufferLength);
            break;

        case CRC_INPUTDATA_FORMAT_HALFWORDS:
            /* Specific 16-bit input data handling  */
            temp = CRC_Handle_16( (uint16_t *)(void *)pBuffer, BufferLength);    /* Derogation MisraC2012 R.11.5 */
            break;

        default:
            break;
    }

    /* Return the CRC computed value */
    return temp;
}

/**
*\*\name   CRC_Calculate
*\*\fun    Compute the 7, 8, 16 or 32-bit CRC value of an 8, 16 or 32-bit data buffer
*\*\        starting with CRC_INIT as initialization value.
*\*\param  InputDataFormat
*\*\          - CRC_INPUTDATA_FORMAT_WORDS
*\*\          - CRC_INPUTDATA_FORMAT_BYTES
*\*\          - CRC_INPUTDATA_FORMAT_HALFWORDS
*\*\param  pBuffer pointer to the input data buffer, exact input data format is
*\*\        provided by InputDataFormat.
*\*\param  BufferLength input data buffer length,and:
*\*\          - if InputDataFormat is CRC_INPUTDATA_FORMAT_WORDS,count in words(32bit)
*\*\          - if InputDataFormat is CRC_INPUTDATA_FORMAT_BYTES,count in bytes(8bit)
*\*\          - if InputDataFormat is CRC_INPUTDATA_FORMAT_HALFWORDS,count in half-words(16bit)
*\*\return 32-bit CRC result
*\*\note   If the length of CRC result is shorter than 32-bits,only LSB is used.
**/
uint32_t CRC_Calculate(uint32_t InputDataFormat, void *pBuffer, uint32_t BufferLength)
{
    /* Reset CRC Calculation Unit (CRC_INIT is written in CRC_DAT) */
    CRC_ResetCalculation();

    /* Return the CRC computed value */
    return (CRC_Accumulate(InputDataFormat, pBuffer, BufferLength));
}

