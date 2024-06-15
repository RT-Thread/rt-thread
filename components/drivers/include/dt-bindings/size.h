/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DT_BINDINGS_SIZE_H__
#define __DT_BINDINGS_SIZE_H__

#define SIZE_KB 1024
#define SIZE_MB (1024 * SIZE_KB)
#define SIZE_GB (1024 * SIZE_MB)

#define SIZE_ALIGN(size, align)         (((size) + (align) - 1) & ~((align) - 1))
#define SIZE_ALIGN_DOWN(size, align)    ((size) & ~((align) - 1))

#endif /* __DT_BINDINGS_SIZE_H__ */
