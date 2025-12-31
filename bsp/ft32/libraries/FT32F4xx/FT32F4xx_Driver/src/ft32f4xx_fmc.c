/**
  ******************************************************************************
  * @file    ft32f4xx__fmc.c
  * @author  FMD AE
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Flexible Memory Controller (FMC) peripheral
  *          memories:
  *           + Initialization/de-initialization functions
  *           + Peripheral Control functions
  *           + Peripheral State functions
  * @version  V1.0.0
  * @date     2025-04-16
  ******************************************************************************
  @verbatim
  ==============================================================================
                        ##### FMC peripheral features #####
  ==============================================================================
  [..] The Flexible memory controller (FMC) includes following memory controllers:
       (+) The NOR/PSRAM memory controller
       (+) The NAND memory controller
       (+) The Synchronous DRAM (SDRAM) controller

  [..] The FMC functional block makes the interface with synchronous and asynchronous static
       memories, SDRAM memories. Its main purposes are:
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
           (++) Two banks of NAND Flash memory with ECC hardware to check up to 8 Kbytes of
                data
        (+) Interface with synchronous DRAM (SDRAM) memories
        (+) Independent Chip Select control for each memory bank
        (+) Independent configuration for each memory bank

  @endverbatim
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx_fmc.h"

/** @defgroup
  * @brief FMC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/** @defgroup FMC_Private_Constants FMC Private Constants
  * @{
  */

/* ----------------------- FMC registers bit mask --------------------------- */

#if defined(FMC_Bank1)
/* --- BCR Register ---*/
/* BCR register clear mask */

/* --- BTR Register ---*/
/* BTR register clear mask */
#define BTR_CLEAR_MASK    ((uint32_t)(FMC_BTR1_ADDSET | FMC_BTR1_ADDHLD  |\
                                      FMC_BTR1_DATAST | FMC_BTR1_BUSTURN |\
                                      FMC_BTR1_CLKDIV | FMC_BTR1_DATLAT  |\
                                      FMC_BTR1_ACCMOD))

/* --- BWTR Register ---*/
/* BWTR register clear mask */
#define BWTR_CLEAR_MASK   ((uint32_t)(FMC_BWTR1_ADDSET | FMC_BWTR1_ADDHLD  |\
                                      FMC_BWTR1_DATAST | FMC_BWTR1_BUSTURN |\
                                      FMC_BWTR1_ACCMOD))
#endif /* FMC_Bank1 */

#if defined(FMC_Bank3) || defined(FMC_Bank2_3)
/* --- PCR Register ---*/
/* PCR register clear mask */
#define PCR_CLEAR_MASK    ((uint32_t)(FMC_PCR2_PWAITEN | FMC_PCR2_PBKEN  | \
                                      FMC_PCR2_PTYP    | FMC_PCR2_PWID   | \
                                      FMC_PCR2_ECCEN   | FMC_PCR2_TCLR   | \
                                      FMC_PCR2_TAR     | FMC_PCR2_ECCPS))
/* --- PMEM Register ---*/
/* PMEM register clear mask */
#define PMEM_CLEAR_MASK   ((uint32_t)(FMC_PMEM2_MEMSET2  | FMC_PMEM2_MEMWAIT2 |\
                                      FMC_PMEM2_MEMHOLD2 | FMC_PMEM2_MEMHIZ2))

/* --- PATT Register ---*/
/* PATT register clear mask */
#define PATT_CLEAR_MASK   ((uint32_t)(FMC_PATT2_ATTSET2  | FMC_PATT2_ATTWAIT2 |\
                                      FMC_PATT2_ATTHOLD2 | FMC_PATT2_ATTHIZ2))

#endif /* FMC_Bank3) || defined(FMC_Bank2_3 */

#if defined(FMC_Bank5_6)
/* --- SDCR Register ---*/
/* SDCR register clear mask */
#define SDCR_CLEAR_MASK   ((uint32_t)(FMC_SDCR1_NC    | FMC_SDCR1_NR     | \
                                      FMC_SDCR1_MWID  | FMC_SDCR1_NB     | \
                                      FMC_SDCR1_CAS   | FMC_SDCR1_WP     | \
                                      FMC_SDCR1_SDCLK | FMC_SDCR1_RBURST | \
                                      FMC_SDCR1_RPIPE))

/* --- SDTR Register ---*/
/* SDTR register clear mask */
#define SDTR_CLEAR_MASK   ((uint32_t)(FMC_SDTR1_TMRD  | FMC_SDTR1_TXSR   | \
                                      FMC_SDTR1_TRAS  | FMC_SDTR1_TRC    | \
                                      FMC_SDTR1_TWR   | FMC_SDTR1_TRP    | \
                                      FMC_SDTR1_TRCD))
