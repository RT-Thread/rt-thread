/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-01     liukang      first version
 */

#include <mal.h>
#include <board.h>

#define DBG_TAG    "mal"
#ifdef RT_MAL_USING_LOG
#define DBG_LVL    DBG_LOG
#else 
#define DBG_LVL    DBG_INFO
#endif
#include <rtdbg.h>

#ifdef RT_USING_MAL

#ifdef RT_MPU_PROTECT_AREA_REGIONS
static struct mpu_protect_regions mpu_protect_areas[RT_MPU_PROTECT_AREA_REGIONS] = {0};
#endif

static rt_uint8_t mpu_protect_area_num = 0;
static struct rt_mpu_ops* mpu_ops = RT_NULL;
static rt_uint8_t init_ok = 0;

rt_err_t rt_mpu_init(struct rt_mal_region *tables)
{
    rt_err_t result = RT_EOK;
    if (init_ok)
    {
        LOG_W("mpu already init.");
        return -RT_ERROR;
    }

    if (mpu_ops->init)
    {
        result = mpu_ops->init(tables);
        init_ok = 1;
    }
    else
    {
        LOG_W("please implement the mpu initialization function");
        return -RT_ERROR;
    }
    
    return result;
}

/**
 * @brief   This function will add a region configuration to the mpu configuration table.
 *
 * @param   thread is the static thread object.
 *
 * @param   addr is the pointer to protect memory.
 *
 * @param   size is the length of the protect memory.
 *
 * @param   attribute is the permission setting of the protect memory.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_mpu_attach(rt_thread_t thread, void* addr, size_t size, rt_uint32_t attribute)
{
    if (thread->setting.index >= RT_MPU_NUM_CONFIGURABLE_REGION)
    {
        LOG_E("no region can be configurable, current thread the configured regions number: %d", thread->setting.index);
        return -RT_ERROR;
    }

    thread->setting.tables[thread->setting.index].addr      = (rt_uint32_t)addr;
    thread->setting.tables[thread->setting.index].size      = size;
    thread->setting.tables[thread->setting.index].attribute = attribute;
    LOG_D("thread: %s. attach region: %d success.", thread->name, thread->setting.tables[thread->setting.index + 1].region);
    thread->setting.index += 1;
    return RT_EOK;
}

/**
 * @brief   This function will add multiple regions configuration to the mpu table.
 *
 * @param   thread is the static thread object.
 *
 * @param   regions are the multiple memmory configuration.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_mpu_attach_table(rt_thread_t thread, struct mpu_regions *regions)
{
    rt_uint8_t index = thread->setting.index, i = 0;

    if (regions == RT_NULL || thread->setting.index == RT_MPU_NUM_CONFIGURABLE_REGION)
    {
        LOG_E("no region can be configurable.");
        return -RT_ERROR;
    }

    for (; index < RT_MPU_NUM_CONFIGURABLE_REGION; index++)
    {
        if (regions[i].size > 0)
        {
            thread->setting.tables[thread->setting.index].addr      = (rt_uint32_t)regions[i].addr;
            thread->setting.tables[thread->setting.index].size      = (rt_uint32_t)regions[i].size;
            thread->setting.tables[thread->setting.index].attribute = regions[i].attribute;
            thread->setting.index += 1;
        }
        else
        {
            /* invalidate the region */
            rt_memset(&thread->setting.tables[thread->setting.index], 0x00, sizeof(thread->setting.tables[thread->setting.index]));
        }
        i += 1;
    }

    return RT_EOK;
}

