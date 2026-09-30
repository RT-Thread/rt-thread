/**
  ******************************************************************************
  * @file    tae32g58xx_ll_usb.h
  * @author  MCD Application Team
  * @brief   Header file for USB LL module
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
#ifndef _TAE32G58XX_LL_USB_H_
#define _TAE32G58XX_LL_USB_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup USB_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/** @defgroup USB_LL_Exported_Constants USB LL Exported Constants
  * @brief    USB LL Exported Constants
  * @{
  */

#define USB_IUINTREN_INSTA_Pos          (26UL)                  /*!< INSTA (Bit 26)                                         */
#define USB_IUINTREN_INSTA_Msk          (0x4000000UL)           /*!< INSTA (Bitfield-Mask: 0x1)                             */
#define USB_IUINTREN_OUTSTA_Pos         (25UL)                  /*!< OUTSTA (Bit 25)                                        */
#define USB_IUINTREN_OUTSTA_Msk         (0x2000000UL)           /*!< OUTSTA (Bitfield-Mask: 0x1)                            */
#define USB_IUINTREN_SETUPSTA_Pos       (24UL)                  /*!< SETUPSTA (Bit 24)                                      */
#define USB_IUINTREN_SETUPSTA_Msk       (0x1000000UL)           /*!< SETUPSTA (Bitfield-Mask: 0x1)                          */

/**
  * @}
  */


/* Exported Macros -----------------------------------------------------------*/
/** @defgroup USB_LL_Exported_Macros USB LL Exported Macros
  * @brief    USB LL Exported Macros
  * @{
  */

/**
  * @brief  USB FIFO 8bits Register offset
  * @note   Register must be 8bits
  * @param  __REG__  Register basis from which the offset is applied
  * @param  offset   Numbers of register to Offset
  * @return uint8_t Register value after offset
  */
#define __LL_USB_FIFO_REG_OFFSET(__REG__, offset)            \
    (*((__IO uint8_t *)((uint32_t) ((uint32_t)(&(__REG__)) + (offset)))))



/**
  * @brief  Soft Connect Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_SoftConn_En(__USB__)               SET_BIT((__USB__)->CTRL, USB_CTRL_SCONN_Msk)

/**
  * @brief  Soft Connect Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_SoftConn_Dis(__USB__)              CLEAR_BIT((__USB__)->CTRL, USB_CTRL_SCONN_Msk)

/**
  * @brief  Function Address Set
  * @param  __USB__ Specifies USB peripheral
  * @param  addr Function Address
  * @return None
  */
#define __LL_USB_FuncAddr_Set(__USB__, addr)        \
        MODIFY_REG((__USB__)->CTRL, USB_CTRL_FADDR_Msk, (((addr) & 0x7fUL) << USB_CTRL_FADDR_Pos))


/**
  * @brief  Endpoint Index Set
  * @param  __USB__ Specifies USB peripheral
  * @param  idx Endpoint Index
  * @return None
  */
#define __LL_USB_EPIndex_Set(__USB__, idx)          \
        MODIFY_REG((__USB__)->INDEX, USB_INDEX_INDEX_Msk, (((idx) & 0xfUL) << USB_INDEX_INDEX_Pos))

/**
  * @brief  Endpoint Index Get
  * @param  __USB__ Specifies USB peripheral
  * @return Endpoint Index
  */
#define __LL_USB_EPIndex_Get(__USB__)               READ_BIT_SHIFT((__USB__)->INDEX, USB_INDEX_INDEX_Msk, USB_INDEX_INDEX_Pos)

/**
  * @brief  Frame Number Get
  * @param  __USB__ Specifies USB peripheral
  * @return Frame Number
  */
#define __LL_USB_FrameNum_Get(__USB__)              READ_BIT_SHIFT((__USB__)->INDEX, USB_INDEX_FNUM_Msk, USB_INDEX_FNUM_Pos)


/**
  * @brief  TX Packet Ready AutoSet Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXPktRdyAutoSet_En(__USB__)    SET_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_AUTOSET_Msk)

/**
  * @brief  TX Packet Ready AutoSet Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXPktRdyAutoSet_Dis(__USB__)   CLEAR_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_AUTOSET_Msk)

/**
  * @brief  Endpoint TX ISO Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXISO_En(__USB__)              SET_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_ISO_Msk)

/**
  * @brief  Endpoint TX ISO Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXISO_Dis(__USB__)             CLEAR_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_ISO_Msk)

/**
  * @brief  Endpoint Direction TX Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TX_En(__USB__)                 SET_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_MODE_Msk)

/**
  * @brief  Endpoint Direction RX Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RX_En(__USB__)                 CLEAR_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_MODE_Msk)

/**
  * @brief  Endpoint TX to Force Data Toggle Set
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXForceDataTog_Set(__USB__)    SET_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_FRCDATTOG_Msk)

/**
  * @brief  Endpoint TX to Force Data Toggle Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXForceDataTog_Clr(__USB__)    CLEAR_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_FRCDATTOG_Msk)

/**
  * @brief  Endpoint 0 Flush FIFO
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_FlushFIFO(__USB__)             SET_BIT((__USB__)->TX0CTRL, USB_TX0CTRL_FLFIFO_Msk)

/**
  * @brief  Endpoint 0 SetupEnd Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_SetupEnd_Clr(__USB__)          SET_BIT((__USB__)->TX0CTRL, USB_TX0CTRL_SSECLR_Msk)

/**
  * @brief  Endpoint 0 RX Packet Ready Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_RXPktRdy_Clr(__USB__)          SET_BIT((__USB__)->TX0CTRL, USB_TX0CTRL_SRPCLR_Msk)

/**
  * @brief  TX Endpoint Data Toggle Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXDataTog_Clr(__USB__)         SET_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_CLRDT_Msk)

/**
  * @brief  Endpoint 0 Send Stall Set
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_SendStall_Set(__USB__)         SET_BIT((__USB__)->TX0CTRL, USB_TX0CTRL_SENDSTA_Msk)

/**
  * @brief  Judge TX Endpoint has Sent Stall or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Hasn't Sent Stall
  * @retval 1 Has Sent Stall
  */
