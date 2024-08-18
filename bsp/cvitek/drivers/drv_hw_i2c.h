/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-14     ShichengChu  first version
 */
#ifndef __DRV_HW_I2C_H__
#define __DRV_HW_I2C_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>

#include "pinctrl.h"
#include "mmio.h"

#define I2C0                    0x0
#define I2C1                    0x1
#define I2C2                    0x2
#define I2C3                    0x3
#define I2C4                    0x4

#define I2C0_BASE                0x4000000
#define I2C1_BASE                0x4010000
#define I2C2_BASE                0x4020000
#define I2C3_BASE                0x4030000
#define I2C4_BASE                0x4040000

#define I2C0_IRQ           (BSP_I2C_IRQ_BASE + 0)
#define I2C1_IRQ           (BSP_I2C_IRQ_BASE + 1)
#define I2C2_IRQ           (BSP_I2C_IRQ_BASE + 2)
#define I2C3_IRQ           (BSP_I2C_IRQ_BASE + 3)
#define I2C4_IRQ           (BSP_I2C_IRQ_BASE + 4)


#if !defined(IC_CLK)
#define IC_CLK            100
#endif

/*
 * I2C register bit definitions
 */

/* IC_CON, offset: 0x00 */
#define DW_IIC_CON_DEFAUL                          (0x23U)
#define DW_IIC_CON_MASTER_Pos                      (0U)
#define DW_IIC_CON_MASTER_Msk                      (0x1U << DW_IIC_CON_MASTER_Pos)
#define DW_IIC_CON_MASTER_EN                       DW_IIC_CON_MASTER_Msk

#define DW_IIC_CON_SPEEDL_Pos                      (1U)
#define DW_IIC_CON_SPEEDL_Msk                      (0x1U << DW_IIC_CON_SPEEDL_Pos)
#define DW_IIC_CON_SPEEDL_EN                       DW_IIC_CON_SPEEDL_Msk

#define DW_IIC_CON_SPEEDH_Pos                      (2U)
#define DW_IIC_CON_SPEEDH_Msk                      (0x1U << DW_IIC_CON_SPEEDH_Pos)
#define DW_IIC_CON_SPEEDH_EN                       DW_IIC_CON_SPEEDH_Msk

#define DW_IIC_CON_SLAVE_ADDR_MODE_Pos             (3U)
#define DW_IIC_CON_SLAVE_ADDR_MODE_Msk             (0x1U << DW_IIC_CON_SLAVE_ADDR_MODE_Pos)
#define DW_IIC_CON_SLAVE_ADDR_MODE                 DW_IIC_CON_SLAVE_ADDR_MODE_Msk

#define DW_IIC_CON_MASTER_ADDR_MODE_Pos             (4U)
#define DW_IIC_CON_MASTER_ADDR_MODE_Msk             (0x1U << DW_IIC_CON_MASTER_ADDR_MODE_Pos)
#define DW_IIC_CON_MASTER_ADDR_MODE                 DW_IIC_CON_MASTER_ADDR_MODE_Msk

#define DW_IIC_CON_RESTART_Pos                     (5U)
#define DW_IIC_CON_RESTART_Msk                     (0x1U << DW_IIC_CON_RESTART_Pos)
#define DW_IIC_CON_RESTART_EN                      DW_IIC_CON_RESTART_Msk

#define DW_IIC_CON_SLAVE_Pos                       (6U)
#define DW_IIC_CON_SLAVE_Msk                       (0x1U << DW_IIC_CON_SLAVE_Pos)
#define DW_IIC_CON_SLAVE_EN                        DW_IIC_CON_SLAVE_Msk

/* IC_TAR, offset: 0x04 */
#define DW_IIC_TAR_GC_OR_START_Pos                 (10U)
#define DW_IIC_TAR_GC_OR_START_Msk                 (0x1U << DW_IIC_TAR_GC_OR_START_Pos)
#define DW_IIC_TAR_GC_OR_START                     DW_IIC_TAR_GC_OR_START_Msk

#define DW_IIC_TAR_SPECIAL_Pos                     (11U)
#define DW_IIC_TAR_SPECIAL_Msk                     (0x1U << DW_IIC_TAR_SPECIAL_Pos)
#define DW_IIC_TAR_SPECIAL                         DW_IIC_TAR_SPECIAL_Msk

#define DW_IIC_TAR_MASTER_ADDR_MODE_Pos            (12U)
#define DW_IIC_TAR_MASTER_ADDR_MODE_Msk            (0x1U << DW_IIC_TAR_MASTER_ADDR_MODE_Pos)
#define DW_IIC_TAR_MASTER_ADDR_MODE                DW_IIC_TAR_MASTER_ADDR_MODE_Msk

/* IC_DATA_CMD, offset: 0x10 */
#define DW_IIC_DATA_CMD_Pos                        (8U)
#define DW_IIC_DATA_CMD_Msk                        (0x1U << DW_IIC_DATA_CMD_Pos)
#define DW_IIC_DATA_CMD                            DW_IIC_DATA_CMD_Msk

#define DW_IIC_DATA_STOP_Pos                       (9U)
#define DW_IIC_DATA_STOP_Msk                       (0x1U << DW_IIC_DATA_STOP_Pos)
#define DW_IIC_DATA_STOP                           DW_IIC_DATA_STOP_Msk

/* IC_INTR_STAT, offset: 0x2C */
#define DW_IIC_INTR_RX_UNDER_Pos                   (0U)
#define DW_IIC_INTR_RX_UNDER_Msk                   (0x1U << DW_IIC_INTR_RX_UNDER_Pos)
#define DW_IIC_INTR_RX_UNDER                       DW_IIC_INTR_RX_UNDER_Msk

