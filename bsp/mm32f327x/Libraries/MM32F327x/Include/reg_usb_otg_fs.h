////////////////////////////////////////////////////////////////////////////////
/// @file     reg_usb_otg_fs.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SERIES OF
///           MM32 FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion

#ifndef __REG_USB_OTG_FS_H
#define __REG_USB_OTG_FS_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif










////////////////////////////////////////////////////////////////////////////////
/// @brief USB Base Address Definition
////////////////////////////////////////////////////////////////////////////////

#define USB_OTG_FS_BASE                        (AHB2PERIPH_BASE + 0x0000)              ///< Base Address: 0x50000000




////////////////////////////////////////////////////////////////////////////////
/// @brief USB Register Structure Definition
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    __IO u32 PER_ID;                                                             ///< Peripheral ID register                         offset: 0x00
    __IO u32 ID_COMP;                                                            ///< Peripheral ID complement register              offset: 0x04
    __IO u32 REV;                                                                ///< Peripheral revision register                   offset: 0x08
    __IO u32 ADD_INFO;                                                           ///< Peripheral additional info register            offset: 0x0C
    __IO u32 OTG_ISTAT;                                                          ///< OTG Interrupt Status Register                  offset: 0x10
    __IO u32 OTG_ICTRL;                                                          ///< OTG Interrupt Control Register                 offset: 0x14
    __IO u32 OTG_STAT;                                                           ///< OTG Status Register                            offset: 0x18
    __IO u32 OTG_CTRL;                                                           ///< OTG Control register                           offset: 0x1C
    __IO u32 RESERVED0[24];                                                      ///< Reserved                                       offset: 0x20
    __IO u32 INT_STAT;                                                           ///< Interrupt status register                      offset: 0x80
    __IO u32 INT_ENB;                                                            ///< Interrupt enable register                      offset: 0x84
    __IO u32 ERR_STAT;                                                           ///< Error interrupt status register                offset: 0x88
    __IO u32 ERR_ENB;                                                            ///< Error interrupt enable register                offset: 0x8C
    __IO u32 STAT;                                                               ///< Status register                                offset: 0x90
    __IO u32 CTL;                                                                ///< Control register                               offset: 0x94
    __IO u32 ADDR;                                                               ///< Address register                               offset: 0x98
    __IO u32 BDT_PAGE_01;                                                        ///< BDT page register 1                            offset: 0x9C
    __IO u32 FRM_NUML;                                                           ///< Frame number register                          offset: 0xA0
    __IO u32 FRM_NUMH;                                                           ///< Frame number register                          offset: 0xA4
    __IO u32 TOKEN;                                                              ///< Token register                                 offset: 0xA8
    __IO u32 SOF_THLD;                                                           ///< SOF threshold register                         offset: 0xAC
    __IO u32 BDT_PAGE_02;                                                        ///< BDT page register 2                            offset: 0xB0
    __IO u32 BDT_PAGE_03;                                                        ///< BDT page register 3                            offset: 0xB4
    __IO u32 RESERVED1;                                                          ///< Reserved                                       offset: 0xB8
    __IO u32 RESERVED2;                                                          ///< Reserved                                       offset: 0xBC
    __IO u32 EP_CTL[16];                                                         ///< Endpoint control register                      offset: 0xC0
} USB_OTG_FS_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief USBD type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define USB_OTG_FS                             ((USB_OTG_FS_TypeDef*) USB_OTG_FS_BASE )


