/**
 *******************************************************************************
 * @file  hc32_ll_mcan.c
 * @brief This file provides firmware functions to manage the MCAN.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-12-15       CDT             Optimized driver:
                                    1. Integrated stc_mcan_classic_config_t and stc_mcan_fd_config_t into stc_mcan_bit_time_config_t
                                    2. Integrated u32FdIso into u32FrameFormat.
                                    3. Removed API MCAN_SetFdIsoOperation(), added API MCAN_SetFrameFormat().
                                    4. Optimized the handling of the parameter stc_mcan_filter_t.u32FilterIndex
                                    5. Add 5 APIs for better get protocol status(register PSR):
                                       MCAN_GetTdcValue(), MCAN_GetDataLastErrorCode(), MCAN_GetLastErrorCode(),
                                       MCAN_GetComState(), MCAN_GetProtocolFlagStatus()
                                    6. Changed u8Activity of stc_mcan_protocol_status_t to u8ComState.
                                    7. Changed u8MsgStorageIndex of stc_mcan_hpm_status_t to u8MsgIndex.
                                    8. Optimized local function MCAN_FilterInitConfig()
                                    9. When the frame to be transmitted is a remote frame, do not write the data field to the message RAM.
                                       When the received frame is a remote frame, do not read the data field from the message RAM.
                                    Optimized comments.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_mcan.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_MCAN MCAN
 * @brief MCAN Driver Library
 * @{
 */

