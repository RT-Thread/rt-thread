#ifndef __TOUCH_H__
#define __TOUCH_H__

#include <rtthread.h>

#define RT_TOUCH_NORMAL             0
#define RT_TOUCH_CALIBRATION_DATA   1
#define RT_TOUCH_CALIBRATION        2
#define RT_TOUCH_EVENTPOST          3
#define RT_TOUCH_EVENTPOST_PARAM    4

struct calibration_data
{
    rt_uint16_t min_x, max_x;
    rt_uint16_t min_y, max_y;
};

struct rt_touch_event
{
    rt_uint16_t x;
    rt_uint16_t y;  
    int pressed;
};

typedef void (*rt_touch_calibration_func_t)(rt_uint16_t x, rt_uint16_t y);

typedef void (*rt_touch_eventpost_func_t)(void *, struct rt_touch_event *);

int rtgui_touch_hw_init(void);

#endif