#endif /* FMC_Bank5_6 */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup FMC_Exported_Functions FMC Exported Functions
  * @{
  */

#if defined(FMC_Bank1)

/** @defgroup FMC_Exported_Functions_NORSRAM FMC NOR SRAM Exported Functions
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

/** @defgroup FMC_NORSRAM_Exported_Functions_Group1 Initialization and de-initialization functions
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
  *          This paramater can be FMC_NORSRAM_DEVICE
  * @param  Init Pointer to NORSRAM Initialization structure
  * @retval None
  */
void FMC_NORSRAM_Init(FMC_NORSRAM_TypeDef *Device, FMC_NORSRAM_InitTypeDef *Init)
{
    uint32_t flashaccess;
    uint32_t btcr_reg;
    uint32_t mask;
    uint32_t tmpreg;

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

    btcr_reg |= Init->ContinuousClock;
    btcr_reg |= Init->PageSize;

    mask = (FMC_BCR1_MBKEN                |
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
            FMC_BCR1_CBURSTRW);

    mask |= FMC_BCR1_CCLKEN;
    mask |= FMC_BCR1_CPSIZE;

    tmpreg = Device->BTCR[Init->NSBank];
    tmpreg &= (uint32_t)~((uint32_t)mask);
    tmpreg |= btcr_reg;

    Device->BTCR[Init->NSBank] = tmpreg;

    /* Configure synchronous mode when Continuous clock is enabled for bank2..4 */
    if ((Init->ContinuousClock == FMC_CONTINUOUS_CLOCK_SYNC_ASYNC) && (Init->NSBank != FMC_NORSRAM_BANK1))
    {
        tmpreg = Device->BTCR[FMC_NORSRAM_BANK1];
        tmpreg &= (uint32_t)~((uint32_t)FMC_BCR1_CCLKEN);
        tmpreg |= Init->ContinuousClock;

        Device->BTCR[FMC_NORSRAM_BANK1] = tmpreg;
    }
}

/**
  * @brief  DeInitialize the FMC_NORSRAM peripheral
  * @param  Device Pointer to NORSRAM device instance
  *          This paramater can be FMC_NORSRAM_DEVICE
  * @param  ExDevice Pointer to NORSRAM extended mode device instance
  *          This paramater can be FMC_NORSRAM_EXTENDED_DEVICE
  * @param  Bank NORSRAM bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NORSRAM_BANK1
  *            @arg FMC_NORSRAM_BANK2
  *            @arg FMC_NORSRAM_BANK3
  *            @arg FMC_NORSRAM_BANK4
  * @retval None
  */
void FMC_NORSRAM_DeInit(FMC_NORSRAM_TypeDef *Device, FMC_NORSRAM_EXTENDED_TypeDef *ExDevice, uint32_t Bank)
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
    ExDevice->BWTR[Bank]   = 0x0FFFFFFFU;
}

/**
  * @brief  Initialize the FMC_NORSRAM Timing according to the specified
  *         parameters in the FMC_NORSRAM_TimingTypeDef
  * @param  Device Pointer to NORSRAM device instance
  *          This paramater can be FMC_NORSRAM_DEVICE
  * @param  Timing Pointer to NORSRAM Timing structure
  * @param  Bank NORSRAM bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NORSRAM_BANK1
  *            @arg FMC_NORSRAM_BANK2
  *            @arg FMC_NORSRAM_BANK3
  *            @arg FMC_NORSRAM_BANK4
  * @retval None
  */
void FMC_NORSRAM_Timing_Init(FMC_NORSRAM_TypeDef *Device,
                             FMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank)
{
    uint32_t tmpr;
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_FMC_NORSRAM_DEVICE(Device));
    assert_param(IS_FMC_ADDRESS_SETUP_TIME(Timing->AddressSetupTime));
    assert_param(IS_FMC_ADDRESS_HOLD_TIME(Timing->AddressHoldTime));
    assert_param(IS_FMC_DATASETUP_TIME(Timing->DataSetupTime));
    assert_param(IS_FMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
    assert_param(IS_FMC_CLK_DIV(Timing->CLKDivision));
    assert_param(IS_FMC_DATA_LATENCY(Timing->DataLatency));
    assert_param(IS_FMC_ACCESS_MODE(Timing->AccessMode));
    assert_param(IS_FMC_NORSRAM_BANK(Bank));

    /* Set FMC_NORSRAM device timing parameters */
    tmpreg = Device->BTCR[Bank + 1U];
    tmpreg &= (uint32_t)~((uint32_t)BTR_CLEAR_MASK);
    tmpreg |= (Timing->AddressSetupTime                                   |
               ((Timing->AddressHoldTime)              << FMC_BTR1_ADDHLD_Pos)  |
               ((Timing->DataSetupTime)                << FMC_BTR1_DATAST_Pos)  |
               (((Timing->BusTurnAroundDuration) - 1U) << FMC_BTR1_BUSTURN_Pos) |
               (((Timing->CLKDivision) - 1U)           << FMC_BTR1_CLKDIV_Pos)  |
               (((Timing->DataLatency) - 2U)           << FMC_BTR1_DATLAT_Pos)  |
               (Timing->AccessMode));

    Device->BTCR[Bank + 1U] = tmpreg;

    /* Configure Clock division value (in NORSRAM bank 1) when continuous clock is enabled */
    if ((Device->BTCR[FMC_NORSRAM_BANK1] & FMC_BCR1_CCLKEN) != 0U)
    {
        tmpr = (uint32_t)(Device->BTCR[FMC_NORSRAM_BANK1 + 1U] & ~((0x0FU) << FMC_BTR1_CLKDIV_Pos));
        tmpr |= (uint32_t)(((Timing->CLKDivision) - 1U) << FMC_BTR1_CLKDIV_Pos);

        tmpreg = Device->BTCR[FMC_NORSRAM_BANK1 + 1U];
        tmpreg &= (uint32_t)~((uint32_t)FMC_BTR1_CLKDIV);
        tmpreg |= tmpr;

        Device->BTCR[FMC_NORSRAM_BANK1 + 1U] = tmpreg;
    }
}

