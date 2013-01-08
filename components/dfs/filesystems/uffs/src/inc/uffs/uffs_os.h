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

#ifndef _UFFS_OS_H_
#define _UFFS_OS_H_

#include <rtthread.h>
#define RT_THREAD
#if !defined(RT_THREAD)
#include <stdarg.h>
#endif

#ifdef __cplusplus
extern "C"{
#endif

#define UFFS_TASK_ID_NOT_EXIST	-1

typedef void * OSSEM;
#define OSSEM_NOT_INITED	(NULL)

#if !defined(RT_THREAD)
struct uffs_DebugMsgOutputSt {
	void (*output)(const char *msg);
	void (*vprintf)(const char *fmt, va_list args);
};

void uffs_SetupDebugOutput(void);
#endif

/* OS specific functions */
int uffs_SemCreate(OSSEM *sem);
int uffs_SemWait(OSSEM sem);
int uffs_SemSignal(OSSEM sem);
int uffs_SemDelete(OSSEM *sem);

int uffs_OSGetTaskId(void);	//get current task id
unsigned int uffs_GetCurDateTime(void);

#ifdef __cplusplus
}
#endif


#endif

