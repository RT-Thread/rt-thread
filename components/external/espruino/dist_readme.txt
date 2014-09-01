 _____                 _                                                        
|   __|___ ___ ___ _ _|_|___ ___                                                
|   __|_ -| . |  _| | | |   | . |                                               
|_____|___|  _|_| |___|_|_|_|___|                                               
          |_|                                                               
   Copyright 2013 Gordon Williams
                                               
http://www.espruino.com

--------------------------------------------------------------

There are a few different binaries in this ZIP file, for different
types of Microcontroller:

espruino_#v##_hystm32_24_ve.bin 
   - 'HY'STM32F103VET6 ARM with 2.4" LCD display
     This is available from eBay

espruino_#v##_hystm32_28_rb.bin 
   - 'HY'STM32F103RBT6 ARM with 2.8" LCD display
     This is available from eBay

espruino_#v##_hystm32_32_vc.bin 
   - 'HY'STM32F103VCT6 ARM with 3.2" LCD display
     This is available from eBay
      
espruino_#v##_olimexino_stm32.bin
   - You will need to overwrite the Maple bootloader to install this.
     Espruino is now too large to fit in flash alongside it.
   - Olimexino-STM32 Arduino form factor board
   - Leaf Labs Maple Arduino form factor board

espruino_#v##_stm32vldiscovery.bin
   - STM32VLDISCOVERY board

espruino_#v##_stm32f3discovery.bin
   - STM32F3DISCOVERY board
   
espruino_#v##_stm32f4discovery.bin
   - STM32F4DISCOVERY board

espruino_#v##_raspberrypi
   - Raspberry Pi executable (just copy it to the device and run it)
   NOTE: There is GPIO support (which requires you to run Espruino as root)
   however there is no Serial, SPI, OneWire or I2C support at the moment so
   you're pretty limited!

For information on devices, and on how to flash these binary files on to 
each device, please see our website, http://www.espruino.com

NOTES:

* On the STM32F4DISCOVERY the default USART is USART2 (because
USART1 shares some pins with USB). This means you must connect
serial connections to PA2/PA3 NOT PA9/PA10 as you would for
the STM32VLDISCOVERY.

