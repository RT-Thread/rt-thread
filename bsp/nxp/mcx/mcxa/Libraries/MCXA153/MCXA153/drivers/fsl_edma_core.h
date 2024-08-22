/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_EDMA_CORE_H_
#define FSL_EDMA_CORE_H_

#include "fsl_edma_soc.h"

/*!
 * @addtogroup edma_core
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DMA_CSR_INTMAJOR_MASK          (0x2U)
#define DMA_CSR_INTHALF_MASK           (0x4U)
#define DMA_CSR_DREQ_MASK              (0x8U)
#define DMA_CSR_ESG_MASK               (0x10U)
#define DMA_CSR_BWC_MASK               (0xC000U)
#define DMA_CSR_BWC(x)                 (((uint16_t)(((uint16_t)(x)) << (14U))) & (0xC000U))
#define DMA_CSR_START_MASK             (0x1U)
#define DMA_CITER_ELINKNO_CITER_MASK   (0x7FFFU)
#define DMA_BITER_ELINKNO_BITER_MASK   (0x7FFFU)
#define DMA_CITER_ELINKNO_CITER_SHIFT  (0U)
#define DMA_CITER_ELINKYES_CITER_MASK  (0x1FFU)
#define DMA_CITER_ELINKYES_CITER_SHIFT (0U)
#define DMA_ATTR_SMOD_MASK             (0xF800U)
#define DMA_ATTR_DMOD_MASK             (0xF8U)
#define DMA_CITER_ELINKNO_ELINK_MASK   (0x8000U)
#define DMA_CSR_MAJORELINK_MASK        (0x20U)
#define DMA_BITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_CITER_ELINKYES_ELINK_MASK  (0x8000U)
#define DMA_CSR_MAJORLINKCH_MASK       (0x1F00U)
#define DMA_BITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_CITER_ELINKYES_LINKCH_MASK (0x3E00U)
#define DMA_NBYTES_MLOFFYES_MLOFF_MASK (0x3FFFFC00U)
#define DMA_NBYTES_MLOFFYES_DMLOE_MASK (0x40000000U)
#define DMA_NBYTES_MLOFFYES_SMLOE_MASK (0x80000000U)
#define DMA_NBYTES_MLOFFNO_NBYTES_MASK (0x3FFFFFFFU)
#define DMA_ATTR_DMOD(x)               (((uint16_t)(((uint16_t)(x)) << (3U))) & (0xF8U))
#define DMA_ATTR_SMOD(x)               (((uint16_t)(((uint16_t)(x)) << (11U))) & (0xF800U))
#define DMA_BITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << (9U))) & (0x3E00U))
#define DMA_CITER_ELINKYES_LINKCH(x)   (((uint16_t)(((uint16_t)(x)) << (9U))) & (0x3E00U))
#define DMA_NBYTES_MLOFFYES_MLOFF(x)   (((uint32_t)(((uint32_t)(x)) << (10U))) & (0x3FFFFC00U))
#define DMA_NBYTES_MLOFFYES_DMLOE(x)   (((uint32_t)(((uint32_t)(x)) << (30U))) & (0x40000000U))
#define DMA_NBYTES_MLOFFYES_SMLOE(x)   (((uint32_t)(((uint32_t)(x)) << (31U))) & (0x80000000U))
#define DMA_NBYTES_MLOFFNO_NBYTES(x)   (((uint32_t)(((uint32_t)(x)) << (0U))) & (0x3FFFFFFFU))
#define DMA_NBYTES_MLOFFYES_NBYTES(x)  (((uint32_t)(((uint32_t)(x)) << (0U))) & (0x3FFU))
#define DMA_ATTR_DSIZE(x)              (((uint16_t)(((uint16_t)(x)) << (0U))) & (0x7U))
#define DMA_ATTR_SSIZE(x)              (((uint16_t)(((uint16_t)(x)) << (8U))) & (0x700U))
#define DMA_CSR_DREQ(x)                (((uint16_t)(((uint16_t)(x)) << (3U))) & (0x8U))
#define DMA_CSR_MAJORLINKCH(x)         (((uint16_t)(((uint16_t)(x)) << (8U))) & (0x1F00U))
#define DMA_CH_MATTR_WCACHE(x)         (((uint16_t)(((uint16_t)(x)) << (4U))) & (0xF0U))
#define DMA_CH_MATTR_RCACHE(x)         (((uint16_t)(((uint16_t)(x)) << (0U))) & (0xFU))
#define DMA_CH_CSR_SIGNEXT_MASK        (0x3F0000U)
#define DMA_CH_CSR_SIGNEXT_SHIFT       (16U)
#define DMA_CH_CSR_SWAP_MASK           (0xF000U)
#define DMA_CH_CSR_SWAP_SHIFT          (12U)
#define DMA_CH_SBR_INSTR_MASK          (0x2000U)
#define DMA_CH_SBR_INSTR_SHIFT         (13U)
#define DMA_CH_MUX_SOURCE(x)           (((uint32_t)(((uint32_t)(x)) << (0U))) & (0xFFU))

/*! @brief DMA error flag */
#if defined(FSL_EDMA_SOC_IP_EDMA) && FSL_EDMA_SOC_IP_EDMA
#define DMA_ERR_DBE_FLAG     DMA_ES_DBE_MASK
#define DMA_ERR_SBE_FLAG     DMA_ES_SBE_MASK
#define DMA_ERR_SGE_FLAG     DMA_ES_SGE_MASK
#define DMA_ERR_NCE_FLAG     DMA_ES_NCE_MASK
#define DMA_ERR_DOE_FLAG     DMA_ES_DOE_MASK
#define DMA_ERR_DAE_FLAG     DMA_ES_DAE_MASK
#define DMA_ERR_SOE_FLAG     DMA_ES_SOE_MASK
#define DMA_ERR_SAE_FLAG     DMA_ES_SAE_MASK
#define DMA_ERR_ERRCHAN_FLAG DMA_ES_ERRCHN_MASK
#define DMA_ERR_CPE_FLAG     DMA_ES_CPE_MASK
#define DMA_ERR_ECX_FLAG     DMA_ES_ECX_MASK
#if defined(FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT) && (FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 1)
#define DMA_ERR_GPE_FLAG DMA_ES_GPE_MASK
#endif
#define DMA_ERR_FLAG DMA_ES_VLD_MASK

