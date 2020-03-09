/**
 **************************************************************************
 * File Name    : at32f4xx_xmc.h
 * Description  : at32f4xx XMC header file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F4xx_XMC_H
#define __AT32F4xx_XMC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup XMC
  * @{
  */

/** @defgroup XMC_Exported_Types
  * @{
  */

/**
  * @brief  Timing parameters For NOR/SRAM Banks
  */

typedef struct
{
    uint32_t XMC_AdrOpTime;                 /*!< Defines the number of HCLK cycles to configure
                                                       the duration of the address setup time.
                                                       This parameter can be a value between 0 and 0xF.
                                                       @note: It is not used with synchronous NOR Flash memories. */

    uint32_t XMC_AdrHoldTime;               /*!< Defines the number of HCLK cycles to configure
                                                    the duration of the address hold time.
                                                    This parameter can be a value between 0 and 0xF.
                                                    @note: It is not used with synchronous NOR Flash memories.*/

    uint32_t XMC_DataOpTime;                /*!< Defines the number of HCLK cycles to configure
                                                   the duration of the data setup time.
                                                   This parameter can be a value between 0 and 0xFF.
                                                   @note: It is used for SRAMs, ROMs and asynchronous multiplexed NOR Flash memories. */

    uint32_t XMC_IntervalBetweenOP;         /*!< Defines the number of HCLK cycles to configure
                                                    the duration of the bus turnaround.
                                                    This parameter can be a value between 0 and 0xF.
                                                    @note: It is only used for multiplexed NOR Flash memories. */

    uint32_t XMC_CLKPsc;                    /*!< Defines the period of CLK clock output signal, expressed in number of HCLK cycles.
                                                     This parameter can be a value between 1 and 0xF.
                                                     @note: This parameter is not used for asynchronous NOR Flash, SRAM or ROM accesses. */

    uint32_t XMC_DataStableTime;            /*!< Defines the number of memory clock cycles to issue
                                             to the memory before getting the first data.
                                             The value of this parameter depends on the memory type as shown below:
                                              - It must be set to 0 in case of a CRAM
                                              - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                              - It may assume a value between 0 and 0xF in NOR Flash memories
                                                with synchronous burst mode enable */

    uint32_t XMC_Mode;                      /*!< Specifies the asynchronous access mode.
                                                      This parameter can be a value of @ref XMC_Access_Mode */
} XMC_NORSRAMTimingInitType;

/**
  * @brief  XMC NOR/SRAM Init structure definition
  */

