/**
  ******************************************************************************
  * @file    tae32f53xx_ll_usb.h
  * @author  MCD Application Team
  * @brief   Header file of USB LL module.
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
#ifndef _TAE32F53XX_LL_USB_H_
#define _TAE32F53XX_LL_USB_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32f53xx_ll_def.h"


/** @addtogroup TAE32F53xx_LL_Driver
  * @{
  */

/** @addtogroup USB_LL
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup USB_LL_Exported_Macros USB LL Exported Macros
  * @brief    USB LL Exported Macros
  * @{
  */

/**
  * @brief  Set Function Address
  * @param  __USB__ Specifies USB peripheral
  * @param  func_addr Function Address
  * @return None
  */
#define __LL_USB_FuncAddr_Set(__USB__, func_addr)   \
        MODIFY_REG((__USB__)->FADDR, USB_FUNC_ADDR_Msk, ((func_addr & 0x7FUL) << USB_FUNC_ADDR_Pos))


/**
  * @brief  Enable the SUSPENDM output
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_SuspendDMOut_En(__USB__)           SET_BIT((__USB__)->POWER, USB_SUSPEND_DM_EN_Msk)

/**
  * @brief  Disable the SUSPENDM output
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_SuspendDMOut_Dis(__USB__)          CLEAR_BIT((__USB__)->POWER, USB_SUSPEND_DM_EN_Msk)

/**
  * @brief  Enable HighSpeed
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_HighSpeed_En(__USB__)              SET_BIT((__USB__)->POWER, USB_HS_EN_Msk)

/**
  * @brief  Disable HighSpeed
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_HighSpeed_Dis(__USB__)             CLEAR_BIT((__USB__)->POWER, USB_HS_EN_Msk)

/**
  * @brief  Enable Soft Connect
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_SoftConn_En(__USB__)               SET_BIT((__USB__)->POWER, USB_SOFT_CONN_EN_Msk)

/**
  * @brief  Disable Soft Connect
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_SoftConn_Dis(__USB__)              CLEAR_BIT((__USB__)->POWER, USB_SOFT_CONN_EN_Msk)


/**
  * @brief  Get Endpoint 0 and TX Endpoint Interrupt Status
  * @param  __USB__ Specifies USB peripheral
  * @return Endpoint 0 and TX Endpoint Interrupt Status
  */
#define __LL_USB_EP0AndEPxTX_IntSta_Get(__USB__)    ((__USB__)->INTRTX)


/**
  * @brief  Get RX Endpoint Interrupt Status
  * @param  __USB__ Specifies USB peripheral
  * @return RX Interrupt Status
  */
#define __LL_USB_EPx_RXIntSta_Get(__USB__)          ((__USB__)->INTRRX)


/**
  * @brief  Enable Endpoint 0 and TX Endpoint Interrupt
  * @param  __USB__ Specifies USB peripheral
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @return None
  */
#define __LL_USB_EP0AndEPxTX_Int_EN(__USB__, ep_num)                                                                        \
        do {                                                                                                                \
            if(ep_num >= EP_NUMS){                                                                                          \
                break;                                                                                                      \
            }                                                                                                               \
            uint16_t ep0_and_epxtx_int_en_bitmask[] = {USB_EP0_INT_EN_Msk, USB_TX_EP1_INT_EN_Msk, USB_TX_EP2_INT_EN_Msk};   \
            SET_BIT((__USB__)->INTRTXE, ep0_and_epxtx_int_en_bitmask[ep_num]);                                              \
        } while(0)

/**
  * @brief  Disable Endpoint 0 and TX Endpoint Interrupt
  * @param  __USB__ Specifies USB peripheral
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @return None
  */
#define __LL_USB_EP0AndEPxTX_Int_Dis(__USB__, ep_num)                                                                       \
        do {                                                                                                                \
            if(ep_num >= EP_NUMS){                                                                                          \
                break;                                                                                                      \
            }                                                                                                               \
            uint16_t ep0_and_epxtx_int_en_bitmask[] = {USB_EP0_INT_EN_Msk, USB_TX_EP1_INT_EN_Msk, USB_TX_EP2_INT_EN_Msk};   \
            CLEAR_BIT((__USB__)->INTRTXE, ep0_and_epxtx_int_en_bitmask[ep_num]);                                            \
        } while(0)


/**
  * @brief  Enable RX Endpoint Interrupt
  * @param  __USB__ Specifies USB peripheral
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @return None
  */
#define __LL_USB_EPx_RXInt_En(__USB__, ep_num)                                                                              \
        do {                                                                                                                \
            if(ep_num >= EP_NUMS){                                                                                          \
                break;                                                                                                      \
            }                                                                                                               \
            uint16_t epxrx_int_en_bitmask[] = {0, USB_RX_EP1_INT_EN_Msk, USB_RX_EP2_INT_EN_Msk};                            \
            SET_BIT((__USB__)->INTRRXE, epxrx_int_en_bitmask[ep_num]);                                                      \
        } while(0)

