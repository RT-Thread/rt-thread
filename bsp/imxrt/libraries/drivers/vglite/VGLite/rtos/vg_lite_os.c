#include "vg_lite_os.h"

#include "rtthread.h"
#include "vg_lite_hw.h"
#include "vg_lite_hal.h"

/* If bit31 is activated this indicates a bus error */
#define IS_AXI_BUS_ERR(x) ((x)&(1U << 31))

#if !defined(VG_DRIVER_SINGLE_THREAD)
#define ISR_WAIT_TIME   0x1FFFF
#define MAX_MUTEX_TIME  100
#define THREAD_WAIT_TIME  20

/* command queue task parameter */
#define QUEUE_THREAD_NAME     "queue_thread"
#ifndef QUEUE_THREAD_PRIO
// #define QUEUE_THREAD_PRIO  (configMAX_PRIORITIES - 1)
#define QUEUE_THREAD_PRIO     0
#endif /* QUEUE_THREAD_PRIO */
#define QUEUE_THREAD_SIZE  1024
#define QUEUE_LENGTH     8
#define MAX_QUEUE_WAIT_NUM  10
/* The array stores one or more tlss, which is pointed by user_data of current thread. Set it to 1 when only vglite is used, otherwise set it to 2 if elementary is applied. */
#define TLS_ARRAY_LENGTH    2

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TURE
#define TURE 1
#endif

typedef struct vg_lite_queue{
    uint32_t  cmd_physical;
    uint32_t  cmd_offset;
    uint32_t  cmd_size;
    vg_lite_os_async_event_t *event;
}
vg_lite_queue_t;

rt_uint32_t tls_array[TLS_ARRAY_LENGTH] = {NULL};
typedef struct vg_lite_os{
    rt_thread_t     task_hanlde;
    rt_mq_t    queue_handle;
}
vg_lite_os_t;

static rt_mutex_t mutex;
static vg_lite_os_t os_obj = {0};

rt_sem_t semaphore[THREAD_LENGTH] = {NULL};
rt_sem_t command_semaphore = NULL;
uint32_t curContext;
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */
rt_sem_t int_queue;
volatile uint32_t int_flags;

void __attribute__((weak)) vg_lite_bus_error_handler()
{
    /*
     * Default implementation of the bus error handler does nothing. Application
     * should override this handler if it requires to be notified when a bus
     * error event occurs.
     */
     return;
}

