/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-23     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "tee.optee"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <smccc.h>
#include "optee_msg.h"
#include "optee_smc.h"

#define PAGELIST_ENTRIES_PER_PAGE   ((OPTEE_MSG_NONCONTIG_PAGE_SIZE / sizeof(rt_uint64_t)) - 1)

typedef void (*optee_call_handle)(rt_ubase_t a0, rt_ubase_t a1,
        rt_ubase_t a2, rt_ubase_t a3, rt_ubase_t a4, rt_ubase_t a5,
        rt_ubase_t a6, rt_ubase_t a7, struct arm_smccc_res_t *out_res);

struct optee_device
{
    struct rt_tee_device parent;

    optee_call_handle call;
};

#define raw_to_optee(tdev) rt_container_of(tdev, struct optee_device, parent)

static void optee_call_smc(rt_ubase_t a0, rt_ubase_t a1,
        rt_ubase_t a2, rt_ubase_t a3, rt_ubase_t a4, rt_ubase_t a5,
        rt_ubase_t a6, rt_ubase_t a7, struct arm_smccc_res_t *out_res)
{
    arm_smccc_smc(a0, a1, a2, a3, a4, a5, a6, a7, out_res, RT_NULL);
}

static void optee_call_hvc(rt_ubase_t a0, rt_ubase_t a1,
        rt_ubase_t a2, rt_ubase_t a3, rt_ubase_t a4, rt_ubase_t a5,
        rt_ubase_t a6, rt_ubase_t a7, struct arm_smccc_res_t *out_res)
{
    arm_smccc_hvc(a0, a1, a2, a3, a4, a5, a6, a7, out_res, RT_NULL);
}

static rt_bool_t msg_api_uid_is_optee_api(struct optee_device *optee)
{
    struct arm_smccc_res_t res;

    optee->call(OPTEE_SMC_CALLS_UID, 0, 0, 0, 0, 0, 0, 0, &res);

    return res.a0 == OPTEE_MSG_UID_0 && res.a1 == OPTEE_MSG_UID_1 &&
            res.a2 == OPTEE_MSG_UID_2 && res.a3 == OPTEE_MSG_UID_3;
}

static rt_bool_t exchange_capabilities(struct optee_device *optee,
        rt_uint32_t *sec_caps)
{
    union
    {
        struct arm_smccc_res_t smccc;
        struct optee_smc_exchange_capabilities_result result;
    } res;

    optee->call(OPTEE_SMC_EXCHANGE_CAPABILITIES,
            OPTEE_SMC_NSEC_CAP_UNIPROCESSOR, 0, 0, 0, 0, 0, 0, &res.smccc);

    if (res.result.status != OPTEE_SMC_RETURN_OK)
    {
        return RT_FALSE;
    }

    *sec_caps = res.result.capabilities;

    return RT_TRUE;
}

static rt_err_t to_msg_param(struct optee_msg_param *msg_params,
        rt_uint32_t params_nr, const struct rt_tee_param *raw_params)
{
    for (int n = 0; n < params_nr; ++n, ++msg_params, ++raw_params)
    {
        rt_memset(msg_params, 0, sizeof(*msg_params));

        switch (raw_params->attr)
        {
        case TEE_PARAM_ATTR_TYPE_NONE:
            msg_params->attr = OPTEE_MSG_ATTR_TYPE_NONE;
            break;

        case TEE_PARAM_ATTR_TYPE_VALUE_IN:
        case TEE_PARAM_ATTR_TYPE_VALUE_OUT:
        case TEE_PARAM_ATTR_TYPE_VALUE_IN_OUT:
            msg_params->attr = OPTEE_MSG_ATTR_TYPE_VALUE_INPUT;
            msg_params->attr += raw_params->attr - TEE_PARAM_ATTR_TYPE_VALUE_IN;
            msg_params->value.a = raw_params->value.a;
            msg_params->value.b = raw_params->value.b;
            msg_params->value.c = raw_params->value.c;
            break;

        case TEE_PARAM_ATTR_TYPE_MEMREF_IN:
        case TEE_PARAM_ATTR_TYPE_MEMREF_OUT:
        case TEE_PARAM_ATTR_TYPE_MEMREF_IN_OUT:
            msg_params->attr = OPTEE_MSG_ATTR_TYPE_RMEM_INPUT;
            msg_params->attr += raw_params->attr - TEE_PARAM_ATTR_TYPE_MEMREF_IN;
            msg_params->rmem.shm_ref = (rt_ubase_t)raw_params->memref.shm;
            msg_params->rmem.size = raw_params->memref.size;
            msg_params->rmem.offs = raw_params->memref.shm_offs;
            break;

        default:
            return -RT_EINVAL;
        }
    }

    return RT_EOK;
}

