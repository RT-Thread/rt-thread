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
#if defined(__linux__) && !EMULATOR
#include <asm/uaccess.h>
#include <linux/version.h>
#endif

static int s_reference = 0;

#if !defined(VG_DRIVER_SINGLE_THREAD)
static int task_num = 0;
static vg_lite_kernel_initialize_t ts_initialize = {0};
static uint8_t ts_init = 0;
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

#if defined(VG_DRIVER_SINGLE_THREAD)

#define VG_LITE_OS_LOCK() VG_LITE_SUCCESS
#define VG_LITE_OS_UNLOCK()

#else

#define VG_LITE_OS_LOCK() vg_lite_os_lock()
#define VG_LITE_OS_UNLOCK() vg_lite_os_unlock()

#endif /* VG_DRIVER_SINGLE_THREAD */

static vg_lite_error_t do_terminate(vg_lite_kernel_terminate_t * data);

static void soft_reset(void);

static void gpu(int enable)
{
    vg_lite_hw_clock_control_t value;
    uint32_t          reset_timer = 2;
#ifdef VG_GPU_AUTO_CLOCK_GATING
    uint32_t          temp;
#endif /* VG_GPU_AUTO_CLOCK_GATING */
    const uint32_t    reset_timer_limit = 1000;

    if (enable) {
        /* Disable clock gating. */
        value.data = vg_lite_hal_peek(VG_LITE_HW_CLOCK_CONTROL);
        value.control.clock_gate = 0;
        vg_lite_hal_poke(VG_LITE_HW_CLOCK_CONTROL, value.data);
        vg_lite_hal_delay(1);

        /* Set clock speed. */
        value.control.scale = 64;
        value.control.scale_load = 1;
        vg_lite_hal_poke(VG_LITE_HW_CLOCK_CONTROL, value.data);
        vg_lite_hal_delay(1);
        value.control.scale_load = 0;
        vg_lite_hal_poke(VG_LITE_HW_CLOCK_CONTROL, value.data);
        vg_lite_hal_delay(5);

        do {
            /* Perform a soft reset. */
            soft_reset();
            vg_lite_hal_delay(reset_timer);
            reset_timer *= 2;   // If reset failed, try again with a longer wait. Need to check why if dead lopp happens here.
        } while (!VG_LITE_KERNEL_IS_GPU_IDLE());
#ifdef VG_GPU_AUTO_CLOCK_GATING
        temp = vg_lite_hal_peek(VG_LITE_HW_POWER_CONTROL);
        temp |= 0x1;
        vg_lite_hal_poke(VG_LITE_HW_POWER_CONTROL, temp);
        vg_lite_hal_delay(1);
#endif /* VG_GPU_AUTO_CLOCK_GATING */
    }
    else
    {
        while (!VG_LITE_KERNEL_IS_GPU_IDLE() &&
            (reset_timer < reset_timer_limit)   // Force shutdown if timeout.
            ) {
            vg_lite_hal_delay(reset_timer);
            reset_timer *= 2;
        }

        /* Set idle speed. */
        value.data = vg_lite_hal_peek(VG_LITE_HW_CLOCK_CONTROL);
        value.control.scale = 1;
        value.control.scale_load = 1;
        vg_lite_hal_poke(VG_LITE_HW_CLOCK_CONTROL, value.data);
        vg_lite_hal_delay(1);
        value.control.scale_load = 0;
        vg_lite_hal_poke(VG_LITE_HW_CLOCK_CONTROL, value.data);
        vg_lite_hal_delay(5);

        /* Enable clock gating. */
        value.control.clock_gate = 1;
        vg_lite_hal_poke(VG_LITE_HW_CLOCK_CONTROL, value.data);
        vg_lite_hal_delay(1);
    }
}

/* Initialize some customized modeuls [DDRLess]. */
static vg_lite_error_t init_3rd(vg_lite_kernel_initialize_t * data)
{
    vg_lite_error_t error = VG_LITE_SUCCESS;

    /* TODO: Init the YUV<->RGB converters. Reserved for SOC. */
/*    vg_lite_hal_poke(0x00514, data->yuv_pre);
      vg_lite_hal_poke(0x00518, data->yuv_post); */

    return error;
}