/**
  * @brief  Initialize the FMC_NORSRAM Extended mode Timing according to the specified
  *         parameters in the FMC_NORSRAM_TimingTypeDef
  * @param  Device Pointer to NORSRAM device instance
  *          This paramater can be FMC_NORSRAM_EXTENDED_DEVICE
  * @param  Timing Pointer to NORSRAM Timing structure
  * @param  Bank NORSRAM bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NORSRAM_BANK1
  *            @arg FMC_NORSRAM_BANK2
  *            @arg FMC_NORSRAM_BANK3
  *            @arg FMC_NORSRAM_BANK4
  * @param  ExtendedMode FMC Extended Mode
  *          This parameter can be one of the following values:
  *            @arg FMC_EXTENDED_MODE_DISABLE
  *            @arg FMC_EXTENDED_MODE_ENABLE
  * @retval None
  */
void FMC_NORSRAM_Extended_Timing_Init(FMC_NORSRAM_EXTENDED_TypeDef *Device,
                                      FMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank,
                                      uint32_t ExtendedMode)
{
    uint32_t tmpreg;

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
        assert_param(IS_FMC_TURNAROUND_TIME(Timing->BusTurnAroundDuration));
        assert_param(IS_FMC_ACCESS_MODE(Timing->AccessMode));
        assert_param(IS_FMC_NORSRAM_BANK(Bank));

        /* Set NORSRAM device timing register for write configuration, if extended mode is used */
        tmpreg = Device->BWTR[Bank];
        tmpreg &= (uint32_t)~((uint32_t)BWTR_CLEAR_MASK);
        tmpreg |= (Timing->AddressSetupTime                                          |
                   ((Timing->AddressHoldTime)              << FMC_BWTR1_ADDHLD_Pos)  |
                   ((Timing->DataSetupTime)                << FMC_BWTR1_DATAST_Pos)  |
                   Timing->AccessMode                                                |
                   (((Timing->BusTurnAroundDuration) - 1U) << FMC_BTR1_BUSTURN_Pos));

        Device->BWTR[Bank] = tmpreg;
    }
    else
    {
        Device->BWTR[Bank] = 0x0FFFFFFFU;
    }

}
/**
  * @}
  */

/** @addtogroup FMC_NORSRAM_Private_Functions_Group2
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
  *          This paramater can be FMC_NORSRAM_DEVICE
  * @param  Bank NORSRAM bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NORSRAM_BANK1
  *            @arg FMC_NORSRAM_BANK2
  *            @arg FMC_NORSRAM_BANK3
  *            @arg FMC_NORSRAM_BANK4
  * @retval None
  */
void FMC_NORSRAM_WriteOperation_Enable(FMC_NORSRAM_TypeDef *Device, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_NORSRAM_DEVICE(Device));
    assert_param(IS_FMC_NORSRAM_BANK(Bank));

    /* Enable write operation */
    Device->BTCR[Bank] |= FMC_WRITE_OPERATION_ENABLE;
}

/**
  * @brief  Disables dynamically FMC_NORSRAM write operation.
  * @param  Device Pointer to NORSRAM device instance
  *          This paramater can be FMC_NORSRAM_DEVICE
  * @param  Bank NORSRAM bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NORSRAM_BANK1
  *            @arg FMC_NORSRAM_BANK2
  *            @arg FMC_NORSRAM_BANK3
  *            @arg FMC_NORSRAM_BANK4
  * @retval None
  */
void FMC_NORSRAM_WriteOperation_Disable(FMC_NORSRAM_TypeDef *Device, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_NORSRAM_DEVICE(Device));
    assert_param(IS_FMC_NORSRAM_BANK(Bank));

    /* Disable write operation */
    Device->BTCR[Bank] &= (uint32_t)~((uint32_t)FMC_WRITE_OPERATION_ENABLE);
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* FMC_Bank1 */

#if defined(FMC_Bank2_3)

/** @defgroup FMC_Exported_Functions_NAND FMC NAND Exported Functions
  * @brief    NAND Controller functions
  *
  @verbatim
  ==============================================================================
                    ##### How to use NAND device driver #####
  ==============================================================================
  [..]
    This driver contains a set of APIs to interface with the FMC NAND banks in order
    to run the NAND external devices.

    (+) FMC NAND bank reset using the function FMC_NAND_DeInit()
    (+) FMC NAND bank control configuration using the function FMC_NAND_Init()
    (+) FMC NAND bank common space timing configuration using the function
        FMC_NAND_CommonSpace_Timing_Init()
    (+) FMC NAND bank attribute space timing configuration using the function
        FMC_NAND_AttributeSpace_Timing_Init()
    (+) FMC NAND bank enable/disable ECC correction feature using the functions
        FMC_NAND_ECC_Enable()/FMC_NAND_ECC_Disable()
    (+) FMC NAND bank get ECC correction code using the function FMC_NAND_GetECC()

@endverbatim
  * @{
  */

/** @defgroup FMC_NAND_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the FMC NAND interface
    (+) De-initialize the FMC NAND interface
    (+) Configure the FMC clock and associated GPIOs

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the FMC_NAND device according to the specified
  *         control parameters in the FMC_NAND_HandleTypeDef
  * @param  Device Pointer to NAND device instance
  *          This paramater can be FMC_NAND_DEVICE
  * @param  Init Pointer to NAND Initialization structure
  * @retval None
  */
