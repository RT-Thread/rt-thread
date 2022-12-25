/**
  ******************************************************************************
  * @file    bl808_dma2d.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
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
#ifndef __BL808_DMA2D_H__
#define __BL808_DMA2D_H__

#include "dma2d_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DMA2D
 *  @{
 */

/** @defgroup  DMA2D_Public_Types
 *  @{
 */

/**
 *  @brief DMA2D port type definition
 */
typedef enum {
    DMA2D0_ID,    /*!< DMA2D0 port define */
    DMA2D_ID_MAX, /*!< DMA2D MAX ID define */
} DMA2D_ID_Type;

/**
 *  @brief DMA2D endian type definition
 */
typedef enum {
    DMA2D_LITTLE_ENDIAN = 0, /*!< DMA2D use little endian */
    DMA2D_BIG_ENDIAN,        /*!< DMA2D use big endian */
} DMA2D_Endian_Type;

/**
 *  @brief DMA2D synchronization logic  type definition
 */
typedef enum {
    DMA2D_SYNC_LOGIC_ENABLE = 0, /*!< DMA2D synchronization logic enable */
    DMA2D_SYNC_LOGIC_DISABLE,    /*!< DMA2D synchronization logic disable */
} DMA2D_Sync_Logic_Type;

/**
 *  @brief DMA2D transfer width type definition
 */
typedef enum {
    DMA2D_TRNS_WIDTH_8BITS = 0, /*!< DMA2D transfer width:8 bits */
    DMA2D_TRNS_WIDTH_16BITS,    /*!< DMA2D transfer width:16 bits */
    DMA2D_TRNS_WIDTH_32BITS,    /*!< DMA2D transfer width:32 bits */
} DMA2D_Trans_Width_Type;

/**
 *  @brief DMA2D transfer direction type definition
 */
typedef enum {
    DMA2D_TRNS_M2M = 0, /*!< DMA2D transfer type:memory to memory */
    DMA2D_TRNS_M2P,     /*!< DMA2D transfer type:memory to peripheral */
    DMA2D_TRNS_P2M,     /*!< DMA2D transfer type:peripheral to memory */
    DMA2D_TRNS_P2P,     /*!< DMA2D transfer type:peripheral to peripheral */
} DMA2D_Trans_Dir_Type;

/**
 *  @brief DMA2D burst size type definition
 */
typedef enum {
    DMA2D_BURST_SIZE_1 = 0, /*!< DMA2D burst size:1 * transfer width */
    DMA2D_BURST_SIZE_4,     /*!< DMA2D burst size:4 * transfer width */
    DMA2D_BURST_SIZE_8,     /*!< DMA2D burst size:8 * transfer width */
    DMA2D_BURST_SIZE_16,    /*!< DMA2D burst size:16 * transfer width */
} DMA2D_Burst_Size_Type;

/**
 *  @brief DMA2D destination peripheral type definition
 */