typedef struct
{
    uint32_t XMC_Bank;                      /*!< Specifies the NOR/SRAM memory bank that will be used.
                                                 This parameter can be a value of @ref XMC_NORSRAM_Bank */

    uint32_t XMC_DataAdrMux;                /*!< Specifies whether the address and data values are
                                                 multiplexed on the databus or not.
                                                 This parameter can be a value of @ref XMC_Data_Address_Bus_Multiplexing */

    uint32_t XMC_Dev;                       /*!< Specifies the type of external memory attached to
                                                 the corresponding memory bank.
                                                 This parameter can be a value of @ref XMC_Memory_Type */

    uint32_t XMC_BusType;                   /*!< Specifies the external memory device width.
                                                        This parameter can be a value of @ref XMC_Data_Width */

    uint32_t XMC_EnableBurstMode;           /*!< Enables or disables the burst access mode for Flash memory,
                                                 valid only with synchronous burst Flash memories.
                                                 This parameter can be a value of @ref XMC_Burst_Access_Mode */

    uint32_t XMC_EnableAsynWait;            /*!< Enables or disables wait signal during asynchronous transfers,
                                                 valid only with asynchronous Flash memories.
                                                 This parameter can be a value of @ref XMC_EnableAsynWait */

    uint32_t XMC_WaitSignalLv;              /*!< Specifies the wait signal polarity, valid only when accessing
                                                 the Flash memory in burst mode.
                                                 This parameter can be a value of @ref XMC_Wait_Signal_Polarity */

    uint32_t XMC_EnableBurstModeSplit;      /*!< Enables or disables the Wrapped burst access mode for Flash
                                                 memory, valid only when accessing Flash memories in burst mode.
                                                 This parameter can be a value of @ref XMC_Wrap_Mode */

    uint32_t XMC_WaitSignalConfig;          /*!< Specifies if the wait signal is asserted by the memory one
                                                 clock cycle before the wait state or during the wait state,
                                                 valid only when accessing memories in burst mode.
                                                 This parameter can be a value of @ref XMC_Wait_Timing */

    uint32_t XMC_EnableWrite;               /*!< Enables or disables the write operation in the selected bank by the XMC.
                                                 This parameter can be a value of @ref XMC_Write_Operation */

    uint32_t XMC_EnableWaitSignal;          /*!< Enables or disables the wait-state insertion via wait
                                                 signal, valid for Flash memory access in burst mode.
                                                 This parameter can be a value of @ref XMC_Wait_Signal */

    uint32_t XMC_EnableWriteTiming;         /*!< Enables or disables the extended mode.
                                                 This parameter can be a value of @ref XMC_Extended_Mode */

    uint32_t XMC_WriteBurstSyn;             /*!< Enables or disables the write burst operation.
                                                 This parameter can be a value of @ref XMC_Write_Burst */

    XMC_NORSRAMTimingInitType* XMC_RWTimingStruct;  /*!< Timing Parameters for write and read access if the  ExtendedMode is not used*/

    XMC_NORSRAMTimingInitType* XMC_WTimingStruct;   /*!< Timing Parameters for write access if the  ExtendedMode is used*/
} XMC_NORSRAMInitType;

/**
  * @brief  Timing parameters For XMC NAND and PCCARD Banks
  */

typedef struct
{
    uint32_t XMC_SetupTime;                 /*!< Defines the number of HCLK cycles to setup address before
                                                 the command assertion for NAND-Flash read or write access
                                                 to common/Attribute or I/O memory space (depending on
                                                 the memory space timing to be configured).
                                                 This parameter can be a value between 0 and 0xFF.*/

    uint32_t XMC_OpTime;                    /*!< Defines the minimum number of HCLK cycles to assert the
                                                 command for NAND-Flash read or write access to
                                                 common/Attribute or I/O memory space (depending on the
                                                 memory space timing to be configured).
                                                 This parameter can be a number between 0x00 and 0xFF */

    uint32_t XMC_HoldTime;                  /*!< Defines the number of HCLK clock cycles to hold address
                                                 (and data for write access) after the command deassertion
                                                 for NAND-Flash read or write access to common/Attribute
                                                 or I/O memory space (depending on the memory space timing
                                                 to be configured).
                                                 This parameter can be a number between 0x00 and 0xFF */

    uint32_t XMC_WriteSetupTime;            /*!< Defines the number of HCLK clock cycles during which the
                                                 databus is kept in HiZ after the start of a NAND-Flash
                                                 write access to common/Attribute or I/O memory space (depending
                                                 on the memory space timing to be configured).
                                                 This parameter can be a number between 0x00 and 0xFF */
} XMC_NAND_PCCARDTimingInitType;

/**
  * @brief  XMC NAND Init structure definition
  */

