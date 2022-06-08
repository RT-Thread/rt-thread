/**************************************************************************//**
 * @file     fmi_nand.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 18/08/05 5:17p $
 * @brief    NuMicro ARM9 FMI NAND driver source file
 *
 * @note
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
//#include <string.h>
#include "nand.h"
#include "N9H30.h"
#include "nu_sys.h"
#include "drv_sys.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup NAND_Driver NAND Driver
  @{
*/

/** @addtogroup NAND_EXPORTED_CONSTANTS NAND Exported Constants
  @{
*/
/// @cond HIDDEN_SYMBOLS


#define NAND_EN     0x08
#define READYBUSY   (0x01 << 18)
#define ENDADDR     (0x80000000)

/*-----------------------------------------------------------------------------
 * Define some constants for BCH
 *---------------------------------------------------------------------------*/
// define the total padding bytes for 512/1024 data segment
#define BCH_PADDING_LEN_512     32
#define BCH_PADDING_LEN_1024    64
// define the BCH parity code lenght for 512 bytes data pattern
#define BCH_PARITY_LEN_T4  8
#define BCH_PARITY_LEN_T8  15
#define BCH_PARITY_LEN_T12 23
#define BCH_PARITY_LEN_T15 29
// define the BCH parity code lenght for 1024 bytes data pattern
#define BCH_PARITY_LEN_T24 45


#define BCH_T15   0x00400000
#define BCH_T12   0x00200000
#define BCH_T8    0x00100000
#define BCH_T4    0x00080000
#define BCH_T24   0x00040000


struct nuvoton_nand_info
{
    struct nand_hw_control  controller;
    struct mtd_info         mtd;
    struct nand_chip        chip;
    int                     eBCHAlgo;
    int                     m_i32SMRASize;
};
struct nuvoton_nand_info g_nuvoton_nand;
struct nuvoton_nand_info *nuvoton_nand;

static struct nand_ecclayout nuvoton_nand_oob;

static const int g_i32BCHAlgoIdx[5] = { BCH_T4, BCH_T8, BCH_T12, BCH_T15, BCH_T24 };
static const int g_i32ParityNum[4][5] =
{
    { 8,    15,     23,     29,     -1  },  // For 512
    { 32,   60,     92,     116,    90  },  // For 2K
    { 64,   120,    184,    232,    180 },  // For 4K
    { 128,  240,    368,    464,    360 },  // For 8K
};

static void nuvoton_layout_oob_table(struct nand_ecclayout *pNandOOBTbl, int oobsize, int eccbytes)
{
    pNandOOBTbl->eccbytes = eccbytes;

    pNandOOBTbl->oobavail = oobsize - 4 - eccbytes ;

    pNandOOBTbl->oobfree[0].offset = 4;  // Bad block marker size

    pNandOOBTbl->oobfree[0].length = oobsize - eccbytes - pNandOOBTbl->oobfree[0].offset ;
}


static void nuvoton_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
    struct nand_chip *chip = mtd->priv;

    if (ctrl & NAND_CTRL_CHANGE)
    {
        uint32_t IO_ADDR_W = (uint32_t)REG_NANDDATA;

        if ((ctrl & NAND_CLE))
            IO_ADDR_W = REG_NANDCMD;
        if ((ctrl & NAND_ALE))
            IO_ADDR_W = REG_NANDADDR;

        chip->IO_ADDR_W = (void *)IO_ADDR_W;
    }

    if (cmd != NAND_CMD_NONE)
        outpb(chip->IO_ADDR_W, cmd);
}


/* select chip */
static void nuvoton_nand_select_chip(struct mtd_info *mtd, int chip)
{
    outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x06000000)) | 0x04000000);
}


static int nuvoton_dev_ready(struct mtd_info *mtd)
{
    return ((inpw(REG_NANDINTSTS) & READYBUSY) ? 1 : 0);
}


static void nuvoton_nand_command(struct mtd_info *mtd, unsigned int command, int column, int page_addr)
{
    register struct nand_chip *chip = mtd->priv;
    int volatile i;

    if (command == NAND_CMD_READOOB)
    {
        column += mtd->writesize;
        command = NAND_CMD_READ0;
    }

    outpw(REG_NANDCMD, command & 0xff);

    if (column != -1 || page_addr != -1)
    {
        if (column != -1)
        {
            outpw(REG_NANDADDR, column & 0xff);
            if (page_addr != -1)
                outpw(REG_NANDADDR, column >> 8);
            else
                outpw(REG_NANDADDR, (column >> 8) | ENDADDR);
        }

        if (page_addr != -1)
        {
            outpw(REG_NANDADDR, page_addr & 0xFF);

            if (chip->chipsize > (128 << 20))
            {
                outpw(REG_NANDADDR, (page_addr >> 8) & 0xFF);
                outpw(REG_NANDADDR, ((page_addr >> 16) & 0xFF) | ENDADDR);
            }
            else
            {
                outpw(REG_NANDADDR, ((page_addr >> 8) & 0xFF) | ENDADDR);
            }
        }
    }

    switch (command)
    {
    case NAND_CMD_CACHEDPROG:
    case NAND_CMD_PAGEPROG:
    case NAND_CMD_ERASE1:
    case NAND_CMD_ERASE2:
    case NAND_CMD_SEQIN:
    case NAND_CMD_RNDIN:
    case NAND_CMD_STATUS:
        return;

    case NAND_CMD_RESET:
        if (chip->dev_ready)
            break;

        if (chip->chip_delay)
            for (i = 0; i < chip->chip_delay; i++);

        outpw(REG_NANDCMD, NAND_CMD_STATUS);
        outpw(REG_NANDCMD, command);

        while (!(inpw(REG_NANDINTSTS) & READYBUSY));
        return;

    case NAND_CMD_RNDOUT:
        outpw(REG_NANDCMD, NAND_CMD_RNDOUTSTART);
        for (i = 0; i < 10; i++);
        return;

    case NAND_CMD_READ0:
        outpw(REG_NANDCMD, NAND_CMD_READSTART);
        break;
    default:
        if (!chip->dev_ready)
        {
            if (chip->chip_delay)
                for (i = 0; i < chip->chip_delay; i++);
            return;
        }
    }

    if (chip->chip_delay)
        for (i = 0; i < chip->chip_delay; i++);
    while (!(inpw(REG_NANDINTSTS) & READYBUSY)) ;

}

/*
 * nuvoton_nand_read_byte - read a byte from NAND controller into buffer
 * @mtd: MTD device structure
 */
static unsigned char nuvoton_nand_read_byte(struct mtd_info *mtd)
{
    return ((unsigned char)inpw(REG_NANDDATA));
}

/*
 * nuvoton_nand_write_buf - write data from buffer into NAND controller
 * @mtd: MTD device structure
 * @buf: virtual address in RAM of source
 * @len: number of data bytes to be transferred
 */

static void nuvoton_nand_write_buf(struct mtd_info *mtd, const unsigned char *buf, int len)
{
    int i;

    for (i = 0; i < len; i++)
        outpw(REG_NANDDATA, buf[i]);
}

/*
 * nuvoton_nand_read_buf - read data from NAND controller into buffer
 * @mtd: MTD device structure
 * @buf: virtual address in RAM of source
 * @len: number of data bytes to be transferred
 */
static void nuvoton_nand_read_buf(struct mtd_info *mtd, unsigned char *buf, int len)
{
    int i;

    for (i = 0; i < len; i++)
        buf[i] = (unsigned char)inpw(REG_NANDDATA);
}


/*
 * Enable HW ECC : unused on most chips
 */
void nuvoton_nand_enable_hwecc(struct mtd_info *mtd, int mode)
{
}

/*
 * Calculate HW ECC
 * function called after a write
 * mtd:        MTD block structure
 * dat:        raw data (unused)
 * ecc_code:   buffer for ECC
 */
static int nuvoton_nand_calculate_ecc(struct mtd_info *mtd, const u_char *dat, u_char *ecc_code)
{
    return 0;
}

/*
 * HW ECC Correction
 * function called after a read
 * mtd:        MTD block structure
 * dat:        raw data read from the chip
 * read_ecc:   ECC from the chip (unused)
 * isnull:     unused
 */
static int nuvoton_nand_correct_data(struct mtd_info *mtd, u_char *dat,
                                     u_char *read_ecc, u_char *calc_ecc)
{
    return 0;
}


/*-----------------------------------------------------------------------------
 * Correct data by BCH alrogithm.
 *      Support 8K page size NAND and BCH T4/8/12/15/24.
 *---------------------------------------------------------------------------*/
void fmiSM_CorrectData_BCH(u8 ucFieidIndex, u8 ucErrorCnt, u8 *pDAddr)
{
    u32 uaData[24], uaAddr[24];
    u32 uaErrorData[6];
    u8  ii, jj;
    u32 uPageSize;
    u32 field_len, padding_len, parity_len;
    u32 total_field_num;
    u8  *smra_index;

    //--- assign some parameters for different BCH and page size
    switch (inpw(REG_NANDCTL) & 0x007C0000)
    {
    case BCH_T24:
        field_len   = 1024;
        padding_len = BCH_PADDING_LEN_1024;
        parity_len  = BCH_PARITY_LEN_T24;
        break;
    case BCH_T15:
        field_len   = 512;
        padding_len = BCH_PADDING_LEN_512;
        parity_len  = BCH_PARITY_LEN_T15;
        break;
    case BCH_T12:
        field_len   = 512;
        padding_len = BCH_PADDING_LEN_512;
        parity_len  = BCH_PARITY_LEN_T12;
        break;
    case BCH_T8:
        field_len   = 512;
        padding_len = BCH_PADDING_LEN_512;
        parity_len  = BCH_PARITY_LEN_T8;
        break;
    case BCH_T4:
        field_len   = 512;
        padding_len = BCH_PADDING_LEN_512;
        parity_len  = BCH_PARITY_LEN_T4;
        break;
    default:
        return;
    }

    uPageSize = inpw(REG_NANDCTL) & 0x00030000;
    switch (uPageSize)
    {
    case 0x30000:
        total_field_num = 8192 / field_len;
        break;
    case 0x20000:
        total_field_num = 4096 / field_len;
        break;
    case 0x10000:
        total_field_num = 2048 / field_len;
        break;
    case 0x00000:
        total_field_num =  512 / field_len;
        break;
    default:
        return;
    }

    //--- got valid BCH_ECC_DATAx and parse them to uaData[]
    // got the valid register number of BCH_ECC_DATAx since one register include 4 error bytes
    jj = ucErrorCnt / 4;
    jj ++;
    if (jj > 6)
        jj = 6;     // there are 6 BCH_ECC_DATAx registers to support BCH T24

    for (ii = 0; ii < jj; ii++)
    {
        uaErrorData[ii] = inpw(REG_NANDECCED0 + ii * 4);
    }

    for (ii = 0; ii < jj; ii++)
    {
        uaData[ii * 4 + 0] = uaErrorData[ii] & 0xff;
        uaData[ii * 4 + 1] = (uaErrorData[ii] >> 8) & 0xff;
        uaData[ii * 4 + 2] = (uaErrorData[ii] >> 16) & 0xff;
        uaData[ii * 4 + 3] = (uaErrorData[ii] >> 24) & 0xff;
    }

    //--- got valid REG_BCH_ECC_ADDRx and parse them to uaAddr[]
    // got the valid register number of REG_BCH_ECC_ADDRx since one register include 2 error addresses
    jj = ucErrorCnt / 2;
    jj ++;
    if (jj > 12)
        jj = 12;    // there are 12 REG_BCH_ECC_ADDRx registers to support BCH T24

    for (ii = 0; ii < jj; ii++)
    {
        uaAddr[ii * 2 + 0] = inpw(REG_NANDECCEA0 + ii * 4) & 0x07ff; // 11 bits for error address
        uaAddr[ii * 2 + 1] = (inpw(REG_NANDECCEA0 + ii * 4) >> 16) & 0x07ff;
    }

    //--- pointer to begin address of field that with data error
    pDAddr += (ucFieidIndex - 1) * field_len;

    //--- correct each error bytes
    for (ii = 0; ii < ucErrorCnt; ii++)
    {
        // for wrong data in field
        if (uaAddr[ii] < field_len)
        {
            *(pDAddr + uaAddr[ii]) ^= uaData[ii];
        }
        // for wrong first-3-bytes in redundancy area
        else if (uaAddr[ii] < (field_len + 3))
        {
            uaAddr[ii] -= field_len;
            uaAddr[ii] += (parity_len * (ucFieidIndex - 1)); // field offset
            *((u8 *)REG_NANDRA0 + uaAddr[ii]) ^= uaData[ii];
        }
        // for wrong parity code in redundancy area
        else
        {
            // BCH_ERR_ADDRx = [data in field] + [3 bytes] + [xx] + [parity code]
            //                                   |<--     padding bytes      -->|
            // The BCH_ERR_ADDRx for last parity code always = field size + padding size.
            // So, the first parity code = field size + padding size - parity code length.
            // For example, for BCH T12, the first parity code = 512 + 32 - 23 = 521.
            // That is, error byte address offset within field is
            uaAddr[ii] = uaAddr[ii] - (field_len + padding_len - parity_len);

            // smra_index point to the first parity code of first field in register SMRA0~n
            smra_index = (u8 *)
                         (REG_NANDRA0 + (inpw(REG_NANDRACTL) & 0x1ff) - // bottom of all parity code -
                          (parity_len * total_field_num)                             // byte count of all parity code
                         );

            // final address = first parity code of first field +
            //                 offset of fields +
            //                 offset within field
            *((u8 *)smra_index + (parity_len * (ucFieidIndex - 1)) + uaAddr[ii]) ^= uaData[ii];
        }
    }   // end of for (ii<ucErrorCnt)
}

