/**
  ******************************************************************************
  * @file    bl808_dsi.h
  * @version V1.0
  * @date    2021-04-22
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2021 Bouffalo Lab</center></h2>
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
#ifndef __BL808_DSI_H__
#define __BL808_DSI_H__

#include "dsi_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DSI
 *  @{
 */

/** @defgroup  DSI_Public_Types
 *  @{
 */

/**
 *  @brief DSI port type definition
 */
typedef enum {
    DSI0_ID,    /*!< DSI0 port define */
    DSI_ID_MAX, /*!< DSI max ID define */
} DSI_ID_Type;

/**
 *  @brief DSI interrupt type definition
 */
typedef enum {
    DSI_INT_ESCAPE_TX_END = 0x01,           /*!< DSI escape tx end interrupt */
    DSI_INT_LPDT_RX_END = 0x02,             /*!< DSI lpdt rx end interrupt */
    DSI_INT_ULPS_RX_END = 0x04,             /*!< DSI ulps rx end interrupt */
    DSI_INT_TRIGGER0_RX_END = 0x08,         /*!< DSI trigger0 rx end interrupt */
    DSI_INT_TRIGGER1_RX_END = 0x10,         /*!< DSI trigger1 rx end interrupt */
    DSI_INT_TRIGGER2_RX_END = 0x20,         /*!< DSI trigger2 rx end interrupt */
    DSI_INT_TRIGGER3_RX_END = 0x40,         /*!< DSI trigger3 rx end interrupt */
    DSI_INT_TX_FIFO_READY = 0x80,           /*!< DSI tx fifo ready interrupt */
    DSI_INT_RX_FIFO_READY = 0x100,          /*!< DSI rx fifo ready interrupt */
    DSI_INT_DATA_OVERRUN_ERR = 0x200,       /*!< DSI data overrun error interrupt */
    DSI_INT_DATA_UNDERRUN_ERR = 0x400,      /*!< DSI data underrun error interrupt */
    DSI_INT_PIXEL_COUNT_SMALL_ERR = 0x800,  /*!< DSI pixel count too small error interrupt */
    DSI_INT_PIXEL_COUNT_LARGE_ERR = 0x1000, /*!< DSI pixel count too large error interrupt */
    DSI_INT_FIFO_ERROR = 0x2000,            /*!< DSI fifo error interrupt */
    DSI_INT_ALL = 0x3FFF,                   /*!< All interrupt */
    DSI_INT_COUNT = 0x0E,                   /*!< Interrupt count */
} DSI_INT_Type;

/**
 *  @brief DSI fifo error type definition
 */
typedef enum {
    DSI_FIFO_ERR_TX_OVERFLOW = 0x01,  /*!< DSI tx fifo overflow */
    DSI_FIFO_ERR_TX_UNDERFLOW = 0x02, /*!< DSI tx fifo underflow */
    DSI_FIFO_ERR_RX_OVERFLOW = 0x04,  /*!< DSI rx fifo overflow */
    DSI_FIFO_ERR_RX_UNDERFLOW = 0x08, /*!< DSI rx fifo underflow */
} DSI_FIFO_Error_Type;

/**
 *  @brief DSI lane type definition
 */
typedef enum {
    DSI_LANE_DATA0 = 0x01,  /*!< Data0 */
    DSI_LANE_DATA1 = 0x02,  /*!< Data1 */
    DSI_LANE_DATA2 = 0x04,  /*!< Data2 */
    DSI_LANE_DATA3 = 0x08,  /*!< Data3 */
    DSI_LANE_CLOCK = 0x010, /*!< Clcok */
} DSI_Lane_Type;

/**
 *  @brief DSI data type definition
 */
typedef enum {
    DSI_DATA_YUV422 = 0x2c, /*!< YUV422, 8-bit */
    DSI_DATA_RGB565 = 0x0e, /*!< RGB565 */
    DSI_DATA_RGB666 = 0x2e, /*!< RGB666, lossely packed */
    DSI_DATA_RGB888 = 0x3e, /*!< RGB888 */
} DSI_Data_Type;

/**
 *  @brief DSI lane number type definition
 */
typedef enum {
    DSI_LANE_NUMBER_1, /*!< 1-lane TX */
    DSI_LANE_NUMBER_2, /*!< 2-lane TX */
    DSI_LANE_NUMBER_4, /*!< 4-lane TX */
} DSI_Lane_Number_Type;

/**
 *  @brief DSI lane order type definition
 */