////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_PER_ID Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_PER_ID_ID_Pos                    (0)
#define OTG_FS_PER_ID_ID                        (0x3FU << OTG_FS_PER_ID_ID_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_ID_COMP Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_ID_COMP_NID_Pos                  (0)
#define OTG_FS_ID_COMP_NID                      (0x3FU << OTG_FS_ID_COMP_NID_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_REV Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_REV_REV_Pos                      (0)
#define OTG_FS_REV_REV                          (0xFFU << OTG_FS_REV_REV_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_ADD_INFO Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_ADD_INFO_HOST_Pos                (0)
#define OTG_FS_ADD_INFO_HOST                    (0x01U << OTG_FS_ADD_INFO_HOST_Pos)
#define OTG_FS_ADD_INFO_IRQ_NUM_Pos             (3)
#define OTG_FS_ADD_INFO_IRQ_NUM                 (0x1FU << OTG_FS_ADD_INFO_IRQ_NUM_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_OTG_ISTAT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_OTG_ISTAT_A_VBUS_VLD_CHG_Pos     (0)
#define OTG_FS_OTG_ISTAT_A_VBUS_VLD_CHG         (0x01U << OTG_FS_OTG_ISTAT_A_VBUS_VLD_CHG_Pos)
#define OTG_FS_OTG_ISTAT_B_SESS_END_CHG_Pos     (2)
#define OTG_FS_OTG_ISTAT_B_SESS_END_CHG         (0x01U << OTG_FS_OTG_ISTAT_B_SESS_END_CHG_Pos)
#define OTG_FS_OTG_ISTAT_SESS_VLD_CHG_Pos       (3)
#define OTG_FS_OTG_ISTAT_SESS_VLD_CHG           (0x01U << OTG_FS_OTG_ISTAT_SESS_VLD_CHG_Pos)
#define OTG_FS_OTG_ISTAT_LINE_STATE_CHG_Pos     (5)
#define OTG_FS_OTG_ISTAT_LINE_STATE_CHG         (0x01U << OTG_FS_OTG_ISTAT_LINE_STATE_CHG_Pos)
#define OTG_FS_OTG_ISTAT_1_MSEC_Pos             (6)
#define OTG_FS_OTG_ISTAT_1_MSEC                 (0x01U << OTG_FS_OTG_ISTAT_1_MSEC_Pos)
#define OTG_FS_OTG_ISTAT_ID_CHG_Pos             (7)
#define OTG_FS_OTG_ISTAT_ID_CHG                 (0x01U << OTG_FS_OTG_ISTAT_ID_CHG_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_OTG_ICTRL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_OTG_ICTRL_A_VBUS_VLD_EN_Pos      (0)
#define OTG_FS_OTG_ICTRL_A_VBUS_VLD_EN          (0x01U << OTG_FS_OTG_ICTRL_A_VBUS_VLD_EN_Pos)
#define OTG_FS_OTG_ICTRL_B_SESS_END_EN_Pos      (2)
#define OTG_FS_OTG_ICTRL_B_SESS_END_EN          (0x01U << OTG_FS_OTG_ICTRL_B_SESS_END_EN_Pos)
#define OTG_FS_OTG_ICTRL_SESS_VLD_EN_Pos        (3)
#define OTG_FS_OTG_ICTRL_SESS_VLD_EN            (0x01U << OTG_FS_OTG_ICTRL_SESS_VLD_EN_Pos)
#define OTG_FS_OTG_ICTRL_LINE_STATE_EN_Pos      (5)
#define OTG_FS_OTG_ICTRL_LINE_STATE_EN          (0x01U << OTG_FS_OTG_ICTRL_LINE_STATE_EN_Pos)
#define OTG_FS_OTG_ICTRL_1_MSEC_EN_Pos          (6)
#define OTG_FS_OTG_ICTRL_1_MSEC_EN              (0x01U << OTG_FS_OTG_ICTRL_1_MSEC_EN_Pos)
#define OTG_FS_OTG_ICTRL_ID_EN_Pos              (7)
#define OTG_FS_OTG_ICTRL_ID_EN                  (0x01U << OTG_FS_OTG_ICTRL_ID_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_OTG_STAT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_OTG_STAT_A_VBUS_VLD_Pos          (0)
#define OTG_FS_OTG_STAT_A_VBUS_VLD              (0x01U << OTG_FS_OTG_STAT_A_VBUS_VLD_Pos)
#define OTG_FS_OTG_STAT_B_SESS_END_Pos          (2)
#define OTG_FS_OTG_STAT_B_SESS_END              (0x01U << OTG_FS_OTG_STAT_B_SESS_END_Pos)
#define OTG_FS_OTG_STAT_SESS_VLD_Pos            (3)
#define OTG_FS_OTG_STAT_SESS_VLD                (0x01U << OTG_FS_OTG_STAT_SESS_VLD_Pos)
#define OTG_FS_OTG_STAT_LINE_STATE_STABLE_Pos   (5)
#define OTG_FS_OTG_STAT_LINE_STATE_STABLE       (0x01U << OTG_FS_OTG_STAT_LINE_STATE_STABLE_Pos)
#define OTG_FS_OTG_STAT_1_MSEC_Pos              (6)
#define OTG_FS_OTG_STAT_1_MSEC                  (0x01U << OTG_FS_OTG_STAT_1_MSEC_Pos)
#define OTG_FS_OTG_STAT_ID_Pos                  (7)
#define OTG_FS_OTG_STAT_ID                      (0x01U << OTG_FS_OTG_STAT_ID_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_OTG_CTRL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_OTG_CTRL_VBUS_DSCHG_Pos          (0)
#define OTG_FS_OTG_CTRL_VBUS_DSCHG              (0x01U << OTG_FS_OTG_CTRL_VBUS_DSCHG_Pos)
#define OTG_FS_OTG_CTRL_VBUS_CHG_Pos            (1)
#define OTG_FS_OTG_CTRL_VBUS_CHG                (0x01U << OTG_FS_OTG_CTRL_VBUS_CHG_Pos)
#define OTG_FS_OTG_CTRL_OTG_EN_Pos              (2)
#define OTG_FS_OTG_CTRL_OTG_EN                  (0x01U << OTG_FS_OTG_CTRL_OTG_EN_Pos)
#define OTG_FS_OTG_CTRL_VBUS_ON_Pos             (3)
#define OTG_FS_OTG_CTRL_VBUS_ON                 (0x01U << OTG_FS_OTG_CTRL_VBUS_ON_Pos)
#define OTG_FS_OTG_CTRL_DM_LOW_Pos              (4)
#define OTG_FS_OTG_CTRL_DM_LOW                  (0x01U << OTG_FS_OTG_CTRL_DM_LOW_Pos)
#define OTG_FS_OTG_CTRL_DP_LOW_Pos              (5)
#define OTG_FS_OTG_CTRL_DP_LOW                  (0x01U << OTG_FS_OTG_CTRL_DP_LOW_Pos)
#define OTG_FS_OTG_CTRL_DM_HIGH_Pos             (6)
#define OTG_FS_OTG_CTRL_DM_HIGH                 (0x01U << OTG_FS_OTG_CTRL_DM_HIGH_Pos)
#define OTG_FS_OTG_CTRL_DP_HIGH_Pos             (7)
#define OTG_FS_OTG_CTRL_DP_HIGH                 (0x01U << OTG_FS_OTG_CTRL_DP_HIGH_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_INT_STAT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_INT_STAT_USB_RST_Pos             (0)
#define OTG_FS_INT_STAT_USB_RST                 (0x01U << OTG_FS_INT_STAT_USB_RST_Pos)
#define OTG_FS_INT_STAT_ERROR_Pos               (1)
#define OTG_FS_INT_STAT_ERROR                   (0x01U << OTG_FS_INT_STAT_ERROR_Pos)
#define OTG_FS_INT_STAT_SOF_TOK_Pos             (2)
#define OTG_FS_INT_STAT_SOF_TOK                 (0x01U << OTG_FS_INT_STAT_SOF_TOK_Pos)
#define OTG_FS_INT_STAT_TOK_DNE_Pos             (3)
#define OTG_FS_INT_STAT_TOK_DNE                 (0x01U << OTG_FS_INT_STAT_TOK_DNE_Pos)
#define OTG_FS_INT_STAT_SLEEP_Pos               (4)
#define OTG_FS_INT_STAT_SLEEP                   (0x01U << OTG_FS_INT_STAT_SLEEP_Pos)
#define OTG_FS_INT_STAT_RESUME_Pos              (5)
#define OTG_FS_INT_STAT_RESUME                  (0x01U << OTG_FS_INT_STAT_RESUME_Pos)
#define OTG_FS_INT_STAT_ATTACH_Pos              (6)
#define OTG_FS_INT_STAT_ATTACH                  (0x01U << OTG_FS_INT_STAT_ATTACH_Pos)
#define OTG_FS_INT_STAT_STALL_Pos               (7)
#define OTG_FS_INT_STAT_STALL                   (0x01U << OTG_FS_INT_STAT_STALL_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_INT_ENB Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_INT_ENB_USB_RST_EN_Pos           (0)
#define OTG_FS_INT_ENB_USB_RST_EN               (0x01U << OTG_FS_INT_ENB_USB_RST_EN_Pos)
#define OTG_FS_INT_ENB_ERROR_EN_Pos             (1)
#define OTG_FS_INT_ENB_ERROR_EN                 (0x01U << OTG_FS_INT_ENB_ERROR_EN_Pos)
#define OTG_FS_INT_ENB_SOF_TOK_EN_Pos           (2)
#define OTG_FS_INT_ENB_SOF_TOK_EN               (0x01U << OTG_FS_INT_ENB_SOF_TOK_EN_Pos)
#define OTG_FS_INT_ENB_TOK_DNE_EN_Pos           (3)
#define OTG_FS_INT_ENB_TOK_DNE_EN               (0x01U << OTG_FS_INT_ENB_TOK_DNE_EN_Pos)
#define OTG_FS_INT_ENB_SLEEP_EN_Pos             (4)
#define OTG_FS_INT_ENB_SLEEP_EN                 (0x01U << OTG_FS_INT_ENB_SLEEP_EN_Pos)
#define OTG_FS_INT_ENB_RESUME_EN_Pos            (5)
#define OTG_FS_INT_ENB_RESUME_EN                (0x01U << OTG_FS_INT_ENB_RESUME_EN_Pos)
#define OTG_FS_INT_ENB_ATTACH_EN_Pos            (6)
#define OTG_FS_INT_ENB_ATTACH_EN                (0x01U << OTG_FS_INT_ENB_ATTACH_EN_Pos)
#define OTG_FS_INT_ENB_STALL_EN_Pos             (7)
#define OTG_FS_INT_ENB_STALL_EN                 (0x01U << OTG_FS_INT_ENB_STALL_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_ERR_STAT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_ERR_STAT_PID_ERR_Pos             (0)
#define OTG_FS_ERR_STAT_PID_ERR                 (0x01U << OTG_FS_ERR_STAT_PID_ERR_Pos)
#define OTG_FS_ERR_STAT_CRC5_EOF_Pos            (1)
#define OTG_FS_ERR_STAT_CRC5_EOF                (0x01U << OTG_FS_ERR_STAT_CRC5_EOF_Pos)
#define OTG_FS_ERR_STAT_CRC16_Pos               (2)
#define OTG_FS_ERR_STAT_CRC16                   (0x01U << OTG_FS_ERR_STAT_CRC16_Pos)
#define OTG_FS_ERR_STAT_DFN8_Pos                (3)
#define OTG_FS_ERR_STAT_DFN8                    (0x01U << OTG_FS_ERR_STAT_DFN8_Pos)
#define OTG_FS_ERR_STAT_BTO_ERR_Pos             (4)
#define OTG_FS_ERR_STAT_BTO_ERR                 (0x01U << OTG_FS_ERR_STAT_BTO_ERR_Pos)
#define OTG_FS_ERR_STAT_DMA_ERR_Pos             (5)
#define OTG_FS_ERR_STAT_DMA_ERR                 (0x01U << OTG_FS_ERR_STAT_DMA_ERR_Pos)
#define OTG_FS_ERR_STAT_BTS_ERR_Pos             (7)
#define OTG_FS_ERR_STAT_BTS_ERR                 (0x01U << OTG_FS_ERR_STAT_BTS_ERR_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_ERR_ENB Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_ERR_ENB_PID_ERR_EN_Pos           (0)
#define OTG_FS_ERR_ENB_PID_ERR_EN               (0x01U << OTG_FS_ERR_ENB_PID_ERR_EN_Pos)
#define OTG_FS_ERR_ENB_CRC5_EOF_EN_Pos          (1)
#define OTG_FS_ERR_ENB_CRC5_EOF_EN              (0x01U << OTG_FS_ERR_ENB_CRC5_EOF_EN_Pos)
#define OTG_FS_ERR_ENB_CRC16_EN_Pos             (2)
#define OTG_FS_ERR_ENB_CRC16_EN                 (0x01U << OTG_FS_ERR_ENB_CRC16_EN_Pos)
#define OTG_FS_ERR_ENB_DFN8_EN_Pos              (3)
#define OTG_FS_ERR_ENB_DFN8_EN                  (0x01U << OTG_FS_ERR_ENB_DFN8_EN_Pos)
#define OTG_FS_ERR_ENB_BTO_ERR_EN_Pos           (4)
#define OTG_FS_ERR_ENB_BTO_ERR_EN               (0x01U << OTG_FS_ERR_ENB_BTO_ERR_EN_Pos)
#define OTG_FS_ERR_ENB_DMA_ERR_EN_Pos           (5)
#define OTG_FS_ERR_ENB_DMA_ERR_EN               (0x01U << OTG_FS_ERR_ENB_DMA_ERR_EN_Pos)
#define OTG_FS_ERR_ENB_BTS_ERR_EN_Pos           (7)
#define OTG_FS_ERR_ENB_BTS_ERR_EN               (0x01U << OTG_FS_ERR_ENB_BTS_ERR_EN_Pos)


