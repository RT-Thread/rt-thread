/*
 * @brief DMA controller ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "hw_dmaaltd.h"

const ROM_DMAALTD_API_T  dmaalt_api = {
	&dmaalt_get_mem_size,
	&dmaalt_init,
	&dmaalt_setup_channel,
	&dmaalt_init_queue,
	&dmaalt_register_queue_callback,
	&dmaalt_build_descriptor_chain,
	&dmaalt_get_transfer_count,
	&dmaalt_unstall_descriptor_chain,
	&dmaalt_queue_descriptor,
	&dmaalt_get_queue_pop_descriptor_status,
	&dmaalt_unqueue_descriptor,
	&dmaalt_start_queue,
	&dmaalt_stop_queue,
	&dmaalt_flush_queue,
	&dmaalt_get_queue_state,
	&dmaalt_force_trigger,
	&dmaalt_handler,
	&dmaalt_get_driver_version
};		// end of table ************************************
