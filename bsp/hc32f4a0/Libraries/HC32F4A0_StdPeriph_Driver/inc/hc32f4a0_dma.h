/**
 *******************************************************************************
 * @file  hc32f4a0_dma.h
 * @brief This file contains all the functions prototypes of the DMA driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_DMA_H__
#define __HC32F4A0_DMA_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_DMA
 * @{
 */

#if (DDL_DMA_ENABLE == DDL_ON)

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
typedef struct
{
    uint32_t u32IntEn;          /*!< Specifies the DMA interrupt function.
                                    This parameter can be a value of @ref DMA_Int_Config                */

    uint32_t u32SrcAddr;        /*!< Specifies the DMA source address.                                  */

    uint32_t u32DestAddr;       /*!< Specifies the DMA destination address.                             */

    uint32_t u32DataWidth;      /*!< Specifies the DMA transfer data width.
                                    This parameter can be a value of @ref DMA_DataWidth_Sel             */

    uint32_t u32BlockSize;      /*!< Specifies the DMA block size.                                      */

    uint32_t u32TransCnt;       /*!< Specifies the DMA transfer count.                                  */

    uint32_t u32SrcInc;         /*!< Specifies the source address increment mode.
                                    This parameter can be a value of @ref DMA_SrcAddr_Incremented_Mode  */

    uint32_t u32DestInc;        /*!< Specifies the destination address increment mode.
                                    This parameter can be a value of @ref DMA_DesAddr_Incremented_Mode  */

} stc_dma_init_t;

/**
 * @brief  DMA repeat mode configuration
 */
typedef struct
{
    uint32_t u32SrcRptEn;       /*!< Specifies the DMA source repeat function.
                                    This parameter can be a value of @ref DMA_Repeat_Config */

    uint32_t u32SrcRptSize;     /*!< Specifies the DMA source repeat size. */

    uint32_t u32DestRptEn;      /*!< Specifies the DMA destination repeat function.
                                    This parameter can be a value of @ref DMA_Repeat_Config */

    uint32_t u32DestRptSize;    /*!< Specifies the DMA destination repeat size. */

} stc_dma_rpt_init_t;

/**
 * @brief  DMA non-sequence mode configuration
 */
typedef struct
{
    uint32_t u32SrcNonSeqEn;    /*!< Specifies the DMA source non-sequence function.
                                    This parameter can be a value of @ref DMA_NonSeq_Config */

    uint32_t u32SrcNonSeqCnt;   /*!< Specifies the DMA source non-sequence function count. */

    uint32_t u32SrcNonSeqOfs;   /*!< Specifies the DMA source non-sequence function offset. */

    uint32_t u32DestNonSeqEn;   /*!< Specifies the DMA destination non-sequence function.
                                    This parameter can be a value of @ref DMA_NonSeq_Config */

    uint32_t u32DestNonSeqCnt;  /*!< Specifies the DMA destination non-sequence function count. */

    uint32_t u32DestNonSeqOfs;  /*!< Specifies the DMA destination non-sequence function offset. */

} stc_dma_nonseq_init_t;

/**
 * @brief  DMA Link List Pointer (LLP) mode configuration
 */
typedef struct
{
    uint32_t u32LlpEn;          /*!< Specifies the DMA LLP function.
                                    This parameter can be a value of @ref DMA_Llp_En */

    uint32_t u32LlpRun;         /*!< Specifies the DMA LLP auto or wait REQ.
                                    This parameter can be a value of @ref DMA_Llp_Mode */

    uint32_t u32LlpAddr;        /*!< Specifies the DMA list pointer address for LLP function. */

} stc_dma_llp_init_t;

/**
 * @brief  DMA re-config function configuration
 */
typedef struct
{
    uint32_t u32CntMode;        /*!< Specifies the DMA reconfig function count mode.
                                    This parameter can be a value of @ref DMA_ReConfig_Cnt_Sel */

    uint32_t u32DestAddrMode;   /*!< Specifies the DMA reconfig function destination address mode.
                                    This parameter can be a value of @ref DMA_ReConfig_DestAddr_Sel */

    uint32_t u32SrcAddrMode;    /*!< Specifies the DMA reconfig function source address mode.
                                    This parameter can be a value of @ref DMA_ReConfig_SrcAddr_Sel */

} stc_dma_reconfig_init_t;

