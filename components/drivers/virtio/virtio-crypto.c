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

#define DBG_TAG "virtio.dev.crypto"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "virtio_config/virtio-crypto.h"

struct virtio_crypto_symmetric_contex
{
    rt_uint64_t session_id;
    struct rt_virtqueue *data_vq;
};

struct virtio_crypto
{
    struct rt_hwcrypto_device parent;
    struct rt_virtio_device *vdev;

    rt_uint32_t status;
    rt_uint32_t services;
    rt_uint32_t max_data_queues;
    rt_uint64_t max_req_size;
    rt_uint64_t max_cipher_key_len;
    rt_uint64_t max_auth_key_len;

    struct rt_virtqueue **vqs;
    struct rt_virtqueue *ctrl_vq;
    struct rt_completion *data_done;
    struct rt_completion ctrl_done;
    struct rt_spinlock *data_lock;
    struct rt_spinlock ctrl_lock;
};

#define raw_to_virtio_crypto(raw) rt_container_of((raw)->parent.device, struct virtio_crypto, parent)

rt_inline struct rt_virtqueue *virtio_crypto_data_vq(struct virtio_crypto *vcrypto)
{
    return vcrypto->vqs[rt_hw_cpu_id() % vcrypto->max_data_queues];
}

static rt_err_t virtio_crypto_symmetric_create_session(
        struct hwcrypto_symmetric *symmetric_ctx, rt_bool_t encrypt)
{
    rt_ubase_t level;
    struct rt_virtqueue *ctrl_vq, *data_vq;
    struct virtio_crypto_op_ctrl_req ctrl;
    struct virtio_crypto_session_input input;
    struct virtio_crypto_sym_create_session_req *sym_create_session;
    struct virtio_crypto *vcrypto = raw_to_virtio_crypto(symmetric_ctx);
    struct virtio_crypto_symmetric_contex *vctx = symmetric_ctx->parent.contex;

    ctrl_vq = vcrypto->ctrl_vq;
    data_vq = virtio_crypto_data_vq(vcrypto);

    /* Pad ctrl header */
    ctrl.header.opcode = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_CREATE_SESSION);
    switch (symmetric_ctx->parent.type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
        switch (symmetric_ctx->parent.type)
        {
        case HWCRYPTO_TYPE_AES_ECB:
            ctrl.header.algo = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_AES_ECB);
            break;

        case HWCRYPTO_TYPE_AES_CBC:
            ctrl.header.algo = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_AES_CBC);
            break;

        case HWCRYPTO_TYPE_AES_CTR:
            ctrl.header.algo = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_AES_CTR);
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    case HWCRYPTO_TYPE_DES:
        switch (symmetric_ctx->parent.type)
        {
        case HWCRYPTO_TYPE_DES_ECB:
            ctrl.header.algo = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_DES_ECB);
            break;

        case HWCRYPTO_TYPE_DES_CBC:
            ctrl.header.algo = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_DES_CBC);
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    case HWCRYPTO_TYPE_3DES:
        switch (symmetric_ctx->parent.type)
        {
        case HWCRYPTO_TYPE_3DES_ECB:
            ctrl.header.algo = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_3DES_ECB);
            break;

        case HWCRYPTO_TYPE_3DES_CBC:
            ctrl.header.algo = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_3DES_CBC);
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    case HWCRYPTO_TYPE_RC4:
        ctrl.header.algo = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_ARC4);
        break;
    }
    ctrl.header.queue_id = data_vq->index;

    input.status = rt_cpu_to_le32(VIRTIO_CRYPTO_ERR);

    /* Pad cipher's parameters */
    sym_create_session = &ctrl.sym_create_session;
    sym_create_session->op_type = rt_cpu_to_le32(VIRTIO_CRYPTO_SYM_OP_CIPHER);
    sym_create_session->cipher.para.algo = ctrl.header.algo;
    sym_create_session->cipher.para.keylen = rt_cpu_to_le32(symmetric_ctx->key_bitlen / 8);
    sym_create_session->cipher.para.op = rt_cpu_to_le32(encrypt ?
            VIRTIO_CRYPTO_OP_ENCRYPT : VIRTIO_CRYPTO_OP_DECRYPT);

    rt_virtqueue_wait_prepare(ctrl_vq, 3);

    level = rt_spin_lock_irqsave(&vcrypto->ctrl_lock);

    rt_virtqueue_add_outbuf(ctrl_vq, &ctrl, sizeof(ctrl));
    rt_virtqueue_add_outbuf(ctrl_vq, symmetric_ctx->key, symmetric_ctx->key_bitlen / 8);
    rt_virtqueue_add_inbuf(ctrl_vq, &input, sizeof(input));

    rt_virtqueue_kick(ctrl_vq);

    rt_spin_unlock_irqrestore(&vcrypto->ctrl_lock, level);

    rt_completion_wait(&vcrypto->ctrl_done, RT_WAITING_FOREVER);

    switch (input.status)
    {
    case VIRTIO_CRYPTO_OK:
        break;

    case VIRTIO_CRYPTO_INVSESS:
        RT_ASSERT(0);
    case VIRTIO_CRYPTO_ERR:
    case VIRTIO_CRYPTO_KEY_REJECTED:
        return -RT_ERROR;

    case VIRTIO_CRYPTO_BADMSG:
        return -RT_EINVAL;

    case VIRTIO_CRYPTO_NOTSUPP:
        return -RT_ENOSYS;

    case VIRTIO_CRYPTO_NOSPC:
        return -RT_EEMPTY;
    }

    vctx->session_id = input.session_id;
    vctx->data_vq = data_vq;

    return RT_EOK;
}

static void virtio_crypto_symmetric_destroy_session(
        struct hwcrypto_symmetric *symmetric_ctx)
{
    rt_ubase_t level;
    struct rt_virtqueue *ctrl_vq;
    struct virtio_crypto_inhdr inhdr;
    struct virtio_crypto_op_ctrl_req ctrl;
    struct virtio_crypto_destroy_session_req *destroy_session;
    struct virtio_crypto *vcrypto = raw_to_virtio_crypto(symmetric_ctx);
    struct virtio_crypto_symmetric_contex *vctx = symmetric_ctx->parent.contex;

    ctrl_vq = vcrypto->ctrl_vq;
    inhdr.status = VIRTIO_CRYPTO_ERR;

    /* Pad ctrl header */
    ctrl.header.opcode = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_DESTROY_SESSION);
    ctrl.header.queue_id = vctx->data_vq->index;

    destroy_session = &ctrl.destroy_session;
    destroy_session->session_id = rt_cpu_to_le64(vctx->session_id);

    rt_virtqueue_wait_prepare(ctrl_vq, 2);

    level = rt_spin_lock_irqsave(&vcrypto->ctrl_lock);

    rt_virtqueue_add_outbuf(ctrl_vq, &ctrl, sizeof(ctrl));
    rt_virtqueue_add_inbuf(ctrl_vq, &inhdr.status, sizeof(inhdr.status));

    rt_virtqueue_kick(ctrl_vq);

    rt_spin_unlock_irqrestore(&vcrypto->ctrl_lock, level);

    rt_completion_wait(&vcrypto->ctrl_done, RT_WAITING_FOREVER);

    if (inhdr.status != VIRTIO_CRYPTO_OK)
    {
        LOG_E("%s fail status = %d", __func__, inhdr.status);
    }
}

static rt_err_t virtio_crypto_symmetric_crypt(
        struct hwcrypto_symmetric *symmetric_ctx,
        struct hwcrypto_symmetric_info *symmetric_info)
{
    rt_err_t err;
    rt_ubase_t level;
    struct rt_virtqueue *data_vq;
    struct virtio_crypto_inhdr inhdr;
    struct virtio_crypto_op_data_req data;
    struct virtio_crypto *vcrypto = raw_to_virtio_crypto(symmetric_ctx);
    struct virtio_crypto_symmetric_contex *vctx = symmetric_ctx->parent.contex;

    if (!(vcrypto->status & VIRTIO_CRYPTO_S_HW_READY))
    {
        LOG_D("%s: to %s %s is not ready",
                rt_dm_dev_get_name(&vcrypto->parent.parent), "symmetric", "crypt");

        return -RT_EIO;
    }

    if (symmetric_info->mode == HWCRYPTO_MODE_ENCRYPT)
    {
        err = virtio_crypto_symmetric_create_session(symmetric_ctx, RT_TRUE);
    }
    else if (symmetric_info->mode == HWCRYPTO_MODE_DECRYPT)
    {
        err = virtio_crypto_symmetric_create_session(symmetric_ctx, RT_FALSE);
    }
    else
    {
        err = -RT_ENOSYS;
    }

    if (err)
    {
        return err;
    }

    vctx = symmetric_ctx->parent.contex;
    data_vq = vctx->data_vq;

    data.header.session_id = rt_cpu_to_le64(vctx->session_id);
    if (symmetric_info->mode == HWCRYPTO_MODE_ENCRYPT)
    {
        data.header.opcode = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_ENCRYPT);
    }
    else if (symmetric_info->mode == HWCRYPTO_MODE_DECRYPT)
    {
        data.header.opcode = rt_cpu_to_le32(VIRTIO_CRYPTO_CIPHER_DECRYPT);
    }

    if (!symmetric_ctx->iv_len)
    {
        symmetric_ctx->iv_len = sizeof(symmetric_ctx->iv);
        rt_memset(symmetric_ctx->iv, 0, symmetric_ctx->iv_len);
    }

    data.sym_req.op_type = rt_cpu_to_le32(VIRTIO_CRYPTO_SYM_OP_CIPHER);
    data.sym_req.cipher.para.iv_len = rt_cpu_to_le32(symmetric_ctx->iv_len);
    data.sym_req.cipher.para.src_data_len = rt_cpu_to_le32(symmetric_info->length);
    data.sym_req.cipher.para.dst_data_len = rt_cpu_to_le32(symmetric_info->length);

    inhdr.status = VIRTIO_CRYPTO_ERR;

    rt_virtqueue_wait_prepare(data_vq, 5);

    level = rt_spin_lock_irqsave(&vcrypto->data_lock[data_vq->index]);

    /* Outhdr */
    rt_virtqueue_add_outbuf(data_vq, &data, sizeof(data));

    rt_virtqueue_add_outbuf(data_vq,
                &symmetric_ctx->iv[symmetric_ctx->iv_off], symmetric_ctx->iv_len);

    /* Source data */
    rt_virtqueue_add_outbuf(data_vq, (void *)symmetric_info->in, symmetric_info->length);

    /* Destination data */
    rt_virtqueue_add_inbuf(data_vq, symmetric_info->out, symmetric_info->length);

    rt_virtqueue_add_inbuf(data_vq, &inhdr.status, sizeof(inhdr.status));

    rt_virtqueue_kick(data_vq);

    rt_spin_unlock_irqrestore(&vcrypto->data_lock[data_vq->index], level);

    rt_completion_wait(&vcrypto->data_done[data_vq->index], RT_WAITING_FOREVER);

    switch (inhdr.status)
    {
    case VIRTIO_CRYPTO_OK:
        err = RT_EOK;
        break;

    case VIRTIO_CRYPTO_INVSESS:
        err = -RT_EINVAL;
        break;

    case VIRTIO_CRYPTO_ERR:
    case VIRTIO_CRYPTO_KEY_REJECTED:
        err = -RT_ERROR;
        break;

    case VIRTIO_CRYPTO_BADMSG:
        err = -RT_EINVAL;
        break;

    case VIRTIO_CRYPTO_NOTSUPP:
        err = -RT_ENOSYS;
        break;

    case VIRTIO_CRYPTO_NOSPC:
        err = -RT_EEMPTY;
        break;
    }

    virtio_crypto_symmetric_destroy_session(symmetric_ctx);

    return err;
}

static const struct hwcrypto_symmetric_ops virtio_crypto_symmetric_ops =
{
    .crypt = virtio_crypto_symmetric_crypt,
};

