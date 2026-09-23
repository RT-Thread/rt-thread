/**
  ******************************************************************************
  * @file    tae32g58xx_ll_xif.h
  * @author  MCD Application Team
  * @brief   Header file for XIF LL module
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
#ifndef _TAE32G58XX_LL_XIF_H_
#define _TAE32G58XX_LL_XIF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "tae32g58xx_ll_def.h"
#ifdef LL_DMA_MODULE_ENABLED
#include "tae32g58xx_ll_dma.h"
#endif


/** @addtogroup TAE32G58xx_LL_Driver
  * @{
  */

/** @addtogroup XIF_LL
  * @{
  */


/* Exported Constants --------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/** @defgroup XIF_LL_Exported_Macros XIF LL Exported Macros
  * @brief    XIF LL Exported Macros
  * @{
  */


/**
  * @brief  XIF Transfer Direction Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  dir Transfer Direction @ref XIF_TsfDirETypeDef
  * @return None
  */
#define __LL_XIF_TsfDir_Set(__XIF__, dir)               \
        MODIFY_REG((__XIF__)->ENABLE, XIF_ENABLE_DIR_Msk, ((dir & 0x1UL) << XIF_ENABLE_DIR_Pos))

/**
  * @brief  XIF Transfer Direction Get
  * @param  __XIF__ Specifies XIF peripheral
  * @return Transfer Direction @ref XIF_TsfDirETypeDef
  */
#define __LL_XIF_TsfDir_Get(__XIF__)                    \
        READ_BIT_SHIFT((__XIF__)->ENABLE, XIF_ENABLE_DIR_Msk, XIF_ENABLE_DIR_Pos)

/**
  * @brief  XIF DMA Transmit Enable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_TxDMA_En(__XIF__)                      SET_BIT((__XIF__)->ENABLE, XIF_ENABLE_TXDEN_Msk)

/**
  * @brief  XIF DMA Transmit Disable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_TxDMA_Dis(__XIF__)                     CLEAR_BIT((__XIF__)->ENABLE, XIF_ENABLE_TXDEN_Msk)

/**
  * @brief  Judge is XIF DMA Transmit Enable or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 isn't XIF DMA Transmit Enable
  * @retval 1 is XIF DMA Transmit Enable
  */
#define __LL_XIF_IsTxDMAEn(__XIF__)                     READ_BIT_SHIFT((__XIF__)->ENABLE, XIF_ENABLE_TXDEN_Msk, XIF_ENABLE_TXDEN_Pos)

/**
  * @brief  Reload Mode Enable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_ReloadMode_En(__XIF__)                 SET_BIT((__XIF__)->ENABLE, XIF_ENABLE_RELOAD_Msk)

/**
  * @brief  Reload Mode Disable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_ReloadMode_Dis(__XIF__)                CLEAR_BIT((__XIF__)->ENABLE, XIF_ENABLE_RELOAD_Msk)

/**
  * @brief  Judge is Reload Mode Enable or not
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_IsReloadModeEn(__XIF__)                READ_BIT_SHIFT((__XIF__)->ENABLE, XIF_ENABLE_RELOAD_Msk, XIF_ENABLE_RELOAD_Pos)

/**
  * @brief  Software Reset
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_Sw_Rst(__XIF__)                        SET_BIT((__XIF__)->ENABLE, XIF_ENABLE_SRST_Msk)

/**
  * @brief  Rx DMA Enable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_RxDMA_En(__XIF__)                      SET_BIT((__XIF__)->ENABLE, XIF_ENABLE_DMAEN_Msk)

/**
  * @brief  Rx DMA Disable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_RxDMA_Dis(__XIF__)                     CLEAR_BIT((__XIF__)->ENABLE, XIF_ENABLE_DMAEN_Msk)

/**
  * @brief  XIF Enable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_En(__XIF__)                            SET_BIT((__XIF__)->ENABLE, XIF_ENABLE_ENABLE_Msk)

/**
  * @brief  XIF Disable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_Dis(__XIF__)                           CLEAR_BIT((__XIF__)->ENABLE, XIF_ENABLE_ENABLE_Msk)


/**
  * @brief  Tx Done Interrupt Enable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_TxDone_INT_En(__XIF__)                 SET_BIT((__XIF__)->CTRL, XIF_CTRL_TXDIE_Msk)

/**
  * @brief  Tx Done Interrupt Disable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_TxDone_INT_Dis(__XIF__)                CLEAR_BIT((__XIF__)->CTRL, XIF_CTRL_TXDIE_Msk)

/**
  * @brief  TXFIFO Empty Interrupt Enable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_TxFIFOEmpty_INT_En(__XIF__)            SET_BIT((__XIF__)->CTRL, XIF_CTRL_TXEIE_Msk)

/**
  * @brief  TXFIFO Empty Interrupt Disable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_TxFIFOEmpty_INT_Dis(__XIF__)           CLEAR_BIT((__XIF__)->CTRL, XIF_CTRL_TXEIE_Msk)

/**
  * @brief  Judge is TXFIFO Empty Interrupt Enable or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 TXFIFO Empty Interrupt Disable
  * @retval 1 TXFIFO Empty Interrupt Enable
  */
