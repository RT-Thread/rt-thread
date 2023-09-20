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

#ifndef _vg_lite_kernel_h_
#define _vg_lite_kernel_h_

#include "vg_lite_os.h"

/* Interrupt IDs from GPU. */
#define EVENT_UNEXPECTED_MESH  0x80000000
#define EVENT_CMD_BAD_WRITE    0x40000000
#define EVENT_ERROR_RECOVER    0x20000000
#define EVENT_CMD_SWITCH       0x10000000
#define EVENT_MCU_BAD_WRITE    0x08000000
#define EVENT_END              0

#define MAX_CONTIGUOUS_SIZE 0x02000000

#define VG_LITE_INFINITE       0xFFFFFFFF
#define VG_LITE_MAX_WAIT_TIME  0x130000
#define CMDBUF_COUNT        2

#define VG_LITE_ALIGN(number, alignment)    \
        (((number) + ((alignment) - 1)) & ~((alignment) - 1))

/* Available function optimization levels */
#if (defined(__ICCARM__))
#define VG_LITE_ATTR_OPTIMIZE_LOW               _Pragma("optimize=none")
#define VG_LITE_ATTR_OPTIMIZE_MEDIUM            _Pragma("optimize=medium")
#define VG_LITE_ATTR_OPTIMIZE_HIGH              _Pragma("optimize=high")
#else /* ARMGCC */
#define VG_LITE_ATTR_OPTIMIZE_LOW               __attribute__((optimize(1)))
#define VG_LITE_ATTR_OPTIMIZE_MEDIUM            __attribute__((optimize(2)))
#define VG_LITE_ATTR_OPTIMIZE_HIGH              __attribute__((optimize(3)))
#endif /* defined(__ICCARM__) */

/* Allow develpers to force a function optimization level */
#define VG_LITE_OPTIMIZE(level)                 VG_LITE_ATTR_OPTIMIZE_##level

#define VG_LITE_KERNEL_IS_GPU_IDLE() \
((vg_lite_hal_peek(VG_LITE_HW_IDLE) & VG_LITE_HW_IDLE_STATE) == VG_LITE_HW_IDLE_STATE)

/* Hardware chip Ids */
#define GPU_CHIP_ID_GCNanoliteV         0x255
#define GPU_CHIP_ID_GC355               0x355

