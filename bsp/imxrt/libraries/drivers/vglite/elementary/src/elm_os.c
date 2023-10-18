#include "elm_os.h"
#include "rtthread.h"

vg_lite_error_t elm_os_set_tls(void* tls)
{
    if(tls == NULL)
        return VG_LITE_INVALID_ARGUMENT;

    rt_thread_t rt_TCB;

    rt_TCB = rt_thread_self();
    RT_ASSERT( rt_TCB != NULL );


    rt_uint32_t * tls_ptr = (rt_uint32_t *)rt_TCB->user_data;
    *(tls_ptr + 1) = (rt_uint32_t) tls;
        return VG_LITE_SUCCESS;
}

void * elm_os_get_tls(void)
{
    rt_thread_t rt_TCB;

    void * pvReturn = NULL;

    rt_TCB = rt_thread_self();

    rt_uint32_t * tls_ptr = (rt_uint32_t *)rt_TCB->user_data;
    pvReturn = (void *) *(tls_ptr + 1);

    return pvReturn;
}

void elm_os_reset_tls(void)
{
    rt_thread_t rt_TCB;

    rt_TCB = rt_thread_self();
    RT_ASSERT( rt_TCB != NULL );

    rt_uint32_t * tls_ptr = (rt_uint32_t *)rt_TCB->user_data;
    *(tls_ptr + 1) = NULL;
}
