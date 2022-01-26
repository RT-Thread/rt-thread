/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-10-28     tyx          the first version.
 */

#include <rtthread.h>

#ifdef ARM_CM33_ENABLE_TRUSTZONE
extern void TZ_InitContextSystem_S(void);
extern rt_uint32_t TZ_AllocModuleContext_S (rt_uint32_t module);
extern rt_uint32_t TZ_FreeModuleContext_S(rt_uint32_t id);
extern rt_uint32_t TZ_LoadContext_S(rt_uint32_t id);
extern rt_uint32_t TZ_StoreContext_S(rt_uint32_t id);
#else
void TZ_InitContextSystem_S(void){}
rt_uint32_t TZ_AllocModuleContext_S (rt_uint32_t module){return 0;}
rt_uint32_t TZ_FreeModuleContext_S(rt_uint32_t id) {return 0;}
rt_uint32_t TZ_LoadContext_S(rt_uint32_t id){return 0;};
rt_uint32_t TZ_StoreContext_S(rt_uint32_t id){return 0;};
#endif
extern int tzcall(int id, rt_ubase_t arg0, rt_ubase_t arg1, rt_ubase_t arg2);

#define TZ_INIT_CONTEXT_ID     (0x1001)
#define TZ_ALLOC_CONTEXT_ID    (0x1002)
#define TZ_FREE_CONTEXT_ID     (0x1003)

rt_ubase_t rt_trustzone_current_context;

#if defined(__CC_ARM)
static __inline rt_uint32_t __get_IPSR(void)
{
  register rt_uint32_t result          __asm("ipsr");
  return(result);
}
#elif defined(__clang__)
__attribute__((always_inline)) static __inline rt_uint32_t __get_IPSR(void)
{
    rt_uint32_t result;

    __asm volatile ("MRS %0, ipsr" : "=r" (result) );
    return(result);
}
#elif defined(__IAR_SYSTEMS_ICC__)
_Pragma("inline=forced") static inline int __get_IPSR(int value)
{
    rt_uint32_t result;

    asm("MRS  %0, ipsr" : "=r"(result));
    return result;
}
#elif defined(__GNUC__)
__attribute__((always_inline)) static inline rt_uint32_t __get_IPSR(void)
{
  rt_uint32_t result;

  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}
#endif

void rt_trustzone_init(void)
{
    static rt_uint8_t _init;

    if (_init)
        return;
    tzcall(TZ_INIT_CONTEXT_ID, 0, 0, 0);
    _init = 1;
}

rt_err_t rt_trustzone_enter(rt_ubase_t module)
{
    rt_trustzone_init();
    if (tzcall(TZ_ALLOC_CONTEXT_ID, module, 0, 0))
    {
        return RT_EOK;
    }
    return -RT_ERROR;
}

rt_err_t rt_trustzone_exit(void)
{
    tzcall(TZ_FREE_CONTEXT_ID, 0, 0, 0);
    return RT_EOK;
}

void rt_trustzone_context_store(rt_ubase_t context)
{
    TZ_StoreContext_S(context);
}

void rt_trustzone_context_load(rt_ubase_t context)
{
    TZ_LoadContext_S(context);
}

int rt_secure_svc_handle(int svc_id, rt_ubase_t arg0, rt_ubase_t arg1, rt_ubase_t arg2)
{
    rt_ubase_t tmp;
    int res = 0;

    switch (svc_id)
    {
    case TZ_INIT_CONTEXT_ID:
        TZ_InitContextSystem_S();
        break;
    case TZ_ALLOC_CONTEXT_ID:
        res = TZ_AllocModuleContext_S(arg0);
        if (res <= 0)
        {
            rt_kprintf("Alloc Context Failed\n");
        }
        else
        {
            rt_trustzone_current_context = res;
            TZ_LoadContext_S(res);
        }
        break;
    case TZ_FREE_CONTEXT_ID:
        TZ_FreeModuleContext_S(rt_trustzone_current_context);
        rt_trustzone_current_context = 0;
        break;
    }
    return res;
}

