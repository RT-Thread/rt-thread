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
 * \file uffs_os.c
 * \brief Emulation on win32 host
 * \author Ricky Zheng
 */

#include "uffs_config.h"
#include "uffs/uffs_os.h"
#include "uffs/uffs_public.h"
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>

#define PFX "os  : "

int uffs_SemCreate(OSSEM *sem)
{
	HANDLE mutex = CreateMutex( 
        NULL,		// default security attributes
        FALSE,		// initially not owned
        NULL);		// unnamed mutex

	if (mutex == NULL) {
		printf("Create mutex failed !\n");
		return -1;
	}
	else {
		*sem = (OSSEM)mutex;
	}

	return 0;
}

int uffs_SemWait(OSSEM sem)
{
	DWORD result;

	result =  WaitForSingleObject( 
            (HANDLE)sem,    // handle to mutex
            INFINITE);		// no time-out interval

	return result == WAIT_ABANDONED ? -1 : 0;
}

int uffs_SemSignal(OSSEM sem)
{
	return ReleaseMutex((HANDLE)sem) ? 0 : -1;
}

int uffs_SemDelete(OSSEM *sem)
{
	if (CloseHandle((HANDLE)(*sem))) {
		*sem = 0;
		return 0;
	}
	else
		return -1;
}

int uffs_OSGetTaskId(void)
{
	return 0;
}

unsigned int uffs_GetCurDateTime(void)
{
	// FIXME: return system time, please modify this for your platform ! 
	//			or just return 0 if you don't care about file time.
	time_t tvalue;

	tvalue = time(NULL);
	
	return (unsigned int)tvalue;
}

#if CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR > 0
static void * sys_malloc(struct uffs_DeviceSt *dev, unsigned int size)
{
	dev = dev;
	uffs_Perror(UFFS_MSG_NORMAL, "system memory alloc %d bytes", size);
	return malloc(size);
}

static URET sys_free(struct uffs_DeviceSt *dev, void *p)
{
	dev = dev;
	free(p);
	return U_SUCC;
}

void uffs_MemSetupSystemAllocator(uffs_MemAllocator *allocator)
{
	allocator->malloc = sys_malloc;
	allocator->free = sys_free;
}
#endif


/* debug message output throught 'printf' */
static void output_dbg_msg(const char *msg);
static struct uffs_DebugMsgOutputSt m_dbg_ops = {
	output_dbg_msg,
	NULL,
};

static void output_dbg_msg(const char *msg)
{
	printf("%s", msg);
}

void uffs_SetupDebugOutput(void)
{
	uffs_InitDebugMessageOutput(&m_dbg_ops, UFFS_MSG_NOISY);
}