#define __LL_XIF_IsTxFIFOEmptyIntEn(__XIF__)            READ_BIT_SHIFT((__XIF__)->CTRL, XIF_CTRL_TXEIE_Msk, XIF_CTRL_TXEIE_Pos)

/**
  * @brief  TXFIFO Empty Watermark Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  thres TXFIFO Empty Watermark 
  * @return None
  */
#define __LL_XIF_TxFIFOEmptyThres_Set(__XIF__, thres)   \
        MODIFY_REG((__XIF__)->CTRL, XIF_CTRL_TXFTLR_Msk, (((thres - 1) & 0x7UL)  << XIF_CTRL_TXFTLR_Pos))

/**
  * @brief  TXFIFO Empty Watermark Get
  * @param  __XIF__ Specifies XIF peripheral
  * @return TXFIFO Empty Watermark
  */
#define __LL_XIF_TxFIFOEmptyThres_Get(__XIF__)          \
        ((READ_BIT_SHIFT((__XIF__)->CTRL, XIF_CTRL_TXFTLR_Msk, XIF_CTRL_TXFTLR_Pos)) + 1)

/**
  * @brief  XIF Delay Chain Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  dly Delay Chain @ref XIF_DlyChainETypeDef
  * @return None
  */
#define __LL_XIF_DlyChain_Set(__XIF__, dly)             \
        MODIFY_REG((__XIF__)->CTRL, XIF_CTRL_DCS_Msk, (((dly) & 0x7UL) << XIF_CTRL_DCS_Pos))

/**
  * @brief  Wait BUSY Timeout Interrupt Enable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_WaitBusyTimeout_INT_En(__XIF__)        SET_BIT((__XIF__)->CTRL, XIF_CTRL_BTOIE_Msk)

/**
  * @brief  Wait BUSY Timeout Interrupt Disable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_WaitBusyTimeout_INT_Dis(__XIF__)       CLEAR_BIT((__XIF__)->CTRL, XIF_CTRL_BTOIE_Msk)

/**
  * @brief  Rx Done Interrupt Enable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_RxDone_INT_En(__XIF__)                 SET_BIT((__XIF__)->CTRL, XIF_CTRL_RXDIE_Msk)

/**
  * @brief  Rx Done Interrupt Disable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_RxDone_INT_Dis(__XIF__)                CLEAR_BIT((__XIF__)->CTRL, XIF_CTRL_RXDIE_Msk)

/**
  * @brief  RxFIFO Overflow Interrupt Enable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_RxFIFOOverflow_INT_En(__XIF__)         SET_BIT((__XIF__)->CTRL, XIF_CTRL_RXOFIE_Msk)

/**
  * @brief  RxFIFO Overflow Interrupt Disable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_RxFIFOOverflow_INT_Dis(__XIF__)        CLEAR_BIT((__XIF__)->CTRL, XIF_CTRL_RXOFIE_Msk)

/**
  * @brief  RxFIFO Full Interrupt Enable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_RxFIFOFull_INT_En(__XIF__)             SET_BIT((__XIF__)->CTRL, XIF_CTRL_RXFIE_Msk)

/**
  * @brief  RxFIFO Full Interrupt Disable
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_RxFIFOFull_INT_Dis(__XIF__)            CLEAR_BIT((__XIF__)->CTRL, XIF_CTRL_RXFIE_Msk)

/**
  * @brief  All Interrupt Enable Status Get
  * @param  __XIF__ Specifies XIF peripheral
  * @return All Interrupt Enable Status
  */
