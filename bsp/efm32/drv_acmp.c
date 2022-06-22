/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-02-21   onelife     Initial creation for EFM32
 * 2011-06-17   onelife     Modify init and control function for efm32lib v2 upgrading
 */

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_acmp.h"

#if (defined(RT_USING_ACMP0) || defined(RT_USING_ACMP1))
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef RT_ACMP_DEBUG
#define acmp_debug(format,args...)          rt_kprintf(format, ##args)
#else
#define acmp_debug(format,args...)
#endif

/* Private variables ---------------------------------------------------------*/
#ifdef RT_USING_ACMP0
    static struct rt_device acmp0_device;
#endif

#ifdef RT_USING_ACMP1
    static struct rt_device acmp1_device;
#endif

/* Private function prototypes -----------------------------------------------*/
ACMP_WarmTime_TypeDef efm32_acmp_WarmTimeCalc(rt_uint32_t hfperFreq);

/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Initialize ACMP device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 ******************************************************************************/
 static rt_err_t rt_acmp_init(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_acmp_device_t *acmp;

    acmp = (struct efm32_acmp_device_t *)(dev->user_data);

    acmp->hook.cbFunc   = RT_NULL;
    acmp->hook.userPtr  = RT_NULL;

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *  Configure ACMP device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *  Pointer to device descriptor
 *
 * @param[in] cmd
 *  ACMP control command
 *
 * @param[in] args
 *  Arguments
 *
 * @return
 *  Error code
 ******************************************************************************/
static rt_err_t rt_acmp_control(
    rt_device_t     dev,
    rt_uint8_t      cmd,
    void            *args)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_acmp_device_t *acmp;

    acmp = (struct efm32_acmp_device_t *)(dev->user_data);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_SUSPEND:
        /* Suspend device */
        dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
        ACMP_Disable(acmp->acmp_device);
        break;

    case RT_DEVICE_CTRL_RESUME:
        /* Resume device */
        dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
        ACMP_Enable(acmp->acmp_device);
        break;

    case RT_DEVICE_CTRL_ACMP_INIT:
        {
            rt_bool_t int_en = false;
            struct efm32_acmp_control_t *control;

            control = (struct efm32_acmp_control_t *)args;
            acmp_debug("ACMP: control -> init start\n");

            /* Configure ACMPn */
            if (control->init == RT_NULL)
            {
                return -RT_ERROR;
            }
            ACMP_Init(acmp->acmp_device, control->init);
            ACMP_ChannelSet(acmp->acmp_device, control->negInput, control->posInput);
            if (control->output != RT_NULL)
            {
                ACMP_GPIOSetup(
                    acmp->acmp_device,
                    control->output->location,
                    control->output->enable,
                    control->output->invert);
                int_en = true;
            }
            if (control->hook.cbFunc != RT_NULL)
            {
                acmp->hook.cbFunc = control->hook.cbFunc;
                acmp->hook.userPtr = control->hook.userPtr;
                int_en = true;
            }

            if (int_en)
            {
                /* Enable edge interrupt */
                ACMP_IntEnable(acmp->acmp_device, ACMP_IEN_EDGE);
                ACMP_IntClear(acmp->acmp_device, ACMP_IFC_EDGE);

                /* Enable ACMP0/1 interrupt vector in NVIC */
                NVIC_ClearPendingIRQ(ACMP0_IRQn);
                NVIC_SetPriority(ACMP0_IRQn, EFM32_IRQ_PRI_DEFAULT);
                NVIC_EnableIRQ(ACMP0_IRQn);
            }
        }
        break;

    case RT_DEVICE_CTRL_ACMP_OUTPUT:
        *((rt_bool_t *)args) = \
            (acmp->acmp_device->STATUS & ACMP_STATUS_ACMPOUT) ? true : false;
        break;

        default:
            return -RT_ERROR;
    }

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *  Register ACMP device
 *
 * @details
 *
 * @note
 *
 * @param[in] device
 *  Pointer to device descriptor
 *
 * @param[in] name
 *  Device name
 *
 * @param[in] flag
 *  Configuration flags
 *
 * @param[in] acmp
 *  Pointer to ACMP device descriptor
 *
 * @return
 *  Error code
 ******************************************************************************/
rt_err_t rt_hw_acmp_register(
    rt_device_t     device,
    const char      *name,
    rt_uint32_t     flag,
    struct efm32_acmp_device_t *acmp)
{
    RT_ASSERT(device != RT_NULL);

    device->type        = RT_Device_Class_Char; /* fixme: should be acmp type */
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->init        = rt_acmp_init;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = rt_acmp_control;
    device->user_data   = acmp;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

/***************************************************************************//**
 * @brief
 *  ACMP edge trigger interrupt handler
 *
 * @details
 *
 * @note
 ******************************************************************************/
void rt_hw_acmp_isr(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);

    struct efm32_acmp_device_t *acmp;

