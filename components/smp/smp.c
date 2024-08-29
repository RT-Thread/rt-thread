#include "smp.h"
struct smp_call **global_work;

rt_err_t smp_call_handler(struct smp_event * event)
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
    struct smp_call *work,*tmp;
    int cur_cpu = rt_hw_cpu_id();
    rt_spin_lock(&global_work[cur_cpu]->lock);
    rt_list_for_each_entry_safe(work,tmp,&global_work[cur_cpu]->node,node)
    {
        if(work->event)
        {
            err = smp_call_handler(work->event);
            if(err)
                break;
            rt_list_remove(&work->node);
            rt_free(work);
        }
            
    }
    rt_spin_unlock(&global_work[cur_cpu]->lock);
    
}

void rt_smp_call_func_cond(int cpu_mask, smp_func func, void *data)
{
    rt_bool_t run_cur_cpu = RT_TRUE;
    rt_bool_t need_call = RT_TRUE;
    int cur_cpu = rt_hw_cpu_id();
    int cpuid = 1 << cur_cpu;
    int tmp_id = 0;
    int tmp_mask = cpu_mask;

    if(cpuid & ~cpu_mask)
        run_cur_cpu = RT_FALSE;

    if(run_cur_cpu)
        func(data);

    if(!(cpu_mask & cpuid))
        need_call = RT_FALSE;
    else
        cpu_mask = cpu_mask & (~cpuid);

    if(need_call)
    {
        while(tmp_mask)
        {
            if((tmp_mask & 1) && tmp_id < RT_CPUS_NR)
            {
                struct smp_event *event = rt_calloc(1, sizeof(struct smp_event));
                event->event_id = SMP_CALL_EVENT_FUNC;
                event->func = func;
                event->data = data;
                event->cpu_mask = cpu_mask;
                struct smp_call *work = rt_calloc(1, sizeof(struct smp_call));
                if(work == RT_NULL)
                    break;
                
                work->event = event;
                rt_spin_lock(&global_work[tmp_id]->lock);
                rt_list_insert_before(&global_work[tmp_id]->node, &work->node);
                rt_spin_unlock(&global_work[tmp_id]->lock);
            }
            tmp_id++;
            tmp_mask = tmp_mask >> 1;
        }
        rt_hw_ipi_send(RT_IPI_FUNC, cpu_mask);
    }
}

void smp_init(void)
{
    struct smp_call **work_list = (struct smp_call **)rt_malloc(sizeof(struct smp_call *));
    for(int i = 0; i < RT_CPUS_NR; i++)
    {        
        work_list[i] = rt_calloc(1, sizeof(struct smp_call));
        if(work_list[i] == RT_NULL)
            break;
        rt_list_init(&work_list[i]->node);
        rt_spin_lock_init(&work_list[i]->lock);
    }        
    global_work = work_list;
}

void test_call(void *data)
{
    rt_kprintf("call cpu id  = %d \n",rt_hw_cpu_id());
}
void test()
{
    int cpu_mask = 0xf;
    rt_smp_call_func_cond(cpu_mask,test_call, RT_NULL);

}
