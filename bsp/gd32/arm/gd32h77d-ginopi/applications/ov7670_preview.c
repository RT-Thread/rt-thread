/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-08-06     RTT          add OV7670 LVGL preview
 * 2026-09-08     CYFS         implement asynchronous OV7670 preview with internal AXI SRAM buffers
 */

#include <rtconfig.h>

#ifdef BSP_USING_OV7670_PREVIEW

#include <lvgl.h>
#include <rtdevice.h>
#include <rtthread.h>
#include <board.h>

#include "drv_ov7670.h"
#include "ov7670_preview.h"

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#define DBG_TAG                         "app.ov7670"
#define DBG_LVL                         DBG_INFO
#include <rtdbg.h>

#define OV7670_PREVIEW_PERIOD_MS        10U
#define OV7670_CONTROL_PERIOD_MS        20U
#define OV7670_PREVIEW_BUFFER_COUNT     2U
#define OV7670_PREVIEW_INVALID_BUFFER   (-1)
#define OV7670_CAPTURE_THREAD_STACK     4096U

#ifndef PKG_LVGL_THREAD_PRIO
#define PKG_LVGL_THREAD_PRIO            (RT_THREAD_PRIORITY_MAX * 2U / 3U)
#endif

#define OV7670_CAPTURE_THREAD_PRIORITY  (PKG_LVGL_THREAD_PRIO + 1U)

/* Static storage cannot fall back to the automatically bound SDRAM heap. */
rt_align(32) static rt_uint8_t ov7670_preview_buffers[OV7670_PREVIEW_BUFFER_COUNT]
                                                       [OV7670_FRAME_SIZE];
#define OV7670_PREVIEW_BUFFER(index)    ov7670_preview_buffers[index]

enum ov7670_preview_request
{
    OV7670_PREVIEW_REQUEST_NONE = 0,
    OV7670_PREVIEW_REQUEST_START,
    OV7670_PREVIEW_REQUEST_STOP,
};

static const lv_image_dsc_t preview_image_descriptors[OV7670_PREVIEW_BUFFER_COUNT] =
{
    {
        .header.magic = LV_IMAGE_HEADER_MAGIC,
        .header.cf = LV_COLOR_FORMAT_RGB565,
        .header.flags = 0,
        .header.w = OV7670_WIDTH,
        .header.h = OV7670_HEIGHT,
        .header.stride = OV7670_WIDTH * 2U,
        .data_size = OV7670_FRAME_SIZE,
        .data = OV7670_PREVIEW_BUFFER(0U),
    },
    {
        .header.magic = LV_IMAGE_HEADER_MAGIC,
        .header.cf = LV_COLOR_FORMAT_RGB565,
        .header.flags = 0,
        .header.w = OV7670_WIDTH,
        .header.h = OV7670_HEIGHT,
        .header.stride = OV7670_WIDTH * 2U,
        .data_size = OV7670_FRAME_SIZE,
        .data = OV7670_PREVIEW_BUFFER(1U),
    },
};

static rt_device_t preview_camera;
static struct rt_thread preview_capture_thread;
rt_align(RT_ALIGN_SIZE) static rt_uint8_t
    preview_capture_stack[OV7670_CAPTURE_THREAD_STACK];
static struct rt_semaphore preview_capture_semaphore;
static lv_obj_t *preview_previous_screen;
static lv_obj_t *preview_screen;
static lv_obj_t *preview_image;
static lv_timer_t *preview_frame_timer;
static lv_timer_t *preview_control_timer;
static volatile enum ov7670_preview_request preview_request;
static volatile rt_bool_t preview_ready;
static volatile rt_bool_t preview_active;
static volatile rt_bool_t preview_capture_enabled;
static volatile rt_bool_t preview_capture_thread_ready;
static volatile rt_int32_t preview_display_buffer;
static volatile rt_int32_t preview_ready_buffer;
static volatile rt_int32_t preview_capture_buffer;
static volatile rt_uint32_t preview_frame_count;
static volatile rt_uint32_t preview_display_count;
static volatile rt_uint32_t preview_drop_count;
static volatile rt_uint32_t preview_error_count;
static volatile rt_err_t preview_last_result;
static volatile rt_tick_t preview_start_tick;

static rt_int32_t ov7670_preview_acquire_buffer(void)
{
    rt_int32_t index;

    rt_enter_critical();
    if (!preview_capture_enabled)
    {
        rt_exit_critical();
        return OV7670_PREVIEW_INVALID_BUFFER;
    }

    for (index = 0; index < (rt_int32_t)OV7670_PREVIEW_BUFFER_COUNT; index++)
    {
        if ((index != preview_display_buffer) &&
            (index != preview_ready_buffer) &&
            (index != preview_capture_buffer))
        {
            preview_capture_buffer = index;
            rt_exit_critical();
            return index;
        }
    }
    rt_exit_critical();
    return OV7670_PREVIEW_INVALID_BUFFER;
}