    acmp = (struct efm32_acmp_device_t *)(dev->user_data);

    if (acmp->hook.cbFunc != RT_NULL)
    {
        (acmp->hook.cbFunc)(acmp->hook.userPtr);
    }
}

/***************************************************************************//**
 * @brief
 *  Initialize the specified ACMP unit
 *
 * @details
 *
 * @note
 *
 * @param[in] device
 *  Pointer to device descriptor
 *
 * @param[in] unitNumber
 *  Unit number
 *
 * @return
 *  Pointer to ACMP device
 ******************************************************************************/
static struct efm32_acmp_device_t *rt_hw_acmp_unit_init(
    rt_device_t device,
    rt_uint8_t  unitNumber)
{
    struct efm32_acmp_device_t      *acmp;
    efm32_irq_hook_init_t           hook;
    CMU_Clock_TypeDef               acmpClock;

    do
    {
        /* Allocate device */
        acmp = rt_malloc(sizeof(struct efm32_acmp_device_t));
        if (acmp == RT_NULL)
        {
            acmp_debug("ACMP err: no mem for ACMP%d\n", unitNumber);
            break;
        }

        /* Initialization */
        if (unitNumber >= ACMP_COUNT)
        {
            break;
        }
        switch (unitNumber)
        {
        case 0:
            acmp->acmp_device   = ACMP0;
            acmpClock           = (CMU_Clock_TypeDef)cmuClock_ACMP0;
            break;

        case 1:
            acmp->acmp_device   = ACMP1;
            acmpClock           = (CMU_Clock_TypeDef)cmuClock_ACMP1;
            break;

        default:
            break;
        }

        /* Enable ACMP clock */
        CMU_ClockEnable(acmpClock, true);

        /* Reset */
        ACMP_Reset(acmp->acmp_device);

        /* Config interrupt and NVIC */
        hook.type           = efm32_irq_type_acmp;
        hook.unit           = unitNumber;
        hook.cbFunc         = rt_hw_acmp_isr;
        hook.userPtr        = device;
        efm32_irq_hook_register(&hook);

        return acmp;
    } while(0);

    if (acmp)
    {
        rt_free(acmp);
    }
    rt_kprintf("ACMP: Init failed!\n");
    return RT_NULL;
}

/***************************************************************************//**
 * @brief
 *  Initialize all ACMP module related hardware and register ACMP device to
 *  kernel
 *
 * @details
 *
 * @note
 *
 ******************************************************************************/
void rt_hw_acmp_init(void)
{
    struct efm32_acmp_device_t  *acmp;

#ifdef RT_USING_ACMP0
    if ((acmp = rt_hw_acmp_unit_init(&acmp0_device, 0)) != RT_NULL)
    {
        rt_hw_acmp_register(&acmp0_device, RT_ACMP0_NAME, EFM32_NO_DATA, acmp);
    }
#endif

#ifdef RT_USING_ACMP1
    if ((acmp = rt_hw_acmp_unit_init(&acmp1_device, 1)) != RT_NULL)
    {
        rt_hw_acmp_register(&acmp1_device, RT_ACMP1_NAME, EFM32_NO_DATA, acmp);
    }
#endif

}

/***************************************************************************//**
 * @brief
 *    Calculate the warm-up time value providing at least 10us
 *
 * @param[in] hfperFreq
 *  Frequency in Hz of reference HFPER clock. Set to 0 to use currently defined
 *  HFPER clock setting
 *
 * @return
 *  Warm-up time value to use for ACMP in order to achieve at least 10us
 ******************************************************************************/
ACMP_WarmTime_TypeDef efm32_acmp_WarmTimeCalc(rt_uint32_t hfperFreq)
{
    if (!hfperFreq)
    {
        hfperFreq = CMU_ClockFreqGet(cmuClock_HFPER);

        /* Just in case, make sure we get non-zero freq for below calculation */
        if (!hfperFreq)
        {
          hfperFreq = 1;
        }
    }

    /* Determine number of HFPERCLK cycle >= 10us */
    if (4 * 1000000 / hfperFreq > 10)
    {
        return acmpWarmTime4;
    }
    else if (8 * 1000000 / hfperFreq > 10)
    {
        return acmpWarmTime8;
    }
    else if (16 * 1000000 / hfperFreq > 10)
    {
        return acmpWarmTime16;
    }
    else if (32 * 1000000 / hfperFreq > 10)
    {
        return acmpWarmTime32;
    }
    else if (64 * 1000000 / hfperFreq > 10)
    {
        return acmpWarmTime64;
    }
    else if (128 * 1000000 / hfperFreq > 10)
    {
        return acmpWarmTime128;
    }
    else if (256 * 1000000 / hfperFreq > 10)
    {
        return acmpWarmTime256;
    }
    else if (512 * 1000000 / hfperFreq > 10)
    {
        return acmpWarmTime512;
    }
}

#endif
/***************************************************************************//**
 * @}
 ******************************************************************************/
