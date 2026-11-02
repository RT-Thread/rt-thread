/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-23     GuEe-GUI     first version
 */

#ifndef __TEE_H__
#define __TEE_H__

#include <rtthread.h>
#include <drivers/misc.h>

#define RT_TEE_SUCCESS                          0x00000000
#define RT_TEE_ERROR_STORAGE_NOT_AVAILABLE      0xf0100003
#define RT_TEE_ERROR_GENERIC                    0xffff0000
#define RT_TEE_ERROR_EXCESS_DATA                0xffff0004
#define RT_TEE_ERROR_BAD_PARAMETERS             0xffff0006
#define RT_TEE_ERROR_ITEM_NOT_FOUND             0xffff0008
#define RT_TEE_ERROR_NOT_IMPLEMENTED            0xffff0009
#define RT_TEE_ERROR_NOT_SUPPORTED              0xffff000a
#define RT_TEE_ERROR_COMMUNICATION              0xffff000e
#define RT_TEE_ERROR_SECURITY                   0xffff000f
#define RT_TEE_ERROR_SHORT_BUFFER               0xffff0010
#define RT_TEE_ERROR_OUT_OF_MEMORY              0xffff000c
#define RT_TEE_ERROR_OVERFLOW                   0xffff300f
#define RT_TEE_ERROR_TARGET_DEAD                0xffff3024
#define RT_TEE_ERROR_STORAGE_NO_SPACE           0xffff3041

#define RT_TEE_ORIGIN_COMMS                     0x00000002
#define RT_TEE_ORIGIN_TEE                       0x00000003
#define RT_TEE_ORIGIN_TRUSTED_APP               0x00000004

struct rt_tee_ops;

struct rt_tee_device
{
    struct rt_device parent;

    rt_list_t shm_nodes;

    const struct rt_tee_ops *ops;
    struct rt_mutex mutex;
};
#define rt_device_to_tee_device(dev) rt_container_of(dev, struct rt_tee_device, parent)

struct rt_tee_version
{
#define TEE_IMPL_ID_OPTEE       1
#define TEE_IMPL_ID_AMDTEE      2
    /* TEE implementation id */
    rt_uint32_t impl_id;
#define TEE_OPTEE_CAP_TZ        RT_BIT(0)
    /* Implementation specific capabilities */
    rt_uint32_t impl_caps;
#define TEE_GEN_CAP_GP          RT_BIT(0)   /* GlobalPlatform compliant TEE */
#define TEE_GEN_CAP_PRIVILEGED  RT_BIT(1)   /* Privileged device (for supplicant) */
#define TEE_GEN_CAP_REG_MEM     RT_BIT(2)   /* Supports registering shared memory */
#define TEE_GEN_CAP_MEMREF_NULL RT_BIT(3)   /* NULL MemRef support */
    /* Generic capabilities */
    rt_uint32_t gen_caps;
};

struct rt_tee_shm
{
    rt_list_t list;
    struct rt_tee_device *tdev;

    void *vaddr;
    rt_ubase_t paddr;
    rt_size_t size;
    rt_size_t align;
#define TEE_SHM_DRV             RT_BIT(0)  /* Memory allocated from pool */
#define TEE_SHM_SYS             RT_BIT(1)  /* Memory allocated from system */
#define TEE_SHM_USER            RT_BIT(2)  /* Memory from user */
    rt_uint32_t flags;
};

struct rt_tee_param_memref
{
    rt_off_t shm_offs;
    rt_size_t size;
    struct rt_tee_shm *shm;
};

struct rt_tee_param_value
{
    rt_uint64_t a;
    rt_uint64_t b;
    rt_uint64_t c;
};

struct rt_tee_param
{
#define TEE_PARAM_ATTR_TYPE_NONE            0
#define TEE_PARAM_ATTR_TYPE_VALUE_IN        1
#define TEE_PARAM_ATTR_TYPE_VALUE_OUT       2
#define TEE_PARAM_ATTR_TYPE_VALUE_IN_OUT    3
#define TEE_PARAM_ATTR_TYPE_MEMREF_IN       5
#define TEE_PARAM_ATTR_TYPE_MEMREF_OUT      6
#define TEE_PARAM_ATTR_TYPE_MEMREF_IN_OUT   7
    rt_uint64_t attr;

    union
    {
        struct rt_tee_param_memref memref;
        struct rt_tee_param_value value;
    };
};

rt_packed(struct rt_tee_uuid
{
   rt_uint32_t time_low;
   rt_uint16_t time_mid;
   rt_uint16_t time_hi_and_version;
   rt_uint8_t clock_seq_and_node[8];
});

struct rt_tee_open_session_arg
{
    rt_uint8_t uuid[16];
    rt_uint8_t clnt_uuid[16];
    rt_uint32_t clnt_login;
    rt_uint32_t cancel_id;
    rt_uint32_t session;
    rt_uint32_t ret;
    rt_uint32_t ret_origin;

    rt_uint32_t params_nr;
    struct rt_tee_param params[];
};

struct rt_tee_invoke_arg
{
    rt_uint32_t func;
    rt_uint32_t session;
    rt_uint32_t cancel_id;
    rt_uint32_t ret;
    rt_uint32_t ret_origin;

    rt_uint32_t params_nr;
    struct rt_tee_param params[];
};

struct rt_tee_ops
{
    rt_err_t (*get_version)(struct rt_tee_device *tdev,
            struct rt_tee_version *out_version);

    rt_err_t (*open_session)(struct rt_tee_device *tdev,
            struct rt_tee_open_session_arg *arg);
    rt_err_t (*close_session)(struct rt_tee_device *tdev, rt_uint32_t session);

    rt_err_t (*invoke)(struct rt_tee_device *tdev,
            struct rt_tee_invoke_arg *arg);
    rt_err_t (*cancel)(struct rt_tee_device *tdev,
            rt_uint32_t session, rt_uint32_t cancel_id);

    rt_err_t (*shm_register)(struct rt_tee_device *tdev, struct rt_tee_shm *shm);
    rt_err_t (*shm_unregister)(struct rt_tee_device *tdev, struct rt_tee_shm *shm);
};

rt_err_t rt_tee_device_register(struct rt_tee_device *tdev);
rt_err_t rt_tee_device_unregister(struct rt_tee_device *tdev);

rt_err_t rt_tee_get_version(struct rt_tee_device *tdev,
        struct rt_tee_version *out_version);

rt_err_t rt_tee_open_session(struct rt_tee_device *tdev,
        struct rt_tee_open_session_arg *arg);
rt_err_t rt_tee_close_session(struct rt_tee_device *tdev, rt_uint32_t session);

rt_err_t rt_tee_invoke(struct rt_tee_device *tdev,
        struct rt_tee_invoke_arg *arg);

rt_err_t rt_tee_cancel(struct rt_tee_device *tdev,
        rt_uint32_t session, rt_uint32_t cancel_id);

rt_err_t rt_tee_shm_alloc_helper(struct rt_tee_shm *shm);
rt_err_t rt_tee_shm_free_helper(struct rt_tee_shm *shm);
rt_err_t rt_tee_shm_register(struct rt_tee_device *tdev, struct rt_tee_shm *shm);
rt_err_t rt_tee_shm_unregister(struct rt_tee_device *tdev, struct rt_tee_shm *shm);

#endif /* __TEE_H__ */
