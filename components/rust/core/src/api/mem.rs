/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-10     foxglove     memory management API
 */

use crate::bindings::*;
use core::ffi::c_void;

/// Safe memory allocation
/// 
/// # Arguments
/// * `bytes` - Number of bytes to allocate
/// 
/// # Returns
/// * `Some(ptr)` - Valid pointer to allocated memory
/// * `None` - Allocation failed
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

/// Safe memory allocation with zero initialization
/// 
/// # Arguments
/// * `count` - Number of elements
/// * `size` - Size of each element in bytes
/// 
/// # Returns
/// * `Some(ptr)` - Valid pointer to zero-initialized memory
/// * `None` - Allocation failed
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

/// Safe aligned memory allocation
/// 
/// # Arguments
/// * `bytes` - Number of bytes to allocate
/// * `align` - Alignment requirement (must be power of 2)
/// 
/// # Returns
/// * `Some(ptr)` - Valid aligned pointer to allocated memory
/// * `None` - Allocation failed or invalid alignment
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

/// Safe memory reallocation
/// 
/// # Arguments
/// * `ptr` - Existing pointer (can be null)
/// * `new_size` - New size in bytes
/// 
/// # Returns
/// * `Some(ptr)` - Valid pointer to reallocated memory
/// * `None` - Reallocation failed
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

/// Safe memory deallocation
/// 
/// # Arguments
/// * `ptr` - Pointer to memory to free (null pointers are safely ignored)
pub fn mem_free(ptr: *mut c_void) {
    if !ptr.is_null() {
        unsafe { rt_free(ptr) };
    }
}

/// Safe aligned memory deallocation
/// 
/// # Arguments
/// * `ptr` - Pointer to aligned memory to free (null pointers are safely ignored)
pub fn mem_free_aligned(ptr: *mut c_void) {
    if !ptr.is_null() {
        unsafe { rt_free_align(ptr) };
    }
}

/// Unsafe raw memory allocation (for compatibility)
/// 
/// # Safety
/// Caller must ensure proper error handling and memory management
pub unsafe fn mem_alloc_raw(bytes: usize) -> *mut c_void {
    rt_malloc(bytes as rt_size_t)
}

/// Memory allocation result type for better error handling
pub type MemResult<T> = Result<T, MemError>;

/// Memory allocation error types
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum MemError {
    /// Out of memory
    OutOfMemory,
    /// Invalid size (zero or too large)
    InvalidSize,
    /// Invalid alignment (not power of 2)
    InvalidAlignment,
    /// Null pointer passed where valid pointer expected
    NullPointer,
}

/// Safe typed memory allocation
/// 
/// # Type Parameters
/// * `T` - Type to allocate
/// 
/// # Returns
/// * `Ok(ptr)` - Valid pointer to allocated memory for type T
/// * `Err(error)` - Allocation error
pub fn mem_alloc_typed<T>() -> MemResult<*mut T> {
    let size = core::mem::size_of::<T>();
    if size == 0 {
        return Err(MemError::InvalidSize);
    }
    
    match mem_alloc(size) {
        Some(ptr) => Ok(ptr as *mut T),
        None => Err(MemError::OutOfMemory),
    }
}

/// Safe typed array allocation
/// 
/// # Type Parameters
/// * `T` - Element type
/// 
/// # Arguments
/// * `count` - Number of elements
/// 
/// # Returns
/// * `Ok(ptr)` - Valid pointer to allocated array
/// * `Err(error)` - Allocation error
pub fn mem_alloc_array<T>(count: usize) -> MemResult<*mut T> {
    if count == 0 {
        return Err(MemError::InvalidSize);
    }
    
    let size = core::mem::size_of::<T>()
        .checked_mul(count)
        .ok_or(MemError::InvalidSize)?;
    
    match mem_alloc(size) {
        Some(ptr) => Ok(ptr as *mut T),
        None => Err(MemError::OutOfMemory),
    }
}

/// Safe typed array allocation with zero initialization
/// 
/// # Type Parameters
/// * `T` - Element type
/// 
/// # Arguments
/// * `count` - Number of elements
/// 
/// # Returns
/// * `Ok(ptr)` - Valid pointer to zero-initialized array
/// * `Err(error)` - Allocation error
pub fn mem_calloc_array<T>(count: usize) -> MemResult<*mut T> {
    if count == 0 {
        return Err(MemError::InvalidSize);
    }
    
    let size = core::mem::size_of::<T>();
    match mem_calloc(count, size) {
        Some(ptr) => Ok(ptr as *mut T),
        None => Err(MemError::OutOfMemory),
    }
}