typedef enum {
    DSI_LANE_ORDER_3210, /*!< Lane 3, 2, 1, 0 */
    DSI_LANE_ORDER_2130, /*!< Lane 2, 1, 3, 0 */
    DSI_LANE_ORDER_1320, /*!< Lane 1, 3, 2, 0 */
    DSI_LANE_ORDER_3120, /*!< Lane 3, 1, 2, 0 */
} DSI_Lane_Order_Type;

/**
 *  @brief DSI lane state type definition
 */
typedef enum {
    DSI_LANE_STAT_NORMAL = 0x00, /*!< Status normal */
    DSI_LANE_STAT_STOP = 0x01,   /*!< Status stop */
    DSI_LANE_STAT_BRIDGE = 0x02, /*!< Status bridge changing */
    DSI_LANE_STAT_ULP = 0x04,    /*!< Status ultra low power */
    DSI_LANE_STAT_HS=0x08,       /*!< Status high speed */
} DSI_Lane_State_Type;

/**
 *  @brief DSI clock lane option type definition
 */
typedef enum {
    DSI_CLOCK_LANE_OPT_ULP_ENTER = 0x01, /*!< Clock lane low power enter */
    DSI_CLOCK_LANE_OPT_ULP_EXIT = 0x02,  /*!< Clock lane low power exit */
    DSI_CLOCK_LANE_OPT_HS_REQ = 0x04,    /*!< Clock lane hs request */
    DSI_CLOCK_LANE_OPT_HS_EXIT = 0x08,   /*!< Clock lane hs exit */
} DSI_Clock_Lane_Opt_Type;

/**
 *  @brief Escape mode type definition
 */
typedef enum {
    DSI_ESCAPSE_TYPE_LPDT,    /*!< Escape type:LPDT */
    DSI_ESCAPSE_TYPE_TRIGGER, /*!< Escape type:TRIGGER */
    DSI_ESCAPSE_TYPE_ULPS,    /*!< Escape type:UPLS */
} DSI_Escape_Type;

/**
 *  @brief HS sync mode type definition
 */
typedef enum {
    DSI_HS_SYNC_EVENT_MODE, /*!< HS sync event mode */
    DSI_HS_SYNC_PULSE_MODE, /*!< HS sync pulse mode */
} DSI_HS_Sync_Type;

/**
 *  @brief DSI configuration strcut definition
 */
typedef struct
{
    uint8_t virtualChan;           /*!< DSI virtual channels */
    DSI_Lane_Number_Type laneNum;  /*!< DSI lane numbers */
    DSI_Lane_Order_Type laneOrder; /*!< DSI lane order */
    DSI_Data_Type dataType;        /*!< DSI data type */
    DSI_HS_Sync_Type syncType;     /*!< DSI HS sync mode select */
    uint8_t vsa;                   /*!< HS vertical sync active width */
    uint8_t vfp;                   /*!< HS vertical front porch width */
} DSI_CFG_Type;

/**
 *  @brief DSI configuration strcut definition
 */
typedef struct
{
    uint8_t virtualChan;   /*!< DSI LPDT msg virtual channels */
    uint8_t dataType;      /*!< DSI LPDT msg data type */
    uint8_t flag;          /*!< DSI LPDT msg flag */
    uint16_t tx_len;       /*!< DSI LPDT msg len */
    const uint8_t *tx_buf; /*!< DSI LPDT msg buffer */
    uint16_t rx_len;       /*!< DSI LPDT rx len */
    uint8_t *rx_buf;       /*!< DSI LPDT rx buffer */
} DSI_LPDT_MSG_Type;

/**
 *  @brief DSI DPHY configuration strcut definition
 */
typedef struct
{
    uint8_t time_clk_zero;     /*!< Clock lane zero time */
    uint8_t time_clk_trail;    /*!< Clock lane trail time */
    uint8_t time_clk_exit;     /*!< Clock lane exit time */
    uint8_t time_data_prepare; /*!< Data lane prepare time*/
    uint8_t time_data_zero;    /*!< Data lane zero time*/
    uint8_t time_data_trail;   /*!< Data lane trail time */
    uint8_t time_data_exit;    /*!< Data lane exit time */
    uint8_t time_lpx;          /*!< Low power time */
    uint8_t time_req_ready;    /*!< HS request time */
    uint8_t time_ta_get;       /*!< Bus turn around get time */
    uint8_t time_ta_go;        /*!< Bus turn around go time */
    uint32_t time_wakeup;      /*!< Low power wake up time */
} DSI_DPhy_CFG_Type;

/**
 *  @brief DSI FIFO configuration structure type definition
 */