static void ov7670_preview_capture_entry(void *parameter)
{
    rt_int32_t buffer_index;
    rt_ssize_t size;
    rt_err_t result;
    rt_uint32_t error_count;

    RT_UNUSED(parameter);
    while (1)
    {
        rt_sem_take(&preview_capture_semaphore, RT_WAITING_FOREVER);
        while (preview_capture_enabled)
        {
            buffer_index = ov7670_preview_acquire_buffer();
            if (buffer_index == OV7670_PREVIEW_INVALID_BUFFER)
            {
                /* With two buffers, a ready frame must be consumed before
                 * capture resumes. Never overwrite the displayed or ready frame. */
                rt_thread_mdelay(1U);
                continue;
            }

            size = rt_device_read(preview_camera, 0,
                                  OV7670_PREVIEW_BUFFER(buffer_index),
                                  OV7670_FRAME_SIZE);
            result = size == OV7670_FRAME_SIZE ? RT_EOK :
                     (size < 0 ? (rt_err_t)size : -RT_EIO);

            rt_enter_critical();
            preview_capture_buffer = OV7670_PREVIEW_INVALID_BUFFER;
            if (!preview_capture_enabled)
            {
                rt_exit_critical();
                continue;
            }
            if (result == RT_EOK)
            {
                if (preview_ready_buffer != OV7670_PREVIEW_INVALID_BUFFER)
                {
                    preview_drop_count++;
                }
                preview_ready_buffer = buffer_index;
                preview_frame_count++;
                preview_last_result = RT_EOK;
                rt_exit_critical();
                continue;
            }

            preview_error_count++;
            error_count = preview_error_count;
            preview_last_result = result;
            rt_exit_critical();
            if ((error_count <= 3U) || ((error_count % 30U) == 0U))
            {
                LOG_E("frame capture failed: %d", result);
            }
        }
    }
}

static void ov7670_preview_frame(lv_timer_t *timer)
{
    rt_int32_t buffer_index;

    RT_UNUSED(timer);
    /* LVGL timer callbacks run after the previous refresh has finished reading
     * its image sources; only then can capture reuse the old display buffer. */
    rt_enter_critical();
    buffer_index = preview_ready_buffer;
    if (buffer_index != OV7670_PREVIEW_INVALID_BUFFER)
    {
        preview_ready_buffer = OV7670_PREVIEW_INVALID_BUFFER;
        preview_display_buffer = buffer_index;
        preview_display_count++;
    }
    rt_exit_critical();

    if ((buffer_index == OV7670_PREVIEW_INVALID_BUFFER) ||
        (preview_image == RT_NULL))
    {
        return;
    }

    lv_image_set_src(preview_image, &preview_image_descriptors[buffer_index]);
    lv_obj_invalidate(preview_image);
}

static void ov7670_preview_stop(void)
{
    if (!preview_active)
    {
        return;
    }

    rt_enter_critical();
    preview_capture_enabled = RT_FALSE;
    preview_ready_buffer = OV7670_PREVIEW_INVALID_BUFFER;
    preview_active = RT_FALSE;
    rt_exit_critical();

    if (preview_frame_timer != RT_NULL)
    {
        lv_timer_del(preview_frame_timer);
        preview_frame_timer = RT_NULL;
    }
    if ((preview_previous_screen != RT_NULL) &&
        (lv_screen_active() == preview_screen))
    {
        lv_screen_load(preview_previous_screen);
    }
    if (preview_screen != RT_NULL)
    {
        lv_obj_delete(preview_screen);
    }

    preview_previous_screen = RT_NULL;
    preview_screen = RT_NULL;
    preview_image = RT_NULL;
    LOG_I("preview stopped");
}

static void ov7670_preview_back_event(lv_event_t *event)
{
    RT_UNUSED(event);
    ov7670_preview_request_stop();
}

