/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-10-14     foxglove     High-level libdl facade (libloader-style)
 */

use core::ffi::{c_char, c_int};
pub use crate::api::libloading as libloading;
pub use libloading::{RTLD_GLOBAL, RTLD_LAZY, RTLD_LOCAL, RTLD_NOW, last_error};
use libloading::{DlError, Library, Symbol};
use crate::println;

/** Open a module with `RTLD_NOW | RTLD_GLOBAL` convenience flags.

Safety: `path` must be a valid NUL-terminated C string pointer.
*/
pub unsafe fn dl_open(path: *const c_char) -> Result<Library, DlError> {
    Library::open_global(path)
}

/** Open a module with custom flags.

Safety: `path` must be a valid NUL-terminated C string pointer.
*/
pub unsafe fn dl_open_with_flags(path: *const c_char, flags: c_int) -> Result<Library, DlError> {
    Library::open(path, flags)
}

/** Resolve a typed symbol from a library.

Safety: Caller must ensure `T` matches the actual symbol type.
*/
pub unsafe fn dl_sym<'lib, T>(lib: &'lib Library, symbol: *const c_char) -> Result<Symbol<'lib, T>, DlError> {
    lib.get_ptr(symbol)
}

pub fn dl_print_last_error() {
    println!("libdl error: {}", libloading::DlError::Open(last_error()));
}

/** Use a library for a scoped operation; the library is closed on drop.

Safety: `path` must be a valid NUL-terminated C string pointer.
*/
pub unsafe fn with_library<R, F>(path: *const c_char, flags: c_int, f: F) -> Result<R, DlError>
where
    F: FnOnce(&Library) -> R,
{
    let lib = Library::open(path, flags)?;
    let result = f(&lib);
    /* Drop will handle closing; return the result */
    Ok(result)
}

#[macro_export]
/** Get a function from a dynamic link library
 * *You need `use libloader::libloading` first*
 * * `lib_path`: the path of DLL
 * * `fn_name`: The function name from dll
 * * `call_name`: The call function name of `fn_name`
 * * `ret`: return type of the function **if the function don't have return value, use "()" instead**
 * * `(value: type)`: **(variadic argument)** The arguments of the function from dll
 */
macro_rules! get_libfn {
    ($lib_path: expr, $fn_name: expr, $call_name: ident, $ret: ty, $($v: ident: $t:ty),*) => {
        pub fn $call_name($($v: $t),*) -> $ret {
            let lib = $crate::libloader::libloading::Library::new($lib_path).unwrap();
            let func: $crate::libloader::libloading::Symbol<fn($($t,)*) -> $ret> = lib.get($fn_name.as_bytes()).unwrap();
            func($($v,)*)
        }
    };
    ($lib_path: expr, $fn_name: expr, $call_name:ident, $ret: ty) => {
        pub fn $call_name() -> $ret {
            let lib = $crate::libloader::libloading::Library::new($lib_path).unwrap();
            let func: $crate::libloader::libloading::Symbol<fn() -> $ret> = lib.get($fn_name.as_bytes()).unwrap();
            func()
        }
    };
}