#define __LL_XIF_AllIntEn_Get(__XIF__)                  ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ? \
        (READ_BIT((__XIF__)->CTRL, 0x0500f000UL)) : (READ_BIT((__XIF__)->CTRL, 0x0000f000UL)))



/**
  * @brief  RxFIFO Full Threshold Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  thres RxFIFO Full Threshold
  * @return None
  */
#define __LL_XIF_RxFIFOFullThres_Set(__XIF__, thres)    \
        MODIFY_REG((__XIF__)->CTRL, XIF_CTRL_RXFTLR_Msk, (((thres - 1) & 0x7UL) << XIF_CTRL_RXFTLR_Pos))

/**
  * @brief  RxFIFO Full Threshold Get
  * @param  __XIF__ Specifies XIF peripheral
  * @return RxFIFO Full Threshold
  */
#define __LL_XIF_RxFIFOFullThres_Get(__XIF__)           \
        (READ_BIT_SHIFT((__XIF__)->CTRL, XIF_CTRL_RXFTLR_Msk, XIF_CTRL_RXFTLR_Pos) + 1)

/**
  * @brief  Rx Data Count Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  cnt Rx Data Count
  * @return None
  */
#define __LL_XIF_RxDatCnt_Set(__XIF__, cnt)             \
        MODIFY_REG((__XIF__)->CTRL, XIF_CTRL_DCNT_Msk, (((cnt) & 0xffUL) << XIF_CTRL_DCNT_Pos))

/**
  * @brief  Tx Data Count Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  cnt Rx Data Count
  * @return None
  */
#define __LL_XIF_TxDatCnt_Set(__XIF__, cnt)             \
        MODIFY_REG((__XIF__)->CTRL, XIF_CTRL_DCNT_Msk, (((cnt) & 0xffUL) << XIF_CTRL_DCNT_Pos))

/**
  * @brief  RD High Time Length Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  len RD High Time Length
  * @return None
  */
#define __LL_XIF_RD_HighTimeLen_Set(__XIF__, len)       \
        MODIFY_REG((__XIF__)->TIMING, XIF_TIMING_RDHTIME_Msk, (((len) & 0xffUL) << XIF_TIMING_RDHTIME_Pos))

/**
  * @brief  RD Low Time Length Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  len RD Low Time Length
  * @return None
  */
#define __LL_XIF_RD_LowTimeLen_Set(__XIF__, len)        \
        MODIFY_REG((__XIF__)->TIMING, XIF_TIMING_RDLTIME_Msk, (((len) & 0xffUL) << XIF_TIMING_RDLTIME_Pos))

/**
  * @brief  CONVST Low Time Length Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  len CONVST Low Time Length
  * @return None
  */
#define __LL_XIF_CONVST_LowTimeLen_Set(__XIF__, len)    \
        MODIFY_REG((__XIF__)->TIMING, XIF_TIMING_CONLTIME_Msk, (((len) & 0xffUL) << XIF_TIMING_CONLTIME_Pos))