////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_STAT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_STAT_ODD_Pos                     (2)
#define OTG_FS_STAT_ODD                         (0x01U << OTG_FS_STAT_ODD_Pos)
#define OTG_FS_STAT_TX_Pos                      (3)
#define OTG_FS_STAT_TX                          (0x01U << OTG_FS_STAT_TX_Pos)
#define OTG_FS_STAT_ENDP_Pos                    (4)
#define OTG_FS_STAT_ENDP                        (0x0FU << OTG_FS_STAT_ENDP_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_CTL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_CTL_USB_EN_SOF_EN_Pos            (0)
#define OTG_FS_CTL_USB_EN_SOF_EN                (0x01U << OTG_FS_CTL_USB_EN_SOF_EN_Pos)
#define OTG_FS_CTL_ODD_RST_Pos                  (1)
#define OTG_FS_CTL_ODD_RST                      (0x01U << OTG_FS_CTL_ODD_RST_Pos)
#define OTG_FS_CTL_RESUME_Pos                   (2)
#define OTG_FS_CTL_RESUME                       (0x01U << OTG_FS_CTL_RESUME_Pos)
#define OTG_FS_CTL_HOST_MODE_EN_Pos             (3)
#define OTG_FS_CTL_HOST_MODE_EN                 (0x01U << OTG_FS_CTL_HOST_MODE_EN_Pos)
#define OTG_FS_CTL_RESET_Pos                    (4)
#define OTG_FS_CTL_RESET                        (0x01U << OTG_FS_CTL_RESET_Pos)
#define OTG_FS_CTL_TXDSUSPEND_TOKENBUSY_Pos     (5)
#define OTG_FS_CTL_TXDSUSPEND_TOKENBUSY         (0x01U << OTG_FS_CTL_TXDSUSPEND_TOKENBUSY_Pos)
#define OTG_FS_CTL_SE0_Pos                      (6)
#define OTG_FS_CTL_SE0                          (0x01U << OTG_FS_CTL_SE0_Pos)
#define OTG_FS_CTL_JSTATE_Pos                   (7)
#define OTG_FS_CTL_JSTATE                       (0x01U << OTG_FS_CTL_JSTATE_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_ADDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_ADDR_ADDR_Pos                    (0)
#define OTG_FS_ADDR_ADDR                        (0x7FU << OTG_FS_ADDR_ADDR_Pos)
#define OTG_FS_ADDR_LS_EN_Pos                   (7)
#define OTG_FS_ADDR_LS_EN                       (0x01U << OTG_FS_ADDR_LS_EN_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_BDT_PAGE_01 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_BDT_PAGE_01_BDT_BA_15_9_Pos      (1)
#define OTG_FS_BDT_PAGE_01_BDT_BA_15_9          (0x7FU << OTG_FS_BDT_PAGE_01_BDT_BA_15_9_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_FRM_NUML Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_FRM_NUML_FRM_Pos                 (0)
#define OTG_FS_FRM_NUML_FRM                     (0xFFU << OTG_FS_FRM_NUML_FRM_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_FRM_NUMH Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_FRM_NUMH_FRM_Pos                 (0)
#define OTG_FS_FRM_NUMH_FRM                     (0x07U << OTG_FS_FRM_NUMH_FRM_Pos)


////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_TOKEN Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_TOKEN_TOKEN_ENDPT_Pos            (0)
#define OTG_FS_TOKEN_TOKEN_ENDPT                (0x0FU << OTG_FS_TOKEN_TOKEN_ENDPT_Pos)
#define OTG_FS_TOKEN_TOKEN_PID_Pos              (4)
#define OTG_FS_TOKEN_TOKEN_PID                  (0x0FU << OTG_FS_TOKEN_TOKEN_PID_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_SOF_THLD Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_SOF_THLD_CNT_Pos                 (0)
#define OTG_FS_SOF_THLD_CNT                     (0xFFU << OTG_FS_SOF_THLD_CNT_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_BDT_PAGE_02 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_BDT_PAGE_02_BDT_BA_23_16_Pos     (0)
#define OTG_FS_BDT_PAGE_02_BDT_BA_23_16         (0xFFU << OTG_FS_BDT_PAGE_02_BDT_BA_23_16_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_BDT_PAGE_03 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_BDT_PAGE_03_BDT_BA_31_24_Pos     (0)
#define OTG_FS_BDT_PAGE_03_BDT_BA_31_24         (0xFFU << OTG_FS_BDT_PAGE_03_BDT_BA_31_24_Pos)

////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS_EP_CTL Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define OTG_FS_EP_CTL_EP_HSHK_Pos               (0)
#define OTG_FS_EP_CTL_EP_HSHK                   (0x01U << OTG_FS_EP_CTL_EP_HSHK_Pos)
#define OTG_FS_EP_CTL_EP_STALL_Pos              (1)
#define OTG_FS_EP_CTL_EP_STALL                  (0x01U << OTG_FS_EP_CTL_EP_STALL_Pos)
#define OTG_FS_EP_CTL_EP_TX_EN_Pos              (2)
#define OTG_FS_EP_CTL_EP_TX_EN                  (0x01U << OTG_FS_EP_CTL_EP_TX_EN_Pos)
#define OTG_FS_EP_CTL_EP_RX_EN_Pos              (3)
#define OTG_FS_EP_CTL_EP_RX_EN                  (0x01U << OTG_FS_EP_CTL_EP_RX_EN_Pos)
#define OTG_FS_EP_CTL_EP_CTL_DIS_Pos            (4)
#define OTG_FS_EP_CTL_EP_CTL_DIS                (0x01U << OTG_FS_EP_CTL_EP_CTL_DIS_Pos)
#define OTG_FS_EP_CTL_RETRY_DIS_Pos             (6)
#define OTG_FS_EP_CTL_RETRY_DIS                 (0x01U << OTG_FS_EP_CTL_RETRY_DIS_Pos)
#define OTG_FS_EP_CTL_HOST_WO_HUB_Pos           (7)
#define OTG_FS_EP_CTL_HOST_WO_HUB               (0x01U << OTG_FS_EP_CTL_HOST_WO_HUB_Pos)


////////////////////////////////////////////////////////////////////////////////
/// @brief OTG_FS Buffer Descriptor Bit Definition
////////////////////////////////////////////////////////////////////////////////

#define OTG_FS_BD_TOK_PID_Pos                   (2)
#define OTG_FS_BD_TOK_PID                       (0x0FU << OTG_FS_BD_TOK_PID_Pos)
#define OTG_FS_BD_DATA01_Pos                    (6)
#define OTG_FS_BD_DATA01                        (0x01U << OTG_FS_BD_DATA01_Pos)
#define OTG_FS_BD_OWN_Pos                       (7)
#define OTG_FS_BD_OWN                           (0x01U << OTG_FS_BD_OWN_Pos)
#define OTG_FS_BD_BC_Pos                        (16)
#define OTG_FS_BD_BC                            (0x3FFU << OTG_FS_BD_BC_Pos)
#define OTG_FS_BD_ADDRESS_Pos                   (0)
#define OTG_FS_BD_ADDRESS                       (0xFFFFFFFFU << OTG_FS_BD_ADDRESS_Pos)



/**
* @}
*/
//#define OTG_FS_INT_STAT_RST         ((uint32_t)0x01)
//#define OTG_FS_INT_STAT_ERROR       ((uint32_t)0x02)
//#define OTG_FS_INT_STAT_SOF         ((uint32_t)0x04)
//#define OTG_FS_INT_STAT_DNE         ((uint32_t)0x08)
//#define OTG_FS_INT_STAT_SLEEP       ((uint32_t)0x10)
//#define OTG_FS_INT_STAT_RESUME      ((uint32_t)0x20)
//#define OTG_FS_INT_STAT_ATTACH      ((uint32_t)0x40)
//#define OTG_FS_INT_STAT_STALL       ((uint32_t)0x80)

//TEMP
#define  USB_INT_STAT_RST       0x01
#define  USB_INT_STAT_ERROR     0x02
#define  USB_INT_STAT_SOF_TOK   0x04
#define  USB_INT_STAT_TOK_DNE   0x08
#define  USB_INT_STAT_SLEEP     0x10
#define  USB_INT_STAT_RESUME    0x20
#define  USB_INT_STAT_ATTACH    0x40
#define  USB_INT_STAT_STALL     0x80



















/*! @name PERID - Peripheral ID register */
#define USB_PERID_ID_MASK                        (0x3FU)
#define USB_PERID_ID_SHIFT                       (0U)
#define USB_PERID_ID(x)                          (((uint8_t)(((uint8_t)(x)) << USB_PERID_ID_SHIFT)) & USB_PERID_ID_MASK)

/*! @name IDCOMP - Peripheral ID Complement register */
#define USB_IDCOMP_NID_MASK                      (0x3FU)
#define USB_IDCOMP_NID_SHIFT                     (0U)
#define USB_IDCOMP_NID(x)                        (((uint8_t)(((uint8_t)(x)) << USB_IDCOMP_NID_SHIFT)) & USB_IDCOMP_NID_MASK)

/*! @name REV - Peripheral Revision register */
#define USB_REV_REV_MASK                         (0xFFU)
#define USB_REV_REV_SHIFT                        (0U)
#define USB_REV_REV(x)                           (((uint8_t)(((uint8_t)(x)) << USB_REV_REV_SHIFT)) & USB_REV_REV_MASK)

