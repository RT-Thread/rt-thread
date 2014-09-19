/*
 * GDB stub.
 * 
 * Migarte form linux to rt-thread by Wzyy2
 * Original edition : KGDB stub
 * 
 * File      : gdb_stub.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-04     Wzyy2      first version
 *
 * This file incorporates work covered by the following copyright and
 * permission notice: 
 *
 * KGDB stub.
 *
 * Maintainer: Jason Wessel <jason.wessel@windriver.com>
 *
 * Copyright (C) 2000-2001 VERITAS Software Corporation.
 * Copyright (C) 2002-2004 Timesys Corporation
 * Copyright (C) 2003-2004 Amit S. Kale <amitkale@linsyssoft.com>
 * Copyright (C) 2004 Pavel Machek <pavel@suse.cz>
 * Copyright (C) 2004-2006 Tom Rini <trini@kernel.crashing.org>
 * Copyright (C) 2004-2006 LinSysSoft Technologies Pvt. Ltd.
 * Copyright (C) 2005-2008 Wind River Systems, Inc.
 * Copyright (C) 2007 MontaVista Software, Inc.
 * Copyright (C) 2008 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * Contributors at various stages not listed above:
 *  Jason Wessel ( jason.wessel@windriver.com )
 *  George Anzinger <george@mvista.com>
 *  Anurekh Saxena (anurekh.saxena@timesys.com)
 *  Lake Stevens Instrument Division (Glenn Engel)
 *  Jim Kingdon, Cygnus Support.
 *
 * Original KGDB stub: David Grothe <dave@gcom.com>,
 * Tigran Aivazian <tigran@sco.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */
#include <rtthread.h>
#include <rthw.h>
#include <string.h>
#include "gdb_stub.h"


struct gdb_state {
    int	        signo;
    int			pass_exception;    
}gs;

/**
 * gdb_connected - Is a host GDB connected to us?
 */
int				gdb_connected;



/*
 * Holds information about breakpoints in a kernel. These breakpoints are
 * added and removed by gdb.
 */
#if RT_GDB_HAVE_SWBP
static struct gdb_bkpt		gdb_break[GDB_MAX_BREAKPOINTS] = {
    [0 ... GDB_MAX_BREAKPOINTS-1] = { .state = BP_UNDEFINED }
};
#endif


/* Storage for the registers, in GDB format. */
static unsigned long		gdb_regs[(NUMREGBYTES +
        sizeof(unsigned long) - 1) /
sizeof(unsigned long)];

char remcom_in_buffer[BUFMAX];
char remcom_out_buffer[BUFMAX];


static const char hexchars[] = "0123456789abcdef";


//to call that there has been an error
void* volatile gdb_mem_fault_handler = (void *)0;
static long probe_kernel_write(void *dst, void *src, size_t size)
{
    int i = 0;
    char *dst_ptr = (char *)dst;
    char *src_ptr = (char *)src;

    gdb_mem_fault_handler = &&err;

    for (i = 0; i<size; i++) {
        *(dst_ptr++) = *(src_ptr++);
    }

    gdb_mem_fault_handler = (void *)0;
    return 0;
err:
    gdb_mem_fault_handler = (void *)0;
    return -1;
}

/*
 * GDB remote protocol parser:
 */
static int hex(char ch)
{
    if ((ch >= 'a') && (ch <= 'f'))
        return ch - 'a' + 10;
    if ((ch >= '0') && (ch <= '9'))
        return ch - '0';
    if ((ch >= 'A') && (ch <= 'F'))
        return ch - 'A' + 10;
    return -1;
}

static char tohex(char c)
{
    return hexchars[c & 15];
}

/*
 * Copy the binary array pointed to by buf into mem.  Fix $, #, and
 * 0x7d escaped with 0x7d.  Return a pointer to the character after
 * the last byte written.
 */
int gdb_ebin2mem(char *buf, char *mem, int count)
{
    int err = 0;
    char c;

    while (count-- > 0) {
        c = *buf++;
        if (c == 0x7d)
            c = *buf++ ^ 0x20;

		err = probe_kernel_write(mem, &c, 1);
		if (err)
			break;

        mem++;
    }

    return err;
}

