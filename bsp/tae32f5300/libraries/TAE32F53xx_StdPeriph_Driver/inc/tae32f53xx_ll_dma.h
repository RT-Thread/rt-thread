/**
  ******************************************************************************
  * @file    tae32f53xx_ll_dma.h
  * @author  MCD Application Team
  * @brief   Header file for DMA LL module.
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Tai-Action.
  * All rights reserved.</center></h2>
  *
  * This software is licensed by Tai-Action under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TAE32F53XX_LL_DMA_H_
#define _TAE32F53XX_LL_DMA_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup DMA_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Constants DMA LL Exported Constants
  * @brief    DMA LL Exported Constants
  * @{
  */

/**
  * @brief DMA block size max
  */
#define LL_DMA_BLOCK_SIZE_MAX       (0xfffU)

/**
  * @brief SRAMBC address start
  */
#define LL_DMA_SRMBC_ADDR_START     (0x20004000UL)

/**
  * @brief SRAMBC address end
  */
#define LL_DMA_SRMBC_ADDR_END       (0x20006000UL - 1)

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Types DMA LL Exported Types
  * @brief    DMA LL Exported Types
  * @{
  */

/**
  * @brief DMA Source Peripheral bus type definition
  */
typedef enum {
    DMA_SRC_PERIPH_BUS_AHB_MST1 = DMA_CH_CR0_SMS_AHB_MST1,      /*!< Source Peripheral bus AHB Master1      */
    DMA_SRC_PERIPH_BUS_AHB_MST2 = DMA_CH_CR0_SMS_AHB_MST2,      /*!< Source Peripheral bus AHB Master2      */
} DMA_SrcPeriphBusETypeDef;

/**
  * @brief DMA Destination Peripheral bus type definition
  */
typedef enum {
    DMA_DST_PERIPH_BUS_AHB_MST1 = DMA_CH_CR0_DMS_AHB_MST1,      /*!< Destination Peripheral bus AHB Master1 */
    DMA_DST_PERIPH_BUS_AHB_MST2 = DMA_CH_CR0_DMS_AHB_MST2,      /*!< Destination Peripheral bus AHB Master2 */
} DMA_DstPeriphBusETypeDef;

/**
  * brief DMA transfer type type definition
  */
typedef enum {
    DMA_TRANS_TYPE_M2M = DMA_CH_CR0_TTC_M2M,        /*!< Transfer type M2M          */
    DMA_TRANS_TYPE_M2P = DMA_CH_CR0_TTC_M2P,        /*!< Transfer type M2P          */
    DMA_TRANS_TYPE_P2M = DMA_CH_CR0_TTC_P2M,        /*!< Transfer type P2M          */
    DMA_TRANS_TYPE_P2P = DMA_CH_CR0_TTC_P2P,        /*!< Transfer type P2P          */
} DMA_TransTypeETypeDef;

/**
  * @brief DMA Source burst length type definition
  */
typedef enum {
    DMA_SRC_BURST_LEN_1 = DMA_CH_CR0_SBTL_1,        /*!< Source burst length 1      */
    DMA_SRC_BURST_LEN_4 = DMA_CH_CR0_SBTL_4,        /*!< Source burst length 4      */
    DMA_SRC_BURST_LEN_8 = DMA_CH_CR0_SBTL_8,        /*!< Source burst length 8      */
} DMA_SrcBurstLenETypeDef;

/**
  * @brief DMA Destination burst length type definition
  */
typedef enum {
    DMA_DST_BURST_LEN_1 = DMA_CH_CR0_DBTL_1,        /*!< Destination burst length 1 */
    DMA_DST_BURST_LEN_4 = DMA_CH_CR0_DBTL_4,        /*!< Destination burst length 4 */
    DMA_DST_BURST_LEN_8 = DMA_CH_CR0_DBTL_8,        /*!< Destination burst length 8 */
} DMA_DstBurstLenETypeDef;

/**
  * @brief DMA Source address mode type definition
  */
typedef enum {
    DMA_SRC_ADDR_MODE_INC = DMA_CH_CR0_SINC_INC,    /*!< Source address mode Increase       */
    DMA_SRC_ADDR_MODE_DEC = DMA_CH_CR0_SINC_DEC,    /*!< Source address mode Decrease       */
    DMA_SRC_ADDR_MODE_FIX = DMA_CH_CR0_SINC_FIX,    /*!< Source address mode Fixed          */
} DMA_SrcAddrModeETypeDef;

/**
  * @brief DMA Destination address mode type definition
  */
typedef enum {
    DMA_DST_ADDR_MODE_INC = DMA_CH_CR0_DINC_INC,    /*!< Destination address mode Increase  */
    DMA_DST_ADDR_MODE_DEC = DMA_CH_CR0_DINC_DEC,    /*!< Destination address mode Decrease  */
    DMA_DST_ADDR_MODE_FIX = DMA_CH_CR0_DINC_FIX,    /*!< Destination address mode Fixed     */
} DMA_DstAddrModeETypeDef;

/**
  * @brief DMA Source transfer width type definition
  */
typedef enum {
    DMA_SRC_TRANS_WIDTH_8b  = DMA_CH_CR0_STW_8b,    /*!< Source transfer width 8bit         */
    DMA_SRC_TRANS_WIDTH_16b = DMA_CH_CR0_STW_16b,   /*!< Source transfer width 16bit        */
    DMA_SRC_TRANS_WIDTH_32b = DMA_CH_CR0_STW_32b,   /*!< Source transfer width 32bit        */
} DMA_SrcTransWidthETypeDef;

/**
  * @brief DMA Destination transfer width type definition
  */
typedef enum {
    DMA_DST_TRANS_WIDTH_8b  = DMA_CH_CR0_DTW_8b,    /*!< Destination transfer width 8bit    */
    DMA_DST_TRANS_WIDTH_16b = DMA_CH_CR0_DTW_16b,   /*!< Destination transfer width 16bit   */
    DMA_DST_TRANS_WIDTH_32b = DMA_CH_CR0_DTW_32b,   /*!< Destination transfer width 32bit   */
} DMA_DstTransWidthETypeDef;

/**
  * @brief DMA Source handshaking interface type definition
  */
typedef enum {
    DMA_SRC_HANDSHAKE_IFC_MEMORY   = 0,                             /*!< Source handshaking interface MEMORY        */
    DMA_SRC_HANDSHAKE_IFC_I2C0_TX  = DMA_CH_CR3_SHSIF_I2C0_TX,      /*!< Source handshaking interface I2C0_TX       */
    DMA_SRC_HANDSHAKE_IFC_I2C0_RX  = DMA_CH_CR3_SHSIF_I2C0_RX,      /*!< Source handshaking interface I2C0_RX       */
    DMA_SRC_HANDSHAKE_IFC_I2C1_TX  = DMA_CH_CR3_SHSIF_I2C1_TX,      /*!< Source handshaking interface I2C1_TX       */
    DMA_SRC_HANDSHAKE_IFC_I2C1_RX  = DMA_CH_CR3_SHSIF_I2C1_RX,      /*!< Source handshaking interface I2C1_RX       */
    DMA_SRC_HANDSHAKE_IFC_UART0_TX = DMA_CH_CR3_SHSIF_UART0_TX,     /*!< Source handshaking interface UART0_TX      */
    DMA_SRC_HANDSHAKE_IFC_UART0_RX = DMA_CH_CR3_SHSIF_UART0_RX,     /*!< Source handshaking interface UART0_RX      */
    DMA_SRC_HANDSHAKE_IFC_UART1_TX = DMA_CH_CR3_SHSIF_UART1_TX,     /*!< Source handshaking interface UART1_TX      */
    DMA_SRC_HANDSHAKE_IFC_UART1_RX = DMA_CH_CR3_SHSIF_UART1_RX,     /*!< Source handshaking interface UART1_RX      */
} DMA_SrcHandshakeIfcETypeDef;

/**
  * @brief DMA Destination handshaking interface type definition
  */
typedef enum {
    DMA_DST_HANDSHAKE_IFC_MEMORY   = 0,                             /*!< Destination handshaking interface MEMORY   */
    DMA_DST_HANDSHAKE_IFC_I2C0_TX  = DMA_CH_CR3_DHSIF_I2C0_TX,      /*!< Destination handshaking interface I2C0_TX  */
    DMA_DST_HANDSHAKE_IFC_I2C0_RX  = DMA_CH_CR3_DHSIF_I2C0_RX,      /*!< Destination handshaking interface I2C0_RX  */
    DMA_DST_HANDSHAKE_IFC_I2C1_TX  = DMA_CH_CR3_DHSIF_I2C1_TX,      /*!< Destination handshaking interface I2C1_TX  */
    DMA_DST_HANDSHAKE_IFC_I2C1_RX  = DMA_CH_CR3_DHSIF_I2C1_RX,      /*!< Destination handshaking interface I2C1_RX  */
    DMA_DST_HANDSHAKE_IFC_UART0_TX = DMA_CH_CR3_DHSIF_UART0_TX,     /*!< Destination handshaking interface UART0_TX */
    DMA_DST_HANDSHAKE_IFC_UART0_RX = DMA_CH_CR3_DHSIF_UART0_RX,     /*!< Destination handshaking interface UART0_RX */
    DMA_DST_HANDSHAKE_IFC_UART1_TX = DMA_CH_CR3_DHSIF_UART1_TX,     /*!< Destination handshaking interface UART1_TX */
    DMA_DST_HANDSHAKE_IFC_UART1_RX = DMA_CH_CR3_DHSIF_UART1_RX,     /*!< Destination handshaking interface UART1_RX */
} DMA_DstHandshakeIfcETypeDef;

/**
  * @brief DMA channel type definition
  */
typedef enum {
    DMA_CHANNEL_0   = 0U,           /*!< DMA Channel 0          */
    DMA_CHANNEL_1   = 1U,           /*!< DMA Channel 1          */
    DMA_CHANNEL_NUM = 2U,           /*!< DMA Channel Number     */
    DMA_CHANNEL_INVALID = 0xFFU,    /*!< DMA Channel Invalid    */
} DMA_ChannelETypeDef;

/**
  * @brief DMA State type definition
  */
typedef enum {
    DMA_STATE_RESET = 0,            /*!< DMA State Reset:   not yet initialized or disabled */
    DMA_STATE_READY,                /*!< DMA State Ready:   initialized and ready for use   */
    DMA_STATE_BUSY,                 /*!< DMA State Busy:    process is ongoing              */
} DMA_StateETypeDef;


/**
  * @brief DMA IRQ callback function type definition
  */
typedef void (*DMA_IRQCallback)(void *arg);


/**
  * @brief DMA user config type definition
  */
typedef struct __DMA_UserCfgTypeDef {
    DMA_TransTypeETypeDef       trans_type;     /*!< transfer type                                      */
    DMA_SrcAddrModeETypeDef     src_addr_mode;  /*!< source address mode                                */
    DMA_DstAddrModeETypeDef     dst_addr_mode;  /*!< destination address mode                           */
    DMA_SrcTransWidthETypeDef   src_data_width; /*!< source data width                                  */
    DMA_DstTransWidthETypeDef   dst_data_width; /*!< destination data width                             */
    DMA_SrcHandshakeIfcETypeDef src_hs_ifc;     /*!< source handshake interface                         */
    DMA_DstHandshakeIfcETypeDef dst_hs_ifc;     /*!< destination handshake interface                    */

    void *end_arg;                              /*!< argument of transfer complete callback fucntion    */
    DMA_IRQCallback end_callback;               /*!< transfer complete callback fucntion                */
    void *err_arg;                              /*!< argument of transfer error callback fucntion       */
    DMA_IRQCallback err_callback;               /*!< transfer error callback fucntion                   */
} DMA_UserCfgTypeDef;

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup DMA_LL_Exported_Macros DMA LL Exported Macros
  * @brief    DMA LL Exported Macros
  * @{
  */

/**
  * @brief  Source address set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  addr Source address
  * @return None
  */
#define __LL_DMA_SrcAddr_Set(__DMA__, ch, addr)         WRITE_REG((__DMA__)->CH[(ch)].SAR, addr)


/**
  * @brief  Destination address set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  addr Destination address
  * @return None
  */
#define __LL_DMA_DstAddr_Set(__DMA__, ch, addr)         WRITE_REG((__DMA__)->CH[(ch)].DAR, addr)


/**
  * @brief  Source peripheral bus set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  bus Source peripheral bus
  * @return None
  */
#define __LL_DMA_SrcPeriphBus_Set(__DMA__, ch, bus)     MODIFY_REG((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_SMS_Msk, bus)

/**
  * @brief  Destination peripheral bus set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  bus Destination peripheral bus
  * @return None
  */
#define __LL_DMA_DstPeriphBus_Set(__DMA__, ch, bus)     MODIFY_REG((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_DMS_Msk, bus)

/**
  * @brief  Transfer type set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  type Transfer type
  * @return None
  */
#define __LL_DMA_TransType_Set(__DMA__, ch, type)       MODIFY_REG((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_TTC_Msk, type)

/**
  * @brief  Source burst length set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  len Source burst length
  * @return None
  */
#define __LL_DMA_SrcBurstLen_Set(__DMA__, ch, len)      MODIFY_REG((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_SBTL_Msk, len)

/**
  * @brief  Destination burst length set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  len Destination burst length
  * @return None
  */
#define __LL_DMA_DstBurstLen_Set(__DMA__, ch, len)      MODIFY_REG((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_DBTL_Msk, len)

/**
  * @brief  Source address mode set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  mode Source address mode
  * @return None
  */
#define __LL_DMA_SrcAddrMode_Set(__DMA__, ch, mode)     MODIFY_REG((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_SINC_Msk, mode)

/**
  * @brief  Destination address mode set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  mode Destination address mode
  * @return None
  */
#define __LL_DMA_DstAddrMode_Set(__DMA__, ch, mode)     MODIFY_REG((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_DINC_Msk, mode)

/**
  * @brief  Source transfer width set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  width Source transfer width
  * @return None
  */
#define __LL_DMA_SrcTransWidth_Set(__DMA__, ch, width)  MODIFY_REG((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_STW_Msk, width)

/**
  * @brief  Source transfer width get
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @retval 0 8 bits
  * @retval 1 16 bits
  * @retval 2 32 bits
  */
#define __LL_DMA_SrcTransWidth_Get(__DMA__, ch)         (READ_BIT((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_STW_Msk) >> DMA_CH_CR0_STW_Pos)

/**
  * @brief  Destination transfer width set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  width Destination transfer width
  * @return None
  */
#define __LL_DMA_DstTransWidth_Set(__DMA__, ch, width)  MODIFY_REG((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_DTW_Msk, width)

/**
  * @brief  Channel interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_Channel_Int_En(__DMA__, ch)             SET_BIT((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_CHIE_Msk)

/**
  * @brief  Channel interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_Channel_Int_Dis(__DMA__, ch)            CLEAR_BIT((__DMA__)->CH[(ch)].CR0, DMA_CH_CR0_CHIE_Msk)

/**
  * @brief  Channel register CR0 write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  val write value
  * @return None
  */
#define __LL_DMA_ChannelRegCR0_Write(__DMA__, ch, val)  WRITE_REG((__DMA__)->CH[(ch)].CR0, val)


/**
  * @brief  Judge is block transfer done or not
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @retval 0 isn't block transfer done
  * @retval 1 is block transfer done
  */
#define __LL_DMA_IsBlockTransDone(__DMA__, ch)          (READ_BIT((__DMA__)->CH[(ch)].CR1, DMA_CH_CR1_DONE_Msk) >> DMA_CH_CR1_DONE_Pos)

/**
  * @brief  Block transfer done clear
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_BlockTransDone_Clr(__DMA__, ch)        CLEAR_BIT((__DMA__)->CH[(ch)].CR1, DMA_CH_CR1_DONE_Msk)

/**
  * @brief  Block transfer count set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  cnt Block transfer count
  * @return None
  */
#define __LL_DMA_BlockTransCnt_Set(__DMA__, ch, cnt)    \
        MODIFY_REG((__DMA__)->CH[(ch)].CR1, DMA_CH_CR1_BTCNT_Msk, (((cnt) & 0xfffUL) << DMA_CH_CR1_BTCNT_Pos))

/**
  * @brief  Channel register CR1 write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  val write value
  * @return None
  */
#define __LL_DAM_ChannelRegCR1_Write(__DMA__, ch, val)  WRITE_REG((__DMA__)->CH[(ch)].CR1, val)


/**
  * @brief  Burst length max set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  max Burst length max
  * @return None
  */
#define __LL_DMA_BurstLenMax_Set(__DMA__, ch, max)      \
        MODIFY_REG((__DMA__)->CH[(ch)].CR2, DMA_CH_CR2_MBL_Msk, (((max) & 0x3ffUL) << DMA_CH_CR2_MBL_Pos))

/**
  * @brief  Source handshake mode set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_SrcHandshakeMode_Set(__DMA__, ch)      SET_BIT((__DMA__)->CH[(ch)].CR2, DMA_CH_CR2_SHSM_Msk)

/**
  * @brief  Source handshake mode clear
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_SrcHandshakeMode_Clr(__DMA__, ch)      CLEAR_BIT((__DMA__)->CH[(ch)].CR2, DMA_CH_CR2_SHSM_Msk)

/**
  * @brief  Destination handshake mode set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_DstHandshakeMode_Set(__DMA__, ch)      SET_BIT((__DMA__)->CH[(ch)].CR2, DMA_CH_CR2_DHSM_Msk)

/**
  * @brief  Destination handshake mode clear
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_DstHandshakeMode_Clr(__DMA__, ch)      CLEAR_BIT((__DMA__)->CH[(ch)].CR2, DMA_CH_CR2_DHSM_Msk)

/**
  * @brief  Judge is channel FIFO empty or not
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @retval 0 isn't channel FIFO empty
  * @retval 1 is channel FIFO empty
  */
#define __LL_DMA_IsChannelFIFOEmpty(__DMA__, ch)        \
        (READ_BIT((__DMA__)->CH[(ch)].CR2, DMA_CH_CR2_FIFO_EF_Msk) >> DMA_CH_CR2_FIFO_EF_Pos)

/**
  * @brief  Channel suspend set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_ChannelSuspend_Set(__DMA__, ch)        SET_BIT((__DMA__)->CH[(ch)].CR2, DMA_CH_CR2_SUSP_Msk)

/**
  * @brief  Channel suspend clear
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_ChannelSuspend_Clr(__DMA__, ch)        CLEAR_BIT((__DMA__)->CH[(ch)].CR2, DMA_CH_CR2_SUSP_Msk)

/**
  * @brief  Channel priority set high
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_ChannelPriHigh_Set(__DMA__, ch)        SET_BIT((__DMA__)->CH[(ch)].CR2, DMA_CH_CR2_PRI_Msk)

/**
  * @brief  Channel priority set low
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_ChannelPriLow_Set(__DMA__, ch)         CLEAR_BIT((__DMA__)->CH[(ch)].CR2, DMA_CH_CR2_PRI_Msk)

/**
  * @brief  Channel register CR2 write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  val write value
  * @return None
  */
#define __LL_DAM_ChannelRegCR2_Write(__DMA__, ch, val)  WRITE_REG((__DMA__)->CH[(ch)].CR2, val)


/**
  * @brief  Destination handshake interface set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  ifc Destination handshake interface
  * @return None
  */
#define __LL_DMA_DstHandshakeIfc_Set(__DMA__, ch, ifc)  MODIFY_REG((__DMA__)->CH[(ch)].CR3, DMA_CH_CR3_DHSIF_Msk, ifc)

/**
  * @brief  Source handshake interface set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  ifc Source handshake interface
  * @return None
  */
#define __LL_DMA_SrcHandshakeIfc_Set(__DMA__, ch, ifc)  MODIFY_REG((__DMA__)->CH[(ch)].CR3, DMA_CH_CR3_SHSIF_Msk, ifc)

/**
  * @brief  FIFO mode half set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_FIFOModeHalf_Set(__DMA__, ch)          SET_BIT((__DMA__)->CH[(ch)].CR3, DMA_CH_CR3_FMD_Msk)

/**
  * @brief  FIFO mode once set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_FIFOModeOnce_Set(__DMA__, ch)          CLEAR_BIT((__DMA__)->CH[(ch)].CR3, DMA_CH_CR3_FMD_Msk)

/**
  * @brief  Channel folw control mode source request set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_ChFlowModeSrcReq_Set(__DMA__, ch)      CLEAR_BIT((__DMA__)->CH[(ch)].CR3, DMA_CH_CR3_FCMD_Msk)

/**
  * @brief  Channel folw control mode destination request set
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @return None
  */
#define __LL_DMA_ChFlowModeDstReq_Set(__DMA__, ch)      SET_BIT((__DMA__)->CH[(ch)].CR3, DMA_CH_CR3_FCMD_Msk)

/**
  * @brief  Channel register CR3 write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  ch DMA channel
  * @param  val write value
  * @return None
  */
#define __LL_DAM_ChannelRegCR3_Write(__DMA__, ch, val)  WRITE_REG((__DMA__)->CH[(ch)].CR3, val)


/**
  * @brief  Channel 1 transfer complete status get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 Channel 1 transfer hasn't completed
  * @retval 1 Channel 1 transfer has completed
  */
#define __LL_DMA_Ch1TransComSta_Get(__DMA__)       (READ_BIT((__DMA__)->TSR, DMA_TSR_TS_CH1_Msk) >> DMA_TSR_TS_CH1_Pos)

/**
  * @brief  Channel 0 transfer complete status get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 Channel 0 transfer hasn't completed
  * @retval 1 Channel 0 transfer has completed
  */
#define __LL_DMA_Ch0TransComSta_Get(__DMA__)       (READ_BIT((__DMA__)->TSR, DMA_TSR_TS_CH0_Msk) >> DMA_TSR_TS_CH0_Pos)


/**
  * @brief  Channel 1 block transfer complete status get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 Channel 1 block transfer hasn't completed
  * @retval 1 Channel 1 block transfer has completed
  */
#define __LL_DMA_Ch1BlockTransComSta_Get(__DMA__)   (READ_BIT((__DMA__)->BTSR, DMA_BTSR_BTS_CH1_Msk) >> DMA_BTSR_BTS_CH1_Pos)

/**
  * @brief  Channel 0 block transfer complete status get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 Channel 0 block transfer hasn't completed
  * @retval 1 Channel 0 block transfer has completed
  */
#define __LL_DMA_Ch0BlockTransComSta_Get(__DMA__)   (READ_BIT((__DMA__)->BTSR, DMA_BTSR_BTS_CH0_Msk) >> DMA_BTSR_BTS_CH0_Pos)


/**
  * @brief  Channel 1 source transfer complete status get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 Channel 1 source transfer hasn't completed
  * @retval 1 Channel 1 source transfer has completed
  */
#define __LL_DMA_Ch1SrcTransComSta_Get(__DMA__)     (READ_BIT((__DMA__)->STSR, DMA_STSR_STS_CH1_Msk) >> DMA_STSR_STS_CH1_Pos)

/**
  * @brief  Channel 0 source transfer complete status get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 Channel 0 source transfer hasn't completed
  * @retval 1 Channel 0 source transfer has completed
  */
#define __LL_DMA_Ch0SrcTransComSta_Get(__DMA__)     (READ_BIT((__DMA__)->STSR, DMA_STSR_STS_CH0_Msk) >> DMA_STSR_STS_CH0_Pos)


/**
  * @brief  Channel 1 destination transfer complete status get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 Channel 1 destination transfer hasn't completed
  * @retval 1 Channel 1 destination transfer has completed
  */
#define __LL_DMA_Ch1DstTransComSta_Get(__DMA__)     (READ_BIT((__DMA__)->DTSR, DMA_DTSR_DTS_CH1_Msk) >> DMA_DTSR_DTS_CH1_Pos)

/**
  * @brief  Channel 0 destination transfer complete status get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 Channel 0 destination transfer hasn't completed
  * @retval 1 Channel 0 destination transfer has completed
  */
#define __LL_DMA_Ch0DstTransComSta_Get(__DMA__)     (READ_BIT((__DMA__)->DTSR, DMA_DTSR_DTS_CH0_Msk) >> DMA_DTSR_DTS_CH0_Pos)


/**
  * @brief  Channel 1 transfer error status get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 Channel 1 transfer normal
  * @retval 1 Channel 1 transfer error
  */
#define __LL_DMA_Ch1TransErrSta_Get(__DMA__)        (READ_BIT((__DMA__)->TESR, DMA_TESR_TES_CH1_Msk) >> DMA_TESR_TES_CH1_Pos)

/**
  * @brief  Channel 0 transfer error status get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 Channel 0 transfer normal
  * @retval 1 Channel 0 transfer error
  */
#define __LL_DMA_Ch0TransErrSta_Get(__DMA__)        (READ_BIT((__DMA__)->TESR, DMA_TESR_TES_CH0_Msk) >> DMA_TESR_TES_CH0_Pos)


/**
  * @brief  Channel 1 transfer complete interrupt pending get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 no pending
  * @retval 1 pending
  */
#define __LL_DMA_Ch1TransComIntSta_Get(__DMA__)     (READ_BIT((__DMA__)->TIPR, DMA_TIPR_TIP_CH1_Msk) >> DMA_TIPR_TIP_CH1_Pos)

/**
  * @brief  Channel 0 transfer complete interrupt pending get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 no pending
  * @retval 1 pending
  */
#define __LL_DMA_Ch0TransComIntSta_Get(__DMA__)     (READ_BIT((__DMA__)->TIPR, DMA_TIPR_TIP_CH0_Msk) >> DMA_TIPR_TIP_CH0_Pos)


/**
  * @brief  Channel 1 block transfer complete interrupt pending get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 no pending
  * @retval 1 pending
  */
#define __LL_DMA_Ch1BlockTransComIntSta_Get(__DMA__)    (READ_BIT((__DMA__)->BTIPR, DMA_BTIPR_BTIF_CH1_Msk) >> DMA_BTIPR_BTIF_CH1_Pos)

/**
  * @brief  Channel 0 block transfer complete interrupt pending get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 no pending
  * @retval 1 pending
  */
#define __LL_DMA_Ch0BlockTransComIntSta_Get(__DMA__)    (READ_BIT((__DMA__)->BTIPR, DMA_BTIPR_BTIF_CH0_Msk) >> DMA_BTIPR_BTIF_CH0_Pos)


/**
  * @brief  Channel 1 source transfer complete interrupt pending get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 no pending
  * @retval 1 pending
  */
#define __LL_DMA_Ch1SrcTransComIntSta_Get(__DMA__)  (READ_BIT((__DMA__)->STIPR, DMA_STIPR_STIF_CH1_Msk) >> DMA_STIPR_STIF_CH1_Pos)

/**
  * @brief  Channel 0 source transfer complete interrupt pending get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 no pending
  * @retval 1 pending
  */
#define __LL_DMA_Ch0SrcTransComIntSta_Get(__DMA__)  (READ_BIT((__DMA__)->STIPR, DMA_STIPR_STIF_CH0_Msk) >> DMA_STIPR_STIF_CH0_Pos)


/**
  * @brief  Channel 1 destination transfer complete interrupt pending get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 no pending
  * @retval 1 pending
  */
#define __LL_DMA_Ch1DstTransComIntSta_Get(__DMA__)  (READ_BIT((__DMA__)->DTIPR, DMA_DTIPR_DTIF_CH1_Msk) >> DMA_DTIPR_DTIF_CH1_Pos)

/**
  * @brief  Channel 0 destination transfer complete interrupt pending get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 no pending
  * @retval 1 pending
  */
#define __LL_DMA_Ch0DstTransComIntSta_Get(__DMA__)  (READ_BIT((__DMA__)->DTIPR, DMA_DTIPR_DTIF_CH0_Msk) >> DMA_DTIPR_DTIF_CH0_Pos)


/**
  * @brief  Channel 1 transfer error interrupt pending get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 no pending
  * @retval 1 pending
  */
#define __LL_DMA_Ch1TransErrIntSta_Get(__DMA__)     (READ_BIT((__DMA__)->TEIPR, DMA_TEIPR_TEIF_CH1_Msk) >> DMA_TEIPR_TEIF_CH1_Pos)

/**
  * @brief  Channel 0 transfer error interrupt pending get
  * @param  __DMA__ Specifies DMA peripheral
  * @retval 0 no pending
  * @retval 1 pending
  */
#define __LL_DMA_Ch0TransErrIntSta_Get(__DMA__)     (READ_BIT((__DMA__)->TEIPR, DMA_TEIPR_TEIF_CH0_Msk) >> DMA_TEIPR_TEIF_CH0_Pos)


/**
  * @brief  Channel 1 transfer complete interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1TransCom_Int_En(__DMA__)                 SET_BIT((__DMA__)->TIMR, DMA_TIMR_TIWE_CH1_Msk | DMA_TIMR_TIE_CH1_Msk)

/**
  * @brief  Channel 1 transfer complete interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1TransCom_Int_Dis(__DMA__)                \
    MODIFY_REG((__DMA__)->TIMR, DMA_TIMR_TIWE_CH1_Msk | DMA_TIMR_TIE_CH1_Msk, DMA_TIMR_TIWE_CH1_Msk | (0x0 << DMA_TIMR_TIE_CH1_Pos))

/**
  * @brief  Channel 0 transfer complete interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0TransCom_Int_En(__DMA__)                 SET_BIT((__DMA__)->TIMR, DMA_TIMR_TIWE_CH0_Msk | DMA_TIMR_TIE_CH0_Msk)

/**
  * @brief  Channel 0 transfer complete interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0TransCom_Int_Dis(__DMA__)               \
    MODIFY_REG((__DMA__)->TIMR, DMA_TIMR_TIWE_CH0_Msk | DMA_TIMR_TIE_CH0_Msk, DMA_TIMR_TIWE_CH0_Msk | (0x0 << DMA_TIMR_TIE_CH0_Pos))

/**
  * @brief  Reg TIMR Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegTIMR_Write(__DMA__, val)                WRITE_REG((__DMA__)->TIMR, val)


/**
  * @brief  Channel 1 block transfer complete interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1BlockTransCom_Int_En(__DMA__)            SET_BIT((__DMA__)->BTIMR, DMA_BTIMR_BTIWE_CH1_Msk | DMA_BTIMR_BTIE_CH1_Msk)

/**
  * @brief  Channel 1 block transfer complete interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1BlockTransCom_Int_Dis(__DMA__)           \
    MODIFY_REG((__DMA__)->BTIMR, DMA_BTIMR_BTIWE_CH1_Msk | DMA_BTIMR_BTIE_CH1_Msk, DMA_BTIMR_BTIWE_CH1_Msk | (0x0 << DMA_BTIMR_BTIE_CH1_Pos))

/**
  * @brief  Channel 0 block transfer complete interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0BlockTransCom_Int_En(__DMA__)            SET_BIT((__DMA__)->BTIMR, DMA_BTIMR_BTIWE_CH0_Msk | DMA_BTIMR_BTIE_CH0_Msk)

/**
  * @brief  Channel 0 block transfer complete interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0BlockTransCom_Int_Dis(__DMA__)           \
    MODIFY_REG((__DMA__)->BTIMR, DMA_BTIMR_BTIWE_CH0_Msk | DMA_BTIMR_BTIE_CH0_Msk, DMA_BTIMR_BTIWE_CH0_Msk | (0x0 << DMA_BTIMR_BTIE_CH0_Pos))

/**
  * @brief  Reg BTIMR Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegBTIMR_Write(__DMA__, val)               WRITE_REG((__DMA__)->BTIMR, val)


/**
  * @brief  Channel 1 source transfer complete interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1SrcTransCom_Int_En(__DMA__)              SET_BIT((__DMA__)->STIMR, DMA_STIMR_STIWE_CH1_Msk | DMA_STIMR_STIE_CH1_Msk)

/**
  * @brief  Channel 1 source transfer complete interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1SrcTransCom_Int_Dis(__DMA__)             \
    MODIFY_REG((__DMA__)->STIMR, DMA_STIMR_STIWE_CH1_Msk | DMA_STIMR_STIE_CH1_Msk, DMA_STIMR_STIWE_CH1_Msk | (0x0 << DMA_STIMR_STIE_CH1_Pos))

/**
  * @brief  Channel 0 source transfer complete interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0SrcTransCom_Int_En(__DMA__)              SET_BIT((__DMA__)->STIMR, DMA_STIMR_STIWE_CH0_Msk | DMA_STIMR_STIE_CH0_Msk)

/**
  * @brief  Channel 0 source transfer complete interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0SrcTransCom_Int_Dis(__DMA__)             \
    MODIFY_REG((__DMA__)->STIMR, DMA_STIMR_STIWE_CH0_Msk | DMA_STIMR_STIE_CH0_Msk, DMA_STIMR_STIWE_CH0_Msk | (0x0 << DMA_STIMR_STIE_CH0_Pos))

/**
  * @brief  Reg STIMR Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegSTIMR_Write(__DMA__, val)               WRITE_REG((__DMA__)->STIMR, val)


/**
  * @brief  Channel 1 destination transfer complete interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1DstTransCom_Int_En(__DMA__)              SET_BIT((__DMA__)->DTIMR, DMA_DTIMR_DTIWE_CH1_Msk | DMA_DTIMR_DTIE_CH1_Msk)

/**
  * @brief  Channel 1 destination transfer complete interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1DstTransCom_Int_Dis(__DMA__)             \
    MODIFY_REG((__DMA__)->DTIMR, DMA_DTIMR_DTIWE_CH1_Msk | DMA_DTIMR_DTIE_CH1_Msk, DMA_DTIMR_DTIWE_CH1_Msk | (0x0 << DMA_DTIMR_DTIE_CH1_Pos))

/**
  * @brief  Channel 0 destination transfer complete interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0DstTransCom_Int_En(__DMA__)              SET_BIT((__DMA__)->DTIMR, DMA_DTIMR_DTIWE_CH0_Msk | DMA_DTIMR_DTIE_CH0_Msk)

/**
  * @brief  Channel 0 destination transfer complete interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0DstTransCom_Int_Dis(__DMA__)             \
    MODIFY_REG((__DMA__)->DTIMR, DMA_DTIMR_DTIWE_CH0_Msk | DMA_DTIMR_DTIE_CH0_Msk, DMA_DTIMR_DTIWE_CH0_Msk | (0x0 << DMA_DTIMR_DTIE_CH0_Pos))

/**
  * @brief  Reg DTIMR Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegDTIMR_Write(__DMA__, val)               WRITE_REG((__DMA__)->DTIMR, val)


/**
  * @brief  Channel 1 transfer error interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1TransErr_Int_En(__DMA__)                 SET_BIT((__DMA__)->TEIMR, DMA_TEIMR_TEIWE_CH1_Msk | DMA_TEIMR_TEIE_CH1_Msk)

/**
  * @brief  Channel 1 transfer error interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1TransErr_Int_Dis(__DMA__)                \
    MODIFY_REG((__DMA__)->TEIMR, DMA_TEIMR_TEIWE_CH1_Msk | DMA_TEIMR_TEIE_CH1_Msk, DMA_TEIMR_TEIWE_CH1_Msk | (0x0 << DMA_TEIMR_TEIE_CH1_Pos))

/**
  * @brief  Channel 0 transfer error interrupt enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0TransErr_Int_En(__DMA__)                 SET_BIT((__DMA__)->TEIMR, DMA_TEIMR_TEIWE_CH0_Msk | DMA_TEIMR_TEIE_CH0_Msk)

/**
  * @brief  Channel 0 transfer error interrupt disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0TransErr_Int_Dis(__DMA__)                \
    MODIFY_REG((__DMA__)->TEIMR, DMA_TEIMR_TEIWE_CH0_Msk | DMA_TEIMR_TEIE_CH0_Msk, DMA_TEIMR_TEIWE_CH0_Msk | (0x0 << DMA_TEIMR_TEIE_CH0_Pos))

/**
  * @brief  Reg TEIMR Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegTEIMR_Write(__DMA__, val)               WRITE_REG((__DMA__)->TEIMR, val)


/**
  * @brief  Channel 1 transfer complete status clear
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1TransComSta_Clr(__DMA__)                WRITE_REG((__DMA__)->TCR, DMA_TCR_TC_CH1_Msk)

/**
  * @brief  Channel 0 transfer complete status clear
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0TransComSta_Clr(__DMA__)                WRITE_REG((__DMA__)->TCR, DMA_TCR_TC_CH0_Msk)

/**
  * @brief  Reg TCR Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegTCR_Write(__DMA__, val)                 WRITE_REG((__DMA__)->TCR, val)


/**
  * @brief  Channel 1 block transfer complete status clear
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1BlockTransComSta_Clr(__DMA__)           WRITE_REG((__DMA__)->BTCR, DMA_BTCR_BTC_CH1_Msk)

/**
  * @brief  Channel 0 block transfer complete status clear
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0BlockTransComSta_Clr(__DMA__)           WRITE_REG((__DMA__)->BTCR, DMA_BTCR_BTC_CH0_Msk)

/**
  * @brief  Reg BTCR Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegBTCR_Write(__DMA__, val)                WRITE_REG((__DMA__)->BTCR, val)


/**
  * @brief  Channel 1 source transfer complete status clear
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1SrcTransComSta_Clr(__DMA__)             WRITE_REG((__DMA__)->STCR, DMA_STCR_STC_CH1_Msk)

/**
  * @brief  Channel 0 source transfer complete status clear
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0SrcTransComSta_Clr(__DMA__)             WRITE_REG((__DMA__)->STCR, DMA_STCR_STC_CH0_Msk)

/**
  * @brief  Reg STCR Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegSTCR_Write(__DMA__, val)                WRITE_REG((__DMA__)->STCR, val)


/**
  * @brief  Channel 1 destination transfer complete status clear
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1DstTransComSta_Clr(__DMA__)             WRITE_REG((__DMA__)->DTCR, DMA_DTCR_DTC_CH1_Msk)

/**
  * @brief  Channel 0 destination transfer complete status clear
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0DstTransComSta_Clr(__DMA__)             WRITE_REG((__DMA__)->DTCR, DMA_DTCR_DTC_CH0_Msk)

/**
  * @brief  Reg DTCR Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegDTCR_Write(__DMA__, val)                WRITE_REG((__DMA__)->DTCR, val)


/**
  * @brief  Channel 1 transfer error status clear
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1TransErrSta_Clr(__DMA__)                WRITE_REG((__DMA__)->TECR, DMA_TECR_TEC_CH1_Msk)

/**
  * @brief  Channel 0 transfer error status clear
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0TransErrSta_Clr(__DMA__)                WRITE_REG((__DMA__)->TECR, DMA_TECR_TEC_CH0_Msk)

/**
  * @brief  Reg TECR Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegTECR_Write(__DMA__, val)                WRITE_REG((__DMA__)->TECR, val)


/**
  * @brief  Peripheral enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Periph_En(__DMA__)                         SET_BIT((__DMA__)->CR0, DMA_CR0_PEN_Msk)

/**
  * @brief  Peripheral disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Periph_Dis(__DMA__)                        CLEAR_BIT((__DMA__)->CR0, DMA_CR0_PEN_Msk)

/**
  * @brief  Reg CR0 Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegCR0_Write(__DMA__, val)                 WRITE_REG((__DMA__)->CR0, val)


/**
  * @brief  Channel 1 enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1_En(__DMA__)                            SET_BIT((__DMA__)->CR1, DMA_CR1_CHWE_CH1_Msk | DMA_CR1_CHEN_CH1_Msk)

/**
  * @brief  Channel 1 disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch1_Dis(__DMA__)                           \
    MODIFY_REG((__DMA__)->CR1, DMA_CR1_CHWE_CH1_Msk | DMA_CR1_CHEN_CH1_Msk, DMA_CR1_CHWE_CH1_Msk | (0x0 << DMA_CR1_CHEN_CH1_Pos))

/**
  * @brief  Channel 0 enable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0_En(__DMA__)                            SET_BIT((__DMA__)->CR1, DMA_CR1_CHWE_CH0_Msk | DMA_CR1_CHEN_CH0_Msk)

/**
  * @brief  Channel 0 disable
  * @param  __DMA__ Specifies DMA peripheral
  * @return None
  */
#define __LL_DMA_Ch0_Dis(__DMA__)   \
        MODIFY_REG((__DMA__)->CR1, DMA_CR1_CHWE_CH0_Msk | DMA_CR1_CHEN_CH0_Msk, DMA_CR1_CHWE_CH0_Msk | (0x0 << DMA_CR1_CHEN_CH0_Pos))

/**
  * @brief  Reg CR1 Write
  * @param  __DMA__ Specifies DMA peripheral
  * @param  val write value
  * @return None
  */
#define __LL_DMA_RegCR1_Write(__DMA__, val)                 WRITE_REG((__DMA__)->CR1, val)

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup DMA_LL_Exported_Functions
  * @{
  */

/** @addtogroup DMA_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_DMA_Init(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch, DMA_UserCfgTypeDef *user_cfg);
LL_StatusETypeDef LL_DMA_DeInit(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch);
/**
  * @}
  */


/** @addtogroup DMA_LL_Exported_Functions_Group2
  * @{
  */
DMA_ChannelETypeDef LL_DMA_ChannelRequest(void);
DMA_ChannelETypeDef LL_DMA_ChReqSpecific(DMA_ChannelETypeDef ch);
void LL_DMA_ChannelRelease(DMA_ChannelETypeDef ch);
/**
  * @}
  */


/** @addtogroup DMA_LL_Exported_Functions_Group3
  * @{
  */
LL_StatusETypeDef LL_DMA_Start_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch,
                                   uint32_t src_addr, uint32_t dst_addr, uint32_t data_len);
LL_StatusETypeDef LL_DMA_Start_IT(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch,
                                  uint32_t src_addr, uint32_t dst_addr, uint32_t data_len);
LL_StatusETypeDef LL_DMA_Stop_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch);
LL_StatusETypeDef LL_DMA_Stop_IT(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch);
LL_StatusETypeDef LL_DMA_WaitComplete_CPU(DMA_TypeDef *Instance, DMA_ChannelETypeDef ch, uint32_t timeout);
/**
  * @}
  */


/** @addtogroup DMA_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_DMA_IRQHandler(DMA_TypeDef *Instance);
/**
  * @}
  */


/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _TAE32F53XX_LL_DMA_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

