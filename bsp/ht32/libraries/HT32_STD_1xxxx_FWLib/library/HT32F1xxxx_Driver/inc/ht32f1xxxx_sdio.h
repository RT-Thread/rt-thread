/*********************************************************************************************************//**
 * @file    ht32f1xxxx_sdio.h
 * @version $Rev:: 2458         $
 * @date    $Date:: 2021-08-05 #$
 * @brief   The header file of the SDIO library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F1XXXX_SDIO_H
#define __HT32F1XXXX_SDIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup SDIO
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Exported_Types SDIO exported types
  * @{
  */
typedef struct
{
  u32 SDIO_ClockDiv;              /*!< Specify the SDIO clock divider value.
                                       This parameter can be a value between 1 and 256. */

  u32 SDIO_ClockPeriod;           /*!< Specify whether SDIO clock has longer or shorter low period
                                       when the SDIO clock divider value is odd.
                                       This parameter can be a value of @ref SDIO_Clock_Period */

  u32 SDIO_ClockPowerSave;        /*!< Specify whether SDIO clock output is enabled or disabled
                                       when the bus is idle.
                                       This parameter can be a value of @ref SDIO_Clock_Power_Save */

  u32 SDIO_BusWide;               /*!< Specify the SDIO bus width.
                                       This parameter can be a value of @ref SDIO_Bus_Wide */

  u32 SDIO_BusMode;               /*!< Specify the SDIO bus Mode.
                                       This parameter can be a value of @ref SDIO_Bus_Mode */
} SDIO_InitTypeDef;


typedef struct
{
  u32 SDIO_Argument;              /*!< Specify the SDIO command argument which is sent
                                       to a card as part of a command message. If a command
                                       contains an argument, it must be loaded into this register
                                       before writing the command to the command register */

  u32 SDIO_CmdIndex;              /*!< Specify the SDIO command index. It must be lower than 0x40.          */

  u32 SDIO_Response;              /*!< Specify the SDIO response type.
                                       This parameter can be a value of @ref SDIO_Response_Type */

  u32 SDIO_DatPresent;            /*!< Specify whether data is present on the SDIO data line
                                       after SDIO command or not.
                                       This parameter can be a value of @ref SDIO_Data_Present */

  u32 SDIO_CmdIdxChk;             /*!< Specify whether SDIO command index check function is enabled or not.
                                       This parameter can be a value of @ref SDIO_CmdIdx_Check */

  u32 SDIO_CmdCrcChk;             /*!< Specify whether SDIO command CRC check function is enabled or not.
                                       This parameter can be a value of @ref SDIO_CmdCrc_Check */
} SDIO_CmdInitTypeDef;


typedef struct
{
  u32 SDIO_DataBlockCount;        /*!< Specify the number of data block count to be transferred.
                                       This parameter can be a value between 1 and 65535. */

  u32 SDIO_DataBlockSize;         /*!< Specify the data block size for block transfer.
                                       This parameter can be a value between 1 and 2048. */

  u32 SDIO_TransferDir;           /*!< Specify the data transfer direction, whether the transfer
                                       is a read or write.
                                       This parameter can be a value of @ref SDIO_Transfer_Direction */

  u32 SDIO_TransferMode;          /*!< Specify whether data transfer is in single block or multi-block mode.
                                       This parameter can be a value of @ref SDIO_Transfer_Mode */

  u32 SDIO_DataTimeOut;           /*!< Specify the data timeout period in card bus clock periods.
                                       This parameter can be a value between 0x1 and 0x00ffffff. */

} SDIO_DataInitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Exported_Constants SDIO exported constants
  * @{
  */

/** @defgroup SDIO_Clock_Div SDIO Clock Div
  * @{
  */
#define IS_SDIO_CLOC_DIV(DIV)           ((DIV > 0) && (DIV < 256))
/**
  * @}
  */

/** @defgroup SDIO_Clock_Period SDIO Clock Period
  * @{
  */
#define SDIO_Clock_LowPeriod_Shorter    (0x00000000)
#define SDIO_Clock_LowPeriod_Longer     (0x00000008)

#define IS_SDIO_CLOCK_PERIOD(PERIOD)    (((PERIOD) == SDIO_Clock_LowPeriod_Shorter) || \
                                         ((PERIOD) == SDIO_Clock_LowPeriod_Longer))
/**
  * @}
  */

/** @defgroup SDIO_Clock_Power_Save SDIO Clock Power Save
  * @{
  */
#define SDIO_Clock_PowerSave_Disable    (0x00000000)
#define SDIO_Clock_PowerSave_StopLow    (0x00000002)
#define SDIO_Clock_PowerSave_StopHigh   (0x00000003)

