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
 * FilePath: platform_info.h
 * Created Date: 2024-04-28 17:13:17
 * Last Modified: 2024-06-26 14:47:43
 * Description:  This file is for
 * 
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 */
#ifndef PLATFORM_INFO_H_
#define PLATFORM_INFO_H_

/***************************** Include Files *********************************/
#include <openamp/remoteproc.h>
#include <openamp/virtio.h>
#include <openamp/rpmsg.h>
#include <openamp/rpmsg_virtio.h>
#include "sdkconfig.h"
#include "ftypes.h"
#include "platform_info_common.h"

/************************** Constant Definitions *****************************/

/************************** Variable Definitions *****************************/

#if defined __cplusplus
extern "C" {
#endif

/***************** Macros (Inline Functions) Definitions *********************/
/* 需要宇linux 进行沟通 */
#define POLL_STOP 				0x1U
#define REMOTE_PROC_STOP      	0x0001U
/**************************** Type Definitions *******************************/

struct remoteproc_priv {
	const char *kick_dev_name;
	const char *kick_dev_bus_name;
	struct metal_device *kick_dev;
	struct metal_io_region *kick_io;
#ifdef CONFIG_USE_OPENAMP_IPI
	atomic_int ipi_nokick;
#endif /* !RPMSG_NO_IPI */
	unsigned int cpu_id ;
	/* remoteproc elf address */
	metal_phys_addr_t elf_addr;
	unsigned int src_table_ready_flag ;
	/* src_table memory */
	u32 src_table_attribute ;
	/* share_mem_size = |tx vring|rx vring|share buffer| */
	metal_phys_addr_t share_mem_va ;
	metal_phys_addr_t share_mem_pa ;
	u32	share_mem_size ;
	u32 share_buffer_offset ;
	u32 share_mem_attribute ;
	struct rpmsg_virtio_shm_pool shpool;
};

/************************** Function Prototypes ******************************/

struct remoteproc *platform_create_proc(struct remoteproc * rproc_inst,struct remoteproc_priv *priv ,struct metal_device *kick_dev) ;

int platform_setup_src_table(struct remoteproc *rproc_inst,metal_phys_addr_t *rsc_table) ;

int platform_setup_share_mems(struct remoteproc *rproc_inst);

int platform_poll_nonblocking(void *priv) ;

#ifdef  CONFIG_USE_OPENAMP_IPI
unsigned int rproc_check_rsc_table_stop(struct remoteproc *rproc);
#endif

unsigned int rproc_get_stop_flag(void);

void rproc_set_stop_flag(void);

void rproc_clear_stop_flag(void);

#if defined __cplusplus
}
#endif


#endif
