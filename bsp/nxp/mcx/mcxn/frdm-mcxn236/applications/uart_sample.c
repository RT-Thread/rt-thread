/**
 * @file uart_sample.c
 * @brief UART5 interrupt-driven sample for RT-Thread on MCX N236
 */

#include <rtthread.h>
#include <rtdevice.h>

#define UART_DEVICE_NAME     "uart5"
#define UART_THREAD_STACK    1024
#define UART_THREAD_PRIORITY 25
#define UART_THREAD_TIMESLICE 10

static rt_device_t g_uart_device;
static struct rt_semaphore g_rx_sem;

/**
 * @brief UART receive callback function
 * @param dev Pointer to device
 * @param size Size of received data
 * @return RT_EOK
 */
static rt_err_t uart_rx_callback(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&g_rx_sem);
    return RT_EOK;
}

/**
 * @brief UART processing thread
 * @param parameter Thread parameter (unused)
 */
static void uart_thread_entry(void *parameter)
{
    char ch;

    while (1)
    {
        /* Wait for incoming data */
        rt_sem_take(&g_rx_sem, RT_WAITING_FOREVER);

        /* Read and echo back each character */
        while (rt_device_read(g_uart_device, -1, &ch, 1) == 1)
        {
            rt_device_write(g_uart_device, 0, &ch, 1);
        }
    }
}

/**
 * @brief Initialize and start UART sample
 * @return RT_EOK on success, RT_ERROR otherwise
 */
static int uart_sample(void)
{
    rt_err_t result = RT_EOK;
    rt_thread_t thread;

    const char *welcome_msg = "RT-Thread MCX N236 UART5 Sample Started!\r\n";

    /* Find UART device */
    g_uart_device = rt_device_find(UART_DEVICE_NAME);
    if (!g_uart_device)
    {
        rt_kprintf("Failed to find %s device!\n", UART_DEVICE_NAME);
        return RT_ERROR;
    }

    /* Open UART device */
    result = rt_device_open(g_uart_device, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    if (result != RT_EOK)
    {
        rt_kprintf("Failed to open %s device!\n", UART_DEVICE_NAME);
        return result;
    }

    /* Initialize receive semaphore */
    result = rt_sem_init(&g_rx_sem, "rx_sem", 0, RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_kprintf("Failed to initialize receive semaphore!\n");
        return result;
    }

    /* Set receive callback */
    rt_device_set_rx_indicate(g_uart_device, uart_rx_callback);

    /* Send welcome message */
    rt_device_write(g_uart_device, 0, welcome_msg, rt_strlen(welcome_msg));

    /* Create UART processing thread */
    thread = rt_thread_create("uart_thread", uart_thread_entry, RT_NULL,
                              UART_THREAD_STACK, UART_THREAD_PRIORITY, UART_THREAD_TIMESLICE);
    if (thread != RT_NULL)
    {
        rt_kprintf("Starting UART processing thread...\n");
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("Failed to create UART processing thread!\n");
        result = RT_ERROR;
    }

    return result;
}

/* Export the initialization function to MSH */
MSH_CMD_EXPORT(uart_sample, Initialize UART5 sample);
