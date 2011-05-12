/******************************************************************//**
 * @file 		dev_sflash.c
 * @brief 	SPI Flash driver of RT-Thread RTOS for using EFM32 USART module.
 * 	This driver is tested by using the M25PX16 device on the EFM32 development kit.
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2010-05-06	onelife		Initial creation for using EFM32 USART module
 *********************************************************************/

/******************************************************************//**
 * @addtogroup efm32_dk
 * @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "board.h"
#include "dev_sflash.h"

#if defined(EFM32_USING_SFLASH)
/* Private typedef -------------------------------------------------------------*/
typedef struct
{
	rt_uint8_t code;
	rt_uint32_t address:24;
	rt_uint32_t dummy:8;
} sflash_instruction;

/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
#ifdef EFM32_SFLASH_DEBUG
#define sflash_debug(format,args...) 		rt_kprintf(format, ##args)
#else
#define sflash_debug(format,args...)
#endif

/* Private constants -----------------------------------------------------------*/
static rt_uint8_t sflash_inst_code_tbl[] = 
{
	/* Instruction only */
	SFLASH_INST_CODE_WREN,
	SFLASH_INST_CODE_WRDI,
	SFLASH_INST_CODE_RDID_L,
	SFLASH_INST_CODE_RDID_S,
	SFLASH_INST_CODE_RDSR,
	SFLASH_INST_CODE_WRSR,
	SFLASH_INST_CODE_BE,
	SFLASH_INST_CODE_DP,
	SFLASH_INST_CODE_RDP,
	/* Instruction and address */
	SFLASH_INST_CODE_WRLR,
	SFLASH_INST_CODE_RDLR,
	SFLASH_INST_CODE_READ,
	SFLASH_INST_CODE_POTP,
	SFLASH_INST_CODE_PP,
	SFLASH_INST_CODE_DIFP,
	SFLASH_INST_CODE_SSE,
	SFLASH_INST_CODE_SE,
	/* Instruction, address and dummy read */
	SFLASH_INST_CODE_READ_F,
	SFLASH_INST_CODE_DOFR,
	SFLASH_INST_CODE_ROTP
};
static rt_uint16_t sflash_data_len_tbl[] = 
{
	/* Instruction only */
	SFLASH_REPLY_LEN_WREN,
	SFLASH_REPLY_LEN_WRDI,
	SFLASH_REPLY_LEN_RDID_L,
	SFLASH_REPLY_LEN_RDID_S,
	SFLASH_REPLY_LEN_RDSR,
	SFLASH_REPLY_LEN_WRSR,
	SFLASH_REPLY_LEN_BE,
	SFLASH_REPLY_LEN_DP,
	SFLASH_REPLY_LEN_RDP,
	/* Instruction and address */
	SFLASH_REPLY_LEN_WRLR,
	SFLASH_REPLY_LEN_RDLR,
	SFLASH_REPLY_LEN_READ,
	SFLASH_REPLY_LEN_POTP,
	SFLASH_REPLY_LEN_PP,
	SFLASH_REPLY_LEN_DIFP,
	SFLASH_REPLY_LEN_SSE,
	SFLASH_REPLY_LEN_SE,
	/* Instruction, address and dummy read */
	SFLASH_REPLY_LEN_READ_F,
	SFLASH_REPLY_LEN_DOFR,
	SFLASH_REPLY_LEN_ROTP
};
static rt_bool_t sflash_read_inst_tbl[] = 
{
	/* Instruction only */
	false,
	false,
	true,
	true,
	true,
	false,
	false,
	false,
	false,
	/* Instruction and address */
	false,
	true,
	true,
	false,
	false,
	false,
	false,
	false,
	/* Instruction, address and dummy read */
	true,
	true,
	true
};

/* Private variables ------------------------------------------------------------*/
static rt_device_t 	sflash 					= RT_NULL;

/* Private function prototypes ---------------------------------------------------*/
/* Private functions ------------------------------------------------------------*/
/******************************************************************//**
 * @brief
 *   Initialize the SPI Flash
 *
 * @details
 *
 * @note
 *
 * @return
 *	 Error code
 *********************************************************************/