#if (LL_MCAN_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup MCAN_Local_Macros MCAN Local Macros
 * @{
 */

/**
 * @defgroup MCAN_Private_Constants MCAN Private Constants
 * @{
 */
#define MCAN_TIMEOUT_COUNT              (100U)
#define MCAN_TIMEOUT_VALUE              (SystemCoreClock / 1000UL)

#define MCAN_DATA_SIZE_MIN              (MCAN_DATA_SIZE_8BYTE)
#define MCAN_DATA_SIZE_MAX              (MCAN_DATA_SIZE_64BYTE)

#define CAN20_DATA_SIZE_MAX             (8U)

#define MCAN_STD_FILTER_NUM_MAX         (128U)
#define MCAN_EXT_FILTER_NUM_MAX         (64U)
#define MCAN_RX_FIFO0_NUM_MAX           (64U)
#define MCAN_RX_FIFO1_NUM_MAX           (64U)
#define MCAN_RX_BUF_NUM_MAX             (64U)
#define MCAN_TX_EVT_NUM_MAX             (32U)
#define MCAN_TX_ELMT_NUM_MAX            (32U)

#define MCAN_FRAME_ESI_POS              (31U)       /*!< Position of Error State Indicator */
#define MCAN_FRAME_ANMF_POS             (31U)
#define MCAN_FRAME_XTD_POS              (30U)       /*!< Position of Extended ID */
#define MCAN_FRAME_RTR_POS              (29U)       /*!< Position of Remote Transmission Request */
#define MCAN_FRAME_MM_L_POS             (24U)       /*!< Position of Message Marker */
#define MCAN_FRAME_FIDX_POS             (24U)
#define MCAN_FRAME_EFC_POS              (23U)
#define MCAN_FRAME_TSCE_POS             (22U)
#define MCAN_FRAME_ET_POS               (22U)       /*!< Position of Event type */
#define MCAN_FRAME_FDF_POS              (21U)       /*!< Position of FD Format */
#define MCAN_FRAME_BRS_POS              (20U)       /*!< Position of Bit Rate Switch */
#define MCAN_FRAME_STDID_POS            (18U)       /*!< Position of Standard ID */
#define MCAN_FRAME_DLC_POS              (16U)       /*!< Position of Data Length Code */
#define MCAN_FRAME_MM_H_POS             (8U)        /*!< Position of Message Marker */

#define MCAN_FRAME_ESI_MASK             (1UL << MCAN_FRAME_ESI_POS)
#define MCAN_FRAME_ANMF_MASK            (1UL << MCAN_FRAME_ANMF_POS)
#define MCAN_FRAME_XTD_MASK             (1UL << MCAN_FRAME_XTD_POS)
#define MCAN_FRAME_RTR_MASK             (1UL << MCAN_FRAME_RTR_POS)
#define MCAN_FRAME_MM_L_MASK            (0xFFUL << MCAN_FRAME_MM_L_POS)
#define MCAN_FRAME_FIDX_MASK            (0x7FUL << MCAN_FRAME_FIDX_POS)
#define MCAN_FRAME_EFC_MASK             (1UL << MCAN_FRAME_EFC_POS)
#define MCAN_FRAME_TSCE_MASK            (1UL << MCAN_FRAME_TSCE_POS)
#define MCAN_FRAME_ET_MASK              (3UL << MCAN_FRAME_ET_POS)
#define MCAN_FRAME_FDF_MASK             (1UL << MCAN_FRAME_FDF_POS)
#define MCAN_FRAME_BRS_MASK             (1UL << MCAN_FRAME_BRS_POS)
#define MCAN_FRAME_STDID_MASK           (MCAN_STD_ID_MASK << MCAN_FRAME_STDID_POS)
#define MCAN_FRAME_EXTID_MASK           (MCAN_EXT_ID_MASK)
#define MCAN_FRAME_DLC_MASK             (0xFUL << MCAN_FRAME_DLC_POS)
#define MCAN_FRAME_MM_H_MASK            (0xFFUL << MCAN_FRAME_MM_H_POS)
#define MCAN_FRAME_TS_MASK              (0x0000FFFFUL)

#define MCAN_FILTER_SFTYPE_POS          (30U)
#define MCAN_FILTER_SFCFG_POS           (27U)
#define MCAN_FILTER_SFID1_POS           (16U)
#define MCAN_FILTER_SFDBGMSG_POS        (9U)

#define MCAN_FILTER_EFTYPE_POS          (30U)
#define MCAN_FILTER_EFCFG_POS           (29U)

/* Allocate start address of each part */
#define MCAN_STD_FILTER_SA(u)           (MCAN_MSG_RAM_BASE + READ_REG32_BIT((u)->SIDFC, MCAN_SIDFC_FLSSA))
#define MCAN_EXT_FILTER_SA(u)           (MCAN_MSG_RAM_BASE + READ_REG32_BIT((u)->XIDFC, MCAN_XIDFC_FLESA))
#define MCAN_RX_FIFO0_SA(u)             (MCAN_MSG_RAM_BASE + READ_REG32_BIT((u)->RXF0C, MCAN_RXF0C_F0SA))
#define MCAN_RX_FIFO1_SA(u)             (MCAN_MSG_RAM_BASE + READ_REG32_BIT((u)->RXF1C, MCAN_RXF1C_F1SA))
#define MCAN_RX_BUF_SA(u)               (MCAN_MSG_RAM_BASE + READ_REG32_BIT((u)->RXBC, MCAN_RXBC_RBSA))
#define MCAN_TX_EVT_FIFO_SA(u)          (MCAN_MSG_RAM_BASE + READ_REG32_BIT((u)->TXEFC, MCAN_TXEFC_EFSA))
#define MCAN_TX_ELMT_SA(u)              (MCAN_MSG_RAM_BASE + READ_REG32_BIT((u)->TXBC, MCAN_TXBC_TBSA))

/* Allocate number of each part */
#define MCAN_GET_STD_FILTER_NUM(u)      (READ_REG32_BIT((u)->SIDFC, MCAN_SIDFC_LSS) >> MCAN_SIDFC_LSS_POS)
#define MCAN_GET_EXT_FILTER_NUM(u)      (READ_REG32_BIT((u)->XIDFC, MCAN_XIDFC_LSE) >> MCAN_XIDFC_LSE_POS)
#define MCAN_GET_RX_FIFO0_NUM(u)        (READ_REG32_BIT((u)->RXF0C, MCAN_RXF0C_F0S) >> MCAN_RXF0C_F0S_POS)
#define MCAN_GET_RX_FIFO1_NUM(u)        (READ_REG32_BIT((u)->RXF1C, MCAN_RXF1C_F1S) >> MCAN_RXF1C_F1S_POS)
#define MCAN_GET_TX_EVT_FIFO_NUM(u)     (READ_REG32_BIT((u)->TXEFC, MCAN_TXEFC_EFS) >> MCAN_TXEFC_EFS_POS)
#define MCAN_GET_TX_BUF_NUM(u)          (READ_REG32_BIT((u)->TXBC, MCAN_TXBC_NDTB) >> MCAN_TXBC_NDTB_POS)
#define MCAN_GET_TX_FQ_NUM(u)           (READ_REG32_BIT((u)->TXBC, MCAN_TXBC_TFQS) >> MCAN_TXBC_TFQS_POS)

/* Data field size */
#define MCAN_RX_FIFO0_DS(u)             (READ_REG32_BIT((u)->RXESC, MCAN_RXESC_F0DS))
#define MCAN_RX_FIFO1_DS(u)             (READ_REG32_BIT((u)->RXESC, MCAN_RXESC_F1DS) >> MCAN_RXESC_F1DS_POS)
#define MCAN_RX_BUF_DS(u)               (READ_REG32_BIT((u)->RXESC, MCAN_RXESC_RBDS) >> MCAN_RXESC_RBDS_POS)
#define MCAN_TX_DS(u)                   (READ_REG32_BIT((u)->TXESC, MCAN_TXESC_TBDS))

/* Element size */
#define MCAN_STD_FILTER_ES              (4U)
#define MCAN_EXT_FILTER_ES              (8U)
#define MCAN_TX_EVT_ES                  (8U)
#define MCAN_RX_FIFO0_ES(u)             ((uint32_t)m_au8ElmtSize[MCAN_RX_FIFO0_DS(u)])
#define MCAN_RX_FIFO1_ES(u)             ((uint32_t)m_au8ElmtSize[MCAN_RX_FIFO1_DS(u)])
#define MCAN_RX_BUF_ES(u)               ((uint32_t)m_au8ElmtSize[MCAN_RX_BUF_DS(u)])
#define MCAN_TX_ES(u)                   ((uint32_t)m_au8ElmtSize[MCAN_TX_DS(u)])

#define MCAN_GET_ES(ds)                 ((uint32_t)m_au8ElmtSize[(ds)])

#define MCAN_RX_FIFO0_REAL_DS(u)        m_au8DLC2Size[MCAN_RX_FIFO0_DS(u) + 8U]
#define MCAN_RX_FIFO1_REAL_DS(u)        m_au8DLC2Size[MCAN_RX_FIFO1_DS(u) + 8U]
#define MCAN_RX_BUF_REAL_DS(u)          m_au8DLC2Size[MCAN_RX_BUF_DS(u) + 8U]
#define MCAN_TX_REAL_DS(u)              m_au8DLC2Size[MCAN_TX_DS(u) + 8U]

#define GET_BIT_POS(val)                (__CLZ(__RBIT(val)))

/**
 * @}
 */

/**
 * @defgroup MCAN_Check_Parameters_Validity MCAN Check Parameters Validity
 * @{
 */
#define IS_MCAN_BIT_MASK(x, mask)       (((x) != 0U) && (((x) | (mask)) == (mask)))

#define IS_ADC_1BIT_MASK(x)             (((x) != 0U) && (((x) & ((x) - 1U)) == 0U))

#define IS_MCAN_FUNC_EN(x, en)          (((x) == 0U) || ((x) == (en)))

#define IS_MCAN_RANGE(x, min, max)      (((x) >= (min)) && ((x) <= (max)))

/* MCAN unit */
#define IS_MCAN_UNIT(x)                 (((x) == CM_MCAN1) || ((x) == CM_MCAN2))

/* MCAN operating mode */
#define IS_MCAN_MD(x)                                                           \
(   ((x) == MCAN_MD_NORMAL)             ||                                      \
    ((x) == MCAN_MD_RESTRICTED_OP)      ||                                      \
    ((x) == MCAN_MD_BUS_MON)            ||                                      \
    ((x) == MCAN_MD_INTERN_LOOPBACK)    ||                                      \
    ((x) == MCAN_MD_EXTERN_LOOPBACK))

/* MCAN frame format */
#define IS_MCAN_FRAME_FORMAT(x)                                                 \
(   ((x) == MCAN_FRAME_CLASSIC)             ||                                  \
    ((x) == MCAN_FRAME_ISO_FD_NO_BRS)       ||                                  \
    ((x) == MCAN_FRAME_ISO_FD_BRS)          ||                                  \
    ((x) == MCAN_FRAME_NON_ISO_FD_NO_BRS)   ||                                  \
    ((x) == MCAN_FRAME_NON_ISO_FD_BRS))

/* Nominal bit time */
#define IS_MCAN_NBRP(x)                 IS_MCAN_RANGE(x, 1U, 512U)
#define IS_MCAN_NSEG1(x)                IS_MCAN_RANGE(x, 3U, 257U)
#define IS_MCAN_NSEG2(x)                IS_MCAN_RANGE(x, 2U, 128U)
#define IS_MCAN_NSJW(x)                 IS_MCAN_RANGE(x, 1U, 128U)

/* FD data bit time */
#define IS_MCAN_DBRP(tdc, x)                                                    \
(   (((tdc) == MCAN_FD_TDC_DISABLE) && IS_MCAN_RANGE(x, 1U, 32U))           ||  \
    (((tdc) == MCAN_FD_TDC_ENABLE) && IS_MCAN_RANGE(x, 1U, 2U)))
#define IS_MCAN_DSEG1(x)                IS_MCAN_RANGE(x, 2U, 33U)
#define IS_MCAN_DSEG2(x)                IS_MCAN_RANGE(x, 1U, 16U)
#define IS_MCAN_DSJW(x)                 IS_MCAN_RANGE(x, 1U, 16U)

/* FD data SSP offset */
#define IS_MCAN_SSP(x)                  ((x) <= 127U)
#define IS_MCAN_TDC_FILTER(x)           ((x) <= 127U)

/* MCAN Automatic Retransmission */
#define IS_MCAN_AUTO_RETX_EN(x)                                                 \
(   ((x) == MCAN_AUTO_RETX_DISABLE)     ||                                      \
    ((x) == MCAN_AUTO_RETX_ENABLE))

/* MCAN transmit pause */
#define IS_MCAN_TX_PAUSE_EN(x)                                                  \
(   ((x) == MCAN_TX_PAUSE_DISABLE)      ||                                      \
    ((x) == MCAN_TX_PAUSE_ENABLE))

/* MCAN Tx event message marker */
#define IS_MCAN_MSG_MARKER_CFG(x)                                               \
(   ((x) == MCAN_MSG_MARKER_8BIT)       ||                                      \
    ((x) == MCAN_MSG_MARKER_16BIT))

/* MCAN protocol exception handling */
#define IS_MCAN_PXH_EN(x)                                                       \
(   ((x) == MCAN_PROTOCOL_EXP_DISABLE)  ||                                      \
    ((x) == MCAN_PROTOCOL_EXP_ENABLE))

/* MCAN Tx pin control */
#define IS_MCAN_PIN_CTRL(x)                                                     \
(   ((x) == MCAN_TX_PIN_NORMAL)         ||                                      \
    ((x) == MCAN_TX_PIN_MONITOR)        ||                                      \
    ((x) == MCAN_TX_PIN_DOMINANT)       ||                                      \
    ((x) == MCAN_TX_PIN_RECESSIVE))

/* MCAN message RAM */
#define IS_MCAN_MSG_RAM_OFFSET_ADDR(x)  ((((x) & 0x3UL) == 0U) && ((x) < MCAN_MSG_RAM_SIZE))
#define IS_MCAN_STD_FILTER_NUM(x)       ((x) <= MCAN_STD_FILTER_NUM_MAX)
#define IS_MCAN_EXT_FILTER_NUM(x)       ((x) <= MCAN_EXT_FILTER_NUM_MAX)
#define IS_MCAN_RX_FIFO0_NUM(x)         ((x) <= MCAN_RX_FIFO0_NUM_MAX)
#define IS_MCAN_RX_FIFO1_NUM(x)         ((x) <= MCAN_RX_FIFO1_NUM_MAX)
#define IS_MCAN_RX_BUF_NUM(x)           ((x) <= MCAN_RX_BUF_NUM_MAX)
#define IS_MCAN_TX_EVT_NUM(x)           ((x) <= MCAN_TX_EVT_NUM_MAX)
#define IS_MCAN_TX_ELMT_NUM(x)          ((x) <= MCAN_TX_ELMT_NUM_MAX)
#define IS_MCAN_MSG_RAM_END_ADDR(x)     ((x) <= MCAN_MSG_RAM_END)

/* MCAN data field size */
#define IS_MCAN_DATA_FIELD_SIZE(x)      ((x) <= MCAN_DATA_SIZE_MAX)

/* Tx FIFO/Queue operation mode */
#define IS_MCAN_TX_FIFO_QUEUE_MD(x)     (((x) == MCAN_TX_FIFO_MD) || ((x) == MCAN_TX_QUEUE_MD))

/* MCAN filter */
#define IS_MCAN_ID_TYPE(x)              (((x) == MCAN_STD_ID) || ((x) == MCAN_EXT_ID))
#define IS_MCAN_STD_ID_VAL(x)           ((x) <= MCAN_STD_ID_MASK)
#define IS_MCAN_EXT_ID_VAL(x)           ((x) <= MCAN_EXT_ID_MASK)

#define IS_MCAN_STD_FILTER_TYPE(x)                                              \
(   ((x) == MCAN_FILTER_RANGE)          ||                                      \
    ((x) == MCAN_FILTER_DUAL )          ||                                      \
    ((x) == MCAN_FILTER_MASK))

#define IS_MCAN_EXT_FILTER_TYPE(x)                                              \
(   ((x) == MCAN_FILTER_RANGE)          ||                                      \
    ((x) == MCAN_FILTER_DUAL)           ||                                      \
    ((x) == MCAN_FILTER_MASK)           ||                                      \
    ((x) == MCAN_FILTER_RANGE_NO_EIDM))

#define IS_MCAN_FILTER_CFG(x)                                                   \
(   ((x) == MCAN_FILTER_DISABLE)        ||                                      \
    ((x) == MCAN_FILTER_TO_RX_FIFO0)    ||                                      \
    ((x) == MCAN_FILTER_TO_RX_FIFO1)    ||                                      \
    ((x) == MCAN_FILTER_REJECT)         ||                                      \
    ((x) == MCAN_FILTER_HP_NO_STORAGE)  ||                                      \
    ((x) == MCAN_FILTER_HP_TO_RX_FIFO0) ||                                      \
    ((x) == MCAN_FILTER_HP_TO_RX_FIFO1) ||                                      \
    ((x) == MCAN_FILTER_TO_RX_BUF))

/* Non-matching frame operation */
#define IS_MCAN_NMF_OP(x)                                                       \
(   ((x) == MCAN_NMF_ACCEPT_IN_RX_FIFO0)    ||                                  \
    ((x) == MCAN_NMF_ACCEPT_IN_RX_FIFO1)    ||                                  \
    ((x) == MCAN_NMF_REJECT))

/* Remote frame operation */
#define IS_MCAN_REMOTE_FRAME_OP(x)                                              \
(   ((x) == MCAN_REMOTE_FRAME_FILTER)   ||                                      \
    ((x) == MCAN_REMOTE_FRAME_REJECT ))

/* Rx FIFO */
#define IS_MCAN_RX_FIFO(x)                                                      \
(   ((x) == MCAN_RX_FIFO0)              ||                                      \
    ((x) == MCAN_RX_FIFO1))

/* Rx FIFO operation mode */
#define IS_MCAN_RX_FIFO_MD(x)                                                   \
(   ((x) == MCAN_RX_FIFO_BLOCKING)      ||                                      \
    ((x) == MCAN_RX_FIFO_OVERWRITE))

/* Watermark FIFO */
#define IS_MCAN_WATERMARK_FIFO(x)                                               \
(   ((x) == MCAN_WATERMARK_TX_EVT_FIFO) ||                                      \
    ((x) == MCAN_WATERMARK_RX_FIFO0)    ||                                      \
    ((x) == MCAN_WATERMARK_RX_FIFO1))

/* RAM watchdog counter start value */
#define IS_MCAN_RAM_WDT_START_VAL(x)    ((x) <= 255U)

/* MCAN timestamp counter */
#define IS_MCAN_TS_PRESC(x)             (((x) >= 1U) && ((x) <= 16U ))

/* MCAN timeout counter */
#define IS_MCAN_TO_SEL(x)                                                       \
(   ((x) == MCAN_TIMEOUT_CONT)          ||                                      \
    ((x) == MCAN_TIMEOUT_TX_EVT_FIFO)   ||                                      \
    ((x) == MCAN_TIMEOUT_RX_FIFO0)      ||                                      \
    ((x) == MCAN_TIMEOUT_RX_FIFO1))

#define IS_MCAN_TO_PERIOD(x)            ((x) <= 65535U)

/* MCAN frame bit field */
#define IS_MCAN_FRAME_RTR(x)            (((x) == 0U) || ((x) == 1U))
#define IS_MCAN_FRAME_DLC(x)            ((x) <= MCAN_DLC64)
#define IS_MCAN_FRAME_ESI(x)            (((x) == 0U) || ((x) == 1U))
#define IS_MCAN_FRAME_BRS(x)            (((x) == 0U) || ((x) == 1U))
#define IS_MCAN_FRAME_FDF(x)            (((x) == 0U) || ((x) == 1U))
#define IS_MCAN_FRAME_EFC(x)            (((x) == 0U) || ((x) == 1U))

#define IS_MCAN_FRAME_MSG_MARKER(wmm, x)                                        \
(   (((wmm) == 0U) && ((x) <= 255UL))   ||                                      \
    (((wmm) != 0U) && ((x) <= 65535UL)))

/* One Tx buffer check */
#define IS_MCAN_1TXBUF(x)               IS_ADC_1BIT_MASK(x)
#define IS_MCAN_TX_BUF(x)               IS_MCAN_BIT_MASK(x, MCAN_TX_BUF_ALL)

/* Interrupt */
#define IS_MCAN_INT_LINE(x)                                                     \
(   ((x) == MCAN_INT_LINE0)             ||                                      \
    ((x) == MCAN_INT_LINE1))
#define IS_MCAN_INT_TYPE(x)             IS_MCAN_BIT_MASK(x, MCAN_INT_ALL)
#define IS_MCAN_TX_BUF_NOTICE(x)        IS_MCAN_BIT_MASK(x, MCAN_INT_TX_CPLT | MCAN_INT_TX_ABORT_CPLT)

/* Interrupt flag */
#define IS_MCAN_FLAG(x)                 IS_MCAN_BIT_MASK(x, MCAN_FLAG_ALL)

/* Protocol status flag */
#define IS_MCAN_PS_FLAG(x)              IS_MCAN_BIT_MASK(x, MCAN_PROTOCOL_FLAG_ALL)

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/**
 * @defgroup MCAN_Local_Variables MCAN Local Variables
 * @{
 */
static const uint8_t m_au8DLC2Size[16U] = {
    0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U
};

static const uint8_t m_au8ElmtSize[8U] = {16U, 20U, 24U, 28U, 32U, 40U, 56U, 72U};

/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup MCAN_Local_Functions MCAN Local Functions
 * @{
 */

/**
 * @brief  Specifies MCAN operating mode.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32Mode                MCAN operating mode.
 *                                      This parameter can be a value of @ref MCAN_Operating_Mode
 *   @arg  MCAN_MD_NORMAL:              Normal mode.
 *   @arg  MCAN_MD_RESTRICTED_OP:       Restricted operation mode.
 *   @arg  MCAN_MD_BUS_MON:             Bus monitoring mode.
 *   @arg  MCAN_MD_INTERN_LOOPBACK:     Internal loopBack mode.
 *   @arg  MCAN_MD_EXTERN_LOOPBACK:     External loopBack mode.
 * @retval None
 */
static void MCAN_SetMode(CM_MCAN_TypeDef *MCANx, uint32_t u32Mode)
{
    /* Set MCAN operating mode:
       |----------------------|-----------|----------|-----------|----------|
       |                      | CCCR.TEST | CCCR.MON | TEST.LBCK | CCCR.ASM |
       |----------------------|-----------|----------|-----------|----------|
       | Normal               |     0     |     0    |     0     |    0     |
       |----------------------|-----------|----------|-----------|----------|
       | Restricted Operation |     0     |     0    |     0     |    1     |
       |----------------------|-----------|----------|-----------|----------|
       | Bus Monitoring       |     0     |     1    |     0     |    0     |
       |----------------------|-----------|----------|-----------|----------|
       | Internal LoopBack    |     1     |     1    |     1     |    0     |
       |----------------------|-----------|----------|-----------|----------|
       | External LoopBack    |     1     |     0    |     1     |    0     |
       |----------------------|-----------|----------|-----------|----------|
    */
    /* Default mode: normal mode */
    CLR_REG32_BIT(MCANx->CCCR, MCAN_CCCR_TEST | MCAN_CCCR_MON | MCAN_CCCR_ASM);
    CLR_REG32_BIT(MCANx->TEST, MCAN_TEST_LBCK);
    /* Switch mode according to the parameter u32Mode */
    switch (u32Mode) {
        case MCAN_MD_RESTRICTED_OP:
            SET_REG32_BIT(MCANx->CCCR, MCAN_CCCR_ASM);
            break;
        case MCAN_MD_BUS_MON:
            SET_REG32_BIT(MCANx->CCCR, MCAN_CCCR_MON);
            break;
        case MCAN_MD_INTERN_LOOPBACK:
            SET_REG32_BIT(MCANx->CCCR, MCAN_CCCR_TEST | MCAN_CCCR_MON);
            SET_REG32_BIT(MCANx->TEST, MCAN_TEST_LBCK);
            break;
        case MCAN_MD_EXTERN_LOOPBACK:
            SET_REG32_BIT(MCANx->CCCR, MCAN_CCCR_TEST);
            SET_REG32_BIT(MCANx->TEST, MCAN_TEST_LBCK);
            break;
        default:
            /* Nothing to do: normal mode */
            break;
    }
}

/**
 * @brief  Configures MCAN message RAM.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  pstcMsgRam             Pointer to a @ref stc_mcan_msg_ram_config_t type structure
 *                                      which contains the message RAM configuration information.
 * @retval None
 */
static void MCAN_MsgRamInitConfig(CM_MCAN_TypeDef *MCANx, stc_mcan_msg_ram_config_t *pstcMsgRam)
{
    uint32_t u32EndAddr;
    uint32_t u32StartAddr = pstcMsgRam->u32AddrOffset;
    uint32_t u32TxElmtNum = pstcMsgRam->u32TxBufferNum + pstcMsgRam->u32TxFifoQueueNum;

    /* Start address(offset address) 4byte alignment required */
    DDL_ASSERT(IS_MCAN_MSG_RAM_OFFSET_ADDR(u32StartAddr));
    DDL_ASSERT(IS_MCAN_STD_FILTER_NUM(pstcMsgRam->u32StdFilterNum));
    DDL_ASSERT(IS_MCAN_EXT_FILTER_NUM(pstcMsgRam->u32ExtFilterNum));
    DDL_ASSERT(IS_MCAN_RX_FIFO0_NUM(pstcMsgRam->u32RxFifo0Num));
    DDL_ASSERT(IS_MCAN_RX_FIFO1_NUM(pstcMsgRam->u32RxFifo1Num));
    DDL_ASSERT(IS_MCAN_RX_BUF_NUM(pstcMsgRam->u32RxBufferNum));
    DDL_ASSERT(IS_MCAN_TX_EVT_NUM(pstcMsgRam->u32TxEventNum));
    DDL_ASSERT(IS_MCAN_TX_ELMT_NUM(u32TxElmtNum));

    /* Standard filter start address and elements number */
    WRITE_REG32(MCANx->SIDFC, u32StartAddr);
    SET_REG32_BIT(MCANx->SIDFC, (pstcMsgRam->u32StdFilterNum << MCAN_SIDFC_LSS_POS));

    /* Extended filter start address and elements number */
    u32StartAddr += (pstcMsgRam->u32StdFilterNum * MCAN_STD_FILTER_ES);
    WRITE_REG32(MCANx->XIDFC, (pstcMsgRam->u32ExtFilterNum << MCAN_XIDFC_LSE_POS) | u32StartAddr);

    /* Rx FIFO0 start address and elements number */
    u32StartAddr += (pstcMsgRam->u32ExtFilterNum * MCAN_EXT_FILTER_ES);
    WRITE_REG32(MCANx->RXF0C, (pstcMsgRam->u32RxFifo0Num << MCAN_RXF0C_F0S_POS) | u32StartAddr);

    /* Rx FIFO1 start address and elements number */
    u32StartAddr += (pstcMsgRam->u32RxFifo0Num * MCAN_GET_ES(pstcMsgRam->u32RxFifo0DataSize));
    WRITE_REG32(MCANx->RXF1C, (pstcMsgRam->u32RxFifo1Num << MCAN_RXF1C_F1S_POS) | u32StartAddr);

    /* Rx buffer list start address */
    u32StartAddr += (pstcMsgRam->u32RxFifo1Num * MCAN_GET_ES(pstcMsgRam->u32RxFifo1DataSize));
    WRITE_REG32(MCANx->RXBC, u32StartAddr);

    /* Tx event FIFO start address and elements number */
    u32StartAddr += (pstcMsgRam->u32RxBufferNum * MCAN_GET_ES(pstcMsgRam->u32RxBufferDataSize));
    WRITE_REG32(MCANx->TXEFC, (pstcMsgRam->u32TxEventNum << MCAN_TXEFC_EFS_POS) | u32StartAddr);

    /* Tx buffer list start address, dedicated Tx buffers number, Tx FIFO/queue elements number */
    u32StartAddr += (pstcMsgRam->u32TxEventNum * MCAN_TX_EVT_ES);
    WRITE_REG32(MCANx->TXBC, (pstcMsgRam->u32TxFifoQueueNum << MCAN_TXBC_TFQS_POS) | \
                (pstcMsgRam->u32TxBufferNum << MCAN_TXBC_NDTB_POS) | \
                u32StartAddr);
    u32StartAddr += (u32TxElmtNum * MCAN_GET_ES(pstcMsgRam->u32TxDataSize));
    /* Get total allocated size */
    pstcMsgRam->u32AllocatedSize = u32StartAddr - pstcMsgRam->u32AddrOffset;

    /* Message RAM end address */
    u32EndAddr = MCAN_MSG_RAM_BASE + u32StartAddr;
    /* Assert the end address is not out of range. */
    DDL_ASSERT(IS_MCAN_MSG_RAM_END_ADDR(u32EndAddr));

    /* Configure Rx FIFO0, Rx FIFO1 and Rx buffer data filed size */
    if (pstcMsgRam->u32RxFifo0Num > 0U) {
        DDL_ASSERT(IS_MCAN_DATA_FIELD_SIZE(pstcMsgRam->u32RxFifo0DataSize));
        MODIFY_REG32(MCANx->RXESC, MCAN_RXESC_F0DS, (pstcMsgRam->u32RxFifo0DataSize << MCAN_RXESC_F0DS_POS));
    }
    if (pstcMsgRam->u32RxFifo1Num > 0U) {
        DDL_ASSERT(IS_MCAN_DATA_FIELD_SIZE(pstcMsgRam->u32RxFifo1DataSize));
        MODIFY_REG32(MCANx->RXESC, MCAN_RXESC_F1DS, (pstcMsgRam->u32RxFifo1DataSize << MCAN_RXESC_F1DS_POS));
    }
    if (pstcMsgRam->u32RxBufferNum > 0U) {
        DDL_ASSERT(IS_MCAN_DATA_FIELD_SIZE(pstcMsgRam->u32RxBufferDataSize));
        MODIFY_REG32(MCANx->RXESC, MCAN_RXESC_RBDS, (pstcMsgRam->u32RxBufferDataSize << MCAN_RXESC_RBDS_POS));
    }

    /* Configure Tx data filed size */
    if (u32TxElmtNum > 0U) {
        DDL_ASSERT(IS_MCAN_DATA_FIELD_SIZE(pstcMsgRam->u32TxDataSize));
        WRITE_REG32(MCANx->TXESC, pstcMsgRam->u32TxDataSize);

        if (pstcMsgRam->u32TxFifoQueueNum > 0U) {
            DDL_ASSERT(IS_MCAN_TX_FIFO_QUEUE_MD(pstcMsgRam->u32TxFifoQueueMode));
            MODIFY_REG32(MCANx->TXBC, MCAN_TXBC_TFQM, pstcMsgRam->u32TxFifoQueueMode);
        }
    }

    /* Flush the allocated Message RAM area */
    u32StartAddr = pstcMsgRam->u32AddrOffset + MCAN_MSG_RAM_BASE;
    while (u32StartAddr < u32EndAddr) {
        RW_MEM32(u32StartAddr) = 0x0UL;
        u32StartAddr += 4UL;
    }
}

/**
 * @brief  Configures MCAN acceptance filters when initializing the MCAN module.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  pstcFilter             Pointer to a @ref stc_mcan_filter_config_t type structure which
 *                                      contains the acceptance filters configuration information.
 * @retval None
 */
static void MCAN_FilterInitConfig(CM_MCAN_TypeDef *MCANx, stc_mcan_filter_config_t *pstcFilter)
{
    uint32_t i;

    if (pstcFilter->pstcStdFilterList != NULL) {
        for (i = 0U; i < pstcFilter->u32StdFilterConfigNum; i++) {
            pstcFilter->pstcStdFilterList[i].u32FilterIndex = i;
            (void)MCAN_FilterConfig(MCANx, &pstcFilter->pstcStdFilterList[i]);
        }
    }

    if (pstcFilter->pstcExtFilterList != NULL) {
        for (i = 0U; i < pstcFilter->u32ExtFilterConfigNum; i++) {
            pstcFilter->pstcExtFilterList[i].u32FilterIndex = i;
            (void)MCAN_FilterConfig(MCANx, &pstcFilter->pstcExtFilterList[i]);
        }
    }
}

/**
 * @brief  Copy Tx message to the message RAM.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  pTxMsg                 Pointer to a @ref stc_mcan_tx_msg_t structure that contains
 *                                      the information of the message that to be transmitted.
 * @param  [in]  u32TxPutIndex          Index of the Tx buffer to be configured.
 * @retval None
 */
static void MCAN_CopyTxMsgToRam(CM_MCAN_TypeDef *MCANx, stc_mcan_tx_msg_t *pTxMsg, uint32_t u32TxPutIndex)
{
    uint8_t i;
    uint32_t u32T0;
    uint32_t u32T1;
    uint32_t u32TxAddr;
    uint32_t u32MsgMarkerCfg;
    uint32_t u32DataSize;

    /* Build first word of Tx header element */
    if (pTxMsg->IDE == MCAN_STD_ID) {
        /* Standard frame */
        u32T0 = ((pTxMsg->ESI << MCAN_FRAME_ESI_POS) | \
                 (pTxMsg->RTR << MCAN_FRAME_RTR_POS) | \
                 (pTxMsg->ID << MCAN_FRAME_STDID_POS));
    } else {
        /* Extended frame */
        u32T0 = ((pTxMsg->ESI << MCAN_FRAME_ESI_POS) | \
                 (pTxMsg->IDE << MCAN_FRAME_XTD_POS) | \
                 (pTxMsg->RTR << MCAN_FRAME_RTR_POS) | \
                 pTxMsg->ID);
    }

    u32MsgMarkerCfg = pTxMsg->u32MsgMarker << MCAN_FRAME_MM_L_POS;
    if (READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_WMM) != 0U) {
        u32MsgMarkerCfg |= (pTxMsg->u32MsgMarker & MCAN_FRAME_MM_H_MASK);
    }
    /* Build second word of Tx header element */
    u32T1 = (u32MsgMarkerCfg | \
             (pTxMsg->u32StoreTxEvent << MCAN_FRAME_EFC_POS) | \
             (pTxMsg->FDF << MCAN_FRAME_FDF_POS) | \
             (pTxMsg->BRS << MCAN_FRAME_BRS_POS) | \
             (pTxMsg->DLC << MCAN_FRAME_DLC_POS));
    /* Calculate Tx element address */
    u32TxAddr  = MCAN_TX_ELMT_SA(MCANx);
    u32TxAddr += (u32TxPutIndex * MCAN_TX_ES(MCANx));

    /* Write Tx element header to the message RAM */
    RW_MEM32(u32TxAddr) = u32T0;
    u32TxAddr += 4U;
    RW_MEM32(u32TxAddr) = u32T1;

    u32DataSize = m_au8DLC2Size[pTxMsg->DLC];
    /* Determine the CAN frame format: classical CAN or FD CAN */
    if (READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_FDOE) == 0U) {
        /* Max 8 bytes for classical CAN */
        if (u32DataSize > CAN20_DATA_SIZE_MAX) {
            u32DataSize = CAN20_DATA_SIZE_MAX;
        }
    } else {
        DDL_ASSERT(u32DataSize <= MCAN_TX_REAL_DS(MCANx));
    }
    if (pTxMsg->RTR == 0U) {
        /* Write Tx payload to the message RAM */
        for (i = 0U; i < u32DataSize; i += 4U) {
            u32TxAddr += 4U;
            RW_MEM32(u32TxAddr) = (((uint32_t)pTxMsg->au8Data[i + 3U] << 24U) | \
                                   ((uint32_t)pTxMsg->au8Data[i + 2U] << 16U) | \
                                   ((uint32_t)pTxMsg->au8Data[i + 1U] << 8U)  | \
                                   (uint32_t)pTxMsg->au8Data[i]);
        }
    }
}

