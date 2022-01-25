/**************************************************************************//**
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-04-20      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_ADC_TOUCH)

#include "NuMicro.h"
#include <rtdevice.h>
#include <dfs_posix.h>
#include "drv_adc.h"
#include "touch.h"

#if !defined(PATH_CALIBRATION_FILE)
    #define PATH_CALIBRATION_FILE "/mnt/filesystem/ts_calibration"
#endif


typedef struct
{
    struct rt_touch_device dev;
    rt_uint32_t x_range;
    rt_uint32_t y_range;
} nu_adc_touch;
typedef nu_adc_touch *nu_adc_touch_t;

static nu_adc_touch s_NuAdcTouch = {0};

#if (BSP_LCD_WIDTH==320) && (BSP_LCD_HEIGHT==240)
static S_CALIBRATION_MATRIX g_sCalMat = { 43, -5839, 21672848, 4193, -11, -747882, 65536 };
static volatile uint32_t g_u32Calibrated = 1;
#else
static S_CALIBRATION_MATRIX g_sCalMat = { 1, 0, 0, 0, 1, 0, 1 };
static volatile uint32_t g_u32Calibrated = 0;
#endif

static int nu_adc_touch_readfile(void);

static const S_CALIBRATION_MATRIX g_sCalZero = { 1, 0, 0, 0, 1, 0, 1 };

static int nu_adc_cal_mat_get(const S_COORDINATE_POINT *psDispCP, S_COORDINATE_POINT *psADCCP, S_CALIBRATION_MATRIX *psCM)
{
#if (DEF_CAL_POINT_NUM==3)

    psCM->div = ((psADCCP[0].x - psADCCP[2].x) * (psADCCP[1].y - psADCCP[2].y)) -
                ((psADCCP[1].x - psADCCP[2].x) * (psADCCP[0].y - psADCCP[2].y)) ;

    if (psCM->div == 0)
    {
        return -1;
    }
    else
    {
        psCM->a = ((psDispCP[0].x - psDispCP[2].x) * (psADCCP[1].y - psADCCP[2].y)) -
                  ((psDispCP[1].x - psDispCP[2].x) * (psADCCP[0].y - psADCCP[2].y)) ;

        psCM->b = ((psADCCP[0].x - psADCCP[2].x) * (psDispCP[1].x - psDispCP[2].x)) -
                  ((psDispCP[0].x - psDispCP[2].x) * (psADCCP[1].x - psADCCP[2].x)) ;

        psCM->c = (psADCCP[2].x * psDispCP[1].x - psADCCP[1].x * psDispCP[2].x) * psADCCP[0].y +
                  (psADCCP[0].x * psDispCP[2].x - psADCCP[2].x * psDispCP[0].x) * psADCCP[1].y +
                  (psADCCP[1].x * psDispCP[0].x - psADCCP[0].x * psDispCP[1].x) * psADCCP[2].y ;

        psCM->d = ((psDispCP[0].y - psDispCP[2].y) * (psADCCP[1].y - psADCCP[2].y)) -
                  ((psDispCP[1].y - psDispCP[2].y) * (psADCCP[0].y - psADCCP[2].y)) ;

        psCM->e = ((psADCCP[0].x - psADCCP[2].x) * (psDispCP[1].y - psDispCP[2].y)) -
                  ((psDispCP[0].y - psDispCP[2].y) * (psADCCP[1].x - psADCCP[2].x)) ;

        psCM->f = (psADCCP[2].x * psDispCP[1].y - psADCCP[1].x * psDispCP[2].y) * psADCCP[0].y +
                  (psADCCP[0].x * psDispCP[2].y - psADCCP[2].x * psDispCP[0].y) * psADCCP[1].y +
                  (psADCCP[1].x * psDispCP[0].y - psADCCP[0].x * psDispCP[1].y) * psADCCP[2].y ;
    }

#elif (DEF_CAL_POINT_NUM==5)

    int i;
    float n, x, y, xx, yy, xy, z, zx, zy;
    float a, b, c, d, e, f, g;
    float scaling = 65536.0f;

    n = x = y = xx = yy = xy = 0;
    for (i = 0; i < DEF_CAL_POINT_NUM; i++)
    {
        n  += 1.0;
        x  += (float)psADCCP[i].x;
        y  += (float)psADCCP[i].y;
        xx += (float)psADCCP[i].x * psADCCP[i].x;
        yy += (float)psADCCP[i].y * psADCCP[i].y;
        xy += (float)psADCCP[i].x * psADCCP[i].y;
    }

    d = n * (xx * yy - xy * xy) + x * (xy * y - x * yy) + y * (x * xy - y * xx);
    if (d < 0.1 && d > -0.1)
    {
        return -1;
    }

    a = (xx * yy - xy * xy) / d;
    b = (xy * y  - x * yy)  / d;
    c = (x * xy  - y * xx)  / d;
    e = (n * yy  - y * y)   / d;
    f = (x * y   - n * xy)  / d;
    g = (n * xx  - x * x)   / d;

    z = zx = zy = 0;
    for (i = 0; i < DEF_CAL_POINT_NUM; i++)
    {
        z  += (float)psDispCP[i].x;
        zx += (float)psDispCP[i].x * psADCCP[i].x;
        zy += (float)psDispCP[i].x * psADCCP[i].y;
    }

    psCM->c = (int32_t)((a * z + b * zx + c * zy) * scaling);
    psCM->a = (int32_t)((b * z + e * zx + f * zy) * scaling);
    psCM->b = (int32_t)((c * z + f * zx + g * zy) * scaling);

    z = zx = zy = 0;
    for (i = 0; i < DEF_CAL_POINT_NUM; i++)
    {
        z  += (float)psDispCP[i].y;
        zx += (float)psDispCP[i].y * psADCCP[i].x;
        zy += (float)psDispCP[i].y * psADCCP[i].y;
    }

    psCM->f = (int32_t)((a * z + b * zx + c * zy) * scaling);
    psCM->d = (int32_t)((b * z + e * zx + f * zy) * scaling);
    psCM->e = (int32_t)((c * z + f * zx + g * zy) * scaling);

    psCM->div = (int32_t)scaling;

#else
#error "Not supported calibration method"
#endif
    return 0;
}

static void nu_adc_touch_cal(int32_t *sumx, int32_t *sumy)
{
    int32_t xtemp, ytemp;

    xtemp = *sumx;
    ytemp = *sumy;
    *sumx = (g_sCalMat.c +
             g_sCalMat.a * xtemp +
             g_sCalMat.b * ytemp) / g_sCalMat.div;
    *sumy = (g_sCalMat.f +
             g_sCalMat.d * xtemp +
             g_sCalMat.e * ytemp) / g_sCalMat.div;
}

static rt_size_t nu_adc_touch_readpoint(struct rt_touch_device *device, void *buf, rt_size_t read_num)
{
    static uint32_t last_report_x = 0, last_report_y = 0;
    struct rt_touch_data *pPoint = (struct rt_touch_data *)buf;
    nu_adc_touch_t psNuAdcTouch = (nu_adc_touch_t)device;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    int i;

    for (i = 0; i < read_num; i++)
    {
        uint32_t bufZ0 = 0, bufZ1 = 0;
        int32_t sumx = 0, sumy = 0;
        pPoint[i].timestamp = rt_touch_get_ts();
        pPoint[i].track_id = 0;

        if (nu_adc_touch_read_xyz((uint32_t *)&sumx, (uint32_t *)&sumy, &bufZ0, &bufZ1, 1) != 1)
            break;

        if (bufZ0 == 0)
        {
            /* Workaround: In this case, x, y values are unstable. so, report last point's coordinate.*/
            pPoint[i].event = RT_TOUCH_EVENT_UP;
            pPoint[i].x_coordinate = (uint16_t)last_report_x;
            pPoint[i].y_coordinate = (uint16_t)last_report_y;
        }
        else
        {
            if (g_u32Calibrated)
            {
                nu_adc_touch_cal(&sumx, &sumy);
            }
            last_report_x = sumx;
            last_report_y = sumy;

            pPoint[i].event = RT_TOUCH_EVENT_DOWN;
            pPoint[i].x_coordinate = (uint16_t)sumx;
            pPoint[i].y_coordinate = (uint16_t)sumy;
        }

        if (g_u32Calibrated)
        {
            bufZ0 = bufZ0 >> 3;
            pPoint[i].width = (bufZ0 > 255) ? 255 : bufZ0;

            //Limit max x, y coordinate if value is over its range.
            pPoint[i].x_coordinate = (pPoint[i].x_coordinate > psNuAdcTouch->x_range) ? psNuAdcTouch->x_range : pPoint[i].x_coordinate;
            pPoint[i].y_coordinate = (pPoint[i].y_coordinate > psNuAdcTouch->y_range) ? psNuAdcTouch->y_range : pPoint[i].y_coordinate;
        }
    }
    return (rt_size_t)i;
}

