/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2015  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
#ifndef COM_AS_INFRASTRUCTURE_INCLUDE_ASDEBUG_H_
#define COM_AS_INFRASTRUCTURE_INCLUDE_ASDEBUG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#if defined(__LINUX__) || defined(__WINDOWS__)
#include <sys/time.h>
#endif
#include "__debug.h"
/* ============================ [ MACROS    ] ====================================================== */
#ifdef CONFIG_ARCH_VEXPRESS
#define USE_DET
#define printf printk
#define asAssertErrorHook()
#endif
/* levels for log output */
#define AS_LOG_DEFAULT  1
#define AS_LOG_STDOUT  	AS_LOG_DEFAULT
#define AS_LOG_STDERR  	AS_LOG_DEFAULT
#define AS_LOG_ON       AS_LOG_DEFAULT
#define AS_LOG_ERROR    AS_LOG_DEFAULT
#define AS_LOG_OFF      0

/* debug/warning/error */
#define AS_LOG_TRACE_D AS_LOG_DEFAULT
#define AS_LOG_TRACE_W AS_LOG_DEFAULT
#define AS_LOG_TRACE_E AS_LOG_DEFAULT

#ifdef USE_DET
#if defined(__LINUX__) || defined(__WINDOWS__)
#define ASLOG(level,fmt,...) 								\
	do {													\
		if((AS_LOG_##level) >= AS_LOG_DEFAULT) {			\
			aslog(#level,fmt,##__VA_ARGS__);				\
		} 													\
	}while(0)

#define ASWARNING(fmt,...) 									\
	do {													\
			aslog("WARING",fmt,##__VA_ARGS__);				\
	}while(0)
#else
#define ASLOG(level,fmt,...) 								\
	do {													\
		if((AS_LOG_##level) >= AS_LOG_DEFAULT) {			\
			printf("%-16s:",#level);						\
			printf(fmt,##__VA_ARGS__);						\
		} 													\
	}while(0)

#define ASWARNING(fmt,...) 									\
	do {													\
			printf("%-16s:","WARNING");						\
			printf(fmt,##__VA_ARGS__);						\
	}while(0)
#endif

#define ASMEM(level,prefix,p,len)							\
	if((AS_LOG_##level) >= AS_LOG_DEFAULT) {				\
        asmem(#level " " prefix, p, len);					\
	}
#else	/* USE_DET */
#define ASLOG(level,fmt,...)
#define ASWARNING(fmt,...)
#define ASMEM(level,prefix,p,len)
#endif

#ifdef USE_DET
#define PRINTF(fmt,...) ASLOG(STDOUT,fmt,##__VA_ARGS__)
#if defined(__WINDOWS__) || defined(__LINUX__)
#define ASHEX(a)	ashex((unsigned long)(a))
#else
#define ASHEX(a) "hex-null"
#endif
#else
#define PRINTF(fmt,...)
#define ASHEX(a)	"hex-null"
#endif

#ifdef USE_DET
#define asAssert(e)  																					\
	do {																								\
		if(FALSE==(e))																					\
		{																								\
			ASLOG(STDERR,"assert error on condition(%s) at line %d of %s\n",#e, __LINE__, __FILE__);	\
			asAssertErrorHook();																		\
		}																								\
	}while(0)
#else
#define asAssert(e)
#endif

#ifdef AS_PERF_ENABLED
#if defined(__LINUX__) || defined(__WINDOWS__)
#define ASPERF_MEASURE_START() 						\
	{												\
		asperf_t asperf0,asperf1;					\
		asPerfSet(&asperf0)

#define ASPERF_MEASURE_STOP(infor) 					\
		asPerfSet(&asperf1);						\
		asPerfLog(&asperf0,&asperf1,infor);			\
	}
#else
#define ASPERF_MEASURE_START()
#define ASPERF_MEASURE_STOP(infor)
#endif
#else	/* AS_PERF_ENABLED */
#define ASPERF_MEASURE_START()
#define ASPERF_MEASURE_STOP(infor)
#endif
/*
 * Env Definition:
 * 0: program name
 * 1: OSEK NM Node ID
 * 2: remote gui websock uri:port, e.g "127.0.0.1:8080" or "null" to disable remote gui to use local SG.
 */

#if defined(__LINUX__) || defined(__WINDOWS__)
#define ASENVINIT(argc,argv) asEnvInit(argc,argv)
#define ASENV(index) asEnvGet(index)
#else
#define ASENVINIT(argc,argv)
#define ASENV(index)
#endif

#if defined(__LINUX__)
#define asCallStack() asPrintCallStack()
#else
#define asCallStack()
#endif

#define ASTRACE(module) ASLOG(TRACE_##module,"%s @line %d of %s\n",__func__,__LINE__,__FILE__)
/* ============================ [ TYPES     ] ====================================================== */
#if defined(__LINUX__) || defined(__WINDOWS__)
typedef struct timeval asperf_t;
#endif
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#ifndef CONFIG_ARCH_VEXPRESS
extern void  aslog(const char* module,const char* format,...);
extern void  asmem(const char* prefix,const void* address,size_t size);
extern char* ashex(unsigned long a);
extern char* aswho(void);
extern void  asAssertErrorHook(void);
#if defined(__LINUX__)
extern void  asPrintCallStack(void);
#endif
#if defined(__LINUX__) || defined(__WINDOWS__)
extern void asPerfSet(asperf_t *m);
extern void asPerfLog(asperf_t *m0,asperf_t *m1,char* infor);
extern void asEnvInit(int argc,char* argv[]);
extern char* asEnvGet(int index);
#endif
#endif	/* CONFIG_ARCH_VEXPRESS */
#endif /* COM_AS_INFRASTRUCTURE_INCLUDE_ASDEBUG_H_ */
