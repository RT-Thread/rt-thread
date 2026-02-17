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
 * @file n32h76x_78x_fmac.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_fmac.h"
#include "n32h76x_78x_rcc.h"

#ifndef NULL
    #define NULL          0
#endif

/**
*\*\name    FMAC_DeInit.
*\*\fun     Deinitializes the FMAC peripheral registers to their default reset values
*\*\param   none
*\*\return  none
**/
void FMAC_DeInit(void)
{
    /* Enable FMAC reset state */
    RCC_EnableAHB2PeriphReset1(RCC_AHB2_PERIPHRST_FMAC);
}

/**
*\*\name    FMAC_Init.
*\*\fun     Initialize the FMAC peripheral
*\*\param   FMAC_InitStruct :
*\*\            - InputBufBaseAddress
*\*\                - 0...255
*\*\            - InputBufSize
*\*\                - 0...255
*\*\            - InputBufThreshold
*\*\                - FMAC_THRESHOLD1
*\*\                - FMAC_THRESHOLD2
*\*\                - FMAC_THRESHOLD4
*\*\                - FMAC_THRESHOLD8
*\*\            - CoeffBufBaseAddress
*\*\                - 0...255
*\*\            - CoeffBufSize
*\*\                - 0...255
*\*\            - OutBufBaseAddress
*\*\                - 0...255
*\*\            - OutBufSize
*\*\                - 0...255
*\*\            - OutBufThreshold
*\*\                - FMAC_THRESHOLD1
*\*\                - FMAC_THRESHOLD2
*\*\                - FMAC_THRESHOLD4
*\*\                - FMAC_THRESHOLD8
*\*\            - Limit
*\*\                - FMAC_LIMIT_ENABLE
*\*\                - FMAC_LIMIT_DISABLE
*\*\            - Func
*\*\                - FMAC_FUNC_LOADX1
*\*\                - FMAC_FUNC_LOADX2
*\*\                - FMAC_FUNC_LOADY
*\*\                - FMAC_FUNC_CONVO_FIR
*\*\                - FMAC_FUNC_IIR_DIRECT_FORM_1
*\*\            - P.
*\*\                - 0...255
*\*\            - Q.
*\*\                - 0...255
*\*\            - R.
*\*\                - 0...255
*\*\return  none
**/
void FMAC_Init(FMAC_InitType * FMAC_InitStruct)
{
    /* configure the input buffer parameter  */
    FMAC->X1BUFCFG = ((((uint32_t)FMAC_InitStruct->InputBufBaseAddress) & FMAC_X1BUFCFG_X1BASE)     \
                      | ((((uint32_t)FMAC_InitStruct->InputBufSize) << REG_BIT8_OFFSET) & FMAC_X1BUFCFG_X1BUFSIZE) \
                      | (FMAC_InitStruct->InputBufThreshold & FMAC_X1BUFCFG_X1BUFWM)  );

    /* configure the coefficient parameter */
    FMAC->X2BUFCFG = ((((uint32_t)FMAC_InitStruct->CoeffBufBaseAddress) & FMAC_X2BUFCFG_X2BASE)     \
                      | ((((uint32_t)FMAC_InitStruct->CoeffBufSize) << REG_BIT8_OFFSET) & FMAC_X2BUFCFG_X2BUFSIZE));

    /* configure the output buffer parameter  */
    FMAC->YBUFCFG =  ((((uint32_t)FMAC_InitStruct->OutBufBaseAddress) & FMAC_YBUFCFG_YBASE)  \
                      | ((((uint32_t)FMAC_InitStruct->OutBufSize) << REG_BIT8_OFFSET) & FMAC_YBUFCFG_YBUFSIZE) \
                      | (FMAC_InitStruct->OutBufThreshold & FMAC_YBUFCFG_YBUFWM) );

    /* configure the state of limit */
    if(FMAC_InitStruct->Limit == FMAC_LIMIT_ENABLE)
    {
        FMAC->CTRL |= FMAC_CTRL_LIMITEN;
    }
    else
    {
        FMAC->CTRL &= ~FMAC_CTRL_LIMITEN;
    }
}