/**
 * @brief  Get the number of the Rx buffer that has an allocated area into the message RAM.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint32_t type value of the number of the Rx buffer
 */
static uint32_t MCAN_GetRxBufferNum(const CM_MCAN_TypeDef *MCANx)
{
    uint32_t u32Temp;
    /* Get Tx event FIFO start address */
    u32Temp = MCAN_TX_EVT_FIFO_SA(MCANx);
    /* Get Rx buffer size */
    u32Temp -= MCAN_RX_BUF_SA(MCANx);
    /* Get Rx buffer number */
    return (u32Temp / MCAN_RX_BUF_ES(MCANx));
}

/**
 * @}
 */

/**
 * @defgroup MCAN_Global_Functions MCAN Global Functions
 * @{
 */

/**
 * @brief  Initializes the specified MCAN peripheral according to the specified parameters
 *         in the structure pstcMcanInit.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  pstcMcanInit           Pointer to a @ref stc_mcan_init_t structure value that
 *                                      contains the configuration information for the MCAN.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcMcanInit == NULL
 */
int32_t MCAN_Init(CM_MCAN_TypeDef *MCANx, stc_mcan_init_t *pstcMcanInit)
{
    uint32_t u32Config;
    uint32_t u32Mask;
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    __IO uint32_t u32TimeoutValue = MCAN_TIMEOUT_VALUE;

    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (pstcMcanInit != NULL) {
        DDL_ASSERT(IS_MCAN_MD(pstcMcanInit->u32Mode));
        DDL_ASSERT(IS_MCAN_FRAME_FORMAT(pstcMcanInit->u32FrameFormat));
        DDL_ASSERT(IS_MCAN_NBRP(pstcMcanInit->stcBitTime.u32NominalPrescaler));
        DDL_ASSERT(IS_MCAN_NSEG1(pstcMcanInit->stcBitTime.u32NominalTimeSeg1));
        DDL_ASSERT(IS_MCAN_NSEG2(pstcMcanInit->stcBitTime.u32NominalTimeSeg2));
        DDL_ASSERT(IS_MCAN_NSJW(pstcMcanInit->stcBitTime.u32NominalSyncJumpWidth));
        /* If FD enabled */
        if ((pstcMcanInit->u32FrameFormat & MCAN_CCCR_FDOE) == MCAN_CCCR_FDOE) {
            DDL_ASSERT(IS_MCAN_DBRP(pstcMcanInit->stcBitTime.u32TDC, \
                                    pstcMcanInit->stcBitTime.u32DataPrescaler));
            DDL_ASSERT(IS_MCAN_DSEG1(pstcMcanInit->stcBitTime.u32DataTimeSeg1));
            DDL_ASSERT(IS_MCAN_DSEG2(pstcMcanInit->stcBitTime.u32DataTimeSeg2));
            DDL_ASSERT(IS_MCAN_DSJW(pstcMcanInit->stcBitTime.u32DataSyncJumpWidth));
            if (pstcMcanInit->stcBitTime.u32TDC == MCAN_FD_TDC_ENABLE) {
                DDL_ASSERT(IS_MCAN_SSP(pstcMcanInit->stcBitTime.u32SspOffset));
                DDL_ASSERT(IS_MCAN_TDC_FILTER(pstcMcanInit->stcBitTime.u32TdcFilter));
            }
        }
        DDL_ASSERT(IS_MCAN_AUTO_RETX_EN(pstcMcanInit->u32AutoRetx));
        DDL_ASSERT(IS_MCAN_TX_PAUSE_EN(pstcMcanInit->u32TxPause));
        DDL_ASSERT(IS_MCAN_PXH_EN(pstcMcanInit->u32ProtocolException));

        if (pstcMcanInit->stcFilter.u32StdFilterConfigNum > 0U) {
            DDL_ASSERT(pstcMcanInit->stcFilter.u32StdFilterConfigNum <= \
                       (uint8_t)pstcMcanInit->stcMsgRam.u32StdFilterNum);
        }
        if (pstcMcanInit->stcFilter.u32ExtFilterConfigNum > 0U) {
            DDL_ASSERT(pstcMcanInit->stcFilter.u32ExtFilterConfigNum <= \
                       (uint8_t)pstcMcanInit->stcMsgRam.u32ExtFilterNum);
        }

        i32Ret = LL_OK;
        /* Exit from sleep mode */
        CLR_REG32_BIT(MCANx->CCCR, MCAN_CCCR_CSR);
        /* Check sleep mode acknowledge */
        while (READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_CSA) == MCAN_CCCR_CSA) {
            u32TimeoutValue--;
            if (u32TimeoutValue == 0u) {
                i32Ret = LL_ERR_TIMEOUT;
            }
        }

        if (i32Ret == LL_OK) {
            /* Request initialization */
            SET_REG32_BIT(MCANx->CCCR, MCAN_CCCR_INIT);
            /* Wait until the CCCR.INIT is set */
            u32TimeoutValue = MCAN_TIMEOUT_VALUE;
            while (READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_INIT) == 0U) {
                u32TimeoutValue--;
                if (u32TimeoutValue == 0u) {
                    i32Ret = LL_ERR_TIMEOUT;
                }
            }
        }

        if (i32Ret == LL_OK) {
            /* Enable configuration change */
            SET_REG32_BIT(MCANx->CCCR, MCAN_CCCR_CCE);

            /* Frame format, automatic retransmission, transmit pause, protocol exception handling */
            u32Mask   = MCAN_FRAME_NON_ISO_FD_BRS | MCAN_CCCR_DAR | MCAN_CCCR_TXP | MCAN_CCCR_PXHD;
            u32Config = pstcMcanInit->u32FrameFormat | pstcMcanInit->u32AutoRetx | \
                        pstcMcanInit->u32TxPause | pstcMcanInit->u32ProtocolException;
            MODIFY_REG32(MCANx->CCCR, u32Mask, u32Config);

            /* Nominal bit time */
            u32Config = ((pstcMcanInit->stcBitTime.u32NominalPrescaler - 1U) << MCAN_NBTP_NBRP_POS)     | \
                        ((pstcMcanInit->stcBitTime.u32NominalTimeSeg1 - 2U) << MCAN_NBTP_NTSEG1_POS)    | \
                        ((pstcMcanInit->stcBitTime.u32NominalSyncJumpWidth - 1U) << MCAN_NBTP_NSJW_POS) | \
                        (pstcMcanInit->stcBitTime.u32NominalTimeSeg2 - 1U);
            WRITE_REG32(MCANx->NBTP, u32Config);

            /* Data bit time */
            if ((pstcMcanInit->u32FrameFormat & MCAN_CCCR_FDOE) == MCAN_CCCR_FDOE) {
                u32Config = ((pstcMcanInit->stcBitTime.u32DataPrescaler - 1U) << MCAN_DBTP_DBRP_POS)  | \
                            ((pstcMcanInit->stcBitTime.u32DataTimeSeg1 - 2U) << MCAN_DBTP_DTSEG1_POS) | \
                            (pstcMcanInit->stcBitTime.u32DataSyncJumpWidth - 1U)                      | \
                            ((pstcMcanInit->stcBitTime.u32DataTimeSeg2 - 1U) << MCAN_DBTP_DTSEG2_POS);
                WRITE_REG32(MCANx->DBTP, u32Config);
                if (pstcMcanInit->stcBitTime.u32TDC == MCAN_FD_TDC_ENABLE) {
                    SET_REG32_BIT(MCANx->DBTP, pstcMcanInit->stcBitTime.u32TDC);
                    u32Config = (pstcMcanInit->stcBitTime.u32SspOffset << MCAN_TDCR_TDCO_POS) | \
                                pstcMcanInit->stcBitTime.u32TdcFilter;
                    WRITE_REG32(MCANx->TDCR, u32Config);
                }
            }

            /* MCAN operating mode */
            MCAN_SetMode(MCANx, pstcMcanInit->u32Mode);
            /* MCAN message RAM */
            MCAN_MsgRamInitConfig(MCANx, &pstcMcanInit->stcMsgRam);
            /* MCAN message filter */
            MCAN_FilterInitConfig(MCANx, &pstcMcanInit->stcFilter);
            /* Reject all non-matching frames. */
            WRITE_REG32(MCANx->GFC, 0x3FUL);
        }

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set each member of @ref stc_mcan_init_t to a default value.
 *         The default value for bit time is an example for application, based on the 40MHz MCAN clock.
 *         The default value set nominal bit rate to 500Kbps, set data bit rate to 4Mbps.
 *         Nominal prescaler: 1
 *         Nominal total TQs: 80
 *         Nominal time segment before sample point: 64
 *         Nominal time segment after sample point: 16
 *         Nominal (re)synchronization jump width: 16
 *         Nominal sample point: 80%
 *         Data prescaler: 1
 *         Data total TQs: 10
 *         Data time segment before sample point: 8
 *         Data time segment after sample point: 2
 *         Data (re)synchronization jump width: 2
 *         Data sample point: 80%
 * @param  [in]  pstcMcanInit           Pointer to a @ref stc_mcan_init_t structure
 *                                      whose members will be set to default values.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcMcanInit == NULL.
 */
