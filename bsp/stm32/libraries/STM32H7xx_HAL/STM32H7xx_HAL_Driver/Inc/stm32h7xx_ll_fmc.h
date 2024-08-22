/**
  ******************************************************************************
  * @file    stm32h7xx_ll_fmc.h
  * @author  MCD Application Team
  * @brief   Header file of FMC HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_LL_FMC_H
#define STM32H7xx_LL_FMC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup FMC_LL
  * @{
  */

/** @addtogroup FMC_LL_Private_Macros
  * @{
  */

#define IS_FMC_NORSRAM_BANK(__BANK__) (((__BANK__) == FMC_NORSRAM_BANK1) || \
                                       ((__BANK__) == FMC_NORSRAM_BANK2) || \
                                       ((__BANK__) == FMC_NORSRAM_BANK3) || \
                                       ((__BANK__) == FMC_NORSRAM_BANK4))
#define IS_FMC_MUX(__MUX__) (((__MUX__) == FMC_DATA_ADDRESS_MUX_DISABLE) || \
                             ((__MUX__) == FMC_DATA_ADDRESS_MUX_ENABLE))
#define IS_FMC_MEMORY(__MEMORY__) (((__MEMORY__) == FMC_MEMORY_TYPE_SRAM) || \
                                   ((__MEMORY__) == FMC_MEMORY_TYPE_PSRAM)|| \
                                   ((__MEMORY__) == FMC_MEMORY_TYPE_NOR))
#define IS_FMC_NORSRAM_MEMORY_WIDTH(__WIDTH__) (((__WIDTH__) == FMC_NORSRAM_MEM_BUS_WIDTH_8)  || \
                                                ((__WIDTH__) == FMC_NORSRAM_MEM_BUS_WIDTH_16) || \
                                                ((__WIDTH__) == FMC_NORSRAM_MEM_BUS_WIDTH_32))
#define IS_FMC_PAGESIZE(__SIZE__) (((__SIZE__) == FMC_PAGE_SIZE_NONE) || \
                                   ((__SIZE__) == FMC_PAGE_SIZE_128) || \
                                   ((__SIZE__) == FMC_PAGE_SIZE_256) || \
                                   ((__SIZE__) == FMC_PAGE_SIZE_512) || \
                                   ((__SIZE__) == FMC_PAGE_SIZE_1024))
#define IS_FMC_WRITE_FIFO(__FIFO__) (((__FIFO__) == FMC_WRITE_FIFO_DISABLE) || \
                                     ((__FIFO__) == FMC_WRITE_FIFO_ENABLE))
#define IS_FMC_ACCESS_MODE(__MODE__) (((__MODE__) == FMC_ACCESS_MODE_A) || \
                                      ((__MODE__) == FMC_ACCESS_MODE_B) || \
                                      ((__MODE__) == FMC_ACCESS_MODE_C) || \
                                      ((__MODE__) == FMC_ACCESS_MODE_D))
#define IS_FMC_BURSTMODE(__STATE__) (((__STATE__) == FMC_BURST_ACCESS_MODE_DISABLE) || \
                                     ((__STATE__) == FMC_BURST_ACCESS_MODE_ENABLE))
#define IS_FMC_WAIT_POLARITY(__POLARITY__) (((__POLARITY__) == FMC_WAIT_SIGNAL_POLARITY_LOW) || \
                                            ((__POLARITY__) == FMC_WAIT_SIGNAL_POLARITY_HIGH))
#define IS_FMC_WAIT_SIGNAL_ACTIVE(__ACTIVE__) (((__ACTIVE__) == FMC_WAIT_TIMING_BEFORE_WS) || \
                                               ((__ACTIVE__) == FMC_WAIT_TIMING_DURING_WS))
#define IS_FMC_WRITE_OPERATION(__OPERATION__) (((__OPERATION__) == FMC_WRITE_OPERATION_DISABLE) || \
                                               ((__OPERATION__) == FMC_WRITE_OPERATION_ENABLE))
#define IS_FMC_WAITE_SIGNAL(__SIGNAL__) (((__SIGNAL__) == FMC_WAIT_SIGNAL_DISABLE) || \
                                         ((__SIGNAL__) == FMC_WAIT_SIGNAL_ENABLE))
#define IS_FMC_EXTENDED_MODE(__MODE__) (((__MODE__) == FMC_EXTENDED_MODE_DISABLE) || \
                                        ((__MODE__) == FMC_EXTENDED_MODE_ENABLE))
#define IS_FMC_ASYNWAIT(__STATE__) (((__STATE__) == FMC_ASYNCHRONOUS_WAIT_DISABLE) || \
                                    ((__STATE__) == FMC_ASYNCHRONOUS_WAIT_ENABLE))
#define IS_FMC_DATA_LATENCY(__LATENCY__) (((__LATENCY__) > 1U) && ((__LATENCY__) <= 17U))
#define IS_FMC_WRITE_BURST(__BURST__) (((__BURST__) == FMC_WRITE_BURST_DISABLE) || \
                                       ((__BURST__) == FMC_WRITE_BURST_ENABLE))
#define IS_FMC_CONTINOUS_CLOCK(__CCLOCK__) (((__CCLOCK__) == FMC_CONTINUOUS_CLOCK_SYNC_ONLY) || \
                                            ((__CCLOCK__) == FMC_CONTINUOUS_CLOCK_SYNC_ASYNC))
#define IS_FMC_ADDRESS_SETUP_TIME(__TIME__) ((__TIME__) <= 15U)
#define IS_FMC_ADDRESS_HOLD_TIME(__TIME__) (((__TIME__) > 0U) && ((__TIME__) <= 15U))
#define IS_FMC_DATASETUP_TIME(__TIME__) (((__TIME__) > 0U) && ((__TIME__) <= 255U))
#define IS_FMC_DATAHOLD_DURATION(__DATAHOLD__) ((__DATAHOLD__) <= 3U)
#define IS_FMC_TURNAROUND_TIME(__TIME__) ((__TIME__) <= 15U)
#define IS_FMC_CLK_DIV(__DIV__) (((__DIV__) > 1U) && ((__DIV__) <= 16U))
#define IS_FMC_NORSRAM_DEVICE(__INSTANCE__) ((__INSTANCE__) == FMC_NORSRAM_DEVICE)
#define IS_FMC_NORSRAM_EXTENDED_DEVICE(__INSTANCE__) ((__INSTANCE__) == FMC_NORSRAM_EXTENDED_DEVICE)


#define IS_FMC_NAND_BANK(__BANK__) ((__BANK__) == FMC_NAND_BANK3)
#define IS_FMC_WAIT_FEATURE(__FEATURE__) (((__FEATURE__) == FMC_NAND_WAIT_FEATURE_DISABLE) || \
                                          ((__FEATURE__) == FMC_NAND_WAIT_FEATURE_ENABLE))
