# WATCHDOG Device

## An Introduction to WATCHDOG

The hardware watchdog timer is a timer whose timing output is connected to the reset terminal of the circuit. In a productized embedded system, in order to automatically reset the system under abnormal conditions, it generally needs a watchdog.

When the watchdog was started, the counter starts counting automatically. If it is not reset counter value before the counter overflows, the counter overflow will generate a reset signal to the CPU to restart the system. When the system is running normally, it is necessary to clear the watchdog counter within the time interval allowed by the watchdog (commonly known as "feeding the dog"), and the reset signal will not be generated. If the program can "feed the dog" on time，the system does not go wrong，otherwise the system will reset.

In general, users can feed the dog in the idlehook function and key function of RT-Thread.

## Access to the WATCHDOG Device

The application accesses the watchdog hardware through the I/O device management interface provided by RT-Thread. The related interfaces are as follows:

| **Function** | **Description**       |
| ---------------- | ---------------------------------- |
| rt_device_find()  | Find the device handle based on the device name of the watchdog device |
| rt_device_init()     | Initialize the watchdog device |
| rt_device_control()   |Control the watchdog device |
| rt_device_close()  | Close the watchdog device |

### Find the Watchdog Device

The application obtains the device handle based on the watchdog device's name, and then it can operate the watchdog device. The function for finding a device is as follows:

```c
rt_device_t rt_device_find(const char* name);
```

| **Function** | **Description**                |
| -------- | ---------------------------------- |
| name     | the name of the watchdog device |
| **return** | ——                                 |
| device handle | finding the corresponding device and then return to the corresponding device handle |
| RT_NULL  | no corresponding device object found |

An usage example is as follows:

```c
#define IWDG_DEVICE_NAME    "iwg"    /* the name of the watchdog device */

static rt_device_t wdg_dev;         /* device handle of the watchdog */
/* find the watchdog device based on the device's name and obtain the device handle */
wdg_dev = rt_device_find(IWDG_DEVICE_NAME);
```

### Initialize the Watchdog Device

The watchdog device need to be initialized before using, which can be done by the following function:

```c
rt_err_t rt_device_init(rt_device_t dev);
```

| **Function** | **Description**              |
| ---------- | ------------------------------- |
| dev        | handle of the watchdog device |
| **return** | ——                             |
| RT_EOK     | the device succeeded initializing |
| -RT_ENOSYS | initialization failed, the watchdog device driver initialization function is empty |
| other error code | the device failed to open |

An example is as follows:

```c
#define IWDG_DEVICE_NAME    "iwg"    /* the name of the watchdog device */

static rt_device_t wdg_dev;    /* handle of the watchdog device */
/* find the watchdog device based on the device's name and obtain the device handle */
wdg_dev = rt_device_find(IWDG_DEVICE_NAME);

/* initialize the device */
rt_device_init(wdg_dev);
```

### Control the Watchdog Device

The application can configure the watchdog device using the command control word, which can be done by the following function:

```c
rt_err_t rt_device_control(rt_device_t dev, rt_uint8_t cmd, void* arg);
```

| **Function**     | **Description**                    |
| ---------------- | ---------------------------------- |
| dev              | handle of the watchdog device      |
| cmd              | the command word                   |
| arg              | controlled parameter               |
| **return**       | ——                                 |
| RT_EOK           | function executed successfully     |
| -RT_ENOSYS       | execution failed, the dev is empty |
| other error code | execution failed                   |

The command control word `'cmd'` can take the following macro definition values:

```c
#define RT_DEVICE_CTRL_WDT_GET_TIMEOUT    (1) /* get the overflow time */
#define RT_DEVICE_CTRL_WDT_SET_TIMEOUT    (2) /* set the overflow time */
#define RT_DEVICE_CTRL_WDT_GET_TIMELEFT   (3) /* get the remaining time */
#define RT_DEVICE_CTRL_WDT_KEEPALIVE      (4) /* feed the dog */
#define RT_DEVICE_CTRL_WDT_START          (5) /* start the watchdog */
#define RT_DEVICE_CTRL_WDT_STOP           (6) /* stop the watchdog */
```

An example of setting the overflow time of the watchdog is as follows:

```c
#define IWDG_DEVICE_NAME    "iwg"    /* the name of the watchdog device */

rt_uint32_t timeout = 1000;    /* the overflow time */
static rt_device_t wdg_dev;    /* handle of the watchdog device */
/* find the watchdog device based on the device's name and obtain the device handle */
wdg_dev = rt_device_find(IWDG_DEVICE_NAME);
/* initialize the device */
rt_device_init(wdg_dev);

/* set the overflow time of the watch dog */
rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, (void *)timeout);
/* set idle-hook function */
rt_thread_idle_sethook(idle_hook);
```

An example of feeding a dog in an idle thread hook function is as follows:

```c
static void idle_hook(void)
{
    /* Feed the dog in the callback function of the idle thread */
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
}
```

### Close the Watchdog Device

When the application completes the operation of the watchdog, it can close the watchdog device:

```c
rt_err_t rt_device_close(rt_device_t dev);
```

| **Function** | **Description**                |
| ---------- | ---------------------------------- |
| dev        | handle of the watchdog device                                |
| **return** | ——                                 |
| RT_EOK     | close the device successfully |
| -RT_ERROR  | The device has been completely shut down and cannot be closed repeatedly |
| other error code | fail to close the device |

Closing the device interface and opening the device interface need to match each other. When you open the device, you need to close the device once correspondingly, so that the device will be completely shut down, otherwise the device will remain unclosed.

## Watchdog Device usage example

The specific use of the watchdog device can be referred to the following sample code. The main steps of the sample code are as follows:

1. First find the device handle based on the device name "iwg".
2. Set the overflow time of the watchdog after initializing the device.
3. Set the idle thread callback function.
4. This callback function will run and feed the dog when the system executes idle threads.

```c
/*
 * Program list: This is an independent watchdog device usage routine
 * The routine exports the iwdg_sample command to the control terminal
 * Command call format: iwdg_sample iwg
 * Command explanation: The second parameter of the command is the name of the watchdog device to be used. If it is empty, you can use the default watchdog device of the routine.
 * Program function: The program finds the watchdog device through the device's name, and then initializes the device and sets the overflow time of the watchdog device.
 *           Then set the idle thread callback function, which will feed the dog in the idle callback function.
*/

#include <rtthread.h>
#include <rtdevice.h>

#define IWDG_DEVICE_NAME    "iwg"    /* the name of the watchdog device */

static rt_device_t wdg_dev;         /* handle of the watchdog device */

static void idle_hook(void)
{
    /* feed the dog in the callback function */
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
    rt_kprintf("feed the dog!\n ");
}

static int iwdg_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 1000;    /* the overflow time */
    char device_name[RT_NAME_MAX];

    /* Determine if the command-line parameter is given the device name */
    if (argc == 2)
    {
        rt_strncpy(device_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(device_name, IWDG_DEVICE_NAME, RT_NAME_MAX);
    }
    /* find the watchdog device based on the device's name and obtain the device handle */
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* initialize the device */
    ret = rt_device_init(wdg_dev);
    if (ret != RT_EOK)
    {
        rt_kprintf("initialize %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* set the overflow time of the watch dog */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return -RT_ERROR;
    }
    /* set idle thread callback function */
    rt_thread_idle_sethook(idle_hook);

    return ret;
}
/* export to the msh command list */
MSH_CMD_EXPORT(iwdg_sample, iwdg sample);
```