static rt_err_t nu_adc_touch_control(struct rt_touch_device *device, int cmd, void *data)
{
    nu_adc_touch_t psNuAdcTouch = (nu_adc_touch_t)device;
    RT_ASSERT(psNuAdcTouch != RT_NULL);

    switch (cmd)
    {
    case RT_TOUCH_CTRL_SET_X_RANGE: /* set x range */
        psNuAdcTouch->x_range = *((rt_int32_t *)data);
        break;

    case RT_TOUCH_CTRL_SET_Y_RANGE: /* set y range */
        psNuAdcTouch->y_range = *((rt_int32_t *)data);
        break;

    case RT_TOUCH_CTRL_ENABLE_INT: /* enable pen_down interrupt */
        nu_adc_touch_detect(RT_TRUE);
        break;

    case RT_TOUCH_CTRL_DISABLE_INT: /* disable pen_down interrupt */
        nu_adc_touch_detect(RT_FALSE);
        break;

    case RT_TOUCH_CTRL_POWER_ON:    /* Touch Power On */
        return nu_adc_touch_enable(device);

    case RT_TOUCH_CTRL_POWER_OFF:   /* Touch Power Off */
        return nu_adc_touch_disable();

    default:
        return -RT_ERROR;
    }
    return RT_EOK;
}

