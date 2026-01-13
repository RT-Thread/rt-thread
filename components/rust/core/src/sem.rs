/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-10     foxglove     RT-Thread Semaphore implementation
 */
#![allow(dead_code)]

use crate::api::*;
use crate::{panic::panic_on_atomic_context, RTTError};
use core::cell::UnsafeCell;
use core::marker::PhantomData;

const RT_WAITING_FOREVER: i32 = -1;

unsafe impl Send for Semaphore {}
unsafe impl Sync for Semaphore {}

pub struct Semaphore {
    data: PhantomData<*const UnsafeCell<usize>>,
    sem: APIRawSem
}

impl Semaphore {
    pub fn new() -> Result<Self, RTTError> {
        Self::new_with_name("unknown")
    }

    pub fn new_with_name(name: &str) -> Result<Self, RTTError> {
        panic_on_atomic_context("new_with_name");
        semaphore_create(name)
            .ok_or(RTTError::OutOfMemory)
            .map(|m| Semaphore {
                data: Default::default(),
                sem: m
            })
    }

    pub fn try_take(&self) -> Result<(), RTTError> {
        let m = semaphore_try_take(self.sem);
        if !is_eok(m) {
            return Err(RTTError::SemaphoreTakeTimeout);
        }
        Ok(())
    }

    pub fn take_wait_forever(&self) -> Result<(), RTTError> {
        panic_on_atomic_context("sem take_wait_forever");
        let ret = semaphore_take(self.sem, RT_WAITING_FOREVER as u32);

        if !is_eok(ret) {
            return Err(RTTError::SemaphoreTakeTimeout);
        }

        Ok(())
    }

    pub fn take(&self, max_wait: i32) -> Result<(), RTTError> {
        panic_on_atomic_context("sem take");
        let ret = semaphore_take(self.sem, max_wait as u32);

        if !is_eok(ret) {
            return Err(RTTError::SemaphoreTakeTimeout);
        }

        Ok(())
    }

    pub fn release(&self) {
        semaphore_release(self.sem);
    }
}

impl Drop for Semaphore {
    fn drop(&mut self) {
        semaphore_delete(self.sem)
    }
}