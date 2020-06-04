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
 * @author Nations Solution Team
 * @version v1.0.0
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
    uint32_t AddrSetTime; /*!< Defines the number of HCLK cycles to configure
                                         the duration of the address setup time.
                                         This parameter can be a value between 0 and 0xF.
                                         @note: It is not used with synchronous NOR Flash memories. */

    uint32_t AddrHoldTime; /*!< Defines the number of HCLK cycles to configure
                                        the duration of the address hold time.
                                        This parameter can be a value between 0 and 0xF.
                                        @note: It is not used with synchronous NOR Flash memories.*/

    uint32_t
        DataSetTime; /*!< Defines the number of HCLK cycles to configure
                                 the duration of the data setup time.
                                 This parameter can be a value between 0 and 0xFF.
                                 @note: It is used for SRAMs, ROMs and asynchronous multiplexed NOR Flash memories. */

    uint32_t BusRecoveryCycle; /*!< Defines the number of HCLK cycles to configure
                                              the duration of the bus turnaround.
                                              This parameter can be a value between 0 and 0xF.
                                              @note: It is only used for multiplexed NOR Flash memories. */

    uint32_t
        ClkDiv; /*!< Defines the period of CLK clock output signal, expressed in number of HCLK cycles.
                               This parameter can be a value between 1 and 0xF.
                               @note: This parameter is not used for asynchronous NOR Flash, SRAM or ROM accesses. */

    uint32_t DataLatency; /*!< Defines the number of memory clock cycles to issue
                                    to the memory before getting the first data.
                                    The value of this parameter depends on the memory type as shown below:
                                     - It must be set to 0 in case of a CRAM
                                     - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                     - It may assume a value between 0 and 0xF in NOR Flash memories
                                       with synchronous burst mode enable */

    uint32_t AccMode; /*!< Specifies the asynchronous access mode.
                                   This parameter can be a value of @ref XFMC_Access_Mode */
} XFMC_NorSramTimingInitType;

/**
 * @brief  XFMC NOR/SRAM Init structure definition
 */

typedef struct
{
    uint32_t Bank; /*!< Specifies the NOR/SRAM memory bank that will be used.
                             This parameter can be a value of @ref XFMC_NORSRAM_Bank */

    uint32_t DataAddrMux; /*!< Specifies whether the address and data values are
                                       multiplexed on the databus or not.
                                       This parameter can be a value of @ref XFMC_Data_Address_Bus_Multiplexing */

    uint32_t MemType; /*!< Specifies the type of external memory attached to
                                   the corresponding memory bank.
                                   This parameter can be a value of @ref XFMC_Memory_Type */

    uint32_t MemDataWidth; /*!< Specifies the external memory device width.
                                        This parameter can be a value of @ref XFMC_Data_Width */

    uint32_t BurstAccMode; /*!< Enables or disables the burst access mode for Flash memory,
                                        valid only with synchronous burst Flash memories.
                                        This parameter can be a value of @ref XFMC_Burst_Access_Mode */

    uint32_t AsynchroWait; /*!< Enables or disables wait signal during asynchronous transfers,
                                        valid only with asynchronous Flash memories.
                                        This parameter can be a value of @ref AsynchroWait */

    uint32_t WaitSigPolarity; /*!< Specifies the wait signal polarity, valid only when accessing
                                           the Flash memory in burst mode.
                                           This parameter can be a value of @ref XFMC_Wait_Signal_Polarity */

    uint32_t WrapMode; /*!< Enables or disables the Wrapped burst access mode for Flash
                                 memory, valid only when accessing Flash memories in burst mode.
                                 This parameter can be a value of @ref XFMC_Wrap_Mode */

    uint32_t WaitSigConfig; /*!< Specifies if the wait signal is asserted by the memory one
                                         clock cycle before the wait state or during the wait state,
                                         valid only when accessing memories in burst mode.
                                         This parameter can be a value of @ref XFMC_Wait_Timing */

    uint32_t WriteEnable; /*!< Enables or disables the write operation in the selected bank by the XFMC.
                                       This parameter can be a value of @ref XFMC_Write_Operation */

    uint32_t WaitSigEnable; /*!< Enables or disables the wait-state insertion via wait
                                   signal, valid for Flash memory access in burst mode.
                                   This parameter can be a value of @ref XFMC_Wait_Signal */

    uint32_t ExtModeEnable; /*!< Enables or disables the extended mode.
                                     This parameter can be a value of @ref XFMC_Extended_Mode */

    uint32_t WriteBurstEnable; /*!< Enables or disables the write burst operation.
                                   This parameter can be a value of @ref XFMC_Write_Burst */

    XFMC_NorSramTimingInitType*
        RWTimingStruct; /*!< Timing Parameters for write and read access if the  ExtendedMode is not used*/

    XFMC_NorSramTimingInitType* WTimingStruct; /*!< Timing Parameters for write access if the  ExtendedMode is used*/
} XFMC_NorSramInitTpye;