static struct rt_touch_ops touch_ops =
{
    .touch_readpoint = nu_adc_touch_readpoint,
    .touch_control = nu_adc_touch_control,
};

static void nu_adc_touch_update_calmat(S_CALIBRATION_MATRIX *psNewCalMat)
{
    if (psNewCalMat &&
            psNewCalMat->div != 0)
    {
        rt_memcpy(&g_sCalMat, psNewCalMat, sizeof(S_CALIBRATION_MATRIX));
        g_u32Calibrated = 1;
        rt_kprintf("Applied calibration data: %d, %d, %d, %d, %d, %d, %d\n",
                   g_sCalMat.a,
                   g_sCalMat.b,
                   g_sCalMat.c,
                   g_sCalMat.d,
                   g_sCalMat.e,
                   g_sCalMat.f,
                   g_sCalMat.div);

    }
}

static void nu_adc_touch_reset_calmat(void)
{
    rt_memcpy(&g_sCalMat, &g_sCalZero, sizeof(S_CALIBRATION_MATRIX));
    g_u32Calibrated = 0;
}

int rt_hw_adc_touch_init(void)
{
    /* Register touch device */
    s_NuAdcTouch.dev.info.type = RT_TOUCH_TYPE_RESISTANCE;
    s_NuAdcTouch.dev.info.vendor = RT_TOUCH_VENDOR_UNKNOWN;
    s_NuAdcTouch.dev.info.point_num = 1;
    s_NuAdcTouch.dev.info.range_x = BSP_LCD_WIDTH;
    s_NuAdcTouch.dev.info.range_y = BSP_LCD_HEIGHT;

    s_NuAdcTouch.dev.ops = &touch_ops;

    return (int)rt_hw_touch_register(&s_NuAdcTouch.dev, "adc_touch", RT_DEVICE_FLAG_INT_RX, RT_NULL);
}
INIT_DEVICE_EXPORT(rt_hw_adc_touch_init);


static rt_thread_t  adc_touch_thread = RT_NULL;
static rt_sem_t     adc_touch_sem = RT_NULL;
static int          adc_touch_worker_run = 0;

static rt_err_t adc_touch_rx_callback(rt_device_t dev, rt_size_t size)
{
    //rt_kprintf("[%s %d] %d\n", __func__, __LINE__, size);
    return rt_sem_release(adc_touch_sem);
}

static rt_err_t adc_request_point(rt_device_t pdev, struct rt_touch_data *psTouchPoint)
{
    rt_err_t ret = -RT_ERROR;

    if ((ret = rt_sem_take(adc_touch_sem, rt_tick_from_millisecond(500))) == RT_EOK)
    {
        rt_memset(psTouchPoint, 0, sizeof(struct rt_touch_data));

        if (rt_device_read(pdev, 0, psTouchPoint, s_NuAdcTouch.dev.info.point_num) == s_NuAdcTouch.dev.info.point_num)
        {
            ret = RT_EOK;
        }

    }

    return ret;
}

