/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.    
*
* This software is owned and published by: 
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND 
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC 
* components. This software is licensed by HDSC to be adapted only 
* for use in systems utilizing HDSC components. HDSC shall not be 
* responsible for misuse or illegal use of this software for devices not 
* supported herein. HDSC is providing this software "AS IS" and will 
* not be responsible for issues arising from incorrect user implementation 
* of the software.  
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS), 
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING, 
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED 
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED 
* WARRANTY OF NONINFRINGEMENT.  
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT, 
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT 
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, 
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR 
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA, 
* SAVINGS OR PROFITS, 
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED 
* FROM, THE SOFTWARE.  
*
* This software may be replicated in part or whole for the licensed use, 
* with the restriction that this Disclaimer and Copyright notice must be 
* included with each copy of this software, whether used in part or whole, 
* at all times.
*/
/******************************************************************************/
/** \file stkhc32l19x.h
 **
 ** stk board common define.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2018-03-09  1.0  Lux First version.
 **
 ******************************************************************************/
#ifndef __BOARD_STKHC32L19X_H__
#define __BOARD_STKHC32L19X_H__

///< STK GPIO DEFINE
///< USER KEY
#define STK_USER_PORT       GpioPortA
#define STK_USER_PIN        GpioPin7

///< LED
#define STK_LED_PORT        GpioPortC
#define STK_LED_PIN         GpioPin13

///< XTH
#define SYSTEM_XTH          (32*1000*1000u)     ///< 32MHz

#define STK_XTHI_PORT       GpioPortF
#define STK_XTHI_PIN        GpioPin0
#define STK_XTHO_PORT       GpioPortF
#define STK_XTHO_PIN        GpioPin1

///< XTL
#define SYSTEM_XTL          (32768u)            ///< 32768Hz
#define STK_XTLI_PORT       GpioPortC
#define STK_XTLI_PIN        GpioPin14
#define STK_XTLO_PORT       GpioPortC
#define STK_XTLO_PIN        GpioPin15

///< LCD
#define STK_LCD_COM0_PORT   GpioPortA
#define STK_LCD_COM0_PIN    GpioPin9
#define STK_LCD_COM1_PORT   GpioPortA
#define STK_LCD_COM1_PIN    GpioPin10
#define STK_LCD_COM2_PORT   GpioPortA
#define STK_LCD_COM2_PIN    GpioPin11
#define STK_LCD_COM3_PORT   GpioPortA
#define STK_LCD_COM3_PIN    GpioPin12
#define STK_LCD_SEG0_PORT   GpioPortA
#define STK_LCD_SEG0_PIN    GpioPin8
#define STK_LCD_SEG1_PORT   GpioPortC
#define STK_LCD_SEG1_PIN    GpioPin9
#define STK_LCD_SEG2_PORT   GpioPortC
#define STK_LCD_SEG2_PIN    GpioPin8
#define STK_LCD_SEG3_PORT   GpioPortC
#define STK_LCD_SEG3_PIN    GpioPin7
#define STK_LCD_SEG4_PORT   GpioPortC
#define STK_LCD_SEG4_PIN    GpioPin6
#define STK_LCD_SEG5_PORT   GpioPortB
#define STK_LCD_SEG5_PIN    GpioPin15
#define STK_LCD_SEG6_PORT   GpioPortB
#define STK_LCD_SEG6_PIN    GpioPin14
#define STK_LCD_SEG7_PORT   GpioPortB
#define STK_LCD_SEG7_PIN    GpioPin13

///< I2C EEPROM
#define EVB_I2C0_EEPROM_SCL_PORT    GpioPortB
#define EVB_I2C0_EEPROM_SCL_PIN     GpioPin6
#define EVB_I2C0_EEPROM_SDA_PORT    GpioPortB
#define EVB_I2C0_EEPROM_SDA_PIN     GpioPin7

///< SPI0
#define STK_SPI0_CS_PORT      GpioPortE
#define STK_SPI0_CS_PIN       GpioPin12
#define STK_SPI0_SCK_PORT     GpioPortE
#define STK_SPI0_SCK_PIN      GpioPin13
#define STK_SPI0_MISO_PORT    GpioPortE
#define STK_SPI0_MISO_PIN     GpioPin14
#define STK_SPI0_MOSI_PORT    GpioPortE
#define STK_SPI0_MOSI_PIN     GpioPin15

///< SPI1
#define STK_SPI1_CS_PORT      GpioPortB
#define STK_SPI1_CS_PIN       GpioPin12
#define STK_SPI1_SCK_PORT     GpioPortB
#define STK_SPI1_SCK_PIN      GpioPin13
#define STK_SPI1_MISO_PORT    GpioPortB
#define STK_SPI1_MISO_PIN     GpioPin14
#define STK_SPI1_MOSI_PORT    GpioPortB
#define STK_SPI1_MOSI_PIN     GpioPin15

#endif
