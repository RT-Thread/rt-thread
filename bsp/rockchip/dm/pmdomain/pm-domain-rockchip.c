/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <cpuport.h>

#define DBG_TAG "pm-domain.rockchip"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <dt-bindings/power/px30-power.h>
#include <dt-bindings/power/rk1808-power.h>
#include <dt-bindings/power/rk3036-power.h>
#include <dt-bindings/power/rk3066-power.h>
#include <dt-bindings/power/rk3128-power.h>
#include <dt-bindings/power/rk3188-power.h>
#include <dt-bindings/power/rk3228-power.h>
#include <dt-bindings/power/rk3288-power.h>
#include <dt-bindings/power/rk3328-power.h>
#include <dt-bindings/power/rk3366-power.h>
#include <dt-bindings/power/rk3368-power.h>
#include <dt-bindings/power/rk3399-power.h>
#include <dt-bindings/power/rk3528-power.h>
#include <dt-bindings/power/rk3562-power.h>
#include <dt-bindings/power/rk3568-power.h>
#include <dt-bindings/power/rk3576-power.h>
#include <dt-bindings/power/rk3588-power.h>
#include <dt-bindings/power/rv1126-power.h>

struct rockchip_domain_info
{
    const char *name;
    int pwr_mask;
    int status_mask;
    int req_mask;
    int idle_mask;
    int ack_mask;
    rt_bool_t active_wakeup;
    int pwr_w_mask;
    int req_w_mask;
    int mem_status_mask;
    int repair_status_mask;
    int clk_ungate_mask;
    int clk_ungate_w_mask;
    int mem_num;
    rt_bool_t keepon_startup;
    rt_bool_t always_on;
    rt_uint32_t pwr_offset;
    rt_uint32_t mem_offset;
    rt_uint32_t req_offset;
    rt_uint32_t clk_ungate_offset;
    rt_uint32_t delay_us;
};

enum soc_type
{
    SOC_TYPE_ALL = 0,
    SOC_TYPE_PX30,
};

struct rockchip_pmu_info
{
    enum soc_type type;

    rt_uint32_t pwr_offset;
    rt_uint32_t status_offset;
    rt_uint32_t req_offset;
    rt_uint32_t idle_offset;
    rt_uint32_t ack_offset;
    rt_uint32_t mem_pwr_offset;
    rt_uint32_t chain_status_offset;
    rt_uint32_t mem_status_offset;
    rt_uint32_t repair_status_offset;
    rt_uint32_t clk_ungate_offset;
    rt_uint32_t mem_sd_offset;

    rt_uint32_t core_pwrcnt_offset;
    rt_uint32_t gpu_pwrcnt_offset;

    unsigned int core_power_transition_time;
    unsigned int gpu_power_transition_time;

    int num_domains;
    const struct rockchip_domain_info *domain_info;
};

#define DOMAIN(NAME, PWR, STATUS, REQ, IDLE, ACK, WAKEUP, KEEPON) \
{                               \
    .name = NAME,               \
    .pwr_mask = (PWR),          \
    .status_mask = (STATUS),    \
    .req_mask = (REQ),          \
    .idle_mask = (IDLE),        \
    .ack_mask = (ACK),          \
    .active_wakeup = WAKEUP,    \
    .keepon_startup = KEEPON,   \
}

#define DOMAIN_M(NAME, PWR, STATUS, REQ, IDLE, ACK, WAKEUP, KEEPON) \
{                               \
    .name = NAME,               \
    .pwr_w_mask = (PWR) << 16,  \
    .pwr_mask = (PWR),          \
    .status_mask = (STATUS),    \
    .req_w_mask = (REQ) << 16,  \
    .req_mask = (REQ),          \
    .idle_mask = (IDLE),        \
    .ack_mask = (ACK),          \
    .active_wakeup = WAKEUP,    \
    .keepon_startup = KEEPON,   \
}

#define DOMAIN_M_A(PWR, STATUS, REQ, IDLE, ACK, ALWAYS, WAKEUP, KEEPON) \
{                               \
    .pwr_w_mask = (PWR) << 16,  \
    .pwr_mask = (PWR),          \
    .status_mask = (STATUS),    \
    .req_w_mask = (REQ) << 16,  \
    .req_mask = (REQ),          \
    .idle_mask = (IDLE),        \
    .ack_mask = (ACK),          \
    .always_on = ALWAYS,        \
    .active_wakeup = WAKEUP,    \
    .keepon_startup = KEEPON,   \
}

#define DOMAIN_M_C_SD(NAME, PWR, STATUS, REQ, IDLE, ACK, CLK, MEM, WAKEUP, KEEPON) \
{                                       \
    .name = NAME,                       \
    .pwr_w_mask = (PWR) << 16,          \
    .pwr_mask = (PWR),                  \
    .status_mask = (STATUS),            \
    .req_w_mask = (REQ) << 16,          \
    .req_mask = (REQ),                  \
    .idle_mask = (IDLE),                \
    .ack_mask = (ACK),                  \
    .clk_ungate_mask = (CLK),           \
    .clk_ungate_w_mask = (CLK) << 16,   \
    .mem_num = (MEM),                   \
    .active_wakeup = WAKEUP,            \
    .keepon_startup = KEEPON,           \
}

#define DOMAIN_M_O(NAME, PWR, STATUS, P_OFFSET, REQ, IDLE, ACK, R_OFFSET, WAKEUP, KEEPON) \
{                               \
    .name = NAME,               \
    .pwr_w_mask = (PWR) << 16,  \
    .pwr_mask = (PWR),          \
    .status_mask = (STATUS),    \
    .req_w_mask = (REQ) << 16,  \
    .req_mask = (REQ),          \
    .idle_mask = (IDLE),        \
    .ack_mask = (ACK),          \
    .active_wakeup = WAKEUP,    \
    .keepon_startup = KEEPON,   \
    .pwr_offset = P_OFFSET,     \
    .req_offset = R_OFFSET,     \
}

#define DOMAIN_M_O_R(NAME, P_OFF, PWR, STATUS, M_OFF, M_STATUS, R_STATUS, R_OFF, REQ, IDLE, ACK, WAKEUP, KEEPON) \
{                                       \
    .name = NAME,                       \
    .pwr_offset = P_OFF,                \
    .pwr_w_mask = (PWR) << 16,          \
    .pwr_mask = (PWR),                  \
    .status_mask = (STATUS),            \
    .mem_offset = M_OFF,                \
    .mem_status_mask = (M_STATUS),      \
    .repair_status_mask = (R_STATUS),   \
    .req_offset = R_OFF,                \
    .req_w_mask = (REQ) << 16,          \
    .req_mask = (REQ),                  \
    .idle_mask = (IDLE),                \
    .ack_mask = (ACK),                  \
    .active_wakeup = WAKEUP,            \
    .keepon_startup = KEEPON,           \
}

#define DOMAIN_M_O_R_G(NAME, P_OFF, PWR, STATUS, R_STATUS, R_OFFSET, REQ, IDLE, ACK, G_MASK, DELAY, WAKEUP, KEEPON) \
{                                       \
    .name = NAME,                       \
    .pwr_offset = P_OFF,                \
    .pwr_w_mask = (PWR) << 16,          \
    .pwr_mask = (PWR),                  \
    .status_mask = (STATUS),            \
    .mem_status_mask = (R_STATUS),      \
    .repair_status_mask = (R_STATUS),   \
    .req_offset = R_OFFSET,             \
    .req_w_mask = (REQ) << 16,          \
    .req_mask = (REQ),                  \
    .idle_mask = (IDLE),                \
    .ack_mask = (ACK),                  \
    .clk_ungate_offset = R_OFFSET,      \
    .clk_ungate_mask = (G_MASK),        \
    .clk_ungate_w_mask = (G_MASK) << 16,\
    .delay_us = DELAY,                  \
    .active_wakeup = WAKEUP,            \
    .keepon_startup = KEEPON,           \
}

#define MAX_QOS_REGS_NUM    5
#define QOS_PRIORITY        0x08
#define QOS_MODE            0x0c
#define QOS_BANDWIDTH       0x10
#define QOS_SATURATION      0x14
#define QOS_EXTCONTROL      0x18
#define SHAPING_NBPKTMAX0   0x0

struct rockchip_pmu;

struct rockchip_pm_domain
{
    struct rt_dm_power_domain parent;

    const struct rockchip_domain_info *info;
    struct rockchip_pmu *pmu;
    struct rt_ofw_node *np;

    int num_qos;
    int num_shaping;
    struct rt_syscon **qos_regmaps;
    struct rt_syscon **shaping_regmaps;

    rt_uint32_t *qos_save_regs[MAX_QOS_REGS_NUM];
    rt_uint32_t *shaping_save_regs;

    rt_bool_t *qos_is_need_init[MAX_QOS_REGS_NUM];
    rt_bool_t *shaping_is_need_init;

    struct rt_clk_array *clk_arr;

    rt_bool_t is_ignore_pwr;
    rt_bool_t is_qos_saved;
    rt_bool_t is_qos_need_init;
    rt_bool_t is_shaping_need_init;
    struct rt_regulator *supply;
};

#define raw_to_rockchip_pm_domain(raw) rt_container_of(raw, struct rockchip_pm_domain, parent)

struct rockchip_pmu
{
    struct rt_dm_power_domain_proxy parent;
    struct rt_device *dev;

    struct rt_syscon *regmap;
    const struct rockchip_pmu_info *info;

    struct rockchip_pm_domain rk_pmdomains[];
};

#define raw_to_rockchip_pmu(raw) rt_container_of(raw, struct rockchip_pmu, parent)

#define read_uxx_poll_timeout(OP, PD, VAL, COND, DELAY_US, TIMEOUT_US) \
({                                                      \
    rt_uint64_t timeout_us = TIMEOUT_US;                \
    rt_int64_t left_ns = timeout_us * 1000L;            \
    rt_ubase_t delay_us = DELAY_US;                     \
    rt_uint64_t delay_ns = delay_us * 1000L;            \
    for (;;)                                            \
    {                                                   \
        (VAL) = OP(PD);                                 \
        if (COND)                                       \
        {                                               \
            break;                                      \
        }                                               \
        if (timeout_us && left_ns < 0)                  \
        {                                               \
            (VAL) = OP(PD);                             \
            break;                                      \
        }                                               \
        if (delay_us)                                   \
        {                                               \
            rt_hw_us_delay(delay_us);                   \
            if (timeout_us)                             \
            {                                           \
                left_ns -= delay_ns;                    \
            }                                           \
        }                                               \
        rt_hw_cpu_relax();                              \
        if (timeout_us)                                 \
        {                                               \
            --left_ns;                                  \
        }                                               \
    }                                                   \
    (COND) ? RT_EOK : -RT_ETIMEOUT;                     \
})

static rt_bool_t rockchip_pmu_domain_is_idle(struct rockchip_pm_domain *rk_domain)
{
    rt_uint32_t val;
    struct rockchip_pmu *pmu = rk_domain->pmu;
    const struct rockchip_domain_info *domain_info = rk_domain->info;

    rt_syscon_read(pmu->regmap, pmu->info->idle_offset, &val);

    return (val & domain_info->idle_mask) == domain_info->idle_mask;
}

static rt_uint32_t rockchip_pmu_read_ack(struct rockchip_pmu *pmu)
{
    rt_uint32_t val;

    rt_syscon_read(pmu->regmap, pmu->info->ack_offset, &val);

    return val;
}

