#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#define DEBUG(enable, tagged, ...) \
		do \
		{ \
			if (enable) \
			{ \
				if (tagged) \
					fprintf(stderr, "[ %25s() ] ", __func__); \
				fprintf(stderr, __VA_ARGS__); \
			} \
		} while( 0)

#define ERROR(...) DEBUG(1, 1, "ERROR:"__VA_ARGS__)

#define KASSERT(cond)						\
{										    \
	if (!(cond))                            \
	{								        \
		ERROR("Failed assertion in %s:\n"	\
				"%s at %s\n"				\
				"line %d\n"					\
				"RA=%lx\n",					\
				__func__,					\
				#cond,						\
				__FILE__,					\
				__LINE__,					\
				(unsigned long)__builtin_return_address(0));	\
		                                    \
		while (1)							\
			;							    \
	}									    \
}

#define KPANIC(args, ...)		\
{					            \
	ERROR(args, __VA_ARGS__);	\
	while (1) ;			        \
}

static inline void dump_mem(const void *mem, int count)
{
	const unsigned char *p = mem;
	int i = 0;

	for(i = 0; i < count; i++)
	{
		if( i % 16 == 0)
			DEBUG(1, 0, "\n");

		DEBUG(1, 0, "%02x ", p[i]);
	}
}

/* help to trace back */
static inline void dump_stack(void)
{
	unsigned long *stack;
	unsigned long addr;

	__asm__ __volatile__ ("\tori\t%0, $sp, #0\n" : "=r" (stack));

	printf("Call Trace:\n");
	addr = *stack;
	while (addr)
	{
		addr = *stack++;
		printf("[<%08lx>] ", addr);
	}		
	printf("\n");

	return;
}

#endif /* __DEBUG_H__ */
