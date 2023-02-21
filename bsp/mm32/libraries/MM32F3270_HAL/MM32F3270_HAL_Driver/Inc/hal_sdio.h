/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_SDIO_H__
#define __HAL_SDIO_H__

#include "hal_common.h"

/*!
 * @addtogroup SDIO
 * @{
 */

/*!
 * @brief SDIO driver version number.
 */
#define SDIO_DRIVER_VERSION 0u /*!< sdio_0. */

/*!
 * @brief Card command return type .
 */
typedef enum
{
    SDIO_RespType_R1, /*!< 32 bit + 8 bit CRC. */
    SDIO_RespType_R2, /*!< 128 bit + 8 bit CRC, for CID and CSD. */
    SDIO_RespType_R3, /*!< 32 bit + 8 bit CRC, for OCR. */
    SDIO_RespType_R6, /*!< 32 bit + 8 bit CRC, for RCA. */
    SDIO_RespType_R7, /*!< 32 bit + 8 bit CRC, for card interface condition. */
} SDIO_RespType_Type;

/*!
* @brief SDIO data bus width.
*/
typedef enum
{
    SDIO_DataBusWidth_1b = 0u, /*!< 1-bit data bus. */
    SDIO_DataBusWidth_4b = 1u, /*!< 4-bit data bus. */
} SDIO_DataBusWidth_Type;

/*!
* @brief SDIO base clock source.
*/
typedef enum
{
    SDIO_BaseClkSrc_1MHz   = 0u, /*!< Select 1MHz clock as the clock source of SDIO module. */
    SDIO_BaseClkSrc_BusClk = 1u, /*!< Select bus clock as the clock source of SDIO module. */
} SDIO_BaseClkSrc_Type;

/*!
 * @brief The divider from base clock to port clk line speed.
*/
typedef enum
{
    SDIO_ClkLineSpeedDiv_Div2  = 0u, /*!< SDIO clk command line clock freq's divider as 2. */
    SDIO_ClkLineSpeedDiv_Div4  = 1u, /*!< SDIO clk command line clock freq's divider as 4. */
    SDIO_ClkLineSpeedDiv_Div6  = 2u, /*!< SDIO clk command line clock freq's divider as 6. */
    SDIO_ClkLineSpeedDiv_Div8  = 3u, /*!< SDIO clk command line clock freq's divider as 8. */
    SDIO_ClkLineSpeedDiv_Div10 = 4u, /*!< SDIO clk command line clock freq's divider as 10. */
    SDIO_ClkLineSpeedDiv_Div12 = 5u, /*!< SDIO clk command line clock freq's divider as 12. */
    SDIO_ClkLineSpeedDiv_Div14 = 6u, /*!< SDIO clk command line clock freq's divider as 14. */
    SDIO_ClkLineSpeedDiv_Div16 = 7u, /*!< SDIO clk command line clock freq's divider as 16. */
} SDIO_ClkLineSpeedDiv_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref SDIO_Init() to initialize the SDIO module.
 */
typedef struct
{
    uint32_t                  BusClkHz;        /*!< SDIO module clock freq. */
    SDIO_BaseClkSrc_Type      BaseClkSrc;      /*!< Select the SDIO base clock source.  */
    SDIO_ClkLineSpeedDiv_Type ClkLineSpeedDiv; /*!< Select the divider from base clock to port clk line speed. */
} SDIO_Init_Type;

/*!
 * @addtogroup SDIO_STATUS
 * @{
 */
