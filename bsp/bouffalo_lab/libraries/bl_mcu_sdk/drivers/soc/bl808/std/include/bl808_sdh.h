/**
  ******************************************************************************
  * @file    bl808_sdh.h
  * @version V1.2
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2018 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL808_SDH_H__
#define __BL808_SDH_H__

#include "sdh_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SDH
 *  @{
 */

/** @defgroup  SDH_Public_Types
 *  @{
 */

/**
 *  @brief SDH status type definition
 */
typedef enum {
    SDH_STAT_SUCCESS = 0,        /*!< SDH status success */
    SDH_STAT_BUSY,               /*!< SDH status busy */
    SDH_STAT_INVLAID_PARA,       /*!< SDH status invalid parameter */
    SDH_STAT_NOT_SUPPORT,        /*!< SDH not support this feature */
    SDH_STAT_OUTOF_RANGE,        /*!< SDH out of range */
    SDH_STAT_PREPARE_DESC,       /*!< SDH status prepare ADMA descriptor */
    SDH_STAT_SEND_CMD_FAIL,      /*!< SDH status send command fail */
    SDH_STAT_SEND_DATA_FAIL,     /*!< SDH status send data fail */
    SDH_STAT_RECV_DATA_FAIL,     /*!< SDH status receive data fail */
    SDH_STAT_DMA_ADDR_NOT_ALIGN, /*!< SDH status DMA address not align */
    SDH_STAT_RETUNE_REQ,         /*!< SDH status re-tune request */
    SDH_STAT_TUNE_ERROR,         /*!< SDH status tune error */
} SDH_Stat_Type;

/**
 *  @brief SDH capability type definition
 */
typedef enum {
    SDH_CAP_SUPPORT_8BITS = 0x00000004,       /*!< SDH support 8 bits */
    SDH_CAP_SUPPORT_ADMA2 = 0x00000008,       /*!< SDH support ADMA 2 */
    SDH_CAP_SUPPORT_ADMA1 = 0x00000010,       /*!< SDH support ADMA 1 */
    SDH_CAP_SUPPORT_HIGHSPEED = 0x00000020,   /*!< SDH support SDMA */
    SDH_CAP_SUPPORT_SDMA = 0x00000040,        /*!< SDH support high speed */
    SDH_CAP_SUPPORT_SUS_RES = 0x00000080,     /*!< SDH support suspend and resume */
    SDH_CAP_SUPPORT_VLT33 = 0x00000100,       /*!< SDH support voltgae 3.3V */
    SDH_CAP_SUPPORT_VLT30 = 0x00000200,       /*!< SDH support voltage 3.0V */
    SDH_CAP_SUPPORT_VLT18 = 0x00000400,       /*!< SDH support voltage 1.8V */
    SDH_CAP_SUPPORT_SBUS_64BITS = 0x00001000, /*!< SDH support system bus 64 bits */
    SDH_CAP_SUPPORT_ASYNC_INT = 0x00002000,   /*!< SDH support async interrupt */
    SDH_CAP_SUPPORT_DDR50 = 0x00010000,       /*!< SDH support DDR 50MHz */
    SDH_CAP_SUPPORT_SDR104 = 0x00020000,      /*!< SDH support SDR 104MHz */
    SDH_CAP_SUPPORT_SDR50 = 0x00040000,       /*!< SDH support SDR 50MHz */
    SDH_CAP_SUPPORT_DRV_TYPE_A = 0x00100000,  /*!< SDH support driver type C */
    SDH_CAP_SUPPORT_DRV_TYPE_C = 0x00200000,  /*!< SDH support driver type A */
    SDH_CAP_SUPPORT_DRV_TYPE_D = 0x00400000,  /*!< SDH support driver type A */
    SDH_CAP_SUPPORT_SDR50_TUNE = 0x20000000,  /*!< SDH support SDR 50MHz tuning */
} SDH_Cap_Support_Type;

/**
 *  @brief SDH wakeup event type definition
 */
typedef enum {
    SDH_WAKEUP_EVENT_INT,    /*!< Wakeup on card interrupt */
    SDH_WAKEUP_EVENT_INSERT, /*!< Wakeup on card insertion */
    SDH_WAKEUP_EVENT_REMOVE, /*!< Wakeup on card remove */
} SDH_Wakeup_Event_Type;

/**
 *  @brief SDH trnasfer flag type definition
 */
typedef enum {
    SDH_TRANS_FLAG_NONE = 0x00000000,
    SDH_TRANS_FLAG_EN_DMA = 0x00000001,                /*!< Enable DMA */
    SDH_TRANS_FLAG_EN_BLK_COUNT = 0x00000002,          /*!< Enable block count */
    SDH_TRANS_FLAG_EN_AUTO_CMD12 = 0x00000004,         /*!< Enable auto CMD12 */
    SDH_TRANS_FLAG_EN_AUTO_CMD23 = 0x00000008,         /*!< Enable auto CMD23 */
    SDH_TRANS_FLAG_READ_DATA = 0x00000010,             /*!< Enable read data */
    SDH_TRANS_FLAG_MULTI_BLK = 0x00000020,             /*!< Enable multi-block data operation */
    SDH_TRANS_FLAG_RESP_136BITS = 0x00010000,          /*!< Response is 136 bits length */
    SDH_TRANS_FLAG_RESP_48BITS = 0x00020000,           /*!< Response is 48 bits length */
    SDH_TRANS_FLAG_RESP_48BITS_WITH_BUSY = 0x00030000, /*!< Response is 48 bits length with busy status */
    SDH_TRANS_FLAG_EN_CRC_CHECK = 0x00080000,          /*!< Enable CRC check */
    SDH_TRANS_FLAG_EN_INDEX_CHECK = 0x00100000,        /*!< Enable index check */
    SDH_TRANS_FLAG_DATA_PRESENT = 0x00200000,          /*!< Data present */
    SDH_TRANS_FLAG_SUSPEND = 0x00400000,               /*!< Suspend command */
    SDH_TRANS_FLAG_RESUME = 0x00800000,                /*!< Resume command */
    SDH_TRANS_FLAG_ABORT = 0x00C00000,                 /*!< Abort command */
} SDH_Trans_Flag_Type;

/**
 *  @brief SDH present flag type definition
 */
typedef enum {
    SDH_PRESENT_FLAG_CMD_INHBIT = 0x00000001,       /*!< Command inhbit */
    SDH_PRESENT_FLAG_DATA_INHBIT = 0x00000002,      /*!< Data inhbit */
    SDH_PRESENT_FLAG_DATA_LINE_ACTIVE = 0x00000004, /*!< Data line active */
    SDH_PRESENT_FLAG_RETUNE_REQ = 0x00000008,       /*!< Retuning request */
    SDH_PRESENT_FLAG_TX_ACTIVE = 0x00000100,        /*!< Write trnasfer atcive */
    SDH_PRESENT_FLAG_RX_ACTIVE = 0x00000200,        /*!< Read transfer active */
    SDH_PRESENT_FLAG_BUF_WRITE_ENABLE = 0x00000400, /*!< Buffer write enabled */
    SDH_PRESENT_FLAG_BUF_READ_ENABLE = 0x00000800,  /*!< Buffer read enabled */
    SDH_PRESENT_FLAG_CARD_INSERT = 0x00010000,      /*!< Card intert */
    SDH_PRESENT_FLAG_CARD_STABLE = 0x00020000,      /*!< Card stable */
    SDH_PRESENT_FLAG_CARD_DET = 0x00040000,         /*!< Card detect */
    SDH_PRESENT_FLAG_CARD_WP = 0x00080000,          /*!< Card write protect */
    SDH_PRESENT_FLAG_DATA0_LINE_LEVEL = 0x00100000, /*!< Data 0 line signal level */
    SDH_PRESENT_FLAG_DATA1_LINE_LEVEL = 0x00200000, /*!< Data 1 line signal level */
    SDH_PRESENT_FLAG_DATA2_LINE_LEVEL = 0x00400000, /*!< Data 2 line signal level */
    SDH_PRESENT_FLAG_DATA3_LINE_LEVEL = 0x00800000, /*!< Data 3 line signal level */
    SDH_PRESENT_FLAG_CMD_LINE_LEVEL = 0x01000000,   /*!< Command line signal level */
} SDH_Present_Flag_Type;

