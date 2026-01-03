
/**
 * @file drv_tim_pulse_width.c
 * @brief
 * @author jiache (wanghuan3037@fiberhome.com)
 * @version 1.0
 * @date 2025-12-02
 *      1.添加注释，加入日志宏的定义
 *      2.处理头文件，将不必要的直接放入c文件
 *      3.处理了代码警告问题
 *      4.修改了pwm输入模式的滤波，将3改为0
 *      5. 基于N32g457 TIM8 测量：输入pwm的最大宽度测量范围 455100ns(Reload=0xfffc),最小的脉宽可以测量到28ns（COMP=0x02）,经测试1MHz的方波，输出比较器必须大于2时，测量测对准确
 *              > pwm set 1 455100 28   455100ns=2197Hz，测量的频率不可以低于这个，否测测量的周期不准哦
 *      6回调函数的为空判定的bug修复
 *      7.在dam中断中需要+一个对象偏移，用于宏配置，于是添加了一个枚举，用于定义tim测量设备
 *      8.这个驱动使用了一个2000字节的dma缓存区，用户定时器的dma数据传输，以降低CPU的使用率；缓存越小，占用越小
 *      9.驱动使用了dma的传输过半中断，可以防止dma传输完成导致的数据覆盖问题。
 *      10.经过测试测量1MHz的方波的，脉宽 大于28ns情况，脉冲数据误差±1个脉冲；同时测量2MHz，将缓存放大到4096，mcu直接忙的打印都不输出了
 *      11.将定时器的时钟和gpio时钟统一放在drv_base.c中
 *      12.这个驱动必须注册一个回调函数，用于每一个脉宽数据的处理，回调函数执行与高优先级线程中
 *      13.该驱动支持高级定时器和通用定时器
 *      14.目前驱动仅仅支持通道1输入测量，理论上通道2也是可以的。
 *  @copyright Copyright (c) 2025  58
 *
 */
#include <rtthread.h>

#ifdef BSP_USING_TIM_PULSE_WIDTH

#define DBG_TAG "PWT_7NS"
#define DBG_LVL DBG_INFO

#include <rtdbg.h>

#include <rtdevice.h>
#include "board.h"
#include "drv_tim_pulse_width.h"
#include "drv_base.h"

/* 脉宽测量设备控制命令 */
#define RT_DEVICE_CTRL_PULSE_WIDTH_TEST_TIMEOUT (RT_DEVICE_CTRL_BASE(Miscellaneous) + 0x10) // 间隔XX时间，开始统计采集的脉冲数量
#define RT_DEVICE_CTRL_PULSE_WIDTH_SET_CALLBACK (RT_DEVICE_CTRL_BASE(Miscellaneous) + 0x11) // 设置回调函数

#define DMA_BUFFER_SIZE 4096 // 2KB DMA缓冲区

/* GPIO配置结构 */
struct n32_tim_pulse_width_gpio
{
    GPIO_Module *gpio_port; /* GPIO端口 */
    rt_uint16_t gpio_pin;   /* GPIO引脚 */
    rt_uint8_t gpio_af;     /* 复用功能 */
};
/**dam配置结构体 */
typedef struct
{
    uint32_t rcc_dma;        // dma的时钟
    DMA_Module *dma;         // dma外设
    DMA_ChannelType *dma_ch; // dam通道
    uint32_t dma_remap;      // dma通道映射
    uint32_t dma_irq;        // dma的中断号
    uint32_t dma_it_tx;      // dma传输完成标记
    uint32_t dma_it_hx;      // dma传输过半标记
} dma_config_t;

/* 脉宽测量配置结构 */
struct n32_tim_pulse_width_config
{

    TIM_Module *timer_periph;                    /* 定时器外设 */
    rt_uint16_t tim_channel;                     /* 定时器通道 */
    rt_uint16_t prescaler;                       /* 预分频器 */
    struct n32_tim_pulse_width_gpio gpio_config; /* GPIO配置 */
    dma_config_t dma_cfg;                        /**dma配置结构 */
    char *name;                                  /**脉宽采集设备名称 */
    char *info;                                  /*附加信息*/
};

