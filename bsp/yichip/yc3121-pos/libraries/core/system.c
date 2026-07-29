/*
File Name    : system.c
Author       : Yichip
Version      : V1.0
Date         : 2019/12/4
Description  : none.
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

static const int8_t *const g_pcHex1 = "0123456789abcdef";
static const int8_t *const g_pcHex2 = "0123456789ABCDEF";


void printfsend(UART_TypeDef UARTx, uint8_t *buf, int len)
{
    uint8_t printbuf[256];
    for (int i = 0; i < len; i++)
    {
        printbuf[i] = buf[i];
    }

    UART_SendBuf(UARTx, printbuf, len);
}

void MyPrintf(char *format, ...)
{
    uint32_t ulIdx, ulValue, ulPos, ulCount, ulBase, ulNeg;
    int8_t *pcStr, pcBuf[16], cFill;
    char HexFormat;
    va_list vaArgP;

    va_start(vaArgP, format);

    while (*format)
    {
        // Find the first non-% character, or the end of the string.
        for (ulIdx = 0; (format[ulIdx] != '%') && (format[ulIdx] != '\0'); ulIdx++)
        {
        }

        // Write this portion of the string.
        if (ulIdx > 0)
        {
            printfsend(UART0, (uint8_t *)format, ulIdx);
        }

        format += ulIdx;

        if (*format == '%')
        {
            format++;

            // Set the digit count to zero, and the fill character to space
            // (i.e. to the defaults).
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
                printfsend(UART0, (uint8_t *)&ulValue, 1);
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
                {
                }

                printfsend(UART0, (uint8_t *)pcStr, ulIdx);

                if (ulCount > ulIdx)
                {
                    ulCount -= ulIdx;
                    while (ulCount--)
                    {
                        printfsend(UART0, (uint8_t *)" ", 1);
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
                        pcBuf[ulPos++] = g_pcHex1[(ulValue / ulIdx) % ulBase]; //x
                    else
                        pcBuf[ulPos++] = g_pcHex2[(ulValue / ulIdx) % ulBase]; //X
                }

                printfsend(UART0, (uint8_t *)pcBuf, ulPos);
                break;
            }

            case '%':
            {
                printfsend(UART0, (uint8_t *)format - 1, 1);
                break;
            }

            default:
            {
                printfsend(UART0, (uint8_t *)"ERROR", 5);
                break;
            }
            } //switch
        }     //if
    }         //while
    va_end(vaArgP);
}

void printv(uint8_t *buf, uint32_t len, uint8_t *s)
{
    uint32_t i = 0;
    uint32_t n = 0;
    MyPrintf("\r\n %s:", s);
    for (i = 0; i < len; i++)
    {
        if (i % 16 == 0)
        {
            MyPrintf("\r\n%08x:", n);
            n += 16;
        }
        MyPrintf("%02x ", buf[i]);
    }
}

void _assert_handler(const char *file, int line, const char *func)
{
#if defined(SDK_DEBUG)
    MyPrintf("Assert trigger at file: %s line:%d func: %s\n ", file, line, func);
#endif
    while (1);
}
