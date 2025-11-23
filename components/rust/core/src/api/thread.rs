/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-10     foxglove     Thread API
 */
use super::base::*;
use crate::bindings::*;
use core::ptr;
use core::ffi::c_void;
use alloc::ffi::CString;

/* Thread handle, defined by RT-Thread C code */
pub type APIRawThread = rt_thread_t;
/* Thread entry function, defined by RT-Thread C code */
pub type ThreadEntry = extern "C" fn(parameter: *mut c_void);

#[inline]
pub fn thread_create(
    name: &str,
    entry: ThreadEntry,
    param: *mut c_void,
    stack_size: u32,
    priority: u8,
    tick: u32,
) -> Option<APIRawThread> {
    let name = CString::new(name).unwrap();
    let raw;
    unsafe {
        raw = rt_thread_create(
            name.as_ptr(),
            entry,
            param,
            stack_size as crate::bindings::librt::rt_size_t,
            priority,
            tick,
        );
    }
    if raw == ptr::null_mut() {
        None
    } else {
        Some(raw)
    }
}

#[inline]
pub fn thread_delete(th: APIRawThread) -> RttCResult {
    unsafe { rt_thread_delete(th).into() }
}

#[inline]
pub fn thread_self() -> Option<APIRawThread> {
    let ret;
    unsafe {
        ret = rt_thread_self();
    }
    if ret == ptr::null_mut() {
        None
    } else {
        Some(ret)
    }
}

#[inline]
pub fn thread_startup(th: APIRawThread) -> RttCResult {
    unsafe { rt_thread_startup(th).into() }
}

#[inline]
pub fn thread_delay(ticks: usize) -> RttCResult {
    unsafe { rt_thread_delay(ticks as _).into() }
}

#[inline]
pub fn thread_m_delay(ms: i32) -> RttCResult {
    unsafe { rt_thread_mdelay(ms as _).into() }
}

#[inline]
pub fn thread_yield() {
    unsafe {
        rt_thread_yield();
    }
}

#[inline]
pub fn thread_suspend(th: APIRawThread) -> RttCResult {
    unsafe { rt_thread_suspend(th).into() }
}

#[inline]
pub fn thread_resume(th: APIRawThread) -> RttCResult {
    unsafe { rt_thread_resume(th).into() }
}
