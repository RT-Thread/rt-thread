#ifndef XIL_CACHE_H
#define XIL_CACHE_H

#ifdef __cplusplus
extern "C" {
#endif

#define Xil_DCacheFlushRange(addr, size)  rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void*)(addr), (size))
#define Xil_DCacheInvalidateRange(addr, size)  rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void*)(addr), (size))

#ifdef __cplusplus
}
#endif

#endif
/**
* @} End of "addtogroup r5_cache_apis".
*/