typedef struct
{
    uint32_t XMC_Bank;                      /*!< Specifies the NAND memory bank that will be used.
                                                 This parameter can be a value of @ref XMC_NAND_Bank */

    uint32_t XMC_EnableWait;                /*!< Enables or disables the Wait feature for the NAND Memory Bank.
                                                 This parameter can be any value of @ref XMC_Wait_feature */

    uint32_t XMC_BusType;                   /*!< Specifies the external memory device width.
                                                 This parameter can be any value of @ref XMC_Data_Width */

    uint32_t XMC_EnableECC;                 /*!< Enables or disables the ECC computation.
                                                 This parameter can be any value of @ref XMC_EnableECC */

    uint32_t XMC_ECCPageSize;               /*!< Defines the page size for the extended ECC.
                                                 This parameter can be any value of @ref XMC_ECC_Page_Size */

    uint32_t XMC_DelayTimeCR;               /*!< Defines the number of HCLK cycles to configure the
                                                 delay between CLE low and RE low.
                                                 This parameter can be a value between 0 and 0xFF. */

    uint32_t XMC_DelayTimeAR;               /*!< Defines the number of HCLK cycles to configure the
                                                 delay between ALE low and RE low.
                                                 This parameter can be a number between 0x0 and 0xFF */

    XMC_NAND_PCCARDTimingInitType*  XMC_CommonSpaceTimingStruct;    /*!< XMC Common Space Timing */

    XMC_NAND_PCCARDTimingInitType*  XMC_AttributeSpaceTimingStruct; /*!< XMC Attribute Space Timing */
} XMC_NANDInitType;

/**
  * @brief  XMC PCCARD Init structure definition
  */

typedef struct
{
    uint32_t XMC_EnableWait;                /*!< Enables or disables the Wait feature for the Memory Bank.
                                                 This parameter can be any value of @ref XMC_Wait_feature */

    uint32_t XMC_DelayTimeCR;               /*!< Defines the number of HCLK cycles to configure the
                                                 delay between CLE low and RE low.
                                                 This parameter can be a value between 0 and 0xFF. */

    uint32_t XMC_DelayTimeAR;               /*!< Defines the number of HCLK cycles to configure the
                                                 delay between ALE low and RE low.
                                                 This parameter can be a number between 0x0 and 0xFF */


    XMC_NAND_PCCARDTimingInitType*  XMC_CommonSpaceTimingStruct; /*!< XMC Common Space Timing */

    XMC_NAND_PCCARDTimingInitType*  XMC_AttributeSpaceTimingStruct;  /*!< XMC Attribute Space Timing */

    XMC_NAND_PCCARDTimingInitType*  XMC_IOSpaceTimingStruct; /*!< XMC IO Space Timing */
} XMC_PCCARDInitType;

/**
  * @}
  */

/** @defgroup XMC_Exported_Constants
  * @{
  */

/** @defgroup XMC_NORSRAM_Bank
  * @{
  */
#define XMC_Bank1_NORSRAM1                  ((uint32_t)0x00000000)
#define XMC_Bank1_NORSRAM2                  ((uint32_t)0x00000002)
#define XMC_Bank1_NORSRAM3                  ((uint32_t)0x00000004)
#define XMC_Bank1_NORSRAM4                  ((uint32_t)0x00000006)
/**
  * @}
  */

/** @defgroup XMC_SubBank
  * @{
  */
#define XMC_SubBank1_NORSRAM1                  ((uint32_t)0x00000000)
#define XMC_SubBank1_NORSRAM2                  ((uint32_t)0x00000001)
#define XMC_SubBank1_NORSRAM3                  ((uint32_t)0x00000002)
#define XMC_SubBank1_NORSRAM4                  ((uint32_t)0x00000003)
/**
  * @}
  */


/** @defgroup XMC_NAND_Bank
  * @{
  */
#define XMC_Bank2_NAND                      ((uint32_t)0x00000010)
#define XMC_Bank3_NAND                      ((uint32_t)0x00000100)
/**
  * @}
  */

/** @defgroup XMC_PCCARD_Bank
  * @{
  */
#define XMC_Bank4_PCCARD                    ((uint32_t)0x00001000)
/**
  * @}
  */

#define IS_XMC_Sub_NORSRAM_REGION(REGION)       (((REGION) == XMC_SubBank1_NORSRAM1) || \
                                             ((REGION) == XMC_SubBank1_NORSRAM2) || \
                                             ((REGION) == XMC_SubBank1_NORSRAM3) || \
                                             ((REGION) == XMC_SubBank1_NORSRAM4))

