/**
  ******************************************************************************
  * @file    stm32f1xx_ll_fsmc.c
  * @author  MCD Application Team
  * @brief   FSMC Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the Flexible Memory Controller (FSMC) peripheral memories:
  *           + Initialization/de-initialization functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  *
  @verbatim
  ==============================================================================
                        ##### FSMC peripheral features #####
  ==============================================================================
  [..] The Flexible memory controller (FSMC) includes following memory controllers:
       (+) The NOR/PSRAM memory controller
       (+) The NAND/PC Card memory controller

  [..] The FSMC functional block makes the interface with synchronous and asynchronous static
       memories and 16-bit PC memory cards. Its main purposes are:
       (+) to translate AHB transactions into the appropriate external device protocol
       (+) to meet the access time requirements of the external memory devices

  [..] All external memories share the addresses, data and control signals with the controller.
       Each external device is accessed by means of a unique Chip Select. The FSMC performs
       only one access at a time to an external device.
       The main features of the FSMC controller are the following:
        (+) Interface with static-memory mapped devices including:
           (++) Static random access memory (SRAM)
           (++) Read-only memory (ROM)
           (++) NOR Flash memory/OneNAND Flash memory
           (++) PSRAM (4 memory banks)
           (++) 16-bit PC Card compatible devices
           (++) Two banks of NAND Flash memory with ECC hardware to check up to 8 Kbytes of
                data
        (+) Independent Chip Select control for each memory bank
        (+) Independent configuration for each memory bank

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */
#if defined(HAL_NOR_MODULE_ENABLED) || defined(HAL_SRAM_MODULE_ENABLED) || defined(HAL_NAND_MODULE_ENABLED) || defined(HAL_PCCARD_MODULE_ENABLED)

/** @defgroup FSMC_LL  FSMC Low Layer
  * @brief FSMC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup FSMC_LL_Private_Constants FSMC Low Layer Private Constants
  * @{
  */

/* ----------------------- FSMC registers bit mask --------------------------- */

#if defined(FSMC_BANK1)
/* --- BCR Register ---*/
/* BCR register clear mask */

/* --- BTR Register ---*/
/* BTR register clear mask */
#define BTR_CLEAR_MASK    ((uint32_t)(FSMC_BTRx_ADDSET | FSMC_BTRx_ADDHLD  |\
                                      FSMC_BTRx_DATAST | FSMC_BTRx_BUSTURN |\
                                      FSMC_BTRx_CLKDIV | FSMC_BTRx_DATLAT  |\
                                      FSMC_BTRx_ACCMOD))

/* --- BWTR Register ---*/
/* BWTR register clear mask */
#if defined(FSMC_BWTRx_BUSTURN)
#define BWTR_CLEAR_MASK   ((uint32_t)(FSMC_BWTRx_ADDSET | FSMC_BWTRx_ADDHLD  |\
                                      FSMC_BWTRx_DATAST | FSMC_BWTRx_BUSTURN |\
                                      FSMC_BWTRx_ACCMOD))
#else
#define BWTR_CLEAR_MASK   ((uint32_t)(FSMC_BWTRx_ADDSET | FSMC_BWTRx_ADDHLD |\
                                      FSMC_BWTRx_DATAST | FSMC_BWTRx_ACCMOD |\
                                      FSMC_BWTRx_CLKDIV | FSMC_BWTRx_DATLAT))
#endif /* FSMC_BWTRx_BUSTURN */
#endif /* FSMC_BANK1 */
#if defined(FSMC_BANK3)

/* --- PCR Register ---*/
/* PCR register clear mask */
#define PCR_CLEAR_MASK    ((uint32_t)(FSMC_PCRx_PWAITEN | FSMC_PCRx_PBKEN  | \
                                      FSMC_PCRx_PTYP    | FSMC_PCRx_PWID   | \
                                      FSMC_PCRx_ECCEN   | FSMC_PCRx_TCLR   | \
                                      FSMC_PCRx_TAR     | FSMC_PCRx_ECCPS))
/* --- PMEM Register ---*/
/* PMEM register clear mask */
#define PMEM_CLEAR_MASK   ((uint32_t)(FSMC_PMEMx_MEMSETx  | FSMC_PMEMx_MEMWAITx |\
                                      FSMC_PMEMx_MEMHOLDx | FSMC_PMEMx_MEMHIZx))

/* --- PATT Register ---*/
/* PATT register clear mask */
#define PATT_CLEAR_MASK   ((uint32_t)(FSMC_PATTx_ATTSETx  | FSMC_PATTx_ATTWAITx |\
                                      FSMC_PATTx_ATTHOLDx | FSMC_PATTx_ATTHIZx))

