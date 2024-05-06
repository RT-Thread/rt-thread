/**
 *******************************************************************************
 * @file  hc32_ll_qspi.h
 * @brief This file contains all the functions prototypes of the QSPI driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_QSPI_H__
#define __HC32_LL_QSPI_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_QSPI
 * @{
 */

#if (LL_QSPI_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup QSPI_Global_Types QSPI Global Types
 * @{
 */

/**
 * @brief QSPI initialization structure definition
 */
typedef struct {
    uint32_t u32ClockDiv;               /*!< Specifies the clock division.
                                             This parameter can be a value of @ref QSPI_Clock_Division */
    uint32_t u32SpiMode;                /*!< Specifies the SPI mode.
                                             This parameter can be a value of @ref QSPI_SPI_Mode */
    uint32_t u32PrefetchMode;           /*!< Specifies the prefetch mode.
                                             This parameter can be a value of @ref QSPI_Prefetch_Mode */
    uint32_t u32ReadMode;               /*!< Specifies the read mode.
                                             This parameter can be a value of @ref QSPI_Read_Mode */
    uint32_t u32DummyCycle;             /*!< Specifies the number of dummy cycles.
                                             This parameter can be a value of @ref QSPI_Dummy_Cycle */
    uint32_t u32AddrWidth;              /*!< Specifies the address width.
                                             This parameter can be a value of @ref QSPI_Addr_Width */
    uint32_t u32SetupTime;              /*!< Specifies the advance time of QSSN setup.
                                             This parameter can be a value of @ref QSPI_QSSN_Setup_Time */
    uint32_t u32ReleaseTime;            /*!< Specifies the delay time of QSSN release.
                                             This parameter can be a value of @ref QSPI_QSSN_Release_Time */
    uint32_t u32IntervalTime;           /*!< Specifies the minimum interval time of QSSN.
                                             This parameter can be a value of @ref QSPI_QSSN_Interval_Time */
} stc_qspi_init_t;

/**
 * @brief QSPI Custom read mode structure definition
 */
typedef struct {
    uint32_t u32InstrProtocol;          /*!< Specifies the instruction stage protocol.
                                             This parameter can be a value of @ref QSPI_Instruction_Protocol */
    uint32_t u32AddrProtocol;           /*!< Specifies the address stage protocol.
                                             This parameter can be a value of @ref QSPI_Addr_Protocol */
    uint32_t u32DataProtocol;           /*!< Specifies the data stage protocol.
                                             This parameter can be a value of @ref QSPI_Data_Protocol */
    uint8_t  u8InstrCode;               /*!< Specifies the instruction code in custom read mode.
                                             This parameter must be a number between Min_Data = 0x0 and Max_Data = 0xFF */
} stc_qspi_custom_mode_t;

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

/* QSPI memory mapping base and end address */
#define QSPI_ROM_BASE                           (0x98000000UL)
#define QSPI_ROM_END                            (0x9BFFFFFFUL)

/**
 * @defgroup QSPI_Clock_Division QSPI Clock Division
 * @{
 */
#define QSPI_CLK_DIV2                           (0x01UL << QSPI_CR_DIV_POS)     /*!< Clock division by 2    */
#define QSPI_CLK_DIV3                           (0x02UL << QSPI_CR_DIV_POS)     /*!< Clock division by 3    */
#define QSPI_CLK_DIV4                           (0x03UL << QSPI_CR_DIV_POS)     /*!< Clock division by 4    */
#define QSPI_CLK_DIV5                           (0x04UL << QSPI_CR_DIV_POS)     /*!< Clock division by 5    */
#define QSPI_CLK_DIV6                           (0x05UL << QSPI_CR_DIV_POS)     /*!< Clock division by 6    */
#define QSPI_CLK_DIV7                           (0x06UL << QSPI_CR_DIV_POS)     /*!< Clock division by 7    */
#define QSPI_CLK_DIV8                           (0x07UL << QSPI_CR_DIV_POS)     /*!< Clock division by 8    */
#define QSPI_CLK_DIV9                           (0x08UL << QSPI_CR_DIV_POS)     /*!< Clock division by 9    */
#define QSPI_CLK_DIV10                          (0x09UL << QSPI_CR_DIV_POS)     /*!< Clock division by 10   */
#define QSPI_CLK_DIV11                          (0x0AUL << QSPI_CR_DIV_POS)     /*!< Clock division by 11   */
#define QSPI_CLK_DIV12                          (0x0BUL << QSPI_CR_DIV_POS)     /*!< Clock division by 12   */
#define QSPI_CLK_DIV13                          (0x0CUL << QSPI_CR_DIV_POS)     /*!< Clock division by 13   */
#define QSPI_CLK_DIV14                          (0x0DUL << QSPI_CR_DIV_POS)     /*!< Clock division by 14   */
#define QSPI_CLK_DIV15                          (0x0EUL << QSPI_CR_DIV_POS)     /*!< Clock division by 15   */
#define QSPI_CLK_DIV16                          (0x0FUL << QSPI_CR_DIV_POS)     /*!< Clock division by 16   */
#define QSPI_CLK_DIV17                          (0x10UL << QSPI_CR_DIV_POS)     /*!< Clock division by 17   */
#define QSPI_CLK_DIV18                          (0x11UL << QSPI_CR_DIV_POS)     /*!< Clock division by 18   */
#define QSPI_CLK_DIV19                          (0x12UL << QSPI_CR_DIV_POS)     /*!< Clock division by 19   */
#define QSPI_CLK_DIV20                          (0x13UL << QSPI_CR_DIV_POS)     /*!< Clock division by 20   */
#define QSPI_CLK_DIV21                          (0x14UL << QSPI_CR_DIV_POS)     /*!< Clock division by 21   */
#define QSPI_CLK_DIV22                          (0x15UL << QSPI_CR_DIV_POS)     /*!< Clock division by 22   */
#define QSPI_CLK_DIV23                          (0x16UL << QSPI_CR_DIV_POS)     /*!< Clock division by 23   */
#define QSPI_CLK_DIV24                          (0x17UL << QSPI_CR_DIV_POS)     /*!< Clock division by 24   */
#define QSPI_CLK_DIV25                          (0x18UL << QSPI_CR_DIV_POS)     /*!< Clock division by 25   */
#define QSPI_CLK_DIV26                          (0x19UL << QSPI_CR_DIV_POS)     /*!< Clock division by 26   */
#define QSPI_CLK_DIV27                          (0x1AUL << QSPI_CR_DIV_POS)     /*!< Clock division by 27   */
#define QSPI_CLK_DIV28                          (0x1BUL << QSPI_CR_DIV_POS)     /*!< Clock division by 28   */
#define QSPI_CLK_DIV29                          (0x1CUL << QSPI_CR_DIV_POS)     /*!< Clock division by 29   */
#define QSPI_CLK_DIV30                          (0x1DUL << QSPI_CR_DIV_POS)     /*!< Clock division by 30   */
#define QSPI_CLK_DIV31                          (0x1EUL << QSPI_CR_DIV_POS)     /*!< Clock division by 31   */
#define QSPI_CLK_DIV32                          (0x1FUL << QSPI_CR_DIV_POS)     /*!< Clock division by 32   */
#define QSPI_CLK_DIV33                          (0x20UL << QSPI_CR_DIV_POS)     /*!< Clock division by 33   */
#define QSPI_CLK_DIV34                          (0x21UL << QSPI_CR_DIV_POS)     /*!< Clock division by 34   */
#define QSPI_CLK_DIV35                          (0x22UL << QSPI_CR_DIV_POS)     /*!< Clock division by 35   */
#define QSPI_CLK_DIV36                          (0x23UL << QSPI_CR_DIV_POS)     /*!< Clock division by 36   */
#define QSPI_CLK_DIV37                          (0x24UL << QSPI_CR_DIV_POS)     /*!< Clock division by 37   */
#define QSPI_CLK_DIV38                          (0x25UL << QSPI_CR_DIV_POS)     /*!< Clock division by 38   */
#define QSPI_CLK_DIV39                          (0x26UL << QSPI_CR_DIV_POS)     /*!< Clock division by 39   */
#define QSPI_CLK_DIV40                          (0x27UL << QSPI_CR_DIV_POS)     /*!< Clock division by 40   */
#define QSPI_CLK_DIV41                          (0x28UL << QSPI_CR_DIV_POS)     /*!< Clock division by 41   */
#define QSPI_CLK_DIV42                          (0x29UL << QSPI_CR_DIV_POS)     /*!< Clock division by 42   */
#define QSPI_CLK_DIV43                          (0x2AUL << QSPI_CR_DIV_POS)     /*!< Clock division by 43   */
#define QSPI_CLK_DIV44                          (0x2BUL << QSPI_CR_DIV_POS)     /*!< Clock division by 44   */
#define QSPI_CLK_DIV45                          (0x2CUL << QSPI_CR_DIV_POS)     /*!< Clock division by 45   */
#define QSPI_CLK_DIV46                          (0x2DUL << QSPI_CR_DIV_POS)     /*!< Clock division by 46   */
#define QSPI_CLK_DIV47                          (0x2EUL << QSPI_CR_DIV_POS)     /*!< Clock division by 47   */
#define QSPI_CLK_DIV48                          (0x2FUL << QSPI_CR_DIV_POS)     /*!< Clock division by 48   */
#define QSPI_CLK_DIV49                          (0x30UL << QSPI_CR_DIV_POS)     /*!< Clock division by 49   */
#define QSPI_CLK_DIV50                          (0x31UL << QSPI_CR_DIV_POS)     /*!< Clock division by 50   */
#define QSPI_CLK_DIV51                          (0x32UL << QSPI_CR_DIV_POS)     /*!< Clock division by 51   */
#define QSPI_CLK_DIV52                          (0x33UL << QSPI_CR_DIV_POS)     /*!< Clock division by 52   */
#define QSPI_CLK_DIV53                          (0x34UL << QSPI_CR_DIV_POS)     /*!< Clock division by 53   */
#define QSPI_CLK_DIV54                          (0x35UL << QSPI_CR_DIV_POS)     /*!< Clock division by 54   */
#define QSPI_CLK_DIV55                          (0x36UL << QSPI_CR_DIV_POS)     /*!< Clock division by 55   */
#define QSPI_CLK_DIV56                          (0x37UL << QSPI_CR_DIV_POS)     /*!< Clock division by 56   */
#define QSPI_CLK_DIV57                          (0x38UL << QSPI_CR_DIV_POS)     /*!< Clock division by 57   */
#define QSPI_CLK_DIV58                          (0x39UL << QSPI_CR_DIV_POS)     /*!< Clock division by 58   */
#define QSPI_CLK_DIV59                          (0x3AUL << QSPI_CR_DIV_POS)     /*!< Clock division by 59   */
#define QSPI_CLK_DIV60                          (0x3BUL << QSPI_CR_DIV_POS)     /*!< Clock division by 60   */
#define QSPI_CLK_DIV61                          (0x3CUL << QSPI_CR_DIV_POS)     /*!< Clock division by 61   */
#define QSPI_CLK_DIV62                          (0x3DUL << QSPI_CR_DIV_POS)     /*!< Clock division by 62   */
#define QSPI_CLK_DIV63                          (0x3EUL << QSPI_CR_DIV_POS)     /*!< Clock division by 63   */
#define QSPI_CLK_DIV64                          (0x3FUL << QSPI_CR_DIV_POS)     /*!< Clock division by 64   */
/**
 * @}
 */

/**
 * @defgroup QSPI_SPI_Mode QSPI SPI Mode
 * @{
 */
#define QSPI_SPI_MD0                            (0UL)               /*!< Selects SPI mode 0 */
#define QSPI_SPI_MD3                            (QSPI_CR_SPIMD3)    /*!< Selects SPI mode 3 */
/**
 * @}
 */

/**
 * @defgroup QSPI_Prefetch_Mode QSPI Prefetch Mode
 * @{
 */
#define QSPI_PREFETCH_MD_INVD                   (0UL)                           /*!< Disable prefetch                              */
#define QSPI_PREFETCH_MD_EDGE_STOP              (QSPI_CR_PFE)                   /*!< Stop prefetch at the edge of byte             */
#define QSPI_PREFETCH_MD_IMMED_STOP             (QSPI_CR_PFE | QSPI_CR_PFSAE)   /*!< Stop prefetch at current position immediately */
/**
 * @}
 */

/**
 * @defgroup QSPI_Read_Mode QSPI Read Mode
 * @{
 */
#define QSPI_RD_MD_STD_RD                       (0UL)                           /*!< Standard read mode (no dummy cycles)                   */
#define QSPI_RD_MD_FAST_RD                      (0x01UL << QSPI_CR_MDSEL_POS)   /*!< Fast read mode (dummy cycles between address and data) */
#define QSPI_RD_MD_DUAL_OUTPUT_FAST_RD          (0x02UL << QSPI_CR_MDSEL_POS)   /*!< Fast read dual output mode (data on 2 lines)           */
#define QSPI_RD_MD_DUAL_IO_FAST_RD              (0x03UL << QSPI_CR_MDSEL_POS)   /*!< Fast read dual I/O mode (address and data on 2 lines)  */
#define QSPI_RD_MD_QUAD_OUTPUT_FAST_RD          (0x04UL << QSPI_CR_MDSEL_POS)   /*!< Fast read quad output mode (data on 4 lines)           */
#define QSPI_RD_MD_QUAD_IO_FAST_RD              (0x05UL << QSPI_CR_MDSEL_POS)   /*!< Fast read quad I/O mode (address and data on 4 lines)  */
#define QSPI_RD_MD_CUSTOM_STANDARD_RD           (0x06UL << QSPI_CR_MDSEL_POS)   /*!< Custom standard read mode                              */
#define QSPI_RD_MD_CUSTOM_FAST_RD               (0x07UL << QSPI_CR_MDSEL_POS)   /*!< Custom fast read mode                                  */
/**
 * @}
 */

/**
 * @defgroup QSPI_Dummy_Cycle QSPI Dummy Cycle
 * @{
 */
#define QSPI_DUMMY_CYCLE3                       (0UL)                           /*!< Dummy cycle is 3   */
#define QSPI_DUMMY_CYCLE4                       (0x01UL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 4   */
#define QSPI_DUMMY_CYCLE5                       (0x02UL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 5   */
#define QSPI_DUMMY_CYCLE6                       (0x03UL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 6   */
#define QSPI_DUMMY_CYCLE7                       (0x04UL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 7   */
#define QSPI_DUMMY_CYCLE8                       (0x05UL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 8   */
#define QSPI_DUMMY_CYCLE9                       (0x06UL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 9   */
#define QSPI_DUMMY_CYCLE10                      (0x07UL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 10  */
#define QSPI_DUMMY_CYCLE11                      (0x08UL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 11  */
#define QSPI_DUMMY_CYCLE12                      (0x09UL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 12  */
#define QSPI_DUMMY_CYCLE13                      (0x0AUL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 13  */
#define QSPI_DUMMY_CYCLE14                      (0x0BUL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 14  */
#define QSPI_DUMMY_CYCLE15                      (0x0CUL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 15  */
#define QSPI_DUMMY_CYCLE16                      (0x0DUL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 16  */
#define QSPI_DUMMY_CYCLE17                      (0x0EUL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 15  */
#define QSPI_DUMMY_CYCLE18                      (0x0FUL << QSPI_FCR_DMCYCN_POS) /*!< Dummy cycle is 16  */
/**
 * @}
 */

/**
 * @defgroup QSPI_Addr_Width QSPI Address Width
 * @{
 */
#define QSPI_ADDR_WIDTH_8BIT                    (0x0U)                              /*!< QSPI address width is 8 bits   */
#define QSPI_ADDR_WIDTH_16BIT                   (QSPI_FCR_AWSL_0)                   /*!< QSPI address width is 16 bits  */
#define QSPI_ADDR_WIDTH_24BIT                   (QSPI_FCR_AWSL_1)                   /*!< QSPI address width is 24 bits  */
#define QSPI_ADDR_WIDTH_32BIT_INSTR_24BIT       (QSPI_FCR_AWSL)                     /*!< QSPI address width is 32 bits and don't use 4-byte address read instruction code */
#define QSPI_ADDR_WIDTH_32BIT_INSTR_32BIT       (QSPI_FCR_AWSL | QSPI_FCR_FOUR_BIC) /*!< QSPI address width is 32 bits and use 4-byte address read instruction code       */
/**
 * @}
 */

/**
 * @defgroup QSPI_QSSN_Setup_Time QSPI QSSN Setup Time
 * @{
 */
#define QSPI_QSSN_SETUP_ADVANCE_QSCK0P5         (0UL)               /*!< Output QSSN signal 0.5 QSCK before the first rising edge of QSCK */
#define QSPI_QSSN_SETUP_ADVANCE_QSCK1P5         (QSPI_FCR_SSNLD)    /*!< Output QSSN signal 1.5 QSCK before the first rising edge of QSCK */
/**
 * @}
 */

/**
 * @defgroup QSPI_QSSN_Release_Time QSPI QSSN Release Time
 * @{
 */
#define QSPI_QSSN_RELEASE_DELAY_QSCK0P5         (0UL)                       /*!< Release QSSN signal 0.5 QSCK after the last rising edge of QSCK */
#define QSPI_QSSN_RELEASE_DELAY_QSCK1P5         (QSPI_FCR_SSNHD)            /*!< Release QSSN signal 1.5 QSCK after the last rising edge of QSCK */
#define QSPI_QSSN_RELEASE_DELAY_QSCK32          (QSPI_CSCR_SSNW_0 << 8U)    /*!< Release QSSN signal 32 QSCK after the last rising edge of QSCK  */
#define QSPI_QSSN_RELEASE_DELAY_QSCK128         (QSPI_CSCR_SSNW_1 << 8U)    /*!< Release QSSN signal 128 QSCK after the last rising edge of QSCK */
#define QSPI_QSSN_RELEASE_DELAY_INFINITE        (QSPI_CSCR_SSNW   << 8U)    /*!< Never release QSSN signal after the last rising edge of QSCK    */
/**
 * @}
 */

/**
 * @defgroup QSPI_QSSN_Interval_Time QSPI QSSN Interval Time
 * @{
 */
#define QSPI_QSSN_INTERVAL_QSCK1                (0UL)                           /*!< Minimum interval time is 1 QSCK    */
#define QSPI_QSSN_INTERVAL_QSCK2                (0x01UL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 2 QSCK    */
#define QSPI_QSSN_INTERVAL_QSCK3                (0x02UL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 3 QSCK    */
#define QSPI_QSSN_INTERVAL_QSCK4                (0x03UL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 4 QSCK    */
#define QSPI_QSSN_INTERVAL_QSCK5                (0x04UL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 5 QSCK    */
#define QSPI_QSSN_INTERVAL_QSCK6                (0x05UL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 6 QSCK    */
#define QSPI_QSSN_INTERVAL_QSCK7                (0x06UL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 7 QSCK    */
#define QSPI_QSSN_INTERVAL_QSCK8                (0x07UL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 8 QSCK    */
#define QSPI_QSSN_INTERVAL_QSCK9                (0x08UL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 9 QSCK    */
#define QSPI_QSSN_INTERVAL_QSCK10               (0x09UL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 10 QSCK   */
#define QSPI_QSSN_INTERVAL_QSCK11               (0x0AUL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 11 QSCK   */
#define QSPI_QSSN_INTERVAL_QSCK12               (0x0BUL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 12 QSCK   */
#define QSPI_QSSN_INTERVAL_QSCK13               (0x0CUL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 13 QSCK   */
#define QSPI_QSSN_INTERVAL_QSCK14               (0x0DUL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 14 QSCK   */
#define QSPI_QSSN_INTERVAL_QSCK15               (0x0EUL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 15 QSCK   */
#define QSPI_QSSN_INTERVAL_QSCK16               (0x0FUL << QSPI_CSCR_SSHW_POS)  /*!< Minimum interval time is 16 QSCK   */
/**
 * @}
 */

/**
 * @defgroup QSPI_Instruction_Protocol QSPI Instruction Protocol
 * @{
 */
#define QSPI_INSTR_PROTOCOL_1LINE               (0x0U)              /*!< Instruction on 1 line  */
#define QSPI_INSTR_PROTOCOL_2LINE               (QSPI_CR_IPRSL_0)   /*!< Instruction on 2 lines */
#define QSPI_INSTR_PROTOCOL_4LINE               (QSPI_CR_IPRSL_1)   /*!< Instruction on 4 lines */
/**
 * @}
 */

/**
 * @defgroup QSPI_Addr_Protocol QSPI Address Protocol
 * @{
 */
#define QSPI_ADDR_PROTOCOL_1LINE                (0x0U)              /*!< Address on 1 line  */
#define QSPI_ADDR_PROTOCOL_2LINE                (QSPI_CR_APRSL_0)   /*!< Address on 2 lines */
#define QSPI_ADDR_PROTOCOL_4LINE                (QSPI_CR_APRSL_1)   /*!< Address on 4 lines */
/**
 * @}
 */

/**
 * @defgroup QSPI_Data_Protocol QSPI Data Protocol
 * @{
 */
#define QSPI_DATA_PROTOCOL_1LINE                (0x0U)              /*!< Data on 1 line  */
#define QSPI_DATA_PROTOCOL_2LINE                (QSPI_CR_DPRSL_0)   /*!< Data on 2 lines */
#define QSPI_DATA_PROTOCOL_4LINE                (QSPI_CR_DPRSL_1)   /*!< Data on 4 lines */
/**
 * @}
 */

/**
 * @defgroup QSPI_WP_Pin_Level QSPI WP Pin Level
 * @{
 */
#define QSPI_WP_PIN_LOW                         (0x0U)          /*!< WP(QSIO2) pin output low  */
#define QSPI_WP_PIN_HIGH                        (QSPI_FCR_WPOL) /*!< WP(QSIO2) pin output high */
/**
 * @}
 */

/**
 * @defgroup QSPI_Status_Flag QSPI Status Flag
 * @{
 */
#define QSPI_FLAG_DIRECT_COMM_BUSY              (QSPI_SR_BUSY)  /*!< Serial transfer being processed                          */
#define QSPI_FLAG_XIP_MD                        (QSPI_SR_XIPF)  /*!< XIP mode                                                 */
#define QSPI_FLAG_ROM_ACCESS_ERR                (QSPI_SR_RAER)  /*!< ROM access detection status in direct communication mode */
#define QSPI_FLAG_PREFETCH_BUF_FULL             (QSPI_SR_PFFUL) /*!< Prefetch buffer is full                                  */
#define QSPI_FLAG_PREFETCH_STOP                 (QSPI_SR_PFAN)  /*!< Prefetch function operating                              */

#define QSPI_FLAG_ALL                           (QSPI_FLAG_DIRECT_COMM_BUSY | QSPI_FLAG_XIP_MD            | \
                                                 QSPI_FLAG_ROM_ACCESS_ERR   | QSPI_FLAG_PREFETCH_BUF_FULL | \
                                                 QSPI_FLAG_PREFETCH_STOP)