/**
 *  @brief SDH interrupt type definition
 */
#define SDH_INT_CMD_COMPLETED      ((uint32_t)(0x00000001)) /*!< SDH command complete interrupt */
#define SDH_INT_DATA_COMPLETED     ((uint32_t)(0x00000002)) /*!< SDH data complete interrupt */
#define SDH_INT_BLK_GAP_EVENT      ((uint32_t)(0x00000004)) /*!< SDH block gap event interrupt */
#define SDH_INT_DMA_COMPLETED      ((uint32_t)(0x00000008)) /*!< SDH DMA complete interrupt */
#define SDH_INT_BUFFER_WRITE_READY ((uint32_t)(0x00000010)) /*!< SDH buffer write ready interrupt */
#define SDH_INT_BUFFER_READ_READY  ((uint32_t)(0x00000020)) /*!< SDH buffer read ready interrupt */
#define SDH_INT_CARD_INSERT        ((uint32_t)(0x00000040)) /*!< SDH card insert interrupt */
#define SDH_INT_CARD_REMOVE        ((uint32_t)(0x00000080)) /*!< SDH card remove interrupt */
#define SDH_INT_CARD               ((uint32_t)(0x00000100)) /*!< SDH card produce interrupt */
#define SDH_INT_DRIVER_TA          ((uint32_t)(0x00000200)) /*!< SDH driver type A interrupt */
#define SDH_INT_DRIVER_TB          ((uint32_t)(0x00000400)) /*!< SDH driver type B interrupt */
#define SDH_INT_DRIVER_TC          ((uint32_t)(0x00000800)) /*!< SDH driver type C interrupt */
#define SDH_INT_RETUNE_EVENT       ((uint32_t)(0x00001000)) /*!< SDH re-tuning event interrupt */
#define SDH_INT_CMD_TIMEOUT        ((uint32_t)(0x00010000)) /*!< SDH command timeout interrupt */
#define SDH_INT_CMD_CRC_ERROR      ((uint32_t)(0x00020000)) /*!< SDH command CRC error interrupt */
#define SDH_INT_CMD_ENDBIT_ERROR   ((uint32_t)(0x00040000)) /*!< SDH command endbit error interrupt */
#define SDH_INT_CMD_INDEX_ERROR    ((uint32_t)(0x00080000)) /*!< SDH command index error interrupt */
#define SDH_INT_DATA_TIMEOUT       ((uint32_t)(0x00100000)) /*!< SDH data timeout interrupt */
#define SDH_INT_DATA_CRC_ERROR     ((uint32_t)(0x00200000)) /*!< SDH data CRC error interrupt */
#define SDH_INT_DATA_ENDBIT_ERROR  ((uint32_t)(0x00400000)) /*!< SDH data endbit error interrupt */
#define SDH_INT_CURRENT_ERROR      ((uint32_t)(0x00800000)) /*!< SDH current error interrupt */
#define SDH_INT_AUTO_CMD12_ERROR   ((uint32_t)(0x01000000)) /*!< SDH auto command12 error */
#define SDH_INT_DMA_ERROR          ((uint32_t)(0x02000000)) /*!< SDH DMA error interrupt */
#define SDH_INT_TUNE_ERROR         ((uint32_t)(0x04000000)) /*!< SDH tuning maybe fail,this bit is set when an unrecoverable error is detected in a tuning circuit except during tuning procedure */
#define SDH_INT_SPI_ERROR          ((uint32_t)(0x10000000)) /*!< SDH SPI mode error,read  <SPI Error Token> field in the SPI mode register */
#define SDH_INT_AXI_RESP_ERROR     ((uint32_t)(0x20000000)) /*!< SDH AXI bus response error */
#define SDH_INT_CPL_TIMEOUT_ERROR  ((uint32_t)(0x40000000)) /*!< SDH command completion signal timeout error,this field is applicable for CE-ATA mode only */
#define SDH_INT_CRC_STAT_ERROR     ((uint32_t)(0x80000000)) /*!< SDH CRC status start bit or CRC status end bit or boot ack status, returned from the card in write transaction has errors */
#define SDH_INT_CMD_ERRORS         ((uint32_t)(0x000f0000)) /*!< SDH all command errors */
#define SDH_INT_DATA_ERRORS        ((uint32_t)(0x01700000)) /*!< SDH all data errors */
#define SDH_INT_ALL                ((uint32_t)(0xffffffff)) /*!< SDH all interrupt */

/**
 *  @brief SDH boot mode type definition
 */
typedef enum {
    SDH_BOOT_MODE_NORMAL, /*!< SDH normal boot mode */
    SDH_BOOT_MODE_ALT,    /*!< SDH alternative boot mode */
} SDH_Boot_Mode_Type;

/**
 *  @brief SDH auto command 12 error status type definition
 */
typedef enum {
    SDH_AUTO_CMD12_ERR_NOT_EXE,   /*!< SDH auto command not execute error */
    SDH_AUTO_CMD12_ERR_TIMEOUT,   /*!< SDH auto command timeout error */
    SDH_AUTO_CMD12_ERR_ENDBIT,    /*!< SDH auto command endbit error */
    SDH_AUTO_CMD12_ERR_INDEX,     /*!< SDH auto command index error */
    SDH_AUTO_CMD12_ERR_CRC,       /*!< SDH auto command CRC error */
    SDH_AUTO_CMD12_ERR_NOT_ISSUE, /*!< SDH auto command not issue error */
} SDH_AUTO_CMD12_ERR_Type;

/**
 *  @brief SDH ADMA error type definition
 */
typedef enum {
    SDH_ADMA_ERR_LEN_MISMATCH, /*!< SDH ADMA length mismatch */
    SDH_ADMA_ERR_DESC_ERROR,   /*!< SDH ADMA descriptor error */
} SDH_ADMA_ERR_Type;

/**
 *  @brief SDH ADMA error status type definition
 */
typedef enum {
    SDH_ADMA_ERR_STAT_STOP_DMA,     /*!< SDH ADMA stop */
    SDH_ADMA_ERR_STAT_FETCH_DESC,   /*!< SDH ADMA fetch descriptor */
    SDH_ADMA_ERR_STAT_CHANGE_ADDR,  /*!< SDH ADMA change address */
    SDH_ADMA_ERR_STAT_TRANS_DATA,   /*!< SDH ADMA transfer data */
    SDH_ADMA_ERR_STAT_INVALID_LEN,  /*!< SDH ADMA invalid length */
    SDH_ADMA_ERR_STAT_INVALID_DESC, /*!< SDH ADMA invalid descriptor */
} SDH_ADMA_ERR_Stat_Type;

/**
 *  @brief SDH force event type definition
 */