static rt_err_t rockchip_pmu_ungate_clk(struct rockchip_pm_domain *rk_domain,
        rt_bool_t ungate)
{
    rt_uint32_t val;
    struct rockchip_pmu *pmu = rk_domain->pmu;
    const struct rockchip_domain_info *domain_info = rk_domain->info;

    if (!domain_info->clk_ungate_mask)
    {
        return RT_EOK;
    }

    if (!pmu->info->clk_ungate_offset)
    {
        return RT_EOK;
    }

    val = domain_info->clk_ungate_w_mask;

    if (ungate)
    {
        val |= domain_info->clk_ungate_mask;
    }

    rt_syscon_write(pmu->regmap, pmu->info->clk_ungate_offset + domain_info->clk_ungate_offset, val);

    return RT_EOK;
}

static rt_err_t rockchip_pmu_mem_shut_down(struct rockchip_pm_domain *rk_domain,
        rt_bool_t sd)
{
    struct rockchip_pmu *pmu = rk_domain->pmu;
    const struct rockchip_domain_info *domain_info = rk_domain->info;

    if (!domain_info->mem_num)
    {
        return RT_EOK;
    }

    if (!pmu->info->mem_sd_offset)
    {
        return RT_EOK;
    }

    for (int i = 0; i < domain_info->mem_num; ++i)
    {
        rt_syscon_write(pmu->regmap, pmu->info->mem_sd_offset,
                ((!!sd) << i) | (1 << (i + 16)));
    }

    return RT_EOK;
}

static rt_err_t rockchip_pmu_set_idle_request(struct rockchip_pm_domain *rk_domain,
        rt_bool_t idle)
{
    rt_err_t err;
    rt_bool_t is_idle;
    rt_uint32_t val, target_ack, domain_req_offset;
    struct rockchip_pmu *pmu = rk_domain->pmu;
    const struct rockchip_domain_info *domain_info = rk_domain->info;

    domain_req_offset = domain_info->req_offset;

    if (domain_info->req_mask == 0)
    {
        return RT_EOK;
    }
    else if (domain_info->req_w_mask)
    {
        rt_syscon_write(pmu->regmap, pmu->info->req_offset + domain_req_offset,
                idle ? (domain_info->req_mask | domain_info->req_w_mask) :
                        domain_info->req_w_mask);
    }
    else
    {
        rt_syscon_update_bits(pmu->regmap, pmu->info->req_offset + domain_req_offset,
                domain_info->req_mask, idle ? RT_UINT32_MAX : 0);
    }

    rt_hw_wmb();

    /* Wait util idle_ack = 1 */
    target_ack = idle ? domain_info->ack_mask : 0;
    err = read_uxx_poll_timeout(rockchip_pmu_read_ack, pmu, val,
            (val & domain_info->ack_mask) == target_ack, 0, 10000);

    if (err)
    {
        LOG_E("Failed to get ack on domain '%s' = %d",
                rt_ofw_node_full_name(rk_domain->np), val);
        return err;
    }

    err = read_uxx_poll_timeout(rockchip_pmu_domain_is_idle, rk_domain,
                    is_idle, is_idle == idle, 0, 10000);
    if (err)
    {
        LOG_E("Failed to set idle on domain '%s' = %d",
                rt_ofw_node_full_name(rk_domain->np), is_idle);
        return err;
    }

    return RT_EOK;
}

static rt_err_t rockchip_pmu_save_shaping(struct rockchip_pm_domain *rk_domain)
{
    for (int i = 0; i < rk_domain->num_shaping; ++i)
    {
        rt_syscon_read(rk_domain->shaping_regmaps[i], SHAPING_NBPKTMAX0,
                &rk_domain->shaping_save_regs[i]);
    }

    return RT_EOK;
}

static rt_err_t rockchip_pmu_restore_shaping(struct rockchip_pm_domain *rk_domain)
{
    for (int i = 0; i < rk_domain->num_shaping; ++i)
    {
        rt_syscon_write(rk_domain->shaping_regmaps[i], SHAPING_NBPKTMAX0,
                rk_domain->shaping_save_regs[i]);
    }

    return RT_EOK;
}

static rt_err_t rockchip_pmu_save_qos(struct rockchip_pm_domain *rk_domain)
{
    for (int i = 0; i < rk_domain->num_qos; ++i)
    {
        rt_syscon_read(rk_domain->qos_regmaps[i], QOS_PRIORITY,
                &rk_domain->qos_save_regs[0][i]);
        rt_syscon_read(rk_domain->qos_regmaps[i], QOS_MODE,
                &rk_domain->qos_save_regs[1][i]);
        rt_syscon_read(rk_domain->qos_regmaps[i], QOS_BANDWIDTH,
                &rk_domain->qos_save_regs[2][i]);
        rt_syscon_read(rk_domain->qos_regmaps[i], QOS_SATURATION,
                &rk_domain->qos_save_regs[3][i]);
        rt_syscon_read(rk_domain->qos_regmaps[i], QOS_EXTCONTROL,
                &rk_domain->qos_save_regs[4][i]);
    }

    return rockchip_pmu_save_shaping(rk_domain);
}

static rt_err_t rockchip_pmu_restore_qos(struct rockchip_pm_domain *rk_domain)
{
    for (int i = 0; i < rk_domain->num_qos; ++i)
    {
        rt_syscon_write(rk_domain->qos_regmaps[i], QOS_PRIORITY,
                rk_domain->qos_save_regs[0][i]);
        rt_syscon_write(rk_domain->qos_regmaps[i], QOS_MODE,
                rk_domain->qos_save_regs[1][i]);
        rt_syscon_write(rk_domain->qos_regmaps[i], QOS_BANDWIDTH,
                rk_domain->qos_save_regs[2][i]);
        rt_syscon_write(rk_domain->qos_regmaps[i], QOS_SATURATION,
                rk_domain->qos_save_regs[3][i]);
        rt_syscon_write(rk_domain->qos_regmaps[i], QOS_EXTCONTROL,
                rk_domain->qos_save_regs[4][i]);
    }

    return rockchip_pmu_restore_shaping(rk_domain);
}

static void rockchip_pmu_init_shaping(struct rockchip_pm_domain *rk_domain)
{
    if (!rk_domain->is_shaping_need_init)
    {
        return;
    }

    for (int i = 0; i < rk_domain->num_shaping; ++i)
    {
        if (rk_domain->shaping_is_need_init[i])
        {
            rt_syscon_write(rk_domain->shaping_regmaps[i], SHAPING_NBPKTMAX0,
                    rk_domain->shaping_save_regs[i]);
        }
    }

    rt_free(rk_domain->shaping_is_need_init);
    rk_domain->shaping_is_need_init = RT_NULL;
    rk_domain->is_shaping_need_init = RT_FALSE;
}

static void rockchip_pmu_init_qos(struct rockchip_pm_domain *rk_domain)
{
    rockchip_pmu_init_shaping(rk_domain);

    if (!rk_domain->is_qos_need_init)
    {
        return;
    }

    for (int i = 0; i < rk_domain->num_qos; ++i)
    {
        if (rk_domain->qos_is_need_init[0][i])
        {
            rt_syscon_write(rk_domain->qos_regmaps[i], QOS_PRIORITY,
                    rk_domain->qos_save_regs[0][i]);
        }

        if (rk_domain->qos_is_need_init[1][i])
        {
            rt_syscon_write(rk_domain->qos_regmaps[i], QOS_MODE,
                    rk_domain->qos_save_regs[1][i]);
        }

        if (rk_domain->qos_is_need_init[2][i])
        {
            rt_syscon_write(rk_domain->qos_regmaps[i], QOS_BANDWIDTH,
                    rk_domain->qos_save_regs[2][i]);
        }

        if (rk_domain->qos_is_need_init[3][i])
        {
            rt_syscon_write(rk_domain->qos_regmaps[i], QOS_SATURATION,
                    rk_domain->qos_save_regs[3][i]);
        }

        if (rk_domain->qos_is_need_init[4][i])
        {
            rt_syscon_write(rk_domain->qos_regmaps[i], QOS_EXTCONTROL,
                    rk_domain->qos_save_regs[4][i]);
        }
    }

    rt_free(rk_domain->qos_is_need_init[0]);
    rk_domain->qos_is_need_init[0] = RT_NULL;
    rk_domain->is_qos_need_init = RT_FALSE;
}

static rt_bool_t rockchip_pmu_domain_is_on(struct rockchip_pm_domain *rk_domain)
{
    rt_uint32_t val;
    struct rockchip_pmu *pmu = rk_domain->pmu;

    if (rk_domain->info->repair_status_mask)
    {
        rt_syscon_read(pmu->regmap, pmu->info->repair_status_offset, &val);

        /* 1'b1: power on, 1'b0: power off */
        return !!(val & rk_domain->info->repair_status_mask);
    }

    /* check idle status for idle-only domains */
    if (rk_domain->info->status_mask == 0)
    {
        return !rockchip_pmu_domain_is_idle(rk_domain);
    }

    rt_syscon_read(pmu->regmap, pmu->info->status_offset, &val);

    /* 1'b0: power on, 1'b1: power off */
    return !(val & rk_domain->info->status_mask);
}

static bool rockchip_pmu_domain_is_mem_on(struct rockchip_pm_domain *rk_domain)
{
    rt_uint32_t val;
    struct rockchip_pmu *pmu = rk_domain->pmu;

    rt_syscon_read(pmu->regmap, pmu->info->mem_status_offset + rk_domain->info->mem_offset, &val);

    /* 1'b0: power on, 1'b1: power off */
    return !(val & rk_domain->info->mem_status_mask);
}

static rt_bool_t rockchip_pmu_domain_is_chain_on(struct rockchip_pm_domain *rk_domain)
{
    rt_uint32_t val;
    struct rockchip_pmu *pmu = rk_domain->pmu;

    rt_syscon_read(pmu->regmap, pmu->info->chain_status_offset + rk_domain->info->mem_offset, &val);

    /* 1'b1: power on, 1'b0: power off */
    return val & rk_domain->info->mem_status_mask;
}

static rt_err_t rockchip_pmu_domain_mem_reset(struct rockchip_pm_domain *rk_domain)
{
    rt_bool_t is_on;
    rt_err_t err = 0;
    struct rockchip_pmu *pmu = rk_domain->pmu;

    err = read_uxx_poll_timeout(rockchip_pmu_domain_is_chain_on, rk_domain,
            is_on, is_on == RT_TRUE, 0, 10000);

    if (err)
    {
        LOG_E("Failed to get chain status '%s', target_on = %s, is %s",
                rt_ofw_node_full_name(rk_domain->np), "1", is_on ? "on" : "off");
        goto _err;
    }

    rt_hw_us_delay(60);

    rt_syscon_write(pmu->regmap, pmu->info->mem_pwr_offset + rk_domain->info->pwr_offset,
             (rk_domain->info->pwr_mask | rk_domain->info->pwr_w_mask));
    rt_hw_wmb();

    err = read_uxx_poll_timeout(rockchip_pmu_domain_is_mem_on, rk_domain,
            is_on, is_on == RT_FALSE, 0, 10000);

    if (err)
    {
        LOG_E("Failed to get mem status '%s', target_on = %s, is %s",
                rt_ofw_node_full_name(rk_domain->np), "0", is_on ? "on" : "off");
        goto _err;
    }

    rt_syscon_write(pmu->regmap, pmu->info->mem_pwr_offset + rk_domain->info->pwr_offset,
            rk_domain->info->pwr_w_mask);
    rt_hw_wmb();

    err = read_uxx_poll_timeout(rockchip_pmu_domain_is_mem_on, rk_domain,
            is_on, is_on == RT_TRUE, 0, 10000);

    if (err)
    {
        LOG_E("Failed to get mem status '%s', target_on = %s, is %s",
                rt_ofw_node_full_name(rk_domain->np), "1", is_on ? "on" : "off");
    }

_err:
    return err;
}