/**
  * @brief  Disable RX Endpoint Interrupt
  * @param  __USB__ Specifies USB peripheral
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @return None
  */
#define __LL_USB_EPx_RXInt_Dis(__USB__, ep_num)                                                                             \
        do {                                                                                                                \
            if(ep_num >= EP_NUMS){                                                                                          \
                break;                                                                                                      \
            }                                                                                                               \
            uint16_t epxrx_int_en_bitmask[] = {0, USB_RX_EP1_INT_EN_Msk, USB_RX_EP2_INT_EN_Msk};                            \
            CLEAR_BIT((__USB__)->INTRRXE, epxrx_int_en_bitmask[ep_num]);                                                    \
        } while(0)


/**
  * @brief  Get USB Controler Interrupt Status
  * @param  __USB__ Specifies USB peripheral
  * @return USB Controler Interrupt Status
  */
#define __LL_USB_IntSta_Get(__USB__)            (READ_BIT((__USB__)->INTRUSB, USB_CTRL_INT_ALL_Msk) >> USB_SUSPEND_INT_STA_Pos)


/**
  * @brief  Enable USB Controler Interrupt
  * @param  __USB__ Specifies USB peripheral
  * @param  int_bit_mask Interrupt BitMask to Be Enable
  * @return None
  */
#define __LL_USB_Int_EN(__USB__, int_bit_mask)      SET_BIT((__USB__)->INTRUSBE, int_bit_mask)

/**
  * @brief  Disable USB Controler Interrupt
  * @param  __USB__ Specifies USB peripheral
  * @param  int_bit_mask Interrupt BitMask to be Disable
  * @return None
  */
#define __LL_USB_Int_Dis(__USB__, int_bit_mask)     CLEAR_BIT((__USB__)->INTRUSBE, int_bit_mask)


/**
  * @brief  Get Frame Number
  * @param  __USB__ Specifies USB peripheral
  * @return Frame Number
  */
#define __LL_USB_FrameNum_Get(__USB__)              (READ_BIT((__USB__)->FRAME, USB_FRAME_NUM_Msk) >> USB_FRAME_NUM_Pos)


/**
  * @brief  Set Endpoint Index
  * @param  __USB__ Specifies USB peripheral
  * @param  idx Index to be Set
  * @return None
  */
#define __LL_USB_EPIndex_Set(__USB__, idx)                      \
        MODIFY_REG((__USB__)->INDEX, USB_EP_INDEX_Msk, ((idx & 0xFUL) << USB_EP_INDEX_Pos))


/**
  * @brief  Set TX Max Payload
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @param  max_payload Max Payload to be Set
  * @return None
  */
#define __LL_USB_EPx_TXMaxPayload_Set(__USB__,  max_payload)    \
        MODIFY_REG((__USB__)->TXMAXP, USB_EPX_TX_MAX_PAYLD_Msk, ((max_payload & 0xFFFFUL) << USB_EPX_TX_MAX_PAYLD_Pos))

/**
  * @brief  Get TX Max Payload
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return TX Max Payload
  */
#define __LL_USB_EPx_TXMaxPayload_Get(__USB__)                  \
        (READ_BIT((__USB__)->TXMAXP, USB_EPX_TX_MAX_PAYLD_Msk) >> USB_EPX_TX_MAX_PAYLD_Pos)


/**
  * @brief  Judge Endpoint 0 RX Packet Ready or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 RX Packet Not Ready
  * @retval 1 RX Packet Ready
  */
#define __LL_USB_EP0_IsRXPktRdy(__USB__)        (READ_BIT((__USB__)->TX_CSR0, USB_EP0_RX_PKT_RDY_Msk) >> USB_EP0_RX_PKT_RDY_Pos)

/**
  * @brief  Clear Endpoint 0 RX Packet Ready
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_RXPktRdy_Clr(__USB__)      SET_BIT((__USB__)->TX_CSR0, USB_EP0_CLR_RX_PKT_RDY_Msk)

/**
  * @brief  Set Endpoint 0 TX Packet Ready
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_TXPktRdy_Set(__USB__)      SET_BIT((__USB__)->TX_CSR0, USB_EP0_TX_PKT_RDY_Msk)

/**
  * @brief  Judge Endpoint 0 TX Packet Ready or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 TX Packet Not Ready
  * @retval 1 TX Packet Ready
  */
#define __LL_USB_EP0_IsTXPktRdy(__USB__)        (READ_BIT((__USB__)->TX_CSR0, USB_EP0_TX_PKT_RDY_Msk) >> USB_EP0_TX_PKT_RDY_Pos)

/**
  * @brief  Set Endpoint 0 to Send Stall
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_SendStall_Set(__USB__)     SET_BIT((__USB__)->TX_CSR0, USB_EP0_SEND_STALL_Msk)

/**
  * @brief  Judge Endpoint 0 has Sent Stall or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Hasn't Sent Stall
  * @retval 1 Has Sent Stall
  */