typedef enum {
    SDH_FORCE_EVENT_AUTO_CMD12_NOT_EXE,     /*!< SDH force event auto command 12 not executed */
    SDH_FORCE_EVENT_AUTO_CMD12_TIMEOUT,     /*!< SDH force event auto command 12 timeout */
    SDH_FORCE_EVENT_AUTO_CMD12_CRC_ERROR,   /*!< SDH force event auto command 12 crc error */
    SDH_FORCE_EVENT_AUTO_CMD12_INDEX_ERROR, /*!< SDH force event auto command 12 index error */
    SDH_FORCE_EVENT_AUTO_CMD12_NOT_ISSUE,   /*!< SDH force event auto command 12 not issue */
    SDH_FORCE_EVENT_ENDBIT_ERROR,           /*!< SDH force event end bit error */
    SDH_FORCE_EVENT_CMD_TIMEOUT,            /*!< SDH force event command timeout */
    SDH_FORCE_EVENT_CMD_CRC_ERROR,          /*!< SDH force event command crc error */
    SDH_FORCE_EVENT_CMD_ENDBIT_ERROR,       /*!< SDH force event command end bit error */
    SDH_FORCE_EVENT_CMD_INDEX_ERROR,        /*!< SDH force event command index error */
    SDH_FORCE_EVENT_DATA_TIMEOUT,           /*!< SDH force event data timeout */
    SDH_FORCE_EVENT_DATA_CRC_ERROR,         /*!< SDH force event data crc error */
    SDH_FORCE_EVENT_DATA_ENDBIT_ERROR,      /*!< SDH force event data end bit error */
    SDH_FORCE_EVENT_DATA_INDEX_ERROR,       /*!< SDH force event data index error */
    SDH_FORCE_EVENT_AUTO_CMD12_ERROR,       /*!< SDH force event auto command 12 error */
    SDH_FORCE_EVENT_CARD_INT,               /*!< SDH force event card interrupt */
    SDH_FORCE_EVENT_DMA_ERROR,              /*!< SDH force event DMA error */
} SDH_Force_Event_Type;

/**
 *  @brief SDH speed mode type definition
 */
typedef enum {
    SDH_SPEED_MODE_SDR12,  /*!< SDH speed :12.5MHZ */
    SDH_SPEED_MODE_SDR25,  /*!< SDH speed :25MHZ */
    SDH_SPEED_MODE_SDR50,  /*!< SDH speed :50MHZ */
    SDH_SPEED_MODE_SDR104, /*!< SDH speed :104MHZ */
    SDH_SPEED_MODE_DDR50,  /*!< SDH speed :50MHZ (DDR mode) */
} SDH_Speed_Mode_Type;

/**
 *  @brief SDH data bus width type definition
 */
typedef enum {
    SDH_DATA_BUS_WIDTH_1BIT,  /*!< SDH data bus width 1 bit */
    SDH_DATA_BUS_WIDTH_4BITS, /*!< SDH data bus width 4 bits */
    SDH_DATA_BUS_WIDTH_8BITS, /*!< SDH data bus width 8 bits */
} SDH_Data_Bus_Width_Type;

/**
 *  @brief SDH voltage type definition
 */
typedef enum {
    SDH_VOLTAGE_3P3V = 0x07, /*!< SDH voltage 3.3V */
    SDH_VOLTAGE_3P0V = 0x06, /*!< SDH voltage 3.0V */
    SDH_VOLTAGE_1P8V = 0x05, /*!< SDH voltage 1.8V */
} SDH_Voltage_Type;

/**
 *  @brief SDH DMA mode type definition
 */
typedef enum {
    SDH_DMA_MODE_SIMPLE, /*!< SDH DMA mode:simple */
    SDH_DMA_MODE_ADMA1,  /*!< SDH DMA mode:ADMA1 */
    SDH_DMA_MODE_ADMA2,  /*!< SDH DMA mode:ADMA2 */
} SDH_DMA_Mode_Type;

/**
 *  @brief SDH control flag type definition
 */
typedef enum {
    SDH_CTRL_FLAG_STOP_AT_BLK_GAP,         /*!< SDH control flag: stop at block gap */
    SDH_CTRL_FLAG_READ_WAIT,               /*!< SDH control flag: read wait */
    SDH_CTRL_FLAG_INT_AT_BLK_GAP,          /*!< SDH control flag: interrupt at block gap */
    SDH_CTRL_FLAG_RAED_DONE_WITHOUT_8CLKS, /*!< SDH control flag: read done without 8 clks for block gap */
    SDH_CTRL_FLAG_EXACT_BLK_NUM_READ,      /*!< SDH control flag: Exact block number read */
} SDH_Ctrl_Flag_Type;

/**
 *  @brief SDH Command type definition
 */
typedef enum {
    SDH_CMD_NORMAL,  /*!< SDH command type:normal */
    SDH_CMD_SUSPEND, /*!< SDH command type:suspend */
    SDH_CMD_RESUME,  /*!< SDH command type:resume */
    SDH_CMD_ABORT,   /*!< SDH command type:abort */
    SDH_CMD_EMPTY,   /*!< SDH command type:empty */
} SDH_Cmd_Type;

/**
 *  @brief SDH response type definition
 */
typedef enum {
    SDH_RESP_NONE, /*!< SDH response type:none */
    SDH_RESP_136LEN,
    SDH_RESP_48LEN,
    SDH_RESP_48LEN_BUSY,
    SDH_RESP_R1,  /*!< SDH response type:r1 */
    SDH_RESP_R1B, /*!< SDH response type:r1b */
    SDH_RESP_R2,  /*!< SDH response type:r2 */
    SDH_RESP_R3,  /*!< SDH response type:r3 */
    SDH_RESP_R4,  /*!< SDH response type:r4 */
    SDH_RESP_R5,  /*!< SDH response type:r5 */
    SDH_RESP_R5B, /*!< SDH response type:r5b */
    SDH_RESP_R6,  /*!< SDH response type:r6 */
    SDH_RESP_R7,  /*!< SDH response type:r7 */
} SDH_Resp_Type;

/**
 *  @brief SDH ADMA descriptor chain type definition
 */
typedef enum {
    SDH_ADMA_FLAG_SINGLE_DESC, /*!< SDH transfer a single ADMA descriptor */
    SDH_ADMA_FLAG_MULTI_DESC,  /*!< SDH create multiple ADMA descriptor within the ADMA table(mmc boot mode) */
} SDH_ADMA_Flag_Type;

/**
 *  @brief SDH ADMA1 descriptor flag type definition
 */
typedef enum {
    SDH_ADMA1_DESC_FLAG_VALID = 0X01,    /*!< SDH ADMA1 descriptor valid flag */
    SDH_ADMA1_DESC_FLAG_END = 0X02,      /*!< SDH ADMA1 descriptor end flag */
    SDH_ADMA1_DESC_FLAG_INT = 0X04,      /*!< SDH ADMA1 descriptor interrupt flag */
    SDH_ADMA1_DESC_FLAG_ACTIVE1 = 0X10,  /*!< SDH ADMA1 descriptor atcive1 flag */
    SDH_ADMA1_DESC_FLAG_ACTIVE2 = 0X20,  /*!< SDH ADMA1 descriptor active2 flag */
    SDH_ADMA1_DESC_FLAG_TRANSFER = 0x21, /*!< SDH ADMA1 trnasfer descriptor flag\ */
    SDH_ADMA1_DESC_FLAG_LINK = 0x31,     /*!< SDH ADMA1 link descriptor flag */
    SDH_ADMA1_DESC_FLAG_SETLEN = 0x11,   /*!< SDH ADMA1 set length descriptor flag */
} SDH_ADMA1_Desc_Flag_Type;

/**
 *  @brief SDH ADMA2 descriptor flag type definition
 */
typedef enum {
    SDH_ADMA2_DESC_FLAG_VALID = 0X01,    /*!< SDH ADMA2 descriptor valid flag */
    SDH_ADMA2_DESC_FLAG_END = 0X02,      /*!< SDH ADMA2 descriptor end flag */
    SDH_ADMA2_DESC_FLAG_INT = 0X04,      /*!< SDH ADMA2 descriptor interrupt flag */
    SDH_ADMA2_DESC_FLAG_ACTIVE1 = 0X10,  /*!< SDH ADMA2 descriptor atcive1 flag */
    SDH_ADMA2_DESC_FLAG_ACTIVE2 = 0X20,  /*!< SDH ADMA2 descriptor active2 flag */
    SDH_ADMA2_DESC_FLAG_TRANSFER = 0x21, /*!< SDH ADMA2 trnasfer descriptor flag\ */
    SDH_ADMA2_DESC_FLAG_LINK = 0x31,     /*!< SDH ADMA2 link descriptor flag */
} SDH_ADMA2_Desc_Flag_Type;

