/***************************************************************************//**
 * @file    dev_accel.c
 * @brief   Accelerometer driver of RT-Thread RTOS for EFM32
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2011-07-13   onelife     Initial creation for using EFM32 ADC module to
 *  interface the Freescale MMA7361L
 * 2011-08-02   onelife     Add digital interface support of using EFM32 IIC
 *  module for the Freescale MMA7455L
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"

#if defined(EFM32_USING_ACCEL)
#if (EFM32_USING_ACCEL == EFM32_INTERFACE_ADC)
#include "drv_adc.h"
#elif (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
#include "drv_iic.h"
#include "hdl_interrupt.h"
#endif
#include "dev_accel.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef EFM32_ACCEL_DEBUG
#define accel_debug(format,args...)         rt_kprintf(format, ##args)
#else
#define accel_debug(format,args...)
#endif

/* Private constants ---------------------------------------------------------*/
static rt_device_t                      accel;
#if (EFM32_USING_ACCEL == EFM32_INTERFACE_ADC)
static struct efm32_adc_control_t       control = \
    {ADC_MODE_SCAN, {3, ACCEL_USING_DMA}, {}};
static struct efm32_accel_result_t      accelOffset = {0};
#elif (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
static const struct efm32_iic_control_t control = \
    {IIC_STATE_MASTER, 0x0000};
#endif
static rt_bool_t                        accelInTime = true;
static rt_uint32_t                      accelConfig = 0;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Get accelerometer output
 *
 * @details
 *
 * @note
 *
 * @param[out] data
 *  Pointer to output buffer
 *
 * @param[in] lowResolution
 *  Resolution selection
 *
 * @return
 *   Error code
 ******************************************************************************/
rt_err_t efm_accel_get_data(struct efm32_accel_result_t *data,
    rt_bool_t lowResolution)
{
    RT_ASSERT(accel != RT_NULL);

    rt_err_t ret;

    if (data == RT_NULL)
    {
        return -RT_ERROR;
    }

    ret = RT_EOK;
    do
    {
        /* --------- ADC interface --------- */
#if (EFM32_USING_ACCEL == EFM32_INTERFACE_ADC)
        struct efm32_adc_result_t result;

        result.mode = control.mode;
        result.buffer = (void *)data;
        if ((ret = accel->control(accel, RT_DEVICE_CTRL_RESUME,
            (void *)&result)) != RT_EOK)
        {
            break;
        }
        if ((ret = accel->control(accel, RT_DEVICE_CTRL_ADC_RESULT, \
            (void *)&result)) != RT_EOK)
        {
            break;
        }

        data->x += accelOffset.x - 0x800;
        data->y += accelOffset.y - 0x800;
        data->z += accelOffset.z - 0x800;
        if (lowResolution)
        {
            data->x >>= 4;
            data->y >>= 4;
            data->z >>= 4;
        }

        /* --------- IIC interface --------- */
#elif (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
        if (lowResolution || \
            ((accelConfig & ACCEL_MASK_RANGE) != MCTL_RANGE_8G))
        {
            rt_int8_t buf[3];

            buf[0] = XOUT8;
            if (accel->read(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, \
                sizeof(buf)) == 0)
            {
                ret = -RT_ERROR;
                break;
            }
            data->x = buf[0];
            data->y = buf[1];
            data->z = buf[2];
        }
        else
        {
            rt_uint8_t buf[6];
            rt_uint16_t *temp = (rt_uint16_t *)&buf;

            buf[0] = XOUTL;
            if (accel->read(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, \
                sizeof(buf)) == 0)
            {
                ret = -RT_ERROR;
                break;
            }
            data->x = (*temp & 0x200) ? ((rt_uint32_t)*temp | ~0x3FF) : \
                ((rt_uint32_t)*temp & 0x3FF);
            data->y = (*++temp & 0x200) ? ((rt_uint32_t)*temp | ~0x3FF) : \
                ((rt_uint32_t)*temp & 0x3FF);
            data->z = (*++temp & 0x200) ? ((rt_uint32_t)*temp | ~0x3FF) : \
                ((rt_uint32_t)*temp & 0x3FF);
        }
#endif
        return RT_EOK;
    } while (0);

    accel_debug("Accel err: Get data failed!\n");
    return ret;
}

/***************************************************************************//**
 * @brief
 *   Accelerometer timeout interrupt handler
 *
 * @details
 *
 * @note
 *
 * @param[in] parameter
 *  Parameter
 ******************************************************************************/