#endif /* FSMC_BANK3 */
#if defined(FSMC_BANK4)
/* --- PCR Register ---*/
/* PCR register clear mask */
#define PCR4_CLEAR_MASK   ((uint32_t)(FSMC_PCR4_PWAITEN | FSMC_PCR4_PBKEN  | \
                                      FSMC_PCR4_PTYP    | FSMC_PCR4_PWID   | \
                                      FSMC_PCR4_ECCEN   | FSMC_PCR4_TCLR   | \
                                      FSMC_PCR4_TAR     | FSMC_PCR4_ECCPS))
/* --- PMEM Register ---*/
/* PMEM register clear mask */
#define PMEM4_CLEAR_MASK  ((uint32_t)(FSMC_PMEM4_MEMSET4  | FSMC_PMEM4_MEMWAIT4 |\
                                      FSMC_PMEM4_MEMHOLD4 | FSMC_PMEM4_MEMHIZ4))

/* --- PATT Register ---*/
/* PATT register clear mask */
#define PATT4_CLEAR_MASK  ((uint32_t)(FSMC_PATT4_ATTSET4  | FSMC_PATT4_ATTWAIT4 |\
                                      FSMC_PATT4_ATTHOLD4 | FSMC_PATT4_ATTHIZ4))

/* --- PIO4 Register ---*/
/* PIO4 register clear mask */
#define PIO4_CLEAR_MASK   ((uint32_t)(FSMC_PIO4_IOSET4  | FSMC_PIO4_IOWAIT4 | \
                                      FSMC_PIO4_IOHOLD4 | FSMC_PIO4_IOHIZ4))

#endif /* FSMC_BANK4 */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup FSMC_LL_Exported_Functions FSMC Low Layer Exported Functions
  * @{
  */

#if defined(FSMC_BANK1)

/** @defgroup FSMC_LL_Exported_Functions_NORSRAM FSMC Low Layer NOR SRAM Exported Functions
  * @brief  NORSRAM Controller functions
  *
  @verbatim
  ==============================================================================
                   ##### How to use NORSRAM device driver #####
  ==============================================================================

  [..]
    This driver contains a set of APIs to interface with the FSMC NORSRAM banks in order
    to run the NORSRAM external devices.

    (+) FSMC NORSRAM bank reset using the function FSMC_NORSRAM_DeInit()
    (+) FSMC NORSRAM bank control configuration using the function FSMC_NORSRAM_Init()
    (+) FSMC NORSRAM bank timing configuration using the function FSMC_NORSRAM_Timing_Init()
    (+) FSMC NORSRAM bank extended timing configuration using the function
        FSMC_NORSRAM_Extended_Timing_Init()
    (+) FSMC NORSRAM bank enable/disable write operation using the functions
        FSMC_NORSRAM_WriteOperation_Enable()/FSMC_NORSRAM_WriteOperation_Disable()

@endverbatim
  * @{
  */

/** @defgroup FSMC_LL_NORSRAM_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and Configuration functions
  *
  @verbatim
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the FSMC NORSRAM interface
    (+) De-initialize the FSMC NORSRAM interface
    (+) Configure the FSMC clock and associated GPIOs

@endverbatim
  * @{
  */

/**
  * @brief  Initialize the FSMC_NORSRAM device according to the specified
  *         control parameters in the FSMC_NORSRAM_InitTypeDef
  * @param  Device Pointer to NORSRAM device instance
  * @param  Init Pointer to NORSRAM Initialization structure
  * @retval HAL status
  */
HAL_StatusTypeDef  FSMC_NORSRAM_Init(FSMC_NORSRAM_TypeDef *Device,
                                    FSMC_NORSRAM_InitTypeDef *Init)
{
  uint32_t flashaccess;
  uint32_t btcr_reg;
  uint32_t mask;

  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FSMC_NORSRAM_BANK(Init->NSBank));
  assert_param(IS_FSMC_MUX(Init->DataAddressMux));
  assert_param(IS_FSMC_MEMORY(Init->MemoryType));
  assert_param(IS_FSMC_NORSRAM_MEMORY_WIDTH(Init->MemoryDataWidth));
  assert_param(IS_FSMC_BURSTMODE(Init->BurstAccessMode));
  assert_param(IS_FSMC_WAIT_POLARITY(Init->WaitSignalPolarity));
  assert_param(IS_FSMC_WRAP_MODE(Init->WrapMode));
  assert_param(IS_FSMC_WAIT_SIGNAL_ACTIVE(Init->WaitSignalActive));
  assert_param(IS_FSMC_WRITE_OPERATION(Init->WriteOperation));
  assert_param(IS_FSMC_WAITE_SIGNAL(Init->WaitSignal));
  assert_param(IS_FSMC_EXTENDED_MODE(Init->ExtendedMode));
  assert_param(IS_FSMC_ASYNWAIT(Init->AsynchronousWait));
  assert_param(IS_FSMC_WRITE_BURST(Init->WriteBurst));
  assert_param(IS_FSMC_PAGESIZE(Init->PageSize));

  /* Disable NORSRAM Device */
  __FSMC_NORSRAM_DISABLE(Device, Init->NSBank);

  /* Set NORSRAM device control parameters */
  if (Init->MemoryType == FSMC_MEMORY_TYPE_NOR)
  {
    flashaccess = FSMC_NORSRAM_FLASH_ACCESS_ENABLE;
  }
  else
  {
    flashaccess = FSMC_NORSRAM_FLASH_ACCESS_DISABLE;
  }

  btcr_reg = (flashaccess                   | \
              Init->DataAddressMux          | \
              Init->MemoryType              | \
              Init->MemoryDataWidth         | \
              Init->BurstAccessMode         | \
              Init->WaitSignalPolarity      | \
              Init->WaitSignalActive        | \
              Init->WriteOperation          | \
              Init->WaitSignal              | \
              Init->ExtendedMode            | \
              Init->AsynchronousWait        | \
              Init->WriteBurst);

  btcr_reg |= Init->WrapMode;
  btcr_reg |= Init->PageSize;

  mask = (FSMC_BCRx_MBKEN                |
          FSMC_BCRx_MUXEN                |
          FSMC_BCRx_MTYP                 |
          FSMC_BCRx_MWID                 |
          FSMC_BCRx_FACCEN               |
          FSMC_BCRx_BURSTEN              |
          FSMC_BCRx_WAITPOL              |
          FSMC_BCRx_WAITCFG              |
          FSMC_BCRx_WREN                 |
          FSMC_BCRx_WAITEN               |
          FSMC_BCRx_EXTMOD               |
          FSMC_BCRx_ASYNCWAIT            |
          FSMC_BCRx_CBURSTRW);

  mask |= FSMC_BCRx_WRAPMOD;
  mask |= 0x00070000U; /* CPSIZE to be defined in CMSIS file */

  MODIFY_REG(Device->BTCR[Init->NSBank], mask, btcr_reg);


  return HAL_OK;
}