int32_t MCAN_StructInit(stc_mcan_init_t *pstcMcanInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcMcanInit != NULL) {
        pstcMcanInit->u32Mode              = MCAN_MD_NORMAL;
        pstcMcanInit->u32FrameFormat       = MCAN_FRAME_ISO_FD_BRS;
        pstcMcanInit->u32AutoRetx          = MCAN_AUTO_RETX_ENABLE;
        pstcMcanInit->u32TxPause           = MCAN_TX_PAUSE_DISABLE;
        pstcMcanInit->u32ProtocolException = MCAN_PROTOCOL_EXP_ENABLE;
        /* Nominal bit time, for classical CAN and CAN FD arbitration phase */
        pstcMcanInit->stcBitTime.u32NominalPrescaler     = 1U;
        pstcMcanInit->stcBitTime.u32NominalTimeSeg1      = 64U;
        pstcMcanInit->stcBitTime.u32NominalTimeSeg2      = 16U;
        pstcMcanInit->stcBitTime.u32NominalSyncJumpWidth = 16U;
        /* Data bit time, for CAN FD data phase */
        pstcMcanInit->stcBitTime.u32DataPrescaler        = 1U;
        pstcMcanInit->stcBitTime.u32DataTimeSeg1         = 8U;
        pstcMcanInit->stcBitTime.u32DataTimeSeg2         = 2U;
        pstcMcanInit->stcBitTime.u32DataSyncJumpWidth    = 2U;
        pstcMcanInit->stcBitTime.u32TDC                  = MCAN_FD_TDC_ENABLE;
        pstcMcanInit->stcBitTime.u32SspOffset            = 8U;
        pstcMcanInit->stcBitTime.u32TdcFilter            = 0U;
        /* Message RAM */
        pstcMcanInit->stcMsgRam.u32AddrOffset        = 0U;
        pstcMcanInit->stcMsgRam.u32StdFilterNum      = 0U;
        pstcMcanInit->stcMsgRam.u32ExtFilterNum      = 0U;
        pstcMcanInit->stcMsgRam.u32RxFifo0Num        = 0U;
        pstcMcanInit->stcMsgRam.u32RxFifo0DataSize   = MCAN_DATA_SIZE_8BYTE;
        pstcMcanInit->stcMsgRam.u32RxFifo1Num        = 0U;
        pstcMcanInit->stcMsgRam.u32RxFifo1DataSize   = MCAN_DATA_SIZE_8BYTE;
        pstcMcanInit->stcMsgRam.u32RxBufferNum       = 0U;
        pstcMcanInit->stcMsgRam.u32RxBufferDataSize  = MCAN_DATA_SIZE_8BYTE;
        pstcMcanInit->stcMsgRam.u32TxEventNum        = 0U;
        pstcMcanInit->stcMsgRam.u32TxBufferNum       = 0U;
        pstcMcanInit->stcMsgRam.u32TxFifoQueueNum    = 0U;
        pstcMcanInit->stcMsgRam.u32TxFifoQueueMode   = MCAN_TX_FIFO_MD;
        pstcMcanInit->stcMsgRam.u32TxDataSize        = MCAN_DATA_SIZE_8BYTE;
        /* Acceptance filter */
        pstcMcanInit->stcFilter.pstcStdFilterList     = NULL;
        pstcMcanInit->stcFilter.pstcExtFilterList     = NULL;
        pstcMcanInit->stcFilter.u32StdFilterConfigNum = 0U;
        pstcMcanInit->stcFilter.u32ExtFilterConfigNum = 0U;

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief Deinitialize the MCAN peripheral registers to their default reset values.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval None
 */
void MCAN_DeInit(CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    /* Stop the MCAN module: return value is voluntary ignored. */
    (void)MCAN_Stop(MCANx);
    /* Disable interrupt lines. */
    WRITE_REG32(MCANx->ILE, 0U);
    /* Set registers to their default reset values. */
    WRITE_REG32(MCANx->DBTP, 0x0A33U);
    WRITE_REG32(MCANx->TEST, 0x0U);
    WRITE_REG32(MCANx->RWD, 0x0U);
    WRITE_REG32(MCANx->CCCR, 0x3U);
    WRITE_REG32(MCANx->NBTP, 0x06000A03UL);
    WRITE_REG32(MCANx->TSCC, 0x0U);
    WRITE_REG32(MCANx->TOCC, 0x0U);
    WRITE_REG32(MCANx->TDCR, 0x0U);
    WRITE_REG32(MCANx->IR, 0x0U);
    WRITE_REG32(MCANx->IE, 0x0U);
    WRITE_REG32(MCANx->ILS, 0x0U);
    WRITE_REG32(MCANx->GFC, 0x0U);
    WRITE_REG32(MCANx->SIDFC, 0x0U);
    WRITE_REG32(MCANx->XIDFC, 0x0U);
    WRITE_REG32(MCANx->XIDAM, 0x1FFFFFFFUL);
    WRITE_REG32(MCANx->NDAT1, 0x0U);
    WRITE_REG32(MCANx->NDAT2, 0x0U);
    WRITE_REG32(MCANx->RXF0C, 0x0U);
    WRITE_REG32(MCANx->RXBC, 0x0U);
    WRITE_REG32(MCANx->RXF1C, 0x0U);
    WRITE_REG32(MCANx->RXESC, 0x0U);
    WRITE_REG32(MCANx->TXBC, 0x0U);
    WRITE_REG32(MCANx->TXESC, 0x0U);
    WRITE_REG32(MCANx->TXBAR, 0x0U);
    WRITE_REG32(MCANx->TXBCR, 0x0U);
    WRITE_REG32(MCANx->TXBTIE, 0x0U);
    WRITE_REG32(MCANx->TXBCIE, 0x0U);
    WRITE_REG32(MCANx->TXEFC, 0x0U);
}

/**
 * @brief Leave the initialization mode and start the MCAN module.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval None
 */
void MCAN_Start(CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    CLR_REG32_BIT(MCANx->CCCR, MCAN_CCCR_INIT);
}

/**
 * @brief Stop the MCAN module and enable access to configuration registers.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Operation timeout.
 */
int32_t MCAN_Stop(CM_MCAN_TypeDef *MCANx)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32Counter = 0U;

    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    /* Request initialization */
    SET_REG32_BIT(MCANx->CCCR, MCAN_CCCR_INIT);
    /* Wait until the CCCR.INIT bit is set */
    while (READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_INIT) == 0U) {
        u32Counter++;
        if (u32Counter > MCAN_TIMEOUT_COUNT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    /* Exit from sleep mode */
    if (i32Ret == LL_OK) {
        u32Counter = 0U;
        /* Exit from sleep mode */
        CLR_REG32_BIT(MCANx->CCCR, MCAN_CCCR_CSR);
        /* Wait until MCAN exits sleep mode */
        while (READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_CSA) == MCAN_CCCR_CSA) {
            u32Counter++;
            if (u32Counter > MCAN_TIMEOUT_COUNT) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
        }
    }

    if (i32Ret == LL_OK) {
        /* Enable configuration change */
        SET_REG32_BIT(MCANx->CCCR, MCAN_CCCR_CCE);
    }

    return i32Ret;
}

/**
 * @brief Enter MCAN peripheral in sleep mode.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Operation timeout.
 */
int32_t MCAN_EnterSleepMode(CM_MCAN_TypeDef *MCANx)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeoutValue = MCAN_TIMEOUT_VALUE;

    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    /* Request clock stop */
    SET_REG32_BIT(MCANx->CCCR, MCAN_CCCR_CSR);
    /* Wait until MCAN is ready for sleep */
    while (READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_CSA) == 0U) {
        u32TimeoutValue--;
        if (u32TimeoutValue == 0U) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief Exit sleep mode.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Operation timeout.
 */
int32_t MCAN_ExitSleepMode(CM_MCAN_TypeDef *MCANx)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeoutValue = MCAN_TIMEOUT_VALUE;

    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    /* Reset clock stop request */
    CLR_REG32_BIT(MCANx->CCCR, MCAN_CCCR_CSR);
    /* Wait until MCAN exits sleep mode */
    while (READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_CSA) == MCAN_CCCR_CSA) {
        u32TimeoutValue--;
        if (u32TimeoutValue == 0U) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    if (i32Ret == LL_OK) {
        /* Enter normal operation */
        CLR_REG32_BIT(MCANx->CCCR, MCAN_CCCR_INIT);
    }

    return i32Ret;
}

/**
 * @brief Get the address of each element that allocated into the message RAM
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  pstcAddr               Pointer to a @ref stc_mcan_msg_ram_addr_t type structure
 *                                      which contains the message RAM configuration information.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcMcanInit == NULL.
 */
int32_t MCAN_GetMsgRamAddr(const CM_MCAN_TypeDef *MCANx, stc_mcan_msg_ram_addr_t *pstcAddr)
{
    uint32_t i;
    uint32_t u32ElementNum;
    uint32_t u32ElementSize;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (pstcAddr != NULL) {
        /* Get start address */
        pstcAddr->u32StdFilterStartAddr = MCAN_STD_FILTER_SA(MCANx);
        pstcAddr->u32ExtFilterStartAddr = MCAN_EXT_FILTER_SA(MCANx);
        pstcAddr->u32RxFifo0StartAddr   = MCAN_RX_FIFO0_SA(MCANx);
        pstcAddr->u32RxFifo1StartAddr   = MCAN_RX_FIFO1_SA(MCANx);
        pstcAddr->u32RxBufferStartAddr  = MCAN_RX_BUF_SA(MCANx);
        pstcAddr->u32TxEventStartAddr   = MCAN_TX_EVT_FIFO_SA(MCANx);
        pstcAddr->u32TxBufferStartAddr  = MCAN_TX_ELMT_SA(MCANx);
        u32ElementNum = MCAN_GET_TX_BUF_NUM(MCANx);
        pstcAddr->u32TxFifoQueueStartAddr = pstcAddr->u32TxBufferStartAddr + u32ElementNum * MCAN_TX_ES(MCANx);
        u32ElementNum = MCAN_GET_TX_FQ_NUM(MCANx);
        pstcAddr->u32EndAddr = pstcAddr->u32TxFifoQueueStartAddr + u32ElementNum * MCAN_TX_ES(MCANx);

        /* Get each standard filter element address. */
        if (pstcAddr->pu32StdFilterAddrList != NULL) {
            u32ElementNum = MCAN_GET_STD_FILTER_NUM(MCANx);
            for (i = 0U; i < u32ElementNum; i++) {
                pstcAddr->pu32StdFilterAddrList[i] = pstcAddr->u32StdFilterStartAddr + i * MCAN_STD_FILTER_ES;
            }
        }
        /* Get each extended filter element address. */
        if (pstcAddr->pu32ExtFilterAddrList != NULL) {
            u32ElementNum = MCAN_GET_EXT_FILTER_NUM(MCANx);
            for (i = 0U; i < u32ElementNum; i++) {
                pstcAddr->pu32ExtFilterAddrList[i] = pstcAddr->u32ExtFilterStartAddr + i * MCAN_EXT_FILTER_ES;
            }
        }
        /* Get each Rx FIFO0 element address. */
        if (pstcAddr->pu32RxFifo0AddrList != NULL) {
            u32ElementNum  = MCAN_GET_RX_FIFO0_NUM(MCANx);
            u32ElementSize = MCAN_RX_FIFO0_ES(MCANx);
            for (i = 0U; i < u32ElementNum; i++) {
                pstcAddr->pu32RxFifo0AddrList[i] = pstcAddr->u32RxFifo0StartAddr + i * u32ElementSize;
            }
        }
        /* Get each Rx FIFO1 element address. */
        if (pstcAddr->pu32RxFifo1AddrList != NULL) {
            u32ElementNum  = MCAN_GET_RX_FIFO1_NUM(MCANx);
            u32ElementSize = MCAN_RX_FIFO1_ES(MCANx);
            for (i = 0U; i < u32ElementNum; i++) {
                pstcAddr->pu32RxFifo1AddrList[i] = pstcAddr->u32RxFifo1StartAddr + i * u32ElementSize;
            }
        }
        /* Get each Rx buffer element address. */
        if (pstcAddr->pu32RxBufferAddrList != NULL) {
            u32ElementNum  = MCAN_GetRxBufferNum(MCANx);
            u32ElementSize = MCAN_RX_BUF_ES(MCANx);
            for (i = 0U; i < u32ElementNum; i++) {
                pstcAddr->pu32RxBufferAddrList[i] = pstcAddr->u32RxBufferStartAddr + i * u32ElementSize;
            }
        }
        /* Get each Tx event FIFO element address. */
        if (pstcAddr->pu32TxEventAddrList != NULL) {
            u32ElementNum  = MCAN_GET_TX_EVT_FIFO_NUM(MCANx);
            for (i = 0U; i < u32ElementNum; i++) {
                pstcAddr->pu32TxEventAddrList[i] = pstcAddr->u32TxEventStartAddr + i * MCAN_TX_EVT_ES;
            }
        }
        /* Get each dedicated Tx buffer element address. */
        if (pstcAddr->pu32TxBufferAddrList != NULL) {
            u32ElementNum  = MCAN_GET_TX_BUF_NUM(MCANx);
            u32ElementSize = MCAN_TX_ES(MCANx);
            for (i = 0U; i < u32ElementNum; i++) {
                pstcAddr->pu32TxBufferAddrList[i] = pstcAddr->u32TxBufferStartAddr + i * u32ElementSize;
            }
        }
        /* Get each Tx FIFO/Queue element address. */
        if (pstcAddr->pu32TxFifoQueueAddrList != NULL) {
            u32ElementNum  = MCAN_GET_TX_FQ_NUM(MCANx);
            u32ElementSize = MCAN_TX_ES(MCANx);
            for (i = 0U; i < u32ElementNum; i++) {
                pstcAddr->pu32TxFifoQueueAddrList[i] = pstcAddr->u32TxFifoQueueStartAddr + i * u32ElementSize;
            }
        }

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief Configure a reception filter element in the message RAM according to the specified parameters
 *        in the stc_mcan_filter_t structure.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  pstcFilter             Pointer to a @ref stc_mcan_filter_t structure that
 *                                      contains the filter configuration information.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcFilter == NULL.
 * @note Call this API after message RAM configured.
 */
int32_t MCAN_FilterConfig(const CM_MCAN_TypeDef *MCANx, const stc_mcan_filter_t *pstcFilter)
{
    uint32_t u32F0;
    uint32_t u32F1;
    uint32_t *pu32FilterMem;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (pstcFilter != NULL) {
        i32Ret = LL_OK;
        DDL_ASSERT(IS_MCAN_ID_TYPE(pstcFilter->u32IdType));
        DDL_ASSERT(IS_MCAN_FILTER_CFG(pstcFilter->u32FilterConfig));
        if (pstcFilter->u32FilterConfig == MCAN_FILTER_TO_RX_BUF) {
            DDL_ASSERT(pstcFilter->u32RxBufferIndex < MCAN_GetRxBufferNum(MCANx));
        }

        /* Build filter configuration value */
        if (pstcFilter->u32IdType == MCAN_STD_ID) {
            /* Configures the standard ID filter element */
            DDL_ASSERT(pstcFilter->u32FilterIndex < MCAN_GET_STD_FILTER_NUM(MCANx));
            DDL_ASSERT(IS_MCAN_STD_ID_VAL(pstcFilter->u32FilterId1));

            /* Build the filter element */
            if (pstcFilter->u32FilterConfig == MCAN_FILTER_TO_RX_BUF) {
                u32F0 = ((pstcFilter->u32FilterConfig << MCAN_FILTER_SFCFG_POS) | \
                         (pstcFilter->u32FilterId1 << MCAN_FILTER_SFID1_POS)    | \
                         pstcFilter->u32RxBufferIndex);
            } else {
                DDL_ASSERT(IS_MCAN_STD_FILTER_TYPE(pstcFilter->u32FilterType));
                DDL_ASSERT(IS_MCAN_STD_ID_VAL(pstcFilter->u32FilterId2));
                u32F0 = ((pstcFilter->u32FilterType << MCAN_FILTER_SFTYPE_POS)  | \
                         (pstcFilter->u32FilterConfig << MCAN_FILTER_SFCFG_POS) | \
                         (pstcFilter->u32FilterId1 << MCAN_FILTER_SFID1_POS)    | \
                         pstcFilter->u32FilterId2);
            }

            /* Calculate filter address */
            pu32FilterMem = (uint32_t *)(MCAN_STD_FILTER_SA(MCANx) + (pstcFilter->u32FilterIndex * MCAN_STD_FILTER_ES));

            /* Write filter element to the message RAM */
            pu32FilterMem[0] = u32F0;
        } else {
            /* Configures the extended ID filter element */
            DDL_ASSERT(pstcFilter->u32FilterIndex < MCAN_GET_EXT_FILTER_NUM(MCANx));
            DDL_ASSERT(IS_MCAN_EXT_ID_VAL(pstcFilter->u32FilterId1));

            /* Build the first word of the filter element */
            u32F0 = ((pstcFilter->u32FilterConfig << MCAN_FILTER_EFCFG_POS) | pstcFilter->u32FilterId1);

            /* Build the second word of the filter element */
            if (pstcFilter->u32FilterConfig == MCAN_FILTER_TO_RX_BUF) {
                u32F1 = pstcFilter->u32RxBufferIndex;
            } else {
                DDL_ASSERT(IS_MCAN_EXT_FILTER_TYPE(pstcFilter->u32FilterType));
                DDL_ASSERT(IS_MCAN_EXT_ID_VAL(pstcFilter->u32FilterId2));
                u32F1 = ((pstcFilter->u32FilterType << MCAN_FILTER_EFTYPE_POS) | pstcFilter->u32FilterId2);
            }

            /* Calculate filter address */
            pu32FilterMem = (uint32_t *)(MCAN_EXT_FILTER_SA(MCANx) + (pstcFilter->u32FilterIndex * MCAN_EXT_FILTER_ES));

            /* Write filter element to the message RAM */
            pu32FilterMem[0U] = u32F0;
            pu32FilterMem[1U] = u32F1;
        }
    }

    return i32Ret;
}

/**
 * @brief Configures the MCAN global filter.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in] u32StdNmfOperation      The operation of non-matching standard frame.
 *                                      This parameter can be a value of @ref MCAN_NMF_Operation
 *   @arg  MCAN_NMF_ACCEPT_IN_RX_FIFO0: Accept non-matching standard frames in Rx FIFO0.
 *   @arg  MCAN_NMF_ACCEPT_IN_RX_FIFO1: Accept non-matching standard frames in Rx FIFO1.
 *   @arg  MCAN_NMF_REJECT:             Reject all non-matching standard frames.
 * @param  [in] u32ExtNmfOperation      The operation of non-matching extended frame.
 *                                      This parameter can be a value of @ref MCAN_NMF_Operation
 *   @arg  MCAN_NMF_ACCEPT_IN_RX_FIFO0: Accept non-matching extended frames in Rx FIFO0.
 *   @arg  MCAN_NMF_ACCEPT_IN_RX_FIFO1: Accept non-matching extended frames in Rx FIFO1.
 *   @arg  MCAN_NMF_REJECT:             Reject all non-matching extended frames.
 * @param  [in] u32StdRemoteOperation   The operation of standard remote frame.
 *                                      This parameter can be a value of @ref MCAN_Remote_Frame_Operation
 *   @arg  MCAN_REMOTE_FRAME_FILTER:    Filter standard remote frames with ID.
 *   @arg  MCAN_REMOTE_FRAME_REJECT:    Reject all standard remote frames.
 * @param  [in] u32ExtRemoteOperation   The operation of extended remote frame.
 *                                      This parameter can be a value of @ref MCAN_Remote_Frame_Operation
 *   @arg  MCAN_REMOTE_FRAME_FILTER:    Filter extended remote frames with ID.
 *   @arg  MCAN_REMOTE_FRAME_REJECT:    Reject all extended remote frames.
 * @retval None
 */
void MCAN_GlobalFilterConfig(CM_MCAN_TypeDef *MCANx, \
                             uint32_t u32StdNmfOperation, uint32_t u32ExtNmfOperation, \
                             uint32_t u32StdRemoteOperation, uint32_t u32ExtRemoteOperation)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_NMF_OP(u32StdNmfOperation));
    DDL_ASSERT(IS_MCAN_NMF_OP(u32ExtNmfOperation));
    DDL_ASSERT(IS_MCAN_REMOTE_FRAME_OP(u32StdRemoteOperation));
    DDL_ASSERT(IS_MCAN_REMOTE_FRAME_OP(u32ExtRemoteOperation));

    WRITE_REG32(MCANx->GFC, ((u32StdNmfOperation << MCAN_GFC_ANFS_POS)   | \
                             (u32ExtNmfOperation << MCAN_GFC_ANFE_POS)    | \
                             (u32StdRemoteOperation << MCAN_GFC_RRFS_POS) | \
                             (u32ExtRemoteOperation << MCAN_GFC_RRFE_POS)));
}

