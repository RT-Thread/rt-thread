#include <rthw.h>
#include <rtthread.h>
#include "stm32f10x.h"
#include "codec.h"

/*
 * IMPORTANT NOTICE:
 * CODEC_MASTER_MODE = 1 is still unusable due to a suspecting hardware bug of STM32.
 */
#define CODEC_MASTER_MODE	0

/*
SCLK  PA5  SPI1_SCK
SDIN  PA7  SPI1_MOSI
CSB   PC5
*/
#define CODEC_CSB_PORT		GPIOC
#define CODEC_CSB_PIN		GPIO_Pin_5
#define codec_set_csb()		do { CODEC_CSB_PORT->BSRR = CODEC_CSB_PIN; } while (0)
#define codec_reset_csb()	do { CODEC_CSB_PORT->BRR = CODEC_CSB_PIN; } while (0)

void vol(uint16_t v);
static void codec_send(rt_uint16_t s_data);

#define DATA_NODE_MAX 5
/* data node for Tx Mode */
struct codec_data_node
{
    rt_uint16_t *data_ptr;
    rt_size_t  data_size;
};

struct codec_device
{
    /* inherit from rt_device */
    struct rt_device parent;

    /* pcm data list */
    struct codec_data_node data_list[DATA_NODE_MAX];
    rt_uint16_t read_index, put_index;

    /* transmitted offset of current data node */
    rt_size_t offset;
};
struct codec_device codec;

static uint16_t r06 = REG_CLOCK_GEN | CLKSEL_PLL | MCLK_DIV2 | BCLK_DIV8;

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* SPI2 IRQ Channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* DMA1 IRQ Channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	/* Disable the JTAG interface and enable the SWJ interface */
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	/* PC5 CODEC CS */
	GPIO_InitStructure.GPIO_Pin = CODEC_CSB_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(CODEC_CSB_PORT, &GPIO_InitStructure);

#if CODEC_MASTER_MODE
	// WS, CK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// SD
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
#else
	/* Configure SPI2 pins: CK, WS and SD */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif

#ifdef CODEC_USE_MCO
	/*    MCO    configure */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	RCC_MCOConfig(RCC_MCO_HSE);
#endif
}

static void DMA_Configuration(rt_uint32_t addr, rt_size_t size)
{
    DMA_InitTypeDef DMA_InitStructure;

	/* DMA1 Channel2 configuration ----------------------------------------------*/
	DMA_Cmd(DMA1_Channel5, DISABLE);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(SPI2->DR));
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32) addr;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = size;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);

	/* Enable SPI2 DMA Tx request */
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);

	DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
	DMA_Cmd(DMA1_Channel5, ENABLE);
}

static void I2S_Configuration(void)
{
	I2S_InitTypeDef I2S_InitStructure;

	/* I2S peripheral configuration */
	I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
	I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
	I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
	I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_44k;
	I2S_InitStructure.I2S_CPOL = I2S_CPOL_Low;

	/* I2S2 configuration */
#if CODEC_MASTER_MODE
	I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveTx;
#else
	I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;
#endif
	I2S_Init(SPI2, &I2S_InitStructure);
}

uint8_t SPI_WriteByte(unsigned char data)
{
	//Wait until the transmit buffer is empty
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	// Send the byte
	SPI_I2S_SendData(SPI1, data);

	//Wait until a data is received
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	// Get the received data
	data = SPI_I2S_ReceiveData(SPI1);

	// Return the shifted data
	return data;
}

static void codec_send(rt_uint16_t s_data)
{
	codec_reset_csb();
	SPI_WriteByte((s_data >> 8) & 0xFF);
	SPI_WriteByte(s_data & 0xFF);
	codec_set_csb();
}

