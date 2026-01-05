#include <rtthread.h>

#define TX_UART_NAME   "uart3"

static rt_device_t tx_serial = RT_NULL;

/* 发送任务入口函数 */
static void serial_tx_thread(void *parameter)
{
    char msg[] = "hello RT-Thread!\r\n";

    while (1)
    {
        rt_device_write(tx_serial, 0, msg, sizeof(msg) - 1);
        rt_thread_mdelay(500);   /* 每 500ms 发一次 */
    }
}

/* 初始化函数，在系统启动完成后自动运行 */
int uart3_tx_init(void)
{
    /* 查找 uart3 设备 */
    tx_serial = rt_device_find(TX_UART_NAME);
    if (tx_serial == RT_NULL)
    {
        rt_kprintf("Cannot find %s device!\n", TX_UART_NAME);
        return -1;
    }

    /* 打开设备（仅发送，不需要接收） */
    rt_device_open(tx_serial, RT_DEVICE_FLAG_WRONLY);

    /* 创建线程 */
    rt_thread_t tid = rt_thread_create(
        "uart3_tx",           /* 线程名 */
        serial_tx_thread,     /* 入口函数 */
        RT_NULL,              /* 参数 */
        1024,                 /* 栈大小 */
        20,                   /* 优先级 */
        10                    /* 时间片 */
    );

    if (tid != RT_NULL)
        rt_thread_startup(tid);
    else
        rt_kprintf("Create uart3_tx thread failed!\n");

    return 0;
}
//INIT_APP_EXPORT(uart3_tx_init);
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(uart3_tx_init, uart3 device test);
