/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-10     foxglove     RT-Thread Mutex implementation
 */
use crate::api::*;
use crate::{panic::panic_on_atomic_context, RTTError};
use alloc::fmt;
pub use alloc::sync::{Arc, Weak};
use core::cell::UnsafeCell;
use core::ops::{Deref, DerefMut};
use core::sync::atomic::*;

const RT_WAITING_FOREVER: isize = -1;

unsafe impl<T: Send, M: RawMutexOps + Sized> Send for Mutex<T, M> {}
unsafe impl<T: Send, M: RawMutexOps + Sized> Sync for Mutex<T, M> {}

pub struct Mutex<T: ?Sized, M = SleepMutex>
where
    M: RawMutexOps + Sized,
{
    mutex: M,
    data: UnsafeCell<T>,
}

/* Impl for Default Mutex<M = SleepMutex, NAME = UnnamedObj> */
impl<T> Mutex<T> {
    pub fn new(t: T) -> Result<Self, RTTError> {
        Ok(Mutex {
            mutex: SleepMutex::create("Unnamed")?,
            data: UnsafeCell::new(t),
        })
    }

    pub fn new_with_name(t: T, name: &str) -> Result<Self, RTTError> {
        Ok(Mutex {
            mutex: SleepMutex::create(name)?,
            data: UnsafeCell::new(t),
        })
    }

    pub fn try_lock(&self, max_wait: isize) -> Result<MutexGuard<'_, SleepMutex, T>, RTTError> {
        self.mutex.take(max_wait)?;
        Ok(MutexGuard {
            __mutex: &self.mutex,
            __data: &self.data,
        })
    }

    pub fn lock(&self) -> Result<MutexGuard<'_, SleepMutex, T>, RTTError> {
        self.mutex.take(RT_WAITING_FOREVER)?;
        Ok(MutexGuard {
            __mutex: &self.mutex,
            __data: &self.data,
        })
    }
}

/* Impl for all Mutex */
impl<T, M: RawMutexOps> Mutex<T, M> {
    pub fn spec_new(t: T) -> Result<Self, RTTError> {
        Ok(Mutex {
            mutex: M::create("Unnamed")?,
            data: UnsafeCell::new(t),
        })
    }

    pub fn spec_new_with_name(t: T, name: &str) -> Result<Self, RTTError> {
        Ok(Mutex {
            mutex: M::create(name)?,
            data: UnsafeCell::new(t),
        })
    }

    pub fn spec_try_lock(&self, max_wait: isize) -> Result<MutexGuard<'_, M, T>, RTTError> {
        self.mutex.take(max_wait)?;
        Ok(MutexGuard {
            __mutex: &self.mutex,
            __data: &self.data,
        })
    }

    pub fn spec_lock(&self) -> Result<MutexGuard<'_, M, T>, RTTError> {
        self.mutex.take(RT_WAITING_FOREVER)?;
        Ok(MutexGuard {
            __mutex: &self.mutex,
            __data: &self.data,
        })
    }
}

impl<T: ?Sized> fmt::Debug for Mutex<T> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "Mutex address: {:?}", self.mutex)
    }
}

pub struct MutexGuard<'a, M: RawMutexOps + 'a, T: ?Sized + 'a> {
    __mutex: &'a M,
    __data: &'a UnsafeCell<T>,
}

impl<'mutex, M: RawMutexOps, T: ?Sized> Deref for MutexGuard<'mutex, M, T> {
    type Target = T;
    fn deref(&self) -> &T {
        unsafe { &*self.__data.get() }
    }
}

impl<'mutex, M: RawMutexOps, T: ?Sized> DerefMut for MutexGuard<'mutex, M, T> {
    fn deref_mut(&mut self) -> &mut T {
        unsafe { &mut *self.__data.get() }
    }
}

impl<'a, M: RawMutexOps, T: ?Sized> Drop for MutexGuard<'a, M, T> {
    fn drop(&mut self) {
        self.__mutex.release();
    }
}

pub type CommonMutex = SleepMutex;
pub struct SleepMutex(APIRawMutex);

impl fmt::Debug for SleepMutex {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{:?}", self.0)
    }
}

pub struct AtomicMutex(UnsafeCell<InterruptFlag>, AtomicBool);

pub trait RawMutexOps: Sized {
    fn create(name: &str) -> Result<Self, RTTError>;
    fn take(&self, max_wait: isize) -> Result<(), RTTError>;
    fn release(&self);
    fn drop(&mut self);
}

impl RawMutexOps for AtomicMutex {
    fn create(_name: &str) -> Result<Self, RTTError> {
        Ok(AtomicMutex {
            0: UnsafeCell::new(INTERRUPT_FLAG_INIT),
            1: AtomicBool::new(false),
        })
    }

    fn take(&self, max_wait: isize) -> Result<(), RTTError> {
        let f;
        unsafe {
            f = self.0.get();
            *f = interrupt_disable();
        }
        let ret = if max_wait == RT_WAITING_FOREVER {
            while self
                .1
                .compare_exchange_weak(false, true, Ordering::Acquire, Ordering::Relaxed)
                .is_err()
            {
                while self.1.load(Ordering::Relaxed) {}
            }
            Ok(())
        } else {
            if self
                .1
                .compare_exchange_weak(false, true, Ordering::Acquire, Ordering::Relaxed)
                .is_ok()
            {
                Ok(())
            } else {
                unsafe {
                    interrupt_enable(*f);
                }
                Err(RTTError::MutexTakeTimeout)
            }
        };

        return ret;
    }

    fn release(&self) {
        self.1.store(false, Ordering::Release);
        let f;
        unsafe {
            f = self.0.get();
            interrupt_enable(*f);
        }
    }

    fn drop(&mut self) {}
}

impl RawMutexOps for SleepMutex {
    fn create(name: &str) -> Result<Self, RTTError> {
        panic_on_atomic_context("create");
        mutex_create(name)
            .ok_or(RTTError::OutOfMemory)
            .map(|m| SleepMutex(m))
    }

    fn take(&self, max_wait: isize) -> Result<(), RTTError> {
        panic_on_atomic_context("take");
        let ret = mutex_take(self.0, max_wait);
        if !is_eok(ret) {
            return Err(RTTError::MutexTakeTimeout);
        }
        Ok(())
    }

    fn release(&self) {
        panic_on_atomic_context("release");
        mutex_release(self.0);
    }

    fn drop(&mut self) {
        panic_on_atomic_context("drop");
        mutex_delete(self.0);
    }
}