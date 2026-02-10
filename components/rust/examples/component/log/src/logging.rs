/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-20     foxglove     micro rust log component
 */
/* Basic logging primitives and console output helpers */
use alloc::string::String;
use rt_rust::println;

#[repr(usize)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum Level {
    Error = 1,
    Warn = 2,
    Info = 3,
    Debug = 4,
    Trace = 5,
}

/* Top-level logging macro */
#[macro_export]
macro_rules! log {
    ($level:expr, $($arg:tt)*) => ({
        $crate::logging::_log($level, format_args!($($arg)*));
    });
}

/* Error-level logging */
#[macro_export]
macro_rules! error {
    ($($arg:tt)*) => ({
        $crate::logging::_log($crate::logging::Level::Error, format_args!($($arg)*));
    });
}

/* Warning-level logging */
#[macro_export]
macro_rules! warn {
    ($($arg:tt)*) => ({
        $crate::logging::_log($crate::logging::Level::Warn, format_args!($($arg)*));
    });
}

/* Info-level logging */
#[macro_export]
macro_rules! info {
    ($($arg:tt)*) => ({
        $crate::logging::_log($crate::logging::Level::Info, format_args!($($arg)*));
    });
}

/* Debug-level logging */
#[macro_export]
macro_rules! debug {
    ($($arg:tt)*) => ({
        $crate::logging::_log($crate::logging::Level::Debug, format_args!($($arg)*));
    });
}

/* Trace-level logging */
#[macro_export]
macro_rules! trace {
    ($($arg:tt)*) => ({
        $crate::logging::_log($crate::logging::Level::Trace, format_args!($($arg)*));
    });
}

/* Internal logging handler: formats message and prints with color */
pub fn _log(level: Level, args: core::fmt::Arguments) {
    use core::fmt::Write;
    use rt_rust::time;
    let mut s = String::new();
    write!(&mut s, "[{:?}][{:?}]", level, time::get_time()).unwrap();
    write!(&mut s, "{}", args).unwrap();
    match level {
        Level::Error => {
            println!("\x1b[1;31m{}\x1b[0m", s);
        }
        Level::Warn => {
            println!("\x1b[1;33m{}\x1b[0m", s);
        }
        Level::Info => {
            println!("\x1b[1;32m{}\x1b[0m", s);
        }
        Level::Debug => {
            println!("\x1b[1;34m{}\x1b[0m", s);
        }
        Level::Trace => {
            println!("\x1b[1;30m{}\x1b[0m", s);
        }
    }
}