/**
 *  @brief SDH burst length type definition
 */
typedef enum {
    SDH_BUSRT_INCR,  /*!< SDH burst length incremental */
    SDH_BUSRT_INCR4, /*!< SDH ADMA2 length INCR4 */
    SDH_BUSRT_WRAP4, /*!< SDH ADMA2 length Wrap 4 */
} SDH_Burst_Type;

/**
 *  @brief SDH FIFO threshold type definition
 */
typedef enum {
    SDH_FIFO_THRESHOLD_64_BYTES,  /*!< SDH FIFO threshold is 64 bytes to generate DMA request */
    SDH_FIFO_THRESHOLD_128_BYTES, /*!< SDH FIFO threshold is 128 bytes to generate DMA request */
    SDH_FIFO_THRESHOLD_192_BYTES, /*!< SDH FIFO threshold is 192 bytes to generate DMA request */
    SDH_FIFO_THRESHOLD_256_BYTES, /*!< SDH FIFO threshold is 256 bytes to generate DMA request */
} SDH_FIFO_Threshold_Type;

/**
 *  @brief SDH burst length type definition
 */
typedef enum {
    SDH_BURST_SIZE_32_BYTES,  /*!< SDH busrt size is 32 bytes */
    SDH_BURST_SIZE_64_BYTES,  /*!< SDH busrt size is 64 bytes */
    SDH_BURST_SIZE_128_BYTES, /*!< SDH busrt size is 128 bytes */
    SDH_BURST_SIZE_256_BYTES, /*!< SDH busrt size is 256 bytes */
} SDH_Burst_Size_Type;

/**
 *  @brief SDH transferd data type definition
 */
typedef enum {
    SDH_TRANS_DATA_NORMAL,    /*!< SDH transfer normal data */
    SDH_TRANS_DATA_TUNING,    /*!< SDH transfer tuning data */
    SDH_TRANS_DATA_BOOT,      /*!< SDH transfer boot data */
    SDH_TRANS_DATA_BOOT_CONT, /*!< SDH transfer boot data continous */
} SDH_Trans_Data_Type;

/**
 *  @brief SDH ADMA2 descriptor structure type definition
 */
typedef struct
{
    uint32_t attribute; /*!< SDH ADMA2 descriptor attribute */
    uint32_t address;   /*!< SDH ADMA2 descriptor address pointer */
} SDH_ADMA2_Desc_Type;
/**
 *  @brief SDH capability structure type definition
 */
typedef struct
{
    uint32_t sdVersion;      /*!< SDH support SD card/sdio version */
    uint32_t mmcVersion;     /*!< SDH support emmc card version */
    uint32_t maxBlockLength; /*!< SDH maximum block length united as byte */
    uint32_t maxBlockCount;  /*!< SDH maximum block count can be set one time */
    uint32_t flags;          /*!< SDH capability flags to indicate the support information */
} SDH_Cap_Cfg_Type;

/**
 *  @brief SDH boot config structure type definition
 */
typedef struct
{
    uint32_t ackTimeoutCount;         /*!< SDH timeout value for the boot ACK. The available range is 0 ~ 15 */
    SDH_Boot_Mode_Type bootMode;      /*!< SDH boot mode selection */
    uint32_t blockCount;              /*!< SDH stop at block gap value of automatic mode. Available range is 0 ~ 65535 */
    uint32_t blockSize;               /*!< SDH block size */
    uint8_t enableBootAck;            /*!< SDH enable or disable boot ACK */
    uint8_t enableAutoStopAtBlockGap; /*!< SDH enable or disable auto stop at block gap function in boot period */
} SDH_Boot_Cfg_Type;

/**
 *  @brief SDH config structure type definition
 */
typedef struct
{
    SDH_Speed_Mode_Type speed;         /*!< SDH host controller speed */
    BL_Fun_Type vlot18Enable;          /*!< SDH enable 1.8V */
    BL_Fun_Type highSpeed;             /*!< SDH enable high speed */
    SDH_Data_Bus_Width_Type dataWidth; /*!< SDH data bus width */
    SDH_Voltage_Type volt;             /*!< SDH voltage */
    uint32_t srcClock;                 /*!< SDH source clock frequency in HZ */
    uint32_t busClock;                 /*!< SDH bus clock frequency in HZ */
    uint32_t dataTimeout;              /*!< SDH data timeout value */
    uint8_t readWatermarkLevel;        /*!< SDH watermark level for DMA read operation. Available range is 1 ~ 128. */
    uint8_t writeWatermarkLevel;       /*!< SDH watermark level for DMA write operation. Available range is 1 ~ 128. */
    uint8_t readBurstLen;              /*!< SDH read burst len */
    uint8_t writeBurstLen;             /*!< SDH write burst len */
} SDH_Cfg_Type;

/**
 *  @brief SDH config structure type definition
 */
typedef struct
{
    BL_Fun_Type enableAutoCommand12; /*!< SDH enable auto CMD12 */
    BL_Fun_Type enableAutoCommand23; /*!< SDH enable auto CMD23 */
    BL_Fun_Type enableIgnoreError;   /*!< SDH enable to ignore error event to read/write all the data */
    SDH_Trans_Data_Type dataType;    /*!< SDH this is used to distinguish the normal/tuning/boot data */
    uint32_t blockSize;              /*!< SDH block size */
    uint32_t blockCount;             /*!< SDH block count */
    uint32_t rxDataLen;              /*!< SDH RX data length */
    uint32_t *rxData;                /*!< SDH buffer to save data read */
    const uint32_t *txData;          /*!< SDH data buffer to write */
    uint32_t txDataLen;              /*!< SDH TX data length */
} SDH_Data_Cfg_Type;

/**
 *  @brief SDH command config structure type definition
 */
typedef struct
{
    uint32_t index;         /*!< SDH command index */
    uint32_t argument;      /*!< SDH command argument */
    SDH_Cmd_Type type;      /*!< SDH command type */
    SDH_Resp_Type respType; /*!< SDH command response type */
    uint32_t response[4U];  /*!< SDH response for this command */
    uint32_t flag;          /*!< SDH cmd flag */
} SDH_CMD_Cfg_Type;

/**
 *  @brief SDH DMA config structure type definition
 */
typedef struct
{
    SDH_DMA_Mode_Type dmaMode; /*!< SDH DMA mode */
    //SDH_Burst_Type burstType;               /*!< SDH burst type config */
    SDH_Burst_Size_Type burstSize;         /*!< SDH DMA burst size type */
    SDH_FIFO_Threshold_Type fifoThreshold; /*!< SDH FIFO threshold */
    uint32_t *admaEntries;                 /*!< SDH ADMA table entries address */
    uint32_t maxEntries;                   /*!< SDH ADMA table entries size */
} SDH_DMA_Cfg_Type;

/**
 *  @brief SDH transfer config structure type definition
 */
typedef struct
{
    SDH_Data_Cfg_Type *dataCfg; /*!< SDH data config */
    SDH_CMD_Cfg_Type *cmdCfg;   /*!< SDH command config */
} SDH_Trans_Cfg_Type;

typedef struct SDH_Handle_Cfg_Tag SDH_Handle_Cfg_Type;

/**
 *  @brief SDH transfer callback function config structure type definition
 */
