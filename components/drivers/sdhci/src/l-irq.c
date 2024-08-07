#include"sdhci-irq.h"
#include <pic.h>
struct irqaction
{
    irq_handler_t       handler;
    irq_handler_t       thread_fn;
    void            *dev_id;
    unsigned int        flags;
};

struct irq_desc
{
    struct irqaction    action[1];  /* IRQ action list */
    wait_queue_head_t       wait_for_threads;
    unsigned int        irq;

    void *rtthd;
};

static void irq_thread(void *p)
{
    struct irq_desc *desc = (struct irq_desc *)p;

    while (1)
    {
        struct irqaction *action;

        wait_event_interruptible(desc->wait_for_threads, 0);
        action = desc->action;

        action->thread_fn(desc->irq, action->dev_id);
    }
}

static irqreturn_t __irq_hander(int irq, void *id)
{
    irqreturn_t ret = IRQ_NONE;
    struct irq_desc *desc = (struct irq_desc*)id;
    struct irqaction *act;

    act = desc->action;
    if (act)
    {
        irq_handler_t       handler;

        handler = act->handler;
        if (handler)
        {
            ret = handler(desc->irq, act->dev_id);
            if (ret == IRQ_WAKE_THREAD)
            {
                wake_up(&desc->wait_for_threads);
            }
        }
        else
        {
            wake_up(&desc->wait_for_threads);
        }
    }

    return ret;
}


int irq_hw_register(unsigned int irq, irq_handler_t handler, void *id)
{
    rt_pic_attach_irq(irq, (rt_isr_handler_t)handler, id, "mmc", RT_IRQ_F_NONE);
    rt_pic_irq_unmask(irq);

    return 0;
}


const void *free_irq(unsigned int irq, void *d)
{
    return 0;
}

int request_threaded_irq(unsigned int irq, irq_handler_t handler,
                         irq_handler_t thread_fn,
                         unsigned long irqflags, const char *name, void *dev_id)
{
    struct irqaction *action;
    struct irq_desc *desc;
    int ret = 0;

    desc = rt_calloc(1, sizeof(struct irq_desc));
    if (!desc)
        return -ENOMEM;

    if (!handler)
    {
        if (!thread_fn)
            return -EINVAL;
    }

    action = desc->action;

    action->handler = handler;
    action->thread_fn = thread_fn;
    action->flags = irqflags;
    action->dev_id = dev_id;

    ret = irq_hw_register(irq, __irq_hander, desc);
    if (ret == 0)
    {
        init_waitqueue_head(&desc->wait_for_threads);
        desc->rtthd = rt_thread_create("irq", irq_thread, desc, 4096, 0, 20);
        if (desc->rtthd)
            rt_thread_startup(desc->rtthd);
    }

    return ret;
}
