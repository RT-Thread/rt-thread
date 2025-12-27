/**
 * @file tim_etr_cnt.c
 * @brief
 * @author jiache (wanghuan3037@fiberhome.com)
 * @version 1.0
 * @date 2025-11-28
 * 2025-11-28
 *      1.引脚重映射;
 *      2.支持了RT_USING_DEVICE_OPS的定义,
 *      3.增加了N457支持的所有定时器外部ETR计数驱动
 *      4.日志输出的标签设置
 *      5.Kconfig添加了引脚选择
 *      6.这里添加了依赖RT_USING_HWTIMER
 *      7.测试了默认和复用引脚均计数OK
 * 202512-2
 *      1.将定时器的时钟和gpio时钟统一放在drv_base.c中
 * 2025-11-28
 *
 * 2025-12-02
 *  RT_USING_DEVICE_OPS 宏的ops没有添加ops条件编译
 2025-12-06 
    1.修改了在N32L406的兼容驱动代码
    2.经测试TIM1的ETR PA12脉冲采样正常.经过测试100K可以采集到，1M方法采集不了
    3.经过测试TIM2 PA0用于外部ETR计数，正常，测试OK，100K的脉冲测量不可行，10K可行，20K正常，25K可以
    4.使用TIM_ConfigExtClkMode1和TIM_ConfigExtClkMode2就可以实现外部时钟的计数配置
    5.测试错误：：使用外部计数TIM2,ETR PA0测试发现25K,20K，16K，12K在N32L406计数采集OK，50K严重丢数，测试不对，PA0我的看法板连接了按键，按键有一个滤波电容产生了计数的影响。
    5.在N32L406计数采集，使用外部计数TIM1,ETR PA12测试发现100K,1MHz，2MHz，10MOK，还是高级定时器牛逼
    6.使用外部计数TIM2,ETR PA15测试,100K，1M（测试OK误差2个计数），10M(可以测，但是，多了666K)在N32L406计数采集OK
    7.使用外部计数TIM9,ETR PB测试,100Kok
    8.经过测试TIM_ConfigExtClkMode2的滤波设置为1时m,在测试10M时，没有计数
 * @copyright Copyright (c) 2025  58
 *
 */
#include "tim_etr_cnt.h"
#ifdef BSP_USING_TIM_ETR_CNT

#include "board.h"
#include <rtdevice.h>
#include <rtthread.h>

#define DBG_TAG "ETR"
#ifdef BSP_USING_TIM_ETR_CNT_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_INFO
#endif
#include <rtdbg.h>
#include "drv_base.h"
typedef struct
{
    struct rt_device parent;
    GPIO_Module *gpio_grp; // gpio分组
    uint16_t pin;          // gpio pin
    TIM_Module *time;      // 定时器
    uint32_t irq_up;       // 定时器溢出中断
    // uint32_t gpio_rcc;      // gpio时钟
    volatile uint32_t over; // 溢出次数
    uint32_t ioremap;       // gpio重映射
    char name[RT_NAME_MAX];
    char *info_str;
} time_counter_etr_t;

