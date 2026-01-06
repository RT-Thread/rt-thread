/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       foxglove
 * 2025-09-15     foxglove     1.0 version
 */

/*! RT-Thread OS API bindings

Provides Rust wrappers for RT-Thread kernel and device driver APIs
*/

#![allow(non_camel_case_types)]

use core::ffi::{c_char, c_int, c_uint, c_void, c_long, c_ulong, c_uchar};

/* RT-Thread basic type definitions */
pub type rt_base_t = c_long;
pub type rt_ubase_t = c_ulong;
pub type rt_err_t = rt_base_t;
pub type rt_uint32_t = c_uint;
pub type rt_int32_t = c_int;
pub type rt_uint8_t  = c_uchar;
pub type rt_tick_t = rt_uint32_t;
pub type rt_size_t = rt_ubase_t;

pub type rt_thread_t = *mut c_void;
pub type rt_sem_t = *mut c_void;
pub type rt_mutex_t = *mut c_void;
pub type rt_device_t = *mut c_void;
pub type rt_mq_t = *mut c_void;

/* RT-Thread error codes */
pub const RT_EOK: rt_err_t = 0;
pub const RT_ERROR: rt_err_t = 1;
pub const RT_ETIMEOUT: rt_err_t = 2;
pub const RT_EFULL: rt_err_t = 3;
pub const RT_EEMPTY: rt_err_t = 4;
pub const RT_ENOMEM: rt_err_t = 5;
pub const RT_ENOSYS: rt_err_t = 6;
pub const RT_EBUSY: rt_err_t = 7;
pub const RT_EIO: rt_err_t = 8;
pub const RT_EINTR: rt_err_t = 9;
pub const RT_EINVAL: rt_err_t = 10;

/* ============== Kernel object management ============== */
unsafe extern "C" {
    pub fn rt_object_get_type(object: *mut c_void) -> u8;
    pub fn rt_object_find(name: *const c_char, object_type: u8) -> *mut c_void;
}

/* ============== Thread management ============== */
unsafe extern "C" {
    pub fn rt_thread_create(
        name: *const c_char,
        entry: extern "C" fn(*mut c_void),
        parameter: *mut c_void,
        stack_size: rt_size_t,
        priority: rt_uint8_t,
        tick: rt_tick_t,
    ) -> rt_thread_t;
    
    pub fn rt_thread_delete(thread: rt_thread_t) -> rt_err_t;
    pub fn rt_thread_startup(thread: rt_thread_t) -> rt_err_t;
    pub fn rt_thread_self() -> rt_thread_t;
    pub fn rt_thread_yield() -> rt_err_t;
    pub fn rt_thread_delay(tick: rt_tick_t) -> rt_err_t;
    pub fn rt_thread_mdelay(ms: rt_uint32_t) -> rt_err_t;
    pub fn rt_thread_suspend(thread: rt_thread_t) -> rt_err_t;
    pub fn rt_thread_resume(thread: rt_thread_t) -> rt_err_t;
}

/* ============== Semaphore management ============== */
unsafe extern "C" {
    pub fn rt_sem_create(name: *const c_char, value: rt_uint32_t, flag: rt_uint8_t) -> rt_sem_t;
    pub fn rt_sem_delete(sem: rt_sem_t) -> rt_err_t;
    pub fn rt_sem_take(sem: rt_sem_t, time: rt_tick_t) -> rt_err_t;
    pub fn rt_sem_trytake(sem: rt_sem_t) -> rt_err_t;
    pub fn rt_sem_release(sem: rt_sem_t) -> rt_err_t;
}

/* ============== Mutex management ============== */    
unsafe extern "C" {
    pub fn rt_mutex_create(name: *const c_char, flag: rt_uint8_t) -> rt_mutex_t;
    pub fn rt_mutex_delete(mutex: rt_mutex_t) -> rt_err_t;
    pub fn rt_mutex_take(mutex: rt_mutex_t, time: rt_tick_t) -> rt_err_t;
    pub fn rt_mutex_release(mutex: rt_mutex_t) -> rt_err_t;
}
/* ============== Message queue management ============== */
unsafe extern "C" {
    pub fn rt_mq_create(name: *const c_char, msg_size: rt_size_t, max_msgs: rt_size_t, flag: rt_uint8_t) -> rt_mq_t;
    pub fn rt_mq_send(mq: rt_mq_t, buffer: *const c_void, size: rt_size_t) -> rt_err_t;
    pub fn rt_mq_send_wait(mq: rt_mq_t, buffer: *const c_void, size: rt_size_t, timeout: rt_int32_t) -> rt_err_t;
    pub fn rt_mq_recv(mq: rt_mq_t, buffer: *mut c_void, size: rt_size_t, timeout: rt_int32_t) -> rt_base_t;
    pub fn rt_mq_delete(mq: rt_mq_t) -> rt_err_t;
    pub fn rt_mq_detach(mq: rt_mq_t) -> rt_err_t;
}
/* ============== Memory management ============== */
unsafe extern "C" {
    pub fn rt_malloc(size: rt_size_t) -> *mut c_void;
    pub fn rt_free(ptr: *mut c_void);
    pub fn rt_realloc(ptr: *mut c_void, newsize: rt_size_t) -> *mut c_void;
    pub fn rt_calloc(count: rt_size_t, size: rt_size_t) -> *mut c_void;
    pub fn rt_malloc_align(size: rt_size_t, align: rt_size_t) -> *mut c_void;
    pub fn rt_free_align(ptr: *mut c_void);
}

/* ============== Device management ============== */
unsafe extern "C" {
    pub fn rt_device_find(name: *const c_char) -> rt_device_t;
    pub fn rt_device_open(dev: rt_device_t, oflag: u16) -> rt_err_t;
    pub fn rt_device_close(dev: rt_device_t) -> rt_err_t;
    pub fn rt_device_read(
        dev: rt_device_t,
        pos: c_ulong,
        buffer: *mut c_void,
        size: rt_size_t,
    ) -> rt_size_t;
    pub fn rt_device_write(
        dev: rt_device_t,
        pos: c_ulong,
        buffer: *const c_void,
        size: rt_size_t,
    ) -> rt_size_t;
    pub fn rt_device_control(dev: rt_device_t, cmd: c_int, arg: *mut c_void) -> rt_err_t;
}

/* ============== System tick ============== */
unsafe extern "C" {
    pub fn rt_tick_get() -> rt_tick_t;
    pub fn rt_tick_from_millisecond(ms: c_int) -> rt_tick_t;
}

/* ============== Debug output ============== */
unsafe extern "C" {
    pub fn rt_kprintf(fmt: *const u8, ...) -> c_int;
    pub fn rt_kputs(str: *const u8) -> c_int;
}

/* ============== Interrupt management ============== */
unsafe extern "C" {
    pub fn rt_hw_interrupt_disable() -> rt_base_t;
    pub fn rt_hw_interrupt_enable(level: rt_base_t);
    pub fn rt_cpus_lock() -> rt_base_t;
    pub fn rt_cpus_unlock(level: rt_base_t);
    pub fn rt_interrupt_enter();
    pub fn rt_interrupt_leave();
    pub fn rt_interrupt_get_nest() -> u8;
}
