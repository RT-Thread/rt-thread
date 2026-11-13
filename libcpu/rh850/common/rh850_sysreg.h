/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#ifndef __RH850_SYSREG_H__
#define __RH850_SYSREG_H__

#define RH850_SR_EIPC  0, 0
#define RH850_SR_EIPSW 1, 0
#define RH850_SR_FEPC  2, 0
#define RH850_SR_FEPSW 3, 0
#define RH850_SR_PSW   5, 0
#define RH850_SR_FPSR  6, 0
#define RH850_SR_FPEPC 7, 0
#define RH850_SR_FPST  8, 0
#define RH850_SR_FPCC  9, 0
#define RH850_SR_EIIC  13, 0
#define RH850_SR_FEIC  14, 0
#define RH850_SR_CTPC  16, 0
#define RH850_SR_EIWR  28, 0
#define RH850_SR_FEWR  29, 0
#define RH850_SR_EBASE 3, 1
#define RH850_SR_INTBP 4, 1

#define RH850_PSW_ID  0x00000020
#define RH850_PSW_EP  0x00000040
#define RH850_PSW_EBV 0x00008000
#define RH850_PSW_CU0 0x00010000

#endif