/**
  * @brief  RESET High Time Length Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  len RESET High Time Length
  * @return None
  */
#define __LL_XIF_RESET_HighTimeLen_Set(__XIF__, len)    \
        MODIFY_REG((__XIF__)->TIMING, XIF_TIMING_RSTTIME_Msk, (((len) & 0xffUL) << XIF_TIMING_RSTTIME_Pos))


/**
  * @brief  BUSY Timeout Set
  * @param  __XIF__ Specifies XIF peripheral
  * @param  time BUSY Timeout Time
  * @return None
  */
#define __LL_XIF_BUSY_Timeout_Set(__XIF__, time)        \
        MODIFY_REG((__XIF__)->TO, XIF_TO_PTOT_Msk, (((time) & 0xffffUL) << XIF_TO_PTOT_Pos))


/**
  * @brief  RxFIFO Data Read
  * @param  __XIF__ Specifies XIF peripheral
  * @return RxFIFO Read Data in uint16_t(half word) Unit
  */
#define __LL_XIF_Dat_Read(__XIF__)                      READ_BIT_SHIFT((__XIF__)->DATA, XIF_DATA_DATA_Msk, XIF_DATA_DATA_Pos)


/**
  * @brief  Judge is TXFIFO Full or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 isn't TXFIFO Full
  * @retval 1 is TXFIFO Full
  */
#define __LL_XIF_IsTxFIFOFull(__XIF__)                  READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_TFF_Msk, XIF_ISR_TFF_Pos)

/**
  * @brief  Judge is TXFIFO Empty or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 isn't TXFIFO Empty
  * @retval 1 is TXFIFO Empty
  */
#define __LL_XIF_IsTxFIFOEmpty(__XIF__)                 READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_TFE_Msk, XIF_ISR_TFE_Pos)

/**
  * @brief  Judge is Tx Done Interrupt Pending or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 isn't Tx Done Interrupt Pending
  * @retval 1 is Tx Done Interrupt Pending
  */
#define __LL_XIF_IsTxDoneIntPnd(__XIF__)                READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_TXDI_Msk, XIF_ISR_TXDI_Pos)

/**
  * @brief  Tx Done Interrupt Pending Clear
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_TxDoneIntPnd_Clr(__XIF__)              WRITE_REG((__XIF__)->ISR, XIF_ISR_TXDI_Msk)

/**
  * @brief  Judge is TXFIFO Empty Interrupt Pending or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 isn't TXFIFO Empty Interrupt Pending
  * @retval 1 is TXFIFO Empty Interrupt Pending
  */
#define __LL_XIF_IsTxFIFOEmptyIntPnd(__XIF__)           READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_TXEI_Msk, XIF_ISR_TXEI_Pos)

/**
  * @brief  TxFIFO Level Get
  * @param  __XIF__ Specifies XIF peripheral
  * @return TxFIFO Level
  */
#define __LL_XIF_TxFIFOLvl_Get(__XIF__)                 READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_TXFLR_Msk, XIF_ISR_TXFLR_Pos)

/**
  * @brief  RxFIFO Level Get
  * @param  __XIF__ Specifies XIF peripheral
  * @return RxFIFO Level
  */
#define __LL_XIF_RxFIFOLevel_Get(__XIF__)               READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_RXFLR_Msk, XIF_ISR_RXFLR_Pos)

/**
  * @brief  Judge is RxFIFO Full or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 RxFIFO isn't Full
  * @retval 1 RxFIFO is Full
  */
#define __LL_XIF_IsRxFIFOFull(__XIF__)                  READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_FF_Msk, XIF_ISR_FF_Pos)

/**
  * @brief  Judge is RxFIFO Empty or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 RxFIFO isn't Empty
  * @retval 1 RxFIFO is Empty
  */
