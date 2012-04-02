/*
 * File      : rtthread.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-10-13     prife        the first version 
 * 2012-03-11     prife        use mtd device interface
*/

#include <rtdevice.h>
#include <s3c24x0.h>
//#include "nand.h"
//  For flash chip that is bigger than 32 MB, we need to have 4 step address
//  
#define NFCONF_INIT			0xF830  // 512-byte 4 Step Address
#define NEED_EXT_ADDR			1
//#define NFCONF_INIT			0xA830  // 256-byte 4 Step Address
//#define NEED_EXT_ADDR			0

//#define NFCONF_INIT			0xF840
//  NAND Flash Command. This appears to be generic across all NAND flash chips
#define CMD_READ			0x00	//  Read
#define CMD_READ1			0x01	//  Read1
#define CMD_READ2			0x50	//  Read2
#define CMD_READ3			0x30	//  Read3
#define CMD_READID			0x90	//  ReadID
#define CMD_WRITE1			0x80	//  Write phase 1
#define CMD_WRITE2			0x10	//  Write phase 2
#define CMD_ERASE1			0x60	//  Erase phase 1
#define CMD_ERASE2			0xd0	//  Erase phase 2
#define CMD_STATUS			0x70	//  Status read
#define CMD_RESET			0xff	//  Reset
#define CMD_RANDOMREAD1     0x05    //  random read	 phase 1
#define CMD_RANDOMREAD2     0xE0    //	random read	 phase 2
#define CMD_RANDOMWRITE     0x85    //	random write phase 1

#define NF_CMD(cmd)			{NFCMD  = (cmd); }
#define NF_ADDR(addr)		{NFADDR = (addr); }	
#define NF_nFCE_L()			{NFCONT &= ~(1<<1); }
#define NF_nFCE_H()			{NFCONT |= (1<<1); }
#define NF_RSTECC()			{NFCONT |= (1<<4); }
#define NF_RDMECC()			(NFMECC0 )
#define NF_RDSECC()			(NFSECC )
#define NF_RDDATA()			(NFDATA)
#define NF_RDDATA8()		(NFDATA8)
#define NF_WRDATA(data)		{NFDATA = (data); }
#define NF_WRDATA8(data)	{NFDATA8 = (data); } 
#define NF_WAITRB()			{while(!(NFSTAT&(1<<0)));} 
#define NF_CLEAR_RB()		{NFSTAT |= (1<<2); }
#define NF_DETECT_RB()		{while(!(NFSTAT&(1<<2)));}
#define NF_MECC_UnLock()	{NFCONT &= ~(1<<5); }
#define NF_MECC_Lock()		{NFCONT |= (1<<5); }
#define NF_SECC_UnLock()	{NFCONT &= ~(1<<6); }
#define NF_SECC_Lock()		{NFCONT |= (1<<6); }

#define	RdNFDat8()			(NFDATA8)	//byte access
#define	RdNFDat()			RdNFDat8()	//for 8 bit nand flash, use byte access
#define	WrNFDat8(dat)		(NFDATA8 = (dat))	//byte access
#define	WrNFDat(dat)		WrNFDat8()	//for 8 bit nand flash, use byte access

#define NF_CE_L()			NF_nFCE_L()
#define NF_CE_H()			NF_nFCE_H()
#define NF_DATA_R()			NFDATA
#define NF_ECC()			NFECC0


// HCLK=100Mhz
#define TACLS				1	// 1-clk(0ns) 
#define TWRPH0				4	// 3-clk(25ns)
#define TWRPH1				0	// 1-clk(10ns)  //TACLS+TWRPH0+TWRPH1>=50ns

//  Status bit pattern
#define STATUS_READY            0x40        //  Ready
#define STATUS_ERROR            0x01        //  Error
#define	STATUS_ILLACC			0x08		//	Illigar Access
//
// ERROR_Xxx
//
#define ERR_SUCCESS						0
#define ERR_DISK_OP_FAIL1				1
#define ERR_DISK_OP_FAIL2				2
#define ERR_INVALID_BOOT_SECTOR			3
#define ERR_INVALID_LOAD_ADDR			4
#define ERR_GEN_FAILURE					5
#define ERR_INVALID_PARAMETER			6
#define ERR_JUMP_FAILED					7
#define ERR_INVALID_TOC					8
#define ERR_INVALID_FILE_TYPE			9