/**
 * @brief  Dma LLP(linked list pointer) descriptor structure definition
 */
typedef struct
{
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
#define DMA_CH0                     (0x00U)        /*!< DMA Channel 0 */
#define DMA_CH1                     (0x01U)        /*!< DMA Channel 1 */
#define DMA_CH2                     (0x02U)        /*!< DMA Channel 2 */
#define DMA_CH3                     (0x03U)        /*!< DMA Channel 3 */
#define DMA_CH4                     (0x04U)        /*!< DMA Channel 4 */
#define DMA_CH5                     (0x05U)        /*!< DMA Channel 5 */
#define DMA_CH6                     (0x06U)        /*!< DMA Channel 6 */
#define DMA_CH7                     (0x07U)        /*!< DMA Channel 7 */
/**
 * @}
 */

/**
 * @defgroup DMA_Mx_Channel_selection DMA Multiplex Channel selection
 * @{
 */
#define DMA_MX_CH0                  (0x01UL)      /*!< DMA Channel 0 position */
#define DMA_MX_CH1                  (0x02UL)      /*!< DMA Channel 1 position */
#define DMA_MX_CH2                  (0x04UL)      /*!< DMA Channel 2 position */
#define DMA_MX_CH3                  (0x08UL)      /*!< DMA Channel 3 position */
#define DMA_MX_CH4                  (0x10UL)      /*!< DMA Channel 4 position */
#define DMA_MX_CH5                  (0x20UL)      /*!< DMA Channel 5 position */
#define DMA_MX_CH6                  (0x40UL)      /*!< DMA Channel 6 position */
#define DMA_MX_CH7                  (0x80UL)      /*!< DMA Channel 7 position */
#define DMA_MX_CH_ALL               (0xFFUL)      /*!< DMA Channel mask position */
/**
 * @}
 */

/**
 * @defgroup DMA_ReqErrIrq_Sel DMA request error interrupt selection
 * @{
 */
#define DMA_REQ_ERR_CH0             (DMA_INTSTAT0_REQERR_0) /*!< DMA request error interrupt CH.0 */
#define DMA_REQ_ERR_CH1             (DMA_INTSTAT0_REQERR_1) /*!< DMA request error interrupt CH.1 */
#define DMA_REQ_ERR_CH2             (DMA_INTSTAT0_REQERR_2) /*!< DMA request error interrupt CH.2 */
#define DMA_REQ_ERR_CH3             (DMA_INTSTAT0_REQERR_3) /*!< DMA request error interrupt CH.3 */
#define DMA_REQ_ERR_CH4             (DMA_INTSTAT0_REQERR_4) /*!< DMA request error interrupt CH.4 */
#define DMA_REQ_ERR_CH5             (DMA_INTSTAT0_REQERR_5) /*!< DMA request error interrupt CH.5 */
#define DMA_REQ_ERR_CH6             (DMA_INTSTAT0_REQERR_6) /*!< DMA request error interrupt CH.6 */
#define DMA_REQ_ERR_CH7             (DMA_INTSTAT0_REQERR_7) /*!< DMA request error interrupt CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_TransErrIrq_Sel DMA transfer error interrupt selection
 * @{
 */
#define DMA_TRANS_ERR_CH0           (DMA_INTSTAT0_TRNERR_0) /*!< DMA transfer error interrupt CH.0 */
#define DMA_TRANS_ERR_CH1           (DMA_INTSTAT0_TRNERR_1) /*!< DMA transfer error interrupt CH.1 */
#define DMA_TRANS_ERR_CH2           (DMA_INTSTAT0_TRNERR_2) /*!< DMA transfer error interrupt CH.2 */
#define DMA_TRANS_ERR_CH3           (DMA_INTSTAT0_TRNERR_3) /*!< DMA transfer error interrupt CH.3 */
#define DMA_TRANS_ERR_CH4           (DMA_INTSTAT0_TRNERR_4) /*!< DMA transfer error interrupt CH.4 */
#define DMA_TRANS_ERR_CH5           (DMA_INTSTAT0_TRNERR_5) /*!< DMA transfer error interrupt CH.5 */
#define DMA_TRANS_ERR_CH6           (DMA_INTSTAT0_TRNERR_6) /*!< DMA transfer error interrupt CH.6 */
#define DMA_TRANS_ERR_CH7           (DMA_INTSTAT0_TRNERR_7) /*!< DMA transfer error interrupt CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_BtcIrq_Sel DMA block transfer completed interrupt selection
 * @{
 */
#define DMA_BTC_INT_CH0             (DMA_INTSTAT1_BTC_0)    /*!< DMA block transfer completed interrupt CH.0 */
#define DMA_BTC_INT_CH1             (DMA_INTSTAT1_BTC_1)    /*!< DMA block transfer completed interrupt CH.1 */
#define DMA_BTC_INT_CH2             (DMA_INTSTAT1_BTC_2)    /*!< DMA block transfer completed interrupt CH.2 */
#define DMA_BTC_INT_CH3             (DMA_INTSTAT1_BTC_3)    /*!< DMA block transfer completed interrupt CH.3 */
#define DMA_BTC_INT_CH4             (DMA_INTSTAT1_BTC_4)    /*!< DMA block transfer completed interrupt CH.4 */
#define DMA_BTC_INT_CH5             (DMA_INTSTAT1_BTC_5)    /*!< DMA block transfer completed interrupt CH.5 */
#define DMA_BTC_INT_CH6             (DMA_INTSTAT1_BTC_6)    /*!< DMA block transfer completed interrupt CH.6 */
#define DMA_BTC_INT_CH7             (DMA_INTSTAT1_BTC_7)    /*!< DMA block transfer completed interrupt CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_TcIrq_Sel DMA transfer completed interrupt selection
 * @{
 */
#define DMA_TC_INT_CH0              (DMA_INTSTAT1_TC_0)     /*!< DMA transfer completed interrupt CH.0 */
#define DMA_TC_INT_CH1              (DMA_INTSTAT1_TC_1)     /*!< DMA transfer completed interrupt CH.1 */
#define DMA_TC_INT_CH2              (DMA_INTSTAT1_TC_2)     /*!< DMA transfer completed interrupt CH.2 */
#define DMA_TC_INT_CH3              (DMA_INTSTAT1_TC_3)     /*!< DMA transfer completed interrupt CH.3 */
#define DMA_TC_INT_CH4              (DMA_INTSTAT1_TC_4)     /*!< DMA transfer completed interrupt CH.4 */
#define DMA_TC_INT_CH5              (DMA_INTSTAT1_TC_5)     /*!< DMA transfer completed interrupt CH.5 */
#define DMA_TC_INT_CH6              (DMA_INTSTAT1_TC_6)     /*!< DMA transfer completed interrupt CH.6 */
#define DMA_TC_INT_CH7              (DMA_INTSTAT1_TC_7)     /*!< DMA transfer completed interrupt CH.7 */
/**
 * @}
 */

/**
 * @defgroup DMA_IntMsk_Sel DMA interrupt mask selection
 * @{
 */
#define DMA_ERR_INT_MASK            (0x00FF00FFUL)    /*!< DMA error interrupt mask */
#define DMA_TRANS_INT_MASK          (0x00FF00FFUL)    /*!< DMA transfer interrupt mask */
/**
 * @}
 */

/**
 * @defgroup DMA_Req_Status_Sel DMA request status
 * @{
 */
#define DMA_REQ_CH0                 (DMA_REQSTAT_CHREQ_0)   /*!< DMA request from CH.0 */
#define DMA_REQ_CH1                 (DMA_REQSTAT_CHREQ_1)   /*!< DMA request from CH.1 */
#define DMA_REQ_CH2                 (DMA_REQSTAT_CHREQ_2)   /*!< DMA request from CH.2 */
#define DMA_REQ_CH3                 (DMA_REQSTAT_CHREQ_3)   /*!< DMA request from CH.3 */
#define DMA_REQ_CH4                 (DMA_REQSTAT_CHREQ_4)   /*!< DMA request from CH.4 */
#define DMA_REQ_CH5                 (DMA_REQSTAT_CHREQ_5)   /*!< DMA request from CH.5 */
#define DMA_REQ_CH6                 (DMA_REQSTAT_CHREQ_6)   /*!< DMA request from CH.6 */
#define DMA_REQ_CH7                 (DMA_REQSTAT_CHREQ_7)   /*!< DMA request from CH.7 */
#define DMA_REQ_RECONFIG            (DMA_REQSTAT_RCFGREQ)   /*!< DMA request from reconfig */
#define DMA_REQ_STAT_MASK           (0x000080FFUL)          /*!< DMA request mask */
/**
 * @}
 */

/**
 * @defgroup DMA_Trans_Status_Sel DMA transfer status
 * @{
 */
#define DMA_TRANS_CH0               (DMA_CHSTAT_CHACT_0)    /*!< DMA transfer status of CH.0 */
#define DMA_TRANS_CH1               (DMA_CHSTAT_CHACT_1)    /*!< DMA transfer status of CH.1 */
#define DMA_TRANS_CH2               (DMA_CHSTAT_CHACT_2)    /*!< DMA transfer status of CH.2 */
#define DMA_TRANS_CH3               (DMA_CHSTAT_CHACT_3)    /*!< DMA transfer status of CH.3 */
#define DMA_TRANS_CH4               (DMA_CHSTAT_CHACT_4)    /*!< DMA transfer status of CH.4 */
#define DMA_TRANS_CH5               (DMA_CHSTAT_CHACT_5)    /*!< DMA transfer status of CH.5 */
#define DMA_TRANS_CH6               (DMA_CHSTAT_CHACT_6)    /*!< DMA transfer status of CH.6 */
#define DMA_TRANS_CH7               (DMA_CHSTAT_CHACT_7)    /*!< DMA transfer status of CH.7 */
#define DMA_TRANS_RECONFIG          (DMA_CHSTAT_RCFGACT)    /*!< DMA reconfig status */
#define DMA_TRANS_DMA               (DMA_CHSTAT_DMAACT)     /*!< DMA transfer status of the DMA */
#define DMA_TRANS_STAT_MASK         (0x0000FF03UL)          /*!< DMA request mask */
/**
 * @}
 */

/**
 * @defgroup DMA_DataWidth_Sel DMA transfer data width
 * @{
 */
#define DMA_DATAWIDTH_8BIT          (0x00000000UL)          /*!< DMA transfer data width 8bit  */
#define DMA_DATAWIDTH_16BIT         (DMA_CHCTL_HSIZE_0)     /*!< DMA transfer data width 16bit */
#define DMA_DATAWIDTH_32BIT         (DMA_CHCTL_HSIZE_1)     /*!< DMA transfer data width 32bit */
/**
 * @}
 */

/**
 * @defgroup DMA_Llp_En DMA LLP(linked list pinter) enable or disable
 * @{
 */
#define DMA_LLP_ENABLE              (DMA_CHCTL_LLPEN)       /*!< DMA LLP(linked list pinter) enable     */
#define DMA_LLP_DISABLE             (0x00000000UL)          /*!< DMA LLP(linked list pinter) disable    */
/**
 * @}
 */

/**
 * @defgroup DMA_Llp_Mode DMA linked list pinter mode while transferring complete
 * @{
 */
#define DMA_LLP_RUN                 (DMA_CHCTL_LLPRUN)      /*!< DMA Llp run right now while transfering complete     */
#define DMA_LLP_WAIT                (0x00000000UL)          /*!< DMA Llp wait next request while transfering complete */
/**
 * @}
 */

/**
 * @defgroup DMA_SrcAddr_Incremented_Mode DMA source address increment mode
 * @{
 */
#define DMA_SRC_ADDR_FIX            (0x00000000UL)          /*!< DMA source address fix             */
#define DMA_SRC_ADDR_INC            (DMA_CHCTL_SINC_0)      /*!< DMA source address increment       */
#define DMA_SRC_ADDR_DEC            (DMA_CHCTL_SINC_1)      /*!< DMA source address decrement       */
/**
 * @}
 */

/**
 * @defgroup DMA_DesAddr_Incremented_Mode DMA destination address increment mode
 * @{
 */
#define DMA_DEST_ADDR_FIX           (0x00000000UL)          /*!< DMA destination address fix        */
#define DMA_DEST_ADDR_INC           (DMA_CHCTL_DINC_0)      /*!< DMA destination address increment  */
#define DMA_DEST_ADDR_DEC           (DMA_CHCTL_DINC_1)      /*!< DMA destination address decrement  */
/**
 * @}
 */

/**
 * @defgroup DMA_Int_Config DMA interrupt function config
 * @{
 */
#define DMA_INT_ENABLE              (DMA_CHCTL_IE)          /*!< DMA interrupt enable */
#define DMA_INT_DISABLE             (0x00000000UL)          /*!< DMA interrupt disable */
/**
 * @}
 */

/**
 * @defgroup DMA_Repeat_Config DMA repeat mode function config
 * @{
 */
#define DMA_SRC_RPT_ENABLE          (DMA_CHCTL_SRTPEN)      /*!< DMA source repeat enable */
#define DMA_SRC_RPT_DISABLE         (0x00000000UL)          /*!< DMA source repeat disable */
#define DMA_DEST_RPT_ENABLE         (DMA_CHCTL_DRPTEN)      /*!< DMA destination repeat enable */
#define DMA_DEST_RPT_DISABLE        (0x00000000UL)          /*!< DMA destination repeat disable */
/**
 * @}
 */

/**
 * @defgroup DMA_NonSeq_Config DMA non-sequence mode function config
 * @{
 */
#define DMA_SRC_NS_ENABLE           (DMA_CHCTL_SNSEQEN)     /*!< DMA source non-sequence enable */
#define DMA_SRC_NS_DISABLE          (0x00000000UL)          /*!< DMA source non-sequence disable */
#define DMA_DEST_NS_ENABLE          (DMA_CHCTL_DNSEQEN)     /*!< DMA destination non-sequence enable */
#define DMA_DEST_NS_DISABLE         (0x00000000UL)          /*!< DMA destination non-sequence disable */
/**
 * @}
 */

/**
 * @defgroup DMA_ReConfig_Cnt_Sel DMA reconfig count mode selection
 * @{
 */
#define DMA_RC_CNT_FIX              (0x00UL)                /*!< Keep the original counting method */
#define DMA_RC_CNT_SRC              (DMA_RCFGCTL_CNTMD_0)   /*!< Use source address counting method */
#define DMA_RC_CNT_DEST             (DMA_RCFGCTL_CNTMD_1)   /*!< Use destination address counting method */
/**
 * @}
 */

/**
 * @defgroup DMA_ReConfig_DestAddr_Sel DMA reconfig destination address mode selection
 * @{
 */
#define DMA_RC_DA_FIX               (0x00000000UL)          /*!< Destination address fixed */
#define DMA_RC_DA_NS                (DMA_RCFGCTL_DARMD_0)   /*!< Destination address non-sequence */
#define DMA_RC_DA_RPT               (DMA_RCFGCTL_DARMD_1)   /*!< Destination address repeat */
/**
 * @}
 */

/**
 * @defgroup DMA_ReConfig_SrcAddr_Sel DMA reconfig source address mode selection
 * @{
 */
#define DMA_RC_SA_FIX               (0x00000000UL)          /*!< Source address fixed */
#define DMA_RC_SA_NS                (DMA_RCFGCTL_SARMD_0)   /*!< Source address non-sequence */
#define DMA_RC_SA_RPT               (DMA_RCFGCTL_SARMD_1)   /*!< Source address repeat */
/**
 * @}
 */

/**
 * @defgroup DMA_Common_Trigger_Source_Config DMA common Trigger Source Config
 * @{
 */
#define DMA_COM_TRIG1               (AOS_DMA_1_TRGSEL_COMTRG_EN_0)
#define DMA_COM_TRIG2               (AOS_DMA_1_TRGSEL_COMTRG_EN_1)
#define DMA_COM_TRIG_MASK           (AOS_DMA_1_TRGSEL_COMTRG_EN)
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
void DMA_Cmd(M4_DMA_TypeDef *DMAx, en_functional_state_t enNewState);

void DMA_ErrIntCmd(M4_DMA_TypeDef *DMAx, uint32_t u32ErrInt, en_functional_state_t enNewState);
en_flag_status_t DMA_GetErrIntStatus(const M4_DMA_TypeDef *DMAx, uint32_t u32ErrInt);
void DMA_ClearErrIntStatus(M4_DMA_TypeDef *DMAx, uint32_t u32ErrInt);

void DMA_TransIntCmd(M4_DMA_TypeDef *DMAx, uint32_t u32TransInt, en_functional_state_t enNewState);
en_flag_status_t DMA_GetTransIntStatus(const M4_DMA_TypeDef *DMAx, uint32_t u32TransInt);
void DMA_ClearTransIntStatus(M4_DMA_TypeDef *DMAx, uint32_t u32TransInt);

void DMA_MxChannelCmd(M4_DMA_TypeDef *DMAx, uint8_t u8MxCh, en_functional_state_t enNewState);
void DMA_ChannelCmd(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, en_functional_state_t enNewState);

void DMA_SetReConfigTriggerSrc(en_event_src_t enSrc);
void DMA_RCComTriggerCmd(uint32_t u32ComTrig, en_functional_state_t enNewState);
void DMA_SetTriggerSrc(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch, en_event_src_t enSrc);
void DMA_ComTriggerCmd(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32ComTrig, en_functional_state_t enNewState);

en_flag_status_t DMA_GetReqStatus(const M4_DMA_TypeDef *DMAx, uint32_t u32Status);
en_flag_status_t DMA_GetTransStatus(const M4_DMA_TypeDef *DMAx, uint32_t u32Status);

void DMA_SetSrcAddr(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Addr);
void DMA_SetDestAddr(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Addr);
void DMA_SetTransCnt(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint16_t u16Cnt);
void DMA_SetBlockSize(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint16_t u16Size);

void DMA_SetSrcRptSize(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint16_t u16Size);
void DMA_SetDestRptSize(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint16_t u16Size);
void DMA_SetNonSeqSrcCnt(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Cnt);
void DMA_SetNonSeqDestCnt(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Cnt);
void DMA_SetNonSeqSrcOffset(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Ofs);
void DMA_SetNonSeqDestOffset(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32Ofs);

void DMA_SetLlpAddr(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, uint32_t u32LlpAddr);

en_result_t DMA_Init(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_init_t *pstcDmaInit);
en_result_t DMA_RepeatInit(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_rpt_init_t *pstcDmaRptInit);
en_result_t DMA_NonSeqInit(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_nonseq_init_t *pstcDmaNonSeqInit);
en_result_t DMA_LlpInit(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_llp_init_t *pstcDmaLlpInit);
en_result_t DMA_ReConfigInit(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, const stc_dma_reconfig_init_t *pstcDmaRCInit);

en_result_t DMA_StructInit(stc_dma_init_t *pstcDmaInit);
en_result_t DMA_RepeatStructInit(stc_dma_rpt_init_t *pstcDmaRptInit);
en_result_t DMA_NonSeqStructInit(stc_dma_nonseq_init_t *pstcDmaNonSeqInit);
en_result_t DMA_LlpStructInit(stc_dma_llp_init_t *pstcDmaLlpInit);
en_result_t DMA_ReConfigStructInit(stc_dma_reconfig_init_t *pstcDmaRCInit);


void DMA_LlpCmd(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, en_functional_state_t enNewState);
void DMA_ReConfigCmd(M4_DMA_TypeDef *DMAx, en_functional_state_t enNewState);
void DMA_ReConfigLlpCmd(M4_DMA_TypeDef *DMAx, uint8_t u8Ch, en_functional_state_t enNewState);

uint32_t DMA_GetSrcAddr(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetDestAddr(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetTransCnt(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetBlockSize(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetSrcRptSize(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetDestRptSize(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetNonSeqSrcCnt(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetNonSeqDestCnt(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetNonSeqSrcOffset(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch);
uint32_t DMA_GetNonSeqDestOffset(const M4_DMA_TypeDef *DMAx, uint8_t u8Ch);
/**
 * @}
 */

#endif /* DDL_DMA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_DMA_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