static rt_err_t rockchip_do_pmu_set_power_domain(struct rockchip_pm_domain *rk_domain,
        rt_bool_t on)
{
    rt_err_t err;
    rt_uint32_t pd_pwr_offset;
    rt_bool_t is_on, is_mem_on = RT_FALSE;
    struct rockchip_pmu *pmu = rk_domain->pmu;

    pd_pwr_offset = rk_domain->info->pwr_offset;

    if (rk_domain->info->pwr_mask == 0)
    {
        return RT_EOK;
    }

    if (on && rk_domain->info->mem_status_mask)
    {
        is_mem_on = rockchip_pmu_domain_is_mem_on(rk_domain);
    }

    if (rk_domain->info->pwr_w_mask)
    {
        rt_syscon_write(pmu->regmap, pmu->info->pwr_offset + pd_pwr_offset,
                on ? rk_domain->info->pwr_w_mask :
                        (rk_domain->info->pwr_mask | rk_domain->info->pwr_w_mask));
    }
    else
    {
        rt_syscon_update_bits(pmu->regmap, pmu->info->pwr_offset + pd_pwr_offset,
                rk_domain->info->pwr_mask, on ? 0 : RT_UINT32_MAX);
    }

    rt_hw_wmb();

    if (is_mem_on && (err = rockchip_pmu_domain_mem_reset(rk_domain)))
    {
        return err;
    }

    if (read_uxx_poll_timeout(rockchip_pmu_domain_is_on, rk_domain,
            is_on, is_on == on, 0, 10000))
    {
        LOG_E("Failed to set domain '%s', is %s",
                rt_ofw_node_full_name(rk_domain->np), is_on ? "on" : "off");
        return -RT_ETIMEOUT;
    }

    return RT_EOK;
}

static rt_err_t rockchip_pm_domain_power(struct rockchip_pm_domain *rk_pmdomain,
        rt_bool_t power_on)
{
    rt_err_t err = RT_EOK;
    const struct rockchip_pmu_info *pmu_info = rk_pmdomain->pmu->info;
    const struct rockchip_domain_info *domain_info = rk_pmdomain->info;

    if (!power_on && pmu_info->type == SOC_TYPE_PX30 &&
        rt_ofw_machine_is_compatible("rockchip,px30s"))
    {
        if (domain_info->name && !rt_strcmp(domain_info->name, "gpu"))
        {
            return RT_EOK;
        }
    }

    if (rockchip_pmu_domain_is_on(rk_pmdomain) != power_on)
    {
        if (!rk_pmdomain->supply)
        {
            rk_pmdomain->supply = rt_regulator_get(rk_pmdomain->pmu->dev,
                    domain_info->name);

            if (!rk_pmdomain->supply)
            {
                rk_pmdomain->supply = rt_err_ptr(-RT_ENOSYS);
            }
        }

        if (power_on && !rt_is_err(rk_pmdomain->supply))
        {
            if ((err = rt_regulator_enable(rk_pmdomain->supply)))
            {
                return err;
            }
        }

        if (rk_pmdomain->clk_arr)
        {
            if ((err = rt_clk_array_enable(rk_pmdomain->clk_arr)))
            {
                LOG_E("Enable clocks error = %s", rt_strerror(err));
                return err;
            }
        }
        rockchip_pmu_ungate_clk(rk_pmdomain, RT_TRUE);

        if (!power_on)
        {
            rockchip_pmu_save_qos(rk_pmdomain);
            rk_pmdomain->is_qos_saved = RT_TRUE;

            /* if powering down, idle request to NIU first */
            if ((err = rockchip_pmu_set_idle_request(rk_pmdomain, RT_TRUE)))
            {
                goto _out;
            }

            rockchip_pmu_mem_shut_down(rk_pmdomain, RT_TRUE);
        }

        if ((err = rockchip_do_pmu_set_power_domain(rk_pmdomain, power_on)))
        {
            goto _out;
        }

        if (power_on)
        {
            rockchip_pmu_mem_shut_down(rk_pmdomain, RT_FALSE);

            /* if powering up, leave idle mode */
            if ((err = rockchip_pmu_set_idle_request(rk_pmdomain, RT_FALSE)))
            {
                goto _out;
            }

            if (domain_info->delay_us)
            {
                rt_hw_us_delay(domain_info->delay_us);
            }
            if (rk_pmdomain->is_qos_saved)
            {
                rockchip_pmu_restore_qos(rk_pmdomain);
            }
            if (rk_pmdomain->is_qos_need_init || rk_pmdomain->is_shaping_need_init)
            {
                rockchip_pmu_init_qos(rk_pmdomain);
            }
        }

    _out:
        rockchip_pmu_ungate_clk(rk_pmdomain, RT_FALSE);

        if (rk_pmdomain->clk_arr)
        {
            rt_clk_array_disable(rk_pmdomain->clk_arr);
        }

        if (!power_on && !rt_is_err(rk_pmdomain->supply))
        {
            err = rt_regulator_disable(rk_pmdomain->supply);
        }
    }

    return err;
}

static rt_err_t rockchip_pd_power_on(struct rt_dm_power_domain *domain)
{
    struct rockchip_pm_domain *rk_pmdomain = raw_to_rockchip_pm_domain(domain);

    if (rk_pmdomain->is_ignore_pwr)
    {
        return RT_EOK;
    }

    return rockchip_pm_domain_power(rk_pmdomain, RT_TRUE);
}

static rt_err_t rockchip_pd_power_off(struct rt_dm_power_domain *domain)
{
    struct rockchip_pm_domain *rk_pmdomain = raw_to_rockchip_pm_domain(domain);

    if (rk_pmdomain->is_ignore_pwr)
    {
        return RT_EOK;
    }

    return rockchip_pm_domain_power(rk_pmdomain, RT_FALSE);
}

static rt_err_t rockchip_pm_get_shaping(struct rockchip_pm_domain *rk_domain,
        struct rt_ofw_node *np)
{
    struct rt_ofw_node *snp;

    rk_domain->num_shaping = rt_ofw_count_phandle_cells(np, "pm_shaping", RT_NULL);

    if (rk_domain->num_shaping > 0)
    {
        rk_domain->shaping_regmaps = rt_calloc(rk_domain->num_shaping,
                sizeof(*rk_domain->shaping_regmaps));

        if (!rk_domain->shaping_regmaps)
        {
            return -RT_ENOMEM;
        }

        rk_domain->shaping_save_regs = rt_malloc(sizeof(rt_uint32_t) *
                rk_domain->num_shaping);

        if (!rk_domain->shaping_save_regs)
        {
            return -RT_ENOMEM;
        }

        rk_domain->shaping_is_need_init = rt_calloc(rk_domain->num_shaping,
                sizeof(rt_bool_t));

        for (int i = 0; i < rk_domain->num_shaping; ++i)
        {
            rt_uint32_t val;

            snp = rt_ofw_parse_phandle(np, "pm_shaping", i);

            if (!snp)
            {
                return -RT_EINVAL;
            }

            rk_domain->shaping_regmaps[i] = rt_syscon_find_by_ofw_node(snp);
            rt_ofw_node_put(snp);

            if (!rk_domain->shaping_regmaps[i])
            {
                return -RT_EINVAL;
            }

            if (!rt_ofw_prop_read_u32(snp, "shaping-init", &val))
            {
                rk_domain->shaping_save_regs[i] = val;
                rk_domain->shaping_is_need_init[i] = RT_TRUE;
                rk_domain->is_shaping_need_init = RT_TRUE;
            }
        }
    }

    return RT_EOK;
}

static void rockchip_pm_qos_init(struct rockchip_pm_domain *rk_domain)
{
    rt_err_t err;

    if (!rk_domain->is_qos_need_init)
    {
        rt_free(rk_domain->qos_is_need_init[0]);
        rk_domain->qos_is_need_init[0] = RT_NULL;
    }

    if (!rk_domain->is_shaping_need_init)
    {
        rt_free(rk_domain->shaping_is_need_init);
        rk_domain->shaping_is_need_init = RT_NULL;
    }

    if (!rk_domain->is_qos_need_init && !rk_domain->is_shaping_need_init)
    {
        return;
    }

    if (rockchip_pmu_domain_is_on(rk_domain))
    {
        if (rk_domain->clk_arr)
        {
            if ((err = rt_clk_array_enable(rk_domain->clk_arr)))
            {
                LOG_E("Enable clocks error = %s", rt_strerror(err));
                return;
            }
        }

        rockchip_pmu_init_qos(rk_domain);
        rt_clk_array_disable(rk_domain->clk_arr);
    }
}

static void rockchip_pm_remove_one_domain(struct rockchip_pm_domain *rk_domain)
{
    if (rk_domain->pmu)
    {
        rt_dm_power_domain_unregister(&rk_domain->parent);
        rk_domain->pmu = RT_NULL;
    }

    if (rk_domain->qos_save_regs[0])
    {
        rt_free(rk_domain->qos_save_regs[0]);
    }

    if (rk_domain->qos_is_need_init[0])
    {
        rt_free(rk_domain->qos_is_need_init[0]);
    }

    if (rk_domain->qos_regmaps)
    {
        rt_free(rk_domain->qos_regmaps);
        rk_domain->qos_regmaps = RT_NULL;
    }

    if (rk_domain->clk_arr)
    {
        rt_clk_array_unprepare(rk_domain->clk_arr);
        rt_clk_array_put(rk_domain->clk_arr);

        rk_domain->clk_arr = RT_NULL;
    }
}

static rt_err_t rockchip_pm_add_one_domain(struct rockchip_pmu *pmu,
        struct rt_ofw_node *np)
{
    rt_err_t err;
    rt_uint32_t idx;
    struct rt_dm_power_domain *domain;
    struct rockchip_pm_domain *rk_domain;
    const struct rockchip_domain_info *domain_info;

    if ((err = rt_ofw_prop_read_u32(np, "reg", &idx)))
    {
        LOG_E("Failed to read %s domain id (reg) error = %s",
                rt_ofw_node_full_name(np), rt_strerror(err));
        return err;
    }

    rk_domain = &pmu->rk_pmdomains[idx];
    domain_info = &pmu->info->domain_info[idx];

    if (domain_info->pwr_mask)
    {
        rk_domain->is_ignore_pwr = RT_TRUE;
    }

    /* RK3588 has domains with two parents (RKVDEC0/RKVDEC1) */
    if (rk_domain->pmu)
    {
        return RT_EOK;
    }

    rk_domain->num_qos = rt_ofw_count_phandle_cells(np, "pm_qos", RT_NULL);

