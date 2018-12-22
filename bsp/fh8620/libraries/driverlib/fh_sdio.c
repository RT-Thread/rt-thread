/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "string.h"
#include "inc/fh_sdio.h"
#include "fh_arch.h"
//#include "interrupt.h"

#define SDIO_PRINTF rt_kprintf

#define SDC_USE_IDMA

#define INSTRUCTIONS_PER_USEC          1000
#define CMD_TIMEOUT_USEC 	               100000 
#define DATA_READY_TIMEOUT_USEC 	200000
#define DMA_TRANSFER_TIMEOUT_TICKS 300
#define DATA_TRANSFER_OVER_TIMEOUT_USEC 1000
#define ACMD41_RETRY_COUNT                             1000//100000

#define CIU_CLK		       50000//25000//25000 //27MHz
#define MMC_FOD_VALUE  125	/* 125 KHz */
#define NORM_FOD_VALUE  25000//5000//25000	/* 25 MHz */
#define MMC_FOD_DIVIDER_VALUE   (((CIU_CLK+MMC_FOD_VALUE*2-1)/(MMC_FOD_VALUE*2)))
#ifdef SDCARD_CLK_DIVIDER
#define ONE_BIT_BUS_FREQ   SDCARD_CLK_DIVIDER
#else
#define ONE_BIT_BUS_FREQ   (((CIU_CLK)/(NORM_FOD_VALUE*2)))
#endif

static unsigned int sdc_clk_divider = ONE_BIT_BUS_FREQ;

static sdc_t sdc_array[2];

static void plat_loop(unsigned int macrosecond)
{
	unsigned int clk;
	
	while (macrosecond-- > 0) {
		for(clk=INSTRUCTIONS_PER_USEC; clk>0; clk--);
	}
}

static int synopmob_execute_command(unsigned int base, unsigned int cmd_register, unsigned int arg_register)
{
	unsigned int retries = CMD_TIMEOUT_USEC;

	synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts, FIXME
	synopmob_set_register(base+CMDARG, arg_register);
	synopmob_set_register(base+CMD, cmd_register | (0x80000000|0x20000000/*fixed to use hold*/));

	while (retries-- > 0) {
		if (!(synopmob_read_register(base+CMD) & 0x80000000/*CMD done bit*/))
			return 0;
		plat_loop(1);
	}
	
	return ERRCMDRETRIESOVER;
}

static int synopmob_wait_command_done(unsigned int base, unsigned int* inst, unsigned int flag)
{
	unsigned int retries = CMD_TIMEOUT_USEC;
	unsigned int sts;

	while (retries-- > 0) {
		sts = synopmob_read_register(base+RINTSTS);
		if (sts && ((sts & flag) == flag) ) {
			*inst = sts;
			return 0;
		}
		plat_loop(1);
	}
	return ERRCMDRETRIESOVER;
}

static int synopmob_wait_data_ready(unsigned int base)
{
	unsigned int retries = DATA_READY_TIMEOUT_USEC;

	while (retries-- > 0) {
		if  (!((synopmob_read_register(base+STATUS)) & 0x00000200)) {
			return 0;
		}
		
		plat_loop(1);
	}
	return ERRDATANOTREADY;
}

static int synopmob_handle_standard_rinsts(unsigned int raw_int_stat)
{
	int error_status = 0;
	
	if ( raw_int_stat &  INTMASK_ERROR) {
		if (raw_int_stat & INTMSK_RESP_ERR) {
			error_status = ERRRESPRECEP;
		}
		if (raw_int_stat & INTMSK_RCRC) {
			error_status = ERRRESPCRC;
		}
		if (raw_int_stat & INTMSK_DCRC) {
			error_status = ERRDCRC;
		}		
		if (raw_int_stat & INTMSK_RTO) {
			error_status = ERRRESPTIMEOUT;
		}		
		if (raw_int_stat & INTMSK_DTO) {
			error_status = ERRDRTIMEOUT;
		}
		if (raw_int_stat & INTMSK_HTO) {
			error_status = ERRUNDERWRITE;
		}
		if (raw_int_stat & INTMSK_FRUN) {
			error_status = ERROVERREAD;
		}
		if (raw_int_stat & INTMSK_HLE) {
			error_status = ERRHLE;
		}
		if (raw_int_stat & INTMSK_SBE) {
			error_status = ERRSTARTBIT;
		}		
		if (raw_int_stat & INTMSK_EBE) {
			error_status = ERRENDBITERR;
		}
	}

//SDIO_PRINTF("------- %s, line %d raw_int_stat = %08x-------\n", __FUNCTION__, __LINE__, raw_int_stat);
	return error_status;
}

static int synopmob_check_r1_resp(unsigned int the_response)
{
	int retval = 0;
	
	if (the_response & R1CS_ERROR_OCCURED_MAP) {
		if (the_response & R1CS_ADDRESS_OUT_OF_RANGE) {
			retval = ERRADDRESSRANGE;
		} else if (the_response & R1CS_ADDRESS_MISALIGN) {
			retval = ERRADDRESSMISALIGN;
		} else if (the_response & R1CS_BLOCK_LEN_ERR) {
			retval = ERRBLOCKLEN;
		} else if (the_response & R1CS_ERASE_SEQ_ERR) {
			retval = ERRERASESEQERR;
		} else if (the_response & R1CS_ERASE_PARAM) {
			retval = ERRERASEPARAM;
		} else if (the_response & R1CS_WP_VIOLATION) {
			retval = ERRPROT;
		} else if (the_response & R1CS_CARD_IS_LOCKED) {
			retval = ERRCARDLOCKED;
		} else if (the_response & R1CS_LCK_UNLCK_FAILED) {
			retval = ERRCARDLOCKED;
		} else if (the_response & R1CS_COM_CRC_ERROR) {
			retval = ERRCRC;
		} else if (the_response & R1CS_ILLEGAL_COMMAND) {
			retval = ERRILLEGALCOMMAND;
		} else if (the_response & R1CS_CARD_ECC_FAILED) {
			retval = ERRECCFAILED;
		} else if (the_response & R1CS_CC_ERROR) {
			retval = ERRCCERR;
		} else if (the_response & R1CS_ERROR) {
			retval = ERRUNKNOWN;
		} else if (the_response & R1CS_UNDERRUN) {
			retval = ERRUNDERRUN;
		} else if (the_response & R1CS_OVERRUN) {
			retval = ERROVERRUN;
		} else if (the_response & R1CS_CSD_OVERWRITE) {
			retval = ERRCSDOVERWRITE;
		} else if (the_response & R1CS_WP_ERASE_SKIP) {
			retval = ERRPROT;
		} else if (the_response & R1CS_ERASE_RESET) {
			retval = ERRERASERESET;
		} else if (the_response & R1CS_SWITCH_ERROR) {
			retval = ERRFSMSTATE;
		}
	}
	
	return retval;
}


static int synopmob_check_r5_resp(unsigned int the_resp)
{
	int ret = 0;
	
	if (the_resp & R5_IO_ERR_BITS) {
		if (the_resp & R5_IO_CRC_ERR) {
			ret = ERRDCRC;
		} else if (the_resp & R5_IO_BAD_CMD) {
			ret = ERRILLEGALCOMMAND;
		} else if (the_resp & R5_IO_GEN_ERR) {
			ret = ERRUNKNOWN;
		} else if (the_resp & R5_IO_FUNC_ERR) {
			ret = ERRBADFUNC;
		} else if (the_resp & R5_IO_OUT_RANGE) {
			ret = ERRADDRESSRANGE;
		}
	}
	
	return ret;
}

static int sd_send_cmd0(sdc_t* sdc)
{
	int   ret;
	unsigned int intst;
	unsigned int base = sdc->ip_base;

	ret = synopmob_execute_command(base, 0x4000, 0);
	if (!ret) {
		ret = synopmob_wait_command_done(base, &intst, INTMSK_CMD_DONE);
		if (!ret) {
			synopmob_set_register(base+RINTSTS, intst);
			return synopmob_handle_standard_rinsts(intst);
		}
	}

	return ret;
}

static int sd_send_cmd2(sdc_t* sdc)
{
	int   ret;
	unsigned int intst;
	unsigned int base = sdc->ip_base;

	ret = synopmob_execute_command(base, 0xC2, 0);
	if (!ret) {
		ret = synopmob_wait_command_done(base, &intst, INTMSK_CMD_DONE);
		if (!ret) {
			synopmob_set_register(base+RINTSTS, intst);
			return synopmob_handle_standard_rinsts(intst);
		}
	}

	return ret;
}

static int sd_send_cmd3(sdc_t* sdc)
{
	int   ret;
	unsigned int intst;
	unsigned int resp;
	unsigned int base = sdc->ip_base;

	ret = synopmob_execute_command(base, 0x43, 0);
	if (!ret) {
		ret = synopmob_wait_command_done(base, &intst, INTMSK_CMD_DONE);
		if (!ret) {
			synopmob_set_register(base+RINTSTS, intst);
			ret = synopmob_handle_standard_rinsts(intst);
			if (!ret) {
				resp = synopmob_read_register(base+RESP0);
				sdc->rca = resp >> 16;
				resp = (resp & 0x1fff) | (((resp>>13)&1)<<19) | (((resp>>14)&3)<<22);
				return synopmob_check_r1_resp(resp);
			}
		}		
	}

	return ret;
}