void FMC_NAND_Init(FMC_NAND_TypeDef *Device, FMC_NAND_InitTypeDef *Init)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_FMC_NAND_DEVICE(Device));
    assert_param(IS_FMC_NAND_BANK(Init->NandBank));
    assert_param(IS_FMC_WAIT_FEATURE(Init->Waitfeature));
    assert_param(IS_FMC_NAND_MEMORY_WIDTH(Init->MemoryDataWidth));
    assert_param(IS_FMC_ECC_STATE(Init->EccComputation));
    assert_param(IS_FMC_ECCPAGE_SIZE(Init->ECCPageSize));
    assert_param(IS_FMC_TCLR_TIME(Init->TCLRSetupTime));
    assert_param(IS_FMC_TAR_TIME(Init->TARSetupTime));

    /* Set NAND device control parameters */
    if (Init->NandBank == FMC_NAND_BANK2)
    {
        /* NAND bank 2 registers configuration */
        tmpreg = Device->PCR2;
        tmpreg &= (uint32_t)~((uint32_t)PCR_CLEAR_MASK);
        tmpreg |= (Init->Waitfeature                                      |
                   FMC_PCR_MEMORY_TYPE_NAND                               |
                   Init->MemoryDataWidth                                  |
                   Init->EccComputation                                   |
                   Init->ECCPageSize                                      |
                   (((Init->TCLRSetupTime) - 0x1U) << FMC_PCR2_TCLR_Pos)  |
                   (((Init->TARSetupTime) - 0x1U)  << FMC_PCR2_TAR_Pos));

        Device->PCR2 = tmpreg;
    }
    else
    {
        /* NAND bank 3 registers configuration */
        tmpreg = Device->PCR3;
        tmpreg &= (uint32_t)~((uint32_t)PCR_CLEAR_MASK);
        tmpreg |= (Init->Waitfeature                                      |
                   FMC_PCR_MEMORY_TYPE_NAND                               |
                   Init->MemoryDataWidth                                  |
                   Init->EccComputation                                   |
                   Init->ECCPageSize                                      |
                   (((Init->TCLRSetupTime) - 0x1U) << FMC_PCR3_TCLR_Pos)  |
                   (((Init->TARSetupTime) - 0x1U) << FMC_PCR3_TAR_Pos));

        Device->PCR3 = tmpreg;
    }
}

/**
  * @brief  Initializes the FMC_NAND Common space Timing according to the specified
  *         parameters in the FMC_NAND_TimingTypeDef
  * @param  Device Pointer to NAND device instance
  *          This paramater can be FMC_NAND_DEVICE
  * @param  Timing Pointer to NAND timing structure
  * @param  Bank NAND bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NAND_BANK2
  *            @arg FMC_NAND_BANK3
  * @retval None
  */
void FMC_NAND_CommonSpace_Timing_Init(FMC_NAND_TypeDef *Device,
                                      FMC_NAND_TimingTypeDef *Timing, uint32_t Bank)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_FMC_NAND_DEVICE(Device));
    assert_param(IS_FMC_SETUP_TIME(Timing->SetupTime));
    assert_param(IS_FMC_WAIT_TIME(Timing->WaitSetupTime));
    assert_param(IS_FMC_HOLD_TIME(Timing->HoldSetupTime));
    assert_param(IS_FMC_HIZ_TIME(Timing->HiZSetupTime));
    assert_param(IS_FMC_NAND_BANK(Bank));

    /* Set FMC_NAND device timing parameters */
    if (Bank == FMC_NAND_BANK2)
    {
        /* NAND bank 2 registers configuration */
        tmpreg = Device->PMEM2;
        tmpreg &= (uint32_t)~((uint32_t)PMEM_CLEAR_MASK);
        tmpreg |= (Timing->SetupTime                                             |
                   ((Timing->WaitSetupTime) << FMC_PMEM2_MEMWAIT2_Pos)           |
                   ((Timing->HoldSetupTime) << FMC_PMEM2_MEMHOLD2_Pos)           |
                   ((Timing->HiZSetupTime)  << FMC_PMEM2_MEMHIZ2_Pos));

        Device->PMEM2 = tmpreg;
    }
    else
    {
        /* NAND bank 3 registers configuration */
        tmpreg = Device->PMEM3;
        tmpreg &= (uint32_t)~((uint32_t)PMEM_CLEAR_MASK);
        tmpreg |= (Timing->SetupTime                                             |
                   ((Timing->WaitSetupTime) << FMC_PMEM3_MEMWAIT3_Pos)           |
                   ((Timing->HoldSetupTime) << FMC_PMEM3_MEMHOLD3_Pos)           |
                   ((Timing->HiZSetupTime)  << FMC_PMEM3_MEMHIZ3_Pos));

        Device->PMEM3 = tmpreg;
    }
}

/**
  * @brief  Initializes the FMC_NAND Attribute space Timing according to the specified
  *         parameters in the FMC_NAND_TimingTypeDef
  * @param  Device Pointer to NAND device instance
  *          This paramater can be FMC_NAND_DEVICE
  * @param  Timing Pointer to NAND timing structure
  * @param  Bank NAND bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NAND_BANK2
  *            @arg FMC_NAND_BANK3
  * @retval None
  */