typedef struct
{
    uint8_t txFifoDmaThreshold;  /*!< TX FIFO threshold, dma tx request will not be asserted if tx fifo count is less than this value */
    uint8_t rxFifoDmaThreshold;  /*!< RX FIFO threshold, dma rx request will not be asserted if rx fifo count is less than this value */
    BL_Fun_Type txFifoDmaEnable; /*!< Enable or disable tx dma req/ack interface */
    BL_Fun_Type rxFifoDmaEnable; /*!< Enable or disable rx dma req/ack interface */
} DSI_FifoCfg_Type;

/*@} end of group DSI_Public_Types */

/** @defgroup  DSI_Public_Constants
 *  @{
 */

/** @defgroup  DSI_ID_TYPE
 *  @{
 */
#define IS_DSI_ID_TYPE(type) (((type) == DSI0_ID) || \
                              ((type) == DSI_ID_MAX))

/** @defgroup  DSI_INT_TYPE
 *  @{
 */
#define IS_DSI_INT_TYPE(type) (((type) == DSI_INT_ESCAPE_TX_END) || \
                               ((type) == DSI_INT_LPDT_RX_END) || \
                               ((type) == DSI_INT_ULPS_RX_END) || \
                               ((type) == DSI_INT_TRIGGER0_RX_END) || \
                               ((type) == DSI_INT_TRIGGER1_RX_END) || \
                               ((type) == DSI_INT_TRIGGER2_RX_END) || \
                               ((type) == DSI_INT_TRIGGER3_RX_END) || \
                               ((type) == DSI_INT_TX_FIFO_READY) || \
                               ((type) == DSI_INT_RX_FIFO_READY) || \
                               ((type) == DSI_INT_DATA_OVERRUN_ERR) || \
                               ((type) == DSI_INT_DATA_UNDERRUN_ERR) || \
                               ((type) == DSI_INT_PIXEL_COUNT_SMALL_ERR) || \
                               ((type) == DSI_INT_PIXEL_COUNT_LARGE_ERR) || \
                               ((type) == DSI_INT_FIFO_ERROR) || \
                               ((type) == DSI_INT_ALL))

/** @defgroup  DSI_FIFO_ERROR_TYPE
 *  @{
 */
#define IS_DSI_FIFO_ERROR_TYPE(type) (((type) == DSI_FIFO_ERR_TX_OVERFLOW) || \
                                      ((type) == DSI_FIFO_ERR_TX_UNDERFLOW) || \
                                      ((type) == DSI_FIFO_ERR_RX_OVERFLOW) || \
                                      ((type) == DSI_FIFO_ERR_RX_UNDERFLOW))

/** @defgroup  DSI_LANE_TYPE
 *  @{
 */
#define IS_DSI_LANE_TYPE(type) (((type) == DSI_LANE_DATA0) || \
                                ((type) == DSI_LANE_DATA1) || \
                                ((type) == DSI_LANE_DATA2) || \
                                ((type) == DSI_LANE_DATA3) || \
                                ((type) == DSI_LANE_CLOCK))

/** @defgroup  DSI_DATA_TYPE
 *  @{
 */
#define IS_DSI_DATA_TYPE(type) (((type) == DSI_DATA_YUV422) || \
                                ((type) == DSI_DATA_RGB565) || \
                                ((type) == DSI_DATA_RGB666) || \
                                ((type) == DSI_DATA_RGB888))

/** @defgroup  DSI_LANE_NUMBER_TYPE
 *  @{
 */
#define IS_DSI_LANE_NUMBER_TYPE(type) (((type) == DSI_LANE_NUMBER_1) || \
                                       ((type) == DSI_LANE_NUMBER_2) || \
                                       ((type) == DSI_LANE_NUMBER_4))

/** @defgroup  DSI_LANE_ORDER_TYPE
 *  @{
 */
#define IS_DSI_LANE_ORDER_TYPE(type) (((type) == DSI_LANE_ORDER_3210) || \
                                      ((type) == DSI_LANE_ORDER_2130) || \
                                      ((type) == DSI_LANE_ORDER_1320) || \
                                      ((type) == DSI_LANE_ORDER_3120))

/** @defgroup  DSI_LANE_STATE_TYPE
 *  @{
 */
#define IS_DSI_LANE_STATE_TYPE(type) (((type) == DSI_LANE_STAT_NORMAL) || \
                                      ((type) == DSI_LANE_STAT_STOP) || \
                                      ((type) == DSI_LANE_STAT_BRIDGE) || \
                                      ((type) == DSI_LANE_STAT_ULP) || \
                                      ((type) == DSI_LANE_STAT_HS))

/** @defgroup  DSI_CLOCK_LANE_OPT_TYPE
 *  @{
 */
