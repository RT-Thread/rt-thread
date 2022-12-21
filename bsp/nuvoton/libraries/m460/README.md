# M460 Series

## Supported drivers

| Peripheral | rt_device_class_type | Device name |
| ------ | ----  | :------:  |
| BPWM | RT_Device_Class_Miscellaneous (PWM) | ***bpwm[0-1]*** |
| BPWM (Capture function)| RT_Device_Class_Miscellaneous (Input capture) | ***bpwm[0-1]i[0-5]*** |
| CANFD | RT_Device_Class_CAN | ***canfd[0-3]*** |
| CCAP | RT_Device_Class_Miscellaneous | ***ccap0*** |
| CRC | RT_Device_Class_Miscellaneous (HW Crypto) | ***hwcryto*** |
| CRYPTO | RT_Device_Class_Miscellaneous (HW Crypto) | ***hwcryto*** |
| DAC | RT_Device_Class_Miscellaneous (DAC) | ***dac[0-1]*** |
| EADC | RT_Device_Class_Miscellaneous (ADC) | ***eadc[0-1]*** |
| EBI | N/A | ***N/A*** |
| ECAP | RT_Device_Class_Miscellaneous (Input capture) | ***ecap[0-1]i[0-2]*** |
| EMAC | RT_Device_Class_NetIf | ***e0*** |
| EPWM | RT_Device_Class_Miscellaneous (PWM) | ***epwm[0-1]*** |
| EPWM (Capture function) | RT_Device_Class_Miscellaneous (Input capture) | ***epwm[0-1]i[0-5]*** |
| EQEI | RT_Device_Class_Miscellaneous (Pulse encoder) | ***eqei[0-3]*** |
| FMC | FAL | ***N/A*** |
| GPIO | RT_Device_Class_Miscellaneous (Pin) | ***gpio*** |
| GPIO | RT_Device_Class_I2CBUS | ***softi2c0[0-1]*** |
| HSOTG | RT_Device_Class_USBHost/RT_Device_Class_USBDevice | ***N/A*** |
| HSUSBD | RT_Device_Class_USBDevice | ***usbd*** |
| I2C | RT_Device_Class_I2CBUS | ***i2c[0-4]*** |
| I2S | RT_Device_Class_Sound/RT_Device_Class_Pipe | ***sound[0, 1]*** |
| PDMA | N/A | ***N/A*** |
| QSPI | RT_Device_Class_SPIBUS | ***qspi[0-1]*** |
| RTC | RT_Device_Class_RTC | ***rtc*** |
| SC (UART function) | RT_Device_Class_Char | ***scuart[0-2]*** |
| SDH | RT_Device_Class_Block | ***sdh[0-1]*** |
| SDIO | RT_Device_Class_Sdio | ***sdio[0-1]*** |
| SPI | RT_Device_Class_SPIBUS | ***spi[0-10]*** |
| SPI (I2S function) | RT_Device_Class_Sound/RT_Device_Class_Pipe | ***spii2s[0-10]*** |
| TIMER | RT_Device_Class_Timer | ***timer[0-3]*** |
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
* [Download M460 TRM][1]

  [1]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=DA05-M460