#define IS_FMC_NAND_MEMORY_WIDTH(__WIDTH__) (((__WIDTH__) == FMC_NAND_MEM_BUS_WIDTH_8) || \
                                             ((__WIDTH__) == FMC_NAND_MEM_BUS_WIDTH_16))
#define IS_FMC_ECC_STATE(__STATE__) (((__STATE__) == FMC_NAND_ECC_DISABLE) || \
                                     ((__STATE__) == FMC_NAND_ECC_ENABLE))

#define IS_FMC_ECCPAGE_SIZE(__SIZE__) (((__SIZE__) == FMC_NAND_ECC_PAGE_SIZE_256BYTE)  || \
                                       ((__SIZE__) == FMC_NAND_ECC_PAGE_SIZE_512BYTE)  || \
                                       ((__SIZE__) == FMC_NAND_ECC_PAGE_SIZE_1024BYTE) || \
                                       ((__SIZE__) == FMC_NAND_ECC_PAGE_SIZE_2048BYTE) || \
                                       ((__SIZE__) == FMC_NAND_ECC_PAGE_SIZE_4096BYTE) || \
                                       ((__SIZE__) == FMC_NAND_ECC_PAGE_SIZE_8192BYTE))
#define IS_FMC_TCLR_TIME(__TIME__) ((__TIME__) <= 255U)
#define IS_FMC_TAR_TIME(__TIME__) ((__TIME__) <= 255U)
#define IS_FMC_SETUP_TIME(__TIME__) ((__TIME__) <= 254U)
#define IS_FMC_WAIT_TIME(__TIME__) ((__TIME__) <= 254U)
#define IS_FMC_HOLD_TIME(__TIME__) ((__TIME__) <= 254U)
#define IS_FMC_HIZ_TIME(__TIME__) ((__TIME__) <= 254U)
#define IS_FMC_NAND_DEVICE(__INSTANCE__) ((__INSTANCE__) == FMC_NAND_DEVICE)


#define IS_FMC_SDMEMORY_WIDTH(__WIDTH__) (((__WIDTH__) == FMC_SDRAM_MEM_BUS_WIDTH_8)  || \
                                          ((__WIDTH__) == FMC_SDRAM_MEM_BUS_WIDTH_16) || \
                                          ((__WIDTH__) == FMC_SDRAM_MEM_BUS_WIDTH_32))
#define IS_FMC_WRITE_PROTECTION(__WRITE__) (((__WRITE__) == FMC_SDRAM_WRITE_PROTECTION_DISABLE) || \
                                            ((__WRITE__) == FMC_SDRAM_WRITE_PROTECTION_ENABLE))
#define IS_FMC_SDCLOCK_PERIOD(__PERIOD__) (((__PERIOD__) == FMC_SDRAM_CLOCK_DISABLE)  || \
                                           ((__PERIOD__) == FMC_SDRAM_CLOCK_PERIOD_2) || \
                                           ((__PERIOD__) == FMC_SDRAM_CLOCK_PERIOD_3))
#define IS_FMC_READ_BURST(__RBURST__) (((__RBURST__) == FMC_SDRAM_RBURST_DISABLE) || \
                                       ((__RBURST__) == FMC_SDRAM_RBURST_ENABLE))
#define IS_FMC_READPIPE_DELAY(__DELAY__) (((__DELAY__) == FMC_SDRAM_RPIPE_DELAY_0) || \
                                          ((__DELAY__) == FMC_SDRAM_RPIPE_DELAY_1) || \
                                          ((__DELAY__) == FMC_SDRAM_RPIPE_DELAY_2))
#define IS_FMC_COMMAND_MODE(__COMMAND__) (((__COMMAND__) == FMC_SDRAM_CMD_NORMAL_MODE)      || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_CLK_ENABLE)       || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_PALL)             || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_AUTOREFRESH_MODE) || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_LOAD_MODE)        || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_SELFREFRESH_MODE) || \
                                          ((__COMMAND__) == FMC_SDRAM_CMD_POWERDOWN_MODE))
#define IS_FMC_COMMAND_TARGET(__TARGET__) (((__TARGET__) == FMC_SDRAM_CMD_TARGET_BANK1) || \
                                           ((__TARGET__) == FMC_SDRAM_CMD_TARGET_BANK2) || \
                                           ((__TARGET__) == FMC_SDRAM_CMD_TARGET_BANK1_2))
#define IS_FMC_LOADTOACTIVE_DELAY(__DELAY__) (((__DELAY__) > 0U) && ((__DELAY__) <= 16U))
#define IS_FMC_EXITSELFREFRESH_DELAY(__DELAY__) (((__DELAY__) > 0U) && ((__DELAY__) <= 16U))
#define IS_FMC_SELFREFRESH_TIME(__TIME__) (((__TIME__) > 0U) && ((__TIME__) <= 16U))
#define IS_FMC_ROWCYCLE_DELAY(__DELAY__) (((__DELAY__) > 0U) && ((__DELAY__) <= 16U))
#define IS_FMC_WRITE_RECOVERY_TIME(__TIME__) (((__TIME__) > 0U) && ((__TIME__) <= 16U))
#define IS_FMC_RP_DELAY(__DELAY__) (((__DELAY__) > 0U) && ((__DELAY__) <= 16U))
#define IS_FMC_RCD_DELAY(__DELAY__) (((__DELAY__) > 0U) && ((__DELAY__) <= 16U))
#define IS_FMC_AUTOREFRESH_NUMBER(__NUMBER__) (((__NUMBER__) > 0U) && ((__NUMBER__) <= 15U))
#define IS_FMC_MODE_REGISTER(__CONTENT__) ((__CONTENT__) <= 8191U)
#define IS_FMC_REFRESH_RATE(__RATE__) ((__RATE__) <= 8191U)
#define IS_FMC_SDRAM_DEVICE(__INSTANCE__) ((__INSTANCE__) == FMC_SDRAM_DEVICE)
#define IS_FMC_SDRAM_BANK(__BANK__) (((__BANK__) == FMC_SDRAM_BANK1) || \
                                     ((__BANK__) == FMC_SDRAM_BANK2))
#define IS_FMC_COLUMNBITS_NUMBER(__COLUMN__) (((__COLUMN__) == FMC_SDRAM_COLUMN_BITS_NUM_8)  || \
                                              ((__COLUMN__) == FMC_SDRAM_COLUMN_BITS_NUM_9)  || \
                                              ((__COLUMN__) == FMC_SDRAM_COLUMN_BITS_NUM_10) || \
                                              ((__COLUMN__) == FMC_SDRAM_COLUMN_BITS_NUM_11))
#define IS_FMC_ROWBITS_NUMBER(__ROW__) (((__ROW__) == FMC_SDRAM_ROW_BITS_NUM_11) || \
                                        ((__ROW__) == FMC_SDRAM_ROW_BITS_NUM_12) || \
                                        ((__ROW__) == FMC_SDRAM_ROW_BITS_NUM_13))