/**
  * @brief  DeInitialize the FSMC_NORSRAM peripheral
  * @param  Device Pointer to NORSRAM device instance
  * @param  ExDevice Pointer to NORSRAM extended mode device instance
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_DeInit(FSMC_NORSRAM_TypeDef *Device,
                                     FSMC_NORSRAM_EXTENDED_TypeDef *ExDevice, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FSMC_NORSRAM_EXTENDED_DEVICE(ExDevice));
  assert_param(IS_FSMC_NORSRAM_BANK(Bank));

  /* Disable the FSMC_NORSRAM device */
  __FSMC_NORSRAM_DISABLE(Device, Bank);

  /* De-initialize the FSMC_NORSRAM device */
  /* FSMC_NORSRAM_BANK1 */
  if (Bank == FSMC_NORSRAM_BANK1)
  {
    Device->BTCR[Bank] = 0x000030DBU;
  }
  /* FSMC_NORSRAM_BANK2, FSMC_NORSRAM_BANK3 or FSMC_NORSRAM_BANK4 */
  else
  {
    Device->BTCR[Bank] = 0x000030D2U;
  }

  Device->BTCR[Bank + 1U] = 0x0FFFFFFFU;
  ExDevice->BWTR[Bank]   = 0x0FFFFFFFU;

  return HAL_OK;
}

/**
  * @brief  Initialize the FSMC_NORSRAM Timing according to the specified
  *         parameters in the FSMC_NORSRAM_TimingTypeDef
  * @param  Device Pointer to NORSRAM device instance
  * @param  Timing Pointer to NORSRAM Timing structure
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_Timing_Init(FSMC_NORSRAM_TypeDef *Device,
                                          FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank)
{

  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FSMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
  assert_param(IS_FSMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
  assert_param(IS_FSMC_DATASETUP_TIME(Timing->DataSetupTime));
  assert_param(IS_FSMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
  assert_param(IS_FSMC_CLK_DIV(Timing->CLKDivision));
  assert_param(IS_FSMC_DATA_LATENCY(Timing->DataLatency));
  assert_param(IS_FSMC_ACCESS_MODE(Timing->AccessMode));
  assert_param(IS_FSMC_NORSRAM_BANK(Bank));

  /* Set FSMC_NORSRAM device timing parameters */
  MODIFY_REG(Device->BTCR[Bank + 1U], BTR_CLEAR_MASK, (Timing->AddressSetupTime                                  |
                                                       ((Timing->AddressHoldTime)        << FSMC_BTRx_ADDHLD_Pos)  |
                                                       ((Timing->DataSetupTime)          << FSMC_BTRx_DATAST_Pos)  |
                                                       ((Timing->BusTurnAroundDuration)  << FSMC_BTRx_BUSTURN_Pos) |
                                                       (((Timing->CLKDivision) - 1U)     << FSMC_BTRx_CLKDIV_Pos)  |
                                                       (((Timing->DataLatency) - 2U)     << FSMC_BTRx_DATLAT_Pos)  |
                                                       (Timing->AccessMode)));

  return HAL_OK;
}