#define __LL_XIF_IsRxFIFOEmpty(__XIF__)                 READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_FE_Msk, XIF_ISR_FE_Pos)

/**
  * @brief  Judge is Wait BUSY Timeout Interrupt Pending or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 isn't Wait BUSY Timeout Interrupt Pending
  * @retval 1 is Wait BUSY Timeout Interrupt Pending
  */
#define __LL_XIF_IsWaitBUSYTimeoutIntPnd(__XIF__)       READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_BTOI_Msk, XIF_ISR_BTOI_Pos)

/**
  * @brief  Wait BUSY Timeout Interrupt Pending Clear
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_WaitBUSYTimeoutIntPnd_Clr(__XIF__)     WRITE_REG((__XIF__)->ISR, XIF_ISR_BTOI_Msk)

/**
  * @brief  Judge is Rx Done Interrupt Pending or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 isn't Rx Done Interrupt Pending
  * @retval 1 is Rx Done Interrupt Pending
  */
#define __LL_XIF_IsRxDoneIntPnd(__XIF__)                READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_RXDI_Msk, XIF_ISR_RXDI_Pos)

/**
  * @brief  Rx Done Interrupt Pending Clear
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_RxDoneIntPnd_Clr(__XIF__)              WRITE_REG((__XIF__)->ISR, XIF_ISR_RXDI_Msk)

/**
  * @brief  Judge is RxFIFO Overflow Interrupt Pending or not
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 isn't RxFIFO Overflow Interrupt Pending
  * @retval 1 is RxFIFO Overflow Interrupt Pending
  */
#define __LL_XIF_IsRxFIFOOverflowIntPnd(__XIF__)        READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_RXOFI_Msk, XIF_ISR_RXOFI_Pos)

/**
  * @brief  RxFIFO Overflow Interrupt Pending Clear
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_RxFIFOOverflowIntPnd_Clr(__XIF__)      WRITE_REG((__XIF__)->ISR, XIF_ISR_RXOFI_Msk)

/**
  * @brief  Judge is RxFIFO Full Interrupt Pending or not (Auto Clear)
  * @param  __XIF__ Specifies XIF peripheral
  * @retval 0 isn't RxFIFO Full Interrupt Pending
  * @retval 1 is RxFIFO Full Interrupt Pending
  */
#define __LL_XIF_IsRxFIFOFullIntPnd(__XIF__)            READ_BIT_SHIFT((__XIF__)->ISR, XIF_ISR_RXFI_Msk, XIF_ISR_RXFI_Pos)

/**
  * @brief  All Interrupt Pending Get
  * @param  __XIF__ Specifies XIF peripheral
  * @return All Interrupt Pending
  */
#define __LL_XIF_AllIntPnd_Get(__XIF__)                 ((__LL_SYSCTRL_ChipDCN_Get(SYSCTRL) >= 3) ? \
        (READ_BIT((__XIF__)->ISR, 0x0005000fUL)) : (READ_BIT((__XIF__)->ISR, 0x0000000fUL)))

/**
  * @brief  All Interrupt Pending Clear
  * @param  __XIF__ Specifies XIF peripheral
  * @return None
  */
#define __LL_XIF_AllIntPnd_Clr(__XIF__)                 WRITE_REG((__XIF__)->ISR, 0xffffffffUL)


/**
  * @brief  TxFIFO Data Write
  * @param  __XIF__ Specifies XIF peripheral
  * @param  dat TxFIFO Write Data in uint16_t(half word) Unit
  * @return None
  */
#define __LL_XIF_TxFIFODat_Write(__XIF__, dat)          \
        MODIFY_REG((__XIF__)->WDATA, XIF_WDATA_WDATA_Msk, (((dat) & 0xffffUL) << XIF_WDATA_WDATA_Pos))

/**
  * @}
  */


/* Exported Types ------------------------------------------------------------*/
/** @defgroup XIF_LL_Exported_Types XIF LL Exported Types
  * @brief    XIF LL Exported Types
  * @{
  */