#define IS_SDIO_CLOCK_POWER_SAVE(SAVE)  (((SAVE) == SDIO_Clock_PowerSave_Disable) || \
                                         ((SAVE) == SDIO_Clock_PowerSave_StopLow) || \
                                         ((SAVE) == SDIO_Clock_PowerSave_StopHigh))
/**
  * @}
  */

/** @defgroup SDIO_Bus_Wide SDIO Bus Wide
  * @{
  */
#define SDIO_BusWide_1b                 (0x00000000)
#define SDIO_BusWide_4b                 (0x00000002)

#define IS_SDIO_BUS_WIDE(WIDE)          (((WIDE) == SDIO_BusWide_1b) || \
                                         ((WIDE) == SDIO_BusWide_4b))
/**
  * @}
  */

/** @defgroup SDIO_Bus_Mode SDIO Bus Mode
  * @{
  */
#define SDIO_BusMode_NormalSpeed        (0x00000000)
#define SDIO_BusMode_HighSpeed          (0x00000004)

#define IS_SDIO_BUS_MODE(MODE)          (((MODE) == SDIO_BusMode_NormalSpeed) || \
                                         ((MODE) == SDIO_BusMode_HighSpeed))
/**
  * @}
  */

/** @defgroup SDIO_Command_Index SDIO Command Index
  * @{
  */
#define IS_SDIO_CMD_INDEX(INDEX)        ((INDEX) < 0x40)
/**
  * @}
  */

/** @defgroup SDIO_Response_Type SDIO Response Type
  * @{
  */
#define SDIO_Response_No                (0x00000000)
#define SDIO_Response_Long              (0x00000001)
#define SDIO_Response_Short             (0x00000002)

#define IS_SDIO_RESPONSE(RESPONSE)      (((RESPONSE) == SDIO_Response_No)    || \
                                         ((RESPONSE) == SDIO_Response_Short) || \
                                         ((RESPONSE) == SDIO_Response_Long))
/**
  * @}
  */

/** @defgroup SDIO_Data_Present SDIO Data Present
  * @{
  */
#define SDIO_Data_Present_No            (0x00000000)
#define SDIO_Data_Present_Yes           (0x00000020)

#define IS_SDIO_DATA_PRESENT(PRESENT)   (((PRESENT) == SDIO_Data_Present_No) || \
                                         ((PRESENT) == SDIO_Data_Present_Yes))
/**
  * @}
  */

/** @defgroup SDIO_CmdIdx_Check SDIO CmdIdx Check
  * @{
  */
#define SDIO_CmdIdxChk_No               (0x00000000)
#define SDIO_CmdIdxChk_Yes              (0x00000010)

#define IS_SDIO_CMD_IDX_CHK(CHK)        (((CHK) == SDIO_CmdIdxChk_No) || \
                                         ((CHK) == SDIO_CmdIdxChk_Yes))
/**
  * @}
  */

/** @defgroup SDIO_CmdCrc_Check SDIO CmdCrc Check
  * @{
  */
#define SDIO_CmdCrcChk_No               (0x00000000)
#define SDIO_CmdCrcChk_Yes              (0x00000008)

#define IS_SDIO_CMD_CRC_CHK(CHK)        (((CHK) == SDIO_CmdCrcChk_No) || \
                                         ((CHK) == SDIO_CmdCrcChk_Yes))
/**
  * @}
  */

/** @defgroup SDIO_Data_Block_Count SDIO Data Block Count
  * @{
  */
#define IS_SDIO_DATA_BLOCK_COUNT(COUNT) ((COUNT > 0) && (COUNT <= 65535))
/**
  * @}
  */

/** @defgroup SDIO_Data_Block_Size SDIO Data Block Size
  * @{
  */
#define IS_SDIO_DATA_BLOCK_SIZE(SIZE)   ((SIZE > 0) && (SIZE <= 2048))
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Mode SDIO Transfer Mode
  * @{
  */
#define SDIO_SingleBlock_Transfer       (0x00000000)
#define SDIO_MultiBlock_Transfer        (0x00000022)
#define SDIO_SingleBlock_DMA_Transfer   (0x00000100)
#define SDIO_MultiBlock_DMA_Transfer    (0x00000122)

#define IS_SDIO_TRANSFER_MODE(MODE)     (((MODE) == SDIO_SingleBlock_Transfer)     || \
                                         ((MODE) == SDIO_MultiBlock_Transfer)      || \
                                         ((MODE) == SDIO_SingleBlock_DMA_Transfer) || \
                                         ((MODE) == SDIO_MultiBlock_DMA_Transfer))
/**
  * @}
  */
/** @defgroup SDIO_Transfer_Direction SDIO Transfer Direction
  * @{
  */
#define SDIO_TransferDir_ToCard         (0x00000000)
#define SDIO_TransferDir_ToSDIO         (0x00000010)

#define IS_SDIO_TRANSFER_DIR(DIR)       (((DIR) == SDIO_TransferDir_ToCard) || \
                                         ((DIR) == SDIO_TransferDir_ToSDIO))