/*! @brief get/clear DONE status*/
#define DMA_CLEAR_DONE_STATUS(base, channel) (EDMA_BASE(base)->CDNE = (uint8_t)channel)
#define DMA_GET_DONE_STATUS(base, channel) \
    ((EDMA_TCD_BASE(base, channel)->CSR & DMA_CSR_DONE_MASK) >> DMA_CSR_DONE_SHIFT)
/*! @brief enable/disable error interrupt*/
#define DMA_ENABLE_ERROR_INT(base, channel)  (base->EEI |= ((uint32_t)0x1U << channel))
#define DMA_DISABLE_ERROR_INT(base, channel) (base->EEI &= (~((uint32_t)0x1U << channel)))
/*! @brief get/clear error status*/
#define DMA_GET_ERROR_STATUS(base, channel)   (((uint32_t)EDMA_BASE(base)->ERR >> channel) & 0x1U)
#define DMA_CLEAR_ERROR_STATUS(base, channel) ((uint32_t)EDMA_BASE(base)->CERR = (uint8_t)channel)
/*! @brief get/clear int status*/
#define DMA_GET_INT_STATUS(base, channel)   ((((uint32_t)EDMA_BASE(base)->INT >> channel) & 0x1U))
#define DMA_CLEAR_INT_STATUS(base, channel) ((uint32_t)EDMA_BASE(base)->CINT = (uint8_t)channel)

#else

#define DMA_ERR_DBE_FLAG                     DMA_MP_ES_DBE_MASK
#define DMA_ERR_SBE_FLAG                     DMA_MP_ES_SBE_MASK
#define DMA_ERR_SGE_FLAG                     DMA_MP_ES_SGE_MASK
#define DMA_ERR_NCE_FLAG                     DMA_MP_ES_NCE_MASK
#define DMA_ERR_DOE_FLAG                     DMA_MP_ES_DOE_MASK
#define DMA_ERR_DAE_FLAG                     DMA_MP_ES_DAE_MASK
#define DMA_ERR_SOE_FLAG                     DMA_MP_ES_SOE_MASK
#define DMA_ERR_SAE_FLAG                     DMA_MP_ES_SAE_MASK
#define DMA_ERR_ERRCHAN_FLAG                 DMA_MP_ES_ERRCHN_MASK
#define DMA_ERR_ECX_FLAG                     DMA_MP_ES_ECX_MASK
#define DMA_ERR_FLAG                         DMA_MP_ES_VLD_MASK