/*
 * Convert the hex array pointed to by buf into binary to be placed in mem.
 * Return a pointer to the character AFTER the last byte written.
 * May return an error.
 */
int gdb_hex2mem(char *buf, char *mem, int count)
{
    char *tmp_raw;
    char *tmp_hex;

	tmp_raw = buf + count * 2;

    tmp_hex = tmp_raw - 1;
	while (tmp_hex >= buf) {
		tmp_raw--;
		*tmp_raw = hex(*tmp_hex--);
		*tmp_raw |= hex(*tmp_hex--) << 4;
	}

    return probe_kernel_write(mem, tmp_raw, count);
}
/*
 * Convert the memory pointed to by mem into hex, placing result in buf.
 * Return a pointer to the last char put in buf (null). May return an error.
 */
int gdb_mem2hex(char *mem, char *buf, int count)
{
    char *tmp = mem;
    char ch;

    gdb_mem_fault_handler = &&err;

    while (count > 0) {
        ch = *(tmp++);
        *(buf++) = tohex((ch >> 4) & 0xf);
        *(buf++) = tohex(ch & 0xf);

        count--;
    }
    *buf = 0;

    gdb_mem_fault_handler = (void *)0;
    return 0;
err:
    gdb_mem_fault_handler = (void *)0;
    return -1;
}

/*
 * While we find nice hex chars, build a long_val.
 * Return number of chars processed.
 */
int gdb_hex2long(char **ptr, unsigned long *long_val)
{
    int hex_val;
    int num = 0;
    int negate = 0;

    *long_val = 0;

    if (**ptr == '-') {
        negate = 1;
        (*ptr)++;
    }
    while (**ptr) {
        hex_val = hex(**ptr);
        if (hex_val < 0)
            break;

        *long_val = (*long_val << 4) | hex_val;
        num++;
        (*ptr)++;
    }

    if (negate)
        *long_val = -*long_val;

    return num;
}

/* Write memory due to an 'M' or 'X' packet. */
static int write_mem_msg(int binary)
{
    char *ptr = &remcom_in_buffer[1];
    unsigned long addr;
    unsigned long length;
    int err;

    if (gdb_hex2long(&ptr, &addr) > 0 && *(ptr++) == ',' &&
            gdb_hex2long(&ptr, &length) > 0 && *(ptr++) == ':') {
#ifdef GDB_DATA_ACCESS
        //accesses to areas not backed can cause error
        if (gdb_permit_data_access(addr, length))    
            return -1;
#endif
        if (binary)
            err = gdb_ebin2mem(ptr, (char *)addr, length);
        else
            err = gdb_hex2mem(ptr, (char *)addr, length);
        if (err)
            return err;
#ifdef RT_GDB_ICACHE
        if (CACHE_FLUSH_IS_SAFE)
            gdb_flush_icache_range(addr, addr + length);
#endif
        return 0;
    }

    return -1;
}

/*
 * Send the packet in buffer.
 * Check for gdb connection if asked for.
 */
static void put_packet(char *buffer)
{
    unsigned char checksum;
    int count;
    char ch;

    /*
     * $<packet info>#<checksum>.
     */
    while (1) {
        gdb_io_ops.write_char('$');
        checksum = 0;
        count = 0;

        while ((ch = buffer[count])) {
            gdb_io_ops.write_char(ch);
            checksum += ch;
            count++;
        }

        gdb_io_ops.write_char('#');
        gdb_io_ops.write_char(tohex((checksum >> 4) & 0xf));
        gdb_io_ops.write_char(tohex(checksum & 0xf));


        /* Now see what we get in reply. */
        ch = gdb_io_ops.read_char();

        /* If we get an ACK, we are done. */
        if (ch == '+')
            return;

        /*
         * If we get the start of another packet, this means
         * that GDB is attempting to reconnect.  We will NAK
         * the packet being sent, and stop trying to send this
         * packet.
         */
        if (ch == '$') {
            gdb_io_ops.write_char('-');
            if (gdb_io_ops.flush)
                gdb_io_ops.flush();
            return;
        }
    }
}

