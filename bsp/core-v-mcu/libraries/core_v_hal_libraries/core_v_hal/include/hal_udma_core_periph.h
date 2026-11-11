/*
 * Copyright (C) 2019 ETH Zurich, University of Bologna
 * and GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HAL_INCLUDE_HAL_UDMA_CORE_PERIPH_H_
#define HAL_INCLUDE_HAL_UDMA_CORE_PERIPH_H_

#include <stdint.h>

/* ----------------------------------------------------------------------------
   -- UDMA_CORE Peripheral Access Layer --
   ---------------------------------------------------------------------------- */

/** UDMA_CORE_Type Register Layout Typedef */
/* TODO: refactor this really not good code */
typedef struct
{
	volatile uint32_t saddr; /**< RX/TX/CMD Channel uDMA transfer address of associated buffer */
	volatile uint32_t size; /**< RX/TX/CMD Channel uDMA transfer size of buffer */
	volatile uint32_t cfg; /**< RX/TX/CMD Channel uDMA transfer configuration */
	volatile uint32_t initcfg; /**< Not used. */
} udma_channel_t;


typedef enum
{
	RX_CHANNEL      = 0,
	TX_CHANNEL      = 1,
	COMMAND_CHANNEL = 2
} udma_channel_e;

/* ----------------------------------------------------------------------------
   -- UDMA_CORE Register Bitfield Access --
   ---------------------------------------------------------------------------- */

/*! @name RX_SADDR */
/* Configure pointer to memory buffer:
  - Read: value of the pointer until transfer is over. Else returns 0
  - Write: set Address Pointer to memory buffer start address */
#define UDMA_CORE_RX_SADDR_RX_SADDR_MASK                             (0x1fffff)
#define UDMA_CORE_RX_SADDR_RX_SADDR_SHIFT                            (0)
#define UDMA_CORE_RX_SADDR_RX_SADDR(val)                             (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_SADDR_RX_SADDR_SHIFT)) & UDMA_CORE_RX_SADDR_RX_SADDR_MASK)

/* Reserved/Not used. */
#define UDMA_CORE_RX_SADDR_RESERVED_0_MASK                           (0xffe00000)
#define UDMA_CORE_RX_SADDR_RESERVED_0_SHIFT                          (21)
#define UDMA_CORE_RX_SADDR_RESERVED_0(val)                           (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_SADDR_RESERVED_0_SHIFT)) & UDMA_CORE_RX_SADDR_RESERVED_0_MASK)


/*! @name RX_SIZE */
/* Buffer size in byte. (128kBytes maximum)
  - Read: buffer size left
  - Write: set buffer size */
#define UDMA_CORE_RX_SIZE_RX_SIZE_MASK                               (0xfffff)
#define UDMA_CORE_RX_SIZE_RX_SIZE_SHIFT                              (0)
#define UDMA_CORE_RX_SIZE_RX_SIZE(val)                               (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_SIZE_RX_SIZE_SHIFT)) & UDMA_CORE_RX_SIZE_RX_SIZE_MASK)

/* Reserved/Not used. */
#define UDMA_CORE_RX_SIZE_RESERVED_0_MASK                            (0xfff00000)
#define UDMA_CORE_RX_SIZE_RESERVED_0_SHIFT                           (20)
#define UDMA_CORE_RX_SIZE_RESERVED_0(val)                            (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_SIZE_RESERVED_0_SHIFT)) & UDMA_CORE_RX_SIZE_RESERVED_0_MASK)


/*! @name RX_CFG */
/* Channel continuous mode:
  - 1'b0: disable
  - 1'b1: enable
  At the end of the buffer the uDMA reloads the address and size and starts a new transfer. */
#define UDMA_CORE_RX_CFG_CONTINOUS_MASK                              (0x1)
#define UDMA_CORE_RX_CFG_CONTINOUS_SHIFT                             (0)
#define UDMA_CORE_RX_CFG_CONTINOUS(val)                              (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_CFG_CONTINOUS_SHIFT)) & UDMA_CORE_RX_CFG_CONTINOUS_MASK)

/* Channel transfer size used to increment uDMA buffer address pointer:
  - 2'b00: +1 (8 bits)
  - 2'b01: +2 (16 bits)
  - 2'b10: +4 (32 bits)
  - 2'b11: +0 */
#define UDMA_CORE_RX_CFG_DATASIZE_MASK                               (0x6)
#define UDMA_CORE_RX_CFG_DATASIZE_SHIFT                              (1)
#define UDMA_CORE_RX_CFG_DATASIZE(val)                               (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_CFG_DATASIZE_SHIFT)) & UDMA_CORE_RX_CFG_DATASIZE_MASK)

