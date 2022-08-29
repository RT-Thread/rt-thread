# Sensor Device

## Introduction

Sensors are an important part of the Internet of Things, and sensors in an IoT system are equivalent to the eyes of humans. Without eyes, human beings can not see and interpret the world around them. The same is true for the Internet of Things.

Nowadays, with the development of IoT, a large number of sensors are available for developers to choose, such as Accelerometers, Magnetometers, Gyroscopes, Barometers/pressure senosrs, Hygrometers/humidity meters and so on. However, these sensors, manufactured by the world's leading semiconductor manufacturers, have increased market selectivity and made application development more difficult. Because different sensor manufacturers and sensors need their own unique drivers to run, developers need to write a device driver for each sensor, which can be difficult and time-consuming. In order to reduce the difficulty of application development and increase the reusability of sensor driver, we designed a Sensor device.

The function of the Sensor device is to provide a unified operation interface for the upper layer and improve the reusability of the upper code.

### Characteristics of the Sensor Device

- **Interface:** Standard device interface (open/close/read/control)
- **Work mode:** Supports polling, interrupts, three FIFO (First In, First Out) modes
- **Power mode:** support four modes: power failure, common, low power consumption and high power consumption

## Access Sensor Device

The application accesses the sensor device through the I/O device management interface provided by RT-Thread. The related interfaces are as follows:

| Functions                   | Description                                                  |
| --------------------------- | ------------------------------------------------------------ |
| rt_device_find()            | Finding device handles based on device name of sensor device |
| rt_device_open()            | open sensor device                                           |
| rt_device_read()            | read data                                                    |
| rt_device_control()         | control sensor device                                        |
| rt_device_set_rx_indicate() | setting reveive callback fuction                             |
| rt_device_close()           | close sensor device                                          |

### Find Sensor Device

The application obtains the device handle according to the name of the sensor device, and then can operate the sensor device. The function of finding the device is as follows:

```c
rt_device_t rt_device_find(const char* name);
```

| **Parameter** | **Description**                                              |
| ------------- | ------------------------------------------------------------ |
| name          | sensor device name                                           |
| **return**    | ——                                                           |
| handle        | Finding the corresponding device returns the corresponding device handle |
| RT_NULL       | No corresponding device object was found                     |

The use example is as follows:
```c
#define SENSOR_DEVICE_NAME    "acce_st"    /* sensor device name */

static rt_device_t sensor_dev;         /* sensor device handle */
/* Find the sensor device according to the device name and get the device handle */
sensor_dev = rt_device_find(SENSOR_DEVICE_NAME);
```

### Open Sensor Device

Through the device handle, the application can open and close the device. When the device is opened, it will check whether the device has been initialized or not. If it is not initialized, it will call the initialization interface by default. Open the device through the following functions:

```c
rt_err_t rt_device_open(rt_device_t dev, rt_uint16_t oflags);
```

| **Parameter** | **Description**                                              |
| ------------- | ------------------------------------------------------------ |
| dev           | device handle                                                |
| oflags        | open mode flag                                               |
| **Return**    | ——                                                           |
| RT_EOK        | open success                                                 |
| -RT_EBUSY     | If the RT_DEVICE_FLAG_STANDALONE parameter is included in the parameter specified at the time of device registration, the device will not be allowed to open repeatedly. |
| -RT_EINVAL    | Unsupported open mode                                        |
| other err     | open failed                                                  |

The oflags parameter supports the following parameters：

```c
#define RT_DEVICE_FLAG_RDONLY       0x001     /* Read-only mode for standard device, polling mode for corresponding sensors */
#define RT_DEVICE_FLAG_INT_RX       0x100     /* Interrupt Receiving Mode */
#define RT_DEVICE_FLAG_FIFO_RX      0x200     /* FIFO receiving mode */
```

There are three modes of receiving and sending sensor data: interrupt mode, polling mode and FIFO mode. When using these three modes, **only one of them can be chosen**. If the sensor's open parameter oflags does not specify the use of interrupt mode or FIFO mode, polling mode is used by default.

FIFO transmission mode needs sensor hardware support, data is stored in hardware FIFO, which reads and stores multiple data simultaneously, which allows the CPU to do other operations while gathering data. This feature is very useful in low power mode.

If the sensor uses FIFO receiving mode, the value of oflags is RT_DEVICE_FLAG_FIFO_RX.

An example of turning on sensor devices in polling mode is as follows:

