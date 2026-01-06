#include <drv_lcd.h>
#include <stdlib.h>

#define SPI_PORT spi1

uint slice_num;
LCD_ATTRIBUTES LCD;

/******************************************************************************
 function :  Hardware reset
 parameter:
 ******************************************************************************/
static void LCD_Reset(void)
{
    DEV_Digital_Write(LCD_RST_PIN, 1);
    rt_thread_mdelay(100);
    DEV_Digital_Write(LCD_RST_PIN, 0);
    rt_thread_mdelay(100);
    DEV_Digital_Write(LCD_RST_PIN, 1);
    rt_thread_mdelay(100);
}

/******************************************************************************
 function :  send command
 parameter:
 Reg : Command register
 ******************************************************************************/
static void LCD_SendCommand(UBYTE Reg)
{
    DEV_Digital_Write(LCD_DC_PIN, 0);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(LCD_CS_PIN, 1);
}

/******************************************************************************
 function :  send data
 parameter:
 Data : Write data
 ******************************************************************************/
static void LCD_SendData_8Bit(UBYTE Data)
{
    DEV_Digital_Write(LCD_DC_PIN, 1);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(LCD_CS_PIN, 1);
}

/******************************************************************************
 function :  send data
 parameter:
 Data : Write data
 ******************************************************************************/
static void LCD_SendData_16Bit(UWORD Data)
{
    DEV_Digital_Write(LCD_DC_PIN, 1);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    DEV_SPI_WriteByte((Data >> 8) & 0xFF);
    DEV_SPI_WriteByte(Data & 0xFF);
    DEV_Digital_Write(LCD_CS_PIN, 1);
}

/******************************************************************************
 function :  Initialize the lcd register
 parameter:
 ******************************************************************************/
static void LCD_InitReg(void)
{
    LCD_SendCommand(0x3A);
    LCD_SendData_8Bit(0x05);

    LCD_SendCommand(0xB2);
    LCD_SendData_8Bit(0x0C);
    LCD_SendData_8Bit(0x0C);
    LCD_SendData_8Bit(0x00);
    LCD_SendData_8Bit(0x33);
    LCD_SendData_8Bit(0x33);

    LCD_SendCommand(0xB7);   // Gate Control
    LCD_SendData_8Bit(0x35);

    LCD_SendCommand(0xBB);   // VCOM Setting
    LCD_SendData_8Bit(0x19);

    LCD_SendCommand(0xC0);   // LCM Control
    LCD_SendData_8Bit(0x2C);

    LCD_SendCommand(0xC2);   // VDV and VRH Command Enable
    LCD_SendData_8Bit(0x01);
    LCD_SendCommand(0xC3);   // VRH Set
    LCD_SendData_8Bit(0x12);
    LCD_SendCommand(0xC4);   // VDV Set
    LCD_SendData_8Bit(0x20);

    LCD_SendCommand(0xC6);   // Frame Rate Control in Normal Mode
    LCD_SendData_8Bit(0x01); // 110hz

    LCD_SendCommand(0xD0);   // Power Control 1
    LCD_SendData_8Bit(0xA4);
    LCD_SendData_8Bit(0xA1);

    LCD_SendCommand(0xE0);   // Positive Voltage Gamma Control
    LCD_SendData_8Bit(0xD0);
    LCD_SendData_8Bit(0x04);
    LCD_SendData_8Bit(0x0D);
    LCD_SendData_8Bit(0x11);
    LCD_SendData_8Bit(0x13);
    LCD_SendData_8Bit(0x2B);
    LCD_SendData_8Bit(0x3F);
    LCD_SendData_8Bit(0x54);
    LCD_SendData_8Bit(0x4C);
    LCD_SendData_8Bit(0x18);
    LCD_SendData_8Bit(0x0D);
    LCD_SendData_8Bit(0x0B);
    LCD_SendData_8Bit(0x1F);
    LCD_SendData_8Bit(0x23);

    LCD_SendCommand(0xE1);   // Negative Voltage Gamma Control
    LCD_SendData_8Bit(0xD0);
    LCD_SendData_8Bit(0x04);
    LCD_SendData_8Bit(0x0C);
    LCD_SendData_8Bit(0x11);
    LCD_SendData_8Bit(0x13);
    LCD_SendData_8Bit(0x2C);
    LCD_SendData_8Bit(0x3F);
    LCD_SendData_8Bit(0x44);
    LCD_SendData_8Bit(0x51);
    LCD_SendData_8Bit(0x2F);
    LCD_SendData_8Bit(0x1F);
    LCD_SendData_8Bit(0x1F);
    LCD_SendData_8Bit(0x20);
    LCD_SendData_8Bit(0x23);

    LCD_SendCommand(0x21); // Display Inversion On

    LCD_SendCommand(0x11); // Sleep Out

    LCD_SendCommand(0x29); // Display On
}

