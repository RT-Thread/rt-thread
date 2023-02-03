/**
  ******************************************************************************
  * @file    bl808_dma.h
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
#ifndef __BL808_DMA_H__
#define __BL808_DMA_H__

#include "dma_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DMA
 *  @{
 */

/** @defgroup  DMA_Public_Types
 *  @{
 */

/**
 *  @brief DMA port type definition
 */
typedef enum {
    DMA0_ID,    /*!< DMA0 port define,WLSYS,8 channels */
    DMA1_ID,    /*!< DMA1 port define,WLSYS,4 channels */
    DMA2_ID,    /*!< DMA2 port define,MMSYS,8 channels */
    DMA_ID_MAX, /*!< DMA MAX ID define */
} DMA_ID_Type;

/**
 *  @brief DMA endian type definition
 */
typedef enum {
    DMA_LITTLE_ENDIAN = 0, /*!< DMA use little endian */
    DMA_BIG_ENDIAN,        /*!< DMA use big endian */
} DMA_Endian_Type;

/**
 *  @brief DMA synchronization logic  type definition
 */
typedef enum {
    DMA_SYNC_LOGIC_ENABLE = 0, /*!< DMA synchronization logic enable */
    DMA_SYNC_LOGIC_DISABLE,    /*!< DMA synchronization logic disable */
} DMA_Sync_Logic_Type;

/**
 *  @brief DMA transfer width type definition
 */
typedef enum {
    DMA_TRNS_WIDTH_8BITS = 0, /*!< DMA transfer width:8 bits */
    DMA_TRNS_WIDTH_16BITS,    /*!< DMA transfer width:16 bits */
    DMA_TRNS_WIDTH_32BITS,    /*!< DMA transfer width:32 bits */
    DMA_TRNS_WIDTH_64BITS,    /*!< DMA transfer width:64 bits, only for DMA2 channel 0 and channel 1, others should not use this */
} DMA_Trans_Width_Type;

/**
 *  @brief DMA transfer direction type definition
 */
typedef enum {
    DMA_TRNS_M2M = 0, /*!< DMA transfer tyep:memory to memory */
    DMA_TRNS_M2P,     /*!< DMA transfer tyep:memory to peripheral */
    DMA_TRNS_P2M,     /*!< DMA transfer tyep:peripheral to memory */
    DMA_TRNS_P2P,     /*!< DMA transfer tyep:peripheral to peripheral */
} DMA_Trans_Dir_Type;

/**
 *  @brief DMA burst size type definition
 */
typedef enum {
    DMA_BURST_SIZE_1 = 0, /*!< DMA burst size:1 * transfer width */
    DMA_BURST_SIZE_4,     /*!< DMA burst size:4 * transfer width */
    DMA_BURST_SIZE_8,     /*!< DMA burst size:8 * transfer width */
    DMA_BURST_SIZE_16,    /*!< DMA burst size:16 * transfer width */
} DMA_Burst_Size_Type;

/**
 *  @brief DMA destination peripheral type definition
 */
