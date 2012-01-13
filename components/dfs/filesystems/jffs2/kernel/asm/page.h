#ifndef __ASM_PAGE_H__
#define __ASM_PAGE_H__

//#include <pkgconf/linux_compat.h>  //mod by prife
#define PAGE_SHIFT 12 // add by prife 4K
/* These aren't used by much yet. If that changes, you might want
   to make them actually correct :) */
#define PAGE_SIZE  (0x1 << PAGE_SHIFT)


#endif /* __ASM_PAGE_H__ */