#define DW_IIC_INTR_RX_OVER_Pos                    (1U)
#define DW_IIC_INTR_RX_OVER_Msk                    (0x1U << DW_IIC_INTR_RX_OVER_Pos)
#define DW_IIC_INTR_RX_OVER                        DW_IIC_INTR_RX_OVER_Msk

#define DW_IIC_INTR_RX_FULL_Pos                    (2U)
#define DW_IIC_INTR_RX_FULL_Msk                    (0x1U << DW_IIC_INTR_RX_FULL_Pos)
#define DW_IIC_INTR_RX_FULL                        DW_IIC_INTR_RX_FULL_Msk

#define DW_IIC_INTR_TX_OVER_Pos                    (3U)
#define DW_IIC_INTR_TX_OVER_Msk                    (0x1U << DW_IIC_INTR_TX_OVER_Pos)
#define DW_IIC_INTR_TX_OVER                        DW_IIC_INTR_TX_OVER_Msk

#define DW_IIC_INTR_TX_EMPTY_Pos                   (4U)
#define DW_IIC_INTR_TX_EMPTY_Msk                   (0x1U << DW_IIC_INTR_TX_EMPTY_Pos)
#define DW_IIC_INTR_TX_EMPTY                       DW_IIC_INTR_TX_EMPTY_Msk

#define DW_IIC_INTR_RD_REQ_Pos                     (5U)
#define DW_IIC_INTR_RD_REQ_Msk                     (0x1U << DW_IIC_INTR_RD_REQ_Pos)
#define DW_IIC_INTR_RD_REQ                         DW_IIC_INTR_RD_REQ_Msk

#define DW_IIC_INTR_TX_ABRT_Pos                    (6U)
#define DW_IIC_INTR_TX_ABRT_Msk                    (0x1U << DW_IIC_INTR_TX_ABRT_Pos)
#define DW_IIC_INTR_TX_ABRT                        DW_IIC_INTR_TX_ABRT_Msk

#define DW_IIC_INTR_RX_DONE_Pos                    (7U)
#define DW_IIC_INTR_RX_DONE_Msk                    (0x1U << DW_IIC_INTR_RX_DONE_Pos)
#define DW_IIC_INTR_RX_DONE                        DW_IIC_INTR_RX_DONE_Msk

#define DW_IIC_INTR_ACTIVITY_Pos                   (8U)
#define DW_IIC_INTR_ACTIVITY_Msk                   (0x1U << DW_IIC_INTR_ACTIVITY_Pos)
#define DW_IIC_INTR_ACTIVITY                       DW_IIC_INTR_ACTIVITY_Msk

#define DW_IIC_INTR_STOP_DET_Pos                   (9U)
#define DW_IIC_INTR_STOP_DET_Msk                   (0x1U << DW_IIC_INTR_STOP_DET_Pos)
#define DW_IIC_INTR_STOP_DET                       DW_IIC_INTR_STOP_DET_Msk

#define DW_IIC_INTR_START_DET_Pos                  (10U)
#define DW_IIC_INTR_START_DET_Msk                  (0x1U << DW_IIC_INTR_START_DET_Pos)
#define DW_IIC_INTR_START_DET                      DW_IIC_INTR_START_DET_Msk

#define DW_IIC_INTR_GEN_CALL_Pos                   (11U)
#define DW_IIC_INTR_GEN_CALL_Msk                   (0x1U << DW_IIC_INTR_GEN_CALL_Pos)
#define DW_IIC_INTR_GEN_CALL                       DW_IIC_INTR_GEN_CALL_Msk

/* IC_INTR_MASK, offset: 0x30 */
#define DW_IIC_M_RX_UNDER_Pos                      (0U)
#define DW_IIC_M_RX_UNDER_Msk                      (0x1U << DW_IIC_INTR_RX_UNDER_Pos)
#define DW_IIC_M_RX_UNDER                          DW_IIC_INTR_RX_UNDER_Msk

#define DW_IIC_M_RX_OVER_Pos                       (1U)
#define DW_IIC_M_RX_OVER_Msk                       (0x1U << DW_IIC_INTR_RX_OVER_Pos)
#define DW_IIC_M_RX_OVER                           DW_IIC_INTR_RX_OVER_Msk

#define DW_IIC_M_RX_FULL_Pos                       (2U)
#define DW_IIC_M_RX_FULL_Msk                       (0x1U << DW_IIC_INTR_RX_FULL_Pos)
#define DW_IIC_M_RX_FULL                           DW_IIC_INTR_RX_FULL_Msk

#define DW_IIC_M_TX_OVER_Pos                       (3U)
#define DW_IIC_M_TX_OVER_Msk                       (0x1U << DW_IIC_INTR_TX_OVER_Pos)
#define DW_IIC_M_TX_OVER                           DW_IIC_INTR_TX_OVER_Msk

#define DW_IIC_M_TX_EMPTY_Pos                      (4U)
#define DW_IIC_M_TX_EMPTY_Msk                      (0x1U << DW_IIC_INTR_TX_EMPTY_Pos)
#define DW_IIC_M_TX_EMPTY                          DW_IIC_INTR_TX_EMPTY_Msk

#define DW_IIC_M_RD_REQ_Pos                        (5U)
#define DW_IIC_M_RD_REQ_Msk                        (0x1U << DW_IIC_INTR_RD_REQ_Pos)
#define DW_IIC_M_RD_REQ                            DW_IIC_INTR_RD_REQ_Msk

