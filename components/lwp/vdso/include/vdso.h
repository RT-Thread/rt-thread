#ifndef _VDSO_H
#define _VDSO_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#include <lwp.h>
#include <mmu.h>
#include <vdso_datapage.h>

extern char __vdso_text_start[];
extern char __vdso_text_end[];

#define ELF_HEAD "\177ELF"
#define ELF_HEAD_LEN 4
#define MAX_PAGES 5

#define __page_aligned_data	__attribute__((section(".data.vdso.datapage"))) __attribute__((aligned(ARCH_PAGE_SIZE)))

int arch_setup_additional_pages(struct rt_lwp *lwp);
void rt_vdso_time_val_update(void);
void rt_vdso_timeget(VdsoDataPage *vdsoDataPage);
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _VDSO_H */
