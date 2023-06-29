/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author      Notes
 * 2018/08/29     Bernard     first version
 */

#include "../dlmodule.h"
#include "../dlelf.h"

#ifdef __arm__

#define DBG_TAG           "kernel.module"
#ifdef RT_DEBUG_MODULE
#define DBG_LVL           DBG_LOG
#else
#define DBG_LVL           DBG_WARNING
#endif /* defined (RT_DEBUG_MODULE) */
#include <rtdbg.h>

int dlmodule_relocate(struct rt_dlmodule *module, Elf32_Rel *rel, Elf32_Addr sym_val)
{
    Elf32_Addr *where, tmp;
    Elf32_Sword addend, offset;
    rt_uint32_t upper, lower, sign, j1, j2;

    where = (Elf32_Addr *)((rt_uint8_t *)module->mem_space
                           + rel->r_offset
                           - module->vstart_addr);
    switch (ELF32_R_TYPE(rel->r_info))
    {
    case R_ARM_NONE:
        break;
    case R_ARM_ABS32:
        *where += (Elf32_Addr)sym_val;
        LOG_D("R_ARM_ABS32: %x -> %x",
              where, *where);
        break;
    case R_ARM_PC24:
    case R_ARM_PLT32:
    case R_ARM_CALL:
    case R_ARM_JUMP24:
        addend = *where & 0x00ffffff;
        if (addend & 0x00800000)
            addend |= 0xff000000;
        tmp = sym_val - (Elf32_Addr)where + (addend << 2);
        tmp >>= 2;
        *where = (*where & 0xff000000) | (tmp & 0x00ffffff);
        LOG_D("R_ARM_PC24: %x -> %x",
              where, *where);
        break;
    case R_ARM_REL32:
        *where += sym_val - (Elf32_Addr)where;
        LOG_D("R_ARM_REL32: %x -> %x, sym %x, offset %x",
              where, *where, sym_val, rel->r_offset);
        break;
    case R_ARM_V4BX:
        *where &= 0xf000000f;
        *where |= 0x01a0f000;
        break;

    case R_ARM_GLOB_DAT:
    case R_ARM_JUMP_SLOT:
        *where = (Elf32_Addr)sym_val;
        LOG_D("R_ARM_JUMP_SLOT: 0x%x -> 0x%x 0x%x",
              where, *where, sym_val);
        break;
#if 0        /* To do */
    case R_ARM_GOT_BREL:
        temp   = (Elf32_Addr)sym_val;
        *where = (Elf32_Addr)&temp;
        LOG_D("R_ARM_GOT_BREL: 0x%x -> 0x%x 0x%x",
              where, *where, sym_val);
        break;
#endif

    case R_ARM_RELATIVE:
        *where = (Elf32_Addr)sym_val + *where;
        LOG_D("R_ARM_RELATIVE: 0x%x -> 0x%x 0x%x",
              where, *where, sym_val);
        break;
    case R_ARM_THM_CALL:
    case R_ARM_THM_JUMP24:
        upper  = *(rt_uint16_t *)where;
        lower  = *(rt_uint16_t *)((Elf32_Addr)where + 2);

        sign   = (upper >> 10) & 1;
        j1     = (lower >> 13) & 1;
        j2     = (lower >> 11) & 1;
        offset = (sign << 24) |
                 ((~(j1 ^ sign) & 1) << 23) |
                 ((~(j2 ^ sign) & 1) << 22) |
                 ((upper & 0x03ff) << 12) |
                 ((lower & 0x07ff) << 1);
        if (offset & 0x01000000)
            offset -= 0x02000000;
        offset += sym_val - (Elf32_Addr)where;

        if (!(offset & 1) ||
            offset <= (rt_int32_t)0xff000000 ||
            offset >= (rt_int32_t)0x01000000)
        {
            rt_kprintf("Module: Only Thumb addresses allowed\n");

            return -1;
        }

        sign = (offset >> 24) & 1;
        j1   = sign ^ (~(offset >> 23) & 1);
        j2   = sign ^ (~(offset >> 22) & 1);
        *(rt_uint16_t *)where = (rt_uint16_t)((upper & 0xf800) |
                                              (sign << 10) |
                                              ((offset >> 12) & 0x03ff));
        *(rt_uint16_t *)(where + 2) = (rt_uint16_t)((lower & 0xd000) |
                                                    (j1 << 13) | (j2 << 11) |
                                                    ((offset >> 1) & 0x07ff));
        upper = *(rt_uint16_t *)where;
        lower = *(rt_uint16_t *)((Elf32_Addr)where + 2);
        break;
    default:
        return -1;
    }

    return 0;
}
#endif