/* scan for the sequence $<data>#<checksum> */
static void get_packet(char *buffer)
{
    unsigned char checksum;
    unsigned char xmitcsum;
    int count;
    char ch;

    do {
        /*
         * Spin and wait around for the start character, ignore all
         * other characters:
         */
        while ((ch = (gdb_io_ops.read_char())) != '$')
            /* nothing */;
        gdb_connected = 1;
        checksum = 0;
        xmitcsum = -1;

        count = 0;

        /*
         * now, read until a # or end of buffer is found:
         */
        while (count < (BUFMAX - 1)) {
            ch = gdb_io_ops.read_char();
            if (ch == '#')
                break;
            checksum = checksum + ch;
            buffer[count] = ch;
            count = count + 1;
        }
        buffer[count] = 0;

        if (ch == '#') {
            xmitcsum = hex(gdb_io_ops.read_char()) << 4;
            xmitcsum += hex(gdb_io_ops.read_char());

            if (checksum != xmitcsum)
                /* failed checksum */
                gdb_io_ops.write_char('-');
            else
                /* successful transfer */
                gdb_io_ops.write_char('+');
            if (gdb_io_ops.flush)
                gdb_io_ops.flush();
        }
    } while (checksum != xmitcsum);
}

static void error_packet(char *pkt, int error)
{
    error = -error;
    pkt[0] = 'E';
    pkt[1] = tohex((error / 10));
    pkt[2] = tohex((error % 10));
    pkt[3] = '\0';
}

#if RT_GDB_HAVE_SWBP
static int gdb_arch_set_breakpoint(unsigned long addr, char *saved_instr)
{
    int err;

    err = probe_kernel_write((void *)saved_instr, (void *)addr, BREAK_INSTR_SIZE);
	if (err)
		return err;

    return probe_kernel_write((void *)addr, (void *)arch_gdb_ops.gdb_bpt_instr,
				  BREAK_INSTR_SIZE);
}

static int gdb_arch_remove_breakpoint(unsigned long addr, char *bundle)
{
    return probe_kernel_write((void *)addr,
				  (void *)bundle, BREAK_INSTR_SIZE);
}
static int gdb_validate_break_address(unsigned long addr)
{
    char tmp_variable[BREAK_INSTR_SIZE];
    int err;
    /* Validate setting the breakpoint and then removing it.  In the
     * remove fails, the kernel needs to emit a bad message because we
     * are deep trouble not being able to put things back the way we
     * found them.
     */
    err = gdb_arch_set_breakpoint(addr, tmp_variable);
    if (err)
        return err;
    err = gdb_arch_remove_breakpoint(addr, tmp_variable);
    if (err)
        rt_kprintf("GDB: Critical breakpoint error,memory destroyed at: %08x \n", addr);
    return err;
}

/*
 * Some architectures need cache flushes when we set/clear a
 * breakpoint:
 */
static void gdb_flush_swbreak_addr(unsigned long addr)
{
    if (!CACHE_FLUSH_IS_SAFE)
        return;

    /* Force flush instruction cache if it was outside the mm */
    gdb_flush_icache_range(addr, addr + BREAK_INSTR_SIZE);
}

/*
 * SW breakpoint management:
 */
static int gdb_activate_sw_breakpoints(void)
{
    unsigned long addr;
    int error = 0;
    int i;

    for (i = 0; i < GDB_MAX_BREAKPOINTS; i++) {
        if (gdb_break[i].state != BP_SET)
            continue;

        addr = gdb_break[i].bpt_addr;
        error = gdb_arch_set_breakpoint(addr,
                (char *)(gdb_break[i].saved_instr));
        if (error)
            return error;

        gdb_flush_swbreak_addr(addr);
        gdb_break[i].state = BP_ACTIVE;
    }
    return 0;
}