/**
  * @brief  Initialize the FSMC_NORSRAM Extended mode Timing according to the specified
  *         parameters in the FSMC_NORSRAM_TimingTypeDef
  * @param  Device Pointer to NORSRAM device instance
  * @param  Timing Pointer to NORSRAM Timing structure
  * @param  Bank NORSRAM bank number
  * @param  ExtendedMode FSMC Extended Mode
  *          This parameter can be one of the following values:
  *            @arg FSMC_EXTENDED_MODE_DISABLE
  *            @arg FSMC_EXTENDED_MODE_ENABLE
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_Extended_Timing_Init(FSMC_NORSRAM_EXTENDED_TypeDef *Device,
                                                   FSMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank,
                                                   uint32_t ExtendedMode)
{
  /* Check the parameters */
  assert_param(IS_FSMC_EXTENDED_MODE(ExtendedMode));

  /* Set NORSRAM device timing register for write configuration, if extended mode is used */
  if (ExtendedMode == FSMC_EXTENDED_MODE_ENABLE)
  {
    /* Check the parameters */
    assert_param(IS_FSMC_NORSRAM_EXTENDED_DEVICE(Device));
    assert_param(IS_FSMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
    assert_param(IS_FSMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
    assert_param(IS_FSMC_DATASETUP_TIME(Timing->DataSetupTime));
#if defined(FSMC_BWTRx_BUSTURN)
    assert_param(IS_FSMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
#else
    assert_param(IS_FSMC_CLK_DIV(Timing->CLKDivision));
    assert_param(IS_FSMC_DATA_LATENCY(Timing->DataLatency));
#endif /* FSMC_BWTRx_BUSTURN */
    assert_param(IS_FSMC_ACCESS_MODE(Timing->AccessMode));
    assert_param(IS_FSMC_NORSRAM_BANK(Bank));

    /* Set NORSRAM device timing register for write configuration, if extended mode is used */
#if defined(FSMC_BWTRx_BUSTURN)
    MODIFY_REG(Device->BWTR[Bank], BWTR_CLEAR_MASK, (Timing->AddressSetupTime                                    |
                                                     ((Timing->AddressHoldTime)        << FSMC_BWTRx_ADDHLD_Pos)  |
                                                     ((Timing->DataSetupTime)          << FSMC_BWTRx_DATAST_Pos)  |
                                                     Timing->AccessMode                                          |
                                                     ((Timing->BusTurnAroundDuration)  << FSMC_BWTRx_BUSTURN_Pos)));
#else
    MODIFY_REG(Device->BWTR[Bank], BWTR_CLEAR_MASK, (Timing->AddressSetupTime                                    |
                                                     ((Timing->AddressHoldTime)        << FSMC_BWTRx_ADDHLD_Pos)  |
                                                     ((Timing->DataSetupTime)          << FSMC_BWTRx_DATAST_Pos)  |
                                                     Timing->AccessMode                                          |
                                                     (((Timing->CLKDivision) - 1U)     << FSMC_BWTRx_CLKDIV_Pos)  |
                                                     (((Timing->DataLatency) - 2U)     << FSMC_BWTRx_DATLAT_Pos)));
#endif /* FSMC_BWTRx_BUSTURN */
  }
  else
  {
    Device->BWTR[Bank] = 0x0FFFFFFFU;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup FSMC_LL_NORSRAM_Private_Functions_Group2
  *  @brief   management functions
  *
@verbatim
  ==============================================================================
                      ##### FSMC_NORSRAM Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control dynamically
    the FSMC NORSRAM interface.

@endverbatim
  * @{
  */

/**
  * @brief  Enables dynamically FSMC_NORSRAM write operation.
  * @param  Device Pointer to NORSRAM device instance
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_WriteOperation_Enable(FSMC_NORSRAM_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FSMC_NORSRAM_BANK(Bank));

  /* Enable write operation */
  SET_BIT(Device->BTCR[Bank], FSMC_WRITE_OPERATION_ENABLE);

  return HAL_OK;
}

/**
  * @brief  Disables dynamically FSMC_NORSRAM write operation.
  * @param  Device Pointer to NORSRAM device instance
  * @param  Bank NORSRAM bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NORSRAM_WriteOperation_Disable(FSMC_NORSRAM_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NORSRAM_DEVICE(Device));
  assert_param(IS_FSMC_NORSRAM_BANK(Bank));

  /* Disable write operation */
  CLEAR_BIT(Device->BTCR[Bank], FSMC_WRITE_OPERATION_ENABLE);

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* FSMC_BANK1 */

#if defined(FSMC_BANK3)

/** @defgroup FSMC_LL_Exported_Functions_NAND FSMC Low Layer NAND Exported Functions
  * @brief    NAND Controller functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use NAND device driver #####
  ==============================================================================
  [..]
    This driver contains a set of APIs to interface with the FSMC NAND banks in order
    to run the NAND external devices.

    (+) FSMC NAND bank reset using the function FSMC_NAND_DeInit()
    (+) FSMC NAND bank control configuration using the function FSMC_NAND_Init()
    (+) FSMC NAND bank common space timing configuration using the function
        FSMC_NAND_CommonSpace_Timing_Init()
    (+) FSMC NAND bank attribute space timing configuration using the function
        FSMC_NAND_AttributeSpace_Timing_Init()
    (+) FSMC NAND bank enable/disable ECC correction feature using the functions
        FSMC_NAND_ECC_Enable()/FSMC_NAND_ECC_Disable()
    (+) FSMC NAND bank get ECC correction code using the function FSMC_NAND_GetECC()

@endverbatim
  * @{
  */

/** @defgroup FSMC_LL_NAND_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the FSMC NAND interface
    (+) De-initialize the FSMC NAND interface
    (+) Configure the FSMC clock and associated GPIOs

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the FSMC_NAND device according to the specified
  *         control parameters in the FSMC_NAND_HandleTypeDef
  * @param  Device Pointer to NAND device instance
  * @param  Init Pointer to NAND Initialization structure
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_Init(FSMC_NAND_TypeDef *Device, FSMC_NAND_InitTypeDef *Init)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NAND_DEVICE(Device));
  assert_param(IS_FSMC_NAND_BANK(Init->NandBank));
  assert_param(IS_FSMC_WAIT_FEATURE(Init->Waitfeature));
  assert_param(IS_FSMC_NAND_MEMORY_WIDTH(Init->MemoryDataWidth));
  assert_param(IS_FSMC_ECC_STATE(Init->EccComputation));
  assert_param(IS_FSMC_ECCPAGE_SIZE(Init->ECCPageSize));
  assert_param(IS_FSMC_TCLR_TIME(Init->TCLRSetupTime));
  assert_param(IS_FSMC_TAR_TIME(Init->TARSetupTime));

  /* Set NAND device control parameters */
  if (Init->NandBank == FSMC_NAND_BANK2)
  {
    /* NAND bank 2 registers configuration */
    MODIFY_REG(Device->PCR2, PCR_CLEAR_MASK, (Init->Waitfeature                                      |
                                              FSMC_PCR_MEMORY_TYPE_NAND                               |
                                              Init->MemoryDataWidth                                  |
                                              Init->EccComputation                                   |
                                              Init->ECCPageSize                                      |
                                              ((Init->TCLRSetupTime) << FSMC_PCRx_TCLR_Pos)  |
                                              ((Init->TARSetupTime)  << FSMC_PCRx_TAR_Pos)));
  }
  else
  {
    /* NAND bank 3 registers configuration */
    MODIFY_REG(Device->PCR3, PCR_CLEAR_MASK, (Init->Waitfeature                                      |
                                              FSMC_PCR_MEMORY_TYPE_NAND                               |
                                              Init->MemoryDataWidth                                  |
                                              Init->EccComputation                                   |
                                              Init->ECCPageSize                                      |
                                              ((Init->TCLRSetupTime) << FSMC_PCRx_TCLR_Pos)  |
                                              ((Init->TARSetupTime)  << FSMC_PCRx_TAR_Pos)));
  }

  return HAL_OK;
}

/**
  * @brief  Initializes the FSMC_NAND Common space Timing according to the specified
  *         parameters in the FSMC_NAND_PCC_TimingTypeDef
  * @param  Device Pointer to NAND device instance
  * @param  Timing Pointer to NAND timing structure
  * @param  Bank NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_CommonSpace_Timing_Init(FSMC_NAND_TypeDef *Device,
                                                   FSMC_NAND_PCC_TimingTypeDef *Timing, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NAND_DEVICE(Device));
  assert_param(IS_FSMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(Timing->HiZSetupTime));
  assert_param(IS_FSMC_NAND_BANK(Bank));

  /* Set FSMC_NAND device timing parameters */
  if (Bank == FSMC_NAND_BANK2)
  {
    /* NAND bank 2 registers configuration */
    MODIFY_REG(Device->PMEM2, PMEM_CLEAR_MASK, (Timing->SetupTime                                             |
                                                ((Timing->WaitSetupTime) << FSMC_PMEMx_MEMWAITx_Pos) |
                                                ((Timing->HoldSetupTime) << FSMC_PMEMx_MEMHOLDx_Pos) |
                                                ((Timing->HiZSetupTime)  << FSMC_PMEMx_MEMHIZx_Pos)));
  }
  else
  {
    /* NAND bank 3 registers configuration */
    MODIFY_REG(Device->PMEM3, PMEM_CLEAR_MASK, (Timing->SetupTime                                             |
                                                ((Timing->WaitSetupTime) << FSMC_PMEMx_MEMWAITx_Pos) |
                                                ((Timing->HoldSetupTime) << FSMC_PMEMx_MEMHOLDx_Pos) |
                                                ((Timing->HiZSetupTime)  << FSMC_PMEMx_MEMHIZx_Pos)));
  }

  return HAL_OK;
}

/**
  * @brief  Initializes the FSMC_NAND Attribute space Timing according to the specified
  *         parameters in the FSMC_NAND_PCC_TimingTypeDef
  * @param  Device Pointer to NAND device instance
  * @param  Timing Pointer to NAND timing structure
  * @param  Bank NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_AttributeSpace_Timing_Init(FSMC_NAND_TypeDef *Device,
                                                      FSMC_NAND_PCC_TimingTypeDef *Timing, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NAND_DEVICE(Device));
  assert_param(IS_FSMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(Timing->HiZSetupTime));
  assert_param(IS_FSMC_NAND_BANK(Bank));

  /* Set FSMC_NAND device timing parameters */
  if (Bank == FSMC_NAND_BANK2)
  {
    /* NAND bank 2 registers configuration */
    MODIFY_REG(Device->PATT2, PATT_CLEAR_MASK, (Timing->SetupTime                                             |
                                                ((Timing->WaitSetupTime) << FSMC_PATTx_ATTWAITx_Pos) |
                                                ((Timing->HoldSetupTime) << FSMC_PATTx_ATTHOLDx_Pos) |
                                                ((Timing->HiZSetupTime)  << FSMC_PATTx_ATTHIZx_Pos)));
  }
  else
  {
    /* NAND bank 3 registers configuration */
    MODIFY_REG(Device->PATT3, PATT_CLEAR_MASK, (Timing->SetupTime                                             |
                                                ((Timing->WaitSetupTime) << FSMC_PATTx_ATTWAITx_Pos) |
                                                ((Timing->HoldSetupTime) << FSMC_PATTx_ATTHOLDx_Pos) |
                                                ((Timing->HiZSetupTime)  << FSMC_PATTx_ATTHIZx_Pos)));
  }

  return HAL_OK;
}

/**
  * @brief  DeInitializes the FSMC_NAND device
  * @param  Device Pointer to NAND device instance
  * @param  Bank NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_DeInit(FSMC_NAND_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NAND_DEVICE(Device));
  assert_param(IS_FSMC_NAND_BANK(Bank));

  /* Disable the NAND Bank */
  __FSMC_NAND_DISABLE(Device, Bank);

  /* De-initialize the NAND Bank */
  if (Bank == FSMC_NAND_BANK2)
  {
    /* Set the FSMC_NAND_BANK2 registers to their reset values */
    WRITE_REG(Device->PCR2,  0x00000018U);
    WRITE_REG(Device->SR2,   0x00000040U);
    WRITE_REG(Device->PMEM2, 0xFCFCFCFCU);
    WRITE_REG(Device->PATT2, 0xFCFCFCFCU);
  }
  /* FSMC_Bank3_NAND */
  else
  {
    /* Set the FSMC_NAND_BANK3 registers to their reset values */
    WRITE_REG(Device->PCR3,  0x00000018U);
    WRITE_REG(Device->SR3,   0x00000040U);
    WRITE_REG(Device->PMEM3, 0xFCFCFCFCU);
    WRITE_REG(Device->PATT3, 0xFCFCFCFCU);
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup HAL_FSMC_NAND_Group2 Peripheral Control functions
  *  @brief   management functions
  *
@verbatim
  ==============================================================================
                       ##### FSMC_NAND Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control dynamically
    the FSMC NAND interface.

@endverbatim
  * @{
  */


/**
  * @brief  Enables dynamically FSMC_NAND ECC feature.
  * @param  Device Pointer to NAND device instance
  * @param  Bank NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_ECC_Enable(FSMC_NAND_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NAND_DEVICE(Device));
  assert_param(IS_FSMC_NAND_BANK(Bank));

  /* Enable ECC feature */
  if (Bank == FSMC_NAND_BANK2)
  {
    SET_BIT(Device->PCR2, FSMC_PCRx_ECCEN);
  }
  else
  {
    SET_BIT(Device->PCR3, FSMC_PCRx_ECCEN);
  }

  return HAL_OK;
}


/**
  * @brief  Disables dynamically FSMC_NAND ECC feature.
  * @param  Device Pointer to NAND device instance
  * @param  Bank NAND bank number
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_ECC_Disable(FSMC_NAND_TypeDef *Device, uint32_t Bank)
{
  /* Check the parameters */
  assert_param(IS_FSMC_NAND_DEVICE(Device));
  assert_param(IS_FSMC_NAND_BANK(Bank));

  /* Disable ECC feature */
  if (Bank == FSMC_NAND_BANK2)
  {
    CLEAR_BIT(Device->PCR2, FSMC_PCRx_ECCEN);
  }
  else
  {
    CLEAR_BIT(Device->PCR3, FSMC_PCRx_ECCEN);
  }

  return HAL_OK;
}

/**
  * @brief  Disables dynamically FSMC_NAND ECC feature.
  * @param  Device Pointer to NAND device instance
  * @param  ECCval Pointer to ECC value
  * @param  Bank NAND bank number
  * @param  Timeout Timeout wait value
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_NAND_GetECC(FSMC_NAND_TypeDef *Device, uint32_t *ECCval, uint32_t Bank,
                                  uint32_t Timeout)
{
  uint32_t tickstart;

  /* Check the parameters */
  assert_param(IS_FSMC_NAND_DEVICE(Device));
  assert_param(IS_FSMC_NAND_BANK(Bank));

  /* Get tick */
  tickstart = HAL_GetTick();

  /* Wait until FIFO is empty */
  while (__FSMC_NAND_GET_FLAG(Device, Bank, FSMC_FLAG_FEMPT) == RESET)
  {
    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        return HAL_TIMEOUT;
      }
    }
  }

  if (Bank == FSMC_NAND_BANK2)
  {
    /* Get the ECCR2 register value */
    *ECCval = (uint32_t)Device->ECCR2;
  }
  else
  {
    /* Get the ECCR3 register value */
    *ECCval = (uint32_t)Device->ECCR3;
  }

  return HAL_OK;
}

