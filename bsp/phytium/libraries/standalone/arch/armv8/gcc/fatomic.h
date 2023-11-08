/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fatomic.h
 * Date: 2022-03-08 21:56:42
 * LastEditTime: 2022-03-15 11:14:45
 * Description:  This file is for l3 cache-related operations
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong    2023/6/6       first release
 */

#ifndef FATOMIC_H
#define FATOMIC_H

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Function Prototypes ******************************/

/* data atomic add val, return initial data */
#define FATOMIC_ADD(data, val)	__sync_fetch_and_add(&(data), (val))
/* data atomic add 1, return initial data */
#define FATOMIC_INC(data)       FATOMIC_ADD(data, 1)

/* data atomic subtract val, return initial data */
#define FATOMIC_SUB(data, val)	__sync_fetch_and_sub(&(data), (val))
/* data atomic subtract 1, return initial data */
#define FATOMIC_DEC(data)	    FATOMIC_SUB(data, 1)

/* data atomic or val, return initial data */
#define FATOMIC_OR(data, val)	__sync_fetch_and_or(&(data), (val))
/* data atomic xor val, return initial data */
#define FATOMIC_XOR(data, val)	__sync_fetch_and_xor(&(data), (val))

/* data atomic and val, return initial data */
#define FATOMIC_AND(data, val)	__sync_fetch_and_and(&(data), (val))
/* data atomic nand val, return initial data */
#define FATOMIC_NAND(data, val)	__sync_fetch_and_nand(&(data), (val))

/* 
atomic compare data and cmpval
if not equal, return false
if equal, data = newval, return true 
*/
#define FATOMIC_CAS_BOOL(data, cmpval, newval)	__sync_bool_compare_and_swap(&(data), (cmpval), (newval))

/* 
atomic compare data and cmpval
if not equal, return data
if equal, data = newval, return initial data
*/
#define FATOMIC_CAS_VAL(data, cmpval, newval)	__sync_val_compare_and_swap(&(data), (cmpval), (newval))

/* full memory barrier */
#define FATOMIC_MEM_BARRIER(data)	__sync_synchronize()

/* set data = val, and lock data */
#define FATOMIC_LOCK(data, val)	__sync_lock_test_and_set(&(data), val)

/* release data, set data = 0 */
#define FATOMIC_UNLOCK(data)	__sync_lock_release(&(data))

#ifdef __cplusplus
}
#endif

#endif