#define __LL_USB_EP0_IsSentStall(__USB__)       (READ_BIT((__USB__)->TX_CSR0, USB_EP0_SENT_STALL_Msk) >> USB_EP0_SENT_STALL_Pos)

/**
  * @brief  Clear Endpoint 0 Sent Stall Status
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_SentStall_Clr(__USB__)     CLEAR_BIT((__USB__)->TX_CSR0, USB_EP0_SENT_STALL_Msk)

/**
  * @brief  Set Endpoint 0 Data End
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_DataEnd_Set(__USB__)       SET_BIT((__USB__)->TX_CSR0, USB_EP0_DATA_END_Msk)

/**
  * @brief  Judge Endpoint 0 has SetupEnd or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Hasn't Setup End
  * @retval 1 Has Setup End
  */
#define __LL_USB_EP0_IsSetupEnd(__USB__)        (READ_BIT((__USB__)->TX_CSR0, USB_EP0_SETUP_END_Msk) >> USB_EP0_SETUP_END_Pos)

/**
  * @brief  Clear Endpoint 0 SetupEnd Status
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_SetupEnd_Clr(__USB__)      SET_BIT((__USB__)->TX_CSR0, USB_EP0_CLR_SETUP_END_Msk)

/**
  * @brief  Flush Endpoint 0 FIFO
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EP0_FlushFIFO(__USB__)         SET_BIT((__USB__)->TX_CSR0, USB_EP0_FLUSH_FIFO_Msk)


/**
  * @brief  Enable TX Packet Ready Auto Set Function
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXPktRdyAutoSet_En(__USB__)    SET_BIT((__USB__)->TX_CSRX, USB_EPX_TX_AUTO_SET_Msk)

/**
  * @brief  Disable TX Packet Ready Auto Set Function
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXPktRdyAutoSet_Dis(__USB__)   CLEAR_BIT((__USB__)->TX_CSRX, USB_EPX_TX_AUTO_SET_Msk)

/**
  * @brief  Enable Endpoint TX ISO
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXISO_En(__USB__)              SET_BIT((__USB__)->TX_CSRX, USB_EPX_TX_ISO_EN_Msk)

/**
  * @brief  Disable Endpoint TX ISO
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXISO_Dis(__USB__)             CLEAR_BIT((__USB__)->TX_CSRX, USB_EPX_TX_ISO_EN_Msk)

/**
  * @brief  Enable Endpoint TX
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TX_En(__USB__)                 SET_BIT((__USB__)->TX_CSRX, USB_EPX_DIR_MODE_Msk)

/**
  * @brief  Enable Endpoint RX
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RX_En(__USB__)                 CLEAR_BIT((__USB__)->TX_CSRX, USB_EPX_DIR_MODE_Msk)

/**
  * @brief  Enable Endpoint TX DMA Request
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXDMAReq_En(__USB__)           SET_BIT((__USB__)->TX_CSRX, USB_EPX_TX_DMA_REQ_EN_Msk)

/**
  * @brief  Disable Endpoint TX DMA Request
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXDMAReq_Dis(__USB__)          CLEAR_BIT((__USB__)->TX_CSRX, USB_EPX_TX_DMA_REQ_EN_Msk)

/**
  * @brief  Set Endpoint TX to Force Data Toggle
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXForceDataTog_Set(__USB__)    SET_BIT((__USB__)->TX_CSRX, USB_EPX_TX_FRC_DATA_TOG_Msk)

/**
  * @brief  Clear Endpoint TX to Force Data Toggle
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXForceDataTog_Clr(__USB__)    CLEAR_BIT((__USB__)->TX_CSRX, USB_EPX_TX_FRC_DATA_TOG_Msk)

/**
  * @brief  Set Endpoint TX DMA Request Mode to 0
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXDMAReqMode0_Set(__USB__)     CLEAR_BIT((__USB__)->TX_CSRX, USB_EPX_TX_DMA_REQ_MODE_Msk)

/**
  * @brief  Set Endpoint TX DMA Request Mode to 1
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXDMAReqMode1_Set(__USB__)     SET_BIT((__USB__)->TX_CSRX, USB_EPX_TX_DMA_REQ_MODE_Msk)

/**
  * @brief  Judge TX ISO Endpoint Is Incomplete or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Complete
  * @retval 1 Incomplete
  */
#define __LL_USB_EPx_IsTXISOInComp(__USB__)         \
        (READ_BIT((__USB__)->TX_CSRX, USB_EPX_TX_ISO_INCOMP_Msk) >> USB_EPX_TX_ISO_INCOMP_Pos)

/**
  * @brief  Clear TX Endpoint Data Toggle
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXDataTog_Clr(__USB__)         SET_BIT((__USB__)->TX_CSRX, USB_EPX_TX_CLR_DATA_TOG_Msk)

/**
  * @brief  Judge TX Endpoint has Sent Stall or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Hasn't Sent Stall
  * @retval 1 Has Sent Stall
  */
