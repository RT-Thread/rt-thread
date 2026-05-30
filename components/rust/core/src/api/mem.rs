/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-10     foxglove     memory management API
 */

use crate::bindings::*;
use core::ffi::c_void;

pub fn mem_alloc(bytes: usize) -> Option<*mut c_void> {
    if bytes == 0 {
        return None;
    }
    
    let ptr = unsafe { rt_malloc(bytes as rt_size_t) };
    if ptr.is_null() {
        None
    } else {
        Some(ptr)
    }
}

pub fn mem_calloc(count: usize, size: usize) -> Option<*mut c_void> {
    if count == 0 || size == 0 {
        return None;
    }
    
    let ptr = unsafe { rt_calloc(count as rt_size_t, size as rt_size_t) };
    if ptr.is_null() {
        None
    } else {
        Some(ptr)
    }
}

pub fn mem_alloc_aligned(bytes: usize, align: usize) -> Option<*mut c_void> {
    if bytes == 0 || align == 0 || !align.is_power_of_two() {
        return None;
    }
    
    let ptr = unsafe { rt_malloc_align(bytes as rt_size_t, align as rt_size_t) };
    if ptr.is_null() {
        None
    } else {
        Some(ptr)
    }
}

pub fn mem_realloc(ptr: *mut c_void, new_size: usize) -> Option<*mut c_void> {
    if new_size == 0 {
        if !ptr.is_null() {
            mem_free(ptr);
        }
        return None;
    }
    
    let new_ptr = unsafe { rt_realloc(ptr, new_size as rt_size_t) };
    if new_ptr.is_null() {
        None
    } else {
        Some(new_ptr)
    }
}

pub fn mem_free(ptr: *mut c_void) {
    if !ptr.is_null() {
        unsafe { rt_free(ptr) };
    }
}

pub fn mem_free_aligned(ptr: *mut c_void) {
    if !ptr.is_null() {
        unsafe { rt_free_align(ptr) };
    }
}
