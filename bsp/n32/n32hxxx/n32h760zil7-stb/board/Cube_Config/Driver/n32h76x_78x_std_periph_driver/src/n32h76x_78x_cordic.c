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
 * @file n32h76x_78x_cordic.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_cordic.h"
#include "n32h76x_78x_rcc.h"

/** CORDIC Private Defines **/

#define CORDIC_CTRLSTS_MASK                         ((uint32_t)0x07F807FFU)


/** CORDIC Driving Functions Declaration **/

/**
*\*\name    CORDIC_DeInit.
*\*\fun     DeInitializes the CORDIC peripheral.
*\*\param   none
*\*\return  none
**/
void CORDIC_DeInit(void)
{
    /* CORDIC peripheral reset */
    RCC_EnableAHB2PeriphReset1(RCC_AHB2_PERIPHRST_CORDIC);
}

/**
*\*\name    CORDIC_Init.
*\*\fun     Initialize the CORDIC module with CORDIC_InitParam of type CORDIC_InitType.
*\*\param   CORDIC_InitParam :
*\*\          - Function
*\*\            - CORDIC_FUNCTION_COSINE
*\*\            - CORDIC_FUNCTION_SINE
*\*\            - CORDIC_FUNCTION_PHASE
*\*\            - CORDIC_FUNCTION_MODULUS
*\*\            - CORDIC_FUNCTION_ARCTANGENT
*\*\            - CORDIC_FUNCTION_HCOSINE
*\*\            - CORDIC_FUNCTION_HSINE
*\*\            - CORDIC_FUNCTION_HARCTANGENT
*\*\            - CORDIC_FUNCTION_NATURALLOG
*\*\            - CORDIC_FUNCTION_SQUAREROOT
*\*\          - Precision
*\*\            - CORDIC_PRECISION_1CYCLE
*\*\            - CORDIC_PRECISION_2CYCLES
*\*\            - CORDIC_PRECISION_3CYCLES
*\*\            - CORDIC_PRECISION_4CYCLES
*\*\            - CORDIC_PRECISION_5CYCLES
*\*\            - CORDIC_PRECISION_6CYCLES
*\*\            - CORDIC_PRECISION_7CYCLES
*\*\            - CORDIC_PRECISION_8CYCLES
*\*\            - CORDIC_PRECISION_9CYCLES
*\*\            - CORDIC_PRECISION_10CYCLES
*\*\            - CORDIC_PRECISION_11CYCLES
*\*\            - CORDIC_PRECISION_12CYCLES
*\*\            - CORDIC_PRECISION_13CYCLES
*\*\            - CORDIC_PRECISION_14CYCLES
*\*\            - CORDIC_PRECISION_15CYCLES
*\*\          - Scale
*\*\            - CORDIC_SCALE_0
*\*\            - CORDIC_SCALE_1
*\*\            - CORDIC_SCALE_2
*\*\            - CORDIC_SCALE_3
*\*\            - CORDIC_SCALE_4
*\*\            - CORDIC_SCALE_5
*\*\            - CORDIC_SCALE_6
*\*\            - CORDIC_SCALE_7
*\*\          - NbWrite
*\*\            - CORDIC_NBWRITE_1
*\*\            - CORDIC_NBWRITE_2
*\*\          - NbRead
*\*\            - CORDIC_NBREAD_1
*\*\            - CORDIC_NBREAD_2
*\*\          - InSize
*\*\            - CORDIC_INSIZE_16BITS
*\*\            - CORDIC_INSIZE_32BITS
*\*\          - OutSize
*\*\            - CORDIC_OUTSIZE_16BITS
*\*\            - CORDIC_OUTSIZE_32BITS
*\*\          - InSelect
*\*\            - CORDIC_INPUT_FIX
*\*\            - CORDIC_INPUT_FLOAT
*\*\          - OutSelect
*\*\            - CORDIC_OUTPUT_FIX
*\*\            - CORDIC_OUTPUT_FLOAT
*\*\          - CodinLimit
*\*\            - CORDIC_CODIN_LIMIT_DISABLE
*\*\            - CORDIC_CODIN_LIMIT_ENABLE
*\*\          - PhaseLimit
*\*\            - CORDIC_PHASE_LIMIT_DISABLE
*\*\            - CORDIC_PHASE_LIMIT_ENABLE
*\*\return  none
**/
void CORDIC_Init(CORDIC_InitType* CORDIC_InitParam)
{
    uint32_t TempValue;

    /* Configure the CORDIC_CTRLSTS register, including setting CODINLIMIT, PHASELIMIT,
    FLOATOUT, FLOATIN, INSIZE, OUTSIZE, NUMWRITE, NUMREAD, SCALE[2:0], PRECISION[3:0],
    FUNC[3:0] bits */
    TempValue = ((CORDIC_InitParam->Function)  | (CORDIC_InitParam->Precision)
               | (CORDIC_InitParam->Scale)     | (CORDIC_InitParam->NbWrite)
               | (CORDIC_InitParam->NbRead)    | (CORDIC_InitParam->InSize)
               | (CORDIC_InitParam->OutSize)   | (CORDIC_InitParam->InSelect)
               | (CORDIC_InitParam->OutSelect) | (CORDIC_InitParam->CodinLimit)
               | (CORDIC_InitParam->PhaseLimit));
    
    /* Write to CORDIC_CTRLSTS */
    MODIFY_REG(CORDIC->CTRLSTS, CORDIC_CTRLSTS_MASK, TempValue);
}