static int sd_send_cmd_r1(sdc_t* sdc, unsigned int cmd, unsigned int arg, unsigned int buzy)
{
	int   ret;
	unsigned int intst;
	unsigned int resp;
	unsigned int base = sdc->ip_base;
	
	ret = synopmob_execute_command(base, cmd,  arg);
	if (!ret) {
		ret = synopmob_wait_command_done(base, &intst, INTMSK_CMD_DONE);
		if (!ret) {
			synopmob_set_register(base+RINTSTS, intst);
			ret = synopmob_handle_standard_rinsts(intst);
			if (!ret) {
				resp = synopmob_read_register(base+RESP0);
				ret = synopmob_check_r1_resp(resp);
				if (buzy && !ret) {
					ret = synopmob_wait_data_ready(base);
				}
			}
		}
	}

	return ret;
}

static int sd_send_cmd7(sdc_t* sdc)
{
	return sd_send_cmd_r1(sdc, 0x47, sdc->rca<<16, 1);
}

static int sd_send_uncmd7(sdc_t* sdc)
{
	int   ret;
	unsigned int intst;
	unsigned int base = sdc->ip_base;

	ret = synopmob_execute_command(base, 0x7, 0);
	if (!ret) {
		ret = synopmob_wait_command_done(base, &intst, INTMSK_CMD_DONE);
		if (!ret) {
			synopmob_set_register(base+RINTSTS, intst);
			ret = synopmob_handle_standard_rinsts(intst);
		}
	}

	return ret;
}

static int sd_send_cmd16(sdc_t* sdc)
{
	return sd_send_cmd_r1(sdc, 0x50, 512, 0);
}

static int sd_send_cmd55(sdc_t* sdc)
{
	return sd_send_cmd_r1(sdc, 0x77, sdc->rca<<16, 0);
}

static int sd_send_acmd6(sdc_t* sdc, unsigned int bitwidth)
{
	unsigned int cmd_arg;
	int   ret;
	unsigned int base = sdc->ip_base;

	ret = sd_send_cmd55(sdc);
	if (!ret) {	
		cmd_arg = 0; //default to 1bit mode
		if (bitwidth == 4) {
			cmd_arg = 2; // 4bit mode
		}
		ret = sd_send_cmd_r1(sdc, 0x2046, cmd_arg, 0);
		if (!ret) {
			if (bitwidth == 4) {
				synopmob_set_register(base+CTYPE, FOUR_BIT_MODE);
			}
			else {
				synopmob_set_register(base+CTYPE, ONE_BIT_MODE);
			}
		}
	}

	return ret;
}

#ifdef SDC_USE_IDMA
static int sdc_read_write_block(HSDC handle, unsigned int rw, unsigned int blk, unsigned int num, unsigned char* buffer)
{
	sdc_t* sdc = (sdc_t*)handle;
	volatile DmaDesc *pDmaDesc = sdc->pDmaDesc;
	int   ret;
	unsigned int intsts = 0;
	unsigned int cmd;
	unsigned int multi = 0;
	unsigned int base = sdc->ip_base;
	int   loop_for_command_done_check = DATA_TRANSFER_OVER_TIMEOUT_USEC;
	rt_err_t err;	

	// valid check
	if (synopmob_read_register(base+CDETECT) & 1) {
		return ERRCARDNOTCONN;
	}
	if (!num || num > 16) {
		return ERRNOTSUPPORTED;
	}
	if (blk + num > sdc->sectors) {
		return ERRADDRESSRANGE;
	}

	if ( rw ) {
		flush_dcache_range((unsigned long)buffer, num << 9);
	}
	else {
	    // to avoid memset bug?
		inv_dcache_range((unsigned long)buffer, num << 9);
    }

	err = rt_sem_take(sdc->mutex, RT_WAITING_FOREVER);
	if (err != RT_EOK) {
		return ERRNORES;
	}

	// reset
	synopmob_set_bits(base+CTRL, FIFO_RESET); //reset FIFO
	while (synopmob_read_register(base+CTRL) & FIFO_RESET);
	synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts

	cmd = 0x2658; // write
	if ( !rw ) {
		cmd = 0x2251; //read
	}
	//if (num > 1) {
	if (num >= 1) { // some card fail on sigle-block mode, so use multi-block instead of sigle-block mode.
		cmd++;
		multi++;
	}
	if (sdc->card_type == SD_TYPE) {
		blk <<= 9; //SD stadand capability card use 512 unit.
	}
	num <<= 9;
	
	pDmaDesc->desc0 |= DescOwnByDma | DescFirstDesc | DescLastDesc;
	pDmaDesc->desc1 = ((num << DescBuf1SizeShift) & DescBuf1SizMsk);
	pDmaDesc->desc2 = (unsigned int)buffer;
	flush_dcache_range((unsigned long)pDmaDesc, sizeof(DmaDesc)); // add SZ_ADJUST
	synopmob_set_register(base + DBADDR, (unsigned int)(pDmaDesc)); // add SZ_ADJUST
	synopmob_set_register(base+BLKSIZ, 512);
	synopmob_set_register(base+BYTCNT, num);
	synopmob_set_bits(base + CTRL, CTRL_USE_IDMAC);
	synopmob_set_bits(base + BMOD,BMOD_DE);
	
	ret = synopmob_execute_command(base, cmd,  blk);
	if ( !ret ) {
		ret = ERRIDMA;
		synopmob_set_bits(base+CTRL, INT_ENABLE);
		err = rt_sem_take(sdc->sem, DMA_TRANSFER_TIMEOUT_TICKS);
		if ( !err ) {
			while (--loop_for_command_done_check > 0) {
				intsts = synopmob_read_register(base+RINTSTS);
				if ((intsts & (INTMSK_CMD_DONE|INTMSK_DAT_OVER)) == (INTMSK_CMD_DONE|INTMSK_DAT_OVER)) {
					break;
				}
				plat_loop(1);
			}
			ret = synopmob_handle_standard_rinsts(intsts);
			if (!ret ) {
				if( !loop_for_command_done_check || !(sdc->idsts & 0x100)) { //normal interrupt
					ret = ERRIDMA;
				}
			}
		}
	}

	if (ret) {
	   	char* op = "read";
	   	if (rw) 
	   		op = "write";
	   		
	        SDIO_PRINTF("sdc_read_write_block(%s) fail:, ret = %d\n", op, ret);
	}

	synopmob_clear_bits(base+CTRL, INT_ENABLE);
	synopmob_clear_bits(base + CTRL, CTRL_USE_IDMAC);
	synopmob_clear_bits(base + BMOD,BMOD_DE);

	synopmob_set_register(base+BLKSIZ, 512);
	synopmob_set_register(base+BYTCNT, 512);

	synopmob_set_register(base + RINTSTS, 0xfffe);

	if ( !ret && rw) {
		ret = synopmob_wait_data_ready(base);
	}

	if (!ret && multi ) { //send STOP_TRANSACTION command
		ret = sd_send_cmd_r1(sdc, 0x404c, 0, 1);
	}

	rt_sem_release(sdc->mutex);
	
	if ( !rw && !ret ) { //read
		inv_dcache_range((unsigned long)buffer, num);
	}
	
	return ret;
}
#else  //no IDMA
static int sdc_read_write_block(HSDC handle, unsigned int rw, unsigned int blk, unsigned int num, unsigned char* buffer)
{
	sdc_t* sdc = (sdc_t*)handle;
	volatile DmaDesc *pDmaDesc = sdc->pDmaDesc;
	int   ret;
	unsigned int intsts = 0;
	unsigned int entries;
	unsigned int cmd;
	unsigned int multi = 0;
	unsigned int base = sdc->ip_base;
	int   loop_for_command_done_check = DATA_TRANSFER_OVER_TIMEOUT_USEC;
	rt_err_t err;	

	// valid check
	if (synopmob_read_register(base+CDETECT) & 1) {
		return ERRCARDNOTCONN;
	}
	if (!num || num > 16) {
		return ERRNOTSUPPORTED;
	}
	if (blk + num > sdc->sectors) {
		return ERRADDRESSRANGE;
	}

	if ( rw ) {
		flush_dcache_range((unsigned long)buffer, num << 9);
	}
	else {
	    // to avoid memset bug?
		inv_dcache_range((unsigned long)buffer, num << 9);
    }

	err = rt_sem_take(sdc->mutex, RT_WAITING_FOREVER);
	if (err != RT_EOK) {
		return ERRNORES;
	}

	// reset
	synopmob_set_bits(base+CTRL, FIFO_RESET); //reset FIFO
	while (synopmob_read_register(base+CTRL) & FIFO_RESET);
	synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts

	cmd = 0x2658; // write
	if ( !rw ) {
		cmd = 0x2251; //read
	}
	if (num > 1) {
		cmd++;
		multi++;
	}
	if (sdc->card_type == SD_TYPE) {
		blk <<= 9; //SD stadand capability card use 512 unit.
	}
	num <<= 9;
	
	synopmob_set_register(base+BLKSIZ, 512);
	synopmob_set_register(base+BYTCNT, num);
	
	ret = synopmob_execute_command(base, cmd,  blk);
	if ( !ret ) {
		while (1) {
			ret = synopmob_wait_command_done(base, &intsts, 0);
			if (ret)
				break;

			ret = synopmob_handle_standard_rinsts(intsts);
			if (ret)
				break;

			if (!rw && (intsts & (INTMSK_RXDR|INTMSK_DAT_OVER)) ){
				while (num > 0 ) {
					entries = synopmob_read_register(base + STATUS);
					if (!GET_FIFO_COUNT(entries))
						break;
					*((volatile unsigned int*)buffer) = synopmob_read_register(base + FIFODAT);
					buffer += 4;
					num -= 4;
				}
			}
			
			if (rw && ( intsts & INTMSK_TXDR ) ) {
				while (num > 0) {
					entries = synopmob_read_register(base+STATUS);
					if ( entries & 8 ) { //FIFO is full
						break;
					}
					synopmob_set_register(base+FIFODAT, *((volatile unsigned int*)buffer));
					buffer += 4;
					num -= 4;
				}
			}
			
			if ( intsts & INTMSK_DAT_OVER ) {
				break;
			}

			if (intsts & INTMSK_CMD_DONE) {
				entries = synopmob_read_register(base+RESP0);
				ret = synopmob_check_r1_resp(entries);
				if (ret) {
					break;
				}
			}

			synopmob_set_register(base+RINTSTS, intsts); //write to clear
			intsts = 0;
		}		
		
		if (intsts) {
			synopmob_set_register(base+RINTSTS, intsts); //write to clear
		}
	}

	synopmob_set_register(base+BLKSIZ, 512);
	synopmob_set_register(base+BYTCNT, 512);
	synopmob_set_register(base + RINTSTS, 0xfffe);

	if ( !ret && rw) {
		ret = synopmob_wait_data_ready(base);
	}

	if (!ret && multi ) { //send STOP_TRANSACTION command
		ret = sd_send_cmd_r1(sdc, 0x404c, 0, 1);
	}

	rt_sem_release(sdc->mutex);
	
	if ( !rw && !ret ) { //read
		inv_dcache_range((unsigned long)buffer, num);
	}
	
	return ret;
}
#endif //SDC_USE_IDMA