#define IS_XMC_NORSRAM_REGION(REGION)       (((REGION) == XMC_Bank1_NORSRAM1) || \
                                             ((REGION) == XMC_Bank1_NORSRAM2) || \
                                             ((REGION) == XMC_Bank1_NORSRAM3) || \
                                             ((REGION) == XMC_Bank1_NORSRAM4))

#define IS_XMC_NAND_BANK(BANK)              (((BANK) == XMC_Bank2_NAND) || \
                                             ((BANK) == XMC_Bank3_NAND))

#define IS_XMC_GETFLAG_BANK(BANK)           (((BANK) == XMC_Bank2_NAND) || \
                                             ((BANK) == XMC_Bank3_NAND) || \
                                             ((BANK) == XMC_Bank4_PCCARD))

#define IS_XMC_INT_BANK(BANK)               (((BANK) == XMC_Bank2_NAND) || \
                                             ((BANK) == XMC_Bank3_NAND) || \
                                             ((BANK) == XMC_Bank4_PCCARD))

/** @defgroup NOR_SRAM_Controller
  * @{
  */

/** @defgroup XMC_Data_Address_Bus_Multiplexing
  * @{
  */

#define XMC_DataAdrMux_Disable              ((uint32_t)0x00000000)
#define XMC_DataAdrMux_Enable               ((uint32_t)0x00000002)
#define IS_XMC_MUX(MUX)                     (((MUX) == XMC_DataAdrMux_Disable) || \
                                             ((MUX) == XMC_DataAdrMux_Enable))

/**
  * @}
  */

/** @defgroup XMC_Memory_Type
  * @{
  */

#define XMC_Dev_SRAM                        ((uint32_t)0x00000000)
#define XMC_Dev_PSRAM                       ((uint32_t)0x00000004)
#define XMC_Dev_NOR                         ((uint32_t)0x00000008)
#define IS_XMC_DEVICE(DEVICE)               (((DEVICE) == XMC_Dev_SRAM) || \
                                             ((DEVICE) == XMC_Dev_PSRAM)|| \
                                             ((DEVICE) == XMC_Dev_NOR))

/**
  * @}
  */

/** @defgroup XMC_Data_Width
  * @{
  */

#define XMC_BusType_8b                      ((uint32_t)0x00000000)
#define XMC_BusType_16b                     ((uint32_t)0x00000010)
#define IS_XMC_BUS_TYPE(TYPE)               (((TYPE) == XMC_BusType_8b) || \
                                             ((TYPE) == XMC_BusType_16b))

/**
  * @}
  */

/** @defgroup XMC_Burst_Access_Mode
  * @{
  */

#define XMC_BurstMode_Disable               ((uint32_t)0x00000000)
#define XMC_BurstMode_Enable                ((uint32_t)0x00000100)
#define IS_XMC_BURSTMODE(STATE)             (((STATE) == XMC_BurstMode_Disable) || \
                                             ((STATE) == XMC_BurstMode_Enable))
/**
  * @}
  */

/** @defgroup XMC_AsynchronousWait
  * @{
  */
#define XMC_AsynWait_Disable                ((uint32_t)0x00000000)
#define XMC_AsynWait_Enable                 ((uint32_t)0x00008000)
#define IS_XMC_ASYNWAIT(STATE)              (((STATE) == XMC_AsynWait_Disable) || \
                                             ((STATE) == XMC_AsynWait_Enable))

/**
  * @}
  */

/** @defgroup XMC_Wait_Signal_Polarity
  * @{
  */

#define XMC_WaitSignalLv_Low                ((uint32_t)0x00000000)
#define XMC_WaitSignalLv_High               ((uint32_t)0x00000200)
#define IS_XMC_WAIT_SIGNAL_LEVEL(LEVEL)     (((LEVEL) == XMC_WaitSignalLv_Low) || \
                                             ((LEVEL) == XMC_WaitSignalLv_High))