#ifdef __cplusplus
extern "C" {
#endif

#ifndef VG_LITE_ERROR
#define VG_LITE_ERROR  1
/*!
    @abstract Error codes that the vg_lite functions can return.

    @discussion
    All API functions return a status code. On success, <code>VG_LITE_SUCCESS</code> will be returned when a function is
    successful. This value is set to zero, so if any function returns a non-zero value, an error has occured.
    */
typedef enum vg_lite_error
{
    VG_LITE_SUCCESS = 0,        /*! Success. */
    VG_LITE_INVALID_ARGUMENT,   /*! An invalid argument was specified. */
    VG_LITE_OUT_OF_MEMORY,      /*! Out of memory. */
    VG_LITE_NO_CONTEXT,         /*! No context or an unintialized context specified. */
    VG_LITE_TIMEOUT,            /*! A timeout has occured during a wait. */
    VG_LITE_OUT_OF_RESOURCES,   /*! Out of system resources. */
    VG_LITE_GENERIC_IO,         /*! Cannot communicate with the kernel driver. */
    VG_LITE_NOT_SUPPORT,        /*! Function call not supported. */
    VG_LITE_MULTI_THREAD_FAIL,  /*! Multi-thread/tasks fail. */
    VG_LITE_ALREADY_EXISTS,     /*! Object already exists */
    VG_LITE_NOT_ALIGNED,        /*! Data alignment error */
}
vg_lite_error_t;
#endif

#if !defined(VG_DRIVER_SINGLE_THREAD)
typedef enum vg_lite_buffer_signal
{
    VG_LITE_IDLE = 0,        /*! Buffer available. */
    VG_LITE_HW_FINISHED,     /*! HW has completed command buffer. */
    VG_LITE_IN_QUEUE,        /*! Buffer has been send to queue. */
}
vg_lite_buffer_signal_t;
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

typedef enum vg_lite_kernel_counter
{
    /* Dont't touch the counter. */
    VG_LITE_NONE,

    /* Turn the counter on. */
    VG_LITE_ON,

    /* Turn the counter off. */
    VG_LITE_OFF,

    /* Query the counter and reset its values. */
    VG_LITE_QUERY,
}
vg_lite_kernel_counter_t;

typedef enum vg_lite_kernel_command
{
    /* Initialize the GPU. */
    VG_LITE_INITIALIZE,

    /* Terminate the GPU. */
    VG_LITE_TERMINATE,

    /* Allocate memory. */
    VG_LITE_ALLOCATE,

    /* Free memory. */
    VG_LITE_FREE,

    /* Submit a command buffer to the GPU. */
    VG_LITE_SUBMIT,

    /* Wait for the GPU to be completed. */
    VG_LITE_WAIT,

    /* Reset the GPU. */
    VG_LITE_RESET,

    /* Debug commands. */
    VG_LITE_DEBUG,

    /* Map memory. */
    VG_LITE_MAP,

    /* Unmap memory. */
    VG_LITE_UNMAP,

    /* Check info. */
    VG_LITE_CHECK,

    /* Query mem. */
    VG_LITE_QUERY_MEM,

#if !defined(VG_DRIVER_SINGLE_THREAD)
    /* Mutex lock. */
    VG_LITE_LOCK,

    /* Mutex unlock. */
    VG_LITE_UNLOCK,

    /* query context switch. */
    VG_LITE_QUERY_CONTEXT_SWITCH,
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

}
vg_lite_kernel_command_t;

struct vg_lite_kernel_context {
    /* Command buffer. */
    void      * command_buffer[CMDBUF_COUNT];
    void      * command_buffer_logical[CMDBUF_COUNT];
    uint32_t    command_buffer_physical[CMDBUF_COUNT];

#if !defined(VG_DRIVER_SINGLE_THREAD)
    vg_lite_os_async_event_t async_event[CMDBUF_COUNT];
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

    /* Tessellation buffer. */
    void      * tessellation_buffer;
    void      * tessellation_buffer_logical;
    uint32_t    tessellation_buffer_physical;

#if !defined(VG_DRIVER_SINGLE_THREAD)
    /* context buffer. */
    void      * context_buffer[CMDBUF_COUNT];
    void      * context_buffer_logical[CMDBUF_COUNT];
    uint32_t    context_buffer_physical[CMDBUF_COUNT];
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

};

/* Context structure. */
typedef struct vg_lite_kernel_context vg_lite_kernel_context_t;

typedef struct capabilities
{
    uint32_t tiled : 2;
    uint32_t l2_cache : 1;
}
capabilities_t;

typedef union vg_lite_capabilities
{
    capabilities_t cap;
    uint32_t       data;
}
vg_lite_capabilities_t;

typedef struct vg_lite_kernel_initialize
{
    /* Command buffer size. */
    uint32_t command_buffer_size;

#if !defined(VG_DRIVER_SINGLE_THREAD)
    /* Context buffer size. */
    uint32_t context_buffer_size;
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

    /* Tessellation buffer width. */
    int32_t tessellation_width;

    /* Tessellation buffer height. */
    int32_t tessellation_height;

    /* OUTPUT */

    /* Context pointer. */
    vg_lite_kernel_context_t * context;

    /* Capabilities. */
    vg_lite_capabilities_t capabilities;

    /* Allocated command buffer. */
    void * command_buffer[CMDBUF_COUNT];

    /* GPU address for command buffer. */
    uint32_t command_buffer_gpu[CMDBUF_COUNT];

#if !defined(VG_DRIVER_SINGLE_THREAD)
    /* Allocated context buffer. */
    void * context_buffer[CMDBUF_COUNT];

    /* GPU address for context buffer. */
    uint32_t context_buffer_gpu[CMDBUF_COUNT];
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

    /* GPU addresses for tesselation buffers. */
    uint32_t tessellation_buffer_gpu[3];

    /* Logic addresses for tessellation buffers: used by SW Tessellator. */
    uint8_t *tessellation_buffer_logic[3];

    /* Size of each level of the tesselation buffer. */
    uint32_t tessellation_buffer_size[3];

    /* Stride of the tessellation buffer. */
    uint32_t tessellation_stride;

    /* Width and height of tessellation buffer. */
    uint32_t tessellation_width_height;

    /* Tessellation config: shift. */
    uint32_t tessellation_shift;
}
vg_lite_kernel_initialize_t;

typedef struct vg_lite_kernel_terminate
{
    /* Context to terminate. */
    vg_lite_kernel_context_t * context;
}
vg_lite_kernel_terminate_t;

typedef struct vg_lite_kernel_allocate
{
    /* Number of bytes to allocate. */
    uint32_t bytes;

    /* Flag to indicate whether the allocated memory is contiguous or not. */
    int32_t contiguous;

    /* OUTPUT */

    /* Memory handle. */
    void * memory_handle;

    /* Allocated memory. */
    void * memory;

    /* GPU address of allocated memory. */
    uint32_t memory_gpu;
}
vg_lite_kernel_allocate_t;

typedef struct vg_lite_kernel_free
{
    /* Memory handle to free. */
    void * memory_handle;
}
vg_lite_kernel_free_t;

typedef struct vg_lite_kernel_submit
{
    /* Context to submit to. */
    vg_lite_kernel_context_t * context;

    /* Pointer to command buffer. */
    void * commands;

    /* Number of bytes in command buffer. */
    uint32_t command_size;

    /* Command Buffer ID. */
    uint32_t command_id;
}
vg_lite_kernel_submit_t;

typedef struct vg_lite_kernel_wait
{
    /* Context to wait for. */
    vg_lite_kernel_context_t * context;

    /* Timeout in milliseconds. */
    uint32_t timeout_ms;

#if defined(VG_DRIVER_SINGLE_THREAD)
    /* The event to wait. */
    uint32_t event_mask;

    /* The event(s) got after waiting. */
    uint32_t event_got;
#else
    /* Command Buffer ID. */
    uint32_t command_id;
#endif /* VG_DRIVER_SINGLE_THREAD */
}
vg_lite_kernel_wait_t;

typedef struct vg_lite_kernel_reset
{
    /* Context to reset. */
    vg_lite_kernel_context_t * context;
}
vg_lite_kernel_reset_t;

typedef struct vg_lite_kernel_debug
{
    /* Context to debug. */
    vg_lite_kernel_context_t * context;

    /* Bandwidth counter enabler. */
    vg_lite_kernel_counter_t bandwidth_counter;

    /* Pixel counter enabler. */
    vg_lite_kernel_counter_t pixel_counters;

    /* OUTPUT */

    /* Bandwidth counters:
     *  [0] - burst of 8.
     *  [1] - burst of 16.
     *  [2] - burst of 32.
     *  [3] - burst of 64.
     */
    uint32_t bandwidth[4];

    /* Pixel counters:.
     *  [0] - Number of tessellated pixels.
     *  [1] - Number of imaged pixels.
     *  [2] - Number of rendered pixels.
     */
    uint32_t pixels[3];
}
vg_lite_kernel_debug_t;

typedef struct vg_lite_kernel_map
{
    /* Number of bytes to map. */
    uint32_t bytes;

    /* Logical memory address or NULL. */
    void * logical;

    /* Physical memory address or 0. */
    uint32_t physical;

    /* OUTPUT */

    /* Memory handle for mapped memory. */
    void * memory_handle;

    /* GPU address of mapped memory. */
    uint32_t memory_gpu;
}
vg_lite_kernel_map_t;

typedef struct vg_lite_kernel_unmap
{
    /* Memory handle to unmap. */
    void * memory_handle;
}
vg_lite_kernel_unmap_t;

typedef struct vg_lite_kernel_info
{
    /* Register's address. */
    uint32_t addr;

    /* Check register info. */
    uint32_t reg;
}
vg_lite_kernel_info_t;

typedef struct vg_lite_kernel_mem
{
    uint32_t bytes;
}
vg_lite_kernel_mem_t;

#if !defined(VG_DRIVER_SINGLE_THREAD)
typedef struct vg_lite_kernel_context_switch
{
    uint8_t isContextSwitched;
    uint32_t context;
}
vg_lite_kernel_context_switch_t;
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

vg_lite_error_t vg_lite_kernel(vg_lite_kernel_command_t command, void * data);

#ifdef  __cplusplus
}
#endif
#endif /* _vg_lite_kernel_h_ */
