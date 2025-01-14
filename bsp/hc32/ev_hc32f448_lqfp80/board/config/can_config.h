/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#ifndef __CAN_CONFIG_H__
#define __CAN_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************************/
/***********************************************************************************************/
// The arguments of RT command RT_CAN_CMD_SET_CANFD
#define MCAN_FD_CLASSICAL                   0       /* CAN classical */
#define MCAN_FD_ISO_FD_NO_BRS               1       /* ISO CAN FD without BRS */
#define MCAN_FD_ISO_FD_BRS                  2       /* ISO CAN FD with BRS */
#define MCAN_FD_NON_ISO_FD_NO_BRS           3       /* non-ISO CAN FD without BRS */
#define MCAN_FD_NON_ISO_FD_BRS              4       /* non-ISO CAN FD with BRS */

#define MCAN_FD_ARG_MIN                     MCAN_FD_ISO_FD_NO_BRS
#define MCAN_FD_ARG_MAX                     MCAN_FD_NON_ISO_FD_BRS

/* The default configuration for MCANs. Users can modify the configurations based on the application.
   For the message RAM:
   1. MCAN1 and MCAN2 share 2048 bytes message RAM
   2. User can modify the definitions of filter number, Rx FIFO number, Tx FIFO number.
   3. MCAN has two conﬁgurable Receive FIFOs, Rx FIFO0 and Rx FIFO1. There use Rx FIFO0 only by default.
      If only one FIFO is needed, use Rx FIFO0. If Rx FIFO1 is needed, define it's macro between 1 and 64,
      and pay attention the total size of meesage RAM that to be allocated.
*/

#ifdef RT_CAN_USING_CANFD
#define MCAN_FD_SEL                     MCAN_FD_ISO_FD_BRS
#define MCAN_TOTAL_FILTER_NUM           (26U)
#define MCAN_STD_FILTER_NUM             (13U)                   /* Each standard filter element size is 4 bytes */
#define MCAN_EXT_FILTER_NUM             (13U)                   /* Each extended filter element size is 8 bytes */
#define MCAN_TX_FIFO_NUM                (6U)
#define MCAN_RX_FIFO_NUM                (6U)
#define MCAN_DATA_FIELD_SIZE            (MCAN_DATA_SIZE_64BYTE) /* Each FIFO element size is 64+8 bytes */
#else
#define MCAN_FD_SEL                     MCAN_FD_CLASSICAL
#define MCAN_TOTAL_FILTER_NUM           (32U)
#define MCAN_STD_FILTER_NUM             (16U)                   /* Each standard filter element size is 4 bytes */
#define MCAN_EXT_FILTER_NUM             (16U)                   /* Each extended filter element size is 8 bytes */
#define MCAN_TX_FIFO_NUM                (26U)
#define MCAN_RX_FIFO_NUM                (26U)
#define MCAN_DATA_FIELD_SIZE            (MCAN_DATA_SIZE_8BYTE)  /* Each FIFO element size is 8+8 bytes */
#endif

#ifdef BSP_USING_MCAN1
#define MCAN1_NAME                      ("can1")
#define MCAN1_WORK_MODE                 (RT_CAN_MODE_NORMAL)
#define MCAN1_TX_PRIV_MODE              RT_CAN_MODE_NOPRIV      /* RT_CAN_MODE_NOPRIV: Tx FIFO mode; RT_CAN_MODE_PRIV: Tx priority mode */

#define MCAN1_FD_SEL                    MCAN_FD_SEL

#define MCAN1_STD_FILTER_NUM            MCAN_STD_FILTER_NUM
#define MCAN1_EXT_FILTER_NUM            MCAN_EXT_FILTER_NUM

#define MCAN1_RX_FIFO0_NUM              MCAN_RX_FIFO_NUM
#define MCAN1_RX_FIFO0_DATA_FIELD_SIZE  MCAN_DATA_FIELD_SIZE

#define MCAN1_TX_FIFO_NUM               MCAN_TX_FIFO_NUM
#define MCAN1_TX_FIFO_DATA_FIELD_SIZE   MCAN_DATA_FIELD_SIZE
#define MCAN1_TX_NOTIFICATION_BUF       ((1UL << MCAN1_TX_FIFO_NUM) - 1U)
#endif /* BSP_USING_MCAN1 */

#ifdef BSP_USING_MCAN2
#define MCAN2_NAME                      ("can2")
#define MCAN2_WORK_MODE                 (RT_CAN_MODE_NORMAL)
#define MCAN2_TX_PRIV_MODE              RT_CAN_MODE_NOPRIV      /* RT_CAN_MODE_NOPRIV: Tx FIFO mode; RT_CAN_MODE_PRIV: Tx priority mode */