/**
 * @brief  Timing parameters For XFMC NAND and PCCARD Banks
 */

typedef struct
{
    uint32_t SetTime; /*!< Defines the number of HCLK cycles to setup address before
                                  the command assertion for NAND-Flash read or write access
                                  to common/Attribute or I/O memory space (depending on
                                  the memory space timing to be configured).
                                  This parameter can be a value between 0 and 0xFF.*/

    uint32_t WaitSetTime; /*!< Defines the minimum number of HCLK cycles to assert the
                                      command for NAND-Flash read or write access to
                                      common/Attribute or I/O memory space (depending on the
                                      memory space timing to be configured).
                                      This parameter can be a number between 0x00 and 0xFF */

    uint32_t HoldSetTime; /*!< Defines the number of HCLK clock cycles to hold address
                                      (and data for write access) after the command deassertion
                                      for NAND-Flash read or write access to common/Attribute
                                      or I/O memory space (depending on the memory space timing
                                      to be configured).
                                      This parameter can be a number between 0x00 and 0xFF */

    uint32_t HiZSetTime; /*!< Defines the number of HCLK clock cycles during which the
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
    uint32_t Bank; /*!< Specifies the NAND memory bank that will be used.
                           This parameter can be a value of @ref XFMC_NAND_Bank */

    uint32_t WaitFeatureEnable; /*!< Enables or disables the Wait feature for the NAND Memory Bank.
                                    This parameter can be any value of @ref XFMC_Wait_feature */

    uint32_t MemDataWidth; /*!< Specifies the external memory device width.
                                        This parameter can be any value of @ref XFMC_Data_Width */

    uint32_t EccEnable; /*!< Enables or disables the ECC computation.
                            This parameter can be any value of @ref XFMC_Ecc */

    uint32_t EccPageSize; /*!< Defines the page size for the extended ECC.
                                    This parameter can be any value of @ref XFMC_ECC_Page_Size */

    uint32_t TCLRSetTime; /*!< Defines the number of HCLK cycles to configure the
                                      delay between CLE low and RE low.
                                      This parameter can be a value between 0 and 0xFF. */

    uint32_t TARSetTime; /*!< Defines the number of HCLK cycles to configure the
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

    uint32_t TCLRSetTime; /*!< Defines the number of HCLK cycles to configure the
                                      delay between CLE low and RE low.
                                      This parameter can be a value between 0 and 0xFF. */

    uint32_t TARSetTime; /*!< Defines the number of HCLK cycles to configure the
                                     delay between ALE low and RE low.
                                     This parameter can be a number between 0x0 and 0xFF */

    XFMC_NandTimingInitType* CommSpaceTimingStruct; /*!< XFMC Common Space Timing */

    XFMC_NandTimingInitType* AttrSpaceTimingStruct; /*!< XFMC Attribute Space Timing */

    XFMC_NandTimingInitType* XFMC_IOSpaceTimingStruct; /*!< XFMC IO Space Timing */
} XFMC_PCCARDInitType;