#define __LL_USB_EPx_IsTXSentStall(__USB__)         \
        (READ_BIT((__USB__)->TX_CSRX, USB_EPX_TX_SENT_STALL_Msk) >> USB_EPX_TX_SENT_STALL_Pos)

/**
  * @brief  Clear TX Endpoint Sent Stall Status
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXSentStall_Clr(__USB__)       CLEAR_BIT((__USB__)->TX_CSRX, USB_EPX_TX_SENT_STALL_Msk)

/**
  * @brief  Enable TX Endpoint to Send Stall
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXSendStall_En(__USB__)        SET_BIT((__USB__)->TX_CSRX, USB_EPX_TX_SEND_STALL_Msk)

/**
  * @brief  Disable TX Endpoint to Send Stall
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXSendStall_Dis(__USB__)       CLEAR_BIT((__USB__)->TX_CSRX, USB_EPX_TX_SEND_STALL_Msk)

/**
  * @brief  Flush TX Endpoint FIFO
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXFlushFIFO(__USB__)           SET_BIT((__USB__)->TX_CSRX, USB_EPX_TX_FLUSH_FIFO_Msk)

/**
  * @brief  Judge TX Endpoint FIFO Is UnderRun or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't UnderRun
  * @retval 1 Is UnderRun
  */
#define __LL_USB_EPx_IsTXFIFOUnderRun(__USB__)      \
        (READ_BIT((__USB__)->TX_CSRX, USB_EPX_TX_UNDER_RUN_Msk) >> USB_EPX_TX_UNDER_RUN_Pos)

/**
  * @brief  Clear TX Endpoint UnderRun Status
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXFIFOUnderRun_Clr(__USB__)    CLEAR_BIT((__USB__)->TX_CSRX, USB_EPX_TX_UNDER_RUN_Msk)

/**
  * @brief  Judge TX Endpoint FIFO Is NoEmpty or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't NoEmpty
  * @retval 1 Is NoEmpty
  */
#define __LL_USB_EPx_IsTXFIFONoEmpty(__USB__)       \
        (READ_BIT((__USB__)->TX_CSRX, USB_EPX_TX_FIFO_NOT_EPY_Msk) >> USB_EPX_TX_FIFO_NOT_EPY_Pos)

/**
  * @brief  Set TX Endpoint Packet Ready
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_TXPktRdy_Set(__USB__)          SET_BIT((__USB__)->TX_CSRX, USB_EPX_TX_PKT_RDY_Msk)

/**
  * @brief  Judge Endpoint TX Packet Ready or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Packet Ready
  * @retval 1 Is Packet Ready
  */
#define __LL_USB_EPx_IsTXPktRdy(__USB__)            \
        (READ_BIT((__USB__)->TX_CSRX, USB_EPX_TX_PKT_RDY_Msk) >> USB_EPX_TX_PKT_RDY_Pos)


/**
  * @brief  Set RX Max Payload
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @param  max_payload Max Payload to be Set
  * @return None
  */
#define __LL_USB_EPx_RXMaxPayload_Set(__USB__,  max_payload)    \
        MODIFY_REG((__USB__)->RXMAXP, USB_EPX_RX_MAX_PAYLD_Msk, ((max_payload & 0xFFFFUL) << USB_EPX_RX_MAX_PAYLD_Pos))

/**
  * @brief  Get RX Max Payload
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return RX Max Payload
  */
#define __LL_USB_EPx_RXMaxPayload_Get(__USB__)                  \
        (READ_BIT((__USB__)->RXMAXP, USB_EPX_RX_MAX_PAYLD_Msk) >> USB_EPX_RX_MAX_PAYLD_Pos)


/**
  * @brief  Enable RX Packet Ready Auto Clear Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXPktRdyAutoClr_En(__USB__)    SET_BIT((__USB__)->RXCSRN, USB_EPX_RX_AUTO_CLR_Msk)

/**
  * @brief  Disable RX Packet Ready Auto Clear Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXPktRdyAutoClr_Dis(__USB__)   CLEAR_BIT((__USB__)->RXCSRN, USB_EPX_RX_AUTO_CLR_Msk)

/**
  * @brief  Enable Endpoint RX ISO
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXISO_En(__USB__)              SET_BIT((__USB__)->RXCSRN, USB_EPX_RX_ISO_EN_Msk)

/**
  * @brief  Disable Endpoint RX ISO
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXISO_Dis(__USB__)             CLEAR_BIT((__USB__)->RXCSRN, USB_EPX_RX_ISO_EN_Msk)

/**
  * @brief  Enable Endpoint RX DMA Request
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXDMAReq_En(__USB__)           SET_BIT((__USB__)->RXCSRN, USB_EPX_RX_DMQ_REQ_EN_Msk)

/**
  * @brief  Disable Endpoint RX DMA Request
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXDMAReq_Dis(__USB__)          CLEAR_BIT((__USB__)->RXCSRN, USB_EPX_RX_DMQ_REQ_EN_Msk)

/**
  * @brief  Judge RX ISO Endpoint PID Error or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't PID Error
  * @retval 1 Is PID Error
  */