int gdb_set_sw_break(unsigned long addr)
{
    int err = gdb_validate_break_address(addr);
    int breakno = -1;
    int i;

    if (err)
        return err;

    for (i = 0; i < GDB_MAX_BREAKPOINTS; i++) {
        if ((gdb_break[i].state == BP_SET) &&
                (gdb_break[i].bpt_addr == addr))
            return -1;
    }
    for (i = 0; i < GDB_MAX_BREAKPOINTS; i++) {
        if (gdb_break[i].state == BP_REMOVED) {
            breakno = i;
            break;
        }
    }

    if (breakno == -1) {
        for (i = 0; i < GDB_MAX_BREAKPOINTS; i++) {
            if (gdb_break[i].state == BP_UNDEFINED) {
                breakno = i;
                break;
            }
        }
    }

    if (breakno == -1)
        return -1;

    gdb_break[breakno].state = BP_SET;
    gdb_break[breakno].type = BP_BREAKPOINT;
    gdb_break[breakno].bpt_addr = addr;

    return 0;
}

static int gdb_deactivate_sw_breakpoints(void)
{
    unsigned long addr;
    int error = 0;
    int i;

    for (i = 0; i < GDB_MAX_BREAKPOINTS; i++) {
        if (gdb_break[i].state != BP_ACTIVE)
            continue;
        addr = gdb_break[i].bpt_addr;
        error = gdb_arch_remove_breakpoint(addr,
                (char *)(gdb_break[i].saved_instr));
        if (error)
            return error;

        gdb_flush_swbreak_addr(addr);
        gdb_break[i].state = BP_SET;
    }
    return 0;
}

int gdb_remove_sw_break(unsigned long addr)
{
    int i;

    for (i = 0; i < GDB_MAX_BREAKPOINTS; i++) {
        if ((gdb_break[i].state == BP_SET) &&
                (gdb_break[i].bpt_addr == addr)) {
            gdb_break[i].state = BP_REMOVED;
            return 0;
        }
    }
    return -1;
}

int gdb_isremovedbreak(unsigned long addr)
{
    int i;

    for (i = 0; i < GDB_MAX_BREAKPOINTS; i++) {
        if ((gdb_break[i].state == BP_REMOVED) &&
                (gdb_break[i].bpt_addr == addr))
            return 1;
    }
    return 0;
}
#endif

static int remove_all_break()
{
#if RT_GDB_HAVE_SWBP
    unsigned long addr;
    int error=0;
    int i;

    /* Clear memory breakpoints. */
    for (i = 0; i < GDB_MAX_BREAKPOINTS; i++) {
        if (gdb_break[i].state != BP_ACTIVE)
            goto setundefined;
        addr = gdb_break[i].bpt_addr;
        error = gdb_arch_remove_breakpoint(addr,
                (char *)gdb_break[i].saved_instr);
        if (error)
            rt_kprintf("GDB: breakpoint remove failed: %lx\n",
                    addr);
setundefined:
        gdb_break[i].state = BP_UNDEFINED;
    }
#endif

#if RT_GDB_HAVE_HWBP
    /* Clear hardware breakpoints. */
    arch_gdb_ops.remove_all_hw_break();
#endif

    return 0;
}


static char gdbmsgbuf[BUFMAX + 1];
static void gdb_msg_write(const char *s, int len)
{
    char *bufptr;
    int wcount;
    int i;

    /* 'O'utput */
    gdbmsgbuf[0] = 'O';

    /* Fill and send buffers... */
    while (len > 0) {
        bufptr = gdbmsgbuf + 1;

        /* Calculate how many this time */
        if ((len << 1) > (BUFMAX - 2))
            wcount = (BUFMAX - 2) >> 1;
        else
            wcount = len;

        /* Pack in hex chars */
        for (i = 0; i < wcount; i++) {
            *(bufptr++) = tohex((s[i] >> 4) & 0xf);
            *(bufptr++) = tohex(s[i] & 0xf);
        }
        *bufptr = '\0';

        /* Move up */
        s += wcount;
        len -= wcount;

        /* Write packet */
        put_packet(gdbmsgbuf);
    }
}