static time_counter_etr_t s_times_count_etr[] = {

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
#define N32G45X_CONFIG
#ifdef BSP_USING_TIM1_ETR_CNT
#ifdef TIM1_ETR_PIN_PA12
    {
        .gpio_grp = GPIOA,
        .pin = GPIO_PIN_12,
        .ioremap = 0, /* [PA12=(0,1,2) PE7=(3)]*/
        .time = TIM1,
        // .gpio_rcc = RCC_APB2_PERIPH_GPIOA,
        .irq_up = TIM1_UP_IRQn,
        .info_str = "TIM1 PA12",
    },
#endif
#ifdef TIM1_ETR_PIN_PE7
    {
        .gpio_grp = GPIOE,
        .pin = GPIO_PIN_7,
        .ioremap = GPIO_ALL_RMP_TIM1, /* [PA12=(0,1,2) PE7=(3)]*/
        .time = TIM1,
        // .gpio_rcc = RCC_APB2_PERIPH_GPIOE,
        .irq_up = TIM1_UP_IRQn,
        .info_str = "TIM1 PE7",

    },
#endif
#endif

#ifdef BSP_USING_TIM2_ETR_CNT
#ifdef TIM2_ETR_PIN_PA0
    {
        .gpio_grp = GPIOA,
        .pin = GPIO_PIN_0,
        .ioremap = 0, /*[PA0=0;PA15=(1,3);PA0=2;]*/
        .time = TIM2,
        // .gpio_rcc = RCC_APB2_PERIPH_GPIOA,
        .irq_up = TIM2_IRQn,
        .info_str = "TIM2 PA0",
    },
#endif /*TIM2_ETR_PIN_PA0*/
#ifdef TIM2_ETR_PIN_PA15
    {
        .gpio_grp = GPIOA,
        .pin = GPIO_PIN_15,
        .ioremap = GPIO_PartialRemap1_TIM2, /*[PA0=0;PA15=(1,3);PA0=2;]*/
        .time = TIM2,
        // .gpio_rcc = RCC_APB2_PERIPH_GPIOA,
        .irq_up = TIM2_IRQn,
        .info_str = "TIM2 PA15",
    },
#endif /*TIM2_ETR_PIN_PA15*/
#endif /*BSP_USING_TIM2_ETR_CNT*/

#ifdef BSP_USING_TIM3_ETR_CNT
    {
        .gpio_grp = GPIOD,
        .pin = GPIO_PIN_2,
        .ioremap = 0, /*olny PD2*/
        .time = TIM3,
        // .gpio_rcc = RCC_APB2_PERIPH_GPIOD,
        .irq_up = TIM3_IRQn,
        .info_str = "TIM3 PD2",
    },
#endif

#ifdef BSP_USING_TIM4_ETR_CNT
    {
        .gpio_grp = GPIOE,
        .pin = GPIO_PIN_0,
        .ioremap = 0, /*olny PE0*/
        .time = TIM4,
        // .gpio_rcc = RCC_APB2_PERIPH_GPIOE,
        .irq_up = TIM4_IRQn,
        .info_str = "TIM4 PE0",
    },
#endif

#ifdef BSP_USING_TIM8_ETR_CNT
#ifdef TIM8_ETR_PIN_PA0
    {
        .gpio_grp = GPIOA,
        .pin = GPIO_PIN_0,
        .ioremap = 0, /*[PA0=0,PB4=1,3]*/
        .time = TIM8,
        // .gpio_rcc = RCC_APB2_PERIPH_GPIOA,
        .irq_up = TIM8_UP_IRQn,
        .info_str = "TIM8 PA0",
    },
#endif
#ifdef TIM8_ETR_PIN_PB4
    {
        .gpio_grp = GPIOB,
        .pin = GPIO_PIN_4,
        .ioremap = GPIO_RMP1_TIM8, /*[PA0=0,PB4=1,3]*/
        .time = TIM8,
        // .gpio_rcc = RCC_APB2_PERIPH_GPIOB,
        .irq_up = TIM8_UP_IRQn,
        .info_str = "TIM8 PB4",
    },
#endif
#endif
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
#define N32L40X_CONFIG
#ifdef BSP_USING_TIM1_ETR_CNT
    {
        .gpio_grp = GPIOA,
        .pin = GPIO_PIN_12,
        .ioremap = GPIO_AF2_TIM1,
        .time = TIM1,
        .irq_up = TIM1_UP_IRQn,
        .info_str = "TIM1 PA12",
    },
#endif /*TIM1_ETR_PIN_PA0*/
#ifdef BSP_USING_TIM2_ETR_CNT
#ifdef TIM2_ETR_PIN_PA0
    {
        .gpio_grp = GPIOA,
        .pin = GPIO_PIN_0,
        .ioremap = GPIO_AF5_TIM2,
        .time = TIM2,
        .irq_up = TIM2_IRQn,
        .info_str = "TIM2 PA0",
    },
#endif /*TIM2_ETR_PIN_PA0*/
#ifdef TIM1_ETR_PIN_PA15
    {
        .gpio_grp = GPIOA,
        .pin = GPIO_PIN_15,
        .ioremap = GPIO_AF2_TIM2, 
        .time = TIM2,
        .irq_up = TIM2_IRQn,
        .info_str = "TIM2 PA15",
    },
#endif /*TIM2_ETR_PIN_PA15*/
#endif /*BSP_USING_TIM2_ETR_CNT*/ 
#ifdef BSP_USING_TIM3_ETR_CNT
    {
        .gpio_grp = GPIOD,
        .pin = GPIO_PIN_2,
        .ioremap = GPIO_AF2_TIM3,
        .time = TIM3,
        .irq_up = TIM3_IRQn,
        .info_str = "TIM3 PD2",
    },
#endif /*BSP_USING_TIM3_ETR_CNT*/
#ifdef BSP_USING_TIM9_ETR_CNT
    {
        .gpio_grp = GPIOB,
        .pin = GPIO_PIN_2,
        .ioremap = GPIO_AF1_TIM9,
        .time = TIM9,
        .irq_up = TIM9_IRQn,
        .info_str = "TIM9 PB2",
    },
#endif /*BSP_USING_TIM9_ETR_CNT*/


#endif /*SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X*/
};