/* Reserved/Not used. */
#define UDMA_CORE_RX_CFG_RESERVED_0_MASK                             (0x8)
#define UDMA_CORE_RX_CFG_RESERVED_0_SHIFT                            (3)
#define UDMA_CORE_RX_CFG_RESERVED_0(val)                             (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_CFG_RESERVED_0_SHIFT)) & UDMA_CORE_RX_CFG_RESERVED_0_MASK)

/* Channel enable and start transfer:
  - 1'b0: disable
  - 1'b1: enable
  This signal is used also to queue a transfer if one is already ongoing. */
#define UDMA_CORE_RX_CFG_EN_MASK                                     (0x10)
#define UDMA_CORE_RX_CFG_EN_SHIFT                                    (4)
#define UDMA_CORE_RX_CFG_EN(val)                                     (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_CFG_EN_SHIFT)) & UDMA_CORE_RX_CFG_EN_MASK)

/* Transfer pending in queue status flag:
  - 1'b0: no pending transfer in the queue
  - 1'b1: pending transfer in the queue */
#define UDMA_CORE_RX_CFG_PENDING_MASK                                (0x20)
#define UDMA_CORE_RX_CFG_PENDING_SHIFT                               (5)
#define UDMA_CORE_RX_CFG_PENDING(val)                                (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_CFG_PENDING_SHIFT)) & UDMA_CORE_RX_CFG_PENDING_MASK)

/* Channel clear and stop transfer:
  - 1'b0: disable
  - 1'b1: stop and clear the on-going transfer */
#define UDMA_CORE_RX_CFG_CLR_MASK                                    (0x40)
#define UDMA_CORE_RX_CFG_CLR_SHIFT                                   (6)
#define UDMA_CORE_RX_CFG_CLR(val)                                    (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_CFG_CLR_SHIFT)) & UDMA_CORE_RX_CFG_CLR_MASK)

/* Reserved/Not used. */
#define UDMA_CORE_RX_CFG_RESERVED_1_MASK                             (0xffffff80)
#define UDMA_CORE_RX_CFG_RESERVED_1_SHIFT                            (7)
#define UDMA_CORE_RX_CFG_RESERVED_1(val)                             (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_CFG_RESERVED_1_SHIFT)) & UDMA_CORE_RX_CFG_RESERVED_1_MASK)


/*! @name RX_INITCFG */
/* Reserved/Not used. */
#define UDMA_CORE_RX_INITCFG_RESERVED_0_MASK                         (0xffffffff)
#define UDMA_CORE_RX_INITCFG_RESERVED_0_SHIFT                        (0)
#define UDMA_CORE_RX_INITCFG_RESERVED_0(val)                         (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_RX_INITCFG_RESERVED_0_SHIFT)) & UDMA_CORE_RX_INITCFG_RESERVED_0_MASK)


/*! @name TX_SADDR */
/* Configure pointer to memory buffer:
  - Read: value of the pointer until transfer is over. Else returns 0
  - Write: set Address Pointer to memory buffer start address */
#define UDMA_CORE_TX_SADDR_TX_SADDR_MASK                             (0x1fffff)
#define UDMA_CORE_TX_SADDR_TX_SADDR_SHIFT                            (0)
#define UDMA_CORE_TX_SADDR_TX_SADDR(val)                             (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_SADDR_TX_SADDR_SHIFT)) & UDMA_CORE_TX_SADDR_TX_SADDR_MASK)

/* Reserved/Not used. */
#define UDMA_CORE_TX_SADDR_RESERVED_0_MASK                           (0xffe00000)
#define UDMA_CORE_TX_SADDR_RESERVED_0_SHIFT                          (21)
#define UDMA_CORE_TX_SADDR_RESERVED_0(val)                           (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_SADDR_RESERVED_0_SHIFT)) & UDMA_CORE_TX_SADDR_RESERVED_0_MASK)


/*! @name TX_SIZE */
/* Buffer size in byte. (128kBytes maximum)
  - Read: buffer size left
  - Write: set buffer size */
#define UDMA_CORE_TX_SIZE_TX_SIZE_MASK                               (0xfffff)
#define UDMA_CORE_TX_SIZE_TX_SIZE_SHIFT                              (0)
#define UDMA_CORE_TX_SIZE_TX_SIZE(val)                               (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_SIZE_TX_SIZE_SHIFT)) & UDMA_CORE_TX_SIZE_TX_SIZE_MASK)

