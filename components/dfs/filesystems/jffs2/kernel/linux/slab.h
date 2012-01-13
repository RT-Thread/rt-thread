#ifndef __LINUX_SLAB_H__
#define __LINUX_SLAB_H__

#include <stdlib.h>  //prife

#include <asm/page.h> /* Don't ask. Linux headers are a mess. */

#define kmalloc(x, y) malloc(x)
#define kfree(x) free(x)
#define vmalloc(x) malloc(x)
#define vfree(x) free(x)

#endif /* __LINUX_SLAB_H__ */

