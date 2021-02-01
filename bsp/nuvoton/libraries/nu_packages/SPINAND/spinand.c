/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-1-13       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(NU_PKG_USING_SPINAND)

#define LOG_TAG                 "spinand_flash"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#include "spinand.h"

const struct nu_spinand_info g_spinandflash_list[] =
{
    /* Winbond */
    { 0xEFAA21, 2048, 64, 0x6b, 0xff, 0xff, 0xff, 0x1, 1024, 64, 0, "Winbond 128MB: 2048+64@64@1024" }, /* Only tested */

#if 0
    { 0xEFAA22, 2048, 64, 0x6b, 0xff, 0xff, 0xff, 0x1, 2048, 64, 0, "Winbond 256MB: 2048+64@64@1024" },
    { 0xEFAB21, 2048, 64, 0x6b, 0xff, 0xff, 0xff, 0x1, 1024, 64, 1, "Winbond 256MB: 2048+64@64@1024, MCP" },

    /* Not test and supporting yet. */
    /* MXIC */
    { 0x00C212, 2048, 64, 0x6b, 0x05, 0x01, 0x40, 0x1, 1024, 64, 0, "MXIC 128MB: 2048+64@64@1024" },

    /* XTX */
    { 0x0BE20B, 2048, 64, 0x6b, 0xff, 0xff, 0xff, 0x1, 2048, 64, 0, "XTX 256MB: 2048+64@64@2048" },
    { 0x0BF20B, 2048, 64, 0x6b, 0xff, 0xff, 0xff, 0x1, 2048, 64, 0, "XTX 256MB: 2048+64@64@2048" },
    { 0x0BE10B, 2048, 64, 0x6b, 0xff, 0xff, 0xff, 0x1, 1024, 64, 0, "XTX 256MB: 2048+64@64@1024" },
    { 0x0BF10B, 2048, 64, 0x6b, 0xff, 0xff, 0xff, 0x1, 1024, 64, 0, "XTX 256MB: 2048+64@64@1024" },

    /* ATO */
    { 0x9B129B, 2048, 64, 0x6b, 0x0f, 0x1f, 0x01, 0x1, 1024, 64, 0, "ATO 128MB: 2048+64@64@1024" },

    /* Micro */
    { 0x2C242C, 2048, 128, 0x6b, 0x0f, 0x1f, 0x01, 0x1, 2048, 64, 0, "Micro 256MB: 2048+128@64@2048" },

    /* GigaDevice */
    { 0xB148C8, 2048, 128, 0x6b, 0x0f, 0x1f, 0x01, 0x1, 1024, 64, 0, "GD 128MB: 2048+128@64@1024" },

    /* Unknown */
    { 0x00C8D1, 2048, 128, 0x6b, 0x0f, 0x1f, 0x01, 0x1, 1024, 64, 0, "Unknown 128MB: 2048+128@64@1024" },
    { 0x00C851, 2048, 128, 0x6b, 0x0f, 0x1f, 0x01, 0x1, 1024, 64, 0, "Unknown 128MB: 2048+128@64@1024" },
    { 0x98E240, 2048, 128, 0x6b, 0x0f, 0x1f, 0x01, 0x1, 1024, 64, 0, "Unknown 128MB: 2048+128@64@1024" }
#endif
};
#define SPINAND_LIST_ELEMENT_NUM ( sizeof(g_spinandflash_list)/sizeof(struct nu_spinand_info) )


/*
For 0xEFAA21 description:

Data Area(2048-Byte)
-----------------------------
|Sect-0|Sect-1|Sect-2|Sect-3|
|(512B)|(512B)|(512B)|(512B)|
-----------------------------

         Spare Area(64-Byte)
         ---------------------------------
         |Spare-0|Spare-1|Spare-2|Spare-3|
         | (16B) | (16B) | (16B) | (16B) |
         ---------------------------------

 ----------------- Spare-0 -------------------
/                                             \
-------------------------------------------------
| BBM | UD2 |   UD1   |  ECC Sect-0 | ECC Spare |
| 0 1 | 2 3 | 4 5 6 7 | 8 9 A B C D | E F       |
-------------------------------------------------
|  NO ECC   |   ECC PROTECTED       |  ECC 4-D  |

BBM: Bad block marker.
UD1: User Data 1.
UD2: User Data 2.
ECC Sect-n: ECC for sector-n.
ECC Spare: ECC for spare 4-D.

 ---------------- Spare-1 -------------------
/                                            \
-----------------------------------------------
|   UD2   |   UD1   |  ECC Sect-1 | ECC Spare |
| 0 1 2 3 | 4 5 6 7 | 8 9 A B C D | E F       |
-----------------------------------------------
|  NO ECC |   ECC PROTECTED       | ECC 14-1D |

 ---------------- Spare-2 -------------------
/                                            \
-----------------------------------------------
|   UD2   |   UD1   |  ECC Sect-2 | ECC Spare |
| 0 1 2 3 | 4 5 6 7 | 8 9 A B C D | E F       |
-----------------------------------------------
|  NO ECC |   ECC PROTECTED       | ECC 24-2D |

 ---------------- Spare-3 -------------------
/                                            \
-----------------------------------------------
|   UD2   |   UD1   |  ECC Sect-3 | ECC Spare |
| 0 1 2 3 | 4 5 6 7 | 8 9 A B C D | E F       |
-----------------------------------------------
|  NO ECC |   ECC PROTECTED       | ECC 34-3D |
*/

rt_uint8_t spinand_flash_data_layout[SPINAND_SPARE_LAYOUT_SIZE] =
{
#if defined(RT_USING_DFS_UFFS)
    /* For storing Seal-byte at 0x37. */
    0x04, 0x04, 0x14, 0x04, 0x24, 0x04, 0x34, 0x03, 0xFF, 0x00
#else
    0x04, 0x04, 0x14, 0x04, 0x24, 0x04, 0x34, 0x04, 0xFF, 0x00
#endif
};

rt_uint8_t spinand_flash_ecc_layout[SPINAND_SPARE_LAYOUT_SIZE] =
{
#if defined(RT_USING_DFS_UFFS)
    /* For storing Seal-byte at 0x37 and not report latest ECC part in Spare-3 */
    0x08, 0x08, 0x18, 0x08, 0x28, 0x08, /*0x38, 0x08,*/ 0xFF, 0x00
#else
    0x08, 0x08, 0x18, 0x08, 0x28, 0x08, 0x38, 0x08, 0xFF, 0x00
#endif
};

static rt_err_t spinand_info_read(struct rt_qspi_device *qspi);

static rt_err_t spinand_die_select(struct rt_qspi_device *qspi, uint8_t select_die)
{
    uint8_t au8Cmd[2] = { 0xC2, 0x0 };
    au8Cmd[1] = select_die;

    return nu_qspi_send(qspi, &au8Cmd[0], sizeof(au8Cmd));
}

static uint8_t spinand_isbusy(struct rt_qspi_device *qspi)
{
#define BUSY_CKECKING_TIMEOUT_MS  3000
    volatile uint8_t SR = 0xFF;
    rt_err_t result;
    uint8_t au8Cmd[2] = { 0x0F, 0xC0 };

    uint32_t u32CheckingDuration = rt_tick_from_millisecond(BUSY_CKECKING_TIMEOUT_MS);
    uint32_t u32Start = rt_tick_get();

    do
    {
        result = nu_qspi_send_then_recv(qspi, &au8Cmd[0], sizeof(au8Cmd), (void *)&SR, 1);
        if (result != RT_EOK)
            goto timeout_spinand_isbusy;

        if ((rt_tick_get() - u32Start) >= u32CheckingDuration)
        {
            goto timeout_spinand_isbusy;
        }

    }
    while ((SR & 0x1) != 0x00);

    return 0;

timeout_spinand_isbusy:

    LOG_E("Error: spinand timeout.");

    return 1;
}