/**
  * @brief XIF Uer callback function type definition
  */
typedef void (*XIF_UserCallback)(void);

/**
  * @brief XIF Instance Definition
  */
typedef enum {
    XIF_INSTANCE_0 = 0,     /*!< XIF Instance 0         */
    XIF_INSTANCE_NUMS,      /*!< XIF Instance Numbers   */
} XIF_InstanceETypeDef;

/**
  * @brief XIF State definition
  */
typedef enum {
    XIF_STATE_RESET,        /*!< Peripheral not Initialized                 */
    XIF_STATE_READY,        /*!< Peripheral Initialized and ready for use   */
    XIF_STATE_BUSY,         /*!< an internal process is ongoing             */
    XIF_STATE_BUSY_READ,    /*!< Data Read process is ongoing               */
    XIF_STATE_ERROR,        /*!< XIF error state                            */
    XIF_STATE_BUSY_WRITE,   /*!< Data Write process is ongoing              */
} XIF_StateETypeDef;


/**
  * @brief XIF Transfer Direction definition
  */
typedef enum {
    XIF_TSF_DIR_RX = 0,     /*!< Transfer Direction Receive   */
    XIF_TSF_DIR_TX,         /*!< Transfer Direction Transmit  */
} XIF_TsfDirETypeDef;


/**
  * @brief XIF Delay Chain Definition
  */
typedef enum {
    XIF_DLY_CHAIN_NONE = 0, /*!< Delay Chain None       */
    XIF_DLY_CHAIN_1_CLK,    /*!< Delay Chain 1 Clock    */
    XIF_DLY_CHAIN_2_CLK,    /*!< Delay Chain 2 Clocks   */
    XIF_DLY_CHAIN_3_CLK,    /*!< Delay Chain 3 Clocks   */
    XIF_DLY_CHAIN_4_CLK,    /*!< Delay Chain 4 Clocks   */
    XIF_DLY_CHAIN_5_CLK,    /*!< Delay Chain 5 Clocks   */
    XIF_DLY_CHAIN_6_CLK,    /*!< Delay Chain 6 Clocks   */
    XIF_DLY_CHAIN_7_CLK,    /*!< Delay Chain 7 Clocks   */
} XIF_DlyChainETypeDef;

/**
 * @brief XIF IRQ Callback ID definition
 */
typedef enum {
    XIF_RX_CPLT_CB_ID,                      /*!< XIF Rx Completed callback ID       */
    XIF_TX_CPLT_CB_ID,                      /*!< XIF Tx Completed callback ID       */    
    XIF_RX_HALF_CPLT_CB_ID,                 /*!< XIF Rx Half Completed callback ID  */
    XIF_TX_HALF_CPLT_CB_ID,                 /*!< XIF Tx Half Completed callback ID  */    
    XIF_ERROR_CB_ID,                        /*!< XIF Error callback ID              */
} XIF_UserCallbackIdETypeDef;


/**
  * @brief XIF IRQ Callback structure definition
  */
typedef struct __XIF_UserCallbackTypeDef {
    XIF_UserCallback RxCpltCallback;        /*!< XIF Rx Completed callback          */
    XIF_UserCallback RxHalfCpltCallback;    /*!< XIF Rx Half Completed callback     */
    XIF_UserCallback ErrorCallback;         /*!< XIF Error callback                 */
    XIF_UserCallback TxCpltCallback;        /*!< XIF Tx Completed callback          */
    XIF_UserCallback TxHalfCpltCallback;    /*!< XIF Tx Half Completed callback     */
} XIF_UserCallbackTypeDef;

/**
  * @brief XIF LL Config Type Definition
  */
