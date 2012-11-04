#include <rtdevice.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dfs_def.h>

// #define NAND_TRACE		rt_kprintf
#define NAND_TRACE(...)

#define NAND_SIM  "nand.bin"

struct nand_device
{
	struct rt_mtd_nand_device parent;
	FILE * file;
};
static struct nand_device _nand;

#define NAND_DEVICE(device) 		(( struct nand_device*)(device))

#define PAGE_DATA_SIZE                2048  /* page data size in bytes */
#define PAGE_SPARE_SIZE               64    /* oob size in bytes */
#define BLOCK_PAGES                   64    /* the number of pages in a block */
#define BLOCK_SIZE                    ((PAGE_DATA_SIZE + PAGE_SPARE_SIZE) * BLOCK_PAGES)

#define BLOCK_COUNT                   128  /* 128 blocks == 16M */
#define BLOCK_MARK_SPARE_OFFSET       4

static rt_mutex_t lock;

/* RT-Thread device interface */

static rt_err_t k9f1g08_mtd_check_block(
		struct rt_mtd_nand_device* device,
		rt_uint32_t block)
{
	rt_uint8_t block_status;
	int result;

	struct nand_device * nand;
	nand = NAND_DEVICE(device);

	fseek(nand->file, block * device->pages_per_block * 
		              (device->page_size + device->oob_size) +
					  device->page_size + BLOCK_MARK_SPARE_OFFSET,
					  SEEK_SET);
	result = fread(&block_status, 1, 1, nand->file);
	if (result < 0)
	{
		NAND_TRACE("nand fread error\n");
		return -RT_ERROR;
	}

	return block_status == 0xFF ? RT_EOK : -RT_ERROR;
}

static rt_err_t k9f1g08_mtd_mark_bad_block(
		struct rt_mtd_nand_device* device,
		rt_uint32_t block)
{
	rt_uint8_t block_status;
	int result;

	struct nand_device * nand;
	nand = NAND_DEVICE(device);

	fseek(nand->file, block * device->pages_per_block *  
		              (device->page_size + device->oob_size) +
					  device->page_size + BLOCK_MARK_SPARE_OFFSET,
					  SEEK_SET);

	block_status = 0x00;
	result = fwrite(&block_status, 1, 1, nand->file);
	if (result < 0)
	{
		NAND_TRACE("nand fwrite error\n");
		return -RT_ERROR;
	}

	return RT_EOK;
}

static char block_buffer[BLOCK_SIZE];

static rt_err_t k9f1g08_mtd_erase_block(
		struct rt_mtd_nand_device* device,
		rt_uint32_t block)
{
	int result;

	struct nand_device * nand;
	nand = NAND_DEVICE(device);

	fseek(nand->file, block * device->pages_per_block * 
		              (device->page_size + device->oob_size),
					  SEEK_SET);

	memset(block_buffer, 0xFF, sizeof(BLOCK_SIZE));
	result = fwrite(block_buffer, BLOCK_SIZE, 1, nand->file);
	if (result < 0)
	{
		NAND_TRACE("nand fwrite error\n");
		return -RT_ERROR;
	}

	return RT_EOK;
}

/* return 0, ecc ok, 1, can be fixed , -1 can not be fixed */
static rt_err_t k9f1g08_mtd_read(
		struct rt_mtd_nand_device * device,
		rt_off_t page,
		rt_uint8_t * data, rt_uint32_t data_len, //may not always be 2048
		rt_uint8_t * spare, rt_uint32_t spare_len)
{
	int result;
	int ecc_status = 0;

	struct nand_device * nand;
	nand = NAND_DEVICE(device);

	if (data != RT_NULL && data_len != 0)
	{
		fseek(nand->file, page * (device->page_size + device->oob_size),
						  SEEK_SET);
		result = fread(data, data_len, 1, nand->file);
		if (result < 0)
			ecc_status = -1;
	}

	if (spare != RT_NULL && spare_len != 0)
	{
		fseek(nand->file, page * (device->page_size + device->oob_size)
			              +device->page_size,
						  SEEK_SET);
		result = fread(spare, spare_len, 1, nand->file);
		if (result < 0)
			ecc_status = -1;
	}

	return ecc_status;
}

static rt_err_t k9f1g08_mtd_write (
		struct rt_mtd_nand_device * device,
		rt_off_t page,
		const rt_uint8_t * data, rt_uint32_t data_len,//will be 2048 always!
		const rt_uint8_t * spare, rt_uint32_t spare_len)
{
	int result;
	int ecc_status = 0;

	struct nand_device * nand;
	nand = NAND_DEVICE(device);

	if (data != RT_NULL && data_len != 0)
	{
		fseek(nand->file, page * (device->page_size + device->oob_size),
						  SEEK_SET);
		result = fwrite(data, data_len, 1, nand->file);
		if (result < 0)
			ecc_status = -1;
	}

	if (spare != RT_NULL && spare_len != 0)
	{
		fseek(nand->file, page * (device->page_size + device->oob_size)
			              +device->page_size,
						  SEEK_SET);
		result = fwrite(spare, spare_len, 1, nand->file);
		if (result < 0)
			ecc_status = -1;
	}

	return ecc_status;
}


const static struct rt_mtd_nand_driver_ops k9f1g08_mtd_ops =
{
	RT_NULL,
	k9f1g08_mtd_read,
	k9f1g08_mtd_write,
	k9f1g08_mtd_erase_block,
	k9f1g08_mtd_check_block,
	k9f1g08_mtd_mark_bad_block,
};

/* interface of nand and rt-thread device */
static struct rt_mtd_nand_device nand_part[2];

int rt_hw_mtd_nand_init(void)
{
	int size;
    rt_uint32_t id, total_block;
    struct nand_device * nand;
    struct rt_mtd_nand_device * nand_part;

    nand = &_nand;
	nand_part = &(nand->parent);

	lock = rt_mutex_create("nand", RT_IPC_FLAG_FIFO);

	/* open sd card file, if not exist, then create it  */
	nand->file = fopen(NAND_SIM, "rb+");
	if (nand->file == NULL)
	{
		int i;
		/* create a file to simulate sd card */
		nand->file = fopen(NAND_SIM, "wb+");

		memset(block_buffer, 0xFF, sizeof(block_buffer));
		for(i=0; i<BLOCK_COUNT; i++)
		{
			fseek(nand->file, i * BLOCK_SIZE, SEEK_SET);
			fwrite(block_buffer, BLOCK_SIZE, 1, nand->file);
		}
	}
	fseek(nand->file, 0, SEEK_SET);

	/* the first partition of nand */
	nand_part->page_size = PAGE_DATA_SIZE;
	nand_part->pages_per_block = BLOCK_PAGES;//don't caculate oob size
	nand_part->block_start = 0;
	nand_part->block_end = BLOCK_COUNT -1;
	nand_part->oob_size = PAGE_SPARE_SIZE;
	nand_part->ops = &k9f1g08_mtd_ops;
	rt_mtd_nand_register_device("nand0", nand_part);
    return RT_EOK;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif
