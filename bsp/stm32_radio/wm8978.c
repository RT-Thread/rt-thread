#include <rthw.h>
#include <rtthread.h>
#include "stm32f10x.h"

/*
 * WM8978 Driver
 */

/* WM8978 register definitions */
#define WM8978_DAC		0x01
#define WM8978_ADC		0x02
#define WM8978_PCM		0x03
#define WM8978_HIFI		0x04
#define WM8978_IOCTL	0x05
#define WM8978_SRATE1	0x06
#define WM8978_SRATE2	0x07
#define WM8978_LDAC		0x08
#define WM8978_RDAC		0x09
#define WM8978_BASS		0x0a
#define WM8978_TREBLE	0x0b
#define WM8978_ALC1		0x0c
#define WM8978_ALC2		0x0d
#define WM8978_ALC3		0x0e
#define WM8978_NGATE	0x0f
#define WM8978_LADC		0x10
#define WM8978_RADC		0x11
#define WM8978_ADCTL1	0x12
#define WM8978_3D		0x13
#define WM8978_PWR1		0x14
#define WM8978_PWR2		0x15
#define WM8978_PWR3		0x16
#define WM8978_PWR4		0x17
#define WM8978_ID		0x18
#define WM8978_INTPOL	0x19
#define WM8978_INTEN	0x1a
#define WM8978_GPIO1	0x1b
#define WM8978_GPIO2	0x1c
#define WM8978_RESET	0x1f
#define WM8978_RECMIX1	0x20
#define WM8978_RECMIX2	0x21
#define WM8978_LOUTM1	0x22
#define WM8978_LOUTM2	0x23
#define WM8978_ROUTM1	0x24
#define WM8978_ROUTM2	0x25
#define WM8978_MOUTM1	0x26
#define WM8978_MOUTM2	0x27
#define WM8978_LOUT1V	0x28
#define WM8978_ROUT1V	0x29
#define WM8978_LOUT2V	0x2a
#define WM8978_ROUT2V	0x2b
#define WM8978_MOUTV	0x2c
#define WM8978_OUTCTL	0x2d
#define WM8978_ADCIN	0x2e
#define WM8978_INCTL1	0x2f
#define WM8978_INCTL2	0x30
#define WM8978_LINVOL	0x31
#define WM8978_RINVOL	0x32
#define WM8978_MICBIAS	0x33
#define WM8978_CLOCK	0x34
#define WM8978_PLL1CTL1	0x35
#define WM8978_PLL1CTL2	0x36
#define WM8978_PLL1CTL3	0x37
#define WM8978_PLL1CTL4	0x38
#define WM8978_PLL2CTL1	0x39
#define WM8978_PLL2CTL2	0x3a
#define WM8978_PLL2CTL3	0x3b
#define WM8978_PLL2CTL4	0x3c
#define WM8978_BIASCTL	0x3d
#define WM8978_ADCTL2	0x3f

/*
SCLK  PB7
SDIN  PB8
CSB   PB9
*/

#define wm_sclk_0  GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define wm_sclk_1  GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define wm_sdin_0  GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define wm_sdin_1  GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define wm_csb_0   GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define wm_csb_1   GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define DATA_NODE_MAX 5
/* data node for Tx Mode */
struct wm8978_data_node
{
    rt_uint16_t *data_ptr;
    rt_size_t   data_size;
};

struct wm8978_device
{
    /* inherit from rt_device */
    struct rt_device parent;

    /* pcm data list */
    struct wm8978_data_node data_list[DATA_NODE_MAX];
    rt_uint16_t read_index, put_index;

    /* transmitted offset of current data node */
    rt_size_t offset;
};
struct wm8978_device wm8978;

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* SPI3 IRQ Channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel = SPI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* DMA1 IRQ Channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* configure GPIO B 7, 8, 9 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8  | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    /* configure GPIO B 3, 5 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* configure GPIO A15 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Disable the JTAG interface and enable the SWJ interface */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}

