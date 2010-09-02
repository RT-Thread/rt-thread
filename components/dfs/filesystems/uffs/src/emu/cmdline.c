/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  UFFS is free software; you can redistribute it and/or modify it under
  the GNU Library General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any
  later version.

  UFFS is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  or GNU Library General Public License, as applicable, for more details.
 
  You should have received a copy of the GNU General Public License
  and GNU Library General Public License along with UFFS; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301, USA.

  As a special exception, if other files instantiate templates or use
  macros or inline functions from this file, or you compile this file
  and link it with other works to produce a work based on this file,
  this file does not by itself cause the resulting work to be covered
  by the GNU General Public License. However the source code for this
  file must still be made available in accordance with section (3) of
  the GNU General Public License v2.
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/

/**
 * \file cmdline.c
 * \brief command line test interface
 * \author Ricky Zheng, created in 22th Feb, 2007
 */

#include <string.h>
#include <stdio.h>
//#include <conio.h>
#include "cmdline.h"
#include "uffs/uffs_fs.h"

#define PROMPT "UFFS>"


static BOOL m_exit = FALSE;
static struct cli_commandset cmdset[200] = {0};
static int m_cmdCount = 0;
static char str_buf[128];

const char * cli_getparam(const char *tail, const char **next)
{
	char *p;

	if (tail == NULL) 
		return NULL;

	strcpy(str_buf, tail);
	p = str_buf;

	while (*tail != ' ' && *tail != 0) {
		tail++; p++; 
	}

	if (*tail == ' ') {
		*p = 0;
		while(*tail == ' ') 
			tail++;
	}

	if(next) 
		*next = (char *)(*tail ? tail : NULL);
	
	return str_buf;
}


static BOOL cmdExit(const char *tail)
{
	m_exit = TRUE;
	return TRUE;
}

static BOOL cmdHelp(const char *tail);


static struct cli_commandset default_cmdset[] = 
{
    { cmdHelp,  "help|?",	"[<command>]",	"Show commands or help on one command" },
	{ cmdExit,	"exit",		NULL,			"exit command line" },
    { NULL, NULL, NULL, NULL }
};

static BOOL match_cmd(const char *src, int start, int end, const char *des)
{
	while (src[start] == ' ' && start < end) 
		start++;

	while (src[end] == ' ' && start < end) 
		end--;
	
	if ((int)strlen(des) == (end - start + 1)) {
		if (memcmp(src + start, des, end - start + 1) == 0) {
			return TRUE;
		}
	}

	return FALSE;
}

static BOOL check_cmd(const char *cmds, const char *cmd)
{
	int start, end;

	for (start = end = 0; cmds[end] != 0 && cmds[end] != '|'; end++);

	while (end > start) {
		if (match_cmd(cmds, start, end - 1, cmd) == TRUE) 
			return TRUE;
		if (cmds[end] == 0) 
			break;
		if (cmds[end] == '|') {
			end++;
			for (start = end; cmds[end] != 0 && cmds[end] != '|'; end++);
		}
	} 

	return FALSE;
}

static int cmdFind(const char *cmd)
{
    int icmd;

    for (icmd = 0; cmdset[icmd].cmd != NULL; icmd++) {
		//printf("cmdFind: Check cmd: %s with %s\n", cmd, cmdset[icmd].cmd);
        if (check_cmd(cmdset[icmd].cmd, cmd) == TRUE)
			return icmd;
    }
    return -1;
}


static BOOL cmdHelp(const char *tail)
{
    int icmd;

    if (tail == NULL)  {
        printf("Available commands:\n");
        for (icmd = 0; cmdset[icmd].cmd != NULL; icmd++) {
            int i;
            printf("%s", cmdset[icmd].cmd);
            for (i = strlen(cmdset[icmd].cmd); i%10; i++,printf(" "));

            //if ((icmd & 7) == 7 || cmdset[icmd+1].cmd == NULL) printf("\n");
        }
		printf("\n");
    }
    else {
        icmd = cmdFind(tail);
        if (icmd < 0) {
            printf("No such command\n");
        }
        else {
            printf("%s: %s\n", cmdset[icmd].cmd, cmdset[icmd].descr);
            printf("Usage: %s %s\n", cmdset[icmd].cmd, cmdset[icmd].args);
        }
    }

    return TRUE;
}


void cliInterpret(const char *line)
{
    char cmd[64];
    const char *tail;
    const char *psep;
    int icmd;

    psep = strchr(line, ' ');
    cmd[0] = 0;

    if (psep == NULL) {
        strncat(cmd, line, sizeof(cmd) - 1);
        tail = NULL;
    }
    else {
        strncat(cmd, line, psep - line);
        for (tail = psep; *tail == ' '; ++tail);
        if (*tail == 0) 
			tail = NULL;
    }

    icmd = cmdFind(cmd);

    if (icmd < 0) {
        printf("Unknown command - try help\n");
        return;
    }
    else {
		//printf("Command idx: %d\n", icmd);
        if (!cmdset[icmd].handler(tail)) {
            cmdHelp(cmd);
        }
    }
}

void cli_add_commandset(struct cli_commandset *cmds)
{
    int icmd;

    for (icmd = 0; cmds[icmd].cmd != NULL; icmd++) {
        memcpy(&(cmdset[m_cmdCount++]), &(cmds[icmd]), sizeof(struct cli_commandset));
    }
}

void cliMain()
{
    char line[80];
    int linelen = 0;

	printf("$ ");
	cli_add_commandset(default_cmdset);

    while (!m_exit) {
        char ch;
		ch = getc(stdin);
        switch (ch) {
        case 8:
        case 127:
            if (linelen > 0) {
                --linelen;
                printf("\x08 \x08");
            }
            break;

        case '\r':
		case '\n':
            //printf("\r\n");
            if (linelen > 0) {
                line[linelen] = 0;
                cliInterpret(line);
            }
            linelen = 0;
			printf("$ ");
            break;

        case 21:
            while (linelen > 0) {
                --linelen;
                printf("\x08 \x08");
            }
            break;

        default:
            if (ch >= ' ' && ch < 127 && linelen < sizeof(line) - 1) {
                line[linelen++] = ch;
                //printf("%c", ch);
            }
        }
    }
}
