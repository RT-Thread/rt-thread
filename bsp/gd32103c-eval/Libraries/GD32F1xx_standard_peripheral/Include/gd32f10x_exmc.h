/**
  ******************************************************************************
  * @brief   EXMC header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_EXMC_H
#define __GD32F10X_EXMC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup EXMC
  * @{
  */

/** @defgroup EXMC_Exported_Types
  * @{
  */

/**
  * @brief  Initial Timing Parameters For NOR/SRAM Banks
  */
typedef struct {
    uint32_t EXMC_AsynAccessMode;       /*!< The asynchronous access mode, detailed in @ref EXMC_AsynAccess_Mode*/
    uint32_t EXMC_SynDataLatency;       /*!< The number of CLK cycles to configure the data latency,
                                             which may assume a value between 0x0 and 0xF. */
    uint32_t EXMC_SynCLKDivision;       /*!< The number of  HCLK cycles to configure the clock divide ratio,
                                             which can be a value between 0x0 and 0xF. */
    uint32_t EXMC_BusLatency;           /*!< The number of HCLK cycles to configure the bus latency,
                                             which can be a value between 0x0 and 0xF. */
    uint32_t EXMC_AsynDataSetupTime;    /*!< The number of  HCLK cycles to configure the data setup time
                                             while in the asynchronous access mode, which can be a value
                                             between 0x00 and 0xFF. */
    uint32_t EXMC_AsynAddressHoldTime;  /*!< The number of  HCLK cycles to configure the address hold time
                                             while in the asynchronous access mode, which can be a value
                                             between 0x0 and 0xF. */
    uint32_t EXMC_AsynAddressSetupTime; /*!< The number of  HCLK cycles to configure the data setup time
                                             while in the asynchronous access mode, which can be a value
                                             between 0x0 and 0xF. */
} EXMC_NORSRAMTimingInitPara;

/**
  * @brief  EXMC NOR/SRAM Init structure definition
  */
typedef struct {
    uint32_t EXMC_NORSRAMBank;                                  /*!< The specified region of NORSRAM Bank1,
                                                                     choose one from @ref EXMC_NORSRAMBank. */
    uint32_t EXMC_WriteMode;                                    /*!< The write mode, details in @ref EXMC_WriteMode. */
    uint32_t EXMC_ExtendedMode;                                 /*!< Enable or Disable the extended mode, details in
                                                                     @ref EXMC_ExtendedMode. */
    uint32_t EXMC_AsynWait;                                     /*!< Enable or disable the asynchronous wait feature,detial
                                                                     in @ref EXMC_AsynWait. */
    uint32_t EXMC_NWAITSignal;                                  /*!< Enable or Disable the NWAIT signal while in synchronous
                                                                     bust mode, details in @ref EXMC_NWAITSignal. */
    uint32_t EXMC_MemoryWrite;                                  /*!< Enable or Disable the write operation, details in
                                                                     @ref EXMC_MemoryWrite. */
    uint32_t EXMC_NWAITConfig;                                  /*!< NWAIT signal configuration, details in @ref EXMC_NWAITConfig */
    uint32_t EXMC_WrapBurstMode;                                /*!< Enable or Disable the wrap burst mode, details in
                                                                     @ref EXMC_WrapBurstMode. */
    uint32_t EXMC_NWAITPolarity;                                /*!< Specifies the polarity of NWAIT signal from memory,
                                                                     details in @ref EXMC_NWAITPolarity. */
    uint32_t EXMC_BurstMode;                                    /*!< Enable or Disable the burst mode, details in
                                                                     @ref EXMC_BurstMode. */
    uint32_t EXMC_DatabusWidth;                                 /*!< Specifies the databus width of external memory,
                                                                     details in @ref EXMC_DatabusWidth. */
    uint32_t EXMC_MemoryType;                                   /*!< Specifies the type of external memory, details in
                                                                     @ref EXMC_MemoryType. */
    uint32_t EXMC_AddressDataMux;                               /*!< Specifies whether the data bus and address bus are multiplexed
                                                                     or not,details in @ref EXMC_AddressDataMux. */

    EXMC_NORSRAMTimingInitPara *EXMC_ReadWriteTimingParaStruct; /*!< The struct EXMC_NORSRAMTimingInitPara pointer,which is
                                                                     used to define the timing parameters for read and write
                                                                     if the ExtendedMode is not used or define the timing
                                                                     parameters for read if the ExtendedMode is used. */

    EXMC_NORSRAMTimingInitPara *EXMC_WriteTimingParaStruct;     /*!< The struct EXMC_NORSRAMTimingInitPara pointer,which is
                                                                     only used to define the timing parameters for write when
                                                                     the ExtendedMode is used. */
} EXMC_NORSRAMInitPara;