#define __LL_USB_EPx_IsRXISOPIDErr(__USB__)         \
        (READ_BIT((__USB__)->RXCSRN, USB_EPX_RX_ISO_PID_ERR_Msk) >> USB_EPX_RX_ISO_PID_ERR_Pos)

/**
  * @brief  Set Endpoint RX DMA Request Mode to 0
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXDMAReqMode0_Set(__USB__)     CLEAR_BIT((__USB__)->RXCSRN, USB_EPX_RX_DMA_REQ_MODE_Msk)

/**
  * @brief  Set Endpoint RX DMA Request Mode to 1
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXDMAReqMode1_Set(__USB__)     SET_BIT((__USB__)->RXCSRN, USB_EPX_RX_DMA_REQ_MODE_Msk)

/**
  * @brief  Judge RX ISO Endpoint Is Incomplete or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Complete
  * @retval 1 Incomplete
  */
#define __LL_USB_EPx_IsRXISOInComp(__USB__)         \
        (READ_BIT((__USB__)->RXCSRN, USB_EPX_RX_ISO_INCOMP_Msk) >> USB_EPX_RX_ISO_INCOMP_Pos)

/**
  * @brief  Clear RX Endpoint Data Toggle
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXDataTog_Clr(__USB__)         SET_BIT((__USB__)->RXCSRN, USB_EPX_RX_CLR_DATA_TOG_Msk)

/**
  * @brief  Judge RX Endpoint has Sent Stall or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Hasn't Sent Stall
  * @retval 1 Has Sent Stall
  */
#define __LL_USB_EPx_IsRXSentStall(__USB__)         \
        (READ_BIT((__USB__)->RXCSRN, USB_EPX_RX_SENT_STALL_Msk) >> USB_EPX_RX_SENT_STALL_Pos)

/**
  * @brief  Clear RX Endpoint Sent Stall Status
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXSentStall_Clr(__USB__)       CLEAR_BIT((__USB__)->RXCSRN, USB_EPX_RX_SENT_STALL_Msk)

/**
  * @brief  Enable RX Endpoint to Send Stall
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXSendStall_En(__USB__)        SET_BIT((__USB__)->RXCSRN, USB_EPX_RX_SEND_STALL_Msk)

/**
  * @brief  Disable RX Endpoint to Send Stall
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXSendStall_Dis(__USB__)       CLEAR_BIT((__USB__)->RXCSRN, USB_EPX_RX_SEND_STALL_Msk)

/**
  * @brief  Flush RX Endpoint FIFO
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXFlushFIFO(__USB__)           SET_BIT((__USB__)->RXCSRN, USB_EPX_RX_FLUSH_FIFO_Msk)

/**
  * @brief  Judge RX ISO Endpoint Data Error or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Data Error
  * @retval 1 Is Data Error
  */
#define __LL_USB_EPx_IsISORXDataErr(__USB__)        \
        (READ_BIT((__USB__)->RXCSRN, USB_EPX_RX_ISO_DATA_ERR_Msk) >> USB_EPX_RX_ISO_DATA_ERR_Pos)

/**
  * @brief  Judge RX ISO Endpoint FIFO Is OverRun or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't OverRun
  * @retval 1 Is OverRun
  */
#define __LL_USB_EPx_IsISORXFIFOOverRun(__USB__)    \
        (READ_BIT((__USB__)->RXCSRN, USB_EPX_RX_OVER_RUN_Msk) >> USB_EPX_RX_OVER_RUN_Pos)

/**
  * @brief  Clear RX ISO Endpoint OverrRun Status
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_ISORXFIFOOverRun_Clr(__USB__)  CLEAR_BIT((__USB__)->RXCSRN, USB_EPX_RX_OVER_RUN_Msk)

/**
  * @brief  Judge RX FIFO Full or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Full
  * @retval 1 Is Full
  */
#define __LL_USB_EPx_IsRXFIFOFull(__USB__)          \
        (READ_BIT((__USB__)->RXCSRN, USB_EPX_RX_FIFO_FULL_Msk) >> USB_EPX_RX_FIFO_FULL_Pos)

/**
  * @brief  Judge Endpoint RX Packet Ready or not
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Packet Ready
  * @retval 1 Is Packet Ready
  */
#define __LL_USB_EPx_IsRXPktRdy(__USB__)            \
        (READ_BIT((__USB__)->RXCSRN, USB_EPX_RX_PKT_RDY_Msk) >> USB_EPX_RX_PKT_RDY_Pos)

/**
  * @brief  Clear RX Endpoint Packet Ready Status
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_EPx_RXPktRdy_Clr(__USB__)          CLEAR_BIT((__USB__)->RXCSRN, USB_EPX_RX_PKT_RDY_Msk)


/**
  * @brief  Get Endpoint RX Counter
  * @note   Must Set Endpoint Index first Before Call This Macro Function
  * @param  __USB__ Specifies USB peripheral
  * @return RX Counter
  */
