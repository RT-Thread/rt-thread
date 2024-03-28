/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-18     Shell        Separate the basic types from rtdef.h
 */

#ifndef __RT_TYPES_H__
#define __RT_TYPES_H__

#include <rtconfig.h>

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#ifndef RT_USING_NANO
#include <sys/types.h>
#include <sys/errno.h>
#if defined(RT_USING_SIGNALS) || defined(RT_USING_SMART)
#include <sys/signal.h>
#endif /* defined(RT_USING_SIGNALS) || defined(RT_USING_SMART) */
#endif /* RT_USING_NANO */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * RT-Thread basic data types definition
 */

typedef int                             rt_bool_t;      /**< boolean type */
typedef signed long                     rt_base_t;      /**< Nbit CPU related date type */
typedef unsigned long                   rt_ubase_t;     /**< Nbit unsigned CPU related data type */

#ifndef RT_USING_ARCH_DATA_TYPE
#ifdef RT_USING_LIBC
typedef int8_t                          rt_int8_t;      /**<  8bit integer type */
typedef int16_t                         rt_int16_t;     /**< 16bit integer type */
typedef int32_t                         rt_int32_t;     /**< 32bit integer type */
typedef uint8_t                         rt_uint8_t;     /**<  8bit unsigned integer type */
typedef uint16_t                        rt_uint16_t;    /**< 16bit unsigned integer type */
typedef uint32_t                        rt_uint32_t;    /**< 32bit unsigned integer type */
typedef int64_t                         rt_int64_t;     /**< 64bit integer type */
typedef uint64_t                        rt_uint64_t;    /**< 64bit unsigned integer type */
#else
typedef signed   char                   rt_int8_t;      /**<  8bit integer type */
typedef signed   short                  rt_int16_t;     /**< 16bit integer type */
typedef signed   int                    rt_int32_t;     /**< 32bit integer type */
typedef unsigned char                   rt_uint8_t;     /**<  8bit unsigned integer type */
typedef unsigned short                  rt_uint16_t;    /**< 16bit unsigned integer type */
typedef unsigned int                    rt_uint32_t;    /**< 32bit unsigned integer type */
#ifdef ARCH_CPU_64BIT
typedef signed long                     rt_int64_t;     /**< 64bit integer type */
typedef unsigned long                   rt_uint64_t;    /**< 64bit unsigned integer type */
#else
typedef signed long long                rt_int64_t;     /**< 64bit integer type */
typedef unsigned long long              rt_uint64_t;    /**< 64bit unsigned integer type */
#endif /* ARCH_CPU_64BIT */
#endif /* RT_USING_LIBC */
#endif /* RT_USING_ARCH_DATA_TYPE */

#if defined(RT_USING_LIBC) && !defined(RT_USING_NANO)
typedef size_t                          rt_size_t;      /**< Type for size number */
typedef ssize_t                         rt_ssize_t;     /**< Used for a count of bytes or an error indication */
#else
typedef rt_ubase_t                      rt_size_t;      /**< Type for size number */
typedef rt_base_t                       rt_ssize_t;     /**< Used for a count of bytes or an error indication */
#endif /* defined(RT_USING_LIBC) && !defined(RT_USING_NANO) */

typedef rt_base_t                       rt_err_t;       /**< Type for error number */
typedef rt_uint32_t                     rt_time_t;      /**< Type for time stamp */
typedef rt_uint32_t                     rt_tick_t;      /**< Type for tick count */
typedef rt_base_t                       rt_flag_t;      /**< Type for flags */
typedef rt_ubase_t                      rt_dev_t;       /**< Type for device */
typedef rt_base_t                       rt_off_t;       /**< Type for offset */

#ifdef __cplusplus
typedef rt_ubase_t rt_atomic_t;
#else
#if defined(RT_USING_HW_ATOMIC)
typedef rt_ubase_t rt_atomic_t;
#elif defined(RT_USING_STDC_ATOMIC)
#include <stdatomic.h>
        typedef atomic_intptr_t rt_atomic_t;
#else
typedef rt_ubase_t rt_atomic_t;
#endif /* RT_USING_STDC_ATOMIC */
#endif /* __cplusplus */

/* boolean type definitions */
#define RT_TRUE                         1               /**< boolean true  */
#define RT_FALSE                        0               /**< boolean fails */

