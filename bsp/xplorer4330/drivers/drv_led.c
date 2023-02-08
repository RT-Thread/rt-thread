#include <rtthread.h>
#include "board.h"
#include "drv_led.h"


/**
*
* LED1 <==> GPIO1[11]
* LED2 <==> GPIO1[12]
*
**/

#define LED_NUM    2

#define LED1_PIN   11
#define LED1_PORT  1

#define LED2_PIN   12
#define LED2_PORT  1

struct led_ctrl
{
    uint8_t num;
    uint8_t port;
};

struct lpc_led
{
    /* inherit from rt_device */
    struct rt_device parent;

    struct led_ctrl ctrl[LED_NUM];
};

static struct lpc_led led;

static rt_err_t rt_led_init(rt_device_t dev)
{
    /* Enable clock and init GPIO outputs */
    LPC_CCU1->CLK_M4_GPIO_CFG  = CCU_CLK_CFG_AUTO | CCU_CLK_CFG_RUN;
    while (!(LPC_CCU1->CLK_M4_GPIO_STAT & CCU_CLK_STAT_RUN));

    /* set GPIO1[11] GPIO1[12] as GPIO. */
    LPC_SCU->SFSP2_11  =  0;                              /* GPIO1[11]          */
    LPC_SCU->SFSP2_12  =  0;                              /* GPIO1[12]          */
    /* set GPIO1[11]  GPIO1[12]  output. */
    LPC_GPIO_PORT->DIR[LED1_PORT] |= 0x01 << LED1_PIN;
    LPC_GPIO_PORT->DIR[LED2_PORT] |= 0x01 << LED2_PIN;
    /* turn off all the led */
    LPC_GPIO_PORT->SET[LED1_PORT] |= 0x01 << LED1_PIN;
    LPC_GPIO_PORT->SET[LED2_PORT] |= 0x01 << LED2_PIN;


    led.ctrl[0].num = LED1_PIN;
    led.ctrl[0].port = LED1_PORT;
    led.ctrl[1].num = LED2_PIN;
    led.ctrl[1].port = LED2_PORT;

    return RT_EOK;
}

static rt_err_t rt_led_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_led_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t rt_led_read(rt_device_t dev, rt_off_t pos, void *buffer,
                             rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nr = size;
    rt_uint8_t *value = buffer;

    RT_ASSERT(dev == &led.parent);
    RT_ASSERT((pos + size) <= LED_NUM);

    for (index = 0; index < nr; index++)
    {
        if ((LPC_GPIO_PORT->PIN[led.ctrl[pos + index].port] & (1 << led.ctrl[pos + index].num)) != 0)
        {
            *value = 0;
        }
        else
        {
            *value = 1;
        }
        value++;
    }
    return index;
}

static rt_ssize_t rt_led_write(rt_device_t dev, rt_off_t pos,
                              const void *buffer, rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nw = size;
    const rt_uint8_t *value = buffer;

    RT_ASSERT(dev == &led.parent);
    RT_ASSERT((pos + size) <= LED_NUM);

    for (index = 0; index < nw; index++)
    {
        if (*value++)
        {
            LPC_GPIO_PORT->CLR[led.ctrl[pos + index].port] = (1 << led.ctrl[pos + index].num);
        }
        else
        {
            LPC_GPIO_PORT->SET[led.ctrl[pos + index].port] = (1 << led.ctrl[pos + index].num);
        }
    }
    return index;
}

static rt_err_t rt_led_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev == &led.parent);

    if (cmd == LED_DEVICE_CTRL)
    {
        rt_uint32_t *led_num = args;
        *led_num = LED_NUM;
    }
    return RT_EOK;
}

int rt_led_hw_init(void)
{
    led.parent.type         = RT_Device_Class_Char;
    led.parent.rx_indicate  = RT_NULL;
    led.parent.tx_complete  = RT_NULL;
    led.parent.init         = rt_led_init;
    led.parent.open         = rt_led_open;
    led.parent.close        = rt_led_close;
    led.parent.read         = rt_led_read;
    led.parent.write        = rt_led_write;
    led.parent.control      = rt_led_control;
    led.parent.user_data    = RT_NULL;

    /* register a character device */
    rt_device_register(&led.parent, "led", RT_DEVICE_FLAG_RDWR);
    /* init led device */
    rt_led_init(&led.parent);
    return 0;
}
INIT_DEVICE_EXPORT(rt_led_hw_init);

#ifdef RT_USING_FINSH
#include <finsh.h>
void led_test(rt_uint32_t led_num, rt_uint32_t value)
{
    rt_uint8_t led_value = value;
    rt_led_write(&led.parent, led_num, &led_value, 1);
}
FINSH_FUNCTION_EXPORT(led_test, e.g: led_test(0, 100).)
#endif