#define __LL_USB_EPx_IsTXSentStall(__USB__)         READ_BIT_SHIFT((__USB__)->TXnCTRL, USB_TXnCTRL_SENTSTA_Msk, USB_TXnCTRL_SENTSTA_Pos)

/**
  * @brief  TX Endpoint Sent Stall Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXSentStall_Clr(__USB__)       CLEAR_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_SENTSTA_Msk)

/**
  * @brief  Judge Endpoint 0 is SetupEnd or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 isn't Setup End
  * @retval 1 is Setup End
  */
#define __LL_USB_EP0_IsSetupEnd(__USB__)            READ_BIT_SHIFT((__USB__)->TX0CTRL, USB_TX0CTRL_SETUPEND_Msk, USB_TX0CTRL_SETUPEND_Pos)

/**
  * @brief  TX Endpoint Send Stall Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXSendStall_En(__USB__)        SET_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_SENDSTA_Msk)

/**
  * @brief  TX Endpoint Send Stall Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXSendStall_Dis(__USB__)       CLEAR_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_SENDSTA_Msk)

/**
  * @brief  Endpoint 0 Data End Set
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_DataEnd_Set(__USB__)           SET_BIT((__USB__)->TX0CTRL, USB_TX0CTRL_DATAEND_Msk)

/**
  * @brief  TX Endpoint Flush FIFO
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXFlushFIFO(__USB__)           SET_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_FLFIFO_Msk)

/**
  * @brief  Judge Endpoint 0 has Sent Stall or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Hasn't Sent Stall
  * @retval 1 Has Sent Stall
  */
#define __LL_USB_EP0_IsSentStall(__USB__)           READ_BIT_SHIFT((__USB__)->TX0CTRL, USB_TX0CTRL_SENTSTA_Msk, USB_TX0CTRL_SENTSTA_Pos)

/**
  * @brief  Endpoint 0 Sent Stall Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_SentStall_Clr(__USB__)         CLEAR_BIT((__USB__)->TX0CTRL, USB_TX0CTRL_SENTSTA_Msk)

/**
  * @brief  Judge TX Endpoint FIFO Is UnderRun or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't UnderRun
  * @retval 1 Is UnderRun
  */
#define __LL_USB_EPx_IsTXFIFOUnderRun(__USB__)      READ_BIT_SHIFT((__USB__)->TXnCTRL, USB_TXnCTRL_UNRUN_Msk, USB_TXnCTRL_UNRUN_Pos)

/**
  * @brief  TX Endpoint UnderRun Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXFIFOUnderRun_Clr(__USB__)    CLEAR_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_UNRUN_Msk)

/**
  * @brief  Endpoint 0 TX Packet Ready Set
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_TXPktRdy_Set(__USB__)          SET_BIT((__USB__)->TX0CTRL, USB_TX0CTRL_TXPR_Msk)

/**
  * @brief  Judge is Endpoint 0 TX Packet Ready or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 isn't Endpoint 0 TX Packet Ready
  * @retval 1 is Endpoint 0 TX Packet Ready
  */
#define __LL_USB_EP0_IsTXPktRdy(__USB__)            READ_BIT_SHIFT((__USB__)->TX0CTRL, USB_TX0CTRL_TXPR_Msk, USB_TX0CTRL_TXPR_Pos)

/**
  * @brief  Judge Is TX Endpoint FIFO NoEmpty or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Is Empty
  * @retval 1 Is NoEmpty
  */
#define __LL_USB_EPx_IsTXFIFONoEmpty(__USB__)       READ_BIT_SHIFT((__USB__)->TXnCTRL, USB_TXnCTRL_FIFONE_Msk, USB_TXnCTRL_FIFONE_Pos)

/**
  * @brief  Judge is Endpoint 0 RX Packet Ready or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 RX Packet isn't Ready
  * @retval 1 RX Packet is Ready
  */
#define __LL_USB_EP0_IsRXPktRdy(__USB__)            READ_BIT_SHIFT((__USB__)->TX0CTRL, USB_TX0CTRL_RXPR_Msk, USB_TX0CTRL_RXPR_Pos)

/**
  * @brief  TX Endpoint Packet Ready Set
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXPktRdy_Set(__USB__)          SET_BIT((__USB__)->TXnCTRL, USB_TXnCTRL_TXPR_Msk)

/**
  * @brief  Judge is Endpoint TX Packet Ready or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Packet Ready
  * @retval 1 Is Packet Ready
  */
#define __LL_USB_EPx_IsTXPktRdy(__USB__)            READ_BIT_SHIFT((__USB__)->TXnCTRL, USB_TXnCTRL_TXPR_Msk, USB_TXnCTRL_TXPR_Pos)

/**
  * @brief  TX Max Payload Set
  * @param  __USB__ Specifies USB peripheral
  * @param  max TX Max Payload
  * @return None
  */
