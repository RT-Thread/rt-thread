/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-10     foxglove     RT-Thread Time implementation
 */
use crate::api::*;
use crate::bindings::libc;
use core::time::Duration;

pub fn sleep(time: Duration) {
    let mut time = time.as_millis();
    const MAX_DELAY: u128 = i32::MAX as u128;
    const MAX_DELAY_P1: u128 = i32::MAX as u128 + 1;
    loop {
        match time {
            1..=MAX_DELAY => {
                let _ = thread_m_delay(time as i32);
                return;
            }
            0 => return,
            MAX_DELAY_P1..=u128::MAX => {
                let _ = thread_m_delay(i32::MAX);
                time -= i32::MAX as u128;
            }
        }
    }
}

pub fn get_time() -> Duration {
    let mut tv = libc::timeval {
        tv_sec: 0,
        tv_usec: 0,
    };
    unsafe {
        libc::gettimeofday(&mut tv, core::ptr::null_mut());
    }
    Duration::new(tv.tv_sec as u64, tv.tv_usec as u32 * 1000)
}