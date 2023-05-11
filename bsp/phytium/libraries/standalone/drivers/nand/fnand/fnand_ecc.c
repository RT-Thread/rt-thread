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
 * FilePath: fnand_ecc.c
 * Date: 2022-05-12 14:17:42
 * LastEditTime: 2022-05-12 15:56:27
 * Description:  This file is for ecc validation related api
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */


#include "fnand_ecc.h"
#include "fnand.h"
#include "fnand_hw.h"
#include "fdebug.h"
#define FNAND_ECC_DEBUG_TAG "FNAND_ECC"
#define FNAND_ECC_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FNAND_ECC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_ECC_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FNAND_ECC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FNAND_ECC_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FNAND_ECC_DEBUG_TAG, format, ##__VA_ARGS__)


/**
 * @name: FNandGetEccTotalLength
 * @msg:  根据page size 与 ecc_strength（纠错个数）确定硬件ecc 产生
 * @param {u32} bytes_per_page
 * @param {u32} ecc_strength
 * @return {*}
 * @note:
 */
u32 FNandGetEccTotalLength(u32 bytes_per_page, u32 ecc_strength)
{
    int ecc_total = 0;
    switch (bytes_per_page)
    {
        case 0x200:
            if (ecc_strength == 8)
            {
                ecc_total = 0x0D;
            }
            else if (ecc_strength == 4)
            {
                ecc_total = 7;
            }
            else if (ecc_strength == 2)
            {
                ecc_total = 4;
            }
            else
            {
                ecc_total = 0;
            }
            break;
        case 0x800:
            if (ecc_strength == 8)
            {
                ecc_total = 0x34;
            }
            else if (ecc_strength == 4)
            {
                ecc_total = 0x1a;
            }
            else if (ecc_strength == 2)
            {
                ecc_total = 0xd;
            }
            else
            {
                ecc_total = 0;
            }
            break;
        case 0x1000:
            if (ecc_strength == 8)
            {
                ecc_total = 0x68;
            }
            else if (ecc_strength == 4)
            {
                ecc_total = 0x34;
            }
            else if (ecc_strength == 2)
            {
                ecc_total = 0x1a;
            }
            else
            {
                ecc_total = 0;
            }
            break;
        case 0x2000:
            if (ecc_strength == 8)
            {
                ecc_total = 0xD0;
            }
            else if (ecc_strength == 4)
            {
                ecc_total = 0x68;
            }
            else if (ecc_strength == 2)
            {
                ecc_total = 0x34;
            }
            else
            {
                ecc_total = 0;
            }
            break;
        case 0x4000:
            if (ecc_strength == 8)
            {
                ecc_total = 0x1A0;
            }
            if (ecc_strength == 4)
            {
                ecc_total = 0xD0;
            }
            else if (ecc_strength == 2)
            {
                ecc_total = 0x68;
            }
            else
            {
                ecc_total = 0;
            }
            break;
        default:
            ecc_total = 0;
            break;
    }

    FNAND_ECC_DEBUG_I("[%s %d]writesize: 0x%x, ecc strength: %d, ecc_total: 0x%x\n", __func__, __LINE__, bytes_per_page, ecc_strength, ecc_total);
    return ecc_total;
}


/**
 * @name: FNandCorrectEcc
 * @msg:
 * @note:
 * @return {*}
 * @param {uintptr_t} base_address
 * @param {u32} ecc_step_size   单次ecc 使用的步长大小
 * @param {u32} hw_ecc_steps    一页操作需要进行的ecc 次数
 * @param {u8*} buf page 页 对应的指针
 * @param {u32} length
 */
// s32 FNandCorrectEcc(uintptr_t base_address,u32 ecc_step_size,u32 hw_ecc_steps,u8* buf ,u32 length)
// {
//     u32 i, j;
//  u32 value, tmp;
//  int stat = 0;
//     if(!buf)
//     {
//         FNAND_ECC_DEBUG_E("page buffer is null");
//         return -1;
//     }