#define __LL_USB_EPx_TXMaxPayload_Set(__USB__, max) \
        MODIFY_REG((__USB__)->TXnCTRL, USB_TXnCTRL_TXMAXP_Msk, (((max) & 0xffffUL) << USB_TXnCTRL_TXMAXP_Pos))

/**
  * @brief  TX Max Payload Get
  * @param  __USB__ Specifies USB peripheral
  * @return TX Max Payload
  */
#define __LL_USB_EPx_TXMaxPayload_Get(__USB__)      READ_BIT_SHIFT((__USB__)->TXnCTRL, USB_TXnCTRL_TXMAXP_Msk, USB_TXnCTRL_TXMAXP_Pos)


/**
  * @brief  RX Packet Ready Auto Clear Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXPktRdyAutoClr_En(__USB__)    SET_BIT((__USB__)->RXCTRL, USB_RXCTRL_AUTOCLR_Msk)

/**
  * @brief  RX Packet Ready Auto Clear Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXPktRdyAutoClr_Dis(__USB__)   CLEAR_BIT((__USB__)->RXCTRL, USB_RXCTRL_AUTOCLR_Msk)

/**
  * @brief  Endpoint RX ISO Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXISO_En(__USB__)              SET_BIT((__USB__)->RXCTRL, USB_RXCTRL_ISO_Msk)

/**
  * @brief  Endpoint RX ISO Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXISO_Dis(__USB__)             CLEAR_BIT((__USB__)->RXCTRL, USB_RXCTRL_ISO_Msk)

/**
  * @brief  Judge Is RX ISO Endpoint Incomplete or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Complete
  * @retval 1 Incomplete
  */
#define __LL_USB_EPx_IsRXISOInComp(__USB__)         READ_BIT_SHIFT((__USB__)->RXCTRL, USB_RXCTRL_INCRX_Msk, USB_RXCTRL_INCRX_Pos)

/**
  * @brief  RX Endpoint Data Toggle Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXDataTog_Clr(__USB__)         SET_BIT((__USB__)->RXCTRL, USB_RXCTRL_CDATTOG_Msk)

/**
  * @brief  Judge RX Endpoint has Sent Stall or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Hasn't Sent Stall
  * @retval 1 Has Sent Stall
  */
#define __LL_USB_EPx_IsRXSentStall(__USB__)         READ_BIT_SHIFT((__USB__)->RXCTRL, USB_RXCTRL_SENTSTA_Msk, USB_RXCTRL_SENTSTA_Pos)

/**
  * @brief  RX Endpoint Sent Stall Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXSentStall_Clr(__USB__)       CLEAR_BIT((__USB__)->RXCTRL, USB_RXCTRL_SENTSTA_Msk)

/**
  * @brief  RX Endpoint Send Stall Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXSendStall_En(__USB__)        SET_BIT((__USB__)->RXCTRL, USB_RXCTRL_SENDSTA_Msk)

/**
  * @brief  RX Endpoint Send Stall Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXSendStall_Dis(__USB__)       CLEAR_BIT((__USB__)->RXCTRL, USB_RXCTRL_SENDSTA_Msk)

/**
  * @brief  RX Endpoint Flush FIFO
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXFlushFIFO(__USB__)           SET_BIT((__USB__)->RXCTRL, USB_RXCTRL_FLFIFO_Msk)

/**
  * @brief  Judge is RX ISO Endpoint Data Error or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Data Error
  * @retval 1 Is Data Error
  */
#define __LL_USB_EPx_IsISORXDataErr(__USB__)        READ_BIT_SHIFT((__USB__)->RXCTRL, USB_RXCTRL_DATAERR_Msk, USB_RXCTRL_DATAERR_Pos)

/**
  * @brief  Judge Is RX ISO Endpoint FIFO OverRun or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't OverRun
  * @retval 1 Is OverRun
  */
#define __LL_USB_EPx_IsISORXFIFOOverRun(__USB__)    READ_BIT_SHIFT((__USB__)->RXCTRL, USB_RXCTRL_OVERRUN_Msk, USB_RXCTRL_OVERRUN_Pos)

/**
  * @brief  RX ISO Endpoint OverrRun Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_ISORXFIFOOverRun_Clr(__USB__)  CLEAR_BIT((__USB__)->RXCTRL, USB_RXCTRL_OVERRUN_Msk)

/**
  * @brief  Judge is RX FIFO Full or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Full
  * @retval 1 Is Full
  */
#define __LL_USB_EPx_IsRXFIFOFull(__USB__)          READ_BIT_SHIFT((__USB__)->RXCTRL, USB_RXCTRL_FIFOFULL_Msk, USB_RXCTRL_FIFOFULL_Pos)

/**
  * @brief  Judge is Endpoint RX Packet Ready or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Packet Ready
  * @retval 1 Is Packet Ready
  */
#define __LL_USB_EPx_IsRXPktRdy(__USB__)            READ_BIT_SHIFT((__USB__)->RXCTRL, USB_RXCTRL_RXPR_Msk, USB_RXCTRL_RXPR_Pos)

/**
  * @brief  RX Endpoint Packet Ready Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXPktRdy_Clr(__USB__)          CLEAR_BIT((__USB__)->RXCTRL, USB_RXCTRL_RXPR_Msk)

/**
  * @brief  RX Max Payload Set
  * @param  __USB__ Specifies USB peripheral
  * @param  max RX Max Payload
  * @return None
  */
