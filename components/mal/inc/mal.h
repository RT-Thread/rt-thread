/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-26     liukang      the first version
 */

#ifndef __MAL_H__
#define __MAL_H__

#include <rthw.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MAL version information */
#define RT_MAL_VERSION                      1L              /**< major version number */
#define RT_MAL_SUBVERSION                   0L              /**< minor version number */
#define RT_MAL_REVISION                     0L              /**< revise version number */

#ifndef RT_MPU_ALIGN_SMALLEST_SIZE
#define RT_MPU_ALIGN_SMALLEST_SIZE     32                   /* mpu region smallest size */
#endif

#ifndef RT_MPU_THREAD_PROTECT_SIZE
#define RT_MPU_THREAD_PROTECT_SIZE     32
#endif

/* region attribute 
--------------------------------------------
32 31 30 29 28 27 26 25 24 23 22 21 20 19 18
|                   Reserved           
--------------------------------------------
17 16 15 14 13 12 11 10          9          8          7 6 5 4        3 2 1 0
                     |bufferable |cacheable |shareable |tex  |execute |permission
--------------------------------------------
*/
#define REGION_PERMISSION_Pos          0U                               /* Data access permissions, allows you to configure read/write access for User and Privileged mode */
#define REGION_PERMISSION_Msk          (0x7U << REGION_PERMISSION_Pos)

#define REGION_EXECUTE_Pos             4U                               /* Instruction access disable bit */
#define REGION_EXECUTE_Msk             (0x1U << REGION_EXECUTE_Pos)

#define REGION_TEX_Pos                 5U                               /* Type extension field */
#define REGION_TEX_Msk                 (0x7U << REGION_TEX_Pos)

#define REGION_SHAREABLE_Pos           8U                               /* Region is shareable between multiple bus masters */
#define REGION_SHAREABLE_Msk           (0x1U << REGION_SHAREABLE_Pos)

#define REGION_CACHEABLE_Pos           9U                               /* Region is cacheable */
#define REGION_CACHEABLE_Msk           (0x1U << REGION_CACHEABLE_Pos)

#define REGION_BUFFERABLE_Pos          10U                               /* Region is bufferable */
#define REGION_BUFFERABLE_Msk          (0x1U << REGION_BUFFERABLE_Pos)

/* access */
#define RT_MPU_REGION_NO_ACCESS                          0x0U
#define RT_MPU_REGION_PRIVILEGED_RW                      0x1U
#define RT_MPU_REGION_PRIVILEGED_RW_UNPRIV_RO            0x2U
#define RT_MPU_REGION_RW                                 0x3U
#define RT_MPU_REGION_PRIVILEGED_RO                      0x5U
#define RT_MPU_REGION_RO                                 0x6U

/* execute */
#define RT_MPU_REGION_EXECUTE_ENABLE                     0x0U
#define RT_MPU_REGION_EXECUTE_DISABLE                    0x1U

/* shareable */
#define RT_MPU_REGION_SHAREABLE_ENABLE                   0x1U
#define RT_MPU_REGION_SHAREABLE_DISABLE                  0x0U

/* cacheable */
#define RT_MPU_REGION_CACHEABLE_ENABLE                   0x1U
#define RT_MPU_REGION_CACHEABLE_DISABLE                  0x0U

/* bufferable */
#define RT_MPU_REGION_BUFFERABLE_ENABLE                  0x1U
#define RT_MPU_REGION_BUFFERABLE_DISABLE                 0x0U

/* type_extern */
#define RT_MPU_REGION_TEX_ENABLE                         0x1U
#define RT_MPU_REGION_TEX_DISABLE                        0x0U


#define RT_MPU_REGION_INVALID                            0x0U
#define RT_MPU_REGION_VALID                              0x1U

#ifndef RT_MPU_HW_USED_REGIONS
#define RT_MPU_HW_USED_REGIONS                           0x0U
#endif

#ifdef  RT_MPU_USING_THREAD_STACK_PROTECT
#define RT_MPU_THREAD_STACK_REGION                       (RT_MPU_HW_USED_REGIONS)             /* Thread stack region  */
#define RT_MPU_FIRST_CONFIGURABLE_REGION                 (RT_MPU_THREAD_STACK_REGION + 1)     /* User can configurable first region number */
#else
#define RT_MPU_FIRST_CONFIGURABLE_REGION                 (RT_MPU_HW_USED_REGIONS + 1)          /* User can configurable first region number */
#endif