```c
#define SAMPLE_SENSOR_NAME       "acce_st"  /* sensor device name */
int main(void)
{
    rt_device_t dev;
    struct rt_sensor_data data;

    /* find sensor device */
    dev = rt_device_find(SAMPLE_SENSOR_NAME);
    /* Open sensor devices in read-only and polling mode */
    rt_device_open(dev, RT_DEVICE_FLAG_RDWR);

    if (rt_device_read(dev, 0, &data, 1) == 1)
    {
        rt_kprintf("acce: x:%5d, y:%5d, z:%5d, timestamp:%5d\n", data.data.acce.x, data.data.acce.y, data.data.acce.z, data.timestamp);
    }
    rt_device_close(dev);

    return RT_EOK;
}
```

### Control Sensor Device

By command control words, the application program can configure the sensor device through the following functions:

```c
rt_err_t rt_device_control(rt_device_t dev, rt_uint8_t cmd, void* arg);
```

| **Parameter** | **Description**                                              |
| ------------- | ------------------------------------------------------------ |
| dev           | device handle                                                |
| cmd           | command control word, see below for more details.            |
| arg           | the parameters of command control word, see below for more details. |
| **Return**    | ——                                                           |
| RT_EOK        | success                                                      |
| -RT_ENOSYS    | failed，device is NULL                                       |
| other err     | failed                                                       |

`cmd` currently supports the following command control words:

```c
#define  RT_SEN_CTRL_GET_ID            (0)  /* read device ID */
#define  RT_SEN_CTRL_GET_INFO          (1)  /* get device information */
#define  RT_SEN_CTRL_SET_RANGE         (2)  /* Setting the measuring range of the sensor */
#define  RT_SEN_CTRL_SET_ODR           (3)  /* Setting the Output Rate of Sensor Data，unit is HZ */
#define  RT_SEN_CTRL_SET_MODE          (4)  /* Setting up working mode */
#define  RT_SEN_CTRL_SET_POWER         (5)  /* Setting up power mode */
#define  RT_SEN_CTRL_SELF_TEST         (6)  /* selfcheck */
```

#### Get device information

```c
struct rt_sensor_info info;
rt_device_control(dev, RT_SEN_CTRL_GET_INFO, &info);
LOG_I("vendor :%d", info.vendor);
LOG_I("model  :%s", info.model);
LOG_I("unit   :%d", info.unit);
LOG_I("intf_type :%d", info.intf_type);
LOG_I("period_min:%d", info.period_min);
```

#### Read Device ID

```c
rt_uint8_t reg = 0xFF;
rt_device_control(dev, RT_SEN_CTRL_GET_ID, &reg);
LOG_I("device id: 0x%x!", reg);
```

#### Setting the measuring range of the sensor

The unit that sets the measuring range of the sensor is the unit that is provided when the device is registered.

```c
rt_device_control(dev, RT_SEN_CTRL_SET_RANGE, (void *)1000);
```

#### Setting the Output Rate of Sensor Data

Set the output rate to 100Hz and call the following interface.

```c
rt_device_control(dev, RT_SEN_CTRL_SET_ODR, (void *)100);
```

#### Setting up working mode

```c
/* Set the working mode to polling mode */
rt_device_control(dev, RT_SEN_CTRL_SET_MODE, (void *)RT_SEN_MODE_POLLING);
/* Set working mode to interrupt mode */
rt_device_control(dev, RT_SEN_CTRL_SET_MODE, (void *)RT_SEN_MODE_INT);
/* Set working mode to FIFO mode */
rt_device_control(dev, RT_SEN_CTRL_SET_MODE, (void *)RT_SEN_MODE_FIFO);
```

####  Setting up power mode

```c
/* Set power mode to power-off mode */
rt_device_control(dev, RT_SEN_CTRL_SET_POWER, (void *)RT_SEN_POWER_DOWN);
/* Set power mode to normal mode */
rt_device_control(dev, RT_SEN_CTRL_SET_POWER, (void *)RT_SEN_POWER_NORMAL);
/* Setting Power Mode to Low Power Consumption Mode */
rt_device_control(dev, RT_SEN_CTRL_SET_POWER, (void *)RT_SEN_POWER_LOW);
/* Setting Power Mode to High Performance Mode */
rt_device_control(dev, RT_SEN_CTRL_SET_POWER, (void *)RT_SEN_POWER_HIGH);
```

####  Device self-inspection