#define __LL_USB_RXCount_Get(__USB__)               (READ_BIT((__USB__)->RXCOUNT, USB_RX_CNT_Msk) >> USB_RX_CNT_Pos)


/**
  * @brief  Write Single Byte to Endpoint TX FIFO
  * @param  __USB__ Specifies USB peripheral
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @param  dat Data to be Written
  * @return None
  */
#define __LL_USB_EPFIFOWriteByte(__USB__, ep_num, dat)      do{ (__USB__)->EP_FIFO[ep_num][0] = dat; }while(0)

/**
  * @brief  Read Single Byte form Endpoint RX FIFO
  * @param  __USB__ Specifies USB peripheral
  * @param  ep_num USB_EpNumETypeDef Type Endpoint Number
  * @return Read Byte Data
  */
#define __LL_USB_EPFIFOReadByte(__USB__, ep_num)            ((__USB__)->EP_FIFO[ep_num][0])


/**
  * @brief  Config DM Output Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMOutputHardware(__USB__)          CLEAR_BIT((__USB__)->UCFG0, USB_DM_OE_EN_Msk)

/**
  * @brief  Config DM Output Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMOutputNormal(__USB__)            SET_BIT((__USB__)->UCFG0, USB_DM_OE_EN_Msk | USB_DM_OE_Msk)

/**
  * @brief  Disable DM Output
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMOutputDisable(__USB__)           MODIFY_REG((__USB__)->UCFG0, 0x3UL<<USB_DM_OE_EN_Pos, 0x1UL<<USB_DM_OE_EN_Pos)

/**
  * @brief  Config DP Output Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPOutputHardware(__USB__)          CLEAR_BIT((__USB__)->UCFG0, USB_DP_OE_EN_Msk)

/**
  * @brief  Config DP Output Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPOutputNormal(__USB__)            SET_BIT((__USB__)->UCFG0, USB_DP_OE_EN_Msk | USB_DP_OE_Msk)

/**
  * @brief  Disable DP Output
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPOutputDisable(__USB__)           MODIFY_REG((__USB__)->UCFG0, 0x3UL<<USB_DP_OE_EN_Pos, 0x1UL<<USB_DP_OE_EN_Pos)

/**
  * @brief  Config DM Input Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMInputHardware(__USB__)           CLEAR_BIT((__USB__)->UCFG0, USB_DM_IE_EN_Msk)

/**
  * @brief  Config DM Input Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMInputNormal(__USB__)             SET_BIT((__USB__)->UCFG0, USB_DM_IE_EN_Msk | USB_DM_IE_Msk)

/**
  * @brief  Disable DM Input
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMInputDisable(__USB__)            MODIFY_REG((__USB__)->UCFG0, 0x3UL<<USB_DM_IE_EN_Pos, 0x1UL<<USB_DM_IE_EN_Pos)

/**
  * @brief  Config DP Input Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPInputHardware(__USB__)           CLEAR_BIT((__USB__)->UCFG0, USB_DP_IE_EN_Msk)

/**
  * @brief  Config DP Input Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPInputNormal(__USB__)             SET_BIT((__USB__)->UCFG0, USB_DP_IE_EN_Msk | USB_DP_IE_Msk)

/**
  * @brief  Disable DP Input
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPInputDisable(__USB__)            MODIFY_REG((__USB__)->UCFG0, 0x3UL<<USB_DP_IE_EN_Pos, 0x1UL<<USB_DP_IE_EN_Pos)

/**
  * @brief  Config DM PullDown Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullDownHardware(__USB__)        CLEAR_BIT((__USB__)->UCFG0, USB_DM_PD_EN_Msk)

/**
  * @brief  Config DM PullDown Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullDownNormal(__USB__)          SET_BIT((__USB__)->UCFG0, USB_DM_PD_EN_Msk | USB_DM_PD_Msk)

/**
  * @brief  Disable DM PullDown
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullDownDisable(__USB__)         MODIFY_REG((__USB__)->UCFG0, 0x3UL<<USB_DM_PD_EN_Pos, 0x1UL<<USB_DM_PD_EN_Pos)

/**
  * @brief  Config DM PullUp Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullUpHardware(__USB__)          CLEAR_BIT((__USB__)->UCFG0, USB_DM_PU_EN_Msk)

/**
  * @brief  Config DM PullUp Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullUpNormal(__USB__)            SET_BIT((__USB__)->UCFG0, USB_DM_PU_EN_Msk | USB_DM_PU_Msk)

/**
  * @brief  Disable DM PullUp
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DMPullUpDisable(__USB__)           MODIFY_REG((__USB__)->UCFG0, 0x3UL<<USB_DM_PU_EN_Pos, 0x1UL<<USB_DM_PU_EN_Pos)

/**
  * @brief  Config DP PullDown Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullDownHardware(__USB__)        CLEAR_BIT((__USB__)->UCFG0, USB_DP_PD_EN_Msk)

/**
  * @brief  Config DP PullDown Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullDownNormal(__USB__)          SET_BIT((__USB__)->UCFG0, USB_DP_PD_EN_Msk | USB_DP_PD_Msk)

/**
  * @brief  Disable DP PullDown
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullDownDisable(__USB__)         MODIFY_REG((__USB__)->UCFG0, 0x3UL<<USB_DP_PD_EN_Pos, 0x1UL<<USB_DP_PD_EN_Pos)

/**
  * @brief  Config DP PullUp Hardware
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullUpHardware(__USB__)          CLEAR_BIT((__USB__)->UCFG0, USB_DP_PU_EN_Msk)

/**
  * @brief  Config DP PullUp Normal
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullUpNormal(__USB__)            SET_BIT((__USB__)->UCFG0, USB_DP_PU_EN_Msk | USB_DP_PU_Msk)

/**
  * @brief  Disable DP PullUp
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_DPPullUpDisable(__USB__)           MODIFY_REG((__USB__)->UCFG0, 0x3UL<<USB_DP_PU_EN_Pos, 0x1UL<<USB_DP_PU_EN_Pos)

/**
  * @brief  Set Vbus Above VBusValid Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusValidThreshold_Set(__USB__)    SET_BIT((__USB__)->UCFG0, USB_VBUS_VALID_THRES_Msk)

/**
  * @brief  Clear Vbus Above VBusValid Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusValidThreshold_Clr(__USB__)    CLEAR_BIT((__USB__)->UCFG0, USB_VBUS_VALID_THRES_Msk)

/**
  * @brief  Set Vbus Above Vbus A-device Session Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusAboveAdevSessThres_Set(__USB__)    SET_BIT((__USB__)->UCFG0, USB_VBUS_A_SESS_THRES_Msk)

/**
  * @brief  Clear Vbus Above Vbus A-device Session Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusAboveAdevSessThres_Clr(__USB__)    CLEAR_BIT((__USB__)->UCFG0, USB_VBUS_A_SESS_THRES_Msk)

/**
  * @brief  Set Vbus Above Session End Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusAboveSessEndThres_Set(__USB__)     SET_BIT((__USB__)->UCFG0, USB_VBUS_SESS_END_THRES_Msk)

/**
  * @brief  Clear Vbus Above Session End Threshold
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_VbusAboveSessEndThres_Clr(__USB__)     CLEAR_BIT((__USB__)->UCFG0, USB_VBUS_SESS_END_THRES_Msk)

/**
  * @brief  Set Mini-AB Connector ID Pin
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_MiniABConnectorID_Set(__USB__)         SET_BIT((__USB__)->UCFG0, USB_MINI_AB_CONN_ID_Msk)

/**
  * @brief  Clear Mini-AB Connector ID Pin
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_MiniABConnectorID_Clr(__USB__)         CLEAR_BIT((__USB__)->UCFG0, USB_MINI_AB_CONN_ID_Msk)

/**
  * @brief  Enable USB PHY
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_PHY_En(__USB__)                        SET_BIT((__USB__)->UCFG0, USB_PHY_EN_Msk)

/**
  * @brief  Disable USB PHY
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_PHY_Dis(__USB__)                       CLEAR_BIT((__USB__)->UCFG0, USB_PHY_EN_Msk)


/**
  * @brief  Enable Interrupt Send to CPU
  * @param  __USB__ Specifies USB peripheral
  * @param  int_bit_mask Interrupt BitMask to be Enable
  * @return None
  */
