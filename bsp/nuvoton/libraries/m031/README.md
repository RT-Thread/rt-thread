# M031 Series

## Supported drivers

| Peripheral | rt_device_class_type | Device name |
| ------ | ----  | :------:  |
| ADC | RT_Device_Class_Miscellaneous (ADC) | ***adc0*** |
| BPWM | RT_Device_Class_Miscellaneous (PWM) | ***bpwm[0-1]*** |
| BPWM (Capture function)| RT_Device_Class_Miscellaneous (Input capture) | ***bpwm[0-1]i[0-5]*** |
| CLK | RT_Device_Class_PM | ***pm*** |
| CRC | RT_Device_Class_Miscellaneous (HW Crypto) | ***hwcryto*** |
| EBI | N/A | ***N/A*** |
| FMC | FAL | ***N/A*** |
| GPIO | RT_Device_Class_Miscellaneous (Pin) | ***gpio*** |
| GPIO | RT_Device_Class_I2CBUS | ***softi2c0[0-1]*** |
| I2C | RT_Device_Class_I2CBUS | ***i2c[0-1]*** |
| PDMA | N/A | ***N/A*** |
| PWM | RT_Device_Class_Miscellaneous (PWM) | ***pwm[0-1]*** |
| PWM (Capture function) | RT_Device_Class_Miscellaneous (Input capture) | ***pwm[0-1]i[0-5]*** |
| QSPI | RT_Device_Class_SPIBUS | ***qspi0*** |
| RTC | RT_Device_Class_RTC | ***rtc*** |
| SPI | RT_Device_Class_SPIBUS | ***spi0*** |
| SPI (I2S function) | RT_Device_Class_Sound/RT_Device_Class_Pipe | ***spii2s0*** |
| TIMER | RT_Device_Class_Timer | ***timer[0-3]*** |
| TIMER (Capture function) | RT_Device_Class_Miscellaneous (Input capture) | ***timer[0-3]i0*** |
| UART | RT_Device_Class_Char | ***uart[0-7]*** |
| USBD | RT_Device_Class_USBDevice | ***usbd*** |
| USCI (I2C function) | RT_Device_Class_I2CBUS | ***ui2c[0-1]*** |
| USCI (SPI function) | RT_Device_Class_SPIBUS | ***uspi[0-1]*** |
| USCI (UART function) | RT_Device_Class_Char | ***uuart[0-1]*** |
| WDT | RT_Device_Class_Miscellaneous (Watchdog) | ***wdt*** |


## Resources
* [Download M031 TRM](https://www.nuvoton.com/resource-download.jsp?tp_GUID=DA05-M031)
