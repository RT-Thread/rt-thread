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
 * \file uffs_debug.c
 * \brief output debug messages
 * \author Ricky Zheng, created 10th May, 2005
 */
#include "uffs/uffs_public.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#if !defined(_UBASE_)
#define ENABLE_DEBUG
//#define OUTPUT_TOFILE
#endif

#if !defined(_UBASE_)


#ifdef OUTPUT_TOFILE
#define DEBUG_LOGFILE	"log.txt"
#endif

void uffs_DebugMessage(int level, const char *prefix, const char *suffix, const char *errFmt, ...)
{

#ifdef ENABLE_DEBUG
	if (level >= UFFS_DBG_LEVEL) {

		char buf[1024] = {0};
		char *p;
		

#ifdef OUTPUT_TOFILE
		FILE *fp = NULL;	
#endif
		
		va_list arg;

		if (strlen(errFmt) > 800) {
			// dangerous!!
			rt_kprintf("uffs_Perror buffer is not enough !");
			return;
		}

		p = buf;

		if (prefix) {
			strcpy(p, prefix);
			p += strlen(prefix);
		}

		va_start(arg, errFmt);
		vsprintf(p, errFmt, arg);
		va_end(arg);

		if (suffix)
			strcat(p, suffix);

#ifdef OUTPUT_TOFILE
		fp = fopen(DEBUG_LOGFILE, "a+b");
		if (fp) {
			fwrite(buf, 1, strlen(buf), fp);
			fclose(fp);
		}
#else
		rt_kprintf("%s", buf);
#endif
	}
#endif //ENABLE_DEBUG
}

#else

#define ENABLE_DEBUG

#include <uBase.h>
#include <sys/debug.h>


void uffs_Perror( int level, const char *errFmt, ...)
{
#ifdef ENABLE_DEBUG
	va_list args;
	if (level >= UFFS_DBG_LEVEL) {
		va_start(args, errFmt);
		//uffs_vTrace(errFmt, args);
		dbg_simple_vprintf(errFmt, args);
		va_end(args);
	}
	dbg_simple_raw(TENDSTR);
#else
	level = level;
	errFmt = errFmt;
#endif //ENABLE_DEBUG
}

#endif

/**
 * \brief Called when an assert occurred.
 * This method is called when an assert occurred and should stop the
 * application from running, as this there is a severe error condition.
 * \param[in] file Source filename
 * \param[in] line Source line of code
 * \param[in] msg Assert message
 */
void uffs_AssertCall(const char *file, int line, const char *msg)
{
	rt_kprintf("ASSERT %s:%d - msg:%s\n", file, line, msg);
	while (1);
}
