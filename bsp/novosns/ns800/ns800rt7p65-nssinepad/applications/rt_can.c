#include <rtthread.h>
#include <rtdevice.h>
#include "drivers/dev_can.h"
#include "rt_can.h"


#define CAN_DEV_NAME       "canfd1"      // The name of the CAN device

static rt_device_t can_dev;            // CAN device handle
static struct rt_semaphore rx_sem;     // Semaphore for message reception


// Callback function for CAN reception
static rt_err_t can_rx_callback(rt_device_t dev, rt_size_t size)
{
    // The CAN interrupt calls this callback when data is received.
    // Release the semaphore to notify the receiving thread.
    rt_sem_release(&rx_sem);
    return RT_EOK;
}

static void can_rx_thread(void *parameter)
{
    rt_err_t res;
    struct rt_can_msg rx_msg = {0};

    // Set the receive callback function
    rt_device_set_rx_indicate(can_dev, can_rx_callback);

    // Some drivers might require an explicit start command.
    // This is driver-specific.
    rt_uint32_t cmd_arg = 1; // Argument to enable the controller
    res = rt_device_control(can_dev, RT_CAN_CMD_START, &cmd_arg);
    RT_ASSERT(res == RT_EOK);

    #define CAN_RX_BATCH_SIZE 8

    while (1)
    {
        // Block and wait for the semaphore, which is released by the receive callback.
        rt_sem_take(&rx_sem, RT_WAITING_FOREVER);

        // Drain all pending frames in batches.
        struct rt_can_msg rx_buf[CAN_RX_BATCH_SIZE];
        rt_ssize_t read_size;
        rt_size_t count;
        do
        {
            for (rt_size_t i = 0; i < CAN_RX_BATCH_SIZE; i++)
            {
                rx_buf[i].hdr_index = -1;
            }

            read_size = rt_device_read(can_dev, 0, rx_buf, sizeof(rx_buf));
            if (read_size <= 0)
            {
                break;
            }
            count = (rt_size_t)(read_size / sizeof(rx_buf[0]));
            for (rt_size_t i = 0; i < count; i++)
            {
                // Print the received message's ID and data.
                rt_kprintf("Received a message. ID: 0x%x, Data: ", rx_buf[i].id);
                for (int j = 0; j < rx_buf[i].len; j++)
                {
                    rt_kprintf("%02x ", rx_buf[i].data[j]);
                }
                rt_kprintf("\n");
            }
        }
        while(count == CAN_RX_BATCH_SIZE);
    }
}

static void can_tx_thread(void *parameter)
{
    rt_err_t res;
    static uint8_t index;
    struct rt_can_msg blocking_msg = {0};
    blocking_msg.id = 0x78;
    blocking_msg.ide = RT_CAN_STDID;
    blocking_msg.rtr = RT_CAN_DTR;
    blocking_msg.len = 8;
    
    while(1)
    {
        // The `nonblocking` flag is 0 by default for blocking mode.
        for(int i = 0; i < 8; i++) blocking_msg.data[i] = i+index;
        index++;
        
        rt_kprintf("Attempting to send a message in BLOCKING mode...\n");
        if (rt_device_write(can_dev, 0, &blocking_msg, sizeof(blocking_msg)) == sizeof(blocking_msg))
        {
            rt_kprintf("Blocking message sent successfully.\n");
        }
        else
        {
            rt_kprintf("Blocking message send failed.\n");
        }
        
        rt_thread_mdelay(1000); // Wait a moment for clarity in the log
    }
}

int can_sample(int argc, char *argv[])
{
    rt_err_t res;
    rt_thread_t thread;
    char can_name[RT_NAME_MAX];

    // Allow specifying the CAN device name from the command line, e.g., "can_sample can2"
    if (argc == 2)
    {
        rt_strncpy(can_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(can_name, CAN_DEV_NAME, RT_NAME_MAX);
    }

    // Find the CAN device by name
    can_dev = rt_device_find(can_name);
    if (!can_dev)
    {
        rt_kprintf("find device %s failed!\n", can_name);
        return -RT_ERROR;
    }

    // Initialize the receive semaphore
    rt_sem_init(&rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);

    // Open the CAN device in interrupt-driven TX/RX mode
    res = rt_device_open(can_dev, RT_DEVICE_FLAG_INT_TX | RT_DEVICE_FLAG_INT_RX);
    RT_ASSERT(res == RT_EOK);

    // Create and start the data receiving thread
    thread = rt_thread_create("can_rx", can_rx_thread, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create can_rx thread failed!\n");
        return -RT_ERROR;
    }
    
    // Create and start the data receiving thread
    thread = rt_thread_create("can_tx", can_tx_thread, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create can_tx thread failed!\n");
        return -RT_ERROR;
    }

    rt_kprintf("CAN device %s opened successfully.\n", can_name);

    return res;
}
// Export the function to the MSH command line
MSH_CMD_EXPORT(can_sample, can device usage example);