//#define NF_READID   1
#define READ_SECTOR_INFO		


#define NAND_BASE 0xB0E00000
#define IOP_BASE  0xB1600000

#define PAGE_DATA_SIZE  2048
static struct rt_mutex nand;

/*
 * In a page, data's ecc code is stored in spare area, spare BYTE0 to BYTEE 3
 * block's status byte which indicate a block is bad is BYTE4 in spare area
 */
static void nand_hw_init(void)
{
	/* Init GPIO£¬ nFWE£¬ALE£¬CLE£¬nFCE£¬nFRE */
	GPACON |= (1<<17) | (1<<18) | (1<<19) | (1<<20) | (1<<22);

	/* Enable PCLK into nand Controller */
	CLKCON |= 1 << 4;

	NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4)|(0<<0);
	NFCONT = (0<<13)|(0<<12)|(0<<10)|(0<<9)|(0<<8)|(1<<6)|(1<<5)|(1<<4)|(1<<1)|(1<<0);
	NFSTAT = 0;

	/* reset nand flash */
	NF_CE_L();
	NF_CLEAR_RB();
	NF_CMD(CMD_RESET);
	NF_DETECT_RB();
	NF_CE_H();
}

static rt_err_t k9f1g08_mtd_erase_block(
		struct rt_mtd_nand_device* device,
		rt_uint32_t block)
{
	/* 1 block = 64 page= 2^6*/
    rt_err_t result = RT_EOK;
	block <<= 6; /* get the first page's address in this block*/

	rt_mutex_take(&nand, RT_WAITING_FOREVER);
	NF_nFCE_L();  /* enable chip */
	NF_CLEAR_RB();
	
	NF_CMD(CMD_ERASE1);	/* Erase one block 1st command */
	NF_ADDR(block & 0xff);
	NF_ADDR((block >> 8) & 0xff);
//	NF_ADDR((block >> 16) & 0xff);
	NF_CMD(CMD_ERASE2);	

	NF_DETECT_RB(); /* Wait for ready bit */

	if ( NFSTAT & STATUS_ILLACC )
	{
		NFSTAT |= STATUS_ILLACC; /* Write 1 to clear.*/
        result = -RT_ERROR;
	} else {
		
		NF_CMD(CMD_STATUS);	/* Check the status	*/

		if (NF_DATA_R() & STATUS_ERROR) {
			result = -RT_ERROR;
		}
	}

	NF_nFCE_H();
	rt_mutex_release(&nand);
	return result;
/* TODO: more check about status */
}