/*! @name ADDINFO - Peripheral Additional Info register */
#define USB_ADDINFO_IEHOST_MASK                  (0x1U)
#define USB_ADDINFO_IEHOST_SHIFT                 (0U)
#define USB_ADDINFO_IEHOST(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ADDINFO_IEHOST_SHIFT)) & USB_ADDINFO_IEHOST_MASK)

/*! @name OTGISTAT - OTG Interrupt Status register */
#define USB_OTGISTAT_LINE_STATE_CHG_MASK         (0x20U)
#define USB_OTGISTAT_LINE_STATE_CHG_SHIFT        (5U)
#define USB_OTGISTAT_LINE_STATE_CHG(x)           (((uint8_t)(((uint8_t)(x)) << USB_OTGISTAT_LINE_STATE_CHG_SHIFT)) & USB_OTGISTAT_LINE_STATE_CHG_MASK)
#define USB_OTGISTAT_ONEMSEC_MASK                (0x40U)
#define USB_OTGISTAT_ONEMSEC_SHIFT               (6U)
#define USB_OTGISTAT_ONEMSEC(x)                  (((uint8_t)(((uint8_t)(x)) << USB_OTGISTAT_ONEMSEC_SHIFT)) & USB_OTGISTAT_ONEMSEC_MASK)

/*! @name OTGICR - OTG Interrupt Control register */
#define USB_OTGICR_LINESTATEEN_MASK              (0x20U)
#define USB_OTGICR_LINESTATEEN_SHIFT             (5U)
#define USB_OTGICR_LINESTATEEN(x)                (((uint8_t)(((uint8_t)(x)) << USB_OTGICR_LINESTATEEN_SHIFT)) & USB_OTGICR_LINESTATEEN_MASK)
#define USB_OTGICR_ONEMSECEN_MASK                (0x40U)
#define USB_OTGICR_ONEMSECEN_SHIFT               (6U)
#define USB_OTGICR_ONEMSECEN(x)                  (((uint8_t)(((uint8_t)(x)) << USB_OTGICR_ONEMSECEN_SHIFT)) & USB_OTGICR_ONEMSECEN_MASK)

/*! @name OTGSTAT - OTG Status register */
#define USB_OTGSTAT_LINESTATESTABLE_MASK         (0x20U)
#define USB_OTGSTAT_LINESTATESTABLE_SHIFT        (5U)
#define USB_OTGSTAT_LINESTATESTABLE(x)           (((uint8_t)(((uint8_t)(x)) << USB_OTGSTAT_LINESTATESTABLE_SHIFT)) & USB_OTGSTAT_LINESTATESTABLE_MASK)
#define USB_OTGSTAT_ONEMSECEN_MASK               (0x40U)
#define USB_OTGSTAT_ONEMSECEN_SHIFT              (6U)
#define USB_OTGSTAT_ONEMSECEN(x)                 (((uint8_t)(((uint8_t)(x)) << USB_OTGSTAT_ONEMSECEN_SHIFT)) & USB_OTGSTAT_ONEMSECEN_MASK)

/*! @name OTGCTL - OTG Control register */
#define USB_OTGCTL_OTGEN_MASK                    (0x4U)
#define USB_OTGCTL_OTGEN_SHIFT                   (2U)
#define USB_OTGCTL_OTGEN(x)                      (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_OTGEN_SHIFT)) & USB_OTGCTL_OTGEN_MASK)
#define USB_OTGCTL_DMLOW_MASK                    (0x10U)
#define USB_OTGCTL_DMLOW_SHIFT                   (4U)
#define USB_OTGCTL_DMLOW(x)                      (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_DMLOW_SHIFT)) & USB_OTGCTL_DMLOW_MASK)
#define USB_OTGCTL_DPLOW_MASK                    (0x20U)
#define USB_OTGCTL_DPLOW_SHIFT                   (5U)
#define USB_OTGCTL_DPLOW(x)                      (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_DPLOW_SHIFT)) & USB_OTGCTL_DPLOW_MASK)
#define USB_OTGCTL_DPHIGH_MASK                   (0x80U)
#define USB_OTGCTL_DPHIGH_SHIFT                  (7U)
#define USB_OTGCTL_DPHIGH(x)                     (((uint8_t)(((uint8_t)(x)) << USB_OTGCTL_DPHIGH_SHIFT)) & USB_OTGCTL_DPHIGH_MASK)

/*! @name ISTAT - Interrupt Status register */
#define USB_ISTAT_USBRST_MASK                    (0x1U)
#define USB_ISTAT_USBRST_SHIFT                   (0U)
#define USB_ISTAT_USBRST(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_USBRST_SHIFT)) & USB_ISTAT_USBRST_MASK)
#define USB_ISTAT_ERROR_MASK                     (0x2U)
#define USB_ISTAT_ERROR_SHIFT                    (1U)
#define USB_ISTAT_ERROR(x)                       (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_ERROR_SHIFT)) & USB_ISTAT_ERROR_MASK)
#define USB_ISTAT_SOFTOK_MASK                    (0x4U)
#define USB_ISTAT_SOFTOK_SHIFT                   (2U)
#define USB_ISTAT_SOFTOK(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_SOFTOK_SHIFT)) & USB_ISTAT_SOFTOK_MASK)
#define USB_ISTAT_TOKDNE_MASK                    (0x8U)
#define USB_ISTAT_TOKDNE_SHIFT                   (3U)
#define USB_ISTAT_TOKDNE(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_TOKDNE_SHIFT)) & USB_ISTAT_TOKDNE_MASK)
#define USB_ISTAT_SLEEP_MASK                     (0x10U)
#define USB_ISTAT_SLEEP_SHIFT                    (4U)
#define USB_ISTAT_SLEEP(x)                       (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_SLEEP_SHIFT)) & USB_ISTAT_SLEEP_MASK)
#define USB_ISTAT_RESUME_MASK                    (0x20U)
#define USB_ISTAT_RESUME_SHIFT                   (5U)
#define USB_ISTAT_RESUME(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_RESUME_SHIFT)) & USB_ISTAT_RESUME_MASK)
#define USB_ISTAT_ATTACH_MASK                    (0x40U)
#define USB_ISTAT_ATTACH_SHIFT                   (6U)
#define USB_ISTAT_ATTACH(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_ATTACH_SHIFT)) & USB_ISTAT_ATTACH_MASK)
#define USB_ISTAT_STALL_MASK                     (0x80U)
#define USB_ISTAT_STALL_SHIFT                    (7U)
#define USB_ISTAT_STALL(x)                       (((uint8_t)(((uint8_t)(x)) << USB_ISTAT_STALL_SHIFT)) & USB_ISTAT_STALL_MASK)

/*! @name INTEN - Interrupt Enable register */
#define USB_INTEN_USBRSTEN_MASK                  (0x1U)
#define USB_INTEN_USBRSTEN_SHIFT                 (0U)
#define USB_INTEN_USBRSTEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_INTEN_USBRSTEN_SHIFT)) & USB_INTEN_USBRSTEN_MASK)
#define USB_INTEN_ERROREN_MASK                   (0x2U)
#define USB_INTEN_ERROREN_SHIFT                  (1U)
#define USB_INTEN_ERROREN(x)                     (((uint8_t)(((uint8_t)(x)) << USB_INTEN_ERROREN_SHIFT)) & USB_INTEN_ERROREN_MASK)
#define USB_INTEN_SOFTOKEN_MASK                  (0x4U)
#define USB_INTEN_SOFTOKEN_SHIFT                 (2U)
#define USB_INTEN_SOFTOKEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_INTEN_SOFTOKEN_SHIFT)) & USB_INTEN_SOFTOKEN_MASK)
#define USB_INTEN_TOKDNEEN_MASK                  (0x8U)
#define USB_INTEN_TOKDNEEN_SHIFT                 (3U)
#define USB_INTEN_TOKDNEEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_INTEN_TOKDNEEN_SHIFT)) & USB_INTEN_TOKDNEEN_MASK)
#define USB_INTEN_SLEEPEN_MASK                   (0x10U)
#define USB_INTEN_SLEEPEN_SHIFT                  (4U)
#define USB_INTEN_SLEEPEN(x)                     (((uint8_t)(((uint8_t)(x)) << USB_INTEN_SLEEPEN_SHIFT)) & USB_INTEN_SLEEPEN_MASK)
#define USB_INTEN_RESUMEEN_MASK                  (0x20U)
#define USB_INTEN_RESUMEEN_SHIFT                 (5U)
#define USB_INTEN_RESUMEEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_INTEN_RESUMEEN_SHIFT)) & USB_INTEN_RESUMEEN_MASK)
#define USB_INTEN_ATTACHEN_MASK                  (0x40U)
#define USB_INTEN_ATTACHEN_SHIFT                 (6U)
#define USB_INTEN_ATTACHEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_INTEN_ATTACHEN_SHIFT)) & USB_INTEN_ATTACHEN_MASK)
#define USB_INTEN_STALLEN_MASK                   (0x80U)
#define USB_INTEN_STALLEN_SHIFT                  (7U)
#define USB_INTEN_STALLEN(x)                     (((uint8_t)(((uint8_t)(x)) << USB_INTEN_STALLEN_SHIFT)) & USB_INTEN_STALLEN_MASK)

