#include "rtthread.h"

#include "xparameters.h"
#include "xscutimer.h"
#include "drv_timer.h"

#define APU_FREQ XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ
#define TIMER_DEVICE_ID XPAR_XSCUTIMER_0_DEVICE_ID

static  XScuTimer timers[2];
#define P_TIMER() (&timers[cpu_id])

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_int32_t cpu_id = rt_hw_cpu_id();

    rt_tick_increase();

    XScuTimer_ClearInterruptStatus(P_TIMER());
}

int rt_hw_timer_init(void)
{
    rt_int32_t cpu_id = rt_hw_cpu_id();

    XScuTimer_Config *cfg;
    s32 err;

    cfg = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
    RT_ASSERT(cfg);

    err = XScuTimer_CfgInitialize(P_TIMER(), cfg, cfg->BaseAddr);
    RT_ASSERT(err == XST_SUCCESS);

    err = XScuTimer_SelfTest(P_TIMER());
    RT_ASSERT(err == XST_SUCCESS);

    if (cpu_id == 0)
    {
        rt_hw_interrupt_install(TIMER_IRPT_INTR, rt_hw_timer_isr, RT_NULL, "tick");
    }
    rt_hw_interrupt_umask(TIMER_IRPT_INTR);
    XScuTimer_EnableInterrupt(P_TIMER());

    XScuTimer_LoadTimer(P_TIMER(), APU_FREQ/2/RT_TICK_PER_SECOND);
    XScuTimer_EnableAutoReload(P_TIMER());

    XScuTimer_Start(P_TIMER());

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);