/**
*\*\name    FMAC_StructInit.
*\*\fun     Initialize the FMAC filter parameter struct with the default values
*\*\param   FMAC_InitStruct :
*\*\            - InputBufBaseAddress
*\*\            - InputBufSize
*\*\            - InputBufThreshold
*\*\            - CoeffBufBaseAddress
*\*\            - CoeffBufSize
*\*\            - OutBufBaseAddress
*\*\            - OutBufSize
*\*\            - OutBufThreshold
*\*\            - Limit
*\*\            - Func
*\*\            - P
*\*\            - Q
*\*\            - R
*\*\return  none
**/
void FMAC_StructInit(FMAC_InitType * FMAC_InitStruct)
{
    FMAC_InitStruct->InputBufBaseAddress       = 0U;
    FMAC_InitStruct->InputBufSize              = 0U;
    FMAC_InitStruct->InputBufThreshold         = 0U;
    FMAC_InitStruct->CoeffBufBaseAddress       = 0U;
    FMAC_InitStruct->CoeffBufSize              = 0U;
    FMAC_InitStruct->OutBufBaseAddress         = 0U;
    FMAC_InitStruct->OutBufSize                = 0U;
    FMAC_InitStruct->OutBufThreshold           = 0U;
    FMAC_InitStruct->Limit                     = 0U;
    FMAC_InitStruct->Func                      = 0U;
    FMAC_InitStruct->P                         = 0U;
    FMAC_InitStruct->Q                         = 0U;
    FMAC_InitStruct->R                         = 0U;
}

/**
*\*\name    FMAC_PreLoadData.
*\*\fun     Preload data
*\*\param   size :
*\*\            - 0~255  size of data
*\*\param   array[]:
*\*\            - pointer to the buffer containing the data to be loaded
*\*\return  none
**/
void FMAC_PreLoadData(uint32_t size, int16_t array[])
{
    uint32_t i;

    for(i = 0U; i < size; i++)
    {
        FMAC->WDAT = (uint32_t)array[i] & FMAC_WDAT_WDAT;
    }
}

/**
*\*\name    FMAC_PreloadBufferData.
*\*\fun     Preload three buffer data
*\*\param   FMAC_PreloadStruct :
*\*\            - pInputData :
*\*\                - pointer to the input buffer containing the data to be computed
*\*\            - InputDataSize :
*\*\                - 0..255
*\*\            - pCoeffA :
*\*\                - pointer to the buffer containing the data to be computed
*\*\            - CoeffASize :
*\*\                - 0..255
*\*\            - pCoeffB :
*\*\                - pointer to the buffer containing the data to be computed
*\*\            - CoeffBSize :
*\*\                - 0..255
*\*\            - pOutputData :
*\*\                - pointer to the output buffer containing the data to be computed
*\*\            - OutputDataSize :
*\*\                - 0..255
*\*\return  ErrorStatus:
*\*\         - SUCCESS    FMAC preload success
*\*\         - ERROR      FMAC preload timeout
**/
ErrorStatus FMAC_PreloadBufferData(FMAC_PreLoadType * FMAC_PreloadStruct)
{
    uint32_t timeout;
    ErrorStatus status = SUCCESS;

    if((NULL != FMAC_PreloadStruct->pInputData) && (0U != FMAC_PreloadStruct->InputDataSize))
    {
        /* configure parameter of filter preload */
        FMAC->PARAMCFG = ((uint32_t)(FMAC_PreloadStruct->InputDataSize) & FMAC_PARAMCFG_P) \
                         | FMAC_FUNC_LOADX1  \
                         | FMAC_PARAMCFG_START;

        /* load the X1 buffer for input data */
        FMAC_PreLoadData(FMAC_PreloadStruct->InputDataSize, FMAC_PreloadStruct->pInputData);

        timeout = FMAC_TIMEOUT;

        while((FMAC->PARAMCFG & FMAC_PARAMCFG_START) != 0U)
        {
            if(0U == timeout)
            {
                status = ERROR;
                break;
            }

            timeout--;
        }
    }

    if(ERROR == status)
    {
    }
    else if((NULL != FMAC_PreloadStruct->pCoeffB) && (0U != FMAC_PreloadStruct->CoeffBSize))
    {
        /* configure parameter of filter preload */
        FMAC->PARAMCFG = (((uint32_t)FMAC_PreloadStruct->CoeffBSize) & FMAC_PARAMCFG_P)     \
                         | ((((uint32_t)FMAC_PreloadStruct->CoeffASize) << REG_BIT8_OFFSET) & FMAC_PARAMCFG_Q)     \
                         | FMAC_FUNC_LOADX2      \
                         | FMAC_PARAMCFG_START;
        /* load the X2 buffer for cofficientB */
        FMAC_PreLoadData(FMAC_PreloadStruct->CoeffBSize, FMAC_PreloadStruct->pCoeffB);


        /* load the x2 buffer for cofficientA */
        if((NULL != FMAC_PreloadStruct->pCoeffA) && (0U != FMAC_PreloadStruct->CoeffASize))
        {
            /* Load the buffer into the internal memory */
            FMAC_PreLoadData(FMAC_PreloadStruct->CoeffASize, FMAC_PreloadStruct->pCoeffA);
        }

        timeout = FMAC_TIMEOUT;

        while((FMAC->PARAMCFG & FMAC_PARAMCFG_START) != 0U)
        {
            if(0U == timeout)
            {
                status = ERROR;
                break;
            }

            timeout--;
        }
    }
    else
    {
    }

    if(ERROR == status)
    {
    }
    else if((NULL != FMAC_PreloadStruct->pOutputData) && (0U != FMAC_PreloadStruct->OutputDataSize)) /* configure to preload output buffer */
    {
        FMAC->PARAMCFG = ((uint32_t)FMAC_PreloadStruct->OutputDataSize & FMAC_PARAMCFG_P)   \
                         | FMAC_FUNC_LOADY   \
                         | FMAC_PARAMCFG_START;

        /* load the Y buffer for input data */
        FMAC_PreLoadData(FMAC_PreloadStruct->OutputDataSize, FMAC_PreloadStruct->pOutputData);

        timeout = FMAC_TIMEOUT;

        while((FMAC->PARAMCFG & FMAC_PARAMCFG_START) != 0U)
        {
            if(0U == timeout)
            {
                status = ERROR;
                break;
            }

            timeout--;
        }
    }
    else
    {

    }

    return status;
}

