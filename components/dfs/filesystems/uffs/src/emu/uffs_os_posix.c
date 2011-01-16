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
 * \file uffs_os_linux.c
 * \brief emulation on linux host
 * \author Ricky Zheng
 */
#include "uffs/uffs_os.h"
#include "uffs/uffs_public.h"
//#include <memory.h>
#include <stdlib.h>
#include <time.h>

#define PFX "linuxemu:"

int uffs_SemCreate(int n)
{
	//TODO: ... create semaphore, return semaphore handler (rather then return n) ...
	return n;
}

int uffs_SemWait(int sem)
{
	if (sem) {
		//TODO: ... wait semaphore available ...
	}
	return 0;
}

int uffs_SemSignal(int sem)
{
	if (sem) {
		//TODO: ... release semaphore ...
	}
	return 0;
}

int uffs_SemDelete(int sem)
{
	if (sem) {
		//TODO: ... delete semaphore ...
	}
	return 0;
}

int uffs_OSGetTaskId(void)
{
	//TODO: ... return current task ID ...
	return 0;
}


void uffs_CriticalEnter(void)
{
	//TODO: enter critical section (for example, disable IRQ?)
	return;
}

void uffs_CriticalExit(void)
{
	//TODO: exit from critical section (for example, enable IRQ?)
	return;
}

unsigned int uffs_GetCurDateTime(void)
{
	// FIXME: return system time, please modify this for your platform ! 
	//			or just return 0 if you don't care about file time.
	time_t tvalue;

	tvalue = 0;//time(NULL);
	
	return (unsigned int)tvalue;
}
