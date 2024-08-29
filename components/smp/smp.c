#include "smp.h"

#define DBG_TAG "SMP"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct smp_call global_work[RT_CPUS_NR];

rt_err_t smp_call_handler(struct smp_event *event)
{
    switch(event->event_id)
    {
    case SMP_CALL_EVENT_FUNC:
        event->func(event->data);
        break;
    default:
        rt_kprintf("error event id\n");
        return -RT_ERROR;
        break;
    }
    return RT_EOK;
}
void rt_smp_call_ipi_handler(int vector, void *param)
{
    int err;
    int cur_cpu = rt_hw_cpu_id();
    rt_spin_lock(&global_work[cur_cpu].lock);
    if(global_work[cur_cpu].event.event_id)
    {
        err = smp_call_handler(&global_work[cur_cpu].event);
        if(err)
        {
            LOG_E("Have no event\n");
            rt_memset(&global_work[cur_cpu].event,0,sizeof(struct smp_event));
            rt_spin_unlock(&global_work[cur_cpu].lock);
        }
        rt_memset(&global_work[cur_cpu].event,0,sizeof(struct smp_event));
    }
    rt_spin_unlock(&global_work[cur_cpu].lock);
    
}

void rt_smp_call_func_cond(int cpu_mask, smp_func func, void *data)
{
    RT_DEBUG_NOT_IN_INTERRUPT;
    struct smp_call work;
    struct smp_event event;
    rt_bool_t need_call = RT_TRUE;
    int cur_cpu = rt_hw_cpu_id();
    int cpuid = 1 << cur_cpu;
    int tmp_id = 0;
    int tmp_mask;

    if(cpuid & cpu_mask)
    {
        func(data);
        cpu_mask = cpu_mask & (~cpuid);
    }

    if(!cpu_mask)
        need_call = RT_FALSE;   

    tmp_mask = cpu_mask;
    if(need_call)
    {
        while(tmp_mask)
        {
            if((tmp_mask & 1) && (tmp_id < RT_CPUS_NR))
            {
                event.event_id = SMP_CALL_EVENT_FUNC;
                event.func = func;
                event.data = data;
                event.cpu_mask = cpu_mask;
                rt_spin_lock(&global_work[tmp_id].lock);
                global_work[tmp_id].event = event;
                rt_spin_unlock(&global_work[tmp_id].lock);
            }
            tmp_id++;
            tmp_mask = tmp_mask >> 1;
        }
        rt_hw_ipi_send(RT_IPI_FUNC, cpu_mask);
    }
}
struct rt_spinlock lock_1;
void smp_init(void)
{
    rt_spin_lock_init(&lock_1);
    for(int i = 0; i < RT_CPUS_NR; i++)
    {        
        rt_memset(&global_work[i],0,sizeof(struct smp_call));
        rt_spin_lock_init(&global_work[i].lock);
    }        
}

