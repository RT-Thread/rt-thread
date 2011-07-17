/*
 * Copyright © Marvell International Ltd. and/or its affiliates, 2003-2006
 */

#ifndef _OS_HEADERS_H
#define _OS_HEADERS_H

#ifndef __ATTRIB_ALIGN__
#define __ATTRIB_ALIGN__ (__aligned(4))  //changed by dennis for compiler compatibility
#endif

#ifndef __ATTRIB_PACK__
//#define __ATTRIB_PACK__ __attribute__ ((packed))
//#define __ATTRIB_PACK__ 				 //changed by dennis for compiler compatibility
#endif

/* RT_Thread header files */
#include <rtconfig.h>
#include <rtthread.h>
#include <rtdef.h>
#include <stdio.h>
#include <string.h>

/* New Code to synchronize between IEEE Power save and PM*/
#ifdef ENABLE_PM

#endif

/* ASM files */


/* Net header files */


/* Wireless header */

#endif