#define SPI3_DR_Address  0x40003C0C
static void DMA_Configuration(rt_uint32_t addr, rt_size_t size)
{
    DMA_InitTypeDef    DMA_InitStructure;

    /* DMA2 Channel2 configuration ----------------------------------------------*/
    DMA_Cmd(DMA2_Channel2, DISABLE);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)SPI3_DR_Address;
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
    DMA_Init(DMA2_Channel2, &DMA_InitStructure);

    /* Enable SPI3 DMA Tx request */
    SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Tx, ENABLE);

    DMA_ITConfig(DMA2_Channel2, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA2_Channel2, ENABLE);
}

static void I2S_Configuration(void)
{
    I2S_InitTypeDef I2S_InitStructure;

    /* I2S peripheral configuration */
    I2S_InitStructure.I2S_Standard = I2S_Standard_Phillips;
    I2S_InitStructure.I2S_DataFormat = I2S_DataFormat_16b;
    I2S_InitStructure.I2S_MCLKOutput = I2S_MCLKOutput_Disable;
    I2S_InitStructure.I2S_AudioFreq = I2S_AudioFreq_44k;
    I2S_InitStructure.I2S_CPOL = I2S_CPOL_High;// I2S_CPOL_Low

    /* I2S2 Master Transmitter to I2S3 Slave Receiver communication -----------*/
    /* I2S2 configuration */
    I2S_InitStructure.I2S_Mode = I2S_Mode_SlaveTx;
    I2S_Init(SPI3, &I2S_InitStructure);
}

void wm_send(rt_uint16_t s_data)
{
    u8 i;
    wm_csb_0;
    wm_sclk_0;

    for (i=0;i<16;i++)
    {
        if (s_data & 0x8000)
        {
            wm_sdin_1;
        }
        else
        {
            wm_sdin_0;
        }
        wm_sclk_1;
        s_data <<= 1;
        wm_sclk_0;
    }

    wm_csb_1;
}

static rt_err_t wm8978_init (rt_device_t dev)
{
    wm_send(0<<9 | 0xFF); // reset

    /* POWER manager */
    wm_send(1<<9 | (0<<8) | (0<<7) | (0<<6) | (0<<5) | (1<<4) | (1<<3) | (1<<2) | 3 );
    wm_send(2<<9 | (1<<8) | (1<<7) | (1<<5) | (1<<4) );
    wm_send(3<<9 | (0<<8) | (0<<7) | (1<<6) | (1<<5) | (1<<3) | (1<<2) | (1<<1) | 1 );

    /* IIS DAC test */
    wm_send(4<<9 | 0 | (2<<3) );//IIS 16BIT
#if 0
    wm_send(6<<9  | (3<<5) | (3<<2)| 1);//0: slave 1: master  | (3<<5) | (3<<2)
    wm_send(43<<9 | (1<<4) );//INVROUT2
#else
    // 12.288/3 = 4.096M 4.096M / 8 = 512K == (16K *2??)*16?
    wm_send(6<<9  | (3<<5) | (3<<2)| 1); //16K MCLK/3/8
    wm_send(6<<9  | (0<<5) | (3<<2)| 1); //48K MCLK/1/8
#endif

    return RT_EOK;
}

#include <finsh.h>
#if 0
void vol(int v)
{
    wm_send(40<<9 | 0<<8 | 1<<7 | v);
    wm_send(41<<9 | 1<<8 | 1<<7 | v);

    wm_send(42<<9 | 0<<8 | 1<<7 | v);
    wm_send(43<<9 | 1<<8 | 1<<7 | v);
}
FINSH_FUNCTION_EXPORT(vol, set volume)
#endif

static rt_err_t wm8978_open(rt_device_t dev, rt_uint16_t oflag)
{
    /* enable I2S */
    I2S_Cmd(SPI3, ENABLE);

    return RT_EOK;
}

static rt_err_t wm8978_close(rt_device_t dev)
{
    /* interrupt mode */
    if (dev->flag & RT_DEVICE_FLAG_INT_TX)
    {
        /* Disable the I2S2 */
        I2S_Cmd(SPI3, DISABLE);
    }

    /* remove all data node */

    return RT_EOK;
}

static rt_err_t wm8978_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    /* rate control */
    return RT_EOK;
}

