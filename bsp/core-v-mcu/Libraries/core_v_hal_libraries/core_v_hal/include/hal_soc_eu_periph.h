/*
 * Copyright 2020 GreenWaves Technologies
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef HAL_INCLUDE_HAL_SOC_EU_PERIPH_H_
#define HAL_INCLUDE_HAL_SOC_EU_PERIPH_H_

#include "core-v-mcu-target.h"
#include "pulp_io.h"

/*!
 * @addtogroup soc_eu
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* FC SOC domain events, all delegated by FC_SOC_EVENT_IRQn = 27 */
/* TODO: garbage collect this */
#define    UDMA_EVENT_LVDS_RX              0
#define    UDMA_EVENT_LVDS_TX              1
#define    UDMA_EVENT_SPIM0_RX             2
#define    UDMA_EVENT_SPIM0_TX             3
#define    UDMA_EVENT_SPIM1_RX             4
#define    UDMA_EVENT_SPIM1_TX             5
#define    UDMA_EVENT_HYPERBUS_RX          6
#define    UDMA_EVENT_HYPERBUS_TX          7
#define    UDMA_EVENT_UART_RX              8
#define    UDMA_EVENT_UART_TX              9
#define    UDMA_EVENT_I2C0_RX              10
#define    UDMA_EVENT_I2C0_TX              11
#define    UDMA_EVENT_I2C1_RX              12
#define    UDMA_EVENT_I2C1_TX              13
#define    UDMA_EVENT_DMACPY_RX            14
#define    UDMA_EVENT_DMACPY_TX            15
#define    UDMA_EVENT_SAI_CH0              16
#define    UDMA_EVENT_SAI_CH1              17
#define    UDMA_EVENT_CPI_RX               18
#define    UDMA_EVENT_RESERVED0            19

#define    UDMA_EVENT_LVDS_GEN0            20
#define    UDMA_EVENT_LVDS_GEN1            21
#define    UDMA_EVENT_SPIM0_EOT            22
#define    UDMA_EVENT_SPIM1_EOT            23
#define    UDMA_EVENT_HYPERBUS_RESERVED    24
#define    UDMA_EVENT_UART_RESERVED        25
#define    UDMA_EVENT_I2C0_ERROR           26
#define    UDMA_EVENT_I2C1_ERROR           27
#define    UDMA_EVENT_I2S_RESERVED         28
#define    UDMA_EVENT_CAM_RESERVED         29
#define    UDMA_EVENT_RESERVED1            30

#define    PMU_EVENT_CLUSTER_POWER_ON      31
#define    PMU_EVENT_CLUSTER_RESERVED0     32
#define    PMU_EVENT_CLUSTER_RESERVED1     33
#define    PMU_EVENT_CLUSTER_RESERVED2     34
#define    PMU_EVENT_CLUSTER_CLOCK_GATING  35
#define    PMU_DLC_EVENT_BRIDGE_PICL_OK    36
#define    PMU_DLC_EVENT_BRIDGE_SCU_OK     37
#define    PMU_EVENTS_NUM                  7

#define    PWM0_EVENT                      38
#define    PWM1_EVENT                      39
#define    PWM2_EVENT                      40
#define    PWM3_EVENT                      41
#define    GPIO_EVENT                      42              /**< GPIO group interrupt */
#define    RTC_APB_EVENT                   43
#define    RTC_EVENT                       44
#define    EVENT_RESERVED0                 45
#define    EVENT_RESERVED1                 46
#define    EVENT_RESERVED2                 47

#define    SOC_SW_EVENT0                   48              /**< GAP8 SOC SW Event0 */
#define    SOC_SW_EVENT1                   49              /**< GAP8 SOC SW Event1 */
#define    SOC_SW_EVENT2                   50              /**< GAP8 SOC SW Event2 */
#define    SOC_SW_EVENT3                   51              /**< GAP8 SOC SW Event3 */
#define    SOC_SW_EVENT4                   52              /**< GAP8 SOC SW Event4 */
#define    SOC_SW_EVENT5                   53              /**< GAP8 SOC SW Event5 */
#define    SOC_SW_EVENT6                   54              /**< GAP8 SOC SW Event6 */
#define    SOC_SW_EVENT7                   55              /**< GAP8 SOC SW Event7 */
#define    REF32K_CLK_RISE_EVENT           56              /**< GAP8 SOC EU SW Event Reference 32K Clock event */

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

static inline void soc_eu_fc_write(uint32_t val, uint32_t reg)
{
	writew(val, (uintptr_t)(SOC_EU_ADDR + SOC_FC_MASK0_OFFSET + reg));
}

static inline uint32_t soc_eu_fc_read(uint32_t reg)
{
	return readw((uintptr_t)(SOC_EU_ADDR + SOC_FC_MASK0_OFFSET + reg));
}