#define DW_IIC_M_TX_ABRT_Pos                       (6U)
#define DW_IIC_M_TX_ABRT_Msk                       (0x1U << DW_IIC_INTR_TX_ABRT_Pos)
#define DW_IIC_M_TX_ABRT                           DW_IIC_INTR_TX_ABRT_Msk

#define DW_IIC_M_RX_DONE_Pos                       (7U)
#define DW_IIC_M_RX_DONE_Msk                       (0x1U << DW_IIC_INTR_RX_DONE_Pos)
#define DW_IIC_M_RX_DONE                           DW_IIC_INTR_RX_DONE_Msk

#define DW_IIC_M_ACTIVITY_Pos                      (8U)
#define DW_IIC_M_ACTIVITY_Msk                      (0x1U << DW_IIC_INTR_ACTIVITY_Pos)
#define DW_IIC_M_ACTIVITY                          DW_IIC_INTR_ACTIVITY_Msk

#define DW_IIC_M_STOP_DET_Pos                      (9U)
#define DW_IIC_M_STOP_DET_Msk                      (0x1U << DW_IIC_INTR_STOP_DET_Pos)
#define DW_IIC_M_STOP_DET                          DW_IIC_INTR_STOP_DET_Msk

#define DW_IIC_M_START_DET_Pos                     (10U)
#define DW_IIC_M_START_DET_Msk                     (0x1U << DW_IIC_INTR_START_DET_Pos)
#define DW_IIC_M_START_DET                         DW_IIC_INTR_START_DET_Msk

#define DW_IIC_M_GEN_CALL_Pos                      (11U)
#define DW_IIC_M_GEN_CALL_Msk                      (0x1U << DW_IIC_INTR_GEN_CALL_Pos)
#define DW_IIC_M_GEN_CALL                          DW_IIC_INTR_GEN_CALL_Msk

#define DW_IIC_INTR_DEFAULT_MASK                   ( DW_IIC_M_RX_FULL | DW_IIC_M_TX_EMPTY | DW_IIC_M_TX_ABRT | DW_IIC_M_STOP_DET)

/* IC_RAW_INTR_STAT, offset: 0x34 */
#define DW_IIC_RAW_RX_UNDER_Pos                    (0U)
#define DW_IIC_RAW_RX_UNDER_Msk                    (0x1U << DW_IIC_INTR_RX_UNDER_Pos)
#define DW_IIC_RAW_RX_UNDER                        DW_IIC_INTR_RX_UNDER_Msk

#define DW_IIC_RAW_RX_OVER_Pos                     (1U)
#define DW_IIC_RAW_RX_OVER_Msk                     (0x1U << DW_IIC_INTR_RX_OVER_Pos)
#define DW_IIC_RAW_RX_OVER                         DW_IIC_INTR_RX_OVER_Msk

#define DW_IIC_RAW_RX_FULL_Pos                     (2U)
#define DW_IIC_RAW_RX_FULL_Msk                     (0x1U << DW_IIC_INTR_RX_FULL_Pos)
#define DW_IIC_RAW_RX_FULL                         DW_IIC_INTR_RX_FULL_Msk

#define DW_IIC_RAW_TX_OVER_Pos                     (3U)
#define DW_IIC_RAW_TX_OVER_Msk                     (0x1U << DW_IIC_INTR_TX_OVER_Pos)
#define DW_IIC_RAW_TX_OVER                         DW_IIC_INTR_TX_OVER_Msk

#define DW_IIC_RAW_TX_EMPTY_Pos                    (4U)
#define DW_IIC_RAW_TX_EMPTY_Msk                    (0x1U << DW_IIC_INTR_TX_EMPTY_Pos)
#define DW_IIC_RAW_TX_EMPTY                        DW_IIC_INTR_TX_EMPTY_Msk

#define DW_IIC_RAW_RD_REQ_Pos                      (5U)
#define DW_IIC_RAW_RD_REQ_Msk                      (0x1U << DW_IIC_INTR_RD_REQ_Pos)
#define DW_IIC_RAW_RD_REQ                          DW_IIC_INTR_RD_REQ_Msk

#define DW_IIC_RAW_TX_ABRT_Pos                     (6U)
#define DW_IIC_RAW_TX_ABRT_Msk                     (0x1U << DW_IIC_INTR_TX_ABRT_Pos)
#define DW_IIC_RAW_TX_ABRT                         DW_IIC_INTR_TX_ABRT_Msk

#define DW_IIC_RAW_RX_DONE_Pos                     (7U)
#define DW_IIC_RAW_RX_DONE_Msk                     (0x1U << DW_IIC_INTR_RX_DONE_Pos)
#define DW_IIC_RAW_RX_DONE                         DW_IIC_INTR_RX_DONE_Msk

#define DW_IIC_RAW_ACTIVITY_Pos                    (8U)
#define DW_IIC_RAW_ACTIVITY_Msk                    (0x1U << DW_IIC_INTR_ACTIVITY_Pos)
#define DW_IIC_RAW_ACTIVITY                        DW_IIC_INTR_ACTIVITY_Msk

#define DW_IIC_RAW_STOP_DET_Pos                    (9U)
#define DW_IIC_RAW_STOP_DET_Msk                    (0x1U << DW_IIC_INTR_STOP_DET_Pos)
#define DW_IIC_RAW_STOP_DET                        DW_IIC_INTR_STOP_DET_Msk

#define DW_IIC_RAW_START_DET_Pos                   (10U)
#define DW_IIC_RAW_START_DET_Msk                   (0x1U << DW_IIC_INTR_START_DET_Pos)
#define DW_IIC_RAW_START_DET                       DW_IIC_INTR_START_DET_Msk