/* 脉宽测量设备结构 */
struct n32_tim_pulse_width_device
{
    struct rt_device parent;
    struct n32_tim_pulse_width_config *config;
    // 每一次dma传输完成产生一次中断
    fun_pulse_callback pulse_callback;
    rt_uint32_t dma_buffer[DMA_BUFFER_SIZE]; /* DMA缓冲区指针 */
    rt_thread_t thread;                      // 线程
    rt_mailbox_t box;                        // 接收dma传输完成的信号
    // DMA_ChannelType *dma_channel;       /* DMA通道 */
};

// 前向声明
static void n32_tim_pulse_width_dma_config(struct n32_tim_pulse_width_device *device);
static void n32_tim_pulse_width_dma_start(struct n32_tim_pulse_width_device *device);
/* 重新启动DMA传输 */
// void n32_tim_pulse_width_dma_restart(struct n32_tim_pulse_width_device *device);

// dma事件
enum EV
{
    TX_OK = 0X0FFF0000,
    HX_OK,
    OTHERS
};

enum PULSE_TEST_DEV
{
#ifdef BSP_USING_TIM1_PULSE_WIDTH
    PWTD_TIM1,
#endif
#ifdef BSP_USING_TIM4_PULSE_WIDTH
    PWTD_TIM4,
#endif

#ifdef BSP_USING_TIM8_PULSE_WIDTH
    PWTD_TIM8,
#endif


    PWTD_NUM /*设备数量*/
};

/**
 * @brief 脉宽采集对象
 *
 */
static struct n32_tim_pulse_width_device tim_pulse_width_device[PWTD_NUM];

/* TIM1脉宽测量配置 - PA8 */

static struct n32_tim_pulse_width_config tim_pulse_width_config[PWTD_NUM] =
    {
#ifdef BSP_USING_TIM1_PULSE_WIDTH
        {
            .timer_periph = TIM1,
            .tim_channel = TIM_CH_1,
            .prescaler = 0, /* 1MHz计数频率 */
            .name = "pulse1",
            .info = "TIM1 PA8",
            .gpio_config = {
                .gpio_port = GPIOA,
                .gpio_pin = GPIO_PIN_8,
                .gpio_af = 0,
            },
            .dma_cfg = {
                .rcc_dma = RCC_AHB_PERIPH_DMA1,
                .dma = DMA1,
                .dma_ch = DMA1_CH2,
                .dma_remap = DMA1_REMAP_TIM1_CH1,
                .dma_irq = DMA1_Channel2_IRQn,
                .dma_it_tx = DMA1_INT_TXC2,
                .dma_it_hx = DMA1_INT_HTX2,
            },
        },
#endif/*BSP_USING_TIM1_PULSE_WIDTH*/

#ifdef BSP_USING_TIM4_PULSE_WIDTH
        {.timer_periph = TIM4, .tim_channel = TIM_CH_1, .prescaler = 0, /* 1MHz计数频率 */
         .name = "pulse4",
         .info = "TIM4 PB6",
         .gpio_config = {
             .gpio_port = GPIOB,
             .gpio_pin = GPIO_PIN_6,
             .gpio_af = 0,
         },
         .dma_cfg = {
             .rcc_dma = RCC_AHB_PERIPH_DMA1,
             .dma = DMA1,
             .dma_ch = DMA1_CH1,
             .dma_remap = DMA1_REMAP_TIM4_CH1,
             .dma_irq = DMA1_Channel1_IRQn,
             .dma_it_tx = DMA1_INT_TXC1,
             .dma_it_hx = DMA1_INT_HTX1,
         }}
#endif/*BSP_USING_TIM4_PULSE_WIDTH*/

#ifdef BSP_USING_TIM8_PULSE_WIDTH
        {.timer_periph = TIM8, .tim_channel = TIM_CH_1, .prescaler = 0, /* 1MHz计数频率 */
         .name = "pulse8",
         .info = "TIM8 PC6",
         .gpio_config = {
             .gpio_port = GPIOC,
             .gpio_pin = GPIO_PIN_6,
             .gpio_af = 0,
         },
         .dma_cfg = {
             .rcc_dma = RCC_AHB_PERIPH_DMA2,
             .dma = DMA2,
             .dma_ch = DMA2_CH3,
             .dma_remap = DMA2_REMAP_TIM8_CH1,
             .dma_irq = DMA2_Channel3_IRQn,
             .dma_it_tx = DMA2_INT_TXC3,
             .dma_it_hx = DMA2_INT_HTX3,
         }}
#endif/*BSP_USING_TIM8_PULSE_WIDTH*/

};

