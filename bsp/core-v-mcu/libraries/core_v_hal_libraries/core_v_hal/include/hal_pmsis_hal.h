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

/* This file shall be used for verification purpose only. */

#ifndef HAL_INCLUDE_HAL_PMSIS_HAL_H_
#define HAL_INCLUDE_HAL_PMSIS_HAL_H_


/* Hal includes. */

/* Event unit. */
//#include "event_unit/event_unit.h"

/* Efuse */
/* #include "efuse/pmsis_efuse.h" */

/* GPIO. */
#include "gpio/gpio.h"

/* PWM */
#include "pwm/pwm.h"
#include "pwm/pwm_ctrl.h"

/* RTC */
/* #include "rtc/rtc.h" */

/* Soc_ctrl. */
#include "soc_ctrl/soc_ctrl_pad.h"

/* Soc events generator. */
#include "soc_eu/soc_eu.h"

/* UDMA. */
#include "udma/udma_core.h"
/* #include "udma/udma_cpi.h" */
#include "udma/udma_ctrl.h"
/* #include "udma/udma_dmacpy.h" */
/* #include "udma/udma_hyper.h" */
#include "udma/udma_i2c.h"
#include "udma/udma_i2s.h"
#include "udma/udma_spim.h"
#include "udma/udma_uart.h"

/* Cluster. */
/* DMA. */
#include "dma/dma.h"

#endif /* HAL_INCLUDE_HAL_PMSIS_HAL_H_ */
