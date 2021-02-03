#include "rtthread.h"
#include "headfile.h"

#pragma section all "cpu0_dsram"

void GPIO_Demo_init(void)
{
    /* configure P20.8 as general output */
    IfxPort_setPinMode(&MODULE_P20, 8,  IfxPort_Mode_outputPushPullGeneral);
    /* configure P20.9 as general output */
    IfxPort_setPinMode(&MODULE_P20, 9,  IfxPort_Mode_outputPushPullGeneral);
    /* configure P21.4 as general output */
    IfxPort_setPinMode(&MODULE_P21, 4,  IfxPort_Mode_outputPushPullGeneral);
    /* configure P21.5 as general output */
    IfxPort_setPinMode(&MODULE_P21, 5,  IfxPort_Mode_outputPushPullGeneral);
}

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
    GPIO_Demo_init();
    while(1)
    {
        rt_kprintf("hello rt-thread!\n");
        IfxPort_togglePin(&MODULE_P20, 8);
        IfxPort_togglePin(&MODULE_P20, 9);
        IfxPort_togglePin(&MODULE_P21, 4);
        IfxPort_togglePin(&MODULE_P21, 5);
        rt_thread_mdelay(1000);
    }
}

#pragma section all restore

