/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_system.c
 * @brief    source file for setting system
 *
 * Change Logs:
 * Date           Author      Version        Notes
 * 2020-11-05     wushengyan         V1.0.0         the first version
 */

#include <stdarg.h>
#include "system.h"


//*****************************************************************************
//
//! A simple  MyPrintf function supporting \%c, \%d, \%p, \%s, \%u,\%x, and \%X.
//!
//! \param format is the format string.
//! \param ... are the optional arguments, which depend on the contents of the
//! \return None.
//
//*****************************************************************************

typedef struct _PrintPort_TypeDef_
{
    UART_TypeDef            *PrintUart;
    GPIO_TypeDef            PrintRX_Port;
    GPIO_Pin_TypeDef        PrintRX_Pin;
    GPIO_TypeDef            PrintTX_Port;
    GPIO_Pin_TypeDef        PrintTX_Pin;
} PrintPort_TypeDef;

static PrintPort_TypeDef PrintPort_Struct =
{
    .PrintUart    = PRINTPORT,
    .PrintRX_Port = PRINTRX_PORT,
    .PrintRX_Pin  = PRINTRX_IO_PIN,
    .PrintTX_Port = PRINTTX_PORT,
    .PrintTX_Pin  = PRINTTX_IO_PIN,
};


//#define SIM_PLATFORM

void print_char(int data)
{

    volatile int *ptr;
    ptr = (volatile int *)0xE0300;
    *ptr = data;
}

void printfsend(uint8_t *buf, int len)
{
    uint8_t printbuf[256];
    for (int i = 0; i < len; i++)
    {
        printbuf[i] = buf[i];
#ifdef  SIM_PLATFORM
        print_char(buf[i]);
#endif
    }
#ifndef SIM_PLATFORM
    //UART_SendBuf(PrintPort_Struct.PrintUart, printbuf, len);
    UART_SendBuf(PRINTPORT, printbuf, len);
#endif
}

