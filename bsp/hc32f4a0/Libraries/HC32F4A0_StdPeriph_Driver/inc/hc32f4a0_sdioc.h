/**
 *******************************************************************************
 * @file  hc32f4a0_sdioc.h
 * @brief This file contains all the functions prototypes of the SDIOC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
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
#ifndef __HC32F4A0_SDIOC_H__
#define __HC32F4A0_SDIOC_H__

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
 * @addtogroup DDL_SDIOC
 * @{
 */

#if (DDL_SDIOC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup SDIOC_Global_Types SDIOC Global Types
 * @{
 */

/**
 * @brief SDIOC Init structure definition
 */
typedef struct
{
    uint32_t u32Mode;                         /*!< Specifies the SDIOC work mode.
                                                   This parameter can be a value of @ref SDIOC_Mode */

    uint8_t  u8CardDetectSelect;              /*!< Specifies the SDIOC card detect source select.
                                                   This parameter can be a value of @ref SDIOC_Card_Detect_Select */

    uint8_t  u8SpeedMode;                     /*!< Specifies the SDIOC speed mode.
                                                   This parameter can be a value of @ref SDIOC_Speed_Mode */

    uint8_t  u8BusWidth;                      /*!< Specifies the SDIOC bus width.
                                                   This parameter can be a value of @ref SDIOC_Bus_Width */

    uint16_t u16ClockDiv;                     /*!< Specifies the SDIOC clock division.
                                                   This parameter can be a value of @ref SDIOC_Clock_Division */
} stc_sdioc_init_t;

/**
 * @brief SDIOC Command Init structure definition
 */
typedef struct
{
    uint32_t u32Argument;                     /*!< Specifies the SDIOC command argument. */

    uint16_t u16CmdIndex;                     /*!< Specifies the SDIOC command index.
                                                   This parameter must be a number between Min_Data = 0 and Max_Data = 63 */

    uint16_t u16CmdType;                      /*!< Specifies the SDIOC command type.
                                                   This parameter can be a value of @ref SDIOC_Command_Type */

    uint16_t u16DataLineEn;                   /*!< Specifies whether SDIOC uses data lines in current command.
                                                   This parameter can be a value of @ref SDIOC_Data_Line_Valid */

    uint16_t u16RespType;                     /*!< Specifies the SDIOC response type.
                                                   This parameter can be a value of @ref SDIOC_Response_Type */
} stc_sdioc_cmd_init_t;

/**
 * @brief SDIOC Data Init structure definition
 */
typedef struct
{
    uint16_t u16BlockSize;                    /*!< Specifies the SDIOC data block size.
                                                   This parameter must be a number between Min_Data = 1 and Max_Data = 512 */

    uint16_t u16BlockCount;                   /*!< Specifies the SDIOC data block count.
                                                   This parameter must be a number between Min_Data = 0 and Max_Data = 0xFFFF */

    uint16_t u16TransferDir;                  /*!< Specifies the SDIOC data transfer direction.
                                                   This parameter can be a value of @ref SDIOC_Transfer_Direction */

    uint16_t u16AutoCMD12En;                  /*!< Specifies the validity of the SDIOC Auto Send CMD12.
                                                   This parameter can be a value of @ref SDIOC_Auto_Send_CMD12 */

    uint16_t u16TransferMode;                 /*!< Specifies the SDIOC data transfer mode.
                                                   This parameter can be a value of @ref SDIOC_Transfer_Mode */

    uint8_t  u16DataTimeout;                  /*!< Specifies the SDIOC data timeout time.
                                                   This parameter can be a value of @ref SDIOC_Data_Timeout_Time */
} stc_sdioc_data_init_t;


/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SDIOC_Global_Macros SDIOC Global Macros
 * @{
 */

/**
 * @defgroup SDIOC_Mode SDIOC Mode
 * @{
 */
#define SDIOC_MODE_SD                           (0x00UL)              /*!< SDIOCx selects SD mode  */
#define SDIOC_MODE_MMC                          (0x01UL)              /*!< SDIOCx selects MMC mode */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Card_Detect_Select SDIOC Card Detect Select
 * @{
 */
#define SDIOC_CARD_DETECT_CD_PIN_LEVEL          (0x00U)               /*!< SDIOCx_CD(x=1~2) line is selected (for normal use)       */
#define SDIOC_CARD_DETECT_TEST_SIGNAL           (SDIOC_HOSTCON_CDSS)  /*!< The Card Detect Test Level is selected(for test purpose) */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Card_Detect_Test_Level SDIOC Card Detect Test Level
 * @{
 */
#define SDIOC_CARD_DETECT_TEST_LEVEL_LOW        (0x00U)               /*!< Card identification test signal is low level (with device insertion) */
#define SDIOC_CARD_DETECT_TEST_LEVEL_HIGH       (SDIOC_HOSTCON_CDTL)  /*!< Card identification test signal is high level (no device insertion)  */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Speed_Mode SDIOC Speed Mode
 * @{
 */
#define SDIOC_SPEED_MODE_NORMAL                 (0x00U)               /*!< Normal speed mode */
#define SDIOC_SPEED_MODE_HIGH                   (SDIOC_HOSTCON_HSEN)  /*!< High speed mode   */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Bus_Width SDIOC Bus Width
 * @{
 */
#define SDIOC_BUS_WIDTH_1BIT                    (0x00U)               /*!< The Bus width is 1 bit */
#define SDIOC_BUS_WIDTH_4BIT                    (SDIOC_HOSTCON_DW)    /*!< The Bus width is 4 bit */
#define SDIOC_BUS_WIDTH_8BIT                    (SDIOC_HOSTCON_EXDW)  /*!< The Bus width is 8 bit */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Clock_Division SDIOC Clock Division
 * @{
 */
#define SDIOC_CLOCK_DIV_1                       (0x00U)               /*!< PCLK1/1   */
#define SDIOC_CLOCK_DIV_2                       (SDIOC_CLKCON_FS_0)   /*!< PCLK1/2   */
#define SDIOC_CLOCK_DIV_4                       (SDIOC_CLKCON_FS_1)   /*!< PCLK1/4   */
#define SDIOC_CLOCK_DIV_8                       (SDIOC_CLKCON_FS_2)   /*!< PCLK1/8   */
#define SDIOC_CLOCK_DIV_16                      (SDIOC_CLKCON_FS_3)   /*!< PCLK1/16  */
#define SDIOC_CLOCK_DIV_32                      (SDIOC_CLKCON_FS_4)   /*!< PCLK1/32  */
#define SDIOC_CLOCK_DIV_64                      (SDIOC_CLKCON_FS_5)   /*!< PCLK1/64  */
#define SDIOC_CLOCK_DIV_128                     (SDIOC_CLKCON_FS_6)   /*!< PCLK1/128 */
#define SDIOC_CLOCK_DIV_256                     (SDIOC_CLKCON_FS_7)   /*!< PCLK1/256 */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Command_Type SDIOC Command Type
 * @{
 */
#define SDIOC_CMD_TYPE_NORMAL                   (0x00U)               /*!< Other commands                               */
#define SDIOC_CMD_TYPE_SUSPEND                  (SDIOC_CMD_TYP_0)     /*!< CMD52 for writing "Bus Suspend" in CCCR      */
#define SDIOC_CMD_TYPE_RESUME                   (SDIOC_CMD_TYP_1)     /*!< CMD52 for writing "Function Select" in CCCR  */
#define SDIOC_CMD_TYPE_ABORT                    (SDIOC_CMD_TYP)       /*!< CMD12, CMD52 for writing "I/O Abort" in CCCR */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Data_Line_Valid SDIOC Data Line Valid
 * @{
 */
#define SDIOC_DATA_LINE_DISABLE                 (0x00U)               /*!< The current command uses only SDIOCx_CMD(x=1~2) command line       */
#define SDIOC_DATA_LINE_ENABLE                  (SDIOC_CMD_DAT)       /*!< The current command requires the use of SDIOCx_Dy(x=1~2) data line */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Transfer_Direction SDIOC Transfer Direction
 * @{
 */
#define SDIOC_TRANSFER_DIR_TO_CARD              (0x00U)                 /*!< Write (Host to Card) */
#define SDIOC_TRANSFER_DIR_TO_HOST              (SDIOC_TRANSMODE_DDIR)  /*!< Read (Card to Host)  */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Auto_Send_CMD12 SDIOC Auto Send CMD12
 * @{
 */
#define SDIOC_AUTO_SEND_CMD12_DISABLE           (0x00U)                    /*!< Do not send autocommands                                   */
#define SDIOC_AUTO_SEND_CMD12_ENABLE            (SDIOC_TRANSMODE_ATCEN_0)  /*!< CMD12 is automatically sent after multiple block transfers */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Transfer_Mode SDIOC Transfer Mode
 * @{
 */
#define SDIOC_TRANSFER_MODE_SINGLE              (0x00U)                                       /*!< Single Block transfer        */
#define SDIOC_TRANSFER_MODE_INFINITE            (SDIOC_TRANSMODE_MULB)                        /*!< Infinite Block transfer      */
#define SDIOC_TRANSFER_MODE_MULTIPLE            (SDIOC_TRANSMODE_MULB | SDIOC_TRANSMODE_BCE)  /*!< Multiple Block transfer      */
#define SDIOC_TRANSFER_MODE_STOP_MULTIPLE       (0x8000U | SDIOC_TRANSFER_MODE_MULTIPLE)      /*!< Stop Multiple Block transfer */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Data_Timeout_Time SDIOC Data Timeout Time
 * @{
 */
#define SDIOC_DATA_TIMEOUT_CLK_2_13             (0x00U)  /*!< Timeout time: PCLK1*2^13 */
#define SDIOC_DATA_TIMEOUT_CLK_2_14             (0x01U)  /*!< Timeout time: PCLK1*2^14 */
#define SDIOC_DATA_TIMEOUT_CLK_2_15             (0x02U)  /*!< Timeout time: PCLK1*2^15 */
#define SDIOC_DATA_TIMEOUT_CLK_2_16             (0x03U)  /*!< Timeout time: PCLK1*2^16 */
#define SDIOC_DATA_TIMEOUT_CLK_2_17             (0x04U)  /*!< Timeout time: PCLK1*2^17 */
#define SDIOC_DATA_TIMEOUT_CLK_2_18             (0x05U)  /*!< Timeout time: PCLK1*2^18 */
#define SDIOC_DATA_TIMEOUT_CLK_2_19             (0x06U)  /*!< Timeout time: PCLK1*2^19 */
#define SDIOC_DATA_TIMEOUT_CLK_2_20             (0x07U)  /*!< Timeout time: PCLK1*2^20 */
#define SDIOC_DATA_TIMEOUT_CLK_2_21             (0x08U)  /*!< Timeout time: PCLK1*2^21 */
#define SDIOC_DATA_TIMEOUT_CLK_2_22             (0x09U)  /*!< Timeout time: PCLK1*2^22 */
#define SDIOC_DATA_TIMEOUT_CLK_2_23             (0x0AU)  /*!< Timeout time: PCLK1*2^23 */
#define SDIOC_DATA_TIMEOUT_CLK_2_24             (0x0BU)  /*!< Timeout time: PCLK1*2^24 */
#define SDIOC_DATA_TIMEOUT_CLK_2_25             (0x0CU)  /*!< Timeout time: PCLK1*2^25 */
#define SDIOC_DATA_TIMEOUT_CLK_2_26             (0x0DU)  /*!< Timeout time: PCLK1*2^26 */
#define SDIOC_DATA_TIMEOUT_CLK_2_27             (0x0EU)  /*!< Timeout time: PCLK1*2^27 */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Response_Register SDIOC Response Register
 * @{
 */
#define SDIOC_RESPONSE_REG_BIT0_31              (0x00U)  /*!< Command Response Register 0-31bit   */
#define SDIOC_RESPONSE_REG_BIT32_63             (0x04U)  /*!< Command Response Register 32-63bit  */
#define SDIOC_RESPONSE_REG_BIT64_95             (0x08U)  /*!< Command Response Register 64-95bit  */
#define SDIOC_RESPONSE_REG_BIT96_127            (0x0CU)  /*!< Command Response Register 96-127bit */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Software_Reset_Type SDIOC_Software_Reset_Type
 * @{
 */
#define SDIOC_SW_RESET_DATA_LINE                (SDIOC_SFTRST_RSTD)  /*!< Only part of data circuit is reset                                     */
#define SDIOC_SW_RESET_CMD_LINE                 (SDIOC_SFTRST_RSTC)  /*!< Only part of command circuit is reset                                  */
#define SDIOC_SW_RESET_ALL                      (SDIOC_SFTRST_RSTA)  /*!< Reset the entire Host Controller except for the card detection circuit */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Output_Clock_Frequency SDIOC Output Clock Frequency
 * @{
 */
#define SDIOC_OUTPUT_CLK_FREQ_400K              (400000UL)    /*!< SDIOC clock: 400KHz */
#define SDIOC_OUTPUT_CLK_FREQ_25M               (25000000UL)  /*!< SDIOC clock: 25MHz  */
#define SDIOC_OUTPUT_CLK_FREQ_26M               (26000000UL)  /*!< SDIOC clock: 26MHz  */
#define SDIOC_OUTPUT_CLK_FREQ_50M               (50000000UL)  /*!< SDIOC clock: 50MHz  */
#define SDIOC_OUTPUT_CLK_FREQ_52M               (52000000UL)  /*!< SDIOC clock: 52MHz  */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Host_Status SDIOC Host Status
 * @{
 */
#define SDIOC_HOST_FLAG_CMDL                    (SDIOC_PSTAT_CMDL)    /*!< CMD Line Level status            */
#define SDIOC_HOST_FLAG_DATL                    (SDIOC_PSTAT_DATL)    /*!< DAT[3:0] Line Level status       */
#define SDIOC_HOST_FLAG_DATL_D0                 (SDIOC_PSTAT_DATL_0)  /*!< DAT[0] Line Level status         */
#define SDIOC_HOST_FLAG_DATL_D1                 (SDIOC_PSTAT_DATL_1)  /*!< DAT[1] Line Level status         */
#define SDIOC_HOST_FLAG_DATL_D2                 (SDIOC_PSTAT_DATL_2)  /*!< DAT[2] Line Level status         */
#define SDIOC_HOST_FLAG_DATL_D3                 (SDIOC_PSTAT_DATL_3)  /*!< DAT[3] Line Level status         */
#define SDIOC_HOST_FLAG_WPL                     (SDIOC_PSTAT_WPL)     /*!< Write Protect Line Level status  */
#define SDIOC_HOST_FLAG_CDL                     (SDIOC_PSTAT_CDL)     /*!< Card Detect Line Level status    */
#define SDIOC_HOST_FLAG_CSS                     (SDIOC_PSTAT_CSS)     /*!< Device Stable Status             */
#define SDIOC_HOST_FLAG_CIN                     (SDIOC_PSTAT_CIN)     /*!< Device Inserted status           */
#define SDIOC_HOST_FLAG_BRE                     (SDIOC_PSTAT_BRE)     /*!< Data buffer full status          */
#define SDIOC_HOST_FLAG_BWE                     (SDIOC_PSTAT_BWE)     /*!< Data buffer empty status         */
#define SDIOC_HOST_FLAG_RTA                     (SDIOC_PSTAT_RTA)     /*!< Read operation status            */
#define SDIOC_HOST_FLAG_WTA                     (SDIOC_PSTAT_WTA)     /*!< Write operation status           */
#define SDIOC_HOST_FLAG_DA                      (SDIOC_PSTAT_DA)      /*!< DAT Line transfer status         */
#define SDIOC_HOST_FLAG_CID                     (SDIOC_PSTAT_CID)     /*!< Command Inhibit with data status */
#define SDIOC_HOST_FLAG_CIC                     (SDIOC_PSTAT_CIC)     /*!< Command Inhibit status           */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Normal_Error_Interrupt_Status SDIOC Normal Error Interrupt Status
 * @{
 */
#define SDIOC_NORMAL_INT_FLAG_EI                (SDIOC_NORINTST_EI)     /*!< Error Interrupt Status     */
#define SDIOC_NORMAL_INT_FLAG_CINT              (SDIOC_NORINTST_CINT)   /*!< Card Interrupt status      */
#define SDIOC_NORMAL_INT_FLAG_CRM               (SDIOC_NORINTST_CRM)    /*!< Card Removal status        */
#define SDIOC_NORMAL_INT_FLAG_CIST              (SDIOC_NORINTST_CIST)   /*!< Card Insertion status      */
#define SDIOC_NORMAL_INT_FLAG_BRR               (SDIOC_NORINTST_BRR)    /*!< Buffer Read Ready status   */
#define SDIOC_NORMAL_INT_FLAG_BWR               (SDIOC_NORINTST_BWR)    /*!< Buffer Write Ready status  */
#define SDIOC_NORMAL_INT_FLAG_BGE               (SDIOC_NORINTST_BGE)    /*!< Block Gap Event status     */
#define SDIOC_NORMAL_INT_FLAG_TC                (SDIOC_NORINTST_TC)     /*!< Transfer Complete status   */
#define SDIOC_NORMAL_INT_FLAG_CC                (SDIOC_NORINTST_CC)     /*!< Command Complete status    */
#define SDIOC_ERROR_INT_FLAG_ACE                ((uint32_t)SDIOC_ERRINTST_ACE  << 16U)  /*!< Auto CMD12 Error Status      */
#define SDIOC_ERROR_INT_FLAG_DEBE               ((uint32_t)SDIOC_ERRINTST_DEBE << 16U)  /*!< Data End Bit Error status    */
#define SDIOC_ERROR_INT_FLAG_DCE                ((uint32_t)SDIOC_ERRINTST_DCE  << 16U)  /*!< Data CRC Error status        */
#define SDIOC_ERROR_INT_FLAG_DTOE               ((uint32_t)SDIOC_ERRINTST_DTOE << 16U)  /*!< Data Timeout Error status    */
#define SDIOC_ERROR_INT_FLAG_CIE                ((uint32_t)SDIOC_ERRINTST_CIE  << 16U)  /*!< Command Index Error status   */
#define SDIOC_ERROR_INT_FLAG_CEBE               ((uint32_t)SDIOC_ERRINTST_CEBE << 16U)  /*!< Command End Bit Error status */
#define SDIOC_ERROR_INT_FLAG_CCE                ((uint32_t)SDIOC_ERRINTST_CCE  << 16U)  /*!< Command CRC Error status     */
#define SDIOC_ERROR_INT_FLAG_CTOE               ((uint32_t)SDIOC_ERRINTST_CTOE << 16U)  /*!< Command Timeout Error status */
#define SDIOC_ERROR_INT_STATIC_FLAGS            ((uint32_t)SDIOC_ERROR_INT_FLAG_ACE | SDIOC_ERROR_INT_FLAG_DEBE | \
                                                           SDIOC_ERROR_INT_FLAG_DCE | SDIOC_ERROR_INT_FLAG_DTOE | \
                                                           SDIOC_ERROR_INT_FLAG_CIE | SDIOC_ERROR_INT_FLAG_CEBE | \
                                                           SDIOC_ERROR_INT_FLAG_CCE | SDIOC_ERROR_INT_FLAG_CTOE | \
                                                           SDIOC_NORMAL_INT_FLAG_TC | SDIOC_NORMAL_INT_FLAG_CC)
/**
 * @}
 */

/**
 * @defgroup SDIOC_Normal_Error_Interrupt SDIOC Normal Error Interrupt
 * @{
 */
#define SDIOC_NORMAL_INT_CINTSEN                (SDIOC_NORINTSGEN_CINTSEN)   /*!< Card Interrupt                */
#define SDIOC_NORMAL_INT_CRMSEN                 (SDIOC_NORINTSGEN_CRMSEN)    /*!< Card Removal Interrupt        */
#define SDIOC_NORMAL_INT_CISTSEN                (SDIOC_NORINTSGEN_CISTSEN)   /*!< Card Insertion Interrupt      */
#define SDIOC_NORMAL_INT_BRRSEN                 (SDIOC_NORINTSGEN_BRRSEN)    /*!< Buffer Read Ready Interrupt   */
#define SDIOC_NORMAL_INT_BWRSEN                 (SDIOC_NORINTSGEN_BWRSEN)    /*!< Buffer Write Ready Interrupt  */
#define SDIOC_NORMAL_INT_BGESEN                 (SDIOC_NORINTSGEN_BGESEN)    /*!< Block Gap Event Interrupt     */
#define SDIOC_NORMAL_INT_TCSEN                  (SDIOC_NORINTSGEN_TCSEN)     /*!< Transfer Complete Interrupt   */
#define SDIOC_NORMAL_INT_CCSEN                  (SDIOC_NORINTSGEN_CCSEN)     /*!< Command Complete Interrupt    */
#define SDIOC_ERROR_INT_ACESEN                  ((uint32_t)SDIOC_ERRINTSGEN_ACESEN  << 16U)   /*!< Auto CMD12 Error Interrupt      */
#define SDIOC_ERROR_INT_DEBESEN                 ((uint32_t)SDIOC_ERRINTSGEN_DEBESEN << 16U)   /*!< Data End Bit Error Interrupt    */
#define SDIOC_ERROR_INT_DCESEN                  ((uint32_t)SDIOC_ERRINTSGEN_DCESEN  << 16U)   /*!< Data CRC Error Interrupt        */
#define SDIOC_ERROR_INT_DTOESEN                 ((uint32_t)SDIOC_ERRINTSGEN_DTOESEN << 16U)   /*!< Data Timeout Error Interrupt    */
#define SDIOC_ERROR_INT_CIESEN                  ((uint32_t)SDIOC_ERRINTSGEN_CIESEN  << 16U)   /*!< Command Index Error Interrupt   */
#define SDIOC_ERROR_INT_CEBESEN                 ((uint32_t)SDIOC_ERRINTSGEN_CEBESEN << 16U)   /*!< Command End Bit Error Interrupt */
#define SDIOC_ERROR_INT_CCESEN                  ((uint32_t)SDIOC_ERRINTSGEN_CCESEN  << 16U)   /*!< Command CRC Error Interrupt     */
#define SDIOC_ERROR_INT_CTOESEN                 ((uint32_t)SDIOC_ERRINTSGEN_CTOESEN << 16U)   /*!< Command Timeout Error Interrupt */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Auto_CMD_Error_Status SDIOC Auto CMD Error Status
 * @{
 */
#define SDIOC_AUTO_CMD_ERROR_FLAG_CMDE          (SDIOC_ATCERRST_CMDE)   /*!< Command Not Issued By Auto CMD12 Error Status  */
#define SDIOC_AUTO_CMD_ERROR_FLAG_IE            (SDIOC_ATCERRST_IE)     /*!< Auto CMD12 Index Error status                  */
#define SDIOC_AUTO_CMD_ERROR_FLAG_EBE           (SDIOC_ATCERRST_EBE)    /*!< Auto CMD12 End Bit Error status                */
#define SDIOC_AUTO_CMD_ERROR_FLAG_CE            (SDIOC_ATCERRST_CE)     /*!< Auto CMD12 CRC Error status                    */
#define SDIOC_AUTO_CMD_ERROR_FLAG_TOE           (SDIOC_ATCERRST_TOE)    /*!< Auto CMD12 Timeout Error status                */
#define SDIOC_AUTO_CMD_ERROR_FLAG_NE            (SDIOC_ATCERRST_NE)     /*!< Auto CMD12 Not Executed status                 */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Force_Auto_CMD_Error SDIOC Force Auto CMD Error
 * @{
 */
#define SDIOC_FORCE_AUTO_CMD_ERROR_FCMDE        (SDIOC_FEA_FCMDE)   /*!< Force Event for Command Not Issued By Auto CMD12 Error */
#define SDIOC_FORCE_AUTO_CMD_ERROR_FIE          (SDIOC_FEA_FIE)     /*!< Force Event for Auto CMD12 Index Error                 */
#define SDIOC_FORCE_AUTO_CMD_ERROR_FEBE         (SDIOC_FEA_FEBE)    /*!< Force Event for Auto CMD12 End Bit Error               */
#define SDIOC_FORCE_AUTO_CMD_ERROR_FCE          (SDIOC_FEA_FCE)     /*!< Force Event for Auto CMD12 CRC Error                   */
#define SDIOC_FORCE_AUTO_CMD_ERROR_FTOE         (SDIOC_FEA_FTOE)    /*!< Force Event for Auto CMD12 Timeout Error               */
#define SDIOC_FORCE_AUTO_CMD_ERROR_FNE          (SDIOC_FEA_FNE)     /*!< Force Event for Auto CMD12 Not Executed                */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Force_Error_Interrupt SDIOC Force Error Interrupt
 * @{
 */
#define SDIOC_FORCE_ERROR_INT_FACE              (SDIOC_FEE_FACE)    /*!< Force Event for Auto CMD12 Error       */
#define SDIOC_FORCE_ERROR_INT_FDEBE             (SDIOC_FEE_FDEBE)   /*!< Force Event for Data End Bit Error     */
#define SDIOC_FORCE_ERROR_INT_FDCE              (SDIOC_FEE_FDCE)    /*!< Force Event for Data CRC Error         */
#define SDIOC_FORCE_ERROR_INT_FDTOE             (SDIOC_FEE_FDTOE)   /*!< Force Event for Data Timeout Error     */
#define SDIOC_FORCE_ERROR_INT_FCIE              (SDIOC_FEE_FCIE)    /*!< Force Event for Command Index Error    */
#define SDIOC_FORCE_ERROR_INT_FCEBE             (SDIOC_FEE_FCEBE)   /*!< Force Event for Command End Bit Error  */
#define SDIOC_FORCE_ERROR_INT_FCCE              (SDIOC_FEE_FCCE)    /*!< Force Event for Command CRC Error      */
#define SDIOC_FORCE_ERROR_INT_FCTOE             (SDIOC_FEE_FCTOE)   /*!< Force Event for Command Timeout Error  */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Response_Type SDIOC Response Type
 * @{
 */
#define SDIOC_RESOPNE_TYPE_NO                   (0x00U)                                               /*!< No Response                        */
#define SDIOC_RESOPNE_TYPE_R2                   (SDIOC_CMD_RESTYP_0 | SDIOC_CMD_CCE)                  /*!< Command Response 2                 */
#define SDIOC_RESOPNE_TYPE_R3_R4                (SDIOC_CMD_RESTYP_1)                                  /*!< Command Response 3, 4              */
#define SDIOC_RESOPNE_TYPE_R1_R5_R6_R7          (SDIOC_CMD_RESTYP_1 | SDIOC_CMD_ICE | SDIOC_CMD_CCE)  /*!< Command Response 1, 5, 6, 7        */
#define SDIOC_RESOPNE_TYPE_R1B_R5B              (SDIOC_CMD_RESTYP   | SDIOC_CMD_ICE | SDIOC_CMD_CCE)  /*!< Command Response 1 and 5 with busy */
/**
 * @}
 */

/**
 * @defgroup SDIOC_Commands_Index SDIOC Commands Index
 * @{
 */
#define SDIOC_CMD0_GO_IDLE_STATE                (0U)   /*!< Resets the SD memory card. */
#define SDIOC_CMD1_SEND_OP_COND                 (1U)   /*!< Sends host capacity support information and activates the card's initialization process. */
#define SDIOC_CMD2_ALL_SEND_CID                 (2U)   /*!< Asks any card connected to the host to send the CID numbers on the CMD line.             */
#define SDIOC_CMD3_SEND_RELATIVE_ADDR           (3U)   /*!< Asks the card to publish a new relative address (RCA).                                   */
#define SDIOC_CMD4_SET_DSR                      (4U)   /*!< Programs the DSR of all cards.                                                           */
#define SDIOC_CMD5_IO_SEND_OP_COND              (5U)   /*!< Sends host capacity support information (HCS) and asks the accessed card to send its \
                                                            operating condition register (OCR) content in the response on the CMD line.              */
#define SDIOC_CMD6_SWITCH_FUNC                  (6U)   /*!< Checks switchable function (mode 0) and switch card function (mode 1).                   */
#define SDIOC_CMD7_SELECT_DESELECT_CARD         (7U)   /*!< Selects the card by its own relative address and gets deselected by any other address    */
#define SDIOC_CMD8_SEND_IF_COND                 (8U)   /*!< Sends SD Memory Card interface condition, which includes host supply voltage information \
                                                            and asks the card whether card supports voltage.                                         */
#define SDIOC_CMD9_SEND_CSD                     (9U)   /*!< Addressed card sends its card specific data (CSD) on the CMD line.                       */
#define SDIOC_CMD10_SEND_CID                    (10U)  /*!< Addressed card sends its card identification (CID) on the CMD line.                      */
#define SDIOC_CMD11_READ_DAT_UNTIL_STOP         (11U)  /*!< SD card doesn't support it.                                                              */
#define SDIOC_CMD12_STOP_TRANSMISSION           (12U)  /*!< Forces the card to stop transmission.                                                    */
#define SDIOC_CMD13_SEND_STATUS                 (13U)  /*!< Addressed card sends its status register.                                                */
#define SDIOC_CMD14_HS_BUSTEST_READ             (14U)  /*!< Reserved                                                                                 */
#define SDIOC_CMD15_GO_INACTIVE_STATE           (15U)  /*!< Sends an addressed card into the inactive state.                                         */
#define SDIOC_CMD16_SET_BLOCKLEN                (16U)  /*!< Sets the block length (in bytes for SDSC) for all following block commands(read, write).  \
                                                            Default block length is fixed to 512 Bytes. Not effective for SDHS and SDXC.             */
#define SDIOC_CMD17_READ_SINGLE_BLOCK           (17U)  /*!< Reads single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of fixed \
                                                            512 bytes in case of SDHC and SDXC.                                                      */
#define SDIOC_CMD18_READ_MULTIPLE_BLOCK         (18U)  /*!< Continuously transfers data blocks from card to host until interrupted by                 \
                                                            STOP_TRANSMISSION command.                                                               */
#define SDIOC_CMD19_HS_BUSTEST_WRITE            (19U)  /*!< 64 bytes tuning pattern is sent for SDR50 and SDR104.                                    */
#define SDIOC_CMD20_WRITE_DAT_UNTIL_STOP        (20U)  /*!< Speed class control command.                                                             */
#define SDIOC_CMD23_SET_BLOCK_COUNT             (23U)  /*!< Specify block count for CMD18 and CMD25.                                                 */
#define SDIOC_CMD24_WRITE_SINGLE_BLOCK          (24U)  /*!< Writes single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of fixed\
                                                            512 bytes in case of SDHC and SDXC.                                                      */
#define SDIOC_CMD25_WRITE_MULTIPLE_BLOCK        (25U)  /*!< Continuously writes blocks of data until a STOP_TRANSMISSION follows.                    */
#define SDIOC_CMD26_PROGRAM_CID                 (26U)  /*!< Reserved for manufacturers.                                                              */
#define SDIOC_CMD27_PROGRAM_CSD                 (27U)  /*!< Programming of the programmable bits of the CSD.                                         */
#define SDIOC_CMD28_SET_WRITE_PROT              (28U)  /*!< Sets the write protection bit of the addressed group.                                    */
#define SDIOC_CMD29_CLR_WRITE_PROT              (29U)  /*!< Clears the write protection bit of the addressed group.                                  */
#define SDIOC_CMD30_SEND_WRITE_PROT             (30U)  /*!< Asks the card to send the status of the write protection bits.                           */
#define SDIOC_CMD32_ERASE_WR_BLK_START          (32U)  /*!< Sets the address of the first write block to be erased. (For SD card only).              */
#define SDIOC_CMD33_ERASE_WR_BLK_END            (33U)  /*!< Sets the address of the last write block of the continuous range to be erased.           */
#define SDIOC_CMD35_ERASE_GRP_START             (35U)  /*!< Sets the address of the first write block to be erased. Reserved for each command system  \
                                                            set by switch function command (CMD6).                                                   */
#define SDIOC_CMD36_ERASE_GRP_END               (36U)  /*!< Sets the address of the last write block of the continuous range to be erased.            \
                                                            Reserved for each command system set by switch function command (CMD6).                  */
#define SDIOC_CMD38_ERASE                       (38U)  /*!< Reserved for SD security applications.                                                   */
#define SDIOC_CMD39_FAST_IO                     (39U)  /*!< SD card doesn't support it (Reserved).                                                   */
#define SDIOC_CMD40_GO_IRQ_STATE                (40U)  /*!< SD card doesn't support it (Reserved).                                                   */
#define SDIOC_CMD42_LOCK_UNLOCK                 (42U)  /*!< Sets/resets the password or lock/unlock the card. The size of the data block is set by    \
                                                            the SET_BLOCK_LEN command.                                                               */
#define SDIOC_CMD55_APP_CMD                     (55U)  /*!< Indicates to the card that the next command is an application specific command rather     \
                                                            than a standard command.                                                                 */
#define SDIOC_CMD56_GEN_CMD                     (56U)  /*!< Used either to transfer a data block to the card or to get a data block from the card     \
                                                            for general purpose/application specific commands.                                       */
#define SDIOC_CMD64_NO_CMD                      (64U)  /*!< No command                                                                               */

/**
 * @brief Following commands are SD Card Specific commands.
 *        CMD55_APP_CMD should be sent before sending these commands.
 */
#define SDIOC_ACMD6_SET_BUS_WIDTH               (6U)   /*!< (ACMD6) Defines the data bus width to be used for data transfer. The allowed data bus     \
                                                            widths are given in SCR register.                                                        */
#define SDIOC_ACMD13_SD_STATUS                  (13U)  /*!< (ACMD13) Sends the SD status.                                                            */
#define SDIOC_ACMD22_SEND_NUM_WR_BLOCKS         (22U)  /*!< (ACMD22) Sends the number of the written (without errors) write blocks. Responds with     \
                                                            32bit+CRC data block.                                                                    */
#define SDIOC_ACMD41_SD_APP_OP_COND             (41U)  /*!< (ACMD41) Sends host capacity support information (HCS) and asks the accessed card to      \
                                                            send its operating condition register (OCR) content in the response on the CMD line.     */
#define SDIOC_ACMD42_SET_CLR_CARD_DETECT        (42U)  /*!< (ACMD42) Connect/Disconnect the 50 KOhm pull-up resistor on CD/DAT3 (pin 1) of the card  */
#define SDIOC_ACMD51_SEND_SCR                   (51U)  /*!< Reads the SD Configuration Register (SCR).                                               */
#define SDIOC_ACMD52_RW_DIRECT                  (52U)  /*!< For SD I/O card only, reserved for security specification.                               */
#define SDIOC_ACMD53_RW_EXTENDED                (53U)  /*!< For SD I/O card only, reserved for security specification.                               */

/**
 * @brief Following commands are SD Card Specific security commands.
 *        CMD55_APP_CMD should be sent before sending these commands.
 */
#define SDIOC_ACMD43_GET_MKB                        (43U)
#define SDIOC_ACMD44_GET_MID                        (44U)
#define SDIOC_ACMD45_SET_CER_RN1                    (45U)
#define SDIOC_ACMD46_GET_CER_RN2                    (46U)
#define SDIOC_ACMD47_SET_CER_RES2                   (47U)
#define SDIOC_ACMD48_GET_CER_RES1                   (48U)
#define SDIOC_ACMD18_SECURE_READ_MULTIPLE_BLOCK     (18U)
#define SDIOC_ACMD25_SECURE_WRITE_MULTIPLE_BLOCK    (25U)
#define SDIOC_ACMD38_SECURE_ERASE                   (38U)
#define SDIOC_ACMD49_CHANGE_SECURE_AREA             (49U)
#define SDIOC_ACMD48_SECURE_WRITE_MKB               (48U)
/**
 * @}
 */

/**
 * @defgroup SDMMC_Error_Code SDMMC Error Code
 * @{
 */
#define SDMMC_ERROR_NONE                        (0x00000000UL)  /*!< No error                                                      */
#define SDMMC_ERROR_ADDR_OUT_OF_RANGE           (0x80000000UL)  /*!< Error when addressed block is out of range                    */
#define SDMMC_ERROR_ADDR_MISALIGNED             (0x40000000UL)  /*!< Misaligned address                                            */
#define SDMMC_ERROR_BLOCK_LEN_ERR               (0x20000000UL)  /*!< Transferred block length is not allowed for the card or the    \
                                                                     number of transferred bytes does not match the block length   */
#define SDMMC_ERROR_ERASE_SEQ_ERR               (0x10000000UL)  /*!< An error in the sequence of erase command occurs              */
#define SDMMC_ERROR_BAD_ERASE_PARAM             (0x08000000UL)  /*!< An invalid selection for erase groups                         */
#define SDMMC_ERROR_WRITE_PROT_VIOLATION        (0x04000000UL)  /*!< Attempt to program a write protect block                      */
#define SDMMC_ERROR_LOCK_UNLOCK_FAILED          (0x01000000UL)  /*!< Sequence or password error has been detected in unlock command \
                                                                     or if there was an attempt to access a locked card            */
#define SDMMC_ERROR_COM_CRC_FAILED              (0x00800000UL)  /*!< CRC check of the previous command failed                      */
#define SDMMC_ERROR_ILLEGAL_CMD                 (0x00400000UL)  /*!< Command is not legal for the card state                       */
#define SDMMC_ERROR_CARD_ECC_FAILED             (0x00200000UL)  /*!< Card internal ECC was applied but failed to correct the data  */
#define SDMMC_ERROR_CC_ERR                      (0x00100000UL)  /*!< Internal card controller error                                */
#define SDMMC_ERROR_GENERAL_UNKNOWN_ERR         (0x00080000UL)  /*!< General or unknown error                                      */
#define SDMMC_ERROR_STREAM_READ_UNDERRUN        (0x00040000UL)  /*!< The card could not sustain data reading in stream rmode       */
#define SDMMC_ERROR_STREAM_WRITE_OVERRUN        (0x00020000UL)  /*!< The card could not sustain data programming in stream mode    */
#define SDMMC_ERROR_CID_CSD_OVERWRITE           (0x00010000UL)  /*!< CID/CSD overwrite error                                       */
#define SDMMC_ERROR_WP_ERASE_SKIP               (0x00008000UL)  /*!< Only partial address space was erased                         */
#define SDMMC_ERROR_CARD_ECC_DISABLED           (0x00004000UL)  /*!< Command has been executed without using internal ECC          */
#define SDMMC_ERROR_ERASE_RESET                 (0x00002000UL)  /*!< Erase sequence was cleared before executing because an out of  \
                                                                     erase sequence command was received                           */
#define SDMMC_ERROR_CMD_AUTO_SEND               (0x00001000UL)  /*!< An error occurred in sending the command automatically        */
#define SDMMC_ERROR_CMD_INDEX                   (0x00000800UL)  /*!< The received response contains a command number error         */
#define SDMMC_ERROR_CMD_STOP_BIT                (0x00000400UL)  /*!< Command line detects low level at stop bit                    */
#define SDMMC_ERROR_CMD_CRC_FAIL                (0x00000200UL)  /*!< Command response received (but CRC check failed)              */
#define SDMMC_ERROR_CMD_TIMEOUT                 (0x00000100UL)  /*!< Command response timeout                                      */
#define SDMMC_ERROR_SWITCH_ERROR                (0x00000080UL)  /*!< The card did not switch to the expected mode as requested by   \
                                                                     the SWITCH command                                            */
#define SDMMC_ERROR_DATA_STOP_BIT               (0x00000040UL)  /*!< Data line detects low level at stop bit                       */
#define SDMMC_ERROR_DATA_CRC_FAIL               (0x00000020UL)  /*!< Data block sent/received (CRC check failed)                   */
#define SDMMC_ERROR_DATA_TIMEOUT                (0x00000010UL)  /*!< Data timeout                                                  */
#define SDMMC_ERROR_AKE_SEQ_ERR                 (0x00000008UL)  /*!< Error in sequence of authentication                           */
#define SDMMC_ERROR_INVALID_VOLTRANGE           (0x00000004UL)  /*!< Error in case of invalid voltage range                        */
#define SDMMC_ERROR_REQUEST_NOT_APPLICABLE      (0x00000002UL)  /*!< Error when command request is not applicable                  */
#define SDMMC_ERROR_UNSUPPORTED_FEATURE         (0x00000001UL)  /*!< Error when feature is not insupported                         */

#define SDMMC_CARD_ERROR_BITS_MASK              (0xFDFFE048UL)  /*!< SD/MMC Error status bits mask                                 */
/**
 * @}
 */

/**
 * @defgroup SDMMC_Card_Status_Bit SDMMC Card Status Bit
 * @{
 */
#define SDMMC_STATUS_CARD_IS_LOCKED_POS         (24U)
#define SDMMC_STATUS_CARD_IS_LOCKED             (0x02000000UL)  /*!< When set, signals that the card is locked by the host */
#define SDMMC_STATUS_CURRENT_STATE_POS          (9U)
#define SDMMC_STATUS_CURRENT_STATE              (0x00001E00UL)  /*!< The state of the card when receiving the command */
#define SDMMC_STATUS_READY_FOR_DATA_POS         (8U)
#define SDMMC_STATUS_READY_FOR_DATA             (0x00000100UL)  /*!< Corresponds to buffer empty signaling on the bus */
#define SDMMC_STATUS_APP_CMD_POS                (5U)
#define SDMMC_STATUS_APP_CMD                    (0x00000020UL)  /*!< The card will expect ACMD, or an indication that the command has been interpreted as ACMD */
/**
 * @}
 */

/**
 * @defgroup SDMMC_SCR_Register SDMMC SCR Register
 * @{
 */
#define SDMMC_SCR_PHY_SPEC_VER_1P0              (0x00000000UL)
#define SDMMC_SCR_PHY_SPEC_VER_1P1              (0x01000000UL)
#define SDMMC_SCR_PHY_SPEC_VER_2P0              (0x02000000UL)
#define SDMMC_SCR_BUS_WIDTH_4BIT                (0x00040000UL)
#define SDMMC_SCR_BUS_WIDTH_1BIT                (0x00010000UL)
/**
 * @}
 */

/**
 * @defgroup SDMMC_OCR_Register SDMMC OCR Register
 * @{
 */
#define SDMMC_OCR_HIGH_CAPACITY                 (0x40000000UL)
#define SDMMC_OCR_STD_CAPACITY                  (0x00000000UL)
/**
 * @}
 */

/**
 * @defgroup SDMMC_CSD_Register SDMMC CSD Register
 * @{
 */
/* Command Class supported */
#define SDMMC_CSD_SUPPORT_CLASS5_ERASE          (0x00000020UL)
/**
 * @}
 */

/**
 * @defgroup SDMMC_Common_Parameter SDMMC Common Parameter
 * @{
 */
#define SDMMC_DATA_TIMEOUT                      (0x0000FFFFUL)
#define SDMMC_MAX_VOLTAGE_TRIAL                 (0x0000FFFFUL)
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
 * @addtogroup SDIOC_Global_Functions
 * @{
 */
en_result_t SDIOC_DeInit(M4_SDIOC_TypeDef *SDIOCx);
en_result_t SDIOC_Init(M4_SDIOC_TypeDef *SDIOCx, const stc_sdioc_init_t *pstcSdiocInit);
en_result_t SDIOC_StructInit(stc_sdioc_init_t *pstcSdiocInit);
en_result_t SDIOC_SoftwareReset(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8ResetType);
void SDIOC_PowerCmd(M4_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewSta);
en_functional_state_t SDIOC_GetPowerState(const M4_SDIOC_TypeDef *SDIOCx);
uint32_t SDIOC_GetMode(const M4_SDIOC_TypeDef *SDIOCx);
void SDIOC_ClockCmd(M4_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewSta);
void SDIOC_SetClockDiv(M4_SDIOC_TypeDef *SDIOCx, uint16_t u16ClkDiv);
en_result_t SDIOC_GetOptimumClockDiv(uint32_t u32ClkFreq, uint16_t *pu16ClkDiv);
en_result_t SDIOC_VerifyClockDiv(uint32_t u32Mode, uint8_t u8SpeedMode, uint16_t u16ClkDiv);
en_functional_state_t SDIOC_GetDeviceInsertState(const M4_SDIOC_TypeDef *SDIOCx);
void SDIOC_SetSpeedMode(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8SpeedMode);
void SDIOC_SetBusWidth(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8BusWidth);
void SDIOC_SetCardDetectSource(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8Src);
void SDIOC_SetCardDetectTestLevel(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8Level);

en_result_t SDIOC_SendCommand(M4_SDIOC_TypeDef *SDIOCx, const stc_sdioc_cmd_init_t *pstcCmd);
en_result_t SDIOC_CmdStructInit(stc_sdioc_cmd_init_t *pstcCmd);
en_result_t SDIOC_GetResponse(M4_SDIOC_TypeDef *SDIOCx, uint8_t u8RespReg, uint32_t *pu32RespVal);
en_result_t SDIOC_ConfigData(M4_SDIOC_TypeDef *SDIOCx, const stc_sdioc_data_init_t *pstcData);
en_result_t SDIOC_DataStructInit(stc_sdioc_data_init_t *pstcData);
en_result_t SDIOC_ReadBuffer(M4_SDIOC_TypeDef *SDIOCx, uint8_t au8Data[], uint32_t u32Len);
en_result_t SDIOC_WriteBuffer(M4_SDIOC_TypeDef *SDIOCx, const uint8_t au8Data[], uint32_t u32Len);

void SDIOC_BlockGapStopCmd(M4_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewSta);
void SDIOC_RestartTransfer(M4_SDIOC_TypeDef *SDIOCx);
void SDIOC_ReadWaitCmd(M4_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewSta);
void SDIOC_BlockGapInterruptCmd(M4_SDIOC_TypeDef *SDIOCx, en_functional_state_t enNewSta);

void SDIOC_IntCmd(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32IntSrc, en_functional_state_t enNewSta);
en_functional_state_t SDIOC_GetIntEnableState(const M4_SDIOC_TypeDef *SDIOCx, uint32_t u32IntSrc);
en_flag_status_t SDIOC_GetIntStatus(const M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Flag);
void SDIOC_ClearIntStatus(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Flag);
void SDIOC_IntStatusCmd(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32IntSrc, en_functional_state_t enNewSta);
en_flag_status_t SDIOC_GetHostStatus(const M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Flag);
en_flag_status_t SDIOC_GetAutoCmdErrorStatus(const M4_SDIOC_TypeDef *SDIOCx, uint16_t u16Flag);
void SDIOC_ForceAutoCmdErrorEvent(M4_SDIOC_TypeDef *SDIOCx, uint16_t u16CmdFlag);
void SDIOC_ForceErrorInterruptEvent(M4_SDIOC_TypeDef *SDIOCx, uint16_t u16IntFlag);

/* SDMMC Commands management functions */
en_result_t SDMMC_CMD0_GoIdleState(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD2_AllSendCID(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD3_SendRelativeAddr(M4_SDIOC_TypeDef *SDIOCx, uint16_t *pu16RCA, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD6_SwitchFunc(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD7_SelectDeselectCard(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32RCA, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD8_SendInterfaceCond(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD9_SendCSD(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32RCA, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD12_StopTransmission(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD13_SendStatus(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32RCA, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD16_SetBlockLength(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32BlockLen, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD17_ReadSingleBlock(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32ReadAddr, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD18_ReadMultipleBlock(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32ReadAddr, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD24_WriteSingleBlock(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32WriteAddr, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD25_WriteMultipleBlock(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32WriteAddr, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD32_EraseBlockStartAddr(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32StartAddr, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD33_EraseBlockEndAddr(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32EndAddr, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD38_Erase(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD55_AppCmd(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrSta);

en_result_t SDMMC_ACMD6_SetBusWidth(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32BusWidth, uint32_t *pu32ErrSta);
en_result_t SDMMC_ACMD13_SendStatus(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta);
en_result_t SDMMC_ACMD41_SendOperatCond(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrSta);
en_result_t SDMMC_ACMD51_SendSCR(M4_SDIOC_TypeDef *SDIOCx, uint32_t *pu32ErrSta);

en_result_t SDMMC_CMD1_SendOperatCond(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32Argument, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD35_EraseGroupStartAddr(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32StartAddr, uint32_t *pu32ErrSta);
en_result_t SDMMC_CMD36_EraseGroupEndAddr(M4_SDIOC_TypeDef *SDIOCx, uint32_t u32EndAddr, uint32_t *pu32ErrSta);

/**
 * @}
 */

#endif /* DDL_SDIOC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_SDIOC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