void FMC_NAND_AttributeSpace_Timing_Init(FMC_NAND_TypeDef *Device,
        FMC_NAND_TimingTypeDef *Timing, uint32_t Bank)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_FMC_NAND_DEVICE(Device));
    assert_param(IS_FMC_SETUP_TIME(Timing->SetupTime));
    assert_param(IS_FMC_WAIT_TIME(Timing->WaitSetupTime));
    assert_param(IS_FMC_HOLD_TIME(Timing->HoldSetupTime));
    assert_param(IS_FMC_HIZ_TIME(Timing->HiZSetupTime));
    assert_param(IS_FMC_NAND_BANK(Bank));

    /* Set FMC_NAND device timing parameters */
    if (Bank == FMC_NAND_BANK2)
    {
        /* NAND bank 2 registers configuration */
        tmpreg = Device->PATT2;
        tmpreg &= (uint32_t)((uint32_t)PATT_CLEAR_MASK);
        tmpreg |= (Timing->SetupTime                                             |
                   ((Timing->WaitSetupTime) << FMC_PATT2_ATTWAIT2_Pos)           |
                   ((Timing->HoldSetupTime) << FMC_PATT2_ATTHOLD2_Pos)           |
                   ((Timing->HiZSetupTime)  << FMC_PATT2_ATTHIZ2_Pos));

        Device->PATT2 = tmpreg;
    }
    else
    {
        /* NAND bank 3 registers configuration */
        tmpreg = Device->PATT3;
        tmpreg &= (uint32_t)((uint32_t)PATT_CLEAR_MASK);
        tmpreg |= (Timing->SetupTime                                             |
                   ((Timing->WaitSetupTime) << FMC_PATT3_ATTWAIT3_Pos)           |
                   ((Timing->HoldSetupTime) << FMC_PATT3_ATTHOLD3_Pos)           |
                   ((Timing->HiZSetupTime)  << FMC_PATT3_ATTHIZ3_Pos));

        Device->PATT3 = tmpreg;
    }
}

/**
  * @brief  DeInitializes the FMC_NAND device
  * @param  Device Pointer to NAND device instance
  *          This paramater can be FMC_NAND_DEVICE
  * @param  Bank NAND bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NAND_BANK2
  *            @arg FMC_NAND_BANK3
  * @retval None
  */
void FMC_NAND_DeInit(FMC_NAND_TypeDef *Device, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_NAND_DEVICE(Device));
    assert_param(IS_FMC_NAND_BANK(Bank));

    /* Disable the NAND Bank */
    __FMC_NAND_DISABLE(Device, Bank);

    /* De-initialize the NAND Bank */
    if (Bank == FMC_NAND_BANK2)
    {
        /* Set the FMC_NAND_BANK2 registers to their reset values */
        Device->PCR2  = 0x00000018U;
        Device->SR2   = 0x00000040U;
        Device->PMEM2 = 0xFCFCFCFCU;
        Device->PATT2 = 0xFCFCFCFCU;
    }
    /* FMC_Bank3_NAND */
    else
    {
        /* Set the FMC_NAND_BANK3 registers to their reset values */
        Device->PCR3  = 0x00000018U;
        Device->SR3   = 0x00000040U;
        Device->PMEM3 = 0xFCFCFCFCU;
        Device->PATT3 = 0xFCFCFCFCU;
    }
}

/**
  * @}
  */

/** @defgroup FMC_NAND_Group2 Peripheral Control functions
  *  @brief   management functions
  *
@verbatim
  ==============================================================================
                       ##### FMC_NAND Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control dynamically
    the FMC NAND interface.

@endverbatim
  * @{
  */


/**
  * @brief  Enables dynamically FMC_NAND ECC feature.
  * @param  Device Pointer to NAND device instance
  *          This paramater can be FMC_NAND_DEVICE
  * @param  Bank NAND bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NAND_BANK2
  *            @arg FMC_NAND_BANK3
  * @retval None
  */
void FMC_NAND_ECC_Enable(FMC_NAND_TypeDef *Device, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_NAND_DEVICE(Device));
    assert_param(IS_FMC_NAND_BANK(Bank));

    /* Enable ECC feature */
    if (Bank == FMC_NAND_BANK2)
    {
        Device->PCR2 |= FMC_PCR2_ECCEN;
    }
    else
    {
        Device->PCR3 |= FMC_PCR3_ECCEN;
    }
}


/**
  * @brief  Disables dynamically FMC_NAND ECC feature.
  * @param  Device Pointer to NAND device instance
  *          This paramater can be FMC_NAND_DEVICE
  * @param  Bank NAND bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NAND_BANK2
  *            @arg FMC_NAND_BANK3
  * @retval None
  */
void FMC_NAND_ECC_Disable(FMC_NAND_TypeDef *Device, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_NAND_DEVICE(Device));
    assert_param(IS_FMC_NAND_BANK(Bank));

    /* Disable ECC feature */
    if (Bank == FMC_NAND_BANK2)
    {
        Device->PCR2 &= (uint32_t)~((uint32_t)FMC_PCR2_ECCEN);
    }
    else
    {
        Device->PCR3 &= (uint32_t)~((uint32_t)FMC_PCR3_ECCEN);
    }
}

/**
  * @brief  Disables dynamically FMC_NAND ECC feature.
  * @param  Device Pointer to NAND device instance
  *          This paramater can be FMC_NAND_DEVICE
  * @param  ECCval Pointer to ECC value
  * @param  Bank NAND bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_NAND_BANK2
  *            @arg FMC_NAND_BANK3
  * @param  Timeout Timeout wait value
  * @retval None
  */
void FMC_NAND_GetECC(FMC_NAND_TypeDef *Device, uint32_t *ECCval, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_NAND_DEVICE(Device));
    assert_param(IS_FMC_NAND_BANK(Bank));

    /* Wait until FIFO is empty */
    while (__FMC_NAND_GET_FLAG(Device, Bank, FMC_FLAG_FEMPT) == RESET)
    {
    }

    if (Bank == FMC_NAND_BANK2)
    {
        /* Get the ECCR2 register value */
        *ECCval = (uint32_t)Device->ECCR2;
    }
    else
    {
        /* Get the ECCR3 register value */
        *ECCval = (uint32_t)Device->ECCR3;
    }
}

