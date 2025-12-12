/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-10     foxglove     Semaphore API
 */
use crate::api::RttCResult;
use crate::bindings::*;
use core::ptr;
use alloc::ffi::CString;

pub type APIRawSem = rt_sem_t;

 #[inline]
pub(crate) fn semaphore_create(name: &str) -> Option<APIRawSem> {
    let s = CString::new(name).unwrap();
    let raw;
    unsafe {
        raw = rt_sem_create(s.as_ptr(), 0, 0);
    }
    return if raw == ptr::null_mut() {
        None
    } else {
        Some(raw)
    };
}

 #[inline]
pub(crate) fn semaphore_try_take(handle: APIRawSem) -> RttCResult {
    unsafe { rt_sem_trytake(handle).into() }
}

 #[inline]
pub(crate) fn semaphore_take(handle: APIRawSem, tick: u32) -> RttCResult {
    unsafe { rt_sem_take(handle, tick).into() }
}

 #[inline]
pub(crate) fn semaphore_release(handle: APIRawSem) -> RttCResult {
    unsafe { rt_sem_release(handle).into() }
}

 #[inline]
pub(crate) fn semaphore_delete(handle: APIRawSem) {
    unsafe {
        let _ = rt_sem_delete(handle);
    }
}