#define __LL_USB_EPx_RXMaxPayload_Set(__USB__, max) \
        MODIFY_REG((__USB__)->RXCTRL, USB_RXCTRL_RXMAXP_Msk, (((max) & 0xffffUL) << USB_RXCTRL_RXMAXP_Pos))

/**
  * @brief  RX Max Payload Get
  * @param  __USB__ Specifies USB peripheral
  * @return RX Max Payload
  */
#define __LL_USB_EPx_RXMaxPayload_Get(__USB__)      READ_BIT_SHIFT((__USB__)->RXCTRL, USB_RXCTRL_RXMAXP_Msk, USB_RXCTRL_RXMAXP_Pos)


/**
  * @brief  Endpoint RX Counter Get
  * @param  __USB__ Specifies USB peripheral
  * @return RX Counter
  */
#define __LL_USB_RXCount_Get(__USB__)               READ_BIT_SHIFT((__USB__)->RXCOUNT, USB_RXCOUNT_RXCOUNT_Msk, USB_RXCOUNT_RXCOUNT_Pos)


/**
  * @brief  Endpoint RX FIFO Size Get
  * @param  __USB__ Specifies USB peripheral
  * @return RX FIFO Size
  */
#define __LL_USB_RXFIFOSize_Get(__USB__)            \
        (1 << (READ_BIT_SHIFT((__USB__)->FIFOSIZE, USB_FIFOSIZE_RXFIFOSIZE_Msk, USB_FIFOSIZE_RXFIFOSIZE_Pos)))

/**
  * @brief  Endpoint TX FIFO Size Get
  * @param  __USB__ Specifies USB peripheral
  * @return TX FIFO Size
  */
#define __LL_USB_TXFIFOSize_Get(__USB__)            \
        (1 << (READ_BIT_SHIFT((__USB__)->FIFOSIZE, USB_FIFOSIZE_TXFIFOSIZE_Msk, USB_FIFOSIZE_TXFIFOSIZE_Pos)))


/**
  * @brief  Rx Endpoint Double Packet Buffer Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_RxEpDoublePktBuf_En(__USB__)       SET_BIT((__USB__)->FIFOSZ, USB_FIFOSZ_RXDPB_Msk)

/**
  * @brief  Rx Endpoint Double Packet Buffer Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_RxEpDoublePktBuf_Dis(__USB__)      CLEAR_BIT((__USB__)->FIFOSZ, USB_FIFOSZ_RXDPB_Msk)

/**
  * @brief  Rx Endpoint Maximum Packet Size Set
  * @param  __USB__ Specifies USB peripheral
  * @param  max Rx Endpoint Maximum Packet Size
  * @return None
  */
#define __LL_USB_RxEpMaxPktSize_Set(__USB__, max)   \
        MODIFY_REG((__USB__)->FIFOSZ, USB_FIFOSZ_RXSZ_Msk, (((max) & 0xfUL) << USB_FIFOSZ_RXSZ_Pos))

/**
  * @brief  Tx Endpoint Double Packet Buffer Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_TxEpDoublePktBuf_En(__USB__)       SET_BIT((__USB__)->FIFOSZ, USB_FIFOSZ_TXDPB_Msk)

/**
  * @brief  Tx Endpoint Double Packet Buffer Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_TxEpDoublePktBuf_Dis(__USB__)      CLEAR_BIT((__USB__)->FIFOSZ, USB_FIFOSZ_TXDPB_Msk)

/**
  * @brief  Tx Endpoint Maximum Packet Size Set
  * @param  __USB__ Specifies USB peripheral
  * @param  max Tx Endpoint Maximum Packet Size
  * @return None
  */
#define __LL_USB_TxEpMaxPktSize_Set(__USB__, max)   \
        MODIFY_REG((__USB__)->FIFOSZ, USB_FIFOSZ_TXSZ_Msk, (((max) & 0xfUL) << USB_FIFOSZ_TXSZ_Pos))


/**
  * @brief  Rx Endpoint FIFO Start Address Set
  * @param  __USB__ Specifies USB peripheral
  * @param  addr Rx Endpoint FIFO Start Address
  * @return None
  */
#define __LL_USB_RxEpFIFOStartAddr_Set(__USB__, addr)   \
        MODIFY_REG((__USB__)->FIFOAD, USB_FIFOAD_RXAD_Msk, (((addr) & 0x1fffUL) << USB_FIFOAD_RXAD_Pos))

/**
  * @brief  Tx Endpoint FIFO Start Address Set
  * @param  __USB__ Specifies USB peripheral
  * @param  addr Tx Endpoint FIFO Start Address
  * @return None
  */
#define __LL_USB_TxEpFIFOStartAddr_Set(__USB__, addr)   \
        MODIFY_REG((__USB__)->FIFOAD, USB_FIFOAD_TXAD_Msk, (((addr) & 0x1fffUL) << USB_FIFOAD_TXAD_Pos))