/**
  * @}
  */
#endif /* FSMC_BANK3 */

#if defined(FSMC_BANK4)

/** @addtogroup FSMC_LL_PCCARD
  * @brief    PCCARD Controller functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use PCCARD device driver #####
  ==============================================================================
  [..]
    This driver contains a set of APIs to interface with the FSMC PCCARD bank in order
    to run the PCCARD/compact flash external devices.

    (+) FSMC PCCARD bank reset using the function FSMC_PCCARD_DeInit()
    (+) FSMC PCCARD bank control configuration using the function FSMC_PCCARD_Init()
    (+) FSMC PCCARD bank common space timing configuration using the function
        FSMC_PCCARD_CommonSpace_Timing_Init()
    (+) FSMC PCCARD bank attribute space timing configuration using the function
        FSMC_PCCARD_AttributeSpace_Timing_Init()
    (+) FSMC PCCARD bank IO space timing configuration using the function
        FSMC_PCCARD_IOSpace_Timing_Init()
@endverbatim
  * @{
  */

/** @addtogroup FSMC_LL_PCCARD_Private_Functions_Group1
  *  @brief    Initialization and Configuration functions
  *
@verbatim
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the FSMC PCCARD interface
    (+) De-initialize the FSMC PCCARD interface
    (+) Configure the FSMC clock and associated GPIOs

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the FSMC_PCCARD device according to the specified
  *         control parameters in the FSMC_PCCARD_HandleTypeDef
  * @param  Device Pointer to PCCARD device instance
  * @param  Init Pointer to PCCARD Initialization structure
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_PCCARD_Init(FSMC_PCCARD_TypeDef *Device, FSMC_PCCARD_InitTypeDef *Init)
{
  /* Check the parameters */
  assert_param(IS_FSMC_PCCARD_DEVICE(Device));
