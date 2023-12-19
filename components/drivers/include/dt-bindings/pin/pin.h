/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DT_BINDINGS_PIN_PIN_H__
#define __DT_BINDINGS_PIN_PIN_H__

/* Bit 0 express polarity */
#define PIN_ACTIVE_HIGH         0
#define PIN_ACTIVE_LOW          1

/* Bit 1 express single-endedness */
#define PIN_PUSH_PULL           0
#define PIN_SINGLE_ENDED        2

/* Bit 2 express Open drain or open source */
#define PIN_LINE_OPEN_SOURCE    0
#define PIN_LINE_OPEN_DRAIN     4

/*
 * Open Drain/Collector is the combination of single-ended open drain interface.
 * Open Source/Emitter is the combination of single-ended open source interface.
 */
#define PIN_OPEN_DRAIN          (PIN_SINGLE_ENDED | PIN_LINE_OPEN_DRAIN)
#define PIN_OPEN_SOURCE         (PIN_SINGLE_ENDED | PIN_LINE_OPEN_SOURCE)

/* Bit 3 express PIN suspend/resume and reset persistence */
#define PIN_PERSISTENT          0
#define PIN_TRANSITORY          8

/* Bit 4 express pull up */
#define PIN_PULL_UP             16

/* Bit 5 express pull down */
#define PIN_PULL_DOWN           32

/* Bit 6 express pull disable */
#define PIN_PULL_DISABLE        64

#endif /* __DT_BINDINGS_PIN_PIN_H__ */