#if !defined(VG_DRIVER_SINGLE_THREAD)
/* command queue function */
void command_queue(void * parameters)
{
    vg_lite_queue_t* peek_queue;
    uint32_t  even_got;
    uint32_t  len;

    os_obj.queue_handle = rt_mq_create("queue_vglite", sizeof(vg_lite_queue_t * ), QUEUE_LENGTH, RT_IPC_FLAG_PRIO);
    if(os_obj.queue_handle == RT_NULL)
    {
        /*command queue create fail, delete queue task */
        rt_thread_delete(rt_thread_self());
    }

    command_semaphore = rt_sem_create("cs", 0, RT_IPC_FLAG_PRIO);
    while(1)
    {
        even_got = 0;
        if (rt_sem_take((rt_sem_t)command_semaphore, RT_WAITING_FOREVER) == RT_EOK) {
            if(os_obj.queue_handle->entry)
            {
                len = rt_mq_recv(os_obj.queue_handle, (void*) &peek_queue, os_obj.queue_handle->msg_size, (rt_int32_t) ((rt_int64_t)THREAD_WAIT_TIME * RT_TICK_PER_SECOND / 1000));
                if(len)
                {
#if defined(PRINT_COMMAND_BUFFER)
                    int i = 0;
                    for(i=0;i < (peek_queue->cmd_size + 3) / 4; i++)
                    {
                        if(i % 4 == 0)
                            printf("\r\n");
                        printf("0x%08x ",((uint32_t*)(peek_queue->cmd_physical + peek_queue->cmd_offset))[i]);
                    }
#endif
                    vg_lite_hal_poke(VG_LITE_HW_CMDBUF_ADDRESS, peek_queue->cmd_physical + peek_queue->cmd_offset);
                    vg_lite_hal_poke(VG_LITE_HW_CMDBUF_SIZE, (peek_queue->cmd_size +7)/8 );

                    if(vg_lite_hal_wait_interrupt(ISR_WAIT_TIME, (uint32_t)~0, &even_got))
                        peek_queue->event->signal = VG_LITE_HW_FINISHED;
                    else
#if defined(PRINT_DEBUG_REGISTER)
                    {
                        unsigned int debug;
                        unsigned int iter;
                        for(iter =0; iter < 16 ; iter ++)
                        {
                             vg_lite_hal_poke(0x470, iter);
                             debug = vg_lite_hal_peek(0x450);
                             printf("0x450[%d] = 0x%x\n", iter,debug);
                        }
                        for(iter =0; iter < 16 ; iter ++)
                        {
                             vg_lite_hal_poke(0x470, iter <<16);
                             debug = vg_lite_hal_peek(0x454);
                             printf("0x454[%d] = 0x%x\n", iter,debug);
                        }
                        for(iter =0; iter < 16 ; iter ++)
                        {
                             vg_lite_hal_poke(0x478, iter);
                             debug = vg_lite_hal_peek(0x468);
                             printf("0x468[%d] = 0x%x\n", iter,debug);
                        }
                        for(iter =0; iter < 16 ; iter ++)
                        {
                             vg_lite_hal_poke(0x478, iter);
                             debug = vg_lite_hal_peek(0x46C);
                             printf("0x46C[%d] = 0x%x\n", iter,debug);
                        }
#endif
                        /* wait timeout */
                        peek_queue->event->signal = VG_LITE_IDLE;
#if defined(PRINT_DEBUG_REGISTER)
                    }
#endif
                    if(semaphore[peek_queue->event->semaphore_id]){
                        rt_sem_release(semaphore[peek_queue->event->semaphore_id]);
                    }

                    vg_lite_os_free((void *) peek_queue);
                }
            }
        }
    }
}

int32_t vg_lite_os_init_tls_array(void)
{
    rt_thread_t rt_TCB;

    rt_TCB = rt_thread_self();
    RT_ASSERT( rt_TCB != NULL );

    rt_TCB->user_data = (rt_uint32_t) tls_array;

    return VG_LITE_SUCCESS;
}

void vg_lite_os_deinit_tls_array(void)
{
    rt_thread_t rt_TCB;

    rt_TCB = rt_thread_self();
    RT_ASSERT( rt_TCB != NULL );
    rt_TCB->user_data = NULL;
}

int32_t vg_lite_os_set_tls(void* tls)
{
    if(tls == NULL)
        return VG_LITE_INVALID_ARGUMENT;

    rt_thread_t rt_TCB;

    rt_TCB = rt_thread_self();
    RT_ASSERT( rt_TCB != NULL );

    rt_uint32_t * tls_ptr = (rt_uint32_t *) rt_TCB->user_data;
    *tls_ptr = (rt_uint32_t) tls;
    return VG_LITE_SUCCESS;
}

void * vg_lite_os_get_tls( )
{
    rt_thread_t rt_TCB;

    void * pvReturn = NULL;

    rt_TCB = rt_thread_self();

    rt_uint32_t * tls_ptr = (rt_uint32_t *) rt_TCB->user_data;
    pvReturn = (void *) (*tls_ptr);

    return pvReturn;
}
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

void * vg_lite_os_malloc(uint32_t size)
{
    return rt_malloc((rt_size_t)size);
}

void vg_lite_os_free(void * memory)
{
    rt_free(memory);
}

#if !defined(VG_DRIVER_SINGLE_THREAD)
void vg_lite_os_reset_tls()
{
    rt_thread_t rt_TCB;

    rt_TCB = rt_thread_self();
    RT_ASSERT( rt_TCB != NULL );

    rt_uint32_t * tls_ptr = (rt_uint32_t *) rt_TCB->user_data;
    *tls_ptr = NULL;
}
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

void vg_lite_os_sleep(uint32_t msec)
{
      rt_thread_mdelay(msec);
}