static rt_err_t from_msg_param(struct rt_tee_param *raw_params,
        rt_uint32_t params_nr, const struct optee_msg_param *msg_params)
{
    for (int n = 0; n < params_nr; ++n, ++raw_params, ++msg_params)
    {
        rt_uint32_t attr = msg_params->attr & OPTEE_MSG_ATTR_TYPE_MASK;

        rt_memset(raw_params, 0, sizeof(*raw_params));

        switch (attr)
        {
        case OPTEE_MSG_ATTR_TYPE_NONE:
            raw_params->attr = TEE_PARAM_ATTR_TYPE_NONE;
            break;

        case OPTEE_MSG_ATTR_TYPE_VALUE_INPUT:
        case OPTEE_MSG_ATTR_TYPE_VALUE_OUTPUT:
        case OPTEE_MSG_ATTR_TYPE_VALUE_INOUT:
            raw_params->attr = TEE_PARAM_ATTR_TYPE_VALUE_IN;
            raw_params->attr += msg_params->attr - OPTEE_MSG_ATTR_TYPE_VALUE_INPUT;
            raw_params->value.a = msg_params->value.a;
            raw_params->value.b = msg_params->value.b;
            raw_params->value.c = msg_params->value.c;
            break;

        case OPTEE_MSG_ATTR_TYPE_RMEM_INPUT:
        case OPTEE_MSG_ATTR_TYPE_RMEM_OUTPUT:
        case OPTEE_MSG_ATTR_TYPE_RMEM_INOUT:
            raw_params->attr = TEE_PARAM_ATTR_TYPE_MEMREF_IN;
            raw_params->attr += msg_params->attr - OPTEE_MSG_ATTR_TYPE_RMEM_INPUT;

            raw_params->memref.size = msg_params->rmem.size;
            raw_params->memref.shm = (void *)(rt_ubase_t)msg_params->rmem.shm_ref;
            raw_params->memref.shm_offs = raw_params->memref.shm ?
                    msg_params->rmem.offs : 0;
            break;

        default:
            return -RT_EINVAL;
        }
    }

    return RT_EOK;
}

static void *alloc_page_list(void *buf, rt_size_t len, rt_uint64_t *out_paddr)
{
    const rt_size_t page_size = OPTEE_MSG_NONCONTIG_PAGE_SIZE;
    void *page_list;
    rt_uint8_t *buf_base;
    unsigned int page_offset, num_pages, list_size;
    struct
    {
        rt_uint64_t pages_list[PAGELIST_ENTRIES_PER_PAGE];
        rt_uint64_t next_page_data;
    } *pages_data;

    page_offset = (rt_ubase_t)buf & (page_size - 1);
    num_pages = rt_roundup(page_offset + len, page_size) / page_size;
    list_size = RT_DIV_ROUND_UP(num_pages, PAGELIST_ENTRIES_PER_PAGE) * page_size;

    if (!(page_list = rt_malloc_align(list_size, page_size)))
    {
        return RT_NULL;
    }

    pages_data = page_list;
    buf_base = (rt_uint8_t *)rt_rounddown((rt_ubase_t)buf, page_size);

    for (int n = 0; num_pages; --num_pages)
    {
        pages_data->pages_list[n++] = (rt_uint64_t)rt_kmem_v2p(buf_base);
        buf_base += page_size;

        if (n == PAGELIST_ENTRIES_PER_PAGE)
        {
            pages_data->next_page_data = (rt_uint64_t)rt_kmem_v2p(pages_data + 1);
            ++pages_data;
            n = 0;
        }
    }

    *out_paddr = (rt_ubase_t)rt_kmem_v2p(page_list) | page_offset;

    return page_list;
}

