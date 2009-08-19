#include <rthw.h>
#include <rtthread.h>
#include "stm32f10x_lib.h"

/*
 * WM8753 Driver
 */
	
/* WM8753 register definitions */
#define WM8753_DAC		0x01
#define WM8753_ADC		0x02
#define WM8753_PCM		0x03
#define WM8753_HIFI		0x04
#define WM8753_IOCTL	0x05
#define WM8753_SRATE1	0x06
#define WM8753_SRATE2	0x07
#define WM8753_LDAC		0x08
#define WM8753_RDAC		0x09
#define WM8753_BASS		0x0a
#define WM8753_TREBLE	0x0b
#define WM8753_ALC1		0x0c
#define WM8753_ALC2		0x0d
#define WM8753_ALC3		0x0e
#define WM8753_NGATE	0x0f
#define WM8753_LADC		0x10
#define WM8753_RADC		0x11
#define WM8753_ADCTL1	0x12
#define WM8753_3D		0x13
#define WM8753_PWR1		0x14
#define WM8753_PWR2		0x15
#define WM8753_PWR3		0x16
#define WM8753_PWR4		0x17
#define WM8753_ID		0x18
#define WM8753_INTPOL	0x19
#define WM8753_INTEN	0x1a
#define WM8753_GPIO1	0x1b
#define WM8753_GPIO2	0x1c
#define WM8753_RESET	0x1f
#define WM8753_RECMIX1	0x20
#define WM8753_RECMIX2	0x21
#define WM8753_LOUTM1	0x22
#define WM8753_LOUTM2	0x23
#define WM8753_ROUTM1	0x24
#define WM8753_ROUTM2	0x25
#define WM8753_MOUTM1	0x26
#define WM8753_MOUTM2	0x27
#define WM8753_LOUT1V	0x28
#define WM8753_ROUT1V	0x29
#define WM8753_LOUT2V	0x2a
#define WM8753_ROUT2V	0x2b
#define WM8753_MOUTV	0x2c
#define WM8753_OUTCTL	0x2d
#define WM8753_ADCIN	0x2e
#define WM8753_INCTL1	0x2f
#define WM8753_INCTL2	0x30
#define WM8753_LINVOL	0x31
#define WM8753_RINVOL	0x32
#define WM8753_MICBIAS	0x33
#define WM8753_CLOCK	0x34
#define WM8753_PLL1CTL1	0x35
#define WM8753_PLL1CTL2	0x36
#define WM8753_PLL1CTL3	0x37
#define WM8753_PLL1CTL4	0x38
#define WM8753_PLL2CTL1	0x39
#define WM8753_PLL2CTL2	0x3a
#define WM8753_PLL2CTL3	0x3b
#define WM8753_PLL2CTL4	0x3c
#define WM8753_BIASCTL	0x3d
#define WM8753_ADCTL2	0x3f

/*
SCLK  PA3  SPI1_SCK
SDIN  PA7  SPI1_MOSI
CSB   PA2  SPI1_NSS
*/
#define wm_sclk_0  GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define wm_sclk_1  GPIO_SetBits(GPIOA,GPIO_Pin_3)
#define wm_sdin_0  GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define wm_sdin_1  GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define wm_csb_0   GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define wm_csb_1   GPIO_SetBits(GPIOA,GPIO_Pin_2)

#define DATA_NODE_MAX 5
/* data node for Tx Mode */
struct wm8753_data_node
{
	rt_uint16_t *data_ptr;
	rt_size_t  data_size;
};

struct wm8753_device
{
	/* inherit from rt_device */
	struct rt_device parent;

	/* pcm data list */
	struct wm8753_data_node data_list[DATA_NODE_MAX];
	rt_uint16_t read_index, put_index;

	/* transmitted offset of current data node */
	rt_size_t offset;
};
struct wm8753_device wm8753;

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* SPI2 IRQ Channel configuration */
	NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* DMA1 IRQ Channel configuration */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

	/* Disable the JTAG interface and enable the SWJ interface */
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	/* Configure GPIOA 2, 3, 7 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

	/* Configure SPI2 pins: CK, WS and SD */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

#define SPI2_DR_Address  0x4000380C
static void DMA_Configuration(rt_uint32_t addr, rt_size_t size)
{
	DMA_InitTypeDef    DMA_InitStructure;

	/* DMA1 Channel2 configuration ----------------------------------------------*/
	DMA_Cmd(DMA1_Channel5, DISABLE);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)SPI2_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)addr;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = size;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
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
	I2S_InitStructure.I2S_Standard = I2S_Standard_LSB;
	I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
	I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
	I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_44k;
	I2S_InitStructure.I2S_CPOL = I2S_CPOL_High;// I2S_CPOL_Low

	/* I2S2 Master Transmitter to I2S3 Slave Receiver communication -----------*/
	/* I2S2 configuration */
	I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;//I2S_Mode_MasterTx
	I2S_Init(SPI2, &I2S_InitStructure);
}

