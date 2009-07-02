/*****************************************************************************\
*                     EFSL - Embedded Filesystems Library                     *
*                     -----------------------------------                     *
*                                                                             *
* Filename : debug.c                                                          *
* Release  : 0.3 - devel                                                      *
* Description : These functions are used for debugging output on different    *
*               environments                                                  *
*                                                                             *
* This program is free software; you can redistribute it and/or               *
* modify it under the terms of the GNU General Public License                 *
* as published by the Free Software Foundation; version 2                     *
* of the License.                                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful,             *
* but WITHOUT ANY WARRANTY; without even the implied warranty of              *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
* GNU General Public License for more details.                                *
*                                                                             *
* As a special exception, if other files instantiate templates or             *
* use macros or inline functions from this file, or you compile this          *
* file and link it with other works to produce a work based on this file,     *
* this file does not by itself cause the resulting work to be covered         *
* by the GNU General Public License. However the source code for this         *
* file must still be made available in accordance with section (3) of         *
* the GNU General Public License.                                             *
*                                                                             *
* This exception does not invalidate any other reasons why a work based       *
* on this file might be covered by the GNU General Public License.            *
*                                                                             *
*                                                    (c)2006 Lennart Yseboodt *
*                                                    (c)2006 Michael De Nil   *
\*****************************************************************************/

/* COMMENT REGARDING FUNCTION COMMENTS IN THIS FILE
 * Only the linuxfile debug functions are commented since all functions
 * perform the same logical task.
*/

/*****************************************************************************/
#include "debug.h"
/*****************************************************************************/


/*****************************************************************************/
#ifdef DEBUG
#ifdef HW_ENDPOINT_LINUX_ALL
/*****************************************************************************/

/* ****************************************************************************  
 * void debug(const eint8 *format, ...)
 * Description: This function prints debug output to the screen (target dependant)
 * and if DO_FUNC_DEBUG is defined also to a localfile.
 * Return value: void
*/

void debug(const eint8 *format, ...)
{
	va_list ap;
	#ifdef DO_FUNC_DEBUG
	euint8 c;
	extern  FILE* debugfile;
	extern volatile euint8 tw;
	#endif
	
	va_start(ap, format);
	vprintf(format,ap);
	#ifdef DO_FUNC_DEBUG
		for(c=0;c<tw+1;c++)
		{
			fprintf(debugfile,"  ");
		}
		vfprintf(debugfile,format,ap);
	#endif
	va_end(ap);
}
/*****************************************************************************/

/* ****************************************************************************  
 * void debug_funcin(const eint8 *format, ...)
 * Description: This function marks the entrance of a function, which
 * increments a tabfieldcounter. A tree like structure can the be found in the
 * debugging file.
 * Return value: void
*/

void debug_funcin(const eint8 *format, ...)
{
	#ifdef DO_FUNC_DEBUG
	eint8 c;
	va_list ap;
	extern  FILE* debugfile;
	extern volatile unsigned char tw;
	
	if(debugfile==RT_NULL)return;
	
	for(c=0;c<tw;c++){
		fprintf(debugfile,"  ");
	}
	
	va_start(ap, format);
	vfprintf(debugfile,format,ap);
	va_end(ap);
	fprintf(debugfile,"\n");
	
	tw++;
	#endif
}
/*****************************************************************************/

/* ****************************************************************************  
 * void debug_funcout(const eint8 *format, ...)
 * Description: Decrements the tabfieldcounter. This function is called everywhere
 * a function is left.
 * Return value: void
*/

void debug_funcout(const eint8 *format, ...)
{
	#ifdef DO_FUNC_DEBUG
	eint8 c;
	va_list ap;
	extern  FILE* debugfile;
	extern volatile euint8 tw;
	
	if(debugfile==RT_NULL)return;
	
	if(tw>0)tw--;
	
	for(c=0;c<tw;c++){
		fprintf(debugfile,"  ");
	}
	
	va_start(ap, format);
	vfprintf(debugfile,format,ap);
	va_end(ap);
	fprintf(debugfile,"\n");
	#endif
}
/*****************************************************************************/

/* ****************************************************************************  
 * void debug_init()
 * Description: This function optionally opens the debugfile, or does any other
 * initialisation to enable debugoutput.
 * Return value: void
*/
void debug_init()
{
	#ifdef DO_FUNC_DEBUG
	extern  FILE* debugfile;
	extern volatile unsigned char tw;

	debugfile=RT_NULL;
	tw=0;
	
	debugfile=fopen("DBG.OUT","w");
	#endif
}
/*****************************************************************************/

/* ****************************************************************************  
 * void debug_end()
 * Description: This function closes the debugfile.
 * Return value: void
*/
void debug_end()
{
	#ifdef DO_FUNC_DEBUG
	extern  FILE* debugfile;
	
	fflush(debugfile);
	fclose(debugfile);
	#endif
}
/*****************************************************************************/

/*****************************************************************************/
#endif
#endif
/*****************************************************************************/