/**
 * @brief Set the extended ID mask.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in] u32Mask                 Extended ID AND(logic AND operation) mask.
 *                                      This parameter must be a number between 0 and 0x1FFFFFFF.
 *                                      For acceptance filtering of extended frames the extended ID AND
 *                                      mask is ANDed with the message ID of a received frame. With the
 *                                      reset value of all bits set to one(0x1FFFFFFF) the mask is not active.
 * @retval None
 */
void MCAN_SetExtIDMask(CM_MCAN_TypeDef *MCANx, uint32_t u32Mask)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_EXT_ID_VAL(u32Mask));
    WRITE_REG32(MCANx->XIDAM, u32Mask);
}

/**
 * @brief Configures the Rx FIFO operation mode.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in] u32RxFifo               Rx FIFO.
 *                                      This parameter can be one of the following values:
 *   @arg  MCAN_RX_FIFO0:               Rx FIFO0
 *   @arg  MCAN_RX_FIFO1:               Rx FIFO1
 * @param  [in] u32OperationMode        Rx FIFO operation mode.
 *                                      This parameter can be one of @ref MCAN_Rx_Fifo_Operation_Mode
 *   @arg  MCAN_RX_FIFO_BLOCKING:       Rx FIFO blocking mode.
 *                                      New received message will not be stored.
 *   @arg  MCAN_RX_FIFO_OVERWRITE:      Rx FIFO overwrite mode.
 *                                      New received message will overwrite the oldest received message.
 * @retval None
 */
void MCAN_RxFifoOperationModeConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32RxFifo, uint32_t u32OperationMode)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_RX_FIFO(u32RxFifo));
    DDL_ASSERT(IS_MCAN_RX_FIFO_MD(u32OperationMode));

    if (u32RxFifo == MCAN_RX_FIFO0) {
        /* Set Rx FIFO0 operation mode */
        MODIFY_REG32(MCANx->RXF0C, MCAN_RXF0C_F0OM, u32OperationMode);
    } else {
        /* Set Rx FIFO1 operation mode */
        MODIFY_REG32(MCANx->RXF1C, MCAN_RXF1C_F1OM, u32OperationMode);
    }
}

/**
 * @brief Set the watermark of the specified FIFO.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in] u32Fifo                 FIFO that supports watermark interrupt.
 *                                      This parameter can be one of the following values:
 *   @arg  MCAN_WATERMARK_RX_FIFO0:     Rx FIFO0.
 *   @arg  MCAN_WATERMARK_RX_FIFO1:     Rx FIFO1.
 *   @arg  MCAN_WATERMARK_TX_EVT_FIFO:  Tx event FIFO.
 * @param  [in] u32Watermark            Level for FIFO watermark interrupt.
 *                                      This parameter must be a number between:
 *                                      - 0 and u32RxFifo0Num of @ref stc_mcan_msg_ram_config_t, if u32Fifo is MCAN_WATERMARK_RX_FIFO0
 *                                      - 0 and u32RxFifo1Num of @ref stc_mcan_msg_ram_config_t, if u32Fifo is MCAN_WATERMARK_RX_FIFO1
 *                                      - 0 and u32TxEventNum of @ref stc_mcan_msg_ram_config_t, if u32Fifo is MCAN_WATERMARK_TX_EVT_FIFO
 * @retval None
 * @note   Call this API after message RAM configured.
 */
void MCAN_SetFifoWatermark(CM_MCAN_TypeDef *MCANx, uint32_t u32Fifo, uint32_t u32Watermark)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_WATERMARK_FIFO(u32Fifo));

    switch (u32Fifo) {
        case MCAN_WATERMARK_RX_FIFO0:
            /* Set Rx FIFO0 watermark */
            DDL_ASSERT(u32Watermark <= MCAN_GET_RX_FIFO0_NUM(MCANx));
            MODIFY_REG32(MCANx->RXF0C, MCAN_RXF0C_F0WM, (u32Watermark << MCAN_RXF0C_F0WM_POS));
            break;

        case MCAN_WATERMARK_RX_FIFO1:
            /* Set Rx FIFO1 watermark */
            DDL_ASSERT(u32Watermark <= MCAN_GET_RX_FIFO1_NUM(MCANx));
            MODIFY_REG32(MCANx->RXF1C, MCAN_RXF1C_F1WM, (u32Watermark << MCAN_RXF1C_F1WM_POS));
            break;

        case MCAN_WATERMARK_TX_EVT_FIFO:
            /* Set Tx event FIFO watermark */
            DDL_ASSERT(u32Watermark <= MCAN_GET_TX_EVT_FIFO_NUM(MCANx));
            MODIFY_REG32(MCANx->TXEFC, MCAN_TXEFC_EFWM, (u32Watermark << MCAN_TXEFC_EFWM_POS));
            break;

        default:
            break;
    }
}

/**
 * @brief Set the start value of the message RAM watchdog counter.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in] u32StartValue           The start value of the message RAM watchdog counter.
 *                                      This parameter must be a number between 0x00 and 0xFF,
 *                                      with the reset value of 0x00 the counter is disabled.
 * @retval None
 */
void MCAN_RamWatchdogConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32StartValue)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_RAM_WDT_START_VAL(u32StartValue));

    /* Set the message RAM watchdog counter start value */
    MODIFY_REG32(MCANx->RWD, MCAN_RWD_WDC, u32StartValue);
}

/**
 * @brief Get the actual message RAM watchdog counter value.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint8_t type value of the actual message RAM watchdog counter value.
 */
uint8_t MCAN_GetRamWatchdogCountValue(const CM_MCAN_TypeDef *MCANx)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    return (uint8_t)(READ_REG32_BIT(MCANx->RWD, MCAN_RWD_WDV) >> MCAN_RWD_WDV_POS);
}

/**
 * @brief Configures MCAN timestamp.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in] u32TsPrescaler          Timestamp counter prescaler.
 *                                      This parameter must be a value between 1 and 16.
 * @retval None
 */
void MCAN_TimestampCounterConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32TsPrescaler)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_TS_PRESC(u32TsPrescaler));

    /* Set timestamp prescaler */
    MODIFY_REG32(MCANx->TSCC, MCAN_TSCC_TCP, (u32TsPrescaler - 1U) << MCAN_TSCC_TCP_POS);
}

/**
 * @brief Enable or disable the timestamp counter.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 *   @arg  ENABLE:                      Enable timestamp counter.
 *   @arg  DISABLE:                     Disable timestamp counter.
 * @retval None
 */
void MCAN_TimestampCounterCmd(CM_MCAN_TypeDef *MCANx, en_functional_state_t enNewState)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        /* Enable timestamp counter */
        SET_REG32_BIT(MCANx->TSCC, MCAN_TSCC_TSS_0);
    } else {
        /* Disable timestamp counter */
        CLR_REG32_BIT(MCANx->TSCC, MCAN_TSCC_TSS);
    }
}

/**
 * @brief Get the timestamp counter value.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint16_t type value of timestamp counter.
 */
uint16_t MCAN_GetTimestampCounter(const CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    return (uint16_t)(MCANx->TSCV);
}

/**
 * @brief Reset the timestamp counter to zero.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval None
 */
void MCAN_ResetTimestampCounter(CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    /* Reset timestamp counter. */
    CLR_REG32(MCANx->TSCV);
}

/**
 * @brief Set the watermark of the specified FIFO.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in] u32ToSelect             Timeout select.
 *                                      This parameter can be one of @ref MCAN_Timeout_Select
 *   @arg  MCAN_TIMEOUT_CONT:           Timeout continuous operation.
 *   @arg  MCAN_TIMEOUT_TX_EVT_FIFO:    Timeout controlled by Tx event FIFO.
 *   @arg  MCAN_TIMEOUT_RX_FIFO0:       Timeout controlled by Rx FIFO0.
 *   @arg  MCAN_TIMEOUT_RX_FIFO1:       Timeout controlled by Rx FIFO1.
 * @param  [in] u32ToPeriod             Start value of the timeout counter.Configures the Timeout Period.
 *                                      This parameter must be a number between 0x0000 and 0xFFFF
 * @retval None
 */
void MCAN_TimeoutCounterConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32ToSelect, uint32_t u32ToPeriod)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_TO_SEL(u32ToSelect));
    DDL_ASSERT(IS_MCAN_TO_PERIOD(u32ToPeriod));

    /* Select timeout operation and configure period */
    MODIFY_REG32(MCANx->TOCC, (MCAN_TOCC_TOS | MCAN_TOCC_TOP),
                 (u32ToSelect | (u32ToPeriod << MCAN_TOCC_TOP_POS)));
}

/**
 * @brief Enable or disable the timeout counter.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 *   @arg  ENABLE:                      Enable timeout counter.
 *   @arg  DISABLE:                     Disable timeout counter.
 * @retval None
 */
void MCAN_TimeoutCounterCmd(CM_MCAN_TypeDef *MCANx, en_functional_state_t enNewState)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        /* Enable timeout counter */
        SET_REG32_BIT(MCANx->TOCC, MCAN_TOCC_ETOC);
    } else {
        /* Disable timeout counter */
        CLR_REG32_BIT(MCANx->TOCC, MCAN_TOCC_ETOC);
    }
}

/**
 * @brief Get the timeout counter value.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint16_t type value of timeout counter.
 */
uint16_t MCAN_GetTimeoutCounter(const CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    return (uint16_t)(MCANx->TOCV);
}

/**
 * @brief Reset the timeout counter to its start value.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval None
 */
void MCAN_ResetTimeoutCounter(CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (READ_REG32_BIT(MCANx->TOCC, MCAN_TOCC_TOS) == MCAN_TIMEOUT_CONT) {
        /* Reset timeout counter to start value */
        CLR_REG32(MCANx->TOCV);
    }
}