/**
  * @brief  Timing parameters For EXMC NAND and PCCARD Banks
  */

typedef struct {
    uint32_t EXMC_DatabusHiZTime;       /*!< The number of  HCLK cycles to configure the dadtabus HiZ time
                                             for write operation, which can be a value between 0x00 and 0xFF. */
    uint32_t EXMC_HoldTime;             /*!< The number of HCLK cycles to configure the address hold time
                                             (or the data hold time for write operation),which can be a value
                                             between 0x00 and 0xFF. */
    uint32_t EXMC_WaitTime;             /*!< The number of HCLK cycles to configure the minimum wait time,
                                             which can be a value between 0x00 and 0xFF. */
    uint32_t EXMC_SetupTime;            /*!< The number of HCLK cycles to configure the address setup time ,
                                             which can be a value between 0x00 and 0xFF. */
} EXMC_NAND_PCCARDTimingInitPara;

/**
  * @brief  EXMC NAND Init structure definition
  */
typedef struct {
    uint32_t EXMC_NANDBank;                                                /*!< The specified Bank of NAND FLASH, choose one
                                                                                from @ref EXMC_NANDBank. */
    uint32_t EXMC_ECCSize;                                                 /*!< The page size for the ECC calculation,details
                                                                                in @ref EXMC_ECCSize. */
    uint32_t EXMC_ATRLatency;                                              /*!< The number of HCLK cycles to configure the
                                                                                latency of ALE low to RB low, which can be a
                                                                                value between 0x0 and 0xF. */
    uint32_t EXMC_CTRLatency;                                              /*!< The number of HCLK cycles to configure the
                                                                                latency of CLE low to RB low, which can be a
                                                                                value between 0x0 and 0xF. */
    uint32_t EXMC_ECCLogic;                                                /*!< Enable or Disable the ECC calculation logic,
                                                                                details in @ref EXMC_ECCLogic. */
    uint32_t EXMC_DatabusWidth;                                            /*!< the NAND flash databus width, details in
                                                                                @ref EXMC_DatabusWidth. */
    uint32_t EXMC_WaitFeature;                                             /*!< Enables or Disables the Wait feature,details
                                                                                in @ref EXMC_WaitFeature. */
    EXMC_NAND_PCCARDTimingInitPara  *EXMC_CommonSpaceTimingParaStruct;     /*!< The struct EXMC_NAND_PCCARDTimingInitPara
                                                                                pointer, which is used to define the timing
                                                                                parameters for NAND flash Common Space. */
    EXMC_NAND_PCCARDTimingInitPara  *EXMC_AttributeSpaceTimingParaStruct;  /*!< The struct EXMC_NAND_PCCARDTimingInitPara
                                                                                pointer, which is used to define the timing
                                                                                parameters for NAND flash Attribute Space. */
} EXMC_NANDInitPara;

/**
  * @brief  EXMC PCCARD Init structure definition
  */

typedef struct {
    uint32_t EXMC_ATRLatency;                                               /*!< The number of HCLK cycles to configure
                                                                                 the latency of ALE low to RB low, which can
                                                                                 be a value between 0x0 and 0xF. */
    uint32_t EXMC_CTRLatency;                                               /*!< The number of HCLK cycles to configure
                                                                                 the latency of CLE low to RB low, which can
                                                                                 be a value between 0x0 and 0xF. */
    uint32_t EXMC_WaitFeature;                                              /*!< Enables or Disables the Wait feature,details
                                                                                 in @ref EXMC_WaitFeature. */
    EXMC_NAND_PCCARDTimingInitPara  *EXMC_CommonSpaceTimingParaStruct;      /*!< The struct EXMC_NAND_PCCARDTimingInitPara
                                                                                 pointer, which is used to define the timing
                                                                                 parameters for PC CARD Common Space. */
    EXMC_NAND_PCCARDTimingInitPara  *EXMC_AttributeSpaceTimingParaStruct;   /*!< The struct EXMC_NAND_PCCARDTimingInitPara
                                                                                 pointer, which is used to define the timing
                                                                                 parameters for PC CARD Attribute Space. */
    EXMC_NAND_PCCARDTimingInitPara  *EXMC_IOSpaceTimingParaStruct;          /*!< The struct EXMC_NAND_PCCARDTimingInitPara
                                                                                 pointer, which is used to define the timing
                                                                                 parameters for PC CARD I/O Space. */
} EXMC_PCCARDInitPara;

/**
  * @}
  */

/** @defgroup EXMC_Exported_Constants
  * @{
  */

/** @defgroup EXMC_NORSRAMBank
  * @{
  */