#define IS_FMC_INTERNALBANK_NUMBER(__NUMBER__) (((__NUMBER__) == FMC_SDRAM_INTERN_BANKS_NUM_2) || \
                                                ((__NUMBER__) == FMC_SDRAM_INTERN_BANKS_NUM_4))
#define IS_FMC_CAS_LATENCY(__LATENCY__) (((__LATENCY__) == FMC_SDRAM_CAS_LATENCY_1) || \
                                         ((__LATENCY__) == FMC_SDRAM_CAS_LATENCY_2) || \
                                         ((__LATENCY__) == FMC_SDRAM_CAS_LATENCY_3))


/**
  * @}
  */

/* Exported typedef ----------------------------------------------------------*/

/** @defgroup FMC_LL_Exported_typedef FMC Low Layer Exported Types
  * @{
  */

#define FMC_NORSRAM_TypeDef            FMC_Bank1_TypeDef
#define FMC_NORSRAM_EXTENDED_TypeDef   FMC_Bank1E_TypeDef
#define FMC_NAND_TypeDef               FMC_Bank3_TypeDef
#define FMC_SDRAM_TypeDef              FMC_Bank5_6_TypeDef

#define FMC_NORSRAM_DEVICE             FMC_Bank1_R
#define FMC_NORSRAM_EXTENDED_DEVICE    FMC_Bank1E_R
#define FMC_NAND_DEVICE                FMC_Bank3_R
#define FMC_SDRAM_DEVICE               FMC_Bank5_6_R

/**
  * @brief  FMC NORSRAM Configuration Structure definition
  */
typedef struct
{
  uint32_t NSBank;                       /*!< Specifies the NORSRAM memory device that will be used.
                                              This parameter can be a value of @ref FMC_NORSRAM_Bank                  */

  uint32_t DataAddressMux;               /*!< Specifies whether the address and data values are
                                              multiplexed on the data bus or not.
                                              This parameter can be a value of @ref FMC_Data_Address_Bus_Multiplexing */

  uint32_t MemoryType;                   /*!< Specifies the type of external memory attached to
                                              the corresponding memory device.
                                              This parameter can be a value of @ref FMC_Memory_Type                   */

  uint32_t MemoryDataWidth;              /*!< Specifies the external memory device width.
                                              This parameter can be a value of @ref FMC_NORSRAM_Data_Width            */

  uint32_t BurstAccessMode;              /*!< Enables or disables the burst access mode for Flash memory,
                                              valid only with synchronous burst Flash memories.
                                              This parameter can be a value of @ref FMC_Burst_Access_Mode             */

  uint32_t WaitSignalPolarity;           /*!< Specifies the wait signal polarity, valid only when accessing
                                              the Flash memory in burst mode.
                                              This parameter can be a value of @ref FMC_Wait_Signal_Polarity          */

  uint32_t WaitSignalActive;             /*!< Specifies if the wait signal is asserted by the memory one
                                              clock cycle before the wait state or during the wait state,
                                              valid only when accessing memories in burst mode.
                                              This parameter can be a value of @ref FMC_Wait_Timing                   */

  uint32_t WriteOperation;               /*!< Enables or disables the write operation in the selected device by the FMC.
                                              This parameter can be a value of @ref FMC_Write_Operation               */

  uint32_t WaitSignal;                   /*!< Enables or disables the wait state insertion via wait
                                              signal, valid for Flash memory access in burst mode.
                                              This parameter can be a value of @ref FMC_Wait_Signal                   */

  uint32_t ExtendedMode;                 /*!< Enables or disables the extended mode.
                                              This parameter can be a value of @ref FMC_Extended_Mode                 */

  uint32_t AsynchronousWait;             /*!< Enables or disables wait signal during asynchronous transfers,
                                              valid only with asynchronous Flash memories.
                                              This parameter can be a value of @ref FMC_AsynchronousWait              */

  uint32_t WriteBurst;                   /*!< Enables or disables the write burst operation.
                                              This parameter can be a value of @ref FMC_Write_Burst                   */

  uint32_t ContinuousClock;              /*!< Enables or disables the FMC clock output to external memory devices.
                                              This parameter is only enabled through the FMC_BCR1 register,
                                              and don't care through FMC_BCR2..4 registers.
                                              This parameter can be a value of @ref FMC_Continous_Clock               */

  uint32_t WriteFifo;                    /*!< Enables or disables the write FIFO used by the FMC controller.
                                              This parameter is only enabled through the FMC_BCR1 register,
                                              and don't care through FMC_BCR2..4 registers.
                                              This parameter can be a value of @ref FMC_Write_FIFO                    */

  uint32_t PageSize;                     /*!< Specifies the memory page size.
                                              This parameter can be a value of @ref FMC_Page_Size                     */
} FMC_NORSRAM_InitTypeDef;

/**
  * @brief  FMC NORSRAM Timing parameters structure definition
  */
typedef struct
{
  uint32_t AddressSetupTime;             /*!< Defines the number of HCLK cycles to configure
                                              the duration of the address setup time.
                                              This parameter can be a value between Min_Data = 0 and Max_Data = 15.
                                              @note This parameter is not used with synchronous NOR Flash memories.   */

  uint32_t AddressHoldTime;              /*!< Defines the number of HCLK cycles to configure
                                              the duration of the address hold time.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 15.
                                              @note This parameter is not used with synchronous NOR Flash memories.   */

  uint32_t DataSetupTime;                /*!< Defines the number of HCLK cycles to configure
                                              the duration of the data setup time.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 255.
                                              @note This parameter is used for SRAMs, ROMs and asynchronous multiplexed
                                              NOR Flash memories.                                                     */

  uint32_t BusTurnAroundDuration;        /*!< Defines the number of HCLK cycles to configure
                                              the duration of the bus turnaround.
                                              This parameter can be a value between Min_Data = 0 and Max_Data = 15.
                                              @note This parameter is only used for multiplexed NOR Flash memories.   */

  uint32_t CLKDivision;                  /*!< Defines the period of CLK clock output signal, expressed in number of
                                              HCLK cycles. This parameter can be a value between Min_Data = 2 and
                                              Max_Data = 16.
                                              @note This parameter is not used for asynchronous NOR Flash, SRAM or ROM
                                              accesses.                                                               */

  uint32_t DataLatency;                  /*!< Defines the number of memory clock cycles to issue
                                              to the memory before getting the first data.
                                              The parameter value depends on the memory type as shown below:
                                              - It must be set to 0 in case of a CRAM
                                              - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                              - It may assume a value between Min_Data = 2 and Max_Data = 17
                                                in NOR Flash memories with synchronous burst mode enable              */

  uint32_t AccessMode;                   /*!< Specifies the asynchronous access mode.
                                              This parameter can be a value of @ref FMC_Access_Mode                   */
} FMC_NORSRAM_TimingTypeDef;