/* DMA传输完成中断处理函数 */
static void n32_tim_pulse_width_dma_irq_handler(struct n32_tim_pulse_width_device *device)
{
    // uint32_t int_flag = 0;
    static volatile rt_uint32_t cnt = 0;
    const dma_config_t *config = &(device->config->dma_cfg);

    if (DMA_GetIntStatus(config->dma_it_tx, config->dma) != RESET)
    {
        /* 清除DMA传输完成中断标志 */
        DMA_ClrIntPendingBit(config->dma_it_tx, config->dma);
        // 传递传输完成信号
        rt_mb_send_wait(device->box, TX_OK, 0);
    }
    else if (DMA_GetIntStatus(config->dma_it_hx, config->dma) != RESET)
    {
        /* 清除DMA传输过半中断标志 */
        DMA_ClrIntPendingBit(config->dma_it_hx, config->dma);

        // 传递传输完成信号
        rt_mb_send_wait(device->box, HX_OK, 0);
    }

    // else if (DMA_GetIntStatus(DMA1_INT_ERR2, DMA1) != RESET)
    // {
    //     /* 清除DMA传输错误中断标志 */
    //     DMA_ClrIntPendingBit(DMA1_INT_ERR2, DMA1);
    // }
}
/*
线程 用于处理dam传输的数据，集中处理，降低CPU利用率
*/
static void thread_entry_pulse(void *parameter)
{
    rt_ubase_t val = 0;
    rt_uint32_t len = 0;
    rt_uint32_t data_size = 0;
    rt_uint32_t data_start = 0;

    struct n32_tim_pulse_width_device *device = (struct n32_tim_pulse_width_device *)parameter;
    while (1)
    {
        if (RT_EOK == rt_mb_recv(device->box, &val, RT_WAITING_FOREVER) && device->pulse_callback)
        {
            if (TX_OK == val) // 完成
            {
                data_size = (DMA_BUFFER_SIZE >> 1);
                data_start = (DMA_BUFFER_SIZE >> 1);
            }
            else if (HX_OK == val) // 过半
            {
                data_start = 0;
                data_size = (DMA_BUFFER_SIZE >> 1);
            }
            else // 用户手动停止时的处理
            {
                /**
                 * 这里可能重复处理，上半段的数据，但是数据被清零了，不影响结果
                 *
                 */
                data_start = 0;
                data_size = DMA_BUFFER_SIZE - val;
            }

            len = data_start + data_size;
            for (int i = data_start; i < len; i += 2)
            {
                // 这里处理数据区分脉宽测量,dataptr[i]低电平的宽度，dataptr[i+1]高电平的宽度；只有非零才是有效的数
                if (device->dma_buffer[i + 1] && device->dma_buffer[i] && device->pulse_callback)
                {
                    device->pulse_callback(&device->parent, device->dma_buffer[i + 1], device->dma_buffer[i], 0);
                }
            }
        }
        // 表示测量测试结束
        if (val != TX_OK && val != HX_OK)
        {
            device->pulse_callback(&device->parent, 0, 0, 1);
        }
        // 数据置零--很重要
        rt_memset(device->dma_buffer + data_start, 0, sizeof(rt_uint32_t) * data_size);
    }
}
/**
 * @brief gpio的配重
 *
 * @param  device
 */
