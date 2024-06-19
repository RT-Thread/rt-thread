/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-17     QT-one       first version
 */

#include "board.h"

#ifdef BSP_USING_TEST

/* Task stack */
#define THREAD_PRIORITY             25
#define THREAD_STACK_SIZE           512
#define THREAD_TIMESLICE            5

/* Test pins */
#define TEST_LED0_PIN               GET_PIN(C, 14)
#define TEST_LED1_PIN               GET_PIN(C, 15)
#define TEST_LED2_PIN               GET_PIN(C, 1)

#define TEST_WAKEUP_PIN             GET_PIN(B, 12)
#define TEST_KEY1_PIN               GET_PIN(D, 1)
#define TEST_KEY2_PIN               GET_PIN(D, 2)

#define TEST_OTHER_PIN              GET_PIN(B, 12)
#define TEST_OUTPUT_PIN             GET_PIN(C, 1)

#define TEST_INPUT_PIN              GET_PIN(D, 1)
#define TEST_INT_PIN                GET_PIN(D, 2)
#define TEST_RES_PIN                GET_PIN(C, 1)


/* Event flags */
#define TEST_GPIO_INT_ENV           (1 << 10)
#define TEST_GPIO_KEY_ENV           (1 << 15)
static struct rt_event              led_event;  /* LED event */
#define TASK_KILL_FLAG              (1 << 10)
static struct rt_event              task_event; /* Task event */

/* EEPROM Read/Write Data Structure */
typedef union
{
    rt_uint8_t data[30];
    struct
    {
        rt_uint8_t write_addr;
        char write_date[29];
    }in_data;
}eeprom_write_type;
/* Semaphore variables */
static struct rt_semaphore rx_sem;

/* Mutually exclusive variables */
static rt_mutex_t task_mutex = RT_NULL; /* task mutex */

/* device handle */
static rt_device_t serial;
static rt_device_t wdt_dev;
struct rt_i2c_bus_device *i2c_dev;
static struct rt_spi_device *spi_dev;

/* In-file function declarations */
static void sys_run_dir(void *parameter);
static void gpio_output_test(void *parameter);
static void gpio_input_test(void *parameter);
static void key_iqr_handle(void *args);