/*! @name ERRSTAT - Error Interrupt Status register */
#define USB_ERRSTAT_PIDERR_MASK                  (0x1U)
#define USB_ERRSTAT_PIDERR_SHIFT                 (0U)
#define USB_ERRSTAT_PIDERR(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_PIDERR_SHIFT)) & USB_ERRSTAT_PIDERR_MASK)
#define USB_ERRSTAT_CRC5EOF_MASK                 (0x2U)
#define USB_ERRSTAT_CRC5EOF_SHIFT                (1U)
#define USB_ERRSTAT_CRC5EOF(x)                   (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_CRC5EOF_SHIFT)) & USB_ERRSTAT_CRC5EOF_MASK)
#define USB_ERRSTAT_CRC16_MASK                   (0x4U)
#define USB_ERRSTAT_CRC16_SHIFT                  (2U)
#define USB_ERRSTAT_CRC16(x)                     (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_CRC16_SHIFT)) & USB_ERRSTAT_CRC16_MASK)
#define USB_ERRSTAT_DFN8_MASK                    (0x8U)
#define USB_ERRSTAT_DFN8_SHIFT                   (3U)
#define USB_ERRSTAT_DFN8(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_DFN8_SHIFT)) & USB_ERRSTAT_DFN8_MASK)
#define USB_ERRSTAT_BTOERR_MASK                  (0x10U)
#define USB_ERRSTAT_BTOERR_SHIFT                 (4U)
#define USB_ERRSTAT_BTOERR(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_BTOERR_SHIFT)) & USB_ERRSTAT_BTOERR_MASK)
#define USB_ERRSTAT_DMAERR_MASK                  (0x20U)
#define USB_ERRSTAT_DMAERR_SHIFT                 (5U)
#define USB_ERRSTAT_DMAERR(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_DMAERR_SHIFT)) & USB_ERRSTAT_DMAERR_MASK)
#define USB_ERRSTAT_OWNERR_MASK                  (0x40U)
#define USB_ERRSTAT_OWNERR_SHIFT                 (6U)
#define USB_ERRSTAT_OWNERR(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_OWNERR_SHIFT)) & USB_ERRSTAT_OWNERR_MASK)
#define USB_ERRSTAT_BTSERR_MASK                  (0x80U)
#define USB_ERRSTAT_BTSERR_SHIFT                 (7U)
#define USB_ERRSTAT_BTSERR(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERRSTAT_BTSERR_SHIFT)) & USB_ERRSTAT_BTSERR_MASK)

/*! @name ERREN - Error Interrupt Enable register */
#define USB_ERREN_PIDERREN_MASK                  (0x1U)
#define USB_ERREN_PIDERREN_SHIFT                 (0U)
#define USB_ERREN_PIDERREN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERREN_PIDERREN_SHIFT)) & USB_ERREN_PIDERREN_MASK)
#define USB_ERREN_CRC5EOFEN_MASK                 (0x2U)
#define USB_ERREN_CRC5EOFEN_SHIFT                (1U)
#define USB_ERREN_CRC5EOFEN(x)                   (((uint8_t)(((uint8_t)(x)) << USB_ERREN_CRC5EOFEN_SHIFT)) & USB_ERREN_CRC5EOFEN_MASK)
#define USB_ERREN_CRC16EN_MASK                   (0x4U)
#define USB_ERREN_CRC16EN_SHIFT                  (2U)
#define USB_ERREN_CRC16EN(x)                     (((uint8_t)(((uint8_t)(x)) << USB_ERREN_CRC16EN_SHIFT)) & USB_ERREN_CRC16EN_MASK)
#define USB_ERREN_DFN8EN_MASK                    (0x8U)
#define USB_ERREN_DFN8EN_SHIFT                   (3U)
#define USB_ERREN_DFN8EN(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ERREN_DFN8EN_SHIFT)) & USB_ERREN_DFN8EN_MASK)
#define USB_ERREN_BTOERREN_MASK                  (0x10U)
#define USB_ERREN_BTOERREN_SHIFT                 (4U)
#define USB_ERREN_BTOERREN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERREN_BTOERREN_SHIFT)) & USB_ERREN_BTOERREN_MASK)
#define USB_ERREN_DMAERREN_MASK                  (0x20U)
#define USB_ERREN_DMAERREN_SHIFT                 (5U)
#define USB_ERREN_DMAERREN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERREN_DMAERREN_SHIFT)) & USB_ERREN_DMAERREN_MASK)
#define USB_ERREN_OWNERREN_MASK                  (0x40U)
#define USB_ERREN_OWNERREN_SHIFT                 (6U)
#define USB_ERREN_OWNERREN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERREN_OWNERREN_SHIFT)) & USB_ERREN_OWNERREN_MASK)
#define USB_ERREN_BTSERREN_MASK                  (0x80U)
#define USB_ERREN_BTSERREN_SHIFT                 (7U)
#define USB_ERREN_BTSERREN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ERREN_BTSERREN_SHIFT)) & USB_ERREN_BTSERREN_MASK)

/*! @name STAT - Status register */
#define USB_STAT_ODD_MASK                        (0x4U)
#define USB_STAT_ODD_SHIFT                       (2U)
#define USB_STAT_ODD(x)                          (((uint8_t)(((uint8_t)(x)) << USB_STAT_ODD_SHIFT)) & USB_STAT_ODD_MASK)
#define USB_STAT_TX_MASK                         (0x8U)
#define USB_STAT_TX_SHIFT                        (3U)
#define USB_STAT_TX(x)                           (((uint8_t)(((uint8_t)(x)) << USB_STAT_TX_SHIFT)) & USB_STAT_TX_MASK)
#define USB_STAT_ENDP_MASK                       (0xF0U)
#define USB_STAT_ENDP_SHIFT                      (4U)
#define USB_STAT_ENDP(x)                         (((uint8_t)(((uint8_t)(x)) << USB_STAT_ENDP_SHIFT)) & USB_STAT_ENDP_MASK)

/*! @name CTL - Control register */
#define USB_CTL_USBENSOFEN_MASK                  (0x1U)
#define USB_CTL_USBENSOFEN_SHIFT                 (0U)
#define USB_CTL_USBENSOFEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_CTL_USBENSOFEN_SHIFT)) & USB_CTL_USBENSOFEN_MASK)
#define USB_CTL_ODDRST_MASK                      (0x2U)
#define USB_CTL_ODDRST_SHIFT                     (1U)
#define USB_CTL_ODDRST(x)                        (((uint8_t)(((uint8_t)(x)) << USB_CTL_ODDRST_SHIFT)) & USB_CTL_ODDRST_MASK)
#define USB_CTL_RESUME_MASK                      (0x4U)
#define USB_CTL_RESUME_SHIFT                     (2U)
#define USB_CTL_RESUME(x)                        (((uint8_t)(((uint8_t)(x)) << USB_CTL_RESUME_SHIFT)) & USB_CTL_RESUME_MASK)
#define USB_CTL_HOSTMODEEN_MASK                  (0x8U)
#define USB_CTL_HOSTMODEEN_SHIFT                 (3U)
#define USB_CTL_HOSTMODEEN(x)                    (((uint8_t)(((uint8_t)(x)) << USB_CTL_HOSTMODEEN_SHIFT)) & USB_CTL_HOSTMODEEN_MASK)
#define USB_CTL_RESET_MASK                       (0x10U)
#define USB_CTL_RESET_SHIFT                      (4U)
#define USB_CTL_RESET(x)                         (((uint8_t)(((uint8_t)(x)) << USB_CTL_RESET_SHIFT)) & USB_CTL_RESET_MASK)
#define USB_CTL_TXSUSPENDTOKENBUSY_MASK          (0x20U)
#define USB_CTL_TXSUSPENDTOKENBUSY_SHIFT         (5U)
#define USB_CTL_TXSUSPENDTOKENBUSY(x)            (((uint8_t)(((uint8_t)(x)) << USB_CTL_TXSUSPENDTOKENBUSY_SHIFT)) & USB_CTL_TXSUSPENDTOKENBUSY_MASK)
#define USB_CTL_SE0_MASK                         (0x40U)
#define USB_CTL_SE0_SHIFT                        (6U)
#define USB_CTL_SE0(x)                           (((uint8_t)(((uint8_t)(x)) << USB_CTL_SE0_SHIFT)) & USB_CTL_SE0_MASK)
#define USB_CTL_JSTATE_MASK                      (0x80U)
#define USB_CTL_JSTATE_SHIFT                     (7U)
#define USB_CTL_JSTATE(x)                        (((uint8_t)(((uint8_t)(x)) << USB_CTL_JSTATE_SHIFT)) & USB_CTL_JSTATE_MASK)