static rt_err_t spinand_program_dataload(
    struct rt_qspi_device *qspi,
    uint8_t u8AddrH,
    uint8_t u8AddrL,
    uint8_t *pu8DataBuff,
    uint32_t u32DataCount,
    uint8_t *pu8SpareBuff,
    uint32_t u32SpareCount)
{
    uint32_t volatile i = 0;
    uint8_t u8WECmd = 0x06;
    rt_err_t result = RT_EOK;

    struct rt_qspi_message qspi_messages[2] = {0};

    /* 1-bit mode */
    qspi_messages[0].instruction.content    = 0x32;
    qspi_messages[0].instruction.qspi_lines = 1;

    qspi_messages[0].address.content = (u8AddrH << 8) | (u8AddrL);
    qspi_messages[0].address.size = 2 * 8;
    qspi_messages[0].address.qspi_lines = 1;

    /* 4-bit mode */
    qspi_messages[0].qspi_data_lines   = 4;
    qspi_messages[0].parent.cs_take    = 1;
    qspi_messages[0].parent.cs_release = 0;
    qspi_messages[0].parent.send_buf   = pu8DataBuff;
    qspi_messages[0].parent.length     = u32DataCount;
    qspi_messages[0].parent.next       = &qspi_messages[1].parent;

    qspi_messages[1].qspi_data_lines   = 4;
    qspi_messages[1].parent.cs_take    = 0;
    qspi_messages[1].parent.cs_release = 1;
    qspi_messages[1].parent.send_buf   = pu8SpareBuff;
    qspi_messages[1].parent.length     = u32SpareCount;

    if ((result = nu_qspi_send(qspi, &u8WECmd, sizeof(u8WECmd))) != RT_EOK)
        goto exit_spinand_program_dataload;

    result = nu_qspi_transfer_message(qspi, (struct rt_qspi_message *)&qspi_messages[0]);

exit_spinand_program_dataload:

    return result;
}

static uint8_t spinand_status_register_read(struct rt_qspi_device *qspi, uint8_t u8SRSel)
{
    uint8_t u8SR = 0;
    uint8_t au8Cmd[2];

    switch (u8SRSel)
    {
    case 0x01:
        au8Cmd[0] = 0x05;
        au8Cmd[1] = 0xA0;
        break;

    case 0x02:
        au8Cmd[0] = 0x0F;
        au8Cmd[1] = 0xB0;
        break;

    case 0x03:
        au8Cmd[0] = 0x05;
        au8Cmd[1] = 0xC0;
        break;

    default:
        RT_ASSERT(0);
        break;
    }

    if (nu_qspi_send_then_recv(qspi, &au8Cmd[0], sizeof(au8Cmd), &u8SR, 1) != RT_EOK)
        RT_ASSERT(0);

    return u8SR;
}

static rt_err_t spinand_status_register_write(struct rt_qspi_device *qspi, uint8_t u8SRSel, uint8_t u8Value)
{
    rt_err_t result = RT_EOK;
    uint8_t au8Cmd[3];

    switch (u8SRSel)
    {
    case 0x01:
        au8Cmd[0] = 0x01;
        au8Cmd[1] = 0xA0;
        break;

    case 0x02:
        au8Cmd[0] = 0x01;
        au8Cmd[1] = 0xB0;
        break;

    case 0x03:
        au8Cmd[0] = 0x01;
        au8Cmd[1] = 0xC0;
        break;

    default:
        result = RT_EINVAL;
        goto exit_spinand_status_register_write;
    }

    au8Cmd[2] = u8Value;

    if ((result = nu_qspi_send(qspi, &au8Cmd[0], sizeof(au8Cmd))) != RT_EOK)
        goto exit_spinand_status_register_write;

    if (spinand_isbusy(qspi))
    {
        result = RT_EIO;
        goto exit_spinand_status_register_write;
    }

exit_spinand_status_register_write:

    return result;
}

static rt_err_t spinand_program_execute(struct rt_qspi_device *qspi,  uint8_t u8Addr2, uint8_t u8Addr1, uint8_t u8Addr0)
{
    rt_err_t result;
    uint8_t au8Cmd[4], u8SR;

    au8Cmd[0] = 0x10 ;
    au8Cmd[1] = u8Addr2;
    au8Cmd[2] = u8Addr1;
    au8Cmd[3] = u8Addr0;

    if ((result = nu_qspi_send(qspi, &au8Cmd, sizeof(au8Cmd))) != RT_EOK)
        goto exit_spinand_program_execute;

    if (spinand_isbusy(qspi))
    {
        result = -RT_MTD_EIO;
        goto exit_spinand_program_execute;
    }

    u8SR = (spinand_status_register_read(SPINAND_FLASH_QSPI, 3) & 0x0C) >> 2;
    if (u8SR == 1)
    {
        result = -RT_MTD_EIO;
        LOG_E("Error write status!");
    }

exit_spinand_program_execute:

    return result;
}