typedef enum {
    DMA2D_REQ_UART0_RX = 0,  /*!< DMA2D request peripheral:UART0 RX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_UART0_TX = 1,  /*!< DMA2D request peripheral:UART0 TX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_UART1_RX = 2,  /*!< DMA2D request peripheral:UART1 RX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_UART1_TX = 3,  /*!< DMA2D request peripheral:UART1 TX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_UART2_RX = 4,  /*!< DMA2D request peripheral:UART2 RX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_UART2_TX = 5,  /*!< DMA2D request peripheral:UART2 TX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_I2C0_RX = 6,   /*!< DMA2D request peripheral:I2C0 RX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_I2C0_TX = 7,   /*!< DMA2D request peripheral:I2C0 TX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_IR_TX = 8,     /*!< DMA2D request peripheral:IR TX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_GPIO = 9,      /*!< DMA2D request peripheral:GPIO, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_SPI0_RX = 10,  /*!< DMA2D request peripheral:SPI0 RX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_SPI0_TX = 11,  /*!< DMA2D request peripheral:SPI0 TX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_AUDIO_RX = 12, /*!< DMA2D request peripheral:AUDIO RX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_AUDIO_TX = 13, /*!< DMA2D request peripheral:AUDIO TX, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_GPADC0 = 22,   /*!< DMA2D request peripheral:GPADC0, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_GPADC1 = 23,   /*!< DMA2D request peripheral:GPADC1, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_USB_EP0 = 24,  /*!< DMA2D request peripheral:USB EP 0, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_USB_EP1 = 25,  /*!< DMA2D request peripheral:USB EP 1, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_USB_EP2 = 26,  /*!< DMA2D request peripheral:USB EP 2, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_USB_EP3 = 27,  /*!< DMA2D request peripheral:USB EP 3, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_USB_EP4 = 28,  /*!< DMA2D request peripheral:USB EP 4, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_USB_EP5 = 29,  /*!< DMA2D request peripheral:USB EP 5, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_USB_EP6 = 30,  /*!< DMA2D request peripheral:USB EP 6, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_USB_EP7 = 31,  /*!< DMA2D request peripheral:USB EP 7, DMA2D0 and DMA2D1 support */
    DMA2D_REQ_UART3_RX = 0,  /*!< DMA2D request peripheral:UART3 RX, only DMA2D2 support */
    DMA2D_REQ_UART3_TX = 1,  /*!< DMA2D request peripheral:UART3 TX, only DMA2D2 support */
    DMA2D_REQ_SPI1_RX = 2,   /*!< DMA2D request peripheral:SPI1 RX, only DMA2D2 support */
    DMA2D_REQ_SPI1_TX = 3,   /*!< DMA2D request peripheral:SPI1 TX, only DMA2D2 support */
    DMA2D_REQ_I2C1_RX = 6,   /*!< DMA2D request peripheral:I2C1 RX, only DMA2D2 support */
    DMA2D_REQ_I2C1_TX = 7,   /*!< DMA2D request peripheral:I2C1 TX, only DMA2D2 support */
    DMA2D_REQ_I2S_TX = 12,   /*!< DMA2D request peripheral:I2S TX, only DMA2D2 support */
    DMA2D_REQ_I2S_RX = 13,   /*!< DMA2D request peripheral:I2S RX, only DMA2D2 support */
    DMA2D_REQ_DBI_TX = 22,   /*!< DMA2D request peripheral:DBI TX, only DMA2D2 support */
    DMA2D_REQ_NONE = 0,      /*!< DMA2D request peripheral:None */
} DMA2D_Periph_Req_Type;

/**
 *  @brief DMA2D channel type definition
 */
typedef enum {
    DMA2D_CH0 = 0, /*!< DMA2D channel 0 */
    DMA2D_CH1,     /*!< DMA2D channel 1 */
    DMA2D_CH_MAX,  /*!<  */
} DMA2D_Chan_Type;

/**
 *  @brief DMA2D LLI Structure PING-PONG
 */
typedef enum {
    DMA2D_PING_INDEX = 0, /*!< PING INDEX */
    DMA2D_PONG_INDEX,     /*!< PONG INDEX */
} DMA2D_LLI_PP_Index_Type;

/**
 *  @brief DMA2D interrupt type definition
 */
typedef enum {
    DMA2D_INT_TCOMPLETED = 0, /*!< DMA2D completed interrupt */
    DMA2D_INT_ALL,            /*!< All the interrupt */
} DMA2D_INT_Type;

/**
 *  @brief DMA2D rotate type definition
 */
typedef enum {
    DMA2D_ROTATE_DEGREE_90 = 0, /*!< DMA2D rotate 90 degrees */
    DMA2D_ROTATE_DEGREE_180,    /*!< DMA2D rotate 180 degrees */
    DMA2D_ROTATE_DEGREE_270,    /*!< DMA2D rotate 270 degrees */
} DMA2D_Rotate_Type;

/**
 *  @brief DMA2D fold type definition
 */
typedef enum {
    DMA2D_FOLD_LEFT_RIGHT = 0, /*!< DMA2D fold left and right */
    DMA2D_FOLD_UP_DOWN,        /*!< DMA2D fold up and down */
} DMA2D_Fold_Type;

/**
 *  @brief DMA2D color key type definition
 */
typedef enum {
    DMA2D_COLOR_KEY_8BIT = 0, /*!< DMA2D color key is 8-bit */
    DMA2D_COLOR_KEY_16BIT,    /*!< DMA2D color key is 16-bit */
    DMA2D_COLOR_KEY_24BIT,    /*!< DMA2D color key is 24-bit */
    DMA2D_COLOR_KEY_32BIT,    /*!< DMA2D color key is 32-bit */
} DMA2D_Color_Key_Type;

/**
 *  @brief DMA2D channel Configuration Structure type definition
 */