#define EXMC_BANK1_NORSRAM1                              ((uint32_t)0x00000001)
#define EXMC_BANK1_NORSRAM2                              ((uint32_t)0x00000002)
#define EXMC_BANK1_NORSRAM3                              ((uint32_t)0x00000003)
#define EXMC_BANK1_NORSRAM4                              ((uint32_t)0x00000004)
/**
  * @}
  */

/** @defgroup EXMC_NANDBank
  * @{
  */
#define EXMC_BANK2_NAND                                  ((uint32_t)0x00000010)
#define EXMC_BANK3_NAND                                  ((uint32_t)0x00000100)
/**
  * @}
  */

/** @defgroup EXMC_PCCARD_Bank
  * @{
  */
#define EXMC_BANK4_PCCARD                                ((uint32_t)0x00001000)

/**
  * @}
  */

/** @defgroup NORSRAM_Controller
  * @{
  */

/** @defgroup EXMC_AddressDataMux
  * @{
  */
#define EXMC_ADDRESS_DATA_MUX_DISABLE                    ((uint32_t)0x00000000)
#define EXMC_ADDRESS_DATA_MUX_ENABLE                     ((uint32_t)0x00000002)

/**
  * @}
  */

/** @defgroup EXMC_MemoryType
  * @{
  */
#define EXMC_MEMORY_TYPE_SRAM                            ((uint32_t)0x00000000)
#define EXMC_MEMORY_TYPE_PSRAM                           ((uint32_t)0x00000004)
#define EXMC_MEMORY_TYPE_NOR                             ((uint32_t)0x00000008)

/**
  * @}
  */

/** @defgroup EXMC_DatabusWidth
  * @{
  */
#define EXMC_DATABUS_WIDTH_8B                            ((uint32_t)0x00000000)
#define EXMC_DATABUS_WIDTH_16B                           ((uint32_t)0x00000010)

/**
  * @}
  */

/** @defgroup EXMC_NORFlash_Access
  * @{
  */
#define EXMC_NORFLASH_ACCESS_DISABLE                      ((uint32_t)0x00000000)
#define EXMC_NORFLASH_ACCESS_ENABLE                       ((uint32_t)0x00000040)

/**
  * @}
  */

/** @defgroup EXMC_BurstMode
  * @{
  */
#define EXMC_BURST_MODE_DISABLE                           ((uint32_t)0x00000000)
#define EXMC_BURST_MODE_ENABLE                            ((uint32_t)0x00000100)

/**
  * @}
  */

/** @defgroup EXMC_AsynWait
  * @{
  */
#define EXMC_ASYN_WAIT_DISABLE                            ((uint32_t)0x00000000)
#define EXMC_ASYN_WAIT_ENABLE                             ((uint32_t)0x00008000)

/**
  * @}
  */

/** @defgroup EXMC_NWAITPolarity
  * @{
  */
#define EXMC_NWAIT_POLARITY_LOW                           ((uint32_t)0x00000000)
#define EXMC_NWAIT_POLARITY_HIGH                          ((uint32_t)0x00000200)

/**
  * @}
  */

/** @defgroup EXMC_WrapBurstMode
  * @{
  */
#define EXMC_WRAP_BURST_MODE_DISABLE                     ((uint32_t)0x00000000)
#define EXMC_WRAP_BURST_MODE_ENABLE                      ((uint32_t)0x00000400)

/**
  * @}
  */

/** @defgroup EXMC_NWAITConfig
  * @{
  */
#define EXMC_NWAIT_CONFIG_BEFORE                         ((uint32_t)0x00000000)
#define EXMC_NWAIT_CONFIG_DURING                         ((uint32_t)0x00000800)

/**
  * @}
  */

/** @defgroup EXMC_MemoryWrite
  * @{
  */
#define EXMC_MEMORY_WRITE_DISABLE                        ((uint32_t)0x00000000)
#define EXMC_MEMORY_WRITE_ENABLE                         ((uint32_t)0x00001000)

/**
  * @}
  */

/** @defgroup EXMC_NWAITSignal
  * @{
  */
#define EXMC_NWAIT_SIGNAL_DISABLE                        ((uint32_t)0x00000000)
#define EXMC_NWAIT_SIGNAL_ENABLE                         ((uint32_t)0x00002000)

/**
  * @}
  */

/** @defgroup EXMC_ExtendedMode
  * @{
  */
#define EXMC_EXTENDED_MODE_DISABLE                       ((uint32_t)0x00000000)
#define EXMC_EXTENDED_MODE_ENABLE                        ((uint32_t)0x00004000)

/**
  * @}
  */

/** @defgroup EXMC_WriteMode
  * @{
  */
#define EXMC_ASYN_WRITE                                  ((uint32_t)0x00000000)
#define EXMC_SYN_WRITE                                   ((uint32_t)0x00080000)

/**
  * @}
  */

/** @defgroup EXMC_AsynAccess_Mode
  * @{
  */