#define MCAN2_FD_SEL                    MCAN_FD_SEL
#define MCAN2_STD_FILTER_NUM            MCAN_STD_FILTER_NUM
#define MCAN2_EXT_FILTER_NUM            MCAN_EXT_FILTER_NUM

#define MCAN2_RX_FIFO0_NUM              MCAN_RX_FIFO_NUM
#define MCAN2_RX_FIFO0_DATA_FIELD_SIZE  MCAN_DATA_FIELD_SIZE

#define MCAN2_TX_FIFO_NUM               MCAN_TX_FIFO_NUM
#define MCAN2_TX_FIFO_DATA_FIELD_SIZE   MCAN_DATA_FIELD_SIZE
#define MCAN2_TX_NOTIFICATION_BUF       ((1UL << MCAN2_TX_FIFO_NUM) - 1U)
#endif /* BSP_USING_MCAN2 */

/***********************************************************************************************/
/***********************************************************************************************/

/*
  Bit rate configuration examples for CAN FD.
  Nominal bit rate for CAN FD arbitration phase and data bit rate for CAN FD data phase.
  BitRate(bps) = MCANClock(Hz) / (Prescaler * (TimeSeg1 + TimeSeg2))
  SamplePoint(%) = TimeSeg1 / (TimeSeg1 + TimeSeg2)
  eg.
  BitRate(bps) = 40000000(Hz) / (2 * (16 + 4)) = 1000000 = 1M(bps)
  SamplePoint(%) = 16 / (16 + 4) = 80%
  The following bit rate configurations are based on the max MCAN Clock(40MHz).
  NOTE:
  1. It is better to limit u32NominalPrescaler and u32DataPrescaler between 1 and 2.
  1. The unit of u32SspOffset is MCANClock.
  2. For the corresponding function of u32TdcFilter, please refer to the reference manual for details(TDCR.TDCF).
     The u32TdcFilter can be get from PSR.TDCV.
*/
#define MCAN_FD_CFG_500K_1M                                 \
    {                                                       \
    .u32NominalPrescaler = 1,                               \
    .u32NominalTimeSeg1 = 64,                               \
    .u32NominalTimeSeg2 = 16,                               \
    .u32NominalSyncJumpWidth = 16,                          \
    .u32DataPrescaler = 1,                                  \
    .u32DataTimeSeg1 = 32,                                  \
    .u32DataTimeSeg2 = 8,                                   \
    .u32DataSyncJumpWidth = 8,                              \
    .u32TDC = MCAN_FD_TDC_ENABLE,                           \
    .u32SspOffset = 32,                                     \
    .u32TdcFilter = 32 + 1,                                 \
    }

#define MCAN_FD_CFG_500K_2M                                 \
    {                                                       \
    .u32NominalPrescaler = 1,                               \
    .u32NominalTimeSeg1 = 64,                               \
    .u32NominalTimeSeg2 = 16,                               \
    .u32NominalSyncJumpWidth = 16,                          \
    .u32DataPrescaler = 1,                                  \
    .u32DataTimeSeg1 = 16,                                  \
    .u32DataTimeSeg2 = 4,                                   \
    .u32DataSyncJumpWidth = 4,                              \
    .u32TDC = MCAN_FD_TDC_ENABLE,                           \
    .u32SspOffset = 16,                                     \
    .u32TdcFilter = 16 + 1,                                 \
    }

#define MCAN_FD_CFG_500K_4M                                 \
    {                                                       \
    .u32NominalPrescaler = 1,                               \
    .u32NominalTimeSeg1 = 64,                               \
    .u32NominalTimeSeg2 = 16,                               \
    .u32NominalSyncJumpWidth = 16,                          \
    .u32DataPrescaler = 1,                                  \
    .u32DataTimeSeg1 = 8,                                   \
    .u32DataTimeSeg2 = 2,                                   \
    .u32DataSyncJumpWidth = 2,                              \
    .u32TDC = MCAN_FD_TDC_ENABLE,                           \
    .u32SspOffset = 8,                                      \
    .u32TdcFilter = 8 + 1,                                  \
    }

#define MCAN_FD_CFG_500K_5M                                 \
    {                                                       \
    .u32NominalPrescaler = 1,                               \
    .u32NominalTimeSeg1 = 64,                               \
    .u32NominalTimeSeg2 = 16,                               \
    .u32NominalSyncJumpWidth = 16,                          \
    .u32DataPrescaler = 1,                                  \
    .u32DataTimeSeg1 = 6,                                   \
    .u32DataTimeSeg2 = 2,                                   \
    .u32DataSyncJumpWidth = 2,                              \
    .u32TDC = MCAN_FD_TDC_ENABLE,                           \
    .u32SspOffset = 6,                                      \
    .u32TdcFilter = 6 + 1,                                  \
    }

#define MCAN_FD_CFG_500K_8M                                 \
    {                                                       \
    .u32NominalPrescaler = 1,                               \
    .u32NominalTimeSeg1 = 64,                               \
    .u32NominalTimeSeg2 = 16,                               \
    .u32NominalSyncJumpWidth = 16,                          \
    .u32DataPrescaler = 1,                                  \
    .u32DataTimeSeg1 = 4,                                   \
    .u32DataTimeSeg2 = 1,                                   \
    .u32DataSyncJumpWidth = 1,                              \
    .u32TDC = MCAN_FD_TDC_ENABLE,                           \
    .u32SspOffset = 4,                                      \
    .u32TdcFilter = 4 + 1,                                  \
    }

#define MCAN_FD_CFG_1M_1M                                   \
    {                                                       \
    .u32NominalPrescaler = 1,                               \
    .u32NominalTimeSeg1 = 32,                               \
    .u32NominalTimeSeg2 = 8,                                \
    .u32NominalSyncJumpWidth = 8,                           \
    .u32DataPrescaler = 1,                                  \
    .u32DataTimeSeg1 = 32,                                  \
    .u32DataTimeSeg2 = 8,                                   \
    .u32DataSyncJumpWidth = 8,                              \
    .u32TDC = MCAN_FD_TDC_ENABLE,                           \
    .u32SspOffset = 2*32,                                   \
    .u32TdcFilter = 2*32 + 1,                               \
    }

#define MCAN_FD_CFG_1M_2M                                   \
    {                                                       \
    .u32NominalPrescaler = 1,                               \
    .u32NominalTimeSeg1 = 32,                               \
    .u32NominalTimeSeg2 = 8,                                \
    .u32NominalSyncJumpWidth = 8,                           \
    .u32DataPrescaler = 1,                                  \
    .u32DataTimeSeg1 = 16,                                  \
    .u32DataTimeSeg2 = 4,                                   \
    .u32DataSyncJumpWidth = 4,                              \
    .u32TDC = MCAN_FD_TDC_ENABLE,                           \
    .u32SspOffset = 16,                                     \
    .u32TdcFilter = 16 + 1,                                 \
    }

#define MCAN_FD_CFG_1M_4M                                   \
    {                                                       \
    .u32NominalPrescaler = 1,                               \
    .u32NominalTimeSeg1 = 32,                               \
    .u32NominalTimeSeg2 = 8,                                \
    .u32NominalSyncJumpWidth = 8,                           \
    .u32DataPrescaler = 1,                                  \
    .u32DataTimeSeg1 = 8,                                   \
    .u32DataTimeSeg2 = 2,                                   \
    .u32DataSyncJumpWidth = 2,                              \
    .u32TDC = MCAN_FD_TDC_ENABLE,                           \
    .u32SspOffset = 8,                                      \
    .u32TdcFilter = 8 + 1,                                  \
    }

#define MCAN_FD_CFG_1M_5M                                   \
    {                                                       \
    .u32NominalPrescaler = 1,                               \
    .u32NominalTimeSeg1 = 64,                               \
    .u32NominalTimeSeg2 = 16,                               \
    .u32NominalSyncJumpWidth = 16,                          \
    .u32DataPrescaler = 1,                                  \
    .u32DataTimeSeg1 = 6,                                   \
    .u32DataTimeSeg2 = 2,                                   \
    .u32DataSyncJumpWidth = 2,                              \
    .u32TDC = MCAN_FD_TDC_ENABLE,                           \
    .u32SspOffset = 6,                                      \
    .u32TdcFilter = 6 + 1,                                  \
    }

#define MCAN_FD_CFG_1M_8M                                   \
    {                                                       \
    .u32NominalPrescaler = 1,                               \
    .u32NominalTimeSeg1 = 64,                               \
    .u32NominalTimeSeg2 = 16,                               \
    .u32NominalSyncJumpWidth = 16,                          \
    .u32DataPrescaler = 1,                                  \
    .u32DataTimeSeg1 = 4,                                   \
    .u32DataTimeSeg2 = 1,                                   \
    .u32DataSyncJumpWidth = 1,                              \
    .u32TDC = MCAN_FD_TDC_ENABLE,                           \
    .u32SspOffset = 4,                                      \
    .u32TdcFilter = 4 + 1,                                  \
    }

