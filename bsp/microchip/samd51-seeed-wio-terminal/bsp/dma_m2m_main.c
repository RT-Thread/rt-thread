/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */

#include "atmel_start.h"

static volatile uint8_t dma_complete_flag;
static void             M2M_DMA_0_complete_cb(void)
{
	dma_complete_flag = 1;
}

void M2M_DMA_0_example(void)
{
	uint8_t  src_array[100];
	uint8_t  dst_array[100];
	uint32_t i;

	dma_memory_register_callback(DMA_MEMORY_COMPLETE_CB, M2M_DMA_0_complete_cb);
	for (i = 0; i < 100; i++) {
		src_array[i] = i;
		dst_array[i] = 0;
	}

	/* dma_memset example, set all array data to 0x01 */
	dma_complete_flag = 0;
	dma_memset(dst_array, 0x01, 100);
	while (dma_complete_flag == 0) {
	}

	/* Check if memory set success */
	for (i = 0; i < 100; i++) {
		if (dst_array[i] != 0x01) {
			while (1) {
			};
		}
	}

	/* dma_memcpy example */
	dma_complete_flag = 0;
	dma_memcpy(dst_array, src_array, 100);
	while (dma_complete_flag == 0) {
	}
	/* Check if dma_memcpy success */
	for (i = 0; i < 100; i++) {
		if (dst_array[i] != src_array[i]) {
			while (1) {
			};
		}
	}
}