/**
 * @brief Configure the transmitter delay compensation
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32SspOffset           Transmitter delay compensation offset.
 * @param  [in]  u32TdcFilter           Transmitter delay compensation filter window length.
 *                                      This parameter must be a number between 0x00 and 0x7F
 * @retval None
 */
void MCAN_TxDelayCompensationConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32SspOffset, uint32_t u32TdcFilter)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_SSP(u32SspOffset));
    DDL_ASSERT(IS_MCAN_TDC_FILTER(u32TdcFilter));

    /* Configure TDC offset and filter window */
    WRITE_REG32(MCANx->TDCR, ((u32SspOffset << MCAN_TDCR_TDCO_POS) | (u32TdcFilter << MCAN_TDCR_TDCF_POS)));
}

/**
 * @brief Enable or disable the transmitter delay compensation.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 *   @arg  ENABLE:                      Enable transmitter delay compensation.
 *   @arg  DISABLE:                     Disable transmitter delay compensation.
 * @retval None
 */
void MCAN_TxDelayCompensationCmd(CM_MCAN_TypeDef *MCANx, en_functional_state_t enNewState)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        /* Enable transmitter delay compensation */
        SET_REG32_BIT(MCANx->DBTP, MCAN_DBTP_TDC);
    } else {
        /* Disable transmitter delay compensation */
        CLR_REG32_BIT(MCANx->DBTP, MCAN_DBTP_TDC);
    }
}

/**
 * @brief Specifies the CAN frame format.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32FrameFormat         CAN frame format.
 *                                      This parameter can be a value of @ref MCAN_Frame_Format
 *   @arg  MCAN_FRAME_CLASSIC:          Classic CAN mode.
 *   @arg  MCAN_FRAME_ISO_FD_NO_BRS:    ISO CAN FD mode without bit rate switching.
 *   @arg  MCAN_FRAME_ISO_FD_BRS:       ISO CAN FD mode with bit rate switching.
 *   @arg  MCAN_FRAME_NON_ISO_FD_NO_BRS: Non-ISO CAN FD mode without bit rate switching.
 *   @arg  MCAN_FRAME_NON_ISO_FD_BRS:   Non-ISO CAN FD mode with bit rate switching.
 * @retval None
 */
void MCAN_SetFrameFormat(CM_MCAN_TypeDef *MCANx, uint32_t u32FrameFormat)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_FRAME_FORMAT(u32FrameFormat));

    MODIFY_REG32(MCANx->CCCR, MCAN_FRAME_NON_ISO_FD_BRS, u32FrameFormat);
}

/**
 * @brief Enable or disable the edge filtering during bus integration.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 *   @arg  ENABLE:                      Enable edge filtering.
 *   @arg  DISABLE:                     Disable edge filtering.
 * @retval None
 */
void MCAN_EdgeFilteringCmd(CM_MCAN_TypeDef *MCANx, en_functional_state_t enNewState)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        /* Enable edge filtering */
        SET_REG32_BIT(MCANx->CCCR, MCAN_CCCR_EFBI);
    } else {
        /* Disable edge filtering */
        CLR_REG32_BIT(MCANx->CCCR, MCAN_CCCR_EFBI);
    }
}

/**
 * @brief Config message marker for Tx event
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32MsgMarker           Message marker configuration.
 *   @arg  MCAN_MSG_MARKER_8BIT:        8-bit message marker used.
 *   @arg  MCAN_MSG_MARKER_16BIT:       16-bit Message Marker used, replacing 16-bit timestamps in Tx Event FIFO.
 * @retval None
 */
void MCAN_TxEventMsgMarkerConfig(CM_MCAN_TypeDef *MCANx, uint32_t u32MsgMarker)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_MSG_MARKER_CFG(u32MsgMarker));

    MODIFY_REG32(MCANx->CCCR, MCAN_CCCR_WMM, u32MsgMarker);
}

/**
 * @brief Add a message to the Tx FIFO/Queue and activate the corresponding transmission request.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  pTxMsg                 Pointer to a @ref stc_mcan_tx_msg_t structure that contains
 *                                      the information of the message that to be transmitted.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pTxMsg == NULL.
 *                                      Tx FIFO/queue has an allocated area into the message RAM.
 *                                      Size of the message data payload is bigger than the configured value.
 *           - LL_ERR_BUF_FULL:         Tx FIFO/queue is full.
 */
int32_t MCAN_AddMsgToTxFifoQueue(CM_MCAN_TypeDef *MCANx, stc_mcan_tx_msg_t *pTxMsg)
{
    uint32_t u32TxPutIndex;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    if (pTxMsg != NULL) {
        DDL_ASSERT(IS_MCAN_ID_TYPE(pTxMsg->IDE));
        if (pTxMsg->IDE == MCAN_STD_ID) {
            DDL_ASSERT(IS_MCAN_STD_ID_VAL(pTxMsg->ID));
        } else {
            DDL_ASSERT(IS_MCAN_EXT_ID_VAL(pTxMsg->ID));
        }
        DDL_ASSERT(IS_MCAN_FRAME_RTR(pTxMsg->RTR));
        DDL_ASSERT(IS_MCAN_FRAME_DLC(pTxMsg->DLC));
        DDL_ASSERT(IS_MCAN_FRAME_ESI(pTxMsg->ESI));
        DDL_ASSERT(IS_MCAN_FRAME_BRS(pTxMsg->BRS));
        DDL_ASSERT(IS_MCAN_FRAME_FDF(pTxMsg->FDF));
        DDL_ASSERT(IS_MCAN_FRAME_EFC(pTxMsg->u32StoreTxEvent));
        u32TxPutIndex = READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_WMM);
        DDL_ASSERT(IS_MCAN_FRAME_MSG_MARKER(u32TxPutIndex, pTxMsg->u32MsgMarker));

        /* Check that the Tx FIFO/Queue has an allocated area into the message RAM.
           Check that the data field size is not bigger than the configured value. */
        if (READ_REG32_BIT(MCANx->TXBC, MCAN_TXBC_TFQS) != 0U) {
            /* Check that the Tx FIFO/queue is not full */
            if (READ_REG32_BIT(MCANx->TXFQS, MCAN_TXFQS_TFQF) == 0U) {
                /* Retrieve the Tx FIFO put index */
                u32TxPutIndex = (READ_REG32_BIT(MCANx->TXFQS, MCAN_TXFQS_TFQPI) >> MCAN_TXFQS_TFQPI_POS);

                /* Add the message to the Tx FIFO/Queue */
                MCAN_CopyTxMsgToRam(MCANx, pTxMsg, u32TxPutIndex);

                /* Store the last Tx FIFO/queue request buffer index. */
                pTxMsg->u32LastTxFifoQueueRequest = 1UL << u32TxPutIndex;
                /* Activate the corresponding transmission request. */
                WRITE_REG32(MCANx->TXBAR, pTxMsg->u32LastTxFifoQueueRequest);

                i32Ret = LL_OK;
            } else {
                i32Ret = LL_ERR_BUF_FULL;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief Add a message to a dedicated Tx buffer.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  pTxMsg                 Pointer to a @ref stc_mcan_tx_msg_t structure that contains
 *                                      the information of the message that to be transmitted.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pTxMsg == NULL.
 *                                      The selected buffer has no allocated area into the message RAM.
 *                                      Size of the message data payload is bigger than the configured value.
 *           - LL_ERR_BUSY:             There is a transmission request pending for the selected buffer.
 */
int32_t MCAN_AddMsgToTxBuffer(CM_MCAN_TypeDef *MCANx, stc_mcan_tx_msg_t *pTxMsg)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    uint32_t u32TxPutIndex;
    uint32_t u32TxBufferNum;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    if (pTxMsg != NULL) {
        DDL_ASSERT(IS_MCAN_ID_TYPE(pTxMsg->IDE));
        if (pTxMsg->IDE == MCAN_STD_ID) {
            DDL_ASSERT(IS_MCAN_STD_ID_VAL(pTxMsg->ID));
        } else {
            DDL_ASSERT(IS_MCAN_EXT_ID_VAL(pTxMsg->ID));
        }
        DDL_ASSERT(IS_MCAN_FRAME_RTR(pTxMsg->RTR));
        DDL_ASSERT(IS_MCAN_FRAME_DLC(pTxMsg->DLC));
        DDL_ASSERT(IS_MCAN_FRAME_ESI(pTxMsg->ESI));
        DDL_ASSERT(IS_MCAN_FRAME_BRS(pTxMsg->BRS));
        DDL_ASSERT(IS_MCAN_FRAME_FDF(pTxMsg->FDF));
        DDL_ASSERT(IS_MCAN_FRAME_EFC(pTxMsg->u32StoreTxEvent));
        u32TxPutIndex = READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_WMM);
        DDL_ASSERT(IS_MCAN_FRAME_MSG_MARKER(u32TxPutIndex, pTxMsg->u32MsgMarker));
        DDL_ASSERT(IS_MCAN_1TXBUF(pTxMsg->u32TxBuffer));
        u32TxBufferNum = MCAN_GET_TX_BUF_NUM(MCANx);
        u32TxPutIndex  = GET_BIT_POS(pTxMsg->u32TxBuffer);
        DDL_ASSERT(u32TxPutIndex < u32TxBufferNum);

        /* Check that the selected buffer has an allocated area into the message RAM.
           Check that the data field size is not bigger than the configured value. */
        if (u32TxPutIndex < u32TxBufferNum) {
            /* Check that there is no transmission request pending for the selected buffer */
            if (READ_REG32_BIT(MCANx->TXBRP, pTxMsg->u32TxBuffer) == 0U) {
                /* Add the message to the Tx buffer */
                MCAN_CopyTxMsgToRam(MCANx, pTxMsg, u32TxPutIndex);
                i32Ret = LL_OK;
            } else {
                i32Ret = LL_ERR_BUSY;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief Enable transmission request of the specified Tx buffer(s).
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32TxBuffer            Tx buffer(s) location.
 *                                      This parameter can be any combination of @ref MCAN_Tx_Location
 * @retval None
 */
void MCAN_EnableTxBufferRequest(CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer)
{
#ifdef __DEBUG
    uint32_t u32TxBufferNum;
#endif
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
#ifdef __DEBUG
    u32TxBufferNum  = MCAN_GET_TX_BUF_NUM(MCANx);
    u32TxBufferNum += MCAN_GET_TX_FQ_NUM(MCANx);
    if (u32TxBufferNum < MCAN_TX_ELMT_NUM_MAX) {
        DDL_ASSERT(IS_MCAN_BIT_MASK(u32TxBuffer, (1UL << u32TxBufferNum) - 1U));
    }
#endif

    /* Add transmission request */
    WRITE_REG32(MCANx->TXBAR, u32TxBuffer);
}

/**
 * @brief Abort the transmission request of the specified Tx buffer(s).
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32TxBuffer            Tx buffer(s) location.
 *                                      This parameter can be any combination of @ref MCAN_Tx_Location
 * @retval None
 */
void MCAN_AbortTxRequest(CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer)
{
#ifdef __DEBUG
    uint32_t u32TxBufferNum;
#endif
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
#ifdef __DEBUG
    u32TxBufferNum  = MCAN_GET_TX_BUF_NUM(MCANx);
    u32TxBufferNum += MCAN_GET_TX_FQ_NUM(MCANx);
    if (u32TxBufferNum < MCAN_TX_ELMT_NUM_MAX) {
        DDL_ASSERT(IS_MCAN_BIT_MASK(u32TxBuffer, (1UL << u32TxBufferNum) - 1U));
    }
#endif

    /* Add cancellation request */
    WRITE_REG32(MCANx->TXBCR, u32TxBuffer);
}

/**
 * @brief Get a received frame from the Rx buffer/FIFO zone into the message RAM.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32RxLocation          Location of the received message to be read.
 *                                      This parameter can be a value of @ref MCAN_Rx_Location
 * @param  [out] pRxMsg                 Pointer to a @ref stc_mcan_rx_msg_t structure which is used to save
 *                                      the received frame.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pRxMsg == NULL;
 *                                      The selected Rx FIFO has no allocated area into the message RAM;
 *                                      The selected Rx buffer is out of range.
 *           - LL_ERR_BUF_EMPTY:        The selected Rx FIFO is empty.
 */
int32_t MCAN_GetRxMsg(CM_MCAN_TypeDef *MCANx, uint32_t u32RxLocation, stc_mcan_rx_msg_t *pRxMsg)
{
    uint32_t i;
    uint32_t u32RxRamAddr = 0U;
    uint32_t u32Tmp;
    uint32_t u32DataFiledSize = 0U;
    uint32_t u32RxGetIndex = 0U;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (pRxMsg != NULL) {
        i32Ret = LL_OK;
        if (u32RxLocation == MCAN_RX_FIFO0) {
            /* Check that the Rx FIFO0 has an allocated area into the message RAM */
            if (READ_REG32_BIT(MCANx->RXF0C, MCAN_RXF0C_F0S) == 0U) {
                i32Ret = LL_ERR_INVD_PARAM;
            }

            if (i32Ret == LL_OK) {
                /* Check that the Rx FIFO0 is not empty */
                if (READ_REG32_BIT(MCANx->RXF0S, MCAN_RXF0S_F0FL) == 0U) {
                    i32Ret = LL_ERR_BUF_EMPTY;
                }
            }

            if (i32Ret == LL_OK) {
                /* Calculate Rx FIFO0 element index*/
                u32RxGetIndex = (READ_REG32_BIT(MCANx->RXF0S, MCAN_RXF0S_F0GI) >> MCAN_RXF0S_F0GI_POS);

                /* Calculate Rx FIFO0 element address */
                u32RxRamAddr  = MCAN_RX_FIFO0_SA(MCANx);
                u32RxRamAddr += (u32RxGetIndex * MCAN_RX_FIFO0_ES(MCANx));

                /* Get the configured data filed size of Rx FIFO0 */
                u32DataFiledSize = MCAN_RX_FIFO0_REAL_DS(MCANx);
            }
        } else if (u32RxLocation == MCAN_RX_FIFO1) {
            /* Check that the Rx FIFO1 has an allocated area into the message RAM */
            if (READ_REG32_BIT(MCANx->RXF1C, MCAN_RXF1C_F1S) == 0U) {
                i32Ret = LL_ERR_INVD_PARAM;
            }

            if (i32Ret == LL_OK) {
                /* Check that the Rx FIFO1 is not empty */
                if (READ_REG32_BIT(MCANx->RXF1S, MCAN_RXF1S_F1FL) == 0U) {
                    i32Ret = LL_ERR_BUF_EMPTY;
                }
            }

            if (i32Ret == LL_OK) {
                /* Calculate Rx FIFO1 element index */
                u32RxGetIndex = (READ_REG32_BIT(MCANx->RXF1S, MCAN_RXF1S_F1GI) >> MCAN_RXF1S_F1GI_POS);

                /* Calculate Rx FIFO1 element address */
                u32RxRamAddr  = MCAN_RX_FIFO1_SA(MCANx);
                u32RxRamAddr += (u32RxGetIndex * MCAN_RX_FIFO1_ES(MCANx));

                /* Get the configured data filed size of Rx FIFO1 */
                u32DataFiledSize = MCAN_RX_FIFO1_REAL_DS(MCANx);
            }
        } else {
            /* Rx element is assigned to a dedicated Rx buffer.
               Check that the selected buffer has an allocated area into the message RAM. */
            if (u32RxLocation >= MCAN_GetRxBufferNum(MCANx)) {
                i32Ret = LL_ERR_INVD_PARAM;
            } else {
                /* Calculate Rx buffer address */
                u32RxRamAddr  = MCAN_RX_BUF_SA(MCANx);
                u32RxRamAddr += (u32RxLocation * MCAN_RX_BUF_ES(MCANx));

                /* Get the configured data filed size of Rx buffer */
                u32DataFiledSize = MCAN_RX_BUF_REAL_DS(MCANx);
            }
        }

        if (i32Ret == LL_OK) {
            /* Retrieve ID type */
            pRxMsg->IDE = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_XTD_MASK) >> MCAN_FRAME_XTD_POS;
            /* Retrieve ID type */
            if (pRxMsg->IDE == MCAN_STD_ID) {
                /* Standard ID element */
                pRxMsg->ID = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_STDID_MASK) >> MCAN_FRAME_STDID_POS;
            } else {
                /* Extended ID element */
                pRxMsg->ID = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_EXTID_MASK);
            }

            /* Retrieve Rx frame type */
            pRxMsg->RTR = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_RTR_MASK) >> MCAN_FRAME_RTR_POS;

            /* Retrieve ESI */
            pRxMsg->ESI = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_ESI_MASK) >> MCAN_FRAME_ESI_POS;

            /* Increment Rx memory pointer to second word of Rx FIFO element */
            u32RxRamAddr += 4UL;

            /* Retrieve Rx timestamp */
            pRxMsg->u32RxTimestamp = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_TS_MASK);

            /* Retrieve DLC */
            pRxMsg->DLC = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_DLC_MASK) >> MCAN_FRAME_DLC_POS;
            pRxMsg->u32DataSize = m_au8DLC2Size[pRxMsg->DLC];

            /* Retrieve BRS */
            pRxMsg->BRS = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_BRS_MASK) >> MCAN_FRAME_BRS_POS;

            /* Retrieve FDF */
            pRxMsg->FDF = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_FDF_MASK) >> MCAN_FRAME_FDF_POS;
            /* Determine the CAN frame format: classical CAN or FD CAN */
            if (pRxMsg->FDF == 0U) {
                /* Max 8 bytes for classical CAN */
                if (pRxMsg->u32DataSize > CAN20_DATA_SIZE_MAX) {
                    pRxMsg->u32DataSize = CAN20_DATA_SIZE_MAX;
                }
            } else {
                /* Max size of the stored data is the allocated size */
                if (pRxMsg->u32DataSize > u32DataFiledSize) {
                    pRxMsg->u32DataSize = u32DataFiledSize;
                }
            }

            /* Retrieve filter index */
            pRxMsg->u32FilterIndex = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_FIDX_MASK) >> MCAN_FRAME_FIDX_POS;

            /* Retrieve non-matching frame */
            pRxMsg->u32NmfFlag = READ_REG32_BIT(RW_MEM32(u32RxRamAddr), MCAN_FRAME_ANMF_MASK) >> MCAN_FRAME_ANMF_POS;

            /* Increment Rx memory pointer to payload of Rx FIFO element */
            /* Retrieve Rx payload */
            if (pRxMsg->RTR == 0U) {
                /* Read the Rx payload from the message RAM. */
                for (i = 0U; i < pRxMsg->u32DataSize; i += 4U) {
                    u32RxRamAddr += 4U;
                    u32Tmp = RW_MEM32(u32RxRamAddr);
                    pRxMsg->au8Data[i]      = (uint8_t)(u32Tmp);
                    pRxMsg->au8Data[i + 1U] = (uint8_t)(u32Tmp >> 8U);
                    pRxMsg->au8Data[i + 2U] = (uint8_t)(u32Tmp >> 16U);
                    pRxMsg->au8Data[i + 3U] = (uint8_t)(u32Tmp >> 24U);
                }
            }

            if (u32RxLocation == MCAN_RX_FIFO0) {
                /* Rx element is assigned to the Rx FIFO0.
                   Acknowledge the Rx FIFO0 that the oldest element
                   is read so that it increments the get index. */
                WRITE_REG32(MCANx->RXF0A, u32RxGetIndex);
            } else if (u32RxLocation == MCAN_RX_FIFO1) {
                /* Rx element is assigned to the Rx FIFO1.
                   Acknowledge the Rx FIFO1 that the oldest element
                   is read so that it increments the get index. */
                WRITE_REG32(MCANx->RXF1A, u32RxGetIndex);
            } else {
                /* Rx element is assigned to a dedicated Rx buffer.
                   Clear the new data flag of the current Rx buffer. */
                if (u32RxLocation < MCAN_RX_BUF32) {
                    WRITE_REG32(MCANx->NDAT1, (1UL << u32RxLocation));
                } else {
                    WRITE_REG32(MCANx->NDAT2, (1UL << (u32RxLocation & 0x1FUL)));
                }
            }
        }
    }

    return i32Ret;
}

