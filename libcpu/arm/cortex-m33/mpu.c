/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-25     tangzz98     the first version
 */

#include <rtdef.h>
#include <mprotect.h>

#define DBG_ENABLE
#define DBG_SECTION_NAME "MEMORY PROTECTION"
#define DBG_LEVEL DBG_ERROR
#include <rtdbg.h>

#define MEM_REGION_TO_MPU_INDEX(thread, region) ((((rt_size_t)region - (rt_size_t)(thread->mem_regions)) / sizeof(rt_mem_region_t)) + NUM_STATIC_REGIONS)

extern rt_mem_region_t *rt_mprotect_find_free_region(rt_thread_t thread);
extern rt_mem_region_t *rt_mprotect_find_region(rt_thread_t thread, rt_mem_region_t *region);

static rt_hw_mpu_exception_hook_t mem_manage_hook = RT_NULL;
static rt_uint8_t mpu_mair[8U];

rt_weak rt_uint8_t rt_hw_mpu_region_default_attr(rt_mem_region_t *region)
{
    static rt_uint8_t default_mem_attr[] =
    {
        ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(1U, 0U, 1U, 0U), ARM_MPU_ATTR_MEMORY_(1U, 0U, 1U, 0U)),
        ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(1U, 1U, 1U, 1U), ARM_MPU_ATTR_MEMORY_(1U, 1U, 1U, 1U)),
        ARM_MPU_ATTR_DEVICE_nGnRE,
        ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(1U, 1U, 1U, 1U), ARM_MPU_ATTR_MEMORY_(1U, 1U, 1U, 1U)),
        ARM_MPU_ATTR(ARM_MPU_ATTR_MEMORY_(1U, 0U, 1U, 0U), ARM_MPU_ATTR_MEMORY_(1U, 0U, 1U, 0U)),
        ARM_MPU_ATTR_DEVICE_nGnRE,
        ARM_MPU_ATTR_DEVICE_nGnRE
    };
    rt_uint8_t attr = 0U;
    if ((rt_uint32_t)region->start >= 0xE0000000U)
    {
        attr = ((rt_uint32_t)region->start >= 0xE0100000U) ? ARM_MPU_ATTR_DEVICE_nGnRE : ARM_MPU_ATTR_DEVICE_nGnRnE;
    }
    else
    {
        attr = default_mem_attr[((rt_uint32_t)region->start & ~0xFFFFFFFU) >> 29U];
    }
    return attr;
}

static rt_err_t _mpu_rbar_rlar(rt_mem_region_t *region)
{
    rt_uint32_t rlar = 0U;
    rt_uint8_t mair_attr;
    rt_uint8_t index;
    rt_uint8_t attr_indx = 0xFFU;
    region->attr.rbar = (rt_uint32_t)region->start | (region->attr.rbar & (~MPU_RBAR_BASE_Msk));
    rlar |= ((rt_uint32_t)region->start + region->size - 1U) & MPU_RLAR_LIMIT_Msk;
    if (region->attr.mair_attr == RT_ARM_DEFAULT_MAIR_ATTR)
    {
        mair_attr = rt_hw_mpu_region_default_attr(region);
    }
    else
    {
        mair_attr = (rt_uint8_t)region->attr.mair_attr;
    }
    for (index = 0U; index < 8U; index++)
    {
        if (mpu_mair[index] == RT_ARM_DEFAULT_MAIR_ATTR)
        {
            break;
        }
        else if (mpu_mair[index] == mair_attr)
        {
            attr_indx = index;
            break;
        }
    }
    /*
     * Current region's mair_attr does not match any existing region.
     * All entries in MPU_MAIR are configured.
     */
    if (index == 8U)
    {
        return RT_ERROR;
    }
    /* An existing region has the same mair_attr. */
    if (attr_indx != 0xFFU)
    {
        rlar |= attr_indx & MPU_RLAR_AttrIndx_Msk;
    }
    /* Current region's mair_attr does not match any existing region. */
    else
    {
        ARM_MPU_SetMemAttr(index, mair_attr);
        rlar |= index & MPU_RLAR_AttrIndx_Msk;
    }
    rlar |= MPU_RLAR_EN_Msk;
    region->attr.rlar = rlar;

    return RT_EOK;
}

rt_bool_t rt_hw_mpu_region_valid(rt_mem_region_t *region)
{
    if (region->size < MPU_MIN_REGION_SIZE)
    {
        LOG_E("Region size is too small");
        return RT_FALSE;
    }
    if (region->size & (~(MPU_MIN_REGION_SIZE - 1U)) != region->size)
    {
        LOG_E("Region size is not a multiple of 32 bytes");
        return RT_FALSE;
    }
    if ((rt_uint32_t)region->start & (MPU_MIN_REGION_SIZE - 1U) != 0U)
    {
        LOG_E("Region is not aligned by 32 bytes");
        return RT_FALSE;
    }
    return RT_TRUE;
}