static void free_page_list(void *page_list)
{
    rt_free_align(page_list);
}

static struct optee_msg_arg *alloc_msg_arg(rt_uint32_t params_nr)
{
    rt_size_t size;
    struct optee_msg_arg *msg_arg;

    size = OPTEE_MSG_GET_ARG_SIZE(params_nr);
    msg_arg = rt_malloc_align(size, OPTEE_MSG_NONCONTIG_PAGE_SIZE);

    if (!msg_arg)
    {
        return RT_NULL;
    }

    rt_memset(msg_arg, 0, size);
    msg_arg->params_nr = params_nr;

    return msg_arg;
}

static void free_msg_arg(struct optee_msg_arg *msg_arg)
{
    rt_free_align(msg_arg);
}

static void supplicant_cmd_shm_alloc(struct optee_device *optee,
        struct optee_msg_arg *msg_arg, void **page_list)
{
    rt_err_t err;
    rt_uint64_t paddr;
    struct rt_tee_shm *shm;

    msg_arg->ret_origin = RT_TEE_ORIGIN_COMMS;

    if (msg_arg->params_nr != 1 ||
        msg_arg->params[0].attr != OPTEE_MSG_ATTR_TYPE_VALUE_INPUT)
    {
        msg_arg->ret = RT_TEE_ERROR_BAD_PARAMETERS;
        return;
    }

    if (!(shm = rt_calloc(1, sizeof(*shm))))
    {
        msg_arg->ret = RT_TEE_ERROR_OUT_OF_MEMORY;
        return;
    }

    shm->size = msg_arg->params[0].value.b;
    shm->align = OPTEE_MSG_NONCONTIG_PAGE_SIZE;
    shm->flags = TEE_SHM_SYS;

    if ((err = rt_tee_shm_register(&optee->parent, shm)))
    {
        if (err == -RT_ENOMEM)
        {
            msg_arg->ret = RT_TEE_ERROR_OUT_OF_MEMORY;
        }
        else
        {
            msg_arg->ret = RT_TEE_ERROR_GENERIC;
        }

        rt_free(shm);
        return;
    }

    if (!(*page_list = alloc_page_list(shm->vaddr, shm->size, &paddr)))
    {
        msg_arg->ret = RT_TEE_ERROR_OUT_OF_MEMORY;

        rt_tee_shm_unregister(&optee->parent, shm);
        rt_free(shm);
        return;
    }

    msg_arg->params[0].attr = OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT |
            OPTEE_MSG_ATTR_NONCONTIG;
    msg_arg->params[0].tmem.buf_ptr = paddr;
    msg_arg->params[0].tmem.size = shm->size;
    msg_arg->params[0].tmem.shm_ref = (rt_ubase_t)(void *)shm;
    msg_arg->ret = RT_TEE_SUCCESS;
}

static void supplicant_cmd_shm_free(struct optee_device *optee,
        struct optee_msg_arg *msg_arg)
{
    struct rt_tee_shm *shm;
    rt_err_t err;

    msg_arg->ret_origin = RT_TEE_ORIGIN_COMMS;

    if (msg_arg->params_nr != 1 ||
        msg_arg->params[0].attr != OPTEE_MSG_ATTR_TYPE_VALUE_INPUT)
    {
        msg_arg->ret = RT_TEE_ERROR_BAD_PARAMETERS;
        return;
    }

    shm = (struct rt_tee_shm *)(rt_ubase_t)msg_arg->params[0].value.b;
    if (!shm)
    {
        msg_arg->ret = RT_TEE_ERROR_BAD_PARAMETERS;
        return;
    }

    if ((err = rt_tee_shm_unregister(&optee->parent, shm)))
    {
        msg_arg->ret = RT_TEE_ERROR_GENERIC;
        return;
    }

    rt_tee_shm_free_helper(shm);
    rt_free(shm);
    msg_arg->ret = RT_TEE_SUCCESS;
}

