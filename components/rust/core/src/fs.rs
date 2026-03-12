/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-10     foxglove     micro rust log component
 */
use alloc::string::{String, ToString};
use alloc::ffi::CString;
use crate::RTResult;
use crate::RTTError::{FileCloseErr, FileFlushErr, FileOpenErr, FileReadErr, FileSeekErr, FileSetLengthErr, FileWriteErr};
use crate::bindings::libc;
use core::ffi::{c_void, c_int};

pub struct File {
    pub fd: i32,
}

pub struct OpenOptions {
    pub path: String,
    pub read: bool,
    pub write: bool,
    pub create: bool,
    pub append: bool,
    pub truncate: bool,
}

impl OpenOptions {
    pub fn new() -> Self {
        Self { path: String::new(), read: false, write: false, create: false, append: false, truncate: false }
    }

    pub fn read(&mut self, read: bool) -> &mut Self { self.read = read; self }
    pub fn write(&mut self, write: bool) -> &mut Self { self.write = write; self }
    pub fn create(&mut self, create: bool) -> &mut Self { self.create = create; self }
    pub fn append(&mut self, append: bool) -> &mut Self { self.append = append; self }
    pub fn truncate(&mut self, truncate: bool) -> &mut Self { self.truncate = truncate; self }

    fn flags(&self) -> c_int {
        let mut flags: c_int = 0;
        flags |= if self.read && self.write { libc::O_RDWR } else if self.write { libc::O_WRONLY } else { libc::O_RDONLY };
        if self.create { flags |= libc::O_CREAT; }
        if self.append { flags |= libc::O_APPEND; }
        if self.truncate { flags |= libc::O_TRUNC; }
        flags
    }

    pub fn open(&mut self, path: &str) -> RTResult<File> {
        self.path = path.to_string();
        let cpath = match CString::new(self.path.clone()) { Ok(s) => s, Err(_) => return Err(FileOpenErr) };
        let oflags = self.flags();
        let fd = unsafe { libc::open(cpath.as_ptr(), oflags, 0o666 as c_int) };
        if fd < 0 { Err(FileOpenErr) } else { Ok(File { fd }) }
    }
}

impl Drop for File {
    fn drop(&mut self) {
        unsafe { libc::close(self.fd); }
    }
}

impl File {
    pub fn read_to_string(&self) -> RTResult<String> {
        let mut buf = [0u8; 256];
        let mut out = String::new();
        self.seek(0)?;
        loop {
            let n = self.read(&mut buf)?;
            if n == 0 { break; }
            let s = alloc::string::String::from_utf8_lossy(&buf[..n]).into_owned();
            out.push_str(&s);
        }
        Ok(out)
    }

    pub fn write_all(&self, buf: &str) -> RTResult<()> {
        let mut written = 0usize;
        let bytes = buf.as_bytes();
        while written < bytes.len() {
            let n = self.write(&bytes[written..])?;
            written += n;
        }
        Ok(())
    }

    pub fn read(&self, buf: &mut [u8]) -> RTResult<usize> {
        let n = unsafe { libc::read(self.fd, buf.as_mut_ptr() as *mut c_void, buf.len() as libc::size_t) };
        if n < 0 { Err(FileReadErr) } else { Ok(n as usize) }
    }

    pub fn write(&self, buf: &[u8]) -> RTResult<usize> {
        let n = unsafe { libc::write(self.fd, buf.as_ptr() as *const c_void, buf.len() as libc::size_t) };
        if n < 0 { Err(FileWriteErr) } else { Ok(n as usize) }
    }

    pub fn seek(&self, offset: i64) -> RTResult<i64> {
        let n = unsafe { libc::lseek(self.fd, offset as libc::off_t, libc::SEEK_SET) };
        if n < 0 { Err(FileSeekErr) } else { Ok(n) }
    }

    pub fn flush(&self) -> RTResult<()> {
        let n = unsafe { libc::fsync(self.fd) };
        if n < 0 { Err(FileFlushErr) } else { Ok(()) }
    }

    pub fn set_len(&self, len: i64) -> RTResult<()> {
        let n = unsafe { libc::ftruncate(self.fd, len as libc::off_t) };
        if n < 0 { Err(FileSetLengthErr) } else { Ok(()) }
    }

    pub fn close(&self) -> RTResult<()> {
        let n = unsafe { libc::close(self.fd) };
        if n < 0 { Err(FileCloseErr) } else { Ok(()) }
    }
}
