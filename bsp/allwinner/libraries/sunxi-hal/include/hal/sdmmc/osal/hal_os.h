/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _DRIVER_CHIP_HAL_OS_H_
#define _DRIVER_CHIP_HAL_OS_H_

#include "os.h"
#include <string.h>
#include <stdlib.h>
#include <hal_atomic.h>
#ifndef CONFIG_KERNEL_FREERTOS
#include <ktimer.h>
#include <hal_cfg.h>
#else
#include <hal_cache.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* IRQ disable/enable */
#define HAL_DisableIRQ()    arch_irq_disable()
#define HAL_EnableIRQ()     arch_irq_enable()

/* Check if IRQ is disabled */
#define HAL_IsIRQDisabled() __get_PRIMASK()

/* Check if in ISR context or not */
#define HAL_IsISRContext()  __get_IPSR()

extern hal_spinlock_t sdmmc_lock;
/* Critical Sections */
//#define HAL_EnterCriticalSection()      arch_irq_save()
//#define HAL_ExitCriticalSection(flags)  arch_irq_restore(flags)
#define HAL_EnterCriticalSection()  ({hal_spin_lock_irqsave(&sdmmc_lock);})
#define HAL_ExitCriticalSection(f)  ({hal_spin_unlock_irqrestore(&sdmmc_lock, f);})
#define HAL_ATMOTIC_SET(a,v)            ({int flags = HAL_EnterCriticalSection();\
                                        a = v;HAL_ExitCriticalSection(flags);})
#define HAL_ATMOTIC_READ(a)         ({int flags=0;int v=0; flags = HAL_EnterCriticalSection();v=a;HAL_ExitCriticalSection(flags);v;})

#define HAL_FlushDcacheRegion(s,len)            (hal_dcache_clean_invalidate(s,len))
#define HAL_InvalidDcacheRegion(s,len)      (hal_dcache_invalidate(s, len))

#if 0
#define HAL_GetTimeMs()             (aos_now_ms())
#define HAL_GetTimeUs()             (aos_now()/1000)
//#define HAL_GetTimeUs()           (OS_GetTime()*1000)
#define HAL_GetTimeNs()             (aos_now())
#else
#if 0
#define HAL_GetTimeMs()             ((rt_tick_get()*1000)/CONFIG_HZ)
#define HAL_GetTimeUs()             ((rt_tick_get()*1000*1000)/CONFIG_HZ)
#define HAL_GetTimeNs()             ((rt_tick_get()*1000*1000)/CONFIG_HZ)
#endif
#define HAL_GetTimeMs()             ({\
                            struct timeval tv;\
                            gettimeofday(&tv, NULL);\
                            (tv.tv_usec + tv.tv_sec * 1000000ll)/1000;\
                        })
#define HAL_GetTimeUs()             ({\
                            struct timeval tv;\
                            gettimeofday(&tv, NULL);\
                            (tv.tv_usec + tv.tv_sec * 1000000ll);\
                        })
#define HAL_GetTimeNs()             ({\
                            struct timespec64  sdmmc_timeval;\
                            do_gettimeofday(&sdmmc_timeval);\
                            (sdmmc_timeval.tv_sec*1000ll*1000*1000ll + sdmmc_timeval.tv_nsec);\
                        })
#endif



/* Semaphore */
typedef OS_Semaphore_t HAL_Semaphore;

#define HAL_SemaphoreInit(sem, initCount, maxCount) \
    (OS_SemaphoreCreate(sem, initCount, maxCount) == OS_OK ? HAL_OK : HAL_ERROR)

#define HAL_SemaphoreInitBinary(sem) \
    (OS_SemaphoreCreateBinary(sem) == OS_OK ? HAL_OK : HAL_ERROR)

#define HAL_SemaphoreDeinit(sem) \
    (OS_SemaphoreDelete(sem) == OS_OK ? HAL_OK : HAL_ERROR)

#define HAL_SemaphoreWait(sem, msec) \
    (OS_SemaphoreWait(sem, msec) == OS_OK ? HAL_OK : HAL_ERROR)

#define HAL_SemaphoreRelease(sem) \
    (OS_SemaphoreRelease(sem) == OS_OK ? HAL_OK : HAL_ERROR)

#define HAL_SemaphoreIsValid(sem) \
    OS_SemaphoreIsValid(sem)

#define HAL_SemaphoreSetInvalid(sem) \
    OS_SemaphoreSetInvalid(sem)

/* Mutex */
typedef OS_Mutex_t HAL_Mutex;

#define HAL_MutexInit(mtx) \
    (OS_RecursiveMutexCreate(mtx) == OS_OK ? HAL_OK : HAL_ERROR)