#define __LL_USB_INTSendToCPU_En(__USB__,  int_bit_mask)        SET_BIT((__USB__)->UCFG1, int_bit_mask)

/**
  * @brief  Disable Interrupt Send to CPU
  * @param  __USB__ Specifies USB peripheral
  * @param  int_bit_mask Interrupt BitMask to be Disable
  * @return None
  */
#define __LL_USB_INTSendToCPU_Dis(__USB__,  int_bit_mask)       CLEAR_BIT((__USB__)->UCFG1, int_bit_mask)


/**
  * @brief  Get SendState
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Reserved
  * @retval 1 Setup
  * @retval 2 Out
  * @retval 3 IN
  */
#define __LL_USB_SendState_Get(__USB__)             (READ_BIT((__USB__)->UCFG2, USB_SEND_STATE_Msk) >> USB_SEND_STATE_Pos)

/**
  * @brief  Judge Is IN Packet or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't IN Packet
  * @retval 1 Is IN Packet
  */
#define __LL_USB_IsInPacket(__USB__)                (READ_BIT((__USB__)->UCFG2, USB_IN_STATE_Msk) >> USB_IN_STATE_Pos)

/**
  * @brief  Judge Is OUT Packet or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't OUT Packet
  * @retval 1 Is OUT Packet
  */