int sdc_write_block(HSDC handle, unsigned int blk, unsigned int num, unsigned char* buffer)
{
	return sdc_read_write_block(handle, 1, blk, num, buffer);
}

int sdc_read_block(HSDC handle, unsigned int blk, unsigned int num, unsigned char* buffer)
{
	return sdc_read_write_block(handle, 0, blk, num, buffer);
}

int sdc_erase_block(HSDC handle, unsigned int blk, unsigned int num)
{
	int   ret;
	sdc_t* sdc = (sdc_t*)handle;
	
	if (sdc->card_type == SD_TYPE) {
		blk <<= 9; //SD stadand capability card use 512 unit.
		num = ((num-1)<<9) + blk;
	}
	else {
		num = blk + num - 1;
	}
	
	ret = sd_send_cmd_r1(sdc, 0x40|32, blk, 0); // cmd32
	if (!ret) {
		ret = sd_send_cmd_r1(sdc, 0x40|33, num, 0); // cmd33
		if (!ret) {
			ret = sd_send_cmd_r1(sdc, 0x40|38, 0, 1); // cmd38
		}
	}

	return ret;
}

int sdc_get_sector_num(HSDC handle)
{
	return ((sdc_t*)handle)->sectors;
}

static int sd_send_cmd9(sdc_t* sdc)
{
	int   ret;
	unsigned int intst;
	unsigned int resp0;
	unsigned int resp1;
	unsigned int resp2;
	unsigned int resp3;
	unsigned int base = sdc->ip_base;
	unsigned int C_SIZE;
	unsigned int C_SIZE_MULT;
	unsigned int READ_BL_LEN;

	ret = synopmob_execute_command(base, 0xC9, sdc->rca<<16);
	if (!ret) {
		ret = synopmob_wait_command_done(base, &intst, INTMSK_CMD_DONE);
		if (!ret) {
			synopmob_set_register(base+RINTSTS, intst);
			ret = synopmob_handle_standard_rinsts(intst);
			if (!ret) {
				sdc->csd[0] = resp0 = synopmob_read_register(base+RESP0);
				sdc->csd[1] = resp1 = synopmob_read_register(base+RESP1);
				sdc->csd[2] = resp2 = synopmob_read_register(base+RESP2);
				sdc->csd[3] = resp3 = synopmob_read_register(base+RESP3);
				
				if ((resp3>>30) == 0) { //CSD version 1.0
					C_SIZE = (resp1 >> 30) | ((resp2 & 0x3ff)<<2);
					C_SIZE_MULT = ((resp1 >> 15) & 0x07);				
					READ_BL_LEN = ((resp2 >> 16) & 0xf);
					sdc->sectors = ((((C_SIZE+1)<<(C_SIZE_MULT+2))<<(READ_BL_LEN))>>9);
				}
				else { //CSD version 2.0
					sdc->sectors = (((resp1 >> 16)+1)<<10);
				}
			}
		}		
	}

	return ret;
}

static int sd_send_cmd5(sdc_t* sdc, unsigned int arg, unsigned int* resp)
{
	unsigned int cmd_reg = 0x45;
	unsigned int intst;
	int   ret;
	unsigned int base = sdc->ip_base;

	ret = synopmob_execute_command(base, cmd_reg, arg);
	if (!ret) {
		ret = synopmob_wait_command_done(base, &intst, INTMSK_CMD_DONE);
		if (!ret) {
			synopmob_set_register(base+RINTSTS, intst);
			ret = synopmob_handle_standard_rinsts(intst);
			if (!ret) {
				*resp = synopmob_read_register(base+RESP0);
			}
		}
	}
	
	return ret;	
}

static int sd_send_cmd8(sdc_t* sdc)
{
	int   ret;
	unsigned int cmd_reg = 0x48;
	unsigned int intst;
	unsigned int err = 0;
	unsigned int base = sdc->ip_base;
	
	ret = synopmob_execute_command(base, cmd_reg, 0x000001A5);
	if (!ret) {
		while (1) {
			ret = synopmob_wait_command_done(base, &intst, 0);
			if (!ret) {
				synopmob_set_register(base+RINTSTS, intst);
				err |= synopmob_handle_standard_rinsts(intst);
				if (intst & INTMSK_CMD_DONE) {
					break;
				}
			}
		}
	}

	return err;
}

static int sd_send_acmd41(sdc_t* sdc, int* hcs)
{
	unsigned int cmd_reg = 0x69;
	unsigned int resp;
	int   ret = 0;
	unsigned int count = ACMD41_RETRY_COUNT;
	unsigned int cmd_arg = 0xff8000;
	unsigned int base = sdc->ip_base;

	if (*hcs) {
		cmd_arg |= (1<<30);
	}
	while ( count > 0) {
		SDC_WHERE();
		ret = sd_send_cmd55(sdc);
		if (ret)
			break;

		SDC_WHERE();
		ret = synopmob_execute_command(base, cmd_reg, cmd_arg);
		if (ret)
			break;

		SDC_WHERE();
		ret = synopmob_wait_command_done(base, &resp, INTMSK_CMD_DONE);
		if ( ret ) 
			break;

		SDC_WHERE();
		synopmob_set_register(base+RINTSTS, resp);
		ret = synopmob_handle_standard_rinsts(resp);
		if (!ret) {
			SDC_WHERE();
			resp = synopmob_read_register(base+RESP0);
			if (resp & 0x80000000) { //card is ready.
				SDC_WHERE();
				if ( !(resp & (1<<30)) ) {
					SDC_WHERE();
					*hcs = 0;
				}
				if ( (resp & 0x00ff8000) != 0x00ff8000 ) { //not supported voltage
					ret = ERRHARDWARE;
				}
				break;
			}
		}

		--count;
		plat_loop(1);
	}

	if (!count)
		ret = ERRACMD41TIMEOUT;
	
	return ret;
}