/* return 0, ecc ok, 1, can be fixed , -1 can not be fixed */
static rt_err_t k9f1g08_mtd_read(
		struct rt_mtd_nand_device * dev,
		rt_off_t page,
		rt_uint8_t * data, rt_uint32_t data_len, //may not always be 2048
		rt_uint8_t * spare, rt_uint32_t spare_len)
{
	rt_uint32_t i;
 	rt_uint32_t mecc;
	rt_uint32_t status;
	rt_err_t result;
	
	rt_mutex_take(&nand, RT_WAITING_FOREVER);

	NF_RSTECC();   /* reset ECC*/
	NF_MECC_UnLock();/* unlock MECC */

	NF_nFCE_L(); /* enable chip */

	if (data != RT_NULL && data_len != 0)
	{
		/* read page data area */
		NF_CLEAR_RB();

		NF_CMD(CMD_READ);
		NF_ADDR(0);
		NF_ADDR(0);
		NF_ADDR((page) & 0xff);
		NF_ADDR((page >> 8) & 0xff);
//		NF_ADDR((page >> 16) & 0xff);
		NF_CMD(CMD_READ3);

		NF_DETECT_RB();/* Wait for RB	*/

		/*TODO: use a more quick method */
		for (i = 0; i < data_len; i++)
			data[i] = NF_RDDATA8();

		NF_MECC_Lock();

		/* if read whole page data, then check ecc status */
		if (data_len == PAGE_DATA_SIZE)
		{
			mecc = NF_RDDATA();

			NFMECCD0 = ((mecc&0xff00)<<8)|(mecc&0xff);
			NFMECCD1 = ((mecc&0xff000000)>>8)|((mecc&0xff0000)>>16);

			/* check data ecc */
			status = NFESTAT0 & 0x03;
			if (status == 0x00)
				result = RT_EOK; /* no error */
			else if (status == 0x01)
				result = -1;/* error can be fixed */
			else
				result = -2; /* erroe can't be fixed */
		}
		else
			result = RT_EOK;

	}

	if (spare != RT_NULL && spare_len != 0)
	{
		/* read page spare area */

		NF_CLEAR_RB();

		NF_CMD(CMD_READ);
		NF_ADDR(PAGE_DATA_SIZE);
		NF_ADDR((PAGE_DATA_SIZE >> 8) & 0xff);
		NF_ADDR((page) & 0xff);
		NF_ADDR((page >> 8) & 0xff);
//		NF_ADDR((page >> 16) & 0xff);
		NF_CMD(CMD_READ3);

		NF_DETECT_RB();/* Wait for RB	*/
		/*TODO: use a more quick method */
		for (i = 0; i < spare_len; i++)
			spare[i] = NF_RDDATA8();

		NF_MECC_Lock();

		result = RT_EOK;
	}
	NF_nFCE_H();
	rt_mutex_release(&nand);
	return result;
}

static rt_err_t k9f1g08_mtd_write (
		struct rt_mtd_nand_device * dev,
		rt_off_t page,
		const rt_uint8_t * data, rt_uint32_t data_len,//will be 2048 always!
		const rt_uint8_t * spare, rt_uint32_t spare_len)
{
	rt_uint32_t i;
	rt_uint32_t mecc0;
	rt_err_t result = RT_EOK;
	rt_uint8_t ecc_data[4];

	rt_mutex_take(&nand, RT_WAITING_FOREVER);

	NF_nFCE_L();       /* enable chip */

	NF_RSTECC();
	NF_MECC_UnLock();

	if (data != RT_NULL && data_len != 0)
	{
		RT_ASSERT(data_len == PAGE_DATA_SIZE);

		NF_CLEAR_RB();     /* clear RB */
		NF_CMD(CMD_WRITE1);

		NF_ADDR(0);
		NF_ADDR(0);
		NF_ADDR( page & 0xff);
		NF_ADDR((page >> 8) & 0xff);
//		NF_ADDR((page >> 16) & 0xff);

		for(i=0; i<PAGE_DATA_SIZE; i++) //PAGE_DATA_SIZE
			NF_WRDATA8(data[i]);

		NF_MECC_Lock();

		/* produce HARDWARE ECC */
		mecc0=NFMECC0;
		ecc_data[0]=(rt_uint8_t)(mecc0 & 0xff);
		ecc_data[1]=(rt_uint8_t)((mecc0 >> 8) & 0xff);
		ecc_data[2]=(rt_uint8_t)((mecc0 >> 16) & 0xff);
		ecc_data[3]=(rt_uint8_t)((mecc0 >> 24) & 0xff);

		/* write ecc to spare[0]..[3] */
		for(i=0; i<4; i++)
			NF_WRDATA8(ecc_data[i]);

		NF_CMD(CMD_WRITE2);
		NF_DETECT_RB();	 	/* Wait for RB	*/
		if (NFSTAT & STATUS_ILLACC)
		{
			NFSTAT |= STATUS_ILLACC;
			result = -RT_ERROR;
			goto __ret;
		}
		else
		{
			NF_CMD(CMD_STATUS);
			if (NF_DATA_R() & STATUS_ERROR)
			{
				result = -RT_ERROR;
				goto __ret;
			}
		}
	}

	if (spare != RT_NULL && spare_len != 0)
	{
		NF_CLEAR_RB();
		NF_CMD(CMD_WRITE1);

		NF_ADDR(PAGE_DATA_SIZE);
		NF_ADDR((PAGE_DATA_SIZE >> 8) & 0xff);
		NF_ADDR( page & 0xff);
		NF_ADDR((page >> 8) & 0xff);
//		NF_ADDR((page >> 16) & 0xff);

		for(i=0; i<spare_len; i++)
			NF_WRDATA8(spare[i]);

		NF_CMD(CMD_WRITE2);
		NF_DETECT_RB();
		if (NFSTAT & STATUS_ILLACC)
		{
			NFSTAT |= STATUS_ILLACC;
			result = -RT_ERROR;
			goto __ret;
		}
		else
		{
			NF_CMD(CMD_STATUS);
			if (NF_DATA_R() & STATUS_ERROR)
			{
				result = -RT_ERROR;
				goto __ret;
			}
		}
	}

__ret:
	NF_nFCE_H(); /* disable chip */
	rt_mutex_release(&nand);
	return result;
}

