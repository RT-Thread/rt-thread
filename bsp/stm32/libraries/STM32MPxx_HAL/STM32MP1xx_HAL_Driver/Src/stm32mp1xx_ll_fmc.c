/**
  ******************************************************************************
  * @file    stm32mp1xx_ll_fmc.c
  * @author  MCD Application Team
  * @brief   FMC Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the Flexible Memory Controller (FMC) peripheral memories:
  *           + Initialization/de-initialization functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                        ##### FMC peripheral features #####
  ==============================================================================
  [..] The Flexible memory controller (FMC) includes following memory controllers:
       (+) The NOR/PSRAM memory controller

  [..] The FMC functional block makes the interface with synchronous and asynchronous static
       memories. Its main purposes are:
       (+) to translate AHB transactions into the appropriate external device protocol
       (+) to meet the access time requirements of the external memory devices

  [..] All external memories share the addresses, data and control signals with the controller.
       Each external device is accessed by means of a unique Chip Select. The FMC performs
       only one access at a time to an external device.
       The main features of the FMC controller are the following:
        (+) Interface with static-memory mapped devices including:
           (++) Static random access memory (SRAM)
           (++) Read-only memory (ROM)
           (++) NOR Flash memory/OneNAND Flash memory
           (++) PSRAM (4 memory banks)
        (+) Independent Chip Select control for each memory bank
        (+) Independent configuration for each memory bank

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx_hal.h"

/** @addtogroup STM32MP1xx_HAL_Driver
  * @{
  */
#if defined HAL_NOR_MODULE_ENABLED || defined HAL_SRAM_MODULE_ENABLED

/** @defgroup FMC_LL  FMC Low Layer
  * @brief FMC driver modules
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup FMC_LL_Private_Constants FMC Low Layer Private Constants
  * @{
  */

/* ----------------------- FMC registers bit mask --------------------------- */

/* --- BCR Register ---*/
/* BCR register clear mask */

/* --- BTR Register ---*/
/* BTR register clear mask */
#define BTR_CLEAR_MASK    ((uint32_t)(FMC_BTR1_ADDSET | FMC_BTR1_ADDHLD  |\
                                      FMC_BTR1_DATAST | FMC_BTR1_BUSTURN |\
                                      FMC_BTR1_CLKDIV | FMC_BTR1_DATLAT  |\
                                      FMC_BTR1_ACCMOD | FMC_BTR1_DATAHLD))

/* --- BWTR Register ---*/
/* BWTR register clear mask */
#if defined(FMC_BWTR1_BUSTURN)
#define BWTR_CLEAR_MASK   ((uint32_t)(FMC_BWTR1_ADDSET | FMC_BWTR1_ADDHLD  |\
                                      FMC_BWTR1_DATAST | FMC_BWTR1_BUSTURN |\
                                      FMC_BWTR1_ACCMOD | FMC_BWTR1_DATAHLD))
#else
#define BWTR_CLEAR_MASK   ((uint32_t)(FMC_BWTR1_ADDSET | FMC_BWTR1_ADDHLD  |\
                                      FMC_BWTR1_DATAST | FMC_BWTR1_ACCMOD  |\
                                      FMC_BWTR1_DATAHLD))
