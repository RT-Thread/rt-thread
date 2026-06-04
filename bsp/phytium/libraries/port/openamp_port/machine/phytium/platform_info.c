/*
 * Copyright (C) 2024, Phytium Technology Co., Ltd.   All Rights Reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * 
 * FilePath: platform_info.c
 * Created Date: 2024-04-28 17:13:10
 * Last Modified: 2025-02-28 09:57:15
 * Description:  This file is for
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 */


#include "platform_info.h"
#include "ftypes.h"
#include <openamp/rpmsg_virtio.h>
#include <metal/device.h>
#include <metal/irq.h>
#include <errno.h>
#include "platform_info.h"
#include "remoteproc.h"
#include "rsc_table.h"
#include "sdkconfig.h"
#include "fdebug.h"
#include "helper.h"

#define     FT_PLAT_INFO_MAIN_DEBUG_TAG "FT_PLAT_INFO_MAIN"
#define     FT_PLAT_INFO_MAIN_DEBUG_I(format, ...) FT_DEBUG_PRINT_I( FT_PLAT_INFO_MAIN_DEBUG_TAG, format, ##__VA_ARGS__)
#define     FT_PLAT_INFO_MAIN_DEBUG_W(format, ...) FT_DEBUG_PRINT_W( FT_PLAT_INFO_MAIN_DEBUG_TAG, format, ##__VA_ARGS__)
#define     FT_PLAT_INFO_MAIN_DEBUG_E(format, ...) FT_DEBUG_PRINT_E( FT_PLAT_INFO_MAIN_DEBUG_TAG, format, ##__VA_ARGS__)

#ifdef CONFIG_USE_OPENAMP_IPI
#define _rproc_wait() asm volatile("wfi")
#endif /* !RPMSG_NO_IPI */

/************************** Variable Definitions *****************************/
static volatile unsigned int stop_flag = 0;
extern struct remoteproc_ops phytium_proc_ops ;

#ifdef CONFIG_USE_MASTER_VRING_DEFINE
static metal_phys_addr_t linux_share_buffer;
#endif
/************************** Function Prototypes ******************************/
#ifdef  CONFIG_USE_OPENAMP_IPI
unsigned int rproc_check_rsc_table_stop(struct remoteproc *rproc)
{
    if (!rproc) {
        FT_PLAT_INFO_MAIN_DEBUG_E("rproc NULL! \r\n");
        return 0;
    }
    struct remote_resource_table *table_ptr = rproc->rsc_table;
    unsigned int *flag = table_ptr->reserved;

    if (*flag & REMOTE_PROC_STOP) {
        return 1;
    } else {
        return 0;
    }
}
#endif

unsigned int rproc_get_stop_flag(void)
{
    return stop_flag;
}

void rproc_set_stop_flag(void)
{
    stop_flag |= REMOTE_PROC_STOP;
}

void rproc_clear_stop_flag(void)
{
    stop_flag &= ~REMOTE_PROC_STOP;
}

struct remoteproc *platform_create_proc(struct remoteproc * rproc_inst,struct remoteproc_priv *priv ,struct metal_device *kick_dev)
{
	struct remoteproc * rproc;

	if (metal_register_generic_device(kick_dev))
    {
        return NULL;
    }

	/* Initialize remoteproc instance */
	/* metal_device_open(KICK_BUS_NAME,KICK_DEV_NAME,rproc_inst->priv->kick_dev) */
	/* rproc_inst->priv->kick_io = metal_device_io_region(rproc_inst->priv->kick_dev, 0); */
    rproc = remoteproc_init(rproc_inst, &phytium_proc_ops, priv) ;
    
    return rproc;
}


int platform_setup_src_table(struct remoteproc *rproc_inst,metal_phys_addr_t *rsc_table)
{
    metal_phys_addr_t pa;
	struct remoteproc_priv *priv = rproc_inst->priv;
    int ret;
	// metal_phys_addr_t *rsc_table = priv->src_table_va ;
	size_t rsc_size = sizeof(struct remote_resource_table) ;
	unsigned int attribute = priv->src_table_attribute ;	

    pa = (metal_phys_addr_t)rsc_table;
	/* rproc_inst.mems  rproc_inst.rsc_io*/
	/* 在OpenAMP应用中，通常需要通过remoteproc_mmap()函数将远程处理器中的共享内存映射到本地主机中，以便应用程序进行读写操作。*/
	(void *)remoteproc_mmap(rproc_inst, &pa, NULL, rsc_size, attribute, &rproc_inst->rsc_io);

    ret = remoteproc_set_rsc_table(rproc_inst, (struct resource_table *)rsc_table, rsc_size);
	if (ret)
    {
		FT_PLAT_INFO_MAIN_DEBUG_E("Failed to intialize remoteproc %d \r\n",ret);
		remoteproc_remove(rproc_inst);
		return -1;
	}
	priv->src_table_ready_flag = 1;/* 标记src_table已经准备好了 */
    return 0 ;
}


int platform_setup_share_mems(struct remoteproc *rproc_inst)
{
	int ret;
	struct remoteproc_priv *priv = rproc_inst->priv;
#ifdef CONFIG_USE_MASTER_VRING_DEFINE /*获取资源表中的共享内存地址*/
	struct remote_resource_table *table_ptr = rproc_inst->rsc_table;
	FT_PLAT_INFO_MAIN_DEBUG_I("da is %p ~ %p \r\n",table_ptr->rpmsg_vdev.vring[0].da,table_ptr->rpmsg_vdev.vring[0].da + priv->share_mem_size);
	priv->share_mem_pa = table_ptr->rpmsg_vdev.vring[0].da;/* 默认kernel vring[0].da 的首地址是整个sharememory的起始位置*/
	priv->share_mem_va = priv->share_mem_pa;
#endif
	(void *)remoteproc_mmap(rproc_inst, &priv->share_mem_pa, &priv->share_mem_va, priv->share_mem_size, priv->share_mem_attribute, NULL);
    return 0 ;
}