rt_err_t efm_spiFash_init(void)
{
	/* Find SPI device */
	sflash = rt_device_find(SFLASH_USING_DEVICE_NAME);

	do
	{
		if (sflash == RT_NULL)
		{
			sflash_debug("SFLASH: Can't find device %s!\n", 
				SFLASH_USING_DEVICE_NAME);
			break;
		}
		sflash_debug("SFLASH: Find device %s\n", SFLASH_USING_DEVICE_NAME);
	
		/* Open SPI device */
		if (sflash->open(sflash, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
		{
			break;
		}

		return RT_EOK;
	} while(0);

	sflash_debug("SFLASH: Init failed!\n");
	return -RT_ERROR;
}

/******************************************************************//**
 * @brief
 *   De-initialize the SPI Flash
 *
 * @details
 *
 * @note
 *
 * @return
 *	 Error code
 *********************************************************************/
rt_err_t efm_spiFash_deinit(void)
{
	do
	{
		if (sflash == RT_NULL)
		{
			sflash_debug("SFLASH: Already deinit!\n");
			break;
		}
	
		/* Close SPI device */
		if (sflash->close(sflash) != RT_EOK)
		{
			break;
		}
		sflash = RT_NULL;
		sflash_debug("SFLASH: Close device %s\n", SFLASH_USING_DEVICE_NAME);

		return RT_EOK;
	} while(0);

	sflash_debug("SFLASH: Deinit failed!\n");
	return -RT_ERROR;
}


/******************************************************************//**
 * @brief
 *   Execute a command
 *
 * @details
 *
 * @note
 *
 * @param[in] command
 *  SPI Flash instruction
 *
 * @param[in] address
 *   Memory address
 *
 * @param[in] buffer
 *   Poniter to the read/write buffer
 *
 * @param[in] size
 *   Buffer size in byte
 *
 * @return
 *	 Number of read/written bytes
 *********************************************************************/
rt_uint32_t efm_spiFash_cmd(
	enum sflash_inst_type_t command, 
	rt_uint32_t address,
	rt_uint8_t *buffer, 
	rt_uint32_t size)
{
	RT_ASSERT(sflash != RT_NULL);

	sflash_instruction *inst;
	rt_uint8_t *inst_buf;
	rt_uint8_t inst_len, head_len;
	rt_uint32_t data_len;

	sflash_debug("SFLASH: Inst %x\n", sflash_inst_code_tbl[command]);
	if (sflash_data_len_tbl[command] && !size)
	{
		sflash_debug("SFLASH: No data!\n");
		return 0x00;
	}

	data_len = (sflash_data_len_tbl[command] < size)? \
				sflash_data_len_tbl[command] : size;
	if (data_len && (buffer == RT_NULL))
	{
		sflash_debug("SFLASH: No buffer specified!\n");
		return 0x00;
	}

	/* Allocate memory for write buffer */
	if (sflash_read_inst_tbl[command])
	{
		inst_buf = rt_malloc(6 + 4);
		inst = (sflash_instruction *)(inst_buf + 1);
		head_len = 1;
	}
	else
	{
		inst_buf = rt_malloc(5 + data_len);
		inst = (sflash_instruction *)inst_buf;
		head_len = 0;
	}

	/* Fill in instruction */
	inst->code = sflash_inst_code_tbl[command];
	if (command >= sflash_inst_wrlr)
	{
		/* MSB first */
		inst->address = ((address & 0x000000FF) << 16) | \
						(address & 0x0000FF00) | \
						((address & 0x00FF0000) >> 16);
		if (command >= sflash_inst_read_f)
		{
			inst->dummy = 0x00;
			inst_len = 5;
		}
		else
		{
			inst_len = 4;
		}
	}
	else
	{
		inst_len = 1;
	}
	head_len += inst_len;

	/* Fill in data and send the buffer */
	if (sflash_read_inst_tbl[command])
	{
		inst_buf[0] = inst_len;
		*(rt_uint8_t **)(inst_buf + head_len) = buffer;

		if (sflash->read(sflash, EFM32_NO_DATA, inst_buf, \
			(data_len == size)? data_len - 1 : data_len) == 0)
		{
			sflash_debug("SFLASH: Read failed!\n");
			return 0x00;
		}
		buffer[data_len] = 0x00;
		sflash_debug("SFLASH: Read %d bytes data to 0x%x\n", data_len, buffer);
	}
	else
	{
		if (data_len)
		{
			rt_memcpy((inst_buf + head_len), buffer, data_len);
		}

		if (sflash->write(sflash, EFM32_NO_DATA, inst_buf, \
			head_len + data_len) == 0)
		{
			sflash_debug("SFLASH: Write failed!\n");
			return 0x00;
		}
		sflash_debug("SFLASH: Write %d/%d bytes data\n", data_len, \
			head_len + data_len);
	}

	/* Free the buffer */
	rt_free(inst_buf);
	return data_len;
}

/*********************************************************************
* 	Export to FINSH
*********************************************************************/
#ifdef RT_USING_FINSH
#include <finsh.h>

void list_sflash(void)
{
	rt_uint8_t buf[4];

	efm_spiFash_cmd(sflash_inst_rdid_s, EFM32_NO_DATA, buf, sizeof(buf));
	
	rt_kprintf(" spi flash on %s\n", SFLASH_USING_DEVICE_NAME);
	rt_kprintf(" manufacturer id: \t%x\n", buf[0]);
	rt_kprintf(" memory type: \t\t%x\n", buf[1]);
	rt_kprintf(" memory capacity: \t%x\n", buf[2]);
}
FINSH_FUNCTION_EXPORT(list_sflash, list the SPI Flash.)
#endif

#endif /* defined(EFM32_USING_SFLASH) */

/******************************************************************//**
 * @}
*********************************************************************/