#define HAL_MutexDeinit(mtx) \
    (OS_RecursiveMutexDelete(mtx) == OS_OK ? HAL_OK : HAL_ERROR)

#define HAL_MutexLock(mtx, msec) \
    (OS_RecursiveMutexLock(mtx, msec) == OS_OK ? HAL_OK : HAL_ERROR)

#define HAL_MutexUnlock(mtx) \
    (OS_RecursiveMutexUnlock(mtx) == OS_OK ? HAL_OK : HAL_ERROR)

/* Thread */
#define HAL_ThreadSuspendScheduler()    OS_ThreadSuspendScheduler()
#define HAL_ThreadResumeScheduler()     OS_ThreadResumeScheduler()
#define HAL_ThreadIsSchedulerRunning()  OS_ThreadIsSchedulerRunning()
#define HAL_ThreadEnd(s)                (HAL_ATMOTIC_SET(s,0))
#define HAL_ThreadStop(s)               (HAL_ATMOTIC_SET(s,1))
#define HAL_Thread_Should_Stop(s)       (HAL_ATMOTIC_READ(s))
#define HAL_ThreadDelete(w)         (OS_ThreadDelete(NULL))


/* Keep system alive, eg. feed watchdog */
#define HAL_Alive()             HAL_WDG_Feed()

/* Time */
#define HAL_Ticks()             OS_GetTicks()
#define HAL_MSleep(msec)        OS_MSleep(msec)
#define HAL_UDelay(us)          OS_Udelay(us)

#define HAL_SecsToTicks(sec)    OS_SecsToTicks(sec)
#define HAL_MSecsToTicks(msec)  OS_MSecsToTicks(msec)
#define HAL_TicksToMSecs(t)     OS_TicksToMSecs(t)
#define HAL_TicksToSecs(t)      OS_TicksToSecs(t)

#define HAL_TimeAfter(a, b)         OS_TimeAfter(a, b)
#define HAL_TimeBefore(a, b)        OS_TimeBefore(a, b)
#define HAL_TimeAfterEqual(a, b)    OS_TimeAfterEqual(a, b)
#define HAL_TimeBeforeEqual(a, b)   OS_TimeBeforeEqual(a, b)

#define HAL_ALIGN(x, a) __ALIGN_KERNEL((x), (a))
#define ALIGN_DOWN(x, a) __ALIGN_KERNEL((x) - ((a)-1), (a))
#define __ALIGN_KERNEL(x, a) __ALIGN_KERNEL_MASK(x, (typeof(x))(a)-1)
#define __ALIGN_KERNEL_MASK(x, mask) (((x) + (mask)) & ~(mask))

#define OS_CACHE_ALIGN_BYTES  (64)

static inline void *malloc_align_buf(size_t size)
{
    void *fake_ptr = NULL;
    void *malloc_ptr = NULL;

    /*malloc_ptr = krhino_mm_alloc(size + OS_CACHE_ALIGN_BYTES);*/
    malloc_ptr = hal_malloc(size + OS_CACHE_ALIGN_BYTES);
    if (HAL_PT_TO_U(malloc_ptr) & 0x3) {
        printf("error: krhino_mm_alloc not align to 4 byte\r\n");
    }
    fake_ptr = (void *)(HAL_PT_TO_U(malloc_ptr + OS_CACHE_ALIGN_BYTES) & (~(OS_CACHE_ALIGN_BYTES -1)));
    *(uint32_t *)((uint32_t *)fake_ptr - 1) = HAL_PT_TO_U(malloc_ptr);

    return fake_ptr;
}

static inline void free_align_buf(void *addr)
{
    void *malloc_ptr = NULL;
    if (!addr)
        return;
    malloc_ptr = (void *)HAL_PT_TO_U(*(uint32_t *)((uint32_t *)addr - 1));
    /*krhino_mm_free(malloc_ptr);*/
    hal_free(malloc_ptr);
}


/* Memory */
#define HAL_Malloc(l)           malloc(l)
#define HAL_Free(p)             free(p)
#define HAL_Memcpy(d, s, l)     memcpy(d, s, l)
#define HAL_Memset(d, c, l)     memset(d, c, l)
#define HAL_Memcmp(a, b, l)     memcmp(a, b, l)
#define HAL_Memmove(d, s, n)    memmove(d, s, n)
#define HAL_MallocAlign(l)      (malloc_align_buf(l))
#define HAL_FreeAlign(p)        (free_align_buf(p))
#ifndef CONFIG_KERNEL_FREERTOS
#define HAL_SetPin
#endif


#ifdef __cplusplus
}
#endif

#endif /* _DRIVER_CHIP_HAL_OS_H_ */
