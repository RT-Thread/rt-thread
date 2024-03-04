/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DT_BINDINGS_PIN_STATE_H__
#define __DT_BINDINGS_PIN_STATE_H__

#define PIND_FLAGS_BIT_DIR_SET       (1 << 0)
#define PIND_FLAGS_BIT_DIR_OUT       (1 << 1)
#define PIND_FLAGS_BIT_DIR_VAL       (1 << 2)
#define PIND_FLAGS_BIT_OPEN_DRAIN    (1 << 3)
#define PIND_FLAGS_BIT_NONEXCLUSIVE  (1 << 4)

/* Don't change anything */
#define PIND_ASIS                 0
/* Set lines to input mode */
#define PIND_IN                   PIND_FLAGS_BIT_DIR_SET
/* Set lines to output and drive them low */
#define PIND_OUT_LOW              (PIND_FLAGS_BIT_DIR_SET | PIND_FLAGS_BIT_DIR_OUT)
/* Set lines to output and drive them high */
#define PIND_OUT_HIGH             (PIND_FLAGS_BIT_DIR_SET | PIND_FLAGS_BIT_DIR_OUT | PIND_FLAGS_BIT_DIR_VAL)
/* Set lines to open-drain output and drive them low */
#define PIND_OUT_LOW_OPEN_DRAIN   (PIND_OUT_LOW | PIND_FLAGS_BIT_OPEN_DRAIN)
/* Set lines to open-drain output and drive them high */
#define PIND_OUT_HIGH_OPEN_DRAIN  (PIND_OUT_HIGH | PIND_FLAGS_BIT_OPEN_DRAIN)

#endif /* __DT_BINDINGS_PIN_STATE_H__ */