static void supplicant_cmd_i2c_transfer(struct optee_msg_arg *msg_arg)
{
#ifdef RT_USING_I2C
    char devname[RT_NAME_MAX];
    struct rt_tee_shm *shm;
    struct rt_i2c_msg msg;
    struct rt_i2c_bus_device *adapter;
    const rt_uint8_t attr[] =
    {
        OPTEE_MSG_ATTR_TYPE_VALUE_INPUT,
        OPTEE_MSG_ATTR_TYPE_VALUE_INPUT,
        OPTEE_MSG_ATTR_TYPE_RMEM_INOUT,
        OPTEE_MSG_ATTR_TYPE_VALUE_OUTPUT,
    };

    if (msg_arg->params_nr != RT_ARRAY_SIZE(attr) ||
        msg_arg->params[0].attr != attr[0] ||
        msg_arg->params[1].attr != attr[1] ||
        msg_arg->params[2].attr != attr[2] ||
        msg_arg->params[3].attr != attr[3])
    {
        msg_arg->ret = RT_TEE_ERROR_BAD_PARAMETERS;
        return;
    }

    shm = (void *)msg_arg->params[2].rmem.shm_ref;

    rt_sprintf(devname, "i2c%u", msg_arg->params[0].value.b);

    if (!(adapter = rt_i2c_bus_device_find(devname)))
    {
        goto _not_supp;
    }

    if (msg_arg->params[1].value.a & OPTEE_MSG_RPC_CMD_I2C_FLAGS_TEN_BIT)
    {
        if (!(adapter->flags & RT_I2C_ADDR_10BIT))
        {
            goto _not_supp;
        }

        msg.flags = RT_I2C_ADDR_10BIT;
    }

    msg.addr = msg_arg->params[0].value.c;
    msg.len = msg_arg->params[2].rmem.size;
    msg.buf = shm->vaddr;

    switch (msg_arg->params[0].value.a)
    {
    case OPTEE_MSG_RPC_CMD_I2C_TRANSFER_RD:
        msg.flags |= RT_I2C_RD;
        break;

    case OPTEE_MSG_RPC_CMD_I2C_TRANSFER_WR:
        break;

    default:
        goto _not_supp;
    }

    if (rt_i2c_transfer(adapter, &msg, 1) <= 0)
    {
        msg_arg->ret = RT_TEE_ERROR_COMMUNICATION;
    }
    else
    {
        msg_arg->params[3].value.a = msg.len;
        msg_arg->ret = RT_TEE_SUCCESS;
    }

    return;

_not_supp:
#endif /* RT_USING_I2C */
    msg_arg->ret = RT_TEE_ERROR_NOT_SUPPORTED;
}

static void supplicant_cmd(struct optee_device *optee, struct rt_tee_shm *shm,
        void **page_list)
{
    struct optee_msg_arg *msg_arg = shm->vaddr;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, shm->vaddr, shm->size);

    switch (msg_arg->cmd)
    {
    case OPTEE_MSG_RPC_CMD_SHM_ALLOC:
        supplicant_cmd_shm_alloc(optee, msg_arg, page_list);
        break;

    case OPTEE_MSG_RPC_CMD_SHM_FREE:
        supplicant_cmd_shm_free(optee, msg_arg);
        break;

    case OPTEE_MSG_RPC_CMD_I2C_TRANSFER:
        supplicant_cmd_i2c_transfer(msg_arg);
        break;

    default:
        msg_arg->ret = RT_TEE_ERROR_NOT_IMPLEMENTED;
    }
}

