/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/ufs.h>

#define DBG_TAG "rtdm.ufs.pm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define RT_UFS_DME_ATTR_SET_NOR         0

rt_inline rt_uint32_t ufs_uic_arg_attr_type(rt_uint8_t t)
{
    return ((rt_uint32_t)(t) & 0xffu) << 16;
}

rt_err_t rt_ufs_dme_set(struct rt_ufs_host *ufs, rt_uint32_t attr_sel, rt_uint32_t value)
{
    rt_err_t err;
    rt_uint32_t arg2 = ufs_uic_arg_attr_type(RT_UFS_DME_ATTR_SET_NOR);

    if ((err = rt_ufs_uic_cmd_send(ufs, RT_UFS_CMDOP_DME_SET, attr_sel, &arg2, value)))
    {
        return err;
    }

    if ((arg2 & RT_UFS_CMDRES_MASK) != RT_UFS_CMDRES_SUCCESS)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

rt_err_t rt_ufs_dme_get(struct rt_ufs_host *ufs, rt_uint32_t attr_sel, rt_uint32_t *value)
{
    rt_uint32_t arg2 = 0;
    rt_err_t err;

    if (!value)
    {
        return -RT_EINVAL;
    }

    if ((err = rt_ufs_uic_cmd_send(ufs, RT_UFS_CMDOP_DME_GET, attr_sel, &arg2, 0)))
    {
        return err;
    }

    if ((arg2 & RT_UFS_CMDRES_MASK) != RT_UFS_CMDRES_SUCCESS)
    {
        return -RT_ERROR;
    }

    *value = HWREG32(ufs->regs + RT_UFS_REG_UCMDARG3);

    return RT_EOK;
}

rt_err_t rt_ufs_uic_pa_pwrmode(struct rt_ufs_host *ufs, rt_uint8_t mode)
{
    return rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_PWRMODE), mode);
}

rt_err_t rt_ufs_pa_power_mode_set(struct rt_ufs_host *ufs, const struct rt_ufs_pa_layer_attr *attr, rt_bool_t force)
{
    rt_err_t err;
    rt_uint8_t mode;

    if (!ufs || !attr || !ufs->regs)
    {
        return -RT_EINVAL;
    }

    if (!force && ufs->pwr_active_valid &&
        attr->gear_rx == ufs->pwr_active.gear_rx &&
        attr->gear_tx == ufs->pwr_active.gear_tx &&
        attr->lane_rx == ufs->pwr_active.lane_rx &&
        attr->lane_tx == ufs->pwr_active.lane_tx &&
        attr->pwr_rx == ufs->pwr_active.pwr_rx &&
        attr->pwr_tx == ufs->pwr_active.pwr_tx &&
        attr->hs_rate == ufs->pwr_active.hs_rate)
    {
        return RT_EOK;
    }

    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_RXGEAR), attr->gear_rx)))
    {
        return err;
    }
    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_ACTIVERXDATALANES), attr->lane_rx)))
    {
        return err;
    }
    if (attr->pwr_rx == RT_UFS_PA_FASTAUTO_MODE || attr->pwr_rx == RT_UFS_PA_FAST_MODE)
    {
        err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_RXTERMINATION), 1);
    }
    else
    {
        err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_RXTERMINATION), 0);
    }
    if (err)
    {
        return err;
    }

    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_TXGEAR), attr->gear_tx)))
    {
        return err;
    }
    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_ACTIVETXDATALANES), attr->lane_tx)))
    {
        return err;
    }
    if (attr->pwr_tx == RT_UFS_PA_FASTAUTO_MODE || attr->pwr_tx == RT_UFS_PA_FAST_MODE)
    {
        err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_TXTERMINATION), 1);
    }
    else
    {
        err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_TXTERMINATION), 0);
    }
    if (err)
    {
        return err;
    }

    if (attr->pwr_rx == RT_UFS_PA_FASTAUTO_MODE || attr->pwr_tx == RT_UFS_PA_FASTAUTO_MODE ||
        attr->pwr_rx == RT_UFS_PA_FAST_MODE || attr->pwr_tx == RT_UFS_PA_FAST_MODE)
    {
        if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_HSSERIES), attr->hs_rate)))
        {
            return err;
        }
    }

    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_PWRMODEUSERDATA0), RT_UFS_DL_FC0_PROT_TO_DEFAULT)))
    {
        return err;
    }
    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_PWRMODEUSERDATA1), RT_UFS_DL_TC0_REPLAY_TO_DEFAULT)))
    {
        return err;
    }
    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_PWRMODEUSERDATA2), RT_UFS_DL_AFC0_REQ_TO_DEFAULT)))
    {
        return err;
    }
    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_PWRMODEUSERDATA3), RT_UFS_DL_FC1_PROT_TO_DEFAULT)))
    {
        return err;
    }
    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_PWRMODEUSERDATA4), RT_UFS_DL_TC1_REPLAY_TO_DEFAULT)))
    {
        return err;
    }
    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_PA_PWRMODEUSERDATA5), RT_UFS_DL_AFC1_REQ_TO_DEFAULT)))
    {
        return err;
    }

    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_DME_LOCAL_FC0_PROT_TO), RT_UFS_DL_FC0_PROT_TO_DEFAULT)))
    {
        return err;
    }
    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_DME_LOCAL_TC0_REPLAY_TO), RT_UFS_DL_TC0_REPLAY_TO_DEFAULT)))
    {
        return err;
    }
    if ((err = rt_ufs_dme_set(ufs, RT_UFS_UIC_ARG_MIB(RT_UFS_DME_LOCAL_AFC0_REQ_TO), RT_UFS_DL_AFC0_REQ_TO_DEFAULT)))
    {
        return err;
    }

    mode = (rt_uint8_t)((attr->pwr_rx << 4) | (attr->pwr_tx & 0xfu));

    if ((err = rt_ufs_uic_pa_pwrmode(ufs, mode)))
    {
        LOG_E("%s: PA power mode change failed: %s", rt_dm_dev_get_name(ufs->parent.dev), rt_strerror(err));
        return err;
    }

    ufs->pwr_active = *attr;
    ufs->pwr_active_valid = 1;

    return RT_EOK;
}

