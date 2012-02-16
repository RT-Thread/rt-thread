#ifndef __ASM_PAGE_H__
#define __ASM_PAGE_H__

//#include <pkgconf/linux_compat.h>  //mod by prife
#include "jffs2_config.h"
#define PAGE_SHIFT  CONFIG_JFFS2_PAGE_SHIFT
/* These aren't used by much yet. If that changes, you might want
   to make them actually correct :) */
#define PAGE_SIZE  (0x1 << PAGE_SHIFT)


#endif /* __ASM_PAGE_H__ */