/**
 * @brief Get a Tx event from the Tx event FIFO zone into the message RAM.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [out] pTxEvent               Pointer to a @ref stc_mcan_tx_event_t structure which is used to save
 *                                      the Tx event.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pTxEvent == NULL;
 *           - LL_ERR_BUF_EMPTY:        The Tx event FIFO is empty.
 */
int32_t MCAN_GetTxEvent(CM_MCAN_TypeDef *MCANx, stc_mcan_tx_event_t *pTxEvent)
{
    uint32_t u32TxEventAddr;
    uint32_t u32GetIndex;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (pTxEvent != NULL) {
        i32Ret = LL_OK;

        /* Check that the Tx Event FIFO has an allocated area into the message RAM */
        if (READ_REG32_BIT(MCANx->TXEFC, MCAN_TXEFC_EFS) == 0U) {
            /* The Tx event has no allocated area into the message RAM. */
            i32Ret = LL_ERR_INVD_PARAM;
        }

        /* Check that the Tx event FIFO is not empty */
        if (i32Ret == LL_OK) {
            if (READ_REG32_BIT(MCANx->TXEFS, MCAN_TXEFS_EFFL) == 0U) {
                /* The Tx event FIFO is empty */
                i32Ret = LL_ERR_BUF_EMPTY;
            }
        }

        if (i32Ret == LL_OK) {
            /* Calculate Tx event FIFO element address */
            u32GetIndex = READ_REG32_BIT(MCANx->TXEFS, MCAN_TXEFS_EFGI) >> MCAN_TXEFS_EFGI_POS;
            u32TxEventAddr = MCAN_TX_EVT_FIFO_SA(MCANx) + (u32GetIndex * MCAN_TX_EVT_ES);

            /* Retrieve ID type */
            pTxEvent->IDE = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_XTD_MASK) >> MCAN_FRAME_XTD_POS;

            /* Retrieve ID */
            if (pTxEvent->IDE == MCAN_STD_ID) {
                /* Standard ID element */
                pTxEvent->ID = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_STDID_MASK) >> MCAN_FRAME_STDID_POS;
            } else {
                /* Extended ID element */
                pTxEvent->ID = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_EXTID_MASK);
            }

            /* Retrieve Tx frame type */
            pTxEvent->RTR = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_RTR_MASK) >> MCAN_FRAME_RTR_POS;

            /* Retrieve ESI */
            pTxEvent->ESI = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_ESI_MASK) >> MCAN_FRAME_ESI_POS;

            /* Increment Tx event memory pointer to second word of Tx event FIFO element */
            u32TxEventAddr += 4UL;

            /* Retrieve DLC */
            pTxEvent->DLC = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_DLC_MASK) >> MCAN_FRAME_DLC_POS;

            /* Retrieve BRS */
            pTxEvent->BRS = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_BRS_MASK) >> MCAN_FRAME_BRS_POS;

            /* Retrieve FDF */
            pTxEvent->FDF = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_FDF_MASK) >> MCAN_FRAME_FDF_POS;

            /* Retrieve event type */
            pTxEvent->u32EventType = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_ET_MASK) >> MCAN_FRAME_ET_POS;

            /* Retrieve message marker */
            pTxEvent->u32MsgMarker = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_MM_L_MASK) >> MCAN_FRAME_MM_L_POS;
            /* If 16-bit(wide) message marker used */
            if (READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_WMM) != 0U) {
                pTxEvent->u32MsgMarker |= READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_MM_H_MASK);
            } else {
                /* Retrieve Tx timestamp. It is invalid if 16-bit(wide) message marker used. */
                pTxEvent->u32TxTimestamp = READ_REG32_BIT(RW_MEM32(u32TxEventAddr), MCAN_FRAME_TS_MASK);
            }

            /* Acknowledge the Tx event FIFO that the oldest element is
               read so that it increments the get index. */
            WRITE_REG32(MCANx->TXEFA, u32GetIndex);
        }
    }

    return i32Ret;
}

/**
 * @brief Get high priority message status.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [out] pHpmStatus             Pointer to a @ref stc_mcan_hpm_status_t structure which is used to save
 *                                      the status of the high priority message.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pHpmStatus == NULL.
 */
