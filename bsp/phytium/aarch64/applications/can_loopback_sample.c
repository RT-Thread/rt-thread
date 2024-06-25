
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
static rt_device_t can_tx_dev;      /* CAN device handle */
static rt_device_t can_rx_dev;      /* CAN device handle */
static struct rt_semaphore rx_sem;
static struct rt_can_msg txmsg;
static struct rt_can_msg rxmsg;

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
    char can_name[RT_NAME_MAX];
    struct rt_can_msg rxmsg = {0};
    rt_strncpy(can_name, (char *)parameter, RT_NAME_MAX);

    can_rx_dev = rt_device_find(can_name);
    if (!can_rx_dev)
    {
        rt_kprintf("Find %s failed.\n", can_name);
        return RT_ERROR;
    }
    res = rt_device_open(can_rx_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    rt_device_control(can_rx_dev, RT_CAN_CMD_SET_BAUD, CAN1MBaud);
    RT_ASSERT(res == RT_EOK);
    rt_device_set_rx_indicate(can_rx_dev, can_rx_call);

    while (1)
    {
        /* The hdr value is - 1, which means reading data directly from the uselist */
        rxmsg.hdr_index = -1;
        /* Blocking waiting to receive semaphore */
        res = rt_sem_take(&rx_sem, RT_WAITING_FOREVER);
        RT_ASSERT(res == RT_EOK);
        /* Read a frame of data from CAN */
        rt_device_read(can_rx_dev, 0, &rxmsg, sizeof(rxmsg));
        /* Print data ID and conten */
        rt_kprintf("ID:%x\n", rxmsg.id);
        rt_kprintf("DATA: ");
        for (i = 0; i < 8; i++)
        {
            if (rxmsg.data[i] != txmsg.data[i])
            {
                RT_ASSERT(0);
            }
            rt_kprintf("%2x ", rxmsg.data[i]);
        }

        rt_kprintf("\n");
    }
}

static void can_tx_thread(void *parameter)
{
    rt_err_t res = RT_EOK;
    int times = 0;
    char can_name[RT_NAME_MAX];
    rt_strncpy(can_name, (char *)parameter, RT_NAME_MAX);

    can_tx_dev = rt_device_find(can_name);

    if (!can_tx_dev)
    {
        rt_kprintf("Find %s failed.\n", can_name);
        return RT_ERROR;
    }
    res = rt_device_open(can_tx_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    rt_device_control(can_tx_dev, RT_CAN_CMD_SET_BAUD, CAN1MBaud);
    RT_ASSERT(res == RT_EOK);

    while (1)
    {
        txmsg.id = 0x01 + times;              /* ID = 0x78 */
        txmsg.ide = RT_CAN_STDID;     /* Standard format */
        txmsg.rtr = RT_CAN_DTR;       /* Data frame */
        txmsg.len = 8;                /* Data length is 8 */
        /* 8-byte data to be sent */
        txmsg.data[0] = 0x0 + times;
        txmsg.data[1] = 0x1 + times;
        txmsg.data[2] = 0x2 + times;
        txmsg.data[3] = 0x3 + times;
        txmsg.data[4] = 0x4 + times;
        txmsg.data[5] = 0x5 + times;
        txmsg.data[6] = 0x6 + times;
        txmsg.data[7] = 0x7 + times;
        rt_device_write(can_tx_dev, 0, &txmsg, sizeof(txmsg));

        if(times < 50)
        {
            times++;
        }
        else
        {
            times = 0;
        }

        FDriverMdelay(50);
    }
}

int can_loopback_sample(int argc, char *argv[])
{
    rt_err_t res = RT_EOK;
    rt_thread_t tx_thread;
    rt_thread_t rx_thread;

    /* Initialize CAN receive signal quantity */
    res = rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    RT_ASSERT(res == RT_EOK);

    rx_thread = rt_thread_create("can_rx", can_rx_thread, "CAN1", 4096, 20, 10);
    if (rx_thread != RT_NULL)
    {
        res = rt_thread_startup(rx_thread);
        RT_ASSERT(res == RT_EOK);
    }
    else
    {
        rt_kprintf("Create can_rx thread failed.\n");
    }

    /* Create data receiving thread */
    tx_thread = rt_thread_create("can_tx", can_tx_thread, "CAN0", 4096, 25, 10);
    if (tx_thread != RT_NULL)
    {
        res = rt_thread_startup(tx_thread);
        RT_ASSERT(res == RT_EOK);
    }
    else
    {
        rt_kprintf("Create can_tx thread failed.\n");
    }

    return res;
}
/* Enter can_loopback_sample command for testing */
MSH_CMD_EXPORT(can_loopback_sample, can device sample);
#endif