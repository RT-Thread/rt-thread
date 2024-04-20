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


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _VDSO_DATAPAGE_H */