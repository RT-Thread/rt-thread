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
#include "ferror_code.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FELF_SUCCESS        FT_SUCCESS /* SUCCESS */
#define FELF_SECTION_NO_STRTAB      FT_MAKE_ERRCODE(ErrorModGeneral, ErrElf, 1)   /* There is no string table */
#define FELF_SECTION_NO_SPACE       FT_MAKE_ERRCODE(ErrorModGeneral, ErrElf, 2)   /* There is no space section */
#define FELF_SECTION_NOT_FIT        FT_MAKE_ERRCODE(ErrorModGeneral, ErrElf, 3)  /* No corresponding section was matched */
#define FELF_SECTION_GET_ERROR      FT_MAKE_ERRCODE(ErrorModGeneral, ErrElf, 3)

unsigned long ElfLoadElfImagePhdr(unsigned long addr);
unsigned long ElfLoadElfImageShdr(unsigned long addr);
int ElfIsImageValid(unsigned long addr);
unsigned long ElfExecBootElf(unsigned long (*entry)(int, char *const[]),
                             int argc, char *const argv[]);

FError ElfGetSection(unsigned long addr, char *section_name, u8 *data_get, u32 *length_p);

#ifdef __cplusplus
}
#endif

#endif // !