/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "sata/imx_sata.h"
#include "atapi.h"
#include "registers/regsccm.h"
#include "registers/regsiomuxc.h"
#include "soc_memory_map.h"
#include "timer/timer.h"
#include "registers.h"
#include "buffers.h"

//////////////////////////////////////////////////////////////////////////////
// Definitions
/////////////////////////////////////////////////////////////////////////////
#define PRINT(opt,fmt,args...) \
	if(opt) \
		printf(fmt, ## args)

sata_command_header_t *cmdhdr = NULL;
sata_command_table_t *cmdtbl = NULL;
//sata_ahci_regs_t *imx_sata_host = (sata_ahci_regs_t *) SATA_BASE_ADDR;
//sata_port_regs_t *imx_sata_port0 =
//    (sata_port_regs_t *) SATA_PORT_N_BASE_ADDRESS(0, SATA_BASE_ADDR);
sata_identify_data_t hdd_ident;
disk_identify_t ident;

static sata_phy_ref_clk_t sata_phy_clk_sel = OSC_UNKNOWN;

//////////////////////////////////////////////////////////////////////////////
// CODE
/////////////////////////////////////////////////////////////////////////////
extern void sata_clock_enable(void);
extern void sata_power_on(void);
void sata_get_phy_src_clk(sata_phy_ref_clk_t *);

static void sata_ahci_host_info_print(void);
static sata_return_t sata_ahci_set_port_idle(u32 port);
static sata_return_t sata_ahci_port_reset(u32 port);

static void sata_clock_init(sata_phy_ref_clk_t * phyclk);
static sata_return_t sata_hdd_init(u32 port);
static sata_return_t ahci_find_empty_slot(u32 port);
static sata_return_t sata_wait_command_done(u32 port);

static sata_return_t sata_reg_fis_h2d(u32 port, 
                                      u32 sect_addr,
                                      u32 sect_cnt,
                                      u32 rw, 
                                      u32 command, 
                                      char features, 
                                      u32 size, 
                                      u32 data_addr,  
                                      sata_command_header_t * cmdh, 
                                      sata_command_table_t * cmdt); 
static sata_return_t sata_non_queued_error_recovery(u32 port);
static sata_return_t sata_phy_cr_ack_polling(u32 max_iterations, u32 expected_val, u32 port);
static sata_return_t sata_phy_cr_write(u32 addr, u32 val, u32 port);
static sata_return_t sata_phy_cr_read(u32 addr, u32 * data, u32 port);
static sata_return_t sata_phy_cr_addr(u32 addr, u32 port);
static void sata_phy_config_mpll(char prop_ctl, char int_ctl, char ncy5, char ncy, char prescale);

/*!
 * @brief Read some sectors to SATA disk from SATA HDD
 *
 * @param start_block - Address of start sector
 * @param buf         - Pointer of destination buffer
 * @param len         - Length to read
 * @param port        - SATA port
 * @return SATA_PASS or SATA_FAIL
 */
sata_return_t sata_pio_read_sector(u32 start_block, u8 * buf, u32 len, u32 port)
{
    u32 sect_cnt = 0;
    u32 sect_start_addr = 0;
    sata_return_t ret = SATA_FAIL;
    sect_cnt = len / SATA_HDD_SECTOR_SIZE;
    sect_start_addr = start_block;  //*SATA_HDD_SECTOR_SIZE;
    u32 try_times = 10;

  exec:

    if (try_times == 0) {
        //PRINT(0,"+SATAERR: !error@sata_pio_read_sector blk%d@0x%08x,len%d\n",start_block,buf,len);
        return (!ret);
    }

    cmdhdr = (sata_command_header_t *) SATA_COMMAND_LIST_BASE;
    cmdtbl = (sata_command_table_t *) SATA_COMMAND_TABLE_BASE;

    ret = sata_reg_fis_h2d(port,
                           sect_start_addr,
                           sect_cnt,
                           SATA_READ, ATAPI_COMMAND_READ_SECTOR, 0, len, (u32) buf, cmdhdr, cmdtbl);

    if (ret == SATA_FAIL) {
        PRINT(0, "+SATAERR: !error@sata_pio_read_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);

        if (SATA_PASS == sata_non_queued_error_recovery(port)) {
            try_times--;
            goto exec;
        }
    }

    ret = sata_wait_command_done(port);

    if (ret == SATA_FAIL) {
        PRINT(0, "+SATAERR: !error@sata_pio_read_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);

        if (SATA_PASS == sata_non_queued_error_recovery(port)) {
            try_times--;
            goto exec;
        }
    }

    try_times--;

    return (!ret);
}


/*!
 * @brief Write some sectors to SATA disk from SATA HDD
 *
 * @param start_block Address of start sector
 * @param buf Pointer of destination buffer
 * @param len Length to read
 * @return SATA_PASS or SATA_FAIL
 */
sata_return_t sata_pio_write_sector(u32 start_block, u8 * buf, u32 len, u32 port)
{
    u32 sect_cnt = 0;
    u32 sect_start_addr = 0;
    sata_return_t ret = SATA_FAIL;
    u32 try_times = 10;

    sect_cnt = len / SATA_HDD_SECTOR_SIZE;
    sect_start_addr = start_block;  //*SATA_HDD_SECTOR_SIZE;

  exec:

    if (try_times == 0) {
        PRINT(0, "+SATAERR: !error@sata_pio_write_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);
        return (!ret);
    }

    cmdhdr = (sata_command_header_t *) SATA_COMMAND_LIST_BASE;
    cmdtbl = (sata_command_table_t *) SATA_COMMAND_TABLE_BASE;

    ret = sata_reg_fis_h2d(port,
                           sect_start_addr,
                           sect_cnt,
                           SATA_WRITE,
                           ATAPI_COMMAND_WRITE_SECTOR, 0, len, (u32) buf, cmdhdr, cmdtbl);

    if (ret == SATA_FAIL) {
        PRINT(0, "+SATAERR: !error@sata_pio_read_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);

        if (SATA_PASS == sata_non_queued_error_recovery(port)) {
            try_times--;
            goto exec;
        }
    }

    ret = sata_wait_command_done(port);

    if (ret == SATA_FAIL) {
        PRINT(0, "+SATAERR: !error@sata_pio_write_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);

        if (SATA_PASS == sata_non_queued_error_recovery(port)) {
            try_times--;
            goto exec;
        }
    }

    return (!ret);
}

/*!
 * @brief This function read some sectors from SATA HDD through Port DMA
 *
 * @param start_block Address of start sector
 * @param ident_data Pointer of destination buffer
 * @param len Length to read
 * @return SATA_PASS or SATA_FAIL
 */
sata_return_t sata_dma_read_sector(u32 start_block, u8 * buf, u32 len, u32 port)
{
    u32 sect_cnt = 0;
    u32 sect_start_addr = 0;
    sata_return_t ret = SATA_FAIL;
    sect_cnt = len / SATA_HDD_SECTOR_SIZE;
    sect_start_addr = start_block;  //*SATA_HDD_SECTOR_SIZE;
    u32 try_times = 10;
  exec:

    if (try_times == 0) {
        PRINT(0, "+SATAERR: !error@sata_dma_read_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);
        return (!ret);
    }

    cmdhdr = (sata_command_header_t *) SATA_COMMAND_LIST_BASE;
    cmdtbl = (sata_command_table_t *) SATA_COMMAND_TABLE_BASE;

    ret = sata_reg_fis_h2d(port,
                           sect_start_addr,
                           sect_cnt,
                           SATA_READ, ATAPI_COMMAND_READ_DMA, 0, len, (u32) buf, cmdhdr, cmdtbl);

    if (ret == SATA_FAIL) {
        PRINT(0, "+SATAERR: !error@sata_pio_read_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);

        if (SATA_PASS == sata_non_queued_error_recovery(port)) {
            try_times--;
            goto exec;
        }
    }

    ret = sata_wait_command_done(port);

    if (ret == SATA_FAIL) {
        PRINT(0, "+SATAERR: !error@sata_dma_read_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);

        if (SATA_PASS == sata_non_queued_error_recovery(port)) {
            try_times--;
            goto exec;
        }
    }

    return (!ret);
}

sata_return_t sata_dma_write_sector(u32 start_block, u8 * buf, u32 len, u32 port)
{
    u32 sect_cnt = 0;
    u32 sect_start_addr = 0;
    sata_return_t ret = SATA_FAIL;

    sect_cnt = len / SATA_HDD_SECTOR_SIZE;
    sect_start_addr = start_block;  //start_block*SATA_HDD_SECTOR_SIZE;
    u32 try_times = 10;
  exec:

    if (try_times == 0) {
        PRINT(0, "+SATAERR: !error@sata_dma_write_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);
        return (!ret);
    }

    PRINT(0, "+SATAINFO: sata_dma_write_sector blk %d,len %d\n", start_block, len);

    cmdhdr = (sata_command_header_t *) SATA_COMMAND_LIST_BASE;
    cmdtbl = (sata_command_table_t *) SATA_COMMAND_TABLE_BASE;

    ret = sata_reg_fis_h2d(port,
                           sect_start_addr,
                           sect_cnt,
                           SATA_WRITE, ATAPI_COMMAND_WRITE_DMA, 0, len, (u32) buf, cmdhdr, cmdtbl);

    if (ret == SATA_FAIL) {
        PRINT(0, "+SATAERR: !error@sata_pio_read_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);

        if (SATA_PASS == sata_non_queued_error_recovery(port)) {
            try_times--;
            goto exec;
        }
    }

    ret = sata_wait_command_done(port);

    if (ret == SATA_FAIL) {
        PRINT(0, "+SATAERR: !error@sata_dma_write_sector blk%d@0x%08x,len%d\n", start_block,
              (u32) buf, len);

        if (SATA_PASS == sata_non_queued_error_recovery(port)) {
            try_times--;
            goto exec;
        }
    }

    return (!ret);
}

sata_return_t sata_disk_read_sector(u32 start_block, u8 * buf, u32 len, u32 port)
{
    u32 i = 0;
    u32 cycle = 0;
    u32 sz = 0;
    u32 single_rd_sz = SATA_MAX_TRANSFER_DATA_SZ;
    u32 xfer_sz = 0;
    u32 blk;

    PRINT(0, "+SATAINFO: sata_disk_read_sector@blk %d, buf 0x%08x, sz %d\n", start_block, (u32) buf,
          len);
    cycle = len / single_rd_sz;

    if (len % single_rd_sz)
        cycle++;

    while (i < cycle) {
        blk = start_block + i * (single_rd_sz / SATA_HDD_SECTOR_SIZE);

        if (len > single_rd_sz)
            sz = single_rd_sz;
        else
            sz = len;

        PRINT(0, "+SATAINFO: sata_disk_read_sector cycle %d,blk %d,sz %d\n", i, blk, sz);
#ifdef SATA_PDMA_ENABLED

        if (!sata_dma_read_sector(blk, (buf + xfer_sz), sz, port))
#else
        if (!sata_pio_read_sector(blk, (buf + xfer_sz), sz, port))
#endif
        {
            PRINT(0, "+SATAERR: sata_disk_read_sector error@blk %d, buf 0x%08x, sz %d\n", blk,
                  (u32) ((u8 *) buf + i * single_rd_sz), sz);
            return SATA_FAIL;
        }

        i++;
        len -= sz;
        xfer_sz += sz;
    }

    return SATA_PASS;
}

sata_return_t sata_disk_write_sector(u32 start_block, u8 * buf, u32 len, u32 port)
{
    u32 i = 0;
    u32 cycle = 0;
    u32 sz = 0;
    u32 single_wr_sz = SATA_MAX_TRANSFER_DATA_SZ;   // total 32 sectors was transferred each time
    u32 blk;
    u32 xfer_sz = 0;
    cycle = len / single_wr_sz;

    cycle = len / single_wr_sz;

    if (len % single_wr_sz)
        cycle++;

    PRINT(0, "+SATAINFO: sata_disk_write_sector@blk %d, buf 0x%08x, sz %d\n", start_block,
          (u32) buf, len);

    while (i < cycle) {
        blk = start_block + i * (single_wr_sz / SATA_HDD_SECTOR_SIZE);

        if (len > single_wr_sz)
            sz = single_wr_sz;
        else
            sz = len;

        PRINT(0, "+SATAINFO: sata_disk_write_sector cycle%d,blk %d,sz %d\n", i, blk, sz);

#ifdef SATA_PDMA_ENABLED

        if (!sata_dma_write_sector(blk, (buf + xfer_sz), sz, port))
#else
        if (!sata_pio_write_sector(blk, (buf + xfer_sz), sz, port))
#endif
        {
            PRINT(0, "+SATAERR: sata_disk_write_sector error@%d\n", i);
            return SATA_FAIL;
        }

        i++;
        len -= sz;
        xfer_sz += sz;
    }

    return SATA_PASS;
}

void printf_buffer(u32 buff, u32 size, u32 enable)
{
    u32 i;
    unsigned char *ptr = (unsigned char *)buff;

    if (enable) {
        PRINT(0, "Data@BASE:0x%08x, LEN:%d bytes\n", buff, size);

        for (i = 0; i < size; i++) {
            PRINT(0, "%02X ", *(ptr + i));

            if (i % 16 == 15)
                PRINT(0, "\n");
        }

        PRINT(0, "\n");
    }
}

/*!
 * @brief Print the identify data
 *
 * @param ident_data Pointer to the identify data
 */
void print_identify_data(disk_identify_t * ident_data)
{
    PRINT(1, "HDD Identification Data:\n");
    PRINT(1, "\tSerial        : %s\n", (u8 *) ident_data->serial);
    PRINT(1, "\tFirmware rev. : %s\n", (u8 *) ident_data->firmware_rev);
    PRINT(1, "\tModel         : %s\n", (u8 *) ident_data->model_num);
    PRINT(1, "\tC/H/S         : %d/%d/%d\n", ident_data->cylinders_num, ident_data->heads_num,
          ident_data->sectors_num);
    PRINT(1, "\tSect Num      : %d\n", ident_data->lba_sectors_num);
    PRINT(1, "\tPhys Blk Sz   : %d\n", ident_data->phys_block_size);
    PRINT(1, "\tMax Trans Sz  : %d\n", ident_data->max_transfer * 512);
}

/*!
 * @brief Copy sata identify data
 *
 * @param dest Destination buffer address
 * @param src Source buffer address
 * @param size Data size
 */
static void _sata_identify_data_strcpy(char *dest, u16 * src, u16 size)
{
    u32 i;

    for (i = 0; i < size; i += 2) {
        *dest++ = (char)(*src >> 8);
        *dest++ = (char)(*src & 0x00FF);

        if (*src == 0x2020) {
            break;
        }

        src++;
    }

    *dest = '\0';
}

/*!
 * @brief Make sure SATA Port in IDLE state
 * Reading each implemented port's PxCMD register to ensure the controller
 * is not in the running state.
 * PxCMD.ST/CR/FRE/FR are all cleared -> idle state
 * If the port is not idle, it should be placed in the idle state prior to
 * manipulating HBA and port specific register
 * Method:
 *   1.clearing PxCMD.ST and waiting for PxCMD.CR to return '0' to place a port
 *    into idle. At least 500ms waiting is required.
 *   2.if PxCMD.FRE is set to '1', software should clear it to '0' and wait at
 *    least 500ms for PxCMD.FR returning '0'
 *   3.PxCMD.CR or PxCMD.FR don't clear to '0' correctly, then software may
 *    attempt a port reset or a full HBA reset to recover
 *
 * @param port_n_regs Base address of port regs
 * @return SATA_PASS or SATA_FAIL
 */
static sata_return_t sata_ahci_set_port_idle(u32 port)
{
    u32 v;
    sata_return_t ret = SATA_PASS;

    v = (HW_SATA_PORT(port).CMD).U;

    PRINT(0, "+SATAINFO: PxCMD@0x%08x = 0x%08x\n", (u32) (&(HW_SATA_PORT(port).CMD)), v);

    if (v & BM_SATA_P0CMD_HPCP) {
        PRINT(0, "+SATAINFO: Hot Plug Supported\n");
    }

    if ((!(v & BM_SATA_P0CMD_ST))
        && (!(v & BM_SATA_P0CMD_CR))
        && (!(v & BM_SATA_P0CMD_FRE))
        && (!(v & BM_SATA_P0CMD_FR))) {
        PRINT(0, "+SATADBGMSG: The port is in IDLE state.\n");
        return ret;
    }

    /*------Place the port into IDLE state------*/
    /*Clear CMD.ST and wait for CMD.CR to return '0' */
    (HW_SATA_PORT(port).CMD).B.ST = SATA_DISABLED;
    hal_delay_us(PORT_N_INIT_TIMEOUT);  //delay 500ms

    if ((HW_SATA_PORT(port).CMD).B.CR) {
        ret = SATA_FAIL;
        PRINT(0, "+SATADBGMSG:PxCMD.CR does not return to zero.\n");
        return ret;
    }

    if ((HW_SATA_PORT(port).CMD).B.FRE) {
    	(HW_SATA_PORT(port).CMD).B.FRE = SATA_DISABLED;
        hal_delay_us(PORT_N_INIT_TIMEOUT);  //delay 500ms

        if ((HW_SATA_PORT(port).CMD).B.FR) {
            ret = SATA_FAIL;
            PRINT(0, "+SATADBGMSG:PxCMD.FR does not return to zero.\n");
            return ret;
        }
    }

    PRINT(0, "+SATADBGMSG:place the port into IDLE state completed.\n");
    return ret;

}

/*!
 * @brief Reset sata AHCI port
 *
 * @param port_n_regs Base address of port regs
 * @return SATA_PASS or SATA_FAIL
 */
static sata_return_t sata_ahci_port_reset(u32 port)
{
    sata_return_t ret;
    (HW_SATA_PORT(port).CMD).B.ST = SATA_DISABLED;
    hal_delay_us(PORT_N_INIT_TIMEOUT);  //delay 500ms

    if ((HW_SATA_PORT(port).CMD).B.CR) {
        ret = SATA_FAIL;
        PRINT(0, "+SATADBGMSG:PxCMD.CR does not return to zero.\n");
        return ret;
    }

    (HW_SATA_PORT(port).CMD).B.ST = SATA_ENABLED;
    return SATA_PASS;
}

/*!
 * @brief Parsing the SATA host information by reading host regs
 *
 * @param ahci AHCI register handle
 */
static void sata_ahci_host_info_print(void)
{
    u32 vers, cap, speed, ip_vers;
    const char *speed_s;

    vers = HW_SATA_VS.U;
    ip_vers = HW_SATA_VERSIONR.U;
    cap = HW_SATA_CAP.U;

    speed = HW_SATA_CAP.B.ISS;

    if (speed == 1)
        speed_s = "1.5";
    else if (speed == 2)
        speed_s = "3.0";
    else if (speed == 3)
        speed_s = "6.0";
    else
        speed_s = "?";

    PRINT(1, "-------------------------------------\n");
    PRINT(1, "+SATAINFO:SATA AHCI Host Information:\n");
    PRINT(1, " AHCI Spec Ver: %x%x.%x%x\n"
          " SATA IP Ver  : %c.%c%c%c\n"
          " Command Slots: %u\n"
          " Impl. Ports  : %u\n"
          " Speed        : %sGbps\n",
          (vers >> 24) & 0xff,
          (vers >> 16) & 0xff,
          (vers >> 8) & 0xff,
          (vers) & 0xff,
          (ip_vers >> 24) & 0xff,
          (ip_vers >> 16) & 0xff,
          (ip_vers >> 8) & 0xff,
          (ip_vers) & 0xff, ((cap >> 8) & 0x1f) + 1, (cap & 0x1f) + 1, speed_s);

    PRINT(1, " Flags        : "
          "%s%s%s%s%s%s%s%s%s"
          "%s%s%s%s%s%s%s%s\n",
          cap & (1 << BP_SATA_CAP_S64A) ? "64bit" : "32bit",
          cap & (1 << BP_SATA_CAP_SNCQ) ? "|SNCQ" : "",
          cap & (1 << BP_SATA_CAP_SSNTF) ? "|SSNTF" : "",
          cap & (1 << BP_SATA_CAP_SMPS) ? "|SMPS" : "",
          cap & (1 << BP_SATA_CAP_SSS) ? "|SSS" : "",
          cap & (1 << BP_SATA_CAP_SALP) ? "|SALP" : "",
          cap & (1 << BP_SATA_CAP_SAL) ? "|SAL" : "",
          cap & (1 << BP_SATA_CAP_SCLO) ? "|SCLO" : "",
//          cap & (1 << 19) ? "|NZO" : "",
          cap & (1 << BP_SATA_CAP_SAM) ? "|SAM" : "",
          cap & (1 << BP_SATA_CAP_SMP) ? "|SMP" : "",
          cap & (1 << BP_SATA_CAP_PMD) ? "|PMD" : "",
          cap & (1 << BP_SATA_CAP_SSC) ? "|SSC" : "",
          cap & (1 << BP_SATA_CAP_PSC) ? "|PSC" : "",
          cap & (1 << BP_SATA_CAP_CCCS) ? "|CCCS" : "", 
          cap & (1 << BP_SATA_CAP_EMS) ? "|EMS" : "", 
          cap & (1 << BP_SATA_CAP_SXS) ? "|SXS" : "");
          
/*          cap & (1 << 31) ? "64bit" : "32bit",
          cap & (1 << 30) ? "|NCQ" : "",
          cap & (1 << 29) ? "|SNTF" : "",
          cap & (1 << 28) ? "|MPS" : "",
          cap & (1 << 27) ? "|STAG" : "",
          cap & (1 << 26) ? "|ALPM" : "",
          cap & (1 << 25) ? "|LED" : "",
          cap & (1 << 24) ? "|CLO" : "",
          cap & (1 << 19) ? "|NZO" : "",
          cap & (1 << 18) ? "|ONLY" : "",
          cap & (1 << 17) ? "|PMP" : "",
          cap & (1 << 15) ? "|PIO" : "",
          cap & (1 << 14) ? "|SLUM" : "",
          cap & (1 << 13) ? "|PART" : "",
          cap & (1 << 7) ? "|CCC" : "", cap & (1 << 6) ? "|EMS" : "", cap & (1 << 5) ? "|SXS" : "");
*/
    PRINT(1, "-------------------------------------\n");

}

/*!
 * @brief Enable the clocks of SATA, and configure the reference clock
 *
 * @param phyclk Phy clock
 */
//! todo Fix writing undocumented bits to HW_IOMUXC_SW_PAD_CTL_PAD_GPIO03_WR()
static void sata_clock_init(sata_phy_ref_clk_t * phyclk)
{
//     u32 v;
    sata_phy_ref_clk_t clk_val = *phyclk;

    /*Enable SATA module clock */
    sata_clock_enable();

    PRINT(0, "+SATADBGMSG: SATA relevant clocks gated on\n");

    if (clk_val == FREQ_100MHZ) {
        /*Set GPIO_3 as CLKO2 */
        HW_IOMUXC_SW_MUX_CTL_PAD_GPIO03_WR(
                BF_IOMUXC_SW_MUX_CTL_PAD_GPIO03_SION_V(DISABLED) |
                BF_IOMUXC_SW_MUX_CTL_PAD_GPIO03_MUX_MODE_V(ALT4));
        /* Configure CMD SW PAD */
        HW_IOMUXC_SW_PAD_CTL_PAD_GPIO03_WR(0x184);

        /*Set CLKO2 to ddr_clk_root,300MHz */
//         writel(~(0x1F << 16), CCM_CCOSR);
//         writel((0x9 << 16), CCM_CCOSR); //DDR
        HW_CCM_CCOSR.B.CLKO2_SEL = 9; // 125M_clk_root

        /*Set CLKO2 Divider as 3 to get 100MHz */
        HW_CCM_CCOSR.B.CLKO2_DIV = 2; // div 3

        /*Enable CLKO2 */
        HW_CCM_CCOSR.B.CLKO2_EN = 1;

        PRINT(0, "+SATADBGMSG: SATA PHY Clock 100MHz Div of CLKO2\n");
        PRINT(0, "+SATADBGMSG: CCOSR = 0x%08x\n", HW_CCM_CCOSR_RD());

        sata_phy_config_mpll(7, 0, 2, 6, 2);
        PRINT(1, "+SATADBGMSG: SATA PHY Clock 100MHz divided DDR clock\n");
    } else if (clk_val == OSC_25MHZ) {
        sata_phy_config_mpll(7, 0, 2, 6, 1);
        PRINT(1, "+SATADBGMSG: SATA PHY Clock 25MHz Osc\n");
    } else if (clk_val == OSC_50MHZ) {
        sata_phy_config_mpll(7, 0, 2, 6, 0);
        PRINT(1, "+SATADBGMSG: SATA PHY Clock 50MHz Osc\n");
    } else if (clk_val == OSC_25MHZ) {
        sata_phy_config_mpll(7, 0, 2, 6, 1);
        PRINT(1, "+SATADBGMSG: SATA PHY Clock 25MHz Osc\n");
    } else if (clk_val == FUSE_USB_PHY_CLK) {
        PRINT(1, "+SATADBGMSG: SATA PHY Clock <= USB PHY1\n");
    } else if (clk_val == CCM_PLL_ENET) {
        PRINT(1, "+SATADBGMSG: SATA PHY Clock <= ANATOP ENET PLL\n");
    }

}

/*!
 * @brief Initialize sata HDD
 */
static sata_return_t sata_hdd_init(u32 port)
{
    sata_return_t ret = SATA_FAIL;
    unsigned char *ident_data;  //[SATA_HDD_SECTOR_SIZE];
    u32 i;
    char crc = 0;
    sata_identify_data_t *ide_idData = &hdd_ident;

    u32 total_lba_sect = 0;

    ident_data = (unsigned char *)SATA_TRANSFER_BUFFER_BASE;    //located in OCRAM
    memset(ident_data, 0, SATA_HDD_SECTOR_SIZE);
    PRINT(0, "+SATAINFO: identify data buffer base: 0x%08x\n", (u32) ident_data);
    cmdhdr = (sata_command_header_t *) SATA_COMMAND_LIST_BASE;
    cmdtbl = (sata_command_table_t *) SATA_COMMAND_TABLE_BASE;

    ret = sata_reg_fis_h2d(port,
                           0,
                           1,
                           SATA_READ,
                           ATAPI_COMMAND_IDENTIFY_DEVICE,
                           0, SATA_HDD_SECTOR_SIZE, (u32) ident_data, cmdhdr, cmdtbl);

    if (ret == SATA_FAIL) {
        return (!ret);
    }

    hal_delay_us(5000);         //5ms

    ret = sata_wait_command_done(port);

    printf_buffer((u32) ident_data, SATA_HDD_SECTOR_SIZE, 0);

    /*Check the data integrity of identify data */
    for (i = 0; i < SATA_HDD_SECTOR_SIZE; i++) {
        crc += *(ident_data + i);
    }

    /*check CRC: CIS[255] should be XXA5 where XX=-1*CRC thus total CRC including XX should be 0 */
    if ((*(ident_data + SATA_HDD_SECTOR_SIZE - 2) != 0xA5) || (crc != 0)) {
        PRINT(0, "+SATAERR: idetify CRC Error %xa5 != %.2x%.2x\n", (-1 * crc) & 0xff,
              ident_data[SATA_HDD_SECTOR_SIZE - 2], ident_data[SATA_HDD_SECTOR_SIZE - 1]);
        return SATA_FAIL;
    }

    /*initialize hdd identify data */
    memcpy((char *)ide_idData, ident_data, SATA_HDD_SECTOR_SIZE);

    _sata_identify_data_strcpy(ident.serial, ide_idData->serial, 20);
    _sata_identify_data_strcpy(ident.firmware_rev, ide_idData->fw_rev, 8);
    _sata_identify_data_strcpy(ident.model_num, ide_idData->model_num, 40);

    total_lba_sect = (ide_idData->lba_total_sectors[1] << 16) | ide_idData->lba_total_sectors[0];

    ident.cylinders_num = ide_idData->num_cylinders;
    ident.heads_num = ide_idData->num_heads;
    ident.sectors_num = ide_idData->num_sectors;
    ident.lba_sectors_num = total_lba_sect;
    ident.phys_block_size = ide_idData->sector_size;
    ident.max_transfer = (ide_idData->rw_mult_support & 0xFF);

    //PRINT(0,"+SATAINFO: words per logic sector: %d\n",(ide_idData->sector_sz_in_word));
    print_identify_data(&ident);

    return ret;

}

/*!
 * @brief Parsing the status of SATA
 */
static void sata_port_status_parser(u32 status)
{

//    if (status & SATA_AHCI_PORT_N_IS_CPDS) {
//        PRINT(0, "+SATAINFO: CPDS - Cold Port Detect.\n");
//    }

    if (status & BM_SATA_P0IS_TFES) {
        PRINT(0, "+SATAINFO: TFES - Task File Error.\n");
    }

    if (status & BM_SATA_P0IS_HBFS) {
        PRINT(0, "+SATAINFO: HBFS - Host Bus Fatal Error.\n");
    }

    if (status & BM_SATA_P0IS_HBDS) {
        PRINT(0, "+SATAINFO: HBDS - Host Bus Data Error.\n");
    }

    if (status & BM_SATA_P0IS_IFS) {
        PRINT(0, "+SATAINFO: IFS  - Interface Fatal Error.\n");
    }

    if (status & BM_SATA_P0IS_INFS) {
        PRINT(0, "+SATAINFO: INFS - Interface Non-Fatal Error.\n");
    }

    if (status & BM_SATA_P0IS_OFS) {
        PRINT(0, "+SATAINFO: OFS  - OverFlow Error.\n");
    }

    if (status & BM_SATA_P0IS_IPMS) {
        PRINT(0, "+SATAINFO: IPMS - Incorrect Port Multiplier Error.\n");
    }

    if (status & BM_SATA_P0IS_PRCS) {
        PRINT(0, "+SATAINFO: PRCS - PHY Ready Change.\n");
    }

//    if (status & SATA_AHCI_PORT_N_IS_DMPS) {
//        PRINT(0, "+SATAINFO: DMPS - Device Mechanical Presence.\n");
//    }

    if (status & BM_SATA_P0IS_PCS) {
        PRINT(0, "+SATAINFO: PCS  - Port Change.\n");
    }

    if (status & BM_SATA_P0IS_DPS) {
        PRINT(0, "+SATAINFO: DPS  - Descriptor Processed.\n");
    }

    if (status & BM_SATA_P0IS_UFS) {
        PRINT(0, "+SATAINFO: UFS  - Unknown FIS.\n");
    }

    if (status & BM_SATA_P0IS_SDBS) {
        PRINT(0, "+SATAINFO: SDBS - Set Device Bits FIS.\n");
    }

    if (status & BM_SATA_P0IS_DSS) {
        PRINT(0, "+SATAINFO: DSS  - DMA Setup FIS.\n");
    }

    if (status & BM_SATA_P0IS_PSS) {
        PRINT(0, "+SATAINFO: PSS  - PIO Setup FIS.\n");
    }

    if (status & BM_SATA_P0IS_DHRS) {
        PRINT(0, "+SATAINFO: DHRS - Device to Host Register FIS.\n");
    }
}

/*!
 * @brief Find an empty command slot
 *
 * @param port Sata port handle
 * @return SATA_PASS or SATA_FAIL
 */
static sata_return_t ahci_find_empty_slot(u32 port)
{
    u32 idx;
    u32 empty_cmd_slot = 32;
    u32 v;

    // Get an empty command slot
    v = (HW_SATA_PORT(port).CI).U;
    idx = 0;

    while ((((v >> idx) & 0x1) != 0) && (idx < 32)) {
        idx = idx + 1;
    }

    empty_cmd_slot = idx;

    if (empty_cmd_slot > 31) {
        PRINT(0, "SATAERR: Can not find emmpty slot(%d)\n", empty_cmd_slot);
        return -1;
    }

    PRINT(0, "+SATADBGMSG:command slot %d is empty\n", empty_cmd_slot);
    PRINT(0, "+SATADBGMSG:command slot %d is empty\n", empty_cmd_slot);
    
    return empty_cmd_slot;
}

/*!
 * @brief Wait for the sata command execution done
 *
 * @param port Sata port number
 * @return SATA_PASS or SATA_FAIL
 */
static sata_return_t sata_wait_command_done(u32 port)
{
    u32 i;
    sata_return_t ret = SATA_FAIL;
    u32 stat = 0;
    u32 err = 0;
//     u32 port_stat = 0;
    /* wait while device busy */
    i = MAX_TIMEOUT_COUNTER;

    while (((HW_SATA_IS.U & SATA_AHCI_HOST_IS_PORT_N_INTR_ISSUED(port)) != (0x1 << port))
           && (--i > 0)) ;

    if (i == 0) {
        PRINT(0, "+SATAERR: wait interrupt timeout\n");
        stat = (HW_SATA_PORT(port).IS).U; 
        err = (HW_SATA_PORT(port).SERR).U;
        (HW_SATA_PORT(port).SERR).U = err;
        (HW_SATA_PORT(port).IS).U = stat;  //clear port interrupt status
        HW_SATA_IS.U |= SATA_AHCI_HOST_IS_PORT_N_INTR_ISSUED(port);
    } else {
        /* Clear interrupt */
        //PRINT(0,"+SATAINFO: Port.IS = 0x%08x\n",imx_sata_host->is);
        stat = (HW_SATA_PORT(port).IS).U;
        err = (HW_SATA_PORT(port).SERR).U;
//         port_stat = imx_sata_port0->ssts;

        if (stat & 0xff000000) {
            //PRINT(0,"+SATAERR: Port0.IS   : 0x%08x\n",stat);
            //sata_port_status_parser(stat);
            //PRINT(0,"+SATAERR: Err Code   : 0x%08x\n",err);
            //PRINT(0,"+SATAERR: Port Status: 0x%08x\n",port_stat);
            ret = SATA_FAIL;
        } else {
            ret = SATA_PASS;
        }

        PRINT(0, "+SATAINFO: TFD is 0x%08x\n", (HW_SATA_PORT(port).TFD).U);

        (HW_SATA_PORT(port).SERR).U = err;
        (HW_SATA_PORT(port).IS).U = stat;  //clear port interrupt status
        HW_SATA_IS.U  |= SATA_AHCI_HOST_IS_PORT_N_INTR_ISSUED(port); //clear host global interrupt status
    }

    return ret;
}

/*!
 * @brief send a RFIS to SATA device
 *
 * @param port Base address of the SATA port to run the command
 * @param sect_addr Start address of the first sector
 * @param sect_cnt Sector number to read or write
 * @param rw Data transfer direction: read or write
 * @param command ATAPI command code
 * @param features Content in feature register of the shadow register block
 * @param size Data transfer size in byte
 * @param data_addr Base address of data buffer
 * @param cmdh Pointer of command header
 * @param cmdt Pointer of command table
 * @return SATA_PASS or SATA_FAIL
 */
static sata_return_t sata_reg_fis_h2d(u32 port,  
                                      u32 sect_addr, 
                                      u32 sect_cnt, 
                                      u32 rw, 
                                      u32 command,  
                                      char features,    
                                      u32 size,
                                      u32 data_addr,
                                      sata_command_header_t * cmdh,
                                      sata_command_table_t * cmdt)
{
    s32 ept_cmd_slot = -1;
    sata_command_header_t *cmd_hdr;

    /*get empty command slot */
    ept_cmd_slot = ahci_find_empty_slot(port);
    PRINT(0, "+SATAERR: find empty command slot %d\n", ept_cmd_slot);

    if (ept_cmd_slot == -1) {
        return SATA_FAIL;
    }

    /*fill command header */
    cmd_hdr = (sata_command_header_t *) ((u32) cmdh + ept_cmd_slot * sizeof(sata_command_header_t));
    memset((void *)cmd_hdr, 0x0, sizeof(sata_command_header_t));    //clear the command header to zero

    PRINT(0, "+SATAINFO: command header base 0x%8x\n", (u32) cmd_hdr);

    cmd_hdr->info.field.cfl = 5;    //length of Command FIS, for register FIS, it's 5 in maximum

    if (rw == SATA_WRITE)
        cmd_hdr->info.field.write = 1;
    else
        cmd_hdr->info.field.write = 0;  //read operation

    cmd_hdr->info.field.prdtl = 1;  //one PRDT
    cmd_hdr->ctba = (u32) cmdt;

    //printf_buffer((u32)cmd_hdr,sizeof(sata_command_header_t),0);
    PRINT(0, "+SATAINFO: command table base 0x%8x\n", (u32) cmdt);
    /*fill command table */

    memset((void *)cmdt, 0x0, sizeof(sata_command_table_t));

    cmdt->cfis.fisType = SATA_FIS_TYPE_RFIS_H2D;
    cmdt->cfis.pmPort_Cbit = 0x80;
    cmdt->cfis.command = command;
    cmdt->cfis.features = features;
    cmdt->cfis.lbaLow = (sect_addr & 0xFF);
    cmdt->cfis.lbaMid = ((sect_addr >> 8) & 0xFF);
    cmdt->cfis.lbaHigh = ((sect_addr >> 16) & 0xFF);
    cmdt->cfis.device = 0x40;
    cmdt->cfis.sectorNum = sect_cnt;

    cmdt->prdt.dba = data_addr;
    cmdt->prdt.dbc_ioc = ((size) - 1) | (IOC << 31);

    //printf_buffer((u32)cmdt,sizeof(sata_command_table_t),0);

    /*execute the command */
    (HW_SATA_PORT(port).CI).U |= (1 << ept_cmd_slot);

    return SATA_PASS;
}

/*!
 * @brief Sata attempts to recover from an error
 *
 * @return SATA_PASS or SATA_FAIL
 */
static sata_return_t sata_non_queued_error_recovery(u32 port)
{
    sata_return_t ret;
    u32 v;
    u32 errslot;
    u32 cnt;
    /*a - read PxCI to see which commands are still outstanding */
    v = (HW_SATA_PORT(port).CI).U; 
    PRINT(1, "+SATAINFO: outstanding command slots 0x%08x\n", v);
    //b - read PxCMD.CCS to determine the slot that the HBA was processing when
    //the error occured
    errslot = (HW_SATA_PORT(port).CMD).B.CCS;
    PRINT(1, "+SATAINFO: error occurs to command slot %d\n", errslot);
    //c - clear PxCMD.ST to 0 to reset the PxCI register, waits for PxCMD.CR to clear
    //to '0'
    (HW_SATA_PORT(port).CMD).B.ST = SATA_DISABLED;
    hal_delay_us(PORT_N_INIT_TIMEOUT);  //delay 500ms

    if ((HW_SATA_PORT(port).CMD).B.CR) {
        ret = SATA_FAIL;
        PRINT(1, "+SATADBGMSG:PxCMD.CR does not return to zero.\n");
        return ret;
    }
    //d - clear any error bits in PxSERR to enable capturing new errors
    v = (HW_SATA_PORT(port).SERR).U;
    (HW_SATA_PORT(port).SERR).U = v;
    //e - clear status bits in PxIS as appropriate
    v = (HW_SATA_PORT(port).IS).U;
    (HW_SATA_PORT(port).IS).U = v;

    v = HW_SATA_IS.U;
    HW_SATA_IS.U = v;

    //f - if PxTFD.STS.BSY or PxTFD.STS.DRQ is set to '1', issue a COMRESET to the device
    //to put it in an idle state
    if ((HW_SATA_PORT(port).TFD).U & SATA_AHCI_PORT_N_TFD_MASK) {
        if ((HW_SATA_PORT(port).CMD).B.SUD) {
            (HW_SATA_PORT(port).CMD).B.SUD = SATA_DISABLED;
        }

        hal_delay_us(10);       //delay 1ms
        (HW_SATA_PORT(port).CMD).B.SUD = SATA_ENABLED;

        /*Start detect the attached device */
        //imx_sata_port0->sctl |= (SCTL_DET_COMM_INIT);//|SCTL_SPD_GEN2_NEGOCIATE);

        hal_delay_us(1500);     //delay at least 1ms after communication init
        /*wait spin-up finished */
        cnt = MAX_TIMEOUT_COUNTER;

        while (--cnt) {
            if (!((HW_SATA_PORT(port).TFD).U & SATA_AHCI_PORT_N_TFD_MASK)) {
                PRINT(1, "+SATADBGMSG: device ready now\n");
                PRINT(1, "+SATAERR : tfd 0x%08x\n", (HW_SATA_PORT(port).TFD).U);
                break;
            }

        }

        if (!cnt) {
            PRINT(1, "+SATAERR : Timeout to get device ready\n");
            return SATA_FAIL;
        }
    }
    //g - sets PxCMD.ST to '1' to enable issuing new commands
    (HW_SATA_PORT(port).CMD).B.ST = SATA_ENABLED;

    return SATA_PASS;
}

/*!
 * @brief Check the PHY control register acknowledge
 *
 * @param max_iterations Maximum iteration number
 * @param expected_val Expected value
 * @return SATA_PASS or SATA_FAIL
 */
static sata_return_t sata_phy_cr_ack_polling(u32 max_iterations, u32 expected_val, u32 port)
{
    u32 v, ack;
    u32 wait_counter;

    ack = !expected_val;
    wait_counter = 0;

    while ((wait_counter < max_iterations) && (ack != expected_val)) {
        v = (HW_SATA_PORT(port).PHYSR).U;
        ack = (HW_SATA_PORT(port).PHYSR).B.CR_ACK; 
        wait_counter++;
    }

    if (wait_counter == max_iterations)
        return SATA_FAIL;
    else
        return SATA_PASS;
}

/*!
 * @brief Write the PHY control register
 *
 * @param addr register address
 * @param val value
 * @return SATA_PASS or SATA_FAIL
 */
static sata_return_t sata_phy_cr_write(u32 addr, u32 val, u32 port)
{
    u32 v;
    // write addr
    v = addr << BP_SATA_P0PHYCR_CR_DATA_IN;
    (HW_SATA_PORT(port).PHYCR).U = v;

    // capture addr
    v |= (0x1 << BP_SATA_P0PHYCR_CR_CAP_ADDR);
    (HW_SATA_PORT(port).PHYCR).U = v;

    // wait for ack
    if (sata_phy_cr_ack_polling(100, 1, port)) {
        PRINT(0, "SATAERR: PHY Not responding cap addr assertion\n");
        return SATA_FAIL;
    }
    // deassert cap data
    v &= 0xffff << BP_SATA_P0PHYCR_CR_DATA_IN;
    (HW_SATA_PORT(port).PHYCR).U = v;

    // wait for ack de-assetion
    if (sata_phy_cr_ack_polling(100, 0, port)) {
        PRINT(0, "SATAERR: PHY Not responding cap addr de-assetion\n");
        return SATA_FAIL;
    }
    // write data
    v = val << BP_SATA_P0PHYCR_CR_DATA_IN;
    (HW_SATA_PORT(port).PHYCR).U = v;

    // capture data
    v |= (0x1 << BP_SATA_P0PHYCR_CR_CAP_DATA);
    (HW_SATA_PORT(port).PHYCR).U = v;

    // wait for ack
    if (sata_phy_cr_ack_polling(100, 1, port)) {
        PRINT(0, "SATAERR: PHY Not responding cap dat assertion\n");
        return SATA_FAIL;
    }
    // deassert cap data
    v &= 0xffff << BP_SATA_P0PHYCR_CR_DATA_IN;
    (HW_SATA_PORT(port).PHYCR).U = v;

    // wait for ack de-assetion
    if (sata_phy_cr_ack_polling(100, 0, port)) {
        PRINT(0, "SATAERR: PHY Not responding cap data de-assetion\n");
        return SATA_FAIL;
    }
    // assert wr signal
    v = 0x1 << BP_SATA_P0PHYCR_CR_WRITE;
    (HW_SATA_PORT(port).PHYCR).U = v;

    // wait for ack
    if (sata_phy_cr_ack_polling(100, 1, port)) {
        PRINT(0, "SATAERR: PHY Not responding write\n");
        return SATA_FAIL;
    }
    // deassert rd _signal
    v = 0x0;
    (HW_SATA_PORT(port).PHYCR).U = v;

    // wait for ack de-assetion
    if (sata_phy_cr_ack_polling(100, 0, port)) {
        PRINT(0, "SATAERR: PHY Not responding write de-assetion\n");
        return SATA_FAIL;
    }

    return SATA_PASS;
}


/*!
 * @brief Read the PHY control register
 *
 * @param addr register address
 * @param data value read
 * @return SATA_PASS or SATA_FAIL
 */
static sata_return_t sata_phy_cr_read(u32 addr, u32 * data, u32 port)
{
    u32 temp_rd_data;
    u32 temp_wr_data;
    // write addr
    temp_wr_data = addr << BP_SATA_P0PHYCR_CR_DATA_IN;
    (HW_SATA_PORT(port).PHYCR).U = temp_wr_data;

    // capture addr
    temp_wr_data |= (0x1 << BP_SATA_P0PHYCR_CR_CAP_ADDR);
    (HW_SATA_PORT(port).PHYCR).U = temp_wr_data;

    // wait for ack
    if (sata_phy_cr_ack_polling(100, 1, port)) {
        PRINT(0, "SATAERR: PHY Not responding cap addr assertion\n");
        return SATA_FAIL;
    }
    // deassert cap addr
    temp_wr_data &= 0xffff << BP_SATA_P0PHYCR_CR_DATA_IN;
    (HW_SATA_PORT(port).PHYCR).U = temp_wr_data;

    // wait for ack de-assetion
    if (sata_phy_cr_ack_polling(100, 0, port)) {
        PRINT(0, "SATAERR: PHY Not responding cap addr de-assetion\n");
        return SATA_FAIL;
    }
    // assert rd signal
    temp_wr_data = 0x1 << BP_SATA_P0PHYCR_CR_READ;
    (HW_SATA_PORT(port).PHYCR).U = temp_wr_data;

    // wait for ack
    if (sata_phy_cr_ack_polling(100, 1, port)) {
        PRINT(0, "SATAERR: PHY Not responding read\n");
        return SATA_FAIL;
    }
    // after got ack return data
    temp_rd_data = (HW_SATA_PORT(port).PHYSR).U;
    *data = (temp_rd_data & (0xffff << BP_SATA_P0PHYSR_CR_DATA_OUT));
    // deassert rd _signal
    temp_wr_data = 0x0;
    (HW_SATA_PORT(port).PHYCR).U = temp_wr_data;

    // wait for ack de-assetion
    if (sata_phy_cr_ack_polling(100, 0, port)) {
        PRINT(0, "SATAERR: PHY Not responding read de-assetion\n");
        return SATA_FAIL;
    }

    return 0;
}

/*!
 * @brief Set the PHY capture address
 *
 * @param addr capture address
 * @return SATA_PASS or SATA_FAIL
 */
static sata_return_t sata_phy_cr_addr(u32 addr, u32 port)
{
    u32 temp_wr_data;
    // write addr
    temp_wr_data = addr << BP_SATA_P0PHYCR_CR_DATA_IN;
    (HW_SATA_PORT(port).PHYCR).U = temp_wr_data;

    // capture addr
    temp_wr_data |= (0x1 << BP_SATA_P0PHYCR_CR_CAP_ADDR);
    (HW_SATA_PORT(port).PHYCR).U = temp_wr_data;

    // wait for ack
    if (sata_phy_cr_ack_polling(100, 1, port)) {
        PRINT(0, "SATAERR: PHY Not responding cap addr assertion\n");
        return SATA_FAIL;
    }
    // deassert cap addr
    temp_wr_data &= 0xffff << BP_SATA_P0PHYCR_CR_DATA_IN;
    (HW_SATA_PORT(port).PHYCR).U = temp_wr_data;

    // wait for ack de-assetion
    if (sata_phy_cr_ack_polling(100, 0, port)) {
        PRINT(0, "SATAERR: PHY Not responding cap addr de-assetion\n");
        return SATA_FAIL;
    }

    return SATA_PASS;
}

/*!
 * @brief Configure the PHY mpll for clock generation
 *
 * @param prop_ctl Proportional charge pump control
 * @param int_ctl Integral charge pump control
 * @param ncy5 Divide-by-5 control
 * @param ncy Divide-by-4 cycle control
 * @param prescale Prescaler control
 */
static void sata_phy_config_mpll(char prop_ctl, char int_ctl, char ncy5, char ncy, char prescale)
{
    u32 freq_ovrd;

    freq_ovrd = prop_ctl | (int_ctl << 3) | (ncy5 << 6) | (ncy << 8) | (prescale << 13) | (1 << 15);
    //PRINT(0,"+SATAPHY: Phy Freq Ovrd: 0x%04x\n",freq_ovrd);
    //check rd-wr to reg
    sata_phy_cr_write(SATA_PHY_CR_CLOCK_FREQ_OVRD, freq_ovrd, PORT0);

    hal_delay_us(10);
}

sata_return_t sata_init(void)
{
    sata_return_t ret = SATA_PASS;
    u32 i = 0;
    u32 cnt;
    u32 ports;
    u32 cmd_slots;
    u32 v;

    sata_power_on();
    sata_get_phy_src_clk(&sata_phy_clk_sel);

    if (sata_phy_clk_sel == OSC_UNKNOWN) {
        sata_phy_clk_sel = OSC_50MHZ;
        PRINT(0, "+SATADBGMSG: Ref Clk %d\n", sata_phy_clk_sel);
    }
    /*SATA clock initialization. */
    sata_clock_init(&sata_phy_clk_sel);

    /*Reset HBA */
    //ahci->ghc = SATA_AHCI_HOST_GHC_HBA_RESET;
    //ahci->ghc = SATA_AHCI_HOST_GHC_AHCI_ENABLED;
    //while(ahci->ghc&SATA_AHCI_HOST_GHC_HBA_RESET);

    /*!!Rita specific configuration!! */
    /*Set 1ms timer count value */
    HW_SATA_TIMER1MS.U = SATA_AHCI_HOST_TIMER1MS_MASK;
    PRINT(0, "+SATADBGMSG: Timer1ms@0x%08x = 0x%08x\n", (u32) (HW_SATA_TIMER1MS_ADDR), HW_SATA_TIMER1MS.U);

    /*Set OOBR register */
    HW_SATA_OOBR.B.WE = SATA_ENABLED;

    HW_SATA_OOBR.U = (SATA_AHCI_HOST_OOBR_COMWAKE_MIN_VAL
                  | SATA_AHCI_HOST_OOBR_COMWAKE_MAX_VAL
                  | SATA_AHCI_HOST_OOBR_COMINIT_MIN_VAL | SATA_AHCI_HOST_OOBR_COMINIT_MAX_VAL);
    /*!!Rita specific configuration end!! */

    /*firmware initialize */
    /*Support Staggered Spin-Up */
    HW_SATA_CAP.B.SSS = SATA_ENABLED;

    /*Reading PI register to determine which ports are implemented by HBA */
    ports = HW_SATA_CAP.B.NP;
    ports += 1;

    for (i = 0; i < ports; i++) {
        HW_SATA_PI.U |= (1 << i);
    }

    /*Clear HBA interrupt status */
    //ahci->is = 0xFF;

    for (i = 0; i < ports; i++) {
        PRINT(0, "+SATADBGMSG: Port %d Implemented\n", i);
 
        /*Place the port into IDLE state */
        ret = sata_ahci_set_port_idle(i);

        if (ret) {
            PRINT(0, "+SATADBGMSG: Error - Port reset or HBA reset is required\n");
            return SATA_FAIL;
        }

        /*Spin-up the port */
        (HW_SATA_PORT(i).CMD).B.SUD = SATA_ENABLED;

        /*Start detect the attached device */
        (HW_SATA_PORT(i).SCTL).U |= (SCTL_DET_COMM_INIT | SCTL_IPM_TRANS_TO_BOTH_PM_DIS);

        hal_delay_us(1500);     //delay at least 1ms after communication init
        /*wait spin-up finished */
        cnt = MAX_TIMEOUT_COUNTER;

        while (cnt) {
            if ((HW_SATA_PORT(i).CMD).B.SUD) {
                PRINT(0, "+SATADBGMSG: Spin-Up Device completed\n");
                break;
            }

            cnt--;
        }

        if (!cnt) {
            PRINT(1, "+SATAERR : Timeout to Spin-Up Device\n");
            return SATA_FAIL;
        }

        (HW_SATA_PORT(i).SCTL).B.DET = SATA_DISABLED;
        /*Allocate memory for each implemented port, and program PxCLB/CLBU/FB/FBU.
           It's better to clear the memory regions.
           After setting PxFB/FBU,software should set PxCMD.FRE to '1'
         */
        PRINT(0, "+SATADBGMSG: Allocate the memory for port %d\n", i);

        /*i.MX53 only supports Port 0 */
        //PRINT(0,"+SATADBGMSG: set CLB and FB base addr of port %d\n",i);
        //PRINT(0,"+SATADBGMSG: allocated clb addr 0x%08x\n",SATA_COMMAND_LIST_BASE);
        //PRINT(0,"+SATADBGMSG: allocated fb addr 0x%08x\n",SATA_FIS_BASE);
        memset((char *)(SATA_COMMAND_LIST_BASE + i * sizeof(sata_command_header_t) * 32), 0,
               sizeof(sata_command_header_t) * 32);
        (HW_SATA_PORT(i).CLB).U = (SATA_COMMAND_LIST_BASE + i * sizeof(sata_command_header_t) * 32);       
        memset((char *)(SATA_RECEIVED_FIS_BASE + i * sizeof(sata_rx_fis_t)), 0,
               sizeof(sata_rx_fis_t));        
         (HW_SATA_PORT(i).FB).U = SATA_RECEIVED_FIS_BASE;

        /*Set the AHB burst size and transaction size
           port_n_regs->dmacr = (DMACR_AHB_BURST_SIZE_8_DWORDS<<SATA_AHCI_PORT_N_DMACR_RXABL_SHIFT)
           |(DMACR_AHB_BURST_SIZE_8_DWORDS<<SATA_AHCI_PORT_N_DMACR_TXABL_SHIFT)
           |(DMACR_TRANSAC_SIZE_16_DWORDS<<SATA_AHCI_PORT_N_DMACR_RXTS_SHIFT)
           |(DMACR_TRANSAC_SIZE_16_DWORDS<<SATA_AHCI_PORT_N_DMACR_TXTS_SHIFT);
         */
        PRINT(0, "+SATADBGMSG: PxDMACR@0x%08x = 0x%08x\n", (u32) (&(HW_SATA_PORT(i).DMACR)),
              (u32) ((HW_SATA_PORT(i).DMACR).U));
        (HW_SATA_PORT(i).CMD).B.FRE = SATA_ENABLED;
        //PRINT(0,"+SATADBGMSG: clb addr 0x%08x\n",port_n_regs->clb);
        //PRINT(0,"+SATADBGMSG: fb addr 0x%08x\n",port_n_regs->fb);

        cnt = MAX_TIMEOUT_COUNTER;

        while (cnt) {
            if (((HW_SATA_PORT(i).SSTS).B.DET == SSTS_DET_DEV_DET_NO_PHY)
                || (((HW_SATA_PORT(i).SSTS).B.DET) == SSTS_DET_DEV_DET_PHY_RDY)) {
                PRINT(1, "+SATADBGMSG: SATA Device Detected\n");
                break;
            }

            cnt--;
        }

        if (!cnt) {
            PRINT(1, "+SATAERR : Timeout to detect SATA device\n");
            return SATA_FAIL;
        }

        /*Check DIAG_X */
        cnt = MAX_TIMEOUT_COUNTER;

        while (cnt) {
            if ((HW_SATA_PORT(i).SERR).B.DIAG_X) {
                PRINT(0, "+SATADBGMSG: P0SERR:0x%08x\n", (HW_SATA_PORT(i).SERR).U);
                PRINT(0, "+SATADBGMSG: DIAG_X\n");
                break;
            }

            cnt--;
        }

        if (!cnt) {
            PRINT(1, "+SATAERR : Timeout to check DIAG_X\n");
            return SATA_FAIL;
        }

        v = (HW_SATA_PORT(i).SERR).U;
        (HW_SATA_PORT(i).SERR).U = v;

        /*Check Task-File-Data */
        cnt = MAX_TIMEOUT_COUNTER;

        while (cnt) {
            if (((HW_SATA_PORT(i).TFD).U & SATA_AHCI_PORT_N_TFD_MASK) == 0) {
                PRINT(0, "+SATADBGMSG: Device ready\n");
                break;
            }

            cnt--;
        }

        if (!cnt) {
            PRINT(1, "+SATAERR : Timeout to check TFD\n");
            return SATA_FAIL;
        }

        /*Determine which events should cause an interrupt, and set each implemented port's
           PxIE register.
           Bit 0, DHRE, Device to Host Register FIS Interrupt
           Bit 1, PSE,  PIO Setup FIS Interrupt
           Bit 2, DSE,  DMA Setup FIS Interrupt
           Bit 3, SDBE, Set Device Bits FIS Interrupt
           Bit 4, UFE,  Unknown FIS Interrupt
           Bit 6, PCE,  Port Change Interrupt
           Bit 24,OFE,  Overflow Interrupt
           Bit 32,CPDE, Cold Port Detect Interrupt
         */
        PRINT(0, "+SATADBGMSG: Enable the interrupts of port %d\n", i);
        (HW_SATA_PORT(i).IS).U = 0xFFFFFFFF;   //clear all the old interrupt status;
        /*Clear PxSERR register of each implemented port by writing '1' to each implemented
           bit loation */
        PRINT(0, "+SATADBGMSG: Clear SERR register of port %d\n", i);
        (HW_SATA_PORT(i).SERR).U = 0xFFFFFFFF;

        (HW_SATA_PORT(i).IE).U = SATA_AHCI_PORT_N_INTR_ENANBLE_MASK;
        PRINT(0, "+SATADBGMSG: Port %d.IE = 0x%08x\n", i, (HW_SATA_PORT(i).IE).U);
    }

    /*Reading CAP.NCS to determine the command slots the HBA supports */
    cmd_slots = HW_SATA_CAP.B.NCS;

    /*Enable SATA interrupt */
    HW_SATA_GHC.B.IE = SATA_ENABLED;

    /*Start the ports */
    for (i = 0; i < ports; i++) {
        (HW_SATA_PORT(i).CMD).B.ST = SATA_ENABLED;
    }

    sata_ahci_host_info_print();

    return ret;
}

sata_return_t sata_deinit(void)
{
    sata_return_t ret = SATA_PASS;
    u32 i = 0;
    u32 ports;

    PRINT(0, "sata_deinit\n");

    /*Reading PI register to determine which ports are implemented by HBA */
    ports = HW_SATA_CAP.B.NP; 
    ports += 1;

    for (i = 0; i < ports; i++) {
        HW_SATA_PI.U |= (1 << i);
    }

    /*Clear HBA interrupt status */
    //ahci->is = 0xFF;

    for (i = 0; i < ports; i++) {
        PRINT(0, "+SATADBGMSG: Port %d Implemented\n", i);
 
        /*power off the port */
        (HW_SATA_PORT(i).CMD).B.SUD = SATA_DISABLED;
        (HW_SATA_PORT(i).CMD).B.POD = SATA_DISABLED; 

        /*Place the port into IDLE state */
        ret = sata_ahci_port_reset(i);

        if (ret == SATA_FAIL) {
            PRINT(0, "+SATADBGMSG: Port %d reset fail.\n", i);
        }
    }

    //reset HBA
    HW_SATA_GHC_WR(SATA_ENABLED);

    //disable AHCI
    HW_SATA_GHC.B.AE = SATA_DISABLED;

    return ret;
}

sata_return_t sata_identify(u32 port)
{
    u32 hdd_attached;
    u32 hdd_sig;

    PRINT(0, "+SATADBGMSG: SATA port %d base@0x%08x.\n", port, port);
    // 1. check if there is HDD attached.
    hdd_attached = (HW_SATA_PORT(port).SSTS).B.DET; 
    PRINT(0, "+SATADBGMSG: port->ssts = 0x%08x.\n", (HW_SATA_PORT(port).SSTS).U);

    switch (hdd_attached) {
    case SSTS_DET_NO_DEVICE_NO_PHY:
        PRINT(0, "+SATAINFO:No SATA HDD Attached\n");
        return SATA_FAIL;       //fail
    case SSTS_DET_DEV_DET_NO_PHY:
        PRINT(0, "+SATAINFO:SATA HDD Attached, but PHY not established\n");
        //configure PHY
        (HW_SATA_PORT(port).SCTL).U = (SCTL_DET_COMM_INIT | SCTL_SPD_GEN2_NEGOCIATE);
        hal_delay_us(1200);     //at least 1ms is required to ensure COMRESET is sent
        (HW_SATA_PORT(port).CMD).U |= SATA_ENABLED;

        if (((HW_SATA_PORT(port).SSTS).B.DET) != SSTS_DET_DEV_DET_PHY_RDY) {
            PRINT(0, "+SATAINFO:PHY establish fail\n");
            return SATA_FAIL;
        }

        PRINT(0, "+SATAINFO:P0SSTS is 0x%08x\n", (HW_SATA_PORT(port).SSTS).U);
        PRINT(0, "+SATAINFO:PHY establish done\n");
        break;
    case SSTS_DET_DEV_DET_PHY_RDY:
        PRINT(0, "+SATAINFO:SATA HDD Attached, PHY established\n");
        //ready to read the sector 0 to get HDD info
        break;
    case SSTS_DET_PHY_OFFLINE:
    default:
        PRINT(0, "+SATAINFO:SATA DET Status Unknown or unsupported\n");
        return SATA_FAIL;       //faile
    }

    PRINT(0, "+SATAINFO:SATA HDD found on the port %d, ready to get HDD info\n", port);

    hdd_sig = (HW_SATA_PORT(port).SIG).U; 

    sata_hdd_init(port);

    return SATA_PASS;
}

//////////////////////////////////////////////////////////////////////////////
// EOF
//////////////////////////////////////////////////////////////////////////////
