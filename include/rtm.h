#ifndef __RTM_H__
#define __RTM_H__

#include <rtdef.h>
#include <rtthread.h>

#ifdef RT_USING_MODULE
#define RTM_EXPORT(symbol)					 							\
const char __rtmsym_##symbol##_name[] = #symbol;					 	\
const struct rt_module_symtab __rtmsym_##symbol SECTION("RTMSymTab")= 	\
{								\
	(rt_uint32_t)&symbol,		\
	__rtmsym_##symbol##_name,	\
};

#else
#define RTM_EXPORT(symbol)	
#endif

struct rt_module_symtab
{
	rt_uint32_t addr;
	const char* name;
};

#endif
