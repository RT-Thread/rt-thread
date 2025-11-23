/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       notes
 * 2025-10-10     foxglove     latest version
 */
use crate::bindings::*;

/* Error type from rt-thread C code */
#[derive(Clone, Copy, Debug, Eq, Hash, Ord, PartialEq, PartialOrd)]
pub enum RttCResult {
    Ok = RT_EOK as isize,
    Error = -(RT_ERROR as isize),
    TimeOut = -(RT_ETIMEOUT as isize),
    Full = -(RT_EFULL as isize),
    Empty = -(RT_EEMPTY as isize),
    NoMem = -(RT_ENOMEM as isize),
    NoSys = -(RT_ENOSYS as isize),
    Busy = -(RT_EBUSY as isize),
    IO = -(RT_EIO as isize),
    INTR = -(RT_EINTR as isize),
    INVAL = -(RT_EINVAL as isize),

    NotValidCode = -100,
}
/* NOTE Match to `enum Error` */
impl From<i32> for RttCResult {
    fn from(a: i32) -> Self {
        let ret = match a {
            0 => RttCResult::Ok,
            -1 => RttCResult::Error,
            -2 => RttCResult::TimeOut,
            -3 => RttCResult::Full,
            -4 => RttCResult::Empty,
            -5 => RttCResult::NoMem,
            -6 => RttCResult::NoSys,
            -7 => RttCResult::Busy,
            -8 => RttCResult::IO,
            -9 => RttCResult::INTR,
            -10 => RttCResult::INVAL,
            _ => RttCResult::NotValidCode,
        };
        ret
    }
}

impl From<i64> for RttCResult {
    fn from(a: i64) -> Self {
        if a >= 0 {
            RttCResult::Ok
        } else {
            match a {
                -1 => RttCResult::Error,
                -2 => RttCResult::TimeOut,
                -3 => RttCResult::Full,
                -4 => RttCResult::Empty,
                -5 => RttCResult::NoMem,
                -6 => RttCResult::NoSys,
                -7 => RttCResult::Busy,
                -8 => RttCResult::IO,
                -9 => RttCResult::INTR,
                -10 => RttCResult::INVAL,
                _ => RttCResult::NotValidCode,
            }
        }
    }
}

pub fn is_eok(val: RttCResult) -> bool {
    if let RttCResult::Ok = val {
        true
    } else {
        false
    }
}
