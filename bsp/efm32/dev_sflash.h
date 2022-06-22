/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-05-06   onelife     Initial creation by using USART module
 */

#ifndef __DEV_SFLASH_H__
#define __DEV_SFLASH_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
enum sflash_inst_type_t
{
    /* Instruction only */
    sflash_inst_wren = 0x00,
    sflash_inst_wrdi,
    sflash_inst_rdid_l,
    sflash_inst_rdid_s,
    sflash_inst_rdsr,
    sflash_inst_wrsr,
    sflash_inst_be,
    sflash_inst_dp,
    sflash_inst_rdp,
    /* Instruction and address */
    sflash_inst_wrlr,
    sflash_inst_rdlr,
    sflash_inst_read,
    sflash_inst_potp,
    sflash_inst_pp,
    sflash_inst_difp,
    sflash_inst_sse,
    sflash_inst_se,
    /* Instruction, address and dummy read */
    sflash_inst_read_f,
    sflash_inst_dofr,
    sflash_inst_rotp
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define SFLASH_SPI_COMMAND_SKIP     (1)
#define SFLASH_SPI_READ_SKIP        (2)

#define SFLASH_INST_CODE_WREN       (0x06)
#define SFLASH_INST_CODE_WRDI       (0x04)
#define SFLASH_INST_CODE_RDID_L     (0x9F)
#define SFLASH_INST_CODE_RDID_S     (0x9E)
#define SFLASH_INST_CODE_RDSR       (0x05)
#define SFLASH_INST_CODE_WRSR       (0x01)
#define SFLASH_INST_CODE_WRLR       (0xE5)
#define SFLASH_INST_CODE_RDLR       (0xE8)
#define SFLASH_INST_CODE_READ       (0x03)
#define SFLASH_INST_CODE_READ_F     (0x0B)
#define SFLASH_INST_CODE_DOFR       (0x3B)
#define SFLASH_INST_CODE_ROTP       (0x4B)
#define SFLASH_INST_CODE_POTP       (0x42)
#define SFLASH_INST_CODE_PP         (0x02)
#define SFLASH_INST_CODE_DIFP       (0xA2)
#define SFLASH_INST_CODE_SSE        (0x20)
#define SFLASH_INST_CODE_SE         (0xD8)
#define SFLASH_INST_CODE_BE         (0xC7)
#define SFLASH_INST_CODE_DP         (0xB9)
#define SFLASH_INST_CODE_RDP        (0xAB)

#define SFLASH_REPLY_LEN_WREN       (0)
#define SFLASH_REPLY_LEN_WRDI       (0)
#define SFLASH_REPLY_LEN_RDID_L     (20)
#define SFLASH_REPLY_LEN_RDID_S     (3)
#define SFLASH_REPLY_LEN_RDSR       (1)
#define SFLASH_REPLY_LEN_WRSR       (1)
#define SFLASH_REPLY_LEN_WRLR       (1)
#define SFLASH_REPLY_LEN_RDLR       (1)
#define SFLASH_REPLY_LEN_READ       (-1)
#define SFLASH_REPLY_LEN_READ_F     (-1)
#define SFLASH_REPLY_LEN_DOFR       (-1)
#define SFLASH_REPLY_LEN_ROTP       (65)
#define SFLASH_REPLY_LEN_POTP       (65)
#define SFLASH_REPLY_LEN_PP         (256)
#define SFLASH_REPLY_LEN_DIFP       (256)
#define SFLASH_REPLY_LEN_SSE        (0)
#define SFLASH_REPLY_LEN_SE         (0)
#define SFLASH_REPLY_LEN_BE         (0)
#define SFLASH_REPLY_LEN_DP         (0)
#define SFLASH_REPLY_LEN_RDP        (0)

/* Exported functions ------------------------------------------------------- */
rt_err_t efm_spiFlash_init(void);
rt_err_t efm_spiFlash_deinit(void);
rt_uint32_t efm_spiFlash_cmd(
    enum sflash_inst_type_t command,
    rt_uint32_t address,
    rt_uint8_t *buffer,
    rt_uint32_t size);

#endif /* __DEV_SFLASH_H__ */