typedef struct
{
    void (*SDH_CallBack_CardInserted)(void *userData);                                                           /*!< SDH card inserted occurs when DAT3/CD pin is for card detect */
    void (*SDH_CallBack_CardRemoved)(void *userData);                                                            /*!< SDH card removed occurs */
    void (*SDH_CallBack_SdioInterrupt)(void *userData);                                                          /*!< SDH SDIO card interrupt occurs */
    void (*SDH_CallBack_BlockGap)(void *userData);                                                               /*!< SDH stopped at block gap event */
    void (*SDH_CallBack_TransferFinished)(SDH_Handle_Cfg_Type *handle, SDH_Stat_Type status, void *userData);    /*!< SDH transfer complete callback */
    void (*SDH_CMDCallBack_TransferFinished)(SDH_Handle_Cfg_Type *handle, SDH_Stat_Type status, void *userData); /*!< SDH transfer complete callback */
    void (*SDH_CallBack_ReTuning)(void *userData);                                                               /*!< SDH handle the re-tuning */
    void (*SDH_CallBack_Vendor)(void *userData);                                                                 /*!< SDH handle vendor specified interrupt callback */
} SDH_Trans_Callback_Cfg_Type;

struct SDH_Handle_Cfg_Tag {
    SDH_Data_Cfg_Type *dataCfg;           /*!< SDH data config to transfer */
    SDH_CMD_Cfg_Type *cmdCfg;             /*!< SDH command config to transfer */
    uint32_t intFlag;                     /*!< SDH interrupt flags of last transaction */
    SDH_Trans_Callback_Cfg_Type callBack; /*!< SDH callback function */
    void *userData;                       /*!< SDH parameter for transfer complete callback */
};

/*@} end of group SDH_Public_Types */

/** @defgroup  SDH_Public_Constants
 *  @{
 */

/** @defgroup  SDH_STAT_TYPE
 *  @{
 */
#define IS_SDH_STAT_TYPE(type) (((type) == SDH_STAT_SUCCESS) ||            \
                                ((type) == SDH_STAT_BUSY) ||               \
                                ((type) == SDH_STAT_INVLAID_PARA) ||       \
                                ((type) == SDH_STAT_NOT_SUPPORT) ||        \
                                ((type) == SDH_STAT_OUTOF_RANGE) ||        \
                                ((type) == SDH_STAT_PREPARE_DESC) ||       \
                                ((type) == SDH_STAT_SEND_CMD_FAIL) ||      \
                                ((type) == SDH_STAT_SEND_DATA_FAIL) ||     \
                                ((type) == SDH_STAT_RECV_DATA_FAIL) ||     \
                                ((type) == SDH_STAT_DMA_ADDR_NOT_ALIGN) || \
                                ((type) == SDH_STAT_RETUNE_REQ) ||         \
                                ((type) == SDH_STAT_TUNE_ERROR))

/** @defgroup  SDH_CAP_SUPPORT_TYPE
 *  @{
 */
#define IS_SDH_CAP_SUPPORT_TYPE(type) (((type) == SDH_CAP_SUPPORT_8BITS) ||       \
                                       ((type) == SDH_CAP_SUPPORT_ADMA2) ||       \
                                       ((type) == SDH_CAP_SUPPORT_ADMA1) ||       \
                                       ((type) == SDH_CAP_SUPPORT_HIGHSPEED) ||   \
                                       ((type) == SDH_CAP_SUPPORT_SDMA) ||        \
                                       ((type) == SDH_CAP_SUPPORT_SUS_RES) ||     \
                                       ((type) == SDH_CAP_SUPPORT_VLT33) ||       \
                                       ((type) == SDH_CAP_SUPPORT_VLT30) ||       \
                                       ((type) == SDH_CAP_SUPPORT_VLT18) ||       \
                                       ((type) == SDH_CAP_SUPPORT_SBUS_64BITS) || \
                                       ((type) == SDH_CAP_SUPPORT_ASYNC_INT) ||   \
                                       ((type) == SDH_CAP_SUPPORT_DDR50) ||       \
                                       ((type) == SDH_CAP_SUPPORT_SDR104) ||      \
                                       ((type) == SDH_CAP_SUPPORT_SDR50) ||       \
                                       ((type) == SDH_CAP_SUPPORT_DRV_TYPE_A) ||  \
                                       ((type) == SDH_CAP_SUPPORT_DRV_TYPE_C) ||  \
                                       ((type) == SDH_CAP_SUPPORT_DRV_TYPE_D) ||  \
                                       ((type) == SDH_CAP_SUPPORT_SDR50_TUNE))

/** @defgroup  SDH_WAKEUP_EVENT_TYPE
 *  @{
 */
#define IS_SDH_WAKEUP_EVENT_TYPE(type) (((type) == SDH_WAKEUP_EVENT_INT) ||    \
                                        ((type) == SDH_WAKEUP_EVENT_INSERT) || \
                                        ((type) == SDH_WAKEUP_EVENT_REMOVE))

/** @defgroup  SDH_TRANS_FLAG_TYPE
 *  @{
 */
#define IS_SDH_TRANS_FLAG_TYPE(type) (((type) == SDH_TRANS_FLAG_EN_DMA) ||                \
                                      ((type) == SDH_TRANS_FLAG_EN_BLK_COUNT) ||          \
                                      ((type) == SDH_TRANS_FLAG_EN_AUTO_CMD12) ||         \
                                      ((type) == SDH_TRANS_FLAG_EN_AUTO_CMD23) ||         \
                                      ((type) == SDH_TRANS_FLAG_READ_DATA) ||             \
                                      ((type) == SDH_TRANS_FLAG_MULTI_BLK) ||             \
                                      ((type) == SDH_TRANS_FLAG_RESP_136BITS) ||          \
                                      ((type) == SDH_TRANS_FLAG_RESP_48BITS) ||           \
                                      ((type) == SDH_TRANS_FLAG_RESP_48BITS_WITH_BUSY) || \
                                      ((type) == SDH_TRANS_FLAG_EN_CRC_CHECK) ||          \
                                      ((type) == SDH_TRANS_FLAG_EN_INDEX_CHECK) ||        \
                                      ((type) == SDH_TRANS_FLAG_DATA_PRESENT) ||          \
                                      ((type) == SDH_TRANS_FLAG_SUSPEND) ||               \
                                      ((type) == SDH_TRANS_FLAG_RESUME) ||                \
                                      ((type) == SDH_TRANS_FLAG_ABORT))

/** @defgroup  SDH_PRESENT_FLAG_TYPE
 *  @{
 */
#define IS_SDH_PRESENT_FLAG_TYPE(type) (((type) == SDH_PRESENT_FLAG_CMD_INHBIT) ||       \
                                        ((type) == SDH_PRESENT_FLAG_DATA_INHBIT) ||      \
                                        ((type) == SDH_PRESENT_FLAG_DATA_LINE_ACTIVE) || \
                                        ((type) == SDH_PRESENT_FLAG_RETUNE_REQ) ||       \
                                        ((type) == SDH_PRESENT_FLAG_TX_ACTIVE) ||        \
                                        ((type) == SDH_PRESENT_FLAG_RX_ACTIVE) ||        \
                                        ((type) == SDH_PRESENT_FLAG_BUF_WRITE_ENABLE) || \
                                        ((type) == SDH_PRESENT_FLAG_BUF_READ_ENABLE) ||  \
                                        ((type) == SDH_PRESENT_FLAG_CARD_INSERT) ||      \
                                        ((type) == SDH_PRESENT_FLAG_CARD_STABLE) ||      \
                                        ((type) == SDH_PRESENT_FLAG_CARD_DET) ||         \
                                        ((type) == SDH_PRESENT_FLAG_CARD_WP) ||          \
                                        ((type) == SDH_PRESENT_FLAG_DATA0_LINE_LEVEL) || \
                                        ((type) == SDH_PRESENT_FLAG_DATA1_LINE_LEVEL) || \
                                        ((type) == SDH_PRESENT_FLAG_DATA2_LINE_LEVEL) || \
                                        ((type) == SDH_PRESENT_FLAG_DATA3_LINE_LEVEL) || \
                                        ((type) == SDH_PRESENT_FLAG_CMD_LINE_LEVEL))