/**
  * @brief  FMC NAND Configuration Structure definition
  */
typedef struct
{
  uint32_t NandBank;               /*!< Specifies the NAND memory device that will be used.
                                        This parameter can be a value of @ref FMC_NAND_Bank                  */

  uint32_t Waitfeature;            /*!< Enables or disables the Wait feature for the NAND Memory device.
                                        This parameter can be any value of @ref FMC_Wait_feature             */

  uint32_t MemoryDataWidth;        /*!< Specifies the external memory device width.
                                        This parameter can be any value of @ref FMC_NAND_Data_Width          */

  uint32_t EccComputation;         /*!< Enables or disables the ECC computation.
                                        This parameter can be any value of @ref FMC_ECC                      */

  uint32_t ECCPageSize;            /*!< Defines the page size for the extended ECC.
                                        This parameter can be any value of @ref FMC_ECC_Page_Size            */

  uint32_t TCLRSetupTime;          /*!< Defines the number of HCLK cycles to configure the
                                        delay between CLE low and RE low.
                                        This parameter can be a value between Min_Data = 0 and Max_Data = 255  */

  uint32_t TARSetupTime;           /*!< Defines the number of HCLK cycles to configure the
                                        delay between ALE low and RE low.
                                        This parameter can be a number between Min_Data = 0 and Max_Data = 255 */
} FMC_NAND_InitTypeDef;

/**
  * @brief  FMC NAND Timing parameters structure definition
  */
typedef struct
{
  uint32_t SetupTime;            /*!< Defines the number of HCLK cycles to setup address before
                                      the command assertion for NAND-Flash read or write access
                                      to common/Attribute or I/O memory space (depending on
                                      the memory space timing to be configured).
                                      This parameter can be a value between Min_Data = 0 and Max_Data = 254    */

  uint32_t WaitSetupTime;        /*!< Defines the minimum number of HCLK cycles to assert the
                                      command for NAND-Flash read or write access to
                                      common/Attribute or I/O memory space (depending on the
                                      memory space timing to be configured).
                                      This parameter can be a number between Min_Data = 0 and Max_Data = 254   */

  uint32_t HoldSetupTime;        /*!< Defines the number of HCLK clock cycles to hold address
                                      (and data for write access) after the command de-assertion
                                      for NAND-Flash read or write access to common/Attribute
                                      or I/O memory space (depending on the memory space timing
                                      to be configured).
                                      This parameter can be a number between Min_Data = 0 and Max_Data = 254   */

  uint32_t HiZSetupTime;         /*!< Defines the number of HCLK clock cycles during which the
                                      data bus is kept in HiZ after the start of a NAND-Flash
                                      write access to common/Attribute or I/O memory space (depending
                                      on the memory space timing to be configured).
                                      This parameter can be a number between Min_Data = 0 and Max_Data = 254   */
} FMC_NAND_PCC_TimingTypeDef;


/**
  * @brief  FMC SDRAM Configuration Structure definition
  */
typedef struct
{
  uint32_t SDBank;                      /*!< Specifies the SDRAM memory device that will be used.
                                             This parameter can be a value of @ref FMC_SDRAM_Bank                */

  uint32_t ColumnBitsNumber;            /*!< Defines the number of bits of column address.
                                             This parameter can be a value of @ref FMC_SDRAM_Column_Bits_number. */

  uint32_t RowBitsNumber;               /*!< Defines the number of bits of column address.
                                             This parameter can be a value of @ref FMC_SDRAM_Row_Bits_number.    */

  uint32_t MemoryDataWidth;             /*!< Defines the memory device width.
                                             This parameter can be a value of @ref FMC_SDRAM_Memory_Bus_Width.   */

  uint32_t InternalBankNumber;          /*!< Defines the number of the device's internal banks.
                                             This parameter can be of @ref FMC_SDRAM_Internal_Banks_Number.      */

  uint32_t CASLatency;                  /*!< Defines the SDRAM CAS latency in number of memory clock cycles.
                                             This parameter can be a value of @ref FMC_SDRAM_CAS_Latency.        */

  uint32_t WriteProtection;             /*!< Enables the SDRAM device to be accessed in write mode.
                                             This parameter can be a value of @ref FMC_SDRAM_Write_Protection.   */

  uint32_t SDClockPeriod;               /*!< Define the SDRAM Clock Period for both SDRAM devices and they allow
                                             to disable the clock before changing frequency.
                                             This parameter can be a value of @ref FMC_SDRAM_Clock_Period.       */

  uint32_t ReadBurst;                   /*!< This bit enable the SDRAM controller to anticipate the next read
                                             commands during the CAS latency and stores data in the Read FIFO.
                                             This parameter can be a value of @ref FMC_SDRAM_Read_Burst.         */

  uint32_t ReadPipeDelay;               /*!< Define the delay in system clock cycles on read data path.
                                             This parameter can be a value of @ref FMC_SDRAM_Read_Pipe_Delay.    */
} FMC_SDRAM_InitTypeDef;

/**
  * @brief FMC SDRAM Timing parameters structure definition
  */
typedef struct
{
  uint32_t LoadToActiveDelay;            /*!< Defines the delay between a Load Mode Register command and
                                              an active or Refresh command in number of memory clock cycles.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 16  */

  uint32_t ExitSelfRefreshDelay;         /*!< Defines the delay from releasing the self refresh command to
                                              issuing the Activate command in number of memory clock cycles.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 16  */

  uint32_t SelfRefreshTime;              /*!< Defines the minimum Self Refresh period in number of memory clock
                                              cycles.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 16  */

  uint32_t RowCycleDelay;                /*!< Defines the delay between the Refresh command and the Activate command
                                              and the delay between two consecutive Refresh commands in number of
                                              memory clock cycles.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 16  */

  uint32_t WriteRecoveryTime;            /*!< Defines the Write recovery Time in number of memory clock cycles.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 16  */

  uint32_t RPDelay;                      /*!< Defines the delay between a Precharge Command and an other command
                                              in number of memory clock cycles.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 16  */

  uint32_t RCDDelay;                     /*!< Defines the delay between the Activate Command and a Read/Write
                                              command in number of memory clock cycles.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 16  */
} FMC_SDRAM_TimingTypeDef;

/**
  * @brief SDRAM command parameters structure definition
  */