/**
  * @}
  */


/** @defgroup SDIO_Data_TimeOut SDIO Data TimeOut
  * @{
  */
#define IS_SDIO_DATA_TIMEOUT(TIME)      ((TIME > 0) && (TIME <= 0x00ffffff))
/**
  * @}
  */

/** @defgroup SDIO_Flags SDIO Flags
  * @{
  */
#define SDIO_FLAG_CMD_SEND              (0x00000001)
#define SDIO_FLAG_TRANS_END             (0x00000002)
#define SDIO_FLAG_BUF_OVERFLOW          (0x00000008)
#define SDIO_FLAG_BUF_UNDERFLOW         (0x00000010)
#define SDIO_FLAG_BUF_HALF              (0x00000020)
#define SDIO_FLAG_BUF_FULL              (0x00000040)
#define SDIO_FLAG_BUF_EMPTY             (0x00000080)
#define SDIO_FLAG_ERR                   (0x00008000)
#define SDIO_FLAG_CMD_TIMEOUT           (0x00010000)
#define SDIO_FLAG_CMD_CRCERR            (0x00020000)
#define SDIO_FLAG_CMD_ENDERR            (0x00040000)
#define SDIO_FLAG_CMD_IDXERR            (0x00080000)
#define SDIO_FLAG_DATA_TIMEOUT          (0x00100000)
#define SDIO_FLAG_DATA_CRCERR           (0x00200000)
#define SDIO_FLAG_DATA_ENDERR           (0x00400000)
#define SDIO_FLAG_CARD_INT              (0x01000000)
#define SDIO_FLAG_DAT_ERR               (0x02000000)
#define SDIO_FLAG_CMD_ERR               (0x04000000)

#define IS_SDIO_FLAG(FLAG)              (((FLAG) != 0) && (((FLAG) & 0x077F80FB) != 0))
/**
  * @}
  */

/** @defgroup SDIO_Response_Registers SDIO Response Registers
  * @{
  */
#define SDIO_RESP1                      (0x00000000)
#define SDIO_RESP2                      (0x00000004)
#define SDIO_RESP3                      (0x00000008)
#define SDIO_RESP4                      (0x0000000C)

#define IS_SDIO_RESP(RESP)              (((RESP) == SDIO_RESP1) || \
                                         ((RESP) == SDIO_RESP2) || \
                                         ((RESP) == SDIO_RESP3) || \
                                         ((RESP) == SDIO_RESP4))
/**
  * @}
  */

/** @defgroup SDIO_Interrupt_sources SDIO Interrupt sources
  * @{
  */
#define SDIO_INT_CMD_SEND               (0x00000001)
#define SDIO_INT_TRANS_END              (0x00000002)
#define SDIO_INT_BUF_OVERFLOW           (0x00000008)
#define SDIO_INT_BUF_UNDERFLOW          (0x00000010)
#define SDIO_INT_BUF_HALF               (0x00000020)
#define SDIO_INT_BUF_FULL               (0x00000040)
#define SDIO_INT_BUF_EMPTY              (0x00000080)
#define SDIO_INT_CMD_TIMEOUT            (0x00010000)
#define SDIO_INT_CMD_CRCERR             (0x00020000)
#define SDIO_INT_CMD_IDXERR             (0x00080000)
#define SDIO_INT_DATA_TIMEOUT           (0x00100000)
#define SDIO_INT_DATA_CRCERR            (0x00200000)
#define SDIO_INT_CARD_INT               (0x01000000)

#define IS_SDIO_INT(INT)                (((INT) != 0) && (((INT) & 0x013B00FB) != 0))
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Exported_Macro SDIO exported macro
  * @{
  */
#define RESET_CPSM()                    {\
                                        HT_SDIO->SWRST |= (1UL << 1);\
                                        while (HT_SDIO->SWRST & (1UL << 1));\
                                        }

#define RESET_DPSM()                    {\
                                        HT_SDIO->SWRST |= (1UL << 2);\
                                        while (HT_SDIO->SWRST & (1UL << 2));\
                                        }
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Exported_Functions SDIO exported functions
  * @{
  */
void SDIO_DeInit(void);
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct);
void SDIO_ClockCmd(ControlStatus Cmd);
u32 SDIO_ReadData(void);
void SDIO_WriteData(u32 Data);
u32 SDIO_GetFIFOCount(void);
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
u32 SDIO_GetResponse(u32 SDIO_RESP);
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct);
void SDIO_FlagConfig(u32 SDIO_FLAG, ControlStatus NewState);
FlagStatus SDIO_GetFlagStatus(u32 SDIO_FLAG);
void SDIO_ClearFlag(u32 SDIO_FLAG);
void SDIO_IntConfig(u32 SDIO_INT, ControlStatus NewState);
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

#endif
