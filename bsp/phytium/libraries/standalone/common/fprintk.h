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
 * FilePath: fprintk.h
 * Date: 2021-08-23 16:24:02
 * LastEditTime: 2022-02-17 18:01:35
 * Description:  This file is for creating custom print interface for standlone sdk.
 *
 * Modify History:
 *  Ver     Who           Date                  Changes
 * -----   ------       --------     --------------------------------------
 *  1.0    huanghe      2022/7/23            first release
 */

#ifndef FPRINTK_H
#define FPRINTK_H

#ifdef __cplusplus
extern "C"
{
#endif

void f_printk(const char *format, ...) ;

#ifdef __cplusplus
}
#endif

#endif