static int sd_send_acmd51(sdc_t* sdc) //Send SCR
{
	unsigned int cmd_reg = 0x2273;
	unsigned int resp;
	int   ret;
	unsigned int intst = 0;
	unsigned int entries;
	int   count = 1;
	unsigned int base = sdc->ip_base;

	ret = sd_send_cmd55(sdc);
	if (!ret) {	
		synopmob_set_register(base+BLKSIZ, 8);
		synopmob_set_register(base+BYTCNT, 8);
		ret = synopmob_execute_command(base, cmd_reg, 0);
		if (!ret) {
			while (1) {
				ret = synopmob_wait_command_done(base, &intst, 0);
				if (ret) {
					break;
				}

				ret = synopmob_handle_standard_rinsts(intst);
				if (ret) {
					break;
				}
				
				if (intst & INTMSK_CMD_DONE) {
					resp = synopmob_read_register(base+RESP0);
					ret = synopmob_check_r1_resp(resp);
					if (ret) 
						break;
				}

				if (intst & INTMSK_DAT_OVER) {
					entries = synopmob_read_register(base + STATUS);
					if (GET_FIFO_COUNT(entries) == 2) {
						while (count >= 0) {
							entries = synopmob_read_register(base + FIFODAT);
							sdc->scr[count--] = BE32_TO_CPU(entries);
						}
					}
					break;
				}

				synopmob_set_register(base+RINTSTS, intst);
				intst = 0;
			}

			if (intst) {
				synopmob_set_register(base+RINTSTS, intst);
			}
		}

		synopmob_set_register(base+BLKSIZ, 512);
		synopmob_set_register(base+BYTCNT, 512);
	}

	return ret;
}


static int sd_send_cmd6(sdc_t* sdc, unsigned int cmd_arg, unsigned int* data_buff) 
{
	unsigned int cmd_reg = 0x2246;
	unsigned int resp;
	int   ret;
	unsigned int intst = 0;
	unsigned int entries;
	int   count = 64;
	unsigned int base = sdc->ip_base;

	synopmob_set_register(base+BLKSIZ, 64);
	synopmob_set_register(base+BYTCNT, 64);
	ret = synopmob_execute_command(base, cmd_reg, cmd_arg);
	if (!ret) {
		while (1) {
			ret = synopmob_wait_command_done(base, &intst, 0);
			if (ret) {
				break;
			}

			ret = synopmob_handle_standard_rinsts(intst);
			if (ret) {
				break;
			}
				
			if (intst & INTMSK_CMD_DONE) {
				resp = synopmob_read_register(base+RESP0);
				ret = synopmob_check_r1_resp(resp);
				if (ret) 
					break;
			}

			while (count > 0) {
				entries = synopmob_read_register(base + STATUS);
				if ( !GET_FIFO_COUNT(entries) ) {
					break;
				}
				*(data_buff++) = synopmob_read_register(base + FIFODAT);
				count -= 4;
			}

			if (intst & INTMSK_DAT_OVER) {
				break;
			}

			synopmob_set_register(base+RINTSTS, intst); //write to clear
			intst = 0;
		}

		if (intst) {
			synopmob_set_register(base+RINTSTS, intst); //write to clear
		}
	}

	synopmob_set_register(base+BLKSIZ, 512);
	synopmob_set_register(base+BYTCNT, 512);

	return ret;
}

static int synopmob_send_clock_only_cmd(unsigned int base)
{
	return synopmob_execute_command(base, 0x202000, 0);
}


static int synopmob_disable_all_clocks(unsigned int base)
{
	synopmob_set_register(base+CLKENA, 0);
	return synopmob_send_clock_only_cmd(base);
}

static int synopmob_enable_clocks_with_val(unsigned int base, unsigned int val)
{
	synopmob_set_register(base+CLKENA, val);
	return synopmob_send_clock_only_cmd(base);
}


static int synopmob_set_clk_freq(sdc_t* sdc, unsigned int divider)
{
	#define MAX_DIVIDER_VALUE      0xff
	
	unsigned int orig_clkena;
	int  retval;
	unsigned int base = sdc->ip_base;

	if (divider > MAX_DIVIDER_VALUE) {
		return 0xffffffff;
	}

	/* To make sure we dont disturb enable/disable settings of the cards*/
	orig_clkena = synopmob_read_register(base+CLKENA);

	/* Disable all clocks before changing frequency the of card clocks */
	if ((retval = synopmob_disable_all_clocks(base)) != 0) {
		return retval;
	}
	/* Program the clock divider in our case it is divider 0 */
	synopmob_clear_bits(base+CLKDIV, MAX_DIVIDER_VALUE);
	synopmob_set_bits(base+CLKDIV, divider);
	
	/*Send the command to CIU using synopmob_send_clock_only_cmd and enable the clocks in CLKENA register */
	if ((retval = synopmob_send_clock_only_cmd(base)) != 0) {
		synopmob_enable_clocks_with_val(base, orig_clkena);
		return retval;
	}

	return synopmob_enable_clocks_with_val(base, orig_clkena);
}

static int enum_sd_card(sdc_t* sdc)
{
	int ret;
	int count = 1000;
	int hcs = 0;
	unsigned int buffer[16];
	unsigned int base = sdc->ip_base;

	if (synopmob_read_register(base+CDETECT) & 1) {
		return ERRCARDNOTCONN;
	}
	
	#if 0
	synopmob_set_bits(0x98500004, (1<<24)); //set to output mode
	synopmob_set_bits(0x98500000, (1<<24)); //power off
	plat_loop(1000000/5); //Lets give some ramp down period
	synopmob_clear_bits(0x98500000, (1<<24)); //power on
	plat_loop(1000000/5);//Lets give some ramp down period
	#endif
	
	synopmob_set_register(base+CTYPE, ONE_BIT_MODE);

	synopmob_set_register(base+CLKENA, 0x00000001); /*enable clock, non-low-power mode*/
	ret = synopmob_set_clk_freq(sdc, MMC_FOD_DIVIDER_VALUE);
	
	if ( !ret ) {
		plat_loop(1000); //enough for 74 clock.	
		SDC_WHERE();
		ret = sd_send_cmd0(sdc); //CMD0 has no response
	}
	
	if ( !ret ) {
		SDC_WHERE();
		ret = sd_send_cmd8(sdc); //even if CMD8 get response, it may be V1.0 card.
		if (!ret) {
			hcs = 1;
		}
		SDC_WHERE();
		ret = sd_send_acmd41(sdc, &hcs);
	}

	if (!ret) {
		SDC_WHERE();
		ret = sd_send_cmd2(sdc); //CID
	}

	if (!ret) {
		SDC_WHERE();
		ret = sd_send_cmd3(sdc); //get RCA
	}

	if (!ret) {
		SDC_WHERE();
		ret = sd_send_cmd9(sdc); //CSD
	}

	if (!ret) {
		SDC_WHERE();
		ret = sd_send_cmd7(sdc); //select the card
	}

	if (!ret && (sdc->wkmod & SDC_WKMOD_4WIRE) ) {
		SDC_WHERE();
		ret = sd_send_acmd51(sdc); //SCR
		if (!ret && (sdc->scr[1] & 0x00040000)) { // 4bit mode supported?
			ret = sd_send_acmd6(sdc, 4); //switch to 4bit mode
		}
	}
	
	if (!ret && (sdc->wkmod & SDC_WKMOD_50M_HI_SPEED) && (sdc->csd[2] & 0x40000000) ) { //judge whether class10 is supported? CMD6 is belonging to class10.
		SDC_WHERE();
		ret = sd_send_cmd6(sdc, 0x00fffff1, buffer); //switch to high speed mode.
		if ( !ret &&  (*(((unsigned char*)buffer)+13)&0x02) ) { //the card support high speed mode?
			SDC_WHERE();
			ret = sd_send_cmd6(sdc, 0x80fffff1, buffer); //switch to high speed mode.
			if (!ret && ((*(((unsigned char*)buffer)+16) & 0xf) == 1) ) {
				//switch to high speed mode sucess.
				sd_send_uncmd7(sdc); //deselect the card
				sd_send_cmd9(sdc); //CSD
				ret = sd_send_cmd7(sdc); //select the card
			}
		}
	}
	
	if (!ret && (sdc->wkmod & (SDC_WKMOD_50M_HI_SPEED|SDC_WKMOD_25M_STAND_SPEED))) {
		if ( (sdc->csd[3] & 0xff) == 0x5A ) { //50MHz high speed mode.			
			SDC_WHERE();
			ret = synopmob_set_clk_freq(sdc, (((CIU_CLK)/(50000*2))));
		}
		else if ( (sdc->csd[3] & 0xff) == 0x32 ) {
			SDC_WHERE(); //25MHz standard speed mode.
			ret = synopmob_set_clk_freq(sdc, sdc_clk_divider/*ONE_BIT_BUS_FREQ*/);
		}
	}

	if (!ret) {
		sdc->card_type = SD_TYPE;
		if (hcs) {
			sdc->card_type = SD_2_0_TYPE;
		}
	}

	return ret;
}