/**
*\*\name    FMAC_PreLoadStructInit.
*\*\fun     Initialize the FMAC Preload struct with the default values
*\*\param   FMAC_PreloadStruct :
*\*\            - pInputData
*\*\            - InputDataSize
*\*\            - pCoeffA
*\*\            - CoeffASize
*\*\            - pCoeffB
*\*\            - CoeffBSize
*\*\            - pOutputData
*\*\            - OutputDataSize
*\*\return  none
**/
void FMAC_PreLoadStructInit(FMAC_PreLoadType * FMAC_PreloadStruct)
{
    FMAC_PreloadStruct->pInputData          = 0U;
    FMAC_PreloadStruct->InputDataSize       = 0U;
    FMAC_PreloadStruct->pCoeffA             = 0U;
    FMAC_PreloadStruct->CoeffASize          = 0U;
    FMAC_PreloadStruct->pCoeffB             = 0U;
    FMAC_PreloadStruct->CoeffBSize          = 0U;
    FMAC_PreloadStruct->pOutputData         = 0U;
    FMAC_PreloadStruct->OutputDataSize      = 0U;
}

/**
*\*\name    FMAC_ConfigParam.
*\*\fun     Configure FMAC parameter
*\*\param   FMAC_ParamStruct :
*\*\            - Func
*\*\                - FMAC_FUNC_LOADX1
*\*\                - FMAC_FUNC_LOADX2
*\*\                - FMAC_FUNC_LOADY
*\*\                - FMAC_FUNC_CONVO_FIR
*\*\                - FMAC_FUNC_IIR_DIRECT_FORM_1
*\*\            - P
*\*\                - 0..255
*\*\            - Q
*\*\                - 0..255
*\*\            - R
*\*\                - 0..7
*\*\return  none
**/
void FMAC_ConfigParam(FMAC_InitType* FMAC_ParamStruct)
{
    /* Stop execution */
    FMAC->PARAMCFG &= (~FMAC_PARAMCFG_START);

    /* Set filter parameter */
    FMAC->PARAMCFG =   FMAC_ParamStruct->Func                               \
                       | ((uint32_t)FMAC_ParamStruct->P)                       \
                       | (((uint32_t)FMAC_ParamStruct->Q) << REG_BIT8_OFFSET)  \
                       | (((uint32_t)FMAC_ParamStruct->R) << REG_BIT16_OFFSET);
}