static void efm_accel_timer(void* parameter)
{
    accelInTime = false;
}

#if (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
/***************************************************************************//**
 * @brief
 *  Accelerometer level and pulse detection interrupts handler
 *
 * @details
 *
 * @note
 *
 * @param[in] device
 *  Pointer to device descriptor
 ******************************************************************************/
static void efm_accel_isr(rt_device_t device)
{
    rt_uint8_t buf[2];

    if ((accelConfig & ACCEL_MASK_MODE) != ACCEL_MODE_MEASUREMENT)
    {
        /* Read detection source */
        buf[0] = DETSRC;
        if (accel->read(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 1) != 1)
        {
            accel_debug("Accel: read error\n");
            return;
        }
        accel_debug("Accel: DETSRC %x\n", buf[0]);

        /* Reset the interrupt flags: Part 1 */
        buf[0] = INTRST;
        buf[1] = INTRST_INT_1 | INTRST_INT_2;
        accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2);

        /* Read status to waste some time */
        buf[0] = STATUS;
        if (accel->read(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 1) != 1)
        {
            accel_debug("Accel: read error\n");
            return;
        }
        accel_debug("Accel: STATUS %x\n", buf[0]);

        /* Reset the interrupt flags: Part 2 */
        buf[0] = INTRST;
        buf[1] = 0x00;
        accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2);
    }
}

/***************************************************************************//**
 * @brief
 *  Accelerometer configuration function
 *
 * @details
 *
 * @note
 *
 * @param[in] config
 *  Configuration options
 *
 * @param[in] level_threshold
 *  Level detection threshold
 *
 * @param[in] pulse_threshold
 *  Pulse detection threshold
 *
 * @param[in] pulse_duration
 *  Time window for 1st pulse
 *
 * @param[in] pulse_latency
 *  Pulse latency Time
 *
 * @param[in] pulse_duration2
 *  Time window for 2nd pulse
 *
 * @return
 *   Error code
 ******************************************************************************/