/*! @name ADDR - Address register */
#define USB_ADDR_ADDR_MASK                       (0x7FU)
#define USB_ADDR_ADDR_SHIFT                      (0U)
#define USB_ADDR_ADDR(x)                         (((uint8_t)(((uint8_t)(x)) << USB_ADDR_ADDR_SHIFT)) & USB_ADDR_ADDR_MASK)
#define USB_ADDR_LSEN_MASK                       (0x80U)
#define USB_ADDR_LSEN_SHIFT                      (7U)
#define USB_ADDR_LSEN(x)                         (((uint8_t)(((uint8_t)(x)) << USB_ADDR_LSEN_SHIFT)) & USB_ADDR_LSEN_MASK)

/*! @name BDTPAGE1 - BDT Page register 1 */
#define USB_BDTPAGE1_BDTBA_MASK                  (0xFEU)
#define USB_BDTPAGE1_BDTBA_SHIFT                 (1U)
#define USB_BDTPAGE1_BDTBA(x)                    (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE1_BDTBA_SHIFT)) & USB_BDTPAGE1_BDTBA_MASK)

/*! @name FRMNUML - Frame Number register Low */
#define USB_FRMNUML_FRM_MASK                     (0xFFU)
#define USB_FRMNUML_FRM_SHIFT                    (0U)
#define USB_FRMNUML_FRM(x)                       (((uint8_t)(((uint8_t)(x)) << USB_FRMNUML_FRM_SHIFT)) & USB_FRMNUML_FRM_MASK)

/*! @name FRMNUMH - Frame Number register High */
#define USB_FRMNUMH_FRM_MASK                     (0x7U)
#define USB_FRMNUMH_FRM_SHIFT                    (0U)
#define USB_FRMNUMH_FRM(x)                       (((uint8_t)(((uint8_t)(x)) << USB_FRMNUMH_FRM_SHIFT)) & USB_FRMNUMH_FRM_MASK)

/*! @name TOKEN - Token register */
#define USB_TOKEN_TOKENENDPT_MASK                (0xFU)
#define USB_TOKEN_TOKENENDPT_SHIFT               (0U)
#define USB_TOKEN_TOKENENDPT(x)                  (((uint8_t)(((uint8_t)(x)) << USB_TOKEN_TOKENENDPT_SHIFT)) & USB_TOKEN_TOKENENDPT_MASK)
#define USB_TOKEN_TOKENPID_MASK                  (0xF0U)
#define USB_TOKEN_TOKENPID_SHIFT                 (4U)
#define USB_TOKEN_TOKENPID(x)                    (((uint8_t)(((uint8_t)(x)) << USB_TOKEN_TOKENPID_SHIFT)) & USB_TOKEN_TOKENPID_MASK)

/*! @name SOFTHLD - SOF Threshold register */
#define USB_SOFTHLD_CNT_MASK                     (0xFFU)
#define USB_SOFTHLD_CNT_SHIFT                    (0U)
#define USB_SOFTHLD_CNT(x)                       (((uint8_t)(((uint8_t)(x)) << USB_SOFTHLD_CNT_SHIFT)) & USB_SOFTHLD_CNT_MASK)

/*! @name BDTPAGE2 - BDT Page Register 2 */
#define USB_BDTPAGE2_BDTBA_MASK                  (0xFFU)
#define USB_BDTPAGE2_BDTBA_SHIFT                 (0U)
#define USB_BDTPAGE2_BDTBA(x)                    (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE2_BDTBA_SHIFT)) & USB_BDTPAGE2_BDTBA_MASK)

/*! @name BDTPAGE3 - BDT Page Register 3 */
#define USB_BDTPAGE3_BDTBA_MASK                  (0xFFU)
#define USB_BDTPAGE3_BDTBA_SHIFT                 (0U)
#define USB_BDTPAGE3_BDTBA(x)                    (((uint8_t)(((uint8_t)(x)) << USB_BDTPAGE3_BDTBA_SHIFT)) & USB_BDTPAGE3_BDTBA_MASK)

/*! @name ENDPT - Endpoint Control register */
#define USB_ENDPT_EPHSHK_MASK                    (0x1U)
#define USB_ENDPT_EPHSHK_SHIFT                   (0U)
#define USB_ENDPT_EPHSHK(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPHSHK_SHIFT)) & USB_ENDPT_EPHSHK_MASK)
#define USB_ENDPT_EPSTALL_MASK                   (0x2U)
#define USB_ENDPT_EPSTALL_SHIFT                  (1U)
#define USB_ENDPT_EPSTALL(x)                     (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPSTALL_SHIFT)) & USB_ENDPT_EPSTALL_MASK)
#define USB_ENDPT_EPTXEN_MASK                    (0x4U)
#define USB_ENDPT_EPTXEN_SHIFT                   (2U)
#define USB_ENDPT_EPTXEN(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPTXEN_SHIFT)) & USB_ENDPT_EPTXEN_MASK)
#define USB_ENDPT_EPRXEN_MASK                    (0x8U)
#define USB_ENDPT_EPRXEN_SHIFT                   (3U)
#define USB_ENDPT_EPRXEN(x)                      (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPRXEN_SHIFT)) & USB_ENDPT_EPRXEN_MASK)
#define USB_ENDPT_EPCTLDIS_MASK                  (0x10U)
#define USB_ENDPT_EPCTLDIS_SHIFT                 (4U)
#define USB_ENDPT_EPCTLDIS(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_EPCTLDIS_SHIFT)) & USB_ENDPT_EPCTLDIS_MASK)
#define USB_ENDPT_RETRYDIS_MASK                  (0x40U)
#define USB_ENDPT_RETRYDIS_SHIFT                 (6U)
#define USB_ENDPT_RETRYDIS(x)                    (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_RETRYDIS_SHIFT)) & USB_ENDPT_RETRYDIS_MASK)
#define USB_ENDPT_HOSTWOHUB_MASK                 (0x80U)
#define USB_ENDPT_HOSTWOHUB_SHIFT                (7U)
#define USB_ENDPT_HOSTWOHUB(x)                   (((uint8_t)(((uint8_t)(x)) << USB_ENDPT_HOSTWOHUB_SHIFT)) & USB_ENDPT_HOSTWOHUB_MASK)

/* The count of USB_ENDPT */
#define USB_ENDPT_COUNT                          (16U)

/*! @name USBCTRL - USB Control register */
#define USB_USBCTRL_UARTSEL_MASK                 (0x10U)
#define USB_USBCTRL_UARTSEL_SHIFT                (4U)
#define USB_USBCTRL_UARTSEL(x)                   (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_UARTSEL_SHIFT)) & USB_USBCTRL_UARTSEL_MASK)
#define USB_USBCTRL_UARTCHLS_MASK                (0x20U)
#define USB_USBCTRL_UARTCHLS_SHIFT               (5U)
#define USB_USBCTRL_UARTCHLS(x)                  (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_UARTCHLS_SHIFT)) & USB_USBCTRL_UARTCHLS_MASK)
#define USB_USBCTRL_PDE_MASK                     (0x40U)
#define USB_USBCTRL_PDE_SHIFT                    (6U)
#define USB_USBCTRL_PDE(x)                       (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_PDE_SHIFT)) & USB_USBCTRL_PDE_MASK)
#define USB_USBCTRL_SUSP_MASK                    (0x80U)
#define USB_USBCTRL_SUSP_SHIFT                   (7U)
#define USB_USBCTRL_SUSP(x)                      (((uint8_t)(((uint8_t)(x)) << USB_USBCTRL_SUSP_SHIFT)) & USB_USBCTRL_SUSP_MASK)

/*! @name OBSERVE - USB OTG Observe register */
#define USB_OBSERVE_DMPD_MASK                    (0x10U)
#define USB_OBSERVE_DMPD_SHIFT                   (4U)
#define USB_OBSERVE_DMPD(x)                      (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DMPD_SHIFT)) & USB_OBSERVE_DMPD_MASK)
#define USB_OBSERVE_DPPD_MASK                    (0x40U)
#define USB_OBSERVE_DPPD_SHIFT                   (6U)
#define USB_OBSERVE_DPPD(x)                      (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DPPD_SHIFT)) & USB_OBSERVE_DPPD_MASK)
#define USB_OBSERVE_DPPU_MASK                    (0x80U)
#define USB_OBSERVE_DPPU_SHIFT                   (7U)
#define USB_OBSERVE_DPPU(x)                      (((uint8_t)(((uint8_t)(x)) << USB_OBSERVE_DPPU_SHIFT)) & USB_OBSERVE_DPPU_MASK)

/*! @name CONTROL - USB OTG Control register */
#define USB_CONTROL_DPPULLUPNONOTG_MASK          (0x10U)
#define USB_CONTROL_DPPULLUPNONOTG_SHIFT         (4U)
#define USB_CONTROL_DPPULLUPNONOTG(x)            (((uint8_t)(((uint8_t)(x)) << USB_CONTROL_DPPULLUPNONOTG_SHIFT)) & USB_CONTROL_DPPULLUPNONOTG_MASK)

