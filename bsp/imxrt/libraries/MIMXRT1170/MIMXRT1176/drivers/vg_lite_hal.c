/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright (c) 2014 - 2020 Vivante Corporation
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#include "vg_lite_platform.h"
#include "vg_lite_kernel.h"
#include "vg_lite_hal.h"
#include "vg_lite_hw.h"
#include "vg_lite_os.h"

#if !_BAREMETAL
#include "rtthread.h"
#else
#include "xil_cache.h"
#endif

#if _BAREMETAL
/* The followings should be configured by FPGA. */
static    uint32_t    registerMemBase    = 0x43c80000;
#else
static    uint32_t    registerMemBase    = 0x40240000;
#endif

#define HEAP_NODE_USED  0xABBAF00D

volatile void* contiguousMem = NULL;
uint32_t gpuMemBase = 0;

/* Default heap size is 16MB. */
static int heap_size = MAX_CONTIGUOUS_SIZE;

void vg_lite_init_mem(uint32_t register_mem_base,
          uint32_t gpu_mem_base,
          volatile void * contiguous_mem_base,
          uint32_t contiguous_mem_size)
{
    registerMemBase = register_mem_base;
    gpuMemBase      = gpu_mem_base;
    contiguousMem   = contiguous_mem_base;
    heap_size       = contiguous_mem_size;
}

/* Implementation of list. ****************************************/
typedef struct list_head {
    struct list_head *next;
    struct list_head *prev;
}list_head_t;

#define INIT_LIST_HEAD(entry) \
        (entry)->next = (entry);\
        (entry)->prev = (entry);

/* Add the list item in front of "head". */
static inline void add_list(list_head_t *to_add, list_head_t *head)
{
    /* Link the new item. */
    to_add->next = head;
    to_add->prev = head->prev;

  /* Modify the neighbor. */
    head->prev = to_add;
    if (to_add->prev != NULL) {
        to_add->prev->next = to_add;
    }
}

/* Remove an entry out of the list. */
static inline void delete_list(list_head_t *entry)
{
    if (entry->prev != NULL) {
        entry->prev->next = entry->next;
    }
    if (entry->next != NULL) {
        entry->next->prev = entry->prev;
    }
}

/* End of list implementation. ***********/
static inline void _memset(void *mem, unsigned char value, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        ((unsigned char*)mem)[i] = value;
    }
}

typedef struct heap_node {
    list_head_t list; /* TODO: Linux specific, needs to rewrite. */
    uint32_t offset;
    unsigned long size;
    uint32_t status;
}heap_node_t;

struct memory_heap {
    uint32_t free;
    list_head_t list;
};

struct mapped_memory {
    void * logical;
    uint32_t physical;
    int page_count;
    struct page ** pages;
};

struct vg_lite_device {
    /* void * gpu; */
    uint32_t gpu;    /* Always use physical for register access in RTOS. */
    /* struct page * pages; */
    volatile void * contiguous;
    unsigned int order;
    unsigned int heap_size;
    void * virtual;
    uint32_t physical;
    uint32_t size;
    struct memory_heap heap;
    int irq_enabled;

#if defined(VG_DRIVER_SINGLE_THREAD)
    volatile uint32_t int_flags;
#if _BAREMETAL
        /* wait_queue_head_t int_queue; */
        xSemaphoreHandle int_queue;
#else
        /* wait_queue_head_t int_queue; */
        rt_sem_t int_queue;
#endif
#endif /* VG_DRIVER_SINGLE_THREAD */

    void * device;
    int registered;
    int major;
    struct class * class;
    int created;
};

struct client_data {
    struct vg_lite_device * device;
    struct vm_area_struct * vm;
    void * contiguous_mapped;
};

static struct vg_lite_device Device, * device;

void vg_lite_hal_delay(uint32_t ms)
{
    vg_lite_os_sleep(ms);
}

void vg_lite_hal_barrier(void)
{
     /*Memory barrier. */
#if _BAREMETAL
     Xil_DCacheFlush();
#else
    __asm("DSB");
#endif
}

static int vg_lite_init(void);
vg_lite_error_t vg_lite_hal_initialize(void)
{
    int32_t error = VG_LITE_SUCCESS;
    /* TODO: Turn on the power. */
    vg_lite_init();
    /* TODO: Turn on the clock. */
    error = vg_lite_os_initialize();

    return (vg_lite_error_t)error;
}

void vg_lite_hal_deinitialize(void)
{
    /* TODO: Remove clock. */
    vg_lite_os_deinitialize();
    /* TODO: Remove power. */
}

