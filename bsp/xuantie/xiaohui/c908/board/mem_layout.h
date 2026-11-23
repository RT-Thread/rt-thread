/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __MEM_LAYOUT_H__
#define __MEM_LAYOUT_H__

#include "../rtconfig.h"

/*
 * Physical memory layout (xiaohui: DRAM 4GB @ 0x50000000):
 *
 * +---------------+ <- MEM_PHYS_BASE + MEM_TOTAL_SIZE (0x150000000)
 * |   ......      |  (unused by kernel, reserved)
 * +---------------+ <- MEM_PHYS_BASE + MEM_RTSMART_SIZE
 * |   guard       |  MEM_GUARD_SIZE
 * +---------------+ <- end of kernel image + heap + page pool
 * |   page pool   |  (till RTSMART end, managed by rt_page)
 * +---------------+
 * |   heap        |  MEM_HEAP_SIZE (after .bss)
 * +---------------+
 * |   kernel      |  linked at KERNEL_VADDR_START + MEM_PHYS_BASE + MEM_OPENSBI_SIZE
 * +---------------+ <- MEM_PHYS_BASE + MEM_OPENSBI_SIZE (0x50200000)
 * |   opensbi     |  MEM_OPENSBI_SIZE, fw_dynamic.bin is loaded here by QEMU
 * +---------------+ <- MEM_PHYS_BASE (0x50000000)
 *
 */

#define MEM_PHYS_BASE  0x50000000
#define MEM_TOTAL_SIZE 0x100000000
#define MEM_GUARD_SIZE 0x1000

/*
 * Region reserved for the OpenSBI firmware at the bottom of DRAM.
 */
#define MEM_OPENSBI_SIZE 0x200000

/* memory managed by rt-smart kernel (kernel image + heap + page pool) */
#ifndef MEM_RTSMART_SIZE
#define MEM_RTSMART_SIZE 0x10000000
#endif

/* system heap size, placed right after .bss */
#ifndef MEM_HEAP_SIZE
#define MEM_HEAP_SIZE 0x2000000
#endif

#define MEM_KERNEL_SIZE (MEM_RTSMART_SIZE - MEM_OPENSBI_SIZE - MEM_GUARD_SIZE)

#endif /* __MEM_LAYOUT_H__ */
