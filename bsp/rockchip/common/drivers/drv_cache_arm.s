/**
  * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_cache_arm.s
  * @version V0.1
  * @brief   cpu cache interface
  *
  * Change Logs:
  * Date           Author          Notes
  * 2019-04-01     Cliff.Chen      first implementation
  *
  ******************************************************************************
  */

    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

    IMPORT cache_dump_ahb_error
    EXPORT CACHE_IRQHandler

CACHE_IRQHandler    PROC
    MRS     r2, PRIMASK
    CPSID   I
    MOV     r0, lr                  ; get lr
    MOV     r1, sp                  ; get stack pointer (current is MSP)
    BL      cm_backtrace_fault

Fault_Loop
    BL      Fault_Loop              ;while(1)
    ENDP

    END