static rt_err_t call_with_arg(struct optee_device *optee,
        struct optee_msg_arg *msg_arg)
{
    rt_err_t err;
    void *arg_paddr, *page_list = NULL;
    rt_ubase_t a0, a1, a2, a4, a5;
    struct rt_tee_shm *shm;
    struct arm_smccc_res_t res;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH,
            msg_arg, OPTEE_MSG_GET_ARG_SIZE(msg_arg->params_nr));

    arg_paddr = rt_kmem_v2p(msg_arg);
    a0 = OPTEE_SMC_CALL_WITH_ARG;
    a1 = (rt_ubase_t)arg_paddr >> 32;
    a2 = (rt_ubase_t)arg_paddr & RT_UINT32_MAX;
    a4 = 0;
    a5 = 0;

    while (RT_TRUE)
    {
        optee->call(a0, a1, a2, 0, a4, a5, 0, 0, &res);
        a4 = a5 = 0;

        if (page_list)
        {
            free_page_list(page_list);
            page_list = RT_NULL;
        }

        if (!OPTEE_SMC_RETURN_IS_RPC(res.a0))
        {
            err = res.a0 == OPTEE_SMC_RETURN_OK ? RT_EOK : -RT_EINVAL;
            break;
        }

        switch (OPTEE_SMC_RETURN_GET_RPC_FUNC(res.a0))
        {
        case OPTEE_SMC_RPC_FUNC_ALLOC:
            if (!(shm = rt_calloc(1, sizeof(*shm))))
            {
                return -RT_ENOMEM;
            }

            shm->align = OPTEE_MSG_NONCONTIG_PAGE_SIZE;
            shm->size = res.a1;

            if (rt_tee_shm_alloc_helper(shm) == RT_EOK)
            {
                arg_paddr = (void *)shm->paddr;
                a1 = (rt_ubase_t)arg_paddr >> 32;
                a2 = (rt_ubase_t)arg_paddr & RT_UINT32_MAX;

                /* Cookie */
                arg_paddr = (void *)shm;
                a4 = (rt_ubase_t)arg_paddr >> 32;
                a5 = (rt_ubase_t)arg_paddr & RT_UINT32_MAX;
            }
            else
            {
                rt_free(shm);
                a1 = a2 = 0;
            }
            break;

        case OPTEE_SMC_RPC_FUNC_FREE:
            shm = (void *)(((rt_uint64_t)res.a1 << 32) | res.a2);

            rt_tee_shm_free_helper(shm);
            rt_free(shm);
            break;

        case OPTEE_SMC_RPC_FUNC_FOREIGN_INTR:
            break;

        case OPTEE_SMC_RPC_FUNC_CMD:
            shm = (void *)(((rt_uint64_t)res.a1 << 32) | res.a2);

            supplicant_cmd(optee, shm, &page_list);
            break;

        default:
            break;
        }

        a0 = OPTEE_SMC_CALL_RETURN_FROM_RPC;
    }

    return err;
}

static rt_err_t optee_get_version(struct rt_tee_device *tdev,
            struct rt_tee_version *out_version)
{
    out_version->impl_id = TEE_IMPL_ID_OPTEE;
    out_version->impl_caps = TEE_OPTEE_CAP_TZ;
    out_version->gen_caps = TEE_GEN_CAP_GP;

    return RT_EOK;
}

static rt_err_t optee_open_session(struct rt_tee_device *tdev,
        struct rt_tee_open_session_arg *arg)
{
    rt_err_t err;
    struct optee_msg_arg *msg_arg;
    struct optee_device *optee = raw_to_optee(tdev);

    if (!(msg_arg = alloc_msg_arg(arg->params_nr + 2)))
    {
        return -RT_ENOMEM;
    }

    msg_arg->cmd = OPTEE_MSG_CMD_OPEN_SESSION;
    msg_arg->params[0].attr = OPTEE_MSG_ATTR_TYPE_VALUE_INPUT |
            OPTEE_MSG_ATTR_META;
    msg_arg->params[1].attr = OPTEE_MSG_ATTR_TYPE_VALUE_INPUT |
            OPTEE_MSG_ATTR_META;
    rt_memcpy(&msg_arg->params[0].value, arg->uuid, sizeof(arg->uuid));
    rt_memcpy(&msg_arg->params[1].value, arg->uuid, sizeof(arg->clnt_uuid));
    msg_arg->params[1].value.c = arg->clnt_login;

    if ((err = to_msg_param(msg_arg->params + 2, arg->params_nr, arg->params)))
    {
        goto _free_msg_arg;
    }

    if ((err = call_with_arg(optee, msg_arg)))
    {
        if (err == -RT_ENOMEM)
        {
            arg->ret = RT_TEE_ERROR_OUT_OF_MEMORY;
        }
        else
        {
            arg->ret = RT_TEE_ERROR_GENERIC;
        }
        arg->ret_origin = RT_TEE_ORIGIN_COMMS;
        goto _free_msg_arg;
    }