typedef enum {
    DMA_REQ_UART0_RX = 0,  /*!< DMA request peripheral:UART0 RX, DMA0 and DMA1 support */
    DMA_REQ_UART0_TX = 1,  /*!< DMA request peripheral:UART0 TX, DMA0 and DMA1 support */
    DMA_REQ_UART1_RX = 2,  /*!< DMA request peripheral:UART1 RX, DMA0 and DMA1 support */
    DMA_REQ_UART1_TX = 3,  /*!< DMA request peripheral:UART1 TX, DMA0 and DMA1 support */
    DMA_REQ_UART2_RX = 4,  /*!< DMA request peripheral:UART2 RX, DMA0 and DMA1 support */
    DMA_REQ_UART2_TX = 5,  /*!< DMA request peripheral:UART2 TX, DMA0 and DMA1 support */
    DMA_REQ_I2C0_RX = 6,   /*!< DMA request peripheral:I2C0 RX, DMA0 and DMA1 support */
    DMA_REQ_I2C0_TX = 7,   /*!< DMA request peripheral:I2C0 TX, DMA0 and DMA1 support */
    DMA_REQ_IR_TX = 8,     /*!< DMA request peripheral:IR TX, DMA0 and DMA1 support */
    DMA_REQ_GPIO_TX = 9,   /*!< DMA request peripheral:GPIO TX, DMA0 and DMA1 support */
    DMA_REQ_SPI0_RX = 10,  /*!< DMA request peripheral:SPI0 RX, DMA0 and DMA1 support */
    DMA_REQ_SPI0_TX = 11,  /*!< DMA request peripheral:SPI0 TX, DMA0 and DMA1 support */
    DMA_REQ_AUDIO_RX = 12, /*!< DMA request peripheral:AUDIO RX, DMA0 and DMA1 support */
    DMA_REQ_AUDIO_TX = 13, /*!< DMA request peripheral:AUDIO TX, DMA0 and DMA1 support */
    DMA_REQ_I2C1_RX = 14,  /*!< DMA request peripheral:I2C1 RX, DMA0 and DMA1 support */
    DMA_REQ_I2C1_TX = 15,  /*!< DMA request peripheral:I2C1 TX, DMA0 and DMA1 support */
    DMA_REQ_I2S_RX = 16,   /*!< DMA request peripheral:I2S RX, DMA0 and DMA1 support */
    DMA_REQ_I2S_TX = 17,   /*!< DMA request peripheral:I2S TX, DMA0 and DMA1 support */
    DMA_REQ_PDM_RX = 18,   /*!< DMA request peripheral:PDM RX, DMA0 and DMA1 support */
    DMA_REQ_GPADC_RX = 22, /*!< DMA request peripheral:GPADC RX, DMA0 and DMA1 support */
    DMA_REQ_GPADC_TX = 23, /*!< DMA request peripheral:GPADC TX, DMA0 and DMA1 support */
    DMA_REQ_UART3_RX = 0,  /*!< DMA request peripheral:UART3 RX, only DMA2 support */
    DMA_REQ_UART3_TX = 1,  /*!< DMA request peripheral:UART3 TX, only DMA2 support */
    DMA_REQ_SPI1_RX = 2,   /*!< DMA request peripheral:SPI1 RX, only DMA2 support */
    DMA_REQ_SPI1_TX = 3,   /*!< DMA request peripheral:SPI1 TX, only DMA2 support */
    DMA_REQ_I2C2_RX = 6,   /*!< DMA request peripheral:I2C2 RX, only DMA2 support */
    DMA_REQ_I2C2_TX = 7,   /*!< DMA request peripheral:I2C2 TX, only DMA2 support */
    DMA_REQ_I2C3_RX = 8,   /*!< DMA request peripheral:I2C3 RX, only DMA2 support */
    DMA_REQ_I2C3_TX = 9,   /*!< DMA request peripheral:I2C3 TX, only DMA2 support */
    DMA_REQ_DSI_RX = 10,   /*!< DMA request peripheral:DSI RX, only DMA2 support */
    DMA_REQ_DSI_TX = 11,   /*!< DMA request peripheral:DSI TX, only DMA2 support */
    DMA_REQ_DBI_TX = 22,   /*!< DMA request peripheral:DBI TX, only DMA2 support */
    DMA_REQ_NONE = 0,      /*!< DMA request peripheral:None */
} DMA_Periph_Req_Type;

/**
 *  @brief DMA channel type definition
 */
typedef enum {
    DMA_CH0 = 0, /*!< DMA channel 0 */
    DMA_CH1,     /*!< DMA channel 1 */
    DMA_CH2,     /*!< DMA channel 2 */
    DMA_CH3,     /*!< DMA channel 3 */
    DMA_CH4,     /*!< DMA channel 4 */
    DMA_CH5,     /*!< DMA channel 5 */
    DMA_CH6,     /*!< DMA channel 6 */
    DMA_CH7,     /*!< DMA channel 7 */
    DMA_CH_MAX,  /*!<  */
} DMA_Chan_Type;

/**
 *  @brief DMA LLI Structure PING-PONG
 */
typedef enum {
    PING_INDEX = 0, /*!< PING INDEX */
    PONG_INDEX,     /*!< PONG INDEX */
} DMA_LLI_PP_Index_Type;

/**
 *  @brief DMA interrupt type definition
 */
typedef enum {
    DMA_INT_TCOMPLETED = 0, /*!< DMA completed interrupt */
    DMA_INT_ERR,            /*!< DMA error interrupt */
    DMA_INT_ALL,            /*!< All the interrupt */
} DMA_INT_Type;

/**
 *  @brief DMA Configuration Structure type definition
 */
typedef struct
{
    DMA_Endian_Type endian;        /*!< DMA endian type */
    DMA_Sync_Logic_Type syncLogic; /*!< DMA synchronization logic */
} DMA_Cfg_Type;

/**
 *  @brief DMA channel Configuration Structure type definition
 */
