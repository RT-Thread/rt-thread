# M480 Series

## Supported drivers

| Peripheral | rt_device_class_type | Device name |
| ------ | ----  | :------:  |
| BPWM | RT_Device_Class_Miscellaneous (PWM) | ***bpwm[0-1]*** |
| BPWM (Capture function)| RT_Device_Class_Miscellaneous (Input capture) | ***bpwm[0-1]i[0-5]*** |
| CAN | RT_Device_Class_CAN | ***can[0-1]*** |
| CLK | RT_Device_Class_PM | ***pm*** |
| CRC | RT_Device_Class_Miscellaneous (HW Crypto) | ***hwcryto*** |
| CRYPTO | RT_Device_Class_Miscellaneous (HW Crypto) | ***hwcryto*** |
| EADC | RT_Device_Class_Miscellaneous (ADC) | ***eadc[0-1]*** |
| EBI | N/A | ***N/A*** |
| ECAP | RT_Device_Class_Miscellaneous (Input capture) | ***ecap[0-1]i[0-2]*** |
| EMAC | RT_Device_Class_NetIf | ***e0*** |
| EPWM | RT_Device_Class_Miscellaneous (PWM) | ***epwm[0-1]*** |
| EPWM (Capture function) | RT_Device_Class_Miscellaneous (Input capture) | ***epwm[0-1]i[0-5]*** |
| FMC | FAL | ***N/A*** |
| GPIO | RT_Device_Class_Miscellaneous (Pin) | ***gpio*** |
| GPIO | RT_Device_Class_I2CBUS | ***softi2c0[0-1]*** |
| HSOTG | RT_Device_Class_USBHost/RT_Device_Class_USBDevice | ***N/A*** |
| HSUSBD | RT_Device_Class_USBDevice | ***usbd*** |
| I2C | RT_Device_Class_I2CBUS | ***i2c[0-2]*** |
| I2S | RT_Device_Class_Sound/RT_Device_Class_Pipe | ***sound0*** |
| PDMA | N/A | ***N/A*** |
| QEI | RT_Device_Class_Miscellaneous (Pulse encoder) | ***qei[0-1]*** |
| QSPI | RT_Device_Class_SPIBUS | ***qspi[0-1]*** |
| RTC | RT_Device_Class_RTC | ***rtc*** |
| SC (UART function) | RT_Device_Class_Char | ***scuart[0-2]*** |
| SDH | RT_Device_Class_Block | ***sdh[0-1]*** |
| SPI | RT_Device_Class_SPIBUS | ***spi[0-3]*** |
| SPI (I2S function) | RT_Device_Class_Sound/RT_Device_Class_Pipe | ***spii2s[0-3]*** |
| TIMER | RT_Device_Class_Timer | ***timer[0-3]*** |
| TIMER (Capture function) | RT_Device_Class_Miscellaneous (Input capture) | ***timer[0-3]i0*** |
| TIMER (PWM function) | RT_Device_Class_Miscellaneous (PWM) | ***tpwm[0-3]*** |
| TRNG | RT_Device_Class_Miscellaneous (HW Crypto) | ***hwcryto*** |
| UART | RT_Device_Class_Char | ***uart[0-7]*** |
| USBD | RT_Device_Class_USBDevice | ***usbd*** |
| USBH, HSUSBH | RT_Device_Class_USBHost | ***usbh*** |
| USCI (I2C function) | RT_Device_Class_I2CBUS | ***ui2c[0-1]*** |
| USCI (SPI function) | RT_Device_Class_SPIBUS | ***uspi[0-1]*** |
| USCI (UART function) | RT_Device_Class_Char | ***uuart[0-1]*** |
| WDT | RT_Device_Class_Miscellaneous (Watchdog) | ***wdt*** |

## Resources
* [Download M480 TRM][1]

  [1]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=DA05-M480
