/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-10     foxglove     RT-Thread GlobalAlloc implementation
 */

use crate::api::mem::{mem_alloc, mem_alloc_aligned, mem_free, mem_free_aligned, mem_realloc};
use core::alloc::{GlobalAlloc, Layout};
use crate::panic::panic_on_atomic_context;
use core::ptr;
use core::ffi::c_void;

pub struct RttAlloc;
unsafe impl GlobalAlloc for RttAlloc {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        panic_on_atomic_context("alloc");
        let size = layout.size();
        let align = layout.align();
        
        /* Handle zero-sized allocations */
        if size == 0 {
            return ptr::null_mut();
        }
        
        /* Use aligned allocation if alignment is greater than default
         * RT-Thread's default alignment is typically 4 or 8 bytes */
        if align > 8 {
            match mem_alloc_aligned(size, align) {
                Some(ptr) => ptr as *mut u8,
                None => ptr::null_mut(),
            }
        } else {
            match mem_alloc(size) {
                Some(ptr) => ptr as *mut u8,
                None => ptr::null_mut(),
            }
        }
    }
    
    unsafe fn dealloc(&self, ptr: *mut u8, layout: Layout) {
        panic_on_atomic_context("dealloc");
        if ptr.is_null() {
            return;
        }
        
        let align = layout.align();
        
        /* Use aligned deallocation if the original allocation was aligned */
        if align > 8 {
            mem_free_aligned(ptr as *mut c_void);
        } else {
            mem_free(ptr as *mut c_void);
        }
    }
    
    unsafe fn realloc(&self, ptr: *mut u8, layout: Layout, new_size: usize) -> *mut u8 {
        panic_on_atomic_context("realloc");
        /* Handle zero-sized new allocation */  
        if new_size == 0 {
            self.dealloc(ptr, layout);
            return ptr::null_mut();
        }
        
        /* Handle null pointer (equivalent to alloc) */
        if ptr.is_null() {
            let new_layout = Layout::from_size_align_unchecked(new_size, layout.align());
            return self.alloc(new_layout);
        }
        
        /* For aligned allocations, we need to handle realloc manually
         * since RT-Thread's rt_realloc may not preserve alignment */
        let align = layout.align();
        if align > 8 {
            let new_ptr = match mem_alloc_aligned(new_size, align) {
                Some(ptr) => ptr as *mut u8,
                None => return ptr::null_mut(),
            };
            
            /* Copy data from old to new */ 
            let copy_size = core::cmp::min(layout.size(), new_size);
            ptr::copy_nonoverlapping(ptr, new_ptr, copy_size);
            
            mem_free_aligned(ptr as *mut c_void);
            
            new_ptr
        } else {
            match mem_realloc(ptr as *mut c_void, new_size) {
                Some(new_ptr) => new_ptr as *mut u8,
                None => ptr::null_mut(),
            }
        }
    }
}