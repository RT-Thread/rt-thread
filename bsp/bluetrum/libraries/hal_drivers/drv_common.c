#include "drv_common.h"

#define DRV_THREAD_PRIORITY         18
#define DRV_THREAD_STACK_SIZE       512
#define DRV_THREAD_TIMESLICE        5

enum {
    MSG_UART0_IRQ,
    MSG_UART1_IRQ,
    MSG_UART2_IRQ,
};

static rt_thread_t drv_tid = RT_NULL;
static rt_mq_t drv_mq = RT_NULL;

void uart0_irq_process(void);
void uart1_irq_process(void);

rt_section(".irq.uart")
void uart0_irq_post(void)
{
    rt_uint8_t mq_msg = MSG_UART0_IRQ;
    rt_mq_send(drv_mq, &mq_msg, 1);
}

rt_section(".irq.uart")
void uart1_irq_post(void)
{
    rt_uint8_t mq_msg = MSG_UART1_IRQ;
    rt_mq_send(drv_mq, &mq_msg, 1);
}

rt_section(".irq.uart")
void uart2_irq_post(void)
{
    rt_uint8_t mq_msg = MSG_UART2_IRQ;
    rt_mq_send(drv_mq, &mq_msg, 1);
}

static void drv_thread_entry(void *parameter)
{
    rt_uint8_t mq_msg = 0;
    while (1) {
        rt_mq_recv(drv_mq, &mq_msg, 1, RT_WAITING_FOREVER);
        switch (mq_msg) {
#ifdef BSP_USING_UART0
            case MSG_UART0_IRQ:
                uart0_irq_process();
                break;
#endif
#ifdef BSP_USING_UART1
            case MSG_UART1_IRQ:
                uart1_irq_process();
                break;
#endif
#ifdef BSP_USING_UART2
            case MSG_UART2_IRQ:
                uart2_irq_process();
                break;
#endif
            default:
                break;
        }
    }
}

static int drv_thread_init(void)
{
    drv_mq = rt_mq_create("drv", 1, 128, RT_IPC_FLAG_FIFO);
    drv_tid = rt_thread_create("drv",
            drv_thread_entry,
            RT_NULL,
            DRV_THREAD_STACK_SIZE,
            DRV_THREAD_PRIORITY,
            DRV_THREAD_TIMESLICE);

    if (drv_tid != RT_NULL)
        rt_thread_startup(drv_tid);
}
INIT_PREV_EXPORT(drv_thread_init);
