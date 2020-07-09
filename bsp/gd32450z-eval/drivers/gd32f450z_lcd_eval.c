/*!
    \file  gd32f450z_lcd_eval.c
    \brief firmware functions to manage LCD
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-10-19, V1.0.0, firmware for GD32F450Z
*/

#include "gd32f450z_lcd_eval.h"

static void delay(uint32_t time);

/*!
    \brief      enable the LCD
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lcd_enable(void)
{
    gpio_bit_set(LCD_CS_GPIO_PORT, LCD_CS_PIN);
}

/*!
    \brief      disable the LCD
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lcd_disable(void)
{
    gpio_bit_reset(LCD_CS_GPIO_PORT, LCD_CS_PIN);
}

/*!
    \brief      configure the LCD control line
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lcd_ctrl_line_config(void)
{
    /* enable GPIOs clock*/
    rcu_periph_clock_enable(LCD_CS_GPIO_CLK);
    rcu_periph_clock_enable(LCD_RS_GPIO_CLK);

    /* configure LCD_CS_GPIO_PORT(PD11) and LCD_RS_GPIO_PORT(PE3) */
    gpio_mode_set(LCD_CS_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_CS_PIN);
    gpio_output_options_set(LCD_CS_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,LCD_CS_PIN);

    gpio_mode_set(LCD_RS_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LCD_RS_PIN);
    gpio_output_options_set(LCD_RS_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,LCD_RS_PIN);

    /* set the chip select pin */
    lcd_ctrl_line_set(LCD_CS_GPIO_PORT, LCD_CS_PIN);
}

/*!
    \brief      set the LCD control line
    \param[in]  gpiox: control line GPIO
      \arg        LCD_CS_GPIO_PORT: LCD chip select GPIO
      \arg        LCD_RS_GPIO_PORT: LCD register/RAM selection GPIO
    \param[in]  gpiopin: control line pin
      \arg        LCD_CS_PIN: LCD chip select pin
      \arg        LCD_RS_PIN: LCD register/RAM selection pin
    \param[out] none
    \retval     none
*/
void lcd_ctrl_line_set(uint32_t gpiox, uint16_t gpiopin)
{
    gpio_bit_set(gpiox, gpiopin);
}

/*!
    \brief      reset the LCD control line
    \param[in]  gpiox: control line GPIO
      \arg        LCD_CS_GPIO_PORT: LCD chip select GPIO
      \arg        LCD_RS_GPIO_PORT: LCD register/RAM selection GPIO
    \param[in]  gpiopin: control line pin
      \arg        LCD_CS_PIN: LCD chip select pin
      \arg        LCD_RS_PIN: LCD register/RAM selection pin
    \param[out] none
    \retval     none
*/
void lcd_ctrl_line_reset(uint32_t gpiox, uint16_t gpiopin)
{
    gpio_bit_reset(gpiox, gpiopin);
}

/*!
    \brief      configure the LCD SPI and it's GPIOs
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lcd_spi_config(void)
{
    spi_parameter_struct spi_init_struct;
    rcu_periph_clock_enable(RCU_GPIOG);
    rcu_periph_clock_enable(RCU_SPI5);

    /* configure SPI5_SCK(PG13) and SPI5_MOSI(PG14) */
    gpio_af_set(GPIOG,GPIO_AF_5,GPIO_PIN_13);
    gpio_af_set(GPIOG,GPIO_AF_5,GPIO_PIN_14);
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_13|GPIO_PIN_14);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13|GPIO_PIN_14);
    spi_i2s_deinit(SPI5);
    
    if(0 == (SPI_CTL0(LCD_SPI) & SPI_CTL0_SPIEN)){    
        spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
        spi_init_struct.device_mode          = SPI_MASTER;
        spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        spi_init_struct.nss                  = SPI_NSS_SOFT;
        spi_init_struct.prescale             = SPI_PSC_16;
        spi_init_struct.endian               = SPI_ENDIAN_MSB;
        spi_init(LCD_SPI, &spi_init_struct);
        spi_enable(LCD_SPI);
    }
}