#define IS_DSI_CLOCK_LANE_OPT_TYPE(type) (((type) == DSI_CLOCK_LANE_OPT_ULP_ENTER) || \
                                          ((type) == DSI_CLOCK_LANE_OPT_ULP_EXIT) || \
                                          ((type) == DSI_CLOCK_LANE_OPT_HS_REQ) || \
                                          ((type) == DSI_CLOCK_LANE_OPT_HS_EXIT))

/** @defgroup  DSI_ESCAPE_TYPE
 *  @{
 */
#define IS_DSI_ESCAPE_TYPE(type) (((type) == DSI_ESCAPSE_TYPE_LPDT) || \
                                  ((type) == DSI_ESCAPSE_TYPE_TRIGGER) || \
                                  ((type) == DSI_ESCAPSE_TYPE_ULPS))

/** @defgroup  DSI_HS_SYNC_TYPE
 *  @{
 */
#define IS_DSI_HS_SYNC_TYPE(type) (((type) == DSI_HS_SYNC_EVENT_MODE) || \
                                   ((type) == DSI_HS_SYNC_PULSE_MODE))

/*@} end of group DSI_Public_Constants */

/** @defgroup  DSI_Public_Macros
 *  @{
 */
#define DSI_TX_FIFO_SIZE                   4
#define DSI_RX_FIFO_SIZE                   4
/*@} end of group DSI_Public_Macros */

/** @defgroup  DSI_Public_Functions
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
void DSI_IRQHandler(void);
#endif
void DSI_Init(DSI_ID_Type disId, DSI_CFG_Type *cfg);
void DSI_Deinit(DSI_ID_Type disId);
void DSI_Enable(DSI_ID_Type disId);
void DSI_Disable(DSI_ID_Type disId);
void DSI_IntMask(DSI_ID_Type dsiId, DSI_INT_Type intType, BL_Mask_Type intMask);
void DSI_IntClear(DSI_ID_Type dsiId, DSI_INT_Type intType);
void DSI_IntEnable(DSI_ID_Type dsiId, DSI_INT_Type intType);
DSI_INT_Type DSI_IntGet(DSI_ID_Type dsiId);
void DSI_Set_Line_Buffer_Threshold(DSI_ID_Type dsiId, uint32_t frameWidth, uint32_t dvpTsrcClock, uint32_t dsiClock, \
                                   DSI_Data_Type dataType, DSI_Lane_Number_Type laneNumber);
void DSI_Set_VSA_VFP(DSI_ID_Type dsiId, uint8_t vsa, uint8_t vfp);
void DSI_PHY_Reset(DSI_ID_Type dsiId);
void DSI_PHY_Config(DSI_ID_Type dsiId, DSI_DPhy_CFG_Type *phyCfg);
void DSI_PHY_Reinit_Data_Lanes(DSI_ID_Type dsiId, DSI_Lane_Type lanes);
void DSI_PHY_Enable_Lanes(DSI_ID_Type dsiId, DSI_Lane_Type lanes);
void DSI_PHY_Disable_Lanes(DSI_ID_Type dsiId, DSI_Lane_Type lanes);
void DSI_PHY_Data_Lane0_TurnAround(DSI_ID_Type dsiId);
void DSI_PHY_Stop_Data_Lanes(DSI_ID_Type dsiId, DSI_Lane_Type lanes);
void DSI_PHY_Get_Lanes_State(DSI_ID_Type dsiId, DSI_Lane_Type lane, DSI_Lane_State_Type *state);
void DSI_PHY_Set_Clock_Lane(DSI_ID_Type dsiId, DSI_Clock_Lane_Opt_Type opt);
void DSI_PHY_HS_Mode_Start(DSI_ID_Type dsiId);
void DSI_PHY_HS_Mode_Stop(DSI_ID_Type dsiId);
BL_Err_Type DSI_FifoConfig(DSI_ID_Type dsiId, DSI_FifoCfg_Type *fifoCfg);
BL_Err_Type DSI_LPDT_Send_Short_Packet(DSI_ID_Type dsiId, DSI_LPDT_MSG_Type *msg);
BL_Err_Type DSI_LPDT_Send_Long_Packet(DSI_ID_Type dsiId, DSI_LPDT_MSG_Type *msg);
BL_Err_Type DSI_LPDT_Recv_Packet(DSI_ID_Type dsiId, DSI_LPDT_MSG_Type *msg);
BL_Err_Type DSI_Send_Trigger_Command(DSI_ID_Type dsiId, uint8_t cmd);
BL_Err_Type DSI_Send_ULPS_Command(DSI_ID_Type dsiId);
BL_Err_Type DSI_Exit_ULPS(DSI_ID_Type dsiId);

/*@} end of group DSI_Public_Functions */

/*@} end of group DSI */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_DSI_H__ */
