/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_EDMA_CORE_H_
#define _FSL_EDMA_CORE_H_

#include "fsl_edma_soc.h"

/*!
 * @addtogroup edma_core
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#if defined(FSL_EDMA_SOC_IP_DMA3) && defined(FSL_EDMA_SOC_IP_DMA4) && FSL_EDMA_SOC_IP_DMA3 && FSL_EDMA_SOC_IP_DMA4
#define DMA_CSR_INTMAJOR_MASK          DMA_TCD_CSR_INTMAJOR_MASK
#define DMA_CSR_INTHALF_MASK           DMA_TCD_CSR_INTHALF_MASK
#define DMA_CSR_DREQ_MASK              DMA_TCD_CSR_DREQ_MASK
#define DMA_CSR_ESG_MASK               DMA_TCD_CSR_ESG_MASK
#define DMA_CSR_START_MASK             DMA_TCD_CSR_START_MASK
#define DMA_CITER_ELINKNO_CITER_MASK   DMA_TCD_CITER_ELINKNO_CITER_MASK
#define DMA_BITER_ELINKNO_BITER_MASK   DMA_TCD_BITER_ELINKNO_BITER_MASK
#define DMA_CITER_ELINKNO_CITER_SHIFT  DMA_TCD_CITER_ELINKNO_CITER_SHIFT
#define DMA_CITER_ELINKYES_CITER_MASK  DMA_TCD_CITER_ELINKYES_CITER_MASK
#define DMA_CITER_ELINKYES_CITER_SHIFT DMA_TCD_CITER_ELINKYES_CITER_SHIFT
#define DMA_ATTR_SMOD_MASK             DMA_TCD_ATTR_SMOD_MASK
#define DMA_ATTR_DMOD_MASK             DMA_TCD_ATTR_DMOD_MASK
#define DMA_CITER_ELINKNO_ELINK_MASK   DMA_TCD_CITER_ELINKNO_ELINK_MASK
#define DMA_CSR_MAJORELINK_MASK        DMA_TCD_CSR_MAJORELINK_MASK
#define DMA_BITER_ELINKYES_ELINK_MASK  DMA_TCD_BITER_ELINKYES_ELINK_MASK
#define DMA_CITER_ELINKYES_ELINK_MASK  DMA_TCD_CITER_ELINKYES_ELINK_MASK
#define DMA_CSR_MAJORLINKCH_MASK       DMA_TCD_CSR_MAJORLINKCH_MASK
#define DMA_BITER_ELINKYES_LINKCH_MASK DMA_TCD_BITER_ELINKYES_LINKCH_MASK
#define DMA_CITER_ELINKYES_LINKCH_MASK DMA_TCD_CITER_ELINKYES_LINKCH_MASK
#define DMA_NBYTES_MLOFFYES_MLOFF_MASK DMA_TCD_NBYTES_MLOFFYES_MLOFF_MASK
#define DMA_NBYTES_MLOFFYES_DMLOE_MASK DMA_TCD_NBYTES_MLOFFYES_DMLOE_MASK
#define DMA_NBYTES_MLOFFYES_SMLOE_MASK DMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK
#define DMA_NBYTES_MLOFFNO_NBYTES_MASK DMA_TCD_NBYTES_MLOFFNO_NBYTES_MASK
#define DMA_ATTR_DMOD(x)               DMA_TCD_ATTR_DMOD(x)
#define DMA_ATTR_SMOD(X)               DMA_TCD_ATTR_SMOD(X)
#define DMA_BITER_ELINKYES_LINKCH(x)   DMA_TCD_BITER_ELINKYES_LINKCH(x)
#define DMA_CITER_ELINKYES_LINKCH(x)   DMA_TCD_CITER_ELINKYES_LINKCH(x)
#define DMA_NBYTES_MLOFFYES_MLOFF(x)   DMA_TCD_NBYTES_MLOFFYES_MLOFF(x)
#define DMA_NBYTES_MLOFFYES_DMLOE(x)   DMA_TCD_NBYTES_MLOFFYES_DMLOE(x)
#define DMA_NBYTES_MLOFFYES_SMLOE(x)   DMA_TCD_NBYTES_MLOFFYES_SMLOE(x)
#define DMA_NBYTES_MLOFFNO_NBYTES(x)   DMA_TCD_NBYTES_MLOFFNO_NBYTES(x)
#define DMA_NBYTES_MLOFFYES_NBYTES(x)  DMA_TCD_NBYTES_MLOFFYES_NBYTES(x)
#define DMA_ATTR_DSIZE(x)              DMA_TCD_ATTR_DSIZE(x)
#define DMA_ATTR_SSIZE(x)              DMA_TCD_ATTR_SSIZE(x)
#define DMA_CSR_DREQ(x)                DMA_TCD_CSR_DREQ(x)
#define DMA_CSR_MAJORLINKCH(x)         DMA_TCD_CSR_MAJORLINKCH(x)
#define DMA_CH_MATTR_WCACHE(x)         DMA4_CH_MATTR_WCACHE(x)
#define DMA_CH_MATTR_RCACHE(x)         DMA4_CH_MATTR_RCACHE(x)
#define DMA_CH_CSR_SIGNEXT_MASK        DMA4_CH_CSR_SIGNEXT_MASK
#define DMA_CH_CSR_SIGNEXT_SHIFT       DMA4_CH_CSR_SIGNEXT_SHIFT
#define DMA_CH_CSR_SWAP_MASK           DMA4_CH_CSR_SWAP_MASK
#define DMA_CH_CSR_SWAP_SHIFT          DMA4_CH_CSR_SWAP_SHIFT
#define DMA_CH_SBR_INSTR_MASK          DMA4_CH_SBR_INSTR_MASK
#define DMA_CH_SBR_INSTR_SHIFT         DMA4_CH_SBR_INSTR_SHIFT
#define DMA_CH_MUX_SOURCE(x)           DMA4_CH_MUX_SRC(x)
#elif defined(FSL_EDMA_SOC_IP_DMA3) && FSL_EDMA_SOC_IP_DMA3 && \
    (!defined(FSL_EDMA_SOC_IP_DMA4) || (defined(FSL_EDMA_SOC_IP_DMA4) && !FSL_EDMA_SOC_IP_DMA4))
#define DMA_CSR_INTMAJOR_MASK          DMA_TCD_CSR_INTMAJOR_MASK
#define DMA_CSR_INTHALF_MASK           DMA_TCD_CSR_INTHALF_MASK
#define DMA_CSR_DREQ_MASK              DMA_TCD_CSR_DREQ_MASK
#define DMA_CSR_ESG_MASK               DMA_TCD_CSR_ESG_MASK
#define DMA_CSR_START_MASK             DMA_TCD_CSR_START_MASK
#define DMA_CITER_ELINKNO_CITER_MASK   DMA_TCD_CITER_ELINKNO_CITER_MASK
#define DMA_BITER_ELINKNO_BITER_MASK   DMA_TCD_BITER_ELINKNO_BITER_MASK
#define DMA_CITER_ELINKNO_CITER_SHIFT  DMA_TCD_CITER_ELINKNO_CITER_SHIFT
#define DMA_CITER_ELINKYES_CITER_MASK  DMA_TCD_CITER_ELINKYES_CITER_MASK
#define DMA_CITER_ELINKYES_CITER_SHIFT DMA_TCD_CITER_ELINKYES_CITER_SHIFT
#define DMA_ATTR_SMOD_MASK             DMA_TCD_ATTR_SMOD_MASK
#define DMA_ATTR_DMOD_MASK             DMA_TCD_ATTR_DMOD_MASK
#define DMA_CITER_ELINKNO_ELINK_MASK   DMA_TCD_CITER_ELINKNO_ELINK_MASK
#define DMA_CSR_MAJORELINK_MASK        DMA_TCD_CSR_MAJORELINK_MASK
#define DMA_BITER_ELINKYES_ELINK_MASK  DMA_TCD_BITER_ELINKYES_ELINK_MASK
#define DMA_CITER_ELINKYES_ELINK_MASK  DMA_TCD_CITER_ELINKYES_ELINK_MASK
#define DMA_CSR_MAJORLINKCH_MASK       DMA_TCD_CSR_MAJORLINKCH_MASK
#define DMA_BITER_ELINKYES_LINKCH_MASK DMA_TCD_BITER_ELINKYES_LINKCH_MASK
#define DMA_CITER_ELINKYES_LINKCH_MASK DMA_TCD_CITER_ELINKYES_LINKCH_MASK
#define DMA_NBYTES_MLOFFYES_MLOFF_MASK DMA_TCD_NBYTES_MLOFFYES_MLOFF_MASK
#define DMA_NBYTES_MLOFFYES_DMLOE_MASK DMA_TCD_NBYTES_MLOFFYES_DMLOE_MASK
#define DMA_NBYTES_MLOFFYES_SMLOE_MASK DMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK
#define DMA_ATTR_DMOD(x)               DMA_TCD_ATTR_DMOD(x)
#define DMA_ATTR_SMOD(X)               DMA_TCD_ATTR_SMOD(X)
#define DMA_BITER_ELINKYES_LINKCH(x)   DMA_TCD_BITER_ELINKYES_LINKCH(x)
#define DMA_CITER_ELINKYES_LINKCH(x)   DMA_TCD_CITER_ELINKYES_LINKCH(x)
#define DMA_NBYTES_MLOFFYES_MLOFF(x)   DMA_TCD_NBYTES_MLOFFYES_MLOFF(x)
#define DMA_NBYTES_MLOFFYES_DMLOE(x)   DMA_TCD_NBYTES_MLOFFYES_DMLOE(x)
#define DMA_NBYTES_MLOFFYES_SMLOE(x)   DMA_TCD_NBYTES_MLOFFYES_SMLOE(x)
#define DMA_NBYTES_MLOFFNO_NBYTES(x)   DMA_TCD_NBYTES_MLOFFNO_NBYTES(x)
#define DMA_NBYTES_MLOFFYES_NBYTES(x)  DMA_TCD_NBYTES_MLOFFYES_NBYTES(x)
#define DMA_ATTR_DSIZE(x)              DMA_TCD_ATTR_DSIZE(x)
#define DMA_ATTR_SSIZE(x)              DMA_TCD_ATTR_SSIZE(x)
#define DMA_CSR_DREQ(x)                DMA_TCD_CSR_DREQ(x)
#define DMA_CSR_MAJORLINKCH(x)         DMA_TCD_CSR_MAJORLINKCH(x)
#define DMA_CH_MUX_SOURCE(x)           DMA_CH_MUX_SRC(x)
#elif defined(FSL_EDMA_SOC_IP_DMA4) && FSL_EDMA_SOC_IP_DMA4 && \
    (!defined(FSL_EDMA_SOC_IP_DMA3) || (defined(FSL_EDMA_SOC_IP_DMA3) && !FSL_EDMA_SOC_IP_DMA3))
#define DMA_CSR_INTMAJOR_MASK          DMA4_CSR_INTMAJOR_MASK
#define DMA_CSR_INTHALF_MASK           DMA4_CSR_INTHALF_MASK
#define DMA_CSR_DREQ_MASK              DMA4_CSR_DREQ_MASK
#define DMA_CSR_ESG_MASK               DMA4_CSR_ESG_MASK
#define DMA_CSR_START_MASK             DMA4_CSR_START_MASK
#define DMA_CITER_ELINKNO_CITER_MASK   DMA4_CITER_ELINKNO_CITER_MASK
#define DMA_BITER_ELINKNO_BITER_MASK   DMA4_BITER_ELINKNO_BITER_MASK
#define DMA_CITER_ELINKNO_CITER_SHIFT  DMA4_CITER_ELINKNO_CITER_SHIFT
#define DMA_CITER_ELINKYES_CITER_MASK  DMA4_CITER_ELINKYES_CITER_MASK
#define DMA_CITER_ELINKYES_CITER_SHIFT DMA4_CITER_ELINKYES_CITER_SHIFT
#define DMA_ATTR_SMOD_MASK             DMA4_ATTR_SMOD_MASK
#define DMA_ATTR_DMOD_MASK             DMA4_ATTR_DMOD_MASK
#define DMA_CITER_ELINKNO_ELINK_MASK   DMA4_CITER_ELINKNO_ELINK_MASK
#define DMA_CSR_MAJORELINK_MASK        DMA4_CSR_MAJORELINK_MASK
#define DMA_BITER_ELINKYES_ELINK_MASK  DMA4_BITER_ELINKYES_ELINK_MASK
#define DMA_CITER_ELINKYES_ELINK_MASK  DMA4_CITER_ELINKYES_ELINK_MASK
#define DMA_CSR_MAJORLINKCH_MASK       DMA4_CSR_MAJORLINKCH_MASK
#define DMA_BITER_ELINKYES_LINKCH_MASK DMA4_BITER_ELINKYES_LINKCH_MASK
#define DMA_CITER_ELINKYES_LINKCH_MASK DMA4_CITER_ELINKYES_LINKCH_MASK
#define DMA_NBYTES_MLOFFYES_MLOFF_MASK DMA4_NBYTES_MLOFFYES_MLOFF_MASK
#define DMA_NBYTES_MLOFFYES_DMLOE_MASK DMA4_NBYTES_MLOFFYES_DMLOE_MASK
#define DMA_NBYTES_MLOFFYES_SMLOE_MASK DMA4_NBYTES_MLOFFYES_SMLOE_MASK
#define DMA_ATTR_DMOD(x)               DMA4_ATTR_DMOD(x)
#define DMA_ATTR_SMOD(X)               DMA4_ATTR_SMOD(X)
#define DMA_BITER_ELINKYES_LINKCH(x)   DMA4_BITER_ELINKYES_LINKCH(x)
#define DMA_CITER_ELINKYES_LINKCH(x)   DMA4_CITER_ELINKYES_LINKCH(x)
#define DMA_NBYTES_MLOFFYES_MLOFF(x)   DMA4_NBYTES_MLOFFYES_MLOFF(x)
#define DMA_NBYTES_MLOFFYES_DMLOE(x)   DMA4_NBYTES_MLOFFYES_DMLOE(x)
#define DMA_NBYTES_MLOFFYES_SMLOE(x)   DMA4_NBYTES_MLOFFYES_SMLOE(x)
#define DMA_NBYTES_MLOFFNO_NBYTES(x)   DMA4_NBYTES_MLOFFNO_NBYTES(x)
#define DMA_NBYTES_MLOFFYES_NBYTES(x)  DMA4_NBYTES_MLOFFYES_NBYTES(x)
#define DMA_ATTR_DSIZE(x)              DMA4_ATTR_DSIZE(x)
#define DMA_ATTR_SSIZE(x)              DMA4_ATTR_SSIZE(x)
#define DMA_CSR_DREQ(x)                DMA4_CSR_DREQ(x)
#define DMA_CSR_MAJORLINKCH(x)         DMA4_CSR_MAJORLINKCH(x)
#define DMA_CH_MATTR_WCACHE(x)         DMA4_CH_MATTR_WCACHE(x)
#define DMA_CH_MATTR_RCACHE(x)         DMA4_CH_MATTR_RCACHE(x)
#define DMA_CH_CSR_SIGNEXT_MASK        DMA4_CH_CSR_SIGNEXT_MASK
#define DMA_CH_CSR_SIGNEXT_SHIFT       DMA4_CH_CSR_SIGNEXT_SHIFT
#define DMA_CH_CSR_SWAP_MASK           DMA4_CH_CSR_SWAP_MASK
#define DMA_CH_CSR_SWAP_SHIFT          DMA4_CH_CSR_SWAP_SHIFT
#define DMA_CH_SBR_INSTR_MASK          DMA4_CH_SBR_INSTR_MASK
#define DMA_CH_SBR_INSTR_SHIFT         DMA4_CH_SBR_INSTR_SHIFT
#define DMA_CH_MUX_SOURCE(x)           DMA4_CH_MUX_SRC(x)
#define DMA_CH_CSR_DONE_MASK           DMA4_CH_CSR_DONE_MASK
#define DMA_CH_CSR_ERQ_MASK            DMA4_CH_CSR_ERQ_MASK
#elif defined(FSL_EDMA_SOC_IP_EDMA) && FSL_EDMA_SOC_IP_EDMA
/*! intentional empty */
#endif