/*
 * Return true if there is a valid gdb I/O module.  Also if no
 * debugger is attached a message can be printed to the console about
 * waiting for the debugger to attach.
 *
 * The print_wait argument is only to be true when called from inside
 * the core gdb_handle_exception, because it will wait for the
 * debugger to attach.
 */
static int gdb_io_ready(int print_wait)
{
    if (!gdb_dev)
        return 0;
    if (gdb_connected)
        return 1;
    if (print_wait)
        rt_kprintf("GDB: Waiting for remote debugger\n");
    return 1;
}

/* Handle the '?' status packets */
static void gdb_cmd_status(struct gdb_state *gs)
{
    /*
     * We know that this packet is only sent
     * during initial connect.  So to be safe,
     * we clear out our breakpoints now in case
     * GDB is reconnecting.
     */
    remove_all_break();

    remcom_out_buffer[0] = 'S';
    remcom_out_buffer[1] = tohex((gs->signo >> 4) &0xf); 
    remcom_out_buffer[2] = tohex(gs->signo & 0xf); 
    remcom_out_buffer[3] = 0;
}

/* Handle the 'm' memory read bytes */
static void gdb_cmd_memread(struct gdb_state *gs)
{
    char *ptr = &remcom_in_buffer[1];
    unsigned long length;
    unsigned long addr;
    int err;

    if (gdb_hex2long(&ptr, &addr) > 0 && *ptr++ == ',' &&
            gdb_hex2long(&ptr, &length) > 0) {
#ifdef GDB_DATA_ACCESS
        //accesses to areas not backed can cause error
        if (gdb_permit_data_access(addr, length))    
            return ;
#endif
        err = gdb_mem2hex((char *)addr, remcom_out_buffer, length);
        if (err)
            error_packet(remcom_out_buffer, err);
    } else {
        error_packet(remcom_out_buffer, -1);
    }
}

/* Handle the 'M' memory write bytes */
static void gdb_cmd_memwrite(struct gdb_state *gs)
{
    int err = write_mem_msg(0);

    if (err)
        error_packet(remcom_out_buffer, err);
    else
        strcpy(remcom_out_buffer, "OK");
}

/* Handle the 'X' memory binary write bytes */
static void gdb_cmd_binwrite(struct gdb_state *gs)
{
    int err = write_mem_msg(1);

    if (err)
        error_packet(remcom_out_buffer, err);
    else
        strcpy(remcom_out_buffer, "OK");
}

/* Handle the 'q' query packets */
static void gdb_cmd_query(struct gdb_state *gs)
{
    /* nothing,because we have no thread support */
}


/* Handle the 'g' or 'p' get registers request */
static void gdb_cmd_getregs(struct gdb_state *gs)
{
    char len = sizeof(long);

    gdb_get_register((unsigned long *)gdb_regs); 

    /*get one registers*/
    if (remcom_in_buffer[0] == 'p'){
        char *p = &remcom_in_buffer[1];
        unsigned long regno = 0;

        if (gdb_hex2long(&p, &regno)){
            gdb_mem2hex(((char *)gdb_regs) + regno * len, remcom_out_buffer, len);
            return;
        } else {
            strcpy(remcom_out_buffer, "INVALID");
            return;
        }
    }

    gdb_mem2hex((char *)gdb_regs, remcom_out_buffer, NUMREGBYTES);
}

/* Handle the 'G' or 'P' set registers request */
static void gdb_cmd_setregs(struct gdb_state *gs)
{
    char len = sizeof(long);

    /*set one registers*/
    if (remcom_in_buffer[0] == 'P'){       
        char *p = &remcom_in_buffer[1];
        unsigned long regno = 0;

        if (gdb_hex2long(&p, &regno) && *p++ == '='){
            gdb_get_register((unsigned long *)gdb_regs); 
            gdb_hex2mem(p, ((char *)gdb_regs) + regno * len, len);
            gdb_put_register(gdb_regs);
            strcpy(remcom_out_buffer, "OK");
        }

        return;
    }

    gdb_hex2mem(&remcom_in_buffer[1], (char *)gdb_regs, NUMREGBYTES);

    gdb_put_register(gdb_regs);
    strcpy(remcom_out_buffer, "OK");
}