/**
  * @}
  */
#endif /* FMC_Bank2_3 */

#if defined(FMC_Bank5_6)

/** @defgroup FMC_SDRAM
  * @brief    SDRAM Controller functions
  *
  @verbatim
  ==============================================================================
                     ##### How to use SDRAM device driver #####
  ==============================================================================
  [..]
    This driver contains a set of APIs to interface with the FMC SDRAM banks in order
    to run the SDRAM external devices.

    (+) FMC SDRAM bank reset using the function FMC_SDRAM_DeInit()
    (+) FMC SDRAM bank control configuration using the function FMC_SDRAM_Init()
    (+) FMC SDRAM bank timing configuration using the function FMC_SDRAM_Timing_Init()
    (+) FMC SDRAM bank enable/disable write operation using the functions
        FMC_SDRAM_WriteOperation_Enable()/FMC_SDRAM_WriteOperation_Disable()
    (+) FMC SDRAM bank send command using the function FMC_SDRAM_SendCommand()

@endverbatim
  * @{
  */

/** @addtogroup FMC_SDRAM_Private_Functions_Group1
  *  @brief    Initialization and Configuration functions
  *
@verbatim
  ==============================================================================
              ##### Initialization and de_initialization functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
    (+) Initialize and configure the FMC SDRAM interface
    (+) De-initialize the FMC SDRAM interface
    (+) Configure the FMC clock and associated GPIOs

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the FMC_SDRAM device according to the specified
  *         control parameters in the FMC_SDRAM_InitTypeDef
  * @param  Device Pointer to SDRAM device instance
  *          This paramater can be FMC_SDRAM_DEVICE
  * @param  Init Pointer to SDRAM Initialization structure
  * @retval None
  */
void FMC_SDRAM_Init(FMC_SDRAM_TypeDef *Device, FMC_SDRAM_InitTypeDef *Init)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_DEVICE(Device));
    assert_param(IS_FMC_SDRAM_BANK(Init->SDBank));
    assert_param(IS_FMC_COLUMNBITS_NUMBER(Init->ColumnBitsNumber));
    assert_param(IS_FMC_ROWBITS_NUMBER(Init->RowBitsNumber));
    assert_param(IS_FMC_SDMEMORY_WIDTH(Init->MemoryDataWidth));
    assert_param(IS_FMC_INTERNALBANK_NUMBER(Init->InternalBankNumber));
    assert_param(IS_FMC_CAS_LATENCY(Init->CASLatency));
    assert_param(IS_FMC_WRITE_PROTECTION(Init->WriteProtection));
    assert_param(IS_FMC_SDCLOCK_PERIOD(Init->SDClockPeriod));
    assert_param(IS_FMC_READ_BURST(Init->ReadBurst));
    assert_param(IS_FMC_READPIPE_DELAY(Init->ReadPipeDelay));

    /* Set SDRAM bank configuration parameters */
    if (Init->SDBank == FMC_SDRAM_BANK1)
    {
        tmpreg = Device->SDCR[FMC_SDRAM_BANK1];
        tmpreg &= (uint32_t)~((uint32_t)SDCR_CLEAR_MASK);
        tmpreg |= (Init->ColumnBitsNumber   |
                   Init->RowBitsNumber      |
                   Init->MemoryDataWidth    |
                   Init->InternalBankNumber |
                   Init->CASLatency         |
                   Init->WriteProtection    |
                   Init->SDClockPeriod      |
                   Init->ReadBurst          |
                   Init->ReadPipeDelay);

        Device->SDCR[FMC_SDRAM_BANK1] = tmpreg;
    }
    else /* FMC_Bank2_SDRAM */
    {
        tmpreg = Device->SDCR[FMC_SDRAM_BANK1];
        tmpreg &= (uint32_t)~((uint32_t)(FMC_SDCR1_SDCLK  |
                                         FMC_SDCR1_RBURST |
                                         FMC_SDCR1_RPIPE));
        tmpreg |= (Init->SDClockPeriod      |
                   Init->ReadBurst          |
                   Init->ReadPipeDelay);

        Device->SDCR[FMC_SDRAM_BANK1] = tmpreg;

        tmpreg = Device->SDCR[FMC_SDRAM_BANK2];
        tmpreg &= (uint32_t)~((uint32_t)SDCR_CLEAR_MASK);
        tmpreg |= (Init->ColumnBitsNumber   |
                   Init->RowBitsNumber      |
                   Init->MemoryDataWidth    |
                   Init->InternalBankNumber |
                   Init->CASLatency         |
                   Init->WriteProtection);

        Device->SDCR[FMC_SDRAM_BANK2] = tmpreg;
    }
}


/**
  * @brief  Initializes the FMC_SDRAM device timing according to the specified
  *         parameters in the FMC_SDRAM_TimingTypeDef
  * @param  Device Pointer to SDRAM device instance
  *          This paramater can be FMC_SDRAM_DEVICE
  * @param  Timing Pointer to SDRAM Timing structure
  * @param  Bank SDRAM bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_SDRAM_BANK1
  *            @arg FMC_SDRAM_BANK2
  * @retval None
  */