rt_err_t rt_hw_mpu_init(void)
{
    extern rt_mem_region_t static_regions[NUM_STATIC_REGIONS];
    rt_uint8_t num_mpu_regions;
    rt_uint8_t num_dynamic_regions;
    rt_uint8_t index;
    num_mpu_regions = (rt_uint8_t)((MPU->TYPE & MPU_TYPE_DREGION_Msk) >> MPU_TYPE_DREGION_Pos);
    if (num_mpu_regions == 0U)
    {
        LOG_E("Hardware does not support MPU");
        return RT_ERROR;
    }
    if (num_mpu_regions != NUM_MEM_REGIONS)
    {
        LOG_E("Incorrect setting of NUM_MEM_REGIONS");
        LOG_E("NUM_MEM_REGIONS = %d, hardware support %d MPU regions", NUM_MEM_REGIONS, num_mpu_regions);
        return RT_ERROR;
    }

    num_dynamic_regions = NUM_DYNAMIC_REGIONS + NUM_EXCLUSIVE_REGIONS;
    if (num_dynamic_regions + NUM_STATIC_REGIONS > num_mpu_regions)
    {
        LOG_E("Insufficient MPU regions: %d hardware MPU regions", num_mpu_regions);
#ifdef RT_USING_HW_STACK_GUARD
        LOG_E("Current configuration requires %d static regions + %d configurable regions + %d exclusive regions + %d stack guard regions", NUM_STATIC_REGIONS, NUM_CONFIGURABLE_REGIONS, NUM_EXCLUSIVE_REGIONS, 1);
#else
        LOG_E("Current configuration requires %d static regions + %d configurable regions + %d exclusive regions", NUM_STATIC_REGIONS, NUM_CONFIGURABLE_REGIONS, NUM_EXCLUSIVE_REGIONS);
#endif
        return RT_ERROR;
    }
    for (index = 0U; index < 8U; index++)
    {
        mpu_mair[index] = RT_ARM_DEFAULT_MAIR_ATTR;
    }

    ARM_MPU_Disable();
    for (index = 0U; index < NUM_STATIC_REGIONS; index++)
    {
        if (rt_hw_mpu_region_valid(&(static_regions[index])) == RT_FALSE)
        {
            return RT_ERROR;
        }
        if (_mpu_rbar_rlar(&(static_regions[index])) == RT_ERROR)
        {
            LOG_E("Number of different mair_attr configurations exceeds 8");
            return RT_ERROR;
        }
        ARM_MPU_SetRegion(index, static_regions[index].attr.rbar, static_regions[index].attr.rlar);
    }
    /* Enable background region. */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);

    return RT_EOK;
}

rt_err_t rt_hw_mpu_add_region(rt_thread_t thread, rt_mem_region_t *region)
{
    rt_uint8_t index;
    rt_mem_region_t *free_region;
    if (rt_hw_mpu_region_valid(region) == RT_FALSE)
    {
        return RT_ERROR;
    }
    rt_enter_critical();
    if (_mpu_rbar_rlar(region) == RT_ERROR)
    {
        rt_exit_critical();
        LOG_E("Number of different mair_attr configurations exceeds 8");
        return RT_ERROR;
    }
    if (thread == RT_NULL)
    {
        rt_exit_critical();
        return RT_EOK;
    }
    free_region = rt_mprotect_find_free_region(thread);
    if (free_region == RT_NULL)
    {
        rt_exit_critical();
        LOG_E("Insufficient regions");
        return RT_ERROR;
    }
    rt_memcpy(free_region, region, sizeof(rt_mem_region_t));
    if (thread == rt_thread_self())
    {
        index = MEM_REGION_TO_MPU_INDEX(thread, free_region);
        ARM_MPU_SetRegion(index, region->attr.rbar, region->attr.rlar);
    }
    rt_exit_critical();
    return RT_EOK;
}

rt_err_t rt_hw_mpu_delete_region(rt_thread_t thread, rt_mem_region_t *region)
{
    rt_uint8_t index;
    rt_enter_critical();
    rt_mem_region_t *found_region = rt_mprotect_find_region(thread, region);
    if (found_region == RT_NULL)
    {
        rt_exit_critical();
        LOG_E("Region not found");
        return RT_ERROR;
    }
    rt_memset(found_region, 0, sizeof(rt_mem_region_t));
    if (thread == rt_thread_self())
    {
        index = MEM_REGION_TO_MPU_INDEX(thread, found_region);
        ARM_MPU_ClrRegion(index);
    }
    rt_exit_critical();
    return RT_EOK;
}

