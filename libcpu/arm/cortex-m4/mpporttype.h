#ifndef __MPPORTTYPE_H__
#define __MPPORTTYPE_H__

#ifdef RT_USING_MEM_PROTECTION

typedef struct {
	rt_uint32_t rasr;
} rt_mem_attr_t;

#endif /* RT_USING_MEM_PROTECTION */

#endif /* __MPPORTTYPE_H__ */