#define EXMC_ACCESS_MODE_A                               ((uint32_t)0x00000000)
#define EXMC_ACCESS_MODE_B                               ((uint32_t)0x10000000)
#define EXMC_ACCESS_MODE_C                               ((uint32_t)0x20000000)
#define EXMC_ACCESS_MODE_D                               ((uint32_t)0x30000000)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup NAND_PCCARD_Controller
  * @{
  */

/** @defgroup EXMC_WaitFeature
  * @{
  */
#define EXMC_WAIT_FEATURE_DISABLE                        ((uint32_t)0x00000000)
#define EXMC_WAIT_FEATURE_ENABLE                         ((uint32_t)0x00000002)

/**
  * @}
  */

/** @defgroup EXMC_ECCLogic
  * @{
  */
#define EXMC_ECC_LOGIC_DISABLE                           ((uint32_t)0x00000000)
#define EXMC_ECC_LOGIC_ENABLE                            ((uint32_t)0x00000040)

/**
  * @}
  */

/** @defgroup EXMC_ECCSize
  * @{
  */
#define EXMC_ECC_SIZE_256BYTES                           ((uint32_t)0x00000000)
#define EXMC_ECC_SIZE_512BYTES                           ((uint32_t)0x00020000)
#define EXMC_ECC_SIZE_1024BYTES                          ((uint32_t)0x00040000)
#define EXMC_ECC_SIZE_2048BYTES                          ((uint32_t)0x00060000)
#define EXMC_ECC_SIZE_4096BYTES                          ((uint32_t)0x00080000)
#define EXMC_ECC_SIZE_8192BYTES                          ((uint32_t)0x000A0000)

/**
  * @}
  */

/** @defgroup EXMC_Interrupt_Source
  * @{
  */
#define EXMC_INT_RISE                                     ((uint32_t)0x00000008)
#define EXMC_INT_LEVEL                                    ((uint32_t)0x00000010)
#define EXMC_INT_FALL                                     ((uint32_t)0x00000020)

/**
  * @}
  */

/** @defgroup EXMC_FLAG
  * @{
  */
#define EXMC_FLAG_RISE                                   ((uint32_t)0x00000001)
#define EXMC_FLAG_LEVEL                                  ((uint32_t)0x00000002)
#define EXMC_FLAG_FALL                                   ((uint32_t)0x00000004)
#define EXMC_FLAG_FIFOE                                  ((uint32_t)0x00000040)

/**
  * @}
  */

/**
  * @}
  */

/**
* @}
*/

/** @defgroup EXMC_Exported_Functions
  * @{
  */
void EXMC_NORSRAM_DeInit(uint32_t EXMC_NORSRAMBank);
void EXMC_NAND_DeInit(uint32_t EXMC_NANDBank);
void EXMC_PCCARD_DeInit(void);
void EXMC_NORSRAM_Init(EXMC_NORSRAMInitPara *EXMC_NORSRAMInitParaStruct);
void EXMC_NAND_Init(EXMC_NANDInitPara *EXMC_NANDInitParaStruct);
void EXMC_PCCARD_Init(EXMC_PCCARDInitPara *EXMC_PCCARDInitParaStruct);
void EXMC_NORSRAMStruct_Init(EXMC_NORSRAMInitPara *EXMC_NORSRAMInitParaStruct);
void EXMC_NANDStruct_Init(EXMC_NANDInitPara *EXMC_NANDInitParaStruct);
void EXMC_PCCARDStruct_Init(EXMC_PCCARDInitPara *EXMC_PCCARDInitParaStruct);
void EXMC_NORSRAM_Enable(uint32_t EXMC_NORSRAMBank, TypeState NewValue);
void EXMC_NAND_Enable(uint32_t EXMC_NANDBank, TypeState NewValue);
void EXMC_PCCARD_Enable(TypeState NewValue);
void EXMC_NANDECC_Enable(uint32_t EXMC_NANDBank, TypeState NewValue);
uint32_t EXMC_GetECC(uint32_t EXMC_NANDBank);
void EXMC_INTConfig(uint32_t EXMC_PCNANDBank, uint32_t EXMC_INT, TypeState NewValue);
TypeState EXMC_GetBitState(uint32_t EXMC_PCNANDBank, uint32_t EXMC_FLAG);
void EXMC_ClearBitState(uint32_t EXMC_PCNANDBank, uint32_t EXMC_FLAG);
TypeState EXMC_GetIntBitState(uint32_t EXMC_PCNANDBank, uint32_t EXMC_INT);
void EXMC_ClearIntBitState(uint32_t EXMC_PCNANDBank, uint32_t EXMC_INT);

#ifdef __cplusplus
}
#endif

#endif /*__GD32F10x_EXMC_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
