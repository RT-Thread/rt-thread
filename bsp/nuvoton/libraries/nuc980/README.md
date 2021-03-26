# NUC980 Series

## Supported drivers

| Peripheral | rt_device_class_type | Device name |
| ------ | ----  | :------:  |
| ADC | RT_Device_Class_Miscellaneous (ADC) | ***adc*** |
| CAN | RT_Device_Class_CAN | ***can[0-3]*** |
| CRYPTO | RT_Device_Class_Miscellaneous (HW Crypto) | ***hwcryto*** |
| EBI | N/A | ***N/A*** |
| EMAC | RT_Device_Class_NetIf | ***e[0-1]*** |
| GPIO | RT_Device_Class_Miscellaneous (Pin) | ***gpio*** |
| I2C | RT_Device_Class_I2CBUS | ***i2c[0-3]*** |
| I2S | RT_Device_Class_Sound | ***sound0*** |
| PDMA | N/A | ***N/A*** |
| QSPI | RT_Device_Class_SPIBUS | ***qspi[0]*** |
| RTC | RT_Device_Class_RTC | ***rtc*** |
| PWM | RT_Device_Class_Miscellaneous (PWM) | ***pwm[0-1]*** |
| USBH | RT_Device_Class_USBHost | ***usbh*** |
| USBD | RT_Device_Class_USBDevice | ***usbd*** |
| SC (UART function) | RT_Device_Class_Char | ***scuart[0-1]*** |
| SDH | RT_Device_Class_Block | ***sdh[0-1]*** |
| SPI | RT_Device_Class_SPIBUS | ***spi[0-1]*** |
| TIMER | RT_Device_Class_Timer | ***timer[0-5]*** |
| UART | RT_Device_Class_Char | ***uart[0-9]*** |
| WDT | RT_Device_Class_Miscellaneous (Watchdog) | ***wdt*** |

## Resources
* [Download NUC980 TRM][1]

  [1]: https://www.nuvoton.com/resource-download.jsp?tp_GUID=DA05-NUC980-1
