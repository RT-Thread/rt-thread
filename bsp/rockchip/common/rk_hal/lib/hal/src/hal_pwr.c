/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

#ifdef HAL_PWR_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup PWR
 *  @{
 */

/** @defgroup PWR_How_To_Use How To Use
 *  @{

 The PWR driver can be used as follows:

 - Invoke HAL_PWR_SetVoltage to set voltage value.
 - Invoke HAL_PWR_GetVoltage to Get voltage value.
 - Invoke HAL_PWR_SetVoltageSuspend to set voltage value for suspend mode.
 - Invoke HAL_PWR_GetVoltageSuspend to get voltage value for suspend mode.
 - Invoke HAL_PWR_GetVoltageReal to get voltage value while is in effect.
 - Invoke HAL_PWR_Enable to enable a regulator.
 - Invoke HAL_PWR_Disable to disable a regulator.
 - Invoke HAL_PWR_GetEnableState to get the enable state.
 - Invoke HAL_PWR_RoundVoltage to check the volt is valid or not.

 @} */

#ifdef HAL_PWR_INTBUS_MODULE_ENABLED

/** @defgroup PWR_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/

#define WM_SET_BITS(msk, shift, bits) ((msk <<(shift + 16)) | (bits << shift))
#define WM_SET_BIT(shift)             ((1 << (16 + shift) ) | (1 << shift))
#define WM_CLR_BIT(shift)             (1 << (16 + shift) )

/********************* Private Structure Definition **************************/
/********************* Private Variable Definition ***************************/
/********************* Private Function Definition ***************************/
static HAL_Status PWR_SetVoltage_Linear(struct PWR_INTREG_DESC *desc, uint32_t volt,
                                        ePWR_CtrlType ctrlType)
{
    uint32_t val, delta, mod;
    __IO uint32_t *preg;

    HAL_ASSERT(desc->flag & HAL_BIT(ctrlType));

    HAL_ASSERT(volt >= desc->minVolt);

    HAL_ASSERT(ctrlType <= PWR_CTRL_VOLT_SSPD);

    delta = volt - desc->minVolt;
    mod = delta % desc->volt_list.stepVolt;
    if (mod) {
        return HAL_INVAL;
    }

    val = delta / desc->volt_list.stepVolt;

    HAL_ASSERT(val < desc->voltCnt);

    preg = desc->preg[ctrlType];

    val = WM_SET_BITS(desc->voltMask, desc->shift[ctrlType], val);
    WRITE_REG(*preg, val);

    return HAL_OK;
}

static uint32_t PWR_RoundVoltage_Linear(struct PWR_INTREG_DESC *desc, uint32_t volt)
{
    uint32_t val, delta, mod;

    HAL_ASSERT(volt >= desc->minVolt);

    delta = volt - desc->minVolt;
    val = delta / desc->volt_list.stepVolt;

    mod = delta % desc->volt_list.stepVolt;

    if (mod) {
        val += 1;
    }

    return (desc->minVolt + desc->volt_list.stepVolt * val);
}

static uint32_t PWR_GetVoltageLinear(struct PWR_INTREG_DESC *desc,
                                     ePWR_CtrlType ctrlType)
{
    uint32_t val;
    __IO uint32_t *preg;

    HAL_ASSERT(desc->flag & HAL_BIT(ctrlType));
    HAL_ASSERT(ctrlType <= PWR_CTRL_VOLT_ST);

    preg = desc->preg[ctrlType];

    val = (READ_REG(*preg) >> desc->shift[ctrlType]) & desc->voltMask;

    HAL_ASSERT(val < desc->voltCnt);

    return (desc->minVolt + desc->volt_list.stepVolt * val);
}

static HAL_Status PWR_EnableDisable(struct PWR_INTREG_DESC *desc, uint32_t enable)
{
    uint32_t val;
    __IO uint32_t *preg;

    HAL_ASSERT(desc->flag & HAL_BIT(PWR_CTRL_PWR_EN));

    preg = desc->preg[PWR_CTRL_PWR_EN];

    if (enable) {
        val = WM_SET_BIT(desc->shift[PWR_CTRL_PWR_EN]);
    } else {
        val = WM_CLR_BIT(desc->shift[PWR_CTRL_PWR_EN]);
    }

    WRITE_REG(*preg, val);

    return HAL_OK;
}

/** @} */
/********************* Public Function Definition ****************************/
/** @defgroup PWR_Exported_Functions_Group2 State and Errors Functions

 This section provides functions allowing to get the status of the module:

 *  @{
 */

/**
 * @brief  get enable state for the power regulator.
 * @param  desc: the power regulator description pointer.
 * @return 1 is enable, 0 is disable.
 */
int HAL_PWR_GetEnableState(struct PWR_INTREG_DESC *desc)
{
    __IO uint32_t *preg;

    HAL_ASSERT(desc->flag & HAL_BIT(PWR_CTRL_PWR_EN));

    preg = desc->preg[PWR_CTRL_PWR_EN];

    return (READ_REG(*preg) >> desc->shift[PWR_CTRL_PWR_EN]) & 0x1;
}

/**
 * @brief  get voltage value.
 * @param  desc: the power regulator description pointer.
 * @return the voltage value if support, otherwise return 0.
 */
uint32_t HAL_PWR_GetVoltage(struct PWR_INTREG_DESC *desc)
{
    HAL_ASSERT(desc);
    if (desc->flag & PWR_FLG_LINEAR) {
        return PWR_GetVoltageLinear(desc, PWR_CTRL_VOLT_RUN);
    } else {
        return 0;
    }
}

/**
 * @brief  round voltage value.
 * @param  desc: the power regulator description pointer.
 * @param  volt: the volt value to be check
 * @return the voltage value if support, otherwise return 0.
 */
uint32_t HAL_PWR_RoundVoltage(struct PWR_INTREG_DESC *desc, uint32_t volt)
{
    HAL_ASSERT(desc);
    if (desc->flag & PWR_FLG_LINEAR) {
        return PWR_RoundVoltage_Linear(desc, volt);
    } else {
        return 0;
    }
}

/**
 * @brief  get voltage value for suspend mode.
 * @param  desc: the power regulator description pointer.
 * @return the voltage value if support, otherwise return 0.
 */
uint32_t HAL_PWR_GetVoltageSuspend(struct PWR_INTREG_DESC *desc)
{
    HAL_ASSERT(desc);
    if (desc->flag & PWR_FLG_LINEAR) {
        return PWR_GetVoltageLinear(desc, PWR_CTRL_VOLT_SSPD);
    } else {
        return 0;
    }
}

/**
 * @brief  get real voltage value.
 * @param  desc: the power regulator description pointer.
 * @return the voltage value if support, otherwise return 0.
 */
uint32_t HAL_PWR_GetVoltageReal(struct PWR_INTREG_DESC *desc)
{
    HAL_ASSERT(desc);
    if ((desc->flag & (PWR_FLG_LINEAR | PWR_FLG_VOLT_ST)) ==
        (PWR_FLG_LINEAR | PWR_FLG_VOLT_ST)) {
        return PWR_GetVoltageLinear(desc, PWR_CTRL_VOLT_ST);
    } else {
        return 0;
    }
}

/** @} */

/** @defgroup PWR_Exported_Functions_Group5 Other Functions
 *  @{
 */

/**
 * @brief  set voltage value.
 * @param  desc: the power regulator description pointer.
 * @param  volt: the volt value to be config
 * @return HAL_Status.
 */
HAL_Status HAL_PWR_SetVoltage(struct PWR_INTREG_DESC *desc, uint32_t volt)
{
    HAL_ASSERT(desc);

    if (desc->flag & PWR_FLG_LINEAR) {
        return PWR_SetVoltage_Linear(desc, volt, PWR_CTRL_VOLT_RUN);
    } else {
        return HAL_NODEV;
    }
}

/**
 * @brief  set voltage value for suspend mode.
 * @param  desc: the power regulator description pointer.
 * @param  volt: the volt value to be config
 * @return HAL_Status.
 */
HAL_Status HAL_PWR_SetVoltageSuspend(struct PWR_INTREG_DESC *desc,
                                     uint32_t volt)
{
    HAL_ASSERT(desc);
    if (desc->flag & PWR_FLG_LINEAR) {
        return PWR_SetVoltage_Linear(desc, volt, PWR_CTRL_VOLT_SSPD);
    } else {
        return HAL_NODEV;
    }
}

/**
 * @brief  enable a power regulator.
 * @param  desc: the power regulator description pointer.
 * @return HAL_Status.
 */
HAL_Status HAL_PWR_Enable(struct PWR_INTREG_DESC *desc)
{
    HAL_ASSERT(desc);

    return PWR_EnableDisable(desc, 1);
}

/**
 * @brief  disable a power regulator.
 * @param  desc: the power regulator description pointer.
 * @return HAL_Status.
 */
HAL_Status HAL_PWR_Disable(struct PWR_INTREG_DESC *desc)
{
    HAL_ASSERT(desc);

    return PWR_EnableDisable(desc, 0);
}

/**
 * @brief  match a power regulator description by pwr id.
 * @param  desc: a power regulator description.
 * @param  pwrId: a regulator channel id.
 * @return if match return HAL_TRUE.
 */
HAL_Check HAL_PWR_CheckDescByPwrId(struct PWR_INTREG_DESC *desc,
                                   ePWR_ID pwrId)
{
    if (desc->info.pwrId == pwrId) {
        return HAL_TRUE;
    } else {
        return HAL_FALSE;
    }
}

/** @} */

#endif

/** @defgroup PWR_Exported_Functions_Group5 Other Functions
 *  @{
 */

/**
 * @brief  use linear ranges to convert seletor to voltage.
 * @param  linearTables: the power linear range table pointer.
 * @param  sel: the selector value to be converted
 * @return seletor value.
 */
int HAL_PWR_LinearRangeSelToVolt(const struct PWR_LINEAR_RANGE_TABLE *linearTables, uint32_t sel)
{
    const struct PWR_LINEAR_RANGE *range;
    int i;

    HAL_ASSERT(linearTables);
    HAL_ASSERT(linearTables->entry);

    for (i = 0; i < linearTables->nEntry; i++) {
        range = &linearTables->entry[i];
        if (sel < range->minSel || sel > range->maxSel) {
            continue;
        }

        sel -= range->minSel;

        return range->minUV + (range->uVStep * sel);
    }

    return HAL_INVAL;
}
/**
 * @brief  use linear ranges to convert voltage to seletor.
 * @param  linearTables: the power linear range table pointer.
 * @param  volt: the volt value to be converted
 * @return voltage value.
 */
int HAL_PWR_LinearRangeVoltToSel(const struct PWR_LINEAR_RANGE_TABLE *linearTables, uint32_t volt)
{
    const struct PWR_LINEAR_RANGE *range;
    int ret = HAL_INVAL;
    int i;

    HAL_ASSERT(linearTables);
    HAL_ASSERT(linearTables->entry);

    for (i = 0; i < linearTables->nEntry; i++) {
        unsigned int linear_max_uV;

        range = &linearTables->entry[i];
        HAL_ASSERT(range->maxSel >= range->minSel);
        linear_max_uV = range->minUV +
                        (range->maxSel - range->minSel) * range->uVStep;

        if (volt > linear_max_uV || volt < range->minUV) {
            continue;
        }

        /* range->uV_step == 0 means fixed voltage range */
        if (range->uVStep == 0) {
            ret = 0;
        } else {
            ret = HAL_DIV_ROUND_UP(volt - range->minUV,
                                   range->uVStep);
            if (ret < 0) {
                return ret;
            }
        }

        ret += range->minSel;

        break;
    }

    return ret;
}

/** @} */

/** @} */

/** @} */

#endif /* HAL_PWR_MODULE_ENABLED */
