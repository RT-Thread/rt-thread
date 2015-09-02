#ifndef __HWTIMER_H__
#define __HWTIMER_H__

#include <rtthread.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 定时器控制命令 */
typedef enum
{
    HWTIMER_CTRL_TIMEOUT_SET = 0x01, /* 设置超时值 */
    HWTIMER_CTRL_FREQ_SET,           /* 设置计数频率 */
    HWTIMER_CTRL_START,              /* 启动定时器 */
    HWTIMER_CTRL_STOP,               /* 停止定时器 */
    HWTIMER_CTRL_INFO_GET,           /* 获取定时器特征信息 */
    HWTIMER_CTRL_MODE_SET            /* 设置定时模式 */
} rt_hwtimer_ctrl_t;

/* 定时模式 */
typedef enum
{
    HWTIMER_MODE_ONESHOT = 0x01,
    HWTIMER_MODE_PERIOD
} rt_hwtimer_mode_t;

/* 定时器计数值 */
typedef struct rt_hwtimerval
{
    rt_int32_t sec;      /* 秒 */
    rt_int32_t usec;     /* 微秒 */
} rt_hwtimerval_t;

#define HWTIMER_CNTMODE_UP      0x01 /* 定时器递增计数方式 */
#define HWTIMER_CNTMODE_DW      0x02 /* 定时器递减计数方式 */

struct rt_hwtimer_device;

struct rt_hwtimer_ops
{
    void (*init)(struct rt_hwtimer_device *timer);
    void (*deinit)(struct rt_hwtimer_device *timer);
    void (*start)(struct rt_hwtimer_device *timer, rt_hwtimer_mode_t mode);
    void (*stop)(struct rt_hwtimer_device *timer);
    rt_err_t (*timeout_set)(struct rt_hwtimer_device *timer, rt_uint32_t t);
    rt_uint32_t (*count_get)(struct rt_hwtimer_device *timer);
    rt_err_t (*control)(struct rt_hwtimer_device *timer, rt_uint32_t cmd, void *args);
};

/* 定时器基本参数(不可动态更改) */
struct rt_hwtimer_info
{
    rt_int32_t maxfreq;    /* 定时器支持的最大计数时钟 */
    rt_int32_t minfreq;    /* 定时器支持的最小计数时钟 */
    rt_uint32_t maxcnt;    /* 计数器最大超时值 */
    rt_uint8_t  cntmode;   /* 计数模式(递增/递减,应用层无需关心此参数) */
};

typedef struct rt_hwtimer_device
{
    struct rt_device parent;
    const struct rt_hwtimer_ops *ops;
    const struct rt_hwtimer_info *info;

    /* 驱动层不用关心以下参数 */
    rt_int32_t freq;                /* 计数频率 */
    rt_int32_t overflow;            /* 溢出次数 */
    float period_sec;               /* 溢出周期(s) */
    rt_int32_t cycles;              /* 循环次数 */
    rt_int32_t reload;              /* 重载cycles */
    rt_hwtimer_mode_t mode;         /* 定时模式 */
} rt_hwtimer_t;

rt_err_t rt_device_hwtimer_register(rt_hwtimer_t *timer, const char *name, void *user_data);
void rt_device_hwtimer_isr(rt_hwtimer_t *timer);

#ifdef __cplusplus
}
#endif

#endif