int sdio_drv_creg_read(HSDC handle, int addr, int fn, unsigned int *resp)
{
	sdc_t* sdc = (sdc_t*)handle;
	unsigned int arg;
	unsigned int cmd_reg = 0x74;
	unsigned int intst;
	int   ret;
	unsigned int base = sdc->ip_base;
	rt_err_t err;

    if(resp) {
        *resp = 0;
    }
    
	err = rt_sem_take(sdc->mutex, RT_WAITING_FOREVER);
	if (err != RT_EOK) {
		return ERRNORES;
	}

	arg = (fn << 28) | (addr << 9);
	ret = synopmob_execute_command(base, cmd_reg, arg);
	if (!ret) {
		ret = synopmob_wait_command_done(base, &intst, INTMSK_CMD_DONE);
		if (!ret) {
			synopmob_set_register(base+RINTSTS, intst); //write to clear
			ret = synopmob_handle_standard_rinsts(intst);
			if (!ret) {
				*resp = synopmob_read_register(base+RESP0);
				ret = synopmob_check_r5_resp(*resp);
			}
		}
	}

	rt_sem_release(sdc->mutex);
	
	if (ret) {
		ret++;
		ret--;
		SDIO_PRINTF("sdio_drv_creg_read fail:, ret = %d\n", ret);
	}
	
	return ret;
}

int sdio_drv_creg_write(HSDC handle, int addr, int fn, unsigned char data, unsigned int *resp)
{
	sdc_t* sdc = (sdc_t*)handle;
	unsigned int arg;
	unsigned int cmd_reg = 0x74;
	unsigned int intst;
	int   ret;
	unsigned int base = sdc->ip_base;
	rt_err_t err;

	err = rt_sem_take(sdc->mutex, RT_WAITING_FOREVER);
	if (err != RT_EOK) {
		return ERRNORES;
	}
	
	arg = (1 << 31) | (fn << 28) | (1 << 27) | (addr << 9) | data;
	ret = synopmob_execute_command(base, cmd_reg, arg);
	if (!ret) {
		ret = synopmob_wait_command_done(base, &intst, INTMSK_CMD_DONE);
		if (!ret) {
			synopmob_set_register(base+RINTSTS, intst); //write to clear
			ret = synopmob_handle_standard_rinsts(intst);
			if (!ret) {
				*resp = synopmob_read_register(base+RESP0);
				ret = synopmob_check_r5_resp(*resp);
			}
		}
	}

	rt_sem_release(sdc->mutex);
	if (ret) {
		ret++;
		ret--;
		SDIO_PRINTF("sdio_drv_creg_write fail:, ret = %d\n", ret);
	}
	
	return ret;
}

#define ARC_REG_DC_IVDL 0x4A
#define ARC_REG_DC_FLDL 0x4C
#define ARC_REG_DC_CTRL 0x48
#define FS_FLAG 0x100
#define _psp_get_aux(aux_reg) \
   (unsigned long)_lr((unsigned)(aux_reg))

#define _psp_set_aux(aux_reg,value) \
   _sr((unsigned)(value),(unsigned)(aux_reg))

extern void mmu_clean_dcache(rt_uint32_t buffer, rt_uint32_t size);
extern void mmu_invalidate_dcache(rt_uint32_t buffer, rt_uint32_t size);
void inv_dcache_range(unsigned long start, unsigned long len)
{
	mmu_invalidate_dcache(start, len);
}

void flush_dcache_range(unsigned long start, unsigned long len)
{
	mmu_clean_dcache(start, len);
}

int g_use_bcm43362 = 0;
static int sdio_drv_read_write(sdc_t* sdc, unsigned int rw, unsigned int addr, unsigned int fn, unsigned int bcnt,
								   unsigned int bsize, unsigned char *buf)
{
	volatile DmaDesc *pDmaDesc = sdc->pDmaDesc;
	int   ret;	
	unsigned int intsts = 0;
	unsigned int cmd = 0x2275;
	unsigned int base = sdc->ip_base;
	unsigned int arg;
	unsigned int num;
	int   loop_for_command_done_check = 10000;//DATA_TRANSFER_OVER_TIMEOUT_USEC;	
	rt_err_t err;	

//SDIO_PRINTF("------- %s, line %d buf = %08x size = %d -------\n", __FUNCTION__, __LINE__, buf, bsize);
	arg = (fn << 28) | (addr << 9);

	if (g_use_bcm43362) {
		arg |= (1 << 26); //OPcode = 1............, for AP6181.
	}

	if (bcnt == 1 && bsize <= 512)
		arg |= (bsize & 0x1ff);
	else
		arg |= ((1 << 27) | bcnt);	
	if ( rw ) {
		cmd |= 0x400;
		arg |= (1 << 31);
	}
	num = bsize*bcnt;

	if ( rw ) {
		flush_dcache_range((unsigned long)buf, num);
	}
	else {
		inv_dcache_range((unsigned long)buf, num);
    }

	err = rt_sem_take(sdc->mutex, RT_WAITING_FOREVER);
	if (err != RT_EOK) {
	return ERRNORES;
	}

//synopmob_set_bits(base+FIFOTH, 0x2 << 28);
	// reset
	synopmob_set_bits(base+CTRL, FIFO_RESET); //reset FIFO
	while (synopmob_read_register(base+CTRL) & FIFO_RESET);
	synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts

	//pDmaDesc->desc0 = 0;
	pDmaDesc->desc0 |= DescOwnByDma | DescFirstDesc | DescLastDesc;
	pDmaDesc->desc1 = ((num << DescBuf1SizeShift) & DescBuf1SizMsk);
	pDmaDesc->desc2 = (unsigned int)buf;
	//pDmaDesc->desc3 = 0;
	flush_dcache_range((unsigned int)pDmaDesc, sizeof(DmaDesc));
	synopmob_set_register(base+DBADDR, (unsigned int)pDmaDesc);
	synopmob_set_register(base+BLKSIZ, bsize);
	synopmob_set_register(base+BYTCNT, num);
	synopmob_set_bits(base + CTRL, CTRL_USE_IDMAC);
	synopmob_set_bits(base + BMOD,BMOD_DE);

//SDIO_PRINTF("pDmaDesc = %08x, %08x / %08x / %08x / %08x\n", pDmaDesc, pDmaDesc->desc0, pDmaDesc->desc1, pDmaDesc->desc2, pDmaDesc->desc3);
	ret = synopmob_execute_command(base, cmd,  arg);
	if ( !ret ) {
		ret = ERRIDMA;
		err = rt_sem_take(sdc->sem, DMA_TRANSFER_TIMEOUT_TICKS);
		if ( !err ) {
			while (--loop_for_command_done_check > 0) {
				intsts = synopmob_read_register(base+RINTSTS);
				if ((intsts & (INTMSK_CMD_DONE|INTMSK_DAT_OVER)) == (INTMSK_CMD_DONE|INTMSK_DAT_OVER)) {
					break;
				}
				plat_loop(1);
			}
			ret = synopmob_handle_standard_rinsts(intsts);
			if (!ret ) {
				if( !loop_for_command_done_check || !(sdc->idsts & 0x100)) { //normal interrupt
SDIO_PRINTF("------- %s, line %d idsts = %08x check = %d -------\n", __FUNCTION__, __LINE__, sdc->idsts, loop_for_command_done_check);
					ret = ERRIDMA;
				}
			}
			else
                SDIO_PRINTF("------- %s, line %d intsts = %08x buf = %08x -------\n", __FUNCTION__, __LINE__, intsts, buf);
		}
	}

	if (!ret) {
		synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts
		synopmob_clear_bits(base + CTRL, CTRL_USE_IDMAC);
		synopmob_clear_bits(base + BMOD,BMOD_DE);
		synopmob_set_register(base+BLKSIZ, 512);
		synopmob_set_register(base+BYTCNT, 512);
	}
	else {
   		char* op = "read";
   		if (rw) 
   			op = "write";
   		
        SDIO_PRINTF("sdio_drv_read_write1(%s) fail:, ret = %d\n", op, ret);
	}
		
	if ( rw && !ret ) { //write
		ret = synopmob_wait_data_ready(base);
	}

	rt_sem_release(sdc->mutex);

	if ( !rw && !ret ) { //read
		inv_dcache_range((unsigned long)buf, num);
	}
	
       if (ret) {
       		char* op = "read";
       		if (rw) 
       			op = "write";
       		
	        SDIO_PRINTF("sdio_drv_read_write2(%s) fail:, ret = %d\n", op, ret);
       }
	return ret;
	//return ret ? 0/*false*/ : 1/*true*/;
}

int sdio_drv_read(HSDC handle, unsigned int addr, unsigned int fn, unsigned int bcnt,
		   unsigned int bsize, unsigned char *buf)
{
	return sdio_drv_read_write((sdc_t*)handle, 0, addr, fn, bcnt, bsize, buf);
}

int sdio_drv_write(HSDC handle, unsigned int addr, unsigned int fn, unsigned int bcnt,
		   unsigned int bsize, unsigned char *buf)
{
	return sdio_drv_read_write((sdc_t*)handle, 1, addr, fn, bcnt, bsize, buf);
}

static void dumpchain(DmaDesc *pChain)
{
    int i = 0;
    DmaDesc *tmp_pChain = pChain;
    
    while(tmp_pChain && i < 10)
    {
        SDIO_PRINTF("[%d]: chain =%p, buf = %p, size = %d, csi = %08x, next = %p\n", i, tmp_pChain, (DmaDesc *)tmp_pChain->desc2, tmp_pChain->desc1, tmp_pChain->desc0, (DmaDesc *)tmp_pChain->desc3);
        tmp_pChain = (DmaDesc *)tmp_pChain->desc3;
        i++;

        if(tmp_pChain == pChain)
            break;
    }
}