/*! @brief get/clear DONE bit*/
#define DMA_CLEAR_DONE_STATUS(base, channel) (EDMA_CHANNEL_BASE(base, channel)->CH_CSR |= DMA_CH_CSR_DONE_MASK)
#define DMA_GET_DONE_STATUS(base, channel) \
    ((EDMA_CHANNEL_BASE(base, channel)->CH_CSR & DMA_CH_CSR_DONE_MASK) >> DMA_CH_CSR_DONE_SHIFT)
/*! @brief enable/disable error interupt*/
#define DMA_ENABLE_ERROR_INT(base, channel)   (EDMA_CHANNEL_BASE(base, channel)->CH_CSR |= DMA_CH_CSR_EEI_MASK)
#define DMA_DISABLE_ERROR_INT(base, channel)  (EDMA_CHANNEL_BASE(base, channel)->CH_CSR &= ~DMA_CH_CSR_EEI_MASK)
/*! @brief get/clear error status*/
#define DMA_CLEAR_ERROR_STATUS(base, channel) (EDMA_CHANNEL_BASE(base, channel)->CH_ES |= DMA_CH_ES_ERR_MASK)
#define DMA_GET_ERROR_STATUS(base, channel) \
    (((uint32_t)EDMA_CHANNEL_BASE(base, channel)->CH_ES >> DMA_CH_ES_ERR_SHIFT) & 0x1U)
/*! @brief get/clear INT status*/
#define DMA_CLEAR_INT_STATUS(base, channel) (EDMA_CHANNEL_BASE(base, channel)->CH_INT = DMA_CH_INT_INT_MASK)
#define DMA_GET_INT_STATUS(base, channel)   ((((uint32_t)EDMA_CHANNEL_BASE(base, channel)->CH_INT) & 0x1U))
#endif /*FSL_EDMA_SOC_IP_EDMA*/

/*! @brief enable/dsiable MAJOR/HALF INT*/
#define DMA_ENABLE_MAJOR_INT(base, channel) \
    (EDMA_TCD_CSR(EDMA_TCD_BASE(base, channel), EDMA_TCD_TYPE(base)) |= DMA_CSR_INTMAJOR_MASK)
#define DMA_ENABLE_HALF_INT(base, channel) \
    (EDMA_TCD_CSR(EDMA_TCD_BASE(base, channel), EDMA_TCD_TYPE(base)) |= DMA_CSR_INTHALF_MASK)
#define DMA_DISABLE_MAJOR_INT(base, channel) \
    (EDMA_TCD_CSR(EDMA_TCD_BASE(base, channel), EDMA_TCD_TYPE(base)) &= ~(uint16_t)DMA_CSR_INTMAJOR_MASK)
#define DMA_DISABLE_HALF_INT(base, channel) \
    (EDMA_TCD_CSR(EDMA_TCD_BASE(base, channel), EDMA_TCD_TYPE(base)) &= ~(uint16_t)DMA_CSR_INTHALF_MASK)

/*!@brief EDMA tcd align size */
#define EDMA_TCD_ALIGN_SIZE (32U)

/*!@brief edma core channel struture definition */
typedef struct _edma_core_mp
{
    __IO uint32_t MP_CSR; /**< Channel Control and Status, array offset: 0x10000, array step: 0x10000 */
    __IO uint32_t MP_ES;  /**< Channel Error Status, array offset: 0x10004, array step: 0x10000 */
    union
    {
        struct
        {
            __IO uint32_t MP_INT_LOW;   /**< Channel Control and Status, array offset: 0x10008, array step: 0x10000 */
            __I uint32_t MP_INT_HIGH;   /**< Channel Control and Status, array offset: 0x1000C, array step: 0x10000 */
            __I uint32_t MP_HRS_LOW;    /**< Channel Control and Status, array offset: 0x10010, array step: 0x10000 */
            __I uint32_t MP_HRS_HIGH;   /**< Channel Control and Status, array offset: 0x10014, array step: 0x10000 */
            uint8_t RESERVED_0[8];
            __IO uint32_t MP_STOPCH;    /**< Channel Control and Status, array offset: 0x10020, array step: 0x10000 */
            uint8_t RESERVED_1[12];
            __I uint32_t MP_SSR_LOW;    /**< Channel Control and Status, array offset: 0x10030, array step: 0x10000 */
            __I uint32_t MP_SSR_HIGH;   /**< Channel Control and Status, array offset: 0x10034, array step: 0x10000 */
            uint8_t RESERVED_2[200];
            __IO uint32_t CH_GRPRI[64]; /**< Channel Control and Status, array offset: 0x10100, array step: 0x10000 */
            __IO uint32_t CH_MUX[64];   /**< Channel Control and Status, array offset: 0x10200, array step: 0x10000 */
            uint8_t RESERVED_3[256];
            __IO uint32_t CH_PROT[64];  /**< Channel Control and Status, array offset: 0x10400, array step: 0x10000 */
        } EDMA5_REG;
    } MP_REGS;
} edma_core_mp_t;

