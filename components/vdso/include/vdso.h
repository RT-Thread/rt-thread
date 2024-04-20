#ifndef _VDSO_H
#define _VDSO_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#include <lwp.h>
#include <vdso_datapage.h>

#define VDSO_DATAPAGE __attribute__((section(".data.vdso.datapage")))///< vdso分页数据区

extern char __vdso_data_start[];	///< 数据区起始地址 __vdso_data_start < __vdso_text_start
extern char __vdso_text_start[];	///< 代码区起始地址
extern char __vdso_text_end[];	///< 代码区结束地址

#define ELF_HEAD "\177ELF" ///< ELF格式头
#define ELF_HEAD_LEN 4	///< 头长度4个字节
#define MAX_PAGES 5

int arch_setup_additional_pages(struct rt_lwp *lwp);
void rt_vdso_time_val_update(void);
void rt_vdso_timeget(VdsoDataPage *vdsoDataPage);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _VDSO_H */
