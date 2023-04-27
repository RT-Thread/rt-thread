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
 * FilePath: fnand_common_cmd.h
 * @Date: 2022-07-05 19:01:01
 * @LastEditTime: 2022-07-05 19:01:02
 * @Description:  This file is for nand generic command documentation
 *
 * @Modify History:
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */

#ifndef DRIVERS_NAND_COMMON_CMD_H
#define DRIVERS_NAND_COMMON_CMD_H

#include "ftypes.h"
#include "fnand.h"

#ifdef __cplusplus
extern "C"
{
#endif
/*
 * Mandatory commands
 */

#define NAND_CMD_READ1 0x00
#define NAND_CMD_READ2 0x30 /* READ PAGE */

#define NAND_CMD_CHANGE_READ_COLUMN1 0x05 /* NAND Random data Read \
                      Column command (1st                         \
cycle) */
#define NAND_CMD_CHANGE_READ_COLUMN2 0xE0 /* NAND Random data Read \
                      Column command (2nd                         \
cycle) */
#define NAND_CMD_BLOCK_ERASE1 0x60        /* NAND Block Erase \
(1st cycle) */
#define NAND_CMD_BLOCK_ERASE2 0xD0        /* NAND Block Erase \
(2nd cycle) */

#define NAND_CMD_PAGE_PROG1 0x80          /* NAND Page Program \
                          command (1st cycle)                      \
*/
#define NAND_CMD_PAGE_PROG2 0x10          /* NAND Page Program \
                          command (2nd cycle)                      \
*/

#define NAND_CMD_CHANGE_WRITE_COLUMN 0x85 /* NAND Change Write \
Column command */
#define NAND_CMD_READ_ID 0x90             /* NAND Read ID \
command */
#define NAND_CMD_READ_PARAM_PAGE 0xEC     /* NAND Read \
                          Parameter Page                   \
command */
#define NAND_CMD_RESET 0xFF               /* NAND Reset \
command */

#define NAND_END_CMD_NONE 0xfff /* No End command */

#define NAND_CMD_READ_STATUS 0x70 /* Read status */

FError FNandFlashReset(FNand *instance_p, u32 chip_addr) ;
FError FNandFlashReadId(FNand *instance_p, u8 address, u8 *id_buffer, u32 buffer_length, u32 chip_addr);
void FNandFlashFuncRegister(FNand *instance_p);

#ifdef __cplusplus
}
#endif

#endif