static rt_err_t k9f1g08_read_id(
		struct rt_mtd_nand_device * dev)
{
	return RT_EOK;
}

const static struct rt_mtd_nand_driver_ops k9f1g08_mtd_ops =
{
	k9f1g08_read_id,
	k9f1g08_mtd_read,
	k9f1g08_mtd_write,
	k9f1g08_mtd_erase_block,
};

/* interface of nand and rt-thread device */
static struct rt_mtd_nand_device nand_part[4];

void k9f1g08_mtd_init()
{
	/* initialize nand controller of S3C2440 */
	nand_hw_init();

    /* initialize mutex */
	if (rt_mutex_init(&nand, "nand", RT_IPC_FLAG_FIFO) != RT_EOK)
	{
		rt_kprintf("init nand lock mutex failed\n");
	}
	/* the first partition of nand */
	nand_part[0].page_size = PAGE_DATA_SIZE;
	nand_part[0].block_size = PAGE_DATA_SIZE*64;//don't caculate oob size
	nand_part[0].block_start = 0;
	nand_part[0].block_end = 255;
	nand_part[0].oob_size = 64;
	nand_part[0].ops = &k9f1g08_mtd_ops;
	rt_mtd_nand_register_device("nand0", &nand_part[0]);

	/* the second partition of nand */
	nand_part[1].page_size = PAGE_DATA_SIZE;
	nand_part[1].block_size = PAGE_DATA_SIZE*64;//don't caculate oob size
	nand_part[1].block_start = 256;
	nand_part[1].block_end = 512-1;
	nand_part[1].oob_size = 64;
	nand_part[1].ops = &k9f1g08_mtd_ops;
	rt_mtd_nand_register_device("nand1", &nand_part[1]);

	/* the third partition of nand */
	nand_part[2].page_size = PAGE_DATA_SIZE;
	nand_part[2].block_size = PAGE_DATA_SIZE*64;//don't caculate oob size
	nand_part[2].block_start = 512;
	nand_part[2].block_end = 512+256-1;
	nand_part[2].oob_size = 64;
	nand_part[2].ops = &k9f1g08_mtd_ops;
	rt_mtd_nand_register_device("nand2", &nand_part[2]);

	/* the 4th partition of nand */
	nand_part[3].page_size = PAGE_DATA_SIZE;
	nand_part[3].block_size = PAGE_DATA_SIZE*64;//don't caculate oob size
	nand_part[3].block_start = 512+256;
	nand_part[3].block_end = 1024-1;
	nand_part[3].oob_size = 64;
	nand_part[3].ops = &k9f1g08_mtd_ops;
	rt_mtd_nand_register_device("nand3", &nand_part[3]);
}

#include "finsh.h"
static char buf[PAGE_DATA_SIZE+64];
static char spare[64];