#ifdef DONT_COPY_NET_PAYLOAD_TO_SEND
#if 1
int sdio_drv_chain_write(sdc_t* sdc, unsigned int addr, unsigned int fn, unsigned int bcnt, unsigned int bsize, buf_chain_t *chain)
{
	int   ret;	
	unsigned int intsts = 0;
	unsigned int cmd = 0x2275;
	unsigned int base = sdc->ip_base;
	unsigned int arg;
	unsigned int num;
	unsigned int chain_len = 0;
	int   loop_for_command_done_check = DATA_TRANSFER_OVER_TIMEOUT_USEC;	
	rt_err_t err;	
	unsigned int rw = 1;
	DmaDesc *tmpDesc = (DmaDesc *)chain;
	DmaDesc *lastDesc = (void*)0;

	arg = (fn << 28) | (addr << 9);
	if (bcnt == 1 && bsize <= 512)
		arg |= (bsize & 0x1ff);
	else
		arg |= ((1 << 27) | bcnt);	
	if ( rw ) {
		cmd |= 0x400;
		arg |= (1 << 31);
	}
	num = bsize*bcnt;

	err = rt_sem_take(sdc->mutex, RT_WAITING_FOREVER);
	if (err != RT_EOK) {
		return ERRNORES;
	}
	
	// reset
	synopmob_set_bits(base+CTRL, FIFO_RESET); //reset FIFO
	while (synopmob_read_register(base+CTRL) & FIFO_RESET);
    	synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts
	
    while(tmpDesc != 0) {
        // make sure size is little than DescBuf1SizMsk
        if(tmpDesc->desc1 > (DescBuf1SizMsk >> DescBuf1SizeShift)) {
            // TBD... fix me 
            rt_sem_release(sdc->mutex);
            return 0;
        }
        // TBD... fix me, we must align tmpDesc->desc2 to 4 ?
        
        tmpDesc->desc0 = DescOwnByDma | DescSecAddrChained;
        
        // is it last node?
        if(tmpDesc->desc3 == 0 || tmpDesc->desc3 == (unsigned int)chain) {
    		tmpDesc->desc0 |= DescLastDesc;
    		lastDesc = tmpDesc;
        }
        else {
        	tmpDesc->desc0 |= DescDisInt; //disable interrupt...        	
        }
        
        // is it first node?
        if((char *)tmpDesc == (char *)chain) {
    		tmpDesc->desc0 |= DescFirstDesc;
        } 

        flush_dcache_range(tmpDesc->desc2, tmpDesc->desc1);
        
        tmpDesc = (DmaDesc *)tmpDesc->desc3;
        chain_len += sizeof(buf_chain_t);

        if((char *)tmpDesc == (char *)chain) {
        	break;
        }
    }

    lastDesc->desc3 = (unsigned int)chain;

	//FIXME, chain must be continuous arrry.
	flush_dcache_range((unsigned long)chain, chain_len);

	synopmob_set_register(base+DBADDR, (unsigned int)(chain));
    
	synopmob_set_register(base+BLKSIZ, bsize);
	synopmob_set_register(base+BYTCNT, num);
	synopmob_set_bits(base + CTRL, CTRL_USE_IDMAC);
	synopmob_set_bits(base + BMOD,BMOD_DE);
	
	ret = synopmob_execute_command(base, cmd,  arg);
	if ( !ret ) {
		ret = ERRIDMA;
		err = rt_sem_take(sdc->sem, DMA_TRANSFER_TIMEOUT_TICKS);
		if ( !err ) {
			while (--loop_for_command_done_check > 0) {
				intsts = synopmob_read_register(base+RINTSTS);
				if ((intsts & (INTMSK_CMD_DONE|INTMSK_DAT_OVER)) == (INTMSK_CMD_DONE|INTMSK_DAT_OVER)) {
					break;
				}
				plat_loop(1);
			}
			ret = synopmob_handle_standard_rinsts(intsts);
			if (!ret ) {
				if( !loop_for_command_done_check || !(sdc->idsts & 0x100)) { //normal interrupt
					ret = ERRIDMA;
				}
			}
		}
	}

	if (!ret) {
		synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts
		synopmob_clear_bits(base + CTRL, CTRL_USE_IDMAC);
		synopmob_clear_bits(base + BMOD,BMOD_DE);
		synopmob_set_register(base+BLKSIZ, 512);
		synopmob_set_register(base+BYTCNT, 512);
	}
	else {
	   		char* op = "read";
	   		if (rw) 
	   			op = "write";
	   		
	        SDIO_PRINTF("sdio_drv_chain_write1(%s) fail:, ret = %d, bsize = %d * %d\n", op, ret, bsize, bcnt);
	        dumpchain((DmaDesc *)chain);
	}

	if ( rw && !ret ) {
		ret = synopmob_wait_data_ready(base);
	}

	rt_sem_release(sdc->mutex);

	if (ret) {
		ret++;
		ret--;
	        SDIO_PRINTF("sdio_drv_chain_write2, fail:, ret = %d\n", ret);
	}

	return ret;
	//return ret ? 0/*false*/ : 1/*true*/;
}
#elif 0
int sdio_drv_chain_write(sdc_t* sdc, unsigned int addr, unsigned int fn, unsigned int bcnt, unsigned int bsize, buf_chain_t *chain)
{
	//static volatile DmaDesc __attribute__ ((aligned(32))) st_pchain[4];
	volatile DmaDesc *st_pchain = (DmaDesc *)0x9a700000;
		
	int   ret;	
	unsigned int intsts = 0;
	unsigned int cmd = 0x2275;
	unsigned int base = sdc->ip_base;
	unsigned int arg;
	unsigned int num;
	unsigned int chain_len = 0;
	int   loop_for_command_done_check = DATA_TRANSFER_OVER_TIMEOUT_USEC;	
	char err;	
	unsigned int rw = 1;

	buf_chain_t *usrchain;
	unsigned int desc0;
	unsigned int length = 0;

	if (!chain) {
		return 0;
	}

	arg = (fn << 28) | (addr << 9);
	if (bcnt == 1 && bsize <= 512)
		arg |= (bsize & 0x1ff);
	else
		arg |= ((1 << 27) | bcnt);	
	if ( rw ) {
		cmd |= 0x400;
		arg |= (1 << 31);
	}
	num = bsize*bcnt;

	OSSemPend(sdc->mutex, 0, &err);
	if (err != OS_NO_ERR) {
		return ERRNORES;
	}
	
	// reset
	synopmob_set_bits(base+CTRL, FIFO_RESET); //reset FIFO
	while (synopmob_read_register(base+CTRL) & FIFO_RESET);
    	synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts

	usrchain = chain;
    	while (1) {
		if(usrchain->size > (DescBuf1SizMsk >> DescBuf1SizeShift)) {
            		// TBD... fix me 
	            OSSemPost (sdc->mutex);
        	    return 0;
		}
		length += usrchain->size;
    		desc0 = DescOwnByDma | DescSecAddrChained;
    		if (!usrchain->next || usrchain->next == chain) {
    			desc0 |= DescLastDesc;
    		}
		else {
        		desc0 |= DescDisInt; //disable interrupt...        	
		}        

		if(usrchain == chain) {
			desc0 |= DescFirstDesc;
		}

    		st_pchain[chain_len].desc0 = desc0;
		st_pchain[chain_len].desc1 = (unsigned int)usrchain->size;
		st_pchain[chain_len].desc2 = (unsigned int)usrchain->buf;
		st_pchain[chain_len].desc3 = (unsigned int)(&st_pchain[chain_len+1]);
		flush_dcache_range((unsigned int)usrchain->buf, usrchain->size);
		
		usrchain = usrchain->next;
		if( !usrchain || usrchain == chain) {
	        	break;
		}
		if (++chain_len >= 4) {
			while(1) SDIO_PRINTF("sdio_drv_chain_write:long chain!\n");
		}
    	}
	st_pchain[chain_len].desc3 = (unsigned int)(&st_pchain[0]);

	if (length != num) {
		while (1) SDIO_PRINTF("sdio_drv_chain_write:too long packet!\n");
	}

	synopmob_set_register(base+DBADDR, (unsigned int)(st_pchain));
    
	synopmob_set_register(base+BLKSIZ, bsize);
	synopmob_set_register(base+BYTCNT, num);
	synopmob_set_bits(base + CTRL, CTRL_USE_IDMAC);
	synopmob_set_bits(base + BMOD,BMOD_DE);
	
	ret = synopmob_execute_command(base, cmd,  arg);
	if ( !ret ) {
		ret = ERRIDMA;
		OSSemPend(sdc->sem, DMA_TRANSFER_TIMEOUT_TICKS, &err);
		if ( !err ) {
			while (--loop_for_command_done_check > 0) {
				intsts = synopmob_read_register(base+RINTSTS);
				if ((intsts & (INTMSK_CMD_DONE|INTMSK_DAT_OVER)) == (INTMSK_CMD_DONE|INTMSK_DAT_OVER)) {
					break;
				}
				plat_loop(1);
			}
			ret = synopmob_handle_standard_rinsts(intsts);
			if (!ret ) {
				if( !loop_for_command_done_check || !(sdc->idsts & 0x100)) { //normal interrupt
					ret = ERRIDMA;
				}
			}
		}
	}

	if (!ret) {
		synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts
		synopmob_clear_bits(base + CTRL, CTRL_USE_IDMAC);
		synopmob_clear_bits(base + BMOD,BMOD_DE);
		synopmob_set_register(base+BLKSIZ, 512);
		synopmob_set_register(base+BYTCNT, 512);
	}
	else {
	   	char* op = "read";
	   	if (rw) 
	   		op = "write";
	   		
	        SDIO_PRINTF("sdio_drv_chain_write1(%s) fail:, ret = %d\n", op, ret);
	}

	if ( rw && !ret ) {
		ret = synopmob_wait_data_ready(base);
	}

	OSSemPost (sdc->mutex);

	return ret;
	//return ret ? 0/*false*/ : 1/*true*/;
}
#else
static unsigned char __attribute__ ((aligned(32))) st_net_buf[2*1024];
int sdio_drv_chain_write(sdc_t* sdc, unsigned int addr, unsigned int fn, unsigned int bcnt, unsigned int bsize, buf_chain_t *chain)
{
	static volatile DmaDesc __attribute__ ((aligned(32))) st_pchain;
		
	int   ret;	
	unsigned int intsts = 0;
	unsigned int cmd = 0x2275;
	unsigned int base = sdc->ip_base;
	unsigned int arg;
	unsigned int num;
	int   loop_for_command_done_check = DATA_TRANSFER_OVER_TIMEOUT_USEC;	
	rt_err_t err;	
	unsigned int rw = 1;

	buf_chain_t *usrchain;
	unsigned int length = 0;

	if (!chain) {
		return 0;
	}

	arg = (fn << 28) | (addr << 9);
	if (bcnt == 1 && bsize <= 512)
		arg |= (bsize & 0x1ff);
	else
		arg |= ((1 << 27) | bcnt);	
	if ( rw ) {
		cmd |= 0x400;
		arg |= (1 << 31);
	}
	num = bsize*bcnt;

	err = rt_sem_take(sdc->mutex, RT_WAITING_FOREVER);
	if (err != RT_EOK) {
		return ERRNORES;
	}
	
	
	// reset
	synopmob_set_bits(base+CTRL, FIFO_RESET); //reset FIFO
	while (synopmob_read_register(base+CTRL) & FIFO_RESET);
    	synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts

	usrchain = chain;
    	while (1) {    		
    		if (length + usrchain->size >= sizeof(st_net_buf)) {
    			while(1) SDIO_PRINTF("too long net pkt\n");
    		}
    		
    		memcpy(st_net_buf + length, usrchain->buf, usrchain->size);
    		length += usrchain->size;
    		usrchain = usrchain->next;
    		if (!usrchain || usrchain->next == chain) {
    			break;
    		}
    	}
    	
    	st_pchain.desc0 = DescOwnByDma | DescSecAddrChained | DescLastDesc | DescFirstDesc;
    	st_pchain.desc1 = length;
    	st_pchain.desc2 = (unsigned int)st_net_buf;
 	st_pchain.desc3 = (unsigned int)&st_pchain;
	flush_dcache_range((unsigned long)st_net_buf, length);	
	
	if (length != num) {
		while (1) SDIO_PRINTF("sdio_drv_chain_write:too long packet!\n");
	}

	synopmob_set_register(base+DBADDR, (unsigned int)(&st_pchain));
    
	synopmob_set_register(base+BLKSIZ, bsize);
	synopmob_set_register(base+BYTCNT, num);
	synopmob_set_bits(base + CTRL, CTRL_USE_IDMAC);
	synopmob_set_bits(base + BMOD,BMOD_DE);
	
	ret = synopmob_execute_command(base, cmd,  arg);
	if ( !ret ) {
		ret = ERRIDMA;
		err = rt_sem_take(sdc->sem, DMA_TRANSFER_TIMEOUT_TICKS);
		if ( !err ) {
			while (--loop_for_command_done_check > 0) {
				intsts = synopmob_read_register(base+RINTSTS);
				if ((intsts & (INTMSK_CMD_DONE|INTMSK_DAT_OVER)) == (INTMSK_CMD_DONE|INTMSK_DAT_OVER)) {
					break;
				}
				plat_loop(1);
			}
			ret = synopmob_handle_standard_rinsts(intsts);
			if (!ret ) {
				if( !loop_for_command_done_check || !(sdc->idsts & 0x100)) { //normal interrupt
					ret = ERRIDMA;
				}
			}
		}
	}

	if (!ret) {
		synopmob_set_register(base + RINTSTS, 0xfffe); //clear interrupts
		synopmob_clear_bits(base + CTRL, CTRL_USE_IDMAC);
		synopmob_clear_bits(base + BMOD,BMOD_DE);
		synopmob_set_register(base+BLKSIZ, 512);
		synopmob_set_register(base+BYTCNT, 512);
	}
	else {
	   	char* op = "read";
	   	if (rw) 
	   		op = "write";
	   		
	        SDIO_PRINTF("sdio_drv_chain_write1(%s) fail:, ret = %d\n", op, ret);
	}

	if ( rw && !ret ) {
		ret = synopmob_wait_data_ready(base);
	}

	rt_sem_release(sdc->mutex);

	return ret;
	//return ret ? 0/*false*/ : 1/*true*/;
}
#endif
#endif

