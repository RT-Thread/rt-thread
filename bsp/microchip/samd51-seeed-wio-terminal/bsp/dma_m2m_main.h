/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file or main.c
 * to avoid loosing it when reconfiguring.
 */
#ifndef DMA_M2M_MAIN_H
#define DMA_M2M_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <dma_memory.h>

/**
 * \berif Example function for how to use \ref dma_memset and \ref dma_memcpy
 *        function.
 *
 * The system driver DMAC must be setup before using DMA M2M example function.
 * For ATSAMD51P19A, below configuratino must be set:
 * Enable 'DMAC', 'Channel' and associated 'Priority Level'.
 * Enable 'Source Address Increment' and 'Destination Address Increment' for
 * associate 'Channel'.
 */
void M2M_DMA_0_example(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DMA_M2M_MAIN_H */