typedef struct
{
    uint32_t srcDmaAddr;                   /*!< Source address of DMA2D transfer */
    uint32_t destDmaAddr;                  /*!< Destination address of DMA2D transfer */
    uint32_t transfLength;                 /*!< Transfer length, 0~4095, this is burst count */
    DMA2D_Trans_Dir_Type dir;              /*!< Transfer dir control. 0: Memory to Memory, 1: Memory to peripheral, 2: Peripheral to memory */
    DMA2D_Chan_Type ch;                    /*!< Channel select 0-7 */
    DMA2D_Trans_Width_Type srcTransfWidth; /*!< Transfer width. 0: 8  bits, 1: 16  bits, 2: 32  bits, 3: 64  bits(only for DMA2D2 channel 0 and
                                                 channel 1) */
    DMA2D_Trans_Width_Type dstTransfWidth; /*!< Transfer width. 0: 8  bits, 1: 16  bits, 2: 32  bits, 3: 64  bits(only for DMA2D2 channel 0 and
                                                 channel 1) */
    DMA2D_Burst_Size_Type srcBurstSize;    /*!< Number of data items for burst transaction length. Each item width is as same as tansfer width.
                                                 0: 1 item, 1: 4 items, 2: 8 items, 3: 16 items */
    DMA2D_Burst_Size_Type dstBurstSize;    /*!< Number of data items for burst transaction length. Each item width is as same as tansfer width.
                                                 0: 1 item, 1: 4 items, 2: 8 items, 3: 16 items */
    uint8_t srcAddrInc;                    /*!< Source address increment. 0: No change, 1: Increment */
    uint8_t destAddrInc;                   /*!< Destination address increment. 0: No change, 1: Increment */
    DMA2D_Periph_Req_Type srcPeriph;       /*!< Source peripheral select */
    DMA2D_Periph_Req_Type dstPeriph;       /*!< Destination peripheral select */
} DMA2D_Channel_Cfg_Type;

/**
 *  @brief DMA2D configuration Structure definition
 */
typedef struct
{
    uint16_t srcCntX; /*!< Source x count */
    uint16_t srcCntY; /*!< Source y count */
    int32_t srcIncrX; /*!< Source x increment */
    int32_t srcIncrY; /*!< Source y increment */
    uint16_t dstCntX; /*!< Destination x count */
    uint16_t reserve; /*!< Reserved  */
    int32_t dstIncrX; /*!< Destination x increment */
    int32_t dstIncrY; /*!< Destination y increment */
} DMA2D_Cfg_Type;

/**
 *  @brief DMA2D LLI control structure type definition
 */
typedef struct
{
    uint32_t srcDmaAddr;              /*!< Source address of DMA2D transfer */
    uint32_t destDmaAddr;             /*!< Destination address of DMA2D transfer */
    uint32_t nextLLI;                 /*!< Next LLI address */
    struct DMA2D_Control_Reg dmaCtrl; /*!< DMA2D transaction control */
    DMA2D_Cfg_Type dma2dCfg;          /*!< DMA2D configuration */
} DMA2D_LLI_Ctrl_Type;

/**
 *  @brief DMA2D LLI configuration structure type definition
 */
typedef struct
{
    DMA2D_Trans_Dir_Type dir;        /*!< Transfer dir control. 0: Memory to Memory, 1: Memory to peripheral, 2: Peripheral to memory */
    DMA2D_Periph_Req_Type srcPeriph; /*!< Source peripheral select */
    DMA2D_Periph_Req_Type dstPeriph; /*!< Destination peripheral select */
} DMA2D_LLI_Cfg_Type;

/**
 *  @brief DMA2D LLI Ping-Pong Buf definition
 */
typedef struct
{
    uint8_t idleIndex;                               /*!< Index Idle lliListHeader */
    uint8_t dmaId;                                   /*!< DMA2D ID used */
    uint8_t dmaChan;                                 /*!< DMA2D LLI Channel used */
    DMA2D_LLI_Ctrl_Type *lliListHeader[2];           /*!< Ping-Pong BUf List Header */
    void (*onTransCompleted)(DMA2D_LLI_Ctrl_Type *); /*!< Completed Transmit One List Callback Function */
} DMA2D_LLI_PP_Buf;

/**
 *  @brief DMA2D LLI Ping-Pong Structure definition
 */
typedef struct
{
    uint8_t pingpongIndex;                  /*!< Ping or Pong Trigger TC */
    uint8_t dmaId;                          /*!< DMA2D ID used */
    uint8_t dmaChan;                        /*!< DMA2D LLI Channel used */
    struct DMA2D_Control_Reg dmaCtrlRegVal; /*!< DMA2D Basic Pararmeter */
    DMA2D_LLI_Cfg_Type *lliCfg;             /*!< LLI Config parameter */
    uint32_t operatePeriphAddr;             /*!< Operate Peripheral register address */
    uint32_t pingpongBufAddr[2];            /*!< Ping-Pong addr */
} DMA2D_LLI_PP_Struct;