static void n32_tim_pulse_width_gpio_init(struct n32_tim_pulse_width_device *device)
{
    struct n32_tim_pulse_width_config *config = device->config;
    GPIO_InitType gpio_init;
    /* 使能GPIO时钟 */
    n32_gpio_rcc_enable(config->gpio_config.gpio_port);
    /* 配置GPIO引脚 */
    gpio_init.Pin = config->gpio_config.gpio_pin;
    gpio_init.GPIO_Mode = GPIO_Mode_IPU;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitPeripheral(config->gpio_config.gpio_port, &gpio_init);

    /* 配置AFIO重映射（如果需要） */
    if (config->gpio_config.gpio_af)
    {
        GPIO_ConfigPinRemap(config->gpio_config.gpio_af, ENABLE);
    }
}
/**
 * @brief 定时器的基本参数配置
 *
 * @param  device
 */
static void n32_tim_pulse_width_timebase_init(struct n32_tim_pulse_width_device *device)
{
    struct n32_tim_pulse_width_config *config = device->config;
    TIM_TimeBaseInitType tim_base_init;

    /* 使能AFIO时钟 */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);

    /* 使能定时器时钟 */
    n32_time_rcc_config(config->timer_periph);

    /* 配置定时器基本参数 */
    TIM_InitTimBaseStruct(&tim_base_init);
    tim_base_init.Period = 0xFFFF; /* 最大计数值 */
    tim_base_init.Prescaler = config->prescaler;
    tim_base_init.ClkDiv = TIM_CLK_DIV1;
    tim_base_init.CntMode = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(config->timer_periph, &tim_base_init);
}
/**
 * @brief pwm输入模式配置
 *
 * @param  device
 */
static void n32_tim_pulse_width_pwm_init(struct n32_tim_pulse_width_device *device)
{
    struct n32_tim_pulse_width_config *config = device->config;
    TIM_ICInitType tim_ic_init;
    /* 配置PWM输入模式 */
    TIM_InitIcStruct(&tim_ic_init);
    tim_ic_init.Channel = config->tim_channel;           /* 使用通道1和通道2 */
    tim_ic_init.IcPolarity = TIM_IC_POLARITY_RISING;     /* CC1上升沿捕获周期 */
    tim_ic_init.IcSelection = TIM_IC_SELECTION_DIRECTTI; /* CC1直接映射到TI1 */
    tim_ic_init.IcPrescaler = TIM_IC_PSC_DIV1;
    tim_ic_init.IcFilter = 0;
    TIM_ConfigPwmIc(config->timer_periph, &tim_ic_init);
}

// /* 重新启动DMA传输 */
// void n32_tim_pulse_width_dma_restart(struct n32_tim_pulse_width_device *device)
// {
//     const dma_config_t *config = &(device->config->dma_cfg);

//     //   // 启动定时器
//     // TIM_Enable(device->config->timer_periph, DISABLE);
//     // // 禁用DMA通道
//     // DMA_EnableChannel(device->dma_channel, DISABLE);

//     rt_uint32_t curcnt = DMA_GetCurrDataCounter(config->dma_ch);
//     // 传递传输完成信号
//     rt_mb_send_wait(device->box, curcnt, 0);
//     // 重新配置DMA缓冲区大小
//     // DMA_SetCurrDataCounter(device->dma_channel, DMA_BUFFER_SIZE);

//     // // 重新启用DMA通道
//     // DMA_EnableChannel(device->dma_channel, ENABLE);
//     //   // 启动定时器
//     // TIM_Enable(device->config->timer_periph, ENABLE);
// }