#define DW_IIC_RAW_GEN_CALL_Pos                    (11U)
#define DW_IIC_RAW_GEN_CALL_Msk                    (0x1U << DW_IIC_INTR_GEN_CALL_Pos)
#define DW_IIC_RAW_GEN_CALL                        DW_IIC_INTR_GEN_CALL_Msk


/* IC_ENABLE, offset: 0x6C */
#define DW_IIC_ENABLE_Pos                          (0U)
#define DW_IIC_ENABLE_Msk                          (0x1U << DW_IIC_ENABLE_Pos)
#define DW_IIC_EN                                  DW_IIC_ENABLE_Msk

/* IC_STATUS, offset: 0x70 */
#define DW_IIC_STATUS_ACTIVITY_Pos                 (0U)
#define DW_IIC_STATUS_ACTIVITY_Msk                 (0x1U << DW_IIC_STATUS_ACTIVITY_Pos)
#define DW_IIC_STATUS_ACTIVITY_STATE               DW_IIC_STATUS_ACTIVITY_Msk

#define DW_IIC_STATUS_TFNE_Pos                     (1U)
#define DW_IIC_STATUS_TFNE_Msk                     (0x1U << DW_IIC_STATUS_TFNE_Pos)
#define DW_IIC_TXFIFO_NOT_FULL_STATE               DW_IIC_STATUS_TFNE_Msk

#define DW_IIC_STATUS_TFE_Pos                      (2U)
#define DW_IIC_STATUS_TFE_Msk                      (0x1U << DW_IIC_STATUS_TFE_Pos)
#define DW_IIC_TXFIFO_EMPTY_STATE                  DW_IIC_STATUS_TFE_Msk

#define DW_IIC_STATUS_RFNE_Pos                     (3U)
#define DW_IIC_STATUS_RFNE_Msk                     (0x1U << DW_IIC_STATUS_RFNE_Pos)
#define DW_IIC_RXFIFO_NOT_EMPTY_STATE              DW_IIC_STATUS_RFNE_Msk

#define DW_IIC_STATUS_REF_Pos                      (4U)
#define DW_IIC_STATUS_REF_Msk                      (0x1U << DW_IIC_STATUS_REF_Pos)
#define DW_IIC_RXFIFO_FULL_STATE                   DW_IIC_STATUS_REF_Msk

#define DW_IIC_STATUS_MST_ACTIVITY_Pos             (5U)
#define DW_IIC_STATUS_MST_ACTIVITY_Msk             (0x1U << DW_IIC_STATUS_MST_ACTIVITY_Pos)
#define DW_IIC_MST_ACTIVITY_STATE                  DW_IIC_STATUS_MST_ACTIVITY_Msk

#define DW_IIC_STATUS_SLV_ACTIVITY_Pos             (6U)
#define DW_IIC_STATUS_SLV_ACTIVITY_Msk             (0x1U << DW_IIC_STATUS_SLV_ACTIVITY_Pos)
#define DW_IIC_SLV_ACTIVITY_STATE                  DW_IIC_STATUS_SLV_ACTIVITY_Msk

/* IC_TX_ABRT_SOURCE, offset: 0x80 */
#define DW_IIC_TX_ABRT_7B_ADDR_NOACK_Pos           (0U)
#define DW_IIC_TX_ABRT_7B_ADDR_NOACK_Msk           (0x1U << DW_IIC_TX_ABRT_7B_ADDR_NOACK_Pos)
#define DW_IIC_TX_ABRT_7B_ADDR_NOACK               DW_IIC_TX_ABRT_7B_ADDR_NOACK_Msk

#define DW_IIC_TX_ABRT_10ADDR1_NOACK_Pos           (1U)
#define DW_IIC_TX_ABRT_10ADDR1_NOACK_Msk           (0x1U << DW_IIC_TX_ABRT_10ADDR1_NOACK_Pos)
#define DW_IIC_TX_ABRT_10ADDR1_NOACK               DW_IIC_TX_ABRT_10ADDR1_NOACK_Msk

#define DW_IIC_TX_ABRT_10ADDR2_NOACK_Pos           (2U)
#define DW_IIC_TX_ABRT_10ADDR2_NOACK_Msk           (0x1U << DW_IIC_TX_ABRT_10ADDR2_NOACK_Pos)
#define DW_IIC_TX_ABRT_10ADDR2_NOACK               DW_IIC_TX_ABRT_10ADDR2_NOACK_Msk

#define DW_IIC_TX_ABRT_TXDATA_NOACK_Pos            (3U)
#define DW_IIC_TX_ABRT_TXDATA_NOACK_Msk            (0x1U << DW_IIC_TX_ABRT_TXDATA_NOACK_Pos)
#define DW_IIC_TX_ABRT_TXDATA_NOACK                DW_IIC_TX_ABRT_TXDATA_NOACK_Msk

#define DW_IIC_TX_ABRT_GCALL_NOACK_Pos             (4U)
#define DW_IIC_TX_ABRT_GCALL_NOACK_Msk             (0x1U << DW_IIC_TX_ABRT_GCALL_NOACK_Pos)
#define DW_IIC_TX_ABRT_GCALL_NOACK                 DW_IIC_TX_ABRT_GCALL_NOACK_Msk

#define DW_IIC_TX_ABRT_GCALL_READ_Pos              (5U)
#define DW_IIC_TX_ABRT_GCALL_READ_Msk              (0x1U << DW_IIC_TX_ABRT_GCALL_READ_Pos)
#define DW_IIC_TX_ABRT_GCALL_READ                  DW_IIC_TX_ABRT_GCALL_READ_Msk

