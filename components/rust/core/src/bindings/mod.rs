/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-10     foxglove     Bindings module
 */
pub mod libc;
pub mod librt;

/* Explicitly re-export only the needed items from librt to avoid namespace pollution. */
/* Basic RT-Thread types */
pub use librt::{
    rt_base_t, rt_ubase_t, rt_err_t, rt_uint32_t, rt_int32_t, rt_uint8_t, 
    rt_tick_t, rt_size_t, rt_thread_t, rt_sem_t, rt_mutex_t, rt_device_t, rt_mq_t
};

/* RT-Thread error codes */
pub use librt::{
    RT_EOK, RT_ERROR, RT_ETIMEOUT, RT_EFULL, RT_EEMPTY, RT_ENOMEM, 
    RT_ENOSYS, RT_EBUSY, RT_EIO, RT_EINTR, RT_EINVAL
};

/* Thread management functions */
pub use librt::{
    rt_thread_create, rt_thread_delete, rt_thread_startup, rt_thread_self,
    rt_thread_yield, rt_thread_delay, rt_thread_mdelay, rt_thread_suspend, rt_thread_resume
};

/* Semaphore management functions */
pub use librt::{
    rt_sem_create, rt_sem_delete, rt_sem_take, rt_sem_trytake, rt_sem_release
};

/* Mutex management functions */
pub use librt::{
    rt_mutex_create, rt_mutex_delete, rt_mutex_take, rt_mutex_release
};

/* Message queue management functions */
pub use librt::{
    rt_mq_create, rt_mq_send, rt_mq_send_wait, rt_mq_recv, rt_mq_delete, rt_mq_detach
};

/* Memory management functions */
pub use librt::{
    rt_malloc, rt_free, rt_realloc, rt_calloc, rt_malloc_align, rt_free_align,
    rt_safe_malloc, rt_safe_free
};

/* Device management functions */
pub use librt::{
    rt_device_find, rt_device_open, rt_device_close, rt_device_read, 
    rt_device_write, rt_device_control
};

/* System tick functions */     
pub use librt::{
    rt_tick_get, rt_tick_from_millisecond
};

/* Debug output functions */
pub use librt::{
    rt_kprintf, rt_kputs
};

/* Interrupt management functions */
pub use librt::{
    rt_hw_interrupt_disable, rt_hw_interrupt_enable, rt_cpus_lock, rt_cpus_unlock,
    rt_interrupt_enter, rt_interrupt_leave, rt_interrupt_get_nest
};

/* Object management functions */
pub use librt::{
    rt_object_get_type, rt_object_find
};