    if (rk_domain->num_qos > 0)
    {
        rk_domain->qos_regmaps = rt_calloc(rk_domain->num_qos,
                sizeof(*rk_domain->qos_regmaps));

        if (!rk_domain->qos_regmaps)
        {
            return -RT_ENOMEM;
        }

        rk_domain->qos_save_regs[0] = rt_malloc(rk_domain->num_qos *
                MAX_QOS_REGS_NUM * sizeof(rt_uint32_t));

        if (!rk_domain->qos_save_regs[0])
        {
            return -RT_ENOMEM;
        }

        rk_domain->qos_is_need_init[0] = rt_malloc(rk_domain->num_qos *
                MAX_QOS_REGS_NUM * sizeof(rt_bool_t));

        if (!rk_domain->qos_is_need_init[0])
        {
            return -RT_ENOMEM;
        }

        for (int i = 1; i < MAX_QOS_REGS_NUM; ++i)
        {
            rk_domain->qos_save_regs[i] = rk_domain->qos_save_regs[i - 1] +
                    rk_domain->num_qos;
            rk_domain->qos_is_need_init[i] = rk_domain->qos_is_need_init[i - 1] +
                    rk_domain->num_qos;
        }

        for (int i = 0; i < rk_domain->num_qos; ++i)
        {
            rt_uint32_t val;
            struct rt_ofw_node *qos_np = rt_ofw_parse_phandle(np, "pm_qos", i);

            if (!qos_np)
            {
                err = -RT_EIO;
                goto _free;
            }

            if (!(rk_domain->qos_regmaps[i] = rt_syscon_find_by_ofw_node(qos_np)))
            {
                rt_ofw_node_put(qos_np);
                err = -RT_EIO;

                goto _free;
            }

            if (!rt_ofw_prop_read_u32(qos_np, "priority-init", &val))
            {
                rk_domain->qos_save_regs[0][i] = val;
                rk_domain->qos_is_need_init[0][i] = RT_TRUE;
                rk_domain->is_qos_need_init = RT_TRUE;
            }

            if (!rt_ofw_prop_read_u32(qos_np, "mode-init", &val))
            {
                rk_domain->qos_save_regs[1][i] = val;
                rk_domain->qos_is_need_init[1][i] = RT_TRUE;
                rk_domain->is_qos_need_init = RT_TRUE;
            }

            if (!rt_ofw_prop_read_u32(qos_np, "bandwidth-init", &val))
            {
                rk_domain->qos_save_regs[2][i] = val;
                rk_domain->qos_is_need_init[2][i] = RT_TRUE;
                rk_domain->is_qos_need_init = RT_TRUE;
            }

            if (!rt_ofw_prop_read_u32(qos_np, "saturation-init", &val))
            {
                rk_domain->qos_save_regs[3][i] = val;
                rk_domain->qos_is_need_init[3][i] = RT_TRUE;
                rk_domain->is_qos_need_init = RT_TRUE;
            }

            if (!rt_ofw_prop_read_u32(qos_np, "extcontrol-init", &val))
            {
                rk_domain->qos_save_regs[4][i] = val;
                rk_domain->qos_is_need_init[4][i] = RT_TRUE;
                rk_domain->is_qos_need_init = RT_TRUE;
            }

            rt_ofw_node_put(qos_np);
        }
    }

    if ((err = rockchip_pm_get_shaping(rk_domain, np)))
    {
        goto _free;
    }

    rk_domain->clk_arr = rt_ofw_get_clk_array(np);

    if (rt_is_err(rk_domain->clk_arr))
    {
        LOG_E("Failed to %s %s CLKs", "read", rt_ofw_node_full_name(np));
        err = rt_ptr_err(rk_domain->clk_arr);

        goto _free;
    }

    if ((err = rt_clk_array_prepare(rk_domain->clk_arr)))
    {
        LOG_E("Failed to %s %s CLKs", "prepare", rt_ofw_node_full_name(np));
        goto _free;
    }

    rk_domain->info = domain_info;
    rk_domain->pmu = pmu;
    rk_domain->np = np;

    if (domain_info->always_on || domain_info->keepon_startup)
    {
        if (!rockchip_pmu_domain_is_on(rk_domain))
        {
            if ((err = rockchip_pm_domain_power(rk_domain, RT_TRUE)))
            {
                goto _free;
            }
        }
    }

    rockchip_pm_qos_init(rk_domain);

    domain = &rk_domain->parent;
    domain->power_off = rockchip_pd_power_off;
    domain->power_on = rockchip_pd_power_on;

    if ((err = rt_dm_power_domain_register(domain)))
    {
        goto _free;
    }

    rt_ofw_data(np) = &rk_domain->parent;

    return RT_EOK;

_free:
    rk_domain->info = RT_NULL;
    rk_domain->pmu = RT_NULL;
    rk_domain->np = RT_NULL;

    rockchip_pm_remove_one_domain(rk_domain);

    return err;
}

static rt_err_t rockchip_pm_add_subdomain(struct rockchip_pmu *pmu,
        struct rt_ofw_node *parent)
{
    rt_err_t err;
    rt_uint32_t idx;
    struct rt_ofw_node *np;
    struct rockchip_pm_domain *child_rk_domain, *parent_rk_domain;

    rt_ofw_foreach_child_node(parent, np)
    {
        if ((err = rt_ofw_prop_read_u32(parent, "reg", &idx)))
        {
            LOG_E("Failed to read %s domain id (reg) error = %s",
                    rt_ofw_node_full_name(parent), rt_strerror(err));
            goto _err;
        }

        parent_rk_domain = &pmu->rk_pmdomains[idx];

        if ((err = rockchip_pm_add_one_domain(pmu, np)))
        {
            LOG_E("Failed to handle node %s error = %s",
                    rt_ofw_node_full_name(np), rt_strerror(err));
            goto _err;
        }

        if ((err = rt_ofw_prop_read_u32(np, "reg", &idx)))
        {
            LOG_E("Failed to read %s domain id (reg) error = %s",
                    rt_ofw_node_full_name(np), rt_strerror(err));
            goto _err;
        }

        child_rk_domain = &pmu->rk_pmdomains[idx];

        if ((err = rt_dm_power_domain_register_child(&parent_rk_domain->parent,
                &child_rk_domain->parent)))
        {
            LOG_E("Failed to handle subdomain node %s error = %s",
                    rt_ofw_node_full_name(np), rt_strerror(err));
        }

        rockchip_pm_add_subdomain(pmu, np);
    }

    return RT_EOK;

_err:
    rt_ofw_node_put(np);

    return err;
}

static void rockchip_pmdomain_conf_cnt(struct rockchip_pmu *pmu,
        rt_uint32_t domain_reg_offset, int count)
{
    /* 1. configure domain power down transition count */
    rt_syscon_write(pmu->regmap, domain_reg_offset, count);

    /* 2. power up count. */
    rt_syscon_write(pmu->regmap, domain_reg_offset + 4, count);
}

static struct rt_dm_power_domain *rockchip_pm_domain_proxy_ofw_parse(
        struct rt_dm_power_domain_proxy *proxy, struct rt_ofw_cell_args *args)
{
    struct rockchip_pmu *pmu = raw_to_rockchip_pmu(proxy);

    return &pmu->rk_pmdomains[args->args[0]].parent;
}

static rt_err_t rockchip_pmdomain_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rockchip_pmu *pmu;
    struct rt_ofw_node *np, *grf_np, *child;
    const struct rockchip_pmu_info *pmu_info = pdev->id->data;

    pmu = rt_calloc(1, sizeof(*pmu) + sizeof(pmu->rk_pmdomains[0]) * pmu_info->num_domains);

    if (!pmu)
    {
        return -RT_ENOMEM;
    }

    np = pdev->parent.ofw_node;
    grf_np = rt_ofw_get_parent(np);

    pmu->regmap = rt_syscon_find_by_ofw_node(grf_np);

    rt_ofw_node_put(grf_np);

    if (!pmu->regmap)
    {
        err = -RT_EIO;

        goto _fail;
    }

    pmu->info = pmu_info;
    pmu->dev = &pdev->parent;

    /* Configure power up and down transition delays for CORE and GPU domains. */
    if (pmu_info->core_power_transition_time)
    {
        rockchip_pmdomain_conf_cnt(pmu, pmu_info->core_pwrcnt_offset,
                pmu_info->core_power_transition_time);
    }

    if (pmu_info->gpu_pwrcnt_offset)
    {
        rockchip_pmdomain_conf_cnt(pmu, pmu_info->gpu_pwrcnt_offset,
                pmu_info->gpu_power_transition_time);
    }

    rt_ofw_foreach_available_child_node(np, child)
    {
        if ((err = rockchip_pm_add_one_domain(pmu, child)))
        {
            LOG_E("Failed to handle node %s error = %s",
                    rt_ofw_node_full_name(child), rt_strerror(err));

            rt_ofw_node_put(child);
            goto _free_domain;
        }

        if ((err = rockchip_pm_add_subdomain(pmu, child)))
        {
            LOG_E("Failed to handle subdomain node %s error = %s",
                    rt_ofw_node_full_name(child), rt_strerror(err));

            rt_ofw_node_put(child);
            goto _free_domain;
        }
    }

    pmu->parent.ofw_parse = rockchip_pm_domain_proxy_ofw_parse;
    rt_dm_power_domain_proxy_ofw_bind(&pmu->parent, np);

    return RT_EOK;

_free_domain:
    for (int i = 0; i < pmu_info->num_domains; ++i)
    {
        struct rockchip_pm_domain *rk_domain;

        rk_domain = raw_to_rockchip_pm_domain(&pmu->rk_pmdomains[i]);

        if (rk_domain->pmu)
        {
            rockchip_pm_remove_one_domain(rk_domain);
        }
    }

_fail:
    rt_free(pmu);

    return err;
}

#define DOMAIN_PX30(name, pwr, status, req, wakeup) DOMAIN_M(name, pwr, status, req, (req) << 16, req, wakeup, RT_FALSE)
#define DOMAIN_PX30_PROTECT(name, pwr, status, req, wakeup) DOMAIN_M(name, pwr, status, req, (req) << 16, req, wakeup, RT_TRUE)

static const struct rockchip_domain_info px30_pm_domains[] =
{
    [PX30_PD_USB]       = DOMAIN_PX30("usb",        RT_BIT(5),  RT_BIT(5),  RT_BIT(10), RT_FALSE),
    [PX30_PD_SDCARD]    = DOMAIN_PX30("sdcard",     RT_BIT(8),  RT_BIT(8),  RT_BIT(9),  RT_FALSE),
    [PX30_PD_GMAC]      = DOMAIN_PX30("gmac",       RT_BIT(10), RT_BIT(10), RT_BIT(6),  RT_FALSE),
    [PX30_PD_MMC_NAND]  = DOMAIN_PX30("mmc_nand",   RT_BIT(11), RT_BIT(11), RT_BIT(5),  RT_FALSE),
    [PX30_PD_VPU]       = DOMAIN_PX30("vpu",        RT_BIT(12), RT_BIT(12), RT_BIT(14), RT_FALSE),
    [PX30_PD_VO]        = DOMAIN_PX30_PROTECT("vo", RT_BIT(13), RT_BIT(13), RT_BIT(7),  RT_FALSE),
    [PX30_PD_VI]        = DOMAIN_PX30_PROTECT("vi", RT_BIT(14), RT_BIT(14), RT_BIT(8),  RT_FALSE),
    [PX30_PD_GPU]       = DOMAIN_PX30("gpu",        RT_BIT(15), RT_BIT(15), RT_BIT(2),  RT_FALSE),
};

static const struct rockchip_pmu_info px30_pmu =
{
    .type = SOC_TYPE_PX30,
    .pwr_offset = 0x18,
    .status_offset = 0x20,
    .req_offset = 0x64,
    .idle_offset = 0x6c,
    .ack_offset = 0x6c,

    .num_domains = RT_ARRAY_SIZE(px30_pm_domains),
    .domain_info = px30_pm_domains,
};

static const struct rockchip_domain_info rk1808_pm_domains[] =
{
    [RK1808_VD_NPU]     = DOMAIN_PX30("npu",         RT_BIT(15), RT_BIT(15), RT_BIT(2), RT_FALSE),
    [RK1808_PD_PCIE]    = DOMAIN_PX30("pcie",        RT_BIT(9),  RT_BIT(9),  RT_BIT(4), RT_TRUE),
    [RK1808_PD_VPU]     = DOMAIN_PX30("vpu",         RT_BIT(13), RT_BIT(13), RT_BIT(7), RT_FALSE),
    [RK1808_PD_VIO]     = DOMAIN_PX30_PROTECT("vio", RT_BIT(14), RT_BIT(14), RT_BIT(8), RT_FALSE),
};

static const struct rockchip_pmu_info rk1808_pmu =
{
    .pwr_offset = 0x18,
    .status_offset = 0x20,
    .req_offset = 0x64,
    .idle_offset = 0x6c,
    .ack_offset = 0x6c,

    .num_domains = RT_ARRAY_SIZE(rk1808_pm_domains),
    .domain_info = rk1808_pm_domains,
};

#define DOMAIN_RK3036(name, req, ack, idle, wakeup) DOMAIN_M(name, 0, 0, req, idle, ack, wakeup, RT_FALSE)