/**
 * @brief   This function will delete a region configuration from the mpu configuration table, 
 *
 * @param   thread is the static thread object.
 *
 * @param   region is the region of mpu table , which shall be delete.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_mpu_delete(rt_thread_t thread, rt_uint8_t region)
{
    rt_uint8_t index = 0;

    if (region > RT_MPU_NUM_CONFIGURABLE_REGION || region < RT_MPU_FIRST_CONFIGURABLE_REGION - 1) 
    {
        return -RT_ERROR;
    }

    if (region > thread->setting.index + RT_MPU_FIRST_CONFIGURABLE_REGION)
    {
        return -RT_ERROR;
    }

    index = region - RT_MPU_FIRST_CONFIGURABLE_REGION;
    for (; index < RT_MPU_LAST_CONFIGURABLE_REGION; index++)
    {
        thread->setting.tables[index].addr      = thread->setting.tables[index + 1].addr;
        thread->setting.tables[index].size      = thread->setting.tables[index + 1].size;
        thread->setting.tables[index].attribute = thread->setting.tables[index + 1].attribute;
    }

    thread->setting.index -= 1;
    LOG_D("thread: %s. delete region: %d success.", thread->name, region);

    return RT_EOK;
}

/**
 * @brief   This function will refresh a region configuration to the mpu configuration table.
 *
 * @param   thread is the static thread object.
 *
 * @param   addr is the pointer to protect memory.
 *
 * @param   size is the length of the protect memory.
 *
 * @param   attribute is the permission setting of the protect memory.
 *
 * @param   region is the region of mpu table, which shall be refresh.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_mpu_refresh(rt_thread_t thread, void *addr, size_t size, rt_uint32_t attribute, rt_uint8_t region)
{
    rt_uint8_t index = 0;

    if (region > RT_MPU_NUM_CONFIGURABLE_REGION || region < RT_MPU_FIRST_CONFIGURABLE_REGION) 
    {
        return -RT_ERROR;
    }

    if (size == 0 || addr == RT_NULL || thread == RT_NULL)
    {
        return -RT_ERROR;
    }

    index = region - RT_MPU_FIRST_CONFIGURABLE_REGION;

    thread->setting.tables[index].addr      = (rt_uint32_t)addr;
    thread->setting.tables[index].size      = (rt_uint32_t)size;
    thread->setting.tables[index].attribute = attribute;

    return RT_EOK;
}

/**
 * @brief   This function will insert a region configuration to the mpu configuration table.
 *
 * @param   thread is the static thread object.
 *
 * @param   addr is the pointer to protect memory.
 *
 * @param   size is the length of the protect memory.
 *
 * @param   attribute is the permission setting of the protect memory.
 *
 * @param   region is the region of mpu table, which shall be insert.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_mpu_insert(rt_thread_t thread, void *addr, size_t size, rt_uint32_t attribute, rt_uint8_t region)
{
    rt_uint8_t index = 0;

    if (region > RT_MPU_NUM_CONFIGURABLE_REGION || region < RT_MPU_FIRST_CONFIGURABLE_REGION) 
    {
        return -RT_ERROR;
    }

    if (size == 0 || addr == RT_NULL || thread == RT_NULL)
    {
        return -RT_ERROR;
    }

    if (thread->setting.index == RT_MPU_NUM_CONFIGURABLE_REGION)
    {
        return -RT_ERROR;
    }

    index = region - RT_MPU_FIRST_CONFIGURABLE_REGION;

    for(int i = 0; i < RT_MPU_NUM_CONFIGURABLE_REGION; i++)
    {
        if (index == i)
        {
            for (int j = RT_MPU_NUM_CONFIGURABLE_REGION-1; j > index; j--)
            {
                rt_memcpy(&thread->setting.tables[j], &thread->setting.tables[j - 1], sizeof(thread->setting.tables[j]));
            }
            thread->setting.tables[i].addr = (rt_uint32_t)addr;
            thread->setting.tables[i].size = (rt_uint32_t)size;
            thread->setting.tables[i].attribute = attribute;
        }
    }

    return RT_EOK;
}

/**
 * @brief   This function configures that only the current thread can access a block of memory.
 *
 * @param   thread is the static thread object.
 *
 * @param   addr is the pointer to protect memory.
 *
 * @param   size is the length of the protect memory.
 *
 * @param   attribute is the permission setting of the protect memory.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_mpu_enable_protect_area(rt_thread_t thread, void *addr, size_t size, rt_uint32_t attribute)
{
    if (mpu_protect_area_num >= RT_MPU_PROTECT_AREA_REGIONS)
    {
        LOG_E("no protect area enable");
        return -RT_ERROR;
    }

    mpu_protect_areas[mpu_protect_area_num].thread           = thread;

    mpu_protect_areas[mpu_protect_area_num].tables.addr      = (rt_uint32_t)addr;
    mpu_protect_areas[mpu_protect_area_num].tables.size      = (rt_uint32_t)size;
    mpu_protect_areas[mpu_protect_area_num].tables.attribute = attribute;
    mpu_protect_area_num += 1;

    return RT_EOK;
}

/**
 * @brief   This function will removes a memory-protected area.
 *
 * @param   thread is the static thread object.
 *
 * @param   region is the region to be delete of the protect region tables.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_mpu_disable_protect_area(rt_thread_t thread, rt_uint8_t region)
{
    rt_uint8_t index = 0;

    if (mpu_protect_area_num == 0)
    {
        LOG_E("no protect area can be disable");
        return -RT_ERROR;
    }

    for (index = 0; index < mpu_protect_area_num; index++)
    {
        if ((mpu_protect_areas[index].thread == thread) && ((index + RT_MPU_FIRST_PROTECT_AREA_REGION) == region))
        {
            rt_memset(&mpu_protect_areas[index], 0x00, sizeof(mpu_protect_areas[index]));
            mpu_protect_area_num -= 1;
            break;
        }
    }

    return RT_EOK;
}

/**
 * @brief   This function will get the info of mpu.
 *
 * @param   thread is the static thread object.
 *
 * @param   type is the type of the cmd.
 *
 * @param   arg is the return value address.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_mpu_get_info(rt_thread_t thread, rt_uint32_t type, void *arg)
{
    if (mpu_ops->get_info)
    {
        return mpu_ops->get_info(thread, type, arg);
    }
    
    LOG_W("rt_mpu_get_info ops not realize.");
    
    return -RT_ERROR;
}

/**
 * @brief   This function will switch the MPU configuration table when the thread switch.
 *
 * @param   thread is the static thread object.
 */