// DMA配置函数
static void n32_tim_pulse_width_dma_config(struct n32_tim_pulse_width_device *device)
{
    TIM_Module *tim = device->config->timer_periph;
    const dma_config_t *config = &(device->config->dma_cfg);
    DMA_InitType dma_init;

    rt_memset(device->dma_buffer, 0, sizeof(rt_uint32_t) * (DMA_BUFFER_SIZE));
    // 初始化DMA
    RCC_EnableAHBPeriphClk(config->rcc_dma, ENABLE);

    // 配置DMA通道
    dma_init.PeriphAddr = (uint32_t)&tim->DADDR; // 捕获/比较寄存器1地址
    dma_init.MemAddr = (uint32_t)device->dma_buffer;
    dma_init.Direction = DMA_DIR_PERIPH_SRC;
    dma_init.BufSize = DMA_BUFFER_SIZE;
    dma_init.PeriphInc = DMA_PERIPH_INC_DISABLE;
    dma_init.DMA_MemoryInc = DMA_MEM_INC_ENABLE;
    dma_init.PeriphDataSize = DMA_PERIPH_DATA_SIZE_WORD;
    dma_init.MemDataSize = DMA_MemoryDataSize_Word;
    dma_init.CircularMode = DMA_MODE_CIRCULAR;
    dma_init.Priority = DMA_PRIORITY_HIGH;
    dma_init.Mem2Mem = DMA_M2M_DISABLE;

    DMA_Init(config->dma_ch, &dma_init);

    DMA_RequestRemap(config->dma_remap, config->dma, config->dma_ch, ENABLE);

    // 配置DMA传输完成中断
    DMA_ConfigInt(config->dma_ch, DMA_INT_TXC, ENABLE);
    DMA_ConfigInt(config->dma_ch, DMA_INT_HTX, ENABLE);

    // 配置NVIC
    NVIC_InitType nvic_init;
    nvic_init.NVIC_IRQChannel = config->dma_irq;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 2;
    nvic_init.NVIC_IRQChannelSubPriority = 1;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);

    // 使能定时器的DMA请求
    TIM_ConfigDma(tim, TIM_DMABASE_CAPCMPDAT1, TIM_DMABURST_LENGTH_2TRANSFERS); // 配置dam传输的开始地址CAPCMPDAT1和传输数量2TRANSFERS，
    TIM_EnableDma(tim, TIM_DMA_CC1, ENABLE);
}

// DMA启动函数
static void n32_tim_pulse_width_dma_start(struct n32_tim_pulse_width_device *device)
{
    // 启动DMA传输
    DMA_EnableChannel(device->config->dma_cfg.dma_ch, ENABLE);
}

/* 设备初始化 */
static rt_err_t n32_tim_pulse_width_open(rt_device_t dev)
{
    struct n32_tim_pulse_width_device *device = (struct n32_tim_pulse_width_device *)dev;
    struct n32_tim_pulse_width_config *config = device->config;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(config != RT_NULL);

    // 接收dma的传输结束信号
    device->box = rt_mb_create(config->name, 10, RT_IPC_FLAG_FIFO);
    RT_ASSERT(device->box != RT_NULL);
    /* 创建线程 1，名称是 thread1，入口是 thread1_entry*/
    device->thread = rt_thread_create(config->name,
                                      thread_entry_pulse, device,
                                      512,
                                      5, 20);
    /* 如果获得线程控制块，启动这个线程 */
    if (device->thread != RT_NULL)
        rt_thread_startup(device->thread);

    // gpio
    n32_tim_pulse_width_gpio_init(device);
    // timbase
    n32_tim_pulse_width_timebase_init(device);
    // pwm
    n32_tim_pulse_width_pwm_init(device);

    /* 配置从模式：复位模式，TI1FP1作为触发源 */
    TIM_SelectInputTrig(config->timer_periph, TIM_TRIG_SEL_TI1FP1);  /* 选择TI1FP1作为触发源 */
    TIM_SelectSlaveMode(config->timer_periph, TIM_SLAVE_MODE_RESET); /* 复位模式 */

    // 配置DMA
    n32_tim_pulse_width_dma_config(device);
    // 启动DMA
    n32_tim_pulse_width_dma_start(device);

    // 启动定时器
    TIM_Enable(config->timer_periph, ENABLE);

    LOG_I("TIM PWM input open ok %s info =%s", config->name, config->info);

    return RT_EOK;
}
/**
 * @brief 驱动的接口contrl函数
 *
 * @param  dev
 * @param  cmd
 * @param  args
 * @return rt_err_t
 */
