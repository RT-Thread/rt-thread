/**
  * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
  *
  * SPDX-License-Identifier: Apache-2.0
  ******************************************************************************
  * @file    drv_cache_gcc.S
  * @version V0.1
  * @brief   cpu cache interface
  *
  * Change Logs:
  * Date           Author          Notes
  * 2019-04-01     Cliff.Chen      first implementation
  *
  ******************************************************************************
  */

.cpu cortex-m4
.syntax unified
.thumb
.text

.global CACHE_IRQHandler
.type CACHE_IRQHandler, %function
CACHE_IRQHandler:
    MRS r2, PRIMASK
    CPSID   I
    MOV     r0, lr                  /* get lr */
    MOV     r1, sp                  /* get stack pointer (current is MSP) */
    BL      cache_dump_ahb_error

Fault_Loop:
    BL      Fault_Loop              /* while(1) */

