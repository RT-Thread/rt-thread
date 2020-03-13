
/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-13     bigmagic     first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <backtrace.h>

#define DBG_TAG    "BACKTRACE"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

typedef unsigned int bool;
#define true 1
#define false 0
#define UNWIND_LIMIT 20

/* Frame records form a linked list in the stack */
struct frame_record 
{
    /* Previous frame record in the list */
    struct frame_record *parent;
    /* Return address of the function at this level */
    uintptr_t return_addr;
};


static bool is_address_readable(uintptr_t addr)
{
    return true;
}

/*
 * Returns true if all the bytes in a given object are in mapped memory and an
 * LDR using this pointer would succeed, false otherwise.
 */
static bool is_valid_object(uintptr_t addr, size_t size)
{
    if (addr == 0U)
    {
        return false;
    }

    /* Detect overflows */
    if ((addr + size) < addr)
    {
        return false;
    }

    /* A pointer not aligned properly could trigger an alignment fault. */
    if ((addr & (sizeof(uintptr_t) - 1U)) != 0U)
    {
        return false;
    }

    /* Check that all the object is readable */
    for (size_t i = 0; i < size; i++) 
    {
        if (!is_address_readable(addr + i))
        {
            return false;
        }
    }
    return true;
}

/*
 * Returns true if the pointer points at a valid frame record, false otherwise.
 */
static bool is_valid_frame_record(struct frame_record *fr)
{
    return is_valid_object((uintptr_t)fr, sizeof(struct frame_record));
}

/*
 * Returns true if the specified address is correctly aligned and points to a
 * valid memory region.
 */
static bool is_valid_jump_address(uintptr_t addr)
{
    if (addr == 0U)
        return false;

    /* Check alignment. Both A64 and A32 use 32-bit opcodes */
    if ((addr & (sizeof(uint32_t) - 1U)) != 0U)
    {
        return false;
    }

    if (!is_address_readable(addr))
    {
        return false;
    }
    return true;
}

/*
 * Adjust the frame-pointer-register value by 4 bytes on AArch32 to have the
 * same layout as AArch64.
 */
static struct frame_record *adjust_frame_record(struct frame_record *fr)
{
    return fr;
}

static const char *get_el_str(unsigned int el)
{
    if (el == 3U) {
        return "EL3";
    } else if (el == 2U) {
        return "EL2";
    } else {
        return "S-EL1";
    }
}

// static char *unwind_get_function_name(void *address)
// {
//     return RT_NULL;
// }

static void unwind_stack(struct frame_record *fr, uintptr_t current_pc, uintptr_t link_register, struct rt_hw_exp_stack *regs)
{
    uintptr_t call_site;
    static const char *backtrace_str = "%u: %s: 0x%lx\n";
    const char *el_str = get_el_str(1U);

    if (!is_valid_frame_record(fr))
    {
        rt_kprintf("ERROR: Corrupted frame pointer (frame record address = %p)\n",fr);
        return;
    }

    if (fr->return_addr != link_register)
    {
        rt_kprintf("ERROR: Corrupted stack (frame record address = %p)\n", fr);
        return;
    }

    rt_kprintf("please use `aarch64-elf-addr2line -Cif -e rtthread.elf addr`\n");
    
    /* The level 0 of the backtrace is the current backtrace function */
    rt_kprintf(backtrace_str, 0U, el_str, regs->pc);

    /*
     * The last frame record pointer in the linked list at the beginning of
     * the stack should be NULL unless stack is corrupted.
     */
    for (unsigned int i = 1U; i < UNWIND_LIMIT; i++)
    {
        /* If an invalid frame record is found, exit. */
        if (!is_valid_frame_record(fr))
        {
            return;
        }
        /*
         * A32 and A64 are fixed length so the address from where the
         * call was made is the instruction before the return address,
         * which is always 4 bytes before it.
         */
        call_site = fr->return_addr - 4U;
        /*
         * If the address is invalid it means that the frame record is
         * probably corrupted.
         */
        if (!is_valid_jump_address(call_site))
        {
            return;
        }

        if(i > 2)
        {
            rt_kprintf(backtrace_str, i - 2, el_str, call_site);
        }
        

        //rt_kprintf("func name is %s\n",unwind_get_function_name(call_site));

        fr = adjust_frame_record(fr->parent);
    }

    rt_kprintf("ERROR: Max backtrace depth reached\n");
}


void backtrace(struct rt_hw_exp_stack *regs)
{
    uintptr_t return_address = (uintptr_t)__builtin_return_address(0U);
    struct frame_record *fr = __builtin_frame_address(0U);

    fr = adjust_frame_record(fr);

    unwind_stack(fr, (uintptr_t)&backtrace, return_address, regs);
}
