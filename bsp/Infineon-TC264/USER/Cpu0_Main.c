#include "rtthread.h"
#include "headfile.h"

#pragma section all "cpu0_dsram"


int core0_main(void)
{
extern int rtthread_startup(void);
	disableInterrupts();
	get_clk();
	uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);

	rtthread_startup();

    rt_kprintf("Failed to start rt-thread.\n");

    while(1);
}

int main(void)
{
    while(1)
    {
        rt_thread_mdelay(1000);
        rt_kprintf("hello rt-thread!\n");
    }
}

#pragma section all restore