rt_err_t efm_accel_config(rt_uint32_t config,
    rt_uint8_t level_threshold,
    rt_uint8_t pulse_threshold,
    rt_uint8_t pulse_duration,
    rt_uint8_t pulse_latency,
    rt_uint8_t pulse_duration2)
{
    rt_err_t ret;
    rt_uint8_t buf[2];
    rt_uint8_t mode, mctl_reg, ctl1_reg, ctl2_reg;

    ret = RT_EOK;
    mctl_reg = 0;
    ctl1_reg = 0;
    ctl2_reg = 0;

    /* Modify MCTL */
    mode = config & ACCEL_MASK_MODE;
    switch (mode)
    {
    case ACCEL_MODE_STANDBY:
        mctl_reg |= MCTL_MODE_STANDBY;
        break;
    case ACCEL_MODE_MEASUREMENT:
        mctl_reg |= MCTL_MODE_MEASUREMENT;
        break;
    case ACCEL_MODE_LEVEL:
        mctl_reg |= MCTL_MODE_LEVEL;
        break;
    case ACCEL_MODE_PULSE:
        mctl_reg |= MCTL_MODE_PULSE;
        break;
    default:
        return -RT_ERROR;
    }

    switch (config & ACCEL_MASK_RANGE)
    {
    case ACCEL_RANGE_8G:
        mctl_reg |= MCTL_RANGE_8G;
        break;
    case ACCEL_RANGE_4G:
        mctl_reg |= MCTL_RANGE_4G;
        break;
    case ACCEL_RANGE_2G:
        mctl_reg |= MCTL_RANGE_2G;
        break;
    default:
        return -RT_ERROR;
    }

    if ((mode == ACCEL_MODE_LEVEL) || (mode == ACCEL_MODE_PULSE))
    {
        mctl_reg |= MCTL_PIN_INT1;
    }

    /* Modify CTL1 */
    if (config & ACCEL_INTPIN_INVERSE)
    {
        ctl1_reg |= CTL1_INTPIN_INVERSE;
    }

    switch (config & ACCEL_MASK_INT)
    {
    case ACCEL_INT_LEVEL_PULSE:
        ctl1_reg |= CTL1_INT_LEVEL_PULSE;
        break;
    case ACCEL_INT_PULSE_LEVEL:
        ctl1_reg |= CTL1_INT_PULSE_LEVEL;
        break;
    case ACCEL_INT_SINGLE_DOUBLE:
        ctl1_reg |= CTL1_INT_SINGLE_DOUBLE;
        break;
    default:
        break;
    }

    switch (config & ACCEL_MASK_DISABLE)
    {
    case ACCEL_DISABLE_X:
        ctl1_reg |= CTL1_X_DISABLE;
        break;
    case ACCEL_DISABLE_Y:
        ctl1_reg |= CTL1_Y_DISABLE;
        break;
    case ACCEL_DISABLE_Z:
        ctl1_reg |= CTL1_Z_DISABLE;
        break;
    default:
        break;
    }

    if (config & ACCEL_THRESHOLD_INTEGER)
    {
        ctl1_reg |= CTL1_THRESHOLD_INTEGER;
    }

    if (config & ACCEL_BANDWIDTH_125HZ)
    {
        ctl1_reg |= CTL1_BANDWIDTH_125HZ;
    }

    /* Modify CTL2 */
    if (config & ACCEL_LEVEL_AND)
    {
        ctl2_reg |= CTL2_LEVEL_AND;
    }
    if (config & ACCEL_PULSE_AND)
    {
        ctl2_reg |= CTL2_PULSE_AND;
    }
    if (config & ACCEL_DRIVE_STRONG)
    {
        ctl2_reg |= CTL2_DRIVE_STRONG;
    }

    do
    {
        /* Write registers */
        buf[0] = MCTL;
        buf[1] = mctl_reg;
        if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2) == 0)
        {
            ret = -RT_ERROR;
            break;
        }
        accel_debug("Accel: MCTL %x\n", mctl_reg);

        buf[0] = CTL1;
        buf[1] = ctl1_reg;
        if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2) == 0)
        {
            ret = -RT_ERROR;
            break;
        }
        accel_debug("Accel: CTL1 %x\n", ctl1_reg);

        buf[0] = CTL2;
        buf[1] = ctl2_reg;
        if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2) == 0)
        {
            ret = -RT_ERROR;
            break;
        }
        accel_debug("Accel: CTL2 %x\n", ctl2_reg);
        accelConfig = config;

        if (mode == ACCEL_MODE_PULSE)
        {
            buf[0] = PDTH;
            buf[1] = pulse_threshold;
            if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2) == 0)
            {
                ret = -RT_ERROR;
                break;
            }
            accel_debug("Accel: PDTH %x\n", buf[1]);

            buf[0] = PW;
            buf[1] = pulse_duration;
            if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2) == 0)
            {
                ret = -RT_ERROR;
                break;
            }
            accel_debug("Accel: PW %x\n", buf[1]);

            buf[0] = LT;
            buf[1] = pulse_latency;
            if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2) == 0)
            {
                ret = -RT_ERROR;
                break;
            }
            accel_debug("Accel: LT %x\n", buf[1]);

            buf[0] = TW;
            buf[1] = pulse_duration2;
            if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2) == 0)
            {
                ret = -RT_ERROR;
                break;
            }
            accel_debug("Accel: TW %x\n", buf[1]);
        }

        if ((mode == ACCEL_MODE_LEVEL) || (mode == ACCEL_MODE_PULSE))
        {
            efm32_irq_hook_init_t hook;

            /* Reset the interrupt flags: Part 1 */
            buf[0] = INTRST;
            buf[1] = INTRST_INT_1 | INTRST_INT_2;
            if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2) == 0)
            {
                ret = -RT_ERROR;
                break;
            }

            /* Set level detection threshold */
            buf[0] = LDTH;
            if (config & ACCEL_THRESHOLD_INTEGER)
            {
                buf[1] = level_threshold;
            }
            else
            {
                buf[1] = level_threshold & 0x7f;
            }
            if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2) == 0)
            {
                ret = -RT_ERROR;
                break;
            }
            accel_debug("Accel: LDTH %x\n", buf[1]);

            /* Config interrupt */
            hook.type       = efm32_irq_type_gpio;
            hook.unit       = ACCEL_INT1_PIN;
            hook.cbFunc     = efm_accel_isr;
            hook.userPtr    = RT_NULL;
            efm32_irq_hook_register(&hook);
            hook.unit       = ACCEL_INT2_PIN;
            efm32_irq_hook_register(&hook);
            /* Clear pending interrupt */
            BITBAND_Peripheral(&(GPIO->IFC), ACCEL_INT1_PIN, 0x1UL);
            BITBAND_Peripheral(&(GPIO->IFC), ACCEL_INT2_PIN, 0x1UL);
            /* Set raising edge interrupt and clear/enable it */
            GPIO_IntConfig(
                ACCEL_INT1_PORT,
                ACCEL_INT1_PIN,
                true,
                false,
                true);
            GPIO_IntConfig(
                ACCEL_INT2_PORT,
                ACCEL_INT2_PIN,
                true,
                false,
                true);
            if (((rt_uint8_t)ACCEL_INT1_PORT % 2) || \
                ((rt_uint8_t)ACCEL_INT2_PORT % 2))
            {
                NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
                NVIC_SetPriority(GPIO_ODD_IRQn, EFM32_IRQ_PRI_DEFAULT);
                NVIC_EnableIRQ(GPIO_ODD_IRQn);
            }
            if (!((rt_uint8_t)ACCEL_INT1_PORT % 2) || \
                !((rt_uint8_t)ACCEL_INT2_PORT % 2))
            {
                NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
                NVIC_SetPriority(GPIO_EVEN_IRQn, EFM32_IRQ_PRI_DEFAULT);
                NVIC_EnableIRQ(GPIO_EVEN_IRQn);
            }

            /* Reset the interrupt flags: Part 2 */
            buf[0] = INTRST;
            buf[1] = 0x00;
            if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, (void *)buf, 2) == 0)
            {
                ret = -RT_ERROR;
                break;
            }
        }
    } while (0);

    return ret;
}