static rt_size_t wm8978_write (rt_device_t dev, rt_off_t pos, const void* buffer, rt_size_t size)
{
    struct wm8978_device* device;
    struct wm8978_data_node* node;
    rt_uint32_t level;
    rt_uint16_t next_index;

    device = (struct wm8978_device*)dev;
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

    next_index = device->read_index + 1;
    if (next_index >= DATA_NODE_MAX) next_index = 0;

    /* check data list whether is empty */
    if (next_index == device->put_index)
    {
        if (dev->flag & RT_DEVICE_FLAG_INT_TX)
        {
            device->offset = 0;
            /* enable I2S interrupt */
            SPI_I2S_ITConfig(SPI3, SPI_I2S_IT_TXE, ENABLE);
        }
        else if (dev->flag & RT_DEVICE_FLAG_DMA_TX)
        {
            DMA_Configuration((rt_uint32_t)node->data_ptr, node->data_size);
        }
    }
    rt_hw_interrupt_enable(level);

    return size;
}

rt_err_t wm8978_hw_init(void)
{
    rt_device_t dev;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    NVIC_Configuration();
    GPIO_Configuration();
    I2S_Configuration();

    dev = (rt_device_t)&wm8978;
    dev->type			= RT_Device_Class_Unknown;
    dev->rx_indicate 	= RT_NULL;
    dev->tx_complete 	= RT_NULL;
    dev->init 			= wm8978_init;
    dev->open			= wm8978_open;
    dev->close			= wm8978_close;
    dev->read 			= RT_NULL;
    dev->write 			= wm8978_write;
    dev->control 		= wm8978_control;
    dev->private		= RT_NULL;

    /* set read_index and put index to 0 */
    wm8978.read_index	= 0;
    wm8978.put_index 	= 0;

    wm_sclk_0;
    wm_sclk_1;
    wm_sclk_0;

    wm_sdin_0;
    wm_sdin_1;
    wm_sdin_0;

    wm_csb_1;
    wm_csb_0;
    wm_csb_1;

    /* register the device */
    return rt_device_register(&wm8978.parent, "snd",
                              RT_DEVICE_FLAG_WRONLY | RT_DEVICE_FLAG_DMA_TX);
}

void wm8978_isr()
{
    struct wm8978_data_node* node;
    node = &wm8978.data_list[wm8978.read_index]; /* get current data node */

    if (SPI_I2S_GetITStatus(SPI3, SPI_I2S_IT_TXE) == SET)
    {
        SPI_I2S_SendData(SPI3, node->data_ptr[wm8978.offset++]);
    }

    if (wm8978.offset == node->data_size)
    {
        /* move to next node */
        rt_uint16_t next_index;

        next_index = wm8978.read_index + 1;
        if (next_index >= DATA_NODE_MAX) next_index = 0;

        /* notify transmitted complete. */
        if (wm8978.parent.tx_complete != RT_NULL)
        {
            wm8978.parent.tx_complete (&wm8978.parent, wm8978.data_list[wm8978.read_index].data_ptr);
            rt_kprintf("-\n");
        }

        wm8978.offset = 0;
        wm8978.read_index = next_index;
        if (next_index == wm8978.put_index)
        {
            /* no data on the list, disable I2S interrupt */
            SPI_I2S_ITConfig(SPI3, SPI_I2S_IT_TXE, DISABLE);

            rt_kprintf("*\n");
        }
    }
}

void wm8978_dma_isr()
{
    /* switch to next buffer */
    rt_uint16_t next_index;
    void* data_ptr;

    next_index = wm8978.read_index + 1;
    if (next_index >= DATA_NODE_MAX) next_index = 0;

    /* save current data pointer */
    data_ptr = wm8978.data_list[wm8978.read_index].data_ptr;

    wm8978.read_index = next_index;
    if (next_index != wm8978.put_index)
    {
        /* enable next dma request */
        DMA_Configuration((rt_uint32_t)wm8978.data_list[wm8978.read_index].data_ptr,
                          wm8978.data_list[wm8978.read_index].data_size);
    }
    else
    {
        rt_kprintf("*\n");
    }

    /* notify transmitted complete. */
    if (wm8978.parent.tx_complete != RT_NULL)
    {
        wm8978.parent.tx_complete (&wm8978.parent, data_ptr);
        // rt_kprintf("-\n");
    }
}