/**
  * @brief  Config DM Output Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMOutputHardware(__USB__)          CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_DMOE_EN_Msk)

/**
  * @brief  Config DM Output Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMOutputNormal(__USB__)            SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_DMOE_EN_Msk | USB_PINCTRL_DMOE_Msk)

/**
  * @brief  Disable DM Output
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMOutputDisable(__USB__)           \
        MODIFY_REG((__USB__)->PINCTRL, 0x3UL << USB_PINCTRL_DMOE_EN_Pos, 0x1UL << USB_PINCTRL_DMOE_EN_Pos)

/**
  * @brief  Config DP Output Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPOutputHardware(__USB__)          CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_DPOE_EN_Msk)

/**
  * @brief  Config DP Output Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPOutputNormal(__USB__)            SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_DPOE_EN_Msk | USB_PINCTRL_DPOE_Msk)

/**
  * @brief  Disable DP Output
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPOutputDisable(__USB__)           \
        MODIFY_REG((__USB__)->PINCTRL, 0x3UL << USB_PINCTRL_DPOE_EN_Pos, 0x1UL << USB_PINCTRL_DPOE_EN_Pos)

/**
  * @brief  Config DM Input Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMInputHardware(__USB__)           CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_DMIE_EN_Msk)

/**
  * @brief  Config DM Input Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMInputNormal(__USB__)             SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_DMIE_EN_Msk | USB_PINCTRL_DMIE_Msk)

/**
  * @brief  Disable DM Input
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMInputDisable(__USB__)            \
        MODIFY_REG((__USB__)->PINCTRL, 0x3UL << USB_PINCTRL_DMIE_EN_Pos, 0x1UL << USB_PINCTRL_DMIE_EN_Pos)

/**
  * @brief  Config DP Input Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPInputHardware(__USB__)           CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_DPIE_EN_Msk)

/**
  * @brief  Config DP Input Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPInputNormal(__USB__)             SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_DPIE_EN_Msk | USB_PINCTRL_DPIE_Msk)

/**
  * @brief  Disable DP Input
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPInputDisable(__USB__)            \
        MODIFY_REG((__USB__)->PINCTRL, 0x3UL << USB_PINCTRL_DPIE_EN_Pos, 0x1UL << USB_PINCTRL_DPIE_EN_Pos)

/**
  * @brief  Config DM PullDown Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullDownHardware(__USB__)        CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_DMPD_EN_Msk)

/**
  * @brief  Config DM PullDown Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullDownNormal(__USB__)          SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_DMPD_EN_Msk | USB_PINCTRL_DMPD_Msk)

/**
  * @brief  Disable DM PullDown
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullDownDisable(__USB__)         \
        MODIFY_REG((__USB__)->PINCTRL, 0x3UL << USB_PINCTRL_DMPD_EN_Pos, 0x1UL << USB_PINCTRL_DMPD_EN_Pos)

/**
  * @brief  Config DM PullUp Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullUpHardware(__USB__)          CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_DMPU_EN_Msk)

/**
  * @brief  Config DM PullUp Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullUpNormal(__USB__)            SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_DMPU_EN_Msk | USB_PINCTRL_DMPU_Msk)

/**
  * @brief  Disable DM PullUp
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullUpDisable(__USB__)           \
        MODIFY_REG((__USB__)->PINCTRL, 0x3UL << USB_PINCTRL_DMPU_EN_Pos, 0x1UL << USB_PINCTRL_DMPU_EN_Pos)

/**
  * @brief  Config DP PullDown Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullDownHardware(__USB__)        CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_DPPD_EN_Msk)

/**
  * @brief  Config DP PullDown Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullDownNormal(__USB__)          SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_DPPD_EN_Msk | USB_PINCTRL_DPPD_Msk)

/**
  * @brief  Disable DP PullDown
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullDownDisable(__USB__)         \
        MODIFY_REG((__USB__)->PINCTRL, 0x3UL << USB_PINCTRL_DPPD_EN_Pos, 0x1UL << USB_PINCTRL_DPPD_EN_Pos)

/**
  * @brief  Config DP PullUp Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullUpHardware(__USB__)          CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_DPPU_EN_Msk)

/**
  * @brief  Config DP PullUp Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullUpNormal(__USB__)            SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_DPPU_EN_Msk | USB_PINCTRL_DPPU_Msk)

/**
  * @brief  Disable DP PullUp
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullUpDisable(__USB__)           \
        MODIFY_REG((__USB__)->PINCTRL, 0x3UL << USB_PINCTRL_DPPU_EN_Pos, 0x1UL << USB_PINCTRL_DPPU_EN_Pos)

/**
  * @brief  Set Vbus Above VBusValid Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusValidThreshold_Set(__USB__)    SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_VBUSVALID_Msk)

/**
  * @brief  Clear Vbus Above VBusValid Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusValidThreshold_Clr(__USB__)    CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_VBUSVALID_Msk)

/**
  * @brief  Set Vbus Above Vbus A-device Session Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusAboveAdevSessThres_Set(__USB__)    SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_AVALID_Msk)

/**
  * @brief  Clear Vbus Above Vbus A-device Session Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusAboveAdevSessThres_Clr(__USB__)    CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_AVALID_Msk)

/**
  * @brief  Set Vbus Above Session End Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusAboveSessEndThres_Set(__USB__) SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_VBUSLO_Msk)

/**
  * @brief  Clear Vbus Above Session End Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusAboveSessEndThres_Clr(__USB__) CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_VBUSLO_Msk)

/**
  * @brief  Set Mini-AB Connector ID Pin
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_MiniABConnectorID_Set(__USB__)     SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_CID_Msk)

/**
  * @brief  Clear Mini-AB Connector ID Pin
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_MiniABConnectorID_Clr(__USB__)     CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_CID_Msk)

/**
  * @brief  Enable USB PHY
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_PHY_En(__USB__)                    SET_BIT((__USB__)->PINCTRL, USB_PINCTRL_PHY_EN_Msk)

/**
  * @brief  Disable USB PHY
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_PHY_Dis(__USB__)                   CLEAR_BIT((__USB__)->PINCTRL, USB_PINCTRL_PHY_EN_Msk)


/**
  * @brief  Judge Is IN Packet or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't IN Packet
  * @retval 1 Is IN Packet
  */