RT_WEAK void nu_touch_inputevent_cb(rt_int16_t x, rt_int16_t y, rt_uint8_t event)
{
}

static rt_device_t lcd_device = 0;
static struct rt_device_graphic_info info;

static void lcd_cleanscreen(void)
{
    if (info.framebuffer != RT_NULL)
    {
        /* Rendering */
        struct rt_device_rect_info rect;

        rt_memset(info.framebuffer, 0, (info.pitch * info.height));
        rect.x = 0;
        rect.y = 0;
        rect.width = info.width;
        rect.height = info.height;
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
    }
    else
    {
        // TODO
    }
}

#define DEF_DOT_NUMBER    9
#define DOTS_NUMBER       (DEF_DOT_NUMBER*DEF_DOT_NUMBER)
static void nu_draw_bots(int x, int y)
{
    if (info.framebuffer != RT_NULL)
    {
        /* Rendering */
        struct rt_device_rect_info rect;
        int i, j;
        int start_x = x - (DEF_DOT_NUMBER / 2);
        int start_y = y - (DEF_DOT_NUMBER / 2);

        if (info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_RGB565)
        {
            uint16_t *pu16Start = (uint16_t *)((uint32_t)info.framebuffer + (start_y) * info.pitch + (start_x * 2));
            for (j = 0; j < DEF_DOT_NUMBER; j++)
            {
                for (i = 0; i < DEF_DOT_NUMBER; i++)
                    pu16Start[i] = 0x07E0; //Green, RGB
                pu16Start += info.width;
            }
        }
        else if (info.pixel_format == RTGRAPHIC_PIXEL_FORMAT_ARGB888)
        {
            uint32_t *pu32Start = (uint32_t *)((uint32_t)info.framebuffer + (start_y) * info.pitch + (start_x * 4));
            for (j = 0; j < DEF_DOT_NUMBER; j++)
            {
                for (i = 0; i < DEF_DOT_NUMBER; i++)
                    pu32Start[i] = 0xff00ff00; //Green, ARGB
                pu32Start += info.width;
            }
        }
        else
        {
            //Not supported
        }

        rect.x = 0;
        rect.y = 0;
        rect.width = info.width;
        rect.height = info.height;
        rt_device_control(lcd_device, RTGRAPHIC_CTRL_RECT_UPDATE, &rect);
    }
    else
    {
        // TODO
    }
}

#if (DEF_CAL_POINT_NUM==3)
const S_COORDINATE_POINT sDispPoints[DEF_CAL_POINT_NUM] =
{
    {BSP_LCD_WIDTH / 4, BSP_LCD_HEIGHT / 2},
    {BSP_LCD_WIDTH - BSP_LCD_WIDTH / 4, BSP_LCD_HEIGHT / 4},
    {BSP_LCD_WIDTH / 2, BSP_LCD_HEIGHT - BSP_LCD_HEIGHT / 4}
};
#elif (DEF_CAL_POINT_NUM==5)
const static S_COORDINATE_POINT sDispPoints[DEF_CAL_POINT_NUM] =
{
#define DEF_CUT_PIECES 8
    {BSP_LCD_WIDTH / DEF_CUT_PIECES, BSP_LCD_HEIGHT / DEF_CUT_PIECES},
    {BSP_LCD_WIDTH - BSP_LCD_WIDTH / DEF_CUT_PIECES, BSP_LCD_HEIGHT / DEF_CUT_PIECES},
    {BSP_LCD_WIDTH - BSP_LCD_WIDTH / DEF_CUT_PIECES, BSP_LCD_HEIGHT - BSP_LCD_HEIGHT / DEF_CUT_PIECES},
    {BSP_LCD_WIDTH / DEF_CUT_PIECES, BSP_LCD_HEIGHT - BSP_LCD_HEIGHT / DEF_CUT_PIECES},

    {BSP_LCD_WIDTH / 2, BSP_LCD_HEIGHT / 2}
};
#endif