static rt_err_t codec_init(rt_device_t dev)
{
	codec_send(REG_SOFTWARE_RESET);

	// 1.5x boost power up sequence.
	// Mute all outputs.
	codec_send(REG_LOUT1_VOL | LOUT1MUTE);
	codec_send(REG_ROUT1_VOL | ROUT1MUTE);
	codec_send(REG_LOUT2_VOL | LOUT2MUTE);
	codec_send(REG_ROUT2_VOL | ROUT2MUTE);
	// Enable unused output chosen from L/ROUT2, OUT3 or OUT4.
	codec_send(REG_POWER_MANAGEMENT3 | OUT4EN);
	// Set BUFDCOPEN=1 and BUFIOEN=1 in register R1
	codec_send(REG_POWER_MANAGEMENT1 | BUFDCOPEN | BUFIOEN);
	// Set SPKBOOST=1 in register R49.
	codec_send(REG_OUTPUT | SPKBOOST);
	// Set VMIDSEL[1:0] to required value in register R1.
	codec_send(REG_POWER_MANAGEMENT1 | BUFDCOPEN | BUFIOEN | VMIDSEL_75K);
	// Set L/RMIXEN=1 and DACENL/R=1 in register R3.
	codec_send(REG_POWER_MANAGEMENT3 | LMIXEN | RMIXEN | DACENL | DACENR);
	// Set BIASEN=1 in register R1.
	codec_send(REG_POWER_MANAGEMENT1 | BUFDCOPEN | BUFIOEN | VMIDSEL_75K | BIASEN);
	// Set L/ROUT2EN=1 in register R3.
	codec_send(REG_POWER_MANAGEMENT3 | LMIXEN | RMIXEN | DACENL | DACENR | LOUT2EN | ROUT2EN);
	// Enable other mixers as required.
	// Enable other outputs as required.
	codec_send(REG_POWER_MANAGEMENT2 | LOUT1EN | ROUT1EN | BOOSTENL | BOOSTENR | INPPGAENL | INPPGAENR);

	// Digital inferface setup.
	codec_send(REG_AUDIO_INTERFACE | BCP_NORMAL | LRP_NORMAL | WL_16BITS | FMT_I2S);

	// PLL setup.
	// fs = 44.1KHz * 256fs = 11.2896MHz
	// F_PLL = 11.2896MHz * 4 * 2 = 90.3168MHz
	// R = 90.3168MHz / 12.288MHz = 7.35
	// PLL_N = 7
	// PLL_K = 5872026 (5921370 for STM32's 44.117KHz fs generated from 72MHz clock)
	codec_send(REG_PLL_N | 7);
#if CODEC_MASTER_MODE
	codec_send(REG_PLL_K1 | 0x16);
	codec_send(REG_PLL_K2 | 0xCC);
	codec_send(REG_PLL_K3 | 0x19A);
#else
	codec_send(REG_PLL_K1 | 0x16);
	codec_send(REG_PLL_K2 | 0x12D);
	codec_send(REG_PLL_K3 | 0x5A);
#endif
	codec_send(REG_POWER_MANAGEMENT1 | BUFDCOPEN | BUFIOEN | VMIDSEL_75K | BIASEN | PLLEN);
	codec_send(r06);

	// Enable DAC 128x oversampling.
	codec_send(REG_DAC | DACOSR128);

	// Set LOUT2/ROUT2 in BTL operation.
	codec_send(REG_BEEP | INVROUT2);

	// Set output volume.
	vol(20);

	return RT_EOK;
}

// Exported functions
#include <finsh.h>

void vol(uint16_t v)
{
	v = (v & VOL_MASK) << VOL_POS;
	codec_send(REG_LOUT1_VOL | v);
	codec_send(REG_ROUT1_VOL | HPVU | v);
	codec_send(REG_LOUT2_VOL | v);
	codec_send(REG_ROUT2_VOL | SPKVU | v);
}

void eq1(uint8_t freq, uint8_t gain, uint8_t mode)
{
	codec_send(REG_EQ1 | ((freq & EQC_MASK) << EQC_POS) | ((gain & EQG_MASK) << EQG_POS) | (mode ? EQ3DMODE_DAC : EQ3DMODE_ADC));
}

void eq2(uint8_t freq, uint8_t gain, uint8_t bw)
{
	codec_send(REG_EQ2 | ((freq & EQC_MASK) << EQC_POS) | ((gain & EQG_MASK) << EQG_POS) | (bw ? EQ2BW_WIDE : EQ2BW_NARROW));
}

void eq3(uint8_t freq, uint8_t gain, uint8_t bw)
{
	codec_send(REG_EQ3 | ((freq & EQC_MASK) << EQC_POS) | ((gain & EQG_MASK) << EQG_POS) | (bw ? EQ3BW_WIDE : EQ3BW_NARROW));
}

void eq4(uint8_t freq, uint8_t gain, uint8_t bw)
{
	codec_send(REG_EQ4 | ((freq & EQC_MASK) << EQC_POS) | ((gain & EQG_MASK) << EQG_POS) | (bw ? EQ4BW_WIDE : EQ4BW_NARROW));
}

void eq5(uint8_t freq, uint8_t gain)
{
	codec_send(REG_EQ2 | ((freq & EQC_MASK) << EQC_POS) | ((gain & EQG_MASK) << EQG_POS));
}

void eq3d(uint8_t depth)
{
	codec_send(REG_3D | ((depth & DEPTH3D_MASK) << DEPTH3D_POS));
}