/**
  * @}
  */

/** @defgroup XMC_Wrap_Mode
  * @{
  */

#define XMC_BurstModeSplit_Disable          ((uint32_t)0x00000000)
#define XMC_BurstModeSplit_Enable           ((uint32_t)0x00000400)
#define IS_XMC_BURSTMODE_SPLIT(MODE)        (((MODE) == XMC_BurstModeSplit_Disable) || \
                                             ((MODE) == XMC_BurstModeSplit_Enable))

/**
  * @}
  */

/** @defgroup XMC_Wait_Timing
  * @{
  */

#define XMC_WaitSignalConfig_BeforeWaitState        ((uint32_t)0x00000000)
#define XMC_WaitSignalConfig_DuringWaitState        ((uint32_t)0x00000800)
#define IS_XMC_WAIT_SIGNAL_CONFIG(CONFIG)           (((CONFIG) == XMC_WaitSignalConfig_BeforeWaitState) || \
                                                     ((CONFIG) == XMC_WaitSignalConfig_DuringWaitState))

/**
  * @}
  */

/** @defgroup XMC_Write_Operation
  * @{
  */

#define XMC_WriteOperation_Disable          ((uint32_t)0x00000000)
#define XMC_WriteOperation_Enable           ((uint32_t)0x00001000)
#define IS_XMC_WRITE_OPERATION(OPERATION)   (((OPERATION) == XMC_WriteOperation_Disable) || \
                                             ((OPERATION) == XMC_WriteOperation_Enable))

/**
  * @}
  */

/** @defgroup XMC_Wait_Signal
  * @{
  */

#define XMC_WaitSignal_Disable              ((uint32_t)0x00000000)
#define XMC_WaitSignal_Enable               ((uint32_t)0x00002000)
#define IS_XMC_WAIT_SIGNAL(SIGNAL)          (((SIGNAL) == XMC_WaitSignal_Disable) || \
                                             ((SIGNAL) == XMC_WaitSignal_Enable))
/**
  * @}
  */

/** @defgroup XMC_Extended_Mode
  * @{
  */

#define XMC_WriteTiming_Disable             ((uint32_t)0x00000000)
#define XMC_WriteTiming_Enable              ((uint32_t)0x00004000)

#define IS_XMC_WRITE_TIMING(STATE)          (((STATE) == XMC_WriteTiming_Disable) || \
                                             ((STATE) == XMC_WriteTiming_Enable))

/**
  * @}
  */

/** @defgroup XMC_Write_Burst
  * @{
  */

#define XMC_WriteBurstSyn_Disable           ((uint32_t)0x00000000)
#define XMC_WriteBurstSyn_Enable            ((uint32_t)0x00080000)
#define IS_XMC_WRITE_BURST_SYN(SYN)         (((SYN) == XMC_WriteBurstSyn_Disable) || \
                                             ((SYN) == XMC_WriteBurstSyn_Enable))
/**
  * @}
  */

/** @defgroup XMC_Address_Setup_Time
  * @{
  */

#define IS_XMC_ADDRESS_OP_TIME(TIME)        ((TIME) <= 0xF)

/**
  * @}
  */

/** @defgroup XMC_Address_Hold_Time
  * @{
  */

#define IS_XMC_ADDRESS_HOLD_TIME(TIME)      ((TIME) <= 0xF)

/**
  * @}
  */

/** @defgroup XMC_Data_Setup_Time
  * @{
  */

#define IS_XMC_DATA_OP_TIME(TIME)           (((TIME) > 0) && ((TIME) <= 0xFF))

/**
  * @}
  */

/** @defgroup XMC_Bus_Turn_around_Duration
  * @{
  */

#define IS_XMC_INTERVAL_BETWEEN_OP_TIME(TIME)       ((TIME) <= 0xF)