int32_t MCAN_GetHighPriorityMsgStatus(const CM_MCAN_TypeDef *MCANx, stc_mcan_hpm_status_t *pHpmStatus)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (pHpmStatus != NULL) {
        pHpmStatus->u8FilterListType = (uint8_t)(READ_REG32_BIT(MCANx->HPMS, MCAN_HPMS_FLST) >> MCAN_HPMS_FLST_POS);
        pHpmStatus->u8FilterIndex    = (uint8_t)(READ_REG32_BIT(MCANx->HPMS, MCAN_HPMS_FIDX) >> MCAN_HPMS_FIDX_POS);
        pHpmStatus->u8MsgStorage     = (uint8_t)(READ_REG32_BIT(MCANx->HPMS, MCAN_HPMS_MSI) >> MCAN_HPMS_MSI_POS);
        pHpmStatus->u8MsgIndex       = (uint8_t)READ_REG32_BIT(MCANx->HPMS, MCAN_HPMS_BIDX);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief Get protocol status.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [out] pProtocolStatus        Pointer to a @ref stc_mcan_protocol_status_t structure which is used to save
 *                                      the protocol status.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pProtocolStatus == NULL.
 */
int32_t MCAN_GetProtocolStatus(const CM_MCAN_TypeDef *MCANx, stc_mcan_protocol_status_t *pProtocolStatus)
{
    uint32_t u32Status;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (pProtocolStatus != NULL) {
        /* Read the protocol status register */
        u32Status = READ_REG32(MCANx->PSR);

        /* Fill the protocol status structure */
        pProtocolStatus->u8LastErrorCode         = (uint8_t)(u32Status & MCAN_PSR_LEC);
        pProtocolStatus->u8DataLastErrorCode     = (uint8_t)((u32Status & MCAN_PSR_DLEC) >> MCAN_PSR_DLEC_POS);
        pProtocolStatus->u8ComState              = (uint8_t)((u32Status & MCAN_PSR_ACT) >> MCAN_PSR_ACT_POS);
        pProtocolStatus->u8ErrorPassiveFlag      = (uint8_t)((u32Status & MCAN_PSR_EP) >> MCAN_PSR_EP_POS);
        pProtocolStatus->u8WarningFlag           = (uint8_t)((u32Status & MCAN_PSR_EW) >> MCAN_PSR_EW_POS);
        pProtocolStatus->u8BusOffFlag            = (uint8_t)((u32Status & MCAN_PSR_BO) >> MCAN_PSR_BO_POS);
        pProtocolStatus->u8RxESIFlag             = (uint8_t)((u32Status & MCAN_PSR_RESI) >> MCAN_PSR_RESI_POS);
        pProtocolStatus->u8RxBRSFlag             = (uint8_t)((u32Status & MCAN_PSR_RBRS) >> MCAN_PSR_RBRS_POS);
        pProtocolStatus->u8RxFDFFlag             = (uint8_t)((u32Status & MCAN_PSR_RFDF) >> MCAN_PSR_RFDF_POS);
        pProtocolStatus->u8ProtocolExceptionFlag = (uint8_t)((u32Status & MCAN_PSR_PXE) >> MCAN_PSR_PXE_POS);
        pProtocolStatus->u8TdcValue              = (uint8_t)((u32Status & MCAN_PSR_TDCV) >> MCAN_PSR_TDCV_POS);

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief Get the TDC value that used by CAN FD frame transmission.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint8_t value between 0~127.
 */
uint8_t MCAN_GetTdcValue(const CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    return (uint8_t)(READ_REG32_BIT(MCANx->PSR, MCAN_PSR_TDCV) >> MCAN_PSR_TDCV_POS);
}

/**
 * @brief Get the last error code of data phase(data bit time used).
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint8_t value of @ref MCAN_Protocol_Error_Code
 */
uint8_t MCAN_GetDataLastErrorCode(const CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    return (uint8_t)(READ_REG32_BIT(MCANx->PSR, MCAN_PSR_DLEC) >> MCAN_PSR_DLEC_POS);
}

/**
 * @brief Get the last error code of classical CAN frame or CAN FD frame arbitraion phase(nominal bit time used).
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint8_t value of @ref MCAN_Protocol_Error_Code
 */
uint8_t MCAN_GetLastErrorCode(const CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    return (uint8_t)READ_REG32_BIT(MCANx->PSR, MCAN_PSR_LEC);
}

/**
 * @brief Get the communication state.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint8_t value of @ref MCAN_Com_State
 */
uint8_t MCAN_GetComState(const CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    return (uint8_t)(READ_REG32_BIT(MCANx->PSR, MCAN_PSR_ACT) >> MCAN_PSR_ACT_POS);
}

/**
 * @brief Get the status of the specified protocol flag.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32PsFlag              Protocol flag.
 *                                      This parameter can be any combination of @ref MCAN_Protocol_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t MCAN_GetProtocolFlagStatus(const CM_MCAN_TypeDef *MCANx, uint32_t u32PsFlag)
{
    en_flag_status_t enStatus = RESET;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_PS_FLAG(u32PsFlag));

    if (READ_REG32_BIT(MCANx->PSR, u32PsFlag) != 0U) {
        /* Return SET if one the specified flags is SET. */
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief Get error counter values.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [out] pErrorCounter          Pointer to a @ref stc_mcan_error_counter_t structure which is used to save
 *                                      the error counter values.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pErrorCounter == NULL.
 */
int32_t MCAN_GetErrorCounter(const CM_MCAN_TypeDef *MCANx, stc_mcan_error_counter_t *pErrorCounter)
{
    uint32_t u32Counter;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (pErrorCounter != NULL) {
        /* Read the error counters register */
        u32Counter = READ_REG32(MCANx->ECR);

        /* Fill the error counters structure */
        pErrorCounter->u8TxErrorCount   = (uint8_t)(u32Counter & MCAN_ECR_TEC);
        pErrorCounter->u8RxErrorCount   = (uint8_t)((u32Counter & MCAN_ECR_REC) >> MCAN_ECR_REC_POS);
        pErrorCounter->u8RxErrorPassive = (uint8_t)((u32Counter & MCAN_ECR_RP) >> MCAN_ECR_RP_POS);
        pErrorCounter->u8ErrorLogging   = (uint8_t)((u32Counter & MCAN_ECR_CEL) >> MCAN_ECR_CEL_POS);

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief Get the status of the specified interrupt flag.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32Flag                MCAN interrupt flag.
 *                                      This parameter can be any combination of @ref MCAN_Interrupt_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t MCAN_GetStatus(const CM_MCAN_TypeDef *MCANx, uint32_t u32Flag)
{
    en_flag_status_t enStatus = RESET;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_FLAG(u32Flag));

    if (READ_REG32_BIT(MCANx->IR, u32Flag) != 0U) {
        /* Return SET if one the specified flags is SET. */
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief Clear the specified interrupt flag.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32Flag                MCAN interrupt flag.
 *                                      This parameter can be any combination of @ref MCAN_Interrupt_Flag
 * @retval None
 */
void MCAN_ClearStatus(CM_MCAN_TypeDef *MCANx, uint32_t u32Flag)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_FLAG(u32Flag));

    WRITE_REG32(MCANx->IR, u32Flag);
}

/**
 * @brief Get the transmission occurred buffer list.
 *        Each Tx buffer has its own transmission occurred bit. The bits are set when the corresponding
 *        TXBRP bit is cleared after a successful transmission.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint32_t type value.
 */
uint32_t MCAN_GetTxOccurredList(const CM_MCAN_TypeDef *MCANx)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    return READ_REG32(MCANx->TXBTO);
}

/**
 * @brief Get the cancellation occurred buffer list.
 *        Each Tx buffer has its own cancellation finished bit. The bits are set when the corresponding
 *        TXBRP bit is cleared after a cancellation was requested via TXBCR.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint32_t type value.
 */
uint32_t MCAN_GetTxAbortedList(const CM_MCAN_TypeDef *MCANx)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    return READ_REG32(MCANx->TXBCF);
}

/**
 * @brief Check if the transmission of the specified Tx buffer has occurred.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32TxBuffer            A Tx buffer.
 *                                      This parameter can be a value of @ref MCAN_Tx_Location
 * @retval int32_t:
 *           - LL_OK:                   The transmission of the specified Tx buffer has occurred.
 *           - LL_ERR_BUSY:             The transmission of the specified Tx buffer has not occurred.
 */
int32_t MCAN_CheckTxOccurred(const CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer)
{
    int32_t i32Ret = LL_ERR_BUSY;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_1TXBUF(u32TxBuffer));

    if (READ_REG32_BIT(MCANx->TXBTO, u32TxBuffer) != 0U) {
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief Check if the cancellation of the specified Tx buffer has occurred.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32TxBuffer            A Tx buffer.
 *                                      This parameter can be a value of @ref MCAN_Tx_Location
 * @retval int32_t:
 *           - LL_OK:                   The cancellation of the specified Tx buffer has occurred.
 *           - LL_ERR_BUSY:             The cancellation of the specified Tx buffer has not occurred.
 */
int32_t MCAN_CheckTxAborted(const CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer)
{
    int32_t i32Ret = LL_ERR_BUSY;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_1TXBUF(u32TxBuffer));

    if (READ_REG32_BIT(MCANx->TXBCF, u32TxBuffer) != 0U) {
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief Check if a new message is received in the selected Rx buffer.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32RxBufferIndex       Rx buffer index.
 *                                      This parameter must be a number between 0 and 63(MCAN_RX_BUF0~MCAN_RX_BUF63 of @ref MCAN_Rx_Location).
 * @retval int32_t:
 *           - LL_OK:                   A new message is received in the selected Rx buffer.
 *           - LL_ERR_INVD_PARAM:       u32RxBufferIndex is larger than the number of Rx buffer that allocated into the message RAM.
 *           - LL_ERR_BUF_EMPTY:        The selected Rx buffer is empty.
 */
int32_t MCAN_CheckRxBufferMsgAvailable(CM_MCAN_TypeDef *MCANx, uint32_t u32RxBufferIndex)
{
    uint32_t u32RxBufferNum;
    uint32_t u32RxBufferMask;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    u32RxBufferNum = MCAN_GetRxBufferNum(MCANx);
    DDL_ASSERT(u32RxBufferIndex < u32RxBufferNum);

    if (u32RxBufferIndex < u32RxBufferNum) {
        i32Ret = LL_ERR_BUF_EMPTY;
        if (u32RxBufferIndex < 32U) {
            u32RxBufferMask = 1UL << u32RxBufferIndex;
            if (READ_REG32_BIT(MCANx->NDAT1, u32RxBufferMask) != 0U) {
                WRITE_REG32(MCANx->NDAT1, u32RxBufferMask);
                i32Ret = LL_OK;
            }
        } else {
            u32RxBufferMask = 1UL << (u32RxBufferIndex & 0x1FUL);
            if (READ_REG32_BIT(MCANx->NDAT2, u32RxBufferMask) != 0U) {
                WRITE_REG32(MCANx->NDAT2, u32RxBufferMask);
                i32Ret = LL_OK;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief Check if a transmission request is pending on the selected Tx buffer.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32TxBuffer            Tx buffer(s).
 *                                      This parameter can be any combination of @ref MCAN_Tx_Location
 * @retval int32_t:
 *           - LL_OK:                   Pending transmission request on Tx buffer(s).
 *           - LL_ERR_BUF_EMPTY:        No pending transmission request on Tx buffer(s).
 */
int32_t MCAN_CheckTxBufferPending(const CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer)
{
    int32_t i32Ret = LL_ERR_BUF_EMPTY;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    /* Check pending transmission request on the selected buffer */
    if (READ_REG32_BIT(MCANx->TXBRP, u32TxBuffer) != 0U) {
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief Get the fill level of the specified Rx FIFO.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32RxFifo              Rx FIFO.
 *                                      This parameter can be one of the following values:
 *   @arg  MCAN_RX_FIFO0:               Rx FIFO0
 *   @arg  MCAN_RX_FIFO1:               Rx FIFO1
 * @retval An uint32_t type value of the fill level.
 */
uint32_t MCAN_GetRxFifoFillLevel(const CM_MCAN_TypeDef *MCANx, uint32_t u32RxFifo)
{
    uint32_t u32FillLevel;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_RX_FIFO(u32RxFifo));

    if (u32RxFifo == MCAN_RX_FIFO0) {
        u32FillLevel = READ_REG32_BIT(MCANx->RXF0S, MCAN_RXF0S_F0FL);
    } else {
        u32FillLevel = READ_REG32_BIT(MCANx->RXF1S, MCAN_RXF1S_F1FL);
    }

    return u32FillLevel;
}

/**
 * @brief Get the Tx FIFO free level(number of consecutive free Tx FIFO).
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval An uint32_t type value of the Tx FIFO free level.
 */
uint32_t MCAN_GetTxFifoFreeLevel(const CM_MCAN_TypeDef *MCANx)
{
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    return READ_REG32_BIT(MCANx->TXFQS, MCAN_TXFQS_TFFL);
}

/**
 * @brief Check if the specified MCAN peripheral entered restricted operation mode.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval int32_t:
 *           - LL_OK:                   Restricted operation mode active.
 *           - LL_ERR:                  Normal operation mode.
 */
int32_t MCAN_CheckRestrictedOperationMode(const CM_MCAN_TypeDef *MCANx)
{
    int32_t i32Ret = LL_ERR;
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (READ_REG32_BIT(MCANx->CCCR, MCAN_CCCR_ASM) != 0U) {
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief Exit restricted operation mode.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval None
 */
void MCAN_ExitRestrictedOperationMode(CM_MCAN_TypeDef *MCANx)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    /* Exit Restricted Operation mode */
    CLR_REG32_BIT(MCANx->CCCR, MCAN_CCCR_ASM);
}

/**
 * @brief Get the Tx Buffer number of message whose transmission was started last.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval uint8_t:
 *          - 0-31:                     Tx buffer number.
 *          - 0xFF:                     Value of TEST.TXBNS not valid.
 */
uint8_t MCAN_GetStartedTxBufferNum(const CM_MCAN_TypeDef *MCANx)
{
    uint8_t u8TxBufferNum = 0xFFU;

    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    if (READ_REG32_BIT(MCANx->TEST, MCAN_TEST_SVAL) != 0U) {
        u8TxBufferNum = (uint8_t)(READ_REG32_BIT(MCANx->TEST, MCAN_TEST_TXBNS) >> MCAN_TEST_TXBNS_POS);
    }

    return u8TxBufferNum;
}

/**
 * @brief Get the Tx Buffer number of message that is ready for transmission.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval uint8_t:
 *          - 0-31:                     Tx buffer number.
 *          - 0xFF:                     Value of TEST.TXBNP not valid.
 */
uint8_t MCAN_GetPreparedTxBufferNum(const CM_MCAN_TypeDef *MCANx)
{
    uint8_t u8TxBufferNum = 0xFFU;

    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    if (READ_REG32_BIT(MCANx->TEST, MCAN_TEST_PVAL) != 0U) {
        u8TxBufferNum = (uint8_t)(READ_REG32_BIT(MCANx->TEST, MCAN_TEST_TXBNP) >> MCAN_TEST_TXBNP_POS);
    }

    return u8TxBufferNum;
}

/**
 * @brief Get the logical state of the bus.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @retval uint8_t:
 *          - 0:                        The CAN bus is dominant.
 *          - 1:                        The CAN bus is recessive.
 */
uint8_t MCAN_GetBusLogicalState(const CM_MCAN_TypeDef *MCANx)
{
    uint8_t u8LogicalState = 0U;

    DDL_ASSERT(IS_MCAN_UNIT(MCANx));

    if (READ_REG32_BIT(MCANx->TEST, MCAN_TEST_RX) != 0U) {
        u8LogicalState = 1U;
    }

    return u8LogicalState;
}

/**
 * @brief Control of transmit pin
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32PinCtrl             Control of transmit pin
 *                                      This parameter can be one of the following values:
 *   @arg  MCAN_TX_PIN_NORMAL:          Tx pin controlled by the CAN Core, updated at the end of the CAN bit time
 *   @arg  MCAN_TX_PIN_MONITOR:         Sample Point can be monitored at Tx pin
 *   @arg  MCAN_TX_PIN_DOMINANT:        Dominant ('0') level at Tx pin
 *   @arg  MCAN_TX_PIN_RECESSIVE:       Recessive ('1') level at Tx pin
 * @retval None
 */
void MCAN_TxPinControl(CM_MCAN_TypeDef *MCANx, uint32_t u32PinCtrl)
{
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_PIN_CTRL(u32PinCtrl));

    MODIFY_REG32(MCANx->TEST, MCAN_TEST_TX, u32PinCtrl);
}

/**
 * @brief Enable or disable the specifed interrupt(s) of the MCAN.
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32IntType             The MCAN interrupt(s).
 *                                      This parameter can be any combination of @ref MCAN_Interrupt
 * @param  [in]  u32IntLine             Interrupt line, indicates the specified interrupt(s) will be assigned to.
 *                                      This parameter can be a value of @ref MCAN_Interrupt_Line
 *   @arg  MCAN_INT_LINE0:              The specified interrupt(s) will be assigned to interrupt line 0 when enNewState is ENABLE.
 *   @arg  MCAN_INT_LINE1:              The specified interrupt(s) will be assigned to interrupt line 1 when enNewState is ENABLE.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 *   @arg  ENABLE:                      Enable the specifed interrupt(s).
 *   @arg  DISABLE:                     Disable the specifed interrupt(s).
 * @retval None
 */
void MCAN_IntCmd(CM_MCAN_TypeDef *MCANx, uint32_t u32IntType, uint32_t u32IntLine, \
                 en_functional_state_t enNewState)
{
    uint32_t u32ILS;

    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
    DDL_ASSERT(IS_MCAN_INT_TYPE(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        DDL_ASSERT(IS_MCAN_INT_LINE(u32IntLine));

        SET_REG32_BIT(MCANx->IE, u32IntType);
        if (u32IntLine == MCAN_INT_LINE0) {
            CLR_REG32_BIT(MCANx->ILS, u32IntType);
            /* Enable interrupt line 0 */
            SET_REG32_BIT(MCANx->ILE, MCAN_INT_LINE0);
        } else {
            SET_REG32_BIT(MCANx->ILS, u32IntType);
            /* Enable interrupt line 1 */
            SET_REG32_BIT(MCANx->ILE, MCAN_INT_LINE1);
        }
    } else {
        CLR_REG32_BIT(MCANx->IE, u32IntType);
        u32ILS = MCANx->ILS;
        if ((MCANx->IE | u32ILS) == u32ILS) {
            /* Disable interrupt line 0 */
            CLR_REG32_BIT(MCANx->ILE, MCAN_INT_LINE0);
        }

        if ((MCANx->IE & u32ILS) == 0U) {
            /* Disable interrupt line 1 */
            CLR_REG32_BIT(MCANx->ILE, MCAN_INT_LINE1);
        }
    }
}

/**
 * @brief Enable or disable the specifed notification(s) of the specifed Tx buffer(s).
 * @param  [in]  MCANx                  Pointer to MCAN instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_MCAN1:                    MCAN1 instance register base.
 *   @arg  CM_MCAN2:                    MCAN2 instance register base.
 * @param  [in]  u32TxBuffer            Tx buffer(s).
 *                                      This parameter can be any combination of @ref MCAN_Tx_Location
 * @param  [in]  u32Notification        Notification(s) of Tx buffer.
 *                                      This parameter can be any combination of the following parameters:
 *   @arg  MCAN_INT_TX_CPLT:            Transmission completed interrupt.
 *                                      The Tx buffer can cause transmission completed completed interrupt
 *                                      only when its own transmission completed interrupt is enabled.
 *   @arg  MCAN_INT_TX_ABORT_CPLT:      Transmission cancellation finished interrupt.
 *                                      The Tx buffer can cause transmission cancellation finished interrupt
 *                                      only when its own transmission cancellation finished interrupt is enabled.
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 *   @arg  ENABLE:                      Enable the specifed interrupt(s).
 *   @arg  DISABLE:                     Disable the specifed interrupt(s).
 * @retval None
 */
void MCAN_TxBufferNotificationCmd(CM_MCAN_TypeDef *MCANx, uint32_t u32TxBuffer, \
                                  uint32_t u32Notification, en_functional_state_t enNewState)
{
#ifdef __DEBUG
    uint32_t u32TxBufferNum;
#endif
    /* Check function parameters */
    DDL_ASSERT(IS_MCAN_UNIT(MCANx));
#ifdef __DEBUG
    u32TxBufferNum  = MCAN_GET_TX_BUF_NUM(MCANx);
    u32TxBufferNum += MCAN_GET_TX_FQ_NUM(MCANx);
    if (u32TxBufferNum < MCAN_TX_ELMT_NUM_MAX) {
        DDL_ASSERT(IS_MCAN_BIT_MASK(u32TxBuffer, (1UL << u32TxBufferNum) - 1U));
    }
#endif
    DDL_ASSERT(IS_MCAN_TX_BUF_NOTICE(u32Notification));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        if ((u32Notification & MCAN_INT_TX_CPLT) != 0U) {
            /* Enable Tx buffer transmission interrupt to set TC flag in IR register,
               but interrupt will only occur if TC is enabled in IE register */
            SET_REG32_BIT(MCANx->TXBTIE, u32TxBuffer);
        }

        if ((u32Notification & MCAN_INT_TX_ABORT_CPLT) != 0U) {
            /* Enable Tx buffer cancellation finished interrupt to set TCF flag in IR register,
               but interrupt will only occur if TCF is enabled in IE register */
            SET_REG32_BIT(MCANx->TXBCIE, u32TxBuffer);
        }
    } else {
        if ((u32Notification & MCAN_INT_TX_CPLT) != 0U) {
            /* Disable Tx buffer transmission interrupts */
            CLR_REG32_BIT(MCANx->TXBTIE, u32TxBuffer);
        }

        if ((u32Notification & MCAN_INT_TX_ABORT_CPLT) != 0U) {
            /* Disable Tx buffer cancellation finished interrupt */
            CLR_REG32_BIT(MCANx->TXBCIE, u32TxBuffer);
        }
    }
}

/**
 * @}
 */

#endif /* LL_MCAN_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
