/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