#define DW_IIC_TX_ABRT_HS_ACKDET_Pos               (6U)
#define DW_IIC_TX_ABRT_HS_ACKDET_Msk               (0x1U << DW_IIC_TX_ABRT_HS_ACKDET_Pos)
#define DW_IIC_TX_ABRT_HS_ACKDET                   DW_IIC_TX_ABRT_HS_ACKDET_Msk

#define DW_IIC_TX_ABRT_SBYTE_ACKDET_Pos            (7U)
#define DW_IIC_TX_ABRT_SBYTE_ACKDET_Msk            (0x1U << DW_IIC_TX_ABRT_SBYTE_ACKDET_Pos)
#define DW_IIC_TX_ABRT_SBYTE_ACKDET                DW_IIC_TX_ABRT_SBYTE_ACKDET_Msk

#define DW_IIC_TX_ABRT_HS_NORSTRT_Pos              (8U)
#define DW_IIC_TX_ABRT_HS_NORSTRT_Msk              (0x1U << DW_IIC_TX_ABRT_HS_NORSTRT_Pos)
#define DW_IIC_TX_ABRT_HS_NORSTRT                  DW_IIC_TX_ABRT_HS_NORSTRT_Msk

#define DW_IIC_TX_ABRT_SBYTE_NORSTRT_Pos           (9U)
#define DW_IIC_TX_ABRT_SBYTE_NORSTRT_Msk           (0x1U << DW_IIC_TX_ABRT_SBYTE_NORSTRT_Pos)
#define DW_IIC_TX_ABRT_SBYTE_NORSTRT               DW_IIC_TX_ABRT_SBYTE_NORSTRT_Msk

#define DW_IIC_TX_ABRT_10B_RD_NORSTRT_Pos          (10U)
#define DW_IIC_TX_ABRT_10B_RD_NORSTRT_Msk          (0x1U << DW_IIC_TX_ABRT_10B_RD_NORSTRT_Pos)
#define DW_IIC_TX_ABRT_10B_RD_NORSTRT              DW_IIC_TX_ABRT_10B_RD_NORSTRT_Msk

#define DW_IIC_TX_ABRT_ARB_MASTER_DIS_Pos          (11U)
#define DW_IIC_TX_ABRT_ARB_MASTER_DIS_Msk          (0x1U << DW_IIC_TX_ABRT_ARB_MASTER_DIS_Pos)
#define DW_IIC_TX_ABRT_ARB_MASTER_DIS              DW_IIC_TX_ABRT_ARB_MASTER_DIS_Msk

#define DW_IIC_TX_ABRT_ARB_LOST_Pos                (12U)
#define DW_IIC_TX_ABRT_ARB_LOST_Msk                (0x1U << DW_IIC_TX_ABRT_ARB_LOST_Pos)
#define DW_IIC_TX_ABRT_ARB_LOST                    DW_IIC_TX_ABRT_ARB_LOST_Msk

#define DW_IIC_TX_ABRT_SLVFLUSH_TXFIFO_Pos         (13U)
#define DW_IIC_TX_ABRT_SLVFLUSH_TXFIFO_Msk         (0x1U << DW_IIC_TX_ABRT_SLVFLUSH_TXFIFO_Pos)
#define DW_IIC_TX_ABRT_SLVFLUSH_TXFIFO             DW_IIC_TX_ABRT_SLVFLUSH_TXFIFO_Msk

#define DW_IIC_TX_ABRT_SLV_ARBLOST_Pos             (14U)
#define DW_IIC_TX_ABRT_SLV_ARBLOST_Msk             (0x1U << DW_IIC_TX_ABRT_SLV_ARBLOST_Pos)
#define DW_IIC_TX_ABRT_SLV_ARBLOST                 DW_IIC_TX_ABRT_SLV_ARBLOST_Msk

#define DW_IIC_TX_ABRT_SLVRD_INTX_Pos              (15U)
#define DW_IIC_TX_ABRT_SLVRD_INTX_Msk              (0x1U << DW_IIC_TX_ABRT_SLVRD_INTX_Pos)
#define DW_IIC_TX_ABRT_SLVRD_INTX                  DW_IIC_TX_ABRT_SLVRD_INTX_Msk

/* IC_DMA_CR, offset: 0x88 */
#define DW_IIC_DMA_CR_RDMAE_Pos                    (0U)
#define DW_IIC_DMA_CR_RDMAE_Msk                    (0x1U << DW_IIC_DMA_CR_RDMAE_Pos)
#define DW_IIC_DMA_CR_RDMAE                        DW_IIC_DMA_CR_RDMAE_Msk

#define DW_IIC_DMA_CR_TDMAE_Pos                    (1U)
#define DW_IIC_DMA_CR_TDMAE_Msk                    (0x1U << DW_IIC_DMA_CR_TDMAE_Pos)
#define DW_IIC_DMA_CR_TDMAE                        DW_IIC_DMA_CR_TDMAE_Msk

/* IC_DMA_TDLR, offset: 0x8C */
#define DW_IIC_DMA_TDLR_Msk                        (0x7U)
/* IC_DMA_RDLR, offset: 0x90 */
#define DW_IIC_DMA_RDLR_Msk                        (0x7U)

/* IC_GEN_CALL_EN, offset: 0xA0 */
//no this register
#define DW_IIC_GEN_CALL_EN_Pos                     (0U)
#define DW_IIC_GEN_CALL_EN_Msk                     (0x1U << DW_IIC_GEN_CALL_EN_Pos)
#define DW_IIC_GEN_CALL_EN                         DW_IIC_GEN_CALL_EN_Msk