#define SDIO_STATUS_CMD_DONE                     (1u << 0u)  /*!< Status flag when SDIO sent a command to bus. */
#define SDIO_STATUS_DAT_DONE                     (1u << 1u)  /*!< Status flag when SDIO sent a word of data to bus. */
#define SDIO_STATUS_DAT_CRC_ERR                  (1u << 2u)  /*!< Status flag when SDIO found a data crc error. */
#define SDIO_STATUS_CMD_CRC_ERR                  (1u << 3u)  /*!< Status flag when SDIO found a command crc error. */
#define SDIO_STATUS_DAT_MULTI_BLOCKS_DONE        (1u << 4u)  /*!< Status flag when SDIO sent multiple blocks of data. */
#define SDIO_STATUS_DAT_MULTI_BLOCKS_TIMEOUT     (1u << 5u)  /*!< Status flag when SDIO found a timeout of sending multiple blocks of data. */
#define SDIO_STATUS_CMD_NCR_TIMEOUT              (1u << 6u)  /*!< Status flag when SDIO found a command ncr timeout issue. */
#define SDIO_STATUS_CRC_CRC_ERR                  (1u << 7u)  /*!< Status flag when SDIO found a crc issue. */
#define SDIO_STATUS_DAT0_BUSY                    (1u << 8u)  /*!< Status flag when SDIO checked the data0 line is busy. */
#define SDIO_STATUS_DAT_BUF_FULL                 (1u << 9u)  /*!< Status flag when SDIO fifo buffer is full. */
#define SDIO_STATUS_DAT_BUF_EMPTY                (1u << 10u) /*!< Status flag when SDIO fifo buffer is empty. */
/*!
 * @}
 */

/*!
 * @addtogroup SDIO_INT
 * @{
 */
#define SDIO_INT_CMD_DONE                        (1u << 0u) /*!< Interrupt enable when SDIO sent a command to bus. */
#define SDIO_INT_DAT_DONE                        (1u << 1u) /*!< Interrupt enable when SDIO sent a word of data to bus. */
#define SDIO_INT_DAT_CRC_ERR                     (1u << 2u) /*!< Interrupt enable when SDIO found a data crc error. */
#define SDIO_INT_CMD_CRC_ERR                     (1u << 3u) /*!< Interrupt enable when SDIO found a command crc error. */
#define SDIO_INT_DAT_MULTI_BLOCKS_DONE           (1u << 4u) /*!< Interrupt enable when SDIO sent multiple blocks of data. */
#define SDIO_INT_DAT_MULTI_BLOCKS_TIMEOUT        (1u << 5u) /*!< Interrupt enable when SDIO found a timeout of sending multiple blocks of data. */
#define SDIO_INT_CMD_NCR_TIMEOUT                 (1u << 6u) /*!< Interrupt enable when SDIO found a command ncr timeout issue. */
#define SDIO_INT_CRC_CRC_ERR                     (1u << 7u) /*!< Interrupt enable when SDIO found a crc issue. */
#define SDIO_INT_DAT0_BUSY                       (1u << 8u) /*!< Interrupt enable when SDIO checked the data0 line is busy. */
/*!
 * @}
 */

/*!
 * @addtogroup SDIO_CMD_FLAG
 * @{
 */
#define SDIO_CMD_FLAG_READ_BLOCK                 (1u << 0u) /*!< SDIO command flag of reading block. */
#define SDIO_CMD_FLAG_WRITE_BLOCK                (1u << 1u) /*!< SDIO command flag of writing block. */
#define SDIO_CMD_FLAG_READ_CID_CSD               (1u << 2u) /*!< SDIO command flag of reading CID and CSD. */
#define SDIO_CMD_FLAG_WRITE_BLOCKS               (1u << 5u) /*!< SDIO command flag of writing multiple blocks. */
#define SDIO_CMD_FLAG_READ_BLOCKS                (1u << 6u) /*!< SDIO command flag of reading multiple blocks. */
#define SDIO_CMD_FLAG_ENABLE_DATA_XFER           (1u << 7u) /*!< SDIO command flag of starting the data transfer. */
/*!
 * @}
 */

/*!
 * @brief Initialize the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @param init  Pointer to the initialization structure. See to @ref SDIO_Init_Type.
 * @return None.
 */
void     SDIO_Init(SDIO_Type * SDIOx, SDIO_Init_Type * init);

/*!
 * @brief Enable the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void     SDIO_Enable(SDIO_Type * SDIOx, bool enable);

/*!
 * @brief Setup the data bus width of the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @param width SDIO data bus width. See to @ref SDIO_DataBusWidth_Type.
 * @return None.
 */
void     SDIO_SetDataBusWidth(SDIO_Type *SDIOx, SDIO_DataBusWidth_Type width);