static const struct rockchip_domain_info rk3036_pm_domains[] =
{
    [RK3036_PD_MSCH]    = DOMAIN_RK3036("msch", RT_BIT(14), RT_BIT(23), RT_BIT(30), RT_TRUE),
    [RK3036_PD_CORE]    = DOMAIN_RK3036("core", RT_BIT(13), RT_BIT(17), RT_BIT(24), RT_FALSE),
    [RK3036_PD_PERI]    = DOMAIN_RK3036("peri", RT_BIT(12), RT_BIT(18), RT_BIT(25), RT_FALSE),
    [RK3036_PD_VIO]     = DOMAIN_RK3036("vio",  RT_BIT(11), RT_BIT(19), RT_BIT(26), RT_FALSE),
    [RK3036_PD_VPU]     = DOMAIN_RK3036("vpu",  RT_BIT(10), RT_BIT(20), RT_BIT(27), RT_FALSE),
    [RK3036_PD_GPU]     = DOMAIN_RK3036("gpu",  RT_BIT(9),  RT_BIT(21), RT_BIT(28), RT_FALSE),
    [RK3036_PD_SYS]     = DOMAIN_RK3036("sys",  RT_BIT(8),  RT_BIT(22), RT_BIT(29), RT_FALSE),
};

static const struct rockchip_pmu_info rk3036_pmu =
{
    .req_offset = 0x148,
    .idle_offset = 0x14c,
    .ack_offset = 0x14c,

    .num_domains = RT_ARRAY_SIZE(rk3036_pm_domains),
    .domain_info = rk3036_pm_domains,
};

static const struct rockchip_domain_info rk3066_pm_domains[] =
{
    [RK3066_PD_GPU]     = DOMAIN("gpu",   RT_BIT(9), RT_BIT(9), RT_BIT(3), RT_BIT(24), RT_BIT(29), RT_FALSE, RT_FALSE),
    [RK3066_PD_VIDEO]   = DOMAIN("video", RT_BIT(8), RT_BIT(8), RT_BIT(4), RT_BIT(23), RT_BIT(28), RT_FALSE, RT_FALSE),
    [RK3066_PD_VIO]     = DOMAIN("vio",   RT_BIT(7), RT_BIT(7), RT_BIT(5), RT_BIT(22), RT_BIT(27), RT_FALSE, RT_TRUE),
    [RK3066_PD_PERI]    = DOMAIN("peri",  RT_BIT(6), RT_BIT(6), RT_BIT(2), RT_BIT(25), RT_BIT(30), RT_FALSE, RT_FALSE),
    [RK3066_PD_CPU]     = DOMAIN("cpu",   0,         RT_BIT(5), RT_BIT(1), RT_BIT(26), RT_BIT(31), RT_FALSE, RT_FALSE),
};

static const struct rockchip_pmu_info rk3066_pmu =
{
    .pwr_offset = 0x08,
    .status_offset = 0x0c,
    .req_offset = 0x38, /* PMU_MISC_CON1 */
    .idle_offset = 0x0c,
    .ack_offset = 0x0c,

    .num_domains = RT_ARRAY_SIZE(rk3066_pm_domains),
    .domain_info = rk3066_pm_domains,
};

#define DOMAIN_RK3288(name, pwr, status, req, wakeup) DOMAIN(name, pwr, status, req, req, (req) << 16, wakeup, RT_FALSE)
#define DOMAIN_RK3288_PROTECT(name, pwr, status, req, wakeup) DOMAIN(name, pwr, status, req, req, (req) << 16, wakeup, RT_TRUE)

static const struct rockchip_domain_info rk3128_pm_domains[] =
{
    [RK3128_PD_CORE]    = DOMAIN_RK3288("core",        RT_BIT(0), RT_BIT(0), RT_BIT(4), RT_FALSE),
    [RK3128_PD_MSCH]    = DOMAIN_RK3288("msch",        0,         0,         RT_BIT(6), RT_TRUE),
    [RK3128_PD_VIO]     = DOMAIN_RK3288_PROTECT("vio", RT_BIT(3), RT_BIT(3), RT_BIT(2), RT_FALSE),
    [RK3128_PD_VIDEO]   = DOMAIN_RK3288("video",       RT_BIT(2), RT_BIT(2), RT_BIT(1), RT_FALSE),
    [RK3128_PD_GPU]     = DOMAIN_RK3288("gpu",         RT_BIT(1), RT_BIT(1), RT_BIT(3), RT_FALSE),
};

static const struct rockchip_pmu_info rk3128_pmu =
{
    .pwr_offset = 0x04,
    .status_offset = 0x08,
    .req_offset = 0x0c,
    .idle_offset = 0x10,
    .ack_offset = 0x10,

    .num_domains = RT_ARRAY_SIZE(rk3128_pm_domains),
    .domain_info = rk3128_pm_domains,
};

static const struct rockchip_domain_info rk3188_pm_domains[] =
{
    [RK3188_PD_GPU]     = DOMAIN("gpu",   RT_BIT(9), RT_BIT(9), RT_BIT(3), RT_BIT(24), RT_BIT(29), RT_FALSE, RT_FALSE),
    [RK3188_PD_VIDEO]   = DOMAIN("video", RT_BIT(8), RT_BIT(8), RT_BIT(4), RT_BIT(23), RT_BIT(28), RT_FALSE, RT_FALSE),
    [RK3188_PD_VIO]     = DOMAIN("vio",   RT_BIT(7), RT_BIT(7), RT_BIT(5), RT_BIT(22), RT_BIT(27), RT_FALSE, RT_FALSE),
    [RK3188_PD_PERI]    = DOMAIN("peri",  RT_BIT(6), RT_BIT(6), RT_BIT(2), RT_BIT(25), RT_BIT(30), RT_FALSE, RT_FALSE),
    [RK3188_PD_CPU]     = DOMAIN("cpu",   RT_BIT(5), RT_BIT(5), RT_BIT(1), RT_BIT(26), RT_BIT(31), RT_FALSE, RT_FALSE),
};

static const struct rockchip_pmu_info rk3188_pmu =
{
    .pwr_offset = 0x08,
    .status_offset = 0x0c,
    .req_offset = 0x38, /* PMU_MISC_CON1 */
    .idle_offset = 0x0c,
    .ack_offset = 0x0c,

    .num_domains = RT_ARRAY_SIZE(rk3188_pm_domains),
    .domain_info = rk3188_pm_domains,
};

static const struct rockchip_domain_info rk3228_pm_domains[] =
{
    [RK3228_PD_CORE]    = DOMAIN_RK3036("core", RT_BIT(0),  RT_BIT(0),  RT_BIT(16), RT_TRUE),
    [RK3228_PD_MSCH]    = DOMAIN_RK3036("msch", RT_BIT(1),  RT_BIT(1),  RT_BIT(17), RT_TRUE),
    [RK3228_PD_BUS]     = DOMAIN_RK3036("bus",  RT_BIT(2),  RT_BIT(2),  RT_BIT(18), RT_TRUE),
    [RK3228_PD_SYS]     = DOMAIN_RK3036("sys",  RT_BIT(3),  RT_BIT(3),  RT_BIT(19), RT_TRUE),
    [RK3228_PD_VIO]     = DOMAIN_RK3036("vio",  RT_BIT(4),  RT_BIT(4),  RT_BIT(20), RT_FALSE),
    [RK3228_PD_VOP]     = DOMAIN_RK3036("vop",  RT_BIT(5),  RT_BIT(5),  RT_BIT(21), RT_FALSE),
    [RK3228_PD_VPU]     = DOMAIN_RK3036("vpu",  RT_BIT(6),  RT_BIT(6),  RT_BIT(22), RT_FALSE),
    [RK3228_PD_RKVDEC]  = DOMAIN_RK3036("vdec", RT_BIT(7),  RT_BIT(7),  RT_BIT(23), RT_FALSE),
    [RK3228_PD_GPU]     = DOMAIN_RK3036("gpu",  RT_BIT(8),  RT_BIT(8),  RT_BIT(24), RT_FALSE),
    [RK3228_PD_PERI]    = DOMAIN_RK3036("peri", RT_BIT(9),  RT_BIT(9),  RT_BIT(25), RT_TRUE),
    [RK3228_PD_GMAC]    = DOMAIN_RK3036("gmac", RT_BIT(10), RT_BIT(10), RT_BIT(26), RT_FALSE),
};

static const struct rockchip_pmu_info rk3228_pmu =
{
    .req_offset = 0x40c,
    .idle_offset = 0x488,
    .ack_offset = 0x488,

    .num_domains = RT_ARRAY_SIZE(rk3228_pm_domains),
    .domain_info = rk3228_pm_domains,
};

static const struct rockchip_domain_info rk3288_pm_domains[] =
{
    [RK3288_PD_VIO]     = DOMAIN_RK3288_PROTECT("vio", RT_BIT(7),  RT_BIT(7),  RT_BIT(4), RT_FALSE),
    [RK3288_PD_HEVC]    = DOMAIN_RK3288("hevc",        RT_BIT(14), RT_BIT(10), RT_BIT(9), RT_FALSE),
    [RK3288_PD_VIDEO]   = DOMAIN_RK3288("video",       RT_BIT(8),  RT_BIT(8),  RT_BIT(3), RT_FALSE),
    [RK3288_PD_GPU]     = DOMAIN_RK3288("gpu",         RT_BIT(9),  RT_BIT(9),  RT_BIT(2), RT_FALSE),
};

static const struct rockchip_pmu_info rk3288_pmu =
{
    .pwr_offset = 0x08,
    .status_offset = 0x0c,
    .req_offset = 0x10,
    .idle_offset = 0x14,
    .ack_offset = 0x14,

    .core_pwrcnt_offset = 0x34,
    .gpu_pwrcnt_offset = 0x3c,

    .core_power_transition_time = 24, /* 1us */
    .gpu_power_transition_time = 24, /* 1us */

    .num_domains = RT_ARRAY_SIZE(rk3288_pm_domains),
    .domain_info = rk3288_pm_domains,
};

#define DOMAIN_RK3328(name, pwr, status, req, wakeup) DOMAIN_M(name, pwr, pwr, req, (req) << 10, req, wakeup, RT_FALSE)

static const struct rockchip_domain_info rk3328_pm_domains[] =
{
    [RK3328_PD_CORE]    = DOMAIN_RK3328("core",  0, RT_BIT(0), RT_BIT(0), RT_FALSE),
    [RK3328_PD_GPU]     = DOMAIN_RK3328("gpu",   0, RT_BIT(1), RT_BIT(1), RT_FALSE),
    [RK3328_PD_BUS]     = DOMAIN_RK3328("bus",   0, RT_BIT(2), RT_BIT(2), RT_TRUE),
    [RK3328_PD_MSCH]    = DOMAIN_RK3328("msch",  0, RT_BIT(3), RT_BIT(3), RT_TRUE),
    [RK3328_PD_PERI]    = DOMAIN_RK3328("peri",  0, RT_BIT(4), RT_BIT(4), RT_TRUE),
    [RK3328_PD_VIDEO]   = DOMAIN_RK3328("video", 0, RT_BIT(5), RT_BIT(5), RT_FALSE),
    [RK3328_PD_HEVC]    = DOMAIN_RK3328("hevc",  0, RT_BIT(6), RT_BIT(6), RT_FALSE),
    [RK3328_PD_VIO]     = DOMAIN_RK3328("vio",   0, RT_BIT(8), RT_BIT(8), RT_FALSE),
    [RK3328_PD_VPU]     = DOMAIN_RK3328("vpu",   0, RT_BIT(9), RT_BIT(9), RT_FALSE),
};

