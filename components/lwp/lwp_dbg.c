#include <rtthread.h>
#include <rthw.h>
#include <lwp.h>

int dbg_thread_in_debug(void)
{
    int ret = 0;
    struct rt_lwp *lwp = lwp_self();

    if (lwp && lwp->debug)
    {
        ret = 1;
    }
    return ret;
}

struct dbg_ops_t *rt_dbg_ops = RT_NULL;
RTM_EXPORT(rt_dbg_ops);

void dbg_register(struct dbg_ops_t *dbg_ops)
{
    rt_dbg_ops = dbg_ops;
}
RTM_EXPORT(dbg_register);

static int dbg(int argc, char **argv)
{
    int ret = -1;

    if (rt_dbg_ops)
    {
        ret = rt_dbg_ops->dbg(argc, argv);
    }
    else
    {
        rt_kprintf("Error: DBG command is not enabled!\n");
    }
    return ret;
}
MSH_CMD_EXPORT(dbg, dbg);

uint32_t dbg_get_ins(void)
{
    uint32_t ins = 0;

    if (rt_dbg_ops)
    {
        ins = rt_dbg_ops->arch_get_ins();
    }
    return ins;
}

void dbg_activate_step(void)
{
    if (rt_dbg_ops)
    {
        rt_dbg_ops->arch_activate_step();
    }
}

void dbg_deactivate_step(void)
{
    if (rt_dbg_ops)
    {
        rt_dbg_ops->arch_deactivate_step();
    }
}

int dbg_check_event(struct rt_hw_exp_stack *regs, unsigned long esr)
{
    int ret = 0;

    if (rt_dbg_ops)
    {
        ret = rt_dbg_ops->check_debug_event(regs, esr);
    }
    return ret;
}

rt_channel_t gdb_server_channel(void)
{
    rt_channel_t ret = RT_NULL;

    if (rt_dbg_ops)
    {
        ret = rt_dbg_ops->gdb_get_server_channel();
    }
    return ret;
}

int dbg_step_type(void)
{
    int ret = 0;

    if (rt_dbg_ops)
    {
        ret = rt_dbg_ops->gdb_get_step_type();
    }
    return ret;
}

void dbg_attach_req(void *pc)
{
    if (rt_dbg_ops)
    {
        rt_dbg_ops->lwp_check_debug_attach_req(pc);
    }
}

int dbg_check_suspend(void)
{
    int ret = 0;

    if (rt_dbg_ops)
    {
        ret = rt_dbg_ops->lwp_check_debug_suspend();
    }
    return ret;
}