rt_err_t sample_rate(uint8_t sr)
{
	uint16_t r07 = REG_ADDITIONAL;

	switch (sr)
	{
	case 8:
		r06 = REG_CLOCK_GEN | CLKSEL_MCLK | MCLK_DIV6 | BCLK_DIV8 | (r06 & MS);
		r07 |= SR_8KHZ;
		break;

	case 11:
		r06 = REG_CLOCK_GEN | CLKSEL_PLL | MCLK_DIV8 | BCLK_DIV8 | (r06 & MS);
		r07 |= SR_12KHZ;
		break;

#if CODEC_MASTER_MODE
	case 12:
		r06 = REG_CLOCK_GEN | CLKSEL_MCLK | MCLK_DIV4 | BCLK_DIV8 | (r06 & MS);
		r07 |= SR_12KHZ;
		break;
#endif

	case 16:
		r06 = REG_CLOCK_GEN | CLKSEL_MCLK | MCLK_DIV3 | BCLK_DIV8 | (r06 & MS);
		r07 |= SR_16KHZ;
		break;

	case 22:
		r06 = REG_CLOCK_GEN | CLKSEL_PLL | MCLK_DIV4 | BCLK_DIV8 | (r06 & MS);
		r07 |= SR_24KHZ;
		break;

#if CODEC_MASTER_MODE
	case 24:
		r06 = REG_CLOCK_GEN | CLKSEL_MCLK | MCLK_DIV2 | BCLK_DIV8 | (r06 & MS);
		r07 |= SR_24KHZ;
		break;
#endif

	case 32:
		r06 = REG_CLOCK_GEN | CLKSEL_MCLK | MCLK_DIV1_5 | BCLK_DIV8 | (r06 & MS);
		r07 |= SR_32KHZ;
		break;

	case 44:
		r06 = REG_CLOCK_GEN | CLKSEL_PLL | MCLK_DIV2 | BCLK_DIV8 | (r06 & MS);
		r07 |= SR_48KHZ;
		break;

	case 48:
		r06 = REG_CLOCK_GEN | CLKSEL_MCLK | MCLK_DIV1 | BCLK_DIV8 | (r06 & MS);
		r07 |= SR_48KHZ;
		break;

	default:
		return RT_ERROR;
	}
	codec_send(r06);
	codec_send(r07);
	return RT_EOK;
}

FINSH_FUNCTION_EXPORT(vol, Set volume);
FINSH_FUNCTION_EXPORT(eq1, Set EQ1(Cut-off, Gain, Mode));
FINSH_FUNCTION_EXPORT(eq2, Set EQ2(Center, Gain, Bandwidth));
FINSH_FUNCTION_EXPORT(eq3, Set EQ3(Center, Gain, Bandwidth));
FINSH_FUNCTION_EXPORT(eq4, Set EQ4(Center, Gain, Bandwidth));
FINSH_FUNCTION_EXPORT(eq5, Set EQ5(Cut-off, Gain));
FINSH_FUNCTION_EXPORT(eq3d, Set 3D(Depth));
FINSH_FUNCTION_EXPORT(sample_rate, Set sample rate);

static rt_err_t codec_open(rt_device_t dev, rt_uint16_t oflag)
{
#if !CODEC_MASTER_MODE
	/* enable I2S */
	I2S_Cmd(SPI2, ENABLE);
#endif

	return RT_EOK;
}

static rt_err_t codec_close(rt_device_t dev)
{
	/* interrupt mode */
	if (dev->flag & RT_DEVICE_FLAG_INT_TX)
	{
#if CODEC_MASTER_MODE
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET);

		I2S_Cmd(SPI2, DISABLE);

		r06 &= ~MS;
		codec_send(r06);
#else
		/* Disable the I2S2 */
		I2S_Cmd(SPI2, DISABLE);
#endif
	}
#if CODEC_MASTER_MODE
	else if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
	{
		DMA_Cmd(DMA1_Channel5, DISABLE);

		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET);

		I2S_Cmd(SPI2, DISABLE);

		r06 &= ~MS;
		codec_send(r06);
	}
#endif

	/* remove all data node */

	return RT_EOK;
}

static rt_err_t codec_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	/* rate control */
	return RT_EOK;
}