#if defined(FSMC_BANK3)
  assert_param(IS_FSMC_WAIT_FEATURE(Init->Waitfeature));
  assert_param(IS_FSMC_TCLR_TIME(Init->TCLRSetupTime));
  assert_param(IS_FSMC_TAR_TIME(Init->TARSetupTime));
#endif /* FSMC_BANK3 */

  /* Set FSMC_PCCARD device control parameters */
  MODIFY_REG(Device->PCR4,
             (FSMC_PCRx_PTYP                                          |
              FSMC_PCRx_PWAITEN                                       |
              FSMC_PCRx_PWID                                          |
              FSMC_PCRx_TCLR                                          |
              FSMC_PCRx_TAR),
             (FSMC_PCR_MEMORY_TYPE_PCCARD                             |
              Init->Waitfeature                                      |
              FSMC_NAND_PCC_MEM_BUS_WIDTH_16                          |
              (Init->TCLRSetupTime << FSMC_PCRx_TCLR_Pos)   |
              (Init->TARSetupTime  << FSMC_PCRx_TAR_Pos)));

  return HAL_OK;
}

/**
  * @brief  Initializes the FSMC_PCCARD Common space Timing according to the specified
  *         parameters in the FSMC_NAND_PCC_TimingTypeDef
  * @param  Device Pointer to PCCARD device instance
  * @param  Timing Pointer to PCCARD timing structure
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_PCCARD_CommonSpace_Timing_Init(FSMC_PCCARD_TypeDef *Device,
                                                              FSMC_NAND_PCC_TimingTypeDef *Timing)
{
  /* Check the parameters */
  assert_param(IS_FSMC_PCCARD_DEVICE(Device));
