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

#define DBG_TAG "optee.examples"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*
 * Build the OP-TEE for your platform with the hwrng TA:
 *   https://optee.readthedocs.io/en/latest/building/devices/qemu.html#qemu-v8
 */

static void optee_uuid_copy(rt_uint8_t *d, struct rt_tee_uuid *s)
{
    d[0] = s->time_low >> 24;
    d[1] = s->time_low >> 16;
    d[2] = s->time_low >> 8;
    d[3] = s->time_low;
    d[4] = s->time_mid >> 8;
    d[5] = s->time_mid;
    d[6] = s->time_hi_and_version >> 8;
    d[7] = s->time_hi_and_version;

    rt_memcpy(d + 8, s->clock_seq_and_node, sizeof(s->clock_seq_and_node));
}

static struct rt_tee_open_session_arg *open_session_arg_alloc(rt_uint32_t params_nr)
{
    return rt_calloc(1, sizeof(struct rt_tee_open_session_arg) +
                        sizeof(struct rt_tee_param) * params_nr);
}

static void open_session_arg_free(struct rt_tee_open_session_arg *arg)
{
    rt_free(arg);
}

static struct rt_tee_invoke_arg *invoke_arg_alloc(rt_uint32_t params_nr)
{
    return rt_calloc(1, sizeof(struct rt_tee_invoke_arg) +
                        sizeof(struct rt_tee_param) * params_nr);
}

static void invoke_arg_free(struct rt_tee_invoke_arg *arg)
{
    rt_free(arg);
}

static struct rt_tee_device *open_tee_device(char *name)
{
    struct rt_device *dev = rt_device_find(name ? : "tee0");

    if (dev && !rt_device_open(dev, 0))
    {
        return rt_container_of(dev, struct rt_tee_device, parent);
    }

    return RT_NULL;
}

static void close_tee_device(struct rt_tee_device *tdev)
{
    rt_device_close(&tdev->parent);
}

/*
 * This UUID is generated with uuidgen
 * the ITU-T UUID generator at http://www.itu.int/ITU-T/asn1/uuid.html
 */
static int optee_example_rng(int argc, char**argv)
{
    rt_err_t err;
    struct rt_tee_shm shm;
    struct rt_tee_device *tdev;
    struct rt_tee_invoke_arg *invoke;
    struct rt_tee_open_session_arg *open;
    struct rt_tee_uuid uuid =
    {
        0xab7a617c, 0xb8e7, 0x4d8f,
        { 0x83, 0x01, 0xd0, 0x9b, 0x61, 0x03, 0x6b, 0x64 }
    };

    if (!(tdev = open_tee_device(RT_NULL)))
    {
        return -RT_EIO;
    }

    if (!(open = open_session_arg_alloc(0)))
    {
        err = -RT_ENOMEM;
        goto _close_tee;
    }

    optee_uuid_copy(open->uuid, &uuid);

    if ((err = rt_tee_open_session(tdev, open)))
    {
        goto _free_args;
    }

    shm.size = 32;
    shm.align = RT_MM_PAGE_SIZE;
    shm.flags = TEE_SHM_SYS;

    if ((err = rt_tee_shm_register(tdev, &shm)))
    {
        goto _close_session;
    }

    rt_memset(shm.vaddr, 0, shm.size);

    if (!(invoke = invoke_arg_alloc(1)))
    {
        err = -RT_ENOMEM;
        goto _free_shm;
    }

    /* TA_CMD_GET_ENTROPY */
    invoke->func = 0x0;
    invoke->session = open->session;
    invoke->cancel_id = 0;
    invoke->params_nr = 1;

    invoke->params[0].attr = TEE_PARAM_ATTR_TYPE_MEMREF_OUT;
    invoke->params[0].memref.size = shm.size;
    invoke->params[0].memref.shm = &shm;
    invoke->params[0].memref.shm_offs = 0;

    err = rt_tee_invoke(tdev, invoke);

    if (!err && invoke->ret == RT_TEE_SUCCESS)
    {
        rt_uint8_t *rng = shm.vaddr;

        for (int i = 0; i < shm.size; ++i)
        {
            rt_kprintf("RNG[%02d]: %02x\n", i, rng[i]);
        }
    }
    else
    {
        rt_kprintf("Failed to read RNG: err=%x origin=%x\n", invoke->ret, invoke->ret_origin);
    }

    invoke_arg_free(invoke);

_free_shm:
    rt_tee_shm_unregister(tdev, &shm);
    rt_tee_shm_free_helper(&shm);

_close_session:
    rt_tee_close_session(tdev, open->session);

_free_args:
    open_session_arg_free(open);

_close_tee:
    close_tee_device(tdev);

    return (int)err;
}
MSH_CMD_EXPORT(optee_example_rng, optee example rng);