#define __LL_USB_IsOutPacket(__USB__)               (READ_BIT((__USB__)->UCFG2, USB_OUT_STATE_Msk) >> USB_OUT_STATE_Pos)

/**
  * @brief  Judge Is Setup Packet or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Setup Packet
  * @retval 1 Is Setup Packet
  */
#define __LL_USB_IsSetupPacket(__USB__)             (READ_BIT((__USB__)->UCFG2, USB_SETUP_STATE_Msk) >> USB_SETUP_STATE_Pos)

/**
  * @brief  Set Debounce Max
  * @param  __USB__ Specifies USB peripheral
  * @param  debouce debouce to be set
  * @return None
  */
#define __LL_USB_DebouceMax_Set(__USB__,  debouce)  \
        MODIFY_REG((__USB__)->UCFG2, USB_DEBOUCE_MAX_Msk, ((debouce & 0x3FFFUL) << USB_DEBOUCE_MAX_Pos))

/**
  * @brief  Enable Disconnect Interrupt
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Disconn_Int_En(__USB__)            SET_BIT((__USB__)->UCFG2, USB_DISCONN_INT_EN_Msk)

/**
  * @brief  Disable Disconnect Interrupt
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Disconn_Int_Dis(__USB__)           CLEAR_BIT((__USB__)->UCFG2, USB_DISCONN_INT_EN_Msk)

/**
  * @brief  Judge Is Disconnect Interrupt or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Disconnect Interrupt
  * @retval 1 Is Disconnect Interrupt
  */
#define __LL_USB_IsDisconn(__USB__)                 (READ_BIT((__USB__)->UCFG2, USB_DISCONN_INT_STA_Msk) >> USB_DISCONN_INT_STA_Pos)

/**
  * @brief  Clear Disconnect Interrupt Pending
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Disconn_Clr(__USB__)               SET_BIT((__USB__)->UCFG2, USB_DISCONN_INT_STA_Msk)

/**
  * @brief  Enable Connect Interrupt
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Conn_Int_En(__USB__)               SET_BIT((__USB__)->UCFG2, USB_CONN_INT_EN_Msk)

/**
  * @brief  Disable Connect Interrupt
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Conn_Int_Dis(__USB__)              CLEAR_BIT((__USB__)->UCFG2, USB_CONN_INT_EN_Msk)

/**
  * @brief  Judge Is Connect Interrupt or not
  * @param  __USB__ Specifies USB peripheral
  * @retval 0 Isn't Connect Interrupt
  * @retval 1 Is Connect Interrupt
  */
#define __LL_USB_IsConn(__USB__)                    (READ_BIT((__USB__)->UCFG2, USB_CONN_INT_STA_Msk) >> USB_CONN_INT_STA_Pos)

/**
  * @brief  Clear Connect Interrupt Pending
  * @param  __USB__ Specifies USB peripheral
  * @return None
  */
#define __LL_USB_Conn_Clr(__USB__)                  SET_BIT((__USB__)->UCFG2, USB_CONN_INT_STA_Msk)

/**
  * @}
  */


/* Exported types ------------------------------------------------------------*/
/** @defgroup USB_LL_Exported_Types USB LL Exported Types
  * @brief    USB LL Exported Types
  * @{
  */

/**
  * @brief USB Endpoint Number
  */
typedef enum {
    EP_NUM_0 = 0,   /*!< Endpoint Number 0  */
    EP_NUM_1 = 1,   /*!< Endpoint Number 1  */
    EP_NUM_2 = 2,   /*!< Endpoint Number 2  */
    EP_NUMS  = 3,   /*!< Endpoint Numbers   */
} USB_EpNumETypeDef;

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup USB_LL_Exported_Functions
  * @{
  */

/** @addtogroup USB_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_USB_Init(USB_TypeDef *Instance);
LL_StatusETypeDef LL_USB_DeInit(USB_TypeDef *Instance);
void LL_USB_MspInit(USB_TypeDef *Instance);
void LL_USB_MspDeInit(USB_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup USB_LL_Exported_Functions_Group2
  * @{
  */
void LL_USB_CtrlIRQHandler(USB_TypeDef *Instance);
void LL_USB_CtrlSuspendCallback(USB_TypeDef *Instance);
void LL_USB_CtrlResumeCallback(USB_TypeDef *Instance);
void LL_USB_CtrlResetCallback(USB_TypeDef *Instance);
void LL_USB_CtrlSofCallback(USB_TypeDef *Instance);
void LL_USB_CtrlSessEndCallback(USB_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup USB_LL_Exported_Functions_Group3
  * @{
  */
void LL_USB_DetIRQHandler(USB_TypeDef *Instance);
void LL_USB_DetConnectCallback(USB_TypeDef *Instance);
void LL_USB_DetDisonnectCallback(USB_TypeDef *Instance);
/**
  * @}
  */


/** @addtogroup USB_LL_Exported_Functions_Group4
  * @{
  */
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


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
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


#endif /* _TAE32F53XX_LL_USB_H_ */


/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