#define __LL_USB_IsInPacket(__USB__)                \
        READ_BIT_SHIFT((__USB__)->IUINTREN, USB_IUINTREN_INSTA_Msk, USB_IUINTREN_INSTA_Pos)

/**
  * @brief  Judge Is OUT Packet or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't OUT Packet
  * @retval 1 Is OUT Packet
  */
#define __LL_USB_IsOutPacket(__USB__)               \
        READ_BIT_SHIFT((__USB__)->IUINTREN, USB_IUINTREN_OUTSTA_Msk, USB_IUINTREN_OUTSTA_Pos)

/**
  * @brief  Judge Is Setup Packet or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Setup Packet
  * @retval 1 Is Setup Packet
  */
#define __LL_USB_IsSetupPacket(__USB__)             \
        READ_BIT_SHIFT((__USB__)->IUINTREN, USB_IUINTREN_SETUPSTA_Msk, USB_IUINTREN_SETUPSTA_Pos)

/**
  * @brief  Debounce Max Set
  * @param  __USB__ Specifies USB peripheral
  * @param  max Debounce Max
  * @return None
  */
#define __LL_USB_DebouceMax_Set(__USB__,  max)      \
        MODIFY_REG((__USB__)->IUINTREN, USB_IUINTREN_DETDB_Msk, (((max) & 0xfffUL) << USB_IUINTREN_DETDB_Pos))

/**
  * @brief  Unplug Detect Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_UnplugDet_INT_En(__USB__)          SET_BIT((__USB__)->IUINTREN, USB_IUINTREN_UPDETIEN_Msk)

/**
  * @brief  Unplug Detect Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_UnplugDet_INT_Dis(__USB__)         CLEAR_BIT((__USB__)->IUINTREN, USB_IUINTREN_UPDETIEN_Msk)

/**
  * @brief  Judge is Unplug Detect Interrupt Enable or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Unplug Detect Interrupt is Disable
  * @retval 1 Unplug Detect Interrupt is Enable
  */
#define __LL_USB_IsUnplugDetIntEn(__USB__)          \
        READ_BIT_SHIFT((__USB__)->IUINTREN, USB_IUINTREN_UPDETIEN_Msk, USB_IUINTREN_UPDETIEN_Pos)

/**
  * @brief  Insert Detect Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_InsertDet_INT_En(__USB__)          SET_BIT((__USB__)->IUINTREN, USB_IUINTREN_ISDETIEN_Msk)

/**
  * @brief  Insert Detect Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_InsertDet_INT_Dis(__USB__)         CLEAR_BIT((__USB__)->IUINTREN, USB_IUINTREN_ISDETIEN_Msk)

/**
  * @brief  Judge is Insert Detect Interrupt Enable or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Insert Detect Interrupt is Disable
  * @retval 1 Insert Detect Interrupt is Enable
  */
#define __LL_USB_IsInsertDetIntEn(__USB__)          \
        READ_BIT_SHIFT((__USB__)->IUINTREN, USB_IUINTREN_ISDETIEN_Msk, USB_IUINTREN_ISDETIEN_Pos)


/**
  * @brief  Endpoint 2 RX Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Ep2Rx_INT_En(__USB__)              SET_BIT((__USB__)->EPINTREN, USB_EPINTREN_EP2RXINTEN_Msk)

/**
  * @brief  Endpoint 2 RX Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Ep2Rx_INT_Dis(__USB__)             CLEAR_BIT((__USB__)->EPINTREN, USB_EPINTREN_EP2RXINTEN_Msk)

/**
  * @brief  Endpoint 1 RX Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Ep1Rx_INT_En(__USB__)              SET_BIT((__USB__)->EPINTREN, USB_EPINTREN_EP1RXINTEN_Msk)

/**
  * @brief  Endpoint 1 RX Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Ep1Rx_INT_Dis(__USB__)             CLEAR_BIT((__USB__)->EPINTREN, USB_EPINTREN_EP1RXINTEN_Msk)

/**
  * @brief  Endpoint 2 TX Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Ep2Tx_INT_En(__USB__)              SET_BIT((__USB__)->EPINTREN, USB_EPINTREN_EP2TXINTEN_Msk)

/**
  * @brief  Endpoint 2 TX Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Ep2Tx_INT_Dis(__USB__)             CLEAR_BIT((__USB__)->EPINTREN, USB_EPINTREN_EP2TXINTEN_Msk)

/**
  * @brief  Endpoint 1 TX Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Ep1Tx_INT_En(__USB__)              SET_BIT((__USB__)->EPINTREN, USB_EPINTREN_EP1TXINTEN_Msk)

/**
  * @brief  Endpoint 1 TX Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Ep1Tx_INT_Dis(__USB__)             CLEAR_BIT((__USB__)->EPINTREN, USB_EPINTREN_EP1TXINTEN_Msk)

/**
  * @brief  Endpoint 0 Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Ep0_INT_En(__USB__)                SET_BIT((__USB__)->EPINTREN, USB_EPINTREN_EP0INTEN_Msk)

/**
  * @brief  Endpoint 0 Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Ep0_INT_Dis(__USB__)               CLEAR_BIT((__USB__)->EPINTREN, USB_EPINTREN_EP0INTEN_Msk)

/**
  * @brief  Endpoint All Interrupt Enable Get
  * @param  __USB__ Specifies USB peripheral
  * @return Endpoint All Interrupt Enable
  */
