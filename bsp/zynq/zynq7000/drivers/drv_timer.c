#include "rtthread.h"

#include "xparameters.h"
#include "xscutimer.h"

#define APU_FREQ XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ
#define TIMER_DEVICE_ID XPAR_XSCUTIMER_0_DEVICE_ID
#define TIMER_IRPT_INTR XPAR_SCUTIMER_INTR

static  XScuTimer timer;

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_tick_increase();

    XScuTimer_ClearInterruptStatus(&timer);
}

int rt_hw_timer_init(void)
{
    XScuTimer_Config *cfg;
    s32 err;

    cfg = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
    RT_ASSERT(cfg);

    err = XScuTimer_CfgInitialize(&timer, cfg, cfg->BaseAddr);
    RT_ASSERT(err == XST_SUCCESS);

    err = XScuTimer_SelfTest(&timer);
    RT_ASSERT(err == XST_SUCCESS);

    rt_hw_interrupt_install(TIMER_IRPT_INTR, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(TIMER_IRPT_INTR);
    XScuTimer_EnableInterrupt(&timer);

    XScuTimer_LoadTimer(&timer, APU_FREQ/2/RT_TICK_PER_SECOND);
    XScuTimer_EnableAutoReload(&timer);

    XScuTimer_Start(&timer);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);