/**
 *  @brief DMA2D picture configure definition
 */
typedef struct
{
    DMA2D_Trans_Width_Type transWidth; /*!< Transfer width */
    uint32_t pixWidth;                 /*!< Pixel width, unit: byte */
    uint32_t srcAddr;                  /*!< Source address */
    uint32_t srcWidth;                 /*!< Source picture width */
    uint32_t srcX0;                    /*!< Source start x */
    uint32_t srcY0;                    /*!< Source start y */
    uint32_t srcX1;                    /*!< Source stop x */
    uint32_t srcY1;                    /*!< Source stop y */
    uint32_t dstAddr;                  /*!< Destination address */
    uint32_t dstWidth;                 /*!< Destination width */
    uint32_t dstX0;                    /*!< Destination start x */
    uint32_t dstY0;                    /*!< Destination start y */
} DMA2D_Picture_Cfg_Type;

/*@} end of group DMA2D_Public_Types */

/** @defgroup  DMA2D_Public_Constants
 *  @{
 */

/** @defgroup  DMA2D_ID_TYPE
 *  @{
 */
#define IS_DMA2D_ID_TYPE(type) (((type) == DMA2D0_ID) || \
                                ((type) == DMA2D_ID_MAX))

/** @defgroup  DMA2D_ENDIAN_TYPE
 *  @{
 */
#define IS_DMA2D_ENDIAN_TYPE(type) (((type) == DMA2D_LITTLE_ENDIAN) || \
                                    ((type) == DMA2D_BIG_ENDIAN))

/** @defgroup  DMA2D_SYNC_LOGIC_TYPE
 *  @{
 */
#define IS_DMA2D_SYNC_LOGIC_TYPE(type) (((type) == DMA2D_SYNC_LOGIC_ENABLE) || \
                                        ((type) == DMA2D_SYNC_LOGIC_DISABLE))

/** @defgroup  DMA2D_TRANS_WIDTH_TYPE
 *  @{
 */
#define IS_DMA2D_TRANS_WIDTH_TYPE(type) (((type) == DMA2D_TRNS_WIDTH_8BITS) ||  \
                                         ((type) == DMA2D_TRNS_WIDTH_16BITS) || \
                                         ((type) == DMA2D_TRNS_WIDTH_32BITS))

/** @defgroup  DMA2D_TRANS_DIR_TYPE
 *  @{
 */
#define IS_DMA2D_TRANS_DIR_TYPE(type) (((type) == DMA2D_TRNS_M2M) || \
                                       ((type) == DMA2D_TRNS_M2P) || \
                                       ((type) == DMA2D_TRNS_P2M) || \
                                       ((type) == DMA2D_TRNS_P2P))

/** @defgroup  DMA2D_BURST_SIZE_TYPE
 *  @{
 */
#define IS_DMA2D_BURST_SIZE_TYPE(type) (((type) == DMA2D_BURST_SIZE_1) || \
                                        ((type) == DMA2D_BURST_SIZE_4) || \
                                        ((type) == DMA2D_BURST_SIZE_8) || \
                                        ((type) == DMA2D_BURST_SIZE_16))

/** @defgroup  DMA2D_PERIPH_REQ_TYPE
 *  @{
 */
