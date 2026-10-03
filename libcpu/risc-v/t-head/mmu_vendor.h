/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 * 2021-05-03     lizhirui     porting to c906/c908
 * 2023-10-12     Shell        Add permission control API
 * 2025-04-26     GuEe-GUI     Follow the specific and vendor
 */

#ifndef __MMU_VENDOR_H__
#define __MMU_VENDOR_H__

#include <asm-generic.h>

/* C-SKY extend */
#define __PTE_SEC               BIT(59) /* Security */
#define __PTE_SHARE             BIT(60) /* Shareable */
#define __PTE_BUF               BIT(61) /* Bufferable */
#define __PTE_CACHE             BIT(62) /* Cacheable */
#define __PTE_SO                BIT(63) /* Strong Order */

#define PTE_VENDOR_PMA          (__PTE_CACHE | __PTE_BUF | __PTE_SHARE)
#define PTE_VENDOR_NOCACHE      (__PTE_BUF | __PTE_SHARE)
#define PTE_VENDOR_IO           (__PTE_SO | __PTE_SHARE)

#define MMU_VENDOR_MAP_K_RW     (PTE_ATTR_KERNEL | PTE_G)
#define MMU_VENDOR_MAP_EARLY    (MMU_VENDOR_MAP_K_RW | PTE_VENDOR_PMA)

#endif /* __MMU_VENDOR_H__ */
