/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-08     RT-Thread    the first version
 */
#include "rtthread.h"

static void data_abort(unsigned long far, unsigned long iss)
{
    rt_kprintf("fault addr = 0x%016lx\n", far);
    if (iss & 0x40)
    {
        rt_kprintf("abort caused by write instruction\n");
    }
    else
    {
        rt_kprintf("abort caused by read instruction\n");
    }
    switch (iss & 0x3f)
    {
    case 0b000000:
        rt_kprintf("Address size fault, zeroth level of translation or translation table base register\n");
        break;

    case 0b000001:
        rt_kprintf("Address size fault, first level\n");
        break;

    case 0b000010:
        rt_kprintf("Address size fault, second level\n");
        break;

    case 0b000011:
        rt_kprintf("Address size fault, third level\n");
        break;

    case 0b000100:
        rt_kprintf("Translation fault, zeroth level\n");
        break;

    case 0b000101:
        rt_kprintf("Translation fault, first level\n");
        break;

    case 0b000110:
        rt_kprintf("Translation fault, second level\n");
        break;

    case 0b000111:
        rt_kprintf("Translation fault, third level\n");
        break;

    case 0b001000:
        rt_kprintf("Access flag fault, zeroth level\n");
        break;

    case 0b001001:
        rt_kprintf("Access flag fault, first level\n");
        break;

    case 0b001010:
        rt_kprintf("Access flag fault, second level\n");
        break;

    case 0b001011:
        rt_kprintf("Access flag fault, third level\n");
        break;

    case 0b001100:
        rt_kprintf("Permission fault, zeroth level\n");
        break;

    case 0b001101:
        rt_kprintf("Permission fault, first level\n");
        break;

    case 0b001110:
        rt_kprintf("Permission fault, second level\n");
        break;

    case 0b001111:
        rt_kprintf("Permission fault, third level\n");
        break;

    case 0b010000:
        rt_kprintf("Synchronous external abort, not on translation table walk\n");
        break;

    case 0b011000:
        rt_kprintf("Synchronous parity or ECC error on memory access, not on translation table walk\n");
        break;

    case 0b010100:
        rt_kprintf("Synchronous external abort on translation table walk, zeroth level\n");
        break;

    case 0b010101:
        rt_kprintf("Synchronous external abort on translation table walk, first level\n");
        break;

    case 0b010110:
        rt_kprintf("Synchronous external abort on translation table walk, second level\n");
        break;

    case 0b010111:
        rt_kprintf("Synchronous external abort on translation table walk, third level\n");
        break;

    case 0b011100:
        rt_kprintf("Synchronous parity or ECC error on memory access on translation table walk, zeroth level\n");
        break;

    case 0b011101:
        rt_kprintf("Synchronous parity or ECC error on memory access on translation table walk, first level\n");
        break;

    case 0b011110:
        rt_kprintf("Synchronous parity or ECC error on memory access on translation table walk, second level\n");
        break;

    case 0b011111:
        rt_kprintf("Synchronous parity or ECC error on memory access on translation table walk, third level\n");
        break;

    case 0b100001:
        rt_kprintf("Alignment fault\n");
        break;

    case 0b110000:
        rt_kprintf("TLB conflict abort\n");
        break;

    case 0b110100:
        rt_kprintf("IMPLEMENTATION DEFINED fault (Lockdown fault)\n");
        break;

    case 0b110101:
        rt_kprintf("IMPLEMENTATION DEFINED fault (Unsupported Exclusive access fault)\n");
        break;

    case 0b111101:
        rt_kprintf("Section Domain Fault, used only for faults reported in the PAR_EL1\n");
        break;

    case 0b111110:
        rt_kprintf("Page Domain Fault, used only for faults reported in the PAR_EL1\n");
        break;

    default:
        rt_kprintf("unknow abort\n");
        break;
    }
}

void print_exception(unsigned long esr, unsigned long epc)
{
    rt_uint8_t ec;
    rt_uint32_t iss;
    unsigned long fault_addr;
    rt_kprintf("\nexception info:\n");
    ec = (unsigned char)((esr >> 26) & 0x3fU);
    iss = (unsigned int)(esr & 0x00ffffffU);
    rt_kprintf("esr.EC :0x%02x\n", ec);
    rt_kprintf("esr.IL :0x%02x\n", (unsigned char)((esr >> 25) & 0x01U));
    rt_kprintf("esr.ISS:0x%08x\n", iss);
    rt_kprintf("epc    :0x%016p\n", (void *)epc);
    switch (ec)
    {
    case 0x00:
        rt_kprintf("Exceptions with an unknow reason\n");
        break;

    case 0x01:
        rt_kprintf("Exceptions from an WFI or WFE instruction\n");
        break;

    case 0x03:
        rt_kprintf("Exceptions from an MCR or MRC access to CP15 from AArch32\n");
        break;

    case 0x04:
        rt_kprintf("Exceptions from an MCRR or MRRC access to CP15 from AArch32\n");
        break;

    case 0x05:
        rt_kprintf("Exceptions from an MCR or MRC access to CP14 from AArch32\n");
        break;

    case 0x06:
        rt_kprintf("Exceptions from an LDC or STC access to CP14 from AArch32\n");
        break;

    case 0x07:
        rt_kprintf("Exceptions from Access to Advanced SIMD or floating-point registers\n");
        break;

    case 0x08:
        rt_kprintf("Exceptions from an MRC (or VMRS) access to CP10 from AArch32\n");
        break;

    case 0x0c:
        rt_kprintf("Exceptions from an MCRR or MRRC access to CP14 from AArch32\n");
        break;

    case 0x0e:
        rt_kprintf("Exceptions that occur because ther value of PSTATE.IL is 1\n");
        break;

    case 0x11:
        rt_kprintf("SVC call from AArch32 state\n");
        break;

    case 0x15:
        rt_kprintf("SVC call from AArch64 state\n");
        break;

    case 0x20:
        rt_kprintf("Instruction abort from lower exception level\n");
        break;

    case 0x21:
        rt_kprintf("Instruction abort from current exception level\n");
        break;

    case 0x22:
        rt_kprintf("PC alignment fault\n");
        break;

    case 0x24:
        rt_kprintf("Data abort from a lower Exception level\n");
        __asm__ volatile("mrs %0, far_el1":"=r"(fault_addr));
        data_abort(fault_addr, iss);
        break;

    case 0x25:
        rt_kprintf("Data abort\n");
        __asm__ volatile("mrs %0, far_el1":"=r"(fault_addr));
        data_abort(fault_addr, iss);
        break;

    default:
        rt_kprintf("Other error\n");
        break;
    }
}