static rt_size_t codec_write(rt_device_t dev, rt_off_t pos,
		const void* buffer, rt_size_t size)
{
	struct codec_device* device;
	struct codec_data_node* node;
	rt_uint32_t level;
	rt_uint16_t next_index;

	device = (struct codec_device*) dev;
	RT_ASSERT(device != RT_NULL);

	next_index = device->put_index + 1;
	if (next_index >= DATA_NODE_MAX)
		next_index = 0;

	/* check data_list full */
	if (next_index == device->read_index)
	{
		rt_set_errno(-RT_EFULL);
		return 0;
	}

	level = rt_hw_interrupt_disable();
	node = &device->data_list[device->put_index];
	device->put_index = next_index;

	// rt_kprintf("+\n");
	/* set node attribute */
	node->data_ptr = (rt_uint16_t*) buffer;
	node->data_size = size >> 1; /* size is byte unit, convert to half word unit */

	next_index = device->read_index + 1;
	if (next_index >= DATA_NODE_MAX)
		next_index = 0;

	/* check data list whether is empty */
	if (next_index == device->put_index)
	{
		if (dev->flag & RT_DEVICE_FLAG_INT_TX)
		{
			device->offset = 0;
			/* enable I2S interrupt */
			SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, ENABLE);
		}
		else if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
		{
			DMA_Configuration((rt_uint32_t) node->data_ptr, node->data_size);
		}

#if CODEC_MASTER_MODE
		if ((r06 & MS) == 0)
		{
			I2S_Cmd(SPI2, ENABLE);

			r06 |= MS;
			codec_send(r06);
		}
#endif
	}
	rt_hw_interrupt_enable(level);

	return size;
}

rt_err_t codec_hw_init(void)
{
	rt_device_t dev;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	NVIC_Configuration();
	GPIO_Configuration();
	I2S_Configuration();

	dev = (rt_device_t) &codec;
	dev->type = RT_Device_Class_Sound;
	dev->rx_indicate = RT_NULL;
	dev->tx_complete = RT_NULL;
	dev->init = codec_init;
	dev->open = codec_open;
	dev->close = codec_close;
	dev->read = RT_NULL;
	dev->write = codec_write;
	dev->control = codec_control;
	dev->private = RT_NULL;

	/* set read_index and put index to 0 */
	codec.read_index = 0;
	codec.put_index = 0;

	/* unselect */
	codec_set_csb();

	/* register the device */
	return rt_device_register(&codec.parent, "snd", RT_DEVICE_FLAG_WRONLY | RT_DEVICE_FLAG_DMA_TX);
}

void codec_isr()
{
	struct codec_data_node* node;
	node = &codec.data_list[codec.read_index]; /* get current data node */

	if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_TXE) == SET)
	{
#if CODEC_MASTER_MODE
		if ((r06 & MS) == 0)
		{
			I2S_Cmd(SPI2, ENABLE);
			SPI_I2S_SendData(SPI2, node->data_ptr[codec.offset++]);

			r06 |= MS;
			codec_send(r06);
		}
		else
		{
			SPI_I2S_SendData(SPI2, node->data_ptr[codec.offset++]);
		}
#else
		SPI_I2S_SendData(SPI2, node->data_ptr[codec.offset++]);
#endif
	}

	if (codec.offset == node->data_size)
	{
		/* move to next node */
		rt_uint16_t next_index;

		next_index = codec.read_index + 1;
		if (next_index >= DATA_NODE_MAX)
			next_index = 0;

		/* notify transmitted complete. */
		if (codec.parent.tx_complete != RT_NULL)
		{
			codec.parent.tx_complete(&codec.parent,
					codec.data_list[codec.read_index].data_ptr);
			rt_kprintf("-\n");
		}

		codec.offset = 0;
		codec.read_index = next_index;
		if (next_index == codec.put_index)
		{
			/* no data on the list, disable I2S interrupt */
			SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, DISABLE);

#if CODEC_MASTER_MODE
			while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
			while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET);

			I2S_Cmd(SPI2, DISABLE);

			r06 &= ~MS;
			codec_send(r06);
#endif

			rt_kprintf("*\n");
		}
	}
}

void codec_dma_isr()
{
	/* switch to next buffer */
	rt_uint16_t next_index;
	void* data_ptr;

	next_index = codec.read_index + 1;
	if (next_index >= DATA_NODE_MAX)
		next_index = 0;

	/* save current data pointer */
	data_ptr = codec.data_list[codec.read_index].data_ptr;

	codec.read_index = next_index;
	if (next_index != codec.put_index)
	{
		/* enable next dma request */
		DMA_Configuration((rt_uint32_t) codec.data_list[codec.read_index].data_ptr, codec.data_list[codec.read_index].data_size);

#if CODEC_MASTER_MODE
		if ((r06 & MS) == 0)
		{
			I2S_Cmd(SPI2, ENABLE);

			r06 |= MS;
			codec_send(r06);
		}
#endif
	}
	else
	{
#if CODEC_MASTER_MODE
		DMA_Cmd(DMA1_Channel5, DISABLE);

		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET);

		I2S_Cmd(SPI2, DISABLE);

		r06 &= ~MS;
		codec_send(r06);
#endif

		rt_kprintf("*\n");
	}

	/* notify transmitted complete. */
	if (codec.parent.tx_complete != RT_NULL)
	{
		codec.parent.tx_complete(&codec.parent, data_ptr);
		// rt_kprintf("-\n");
	}
}