static int split_node(heap_node_t * node, unsigned long size)
{
    /* TODO: the original is linux specific list based, needs rewrite.
    */
    heap_node_t * split;

    /*
     * If the newly allocated object fits exactly the size of the free
     * node, there is no need to split.
     */
    if (node->size - size == 0)
        return 0;

    /* Allocate a new node. */
    split = (heap_node_t *)vg_lite_os_malloc(sizeof(heap_node_t));

    if (split == NULL)
        return -1;

    /* Fill in the data of this node of the remaning size. */
    split->offset = node->offset + size;
    split->size = node->size - size;
    split->status = 0;

    /* Add the new node behind the current node. */
    add_list(&split->list, &node->list);

    /* Adjust the size of the current node. */
    node->size = size;
    return 0;
}

vg_lite_error_t vg_lite_hal_allocate_contiguous(unsigned long size, void ** logical, uint32_t * physical,void ** node)
{
    unsigned long aligned_size;
    heap_node_t * pos;

    /* Align the size to 64 bytes. */
    aligned_size = (size + 63) & ~63;

    /* Check if there is enough free memory available. */
    if (aligned_size > device->heap.free) {
        return VG_LITE_OUT_OF_MEMORY;
    }

    /* Walk the heap backwards. */
    for (pos = (heap_node_t*)device->heap.list.prev;
                 &pos->list != &device->heap.list;
                 pos = (heap_node_t*) pos->list.prev) {
        /* Check if the current node is free and is big enough. */
        if (pos->status == 0 && pos->size >= aligned_size) {
            /* See if we the current node is big enough to split. */
                if (0 != split_node(pos, aligned_size))
                {
                    return VG_LITE_OUT_OF_RESOURCES;
                }
            /* Mark the current node as used. */
            pos->status = HEAP_NODE_USED;

            /*  Return the logical/physical address. */
            /* *logical = (uint8_t *) private_data->contiguous_mapped + pos->offset; */
            *logical = (uint8_t *)device->virtual + pos->offset;
            *physical = gpuMemBase + (uint32_t)(*logical);/* device->physical + pos->offset; */
            device->heap.free -= aligned_size;

            *node = pos;
            return VG_LITE_SUCCESS;
        }
    }

    /* Out of memory. */
    return VG_LITE_OUT_OF_MEMORY;
}

void vg_lite_hal_free_contiguous(void * memory_handle)
{
    /* TODO: no list available in RTOS. */
    heap_node_t * pos, * node;

    /* Get pointer to node. */
    node = memory_handle;

    if (node->status != HEAP_NODE_USED) {
        return;
    }

    /* Mark node as free. */
    node->status = 0;

    /* Add node size to free count. */
    device->heap.free += node->size;

    /* Check if next node is free. */
    pos = node;
    for (pos = (heap_node_t *)pos->list.next;
         &pos->list != &device->heap.list;
         pos = (heap_node_t *)pos->list.next) {
        if (pos->status == 0) {
            /* Merge the nodes. */
            node->size += pos->size;
            if(node->offset > pos->offset)
                node->offset = pos->offset;
            /* Delete the next node from the list. */
            delete_list(&pos->list);
            vg_lite_os_free(pos);
        }
        break;
    }

    /* Check if the previous node is free. */
    pos = node;
    for (pos = (heap_node_t *)pos->list.prev;
         &pos->list != &device->heap.list;
         pos = (heap_node_t *)pos->list.prev) {
        if (pos->status == 0) {
            /* Merge the nodes. */
            pos->size += node->size;
            if(pos->offset > node->offset)
                pos->offset = node->offset;
            /* Delete the current node from the list. */
            delete_list(&node->list);
            vg_lite_os_free(node);
        }
        break;
    }
    /* when release command buffer node and ts buffer node to exit,release the linked list*/
    if(device->heap.list.next == device->heap.list.prev) {
        delete_list(&pos->list);
        vg_lite_os_free(pos);
    }
}

void vg_lite_hal_free_os_heap(void)
{
    struct heap_node    *pos, *n;

    /* Check for valid device. */
    if (device != NULL) {
        /* Process each node. */
        for (pos = (heap_node_t *)device->heap.list.next,
             n = (heap_node_t *)pos->list.next;
             &pos->list != &device->heap.list;
             pos = n, n = (heap_node_t *)n->list.next) {
                /* Remove it from the linked list. */
                delete_list(&pos->list);
                /* Free up the memory. */
                vg_lite_os_free(pos);
        }
    }
}