static const struct rockchip_pmu_info rk3328_pmu =
{
    .req_offset = 0x414,
    .idle_offset = 0x484,
    .ack_offset = 0x484,

    .num_domains = RT_ARRAY_SIZE(rk3328_pm_domains),
    .domain_info = rk3328_pm_domains,
};

#define DOMAIN_RK3368(name, pwr, status, req, wakeup) DOMAIN(name, pwr, status, req, (req) << 16, req, wakeup, RT_FALSE)
#define DOMAIN_RK3368_PROTECT(name, pwr, status, req, wakeup) DOMAIN(name, pwr, status, req, (req) << 16, req, wakeup, RT_TRUE)

static const struct rockchip_domain_info rk3366_pm_domains[] =
{
    [RK3366_PD_PERI]    = DOMAIN_RK3368("peri",        RT_BIT(10), RT_BIT(10), RT_BIT(6), RT_TRUE),
    [RK3366_PD_VIO]     = DOMAIN_RK3368_PROTECT("vio", RT_BIT(14), RT_BIT(14), RT_BIT(8), RT_FALSE),
    [RK3366_PD_VIDEO]   = DOMAIN_RK3368("video",       RT_BIT(13), RT_BIT(13), RT_BIT(7), RT_FALSE),
    [RK3366_PD_RKVDEC]  = DOMAIN_RK3368("vdec",        RT_BIT(11), RT_BIT(11), RT_BIT(7), RT_FALSE),
    [RK3366_PD_WIFIBT]  = DOMAIN_RK3368("wifibt",      RT_BIT(8),  RT_BIT(8),  RT_BIT(9), RT_FALSE),
    [RK3366_PD_VPU]     = DOMAIN_RK3368("vpu",         RT_BIT(12), RT_BIT(12), RT_BIT(7), RT_FALSE),
    [RK3366_PD_GPU]     = DOMAIN_RK3368("gpu",         RT_BIT(15), RT_BIT(15), RT_BIT(2), RT_FALSE),
};

static const struct rockchip_pmu_info rk3366_pmu =
{
    .pwr_offset = 0x0c,
    .status_offset = 0x10,
    .req_offset = 0x3c,
    .idle_offset = 0x40,
    .ack_offset = 0x40,

    .core_pwrcnt_offset = 0x48,
    .gpu_pwrcnt_offset = 0x50,

    .core_power_transition_time = 24,
    .gpu_power_transition_time = 24,

    .num_domains = RT_ARRAY_SIZE(rk3366_pm_domains),
    .domain_info = rk3366_pm_domains,
};

static const struct rockchip_domain_info rk3368_pm_domains[] =
{
    [RK3368_PD_PERI]    = DOMAIN_RK3368("peri",        RT_BIT(13), RT_BIT(12), RT_BIT(6), RT_TRUE),
    [RK3368_PD_VIO]     = DOMAIN_RK3368_PROTECT("vio", RT_BIT(15), RT_BIT(14), RT_BIT(8), RT_FALSE),
    [RK3368_PD_VIDEO]   = DOMAIN_RK3368("video",       RT_BIT(14), RT_BIT(13), RT_BIT(7), RT_FALSE),
    [RK3368_PD_GPU_0]   = DOMAIN_RK3368("gpu_0",       RT_BIT(16), RT_BIT(15), RT_BIT(2), RT_FALSE),
    [RK3368_PD_GPU_1]   = DOMAIN_RK3368("gpu_1",       RT_BIT(17), RT_BIT(16), RT_BIT(2), RT_FALSE),
};

static const struct rockchip_pmu_info rk3368_pmu =
{
    .pwr_offset = 0x0c,
    .status_offset = 0x10,
    .req_offset = 0x3c,
    .idle_offset = 0x40,
    .ack_offset = 0x40,

    .core_pwrcnt_offset = 0x48,
    .gpu_pwrcnt_offset = 0x50,

    .core_power_transition_time = 24,
    .gpu_power_transition_time = 24,

    .num_domains = RT_ARRAY_SIZE(rk3368_pm_domains),
    .domain_info = rk3368_pm_domains,
};

#define DOMAIN_RK3399(name, pwr, status, req, wakeup) DOMAIN(name, pwr, status, req, req, req, wakeup, RT_FALSE)
#define DOMAIN_RK3399_PROTECT(name, pwr, status, req, wakeup) DOMAIN(name, pwr, status, req, req, req, wakeup, RT_TRUE)

static const struct rockchip_domain_info rk3399_pm_domains[] =
{
    [RK3399_PD_TCPD0]     = DOMAIN_RK3399("tcpd0",        RT_BIT(8),  RT_BIT(8),  0,          RT_FALSE),
    [RK3399_PD_TCPD1]     = DOMAIN_RK3399("tcpd1",        RT_BIT(9),  RT_BIT(9),  0,          RT_FALSE),
    [RK3399_PD_CCI]       = DOMAIN_RK3399("cci",          RT_BIT(10), RT_BIT(10), 0,          RT_TRUE),
    [RK3399_PD_CCI0]      = DOMAIN_RK3399("cci0",         0,          0,          RT_BIT(15), RT_TRUE),
    [RK3399_PD_CCI1]      = DOMAIN_RK3399("cci1",         0,          0,          RT_BIT(16), RT_TRUE),
    [RK3399_PD_PERILP]    = DOMAIN_RK3399("perilp",       RT_BIT(11), RT_BIT(11), RT_BIT(1),  RT_TRUE),
    [RK3399_PD_PERIHP]    = DOMAIN_RK3399("perihp",       RT_BIT(12), RT_BIT(12), RT_BIT(2),  RT_TRUE),
    [RK3399_PD_CENTER]    = DOMAIN_RK3399("center",       RT_BIT(13), RT_BIT(13), RT_BIT(14), RT_TRUE),
    [RK3399_PD_VIO]       = DOMAIN_RK3399_PROTECT("vio",  RT_BIT(14), RT_BIT(14), RT_BIT(17), RT_FALSE),
    [RK3399_PD_GPU]       = DOMAIN_RK3399("gpu",          RT_BIT(15), RT_BIT(15), RT_BIT(0),  RT_FALSE),
    [RK3399_PD_VCODEC]    = DOMAIN_RK3399("vcodec",       RT_BIT(16), RT_BIT(16), RT_BIT(3),  RT_FALSE),
    [RK3399_PD_VDU]       = DOMAIN_RK3399("vdu",          RT_BIT(17), RT_BIT(17), RT_BIT(4),  RT_FALSE),
    [RK3399_PD_RGA]       = DOMAIN_RK3399("rga",          RT_BIT(18), RT_BIT(18), RT_BIT(5),  RT_FALSE),
    [RK3399_PD_IEP]       = DOMAIN_RK3399("iep",          RT_BIT(19), RT_BIT(19), RT_BIT(6),  RT_FALSE),
    [RK3399_PD_VO]        = DOMAIN_RK3399_PROTECT("vo",   RT_BIT(20), RT_BIT(20),         0,  RT_FALSE),
    [RK3399_PD_VOPB]      = DOMAIN_RK3399_PROTECT("vopb", 0,       0,             RT_BIT(7),  RT_FALSE),
    [RK3399_PD_VOPL]      = DOMAIN_RK3399_PROTECT("vopl", 0,       0,             RT_BIT(8),  RT_FALSE),
    [RK3399_PD_ISP0]      = DOMAIN_RK3399("isp0",         RT_BIT(22), RT_BIT(22), RT_BIT(9),  RT_FALSE),
    [RK3399_PD_ISP1]      = DOMAIN_RK3399("isp1",         RT_BIT(23), RT_BIT(23), RT_BIT(10), RT_FALSE),
    [RK3399_PD_HDCP]      = DOMAIN_RK3399_PROTECT("hdcp", RT_BIT(24), RT_BIT(24), RT_BIT(11), RT_FALSE),
    [RK3399_PD_GMAC]      = DOMAIN_RK3399("gmac",         RT_BIT(25), RT_BIT(25), RT_BIT(23), RT_TRUE),
    [RK3399_PD_EMMC]      = DOMAIN_RK3399("emmc",         RT_BIT(26), RT_BIT(26), RT_BIT(24), RT_TRUE),
    [RK3399_PD_USB3]      = DOMAIN_RK3399("usb3",         RT_BIT(27), RT_BIT(27), RT_BIT(12), RT_TRUE),
    [RK3399_PD_EDP]       = DOMAIN_RK3399_PROTECT("edp",  RT_BIT(28), RT_BIT(28), RT_BIT(22), RT_FALSE),
    [RK3399_PD_GIC]       = DOMAIN_RK3399("gic",          RT_BIT(29), RT_BIT(29), RT_BIT(27), RT_TRUE),
    [RK3399_PD_SD]        = DOMAIN_RK3399("sd",           RT_BIT(30), RT_BIT(30), RT_BIT(28), RT_TRUE),
    [RK3399_PD_SDIOAUDIO] = DOMAIN_RK3399("sdioaudio",    RT_BIT(31), RT_BIT(31), RT_BIT(29), RT_TRUE),
};

static const struct rockchip_pmu_info rk3399_pmu =
{
    .pwr_offset = 0x14,
    .status_offset = 0x18,
    .req_offset = 0x60,
    .idle_offset = 0x64,
    .ack_offset = 0x68,

    /* ARM Trusted Firmware manages power transition times */
    .num_domains = RT_ARRAY_SIZE(rk3399_pm_domains),
    .domain_info = rk3399_pm_domains,
};

#define DOMAIN_RK3528(pwr, req, always, wakeup) DOMAIN_M_A(pwr, pwr, req, req, req, always, wakeup, RT_FALSE)

static const struct rockchip_domain_info rk3528_pm_domains[] =
{
    [RK3528_PD_PMU]     = DOMAIN_RK3528(0,          RT_BIT(0), RT_TRUE, RT_FALSE),
    [RK3528_PD_BUS]     = DOMAIN_RK3528(0,          RT_BIT(1), RT_TRUE, RT_FALSE),
    [RK3528_PD_DDR]     = DOMAIN_RK3528(0,          RT_BIT(2), RT_TRUE, RT_FALSE),
    [RK3528_PD_MSCH]    = DOMAIN_RK3528(0,          RT_BIT(3), RT_TRUE, RT_FALSE),
    [RK3528_PD_GPU]     = DOMAIN_RK3528(RT_BIT(0),  RT_BIT(4), RT_TRUE, RT_FALSE),
    [RK3528_PD_RKVDEC]  = DOMAIN_RK3528(0,          RT_BIT(5), RT_TRUE, RT_FALSE),
    [RK3528_PD_RKVENC]  = DOMAIN_RK3528(0,          RT_BIT(6), RT_TRUE, RT_FALSE),
    [RK3528_PD_VO]      = DOMAIN_RK3528(0,          RT_BIT(7), RT_TRUE, RT_FALSE),
    [RK3528_PD_VPU]     = DOMAIN_RK3528(0,          RT_BIT(8), RT_TRUE, RT_FALSE),
};

static const struct rockchip_pmu_info rk3528_pmu =
{
    .pwr_offset = 0x1210,
    .status_offset = 0x1230,
    .req_offset = 0x1110,
    .idle_offset = 0x1128,
    .ack_offset = 0x1120,

    .num_domains = RT_ARRAY_SIZE(rk3528_pm_domains),
    .domain_info = rk3528_pm_domains,
};

#define DOMAIN_RK3562(name, pwr, req, mem, wakeup) DOMAIN_M_C_SD(name, pwr, pwr, req, req, req, req, mem, wakeup, RT_FALSE)
#define DOMAIN_RK3562_PROTECT(name, pwr, req, mem, wakeup) DOMAIN_M_C_SD(name, pwr, pwr, req, req, req, req, mem, wakeup, RT_TRUE)