/* Task registration */
int task_registration(void)
{
    /* Create a dynamic mutex */
    task_mutex = rt_mutex_create("task_mutex", RT_IPC_FLAG_FIFO);
    if (task_mutex == RT_NULL)
    {
        rt_kprintf("rt_mutex_create error.\n");
        return -1;
    }
    /* Create a task event */
    if(rt_event_init(&task_event,"task_event",RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        rt_kprintf("rt_mutex_create error.\n");
        return -1;
    }
    return 0;
}
INIT_BOARD_EXPORT(task_registration);

/* System operation indicator */
static void sys_run_dir(void *parameter)
{
    rt_uint32_t e;
    rt_pin_mode(TEST_LED2_PIN, PIN_MODE_OUTPUT);
    while(1)
    {
        if(rt_event_recv(&task_event,TASK_KILL_FLAG,
                        RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                        RT_WAITING_NO, &e) == RT_EOK)
        {
            rt_thread_t tid = rt_thread_self();
            rt_thread_delete(tid);
        }
        rt_pin_write(TEST_LED2_PIN, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(TEST_LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
    }
}

static int sys_run_task(int argc, char *argv[])
{
    if(argc == 2)
    {
        if(rt_strcmp(argv[1],"start") == 0)
        {
            if(rt_mutex_take(task_mutex, RT_WAITING_NO) != RT_EOK)
            {
                rt_kprintf("The test thread is occupied.\n");
                return -RT_ERROR;
            }
            else
            {
                /* Register the system indicator task */
                rt_thread_t sys_led_task = rt_thread_create("sys_led_task",
                                                sys_run_dir, RT_NULL,
                                                THREAD_STACK_SIZE,
                                                THREAD_PRIORITY, THREAD_TIMESLICE);
                if (sys_led_task != RT_NULL)
                    rt_thread_startup(sys_led_task);
                rt_kprintf("The sys run task is registered.\n");
            }
        }
        else if(rt_strcmp(argv[1],"end") == 0)
        {
            rt_event_send(&task_event,TASK_KILL_FLAG);
            rt_mutex_release(task_mutex);
            rt_kprintf("The sys run task has been deleted.\n");
        }
    }
    else
    {
        rt_kprintf("Necessary parameters are missing.\n");
        rt_kprintf("You can use the following commands.\n");
        rt_kprintf("%s start\n",__func__);
        rt_kprintf("%s end\n",__func__);
        return -1;
    }
    return -1;
}
MSH_CMD_EXPORT(sys_run_task, sys run task operation);

/* Gpio output test */
static void gpio_output_test(void *parameter)
{
    rt_uint32_t e;
    rt_pin_mode(TEST_OUTPUT_PIN, PIN_MODE_OUTPUT);
    while(1)
    {
        if(rt_event_recv(&task_event,TASK_KILL_FLAG,
                        RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                        RT_WAITING_NO, &e) == RT_EOK)
        {
            rt_thread_t tid = rt_thread_self();
            rt_thread_delete(tid);
        }
        rt_pin_write(TEST_OUTPUT_PIN, PIN_LOW);
        rt_thread_mdelay(500);
        rt_pin_write(TEST_OUTPUT_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
    }
}

static int gpio_output_task(int argc, char *argv[])
{
    if(argc == 2)
    {
        if(rt_strcmp(argv[1],"start") == 0)
        {
            if(rt_mutex_take(task_mutex, RT_WAITING_NO) != RT_EOK)
            {
                rt_kprintf("The test thread is occupied.\n");
                return -RT_ERROR;
            }
            else
            {
                /* Gpio output test tasks */
                rt_thread_t gpio_output_task = rt_thread_create("gpio_output_task",
                                                gpio_output_test, RT_NULL,
                                                THREAD_STACK_SIZE,
                                                THREAD_PRIORITY, THREAD_TIMESLICE);
                if (gpio_output_task != RT_NULL)
                    rt_thread_startup(gpio_output_task);
                rt_kprintf("The gpio output task is registered.\n");
            }
        }
        else if(rt_strcmp(argv[1],"end") == 0)
        {
            rt_event_send(&task_event,TASK_KILL_FLAG);
            rt_mutex_release(task_mutex);
            rt_kprintf("The gpio output task has been deleted.\n");
        }
    }
    else
    {
        rt_kprintf("Necessary parameters are missing.\n");
        rt_kprintf("You can use the following commands.\n");
        rt_kprintf("%s start\n",__func__);
        rt_kprintf("%s end\n",__func__);
        return -1;
    }
    return -1;
}
MSH_CMD_EXPORT(gpio_output_task, gpio output task operation);
/* Gpio input test */
static void key_iqr_handle(void *args)
{
    /* gpio iqr fun */
    rt_event_send(&led_event,TEST_GPIO_INT_ENV);
}

static void gpio_input_test(void *parameter)
{
    uint8_t led_flag = PIN_LOW;
    rt_uint32_t e;

    rt_pin_mode(TEST_RES_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(TEST_RES_PIN, PIN_LOW);

    rt_pin_mode(TEST_WAKEUP_PIN,PIN_MODE_INPUT_PULLDOWN);
    rt_pin_mode(TEST_INPUT_PIN,PIN_MODE_INPUT_PULLUP);

    rt_pin_attach_irq(TEST_INT_PIN,PIN_IRQ_MODE_FALLING,key_iqr_handle,RT_NULL);
    rt_pin_irq_enable(TEST_INT_PIN,PIN_IRQ_ENABLE);

    if(rt_event_init(&led_event,"led_event",RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        rt_kprintf("rt_mutex_create error.\n");
    }
    while(1)
    {
        if(PIN_LOW == rt_pin_read(TEST_INPUT_PIN))
        {
            while(PIN_LOW == rt_pin_read(TEST_INPUT_PIN));
            rt_event_send(&led_event,TEST_GPIO_KEY_ENV);
        }
        if(rt_event_recv(&led_event,(TEST_GPIO_INT_ENV|TEST_GPIO_KEY_ENV),
                        RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                        RT_WAITING_NO, &e) == RT_EOK)
        {
            led_flag = (led_flag == PIN_LOW)?PIN_HIGH:PIN_LOW;
            rt_pin_write(TEST_RES_PIN, led_flag);
        }
        if(rt_event_recv(&task_event,TASK_KILL_FLAG,
                        RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
                        RT_WAITING_NO, &e) == RT_EOK)
        {
            rt_thread_t tid = rt_thread_self();
            rt_thread_delete(tid);
        }
    }
}

static int gpio_input_task(int argc, char *argv[])
{
    if(argc == 2)
    {
        if(rt_strcmp(argv[1],"start") == 0)
        {
            if(rt_mutex_take(task_mutex, RT_WAITING_NO) != RT_EOK)
            {
                rt_kprintf("The test thread is occupied.\n");
                return -RT_ERROR;
            }
            /* Gpio input test tasks */
            rt_thread_t gpio_input_task = rt_thread_create("gpio_input_task",
                                            gpio_input_test, RT_NULL,
                                            THREAD_STACK_SIZE,
                                            THREAD_PRIORITY, THREAD_TIMESLICE);
            if (gpio_input_task != RT_NULL)
                rt_thread_startup(gpio_input_task);
            rt_kprintf("The gpio input task is registered.\n");
        }
        else if(rt_strcmp(argv[1],"end") == 0)
        {
            rt_event_send(&task_event,TASK_KILL_FLAG);
            rt_mutex_release(task_mutex);
            rt_kprintf("The gpio input task has been deleted.\n");
        }
    }
    else
    {
        rt_kprintf("Necessary parameters are missing.\n");
        rt_kprintf("You can use the following commands.\n");
        rt_kprintf("%s start\n",__func__);
        rt_kprintf("%s end\n",__func__);
        return -1;
    }
    return -1;
}
MSH_CMD_EXPORT(gpio_input_task, gpio input task operation);
/* uart test */
static rt_err_t uart_iqr_handle(rt_device_t dev, rt_size_t size)
{
    /* Serial port callback function */
    rt_sem_release(&rx_sem);
    return RT_EOK;
}

static void uart_thread(void *parameter)
{
    char ch;
    while (1)
    {
        /* Serial port readout */
        while (rt_device_read(serial, -1, &ch, 1) != 1)
        {
            /* semaphore blocking */
            rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        }
        /* Output the data obtained from the serial port */
        rt_device_write(serial, 0, &ch, 1);
        rt_device_write(serial,0,"\n",1);
    }
}

static int uart_task(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;

    char uart_name[RT_NAME_MAX] = "uart1";
    char str[] = "hello RT-Thread!\r\n";
    if (argc == 3)
    {
        if(rt_strcmp(argv[2],"start") == 0)
        {
            rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
        }
        else
        {
            rt_kprintf("Necessary parameters are missing.\n");
            rt_kprintf("You can use the following commands.\n");
            rt_kprintf("%s <uart name> start\n",__func__);
            rt_kprintf("%s <uart name> end\n",__func__);
            return -1;
        }
    }
    else if(argc == 2)
    {
        if(rt_strcmp(argv[1],"start") == 0)
        {
        }
        else
        {
            rt_kprintf("Necessary parameters are missing.\n");
            rt_kprintf("You can use the following commands.\n");
            rt_kprintf("%s start\n",__func__);
            rt_kprintf("%s end\n",__func__);
            return -1;
        }
    }
    else
    {
        rt_kprintf("Incomplete instruction.\n");
        rt_kprintf("You can use the following commands.\n");
        rt_kprintf("%s <uart name> start/end\n",__func__);
        rt_kprintf("or\n");
        rt_kprintf("%s start/end\n",__func__);
        return -1;
    }
    /* Find Serial Devices */
    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return -RT_ERROR;
    }
    /* Initializing a Signal */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    /* Open the serial device with read/write and interrupt reception. */
    rt_device_open(serial, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    /* Setting the receive callback function */
    rt_device_set_rx_indicate(serial, uart_iqr_handle);
    /* Send String */
    rt_device_write(serial, 0, str, (sizeof(str) - 1));
    /* Creating a serial thread */
    rt_thread_t thread = rt_thread_create("serial",
                                        uart_thread, RT_NULL,
                                        THREAD_STACK_SIZE,
                                        THREAD_PRIORITY, THREAD_TIMESLICE);
    if (thread != RT_NULL)
        rt_thread_startup(thread);

    return ret;
}
MSH_CMD_EXPORT(uart_task, uart device sample);
/* hw/sw iic test */
static void i2c_thread(void *parameter)
{
    uint8_t write_addr = 0x00;
    eeprom_write_type eeprom_date;
    char send_dat[] = "i2c write eeprom";
    char read_dat[20] = {0};
    struct rt_i2c_msg msg1[2];

    eeprom_date.in_data.write_addr = write_addr;
    rt_strncpy(eeprom_date.in_data.write_date, send_dat, rt_strlen(send_dat));

    msg1[0].addr = 0x51;
    msg1[0].flags = RT_I2C_WR;
    msg1[0].buf = eeprom_date.data;
    msg1[0].len = (rt_strlen(send_dat) + 1);
    if (rt_i2c_transfer(i2c_dev, msg1, 1) == 1)
    {
        rt_kprintf("eeprom write succeed!\n");
        rt_kprintf("write_dat = %s\r\n",send_dat);
    }
    else
    {
        rt_kprintf("eeprom write error!\n");
    }
    msg1[0].addr = 0x51;
    msg1[0].flags = RT_I2C_WR;
    msg1[0].buf = &write_addr;
    msg1[0].len = 1;

    msg1[1].addr = 0x51;
    msg1[1].flags = RT_I2C_RD;
    msg1[1].buf = (uint8_t *)read_dat;
    msg1[1].len = rt_strlen(send_dat);

    if (rt_i2c_transfer(i2c_dev, msg1, 2) == 2)
    {
        rt_kprintf("eeprom read succeed!\n");
        rt_kprintf("read_dat = %s\r\n",read_dat);
    }
    else
    {
        rt_kprintf("eeprom read error!\n");
    }
}

static int i2c_task(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;

    char i2c_name[RT_NAME_MAX] = "hw_i2c1";
    if (argc == 3)
    {
        if(rt_strcmp(argv[2],"start") == 0)
        {
            rt_strncpy(i2c_name, argv[1], RT_NAME_MAX);
        }
        else
        {
            rt_kprintf("Necessary parameters are missing.\n");
            rt_kprintf("You can use the following commands.\n");
            rt_kprintf("%s <i2c name> start\n",__func__);
            rt_kprintf("%s <i2c name> end\n",__func__);
            return -1;
        }
    }
    else if(argc == 2)
    {
        if(rt_strcmp(argv[1],"start") == 0)
        {
        }
        else
        {
            rt_kprintf("Necessary parameters are missing.\n");
            rt_kprintf("You can use the following commands.\n");
            rt_kprintf("%s start\n",__func__);
            rt_kprintf("%s end\n",__func__);
            return -1;
        }
    }
    else
    {
        rt_kprintf("Incomplete instruction.\n");
        rt_kprintf("You can use the following commands.\n");
        rt_kprintf("%s <i2c name> start/end\n",__func__);
        rt_kprintf("or\n");
        rt_kprintf("%s start/end\n",__func__);
        return -1;
    }
    /* Find I2C Devices */
    i2c_dev = (struct rt_i2c_bus_device *)rt_device_find(i2c_name);
    if (!i2c_dev)
    {
        rt_kprintf("find %s failed!\n", i2c_name);
        return -RT_ERROR;
    }
    /* Execute I2C read/write eeprom function */
    i2c_thread(RT_NULL);
    return ret;
}
MSH_CMD_EXPORT(i2c_task, i2c device sample);
/* spi test */
static void spi_thread(void *parameter)
{
    rt_uint8_t w25x_read_id = 0x9F;
    rt_uint8_t id[5] = {0};

    /* Use rt_spi_send_then_recv() to send commands to read IDs */
    rt_spi_take_bus(spi_dev);
    rt_spi_take(spi_dev);
    rt_spi_send_then_recv(spi_dev, &w25x_read_id, 1, id, 3);
    rt_spi_release(spi_dev);
    rt_spi_release_bus(spi_dev);
    rt_kprintf("use rt_spi_send_then_recv() read MX25L6406 ID is:0x%X%X%X\n", id[0], id[1], id[2]);
}

static int spi_task(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    struct rt_spi_configuration cfg;
    char spi_name[RT_NAME_MAX] = "spi1";
    char flash_name[RT_NAME_MAX] = "flash";

    if (argc == 3)
    {
        if(rt_strcmp(argv[2],"start") == 0)
        {
            rt_strncpy(spi_name, argv[1], RT_NAME_MAX);
        }
        else
        {
            rt_kprintf("Necessary parameters are missing.\n");
            rt_kprintf("You can use the following commands.\n");
            rt_kprintf("%s <spi name> start\n",__func__);
            rt_kprintf("%s <spi name> end\n",__func__);
            return -1;
        }
    }
    else if(argc == 2)
    {
        if(rt_strcmp(argv[1],"start") == 0)
        {
        }
        else
        {
            rt_kprintf("Necessary parameters are missing.\n");
            rt_kprintf("You can use the following commands.\n");
            rt_kprintf("%s start\n",__func__);
            rt_kprintf("%s end\n",__func__);
            return -1;
        }
    }
    else
    {
        rt_kprintf("Incomplete instruction.\n");
        rt_kprintf("You can use the following commands.\n");
        rt_kprintf("%s <spi name> start/end\n",__func__);
        rt_kprintf("or\n");
        rt_kprintf("%s start/end\n",__func__);
        return -1;
    }
    /* Binding CS pin */
    ret = rt_hw_spi_device_attach(spi_name,flash_name,HT_GPIOD,GPIO_PIN_0);
    if(ret != RT_EOK)
    {
        rt_kprintf("Failed CS pin binding for %s!\n", spi_name);
        return -RT_ERROR;
    }
    /* Find flash devices */
    spi_dev = (struct rt_spi_device*)rt_device_find(flash_name);
    if (!spi_dev)
    {
        rt_kprintf("find %s failed!\n", spi_name);
        return -RT_ERROR;
    }
    /* Configuring the SPI Bus */
    cfg.data_width = 8;
    cfg.mode = RT_SPI_MASTER | RT_SPI_MODE_3 | RT_SPI_MSB;
    cfg.max_hz = 8;
    rt_spi_configure(spi_dev,&cfg);
    rt_kprintf("SPI0 initialization succeeded!\n");

    /* Execute flash read and write functions */
    spi_thread(RT_NULL);
    rt_device_unregister((rt_device_t)spi_dev);
    return ret;
}
MSH_CMD_EXPORT(spi_task, spi device sample);
/* adc test */
static void adc_test(void *parameter)
{
    rt_uint32_t adc0_ch6_val,adc0_ch7_val;
    rt_adc_device_t adc_dev = (rt_adc_device_t)rt_device_find("adc0");
    if (!adc_dev)
    {
        rt_kprintf("No ADC0 device found!\n");
    }
    else
    {
        rt_adc_enable(adc_dev,ADC_CH_6);
        rt_adc_enable(adc_dev,ADC_CH_7);
    }
    while(1)
    {
        adc0_ch6_val = rt_adc_read(adc_dev,6);
        adc0_ch7_val = rt_adc_read(adc_dev,7);
        rt_kprintf("adc0_ch6_val = %d\n",adc0_ch6_val);
        rt_kprintf("adc0_ch7_val = %d\n",adc0_ch7_val);
        rt_thread_mdelay(50);
    }
}

static int adc_task(int argc, char *argv[])
{
    if(argc == 2)
    {
        if(rt_strcmp(argv[1],"start") == 0)
        {
            /* Adc test tasks */
            rt_thread_t adc_task = rt_thread_create("adc_task",
                                            adc_test, RT_NULL,
                                            THREAD_STACK_SIZE,
                                            THREAD_PRIORITY, THREAD_TIMESLICE);
            if (adc_task != RT_NULL)
                rt_thread_startup(adc_task);
            rt_kprintf("The adc task is registered.\n");
        }
        else if(rt_strcmp(argv[1],"end") == 0)
        {
            rt_event_send(&task_event,TASK_KILL_FLAG);
            rt_kprintf("The adc task has been deleted.\n");
        }
    }
    else
    {
        rt_kprintf("Necessary parameters are missing.\n");
        rt_kprintf("You can use the following commands.\n");
        rt_kprintf("%s start\n",__func__);
        rt_kprintf("%s end\n",__func__);
        return -1;
    }
    return -1;
}
MSH_CMD_EXPORT(adc_task, adc task operation);

/* wdt test */
static void wdt_test(void)
{
    rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
}

static int wdt_task(int argc, char *argv[])
{
    rt_err_t ret = -RT_ERROR;
    rt_uint16_t wdt_time = 5;
    char dev_name[] = "wdt";
    if(argc == 2)
    {
        if(rt_strcmp(argv[1],"start") == 0)
        {
            /* Find wdt devices */
            wdt_dev = rt_device_find(dev_name);
            if(wdt_dev == RT_NULL)
            {
                rt_kprintf("No corresponding equipment found.\n");
                return -1;
            }
            /* Configuring the Watchdog */
            ret = rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &wdt_time);
            if(ret != RT_EOK)
            {
                rt_kprintf("wdt configuration failed.\n");
                return -1;
            }
            /* Start the Watchdog */
            ret = rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
            if(ret != RT_EOK)
            {
                rt_kprintf("wdt start failed.\n");
                return -1;
            }
            /* Setting up idle threads */
            rt_thread_idle_sethook(wdt_test);
            rt_kprintf("Watchdog started successfully.\n");
        }
        else if(rt_strcmp(argv[1],"stop") == 0)
        {
            /* Verify device handle */
            if(wdt_dev == RT_NULL)
            {
                rt_kprintf("Device handle does not exist.\n");
                return -1;
            }
            /* Stop the Watchdog */
            ret = rt_device_control(wdt_dev, RT_DEVICE_CTRL_WDT_STOP, RT_NULL);
            if(ret != RT_EOK)
            {
                rt_kprintf("wdt start failed.\n");
                return -1;
            }
            /* Hook function to delete idle threads */
            rt_thread_idle_delhook(wdt_test);
            rt_kprintf("Watchdog has stopped.\n");
        }
    }
    else
    {
        rt_kprintf("Necessary parameters are missing.\n");
        rt_kprintf("You can use the following commands.\n");
        rt_kprintf("%s start\n",__func__);
        rt_kprintf("%s stop\n",__func__);
        return -1;
    }
    return -1;
}
MSH_CMD_EXPORT(wdt_task, wdt task operation);

#endif /* BSP_USING_TEST */
