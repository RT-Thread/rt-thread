/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       foxglove
 * 2025-09-15     foxglove     1.0 version
 * 2025-09-23     foxglove     1.1 version, add libdl bindings
 */

/*! C standard library API bindings

Provides Rust wrappers for standard C library functions
*/

#![allow(non_camel_case_types)]

pub use core::ffi::{c_char, c_int, c_void, c_long, c_ulong};

pub const RTLD_LAZY: c_int = 0x00000;       /* Lazy function call binding */
pub const RTLD_NOW: c_int = 0x00001;        /* Immediate function call binding */
pub const RTLD_GLOBAL: c_int = 0x10000;     /* Make symbols globally available */
pub const RTLD_LOCAL: c_int = 0x00000;      /* Default local */
pub const O_RDONLY: c_int = 0x0000;         /* open for reading only */
pub const O_WRONLY: c_int = 0x0001;         /* open for writing only */
pub const O_RDWR: c_int = 0x0002;           /* open for reading and writing */
pub const O_APPEND: c_int = 0x0008;         /* writes done at eof */
pub const O_CREAT: c_int = 0x0100;          /* create and open file */
pub const O_TRUNC: c_int = 0x0200;          /* open and truncate */
pub const O_EXCL: c_int = 0x0400;           /* open only if file doesn't already exist */
pub type size_t = c_ulong;
pub type ssize_t = c_long;
pub type off_t = c_long;
pub const SEEK_SET: c_int = 0;
pub const SEEK_CUR: c_int = 1;
pub const SEEK_END: c_int = 2;
/* ============== time functions ============== */
pub type time_t = c_long;
pub type suseconds_t = c_int;
#[repr(C)]
pub struct timeval {
    pub tv_sec: time_t,
    pub tv_usec: suseconds_t,
}

/* ============== libdl functions ============== */
unsafe extern "C" {
    pub fn dlopen(filename: *const c_char, flag: c_int) -> *mut c_void;
    pub fn dlsym(handle: *mut c_void, symbol: *const c_char) -> *mut c_void;
    pub fn dlclose(handle: *mut c_void) -> c_int;
    pub fn dlerror() -> *const c_char;
}
unsafe extern "C" {
    pub fn open(path: *const c_char, oflag: c_int, ...) -> c_int;
    pub fn close(fd: c_int) -> c_int;
    pub fn read(fd: c_int, buf: *mut c_void, count: size_t) -> ssize_t;
    pub fn write(fd: c_int, buf: *const c_void, count: size_t) -> ssize_t;
    pub fn lseek(fd: c_int, offset: off_t, whence: c_int) -> off_t;
    pub fn fsync(fd: c_int) -> c_int;
    pub fn ftruncate(fd: c_int, length: off_t) -> c_int;
}

/* ============== time functions ============== */
unsafe extern "C" {
    /* Use local types instead of crate-root paths to avoid E0412 */
    pub fn gettimeofday(tp: *mut timeval, tz: *mut c_void) -> c_int;
}

/* Helper: get last libdl error C-string pointer
 * Safe wrapper around `dlerror()` returning the raw pointer for printing.
 */
#[inline]
pub fn last_error_ptr() -> *const c_char {
    unsafe { dlerror() }
}