/* IC_FIFO_RST_EN, offset: 0xA4 */
//no this register
#define DW_IIC_FIFO_RST_EN_Pos                     (0U)
#define DW_IIC_FIFO_RST_EN_Msk                     (0x1U << DW_IIC_FIFO_RST_EN_Pos)
#define DW_IIC_FIFO_RST_EN                         DW_IIC_FIFO_RST_EN_Msk

#define TXFIFO_IRQ_TH                              (0x4U)
#define RXFIFO_IRQ_TH                              (0x2U)
#define IIC_MAX_FIFO                               (0x8U)

/* IIC default value definitions */
#define DW_IIC_TIMEOUT_DEF_VAL  0x1000U

#define DW_IIC_EEPROM_MAX_WRITE_LEN  0X1U

typedef struct {
    volatile uint32_t IC_CON;                    /* Offset: 0x000 (R/W)  I2C Control */
    volatile uint32_t IC_TAR;                    /* Offset: 0x004 (R/W)  I2C target address */
    volatile uint32_t IC_SAR;                    /* Offset: 0x008 (R/W)  I2C slave address  */
    volatile uint32_t IC_HS_MADDR;               /* Offset: 0x00C (R/W)  I2C HS Master Mode Code Address */
    volatile uint32_t IC_DATA_CMD;               /* Offset: 0x010 (R/W)  I2C RX/TX Data Buffer and Command */
    volatile uint32_t IC_SS_SCL_HCNT;            /* Offset: 0x014 (R/W)  Standard speed I2C Clock SCL High Count */
    volatile uint32_t IC_SS_SCL_LCNT;            /* Offset: 0x018 (R/W)  Standard speed I2C Clock SCL Low Count */
    volatile uint32_t IC_FS_SCL_HCNT;            /* Offset: 0x01C (R/W)  Fast speed I2C Clock SCL High Count */
    volatile uint32_t IC_FS_SCL_LCNT;            /* Offset: 0x020 (R/W)  Fast speed I2C Clock SCL Low Count */
    volatile uint32_t IC_HS_SCL_HCNT;            /* Offset: 0x024 (R/W)  High speed I2C Clock SCL High Count*/
    volatile uint32_t IC_HS_SCL_LCNT;            /* Offset: 0x028 (R/W)  High speed I2C Clock SCL Low Count */
    volatile const  uint32_t IC_INTR_STAT;              /* Offset: 0x02C (R)    I2C Interrupt Status */
    volatile uint32_t IC_INTR_MASK;              /* Offset: 0x030 (R/W)  I2C Interrupt Mask */
    volatile const  uint32_t IC_RAW_INTR_STAT;          /* Offset: 0x034 (R)    I2C Raw Interrupt Status */
    volatile uint32_t IC_RX_TL;                  /* Offset: 0x038 (R/W)  I2C Receive FIFO Threshold */
    volatile uint32_t IC_TX_TL;                  /* Offset: 0x03C (R/W)  I2C Transmit FIFO Threshold */
    volatile const  uint32_t IC_CLR_INTR;               /* Offset: 0x040 (R)    Clear combined and individual interrupts*/
    volatile const  uint32_t IC_CLR_RX_UNDER;           /* Offset: 0x044 (R)    I2C Clear RX_UNDER interrupt  */
    volatile const  uint32_t IC_CLR_RX_OVER;            /* Offset: 0x048 (R)    I2C Clear RX_OVER interrupt  */
    volatile const  uint32_t IC_CLR_TX_OVER;            /* Offset: 0x04C (R)    I2C Clear TX_OVER interrupt  */
    volatile const  uint32_t IC_CLR_RD_REQ;             /* Offset: 0x050 (R)    I2C Clear RD_REQ interrupt  */
    volatile const  uint32_t IC_CLR_TX_ABRT;            /* Offset: 0x054 (R)    I2C Clear TX_ABRT interrupt  */
    volatile const  uint32_t IC_CLR_RX_DONE;            /* Offset: 0x058 (R)    I2C Clear RX_DONE interrupt  */
    volatile const  uint32_t IC_CLR_ACTIVITY;           /* Offset: 0x05C (R)    I2C Clear ACTIVITY interrupt  */
    volatile const  uint32_t IC_CLR_STOP_DET;           /* Offset: 0x060 (R)    I2C Clear STOP_DET interrupt  */
    volatile const  uint32_t IC_CLR_START_DET;          /* Offset: 0x064 (R)    I2C Clear START_DET interrupt  */
    volatile const  uint32_t IC_CLR_GEN_CALL;           /* Offset: 0x068 (R)    I2C Clear GEN_CAL interrupt  */
    volatile uint32_t IC_ENABLE;                 /* Offset: 0x06C (R/W)  I2C enable */
    volatile const  uint32_t IC_STATUS;                 /* Offset: 0x070 (R)    I2C status register */
    volatile const  uint32_t IC_TXFLR;                  /* Offset: 0x074 (R)    Transmit FIFO Level register */
    volatile const  uint32_t IC_RXFLR;                  /* Offset: 0x078 (R)    Receive FIFO Level Register */
    volatile uint32_t IC_SDA_HOLD;               /* Offset: 0x07C (R/W)  SDA hold time register */
    volatile uint32_t IC_TX_ABRT_SOURCE;         /* Offset: 0x080 (R/W)  I2C Transmit Abort Status Register */
    volatile uint32_t IC_SLV_DAT_NACK_ONLY;      /* Offset: 0x084 (R/W)  I2C Slave Address1 */
    volatile uint32_t IC_DMA_CR;                 /* Offset: 0x088 (R/W)  DMA Control Register for transmit and receive handshaking interface  */
    volatile uint32_t IC_DMA_TDLR;               /* Offset: 0x08C (R/W)  DMA Transmit Data Level */
    volatile uint32_t IC_DMA_RDLR;               /* Offset: 0x090 (R/W)  DMA Receive Data Level */
    volatile uint32_t IC_SDA_SETUP;              /* Offset: 0x094 (R/W)  I2C Slave Address2 */
    volatile uint32_t IC_ACK_GENERAL_CALL;       /* Offset: 0x098 (R/W)  I2C Slave Address3 */
    volatile uint32_t IC_ENABLE_STATUS;          /* Offset: 0x09C (R/W)  I2C address number in slave mode */
    volatile uint32_t IC_FS_SPKLEN;              /* Offset: 0x0A0 (R/W)  I2C general call mask register when I2C is in the slave mode */
    volatile uint32_t IC_HS_SPKLEN;              /* Offset: 0x0A4 (R/W)  I2C FIFO flush register when I2C is in the slave transfer mode*/
} dw_iic_regs_t;