/*! @name USBTRC0 - USB Transceiver Control register 0 */
#define USB_USBTRC0_USB_RESUME_INT_MASK          (0x1U)
#define USB_USBTRC0_USB_RESUME_INT_SHIFT         (0U)
#define USB_USBTRC0_USB_RESUME_INT(x)            (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USB_RESUME_INT_SHIFT)) & USB_USBTRC0_USB_RESUME_INT_MASK)
#define USB_USBTRC0_SYNC_DET_MASK                (0x2U)
#define USB_USBTRC0_SYNC_DET_SHIFT               (1U)
#define USB_USBTRC0_SYNC_DET(x)                  (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_SYNC_DET_SHIFT)) & USB_USBTRC0_SYNC_DET_MASK)
#define USB_USBTRC0_USB_CLK_RECOVERY_INT_MASK    (0x4U)
#define USB_USBTRC0_USB_CLK_RECOVERY_INT_SHIFT   (2U)
#define USB_USBTRC0_USB_CLK_RECOVERY_INT(x)      (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USB_CLK_RECOVERY_INT_SHIFT)) & USB_USBTRC0_USB_CLK_RECOVERY_INT_MASK)
#define USB_USBTRC0_VREDG_DET_MASK               (0x8U)
#define USB_USBTRC0_VREDG_DET_SHIFT              (3U)
#define USB_USBTRC0_VREDG_DET(x)                 (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_VREDG_DET_SHIFT)) & USB_USBTRC0_VREDG_DET_MASK)
#define USB_USBTRC0_VFEDG_DET_MASK               (0x10U)
#define USB_USBTRC0_VFEDG_DET_SHIFT              (4U)
#define USB_USBTRC0_VFEDG_DET(x)                 (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_VFEDG_DET_SHIFT)) & USB_USBTRC0_VFEDG_DET_MASK)
#define USB_USBTRC0_USBRESMEN_MASK               (0x20U)
#define USB_USBTRC0_USBRESMEN_SHIFT              (5U)
#define USB_USBTRC0_USBRESMEN(x)                 (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USBRESMEN_SHIFT)) & USB_USBTRC0_USBRESMEN_MASK)
#define USB_USBTRC0_USBRESET_MASK                (0x80U)
#define USB_USBTRC0_USBRESET_SHIFT               (7U)
#define USB_USBTRC0_USBRESET(x)                  (((uint8_t)(((uint8_t)(x)) << USB_USBTRC0_USBRESET_SHIFT)) & USB_USBTRC0_USBRESET_MASK)

/*! @name USBFRMADJUST - Frame Adjust Register */
#define USB_USBFRMADJUST_ADJ_MASK                (0xFFU)
#define USB_USBFRMADJUST_ADJ_SHIFT               (0U)
#define USB_USBFRMADJUST_ADJ(x)                  (((uint8_t)(((uint8_t)(x)) << USB_USBFRMADJUST_ADJ_SHIFT)) & USB_USBFRMADJUST_ADJ_MASK)

/*! @name MISCCTRL - Miscellaneous Control register */
#define USB_MISCCTRL_SOFDYNTHLD_MASK             (0x1U)
#define USB_MISCCTRL_SOFDYNTHLD_SHIFT            (0U)
#define USB_MISCCTRL_SOFDYNTHLD(x)               (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_SOFDYNTHLD_SHIFT)) & USB_MISCCTRL_SOFDYNTHLD_MASK)
#define USB_MISCCTRL_SOFBUSSET_MASK              (0x2U)
#define USB_MISCCTRL_SOFBUSSET_SHIFT             (1U)
#define USB_MISCCTRL_SOFBUSSET(x)                (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_SOFBUSSET_SHIFT)) & USB_MISCCTRL_SOFBUSSET_MASK)
#define USB_MISCCTRL_OWNERRISODIS_MASK           (0x4U)
#define USB_MISCCTRL_OWNERRISODIS_SHIFT          (2U)
#define USB_MISCCTRL_OWNERRISODIS(x)             (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_OWNERRISODIS_SHIFT)) & USB_MISCCTRL_OWNERRISODIS_MASK)
#define USB_MISCCTRL_VREDG_EN_MASK               (0x8U)
#define USB_MISCCTRL_VREDG_EN_SHIFT              (3U)
#define USB_MISCCTRL_VREDG_EN(x)                 (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_VREDG_EN_SHIFT)) & USB_MISCCTRL_VREDG_EN_MASK)
#define USB_MISCCTRL_VFEDG_EN_MASK               (0x10U)
#define USB_MISCCTRL_VFEDG_EN_SHIFT              (4U)
#define USB_MISCCTRL_VFEDG_EN(x)                 (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_VFEDG_EN_SHIFT)) & USB_MISCCTRL_VFEDG_EN_MASK)
#define USB_MISCCTRL_STL_ADJ_EN_MASK             (0x80U)
#define USB_MISCCTRL_STL_ADJ_EN_SHIFT            (7U)
#define USB_MISCCTRL_STL_ADJ_EN(x)               (((uint8_t)(((uint8_t)(x)) << USB_MISCCTRL_STL_ADJ_EN_SHIFT)) & USB_MISCCTRL_STL_ADJ_EN_MASK)

/*! @name STALL_IL_DIS - Peripheral mode stall disable for endpoints 7 to 0 in IN direction */
#define USB_STALL_IL_DIS_STALL_I_DIS0_MASK       (0x1U)
#define USB_STALL_IL_DIS_STALL_I_DIS0_SHIFT      (0U)
#define USB_STALL_IL_DIS_STALL_I_DIS0(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS0_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS0_MASK)
#define USB_STALL_IL_DIS_STALL_I_DIS1_MASK       (0x2U)
#define USB_STALL_IL_DIS_STALL_I_DIS1_SHIFT      (1U)
#define USB_STALL_IL_DIS_STALL_I_DIS1(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS1_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS1_MASK)
#define USB_STALL_IL_DIS_STALL_I_DIS2_MASK       (0x4U)
#define USB_STALL_IL_DIS_STALL_I_DIS2_SHIFT      (2U)
#define USB_STALL_IL_DIS_STALL_I_DIS2(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS2_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS2_MASK)
#define USB_STALL_IL_DIS_STALL_I_DIS3_MASK       (0x8U)
#define USB_STALL_IL_DIS_STALL_I_DIS3_SHIFT      (3U)
#define USB_STALL_IL_DIS_STALL_I_DIS3(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS3_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS3_MASK)
#define USB_STALL_IL_DIS_STALL_I_DIS4_MASK       (0x10U)
#define USB_STALL_IL_DIS_STALL_I_DIS4_SHIFT      (4U)
#define USB_STALL_IL_DIS_STALL_I_DIS4(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS4_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS4_MASK)
#define USB_STALL_IL_DIS_STALL_I_DIS5_MASK       (0x20U)
#define USB_STALL_IL_DIS_STALL_I_DIS5_SHIFT      (5U)
#define USB_STALL_IL_DIS_STALL_I_DIS5(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS5_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS5_MASK)
#define USB_STALL_IL_DIS_STALL_I_DIS6_MASK       (0x40U)
#define USB_STALL_IL_DIS_STALL_I_DIS6_SHIFT      (6U)
#define USB_STALL_IL_DIS_STALL_I_DIS6(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS6_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS6_MASK)
#define USB_STALL_IL_DIS_STALL_I_DIS7_MASK       (0x80U)
#define USB_STALL_IL_DIS_STALL_I_DIS7_SHIFT      (7U)
#define USB_STALL_IL_DIS_STALL_I_DIS7(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_IL_DIS_STALL_I_DIS7_SHIFT)) & USB_STALL_IL_DIS_STALL_I_DIS7_MASK)

