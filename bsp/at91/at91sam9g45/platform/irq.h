/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#ifndef __IRQ_H__
#define __IRQ_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * IRQ line status.
 *
 * Bits 0-7 are reserved
 *
 * IRQ types
 */
#define IRQ_TYPE_NONE       0x00000000  /* Default, unspecified type */
#define IRQ_TYPE_EDGE_RISING    0x00000001  /* Edge rising type */
#define IRQ_TYPE_EDGE_FALLING   0x00000002  /* Edge falling type */
#define IRQ_TYPE_EDGE_BOTH (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING)
#define IRQ_TYPE_LEVEL_HIGH 0x00000004  /* Level high type */
#define IRQ_TYPE_LEVEL_LOW  0x00000008  /* Level low type */
#define IRQ_TYPE_SENSE_MASK 0x0000000f  /* Mask of the above */
#define IRQ_TYPE_PROBE      0x00000010  /* Probing in progress */

#ifdef __cplusplus
}
#endif

#endif
