/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-10     foxglove     RT-Thread Output implementation
 */
use crate::bindings::librt::rt_kprintf;
use core::fmt::{self, Write};
use core::cmp::min;

fn up_cast(a: usize, b: usize) -> usize {
    let r = a / b;
    return if a % b == 0 { r } else { r + 1 };
}

fn puts(str: &str, kp: fn(s: *const u8)) {
    let str = str.as_bytes();
    let mut buf = [0 as u8; 129];
    for i in 0..up_cast(str.len(), 128) {
        let end = min(128, str.len() - i * 128);
        for j in 0..end {
            buf[j] = str[(j + i * 128) as usize];
        }
        buf[end] = 0;
        kp(buf.as_ptr())
    }
}

struct StdOut;

impl fmt::Write for StdOut {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        fn rtt_kputs(s: *const u8) {
            unsafe {
                /* Use kprintf with "%s" format to avoid dependency on rt_kputs symbol */
                rt_kprintf(b"%s\0".as_ptr(), s);
            }
        }
        puts(s, rtt_kputs);
        Ok(())
    }
}

pub fn _print(args: fmt::Arguments) {
    unsafe {
        StdOut.write_fmt(args).unwrap_unchecked();
    }
}

#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => ({
        $crate::out::_print(format_args!($($arg)*));
    });
}

#[macro_export]
macro_rules! println {
    () => ({
        $crate::out::_print(format_args!("\n"));
    });
    ($($arg:tt)*) => ({
        $crate::out::_print(format_args!("{}\n", format_args!($($arg)*)));
    });
}