#if defined(FSMC_BANK3)
  assert_param(IS_FSMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(Timing->HiZSetupTime));
#endif /* FSMC_BANK3 */

  /* Set PCCARD timing parameters */
  MODIFY_REG(Device->PMEM4, PMEM_CLEAR_MASK,
             (Timing->SetupTime                                              |
              ((Timing->WaitSetupTime) << FSMC_PMEMx_MEMWAITx_Pos)  |
              ((Timing->HoldSetupTime) << FSMC_PMEMx_MEMHOLDx_Pos)  |
              ((Timing->HiZSetupTime)  << FSMC_PMEMx_MEMHIZx_Pos)));

  return HAL_OK;
}

/**
  * @brief  Initializes the FSMC_PCCARD Attribute space Timing according to the specified
  *         parameters in the FSMC_NAND_PCC_TimingTypeDef
  * @param  Device Pointer to PCCARD device instance
  * @param  Timing Pointer to PCCARD timing structure
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_PCCARD_AttributeSpace_Timing_Init(FSMC_PCCARD_TypeDef *Device,
                                                                 FSMC_NAND_PCC_TimingTypeDef *Timing)
{
  /* Check the parameters */
  assert_param(IS_FSMC_PCCARD_DEVICE(Device));
#if defined(FSMC_BANK3)
  assert_param(IS_FSMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(Timing->HiZSetupTime));