/********************************************************************************
 function:   Set the resolution and scanning method of the screen
 parameter:
 Scan_dir:   Scan direction
 ********************************************************************************/
static void LCD_SetAttributes(UBYTE Scan_dir)
{
    // Get the screen scan direction
    LCD.SCAN_DIR = Scan_dir;
    UBYTE MemoryAccessReg = 0x00;

    // Get GRAM and LCD width and height
    if (Scan_dir == HORIZONTAL)
    {
        LCD.HEIGHT = LCD_WIDTH;
        LCD.WIDTH = LCD_HEIGHT;
        MemoryAccessReg = 0X70;
    }
    else
    {
        LCD.HEIGHT = LCD_HEIGHT;
        LCD.WIDTH = LCD_WIDTH;
        MemoryAccessReg = 0X00;
    }

    // Set the read / write scan direction of the frame memory
    LCD_SendCommand(0x36);              // MX, MY, RGB mode
    LCD_SendData_8Bit(MemoryAccessReg); // 0x08 set RGB
}

/********************************************************************************
 function :  Initialize the lcd
 parameter:
 ********************************************************************************/
void LCD_Init(UBYTE Scan_dir)
{
    DEV_SET_PWM(50);

    // Hardware reset
    LCD_Reset();

    // Set the resolution and scanning method of the screen
    LCD_SetAttributes(Scan_dir);

    // Set the initialization register
    LCD_InitReg();
}

void LCD_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
    // set the X coordinates
    LCD_SendCommand(0x2A);
    LCD_SendData_8Bit((Xstart >> 8) & 0xFF);
    LCD_SendData_8Bit(Xstart & 0xFF);
    LCD_SendData_8Bit(((Xend - 1) >> 8) & 0xFF);
    LCD_SendData_8Bit((Xend - 1) & 0xFF);

    // set the Y coordinates
    LCD_SendCommand(0x2B);
    LCD_SendData_8Bit((Ystart >> 8) & 0xFF);
    LCD_SendData_8Bit(Ystart & 0xFF);
    LCD_SendData_8Bit(((Yend - 1) >> 8) & 0xFF);
    LCD_SendData_8Bit((Yend - 1) & 0xFF);

    LCD_SendCommand(0X2C);
}

/******************************************************************************
 function :  Clear screen
 parameter:
 ******************************************************************************/
void LCD_Clear(UWORD Color)
{
    UWORD j, i;
    UWORD Image[LCD.WIDTH * LCD.HEIGHT];

    Color = ((Color << 8) & 0xff00) | (Color >> 8);

    for (j = 0; j < LCD.HEIGHT * LCD.WIDTH; j++)
    {
        Image[j] = Color;
    }

    LCD_SetWindows(0, 0, LCD.WIDTH, LCD.HEIGHT);
    DEV_Digital_Write(LCD_DC_PIN, 1);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    for (j = 0; j < LCD.HEIGHT; j++)
    {
        DEV_SPI_Write_nByte((uint8_t *) &Image[j * LCD.WIDTH], LCD.WIDTH * 2);
    }
    DEV_Digital_Write(LCD_CS_PIN, 1);
}

/******************************************************************************
 function :  Sends the image buffer in RAM to displays
 parameter:
 ******************************************************************************/
void LCD_Display(UWORD *Image)
{
    UWORD j;
    LCD_SetWindows(0, 0, LCD.WIDTH, LCD.HEIGHT);
    DEV_Digital_Write(LCD_DC_PIN, 1);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    for (j = 0; j < LCD.HEIGHT; j++)
    {
        DEV_SPI_Write_nByte((uint8_t *) &Image[j * LCD.WIDTH], LCD.WIDTH * 2);
    }
    DEV_Digital_Write(LCD_CS_PIN, 1);
    LCD_SendCommand(0x29);
}

/******************************************************************************
 function :  Sends the image buffer in RAM to displays
 parameter:
 Xstart  :   X direction Start coordinates
 Ystart  :   Y direction Start coordinates
 Xend    :   X direction end coordinates
 Yend    :   Y direction end coordinates
 Image   :   Written content
 ******************************************************************************/
void LCD_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD *Image)
{
    // display
    UDOUBLE Addr = 0;

    UWORD j;
    LCD_SetWindows(Xstart, Ystart, Xend, Yend);
    DEV_Digital_Write(LCD_DC_PIN, 1);
    DEV_Digital_Write(LCD_CS_PIN, 0);
    for (j = Ystart; j < Yend - 1; j++)
    {
        Addr = Xstart + j * LCD.WIDTH;
        DEV_SPI_Write_nByte((uint8_t *) &Image[Addr], (Xend - Xstart) * 2);
    }
    DEV_Digital_Write(LCD_CS_PIN, 1);
}

