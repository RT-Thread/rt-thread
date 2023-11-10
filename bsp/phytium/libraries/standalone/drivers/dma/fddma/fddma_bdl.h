/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fddma_bdl.c
 * Created Date: 2023-08-08 15:46:34
 * Last Modified: 2023-09-01 09:06:44
 * Description:  This file is for
 *
 * Modify History:
 *   Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 */

#ifndef  FDDMA_BDL_H
#define  FDDMA_BDL_H


#include "ftypes.h"
#include "ferror_code.h"
#include "fddma.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FDDMA_DEFAULT_BDL_CHAN_CONFIG(_chan_id, _bdl_descs, _bdl_desc_num)\
    (FDdmaChanConfig){ \
        .id = chan_id,\
        .slave_id = 0U,\
        .timeout = 0xffff,\
        .rd_align = FDDMA_BURST_SIZE_4_BYTE,\
        .wr_align = FDDMA_BURST_SIZE_4_BYTE,\
        .total_desc_num = _bdl_desc_num,\
        .valid_desc_num = 0U,\
        .descs= _bdl_descs\
    }

/*创建DDMA描述符*/
FError FDdmaAppendBDLEntry(FDdmaChan *const chan_p, uintptr src_addr,  fsize_t data_len);

/*通过DDMA描述符传输数据*/
FError FDdmaBDLTransfer(FDdmaChan *const chan_p);

/*检查并设置用于DDMA BDL模式的通道*/
FError FDdmaBdlSetChan(FDdma *const instance, FDdmaChan *const dma_chan, const FDdmaChanConfig *dma_chan_config);


#ifdef __cplusplus
}
#endif

#endif