/*!@brief edma core channel struture definition */
typedef struct _edma_core_channel
{
    __IO uint32_t CH_CSR; /**< Channel Control and Status, array offset: 0x10000, array step: 0x10000 */
    __IO uint32_t CH_ES;  /**< Channel Error Status, array offset: 0x10004, array step: 0x10000 */
    __IO uint32_t CH_INT; /**< Channel Interrupt Status, array offset: 0x10008, array step: 0x10000 */
    __IO uint32_t CH_SBR; /**< Channel System Bus, array offset: 0x1000C, array step: 0x10000 */
    __IO uint32_t CH_PRI; /**< Channel Priority, array offset: 0x10010, array step: 0x10000 */
    union
    {
        struct
        {
            __IO uint8_t RESERVED_1[4];
            __IO uint32_t CH_MATTR; /**< Memory Attributes Register, array offset: 0x10018, array step: 0x8000 */
        } EDMA5_REG;
        struct
        {
            __IO uint32_t CH_MUX; /**< Channel Multiplexor Configuration, array offset: 0x10014, array step: 0x10000 */
            __IO uint16_t CH_MATTR; /**< Memory Attributes Register, array offset: 0x10018, array step: 0x8000 */
        } EDMA4_REG;
    } CH_REGS;
} edma_core_channel_t;

/*! @brief eDMA tcd flag type */
typedef enum _edma_tcd_type
{
    kEDMA_EDMA4Flag = 0x0U, /*!< Data access for eDMA4 transfers. */
    kEDMA_EDMA5Flag = 0x1U, /*!< Instruction access for eDMA4 transfers. */
} edma_tcd_type_t;

/*!@brief edma5 core TCD struture definition */
typedef struct _edma5_core_tcd
{
    __IO uint32_t SADDR;          /*!< SADDR register, used to save source address */
    __IO uint32_t SADDR_HIGH;     /*!< SADDR HIGH register, used to save source address */
    __IO uint16_t SOFF;           /*!< SOFF register, save offset bytes every transfer */
    __IO uint16_t ATTR;           /*!< ATTR register, source/destination transfer size and modulo */
    __IO uint32_t NBYTES;         /*!< Nbytes register, minor loop length in bytes */
    __IO uint32_t SLAST;          /*!< SLAST register */
    __IO uint32_t SLAST_SDA_HIGH; /*!< SLAST SDA HIGH register */
    __IO uint32_t DADDR;          /*!< DADDR register, used for destination address */
    __IO uint32_t DADDR_HIGH;     /*!< DADDR HIGH register, used for destination address */
    __IO uint32_t DLAST_SGA;      /*!< DLASTSGA register, next tcd address used in scatter-gather mode */
    __IO uint32_t DLAST_SGA_HIGH; /*!< DLASTSGA HIGH register, next tcd address used in scatter-gather mode */
    __IO uint16_t DOFF;           /*!< DOFF register, used for destination offset */
    __IO uint16_t CITER;          /*!< CITER register, current minor loop numbers, for unfinished minor loop.*/
    __IO uint16_t CSR;            /*!< CSR register, for TCD control status */
    __IO uint16_t BITER;          /*!< BITER register, begin minor loop count. */
    uint8_t RESERVED[16];         /*!< Aligned 64 bytes */
} edma5_core_tcd_t;

/*!@brief edma4 core TCD struture definition */
typedef struct _edma4_core_tcd
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
} edma4_core_tcd_t;

/*!@brief edma core TCD struture definition */
typedef struct _edma_core_tcd
{
    union
    {
        edma4_core_tcd_t edma4_tcd;
#if defined FSL_EDMA_SOC_IP_DMA5 && FSL_EDMA_SOC_IP_DMA5
        edma5_core_tcd_t edma5_tcd;
#endif /* FSL_EDMA_SOC_IP_DMA5 */
    } TCD_REGS;
} edma_core_tcd_t;