/* Handle the 'D' or 'k', detach or kill packets */
static void gdb_cmd_detachkill(struct gdb_state *gs)
{
    int error;

    /* The detach case */
    if (remcom_in_buffer[0] == 'D') {
        error = remove_all_break();
        if (error < 0) {
            error_packet(remcom_out_buffer, error);
        } else {
            strcpy(remcom_out_buffer, "OK");
            gdb_connected = 0;
        }
        put_packet(remcom_out_buffer);
    } else {
        /*
         * Assume the kill case, with no exit code checking,
         * trying to force detach the debugger:
         */
        remove_all_break();
        gdb_connected = 0;
    }
}

/* Handle the 'z' or 'Z' breakpoint remove or set packets */
static void gdb_cmd_break(struct gdb_state *gs)
{
    /*
     * Since GDB-5.3, it's been drafted that '0' is a software
     * breakpoint, '1' is a hardware breakpoint, so let's do that.
     */
    char *bpt_type = &remcom_in_buffer[1];
    char *ptr = &remcom_in_buffer[2];
    unsigned long addr;
    unsigned long length;
    int error = 0;

    if (arch_gdb_ops.set_hw_breakpoint && *bpt_type >= '1') {
        /* Unsupported */
        if (*bpt_type > '4')
            return;
    } 
    /*
     * Test if this is a hardware breakpoint, and
     * if we support it:
     */
    if (*bpt_type == '1' && !(arch_gdb_ops.flags)) {
        /* Unsupported. */
        return;
    }
    if (*(ptr++) != ',') {
        error_packet(remcom_out_buffer, -1);
        return;
    }
    if (!gdb_hex2long(&ptr, &addr)) {
        error_packet(remcom_out_buffer, -1);
        return;
    }
    if (*(ptr++) != ',' ||
            !gdb_hex2long(&ptr, &length)) {
        error_packet(remcom_out_buffer, -1);
        return;
    }
#if RT_GDB_HAVE_SWBP
    if (remcom_in_buffer[0] == 'Z' && *bpt_type == '0')
        error = gdb_set_sw_break(addr);
    else if (remcom_in_buffer[0] == 'z' && *bpt_type == '0')
        error = gdb_remove_sw_break(addr);
#else
    if (remcom_in_buffer[0] == 'Z' && *bpt_type == '0')
        error = arch_gdb_ops.set_hw_breakpoint(addr,
                (int)length, BP_HARDWARE_BREAKPOINT);
    else if (remcom_in_buffer[0] == 'z' && *bpt_type == '0')
        error = arch_gdb_ops.remove_hw_breakpoint(addr,
                (int) length, BP_HARDWARE_BREAKPOINT);
#endif
    else if (remcom_in_buffer[0] == 'Z')
        error = arch_gdb_ops.set_hw_breakpoint(addr,
                (int)length, *bpt_type - '0');
    else if (remcom_in_buffer[0] == 'z')
        error = arch_gdb_ops.remove_hw_breakpoint(addr,
                (int) length, *bpt_type - '0');

    if (error == 0)
        strcpy(remcom_out_buffer, "OK");
    else
        error_packet(remcom_out_buffer, error);
}

/* Handle the 'C' signal / exception passing packets */
static int gdb_cmd_exception_pass(struct gdb_state *gs)
{
    /* C09 == pass exception
     * C15 == detach gdb, pass exception
     */
    if (remcom_in_buffer[1] == '0' && remcom_in_buffer[2] == '9') {

        gs->pass_exception = 1;
        remcom_in_buffer[0] = 'c';

    } else if (remcom_in_buffer[1] == '1' && remcom_in_buffer[2] == '5') {

        gs->pass_exception = 1;
        remcom_in_buffer[0] = 'D';
        remove_all_break();
        gdb_connected = 0;
        return 1;

    } else {
        error_packet(remcom_out_buffer, -1);
        return 0;
    }

    /* Indicate fall through */
    return -1;
}


