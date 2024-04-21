#ifndef _VDSO_DATAPAGE_H
#define _VDSO_DATAPAGE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

typedef struct {//Vdso数据页结构体
    /* Timeval */
    uint64_t realTimeSec; 	///< 单位秒: 系统实时时间
    uint64_t realTimeNsec; ///< 单位纳秒: 系统实时时间
    uint64_t monoTimeSec;	///< 系统运行时间，从系统启动时开始计时，速度更快精度更低
    uint64_t monoTimeNsec;	///< 
    /* lock DataPage  0:Unlock State  1:Lock State */
    uint64_t lockCount;///< 数据页被锁数量
} VdsoDataPage;


extern char __vdso_data_start[];	///< 数据区起始地址 __vdso_data_start < __vdso_text_start
static inline const  VdsoDataPage *__arch_get_vdso_data(void)
{
	const VdsoDataPage *ret;

	/*
	 * This simply puts &_vdso_data into ret. The reason why we don't use
	 * `ret = _vdso_data` is that the compiler tends to optimise this in a
	 * very suboptimal way: instead of keeping &_vdso_data in a register,
	 * it goes through a relocation almost every time _vdso_data must be
	 * accessed (even in subfunctions). This is both time and space
	 * consuming: each relocation uses a word in the code section, and it
	 * has to be loaded at runtime.
	 *
	 * This trick hides the assignment from the compiler. Since it cannot
	 * track where the pointer comes from, it will only use one relocation
	 * where __arch_get_vdso_data() is called, and then keep the result in
	 * a register.
	 */
	asm volatile("mov %0, %1" : "=r"(ret) : "r"(__vdso_data_start));

	return ret;
};

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _VDSO_DATAPAGE_H */