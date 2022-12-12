# HWTIMER Device


## Introduction to the Timer

Hardware timers generally have two modes of operation, timer mode and counter mode. No matter which mode is operated, it works by counting the pulse signal counted by the internal counter module. Here are some important concepts of timers.

**Timer mode**: Counts the internal pulse. Timers are often used as timing clocks for timing detection, timing response, and timing control.

**Counter mode**: The counter can count up or down. The maximum count value of a 16-bit counter is 65535, and the maximum value of a 32-bit counter is 4 294 967 295.

**Counting frequency**：Since the input frequency is usually fixed, the time it takes for the counter to reach its desired count number can be calculated from just the given frequency - `time = count value / count frequency`. For example, if the counting frequency is 1 MHz, the counter counts once every 1 / 1000000 seconds. That is, every 1 microsecond, the counter is incremented by one (or subtracted by one), at this time, the maximum timing capability of the 16-bit counter is 65535 microseconds, or 65.535 milliseconds.

## Access Hardware Timer Device

The application accesses the hardware timer device through the I/O device management interface provided by RT-Thread. The related interfaces are as follows:

| **Function** | **Description**                |
| -------------------- | ---------------------------------- |
| rt_device_find()  | to look up the timer device |
| rt_device_open()     | to open the timer device in read-write mode |
| rt_device_set_rx_indicate()   | to set the timeout callback function |
| rt_device_control()  | to control the timer device, you can set the timing mode (single time /cycle),counting frequency, or stop the timer |
| rt_device_write()  | to set the timeout value of the timer. The timer then starts |
| rt_device_read()  | to get the current value of the timer |
| rt_device_close()  | to turn off the timer device. |

### Find Timer Device

The application obtains the device handle based on the hardware timer device name, and thus can operate the hardware timer device. The device function is as follows:

```c
rt_device_t rt_device_find(const char* name);
```

| Parameter | **Description**                 |
| -------- | ---------------------------------- |
| name     | hardware timer device name |
| **return** | ——                                 |
| timer device handle | will return to the corresponding device handle if the corresponding device is found |
| RT_NULL  | No device found |

In general, the hardware timer device name registered to the system is timer0, timer1, etc. The usage examples are as follows:

```c
#define HWTIMER_DEV_NAME   "timer0"     /* timer name */
rt_device_t hw_dev;                     /* timer device handle */
/* find timer device */
hw_dev = rt_device_find(HWTIMER_DEV_NAME);
```

### Open Timer Device

With the device handle, the application can open the device. When the device is open, it will detect whether the device has been initialized. If it is not initialized, it will call the initialization interface to initialize the device by default. Open the device with the following function:

```c
rt_err_t rt_device_open(rt_device_t dev, rt_uint16_t oflags);
```

| Parameter | Description              |
| ---------- | ------------------------------- |
| dev        | hardware timer device handle |
| oflags     | device open mode, is generally opened in read and write mode, which is to take the value：RT_DEVICE_OFLAG_RDWR |
| **return** | ——                             |
| RT_EOK     | device opened successfully |
| other error code | device fail to open |

An example of use is as follows:

```c
#define HWTIMER_DEV_NAME   "timer0"     /* timer name */
rt_device_t hw_dev;                     /* timer device handle */
/* find timer device */
hw_dev = rt_device_find(HWTIMER_DEV_NAME);
/* to open the timer device in read-write mode */
rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
```

### Set the Timeout Callback Function

Set the timer timeout callback function with the following function - this is the function that will be called when the timer reaches its set count value:

```c
rt_err_t rt_device_set_rx_indicate(rt_device_t dev, rt_err_t (*rx_ind)(rt_device_t dev, rt_size_t size))
```

| Parameter | **Description**               |
| ---------- | ------------------------------- |
| dev        | device handle           |
| rx_ind     | timeout callback function, provided by the caller |
| **return** | ——                             |
| RT_EOK     | success          |

An example of use is as follows：

```c
#define HWTIMER_DEV_NAME   "timer0"     /* timer name */
rt_device_t hw_dev;                     /* timer device handle */

/* timer timeout callback function */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int hwtimer_sample(int argc, char *argv[])
{
    /* find timer device */
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    /* open the device in read and write mode */
    rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    /* set the timeout callback function */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);
}
```

### Control the Timer Device

By sending control words, the application can configure the hardware timer device with the following function:

```c
rt_err_t rt_device_control(rt_device_t dev, rt_uint8_t cmd, void* arg);
```

| Parameter        | **Description**                |
| ---------------- | ------------------------------ |
| dev              | device handle                  |
| cmd              | command control word           |
| arg              | controlled parameter           |
| **return**       | ——                             |
| RT_EOK           | function executed successfully |
| -RT_ENOSYS       | execution failed，dev is null  |
| other error code | execution failed               |

The command control words available for the hardware timer device are as follows：

| **Control word** | Description                        |
| ---------------------- | ------------------------ |
| HWTIMER_CTRL_FREQ_SET | set the counting frequency |
| HWTIMER_CTRL_STOP     | stop the timer |
| HWTIMER_CTRL_INFO_GET | get timer feature information |
| HWTIMER_CTRL_MODE_SET | set timer mode |

Get the timer parameter argument, which is a pointer to the structure struct rt_hwtimer_info, to save the obtained information.

>Setting frequency is valid only when the timer hardware and included driver set the counting frequency. Generally, the default frequency of the driving setting can be used.

When setting the timer mode, the parameter argument can take the following values：

```c
HWTIMER_MODE_ONESHOT    /* Single timing */
HWTIMER_MODE_PERIOD     /* Periodic timing */
```

An example of using the timer count frequency and timing mode is as follows:

```c
#define HWTIMER_DEV_NAME   "timer0"     /* timer name */
rt_device_t hw_dev;                     /* timer device handle */
rt_hwtimer_mode_t mode;                 /* timer mode */
rt_uint32_t freq = 10000;               /* couting frequency */

/* Timer timeout callback function */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int hwtimer_sample(int argc, char *argv[])
{
    /* find timer device */
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    /* open the device in read and write mode */
    rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    /* Set the timeout callback function */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /* Set the counting frequency (1Mhz or the supported minimum counting frequency by default) */
    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);
    /* Set the mode to periodic timer */
    mode = HWTIMER_MODE_PERIOD;
    rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
}
```

### Set the Timer Timeout Value

The timer timeout value can be set by the following function：

```c
rt_size_t rt_device_write(rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size);
```

| **Parameter** | Description                        |
| ---------- | ------------------------------------------ |
| dev                | device handle                   |
| pos                | write data offset, unused now, can set 0 value |
| buffer             | pointer to the timer timeout structure |
| size               | timeout structure size |
| **return**      | ——                                     |
| The actual size of the written data |  |
| 0                  | fail |

The prototype of the timeout structure is shown below :

```c
typedef struct rt_hwtimerval
{
    rt_int32_t sec;      /* second */
    rt_int32_t usec;     /* microsecond */
} rt_hwtimerval_t;
```

An example of using the timer timeout value is as follows:

```c
#define HWTIMER_DEV_NAME   "timer0"     /* timer name */
rt_device_t hw_dev;                     /* timer device handle */
rt_hwtimer_mode_t mode;                 /* timer mode */
rt_hwtimerval_t timeout_s;              /* Timer timeout value */

/* Timer timeout callback function */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int hwtimer_sample(int argc, char *argv[])
{
    /* find timer device */
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    /* open the device in read-write mode */
    rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    /* set the timeout callback function */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);
    /* set the mode as periodic timer */
    mode = HWTIMER_MODE_PERIOD;
    rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);

    /* Set the timer timeout value to 5s and start the timer */
    timeout_s.sec = 5;      /* second */
    timeout_s.usec = 0;     /* microsecond */
    rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s));
}
```

### Obtain the Current Value of the Timer

The current value of the timer can be obtained by the following function：

```c
rt_size_t rt_device_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size);
```

| **Parameter** | Description                        |
| ---------- | ------------------------------------------ |
| dev                | timer device handle             |
| pos                | write data offset, unused now , can set 0 value |
| buffer             | output parameter, a pointer point to the timeout structure |
| size               | timeout structure size |
| **return**      | ——                                     |
| Timeout structure size | success |
| 0                  | fail |

An example of use is shown below：

```c
rt_hwtimerval_t timeout_s;      /* Used to save the time the timer has elapsed */
/* Read the elapsed time of the timer  */
rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
```

### Close the Timer Device

The timer device can be closed with the following function:

```c
rt_err_t rt_device_close(rt_device_t dev);
```

| Parameter | Description                |
| ---------- | ---------------------------------- |
| dev        | timer device handle         |
| **return** | ——                                 |
| RT_EOK     | close device successfully |
| -RT_ERROR  | the device has been completely shut down and cannot be closed repeatedly |
| other error code | fail to close the device |

When a timer device has been used and is not necessary anymore, it should be closed, otherwise the device will remain in an open status.

 An example of use is shown below：

```c
#define HWTIMER_DEV_NAME   "timer0"     /* timer name */
rt_device_t hw_dev;                     /* timer device handle */
/* find timer device */
hw_dev = rt_device_find(HWTIMER_DEV_NAME);
... ...
rt_device_close(hw_dev);
```

>Timing errors may occur. Assume that the counter has a maximum value of 0xFFFF, a counting frequency of 1Mhz, and a timing time of 1 second and 1 microsecond. Since the timer can only count up to 65535us at a time, the timing requirement for 1000001us can be completed 20 times at 50000us, and the calculation error will be 1us.

## Hardware Timer Device Usage Example

The specific use of the hardware timer device can refer to the following sample code. The main steps of the sample code are as follows:

1. First find the device handle based on the timer device name "timer0".
2. Open the device "timer0" in read-write mode.
3. Set the timer timeout callback function.
4. Set the timer mode to periodic timer and set the timeout period to 5 seconds. At this time, the timer starts.
5. Read the timer after 3500ms delay, the read value will be displayed in seconds and microseconds.

```c
 /*
  * Program listing: This is an hwtimer device usage routine
  * The routine exports the hwtimer_sample command to the control terminal
  * Command call format: hwtimer_sample
  * Program function: The hardware timer timeout callback function periodically prints the current tick value, and the difference between the two tick values is converted to the time equivalent to the timing time value.
  */

#include <rtthread.h>
#include <rtdevice.h>

#define HWTIMER_DEV_NAME   "timer0"     /* timer name */

/* Timer timeout callback function */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int hwtimer_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;      /* timer timeout value */
    rt_device_t hw_dev = RT_NULL;   /* timer device value */
    rt_hwtimer_mode_t mode;         /* timer mode */

    /* find timer device */
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return RT_ERROR;
    }

    /* Open the device in read-write mode */
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    /* set timeout callback function */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /* Setting mode is periodic timer */
    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    /* Set the timer timeout value to 5s and start the timer. */
    timeout_s.sec = 5;      /* second */
    timeout_s.usec = 0;     /* microsecond */

    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return RT_ERROR;
    }

    /* delay 3500ms */
    rt_thread_mdelay(3500);

    /* read the current value of timer */
    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}
/* Export to the msh command list */
MSH_CMD_EXPORT(hwtimer_sample, hwtimer sample);
```
