/*
 * @Copyright : (C) 2022 Phytium Information Technology, Inc. 
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
 * @FilePath: fcompiler.h
 * @Date: 2023-05-26 11:11:30
 * @LastEditTime: 2023-05-26 11:11:31
 * @Description:  This file is for gcc compiler compilation
 * 
 * @Modify History: 
 *  Ver   Who     Date   Changes
 * ----- ------  -------- --------------------------------------
 *  1.0   huanghe 2023-05-26  init
 */


#ifndef FCOMPILER_H
#define FCOMPILER_H

#ifdef __cplusplus
extern "C"
{
#endif

#define FCOMPILER_SECTION(section_name)  __attribute__ ((section (section_name)))
#if defined(__aarch64__)
#define FAARCH64_USE __aarch64__
#endif

#ifdef __cplusplus
}
#endif

#endif // !

