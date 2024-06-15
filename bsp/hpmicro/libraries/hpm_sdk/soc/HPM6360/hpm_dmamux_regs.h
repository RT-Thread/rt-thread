/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DMAMUX_H
#define HPM_DMAMUX_H

typedef struct {
    __RW uint32_t MUXCFG[16];                  /* 0x0 - 0x3C: HDMA MUX0 Configuration */
} DMAMUX_Type;


/* Bitfield definition for register array: MUXCFG */
/*
 * ENABLE (RW)
 *
 * DMA Mux Channel Enable
 * Enables the channel for DMA Mux. The DMA has separate channel enables/disables, which should be
 * used to disable or reconfigure a DMA channel.
 * 0b - DMA Mux channel is disabled
 * 1b - DMA Mux channel is enabled
 */
#define DMAMUX_MUXCFG_ENABLE_MASK (0x80000000UL)
#define DMAMUX_MUXCFG_ENABLE_SHIFT (31U)
#define DMAMUX_MUXCFG_ENABLE_SET(x) (((uint32_t)(x) << DMAMUX_MUXCFG_ENABLE_SHIFT) & DMAMUX_MUXCFG_ENABLE_MASK)
#define DMAMUX_MUXCFG_ENABLE_GET(x) (((uint32_t)(x) & DMAMUX_MUXCFG_ENABLE_MASK) >> DMAMUX_MUXCFG_ENABLE_SHIFT)

/*
 * SOURCE (RW)
 *
 * DMA Channel Source
 * Specifies which DMA source, if any, is routed to a particular DMA channel. See the "DMA MUX Mapping"
 */
#define DMAMUX_MUXCFG_SOURCE_MASK (0x7FU)
#define DMAMUX_MUXCFG_SOURCE_SHIFT (0U)
#define DMAMUX_MUXCFG_SOURCE_SET(x) (((uint32_t)(x) << DMAMUX_MUXCFG_SOURCE_SHIFT) & DMAMUX_MUXCFG_SOURCE_MASK)
#define DMAMUX_MUXCFG_SOURCE_GET(x) (((uint32_t)(x) & DMAMUX_MUXCFG_SOURCE_MASK) >> DMAMUX_MUXCFG_SOURCE_SHIFT)



/* MUXCFG register group index macro definition */
#define DMAMUX_MUXCFG_HDMA_MUX0 (0UL)
#define DMAMUX_MUXCFG_HDMA_MUX1 (1UL)
#define DMAMUX_MUXCFG_HDMA_MUX2 (2UL)
#define DMAMUX_MUXCFG_HDMA_MUX3 (3UL)
#define DMAMUX_MUXCFG_HDMA_MUX4 (4UL)
#define DMAMUX_MUXCFG_HDMA_MUX5 (5UL)
#define DMAMUX_MUXCFG_HDMA_MUX6 (6UL)
#define DMAMUX_MUXCFG_HDMA_MUX7 (7UL)
#define DMAMUX_MUXCFG_XDMA_MUX0 (8UL)
#define DMAMUX_MUXCFG_XDMA_MUX1 (9UL)
#define DMAMUX_MUXCFG_XDMA_MUX2 (10UL)
#define DMAMUX_MUXCFG_XDMA_MUX3 (11UL)
#define DMAMUX_MUXCFG_XDMA_MUX4 (12UL)
#define DMAMUX_MUXCFG_XDMA_MUX5 (13UL)
#define DMAMUX_MUXCFG_XDMA_MUX6 (14UL)
#define DMAMUX_MUXCFG_XDMA_MUX7 (15UL)


#endif /* HPM_DMAMUX_H */