/**
*\*\name    CORDIC_StructInit.
*\*\fun     Initializes the structure parameter of type CORDIC_InitType used to
*\*\        initialize CORDIC. This function is usually called before initializing
*\*\        a parameter of type CORDIC_InitType.
*\*\param   CORDIC_InitParam :
*\*\          - Function
*\*\          - Precision
*\*\          - Scale
*\*\          - NbWrite
*\*\          - NbRead
*\*\          - InSize
*\*\          - OutSize
*\*\          - InSelect
*\*\          - OutSelect
*\*\          - CodinLimit
*\*\          - PhaseLimit
*\*\return  none
**/
void CORDIC_StructInit(CORDIC_InitType* CORDIC_InitParam)
{
    /** Set the default configuration **/

    /* Default Select the function: cosine */
    CORDIC_InitParam->Function   = CORDIC_FUNCTION_COSINE;
    /* Default Set the number of iterations: 5 */
    CORDIC_InitParam->Precision  = CORDIC_PRECISION_5CYCLES;
    /* Default Select the Scaling Factor: 0 */
    CORDIC_InitParam->Scale      = CORDIC_SCALE_0;
    /* Default Select the number of CORDIC_WDAT register to write: 1 */
    CORDIC_InitParam->NbWrite    = CORDIC_NBWRITE_1;
    /* Default Select the number of CORDIC_RDAT register to read: 1 */
    CORDIC_InitParam->NbRead     = CORDIC_NBREAD_1;
    /* Default Select the input data width: 32bit */
    CORDIC_InitParam->InSize     = CORDIC_INSIZE_32BITS;
    /* Default Select the output data width: 32bit */
    CORDIC_InitParam->OutSize    = CORDIC_OUTSIZE_32BITS;
    /* Default Select the fixed-point input */
    CORDIC_InitParam->InSelect   = CORDIC_INPUT_FIX;
    /* Default Select the fixed-point output */
    CORDIC_InitParam->OutSelect  = CORDIC_OUTPUT_FIX;
    /* Default Disable Coordinate Limit function */
    CORDIC_InitParam->CodinLimit = CORDIC_CODIN_LIMIT_DISABLE;
    /* Default Disable Phase Limit function */
    CORDIC_InitParam->PhaseLimit = CORDIC_PHASE_LIMIT_DISABLE;
}

/**
*\*\name    CORDIC_InterruptCmd.
*\*\fun     Enables or disables the specified CORDIC interrupts.
*\*\param   Interrupt:
*\*\          - CORDIC_INT
*\*\          - CORDIC_INT_INOVERFLOW
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void CORDIC_InterruptCmd(uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected CORDIC interrupt */
        SET_BIT(CORDIC->CTRLSTS, Interrupt);
    }
    else
    {
        /* Disable the selected CORDIC interrupt */
        CLEAR_BIT(CORDIC->CTRLSTS, Interrupt);
    }
}

/**
*\*\name    CORDIC_DMAReadRequestCmd.
*\*\fun     Enables or disables the CORDIC DMA read request.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void CORDIC_DMAReadRequestCmd(FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable CORDIC DMA read request */
        SET_BIT(CORDIC->CTRLSTS, CORDIC_CTRLSTS_DMAREN);
    }
    else
    {
        /* Disable CORDIC DMA read request */
        CLEAR_BIT(CORDIC->CTRLSTS, CORDIC_CTRLSTS_DMAREN);
    }
}