typedef struct
{
  uint32_t CommandMode;                  /*!< Defines the command issued to the SDRAM device.
                                              This parameter can be a value of @ref FMC_SDRAM_Command_Mode.          */

  uint32_t CommandTarget;                /*!< Defines which device (1 or 2) the command will be issued to.
                                              This parameter can be a value of @ref FMC_SDRAM_Command_Target.        */

  uint32_t AutoRefreshNumber;            /*!< Defines the number of consecutive auto refresh command issued
                                              in auto refresh mode.
                                              This parameter can be a value between Min_Data = 1 and Max_Data = 15   */

  uint32_t ModeRegisterDefinition;       /*!< Defines the SDRAM Mode register content                                */
} FMC_SDRAM_CommandTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @addtogroup FMC_LL_Exported_Constants FMC Low Layer Exported Constants
  * @{
  */

/** @defgroup FMC_LL_NOR_SRAM_Controller FMC NOR/SRAM Controller
  * @{
  */

/** @defgroup FMC_NORSRAM_Bank FMC NOR/SRAM Bank
  * @{
  */
#define FMC_NORSRAM_BANK1                       (0x00000000U)
#define FMC_NORSRAM_BANK2                       (0x00000002U)
#define FMC_NORSRAM_BANK3                       (0x00000004U)
#define FMC_NORSRAM_BANK4                       (0x00000006U)
/**
  * @}
  */

/** @defgroup FMC_Data_Address_Bus_Multiplexing FMC Data Address Bus Multiplexing
  * @{
  */
#define FMC_DATA_ADDRESS_MUX_DISABLE            (0x00000000U)
#define FMC_DATA_ADDRESS_MUX_ENABLE             (0x00000002U)
/**
  * @}
  */

/** @defgroup FMC_Memory_Type FMC Memory Type
  * @{
  */
#define FMC_MEMORY_TYPE_SRAM                    (0x00000000U)
#define FMC_MEMORY_TYPE_PSRAM                   (0x00000004U)
#define FMC_MEMORY_TYPE_NOR                     (0x00000008U)
/**
  * @}
  */

/** @defgroup FMC_NORSRAM_Data_Width FMC NORSRAM Data Width
  * @{
  */
#define FMC_NORSRAM_MEM_BUS_WIDTH_8             (0x00000000U)
#define FMC_NORSRAM_MEM_BUS_WIDTH_16            (0x00000010U)
#define FMC_NORSRAM_MEM_BUS_WIDTH_32            (0x00000020U)
/**
  * @}
  */

/** @defgroup FMC_NORSRAM_Flash_Access FMC NOR/SRAM Flash Access
  * @{
  */
#define FMC_NORSRAM_FLASH_ACCESS_ENABLE         (0x00000040U)
#define FMC_NORSRAM_FLASH_ACCESS_DISABLE        (0x00000000U)
/**
  * @}
  */

/** @defgroup FMC_Burst_Access_Mode FMC Burst Access Mode
  * @{
  */
#define FMC_BURST_ACCESS_MODE_DISABLE           (0x00000000U)
#define FMC_BURST_ACCESS_MODE_ENABLE            (0x00000100U)
/**
  * @}
  */

/** @defgroup FMC_Wait_Signal_Polarity FMC Wait Signal Polarity
  * @{
  */
#define FMC_WAIT_SIGNAL_POLARITY_LOW            (0x00000000U)
#define FMC_WAIT_SIGNAL_POLARITY_HIGH           (0x00000200U)
/**
  * @}
  */

/** @defgroup FMC_Wait_Timing FMC Wait Timing
  * @{
  */
#define FMC_WAIT_TIMING_BEFORE_WS               (0x00000000U)
#define FMC_WAIT_TIMING_DURING_WS               (0x00000800U)
/**
  * @}
  */

/** @defgroup FMC_Write_Operation FMC Write Operation
  * @{
  */
#define FMC_WRITE_OPERATION_DISABLE             (0x00000000U)
#define FMC_WRITE_OPERATION_ENABLE              (0x00001000U)
/**
  * @}
  */

/** @defgroup FMC_Wait_Signal FMC Wait Signal
  * @{
  */
#define FMC_WAIT_SIGNAL_DISABLE                 (0x00000000U)
#define FMC_WAIT_SIGNAL_ENABLE                  (0x00002000U)
/**
  * @}
  */

/** @defgroup FMC_Extended_Mode FMC Extended Mode
  * @{
  */
#define FMC_EXTENDED_MODE_DISABLE               (0x00000000U)
#define FMC_EXTENDED_MODE_ENABLE                (0x00004000U)
/**
  * @}
  */

/** @defgroup FMC_AsynchronousWait FMC Asynchronous Wait
  * @{
  */
#define FMC_ASYNCHRONOUS_WAIT_DISABLE           (0x00000000U)
#define FMC_ASYNCHRONOUS_WAIT_ENABLE            (0x00008000U)
/**
  * @}
  */

/** @defgroup FMC_Page_Size FMC Page Size
  * @{
  */
#define FMC_PAGE_SIZE_NONE                      (0x00000000U)
#define FMC_PAGE_SIZE_128                       FMC_BCRx_CPSIZE_0
#define FMC_PAGE_SIZE_256                       FMC_BCRx_CPSIZE_1
#define FMC_PAGE_SIZE_512                       (FMC_BCRx_CPSIZE_0\
                                                 | FMC_BCRx_CPSIZE_1)
#define FMC_PAGE_SIZE_1024                      FMC_BCRx_CPSIZE_2
/**
  * @}
  */

/** @defgroup FMC_Write_Burst FMC Write Burst
  * @{
  */
#define FMC_WRITE_BURST_DISABLE                 (0x00000000U)
#define FMC_WRITE_BURST_ENABLE                  (0x00080000U)
/**
  * @}
  */

/** @defgroup FMC_Continous_Clock FMC Continuous Clock
  * @{
  */
#define FMC_CONTINUOUS_CLOCK_SYNC_ONLY          (0x00000000U)
#define FMC_CONTINUOUS_CLOCK_SYNC_ASYNC         (0x00100000U)
/**
  * @}
  */

#if defined(FMC_BCR1_WFDIS)
/** @defgroup FMC_Write_FIFO FMC Write FIFO
  * @{
  */
#define FMC_WRITE_FIFO_DISABLE                  FMC_BCR1_WFDIS
#define FMC_WRITE_FIFO_ENABLE                   (0x00000000U)
#endif /* FMC_BCR1_WFDIS */
/**
  * @}
  */

/** @defgroup FMC_Access_Mode FMC Access Mode
  * @{
  */
#define FMC_ACCESS_MODE_A                       (0x00000000U)
#define FMC_ACCESS_MODE_B                       (0x10000000U)
#define FMC_ACCESS_MODE_C                       (0x20000000U)
#define FMC_ACCESS_MODE_D                       (0x30000000U)
/**
  * @}
  */

/**
  * @}
  */


/** @defgroup FMC_LL_NAND_Controller FMC NAND Controller
  * @{
  */
/** @defgroup FMC_NAND_Bank FMC NAND Bank
  * @{
  */
#define FMC_NAND_BANK3                          (0x00000100U)
/**
  * @}
  */

/** @defgroup FMC_Wait_feature FMC Wait feature
  * @{
  */
#define FMC_NAND_WAIT_FEATURE_DISABLE           (0x00000000U)
#define FMC_NAND_WAIT_FEATURE_ENABLE            (0x00000002U)
/**
  * @}
  */