typedef struct
{
    uint32_t srcDmaAddr;                 /*!< Source address of DMA transfer */
    uint32_t destDmaAddr;                /*!< Destination address of DMA transfer */
    uint32_t transfLength;               /*!< Transfer length, 0~4095, this is burst count */
    DMA_Trans_Dir_Type dir;              /*!< Transfer dir control. 0: Memory to Memory, 1: Memory to peripheral, 2: Peripheral to memory */
    DMA_Chan_Type ch;                    /*!< Channel select 0-7 */
    DMA_Trans_Width_Type srcTransfWidth; /*!< Transfer width. 0: 8  bits, 1: 16  bits, 2: 32  bits, 3: 64  bits(only for DMA2 channel 0 and
                                                 channel 1) */
    DMA_Trans_Width_Type dstTransfWidth; /*!< Transfer width. 0: 8  bits, 1: 16  bits, 2: 32  bits, 3: 64  bits(only for DMA2 channel 0 and
                                                 channel 1) */
    DMA_Burst_Size_Type srcBurstSize;    /*!< Number of data items for burst transaction length. Each item width is as same as tansfer width.
                                                 0: 1 item, 1: 4 items, 2: 8 items, 3: 16 items */
    DMA_Burst_Size_Type dstBurstSize;    /*!< Number of data items for burst transaction length. Each item width is as same as tansfer width.
                                                 0: 1 item, 1: 4 items, 2: 8 items, 3: 16 items */
    BL_Fun_Type dstAddMode;              /*!<  */
    BL_Fun_Type dstMinMode;              /*!<  */
    uint8_t fixCnt;                      /*!<  */
    uint8_t srcAddrInc;                  /*!< Source address increment. 0: No change, 1: Increment */
    uint8_t destAddrInc;                 /*!< Destination address increment. 0: No change, 1: Increment */
    DMA_Periph_Req_Type srcPeriph;       /*!< Source peripheral select */
    DMA_Periph_Req_Type dstPeriph;       /*!< Destination peripheral select */
} DMA_Channel_Cfg_Type;

/**
 *  @brief DMA LLI control structure type definition
 */
typedef struct
{
    uint32_t srcDmaAddr;            /*!< Source address of DMA transfer */
    uint32_t destDmaAddr;           /*!< Destination address of DMA transfer */
    uint32_t nextLLI;               /*!< Next LLI address */
    struct DMA_Control_Reg dmaCtrl; /*!< DMA transaction control */
} DMA_LLI_Ctrl_Type;

/**
 *  @brief DMA LLI configuration structure type definition
 */
typedef struct
{
    DMA_Trans_Dir_Type dir;        /*!< Transfer dir control. 0: Memory to Memory, 1: Memory to peripheral, 2: Peripheral to memory */
    DMA_Periph_Req_Type srcPeriph; /*!< Source peripheral select */
    DMA_Periph_Req_Type dstPeriph; /*!< Destination peripheral select */
} DMA_LLI_Cfg_Type;

/**
 *  @brief DMA LLI Ping-Pong Buf definition
 */
typedef struct
{
    uint8_t idleIndex;                             /*!< Index Idle lliListHeader */
    uint8_t dmaId;                                 /*!< DMA ID used */
    uint8_t dmaChan;                               /*!< DMA LLI Channel used */
    DMA_LLI_Ctrl_Type *lliListHeader[2];           /*!< Ping-Pong BUf List Header */
    void (*onTransCompleted)(DMA_LLI_Ctrl_Type *); /*!< Completed Transmit One List Callback Function */
} DMA_LLI_PP_Buf;

/**
 *  @brief DMA LLI Ping-Pong Structure definition
 */
typedef struct
{
    uint8_t pingpongIndex;                /*!< Ping or Pong Trigger TC */
    uint8_t dmaId;                        /*!< DMA ID used */
    uint8_t dmaChan;                      /*!< DMA LLI Channel used */
    struct DMA_Control_Reg dmaCtrlRegVal; /*!< DMA Basic Pararmeter */
    DMA_LLI_Cfg_Type *lliCfg;             /*!< LLI Config parameter */
    uint32_t operatePeriphAddr;           /*!< Operate Peripheral register address */
    uint32_t pingpongBufAddr[2];          /*!< Ping-Pong addr */
} DMA_LLI_PP_Struct;

/*@} end of group DMA_Public_Types */

/** @defgroup  DMA_Public_Constants
 *  @{
 */

/** @defgroup  DMA_ID_TYPE
 *  @{
 */
#define IS_DMA_ID_TYPE(type) (((type) == DMA0_ID) || \
                              ((type) == DMA1_ID) || \
                              ((type) == DMA2_ID) || \
                              ((type) == DMA_ID_MAX))

/** @defgroup  DMA_ENDIAN_TYPE
 *  @{
 */