struct rpmsg_device *platform_create_rpmsg_vdev(void *platform, unsigned int vdev_index, unsigned int role,
												void (*rst_cb)(struct virtio_device *vdev), rpmsg_ns_bind_cb ns_bind_cb)
{
	struct remoteproc *rproc = platform;
	struct rpmsg_virtio_device *rpmsg_vdev;
	struct virtio_device *vdev;
	void *shbuf;
	struct metal_io_region *shbuf_io;
    struct remoteproc_priv *priv = rproc->priv;
	int ret;

	rpmsg_vdev = metal_allocate_memory(sizeof(*rpmsg_vdev));
	if (!rpmsg_vdev)
		return NULL;

	shbuf_io = remoteproc_get_io_with_pa(rproc, priv->share_mem_pa);
	if (!shbuf_io)
		goto err1;
	FT_PLAT_INFO_MAIN_DEBUG_I("share_mem_pa is %p \r\n",priv->share_mem_pa);
	shbuf = metal_io_phys_to_virt(shbuf_io, priv->share_mem_pa + priv->share_buffer_offset);
	/* TODO: can we have a wrapper for the following two functions? */
	vdev = remoteproc_create_virtio(rproc, vdev_index, role, rst_cb);
	if (!vdev) {
		FT_PLAT_INFO_MAIN_DEBUG_E("failed remoteproc_create_virtio\r\n");
		goto err1;
	}

	/* Only RPMsg virtio master needs to initialize the shared buffers pool */
	rpmsg_virtio_init_shm_pool(&priv->shpool, shbuf, priv->share_mem_size - priv->share_buffer_offset);

	/* RPMsg virtio slave can set shared buffers pool argument to NULL */
	ret = rpmsg_init_vdev(rpmsg_vdev, vdev, ns_bind_cb, shbuf_io, &priv->shpool);
	if (ret) {
		FT_PLAT_INFO_MAIN_DEBUG_E("failed rpmsg_init_vdev ret is %d \r\n",ret);
		goto err2;
	}
	FT_PLAT_INFO_MAIN_DEBUG_I("initializing rpmsg vdev\r\n");
	return rpmsg_virtio_get_rpmsg_device(rpmsg_vdev);

err2:
	remoteproc_remove_virtio(rproc, vdev);
err1:
	metal_free_memory(rpmsg_vdev);
	return NULL;
}

int platform_poll(void *priv)
{
	struct remoteproc *rproc = priv;
	struct remoteproc_priv *prproc;
	unsigned int flags;
	int ret;


	prproc = rproc->priv;
	while(1) {
#ifndef CONFIG_USE_OPENAMP_IPI
		if (metal_io_read32(prproc->kick_io, 0) & POLL_STOP) { //RPROC_M2S_SHIFT
			ret = remoteproc_get_notification(rproc, RSC_NOTIFY_ID_ANY);
			if (ret)
				return ret;
			break;
		}
		(void)flags;
#else /* !RPMSG_NO_IPI */
		flags = metal_irq_save_disable();
		if (!(atomic_flag_test_and_set(&prproc->ipi_nokick)))
		{
			metal_irq_restore_enable(flags);
			ret = remoteproc_get_notification(rproc, RSC_NOTIFY_ID_ANY);
			if (ret)
				return ret;
			break;
		}
		_rproc_wait() ;
		metal_irq_restore_enable(flags);
#endif /* RPMSG_NO_IPI */
	}
	return 0;
}

int platform_poll_nonblocking(void *priv)
{
	struct remoteproc *rproc = priv;
	struct remoteproc_priv *prproc;
	unsigned int flags;
	int ret;


	prproc = rproc->priv;

#ifndef CONFIG_USE_OPENAMP_IPI
		if (metal_io_read32(prproc->kick_io, 0) & POLL_STOP) { //RPROC_M2S_SHIFT
			ret = remoteproc_get_notification(rproc, RSC_NOTIFY_ID_ANY);
			if (ret)
				return ret;
		}
		(void)flags;
#else /* !RPMSG_NO_IPI */
		flags = metal_irq_save_disable();
		if (!(atomic_flag_test_and_set(&prproc->ipi_nokick)))
		{
			metal_irq_restore_enable(flags);
			ret = remoteproc_get_notification(rproc, RSC_NOTIFY_ID_ANY);
			if (ret)
				return ret;
		}
		metal_irq_restore_enable(flags);
#endif /* RPMSG_NO_IPI */
	return 0;
}

void platform_release_rpmsg_vdev(struct rpmsg_device *rpdev, void *platform)
{
	struct rpmsg_virtio_device *rpvdev;
	struct remoteproc *rproc;

	rpvdev = metal_container_of(rpdev, struct rpmsg_virtio_device, rdev);
	rproc = platform;

	rpmsg_deinit_vdev(rpvdev);
	remoteproc_remove_virtio(rproc, rpvdev->vdev);
}

void platform_cleanup(void *platform)
{
	struct remoteproc *rproc = platform;

	if (rproc)
		remoteproc_remove(rproc);
	cleanup_system();
}