static rt_err_t n32_tim_pulse_width_control(rt_device_t dev, int cmd, void *args)
{
    struct n32_tim_pulse_width_device *device = (struct n32_tim_pulse_width_device *)dev;
    const dma_config_t *config = &(device->config->dma_cfg);
    rt_uint32_t curcnt = 0;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_PULSE_WIDTH_TEST_TIMEOUT: // 超时开始统计这个时间段的脉宽测量数据
        curcnt = DMA_GetCurrDataCounter(config->dma_ch);
        // 传递传输完成信号
        rt_mb_send_wait(device->box, curcnt, 0);
        break;
    case RT_DEVICE_CTRL_PULSE_WIDTH_SET_CALLBACK: // 注册回调函数
        device->pulse_callback = (fun_pulse_callback)args;
        break;
    default:
        break;
    }
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
/**设备操作函数接口 */
const struct rt_device_ops ops = {
    .init = RT_NULL,
    .open = n32_tim_pulse_width_open,
    .close = RT_NULL,
    .write = RT_NULL,
    .control = n32_tim_pulse_width_control,
    .read = RT_NULL,
};
#endif
/* 注册脉宽测量设备 */
static rt_err_t n32_tim_pulse_width_register(struct n32_tim_pulse_width_device *device,
                                             struct n32_tim_pulse_width_config *config)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(config != RT_NULL);
    rt_memset(device, 0, sizeof(struct n32_tim_pulse_width_device));

    device->config = config;
    device->parent.type = RT_Device_Class_Miscellaneous;
    device->parent.user_data = config;
#ifdef RT_USING_DEVICE_OPS
    device->parent.ops = &ops;
#else

    device->parent.init = RT_NULL;
    device->parent.open = n32_tim_pulse_width_open;
    device->parent.control = n32_tim_pulse_width_control;
    device->parent.write = RT_NULL;
    device->parent.read = RT_NULL;
    device->parent.close = RT_NULL;
#endif
    return rt_device_register(&device->parent, config->name, RT_DEVICE_FLAG_RDONLY);
}

