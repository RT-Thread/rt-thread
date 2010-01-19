#include <rthw.h>
#include <rtthread.h>
#include "stm32f10x.h"

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
SCLK  PA5  SPI1_SCK
SDIN  PA6
CSB   PC5
*/
#define wm_sclk_0  GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define wm_sclk_1  GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define wm_sdin_0  GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define wm_sdin_1  GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define wm_csb_0   GPIO_ResetBits(GPIOC,GPIO_Pin_5)
#define wm_csb_1   GPIO_SetBits(GPIOC,GPIO_Pin_5)

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
    SPI_InitTypeDef SPI_InitStructure;

#define SPI_MASTER                   SPI1
#define SPI_MASTER_CLK               RCC_APB2Periph_SPI1
#define SPI_MASTER_GPIO              GPIOA
#define SPI_MASTER_GPIO_CLK          RCC_APB2Periph_GPIOA
#define SPI_MASTER_PIN_SCK           GPIO_Pin_5
#define SPI_MASTER_PIN_MISO          GPIO_Pin_6
#define SPI_MASTER_PIN_MOSI          GPIO_Pin_7
#define SPI_MASTER_IRQn              SPI1_IRQn

    /* Disable the JTAG interface and enable the SWJ interface */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                           RCC_APB2Periph_AFIO, ENABLE);

    /* Enable SPI_MASTER Periph clock */
    RCC_APB2PeriphClockCmd(SPI_MASTER_CLK, ENABLE);

    /* Configure SPI_MASTER pins: SCK, MISO and MOSI */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    /* SPI_MASTER configuration ------------------------------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;/* 常态为低电平 */
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; /* SPI_CPHA_1Edge 从第一个沿开始送数据: 上升沿
                                                    SPI_CPHA_2Edge 从第二个沿开始送数据: 下降沿 */
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    /* Enable SPI_MASTER */
    SPI_Cmd(SPI1, ENABLE);
    SPI_CalculateCRC(SPI1, DISABLE);


    /* Configure SPI2 pins: CK, WS and SD */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

#if 0
    /*    MCO    configure */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    RCC_MCOConfig(RCC_MCO_HSE);
#endif
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
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
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
    I2S_InitStructure.I2S_CPOL = I2S_CPOL_High;// I2S_CPOL_Low

    /* I2S2 Master Transmitter to I2S3 Slave Receiver communication -----------*/
    /* I2S2 configuration */
    I2S_InitStructure.I2S_Mode = I2S_Mode_MasterTx;//I2S_Mode_MasterTx  I2S_Mode_SlaveTx
    I2S_Init(SPI2, &I2S_InitStructure);
}

#if 1
static void wm_delay(void)
{
    volatile unsigned int dl;
    for(dl=0; dl<5000; dl++);
}
#endif

void wm8753_send(rt_uint16_t s_data)
{
    /* Wait for SPI1 Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    wm_csb_0;
    /* Send SPI1 data */
    SPI_I2S_SendData(SPI1, (s_data>>8)&0xFF );
    /* Wait for SPI1 Tx buffer empty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    /* Send SPI1 data */
    SPI_I2S_SendData(SPI1, s_data&0xFF);

    wm_delay();
    wm_csb_1;

#if 0
    u8 i;
    wm_csb_0;
    //wm_delay();
    wm_sclk_0;
    //wm_delay();
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
        //wm_delay();
        wm_sclk_1;
        s_data <<= 1;
        //wm_delay();
        wm_sclk_0;
    }
    //wm_delay();
    wm_csb_1;
#endif
}

static rt_err_t wm8753_init (rt_device_t dev)
{
    wm8753_send(0xF00F); // test
    wm8753_send(0<<9 | 0xFF); // reset
    //wm_delay();
    //wm_delay();
    //wm_delay();

    /* POWER manager */
    wm8753_send(1<<9 | (1<<8) | (0<<7) | (0<<6) | (0<<5) | (1<<4) | (1<<3) | (1<<2) | 2    );//电源设置
    wm8753_send(2<<9 | (1<<8) | (1<<7) | (1<<5) | (1<<4) | (1<<3) | (1<<2) );                // 打开电源  耳机输出
    wm8753_send(3<<9 | (0<<8) | (0<<7) | (1<<6) | (1<<5) | (1<<3) | (1<<2) | (1<<1) | 1 );   // 喇叭输出和DAC

    /* IIS DAC test */
    wm8753_send(4<<9 | (0<<7) | (2<<3) );//IIS 16BIT
    // 12.288/3/8=512K
    wm8753_send(6<<9  | (0<<5) | (3<<2)| 0);//0: slave 1: master  | (3<<5) | (3<<2)
    wm8753_send(43<<9 | (1<<4) );//INVROUT2

    /* 设置初始化音量 */
    wm8753_send(52<<9 | (1<<8) | (1<<7) | 35 ); // LOUT1 0-57-63
    wm8753_send(53<<9 | (1<<8) | (1<<7) | 35 ); // ROUT1 0-57-63
    wm8753_send(54<<9 | (1<<8) | (1<<7) | 35 ); // LOUT2 0-57-63
    wm8753_send(55<<9 | (1<<8) | (1<<7) | 35 ); // ROUT2 0-57-63

    return RT_EOK;
}

#include <finsh.h>
//0~57~63
void vol(int v)
{
    wm8753_send(52<<9 | (0<<8) | (1<<7) | v ); // LOUT1 0-57-63
    wm8753_send(53<<9 | (1<<8) | (1<<7) | v ); // ROUT1 0-57-63
    wm8753_send(54<<9 | (0<<8) | (1<<7) | v ); // LOUT2 0-57-63
    wm8753_send(55<<9 | (1<<8) | (1<<7) | v ); // ROUT2 0-57-63
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

	wm_csb_1;

#if 0
    wm_sclk_0;
    wm_sclk_1;
    wm_sclk_0;

    wm_sdin_0;
    wm_sdin_1;
    wm_sdin_0;

    wm_csb_0;
    wm_csb_1;
#endif

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