/**
  * @}
  */

/** @defgroup XMC_CLK_Division
  * @{
  */

#define IS_XMC_CLK_DIV(DIV)                 ((DIV) <= 0xF)

/**
  * @}
  */

/** @defgroup XMC_Data_Latency
  * @{
  */

#define IS_XMC_DATA_STABLE_TIME(TIME)       ((TIME) <= 0xF)

/**
  * @}
  */

/** @defgroup XMC_Access_Mode
  * @{
  */

#define XMC_Mode_A                          ((uint32_t)0x00000000)
#define XMC_Mode_B                          ((uint32_t)0x10000000)
#define XMC_Mode_C                          ((uint32_t)0x20000000)
#define XMC_Mode_D                          ((uint32_t)0x30000000)
#define IS_XMC_MODE(MODE)                   (((MODE) == XMC_Mode_A) || \
                                             ((MODE) == XMC_Mode_B) || \
                                             ((MODE) == XMC_Mode_C) || \
                                             ((MODE) == XMC_Mode_D))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup NAND_PCCARD_Controller
  * @{
  */

/** @defgroup XMC_Wait_feature
  * @{
  */

#define XMC_WaitOperation_Disable           ((uint32_t)0x00000000)
#define XMC_WaitOperation_Enable            ((uint32_t)0x00000002)
#define IS_XMC_WAIT_OPERATION(OPERATION)    (((OPERATION) == XMC_WaitOperation_Disable) || \
                                             ((OPERATION) == XMC_WaitOperation_Enable))

/**
  * @}
  */


/** @defgroup XMC_EnableECC
  * @{
  */

#define XMC_ECCOperation_Disable            ((uint32_t)0x00000000)
#define XMC_ECCOperation_Enable             ((uint32_t)0x00000040)
#define IS_XMC_ECC_OPERATION(OPERATION)     (((OPERATION) == XMC_ECCOperation_Disable) || \
                                             ((OPERATION) == XMC_ECCOperation_Enable))

/**
  * @}
  */

/** @defgroup XMC_ECC_Page_Size
  * @{
  */

#define XMC_ECCPageSize_256Bytes            ((uint32_t)0x00000000)
#define XMC_ECCPageSize_512Bytes            ((uint32_t)0x00020000)
#define XMC_ECCPageSize_1024Bytes           ((uint32_t)0x00040000)
#define XMC_ECCPageSize_2048Bytes           ((uint32_t)0x00060000)
#define XMC_ECCPageSize_4096Bytes           ((uint32_t)0x00080000)
#define XMC_ECCPageSize_8192Bytes           ((uint32_t)0x000A0000)
#define IS_XMC_ECCPAGE_SIZE(SIZE)           (((SIZE) == XMC_ECCPageSize_256Bytes) || \
                                             ((SIZE) == XMC_ECCPageSize_512Bytes) || \
                                             ((SIZE) == XMC_ECCPageSize_1024Bytes) || \
                                             ((SIZE) == XMC_ECCPageSize_2048Bytes) || \
                                             ((SIZE) == XMC_ECCPageSize_4096Bytes) || \
                                             ((SIZE) == XMC_ECCPageSize_8192Bytes))

/**
  * @}
  */

/** @defgroup XMC_TCLR_Setup_Time
  * @{
  */

