/**
  * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    io.c
  * @author
  * @version V0.1
  * @date    10-Jun-2019
  * @brief   read and write memory
  *
  ******************************************************************************
  */

#include <rtthread.h>

#ifdef RT_DEBUG_USING_IO

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "hal_base.h"

static void usage(void)
{
    rt_kprintf("Raw memory i/o utility - $Revision: 1.5 $\n\n");
    rt_kprintf("io -v -1|2|4 -r|w [-l <len>] <addr> [<value>]\n\n");
    rt_kprintf("    -v         Verbose, asks for confirmation\n");
    rt_kprintf("    -1|2|4     Sets memory access size in bytes (default byte)\n");
    rt_kprintf("    -l <len>   Length in bytes of area to access (defaults to\n");
    rt_kprintf("               one access, or whole file length)\n");
    rt_kprintf("    -r|w       Read from or Write to memory (default read)\n");
    rt_kprintf("    <addr>     The memory address to access\n");
    rt_kprintf("    <val>      The value to write (implies -w)\n\n");
    rt_kprintf("Examples:\n");
    rt_kprintf("    io 0x1000                  Reads one byte from 0x1000\n");
    rt_kprintf("    io 0x1000 0x12             Writes 0x12 to location 0x1000\n");
    rt_kprintf("    io -2 -l 8 0x1000          Reads 8 words from 0x1000\n\n");
    rt_kprintf("Note access size (-1|2|4) does not apply to file based accesses.\n\n");
}

static void
read_memory(unsigned long phys_addr, uint8_t *addr, int len, int iosize)
{
    int i;

    while (len)
    {
        rt_kprintf("%08lx: ", phys_addr);
        i = 0;
        while (i < 16 && len)
        {
            switch (iosize)
            {
            case 1:
                rt_kprintf(" %02x", *(uint8_t *)addr);
                break;
            case 2:
                rt_kprintf(" %04x", *(uint16_t *)addr);
                break;
            case 4:
                rt_kprintf(" %08lx", *(uint32_t *)addr);
                break;
            }
            i += iosize;
            addr += iosize;
            len -= iosize;
        }
        phys_addr += 16;
        rt_kprintf("\n");
    }
}

static void
write_memory(uint8_t *addr, int len, int iosize, unsigned long value)
{
    switch (iosize)
    {
    case 1:
        while (len)
        {
            *(uint8_t *)addr = value;
            len -= iosize;
            addr += iosize;
        }
        break;
    case 2:
        while (len)
        {
            *(uint16_t *)addr = value;
            len -= iosize;
            addr += iosize;
        }
        break;
    case 4:
        while (len)
        {
            *(uint32_t *)addr = value;
            len -= iosize;
            addr += iosize;
        }
        break;
    }
}

int io_mem(int argc, char **argv)
{
    int req_len = 0, opt;
    uint8_t *real_io;
    unsigned long req_addr, req_value = 0;
    char *endptr;
    int memread = 1;
    int iosize = 1;
    int verbose = 0;

    opterr = 0;
    optind = 0;

    if (argc == 1)
    {
        usage();
        return 0;
    }

    while ((opt = getopt(argc, argv, "hv124rwl:f:")) > 0)
    {
        switch (opt)
        {
        case 'h':
            usage();
        case 'v':
            verbose = 1;
            break;
        case '1':
        case '2':
        case '4':
            iosize = opt - '0';
            break;
        case 'r':
            memread = 1;
            break;
        case 'w':
            memread = 0;
            break;
        case 'l':
            req_len = strtoul(optarg, &endptr, 0);
            if (*endptr)
            {
                rt_kprintf("Bad <size> value '%s'\n", optarg);
                return 0;
            }
            break;
        default:
            rt_kprintf("Unknown option: %c\n", opt);
            usage();
        }
    }

    if (optind == argc)
    {
        rt_kprintf("No address given\n");
        return 0;
    }
    req_addr = strtoul(argv[optind], &endptr, 0);
    if (*endptr)
    {
        rt_kprintf("Bad <addr> value '%s'\n", argv[optind]);
        return 0;
    }
    optind++;

    if (optind < argc)
        memread = 0;

    if (!memread && optind == argc)
    {
        rt_kprintf("No value given for WRITE\n");
        return 0;
    }
    if (!memread)
    {
        req_value = strtoul(argv[optind], &endptr, 0);
        if (*endptr)
        {
            rt_kprintf("Bad <value> value '%s'\n", argv[optind]);
            return 0;
        }
        if ((iosize == 1 && (req_value & 0xffffff00)) ||
                (iosize == 2 && (req_value & 0xffff0000)))
        {
            rt_kprintf("<value> too large\n");
            return 0;
        }
        optind++;
    }

    if (optind < argc)
    {
        rt_kprintf("Too many arguments '%s'...\n", argv[optind]);
        return 0;
    }

    if (!req_len)
        req_len = iosize;

    if ((iosize == 2 && (req_addr & 1)) ||
            (iosize == 4 && (req_addr & 3)))
    {
        rt_kprintf("Badly aligned <addr> for access size\n");
        return 0;
    }

    if ((iosize == 2 && (req_len & 1)) ||
            (iosize == 4 && (req_len & 3)))
    {
        rt_kprintf("Badly aligned <size> for access size\n");
        return 0;
    }

    if (!verbose)
        /* Nothing */;
    else if (memread)
        rt_kprintf("Request to memread 0x%x bytes from address 0x%08lx\n"
                   "\tusing %d byte accesses\n",
                   req_len, req_addr, iosize);
    else
        rt_kprintf("Request to write 0x%x bytes to address 0x%08lx\n"
                   "\tusing %d byte accesses of value 0x%0*lx\n",
                   req_len, req_addr, iosize, iosize * 2, req_value);

    real_io = (uint8_t *)req_addr;

    if (memread)
        read_memory(req_addr, real_io, req_len, iosize);
    else
        write_memory(real_io, req_len, iosize, req_value);

    return 0;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
MSH_CMD_EXPORT_ALIAS(io_mem, io, memory read or write cmd);
#endif

#endif /* RT_DEBUG_USING_IO */