// /*
//     定时器的时钟使能
//     time：定时器编号
// */
// void bsp_time_etr_cnt_rcc_en(TIM_Module *time)
// {

//     if (TIM1 == time)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
//     }
//     else if (TIM8 == time)
//     {
//         RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8, ENABLE);
//     }
//     else if (TIM2 == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
//     }
//     else if (TIM3 == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
//     }
//     else if (TIM4 == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
//     }
//     else if (TIM5 == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
//     }
//     else if (TIM6 == time)
//     {
//         RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);
//     }
//     LOG_D("%s", __FUNCTION__);
// }

/**
 * 中断相关初始化.
 */
static void bsp_time_count_nvic_etr_config(TIM_Module *time, uint32_t irq)
{
    NVIC_InitType NVIC_InitStructure;

    /* Enable the TIM1 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = irq;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ClrIntPendingBit(time, TIM_INT_UPDATE);  // 清除中断标志
    TIM_ConfigInt(time, TIM_INT_UPDATE, ENABLE); // 使能中断
    LOG_D("%s", __FUNCTION__);
}

/**
 * @brief 外部计数ETR计数配置
 *
 * @param  etr
 */
void bsp_time_etr_cnt_config(time_counter_etr_t *etr)
{
    // 使能 GPIOA 和 TIM1 时钟
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_TIM1, ENABLE);
    // 时钟
    // RCC_EnableAPB2PeriphClk(etr->gpio_rcc, ENABLE);
    n32_gpio_rcc_enable(etr->gpio_grp);
    n32_time_rcc_config(etr->time);
    uint32_t gpio_af; // 引脚复用功能
    GPIO_InitType GPIO_InitStructure;
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)

    // 配置 gpio 为浮空输入，用作外部触发输入
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin = etr->pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 配置为浮空输入GPIO_Mode_IN_FLOATING
    GPIO_InitPeripheral(etr->gpio_grp, &GPIO_InitStructure);
    // 引脚重映射
    if (etr->ioremap)
    {
        GPIO_ConfigPinRemap(etr->ioremap, ENABLE);
    }
    if (GPIOA == etr->gpio_grp && GPIO_PIN_15 == etr->pin)
    {
        GPIO_ConfigPinRemap(GPIO_RMP_SW_JTAG_SW_ENABLE, ENABLE); /*!< JTAG-DP Disabled and SW-DP Enabled */
    }
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin = etr->pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate = etr->ioremap;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_Slew_Rate_High;
    GPIO_InitPeripheral(etr->gpio_grp, &GPIO_InitStructure);
#endif

    // 配置 TIM1 为外部触发模式，使用 PA12 作为触发源
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.Prescaler = 0;             // 不分频
    TIM_TimeBaseStructure.Period = 0xFFFF;           // 最大计数值
    TIM_TimeBaseStructure.ClkDiv = TIM_CLK_DIV1;     // 无分频
    TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP; // 向上计数
    TIM_InitTimeBase(etr->time, &TIM_TimeBaseStructure);


    TIM_ConfigExtClkMode2(etr->time, TIM_EXT_TRG_PSC_OFF, TIM_EXT_TRIG_POLARITY_INVERTED, 1);

    // 配置外部触发模式，使用 ETR (PA12) 作为外部时钟源
    // TIM_ConfigExtClkMode1(etr->time, TIM_EXT_TRG_PSC_OFF, TIM_EXT_TRIG_POLARITY_NONINVERTED, 0);

    // 中断使能
    bsp_time_count_nvic_etr_config(etr->time, etr->irq_up);

    // 启动 TIM
    TIM_Enable(etr->time, ENABLE);
    LOG_D("%s", __FUNCTION__);
}

/*
    获取定时器计数值

*/
uint32_t bsp_timer_count_etr_get_count(time_counter_etr_t *ptime)
{
    uint32_t count;
    RT_ASSERT(ptime);

    // time_counter_etr_t *ptime = s_times_count_etr + id;
    count = ptime->over << 16 | TIM_GetCnt(ptime->time); // 溢出统计
    TIM_SetCnt(ptime->time, 0);                          // 清零
    ptime->over = 0;                                     // 清零

    return count;
}

// 定时器中断集中处理函数
static void bsp_time_count_etr_irq(time_counter_etr_t *ptime)
{
    rt_interrupt_enter(); // 进入中断
    if (TIM_GetIntStatus(ptime->time, TIM_INT_UPDATE) != RESET)
    {
        TIM_ClrIntPendingBit(ptime->time, TIM_INT_UPDATE);
        ptime->over++;
    }
    rt_interrupt_leave(); // 离开中断
}

#ifdef BSP_USING_TIM1_ETR_CNT
void TIM1_UP_IRQHandler(void)
{
    bsp_time_count_etr_irq(s_times_count_etr + TIME1_ETR);
}
#endif

#ifdef BSP_USING_TIM2_ETR_CNT
void TIM2_IRQHandler(void)
{
    bsp_time_count_etr_irq(s_times_count_etr + TIME2_ETR);
}
#endif

#ifdef BSP_USING_TIM3_ETR_CNT
void TIM3_IRQHandler(void)
{
    bsp_time_count_etr_irq(s_times_count_etr + TIME3_ETR);
}
#endif

#ifdef BSP_USING_TIM4_ETR_CNT
void TIM4_IRQHandler(void)
{
    bsp_time_count_etr_irq(s_times_count_etr + TIME4_ETR);
}
#endif

#ifdef BSP_USING_TIM8_ETR_CNT
void TIM8_UP_IRQHandler(void)
{
    bsp_time_count_etr_irq(s_times_count_etr + TIME8_ETR);
}
#endif
 #ifdef BSP_USING_TIM9_ETR_CNT
void TIM9_IRQHandler(void)
{
    bsp_time_count_etr_irq(s_times_count_etr + TIME9_ETR);
}
#endif
/**设备打开函数 */
static rt_err_t n32_tim_etr_cnt_open(rt_device_t dev, rt_uint16_t oflag)
{
    time_counter_etr_t *device = (time_counter_etr_t *)dev;
    bsp_time_etr_cnt_config(device);
    LOG_I("INIT ETR %s", device->info_str);
    return RT_EOK;
}
/**
 * @brief 外部计数ETR计数读，同时加入了溢出统计和读取后清除计数
 *
 * @param  dev
 * @param  pos
 * @param  buffer
 * @param  size
 * @return rt_ssize_t
 */
static rt_ssize_t n32_tim_etr_cnt_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    time_counter_etr_t *device = (time_counter_etr_t *)dev;
    rt_uint32_t *count_buf = (rt_uint32_t *)buffer;

    *count_buf = bsp_timer_count_etr_get_count(device);
    return sizeof(rt_uint32_t);
}
#ifdef RT_USING_DEVICE_OPS
/**设备操作函数接口 */
const struct rt_device_ops ops = {
    .init = RT_NULL,
    .open = n32_tim_etr_cnt_open,
    .close = RT_NULL,
    .write = RT_NULL,
    .control = RT_NULL,
    .read = n32_tim_etr_cnt_read,
};
#endif
static rt_err_t n32_tim_ert_cnt_register(time_counter_etr_t *device,
                                         const char *name)
{
    RT_ASSERT(device != RT_NULL);
    device->parent.type = RT_Device_Class_Miscellaneous; // 杂项设备
#ifdef RT_USING_DEVICE_OPS
    device->parent.ops = &ops;
#else
    device->parent.init = RT_NULL;
    device->parent.open = n32_tim_etr_cnt_open;
    device->parent.close = RT_NULL;
    device->parent.read = n32_tim_etr_cnt_read;
    device->parent.write = RT_NULL;
    device->parent.control = RT_NULL;
    device->parent.user_data = device;
#endif

    return rt_device_register(&device->parent, name, RT_DEVICE_FLAG_RDONLY);
}

// 一键初始化所有定时器
int bsp_timer_count_etr_all_init(void)
{
    int num = sizeof(s_times_count_etr) / sizeof(time_counter_etr_t);
    for (int i = 0; i < num; i++)
    {
        rt_memset(s_times_count_etr[i].name, 0, RT_NAME_MAX);
        rt_snprintf(s_times_count_etr[i].name, RT_NAME_MAX, "etr%d", i);
        if (RT_EOK == n32_tim_ert_cnt_register(s_times_count_etr + i, s_times_count_etr[i].name))
        {
            LOG_I("regiter ETR cnt name = %s is ok time=  %s", s_times_count_etr[i].name, s_times_count_etr[i].info_str);
        }
        else
        {
            LOG_W("regiter ETR cnt %s is fail time=  %s ", s_times_count_etr[i].name, s_times_count_etr[i].info_str);
        }
    }
    return 0;
}