#endif

/***************************************************************************//**
 * @brief
 *   Accelerometer auto-zero calibration function
 *
 * @details
 *
 * @note
 *
 * @param[in] mode
 *  0, simple mode (assuming the device is placed on flat surface)
 *  1, interaction method
 *
 * @param[in] period
 *  Time period to perform auto-zero calibration
 *
 * @return
 *   Error code
 ******************************************************************************/
rt_err_t efm_accel_auto_zero(rt_uint8_t mode, rt_tick_t period)
{
    RT_ASSERT(accel != RT_NULL);

    rt_timer_t calTimer;
    struct efm32_accel_result_t min = {0, 0, 0};
    struct efm32_accel_result_t max = {0, 0, 0};
    struct efm32_accel_result_t temp, sum;
    rt_int32_t simpleOffset[] = ACCEL_CAL_1G_VALUE;
    rt_uint8_t cmd[7] = {0};
    rt_uint8_t i, j;

    /* Reset offset */
#if (EFM32_USING_ACCEL == EFM32_INTERFACE_ADC)
    accelOffset.x = 0;
    accelOffset.y = 0;
    accelOffset.z = 0;

#elif (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
    cmd[0] = XOFFL;
    if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, cmd, sizeof(cmd)) == 0)
    {
        return -RT_ERROR;
    }
#endif

    if (mode == ACCEL_CAL_SIMPLE)
    {
        /* Simple mode */
        for (j = 0; j < ACCEL_CAL_ROUND; j++)
        {
            sum.x = 0x0;
            sum.y = 0x0;
            sum.z = 0x0;

            for (i = 0; i < ACCEL_CAL_SAMPLES; i++)
            {
#if (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
                /* Waiting for data ready */
                while(!GPIO_PinInGet(ACCEL_INT1_PORT, ACCEL_INT1_PIN));
#endif
                if (efm_accel_get_data(&temp, false) != RT_EOK)
                {
                    return -RT_ERROR;
                }
                sum.x += temp.x;
                sum.y += temp.y;
                sum.z += temp.z;
            }

#if (EFM32_USING_ACCEL == EFM32_INTERFACE_ADC)
            temp.x = sum.x / ACCEL_CAL_SAMPLES;
            temp.y = sum.y / ACCEL_CAL_SAMPLES;
            temp.z = sum.z / ACCEL_CAL_SAMPLES - simpleOffset[ACCEL_G_SELECT];
            if ((temp.x == 0) && (temp.y == 0) && \
                (temp.z == 0))
            {
                accel_debug("Accel: Offset %+d %+d %+d\n",
                    accelOffset.x, accelOffset.y, accelOffset.z);
                break;
            }
            accelOffset.x -= temp.x;
            accelOffset.y -= temp.y;
            accelOffset.z -= temp.z;

#elif (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
            temp.x = sum.x / (ACCEL_CAL_SAMPLES >> 1);
            temp.y = sum.y / (ACCEL_CAL_SAMPLES >> 1);
            temp.z = sum.z / (ACCEL_CAL_SAMPLES >> 1) \
                - (simpleOffset[ACCEL_G_SELECT] << 1);
            if ((temp.x == 0) && (temp.y == 0) && \
                (temp.z == 0))
            {
                break;
            }

            /* Set offset drift registers */
            max.x -= temp.x;
            max.y -= temp.y;
            max.z -= temp.z;
            *(rt_int16_t *)&cmd[1] = (rt_int16_t)max.x;
            *(rt_int16_t *)&cmd[3] = (rt_int16_t)max.y;
            *(rt_int16_t *)&cmd[5] = (rt_int16_t)max.z;
            if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, cmd, sizeof(cmd)) == 0)
            {
                return -RT_ERROR;
            }
            accel_debug("Accel: Offset %+d %+d %+d\n", *(rt_int16_t *)&cmd[1], \
                *(rt_int16_t *)&cmd[3], *(rt_int16_t *)&cmd[5]);