void FMC_SDRAM_Timing_Init(FMC_SDRAM_TypeDef *Device,
                           FMC_SDRAM_TimingTypeDef *Timing, uint32_t Bank)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_DEVICE(Device));
    assert_param(IS_FMC_LOADTOACTIVE_DELAY(Timing->LoadToActiveDelay));
    assert_param(IS_FMC_EXITSELFREFRESH_DELAY(Timing->ExitSelfRefreshDelay));
    assert_param(IS_FMC_SELFREFRESH_TIME(Timing->SelfRefreshTime));
    assert_param(IS_FMC_ROWCYCLE_DELAY(Timing->RowCycleDelay));
    assert_param(IS_FMC_WRITE_RECOVERY_TIME(Timing->WriteRecoveryTime));
    assert_param(IS_FMC_RP_DELAY(Timing->RPDelay));
    assert_param(IS_FMC_RCD_DELAY(Timing->RCDDelay));
    assert_param(IS_FMC_SDRAM_BANK(Bank));

    /* Set SDRAM device timing parameters */
    if (Bank == FMC_SDRAM_BANK1)
    {
        tmpreg = Device->SDTR[FMC_SDRAM_BANK1];
        tmpreg &= (uint32_t)~((uint32_t)SDTR_CLEAR_MASK);
        tmpreg |= (((Timing->LoadToActiveDelay) - 1U)                             |
                   (((Timing->ExitSelfRefreshDelay) - 1U) << FMC_SDTR1_TXSR_Pos)  |
                   (((Timing->SelfRefreshTime) - 1U)      << FMC_SDTR1_TRAS_Pos)  |
                   (((Timing->RowCycleDelay) - 1U)        << FMC_SDTR1_TRC_Pos)   |
                   (((Timing->WriteRecoveryTime) - 1U)    << FMC_SDTR1_TWR_Pos)   |
                   (((Timing->RPDelay) - 1U)              << FMC_SDTR1_TRP_Pos)   |
                   (((Timing->RCDDelay) - 1U)             << FMC_SDTR1_TRCD_Pos));

        Device->SDTR[FMC_SDRAM_BANK1] = tmpreg;
    }
    else /* FMC_Bank2_SDRAM */
    {
        tmpreg = Device->SDTR[FMC_SDRAM_BANK1];
        tmpreg &= (uint32_t)~((uint32_t)(FMC_SDTR1_TRC |
                                         FMC_SDTR1_TRP));
        tmpreg |= ((((Timing->RowCycleDelay) - 1U)         << FMC_SDTR1_TRC_Pos)  |
                   (((Timing->RPDelay) - 1U)               << FMC_SDTR1_TRP_Pos));

        Device->SDTR[FMC_SDRAM_BANK1] = tmpreg;

        tmpreg = Device->SDTR[FMC_SDRAM_BANK2];
        tmpreg &= (uint32_t)~((uint32_t)SDTR_CLEAR_MASK);
        tmpreg |= (((Timing->LoadToActiveDelay) - 1U)                             |
                   (((Timing->ExitSelfRefreshDelay) - 1U) << FMC_SDTR1_TXSR_Pos)  |
                   (((Timing->SelfRefreshTime) - 1U)      << FMC_SDTR1_TRAS_Pos)  |
                   (((Timing->WriteRecoveryTime) - 1U)    << FMC_SDTR1_TWR_Pos)   |
                   (((Timing->RCDDelay) - 1U)             << FMC_SDTR1_TRCD_Pos));

        Device->SDTR[FMC_SDRAM_BANK2] = tmpreg;
    }
}

/**
  * @brief  DeInitializes the FMC_SDRAM peripheral
  * @param  Device Pointer to SDRAM device instance
  *          This paramater can be FMC_SDRAM_DEVICE
  * @param  Bank SDRAM bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_SDRAM_BANK1
  *            @arg FMC_SDRAM_BANK2
  * @retval None
  */
void FMC_SDRAM_DeInit(FMC_SDRAM_TypeDef *Device, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_DEVICE(Device));
    assert_param(IS_FMC_SDRAM_BANK(Bank));

    /* De-initialize the SDRAM device */
    Device->SDCR[Bank] = 0x000002D0U;
    Device->SDTR[Bank] = 0x0FFFFFFFU;
    Device->SDCMR      = 0x00000000U;
    Device->SDRTR      = 0x00000000U;
    Device->SDSR       = 0x00000000U;
}

/**
  * @}
  */

/** @addtogroup FMC_SDRAMPrivate_Functions_Group2
  *  @brief   management functions
  *
@verbatim
  ==============================================================================
                      ##### FMC_SDRAM Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control dynamically
    the FMC SDRAM interface.

@endverbatim
  * @{
  */

/**
  * @brief  Enables dynamically FMC_SDRAM write protection.
  * @param  Device Pointer to SDRAM device instance
  *          This paramater can be FMC_SDRAM_DEVICE
  * @param  Bank SDRAM bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_SDRAM_BANK1
  *            @arg FMC_SDRAM_BANK2
  * @retval None
  */
void FMC_SDRAM_WriteProtection_Enable(FMC_SDRAM_TypeDef *Device, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_DEVICE(Device));
    assert_param(IS_FMC_SDRAM_BANK(Bank));

    /* Enable write protection */
    Device->SDCR[Bank] |= FMC_SDRAM_WRITE_PROTECTION_ENABLE;
}

/**
  * @brief  Disables dynamically FMC_SDRAM write protection.
  * @param  Device Pointer to SDRAM device instance
  *          This paramater can be FMC_SDRAM_DEVICE
  * @param  Bank SDRAM bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_SDRAM_BANK1
  *            @arg FMC_SDRAM_BANK2
  * @retval None
  */
