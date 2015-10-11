/*
 *  script for RT-Thread module shell
 *
 * COPYRIGHT (C) 2013-2015, Shanghai Real-Thread Technology Co., Ltd
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-09-25     Bernard      the first verion for FinSH
 */

#include <rtthread.h>
#include <finsh.h>

#include "msh.h"

#if defined(FINSH_USING_MSH) && defined(RT_USING_DFS)
#include <dfs_posix.h>

static int msh_readline(int fd, char *line_buf, int size)
{
    char ch;
    int index = 0;

    do
    {
        if (read(fd, &ch, 1) != 1)
        {
            /* nothing in this file */
            return 0;
        }
    }
    while (ch == '\n' || ch == '\r');

    /* set the first character */
    line_buf[index ++] = ch;

    while (index < size)
    {
        if (read(fd, &ch, 1) == 1)
        {
            if (ch == '\n' || ch == '\r')
            {
                line_buf[index] = '\0';
                break;
            }

            line_buf[index++] = ch;
        }
        else
        {
            line_buf[index] = '\0';
            break;
        }
    }

    return index;
}

int msh_exec_script(const char *cmd_line, int size)
{
    int ret;
    int fd = -1;
    char *pg_name;
    int length, cmd_length = 0;

    if (size == 0) return -RT_ERROR;

    /* get the length of command0 */
    while ((cmd_line[cmd_length] != ' ' && cmd_line[cmd_length] != '\t') && cmd_length < size)
        cmd_length ++;

    /* get name length */
    length = cmd_length + 32;

    /* allocate program name memory */
    pg_name = (char *) rt_malloc(length);
    if (pg_name == RT_NULL) return -RT_ENOMEM;

    /* copy command0 */
    memcpy(pg_name, cmd_line, cmd_length);
    pg_name[cmd_length] = '\0';

    if (strstr(pg_name, ".sh") != RT_NULL || strstr(pg_name, ".SH") != RT_NULL)
    {
        /* try to open program */
        fd = open(pg_name, O_RDONLY, 0);

        /* search in /bin path */
        if (fd < 0)
        {
            rt_snprintf(pg_name, length - 1, "/bin/%.*s", cmd_length, cmd_line);
            fd = open(pg_name, O_RDONLY, 0);
        }
    }

    rt_free(pg_name);
    if (fd >= 0)
    {
        /* found script */
        char *line_buf;
        int length;

        line_buf = (char *) rt_malloc(RT_CONSOLEBUF_SIZE);

        /* read line by line and then exec it */
        do
        {
            length = msh_readline(fd, line_buf, RT_CONSOLEBUF_SIZE);
            if (length > 0)
            {
                char ch = '\0';
                int index;

                for (index = 0; index < length; index ++)
                {
                    ch = line_buf[index];
                    if (ch == ' ' || ch == '\t') continue;
                    else break;
                }

                if (ch != '#') /* not a comment */
                    msh_exec(line_buf, length);
            }
        }
        while (length > 0);

        close(fd);
        rt_free(line_buf);

        ret = 0;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

#endif