/**
*\*\name    FMAC_FilterStart.
*\*\fun     Configure FMAC parameter and start filter
*\*\param   FMAC_ParamStruct :
*\*\            - Func
*\*\                - FMAC_FUNC_LOADX1
*\*\                - FMAC_FUNC_LOADX2
*\*\                - FMAC_FUNC_LOADY
*\*\                - FMAC_FUNC_CONVO_FIR
*\*\                - FMAC_FUNC_IIR_DIRECT_FORM_1
*\*\            - P
*\*\                - 0..255
*\*\            - Q
*\*\                - 0..255
*\*\            - R
*\*\                - 0..7
*\*\return  none
**/
void FMAC_FilterStart(FMAC_InitType* FMAC_ParamStruct)
{
    /* Stop execution */
    FMAC->PARAMCFG &= (~FMAC_PARAMCFG_START);

    /* Set filter parameter and start execution */
    FMAC->PARAMCFG =   FMAC_PARAMCFG_START                                  \
                       |  FMAC_ParamStruct->Func                               \
                       | ((uint32_t)FMAC_ParamStruct->P)                       \
                       | (((uint32_t)FMAC_ParamStruct->Q) << REG_BIT8_OFFSET)  \
                       | (((uint32_t)FMAC_ParamStruct->R) << REG_BIT16_OFFSET);
}

/**
*\*\name    FMAC_Reset.
*\*\fun     Reset FMAC, The write and read pointers, internal control logic,FAC_STS and FAC_PARAMCFG register is set to default value.
*\*\param   none
*\*\return  ErrorStatus:
*\*\         - SUCCESS    FMAC reset done
*\*\         - ERROR      FMAC reset timeout
**/
ErrorStatus FMAC_Reset(void)
{
    uint32_t timeout = FMAC_RESET_TIMEOUT_VALUE;
    ErrorStatus status = SUCCESS;

    /* Reset FMAC peripheral */
    FMAC->CTRL |= FMAC_CTRL_RESET;

    while((FMAC->CTRL & FMAC_CTRL_RESET) != 0U)
    {
        if(0U == timeout)
        {
            status = ERROR;
            break;
        }

        timeout--;
    }

    return status;
}

/**
*\*\name    FMAC_Enable.
*\*\fun     Enable or disable FMAC start execution.
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FMAC_Enable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected FMAC peripheral */
        FMAC->PARAMCFG |= FMAC_PARAMCFG_START;
    }
    else
    {
        /* Disable the selected FMAC peripheral */
        FMAC->PARAMCFG  &= ~FMAC_PARAMCFG_START;
    }
}

/**
*\*\name    FMAC_ConfigX1.
*\*\fun     Configuration X1 paramer.
*\*\param   Baseaddr
*\*\          - 0...255
*\*\param   Bufsize
*\*\          - 0...255
*\*\param   Threshold
*\*\          - FMAC_THRESHOLD1
*\*\          - FMAC_THRESHOLD2
*\*\          - FMAC_THRESHOLD4
*\*\          - FMAC_THRESHOLD8
*\*\return  none
**/
void FMAC_ConfigX1(uint8_t Baseaddr, uint8_t Bufsize, uint32_t Threshold)
{
    FMAC->X1BUFCFG = (uint32_t)Baseaddr | Threshold | ((uint32_t)Bufsize << REG_BIT8_OFFSET);
}

/**
*\*\name    FMAC_ConfigX2.
*\*\fun     Configuration X2 paramer.
*\*\param   Baseaddr
*\*\          - 0...255
*\*\param   Bufsize
*\*\          - 0...255
*\*\return  none
**/
void FMAC_ConfigX2(uint8_t Baseaddr, uint8_t Bufsize)
{
    FMAC->X2BUFCFG = (uint32_t)Baseaddr | ((uint32_t)Bufsize << REG_BIT8_OFFSET);
}

/**
*\*\name    FMAC_ConfigY.
*\*\fun     Configuration Y paramer.
*\*\param   Baseaddr
*\*\          - 0...255
*\*\param   Bufsize
*\*\          - 0...255
*\*\param   Threshold
*\*\          - FMAC_THRESHOLD1
*\*\          - FMAC_THRESHOLD2
*\*\          - FMAC_THRESHOLD4
*\*\          - FMAC_THRESHOLD8
*\*\return  none
**/
void FMAC_ConfigY(uint8_t Baseaddr, uint8_t Bufsize, uint32_t Threshold)
{
    FMAC->YBUFCFG = (uint32_t)Baseaddr | Threshold | ((uint32_t)Bufsize << REG_BIT8_OFFSET);
}

/**
*\*\name    FMAC_WriteData
*\*\fun     Write data
*\*\param   none
*\*\return  16-bit data
**/
void FMAC_WriteData(int16_t data)
{
    FMAC->WDAT = (uint32_t)data;
}

/**
*\*\name    FMAC_ReadData
*\*\fun     Read output data
*\*\param   none
*\*\return  16-bit data
**/
int16_t FMAC_ReadData(void)
{
    int16_t value;
    value = (int16_t)FMAC->RDAT;
    return value;
}