int fmiSMCorrectData(struct mtd_info *mtd, unsigned long uDAddr)
{
    int uStatus, ii, jj, i32FieldNum = 0;
    volatile int uErrorCnt = 0;

    if (inpw(REG_NANDINTSTS) & 0x4)
    {
        if ((inpw(REG_NANDCTL) & 0x7C0000) == BCH_T24)
            i32FieldNum = mtd->writesize / 1024;    // Block=1024 for BCH
        else
            i32FieldNum = mtd->writesize / 512;

        if (i32FieldNum < 4)
            i32FieldNum  = 1;
        else
            i32FieldNum /= 4;

        for (jj = 0; jj < i32FieldNum; jj++)
        {
            uStatus = inpw(REG_NANDECCES0 + jj * 4);
            if (!uStatus)
                continue;

            for (ii = 1; ii < 5; ii++)
            {
                if (!(uStatus & 0x03))     // No error
                {

                    uStatus >>= 8;
                    continue;

                }
                else if ((uStatus & 0x03) == 0x01)     // Correctable error
                {

                    uErrorCnt = (uStatus >> 2) & 0x1F;
                    fmiSM_CorrectData_BCH(jj * 4 + ii, uErrorCnt, (u8 *)uDAddr);

                    uStatus >>= 8;
                    continue;
                }
                else   // uncorrectable error or ECC error
                {
                    return -1;
                }
            }
        } //jj
    }
    return uErrorCnt;
}


static __inline int _nuvoton_nand_dma_transfer(struct mtd_info *mtd, const u_char *addr, unsigned int len, int is_write)
{
    struct nuvoton_nand_info *nand = nuvoton_nand;

    // For save, wait DMAC to ready
    while (inpw(REG_FMI_DMACTL) & 0x200);

    // Reinitial dmac
    // DMAC enable
    outpw(REG_FMI_DMACTL, inpw(REG_FMI_DMACTL) | 0x3);
    while (inpw(REG_FMI_DMACTL) & 0x2);

    // Clear DMA finished flag
    outpw(REG_NANDINTSTS, inpw(REG_NANDINTSTS) | 0x1);

    // Disable Interrupt
    outpw(REG_NANDINTEN, inpw(REG_NANDINTEN) & ~(0x1));

#if defined(BSP_USING_MMU)
    mmu_clean_invalidated_dcache((uint32_t)addr, len);
#endif
    // Fill dma_addr
    outpw(REG_FMI_DMASA, (unsigned long)addr);

    // Enable target abort interrupt generation during DMA transfer.
    outpw(REG_FMI_DMAINTEN, 0x1);

    // Clear Ready/Busy 0 Rising edge detect flag
    outpw(REG_NANDINTSTS, 0x400);

    // Set which BCH algorithm
    if (nand->eBCHAlgo >= 0)
    {
        // Set BCH algorithm
        outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x7C0000)) | g_i32BCHAlgoIdx[nand->eBCHAlgo]);
        // Enable H/W ECC, ECC parity check enable bit during read page
        outpw(REG_NANDCTL, inpw(REG_NANDCTL) | 0x00800080);
    }
    else
    {
        // Disable H/W ECC / ECC parity check enable bit during read page
        outpw(REG_NANDCTL, inpw(REG_NANDCTL) & (~0x00800080));
    }

    outpw(REG_NANDRACTL, nand->m_i32SMRASize);

    outpw(REG_NANDINTEN, inpw(REG_NANDINTEN) & (~0x4));

    outpw(REG_NANDINTSTS, 0x4);

    // Enable SM_CS0
    outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x06000000)) | 0x04000000);
    /* setup and start DMA using dma_addr */

    if (is_write)
    {
        register char *ptr = (char *)REG_NANDRA0;
        // To mark this page as dirty.
        if (ptr[3] == 0xFF)
            ptr[3] = 0;
        if (ptr[2] == 0xFF)
            ptr[2] = 0;

        outpw(REG_NANDCTL, inpw(REG_NANDCTL) | 0x4);
        while (!(inpw(REG_NANDINTSTS) & 0x1));

    }
    else
    {
        // Blocking for reading
        // Enable DMA Read

        outpw(REG_NANDCTL, inpw(REG_NANDCTL) | 0x2);

        if (inpw(REG_NANDCTL) & 0x80)
        {
            do
            {
                int stat = 0;
                if ((stat = fmiSMCorrectData(mtd, (unsigned long)addr)) < 0)
                {
                    mtd->ecc_stats.failed++;
                    outpw(REG_NANDINTSTS, 0x4);
                    outpw(REG_FMI_DMACTL, 0x3);          // reset DMAC
                    outpw(REG_NANDCTL, inpw(REG_NANDCTL) | 0x1);
                    break;
                }
                else if (stat > 0)
                {
                    //mtd->ecc_stats.corrected += stat; //Occure: MLC UBIFS mount error
                    outpw(REG_NANDINTSTS, 0x4);
                }

            }
            while (!(inpw(REG_NANDINTSTS) & 0x1) || (inpw(REG_NANDINTSTS) & 0x4));
        }
        else
            while (!(inpw(REG_NANDINTSTS) & 0x1));
    }

    // Clear DMA finished flag
    outpw(REG_NANDINTSTS, inpw(REG_NANDINTSTS) | 0x1);

    return 0;
}