#define IS_DMA_ENDIAN_TYPE(type) (((type) == DMA_LITTLE_ENDIAN) || \
                                  ((type) == DMA_BIG_ENDIAN))

/** @defgroup  DMA_SYNC_LOGIC_TYPE
 *  @{
 */
#define IS_DMA_SYNC_LOGIC_TYPE(type) (((type) == DMA_SYNC_LOGIC_ENABLE) || \
                                      ((type) == DMA_SYNC_LOGIC_DISABLE))

/** @defgroup  DMA_TRANS_WIDTH_TYPE
 *  @{
 */
#define IS_DMA_TRANS_WIDTH_TYPE(type) (((type) == DMA_TRNS_WIDTH_8BITS) ||  \
                                       ((type) == DMA_TRNS_WIDTH_16BITS) || \
                                       ((type) == DMA_TRNS_WIDTH_32BITS) || \
                                       ((type) == DMA_TRNS_WIDTH_64BITS))

/** @defgroup  DMA_TRANS_DIR_TYPE
 *  @{
 */
#define IS_DMA_TRANS_DIR_TYPE(type) (((type) == DMA_TRNS_M2M) || \
                                     ((type) == DMA_TRNS_M2P) || \
                                     ((type) == DMA_TRNS_P2M) || \
                                     ((type) == DMA_TRNS_P2P))

/** @defgroup  DMA_BURST_SIZE_TYPE
 *  @{
 */
#define IS_DMA_BURST_SIZE_TYPE(type) (((type) == DMA_BURST_SIZE_1) || \
                                      ((type) == DMA_BURST_SIZE_4) || \
                                      ((type) == DMA_BURST_SIZE_8) || \
                                      ((type) == DMA_BURST_SIZE_16))

/** @defgroup  DMA_PERIPH_REQ_TYPE
 *  @{
 */
#define IS_DMA_PERIPH_REQ_TYPE(type) (((type) == DMA_REQ_UART0_RX) || \
                                      ((type) == DMA_REQ_UART0_TX) || \
                                      ((type) == DMA_REQ_UART1_RX) || \
                                      ((type) == DMA_REQ_UART1_TX) || \
                                      ((type) == DMA_REQ_UART2_RX) || \
                                      ((type) == DMA_REQ_UART2_TX) || \
                                      ((type) == DMA_REQ_I2C0_RX) ||  \
                                      ((type) == DMA_REQ_I2C0_TX) ||  \
                                      ((type) == DMA_REQ_IR_TX) ||    \
                                      ((type) == DMA_REQ_GPIO_TX) ||  \
                                      ((type) == DMA_REQ_SPI0_RX) ||  \
                                      ((type) == DMA_REQ_SPI0_TX) ||  \
                                      ((type) == DMA_REQ_AUDIO_RX) || \
                                      ((type) == DMA_REQ_AUDIO_TX) || \
                                      ((type) == DMA_REQ_I2C1_RX) ||  \
                                      ((type) == DMA_REQ_I2C1_TX) ||  \
                                      ((type) == DMA_REQ_I2S_RX) ||   \
                                      ((type) == DMA_REQ_I2S_TX) ||   \
                                      ((type) == DMA_REQ_PDM_RX) ||   \
                                      ((type) == DMA_REQ_GPADC_RX) || \
                                      ((type) == DMA_REQ_GPADC_TX) || \
                                      ((type) == DMA_REQ_UART3_RX) || \
                                      ((type) == DMA_REQ_UART3_TX) || \
                                      ((type) == DMA_REQ_SPI1_RX) ||  \
                                      ((type) == DMA_REQ_SPI1_TX) ||  \
                                      ((type) == DMA_REQ_I2C2_RX) ||  \
                                      ((type) == DMA_REQ_I2C2_TX) ||  \
                                      ((type) == DMA_REQ_I2C3_RX) ||  \
                                      ((type) == DMA_REQ_I2C3_TX) ||  \
                                      ((type) == DMA_REQ_DSI_RX) ||   \
                                      ((type) == DMA_REQ_DBI_TX) ||   \
                                      ((type) == DMA_REQ_DBI_TX) ||   \
                                      ((type) == DMA_REQ_NONE))

/** @defgroup  DMA_CHAN_TYPE
 *  @{
 */
#define IS_DMA_CHAN_TYPE(type) (((type) == DMA_CH0) || \
                                ((type) == DMA_CH1) || \
                                ((type) == DMA_CH2) || \
                                ((type) == DMA_CH3) || \
                                ((type) == DMA_CH4) || \
                                ((type) == DMA_CH5) || \
                                ((type) == DMA_CH6) || \
                                ((type) == DMA_CH7) || \
                                ((type) == DMA_CH_MAX))