/* null pointer definition */
#define RT_NULL                         0

/**
 * Double List structure
 */
struct rt_list_node
{
    struct rt_list_node *next;                          /**< point to next node. */
    struct rt_list_node *prev;                          /**< point to prev node. */
};
typedef struct rt_list_node rt_list_t;                  /**< Type for lists. */

/**
 * Single List structure
 */
struct rt_slist_node
{
    struct rt_slist_node *next;                         /**< point to next node. */
};
typedef struct rt_slist_node rt_slist_t;                /**< Type for single list. */

/**
 * Spinlock
 */
#ifdef RT_USING_SMP
#include <cpuport.h> /* for spinlock from arch */

struct rt_spinlock
{
    rt_hw_spinlock_t lock;
#ifdef RT_USING_DEBUG
    rt_uint32_t critical_level;
#endif /* RT_USING_DEBUG */
#if defined(RT_DEBUGING_SPINLOCK)
    void *owner;
    void *pc;
#endif /* RT_DEBUGING_SPINLOCK */
};

#ifdef RT_DEBUGING_SPINLOCK

#define __OWNER_MAGIC ((void *)0xdeadbeaf)

#if defined(__GNUC__)
#define __GET_RETURN_ADDRESS __builtin_return_address(0)
#else
#define __GET_RETURN_ADDRESS RT_NULL
#endif

#define _SPIN_LOCK_DEBUG_OWNER(lock)                  \
    do                                                \
    {                                                 \
        struct rt_thread *_curthr = rt_thread_self(); \
        if (_curthr != RT_NULL)                       \
        {                                             \
            (lock)->owner = _curthr;                  \
            (lock)->pc = __GET_RETURN_ADDRESS;        \
        }                                             \
    } while (0)

#define _SPIN_UNLOCK_DEBUG_OWNER(lock) \
    do                                 \
    {                                  \
        (lock)->owner = __OWNER_MAGIC; \
        (lock)->pc = RT_NULL;          \
    } while (0)

#else

#define _SPIN_LOCK_DEBUG_OWNER(lock)
#define _SPIN_UNLOCK_DEBUG_OWNER(lock)
#endif

#ifdef RT_USING_DEBUG

#define _SPIN_LOCK_DEBUG_CRITICAL(lock)                   \
    do                                                    \
    {                                                     \
        struct rt_thread *_curthr = rt_thread_self();     \
        if (_curthr != RT_NULL)                           \
        {                                                 \
            (lock)->critical_level = rt_critical_level(); \
        }                                                 \
    } while (0)

#define _SPIN_UNLOCK_DEBUG_CRITICAL(lock, critical) \
    do                                              \
    {                                               \
        (critical) = (lock)->critical_level;        \
    } while (0)

#else

#define _SPIN_LOCK_DEBUG_CRITICAL(lock)
#define _SPIN_UNLOCK_DEBUG_CRITICAL(lock, critical) (critical = 0)
#endif /* RT_USING_DEBUG */

#define RT_SPIN_LOCK_DEBUG(lock)         \
    do                                   \
    {                                    \
        _SPIN_LOCK_DEBUG_OWNER(lock);    \
        _SPIN_LOCK_DEBUG_CRITICAL(lock); \
    } while (0)

#define RT_SPIN_UNLOCK_DEBUG(lock, critical)         \
    do                                               \
    {                                                \
        _SPIN_UNLOCK_DEBUG_OWNER(lock);              \
        _SPIN_UNLOCK_DEBUG_CRITICAL(lock, critical); \
    } while (0)

#ifndef RT_SPINLOCK_INIT
#define RT_SPINLOCK_INIT {{0}} /* can be overridden by cpuport.h */
#endif /* RT_SPINLOCK_INIT */

#else

struct rt_spinlock
{
#ifdef RT_USING_DEBUG
    rt_uint32_t critical_level;
#endif /* RT_USING_DEBUG */
    rt_ubase_t lock;
};
#define RT_SPINLOCK_INIT {0}
#endif /* RT_USING_SMP */

typedef struct rt_spinlock rt_spinlock_t;

#define RT_DEFINE_SPINLOCK(x)  struct rt_spinlock x = RT_SPINLOCK_INIT

#ifdef __cplusplus
}
#endif

#endif /* __RT_TYPES_H__ */