/* Reserved/Not used. */
#define UDMA_CORE_TX_SIZE_RESERVED_0_MASK                            (0xfff00000)
#define UDMA_CORE_TX_SIZE_RESERVED_0_SHIFT                           (20)
#define UDMA_CORE_TX_SIZE_RESERVED_0(val)                            (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_SIZE_RESERVED_0_SHIFT)) & UDMA_CORE_TX_SIZE_RESERVED_0_MASK)


/*! @name TX_CFG */
/* Channel continuous mode:
  - 1'b0: disable
  - 1'b1: enable
  At the end of the buffer the uDMA reloads the address and size and starts a new transfer. */
#define UDMA_CORE_TX_CFG_CONTINOUS_MASK                              (0x1)
#define UDMA_CORE_TX_CFG_CONTINOUS_SHIFT                             (0)
#define UDMA_CORE_TX_CFG_CONTINOUS(val)                              (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_CFG_CONTINOUS_SHIFT)) & UDMA_CORE_TX_CFG_CONTINOUS_MASK)

/* Channel transfer size used to increment uDMA buffer address pointer:
  - 2'b00: +1 (8 bits)
  - 2'b01: +2 (16 bits)
  - 2'b10: +4 (32 bits)
  - 2'b11: +0 */
#define UDMA_CORE_TX_CFG_DATASIZE_MASK                               (0x6)
#define UDMA_CORE_TX_CFG_DATASIZE_SHIFT                              (1)
#define UDMA_CORE_TX_CFG_DATASIZE(val)                               (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_CFG_DATASIZE_SHIFT)) & UDMA_CORE_TX_CFG_DATASIZE_MASK)

/* Reserved/Not used. */
#define UDMA_CORE_TX_CFG_RESERVED_0_MASK                             (0x8)
#define UDMA_CORE_TX_CFG_RESERVED_0_SHIFT                            (3)
#define UDMA_CORE_TX_CFG_RESERVED_0(val)                             (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_CFG_RESERVED_0_SHIFT)) & UDMA_CORE_TX_CFG_RESERVED_0_MASK)

/* Channel enable and start transfer:
  - 1'b0: disable
  - 1'b1: enable
  This signal is used also to queue a transfer if one is already ongoing. */
#define UDMA_CORE_TX_CFG_EN_MASK                                     (0x10)
#define UDMA_CORE_TX_CFG_EN_SHIFT                                    (4)
#define UDMA_CORE_TX_CFG_EN(val)                                     (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_CFG_EN_SHIFT)) & UDMA_CORE_TX_CFG_EN_MASK)

/* Transfer pending in queue status flag:
  - 1'b0: no pending transfer in the queue
  - 1'b1: pending transfer in the queue */
#define UDMA_CORE_TX_CFG_PENDING_MASK                                (0x20)
#define UDMA_CORE_TX_CFG_PENDING_SHIFT                               (5)
#define UDMA_CORE_TX_CFG_PENDING(val)                                (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_CFG_PENDING_SHIFT)) & UDMA_CORE_TX_CFG_PENDING_MASK)

/* Channel clear and stop transfer:
  - 1'b0: disable
  - 1'b1: stop and clear the on-going transfer */
#define UDMA_CORE_TX_CFG_CLR_MASK                                    (0x40)
#define UDMA_CORE_TX_CFG_CLR_SHIFT                                   (6)
#define UDMA_CORE_TX_CFG_CLR(val)                                    (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_CFG_CLR_SHIFT)) & UDMA_CORE_TX_CFG_CLR_MASK)

/* Reserved/Not used. */
#define UDMA_CORE_TX_CFG_RESERVED_1_MASK                             (0xffffff80)
#define UDMA_CORE_TX_CFG_RESERVED_1_SHIFT                            (7)
#define UDMA_CORE_TX_CFG_RESERVED_1(val)                             (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_CFG_RESERVED_1_SHIFT)) & UDMA_CORE_TX_CFG_RESERVED_1_MASK)


/*! @name TX_INITCFG */
/* Reserved/Not used. */
#define UDMA_CORE_TX_INITCFG_RESERVED_0_MASK                         (0xffffffff)
#define UDMA_CORE_TX_INITCFG_RESERVED_0_SHIFT                        (0)
#define UDMA_CORE_TX_INITCFG_RESERVED_0(val)                         (((uint32_t)(((uint32_t)(val)) << UDMA_CORE_TX_INITCFG_RESERVED_0_SHIFT)) & UDMA_CORE_TX_INITCFG_RESERVED_0_MASK)




/*! @name RX_SADDR */
typedef union
{
    struct
    {
        /* Configure pointer to memory buffer:
        - Read: value of the pointer until transfer is over. Else returns 0
        - Write: set Address Pointer to memory buffer start address */
        uint32_t rx_saddr:21;
        /* Reserved/Not used. */
        uint32_t reserved_0:11;
    } field;
    uint32_t word;
} udma_core_rx_saddr_t;