static int sdio_card_reset(sdc_t* sdc)
{
	unsigned int resp;
	int ret;

	/* Soft Reset card */
    sdio_drv_creg_write(sdc, 0x6, 0, 0x8, &resp);

	return 0;
}

static int enum_sdio_card(sdc_t* sdc)
{
	int ret;
	unsigned int resp;
	unsigned int base = sdc->ip_base;

	#if 0
	synopmob_set_bits(0x98500004, (1<<24)); //set to output mode
	synopmob_set_bits(0x98500000, (1<<24)); //power off
	plat_loop(1000000/5); //Lets give some ramp down period
	synopmob_clear_bits(0x98500000, (1<<24)); //power on
	plat_loop(1000000/5);//Lets give some ramp down period
	#endif

	synopmob_set_register(base+CTYPE, ONE_BIT_MODE);

	synopmob_set_register(base+CLKENA, 0x00000001); /*enable clock, non-low-power mode*/
	ret = synopmob_set_clk_freq(sdc, MMC_FOD_DIVIDER_VALUE);
	
	if ( !ret ) {
		plat_loop(100); //enough for 74 clock.	
		#if 0
		sdio_card_reset(sdc);
		plat_loop(100000);
		#endif
		ret = sd_send_cmd5(sdc, 0, &resp);
		if (!ret) {
			resp &= 0x00ffffff;
			ret = sd_send_cmd5(sdc, resp, &resp);
		}
	}

	if (!ret) {
		ret = sd_send_cmd3(sdc); //get RCA
	}
	
	if (!ret) {
		ret = sd_send_cmd7(sdc); //select the card
	}


	if (!g_use_bcm43362)
	{
	sdio_drv_creg_read(sdc, 0x13, 0, &resp);
	if ((resp & 1) && (sdc->wkmod & (SDC_WKMOD_4WIRE|SDC_WKMOD_25M_STAND_SPEED|SDC_WKMOD_50M_HI_SPEED))){ //high speed support?
		if (sdc->wkmod & SDC_WKMOD_4WIRE) {
			sdio_drv_creg_read(sdc, 0x7, 0, &resp);
			resp &= 0xfc;
			resp |= (1 << 1);
			sdio_drv_creg_write(sdc, 0x7, 0, resp, &resp); //switch to 4bit mode
			sdio_drv_creg_read(sdc, 0x7, 0, &resp);
			if ((resp & 0x3) != 0x2) {
				return  ERRCARDINTERNAL; // 4bit mode failed
			}
			synopmob_set_register(base+CTYPE, FOUR_BIT_MODE);
		}
		if (sdc->wkmod & (SDC_WKMOD_25M_STAND_SPEED|SDC_WKMOD_50M_HI_SPEED)) {
			ret = synopmob_set_clk_freq(sdc, ONE_BIT_BUS_FREQ);
			//ret = synopmob_set_clk_freq(sdc, 0);
		}
	}

	sdio_drv_creg_read(sdc, 0x3, 0, &resp); 
	if (!ret) {
		sdio_drv_creg_read(sdc, 0x0, 0, &resp); //card version
		sdio_drv_creg_write(sdc, 0x4, 0, 0x3, &resp); //enable interrupts in card
		sdio_drv_creg_write(sdc, 0x2, 0, 0x2, &resp); //Eable IO in card
		do {
			sdio_drv_creg_read(sdc, 0x3, 0, &resp); 
		} while (!(resp & 2));
	}
	} //g_use_bcm43362

	sdc->card_type = SDIO_TYPE;

	synopmob_set_bits(base+CTRL, INT_ENABLE);
	
	return ret;
}