rt_err_t rt_hw_mpu_update_region(rt_thread_t thread, rt_mem_region_t *region)
{
    rt_uint8_t index;
    if (rt_hw_mpu_region_valid(region) == RT_FALSE)
    {
        return RT_ERROR;
    }
    rt_enter_critical();
    if (_mpu_rbar_rlar(region) == RT_ERROR)
    {
        rt_exit_critical();
        LOG_E("Number of different mair_attr configurations exceeds 8");
        return RT_ERROR;
    }
    rt_mem_region_t *old_region = rt_mprotect_find_region(thread, region);
    if (old_region == RT_NULL)
    {
        rt_exit_critical();
        LOG_E("Region not found");
        return RT_ERROR;
    }
    rt_memcpy(old_region, region, sizeof(rt_mem_region_t));
    if (thread == rt_thread_self())
    {
        index = MEM_REGION_TO_MPU_INDEX(thread, old_region);
        ARM_MPU_SetRegion(index, region->attr.rbar, region->attr.rlar);
    }
    rt_exit_critical();
    return RT_EOK;
}

rt_err_t rt_hw_mpu_exception_set_hook(rt_hw_mpu_exception_hook_t hook)
{
    mem_manage_hook = hook;
    return RT_EOK;
}

void rt_hw_mpu_table_switch(rt_thread_t thread)
{
    extern rt_mem_exclusive_region_t exclusive_regions[NUM_EXCLUSIVE_REGIONS];
    rt_uint8_t i;
    rt_uint8_t index = NUM_STATIC_REGIONS;
    if (thread->mem_regions != RT_NULL)
    {
        for (i = 0U; i < NUM_DYNAMIC_REGIONS; i++)
        {
            if (((rt_mem_region_t *)thread->mem_regions)[i].size != 0U)
            {
                ARM_MPU_SetRegion(index, ((rt_mem_region_t *)thread->mem_regions)[i].attr.rbar, ((rt_mem_region_t *)thread->mem_regions)[i].attr.rlar);
                index += 1U;
            }
        }
    }
    for (i = 0U; i < NUM_EXCLUSIVE_REGIONS; i++)
    {
        if ((exclusive_regions[i].owner != RT_NULL) && (exclusive_regions[i].owner != thread))
        {
            ARM_MPU_SetRegion(index, exclusive_regions[i].region.attr.rbar, exclusive_regions[i].region.attr.rlar);
            index += 1U;
        }
    }
    for ( ; index < NUM_MEM_REGIONS; index++)
    {
        ARM_MPU_ClrRegion(index);
    }
}

void MemManage_Handler(void)
{
    extern rt_mem_region_t static_regions[NUM_STATIC_REGIONS];
    extern rt_mem_exclusive_region_t exclusive_regions[NUM_EXCLUSIVE_REGIONS];
    rt_mem_exception_info_t info;
    rt_int8_t i;
    rt_memset(&info, 0, sizeof(rt_mem_exception_info_t));
    info.thread = rt_thread_self();
    if (SCB->CFSR & SCB_CFSR_MMARVALID_Msk)
    {
        info.addr = (void *)(SCB->MMFAR);
        for (i = NUM_EXCLUSIVE_REGIONS - 1; i >= 0; i--)
        {
        if ((exclusive_regions[i].owner != RT_NULL) && ((exclusive_regions[i].owner != rt_thread_self())) && ADDR_IN_REGION(info.addr, (rt_mem_region_t *)&(exclusive_regions[i])))
            {
                rt_memcpy(&(info.region), &(exclusive_regions[i]), sizeof(rt_mem_region_t));
                break;
            }
        }
        if (info.region.size == 0U)
        {
            if (info.thread->mem_regions != RT_NULL)
            {
                for (i = NUM_DYNAMIC_REGIONS - 1; i >= 0; i--)
                {
                    if ((((rt_mem_region_t *)info.thread->mem_regions)[i].size != 0U) && ADDR_IN_REGION(info.addr, &(((rt_mem_region_t *)info.thread->mem_regions)[i])))
                    {
                        rt_memcpy(&(info.region), &(((rt_mem_region_t *)info.thread->mem_regions)[i]), sizeof(rt_mem_region_t));
                        break;
                    }
                }
            }
            if (info.region.size == 0U)
            {
                for (i = NUM_STATIC_REGIONS - 1; i >= 0; i--)
                {
                    if (ADDR_IN_REGION(info.addr, &(static_regions[i])))
                    {
                        rt_memcpy(&(info.region), &(static_regions[i]), sizeof(rt_mem_region_t));
                        break;
                    }
                }
            }
        }
    }
    info.mmfsr = (SCB->CFSR & SCB_CFSR_MEMFAULTSR_Msk) >> SCB_CFSR_MEMFAULTSR_Pos;
    if (mem_manage_hook != RT_NULL)
    {
        mem_manage_hook(&info);
    }
    while (1);
}
