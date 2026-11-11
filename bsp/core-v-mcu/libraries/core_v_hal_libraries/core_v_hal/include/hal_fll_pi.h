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

#ifndef HAL_INCLUDE_HAL_FLL_PI_H_
#define HAL_INCLUDE_HAL_FLL_PI_H_

//#include "pmsis/targets/target.h"
#include "core-v-mcu-target.h"

/*!
 * @addtogroup fll
 * @{
 */

#define DCDC_OPER_POINTS    (4)

#define DCDC_DEFAULT_NV     (1200)
#define DCDC_DEFAULT_MV     (1200)
#define DCDC_DEFAULT_LV     (1000)
#define DCDC_DEFAULT_RET    (800)
#define DCDC_RANGE          (5)
#define DCDC_RANGE_MASK     (0x1F)
#define DCDC_BASE_VALUE     (550)
#define DCDC_STEP           (50)

#define MAX_DCDC_VARIATION  ((int32_t) (0.1*32767))

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define    FLL_LV_MAX_FREQUENCY       150000000
#define    FLL_NV_MAX_FREQUENCY       250000000
#define    FLL_SOC_MIN_FREQUENCY      150000000
#define    FLL_SOC_MAX_FREQUENCY      250000000
#define    FLL_CLUSTER_MIN_FREQUENCY   87000000
#define    FLL_CLUSTER_MAX_FREQUENCY  175000000

#define    FLL_SOC_FV_SLOPE       ((FLL_SOC_MAX_FREQUENCY - FLL_SOC_MIN_FREQUENCY) / (DCDC_DEFAULT_NV - DCDC_DEFAULT_LV))
#define    FLL_CLUSTER_FV_SLOPE   ((FLL_CLUSTER_MAX_FREQUENCY - FLL_CLUSTER_MIN_FREQUENCY) / (DCDC_DEFAULT_NV - DCDC_DEFAULT_LV))

typedef enum _fll_type
{
    FLL_SOC     = 0,
    FLL_PERI    = 1,
    FLL_CLUSTER = 2
} fll_type_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief Initialize one FLL.
 *
 * @param which_fll       SoC's or Cluster's fll.
 * @param ret_state       Retention state.
 *
 * @note .
 */
void pi_fll_init(fll_type_t which_fll, uint32_t ret_state);

/*!
 * @brief Deinitalize one FLL.
 *
 * @param which_fll       SoC's or Cluster's fll.
 *
 * @note .
 */
void pi_fll_deinit(fll_type_t which_fll);

/*!
 * @brief Clean all FLL configuration.
 *
 * @note .
 */
void pi_fll_clear();


/*!
 * @brief Set specific FLL to wanted frequency.
 *
 * @param which_fll       SoC's or Cluster's fll.
 * @param frequency       The frequency value to set.
 * @param check           Check frequency.
 *
 * @note .
 * @return check result of frequency.
 */
int pi_fll_set_frequency(fll_type_t which_fll, uint32_t frequency, int check);

/*!
 * @brief Get specific FLL's frequency.
 *
 * @param which_fll       SoC's or Cluster's fll.
 *
 * @note .
 * @return frequency value.
 */
int pi_fll_get_frequency(fll_type_t which_fll, uint8_t real);

/*!
 * @brief Calculate FC SOC domain's max frequency with certain voltage
 *
 * @param  voltage  Given voltage
 *
 * @return max frquency.
 */
static inline int pi_fll_soc_max_freq_at_V(int voltage)
{
    return (FLL_SOC_MIN_FREQUENCY + (voltage - DCDC_DEFAULT_LV) * FLL_SOC_FV_SLOPE);
}

/*!
 * @brief Calculate cluster domain's max frequency with certain voltage
 *
 * @param  voltage  Given voltage
 *
 * @return max frquency.
 */
static inline int pi_fll_cluster_max_freq_at_V(int voltage)
{
    return (FLL_CLUSTER_MIN_FREQUENCY + (voltage - DCDC_DEFAULT_LV) * FLL_CLUSTER_FV_SLOPE);
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* @} */



#endif /* HAL_INCLUDE_HAL_FLL_PI_H_ */