/******************************************************************************
 function :  Change the color of a point
 parameter:
 X       :   X coordinates
 Y       :   Y coordinates
 Color   :   Color
 ******************************************************************************/
void LCD_DisplayPoint(UWORD X, UWORD Y, UWORD Color)
{
    LCD_SetWindows(X, Y, X, Y);
    LCD_SendData_16Bit(Color);
}

void Handler_LCD(int signo)
{
    // System Exit
    rt_kprintf("\r\nHandler:Program stop\r\n");
    DEV_Module_Exit();
    exit(0);
}

/**
 * GPIO read and write
 **/
void DEV_Digital_Write(UWORD Pin, UBYTE Value)
{
    gpio_put(Pin, Value);
}

UBYTE DEV_Digital_Read(UWORD Pin)
{
    return gpio_get(Pin);
}

/**
 * GPIO Mode
 **/
void DEV_GPIO_Mode(UWORD Pin, UWORD Mode)
{
    gpio_init(Pin);
    if (Mode == 0 || Mode == GPIO_IN)
    {
        gpio_set_dir(Pin, GPIO_IN);
    }
    else
    {
        gpio_set_dir(Pin, GPIO_OUT);
    }
}

/**
 * SPI
 **/
void DEV_SPI_WriteByte(UBYTE Value)
{
    spi_write_blocking(SPI_PORT, &Value, 1);
}

void DEV_SPI_Write_nByte(UBYTE pData[], UDOUBLE Len)
{
    spi_write_blocking(SPI_PORT, pData, Len);
}

void DEV_GPIO_Init(void)
{
    DEV_GPIO_Mode(LCD_RST_PIN, 1);
    DEV_GPIO_Mode(LCD_DC_PIN, 1);
    DEV_GPIO_Mode(LCD_CS_PIN, 1);
    DEV_GPIO_Mode(LCD_BL_PIN, 1);

    DEV_Digital_Write(LCD_CS_PIN, 1);
    DEV_Digital_Write(LCD_DC_PIN, 0);
    DEV_Digital_Write(LCD_BL_PIN, 1);
}

/******************************************************************************
 function:  Module Initialize, the library and initialize the pins, SPI protocol
 parameter:
 Info:
 ******************************************************************************/
UBYTE DEV_Module_Init(void)
{
    // SPI Config
    spi_init(SPI_PORT, 80000 * 1000);
    gpio_set_function(LCD_CLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(LCD_MOSI_PIN, GPIO_FUNC_SPI);

    // GPIO Config
    DEV_GPIO_Init();

    // PWM Config
    gpio_set_function(LCD_BL_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(LCD_BL_PIN);
    pwm_set_wrap(slice_num, 100);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 1);
    pwm_set_clkdiv(slice_num, 50);
    pwm_set_enabled(slice_num, true);

    rt_kprintf("DEV_Module_Init OK \r\n");

    return 0;
}

void DEV_SET_PWM(UBYTE Value)
{
    if (Value < 0 || Value > 100)
    {
        rt_kprintf("DEV_SET_PWM Error \r\n");
    }
    else
    {
        pwm_set_chan_level(slice_num, PWM_CHAN_B, Value);
    }
}

UBYTE SPI_Init(void)
{
    DEV_Module_Init();
    return 0;
}

bool _swapBytes;
UDOUBLE dma_tx_channel;
dma_channel_config dma_tx_config;

/***************************************************************************************
 ** Function name:           dmaWait
 ** Description:             Wait until DMA is over (blocking!)
 ***************************************************************************************/
void dmaWait(void)
{
    while (dma_channel_is_busy(dma_tx_channel))
        ;

    // For SPI must also wait for FIFO to flush and reset format
    while (spi_get_hw(SPI_PORT)->sr & SPI_SSPSR_BSY_BITS)
    {
    };
    spi_set_format(SPI_PORT, 16, (spi_cpol_t) 0, (spi_cpha_t) 0, SPI_MSB_FIRST);
}

/***************************************************************************************
 ** Function name:           pushPixelsDMA
 ** Description:             Push pixels to TFT
 ***************************************************************************************/
void pushPixelsDMA(UWORD* image, UDOUBLE len)
{
    if ((len == 0))
        return;

    dmaWait();

    channel_config_set_bswap(&dma_tx_config, !_swapBytes);

    dma_channel_configure(dma_tx_channel, &dma_tx_config, &spi_get_hw(SPI_PORT)->dr, (UWORD*) image, len, true);
}

bool initDMA(bool ctrl_cs)
{
    dma_tx_channel = dma_claim_unused_channel(true);
    dma_tx_config = dma_channel_get_default_config(dma_tx_channel);

    channel_config_set_transfer_data_size(&dma_tx_config, DMA_SIZE_16);
    channel_config_set_dreq(&dma_tx_config, spi_get_index(SPI_PORT) ? DREQ_SPI1_TX : DREQ_SPI0_TX);

    return true;
}
