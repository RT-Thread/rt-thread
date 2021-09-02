/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021/04/23     chunyexixiaoyu    first version

 */

#include "../dlmodule.h"
#include "../dlelf.h"

#if (__riscv_xlen == 64)
#define R_RISCV_NONE           0
#define R_RISCV_32             1
#define R_RISCV_64             2
#define R_RISCV_RELATIVE       3
#define R_RISCV_COPY           4
#define R_RISCV_JUMP_SLOT      5
#define R_RISCV_TLS_DTPMOD32   6
#define R_RISCV_TLS_DTPMOD64   7
#define R_RISCV_TLS_DTPREL32   8
#define R_RISCV_TLS_DTPREL64   9
#define R_RISCV_TLS_TPREL32   10
#define R_RISCV_TLS_TPREL64   11

int dlmodule_relocate(struct rt_dlmodule *module, Elf_Rel *rel, Elf_Addr sym_val)
{
    Elf64_Addr *where, tmp;
    Elf64_Sword addend, offset;
    rt_uint64_t upper, lower, sign, j1, j2;

    where = (Elf64_Addr *)((rt_uint8_t *)module->mem_space
                           + rel->r_offset
                           - module->vstart_addr);
    switch (ELF64_R_TYPE(rel->r_info))
    {
        case R_RISCV_NONE:
            break;
        case R_RISCV_64:
            *where = (Elf64_Addr)(sym_val + rel->r_addend);
            RT_DEBUG_LOG(RT_DEBUG_MODULE, ("R_RISCV_64: %x -> %x\n",where, *where));
            break;
        case R_RISCV_RELATIVE:
            *where = (Elf64_Addr)((rt_uint8_t *)module->mem_space - module->vstart_addr + rel->r_addend);
            RT_DEBUG_LOG(RT_DEBUG_MODULE, ("R_RISCV_RELATIVE: %x -> %x\n",where, *where));
            break;
        case R_RISCV_JUMP_SLOT:
            *where = (Elf64_Addr)sym_val;
            RT_DEBUG_LOG(RT_DEBUG_MODULE, ("R_RISCV_JUMP_SLOT: %x -> %x\n",where, *where));
            break;
        default:
            RT_DEBUG_LOG(RT_DEBUG_MODULE, ("__riscv__ELF: invalid relocate TYPE %d\n", ELF64_R_TYPE(rel->r_info)));
            return -1;
    }
    return 0;
}
#endif