/**
 * @}
 */

/** @addtogroup XFMC_Exported_Constants
 * @{
 */

/** @addtogroup XFMC_NORSRAM_Bank
 * @{
 */
#define XFMC_BANK1_NORSRAM1 ((uint32_t)0x00000000)
#define XFMC_BANK1_NORSRAM2 ((uint32_t)0x00000002)
/**
 * @}
 */

/** @addtogroup XFMC_NAND_Bank
 * @{
 */
#define XFMC_BANK2_NAND ((uint32_t)0x00000010)
#define XFMC_BANK3_NAND ((uint32_t)0x00000100)
/**
 * @}
 */

#define IS_XFMC_NORSRAM_BANK(BANK) (((BANK) == XFMC_BANK1_NORSRAM1) || ((BANK) == XFMC_BANK1_NORSRAM2))

#define IS_XFMC_NAND_BANK(BANK) (((BANK) == XFMC_BANK2_NAND) || ((BANK) == XFMC_BANK3_NAND))

#define IS_XFMC_GETFLAG_BANK(BANK) (((BANK) == XFMC_BANK2_NAND) || ((BANK) == XFMC_BANK3_NAND))

#define IS_XFMC_IT_BANK(BANK) (((BANK) == XFMC_BANK2_NAND) || ((BANK) == XFMC_BANK3_NAND))

/** @addtogroup NOR_SRAM_Controller
 * @{
 */

/** @addtogroup XFMC_Data_Address_Bus_Multiplexing
 * @{
 */

#define XFMC_DATA_ADDR_MUX_DISABLE ((uint32_t)0x00000000)
#define XFMC_DATA_ADDR_MUX_ENABLE  ((uint32_t)0x00000002)
#define IS_XFMC_MUX(MUX)           (((MUX) == XFMC_DATA_ADDR_MUX_DISABLE) || ((MUX) == XFMC_DATA_ADDR_MUX_ENABLE))

/**
 * @}
 */

/** @addtogroup XFMC_Memory_Type
 * @{
 */

#define XFMC_MEM_TYPE_SRAM  ((uint32_t)0x00000000)
#define XFMC_MEM_TYPE_PSRAM ((uint32_t)0x00000004)
#define XFMC_MEM_TYPE_NOR   ((uint32_t)0x00000008)
#define IS_XFMC_MEMORY(MEMORY)                                                                                         \
    (((MEMORY) == XFMC_MEM_TYPE_SRAM) || ((MEMORY) == XFMC_MEM_TYPE_PSRAM) || ((MEMORY) == XFMC_MEM_TYPE_NOR))

/**
 * @}
 */

/** @addtogroup XFMC_Data_Width
 * @{
 */

#define XFMC_MEM_DATA_WIDTH_8B      ((uint32_t)0x00000000)
#define XFMC_MEM_DATA_WIDTH_16B     ((uint32_t)0x00000010)
#define IS_XFMC_MEMORY_WIDTH(WIDTH) (((WIDTH) == XFMC_MEM_DATA_WIDTH_8B) || ((WIDTH) == XFMC_MEM_DATA_WIDTH_16B))

/**
 * @}
 */

/** @addtogroup XFMC_Burst_Access_Mode
 * @{
 */

#define XFMC_BURST_ACC_MODE_DISABLE ((uint32_t)0x00000000)
#define XFMC_BURST_ACC_MODE_ENABLE  ((uint32_t)0x00000100)
#define IS_XFMC_BURSTMODE(STATE)    (((STATE) == XFMC_BURST_ACC_MODE_DISABLE) || ((STATE) == XFMC_BURST_ACC_MODE_ENABLE))
/**
 * @}
 */

/** @addtogroup AsynchroWait
 * @{
 */