/**
 * nand_write_page_hwecc - [REPLACABLE] hardware ecc based page write function
 * @mtd:        mtd info structure
 * @chip:       nand chip info structure
 * @buf:        data buffer
 */
static int nuvoton_nand_write_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip, const uint8_t *buf, int oob_required, int page)
{
    uint8_t *ecc_calc = chip->buffers->ecccalc;
    uint32_t hweccbytes = chip->ecc.layout->eccbytes;
    register char *ptr = (char *)REG_NANDRA0;

    //debug("nuvoton_nand_write_page_hwecc\n");
    memset((void *)ptr, 0xFF, mtd->oobsize);
    memcpy((void *)ptr, (void *)chip->oob_poi,  mtd->oobsize - chip->ecc.total);

    _nuvoton_nand_dma_transfer(mtd, buf, mtd->writesize, 0x1);

    // Copy parity code in SMRA to calc
    memcpy((void *)ecc_calc, (void *)(REG_NANDRA0 + (mtd->oobsize - chip->ecc.total)), chip->ecc.total);

    // Copy parity code in calc to oob_poi
    memcpy((void *)(chip->oob_poi + hweccbytes), (void *)ecc_calc, chip->ecc.total);

    return 0;
}

/**
 * nuvoton_nand_read_page_hwecc_oob_first - hardware ecc based page write function
 * @mtd:        mtd info structure
 * @chip:       nand chip info structure
 * @buf:        buffer to store read data
 * @page:       page number to read
 */
static int nuvoton_nand_read_page_hwecc_oob_first(struct mtd_info *mtd, struct nand_chip *chip, uint8_t *buf, int oob_required, int page)
{
    int eccsize = chip->ecc.size;
    uint8_t *p = buf;
    char *ptr = (char *)REG_NANDRA0;
    int volatile i;

    //debug("nuvoton_nand_read_page_hwecc_oob_first\n");
    /* At first, read the OOB area  */
    nuvoton_nand_command(mtd, NAND_CMD_READOOB, 0, page);
    nuvoton_nand_read_buf(mtd, chip->oob_poi, mtd->oobsize);

    // Second, copy OOB data to SMRA for page read
    memcpy((void *)ptr, (void *)chip->oob_poi, mtd->oobsize);

    // Third, read data from nand
    nuvoton_nand_command(mtd, NAND_CMD_READ0, 0, page);
    _nuvoton_nand_dma_transfer(mtd, p, eccsize, 0x0);

    // Fouth, restore OOB data from SMRA
    memcpy((void *)chip->oob_poi, (void *)ptr, mtd->oobsize);

    return 0;
}