/** @defgroup  SDH_INT_TYPE
 *  @{
 */
#define IS_SDH_INT_TYPE(type) (((type) == SDH_INT_CMD_COMPLETED) ||      \
                               ((type) == SDH_INT_DATA_COMPLETED) ||     \
                               ((type) == SDH_INT_BLK_GAP_EVENT) ||      \
                               ((type) == SDH_INT_DMA_COMPLETED) ||      \
                               ((type) == SDH_INT_BUFFER_WRITE_READY) || \
                               ((type) == SDH_INT_BUFFER_READ_READY) ||  \
                               ((type) == SDH_INT_CARD_INSERT) ||        \
                               ((type) == SDH_INT_CARD_REMOVE) ||        \
                               ((type) == SDH_INT_CARD) ||               \
                               ((type) == SDH_INT_DRIVER_TA) ||          \
                               ((type) == SDH_INT_DRIVER_TB) ||          \
                               ((type) == SDH_INT_DRIVER_TC) ||          \
                               ((type) == SDH_INT_RETUNE_EVENT) ||       \
                               ((type) == SDH_INT_CMD_TIMEOUT) ||        \
                               ((type) == SDH_INT_CMD_CRC_ERROR) ||      \
                               ((type) == SDH_INT_CMD_ENDBIT_ERROR) ||   \
                               ((type) == SDH_INT_CMD_INDEX_ERROR) ||    \
                               ((type) == SDH_INT_DATA_TIMEOUT) ||       \
                               ((type) == SDH_INT_DATA_CRC_ERROR) ||     \
                               ((type) == SDH_INT_DATA_ENDBIT_ERROR) ||  \
                               ((type) == SDH_INT_CURRENT_ERROR) ||      \
                               ((type) == SDH_INT_AUTO_CMD12_ERROR) ||   \
                               ((type) == SDH_INT_DMA_ERROR) ||          \
                               ((type) == SDH_INT_TUNE_ERROR) ||         \
                               ((type) == SDH_INT_SPI_ERROR) ||          \
                               ((type) == SDH_INT_AXI_RESP_ERROR) ||     \
                               ((type) == SDH_INT_CPL_TIMEOUT_ERROR) ||  \
                               ((type) == SDH_INT_CRC_STAT_ERROR) ||     \
                               ((type) == SDH_INT_CMD_ERRORS) ||         \
                               ((type) == SDH_INT_DATA_ERRORS) ||        \
                               ((type) == SDH_INT_ALL))

/** @defgroup  SDH_BOOT_MODE_TYPE
 *  @{
 */
#define IS_SDH_BOOT_MODE_TYPE(type) (((type) == SDH_BOOT_MODE_NORMAL) || \
                                     ((type) == SDH_BOOT_MODE_ALT))

/** @defgroup  SDH_AUTO_CMD12_ERR_TYPE
 *  @{
 */
#define IS_SDH_AUTO_CMD12_ERR_TYPE(type) (((type) == SDH_AUTO_CMD12_ERR_NOT_EXE) || \
                                          ((type) == SDH_AUTO_CMD12_ERR_TIMEOUT) || \
                                          ((type) == SDH_AUTO_CMD12_ERR_ENDBIT) ||  \
                                          ((type) == SDH_AUTO_CMD12_ERR_INDEX) ||   \
                                          ((type) == SDH_AUTO_CMD12_ERR_CRC) ||     \
                                          ((type) == SDH_AUTO_CMD12_ERR_NOT_ISSUE))

/** @defgroup  SDH_ADMA_ERR_TYPE
 *  @{
 */
#define IS_SDH_ADMA_ERR_TYPE(type) (((type) == SDH_ADMA_ERR_LEN_MISMATCH) || \
                                    ((type) == SDH_ADMA_ERR_DESC_ERROR))

/** @defgroup  SDH_ADMA_ERR_STAT_TYPE
 *  @{
 */
#define IS_SDH_ADMA_ERR_STAT_TYPE(type) (((type) == SDH_ADMA_ERR_STAT_STOP_DMA) ||    \
                                         ((type) == SDH_ADMA_ERR_STAT_FETCH_DESC) ||  \
                                         ((type) == SDH_ADMA_ERR_STAT_CHANGE_ADDR) || \
                                         ((type) == SDH_ADMA_ERR_STAT_TRANS_DATA) ||  \
                                         ((type) == SDH_ADMA_ERR_STAT_INVALID_LEN) || \
                                         ((type) == SDH_ADMA_ERR_STAT_INVALID_DESC))

/** @defgroup  SDH_FORCE_EVENT_TYPE
 *  @{
 */
#define IS_SDH_FORCE_EVENT_TYPE(type) (((type) == SDH_FORCE_EVENT_AUTO_CMD12_NOT_EXE) ||     \
                                       ((type) == SDH_FORCE_EVENT_AUTO_CMD12_TIMEOUT) ||     \
                                       ((type) == SDH_FORCE_EVENT_AUTO_CMD12_CRC_ERROR) ||   \
                                       ((type) == SDH_FORCE_EVENT_AUTO_CMD12_INDEX_ERROR) || \
                                       ((type) == SDH_FORCE_EVENT_AUTO_CMD12_NOT_ISSUE) ||   \
                                       ((type) == SDH_FORCE_EVENT_ENDBIT_ERROR) ||           \
                                       ((type) == SDH_FORCE_EVENT_CMD_TIMEOUT) ||            \
                                       ((type) == SDH_FORCE_EVENT_CMD_CRC_ERROR) ||          \
                                       ((type) == SDH_FORCE_EVENT_CMD_ENDBIT_ERROR) ||       \
                                       ((type) == SDH_FORCE_EVENT_CMD_INDEX_ERROR) ||        \
                                       ((type) == SDH_FORCE_EVENT_DATA_TIMEOUT) ||           \
                                       ((type) == SDH_FORCE_EVENT_DATA_CRC_ERROR) ||         \
                                       ((type) == SDH_FORCE_EVENT_DATA_ENDBIT_ERROR) ||      \
                                       ((type) == SDH_FORCE_EVENT_DATA_INDEX_ERROR) ||       \
                                       ((type) == SDH_FORCE_EVENT_AUTO_CMD12_ERROR) ||       \
                                       ((type) == SDH_FORCE_EVENT_CARD_INT) ||               \
                                       ((type) == SDH_FORCE_EVENT_DMA_ERROR))

/** @defgroup  SDH_SPEED_MODE_TYPE
 *  @{
 */
#define IS_SDH_SPEED_MODE_TYPE(type) (((type) == SDH_SPEED_MODE_SDR12) ||  \
                                      ((type) == SDH_SPEED_MODE_SDR25) ||  \
                                      ((type) == SDH_SPEED_MODE_SDR50) ||  \
                                      ((type) == SDH_SPEED_MODE_SDR104) || \
                                      ((type) == SDH_SPEED_MODE_DDR50))

/** @defgroup  SDH_DATA_BUS_WIDTH_TYPE
 *  @{
 */
#define IS_SDH_DATA_BUS_WIDTH_TYPE(type) (((type) == SDH_DATA_BUS_WIDTH_1BIT) ||  \
                                          ((type) == SDH_DATA_BUS_WIDTH_4BITS) || \
                                          ((type) == SDH_DATA_BUS_WIDTH_8BITS))

/** @defgroup  SDH_VOLTAGE_TYPE
 *  @{
 */
#define IS_SDH_VOLTAGE_TYPE(type) (((type) == SDH_VOLTAGE_3P3V) || \
                                   ((type) == SDH_VOLTAGE_3P0V) || \
                                   ((type) == SDH_VOLTAGE_1P8V))