#define XFMC_ASYNCHRO_WAIT_DISABLE ((uint32_t)0x00000000)
#define XFMC_ASYNCHRO_WAIT_ENABLE  ((uint32_t)0x00008000)
#define IS_XFMC_ASYNWAIT(STATE)    (((STATE) == XFMC_ASYNCHRO_WAIT_DISABLE) || ((STATE) == XFMC_ASYNCHRO_WAIT_ENABLE))

/**
 * @}
 */

/** @addtogroup XFMC_Wait_Signal_Polarity
 * @{
 */

#define XFMC_WAIT_SIGNAL_POLARITY_LOW  ((uint32_t)0x00000000)
#define XFMC_WAIT_SIGNAL_POLARITY_HIGH ((uint32_t)0x00000200)
#define IS_XFMC_WAIT_POLARITY(POLARITY)                                                                                \
    (((POLARITY) == XFMC_WAIT_SIGNAL_POLARITY_LOW) || ((POLARITY) == XFMC_WAIT_SIGNAL_POLARITY_HIGH))

/**
 * @}
 */

/** @addtogroup XFMC_Wrap_Mode
 * @{
 */

#define XFMC_WRAP_MODE_DISABLE  ((uint32_t)0x00000000)
#define XFMC_WRAP_MODE_ENABLE   ((uint32_t)0x00000400)
#define IS_XFMC_WRAP_MODE(MODE) (((MODE) == XFMC_WRAP_MODE_DISABLE) || ((MODE) == XFMC_WRAP_MODE_ENABLE))

/**
 * @}
 */

/** @addtogroup XFMC_Wait_Timing
 * @{
 */

#define XFMC_WAIT_SIG_ACTIVE_BEFORE_WAIT_STATE ((uint32_t)0x00000000)
#define XFMC_WAIT_SIG_ACTIVE_DURING_WAIT_STATE ((uint32_t)0x00000800)
#define IS_XFMC_WAIT_SIGNAL_ACTIVE(ACTIVE)                                                                             \
    (((ACTIVE) == XFMC_WAIT_SIG_ACTIVE_BEFORE_WAIT_STATE) || ((ACTIVE) == XFMC_WAIT_SIG_ACTIVE_DURING_WAIT_STATE))

/**
 * @}
 */

/** @addtogroup XFMC_Write_Operation
 * @{
 */

#define XFMC_WRITE_DISABLE                 ((uint32_t)0x00000000)
#define XFMC_WRITE_ENABLE                  ((uint32_t)0x00001000)
#define IS_XFMC_WRITE_OPERATION(OPERATION) (((OPERATION) == XFMC_WRITE_DISABLE) || ((OPERATION) == XFMC_WRITE_ENABLE))

/**
 * @}
 */

/** @addtogroup XFMC_Wait_Signal
 * @{
 */

#define XFMC_WAIT_SIGNAL_DISABLE     ((uint32_t)0x00000000)
#define XFMC_WAIT_SIGNAL_ENABLE      ((uint32_t)0x00002000)
#define IS_XFMC_WAITE_SIGNAL(SIGNAL) (((SIGNAL) == XFMC_WAIT_SIGNAL_DISABLE) || ((SIGNAL) == XFMC_WAIT_SIGNAL_ENABLE))
/**
 * @}
 */

/** @addtogroup XFMC_Extended_Mode
 * @{
 */

#define XFMC_EXTENDED_DISABLE ((uint32_t)0x00000000)
#define XFMC_EXTENDED_ENABLE  ((uint32_t)0x00004000)

#define IS_XFMC_EXTENDED_MODE(MODE) (((MODE) == XFMC_EXTENDED_DISABLE) || ((MODE) == XFMC_EXTENDED_ENABLE))

/**
 * @}
 */

/** @addtogroup XFMC_Write_Burst
 * @{
 */

