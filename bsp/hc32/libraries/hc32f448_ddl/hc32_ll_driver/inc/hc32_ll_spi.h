/**
 *******************************************************************************
 * @file  hc32_ll_spi.h
 * @brief This file contains all the functions prototypes of the SPI driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-12-15       CDT             Rename SPI_FLAG_OVERLOAD as SPI_FLAG_OVERRUN, SPI_FLAG_UNDERLOAD as SPI_FLAG_UNDERRUN
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
#ifndef __HC32_LL_SPI_H__
#define __HC32_LL_SPI_H__

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
 * @addtogroup LL_SPI
 * @{
 */

#if (LL_SPI_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Types SPI Global Types
 * @{
 */

/**
 * @brief Structure definition of SPI initialization.
 * @note The parameter u32BaudRatePrescaler is invalid while slave mode
 */
typedef struct {
    uint32_t u32WireMode;           /*!< SPI wire mode, 3 wire mode or 4 wire mode.
                                         This parameter can be a value of @ref SPI_Wire_Mode_Define */
    uint32_t u32TransMode;          /*!< SPI transfer mode, send only or full duplex.
                                         This parameter can be a value of @ref SPI_Trans_Mode_Define */
    uint32_t u32MasterSlave;        /*!< SPI master/slave mode.
                                         This parameter can be a value of @ref SPI_Master_Slave_Mode_Define */
    uint32_t u32ModeFaultDetect;    /*!< SPI mode fault detect command.
                                         This parameter can be a value of @ref SPI_Mode_Fault_Detect_Command_Define */
    uint32_t u32Parity;             /*!< SPI parity check selection.
                                         This parameter can be a value of @ref SPI_Parity_Check_Define */
    uint32_t u32SpiMode;            /*!< SPI mode.
                                         This parameter can be a value of @ref SPI_Mode_Define */
    uint32_t u32BaudRatePrescaler;  /*!< SPI baud rate prescaler.
                                         This parameter can be a value of @ref SPI_Baud_Rate_Prescaler_Define */
    uint32_t u32DataBits;           /*!< SPI data bits, 4 bits ~ 32 bits.
                                         This parameter can be a value of @ref SPI_Data_Size_Define */
    uint32_t u32FirstBit;           /*!< MSB first or LSB first.
                                         This parameter can be a value of @ref SPI_First_Bit_Define */
    uint32_t u32SuspendMode;        /*!< SPI communication suspend function.
                                         This parameter can be a value of @ref SPI_Com_Suspend_Func_Define */
    uint32_t u32FrameLevel;         /*!< SPI frame level, SPI_1_FRAME ~ SPI_4_FRAME.
                                         This parameter can be a value of @ref SPI_Frame_Level_Define */
} stc_spi_init_t;

/**
 * @brief Structure definition of SPI delay time configuration.
 */
typedef struct {
    uint32_t u32IntervalDelay;      /*!< SPI interval time delay (Next access delay time)
                                         This parameter can be a value of @ref SPI_Interval_Delay_Time_define */
    uint32_t u32ReleaseDelay;       /*!< SPI release time delay (SCK invalid delay time)
                                         This parameter can be a value of @ref SPI_Release_Delay_Time_define */
    uint32_t u32SetupDelay;         /*!< SPI Setup time delay (SCK valid delay time) define
                                         This parameter can be a value of @ref SPI_Setup_Delay_Time_define */
} stc_spi_delay_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Macros SPI Global Macros
 * @{
 */

/**
 * @defgroup SPI_Wire_Mode_Define SPI Wire Mode Define
 * @{
 */
#define SPI_4_WIRE                  (0UL)
#define SPI_3_WIRE                  (SPI_CR_SPIMDS)
/**
 * @}
 */

/**
 * @defgroup SPI_Trans_Mode_Define SPI Transfer Mode Define
 * @{
 */
#define SPI_FULL_DUPLEX             (0UL)               /*!< Full duplex. */
#define SPI_SEND_ONLY               (SPI_CR_TXMDS)      /*!< Send only. */
/**
 * @}
 */

/**
 * @defgroup SPI_Master_Slave_Mode_Define SPI Master Slave Mode Define
 * @{
 */
#define SPI_SLAVE                   (0UL)
#define SPI_MASTER                  (SPI_CR_MSTR)
/**
 * @}
 */

/**
 * @defgroup SPI_Loopback_Selection_Define SPI Loopback Selection Define
 * @note Loopback mode is mainly used for parity self-diagnosis in 4-wire full-duplex mode.
 * @{
 */
#define SPI_LOOPBACK_INVD           (0UL)
#define SPI_LOOPBACK_MOSI_INVT      (SPI_CR_SPLPBK)     /*!< MISO data is the inverse of the data output by MOSI. */
#define SPI_LOOPBACK_MOSI           (SPI_CR_SPLPBK2)    /*!< MISO data is the data output by MOSI. */
/**
 * @}
 */

/**
 * @defgroup SPI_Int_Type_Define SPI Interrupt Type Define
 * @{
 */
#define SPI_INT_ERR                 (SPI_CR_EIE)        /*!< Including overload, underload and parity error. */
#define SPI_INT_TX_BUF_EMPTY        (SPI_CR_TXIE)
#define SPI_INT_RX_BUF_FULL         (SPI_CR_RXIE)
#define SPI_INT_IDLE                (SPI_CR_IDIE)
#define SPI_INT_ALL                 (SPI_INT_ERR | SPI_INT_TX_BUF_EMPTY | SPI_INT_RX_BUF_FULL | SPI_INT_IDLE )
/**
 * @}
 */

/**
 * @defgroup SPI_Mode_Fault_Detect_Command_Define SPI Mode Fault Detect Command Define
 * @{
 */
#define SPI_MD_FAULT_DETECT_DISABLE (0UL)               /*!< Disable mode fault detection. */
#define SPI_MD_FAULT_DETECT_ENABLE  (SPI_CR_MODFE)      /*!< Enable mode fault detection. */
/**
 * @}
 */

/**
 * @defgroup SPI_Parity_Check_Define SPI Parity Check Mode Define
 * @{
 */
#define SPI_PARITY_INVD             (0UL)                           /*!< Parity check invalid. */
#define SPI_PARITY_EVEN             (SPI_CR_PAE)                    /*!< Parity check selection even parity. */
#define SPI_PARITY_ODD              (SPI_CR_PAE | SPI_CR_PAOE)      /*!< Parity check selection odd parity. */
/**
 * @}
 */

/**
 * @defgroup SPI_SS_Pin_Define SPI SSx Define
 * @{
 */
#define SPI_PIN_SS0                 (SPI_CFG1_SS0PV)
#define SPI_PIN_SS1                 (SPI_CFG1_SS1PV)
#define SPI_PIN_SS2                 (SPI_CFG1_SS2PV)
#define SPI_PIN_SS3                 (SPI_CFG1_SS3PV)
/**
 * @}
 */

/**
 * @defgroup SPI_SS_Level SPI SS pin valid level
 * @{
 */
#define SPI_SS_VALID_LVL_HIGH       (1UL)
#define SPI_SS_VALID_LVL_LOW        (0UL)
/**
 * @}
 */

/**
 * @defgroup SPI_Read_Target_Buf_Define SPI Read Data Register Target Buffer Define
 * @{
 */
#define SPI_RD_TARGET_RD_BUF        (0UL)               /*!< Read RX buffer. */
#define SPI_RD_TARGET_WR_BUF        (SPI_CFG1_SPRDTD)   /*!< Read TX buffer. */
/**
 * @}
 */

/**
 * @defgroup SPI_Frame_Level_Define SPI data frame level define, The Data in the SPI_DR register will be send to TX_BUFF
 *                                   after enough data frame write to the SPI_DR
 * @{
 */
#define SPI_1_FRAME                 (0UL)                   /*!< Data 1 frame */
#define SPI_2_FRAME                 (SPI_CFG1_FTHLV_0)      /*!< Data 2 frame.*/
#define SPI_3_FRAME                 (SPI_CFG1_FTHLV_1)      /*!< Data 3 frame.*/
#define SPI_4_FRAME                 (SPI_CFG1_FTHLV)        /*!< Data 4 frame.*/
/**
 * @}
 */

/**
 * @defgroup SPI_Interval_Delay_Time_define SPI Interval Time Delay (Next Access Delay Time) define
 * @{
 */
#define SPI_INTERVAL_TIME_1SCK      (0UL << SPI_CFG1_MIDI_POS)    /*!< 1 SCK + 2 PCLK1 */
#define SPI_INTERVAL_TIME_2SCK      (1UL << SPI_CFG1_MIDI_POS)    /*!< 2 SCK + 2 PCLK1 */
#define SPI_INTERVAL_TIME_3SCK      (2UL << SPI_CFG1_MIDI_POS)    /*!< 3 SCK + 2 PCLK1 */
#define SPI_INTERVAL_TIME_4SCK      (3UL << SPI_CFG1_MIDI_POS)    /*!< 4 SCK + 2 PCLK1 */
#define SPI_INTERVAL_TIME_5SCK      (4UL << SPI_CFG1_MIDI_POS)    /*!< 5 SCK + 2 PCLK1 */
#define SPI_INTERVAL_TIME_6SCK      (5UL << SPI_CFG1_MIDI_POS)    /*!< 6 SCK + 2 PCLK1 */
#define SPI_INTERVAL_TIME_7SCK      (6UL << SPI_CFG1_MIDI_POS)    /*!< 7 SCK + 2 PCLK1 */
#define SPI_INTERVAL_TIME_8SCK      (7UL << SPI_CFG1_MIDI_POS)    /*!< 8 SCK + 2 PCLK1 */
/**
 * @}
 */

/**
 * @defgroup SPI_Release_Delay_Time_define SPI Release Time Delay (SCK Invalid Delay Time) Define
 * @{
 */
#define SPI_RELEASE_TIME_1SCK       (0UL << SPI_CFG1_MSSDL_POS)
#define SPI_RELEASE_TIME_2SCK       (1UL << SPI_CFG1_MSSDL_POS)
#define SPI_RELEASE_TIME_3SCK       (2UL << SPI_CFG1_MSSDL_POS)
#define SPI_RELEASE_TIME_4SCK       (3UL << SPI_CFG1_MSSDL_POS)
#define SPI_RELEASE_TIME_5SCK       (4UL << SPI_CFG1_MSSDL_POS)
#define SPI_RELEASE_TIME_6SCK       (5UL << SPI_CFG1_MSSDL_POS)
#define SPI_RELEASE_TIME_7SCK       (6UL << SPI_CFG1_MSSDL_POS)
#define SPI_RELEASE_TIME_8SCK       (7UL << SPI_CFG1_MSSDL_POS)
/**
 * @}
 */

/**
 * @defgroup SPI_Setup_Delay_Time_define SPI Setup Time Delay (SCK Valid Delay Time) Define
 * @{
 */
#define SPI_SETUP_TIME_1SCK         (0UL << SPI_CFG1_MSSI_POS)
#define SPI_SETUP_TIME_2SCK         (1UL << SPI_CFG1_MSSI_POS)
#define SPI_SETUP_TIME_3SCK         (2UL << SPI_CFG1_MSSI_POS)
#define SPI_SETUP_TIME_4SCK         (3UL << SPI_CFG1_MSSI_POS)
#define SPI_SETUP_TIME_5SCK         (4UL << SPI_CFG1_MSSI_POS)
#define SPI_SETUP_TIME_6SCK         (5UL << SPI_CFG1_MSSI_POS)
#define SPI_SETUP_TIME_7SCK         (6UL << SPI_CFG1_MSSI_POS)
#define SPI_SETUP_TIME_8SCK         (7UL << SPI_CFG1_MSSI_POS)
/**
 * @}
 */

/**
 * @defgroup SPI_Com_Suspend_Func_Define SPI Communication Suspend Function Define
 * @{
 */
#define SPI_COM_SUSP_FUNC_OFF       (0UL)
#define SPI_COM_SUSP_FUNC_ON        (SPI_CR_CSUSPE)
/**
 * @}
 */

/**
 * @defgroup SPI_Mode_Define SPI Mode Define
 * @{
 */
#define SPI_MD_0                    (0UL)                           /*!< SCK pin output low in idle state; \
                                                                         MOSI/MISO pin data valid in odd edge, \
                                                                         MOSI/MISO pin data change in even edge */
#define SPI_MD_1                    (SPI_CFG2_CPHA)                 /*!< SCK pin output low in idle state; \
                                                                         MOSI/MISO pin data valid in even edge, \
                                                                         MOSI/MISO pin data change in odd edge */
#define SPI_MD_2                    (SPI_CFG2_CPOL)                 /*!< SCK pin output high in idle state; \
                                                                         MOSI/MISO pin data valid in odd edge, \
                                                                         MOSI/MISO pin data change in even edge */
#define SPI_MD_3                    (SPI_CFG2_CPOL | SPI_CFG2_CPHA) /*!< SCK pin output high in idle state; \
                                                                         MOSI/MISO pin data valid in even edge, \
                                                                         MOSI/MISO pin data change in odd edge */
/**
 * @}
 */

/**
 * @defgroup SPI_SCK_Polarity_Define SPI SCK Polarity Define
 * @{
 */
#define SPI_SCK_POLARITY_LOW        (0UL)                   /*!< SCK pin output low in idle state  */
#define SPI_SCK_POLARITY_HIGH       (SPI_CFG2_CPOL)         /*!< SCK pin output high in idle state */
/**
 * @}
 */

/**
 * @defgroup SPI_SCK_Phase_Define SPI SCK Phase Define
 * @{
 */
#define SPI_SCK_PHASE_ODD_EDGE_SAMPLE   (0UL)               /*!< MOSI/MISO pin data sample in odd edge, MOSI/MISO pin data change in even edge */
#define SPI_SCK_PHASE_EVEN_EDGE_SAMPLE  (SPI_CFG2_CPHA)     /*!< MOSI/MISO pin data sample in even edge, MOSI/MISO pin data change in odd edge */
/**
 * @}
 */

/**
 * @defgroup SPI_Baud_Rate_Prescaler_Define SPI Baudrate Prescaler Define
 * @{
 */
#define SPI_BR_CLK_DIV2             (0UL)                           /*!< PCLK1 / 2   */
#define SPI_BR_CLK_DIV4             (1UL  << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 4   */
#define SPI_BR_CLK_DIV6             (2UL  << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 6   */
#define SPI_BR_CLK_DIV8             (3UL  << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 8   */
#define SPI_BR_CLK_DIV10            (4UL  << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 10  */
#define SPI_BR_CLK_DIV12            (5UL  << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 12  */
#define SPI_BR_CLK_DIV14            (6UL  << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 14  */
#define SPI_BR_CLK_DIV16            (7UL  << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 16  */
#define SPI_BR_CLK_DIV18            (8UL  << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 18  */
#define SPI_BR_CLK_DIV20            (9UL  << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 20  */
#define SPI_BR_CLK_DIV22            (10UL << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 22  */
#define SPI_BR_CLK_DIV24            (11UL << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 24  */
#define SPI_BR_CLK_DIV26            (12UL << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 26  */
#define SPI_BR_CLK_DIV28            (13UL << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 28  */
#define SPI_BR_CLK_DIV30            (14UL << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 30  */
#define SPI_BR_CLK_DIV32            (15UL << SPI_CFG1_CLKDIV_POS)   /*!< PCLK1 / 32  */
#define SPI_BR_CLK_DIV36            ((8UL  << SPI_CFG1_CLKDIV_POS) | (1UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 36  */
#define SPI_BR_CLK_DIV40            ((9UL  << SPI_CFG1_CLKDIV_POS) | (1UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 40  */
#define SPI_BR_CLK_DIV44            ((10UL << SPI_CFG1_CLKDIV_POS) | (1UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 44  */
#define SPI_BR_CLK_DIV48            ((11UL << SPI_CFG1_CLKDIV_POS) | (1UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 48  */
#define SPI_BR_CLK_DIV52            ((12UL << SPI_CFG1_CLKDIV_POS) | (1UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 52  */
#define SPI_BR_CLK_DIV56            ((13UL << SPI_CFG1_CLKDIV_POS) | (1UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 56  */
#define SPI_BR_CLK_DIV60            ((14UL << SPI_CFG1_CLKDIV_POS) | (1UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 60  */
#define SPI_BR_CLK_DIV64            ((15UL << SPI_CFG1_CLKDIV_POS) | (1UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 64  */
#define SPI_BR_CLK_DIV72            ((8UL  << SPI_CFG1_CLKDIV_POS) | (2UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 72  */
#define SPI_BR_CLK_DIV80            ((9UL  << SPI_CFG1_CLKDIV_POS) | (2UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 80  */
#define SPI_BR_CLK_DIV88            ((10UL << SPI_CFG1_CLKDIV_POS) | (2UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 88  */
#define SPI_BR_CLK_DIV96            ((11UL << SPI_CFG1_CLKDIV_POS) | (2UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 96  */
#define SPI_BR_CLK_DIV104           ((12UL << SPI_CFG1_CLKDIV_POS) | (2UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 104 */
#define SPI_BR_CLK_DIV112           ((13UL << SPI_CFG1_CLKDIV_POS) | (2UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 112 */
#define SPI_BR_CLK_DIV120           ((14UL << SPI_CFG1_CLKDIV_POS) | (2UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 120 */
#define SPI_BR_CLK_DIV128           ((15UL << SPI_CFG1_CLKDIV_POS) | (2UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 128 */
#define SPI_BR_CLK_DIV144           ((8UL  << SPI_CFG1_CLKDIV_POS) | (3UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 144 */
#define SPI_BR_CLK_DIV160           ((9UL  << SPI_CFG1_CLKDIV_POS) | (3UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 160 */
#define SPI_BR_CLK_DIV176           ((10UL << SPI_CFG1_CLKDIV_POS) | (3UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 176 */
#define SPI_BR_CLK_DIV192           ((11UL << SPI_CFG1_CLKDIV_POS) | (3UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 192 */
#define SPI_BR_CLK_DIV208           ((12UL << SPI_CFG1_CLKDIV_POS) | (3UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 208 */
#define SPI_BR_CLK_DIV224           ((13UL << SPI_CFG1_CLKDIV_POS) | (3UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 224 */
#define SPI_BR_CLK_DIV240           ((14UL << SPI_CFG1_CLKDIV_POS) | (3UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 240 */
#define SPI_BR_CLK_DIV256           ((15UL << SPI_CFG1_CLKDIV_POS) | (3UL << SPI_CFG2_MBR_POS)) /*!< PCLK1 / 256 */
/**
 * @}
 */

/**
 * @defgroup SPI_Data_Size_Define SPI Data Size Define
 * @{
 */
#define SPI_DATA_SIZE_4BIT          (0UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_5BIT          (1UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_6BIT          (2UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_7BIT          (3UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_8BIT          (4UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_9BIT          (5UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_10BIT         (6UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_11BIT         (7UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_12BIT         (8UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_13BIT         (9UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_14BIT         (10UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_15BIT         (11UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_16BIT         (12UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_20BIT         (13UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_24BIT         (14UL << SPI_CFG2_DSIZE_POS)
#define SPI_DATA_SIZE_32BIT         (15UL << SPI_CFG2_DSIZE_POS)

/**
 * @}
 */

/**
 * @defgroup SPI_First_Bit_Define SPI First Bit Define
 * @{
 */
#define SPI_FIRST_MSB               (0UL)
#define SPI_FIRST_LSB               (SPI_CFG2_LSBF)
/**
 * @}
 */

/**
 * @defgroup SPI_Comm_Mode_Define SPI communication mode Define
 * @{
 */
#define SPI_COMM_MD_NORMAL          (0UL)               /*!< Normal communication mode     */
#define SPI_COMM_MD_CONT            (SPI_CFG1_CTMDS)    /*!< Continuous communication mode */
/**
 * @}
 */

/**
 * @defgroup SPI_State_Flag_Define SPI State Flag Define
 * @{
 */
#define SPI_FLAG_OVERRUN            (SPI_SR_OVRERF)
#define SPI_FLAG_IDLE               (SPI_SR_IDLNF)
#define SPI_FLAG_MD_FAULT           (SPI_SR_MODFERF)
#define SPI_FLAG_PARITY_ERR         (SPI_SR_PERF)
#define SPI_FLAG_UNDERRUN           (SPI_SR_UDRERF)
#define SPI_FLAG_TX_BUF_EMPTY       (SPI_SR_TDEF)       /*!< This flag is set when the data in the data register     \
                                                             is copied into the shift register, but the transmission \
                                                             of the data bit may not have been completed. */
#define SPI_FLAG_RX_BUF_FULL        (SPI_SR_RDFF)       /*!< Indicates that a data was received. */
#define SPI_FLAG_CLR_ALL            (SPI_FLAG_OVERRUN  | SPI_FLAG_MD_FAULT | SPI_FLAG_PARITY_ERR | SPI_FLAG_UNDERRUN)
#define SPI_FLAG_ALL                (SPI_FLAG_OVERRUN  | SPI_FLAG_IDLE | SPI_FLAG_MD_FAULT | SPI_FLAG_PARITY_ERR | \
                                     SPI_FLAG_UNDERRUN | SPI_FLAG_TX_BUF_EMPTY | SPI_FLAG_RX_BUF_FULL)
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
 * @addtogroup SPI_Global_Functions
 * @{
 */
int32_t SPI_StructInit(stc_spi_init_t *pstcSpiInit);
int32_t SPI_Init(CM_SPI_TypeDef *SPIx, const stc_spi_init_t *pstcSpiInit);
int32_t SPI_DeInit(CM_SPI_TypeDef *SPIx);

void SPI_IntCmd(CM_SPI_TypeDef *SPIx, uint32_t u32IntType, en_functional_state_t enNewState);
void SPI_Cmd(CM_SPI_TypeDef *SPIx, en_functional_state_t enNewState);
void SPI_WriteData(CM_SPI_TypeDef *SPIx, uint32_t u32Data);
uint32_t SPI_ReadData(const CM_SPI_TypeDef *SPIx);

en_flag_status_t SPI_GetStatus(const CM_SPI_TypeDef *SPIx, uint32_t u32Flag);
void SPI_ClearStatus(CM_SPI_TypeDef *SPIx, uint32_t u32Flag);
void SPI_SetLoopbackMode(CM_SPI_TypeDef *SPIx, uint32_t u32Mode);
void SPI_ParityCheckCmd(CM_SPI_TypeDef *SPIx, en_functional_state_t enNewState);
void SPI_SetSSValidLevel(CM_SPI_TypeDef *SPIx, uint32_t u32SSPin, uint32_t u32SSLevel);
void SPI_SetSckPolarity(CM_SPI_TypeDef *SPIx, uint32_t u32Polarity);
void SPI_SetSckPhase(CM_SPI_TypeDef *SPIx, uint32_t u32Phase);

int32_t SPI_DelayTimeConfig(CM_SPI_TypeDef *SPIx, const stc_spi_delay_t *pstcDelayConfig);
void SPI_SSPinSelect(CM_SPI_TypeDef *SPIx, uint32_t u32SSPin);
void SPI_SetReadBuf(CM_SPI_TypeDef *SPIx, uint32_t u32ReadBuf);
int32_t SPI_DelayStructInit(stc_spi_delay_t *pstcDelayConfig);

void SPI_SetCommMode(CM_SPI_TypeDef *SPIx, uint32_t u32Mode);

int32_t SPI_Trans(CM_SPI_TypeDef *SPIx, const void *pvTxBuf, uint32_t u32TxLen, uint32_t u32Timeout);
int32_t SPI_Receive(CM_SPI_TypeDef *SPIx, void *pvRxBuf, uint32_t u32RxLen, uint32_t u32Timeout);
int32_t SPI_TransReceive(CM_SPI_TypeDef *SPIx, const void *pvTxBuf, void *pvRxBuf, uint32_t u32Len, uint32_t u32Timeout);

/**
 * @}
 */

#endif /* LL_SPI_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_SPI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
