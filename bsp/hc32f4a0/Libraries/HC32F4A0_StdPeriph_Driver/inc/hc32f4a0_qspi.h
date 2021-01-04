/**
 *******************************************************************************
 * @file  hc32f4a0_qspi.h
 * @brief This file contains all the functions prototypes of the QSPI driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wuze            First version
   2020-07-15       Wuze            Corrected the definition of 'QSPI_4BIC_ENABLE'.
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_QSPI_H__
#define __HC32F4A0_QSPI_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_QSPI
 * @{
 */

#if (DDL_QSPI_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup QSPI_Global_Types QSPI Global Types
 * @{
 */

/**
 * @brief QSPI initialization structure.
 */
typedef struct
{
    uint32_t u32ClkDiv;                             /*!< Specifies the clock divider for QSCK. QSCK = HCLK / u32ClkDiv.
                                                         This parameter can be a value between 2U and 64U, inclusive. */
    uint32_t u32CSSetupTiming;                      /*!< Specifies the setup timing of CS.
                                                         This parameter can be a value of @ref QSPI_CS_Setup_Timing */
    uint32_t u32CSReleaseTiming;                    /*!< Specifies the hold timing of CS.
                                                         This parameter can be a value of @ref QSPI_CS_Release_Timing */
    uint32_t u32CSIdleTime;                         /*!< Specifies the minimum idle time for CS. CS needs idle(stay high) for several cycles between commands.
                                                         This parameter can be a value of between 1U and 16U, inclusive. */
    uint32_t u32CSExtendTime;                       /*!< Extend the time of chip-select signal after SPI bus access.
                                                         This parameter can be a value of @ref QSPI_CS_Extend_Time */
    uint32_t u32SPIMode;                            /*!< Specifies the SPI mode. The difference between SPI modes 0 and 3 is the standby level of the QSCK signal.
                                                         The standby level of the QSCK signal in SPI mode 0 is low, and high in SPI mode 3.
                                                         This parameter can be a value of @ref QSPI_SPI_Mode */
    uint32_t u32PrefetchCmd;                        /*!< Enable or disable prefeth function.
                                                         This parameter can be a value of @ref QSPI_Prefetch_Cmd */
    uint32_t u32PrefetchStopPos;                    /*!< Specifies the position of prefetch stop.
                                                         This parameter can be a value of @ref QSPI_Prefetch_Stop_Position */
    uint32_t u32WPLevel;                            /*!< Specifies the level of pin WP(IO2).
                                                         This parameter can be a value of @ref QSPI_WP_Level */
    uint32_t u32CommMode;                           /*!< Specifies the communication mode.
                                                         This parameter can be a value of @ref QSPI_Communication_Mode */
    uint32_t u32AddrWidth;                          /*!< Specifies the address width.
                                                         This parameter can be a value of @ref QSPI_Addr_Width */
    uint32_t u32InstrMode;                          /*!< Specifies the instruction mode.
                                                         This parameter can be a value of @ref QSPI_Instruction_Mode */
    uint32_t u32AddrMode;                           /*!< Specifies the address mode.
                                                         This parameter can be a value of @ref QSPI_Addr_Mode */
    uint32_t u32DataMode;                           /*!< Specifies the data mode (used for dummy cycles and data phases)
                                                         This parameter can be a value of @ref QSPI_Data_Mode */
    uint32_t u32ReadMode;                           /*!< Specifies the read mode.
                                                         This parameter can be a value of @ref QSPI_Read_Mode */
    uint8_t u8RomAccessInstr;                       /*!< Rom access instruction. This parameter only supports read instruction of QSPI flash now.
                                                         Tis instruction must correspond to the read mode that specified by parameter 'u32ReadMode'. */
    uint32_t u32DummyCycles;                        /*!< Specifies the number of dummy cycles for fast read.
                                                         This parameter can be a value between 3U and 18U. */
} stc_qspi_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup QSPI_Global_Macros QSPI Global Macros
 * @{
 */

/**
 * @defgroup QSPI_Read_Mode QSPI Read Mode
 * @{
 */
#define QSPI_READ_STANDARD_READ             (0x0U)                  /*!< Standard read mode (no dummy cycles). */
#define QSPI_READ_FAST_READ                 (QSPI_CR_MDSEL_0)       /*!< Fast read mode (dummy cycles between address and data). */
#define QSPI_READ_FAST_READ_DUAL_OUTPUT     (QSPI_CR_MDSEL_1)       /*!< Fast read dual output mode (data on 2 lines). */
#define QSPI_READ_FAST_READ_DUAL_IO         (QSPI_CR_MDSEL_1 | \
                                             QSPI_CR_MDSEL_0)       /*!< Fast read dual I/O mode (address and data on 2 lines). */
#define QSPI_READ_FAST_READ_QUAD_OUTPUT     (QSPI_CR_MDSEL_2)       /*!< Fast read quad output mode (data on 4 lines). */
#define QSPI_READ_FAST_READ_QUAD_IO         (QSPI_CR_MDSEL_2 | \
                                             QSPI_CR_MDSEL_0)       /*!< Fast read quad I/O mode (address and data on 4 lines). */