/*!@brief EDMA typedef */
typedef edma_core_channel_t EDMA_ChannelType;
typedef edma_core_tcd_t EDMA_TCDType;
typedef void EDMA_Type;

/*!@brief EDMA base address convert macro */
#define EDMA_BASE(base)
#define EDMA_CHANNEL_BASE(base, channel)                                          \
    ((edma_core_channel_t *)((uint32_t)(uint32_t *)(base) + EDMA_CHANNEL_OFFSET + \
                             (channel)*EDMA_CHANNEL_ARRAY_STEP(base)))
#define EDMA_TCD_BASE(base, channel)                                          \
    ((edma_core_tcd_t *)((uint32_t)(uint32_t *)(base) + EDMA_CHANNEL_OFFSET + \
                         (channel)*EDMA_CHANNEL_ARRAY_STEP(base) + 0x20U))
#define EDMA_MP_BASE(base) ((edma_core_mp_t *)((uint32_t)(uint32_t *)(base)))

/*!@brief EDMA TCD type macro */
#if defined FSL_FEATURE_EDMA_TCD_TYPEn
#define EDMA_TCD_TYPE(x) FSL_FEATURE_EDMA_TCD_TYPEn(x)
#else
#define EDMA_TCD_TYPE(x) (0)
#endif

#if defined FSL_EDMA_SOC_IP_DMA5 && FSL_EDMA_SOC_IP_DMA5
/*!@brief EDMA TCD address convert macro */
#define EDMA_TCD_SADDR(tcd, flag)                                                                                    \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ? (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->SADDR)) : \
                                                      (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->SADDR))))

#define EDMA_TCD_SOFF(tcd, flag)                                                                                    \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ? (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->SOFF)) : \
                                                      (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->SOFF))))

#define EDMA_TCD_ATTR(tcd, flag)                                                                                    \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ? (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->ATTR)) : \
                                                      (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->ATTR))))

#define EDMA_TCD_NBYTES(tcd, flag)                                                                                    \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ? (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->NBYTES)) : \
                                                      (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->NBYTES))))

#define EDMA_TCD_SLAST(tcd, flag)                                                                                    \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ? (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->SLAST)) : \
                                                      (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->SLAST))))

#define EDMA_TCD_DADDR(tcd, flag)                                                                                    \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ? (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->DADDR)) : \
                                                      (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->DADDR))))

#define EDMA_TCD_DOFF(tcd, flag)                                                                                    \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ? (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->DOFF)) : \
                                                      (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->DOFF))))

#define EDMA_TCD_CITER(tcd, flag)                                                                                    \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ? (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->CITER)) : \
                                                      (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->CITER))))

#define EDMA_TCD_DLAST_SGA(tcd, flag)                                         \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ?                         \
           (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->DLAST_SGA)) : \
           (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->DLAST_SGA))))

#define EDMA_TCD_CSR(tcd, flag)                                                                                    \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ? (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->CSR)) : \
                                                      (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->CSR))))

#define EDMA_TCD_BITER(tcd, flag)                                                                                    \
    (*(((edma_tcd_type_t)(flag) == kEDMA_EDMA4Flag) ? (&(((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->BITER)) : \
                                                      (&(((edma5_core_tcd_t *)(&(tcd)->TCD_REGS.edma5_tcd))->BITER))))
#else
/*!@brief EDMA TCD address convert macro */
#define EDMA_TCD_SADDR(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->SADDR)

#define EDMA_TCD_SOFF(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->SOFF)

#define EDMA_TCD_ATTR(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->ATTR)

#define EDMA_TCD_NBYTES(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->NBYTES)

#define EDMA_TCD_SLAST(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->SLAST)

#define EDMA_TCD_DADDR(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->DADDR)

#define EDMA_TCD_DOFF(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->DOFF)

#define EDMA_TCD_CITER(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->CITER)

#define EDMA_TCD_DLAST_SGA(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->DLAST_SGA)

#define EDMA_TCD_CSR(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->CSR)

#define EDMA_TCD_BITER(tcd, flag) (((edma4_core_tcd_t *)(&(tcd)->TCD_REGS.edma4_tcd))->BITER)
#endif /* FSL_EDMA_SOC_IP_DMA5 */
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

#endif /* FSL_EDMA_CORE_H_ */