#define IS_XMC_DELAY_CR_TIME(TIME)          ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup XMC_TAR_Setup_Time
  * @{
  */

#define IS_XMC_DELAY_AR_TIME(TIME)          ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup XMC_Setup_Time
  * @{
  */

#define IS_XMC_SETUP_TIME(TIME)             ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup XMC_Wait_Setup_Time
  * @{
  */

#define IS_XMC_OP_TIME(TIME)                ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup XMC_Hold_Setup_Time
  * @{
  */

#define IS_XMC_HOLD_TIME(TIME)              ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup XMC_HiZ_Setup_Time
  * @{
  */

#define IS_XMC_WRITE_SETUP_TIME(TIME)       ((TIME) <= 0xFF)

/**
  * @}
  */

/** @defgroup XMC_Interrupt_sources
  * @{
  */

#define XMC_INT_RisingEdge                  ((uint32_t)0x00000008)
#define XMC_INT_Level                       ((uint32_t)0x00000010)
#define XMC_INT_FallingEdge                 ((uint32_t)0x00000020)
#define IS_XMC_INT(INT)                     ((((INT) & (uint32_t)0xFFFFFFC7) == 0x00000000) && ((INT) != 0x00000000))
#define IS_XMC_GET_INT(INT)                 (((INT) == XMC_INT_RisingEdge) || \
                                             ((INT) == XMC_INT_Level) || \
                                             ((INT) == XMC_INT_FallingEdge))
/**
  * @}
  */

/** @defgroup XMC_Flags
  * @{
  */

#define XMC_FLAG_RisingEdge                 ((uint32_t)0x00000001)
#define XMC_FLAG_Level                      ((uint32_t)0x00000002)
#define XMC_FLAG_FallingEdge                ((uint32_t)0x00000004)
#define XMC_FLAG_FEMPT                      ((uint32_t)0x00000040)
#define IS_XMC_GET_FLAG(FLAG)               (((FLAG) == XMC_FLAG_RisingEdge) || \
                                             ((FLAG) == XMC_FLAG_Level) || \
                                             ((FLAG) == XMC_FLAG_FallingEdge) || \
                                             ((FLAG) == XMC_FLAG_FEMPT))

#define IS_XMC_CLEAR_FLAG(FLAG)             ((((FLAG) & (uint32_t)0xFFFFFFF8) == 0x00000000) && ((FLAG) != 0x00000000))

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup XMC_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup XMC_Exported_Functions
  * @{
  */
  
void XMC_ExtTimingConfig(uint32_t XMC_SubBank, uint8_t W2W_Timing, uint8_t R2R_Timing);
void XMC_NORSRAMReset(uint32_t XMC_Bank);
void XMC_NANDReset(uint32_t XMC_Bank);
void XMC_PCCARDReset(void);
void XMC_NORSRAMInit(XMC_NORSRAMInitType* XMC_NORSRAMInitStruct);
void XMC_NANDInit(XMC_NANDInitType* XMC_NANDInitStruct);
void XMC_PCCARDInit(XMC_PCCARDInitType* XMC_PCCARDInitStruct);
void XMC_NORSRAMStructInit(XMC_NORSRAMInitType* XMC_NORSRAMInitStruct);
void XMC_NANDStructInit(XMC_NANDInitType* XMC_NANDInitStruct);
void XMC_PCCARDStructInit(XMC_PCCARDInitType* XMC_PCCARDInitStruct);
void XMC_NORSRAMCmd(uint32_t XMC_Bank, FunctionalState NewState);
void XMC_NANDCmd(uint32_t XMC_Bank, FunctionalState NewState);
void XMC_PCCARDCmd(FunctionalState NewState);
void XMC_NANDECCCmd(uint32_t XMC_Bank, FunctionalState NewState);
uint32_t XMC_GetECC(uint32_t XMC_Bank);
void XMC_INTConfig(uint32_t XMC_Bank, uint32_t XMC_INT, FunctionalState NewState);
FlagStatus XMC_GetFlagStatus(uint32_t XMC_Bank, uint32_t XMC_FLAG);
void XMC_ClearFlag(uint32_t XMC_Bank, uint32_t XMC_FLAG);
ITStatus XMC_GetINTStatus(uint32_t XMC_Bank, uint32_t XMC_INT);
void XMC_ClearINTPendingBit(uint32_t XMC_Bank, uint32_t XMC_INT);

#ifdef __cplusplus
}
#endif

#endif /*__AT32F4xx_XMC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