/*!
    \brief      write command to select LCD register
    \param[in]  lcd_register: the address of the selected register
    \param[out] none
    \retval     none
*/
void lcd_command_write(uint8_t lcd_register)
{
    /* reset LCD_RS to send command */
    lcd_ctrl_line_reset(LCD_RS_GPIO_PORT, LCD_RS_PIN);

    /* reset LCD control line and send command */
    lcd_disable();
    while(RESET == spi_i2s_flag_get(LCD_SPI, SPI_FLAG_TBE)) ;
    spi_i2s_data_transmit(LCD_SPI, lcd_register);

    /* wait until a data is sent */
    while(RESET != spi_i2s_flag_get(LCD_SPI, SPI_FLAG_TRANS));

    lcd_enable();
}

/*!
    \brief      write data to select LCD register
    \param[in]  value: the value that will be written to the selected register
    \param[out] none
    \retval     none
*/
void lcd_data_write(uint8_t value)
{
    /* set LCD_RS to send data */
    lcd_ctrl_line_set(LCD_RS_GPIO_PORT, LCD_RS_PIN);

    /* reset LCD control line and send data */  
    lcd_disable();
    while(RESET == spi_i2s_flag_get(LCD_SPI, SPI_FLAG_TBE)) ;

    spi_i2s_data_transmit(LCD_SPI, value);

    /* wait until a data is sent */
    while(RESET != spi_i2s_flag_get(LCD_SPI, SPI_FLAG_TRANS)) ;

    lcd_enable();
}

/*!
    \brief      configure the LCD based on the power on sequence
    \param[in]  none
    \param[out] none
    \retval     none
*/
void lcd_power_on(void)
{
    lcd_command_write(0x11);
    delay(120);
    lcd_command_write(0x36);
    lcd_data_write(0x48);
    lcd_command_write(0x3A);
    lcd_data_write(0x55);
    lcd_command_write(0xB4);
    lcd_data_write(0x11);
    lcd_command_write(0xB3);
    lcd_data_write(0x00);
    lcd_data_write(0x00);
    lcd_data_write(0x00);
    lcd_data_write(0x20);
    lcd_command_write(0xC0);
    lcd_data_write(0x10);
    lcd_data_write(0x3B);
    lcd_data_write(0x00);
    lcd_data_write(0x12);
    lcd_data_write(0x01);
    lcd_command_write(0xC5);
    lcd_data_write(0x07);
    lcd_command_write(0xC8);
    lcd_data_write(0x01 );
    lcd_data_write(0x36);
    lcd_data_write(0x00);
    lcd_data_write(0x02);
    lcd_data_write(0x00);
    lcd_data_write(0x1C);
    lcd_data_write(0x77);
    lcd_data_write(0x14);
    lcd_data_write(0x67);
    lcd_data_write(0x20);
    lcd_data_write(0x0E);
    lcd_data_write(0x00);
    lcd_command_write(0xD0);
    lcd_data_write(0x44);
    lcd_data_write(0x41 );
    lcd_data_write(0x08);
    lcd_data_write(0xC2);
    lcd_command_write(0xD1);
    lcd_data_write(0x50);
    lcd_data_write(0x11);
    lcd_command_write(0xD2);
    lcd_data_write(0x05);
    lcd_data_write(0x12);

    lcd_command_write(0xC6);
    lcd_data_write(0x83);
    lcd_command_write(0x29);
    delay(5);
}
/**
  * @brief  New Version 3.5" TFT RGB Hardware needs add this initilize funtion  ---By xufei 2016.10.21
						Modified by GAO HAIYANG, test pass, 17, Nov, 2016
  * @param  None
  * @retval None
  */
void lcd_power_on3(void)
{
		lcd_command_write(0xC0);//power control1 command/w/
		lcd_data_write(0x0A); // P-Gamma level//4.1875v
		lcd_data_write(0x0A); // N-Gamma level
		lcd_command_write(0xC1); // BT & VC Setting//power contrl2 command/w/
		lcd_data_write(0x41);
		lcd_data_write(0x07); // VCI1 = 2.5V
		lcd_command_write(0xC2); // DC1.DC0 Setting//power control3 for normal mode
		lcd_data_write(0x33);
		lcd_command_write(0xC5);//VCOM control
		lcd_data_write(0x00);  //NV memory is not programmed
		lcd_data_write(0x42); // VCM Setting
		lcd_data_write(0x80); // VCM Register Enable
		lcd_command_write(0xB0);      //interface mode control //Polarity Setting
		lcd_data_write(0x02);
		lcd_command_write(0xB1);//frame rate control for normal mode
		lcd_data_write(0xB0); // Frame Rate Setting//70 frame per second//no division for internal clocks
		lcd_data_write(0x11);//17 clocks per line period for idle mode at cpu interface
		lcd_command_write(0xB4);//dispaly inversion control
		lcd_data_write(0x00); // disable Z-inversion , column inversion
		lcd_command_write(0xB6); //display function control// RM.DM Setting
		lcd_data_write(0x70);////0xF0
		lcd_data_write(0x02);//direction of gate scan: G1->G480 one by one, source scan: S1->S960, scan cycle if interval scan in non-display area
		lcd_data_write(0x3B); // number of lines to drive LCD: 8*(0x3C) = 480
		lcd_command_write(0xB7); // Entry Mode
		lcd_data_write(0x07); // disable low voltage detection, normal display, 
		lcd_command_write(0xF0); // Enter ENG , must be set before gamma setting
		lcd_data_write(0x36);
		lcd_data_write(0xA5);
		lcd_data_write(0xD3);
		lcd_command_write(0xE5); // Open gamma function , must be set before gamma setting
		lcd_data_write(0x80);
		lcd_command_write(0xE5); // Page 1
		lcd_data_write(0x01);
		lcd_command_write(0XB3); // WEMODE=0(Page 1) , pixels over window setting will be ignored.//frame rate control in partial mode/full colors
		lcd_data_write(0x00);
		lcd_command_write(0xE5); // Page 0
		lcd_data_write(0x00);
		lcd_command_write(0xF0); // Exit ENG , must be set before gamma setting
		lcd_data_write(0x36);
		lcd_data_write(0xA5);
		lcd_data_write(0x53);
		lcd_command_write(0xE0); // Gamma setting
		//y fine adjustment register for positive polarity
		lcd_data_write(0x00);
		lcd_data_write(0x35);
		lcd_data_write(0x33);
		//y gradient adjustment register for positive polarity
		lcd_data_write(0x00);
		//y amplitude adjustment register for positive polarity
		lcd_data_write(0x00);
		lcd_data_write(0x00);
		//y fine adjustment register for negative polarity
		lcd_data_write(0x00);
		lcd_data_write(0x35);
		lcd_data_write(0x33);
		//y gradient adjustment register for negative polarity
		lcd_data_write(0x00);
		//y amplitude adjustment register for negative polarity
		lcd_data_write(0x00);
		lcd_data_write(0x00);
		lcd_command_write(0x36); // memory data access control //
		lcd_data_write(0x48);//
		lcd_command_write(0x3A); // interface pixel format setting
		lcd_data_write(0x55);//16-bits
		lcd_command_write(0x11); // Exit sleep mode
		lcd_command_write(0x29); // Display on 

		delay(10);
}
/*!
    \brief      insert a delay time
    \param[in]  time: delay time length
    \param[out] none
    \retval     none
*/
static void delay(uint32_t time)
{
    uint32_t timecount = time;
    while(0 != timecount--);
}
