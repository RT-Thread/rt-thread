/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DMAMUX_H
#define HPM_DMAMUX_H

typedef struct {
    __W  uint32_t MUXCFG[32];                  /* 0x0 - 0x7C: HDMA MUX0 Configuration */
} DMAMUX_Type;


/* Bitfield definition for register array: MUXCFG */
/*
 * ENABLE (WO)
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
 * SOURCE (WO)
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
#define DMAMUX_MUXCFG_HDMA_MUX8 (8UL)
#define DMAMUX_MUXCFG_HDMA_MUX9 (9UL)
#define DMAMUX_MUXCFG_HDMA_MUX10 (10UL)
#define DMAMUX_MUXCFG_HDMA_MUX11 (11UL)
#define DMAMUX_MUXCFG_HDMA_MUX12 (12UL)
#define DMAMUX_MUXCFG_HDMA_MUX13 (13UL)
#define DMAMUX_MUXCFG_HDMA_MUX14 (14UL)
#define DMAMUX_MUXCFG_HDMA_MUX15 (15UL)
#define DMAMUX_MUXCFG_HDMA_MUX16 (16UL)
#define DMAMUX_MUXCFG_HDMA_MUX17 (17UL)
#define DMAMUX_MUXCFG_HDMA_MUX18 (18UL)
#define DMAMUX_MUXCFG_HDMA_MUX19 (19UL)
#define DMAMUX_MUXCFG_HDMA_MUX20 (20UL)
#define DMAMUX_MUXCFG_HDMA_MUX21 (21UL)
#define DMAMUX_MUXCFG_HDMA_MUX22 (22UL)
#define DMAMUX_MUXCFG_HDMA_MUX23 (23UL)
#define DMAMUX_MUXCFG_HDMA_MUX24 (24UL)
#define DMAMUX_MUXCFG_HDMA_MUX25 (25UL)
#define DMAMUX_MUXCFG_HDMA_MUX26 (26UL)
#define DMAMUX_MUXCFG_HDMA_MUX27 (27UL)
#define DMAMUX_MUXCFG_HDMA_MUX28 (28UL)
#define DMAMUX_MUXCFG_HDMA_MUX29 (29UL)
#define DMAMUX_MUXCFG_HDMA_MUX30 (30UL)
#define DMAMUX_MUXCFG_HDMA_MUX31 (31UL)


#endif /* HPM_DMAMUX_H */