#endif /* FSMC_BANK3 */

  /* Set PCCARD timing parameters */
  MODIFY_REG(Device->PATT4, PATT_CLEAR_MASK,
             (Timing->SetupTime                                              |
              ((Timing->WaitSetupTime) << FSMC_PATTx_ATTWAITx_Pos)  |
              ((Timing->HoldSetupTime) << FSMC_PATTx_ATTHOLDx_Pos)  |
              ((Timing->HiZSetupTime)  << FSMC_PATTx_ATTHIZx_Pos)));

  return HAL_OK;
}

/**
  * @brief  Initializes the FSMC_PCCARD IO space Timing according to the specified
  *         parameters in the FSMC_NAND_PCC_TimingTypeDef
  * @param  Device Pointer to PCCARD device instance
  * @param  Timing Pointer to PCCARD timing structure
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_PCCARD_IOSpace_Timing_Init(FSMC_PCCARD_TypeDef *Device,
                                                          FSMC_NAND_PCC_TimingTypeDef *Timing)
{
  /* Check the parameters */
  assert_param(IS_FSMC_PCCARD_DEVICE(Device));
#if defined(FSMC_BANK3)
  assert_param(IS_FSMC_SETUP_TIME(Timing->SetupTime));
  assert_param(IS_FSMC_WAIT_TIME(Timing->WaitSetupTime));
  assert_param(IS_FSMC_HOLD_TIME(Timing->HoldSetupTime));
  assert_param(IS_FSMC_HIZ_TIME(Timing->HiZSetupTime));
#endif /* FSMC_BANK3 */

  /* Set FSMC_PCCARD device timing parameters */
  MODIFY_REG(Device->PIO4, PIO4_CLEAR_MASK,
             (Timing->SetupTime                                           |
              (Timing->WaitSetupTime   << FSMC_PIO4_IOWAIT4_Pos) |
              (Timing->HoldSetupTime   << FSMC_PIO4_IOHOLD4_Pos) |
              (Timing->HiZSetupTime    << FSMC_PIO4_IOHIZ4_Pos)));

  return HAL_OK;
}

/**
  * @brief  DeInitializes the FSMC_PCCARD device
  * @param  Device Pointer to PCCARD device instance
  * @retval HAL status
  */
HAL_StatusTypeDef FSMC_PCCARD_DeInit(FSMC_PCCARD_TypeDef *Device)
{
  /* Check the parameters */
  assert_param(IS_FSMC_PCCARD_DEVICE(Device));

  /* Disable the FSMC_PCCARD device */
  __FSMC_PCCARD_DISABLE(Device);

  /* De-initialize the FSMC_PCCARD device */
  Device->PCR4    = 0x00000018U;
  Device->SR4     = 0x00000040U;
  Device->PMEM4   = 0xFCFCFCFCU;
  Device->PATT4   = 0xFCFCFCFCU;
  Device->PIO4    = 0xFCFCFCFCU;

  return HAL_OK;
}

/**
  * @}
  */
#endif /* FSMC_BANK4 */


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
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