void wm8753_send(rt_uint16_t s_data)
{
    u8 i;
    wm_sclk_0;

    for(i=0;i<16;i++)
    {
        if(s_data & 0x8000)
        {
            wm_sdin_1;
        }
        else
        {
            wm_sdin_0;
        }
        //wde();
        wm_sclk_1;
        //wde();
        s_data <<= 1;
        wm_sclk_0;
        //wde();
    }

    wm_csb_0;
    //wde();
    wm_csb_1;
}

void wm8753_hw_write(rt_uint16_t reg, rt_uint16_t value)
{
	rt_uint32_t index;

	value = (reg << 9) | value;

    wm_sclk_0;
    for(index = 0; index < 16; index++)
    {
        if(value & 0x8000) wm_sdin_1;
        else wm_sdin_0;

        wm_sclk_1;
        value <<= 1;
        wm_sclk_0;
    }

    wm_csb_0;
    wm_csb_1;
}

static rt_err_t wm8753_init (rt_device_t dev)
{
	wm8753_send(31<<9 | 0); // reset
	
	wm8753_send(20<<9 | (1<<7) | 1<<6 | 1<<3 | 1<<2 );      // 打开电源 处理部分
	//wm8753_send(21<<9 | 0x1FF);
	wm8753_send(22<<9 | 1<<3 | 1<<7 | 1<<8 | 1<<5 | 1<<6 ); // 电源管理 功率输出部分
	wm8753_send(23<<9 | 1<<1 | 1 ); // 打开左右调音台电源
	
	/*  设置时钟及PLL　 */
	#define MCLK1DIV2 0
	#define pll1_N    11 // 12
	#define pll1_K    0x1288CE // 0x126E97 //0x126E97
	
	#if pll1_K > 0x3FFFFF
	#warning MAX bit(21:0)
	#endif
	
	wm8753_send(53<<9 | 1<<5 | MCLK1DIV2<<3 | 1<<2 | 1<<1 | 1 );
	wm8753_send(54<<9 | pll1_N<<5 | (pll1_K>>18) );
	wm8753_send(55<<9 | ( (pll1_K>>9)&0x1FF ) );
	wm8753_send(56<<9 | ( (pll1_K)&0x1FF ) );
	
	wm8753_send(52<<9 | 1<<1 | 1 ); // 打开CLK输出 测试用 可以不设置
	/*  设置时钟及PLL　 */
	
	/* 设置IIS及DAC */
	// wm8753_send(6<<9 | 0<<1 | 0 ); // 48K
	wm8753_send(6<<9 | 1<<5 | 0 ); // 44.1K
	wm8753_send(4<<9 | 0<<6 | 2 ); // 6.master IIS
	wm8753_send(1<<9 | 0 ); // 关闭DAC静音
	/* 设置IIS及DAC */

	/* 设置模拟通道及功放输出部分 */
	wm8753_send(34<<9 | 1<<8 | 1<<7 | 4<<4 );  // DAC LINE
	wm8753_send(36<<9 | 1<<8 | 1<<7 | 4<<4 );  // DAC LINE
	
	wm8753_send(40<<9 | 1<<8 | 1<<7 | 110);    // 耳机音量
	wm8753_send(41<<9 | 1<<8 | 1<<7 | 110);    // 耳机音量
	
	wm8753_send(45<<9 | 1<<2); // 设置ROUT反向
	wm8753_send(43<<9 | 1<<8 | 1<<7 | 70 ); //喇叭音量

	return RT_EOK;
}

#include <finsh.h>
void vol(int v)
{
	wm8753_send(40<<9 | 1<<8 | 1<<7 | v);    // 耳机音量
	wm8753_send(41<<9 | 1<<8 | 1<<7 | v);    // 耳机音量
}
FINSH_FUNCTION_EXPORT(vol, set volume)

static rt_err_t wm8753_open(rt_device_t dev, rt_uint16_t oflag)
{
	/* enable I2S */
	I2S_Cmd(SPI2, ENABLE);

	return RT_EOK;
}

