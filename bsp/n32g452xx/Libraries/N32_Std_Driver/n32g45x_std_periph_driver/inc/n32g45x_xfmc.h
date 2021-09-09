/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_xfmc.h
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G45X_XFMC_H__
#define __N32G45X_XFMC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup XFMC
 * @{
 */

/** @addtogroup XFMC_Exported_Types
 * @{
 */

/**
 * @brief  Timing parameters For NOR/SRAM Banks
 */
typedef struct
{
    uint32_t AddrSetTime;       /*!< Defines the number of HCLK cycles to configure
                                    the duration of the address setup time.
                                    This parameter can be a value between 0 and 0xF.
                                    @note: It is not used with synchronous NOR Flash memories. */

    uint32_t AddrHoldTime;      /*!< Defines the number of HCLK cycles to configure
                                    the duration of the address hold time.
                                    This parameter can be a value between 0 and 0xF.
                                    @note: It is not used with synchronous NOR Flash memories.*/

    uint32_t DataSetTime;       /*!< Defines the number of HCLK cycles to configure
                                    the duration of the data setup time.
                                    This parameter can be a value between 1 and 0xFF.
                                    @note: It is used for SRAMs, ROMs and asynchronous multiplexed NOR Flash memories. */

    uint32_t BusRecoveryCycle;  /*!< Defines the number of HCLK cycles to configure
                                    the duration of the bus turnaround.
                                    This parameter can be a value between 0 and 0xF.
                                    @note: It is only used for multiplexed NOR Flash memories. */

    uint32_t ClkDiv;            /*!< Defines the period of CLK clock output signal, expressed in number of HCLK cycles.
                                    This parameter can be a value between 1 and 0xF.
                                    @note: This parameter is not used for asynchronous NOR Flash, SRAM or ROM accesses. */

    uint32_t DataLatency;       /*!< Defines the number of memory clock cycles to issue
                                    to the memory before getting the first data.
                                    The value of this parameter depends on the memory type as shown below:
                                    - It must be set to 0 in case of a CRAM
                                    - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                    - It may assume a value between 0 and 0xF in NOR Flash memories
                                      with synchronous burst mode enable */

    uint32_t AccMode;           /*!< Specifies the asynchronous access mode.
                                    This parameter can be a value of @ref XFMC_Access_Mode */
} XFMC_NorSramTimingInitType;

/**
 * @brief  XFMC NOR/SRAM Init structure definition
 */

typedef struct
{
    XFMC_Bank1_Block *Block;    /*!< Specifies the NOR/SRAM memory bank block that will be used.
                                    This parameter can be a XFMC_BANK1_BLOCK1 or XFMC_BANK1_BLOCK2 */

    uint32_t DataAddrMux;       /*!< Specifies whether the address and data values are
                                    multiplexed on the databus or not.
                                    This parameter can be a value of @ref XFMC_Data_Address_Bus_Multiplexing */

    uint32_t MemType;           /*!< Specifies the type of external memory attached to
                                    the corresponding memory bank.
                                    This parameter can be a value of @ref XFMC_Memory_Type */

    uint32_t MemDataWidth;      /*!< Specifies the external memory device width.
                                    This parameter can be a value of @ref XFMC_Data_Width */

    uint32_t BurstAccMode;      /*!< Enables or disables the burst access mode for Flash memory,
                                    valid only with synchronous burst Flash memories.
                                    This parameter can be a value of @ref XFMC_Burst_Access_Mode */

    uint32_t AsynchroWait;      /*!< Enables or disables wait signal during asynchronous transfers,
                                    valid only with asynchronous Flash memories.
                                    This parameter can be a value of @ref AsynchroWait */

    uint32_t WaitSigPolarity;   /*!< Specifies the wait signal polarity, valid only when accessing
                                    the Flash memory in burst mode.
                                    This parameter can be a value of @ref XFMC_Wait_Signal_Polarity */

    uint32_t WrapMode;          /*!< Enables or disables the Wrapped burst access mode for Flash
                                    memory, valid only when accessing Flash memories in burst mode.
                                    This parameter can be a value of @ref XFMC_Wrap_Mode */

    uint32_t WaitSigConfig;     /*!< Specifies if the wait signal is asserted by the memory one
                                    clock cycle before the wait state or during the wait state,
                                    valid only when accessing memories in burst mode.
                                    This parameter can be a value of @ref XFMC_Wait_Timing */

    uint32_t WriteEnable;       /*!< Enables or disables the write operation in the selected bank by the XFMC.
                                    This parameter can be a value of @ref XFMC_Write_Operation */

    uint32_t WaitSigEnable;     /*!< Enables or disables the wait-state insertion via wait
                                    signal, valid for Flash memory access in burst mode.
                                    This parameter can be a value of @ref XFMC_Wait_Signal */

    uint32_t ExtModeEnable;     /*!< Enables or disables the extended mode.
                                    This parameter can be a value of @ref XFMC_Extended_Mode */

    uint32_t WriteBurstEnable;  /*!< Enables or disables the write burst operation.
                                    This parameter can be a value of @ref XFMC_Write_Burst */

    XFMC_NorSramTimingInitType* RWTimingStruct; /*!< Timing Parameters for write and read access
                                                        if the  ExtendedMode is not used*/

    XFMC_NorSramTimingInitType* WTimingStruct;  /*!< Timing Parameters for write access if the
                                                        ExtendedMode is used*/
} XFMC_NorSramInitTpye;

/**
 * @brief  Timing parameters For XFMC NAND and PCCARD Banks
 */

typedef struct
{
    uint32_t SetTime;       /*!< Defines the number of HCLK cycles to setup address before
                                the command assertion for NAND-Flash read or write access
                                to common/Attribute or I/O memory space (depending on
                                the memory space timing to be configured).
                                This parameter can be a value between 0 and 0xFF.*/

    uint32_t WaitSetTime;   /*!< Defines the minimum number of HCLK cycles to assert the
                                command for NAND-Flash read or write access to
                                common/Attribute or I/O memory space (depending on the
                                memory space timing to be configured).
                                This parameter can be a number between 0x00 and 0xFF */

    uint32_t HoldSetTime;   /*!< Defines the number of HCLK clock cycles to hold address
                                (and data for write access) after the command deassertion
                                for NAND-Flash read or write access to common/Attribute
                                or I/O memory space (depending on the memory space timing
                                to be configured).
                                This parameter can be a number between 0x00 and 0xFF */

    uint32_t HiZSetTime;    /*!< Defines the number of HCLK clock cycles during which the
                                databus is kept in HiZ after the start of a NAND-Flash
                                write access to common/Attribute or I/O memory space (depending
                                on the memory space timing to be configured).
                                This parameter can be a number between 0x00 and 0xFF */
} XFMC_NandTimingInitType;

/**
 * @brief  XFMC NAND Init structure definition
 */

typedef struct
{
    XFMC_Bank23_Module *Bank;   /*!< Specifies the NAND memory bank that will be used.
                                    This parameter can be XFMC_BANK2 or XFMC_BANK3 */

    uint32_t WaitFeatureEnable; /*!< Enables or disables the Wait feature for the NAND Memory Bank.
                                    This parameter can be any value of @ref XFMC_Wait_feature */

    uint32_t MemDataWidth;      /*!< Specifies the external memory device width.
                                    This parameter can be any value of @ref XFMC_Data_Width */

    uint32_t EccEnable;         /*!< Enables or disables the ECC computation.
                                    This parameter can be any value of @ref XFMC_Ecc */

    uint32_t EccPageSize;       /*!< Defines the page size for the extended ECC.
                                    This parameter can be any value of @ref XFMC_ECC_Page_Size */

    uint32_t TCLRSetTime;       /*!< Defines the number of HCLK cycles to configure the
                                    delay between CLE low and RE low.
                                    This parameter can be a value between 0 and 0xFF. */

    uint32_t TARSetTime;        /*!< Defines the number of HCLK cycles to configure the
                                    delay between ALE low and RE low.
                                    This parameter can be a number between 0x0 and 0xFF */

    XFMC_NandTimingInitType* CommSpaceTimingStruct; /*!< XFMC Common Space Timing */

    XFMC_NandTimingInitType* AttrSpaceTimingStruct; /*!< XFMC Attribute Space Timing */
} XFMC_NandInitType;

/**
 * @brief  XFMC PCCARD Init structure definition
 */

typedef struct
{
    uint32_t WaitFeatureEnable; /*!< Enables or disables the Wait feature for the Memory Bank.
                                    This parameter can be any value of @ref XFMC_Wait_feature */

    uint32_t TCLRSetTime;       /*!< Defines the number of HCLK cycles to configure the
                                    delay between CLE low and RE low.
                                    This parameter can be a value between 0 and 0xFF. */

    uint32_t TARSetTime;        /*!< Defines the number of HCLK cycles to configure the
                                    delay between ALE low and RE low.
                                    This parameter can be a number between 0x0 and 0xFF */

    XFMC_NandTimingInitType* CommSpaceTimingStruct;     /*!< XFMC Common Space Timing */

    XFMC_NandTimingInitType* AttrSpaceTimingStruct;     /*!< XFMC Attribute Space Timing */

    XFMC_NandTimingInitType* XFMC_IOSpaceTimingStruct;  /*!< XFMC IO Space Timing */
} XFMC_PCCARDInitType;

/**
 * @}
 */

/** @addtogroup XFMC_Exported_Constants
 * @{
 */

/** @addtogroup XFMC_NORSRAM_Bank1_Reg_ResetValue
 * @{
 */
#define XFMC_NOR_SRAM_CR1_RESET         ((uint32_t)0x000030DB)
#define XFMC_NOR_SRAM_CR2_RESET         ((uint32_t)0x000030D2)
#define XFMC_NOR_SRAM_TR_RESET          ((uint32_t)0x0FFFFFFF)
#define XFMC_NOR_SRAM_WTR_RESET         ((uint32_t)0x0FFFFFFF)

/**
 * @}
 */

/** @addtogroup XFMC_NAND_Bank23_Reg_ResetValue
 * @{
 */
#define XFMC_NAND_CTRL_RESET            ((uint32_t)0x00000018)
#define XFMC_NAND_STS_RESET             ((uint32_t)0x00000040)
#define XFMC_NAND_CMEMTM_RESET          ((uint32_t)0xFCFCFCFC)
#define XFMC_NAND_ATTMEMTM_RESET        ((uint32_t)0xFCFCFCFC)

/**
 * @}
 */

#define IS_XFMC_NOR_SRAM_BLOCK(BLOCK)   (((BLOCK) == XFMC_BANK1_BLOCK1) || ((BLOCK) == XFMC_BANK1_BLOCK2))
#define IS_XFMC_NAND_BANK(BANK)         (((BANK) == XFMC_BANK2) || ((BANK) == XFMC_BANK3))


/** @addtogroup NOR_SRAM_Controller
 * @{
 */

/** @addtogroup XFMC_Data_Address_Bus_Multiplexing
 * @{
 */
#define XFMC_NOR_SRAM_DISABLE           ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_ENABLE            (XFMC_BANK1_CR_MBEN)
/**
 * @}
 */

/** @addtogroup XFMC_Data_Address_Bus_Multiplexing
 * @{
 */
#define XFMC_NOR_SRAM_MUX_DISABLE       ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_MUX_ENABLE        (XFMC_BANK1_CR_MUXEN)
#define IS_XFMC_NOR_SRAM_MUX(MUX)       (((MUX) == XFMC_NOR_SRAM_MUX_DISABLE) || ((MUX) == XFMC_NOR_SRAM_MUX_ENABLE))
/**
 * @}
 */

/** @addtogroup XFMC_Memory_Type
 * @{
 */
#define XFMC_MEM_TYPE_SRAM              ((uint32_t)0x00000000)
#define XFMC_MEM_TYPE_PSRAM             (XFMC_BANK1_CR_MTYPE_0)
#define XFMC_MEM_TYPE_NOR               (XFMC_BANK1_CR_MTYPE_1)
#define IS_XFMC_NOR_SRAM_MEMORY(MEMORY)                                                                                         \
    (((MEMORY) == XFMC_MEM_TYPE_SRAM) || ((MEMORY) == XFMC_MEM_TYPE_PSRAM) || ((MEMORY) == XFMC_MEM_TYPE_NOR))
/**
 * @}
 */

/** @addtogroup XFMC_Data_Width
 * @{
 */
#define XFMC_NOR_SRAM_DATA_WIDTH_8B     ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_DATA_WIDTH_16B    (XFMC_BANK1_CR_MDBW_0)
#define IS_XFMC_NOR_SRAM_MEMORY_WIDTH(WIDTH)     (((WIDTH) == XFMC_NOR_SRAM_DATA_WIDTH_8B) || ((WIDTH) == XFMC_NOR_SRAM_DATA_WIDTH_16B))
/**
 * @}
 */

/** @addtogroup XFMC_Flash_Access_Enable
 * @{
 */
#define XFMC_NOR_SRAM_ACC_DISABLE       ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_ACC_ENABLE        (XFMC_BANK1_CR_ACCEN)
/**
 * @}
 */

/** @addtogroup XFMC_Burst_Access_Mode
 * @{
 */
#define XFMC_NOR_SRAM_BURST_MODE_DISABLE    ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_BURST_MODE_ENABLE     (XFMC_BANK1_CR_BURSTEN)
#define IS_XFMC_NOR_SRAM_BURSTMODE(STATE)   (((STATE) == XFMC_NOR_SRAM_BURST_MODE_DISABLE) || ((STATE) == XFMC_NOR_SRAM_BURST_MODE_ENABLE))
/**
 * @}
 */

/** @addtogroup XFMC_Wait_Signal_Polarity
 * @{
 */
#define XFMC_NOR_SRAM_WAIT_SIGNAL_LOW   ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_WAIT_SIGNAL_HIGH  (XFMC_BANK1_CR_WAITDIR)
#define IS_XFMC_NOR_SRAM_WAIT_POLARITY(POLARITY)                                                                                \
    (((POLARITY) == XFMC_NOR_SRAM_WAIT_SIGNAL_LOW) || ((POLARITY) == XFMC_NOR_SRAM_WAIT_SIGNAL_HIGH))
/**
 * @}
 */

/** @addtogroup XFMC_Wrap_Mode
 * @{
 */
#define XFMC_NOR_SRAM_WRAP_DISABLE          ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_WRAP_ENABLE           (XFMC_BANK1_CR_WRAPEN)
#define IS_XFMC_NOR_SRAM_WRAP_MODE(MODE)    (((MODE) == XFMC_NOR_SRAM_WRAP_DISABLE) || ((MODE) == XFMC_NOR_SRAM_WRAP_ENABLE))
/**
 * @}
 */

/** @addtogroup XFMC_Wait_Timing
 * @{
 */
#define XFMC_NOR_SRAM_NWAIT_BEFORE_STATE    ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_NWAIT_DURING_STATE    (XFMC_BANK1_CR_WCFG)
#define IS_XFMC_NOR_SRAM_WAIT_SIGNAL_ACTIVE(ACTIVE)                                                                             \
    (((ACTIVE) == XFMC_NOR_SRAM_NWAIT_BEFORE_STATE) || ((ACTIVE) == XFMC_NOR_SRAM_NWAIT_DURING_STATE))
/**
 * @}
 */

/** @addtogroup XFMC_Write_Operation
 * @{
 */
#define XFMC_NOR_SRAM_WRITE_DISABLE                 ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_WRITE_ENABLE                  (XFMC_BANK1_CR_WREN)
#define IS_XFMC_NOR_SRAM_WRITE_OPERATION(OPERATION) (((OPERATION) == XFMC_NOR_SRAM_WRITE_DISABLE) || ((OPERATION) == XFMC_NOR_SRAM_WRITE_ENABLE))
/**
 * @}
 */

/** @addtogroup XFMC_Wait_Signal
 * @{
 */
#define XFMC_NOR_SRAM_NWAIT_DISABLE             ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_NWAIT_ENABLE              (XFMC_BANK1_CR_WAITEN)
#define IS_XFMC_NOR_SRAM_WAITE_SIGNAL(SIGNAL)   (((SIGNAL) == XFMC_NOR_SRAM_NWAIT_DISABLE) || ((SIGNAL) == XFMC_NOR_SRAM_NWAIT_ENABLE))
/**
 * @}
 */

/** @addtogroup XFMC_Extended_Mode
 * @{
 */
#define XFMC_NOR_SRAM_EXTENDED_DISABLE          ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_EXTENDED_ENABLE           (XFMC_BANK1_CR_EXTEN)
#define IS_XFMC_NOR_SRAM_EXTENDED_MODE(MODE)    (((MODE) == XFMC_NOR_SRAM_EXTENDED_DISABLE) || ((MODE) == XFMC_NOR_SRAM_EXTENDED_ENABLE))
/**
 * @}
 */

/** @addtogroup AsynchroWait
 * @{
 */
#define XFMC_NOR_SRAM_ASYNC_NWAIT_DISABLE   ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_ASYNC_NWAIT_ENABLE    (XFMC_BANK1_CR_WAITASYNC)
#define IS_XFMC_NOR_SRAM_ASYNWAIT(STATE)     (((STATE) == XFMC_NOR_SRAM_ASYNC_NWAIT_DISABLE) || ((STATE) == XFMC_NOR_SRAM_ASYNC_NWAIT_ENABLE))
/**
 * @}
 */


/** @addtogroup XFMC_Write_Burst
 * @{
 */
#define XFMC_NOR_SRAM_BURST_WRITE_DISABLE   ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_BURST_WRITE_ENABLE    (XFMC_BANK1_CR_BURSTWREN)
#define IS_XFMC_NOR_SRAM_WRITE_BURST(BURST) (((BURST) == XFMC_NOR_SRAM_BURST_WRITE_DISABLE) || ((BURST) == XFMC_NOR_SRAM_BURST_WRITE_ENABLE))
/**
 * @}
 */

/**
 * @} End of NOR_SRAM_Controller
 */


/** @addtogroup NOR_SRAM_Time_Control
 * @{
 */

/** @addtogroup XFMC_Address_Setup_Time
 * @{
 */
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_1HCLK         (0x0UL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_2HCLK         (0x1UL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_3HCLK         (0x2UL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_4HCLK         (0x3UL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_5HCLK         (0x4UL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_6HCLK         (0x5UL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_7HCLK         (0x6UL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_8HCLK         (0x7UL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_9HCLK         (0x8UL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_10HCLK        (0x9UL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_11HCLK        (0xAUL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_12HCLK        (0xBUL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_13HCLK        (0xCUL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_14HCLK        (0xDUL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_15HCLK        (0xEUL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_SETUP_TIME_16HCLK        (0xFUL << XFMC_BANK1_TR_ADDBLD_SHIFT)
#define IS_XFMC_NOR_SRAM_ADDR_SETUP_TIME(TIME)      (0==((TIME) & (~XFMC_BANK1_TR_ADDBLD_MASK)))
/**
 * @}
 */

/** @addtogroup XFMC_Address_Hold_Time
 * @{
 */
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_1HCLK          (0x0UL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_2HCLK          (0x1UL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_3HCLK          (0x2UL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_4HCLK          (0x3UL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_5HCLK          (0x4UL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_6HCLK          (0x5UL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_7HCLK          (0x6UL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_8HCLK          (0x7UL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_9HCLK          (0x8UL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_10HCLK         (0x9UL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_11HCLK         (0xAUL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_12HCLK         (0xBUL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_13HCLK         (0xCUL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_14HCLK         (0xDUL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_15HCLK         (0xEUL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define XFMC_NOR_SRAM_ADDR_HOLD_TIME_16HCLK         (0xFUL << XFMC_BANK1_TR_ADDHLD_SHIFT)
#define IS_XFMC_NOR_SRAM_ADDR_HOLD_TIME(TIME)       (0==((TIME) & (~XFMC_BANK1_TR_ADDHLD_MASK)))
/**
 * @}
 */

/** @addtogroup XFMC_Data_Setup_Time
 * @{
 */
#define XFMC_NOR_SRAM_DATA_SETUP_TIME_MIN           (0x01UL << XFMC_BANK1_TR_DATABLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_SETUP_TIME_MAX           (0xFFUL << XFMC_BANK1_TR_DATABLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_SETUP_TIME(x)            ((x) << XFMC_BANK1_TR_DATABLD_SHIFT)
#define IS_XFMC_NOR_SRAM_DATASETUP_TIME(TIME)       ( ((TIME) >= XFMC_NOR_SRAM_DATA_SETUP_TIME_MIN)    \
                                                  &&  ((TIME) <= XFMC_NOR_SRAM_DATA_SETUP_TIME_MAX) )
/**
 * @}
 */

/** @addtogroup XFMC_Bus_Recovery_Time
 * @{
 */
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_1HCLK        (0x0UL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_2HCLK        (0x1UL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_3HCLK        (0x2UL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_4HCLK        (0x3UL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_5HCLK        (0x4UL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_6HCLK        (0x5UL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_7HCLK        (0x6UL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_8HCLK        (0x7UL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_9HCLK        (0x8UL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_10HCLK       (0x9UL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_11HCLK       (0xAUL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_12HCLK       (0xBUL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_13HCLK       (0xCUL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_14HCLK       (0xDUL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_15HCLK       (0xEUL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define XFMC_NOR_SRAM_BUSRECOVERY_TIME_16HCLK       (0xFUL << XFMC_BANK1_TR_BUSRECOVERY_SHIFT)
#define IS_XFMC_NOR_SRAM_BUSRECOVERY_TIME(TIME)     (0==((TIME) & (~XFMC_BANK1_TR_BUSRECOVERY_MASK)))
/**
 * @}
 */

/** @addtogroup XFMC_CLK_Division
 * @{
 */
#define XFMC_NOR_SRAM_CLK_DIV_2             (0x1UL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_3             (0x2UL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_4             (0x3UL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_5             (0x4UL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_6             (0x5UL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_7             (0x6UL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_8             (0x7UL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_9             (0x8UL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_10            (0x9UL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_11            (0xAUL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_12            (0xBUL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_13            (0xCUL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_14            (0xDUL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_15            (0xEUL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define XFMC_NOR_SRAM_CLK_DIV_16            (0xFUL << XFMC_BANK1_TR_CLKDIV_SHIFT)
#define IS_XFMC_NOR_SRAM_CLK_DIV(DIV)       ( ((DIV) >= XFMC_NOR_SRAM_CLK_DIV_2)    \
                                            && ((DIV) <= XFMC_NOR_SRAM_CLK_DIV_16) )
/**
 * @}
 */

/** @addtogroup XFMC_Data_Latency
 * @{
 */
#define XFMC_NOR_SRAM_DATA_LATENCY_2CLK         (0x0UL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_3CLK         (0x1UL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_4CLK         (0x2UL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_5CLK         (0x3UL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_6CLK         (0x4UL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_7CLK         (0x5UL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_8CLK         (0x6UL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_9CLK         (0x7UL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_10CLK        (0x8UL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_11CLK        (0x9UL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_12CLK        (0xAUL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_13CLK        (0xBUL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_14CLK        (0xCUL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_15CLK        (0xDUL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_16CLK        (0xEUL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define XFMC_NOR_SRAM_DATA_LATENCY_17CLK        (0xFUL << XFMC_BANK1_TR_DATAHLD_SHIFT)
#define IS_XFMC_NOR_SRAM_DATA_LATENCY(TIME)     (0==((TIME) & (~XFMC_BANK1_TR_DATAHLD_MASK)))
/**
 * @}
 */

/** @addtogroup XFMC_Access_Mode
 * @{
 */
#define XFMC_NOR_SRAM_ACC_MODE_A     ((uint32_t)0x00000000)
#define XFMC_NOR_SRAM_ACC_MODE_B     (0x1UL << XFMC_BANK1_TR_ACCMODE_SHIFT)
#define XFMC_NOR_SRAM_ACC_MODE_C     (0x2UL << XFMC_BANK1_TR_ACCMODE_SHIFT)
#define XFMC_NOR_SRAM_ACC_MODE_D     (0x3UL << XFMC_BANK1_TR_ACCMODE_SHIFT)
#define IS_XFMC_NOR_SRAM_ACCESS_MODE(MODE)    ( ((MODE) == XFMC_NOR_SRAM_ACC_MODE_A) || ((MODE) == XFMC_NOR_SRAM_ACC_MODE_B)    \
                                             || ((MODE) == XFMC_NOR_SRAM_ACC_MODE_C) || ((MODE) == XFMC_NOR_SRAM_ACC_MODE_D) )
/**
 * @} End of NOR_SRAM_Time_Control
 */

/**
 * @}
 */

/** @addtogroup NAND_Controller
 * @{
 */

/** @addtogroup XFMC_Wait_feature
 * @{
 */
#define XFMC_NAND_NWAIT_DISABLE     ((uint32_t)0x00000000)
#define XFMC_NAND_NWAIT_ENABLE      (XFMC_CTRL_WAITEN)
#define IS_XFMC_NAND_WAIT_FEATURE(FEATURE)                                                                                  \
    (((FEATURE) == XFMC_NAND_NWAIT_DISABLE) || ((FEATURE) == XFMC_NAND_NWAIT_ENABLE))
/**
 * @}
 */

/** @addtogroup XFMC_Nand_Enable
 * @{
 */
#define XFMC_NAND_BANK_DISABLE      ((uint32_t)0x00000000)
#define XFMC_NAND_BANK_ENABLE       (XFMC_CTRL_BANKEN)
/**
 * @}
 */

/** @addtogroup XFMC_Bank23_Memory_Type
 * @{
 */
#define XFMC_BANK23_MEM_TYPE_NAND       (XFMC_CTRL_MEMTYPE)
#define IS_XFMC_BANK23_MEM_TYPE(TYPE)   ((TYPE) == XFMC_BANK23_MEM_TYPE_NAND)
/**
 * @}
 */

/** @addtogroup XFMC_Wait_feature
 * @{
 */
#define XFMC_NAND_BUS_WIDTH_8B      ((uint32_t)0x00000000)
#define XFMC_NAND_BUS_WIDTH_16B     (XFMC_CTRL_BUSWID_0)
#define IS_XFMC_NAND_BUS_WIDTH(WIDTH)    (((WIDTH) == XFMC_NAND_BUS_WIDTH_8B)||((WIDTH) == XFMC_NAND_BUS_WIDTH_16B))
/**
 * @}
 */

/** @addtogroup XFMC_Ecc
 * @{
 */
#define XFMC_NAND_ECC_DISABLE       ((uint32_t)0x00000000)
#define XFMC_NAND_ECC_ENABLE        (XFMC_CTRL_ECCEN)
#define IS_XFMC_ECC_STATE(STATE)    (((STATE) == XFMC_NAND_ECC_DISABLE) || ((STATE) == XFMC_NAND_ECC_ENABLE))
/**
 * @}
 */

/** @addtogroup XFMC_CLE_RE_Delay
 * @{
 */
#define XFMC_NAND_CLE_DELAY_1HCLK       (0x0UL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_2HCLK       (0x1UL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_3HCLK       (0x2UL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_4HCLK       (0x3UL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_5HCLK       (0x4UL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_6HCLK       (0x5UL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_7HCLK       (0x6UL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_8HCLK       (0x7UL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_9HCLK       (0x8UL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_10HCLK      (0x9UL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_11HCLK      (0xAUL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_12HCLK      (0xBUL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_13HCLK      (0xCUL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_14HCLK      (0xDUL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_15HCLK      (0xEUL << XFMC_CTRL_CRDLY_SHIFT)
#define XFMC_NAND_CLE_DELAY_16HCLK      (0xFUL << XFMC_CTRL_CRDLY_SHIFT)
#define IS_XFMC_NAND_CLE_DELAY(DELAY)   (0==((DELAY) & (~XFMC_CTRL_CRDLY_MASK)))
/**
 * @}
 */

/** @addtogroup XFMC_ALE_RE_Delay
 * @{
 */
#define XFMC_NAND_ALE_DELAY_1HCLK       (0x0UL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_2HCLK       (0x1UL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_3HCLK       (0x2UL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_4HCLK       (0x3UL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_5HCLK       (0x4UL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_6HCLK       (0x5UL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_7HCLK       (0x6UL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_8HCLK       (0x7UL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_9HCLK       (0x8UL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_10HCLK      (0x9UL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_11HCLK      (0xAUL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_12HCLK      (0xBUL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_13HCLK      (0xCUL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_14HCLK      (0xDUL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_15HCLK      (0xEUL << XFMC_CTRL_ARDLY_SHIFT)
#define XFMC_NAND_ALE_DELAY_16HCLK      (0xFUL << XFMC_CTRL_ARDLY_SHIFT)
#define IS_XFMC_NAND_ALE_DELAY(DELAY)   (0==((DELAY) & (~XFMC_CTRL_ARDLY_MASK)))
/**
 * @}
 */

/** @addtogroup XFMC_ECC_Page_Size
 * @{
 */
#define XFMC_NAND_ECC_PAGE_256BYTES         (0x0UL << XFMC_CTRL_ECCPGS_SHIFT)
#define XFMC_NAND_ECC_PAGE_512BYTES         (0x1UL << XFMC_CTRL_ECCPGS_SHIFT)
#define XFMC_NAND_ECC_PAGE_1024BYTES        (0x2UL << XFMC_CTRL_ECCPGS_SHIFT)
#define XFMC_NAND_ECC_PAGE_2048BYTES        (0x3UL << XFMC_CTRL_ECCPGS_SHIFT)
#define XFMC_NAND_ECC_PAGE_4096BYTES        (0x4UL << XFMC_CTRL_ECCPGS_SHIFT)
#define XFMC_NAND_ECC_PAGE_8192BYTES        (0x5UL << XFMC_CTRL_ECCPGS_SHIFT)
#define IS_XFMC_NAND_ECC_PAGE_SIZE(SIZE)    (0==((SIZE) & (~XFMC_CTRL_ECCPGS_MASK)))
/**
 * @}
 */

/**
 * @} End of NAND_Controller
 */

/** @addtogroup XFMC_StatusFlag
 * @{
 */
#define XFMC_NAND_FLAG_FIFO_EMPTY       (XFMC_STS_FIFOEMPT)
#define IS_XFMC_NAND_FLAG(FLAG)         ((FLAG)==XFMC_NAND_FLAG_FIFO_EMPTY)
/**
 * @}
 */


/** @addtogroup XFMC_TimeController
 * @{
 */

/** @addtogroup XFMC_Setup_Time
 * @{
 */
#define XFMC_NAND_SETUP_TIME_MIN        (0x00000000)
#define XFMC_NAND_SETUP_TIME_MAX        (0x000000FF)
#define XFMC_NAND_SETUP_TIME_DEFAULT    (0x000000FC)
#define IS_XFMC_NAND_SETUP_TIME(TIME)   ((TIME) <= XFMC_NAND_SETUP_TIME_MAX)
/**
 * @}
 */

/** @addtogroup XFMC_Wait_Time
 * @{
 */
#define XFMC_NAND_WAIT_TIME_MIN         (0x00000001)
#define XFMC_NAND_WAIT_TIME_MAX         (0x000000FF)
#define XFMC_NAND_WAIT_TIME_DEFAULT     (0x000000FC)
#define IS_XFMC_NAND_WAIT_TIME(TIME)    ( ((TIME) >= XFMC_NAND_WAIT_TIME_MIN)    \
                                    &&  ((TIME) <= XFMC_NAND_WAIT_TIME_MAX) )
/**
 * @}
 */

/** @addtogroup XFMC_Hold_Time
 * @{
 */
#define XFMC_NAND_HOLD_TIME_MIN         (0x00000001)
#define XFMC_NAND_HOLD_TIME_MAX         (0x000000FF)
#define XFMC_NAND_HOLD_TIME_DEFAULT     (0x000000FC)
#define IS_XFMC_NAND_HOLD_TIME(TIME)    ( ((TIME) >= XFMC_NAND_HOLD_TIME_MIN)    \
                                    &&  ((TIME) <= XFMC_NAND_HOLD_TIME_MAX) )
/**
 * @}
 */

/** @addtogroup XFMC_HiZ_Time
 * @{
 */
#define XFMC_NAND_HIZ_TIME_MIN          (0x00000000)
#define XFMC_NAND_HIZ_TIME_MAX          (0x000000FF)
#define XFMC_NAND_HIZ_TIME_DEFAULT      (0x000000FC)
#define IS_XFMC_NAND_HIZ_TIME(TIME)     ((TIME) <= XFMC_NAND_HIZ_TIME_MAX)
/**
 * @}
 */

/**
 * @} End of XFMC_TimeController
 */

/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup XFMC_Exported_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup XFMC_Exported_Functions
 * @{
 */

void XFMC_DeInitNorSram(XFMC_Bank1_Block *Block);
void XFMC_DeInitNand(XFMC_Bank23_Module *Bank);
void XFMC_InitNorSram(XFMC_NorSramInitTpye* XFMC_NORSRAMInitStruct);
void XFMC_InitNand(XFMC_NandInitType* XFMC_NANDInitStruct);
void XFMC_InitNorSramStruct(XFMC_NorSramInitTpye* XFMC_NORSRAMInitStruct);
void XFMC_InitNandStruct(XFMC_NandInitType* XFMC_NANDInitStruct);
void XFMC_EnableNorSram(XFMC_Bank1_Block *Block, FunctionalState Cmd);
void XFMC_EnableNand(XFMC_Bank23_Module *Bank, FunctionalState Cmd);
void XFMC_EnableNandEcc(XFMC_Bank23_Module *Bank, FunctionalState Cmd);
void XFMC_RestartNandEcc(XFMC_Bank23_Module *Bank);
uint32_t XFMC_GetEcc(XFMC_Bank23_Module *Bank);
FlagStatus XFMC_GetFlag(XFMC_Bank23_Module *Bank, uint32_t XFMC_FLAG);
void XFMC_ClrFlag(XFMC_Bank23_Module *Bank, uint32_t XFMC_FLAG);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*__N32G45X_XFMC_H__ */
/**
 * @}
 */

/**
 * @}
 */