static rt_err_t spinand_normal_read(struct rt_qspi_device *qspi, uint8_t u8AddrH, uint8_t u8AddrL, uint8_t *pu8Buff, uint32_t u32Count)
{
    uint8_t au8Cmd[4];

    au8Cmd[0] = 0x03;
    au8Cmd[1] = u8AddrH;
    au8Cmd[2] = u8AddrL;
    au8Cmd[3] = 0x00;

    return nu_qspi_send_then_recv(qspi, &au8Cmd[0], sizeof(au8Cmd), pu8Buff, u32Count);
}

static rt_err_t spinand_protect_set(struct rt_qspi_device *qspi, uint8_t u8Protect)
{
    /* Read status register 1 */
    uint8_t u8SR = spinand_status_register_read(qspi, 1);

    if (u8Protect)
    {
        /* protect */
        u8SR |= 0x7C;
    }
    else
    {
        /* unprotect */
        u8SR &= 0x83;
    }

    return spinand_status_register_write(qspi, 1, u8SR);
}

static uint8_t spinand_program_erase_isfail(struct rt_qspi_device *qspi)
{
    /* Read status register 3 */
    uint8_t u8SR = spinand_status_register_read(qspi, 3);
    return (u8SR & 0x0C) >> 2; /* Check P-Fail, E-Fail bit */
}

static uint8_t spinand_hwecc_status_get(struct rt_qspi_device *qspi)
{
    /* Read status register 3 */
    uint8_t u8SR = spinand_status_register_read(qspi, 3);
    return (u8SR & 0x30) >> 4; /* ECC-1, ECC0 bit */
}

static rt_err_t spinand_hwecc_set(struct rt_qspi_device *qspi, uint8_t u8Enable)
{
    uint8_t u8SR = spinand_status_register_read(qspi, 2); // Read status register 2

    if (u8Enable)
    {
        u8SR |= 0x10; // Enable ECC-E bit
    }
    else
    {
        u8SR &= 0xEF; // Disable ECC-E bit
    }

    return spinand_status_register_write(qspi, 2, u8SR);
}

static uint8_t spinand_hwecc_get(struct rt_qspi_device *qspi)
{
    /* Read status register 2 */
    uint8_t u8SR = spinand_status_register_read(qspi, 2);
    return (u8SR & 0x10) >> 4;
}

static rt_err_t spinand_read_dataload(struct rt_qspi_device *qspi, uint8_t u8Addr2, uint8_t u8Addr1, uint8_t u8Addr0)
{
    rt_err_t result = RT_EOK;
    uint8_t au8Cmd[4];
    uint8_t u8SR;

    au8Cmd[0] = 0x13 ;
    au8Cmd[1] = u8Addr2;
    au8Cmd[2] = u8Addr1;
    au8Cmd[3] = u8Addr0;

    if ((result = nu_qspi_send(qspi, &au8Cmd[0], sizeof(au8Cmd))) != RT_EOK)
        goto exit_spinand_read_dataload;

    if (spinand_isbusy(qspi))
    {
        result = -RT_EIO;
        goto exit_spinand_read_dataload;
    }

    u8SR = spinand_hwecc_status_get(SPINAND_FLASH_QSPI);
    if ((u8SR != 0x00) && (u8SR != 0x01))
    {
        result = -RT_MTD_EECC;
        LOG_E("Error ECC status error[0x%x].", u8SR);
    }

exit_spinand_read_dataload:

    return result;
}

static uint8_t spinand_block_isbad(struct rt_qspi_device *qspi, uint32_t u32PageAddr)
{
    rt_err_t result;
    uint8_t read_buf;

again_spinand_block_isbad:

    result = spinand_read_dataload(qspi, (u32PageAddr >> 16) & 0xFF, (u32PageAddr >> 8) & 0xFF, u32PageAddr & 0xFF); // Read the first page of a block
    RT_ASSERT(result == RT_EOK);

    result = spinand_normal_read(qspi, (SPINAND_FLASH_PAGE_SIZE >> 8) & 0xff, SPINAND_FLASH_PAGE_SIZE & 0xff, &read_buf, 1); // Read bad block mark at 0x800 update at v.1.0.8
    RT_ASSERT(result == RT_EOK);

    if (read_buf != 0xFF)
    {
        // update at v.1.0.7
        return 1;
    }

    if (((u32PageAddr % (SPINAND_FLASH_PAGE_PER_BLOCK_NUM * SPINAND_FLASH_PAGE_SIZE)) == 0))
    {
        /* Need check second page again. */
        u32PageAddr++;
        goto again_spinand_block_isbad;
    }

    return 0;
}