int sdio_high_speed_mode(HSDC handle, int bitwidth, int freq)
{
	int ret;
	sdc_t* sdc = (sdc_t*)handle;

	if (bitwidth == 4)
	{
		synopmob_set_register(sdc->ip_base+CTYPE, FOUR_BIT_MODE);
	}

	ret = synopmob_set_clk_freq(sdc, /*ONE_BIT_BUS_FREQ*/1);
	if (ret != 0)
	{
		SDIO_PRINTF("sdio_high_speed_mode fail:, ret = %d\n", ret);
	}

	return ret;
}

static int common_init(unsigned int which, unsigned int sdio, unsigned int wkmod, unsigned int* dma_desc, HSDC* phandle)
{
	int    ret = ERRNORES;
	sdc_t* sdc;
	unsigned int  base;
	unsigned int  temp;
	unsigned int  fifo_thresh;
	volatile DmaDesc *pDmaDesc;
	rt_sem_t sem;
	rt_sem_t mutex;
	
	base = SDC0_REG_BASE;
	temp = PMU_SDC0_RST_BIT;
	if (which > 0) {
		base = SDC1_REG_BASE;
		temp = PMU_SDC1_RST_BIT;
	}
	
#if 0
	//PMU_RST_MODULE(temp); plat_loop(1);
	temp = synopmob_read_register(PMU_REG_CLK_DIV3);
	temp &= (~(0x0f<<8));
	temp |= (0xf<<8);
	synopmob_set_register(PMU_REG_CLK_DIV3, temp);
#endif
	*phandle = (HSDC)0;
	
	sdc = &sdc_array[which];
	sem = sdc->sem;
	mutex = sdc->mutex;
	memset((void *)sdc, 0, sizeof(*sdc));
	sdc->wkmod = wkmod;
	sdc->idma_support = 0;
	sdc->ip_base = base;
	sdc->rca = 0;
	sdc->card_type = NONE_TYPE;
	if (!sem) {
		sem = rt_sem_create("fh_sdio_sem", 0, RT_IPC_FLAG_PRIO);//OSSemCreate (0);
		if ( !sem ) {
			return ret;
		}
	}
	sdc->sem = sem;

	if (!mutex) {
		mutex = rt_sem_create("fh_sdio_mutex", 1, RT_IPC_FLAG_PRIO);//OSSemCreate (1);
		if ( !mutex ) {
			return ret;
		}
	}
	sdc->mutex = mutex;
	
	synopmob_set_bits(base + CTRL, CTRL_RESET); //reset host controller
	plat_loop(100);

	synopmob_clear_bits(base + CTRL,CTRL_USE_IDMAC);
	sdc->idma_support = 1; //fixed to support IDMA

	pDmaDesc = (volatile DmaDesc *)dma_desc;
	sdc->pDmaDesc = pDmaDesc;
	if (sdc->idma_support) {
		synopmob_set_bits(base + CTRL, DMA_RESET);
		plat_loop(100);
		synopmob_set_bits(base + CTRL, FIFO_RESET);
		plat_loop(100);
		synopmob_set_bits(base + BMOD, BMOD_SWR);
		plat_loop(100);
		
		//synopmob_set_bits(base + BMOD,BMOD_DE);		
		pDmaDesc->desc0 = DescSecAddrChained;
		pDmaDesc->desc1 = 0;
		pDmaDesc->desc2 = 0;
		pDmaDesc->desc3 = (unsigned int)(pDmaDesc);
		synopmob_set_register(base + DBADDR, (unsigned int)(pDmaDesc));
	}

	synopmob_set_register(base+CTYPE, ONE_BIT_MODE);

	synopmob_set_register(base+RINTSTS, 0xffffffff);//clear interrupt.
	synopmob_clear_bits(base+CTRL, INT_ENABLE);
	synopmob_set_register(base+INTMSK, 0); // mask all INTR
	synopmob_set_register(base+IDINTEN, IDMAINTBITS); //Enable DMA INTR


	synopmob_set_register(base+TMOUT, 0xffffffff); /* Set Data and Response timeout to Maximum Value*/

	/* Set the card Debounce to allow the CDETECT fluctuations to settle down*/	
	synopmob_set_register(base+DEBNCE, 0x0FFFFF);

	fifo_thresh = synopmob_read_register(base+FIFOTH);
	//fifo_thresh = GET_FIFO_DEPTH(fifo_thresh) / 2;
	fifo_thresh = (GET_FIFO_DEPTH(fifo_thresh) + 1) / 2;
	sdc->fifo_depth = fifo_thresh * 2;	
	sdc->fifo_threth = fifo_thresh;
	/* Tx Watermark */
	synopmob_clear_bits(base+FIFOTH, 0xfff);
	synopmob_set_bits(base+FIFOTH, fifo_thresh);
	/* Rx Watermark */
	synopmob_clear_bits(base+FIFOTH, 0x0fff0000);
	synopmob_set_bits(base+FIFOTH, (fifo_thresh-1) << 16);
	//synopmob_set_bits(base+FIFOTH, 2<< 28);

	if (!sdio) {
		ret = enum_sd_card(sdc);
	}
	else {
		ret = enum_sdio_card(sdc);
	}

	if (!ret) {
		*phandle = (HSDC)sdc;
	}

	return ret;
}

int sdc_is_connected(unsigned int which)
{
	unsigned int base = SDC0_REG_BASE;
	
	if (which > 0)
		base = SDC1_REG_BASE;

	return !(synopmob_read_register(base+CDETECT) & 1);
}

int sdc_init(unsigned int which, unsigned int wkmod, unsigned int* dma_desc, HSDC* phandle)
{
	return common_init(which, 0, wkmod, dma_desc, phandle);
}

int sdio_init(unsigned int which, unsigned int wkmod, unsigned int* dma_desc, HSDC* phandle)
{
	return common_init(which, 1, wkmod, dma_desc, phandle);
}

int sdio_enable_card_int(HSDC handle, int enable)
{
	unsigned int base = ((sdc_t*)handle)->ip_base;

	if (enable) {
		//synopmob_set_register(base+INTMSK, INTMSK_SDIO);
		synopmob_set_register(base+INTMSK, (synopmob_read_register(base+INTMSK) | INTMSK_SDIO ));
	}
	else {
		//synopmob_set_register(base+INTMSK, 0);
		synopmob_set_register(base+INTMSK, (synopmob_read_register(base+INTMSK) & ~INTMSK_SDIO ));
	}

	return 0;
}

int sdio_set_card_int_cb(HSDC handle, void (*cb)(void))
{
	((sdc_t*)handle)->cb = cb;

	return 0;
}

static void OSSDCISR(sdc_t* sdc)
{
	unsigned int sts;
	unsigned int base;

	base = sdc->ip_base;
	sts = synopmob_read_register(base+IDSTS);
	if ( sts ) {
		synopmob_set_register(base+IDSTS, sts);
		sdc->idsts = sts;
		rt_sem_release(sdc->sem);
	}

	//sts = synopmob_read_register(base+RINTSTS);
	sts = synopmob_read_register(base+MINTSTS);
	sts &= INTMSK_SDIO;
	if ( sts ) { //interrupt from WIFI card.
		//synopmob_set_register(base+INTMSK, 0); //mask all the interrupt	
		synopmob_set_register(base+INTMSK, synopmob_read_register(base+INTMSK) & ~INTMSK_SDIO ); //mask sdio interrupt	
		synopmob_set_register(base+RINTSTS, sts);
		synopmob_set_register(base+MINTSTS, sts);
		if (sdc->cb) {
			sdc->cb();
		}
	}
}

void OSSDCINTR_0(int vector, void *param)
{
	OSSDCISR(&sdc_array[0]);
}

void OSSDCINTR_1(int vector, void *param)
{
	OSSDCISR(&sdc_array[1]);
}

void fh_sdio0_init(void)
{
    int sd0_irq = SDC0_IRQn;
    
    rt_hw_interrupt_install(sd0_irq, OSSDCINTR_0, NULL, NULL);
    rt_hw_interrupt_umask(sd0_irq);
}

void fh_sdio1_init(void)
{
    int sd1_irq = SDC1_IRQn;
    
    rt_hw_interrupt_install(sd1_irq, OSSDCINTR_1, NULL, NULL);
    rt_hw_interrupt_umask(sd1_irq);
}

void fh_sdio_init(void)
{
    fh_sdio0_init();
    fh_sdio1_init();
}

int sdc_deinit(HSDC handle)
{
	return -1;  // TBD... fix me
}

int sdc_set_clk_divider(unsigned int divider)
{
    if(divider > 255)
        return -1;
    
    sdc_clk_divider = divider;
    return 0;
}