void nand_erase(int start, int end)
{
	int page;
	for(; start <= end; start ++)
	{
		page = start * 64;
		rt_memset(buf, 0, PAGE_DATA_SIZE);
		rt_memset(spare, 0, 64);

		k9f1g08_mtd_erase_block(RT_NULL, start);

		k9f1g08_mtd_read(RT_NULL, page, buf, PAGE_DATA_SIZE, spare, 64);
		if (spare[0] != 0xFF)
		{
			rt_kprintf("block %d is bad, mark it bad\n", start);

			//rt_memset(spare, 0xFF, 64);
			if (spare[4] == 0xFF)
			{
				spare[4] = 0x00;
				k9f1g08_mtd_write(RT_NULL, page, RT_NULL, 0, spare, 64);
			}
		}
	}
}

int nand_read(int page)
{
	int i;
	int res;
	rt_memset(buf, 0, sizeof(buf));
//	rt_memset(spare, 0, 64);

//	res = k9f1g08_mtd_read(RT_NULL, page, buf, PAGE_DATA_SIZE, spare, 64);
	res = k9f1g08_mtd_read(RT_NULL, page, buf, PAGE_DATA_SIZE+64, RT_NULL, 0);
	rt_kprintf("block=%d, page=%d\n", page/64, page%64);
	for(i=0; i<PAGE_DATA_SIZE; i++)
	{
		rt_kprintf("%02x ", buf[i]);
		if((i+1)%16 == 0)
			rt_kprintf("\n");
	}

	rt_kprintf("spare:\n");
	for(i=0; i<64; i++)
	{
//		rt_kprintf("%02x ", spare[i]);
		rt_kprintf("%02x ", buf[2048+i]);
		if((i+1)%8 == 0)
			rt_kprintf("\n");
	}
	return res;
}
int nand_write(int page)
{
	int i;
	rt_memset(buf, 0, PAGE_DATA_SIZE);
	for(i=0; i<PAGE_DATA_SIZE; i++)
		buf[i] = (i % 2) + i / 2;
	return k9f1g08_mtd_write(RT_NULL, page, buf, PAGE_DATA_SIZE, RT_NULL, 0);
}

int nand_read2(int page)
{
	int i;
	int res;
	rt_memset(buf, 0, sizeof(buf));

	res = k9f1g08_mtd_read(RT_NULL, page, buf, PAGE_DATA_SIZE, RT_NULL, 0);
	rt_kprintf("block=%d, page=%d\n", page/64, page%64);
	for(i=0; i<PAGE_DATA_SIZE; i++)
	{
		rt_kprintf("%02x ", buf[i]);
		if((i+1)%16 == 0)
			rt_kprintf("\n");
	}

	rt_memset(spare, 0, 64);
	res = k9f1g08_mtd_read(RT_NULL, page, RT_NULL, 0, spare, 64);
	rt_kprintf("spare:\n");
	for(i=0; i<64; i++)
	{
		rt_kprintf("%02x ", spare[i]);
		if((i+1)%8 == 0)
			rt_kprintf("\n");
	}
	return res;
}
int nand_read3(int page)
{
	int i;
	int res;
	rt_memset(buf, 0, sizeof(buf));
	rt_memset(spare, 0, 64);

	res = k9f1g08_mtd_read(RT_NULL, page, buf, PAGE_DATA_SIZE, spare, 64);
	rt_kprintf("block=%d, page=%d\n", page/64, page%64);
	for(i=0; i<PAGE_DATA_SIZE; i++)
	{
		rt_kprintf("%02x ", buf[i]);
		if((i+1)%16 == 0)
			rt_kprintf("\n");
	}

	rt_kprintf("spare:\n");
	for(i=0; i<64; i++)
	{
		rt_kprintf("%02x ", spare[i]);
		if((i+1)%8 == 0)
			rt_kprintf("\n");
	}
	return res;
}
FINSH_FUNCTION_EXPORT(nand_read, nand_read(1).);
FINSH_FUNCTION_EXPORT(nand_read2, nand_read(1).);
FINSH_FUNCTION_EXPORT(nand_read3, nand_read(1).);
FINSH_FUNCTION_EXPORT(nand_write, nand_write(1).);
FINSH_FUNCTION_EXPORT(nand_erase, nand_erase(100, 200). erase block in nand);