#define __LL_USB_EpAllIntEn_Get(__USB__)            READ_REG((__USB__)->EPINTREN)


/**
  * @brief  Peripheral Disconnect Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_PeriphDisconn_INT_En(__USB__)      SET_BIT((__USB__)->USBINTREN, USB_USBINTREN_DISCONINTEN_Msk)

/**
  * @brief  Peripheral Disconnect Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_PeriphDisconn_INT_Dis(__USB__)     CLEAR_BIT((__USB__)->USBINTREN, USB_USBINTREN_DISCONINTEN_Msk)

/**
  * @brief  RX First SOF Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_SOF_INT_En(__USB__)                SET_BIT((__USB__)->USBINTREN, USB_USBINTREN_SOFINTEN_Msk)

/**
  * @brief  RX First SOF Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_SOF_INT_Dis(__USB__)               CLEAR_BIT((__USB__)->USBINTREN, USB_USBINTREN_SOFINTEN_Msk)

/**
  * @brief  Reset Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Rst_INT_En(__USB__)                SET_BIT((__USB__)->USBINTREN, USB_USBINTREN_RESETINTEN_Msk)

/**
  * @brief  Reset Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Rst_INT_Dis(__USB__)               CLEAR_BIT((__USB__)->USBINTREN, USB_USBINTREN_RESETINTEN_Msk)

/**
  * @brief  Resume Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Resume_INT_En(__USB__)             SET_BIT((__USB__)->USBINTREN, USB_USBINTREN_RESUMEINTEN_Msk)

/**
  * @brief  Resume Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Resume_INT_Dis(__USB__)            CLEAR_BIT((__USB__)->USBINTREN, USB_USBINTREN_RESUMEINTEN_Msk)

/**
  * @brief  Suspend Interrupt Enable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Suspend_INT_En(__USB__)            SET_BIT((__USB__)->USBINTREN, USB_USBINTREN_SUSPENDINTEN_Msk)

/**
  * @brief  Suspend Interrupt Disable
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Suspend_INT_Dis(__USB__)           CLEAR_BIT((__USB__)->USBINTREN, USB_USBINTREN_SUSPENDINTEN_Msk)

/**
  * @brief  Power All Interrupt Enable Get
  * @param  __USB__ Specifies USB peripheral
  * @return Power All Interrupt Enable
  */
#define __LL_USB_PowerAllIntEn_Get(__USB__)         READ_REG((__USB__)->USBINTREN)


/**
  * @brief  Judge is Unplug Detect Interrupt Pending or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 isn't Unplug Detect Interrupt Pending
  * @retval 1 is Unplug Detect Interrupt Pending
  */
#define __LL_USB_IsUnplugDetIntPnd(__USB__)         READ_BIT_SHIFT((__USB__)->IUINTR, USB_IUINTR_UPDETI_Msk, USB_IUINTR_UPDETI_Pos)

/**
  * @brief  Unplug Detect Interrupt Pending Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_UnplugDetIntPnd_Clr(__USB__)       SET_BIT((__USB__)->IUINTR, USB_IUINTR_UPDETI_Msk)

/**
  * @brief  Judge is Insert Detect Interrupt Pending or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 isn't Insert Detect Interrupt Pending
  * @retval 1 is Insert Detect Interrupt Pending
  */
#define __LL_USB_IsInsertDetIntPnd(__USB__)         READ_BIT_SHIFT((__USB__)->IUINTR, USB_IUINTR_ISDETI_Msk, USB_IUINTR_ISDETI_Pos)

/**
  * @brief  Insert Detect Interrupt Pending Clear
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_InsertDetIntPnd_Clr(__USB__)       SET_BIT((__USB__)->IUINTR, USB_IUINTR_ISDETI_Msk)


/**
  * @brief  Endpoint All Interrupt Pending Get
  * @param  __USB__ Specifies USB peripheral
  * @return Endpoint All Interrupt Pending
  */
#define __LL_USB_EpAllIntPending_Get(__USB__)       READ_REG((__USB__)->EPINTR)


/**
  * @brief  Power All Interrupt Pending Get
  * @param  __USB__ Specifies USB peripheral
  * @return Power All Interrupt Pending
  */
#define __LL_USB_PowerAllIntPending_Get(__USB__)    READ_REG((__USB__)->USBINTR)


/**
  * @brief  Write Single Byte to Endpoint TX FIFO
  * @param  __USB__ Specifies USB peripheral
  * @param  ep_num Endpoint Number @ref USB_EpNumETypeDef
  * @param  dat Data to be Written
  * @return None
  */
#define __LL_USB_EPFIFOWriteByte(__USB__, ep_num, dat)                                              \
        do {                                                                                        \
            __LL_USB_FIFO_REG_OFFSET((__USB__)->FIFO0, ((uint32_t)(ep_num) % EP_NUMS) * 4) = dat;   \
        } while(0)

/**
  * @brief  Read Single Byte from Endpoint RX FIFO
  * @param  __USB__ Specifies USB peripheral
  * @param  ep_num Endpoint Number @ref USB_EpNumETypeDef
  * @return Read Byte Data
  */