#define QSPI_FLAG_CLR_ALL                       (QSPI_FLAG_ROM_ACCESS_ERR)
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
 * @brief  Write data in direct communication mode.
 * @param  [in] u8Value                 Byte data.
 * @retval None
 */
__STATIC_INLINE void QSPI_WriteDirectCommValue(uint8_t u8Value)
{
    WRITE_REG32(CM_QSPI->DCOM, u8Value);
}

/**
 * @brief  Read data in direct communication mode.
 * @param  None
 * @retval uint8_t                      Byte data.
 */
__STATIC_INLINE uint8_t QSPI_ReadDirectCommValue(void)
{
    return (uint8_t)CM_QSPI->DCOM;
}

/* Initialization and configuration functions */
int32_t QSPI_DeInit(void);
int32_t QSPI_Init(const stc_qspi_init_t *pstcQspiInit);
int32_t QSPI_StructInit(stc_qspi_init_t *pstcQspiInit);
void QSPI_SetWpPinLevel(uint32_t u32Level);
void QSPI_SetPrefetchMode(uint32_t u32Mode);
void QSPI_SelectMemoryBlock(uint8_t u8Block);
void QSPI_SetReadMode(uint32_t u32Mode);
int32_t QSPI_CustomReadConfig(const stc_qspi_custom_mode_t *pstcCustomMode);
void QSPI_XipModeCmd(uint8_t u8ModeCode, en_functional_state_t enNewState);

/* Transfer and receive data functions */
void QSPI_EnterDirectCommMode(void);
void QSPI_ExitDirectCommMode(void);
void QSPI_WriteDirectCommValue(uint8_t u8Value);
uint8_t QSPI_ReadDirectCommValue(void);

/* Interrupt and flag management functions */
uint8_t QSPI_GetPrefetchBufSize(void);
en_flag_status_t QSPI_GetStatus(uint32_t u32Flag);
void QSPI_ClearStatus(uint32_t u32Flag);

/**
 * @}
 */

#endif /* LL_QSPI_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_QSPI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