/**
*\*\name    FMAC_EnableLimit
*\*\fun     Enable or disable fmac limit
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FMAC_EnableLimit(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        FMAC->CTRL |= FMAC_LIMIT_ENABLE;
    }
    else
    {
        FMAC->CTRL &= ~FMAC_LIMIT_ENABLE;
    }
}

/**
*\*\name    FMAC_EnableDma
*\*\fun     Enable or disable fmac dma
*\*\param   dma_req :
*\*\            - FMAC_DMA_READ: read buffer dma
*\*\            - FMAC_DMA_WRITE: write buffer dma
*\*\param   Cmd :
*\*\            - ENABLE
*\*\            - DISABLE
*\*\return  none
**/
void FMAC_EnableDMA(uint32_t dma_req, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        FMAC->CTRL |= dma_req;
    }
    else
    {
        FMAC->CTRL &= ~dma_req;
    }
}

/**
*\*\name    FMAC_ConfigInt
*\*\fun     Enable or disable fmac interrupt
*\*\param   interrupt :
*\*\            - FMAC_INT_READ: Read buffer interrupt
*\*\            - FMAC_INT_WRITE: Write buffer interrupt
*\*\            - FMAC_INT_OV: Overflow error interrupt
*\*\            - FMAC_INT_UN: Underflow error interrupt
*\*\            - FMAC_INT_SAT: Saturation error interrupt
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FMAC_ConfigInt(uint32_t interrupt, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        FMAC->CTRL |= interrupt;
    }
    else
    {
        FMAC->CTRL &= ~interrupt;
    }
}

/**
*\*\name    FMAC_FinishCalculate.
*\*\fun     finish the filter calculate
*\*\param   none
*\*\return  none
**/
ErrorStatus FMAC_FinishCalculate(void)
{
    ErrorStatus err;

    /* clear start */
    FMAC->PARAMCFG  &= ~FMAC_PARAMCFG_START;

    /* disable read and write interrupt */
    CLEAR_BIT(FMAC->CTRL, FMAC_INT_READ | FMAC_INT_WRITE | FMAC_DMA_READ | FMAC_DMA_WRITE);

    /* reset register and pointer */
    if(FMAC_Reset() != SUCCESS)
    {
        err = ERROR;
    }
    else
    {
        err = SUCCESS;
    }

    return err;
}

/**
*\*\name    FMAC_GetIntStatus
*\*\fun     FMAC interrupt flag status
*\*\param   IntFlag :
*\*\            - FMAC_INT_FLAG_YBUFEF: Read buffer interrupt
*\*\            - FMAC_INT_FLAG_X1BUFFF: Write buffer interrupt
*\*\            - FMAC_INT_FLAG_OVF: Overflow error interrupt
*\*\            - FMAC_INT_FLAG_UNF: Underflow error interrupt
*\*\            - FMAC_INT_FLAG_SATF: Saturation error interrupt
*\*\return  none
**/
FlagStatus FMAC_GetIntStatus(uint32_t IntFlag)
{
    FlagStatus bitstatus;
    uint32_t tReg;

    if(  (FMAC_INT_FLAG_YBUFEF == IntFlag)  \
            || (FMAC_INT_FLAG_X1BUFFF == IntFlag) )
    {
        tReg = ~(FMAC->STS);
    }
    else
    {
        tReg = FMAC->STS;
    }

    tReg &= (IntFlag & FMAC_INT_FLAG_MASK);

    if(tReg == 0U)
    {
        bitstatus = RESET;
    }
    else if((FMAC->CTRL & ((IntFlag >> 16U) & FMAC_INT_FLAG_MASK)) == 0U)
    {
        bitstatus = RESET;
    }
    else
    {
        bitstatus = SET;
    }

    return bitstatus;
}

/**
*\*\name    FMAC_GetFlagStatus
*\*\fun     Get FMAC flag status
*\*\param   Flag :
*\*\            - FMAC_FLAG_YBUFEF: Read buffer interrupt
*\*\            - FMAC_FLAG_X1BUFFF: Write buffer interrupt
*\*\            - FMAC_FLAG_OVF: Overflow error interrupt
*\*\            - FMAC_FLAG_UNF: Underflow error interrupt
*\*\            - FMAC_FLAG_SATF: Saturation error interrupt
*\*\return  FlagStatus:
*\*\            - SET
*\*\            - RESET
**/
FlagStatus FMAC_GetFlagStatus(uint32_t Flag)
{
    FlagStatus bitstatus;

    if ((FMAC->STS & Flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}





