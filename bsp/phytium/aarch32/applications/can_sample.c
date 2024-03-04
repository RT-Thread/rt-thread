
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
static rt_device_t can_dev;            /* CAN device handle */
static struct rt_semaphore rx_sem;
static rt_err_t can_rx_call(rt_device_t dev, rt_size_t size)
{
    /* The CAN generates an interrupt after receiving data, calls this callback function, and then sends the received semaphore */
    rt_sem_release(&rx_sem);
    return RT_EOK;
}
static void can_rx_thread(void *parameter)
{
    int i;
    rt_err_t res = RT_EOK;
    struct rt_can_msg rxmsg = {0};
    rt_device_set_rx_indicate(can_dev, can_rx_call);
    while (1)
    {
        /* The hdr value is - 1, which means reading data directly from the uselist */
        rxmsg.hdr_index = -1;
        /* Blocking waiting to receive semaphore */
        res = rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        RT_ASSERT(res == RT_EOK);
        /* Read a frame of data from CAN */
        rt_device_read(can_dev, 0, &rxmsg, sizeof(rxmsg));
        /* Print data ID and conten */
        rt_kprintf("ID:%x\n", rxmsg.id);
        rt_kprintf("DATA: ");
        for (i = 0; i < 8; i++)
        {
            rt_kprintf("%2x ", rxmsg.data[i]);
        }

        rt_kprintf("\n");
    }
}

int can_sample(int argc, char *argv[])
{
    struct rt_can_msg msg = {0};
    rt_err_t res = RT_EOK;;
    rt_thread_t thread;
    char can_name[RT_NAME_MAX];

    if (argc == 2)
    {
        rt_strncpy(can_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(can_name, "CAN0", RT_NAME_MAX);
    }
    /* Find CAN device */
    can_dev = rt_device_find(can_name);
    if (!can_dev)
    {
        rt_kprintf("Find %s failed.\n", can_name);
        return RT_ERROR;
    }

    /* Initialize CAN receive signal quantity */
    res = rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(res == RT_EOK);

    /* Open the CAN device in the way of interrupt reception and transmission */
    res = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    rt_device_control(can_dev, RT_CAN_CMD_SET_BAUD, CAN1MBaud);
    RT_ASSERT(res == RT_EOK);

#ifdef RT_CAN_USING_HDR
    struct rt_can_filter_item items[4] =
    {
        RT_CAN_FILTER_ITEM_INIT(0x3, 0, 0, 0, 0, RT_NULL, RT_NULL),
        RT_CAN_FILTER_ITEM_INIT(0x3, 0, 0, 0, 0, RT_NULL, RT_NULL),
        RT_CAN_FILTER_ITEM_INIT(0x3, 0, 0, 0, 0, RT_NULL, RT_NULL),
        RT_CAN_FILTER_ITEM_INIT(0x3, 0, 0, 0, 0, RT_NULL, RT_NULL)

    };
    struct rt_can_filter_config cfg = {4, 1, items}; /* There are 4 filter tables in total */

    /* Set the hardware filter table. After setting, only frames with id=0x03 can be received*/
    res = rt_device_control(can_dev, RT_CAN_CMD_SET_FILTER, &cfg);
    RT_ASSERT(res == RT_EOK);
#endif

    /* Create data receiving thread */
    thread = rt_thread_create("can_rx", can_rx_thread, RT_NULL, 4096, 25, 10);
    if (thread != RT_NULL)
    {
        res = rt_thread_startup(thread);
        RT_ASSERT(res == RT_EOK);
    }
    else
    {
        rt_kprintf("Create can_rx thread failed.\n");
    }

    msg.id = 0x78;              /* ID = 0x78 */
    msg.ide = RT_CAN_STDID;     /* Standard format */
    msg.rtr = RT_CAN_DTR;       /* Data frame */
    msg.len = 8;                /* Data length is 8 */
    /* Send CAN data */
    for (int i = 0; i < 1; i++)
    {
        /* 8-byte data to be sent */
        msg.data[0] = 0x00 + i;
        msg.data[1] = 0x11 + i;
        msg.data[2] = 0x22 + i;
        msg.data[3] = 0x33 + i;
        msg.data[4] = 0x44 + i;
        msg.data[5] = 0x55 + i;
        msg.data[6] = 0x66 + i;
        msg.data[7] = 0x77 + i;
        rt_device_write(can_dev, 0, &msg, sizeof(msg));
    }

    return res;
}
/* Enter can_sample command for testing */
MSH_CMD_EXPORT(can_sample, can device sample);
#endif