static int nu_adc_touch_readfile(void)
{
    int fd;

    S_CALIBRATION_MATRIX sCalMat;

    if ((fd = open(PATH_CALIBRATION_FILE, O_RDONLY, 0)) < 0)
    {
        goto exit_nu_adc_touch_readfile;
    }
    else if (read(fd, &sCalMat, sizeof(S_CALIBRATION_MATRIX)) == sizeof(S_CALIBRATION_MATRIX))
    {
        rt_kprintf("[%s] %s\n", __func__, PATH_CALIBRATION_FILE);
    }

    close(fd);

    nu_adc_touch_update_calmat(&sCalMat);

    return 0;

exit_nu_adc_touch_readfile:

    return -1;
}

static int nu_adc_touch_writefile(void *buf, int buf_len)
{
    int fd;

    if ((fd = open(PATH_CALIBRATION_FILE, O_WRONLY | O_CREAT, 0)) < 0)
    {
        goto exit_nu_adc_touch_writefile;
    }
    else if (write(fd, buf, buf_len) == buf_len)
    {
        rt_kprintf("[%s] %s\n", __func__, PATH_CALIBRATION_FILE);
    }

    close(fd);

    return 0;

exit_nu_adc_touch_writefile:

    return -1;
}

static void nu_touch_do_calibration(rt_device_t pdev)
{
    int i;
    rt_err_t result;

    S_CALIBRATION_MATRIX sCalMat;
    S_COORDINATE_POINT sADCPoints[DEF_CAL_POINT_NUM];

    lcd_device = rt_device_find("lcd");
    if (!lcd_device)
    {
        rt_kprintf("Not supported graphics ops\n");
        return;
    }

    result = rt_device_control(lcd_device, RTGRAPHIC_CTRL_GET_INFO, &info);
    if (result != RT_EOK)
    {
        rt_kprintf("error!");
        return;
    }

    result = rt_device_open(lcd_device, 0);
    if (result != RT_EOK)
    {
        rt_kprintf("opened?");
    }

    rt_device_control(lcd_device, RTGRAPHIC_CTRL_PAN_DISPLAY, info.framebuffer);
    rt_device_control(lcd_device, RTGRAPHIC_CTRL_POWERON, RT_NULL);

    for (i = 0; i < DEF_CAL_POINT_NUM; i++)
    {
        struct rt_touch_data sTouchPoint;
        int count = 0;

        lcd_cleanscreen();

        /* Drain RX queue before doing calibrate. */
        while (adc_request_point(pdev, &sTouchPoint) == RT_EOK);

        rt_thread_mdelay(100);

        /* Ready to calibrate */
        nu_draw_bots(sDispPoints[i].x, sDispPoints[i].y);

#define DEF_MAX_GET_POINT_NUM 5

        sADCPoints[i].x = 0;
        sADCPoints[i].y = 0;

        while (count < DEF_MAX_GET_POINT_NUM)
        {
            if (adc_request_point(pdev, &sTouchPoint) == RT_EOK)
            {
                sADCPoints[i].x += (int32_t)sTouchPoint.x_coordinate;
                sADCPoints[i].y += (int32_t)sTouchPoint.y_coordinate;
                rt_kprintf("[%d %d] - Disp:[%d, %d] -> ADC:[%d, %d]\n", i, count, sDispPoints[i].x, sDispPoints[i].y, sADCPoints[i].x, sADCPoints[i].y);
                count++;
            }
        }

        sADCPoints[i].x = (int32_t)((float)sADCPoints[i].x / DEF_MAX_GET_POINT_NUM);
        sADCPoints[i].y = (int32_t)((float)sADCPoints[i].y / DEF_MAX_GET_POINT_NUM);
        rt_kprintf("[%d] - Disp:[%d, %d], ADC:[%d, %d]\n", i, sDispPoints[i].x, sDispPoints[i].y, sADCPoints[i].x, sADCPoints[i].y);

        rt_thread_mdelay(300);
    }

    lcd_cleanscreen();

    /* Get calibration matrix. */
    if (nu_adc_cal_mat_get(&sDispPoints[0], &sADCPoints[0], &sCalMat) == 0)
    {
        /* Finally, update calibration matrix to drivers. */
        nu_adc_touch_update_calmat(&sCalMat);

        nu_adc_touch_writefile(&sCalMat, sizeof(sCalMat));

        for (i = 0; i < DEF_CAL_POINT_NUM; i++)
        {
            rt_kprintf("[%d] - Disp:[%d, %d], ADC:[%d, %d]\n", i, sDispPoints[i].x, sDispPoints[i].y, sADCPoints[i].x, sADCPoints[i].y);
        }
    }
    else
    {
        rt_kprintf("Failed to calibrate.\n");
    }

    rt_device_control(lcd_device, RTGRAPHIC_CTRL_POWEROFF, RT_NULL);
    rt_device_close(lcd_device);

    return;
}

