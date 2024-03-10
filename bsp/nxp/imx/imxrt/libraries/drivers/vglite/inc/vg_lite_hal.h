/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright 2012 - 2020 Vivante Corporation, Santa Clara, California.
*    All Rights Reserved.
*
*    Permission is hereby granted, free of charge, to any person obtaining
*    a copy of this software and associated documentation files (the
*    'Software'), to deal in the Software without restriction, including
*    without limitation the rights to use, copy, modify, merge, publish,
*    distribute, sub license, and/or sell copies of the Software, and to
*    permit persons to whom the Software is furnished to do so, subject
*    to the following conditions:
*
*    The above copyright notice and this permission notice (including the
*    next paragraph) shall be included in all copies or substantial
*    portions of the Software.
*
*    THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
*    IN NO EVENT SHALL VIVANTE AND/OR ITS SUPPLIERS BE LIABLE FOR ANY
*    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
*    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#ifndef _vg_lite_hal_h_
#define _vg_lite_hal_h_

#include "vg_lite_platform.h"
#include "vg_lite_os.h"
#include "vg_lite_kernel.h"

#define VGLITE_MEM_ALIGNMENT    128
#define THREAD_LENGTH             8

#ifdef __cplusplus
extern "C" {
#endif

/*!
 @brief Wait a number of milliseconds.

 @discussion
 The VGLite hardware requires some waiting when changing clock frequencies or issuing a reset. This is the wrapper function
 for the delay function.

 @param milliseconds
 The number of milliseconds to wait.
 */
void vg_lite_hal_delay(uint32_t milliseconds);

/*!
 @brief Initialize the hardware.

 @discussion
 The VGLite kernel knows how to program its own hardware, but in any SOC there might be additional control required for
 turning on the power or initializing the clocks. This function gets called by the VGLite kernel before the VGLite graphics
 hardware gets initialized by the VGLite kernel itself and allows for SOC power management control.

 The implementer should make sure that on exit of this function the power and clock to the VGLite graphics hardware is
 turned on and stable.
 */
vg_lite_error_t vg_lite_hal_initialize(void);

/*!
 @brief Uninitialize the hardware.

 @discussion
 The VGLite kernel knows how to program its own hardware, but in any SOC there might be additional control required for
 turning off the power or uninitializing the clocks. This function gets called by the VGLite kernel after the VGLite
 graphics hardware gets uninitialized by the VGLite kernel itself and allows for SOC power management control.

 On exit of this function it is okay to have the power and/or clock to the VGLite graphics hardware turned off.
 */
void vg_lite_hal_deinitialize(void);

/*!
 @brief Allocate contiguous video memory.

 @discussion
 Any memory the VGLite graphics hardware will see should be allocated as contiguous memory. Any allocated memory will be
 addressed through an opaque handle, usually a pointer to an opaque structure. The porting layer can put any information it
 needs inside this structure.

 @param size
 The number of bytes to allocate.

 @param logical
 A pointer to a variable that will receive the logical address of the allocated memory for the CPU.

 @param gpu
 A pointer to a variable that will receive the physical address of the allocated memory for the VGLite graphics hardware.

 @result
 A pointer to an opaque structure that will be used as the memory handle. <code>NULL</code> should be returned if there is not
 enough memory.
 */
vg_lite_error_t vg_lite_hal_allocate_contiguous(unsigned long size, void ** logical, uint32_t * physical,void ** node);

/*!
 @brief Free contiguous video memory.

 @discussion
 Free the memory allocated by {@link vg_lite_hal_allocate_contiguous}. After this function returns, the associated memory
 handle is no longer a valid handle.

 @param memory_handle
 A pointer to an opaque structure returned by {@link vg_lite_hal_allocate_contiguous}.
 */
void vg_lite_hal_free_contiguous(void * memory_handle);

/*!
 @brief remove unfree node when continuously allocate buffer without free buffer.

 @discussion
 Free the node allocated by {@link kmalloc}. After this function returns, the associated memory
 handle is no longer a valid handle.
 */
void vg_lite_hal_free_os_heap(void);

/*!
 @brief Map contiguous logical or physical memory into the VGLite graphics hardware space.

 @discussion
 Any memory, like a frame buffer or some pre-allocated image or path data, needs to be mapped into the VGLite graphics
 hardware address space and wrapped by a memory handle. This allows the VGLite graphics hardware access that memory
 directly.

 Either a logical or a physical address should be passed in to map.

 @param size
 The number of bytes to map.

 @param logical
 The logical address of the memory region to map or <code>NULL</code> if the logical address is not known.

 @param physical
 The physical address of the memory region to map if <code>logical</code> is <code>NULL</code>.

 @param gpu
 A pointer to a variable that will receive the VGLite graphics hardware addressable address of the mapped region.

 @result
 A pointer to an opaque structure that will be used as the memory handle. <code>NULL</code> should be returned if there is
 not enough system resources to map the region.
 */
void * vg_lite_hal_map(unsigned long size, void * logical, uint32_t physical, uint32_t * gpu);

/*!
 @brief Unmap a previously mapped region.

 @discussion
 If a mapped region by {@link vg_lite_hal_map} is no longer needed, it should be unmapped to free up any allocated system
 resources used when mapping the region.

 @param memory_handle
 A pointer to an opaque structure returned by {@link vg_lite_hal_map}.
 */
void vg_lite_hal_unmap(void * memory_handle);

/*!
 @brief Execute a memory barrier.

 @discussion
 Some systems require a a memory barrier to make sure all store operations in the CPU have been handled. This is the wrapper
 function for a memory barrier.
 */
void vg_lite_hal_barrier(void);

/*!
 @brief Read data from a register from the VGLite graphics hardware.

 @discussion
 In order to communicate with the VGLite graphics hardware, the kernel needs to read and write to some hardware registers.
 In each SOC those registers could be allocated at a different space in the physical memory map.

 @param address
 The relative address of the VGLite graphics hardware register to read from.

 @result
 The 32-bit value returned from reading the register.
 */
uint32_t vg_lite_hal_peek(uint32_t address);

/*!
 @brief Write data to a register from the VGLite graphics hardware.

 @discussion
 In order to communicate with the VGLite graphics hardware, the kernel needs to read and write to some hardware registers.
 In each SOC those registers could be allocated at a different space in the physical memory map.

 @param address
 The relative address of the VGLite graphics hardware register to write to.

 @param data
 The data to write to the VGLite graphics hardware register.
 */
void vg_lite_hal_poke(uint32_t address, uint32_t data);

/*!
 @brief query the remaining allocate contiguous video memory.

 @param data
 The data to get the remaining allocate contiguous video memory bytes.
 */
vg_lite_error_t vg_lite_hal_query_mem(vg_lite_kernel_mem_t *mem);

/*!
 @brief Wait until an interrupt from the VGLite graphics hardware has been received.

 @discussion
 Currently, the VGLite API is synchronous. This means that after each call it will wait until the VGLite graphics hardware
 has completed. The VGLite graphics hardware will send an interrupt when it is finished, and this function will wait until
 that interrupt has been received by the operating system.

 A timeout value is specified in order if the kernel wants to wait for a specific number of milliseconds fir the interrupt to
 occur. If the interrupt does not occur in the specified timeout, a timeout error will be returned.

 @param timeout
 The number of milliseconds to wait for the interrupt before returning a timeout error. If <code>timeout = 0xFFFFFFFF</code>
 then {@link vg_lite_hal_wait_interrupt} will wait forever for the interrupt.

 @param mask
 Irq event mask to wait for.

 @result
 A boolean value indicating whether the interrupt was received (1) or not (0).
 */
int32_t vg_lite_hal_wait_interrupt(uint32_t timeout, uint32_t mask, uint32_t * value);

#if !defined(VG_DRIVER_SINGLE_THREAD)
/*!
 @brief Submit the current command buffer to the command queue.

 @param context
 Address of kernel context.

 @param physical
 Current command buffer physical address.

 @param offset
 Current command buffer offset.

 @param size
 Current command buffer size.

 @param event
 The async event to use to track the response for this request.
 */
vg_lite_error_t vg_lite_hal_submit(uint32_t context,uint32_t physical, uint32_t offset, uint32_t size,  vg_lite_os_async_event_t *event);

/*!
 @brief Wait for the current command buffer to be executed.

 @param timeout
 Timeout in milliseconds.

 @param event
 The async event to wait for. If the event's signal is 1, the current command
 buffer has been executed.
 */
vg_lite_error_t vg_lite_hal_wait(uint32_t timeout, vg_lite_os_async_event_t *event);
#endif /* not defined(VG_DRIVER_SINGLE_THREAD) */

#ifdef __cplusplus
}
#endif
#endif /* _vg_lite_hal_h_ */