/** @defgroup FMC_PCR_Memory_Type FMC PCR Memory Type
  * @{
  */
#define FMC_PCR_MEMORY_TYPE_NAND                (0x00000008U)
/**
  * @}
  */

/** @defgroup FMC_NAND_Data_Width FMC NAND Data Width
  * @{
  */
#define FMC_NAND_MEM_BUS_WIDTH_8                (0x00000000U)
#define FMC_NAND_MEM_BUS_WIDTH_16               (0x00000010U)
/**
  * @}
  */

/** @defgroup FMC_ECC FMC ECC
  * @{
  */
#define FMC_NAND_ECC_DISABLE                    (0x00000000U)
#define FMC_NAND_ECC_ENABLE                     (0x00000040U)
/**
  * @}
  */

/** @defgroup FMC_ECC_Page_Size FMC ECC Page Size
  * @{
  */
#define FMC_NAND_ECC_PAGE_SIZE_256BYTE          (0x00000000U)
#define FMC_NAND_ECC_PAGE_SIZE_512BYTE          (0x00020000U)
#define FMC_NAND_ECC_PAGE_SIZE_1024BYTE         (0x00040000U)
#define FMC_NAND_ECC_PAGE_SIZE_2048BYTE         (0x00060000U)
#define FMC_NAND_ECC_PAGE_SIZE_4096BYTE         (0x00080000U)
#define FMC_NAND_ECC_PAGE_SIZE_8192BYTE         (0x000A0000U)
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FMC_LL_SDRAM_Controller FMC SDRAM Controller
  * @{
  */
/** @defgroup FMC_SDRAM_Bank FMC SDRAM Bank
  * @{
  */
#define FMC_SDRAM_BANK1                         (0x00000000U)
#define FMC_SDRAM_BANK2                         (0x00000001U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Column_Bits_number FMC SDRAM Column Bits number
  * @{
  */
#define FMC_SDRAM_COLUMN_BITS_NUM_8             (0x00000000U)
#define FMC_SDRAM_COLUMN_BITS_NUM_9             (0x00000001U)
#define FMC_SDRAM_COLUMN_BITS_NUM_10            (0x00000002U)
#define FMC_SDRAM_COLUMN_BITS_NUM_11            (0x00000003U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Row_Bits_number FMC SDRAM Row Bits number
  * @{
  */
#define FMC_SDRAM_ROW_BITS_NUM_11               (0x00000000U)
#define FMC_SDRAM_ROW_BITS_NUM_12               (0x00000004U)
#define FMC_SDRAM_ROW_BITS_NUM_13               (0x00000008U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Memory_Bus_Width FMC SDRAM Memory Bus Width
  * @{
  */
#define FMC_SDRAM_MEM_BUS_WIDTH_8               (0x00000000U)
#define FMC_SDRAM_MEM_BUS_WIDTH_16              (0x00000010U)
#define FMC_SDRAM_MEM_BUS_WIDTH_32              (0x00000020U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Internal_Banks_Number FMC SDRAM Internal Banks Number
  * @{
  */
#define FMC_SDRAM_INTERN_BANKS_NUM_2            (0x00000000U)
#define FMC_SDRAM_INTERN_BANKS_NUM_4            (0x00000040U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_CAS_Latency FMC SDRAM CAS Latency
  * @{
  */
#define FMC_SDRAM_CAS_LATENCY_1                 (0x00000080U)
#define FMC_SDRAM_CAS_LATENCY_2                 (0x00000100U)
#define FMC_SDRAM_CAS_LATENCY_3                 (0x00000180U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Write_Protection FMC SDRAM Write Protection
  * @{
  */
#define FMC_SDRAM_WRITE_PROTECTION_DISABLE      (0x00000000U)
#define FMC_SDRAM_WRITE_PROTECTION_ENABLE       (0x00000200U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Clock_Period FMC SDRAM Clock Period
  * @{
  */
#define FMC_SDRAM_CLOCK_DISABLE                 (0x00000000U)
#define FMC_SDRAM_CLOCK_PERIOD_2                (0x00000800U)
#define FMC_SDRAM_CLOCK_PERIOD_3                (0x00000C00U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Read_Burst FMC SDRAM Read Burst
  * @{
  */
#define FMC_SDRAM_RBURST_DISABLE                (0x00000000U)
#define FMC_SDRAM_RBURST_ENABLE                 (0x00001000U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Read_Pipe_Delay FMC SDRAM Read Pipe Delay
  * @{
  */
#define FMC_SDRAM_RPIPE_DELAY_0                 (0x00000000U)
#define FMC_SDRAM_RPIPE_DELAY_1                 (0x00002000U)
#define FMC_SDRAM_RPIPE_DELAY_2                 (0x00004000U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Command_Mode FMC SDRAM Command Mode
  * @{
  */
#define FMC_SDRAM_CMD_NORMAL_MODE               (0x00000000U)
#define FMC_SDRAM_CMD_CLK_ENABLE                (0x00000001U)
#define FMC_SDRAM_CMD_PALL                      (0x00000002U)
#define FMC_SDRAM_CMD_AUTOREFRESH_MODE          (0x00000003U)
#define FMC_SDRAM_CMD_LOAD_MODE                 (0x00000004U)
#define FMC_SDRAM_CMD_SELFREFRESH_MODE          (0x00000005U)
#define FMC_SDRAM_CMD_POWERDOWN_MODE            (0x00000006U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Command_Target FMC SDRAM Command Target
  * @{
  */
#define FMC_SDRAM_CMD_TARGET_BANK2              FMC_SDCMR_CTB2
#define FMC_SDRAM_CMD_TARGET_BANK1              FMC_SDCMR_CTB1
#define FMC_SDRAM_CMD_TARGET_BANK1_2            (0x00000018U)
/**
  * @}
  */

/** @defgroup FMC_SDRAM_Mode_Status FMC SDRAM Mode Status
  * @{
  */
#define FMC_SDRAM_NORMAL_MODE                   (0x00000000U)
#define FMC_SDRAM_SELF_REFRESH_MODE             FMC_SDSR_MODES1_0
#define FMC_SDRAM_POWER_DOWN_MODE               FMC_SDSR_MODES1_1
/**
  * @}
  */

/**
  * @}
  */


/** @defgroup FMC_LL_Interrupt_definition FMC Low Layer Interrupt definition
  * @{
  */
#define FMC_IT_RISING_EDGE                      (0x00000008U)
#define FMC_IT_LEVEL                            (0x00000010U)
#define FMC_IT_FALLING_EDGE                     (0x00000020U)
#define FMC_IT_REFRESH_ERROR                    (0x00004000U)
/**
  * @}
  */

/** @defgroup FMC_LL_Flag_definition FMC Low Layer Flag definition
  * @{
  */
#define FMC_FLAG_RISING_EDGE                    (0x00000001U)
#define FMC_FLAG_LEVEL                          (0x00000002U)
#define FMC_FLAG_FALLING_EDGE                   (0x00000004U)
#define FMC_FLAG_FEMPT                          (0x00000040U)
#define FMC_SDRAM_FLAG_REFRESH_IT               FMC_SDSR_RE
#define FMC_SDRAM_FLAG_BUSY                     FMC_SDSR_BUSY
#define FMC_SDRAM_FLAG_REFRESH_ERROR            FMC_SDRTR_CRE
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/** @defgroup FMC_LL_Private_Macros FMC_LL  Private Macros
  * @{
  */
/**
  * @brief  Enable the FMC Peripheral.
  * @retval None
  */
#define __FMC_ENABLE()  (FMC_Bank1_R->BTCR[0] |= FMC_BCR1_FMCEN)

/**
  * @brief  Disable the FMC Peripheral.
  * @retval None
  */
#define __FMC_DISABLE()  (FMC_Bank1_R->BTCR[0] &= ~FMC_BCR1_FMCEN)
/** @defgroup FMC_LL_NOR_Macros FMC NOR/SRAM Macros
  * @brief macros to handle NOR device enable/disable and read/write operations
  * @{
  */

/**
  * @brief  Enable the NORSRAM device access.
  * @param  __INSTANCE__ FMC_NORSRAM Instance
  * @param  __BANK__ FMC_NORSRAM Bank
  * @retval None
  */
#define __FMC_NORSRAM_ENABLE(__INSTANCE__, __BANK__)  ((__INSTANCE__)->BTCR[(__BANK__)]\
                                                       |= FMC_BCRx_MBKEN)

/**
  * @brief  Disable the NORSRAM device access.
  * @param  __INSTANCE__ FMC_NORSRAM Instance
  * @param  __BANK__ FMC_NORSRAM Bank
  * @retval None
  */
#define __FMC_NORSRAM_DISABLE(__INSTANCE__, __BANK__) ((__INSTANCE__)->BTCR[(__BANK__)]\
                                                       &= ~FMC_BCRx_MBKEN)

/**
  * @}
  */

/** @defgroup FMC_LL_NAND_Macros FMC NAND Macros
  *  @brief macros to handle NAND device enable/disable
  *  @{
  */

/**
  * @brief  Enable the NAND device access.
  * @param  __INSTANCE__ FMC_NAND Instance
  * @retval None
  */
#define __FMC_NAND_ENABLE(__INSTANCE__)  ((__INSTANCE__)->PCR |= FMC_PCR_PBKEN)

/**
  * @brief  Disable the NAND device access.
  * @param  __INSTANCE__ FMC_NAND Instance
  * @param  __BANK__     FMC_NAND Bank
  * @retval None
  */
#define __FMC_NAND_DISABLE(__INSTANCE__, __BANK__) CLEAR_BIT((__INSTANCE__)->PCR, FMC_PCR_PBKEN)

/**
  * @}
  */

/** @defgroup FMC_LL_NAND_Interrupt FMC NAND Interrupt
  * @brief macros to handle NAND interrupts
  * @{
  */

/**
  * @brief  Enable the NAND device interrupt.
  * @param  __INSTANCE__  FMC_NAND instance
  * @param  __INTERRUPT__ FMC_NAND interrupt
  *         This parameter can be any combination of the following values:
  *            @arg FMC_IT_RISING_EDGE: Interrupt rising edge.
  *            @arg FMC_IT_LEVEL: Interrupt level.
  *            @arg FMC_IT_FALLING_EDGE: Interrupt falling edge.
  * @retval None
  */
#define __FMC_NAND_ENABLE_IT(__INSTANCE__, __INTERRUPT__)  ((__INSTANCE__)->SR |= (__INTERRUPT__))

/**
  * @brief  Disable the NAND device interrupt.
  * @param  __INSTANCE__  FMC_NAND Instance
  * @param  __INTERRUPT__ FMC_NAND interrupt
  *         This parameter can be any combination of the following values:
  *            @arg FMC_IT_RISING_EDGE: Interrupt rising edge.
  *            @arg FMC_IT_LEVEL: Interrupt level.
  *            @arg FMC_IT_FALLING_EDGE: Interrupt falling edge.
  * @retval None
  */
#define __FMC_NAND_DISABLE_IT(__INSTANCE__, __INTERRUPT__)  ((__INSTANCE__)->SR &= ~(__INTERRUPT__))

/**
  * @brief  Get flag status of the NAND device.
  * @param  __INSTANCE__ FMC_NAND Instance
  * @param  __BANK__     FMC_NAND Bank
  * @param  __FLAG__     FMC_NAND flag
  *         This parameter can be any combination of the following values:
  *            @arg FMC_FLAG_RISING_EDGE: Interrupt rising edge flag.
  *            @arg FMC_FLAG_LEVEL: Interrupt level edge flag.
  *            @arg FMC_FLAG_FALLING_EDGE: Interrupt falling edge flag.
  *            @arg FMC_FLAG_FEMPT: FIFO empty flag.
  * @retval The state of FLAG (SET or RESET).
  */
#define __FMC_NAND_GET_FLAG(__INSTANCE__, __BANK__, __FLAG__)  (((__INSTANCE__)->SR &(__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear flag status of the NAND device.
  * @param  __INSTANCE__ FMC_NAND Instance
  * @param  __FLAG__     FMC_NAND flag
  *         This parameter can be any combination of the following values:
  *            @arg FMC_FLAG_RISING_EDGE: Interrupt rising edge flag.
  *            @arg FMC_FLAG_LEVEL: Interrupt level edge flag.
  *            @arg FMC_FLAG_FALLING_EDGE: Interrupt falling edge flag.
  *            @arg FMC_FLAG_FEMPT: FIFO empty flag.
  * @retval None
  */
#define __FMC_NAND_CLEAR_FLAG(__INSTANCE__, __FLAG__)  ((__INSTANCE__)->SR &= ~(__FLAG__))

/**
  * @}
  */


/** @defgroup FMC_LL_SDRAM_Interrupt FMC SDRAM Interrupt
  * @brief macros to handle SDRAM interrupts
  * @{
  */

/**
  * @brief  Enable the SDRAM device interrupt.
  * @param  __INSTANCE__  FMC_SDRAM instance
  * @param  __INTERRUPT__ FMC_SDRAM interrupt
  *         This parameter can be any combination of the following values:
  *            @arg FMC_IT_REFRESH_ERROR: Interrupt refresh error
  * @retval None
  */
#define __FMC_SDRAM_ENABLE_IT(__INSTANCE__, __INTERRUPT__)  ((__INSTANCE__)->SDRTR |= (__INTERRUPT__))

/**
  * @brief  Disable the SDRAM device interrupt.
  * @param  __INSTANCE__  FMC_SDRAM instance
  * @param  __INTERRUPT__ FMC_SDRAM interrupt
  *         This parameter can be any combination of the following values:
  *            @arg FMC_IT_REFRESH_ERROR: Interrupt refresh error
  * @retval None
  */
#define __FMC_SDRAM_DISABLE_IT(__INSTANCE__, __INTERRUPT__)  ((__INSTANCE__)->SDRTR &= ~(__INTERRUPT__))

/**
  * @brief  Get flag status of the SDRAM device.
  * @param  __INSTANCE__ FMC_SDRAM instance
  * @param  __FLAG__     FMC_SDRAM flag
  *         This parameter can be any combination of the following values:
  *            @arg FMC_SDRAM_FLAG_REFRESH_IT: Interrupt refresh error.
  *            @arg FMC_SDRAM_FLAG_BUSY: SDRAM busy flag.
  *            @arg FMC_SDRAM_FLAG_REFRESH_ERROR: Refresh error flag.
  * @retval The state of FLAG (SET or RESET).
  */
#define __FMC_SDRAM_GET_FLAG(__INSTANCE__, __FLAG__)  (((__INSTANCE__)->SDSR &(__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear flag status of the SDRAM device.
  * @param  __INSTANCE__ FMC_SDRAM instance
  * @param  __FLAG__     FMC_SDRAM flag
  *         This parameter can be any combination of the following values:
  *           @arg FMC_SDRAM_FLAG_REFRESH_ERROR
  * @retval None
  */
#define __FMC_SDRAM_CLEAR_FLAG(__INSTANCE__, __FLAG__)  ((__INSTANCE__)->SDRTR |= (__FLAG__))

/**
  * @}
  */
/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup FMC_LL_Private_Functions FMC LL Private Functions
  *  @{
  */

/** @defgroup FMC_LL_NORSRAM  NOR SRAM
  *  @{
  */
/** @defgroup FMC_LL_NORSRAM_Private_Functions_Group1 NOR SRAM Initialization/de-initialization functions
  *  @{
  */
HAL_StatusTypeDef  FMC_NORSRAM_Init(FMC_NORSRAM_TypeDef *Device,
                                    FMC_NORSRAM_InitTypeDef *Init);
HAL_StatusTypeDef  FMC_NORSRAM_Timing_Init(FMC_NORSRAM_TypeDef *Device,
                                           FMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank);
HAL_StatusTypeDef  FMC_NORSRAM_Extended_Timing_Init(FMC_NORSRAM_EXTENDED_TypeDef *Device,
                                                    FMC_NORSRAM_TimingTypeDef *Timing, uint32_t Bank,
                                                    uint32_t ExtendedMode);
HAL_StatusTypeDef  FMC_NORSRAM_DeInit(FMC_NORSRAM_TypeDef *Device,
                                      FMC_NORSRAM_EXTENDED_TypeDef *ExDevice, uint32_t Bank);
/**
  * @}
  */

/** @defgroup FMC_LL_NORSRAM_Private_Functions_Group2 NOR SRAM Control functions
  *  @{
  */
HAL_StatusTypeDef  FMC_NORSRAM_WriteOperation_Enable(FMC_NORSRAM_TypeDef *Device, uint32_t Bank);
HAL_StatusTypeDef  FMC_NORSRAM_WriteOperation_Disable(FMC_NORSRAM_TypeDef *Device, uint32_t Bank);
/**
  * @}
  */
/**
  * @}
  */

/** @defgroup FMC_LL_NAND NAND
  *  @{
  */
/** @defgroup FMC_LL_NAND_Private_Functions_Group1 NAND Initialization/de-initialization functions
  *  @{
  */
HAL_StatusTypeDef  FMC_NAND_Init(FMC_NAND_TypeDef *Device, FMC_NAND_InitTypeDef *Init);
HAL_StatusTypeDef  FMC_NAND_CommonSpace_Timing_Init(FMC_NAND_TypeDef *Device,
                                                    FMC_NAND_PCC_TimingTypeDef *Timing, uint32_t Bank);
HAL_StatusTypeDef  FMC_NAND_AttributeSpace_Timing_Init(FMC_NAND_TypeDef *Device,
                                                       FMC_NAND_PCC_TimingTypeDef *Timing, uint32_t Bank);
HAL_StatusTypeDef  FMC_NAND_DeInit(FMC_NAND_TypeDef *Device, uint32_t Bank);
/**
  * @}
  */

/** @defgroup FMC_LL_NAND_Private_Functions_Group2 NAND Control functions
  *  @{
  */
HAL_StatusTypeDef  FMC_NAND_ECC_Enable(FMC_NAND_TypeDef *Device, uint32_t Bank);
HAL_StatusTypeDef  FMC_NAND_ECC_Disable(FMC_NAND_TypeDef *Device, uint32_t Bank);
HAL_StatusTypeDef  FMC_NAND_GetECC(FMC_NAND_TypeDef *Device, uint32_t *ECCval, uint32_t Bank,
                                   uint32_t Timeout);
/**
  * @}
  */
/**
  * @}
  */


/** @defgroup FMC_LL_SDRAM SDRAM
  *  @{
  */
/** @defgroup FMC_LL_SDRAM_Private_Functions_Group1 SDRAM Initialization/de-initialization functions
  *  @{
  */
HAL_StatusTypeDef  FMC_SDRAM_Init(FMC_SDRAM_TypeDef *Device, FMC_SDRAM_InitTypeDef *Init);
HAL_StatusTypeDef  FMC_SDRAM_Timing_Init(FMC_SDRAM_TypeDef *Device,
                                         FMC_SDRAM_TimingTypeDef *Timing, uint32_t Bank);
HAL_StatusTypeDef  FMC_SDRAM_DeInit(FMC_SDRAM_TypeDef *Device, uint32_t Bank);
/**
  * @}
  */

/** @defgroup FMC_LL_SDRAM_Private_Functions_Group2 SDRAM Control functions
  *  @{
  */
HAL_StatusTypeDef  FMC_SDRAM_WriteProtection_Enable(FMC_SDRAM_TypeDef *Device, uint32_t Bank);
HAL_StatusTypeDef  FMC_SDRAM_WriteProtection_Disable(FMC_SDRAM_TypeDef *Device, uint32_t Bank);
HAL_StatusTypeDef  FMC_SDRAM_SendCommand(FMC_SDRAM_TypeDef *Device,
                                         FMC_SDRAM_CommandTypeDef *Command, uint32_t Timeout);
HAL_StatusTypeDef  FMC_SDRAM_ProgramRefreshRate(FMC_SDRAM_TypeDef *Device, uint32_t RefreshRate);
HAL_StatusTypeDef  FMC_SDRAM_SetAutoRefreshNumber(FMC_SDRAM_TypeDef *Device,
                                                  uint32_t AutoRefreshNumber);
uint32_t           FMC_SDRAM_GetModeStatus(const FMC_SDRAM_TypeDef *Device, uint32_t Bank);
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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7xx_LL_FMC_H */