void rt_mpu_table_switch(rt_thread_t thread)
{
    if (mpu_ops->switch_table == RT_NULL)
    {
        LOG_E("mpu switch table ops is null.");
    }

    mpu_ops->switch_table(thread, mpu_protect_area_num, mpu_protect_areas);
}

/**
 * @brief   This function will switch the MPU configuration table when the thread switch.
 *
 * @param   thread is the static thread object.
 * 
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_mpu_exception_handler(rt_thread_t thread, void* addr, rt_uint32_t attribute)
{
    if (thread->mpu_hook)
    {
        return thread->mpu_hook(addr, attribute);
    }
    else
    {
        return -RT_ERROR;
    }
}

/**
 * @brief   This function will register a mpu exception hook of current thread.
 *
 * @param   thread is the static thread object.
 *
 * @param   hook is the mpu exception function.
 */
void rt_mpu_exception_sethook(rt_thread_t thread, rt_err_t (*hook)(void* addr, rt_uint32_t attribute))
{
    if (thread->mpu_hook != RT_NULL)
    {
        LOG_W("thread: %s update mpu hook function", thread->name);
    }
    thread->mpu_hook = hook;
}

/**
 * @brief   This function will register mpu ops.
 *
 * @param   ops is the ops.
 *
 * @return  Return the operation status. If the return value is RT_EOK, the function is successfully executed.
 *          If the return value is any other values, it means this operation failed.
 */
rt_err_t rt_mpu_ops_register(struct rt_mpu_ops *ops)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(ops != RT_NULL);

    mpu_ops = ops;

    return result;
}

#endif /* RT_USING_MAL */
