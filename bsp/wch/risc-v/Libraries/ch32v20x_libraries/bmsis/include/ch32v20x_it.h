/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v20x_it.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : This file contains the headers of the interrupt handlers.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#ifndef __CH32V20x_IT_H
#define __CH32V20x_IT_H

#include "debug.h"

#define GET_INT_SP()   asm("csrrw sp,mscratch,sp")
#define FREE_INT_SP()  asm("csrrw sp,mscratch,sp")


#endif /* __CH32V20x_IT_H */