static rt_err_t spinand_buffermode_set(struct rt_qspi_device *qspi, uint8_t u8Enable)
{
    uint8_t u8SR = spinand_status_register_read(qspi, 2); // Read status register 2

    if (u8Enable)
    {
        u8SR |= 0x08; // Enable BUF bit
    }
    else
    {
        u8SR &= 0xF7; // Disable BUF bit
    }
    return spinand_status_register_write(qspi, 2, u8SR);
}

static rt_err_t spinand_block_erase(struct rt_qspi_device *qspi, uint8_t u8Addr2, uint8_t u8Addr1, uint8_t u8Addr0)
{
    rt_err_t result;
    uint8_t u8WECmd = 0x06;
    uint8_t au8EraseCmd[4], u8SR;

    au8EraseCmd[0] = 0xD8;
    au8EraseCmd[1] = u8Addr2;
    au8EraseCmd[2] = u8Addr1;
    au8EraseCmd[3] = u8Addr0;

    if ((result = nu_qspi_send(qspi, &u8WECmd, sizeof(u8WECmd))) != RT_EOK)
        goto exit_spinand_block_erase;

    if ((result = nu_qspi_send(qspi, &au8EraseCmd[0], sizeof(au8EraseCmd))) != RT_EOK)
        goto exit_spinand_block_erase;

    if (spinand_isbusy(qspi))
        return -RT_EIO;

    u8SR = spinand_program_erase_isfail(SPINAND_FLASH_QSPI);
    if (u8SR != 0)
    {
        /* Fail to erase */
        LOG_E("Fail to erase. Will mark it bad.");
        result = -RT_ERROR;
        goto exit_spinand_block_erase;
    }

exit_spinand_block_erase:

    return result;
}

static rt_err_t spinand_block_markbad(struct rt_qspi_device *qspi,  uint32_t u32PageAddr)
{
    rt_err_t result = RT_EOK;

    uint8_t u8BadBlockMarker = 0xF0;

    result = spinand_block_erase(qspi, (u32PageAddr >> 16) & 0xFF, (u32PageAddr >> 8) & 0xFF, u32PageAddr & 0xFF);
    if (result != RT_EOK)
        return result;

    result = spinand_program_dataload(qspi, (SPINAND_FLASH_PAGE_SIZE >> 8) & 0xff, SPINAND_FLASH_PAGE_SIZE & 0xff, &u8BadBlockMarker, 1, 0, 0);
    if (result != RT_EOK)
        return result;

    return spinand_program_execute(qspi, (u32PageAddr >> 16) & 0xFF, (u32PageAddr >> 8) & 0xFF, u32PageAddr & 0xFF);
}

static rt_err_t spinand_read_quadoutput(
    struct rt_qspi_device *qspi,
    uint8_t u8AddrH,
    uint8_t u8AddrL,
    uint8_t *pu8DataBuff,
    uint32_t u32DataCount
)
{
    struct rt_qspi_message qspi_messages = {0};

    /* 1-bit mode */
    qspi_messages.instruction.content    = SPINAND_FLASH_QUADREAD_CMDID;
    qspi_messages.instruction.qspi_lines = 1;

    qspi_messages.address.content = (u8AddrH << 8) | (u8AddrL);
    qspi_messages.address.size = 2 * 8;
    qspi_messages.address.qspi_lines = 1;

    qspi_messages.dummy_cycles = SPINAND_FLASH_DUMMYBYTE * 8; //In bit

    /* 4-bit mode */
    qspi_messages.qspi_data_lines   = 4;
    qspi_messages.parent.cs_take    = 1;
    qspi_messages.parent.cs_release = 1;
    qspi_messages.parent.recv_buf   = pu8DataBuff;
    qspi_messages.parent.length     = u32DataCount;
    qspi_messages.parent.next       = RT_NULL;

    return nu_qspi_transfer_message(qspi, (struct rt_qspi_message *) &qspi_messages);
}