#define XFMC_WRITE_BURST_DISABLE   ((uint32_t)0x00000000)
#define XFMC_WRITE_BURST_ENABLE    ((uint32_t)0x00080000)
#define IS_XFMC_WRITE_BURST(BURST) (((BURST) == XFMC_WRITE_BURST_DISABLE) || ((BURST) == XFMC_WRITE_BURST_ENABLE))
/**
 * @}
 */

/** @addtogroup XFMC_Address_Setup_Time
 * @{
 */

#define IS_XFMC_ADDRESS_SETUP_TIME(TIME) ((TIME) <= 0xF)

/**
 * @}
 */

/** @addtogroup XFMC_Address_Hold_Time
 * @{
 */

#define IS_XFMC_ADDRESS_HOLD_TIME(TIME) ((TIME) <= 0xF)

/**
 * @}
 */

/** @addtogroup XFMC_Data_Setup_Time
 * @{
 */

#define IS_XFMC_DATASETUP_TIME(TIME) (((TIME) > 0) && ((TIME) <= 0xFF))

/**
 * @}
 */

/** @addtogroup XFMC_Bus_Turn_around_Duration
 * @{
 */

#define IS_XFMC_TURNAROUND_TIME(TIME) ((TIME) <= 0xF)

/**
 * @}
 */

/** @addtogroup XFMC_CLK_Division
 * @{
 */

#define IS_XFMC_CLK_DIV(DIV) ((DIV) <= 0xF)

/**
 * @}
 */

/** @addtogroup XFMC_Data_Latency
 * @{
 */

#define IS_XFMC_DATA_LATENCY(LATENCY) ((LATENCY) <= 0xF)

/**
 * @}
 */

/** @addtogroup XFMC_Access_Mode
 * @{
 */

#define XFMC_ACC_MODE_A ((uint32_t)0x00000000)
#define XFMC_ACC_MODE_B ((uint32_t)0x10000000)
#define XFMC_ACC_MODE_C ((uint32_t)0x20000000)
#define XFMC_ACC_MODE_D ((uint32_t)0x30000000)
#define IS_XFMC_ACCESS_MODE(MODE)                                                                                      \
    (((MODE) == XFMC_ACC_MODE_A) || ((MODE) == XFMC_ACC_MODE_B) || ((MODE) == XFMC_ACC_MODE_C)                         \
     || ((MODE) == XFMC_ACC_MODE_D))

