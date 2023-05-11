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
 * FilePath: felf.h
 * Date: 2021-08-31 11:16:49
 * LastEditTime: 2022-02-17 18:05:22
 * Description:  This file is for showing elf api.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu  2022/10/27   rename file name
 */

#ifndef FELF_H
#define FELF_H

#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

unsigned long ElfLoadElfImagePhdr(unsigned long addr);
unsigned long ElfLoadElfImageShdr(unsigned long addr);
int ElfIsImageValid(unsigned long addr);
unsigned long ElfExecBootElf(unsigned long (*entry)(int, char *const[]),
                             int argc, char *const argv[]);

#ifdef __cplusplus
}
#endif

#endif // !