/*********************************************************************************************************//**
 * @file    ht32f5xxxx_spi_midi.c
 * @version $Rev:: 7073         $
 * @date    $Date:: 2023-07-28 #$
 * @brief   This file provides all the SPI firmware functions (MIDI Control).
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
#include "ht32f5xxxx_spi_midi.h"


/* Private macro -------------------------------------------------------------------------------------------*/
#define IS_MIDICTRL_MODE(MODE)           ((MODE == DOR_MODE)   || \
                                          (MODE == DIOR_MODE)  || \
                                          (MODE == QOR_MODE)   || \
                                          (MODE == QIOR_MODE)  || \
                                          (MODE == QPI_MODE)   || \
                                          (MODE == SERIAL_MODE))

#define IS_MIDICTRL_CMD_LENGTH(LENGTH)   ((LENGTH == MIDICTRL_CMDLENGTH_0) || \
                                          (LENGTH == MIDICTRL_CMDLENGTH_1) || \
                                          (LENGTH == MIDICTRL_CMDLENGTH_2) || \
                                          (LENGTH == MIDICTRL_CMDLENGTH_3) || \
                                          (LENGTH == MIDICTRL_CMDLENGTH_4) || \
                                          (LENGTH == MIDICTRL_CMDLENGTH_5) || \
                                          (LENGTH == MIDICTRL_CMDLENGTH_6) || \
                                          (LENGTH == MIDICTRL_CMDLENGTH_7) || \
                                          (LENGTH == MIDICTRL_CMDLENGTH_8))

#define IS_MIDICTRL_AD_LENGTH(LENGTH)    ((LENGTH == MIDICTRL_ADLENGTH_0)  || \
                                          (LENGTH == MIDICTRL_ADLENGTH_1)  || \
                                          (LENGTH == MIDICTRL_ADLENGTH_2)  || \
                                          (LENGTH == MIDICTRL_ADLENGTH_3)  || \
                                          (LENGTH == MIDICTRL_ADLENGTH_4)  || \
                                          (LENGTH == MIDICTRL_ADLENGTH_5)  || \
                                          (LENGTH == MIDICTRL_ADLENGTH_6)  || \
                                          (LENGTH == MIDICTRL_ADLENGTH_7)  || \
                                          (LENGTH == MIDICTRL_ADLENGTH_8)  || \
                                          (LENGTH == MIDICTRL_ADLENGTH_9)  || \
                                          (LENGTH == MIDICTRL_ADLENGTH_10) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_11) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_12) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_13) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_14) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_15) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_16) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_17) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_18) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_19) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_20) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_21) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_22) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_23) || \
                                          (LENGTH == MIDICTRL_ADLENGTH_24))

#define IS_MIDICTRL_MODE_LENGTH(LENGTH)  ((LENGTH == MIDICTRL_MODELENGTH_0) || \
                                          (LENGTH == MIDICTRL_MODELENGTH_1) || \
                                          (LENGTH == MIDICTRL_MODELENGTH_2) || \
                                          (LENGTH == MIDICTRL_MODELENGTH_3) || \
                                          (LENGTH == MIDICTRL_MODELENGTH_4) || \
                                          (LENGTH == MIDICTRL_MODELENGTH_5) || \
                                          (LENGTH == MIDICTRL_MODELENGTH_6) || \
                                          (LENGTH == MIDICTRL_MODELENGTH_7) || \
                                          (LENGTH == MIDICTRL_MODELENGTH_8))

#define IS_MIDICTRL_DUMMY_LENGTH(LENGTH) ((LENGTH == MIDICTRL_DUMMYLENGTH_0) || \
                                          (LENGTH == MIDICTRL_DUMMYLENGTH_1) || \
                                          (LENGTH == MIDICTRL_DUMMYLENGTH_2) || \
                                          (LENGTH == MIDICTRL_DUMMYLENGTH_3) || \
                                          (LENGTH == MIDICTRL_DUMMYLENGTH_4) || \
                                          (LENGTH == MIDICTRL_DUMMYLENGTH_5) || \
                                          (LENGTH == MIDICTRL_DUMMYLENGTH_6) || \
                                          (LENGTH == MIDICTRL_DUMMYLENGTH_7) || \
                                          (LENGTH == MIDICTRL_DUMMYLENGTH_8))