/**
*\*\name    CORDIC_DMAWriteRequestCmd.
*\*\fun     Enables or disables the CORDIC DMA write request.
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void CORDIC_DMAWriteRequestCmd(FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable CORDIC DMA write request */
        SET_BIT(CORDIC->CTRLSTS, CORDIC_CTRLSTS_DMAWEN);
    }
    else
    {
        /* Disable CORDIC DMA write request */
        CLEAR_BIT(CORDIC->CTRLSTS, CORDIC_CTRLSTS_DMAWEN);
    }
}

/**
*\*\name    CORDIC_GetRegisterAddr.
*\*\fun     Get the CORDIC data register address used for DMA transfer.
*\*\param   Direction:
*\*\          - CORDIC_AS_DMA_SRCADDR
*\*\          - CORDIC_AS_DMA_DSTADDR
*\*\return  Address of data register.
**/
uint32_t CORDIC_GetRegisterAddr(uint32_t Direction)
{
    uint32_t Address;

    /* Check the direction of transmission */
    if (Direction == CORDIC_AS_DMA_DSTADDR)
    {
        /* Get address of WDAT register */
        Address = (uint32_t) & (CORDIC->WDAT);
    }
    else
    {
        /* Get address of RDAT register */
        Address = (uint32_t) & (CORDIC->RDAT);
    }

    /* Return address value */
    return Address;
}

/**
*\*\name    CORDIC_WriteData.
*\*\fun     Write 32-bit input data for the CORDIC processing.
*\*\param   pInData :
*\*\          - Points to the address of input data
*\*\return  none
**/
void CORDIC_WriteData(uint32_t *pInData)
{
    /* Write WDAT register */
    WRITE_REG(CORDIC->WDAT, *pInData);
}

/**
*\*\name    CORDIC_ReadData.
*\*\fun     Return 32-bit output data of CORDIC processing.
*\*\param   pOutData :
*\*\          - Points to the address where the output data is stored
*\*\return  none.
**/
void CORDIC_ReadData(uint32_t *pOutData)
{
    /* Read RDAT register */
    *pOutData = READ_REG(CORDIC->RDAT);
}

/**
*\*\name    CORDIC_GetFlagStatus.
*\*\fun     Checks whether the specified CORDIC flag is set or not.
*\*\param   Flag:
*\*\          - CORDIC_FLAG_RRF
*\*\          - CORDIC_FLAG_INOVF
*\*\          - CORDIC_FLAG_DMAWENF
*\*\          - CORDIC_FLAG_DMARENF
*\*\          - CORDIC_FLAG_INTENF
*\*\          - CORDIC_FLAG_INOVINTENF
*\*\return  FlagStatus:
*\*\          - RESET : Corresponding flag bit is reset
*\*\          - SET   : Corresponding flag bit is set
**/
FlagStatus CORDIC_GetFlagStatus(uint32_t Flag)
{
    FlagStatus Status;

    /* Read and return the status of the corresponding flag bits */
    if(READ_BIT(CORDIC->CTRLSTS, Flag) != (uint32_t)RESET)
    {
        /* Flag is set */
        Status = SET;
    }
    else
    {
        /* Flag is reset */
        Status = RESET;
    }

    /* Return flag status */
    return Status;
}

/**
*\*\name    CORDIC_ClearStatusFlag.
*\*\fun     Clears the pending flag for the CORDIC.
*\*\param   Flag :
*\*\          - CORDIC_FLAG_INOVF
*\*\          - CORDIC_FLAG_DMAWENF
*\*\          - CORDIC_FLAG_DMARENF
*\*\          - CORDIC_FLAG_INTENF
*\*\          - CORDIC_FLAG_INOVINTENF
*\*\return  none
*\*\note    The RRF flag cannot be cleared by a call to this function;
*\*\        the RRF flag is cleared by hardware when reading the data
*\*\        register is complete.
**/
void CORDIC_ClearStatusFlag(uint32_t Flag)
{
    if (Flag == CORDIC_FLAG_INOVF)
    {
        /* Clear the input parameter overflow flag */
        SET_BIT(CORDIC->CTRLSTS, Flag);
    }
    else
    {
        /* Clear other flags except RRF */
        CLEAR_BIT(CORDIC->CTRLSTS, Flag);
    }
}

