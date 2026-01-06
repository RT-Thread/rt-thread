
#include "rtconfig.h"
#ifdef BSP_USING_CAN
#include <rtdevice.h>
#include "drv_can.h"
#define LOG_TAG      "can_drv"
#include "drv_log.h"
#include "fcan.h"
#include "fio_mux.h"
#include "interrupt.h"
#include "fcpu_info.h"
/*can test example*/
static rt_device_t can0_dev;            /* CAN device handle */
static rt_device_t can1_dev;            /* CAN device handle */
static struct rt_semaphore can0_rx_sem;
static struct rt_semaphore can1_rx_sem;
static struct rt_can_msg rxmsg = {0};

static rt_err_t can0_rx_call(rt_device_t dev, rt_size_t size)
{
    /* The CAN generates an interrupt after receiving data, calls this callback function, and then sends the received semaphore */
    rt_sem_release(&can0_rx_sem);
    return RT_EOK;
}

static void can0_rx_thread(void *parameter)
{
    int i;
    rt_err_t res = RT_EOK;
    rt_device_set_rx_indicate(can0_dev, can0_rx_call);
    while (1)
    {
        /* The hdr value is - 1, which means reading data directly from the uselist */
        rxmsg.hdr_index = -1;
        /* Blocking waiting to receive semaphore */
        res = rt_sem_take(&can0_rx_sem, RT_WAITING_FOREVER);
        RT_ASSERT(res == RT_EOK);
        /* Read a frame of data from CAN */
        rt_device_read(can0_dev, 0, &rxmsg, sizeof(rxmsg));
        /* Print data ID and conten */
        LOG_D("ID:%x\n", rxmsg.id);
        LOG_D("DATA: ");
        for (i = 0; i < 8; i++)
        {
            LOG_D("%2x ", rxmsg.data[i]);
        }

        LOG_D("\n");
    }
}

static rt_err_t can1_rx_call(rt_device_t dev, rt_size_t size)
{
    /* The CAN generates an interrupt after receiving data, calls this callback function, and then sends the received semaphore */
    rt_sem_release(&can1_rx_sem);
    return RT_EOK;
}

static void can1_rx_thread(void *parameter)
{
    int i;
    rt_err_t res = RT_EOK;
    rt_device_set_rx_indicate(can1_dev, can1_rx_call);
    while (1)
    {
        /* The hdr value is - 1, which means reading data directly from the uselist */
        rxmsg.hdr_index = -1;
        /* Blocking waiting to receive semaphore */
        res = rt_sem_take(&can1_rx_sem, RT_WAITING_FOREVER);
        RT_ASSERT(res == RT_EOK);
        /* Read a frame of data from CAN */
        rt_device_read(can1_dev, 0, &rxmsg, sizeof(rxmsg));
        /* Print data ID and conten */
        LOG_D("ID:%x\n", rxmsg.id);
        LOG_D("DATA: ");
        for (i = 0; i < 8; i++)
        {
            LOG_D("%2x ", rxmsg.data[i]);
        }

        LOG_D("\n");
    }
}

rt_err_t can_loopback_sample()
{
    struct rt_can_msg msg = {0};
    rt_err_t res = RT_EOK;;
    rt_thread_t thread;

    /* Find CAN device */
    can0_dev = rt_device_find("CAN0");
    if (!can0_dev)
    {
        rt_kprintf("Find CAN0 failed.\n");
        return -RT_ERROR;
    }

    /* Find CAN device */
    can1_dev = rt_device_find("CAN1");
    if (!can1_dev)
    {
        rt_kprintf("Find CAN1 failed.\n");
        return -RT_ERROR;
    }

    /* Initialize CAN receive signal quantity */
    res = rt_sem_init(&can0_rx_sem, "can0_rx_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(res == RT_EOK);

    res = rt_sem_init(&can1_rx_sem, "can1_rx_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(res == RT_EOK);

    /* Open the CAN device in the way of interrupt reception and transmission */
    res = rt_device_open(can0_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    rt_device_control(can0_dev, RT_CAN_CMD_SET_BAUD, CAN800kBaud);
    RT_ASSERT(res == RT_EOK);

    res = rt_device_open(can1_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    rt_device_control(can1_dev, RT_CAN_CMD_SET_BAUD, CAN800kBaud);
    RT_ASSERT(res == RT_EOK);

    /* Create data receiving thread */
    thread = rt_thread_create("can0_rx", can0_rx_thread, RT_NULL, 4096, 10, 10);
    if (thread != RT_NULL)
    {
        res = rt_thread_startup(thread);
        RT_ASSERT(res == RT_EOK);
    }
    else
    {
        rt_kprintf("Create can0_rx thread failed.\n");
    }
    thread = rt_thread_create("can1_rx", can1_rx_thread, RT_NULL, 4096, 10, 10);
    if (thread != RT_NULL)
    {
        res = rt_thread_startup(thread);
        RT_ASSERT(res == RT_EOK);
    }
    else
    {
        rt_kprintf("Create can1_rx thread failed.\n");
    }


    msg.id = 0x78;              /* ID = 0x78 */
    msg.ide = RT_CAN_STDID;     /* Standard format */
    msg.rtr = RT_CAN_DTR;       /* Data frame */
    msg.len = 8;                /* Data length is 8 */
    /* Send CAN data */
    for (int i = 0; i < 5; i++)
    {
        /* 8-byte data to be sent */
        msg.data[0] = 0x0;
        msg.data[1] = 0x1;
        msg.data[2] = 0x2;
        msg.data[3] = 0x3;
        msg.data[4] = 0x4;
        msg.data[5] = 0x5;
        msg.data[6] = 0x6;
        msg.data[7] = 0x7;
        rt_device_write(can0_dev, 0, &msg, sizeof(msg));
        rt_thread_mdelay(100);
        for (int i = 0; i < 8; i++)
        {
            if (msg.data[i] != rxmsg.data[i])
            {
                res = RT_ERROR;
                goto exit;
            }
        }
    }

    /* Send CAN data */
    for (int i = 0; i < 5; i++)
    {
        /* 8-byte data to be sent */
        msg.data[0] = 0x0;
        msg.data[1] = 0x1;
        msg.data[2] = 0x2;
        msg.data[3] = 0x3;
        msg.data[4] = 0x4;
        msg.data[5] = 0x5;
        msg.data[6] = 0x6;
        msg.data[7] = 0x7;
        rt_device_write(can1_dev, 0, &msg, sizeof(msg));
        rt_thread_mdelay(100);
        for (int i = 0; i < 8; i++)
        {
            if (msg.data[i] != rxmsg.data[i])
            {
                res = RT_ERROR;
                goto exit;
            }
        }
    }
exit:
    /* print message on example run result */
    if (res == RT_EOK)
    {
        rt_kprintf("%s@%d:Can loopback test example [success].\r\n", __func__, __LINE__);
    }
    else
    {
        rt_kprintf("%s@%d:Can loopback test example [failure], res = %d\r\n", __func__, __LINE__, res);
    }

    return res;
}
/* Enter can_sample command for testing */
MSH_CMD_EXPORT(can_loopback_sample, can device sample);
#endif