static inline void dw_iic_enable(dw_iic_regs_t *iic_base)
{
    iic_base->IC_ENABLE = DW_IIC_EN;
}

static inline void dw_iic_disable(dw_iic_regs_t *iic_base)
{
    /* First clear ACTIVITY, then Disable IIC */
    iic_base->IC_CLR_ACTIVITY;
    iic_base->IC_ENABLE = ~DW_IIC_EN;
}

static inline uint32_t dw_iic_get_iic_status(dw_iic_regs_t *iic_base)
{
    return iic_base->IC_ENABLE;
}

static inline void dw_iic_enable_restart(dw_iic_regs_t *iic_base)
{
    iic_base->IC_CON |= DW_IIC_CON_RESTART_EN;
}

static inline void dw_iic_master_enable_transmit_irq(dw_iic_regs_t *iic_base)
{
    iic_base->IC_INTR_MASK =  DW_IIC_INTR_TX_EMPTY | DW_IIC_INTR_TX_OVER | DW_IIC_INTR_STOP_DET;
    iic_base->IC_CLR_INTR;
}

static inline void dw_iic_slave_enable_transmit_irq(dw_iic_regs_t *iic_base)
{
    iic_base->IC_INTR_MASK = DW_IIC_INTR_RD_REQ | DW_IIC_INTR_STOP_DET;
    iic_base->IC_CLR_INTR;
}

static inline void dw_iic_master_enable_receive_irq(dw_iic_regs_t *iic_base)
{
    iic_base->IC_INTR_MASK = DW_IIC_INTR_STOP_DET | DW_IIC_INTR_RX_FULL | DW_IIC_INTR_RX_OVER;
    iic_base->IC_CLR_INTR;
}

static inline void dw_iic_slave_enable_receive_irq(dw_iic_regs_t *iic_base)
{
    iic_base->IC_INTR_MASK = DW_IIC_INTR_STOP_DET | DW_IIC_INTR_RX_FULL;
    iic_base->IC_CLR_INTR;
}

static inline void dw_iic_clear_all_irq(dw_iic_regs_t *iic_base)
{
    iic_base->IC_CLR_INTR;
    iic_base->IC_CLR_RX_UNDER;
    iic_base->IC_CLR_RX_OVER;
    iic_base->IC_CLR_TX_OVER;
    iic_base->IC_CLR_RD_REQ;
    iic_base->IC_CLR_TX_ABRT;
    iic_base->IC_CLR_RX_DONE;
    iic_base->IC_CLR_ACTIVITY;
    iic_base->IC_CLR_STOP_DET;
    iic_base->IC_CLR_START_DET;
    iic_base->IC_CLR_GEN_CALL;
}

static inline void dw_iic_set_sda_hold_time(dw_iic_regs_t *iic_base, uint32_t val)
{
    iic_base->IC_SDA_HOLD = val;
}

static inline void dw_iic_flush_rxfifo(dw_iic_regs_t *iic_base)
{
    while (iic_base->IC_STATUS & DW_IIC_RXFIFO_NOT_EMPTY_STATE)
        iic_base->IC_DATA_CMD;
}

static inline void dw_iic_set_slave_10bit_addr_mode(dw_iic_regs_t *iic_base)
{
    iic_base->IC_CON |= DW_IIC_CON_SLAVE_ADDR_MODE;
}

static inline void dw_iic_set_slave_7bit_addr_mode(dw_iic_regs_t *iic_base)
{
    iic_base->IC_CON &= ~DW_IIC_CON_SLAVE_ADDR_MODE;
}

static inline void dw_iic_set_master_10bit_addr_mode(dw_iic_regs_t *iic_base)
{
    iic_base->IC_TAR |= DW_IIC_TAR_MASTER_ADDR_MODE;
}

static inline void dw_iic_set_master_7bit_addr_mode(dw_iic_regs_t *iic_base)
{
    iic_base->IC_TAR &= ~DW_IIC_TAR_MASTER_ADDR_MODE;
    iic_base->IC_CON &= ~DW_IIC_CON_MASTER_ADDR_MODE;
}

static inline void dw_iic_set_standard_scl_hcnt(dw_iic_regs_t *iic_base, uint32_t cnt)
{
    iic_base->IC_SS_SCL_HCNT = cnt;
}

static inline void dw_iic_set_standard_scl_lcnt(dw_iic_regs_t *iic_base, uint32_t cnt)
{
    iic_base->IC_SS_SCL_LCNT = cnt;
}

static inline void dw_iic_set_fast_scl_hcnt(dw_iic_regs_t *iic_base, uint32_t cnt)
{
    iic_base->IC_FS_SCL_HCNT = cnt;
}

static inline void dw_iic_set_fast_scl_lcnt(dw_iic_regs_t *iic_base, uint32_t cnt)
{
    iic_base->IC_FS_SCL_LCNT = cnt;
}