```c
int test_res;
/* Control equipment self-check and return the results. Returning RT_EOK indicates success of self-check and other values indicate failure of self-check. */
rt_device_control(dev, RT_SEN_CTRL_SELF_TEST, &test_res);
```

### Setting Reveive Callback Fuction

Data reception instructions can be set by following functions. When the sensor receives data, it notifies the upper application thread that data arrives:

```c
rt_err_t rt_device_set_rx_indicate(rt_device_t dev, rt_err_t (*rx_ind)(rt_device_t dev,rt_size_t size));
```

| **Parameter** | **Description**                               |
| ------------- | --------------------------------------------- |
| dev           | device handle                                 |
| rx_ind        | Callback function pointer                     |
| dev           | device handle(parameter of callback function) |
| size          | buffer size(parameter of callback function)   |
| **Return**    | ——                                            |
| RT_EOK        | Successful setup                              |

The callback function of the function is provided by the user. If the sensor is opened in interrupt mode, as the sensor receives data the callback function will be called. The data size of the buffer will be placed in the `size` parameter, and the sensor device handle will be placed in the `dev` parameter for users to obtain.

Generally, receiving callback function can send a semaphore or event to inform sensor data processing thread that data arrives. The use example is as follows:

```c
#define SAMPLE_SENSOR_NAME       "acce_st"  /* sensor device name */
static rt_device_t dev;             /* sensoe device handle*/
static struct rt_semaphore rx_sem;    /* The semaphore used to receive messages */

/* Callback function for receiving data */
static rt_err_t sensor_input(rt_device_t dev, rt_size_t size)
{
    /* When the sensor receives the data, it generates an interrupt, calls the callback function, and sends the semphore . */
    rt_sem_release(&rx_sem);

    return RT_EOK;
}

static int sensor_sample(int argc, char *argv[])
{
    dev = rt_device_find(SAMPLE_SENSOR_NAME);

    /* Open Sensor Device in Interrupt Receive and Poll Send Mode */
    rt_device_open(dev, RT_DEVICE_FLAG_INT_RX);
    /* init semphore */
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

    /* setting reveive callback function */
    rt_device_set_rx_indicate(dev, sensor_input);
}

```

### Read Data of Sensor Device

The following functions can be called to read the data received by the sensor:

```c
rt_size_t rt_device_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size);
```

| **Parameter**          | **Description**                                              |
| ---------------------- | ------------------------------------------------------------ |
| dev                    | device handle                                                |
| pos                    | Read data offset, sensor does not use this parameter         |
| buffer                 | Buffer pointer, read data will be saved in the buffer        |
| size                   | Size of read data                                            |
| **Return**             | ——                                                           |
| Real size of read data | Returns the number of read data                              |
| 0                      | The errno of the current thread needs to be read to determine the error status |

The sensor uses the interrupt receiving mode and cooperates with the receiving callback function as follows:

```c
static rt_device_t dev;             /* sensor device handle */
static struct rt_semaphore rx_sem;    /* The semaphore used to receive messages */

/* Threads receiving data */
static void sensor_irq_rx_entry(void *parameter)
{
    rt_device_t dev = parameter;
    struct rt_sensor_data data;
    rt_size_t res;

    while (1)
    {
        rt_sem_take(rx_sem, RT_WAITING_FOREVER);

        res = rt_device_read(dev, 0, &data, 1);
        if (res == 1)
        {
            sensor_show_data(dev, &data);
        }
    }
}

```

The sensor uses FIFO receiving mode and cooperates with receiving callback function as follows:

```c
static rt_sem_t sensor_rx_sem = RT_NULL;
rt_err_t rx_cb(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(sensor_rx_sem);
    return 0;
}
static void sensor_fifo_rx_entry(void *parameter)
{
    rt_device_t dev = parameter;
    struct rt_sensor_data data;
    rt_size_t res, i;

    data = rt_malloc(sizeof(struct rt_sensor_data) * 32);

    while (1)
    {
        rt_sem_take(sensor_rx_sem, RT_WAITING_FOREVER);

        res = rt_device_read(dev, 0, data, 32);
        for (i = 0; i < res; i++)
        {
            sensor_show_data(dev, &data[i]);
        }
    }
}
int main(void)
{
    static rt_thread_t tid1 = RT_NULL;
    rt_device_t dev;
    struct rt_sensor_data data;

    sensor_rx_sem = rt_sem_create("sen_rx_sem", 0, RT_IPC_FLAG_FIFO);
    tid1 = rt_thread_create("sen_rx_thread",
                            sensor_fifo_rx_entry, dev,
                            1024,
                            15, 5);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    dev = rt_device_find("acce_st");
    rt_device_set_rx_indicate(dev, rx_cb);
    rt_device_open(dev, RT_SEN_FLAG_FIFO);
    return RT_EOK;
}
```