/*! @name RX_SIZE */
typedef union
{
    struct
    {
        /* Buffer size in byte. (128kBytes maximum)
        - Read: buffer size left
        - Write: set buffer size */
        uint32_t rx_size:20;
        /* Reserved/Not used. */
        uint32_t reserved_0:12;
    } field;
    uint32_t word;
} udma_core_rx_size_t;

/*! @name RX_CFG */
typedef union
{
    struct
    {
        /* Channel continuous mode:
        - 1'b0: disable
        - 1'b1: enable
        At the end of the buffer the uDMA reloads the address and size and starts a new transfer. */
        uint32_t continous:1;
        /* Channel transfer size used to increment uDMA buffer address pointer:
        - 2'b00: +1 (8 bits)
        - 2'b01: +2 (16 bits)
        - 2'b10: +4 (32 bits)
        - 2'b11: +0 */
        uint32_t datasize:2;
        /* Reserved/Not used. */
        uint32_t reserved_0:1;
        /* Channel enable and start transfer:
        - 1'b0: disable
        - 1'b1: enable
        This signal is used also to queue a transfer if one is already ongoing. */
        uint32_t en:1;
        /* Transfer pending in queue status flag:
        - 1'b0: no pending transfer in the queue
        - 1'b1: pending transfer in the queue */
        uint32_t pending:1;
        /* Channel clear and stop transfer:
        - 1'b0: disable
        - 1'b1: stop and clear the on-going transfer */
        uint32_t clr:1;
        /* Reserved/Not used. */
        uint32_t reserved_1:25;
    } field;
    uint32_t word;
} udma_core_rx_cfg_t;

/*! @name RX_INITCFG */
typedef union
{
    struct
    {
        /* Reserved/Not used. */
        uint32_t reserved_0:32;
    } field;
    uint32_t word;
} udma_core_rx_initcfg_t;

/*! @name TX_SADDR */
typedef union
{
    struct
    {
        /* Configure pointer to memory buffer:
        - Read: value of the pointer until transfer is over. Else returns 0
        - Write: set Address Pointer to memory buffer start address */
        uint32_t tx_saddr:21;
        /* Reserved/Not used. */
        uint32_t reserved_0:11;
    } field;
    uint32_t word;
} udma_core_tx_saddr_t;

/*! @name TX_SIZE */
typedef union
{
    struct
    {
        /* Buffer size in byte. (128kBytes maximum)
        - Read: buffer size left
        - Write: set buffer size */
        uint32_t tx_size:20;
        /* Reserved/Not used. */
        uint32_t reserved_0:12;
    } field;
    uint32_t word;
} udma_core_tx_size_t;

/*! @name TX_CFG */
typedef union
{
    struct
    {
        /* Channel continuous mode:
        - 1'b0: disable
        - 1'b1: enable
        At the end of the buffer the uDMA reloads the address and size and starts a new transfer. */
        uint32_t continous:1;
        /* Channel transfer size used to increment uDMA buffer address pointer:
        - 2'b00: +1 (8 bits)
        - 2'b01: +2 (16 bits)
        - 2'b10: +4 (32 bits)
        - 2'b11: +0 */
        uint32_t datasize:2;
        /* Reserved/Not used. */
        uint32_t reserved_0:1;
        /* Channel enable and start transfer:
        - 1'b0: disable
        - 1'b1: enable
        This signal is used also to queue a transfer if one is already ongoing. */
        uint32_t en:1;
        /* Transfer pending in queue status flag:
        - 1'b0: no pending transfer in the queue
        - 1'b1: pending transfer in the queue */
        uint32_t pending:1;
        /* Channel clear and stop transfer:
        - 1'b0: disable
        - 1'b1: stop and clear the on-going transfer */
        uint32_t clr:1;
        /* Reserved/Not used. */
        uint32_t reserved_1:25;
    } field;
    uint32_t word;
} udma_core_tx_cfg_t;

/*! @name TX_INITCFG */
typedef union
{
    struct
    {
        /* Reserved/Not used. */
        uint32_t reserved_0:32;
    } field;
    uint32_t word;
} udma_core_tx_initcfg_t;


#define UDMA_CORE_CFG_DATASIZE_8                                     (0x0)
#define UDMA_CORE_CFG_DATASIZE_16                                    (0x1)
#define UDMA_CORE_CFG_DATASIZE_32                                    (0x2)

#endif /* HAL_INCLUDE_HAL_UDMA_CORE_PERIPH_H_ */
