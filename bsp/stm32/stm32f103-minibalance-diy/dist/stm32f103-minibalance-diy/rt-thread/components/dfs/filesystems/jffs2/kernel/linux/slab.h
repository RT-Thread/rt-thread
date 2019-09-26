#ifndef __LINUX_SLAB_H__
#define __LINUX_SLAB_H__

//#include <stdlib.h>  //prife

#include <asm/page.h> /* Don't ask. Linux headers are a mess. */

#define kmalloc(x, y) rt_malloc(x)
#define kfree(x) rt_free(x)
#define vmalloc(x) rt_malloc(x)
#define vfree(x) rt_free(x)

#endif /* __LINUX_SLAB_H__ */