    if ((err = from_msg_param(arg->params, arg->params_nr, msg_arg->params + 2)))
    {
        arg->ret = RT_TEE_ERROR_COMMUNICATION;
        arg->ret_origin = RT_TEE_ORIGIN_COMMS;
        tdev->ops->close_session(tdev, msg_arg->session);
        goto _free_msg_arg;
    }

    arg->session = msg_arg->session;
    arg->ret = msg_arg->ret;
    arg->ret_origin = msg_arg->ret_origin;

_free_msg_arg:
    free_msg_arg(msg_arg);

    return err;
}

static rt_err_t optee_close_session(struct rt_tee_device *tdev,
        rt_uint32_t session)
{
    rt_err_t err;
    struct optee_msg_arg *msg_arg;
    struct optee_device *optee = raw_to_optee(tdev);

    if (!(msg_arg = alloc_msg_arg(1)))
    {
        return -RT_ENOMEM;
    }

    msg_arg->cmd = OPTEE_MSG_CMD_CLOSE_SESSION;
    msg_arg->session = session;
    err = call_with_arg(optee, msg_arg);

    free_msg_arg(msg_arg);

    return err;
}

static rt_err_t optee_invoke(struct rt_tee_device *tdev,
        struct rt_tee_invoke_arg *arg)
{
    rt_err_t err;
    struct optee_msg_arg *msg_arg;
    struct optee_device *optee = raw_to_optee(tdev);

    if (!(msg_arg = alloc_msg_arg(arg->params_nr)))
    {
        return -RT_ENOMEM;
    }

    msg_arg->cmd = OPTEE_MSG_CMD_INVOKE_COMMAND;
    msg_arg->func = arg->func;
    msg_arg->session = arg->session;

    if ((err = to_msg_param(msg_arg->params, arg->params_nr, arg->params)))
    {
        goto _free_msg_arg;
    }

    if ((err = call_with_arg(optee, msg_arg)))
    {
        if (err == -RT_ENOMEM)
        {
            arg->ret = RT_TEE_ERROR_OUT_OF_MEMORY;
        }
        else
        {
            arg->ret = RT_TEE_ERROR_GENERIC;
        }
        arg->ret_origin = RT_TEE_ORIGIN_COMMS;
        goto _free_msg_arg;
    }

    if ((err = from_msg_param(arg->params, arg->params_nr, msg_arg->params)))
    {
        arg->ret = RT_TEE_ERROR_COMMUNICATION;
        arg->ret_origin = RT_TEE_ORIGIN_COMMS;
        goto _free_msg_arg;
    }

    arg->ret = msg_arg->ret;
    arg->ret_origin = msg_arg->ret_origin;

_free_msg_arg:
    free_msg_arg(msg_arg);

    return err;
}

static rt_err_t optee_cancel(struct rt_tee_device *tdev,
            rt_uint32_t session, rt_uint32_t cancel_id)
{
    rt_err_t err = RT_EOK;
    struct optee_msg_arg *msg_arg;
    struct optee_device *optee = raw_to_optee(tdev);

    if (!(msg_arg = alloc_msg_arg(1)))
    {
        return -RT_ENOMEM;
    }

    msg_arg->cmd = OPTEE_MSG_CMD_CANCEL;
    msg_arg->session = session;
    msg_arg->cancel_id = cancel_id;
    err = call_with_arg(optee, msg_arg);

    free_msg_arg(msg_arg);

    return err;
}

static rt_err_t optee_shm_register(struct rt_tee_device *tdev,
        struct rt_tee_shm *shm)
{
    rt_err_t err;
    rt_uint64_t paddr;
    void *page_list;
    struct optee_msg_arg *msg_arg;
    struct optee_device *optee = raw_to_optee(tdev);

    if (shm->flags & TEE_SHM_DRV && !shm->vaddr)
    {
        return -RT_ENOSYS;
    }

    if (!(msg_arg = alloc_msg_arg(1)))
    {
        return -RT_ENOMEM;
    }

    page_list = alloc_page_list(shm->vaddr, shm->size, &paddr);
    if (!page_list)
    {
        err = -RT_ENOMEM;
        goto _free_msg_arg;
    }

