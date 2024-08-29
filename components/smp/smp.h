#ifndef __SMP_IPI_H__
#define __SMP_IPI_H__
#include <rtthread.h>
typedef void (*smp_func)(void *data);

#define SMP_CALL_EVENT_FUNC 0x1

struct smp_call
{
    struct rt_spinlock lock;
    struct rt_list_node node;
    struct smp_event *event;

};

struct smp_event
{
    int cpu_mask;
    int event_id;
    void *data;
    smp_func func;

};

void test();
void rt_smp_call_func_cond(int cpu_mask,smp_func func, void *data);
void rt_smp_call_ipi_handler(int vector, void *param);
void smp_init(void);

#endif