static const struct rockchip_domain_info rk3562_pm_domains[] =
{
    [RK3562_PD_GPU]     = DOMAIN_RK3562("gpu",         RT_BIT(0), RT_BIT(1),  0, RT_FALSE),
    [RK3562_PD_NPU]     = DOMAIN_RK3562("npu",         RT_BIT(1), RT_BIT(2),  0, RT_FALSE),
    [RK3562_PD_VDPU]    = DOMAIN_RK3562("vdpu",        RT_BIT(2), RT_BIT(6),  0, RT_FALSE),
    [RK3562_PD_VEPU]    = DOMAIN_RK3562("vepu",        RT_BIT(3), RT_BIT(7),  0, RT_FALSE),
    [RK3562_PD_RGA]     = DOMAIN_RK3562("rga",         RT_BIT(4), RT_BIT(5),  0, RT_FALSE),
    [RK3562_PD_VI]      = DOMAIN_RK3562("vi",          RT_BIT(5), RT_BIT(3),  0, RT_FALSE),
    [RK3562_PD_VO]      = DOMAIN_RK3562_PROTECT("vo",  RT_BIT(6), RT_BIT(4), 16, RT_FALSE),
    [RK3562_PD_PHP]     = DOMAIN_RK3562("php",         RT_BIT(7), RT_BIT(8),  0, RT_FALSE),
};

static const struct rockchip_pmu_info rk3562_pmu =
{
    .pwr_offset = 0x210,
    .status_offset = 0x230,
    .req_offset = 0x110,
    .idle_offset = 0x128,
    .ack_offset = 0x120,
    .clk_ungate_offset = 0x140,
    .mem_sd_offset = 0x300,

    .num_domains = RT_ARRAY_SIZE(rk3562_pm_domains),
    .domain_info = rk3562_pm_domains,
};

#define DOMAIN_RK3568(name, pwr, req, wakeup) DOMAIN_M(name, pwr, pwr, req, req, req, wakeup, RT_FALSE)
#define DOMAIN_RK3568_PROTECT(name, pwr, req, wakeup) DOMAIN_M(name, pwr, pwr, req, req, req, wakeup, RT_TRUE)

static const struct rockchip_domain_info rk3568_pm_domains[] =
{
    [RK3568_PD_NPU]     = DOMAIN_RK3568("npu",        RT_BIT(1), RT_BIT(2),  RT_FALSE),
    [RK3568_PD_GPU]     = DOMAIN_RK3568("gpu",        RT_BIT(0), RT_BIT(1),  RT_FALSE),
    [RK3568_PD_VI]      = DOMAIN_RK3568("vi",         RT_BIT(6), RT_BIT(3),  RT_FALSE),
    [RK3568_PD_VO]      = DOMAIN_RK3568_PROTECT("vo", RT_BIT(7), RT_BIT(4),  RT_FALSE),
    [RK3568_PD_RGA]     = DOMAIN_RK3568("rga",        RT_BIT(5), RT_BIT(5),  RT_FALSE),
    [RK3568_PD_VPU]     = DOMAIN_RK3568("vpu",        RT_BIT(2), RT_BIT(6),  RT_FALSE),
    [RK3568_PD_RKVDEC]  = DOMAIN_RK3568("vdec",       RT_BIT(4), RT_BIT(8),  RT_FALSE),
    [RK3568_PD_RKVENC]  = DOMAIN_RK3568("venc",       RT_BIT(3), RT_BIT(7),  RT_FALSE),
    [RK3568_PD_PIPE]    = DOMAIN_RK3568("pipe",       RT_BIT(8), RT_BIT(11), RT_FALSE),
};

static const struct rockchip_pmu_info rk3568_pmu =
{
    .pwr_offset = 0xa0,
    .status_offset = 0x98,
    .req_offset = 0x50,
    .idle_offset = 0x68,
    .ack_offset = 0x60,

    .num_domains = RT_ARRAY_SIZE(rk3568_pm_domains),
    .domain_info = rk3568_pm_domains,
};

#define DOMAIN_RK3576(name, p_offset, pwr, status, r_status, r_offset, req, idle, g_mask, delay, wakeup)    \
    DOMAIN_M_O_R_G(name, p_offset, pwr, status, r_status, r_offset, req, idle, idle, g_mask, delay, wakeup, RT_FALSE)

#define DOMAIN_RK3576_P(name, p_offset, pwr, status, r_status, r_offset, req, idle, g_mask, delay, wakeup)  \
    DOMAIN_M_O_R_G(name, p_offset, pwr, status, r_status, r_offset, req, idle, idle, g_mask, delay, wakeup, RT_TRUE)

static const struct rockchip_domain_info rk3576_pm_domains[] =
{
    /* name  p_offset pwr      status  r_status r_offset req  idle_st  g_mask   delay wakeup */
    [RK3576_PD_NPU]     = DOMAIN_RK3576("npu",    0x0, RT_BIT(0),  RT_BIT(0), 0,          0x0, 0,          0,          0,          0,  RT_FALSE),
    [RK3576_PD_NVM]     = DOMAIN_RK3576("nvm",    0x0, RT_BIT(6),  0,         RT_BIT(6),  0x4, RT_BIT(2),  RT_BIT(18), RT_BIT(2),  0,  RT_FALSE),
    [RK3576_PD_SDGMAC]  = DOMAIN_RK3576("sdgmac", 0x0, RT_BIT(7),  0,         RT_BIT(7),  0x4, RT_BIT(1),  RT_BIT(17), 0x6,        0,  RT_FALSE),
    [RK3576_PD_AUDIO]   = DOMAIN_RK3576("audio",  0x0, RT_BIT(8),  0,         RT_BIT(8),  0x4, RT_BIT(0),  RT_BIT(16), RT_BIT(0),  0,  RT_FALSE),
    [RK3576_PD_PHP]     = DOMAIN_RK3576("php",    0x0, RT_BIT(9),  0,         RT_BIT(9),  0x0, RT_BIT(15), RT_BIT(15), RT_BIT(15), 0,  RT_FALSE),
    [RK3576_PD_SUBPHP]  = DOMAIN_RK3576("subphp", 0x0, RT_BIT(10), 0,         RT_BIT(10), 0x0, 0,          0,          0,          0,  RT_FALSE),
    [RK3576_PD_VOP]     = DOMAIN_RK3576_P("vop",  0x0, RT_BIT(11), 0,         RT_BIT(11), 0x0, 0x6000,     0x6000,     0x6000,     15, RT_FALSE),
    [RK3576_PD_VO1]     = DOMAIN_RK3576_P("vo1",  0x0, RT_BIT(14), 0,         RT_BIT(14), 0x0, RT_BIT(12), RT_BIT(12), 0x7000,     0,  RT_FALSE),
    [RK3576_PD_VO0]     = DOMAIN_RK3576_P("vo0",  0x0, RT_BIT(15), 0,         RT_BIT(15), 0x0, RT_BIT(11), RT_BIT(11), 0x6800,     0,  RT_FALSE),
    [RK3576_PD_USB]     = DOMAIN_RK3576("usb",    0x4, RT_BIT(0),  0,         RT_BIT(16), 0x0, RT_BIT(10), RT_BIT(10), 0x6400,     0,  RT_TRUE),
    [RK3576_PD_VI]      = DOMAIN_RK3576("vi",     0x4, RT_BIT(1),  0,         RT_BIT(17), 0x0, RT_BIT(9),  RT_BIT(9),  RT_BIT(9),  0,  RT_FALSE),
    [RK3576_PD_VEPU0]   = DOMAIN_RK3576("vepu0",  0x4, RT_BIT(2),  0,         RT_BIT(18), 0x0, RT_BIT(7),  RT_BIT(7),  0x280,      0,  RT_FALSE),
    [RK3576_PD_VEPU1]   = DOMAIN_RK3576("vepu1",  0x4, RT_BIT(3),  0,         RT_BIT(19), 0x0, RT_BIT(8),  RT_BIT(8),  RT_BIT(8),  0,  RT_FALSE),
    [RK3576_PD_VDEC]    = DOMAIN_RK3576("vdec",   0x4, RT_BIT(4),  0,         RT_BIT(20), 0x0, RT_BIT(6),  RT_BIT(6),  RT_BIT(6),  0,  RT_FALSE),
    [RK3576_PD_VPU]     = DOMAIN_RK3576_P("vpu",  0x4, RT_BIT(5),  0,         RT_BIT(21), 0x0, RT_BIT(5),  RT_BIT(5),  RT_BIT(5),  0,  RT_FALSE),
    [RK3576_PD_NPUTOP]  = DOMAIN_RK3576("nputop", 0x4, RT_BIT(6),  0,         RT_BIT(22), 0x0, 0x18,       0x18,       0x18,       15, RT_FALSE),
    [RK3576_PD_NPU0]    = DOMAIN_RK3576("npu0",   0x4, RT_BIT(7),  0,         RT_BIT(23), 0x0, RT_BIT(1),  RT_BIT(1),  0x1a,       0,  RT_FALSE),
    [RK3576_PD_NPU1]    = DOMAIN_RK3576("npu1",   0x4, RT_BIT(8),  0,         RT_BIT(24), 0x0, RT_BIT(2),  RT_BIT(2),  0x1c,       0,  RT_FALSE),
    [RK3576_PD_GPU]     = DOMAIN_RK3576("gpu",    0x4, RT_BIT(9),  0,         RT_BIT(25), 0x0, RT_BIT(0),  RT_BIT(0),  RT_BIT(0),  0,  RT_FALSE),
};


static const struct rockchip_pmu_info rk3576_pmu =
{
    .pwr_offset = 0x210,
    .status_offset = 0x230,
    .chain_status_offset = 0x248,
    .mem_status_offset = 0x250,
    .mem_pwr_offset = 0x300,
    .req_offset = 0x110,
    .idle_offset = 0x128,
    .ack_offset = 0x120,
    .repair_status_offset = 0x570,
    .clk_ungate_offset = 0x140,

    .num_domains = RT_ARRAY_SIZE(rk3576_pm_domains),
    .domain_info = rk3576_pm_domains,
};

#define DOMAIN_RK3588(name, p_offset, pwr, status, m_offset, m_status, r_status, r_offset, req, idle, wakeup) \
    DOMAIN_M_O_R(name, p_offset, pwr, status, m_offset, m_status, r_status, r_offset, req, idle, idle, wakeup, RT_FALSE)

#define DOMAIN_RK3588_P(name, p_offset, pwr, status, m_offset, m_status, r_status, r_offset, req, idle, wakeup) \
    DOMAIN_M_O_R(name, p_offset, pwr, status, m_offset, m_status, r_status, r_offset, req, idle, idle, wakeup, RT_TRUE)