static inline void dw_iic_set_high_scl_hcnt(dw_iic_regs_t *iic_base, uint32_t cnt)
{
    iic_base->IC_HS_SCL_HCNT = cnt;
}

static inline void dw_iic_set_high_scl_lcnt(dw_iic_regs_t *iic_base, uint32_t cnt)
{
    iic_base->IC_HS_SCL_LCNT = cnt;
}

static inline void dw_iic_set_own_address(dw_iic_regs_t *iic_base, uint32_t address)
{
    iic_base->IC_SAR = address;
}

static inline void dw_iic_set_transmit_fifo_threshold(dw_iic_regs_t *iic_base, uint32_t level)
{
    iic_base->IC_TX_TL = level;
}

static inline void dw_iic_set_receive_fifo_threshold(dw_iic_regs_t *iic_base, uint32_t level)
{
    iic_base->IC_RX_TL = level - 1U;
}

static inline uint32_t dw_iic_get_transmit_fifo_num(dw_iic_regs_t *iic_base)
{
    return iic_base->IC_TXFLR;
}

static inline uint32_t dw_iic_get_receive_fifo_num(dw_iic_regs_t *iic_base)
{
    return iic_base->IC_RXFLR;
}

static inline void dw_iic_transmit_data(dw_iic_regs_t *iic_base, uint16_t data)
{
    iic_base->IC_DATA_CMD = data;
}

static inline uint8_t dw_iic_receive_data(dw_iic_regs_t *iic_base)
{
    return (uint8_t)iic_base->IC_DATA_CMD;
}

static inline void dw_iic_data_cmd(dw_iic_regs_t *iic_base)
{
    iic_base->IC_DATA_CMD = DW_IIC_DATA_CMD;
}

static inline void dw_iic_data_cmd_stop(dw_iic_regs_t *iic_base)
{
    iic_base->IC_DATA_CMD = DW_IIC_DATA_CMD | (1<<9);
}

static inline void dw_iic_fifo_rst(dw_iic_regs_t *iic_base, uint32_t en)
{
    //no this register
    //iic_base->IC_FIFO_RST_EN = (en & DW_IIC_FIFO_RST_EN_Msk);
}

static inline void dw_iic_dma_transmit_enable(dw_iic_regs_t *iic_base)
{
    iic_base->IC_DMA_CR |= DW_IIC_DMA_CR_TDMAE;
}

static inline void dw_iic_dma_transmit_disable(dw_iic_regs_t *iic_base)
{
    iic_base->IC_DMA_CR &= ~DW_IIC_DMA_CR_TDMAE;
}

static inline void dw_iic_dma_receive_enable(dw_iic_regs_t *iic_base)
{
    iic_base->IC_DMA_CR |= DW_IIC_DMA_CR_RDMAE;
}

static inline void dw_iic_dma_receive_disable(dw_iic_regs_t *iic_base)
{
    iic_base->IC_DMA_CR &= ~DW_IIC_DMA_CR_RDMAE;
}

static inline void dw_iic_dma_transmit_level(dw_iic_regs_t *iic_base, uint8_t level)
{
    iic_base->IC_DMA_TDLR = ((uint32_t)level & DW_IIC_DMA_TDLR_Msk);
}

static inline void dw_iic_dma_receive_level(dw_iic_regs_t *iic_base, uint8_t level)
{
    iic_base->IC_DMA_RDLR = ((uint32_t)level & DW_IIC_DMA_RDLR_Msk);
}

static inline uint32_t dw_iic_get_raw_interrupt_state(dw_iic_regs_t *iic_base)
{
    return iic_base->IC_RAW_INTR_STAT;
}

static inline void dw_iic_disable_all_irq(dw_iic_regs_t *iic_base)
{
    iic_base->IC_INTR_MASK = 0U;
}

static inline uint32_t dw_iic_read_clear_intrbits(dw_iic_regs_t *iic_base)
{
    uint32_t  stat = 0U;

    stat = iic_base->IC_INTR_STAT;

    if (stat & DW_IIC_INTR_RX_UNDER)
    {
        iic_base->IC_CLR_RX_UNDER;
    }

    if (stat & DW_IIC_INTR_RX_OVER)
    {
        iic_base->IC_CLR_RX_OVER;
    }

    if (stat & DW_IIC_INTR_TX_OVER)
    {
        iic_base->IC_CLR_TX_OVER;
    }

    if (stat & DW_IIC_INTR_RD_REQ)
    {
        iic_base->IC_CLR_RD_REQ;
    }

    if (stat & DW_IIC_INTR_TX_ABRT)
    {
        iic_base->IC_TX_ABRT_SOURCE;
    }

    if (stat & DW_IIC_INTR_RX_DONE)
    {
        iic_base->IC_CLR_RX_DONE;
    }

    if (stat & DW_IIC_INTR_ACTIVITY)
    {
        iic_base->IC_CLR_ACTIVITY;
    }

    if (stat & DW_IIC_INTR_STOP_DET)
    {
        iic_base->IC_CLR_STOP_DET;
    }

    if (stat & DW_IIC_INTR_START_DET)
    {
        iic_base->IC_CLR_START_DET;
    }

    if (stat & DW_IIC_INTR_GEN_CALL)
    {
        iic_base->IC_CLR_GEN_CALL;
    }

    return stat;
}

static inline uint32_t dw_iic_get_intrrupt_state(dw_iic_regs_t *iic_base)
{
    return iic_base->IC_INTR_STAT;
}

int rt_hw_i2c_init(void);

#endif /* __DRV_HW_I2C_H__ */