/** @defgroup  SDH_DMA_MODE_TYPE
 *  @{
 */
#define IS_SDH_DMA_MODE_TYPE(type) (((type) == SDH_DMA_MODE_SIMPLE) || \
                                    ((type) == SDH_DMA_MODE_ADMA1) ||  \
                                    ((type) == SDH_DMA_MODE_ADMA2))

/** @defgroup  SDH_CTRL_FLAG_TYPE
 *  @{
 */
#define IS_SDH_CTRL_FLAG_TYPE(type) (((type) == SDH_CTRL_FLAG_STOP_AT_BLK_GAP) ||         \
                                     ((type) == SDH_CTRL_FLAG_READ_WAIT) ||               \
                                     ((type) == SDH_CTRL_FLAG_INT_AT_BLK_GAP) ||          \
                                     ((type) == SDH_CTRL_FLAG_RAED_DONE_WITHOUT_8CLKS) || \
                                     ((type) == SDH_CTRL_FLAG_EXACT_BLK_NUM_READ))

/** @defgroup  SDH_CMD_TYPE
 *  @{
 */
#define IS_SDH_CMD_TYPE(type) (((type) == SDH_CMD_NORMAL) ||  \
                               ((type) == SDH_CMD_SUSPEND) || \
                               ((type) == SDH_CMD_RESUME) ||  \
                               ((type) == SDH_CMD_ABORT) ||   \
                               ((type) == SDH_CMD_EMPTY))

/** @defgroup  SDH_RESP_TYPE
 *  @{
 */
#define IS_SDH_RESP_TYPE(type) (((type) == SDH_RESP_NONE) || \
                                ((type) == SDH_RESP_R1) ||   \
                                ((type) == SDH_RESP_R1B) ||  \
                                ((type) == SDH_RESP_R2) ||   \
                                ((type) == SDH_RESP_R3) ||   \
                                ((type) == SDH_RESP_R4) ||   \
                                ((type) == SDH_RESP_R5) ||   \
                                ((type) == SDH_RESP_R5B) ||  \
                                ((type) == SDH_RESP_R6) ||   \
                                ((type) == SDH_RESP_R7))

/** @defgroup  SDH_ADMA_FLAG_TYPE
 *  @{
 */
#define IS_SDH_ADMA_FLAG_TYPE(type) (((type) == SDH_ADMA_FLAG_SINGLE_DESC) || \
                                     ((type) == SDH_ADMA_FLAG_MULTI_DESC))

/** @defgroup  SDH_ADMA1_DESC_FLAG_TYPE
 *  @{
 */
#define IS_SDH_ADMA1_DESC_FLAG_TYPE(type) (((type) == SDH_ADMA1_DESC_FLAG_VALID) ||    \
                                           ((type) == SDH_ADMA1_DESC_FLAG_END) ||      \
                                           ((type) == SDH_ADMA1_DESC_FLAG_INT) ||      \
                                           ((type) == SDH_ADMA1_DESC_FLAG_ACTIVE1) ||  \
                                           ((type) == SDH_ADMA1_DESC_FLAG_ACTIVE2) ||  \
                                           ((type) == SDH_ADMA1_DESC_FLAG_TRANSFER) || \
                                           ((type) == SDH_ADMA1_DESC_FLAG_LINK) ||     \
                                           ((type) == SDH_ADMA1_DESC_FLAG_SETLEN))

/** @defgroup  SDH_ADMA2_DESC_FLAG_TYPE
 *  @{
 */
#define IS_SDH_ADMA2_DESC_FLAG_TYPE(type) (((type) == SDH_ADMA2_DESC_FLAG_VALID) ||    \
                                           ((type) == SDH_ADMA2_DESC_FLAG_END) ||      \
                                           ((type) == SDH_ADMA2_DESC_FLAG_INT) ||      \
                                           ((type) == SDH_ADMA2_DESC_FLAG_ACTIVE1) ||  \
                                           ((type) == SDH_ADMA2_DESC_FLAG_ACTIVE2) ||  \
                                           ((type) == SDH_ADMA2_DESC_FLAG_TRANSFER) || \
                                           ((type) == SDH_ADMA2_DESC_FLAG_LINK))

/** @defgroup  SDH_BURST_TYPE
 *  @{
 */
#define IS_SDH_BURST_TYPE(type) (((type) == SDH_BUSRT_INCR) ||  \
                                 ((type) == SDH_BUSRT_INCR4) || \
                                 ((type) == SDH_BUSRT_WRAP4))

/** @defgroup  SDH_FIFO_THRESHOLD_TYPE
 *  @{
 */
#define IS_SDH_FIFO_THRESHOLD_TYPE(type) (((type) == SDH_FIFO_THRESHOLD_64_BYTES) ||  \
                                          ((type) == SDH_FIFO_THRESHOLD_128_BYTES) || \
                                          ((type) == SDH_FIFO_THRESHOLD_192_BYTES) || \
                                          ((type) == SDH_FIFO_THRESHOLD_256_BYTES))

/** @defgroup  SDH_BURST_SIZE_TYPE
 *  @{
 */
#define IS_SDH_BURST_SIZE_TYPE(type) (((type) == SDH_BURST_SIZE_32_BYTES) ||  \
                                      ((type) == SDH_BURST_SIZE_64_BYTES) ||  \
                                      ((type) == SDH_BURST_SIZE_128_BYTES) || \
                                      ((type) == SDH_BURST_SIZE_256_BYTES))

/** @defgroup  SDH_TRANS_DATA_TYPE
 *  @{
 */
#define IS_SDH_TRANS_DATA_TYPE(type) (((type) == SDH_TRANS_DATA_NORMAL) || \
                                      ((type) == SDH_TRANS_DATA_TUNING) || \
                                      ((type) == SDH_TRANS_DATA_BOOT) ||   \
                                      ((type) == SDH_TRANS_DATA_BOOT_CONT))

/*@} end of group SDH_Public_Constants */

/** @defgroup  SDH_Public_Macros
 *  @{
 */
