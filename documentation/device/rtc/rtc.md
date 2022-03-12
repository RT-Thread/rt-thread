# RTC Device

## Introduction of RTC

The RTC (Real-Time Clock) provides accurate real-time clock time, which can be used to generate information such as year, month, day, hour, minute, and second. At present, most real-time clock chips use a higher precision crystal oscillator as a clock source. In order to work when the main power supply is powered down, some clock chips will be powered by a battery to keep the time information valid.

The RT-Thread RTC device provides the basic services for the operating system's time system. In the face of more and more IoT scenarios, RTC has become the standard configuration of the product, and even in the secure transmission process such as SSL, RTC has become an indispensable part.


## Access RTC Devices

The application accesses the RTC hardware through the RTC device management interface, and the relevant interfaces are as follows:

| **Function** | Description                |
| ------------- | ---------------------------------- |
| set_date()  | Set date, year, month, day |
| set_time()     | Set time, hour, minute, second |
| time()   | Obtain current time |

### Set Date

Set the current date value of the RTC device by the following functions:

```c
rt_err_t set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day)
```

| **Parameter** | **Description**                |
| -------- | ---------------------------------- |
|year      |The year to be set to take effect|
|month     |The month to be set to take effect|
|day       | The date to be set to take effect  |
| **return** | ——                                 |
| RT_EOK   | Set-up succeeded |
| -RT_ERROR | Set-up failed, no rtc device found |
| other error code | Set-up failed  |

An example of use is as follows:

```c
/* Set the date to December 3, 2018 */
set_date(2018, 12, 3);
```

### Set Time

Set the current time value of the RTC device by the following function:

```c
rt_err_t set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second)
```

| **Parameter** | **Description**              |
| ---------- | ------------------------------- |
|hour         |The hour to be set to take effect|
|minute        |The minute to be set to take effect|
|second        |The second to be set to take effect|
| **return** | ——                             |
| RT_EOK   | Set-up succeeded |
| -RT_ERROR | Set-up failed, no rtc device found |
| other error code | Set-up failed   |

An example of use is as follows:

```c
/* Set the time to 11:15:50 */
set_time(11, 15, 50);
```

### Obtain Current Time

Obtain time using the time API in the C standard library:

```c
time_t time(time_t *t)
```

| **Parameter** | **Description**              |
| ---------- | ------------------------------- |
|t          |Time data pointer      |
| **return** | ——                             |
| Current time value |  |

Examples of use are as follows:

```c
time_t now;     /* Save the current time value obtained */
/* Obtain Time */
now = time(RT_NULL);
/* Printout time information */
rt_kprintf("%s\n", ctime(&now));
```

>Currently only one RTC device is allowed in the system and the name is `"rtc"`.

## Functional Configuration

### Enable Soft RTC (Software Emulation RTC)

You can use the function of enabling RTC software emulation, which is ideal for products that do not require high time precision and have no hardware RTC. The configuration options of menuconfig are as follows:

```c
RT-Thread Components →
    Device Drivers:
        -*- Using RTC device drivers                                 /* Use RTC device driver */
        [ ]   Using software simulation RTC device                   /* Use software simulation RTC device */
```

### Enable NTP Time Automatic Synchronization

If the RT-Thread is connected to the Internet, you can enable automatic NTP time synchronization to synchronize local time periodically.

First open the NTP function in menuconfig as follows:

```c
RT-Thread online packages →
    IoT - internet of things →
        netutils: Networking utilities for RT-Thread:
             [*]   Enable NTP(Network Time Protocol) client
```

After the NTP is turned on, the RTC's automatic synchronization function will be automatically turned on, and the synchronization period and the delay time of the first synchronization can also be set:

```c
RT-Thread Components →
    Device Drivers:
        -*- Using RTC device drivers                                 /* Use RTC device driver */
        [ ]   Using software simulation RTC device                   /* Use software simulation RTC device */
        [*]   Using NTP auto sync RTC time                           /* Automatically synchronize RTC time with NTP */
       (30)    NTP first sync delay time(second) for network connect /* The delay for performing NTP time synchronization for the first time. The purpose of the delay is to reserve a certain amount of time for the network connection and try to increase the success rate of the first NTP time synchronization. The default time is 30S； */
       (3600)  NTP auto sync period(second)                          /* NTP The synchronization period is automatically synchronized in seconds, and the default period is one hour (ie 3600S). */
```

## FinSH Command

Enter `date` to view the current time.

```c
msh />date
Fri Feb 16 01:11:56 2018
msh />
```

Also use the `date` command, after the command, enter `year` `month` `date` `hour ` ` minute ` ` second ` (between spaces, 24H system), and set the current time to 2018-02-16 01:15:30. The approximate effect is as follows:

```c
msh />date 2018 02 16 01 15 30
msh />
```

## RTC Device Usage Examples

For the specific usage of the RTC device, refer to the following example code. First, set the year, month, date, hour, minute and second information, and then delay the data for 3 seconds to get the current time information.

```c
/*
 * Program listing: This is an RTC device usage routine
 * The routine exports the rtc_sample command to the control terminal
 * Command call format：rtc_sample
 * Program function: Set the date and time of the RTC device. After a delay, obtain the current time and print the display.
*/

#include <rtthread.h>
#include <rtdevice.h>

static int rtc_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    time_t now;

    /* Set date */
    ret = set_date(2018, 12, 3);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC date failed\n");
        return ret;
    }

    /* Set time */
    ret = set_time(11, 15, 50);
    if (ret != RT_EOK)
    {
        rt_kprintf("set RTC time failed\n");
        return ret;
    }

    /* Delay 3 seconds */
    rt_thread_mdelay(3000);

    /* Obtain Time */
    now = time(RT_NULL);
    rt_kprintf("%s\n", ctime(&now));

    return ret;
}
/* Export to the msh command list */
MSH_CMD_EXPORT(rtc_sample, rtc sample);
```