/*! @name STALL_IH_DIS - Peripheral mode stall disable for endpoints 15 to 8 in IN direction */
#define USB_STALL_IH_DIS_STALL_I_DIS8_MASK       (0x1U)
#define USB_STALL_IH_DIS_STALL_I_DIS8_SHIFT      (0U)
#define USB_STALL_IH_DIS_STALL_I_DIS8(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS8_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS8_MASK)
#define USB_STALL_IH_DIS_STALL_I_DIS9_MASK       (0x2U)
#define USB_STALL_IH_DIS_STALL_I_DIS9_SHIFT      (1U)
#define USB_STALL_IH_DIS_STALL_I_DIS9(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS9_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS9_MASK)
#define USB_STALL_IH_DIS_STALL_I_DIS10_MASK      (0x4U)
#define USB_STALL_IH_DIS_STALL_I_DIS10_SHIFT     (2U)
#define USB_STALL_IH_DIS_STALL_I_DIS10(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS10_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS10_MASK)
#define USB_STALL_IH_DIS_STALL_I_DIS11_MASK      (0x8U)
#define USB_STALL_IH_DIS_STALL_I_DIS11_SHIFT     (3U)
#define USB_STALL_IH_DIS_STALL_I_DIS11(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS11_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS11_MASK)
#define USB_STALL_IH_DIS_STALL_I_DIS12_MASK      (0x10U)
#define USB_STALL_IH_DIS_STALL_I_DIS12_SHIFT     (4U)
#define USB_STALL_IH_DIS_STALL_I_DIS12(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS12_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS12_MASK)
#define USB_STALL_IH_DIS_STALL_I_DIS13_MASK      (0x20U)
#define USB_STALL_IH_DIS_STALL_I_DIS13_SHIFT     (5U)
#define USB_STALL_IH_DIS_STALL_I_DIS13(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS13_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS13_MASK)
#define USB_STALL_IH_DIS_STALL_I_DIS14_MASK      (0x40U)
#define USB_STALL_IH_DIS_STALL_I_DIS14_SHIFT     (6U)
#define USB_STALL_IH_DIS_STALL_I_DIS14(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS14_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS14_MASK)
#define USB_STALL_IH_DIS_STALL_I_DIS15_MASK      (0x80U)
#define USB_STALL_IH_DIS_STALL_I_DIS15_SHIFT     (7U)
#define USB_STALL_IH_DIS_STALL_I_DIS15(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_IH_DIS_STALL_I_DIS15_SHIFT)) & USB_STALL_IH_DIS_STALL_I_DIS15_MASK)

/*! @name STALL_OL_DIS - Peripheral mode stall disable for endpoints 7 to 0 in OUT direction */
#define USB_STALL_OL_DIS_STALL_O_DIS0_MASK       (0x1U)
#define USB_STALL_OL_DIS_STALL_O_DIS0_SHIFT      (0U)
#define USB_STALL_OL_DIS_STALL_O_DIS0(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS0_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS0_MASK)
#define USB_STALL_OL_DIS_STALL_O_DIS1_MASK       (0x2U)
#define USB_STALL_OL_DIS_STALL_O_DIS1_SHIFT      (1U)
#define USB_STALL_OL_DIS_STALL_O_DIS1(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS1_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS1_MASK)
#define USB_STALL_OL_DIS_STALL_O_DIS2_MASK       (0x4U)
#define USB_STALL_OL_DIS_STALL_O_DIS2_SHIFT      (2U)
#define USB_STALL_OL_DIS_STALL_O_DIS2(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS2_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS2_MASK)
#define USB_STALL_OL_DIS_STALL_O_DIS3_MASK       (0x8U)
#define USB_STALL_OL_DIS_STALL_O_DIS3_SHIFT      (3U)
#define USB_STALL_OL_DIS_STALL_O_DIS3(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS3_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS3_MASK)
#define USB_STALL_OL_DIS_STALL_O_DIS4_MASK       (0x10U)
#define USB_STALL_OL_DIS_STALL_O_DIS4_SHIFT      (4U)
#define USB_STALL_OL_DIS_STALL_O_DIS4(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS4_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS4_MASK)
#define USB_STALL_OL_DIS_STALL_O_DIS5_MASK       (0x20U)
#define USB_STALL_OL_DIS_STALL_O_DIS5_SHIFT      (5U)
#define USB_STALL_OL_DIS_STALL_O_DIS5(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS5_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS5_MASK)
#define USB_STALL_OL_DIS_STALL_O_DIS6_MASK       (0x40U)
#define USB_STALL_OL_DIS_STALL_O_DIS6_SHIFT      (6U)
#define USB_STALL_OL_DIS_STALL_O_DIS6(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS6_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS6_MASK)
#define USB_STALL_OL_DIS_STALL_O_DIS7_MASK       (0x80U)
#define USB_STALL_OL_DIS_STALL_O_DIS7_SHIFT      (7U)
#define USB_STALL_OL_DIS_STALL_O_DIS7(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_OL_DIS_STALL_O_DIS7_SHIFT)) & USB_STALL_OL_DIS_STALL_O_DIS7_MASK)

/*! @name STALL_OH_DIS - Peripheral mode stall disable for endpoints 15 to 8 in OUT direction */
#define USB_STALL_OH_DIS_STALL_O_DIS8_MASK       (0x1U)
#define USB_STALL_OH_DIS_STALL_O_DIS8_SHIFT      (0U)
#define USB_STALL_OH_DIS_STALL_O_DIS8(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS8_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS8_MASK)
#define USB_STALL_OH_DIS_STALL_O_DIS9_MASK       (0x2U)
#define USB_STALL_OH_DIS_STALL_O_DIS9_SHIFT      (1U)
#define USB_STALL_OH_DIS_STALL_O_DIS9(x)         (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS9_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS9_MASK)
#define USB_STALL_OH_DIS_STALL_O_DIS10_MASK      (0x4U)
#define USB_STALL_OH_DIS_STALL_O_DIS10_SHIFT     (2U)
#define USB_STALL_OH_DIS_STALL_O_DIS10(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS10_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS10_MASK)
#define USB_STALL_OH_DIS_STALL_O_DIS11_MASK      (0x8U)
#define USB_STALL_OH_DIS_STALL_O_DIS11_SHIFT     (3U)
#define USB_STALL_OH_DIS_STALL_O_DIS11(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS11_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS11_MASK)
#define USB_STALL_OH_DIS_STALL_O_DIS12_MASK      (0x10U)
#define USB_STALL_OH_DIS_STALL_O_DIS12_SHIFT     (4U)
#define USB_STALL_OH_DIS_STALL_O_DIS12(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS12_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS12_MASK)
#define USB_STALL_OH_DIS_STALL_O_DIS13_MASK      (0x20U)
#define USB_STALL_OH_DIS_STALL_O_DIS13_SHIFT     (5U)
#define USB_STALL_OH_DIS_STALL_O_DIS13(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS13_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS13_MASK)
#define USB_STALL_OH_DIS_STALL_O_DIS14_MASK      (0x40U)
#define USB_STALL_OH_DIS_STALL_O_DIS14_SHIFT     (6U)
#define USB_STALL_OH_DIS_STALL_O_DIS14(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS14_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS14_MASK)
#define USB_STALL_OH_DIS_STALL_O_DIS15_MASK      (0x80U)
#define USB_STALL_OH_DIS_STALL_O_DIS15_SHIFT     (7U)
#define USB_STALL_OH_DIS_STALL_O_DIS15(x)        (((uint8_t)(((uint8_t)(x)) << USB_STALL_OH_DIS_STALL_O_DIS15_SHIFT)) & USB_STALL_OH_DIS_STALL_O_DIS15_MASK)

/*! @name CLK_RECOVER_CTRL - USB Clock recovery control */
#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_MASK (0x20U)
#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_SHIFT (5U)
#define USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_SHIFT)) & USB_CLK_RECOVER_CTRL_RESTART_IFRTRIM_EN_MASK)
#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_MASK (0x40U)
#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_SHIFT (6U)
#define USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_SHIFT)) & USB_CLK_RECOVER_CTRL_RESET_RESUME_ROUGH_EN_MASK)
#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK (0x80U)
#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_SHIFT (7U)
#define USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN(x) (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_SHIFT)) & USB_CLK_RECOVER_CTRL_CLOCK_RECOVER_EN_MASK)

/*! @name CLK_RECOVER_IRC_EN - IRC48M oscillator enable register */
#define USB_CLK_RECOVER_IRC_EN_REG_EN_MASK       (0x1U)
#define USB_CLK_RECOVER_IRC_EN_REG_EN_SHIFT      (0U)
#define USB_CLK_RECOVER_IRC_EN_REG_EN(x)         (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_IRC_EN_REG_EN_SHIFT)) & USB_CLK_RECOVER_IRC_EN_REG_EN_MASK)
#define USB_CLK_RECOVER_IRC_EN_IRC_EN_MASK       (0x2U)
#define USB_CLK_RECOVER_IRC_EN_IRC_EN_SHIFT      (1U)
#define USB_CLK_RECOVER_IRC_EN_IRC_EN(x)         (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_IRC_EN_IRC_EN_SHIFT)) & USB_CLK_RECOVER_IRC_EN_IRC_EN_MASK)

/*! @name CLK_RECOVER_INT_EN - Clock recovery combined interrupt enable */
#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_MASK (0x10U)
#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_SHIFT (4U)
#define USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN(x)   (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_SHIFT)) & USB_CLK_RECOVER_INT_EN_OVF_ERROR_EN_MASK)

/*! @name CLK_RECOVER_INT_STATUS - Clock recovery separated interrupt status */
#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_MASK (0x10U)
#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_SHIFT (4U)
#define USB_CLK_RECOVER_INT_STATUS_OVF_ERROR(x)  (((uint8_t)(((uint8_t)(x)) << USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_SHIFT)) & USB_CLK_RECOVER_INT_STATUS_OVF_ERROR_MASK)

#define USB0_BASE                                ((0x50000000))

#define USB_BASE_ADDRS                           { USB0_BASE }







/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif //__REG_USB_OTG_FS_H
////////////////////////////////////////////////////////////////////////////////