//     /* i  */
//  for (i = 0; i < hw_ecc_steps; i++)
//     {
//      for (j = 0; j < 2; j++) {
//          value = FNAND_READREG(base_address, 0xB8 + 4 * (2 * i + j));
//             FNAND_ECC_DEBUG_W("index:%x i is %d ,j is %d ",
//                   0xB8 + 4 * (2 * i + j),i,j);
//             if (value)
//             {
//              FNAND_ECC_DEBUG_W("offset:%x value:0x%08x\n",
//                   0xB8 + 4 * (2 * i + j), value);
//              //phytium_nfc_data_dump2(nfc, nfc->dma_buf + (ecc_step_size * i + tmp/8)/512, 512);
//          }

//          tmp = value & 0xFFFF;
//          if (tmp && (tmp <= 4096))
//             {
//              tmp -= 1;
//              FNAND_ECC_DEBUG_W( "ECC_CORRECT %x %02x\n",
//                   ecc_step_size * i + tmp / 8,
//                   buf[ecc_step_size * i + tmp / 8]);

//              buf[ecc_step_size*i + tmp/8] ^= (0x01 << tmp%8);
//              stat++;

//              FNAND_ECC_DEBUG_W( "ECC_CORRECT xor %x %02x\n",
//                   0x01 << tmp % 8,
//                   buf[ecc_step_size * i + tmp / 8]);
//          }
//             else
//             {
//                 FNAND_ECC_DEBUG_E("ECC_CORRECT offset > 4096!\n");
//             }

//             tmp = (value >> 16) & 0xFFFF;
//          if (tmp && (tmp <= 4096) )
//             {
//              tmp -= 1;
//              FNAND_ECC_DEBUG_W( "ECC_CORRECT %x %02x\n",
//                   ecc_step_size * i + tmp / 8,
//                   buf[ecc_step_size * i + tmp / 8]);

//              buf[ecc_step_size*i + tmp/8] ^= (0x01 << tmp%8);
//              stat++;

//              FNAND_ECC_DEBUG_W( "ECC_CORRECT xor %x %02x\n",
//                   ecc_step_size * i + tmp / 8,
//                   buf[ecc_step_size * i + tmp / 8]);
//          }
//             else
//             {
//                 FNAND_ECC_DEBUG_E("ECC_CORRECT offset > 4096!\n");
//             }
//      }
//  }

//  return stat;

// }

// 校验offset 0xb8  + i * 0x10
// 校验强度为 2 j = 1
// 校验强度为 4 j = 2
// 校验强度为 8 j = 4




s32 FNandCorrectEcc(uintptr_t base_address, u32 ecc_step_size, u32 hw_ecc_steps, u8 *buf, u32 length)
{
    u32 i, j;
    u32 value, tmp;
    int stat = 0;
    if (!buf)
    {
        FNAND_ECC_DEBUG_E("Page buffer is null");
        return -1;
    }

    /* i  */
    for (i = 0; i < hw_ecc_steps; i++)
    {
        for (j = 0; j < 4; j++)
        {        
            value = FNAND_READREG(base_address, 0xB8 + 0x10 * i + 4 * j);
         
            tmp = value & 0xFFFF;
            if (tmp && (tmp <= 4096))
            {
                tmp -= 1;
                FNAND_ECC_DEBUG_W("ECC_CORRECT %x %02x\n",
                                  ecc_step_size * i + tmp / 8,
                                  buf[ecc_step_size * i + tmp / 8]);

                buf[ecc_step_size * i + tmp / 8] ^= (0x01 << tmp % 8);
                stat++;

                FNAND_ECC_DEBUG_W("ECC_CORRECT xor %x %02x\n",
                                  0x01 << tmp % 8,
                                  buf[ecc_step_size * i + tmp / 8]);
            }


            tmp = (value >> 16) & 0xFFFF;
            if (tmp && (tmp <= 4096))
            {
                tmp -= 1;
                FNAND_ECC_DEBUG_W("ECC_CORRECT %x %02x\n",
                                  ecc_step_size * i + tmp / 8,
                                  buf[ecc_step_size * i + tmp / 8]);

                buf[ecc_step_size * i + tmp / 8] ^= (0x01 << tmp % 8);
                stat++;

                FNAND_ECC_DEBUG_W("ECC_CORRECT xor %x %02x\n",
                                  ecc_step_size * i + tmp / 8,
                                  buf[ecc_step_size * i + tmp / 8]);
            }

        }
    }

    return stat;

}