int32_t vg_lite_os_initialize(void)
{
#if !defined(VG_DRIVER_SINGLE_THREAD)
    static int task_number = 0;

#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

    int_queue = rt_sem_create("iq", 0, RT_IPC_FLAG_PRIO);
    int_flags = 0;

#if !defined(VG_DRIVER_SINGLE_THREAD)
    if(mutex == NULL)
    {
        mutex = rt_mutex_create("mut", RT_IPC_FLAG_PRIO);
        if(mutex == NULL)
            return VG_LITE_MULTI_THREAD_FAIL;
    }

    if(task_number == 0)
    {
        if(rt_mutex_take(mutex, (rt_int32_t) ((rt_int64_t)THREAD_WAIT_TIME * RT_TICK_PER_SECOND / 1000)) == RT_EOK)
        {
            if(os_obj.task_hanlde == NULL)
            {
                os_obj.task_hanlde = rt_thread_create(QUEUE_THREAD_NAME, command_queue, NULL, QUEUE_THREAD_SIZE, QUEUE_THREAD_PRIO, 1);
                if(os_obj.task_hanlde == RT_NULL)
                {
                    /* command queue task create fail */
                    rt_mutex_release(mutex);
                    return VG_LITE_MULTI_THREAD_FAIL;
                }
                else
                    rt_thread_startup(os_obj.task_hanlde);
            }
            task_number++;
            rt_mutex_release(mutex);
            return VG_LITE_SUCCESS;
        }
    }
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */
    return VG_LITE_SUCCESS;
}

void vg_lite_os_deinitialize(void)
{
    /* TODO: Remove clock. */
#if !defined(VG_DRIVER_SINGLE_THREAD)
    rt_mutex_delete(mutex);
    mutex = 0;
#endif /* VG_DRIVER_SINGLE_THREAD */
    rt_sem_delete(int_queue);
    /* TODO: Remove power. */
}

#if !defined(VG_DRIVER_SINGLE_THREAD)
int32_t vg_lite_os_lock()
{
    if(mutex == NULL)
        return VG_LITE_NOT_SUPPORT;

    if(rt_mutex_take(mutex, (rt_int32_t) ((rt_int64_t)MAX_MUTEX_TIME * RT_TICK_PER_SECOND / 1000)) != RT_EOK)
        return VG_LITE_MULTI_THREAD_FAIL;

    return VG_LITE_SUCCESS;
}

int32_t vg_lite_os_unlock()
{
    if(rt_mutex_release(mutex) != RT_EOK)
        return VG_LITE_MULTI_THREAD_FAIL;

    return VG_LITE_SUCCESS;
}

int32_t vg_lite_os_submit(uint32_t context, uint32_t physical, uint32_t offset, uint32_t size, vg_lite_os_async_event_t *event)
{
    vg_lite_queue_t* queue_node;

    if(os_obj.queue_handle == RT_NULL)
        return VG_LITE_NOT_SUPPORT;

    queue_node = (vg_lite_queue_t*) vg_lite_os_malloc(sizeof(vg_lite_queue_t));
    if(queue_node == NULL)
        return VG_LITE_MULTI_THREAD_FAIL;

    queue_node->cmd_physical = physical;
    queue_node->cmd_offset = offset;
    queue_node->cmd_size = size;
    queue_node->event = event;

    /* Current command buffer has been sent to the command queue. */
    event->signal = VG_LITE_IN_QUEUE;

    if(rt_mq_send_wait(os_obj.queue_handle, (void *) &queue_node, os_obj.queue_handle->msg_size, (rt_int32_t) ((rt_int64_t)ISR_WAIT_TIME * RT_TICK_PER_SECOND / 1000)) != RT_EOK)
        return VG_LITE_MULTI_THREAD_FAIL;
    curContext = context;

    if (vg_lite_os_wait_event(event) == VG_LITE_SUCCESS) {
        if(rt_sem_release(command_semaphore) != RT_EOK)
            return VG_LITE_MULTI_THREAD_FAIL;
        return VG_LITE_SUCCESS;
    }

    return VG_LITE_MULTI_THREAD_FAIL;
}

