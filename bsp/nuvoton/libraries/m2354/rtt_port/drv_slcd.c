/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-11-11      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_SLCD)

#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"
#include <drv_slcd.h>

/* Private define ---------------------------------------------------------------*/
#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "slcd"
#define DBG_COLOR
#include <rtdbg.h>

enum
{
    SLCD_START = -1,
    SLCD_IDX,
    SLCD_CNT
};
#define LCD_ALPHABET_NUM    7

/* Private typedef --------------------------------------------------------------*/
struct nu_slcd
{
    struct rt_device dev;
    char *name;
    LCD_T *base;
    uint32_t rst;
    rt_mutex_t lock;
};
typedef struct nu_slcd *nu_slcd_t;

/* Private functions ------------------------------------------------------------*/

/* Public functions ------------------------------------------------------------*/

/* Private variables ------------------------------------------------------------*/
static struct nu_slcd nu_slcd_arr [] =
{
    {
        .name = "slcd",
        .base = LCD,
        .rst = LCD_RST,
    }
}; /* nu_slcd_arr */

static S_LCD_CFG_T g_SLCDCfg =
{
    __LXT,                      /*!< LCD clock source frequency */
    LCD_COM_DUTY_1_8,           /*!< COM duty */
    LCD_BIAS_LV_1_4,            /*!< Bias level */
    64,                         /*!< Operation frame rate */
    LCD_WAVEFORM_TYPE_A_NORMAL, /*!< Waveform type */
    LCD_DISABLE_ALL_INT,        /*!< Interrupt source */
    LCD_LOW_DRIVING_AND_BUF_ON, /*!< Driving mode */
    LCD_VOLTAGE_SOURCE_VLCD,    /*!< Voltage source */
};

static rt_err_t nu_slcd_open(struct rt_device *dev, rt_uint16_t oflag)
{
    if (dev->ref_count == 0)
    {
        nu_slcd_t psNuSLcd = (nu_slcd_t)dev;

        /* Reset LCD module */
        SYS_ResetModule(psNuSLcd->rst);

        uint32_t u32ActiveFPS = LCD_Open(&g_SLCDCfg);

        /* LCD Initialize and calculate real frame rate */
        LOG_I("Working frame rate is %dHz on Type-%c.\n\n", u32ActiveFPS, (g_SLCDCfg.u32WaveformType == LCD_PCTL_TYPE_Msk) ? 'B' : 'A');

        /* Enable LCD display */
        LCD_ENABLE_DISPLAY();
    }

    return RT_EOK;
}

static rt_err_t nu_slcd_close(struct rt_device *dev)
{
    if (dev->ref_count == 0)
    {
        /* Disable LCD display */
        LCD_DISABLE_DISPLAY();
    }
    return RT_EOK;
}

static rt_ssize_t nu_slcd_write(struct rt_device *dev,
                               rt_off_t          pos,
                               const void       *buffer,
                               rt_size_t         size)
{
    nu_slcd_pixel_t psSlcdPixel;
    nu_slcd_t psNuSLCD = (nu_slcd_t)dev;

    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size == sizeof(struct nu_slcd_pixel));

    psSlcdPixel = (nu_slcd_pixel_t)buffer;

    /* Critical section */
    rt_mutex_take(psNuSLCD->lock, RT_WAITING_FOREVER);
    LCD_SetPixel(psSlcdPixel->m_u32Com, psSlcdPixel->m_u32Seg, psSlcdPixel->m_u32OnFlag);
    rt_mutex_release(psNuSLCD->lock);

    return size;
}

static rt_err_t nu_slcd_control(struct rt_device *dev,
                                int              cmd,
                                void             *args)
{
    rt_err_t ret = RT_EOK;
    switch (cmd)
    {
    case NU_SLCD_CMD_SET_LCD_CFG:
    {
        S_LCD_CFG_T *psLCDCfg;

        RT_ASSERT(args != RT_NULL);
        psLCDCfg = (S_LCD_CFG_T *)args;

        rt_memcpy((void *)&g_SLCDCfg, (void *)psLCDCfg, sizeof(S_LCD_CFG_T));
    }
    break;

    case NU_SLCD_CMD_SET_CP_VOLTAGE:
    {
        /*
        LCD_CP_VOLTAGE_LV_0  2.6 V
        LCD_CP_VOLTAGE_LV_1  2.8 V
        LCD_CP_VOLTAGE_LV_2  3.0 V
        LCD_CP_VOLTAGE_LV_3  3.2 V
        LCD_CP_VOLTAGE_LV_4  3.4 V
        LCD_CP_VOLTAGE_LV_5  3.6 V
        */
        uint32_t u32CPVol;
        RT_ASSERT(args != RT_NULL);

        u32CPVol = *((uint32_t *)args) ;
        if ((u32CPVol >> LCD_PCTL_CPVSEL_Pos) <= (LCD_CP_VOLTAGE_LV_5 >> LCD_PCTL_CPVSEL_Pos))
        {
            LCD_SET_CP_VOLTAGE(u32CPVol);
        }
        else
        {
            ret = -RT_ERROR;
        }
    }
    break;
    default:
        return -RT_EINVAL;
    }
    return ret;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops slcd_ops =
{
    RT_NULL,
    nu_slcd_open,
    nu_slcd_close,
    RT_NULL,
    nu_slcd_write,
    nu_slcd_control
};
#endif

rt_err_t rt_hw_slcd_register(struct rt_device *device,
                             const char              *name,
                             rt_uint32_t              flag,
                             void                    *data)
{
    RT_ASSERT(device != RT_NULL);

    device->type        = RT_Device_Class_Char;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->ops         = &slcd_ops;
#else
    device->init        = RT_NULL;
    device->open        = nu_slcd_open;
    device->close       = nu_slcd_close;
    device->read        = RT_NULL;
    device->write       = nu_slcd_write;
    device->control     = nu_slcd_control;
#endif
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

/**
 * Hardware SLCD Initialization
 */
static int rt_hw_slcd_init(void)
{
    int i;
    rt_err_t ret = RT_EOK;

    for (i = (SLCD_START + 1); i < SLCD_CNT; i++)
    {
        ret = rt_hw_slcd_register(&nu_slcd_arr[i].dev, nu_slcd_arr[i].name, RT_DEVICE_FLAG_RDWR, NULL);
        RT_ASSERT(ret == RT_EOK);
        nu_slcd_arr[i].lock = rt_mutex_create(nu_slcd_arr[i].name, RT_IPC_FLAG_PRIO);
        RT_ASSERT(nu_slcd_arr[i].lock != RT_NULL);
    }

    return (int)ret;
}
INIT_DEVICE_EXPORT(rt_hw_slcd_init);

#endif //#if defined(BSP_USING_SLCD)