/*!@brief edma core channel struture definition */
typedef struct _edma_core_mp
{
    __IO uint32_t MP_CSR; /**< Channel Control and Status, array offset: 0x10000, array step: 0x10000 */
    __IO uint32_t MP_ES;  /**< Channel Error Status, array offset: 0x10004, array step: 0x10000 */
} edma_core_mp_t;

/*!@brief edma core channel struture definition */
typedef struct _edma_core_channel
{
    __IO uint32_t CH_CSR;   /**< Channel Control and Status, array offset: 0x10000, array step: 0x10000 */
    __IO uint32_t CH_ES;    /**< Channel Error Status, array offset: 0x10004, array step: 0x10000 */
    __IO uint32_t CH_INT;   /**< Channel Interrupt Status, array offset: 0x10008, array step: 0x10000 */
    __IO uint32_t CH_SBR;   /**< Channel System Bus, array offset: 0x1000C, array step: 0x10000 */
    __IO uint32_t CH_PRI;   /**< Channel Priority, array offset: 0x10010, array step: 0x10000 */
    __IO uint32_t CH_MUX;   /**< Channel Multiplexor Configuration, array offset: 0x10014, array step: 0x10000 */
    __IO uint16_t CH_MATTR; /**< Memory Attributes Register, array offset: 0x10018, array step: 0x8000 */
} edma_core_channel_t;

