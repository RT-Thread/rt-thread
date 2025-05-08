/*********************************************************************************************************//**
 * @file    ht32f66xxx_cordic.c
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
 * @brief   This file provides all the CORDIC firmware functions.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f66xxx_cordic.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup CORDIC CORDIC
  * @brief CORDIC driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup CORDIC_Private_Define CORDIC private definitions
  * @{
  */
#define IS_CORDIC_FUNCTION(__FUNCTION__)   (((__FUNCTION__) == CORDIC_FUNCTION_COSINE)            || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_SINE)              || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_PHASE)             || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_MODULUS)           || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_ARCTANGENT)        || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_HCOSINE)           || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_HSINE)             || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_HARCTANGENT)       || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_NATURALLOG)        || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_SQUAREROOT)        || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_ROTATIONMATRIX)    || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_INTEGERMODULUS)    || \
                                            ((__FUNCTION__) == CORDIC_FUNCTION_INTEGERSQUAREROOT))

#define IS_CORDIC_PRECISION(__PRECISION__) (((__PRECISION__) == CORDIC_PRECISION_1CYCLE)   || \
                                            ((__PRECISION__) == CORDIC_PRECISION_2CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_3CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_4CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_5CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_6CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_7CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_8CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_9CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_10CYCLES) || \
                                            ((__PRECISION__) == CORDIC_PRECISION_11CYCLES) || \
                                            ((__PRECISION__) == CORDIC_PRECISION_12CYCLES) || \
                                            ((__PRECISION__) == CORDIC_PRECISION_13CYCLES) || \
                                            ((__PRECISION__) == CORDIC_PRECISION_14CYCLES) || \
                                            ((__PRECISION__) == CORDIC_PRECISION_15CYCLES))


#define IS_CORDIC_SCALE(__SCALE__)         (((__SCALE__) == CORDIC_SCALE_0)  || \
                                            ((__SCALE__) == CORDIC_SCALE_1)  || \
                                            ((__SCALE__) == CORDIC_SCALE_2)  || \
                                            ((__SCALE__) == CORDIC_SCALE_3)  || \
                                            ((__SCALE__) == CORDIC_SCALE_4)  || \
                                            ((__SCALE__) == CORDIC_SCALE_5)  || \
                                            ((__SCALE__) == CORDIC_SCALE_6)  || \
                                            ((__SCALE__) == CORDIC_SCALE_7))

#define IS_CORDIC_PDMA_REQ(REQ)            (((REQ & 0xFFF9FFFF) == 0x0) && (REQ != 0x0))

#define IS_CORDIC_NBWRITE(__NBWRITE__)     (((__NBWRITE__) == CORDIC_NBWRITE_1)  || \
                                            ((__NBWRITE__) == CORDIC_NBWRITE_2)  || \
                                            ((__NBWRITE__) == CORDIC_NBWRITE_3))

#define IS_CORDIC_NBREAD(__NBREAD__)       (((__NBREAD__) == CORDIC_NBREAD_1)  || \
                                            ((__NBREAD__) == CORDIC_NBREAD_2))

#define IS_CORDIC_INSIZE(__INSIZE__)       (((__INSIZE__) == CORDIC_INSIZE_32BITS)  || \
                                            ((__INSIZE__) == CORDIC_INSIZE_16BITS))

#define IS_CORDIC_OUTSIZE(__OUTSIZE__)     (((__OUTSIZE__) == CORDIC_OUTSIZE_32BITS)  || \
                                            ((__OUTSIZE__) == CORDIC_OUTSIZE_16BITS))
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup CORDIC_Exported_Functions CORDIC exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the CORDIC peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void CORDIC_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.CORDIC = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the CORDIC peripheral according to the specified parameters in the CORDIC_InitStruct.
 * @param CORDIC_InitStruct: pointer to a CORDIC_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void CORDIC_Init(CORDIC_InitTypeDef *CORDIC_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CORDIC_FUNCTION(CORDIC_InitStruct->Function));
  Assert_Param(IS_CORDIC_PRECISION(CORDIC_InitStruct->Precision));
  Assert_Param(IS_CORDIC_SCALE(CORDIC_InitStruct->Scale));
  Assert_Param(IS_CORDIC_NBWRITE(CORDIC_InitStruct->NbWrite));
  Assert_Param(IS_CORDIC_NBREAD(CORDIC_InitStruct->NbRead));
  Assert_Param(IS_CORDIC_INSIZE(CORDIC_InitStruct->InSize));
  Assert_Param(IS_CORDIC_OUTSIZE(CORDIC_InitStruct->OutSize));

  HT_CORDIC->CSR &= ~(CORDIC_CSR_FUNC_MASK | CORDIC_CSR_PRECISION_MASK | CORDIC_CSR_SCALE_MASK | \
                      CORDIC_CSR_NRES_MASK | CORDIC_CSR_NARGS_MASK | CORDIC_CSR_RESSIZE_MASK | CORDIC_CSR_ARGSIZE_MASK);

  HT_CORDIC->CSR |= (CORDIC_InitStruct->Function | CORDIC_InitStruct->Precision | CORDIC_InitStruct->Scale | \
                     CORDIC_InitStruct->NbWrite | CORDIC_InitStruct->NbRead | CORDIC_InitStruct->InSize | CORDIC_InitStruct->OutSize);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable CORDIC result ready interrupt. (RRDY)
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void CORDIC_IntCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_CORDIC->CSR |= CORDIC_CSR_IEN;
  }
  else
  {
    HT_CORDIC->CSR &= ~CORDIC_CSR_IEN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the CORDIC PDMA interface.
 * @param CORDIC_DMA: specify the CORDIC PDMA transfer request to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg CORDIC_DMA_REN: Read PDMA transfer request
 *     @arg CORDIC_DMA_WEN: Write PDMA transfer request
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void CORDIC_PDMACmd(u32 CORDIC_DMA, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CORDIC_PDMA_REQ(CORDIC_DMA));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_CORDIC->CSR |= CORDIC_DMA;
  }
  else
  {
    HT_CORDIC->CSR &= ~CORDIC_DMA;
  }
}

/*********************************************************************************************************//**
 * @brief Check CORDIC result ready flag state. (RRDY)
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus CORDIC_GetFlagStatus_RRDY(void)
{
  if ((HT_CORDIC->CSR & CORDIC_FLAG_RRDY) != (u32)RESET)
  {
    return (SET);
  }
  else
  {
    return (RESET);
  }
}

/*********************************************************************************************************//**
 * @brief Write 32-bit input data for the CORDIC processing.
 * @param InData: 32-bit value to be provided as input data for CORDIC processing.
 * @retval None
 ************************************************************************************************************/
void CORDIC_WriteData(u32 InData)
{
  HT_CORDIC->WDATA = InData;
}

/*********************************************************************************************************//**
 * @brief Return 32-bit output data of CORDIC processing.
 * @retval 32-bit output data of CORDIC processing.
 ************************************************************************************************************/
u32 CORDIC_ReadData(void)
{
  return (u32)HT_CORDIC->RDATA;
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
