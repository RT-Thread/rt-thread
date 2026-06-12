/* Includes ------------------------------------------------------------------*/
#include "rtthread.h"
#include "rtdevice.h"
#include "NuMicro.h"
#include "drv_gpio.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.usb.sw.otg"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

/* Functions Implementation --------------------------------------------------*/
/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(BOARD_USING_USB_SWOTG) && defined(RT_USING_ADC) && defined(RT_USING_PIN)

#define DEF_ADC_DEV_NAME            ("eadc0")   // EADC device name
#define DEF_ADC_CC1_CHANNEL         (6)         // CC1
#define DEF_ADC_CC2_CHANNEL         (7)         // CC2
#define DEF_ADC_SAMPLING_DURATION   (1000)      // in ticks

/* defined the PA7 PIN */
#define DEF_MOS_G_S_PIN             NU_GET_PININDEX(NU_PA, 7)

#define THREAD_PRIORITY   5
#define THREAD_STACK_SIZE 2048
#define THREAD_TIMESLICE  5

typedef enum
{
    evUSB_ROLE_DEVICE = 0,
    evUSB_ROLE_HOST,
    evUSB_ROLE_NONE
} E_USB_ROLE;

static const uint16_t s_swotg_ccx_threshold[evUSB_ROLE_NONE][2] =
{
    /* Min / Max CC1+CC2  */
    {3200,   3800},  /* evUSB_ROLE_DEVICE */
    {400,    600},   /* evUSB_ROLE_HOST */
};

static int isConnectedUSBRole(const rt_int16_t *cc_sum)
{
    /* Determine the USB role based on CC1+CC2 voltage. */
    for (E_USB_ROLE role = evUSB_ROLE_DEVICE; role < evUSB_ROLE_NONE; role++)
    {
        /* Check if CC1+CC2 voltage is within the threshold range. */
        if ((cc_sum[role] >= s_swotg_ccx_threshold[role][0]) &&
                (cc_sum[role] <= s_swotg_ccx_threshold[role][1]))
        {
            /* Found the connected USB role */
            return role;
        }
    }
    return evUSB_ROLE_NONE;
}

static void swotg_worker(void *parameter)
{
    static E_USB_ROLE last_role = evUSB_ROLE_NONE;
    static rt_adc_device_t s_swotg_adc_dev = RT_NULL;

    rt_err_t err = 0;

    /* Find EADC device */
    s_swotg_adc_dev = (rt_adc_device_t)rt_device_find(DEF_ADC_DEV_NAME);
    if (s_swotg_adc_dev == RT_NULL)
    {
        rt_kprintf("Failed to find EADC device for USB OTG Type-C detection!\n");
        return;
    }
    err = rt_adc_enable(s_swotg_adc_dev, DEF_ADC_CC1_CHANNEL);
    err |= rt_adc_enable(s_swotg_adc_dev, DEF_ADC_CC2_CHANNEL);
    if (err != RT_EOK)
    {
        rt_kprintf("Failed to enable EADC channel for USB OTG Type-C detection!\n");
        goto fail_init;
    }

#if defined(RT_USING_PIN)
    /* set LEDR pin mode to output. */
    rt_pin_mode(DEF_MOS_G_S_PIN, PIN_MODE_OUTPUT);
#endif

    /* Sample CC1 and CC2 voltages periodically. */
    while (1)
    {
        rt_int16_t cc_sum[2] = {0};

        /* Sample CC1 and CC2 voltages under both USB roles. */
        for (E_USB_ROLE role = evUSB_ROLE_DEVICE; role < evUSB_ROLE_NONE; role++)
        {
            rt_int16_t cc1_mv, cc2_mv;

            /* Set MOS_G_S pin to select USB role */
            rt_pin_write(DEF_MOS_G_S_PIN, role);
            rt_thread_mdelay(100);

            /* Read CC1 and CC2 voltages */
            cc1_mv = rt_adc_voltage((rt_adc_device_t)s_swotg_adc_dev, DEF_ADC_CC1_CHANNEL);  // CC1
            cc2_mv = rt_adc_voltage((rt_adc_device_t)s_swotg_adc_dev, DEF_ADC_CC2_CHANNEL);  // CC2

            /* Sum CC1 and CC2 voltages */
            cc_sum[role] = cc1_mv + cc2_mv;

            //rt_kprintf("%d: cc1:%04d + cc2:%04d = %04d(mv)\n", role, cc1_mv, cc2_mv, cc_sum[role]);
        }
        E_USB_ROLE role = isConnectedUSBRole(cc_sum);
        if (role != last_role)
        {
            //rt_kprintf("L: %d(mv), H:%d(mv)\n", cc_sum[evUSB_ROLE_DEVICE], cc_sum[evUSB_ROLE_HOST]);

            switch (role)
            {
            case evUSB_ROLE_DEVICE:
                rt_kprintf("=> Connected to Device. (Will switch USBPHY role to Host.)\n");

                SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_HSUSBROLE_Msk) | (0x1u << SYS_USBPHY_HSUSBROLE_Pos);  // Select HSUSBH
                SYS->USBPHY |= SYS_USBPHY_HSUSBEN_Msk | SYS_USBPHY_SBO_Msk;
                rt_thread_mdelay(1);
                SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;

                break;

            case evUSB_ROLE_HOST:
                rt_kprintf("=> Connected to Host. (Will switch USBPHY role to Device.)\n");

                SYS->USBPHY  = (SYS->USBPHY & ~(SYS_USBPHY_HSUSBROLE_Msk)) | (0x0u << SYS_USBPHY_HSUSBROLE_Pos);  // Select HSUSBD
                SYS->USBPHY &= ~SYS_USBPHY_HSUSBACT_Msk;
                SYS->USBPHY |= (SYS_USBPHY_HSUSBEN_Msk);
                rt_thread_mdelay(1);
                SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;

                break;

            case evUSB_ROLE_NONE:
            default:
                /* TODO: Add USB OTG de-initialization code here. */
                rt_kprintf("=> No connected.\n");

                SYS->USBPHY &= (~SYS_USBPHY_HSUSBEN_Msk);

                break;
            }

            last_role = role;
        }

        rt_thread_mdelay(DEF_ADC_SAMPLING_DURATION);
    }

fail_init:

    /* Disable EADC channels */
    if (s_swotg_adc_dev)
    {
        rt_adc_disable(s_swotg_adc_dev, DEF_ADC_CC1_CHANNEL);
        rt_adc_disable(s_swotg_adc_dev, DEF_ADC_CC2_CHANNEL);
    }

}

static int swotg_init(void)
{
#define DEF_THREAD_NAME "SWOTG"

    rt_thread_t swotg_thread = rt_thread_find(DEF_THREAD_NAME);
    if (swotg_thread == RT_NULL)
    {
        swotg_thread = rt_thread_create(DEF_THREAD_NAME,
                                        swotg_worker,
                                        RT_NULL,
                                        THREAD_STACK_SIZE,
                                        THREAD_PRIORITY,
                                        THREAD_TIMESLICE);

        if (swotg_thread != RT_NULL)
            rt_thread_startup(swotg_thread);
    }

    return 0;
}

MSH_CMD_EXPORT(swotg_init, enable ccx polling);
INIT_APP_EXPORT(swotg_init);

#endif
