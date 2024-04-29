/**
 *******************************************************************************
 * @file  hc32_ll_dma.h
 * @brief This file contains all the functions prototypes of the DMA driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-12-15       CDT             Modify API input param type:u16->u32
                                    Add structure stc_dma_rc_nonseq_init_t
                                    Add API DMA_ReconfigNonSeqStructInit() & DMA_ReconfigNonSeqInit()
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_DMA_H__
#define __HC32_LL_DMA_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"
/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_DMA
 * @{
 */

#if (LL_DMA_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup DMA_Global_Types DMA Global Types
 * @{
 */

/**
 * @brief  DMA basic configuration
 */
typedef struct {
    uint32_t u32IntEn;          /*!< Specifies the DMA interrupt function.
                                    This parameter can be a value of @ref DMA_Int_Config                */
    uint32_t u32SrcAddr;        /*!< Specifies the DMA source address.                                  */
    uint32_t u32DestAddr;       /*!< Specifies the DMA destination address.                             */
    uint32_t u32DataWidth;      /*!< Specifies the DMA transfer data width.
                                    This parameter can be a value of @ref DMA_DataWidth_Sel             */
    uint32_t u32BlockSize;      /*!< Specifies the DMA block size.                                      */
    uint32_t u32TransCount;     /*!< Specifies the DMA transfer count.                                  */
    uint32_t u32SrcAddrInc;     /*!< Specifies the source address increment mode.
                                    This parameter can be a value of @ref DMA_SrcAddr_Incremented_Mode  */
    uint32_t u32DestAddrInc;    /*!< Specifies the destination address increment mode.
                                    This parameter can be a value of @ref DMA_DesAddr_Incremented_Mode  */
} stc_dma_init_t;

/**
 * @brief  DMA repeat mode configuration
 */
typedef struct {
    uint32_t u32Mode;       /*!< Specifies the DMA source repeat function.
                                This parameter can be a value of @ref DMA_Repeat_Config */
    uint32_t u32SrcCount;   /*!< Specifies the DMA source repeat size. */
    uint32_t u32DestCount;  /*!< Specifies the DMA destination repeat size. */
} stc_dma_repeat_init_t;

/**
 * @brief  DMA non-sequence mode configuration
 */
typedef struct {
    uint32_t u32Mode;        /*!< Specifies the DMA source non-sequence function.
                                        This parameter can be a value of @ref DMA_NonSeq_Config */
    uint32_t u32SrcCount;     /*!< Specifies the DMA source non-sequence function count. */
    uint32_t u32SrcOffset;    /*!< Specifies the DMA source non-sequence function offset. */
    uint32_t u32DestCount;    /*!< Specifies the DMA destination non-sequence function count. */
    uint32_t u32DestOffset;   /*!< Specifies the DMA destination non-sequence function offset. */
} stc_dma_nonseq_init_t;

/**
 * @brief  DMA Link List Pointer (LLP) mode configuration
 */
typedef struct {
    uint32_t u32State;      /*!< Specifies the DMA LLP function.
                                This parameter can be a value of @ref DMA_Llp_En */
    uint32_t u32Mode;       /*!< Specifies the DMA LLP auto or wait REQ.
                                This parameter can be a value of @ref DMA_Llp_Mode */
    uint32_t u32Addr;       /*!< Specifies the DMA list pointer address for LLP function. */
} stc_dma_llp_init_t;

/**
 * @brief  DMA re-config function configuration
 */
typedef struct {
    uint32_t u32CountMode;          /*!< Specifies the DMA reconfig function count mode.
                                      This parameter can be a value of @ref DMA_Reconfig_Count_Sel */
    uint32_t u32DestAddrMode;       /*!< Specifies the DMA reconfig function destination address mode.
                                        This parameter can be a value of @ref DMA_Reconfig_DestAddr_Sel */
    uint32_t u32SrcAddrMode;        /*!< Specifies the DMA reconfig function source address mode.
                                        This parameter can be a value of @ref DMA_Reconfig_SrcAddr_Sel */
} stc_dma_reconfig_init_t;

/**
 * @brief  DMA re-config non-sequence mode configuration
 */
typedef struct {
    uint32_t u32Mode;           /*!< Specifies the DMA source non-sequence function.
                                    This parameter can be a value of @ref DMA_NonSeq_Config         */
    uint32_t u32SrcCount;       /*!< Specifies the DMA source non-sequence function count.          */
    uint32_t u32SrcDist;        /*!< Specifies the DMA source non-sequence function distance.       */
    uint32_t u32DestCount;      /*!< Specifies the DMA destination non-sequence function count.     */
    uint32_t u32DestDist;       /*!< Specifies the DMA destination non-sequence function distance.  */
} stc_dma_rc_nonseq_init_t;

/**
 * @brief  Dma LLP(linked list pointer) descriptor structure definition
 */
typedef struct {
    uint32_t SARx;              /*!< LLP source address */
    uint32_t DARx;              /*!< LLP destination address */
    uint32_t DTCTLx;            /*!< LLP transfer count and block size */
    uint32_t RPTx;              /*!< LLP source & destination repeat size */
    uint32_t SNSEQCTLx;         /*!< LLP source non-seq count and offset */
    uint32_t DNSEQCTLx;         /*!< LLP destination non-seq count and offset */
    uint32_t LLPx;              /*!< LLP next list pointer */
    uint32_t CHCTLx;            /*!< LLP channel control */
} stc_dma_llp_descriptor_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DMA_Global_Macros DMA Global Macros
 * @{
 */

/**
 * @defgroup DMA_Channel_selection DMA Channel Position selection
 * @{
 */
#define DMA_CH0                         (0x00U)        /*!< DMA Channel 0 */
#define DMA_CH1                         (0x01U)        /*!< DMA Channel 1 */
#define DMA_CH2                         (0x02U)        /*!< DMA Channel 2 */
#define DMA_CH3                         (0x03U)        /*!< DMA Channel 3 */
#define DMA_CH4                         (0x04U)        /*!< DMA Channel 4 */
#define DMA_CH5                         (0x05U)        /*!< DMA Channel 5 */
#define DMA_CH6                         (0x06U)        /*!< DMA Channel 6 */
#define DMA_CH7                         (0x07U)        /*!< DMA Channel 7 */

/**
 * @}
 */

/**
 * @defgroup DMA_Mx_Channel_selection DMA Multiplex Channel selection
 * @{
 */
#define DMA_MX_CH0                      (0x01UL)        /*!< DMA Channel 0 position */
#define DMA_MX_CH1                      (0x02UL)        /*!< DMA Channel 1 position */
#define DMA_MX_CH_ALL                   (DMA_CHEN_CHEN) /*!< DMA Channel mask position */
#define DMA_MX_CH2                      (0x04UL)        /*!< DMA Channel 2 position */
#define DMA_MX_CH3                      (0x08UL)        /*!< DMA Channel 3 position */
#define DMA_MX_CH4                      (0x10UL)        /*!< DMA Channel 4 position */
#define DMA_MX_CH5                      (0x20UL)        /*!< DMA Channel 5 position */
#define DMA_MX_CH6                      (0x40UL)        /*!< DMA Channel 6 position */
#define DMA_MX_CH7                      (0x80UL)        /*!< DMA Channel 7 position */
/**
 * @}
 */

/**
 * @defgroup DMA_Flag_Request_Err_Sel  DMA request error flag selection
 * @{
 */
#define DMA_FLAG_REQ_ERR_CH0            (DMA_INTSTAT0_REQERR_0) /*!< DMA request error flag CH.0 */
#define DMA_FLAG_REQ_ERR_CH1            (DMA_INTSTAT0_REQERR_1) /*!< DMA request error flag CH.1 */
#define DMA_FLAG_REQ_ERR_CH2            (DMA_INTSTAT0_REQERR_2) /*!< DMA request error flag CH.2 */
#define DMA_FLAG_REQ_ERR_CH3            (DMA_INTSTAT0_REQERR_3) /*!< DMA request error flag CH.3 */
#define DMA_FLAG_REQ_ERR_CH4            (DMA_INTSTAT0_REQERR_4) /*!< DMA request error flag CH.4 */
#define DMA_FLAG_REQ_ERR_CH5            (DMA_INTSTAT0_REQERR_5) /*!< DMA request error flag CH.5 */
#define DMA_FLAG_REQ_ERR_CH6            (DMA_INTSTAT0_REQERR_6) /*!< DMA request error flag CH.6 */
#define DMA_FLAG_REQ_ERR_CH7            (DMA_INTSTAT0_REQERR_7) /*!< DMA request error flag CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_Flag_Trans_Err_Sel  DMA transfer error flag selection
 * @{
 */
#define DMA_FLAG_TRANS_ERR_CH0          (DMA_INTSTAT0_TRNERR_0) /*!< DMA transfer error flag CH.0 */
#define DMA_FLAG_TRANS_ERR_CH1          (DMA_INTSTAT0_TRNERR_1) /*!< DMA transfer error flag CH.1 */
#define DMA_FLAG_TRANS_ERR_CH2          (DMA_INTSTAT0_TRNERR_2) /*!< DMA transfer error flag CH.2 */
#define DMA_FLAG_TRANS_ERR_CH3          (DMA_INTSTAT0_TRNERR_3) /*!< DMA transfer error flag CH.3 */
#define DMA_FLAG_TRANS_ERR_CH4          (DMA_INTSTAT0_TRNERR_4) /*!< DMA transfer error flag CH.4 */
#define DMA_FLAG_TRANS_ERR_CH5          (DMA_INTSTAT0_TRNERR_5) /*!< DMA transfer error flag CH.5 */
#define DMA_FLAG_TRANS_ERR_CH6          (DMA_INTSTAT0_TRNERR_6) /*!< DMA transfer error flag CH.6 */
#define DMA_FLAG_TRANS_ERR_CH7          (DMA_INTSTAT0_TRNERR_7) /*!< DMA transfer error flag CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_Flag_Btc_Sel  DMA block transfer completed flag selection
 * @{
 */
#define DMA_FLAG_BTC_CH0                (DMA_INTSTAT1_BTC_0)    /*!< DMA block transfer completed flag CH.0 */
#define DMA_FLAG_BTC_CH1                (DMA_INTSTAT1_BTC_1)    /*!< DMA block transfer completed flag CH.1 */
#define DMA_FLAG_BTC_CH2                (DMA_INTSTAT1_BTC_2)    /*!< DMA block transfer completed flag CH.2 */
#define DMA_FLAG_BTC_CH3                (DMA_INTSTAT1_BTC_3)    /*!< DMA block transfer completed flag CH.3 */
#define DMA_FLAG_BTC_CH4                (DMA_INTSTAT1_BTC_4)    /*!< DMA block transfer completed flag CH.4 */
#define DMA_FLAG_BTC_CH5                (DMA_INTSTAT1_BTC_5)    /*!< DMA block transfer completed flag CH.5 */
#define DMA_FLAG_BTC_CH6                (DMA_INTSTAT1_BTC_6)    /*!< DMA block transfer completed flag CH.6 */
#define DMA_FLAG_BTC_CH7                (DMA_INTSTAT1_BTC_7)    /*!< DMA block transfer completed flag CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_Flag_Tc_Sel  DMA transfer completed flag selection
 * @{
 */
#define DMA_FLAG_TC_CH0                 (DMA_INTSTAT1_TC_0)     /*!< DMA transfer completed flag CH.0 */
#define DMA_FLAG_TC_CH1                 (DMA_INTSTAT1_TC_1)     /*!< DMA transfer completed flag CH.1 */
#define DMA_FLAG_TC_CH2                 (DMA_INTSTAT1_TC_2)     /*!< DMA transfer completed flag CH.2 */
#define DMA_FLAG_TC_CH3                 (DMA_INTSTAT1_TC_3)     /*!< DMA transfer completed flag CH.3 */
#define DMA_FLAG_TC_CH4                 (DMA_INTSTAT1_TC_4)     /*!< DMA transfer completed flag CH.4 */
#define DMA_FLAG_TC_CH5                 (DMA_INTSTAT1_TC_5)     /*!< DMA transfer completed flag CH.5 */
#define DMA_FLAG_TC_CH6                 (DMA_INTSTAT1_TC_6)     /*!< DMA transfer completed flag CH.6 */
#define DMA_FLAG_TC_CH7                 (DMA_INTSTAT1_TC_7)     /*!< DMA transfer completed flag CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_Int_Request_Err_Sel  DMA request error interrupt selection
 * @{
 */
#define DMA_INT_REQ_ERR_CH0             (DMA_INTMASK0_MSKREQERR_0) /*!< DMA request error interrupt CH.0 */
#define DMA_INT_REQ_ERR_CH1             (DMA_INTMASK0_MSKREQERR_1) /*!< DMA request error interrupt CH.1 */
#define DMA_INT_REQ_ERR_CH2             (DMA_INTMASK0_MSKREQERR_2) /*!< DMA request error interrupt CH.2 */
#define DMA_INT_REQ_ERR_CH3             (DMA_INTMASK0_MSKREQERR_3) /*!< DMA request error interrupt CH.3 */
#define DMA_INT_REQ_ERR_CH4             (DMA_INTMASK0_MSKREQERR_4) /*!< DMA request error interrupt CH.4 */
#define DMA_INT_REQ_ERR_CH5             (DMA_INTMASK0_MSKREQERR_5) /*!< DMA request error interrupt CH.5 */
#define DMA_INT_REQ_ERR_CH6             (DMA_INTMASK0_MSKREQERR_6) /*!< DMA request error interrupt CH.6 */
#define DMA_INT_REQ_ERR_CH7             (DMA_INTMASK0_MSKREQERR_7) /*!< DMA request error interrupt CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_Int_Trans_Err_Sel  DMA transfer error interrupt selection
 * @{
 */
#define DMA_INT_TRANS_ERR_CH0           (DMA_INTMASK0_MSKTRNERR_0) /*!< DMA transfer error interrupt CH.0 */
#define DMA_INT_TRANS_ERR_CH1           (DMA_INTMASK0_MSKTRNERR_1) /*!< DMA transfer error interrupt CH.1 */
#define DMA_INT_TRANS_ERR_CH2           (DMA_INTMASK0_MSKTRNERR_2) /*!< DMA transfer error interrupt CH.2 */
#define DMA_INT_TRANS_ERR_CH3           (DMA_INTMASK0_MSKTRNERR_3) /*!< DMA transfer error interrupt CH.3 */
#define DMA_INT_TRANS_ERR_CH4           (DMA_INTMASK0_MSKTRNERR_4) /*!< DMA transfer error interrupt CH.4 */
#define DMA_INT_TRANS_ERR_CH5           (DMA_INTMASK0_MSKTRNERR_5) /*!< DMA transfer error interrupt CH.5 */
#define DMA_INT_TRANS_ERR_CH6           (DMA_INTMASK0_MSKTRNERR_6) /*!< DMA transfer error interrupt CH.6 */
#define DMA_INT_TRANS_ERR_CH7           (DMA_INTMASK0_MSKTRNERR_7) /*!< DMA transfer error interrupt CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_Int_Btc_Sel  DMA block transfer completed interrupt selection
 * @{
 */
#define DMA_INT_BTC_CH0                 (DMA_INTMASK1_MSKBTC_0)    /*!< DMA block transfer completed interrupt CH.0 */
#define DMA_INT_BTC_CH1                 (DMA_INTMASK1_MSKBTC_1)    /*!< DMA block transfer completed interrupt CH.1 */
#define DMA_INT_BTC_CH2                 (DMA_INTMASK1_MSKBTC_2)    /*!< DMA block transfer completed interrupt CH.2 */
#define DMA_INT_BTC_CH3                 (DMA_INTMASK1_MSKBTC_3)    /*!< DMA block transfer completed interrupt CH.3 */
#define DMA_INT_BTC_CH4                 (DMA_INTMASK1_MSKBTC_4)    /*!< DMA block transfer completed interrupt CH.4 */
#define DMA_INT_BTC_CH5                 (DMA_INTMASK1_MSKBTC_5)    /*!< DMA block transfer completed interrupt CH.5 */
#define DMA_INT_BTC_CH6                 (DMA_INTMASK1_MSKBTC_6)    /*!< DMA block transfer completed interrupt CH.6 */
#define DMA_INT_BTC_CH7                 (DMA_INTMASK1_MSKBTC_7)    /*!< DMA block transfer completed interrupt CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_Int_Tc_Sel  DMA transfer completed interrupt selection
 * @{
 */
#define DMA_INT_TC_CH0                  (DMA_INTMASK1_MSKTC_0)     /*!< DMA transfer completed interrupt CH.0 */
#define DMA_INT_TC_CH1                  (DMA_INTMASK1_MSKTC_1)     /*!< DMA transfer completed interrupt CH.1 */
#define DMA_INT_TC_CH2                  (DMA_INTMASK1_MSKTC_2)     /*!< DMA transfer completed interrupt CH.2 */
#define DMA_INT_TC_CH3                  (DMA_INTMASK1_MSKTC_3)     /*!< DMA transfer completed interrupt CH.3 */
#define DMA_INT_TC_CH4                  (DMA_INTMASK1_MSKTC_4)     /*!< DMA transfer completed interrupt CH.4 */
#define DMA_INT_TC_CH5                  (DMA_INTMASK1_MSKTC_5)     /*!< DMA transfer completed interrupt CH.5 */
#define DMA_INT_TC_CH6                  (DMA_INTMASK1_MSKTC_6)     /*!< DMA transfer completed interrupt CH.6 */
#define DMA_INT_TC_CH7                  (DMA_INTMASK1_MSKTC_7)     /*!< DMA transfer completed interrupt CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_FlagMsk_Sel DMA flag mask selection
 * @{
 */
#define DMA_FLAG_ERR_MASK               (DMA_INTSTAT0_TRNERR | DMA_INTSTAT0_REQERR)   /*!< DMA error flag mask */
#define DMA_FLAG_TRANS_MASK             (DMA_INTSTAT1_TC | DMA_INTSTAT1_BTC)          /*!< DMA transfer flag mask */
/**
 * @}
 */

/**
 * @defgroup DMA_IntMsk_Sel DMA interrupt mask selection
 * @{
 */
#define DMA_INT_ERR_MASK                (DMA_INTMASK0_MSKREQERR | DMA_INTMASK0_MSKTRNERR)   /*!< DMA error interrupt mask */
#define DMA_INT_TRANS_MASK              (DMA_INTMASK1_MSKTC | DMA_INTMASK1_MSKBTC)          /*!< DMA transfer interrupt mask */
/**
 * @}
 */

/**
 * @defgroup DMA_Req_Status_Sel DMA request status
 * @{
 */
#define DMA_STAT_REQ_RECONFIG           (DMA_REQSTAT_RCFGREQ)                       /*!< DMA request from reconfig */
#define DMA_STAT_REQ_CH0                (DMA_REQSTAT_CHREQ_0)                       /*!< DMA request from CH.0 */
#define DMA_STAT_REQ_CH1                (DMA_REQSTAT_CHREQ_1)                       /*!< DMA request from CH.1 */
#define DMA_STAT_REQ_CH2                (DMA_REQSTAT_CHREQ_2)                       /*!< DMA request from CH.2 */
#define DMA_STAT_REQ_CH3                (DMA_REQSTAT_CHREQ_3)                       /*!< DMA request from CH.3 */
#define DMA_STAT_REQ_CH4                (DMA_REQSTAT_CHREQ_4)                       /*!< DMA request from CH.4 */
#define DMA_STAT_REQ_CH5                (DMA_REQSTAT_CHREQ_5)                       /*!< DMA request from CH.5 */
#define DMA_STAT_REQ_CH6                (DMA_REQSTAT_CHREQ_6)                       /*!< DMA request from CH.6 */
#define DMA_STAT_REQ_CH7                (DMA_REQSTAT_CHREQ_7)                       /*!< DMA request from CH.7 */

#define DMA_STAT_REQ_MASK               (DMA_REQSTAT_CHREQ | DMA_REQSTAT_RCFGREQ)   /*!< DMA request mask */
/**
 * @}
 */

/**
 * @defgroup DMA_Trans_Status_Sel DMA transfer status
 * @{
 */
#define DMA_STAT_TRANS_CH0              (DMA_CHSTAT_CHACT_0)    /*!< DMA transfer status of CH.0 */
#define DMA_STAT_TRANS_CH1              (DMA_CHSTAT_CHACT_1)    /*!< DMA transfer status of CH.1 */
#define DMA_STAT_TRANS_CH2              (DMA_CHSTAT_CHACT_2)    /*!< DMA transfer status of CH.2 */
#define DMA_STAT_TRANS_CH3              (DMA_CHSTAT_CHACT_3)    /*!< DMA transfer status of CH.3 */
#define DMA_STAT_TRANS_CH4              (DMA_CHSTAT_CHACT_4)    /*!< DMA transfer status of CH.4 */
#define DMA_STAT_TRANS_CH5              (DMA_CHSTAT_CHACT_5)    /*!< DMA transfer status of CH.5 */
#define DMA_STAT_TRANS_CH6              (DMA_CHSTAT_CHACT_6)    /*!< DMA transfer status of CH.6 */
#define DMA_STAT_TRANS_CH7              (DMA_CHSTAT_CHACT_7)    /*!< DMA transfer status of CH.7 */
#define DMA_STAT_TRANS_DMA              (DMA_CHSTAT_DMAACT)     /*!< DMA transfer status of the DMA */
#define DMA_STAT_TRANS_RECONFIG         (DMA_CHSTAT_RCFGACT)    /*!< DMA reconfig status */

#define DMA_STAT_TRANS_MASK             (DMA_CHSTAT_DMAACT | DMA_CHSTAT_CHACT | DMA_CHSTAT_RCFGACT)
/**
 * @}
 */

/**
 * @defgroup DMA_DataWidth_Sel DMA transfer data width
 * @{
 */
#define DMA_DATAWIDTH_8BIT              (0x00000000UL)          /*!< DMA transfer data width 8bit  */
#define DMA_DATAWIDTH_16BIT             (DMA_CHCTL_HSIZE_0)     /*!< DMA transfer data width 16bit */
#define DMA_DATAWIDTH_32BIT             (DMA_CHCTL_HSIZE_1)     /*!< DMA transfer data width 32bit */

/**
 * @}
 */

/**
 * @defgroup DMA_Llp_En DMA LLP(linked list pinter) enable or disable
 * @{
 */
#define DMA_LLP_DISABLE                 (0x00000000UL)          /*!< DMA linked list pinter disable    */
#define DMA_LLP_ENABLE                  (DMA_CHCTL_LLPEN)       /*!< DMA linked list pinter enable     */
/**
 * @}
 */

/**
 * @defgroup DMA_Llp_Mode DMA linked list pinter mode while transferring complete
 * @{
 */
#define DMA_LLP_WAIT                    (0x00000000UL)          /*!< DMA Llp wait next request while transferring complete */
#define DMA_LLP_RUN                     (DMA_CHCTL_LLPRUN)      /*!< DMA Llp run right now while transferring complete     */
/**
 * @}
 */

/**
 * @defgroup DMA_SrcAddr_Incremented_Mode DMA source address increment mode
 * @{
 */
#define DMA_SRC_ADDR_FIX                (0x00000000UL)          /*!< DMA source address fix             */
#define DMA_SRC_ADDR_INC                (DMA_CHCTL_SINC_0)      /*!< DMA source address increment       */
#define DMA_SRC_ADDR_DEC                (DMA_CHCTL_SINC_1)      /*!< DMA source address decrement       */
/**
 * @}
 */

/**
 * @defgroup DMA_DesAddr_Incremented_Mode DMA destination address increment mode
 * @{
 */
#define DMA_DEST_ADDR_FIX               (0x00000000UL)          /*!< DMA destination address fix        */
#define DMA_DEST_ADDR_INC               (DMA_CHCTL_DINC_0)      /*!< DMA destination address increment  */
#define DMA_DEST_ADDR_DEC               (DMA_CHCTL_DINC_1)      /*!< DMA destination address decrement  */
/**
 * @}
 */

/**
 * @defgroup DMA_Int_Config DMA interrupt function config
 * @{
 */
#define DMA_INT_ENABLE                  (DMA_CHCTL_IE)          /*!< DMA interrupt enable */
#define DMA_INT_DISABLE                 (0x00000000UL)          /*!< DMA interrupt disable */
/**
 * @}
 */

/**
 * @defgroup DMA_Repeat_Config DMA repeat mode function config
 * @{
 */
#define DMA_RPT_NONE                    (0x00000000UL)                                  /*!< DMA repeat disable */
#define DMA_RPT_SRC                     (DMA_CHCTL_SRPTEN)                              /*!< DMA source repeat enable */
#define DMA_RPT_DEST                    (DMA_CHCTL_DRPTEN)                              /*!< DMA destination repeat enable */
#define DMA_RPT_BOTH                    (DMA_CHCTL_SRPTEN | DMA_CHCTL_DRPTEN)           /*!< DMA source & destination repeat enable */

/**
 * @}
 */

/**
 * @defgroup DMA_NonSeq_Config DMA non-sequence mode function config
 * @{
 */
#define DMA_NON_SEQ_NONE                (0x00000000UL)                                  /*!< DMA non-sequence disable */
#define DMA_NON_SEQ_SRC                 (DMA_CHCTL_SNSEQEN)                             /*!< DMA source non-sequence enable */
#define DMA_NON_SEQ_DEST                (DMA_CHCTL_DNSEQEN)                             /*!< DMA destination non-sequence enable */
#define DMA_NON_SEQ_BOTH                (DMA_CHCTL_SNSEQEN | DMA_CHCTL_DNSEQEN)         /*!< DMA source & destination non-sequence enable */

/**
 * @}
 */

/**
 * @defgroup DMA_Reconfig_Count_Sel DMA reconfig count mode selection
 * @{
 */
#define DMA_RC_CNT_KEEP                 (0x00000000UL)          /*!< Keep the original counting method */
#define DMA_RC_CNT_SRC                  (DMA_RCFGCTL_CNTMD_0)   /*!< Use source address counting method */
#define DMA_RC_CNT_DEST                 (DMA_RCFGCTL_CNTMD_1)   /*!< Use destination address counting method */
/**
 * @}
 */

/**
 * @defgroup DMA_Reconfig_DestAddr_Sel DMA reconfig destination address mode selection
 * @{
 */
#define DMA_RC_DEST_ADDR_KEEP           (0x00000000UL)          /*!< Destination address Keep the original mode */
#define DMA_RC_DEST_ADDR_NS             (DMA_RCFGCTL_DARMD_0)   /*!< Destination address non-sequence */
#define DMA_RC_DEST_ADDR_RPT            (DMA_RCFGCTL_DARMD_1)   /*!< Destination address repeat */
/**
 * @}
 */

/**
 * @defgroup DMA_Reconfig_SrcAddr_Sel DMA reconfig source address mode selection
 * @{
 */
#define DMA_RC_SRC_ADDR_KEEP            (0x00000000UL)          /*!< Source address Keep the original mode */
#define DMA_RC_SRC_ADDR_NS              (DMA_RCFGCTL_SARMD_0)   /*!< Source address non-sequence */
#define DMA_RC_SRC_ADDR_RPT             (DMA_RCFGCTL_SARMD_1)   /*!< Source address repeat */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup DMA_Global_Functions
 * @{
 */
void DMA_Cmd(CM_DMA_TypeDef *DMAx, en_functional_state_t enNewState);

void DMA_ErrIntCmd(CM_DMA_TypeDef *DMAx, uint32_t u32ErrInt, en_functional_state_t enNewState);
en_flag_status_t DMA_GetErrStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32Flag);
void DMA_ClearErrStatus(CM_DMA_TypeDef *DMAx, uint32_t u32Flag);

void DMA_TransCompleteIntCmd(CM_DMA_TypeDef *DMAx, uint32_t u32TransCompleteInt, en_functional_state_t enNewState);
en_flag_status_t DMA_GetTransCompleteStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32Flag);
void DMA_ClearTransCompleteStatus(CM_DMA_TypeDef *DMAx, uint32_t u32Flag);

void DMA_MxChCmd(CM_DMA_TypeDef *DMAx, uint8_t u8MxCh, en_functional_state_t enNewState);
int32_t DMA_ChCmd(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, en_functional_state_t enNewState);

en_flag_status_t DMA_GetRequestStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32Status);
en_flag_status_t DMA_GetTransStatus(const CM_DMA_TypeDef *DMAx, uint32_t u32Status);

int32_t DMA_SetSrcAddr(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Addr);
int32_t DMA_SetDestAddr(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Addr);
int32_t DMA_SetTransCount(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint16_t u16Count);
int32_t DMA_SetBlockSize(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint16_t u16Size);
int32_t DMA_SetDataWidth(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32DataWidth);

int32_t DMA_SetSrcRepeatSize(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Size);
int32_t DMA_SetDestRepeatSize(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Size);
int32_t DMA_SetNonSeqSrcCount(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Count);
int32_t DMA_SetNonSeqDestCount(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Count);
int32_t DMA_SetNonSeqSrcOffset(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Offset);
int32_t DMA_SetNonSeqDestOffset(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Offset);

void DMA_SetLlpAddr(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Addr);

int32_t DMA_StructInit(stc_dma_init_t *pstcDmaInit);
int32_t DMA_Init(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_init_t *pstcDmaInit);
void DMA_DeInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
int32_t DMA_UnitDeInit(CM_DMA_TypeDef *DMAx);

int32_t DMA_RepeatStructInit(stc_dma_repeat_init_t *pstcDmaRepeatInit);
int32_t DMA_RepeatInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_repeat_init_t *pstcDmaRepeatInit);

int32_t DMA_NonSeqStructInit(stc_dma_nonseq_init_t *pstcDmaNonSeqInit);
int32_t DMA_NonSeqInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_nonseq_init_t *pstcDmaNonSeqInit);

int32_t DMA_LlpStructInit(stc_dma_llp_init_t *pstcDmaLlpInit);
int32_t DMA_LlpInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_llp_init_t *pstcDmaLlpInit);

void DMA_LlpCmd(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, en_functional_state_t enNewState);

int32_t DMA_ReconfigStructInit(stc_dma_reconfig_init_t *pstcDmaRCInit);
int32_t DMA_ReconfigInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_reconfig_init_t *pstcDmaRCInit);
void DMA_ReconfigCmd(CM_DMA_TypeDef *DMAx, en_functional_state_t enNewState);
void DMA_ReconfigLlpCmd(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, en_functional_state_t enNewState);
int32_t DMA_ReconfigNonSeqStructInit(stc_dma_rc_nonseq_init_t *pstcDmaRcNonSeqInit);
int32_t DMA_ReconfigNonSeqInit(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_rc_nonseq_init_t *pstcDmaRcNonSeqInit);

uint32_t DMA_GetSrcAddr(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetDestAddr(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetTransCount(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetBlockSize(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetSrcRepeatSize(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetDestRepeatSize(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetNonSeqSrcCount(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetNonSeqDestCount(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetNonSeqSrcOffset(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetNonSeqDestOffset(const CM_DMA_TypeDef *DMAx, uint8_t u8Ch);
void DMA_AHB_HProtBufCacheCmd(CM_DMA_TypeDef *DMAx, uint8_t u8Ch, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* LL_DMA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_DMA_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