typedef struct __XIF_LLCfgTypeDef {
    uint8_t  rx_fifo_full_thres;    /*!< RxFIFO Full Threshold  */
    uint16_t busy_timeout;          /*!< BUSY Timeout Time      */
    XIF_DlyChainETypeDef dly_chain; /*!< Delay Chain            */
    uint8_t  tx_fifo_empty_thres;   /*!< TxFIFO Empty Threshold */
} XIF_LLCfgTypeDef;

/**
  * @brief XIF User Config Type Definition
  */
typedef struct __XIF_UserCfgTypeDef {
    bool reload_mode_en;                    /*!< Reload Mode Enable             */
    uint8_t ch_per_frame;                   /*!< Channel per Frame              */

    //Timing Config
    uint8_t  reset_high_len;                /*!< RESET Signal High Time Length  */
    uint8_t  convst_low_len;                /*!< CONVST Signal Low Time Length  */
    uint8_t  rd_low_len;                    /*!< RD Signal Low Time Length      */
    uint8_t  rd_high_len;                   /*!< RD Signal High Time Length     */

    XIF_LLCfgTypeDef        *ll_cfg;        /*!< Optional LL Config Pointer     */
    XIF_UserCallbackTypeDef user_callback;  /*!< User Callback                  */
} XIF_UserCfgTypeDef;

/**
  * @}
  */


/* Exported Variables --------------------------------------------------------*/
/* Exported Functions --------------------------------------------------------*/
/** @addtogroup XIF_LL_Exported_Functions
  * @{
  */

/** @addtogroup XIF_LL_Exported_Functions_Group1
  * @{
  */
LL_StatusETypeDef LL_XIF_Init(XIF_TypeDef *Instance, XIF_UserCfgTypeDef *user_cfg);
LL_StatusETypeDef LL_XIF_DeInit(XIF_TypeDef *Instance);
LL_StatusETypeDef LL_XIF_Reset(XIF_TypeDef *Instance);
void LL_XIF_MspInit(XIF_TypeDef *Instance);
void LL_XIF_MspDeInit(XIF_TypeDef *Instance);
LL_StatusETypeDef LL_XIF_RegisterCallback(XIF_TypeDef *Instance, XIF_UserCallbackIdETypeDef CallbackID, XIF_UserCallback pCallback);
LL_StatusETypeDef LL_XIF_UnRegisterCallback(XIF_TypeDef *Instance, XIF_UserCallbackIdETypeDef CallbackID);
/**
  * @}
  */


/** @addtogroup XIF_LL_Exported_Functions_Group2
  * @{
  */
LL_StatusETypeDef LL_XIF_Transmit_CPU(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size, uint32_t timeout);
LL_StatusETypeDef LL_XIF_Receive_CPU(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size, uint32_t timeout);

LL_StatusETypeDef LL_XIF_Transmit_IT(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size);
LL_StatusETypeDef LL_XIF_Receive_IT(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size);

#ifdef LL_DMA_MODULE_ENABLED
LL_StatusETypeDef LL_XIF_Transmit_DMA(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size);
LL_StatusETypeDef LL_XIF_Receive_DMA(XIF_TypeDef *Instance, uint16_t *buf, uint32_t size);
#endif
/**
  * @}
  */


/** @addtogroup XIF_LL_Exported_Functions_Interrupt
  * @{
  */
void LL_XIF_IRQHandler(XIF_TypeDef *Instance);

void LL_XIF_TxEmptyCallback(XIF_TypeDef *Instance);
void LL_XIF_TxDoneCallback(XIF_TypeDef *Instance);
void LL_XIF_RxFullCallback(XIF_TypeDef *Instance);
void LL_XIF_RxOverflowCallback(XIF_TypeDef *Instance);
void LL_XIF_RxDoneCallback(XIF_TypeDef *Instance);
void LL_XIF_WaitBusyTimeoutCallback(XIF_TypeDef *Instance);
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

#endif /* _TAE32G58XX_LL_XIF_H_ */

/************************* (C) COPYRIGHT Tai-Action *****END OF FILE***********/

