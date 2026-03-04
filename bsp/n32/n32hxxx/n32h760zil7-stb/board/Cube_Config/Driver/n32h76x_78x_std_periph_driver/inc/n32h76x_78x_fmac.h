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
 * @file n32h76x_78x_fmac.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#ifndef __N32H76X_78X_FMAC_H
#define __N32H76X_78X_FMAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h76x_78x.h"

/**  FMAC Init structure definition **/

typedef struct
{
    uint8_t  InputBufBaseAddress;     /* Base address of the input buffer (X1) within the internal memory (0x00 to 0xFF) */
      
    uint8_t  InputBufSize;            /* Number of 16-bit words allocated to the input buffer (including the optional "headroom")*/
      
    uint8_t  CoeffBufBaseAddress;     /* Base address of the coefficient buffer (X2) within the internal memory (0x00 to 0xFF)*/
      
    uint8_t  CoeffBufSize;            /* Number of 16-bit words allocated to the coefficient buffer */
      
    uint8_t  OutBufBaseAddress;       /* Base address of the output buffer (Y) within the internal memory (0x00 to 0xFF). */
      
    uint8_t  OutBufSize;              /* Number of 16-bit words allocated to the output buffer (including the optional "headroom") */
      
    uint8_t  P;                       /* Parameter P (vector length, number of filter taps, etc.) */
      
    uint8_t  Q;                       /* Parameter Q (vector length, etc.). Ignored if not needed */
      
    uint8_t  R;                       /* Parameter R (gain, etc.). Ignored if not needed. */

    uint32_t InputBufThreshold;       /* Input threshold: the buffer full flag will be set if the number of free spaces in the buffer is lower than this threshold*/

    uint32_t OutBufThreshold;         /* Output threshold: the buffer empty flag will be set if the number of unread values */
      
    uint32_t Limit;                   /* Enable or disable the limit feature */

    uint32_t Func;                    /* Filter type */
} FMAC_InitType;

/**  FMAC preload buffer parameters structure definition **/
typedef struct
{
    int16_t *pInputData;        /* content of the input data */
    uint8_t InputDataSize;      /* Size of the input data */

    int16_t *pCoeffA;           /* [IIR only] Initialization of the coefficient vector A. If not needed, it should be set to NULL. */
    uint8_t CoeffASize;         /* Size of the coefficient vector A. */
    int16_t *pCoeffB;           /* Initialization of the coefficient vector B. If not needed (re-use of a previously loaded buffer), it should be set to NULL. */
    uint8_t CoeffBSize;         /* Size of the coefficient vector B. */
    int16_t *pOutputData;       /* content of the output data */
    uint8_t OutputDataSize;     /* size of the output data */
} FMAC_PreLoadType;

/* Function define  */
#define FMAC_FUNC_LOADX1                ((uint32_t)0x01000000U) /* Load X1 buffer */
#define FMAC_FUNC_LOADX2                ((uint32_t)0x02000000U) /* Load X2 buffer */
#define FMAC_FUNC_LOADY                 ((uint32_t)0x03000000U) /* Load Y buffer  */
#define FMAC_FUNC_CONVO_FIR             ((uint32_t)0x08000000U) /* Convolution (FIR filter)   */
#define FMAC_FUNC_IIR_DIRECT_FORM_1     ((uint32_t)0x09000000U) /* IIR filter (direct form 1)  */

/* Buffer threshold define, used for X1 buffer and Y buffer */
#define FMAC_THRESHOLD1                 ((uint32_t)0x00000000U) /* Input: Buffer full flag set if the number of free spaces in the buffer is less than 1.
                                                                   Output: Buffer empty flag set if the number of unread values in the buffer is less than 1. */
#define FMAC_THRESHOLD2                 ((uint32_t)0x01000000U) /* Input: Buffer full flag set if the number of free spaces in the buffer is less than 2.
                                                                   Output: Buffer empty flag set if the number of unread values in the buffer is less than 2. */
#define FMAC_THRESHOLD4                 ((uint32_t)0x02000000U) /* Input: Buffer full flag set if the number of free spaces in the buffer is less than 4.
                                                                   Output: Buffer empty flag set if the number of unread values in the buffer is less than 4. */
#define FMAC_THRESHOLD8                 ((uint32_t)0x03000000U) /* Input: Buffer full flag set if the number of free spaces in the buffer is less than 8.
                                                                   Output: Buffer empty flag set if the number of unread values in the buffer is less than 8. */

/* Data limit define */
#define FMAC_LIMIT_DISABLE              ((uint32_t)0x00000000U) /* Limit disabled */
#define FMAC_LIMIT_ENABLE               FMAC_CTRL_LIMITEN       /* Limit enabled */