rt_err_t rt_ufs_hibern8_enter(struct rt_ufs_host *ufs)
{
    rt_uint32_t arg2 = 0;

    if (!ufs || !ufs->regs)
    {
        return -RT_EINVAL;
    }

    if (rt_ufs_uic_cmd_send(ufs, RT_UFS_CMDOP_DME_HIBERNATE_ENTER, 0, &arg2, 0))
    {
        return -RT_ERROR;
    }

    if ((arg2 & RT_UFS_CMDRES_MASK) != RT_UFS_CMDRES_SUCCESS)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

rt_err_t rt_ufs_hibern8_exit(struct rt_ufs_host *ufs)
{
    rt_uint32_t arg2 = 0;

    if (!ufs || !ufs->regs)
    {
        return -RT_EINVAL;
    }

    if (rt_ufs_uic_cmd_send(ufs, RT_UFS_CMDOP_DME_HIBERNATE_EXIT, 0, &arg2, 0))
    {
        return -RT_ERROR;
    }

    if ((arg2 & RT_UFS_CMDRES_MASK) != RT_UFS_CMDRES_SUCCESS)
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

rt_err_t rt_ufs_auto_hibern8_set(struct rt_ufs_host *ufs, rt_uint32_t reg_val)
{
    if (!ufs || !ufs->regs)
    {
        return -RT_EINVAL;
    }

    if (!(ufs->cap & RT_UFS_REG_CAP_AUTOH8))
    {
        return -RT_ENOSYS;
    }

    HWREG32(ufs->regs + RT_UFS_REG_AHIT) = reg_val;
    ufs->ahit = reg_val;

    return RT_EOK;
}

void rt_ufs_intr_aggr_configure(struct rt_ufs_host *ufs, rt_bool_t enable, rt_uint8_t cnt, rt_uint8_t timeout)
{
    void *regs;

    if (!ufs || !(regs = ufs->regs))
    {
        return;
    }

    if (!enable)
    {
        HWREG32(regs + RT_UFS_REG_UTRIACR) = 0;
        return;
    }

    /* Same layout as Linux ufshcd_config_intr_aggr */
    HWREG32(regs + RT_UFS_REG_UTRIACR) = RT_UFS_UTRIACR_ENABLE_PARAMS(cnt, timeout);
}

void rt_ufs_pm_post_linkup(struct rt_ufs_host *ufs)
{
    rt_uint8_t cnt;

    if (!ufs || !ufs->regs)
    {
        return;
    }

    /* Linux INT_AGGR_DEF_TO = 2 (~80µs), counter = nutrs - 1 */
    cnt = (ufs->nutrs > 0) ? (rt_uint8_t)(ufs->nutrs - 1) : 0;
    if (cnt > 31)
    {
        cnt = 31;
    }
    rt_ufs_intr_aggr_configure(ufs, RT_TRUE, cnt, 2);

    if (ufs->cap & RT_UFS_REG_CAP_AUTOH8)
    {
        rt_uint32_t ahit = ufs->ahit ? ufs->ahit : RT_UFS_AHIT_DEFAULT;

        if (rt_ufs_auto_hibern8_set(ufs, ahit))
        {
            LOG_W("%s: Auto-Hibernate8 (AHIT) not applied", rt_dm_dev_get_name(ufs->parent.dev));
        }
        else
        {
            LOG_D("%s: AHIT=%#08x (auto-Hibernate8)", rt_dm_dev_get_name(ufs->parent.dev), ahit);
        }
    }
}