void MyPrintf(char *format, ...)
{
    static const int8_t *const g_pcHex1 = "0123456789abcdef";
    static const int8_t *const g_pcHex2 = "0123456789ABCDEF";

    uint32_t ulIdx = 0, ulValue = 0, ulPos = 0, ulCount = 0, ulBase = 0, ulNeg = 0;
    int8_t *pcStr = NULL, pcBuf[16] = {0}, cFill = 0;
    char HexFormat;
    va_list vaArgP;

    va_start(vaArgP, format);

    while (*format)
    {
        /* Find the first non-% character, or the end of the string. */
        for (ulIdx = 0; (format[ulIdx] != '%') && (format[ulIdx] != '\0'); ulIdx++)
        {}

        /* Write this portion of the string. */
        if (ulIdx > 0)
        {
            printfsend((uint8_t *)format, ulIdx);
        }

        format += ulIdx;

        if (*format == '%')
        {
            format++;

            /* Set the digit count to zero, and the fill character to space */
            /* (i.e. to the defaults) */
            ulCount = 0;
            cFill = ' ';

again:
            switch (*format++)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                if ((format[-1] == '0') && (ulCount == 0))
                {
                    cFill = '0';
                }

                ulCount *= 10;
                ulCount += format[-1] - '0';

                goto again;
            }

            case 'c':
            {
                ulValue = va_arg(vaArgP, unsigned long);
                printfsend((uint8_t *)&ulValue, 1);
                break;
            }

            case 'd':
            {
                ulValue = va_arg(vaArgP, unsigned long);
                ulPos = 0;

                if ((long)ulValue < 0)
                {
                    ulValue = -(long)ulValue;
                    ulNeg = 1;
                }
                else
                {
                    ulNeg = 0;
                }

                ulBase = 10;
                goto convert;
            }

            case 's':
            {
                pcStr = (int8_t *)va_arg(vaArgP, char *);

                for (ulIdx = 0; pcStr[ulIdx] != '\0'; ulIdx++)
                {}

                printfsend((uint8_t *)pcStr, ulIdx);

                if (ulCount > ulIdx)
                {
                    ulCount -= ulIdx;
                    while (ulCount--)
                    {
                        printfsend((uint8_t *)" ", 1);
                    }
                }
                break;
            }

            case 'u':
            {
                ulValue = va_arg(vaArgP, unsigned long);
                ulPos = 0;
                ulBase = 10;
                ulNeg = 0;
                goto convert;
            }

            case 'X':
            {
                ulValue = va_arg(vaArgP, unsigned long);
                ulPos = 0;
                ulBase = 16;
                ulNeg = 0;
                HexFormat = 'X';
                goto convert;
            }

            case 'x':

            case 'p':
            {
                ulValue = va_arg(vaArgP, unsigned long);
                ulPos = 0;
                ulBase = 16;
                ulNeg = 0;
                HexFormat = 'x';

convert:
                for (ulIdx = 1;
                        (((ulIdx * ulBase) <= ulValue) &&
                         (((ulIdx * ulBase) / ulBase) == ulIdx));
                        ulIdx *= ulBase, ulCount--)
                {
                }

                if (ulNeg)
                {
                    ulCount--;
                }

                if (ulNeg && (cFill == '0'))
                {
                    pcBuf[ulPos++] = '-';
                    ulNeg = 0;
                }

                if ((ulCount > 1) && (ulCount < 16))
                {
                    for (ulCount--; ulCount; ulCount--)
                    {
                        pcBuf[ulPos++] = cFill;
                    }
                }

                if (ulNeg)
                {
                    pcBuf[ulPos++] = '-';
                }

                for (; ulIdx; ulIdx /= ulBase)
                {
                    if (HexFormat == 'x')
                        pcBuf[ulPos++] = g_pcHex1[(ulValue / ulIdx) % ulBase];//x
                    else
                        pcBuf[ulPos++] = g_pcHex2[(ulValue / ulIdx) % ulBase];//X
                }

                printfsend((uint8_t *)pcBuf, ulPos);
                break;
            }

            case '%':
            {
                printfsend((uint8_t *)format - 1, 1);
                break;
            }

            default:
            {
                printfsend((uint8_t *)"ERROR", 5);
                break;
            }
            }/* switch */
        }/* if */
    }/* while */
    va_end(vaArgP);
}

void printv(uint8_t *buf, uint32_t len, char *s)
{
    uint32_t i = 0;
    uint32_t n = 0;
    MyPrintf("\r\n%s:", s);
    for (i = 0; i < len; i++)
    {
        if (i % 16 == 0)
        {
            MyPrintf("\r\n%08x:", n);
            n += 16;
        }
        MyPrintf("%02x ", buf[i]);

    }
    MyPrintf("\r\n");
}




static void PrintPort_Init(void)
{
    UART_InitTypeDef   UART_InitStruct;
    UART_InitStruct.BaudRate  = PRINT_BAUD;			//Configure serial port baud rate, the baud rate defaults to 128000.
    UART_InitStruct.DataBits  = DATABITS_8B;
    UART_InitStruct.StopBits  = STOPBITS_1;
    UART_InitStruct.Parity    = YC_PARITY_NONE;
    UART_InitStruct.FlowCtrl  = FLOWCTRL_NONE;
    UART_InitStruct.RxMode    = MODE_RX_ENABLE;
    UART_InitStruct.SmartCard = SMARTCARD_DISABLE;
    UART_InitStruct.CommMode  = MODE_DUPLEX;

    if (PrintPort_Struct.PrintUart == MUART0)
    {
        GPIO_Config(PrintPort_Struct.PrintRX_Port, PrintPort_Struct.PrintRX_Pin, UART0_RXD);
        GPIO_Config(PrintPort_Struct.PrintTX_Port, PrintPort_Struct.PrintTX_Pin, UART0_TXD);
    }
    else if (PrintPort_Struct.PrintUart == MUART1)
    {
        GPIO_Config(PrintPort_Struct.PrintRX_Port, PrintPort_Struct.PrintRX_Pin, UART1_RXD);
        GPIO_Config(PrintPort_Struct.PrintTX_Port, PrintPort_Struct.PrintTX_Pin, UART1_TXD);
    }
    else if (PrintPort_Struct.PrintUart == MUART2)
    {
        GPIO_Config(PrintPort_Struct.PrintRX_Port, PrintPort_Struct.PrintRX_Pin, UART2_RXD);
        GPIO_Config(PrintPort_Struct.PrintTX_Port, PrintPort_Struct.PrintTX_Pin, UART2_TXD);
    }
    else if (PrintPort_Struct.PrintUart == MUART3)
    {
        GPIO_Config(PrintPort_Struct.PrintRX_Port, PrintPort_Struct.PrintRX_Pin, UART3_RXD);
        GPIO_Config(PrintPort_Struct.PrintTX_Port, PrintPort_Struct.PrintTX_Pin, UART3_TXD);
    }

    UART_Init(PrintPort_Struct.PrintUart, &UART_InitStruct);
    uint8_t print_irq = (PrintPort_Struct.PrintUart - MUART0) / (MUART1 - MUART0);
    NVIC_EnableIRQ((IRQn_Type)(UART0_IRQn + print_irq));
    NVIC_SetPriority((IRQn_Type)(UART0_IRQn + print_irq),1);
}

void PrintPort_Set(UART_TypeDef *UARTx)
{
    PrintPort_Struct.PrintUart = UARTx;

//    if(UARTx == MUART1)
//    {
//        PrintPort_Struct.PrintRX_Port = UART1RX_PORT;
//        PrintPort_Struct.PrintRX_Pin  = UART1RX_IO_PIN;
//        PrintPort_Struct.PrintTX_Port = UART1TX_PORT;
//        PrintPort_Struct.PrintTX_Pin  = UART1TX_IO_PIN;
//    }
}

void Board_Init(void)
{
    /*fpga io func sel*/
#if (BOARD_TYPE == FPGA_BOARD)

    uint8_t fpga_io_func_sel_list[][2] =
    {
#ifdef __SPI0_FLASH_FPGA__
        {0x02,0x01},
        {0x08,0x01},
        {0x21,0x40},
#endif

        {0x00,0x00},

#ifdef __SPI1_FLASH_FPGA__
        {0x05,0x01},
        {0x08,0x01},
        {0x21,0x80},
#endif
#ifdef __SCANNER_BF3007_BCTC_FPGA__
        {0x01,0x01}, //func_sel1: ALT1 psram
        {0x08,0x01}, //func_sel8: ALT1 tft
        {0x09,0x01}, //func_sel9: ALT1 tft led
        {0x02,0x01}, //func_sel9: ALT1 spia
        {0x21,0x04}, //spi_sel:tft_spi_sel: SPIy
        {0x20,0x02}, //iic_sel:iic0_sel: fingerprint i2c
        {0x04,0x01}, //sel iica
        {0x06,0x02}, //func_sel6: ALT2 fingerprint DCMI
        {0x07,0x01}, //alt1 buzzer
#endif
    };
    for(uint8_t i = 0; i < (sizeof(fpga_io_func_sel_list)/2); i ++)
    {
        FPGA_reg_write(fpga_io_func_sel_list[i][0],fpga_io_func_sel_list[i][1]);
    }

#endif

    /*print init*/
    PrintPort_Init();
}

void _assert_handler(const char *file, int line, const char *func)
{
#if defined (SDK_DEBUG)
    if(PRINTPORT->CTRL.bit.RX_EN == MODE_RX_ENABLE) /*check printuart is init*/
    {
        MyPrintf("Assert trigger at file: %s line:%d func: %s\n ", file, line, func);
    }
#endif
    while (1);
}