/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup NAND_PCCARD_Controller
 * @{
 */

/** @addtogroup XFMC_Wait_feature
 * @{
 */

#define XFMC_WAIT_FEATURE_DISABLE ((uint32_t)0x00000000)
#define XFMC_WAIT_FEATURE_ENABLE  ((uint32_t)0x00000002)
#define IS_XFMC_WAIT_FEATURE(FEATURE)                                                                                  \
    (((FEATURE) == XFMC_WAIT_FEATURE_DISABLE) || ((FEATURE) == XFMC_WAIT_FEATURE_ENABLE))

/**
 * @}
 */

/** @addtogroup XFMC_Ecc
 * @{
 */

#define XFMC_ECC_DISABLE         ((uint32_t)0x00000000)
#define XFMC_ECC_ENABLE          ((uint32_t)0x00000040)
#define IS_XFMC_ECC_STATE(STATE) (((STATE) == XFMC_ECC_DISABLE) || ((STATE) == XFMC_ECC_ENABLE))

/**
 * @}
 */

/** @addtogroup XFMC_ECC_Page_Size
 * @{
 */

#define XFMC_ECC_PAGE_SIZE_256BYTES  ((uint32_t)0x00000000)
#define XFMC_ECC_PAGE_SIZE_512BYTES  ((uint32_t)0x00020000)
#define XFMC_ECC_PAGE_SIZE_1024BYTES ((uint32_t)0x00040000)
#define XFMC_ECC_PAGE_SIZE_2048BYTES ((uint32_t)0x00060000)
#define XFMC_ECC_PAGE_SIZE_4096BYTES ((uint32_t)0x00080000)
#define XFMC_ECC_PAGE_SIZE_8192BYTES ((uint32_t)0x000A0000)
#define IS_XFMC_ECCPAGE_SIZE(SIZE)                                                                                     \
    (((SIZE) == XFMC_ECC_PAGE_SIZE_256BYTES) || ((SIZE) == XFMC_ECC_PAGE_SIZE_512BYTES)                                \
     || ((SIZE) == XFMC_ECC_PAGE_SIZE_1024BYTES) || ((SIZE) == XFMC_ECC_PAGE_SIZE_2048BYTES)                           \
     || ((SIZE) == XFMC_ECC_PAGE_SIZE_4096BYTES) || ((SIZE) == XFMC_ECC_PAGE_SIZE_8192BYTES))

/**
 * @}
 */

/** @addtogroup XFMC_TCLR_Setup_Time
 * @{
 */

#define IS_XFMC_TCLR_TIME(TIME) ((TIME) <= 0xFF)

/**
 * @}
 */

/** @addtogroup XFMC_TAR_Setup_Time
 * @{
 */

#define IS_XFMC_TAR_TIME(TIME) ((TIME) <= 0xFF)

/**
 * @}
 */

/** @addtogroup XFMC_Setup_Time
 * @{
 */

#define IS_XFMC_SETUP_TIME(TIME) ((TIME) <= 0xFF)

/**
 * @}
 */

/** @addtogroup XFMC_Wait_Setup_Time
 * @{
 */

#define IS_XFMC_WAIT_TIME(TIME) ((TIME) <= 0xFF)

/**
 * @}
 */

/** @addtogroup XFMC_Hold_Setup_Time
 * @{
 */

#define IS_XFMC_HOLD_TIME(TIME) ((TIME) <= 0xFF)

/**
 * @}
 */

/** @addtogroup XFMC_HiZ_Setup_Time
 * @{
 */

#define IS_XFMC_HIZ_TIME(TIME) ((TIME) <= 0xFF)

/**
 * @}
 */

/**
 * @}
 */

/** @addtogroup XFMC_Flags
 * @{
 */
#define XFMC_FLAG_FEMPT        ((uint32_t)0x00000040)
#define IS_XFMC_GET_FLAG(FLAG) ((FLAG == XFMC_FLAG_FEMPT))

#define IS_XFMC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFFF8) == 0x00000000) && ((FLAG) != 0x00000000))

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

void XFMC_DeInitNorSram(uint32_t Bank);
void XFMC_DeInitNand(uint32_t Bank);
void XFMC_PCCARDDeInit(void);
void XFMC_InitNorSram(XFMC_NorSramInitTpye* XFMC_NORSRAMInitStruct);
void XFMC_InitNand(XFMC_NandInitType* XFMC_NANDInitStruct);
void XFMC_PCCARDInit(XFMC_PCCARDInitType* XFMC_PCCARDInitStruct);
void XFMC_InitNorSramStruct(XFMC_NorSramInitTpye* XFMC_NORSRAMInitStruct);
void XFMC_InitNandStruct(XFMC_NandInitType* XFMC_NANDInitStruct);
// void XFMC_PCCARDStructInit(XFMC_PCCARDInitType* XFMC_PCCARDInitStruct);
void XFMC_EnableNorSram(uint32_t Bank, FunctionalState Cmd);
void XFMC_EnableNand(uint32_t Bank, FunctionalState Cmd);
// void XFMC_PCCARDCmd(FunctionalState Cmd);
void XFMC_EnableNandEcc(uint32_t Bank, FunctionalState Cmd);
uint32_t XFMC_GetEcc(uint32_t Bank);
FlagStatus XFMC_GetFlag(uint32_t Bank, uint32_t XFMC_FLAG);
void XFMC_ClrFlag(uint32_t Bank, uint32_t XFMC_FLAG);
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
