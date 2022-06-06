/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PWR
 *  @{
 */

#ifndef _HAL_PWR_H_
#define _HAL_PWR_H_

#include "hal_def.h"

/** @defgroup PWR_Exported_Definition_Group1 Basic Definition
 *  @{
 */

/***************************** MACRO Definition ******************************/

typedef enum {
    PWR_ID_NULL = 0,
    PWR_ID_CORE,
    PWR_ID_LOG,
    PWR_ID_DSP_CORE,
    PWR_ID_VCC_MIPI,
    PWR_ID_VCC_AUDIO,
    PWR_ID_DSP_VCC_MIPI,
    PWR_ID_MEMORY, /**< for share memory and sram */
    PWR_ID_TOP,
    PWR_ID_BUCK_1V8, /**< Usually as a transition between high and low voltage */
    PWR_ID_VCCIO_3V3,
    PWR_ID_VDD_1V1,
    PWR_ID_VCCIO_1V8,
    PWR_ID_VCCIO_1V8_PMU,
    PWR_ID_VCC_3V0_BL,
    PWR_ID_VCC_1V8_BUCK,
    PWR_ID_VCC_1V8_LDO,
    PWR_ID_VCC33_CODEC,
    PWR_ID_VCC33_AUDIO,
    PWR_ID_VCC1,
    PWR_ID_VLDO3,
    PWR_ID_VLDO6,
    PWR_ID_MAX,
} ePWR_ID;

typedef enum {
    PWR_CTRL_VOLT_RUN = 0, /**< run mode voltage */
    PWR_CTRL_VOLT_SSPD, /**< suspend mode voltage */
    PWR_CTRL_PWR_EN, /**< enable a regulator */
    PWR_CTRL_PWR_SSPD, /**< suspend mode enable a regulator */
    PWR_CTRL_VOLT_ST, /**< get a regulator state */
    PWR_CTRL_MAX
} ePWR_CtrlType;

#define PWR_FLG_VOLT_RUN  HAL_BIT(PWR_CTRL_VOLT_RUN)
#define PWR_FLG_VOLT_SSPD HAL_BIT(PWR_CTRL_VOLT_SSPD)
#define PWR_FLG_PWR_EN    HAL_BIT(PWR_CTRL_PWR_EN)
#define PWR_FLG_PWR_SSPD  HAL_BIT(PWR_CTRL_PWR_SSPD)
#define PWR_FLG_VOLT_ST   HAL_BIT(PWR_CTRL_VOLT_ST)
#define PWR_FLG_LINEAR    HAL_BIT(PWR_CTRL_MAX)
#define PWR_FLG_FIXED     (PWR_FLG_LINEAR << 1)
#define PWR_FLG_ALWAYSON  (PWR_FLG_FIXED << 1)
#define PWR_FLG_ENMASK    (PWR_FLG_ALWAYSON << 1)

#define DESC_FLAG_LINEAR(flag)   (PWR_FLG_LINEAR | PWR_FLG_VOLT_RUN | (flag))
#define DESC_FLAG_N_LINEAR(flag) (PWR_FLG_VOLT_RUN | (flag))

#define PWR_INTREG_SHIFT_RUN(reg, sft)            \
    .preg[PWR_CTRL_VOLT_RUN] = (uint32_t *)(reg), \
    .shift[PWR_CTRL_VOLT_RUN] = (sft)

#define PWR_INTREG_SHIFT_SSPD(reg, sft)            \
    .preg[PWR_CTRL_VOLT_SSPD] = (uint32_t *)(reg), \
    .shift[PWR_CTRL_VOLT_SSPD] = (sft)

#define PWR_INTREG_SHIFT_EN(reg, sft)           \
    .preg[PWR_CTRL_PWR_EN] = (uint32_t *)(reg), \
    .shift[PWR_CTRL_PWR_EN] = (sft)

#define PWR_INTREG_SHIFT_ST(reg, sft)            \
    .preg[PWR_CTRL_VOLT_ST] = (uint32_t *)(reg), \
    .shift[PWR_CTRL_VOLT_ST] = (sft)

#define PWR_DESC_LINEAR_VOLT(min, max, step) \
    .voltCnt = (((max)-(min))/(step)) + 1,   \
    .minVolt = (min),                        \
    .volt_list = {                           \
        .stepVolt = (step)                   \
    }

#define POWER_LINEAR_RANGE(_minUV, _minSel, _maxSel, _stepUV) \
{                                                             \
    .minUV = _minUV,                                          \
    .minSel = _minSel,                                        \
    .maxSel = _maxSel,                                        \
    .uVStep = _stepUV,                                        \
}

/***************************** Structure Definition **************************/
struct PWR_LINEAR_RANGE {
    unsigned int minUV;
    unsigned int minSel;
    unsigned int maxSel;
    unsigned int uVStep;
};

struct PWR_LINEAR_RANGE_TABLE {
    int nEntry;
    struct PWR_LINEAR_RANGE *entry;
};

union U_PWR_VOLT_LIST {
    int stepVolt;
    const uint32_t *voltTable;
    struct PWR_LINEAR_RANGE_TABLE linearTables;
};

struct PWR_CTRL_INFO {
    uint16_t pwrId : 8;
    uint16_t enCnt : 4;
};

struct PWR_INTREG_DESC {
    struct PWR_CTRL_INFO info;
    uint16_t flag;
    uint8_t voltMask;
    uint8_t voltCnt;
    __IO uint32_t *preg[PWR_CTRL_MAX];
    uint8_t shift[PWR_CTRL_MAX];
    uint32_t minVolt;
    union  U_PWR_VOLT_LIST volt_list;
};

/** @} */

/***************************** Function Declare ******************************/
/** @defgroup PWR_Public_Function_Declare Public Function Declare
 *  @{
 */
#ifdef HAL_PWR_INTBUS_MODULE_ENABLED
int HAL_PWR_GetEnableState(struct PWR_INTREG_DESC *desc);
uint32_t HAL_PWR_GetVoltage(struct PWR_INTREG_DESC *desc);
uint32_t HAL_PWR_GetVoltageSuspend(struct PWR_INTREG_DESC *desc);
uint32_t HAL_PWR_GetVoltageReal(struct PWR_INTREG_DESC *desc);
HAL_Status HAL_PWR_SetVoltage(struct PWR_INTREG_DESC *desc, uint32_t volt);
HAL_Status HAL_PWR_SetVoltageSuspend(struct PWR_INTREG_DESC *desc, uint32_t volt);
HAL_Status HAL_PWR_Enable(struct PWR_INTREG_DESC *desc);
HAL_Status HAL_PWR_Disable(struct PWR_INTREG_DESC *desc);
HAL_Check HAL_PWR_CheckDescByPwrId(struct PWR_INTREG_DESC *pdesc,
                                   ePWR_ID pwrId);
uint32_t HAL_PWR_RoundVoltage(struct PWR_INTREG_DESC *desc, uint32_t volt);
#endif

int HAL_PWR_LinearRangeSelToVolt(const struct PWR_LINEAR_RANGE_TABLE *linearTables, uint32_t sel);
int HAL_PWR_LinearRangeVoltToSel(const struct PWR_LINEAR_RANGE_TABLE *linearTables, uint32_t volt);

/** @} */

#endif

/** @} */

/** @} */