static rt_err_t virtio_crypto_create(struct rt_hwcrypto_ctx *ctx)
{
    struct hwcrypto_symmetric *crypto_symmetric;

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
        ctx->contex = rt_calloc(1, sizeof(struct virtio_crypto_symmetric_contex));

        if (!ctx->contex)
        {
            return -RT_ENOMEM;
        }

        crypto_symmetric = rt_container_of(ctx, struct hwcrypto_symmetric, parent);
        crypto_symmetric->ops = &virtio_crypto_symmetric_ops;
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static void virtio_crypto_destroy(struct rt_hwcrypto_ctx *ctx)
{
    if (!ctx->contex)
    {
        return;
    }

    switch (ctx->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
        rt_free(ctx->contex);
        break;
    }
}

static rt_err_t virtio_crypto_copy(struct rt_hwcrypto_ctx *des,
        const struct rt_hwcrypto_ctx *src)
{
    rt_err_t err = RT_EOK;

    switch (src->type & HWCRYPTO_MAIN_TYPE_MASK)
    {
    case HWCRYPTO_TYPE_AES:
    case HWCRYPTO_TYPE_DES:
    case HWCRYPTO_TYPE_3DES:
    case HWCRYPTO_TYPE_RC4:
        break;

    default:
        err = -RT_ENOSYS;
        break;
    }

    return err;
}

static void virtio_crypto_reset(struct rt_hwcrypto_ctx *ctx)
{
}

static const struct rt_hwcrypto_ops virtio_crypto_ops =
{
    .create = virtio_crypto_create,
    .destroy = virtio_crypto_destroy,
    .copy = virtio_crypto_copy,
    .reset = virtio_crypto_reset,
};

static void virtio_crypto_data_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_crypto *vcrypto = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&vcrypto->data_lock[vq->index]);

    rt_virtqueue_read_buf(vq, RT_NULL);
    rt_completion_done(&vcrypto->data_done[vq->index]);

    rt_spin_unlock_irqrestore(&vcrypto->data_lock[vq->index], level);
}

static void virtio_crypto_ctrl_done(struct rt_virtqueue *vq)
{
    rt_ubase_t level;
    struct virtio_crypto *vcrypto = vq->vdev->priv;

    level = rt_spin_lock_irqsave(&vcrypto->ctrl_lock);

    rt_virtqueue_read_buf(vq, RT_NULL);
    rt_completion_done(&vcrypto->ctrl_done);

    rt_spin_unlock_irqrestore(&vcrypto->ctrl_lock, level);
}

static void virtio_crypto_config_changed(struct rt_virtio_device *vdev)
{
    rt_uint32_t status;
    struct virtio_crypto *vcrypto = vdev->parent.user_data;

    rt_virtio_read_config(vdev, struct virtio_crypto_config, status, &status);

    if (status & (~VIRTIO_CRYPTO_S_HW_READY))
    {
        LOG_E("%s: Unknown status bits = 0x%x",
                rt_dm_dev_get_name(&vdev->parent), status);

        RT_ASSERT(0);
        return;
    }

    if (vcrypto->status != status)
    {
        /* Change status */
        vcrypto->status = status;
    }
}

static rt_err_t virtio_crypto_vq_init(struct virtio_crypto *vcrypto)
{
    rt_err_t err;
    rt_size_t vqs_nr;
    const char **names = RT_NULL;
    rt_virtqueue_callback *cbs = RT_NULL;

    vqs_nr = vcrypto->max_data_queues + 1;

    vcrypto->vqs = rt_calloc(vqs_nr, sizeof(*vcrypto->vqs));

    if (!vcrypto->vqs)
    {
        return -RT_ENOMEM;
    }

    if (!(names = rt_malloc(sizeof(*names) * vqs_nr)))
    {
        return -RT_ENOMEM;
    }

    if (!(cbs = rt_malloc(sizeof(*cbs) * vqs_nr)))
    {
        err = -RT_ENOMEM;
        goto _out_free;
    }

    vcrypto->data_lock = rt_malloc(sizeof(vcrypto->data_lock[0]) *
            vcrypto->max_data_queues);

    if (!vcrypto->data_lock)
    {
        err = -RT_ENOMEM;
        goto _out_free;
    }

    vcrypto->data_done = rt_malloc(sizeof(vcrypto->data_done[0]) *
            vcrypto->max_data_queues);

    if (!vcrypto->data_done)
    {
        err = -RT_ENOMEM;
        goto _out_free;
    }

    for (int i = 0; i < vcrypto->max_data_queues; ++i)
    {
        names[i] = "data";
        cbs[i] = &virtio_crypto_data_done;

        rt_spin_lock_init(&vcrypto->data_lock[i]);
        rt_completion_init(&vcrypto->data_done[i]);
    }

    names[vqs_nr - 1] = "ctrl";
    cbs[vqs_nr - 1] = &virtio_crypto_ctrl_done;

    if ((err = rt_virtio_virtqueue_install(vcrypto->vdev, vqs_nr,
            vcrypto->vqs, names, cbs)))
    {
        goto _out_free;
    }

    vcrypto->ctrl_vq = vcrypto->vqs[vcrypto->max_data_queues];

_out_free:
    if (names)
    {
        rt_free(names);
    }
    if (cbs)
    {
        rt_free(cbs);
    }

    return err;
}