/* The alignment size for ADDRESS filed in SDMA */
#define SDH_SDMA_ADDRESS_ALIGN (1U)
/* The alignment size for LENGTH field in SDMA */
#define SDH_SDMA_LENGTH_ALIGN (1U)
/* The alignment size for ADDRESS filed in ADMA1's descriptor */
#define SDH_ADMA1_ADDRESS_ALIGN (4096U)
/* The alignment size for ADDRESS field in ADMA2's descriptor */
#define SDH_ADMA2_ADDRESS_ALIGN (1U)
/* The alignment size for LENGTH filed in ADMA2's descriptor */
#define SDH_ADMA2_LENGTH_ALIGN (1U)
/* ADMA1 descriptor table
* |------------------------|---------|--------------------------|
* | Address/page field     |Reserved |         Attribute        |
* |------------------------|---------|--------------------------|
* |31                    12|11      6|05  |04  |03|02 |01 |00   |
* |------------------------|---------|----|----|--|---|---|-----|
* | address or data length | 000000  |Act2|Act1| 0|Int|End|Valid|
* |------------------------|---------|----|----|--|---|---|-----|
*
*
* |------|------|-----------------|-------|-------------|
* | Act2 | Act1 |     Comment     | 31-28 | 27 - 12     |
* |------|------|-----------------|---------------------|
* |   0  |   0  | No op           | Don't care          |
* |------|------|-----------------|-------|-------------|
* |   0  |   1  | Set data length |  0000 | Data Length |
* |------|------|-----------------|-------|-------------|
* |   1  |   0  | Transfer data   | Data address        |
* |------|------|-----------------|---------------------|
* |   1  |   1  | Link descriptor | Descriptor address  |
* |------|------|-----------------|---------------------|
*/
/* The bit shift for ADDRESS filed in ADMA1's descriptor */
#define SDH_ADMA1_DESCRIPTOR_ADDRESS_POS (12U)
/* The bit mask for ADDRESS field in ADMA1's descriptor */
#define SDH_ADMA1_DESCRIPTOR_ADDRESS_MASK (0xFFFFFU)
/* The bit shift for LENGTH filed in ADMA1's descriptor */
#define SDH_ADMA1_DESCRIPTOR_LENGTH_POS (12U)
/* The mask for LENGTH field in ADMA1's descriptor */
#define SDH_ADMA1_DESCRIPTOR_LENGTH_MASK (0xFFFFU)
/* The maximum value of LENGTH filed in ADMA1's descriptor */
#define SDH_ADMA1_DESCRIPTOR_MAX_LENGTH_PER_ENTRY (SDH_ADMA1_DESCRIPTOR_LENGTH_MASK - 511U)
/* ADMA2 descriptor table
* |----------------|---------------|-------------|--------------------------|
* | Address field  |     Length    | Reserved    |         Attribute        |
* |----------------|---------------|-------------|--------------------------|
* |63            32|31           16|15         06|05  |04  |03|02 |01 |00   |
* |----------------|---------------|-------------|----|----|--|---|---|-----|
* | 32-bit address | 16-bit length | 0000000000  |Act2|Act1| 0|Int|End|Valid|
* |----------------|---------------|-------------|----|----|--|---|---|-----|
*
*
* | Act2 | Act1 |     Comment     | Operation                                                         |
* |------|------|-----------------|-------------------------------------------------------------------|
* |   0  |   0  | No op           | Don't care                                                        |
* |------|------|-----------------|-------------------------------------------------------------------|
* |   0  |   1  | Reserved        | Read this line and go to next one                                 |
* |------|------|-----------------|-------------------------------------------------------------------|
* |   1  |   0  | Transfer data   | Transfer data with address and length set in this descriptor line |
* |------|------|-----------------|-------------------------------------------------------------------|
* |   1  |   1  | Link descriptor | Link to another descriptor                                        |
* |------|------|-----------------|-------------------------------------------------------------------|
*/
/* The bit shift for LENGTH field in ADMA2's descriptor */
#define SDH_ADMA2_DESCRIPTOR_LENGTH_POS (16U)
/* The bit mask for LENGTH field in ADMA2's descriptor */
#define SDH_ADMA2_DESCRIPTOR_LENGTH_MASK (0xFFFFU)
/* The maximum value of LENGTH field in ADMA2's descriptor */
#define SDH_ADMA2_DESCRIPTOR_MAX_LENGTH_PER_ENTRY (SDH_ADMA2_DESCRIPTOR_LENGTH_MASK - 511U)
#define SDH_EnableIntStatus(mask)                                             \
    do {                                                                      \
        BL_WR_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS_EN,                      \
                  BL_RD_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS_EN) | (mask)); \
    } while (0)
#define SDH_DisableIntStatus(mask)                                               \
    do {                                                                         \
        BL_WR_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS_EN,                         \
                  BL_RD_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS_EN) & (~(mask))); \
    } while (0)
#define SDH_EnableIntSource(mask)                                                 \
    do {                                                                          \
        BL_WR_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS_INT_EN,                      \
                  BL_RD_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS_INT_EN) | (mask)); \
    } while (0)
#define SDH_DisableIntSource(mask)                                                   \
    do {                                                                             \
        BL_WR_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS_INT_EN,                         \
                  BL_RD_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS_INT_EN) & (~(mask))); \
    } while (0)
#define SDH_GetIntStatus()       BL_RD_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS);
#define SDH_GetIntEnableStatus() BL_RD_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS_INT_EN);
#define SDH_ClearIntStatus(mask) BL_WR_REG(SDH_BASE, SDH_SD_NORMAL_INT_STATUS, (mask));
#define SDH_AutoCmd12ErrStatus() BL_RD_SHORT(SDH_BASE + SDH_SD_AUTO_CMD12_ERROR_STATUS_OFFSET);
#define SDH_GetDMAErrStatus()    BL_RD_SHORT(SDH_BASE + SDH_SD_ADMA_ERROR_STATUS_OFFSET);
#define SDH_GetPresentStatus()   BL_RD_REG(SDH_BASE, SDH_SD_PRESENT_STATE_1);
#define SDH_MAX_BLOCK_COUNT      0xffff
//#define SDH_CMD_INDEX(x)                    (x)

/*@} end of group SDH_Public_Macros */

/** @defgroup  SDH_Public_Functions
 *  @{
 */
void SDH_MMC1_IRQHandler(void);

void SDH_Reset(void);
void SDH_Set_Timeout(uint8_t tmo);
void SDH_SetSdClock(uint32_t srcClock, uint32_t busClock);
void SDH_ITConfig(uint32_t SDH_IT_FLAG, BL_Fun_Type NewState);
void SDH_Ctrl_Init(const SDH_Cfg_Type *cfg);
void SDH_Powon(void);
void SDH_SendCommand(SDH_CMD_Cfg_Type *cmd);
void SDH_DisableDMA(void);
void SDH_SetSdClock(uint32_t srcClock, uint32_t busClock);
SDH_Stat_Type SDH_GetCmdResp(SDH_CMD_Cfg_Type *cmd);
uint32_t SDH_ReadDataPort(SDH_Data_Cfg_Type *dataCfg);
SDH_Stat_Type SDH_WaitCommandDone(SDH_CMD_Cfg_Type *cmd);
SDH_Stat_Type SDH_ConfigDataTranfer(SDH_Data_Cfg_Type *dataCfg);
SDH_Stat_Type SDH_TransferDataBlocking(SDH_Data_Cfg_Type *dataCfg, uint8_t enDMA);
SDH_Stat_Type SDH_TransferBlocking(SDH_DMA_Cfg_Type *dmaCfg, SDH_Trans_Cfg_Type *transfer);
SDH_Stat_Type SDH_TransferNonBlocking(SDH_DMA_Cfg_Type *dmaCfg, SDH_Trans_Cfg_Type *transfer);
void SDH_InstallHandleCallback(SDH_Handle_Cfg_Type *handle, const SDH_Trans_Callback_Cfg_Type *callBack, void *userData);
void SDH_EnableDMA(SDH_DMA_Mode_Type dmaMode);
void SDH_EnableStatus(void);
SDH_Stat_Type SDH_ReadDataPortBlock(SDH_Data_Cfg_Type *dataCfg);
uint32_t SDH_WriteDataPort(SDH_Data_Cfg_Type *dataCfg);
SDH_Stat_Type SDH_WriteDataPortBlock(SDH_Data_Cfg_Type *dataCfg);
void SDH_DisableSdClock(void);
void SDH_Deinit(void);
void SDH_GetCapability(SDH_Cap_Cfg_Type *capability);
SDH_Stat_Type SDH_CreateADMA1Descriptor(uint32_t *adma1Entries, uint32_t maxEntries,
                                        const uint32_t *data, uint32_t dataLen, SDH_ADMA_Flag_Type flag);
SDH_Stat_Type SDH_CreateADMA2Descriptor(SDH_ADMA2_Desc_Type *adma2Entries, uint32_t maxEntries,
                                        const uint32_t *data, uint32_t dataLen, SDH_ADMA_Flag_Type flag);
SDH_Stat_Type SDH_SetInternalDmaConfig(SDH_DMA_Cfg_Type *dmaCfg, const uint32_t *data, uint8_t enAutoCmd23);
SDH_Stat_Type SDH_CreateAdmaEntryConfig(SDH_DMA_Cfg_Type *dmaCfg, SDH_Data_Cfg_Type *dataCfg, SDH_ADMA_Flag_Type flag);
/*@} end of group SDH_Public_Functions */

/*@} end of group SDH */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_SDH_H__ */