#endif
            rt_thread_sleep(1);
        }
    }
    else
    {
        /* Interact mode */
        if ((calTimer = rt_timer_create(
            "cal_tmr",
            efm_accel_timer,
            RT_NULL,
            period,
            RT_TIMER_FLAG_ONE_SHOT)) == RT_NULL)
        {
            accel_debug("Accel err: Create timer failed!\n");
            return -RT_ERROR;
        }

        accelInTime = true;
        rt_timer_start(calTimer);
        do
        {
            sum.x = 0x0;
            sum.y = 0x0;
            sum.z = 0x0;

            for (i = 0; i < ACCEL_CAL_SAMPLES; i++)
            {
#if (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
                /* Waiting for data ready */
                while(!GPIO_PinInGet(ACCEL_INT1_PORT, ACCEL_INT1_PIN));
#endif
                if (efm_accel_get_data(&temp, false) != RT_EOK)
                {
                    return -RT_ERROR;
                }
                sum.x += temp.x;
                sum.y += temp.y;
                sum.z += temp.z;
            }
            sum.x /= ACCEL_CAL_SAMPLES;
            sum.y /= ACCEL_CAL_SAMPLES;
            sum.z /= ACCEL_CAL_SAMPLES;
            if (sum.x < min.x)
            {
                min.x = sum.x;
            }
            if (sum.y < min.y)
            {
                min.y = sum.y;
            }
            if (sum.z < min.z)
            {
                min.z = sum.z;
            }
            if (sum.x > max.x)
            {
                max.x = sum.x;
            }
            if (sum.y > max.y)
            {
                max.y = sum.y;
            }
            if (sum.z > max.z)
            {
                max.z = sum.z;
            }
            rt_thread_sleep(1);
        } while (accelInTime);

        accel_debug("Accel: Min %+d %+d %+d, max %+d %+d %+d\n",
            min.x, min.y, min.z, max.x, max.y, max.z);

#if (EFM32_USING_ACCEL == EFM32_INTERFACE_ADC)
        accelOffset.x = -((min.x + max.x) >> 1);
        accelOffset.y = -((min.y + max.y) >> 1);
        accelOffset.z = -((min.z + max.z) >> 1);

    accel_debug("Accel: Offset %+d %+d %+d\n",
        accelOffset.x, accelOffset.y, accelOffset.z);

#elif (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
        /* Set offset drift registers */
        *(rt_int16_t *)&cmd[1] = (rt_int16_t)-(min.x + max.x);
        *(rt_int16_t *)&cmd[3] = (rt_int16_t)-(min.y + max.y);
        *(rt_int16_t *)&cmd[5] = (rt_int16_t)-(min.z + max.z);
        if (accel->write(accel, ACCEL_IIC_SLAVE_ADDRESS, cmd, sizeof(cmd)) == 0)
        {
            return -RT_ERROR;
        }

    accel_debug("Accel: Offset %+d %+d %+d\n",
        *(rt_int16_t *)&cmd[1], *(rt_int16_t *)&cmd[3], *(rt_int16_t *)&cmd[5]);
#endif

        rt_timer_delete(calTimer);
    }

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Initialize the accelerometer
 *
 * @details
 *
 * @note
 *
 * @return
 *   Error code
 ******************************************************************************/