#define IS_DMA2D_PERIPH_REQ_TYPE(type) (((type) == DMA2D_REQ_UART0_RX) || \
                                        ((type) == DMA2D_REQ_UART0_TX) || \
                                        ((type) == DMA2D_REQ_UART1_RX) || \
                                        ((type) == DMA2D_REQ_UART1_TX) || \
                                        ((type) == DMA2D_REQ_UART2_RX) || \
                                        ((type) == DMA2D_REQ_UART2_TX) || \
                                        ((type) == DMA2D_REQ_I2C0_RX) ||  \
                                        ((type) == DMA2D_REQ_I2C0_TX) ||  \
                                        ((type) == DMA2D_REQ_IR_TX) ||    \
                                        ((type) == DMA2D_REQ_GPIO) ||     \
                                        ((type) == DMA2D_REQ_SPI0_RX) ||  \
                                        ((type) == DMA2D_REQ_SPI0_TX) ||  \
                                        ((type) == DMA2D_REQ_AUDIO_RX) || \
                                        ((type) == DMA2D_REQ_AUDIO_TX) || \
                                        ((type) == DMA2D_REQ_GPADC0) ||   \
                                        ((type) == DMA2D_REQ_GPADC1) ||   \
                                        ((type) == DMA2D_REQ_USB_EP0) ||  \
                                        ((type) == DMA2D_REQ_USB_EP1) ||  \
                                        ((type) == DMA2D_REQ_USB_EP2) ||  \
                                        ((type) == DMA2D_REQ_USB_EP3) ||  \
                                        ((type) == DMA2D_REQ_USB_EP4) ||  \
                                        ((type) == DMA2D_REQ_USB_EP5) ||  \
                                        ((type) == DMA2D_REQ_USB_EP6) ||  \
                                        ((type) == DMA2D_REQ_USB_EP7) ||  \
                                        ((type) == DMA2D_REQ_UART3_RX) || \
                                        ((type) == DMA2D_REQ_UART3_TX) || \
                                        ((type) == DMA2D_REQ_SPI1_RX) ||  \
                                        ((type) == DMA2D_REQ_SPI1_TX) ||  \
                                        ((type) == DMA2D_REQ_I2C1_RX) ||  \
                                        ((type) == DMA2D_REQ_I2C1_TX) ||  \
                                        ((type) == DMA2D_REQ_I2S_TX) ||   \
                                        ((type) == DMA2D_REQ_I2S_RX) ||   \
                                        ((type) == DMA2D_REQ_DBI_TX) ||   \
                                        ((type) == DMA2D_REQ_NONE))

/** @defgroup  DMA2D_CHAN_TYPE
 *  @{
 */
#define IS_DMA2D_CHAN_TYPE(type) (((type) == DMA2D_CH0) || \
                                  ((type) == DMA2D_CH1) || \
                                  ((type) == DMA2D_CH_MAX))

/** @defgroup  DMA2D_LLI_PP_INDEX_TYPE
 *  @{
 */
#define IS_DMA2D_LLI_PP_INDEX_TYPE(type) (((type) == DMA2D_PING_INDEX) || \
                                          ((type) == DMA2D_PONG_INDEX))

/** @defgroup  DMA2D_INT_TYPE
 *  @{
 */
#define IS_DMA2D_INT_TYPE(type) (((type) == DMA2D_INT_TCOMPLETED) || \
                                 ((type) == DMA2D_INT_ALL))

/** @defgroup  DMA2D_ROTATE_TYPE
 *  @{
 */
#define IS_DMA2D_ROTATE_TYPE(type) (((type) == DMA2D_ROTATE_DEGREE_90) ||  \
                                    ((type) == DMA2D_ROTATE_DEGREE_180) || \
                                    ((type) == DMA2D_ROTATE_DEGREE_270))

/** @defgroup  DMA2D_FOLD_TYPE
 *  @{
 */
#define IS_DMA2D_FOLD_TYPE(type) (((type) == DMA2D_FOLD_LEFT_RIGHT) || \
                                  ((type) == DMA2D_FOLD_UP_DOWN))

/** @defgroup  DMA2D_COLOR_KEY_TYPE
 *  @{
 */
#define IS_DMA2D_COLOR_KEY_TYPE(type) (((type) == DMA2D_COLOR_KEY_8BIT) || \
                                       ((type) == DMA2D_COLOR_KEY_16BIT) || \
                                       ((type) == DMA2D_COLOR_KEY_24BIT) || \
                                       ((type) == DMA2D_COLOR_KEY_32BIT))

/*@} end of group DMA2D_Public_Constants */

/** @defgroup  DMA2D_Public_Macros
 *  @{
 */
#define DMA2D_PINC_ENABLE  1
#define DMA2D_PINC_DISABLE 0
#define DMA2D_MINC_ENABLE  1
#define DMA2D_MINC_DISABLE 0

/*@} end of group DMA2D_Public_Macros */

/** @defgroup  DMA2D_Public_Functions
 *  @{
 */

/**
 *  @brief DMA2D Functions
 */