static const struct rockchip_domain_info rk3588_pm_domains[] =
{
    [RK3588_PD_GPU]     = DOMAIN_RK3588("gpu",     0x0, RT_BIT(0),  0,          0x0, 0,          RT_BIT(1),  0x0, RT_BIT(0),  RT_BIT(0),  RT_FALSE),
    [RK3588_PD_NPU]     = DOMAIN_RK3588("npu",     0x0, RT_BIT(1),  RT_BIT(1),  0x0, 0,          0,          0x0, 0,          0,          RT_FALSE),
    [RK3588_PD_VCODEC]  = DOMAIN_RK3588("vcodec",  0x0, RT_BIT(2),  RT_BIT(2),  0x0, 0,          0,          0x0, 0,          0,          RT_FALSE),
    [RK3588_PD_NPUTOP]  = DOMAIN_RK3588("nputop",  0x0, RT_BIT(3),  0,          0x0, RT_BIT(11), RT_BIT(2),  0x0, RT_BIT(1),  RT_BIT(1),  RT_FALSE),
    [RK3588_PD_NPU1]    = DOMAIN_RK3588("npu1",    0x0, RT_BIT(4),  0,          0x0, RT_BIT(12), RT_BIT(3),  0x0, RT_BIT(2),  RT_BIT(2),  RT_FALSE),
    [RK3588_PD_NPU2]    = DOMAIN_RK3588("npu2",    0x0, RT_BIT(5),  0,          0x0, RT_BIT(13), RT_BIT(4),  0x0, RT_BIT(3),  RT_BIT(3),  RT_FALSE),
    [RK3588_PD_VENC0]   = DOMAIN_RK3588("venc0",   0x0, RT_BIT(6),  0,          0x0, RT_BIT(14), RT_BIT(5),  0x0, RT_BIT(4),  RT_BIT(4),  RT_FALSE),
    [RK3588_PD_VENC1]   = DOMAIN_RK3588("venc1",   0x0, RT_BIT(7),  0,          0x0, RT_BIT(15), RT_BIT(6),  0x0, RT_BIT(5),  RT_BIT(5),  RT_FALSE),
    [RK3588_PD_RKVDEC0] = DOMAIN_RK3588("rkvdec0", 0x0, RT_BIT(8),  0,          0x0, RT_BIT(16), RT_BIT(7),  0x0, RT_BIT(6),  RT_BIT(6),  RT_FALSE),
    [RK3588_PD_RKVDEC1] = DOMAIN_RK3588("rkvdec1", 0x0, RT_BIT(9),  0,          0x0, RT_BIT(17), RT_BIT(8),  0x0, RT_BIT(7),  RT_BIT(7),  RT_FALSE),
    [RK3588_PD_VDPU]    = DOMAIN_RK3588("vdpu",    0x0, RT_BIT(10), 0,          0x0, RT_BIT(18), RT_BIT(9),  0x0, RT_BIT(8),  RT_BIT(8),  RT_FALSE),
    [RK3588_PD_RGA30]   = DOMAIN_RK3588("rga30",   0x0, RT_BIT(11), 0,          0x0, RT_BIT(19), RT_BIT(10), 0x0, 0,          0,          RT_FALSE),
    [RK3588_PD_AV1]     = DOMAIN_RK3588("av1",     0x0, RT_BIT(12), 0,          0x0, RT_BIT(20), RT_BIT(11), 0x0, RT_BIT(9),  RT_BIT(9),  RT_FALSE),
    [RK3588_PD_VI]      = DOMAIN_RK3588("vi",      0x0, RT_BIT(13), 0,          0x0, RT_BIT(21), RT_BIT(12), 0x0, RT_BIT(10), RT_BIT(10), RT_FALSE),
    [RK3588_PD_FEC]     = DOMAIN_RK3588("fec",     0x0, RT_BIT(14), 0,          0x0, RT_BIT(22), RT_BIT(13), 0x0, 0,          0,          RT_FALSE),
    [RK3588_PD_ISP1]    = DOMAIN_RK3588("isp1",    0x0, RT_BIT(15), 0,          0x0, RT_BIT(23), RT_BIT(14), 0x0, RT_BIT(11), RT_BIT(11), RT_FALSE),
    [RK3588_PD_RGA31]   = DOMAIN_RK3588("rga31",   0x4, RT_BIT(0),  0,          0x0, RT_BIT(24), RT_BIT(15), 0x0, RT_BIT(12), RT_BIT(12), RT_FALSE),
    [RK3588_PD_VOP]     = DOMAIN_RK3588_P("vop",   0x4, RT_BIT(1),  0,          0x0, RT_BIT(25), RT_BIT(16), 0x0, RT_BIT(13) | RT_BIT(14), RT_BIT(13) | RT_BIT(14), RT_FALSE),
    [RK3588_PD_VO0]     = DOMAIN_RK3588_P("vo0",   0x4, RT_BIT(2),  0,          0x0, RT_BIT(26), RT_BIT(17), 0x0, RT_BIT(15), RT_BIT(15), RT_FALSE),
    [RK3588_PD_VO1]     = DOMAIN_RK3588_P("vo1",   0x4, RT_BIT(3),  0,          0x0, RT_BIT(27), RT_BIT(18), 0x4, RT_BIT(0),  RT_BIT(16), RT_FALSE),
    [RK3588_PD_AUDIO]   = DOMAIN_RK3588("audio",   0x4, RT_BIT(4),  0,          0x0, RT_BIT(28), RT_BIT(19), 0x4, RT_BIT(1),  RT_BIT(17), RT_FALSE),
    [RK3588_PD_PHP]     = DOMAIN_RK3588("php",     0x4, RT_BIT(5),  0,          0x0, RT_BIT(29), RT_BIT(20), 0x4, RT_BIT(5),  RT_BIT(21), RT_FALSE),
    [RK3588_PD_GMAC]    = DOMAIN_RK3588("gmac",    0x4, RT_BIT(6),  0,          0x0, RT_BIT(30), RT_BIT(21), 0x0, 0,          0,          RT_FALSE),
    [RK3588_PD_PCIE]    = DOMAIN_RK3588("pcie",    0x4, RT_BIT(7),  0,          0x0, RT_BIT(31), RT_BIT(22), 0x0, 0,          0,          RT_TRUE),
    [RK3588_PD_NVM]     = DOMAIN_RK3588("nvm",     0x4, RT_BIT(8),  RT_BIT(24), 0x4, 0,          0,          0x4, RT_BIT(2),  RT_BIT(18), RT_FALSE),
    [RK3588_PD_NVM0]    = DOMAIN_RK3588("nvm0",    0x4, RT_BIT(9),  0,          0x4, RT_BIT(1),  RT_BIT(23), 0x0, 0,          0,          RT_FALSE),
    [RK3588_PD_SDIO]    = DOMAIN_RK3588("sdio",    0x4, RT_BIT(10), 0,          0x4, RT_BIT(2),  RT_BIT(24), 0x4, RT_BIT(3),  RT_BIT(19), RT_FALSE),
    [RK3588_PD_USB]     = DOMAIN_RK3588("usb",     0x4, RT_BIT(11), 0,          0x4, RT_BIT(3),  RT_BIT(25), 0x4, RT_BIT(4),  RT_BIT(20), RT_TRUE),
    [RK3588_PD_SDMMC]   = DOMAIN_RK3588("sdmmc",   0x4, RT_BIT(13), 0,          0x4, RT_BIT(5),  RT_BIT(26), 0x0, 0,          0,          RT_FALSE),
};

static const struct rockchip_pmu_info rk3588_pmu =
{
    .pwr_offset = 0x14c,
    .status_offset = 0x180,
    .req_offset = 0x10c,
    .idle_offset = 0x120,
    .ack_offset = 0x118,
    .mem_pwr_offset = 0x1a0,
    .chain_status_offset = 0x1f0,
    .mem_status_offset = 0x1f8,
    .repair_status_offset = 0x290,

    .num_domains = RT_ARRAY_SIZE(rk3588_pm_domains),
    .domain_info = rk3588_pm_domains,
};

#define DOMAIN_RV1126(name, pwr, req, idle, wakeup) DOMAIN_M(name, pwr, pwr, req, idle, idle, wakeup, RT_FALSE)
#define DOMAIN_RV1126_PROTECT(name, pwr, req, idle, wakeup)  DOMAIN_M(name, pwr, pwr, req, idle, idle, wakeup, RT_TRUE)
#define DOMAIN_RV1126_O(name, pwr, req, idle, r_offset, wakeup) DOMAIN_M_O(name, pwr, pwr, 0, req, idle, idle, r_offset, wakeup, RT_FALSE)

static const struct rockchip_domain_info rv1126_pm_domains[] =
{
    [RV1126_PD_CRYPTO]  = DOMAIN_RV1126_O("crypto",   RT_BIT(10), RT_BIT(4),  RT_BIT(20), 0x4, RT_FALSE),
    [RV1126_PD_VEPU]    = DOMAIN_RV1126("vepu",       RT_BIT(2),  RT_BIT(9),  RT_BIT(9),       RT_FALSE),
    [RV1126_PD_VI]      = DOMAIN_RV1126("vi",         RT_BIT(4),  RT_BIT(6),  RT_BIT(6),       RT_FALSE),
    [RV1126_PD_VO]      = DOMAIN_RV1126_PROTECT("vo", RT_BIT(5),  RT_BIT(7),  RT_BIT(7),       RT_FALSE),
    [RV1126_PD_ISPP]    = DOMAIN_RV1126("ispp",       RT_BIT(1),  RT_BIT(8),  RT_BIT(8),       RT_FALSE),
    [RV1126_PD_VDPU]    = DOMAIN_RV1126("vdpu",       RT_BIT(3),  RT_BIT(10), RT_BIT(10),      RT_FALSE),
    [RV1126_PD_NVM]     = DOMAIN_RV1126("nvm",        RT_BIT(7),  RT_BIT(11), RT_BIT(11),      RT_FALSE),
    [RV1126_PD_SDIO]    = DOMAIN_RV1126("sdio",       RT_BIT(8),  RT_BIT(13), RT_BIT(13),      RT_FALSE),
    [RV1126_PD_USB]     = DOMAIN_RV1126("usb",        RT_BIT(9),  RT_BIT(15), RT_BIT(15),      RT_FALSE),
    [RV1126_PD_NPU]     = DOMAIN_RV1126_O("npu",      RT_BIT(0),  RT_BIT(2),  RT_BIT(18), 0x4, RT_FALSE),
};

static const struct rockchip_pmu_info rv1126_pmu =
{
    .pwr_offset = 0x110,
    .status_offset = 0x108,
    .req_offset = 0xc0,
    .idle_offset = 0xd8,
    .ack_offset = 0xd0,

    .num_domains = RT_ARRAY_SIZE(rv1126_pm_domains),
    .domain_info = rv1126_pm_domains,
};

static const struct rt_ofw_node_id rockchip_pmdomain_ofw_ids[] =
{
    { .compatible = "rockchip,px30-power-controller", .data = &px30_pmu, },
    { .compatible = "rockchip,rk1808-power-controller", .data = &rk1808_pmu, },
    { .compatible = "rockchip,rk3036-power-controller", .data = &rk3036_pmu, },
    { .compatible = "rockchip,rk3066-power-controller", .data = &rk3066_pmu, },
    { .compatible = "rockchip,rk3128-power-controller", .data = &rk3128_pmu, },
    { .compatible = "rockchip,rk3188-power-controller", .data = &rk3188_pmu, },
    { .compatible = "rockchip,rk3228-power-controller", .data = &rk3228_pmu, },
    { .compatible = "rockchip,rk3288-power-controller", .data = &rk3288_pmu, },
    { .compatible = "rockchip,rk3328-power-controller", .data = &rk3328_pmu, },
    { .compatible = "rockchip,rk3366-power-controller", .data = &rk3366_pmu, },
    { .compatible = "rockchip,rk3368-power-controller", .data = &rk3368_pmu, },
    { .compatible = "rockchip,rk3399-power-controller", .data = &rk3399_pmu, },
    { .compatible = "rockchip,rk3528-power-controller", .data = &rk3528_pmu, },
    { .compatible = "rockchip,rk3562-power-controller", .data = &rk3562_pmu, },
    { .compatible = "rockchip,rk3568-power-controller", .data = &rk3568_pmu, },
    { .compatible = "rockchip,rk3576-power-controller", .data = &rk3576_pmu, },
    { .compatible = "rockchip,rk3588-power-controller", .data = &rk3588_pmu, },
    { .compatible = "rockchip,rv1126-power-controller", .data = &rv1126_pmu, },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_pmdomain_driver =
{
    .name = "rockchip-pmdomain",
    .ids = rockchip_pmdomain_ofw_ids,

    .probe = rockchip_pmdomain_probe,
};

static int rockchip_pmdomain_drv_register(void)
{
    rt_platform_driver_register(&rockchip_pmdomain_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(rockchip_pmdomain_drv_register);