#ifdef BSP_USING_TIM1_PULSE_WIDTH
// TIM1 DMA中断处理函数
void DMA1_Channel2_IRQHandler(void)
{
    rt_interrupt_enter();
    n32_tim_pulse_width_dma_irq_handler(tim_pulse_width_device + PWTD_TIM1);
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_TIM4_PULSE_WIDTH
// TIM1 DMA中断处理函数
void DMA1_Channel1_IRQHandler(void)
{
    rt_interrupt_enter();
    n32_tim_pulse_width_dma_irq_handler(tim_pulse_width_device + PWTD_TIM4);
    rt_interrupt_leave();
}
#endif


#ifdef BSP_USING_TIM8_PULSE_WIDTH
// TIM8 DMA中断处理函数
void DMA2_Channel3_IRQHandler(void)
{
    rt_interrupt_enter();
    n32_tim_pulse_width_dma_irq_handler(tim_pulse_width_device + PWTD_TIM8);
    rt_interrupt_leave();
}
#endif

static int rt_hw_tim1_pulse_width_init(void)
{

    for (int i = 0; i < PWTD_NUM; i++)
    {
        n32_tim_pulse_width_register(tim_pulse_width_device + i,
                                     tim_pulse_width_config + i);
        LOG_I("register pwm width test %s info :%s", tim_pulse_width_config[i].name,tim_pulse_width_config[i].info);
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_tim1_pulse_width_init);

#ifdef BSP_USING_PULSE_WIDTH_DEMO
/**
 * @file drv_tim_pulse_width.c
 * @brief
 * @author jiache (wanghuan3037@fiberhome.com)
 * @version 1.0
 * @date 2025-12-02
 *
 * 输入pwm的最大宽度测量范围 455100ns(0xfffc),最小的脉宽可以测量到28ns（0x02），
 *这个驱动必须注册一个回调函数，用于每一个脉宽数据的处理，回调函数执行与高优先级线程中
 * @copyright Copyright (c) 2025  58
 *
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_tim_pulse_width.h"
#include <rtdbg.h>
#define DEV_NAME "pulse4"

static rt_device_t pwm_input_dev = RT_NULL;
static rt_uint32_t total_pulse_count = 0, period_ns;
static rt_uint32_t cnt = 0;
rt_thread_t thread; // 线程
rt_mailbox_t box;   // 接收dma传输完成的信号
static void pulse_callback(rt_device_t dev, rt_uint32_t pulse_width_us, rt_uint32_t period_us, rt_uint32_t status)
{
    if (status)
    {
        rt_mb_send_wait(box, cnt, 0);
        cnt = 0;
    }
    else
    {
        cnt++;
        total_pulse_count = pulse_width_us;
        period_ns = period_us;
    }
}

void timeout_1S(void *parameter)
{

    rt_device_t pwm_dev = (rt_device_t)parameter;
    rt_device_control(pwm_input_dev, RT_DEVICE_CTRL_PULSE_WIDTH_TEST_TIMEOUT, 0);
}

/* 线程 1 的入口函数 */
static void thread_entry_data(void *parameter)
{
    rt_base_t val = 0;
    rt_uint32_t len = 0;
    rt_uint32_t data_size = 0;
    rt_uint32_t data_start = 0;
    struct n32_tim_pulse_width_device *device = (struct n32_tim_pulse_width_device *)parameter;
    while (1)
    {
        if (RT_EOK == rt_mb_recv(box, &val, RT_WAITING_FOREVER))
        {

            LOG_I("CNT %d width %d period_ns %d(%04x)", val, total_pulse_count, period_ns, period_ns);
        }
    }
}

/* PWM输入测试命令 */
static int pwm_input_test(void)
{

    /* 查找设备 */
    pwm_input_dev = rt_device_find(DEV_NAME);

    if (pwm_input_dev == RT_NULL)
    {
        LOG_W("Device %s not found!", DEV_NAME);
        return -1;
    }

    /* 设置回调函数 */
    //    rt_device_set_rx_indicate(pwm_input_dev,pulse_callback);
    rt_device_control(pwm_input_dev, RT_DEVICE_CTRL_PULSE_WIDTH_SET_CALLBACK, pulse_callback);

    /* 打开设备 */
    if (rt_device_open(pwm_input_dev, RT_DEVICE_OFLAG_RDONLY) != RT_EOK)
    {
        LOG_W("Failed to open device %s", DEV_NAME);
        return -1;
    }

    LOG_I("PWM input test started on %s", DEV_NAME);

    rt_timer_t timer = rt_timer_create("pulse", timeout_1S, pwm_input_dev, 1000, RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_HARD_TIMER);

    rt_timer_start(timer);

    // 接收dma的传输结束信号
    box = rt_mb_create("pulse", 10, RT_IPC_FLAG_FIFO);
    RT_ASSERT(box != RT_NULL);
    /* 创建线程 1，名称是 thread1，入口是 thread1_entry*/
    thread = rt_thread_create("pulseapp",
                              thread_entry_data, NULL,
                              512,
                              25, 20);
    /* 如果获得线程控制块，启动这个线程 */
    if (thread != RT_NULL)
        rt_thread_startup(thread);

    return 0;
}
INIT_APP_EXPORT(pwm_input_test);
// MSH_CMD_EXPORT(pwm_input_test, PWM input mode test);

#endif/*BSP_USING_PULSE_WIDTH_DEMO*/

#endif /*BSP_USING_TIM_PULSE_WIDTH*/
