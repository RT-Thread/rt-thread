/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-14     foxglove     libdl safe wrapper (libloading-like)
 */

/*! Minimal `libloading`-style safe wrapper around RT-Thread libdl.
Provides RAII `Library` and typed `Symbol<T>` for dlsym.
*/

extern crate alloc;

use core::ffi::{c_char, c_int, c_void};
use core::ffi::CStr;
use core::marker::PhantomData;
use core::mem::forget;
use core::ops::Deref;

use alloc::ffi::CString;
use alloc::vec::Vec;

use crate::bindings::libc;

pub use crate::bindings::libc::{RTLD_GLOBAL, RTLD_LAZY, RTLD_LOCAL, RTLD_NOW};

/* Error type for dynamic loading operations */
pub enum DlError {
    /* dlopen failed; contains last error C-string pointer */
    Open(*const c_char),
    /* dlsym failed; contains last error C-string pointer */
    Symbol(*const c_char),
    /* dlclose returned non-zero; contains return code */
    Close(c_int),
}

impl core::fmt::Debug for DlError {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        core::fmt::Display::fmt(self, f)
    }
}

impl core::fmt::Display for DlError {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            &DlError::Open(ptr) | &DlError::Symbol(ptr) => {
                if ptr.is_null() {
                    write!(f, "[libdl open/sym error: none]")
                } else {
                    unsafe {
                        // `ptr` is a raw C string pointer
                        let cstr = CStr::from_ptr(ptr);
                        match cstr.to_str() {
                            Ok(s) => write!(f, "{}", s),
                            Err(_) => write!(f, "[libdl error: invalid UTF-8]")
                        }
                    }
                }
            }
            DlError::Close(rc) => write!(f, "dlclose rc={}", rc),
        }
    }
}

/* RAII wrapper for a `dlopen` handle */
pub struct Library {
    handle: *mut c_void,
}

impl Library {
    /* Create a new library using default flags (`RTLD_NOW | RTLD_GLOBAL`).
     * Accepts a Rust string path and converts internally to a C string.
     */
    pub fn new(path: &str) -> Result<Self, DlError> {
        let cstr = match CString::new(path) {
            Ok(s) => s,
            Err(_) => {
                return Err(DlError::Open(core::ptr::null()));
            }
        };
        unsafe { Self::open_global(cstr.as_ptr()) }
    }
    /* Open a dynamic module with given flags
     * Safety: `path` must be a valid, NUL-terminated C string pointer
     */
    pub unsafe fn open(path: *const c_char, flags: c_int) -> Result<Self, DlError> {
        let h = libc::dlopen(path, flags);
        if h.is_null() {
            Err(DlError::Open(libc::last_error_ptr()))
        } else {
            Ok(Library { handle: h })
        }
    }

    /* Convenience open using `RTLD_NOW | RTLD_GLOBAL` */
    pub unsafe fn open_global(path: *const c_char) -> Result<Self, DlError> {
        Self::open(path, RTLD_NOW | RTLD_GLOBAL)
    }

    /* Resolve a typed symbol from the library using a C string pointer.
     * Safety: Caller must ensure `T` matches the actual symbol type and `symbol` is NUL-terminated.
     */
    pub unsafe fn get_ptr<T>(&self, symbol: *const c_char) -> Result<Symbol<'_, T>, DlError> {
        let sym = libc::dlsym(self.handle, symbol);
        if sym.is_null() {
            Err(DlError::Symbol(libc::last_error_ptr()))
        } else {
            Ok(Symbol {
                raw: sym,
                _lib: PhantomData,
                _ty: PhantomData,
            })
        }
    }

    /* Resolve a typed symbol from the library using a byte slice name.
     * If the slice is not NUL-terminated, a temporary buffer is allocated.
     */
    pub fn get<T>(&self, symbol: &[u8]) -> Result<Symbol<'_, T>, DlError> {
        let (ptr, _guard_buf): (*const c_char, Option<Vec<u8>>) = if symbol.last().copied() == Some(0) {
            (symbol.as_ptr() as *const c_char, None)
        } else {
            let mut buf = Vec::with_capacity(symbol.len() + 1);
            buf.extend_from_slice(symbol);
            buf.push(0);
            (buf.as_ptr() as *const c_char, Some(buf))
        };
        let sym = unsafe { libc::dlsym(self.handle, ptr) };
        if sym.is_null() {
            Err(DlError::Symbol(libc::last_error_ptr()))
        } else {
            Ok(Symbol {
                raw: sym,
                _lib: PhantomData,
                _ty: PhantomData,
            })
        }
    }

    /* Check if handle is null */
    pub fn is_null(&self) -> bool {
        self.handle.is_null()
    }

    /* Consume and close the library explicitly */
    pub unsafe fn close(self) -> Result<(), DlError> {
        let h = self.handle;
        forget(self);
        let rc = libc::dlclose(h);
        if rc == 0 {
            Ok(())
        } else {
            Err(DlError::Close(rc))
        }
    }

    /* Leak the handle out (caller manages lifetime) */
    pub unsafe fn into_raw(self) -> *mut c_void {
        let h = self.handle;
        forget(self);
        h
    }
}

impl Drop for Library {
    fn drop(&mut self) {
        unsafe {
            if !self.handle.is_null() {
                let _ = libc::dlclose(self.handle);
                self.handle = core::ptr::null_mut();
            }
        }
    }
}

/* RAII wrapper for a symbol tied to a `Library` lifetime.
 * Stores the raw pointer and performs typed conversion at the use site.
 */
pub struct Symbol<'lib, T> {
    raw: *mut c_void,
    _lib: PhantomData<&'lib Library>,
    _ty: PhantomData<T>,
}

impl<'lib, T> Symbol<'lib, T> {
    /* Check if the underlying pointer is null */
    pub fn is_null(&self) -> bool {
        self.raw.is_null()
    }

    /* Get the raw pointer as `*mut c_void` */
    pub fn as_raw(&self) -> *mut c_void {
        self.raw
    }

    /* Cast the raw pointer to a different pointer type
     * Safety: Caller must ensure `U` is the correct target type.
     */
    pub unsafe fn as_ptr<U>(&self) -> *mut U {
        self.raw as *mut U
    }

    /* Convert to the typed value (e.g., function pointer) at use site
    Safety: `T` must be the correct type for the symbol.
    */
    pub unsafe fn to_value(&self) -> T
    where
        T: Sized + Copy,
    {
        // Bitwise-copy the pointer value into a `T` without using `transmute`.
        // This relies on `T` (e.g., extern "C" fn ...) having the same representation size.
        let src: *const T = (&self.raw as *const *mut c_void) as *const T;
        core::ptr::read(src)
    }

    pub fn into_raw(self) -> *mut c_void {
        let p = self.raw;
        forget(self);
        p
    }
}

impl<'lib, T> Deref for Symbol<'lib, T> {
    type Target = T;
    fn deref(&self) -> &Self::Target {
        /* Reinterpret the `raw` pointer storage as a value of type `T`. */
        /* Safety: This is safe if `T` is a pointer-sized function pointer or compatible pointer type. */
        unsafe { &*((&self.raw as *const *mut c_void) as *const T) }
    }
}

#[inline]
pub fn last_error() -> *const c_char {
    libc::last_error_ptr()
}