#define RT_MPU_FIRST_PROTECT_AREA_REGION   (RT_MPU_REGIONS_NUMBER - RT_MPU_HW_USED_REGIONS)
#define RT_MPU_NUM_CONFIGURABLE_REGION     (RT_MPU_REGIONS_NUMBER - RT_MPU_FIRST_CONFIGURABLE_REGION - RT_MPU_HW_USED_REGIONS) /* number of regions that can be configured */
#define RT_MPU_LAST_CONFIGURABLE_REGION    (RT_MPU_REGIONS_NUMBER - RT_MPU_HW_USED_REGIONS - 1)

struct mpu_regions
{
    rt_uint32_t addr;
    rt_uint32_t size;
    rt_uint32_t attribute;
};

struct mpu_protect_regions
{
    rt_thread_t thread;
    struct rt_mal_region tables;
};

struct rt_mpu_ops
{
   rt_err_t (*init) (struct rt_mal_region *regions);
   void (*switch_table) (rt_thread_t thread, rt_uint8_t mpu_protect_area_num, struct mpu_protect_regions* mpu_protect_areas);
   rt_err_t (*get_info) (rt_thread_t thread, rt_uint32_t type, void *arg);
};

enum mpu_info_type {
    GET_MPU_REGIONS_NUMBER = 0,
    GET_MPU_REGIONS_CONFGIG,
};

/**
* MPU Region Attribute
* \param access             Data access permissions, allows you to configure read/write access for User and Privileged mode.
* \param execute            Instruction access disable bit, 1= disable instruction fetches.
* \param shareable          Region is shareable between multiple bus masters.
* \param cacheable          Region is cacheable, i.e. its value may be kept in cache.
* \param bufferable         Region is bufferable, i.e. using write-back caching. Cacheable but non-bufferable regions use write-through policy.
* \param type_extern        Type extension field, allows you to configure memory access type, for example strongly ordered, peripheral.
*/ 
rt_inline rt_uint32_t rt_mpu_region_attribute(rt_uint32_t access,
                                            rt_uint32_t execute,
                                            rt_uint32_t shareable,
                                            rt_uint32_t cacheable,
                                            rt_uint32_t bufferable,
                                            rt_uint32_t type_extern)
{
    rt_uint32_t attribute = 0;

    attribute = (((access     << REGION_PERMISSION_Pos)  & REGION_PERMISSION_Msk) | \
                ((execute     << REGION_EXECUTE_Pos)     & REGION_EXECUTE_Msk)    | \
                ((type_extern << REGION_TEX_Pos )        & REGION_TEX_Msk)        | \
                ((shareable   << REGION_SHAREABLE_Pos )  & REGION_SHAREABLE_Msk)  | \
                ((cacheable   << REGION_CACHEABLE_Pos )  & REGION_CACHEABLE_Msk)  | \
                ((bufferable  << REGION_BUFFERABLE_Pos ) & REGION_BUFFERABLE_Msk));

    return attribute;
};

/* Extern Fucntion */
rt_err_t rt_mpu_init(struct rt_mal_region *tables);
rt_err_t rt_mpu_attach(rt_thread_t thread, void* addr, size_t size, rt_uint32_t attribute);
rt_err_t rt_mpu_attach_table(rt_thread_t thread, struct mpu_regions *regions);
rt_err_t rt_mpu_delete(rt_thread_t thread, rt_uint8_t region);
rt_err_t rt_mpu_refresh(rt_thread_t thread, void *addr, size_t size, rt_uint32_t attribute, rt_uint8_t region);
rt_err_t rt_mpu_insert(rt_thread_t thread, void *addr, size_t size, rt_uint32_t attribute, rt_uint8_t region);
rt_err_t rt_mpu_get_info(rt_thread_t thread, rt_uint32_t type, void *arg);
rt_err_t rt_mpu_enable_protect_area(rt_thread_t thread, void *addr, size_t size, rt_uint32_t attribute);
rt_err_t rt_mpu_disable_protect_area(rt_thread_t thread, rt_uint8_t region);
void rt_mpu_table_switch(rt_thread_t thread);
rt_err_t rt_mpu_ops_register(struct rt_mpu_ops *ops);

void rt_mpu_exception_sethook(rt_thread_t thread, rt_err_t (*hook)(void* addr, rt_uint32_t attribute));
rt_err_t rt_mpu_exception_handler(rt_thread_t thread, void* addr, rt_uint32_t attribute);

#ifdef __cplusplus
}
#endif

#endif /* __MAL_H__ */