static void virtio_crypto_vq_finit(struct virtio_crypto *vcrypto)
{
    if (vcrypto->vqs)
    {
        if (vcrypto->vqs[0])
        {
            rt_virtio_virtqueue_release(vcrypto->vdev);
        }

        rt_free(vcrypto->vqs);
    }

    if (vcrypto->data_lock)
    {
        rt_free(vcrypto->data_lock);
    }

    if (vcrypto->data_done)
    {
        rt_free(vcrypto->data_done);
    }
}

static rt_err_t virtio_crypto_probe(struct rt_virtio_device *vdev)
{
    rt_err_t err;
    struct virtio_crypto *vcrypto = rt_calloc(1, sizeof(*vcrypto));

    if (!vcrypto)
    {
        return -RT_ENOMEM;
    }

    vdev->priv = vcrypto;
    vcrypto->vdev = vdev;
    vdev->parent.user_data = vcrypto;

    rt_virtio_read_config(vdev, struct virtio_crypto_config, max_dataqueues,
            &vcrypto->max_data_queues);

    if (vcrypto->max_data_queues > RT_CPUS_NR)
    {
        vcrypto->max_data_queues = RT_CPUS_NR;
    }
    else
    {
        vcrypto->max_data_queues = 1;
    }

    rt_virtio_read_config(vdev, struct virtio_crypto_config, crypto_services,
            &vcrypto->services);
    rt_virtio_read_config(vdev, struct virtio_crypto_config, max_size,
            &vcrypto->max_req_size);
    rt_virtio_read_config(vdev, struct virtio_crypto_config, max_cipher_key_len,
            &vcrypto->max_cipher_key_len);
    rt_virtio_read_config(vdev, struct virtio_crypto_config, max_auth_key_len,
            &vcrypto->max_auth_key_len);

    if ((err = virtio_crypto_vq_init(vcrypto)))
    {
        goto _fail;
    }

    rt_spin_lock_init(&vcrypto->ctrl_lock);
    rt_completion_init(&vcrypto->ctrl_done);

    vcrypto->parent.ops = &virtio_crypto_ops;
    vcrypto->parent.id = ((rt_uint64_t)vdev->id.vendor << 32) | vdev->id.device;

    virtio_crypto_config_changed(vdev);

    if ((err = rt_hwcrypto_register(&vcrypto->parent, RT_HWCRYPTO_DEFAULT_NAME)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    virtio_crypto_vq_finit(vcrypto);
    rt_free(vcrypto);

    return err;
}

static rt_err_t virtio_crypto_remove(struct rt_virtio_device *vdev)
{
    struct virtio_crypto *vcrypto = vdev->parent.user_data;

    rt_device_unregister(&vcrypto->parent.parent);

    virtio_crypto_vq_finit(vcrypto);
    rt_free(vcrypto);

    return RT_EOK;
}

static const struct rt_virtio_device_id virtio_crypto_ids[] =
{
    { VIRTIO_DEVICE_ID_CRYPTO, VIRTIO_DEVICE_ANY_ID },
    { /* sentinel */ }
};

static struct rt_virtio_driver virtio_crypto_driver =
{
    .ids = virtio_crypto_ids,
    .features =
        RT_BIT(VIRTIO_F_ANY_LAYOUT),

    .probe = virtio_crypto_probe,
    .remove = virtio_crypto_remove,
    .config_changed = virtio_crypto_config_changed,
};
RT_VIRTIO_DRIVER_EXPORT(virtio_crypto_driver);