INIT_DEVICE_EXPORT(bsp_timer_count_etr_all_init);

/*************************************shell 中断指令用于测试*************************************************************** */
#ifdef RT_USING_FINSH
#include <stdlib.h>
#include <string.h>
#include <finsh.h>

enum pwm_list_parameters
{
    ETR_LIST_PROBE = 1,
    ETR_LIST_GET,
};

CMD_OPTIONS_STATEMENT(etr_list)

static int etr_list(int argc, char **argv)
{
    rt_err_t result = -RT_ERROR;
    char *result_str;
    static rt_device_t device= RT_NULL;
    int arg2 = 0;
    uint32_t count = 0;
    if (argc > 1)
    {
        if (MSH_OPT_ID_GET(etr_list) == ETR_LIST_PROBE)
        {
            if (argc == 3)
            {
                device =  rt_device_find(argv[2]);
                if (device)
                {
                    rt_device_open(device, 0);
                }
                result_str = (device == RT_NULL) ? "failure" : "success";
                rt_kprintf("probe %s %s\n", argv[2], result_str);
                return (device == RT_NULL) ? -RT_ERROR : RT_EOK;
            }
            else
            {
                rt_kprintf("etr probe <device name>                  - probe etr by name\n");
                return -RT_EINVAL;
            }
        }
        else if (device == RT_NULL)
        {
            rt_kprintf("Please using 'etr probe <device name>' first.\n");
            return -RT_ERROR;
        }

        switch (MSH_OPT_ID_GET(etr_list))
        {

        case ETR_LIST_GET:
            // arg2 = atoi(argv[2]);
            rt_device_read(device, 0, &count, sizeof(count));
            // count = bsp_timer_count_etr_get_count(device);
            rt_kprintf("Info of device count=  [%d]:\n", count);
            return RT_EOK;

            break;

        default:
            goto _usage;
        }
    }
    else
    {
        goto _usage;
    }
    return result;

_usage:
    rt_kprintf("Usage: \n");
    rt_kprintf("etr probe      <device name>                - probe etr by name\n");
    rt_kprintf("etr get                           - get etr cnt info\n");

    result = -RT_ERROR;
    return result;
}
CMD_OPTIONS_NODE_START(etr_list)
CMD_OPTIONS_NODE(ETR_LIST_PROBE, probe, probe etr name)
CMD_OPTIONS_NODE(ETR_LIST_GET, get, get etr count)
CMD_OPTIONS_NODE_END
MSH_CMD_EXPORT_ALIAS(etr_list, etr, control etr device, optenable);

#endif /* RT_USING_FINSH */

#ifdef BSP_USING_TIM_ETR_CNT_DEMO  // demo
#define ETR_DEV_NAME "etr2"

static rt_mailbox_t mb_etr;
static void timout_etr(void *parameter)
{
    uint32_t count = 0;
    rt_device_t etr_dev = (rt_device_t)parameter;
    rt_device_read(etr_dev, 0, &count, sizeof(count));
    rt_mb_send_wait(mb_etr,count,0);
}
static void thd_entry_etr(void *parameter)
{
    uint32_t value = 0;
    while (1)
    {
        if (RT_EOK == rt_mb_recv(mb_etr, &value, RT_WAITING_FOREVER))
        {
            LOG_I("ETR CNT %d", value);
        }
    }
}
static int extr_app_demo(void)
{
    static rt_device_t etr_dev = RT_NULL;
    etr_dev = rt_device_find(ETR_DEV_NAME);
    if (etr_dev)
    {
        rt_device_open(etr_dev, 0);
    }
    else
    {
        LOG_W("ETR device not find");
    }
    mb_etr = rt_mb_create(ETR_DEV_NAME, 5, RT_IPC_FLAG_FIFO);
    RT_ASSERT(mb_etr);
    rt_thread_t thd_etr = rt_thread_create(ETR_DEV_NAME, thd_entry_etr, etr_dev, 512, 20, 5);
    RT_ASSERT(thd_etr);
    rt_thread_startup(thd_etr);
    rt_timer_t timer = rt_timer_create(ETR_DEV_NAME, timout_etr, etr_dev, 1000, RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_HARD_TIMER);
    RT_ASSERT(timer);
    rt_timer_start(timer);
    return RT_EOK;
}
INIT_APP_EXPORT(extr_app_demo);
#endif /* BSP_USING_TIM_ETR_CNT_DEMO */
/*************************************shell 中断指令用于测试*************************************************************** */

#endif /**BSP_USING_TIM_ETR_CNT */