/* Portable: read register value. */
uint32_t vg_lite_hal_peek(uint32_t address)
{
    /* Read data from the GPU register. */
    return (uint32_t) (*(volatile uint32_t *) (device->gpu + address));
}

/* Portable: write register. */
void vg_lite_hal_poke(uint32_t address, uint32_t data)
{
    /* Write data to the GPU register. */
    uint32_t *LocalAddr = (uint32_t *)(device->gpu + address);
    *LocalAddr = data;
}

vg_lite_error_t vg_lite_hal_query_mem(vg_lite_kernel_mem_t *mem)
{
    if(device != NULL){
        mem->bytes  = device->heap.free;
        return VG_LITE_SUCCESS;
    }
    mem->bytes = 0;
    return VG_LITE_NO_CONTEXT;
}

void vg_lite_IRQHandler(void)
{
    vg_lite_os_IRQHandler();
}

int32_t vg_lite_hal_wait_interrupt(uint32_t timeout, uint32_t mask, uint32_t * value)
{
    return vg_lite_os_wait_interrupt(timeout,mask,value);
}

void * vg_lite_hal_map(unsigned long bytes, void * logical, uint32_t physical, uint32_t * gpu)
{

    (void) bytes;
    (void) logical;
    (void) physical;
    (void) gpu;
    return (void *)0;
}

void vg_lite_hal_unmap(void * handle)
{

    (void) handle;
}

#if !defined(VG_DRIVER_SINGLE_THREAD)
vg_lite_error_t vg_lite_hal_submit(uint32_t context,uint32_t physical, uint32_t offset, uint32_t size, vg_lite_os_async_event_t *event)
{
    return (vg_lite_error_t)vg_lite_os_submit(context,physical,offset,size,event);
}

vg_lite_error_t vg_lite_hal_wait(uint32_t timeout, vg_lite_os_async_event_t *event)
{
    return  (vg_lite_error_t)vg_lite_os_wait(timeout,event);
}
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

static void vg_lite_exit(void)
{
    heap_node_t * pos;
    heap_node_t * n;

    /* Check for valid device. */
    if (device != NULL) {
        /* TODO: unmap register mem should be unnecessary. */
        device->gpu = 0;

        /* Process each node. */
        for (pos = (heap_node_t *)device->heap.list.next, n = (heap_node_t *)pos->list.next;
             &pos->list != &device->heap.list;
             pos = n, n = (heap_node_t *)n->list.next) {
            /* Remove it from the linked list. */
            delete_list(&pos->list);

            /* Free up the memory. */
            vg_lite_os_free(pos);
        }

        /* Free up the device structure. */
        vg_lite_os_free(device);
    }
}

static int vg_lite_init(void)
{
    heap_node_t * node;

    /* Initialize memory and objects ***************************************/
    /* Create device structure. */
    device = &Device;

    /* Zero out the enture structure. */
    _memset(device, 0, sizeof(struct vg_lite_device));

    /* Setup register memory. **********************************************/
    device->gpu = registerMemBase;

    /* Initialize contiguous memory. ***************************************/
    /* Allocate the contiguous memory. */
    device->heap_size = heap_size;
    device->contiguous = (volatile void *)contiguousMem;
    _memset((void *)device->contiguous, 0, heap_size);
    /* Make 64byte aligned. */
    while ((((uint32_t)device->contiguous) & 63) != 0)
    {
        device->contiguous = ((unsigned char*) device->contiguous) + 4;
        device->heap_size -= 4;
    }

    /* Check if we allocated any contiguous memory or not. */
    if (device->contiguous == NULL) {
        vg_lite_exit();
        return -1;
    }

    device->virtual = (void *)device->contiguous;
    device->physical = gpuMemBase + (uint32_t)device->virtual;
    device->size = device->heap_size;

    /* Create the heap. */
    INIT_LIST_HEAD(&device->heap.list);
    device->heap.free = device->size;

    node = (heap_node_t *)vg_lite_os_malloc(sizeof(heap_node_t));

    if (node == NULL) {
        vg_lite_exit();
        return -1;
    }
    node->offset = 0;
    node->size = device->size;
    node->status = 0;
    add_list(&node->list, &device->heap.list);
#if defined(VG_DRIVER_SINGLE_THREAD)
#if !_BAREMETAL /*for rt500*/
        device->int_queue = rt_sem_create("diq", 0, RT_IPC_FLAG_PRIO);
        device->int_flags = 0;
#endif
#endif /* VG_DRIVER_SINGLE_THREAD */
    /* Success. */
    return 0;
}
