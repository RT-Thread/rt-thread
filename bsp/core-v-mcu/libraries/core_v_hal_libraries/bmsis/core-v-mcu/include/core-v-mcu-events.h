/*
 * Copyright (C) 2019 ETH Zurich, University of Bologna and GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_EVENTS_H_
#define TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_EVENTS_H_
#include "core-v-mcu-properties.h"

/* Events offsets. */
#define UDMA_EVENT_OFFSET_RX            (0U)
#define UDMA_EVENT_OFFSET_TX            (1U)
#define EVENT_UART_RX            (2U)
#define EVENT_UART_ERR            (3U)

#define UDMA_EVENT_OFFSET_SPI_CMD       (2)
#define UDMA_EVENT_OFFSET_SPI_EOT       (3)

/* Number of events per peripheral. */
#define UDMA_CHANNEL_NB_EVENTS_LOG2     (2)
#define UDMA_CHANNEL_NB_EVENTS          (1 << UDMA_CHANNEL_NB_EVENTS_LOG2)

/* Number of SW events. */
#define NB_SW_EVENTS                    (8)

/*! @brief FC events (aka IRQ lines)*/
#define FC_EVENT_SW(id)                 (id & (NB_SW_EVENTS - 1))
#define FC_EVENT_DMA_EVT                (8)
#define FC_EVENT_DMA                    (9)
#define FC_EVENT_TIMER0                 (10) /* Timer low.  */
#define SYSTICK_IRQN                    FC_EVENT_TIMER0
#define FC_EVENT_TIMER1                 (11) /* Timer high. */
/* #define FC_EVENT_EU_HWCE                (12) */

/*
 * SoC event unit events: Many events get implicitely muxed into this interrupt.
 * A user that gets such an interrupt has to check the event unit's registers to
 * see what happened
 */
#define FC_EVENT_SOC_EVENT              (27)
/* #define FC_EVENT_MPU_ERROR              (28) */
/*
 * Event queue error: If we don't process event unit events quickly enough
 * internal fifos can overflow and we get this error interrupt
 */
#define FC_EVENT_FC_QUEUE_ERROR         (29)
#define FC_EVENT_HP0                runn     (30)
#define FC_EVENT_HP1                    (31)

/*! @name SoC events  */
/*! @brief Number of FC_Events. */
#define SOC_EU_NB_FC_EVENTS             (168)

/*! @brief UDMA events */
/* SPIM */
#define SOC_EVENT_UDMA_SPIM_RX(id)      ((UDMA_QSPIM_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_RX)
#define SOC_EVENT_UDMA_SPIM_TX(id)      ((UDMA_QSPIM_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_TX)
#define SOC_EVENT_UDMA_SPIM_CMD(id)     ((UDMA_QSPIM_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_SPI_CMD)
#define SOC_EVENT_UDMA_SPIM_EOT(id)     ((UDMA_QSPIM_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_SPI_EOT)
/* HYPER */
/* #define SOC_EVENT_UDMA_HYPER_RX(id)     ((UDMA_HYPER_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_RX) */
/* #define SOC_EVENT_UDMA_HYPER_TX(id)     ((UDMA_HYPER_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_TX) */
/* UART */
#define SOC_EVENT_UDMA_UART_RX(id)      ((UDMA_UART_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_RX)
#define SOC_EVENT_UDMA_UART_TX(id)      ((UDMA_UART_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_TX)
#define SOC_EVENT_UART_RX(id)           ((UDMA_UART_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + EVENT_UART_RX)
#define SOC_EVENT_UART_ERR(id)           ((UDMA_UART_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + EVENT_UART_ERR)
/* I2C */
#define SOC_EVENT_UDMA_I2C_RX(id)       ((UDMA_I2CM_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_RX)
#define SOC_EVENT_UDMA_I2C_TX(id)       ((UDMA_I2CM_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_TX)
/* DMACPY */
/* #define SOC_EVENT_UDMA_DMACPY_RX(id)    ((UDMA_DMACPY_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_RX) */
/* #define SOC_EVENT_UDMA_DMACPY_TX(id)    ((UDMA_DMACPY_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_TX) */
/* I2S */
#define SOC_EVENT_UDMA_I2S_RX(id)       ((UDMA_I2S_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_RX)
#define SOC_EVENT_UDMA_I2S_TX(id)       ((UDMA_I2S_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_TX)
/* CPI */
#define SOC_EVENT_UDMA_CAM_RX(id)       ((UDMA_CAM_ID(id) << UDMA_CHANNEL_NB_EVENTS_LOG2) + UDMA_EVENT_OFFSET_RX)

/* UDMA EOT & error events. */
//#define SOC_EVENT_UDMA_I2C_ERROR(id)  (26 + id)

/*! @brief PMU events, no pmu*/
/* #define SOC_EVENT_PMU_CLUSTER_POWER     (31) */
/* #define SOC_EVENT_PMU_CLUSTER_CG        (35) */
/* #define SOC_EVENT_PMU_DLC_BRIDGE_PICL   (36) */
/* #define SOC_EVENT_PMU_DLC_BRIDGE_SCU    (37) */
/* #define SOC_EVENT_PWM(id)               (38 + id) */
#define SOC_EVENT_GPIO                  (139)
#define SOC_EVENT_HWPE0                 (140)
#define SOC_EVENT_HWPE1                 (141)
/* #define SOC_EVENT_RTC_APB               (43) */
/* #define SOC_EVENT_RTC                   (44) */

#define SOC_EVENT_SW(id)                (160 + (id & (NB_SW_EVENTS - 1)))
#define SOC_EVENT_REF32K_CLK_RISE       (168)

/* @brief Cluster events */
#define CL_EVENT_SW(id)                 (id & (NB_SW_EVENTS - 1))
#define CL_EVENT_DMA0                   (8)
#define CL_EVENT_DMA1                   (9)
#define CL_EVENT_TIMER0_LO              (10)
#define CL_EVENT_TIMER0_HI              (11)
#define CL_EVENT_ACC0                   (12)
#define CL_EVENT_ACC1                   (13)
#define CL_EVENT_ACC2                   (14)
#define CL_EVENT_ACC3                   (15)
#define CL_EVENT_BAR                    (16)
#define CL_EVENT_MUTEX                  (17)
#define CL_EVENT_DISPATCH               (18)
/* #define CL_EVENT_CLUSTER0               (22) */
/* #define CL_EVENT_CLUSTER1               (23) */
#define CL_EVENT_SOC_EVT                (30) /* adapted */

#endif /* TARGET_CORE_V_MCU_INCLUDE_CORE_V_MCU_EVENTS_H_ */