void FMC_SDRAM_WriteProtection_Disable(FMC_SDRAM_TypeDef *Device, uint32_t Bank)
{
    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_DEVICE(Device));
    assert_param(IS_FMC_SDRAM_BANK(Bank));

    /* Disable write protection */
    Device->SDCR[Bank] &= (uint32_t)~((uint32_t)FMC_SDRAM_WRITE_PROTECTION_ENABLE);
}

/**
  * @brief  Send Command to the FMC SDRAM bank
  * @param  Device Pointer to SDRAM device instance
  *          This paramater can be FMC_SDRAM_DEVICE
  * @param  Command Pointer to SDRAM command structure
  * @param  Timing Pointer to SDRAM Timing structure
  * @param  Timeout Timeout wait value
  * @retval None
  */
void FMC_SDRAM_SendCommand(FMC_SDRAM_TypeDef *Device,
                           FMC_SDRAM_CommandTypeDef *Command)
{
    uint32_t tmpreg;
    uint32_t tickstart = 0U;

    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_DEVICE(Device));
    assert_param(IS_FMC_COMMAND_MODE(Command->CommandMode));
    assert_param(IS_FMC_COMMAND_TARGET(Command->CommandTarget));
    assert_param(IS_FMC_AUTOREFRESH_NUMBER(Command->AutoRefreshNumber));
    assert_param(IS_FMC_MODE_REGISTER(Command->ModeRegisterDefinition));

    /* Set command register */
    tmpreg = Device->SDCMR;
    tmpreg &= (uint32_t)~((uint32_t)(FMC_SDCMR_MODE |
                                     FMC_SDCMR_CTB2 |
                                     FMC_SDCMR_CTB1 |
                                     FMC_SDCMR_NRFS |
                                     FMC_SDCMR_MRD));
    tmpreg |= ((Command->CommandMode)                                      |
               (Command->CommandTarget)                                    |
               (((Command->AutoRefreshNumber) - 1U) << FMC_SDCMR_NRFS_Pos) |
               ((Command->ModeRegisterDefinition) << FMC_SDCMR_MRD_Pos));

    Device->SDCMR = tmpreg;

    /* wait until command is send */
    while ((Device->SDSR & FMC_SDSR_BUSY) != 0U)
    {
    }
}

/**
  * @brief  Program the SDRAM Memory Refresh rate.
  * @param  Device Pointer to SDRAM device instance
  *          This paramater can be FMC_SDRAM_DEVICE
  * @param  RefreshRate The SDRAM refresh rate value.
  * @retval None
  */
void FMC_SDRAM_ProgramRefreshRate(FMC_SDRAM_TypeDef *Device, uint32_t RefreshRate)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_DEVICE(Device));
    assert_param(IS_FMC_REFRESH_RATE(RefreshRate));

    /* Set the refresh rate in command register */
    tmpreg = Device->SDRTR;
    tmpreg &= (uint32_t)~((uint32_t)FMC_SDRTR_COUNT);
    tmpreg |= (RefreshRate << FMC_SDRTR_COUNT_Pos);

    Device->SDRTR = tmpreg;
}

/**
  * @brief  Set the Number of consecutive SDRAM Memory auto Refresh commands.
  * @param  Device Pointer to SDRAM device instance
  *          This paramater can be FMC_SDRAM_DEVICE
  * @param  AutoRefreshNumber Specifies the auto Refresh number.
  * @retval None
  */
void FMC_SDRAM_SetAutoRefreshNumber(FMC_SDRAM_TypeDef *Device,
                                    uint32_t AutoRefreshNumber)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_DEVICE(Device));
    assert_param(IS_FMC_AUTOREFRESH_NUMBER(AutoRefreshNumber));

    /* Set the Auto-refresh number in command register */
    tmpreg = Device->SDCMR;
    tmpreg &= (uint32_t)~((uint32_t)FMC_SDCMR_NRFS);
    tmpreg |= ((AutoRefreshNumber - 1U) << FMC_SDCMR_NRFS_Pos);

    Device->SDCMR = tmpreg;
}

/**
  * @brief  Returns the indicated FMC SDRAM bank mode status.
  * @param  Device Pointer to SDRAM device instance
  *          This paramater can be FMC_SDRAM_DEVICE
  * @param  Bank SDRAM bank number
  *          This paramater can be one of the following values:
  *            @arg FMC_SDRAM_BANK1
  *            @arg FMC_SDRAM_BANK2
  * @retval The FMC SDRAM bank mode status, could be on of the following values:
  *         FMC_SDRAM_NORMAL_MODE, FMC_SDRAM_SELF_REFRESH_MODE or
  *         FMC_SDRAM_POWER_DOWN_MODE.
  */
uint32_t FMC_SDRAM_GetModeStatus(const FMC_SDRAM_TypeDef *Device, uint32_t Bank)
{
    uint32_t tmpreg;

    /* Check the parameters */
    assert_param(IS_FMC_SDRAM_DEVICE(Device));
    assert_param(IS_FMC_SDRAM_BANK(Bank));

    /* Get the corresponding bank mode */
    if (Bank == FMC_SDRAM_BANK1)
    {
        tmpreg = (uint32_t)(Device->SDSR & FMC_SDSR_MODES1);
    }
    else
    {
        tmpreg = ((uint32_t)(Device->SDSR & FMC_SDSR_MODES2) >> 2U);
    }

    /* Return the mode status */
    return tmpreg;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* FMC_Bank5_6 */

/**
  * @}
  */

/**
  * @}
  */
/**
  * @}
  */