#define QSPI_READ_CUSTOM_STANDARD_READ      (QSPI_CR_MDSEL_2 | \
                                             QSPI_CR_MDSEL_1)       /*!< Custom standard read mode. */
#define QSPI_READ_CUSTOM_FAST_READ          (QSPI_CR_MDSEL_2 | \
                                             QSPI_CR_MDSEL_1 | \
                                             QSPI_CR_MDSEL_0)       /*!< Custom fast read mode. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Prefetch_Cmd QSPI Prefetch Cmd
 * @{
 */
#define QSPI_PREFETCH_DISABLE               (0x0U)                  /*!< Disable prefetch. */
#define QSPI_PREFETCH_ENABLE                (QSPI_CR_PFE)           /*!< Enable prefetch. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Prefetch_Stop_Position QSPI Prefetch Stop Position
 * @{
 */
#define QSPI_PREFETCH_STOP_BYTE_EDGE        (0x0U)                  /*!< Stop prefetch at the edge of byte. */
#define QSPI_PREFETCH_STOP_IMMED            (QSPI_CR_PFSAE)         /*!< Stop prefetch at current position immediately. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Communication_Mode QSPI Communication Mode
 * @{
 */
#define QSPI_COMM_ROM_ACCESS                (0x0U)                  /*!< ROM access mode. */
#define QSPI_COMM_DIRECT_COMM               (QSPI_CR_DCOME)         /*!< Direct communication mode. */
/**
 * @}
 */

/**
 * @defgroup QSPI_XIP_Mode_Command QSPI XIP Mode Command
 * @{
 */
#define QSPI_XIP_DISABLE                    (0x0U)                  /*!< XIP mode disable. */
#define QSPI_XIP_ENABLE                     (QSPI_CR_XIPE)          /*!< XIP mode enable. */
/**
 * @}
 */

/**
 * @defgroup QSPI_SPI_Mode QSPI SPI Mode
 * @{
 */
#define QSPI_SPI_MODE_0                     (0x0U)                  /*!< Selects SPI mode 0. */
#define QSPI_SPI_MODE_3                     (QSPI_CR_SPIMD3)        /*!< Selects SPI mode 3. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Instruction_Mode QSPI Instruction Mode
 * @{
 */
#define QSPI_INSTR_1LINE                    (0x0U)                  /*!< Instruction on a single line. */
#define QSPI_INSTR_2LINE                    (QSPI_CR_IPRSL_0)       /*!< Instruction on 2 lines. */
#define QSPI_INSTR_4LINE                    (QSPI_CR_IPRSL_1)       /*!< Instruction on 4 lines. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Addr_Mode QSPI Address Mode
 * @{
 */
#define QSPI_ADDR_1LINE                     (0x0U)                  /*!< Address on a single line. */
#define QSPI_ADDR_2LINE                     (QSPI_CR_APRSL_0)       /*!< Address on 2 lines. */
#define QSPI_ADDR_4LINE                     (QSPI_CR_APRSL_1)       /*!< Address on 4 lines. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Data_Mode QSPI Data Mode
 * @{
 */
#define QSPI_DATA_1LINE                     (0x0U)                  /*!< Data on a single line. */
#define QSPI_DATA_2LINE                     (QSPI_CR_DPRSL_0)       /*!< Data on 2 lines. */
#define QSPI_DATA_4LINE                     (QSPI_CR_DPRSL_1)       /*!< Data on 4 lines. */
/**
 * @}
 */

/**
 * @defgroup QSPI_CS_Extend_Time QSPI Chip-select Extend Time
 * @{
 */
#define QSPI_CS_EXTEND_0CYCLE               (0x0U)                  /*!< Do not extend chip-select signal time. */
#define QSPI_CS_EXTEND_32CYCLE              (QSPI_CSCR_SSNW_0)      /*!< Extend chip-select time by 32 QSCK cycles. */
#define QSPI_CS_EXTEND_128CYCLE             (QSPI_CSCR_SSNW_1)      /*!< Extend chip-select time by 128 QSCK cycles. */
#define QSPI_CS_EXTEND_INFINITE             (QSPI_CSCR_SSNW_1 | \
                                             QSPI_CSCR_SSNW_0)      /*!< Extend chip-select time infinitely. */
/**
 * @}
 */

/**
 * @defgroup QSPI_Addr_Width QSPI Address Width
 * @{
 */
#define QSPI_ADDR_WIDTH_1BYTE               (0x0U)                  /*!< QSPI address width is 1 byte. */
#define QSPI_ADDR_WIDTH_2BYTE               (QSPI_FCR_AWSL_0)       /*!< QSPI address width is 2 bytes. */
#define QSPI_ADDR_WIDTH_3BYTE               (QSPI_FCR_AWSL_1)       /*!< QSPI address width is 3 bytes. */
#define QSPI_ADDR_WIDTH_4BYTE               (QSPI_FCR_AWSL_1 | \
                                             QSPI_FCR_AWSL_0)       /*!< QSPI address width is 4 bytes. */
/**
 * @}
 */

/**
 * @defgroup QSPI_4BIC_Command QSPI 4-Byte Address Instruction Read Code Command
 * @note Valid when the serial interface address width is 4 bytes.
 * @{
 */
#define QSPI_4BIC_DISABLE                   (0x0U)                  /*!< Do not use 4-byte address read instruction code. */
#define QSPI_4BIC_ENABLE                    (QSPI_FCR_FOUR_BIC)     /*!< Use 4-byte address read instruction code. */
/**
 * @}
 */

/**
 * @defgroup QSPI_CS_Release_Timing QSPI Chip-select Hold Timing
 * @{
 */
#define QSPI_CS_RELEASE_AFTER_0P5_CYCLE     (0x0U)                  /*!< Release chip-select signal 0.5 QSCK cycles after the last rising edge of QSCK. */
#define QSPI_CS_RELEASE_AFTER_1P5_CYCLE     (QSPI_FCR_SSNHD)        /*!< Release chip-select signal 1.5 QSCK cycles after the last rising edge of QSCK. */
/**
 * @}
 */

/**
 * @defgroup QSPI_CS_Setup_Timing QSPI Chip-select Setup Timing
 * @{
 */
#define QSPI_CS_SETUP_BEFORE_0P5_CYCLE      (0x0U)                  /*!< Output chip-select signal 0.5 QSCK cycles before the first rising edge of QSCK. */
#define QSPI_CS_SETUP_BEFORE_1P5_CYCLE      (QSPI_FCR_SSNLD)        /*!< Output chip-select signal 1.5 QSCK cycles before the first rising edge of QSCK. */
/**
 * @}
 */

/**
 * @defgroup QSPI_WP_Level QSPI Write Protect Pin Level
 * @{
 */
#define QSPI_WP_LOW                         (0x0U)                  /*!< WP(QIO2) output low. */
#define QSPI_WP_HIGH                        (QSPI_FCR_WPOL)         /*!< WP(QIO2) output high. */
/**
 * @}
 */

/**
 * @defgroup QSPI_QSCK_Duty_Correction_Command QSPI QSCK Duty Correction Command
 * @{
 */
#define QSPI_DUTY_CORRECTION_DISABLE        (0x0U)                  /*!< Make no duty ratio correction on QSCK. */
#define QSPI_DUTY_CORRECTION_ENABLE         (QSPI_FCR_DUTY)         /*!< Delay the rising of the QSCK signal by 0.5 HCLK cycles. \
                                                                         (Valid when HCLK is multiplied by an odd number.) */
/**
 * @}
 */

/**
 * @defgroup QSPI_Status_Flag QSPI Status Flag
 * @{
 */
#define QSPI_FLAG_DIRECT_COMM_BUSY          (QSPI_SR_BUSY)          /*!< Serial transfer being processed. */
#define QSPI_FLAG_XIP_MODE                  (QSPI_SR_XIPF)          /*!< XIP mode. */
#define QSPI_FLAG_ROM_ACCESS_ERR            (QSPI_SR_RAER)          /*!< ROM access detection status in direct communication mode. */
#define QSPI_FLAG_PREFETCH_BUF_FULL         (QSPI_SR_PFFUL)         /*!< Prefetch buffer is full. */
#define QSPI_FLAG_PREFETCH_ACTIVE           (QSPI_SR_PFAN)          /*!< Prefetch function operating. */

#define QSPI_FLAG_ALL                       (QSPI_FLAG_DIRECT_COMM_BUSY  | \
                                             QSPI_FLAG_XIP_MODE          | \
                                             QSPI_FLAG_ROM_ACCESS_ERR    | \
                                             QSPI_FLAG_PREFETCH_BUF_FULL | \
                                             QSPI_FLAG_PREFETCH_ACTIVE)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup QSPI_Global_Functions
 * @{
 */

/**
 * @brief  Enter direct communication mode.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void QSPI_EnterDirectCommMode(void)
{
    /* Set standard read mode. */
    CLEAR_REG32_BIT(M4_QSPI->CR, QSPI_CR_MDSEL);
    /* Enter direct communication mode. */
    SET_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);
}

/**
 * @brief  Exit direct communication mode.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void QSPI_ExitDirectCommMode(void)
{
    CLEAR_REG32_BIT(M4_QSPI->CR, QSPI_CR_DCOME);
}

/**
 * @brief  Write data in direct communication mode.
 * @param  [in]  u8Val              Byte data.
 * @retval None
 */
__STATIC_INLINE void QSPI_WriteDirectCommValue(uint8_t u8Val)
{
    WRITE_REG32(M4_QSPI->DCOM, u8Val);
}

/**
 * @brief  Read data in communication mode.
 * @param  None
 * @retval Byte data.
 */
__STATIC_INLINE uint8_t QSPI_ReadDirectCommValue(void)
{
    return (uint8_t)M4_QSPI->DCOM;
}

/**
 * @brief  Set ROM access instruction.
 * @param  [in]  u8Instr                ROM access instruction.
 * @retval None
 */
__STATIC_INLINE void QSPI_SetRomAccressInstr(uint8_t u8Instr)
{
    WRITE_REG32(M4_QSPI->CCMD, u8Instr);
}


en_result_t QSPI_Init(const stc_qspi_init_t *pstcInit);
void QSPI_DeInit(void);
en_result_t QSPI_StructInit(stc_qspi_init_t *pstcInit);

en_result_t QSPI_WriteData(uint32_t u32Instr, uint32_t u32Address, \
                           const uint8_t pu8Src[], uint32_t u32SrcSize);
en_result_t QSPI_ReadData(uint32_t u32Address, uint8_t pu8Dest[], uint32_t u32DestSize);

void QSPI_SetReadMode(uint32_t u32ReadMode, uint8_t u8ReadInstr, uint32_t u32DummyCycles);
void QSPI_DutyCorrectCmd(en_functional_state_t enNewState);
void QSPI_PrefetchCmd(en_functional_state_t enNewState);
void QSPI_XIPModeCmd(en_functional_state_t enNewState);
void QSPI_SetWPPinLevel(uint32_t u32Level);
void QSPI_4ByteAddrModeCmd(en_functional_state_t enNewState);
void QSPI_SelectBlock(uint32_t u32Block);

uint32_t QSPI_GetPrefetchedSize(void);
en_flag_status_t QSPI_GetStatus(uint32_t u32Flag);
void QSPI_ClrStatus(uint32_t u32Flag);

void QSPI_EnterDirectCommMode(void);
void QSPI_ExitDirectCommMode(void);
void QSPI_WriteDirectCommValue(uint8_t u8Val);
uint8_t QSPI_ReadDirectCommValue(void);
void QSPI_SetRomAccressInstr(uint8_t u8Instr);

/**
 * @}
 */

#endif /* DDL_QSPI_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_QSPI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