    msg_arg->cmd = OPTEE_MSG_CMD_REGISTER_SHM;
    msg_arg->params->attr = OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT |
            OPTEE_MSG_ATTR_NONCONTIG;
    msg_arg->params->tmem.buf_ptr = paddr;
    msg_arg->params->tmem.shm_ref = (rt_ubase_t)shm;
    msg_arg->params->tmem.size = shm->size;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH,
            msg_arg, OPTEE_MSG_GET_ARG_SIZE(msg_arg->params_nr));

    if ((err = call_with_arg(optee, msg_arg)) || msg_arg->ret)
    {
        err = err ? : -RT_EINVAL;
    }

    free_page_list(page_list);

_free_msg_arg:
    free_msg_arg(msg_arg);

    return err;
}

static rt_err_t optee_shm_unregister(struct rt_tee_device *tdev,
        struct rt_tee_shm *shm)
{
    rt_err_t err;
    struct optee_msg_arg *msg_arg;
    struct optee_device *optee = raw_to_optee(tdev);

    if (!(msg_arg = alloc_msg_arg(1)))
    {
        return -RT_ENOMEM;
    }

    msg_arg->cmd = OPTEE_MSG_CMD_UNREGISTER_SHM;
    msg_arg->params[0].attr = OPTEE_MSG_ATTR_TYPE_RMEM_INPUT;
    msg_arg->params[0].rmem.shm_ref = (rt_ubase_t)shm;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH,
            msg_arg, OPTEE_MSG_GET_ARG_SIZE(msg_arg->params_nr));

    if ((err = call_with_arg(optee, msg_arg)) || msg_arg->ret)
    {
        err = err ? : -RT_EINVAL;
    }

    free_msg_arg(msg_arg);

    return err;
}

static struct rt_tee_ops optee_ops =
{
    .get_version = optee_get_version,
    .open_session = optee_open_session,
    .close_session = optee_close_session,
    .invoke = optee_invoke,
    .cancel = optee_cancel,
    .shm_register = optee_shm_register,
    .shm_unregister = optee_shm_unregister,
};

static rt_err_t optee_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *method;
    rt_uint32_t sec_caps;
    struct rt_device *dev = &pdev->parent;
    struct optee_device *optee = rt_calloc(1, sizeof(*optee));

    if (!optee)
    {
        return -RT_ENOMEM;
    }

    if (!rt_dm_dev_prop_read_string(dev, "method", &method))
    {
        if (!rt_strcmp(method, "smc"))
        {
            optee->call = optee_call_smc;
        }
        else if (!rt_strcmp(method, "hvc"))
        {
            optee->call = optee_call_hvc;
        }
        else
        {
            err = -RT_EINVAL;
            LOG_E("Invalid \"method\" property: %s", method);
            goto _fail;
        }
    }
    else
    {
        optee->call = optee_call_smc;
    }

    if (!msg_api_uid_is_optee_api(optee))
    {
        LOG_E("Not OP-TEE API supported");
        err = -RT_EINVAL;
        goto _fail;
    }

    if (!exchange_capabilities(optee, &sec_caps) ||
        !(sec_caps & OPTEE_SMC_SEC_CAP_DYNAMIC_SHM))
    {
        LOG_E("Not OP-TEE capabilities supported");
        err = -RT_EINVAL;
        goto _fail;
    }

    optee->parent.ops = &optee_ops;

    if ((err = rt_tee_device_register(&optee->parent)))
    {
        goto _fail;
    }

    dev->user_data = optee;

    /* Enum services here */

    return RT_EOK;

_fail:
    rt_free(optee);

    return err;
}

static rt_err_t optee_remove(struct rt_platform_device *pdev)
{
    struct optee_device *optee = pdev->parent.user_data;

    if (optee)
    {
        rt_tee_device_unregister(&optee->parent);
        rt_free(optee);
        pdev->parent.user_data = RT_NULL;
    }

    return RT_EOK;
}

static const struct rt_ofw_node_id optee_ofw_ids[] =
{
    { .compatible = "linaro,optee-tz" },
    { /* sentinel */ }
};

static struct rt_platform_driver optee_driver =
{
    .name = "optee-smc",
    .ids = optee_ofw_ids,

    .probe = optee_probe,
    .remove = optee_remove,
};
RT_PLATFORM_DRIVER_EXPORT(optee_driver);