#define IS_MIDICTRL_DATA_LENGTH(LENGTH)  ((LENGTH == MIDICTRL_DATALENGTH_0)  || \
                                          (LENGTH == MIDICTRL_DATALENGTH_1)  || \
                                          (LENGTH == MIDICTRL_DATALENGTH_2)  || \
                                          (LENGTH == MIDICTRL_DATALENGTH_3)  || \
                                          (LENGTH == MIDICTRL_DATALENGTH_4)  || \
                                          (LENGTH == MIDICTRL_DATALENGTH_5)  || \
                                          (LENGTH == MIDICTRL_DATALENGTH_6)  || \
                                          (LENGTH == MIDICTRL_DATALENGTH_7)  || \
                                          (LENGTH == MIDICTRL_DATALENGTH_8)  || \
                                          (LENGTH == MIDICTRL_DATALENGTH_9)  || \
                                          (LENGTH == MIDICTRL_DATALENGTH_10) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_11) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_12) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_13) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_14) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_15) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_16) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_17) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_18) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_19) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_20) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_21) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_22) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_23) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_24) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_25) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_26) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_27) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_28) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_29) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_30) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_31) || \
                                          (LENGTH == MIDICTRL_DATALENGTH_32))

#define IS_MIDICTRL_CMD_VALUE(VALUE)  (VALUE <= 0xFF)
#define IS_MIDICTRL_MODE_VALUE(VALUE) (VALUE <= 0xFF)

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief Enable or Disable QSPI MIDICTRL.
 * @param  QSPIx: where QSPIx is the selected QSPI from the QSPI peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void MIDICTRL_Cmd(HT_SPI_TypeDef* QSPIx ,ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    QSPIx->MIDICR0 |= MIDICTRL_ON;
  }
  else
  {
    QSPIx->MIDICR0 &= MIDICTRL_OFF;
  }
}

/*********************************************************************************************************//**
 * @brief Initialize the QSPIx peripheral MIDICTRL according to the specified parameters in the MIDICTRL_InitStruct.
 * @param QSPIx: This parameter can be HT_QSPI.
 * @param MIDICTRL_InitStruct: pointer to a MIDICTRL_InitTypeDef structure that contains the configuration
 *        information for the specified USART peripheral.
 * @retval None
 ************************************************************************************************************/
void MIDICTRL_Init(HT_SPI_TypeDef* QSPIx, MIDICTRL_InitTypeDef* MIDICTRL_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_QSPI(QSPIx));
  Assert_Param(IS_MIDICTRL_MODE(MIDICTRL_InitStruct->MIDICTRL_MODE));
  Assert_Param(IS_MIDICTRL_CMD_LENGTH(MIDICTRL_InitStruct->MIDICTRL_CommandLength));
  Assert_Param(IS_MIDICTRL_AD_LENGTH(MIDICTRL_InitStruct->MIDICTRL_AddressLength));
  Assert_Param(IS_MIDICTRL_MODE_LENGTH(MIDICTRL_InitStruct->MIDICTRL_ModeLength));
  Assert_Param(IS_MIDICTRL_DUMMY_LENGTH(MIDICTRL_InitStruct->MIDICTRL_DummyLength));
  Assert_Param(IS_MIDICTRL_DATA_LENGTH(MIDICTRL_InitStruct->MIDICTRL_DataLength));
  Assert_Param(IS_MIDICTRL_CMD_VALUE(MIDICTRL_InitStruct->MIDICTRL_CommandValue));
  Assert_Param(IS_MIDICTRL_MODE_VALUE(MIDICTRL_InitStruct->MIDICTRL_ModeValue));

  QSPIx->MIDICR0 = (QSPIx->MIDICR0 & 0xF0800000) | MIDICTRL_InitStruct->MIDICTRL_MODE |
                    MIDICTRL_InitStruct->MIDICTRL_CommandLength | MIDICTRL_InitStruct->MIDICTRL_AddressLength |
                    MIDICTRL_InitStruct->MIDICTRL_ModeLength    | MIDICTRL_InitStruct->MIDICTRL_DummyLength   |
                    MIDICTRL_InitStruct->MIDICTRL_DataLength ;

  QSPIx->MIDICR1 = (QSPIx->MIDICR1 & 0xFFFF0000) | ((MIDICTRL_InitStruct->MIDICTRL_ModeValue) <<  MDVALUE_POS )|
                   ((MIDICTRL_InitStruct->MIDICTRL_CommandValue) <<  CMDVALUE_POS );
}