rt_err_t efm_accel_init(void)
{
    rt_err_t ret;

    ret = RT_EOK;
    do
    {
        /* Find ADC device */
        accel = rt_device_find(ACCEL_USING_DEVICE_NAME);
        if (accel == RT_NULL)
        {
            accel_debug("Accel err: Can't find device: %s!\n", ACCEL_USING_DEVICE_NAME);
            ret = -RT_ERROR;
            break;
        }
        accel_debug("Accel: Find device %s\n", ACCEL_USING_DEVICE_NAME);

        /* --------- ADC interface --------- */
#if (EFM32_USING_ACCEL == EFM32_INTERFACE_ADC)
        ADC_InitScan_TypeDef scanInit = ADC_INITSCAN_DEFAULT;

 #if defined(EFM32_GXXX_DK)
        /* Enable accelerometer */
        DVK_enablePeripheral(DVK_ACCEL);
            /* Select g-range */
  #if (ACCEL_G_SELECT == 0)
        DVK_disablePeripheral(DVK_ACCEL_GSEL);
  #elif (ACCEL_G_SELECT == 1)
        DVK_enablePeripheral(DVK_ACCEL_GSEL);
  #else
  #error "Wrong value for ACCEL_G_SELECT"
  #endif
 #endif
        /* Init ADC for scan mode */
        scanInit.reference = adcRefVDD;
        scanInit.input = ACCEL_X_ADC_CH | ACCEL_Y_ADC_CH | ACCEL_Z_ADC_CH;

        control.scan.init = &scanInit;
        if ((ret = accel->control(accel, RT_DEVICE_CTRL_ADC_MODE, \
            (void *)&control)) != RT_EOK)
        {
            break;
        }

        /* --------- IIC interface --------- */
#elif (EFM32_USING_ACCEL == EFM32_INTERFACE_IIC)
        rt_uint8_t cmd[2];

        /* Initialize */
        if ((ret = accel->control(accel, RT_DEVICE_CTRL_IIC_SETTING, \
            (void *)&control)) != RT_EOK)
        {
            break;
        }

        if (efm_accel_config(
            ACCEL_MODE_MEASUREMENT | ACCEL_RANGE_2G,
            EFM32_NO_DATA,
            EFM32_NO_DATA,
            EFM32_NO_DATA,
            EFM32_NO_DATA,
            EFM32_NO_DATA) != RT_EOK)
        {
            break;
        }

        /* Config interrupt pin1 */
        GPIO_PinModeSet(ACCEL_INT1_PORT, ACCEL_INT1_PIN, gpioModeInput, 0);
        /* Config interrupt pin2 */
        GPIO_PinModeSet(ACCEL_INT2_PORT, ACCEL_INT2_PIN, gpioModeInput, 0);
#endif

        accel_debug("Accel: Init OK\n");
        return RT_EOK;
    } while (0);

    accel_debug("Accel err: Init failed!\n");
    return -RT_ERROR;
}

/*******************************************************************************
 *  Export to FINSH
 ******************************************************************************/
#ifdef RT_USING_FINSH
#include <finsh.h>

void accel_cal(rt_uint8_t mode, rt_uint32_t second)
{
    if (efm_accel_auto_zero(mode, RT_TICK_PER_SECOND * second) != RT_EOK)
    {
        rt_kprintf("Error occurred.");
        return;
    }

    rt_kprintf("Calibration done.\n");
}
FINSH_FUNCTION_EXPORT(accel_cal, auto-zero calibration.)

void list_accel(void)
{
    struct efm32_accel_result_t data;

    efm_accel_get_data(&data, false);
    rt_kprintf("X: %d, Y: %d, Z: %d\n", data.x, data.y, data.z);
}
FINSH_FUNCTION_EXPORT(list_accel, list accelerometer info.)

void test_accel(rt_uint8_t mode)
{
    if (mode == 0)
    {
        if (efm_accel_config(
            ACCEL_MODE_LEVEL | ACCEL_RANGE_8G | ACCEL_INT_LEVEL_PULSE | \
            ACCEL_SOURCE_LEVEL_X | ACCEL_SOURCE_LEVEL_Y,
            0x1f,
            EFM32_NO_DATA,
            EFM32_NO_DATA,
            EFM32_NO_DATA,
            EFM32_NO_DATA) != RT_EOK)
        {
            rt_kprintf("efm_accel_config(): error\n");
            return;
        }
    }
    else
    {
        if (efm_accel_config(
            ACCEL_MODE_PULSE | ACCEL_RANGE_8G | ACCEL_INT_SINGLE_DOUBLE | \
            ACCEL_SOURCE_PULSE_X | ACCEL_SOURCE_PULSE_Y,
            0x1f,
            0x1f,
            200,
            255,
            255) != RT_EOK)
        {
            rt_kprintf("efm_accel_config(): error\n");
            return;
        }
    }
}
FINSH_FUNCTION_EXPORT(test_accel, list accelerometer info.)
#endif

#endif
/***************************************************************************//**
 * @}
 ******************************************************************************/