#define __LL_USB_EPFIFOReadByte(__USB__, ep_num)    (__LL_USB_FIFO_REG_OFFSET((__USB__)->FIFO0, ((uint32_t)(ep_num) % EP_NUMS) * 4))

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup USB_LL_Exported_Types USB LL Exported Types
  * @brief    USB LL Exported Types
  * @{
  */

/**
  * @brief USB Instance Definition
  */
typedef enum {
    USB_INSTANCE_0 = 0,         /*!< USB Instance 0         */
    USB_INSTANCE_NUMS,          /*!< USB Instance Numbers   */
} USB_InstanceETypeDef;

/**
  * @brief USB Endpoint Maximum Packet Size Definition
  */
typedef enum {
    USB_EP_MAX_PKT_SIZE_8Bytes = 0,     /*!< USB Endpoint Maximum Packet Size 8Bytes    */
    USB_EP_MAX_PKT_SIZE_16Bytes,        /*!< USB Endpoint Maximum Packet Size 16Bytes   */
    USB_EP_MAX_PKT_SIZE_32Bytes,        /*!< USB Endpoint Maximum Packet Size 32Bytes   */
    USB_EP_MAX_PKT_SIZE_64Bytes,        /*!< USB Endpoint Maximum Packet Size 64Bytes   */
    USB_EP_MAX_PKT_SIZE_128Bytes,       /*!< USB Endpoint Maximum Packet Size 128Bytes  */
    USB_EP_MAX_PKT_SIZE_256Bytes,       /*!< USB Endpoint Maximum Packet Size 256Bytes  */
} USB_EpMaxPktSizeETypeDef;

/**
  * @brief USB Endpoint FIFO Start Address Definition
  */
typedef enum {
    USB_EP_FIFO_START_ADDR_0Byte = 0,   /*!< USB Endpoint FIFO Start Address 0Byte      */
    USB_EP_FIFO_START_ADDR_8Bytes,      /*!< USB Endpoint FIFO Start Address 8Bytes     */
    USB_EP_FIFO_START_ADDR_16Bytes,     /*!< USB Endpoint FIFO Start Address 16Bytes    */
    USB_EP_FIFO_START_ADDR_32Bytes,     /*!< USB Endpoint FIFO Start Address 32Bytes    */
    USB_EP_FIFO_START_ADDR_64Bytes,     /*!< USB Endpoint FIFO Start Address 64Bytes    */
    USB_EP_FIFO_START_ADDR_128Bytes,    /*!< USB Endpoint FIFO Start Address 128Bytes   */
    USB_EP_FIFO_START_ADDR_256Bytes,    /*!< USB Endpoint FIFO Start Address 256Bytes   */
} USB_EpFIFOStartAddrETypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/** @addtogroup USB_LL_Exported_Variables
  * @{
  */
extern const USB_LL_DrvTypeDef usb_ll_drv;
/**
  * @}
  */


/* Exported Functions --------------------------------------------------------*/
/** @addtogroup USB_LL_Exported_Functions
  * @{
  */

/** @addtogroup USB_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_USB_Init(USB_TypeDef *Instance, USB_LL_IRQCbTypeDef *irq_cb);
LL_StatusETypeDef LL_USB_DeInit(USB_TypeDef *Instance);
void LL_USB_MspInit(USB_TypeDef *Instance);
void LL_USB_MspDeInit(USB_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup USB_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_USB_EpCfg(USB_TypeDef *Instance, USB_EpCfgTypeDef *ep_cfg, bool ep_en);
LL_StatusETypeDef LL_USB_EpAllDis(USB_TypeDef *Instance);
LL_StatusETypeDef LL_USB_EpFIFOFlush(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, USB_EpDirETypeDef ep_dir);
uint32_t LL_USB_EpFIFORead(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, uint8_t *buf, uint32_t len);
uint32_t LL_USB_EpFIFOWrite(USB_TypeDef *Instance, USB_EpNumETypeDef ep_num, uint8_t *buf, uint32_t len);
/**
  * @}
  */


/** @addtogroup USB_LL_Exported_Functions_Group3
  * @{
  */
void LL_USB_SetupStallSet(USB_TypeDef *Instance);
void LL_USB_SetupStallClr(USB_TypeDef *Instance);
void LL_USB_SetupDataEndSet(USB_TypeDef *Instance);
void LL_USB_SetupAddrSet(USB_TypeDef *Instance, uint8_t addr);
/**
  * @}
  */


/** @addtogroup USB_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_USB_PowerIRQHandler(USB_TypeDef *Instance);
void LL_USB_PowerSuspendCallback(USB_TypeDef *Instance);
void LL_USB_PowerResumeCallback(USB_TypeDef *Instance);
void LL_USB_PowerResetCallback(USB_TypeDef *Instance);
void LL_USB_PowerSOFCallback(USB_TypeDef *Instance);
void LL_USB_PowerDisconnCallback(USB_TypeDef *Instance);

void LL_USB_DetIRQHandler(USB_TypeDef *Instance);
void LL_USB_DetInsertCallback(USB_TypeDef *Instance);
void LL_USB_DetUnplugCallback(USB_TypeDef *Instance);

void LL_USB_EpIRQHandler(USB_TypeDef *Instance);
void LL_USB_Ep0SetupCallback(USB_TypeDef *Instance);
void LL_USB_Ep0InCallback(USB_TypeDef *Instance);
void LL_USB_Ep0OutCallback(USB_TypeDef *Instance);
void LL_USB_Ep1InCallback(USB_TypeDef *Instance);
void LL_USB_Ep1OutCallback(USB_TypeDef *Instance);
void LL_USB_Ep2InCallback(USB_TypeDef *Instance);
void LL_USB_Ep2OutCallback(USB_TypeDef *Instance);
/**
  * @}
  */

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
#endif /* __cplusplus */

#endif /* _TAE32G58XX_LL_USB_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

