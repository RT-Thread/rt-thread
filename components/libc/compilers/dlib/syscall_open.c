/*
* File      : syscall_open.c
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
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
* 2015-01-28     Bernard      first version
*/

#include <rtthread.h>
#include <yfuns.h>
#ifdef RT_USING_DFS
#include <dfs_posix.h>
#endif

#pragma module_name = "?__open"

int __open(const char *filename, int mode)
{
#ifndef RT_USING_DFS
  return _LLIO_ERROR;
#else
  int handle;
  int open_mode = O_RDONLY;

  if (mode & _LLIO_CREAT)
  {
    open_mode |= O_CREAT;

    /* Check what we should do with it if it exists. */
    if (mode & _LLIO_APPEND)
    {
      /* Append to the existing file. */
      open_mode |= O_APPEND;
    }

    if (mode & _LLIO_TRUNC)
    {
      /* Truncate the existsing file. */
      open_mode |= O_TRUNC;
    }
  }

  if (mode & _LLIO_TEXT)
  {
    /* we didn't support text mode */
  }

  switch (mode & _LLIO_RDWRMASK)
  {
  case _LLIO_RDONLY:
    break;

  case _LLIO_WRONLY:
    open_mode |= O_WRONLY;
    break;

  case _LLIO_RDWR:
    /* The file should be opened for both reads and writes. */
    open_mode |= O_RDWR;
    break;

  default:
    return _LLIO_ERROR;
  }

  handle = open(filename, open_mode, 0);
  if (handle < 0)
    return _LLIO_ERROR;

  return handle;
#endif
}
