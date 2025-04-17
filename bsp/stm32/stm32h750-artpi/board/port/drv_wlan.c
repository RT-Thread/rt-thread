/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-30     ZeroFree     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_WIFI

#include <drv_common.h>
#include <dev_wlan_mgnt.h>
#include <dev_wlan_prot.h>
#include <dev_wlan_cfg.h>
#include <string.h>
#include <fal.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME    "WLAN"
#define DBG_COLOR
#define DBG_LEVEL           DBG_LOG
#include <rtdbg.h>

#define NVRAM_GENERATED_MAC_ADDRESS      "macaddr=02:0A:F7:fe:86:1c"
#define WIFI_IMAGE_PARTITION_NAME        "wifi_image"
#define WIFI_INIT_THREAD_STACK_SIZE      (1024 * 4)
#define WIFI_INIT_THREAD_PRIORITY        (RT_THREAD_PRIORITY_MAX/2)
#define WIFI_INIT_WAIT_TIME              (rt_tick_from_millisecond(1000))

extern int wifi_hw_init(void);
static rt_bool_t init_flag = 0;
static const struct fal_partition *partition = RT_NULL;

rt_align(64)
static const char wifi_nvram_image[] =
    // # The following parameter values are just placeholders, need to be updated.
    "manfid=0x2d0"                                                       "\x00"
    "prodid=0x0726"                                                      "\x00"
    "vendid=0x14e4"                                                      "\x00"
    "devid=0x43e2"                                                       "\x00"
    "boardtype=0x0726"                                                   "\x00"
    "boardrev=0x1101"                                                    "\x00"
    "boardnum=22"                                                        "\x00"
    "xtalfreq=26000"                                                     "\x00"
    "sromrev=11"                                                         "\x00"
    "boardflags=0x00404201"                                              "\x00"
    "boardflags3=0x08000000"                                             "\x00"
    NVRAM_GENERATED_MAC_ADDRESS                                          "\x00"
    "nocrc=1"                                                            "\x00"
    "ag0=255"                                                            "\x00"
    "aa2g=1"                                                             "\x00"
    "ccode=ALL"
    "\x00"
    "swdiv_en=1"                                                         "\x00"
    "swdiv_gpio=2"                                                       "\x00"

    "pa0itssit=0x20"                                                     "\x00"
    "extpagain2g=0"                                                      "\x00"
    "pa2ga0=-215,5267,-656"                                              "\x00"
    "AvVmid_c0=0x0,0xc8"                                                 "\x00"
    "cckpwroffset0=5"                                                    "\x00"
    "maxp2ga0=80"                                                        "\x00"
    "txpwrbckof=6"                                                       "\x00"
    "cckbw202gpo=0x6666"                                                 "\x00"
    "legofdmbw202gpo=0xaaaaaaaa"                                         "\x00"
    "mcsbw202gpo=0xbbbbbbbb"                                             "\x00"
    "propbw202gpo=0xdd"                                                  "\x00"
    "ofdmdigfilttype=18"                                                 "\x00"
    "ofdmdigfilttypebe=18"                                               "\x00"
    "papdmode=1"                                                         "\x00"
    "papdvalidtest=1"                                                    "\x00"
    "pacalidx2g=32"                                                      "\x00"
    "papdepsoffset=-36"                                                  "\x00"
    "papdendidx=61"                                                      "\x00"
    "wl0id=0x431b"                                                       "\x00"
    "deadman_to=0xffffffff"                                              "\x00"
    "muxenab=0x11"                                                        "\x00"
    "spurconfig=0x3"                                                     "\x00"
    "\x00\x00";

int wiced_platform_resource_size(int resource)
{
    int size = 0;

    /* Download firmware */
    if (resource == 0)
    {
        size = 355159;
    }
    else if (resource == 1)
    {
        size = sizeof(wifi_nvram_image);
    }

    return size;
}

int wiced_platform_resource_read(int resource, uint32_t offset, void* buffer, uint32_t buffer_size)
{
    if (resource == 0)
    {
        /* read RF firmware from partition */
        fal_partition_read(partition, offset, buffer, buffer_size);
    }
    else if (resource == 1)
    {
        memcpy(buffer, &wifi_nvram_image[offset], buffer_size);
    }

    return buffer_size;
}

/**
 * wait milliseconds for wifi low level initialize complete
 *
 * time_ms: timeout in milliseconds
 */
int rt_hw_wlan_wait_init_done(rt_uint32_t time_ms)
{
    rt_uint32_t time_cnt = 0;

    /* wait wifi low level initialize complete */
    while (time_cnt <= (time_ms / 100))
    {
        time_cnt++;
        rt_thread_mdelay(100);

        if (init_flag == 1)
        {
            break;
        }
    }

    if (time_cnt > (time_ms / 100))
    {
        return -RT_ETIMEOUT;
    }

    return RT_EOK;
}


static void wifi_init_thread_entry(void *parameter)
{
    /* initialize fal */
    fal_init();
    partition = fal_partition_find(WIFI_IMAGE_PARTITION_NAME);

    if (partition == RT_NULL)
    {
        LOG_E("%s partition is not exist, please check your configuration!", WIFI_IMAGE_PARTITION_NAME);
        return;
    }

    /* initialize low level wifi(ap6212) library */
    wifi_hw_init();

    /* waiting for sdio bus stability */
    rt_thread_delay(WIFI_INIT_WAIT_TIME);

    /* set wifi work mode */
    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    /* NEED TODO !!! */
    /* rt_wlan_set_mode(RT_WLAN_DEVICE_AP_NAME, RT_WLAN_AP); */

    init_flag = 1;
}

int rt_hw_wlan_init(void)
{
    if (init_flag == 1)
    {
        return RT_EOK;
    }

    rt_thread_t tid = RT_NULL;

    tid = rt_thread_create("wifi_init", wifi_init_thread_entry, RT_NULL, WIFI_INIT_THREAD_STACK_SIZE, WIFI_INIT_THREAD_PRIORITY, 20);

    if (tid)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_E("Create wifi initialization thread fail!");
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_APP_EXPORT(rt_hw_wlan_init);

static int ap6212_init(void)
{
#define AP6212_WL_REG_ON    GET_PIN(C, 13)

    /* enable the WLAN REG pin */
    rt_pin_mode(AP6212_WL_REG_ON, PIN_MODE_OUTPUT);
    rt_pin_write(AP6212_WL_REG_ON, PIN_HIGH);

    return 0;
}
INIT_DEVICE_EXPORT(ap6212_init);

#endif /* RT_USING_WIFI */