/* FMAC flag definitions */  
#define FMAC_FLAG_YBUFEF                FMAC_STS_YBUFEF     /* Y buffer empty flag */
#define FMAC_FLAG_X1BUFFF               FMAC_STS_X1BUFFF    /* X1 buffer full flag */
#define FMAC_FLAG_OVF                   FMAC_STS_OVF        /* Overflow error flag */
#define FMAC_FLAG_UNF                   FMAC_STS_UNF        /* Underflow error flag */
#define FMAC_FLAG_SATF                  FMAC_STS_SATF       /* Saturation error flag */

/* FMAC interrupt definitions */  
#define FMAC_INT_READ                   FMAC_CTRL_RINTEN    /* Enable read interrupt */
#define FMAC_INT_WRITE                  FMAC_CTRL_WIINEN    /* Enable write interrupt */
#define FMAC_INT_OV                     FMAC_CTRL_OVINTEN   /* Enable overflow error interrupts */
#define FMAC_INT_UN                     FMAC_CTRL_UNINTEN   /* Enable underflow error interrupts */
#define FMAC_INT_SAT                    FMAC_CTRL_SATINTEN  /* Enable saturation error interrupts */  

/* FMAC DMA mdoe definitions */          
#define FMAC_DMA_READ                   FMAC_CTRL_DMAREN    /* Enable DMA read channel requests */
#define FMAC_DMA_WRITE                  FMAC_CTRL_DMAWEN    /* Enable DMA write channel requests */

/* FMAC interrupt flag definitions */
#define FMAC_INT_FLAG_YBUFEF            ((FMAC_INT_READ  << 16U) | FMAC_FLAG_YBUFEF)    /* Y buffer empty interrupt flag */
#define FMAC_INT_FLAG_X1BUFFF           ((FMAC_INT_WRITE << 16U) | FMAC_FLAG_X1BUFFF)   /* X1 buffer full interrupt flag */
#define FMAC_INT_FLAG_OVF               ((FMAC_INT_OV    << 16U) | FMAC_FLAG_OVF)       /* Overflow error interrupt flag */
#define FMAC_INT_FLAG_UNF               ((FMAC_INT_UN    << 16U) | FMAC_FLAG_UNF)       /* underflow error interrupt flag */
#define FMAC_INT_FLAG_SATF              ((FMAC_INT_SAT   << 16U) | FMAC_FLAG_SATF)      /* saturation error interrupt flag */
#define FMAC_INT_FLAG_MASK              ((uint32_t)0x0000FFFF)

/* FMAC polling-based communications time-out value */
#define FMAC_TIMEOUT                    (400000000U)
/* FMAC reset time-out value */
#define FMAC_RESET_TIMEOUT_VALUE        (200000000U)

void FMAC_DeInit(void);
void FMAC_StructInit(FMAC_InitType * FMAC_InitStruct);
void FMAC_PreLoadStructInit(FMAC_PreLoadType * FMAC_PreloadStruct);
void FMAC_Init(FMAC_InitType * FMAC_InitStruct);
void FMAC_PreLoadData(uint32_t size, int16_t array[]);
ErrorStatus FMAC_PreloadBufferData(FMAC_PreLoadType * FMAC_PreloadStruct);
void FMAC_ConfigParam(FMAC_InitType* FMAC_ParamStruct);
void FMAC_FilterStart(FMAC_InitType* FMAC_ParamStruct);
ErrorStatus FMAC_Reset(void);
void FMAC_Enable(FunctionalState Cmd);
void FMAC_ConfigX1(uint8_t Baseaddr, uint8_t Bufsize, uint32_t Threshold);
void FMAC_ConfigX2(uint8_t Baseaddr, uint8_t Bufsize);
void FMAC_ConfigY(uint8_t Baseaddr, uint8_t Bufsize, uint32_t Threshold);
void FMAC_WriteData(int16_t data);
int16_t FMAC_ReadData(void);
void FMAC_EnableLimit(FunctionalState Cmd);
void FMAC_EnableDMA(uint32_t dma_req, FunctionalState Cmd);
ErrorStatus FMAC_FinishCalculate(void);
void FMAC_ConfigInt(uint32_t interrupt, FunctionalState Cmd);
FlagStatus FMAC_GetIntStatus(uint32_t FMAC_INT);
FlagStatus FMAC_GetFlagStatus(uint32_t FMAC_FLAG);


#ifdef __cplusplus
}
#endif

#endif /* __N32H76X_78X_FMAC_H */


