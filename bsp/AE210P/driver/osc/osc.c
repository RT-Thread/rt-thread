#include "hal.h"
#include "uart/uart.h"
#include "osc.h"
#include "os_except.h"

#define osc_hisr_TASK_PRIORITY 31	// osc_hisr must be the highest priority task of all tasks.

/*
 *********************************************************************************************************
 *                                      Overlay SRAM Controller (OSC) initialize
 *
 * Description : This function is called to initialize overlay SRAM controller,
 *               including setting upfixed region size and overlay region base.
 *
 * Arguments   :
 *
 * Notes       :
 *********************************************************************************************************
 */
void _osc_init(void)
{
	register unsigned int ovly_region_szie;
	register unsigned int fix_regiion_size;
	register unsigned int ovly_region_base_addr;

	/* Read the initial OSC overlay region size. */
	ovly_region_szie = (REG32(OSC_CTRL) & OSC_CTRL_OVL_SZ_MASK) >> 12;

	/* Initialize OSC fix region size */
	fix_regiion_size = OSC_EILM_SIZE - ovly_region_szie;
	REG32(OSC_OVLFS) = fix_regiion_size;

	/* Initialize OSC overlay region to the end of all overlay text. */
	ovly_region_base_addr = fix_regiion_size + ovly_region_szie * _novlys;
	REG32(OSC_OVLBASE) = ovly_region_base_addr;
}

int _osc_drv_init(void (*handler)(unsigned int ipc),
                   void (*osc_hisr)(void *arg),
                   OSC_DRV_INFO *osc_info)
{
	hal_queue_t     *queue = &osc_info->queue;
	hal_thread_t    *th    = &osc_info->th;

	// Initial the Fixed/Overlap regions.
	_osc_init();

	// Register a user-define handler which is called from OSC exception handler.
	register_exception_handler(GE_RESERVED_INST, handler);

	// Register a user-define hisr which will be woken up by lisr sending msg to queue.
	th->fn             = osc_hisr;
        th->name           = "bh_osc";
        th->stack_size     = 0x400;
        th->arg            = queue;
        th->prio           = osc_hisr_TASK_PRIORITY;
        th->task           = NULL;
        th->ptos           = NULL;

	// Create a bottom half.
	// The bottom half is a thread task with a sync queue.
	queue->size = 1;

        if(hal_create_queue(queue) == HAL_FAILURE)
                return HAL_FAILURE;

	if(hal_create_thread(th) != HAL_SUCCESS)
		return HAL_FAILURE;

	puts("OSC driver init success!\n");

	return HAL_SUCCESS;
}