/**
 * nuvoton_nand_read_oob_hwecc - [REPLACABLE] the most common OOB data read function
 * @mtd:        mtd info structure
 * @chip:       nand chip info structure
 * @page:       page number to read
 * @sndcmd:     flag whether to issue read command or not
 */
static int nuvoton_nand_read_oob_hwecc(struct mtd_info *mtd, struct nand_chip *chip, int page)
{
    char *ptr = (char *)REG_NANDRA0;

    /* At first, read the OOB area  */
    nuvoton_nand_command(mtd, NAND_CMD_READOOB, 0, page);

    nuvoton_nand_read_buf(mtd, chip->oob_poi, mtd->oobsize);

    // Second, copy OOB data to SMRA for page read
    memcpy((void *)ptr, (void *)chip->oob_poi, mtd->oobsize);

    return 0;
}

int board_nand_init(struct nand_chip *nand)
{
    struct mtd_info *mtd;

    nuvoton_nand = &g_nuvoton_nand;
    memset((void *)nuvoton_nand, 0, sizeof(struct nuvoton_nand_info));

    if (!nuvoton_nand)
        return -1;

    mtd = &nuvoton_nand->mtd;
    nuvoton_nand->chip.controller = &nuvoton_nand->controller;

    /* initialize nand_chip data structure */
    nand->IO_ADDR_R = (void *)REG_NANDDATA;
    nand->IO_ADDR_W = (void *)REG_NANDDATA;

    /* read_buf and write_buf are default */
    /* read_byte and write_byte are default */
    /* hwcontrol always must be implemented */
    nand->cmd_ctrl = nuvoton_hwcontrol;
    nand->cmdfunc = nuvoton_nand_command;
    nand->dev_ready = nuvoton_dev_ready;
    nand->select_chip = nuvoton_nand_select_chip;

    nand->read_byte = nuvoton_nand_read_byte;
    nand->write_buf = nuvoton_nand_write_buf;
    nand->read_buf = nuvoton_nand_read_buf;
    nand->chip_delay = 50;

    nand->controller = &nuvoton_nand->controller;

    nand->ecc.mode      = NAND_ECC_HW_OOB_FIRST;
    nand->ecc.hwctl     = nuvoton_nand_enable_hwecc;
    nand->ecc.calculate = nuvoton_nand_calculate_ecc;
    nand->ecc.correct   = nuvoton_nand_correct_data;
    nand->ecc.write_page = nuvoton_nand_write_page_hwecc;
    nand->ecc.read_page = nuvoton_nand_read_page_hwecc_oob_first;
    nand->ecc.read_oob  = nuvoton_nand_read_oob_hwecc;

    nand->ecc.layout    = &nuvoton_nand_oob;
    nand->ecc.strength  = 4;
    mtd = nand_to_mtd(nand);

    mtd->priv = nand;

    /* initial NAND controller */
    outpw(REG_CLK_HCLKEN, (inpw(REG_CLK_HCLKEN) | 0x300000));

//    /* select NAND function pins */
//    if (inpw(REG_SYS_PWRON) & 0x08000000)
//    {
//        /* Set GPI1~15 for NAND */
//        outpw(REG_SYS_GPI_MFPL, 0x55555550);
//        outpw(REG_SYS_GPI_MFPH, 0x55555555);
//    }
//    else
//    {
//        /* Set GPC0~14 for NAND */
//        outpw(REG_SYS_GPC_MFPL, 0x55555555);
//        outpw(REG_SYS_GPC_MFPH, 0x05555555);
//    }

    // Enable SM_EN
    outpw(REG_FMI_CTL, NAND_EN);
    outpw(REG_NANDTMCTL, 0x20305);

    // Enable SM_CS0
    outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x06000000)) | 0x04000000);
    outpw(REG_NANDECTL, 0x1); /* un-lock write protect */

    // NAND Reset
    outpw(REG_NANDCTL, inpw(REG_NANDCTL) | 0x1);    // software reset
    while (inpw(REG_NANDCTL) & 0x1);

    /* Detect NAND chips */
    /* first scan to find the device and get the page size */
    if (nand_scan_ident(mtd, 1, NULL))
    {
        sysprintf("NAND Flash not found !\n");
        return -1;
    }

    //Set PSize bits of SMCSR register to select NAND card page size
    switch (mtd->writesize)
    {
    case 2048:
        outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x30000)) + 0x10000);
        nuvoton_nand->eBCHAlgo = 0; /* T4 */
        nuvoton_layout_oob_table(&nuvoton_nand_oob, mtd->oobsize, g_i32ParityNum[1][nuvoton_nand->eBCHAlgo]);
        break;

    case 4096:
        outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x30000)) + 0x20000);
        nuvoton_nand->eBCHAlgo = 1; /* T8 */
        nuvoton_layout_oob_table(&nuvoton_nand_oob, mtd->oobsize, g_i32ParityNum[2][nuvoton_nand->eBCHAlgo]);
        break;

    case 8192:
        outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x30000)) + 0x30000);
        nuvoton_nand->eBCHAlgo = 2; /* T12 */
        nuvoton_layout_oob_table(&nuvoton_nand_oob, mtd->oobsize, g_i32ParityNum[3][nuvoton_nand->eBCHAlgo]);
        break;

    default:
        sysprintf("NUVOTON NAND CONTROLLER IS NOT SUPPORT THE PAGE SIZE. (%d, %d)\n", mtd->writesize, mtd->oobsize);
    }

    /* check power on setting */
    if ((inpw(REG_SYS_PWRON) & 0x300) != 0x300)
    {
        switch (inpw(REG_SYS_PWRON) & 0x300)
        {
        case 0x000:
            nuvoton_nand->eBCHAlgo = 2;
            break;
        case 0x100:
            nuvoton_nand->eBCHAlgo = 3;
            break;
        case 0x200:
            nuvoton_nand->eBCHAlgo = 4;
            break;
        default:
            sysprintf("wrong ECC power-on-setting\n");
        }
    }
    if ((inpw(REG_SYS_PWRON) & 0xc0) != 0xc0)
    {
        switch (inpw(REG_SYS_PWRON) & 0xc0)
        {
        case 0x00:
            mtd->writesize = 2048;
            outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x30000)) + 0x10000);
            mtd->oobsize = g_i32ParityNum[1][nuvoton_nand->eBCHAlgo] + 8;
            nuvoton_layout_oob_table(&nuvoton_nand_oob, mtd->oobsize, g_i32ParityNum[1][nuvoton_nand->eBCHAlgo]);
            break;

        case 0x40:
            mtd->writesize = 4096;
            outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x30000)) + 0x20000);
            mtd->oobsize = g_i32ParityNum[2][nuvoton_nand->eBCHAlgo] + 8;
            nuvoton_layout_oob_table(&nuvoton_nand_oob, mtd->oobsize, g_i32ParityNum[2][nuvoton_nand->eBCHAlgo]);
            break;

        case 0x80:
            mtd->writesize = 8192;
            outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x30000)) + 0x30000);
            mtd->oobsize = g_i32ParityNum[3][nuvoton_nand->eBCHAlgo] + 8;
            nuvoton_layout_oob_table(&nuvoton_nand_oob, mtd->oobsize, g_i32ParityNum[3][nuvoton_nand->eBCHAlgo]);
            break;

        default:
            sysprintf("wrong NAND page power-on-setting\n");
        }
    }
    nuvoton_nand->m_i32SMRASize  = mtd->oobsize;
    nand->ecc.bytes = nuvoton_nand_oob.eccbytes;
    nand->ecc.size  = mtd->writesize;

    nand->options = 0;
    //nand->bbt_options = (NAND_BBT_USE_FLASH | NAND_BBT_NO_OOB);

    // Redundant area size
    outpw(REG_NANDRACTL, nuvoton_nand->m_i32SMRASize);

    // Protect redundant 3 bytes
    // because we need to implement write_oob function to partial data to oob available area.
    // Please note we skip 4 bytes
    outpw(REG_NANDCTL, inpw(REG_NANDCTL) | 0x100);

    // To read/write the ECC parity codes automatically from/to NAND Flash after data area field written.
    outpw(REG_NANDCTL, inpw(REG_NANDCTL) | 0x10);
    // Set BCH algorithm
    outpw(REG_NANDCTL, (inpw(REG_NANDCTL) & (~0x007C0000)) | g_i32BCHAlgoIdx[nuvoton_nand->eBCHAlgo]);
    // Enable H/W ECC, ECC parity check enable bit during read page
    outpw(REG_NANDCTL, inpw(REG_NANDCTL) | 0x00800080);

    return 0;
}

/// @endcond HIDDEN_SYMBOLS


/*@}*/ /* end of group NAND_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NAND_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