static rt_err_t spinand_jedecid_get(struct rt_qspi_device *qspi, uint32_t *pu32ID)
{
    uint32_t u32JedecId = 0;
    uint32_t u32JedecId_real = 0;
    uint8_t u8Cmd = 0x9F;

    if (nu_qspi_send_then_recv(qspi, &u8Cmd, 1, &u32JedecId, 4) != RT_EOK)
    {
        return -RT_ERROR;
    }

    /* Reverse order. */
    nu_set32_be((uint8_t *)&u32JedecId_real, u32JedecId);

    /* Only keep 3-bytes. */
    u32JedecId_real &= 0x00ffffff;

    *pu32ID = u32JedecId_real;

    return RT_EOK;
}

static rt_err_t spinand_reset(struct rt_qspi_device *qspi)
{
    rt_err_t result;
    uint8_t u8Cmd = 0xFF;

    if ((result = nu_qspi_send(qspi, &u8Cmd, 1)) != RT_EOK)
        goto exit_spinand_reset;

    if (spinand_isbusy(qspi))
    {
        result = RT_EIO;
        goto exit_spinand_reset;
    }

exit_spinand_reset:

    return result;
}

rt_err_t spinand_flash_init(struct rt_qspi_device *qspi)
{
    rt_err_t result;

    if ((result = spinand_reset(qspi)) != RT_EOK)
        goto  exit_spinand_init;

    if ((result = spinand_info_read(qspi)) != RT_EOK)
        goto exit_spinand_init;

    /* Un-protect */
    if ((result = spinand_protect_set(qspi, 0)) != RT_EOK)
        goto exit_spinand_init;

    /* Enable BUF mode */
    if ((result = spinand_buffermode_set(qspi, 1)) != RT_EOK)
        goto exit_spinand_init;

    /* Enable HWECC */
    if ((result = spinand_hwecc_set(qspi, 1)) != RT_EOK)
        goto exit_spinand_init;

    /* Check HWECC */
    if (!(spinand_hwecc_get(qspi)))
        goto exit_spinand_init;

    if (SPINAND_FLASH_MCP == 1)
    {
        /* Select die. */
        if ((result = spinand_die_select(qspi, SPINAND_DIE_ID1)) != RT_EOK)
            goto exit_spinand_init;

        /* Unprotect */
        if ((result = spinand_protect_set(qspi, 0)) != RT_EOK)
            goto exit_spinand_init;
    }

    LOG_I("Enabled BUF, HWECC. Unprotected.");

exit_spinand_init:

    return -result;
}

struct spinand_ops spinand_ops_wb =
{
    .block_erase      = spinand_block_erase,
    .block_isbad      = spinand_block_isbad,
    .block_markbad    = spinand_block_markbad,
    .die_select       = spinand_die_select,
    .jedecid_get      = spinand_jedecid_get,
    .program_dataload = spinand_program_dataload,
    .program_execute  = spinand_program_execute,
    .read_dataload    = spinand_read_dataload,
    .read_quadoutput  = spinand_read_quadoutput
};

static rt_err_t spinand_info_read(struct rt_qspi_device *qspi)
{
    int i;
    uint32_t u32JedecId = 0;

    if (spinand_jedecid_get(qspi, &u32JedecId) != RT_EOK)
        goto exit_spinand_info_read;

    for (i = 0 ; i < SPINAND_LIST_ELEMENT_NUM; i++)
    {
        if (u32JedecId == g_spinandflash_list[i].u32JEDECID)   /* Match JEDECID? */
        {
            rt_memcpy(SPINAND_FLASH_INFO, &g_spinandflash_list[i], sizeof(struct nu_spinand_info));
            LOG_I("Found: [%08X] %s.", u32JedecId, SPINAND_FLASH_DESCRIPTION);

            switch (u32JedecId & 0xff0000)
            {
            case 0xEF0000: /* Winbond */
                SPINAND_FLASH_OPS = &spinand_ops_wb;
                break;

            default:
                goto exit_spinand_info_read;
            }

            return RT_EOK;
        }
    }

exit_spinand_info_read:

    LOG_E("Can't find the flash[%08X] in supported list.", u32JedecId);
    return -RT_ERROR;
}

#endif
