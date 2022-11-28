/*
 * Copyright 2019 AllWinnertech  Co., Ltd
 * frank@allwinnertech.com
 */
#include <sunxi_hal_regulator.h>
#include <sunxi_hal_regulator_private.h>
int hal_regulator_get(unsigned int request_flag, struct regulator_dev *rdev)
{
    return 0;
}

#if 0
static int hal_regulator_enable(struct regulator_dev *rdev)
{
    struct pwm_regulator_info *info = rdev->pwm;
    int rc;

    rc = hal_pwm_init();
    rc |= hal_pwm_config(info->chanel, info->period_ns, info->period_ns);
    rc |= hal_pwm_set_polarity(info->chanel, info->polarity);
    if (rc)
        goto out;

    rc = hal_pwm_enable(info->chanel);
    if (!rc)
        return HAL_REGULATOR_STATUS_OK;

out:
    return HAL_REGULATOR_STATUS_ERROR;
}

static hal_regulator_set_voltage(struct regulator_dev *rdev, int *target_uV)
{
    struct pwm_regulator_info *pwm_info = rdev->pwm;
    unsigned int duty_ns = 0;
    int rc;

    if (*target_uV <= pwm_info->vol_base)
        duty_ns = 0;
    else if (*target_uV >= pwm_info->vol_max)
        duty_ns = pwm_info->period_ns;
    else if (pwm_info->vol_base < *target_uV &&
            *target_uV < pwm_info->vol_max) {
    /* Div 1000 for convert to mV */
        duty_ns = ((*target_uV - pwm_info->vol_base) / 1000)
            * pwm_info->period_ns
            / ((pwm_info->vol_max - pwm_info->vol_base) / 1000);
    }

    printf("duty_ns:%d\tperiod_ns:%d\n", duty_ns, pwm_info->period_ns);
    rc = hal_pwm_config(pwm_info->chanel, duty_ns, pwm_info->period_ns);
    if (rc)
        return HAL_REGULATOR_STATUS_ERROR;

    return HAL_REGULATOR_STATUS_OK;
}

static struct regulator_ops pwm_regulator_voltage_continuous_ops = {
    .set_voltage    = pwm_regulator_set_voltage,
    .enable     = pwm_regulator_enable,
};

hal_regulator_status_t hal_regulator_init(void *data, unsigned int request_flag,
                      struct regulator_dev *rdev)
{
    int rc;

    rdev->flag = request_flag;

    switch (REGULATOR_TYPE(rdev->flag)) {
    case PWM_REGULATOR:
        rdev->pwm = (struct pwm_regulator_info *)data;
        rdev->ops = &pwm_regulator_voltage_continuous_ops;
        break;
    default:
        goto out;
    }

    rc = rdev->ops->enable(rdev);
    if (!rc)
        return HAL_REGULATOR_STATUS_OK;

out:
    return HAL_REGULATOR_STATUS_ERROR;
}

hal_regulator_status_t hal_regulator_set_voltage(struct regulator_dev *rdev,
                           int *target_uV)
{
    int rc;

    rc = rdev->ops->set_voltage(rdev, *target_uV);
    if (!rc)
        return HAL_REGULATOR_STATUS_OK;

    return HAL_REGULATOR_STATUS_ERROR;
}
#endif