static rt_err_t wm8753_close(rt_device_t dev)
{
	/* interrupt mode */
	if (dev->flag & RT_DEVICE_FLAG_INT_TX)
	{
		/* Disable the I2S2 */
		I2S_Cmd(SPI2, DISABLE);
	}

	/* remove all data node */
	
	return RT_EOK;
}

static rt_err_t wm8753_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
	/* rate control */
	return RT_EOK;
}

static rt_size_t wm8753_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
	struct wm8753_device* device;
	struct wm8753_data_node* node;
	rt_uint32_t level;
	rt_uint16_t next_index;
	
	device = (struct wm8753_device*)dev;
	RT_ASSERT(device != RT_NULL);
	
	next_index = device->put_index + 1;
	if (next_index >= DATA_NODE_MAX) next_index = 0;

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
	node->data_ptr = (rt_uint16_t*)buffer;
	node->data_size = size >> 1; /* size is byte unit, convert to half word unit */

// #if 0
	{
		/* sound patch */
		rt_uint32_t index;
		for (index = 0; index < node->data_size; index ++)
		{
			((rt_int16_t*)(node->data_ptr))[index] = (rt_int16_t)(node->data_ptr[index] + 0x8000);
		}
	}
// #endif

	next_index = device->read_index + 1;
	if (next_index >= DATA_NODE_MAX) next_index = 0;
	
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
			DMA_Configuration((rt_uint32_t)node->data_ptr, node->data_size);
		}
	}
	rt_hw_interrupt_enable(level);

	return size;
}

rt_err_t wm8753_hw_init(void)
{
	rt_device_t dev;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	NVIC_Configuration();
	GPIO_Configuration();
	I2S_Configuration();

	dev = (rt_device_t)&wm8753;
	dev->type			= RT_Device_Class_Unknown;
	dev->rx_indicate 	= RT_NULL;
	dev->tx_complete 	= RT_NULL;
	dev->init 			= wm8753_init;
	dev->open			= wm8753_open;
	dev->close			= wm8753_close;
	dev->read 			= RT_NULL;
	dev->write 			= wm8753_write;
	dev->control 		= wm8753_control;
	dev->private		= RT_NULL;

	/* set read_index and put index to 0 */
	wm8753.read_index	= 0;
	wm8753.put_index 	= 0;

    wm_sclk_0;
    wm_sclk_1;
    wm_sclk_0;

    wm_sdin_0;
    wm_sdin_1;
    wm_sdin_0;

    wm_csb_0;
    wm_csb_1;

	/* register the device */
	return rt_device_register(&wm8753.parent, "snd", 
		RT_DEVICE_FLAG_WRONLY | RT_DEVICE_FLAG_DMA_TX);
}

void wm8753_isr()
{
	struct wm8753_data_node* node;
	node = &wm8753.data_list[wm8753.read_index]; /* get current data node */
	
	if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_TXE) == SET)
	{
		SPI_I2S_SendData(SPI2, node->data_ptr[wm8753.offset++]);
	}

	if (wm8753.offset == node->data_size)
	{
		/* move to next node */
		rt_uint16_t next_index;
		
		next_index = wm8753.read_index + 1;
		if (next_index >= DATA_NODE_MAX) next_index = 0;

		/* notify transmitted complete. */
		if (wm8753.parent.tx_complete != RT_NULL)
		{
			wm8753.parent.tx_complete (&wm8753.parent, wm8753.data_list[wm8753.read_index].data_ptr);
			rt_kprintf("-\n");
		}

		wm8753.offset = 0;
		wm8753.read_index = next_index;
		if (next_index == wm8753.put_index)
		{
			/* no data on the list, disable I2S interrupt */
			SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, DISABLE);
			
			rt_kprintf("*\n");
		}
	}
}

void wm8753_dma_isr()
{
	/* switch to next buffer */
	rt_uint16_t next_index;
	void* data_ptr;
	
	next_index = wm8753.read_index + 1;
	if (next_index >= DATA_NODE_MAX) next_index = 0;

	/* save current data pointer */
	data_ptr = wm8753.data_list[wm8753.read_index].data_ptr;

	wm8753.read_index = next_index;
	if (next_index != wm8753.put_index)
	{
		/* enable next dma request */
		DMA_Configuration((rt_uint32_t)wm8753.data_list[wm8753.read_index].data_ptr, 
			wm8753.data_list[wm8753.read_index].data_size);
	}
	else
	{
		rt_kprintf("*\n");
	}

	/* notify transmitted complete. */
	if (wm8753.parent.tx_complete != RT_NULL)
	{
		wm8753.parent.tx_complete (&wm8753.parent, data_ptr);
		// rt_kprintf("-\n");
	}
}