#endif /* FMC_BWTR1_BUSTURN */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup FMC_LL_Exported_Functions FMC Low Layer Exported Functions
  * @{
  */


/** @defgroup FMC_LL_Exported_Functions_NORSRAM FMC Low Layer NOR SRAM Exported Functions
  * @brief  NORSRAM Controller functions
  *
  @verbatim
  ==============================================================================
                   ##### How to use NORSRAM device driver #####
  ==============================================================================

  [..]
    This driver contains a set of APIs to interface with the FMC NORSRAM banks in order
    to run the NORSRAM external devices.

    (+) FMC NORSRAM bank reset using the function FMC_NORSRAM_DeInit()
    (+) FMC NORSRAM bank control configuration using the function FMC_NORSRAM_Init()
    (+) FMC NORSRAM bank timing configuration using the function FMC_NORSRAM_Timing_Init()
    (+) FMC NORSRAM bank extended timing configuration using the function
        FMC_NORSRAM_Extended_Timing_Init()
    (+) FMC NORSRAM bank enable/disable write operation using the functions
        FMC_NORSRAM_WriteOperation_Enable()/FMC_NORSRAM_WriteOperation_Disable()

@endverbatim
  * @{
  */

/** @defgroup FMC_LL_NORSRAM_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and Configuration functions
  *
  @verbatim
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the FMC NORSRAM interface
    (+) De-initialize the FMC NORSRAM interface
    (+) Configure the FMC clock and associated GPIOs

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the FMC_NORSRAM device according to the specified
  *         control parameters in the FMC_NORSRAM_InitTypeDef
  * @param  Device Pointer to NORSRAM device instance
  * @param  Init Pointer to NORSRAM Initialization structure
  * @retval HAL status
  */
HAL_StatusTypeDef  FMC_NORSRAM_Init(FMC_NORSRAM_TypeDef *Device, FMC_NORSRAM_InitTypeDef *Init)
{
  uint32_t flashaccess;

  /* Check the parameters */
  assert_param(IS_FMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FMC_NORSRAM_BANK(Init->NSBank));
  assert_param(IS_FMC_MUX(Init->DataAddressMux));
  assert_param(IS_FMC_MEMORY(Init->MemoryType));
  assert_param(IS_FMC_NORSRAM_MEMORY_WIDTH(Init->MemoryDataWidth));
  assert_param(IS_FMC_BURSTMODE(Init->BurstAccessMode));
  assert_param(IS_FMC_WAIT_POLARITY(Init->WaitSignalPolarity));
  assert_param(IS_FMC_WAIT_SIGNAL_ACTIVE(Init->WaitSignalActive));
  assert_param(IS_FMC_WRITE_OPERATION(Init->WriteOperation));
  assert_param(IS_FMC_WAITE_SIGNAL(Init->WaitSignal));
  assert_param(IS_FMC_EXTENDED_MODE(Init->ExtendedMode));
  assert_param(IS_FMC_ASYNWAIT(Init->AsynchronousWait));
  assert_param(IS_FMC_WRITE_BURST(Init->WriteBurst));
  assert_param(IS_FMC_CONTINOUS_CLOCK(Init->ContinuousClock));
  assert_param(IS_FMC_PAGESIZE(Init->PageSize));
  assert_param(IS_FMC_NBL_SETUPTIME(Init->NBLSetupTime));
  assert_param(IS_FUNCTIONAL_STATE(Init->MaxChipSelectPulse));

  /* Disable NORSRAM Device */
  __FMC_NORSRAM_DISABLE(Device, Init->NSBank);

  /* Set NORSRAM device control parameters */
  if (Init->MemoryType == FMC_MEMORY_TYPE_NOR)
  {
    flashaccess = FMC_NORSRAM_FLASH_ACCESS_ENABLE;
  }
  else
  {
    flashaccess = FMC_NORSRAM_FLASH_ACCESS_DISABLE;
  }

  MODIFY_REG(Device->BTCR[Init->NSBank],
             (FMC_BCR1_MBKEN                |
              FMC_BCR1_MUXEN                |
              FMC_BCR1_MTYP                 |
              FMC_BCR1_MWID                 |
              FMC_BCR1_FACCEN               |
              FMC_BCR1_BURSTEN              |
              FMC_BCR1_WAITPOL              |
              FMC_BCR1_WAITCFG              |
              FMC_BCR1_WREN                 |
              FMC_BCR1_WAITEN               |
              FMC_BCR1_EXTMOD               |
              FMC_BCR1_ASYNCWAIT            |
              FMC_BCR1_CBURSTRW             |
              FMC_BCR1_CCLKEN               |
              FMC_BCR1_NBLSET               |
              FMC_BCR1_CPSIZE),
             (flashaccess                   |
              Init->DataAddressMux          |
              Init->MemoryType              |
              Init->MemoryDataWidth         |
              Init->BurstAccessMode         |
              Init->WaitSignalPolarity      |
              Init->WaitSignalActive        |
              Init->WriteOperation          |
              Init->WaitSignal              |
              Init->ExtendedMode            |
              Init->AsynchronousWait        |
              Init->WriteBurst              |
              Init->ContinuousClock         |
              Init->NBLSetupTime            |
              Init->PageSize));

  /* Configure synchronous mode when Continuous clock is enabled for bank2..4 */
  if ((Init->ContinuousClock == FMC_CONTINUOUS_CLOCK_SYNC_ASYNC) && (Init->NSBank != FMC_NORSRAM_BANK1))
  {
    MODIFY_REG(Device->BTCR[FMC_NORSRAM_BANK1], FMC_BCR1_CCLKEN, Init->ContinuousClock);
  }

  /* Check PSRAM chip select counter state */
  if(Init->MaxChipSelectPulse == ENABLE)
  {
    /* Check the parameters */
    assert_param(IS_FMC_MAX_CHIP_SELECT_PULSE_TIME(Init->MaxChipSelectPulseTime));

    /* Configure PSRAM chip select counter value */
    MODIFY_REG(Device->PCSCNTR, FMC_PCSCNTR_CSCOUNT, (uint32_t)(Init->MaxChipSelectPulseTime));

    /* Enable PSRAM chip select counter for the bank */
    switch (Init->NSBank)
    {
      case FMC_NORSRAM_BANK1 :
        SET_BIT(Device->PCSCNTR, FMC_PCSCNTR_CNTB1EN);
        break;

      case FMC_NORSRAM_BANK2 :
        SET_BIT(Device->PCSCNTR, FMC_PCSCNTR_CNTB2EN);
        break;

      case FMC_NORSRAM_BANK3 :
        SET_BIT(Device->PCSCNTR, FMC_PCSCNTR_CNTB3EN);
        break;

      case FMC_NORSRAM_BANK4 :
        SET_BIT(Device->PCSCNTR, FMC_PCSCNTR_CNTB4EN);
        break;

      default :
        break;
    }
  }

  return HAL_OK;
}

/**
  * @brief  DeInitialize the FMC_NORSRAM peripheral
  * @param  Device Pointer to NORSRAM device instance
  * @param  ExDevice Pointer to NORSRAM extended mode device instance
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NORSRAM_DeInit(FMC_NORSRAM_TypeDef *Device, FMC_NORSRAM_EXTENDED_TypeDef *ExDevice, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FMC_NORSRAM_EXTENDED_DEVICE(ExDevice));
  assert_param(IS_FMC_NORSRAM_BANK(Bank));

  /* Disable the FMC_NORSRAM device */
  __FMC_NORSRAM_DISABLE(Device, Bank);

  /* De-initialize the FMC_NORSRAM device */
  /* FMC_NORSRAM_BANK1 */
  if (Bank == FMC_NORSRAM_BANK1)
  {
    Device->BTCR[Bank] = 0x000030DBU;
  }
  /* FMC_NORSRAM_BANK2, FMC_NORSRAM_BANK3 or FMC_NORSRAM_BANK4 */
  else
  {
    Device->BTCR[Bank] = 0x000030D2U;
  }

  Device->BTCR[Bank + 1U] = 0x0FFFFFFFU;
  ExDevice->BWTR[Bank]   = 0x000FFFFFU;

  /* De-initialize PSRAM chip select counter */
    switch (Bank)
    {
      case FMC_NORSRAM_BANK1 :
        CLEAR_BIT(Device->PCSCNTR, FMC_PCSCNTR_CNTB1EN);
        break;

      case FMC_NORSRAM_BANK2 :
        CLEAR_BIT(Device->PCSCNTR, FMC_PCSCNTR_CNTB2EN);
        break;

      case FMC_NORSRAM_BANK3 :
        CLEAR_BIT(Device->PCSCNTR, FMC_PCSCNTR_CNTB3EN);
        break;

      case FMC_NORSRAM_BANK4 :
        CLEAR_BIT(Device->PCSCNTR, FMC_PCSCNTR_CNTB4EN);
        break;

      default :
        break;
    }

  return HAL_OK;
}

/**
  * @brief  Initialize the FMC_NORSRAM Timing according to the specified
  *         parameters in the FMC_NORSRAM_TimingTypeDef
  * @param  Device Pointer to NORSRAM device instance
  * @param  Timing Pointer to NORSRAM Timing structure
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NORSRAM_Timing_Init(FMC_NORSRAM_TypeDef *Device, FMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank)
{
  uint32_t tmpr;

  /* Check the parameters */
  assert_param(IS_FMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
  assert_param(IS_FMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
  assert_param(IS_FMC_DATAHOLD_DURATION(Timing->DataHoldTime));
  assert_param(IS_FMC_DATASETUP_TIME(Timing->DataSetupTime));
  assert_param(IS_FMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
  assert_param(IS_FMC_CLK_DIV(Timing->CLKDivision));
  assert_param(IS_FMC_DATA_LATENCY(Timing->DataLatency));
  assert_param(IS_FMC_ACCESS_MODE(Timing->AccessMode));
  assert_param(IS_FMC_NORSRAM_BANK(Bank));

  /* Set FMC_NORSRAM device timing parameters */
  MODIFY_REG(Device->BTCR[Bank + 1U], BTR_CLEAR_MASK, (Timing->AddressSetupTime                                  |
                                                      ((Timing->AddressHoldTime)        << FMC_BTR1_ADDHLD_Pos)  |
                                                      ((Timing->DataSetupTime)          << FMC_BTR1_DATAST_Pos)  |
                                                      ((Timing->DataHoldTime)           << FMC_BTR1_DATAHLD_Pos) |
                                                      ((Timing->BusTurnAroundDuration)  << FMC_BTR1_BUSTURN_Pos) |
                                                      (((Timing->CLKDivision) - 1U)     << FMC_BTR1_CLKDIV_Pos)  |
                                                      (((Timing->DataLatency) - 2U)     << FMC_BTR1_DATLAT_Pos)  |
                                                      (Timing->AccessMode)));

  /* Configure Clock division value (in NORSRAM bank 1) when continuous clock is enabled */
  if (HAL_IS_BIT_SET(Device->BTCR[FMC_NORSRAM_BANK1], FMC_BCR1_CCLKEN))
  {
    tmpr = (uint32_t)(Device->BTCR[FMC_NORSRAM_BANK1 + 1U] & ~(((uint32_t)0x0F) << FMC_BTR1_CLKDIV_Pos));
    tmpr |= (uint32_t)(((Timing->CLKDivision) - 1U) << FMC_BTR1_CLKDIV_Pos);
    MODIFY_REG(Device->BTCR[FMC_NORSRAM_BANK1 + 1U], FMC_BTR1_CLKDIV, tmpr);
  }

  return HAL_OK;
}

/**
  * @brief  Initialize the FMC_NORSRAM Extended mode Timing according to the specified
  *         parameters in the FMC_NORSRAM_TimingTypeDef
  * @param  Device Pointer to NORSRAM device instance
  * @param  Timing Pointer to NORSRAM Timing structure
  * @param  Bank NORSRAM bank number
  * @param  ExtendedMode FMC Extended Mode
  *          This parameter can be one of the following values:
  *            @arg FMC_EXTENDED_MODE_DISABLE
  *            @arg FMC_EXTENDED_MODE_ENABLE
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NORSRAM_Extended_Timing_Init(FMC_NORSRAM_EXTENDED_TypeDef *Device, FMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank, uint32_t ExtendedMode)
{
  /* Check the parameters */
  assert_param(IS_FMC_EXTENDED_MODE(ExtendedMode));

  /* Set NORSRAM device timing register for write configuration, if extended mode is used */
  if (ExtendedMode == FMC_EXTENDED_MODE_ENABLE)
  {
    /* Check the parameters */
    assert_param(IS_FMC_NORSRAM_EXTENDED_DEVICE(Device));
    assert_param(IS_FMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
    assert_param(IS_FMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
    assert_param(IS_FMC_DATASETUP_TIME(Timing->DataSetupTime));
    assert_param(IS_FMC_DATAHOLD_DURATION(Timing->DataHoldTime));
#if defined(FMC_BWTR1_BUSTURN)
    assert_param(IS_FMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
#endif /* FMC_BWTR1_BUSTURN */
    assert_param(IS_FMC_ACCESS_MODE(Timing->AccessMode));
    assert_param(IS_FMC_NORSRAM_BANK(Bank));

    /* Set NORSRAM device timing register for write configuration, if extended mode is used */
    MODIFY_REG(Device->BWTR[Bank], BWTR_CLEAR_MASK, (Timing->AddressSetupTime                                    |
                                                     ((Timing->AddressHoldTime)        << FMC_BWTR1_ADDHLD_Pos)  |
                                                     ((Timing->DataSetupTime)          << FMC_BWTR1_DATAST_Pos)  |
                                                     ((Timing->DataHoldTime)           << FMC_BWTR1_DATAHLD_Pos) |
#if defined(FMC_BWTR1_BUSTURN)
                                                     Timing->AccessMode                                          |
                                                     ((Timing->BusTurnAroundDuration)  << FMC_BWTR1_BUSTURN_Pos)));
#else
                                                     Timing->AccessMode));
#endif /* FMC_BWTR1_BUSTURN */
  }
  else
  {
    Device->BWTR[Bank] = 0x000FFFFFU;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup FMC_LL_NORSRAM_Private_Functions_Group2
 *  @brief   management functions
 *
@verbatim
  ==============================================================================
                      ##### FMC_NORSRAM Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control dynamically
    the FMC NORSRAM interface.

@endverbatim
  * @{
  */

/**
  * @brief  Enables dynamically FMC_NORSRAM write operation.
  * @param  Device Pointer to NORSRAM device instance
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NORSRAM_WriteOperation_Enable(FMC_NORSRAM_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FMC_NORSRAM_BANK(Bank));

  /* Enable write operation */
  SET_BIT(Device->BTCR[Bank], FMC_WRITE_OPERATION_ENABLE);

  return HAL_OK;
}

/**
  * @brief  Disables dynamically FMC_NORSRAM write operation.
  * @param  Device Pointer to NORSRAM device instance
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FMC_NORSRAM_WriteOperation_Disable(FMC_NORSRAM_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FMC_NORSRAM_BANK(Bank));

  /* Disable write operation */
  CLEAR_BIT(Device->BTCR[Bank], FMC_WRITE_OPERATION_ENABLE);

  return HAL_OK;
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

/**
  * @}
  */

#endif /* HAL_NOR_MODULE_ENABLED */
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