static void ov7670_preview_start(void)
{
    rt_err_t result;
    lv_obj_t *back_button;
    lv_obj_t *back_label;

    if (preview_active)
    {
        return;
    }
    if (!preview_capture_thread_ready)
    {
        preview_last_result = -RT_ENOSYS;
        LOG_E("capture thread is unavailable");
        return;
    }

    if (preview_camera == RT_NULL)
    {
        preview_camera = rt_device_find(OV7670_DEVICE_NAME);
        if (preview_camera == RT_NULL)
        {
            preview_last_result = -RT_ENOSYS;
            LOG_E("device %s not found", OV7670_DEVICE_NAME);
            return;
        }

        result = rt_device_open(preview_camera, RT_DEVICE_OFLAG_RDONLY);
        if (result != RT_EOK)
        {
            preview_camera = RT_NULL;
            preview_last_result = result;
            LOG_E("camera open failed: %d", result);
            return;
        }
    }

    preview_previous_screen = lv_screen_active();
    preview_screen = lv_obj_create(RT_NULL);
    if (preview_screen == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto _failed;
    }
    lv_obj_set_scrollable(preview_screen, false);
    lv_obj_set_style_bg_color(preview_screen, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(preview_screen, LV_OPA_COVER, 0);

    preview_image = lv_image_create(preview_screen);
    if (preview_image == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto _failed;
    }
    rt_memset(OV7670_PREVIEW_BUFFER(preview_display_buffer), 0,
              OV7670_FRAME_SIZE);
    lv_image_set_src(preview_image,
                     &preview_image_descriptors[preview_display_buffer]);
    lv_image_set_scale(preview_image, 512U);
    lv_image_set_antialias(preview_image, false);
    lv_obj_center(preview_image);

    back_button = lv_button_create(preview_screen);
    if (back_button == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto _failed;
    }
    lv_obj_set_size(back_button, 96, 44);
    lv_obj_align(back_button, LV_ALIGN_TOP_LEFT, 16, 16);
    lv_obj_add_event_cb(back_button, ov7670_preview_back_event,
                        LV_EVENT_CLICKED, RT_NULL);

    back_label = lv_label_create(back_button);
    if (back_label == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto _failed;
    }
    lv_label_set_text(back_label, LV_SYMBOL_LEFT " Back");
    lv_obj_center(back_label);

    preview_frame_timer = lv_timer_create(ov7670_preview_frame,
                                           OV7670_PREVIEW_PERIOD_MS,
                                           RT_NULL);
    if (preview_frame_timer == RT_NULL)
    {
        result = -RT_ENOMEM;
        goto _failed;
    }

    preview_frame_count = 0U;
    preview_display_count = 0U;
    preview_drop_count = 0U;
    preview_error_count = 0U;
    preview_last_result = RT_EOK;
    preview_start_tick = rt_tick_get();
    rt_enter_critical();
    preview_ready_buffer = OV7670_PREVIEW_INVALID_BUFFER;
    preview_capture_enabled = RT_TRUE;
    preview_active = RT_TRUE;
    rt_exit_critical();
    lv_screen_load(preview_screen);
    lv_timer_ready(preview_frame_timer);
    rt_sem_release(&preview_capture_semaphore);
    LOG_I("preview started: %ux%u RGB565", OV7670_WIDTH, OV7670_HEIGHT);
    return;

_failed:
    if (preview_frame_timer != RT_NULL)
    {
        lv_timer_del(preview_frame_timer);
        preview_frame_timer = RT_NULL;
    }
    if (preview_screen != RT_NULL)
    {
        lv_obj_delete(preview_screen);
    }
    preview_previous_screen = RT_NULL;
    preview_screen = RT_NULL;
    preview_image = RT_NULL;
    preview_last_result = result;
    LOG_E("preview start failed: %d", result);
}

static void ov7670_preview_control(lv_timer_t *timer)
{
    enum ov7670_preview_request request;

    RT_UNUSED(timer);
    rt_enter_critical();
    request = preview_request;
    preview_request = OV7670_PREVIEW_REQUEST_NONE;
    rt_exit_critical();

    if (request == OV7670_PREVIEW_REQUEST_START)
    {
        ov7670_preview_start();
    }
    else if (request == OV7670_PREVIEW_REQUEST_STOP)
    {
        ov7670_preview_stop();
    }
}

void ov7670_preview_init(void)
{
    rt_err_t result;
    rt_ubase_t buffers_begin = (rt_ubase_t)ov7670_preview_buffers;

    if (preview_control_timer != RT_NULL)
    {
        return;
    }

    if ((buffers_begin < 0x24000000U) ||
        (buffers_begin + sizeof(ov7670_preview_buffers) > (rt_ubase_t)GD32_SRAM_END))
    {
        preview_last_result = -RT_ENOMEM;
        LOG_E("preview buffers must be placed in internal AXI SRAM");
        return;
    }

    preview_display_buffer = 0;
    preview_ready_buffer = OV7670_PREVIEW_INVALID_BUFFER;
    preview_capture_buffer = OV7670_PREVIEW_INVALID_BUFFER;
    preview_last_result = RT_EOK;
    result = rt_sem_init(&preview_capture_semaphore, "ovprev", 0,
                         RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        preview_last_result = result;
        LOG_E("cannot initialize capture semaphore: %d", result);
        return;
    }

    result = rt_thread_init(&preview_capture_thread, "ovcap",
                            ov7670_preview_capture_entry, RT_NULL,
                            preview_capture_stack,
                            sizeof(preview_capture_stack),
                            OV7670_CAPTURE_THREAD_PRIORITY, 10U);
    if (result != RT_EOK)
    {
        rt_sem_detach(&preview_capture_semaphore);
        preview_last_result = result;
        LOG_E("cannot initialize capture thread: %d", result);
        return;
    }
    result = rt_thread_startup(&preview_capture_thread);
    if (result != RT_EOK)
    {
        rt_thread_detach(&preview_capture_thread);
        rt_sem_detach(&preview_capture_semaphore);
        preview_last_result = result;
        LOG_E("cannot start capture thread: %d", result);
        return;
    }
    preview_capture_thread_ready = RT_TRUE;

    preview_control_timer = lv_timer_create(ov7670_preview_control,
                                             OV7670_CONTROL_PERIOD_MS,
                                             RT_NULL);
    if (preview_control_timer == RT_NULL)
    {
        preview_last_result = -RT_ENOMEM;
        LOG_E("cannot create preview control timer");
        return;
    }
    preview_ready = RT_TRUE;
}

rt_err_t ov7670_preview_request_start(void)
{
    if (!preview_ready)
    {
        return -RT_ENOSYS;
    }

    rt_enter_critical();
    preview_request = OV7670_PREVIEW_REQUEST_START;
    rt_exit_critical();
    return RT_EOK;
}

rt_err_t ov7670_preview_request_stop(void)
{
    if (!preview_ready)
    {
        return -RT_ENOSYS;
    }

    rt_enter_critical();
    preview_request = OV7670_PREVIEW_REQUEST_STOP;
    rt_exit_critical();
    return RT_EOK;
}

void ov7670_preview_get_status(struct ov7670_preview_status *status)
{
    if (status == RT_NULL)
    {
        return;
    }

    rt_enter_critical();
    status->ready = preview_ready;
    status->active = preview_active;
    status->frame_count = preview_frame_count;
    status->display_count = preview_display_count;
    status->drop_count = preview_drop_count;
    status->error_count = preview_error_count;
    status->last_result = preview_last_result;
    rt_exit_critical();
}

#ifdef RT_USING_FINSH
static const char *ov7670_preview_request_name(enum ov7670_preview_request request)
{
    if (request == OV7670_PREVIEW_REQUEST_START)
    {
        return "start";
    }
    if (request == OV7670_PREVIEW_REQUEST_STOP)
    {
        return "stop";
    }
    return "none";
}

static void ov7670_preview(int argc, char **argv)
{
    enum ov7670_preview_request request;
    rt_bool_t ready;
    rt_bool_t active;
    rt_uint32_t frames;
    rt_uint32_t displayed;
    rt_uint32_t dropped;
    rt_uint32_t errors;
    rt_uint32_t fps_tenths;
    rt_tick_t start_tick;
    rt_tick_t elapsed_ticks;
    rt_err_t last_result;

    if ((argc == 1) ||
        ((argc == 2) && (rt_strcmp(argv[1], "start") == 0)))
    {
        ov7670_preview_request_start();
        rt_kprintf("OV7670 preview start requested\n");
        return;
    }
    if ((argc == 2) && (rt_strcmp(argv[1], "stop") == 0))
    {
        ov7670_preview_request_stop();
        rt_kprintf("OV7670 preview stop requested\n");
        return;
    }
    if ((argc == 2) && (rt_strcmp(argv[1], "status") == 0))
    {
        rt_enter_critical();
        ready = preview_ready;
        active = preview_active;
        request = preview_request;
        frames = preview_frame_count;
        displayed = preview_display_count;
        dropped = preview_drop_count;
        errors = preview_error_count;
        start_tick = preview_start_tick;
        last_result = preview_last_result;
        rt_exit_critical();
        elapsed_ticks = rt_tick_get() - start_tick;
        fps_tenths = (active && (elapsed_ticks != 0U)) ?
                     (rt_uint32_t)(((rt_uint64_t)frames *
                                    RT_TICK_PER_SECOND * 10U) /
                                   elapsed_ticks) : 0U;
        rt_kprintf("OV7670 preview ready=%d active=%d request=%s "
                   "captured=%u displayed=%u dropped=%u errors=%u "
                   "fps=%u.%u last=%d\n",
                   ready, active, ov7670_preview_request_name(request),
                   frames, displayed, dropped, errors,
                   fps_tenths / 10U, fps_tenths % 10U, last_result);
        return;
    }

    rt_kprintf("usage: ov7670_preview [start|stop|status]\n");
}
MSH_CMD_EXPORT(ov7670_preview, start or stop the OV7670 LCD preview);
#endif /* RT_USING_FINSH */

#endif /* BSP_USING_OV7670_PREVIEW */