#if defined(VG_DRIVER_SINGLE_THREAD)
static vg_lite_error_t init_vglite(vg_lite_kernel_initialize_t * data)
{
    vg_lite_error_t error = VG_LITE_SUCCESS;

    vg_lite_kernel_context_t * context;
    uint32_t id;
    int      i;
    uint32_t chip_id = 0;

#if defined(__linux__) && !EMULATOR
    vg_lite_kernel_context_t __user * context_usr;
    vg_lite_kernel_context_t mycontext = { 0 };

    // Construct the context.
    context_usr = (vg_lite_kernel_context_t  __user *) data->context;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 0, 0)
     if (!access_ok(VERIFY_READ, context_usr, sizeof(*context_usr)) ||
       !access_ok(VERIFY_WRITE, context_usr, sizeof(*context_usr))) {
#else
     if (!access_ok(context_usr, sizeof(*context_usr)) ||
       !access_ok(context_usr, sizeof(*context_usr))) {
#endif
        /* Out of memory. */
        return VG_LITE_OUT_OF_MEMORY;
    }
    context = &mycontext;
#else
    // Construct the context.
    context = data->context;
    if (context == NULL)
    {
        /* Out of memory. */
        return VG_LITE_OUT_OF_MEMORY;
    }
#endif

    /* Zero out all pointers. */
    for (i = 0; i < CMDBUF_COUNT; i++){
        context->command_buffer[i]          = NULL;
        context->command_buffer_logical[i]  = NULL;
        context->command_buffer_physical[i] = 0;
    }
    context->tessellation_buffer            = NULL;
    context->tessellation_buffer_logical    = NULL;
    context->tessellation_buffer_physical   = 0;

    /* Increment reference counter. */
    if (s_reference++ == 0) {
        /* Initialize the SOC. */
        vg_lite_hal_initialize();

        /* Enable the GPU. */
        gpu(1);
    }

    /* Fill in hardware capabilities. */
    data->capabilities.data = 0;
    id = vg_lite_hal_peek(VG_LITE_HW_CHIP_ID);
    if (id >= 0x300) {
        data->capabilities.cap.l2_cache = 1;
    }

    /* Allocate the command buffer. */
    if (data->command_buffer_size) {
        int32_t i;
        for (i = 0; i < 2; i ++)
        {
            /* Allocate the memory. */
            error = vg_lite_hal_allocate_contiguous(data->command_buffer_size,
                                                                         &context->command_buffer_logical[i],
                                                                         &context->command_buffer_physical[i],
                                                                         &context->command_buffer[i]);
            if (error != VG_LITE_SUCCESS) {
                /* Free any allocated memory. */
                vg_lite_kernel_terminate_t terminate = { context };
                do_terminate(&terminate);

                /* Out of memory. */
                return error;
            }

            /* Return command buffer logical pointer and GPU address. */
            data->command_buffer[i] = context->command_buffer_logical[i];
            data->command_buffer_gpu[i] = context->command_buffer_physical[i];
        }
    }

    /* Allocate the tessellation buffer. */
    if ((data->tessellation_width > 0) && (data->tessellation_height > 0))
    {
        int width = data->tessellation_width;
        int height = 0;
        unsigned long stride, buffer_size, l1_size, l2_size;

        height = VG_LITE_ALIGN(data->tessellation_height, 16);

        chip_id = vg_lite_hal_peek(0x20);
        if(chip_id == GPU_CHIP_ID_GC355)
            width = VG_LITE_ALIGN(width, 128);
        /* Check if we can used tiled tessellation (128x16). */
        if (((width & 127) == 0) && ((height & 15) == 0)) {
            data->capabilities.cap.tiled = 0x3;
        } else {
            data->capabilities.cap.tiled = 0x2;
        }

        /* Compute tessellation buffer size. */
        stride = VG_LITE_ALIGN(width * 8, 64);
        buffer_size = VG_LITE_ALIGN(stride * height, 64);
        /* Each bit in the L1 cache represents 64 bytes of tessellation data. */
        l1_size = VG_LITE_ALIGN(VG_LITE_ALIGN(buffer_size / 64, 64) / 8, 64);
        /* Each bit in the L2 cache represents 32 bytes of L1 data. */
        l2_size = data->capabilities.cap.l2_cache ? VG_LITE_ALIGN(VG_LITE_ALIGN(l1_size / 32, 64) / 8, 64) : 0;

        /* Allocate the memory. */
        error = vg_lite_hal_allocate_contiguous(buffer_size + l1_size + l2_size,
                                                                       &context->tessellation_buffer_logical,
                                                                       &context->tessellation_buffer_physical,
                                                                       &context->tessellation_buffer);
        if (error != VG_LITE_SUCCESS) {
            /* Free any allocated memory. */
            vg_lite_kernel_terminate_t terminate = { context };
            do_terminate(&terminate);

            /* Out of memory. */
            return error;
        }

        /* Return the tessellation buffer pointers and GPU addresses. */
        data->tessellation_buffer_gpu[0] = context->tessellation_buffer_physical;
        data->tessellation_buffer_gpu[1] = context->tessellation_buffer_physical + buffer_size;
        data->tessellation_buffer_gpu[2] = (l2_size ? data->tessellation_buffer_gpu[1] + l1_size
                                            : data->tessellation_buffer_gpu[1]);
        data->tessellation_buffer_logic[0] = (uint8_t *)context->tessellation_buffer_logical;
        data->tessellation_buffer_logic[1] = data->tessellation_buffer_logic[0] + buffer_size;
        data->tessellation_buffer_logic[2] = (l2_size ? data->tessellation_buffer_logic[1] + l1_size
                                              : data->tessellation_buffer_logic[1]);
        data->tessellation_buffer_size[0] = buffer_size;
        data->tessellation_buffer_size[1] = l1_size;
        data->tessellation_buffer_size[2] = l2_size;

        data->tessellation_stride = stride;
        data->tessellation_width_height = width | (height << 16);
        data->tessellation_shift = 0;
    }

    /* Enable all interrupts. */
    vg_lite_hal_poke(VG_LITE_INTR_ENABLE, 0xFFFFFFFF);

#if defined(__linux__) && !EMULATOR
    if (copy_to_user(context_usr, context, sizeof(vg_lite_kernel_context_t)) != 0) {
      // Free any allocated memory.
      vg_lite_kernel_terminate_t terminate = { context };
      do_terminate(&terminate);

      return VG_LITE_NO_CONTEXT;
    }
#endif
    return error;
}
#else
static vg_lite_error_t init_vglite(vg_lite_kernel_initialize_t * data)
{
    vg_lite_error_t error = VG_LITE_SUCCESS;

    vg_lite_kernel_context_t * context;
    uint32_t id;
    int      i;
    uint32_t chip_id = 0;
    uint32_t semaphore_id = 0;

#if defined(__linux__) && !EMULATOR
    vg_lite_kernel_context_t __user * context_usr;
    vg_lite_kernel_context_t mycontext = { 0 };

    // Construct the context.
    context_usr = (vg_lite_kernel_context_t  __user *) data->context;
#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 0, 0)
     if (!access_ok(VERIFY_READ, context_usr, sizeof(*context_usr)) ||
       !access_ok(VERIFY_WRITE, context_usr, sizeof(*context_usr))) {
#else
     if (!access_ok(context_usr, sizeof(*context_usr)) ||
       !access_ok(context_usr, sizeof(*context_usr))) {
#endif
        /* Out of memory. */
        return VG_LITE_OUT_OF_MEMORY;
    }
    context = &mycontext;
#else
    // Construct the context.
    context = data->context;
    if (context == NULL)
    {
        /* Out of memory. */
        return VG_LITE_OUT_OF_MEMORY;
    }
#endif

    /* Zero out all pointers. */
    for (i = 0; i < CMDBUF_COUNT; i++){
        context->command_buffer[i]          = NULL;
        context->command_buffer_logical[i]  = NULL;
        context->command_buffer_physical[i] = 0;
    }
    context->tessellation_buffer            = NULL;
    context->tessellation_buffer_logical    = NULL;
    context->tessellation_buffer_physical   = 0;

    /* Increment reference counter. */
    if (s_reference++ == 0) {
        /* Initialize the SOC. */
        error = vg_lite_hal_initialize();
        if(error != VG_LITE_SUCCESS)
        {
            s_reference--;
            vg_lite_hal_free_os_heap();
            vg_lite_hal_deinitialize();

            return error;
        }

        /* Enable the GPU. */
        gpu(1);
    }
    else
    {
        while(!task_num)
        {
            vg_lite_hal_delay(5);
        }
    }

    if((error = (vg_lite_error_t)VG_LITE_OS_LOCK()) == VG_LITE_SUCCESS){
        ++task_num;
        for(semaphore_id = 0; semaphore_id < THREAD_LENGTH ; semaphore_id++)
        {
            if (vg_lite_os_init_event(&context->async_event[0],
                                 semaphore_id,
                                 VG_LITE_IDLE) == VG_LITE_SUCCESS)

            {
                for (i = 1; i < CMDBUF_COUNT; i++)
                    vg_lite_os_config_event(&context->async_event[i],
                                            semaphore_id,
                                            VG_LITE_IDLE);

                break;
            }
        }
        VG_LITE_OS_UNLOCK();
    }
    else
        return error;

    if(semaphore_id == THREAD_LENGTH)
        return VG_LITE_MULTI_THREAD_FAIL;

    /* Fill in hardware capabilities. */
    data->capabilities.data = 0;
    id = vg_lite_hal_peek(VG_LITE_HW_CHIP_ID);
    if (id >= 0x300) {
        data->capabilities.cap.l2_cache = 1;
    }

    /* Allocate the command buffer. */
    if (data->command_buffer_size) {
        int32_t i;
        for (i = 0; i < CMDBUF_COUNT; i ++)
        {
            /* Allocate the memory. */
            VG_LITE_OS_LOCK();
            error = vg_lite_hal_allocate_contiguous(data->command_buffer_size,
                                                                         &context->command_buffer_logical[i],
                                                                         &context->command_buffer_physical[i],
                                                                         &context->command_buffer[i]);
            VG_LITE_OS_UNLOCK();

            if (error != VG_LITE_SUCCESS) {
                /* Free any allocated memory. */
                vg_lite_kernel_terminate_t terminate = { context };
                do_terminate(&terminate);

                /* Out of memory. */
                return error;
            }

            /* Return command buffer logical pointer and GPU address. */
            data->command_buffer[i] = context->command_buffer_logical[i];
            data->command_buffer_gpu[i] = context->command_buffer_physical[i];
        }
    }

    /* Allocate the context buffer. */
    if (data->context_buffer_size) {
        int32_t i;
        for (i = 0; i < CMDBUF_COUNT; i ++)
        {
            /* Allocate the memory. */
            VG_LITE_OS_LOCK();
            error = vg_lite_hal_allocate_contiguous(data->context_buffer_size,
                                                                         &context->context_buffer_logical[i],
                                                                         &context->context_buffer_physical[i],
                                                                         &context->context_buffer[i]);
            VG_LITE_OS_UNLOCK();

            if (error != VG_LITE_SUCCESS) {
                /* Free any allocated memory. */
                vg_lite_kernel_terminate_t terminate = { context };
                do_terminate(&terminate);

                /* Out of memory. */
                return error;
            }

            /* Return context buffer logical pointer and GPU address. */
            data->context_buffer[i] = context->context_buffer_logical[i];
            data->context_buffer_gpu[i] = context->context_buffer_physical[i];
        }
    }


    /* Allocate the tessellation buffer. */
    if ((data->tessellation_width > 0) && (data->tessellation_height > 0))
    {
        int width = data->tessellation_width;
        int height = 0;
        height = VG_LITE_ALIGN(data->tessellation_height, 16);

        chip_id = vg_lite_hal_peek(0x20);
        if(chip_id == GPU_CHIP_ID_GC355)
            width = VG_LITE_ALIGN(width, 128);
        /* Check if we can used tiled tessellation (128x16). */
        if (((width & 127) == 0) && ((height & 15) == 0)) {
            data->capabilities.cap.tiled = 0x3;
        } else {
            data->capabilities.cap.tiled = 0x2;
        }

        if(ts_init++ == 0)
        {
            unsigned long stride, buffer_size, l1_size, l2_size;

            /* Compute tessellation buffer size. */
            stride = VG_LITE_ALIGN(width * 8, 64);
            buffer_size = VG_LITE_ALIGN(stride * height, 64);
            /* Each bit in the L1 cache represents 64 bytes of tessellation data. */
            l1_size = VG_LITE_ALIGN(VG_LITE_ALIGN(buffer_size / 64, 64) / 8, 64);
            /* Each bit in the L2 cache represents 32 bytes of L1 data. */
            l2_size = data->capabilities.cap.l2_cache ? VG_LITE_ALIGN(VG_LITE_ALIGN(l1_size / 32, 64) / 8, 64) : 0;

            /* Allocate the memory. */
            VG_LITE_OS_LOCK();
            error = vg_lite_hal_allocate_contiguous(buffer_size + l1_size + l2_size,
                                                                           &context->tessellation_buffer_logical,
                                                                           &context->tessellation_buffer_physical,
                                                                           &context->tessellation_buffer);
            VG_LITE_OS_UNLOCK();

            if (error != VG_LITE_SUCCESS) {
                /* Free any allocated memory. */
                vg_lite_kernel_terminate_t terminate = { context };
                do_terminate(&terminate);

                /* Out of memory. */
                return error;
            }

            /* Return the tessellation buffer pointers and GPU addresses. */
            ts_initialize.tessellation_buffer_gpu[0] = context->tessellation_buffer_physical;
            ts_initialize.tessellation_buffer_gpu[1] = context->tessellation_buffer_physical + buffer_size;
            ts_initialize.tessellation_buffer_gpu[2] = (l2_size ? ts_initialize.tessellation_buffer_gpu[1] + l1_size
                                                : ts_initialize.tessellation_buffer_gpu[1]);
            ts_initialize.tessellation_buffer_logic[0] = (uint8_t *)context->tessellation_buffer_logical;
            ts_initialize.tessellation_buffer_logic[1] = ts_initialize.tessellation_buffer_logic[0] + buffer_size;
            ts_initialize.tessellation_buffer_logic[2] = (l2_size ? ts_initialize.tessellation_buffer_logic[1] + l1_size
                                                  : ts_initialize.tessellation_buffer_logic[1]);
            ts_initialize.tessellation_buffer_size[0] = buffer_size;
            ts_initialize.tessellation_buffer_size[1] = l1_size;
            ts_initialize.tessellation_buffer_size[2] = l2_size;

            ts_initialize.tessellation_stride = stride;
            ts_initialize.tessellation_width_height = width | (height << 16);
            ts_initialize.tessellation_shift = 0;
        }
        data->tessellation_buffer_gpu[0] = ts_initialize.tessellation_buffer_gpu[0];
        data->tessellation_buffer_gpu[1] = ts_initialize.tessellation_buffer_gpu[1];
        data->tessellation_buffer_gpu[2] = ts_initialize.tessellation_buffer_gpu[2];
        data->tessellation_buffer_logic[0] = ts_initialize.tessellation_buffer_logic[0];
        data->tessellation_buffer_logic[1] = ts_initialize.tessellation_buffer_logic[1];
        data->tessellation_buffer_logic[2] = ts_initialize.tessellation_buffer_logic[2];
        data->tessellation_buffer_size[0] = ts_initialize.tessellation_buffer_size[0];
        data->tessellation_buffer_size[1] = ts_initialize.tessellation_buffer_size[1];
        data->tessellation_buffer_size[2] = ts_initialize.tessellation_buffer_size[2];

        data->tessellation_stride = ts_initialize.tessellation_stride;
        data->tessellation_width_height = ts_initialize.tessellation_width_height;
        data->tessellation_shift = ts_initialize.tessellation_shift;
    }

    if(task_num == 1)
        /* Enable all interrupts. */
        vg_lite_hal_poke(VG_LITE_INTR_ENABLE, 0xFFFFFFFF);

#if defined(__linux__) && !EMULATOR
    if (copy_to_user(context_usr, context, sizeof(vg_lite_kernel_context_t)) != 0) {
      // Free any allocated memory.
      vg_lite_kernel_terminate_t terminate = { context };
      do_terminate(&terminate);

      return VG_LITE_NO_CONTEXT;
    }
#endif
    return error;
}
#endif /* VG_DRIVER_SINGLE_THREAD */

static vg_lite_error_t do_initialize(vg_lite_kernel_initialize_t * data)
{
    vg_lite_error_t error = VG_LITE_SUCCESS;
    /* Free any allocated memory for the context. */
    do {
        error = init_vglite(data);
        if (error != VG_LITE_SUCCESS)
            break;

        error = init_3rd(data);
        if (error != VG_LITE_SUCCESS)
            break;
    } while (0);

    return error;
}

#if defined(VG_DRIVER_SINGLE_THREAD)
static vg_lite_error_t terminate_vglite(vg_lite_kernel_terminate_t * data)
{
    vg_lite_kernel_context_t *context = NULL;
#if defined(__linux__) && !EMULATOR
    vg_lite_kernel_context_t mycontext = {0};
    if (copy_from_user(&mycontext, data->context, sizeof(vg_lite_kernel_context_t)) != 0) {
      return VG_LITE_NO_CONTEXT;
    }
    context = &mycontext;
#else
    context = data->context;
#endif

    /* Free any allocated memory for the context. */
    if (context->command_buffer[0]) {
        /* Free the command buffer. */
        vg_lite_hal_free_contiguous(context->command_buffer[0]);
        context->command_buffer[0] = NULL;
    }

    if (context->command_buffer[1]) {
        /* Free the command buffer. */
        vg_lite_hal_free_contiguous(context->command_buffer[1]);
        context->command_buffer[1] = NULL;
    }

    if (context->tessellation_buffer) {
        /* Free the tessellation buffer. */
        vg_lite_hal_free_contiguous(context->tessellation_buffer);
        context->tessellation_buffer = NULL;
    }
    vg_lite_hal_free_os_heap();
    /* Decrement reference counter. */
    if (--s_reference == 0) {
        /* Disable the GPU. */
        gpu(0);

        /* De-initialize the SOC. */
        vg_lite_hal_deinitialize();
    }
#if defined(__linux__) && !EMULATOR
    if (copy_to_user((vg_lite_kernel_context_t  __user *) data->context,
        &mycontext, sizeof(vg_lite_kernel_context_t)) != 0) {
            return VG_LITE_NO_CONTEXT;
    }
#endif
    return VG_LITE_SUCCESS;
}
#else
static vg_lite_error_t terminate_vglite(vg_lite_kernel_terminate_t * data)
{
    vg_lite_kernel_context_t *context = NULL;
    vg_lite_error_t error = VG_LITE_SUCCESS;
    int32_t i;

#if defined(__linux__) && !EMULATOR
    vg_lite_kernel_context_t mycontext = {0};
    if (copy_from_user(&mycontext, data->context, sizeof(vg_lite_kernel_context_t)) != 0) {
      return VG_LITE_NO_CONTEXT;
    }
    context = &mycontext;
#else
    context = data->context;
#endif

    /* Free any allocated memory for the context. */
    if (context->command_buffer[0]) {
        /* Free the command buffer. */
        vg_lite_hal_free_contiguous(context->command_buffer[0]);
        context->command_buffer[0] = NULL;
    }

    if (context->command_buffer[1]) {
        /* Free the command buffer. */
        vg_lite_hal_free_contiguous(context->command_buffer[1]);
        context->command_buffer[1] = NULL;
    }

    if (context->context_buffer[0]) {
        /* Free the context buffer. */
        vg_lite_hal_free_contiguous(context->context_buffer[0]);
        context->context_buffer[0] = NULL;
    }

    if (context->context_buffer[1]) {
        /* Free the context buffer. */
        vg_lite_hal_free_contiguous(context->context_buffer[1]);
        context->context_buffer[1] = NULL;
    }

    if((error = (vg_lite_error_t)VG_LITE_OS_LOCK()) == VG_LITE_SUCCESS){
        --task_num;
        --s_reference;
        VG_LITE_OS_UNLOCK();
    }
    else
        return error;

    /* Delete all async events associated to command buffers */
    for (i = 0; i < CMDBUF_COUNT; i++)
        vg_lite_os_delete_event(&context->async_event[i]);

    if(task_num == 0){
        if (context->tessellation_buffer) {
            /* Free the tessellation buffer. */
            vg_lite_hal_free_contiguous(context->tessellation_buffer);
            context->tessellation_buffer = NULL;
        }
        ts_init = 0;
        /* Disable the GPU. */
        gpu(0);

        vg_lite_hal_free_os_heap();

        /* De-initialize the SOC. */
        vg_lite_hal_deinitialize();
    }

#if defined(__linux__) && !EMULATOR
    if (copy_to_user((vg_lite_kernel_context_t  __user *) data->context,
        &mycontext, sizeof(vg_lite_kernel_context_t)) != 0) {
            return VG_LITE_NO_CONTEXT;
    }
#endif
    return VG_LITE_SUCCESS;
}
#endif /* VG_DRIVER_SINGLE_THREAD */

static vg_lite_error_t terminate_3rd(vg_lite_kernel_terminate_t * data)
{
    /* TODO: Terminate the converters. */

    return VG_LITE_SUCCESS;
}

static vg_lite_error_t do_terminate(vg_lite_kernel_terminate_t * data)
{
    terminate_vglite(data);
    terminate_3rd(data);

    return VG_LITE_SUCCESS;
}

static vg_lite_error_t do_allocate(vg_lite_kernel_allocate_t * data)
{
    vg_lite_error_t error;

    if((error = (vg_lite_error_t)VG_LITE_OS_LOCK()) == VG_LITE_SUCCESS)
    {
        error = vg_lite_hal_allocate_contiguous(data->bytes, &data->memory, &data->memory_gpu, &data->memory_handle);
        VG_LITE_OS_UNLOCK();
    }

    return error;
}

static vg_lite_error_t do_free(vg_lite_kernel_free_t * data)
{
    vg_lite_hal_free_contiguous(data->memory_handle);

    return VG_LITE_SUCCESS;
}

#if defined(VG_DRIVER_SINGLE_THREAD)
static vg_lite_error_t do_submit(vg_lite_kernel_submit_t * data)
{
    uint32_t offset;
    vg_lite_kernel_context_t *context = NULL;
    uint32_t physical = data->context->command_buffer_physical[data->command_id];

#if defined(__linux__) && !EMULATOR
    vg_lite_kernel_context_t mycontext = { 0 };

    if (copy_from_user(&mycontext, data->context, sizeof(vg_lite_kernel_context_t)) != 0) {
      return VG_LITE_NO_CONTEXT;
    }
    context = &mycontext;
    physical = context->command_buffer_physical[data->command_id];
#else
    context = data->context;
    if (context == NULL)
    {
        return VG_LITE_NO_CONTEXT;
    }
#endif
    /* Perform a memory barrier. */
    vg_lite_hal_barrier();

    offset = (uint8_t *) data->commands - (uint8_t *)context->command_buffer_logical[data->command_id];

#if defined(PRINT_COMMAND_BUFFER)
    int i = 0;
    for(i=0;i < (peek_queue->cmd_size + 3) / 4; i++)
    {
        if(i % 4 == 0)
            printf("\r\n");
        printf("0x%08x ",((uint32_t*)(peek_queue->cmd_physical + peek_queue->cmd_offset))[i]);
    }
#endif

    /* Write the registers to kick off the command execution (CMDBUF_SIZE). */
    vg_lite_hal_poke(VG_LITE_HW_CMDBUF_ADDRESS, physical + offset);
    vg_lite_hal_poke(VG_LITE_HW_CMDBUF_SIZE, (data->command_size + 7) / 8);

    return VG_LITE_SUCCESS;
}

static vg_lite_error_t do_wait(vg_lite_kernel_wait_t * data)
{
    /* Wait for interrupt. */
    if (!vg_lite_hal_wait_interrupt(data->timeout_ms, data->event_mask, &data->event_got)) {
        /* Timeout. */
#if defined(PRINT_DEBUG_REGISTER)
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
        return VG_LITE_TIMEOUT;
    }

    return VG_LITE_SUCCESS;
}
#else
static vg_lite_error_t do_submit(vg_lite_kernel_submit_t * data)
{
    vg_lite_error_t error;
    uint32_t offset;
    vg_lite_kernel_context_t *context = NULL;
    uint32_t physical;

#if defined(__linux__) && !EMULATOR
    vg_lite_kernel_context_t mycontext = { 0 };

    if (copy_from_user(&mycontext, data->context, sizeof(vg_lite_kernel_context_t)) != 0) {
      return VG_LITE_NO_CONTEXT;
    }
    context = &mycontext;
    physical = context->command_buffer_physical[data->command_id];
#else
    context = data->context;
    if (context == NULL)
    {
        return VG_LITE_NO_CONTEXT;
    }
#endif
    /* Perform a memory barrier. */
    vg_lite_hal_barrier();

    physical = data->context->command_buffer_physical[data->command_id];
    offset = (uint8_t *) data->commands - (uint8_t *)context->command_buffer_logical[data->command_id];

    /* Send the current command buffer to the command queue. */
    error = vg_lite_hal_submit((uint32_t)context, physical, offset, data->command_size,
                               &data->context->async_event[data->command_id]);
    if(error != VG_LITE_SUCCESS)
        return error;

    return VG_LITE_SUCCESS;
}

static vg_lite_error_t do_wait(vg_lite_kernel_wait_t * data)
{
    vg_lite_error_t error;
    /* Wait for the signal of current command buffer to 1. */
    error = vg_lite_hal_wait(data->timeout_ms,
                             &data->context->async_event[data->command_id]);

    return error;
}
#endif /* VG_DRIVER_SINGLE_THREAD */

static vg_lite_error_t do_reset(void)
{
    /* Disable and enable the GPU. */
    gpu(1);
    vg_lite_hal_poke(VG_LITE_INTR_ENABLE, 0xFFFFFFFF);

    return VG_LITE_SUCCESS;
}

static vg_lite_error_t do_debug(void)
{
    return VG_LITE_SUCCESS;
}

static vg_lite_error_t do_map(vg_lite_kernel_map_t * data)
{    data->memory_handle = vg_lite_hal_map(data->bytes, data->logical, data->physical, &data->memory_gpu);
    if (data->memory_handle == NULL)
    {
        return VG_LITE_OUT_OF_RESOURCES;
    }

    return VG_LITE_SUCCESS;
}

static vg_lite_error_t do_unmap(vg_lite_kernel_unmap_t * data)
{
    vg_lite_hal_unmap(data->memory_handle);

    return VG_LITE_SUCCESS;
}

static vg_lite_error_t do_peek(vg_lite_kernel_info_t * data)
{
    data->reg = vg_lite_hal_peek(data->addr);

    return VG_LITE_SUCCESS;
}

static vg_lite_error_t do_query_mem(vg_lite_kernel_mem_t * data)
{
    vg_lite_error_t error = VG_LITE_SUCCESS;
    error = vg_lite_hal_query_mem(data);

    return error;
}

#if !defined(VG_DRIVER_SINGLE_THREAD)
static vg_lite_error_t do_query_context_switch(vg_lite_kernel_context_switch_t * data)
{
    data->isContextSwitched = vg_lite_os_query_context_switch(data->context);
    return VG_LITE_SUCCESS;
}
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

static void soft_reset(void)
{
    vg_lite_hw_clock_control_t value;
    value.data = vg_lite_hal_peek(VG_LITE_HW_CLOCK_CONTROL);

    /* Perform a soft reset. */
    value.control.isolate = 1;
    vg_lite_hal_poke(VG_LITE_HW_CLOCK_CONTROL, value.data);
    value.control.soft_reset = 1;
    vg_lite_hal_poke(VG_LITE_HW_CLOCK_CONTROL, value.data);
    vg_lite_hal_delay(5);
    value.control.soft_reset = 0;
    vg_lite_hal_poke(VG_LITE_HW_CLOCK_CONTROL, value.data);
    value.control.isolate = 0;
    vg_lite_hal_poke(VG_LITE_HW_CLOCK_CONTROL, value.data);
}

#if !defined(VG_DRIVER_SINGLE_THREAD)
static vg_lite_error_t do_mutex_lock()
{
    return (vg_lite_error_t)VG_LITE_OS_LOCK();
}

static vg_lite_error_t do_mutex_unlock()
{
    return (vg_lite_error_t)VG_LITE_OS_UNLOCK();
}
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

vg_lite_error_t vg_lite_kernel(vg_lite_kernel_command_t command, void * data)
{
    /* Dispatch on command. */
    switch (command) {
        case VG_LITE_INITIALIZE:
            /* Initialize the context. */
            return do_initialize(data);

        case VG_LITE_TERMINATE:
            /* Terminate the context. */
            return do_terminate(data);

        case VG_LITE_ALLOCATE:
            /* Allocate contiguous memory. */
            return do_allocate(data);

        case VG_LITE_FREE:
            /* Free contiguous memory. */
            return do_free(data);

        case VG_LITE_SUBMIT:
            /* Submit a command buffer. */
            return do_submit(data);

        case VG_LITE_WAIT:
            /* Wait for the GPU. */
            return do_wait(data);

        case VG_LITE_RESET:
            /* Reset the GPU. */
            return do_reset();

        case VG_LITE_DEBUG:
            /* Perform debugging features. */
            return do_debug();

        case VG_LITE_MAP:
            /* Map some memory. */
            return do_map(data);

        case VG_LITE_UNMAP:
            /* Unmap some memory. */
            return do_unmap(data);

            /* Get register info. */
        case VG_LITE_CHECK:
            /* Get register value. */
            return do_peek(data);

        case VG_LITE_QUERY_MEM:
            return do_query_mem(data);

#if !defined(VG_DRIVER_SINGLE_THREAD)
        case VG_LITE_LOCK:
            /* Mutex lock */
            return do_mutex_lock();

        case VG_LITE_UNLOCK:
            /* Mutex unlock */
            return do_mutex_unlock();

        case VG_LITE_QUERY_CONTEXT_SWITCH:
            /* query context switch */
            return do_query_context_switch(data);
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

        default:
            break;
    }

    /* Invalid command. */
    return VG_LITE_INVALID_ARGUMENT;
}