static void adc_touch_entry(void *parameter)
{
    struct rt_touch_data touch_point;

    rt_err_t result;
    rt_device_t pdev;

    int max_range;

    adc_touch_sem = rt_sem_create("adc_touch_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(adc_touch_sem != RT_NULL);

    pdev = rt_device_find("adc_touch");
    if (!pdev)
    {
        rt_kprintf("Not found\n");
        return ;
    }

    nu_adc_touch_readfile();

    result = rt_device_open(pdev, RT_DEVICE_FLAG_INT_RX);
    RT_ASSERT(result == RT_EOK);

    result = rt_device_set_rx_indicate(pdev, adc_touch_rx_callback);
    RT_ASSERT(result == RT_EOK);

    max_range = BSP_LCD_WIDTH;
    result = rt_device_control(pdev, RT_TOUCH_CTRL_SET_X_RANGE, (void *)&max_range);
    RT_ASSERT(result == RT_EOK);

    max_range = BSP_LCD_HEIGHT;
    result = rt_device_control(pdev, RT_TOUCH_CTRL_SET_Y_RANGE, (void *)&max_range);
    RT_ASSERT(result == RT_EOK);

    result = rt_device_control(pdev, RT_TOUCH_CTRL_POWER_ON, RT_NULL);
    RT_ASSERT(result == RT_EOK);

    while (adc_touch_worker_run)
    {
        if (!g_u32Calibrated)
        {
            rt_kprintf("Start ADC touching calibration.\n");
            nu_touch_do_calibration(pdev);
            rt_kprintf("Stop ADC touching calibration.\n");
            continue;
        }

        if (adc_request_point(pdev, &touch_point) == RT_EOK)
        {
            if (touch_point.event == RT_TOUCH_EVENT_DOWN
                    || touch_point.event == RT_TOUCH_EVENT_UP
                    || touch_point.event == RT_TOUCH_EVENT_MOVE)
            {
                nu_touch_inputevent_cb(touch_point.x_coordinate, touch_point.y_coordinate, touch_point.event);

                rt_kprintf("x=%d y=%d event=%s%s%s\n",
                           touch_point.x_coordinate,
                           touch_point.y_coordinate,
                           (touch_point.event == RT_TOUCH_EVENT_DOWN) ? "DOWN" : "",
                           (touch_point.event == RT_TOUCH_EVENT_UP) ? "UP" : "",
                           (touch_point.event == RT_TOUCH_EVENT_MOVE) ? "MOVE" : "");
            }
        }
    }

    result = rt_device_control(pdev, RT_TOUCH_CTRL_POWER_OFF, RT_NULL);
    RT_ASSERT(result == RT_EOK);

    result = rt_device_close(pdev);
    RT_ASSERT(result == RT_EOK);
}


/* Support "nu_touch_start" command line in msh mode */
static rt_err_t nu_touch_start(int argc, char **argv)
{
    if (adc_touch_thread == RT_NULL)
    {
        adc_touch_thread = rt_thread_create("adc_touch_thread",
                                            adc_touch_entry,
                                            RT_NULL,
                                            4096,
                                            25,
                                            5);
        adc_touch_worker_run = 1;
        if (adc_touch_thread != RT_NULL)
            rt_thread_startup(adc_touch_thread);
    }
    return 0;
}
MSH_CMD_EXPORT(nu_touch_start, e.g: start adc touch);

/* Support "nu_touch_stop" command line in msh mode */
static rt_err_t nu_touch_stop(int argc, char **argv)
{
    adc_touch_worker_run = 0;
    adc_touch_thread = RT_NULL;
    return 0;
}
MSH_CMD_EXPORT(nu_touch_stop, e.g: stop adc touch);

static int nu_touch_autostart(void)
{
    return nu_touch_start(0, RT_NULL);
}
INIT_APP_EXPORT(nu_touch_autostart);

static rt_err_t nu_touch_calibration(int argc, char **argv)
{
    /* Clean calibration matrix data for getting raw adc value. */
    nu_adc_touch_reset_calmat();

    return 0;
}
MSH_CMD_EXPORT(nu_touch_calibration, for adc touch);

#endif //#if defined(BSP_USING_ADC_TOUCH)