### Close Sensor Device

When the application completes the sensor operation, the sensor device can be closed by the following functions:

```c
rt_err_t rt_device_close(rt_device_t dev);
```

| **Parameter** | **Description**                                              |
| ------------- | ------------------------------------------------------------ |
| dev           | device handle                                                |
| **Return**    | ——                                                           |
| RT_EOK        | The equipment was closed successfully.                       |
| -RT_ERROR     | The device has been completely shut down and cannot be closed  repeatedly. |
| other err     | failed to close th device                                    |

Closing the device interface and opening the device interface should be used in pairs, opening the primary device should close the primary device, so that the device will be completely closed, otherwise the device is still in an open state.

## Example Code for Sensor Device

The specific use of sensor devices can be referred to the following sample code, the main steps of the sample code are as follows:

1. Find the sensor device first and get the device handle.

2. Open the sensor device by polling.

3. Read the data five times in a row and print it out.

4. Close the sensor device.

This sample code is not limited to a specific BSP. According to the BSP registered sensor device, input different dev_name to run.

```c
/*
 * Program List: This is a routine for sensor devices
 * The routine exports the sensor_sample command to the control terminal
 * Command Call Format：sensor_sample dev_name
 * Command Interpretation: The second parameter of the command is the name of the sensor device to be used.
 * Program function: Open the corresponding sensor, and then read the data five times in a row and print it out.
*/

#include "sensor.h"

static void sensor_show_data(rt_size_t num, rt_sensor_t sensor, struct rt_sensor_data *sensor_data)
{
    switch (sensor->info.type)
    {
    case RT_SENSOR_CLASS_ACCE:
        rt_kprintf("num:%3d, x:%5d, y:%5d, z:%5d, timestamp:%5d\n", num, sensor_data->data.acce.x, sensor_data->data.acce.y, sensor_data->data.acce.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_GYRO:
        rt_kprintf("num:%3d, x:%8d, y:%8d, z:%8d, timestamp:%5d\n", num, sensor_data->data.gyro.x, sensor_data->data.gyro.y, sensor_data->data.gyro.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_MAG:
        rt_kprintf("num:%3d, x:%5d, y:%5d, z:%5d, timestamp:%5d\n", num, sensor_data->data.mag.x, sensor_data->data.mag.y, sensor_data->data.mag.z, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_HUMI:
        rt_kprintf("num:%3d, humi:%3d.%d%%, timestamp:%5d\n", num, sensor_data->data.humi / 10, sensor_data->data.humi % 10, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_TEMP:
        rt_kprintf("num:%3d, temp:%3d.%dC, timestamp:%5d\n", num, sensor_data->data.temp / 10, sensor_data->data.temp % 10, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_BARO:
        rt_kprintf("num:%3d, press:%5d, timestamp:%5d\n", num, sensor_data->data.baro, sensor_data->timestamp);
        break;
    case RT_SENSOR_CLASS_STEP:
        rt_kprintf("num:%3d, step:%5d, timestamp:%5d\n", num, sensor_data->data.step, sensor_data->timestamp);
        break;
    default:
        break;
    }
}

static void sensor_sample(int argc, char **argv)
{
    rt_device_t dev = RT_NULL;
    struct rt_sensor_data data;
    rt_size_t res, i;

    /* Finding Sensor Devices in the System */
    dev = rt_device_find(argv[1]);
    if (dev == RT_NULL)
    {
        rt_kprintf("Can't find device:%s\n", argv[1]);
        return;
    }

    /* Open sensor devices in polling mode */
    if (rt_device_open(dev, RT_DEVICE_FLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("open device failed!");
        return;
    }

    for (i = 0; i < 5; i++)
    {
        /* Read a data from a sensor */
        res = rt_device_read(dev, 0, &data, 1);
        if (res != 1)
        {
            rt_kprintf("read data failed!size is %d", res);
        }
        else
        {
            sensor_show_data(i, (rt_sensor_t)dev, &data);
        }
        rt_thread_mdelay(100);
    }
    /* Close the sensor device */
    rt_device_close(dev);
}
MSH_CMD_EXPORT(sensor_sample, sensor device sample);
```