static inline void soc_eu_cl_write(uint32_t val, uint32_t reg)
{
	writew(val, (uintptr_t)(SOC_EU_ADDR + SOC_CL_MASK0_OFFSET + reg));
}

static inline uint32_t soc_eu_cl_read(uint32_t reg)
{
	return readw((uintptr_t)(SOC_EU_ADDR + SOC_CL_MASK0_OFFSET + reg));
}

static inline void soc_eu_pr_write(uint32_t val, uint32_t reg)
{
	writew(val, (uintptr_t)(SOC_EU_ADDR + SOC_PR_MASK0_OFFSET + reg));
}

static inline uint32_t soc_eu_pr_read(uint32_t reg)
{
	return readw((uintptr_t)(SOC_EU_ADDR + SOC_PR_MASK0_OFFSET + reg));
}

static inline void hal_soc_eu_set_fc_mask(int evt) {
	if (evt >= 256 || evt < 0)
		return;

	int shift = evt % 32;
	uint32_t reg_offset = evt/32 * 4;
	soc_eu_fc_write(soc_eu_fc_read(reg_offset) & ~(1 << shift), reg_offset);
}

static inline void hal_soc_eu_set_pr_mask(int evt) {
	if (evt >= 256 || evt < 0)
		return;

	int shift = evt % 32;
	uint32_t reg_offset = evt/32 * 4;
	soc_eu_pr_write(soc_eu_pr_read(reg_offset) & ~(1 << shift), reg_offset);
}

static inline void hal_soc_eu_set_cl_mask(int clusterId, int evt) {
	if (evt >= 256 || evt < 0)
		return;

	int shift = evt % 32;
	uint32_t reg_offset = evt/32 * 4;
	soc_eu_cl_write(soc_eu_cl_read(reg_offset) & ~(1 << shift), reg_offset);
}

static inline void hal_soc_eu_clear_fc_mask(int evt) {
	if (evt >= 256 || evt < 0)
		return;

	int shift = evt % 32;
	uint32_t reg_offset = evt/32 * 4;
	soc_eu_fc_write(soc_eu_fc_read(reg_offset) | (1 << shift), reg_offset);
}

static inline void hal_soc_eu_clear_pr_mask(int evt) {
	if (evt >= 256 || evt < 0)
		return;

	int shift = evt % 32;
	uint32_t reg_offset = evt/32 * 4;
	soc_eu_pr_write(soc_eu_pr_read(reg_offset) | (1 << shift), reg_offset);
}

static inline void hal_soc_eu_clear_cl_mask(int clusterId, int evt) {
	if (evt >= 256 || evt < 0)
		return;

	int shift = evt % 32;
	uint32_t reg_offset = evt/32 * 4;
	soc_eu_cl_write(soc_eu_cl_read(reg_offset) | (1 << shift), reg_offset);
}


static inline void hal_soc_eu_set_mask(uint32_t mask) {
	writew(mask, (uintptr_t)(SOC_EU_ADDR + SOC_EVENT_OFFSET));
}

static inline void hal_soc_eu_configure(int cluster, int event, int active) {
	abort();
	/* TODO: implement this */
/* #if SOC_SW_EVENT0 < 32 */
/*     uint32_t mask = (cluster == FC_CLUSTER_ID) ? (SOCEU->FC_MASK_LSB) : (SOCEU->CL_MASK_LSB); */
/*     int fullEvent = event - SOC_SW_EVENT0; */

/*     if (!active) */
/*       mask = mask | (1<<fullEvent); */
/*     else */
/*       mask = mask & ~(1<<fullEvent); */

/*     if (cluster == FC_CLUSTER_ID) */
/*       SOCEU->FC_MASK_LSB = mask; */
/*     else */
/*       SOCEU->CL_MASK_LSB = mask; */
/* #else */
/*     uint32_t mask = (cluster == FC_CLUSTER_ID) ? (SOCEU->FC_MASK_MSB) : (SOCEU->CL_MASK_MSB); */
/*     int fullEvent = event + SOC_SW_EVENT0 - 32; */

/*     if (!active) */
/*       mask = mask | (1<<fullEvent); */
/*     else */
/*       mask = mask & ~(1<<fullEvent); */

/*     if (cluster == FC_CLUSTER_ID) */
/*       SOCEU->FC_MASK_MSB = mask; */
/*     else */
/*       SOCEU->CL_MASK_MSB = mask; */
/* #endif */
}

/* static inline int SOC_EU_ReserveConfig(int cluster, int event) { */
/*   if (_bitfield_reserve(&soc_events_mask, event)) return -1; */
/*   SOC_EU_Configure(cluster, event, 1); */
/*   return 0; */
/* } */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* @} */


#endif /* HAL_INCLUDE_HAL_SOC_EU_PERIPH_H_ */