int32_t vg_lite_os_wait(uint32_t timeout, vg_lite_os_async_event_t *event)
{
    if (semaphore[event->semaphore_id]) {
        if (rt_sem_take(semaphore[event->semaphore_id], RT_WAITING_FOREVER) == RT_EOK) {
            if(event->signal == VG_LITE_HW_FINISHED){
                rt_sem_release(semaphore[event->semaphore_id]);
                return VG_LITE_SUCCESS;
            }
            else{
                rt_sem_release(semaphore[event->semaphore_id]);
                return VG_LITE_TIMEOUT;
            }
        }
    }
    return VG_LITE_TIMEOUT;
}
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

void vg_lite_os_IRQHandler(void)
{
    uint32_t flags = vg_lite_hal_peek(VG_LITE_INTR_STATUS);

    if (flags) {
        /* Combine with current interrupt flags. */
        int_flags |= flags;

        /* Wake up any waiters. */
        if(int_queue){
            rt_sem_release(int_queue);
        }
    }
}

int32_t vg_lite_os_wait_interrupt(uint32_t timeout, uint32_t mask, uint32_t * value)
{
#if _BAREMETAL
    uint32_t int_status=0;
    int_status = vg_lite_hal_peek(VG_LITE_INTR_STATUS);
    (void)value;

    while (int_status==0){
        int_status = vg_lite_hal_peek(VG_LITE_INTR_STATUS);
        usleep(1);
    }

    if (IS_AXI_BUS_ERR(*value))
    {
        vg_lite_bus_error_handler();
    }
    return 1;
#else /*for rt500*/
    if(int_queue) {
        if (rt_sem_take(int_queue, (rt_int32_t) ((rt_int64_t)timeout * RT_TICK_PER_SECOND / 1000)) == RT_EOK) {
            if (value != NULL) {
               *value = int_flags & mask;
                if (IS_AXI_BUS_ERR(*value))
                {
                    vg_lite_bus_error_handler();
                }
            }
            int_flags = 0;

            return 1;
        }
    }
    return 0;
#endif
}

#if !defined(VG_DRIVER_SINGLE_THREAD)
int32_t vg_lite_os_init_event(vg_lite_os_async_event_t *event,
                                      uint32_t semaphore_id,
                                      int32_t state)
{
    if (event->semaphore_id >= THREAD_LENGTH)
        return VG_LITE_INVALID_ARGUMENT;

    if (semaphore[semaphore_id])
        return VG_LITE_ALREADY_EXISTS;

    char name[RT_NAME_MAX] = {0};
    rt_snprintf(name, RT_NAME_MAX, "s%d", semaphore_id);
    semaphore[semaphore_id] = rt_sem_create(name, 0, RT_IPC_FLAG_PRIO);
    if (!semaphore[semaphore_id])
        return VG_LITE_OUT_OF_MEMORY;

    rt_sem_release(semaphore[semaphore_id]);

    event->semaphore_id = semaphore_id;
    event->signal       = state;

    return VG_LITE_SUCCESS;
}

int32_t vg_lite_os_delete_event(vg_lite_os_async_event_t *event)
{
    if (event->semaphore_id >= THREAD_LENGTH)
        return VG_LITE_INVALID_ARGUMENT;

    if (semaphore[event->semaphore_id]){
        rt_sem_delete(semaphore[event->semaphore_id]);
        semaphore[event->semaphore_id] = NULL;
    }

    return VG_LITE_SUCCESS;
}

int32_t vg_lite_os_wait_event(vg_lite_os_async_event_t *event)
{
    if (event->semaphore_id >= THREAD_LENGTH)
        return VG_LITE_INVALID_ARGUMENT;

    if (rt_sem_take(semaphore[event->semaphore_id], RT_WAITING_FOREVER) != RT_EOK)
        return VG_LITE_MULTI_THREAD_FAIL;

    return VG_LITE_SUCCESS;
}

int32_t vg_lite_os_signal_event(vg_lite_os_async_event_t *event)
{
    if (event->semaphore_id >= THREAD_LENGTH)
        return VG_LITE_INVALID_ARGUMENT;

    rt_sem_release(semaphore[event->semaphore_id]);
    return VG_LITE_SUCCESS;
}

int8_t vg_lite_os_query_context_switch(uint32_t context)
{
   if(!curContext || curContext == context)
        return FALSE;
    return TURE;
}
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */
