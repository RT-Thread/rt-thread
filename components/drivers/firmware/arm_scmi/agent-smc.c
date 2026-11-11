/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rthw.h>

#include <mmu.h>
#include <smccc.h>
#include <cpuport.h>
#include <dt-bindings/size.h>

#define DBG_TAG "scmi.agent.smc"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "agent.h"

struct scmi_agent_smc
{
    int irq;
    rt_uint32_t func_id;

#define SHMEM_SIZE      (4 * SIZE_KB)
#define SHMEM_SHIFT     12
#define SHMEM_PAGE(x)   (((rt_ubase_t)(x) >> SHMEM_SHIFT))
#define SHMEM_OFFSET(x) ((x) & (SHMEM_SIZE - 1))
    rt_uint32_t param_page;
    rt_uint32_t param_offset;
    rt_ubase_t cap_id;

    rt_bool_t done;

    struct rt_spinlock lock;
    struct scmi_shared_mem *shmem;
};

static void scmi_agent_smc_isr(int irqno, void *param)
{
    struct scmi_agent_smc *asmc = param;

    HWREG32(&asmc->done) = RT_TRUE;
    rt_hw_dmb();
}

static rt_err_t scmi_agent_smc_setup(struct scmi_agent *agent,
        struct rt_device *dev)
{
    rt_err_t err;
    rt_uint64_t shm_addr, shm_size;
    struct rt_ofw_node *np = dev->ofw_node, *shmem_np;
    struct scmi_agent_smc *asmc = rt_calloc(1, sizeof(*asmc));

    if (!asmc)
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_ofw_prop_read_u32(np, "arm,smc-id", &asmc->func_id)))
    {
        goto _fail;
    }

    shmem_np = rt_ofw_parse_phandle(np, "shmem", 0);

    if (!rt_ofw_node_is_compatible(shmem_np, "arm,scmi-shmem"))
    {
        err = -RT_EINVAL;
        rt_ofw_node_put(shmem_np);

        goto _fail;
    }

    if ((err = rt_ofw_get_address(shmem_np, 0, &shm_addr, &shm_size)))
    {
        rt_ofw_node_put(shmem_np);
        goto _fail;
    }
    rt_ofw_node_put(shmem_np);

    asmc->shmem = rt_ioremap((void *)shm_addr, shm_size);

    if (!asmc->shmem)
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (rt_ofw_node_is_compatible(np, "qcom,scmi-smc"))
    {
        void *cap_id_map = (void *)asmc->shmem + (shm_size - 8);

        rt_memcpy(&asmc->cap_id, cap_id_map, sizeof(asmc->cap_id));
    }
    else
    {
        asmc->cap_id = ~0UL;
    }

    if (rt_ofw_node_is_compatible(np, "arm,scmi-smc-param"))
    {
        rt_ubase_t base = (rt_ubase_t)rt_kmem_v2p(asmc->shmem);

        asmc->param_page = SHMEM_PAGE(base);
        asmc->param_offset = SHMEM_OFFSET(base);
    }

    asmc->irq = rt_ofw_get_irq_by_name(np, "a2p");

    if (asmc->irq >= 0)
    {
        rt_hw_interrupt_install(asmc->irq, scmi_agent_smc_isr, asmc, "scmi");
        rt_hw_interrupt_umask(asmc->irq);
    }

    rt_spin_lock_init(&asmc->lock);

    agent->priv = asmc;

    return RT_EOK;

_fail:
    if (asmc->shmem)
    {
        rt_iounmap(asmc->shmem);
    }
    rt_free(asmc);

    return err;
}

static rt_err_t scmi_agent_smc_process_msg(struct scmi_agent *agent,
        struct rt_scmi_msg *msg)
{
    rt_err_t err;
    struct arm_smccc_res_t res;
    struct scmi_shared_mem *shmem;
    struct scmi_agent_smc *asmc = agent->priv;

    rt_spin_lock(&asmc->lock);

    if (asmc->irq >= 0)
    {
        while (HWREG32(&asmc->done))
        {
            rt_hw_cpu_relax();
        }
    }

    shmem = asmc->shmem;

    if ((err = scmi_shmem_msg_write(shmem, msg)))
    {
        goto _out_lock;
    }

    if (asmc->irq >= 0)
    {
        HWREG32(&asmc->done) = RT_FALSE;
    }

    if (asmc->cap_id == ~0UL)
    {
        arm_smccc_smc(asmc->func_id, asmc->param_page, asmc->param_offset,
                0, 0, 0, 0, 0, &res, RT_NULL);
    }
    else
    {
        arm_smccc_smc(asmc->func_id, asmc->cap_id,
                0, 0, 0, 0, 0, 0, &res, RT_NULL);
    }

    if (res.a0)
    {
        err = -RT_EIO;
    }
    else
    {
        err = scmi_shmem_msg_read(shmem, msg);
    }

    scmi_shmem_clear_channel(shmem);

_out_lock:
    rt_spin_unlock(&asmc->lock);

    return err;
}

struct scmi_agent_ops scmi_agent_smc_ops =
{
    .name = "smc",
    .setup = scmi_agent_smc_setup,
    .process_msg = scmi_agent_smc_process_msg,
};