/*
  Bit rate configuration examples for classical CAN.
  BitRate(bps) = MCANClock(Hz) / (u32NominalPrescaler * (u32NominalTimeSeg1 + u32NominalTimeSeg2))
  SamplePoint(%) = u32NominalTimeSeg1 / (u32NominalTimeSeg1 + u32NominalTimeSeg2)
  eg.
  BitRate(bps) = 40000000(Hz) / (2 * (16 + 4)) = 1000000 = 1M(bps)
  SamplePoint(%) = 16 / (16 + 4) = 80%
  The following bit rate configurations are based on the max MCAN Clock(40MHz).
*/
#define MCAN_CC_CFG_1M                                      \
    {                                                       \
    .u32NominalPrescaler = 2,                               \
    .u32NominalTimeSeg1 = 16,                               \
    .u32NominalTimeSeg2 = 4,                                \
    .u32NominalSyncJumpWidth = 4,                           \
    }

#define MCAN_CC_CFG_800K                                    \
    {                                                       \
    .u32NominalPrescaler = 2,                               \
    .u32NominalTimeSeg1 = 20,                               \
    .u32NominalTimeSeg2 = 5,                                \
    .u32NominalSyncJumpWidth = 5,                           \
    }

#define MCAN_CC_CFG_500K                                    \
    {                                                       \
    .u32NominalPrescaler = 4,                               \
    .u32NominalTimeSeg1 = 16,                               \
    .u32NominalTimeSeg2 = 4,                                \
    .u32NominalSyncJumpWidth = 4,                           \
    }

#define MCAN_CC_CFG_250K                                    \
    {                                                       \
    .u32NominalPrescaler = 4,                               \
    .u32NominalTimeSeg1 = 32,                               \
    .u32NominalTimeSeg2 = 8,                                \
    .u32NominalSyncJumpWidth = 8,                           \
    }

#define MCAN_CC_CFG_125K                                    \
    {                                                       \
    .u32NominalPrescaler = 8,                               \
    .u32NominalTimeSeg1 = 32,                               \
    .u32NominalTimeSeg2 = 8,                                \
    .u32NominalSyncJumpWidth = 8,                           \
    }

#define MCAN_CC_CFG_100K                                    \
    {                                                       \
    .u32NominalPrescaler = 10,                              \
    .u32NominalTimeSeg1 = 32,                               \
    .u32NominalTimeSeg2 = 8,                                \
    .u32NominalSyncJumpWidth = 8,                           \
    }

#define MCAN_CC_CFG_50K                                     \
    {                                                       \
    .u32NominalPrescaler = 20,                              \
    .u32NominalTimeSeg1 = 32,                               \
    .u32NominalTimeSeg2 = 8,                                \
    .u32NominalSyncJumpWidth = 8,                           \
    }

#define MCAN_CC_CFG_20K                                     \
    {                                                       \
    .u32NominalPrescaler = 50,                              \
    .u32NominalTimeSeg1 = 32,                               \
    .u32NominalTimeSeg2 = 8,                                \
    .u32NominalSyncJumpWidth = 8,                           \
    }

#define MCAN_CC_CFG_10K                                     \
    {                                                       \
    .u32NominalPrescaler = 100,                             \
    .u32NominalTimeSeg1 = 32,                               \
    .u32NominalTimeSeg2 = 8,                                \
    .u32NominalSyncJumpWidth = 8,                           \
    }

#ifdef RT_CAN_USING_CANFD
#define MCAN1_BAUD_RATE_CFG             MCAN_FD_CFG_1M_4M
#define MCAN1_NOMINAL_BAUD_RATE         MCANFD_NOMINAL_BAUD_1M
#define MCAN1_DATA_BAUD_RATE            MCANFD_DATA_BAUD_4M

#define MCAN2_BAUD_RATE_CFG             MCAN_FD_CFG_1M_4M
#define MCAN2_NOMINAL_BAUD_RATE         MCANFD_NOMINAL_BAUD_1M
#define MCAN2_DATA_BAUD_RATE            MCANFD_DATA_BAUD_4M

#else
#define MCAN1_BAUD_RATE_CFG             MCAN_CC_CFG_1M
#define MCAN1_NOMINAL_BAUD_RATE         CAN1MBaud
#define MCAN1_DATA_BAUD_RATE            0

#define MCAN2_BAUD_RATE_CFG             MCAN_CC_CFG_1M
#define MCAN2_NOMINAL_BAUD_RATE         CAN1MBaud
#define MCAN2_DATA_BAUD_RATE            0

#endif /* #ifdef RT_CAN_USING_CANFD */

/***********************************************************************************************/
/***********************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __CAN_CONFIG_H__ */