/*!@brief edma core TCD struture definition */
typedef struct _edma_core_tcd
{
    __IO uint32_t SADDR;     /*!< SADDR register, used to save source address */
    __IO uint16_t SOFF;      /*!< SOFF register, save offset bytes every transfer */
    __IO uint16_t ATTR;      /*!< ATTR register, source/destination transfer size and modulo */
    __IO uint32_t NBYTES;    /*!< Nbytes register, minor loop length in bytes */
    __IO uint32_t SLAST;     /*!< SLAST register */
    __IO uint32_t DADDR;     /*!< DADDR register, used for destination address */
    __IO uint16_t DOFF;      /*!< DOFF register, used for destination offset */
    __IO uint16_t CITER;     /*!< CITER register, current minor loop numbers, for unfinished minor loop.*/
    __IO uint32_t DLAST_SGA; /*!< DLASTSGA register, next tcd address used in scatter-gather mode */
    __IO uint16_t CSR;       /*!< CSR register, for TCD control status */
    __IO uint16_t BITER;     /*!< BITER register, begin minor loop count. */
} edma_core_tcd_t;

/*!@brief EDMA typedef */
typedef edma_core_channel_t EDMA_ChannelType;
typedef edma_core_tcd_t EDMA_TCDType;
typedef void EDMA_Type;

/*!@brief EDMA base address convert macro */
#define EDMA_BASE(base)
#define EDMA_CHANNEL_BASE(base, channel) \
    ((edma_core_channel_t *)((uint32_t)base + EDMA_CHANNEL_OFFSET + channel * EDMA_CHANNEL_ARRAY_STEP(base)))
#define EDMA_TCD_BASE(base, channel) \
    ((edma_core_tcd_t *)((uint32_t)base + EDMA_CHANNEL_OFFSET + channel * EDMA_CHANNEL_ARRAY_STEP(base) + 0x20U))
#define EDMA_MP_BASE(base) ((edma_core_mp_t *)((uint32_t)base))

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*!
 * @}
 */

#endif /* _FSL_EDMA_CORE_H_ */