/*more about packet in https://www.sourceware.org/gdb/current/onlinedocs/gdb/Packets.html#Packets*/
static int process_packet(char *pkt)
{
    int status = 0;
    int tmp;

    status = gdb_arch_handle_exception(remcom_in_buffer,
            remcom_out_buffer);

    remcom_out_buffer[0] = 0;
    switch (pkt[0]) {
        case '?':/* gdbserial status */
            gdb_cmd_status(&gs);
            break;
        case 'q':/* query command */
            gdb_cmd_query(&gs);
            break;
        case 'p':       /* return the value of  a single CPU register */
        case 'g':       /* return the value of the CPU registers */
            gdb_cmd_getregs(&gs);
            break;  
        case 'P':       /* set the value of a single CPU registers - return OK */
        case 'G':       /* set the value of the CPU registers - return OK */
            gdb_cmd_setregs(&gs);
            break;
        case 'm': /* mAA..AA,LLLL  Read LLLL bytes at address AA..AA */
            gdb_cmd_memread(&gs);
            break;
        case 'X':/* XAA..AA,LLLL: Write LLLL escaped binary bytes at address AA.AA*/
            gdb_cmd_binwrite(&gs);
            break;
        case 'M':/* MAA..AA,LLLL: Write LLLL bytes at address AA.AA return OK */
            gdb_cmd_memwrite(&gs);
            break;
        case 'D': /* Debugger detach */
        case 'k': /* Debugger detach via kill */
            gdb_cmd_detachkill(&gs);  
            break;
        case 'C':/* Exception passing */
            tmp = gdb_cmd_exception_pass(&gs);
            if (tmp > 0)
                process_packet(remcom_in_buffer);
            if (tmp == 0)
                break;
        case 'z':/* Break point remove */
        case 'Z':/* Break point set */
            gdb_cmd_break(&gs);
            break;
        case 'H':/* task related */
            break;
        case 'T':/* Query thread status */
            break;
        case 'b': /* bBB...  Set baud rate to BB... */
            break;
        case 's': /* sAA..AA    step form address AA..AA (optional) */
        case 'c': /* cAA..AA    Continue at address AA..AA (optional) */
#if RT_GDB_HAVE_SWBP
            gdb_activate_sw_breakpoints();
#endif
            break;
    }

    if (!status)
        return -1;

exit:
    put_packet(remcom_out_buffer);
    return 0;
}


/*
 * This function does all command procesing for interfacing to gdb.
 */
int gdb_process_exception()
{
    int status;

    do {
        get_packet(remcom_in_buffer);
        status = process_packet(remcom_in_buffer);
    } while (status == 0);

    if (status < 0)
        return 0;
    else
        return 1;
}


int gdb_handle_exception(int signo, void *regs)
{
    int error; 

    gs.signo = signo;

    if (!gdb_io_ready(1)) {
        error = 1;
        return error; /* No I/O connection, so resume the system */
    }

#if RT_GDB_HAVE_SWBP
    gdb_deactivate_sw_breakpoints();
#endif
    gdb_set_register(regs);

    /* Clear the out buffer. */
    memset(remcom_out_buffer, 0, sizeof(remcom_out_buffer));         
  
    if (gdb_connected) {
        char *ptr;

        gdb_io_ops.write_char('\n');
        /* Reply to host that an exception has occurred */
        ptr = remcom_out_buffer;
        *ptr++ = 'T';
        *ptr++ = tohex((gs.signo >> 4) &0xf); 
        *ptr++ = tohex(gs.signo & 0xf); 
        /*ptr += strlen(strcpy(ptr, "thread:"));*/
        /**ptr++ = ';';*/
        put_packet(remcom_out_buffer);
    }
    gs.pass_exception = 0;


   while (gdb_process_exception());

    error = gs.pass_exception;

    return error;
}

void gdb_console_write(const char *s, unsigned count)
{
    /* If we're debugging, or GDB has not connected, don't try
     * and print. */
    if (!gdb_connected)
        return;

    gdb_msg_write(s, count);
}