/** @defgroup  DMA_LLI_PP_INDEX_TYPE
 *  @{
 */
#define IS_DMA_LLI_PP_INDEX_TYPE(type) (((type) == PING_INDEX) || \
                                        ((type) == PONG_INDEX))

/** @defgroup  DMA_INT_TYPE
 *  @{
 */
#define IS_DMA_INT_TYPE(type) (((type) == DMA_INT_TCOMPLETED) || \
                               ((type) == DMA_INT_ERR) ||        \
                               ((type) == DMA_INT_ALL))

/*@} end of group DMA_Public_Constants */

/** @defgroup  DMA_Public_Macros
 *  @{
 */
#define DMA_PINC_ENABLE  1
#define DMA_PINC_DISABLE 0
#define DMA_MINC_ENABLE  1
#define DMA_MINC_DISABLE 0

/*@} end of group DMA_Public_Macros */

/** @defgroup  DMA_Public_Functions
 *  @{
 */

/**
 *  @brief DMA Functions
 */
#ifndef BFLB_USE_HAL_DRIVER
void DMA0_ALL_IRQHandler(void);
void DMA1_ALL_IRQHandler(void);
void DMA2_INT0_IRQHandler(void);
void DMA2_INT1_IRQHandler(void);
void DMA2_INT2_IRQHandler(void);
void DMA2_INT3_IRQHandler(void);
void DMA2_INT4_IRQHandler(void);
void DMA2_INT5_IRQHandler(void);
void DMA2_INT6_IRQHandler(void);
void DMA2_INT7_IRQHandler(void);
#endif
void DMA_Enable(DMA_ID_Type dmaId);
void DMA_Disable(DMA_ID_Type dmaId);
void DMA_Channel_Init(DMA_ID_Type dmaId, DMA_Channel_Cfg_Type *chCfg);
void DMA_DeInit(DMA_ID_Type dmaId);
void DMA_Channel_Update_SrcMemcfg(DMA_ID_Type dmaId, uint8_t ch, uint32_t memAddr, uint32_t len);
void DMA_Channel_Update_DstMemcfg(DMA_ID_Type dmaId, uint8_t ch, uint32_t memAddr, uint32_t len);
uint32_t DMA_Channel_TranferSize(DMA_ID_Type dmaId, uint8_t ch);
BL_Sts_Type DMA_Channel_Is_Busy(DMA_ID_Type dmaId, uint8_t ch);
void DMA_Channel_Enable(DMA_ID_Type dmaId, uint8_t ch);
void DMA_Channel_Disable(DMA_ID_Type dmaId, uint8_t ch);
void DMA_LLI_Init(DMA_ID_Type dmaId, uint8_t ch, DMA_LLI_Cfg_Type *lliCfg);
void DMA_LLI_Update(DMA_ID_Type dmaId, uint8_t ch, uint32_t LLI);
uint32_t DMA_LLI_Get_Counter(DMA_ID_Type dmaId, uint8_t ch);
void DMA_IntMask(DMA_ID_Type dmaId, uint8_t ch, DMA_INT_Type intType, BL_Mask_Type intMask);
void DMA_LLI_PpBuf_Start_New_Transmit(DMA_LLI_PP_Buf *dmaPpBuf);
DMA_LLI_Ctrl_Type *DMA_LLI_PpBuf_Remove_Completed_List(DMA_LLI_PP_Buf *dmaPpBuf);
void DMA_LLI_PpBuf_Append(DMA_LLI_PP_Buf *dmaPpBuf, DMA_LLI_Ctrl_Type *dmaLliList);
void DMA_LLI_PpBuf_Destroy(DMA_LLI_PP_Buf *dmaPpBuf);
void DMA_Int_Callback_Install(DMA_ID_Type dmaId, DMA_Chan_Type dmaChan, DMA_INT_Type intType, intCallback_Type *cbFun);
void DMA_LLI_PpStruct_Start(DMA_LLI_PP_Struct *dmaPpStruct);
void DMA_LLI_PpStruct_Stop(DMA_LLI_PP_Struct *dmaPpStruct);
BL_Err_Type DMA_LLI_PpStruct_Init(DMA_LLI_PP_Struct *dmaPpStruct);
BL_Err_Type DMA_LLI_PpStruct_Set_Transfer_Len(DMA_LLI_PP_Struct *dmaPpStruct,
                                              uint16_t Ping_Transfer_len, uint16_t Pong_Transfer_len);

/*@} end of group DMA_Public_Functions */

/*@} end of group DMA */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DMA_H__ */
