// See LICENSE for license details.

#ifndef _SIFIVE_HIFIVE1_H
#define _SIFIVE_HIFIVE1_H

#include <stdint.h>

/****************************************************************************
 * GPIO Connections
 *****************************************************************************/

// These are the GPIO bit offsets for the RGB LED on HiFive1 Board.
// These are also mapped to RGB LEDs on the Freedom E300 Arty
// FPGA
// Dev Kit.

#define RED_LED_OFFSET   22
#define GREEN_LED_OFFSET 19
#define BLUE_LED_OFFSET  21

// These are the GPIO bit offsets for the differen digital pins
// on the headers for both the HiFive1 Board and the Freedom E300 Arty FPGA Dev Kit.
#define PIN_0_OFFSET 16
#define PIN_1_OFFSET 17
#define PIN_2_OFFSET 18
#define PIN_3_OFFSET 19
#define PIN_4_OFFSET 20
#define PIN_5_OFFSET 21
#define PIN_6_OFFSET 22
#define PIN_7_OFFSET 23
#define PIN_8_OFFSET 0
#define PIN_9_OFFSET 1
#define PIN_10_OFFSET 2
#define PIN_11_OFFSET 3
#define PIN_12_OFFSET 4
#define PIN_13_OFFSET 5
//#define PIN_14_OFFSET 8 //This pin is not connected on either board.
#define PIN_15_OFFSET 9
#define PIN_16_OFFSET 10
#define PIN_17_OFFSET 11
#define PIN_18_OFFSET 12
#define PIN_19_OFFSET 13

// These are *PIN* numbers, not
// GPIO Offset Numbers.
#define PIN_SPI1_SCK    (13u)
#define PIN_SPI1_MISO   (12u)
#define PIN_SPI1_MOSI   (11u)
#define PIN_SPI1_SS0    (10u)
#define PIN_SPI1_SS1    (14u) 
#define PIN_SPI1_SS2    (15u)
#define PIN_SPI1_SS3    (16u)

#define SS_PIN_TO_CS_ID(x) \
  ((x==PIN_SPI1_SS0 ? 0 :		 \
    (x==PIN_SPI1_SS1 ? 1 :		 \
     (x==PIN_SPI1_SS2 ? 2 :		 \
      (x==PIN_SPI1_SS3 ? 3 :		 \
       -1))))) 


// These buttons are present only on the Freedom E300 Arty Dev Kit.
#ifdef HAS_BOARD_BUTTONS
#define BUTTON_0_OFFSET 15
#define BUTTON_1_OFFSET 30
#define BUTTON_2_OFFSET 31

#define INT_DEVICE_BUTTON_0 (INT_GPIO_BASE + BUTTON_0_OFFSET)
#define INT_DEVICE_BUTTON_1 (INT_GPIO_BASE + BUTTON_1_OFFSET)
#define INT_DEVICE_BUTTON_2 (INT_GPIO_BASE + BUTTON_2_OFFSET)

#endif

#define HAS_HFXOSC 1
#define HAS_LFROSC_BYPASS 1

#define RTC_FREQ 32768

void write_hex(int fd, unsigned long int hex);

#endif /* _SIFIVE_HIFIVE1_H */