/*!
 * @brief Get the status of the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @return SDIO module status, see to @ref SDIO_STATUS.
 */
uint32_t SDIO_GetStatus(SDIO_Type * SDIOx);

/*!
 * @brief Clear the status of the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @param flags Indicate the flags to be cleared. See to @ref SDIO_STATUS.
 * @return SDIO module status, see to @ref SDIO_STATUS.
 */
void     SDIO_ClearStatus(SDIO_Type * SDIOx, uint32_t flags);

/*!
 * @brief Enable interrupts of the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @param interrupts Interrupt code masks. See to @ref SDIO_INT.
 * @param enable 'true' to enable the indicated interrupts, 'false' to disable the indicated interrupts.
 * @return None.
 */
void     SDIO_EnableInterrupts(SDIO_Type * SDIOx, uint32_t interrupts, bool enable);

/*!
 * @brief Execute the SD command through the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @param cmd_index SD command index number.
 * @param param SD commamd parameter.
 * @param cmd_flags SD command option flags. See to @ref SDIO_CMD_FLAG.
 * @return None.
 */
void     SDIO_ExecuteCmd(SDIO_Type * SDIOx, uint8_t cmd_index, uint32_t param, uint32_t cmd_flags);

/*!
 * @brief Send data when executing the SD command through the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @param cmd_flags SD command option flags. See to @ref SDIO_CMD_FLAG.
 * @return None.
 */
void     SDIO_ExecuteData(SDIO_Type * SDIOx, uint32_t cmd_flags);

/*!
 * @brief Receive the return type at the end of executing SD command.
 *
 * @param SDIOx SDIO instance.
 * @param resp_type SD command return type. See to @ref SDIO_RespType_Type.
 * @param resp Pointer to a buffer, which would be used to keep the return value.
 * @return None.
 */
void     SDIO_RequestResp(SDIO_Type * SDIOx, SDIO_RespType_Type resp_type, uint32_t *resp);

/*!
 * @brief Put data into the FIFO inside the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @param dat Data word to be put into the FIFO.
 * @return None.
 */
void     SDIO_PutFifoData(SDIO_Type * SDIOx, uint32_t dat);

/*!
 * @brief Get data from the FIFO inside the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @return Data word from the FIFO.
 */
uint32_t SDIO_GetFifoData(SDIO_Type * SDIOx);

/*!
 * @brief Clear all data of the FIFO inside the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @return None.
 */
void     SDIO_ClearFifoData(SDIO_Type * SDIOx);

/*!
 * @brief Setup the data direction of data transfer.
 *
 * @param SDIOx SDIO instance.
 * @param write 'true' to setup as write, 'false' to setup as read.
 * @return None.
 */
void     SDIO_SwitchFifoWrite(SDIO_Type * SDIOx, bool write);

/*!
 * @brief Setup the watermark of the FIFO inside the SDIO module.
 *
 * @param SDIOx SDIO instance.
 * @param word_cnt Indicated the watermark value.
 * @return None.
 */
void     SDIO_SetFifoWatermark(SDIO_Type * SDIOx, uint32_t word_cnt);

/*!
 * @brief Enable the DMA of SDIO module
 *
 * @param SDIOx SDIO instance.
 * @param enable 'true' to enable the DMA, while 'false' to disable.
 * @return None.
 */
void     SDIO_EnableFifoDMA(SDIO_Type * SDIOx, bool enable);

/*!
 * @brief Setup count number for the read multiple block operation.
 *
 * @param SDIOx SDIO instance.
 * @param blk_cnt Indicated the count number of blocks.
 * @return None.
 */
void     SDIO_SetMultiBlockCount(SDIO_Type * SDIOx, uint32_t blk_cnt);

/*!
 * @brief Enable the wait operation when reading the FIFO.
 *
 * @param SDIOx SDIO instance.
 * @param enable 'true' to enable the wait operation, 'false' to disable this function.
 * @return None.
 */
void     SDIO_EnableFifoReadWait(SDIO_Type * SDIOx, bool enable);

/*!
 * @}
 */

#endif /* __HAL_SDIO_H__ */

