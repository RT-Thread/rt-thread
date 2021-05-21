/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-07 09:53:07
 * @LastEditTime: 2021-04-07 15:29:20
 * @Description:  This files is for list data structure
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#ifndef FT_LIST_H
#define FT_LIST_H

#include "ft_types.h"

#define container_of(ptr, type, member) \
    ((type *)((s8 *)(ptr) - (u32)(&((type *)0)->member)))

#endif // ! FT_LIST_H