#ifndef BFLB_USE_HAL_DRIVER
void DMA2D_INT0_IRQHandler(void);
void DMA2D_INT1_IRQHandler(void);
#endif
void DMA2D_Enable(DMA2D_ID_Type dmaId);
void DMA2D_Disable(DMA2D_ID_Type dmaId);
void DMA2D_Init(DMA2D_ID_Type dmaId, uint8_t ch, DMA2D_Cfg_Type *cfg);
void DMA2D_Channel_Init(DMA2D_ID_Type dmaId, DMA2D_Channel_Cfg_Type *chCfg);
void DMA2D_DeInit(DMA2D_ID_Type dmaId);
void DMA2D_Channel_Update_SrcMemcfg(DMA2D_ID_Type dmaId, uint8_t ch, uint32_t memAddr, uint32_t len);
void DMA2D_Channel_Update_DstMemcfg(DMA2D_ID_Type dmaId, uint8_t ch, uint32_t memAddr, uint32_t len);
uint32_t DMA2D_Channel_TranferSize(DMA2D_ID_Type dmaId, uint8_t ch);
BL_Sts_Type DMA2D_Channel_Is_Busy(DMA2D_ID_Type dmaId, uint8_t ch);
void DMA2D_Channel_Enable(DMA2D_ID_Type dmaId, uint8_t ch);
void DMA2D_Channel_Disable(DMA2D_ID_Type dmaId, uint8_t ch);
void DMA2D_LLI_Init(DMA2D_ID_Type dmaId, uint8_t ch, DMA2D_LLI_Cfg_Type *lliCfg);
void DMA2D_LLI_Update(DMA2D_ID_Type dmaId, uint8_t ch, uint32_t LLI);
uint32_t DMA2D_LLI_Get_Counter(DMA2D_ID_Type dmaId, uint8_t ch);
void DMA2D_IntMask(DMA2D_ID_Type dmaId, uint8_t ch, DMA2D_INT_Type intType, BL_Mask_Type intMask);
void DMA2D_LLI_PpBuf_Start_New_Transmit(DMA2D_LLI_PP_Buf *dmaPpBuf);
DMA2D_LLI_Ctrl_Type *DMA2D_LLI_PpBuf_Remove_Completed_List(DMA2D_LLI_PP_Buf *dmaPpBuf);
void DMA2D_LLI_PpBuf_Append(DMA2D_LLI_PP_Buf *dmaPpBuf, DMA2D_LLI_Ctrl_Type *dmaLliList);
void DMA2D_LLI_PpBuf_Destroy(DMA2D_LLI_PP_Buf *dmaPpBuf);
void DMA2D_Int_Callback_Install(DMA2D_ID_Type dmaId, DMA2D_Chan_Type dmaChan, DMA2D_INT_Type intType, intCallback_Type *cbFun);
void DMA2D_LLI_PpStruct_Start(DMA2D_LLI_PP_Struct *dmaPpStruct);
void DMA2D_LLI_PpStruct_Stop(DMA2D_LLI_PP_Struct *dmaPpStruct);
BL_Err_Type DMA2D_LLI_PpStruct_Init(DMA2D_LLI_PP_Struct *dmaPpStruct);
BL_Err_Type DMA2D_LLI_PpStruct_Set_Transfer_Len(DMA2D_LLI_PP_Struct *dmaPpStruct,
                                                uint16_t Ping_Transfer_len, uint16_t Pong_Transfer_len);
void DMA2D_Picture_Translate_Calculate(DMA2D_Picture_Cfg_Type *cfg, DMA2D_LLI_Ctrl_Type *lliCfg);
void DMA2D_Picture_Rotate_Calculate(DMA2D_Picture_Cfg_Type *cfg, DMA2D_LLI_Ctrl_Type *lliCfg, DMA2D_Rotate_Type rotate);
void DMA2D_Picture_Fold_Calculate(DMA2D_Picture_Cfg_Type *cfg, DMA2D_LLI_Ctrl_Type *lliCfg, DMA2D_Fold_Type fold);
void DMA2D_Picture_Fill_Calculate(DMA2D_Picture_Cfg_Type *cfg, DMA2D_LLI_Ctrl_Type *lliCfg);
void DMA2D_Picture_Transfer_Start(DMA2D_ID_Type dmaId, uint8_t ch, DMA2D_LLI_Ctrl_Type *lliCfg);
void DMA2D_Color_Key_Set(DMA2D_ID_Type dmaId, uint8_t ch, DMA2D_Color_Key_Type keyType, uint32_t keyValue);
void DMA2D_Color_Key_Enable(DMA2D_ID_Type dmaId, uint8_t ch);
void DMA2D_Color_Key_Disable(DMA2D_ID_Type dmaId, uint8_t ch);
/*@} end of group DMA2D_Public_Functions */

/*@} end of group DMA2D */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DMA2D_H__ */
