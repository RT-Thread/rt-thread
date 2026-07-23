/**
********************************************************************************
* @file    target.h
* @author  Application Team
* @version V1.1.0
* @date    2019-10-28
* @brief   Register define
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE 
* TIME. AS A RESULT, XXXXX SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
********************************************************************************
*/

#ifndef TARGET_H
#define TARGET_H

#ifdef __cplusplus
extern "C" {
#endif


/** @addtogroup Configuration_of_CMSIS
  * @{
  */


typedef enum {ERROR = 0, SUCCESS = !ERROR, RESET = 0, SET = !RESET, DISABLE = 0, ENABLE = !DISABLE} TypeState, EventStatus, ControlStatus, FlagStatus,  ErrStatus;

/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum {
/* =======================================  ARM Cortex-M0 Specific Interrupt Numbers  ======================================== */
  Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
  NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
  HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
  SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
  PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
  SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */
/* ===========================================  target Specific Interrupt Numbers  =========================================== */
  PMU_IRQn                  =   0,              /*!< 0  PMU                                                                    */
  RTC_IRQn                  =   1,              /*!< 1  RTC                                                                    */
  U32K0_IRQn                =   2,              /*!< 2  U32K0                                                                  */
  U32K1_IRQn                =   3,              /*!< 3  U32K1                                                                  */
  I2C_IRQn                  =   4,              /*!< 4  I2C                                                                    */
  SPI1_IRQn                 =   5,              /*!< 5  SPI1                                                                   */
  UART0_IRQn                =   6,              /*!< 6  UART0                                                                  */
  UART1_IRQn                =   7,              /*!< 7  UART1                                                                  */
  UART2_IRQn                =   8,              /*!< 8  UART2                                                                  */
  UART3_IRQn                =   9,              /*!< 9  UART3                                                                  */
  UART4_IRQn                =  10,              /*!< 10 UART4                                                                  */
  UART5_IRQn                =  11,              /*!< 11 UART5                                                                  */
  ISO78160_IRQn             =  12,              /*!< 12 ISO78160                                                               */
  ISO78161_IRQn             =  13,              /*!< 13 ISO78161                                                               */
  TMR0_IRQn                 =  14,              /*!< 14 TMR0                                                                   */
  TMR1_IRQn                 =  15,              /*!< 15 TMR1                                                                   */
  TMR2_IRQn                 =  16,              /*!< 16 TMR2                                                                   */
  TMR3_IRQn                 =  17,              /*!< 17 TMR3                                                                   */
  PWM0_IRQn                 =  18,              /*!< 18 PWM0                                                                   */
  PWM1_IRQn                 =  19,              /*!< 19 PWM1                                                                   */
  PWM2_IRQn                 =  20,              /*!< 20 PWM2                                                                   */
  PWM3_IRQn                 =  21,              /*!< 21 PWM3                                                                   */
  DMA_IRQn                  =  22,              /*!< 22 DMA                                                                    */
  FLASH_IRQn                =  23,              /*!< 23 FLASH                                                                  */
  ANA_IRQn                  =  24,              /*!< 24 ANA                                                                    */
  SPI2_IRQn                 =  27,              /*!< 27 SPI2                                                                   */
  SPI3_IRQn                 =  28               /*!< 28 SPI3                                                                   */
} IRQn_Type;



/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ===========================  Configuration of the ARM Cortex-M0 Processor and Core Peripherals  =========================== */
#define __CM0_REV                 0x0000U       /*!< CM0 Core Revision                                                         */
#define __NVIC_PRIO_BITS               2        /*!< Number of Bits used for Priority Levels                                   */
#define __Vendor_SysTickConfig         0        /*!< Set to 1 if different SysTick Config is used                              */
#define __MPU_PRESENT                  0        /*!< MPU present or not                                                        */
#define __FPU_PRESENT                  0        /*!< FPU present or not                                                        */


/** @} */ /* End of group Configuration_of_CMSIS */

#include "core_cm0.h"                           /*!< ARM Cortex-M0 processor and core peripherals                              */

#ifndef __IM                                    /*!< Fallback for older CMSIS versions                                         */
  #define __IM   __I
#endif
#ifndef __OM                                    /*!< Fallback for older CMSIS versions                                         */
  #define __OM   __O
#endif
#ifndef __IOM                                   /*!< Fallback for older CMSIS versions                                         */
  #define __IOM  __IO
#endif


/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                            ANA                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief The Analog controller is used to control the analog function of TARGET. (ANA)
  */

typedef struct {                                /*!< (@ 0x40014200) ANA Structure                                              */
  __IOM uint32_t  REG0;                         /*!< (@ 0x00000000) Analog register 0.                                         */
  __IOM uint32_t  REG1;                         /*!< (@ 0x00000004) Analog register 1.                                         */
  __IOM uint32_t  REG2;                         /*!< (@ 0x00000008) Analog register 2.                                         */
  __IOM uint32_t  REG3;                         /*!< (@ 0x0000000C) Analog register 3.                                         */
  __IOM uint32_t  REG4;                         /*!< (@ 0x00000010) Analog register 4.                                         */
  __IOM uint32_t  REG5;                         /*!< (@ 0x00000014) Analog register 5.                                         */
  __IOM uint32_t  REG6;                         /*!< (@ 0x00000018) Analog register 6.                                         */
  __IOM uint32_t  REG7;                         /*!< (@ 0x0000001C) Analog register 7.                                         */
  __IOM uint32_t  REG8;                         /*!< (@ 0x00000020) Analog register 8.                                         */
  __IOM uint32_t  REG9;                         /*!< (@ 0x00000024) Analog register 9.                                         */
  __IOM uint32_t  REGA;                         /*!< (@ 0x00000028) Analog register 10.                                        */
  __IOM uint32_t  REGB;                         /*!< (@ 0x0000002C) Analog register 11.                                        */
  __IOM uint32_t  REGC;                         /*!< (@ 0x00000030) Analog register 12.                                        */
  __IOM uint32_t  REGD;                         /*!< (@ 0x00000034) Analog register 13.                                        */
  __IOM uint32_t  REGE;                         /*!< (@ 0x00000038) Analog register 14.                                        */
  __IOM uint32_t  REGF;                         /*!< (@ 0x0000003C) Analog register 15.                                        */
  __IOM uint32_t  REG10;                        /*!< (@ 0x00000040) Analog register 16.                                        */
  __IOM uint32_t  REG11;                        /*!< (@ 0x00000044) Analog register 17.                                        */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000050) Analog control register.                                   */
  __IM  uint32_t  CMPOUT;                       /*!< (@ 0x00000054) Comparator result register.                                */
  __IM  uint32_t  RESERVED1;
  __IM  uint32_t  ADCSTATE;                     /*!< (@ 0x0000005C) ADC State register.                                        */
  __IOM uint32_t  INTSTS;                       /*!< (@ 0x00000060) Analog interrupt status register.                          */
  __IOM uint32_t  INTEN;                        /*!< (@ 0x00000064) Analog interrupt enable register.                          */
  __IOM uint32_t  ADCCTRL0;                     /*!< (@ 0x00000068) ADC control register.                                      */
  __IOM uint32_t  CMPCTL;                       /*!< (@ 0x0000006C) CMP1/CMP2 control register.                                */
  __IM  uint32_t  ADCDATA[16];                  /*!< (@ 0x00000070) ADC channel x data register.                               */
  __IOM uint32_t  CMPCNT1;                      /*!< (@ 0x000000B0) Comparator x counter.                                      */
  __IOM uint32_t  CMPCNT2;                      /*!< (@ 0x000000B4) Comparator x counter.                                      */
  __IOM uint32_t  MISC;                         /*!< (@ 0x000000B8) Analog MISC control register.                              */
  __IM  uint32_t  RESERVED2;
  __IM  uint32_t  ADCDOS;                       /*!< (@ 0x000000C0) ANA_ADCDOS.                                                */
  __IM  uint32_t  RESERVED3[7];
  __IM  uint32_t  ADCDATADMA;                   /*!< (@ 0x000000E0) ANA_ADCDATADMA.                                            */
  __IOM uint32_t  CMPTHR;                       /*!< (@ 0x000000E4) CMP1/CMP2 threshold register.                              */
  __IOM uint32_t  ADCCTRL1;                     /*!< (@ 0x000000E8) ANA_ADCCTRL1.                                              */
  __IOM uint32_t  ADCCTRL2;                     /*!< (@ 0x000000EC) ANA_ADCCTRL2.                                              */
  __IM  uint32_t  RESERVED4;
  __IOM uint32_t  ADCDATATHD1_0;                /*!< (@ 0x000000F4) ANA_ADCDATATHD1_0.                                         */
  __IOM uint32_t  ADCDATATHD3_2;                /*!< (@ 0x000000F8) ANA_ADCDATATHD3_2.                                         */
  __IOM uint32_t  ADCDATATHD_CH;                /*!< (@ 0x000000FC) ANA_ADCDATATHD_CH.                                         */
} ANA_Type;                                     /*!< Size = 256 (0x100)                                                        */



/* =========================================================================================================================== */
/* ================                                           CRYPT                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief CRYPT accelerate the sign and verify process speed of ECC. (CRYPT)
  */

typedef struct {                                /*!< (@ 0x40006000) CRYPT Structure                                            */
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000000) CRYPT control register.                                    */
  __IOM uint32_t  PTRA;                         /*!< (@ 0x00000004) CRYPT pointer A.                                           */
  __IOM uint32_t  PTRB;                         /*!< (@ 0x00000008) CRYPT pointer B.                                           */
  __IOM uint32_t  PTRO;                         /*!< (@ 0x0000000C) CRYPT pointer O.                                           */
  __IM  uint32_t  CARRY;                        /*!< (@ 0x00000010) CRYPT carry/borrow bit register.                           */
} CRYPT_Type;                                   /*!< Size = 20 (0x14)                                                          */



/* =========================================================================================================================== */
/* ================                                            DMA                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief DMA(Direct Memory Access) (DMA)
  */

typedef struct {                                /*!< (@ 0x40010000) DMA Structure                                              */
  __IOM uint32_t  IE;                           /*!< (@ 0x00000000) DMA interrupt enable register.                             */
  __IOM uint32_t  STS;                          /*!< (@ 0x00000004) DMA status register.                                       */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  C0CTL;                        /*!< (@ 0x00000010) DMA channel x control register.                            */
  __IOM uint32_t  C0SRC;                        /*!< (@ 0x00000014) DMA source address register.                               */
  __IOM uint32_t  C0DST;                        /*!< (@ 0x00000018) DMA channel x destination register.                        */
  __IOM uint32_t  C0LEN;                        /*!< (@ 0x0000001C) DMA channel x transfer length register.                    */
  __IOM uint32_t  C1CTL;                        /*!< (@ 0x00000020) DMA channel x control register.                            */
  __IOM uint32_t  C1SRC;                        /*!< (@ 0x00000024) DMA source address register.                               */
  __IOM uint32_t  C1DST;                        /*!< (@ 0x00000028) DMA channel x destination register.                        */
  __IOM uint32_t  C1LEN;                        /*!< (@ 0x0000002C) DMA channel x transfer length register.                    */
  __IOM uint32_t  C2CTL;                        /*!< (@ 0x00000030) DMA channel x control register.                            */
  __IOM uint32_t  C2SRC;                        /*!< (@ 0x00000034) DMA source address register.                               */
  __IOM uint32_t  C2DST;                        /*!< (@ 0x00000038) DMA channel x destination register.                        */
  __IOM uint32_t  C2LEN;                        /*!< (@ 0x0000003C) DMA channel x transfer length register.                    */
  __IOM uint32_t  C3CTL;                        /*!< (@ 0x00000040) DMA channel x control register.                            */
  __IOM uint32_t  C3SRC;                        /*!< (@ 0x00000044) DMA source address register.                               */
  __IOM uint32_t  C3DST;                        /*!< (@ 0x00000048) DMA channel x destination register.                        */
  __IOM uint32_t  C3LEN;                        /*!< (@ 0x0000004C) DMA channel x transfer length register.                    */
  __IOM uint32_t  AESCTL;                       /*!< (@ 0x00000050) DMA AES control register.                                  */
  __IM  uint32_t  RESERVED1[3];
  __IOM uint32_t  AESKEY[8];                    /*!< (@ 0x00000060) DMA AES key x register. When mode is AES128,
                                                                    only register KEY3~KEY0 is used. When mode
                                                                    is AES192, only register KEY5~KEY0 is used.
                                                                    When mode is AES256, register KEY7~KEY0
                                                                    is used.                                                   */
} DMA_Type;                                     /*!< Size = 128 (0x80)                                                         */



/* =========================================================================================================================== */
/* ================                                           FLASH                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief FLASH Register (FLASH)
  */

typedef struct {                                /*!< (@ 0x000FFF00) FLASH Structure                                            */
  __IM  uint32_t  RESERVED[42];
  __IOM uint32_t  ICEPROT;                      /*!< (@ 0x000000A8) ICE protect register.                                      */
  __IM  uint32_t  RDPROT;                       /*!< (@ 0x000000AC) Flash read protect status register                         */
  __IOM uint32_t  WRPROT;                       /*!< (@ 0x000000B0) Flash write protect control register                       */
  __IM  uint32_t  RESERVED1[2];
  __IM  uint32_t  STS;                          /*!< (@ 0x000000BC) Flash programming status register.                         */
  __IM  uint32_t  RESERVED2[3];
  __IOM uint32_t  INTSTS;                       /*!< (@ 0x000000CC) FLASH Checksum interrupt status                            */
  __IOM uint32_t  CSSADDR;                      /*!< (@ 0x000000D0) FLASH Checksum start address                               */
  __IOM uint32_t  CSEADDR;                      /*!< (@ 0x000000D4) FLASH Checksum end address.                                */
  __IM  uint32_t  CSVALUE;                      /*!< (@ 0x000000D8) FLASH Checksum value register                              */
  __IOM uint32_t  CSCVALUE;                     /*!< (@ 0x000000DC) FLASH Checksum compare value register.                     */
  __IOM uint32_t  PASS;                         /*!< (@ 0x000000E0) FLASH password register                                    */
  __IOM uint32_t  CTRL;                         /*!< (@ 0x000000E4) FLASH control register.                                    */
  __IOM uint32_t  PGADDR;                       /*!< (@ 0x000000E8) FLASH program address register.                            */
  __IOM uint32_t  PGDATA;                       /*!< (@ 0x000000EC) FLASH program word data register.                          */
  __IM  uint32_t  RESERVED3;
  __IOM uint32_t  SERASE;                       /*!< (@ 0x000000F4) FLASH sector erase control register.                       */
  __IOM uint32_t  CERASE;                       /*!< (@ 0x000000F8) FLASH chip erase control register.                         */
  __IOM uint32_t  DSTB;                         /*!< (@ 0x000000FC) FLASH deep standby control register.                       */
} FLASH_Type;                                   /*!< Size = 256 (0x100)                                                        */



/* =========================================================================================================================== */
/* ================                                           GPIOA                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief The GPIO controller is used to control the GPIOs of TARGET. (GPIOA)
  */

typedef struct {                                /*!< (@ 0x40014010) GPIOA Structure                                            */
  __IOM uint32_t  OEN;                          /*!< (@ 0x00000000) IOA output enable register                                 */
  __IOM uint32_t  IE;                           /*!< (@ 0x00000004) IOA input enable register                                  */
  __IOM uint32_t  DAT;                          /*!< (@ 0x00000008) IOA data register                                          */
  __IOM uint32_t  ATT;                          /*!< (@ 0x0000000C) IOA attribute register                                     */
  __IOM uint32_t  IOAWKUEN;                     /*!< (@ 0x00000010) IOA wake-up enable register                                */
  __IM  uint32_t  STS;                          /*!< (@ 0x00000014) IOA input status register                                  */
  __IOM uint32_t  IOAINTSTS;                    /*!< (@ 0x00000018) IOA interrupt status register.                             */
  __IM  uint32_t  RESERVED[3];
  __IOM uint32_t  SEL;                          /*!< (@ 0x00000028) IOA special function select register.                      */
  __IM  uint32_t  RESERVED1[5];
  __IOM uint32_t  IOANODEG;                     /*!< (@ 0x00000040) IOA no-deglitch control register.                          */
} GPIOA_Type;                                   /*!< Size = 68 (0x44)                                                          */



/* =========================================================================================================================== */
/* ================                                           GPIO                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief The GPIO controller is used to control the GPIOs of TARGET. (GPIO)
  */

typedef struct {                                /*!< (@ 0x40000020) GPIO Structure                                            */
  __IOM uint32_t  OEN;                          /*!< (@ 0x00000000) IO output enable register                                  */
  __IOM uint32_t  IE;                           /*!< (@ 0x00000004) IO input enable register                                   */
  __IOM uint32_t  DAT;                          /*!< (@ 0x00000008) IO data register                                           */
  __IOM uint32_t  ATT;                          /*!< (@ 0x0000000C) IO attribute register                                      */
  __IM  uint32_t  STS;                          /*!< (@ 0x00000010) IO input status register                                   */
} GPIO_Type;                                    /*!< Size = 20 (0x14)                                                          */



/* =========================================================================================================================== */
/* ================                                          GPIOAF                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief The GPIO controller is used to control the GPIOs of TARGET. (GPIOAF)
  */

typedef struct {                                /*!< (@ 0x400000C0) GPIOAF Structure                                           */
  __IOM uint32_t  IOB_SEL;                      /*!< (@ 0x00000000) IOB special function select register.                      */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  IOE_SEL;                      /*!< (@ 0x0000000C) IOE special function select register.                      */
  __IM  uint32_t  RESERVED1[4];
  __IOM uint32_t  IO_MISC;                      /*!< (@ 0x00000020) IO misc. control register.                                 */
} GPIOAF_Type;                                  /*!< Size = 36 (0x24)                                                          */



/* =========================================================================================================================== */
/* ================                                            I2C                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief I2C-Inter Integrated Circuit (I2C)
  */

typedef struct {                                /*!< (@ 0x40010800) I2C Structure                                              */
  __IOM uint32_t  DATA;                         /*!< (@ 0x00000000) I2C data register.                                         */
  __IOM uint32_t  ADDR;                         /*!< (@ 0x00000004) I2C address register.                                      */
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000008) I2C control/status register.                               */
  __IM  uint32_t  STS;                          /*!< (@ 0x0000000C) I2C status register.                                       */
  __IM  uint32_t  RESERVED[2];
  __IOM uint32_t  CTRL2;                        /*!< (@ 0x00000018) I2C interrupt enable register.                             */
} I2C_Type;                                     /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                         ISO7816                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief The ISO7816 controller is an enhance UART protocol which is able to do half-duplex communication on the 2 wires bus. (ISO7816)
  */

typedef struct {                                /*!< (@ 0x40012000) ISO7816 Structure                                         */
  __IM  uint32_t  RESERVED;
  __IOM uint32_t  BAUDDIVL;                     /*!< (@ 0x00000004) ISO7816 baud-rate low byte register                        */
  __IOM uint32_t  BAUDDIVH;                     /*!< (@ 0x00000008) ISO7816 baud-rate high byte register                       */
  __IOM uint32_t  DATA;                         /*!< (@ 0x0000000C) ISO7816 data register.                                     */
  __IOM uint32_t  INFO;                         /*!< (@ 0x00000010) ISO7816 information register.                              */
  __IOM uint32_t  CFG;                          /*!< (@ 0x00000014) ISO7816 control register.                                  */
  __IOM uint32_t  CLK;                          /*!< (@ 0x00000018) ISO7816 clock divider control register.                    */
} ISO7816_Type;                                 /*!< Size = 28 (0x1c)                                                          */



/* =========================================================================================================================== */
/* ================                                            LCD                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief The LCD controller is used to display content on the LCD panel. (LCD)
  */

typedef struct {                                /*!< (@ 0x40002000) LCD Structure                                              */
  __IOM uint32_t  FB[40];                       /*!< (@ 0x00000000) LCD Frame buffer x register                                */
  __IM  uint32_t  RESERVED[24];
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000100) LCD control register.                                      */
  __IOM uint32_t  CTRL2;                        /*!< (@ 0x00000104) LCD control register2.                                     */
  __IOM uint32_t  SEGCTRL0;                     /*!< (@ 0x00000108) LCD segment enable control register 0                      */
  __IOM uint32_t  SEGCTRL1;                     /*!< (@ 0x0000010C) LCD segment enable control register 1                      */
  __IOM uint32_t  SEGCTRL2;                     /*!< (@ 0x00000110) LCD segment enable control register 2                      */
} LCD_Type;                                     /*!< Size = 276 (0x114)                                                        */



/* =========================================================================================================================== */
/* ================                                           MISC1                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief The MISC controller is used to control some special function of TARGET, which will be power-off during sleep and deep-sleep mode. (MISC1)
  */

typedef struct {                                /*!< (@ 0x40013000) MISC1 Structure                                            */
  __IOM uint32_t  SRAMINT;                      /*!< (@ 0x00000000) SRAM Parity Error Interrupt.                               */
  __IOM uint32_t  SRAMINIT;                     /*!< (@ 0x00000004) SRAM initialize register.                                  */
  __IM  uint32_t  PARERR;                       /*!< (@ 0x00000008) SRAM Parity Error address register.                        */
  __IOM uint32_t  IREN;                         /*!< (@ 0x0000000C) IR enable control register.                                */
  __IOM uint32_t  DUTYL;                        /*!< (@ 0x00000010) IR Duty low pulse control register.                        */
  __IOM uint32_t  DUTYH;                        /*!< (@ 0x00000014) IR Duty high pulse control register.                       */
  __IOM uint32_t  IRQLAT;                       /*!< (@ 0x00000018) Cortex M0 IRQ latency control register.                    */
  __IM  uint32_t  RESERVED;
  __IM  uint32_t  HIADDR;                       /*!< (@ 0x00000020) AHB invalid access address.                                */
  __IM  uint32_t  PIADDR;                       /*!< (@ 0x00000024) APB invalid access address.                                */
} MISC1_Type;                                   /*!< Size = 40 (0x28)                                                          */



/* =========================================================================================================================== */
/* ================                                           MISC2                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief MISC2 controller is in retention domain which will be power-off at deep-sleep mode. (MISC2)
  */

typedef struct {                                /*!< (@ 0x40013E00) MISC2 Structure                                            */
  __IOM uint32_t  FLASHWC;                      /*!< (@ 0x00000000) Flash wait cycle register.                                 */
  __IOM uint32_t  CLKSEL;                       /*!< (@ 0x00000004) Clock selection register.                                  */
  __IOM uint32_t  CLKDIVH;                      /*!< (@ 0x00000008) AHB clock divider control register.                        */
  __IOM uint32_t  CLKDIVP;                      /*!< (@ 0x0000000C) APB clock divider control register.                        */
  __IOM uint32_t  HCLKEN;                       /*!< (@ 0x00000010) AHB clock enable control register.                         */
  __IOM uint32_t  PCLKEN;                       /*!< (@ 0x00000014) APB clock enable control register.                         */
} MISC2_Type;                                   /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                            PMU                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Power Management Unit. (PMU)
  */

typedef struct {                                /*!< (@ 0x40014000) PMU Structure                                              */
  __IOM uint32_t  DSLEEPEN;                     /*!< (@ 0x00000000) PMU deep sleep enable register.                            */
  __IOM uint32_t  DSLEEPPASS;                   /*!< (@ 0x00000004) PMU deep sleep password register.                          */
  __IOM uint32_t  CONTROL;                      /*!< (@ 0x00000008) PMU control register.                                      */
  __IOM uint32_t  STS;                          /*!< (@ 0x0000000C) PMU Status register.                                       */
  __IM  uint32_t  RESERVED[12];
  __IOM uint32_t  WDTPASS;                      /*!< (@ 0x00000040) Watch dog timing unlock register.                          */
  __IOM uint32_t  WDTEN;                        /*!< (@ 0x00000044) Watch dog timer enable register.                           */
  __IOM uint32_t  WDTCLR;                       /*!< (@ 0x00000048) Watch dog timer clear register.                            */
  __IM  uint32_t  RESERVED1[237];
  __IOM uint32_t  RAM[64];                      /*!< (@ 0x00000400) PMU 32 bits Retention RAM x.                               */
} PMU_Type;                                     /*!< Size = 1280 (0x500)                                                       */



/* =========================================================================================================================== */
/* ================                                           PWM                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief Timers are 16 bits timers with PWM and capture function. (PWM)
  */

typedef struct {                                /*!< (@ 0x40012900) PWM Structure                                             */
  __IOM uint32_t  CTL;                          /*!< (@ 0x00000000) Control register of PWM Timer 0                            */
  __IM  uint32_t  TAR;                          /*!< (@ 0x00000004) Current count register of PWM Timer x.                     */
  __IOM uint32_t  CCTL[3];                      /*!< (@ 0x00000008) Compare/capture control register x(x=0~3) for
                                                                    PWM timer x.                                               */
  __IOM uint32_t  CCR[3];                       /*!< (@ 0x00000014) Compare/capture data register x for PWM timer
                                                                    x.                                                         */
} PWM_Type;                                     /*!< Size = 32 (0x20)                                                          */



/* =========================================================================================================================== */
/* ================                                          PWM_SEL                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief Timers are 16 bits timers with PWM and capture function. (PWM_SEL)
  */

typedef struct {                                /*!< (@ 0x400129F0) PWM_SEL Structure                                          */
  __IOM uint32_t  O_SEL;                        /*!< (@ 0x00000000) PWM output selection register.                             */
  __IOM uint32_t  I_SEL01;                      /*!< (@ 0x00000004) Input of PWM0 and PWM1 selection register.                 */
  __IOM uint32_t  I_SEL23;                      /*!< (@ 0x00000008) Input of PWM2 and PWM3 selection register.                 */
} PWM_SEL_Type;                                 /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                            RTC                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief The RTC controller is used to control time calculation and RTC auto calibration function. (RTC)
  */

typedef struct {                                /*!< (@ 0x40014800) RTC Structure                                              */
  __IOM uint32_t  SEC;                          /*!< (@ 0x00000000) RTC second register                                        */
  __IOM uint32_t  MIN;                          /*!< (@ 0x00000004) RTC minute register                                        */
  __IOM uint32_t  HOUR;                         /*!< (@ 0x00000008) RTC hour register                                          */
  __IOM uint32_t  DAY;                          /*!< (@ 0x0000000C) RTC day register                                           */
  __IOM uint32_t  WEEK;                         /*!< (@ 0x00000010) RTC week register                                          */
  __IOM uint32_t  MON;                          /*!< (@ 0x00000014) RTC mon register                                           */
  __IOM uint32_t  YEAR;                         /*!< (@ 0x00000018) RTC year register                                          */
  __IOM uint32_t  TIME;                         /*!< (@ 0x0000001C) RTC accurate second/millisecond register                   */
  __IOM uint32_t  WKUSEC;                       /*!< (@ 0x00000020) RTC wake-up second register.                               */
  __IOM uint32_t  WKUMIN;                       /*!< (@ 0x00000024) RTC wake-up minute register                                */
  __IOM uint32_t  WKUHOUR;                      /*!< (@ 0x00000028) RTC wake-up hour register                                  */
  __IOM uint32_t  WKUCNT;                       /*!< (@ 0x0000002C) RTC wake-up counter register                               */
  __IOM uint32_t  CAL;                          /*!< (@ 0x00000030) RTC calibration register                                   */
  __IOM uint32_t  DIV;                          /*!< (@ 0x00000034) RTC calibration register                                   */
  __IOM uint32_t  CTL;                          /*!< (@ 0x00000038) RTC PLL divider control register.                          */
  __IOM uint32_t  ITV;                          /*!< (@ 0x0000003C) RTC wake-up interval control                               */
  __IOM uint32_t  SITV;                         /*!< (@ 0x00000040) RTC wake-up second interval control                        */
  __IOM uint32_t  PWD;                          /*!< (@ 0x00000044) RTC password control register.                             */
  __IOM uint32_t  CE;                           /*!< (@ 0x00000048) RTC write enable control register.                         */
  __IM  uint32_t  LOAD;                         /*!< (@ 0x0000004C) RTC read enable control register                           */
  __IOM uint32_t  INTSTS;                       /*!< (@ 0x00000050) RTC interrupt status control register                      */
  __IOM uint32_t  INTEN;                        /*!< (@ 0x00000054) RTC interrupt enable control register                      */
  __IOM uint32_t  PSCA;                         /*!< (@ 0x00000058) RTC clock pre-scaler control register.                     */
  __IM  uint32_t  RESERVED[10];
  __IOM uint32_t  ACTI;                         /*!< (@ 0x00000084) RTC auto-calibration center temperature control
                                                                    register.                                                  */
  __IOM uint32_t  ACF200;                       /*!< (@ 0x00000088) RTC auto-calibration 200*frequency control register.       */
  __IM  uint32_t  RESERVED1;
  __IOM uint32_t  ACP0;                         /*!< (@ 0x00000090) RTC parameter P0 register.                                 */
  __IOM uint32_t  ACP1;                         /*!< (@ 0x00000094) RTC parameter P1 register.                                 */
  __IOM uint32_t  ACP2;                         /*!< (@ 0x00000098) RTC parameter P2 register.                                 */
  __IM  uint32_t  ACP3;                         /*!< (@ 0x0000009C) RTC parameter P3 register.                                 */
  __IOM uint32_t  ACP4;                         /*!< (@ 0x000000A0) RTC parameter P4 register.                                 */
  __IOM uint32_t  ACP5;                         /*!< (@ 0x000000A4) RTC parameter P5 register.                                 */
  __IOM uint32_t  ACP6;                         /*!< (@ 0x000000A8) RTC parameter P6 register.                                 */
  __IOM uint32_t  ACP7;                         /*!< (@ 0x000000AC) RTC parameter P7 register.                                 */
  __IOM uint32_t  ACK[5];                       /*!< (@ 0x000000B0) RTC auto-calibration parameter Kx control register.        */
  __IM  uint32_t  RESERVED2[2];
  __IM  uint32_t  WKUCNTR;                      /*!< (@ 0x000000CC) This register is used to represent the current
                                                                    WKUCNT value.                                              */
  __IOM uint32_t  ACKTEMP;                      /*!< (@ 0x000000D0) RTC auto-calibration k temperature section control
                                                                    register.                                                  */
  __IOM uint32_t  ALARMTIME;                    /*!< (@ 0x000000D4) RTC alarm accurate second/millisecond.                     */
  __IOM uint32_t  ALARMSEC;                     /*!< (@ 0x000000D8) RTC alarm inaccurate second                                */
  __IOM uint32_t  ALARMMIN;                     /*!< (@ 0x000000DC) RTC alarm minute                                           */
  __IOM uint32_t  ALARMHOUR;                    /*!< (@ 0x000000E0) RTC alarm hour                                             */
  __IOM uint32_t  ALARMCTL;                     /*!< (@ 0x000000E4) RTC alarm control                                          */
  __IOM uint32_t  ADCUCALK;                     /*!< (@ 0x000000E8) RTC ADC Ucal K coefficients                                */
  __IOM uint32_t  ADCMACTL;                     /*!< (@ 0x000000EC) RTC ADC control                                            */
} RTC_Type;                                     /*!< Size = 240 (0xf0)                                                         */



/* =========================================================================================================================== */
/* ================                                           SPI                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief SPI(Serial Peripheral Interface). (SPI)
  */

typedef struct {                                /*!< (@ 0x40011000) SPI Structure                                             */
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000000) SPI Control Register.                                      */
  __IOM uint32_t  TXSTS;                        /*!< (@ 0x00000004) SPI Transmit Status Register.                              */
  __IOM uint32_t  TXDAT;                        /*!< (@ 0x00000008) SPI Transmit FIFO register.                                */
  __IOM uint32_t  RXSTS;                        /*!< (@ 0x0000000C) SPI Receive Status Register.                               */
  __IM  uint32_t  RXDAT;                        /*!< (@ 0x00000010) SPI Receive FIFO Register.                                 */
  __IOM uint32_t  MISC;                         /*!< (@ 0x00000014) SPI Misc. Control Register.                                */
} SPI_Type;                                     /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                           TMR                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief General purpose 32 bits timer, which are used to generate regulate interrupt for CM0. (TMR)
  */

typedef struct {                                /*!< (@ 0x40012800) TMR Structure                                             */
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000000) Control register of Timer x                                */
  __IOM uint32_t  VALUE;                        /*!< (@ 0x00000004) Current count register of Timer x                          */
  __IOM uint32_t  RELOAD;                       /*!< (@ 0x00000008) Reload register of Timer x.                                */
  __IOM uint32_t  INTSTS;                       /*!< (@ 0x0000000C) Interrupt status register of Timer x.                      */
} TMR_Type;                                     /*!< Size = 16 (0x10)                                                          */



/* =========================================================================================================================== */
/* ================                                           UART                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief UART(Universal Asynchronous Receiver/Transmitter). (UART)
  */

typedef struct {                                /*!< (@ 0x40011800) UART Structure                                            */
  __IOM uint32_t  DATA;                         /*!< (@ 0x00000000) UART data register.                                        */
  __IOM uint32_t  STATE;                        /*!< (@ 0x00000004) UART status register.                                      */
  __IOM uint32_t  CTRL;                         /*!< (@ 0x00000008) UART control register.                                     */
  __IOM uint32_t  INTSTS;                       /*!< (@ 0x0000000C) UART interrupt status register.                            */
  __IOM uint32_t  BAUDDIV;                      /*!< (@ 0x00000010) UART baud rate divide register.                            */
  __IOM uint32_t  CTRL2;                        /*!< (@ 0x00000014) UART control register 2.                                   */
} UART_Type;                                    /*!< Size = 24 (0x18)                                                          */



/* =========================================================================================================================== */
/* ================                                           U32K                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief The UART 32K controller is used to receive data via UART protocol. (U32K)
  */

typedef struct {                                /*!< (@ 0x40014100) U32K Structure                                            */
  __IOM uint32_t  CTRL0;                        /*!< (@ 0x00000000) UART 32K x control register 0.                             */
  __IOM uint32_t  CTRL1;                        /*!< (@ 0x00000004) UART 32K x control register 1.                             */
  __IOM uint32_t  BAUDDIV;                      /*!< (@ 0x00000008) UART 32K x baud rate control register.                     */
  __IM  uint32_t  DATA;                         /*!< (@ 0x0000000C) UART 32K x receive data buffer.                            */
  __IOM uint32_t  STS;                          /*!< (@ 0x00000010) UART 32K x interrupt status register.                      */
} U32K_Type;                                    /*!< Size = 20 (0x14)                                                          */


/** @} */ /* End of group Device_Peripheral_peripherals */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

#define ANA_BASE                    0x40014200UL
#define CRYPT_BASE                  0x40006000UL
#define DMA_BASE                    0x40010000UL
#define FLASH_BASE                  0x000FFF00UL
#define GPIOA_BASE                  0x40014010UL
#define GPIOB_BASE                  0x40000020UL
#define GPIOC_BASE                  0x40000040UL
#define GPIOD_BASE                  0x40000060UL
#define GPIOE_BASE                  0x40000080UL
#define GPIOF_BASE                  0x400000A0UL
#define GPIOAF_BASE                 0x400000C0UL
#define I2C_BASE                    0x40010800UL
#define ISO78160_BASE               0x40012000UL
#define ISO78161_BASE               0x40012040UL
#define LCD_BASE                    0x40002000UL
#define MISC1_BASE                  0x40013000UL
#define MISC2_BASE                  0x40013E00UL
#define PMU_BASE                    0x40014000UL
#define PWM0_BASE                   0x40012900UL
#define PWM1_BASE                   0x40012920UL
#define PWM2_BASE                   0x40012940UL
#define PWM3_BASE                   0x40012960UL
#define PWM_SEL_BASE                0x400129F0UL
#define RTC_BASE                    0x40014800UL
#define SPI1_BASE                   0x40011000UL
#define SPI2_BASE                   0x40015800UL
#define SPI3_BASE                   0x40016000UL
#define TMR0_BASE                   0x40012800UL
#define TMR1_BASE                   0x40012820UL
#define TMR2_BASE                   0x40012840UL
#define TMR3_BASE                   0x40012860UL
#define UART0_BASE                  0x40011800UL
#define UART1_BASE                  0x40011820UL
#define UART2_BASE                  0x40011840UL
#define UART3_BASE                  0x40011860UL
#define UART4_BASE                  0x40011880UL
#define UART5_BASE                  0x400118A0UL
#define U32K0_BASE                  0x40014100UL
#define U32K1_BASE                  0x40014180UL

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define ANA                         ((ANA_Type*)               ANA_BASE)
#define CRYPT                       ((CRYPT_Type*)             CRYPT_BASE)
#define DMA                         ((DMA_Type*)               DMA_BASE)
#define FLASH                       ((FLASH_Type*)             FLASH_BASE)
#define GPIOA                       ((GPIOA_Type*)             GPIOA_BASE)
#define GPIOB                       ((GPIO_Type*)              GPIOB_BASE)
#define GPIOC                       ((GPIO_Type*)              GPIOC_BASE)
#define GPIOD                       ((GPIO_Type*)              GPIOD_BASE)
#define GPIOE                       ((GPIO_Type*)              GPIOE_BASE)
#define GPIOF                       ((GPIO_Type*)              GPIOF_BASE)
#define GPIOAF                      ((GPIOAF_Type*)            GPIOAF_BASE)
#define I2C                         ((I2C_Type*)               I2C_BASE)
#define ISO78160                    ((ISO7816_Type*)           ISO78160_BASE)
#define ISO78161                    ((ISO7816_Type*)           ISO78161_BASE)
#define LCD                         ((LCD_Type*)               LCD_BASE)
#define MISC1                       ((MISC1_Type*)             MISC1_BASE)
#define MISC2                       ((MISC2_Type*)             MISC2_BASE)
#define PMU                         ((PMU_Type*)               PMU_BASE)
#define PWM0                        ((PWM_Type*)               PWM0_BASE)
#define PWM1                        ((PWM_Type*)               PWM1_BASE)
#define PWM2                        ((PWM_Type*)               PWM2_BASE)
#define PWM3                        ((PWM_Type*)               PWM3_BASE)
#define PWM_SEL                     ((PWM_SEL_Type*)           PWM_SEL_BASE)
#define RTC                         ((RTC_Type*)               RTC_BASE)
#define SPI1                        ((SPI_Type*)               SPI1_BASE)
#define SPI2                        ((SPI_Type*)               SPI2_BASE)
#define SPI3                        ((SPI_Type*)               SPI3_BASE)
#define TMR0                        ((TMR_Type*)               TMR0_BASE)
#define TMR1                        ((TMR_Type*)               TMR1_BASE)
#define TMR2                        ((TMR_Type*)               TMR2_BASE)
#define TMR3                        ((TMR_Type*)               TMR3_BASE)
#define UART0                       ((UART_Type*)              UART0_BASE)
#define UART1                       ((UART_Type*)              UART1_BASE)
#define UART2                       ((UART_Type*)              UART2_BASE)
#define UART3                       ((UART_Type*)              UART3_BASE)
#define UART4                       ((UART_Type*)              UART4_BASE)
#define UART5                       ((UART_Type*)              UART5_BASE)
#define U32K0                       ((U32K_Type*)              U32K0_BASE)
#define U32K1                       ((U32K_Type*)              U32K1_BASE)

/** @} */ /* End of group Device_Peripheral_declaration */


/* =========================================================================================================================== */
/* ================                                Pos/Mask Peripheral Section                                ================ */
/* =========================================================================================================================== */


/** @addtogroup PosMask_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                            ANA                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  REG0  ========================================================== */
#define ANA_REG0_ADCFRQSEL_Pos            (0UL)                     /*!< ANA REG0: ADCFRQSEL (Bit 0)                           */
#define ANA_REG0_ADCFRQSEL_Msk            (0x1UL)                   /*!< ANA REG0: ADCFRQSEL (Bitfield-Mask: 0x01)             */
#define ANA_REG0_ADCFRQSEL                ANA_REG0_ADCFRQSEL_Msk
/* =========================================================  REG1  ========================================================== */
#define ANA_REG1_ADCMODESEL_Pos           (7UL)                     /*!< ANA REG1: ADCMODESEL (Bit 7)                          */
#define ANA_REG1_ADCMODESEL_Msk           (0x80UL)                  /*!< ANA REG1: ADCMODESEL (Bitfield-Mask: 0x01)            */
#define ANA_REG1_ADCMODESEL               ANA_REG1_ADCMODESEL_Msk
/* =========================================================  REG2  ========================================================== */
#define ANA_REG2_CMP2REFSEL_Pos           (5UL)                     /*!< ANA REG2: CMP2REFSEL (Bit 5)                          */
#define ANA_REG2_CMP2REFSEL_Msk           (0x20UL)                  /*!< ANA REG2: CMP2REFSEL (Bitfield-Mask: 0x01)            */
#define ANA_REG2_CMP2REFSEL               ANA_REG2_CMP2REFSEL_Msk
#define ANA_REG2_CMP1REFSEL_Pos           (4UL)                     /*!< ANA REG2: CMP1REFSEL (Bit 4)                          */
#define ANA_REG2_CMP1REFSEL_Msk           (0x10UL)                  /*!< ANA REG2: CMP1REFSEL (Bitfield-Mask: 0x01)            */
#define ANA_REG2_CMP1REFSEL               ANA_REG2_CMP1REFSEL_Msk
#define ANA_REG2_CMP2SEL_Pos              (2UL)                     /*!< ANA REG2: CMP2SEL (Bit 2)                             */
#define ANA_REG2_CMP2SEL_Msk              (0xcUL)                   /*!< ANA REG2: CMP2SEL (Bitfield-Mask: 0x03)               */
#define ANA_REG2_CMP2SEL                  ANA_REG2_CMP2SEL_Msk
#define ANA_REG2_CMP1SEL_Pos              (0UL)                     /*!< ANA REG2: CMP1SEL (Bit 0)                             */
#define ANA_REG2_CMP1SEL_Msk              (0x3UL)                   /*!< ANA REG2: CMP1SEL (Bitfield-Mask: 0x03)               */
#define ANA_REG2_CMP1SEL                  ANA_REG2_CMP1SEL_Msk
/* =========================================================  REG3  ========================================================== */
#define ANA_REG3_XOHPDN_Pos               (7UL)                     /*!< ANA REG3: XOHPDN (Bit 7)                              */
#define ANA_REG3_XOHPDN_Msk               (0x80UL)                  /*!< ANA REG3: XOHPDN (Bitfield-Mask: 0x01)                */
#define ANA_REG3_XOHPDN                   ANA_REG3_XOHPDN_Msk
#define ANA_REG3_PLLHPDN_Pos              (6UL)                     /*!< ANA REG3: PLLHPDN (Bit 6)                             */
#define ANA_REG3_PLLHPDN_Msk              (0x40UL)                  /*!< ANA REG3: PLLHPDN (Bitfield-Mask: 0x01)               */
#define ANA_REG3_PLLHPDN                  ANA_REG3_PLLHPDN_Msk
#define ANA_REG3_PLLLPDN_Pos              (5UL)                     /*!< ANA REG3: PLLLPDN (Bit 5)                             */
#define ANA_REG3_PLLLPDN_Msk              (0x20UL)                  /*!< ANA REG3: PLLLPDN (Bitfield-Mask: 0x01)               */
#define ANA_REG3_PLLLPDN                  ANA_REG3_PLLLPDN_Msk
#define ANA_REG3_RCHPD_Pos                (4UL)                     /*!< ANA REG3: RCHPD (Bit 4)                               */
#define ANA_REG3_RCHPD_Msk                (0x10UL)                  /*!< ANA REG3: RCHPD (Bitfield-Mask: 0x01)                 */
#define ANA_REG3_RCHPD                    ANA_REG3_RCHPD_Msk
#define ANA_REG3_BGPPD_Pos                (3UL)                     /*!< ANA REG3: BGPPD (Bit 3)                               */
#define ANA_REG3_BGPPD_Msk                (0x8UL)                   /*!< ANA REG3: BGPPD (Bitfield-Mask: 0x01)                 */
#define ANA_REG3_BGPPD                    ANA_REG3_BGPPD_Msk
#define ANA_REG3_CMP2PDN_Pos              (2UL)                     /*!< ANA REG3: CMP2PDN (Bit 2)                             */
#define ANA_REG3_CMP2PDN_Msk              (0x4UL)                   /*!< ANA REG3: CMP2PDN (Bitfield-Mask: 0x01)               */
#define ANA_REG3_CMP2PDN                  ANA_REG3_CMP2PDN_Msk
#define ANA_REG3_CMP1PDN_Pos              (1UL)                     /*!< ANA REG3: CMP1PDN (Bit 1)                             */
#define ANA_REG3_CMP1PDN_Msk              (0x2UL)                   /*!< ANA REG3: CMP1PDN (Bitfield-Mask: 0x01)               */
#define ANA_REG3_CMP1PDN                  ANA_REG3_CMP1PDN_Msk
/* =========================================================  REG4  ========================================================== */
/* =========================================================  REG5  ========================================================== */
#define ANA_REG5_AVCCLVDETPD_Pos          (6UL)                     /*!< ANA REG5: AVCCLVDETPD (Bit 6)                         */
#define ANA_REG5_AVCCLVDETPD_Msk          (0x40UL)                  /*!< ANA REG5: AVCCLVDETPD (Bitfield-Mask: 0x01)           */
#define ANA_REG5_AVCCLVDETPD              ANA_REG5_AVCCLVDETPD_Msk
#define ANA_REG5_CMP2IT_Pos               (2UL)                     /*!< ANA REG5: CMP2IT (Bit 2)                              */
#define ANA_REG5_CMP2IT_Msk               (0xcUL)                   /*!< ANA REG5: CMP2IT (Bitfield-Mask: 0x03)                */
#define ANA_REG5_CMP2IT                   ANA_REG5_CMP2IT_Msk
#define ANA_REG5_CMP1IT_Pos               (0UL)                     /*!< ANA REG5: CMP1IT (Bit 0)                              */
#define ANA_REG5_CMP1IT_Msk               (0x3UL)                   /*!< ANA REG5: CMP1IT (Bitfield-Mask: 0x03)                */
#define ANA_REG5_CMP1IT                   ANA_REG5_CMP1IT_Msk
/* =========================================================  REG6  ========================================================== */
#define ANA_REG6_BATRTCDISC_Pos           (7UL)                     /*!< ANA REG6: BATRTCDISC (Bit 7)                          */
#define ANA_REG6_BATRTCDISC_Msk           (0x80UL)                  /*!< ANA REG6: BATRTCDISC (Bitfield-Mask: 0x01)            */
#define ANA_REG6_BATRTCDISC               ANA_REG6_BATRTCDISC_Msk
#define ANA_REG6_BAT1DISC_Pos             (6UL)                     /*!< ANA REG6: BAT1DISC (Bit 6)                            */
#define ANA_REG6_BAT1DISC_Msk             (0x40UL)                  /*!< ANA REG6: BAT1DISC (Bitfield-Mask: 0x01)              */
#define ANA_REG6_BAT1DISC                 ANA_REG6_BAT1DISC_Msk
#define ANA_REG6_LCDBMODE_Pos             (0UL)                     /*!< ANA REG6: LCDBMODE (Bit 0)                            */
#define ANA_REG6_LCDBMODE_Msk             (0x1UL)                   /*!< ANA REG6: LCDBMODE (Bitfield-Mask: 0x01)              */
#define ANA_REG6_LCDBMODE                 ANA_REG6_LCDBMODE_Msk
/* =========================================================  REG7  ========================================================== */
/* =========================================================  REG8  ========================================================== */
#define ANA_REG8_AVCCLDOPD_Pos            (7UL)                     /*!< ANA REG8: AVCCLDOPD (Bit 7)                           */
#define ANA_REG8_AVCCLDOPD_Msk            (0x80UL)                  /*!< ANA REG8: AVCCLDOPD (Bitfield-Mask: 0x01)             */
#define ANA_REG8_AVCCLDOPD                ANA_REG8_AVCCLDOPD_Msk
#define ANA_REG8_VDDPVDSEL_Pos            (4UL)                     /*!< ANA REG8: VDDPVDSEL (Bit 4)                           */
#define ANA_REG8_VDDPVDSEL_Msk            (0x70UL)                  /*!< ANA REG8: VDDPVDSEL (Bitfield-Mask: 0x07)             */
#define ANA_REG8_VDDPVDSEL                ANA_REG8_VDDPVDSEL_Msk
#define ANA_REG8_DVCCSEL_Pos              (0UL)                     /*!< ANA REG8: DVCCSEL (Bit 0)                             */
#define ANA_REG8_DVCCSEL_Msk              (0x3UL)                   /*!< ANA REG8: DVCCSEL (Bitfield-Mask: 0x03)               */
#define ANA_REG8_DVCCSEL                  ANA_REG8_DVCCSEL_Msk
/* =========================================================  REG9  ========================================================== */
#define ANA_REG9_VDDDETPD_Pos             (7UL)                     /*!< ANA REG9: VDDDETPD (Bit 7)                            */
#define ANA_REG9_VDDDETPD_Msk             (0x80UL)                  /*!< ANA REG9: VDDDETPD (Bitfield-Mask: 0x01)              */
#define ANA_REG9_VDDDETPD                 ANA_REG9_VDDDETPD_Msk
#define ANA_REG9_PLLHSEL_Pos              (3UL)                     /*!< ANA REG9: PLLHSEL (Bit 3)                             */
#define ANA_REG9_PLLHSEL_Msk              (0x78UL)                  /*!< ANA REG9: PLLHSEL (Bitfield-Mask: 0x0f)               */
#define ANA_REG9_PLLHSEL                  ANA_REG9_PLLHSEL_Msk
#define ANA_REG9_PLLLSEL_Pos              (0UL)                     /*!< ANA REG9: PLLLSEL (Bit 0)                             */
#define ANA_REG9_PLLLSEL_Msk              (0x7UL)                   /*!< ANA REG9: PLLLSEL (Bitfield-Mask: 0x07)               */
#define ANA_REG9_PLLLSEL                  ANA_REG9_PLLLSEL_Msk
/* =========================================================  REGA  ========================================================== */
#define ANA_REGA_VDCINDETPD_Pos           (7UL)                     /*!< ANA REGA: VDCINDETPD (Bit 7)                          */
#define ANA_REGA_VDCINDETPD_Msk           (0x80UL)                  /*!< ANA REGA: VDCINDETPD (Bitfield-Mask: 0x01)            */
#define ANA_REGA_VDCINDETPD               ANA_REGA_VDCINDETPD_Msk
/* =========================================================  REGB  ========================================================== */
#define ANA_REGB_RCLTRIM_Pos              (0UL)                     /*!< ANA REGB: RCLTRIM (Bit 0)                             */
#define ANA_REGB_RCLTRIM_Msk              (0x1fUL)                  /*!< ANA REGB: RCLTRIM (Bitfield-Mask: 0x1f)               */
#define ANA_REGB_RCLTRIM                  ANA_REGB_RCLTRIM_Msk
/* =========================================================  REGC  ========================================================== */
#define ANA_REGC_RCHTRIM_Pos              (0UL)                     /*!< ANA REGC: RCHTRIM (Bit 0)                             */
#define ANA_REGC_RCHTRIM_Msk              (0x3fUL)                  /*!< ANA REGC: RCHTRIM (Bitfield-Mask: 0x3f)               */
#define ANA_REGC_RCHTRIM                  ANA_REGC_RCHTRIM_Msk
/* =========================================================  REGD  ========================================================== */
/* =========================================================  REGE  ========================================================== */
#define ANA_REGE_BKPWREN_Pos              (7UL)                     /*!< ANA REGE: BKPWREN (Bit 7)                             */
#define ANA_REGE_BKPWREN_Msk              (0x80UL)                  /*!< ANA REGE: BKPWREN (Bitfield-Mask: 0x01)               */
#define ANA_REGE_BKPWREN                  ANA_REGE_BKPWREN_Msk
/* =========================================================  REGF  ========================================================== */
#define ANA_REGF_ADTREF3SEL_Pos           (7UL)                     /*!< ANA REGF: ADTREF3SEL (Bit 7)                          */
#define ANA_REGF_ADTREF3SEL_Msk           (0x80UL)                  /*!< ANA REGF: ADTREF3SEL (Bitfield-Mask: 0x01)            */
#define ANA_REGF_ADTREF3SEL               ANA_REGF_ADTREF3SEL_Msk
#define ANA_REGF_ADTREF2SEL_Pos           (6UL)                     /*!< ANA REGF: ADTREF2SEL (Bit 6)                          */
#define ANA_REGF_ADTREF2SEL_Msk           (0x40UL)                  /*!< ANA REGF: ADTREF2SEL (Bitfield-Mask: 0x01)            */
#define ANA_REGF_ADTREF2SEL               ANA_REGF_ADTREF2SEL_Msk
#define ANA_REGF_ADTREF1SEL_Pos           (5UL)                     /*!< ANA REGF: ADTREF1SEL (Bit 5)                          */
#define ANA_REGF_ADTREF1SEL_Msk           (0x20UL)                  /*!< ANA REGF: ADTREF1SEL (Bitfield-Mask: 0x01)            */
#define ANA_REGF_ADTREF1SEL               ANA_REGF_ADTREF1SEL_Msk
#define ANA_REGF_ADTSEL_Pos               (4UL)                     /*!< ANA REGF: ADTSEL (Bit 4)                              */
#define ANA_REGF_ADTSEL_Msk               (0x10UL)                  /*!< ANA REGF: ADTSEL (Bitfield-Mask: 0x01)                */
#define ANA_REGF_ADTSEL                   ANA_REGF_ADTSEL_Msk
#define ANA_REGF_ADTPDN_Pos               (3UL)                     /*!< ANA REGF: ADTPDN (Bit 3)                              */
#define ANA_REGF_ADTPDN_Msk               (0x8UL)                   /*!< ANA REGF: ADTPDN (Bitfield-Mask: 0x01)                */
#define ANA_REGF_ADTPDN                   ANA_REGF_ADTPDN_Msk
#define ANA_REGF_AVCCOEN_Pos              (2UL)                     /*!< ANA REGF: AVCCOEN (Bit 2)                             */
#define ANA_REGF_AVCCOEN_Msk              (0x4UL)                   /*!< ANA REGF: AVCCOEN (Bitfield-Mask: 0x01)               */
#define ANA_REGF_AVCCOEN                  ANA_REGF_AVCCOEN_Msk
#define ANA_REGF_BATRTCDETEN_Pos          (1UL)                     /*!< ANA REGF: BATRTCDETEN (Bit 1)                         */
#define ANA_REGF_BATRTCDETEN_Msk          (0x2UL)                   /*!< ANA REGF: BATRTCDETEN (Bitfield-Mask: 0x01)           */
#define ANA_REGF_BATRTCDETEN              ANA_REGF_BATRTCDETEN_Msk
#define ANA_REGF_BAT1DETEN_Pos            (0UL)                     /*!< ANA REGF: BAT1DETEN (Bit 0)                           */
#define ANA_REGF_BAT1DETEN_Msk            (0x1UL)                   /*!< ANA REGF: BAT1DETEN (Bitfield-Mask: 0x01)             */
#define ANA_REGF_BAT1DETEN                ANA_REGF_BAT1DETEN_Msk
/* =========================================================  REG10  ========================================================= */
/* =========================================================  REG11  ========================================================= */
#define ANA_REG11_VINBUFPD_Pos            (7UL)                     /*!< ANA REG11: VINBUFPD (Bit 7)                           */
#define ANA_REG11_VINBUFPD_Msk            (0x80UL)                  /*!< ANA REG11: VINBUFPD (Bitfield-Mask: 0x01)             */
#define ANA_REG11_VINBUFPD                ANA_REG11_VINBUFPD_Msk
#define ANA_REG11_REFBUFPD_Pos            (6UL)                     /*!< ANA REG11: REFBUFPD (Bit 6)                           */
#define ANA_REG11_REFBUFPD_Msk            (0x40UL)                  /*!< ANA REG11: REFBUFPD (Bitfield-Mask: 0x01)             */
#define ANA_REG11_REFBUFPD                ANA_REG11_REFBUFPD_Msk
/* =========================================================  CTRL  ========================================================== */
#define ANA_CTRL_PDNS2_Pos                (26UL)                    /*!< ANA CTRL: PDNS2 (Bit 26)                              */
#define ANA_CTRL_PDNS2_Msk                (0x4000000UL)             /*!< ANA CTRL: PDNS2 (Bitfield-Mask: 0x01)                 */
#define ANA_CTRL_PDNS2                    ANA_CTRL_PDNS2_Msk
#define ANA_CTRL_CMP2DEB_Pos              (22UL)                    /*!< ANA CTRL: CMP2DEB (Bit 22)                            */
#define ANA_CTRL_CMP2DEB_Msk              (0xc00000UL)              /*!< ANA CTRL: CMP2DEB (Bitfield-Mask: 0x03)               */
#define ANA_CTRL_CMP2DEB                  ANA_CTRL_CMP2DEB_Msk
#define ANA_CTRL_CMP1DEB_Pos              (20UL)                    /*!< ANA CTRL: CMP1DEB (Bit 20)                            */
#define ANA_CTRL_CMP1DEB_Msk              (0x300000UL)              /*!< ANA CTRL: CMP1DEB (Bitfield-Mask: 0x03)               */
#define ANA_CTRL_CMP1DEB                  ANA_CTRL_CMP1DEB_Msk
#define ANA_CTRL_RCHTGT_Pos               (8UL)                     /*!< ANA CTRL: RCHTGT (Bit 8)                              */
#define ANA_CTRL_RCHTGT_Msk               (0xff00UL)                /*!< ANA CTRL: RCHTGT (Bitfield-Mask: 0xff)                */
#define ANA_CTRL_RCHTGT                   ANA_CTRL_RCHTGT_Msk
#define ANA_CTRL_PDNS_Pos                 (6UL)                     /*!< ANA CTRL: PDNS (Bit 6)                                */
#define ANA_CTRL_PDNS_Msk                 (0x40UL)                  /*!< ANA CTRL: PDNS (Bitfield-Mask: 0x01)                  */
#define ANA_CTRL_PDNS                     ANA_CTRL_PDNS_Msk
#define ANA_CTRL_CMP2SEL_Pos              (2UL)                     /*!< ANA CTRL: CMP2SEL (Bit 2)                             */
#define ANA_CTRL_CMP2SEL_Msk              (0xcUL)                   /*!< ANA CTRL: CMP2SEL (Bitfield-Mask: 0x03)               */
#define ANA_CTRL_CMP2SEL                  ANA_CTRL_CMP2SEL_Msk
#define ANA_CTRL_CMP1SEL_Pos              (0UL)                     /*!< ANA CTRL: CMP1SEL (Bit 0)                             */
#define ANA_CTRL_CMP1SEL_Msk              (0x3UL)                   /*!< ANA CTRL: CMP1SEL (Bitfield-Mask: 0x03)               */
#define ANA_CTRL_CMP1SEL                  ANA_CTRL_CMP1SEL_Msk
/* ========================================================  CMPOUT  ========================================================= */
#define ANA_CMPOUT_TADCO_Pos              (14UL)                    /*!< ANA CMPOUT: TADCO (Bit 14)                            */
#define ANA_CMPOUT_TADCO_Msk              (0xc000UL)                /*!< ANA CMPOUT: TADCO (Bitfield-Mask: 0x03)               */
#define ANA_CMPOUT_TADCO                  ANA_CMPOUT_TADCO_Msk
#define ANA_CMPOUT_AVCCLV_Pos             (10UL)                    /*!< ANA CMPOUT: AVCCLV (Bit 10)                           */
#define ANA_CMPOUT_AVCCLV_Msk             (0x400UL)                 /*!< ANA CMPOUT: AVCCLV (Bitfield-Mask: 0x01)              */
#define ANA_CMPOUT_AVCCLV                 ANA_CMPOUT_AVCCLV_Msk
#define ANA_CMPOUT_VDCINDROP_Pos          (8UL)                     /*!< ANA CMPOUT: VDCINDROP (Bit 8)                         */
#define ANA_CMPOUT_VDCINDROP_Msk          (0x100UL)                 /*!< ANA CMPOUT: VDCINDROP (Bitfield-Mask: 0x01)           */
#define ANA_CMPOUT_VDCINDROP              ANA_CMPOUT_VDCINDROP_Msk
#define ANA_CMPOUT_VDDALARM_Pos           (7UL)                     /*!< ANA CMPOUT: VDDALARM (Bit 7)                          */
#define ANA_CMPOUT_VDDALARM_Msk           (0x80UL)                  /*!< ANA CMPOUT: VDDALARM (Bitfield-Mask: 0x01)            */
#define ANA_CMPOUT_VDDALARM               ANA_CMPOUT_VDDALARM_Msk
#define ANA_CMPOUT_CMP2_Pos               (3UL)                     /*!< ANA CMPOUT: CMP2 (Bit 3)                              */
#define ANA_CMPOUT_CMP2_Msk               (0x8UL)                   /*!< ANA CMPOUT: CMP2 (Bitfield-Mask: 0x01)                */
#define ANA_CMPOUT_CMP2                   ANA_CMPOUT_CMP2_Msk
#define ANA_CMPOUT_CMP1_Pos               (2UL)                     /*!< ANA CMPOUT: CMP1 (Bit 2)                              */
#define ANA_CMPOUT_CMP1_Msk               (0x4UL)                   /*!< ANA CMPOUT: CMP1 (Bitfield-Mask: 0x01)                */
#define ANA_CMPOUT_CMP1                   ANA_CMPOUT_CMP1_Msk
#define ANA_CMPOUT_LOCKL_Pos              (1UL)                     /*!< ANA CMPOUT: LOCKL (Bit 1)                             */
#define ANA_CMPOUT_LOCKL_Msk              (0x2UL)                   /*!< ANA CMPOUT: LOCKL (Bitfield-Mask: 0x01)               */
#define ANA_CMPOUT_LOCKL                  ANA_CMPOUT_LOCKL_Msk
#define ANA_CMPOUT_LOCKH_Pos              (0UL)                     /*!< ANA CMPOUT: LOCKH (Bit 0)                             */
#define ANA_CMPOUT_LOCKH_Msk              (0x1UL)                   /*!< ANA CMPOUT: LOCKH (Bitfield-Mask: 0x01)               */
#define ANA_CMPOUT_LOCKH                  ANA_CMPOUT_LOCKH_Msk
/* =======================================================  ADCSTATE  ======================================================== */
#define ANA_ADCSTATE_CAL_EN_Pos           (5UL)                     /*!< ANA ADCSTATE: CAL_EN (Bit 5)                          */
#define ANA_ADCSTATE_CAL_EN_Msk           (0x20UL)                  /*!< ANA ADCSTATE: CAL_EN (Bitfield-Mask: 0x01)            */
#define ANA_ADCSTATE_CAL_EN               ANA_ADCSTATE_CAL_EN_Msk
#define ANA_ADCSTATE_RESET_Pos            (4UL)                     /*!< ANA ADCSTATE: RESET (Bit 4)                           */
#define ANA_ADCSTATE_RESET_Msk            (0x10UL)                  /*!< ANA ADCSTATE: RESET (Bitfield-Mask: 0x01)             */
#define ANA_ADCSTATE_RESET                ANA_ADCSTATE_RESET_Msk
#define ANA_ADCSTATE_ADC_EN_Pos           (3UL)                     /*!< ANA ADCSTATE: ADC_EN (Bit 3)                          */
#define ANA_ADCSTATE_ADC_EN_Msk           (0x8UL)                   /*!< ANA ADCSTATE: ADC_EN (Bitfield-Mask: 0x01)            */
#define ANA_ADCSTATE_ADC_EN               ANA_ADCSTATE_ADC_EN_Msk
#define ANA_ADCSTATE_ADCSTATE_Pos         (0UL)                     /*!< ANA ADCSTATE: ADCSTATE (Bit 0)                        */
#define ANA_ADCSTATE_ADCSTATE_Msk         (0x7UL)                   /*!< ANA ADCSTATE: ADCSTATE (Bitfield-Mask: 0x07)          */
#define ANA_ADCSTATE_ADCSTATE             ANA_ADCSTATE_ADCSTATE_Msk
/* ========================================================  INTSTS  ========================================================= */
#define ANA_INTSTS_INTSTS21_Pos           (21UL)                    /*!< ANA INTSTS: INTSTS21 (Bit 21)                         */
#define ANA_INTSTS_INTSTS21_Msk           (0x200000UL)              /*!< ANA INTSTS: INTSTS21 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS21               ANA_INTSTS_INTSTS21_Msk
#define ANA_INTSTS_INTSTS20_Pos           (20UL)                    /*!< ANA INTSTS: INTSTS20 (Bit 20)                         */
#define ANA_INTSTS_INTSTS20_Msk           (0x100000UL)              /*!< ANA INTSTS: INTSTS20 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS20               ANA_INTSTS_INTSTS20_Msk
#define ANA_INTSTS_INTSTS19_Pos           (19UL)                    /*!< ANA INTSTS: INTSTS19 (Bit 19)                         */
#define ANA_INTSTS_INTSTS19_Msk           (0x80000UL)               /*!< ANA INTSTS: INTSTS19 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS19               ANA_INTSTS_INTSTS19_Msk
#define ANA_INTSTS_INTSTS18_Pos           (18UL)                    /*!< ANA INTSTS: INTSTS18 (Bit 18)                         */
#define ANA_INTSTS_INTSTS18_Msk           (0x40000UL)               /*!< ANA INTSTS: INTSTS18 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS18               ANA_INTSTS_INTSTS18_Msk
#define ANA_INTSTS_INTSTS17_Pos           (17UL)                    /*!< ANA INTSTS: INTSTS17 (Bit 17)                         */
#define ANA_INTSTS_INTSTS17_Msk           (0x20000UL)               /*!< ANA INTSTS: INTSTS17 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS17               ANA_INTSTS_INTSTS17_Msk
#define ANA_INTSTS_INTSTS16_Pos           (16UL)                    /*!< ANA INTSTS: INTSTS16 (Bit 16)                         */
#define ANA_INTSTS_INTSTS16_Msk           (0x10000UL)               /*!< ANA INTSTS: INTSTS16 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS16               ANA_INTSTS_INTSTS16_Msk
#define ANA_INTSTS_INTSTS15_Pos           (15UL)                    /*!< ANA INTSTS: INTSTS15 (Bit 15)                         */
#define ANA_INTSTS_INTSTS15_Msk           (0x8000UL)                /*!< ANA INTSTS: INTSTS15 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS15               ANA_INTSTS_INTSTS15_Msk
#define ANA_INTSTS_INTSTS14_Pos           (14UL)                    /*!< ANA INTSTS: INTSTS14 (Bit 14)                         */
#define ANA_INTSTS_INTSTS14_Msk           (0x4000UL)                /*!< ANA INTSTS: INTSTS14 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS14               ANA_INTSTS_INTSTS14_Msk
#define ANA_INTSTS_INTSTS13_Pos           (13UL)                    /*!< ANA INTSTS: INTSTS13 (Bit 13)                         */
#define ANA_INTSTS_INTSTS13_Msk           (0x2000UL)                /*!< ANA INTSTS: INTSTS13 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS13               ANA_INTSTS_INTSTS13_Msk
#define ANA_INTSTS_INTSTS12_Pos           (12UL)                    /*!< ANA INTSTS: INTSTS12 (Bit 12)                         */
#define ANA_INTSTS_INTSTS12_Msk           (0x1000UL)                /*!< ANA INTSTS: INTSTS12 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS12               ANA_INTSTS_INTSTS12_Msk
#define ANA_INTSTS_INTSTS11_Pos           (11UL)                    /*!< ANA INTSTS: INTSTS11 (Bit 11)                         */
#define ANA_INTSTS_INTSTS11_Msk           (0x800UL)                 /*!< ANA INTSTS: INTSTS11 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS11               ANA_INTSTS_INTSTS11_Msk
#define ANA_INTSTS_INTSTS10_Pos           (10UL)                    /*!< ANA INTSTS: INTSTS10 (Bit 10)                         */
#define ANA_INTSTS_INTSTS10_Msk           (0x400UL)                 /*!< ANA INTSTS: INTSTS10 (Bitfield-Mask: 0x01)            */
#define ANA_INTSTS_INTSTS10               ANA_INTSTS_INTSTS10_Msk
#define ANA_INTSTS_INTSTS8_Pos            (8UL)                     /*!< ANA INTSTS: INTSTS8 (Bit 8)                           */
#define ANA_INTSTS_INTSTS8_Msk            (0x100UL)                 /*!< ANA INTSTS: INTSTS8 (Bitfield-Mask: 0x01)             */
#define ANA_INTSTS_INTSTS8                ANA_INTSTS_INTSTS8_Msk
#define ANA_INTSTS_INTSTS7_Pos            (7UL)                     /*!< ANA INTSTS: INTSTS7 (Bit 7)                           */
#define ANA_INTSTS_INTSTS7_Msk            (0x80UL)                  /*!< ANA INTSTS: INTSTS7 (Bitfield-Mask: 0x01)             */
#define ANA_INTSTS_INTSTS7                ANA_INTSTS_INTSTS7_Msk
#define ANA_INTSTS_INTSTS3_Pos            (3UL)                     /*!< ANA INTSTS: INTSTS3 (Bit 3)                           */
#define ANA_INTSTS_INTSTS3_Msk            (0x8UL)                   /*!< ANA INTSTS: INTSTS3 (Bitfield-Mask: 0x01)             */
#define ANA_INTSTS_INTSTS3                ANA_INTSTS_INTSTS3_Msk
#define ANA_INTSTS_INTSTS2_Pos            (2UL)                     /*!< ANA INTSTS: INTSTS2 (Bit 2)                           */
#define ANA_INTSTS_INTSTS2_Msk            (0x4UL)                   /*!< ANA INTSTS: INTSTS2 (Bitfield-Mask: 0x01)             */
#define ANA_INTSTS_INTSTS2                ANA_INTSTS_INTSTS2_Msk
#define ANA_INTSTS_INTSTS1_Pos            (1UL)                     /*!< ANA INTSTS: INTSTS1 (Bit 1)                           */
#define ANA_INTSTS_INTSTS1_Msk            (0x2UL)                   /*!< ANA INTSTS: INTSTS1 (Bitfield-Mask: 0x01)             */
#define ANA_INTSTS_INTSTS1                ANA_INTSTS_INTSTS1_Msk
#define ANA_INTSTS_INTSTS0_Pos            (0UL)                     /*!< ANA INTSTS: INTSTS0 (Bit 0)                           */
#define ANA_INTSTS_INTSTS0_Msk            (0x1UL)                   /*!< ANA INTSTS: INTSTS0 (Bitfield-Mask: 0x01)             */
#define ANA_INTSTS_INTSTS0                ANA_INTSTS_INTSTS0_Msk
/* =========================================================  INTEN  ========================================================= */
#define ANA_INTEN_INTEN21_Pos             (21UL)                    /*!< ANA INTEN: INTEN21 (Bit 21)                           */
#define ANA_INTEN_INTEN21_Msk             (0x200000UL)              /*!< ANA INTEN: INTEN21 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN21                 ANA_INTEN_INTEN21_Msk
#define ANA_INTEN_INTEN20_Pos             (20UL)                    /*!< ANA INTEN: INTEN20 (Bit 20)                           */
#define ANA_INTEN_INTEN20_Msk             (0x100000UL)              /*!< ANA INTEN: INTEN20 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN20                 ANA_INTEN_INTEN20_Msk
#define ANA_INTEN_INTEN19_Pos             (19UL)                    /*!< ANA INTEN: INTEN19 (Bit 19)                           */
#define ANA_INTEN_INTEN19_Msk             (0x80000UL)               /*!< ANA INTEN: INTEN19 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN19                 ANA_INTEN_INTEN19_Msk
#define ANA_INTEN_INTEN18_Pos             (18UL)                    /*!< ANA INTEN: INTEN18 (Bit 18)                           */
#define ANA_INTEN_INTEN18_Msk             (0x40000UL)               /*!< ANA INTEN: INTEN18 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN18                 ANA_INTEN_INTEN18_Msk
#define ANA_INTEN_INTEN17_Pos             (17UL)                    /*!< ANA INTEN: INTEN17 (Bit 17)                           */
#define ANA_INTEN_INTEN17_Msk             (0x20000UL)               /*!< ANA INTEN: INTEN17 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN17                 ANA_INTEN_INTEN17_Msk
#define ANA_INTEN_INTEN16_Pos             (16UL)                    /*!< ANA INTEN: INTEN16 (Bit 16)                           */
#define ANA_INTEN_INTEN16_Msk             (0x10000UL)               /*!< ANA INTEN: INTEN16 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN16                 ANA_INTEN_INTEN16_Msk
#define ANA_INTEN_INTEN15_Pos             (15UL)                    /*!< ANA INTEN: INTEN15 (Bit 15)                           */
#define ANA_INTEN_INTEN15_Msk             (0x8000UL)                /*!< ANA INTEN: INTEN15 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN15                 ANA_INTEN_INTEN15_Msk
#define ANA_INTEN_INTEN14_Pos             (14UL)                    /*!< ANA INTEN: INTEN14 (Bit 14)                           */
#define ANA_INTEN_INTEN14_Msk             (0x4000UL)                /*!< ANA INTEN: INTEN14 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN14                 ANA_INTEN_INTEN14_Msk
#define ANA_INTEN_INTEN13_Pos             (13UL)                    /*!< ANA INTEN: INTEN13 (Bit 13)                           */
#define ANA_INTEN_INTEN13_Msk             (0x2000UL)                /*!< ANA INTEN: INTEN13 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN13                 ANA_INTEN_INTEN13_Msk
#define ANA_INTEN_INTEN12_Pos             (12UL)                    /*!< ANA INTEN: INTEN12 (Bit 12)                           */
#define ANA_INTEN_INTEN12_Msk             (0x1000UL)                /*!< ANA INTEN: INTEN12 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN12                 ANA_INTEN_INTEN12_Msk
#define ANA_INTEN_INTEN11_Pos             (11UL)                    /*!< ANA INTEN: INTEN11 (Bit 11)                           */
#define ANA_INTEN_INTEN11_Msk             (0x800UL)                 /*!< ANA INTEN: INTEN11 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN11                 ANA_INTEN_INTEN11_Msk
#define ANA_INTEN_INTEN10_Pos             (10UL)                    /*!< ANA INTEN: INTEN10 (Bit 10)                           */
#define ANA_INTEN_INTEN10_Msk             (0x400UL)                 /*!< ANA INTEN: INTEN10 (Bitfield-Mask: 0x01)              */
#define ANA_INTEN_INTEN10                 ANA_INTEN_INTEN10_Msk
#define ANA_INTEN_INTEN8_Pos              (8UL)                     /*!< ANA INTEN: INTEN8 (Bit 8)                             */
#define ANA_INTEN_INTEN8_Msk              (0x100UL)                 /*!< ANA INTEN: INTEN8 (Bitfield-Mask: 0x01)               */
#define ANA_INTEN_INTEN8                  ANA_INTEN_INTEN8_Msk
#define ANA_INTEN_INTEN7_Pos              (7UL)                     /*!< ANA INTEN: INTEN7 (Bit 7)                             */
#define ANA_INTEN_INTEN7_Msk              (0x80UL)                  /*!< ANA INTEN: INTEN7 (Bitfield-Mask: 0x01)               */
#define ANA_INTEN_INTEN7                  ANA_INTEN_INTEN7_Msk
#define ANA_INTEN_INTEN3_Pos              (3UL)                     /*!< ANA INTEN: INTEN3 (Bit 3)                             */
#define ANA_INTEN_INTEN3_Msk              (0x8UL)                   /*!< ANA INTEN: INTEN3 (Bitfield-Mask: 0x01)               */
#define ANA_INTEN_INTEN3                  ANA_INTEN_INTEN3_Msk
#define ANA_INTEN_INTEN2_Pos              (2UL)                     /*!< ANA INTEN: INTEN2 (Bit 2)                             */
#define ANA_INTEN_INTEN2_Msk              (0x4UL)                   /*!< ANA INTEN: INTEN2 (Bitfield-Mask: 0x01)               */
#define ANA_INTEN_INTEN2                  ANA_INTEN_INTEN2_Msk
#define ANA_INTEN_INTEN1_Pos              (1UL)                     /*!< ANA INTEN: INTEN1 (Bit 1)                             */
#define ANA_INTEN_INTEN1_Msk              (0x2UL)                   /*!< ANA INTEN: INTEN1 (Bitfield-Mask: 0x01)               */
#define ANA_INTEN_INTEN1                  ANA_INTEN_INTEN1_Msk
#define ANA_INTEN_INTEN0_Pos              (0UL)                     /*!< ANA INTEN: INTEN0 (Bit 0)                             */
#define ANA_INTEN_INTEN0_Msk              (0x1UL)                   /*!< ANA INTEN: INTEN0 (Bitfield-Mask: 0x01)               */
#define ANA_INTEN_INTEN0                  ANA_INTEN_INTEN0_Msk
/* =======================================================  ADCCTRL0  ======================================================== */
#define ANA_ADCCTRL0_MTRIG_Pos            (31UL)                    /*!< ANA ADCCTRL0: MTRIG (Bit 31)                          */
#define ANA_ADCCTRL0_MTRIG_Msk            (0x80000000UL)            /*!< ANA ADCCTRL0: MTRIG (Bitfield-Mask: 0x01)             */
#define ANA_ADCCTRL0_MTRIG                ANA_ADCCTRL0_MTRIG_Msk
#define ANA_ADCCTRL0_STOP_Pos             (19UL)                    /*!< ANA ADCCTRL0: STOP (Bit 19)                           */
#define ANA_ADCCTRL0_STOP_Msk             (0x80000UL)               /*!< ANA ADCCTRL0: STOP (Bitfield-Mask: 0x01)              */
#define ANA_ADCCTRL0_STOP                 ANA_ADCCTRL0_STOP_Msk
#define ANA_ADCCTRL0_AEN_Pos              (16UL)                    /*!< ANA ADCCTRL0: AEN (Bit 16)                            */
#define ANA_ADCCTRL0_AEN_Msk              (0x70000UL)               /*!< ANA ADCCTRL0: AEN (Bitfield-Mask: 0x07)               */
#define ANA_ADCCTRL0_AEN                  ANA_ADCCTRL0_AEN_Msk
#define ANA_ADCCTRL0_CLKSRCSEL_Pos        (12UL)                    /*!< ANA ADCCTRL0: CLKSRCSEL (Bit 12)                      */
#define ANA_ADCCTRL0_CLKSRCSEL_Msk        (0x1000UL)                /*!< ANA ADCCTRL0: CLKSRCSEL (Bitfield-Mask: 0x01)         */
#define ANA_ADCCTRL0_CLKSRCSEL            ANA_ADCCTRL0_CLKSRCSEL_Msk
/* ========================================================  CMPCTL  ========================================================= */
#define ANA_CMPCTL_PWR_DEB_SEL_Pos        (24UL)                    /*!< ANA CMPCTL: PWR_DEB_SEL (Bit 24)                      */
#define ANA_CMPCTL_PWR_DEB_SEL_Msk        (0xff000000UL)            /*!< ANA CMPCTL: PWR_DEB_SEL (Bitfield-Mask: 0xff)         */
#define ANA_CMPCTL_PWR_DEB_SEL            ANA_CMPCTL_PWR_DEB_SEL_Msk
#define ANA_CMPCTL_VDDALARM_CHK_FRQ_SEL_Pos (22UL)                  /*!< ANA CMPCTL: VDDALARM_CHK_FRQ_SEL (Bit 22)             */
#define ANA_CMPCTL_VDDALARM_CHK_FRQ_SEL_Msk (0xc00000UL)            /*!< ANA CMPCTL: VDDALARM_CHK_FRQ_SEL (Bitfield-Mask: 0x03) */
#define ANA_CMPCTL_VDDALARM_CHK_FRQ_SEL     ANA_CMPCTL_VDDALARM_CHK_FRQ_SEL_Msk
#define ANA_CMPCTL_CMP2_IO_NODEB_Pos      (21UL)                    /*!< ANA CMPCTL: CMP2_IO_NODEB (Bit 21)                    */
#define ANA_CMPCTL_CMP2_IO_NODEB_Msk      (0x200000UL)              /*!< ANA CMPCTL: CMP2_IO_NODEB (Bitfield-Mask: 0x01)       */
#define ANA_CMPCTL_CMP2_IO_NODEB          ANA_CMPCTL_CMP2_IO_NODEB_Msk
#define ANA_CMPCTL_CMP2_INT_MASK_EN_Pos   (20UL)                    /*!< ANA CMPCTL: CMP2_INT_MASK_EN (Bit 20)                 */
#define ANA_CMPCTL_CMP2_INT_MASK_EN_Msk   (0x100000UL)              /*!< ANA CMPCTL: CMP2_INT_MASK_EN (Bitfield-Mask: 0x01)    */
#define ANA_CMPCTL_CMP2_INT_MASK_EN       ANA_CMPCTL_CMP2_INT_MASK_EN_Msk
#define ANA_CMPCTL_CMP1_IO_NODEB_Pos      (17UL)                    /*!< ANA CMPCTL: CMP1_IO_NODEB (Bit 17)                    */
#define ANA_CMPCTL_CMP1_IO_NODEB_Msk      (0x20000UL)               /*!< ANA CMPCTL: CMP1_IO_NODEB (Bitfield-Mask: 0x01)       */
#define ANA_CMPCTL_CMP1_IO_NODEB          ANA_CMPCTL_CMP1_IO_NODEB_Msk
#define ANA_CMPCTL_CMP1_INT_MASK_EN_Pos   (16UL)                    /*!< ANA CMPCTL: CMP1_INT_MASK_EN (Bit 16)                 */
#define ANA_CMPCTL_CMP1_INT_MASK_EN_Msk   (0x10000UL)               /*!< ANA CMPCTL: CMP1_INT_MASK_EN (Bitfield-Mask: 0x01)    */
#define ANA_CMPCTL_CMP1_INT_MASK_EN       ANA_CMPCTL_CMP1_INT_MASK_EN_Msk
#define ANA_CMPCTL_CMP2_CHK_NUM_Pos       (12UL)                    /*!< ANA CMPCTL: CMP2_CHK_NUM (Bit 12)                     */
#define ANA_CMPCTL_CMP2_CHK_NUM_Msk       (0xf000UL)                /*!< ANA CMPCTL: CMP2_CHK_NUM (Bitfield-Mask: 0x0f)        */
#define ANA_CMPCTL_CMP2_CHK_NUM           ANA_CMPCTL_CMP2_CHK_NUM_Msk
#define ANA_CMPCTL_CMP2_THR_EN_Pos        (11UL)                    /*!< ANA CMPCTL: CMP2_THR_EN (Bit 11)                      */
#define ANA_CMPCTL_CMP2_THR_EN_Msk        (0x800UL)                 /*!< ANA CMPCTL: CMP2_THR_EN (Bitfield-Mask: 0x01)         */
#define ANA_CMPCTL_CMP2_THR_EN            ANA_CMPCTL_CMP2_THR_EN_Msk
#define ANA_CMPCTL_CMP2_CHK_FRQ_Pos       (8UL)                     /*!< ANA CMPCTL: CMP2_CHK_FRQ (Bit 8)                      */
#define ANA_CMPCTL_CMP2_CHK_FRQ_Msk       (0x700UL)                 /*!< ANA CMPCTL: CMP2_CHK_FRQ (Bitfield-Mask: 0x07)        */
#define ANA_CMPCTL_CMP2_CHK_FRQ           ANA_CMPCTL_CMP2_CHK_FRQ_Msk
#define ANA_CMPCTL_CMP1_CHK_NUM_Pos       (4UL)                     /*!< ANA CMPCTL: CMP1_CHK_NUM (Bit 4)                      */
#define ANA_CMPCTL_CMP1_CHK_NUM_Msk       (0xf0UL)                  /*!< ANA CMPCTL: CMP1_CHK_NUM (Bitfield-Mask: 0x0f)        */
#define ANA_CMPCTL_CMP1_CHK_NUM           ANA_CMPCTL_CMP1_CHK_NUM_Msk
#define ANA_CMPCTL_CMP1_THR_EN_Pos        (3UL)                     /*!< ANA CMPCTL: CMP1_THR_EN (Bit 3)                       */
#define ANA_CMPCTL_CMP1_THR_EN_Msk        (0x8UL)                   /*!< ANA CMPCTL: CMP1_THR_EN (Bitfield-Mask: 0x01)         */
#define ANA_CMPCTL_CMP1_THR_EN            ANA_CMPCTL_CMP1_THR_EN_Msk
#define ANA_CMPCTL_CMP1_CHK_FRQ_Pos       (0UL)                     /*!< ANA CMPCTL: CMP1_CHK_FRQ (Bit 0)                      */
#define ANA_CMPCTL_CMP1_CHK_FRQ_Msk       (0x7UL)                   /*!< ANA CMPCTL: CMP1_CHK_FRQ (Bitfield-Mask: 0x07)        */
#define ANA_CMPCTL_CMP1_CHK_FRQ           ANA_CMPCTL_CMP1_CHK_FRQ_Msk
/* ========================================================  ADCDATA  ======================================================== */
#define ANA_ADCDATA_ADCDATA_Pos           (0UL)                     /*!< ANA ADCDATA: ADCDATA (Bit 0)                          */
#define ANA_ADCDATA_ADCDATA_Msk           (0xffffUL)                /*!< ANA ADCDATA: ADCDATA (Bitfield-Mask: 0xffff)          */
#define ANA_ADCDATA_ADCDATA               ANA_ADCDATA_ADCDATA_Msk
/* ========================================================  CMPCNT  ========================================================= */
#define ANA_CMPCNT_CNT_Pos                (0UL)                     /*!< ANA CMPCNT: CNT (Bit 0)                               */
#define ANA_CMPCNT_CNT_Msk                (0xffffffffUL)            /*!< ANA CMPCNT: CNT (Bitfield-Mask: 0xffffffff)           */
#define ANA_CMPCNT_CNT                    ANA_CMPCNT_CNT_Msk
/* =========================================================  MISC  ========================================================== */
#define ANA_MISC_TADCTH_Pos               (4UL)                     /*!< ANA MISC: TADCTH (Bit 4)                              */
#define ANA_MISC_TADCTH_Msk               (0x30UL)                  /*!< ANA MISC: TADCTH (Bitfield-Mask: 0x03)                */
#define ANA_MISC_TADCTH                   ANA_MISC_TADCTH_Msk
/* ========================================================  ADCDOS  ========================================================= */
#define ANA_ADCDOS_DOS_Pos                (0UL)                     /*!< ANA ADCDOS: DOS (Bit 0)                               */
#define ANA_ADCDOS_DOS_Msk                (0xffUL)                  /*!< ANA ADCDOS: DOS (Bitfield-Mask: 0xff)                 */
#define ANA_ADCDOS_DOS                    ANA_ADCDOS_DOS_Msk
/* ======================================================  ADCDATADMA  ======================================================= */
#define ANA_ADCDATADMA_ADCDATA_DMA_Pos    (0UL)                     /*!< ANA ADCDATADMA: ADCDATA_DMA (Bit 0)                   */
#define ANA_ADCDATADMA_ADCDATA_DMA_Msk    (0xffffUL)                /*!< ANA ADCDATADMA: ADCDATA_DMA (Bitfield-Mask: 0xffff)   */
#define ANA_ADCDATADMA_ADCDATA_DMA        ANA_ADCDATADMA_ADCDATA_DMA_Msk
/* ========================================================  CMPTHR  ========================================================= */
#define ANA_CMPTHR_CMP2_THR_Pos           (16UL)                    /*!< ANA CMPTHR: CMP2_THR (Bit 16)                         */
#define ANA_CMPTHR_CMP2_THR_Msk           (0xffff0000UL)            /*!< ANA CMPTHR: CMP2_THR (Bitfield-Mask: 0xffff)          */
#define ANA_CMPTHR_CMP2_THR               ANA_CMPTHR_CMP2_THR_Msk
#define ANA_CMPTHR_CMP1_THR_Pos           (0UL)                     /*!< ANA CMPTHR: CMP1_THR (Bit 0)                          */
#define ANA_CMPTHR_CMP1_THR_Msk           (0xffffUL)                /*!< ANA CMPTHR: CMP1_THR (Bitfield-Mask: 0xffff)          */
#define ANA_CMPTHR_CMP1_THR               ANA_CMPTHR_CMP1_THR_Msk
/* =======================================================  ADCCTRL1  ======================================================== */
#define ANA_ADCCTRL1_RESDIV_CHx_Pos       (16UL)                    /*!< ANA ADCCTRL1: RESDIV_CHx (Bit 16)                     */
#define ANA_ADCCTRL1_RESDIV_CHx_Msk       (0xffff0000UL)            /*!< ANA ADCCTRL1: RESDIV_CHx (Bitfield-Mask: 0xffff)      */
#define ANA_ADCCTRL1_RESDIV_CHx           ANA_ADCCTRL1_RESDIV_CHx_Msk
#define ANA_ADCCTRL1_UPPER_THD3_EN_Pos    (15UL)                    /*!< ANA ADCCTRL1: UPPER_THD3_EN (Bit 15)                  */
#define ANA_ADCCTRL1_UPPER_THD3_EN_Msk    (0x8000UL)                /*!< ANA ADCCTRL1: UPPER_THD3_EN (Bitfield-Mask: 0x01)     */
#define ANA_ADCCTRL1_UPPER_THD3_EN        ANA_ADCCTRL1_UPPER_THD3_EN_Msk
#define ANA_ADCCTRL1_LOWER_THD3_EN_Pos    (14UL)                    /*!< ANA ADCCTRL1: LOWER_THD3_EN (Bit 14)                  */
#define ANA_ADCCTRL1_LOWER_THD3_EN_Msk    (0x4000UL)                /*!< ANA ADCCTRL1: LOWER_THD3_EN (Bitfield-Mask: 0x01)     */
#define ANA_ADCCTRL1_LOWER_THD3_EN        ANA_ADCCTRL1_LOWER_THD3_EN_Msk
#define ANA_ADCCTRL1_UPPER_THD2_EN_Pos    (13UL)                    /*!< ANA ADCCTRL1: UPPER_THD2_EN (Bit 13)                  */
#define ANA_ADCCTRL1_UPPER_THD2_EN_Msk    (0x2000UL)                /*!< ANA ADCCTRL1: UPPER_THD2_EN (Bitfield-Mask: 0x01)     */
#define ANA_ADCCTRL1_UPPER_THD2_EN        ANA_ADCCTRL1_UPPER_THD2_EN_Msk
#define ANA_ADCCTRL1_LOWER_THD2_EN_Pos    (12UL)                    /*!< ANA ADCCTRL1: LOWER_THD2_EN (Bit 12)                  */
#define ANA_ADCCTRL1_LOWER_THD2_EN_Msk    (0x1000UL)                /*!< ANA ADCCTRL1: LOWER_THD2_EN (Bitfield-Mask: 0x01)     */
#define ANA_ADCCTRL1_LOWER_THD2_EN        ANA_ADCCTRL1_LOWER_THD2_EN_Msk
#define ANA_ADCCTRL1_UPPER_THD1_EN_Pos    (11UL)                    /*!< ANA ADCCTRL1: UPPER_THD1_EN (Bit 11)                  */
#define ANA_ADCCTRL1_UPPER_THD1_EN_Msk    (0x800UL)                 /*!< ANA ADCCTRL1: UPPER_THD1_EN (Bitfield-Mask: 0x01)     */
#define ANA_ADCCTRL1_UPPER_THD1_EN        ANA_ADCCTRL1_UPPER_THD1_EN_Msk
#define ANA_ADCCTRL1_LOWER_THD1_EN_Pos    (10UL)                    /*!< ANA ADCCTRL1: LOWER_THD1_EN (Bit 10)                  */
#define ANA_ADCCTRL1_LOWER_THD1_EN_Msk    (0x400UL)                 /*!< ANA ADCCTRL1: LOWER_THD1_EN (Bitfield-Mask: 0x01)     */
#define ANA_ADCCTRL1_LOWER_THD1_EN        ANA_ADCCTRL1_LOWER_THD1_EN_Msk
#define ANA_ADCCTRL1_UPPER_THD0_EN_Pos    (9UL)                     /*!< ANA ADCCTRL1: UPPER_THD0_EN (Bit 9)                   */
#define ANA_ADCCTRL1_UPPER_THD0_EN_Msk    (0x200UL)                 /*!< ANA ADCCTRL1: UPPER_THD0_EN (Bitfield-Mask: 0x01)     */
#define ANA_ADCCTRL1_UPPER_THD0_EN        ANA_ADCCTRL1_UPPER_THD0_EN_Msk
#define ANA_ADCCTRL1_LOWER_THD0_EN_Pos    (8UL)                     /*!< ANA ADCCTRL1: LOWER_THD0_EN (Bit 8)                   */
#define ANA_ADCCTRL1_LOWER_THD0_EN_Msk    (0x100UL)                 /*!< ANA ADCCTRL1: LOWER_THD0_EN (Bitfield-Mask: 0x01)     */
#define ANA_ADCCTRL1_LOWER_THD0_EN        ANA_ADCCTRL1_LOWER_THD0_EN_Msk
/* =======================================================  ADCCTRL2  ======================================================== */
#define ANA_ADCCTRL2_SCAN_CHx_Pos         (16UL)                    /*!< ANA ADCCTRL2: SCAN_CHx (Bit 16)                       */
#define ANA_ADCCTRL2_SCAN_CHx_Msk         (0xffff0000UL)            /*!< ANA ADCCTRL2: SCAN_CHx (Bitfield-Mask: 0xffff)        */
#define ANA_ADCCTRL2_SCAN_CHx             ANA_ADCCTRL2_SCAN_CHx_Msk
#define ANA_ADCCTRL2_CONV_ERR_Pos         (11UL)                    /*!< ANA ADCCTRL2: CONV_ERR (Bit 11)                       */
#define ANA_ADCCTRL2_CONV_ERR_Msk         (0x800UL)                 /*!< ANA ADCCTRL2: CONV_ERR (Bitfield-Mask: 0x01)          */
#define ANA_ADCCTRL2_CONV_ERR             ANA_ADCCTRL2_CONV_ERR_Msk
#define ANA_ADCCTRL2_CAL_ERR_Pos          (10UL)                    /*!< ANA ADCCTRL2: CAL_ERR (Bit 10)                        */
#define ANA_ADCCTRL2_CAL_ERR_Msk          (0x400UL)                 /*!< ANA ADCCTRL2: CAL_ERR (Bitfield-Mask: 0x01)           */
#define ANA_ADCCTRL2_CAL_ERR              ANA_ADCCTRL2_CAL_ERR_Msk
#define ANA_ADCCTRL2_CONV_ERR_CLR_Pos     (9UL)                     /*!< ANA ADCCTRL2: CONV_ERR_CLR (Bit 9)                    */
#define ANA_ADCCTRL2_CONV_ERR_CLR_Msk     (0x200UL)                 /*!< ANA ADCCTRL2: CONV_ERR_CLR (Bitfield-Mask: 0x01)      */
#define ANA_ADCCTRL2_CONV_ERR_CLR         ANA_ADCCTRL2_CONV_ERR_CLR_Msk
#define ANA_ADCCTRL2_CAL_ERR_CLR_Pos      (8UL)                     /*!< ANA ADCCTRL2: CAL_ERR_CLR (Bit 8)                     */
#define ANA_ADCCTRL2_CAL_ERR_CLR_Msk      (0x100UL)                 /*!< ANA ADCCTRL2: CAL_ERR_CLR (Bitfield-Mask: 0x01)       */
#define ANA_ADCCTRL2_CAL_ERR_CLR          ANA_ADCCTRL2_CAL_ERR_CLR_Msk
#define ANA_ADCCTRL2_RTC_CAL_DONE_Pos     (7UL)                     /*!< ANA ADCCTRL2: RTC_CAL_DONE (Bit 7)                    */
#define ANA_ADCCTRL2_RTC_CAL_DONE_Msk     (0x80UL)                  /*!< ANA ADCCTRL2: RTC_CAL_DONE (Bitfield-Mask: 0x01)      */
#define ANA_ADCCTRL2_RTC_CAL_DONE         ANA_ADCCTRL2_RTC_CAL_DONE_Msk
#define ANA_ADCCTRL2_ADC_EN_TRG_CAL_Pos   (6UL)                     /*!< ANA ADCCTRL2: ADC_EN_TRG_CAL (Bit 6)                  */
#define ANA_ADCCTRL2_ADC_EN_TRG_CAL_Msk   (0x40UL)                  /*!< ANA ADCCTRL2: ADC_EN_TRG_CAL (Bitfield-Mask: 0x01)    */
#define ANA_ADCCTRL2_ADC_EN_TRG_CAL       ANA_ADCCTRL2_ADC_EN_TRG_CAL_Msk
#define ANA_ADCCTRL2_BUSY_Pos             (5UL)                     /*!< ANA ADCCTRL2: BUSY (Bit 5)                            */
#define ANA_ADCCTRL2_BUSY_Msk             (0x20UL)                  /*!< ANA ADCCTRL2: BUSY (Bitfield-Mask: 0x01)              */
#define ANA_ADCCTRL2_BUSY                 ANA_ADCCTRL2_BUSY_Msk
#define ANA_ADCCTRL2_ADCCR_Pos            (3UL)                     /*!< ANA ADCCTRL2: ADCCR (Bit 3)                           */
#define ANA_ADCCTRL2_ADCCR_Msk            (0x8UL)                   /*!< ANA ADCCTRL2: ADCCR (Bitfield-Mask: 0x01)             */
#define ANA_ADCCTRL2_ADCCR                ANA_ADCCTRL2_ADCCR_Msk
#define ANA_ADCCTRL2_RESET_Pos            (1UL)                     /*!< ANA ADCCTRL2: RESET (Bit 1)                           */
#define ANA_ADCCTRL2_RESET_Msk            (0x2UL)                   /*!< ANA ADCCTRL2: RESET (Bitfield-Mask: 0x01)             */
#define ANA_ADCCTRL2_RESET                ANA_ADCCTRL2_RESET_Msk
#define ANA_ADCCTRL2_ADC_EN_Pos           (0UL)                     /*!< ANA ADCCTRL2: ADC_EN (Bit 0)                          */
#define ANA_ADCCTRL2_ADC_EN_Msk           (0x1UL)                   /*!< ANA ADCCTRL2: ADC_EN (Bitfield-Mask: 0x01)            */
#define ANA_ADCCTRL2_ADC_EN               ANA_ADCCTRL2_ADC_EN_Msk
/* =====================================================  ADCDATATHD1_0  ===================================================== */
#define ANA_ADCDATATHD1_0_UPPER_THD1_Pos  (24UL)                    /*!< ANA ADCDATATHD1_0: UPPER_THD1 (Bit 24)                */
#define ANA_ADCDATATHD1_0_UPPER_THD1_Msk  (0xff000000UL)            /*!< ANA ADCDATATHD1_0: UPPER_THD1 (Bitfield-Mask: 0xff)   */
#define ANA_ADCDATATHD1_0_UPPER_THD1      ANA_ADCDATATHD1_0_UPPER_THD1_Msk
#define ANA_ADCDATATHD1_0_LOWER_THD1_Pos  (16UL)                    /*!< ANA ADCDATATHD1_0: LOWER_THD1 (Bit 16)                */
#define ANA_ADCDATATHD1_0_LOWER_THD1_Msk  (0xff0000UL)              /*!< ANA ADCDATATHD1_0: LOWER_THD1 (Bitfield-Mask: 0xff)   */
#define ANA_ADCDATATHD1_0_LOWER_THD1      ANA_ADCDATATHD1_0_LOWER_THD1_Msk
#define ANA_ADCDATATHD1_0_UPPER_THD0_Pos  (8UL)                     /*!< ANA ADCDATATHD1_0: UPPER_THD0 (Bit 8)                 */
#define ANA_ADCDATATHD1_0_UPPER_THD0_Msk  (0xff00UL)                /*!< ANA ADCDATATHD1_0: UPPER_THD0 (Bitfield-Mask: 0xff)   */
#define ANA_ADCDATATHD1_0_UPPER_THD0      ANA_ADCDATATHD1_0_UPPER_THD0_Msk
#define ANA_ADCDATATHD1_0_LOWER_THD0_Pos  (0UL)                     /*!< ANA ADCDATATHD1_0: LOWER_THD0 (Bit 0)                 */
#define ANA_ADCDATATHD1_0_LOWER_THD0_Msk  (0xffUL)                  /*!< ANA ADCDATATHD1_0: LOWER_THD0 (Bitfield-Mask: 0xff)   */
#define ANA_ADCDATATHD1_0_LOWER_THD0      ANA_ADCDATATHD1_0_LOWER_THD0_Msk
/* =====================================================  ADCDATATHD3_2  ===================================================== */
#define ANA_ADCDATATHD3_2_UPPER_THD3_Pos  (24UL)                    /*!< ANA ADCDATATHD3_2: UPPER_THD3 (Bit 24)                */
#define ANA_ADCDATATHD3_2_UPPER_THD3_Msk  (0xff000000UL)            /*!< ANA ADCDATATHD3_2: UPPER_THD3 (Bitfield-Mask: 0xff)   */
#define ANA_ADCDATATHD3_2_UPPER_THD3      ANA_ADCDATATHD3_2_UPPER_THD3_Msk
#define ANA_ADCDATATHD3_2_LOWER_THD3_Pos  (16UL)                    /*!< ANA ADCDATATHD3_2: LOWER_THD3 (Bit 16)                */
#define ANA_ADCDATATHD3_2_LOWER_THD3_Msk  (0xff0000UL)              /*!< ANA ADCDATATHD3_2: LOWER_THD3 (Bitfield-Mask: 0xff)   */
#define ANA_ADCDATATHD3_2_LOWER_THD3      ANA_ADCDATATHD3_2_LOWER_THD3_Msk
#define ANA_ADCDATATHD3_2_UPPER_THD2_Pos  (8UL)                     /*!< ANA ADCDATATHD3_2: UPPER_THD2 (Bit 8)                 */
#define ANA_ADCDATATHD3_2_UPPER_THD2_Msk  (0xff00UL)                /*!< ANA ADCDATATHD3_2: UPPER_THD2 (Bitfield-Mask: 0xff)   */
#define ANA_ADCDATATHD3_2_UPPER_THD2      ANA_ADCDATATHD3_2_UPPER_THD2_Msk
#define ANA_ADCDATATHD3_2_LOWER_THD2_Pos  (0UL)                     /*!< ANA ADCDATATHD3_2: LOWER_THD2 (Bit 0)                 */
#define ANA_ADCDATATHD3_2_LOWER_THD2_Msk  (0xffUL)                  /*!< ANA ADCDATATHD3_2: LOWER_THD2 (Bitfield-Mask: 0xff)   */
#define ANA_ADCDATATHD3_2_LOWER_THD2      ANA_ADCDATATHD3_2_LOWER_THD2_Msk
/* =====================================================  ADCDATATHD_CH  ===================================================== */
#define ANA_ADCDATATHD_CH_UPPER_THD3_TRGED_Pos (31UL)               /*!< ANA ADCDATATHD_CH: UPPER_THD3_TRGED (Bit 31)          */
#define ANA_ADCDATATHD_CH_UPPER_THD3_TRGED_Msk (0x80000000UL)       /*!< ANA ADCDATATHD_CH: UPPER_THD3_TRGED (Bitfield-Mask: 0x01) */
#define ANA_ADCDATATHD_CH_UPPER_THD3_TRGED     ANA_ADCDATATHD_CH_UPPER_THD3_TRGED_Msk
#define ANA_ADCDATATHD_CH_LOWER_THD3_TRGED_Pos (30UL)               /*!< ANA ADCDATATHD_CH: LOWER_THD3_TRGED (Bit 30)          */
#define ANA_ADCDATATHD_CH_LOWER_THD3_TRGED_Msk (0x40000000UL)       /*!< ANA ADCDATATHD_CH: LOWER_THD3_TRGED (Bitfield-Mask: 0x01) */
#define ANA_ADCDATATHD_CH_LOWER_THD3_TRGED     ANA_ADCDATATHD_CH_LOWER_THD3_TRGED_Msk
#define ANA_ADCDATATHD_CH_UPPER_THD2_TRGED_Pos (29UL)               /*!< ANA ADCDATATHD_CH: UPPER_THD2_TRGED (Bit 29)          */
#define ANA_ADCDATATHD_CH_UPPER_THD2_TRGED_Msk (0x20000000UL)       /*!< ANA ADCDATATHD_CH: UPPER_THD2_TRGED (Bitfield-Mask: 0x01) */
#define ANA_ADCDATATHD_CH_UPPER_THD2_TRGED     ANA_ADCDATATHD_CH_UPPER_THD2_TRGED_Msk
#define ANA_ADCDATATHD_CH_LOWER_THD2_TRGED_Pos (28UL)               /*!< ANA ADCDATATHD_CH: LOWER_THD2_TRGED (Bit 28)          */
#define ANA_ADCDATATHD_CH_LOWER_THD2_TRGED_Msk (0x10000000UL)       /*!< ANA ADCDATATHD_CH: LOWER_THD2_TRGED (Bitfield-Mask: 0x01) */
#define ANA_ADCDATATHD_CH_LOWER_THD2_TRGED     ANA_ADCDATATHD_CH_LOWER_THD2_TRGED_Msk
#define ANA_ADCDATATHD_CH_UPPER_THD1_TRGED_Pos (27UL)               /*!< ANA ADCDATATHD_CH: UPPER_THD1_TRGED (Bit 27)          */
#define ANA_ADCDATATHD_CH_UPPER_THD1_TRGED_Msk (0x8000000UL)        /*!< ANA ADCDATATHD_CH: UPPER_THD1_TRGED (Bitfield-Mask: 0x01) */
#define ANA_ADCDATATHD_CH_UPPER_THD1_TRGED     ANA_ADCDATATHD_CH_UPPER_THD1_TRGED_Msk
#define ANA_ADCDATATHD_CH_LOWER_THD1_TRGED_Pos (26UL)               /*!< ANA ADCDATATHD_CH: LOWER_THD1_TRGED (Bit 26)          */
#define ANA_ADCDATATHD_CH_LOWER_THD1_TRGED_Msk (0x4000000UL)        /*!< ANA ADCDATATHD_CH: LOWER_THD1_TRGED (Bitfield-Mask: 0x01) */
#define ANA_ADCDATATHD_CH_LOWER_THD1_TRGED     ANA_ADCDATATHD_CH_LOWER_THD1_TRGED_Msk
#define ANA_ADCDATATHD_CH_UPPER_THD0_TRGED_Pos (25UL)               /*!< ANA ADCDATATHD_CH: UPPER_THD0_TRGED (Bit 25)          */
#define ANA_ADCDATATHD_CH_UPPER_THD0_TRGED_Msk (0x2000000UL)        /*!< ANA ADCDATATHD_CH: UPPER_THD0_TRGED (Bitfield-Mask: 0x01) */
#define ANA_ADCDATATHD_CH_UPPER_THD0_TRGED     ANA_ADCDATATHD_CH_UPPER_THD0_TRGED_Msk
#define ANA_ADCDATATHD_CH_LOWER_THD0_TRGED_Pos (24UL)               /*!< ANA ADCDATATHD_CH: LOWER_THD0_TRGED (Bit 24)          */
#define ANA_ADCDATATHD_CH_LOWER_THD0_TRGED_Msk (0x1000000UL)        /*!< ANA ADCDATATHD_CH: LOWER_THD0_TRGED (Bitfield-Mask: 0x01) */
#define ANA_ADCDATATHD_CH_LOWER_THD0_TRGED     ANA_ADCDATATHD_CH_LOWER_THD0_TRGED_Msk
#define ANA_ADCDATATHD_CH_THD3_SEL_Pos    (22UL)                    /*!< ANA ADCDATATHD_CH: THD3_SEL (Bit 22)                  */
#define ANA_ADCDATATHD_CH_THD3_SEL_Msk    (0xc00000UL)              /*!< ANA ADCDATATHD_CH: THD3_SEL (Bitfield-Mask: 0x03)     */
#define ANA_ADCDATATHD_CH_THD3_SEL        ANA_ADCDATATHD_CH_THD3_SEL_Msk
#define ANA_ADCDATATHD_CH_THD2_SEL_Pos    (20UL)                    /*!< ANA ADCDATATHD_CH: THD2_SEL (Bit 20)                  */
#define ANA_ADCDATATHD_CH_THD2_SEL_Msk    (0x300000UL)              /*!< ANA ADCDATATHD_CH: THD2_SEL (Bitfield-Mask: 0x03)     */
#define ANA_ADCDATATHD_CH_THD2_SEL        ANA_ADCDATATHD_CH_THD2_SEL_Msk
#define ANA_ADCDATATHD_CH_THD1_SEL_Pos    (18UL)                    /*!< ANA ADCDATATHD_CH: THD1_SEL (Bit 18)                  */
#define ANA_ADCDATATHD_CH_THD1_SEL_Msk    (0xc0000UL)               /*!< ANA ADCDATATHD_CH: THD1_SEL (Bitfield-Mask: 0x03)     */
#define ANA_ADCDATATHD_CH_THD1_SEL        ANA_ADCDATATHD_CH_THD1_SEL_Msk
#define ANA_ADCDATATHD_CH_THD0_SEL_Pos    (16UL)                    /*!< ANA ADCDATATHD_CH: THD0_SEL (Bit 16)                  */
#define ANA_ADCDATATHD_CH_THD0_SEL_Msk    (0x30000UL)               /*!< ANA ADCDATATHD_CH: THD0_SEL (Bitfield-Mask: 0x03)     */
#define ANA_ADCDATATHD_CH_THD0_SEL        ANA_ADCDATATHD_CH_THD0_SEL_Msk
#define ANA_ADCDATATHD_CH_THD3_CH_Pos     (12UL)                    /*!< ANA ADCDATATHD_CH: THD3_CH (Bit 12)                   */
#define ANA_ADCDATATHD_CH_THD3_CH_Msk     (0xf000UL)                /*!< ANA ADCDATATHD_CH: THD3_CH (Bitfield-Mask: 0x0f)      */
#define ANA_ADCDATATHD_CH_THD3_CH         ANA_ADCDATATHD_CH_THD3_CH_Msk
#define ANA_ADCDATATHD_CH_THD2_CH_Pos     (8UL)                     /*!< ANA ADCDATATHD_CH: THD2_CH (Bit 8)                    */
#define ANA_ADCDATATHD_CH_THD2_CH_Msk     (0xf00UL)                 /*!< ANA ADCDATATHD_CH: THD2_CH (Bitfield-Mask: 0x0f)      */
#define ANA_ADCDATATHD_CH_THD2_CH         ANA_ADCDATATHD_CH_THD2_CH_Msk
#define ANA_ADCDATATHD_CH_THD1_CH_Pos     (4UL)                     /*!< ANA ADCDATATHD_CH: THD1_CH (Bit 4)                    */
#define ANA_ADCDATATHD_CH_THD1_CH_Msk     (0xf0UL)                  /*!< ANA ADCDATATHD_CH: THD1_CH (Bitfield-Mask: 0x0f)      */
#define ANA_ADCDATATHD_CH_THD1_CH         ANA_ADCDATATHD_CH_THD1_CH_Msk
#define ANA_ADCDATATHD_CH_THD0_CH_Pos     (0UL)                     /*!< ANA ADCDATATHD_CH: THD0_CH (Bit 0)                    */
#define ANA_ADCDATATHD_CH_THD0_CH_Msk     (0xfUL)                   /*!< ANA ADCDATATHD_CH: THD0_CH (Bitfield-Mask: 0x0f)      */
#define ANA_ADCDATATHD_CH_THD0_CH         ANA_ADCDATATHD_CH_THD0_CH_Msk


/* =========================================================================================================================== */
/* ================                                           CRYPT                                           ================ */
/* =========================================================================================================================== */

/* =========================================================  CTRL  ========================================================== */
#define CRYPT_CTRL_NOSTOP_Pos             (15UL)                    /*!< CRYPT CTRL: NOSTOP (Bit 15)                           */
#define CRYPT_CTRL_NOSTOP_Msk             (0x8000UL)                /*!< CRYPT CTRL: NOSTOP (Bitfield-Mask: 0x01)              */
#define CRYPT_CTRL_NOSTOP                 CRYPT_CTRL_NOSTOP_Msk
#define CRYPT_CTRL_LENGTH_Pos             (8UL)                     /*!< CRYPT CTRL: LENGTH (Bit 8)                            */
#define CRYPT_CTRL_LENGTH_Msk             (0xf00UL)                 /*!< CRYPT CTRL: LENGTH (Bitfield-Mask: 0x0f)              */
#define CRYPT_CTRL_LENGTH                 CRYPT_CTRL_LENGTH_Msk
#define CRYPT_CTRL_MODE_Pos               (4UL)                     /*!< CRYPT CTRL: MODE (Bit 4)                              */
#define CRYPT_CTRL_MODE_Msk               (0x70UL)                  /*!< CRYPT CTRL: MODE (Bitfield-Mask: 0x07)                */
#define CRYPT_CTRL_MODE                   CRYPT_CTRL_MODE_Msk
#define CRYPT_CTRL_ACT_Pos                (0UL)                     /*!< CRYPT CTRL: ACT (Bit 0)                               */
#define CRYPT_CTRL_ACT_Msk                (0x1UL)                   /*!< CRYPT CTRL: ACT (Bitfield-Mask: 0x01)                 */
#define CRYPT_CTRL_ACT                    CRYPT_CTRL_ACT_Msk
/* =========================================================  PTRA  ========================================================== */
#define CRYPT_PTRA_PTRA_Pos               (0UL)                     /*!< CRYPT PTRA: PTRA (Bit 0)                              */
#define CRYPT_PTRA_PTRA_Msk               (0xffffUL)                /*!< CRYPT PTRA: PTRA (Bitfield-Mask: 0xffff)              */
#define CRYPT_PTRA_PTRA                   CRYPT_PTRA_PTRA_Msk
/* =========================================================  PTRB  ========================================================== */
#define CRYPT_PTRB_PTRB_Pos               (0UL)                     /*!< CRYPT PTRB: PTRB (Bit 0)                              */
#define CRYPT_PTRB_PTRB_Msk               (0xffffUL)                /*!< CRYPT PTRB: PTRB (Bitfield-Mask: 0xffff)              */
#define CRYPT_PTRB_PTRB                   CRYPT_PTRB_PTRB_Msk
/* =========================================================  PTRO  ========================================================== */
#define CRYPT_PTRO_PTRO_Pos               (0UL)                     /*!< CRYPT PTRO: PTRO (Bit 0)                              */
#define CRYPT_PTRO_PTRO_Msk               (0xffffUL)                /*!< CRYPT PTRO: PTRO (Bitfield-Mask: 0xffff)              */
#define CRYPT_PTRO_PTRO                   CRYPT_PTRO_PTRO_Msk
/* =========================================================  CARRY  ========================================================= */
#define CRYPT_CARRY_CARRY_Pos             (0UL)                     /*!< CRYPT CARRY: CARRY (Bit 0)                            */
#define CRYPT_CARRY_CARRY_Msk             (0x1UL)                   /*!< CRYPT CARRY: CARRY (Bitfield-Mask: 0x01)              */
#define CRYPT_CARRY_CARRY                 CRYPT_CARRY_CARRY_Msk


/* =========================================================================================================================== */
/* ================                                            DMA                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  IE  =========================================================== */
#define DMA_IE_C3DAIE_Pos                 (11UL)                    /*!< DMA IE: C3DAIE (Bit 11)                               */
#define DMA_IE_C3DAIE_Msk                 (0x800UL)                 /*!< DMA IE: C3DAIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C3DAIE                     DMA_IE_C3DAIE_Msk
#define DMA_IE_C2DAIE_Pos                 (10UL)                    /*!< DMA IE: C2DAIE (Bit 10)                               */
#define DMA_IE_C2DAIE_Msk                 (0x400UL)                 /*!< DMA IE: C2DAIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C2DAIE                     DMA_IE_C2DAIE_Msk
#define DMA_IE_C1DAIE_Pos                 (9UL)                     /*!< DMA IE: C1DAIE (Bit 9)                                */
#define DMA_IE_C1DAIE_Msk                 (0x200UL)                 /*!< DMA IE: C1DAIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C1DAIE                     DMA_IE_C1DAIE_Msk
#define DMA_IE_C0DAIE_Pos                 (8UL)                     /*!< DMA IE: C0DAIE (Bit 8)                                */
#define DMA_IE_C0DAIE_Msk                 (0x100UL)                 /*!< DMA IE: C0DAIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C0DAIE                     DMA_IE_C0DAIE_Msk
#define DMA_IE_C3FEIE_Pos                 (7UL)                     /*!< DMA IE: C3FEIE (Bit 7)                                */
#define DMA_IE_C3FEIE_Msk                 (0x80UL)                  /*!< DMA IE: C3FEIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C3FEIE                     DMA_IE_C3FEIE_Msk
#define DMA_IE_C2FEIE_Pos                 (6UL)                     /*!< DMA IE: C2FEIE (Bit 6)                                */
#define DMA_IE_C2FEIE_Msk                 (0x40UL)                  /*!< DMA IE: C2FEIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C2FEIE                     DMA_IE_C2FEIE_Msk
#define DMA_IE_C1FEIE_Pos                 (5UL)                     /*!< DMA IE: C1FEIE (Bit 5)                                */
#define DMA_IE_C1FEIE_Msk                 (0x20UL)                  /*!< DMA IE: C1FEIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C1FEIE                     DMA_IE_C1FEIE_Msk
#define DMA_IE_C0FEIE_Pos                 (4UL)                     /*!< DMA IE: C0FEIE (Bit 4)                                */
#define DMA_IE_C0FEIE_Msk                 (0x10UL)                  /*!< DMA IE: C0FEIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C0FEIE                     DMA_IE_C0FEIE_Msk
#define DMA_IE_C3PEIE_Pos                 (3UL)                     /*!< DMA IE: C3PEIE (Bit 3)                                */
#define DMA_IE_C3PEIE_Msk                 (0x8UL)                   /*!< DMA IE: C3PEIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C3PEIE                     DMA_IE_C3PEIE_Msk
#define DMA_IE_C2PEIE_Pos                 (2UL)                     /*!< DMA IE: C2PEIE (Bit 2)                                */
#define DMA_IE_C2PEIE_Msk                 (0x4UL)                   /*!< DMA IE: C2PEIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C2PEIE                     DMA_IE_C2PEIE_Msk
#define DMA_IE_C1PEIE_Pos                 (1UL)                     /*!< DMA IE: C1PEIE (Bit 1)                                */
#define DMA_IE_C1PEIE_Msk                 (0x2UL)                   /*!< DMA IE: C1PEIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C1PEIE                     DMA_IE_C1PEIE_Msk
#define DMA_IE_C0PEIE_Pos                 (0UL)                     /*!< DMA IE: C0PEIE (Bit 0)                                */
#define DMA_IE_C0PEIE_Msk                 (0x1UL)                   /*!< DMA IE: C0PEIE (Bitfield-Mask: 0x01)                  */
#define DMA_IE_C0PEIE                     DMA_IE_C0PEIE_Msk
/* ==========================================================  STS  ========================================================== */
#define DMA_STS_C3DA_Pos                  (15UL)                    /*!< DMA STS: C3DA (Bit 15)                                */
#define DMA_STS_C3DA_Msk                  (0x8000UL)                /*!< DMA STS: C3DA (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C3DA                      DMA_STS_C3DA_Msk
#define DMA_STS_C2DA_Pos                  (14UL)                    /*!< DMA STS: C2DA (Bit 14)                                */
#define DMA_STS_C2DA_Msk                  (0x4000UL)                /*!< DMA STS: C2DA (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C2DA                      DMA_STS_C2DA_Msk
#define DMA_STS_C1DA_Pos                  (13UL)                    /*!< DMA STS: C1DA (Bit 13)                                */
#define DMA_STS_C1DA_Msk                  (0x2000UL)                /*!< DMA STS: C1DA (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C1DA                      DMA_STS_C1DA_Msk
#define DMA_STS_C0DA_Pos                  (12UL)                    /*!< DMA STS: C0DA (Bit 12)                                */
#define DMA_STS_C0DA_Msk                  (0x1000UL)                /*!< DMA STS: C0DA (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C0DA                      DMA_STS_C0DA_Msk
#define DMA_STS_C3FE_Pos                  (11UL)                    /*!< DMA STS: C3FE (Bit 11)                                */
#define DMA_STS_C3FE_Msk                  (0x800UL)                 /*!< DMA STS: C3FE (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C3FE                      DMA_STS_C3FE_Msk
#define DMA_STS_C2FE_Pos                  (10UL)                    /*!< DMA STS: C2FE (Bit 10)                                */
#define DMA_STS_C2FE_Msk                  (0x400UL)                 /*!< DMA STS: C2FE (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C2FE                      DMA_STS_C2FE_Msk
#define DMA_STS_C1FE_Pos                  (9UL)                     /*!< DMA STS: C1FE (Bit 9)                                 */
#define DMA_STS_C1FE_Msk                  (0x200UL)                 /*!< DMA STS: C1FE (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C1FE                      DMA_STS_C1FE_Msk
#define DMA_STS_C0FE_Pos                  (8UL)                     /*!< DMA STS: C0FE (Bit 8)                                 */
#define DMA_STS_C0FE_Msk                  (0x100UL)                 /*!< DMA STS: C0FE (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C0FE                      DMA_STS_C0FE_Msk
#define DMA_STS_C3PE_Pos                  (7UL)                     /*!< DMA STS: C3PE (Bit 7)                                 */
#define DMA_STS_C3PE_Msk                  (0x80UL)                  /*!< DMA STS: C3PE (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C3PE                      DMA_STS_C3PE_Msk
#define DMA_STS_C2PE_Pos                  (6UL)                     /*!< DMA STS: C2PE (Bit 6)                                 */
#define DMA_STS_C2PE_Msk                  (0x40UL)                  /*!< DMA STS: C2PE (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C2PE                      DMA_STS_C2PE_Msk
#define DMA_STS_C1PE_Pos                  (5UL)                     /*!< DMA STS: C1PE (Bit 5)                                 */
#define DMA_STS_C1PE_Msk                  (0x20UL)                  /*!< DMA STS: C1PE (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C1PE                      DMA_STS_C1PE_Msk
#define DMA_STS_C0PE_Pos                  (4UL)                     /*!< DMA STS: C0PE (Bit 4)                                 */
#define DMA_STS_C0PE_Msk                  (0x10UL)                  /*!< DMA STS: C0PE (Bitfield-Mask: 0x01)                   */
#define DMA_STS_C0PE                      DMA_STS_C0PE_Msk
#define DMA_STS_C3BUSY_Pos                (3UL)                     /*!< DMA STS: C3BUSY (Bit 3)                               */
#define DMA_STS_C3BUSY_Msk                (0x8UL)                   /*!< DMA STS: C3BUSY (Bitfield-Mask: 0x01)                 */
#define DMA_STS_C3BUSY                    DMA_STS_C3BUSY_Msk
#define DMA_STS_C2BUSY_Pos                (2UL)                     /*!< DMA STS: C2BUSY (Bit 2)                               */
#define DMA_STS_C2BUSY_Msk                (0x4UL)                   /*!< DMA STS: C2BUSY (Bitfield-Mask: 0x01)                 */
#define DMA_STS_C2BUSY                    DMA_STS_C2BUSY_Msk
#define DMA_STS_C1BUSY_Pos                (1UL)                     /*!< DMA STS: C1BUSY (Bit 1)                               */
#define DMA_STS_C1BUSY_Msk                (0x2UL)                   /*!< DMA STS: C1BUSY (Bitfield-Mask: 0x01)                 */
#define DMA_STS_C1BUSY                    DMA_STS_C1BUSY_Msk
#define DMA_STS_C0BUSY_Pos                (0UL)                     /*!< DMA STS: C0BUSY (Bit 0)                               */
#define DMA_STS_C0BUSY_Msk                (0x1UL)                   /*!< DMA STS: C0BUSY (Bitfield-Mask: 0x01)                 */
#define DMA_STS_C0BUSY                    DMA_STS_C0BUSY_Msk
/* =========================================================  CCTL  ========================================================== */
#define DMA_CCTL_FLEN_Pos                 (24UL)                    /*!< DMA CCTL: FLEN (Bit 24)                               */
#define DMA_CCTL_FLEN_Msk                 (0xff000000UL)            /*!< DMA CCTL: FLEN (Bitfield-Mask: 0xff)                  */
#define DMA_CCTL_FLEN                     DMA_CCTL_FLEN_Msk
#define DMA_CCTL_PLEN_Pos                 (16UL)                    /*!< DMA CCTL: PLEN (Bit 16)                               */
#define DMA_CCTL_PLEN_Msk                 (0xff0000UL)              /*!< DMA CCTL: PLEN (Bitfield-Mask: 0xff)                  */
#define DMA_CCTL_PLEN                     DMA_CCTL_PLEN_Msk
#define DMA_CCTL_STOP_Pos                 (15UL)                    /*!< DMA CCTL: STOP (Bit 15)                               */
#define DMA_CCTL_STOP_Msk                 (0x8000UL)                /*!< DMA CCTL: STOP (Bitfield-Mask: 0x01)                  */
#define DMA_CCTL_STOP                     DMA_CCTL_STOP_Msk
#define DMA_CCTL_AESEN_Pos                (14UL)                    /*!< DMA CCTL: AESEN (Bit 14)                              */
#define DMA_CCTL_AESEN_Msk                (0x4000UL)                /*!< DMA CCTL: AESEN (Bitfield-Mask: 0x01)                 */
#define DMA_CCTL_AESEN                    DMA_CCTL_AESEN_Msk
#define DMA_CCTL_CONT_Pos                 (13UL)                    /*!< DMA CCTL: CONT (Bit 13)                               */
#define DMA_CCTL_CONT_Msk                 (0x2000UL)                /*!< DMA CCTL: CONT (Bitfield-Mask: 0x01)                  */
#define DMA_CCTL_CONT                     DMA_CCTL_CONT_Msk
#define DMA_CCTL_TMODE_Pos                (12UL)                    /*!< DMA CCTL: TMODE (Bit 12)                              */
#define DMA_CCTL_TMODE_Msk                (0x1000UL)                /*!< DMA CCTL: TMODE (Bitfield-Mask: 0x01)                 */
#define DMA_CCTL_TMODE                    DMA_CCTL_TMODE_Msk
#define DMA_CCTL_DMASEL_Pos               (7UL)                     /*!< DMA CCTL: DMASEL (Bit 7)                              */
#define DMA_CCTL_DMASEL_Msk               (0xf80UL)                 /*!< DMA CCTL: DMASEL (Bitfield-Mask: 0x1f)                */
#define DMA_CCTL_DMASEL                   DMA_CCTL_DMASEL_Msk
#define DMA_CCTL_DMODE_Pos                (5UL)                     /*!< DMA CCTL: DMODE (Bit 5)                               */
#define DMA_CCTL_DMODE_Msk                (0x60UL)                  /*!< DMA CCTL: DMODE (Bitfield-Mask: 0x03)                 */
#define DMA_CCTL_DMODE                    DMA_CCTL_DMODE_Msk
#define DMA_CCTL_SMODE_Pos                (3UL)                     /*!< DMA CCTL: SMODE (Bit 3)                               */
#define DMA_CCTL_SMODE_Msk                (0x18UL)                  /*!< DMA CCTL: SMODE (Bitfield-Mask: 0x03)                 */
#define DMA_CCTL_SMODE                    DMA_CCTL_SMODE_Msk
#define DMA_CCTL_SIZE_Pos                 (1UL)                     /*!< DMA CCTL: SIZE (Bit 1)                                */
#define DMA_CCTL_SIZE_Msk                 (0x6UL)                   /*!< DMA CCTL: SIZE (Bitfield-Mask: 0x03)                  */
#define DMA_CCTL_SIZE                     DMA_CCTL_SIZE_Msk
#define DMA_CCTL_EN_Pos                   (0UL)                     /*!< DMA CCTL: EN (Bit 0)                                  */
#define DMA_CCTL_EN_Msk                   (0x1UL)                   /*!< DMA CCTL: EN (Bitfield-Mask: 0x01)                    */
#define DMA_CCTL_EN                       DMA_CCTL_EN_Msk
/* =========================================================  CSRC  ========================================================== */
#define DMA_CSRC_SRC_Pos                  (0UL)                     /*!< DMA CSRC: SRC (Bit 0)                                 */
#define DMA_CSRC_SRC_Msk                  (0xffffffffUL)            /*!< DMA CSRC: SRC (Bitfield-Mask: 0xffffffff)             */
#define DMA_CSRC_SRC                      DMA_CSRC_SRC_Msk
/* =========================================================  CDST  ========================================================== */
#define DMA_CDST_DST_Pos                  (0UL)                     /*!< DMA CDST: DST (Bit 0)                                 */
#define DMA_CDST_DST_Msk                  (0xffffffffUL)            /*!< DMA CDST: DST (Bitfield-Mask: 0xffffffff)             */
#define DMA_CDST_DST                      DMA_CDST_DST_Msk
/* =========================================================  CLEN  ========================================================== */
#define DMA_CLEN_CFLEN_Pos                (8UL)                     /*!< DMA CLEN: CFLEN (Bit 8)                               */
#define DMA_CLEN_CFLEN_Msk                (0xff00UL)                /*!< DMA CLEN: CFLEN (Bitfield-Mask: 0xff)                 */
#define DMA_CLEN_CFLEN                    DMA_CLEN_CFLEN_Msk
#define DMA_CLEN_CPLEN_Pos                (0UL)                     /*!< DMA CLEN: CPLEN (Bit 0)                               */
#define DMA_CLEN_CPLEN_Msk                (0xffUL)                  /*!< DMA CLEN: CPLEN (Bitfield-Mask: 0xff)                 */
#define DMA_CLEN_CPLEN                    DMA_CLEN_CPLEN_Msk
/* ========================================================  AESCTL  ========================================================= */
#define DMA_AESCTL_MODE_Pos               (2UL)                     /*!< DMA AESCTL: MODE (Bit 2)                              */
#define DMA_AESCTL_MODE_Msk               (0xcUL)                   /*!< DMA AESCTL: MODE (Bitfield-Mask: 0x03)                */
#define DMA_AESCTL_MODE                   DMA_AESCTL_MODE_Msk
#define DMA_AESCTL_ENC_Pos                (0UL)                     /*!< DMA AESCTL: ENC (Bit 0)                               */
#define DMA_AESCTL_ENC_Msk                (0x1UL)                   /*!< DMA AESCTL: ENC (Bitfield-Mask: 0x01)                 */
#define DMA_AESCTL_ENC                    DMA_AESCTL_ENC_Msk
/* ========================================================  AESKEY  ========================================================= */
#define DMA_AESKEY_KEY_Pos                (0UL)                     /*!< DMA AESKEY: KEY (Bit 0)                               */
#define DMA_AESKEY_KEY_Msk                (0xffffffffUL)            /*!< DMA AESKEY: KEY (Bitfield-Mask: 0xffffffff)           */
#define DMA_AESKEY_KEY                    DMA_AESKEY_KEY_Msk


/* =========================================================================================================================== */
/* ================                                           FLASH                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  ICEPROT  ======================================================== */
#define FLASH_ICEPROT_ICEPROT_Pos         (0UL)                     /*!< FLASH ICEPROT: ICEPROT (Bit 0)                        */
#define FLASH_ICEPROT_ICEPROT_Msk         (0xffffffffUL)            /*!< FLASH ICEPROT: ICEPROT (Bitfield-Mask: 0xffffffff)    */
#define FLASH_ICEPROT_ICEPROT             FLASH_ICEPROT_ICEPROT_Msk
/* ========================================================  RDPROT  ========================================================= */
#define FLASH_RDPROT_RDPORT_Pos           (0UL)                     /*!< FLASH RDPROT: RDPORT (Bit 0)                          */
#define FLASH_RDPROT_RDPORT_Msk           (0xffffffffUL)            /*!< FLASH RDPROT: RDPORT (Bitfield-Mask: 0xffffffff)      */
#define FLASH_RDPROT_RDPORT               FLASH_RDPROT_RDPORT_Msk
/* ========================================================  WRPROT  ========================================================= */
#define FLASH_WRPROT_WRPORT_Pos           (0UL)                     /*!< FLASH WRPROT: WRPORT (Bit 0)                          */
#define FLASH_WRPROT_WRPORT_Msk           (0xffffffffUL)            /*!< FLASH WRPROT: WRPORT (Bitfield-Mask: 0xffffffff)      */
#define FLASH_WRPROT_WRPORT               FLASH_WRPROT_WRPORT_Msk
/* ==========================================================  STS  ========================================================== */
#define FLASH_STS_STS_Pos                 (0UL)                     /*!< FLASH STS: STS (Bit 0)                                */
#define FLASH_STS_STS_Msk                 (0x1fUL)                  /*!< FLASH STS: STS (Bitfield-Mask: 0x1f)                  */
#define FLASH_STS_STS                     FLASH_STS_STS_Msk
/* ========================================================  INTSTS  ========================================================= */
#define FLASH_INTSTS_CSERR_Pos            (0UL)                     /*!< FLASH INTSTS: CSERR (Bit 0)                           */
#define FLASH_INTSTS_CSERR_Msk            (0x1UL)                   /*!< FLASH INTSTS: CSERR (Bitfield-Mask: 0x01)             */
#define FLASH_INTSTS_CSERR                FLASH_INTSTS_CSERR_Msk
/* ========================================================  CSSADDR  ======================================================== */
#define FLASH_CSSADDR_CSSADDR_Pos         (0UL)                     /*!< FLASH CSSADDR: CSSADDR (Bit 0)                        */
#define FLASH_CSSADDR_CSSADDR_Msk         (0x7ffffUL)               /*!< FLASH CSSADDR: CSSADDR (Bitfield-Mask: 0x7ffff)       */
#define FLASH_CSSADDR_CSSADDR             FLASH_CSSADDR_CSSADDR_Msk
/* ========================================================  CSEADDR  ======================================================== */
#define FLASH_CSEADDR_CSEADDR_Pos         (0UL)                     /*!< FLASH CSEADDR: CSEADDR (Bit 0)                        */
#define FLASH_CSEADDR_CSEADDR_Msk         (0x7ffffUL)               /*!< FLASH CSEADDR: CSEADDR (Bitfield-Mask: 0x7ffff)       */
#define FLASH_CSEADDR_CSEADDR             FLASH_CSEADDR_CSEADDR_Msk
/* ========================================================  CSVALUE  ======================================================== */
#define FLASH_CSVALUE_CSVALUE_Pos         (0UL)                     /*!< FLASH CSVALUE: CSVALUE (Bit 0)                        */
#define FLASH_CSVALUE_CSVALUE_Msk         (0xffffffffUL)            /*!< FLASH CSVALUE: CSVALUE (Bitfield-Mask: 0xffffffff)    */
#define FLASH_CSVALUE_CSVALUE             FLASH_CSVALUE_CSVALUE_Msk
/* =======================================================  CSCVALUE  ======================================================== */
#define FLASH_CSCVALUE_CSCVALUE_Pos       (0UL)                     /*!< FLASH CSCVALUE: CSCVALUE (Bit 0)                      */
#define FLASH_CSCVALUE_CSCVALUE_Msk       (0xffffffffUL)            /*!< FLASH CSCVALUE: CSCVALUE (Bitfield-Mask: 0xffffffff)  */
#define FLASH_CSCVALUE_CSCVALUE           FLASH_CSCVALUE_CSCVALUE_Msk
/* =========================================================  PASS  ========================================================== */
#define FLASH_PASS_UNLOCK_Pos             (0UL)                     /*!< FLASH PASS: UNLOCK (Bit 0)                            */
#define FLASH_PASS_UNLOCK_Msk             (0x1UL)                   /*!< FLASH PASS: UNLOCK (Bitfield-Mask: 0x01)              */
#define FLASH_PASS_UNLOCK                 FLASH_PASS_UNLOCK_Msk
/* =========================================================  CTRL  ========================================================== */
#define FLASH_CTRL_CSINTEN_Pos            (2UL)                     /*!< FLASH CTRL: CSINTEN (Bit 2)                           */
#define FLASH_CTRL_CSINTEN_Msk            (0x4UL)                   /*!< FLASH CTRL: CSINTEN (Bitfield-Mask: 0x01)             */
#define FLASH_CTRL_CSINTEN                FLASH_CTRL_CSINTEN_Msk
#define FLASH_CTRL_CSMODE_Pos             (0UL)                     /*!< FLASH CTRL: CSMODE (Bit 0)                            */
#define FLASH_CTRL_CSMODE_Msk             (0x3UL)                   /*!< FLASH CTRL: CSMODE (Bitfield-Mask: 0x03)              */
#define FLASH_CTRL_CSMODE                 FLASH_CTRL_CSMODE_Msk
/* ========================================================  PGADDR  ========================================================= */
#define FLASH_PGADDR_PGADDR_Pos           (0UL)                     /*!< FLASH PGADDR: PGADDR (Bit 0)                          */
#define FLASH_PGADDR_PGADDR_Msk           (0x3ffffUL)               /*!< FLASH PGADDR: PGADDR (Bitfield-Mask: 0x3ffff)         */
#define FLASH_PGADDR_PGADDR               FLASH_PGADDR_PGADDR_Msk
/* ========================================================  PGDATA  ========================================================= */
#define FLASH_PGDATA_PGDATA_Pos           (0UL)                     /*!< FLASH PGDATA: PGDATA (Bit 0)                          */
#define FLASH_PGDATA_PGDATA_Msk           (0xffffffffUL)            /*!< FLASH PGDATA: PGDATA (Bitfield-Mask: 0xffffffff)      */
#define FLASH_PGDATA_PGDATA               FLASH_PGDATA_PGDATA_Msk
/* ========================================================  SERASE  ========================================================= */
#define FLASH_SERASE_SERASE_Pos           (0UL)                     /*!< FLASH SERASE: SERASE (Bit 0)                          */
#define FLASH_SERASE_SERASE_Msk           (0x1UL)                   /*!< FLASH SERASE: SERASE (Bitfield-Mask: 0x01)            */
#define FLASH_SERASE_SERASE               FLASH_SERASE_SERASE_Msk
/* ========================================================  CERASE  ========================================================= */
#define FLASH_CERASE_CERASE_Pos           (0UL)                     /*!< FLASH CERASE: CERASE (Bit 0)                          */
#define FLASH_CERASE_CERASE_Msk           (0x1UL)                   /*!< FLASH CERASE: CERASE (Bitfield-Mask: 0x01)            */
#define FLASH_CERASE_CERASE               FLASH_CERASE_CERASE_Msk
/* =========================================================  DSTB  ========================================================== */
#define FLASH_DSTB_DSTB_Pos               (0UL)                     /*!< FLASH DSTB: DSTB (Bit 0)                              */
#define FLASH_DSTB_DSTB_Msk               (0x1UL)                   /*!< FLASH DSTB: DSTB (Bitfield-Mask: 0x01)                */
#define FLASH_DSTB_DSTB                   FLASH_DSTB_DSTB_Msk


/* =========================================================================================================================== */
/* ================                                           GPIOA                                           ================ */
/* =========================================================================================================================== */

/* ==========================================================  OEN  ========================================================== */
#define GPIOA_OEN_IOAOEN_Pos              (0UL)                     /*!< GPIOA OEN: IOAOEN (Bit 0)                             */
#define GPIOA_OEN_IOAOEN_Msk              (0xffffUL)                /*!< GPIOA OEN: IOAOEN (Bitfield-Mask: 0xffff)             */
#define GPIOA_OEN_IOAOEN                  GPIOA_OEN_IOAOEN_Msk
/* ==========================================================  IE  =========================================================== */
#define GPIOA_IE_IOAIE_Pos                (0UL)                     /*!< GPIOA IE: IOAIE (Bit 0)                               */
#define GPIOA_IE_IOAIE_Msk                (0xffffUL)                /*!< GPIOA IE: IOAIE (Bitfield-Mask: 0xffff)               */
#define GPIOA_IE_IOAIE                    GPIOA_IE_IOAIE_Msk
/* ==========================================================  DAT  ========================================================== */
#define GPIOA_DAT_IOADAT_Pos              (0UL)                     /*!< GPIOA DAT: IOADAT (Bit 0)                             */
#define GPIOA_DAT_IOADAT_Msk              (0xffffUL)                /*!< GPIOA DAT: IOADAT (Bitfield-Mask: 0xffff)             */
#define GPIOA_DAT_IOADAT                  GPIOA_DAT_IOADAT_Msk
/* ==========================================================  ATT  ========================================================== */
#define GPIOA_ATT_IOAATT_Pos              (0UL)                     /*!< GPIOA ATT: IOAATT (Bit 0)                             */
#define GPIOA_ATT_IOAATT_Msk              (0xffffUL)                /*!< GPIOA ATT: IOAATT (Bitfield-Mask: 0xffff)             */
#define GPIOA_ATT_IOAATT                  GPIOA_ATT_IOAATT_Msk
/* =======================================================  IOAWKUEN  ======================================================== */
#define GPIOA_IOAWKUEN_WKUEN_Pos          (0UL)                     /*!< GPIOA IOAWKUEN: WKUEN (Bit 0)                         */
#define GPIOA_IOAWKUEN_WKUEN_Msk          (0xffffffffUL)            /*!< GPIOA IOAWKUEN: WKUEN (Bitfield-Mask: 0xffffffff)     */
#define GPIOA_IOAWKUEN_WKUEN              GPIOA_IOAWKUEN_WKUEN_Msk
/* ==========================================================  STS  ========================================================== */
#define GPIOA_STS_IOASTS_Pos              (0UL)                     /*!< GPIOA STS: IOASTS (Bit 0)                             */
#define GPIOA_STS_IOASTS_Msk              (0xffffUL)                /*!< GPIOA STS: IOASTS (Bitfield-Mask: 0xffff)             */
#define GPIOA_STS_IOASTS                  GPIOA_STS_IOASTS_Msk
/* =======================================================  IOAINTSTS  ======================================================= */
#define GPIOA_IOAINTSTS_INTSTS_Pos        (0UL)                     /*!< GPIOA IOAINTSTS: INTSTS (Bit 0)                       */
#define GPIOA_IOAINTSTS_INTSTS_Msk        (0xffffUL)                /*!< GPIOA IOAINTSTS: INTSTS (Bitfield-Mask: 0xffff)       */
#define GPIOA_IOAINTSTS_INTSTS            GPIOA_IOAINTSTS_INTSTS_Msk
/* ==========================================================  SEL  ========================================================== */
#define GPIOA_SEL_SEL7_Pos                (7UL)                     /*!< GPIOA SEL: SEL7 (Bit 7)                               */
#define GPIOA_SEL_SEL7_Msk                (0x80UL)                  /*!< GPIOA SEL: SEL7 (Bitfield-Mask: 0x01)                 */
#define GPIOA_SEL_SEL7                    GPIOA_SEL_SEL7_Msk
#define GPIOA_SEL_SEL6_Pos                (6UL)                     /*!< GPIOA SEL: SEL6 (Bit 6)                               */
#define GPIOA_SEL_SEL6_Msk                (0x40UL)                  /*!< GPIOA SEL: SEL6 (Bitfield-Mask: 0x01)                 */
#define GPIOA_SEL_SEL6                    GPIOA_SEL_SEL6_Msk
#define GPIOA_SEL_SEL3_Pos                (3UL)                     /*!< GPIOA SEL: SEL3 (Bit 3)                               */
#define GPIOA_SEL_SEL3_Msk                (0x8UL)                   /*!< GPIOA SEL: SEL3 (Bitfield-Mask: 0x01)                 */
#define GPIOA_SEL_SEL3                    GPIOA_SEL_SEL3_Msk
/* =======================================================  IOANODEG  ======================================================== */
#define GPIOA_IOANODEG_NODEG_Pos          (0UL)                     /*!< GPIOA IOANODEG: NODEG (Bit 0)                         */
#define GPIOA_IOANODEG_NODEG_Msk          (0xffffUL)                /*!< GPIOA IOANODEG: NODEG (Bitfield-Mask: 0xffff)         */
#define GPIOA_IOANODEG_NODEG              GPIOA_IOANODEG_NODEG_Msk


/* =========================================================================================================================== */
/* ================                                           GPIO                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  OEN  ========================================================== */
#define GPIO_OEN_IOXOEN_Pos               (0UL)                     /*!< GPIO OEN: IOXOEN (Bit 0)                              */
#define GPIO_OEN_IOXOEN_Msk               (0xffffUL)                /*!< GPIO OEN: IOXOEN (Bitfield-Mask: 0xffff)              */
#define GPIO_OEN_IOXOEN                   GPIO_OEN_IOXOEN_Msk
/* ==========================================================  IE  =========================================================== */
#define GPIO_IE_IOXIE_Pos                 (0UL)                     /*!< GPIO IE: IOXIE (Bit 0)                                */
#define GPIO_IE_IOXIE_Msk                 (0xffffUL)                /*!< GPIO IE: IOXIE (Bitfield-Mask: 0xffff)                */
#define GPIO_IE_IOXIE                     GPIO_IE_IOXIE_Msk
/* ==========================================================  DAT  ========================================================== */
#define GPIO_DAT_IOXDAT_Pos               (0UL)                     /*!< GPIO DAT: IOXDAT (Bit 0)                              */
#define GPIO_DAT_IOXDAT_Msk               (0xffffUL)                /*!< GPIO DAT: IOXDAT (Bitfield-Mask: 0xffff)              */
#define GPIO_DAT_IOXDAT                   GPIO_DAT_IOXDAT_Msk
/* ==========================================================  ATT  ========================================================== */
#define GPIO_ATT_IOXATT_Pos               (0UL)                     /*!< GPIO ATT: IOXATT (Bit 0)                              */
#define GPIO_ATT_IOXATT_Msk               (0xffffUL)                /*!< GPIO ATT: IOXATT (Bitfield-Mask: 0xffff)              */
#define GPIO_ATT_IOXATT                   GPIO_ATT_IOXATT_Msk
/* ==========================================================  STS  ========================================================== */
#define GPIO_STS_IOXSTS_Pos               (0UL)                     /*!< GPIO STS: IOXSTS (Bit 0)                              */
#define GPIO_STS_IOXSTS_Msk               (0xffffUL)                /*!< GPIO STS: IOXSTS (Bitfield-Mask: 0xffff)              */
#define GPIO_STS_IOXSTS                   GPIO_STS_IOXSTS_Msk


/* =========================================================================================================================== */
/* ================                                          GPIOAF                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  IOB_SEL  ======================================================== */
#define GPIOAF_IOB_SEL_SEL6_Pos           (6UL)                     /*!< GPIOAF IOB_SEL: SEL6 (Bit 6)                          */
#define GPIOAF_IOB_SEL_SEL6_Msk           (0x40UL)                  /*!< GPIOAF IOB_SEL: SEL6 (Bitfield-Mask: 0x01)            */
#define GPIOAF_IOB_SEL_SEL6               GPIOAF_IOB_SEL_SEL6_Msk
#define GPIOAF_IOB_SEL_SEL2_Pos           (2UL)                     /*!< GPIOAF IOB_SEL: SEL2 (Bit 2)                          */
#define GPIOAF_IOB_SEL_SEL2_Msk           (0x4UL)                   /*!< GPIOAF IOB_SEL: SEL2 (Bitfield-Mask: 0x01)            */
#define GPIOAF_IOB_SEL_SEL2               GPIOAF_IOB_SEL_SEL2_Msk
#define GPIOAF_IOB_SEL_SEL1_Pos           (1UL)                     /*!< GPIOAF IOB_SEL: SEL1 (Bit 1)                          */
#define GPIOAF_IOB_SEL_SEL1_Msk           (0x2UL)                   /*!< GPIOAF IOB_SEL: SEL1 (Bitfield-Mask: 0x01)            */
#define GPIOAF_IOB_SEL_SEL1               GPIOAF_IOB_SEL_SEL1_Msk
/* ========================================================  IOE_SEL  ======================================================== */
#define GPIOAF_IOE_SEL_SEL7_Pos           (7UL)                     /*!< GPIOAF IOE_SEL: SEL7 (Bit 7)                          */
#define GPIOAF_IOE_SEL_SEL7_Msk           (0x80UL)                  /*!< GPIOAF IOE_SEL: SEL7 (Bitfield-Mask: 0x01)            */
#define GPIOAF_IOE_SEL_SEL7               GPIOAF_IOE_SEL_SEL7_Msk
/* ========================================================  IO_MISC  ======================================================== */
#define GPIOAF_IO_MISC_I2CIOC_Pos         (5UL)                     /*!< GPIOAF IO_MISC: I2CIOC (Bit 5)                        */
#define GPIOAF_IO_MISC_I2CIOC_Msk         (0x20UL)                  /*!< GPIOAF IO_MISC: I2CIOC (Bitfield-Mask: 0x01)          */
#define GPIOAF_IO_MISC_I2CIOC             GPIOAF_IO_MISC_I2CIOC_Msk
#define GPIOAF_IO_MISC_PLLHDIV_Pos        (0UL)                     /*!< GPIOAF IO_MISC: PLLHDIV (Bit 0)                       */
#define GPIOAF_IO_MISC_PLLHDIV_Msk        (0x7UL)                   /*!< GPIOAF IO_MISC: PLLHDIV (Bitfield-Mask: 0x07)         */
#define GPIOAF_IO_MISC_PLLHDIV            GPIOAF_IO_MISC_PLLHDIV_Msk


/* =========================================================================================================================== */
/* ================                                            I2C                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  DATA  ========================================================== */
#define I2C_DATA_DATA_Pos                 (0UL)                     /*!< I2C DATA: DATA (Bit 0)                                */
#define I2C_DATA_DATA_Msk                 (0xffUL)                  /*!< I2C DATA: DATA (Bitfield-Mask: 0xff)                  */
#define I2C_DATA_DATA                     I2C_DATA_DATA_Msk
/* =========================================================  ADDR  ========================================================== */
#define I2C_ADDR_SLA_Pos                  (1UL)                     /*!< I2C ADDR: SLA (Bit 1)                                 */
#define I2C_ADDR_SLA_Msk                  (0xfeUL)                  /*!< I2C ADDR: SLA (Bitfield-Mask: 0x7f)                   */
#define I2C_ADDR_SLA                      I2C_ADDR_SLA_Msk
#define I2C_ADDR_GC_Pos                   (0UL)                     /*!< I2C ADDR: GC (Bit 0)                                  */
#define I2C_ADDR_GC_Msk                   (0x1UL)                   /*!< I2C ADDR: GC (Bitfield-Mask: 0x01)                    */
#define I2C_ADDR_GC                       I2C_ADDR_GC_Msk
/* =========================================================  CTRL  ========================================================== */
#define I2C_CTRL_CR2_Pos                  (7UL)                     /*!< I2C CTRL: CR2 (Bit 7)                                 */
#define I2C_CTRL_CR2_Msk                  (0x80UL)                  /*!< I2C CTRL: CR2 (Bitfield-Mask: 0x01)                   */
#define I2C_CTRL_CR2                      I2C_CTRL_CR2_Msk
#define I2C_CTRL_EN_Pos                   (6UL)                     /*!< I2C CTRL: EN (Bit 6)                                  */
#define I2C_CTRL_EN_Msk                   (0x40UL)                  /*!< I2C CTRL: EN (Bitfield-Mask: 0x01)                    */
#define I2C_CTRL_EN                       I2C_CTRL_EN_Msk
#define I2C_CTRL_STA_Pos                  (5UL)                     /*!< I2C CTRL: STA (Bit 5)                                 */
#define I2C_CTRL_STA_Msk                  (0x20UL)                  /*!< I2C CTRL: STA (Bitfield-Mask: 0x01)                   */
#define I2C_CTRL_STA                      I2C_CTRL_STA_Msk
#define I2C_CTRL_STO_Pos                  (4UL)                     /*!< I2C CTRL: STO (Bit 4)                                 */
#define I2C_CTRL_STO_Msk                  (0x10UL)                  /*!< I2C CTRL: STO (Bitfield-Mask: 0x01)                   */
#define I2C_CTRL_STO                      I2C_CTRL_STO_Msk
#define I2C_CTRL_SI_Pos                   (3UL)                     /*!< I2C CTRL: SI (Bit 3)                                  */
#define I2C_CTRL_SI_Msk                   (0x8UL)                   /*!< I2C CTRL: SI (Bitfield-Mask: 0x01)                    */
#define I2C_CTRL_SI                       I2C_CTRL_SI_Msk
#define I2C_CTRL_AA_Pos                   (2UL)                     /*!< I2C CTRL: AA (Bit 2)                                  */
#define I2C_CTRL_AA_Msk                   (0x4UL)                   /*!< I2C CTRL: AA (Bitfield-Mask: 0x01)                    */
#define I2C_CTRL_AA                       I2C_CTRL_AA_Msk
#define I2C_CTRL_CR1_Pos                  (1UL)                     /*!< I2C CTRL: CR1 (Bit 1)                                 */
#define I2C_CTRL_CR1_Msk                  (0x2UL)                   /*!< I2C CTRL: CR1 (Bitfield-Mask: 0x01)                   */
#define I2C_CTRL_CR1                      I2C_CTRL_CR1_Msk
#define I2C_CTRL_CR0_Pos                  (0UL)                     /*!< I2C CTRL: CR0 (Bit 0)                                 */
#define I2C_CTRL_CR0_Msk                  (0x1UL)                   /*!< I2C CTRL: CR0 (Bitfield-Mask: 0x01)                   */
#define I2C_CTRL_CR0                      I2C_CTRL_CR0_Msk
/* ==========================================================  STS  ========================================================== */
#define I2C_STS_STS_Pos                   (3UL)                     /*!< I2C STS: STS (Bit 3)                                  */
#define I2C_STS_STS_Msk                   (0xf8UL)                  /*!< I2C STS: STS (Bitfield-Mask: 0x1f)                    */
#define I2C_STS_STS                       I2C_STS_STS_Msk
/* =========================================================  CTRL2  ========================================================= */
#define I2C_CTRL2_INTEN_Pos               (0UL)                     /*!< I2C CTRL2: INTEN (Bit 0)                              */
#define I2C_CTRL2_INTEN_Msk               (0x1UL)                   /*!< I2C CTRL2: INTEN (Bitfield-Mask: 0x01)                */
#define I2C_CTRL2_INTEN                   I2C_CTRL2_INTEN_Msk


/* =========================================================================================================================== */
/* ================                                          ISO7816                                          ================ */
/* =========================================================================================================================== */

/* =======================================================  BAUDDIVL  ======================================================== */
#define ISO7816_BAUDDIVL_BAUDDIVL_Pos     (0UL)                     /*!< ISO7816 BAUDDIVL: BAUDDIVL (Bit 0)                    */
#define ISO7816_BAUDDIVL_BAUDDIVL_Msk     (0xffUL)                  /*!< ISO7816 BAUDDIVL: BAUDDIVL (Bitfield-Mask: 0xff)      */
#define ISO7816_BAUDDIVL_BAUDDIVL         ISO7816_BAUDDIVL_BAUDDIVL_Msk
/* =======================================================  BAUDDIVH  ======================================================== */
#define ISO7816_BAUDDIVH_BAUDDIVH_Pos     (0UL)                     /*!< ISO7816 BAUDDIVH: BAUDDIVH (Bit 0)                    */
#define ISO7816_BAUDDIVH_BAUDDIVH_Msk     (0xffUL)                  /*!< ISO7816 BAUDDIVH: BAUDDIVH (Bitfield-Mask: 0xff)      */
#define ISO7816_BAUDDIVH_BAUDDIVH         ISO7816_BAUDDIVH_BAUDDIVH_Msk
/* =========================================================  DATA  ========================================================== */
#define ISO7816_DATA_DATA_Pos             (0UL)                     /*!< ISO7816 DATA: DATA (Bit 0)                            */
#define ISO7816_DATA_DATA_Msk             (0xffUL)                  /*!< ISO7816 DATA: DATA (Bitfield-Mask: 0xff)              */
#define ISO7816_DATA_DATA                 ISO7816_DATA_DATA_Msk
/* =========================================================  INFO  ========================================================== */
#define ISO7816_INFO_DMATXDONE_Pos        (9UL)                     /*!< ISO7816 INFO: DMATXDONE (Bit 9)                       */
#define ISO7816_INFO_DMATXDONE_Msk        (0x200UL)                 /*!< ISO7816 INFO: DMATXDONE (Bitfield-Mask: 0x01)         */
#define ISO7816_INFO_DMATXDONE            ISO7816_INFO_DMATXDONE_Msk
#define ISO7816_INFO_TXRTYERRIF_Pos       (8UL)                     /*!< ISO7816 INFO: TXRTYERRIF (Bit 8)                      */
#define ISO7816_INFO_TXRTYERRIF_Msk       (0x100UL)                 /*!< ISO7816 INFO: TXRTYERRIF (Bitfield-Mask: 0x01)        */
#define ISO7816_INFO_TXRTYERRIF           ISO7816_INFO_TXRTYERRIF_Msk
#define ISO7816_INFO_RXOVIF_Pos           (7UL)                     /*!< ISO7816 INFO: RXOVIF (Bit 7)                          */
#define ISO7816_INFO_RXOVIF_Msk           (0x80UL)                  /*!< ISO7816 INFO: RXOVIF (Bitfield-Mask: 0x01)            */
#define ISO7816_INFO_RXOVIF               ISO7816_INFO_RXOVIF_Msk
#define ISO7816_INFO_TXDONEIF_Pos         (6UL)                     /*!< ISO7816 INFO: TXDONEIF (Bit 6)                        */
#define ISO7816_INFO_TXDONEIF_Msk         (0x40UL)                  /*!< ISO7816 INFO: TXDONEIF (Bitfield-Mask: 0x01)          */
#define ISO7816_INFO_TXDONEIF             ISO7816_INFO_TXDONEIF_Msk
#define ISO7816_INFO_RXIF_Pos             (5UL)                     /*!< ISO7816 INFO: RXIF (Bit 5)                            */
#define ISO7816_INFO_RXIF_Msk             (0x20UL)                  /*!< ISO7816 INFO: RXIF (Bitfield-Mask: 0x01)              */
#define ISO7816_INFO_RXIF                 ISO7816_INFO_RXIF_Msk
#define ISO7816_INFO_RXERRIF_Pos          (2UL)                     /*!< ISO7816 INFO: RXERRIF (Bit 2)                         */
#define ISO7816_INFO_RXERRIF_Msk          (0x4UL)                   /*!< ISO7816 INFO: RXERRIF (Bitfield-Mask: 0x01)           */
#define ISO7816_INFO_RXERRIF              ISO7816_INFO_RXERRIF_Msk
#define ISO7816_INFO_CHKSUM_Pos           (1UL)                     /*!< ISO7816 INFO: CHKSUM (Bit 1)                          */
#define ISO7816_INFO_CHKSUM_Msk           (0x2UL)                   /*!< ISO7816 INFO: CHKSUM (Bitfield-Mask: 0x01)            */
#define ISO7816_INFO_CHKSUM               ISO7816_INFO_CHKSUM_Msk
#define ISO7816_INFO_RXACK_Pos            (0UL)                     /*!< ISO7816 INFO: RXACK (Bit 0)                           */
#define ISO7816_INFO_RXACK_Msk            (0x1UL)                   /*!< ISO7816 INFO: RXACK (Bitfield-Mask: 0x01)             */
#define ISO7816_INFO_RXACK                ISO7816_INFO_RXACK_Msk
/* ==========================================================  CFG  ========================================================== */
#define ISO7816_CFG_RXACKSET_Pos          (16UL)                    /*!< ISO7816 CFG: RXACKSET (Bit 16)                        */
#define ISO7816_CFG_RXACKSET_Msk          (0x10000UL)               /*!< ISO7816 CFG: RXACKSET (Bitfield-Mask: 0x01)           */
#define ISO7816_CFG_RXACKSET              ISO7816_CFG_RXACKSET_Msk
#define ISO7816_CFG_TXRTYCNT_Pos          (12UL)                    /*!< ISO7816 CFG: TXRTYCNT (Bit 12)                        */
#define ISO7816_CFG_TXRTYCNT_Msk          (0xf000UL)                /*!< ISO7816 CFG: TXRTYCNT (Bitfield-Mask: 0x0f)           */
#define ISO7816_CFG_TXRTYCNT              ISO7816_CFG_TXRTYCNT_Msk
#define ISO7816_CFG_LSB_Pos               (11UL)                    /*!< ISO7816 CFG: LSB (Bit 11)                             */
#define ISO7816_CFG_LSB_Msk               (0x800UL)                 /*!< ISO7816 CFG: LSB (Bitfield-Mask: 0x01)                */
#define ISO7816_CFG_LSB                   ISO7816_CFG_LSB_Msk
#define ISO7816_CFG_AUTORXACK_Pos         (9UL)                     /*!< ISO7816 CFG: AUTORXACK (Bit 9)                        */
#define ISO7816_CFG_AUTORXACK_Msk         (0x200UL)                 /*!< ISO7816 CFG: AUTORXACK (Bitfield-Mask: 0x01)          */
#define ISO7816_CFG_AUTORXACK             ISO7816_CFG_AUTORXACK_Msk
#define ISO7816_CFG_TXRTYERRIE_Pos        (8UL)                     /*!< ISO7816 CFG: TXRTYERRIE (Bit 8)                       */
#define ISO7816_CFG_TXRTYERRIE_Msk        (0x100UL)                 /*!< ISO7816 CFG: TXRTYERRIE (Bitfield-Mask: 0x01)         */
#define ISO7816_CFG_TXRTYERRIE            ISO7816_CFG_TXRTYERRIE_Msk
#define ISO7816_CFG_RXOVIE_Pos            (7UL)                     /*!< ISO7816 CFG: RXOVIE (Bit 7)                           */
#define ISO7816_CFG_RXOVIE_Msk            (0x80UL)                  /*!< ISO7816 CFG: RXOVIE (Bitfield-Mask: 0x01)             */
#define ISO7816_CFG_RXOVIE                ISO7816_CFG_RXOVIE_Msk
#define ISO7816_CFG_TXDONEIE_Pos          (6UL)                     /*!< ISO7816 CFG: TXDONEIE (Bit 6)                         */
#define ISO7816_CFG_TXDONEIE_Msk          (0x40UL)                  /*!< ISO7816 CFG: TXDONEIE (Bitfield-Mask: 0x01)           */
#define ISO7816_CFG_TXDONEIE              ISO7816_CFG_TXDONEIE_Msk
#define ISO7816_CFG_RXIE_Pos              (5UL)                     /*!< ISO7816 CFG: RXIE (Bit 5)                             */
#define ISO7816_CFG_RXIE_Msk              (0x20UL)                  /*!< ISO7816 CFG: RXIE (Bitfield-Mask: 0x01)               */
#define ISO7816_CFG_RXIE                  ISO7816_CFG_RXIE_Msk
#define ISO7816_CFG_ACKLEN_Pos            (4UL)                     /*!< ISO7816 CFG: ACKLEN (Bit 4)                           */
#define ISO7816_CFG_ACKLEN_Msk            (0x10UL)                  /*!< ISO7816 CFG: ACKLEN (Bitfield-Mask: 0x01)             */
#define ISO7816_CFG_ACKLEN                ISO7816_CFG_ACKLEN_Msk
#define ISO7816_CFG_RXERRIE_Pos           (2UL)                     /*!< ISO7816 CFG: RXERRIE (Bit 2)                          */
#define ISO7816_CFG_RXERRIE_Msk           (0x4UL)                   /*!< ISO7816 CFG: RXERRIE (Bitfield-Mask: 0x01)            */
#define ISO7816_CFG_RXERRIE               ISO7816_CFG_RXERRIE_Msk
#define ISO7816_CFG_CHKP_Pos              (1UL)                     /*!< ISO7816 CFG: CHKP (Bit 1)                             */
#define ISO7816_CFG_CHKP_Msk              (0x2UL)                   /*!< ISO7816 CFG: CHKP (Bitfield-Mask: 0x01)               */
#define ISO7816_CFG_CHKP                  ISO7816_CFG_CHKP_Msk
#define ISO7816_CFG_EN_Pos                (0UL)                     /*!< ISO7816 CFG: EN (Bit 0)                               */
#define ISO7816_CFG_EN_Msk                (0x1UL)                   /*!< ISO7816 CFG: EN (Bitfield-Mask: 0x01)                 */
#define ISO7816_CFG_EN                    ISO7816_CFG_EN_Msk
/* ==========================================================  CLK  ========================================================== */
#define ISO7816_CLK_CLKEN_Pos             (7UL)                     /*!< ISO7816 CLK: CLKEN (Bit 7)                            */
#define ISO7816_CLK_CLKEN_Msk             (0x80UL)                  /*!< ISO7816 CLK: CLKEN (Bitfield-Mask: 0x01)              */
#define ISO7816_CLK_CLKEN                 ISO7816_CLK_CLKEN_Msk
#define ISO7816_CLK_CLKDIV_Pos            (0UL)                     /*!< ISO7816 CLK: CLKDIV (Bit 0)                           */
#define ISO7816_CLK_CLKDIV_Msk            (0x7fUL)                  /*!< ISO7816 CLK: CLKDIV (Bitfield-Mask: 0x7f)             */
#define ISO7816_CLK_CLKDIV                ISO7816_CLK_CLKDIV_Msk


/* =========================================================================================================================== */
/* ================                                            LCD                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  FB  =========================================================== */
#define LCD_FB_DATA_Pos                   (0UL)                     /*!< LCD FB: DATA (Bit 0)                                  */
#define LCD_FB_DATA_Msk                   (0xffffffffUL)            /*!< LCD FB: DATA (Bitfield-Mask: 0xffffffff)              */
#define LCD_FB_DATA                       LCD_FB_DATA_Msk
/* =========================================================  CTRL  ========================================================== */
#define LCD_CTRL_EN_Pos                   (7UL)                     /*!< LCD CTRL: EN (Bit 7)                                  */
#define LCD_CTRL_EN_Msk                   (0x80UL)                  /*!< LCD CTRL: EN (Bitfield-Mask: 0x01)                    */
#define LCD_CTRL_EN                       LCD_CTRL_EN_Msk
#define LCD_CTRL_TYPE_Pos                 (4UL)                     /*!< LCD CTRL: TYPE (Bit 4)                                */
#define LCD_CTRL_TYPE_Msk                 (0x30UL)                  /*!< LCD CTRL: TYPE (Bitfield-Mask: 0x03)                  */
#define LCD_CTRL_TYPE                     LCD_CTRL_TYPE_Msk
#define LCD_CTRL_DRV_Pos                  (2UL)                     /*!< LCD CTRL: DRV (Bit 2)                                 */
#define LCD_CTRL_DRV_Msk                  (0xcUL)                   /*!< LCD CTRL: DRV (Bitfield-Mask: 0x03)                   */
#define LCD_CTRL_DRV                      LCD_CTRL_DRV_Msk
#define LCD_CTRL_FRQ_Pos                  (0UL)                     /*!< LCD CTRL: FRQ (Bit 0)                                 */
#define LCD_CTRL_FRQ_Msk                  (0x3UL)                   /*!< LCD CTRL: FRQ (Bitfield-Mask: 0x03)                   */
#define LCD_CTRL_FRQ                      LCD_CTRL_FRQ_Msk
/* =========================================================  CTRL2  ========================================================= */
#define LCD_CTRL2_SWPR_Pos                (8UL)                     /*!< LCD CTRL2: SWPR (Bit 8)                               */
#define LCD_CTRL2_SWPR_Msk                (0xff00UL)                /*!< LCD CTRL2: SWPR (Bitfield-Mask: 0xff)                 */
#define LCD_CTRL2_SWPR                    LCD_CTRL2_SWPR_Msk
#define LCD_CTRL2_FBMODE_Pos              (6UL)                     /*!< LCD CTRL2: FBMODE (Bit 6)                             */
#define LCD_CTRL2_FBMODE_Msk              (0xc0UL)                  /*!< LCD CTRL2: FBMODE (Bitfield-Mask: 0x03)               */
#define LCD_CTRL2_FBMODE                  LCD_CTRL2_FBMODE_Msk
#define LCD_CTRL2_BKFILL_Pos              (4UL)                     /*!< LCD CTRL2: BKFILL (Bit 4)                             */
#define LCD_CTRL2_BKFILL_Msk              (0x10UL)                  /*!< LCD CTRL2: BKFILL (Bitfield-Mask: 0x01)               */
#define LCD_CTRL2_BKFILL                  LCD_CTRL2_BKFILL_Msk
/* =======================================================  SEGCTRL0  ======================================================== */
#define LCD_SEGCTRL0_SEGCTRL_Pos          (0UL)                     /*!< LCD SEGCTRL0: SEGCTRL (Bit 0)                         */
#define LCD_SEGCTRL0_SEGCTRL_Msk          (0xffffffffUL)            /*!< LCD SEGCTRL0: SEGCTRL (Bitfield-Mask: 0xffffffff)     */
#define LCD_SEGCTRL0_SEGCTRL              LCD_SEGCTRL0_SEGCTRL_Msk
/* =======================================================  SEGCTRL1  ======================================================== */
#define LCD_SEGCTRL1_SEGCTRL_Pos          (0UL)                     /*!< LCD SEGCTRL1: SEGCTRL (Bit 0)                         */
#define LCD_SEGCTRL1_SEGCTRL_Msk          (0xffffffffUL)            /*!< LCD SEGCTRL1: SEGCTRL (Bitfield-Mask: 0xffffffff)     */
#define LCD_SEGCTRL1_SEGCTRL              LCD_SEGCTRL1_SEGCTRL_Msk
/* =======================================================  SEGCTRL2  ======================================================== */
#define LCD_SEGCTRL2_SEGCTRL_Pos          (0UL)                     /*!< LCD SEGCTRL2: SEGCTRL (Bit 0)                         */
#define LCD_SEGCTRL2_SEGCTRL_Msk          (0xffffUL)                /*!< LCD SEGCTRL2: SEGCTRL (Bitfield-Mask: 0xffff)         */
#define LCD_SEGCTRL2_SEGCTRL              LCD_SEGCTRL2_SEGCTRL_Msk


/* =========================================================================================================================== */
/* ================                                           MISC1                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  SRAMINT  ======================================================== */
#define MISC1_SRAMINT_LOCKUP_Pos          (4UL)                     /*!< MISC1 SRAMINT: LOCKUP (Bit 4)                         */
#define MISC1_SRAMINT_LOCKUP_Msk          (0x10UL)                  /*!< MISC1 SRAMINT: LOCKUP (Bitfield-Mask: 0x01)           */
#define MISC1_SRAMINT_LOCKUP              MISC1_SRAMINT_LOCKUP_Msk
#define MISC1_SRAMINT_PIAC_Pos            (3UL)                     /*!< MISC1 SRAMINT: PIAC (Bit 3)                           */
#define MISC1_SRAMINT_PIAC_Msk            (0x8UL)                   /*!< MISC1 SRAMINT: PIAC (Bitfield-Mask: 0x01)             */
#define MISC1_SRAMINT_PIAC                MISC1_SRAMINT_PIAC_Msk
#define MISC1_SRAMINT_HIAC_Pos            (2UL)                     /*!< MISC1 SRAMINT: HIAC (Bit 2)                           */
#define MISC1_SRAMINT_HIAC_Msk            (0x4UL)                   /*!< MISC1 SRAMINT: HIAC (Bitfield-Mask: 0x01)             */
#define MISC1_SRAMINT_HIAC                MISC1_SRAMINT_HIAC_Msk
#define MISC1_SRAMINT_HIAL_Pos            (1UL)                     /*!< MISC1 SRAMINT: HIAL (Bit 1)                           */
#define MISC1_SRAMINT_HIAL_Msk            (0x2UL)                   /*!< MISC1 SRAMINT: HIAL (Bitfield-Mask: 0x01)             */
#define MISC1_SRAMINT_HIAL                MISC1_SRAMINT_HIAL_Msk
#define MISC1_SRAMINT_PERR_Pos            (0UL)                     /*!< MISC1 SRAMINT: PERR (Bit 0)                           */
#define MISC1_SRAMINT_PERR_Msk            (0x1UL)                   /*!< MISC1 SRAMINT: PERR (Bitfield-Mask: 0x01)             */
#define MISC1_SRAMINT_PERR                MISC1_SRAMINT_PERR_Msk
/* =======================================================  SRAMINIT  ======================================================== */
#define MISC1_SRAMINIT_LOCKIE_Pos         (7UL)                     /*!< MISC1 SRAMINIT: LOCKIE (Bit 7)                        */
#define MISC1_SRAMINIT_LOCKIE_Msk         (0x80UL)                  /*!< MISC1 SRAMINIT: LOCKIE (Bitfield-Mask: 0x01)          */
#define MISC1_SRAMINIT_LOCKIE             MISC1_SRAMINIT_LOCKIE_Msk
#define MISC1_SRAMINIT_PIACIE_Pos         (6UL)                     /*!< MISC1 SRAMINIT: PIACIE (Bit 6)                        */
#define MISC1_SRAMINIT_PIACIE_Msk         (0x40UL)                  /*!< MISC1 SRAMINIT: PIACIE (Bitfield-Mask: 0x01)          */
#define MISC1_SRAMINIT_PIACIE             MISC1_SRAMINIT_PIACIE_Msk
#define MISC1_SRAMINIT_HIACIE_Pos         (5UL)                     /*!< MISC1 SRAMINIT: HIACIE (Bit 5)                        */
#define MISC1_SRAMINIT_HIACIE_Msk         (0x20UL)                  /*!< MISC1 SRAMINIT: HIACIE (Bitfield-Mask: 0x01)          */
#define MISC1_SRAMINIT_HIACIE             MISC1_SRAMINIT_HIACIE_Msk
#define MISC1_SRAMINIT_INIT_Pos           (2UL)                     /*!< MISC1 SRAMINIT: INIT (Bit 2)                          */
#define MISC1_SRAMINIT_INIT_Msk           (0x4UL)                   /*!< MISC1 SRAMINIT: INIT (Bitfield-Mask: 0x01)            */
#define MISC1_SRAMINIT_INIT               MISC1_SRAMINIT_INIT_Msk
#define MISC1_SRAMINIT_PERRIE_Pos         (1UL)                     /*!< MISC1 SRAMINIT: PERRIE (Bit 1)                        */
#define MISC1_SRAMINIT_PERRIE_Msk         (0x2UL)                   /*!< MISC1 SRAMINIT: PERRIE (Bitfield-Mask: 0x01)          */
#define MISC1_SRAMINIT_PERRIE             MISC1_SRAMINIT_PERRIE_Msk
#define MISC1_SRAMINIT_PEN_Pos            (0UL)                     /*!< MISC1 SRAMINIT: PEN (Bit 0)                           */
#define MISC1_SRAMINIT_PEN_Msk            (0x1UL)                   /*!< MISC1 SRAMINIT: PEN (Bitfield-Mask: 0x01)             */
#define MISC1_SRAMINIT_PEN                MISC1_SRAMINIT_PEN_Msk
/* ========================================================  PARERR  ========================================================= */
#define MISC1_PARERR_PEADDR_Pos           (0UL)                     /*!< MISC1 PARERR: PEADDR (Bit 0)                          */
#define MISC1_PARERR_PEADDR_Msk           (0x3fffUL)                /*!< MISC1 PARERR: PEADDR (Bitfield-Mask: 0x3fff)          */
#define MISC1_PARERR_PEADDR               MISC1_PARERR_PEADDR_Msk
/* =========================================================  IREN  ========================================================== */
#define MISC1_IREN_IREN_Pos               (0UL)                     /*!< MISC1 IREN: IREN (Bit 0)                              */
#define MISC1_IREN_IREN_Msk               (0x3fUL)                  /*!< MISC1 IREN: IREN (Bitfield-Mask: 0x3f)                */
#define MISC1_IREN_IREN                   MISC1_IREN_IREN_Msk
/* =========================================================  DUTYL  ========================================================= */
#define MISC1_DUTYL_DUTYL_Pos             (0UL)                     /*!< MISC1 DUTYL: DUTYL (Bit 0)                            */
#define MISC1_DUTYL_DUTYL_Msk             (0xffffUL)                /*!< MISC1 DUTYL: DUTYL (Bitfield-Mask: 0xffff)            */
#define MISC1_DUTYL_DUTYL                 MISC1_DUTYL_DUTYL_Msk
/* =========================================================  DUTYH  ========================================================= */
#define MISC1_DUTYH_DUTYH_Pos             (0UL)                     /*!< MISC1 DUTYH: DUTYH (Bit 0)                            */
#define MISC1_DUTYH_DUTYH_Msk             (0xffffUL)                /*!< MISC1 DUTYH: DUTYH (Bitfield-Mask: 0xffff)            */
#define MISC1_DUTYH_DUTYH                 MISC1_DUTYH_DUTYH_Msk
/* ========================================================  IRQLAT  ========================================================= */
#define MISC1_IRQLAT_NOHARDFAULT_Pos      (9UL)                     /*!< MISC1 IRQLAT: NOHARDFAULT (Bit 9)                     */
#define MISC1_IRQLAT_NOHARDFAULT_Msk      (0x200UL)                 /*!< MISC1 IRQLAT: NOHARDFAULT (Bitfield-Mask: 0x01)       */
#define MISC1_IRQLAT_NOHARDFAULT          MISC1_IRQLAT_NOHARDFAULT_Msk
#define MISC1_IRQLAT_LOCKRESET_Pos        (8UL)                     /*!< MISC1 IRQLAT: LOCKRESET (Bit 8)                       */
#define MISC1_IRQLAT_LOCKRESET_Msk        (0x100UL)                 /*!< MISC1 IRQLAT: LOCKRESET (Bitfield-Mask: 0x01)         */
#define MISC1_IRQLAT_LOCKRESET            MISC1_IRQLAT_LOCKRESET_Msk
#define MISC1_IRQLAT_IRQLAT_Pos           (0UL)                     /*!< MISC1 IRQLAT: IRQLAT (Bit 0)                          */
#define MISC1_IRQLAT_IRQLAT_Msk           (0xffUL)                  /*!< MISC1 IRQLAT: IRQLAT (Bitfield-Mask: 0xff)            */
#define MISC1_IRQLAT_IRQLAT               MISC1_IRQLAT_IRQLAT_Msk
/* ========================================================  HIADDR  ========================================================= */
#define MISC1_HIADDR_HIADDR_Pos           (0UL)                     /*!< MISC1 HIADDR: HIADDR (Bit 0)                          */
#define MISC1_HIADDR_HIADDR_Msk           (0xffffffffUL)            /*!< MISC1 HIADDR: HIADDR (Bitfield-Mask: 0xffffffff)      */
#define MISC1_HIADDR_HIADDR               MISC1_HIADDR_HIADDR_Msk
/* ========================================================  PIADDR  ========================================================= */
#define MISC1_PIADDR_PIADDR_Pos           (0UL)                     /*!< MISC1 PIADDR: PIADDR (Bit 0)                          */
#define MISC1_PIADDR_PIADDR_Msk           (0xffffffffUL)            /*!< MISC1 PIADDR: PIADDR (Bitfield-Mask: 0xffffffff)      */
#define MISC1_PIADDR_PIADDR               MISC1_PIADDR_PIADDR_Msk


/* =========================================================================================================================== */
/* ================                                           MISC2                                           ================ */
/* =========================================================================================================================== */

/* ========================================================  FLASHWC  ======================================================== */
#define MISC2_FLASHWC_CYCLE_1US_Pos       (8UL)                     /*!< MISC2 FLASHWC: CYCLE_1US (Bit 8)                      */
#define MISC2_FLASHWC_CYCLE_1US_Msk       (0x3f00UL)                /*!< MISC2 FLASHWC: CYCLE_1US (Bitfield-Mask: 0x3f)        */
#define MISC2_FLASHWC_CYCLE_1US           MISC2_FLASHWC_CYCLE_1US_Msk
/* ========================================================  CLKSEL  ========================================================= */
#define MISC2_CLKSEL_CLKSEL_Pos           (0UL)                     /*!< MISC2 CLKSEL: CLKSEL (Bit 0)                          */
#define MISC2_CLKSEL_CLKSEL_Msk           (0x7UL)                   /*!< MISC2 CLKSEL: CLKSEL (Bitfield-Mask: 0x07)            */
#define MISC2_CLKSEL_CLKSEL               MISC2_CLKSEL_CLKSEL_Msk
/* ========================================================  CLKDIVH  ======================================================== */
#define MISC2_CLKDIVH_CLKDIVH_Pos         (0UL)                     /*!< MISC2 CLKDIVH: CLKDIVH (Bit 0)                        */
#define MISC2_CLKDIVH_CLKDIVH_Msk         (0xffUL)                  /*!< MISC2 CLKDIVH: CLKDIVH (Bitfield-Mask: 0xff)          */
#define MISC2_CLKDIVH_CLKDIVH             MISC2_CLKDIVH_CLKDIVH_Msk
/* ========================================================  CLKDIVP  ======================================================== */
#define MISC2_CLKDIVP_CLKDIVP_Pos         (0UL)                     /*!< MISC2 CLKDIVP: CLKDIVP (Bit 0)                        */
#define MISC2_CLKDIVP_CLKDIVP_Msk         (0xffUL)                  /*!< MISC2 CLKDIVP: CLKDIVP (Bitfield-Mask: 0xff)          */
#define MISC2_CLKDIVP_CLKDIVP             MISC2_CLKDIVP_CLKDIVP_Msk
/* ========================================================  HCLKEN  ========================================================= */
#define MISC2_HCLKEN_CRYPT_Pos            (8UL)                     /*!< MISC2 HCLKEN: CRYPT (Bit 8)                           */
#define MISC2_HCLKEN_CRYPT_Msk            (0x100UL)                 /*!< MISC2 HCLKEN: CRYPT (Bitfield-Mask: 0x01)             */
#define MISC2_HCLKEN_CRYPT                MISC2_HCLKEN_CRYPT_Msk
#define MISC2_HCLKEN_LCD_Pos              (6UL)                     /*!< MISC2 HCLKEN: LCD (Bit 6)                             */
#define MISC2_HCLKEN_LCD_Msk              (0x40UL)                  /*!< MISC2 HCLKEN: LCD (Bitfield-Mask: 0x01)               */
#define MISC2_HCLKEN_LCD                  MISC2_HCLKEN_LCD_Msk
#define MISC2_HCLKEN_GPIO_Pos             (5UL)                     /*!< MISC2 HCLKEN: GPIO (Bit 5)                            */
#define MISC2_HCLKEN_GPIO_Msk             (0x20UL)                  /*!< MISC2 HCLKEN: GPIO (Bitfield-Mask: 0x01)              */
#define MISC2_HCLKEN_GPIO                 MISC2_HCLKEN_GPIO_Msk
#define MISC2_HCLKEN_DMA_Pos              (4UL)                     /*!< MISC2 HCLKEN: DMA (Bit 4)                             */
#define MISC2_HCLKEN_DMA_Msk              (0x10UL)                  /*!< MISC2 HCLKEN: DMA (Bitfield-Mask: 0x01)               */
#define MISC2_HCLKEN_DMA                  MISC2_HCLKEN_DMA_Msk
/* ========================================================  PCLKEN  ========================================================= */
#define MISC2_PCLKEN_SPI3_Pos             (22UL)                    /*!< MISC2 PCLKEN: SPI3 (Bit 22)                           */
#define MISC2_PCLKEN_SPI3_Msk             (0x400000UL)              /*!< MISC2 PCLKEN: SPI3 (Bitfield-Mask: 0x01)              */
#define MISC2_PCLKEN_SPI3                 MISC2_PCLKEN_SPI3_Msk
#define MISC2_PCLKEN_SPI2_Pos             (21UL)                    /*!< MISC2 PCLKEN: SPI2 (Bit 21)                           */
#define MISC2_PCLKEN_SPI2_Msk             (0x200000UL)              /*!< MISC2 PCLKEN: SPI2 (Bitfield-Mask: 0x01)              */
#define MISC2_PCLKEN_SPI2                 MISC2_PCLKEN_SPI2_Msk
#define MISC2_PCLKEN_U32K1_Pos            (19UL)                    /*!< MISC2 PCLKEN: U32K1 (Bit 19)                          */
#define MISC2_PCLKEN_U32K1_Msk            (0x80000UL)               /*!< MISC2 PCLKEN: U32K1 (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_U32K1                MISC2_PCLKEN_U32K1_Msk
#define MISC2_PCLKEN_U32K0_Pos            (18UL)                    /*!< MISC2 PCLKEN: U32K0 (Bit 18)                          */
#define MISC2_PCLKEN_U32K0_Msk            (0x40000UL)               /*!< MISC2 PCLKEN: U32K0 (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_U32K0                MISC2_PCLKEN_U32K0_Msk
#define MISC2_PCLKEN_ANA_Pos              (17UL)                    /*!< MISC2 PCLKEN: ANA (Bit 17)                            */
#define MISC2_PCLKEN_ANA_Msk              (0x20000UL)               /*!< MISC2 PCLKEN: ANA (Bitfield-Mask: 0x01)               */
#define MISC2_PCLKEN_ANA                  MISC2_PCLKEN_ANA_Msk
#define MISC2_PCLKEN_RTC_Pos              (16UL)                    /*!< MISC2 PCLKEN: RTC (Bit 16)                            */
#define MISC2_PCLKEN_RTC_Msk              (0x10000UL)               /*!< MISC2 PCLKEN: RTC (Bitfield-Mask: 0x01)               */
#define MISC2_PCLKEN_RTC                  MISC2_PCLKEN_RTC_Msk
#define MISC2_PCLKEN_PMU_Pos              (15UL)                    /*!< MISC2 PCLKEN: PMU (Bit 15)                            */
#define MISC2_PCLKEN_PMU_Msk              (0x8000UL)                /*!< MISC2 PCLKEN: PMU (Bitfield-Mask: 0x01)               */
#define MISC2_PCLKEN_PMU                  MISC2_PCLKEN_PMU_Msk
#define MISC2_PCLKEN_MISC2_Pos            (14UL)                    /*!< MISC2 PCLKEN: MISC2 (Bit 14)                          */
#define MISC2_PCLKEN_MISC2_Msk            (0x4000UL)                /*!< MISC2 PCLKEN: MISC2 (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_MISC2                MISC2_PCLKEN_MISC2_Msk
#define MISC2_PCLKEN_MISC1_Pos            (13UL)                    /*!< MISC2 PCLKEN: MISC1 (Bit 13)                          */
#define MISC2_PCLKEN_MISC1_Msk            (0x2000UL)                /*!< MISC2 PCLKEN: MISC1 (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_MISC1                MISC2_PCLKEN_MISC1_Msk
#define MISC2_PCLKEN_TIMER_Pos            (12UL)                    /*!< MISC2 PCLKEN: TIMER (Bit 12)                          */
#define MISC2_PCLKEN_TIMER_Msk            (0x1000UL)                /*!< MISC2 PCLKEN: TIMER (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_TIMER                MISC2_PCLKEN_TIMER_Msk
#define MISC2_PCLKEN_ISO78161_Pos         (11UL)                    /*!< MISC2 PCLKEN: ISO78161 (Bit 11)                       */
#define MISC2_PCLKEN_ISO78161_Msk         (0x800UL)                 /*!< MISC2 PCLKEN: ISO78161 (Bitfield-Mask: 0x01)          */
#define MISC2_PCLKEN_ISO78161             MISC2_PCLKEN_ISO78161_Msk
#define MISC2_PCLKEN_ISO78160_Pos         (10UL)                    /*!< MISC2 PCLKEN: ISO78160 (Bit 10)                       */
#define MISC2_PCLKEN_ISO78160_Msk         (0x400UL)                 /*!< MISC2 PCLKEN: ISO78160 (Bitfield-Mask: 0x01)          */
#define MISC2_PCLKEN_ISO78160             MISC2_PCLKEN_ISO78160_Msk
#define MISC2_PCLKEN_UART5_Pos            (9UL)                     /*!< MISC2 PCLKEN: UART5 (Bit 9)                           */
#define MISC2_PCLKEN_UART5_Msk            (0x200UL)                 /*!< MISC2 PCLKEN: UART5 (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_UART5                MISC2_PCLKEN_UART5_Msk
#define MISC2_PCLKEN_UART4_Pos            (8UL)                     /*!< MISC2 PCLKEN: UART4 (Bit 8)                           */
#define MISC2_PCLKEN_UART4_Msk            (0x100UL)                 /*!< MISC2 PCLKEN: UART4 (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_UART4                MISC2_PCLKEN_UART4_Msk
#define MISC2_PCLKEN_UART3_Pos            (7UL)                     /*!< MISC2 PCLKEN: UART3 (Bit 7)                           */
#define MISC2_PCLKEN_UART3_Msk            (0x80UL)                  /*!< MISC2 PCLKEN: UART3 (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_UART3                MISC2_PCLKEN_UART3_Msk
#define MISC2_PCLKEN_UART2_Pos            (6UL)                     /*!< MISC2 PCLKEN: UART2 (Bit 6)                           */
#define MISC2_PCLKEN_UART2_Msk            (0x40UL)                  /*!< MISC2 PCLKEN: UART2 (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_UART2                MISC2_PCLKEN_UART2_Msk
#define MISC2_PCLKEN_UART1_Pos            (5UL)                     /*!< MISC2 PCLKEN: UART1 (Bit 5)                           */
#define MISC2_PCLKEN_UART1_Msk            (0x20UL)                  /*!< MISC2 PCLKEN: UART1 (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_UART1                MISC2_PCLKEN_UART1_Msk
#define MISC2_PCLKEN_UART0_Pos            (4UL)                     /*!< MISC2 PCLKEN: UART0 (Bit 4)                           */
#define MISC2_PCLKEN_UART0_Msk            (0x10UL)                  /*!< MISC2 PCLKEN: UART0 (Bitfield-Mask: 0x01)             */
#define MISC2_PCLKEN_UART0                MISC2_PCLKEN_UART0_Msk
#define MISC2_PCLKEN_SPI1_Pos             (3UL)                     /*!< MISC2 PCLKEN: SPI1 (Bit 3)                            */
#define MISC2_PCLKEN_SPI1_Msk             (0x8UL)                   /*!< MISC2 PCLKEN: SPI1 (Bitfield-Mask: 0x01)              */
#define MISC2_PCLKEN_SPI1                 MISC2_PCLKEN_SPI1_Msk
#define MISC2_PCLKEN_I2C_Pos              (2UL)                     /*!< MISC2 PCLKEN: I2C (Bit 2)                             */
#define MISC2_PCLKEN_I2C_Msk              (0x4UL)                   /*!< MISC2 PCLKEN: I2C (Bitfield-Mask: 0x01)               */
#define MISC2_PCLKEN_I2C                  MISC2_PCLKEN_I2C_Msk
#define MISC2_PCLKEN_DMA_Pos              (1UL)                     /*!< MISC2 PCLKEN: DMA (Bit 1)                             */
#define MISC2_PCLKEN_DMA_Msk              (0x2UL)                   /*!< MISC2 PCLKEN: DMA (Bitfield-Mask: 0x01)               */
#define MISC2_PCLKEN_DMA                  MISC2_PCLKEN_DMA_Msk


/* =========================================================================================================================== */
/* ================                                            PMU                                            ================ */
/* =========================================================================================================================== */

/* =======================================================  DSLEEPEN  ======================================================== */
#define PMU_DSLEEPEN_WKU_Pos              (31UL)                    /*!< PMU DSLEEPEN: WKU (Bit 31)                            */
#define PMU_DSLEEPEN_WKU_Msk              (0x80000000UL)            /*!< PMU DSLEEPEN: WKU (Bitfield-Mask: 0x01)               */
#define PMU_DSLEEPEN_WKU                  PMU_DSLEEPEN_WKU_Msk
/* ======================================================  DSLEEPPASS  ======================================================= */
#define PMU_DSLEEPPASS_UNLOCK_Pos         (0UL)                     /*!< PMU DSLEEPPASS: UNLOCK (Bit 0)                        */
#define PMU_DSLEEPPASS_UNLOCK_Msk         (0x1UL)                   /*!< PMU DSLEEPPASS: UNLOCK (Bitfield-Mask: 0x01)          */
#define PMU_DSLEEPPASS_UNLOCK             PMU_DSLEEPPASS_UNLOCK_Msk
/* ========================================================  CONTROL  ======================================================== */
#define PMU_CONTROL_FORCE_CLKSEL_RCH_Pos  (20UL)                    /*!< PMU CONTROL: FORCE_CLKSEL_RCH (Bit 20)                */
#define PMU_CONTROL_FORCE_CLKSEL_RCH_Msk  (0x100000UL)              /*!< PMU CONTROL: FORCE_CLKSEL_RCH (Bitfield-Mask: 0x01)   */
#define PMU_CONTROL_FORCE_CLKSEL_RCH      PMU_CONTROL_FORCE_CLKSEL_RCH_Msk
#define PMU_CONTROL_PWUPCYC_Pos           (8UL)                     /*!< PMU CONTROL: PWUPCYC (Bit 8)                          */
#define PMU_CONTROL_PWUPCYC_Msk           (0xff00UL)                /*!< PMU CONTROL: PWUPCYC (Bitfield-Mask: 0xff)            */
#define PMU_CONTROL_PWUPCYC               PMU_CONTROL_PWUPCYC_Msk
#define PMU_CONTROL_PLLL_SEL_Pos          (5UL)                     /*!< PMU CONTROL: PLLL_SEL (Bit 5)                         */
#define PMU_CONTROL_PLLL_SEL_Msk          (0x20UL)                  /*!< PMU CONTROL: PLLL_SEL (Bitfield-Mask: 0x01)           */
#define PMU_CONTROL_PLLL_SEL              PMU_CONTROL_PLLL_SEL_Msk
#define PMU_CONTROL_PLLH_SEL_Pos          (4UL)                     /*!< PMU CONTROL: PLLH_SEL (Bit 4)                         */
#define PMU_CONTROL_PLLH_SEL_Msk          (0x10UL)                  /*!< PMU CONTROL: PLLH_SEL (Bitfield-Mask: 0x01)           */
#define PMU_CONTROL_PLLH_SEL              PMU_CONTROL_PLLH_SEL_Msk
#define PMU_CONTROL_INT_6M_EN_Pos         (3UL)                     /*!< PMU CONTROL: INT_6M_EN (Bit 3)                        */
#define PMU_CONTROL_INT_6M_EN_Msk         (0x8UL)                   /*!< PMU CONTROL: INT_6M_EN (Bitfield-Mask: 0x01)          */
#define PMU_CONTROL_INT_6M_EN             PMU_CONTROL_INT_6M_EN_Msk
#define PMU_CONTROL_INT_32K_EN_Pos        (2UL)                     /*!< PMU CONTROL: INT_32K_EN (Bit 2)                       */
#define PMU_CONTROL_INT_32K_EN_Msk        (0x4UL)                   /*!< PMU CONTROL: INT_32K_EN (Bitfield-Mask: 0x01)         */
#define PMU_CONTROL_INT_32K_EN            PMU_CONTROL_INT_32K_EN_Msk
#define PMU_CONTROL_RTCCLK_SEL_Pos        (1UL)                     /*!< PMU CONTROL: RTCCLK_SEL (Bit 1)                       */
#define PMU_CONTROL_RTCCLK_SEL_Msk        (0x2UL)                   /*!< PMU CONTROL: RTCCLK_SEL (Bitfield-Mask: 0x01)         */
#define PMU_CONTROL_RTCCLK_SEL            PMU_CONTROL_RTCCLK_SEL_Msk
#define PMU_CONTROL_INT_IOA_EN_Pos        (0UL)                     /*!< PMU CONTROL: INT_IOA_EN (Bit 0)                       */
#define PMU_CONTROL_INT_IOA_EN_Msk        (0x1UL)                   /*!< PMU CONTROL: INT_IOA_EN (Bitfield-Mask: 0x01)         */
#define PMU_CONTROL_INT_IOA_EN            PMU_CONTROL_INT_IOA_EN_Msk
/* ==========================================================  STS  ========================================================== */
#define PMU_STS_MODE_Pos                  (24UL)                    /*!< PMU STS: MODE (Bit 24)                                */
#define PMU_STS_MODE_Msk                  (0x1000000UL)             /*!< PMU STS: MODE (Bitfield-Mask: 0x01)                   */
#define PMU_STS_MODE                      PMU_STS_MODE_Msk
#define PMU_STS_WKUMODE_Pos               (22UL)                    /*!< PMU STS: WKUMODE (Bit 22)                             */
#define PMU_STS_WKUMODE_Msk               (0x400000UL)              /*!< PMU STS: WKUMODE (Bitfield-Mask: 0x01)                */
#define PMU_STS_WKUMODE                   PMU_STS_WKUMODE_Msk
#define PMU_STS_WKUXTAL_Pos               (20UL)                    /*!< PMU STS: WKUXTAL (Bit 20)                             */
#define PMU_STS_WKUXTAL_Msk               (0x100000UL)              /*!< PMU STS: WKUXTAL (Bitfield-Mask: 0x01)                */
#define PMU_STS_WKUXTAL                   PMU_STS_WKUXTAL_Msk
#define PMU_STS_WKUU32K_Pos               (19UL)                    /*!< PMU STS: WKUU32K (Bit 19)                             */
#define PMU_STS_WKUU32K_Msk               (0x80000UL)               /*!< PMU STS: WKUU32K (Bitfield-Mask: 0x01)                */
#define PMU_STS_WKUU32K                   PMU_STS_WKUU32K_Msk
#define PMU_STS_WKUANA_Pos                (18UL)                    /*!< PMU STS: WKUANA (Bit 18)                              */
#define PMU_STS_WKUANA_Msk                (0x40000UL)               /*!< PMU STS: WKUANA (Bitfield-Mask: 0x01)                 */
#define PMU_STS_WKUANA                    PMU_STS_WKUANA_Msk
#define PMU_STS_WKURTC_Pos                (17UL)                    /*!< PMU STS: WKURTC (Bit 17)                              */
#define PMU_STS_WKURTC_Msk                (0x20000UL)               /*!< PMU STS: WKURTC (Bitfield-Mask: 0x01)                 */
#define PMU_STS_WKURTC                    PMU_STS_WKURTC_Msk
#define PMU_STS_WKUIOA_Pos                (16UL)                    /*!< PMU STS: WKUIOA (Bit 16)                              */
#define PMU_STS_WKUIOA_Msk                (0x10000UL)               /*!< PMU STS: WKUIOA (Bitfield-Mask: 0x01)                 */
#define PMU_STS_WKUIOA                    PMU_STS_WKUIOA_Msk
#define PMU_STS_MODERST_Pos               (10UL)                    /*!< PMU STS: MODERST (Bit 10)                             */
#define PMU_STS_MODERST_Msk               (0x400UL)                 /*!< PMU STS: MODERST (Bitfield-Mask: 0x01)                */
#define PMU_STS_MODERST                   PMU_STS_MODERST_Msk
#define PMU_STS_SFTRST_Pos                (8UL)                     /*!< PMU STS: SFTRST (Bit 8)                               */
#define PMU_STS_SFTRST_Msk                (0x100UL)                 /*!< PMU STS: SFTRST (Bitfield-Mask: 0x01)                 */
#define PMU_STS_SFTRST                    PMU_STS_SFTRST_Msk
#define PMU_STS_WDTRST_Pos                (7UL)                     /*!< PMU STS: WDTRST (Bit 7)                               */
#define PMU_STS_WDTRST_Msk                (0x80UL)                  /*!< PMU STS: WDTRST (Bitfield-Mask: 0x01)                 */
#define PMU_STS_WDTRST                    PMU_STS_WDTRST_Msk
#define PMU_STS_DPORST_Pos                (6UL)                     /*!< PMU STS: DPORST (Bit 6)                               */
#define PMU_STS_DPORST_Msk                (0x40UL)                  /*!< PMU STS: DPORST (Bitfield-Mask: 0x01)                 */
#define PMU_STS_DPORST                    PMU_STS_DPORST_Msk
#define PMU_STS_PORST_Pos                 (5UL)                     /*!< PMU STS: PORST (Bit 5)                                */
#define PMU_STS_PORST_Msk                 (0x20UL)                  /*!< PMU STS: PORST (Bitfield-Mask: 0x01)                  */
#define PMU_STS_PORST                     PMU_STS_PORST_Msk
#define PMU_STS_EXTRST_Pos                (4UL)                     /*!< PMU STS: EXTRST (Bit 4)                               */
#define PMU_STS_EXTRST_Msk                (0x10UL)                  /*!< PMU STS: EXTRST (Bitfield-Mask: 0x01)                 */
#define PMU_STS_EXTRST                    PMU_STS_EXTRST_Msk
#define PMU_STS_EXIST_6M_Pos              (3UL)                     /*!< PMU STS: EXIST_6M (Bit 3)                             */
#define PMU_STS_EXIST_6M_Msk              (0x8UL)                   /*!< PMU STS: EXIST_6M (Bitfield-Mask: 0x01)               */
#define PMU_STS_EXIST_6M                  PMU_STS_EXIST_6M_Msk
#define PMU_STS_EXIST_32K_Pos             (2UL)                     /*!< PMU STS: EXIST_32K (Bit 2)                            */
#define PMU_STS_EXIST_32K_Msk             (0x4UL)                   /*!< PMU STS: EXIST_32K (Bitfield-Mask: 0x01)              */
#define PMU_STS_EXIST_32K                 PMU_STS_EXIST_32K_Msk
#define PMU_STS_INT_6M_Pos                (1UL)                     /*!< PMU STS: INT_6M (Bit 1)                               */
#define PMU_STS_INT_6M_Msk                (0x2UL)                   /*!< PMU STS: INT_6M (Bitfield-Mask: 0x01)                 */
#define PMU_STS_INT_6M                    PMU_STS_INT_6M_Msk
#define PMU_STS_INT_32K_Pos               (0UL)                     /*!< PMU STS: INT_32K (Bit 0)                              */
#define PMU_STS_INT_32K_Msk               (0x1UL)                   /*!< PMU STS: INT_32K (Bitfield-Mask: 0x01)                */
#define PMU_STS_INT_32K                   PMU_STS_INT_32K_Msk
/* ========================================================  WDTPASS  ======================================================== */
#define PMU_WDTPASS_UNLOCK_Pos            (0UL)                     /*!< PMU WDTPASS: UNLOCK (Bit 0)                           */
#define PMU_WDTPASS_UNLOCK_Msk            (0x1UL)                   /*!< PMU WDTPASS: UNLOCK (Bitfield-Mask: 0x01)             */
#define PMU_WDTPASS_UNLOCK                PMU_WDTPASS_UNLOCK_Msk
/* =========================================================  WDTEN  ========================================================= */
#define PMU_WDTEN_WDTSEL_Pos              (2UL)                     /*!< PMU WDTEN: WDTSEL (Bit 2)                             */
#define PMU_WDTEN_WDTSEL_Msk              (0xcUL)                   /*!< PMU WDTEN: WDTSEL (Bitfield-Mask: 0x03)               */
#define PMU_WDTEN_WDTSEL                  PMU_WDTEN_WDTSEL_Msk
#define PMU_WDTEN_WDTEN_Pos               (0UL)                     /*!< PMU WDTEN: WDTEN (Bit 0)                              */
#define PMU_WDTEN_WDTEN_Msk               (0x1UL)                   /*!< PMU WDTEN: WDTEN (Bitfield-Mask: 0x01)                */
#define PMU_WDTEN_WDTEN                   PMU_WDTEN_WDTEN_Msk
/* ========================================================  WDTCLR  ========================================================= */
#define PMU_WDTCLR_WDTCNT_Pos             (0UL)                     /*!< PMU WDTCLR: WDTCNT (Bit 0)                            */
#define PMU_WDTCLR_WDTCNT_Msk             (0xffffUL)                /*!< PMU WDTCLR: WDTCNT (Bitfield-Mask: 0xffff)            */
#define PMU_WDTCLR_WDTCNT                 PMU_WDTCLR_WDTCNT_Msk
/* ==========================================================  RAM  ========================================================== */
#define PMU_RAM_RAM_Pos                   (0UL)                     /*!< PMU RAM: RAM (Bit 0)                                  */
#define PMU_RAM_RAM_Msk                   (0xffffffffUL)            /*!< PMU RAM: RAM (Bitfield-Mask: 0xffffffff)              */
#define PMU_RAM_RAM                       PMU_RAM_RAM_Msk


/* =========================================================================================================================== */
/* ================                                            PWM                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  CTL  ========================================================== */
#define PWM_CTL_ID_Pos                    (6UL)                     /*!< PWM CTL: ID (Bit 6)                                   */
#define PWM_CTL_ID_Msk                    (0xc0UL)                  /*!< PWM CTL: ID (Bitfield-Mask: 0x03)                     */
#define PWM_CTL_ID                        PWM_CTL_ID_Msk
#define PWM_CTL_MC_Pos                    (4UL)                     /*!< PWM CTL: MC (Bit 4)                                   */
#define PWM_CTL_MC_Msk                    (0x30UL)                  /*!< PWM CTL: MC (Bitfield-Mask: 0x03)                     */
#define PWM_CTL_MC                        PWM_CTL_MC_Msk
#define PWM_CTL_TSEL_Pos                  (3UL)                     /*!< PWM CTL: TSEL (Bit 3)                                 */
#define PWM_CTL_TSEL_Msk                  (0x8UL)                   /*!< PWM CTL: TSEL (Bitfield-Mask: 0x01)                   */
#define PWM_CTL_TSEL                      PWM_CTL_TSEL_Msk
#define PWM_CTL_CLR_Pos                   (2UL)                     /*!< PWM CTL: CLR (Bit 2)                                  */
#define PWM_CTL_CLR_Msk                   (0x4UL)                   /*!< PWM CTL: CLR (Bitfield-Mask: 0x01)                    */
#define PWM_CTL_CLR                       PWM_CTL_CLR_Msk
#define PWM_CTL_IE_Pos                    (1UL)                     /*!< PWM CTL: IE (Bit 1)                                   */
#define PWM_CTL_IE_Msk                    (0x2UL)                   /*!< PWM CTL: IE (Bitfield-Mask: 0x01)                     */
#define PWM_CTL_IE                        PWM_CTL_IE_Msk
#define PWM_CTL_IFG_Pos                   (0UL)                     /*!< PWM CTL: IFG (Bit 0)                                  */
#define PWM_CTL_IFG_Msk                   (0x1UL)                   /*!< PWM CTL: IFG (Bitfield-Mask: 0x01)                    */
#define PWM_CTL_IFG                       PWM_CTL_IFG_Msk
/* ==========================================================  TAR  ========================================================== */
#define PWM_TAR_TAR_Pos                   (0UL)                     /*!< PWM TAR: TAR (Bit 0)                                  */
#define PWM_TAR_TAR_Msk                   (0xffffUL)                /*!< PWM TAR: TAR (Bitfield-Mask: 0xffff)                  */
#define PWM_TAR_TAR                       PWM_TAR_TAR_Msk
/* =========================================================  CCTL  ========================================================== */
#define PWM_CCTL_CM_Pos                   (14UL)                    /*!< PWM CCTL: CM (Bit 14)                                 */
#define PWM_CCTL_CM_Msk                   (0xc000UL)                /*!< PWM CCTL: CM (Bitfield-Mask: 0x03)                    */
#define PWM_CCTL_CM                       PWM_CCTL_CM_Msk
#define PWM_CCTL_SCCI_Pos                 (10UL)                    /*!< PWM CCTL: SCCI (Bit 10)                               */
#define PWM_CCTL_SCCI_Msk                 (0x400UL)                 /*!< PWM CCTL: SCCI (Bitfield-Mask: 0x01)                  */
#define PWM_CCTL_SCCI                     PWM_CCTL_SCCI_Msk
#define PWM_CCTL_OUTEN_Pos                (9UL)                     /*!< PWM CCTL: OUTEN (Bit 9)                               */
#define PWM_CCTL_OUTEN_Msk                (0x200UL)                 /*!< PWM CCTL: OUTEN (Bitfield-Mask: 0x01)                 */
#define PWM_CCTL_OUTEN                    PWM_CCTL_OUTEN_Msk
#define PWM_CCTL_CAP_Pos                  (8UL)                     /*!< PWM CCTL: CAP (Bit 8)                                 */
#define PWM_CCTL_CAP_Msk                  (0x100UL)                 /*!< PWM CCTL: CAP (Bitfield-Mask: 0x01)                   */
#define PWM_CCTL_CAP                      PWM_CCTL_CAP_Msk
#define PWM_CCTL_OUTMOD_Pos               (5UL)                     /*!< PWM CCTL: OUTMOD (Bit 5)                              */
#define PWM_CCTL_OUTMOD_Msk               (0xe0UL)                  /*!< PWM CCTL: OUTMOD (Bitfield-Mask: 0x07)                */
#define PWM_CCTL_OUTMOD                   PWM_CCTL_OUTMOD_Msk
#define PWM_CCTL_CCIE_Pos                 (4UL)                     /*!< PWM CCTL: CCIE (Bit 4)                                */
#define PWM_CCTL_CCIE_Msk                 (0x10UL)                  /*!< PWM CCTL: CCIE (Bitfield-Mask: 0x01)                  */
#define PWM_CCTL_CCIE                     PWM_CCTL_CCIE_Msk
#define PWM_CCTL_OUT_Pos                  (2UL)                     /*!< PWM CCTL: OUT (Bit 2)                                 */
#define PWM_CCTL_OUT_Msk                  (0x4UL)                   /*!< PWM CCTL: OUT (Bitfield-Mask: 0x01)                   */
#define PWM_CCTL_OUT                      PWM_CCTL_OUT_Msk
#define PWM_CCTL_COV_Pos                  (1UL)                     /*!< PWM CCTL: COV (Bit 1)                                 */
#define PWM_CCTL_COV_Msk                  (0x2UL)                   /*!< PWM CCTL: COV (Bitfield-Mask: 0x01)                   */
#define PWM_CCTL_COV                      PWM_CCTL_COV_Msk
#define PWM_CCTL_CCIFG_Pos                (0UL)                     /*!< PWM CCTL: CCIFG (Bit 0)                               */
#define PWM_CCTL_CCIFG_Msk                (0x1UL)                   /*!< PWM CCTL: CCIFG (Bitfield-Mask: 0x01)                 */
#define PWM_CCTL_CCIFG                    PWM_CCTL_CCIFG_Msk
/* ==========================================================  CCR  ========================================================== */
#define PWM_CCR_CCRx_Pos                  (0UL)                     /*!< PWM CCR: CCRx (Bit 0)                                 */
#define PWM_CCR_CCRx_Msk                  (0xffffUL)                /*!< PWM CCR: CCRx (Bitfield-Mask: 0xffff)                 */
#define PWM_CCR_CCRx                      PWM_CCR_CCRx_Msk


/* =========================================================================================================================== */
/* ================                                          PWM_SEL                                          ================ */
/* =========================================================================================================================== */

/* =========================================================  O_SEL  ========================================================= */
#define PWM_SEL_O_SEL_SEL3_Pos            (12UL)                    /*!< PWM_SEL O_SEL: SEL3 (Bit 12)                          */
#define PWM_SEL_O_SEL_SEL3_Msk            (0xf000UL)                /*!< PWM_SEL O_SEL: SEL3 (Bitfield-Mask: 0x0f)             */
#define PWM_SEL_O_SEL_SEL3                PWM_SEL_O_SEL_SEL3_Msk
#define PWM_SEL_O_SEL_SEL2_Pos            (8UL)                     /*!< PWM_SEL O_SEL: SEL2 (Bit 8)                           */
#define PWM_SEL_O_SEL_SEL2_Msk            (0xf00UL)                 /*!< PWM_SEL O_SEL: SEL2 (Bitfield-Mask: 0x0f)             */
#define PWM_SEL_O_SEL_SEL2                PWM_SEL_O_SEL_SEL2_Msk
#define PWM_SEL_O_SEL_SEL1_Pos            (4UL)                     /*!< PWM_SEL O_SEL: SEL1 (Bit 4)                           */
#define PWM_SEL_O_SEL_SEL1_Msk            (0xf0UL)                  /*!< PWM_SEL O_SEL: SEL1 (Bitfield-Mask: 0x0f)             */
#define PWM_SEL_O_SEL_SEL1                PWM_SEL_O_SEL_SEL1_Msk
#define PWM_SEL_O_SEL_SEL0_Pos            (0UL)                     /*!< PWM_SEL O_SEL: SEL0 (Bit 0)                           */
#define PWM_SEL_O_SEL_SEL0_Msk            (0xfUL)                   /*!< PWM_SEL O_SEL: SEL0 (Bitfield-Mask: 0x0f)             */
#define PWM_SEL_O_SEL_SEL0                PWM_SEL_O_SEL_SEL0_Msk
/* ========================================================  I_SEL01  ======================================================== */
#define PWM_SEL_I_SEL01_SEL12_Pos         (20UL)                    /*!< PWM_SEL I_SEL01: SEL12 (Bit 20)                       */
#define PWM_SEL_I_SEL01_SEL12_Msk         (0x300000UL)              /*!< PWM_SEL I_SEL01: SEL12 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL01_SEL12             PWM_SEL_I_SEL01_SEL12_Msk
#define PWM_SEL_I_SEL01_SEL11_Pos         (18UL)                    /*!< PWM_SEL I_SEL01: SEL11 (Bit 18)                       */
#define PWM_SEL_I_SEL01_SEL11_Msk         (0xc0000UL)               /*!< PWM_SEL I_SEL01: SEL11 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL01_SEL11             PWM_SEL_I_SEL01_SEL11_Msk
#define PWM_SEL_I_SEL01_SEL10_Pos         (16UL)                    /*!< PWM_SEL I_SEL01: SEL10 (Bit 16)                       */
#define PWM_SEL_I_SEL01_SEL10_Msk         (0x30000UL)               /*!< PWM_SEL I_SEL01: SEL10 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL01_SEL10             PWM_SEL_I_SEL01_SEL10_Msk
#define PWM_SEL_I_SEL01_SEL02_Pos         (4UL)                     /*!< PWM_SEL I_SEL01: SEL02 (Bit 4)                        */
#define PWM_SEL_I_SEL01_SEL02_Msk         (0x30UL)                  /*!< PWM_SEL I_SEL01: SEL02 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL01_SEL02             PWM_SEL_I_SEL01_SEL02_Msk
#define PWM_SEL_I_SEL01_SEL01_Pos         (2UL)                     /*!< PWM_SEL I_SEL01: SEL01 (Bit 2)                        */
#define PWM_SEL_I_SEL01_SEL01_Msk         (0xcUL)                   /*!< PWM_SEL I_SEL01: SEL01 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL01_SEL01             PWM_SEL_I_SEL01_SEL01_Msk
#define PWM_SEL_I_SEL01_SEL00_Pos         (0UL)                     /*!< PWM_SEL I_SEL01: SEL00 (Bit 0)                        */
#define PWM_SEL_I_SEL01_SEL00_Msk         (0x3UL)                   /*!< PWM_SEL I_SEL01: SEL00 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL01_SEL00             PWM_SEL_I_SEL01_SEL00_Msk
/* ========================================================  I_SEL23  ======================================================== */
#define PWM_SEL_I_SEL23_SEL32_Pos         (20UL)                    /*!< PWM_SEL I_SEL23: SEL32 (Bit 20)                       */
#define PWM_SEL_I_SEL23_SEL32_Msk         (0x300000UL)              /*!< PWM_SEL I_SEL23: SEL32 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL23_SEL32             PWM_SEL_I_SEL23_SEL32_Msk
#define PWM_SEL_I_SEL23_SEL31_Pos         (18UL)                    /*!< PWM_SEL I_SEL23: SEL31 (Bit 18)                       */
#define PWM_SEL_I_SEL23_SEL31_Msk         (0xc0000UL)               /*!< PWM_SEL I_SEL23: SEL31 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL23_SEL31             PWM_SEL_I_SEL23_SEL31_Msk
#define PWM_SEL_I_SEL23_SEL30_Pos         (16UL)                    /*!< PWM_SEL I_SEL23: SEL30 (Bit 16)                       */
#define PWM_SEL_I_SEL23_SEL30_Msk         (0x30000UL)               /*!< PWM_SEL I_SEL23: SEL30 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL23_SEL30             PWM_SEL_I_SEL23_SEL30_Msk
#define PWM_SEL_I_SEL23_SEL22_Pos         (4UL)                     /*!< PWM_SEL I_SEL23: SEL22 (Bit 4)                        */
#define PWM_SEL_I_SEL23_SEL22_Msk         (0x30UL)                  /*!< PWM_SEL I_SEL23: SEL22 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL23_SEL22             PWM_SEL_I_SEL23_SEL22_Msk
#define PWM_SEL_I_SEL23_SEL21_Pos         (2UL)                     /*!< PWM_SEL I_SEL23: SEL21 (Bit 2)                        */
#define PWM_SEL_I_SEL23_SEL21_Msk         (0xcUL)                   /*!< PWM_SEL I_SEL23: SEL21 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL23_SEL21             PWM_SEL_I_SEL23_SEL21_Msk
#define PWM_SEL_I_SEL23_SEL20_Pos         (0UL)                     /*!< PWM_SEL I_SEL23: SEL20 (Bit 0)                        */
#define PWM_SEL_I_SEL23_SEL20_Msk         (0x3UL)                   /*!< PWM_SEL I_SEL23: SEL20 (Bitfield-Mask: 0x03)          */
#define PWM_SEL_I_SEL23_SEL20             PWM_SEL_I_SEL23_SEL20_Msk


/* =========================================================================================================================== */
/* ================                                            RTC                                            ================ */
/* =========================================================================================================================== */

/* ==========================================================  SEC  ========================================================== */
#define RTC_SEC_SEC_Pos                   (0UL)                     /*!< RTC SEC: SEC (Bit 0)                                  */
#define RTC_SEC_SEC_Msk                   (0x7fUL)                  /*!< RTC SEC: SEC (Bitfield-Mask: 0x7f)                    */
#define RTC_SEC_SEC                       RTC_SEC_SEC_Msk
/* ==========================================================  MIN  ========================================================== */
#define RTC_MIN_MIN_Pos                   (0UL)                     /*!< RTC MIN: MIN (Bit 0)                                  */
#define RTC_MIN_MIN_Msk                   (0x7fUL)                  /*!< RTC MIN: MIN (Bitfield-Mask: 0x7f)                    */
#define RTC_MIN_MIN                       RTC_MIN_MIN_Msk
/* =========================================================  HOUR  ========================================================== */
#define RTC_HOUR_HOUR_Pos                 (0UL)                     /*!< RTC HOUR: HOUR (Bit 0)                                */
#define RTC_HOUR_HOUR_Msk                 (0x3fUL)                  /*!< RTC HOUR: HOUR (Bitfield-Mask: 0x3f)                  */
#define RTC_HOUR_HOUR                     RTC_HOUR_HOUR_Msk
/* ==========================================================  DAY  ========================================================== */
#define RTC_DAY_DAY_Pos                   (0UL)                     /*!< RTC DAY: DAY (Bit 0)                                  */
#define RTC_DAY_DAY_Msk                   (0x3fUL)                  /*!< RTC DAY: DAY (Bitfield-Mask: 0x3f)                    */
#define RTC_DAY_DAY                       RTC_DAY_DAY_Msk
/* =========================================================  WEEK  ========================================================== */
#define RTC_WEEK_WEEK_Pos                 (0UL)                     /*!< RTC WEEK: WEEK (Bit 0)                                */
#define RTC_WEEK_WEEK_Msk                 (0x7UL)                   /*!< RTC WEEK: WEEK (Bitfield-Mask: 0x07)                  */
#define RTC_WEEK_WEEK                     RTC_WEEK_WEEK_Msk
/* ==========================================================  MON  ========================================================== */
#define RTC_MON_MON_Pos                   (0UL)                     /*!< RTC MON: MON (Bit 0)                                  */
#define RTC_MON_MON_Msk                   (0x1fUL)                  /*!< RTC MON: MON (Bitfield-Mask: 0x1f)                    */
#define RTC_MON_MON                       RTC_MON_MON_Msk
/* =========================================================  YEAR  ========================================================== */
#define RTC_YEAR_YEAR_Pos                 (0UL)                     /*!< RTC YEAR: YEAR (Bit 0)                                */
#define RTC_YEAR_YEAR_Msk                 (0xffUL)                  /*!< RTC YEAR: YEAR (Bitfield-Mask: 0xff)                  */
#define RTC_YEAR_YEAR                     RTC_YEAR_YEAR_Msk
/* =========================================================  TIME  ========================================================== */
#define RTC_TIME_TIME_Pos                 (0UL)                     /*!< RTC TIME: TIME (Bit 0)                                */
#define RTC_TIME_TIME_Msk                 (0x3fffffUL)              /*!< RTC TIME: TIME (Bitfield-Mask: 0x3fffff)              */
#define RTC_TIME_TIME                     RTC_TIME_TIME_Msk
/* ========================================================  WKUSEC  ========================================================= */
#define RTC_WKUSEC_WKUSEC_Pos             (0UL)                     /*!< RTC WKUSEC: WKUSEC (Bit 0)                            */
#define RTC_WKUSEC_WKUSEC_Msk             (0x3fUL)                  /*!< RTC WKUSEC: WKUSEC (Bitfield-Mask: 0x3f)              */
#define RTC_WKUSEC_WKUSEC                 RTC_WKUSEC_WKUSEC_Msk
/* ========================================================  WKUMIN  ========================================================= */
#define RTC_WKUMIN_WKUMIN_Pos             (0UL)                     /*!< RTC WKUMIN: WKUMIN (Bit 0)                            */
#define RTC_WKUMIN_WKUMIN_Msk             (0x3fUL)                  /*!< RTC WKUMIN: WKUMIN (Bitfield-Mask: 0x3f)              */
#define RTC_WKUMIN_WKUMIN                 RTC_WKUMIN_WKUMIN_Msk
/* ========================================================  WKUHOUR  ======================================================== */
#define RTC_WKUHOUR_WKUHOUR_Pos           (0UL)                     /*!< RTC WKUHOUR: WKUHOUR (Bit 0)                          */
#define RTC_WKUHOUR_WKUHOUR_Msk           (0x1fUL)                  /*!< RTC WKUHOUR: WKUHOUR (Bitfield-Mask: 0x1f)            */
#define RTC_WKUHOUR_WKUHOUR               RTC_WKUHOUR_WKUHOUR_Msk
/* ========================================================  WKUCNT  ========================================================= */
#define RTC_WKUCNT_CNTSEL_Pos             (24UL)                    /*!< RTC WKUCNT: CNTSEL (Bit 24)                           */
#define RTC_WKUCNT_CNTSEL_Msk             (0x3000000UL)             /*!< RTC WKUCNT: CNTSEL (Bitfield-Mask: 0x03)              */
#define RTC_WKUCNT_CNTSEL                 RTC_WKUCNT_CNTSEL_Msk
#define RTC_WKUCNT_WKUCNT_Pos             (0UL)                     /*!< RTC WKUCNT: WKUCNT (Bit 0)                            */
#define RTC_WKUCNT_WKUCNT_Msk             (0xffffffUL)              /*!< RTC WKUCNT: WKUCNT (Bitfield-Mask: 0xffffff)          */
#define RTC_WKUCNT_WKUCNT                 RTC_WKUCNT_WKUCNT_Msk
/* ==========================================================  CAL  ========================================================== */
#define RTC_CAL_CAL_Pos                   (0UL)                     /*!< RTC CAL: CAL (Bit 0)                                  */
#define RTC_CAL_CAL_Msk                   (0x3fffUL)                /*!< RTC CAL: CAL (Bitfield-Mask: 0x3fff)                  */
#define RTC_CAL_CAL                       RTC_CAL_CAL_Msk
/* ==========================================================  DIV  ========================================================== */
#define RTC_DIV_RTCDIV_Pos                (0UL)                     /*!< RTC DIV: RTCDIV (Bit 0)                               */
#define RTC_DIV_RTCDIV_Msk                (0x3ffffffUL)             /*!< RTC DIV: RTCDIV (Bitfield-Mask: 0x3ffffff)            */
#define RTC_DIV_RTCDIV                    RTC_DIV_RTCDIV_Msk
/* ==========================================================  CTL  ========================================================== */
#define RTC_CTL_RTCPLLCLKSEL_Pos          (4UL)                     /*!< RTC CTL: RTCPLLCLKSEL (Bit 4)                         */
#define RTC_CTL_RTCPLLCLKSEL_Msk          (0x10UL)                  /*!< RTC CTL: RTCPLLCLKSEL (Bitfield-Mask: 0x01)           */
#define RTC_CTL_RTCPLLCLKSEL              RTC_CTL_RTCPLLCLKSEL_Msk
#define RTC_CTL_RTCPLLOE_Pos              (2UL)                     /*!< RTC CTL: RTCPLLOE (Bit 2)                             */
#define RTC_CTL_RTCPLLOE_Msk              (0x4UL)                   /*!< RTC CTL: RTCPLLOE (Bitfield-Mask: 0x01)               */
#define RTC_CTL_RTCPLLOE                  RTC_CTL_RTCPLLOE_Msk
/* ==========================================================  ITV  ========================================================== */
#define RTC_ITV_ITV_Pos                   (0UL)                     /*!< RTC ITV: ITV (Bit 0)                                  */
#define RTC_ITV_ITV_Msk                   (0x7UL)                   /*!< RTC ITV: ITV (Bitfield-Mask: 0x07)                    */
#define RTC_ITV_ITV                       RTC_ITV_ITV_Msk
/* =========================================================  SITV  ========================================================== */
#define RTC_SITV_SITVEN_Pos               (6UL)                     /*!< RTC SITV: SITVEN (Bit 6)                              */
#define RTC_SITV_SITVEN_Msk               (0x40UL)                  /*!< RTC SITV: SITVEN (Bitfield-Mask: 0x01)                */
#define RTC_SITV_SITVEN                   RTC_SITV_SITVEN_Msk
#define RTC_SITV_SITV_Pos                 (0UL)                     /*!< RTC SITV: SITV (Bit 0)                                */
#define RTC_SITV_SITV_Msk                 (0x3fUL)                  /*!< RTC SITV: SITV (Bitfield-Mask: 0x3f)                  */
#define RTC_SITV_SITV                     RTC_SITV_SITV_Msk
/* ==========================================================  PWD  ========================================================== */
#define RTC_PWD_PWDEN_Pos                 (0UL)                     /*!< RTC PWD: PWDEN (Bit 0)                                */
#define RTC_PWD_PWDEN_Msk                 (0x1UL)                   /*!< RTC PWD: PWDEN (Bitfield-Mask: 0x01)                  */
#define RTC_PWD_PWDEN                     RTC_PWD_PWDEN_Msk
/* ==========================================================  CE  =========================================================== */
#define RTC_CE_BSY_Pos                    (1UL)                     /*!< RTC CE: BSY (Bit 1)                                   */
#define RTC_CE_BSY_Msk                    (0x2UL)                   /*!< RTC CE: BSY (Bitfield-Mask: 0x01)                     */
#define RTC_CE_BSY                        RTC_CE_BSY_Msk
#define RTC_CE_CE_Pos                     (0UL)                     /*!< RTC CE: CE (Bit 0)                                    */
#define RTC_CE_CE_Msk                     (0x1UL)                   /*!< RTC CE: CE (Bitfield-Mask: 0x01)                      */
#define RTC_CE_CE                         RTC_CE_CE_Msk
/* =========================================================  LOAD  ========================================================== */
#define RTC_LOAD_LOAD_Pos                 (0UL)                     /*!< RTC LOAD: LOAD (Bit 0)                                */
#define RTC_LOAD_LOAD_Msk                 (0xffffffffUL)            /*!< RTC LOAD: LOAD (Bitfield-Mask: 0xffffffff)            */
#define RTC_LOAD_LOAD                     RTC_LOAD_LOAD_Msk
/* ========================================================  INTSTS  ========================================================= */
#define RTC_INTSTS_INTSTS10_Pos           (10UL)                    /*!< RTC INTSTS: INTSTS10 (Bit 10)                         */
#define RTC_INTSTS_INTSTS10_Msk           (0x400UL)                 /*!< RTC INTSTS: INTSTS10 (Bitfield-Mask: 0x01)            */
#define RTC_INTSTS_INTSTS10               RTC_INTSTS_INTSTS10_Msk
#define RTC_INTSTS_INTSTS8_Pos            (8UL)                     /*!< RTC INTSTS: INTSTS8 (Bit 8)                           */
#define RTC_INTSTS_INTSTS8_Msk            (0x100UL)                 /*!< RTC INTSTS: INTSTS8 (Bitfield-Mask: 0x01)             */
#define RTC_INTSTS_INTSTS8                RTC_INTSTS_INTSTS8_Msk
#define RTC_INTSTS_INTSTS6_Pos            (6UL)                     /*!< RTC INTSTS: INTSTS6 (Bit 6)                           */
#define RTC_INTSTS_INTSTS6_Msk            (0x40UL)                  /*!< RTC INTSTS: INTSTS6 (Bitfield-Mask: 0x01)             */
#define RTC_INTSTS_INTSTS6                RTC_INTSTS_INTSTS6_Msk
#define RTC_INTSTS_INTSTS5_Pos            (5UL)                     /*!< RTC INTSTS: INTSTS5 (Bit 5)                           */
#define RTC_INTSTS_INTSTS5_Msk            (0x20UL)                  /*!< RTC INTSTS: INTSTS5 (Bitfield-Mask: 0x01)             */
#define RTC_INTSTS_INTSTS5                RTC_INTSTS_INTSTS5_Msk
#define RTC_INTSTS_INTSTS4_Pos            (4UL)                     /*!< RTC INTSTS: INTSTS4 (Bit 4)                           */
#define RTC_INTSTS_INTSTS4_Msk            (0x10UL)                  /*!< RTC INTSTS: INTSTS4 (Bitfield-Mask: 0x01)             */
#define RTC_INTSTS_INTSTS4                RTC_INTSTS_INTSTS4_Msk
#define RTC_INTSTS_INTSTS3_Pos            (3UL)                     /*!< RTC INTSTS: INTSTS3 (Bit 3)                           */
#define RTC_INTSTS_INTSTS3_Msk            (0x8UL)                   /*!< RTC INTSTS: INTSTS3 (Bitfield-Mask: 0x01)             */
#define RTC_INTSTS_INTSTS3                RTC_INTSTS_INTSTS3_Msk
#define RTC_INTSTS_INTSTS2_Pos            (2UL)                     /*!< RTC INTSTS: INTSTS2 (Bit 2)                           */
#define RTC_INTSTS_INTSTS2_Msk            (0x4UL)                   /*!< RTC INTSTS: INTSTS2 (Bitfield-Mask: 0x01)             */
#define RTC_INTSTS_INTSTS2                RTC_INTSTS_INTSTS2_Msk
#define RTC_INTSTS_INTSTS1_Pos            (1UL)                     /*!< RTC INTSTS: INTSTS1 (Bit 1)                           */
#define RTC_INTSTS_INTSTS1_Msk            (0x2UL)                   /*!< RTC INTSTS: INTSTS1 (Bitfield-Mask: 0x01)             */
#define RTC_INTSTS_INTSTS1                RTC_INTSTS_INTSTS1_Msk
#define RTC_INTSTS_INTSTS0_Pos            (0UL)                     /*!< RTC INTSTS: INTSTS0 (Bit 0)                           */
#define RTC_INTSTS_INTSTS0_Msk            (0x1UL)                   /*!< RTC INTSTS: INTSTS0 (Bitfield-Mask: 0x01)             */
#define RTC_INTSTS_INTSTS0                RTC_INTSTS_INTSTS0_Msk
/* =========================================================  INTEN  ========================================================= */
#define RTC_INTEN_INTEN10_Pos             (10UL)                    /*!< RTC INTEN: INTEN10 (Bit 10)                           */
#define RTC_INTEN_INTEN10_Msk             (0x400UL)                 /*!< RTC INTEN: INTEN10 (Bitfield-Mask: 0x01)              */
#define RTC_INTEN_INTEN10                 RTC_INTEN_INTEN10_Msk
#define RTC_INTEN_INTEN8_Pos              (8UL)                     /*!< RTC INTEN: INTEN8 (Bit 8)                             */
#define RTC_INTEN_INTEN8_Msk              (0x100UL)                 /*!< RTC INTEN: INTEN8 (Bitfield-Mask: 0x01)               */
#define RTC_INTEN_INTEN8                  RTC_INTEN_INTEN8_Msk
#define RTC_INTEN_INTEN6_Pos              (6UL)                     /*!< RTC INTEN: INTEN6 (Bit 6)                             */
#define RTC_INTEN_INTEN6_Msk              (0x40UL)                  /*!< RTC INTEN: INTEN6 (Bitfield-Mask: 0x01)               */
#define RTC_INTEN_INTEN6                  RTC_INTEN_INTEN6_Msk
#define RTC_INTEN_INTEN5_Pos              (5UL)                     /*!< RTC INTEN: INTEN5 (Bit 5)                             */
#define RTC_INTEN_INTEN5_Msk              (0x20UL)                  /*!< RTC INTEN: INTEN5 (Bitfield-Mask: 0x01)               */
#define RTC_INTEN_INTEN5                  RTC_INTEN_INTEN5_Msk
#define RTC_INTEN_INTEN4_Pos              (4UL)                     /*!< RTC INTEN: INTEN4 (Bit 4)                             */
#define RTC_INTEN_INTEN4_Msk              (0x10UL)                  /*!< RTC INTEN: INTEN4 (Bitfield-Mask: 0x01)               */
#define RTC_INTEN_INTEN4                  RTC_INTEN_INTEN4_Msk
#define RTC_INTEN_INTRN3_Pos              (3UL)                     /*!< RTC INTEN: INTRN3 (Bit 3)                             */
#define RTC_INTEN_INTRN3_Msk              (0x8UL)                   /*!< RTC INTEN: INTRN3 (Bitfield-Mask: 0x01)               */
#define RTC_INTEN_INTRN3                  RTC_INTEN_INTRN3_Msk
#define RTC_INTEN_INTEN2_Pos              (2UL)                     /*!< RTC INTEN: INTEN2 (Bit 2)                             */
#define RTC_INTEN_INTEN2_Msk              (0x4UL)                   /*!< RTC INTEN: INTEN2 (Bitfield-Mask: 0x01)               */
#define RTC_INTEN_INTEN2                  RTC_INTEN_INTEN2_Msk
#define RTC_INTEN_INTEN1_Pos              (1UL)                     /*!< RTC INTEN: INTEN1 (Bit 1)                             */
#define RTC_INTEN_INTEN1_Msk              (0x2UL)                   /*!< RTC INTEN: INTEN1 (Bitfield-Mask: 0x01)               */
#define RTC_INTEN_INTEN1                  RTC_INTEN_INTEN1_Msk
#define RTC_INTEN_INTEN0_Pos              (0UL)                     /*!< RTC INTEN: INTEN0 (Bit 0)                             */
#define RTC_INTEN_INTEN0_Msk              (0x1UL)                   /*!< RTC INTEN: INTEN0 (Bitfield-Mask: 0x01)               */
#define RTC_INTEN_INTEN0                  RTC_INTEN_INTEN0_Msk
/* =========================================================  PSCA  ========================================================== */
#define RTC_PSCA_PSCA_Pos                 (0UL)                     /*!< RTC PSCA: PSCA (Bit 0)                                */
#define RTC_PSCA_PSCA_Msk                 (0x3UL)                   /*!< RTC PSCA: PSCA (Bitfield-Mask: 0x03)                  */
#define RTC_PSCA_PSCA                     RTC_PSCA_PSCA_Msk
/* =========================================================  ACTI  ========================================================== */
#define RTC_ACTI_ACTI_Pos                 (0UL)                     /*!< RTC ACTI: ACTI (Bit 0)                                */
#define RTC_ACTI_ACTI_Msk                 (0x3fffUL)                /*!< RTC ACTI: ACTI (Bitfield-Mask: 0x3fff)                */
#define RTC_ACTI_ACTI                     RTC_ACTI_ACTI_Msk
/* ========================================================  ACF200  ========================================================= */
#define RTC_ACF200_F200_Pos               (0UL)                     /*!< RTC ACF200: F200 (Bit 0)                              */
#define RTC_ACF200_F200_Msk               (0x3ffffffUL)             /*!< RTC ACF200: F200 (Bitfield-Mask: 0x3ffffff)           */
#define RTC_ACF200_F200                   RTC_ACF200_F200_Msk
/* =========================================================  ACP0  ========================================================== */
#define RTC_ACP0_P0_Pos                   (0UL)                     /*!< RTC ACP0: P0 (Bit 0)                                  */
#define RTC_ACP0_P0_Msk                   (0xffffUL)                /*!< RTC ACP0: P0 (Bitfield-Mask: 0xffff)                  */
#define RTC_ACP0_P0                       RTC_ACP0_P0_Msk
/* =========================================================  ACP1  ========================================================== */
#define RTC_ACP1_P1_Pos                   (0UL)                     /*!< RTC ACP1: P1 (Bit 0)                                  */
#define RTC_ACP1_P1_Msk                   (0xffffUL)                /*!< RTC ACP1: P1 (Bitfield-Mask: 0xffff)                  */
#define RTC_ACP1_P1                       RTC_ACP1_P1_Msk
/* =========================================================  ACP2  ========================================================== */
#define RTC_ACP2_P2_Pos                   (0UL)                     /*!< RTC ACP2: P2 (Bit 0)                                  */
#define RTC_ACP2_P2_Msk                   (0xffffffffUL)            /*!< RTC ACP2: P2 (Bitfield-Mask: 0xffffffff)              */
#define RTC_ACP2_P2                       RTC_ACP2_P2_Msk
/* =========================================================  ACP3  ========================================================== */
#define RTC_ACP3_P3_Pos                   (0UL)                     /*!< RTC ACP3: P3 (Bit 0)                                  */
#define RTC_ACP3_P3_Msk                   (0xffffffffUL)            /*!< RTC ACP3: P3 (Bitfield-Mask: 0xffffffff)              */
#define RTC_ACP3_P3                       RTC_ACP3_P3_Msk
/* =========================================================  ACP4  ========================================================== */
#define RTC_ACP4_P4_Pos                   (0UL)                     /*!< RTC ACP4: P4 (Bit 0)                                  */
#define RTC_ACP4_P4_Msk                   (0xffffUL)                /*!< RTC ACP4: P4 (Bitfield-Mask: 0xffff)                  */
#define RTC_ACP4_P4                       RTC_ACP4_P4_Msk
/* =========================================================  ACP5  ========================================================== */
#define RTC_ACP5_P5_Pos                   (0UL)                     /*!< RTC ACP5: P5 (Bit 0)                                  */
#define RTC_ACP5_P5_Msk                   (0xffffUL)                /*!< RTC ACP5: P5 (Bitfield-Mask: 0xffff)                  */
#define RTC_ACP5_P5                       RTC_ACP5_P5_Msk
/* =========================================================  ACP6  ========================================================== */
#define RTC_ACP6_P6_Pos                   (0UL)                     /*!< RTC ACP6: P6 (Bit 0)                                  */
#define RTC_ACP6_P6_Msk                   (0xffffUL)                /*!< RTC ACP6: P6 (Bitfield-Mask: 0xffff)                  */
#define RTC_ACP6_P6                       RTC_ACP6_P6_Msk
/* =========================================================  ACP7  ========================================================== */
#define RTC_ACP7_P7_Pos                   (0UL)                     /*!< RTC ACP7: P7 (Bit 0)                                  */
#define RTC_ACP7_P7_Msk                   (0xffffUL)                /*!< RTC ACP7: P7 (Bitfield-Mask: 0xffff)                  */
#define RTC_ACP7_P7                       RTC_ACP7_P7_Msk
/* ==========================================================  ACK  ========================================================== */
#define RTC_ACK_K_Pos                     (0UL)                     /*!< RTC ACK: K (Bit 0)                                    */
#define RTC_ACK_K_Msk                     (0xffffUL)                /*!< RTC ACK: K (Bitfield-Mask: 0xffff)                    */
#define RTC_ACK_K                         RTC_ACK_K_Msk
/* ========================================================  WKUCNTR  ======================================================== */
#define RTC_WKUCNTR_WKUCNTR_Pos           (0UL)                     /*!< RTC WKUCNTR: WKUCNTR (Bit 0)                          */
#define RTC_WKUCNTR_WKUCNTR_Msk           (0xffffffUL)              /*!< RTC WKUCNTR: WKUCNTR (Bitfield-Mask: 0xffffff)        */
#define RTC_WKUCNTR_WKUCNTR               RTC_WKUCNTR_WKUCNTR_Msk
/* ========================================================  ACKTEMP  ======================================================== */
#define RTC_ACKTEMP_KTEMP4_Pos            (24UL)                    /*!< RTC ACKTEMP: KTEMP4 (Bit 24)                          */
#define RTC_ACKTEMP_KTEMP4_Msk            (0xff000000UL)            /*!< RTC ACKTEMP: KTEMP4 (Bitfield-Mask: 0xff)             */
#define RTC_ACKTEMP_KTEMP4                RTC_ACKTEMP_KTEMP4_Msk
#define RTC_ACKTEMP_KTEMP3_Pos            (16UL)                    /*!< RTC ACKTEMP: KTEMP3 (Bit 16)                          */
#define RTC_ACKTEMP_KTEMP3_Msk            (0xff0000UL)              /*!< RTC ACKTEMP: KTEMP3 (Bitfield-Mask: 0xff)             */
#define RTC_ACKTEMP_KTEMP3                RTC_ACKTEMP_KTEMP3_Msk
#define RTC_ACKTEMP_KTEMP2_Pos            (8UL)                     /*!< RTC ACKTEMP: KTEMP2 (Bit 8)                           */
#define RTC_ACKTEMP_KTEMP2_Msk            (0xff00UL)                /*!< RTC ACKTEMP: KTEMP2 (Bitfield-Mask: 0xff)             */
#define RTC_ACKTEMP_KTEMP2                RTC_ACKTEMP_KTEMP2_Msk
#define RTC_ACKTEMP_KTEMP1_Pos            (0UL)                     /*!< RTC ACKTEMP: KTEMP1 (Bit 0)                           */
#define RTC_ACKTEMP_KTEMP1_Msk            (0xffUL)                  /*!< RTC ACKTEMP: KTEMP1 (Bitfield-Mask: 0xff)             */
#define RTC_ACKTEMP_KTEMP1                RTC_ACKTEMP_KTEMP1_Msk
/* =======================================================  ALARMTIME  ======================================================= */
#define RTC_ALARMTIME_ALARMTIME_Pos       (0UL)                     /*!< RTC ALARMTIME: ALARMTIME (Bit 0)                      */
#define RTC_ALARMTIME_ALARMTIME_Msk       (0x3fffffUL)              /*!< RTC ALARMTIME: ALARMTIME (Bitfield-Mask: 0x3fffff)    */
#define RTC_ALARMTIME_ALARMTIME           RTC_ALARMTIME_ALARMTIME_Msk
/* =======================================================  ALARMSEC  ======================================================== */
#define RTC_ALARMSEC_ALARMSEC_Pos         (0UL)                     /*!< RTC ALARMSEC: ALARMSEC (Bit 0)                        */
#define RTC_ALARMSEC_ALARMSEC_Msk         (0x7fUL)                  /*!< RTC ALARMSEC: ALARMSEC (Bitfield-Mask: 0x7f)          */
#define RTC_ALARMSEC_ALARMSEC             RTC_ALARMSEC_ALARMSEC_Msk
/* =======================================================  ALARMMIN  ======================================================== */
#define RTC_ALARMMIN_ALARMMIN_Pos         (0UL)                     /*!< RTC ALARMMIN: ALARMMIN (Bit 0)                        */
#define RTC_ALARMMIN_ALARMMIN_Msk         (0x7fUL)                  /*!< RTC ALARMMIN: ALARMMIN (Bitfield-Mask: 0x7f)          */
#define RTC_ALARMMIN_ALARMMIN             RTC_ALARMMIN_ALARMMIN_Msk
/* =======================================================  ALARMHOUR  ======================================================= */
#define RTC_ALARMHOUR_ALARMHOUR_Pos       (0UL)                     /*!< RTC ALARMHOUR: ALARMHOUR (Bit 0)                      */
#define RTC_ALARMHOUR_ALARMHOUR_Msk       (0x3fUL)                  /*!< RTC ALARMHOUR: ALARMHOUR (Bitfield-Mask: 0x3f)        */
#define RTC_ALARMHOUR_ALARMHOUR           RTC_ALARMHOUR_ALARMHOUR_Msk
/* =======================================================  ALARMCTL  ======================================================== */
#define RTC_ALARMCTL_TIME_CNT_EN_Pos      (2UL)                     /*!< RTC ALARMCTL: TIME_CNT_EN (Bit 2)                     */
#define RTC_ALARMCTL_TIME_CNT_EN_Msk      (0x4UL)                   /*!< RTC ALARMCTL: TIME_CNT_EN (Bitfield-Mask: 0x01)       */
#define RTC_ALARMCTL_TIME_CNT_EN          RTC_ALARMCTL_TIME_CNT_EN_Msk
#define RTC_ALARMCTL_ALARM_INACCURATE_Pos (1UL)                     /*!< RTC ALARMCTL: ALARM_INACCURATE (Bit 1)                */
#define RTC_ALARMCTL_ALARM_INACCURATE_Msk (0x2UL)                   /*!< RTC ALARMCTL: ALARM_INACCURATE (Bitfield-Mask: 0x01)  */
#define RTC_ALARMCTL_ALARM_INACCURATE     RTC_ALARMCTL_ALARM_INACCURATE_Msk
#define RTC_ALARMCTL_ALARM_EN_Pos         (0UL)                     /*!< RTC ALARMCTL: ALARM_EN (Bit 0)                        */
#define RTC_ALARMCTL_ALARM_EN_Msk         (0x1UL)                   /*!< RTC ALARMCTL: ALARM_EN (Bitfield-Mask: 0x01)          */
#define RTC_ALARMCTL_ALARM_EN             RTC_ALARMCTL_ALARM_EN_Msk
/* =======================================================  ADCUCALK  ======================================================== */
#define RTC_ADCUCALK_UCAL_K3_Pos          (16UL)                    /*!< RTC ADCUCALK: UCAL_K3 (Bit 16)                        */
#define RTC_ADCUCALK_UCAL_K3_Msk          (0xffff0000UL)            /*!< RTC ADCUCALK: UCAL_K3 (Bitfield-Mask: 0xffff)         */
#define RTC_ADCUCALK_UCAL_K3              RTC_ADCUCALK_UCAL_K3_Msk
#define RTC_ADCUCALK_UCAL_K1_Pos          (0UL)                     /*!< RTC ADCUCALK: UCAL_K1 (Bit 0)                         */
#define RTC_ADCUCALK_UCAL_K1_Msk          (0xffffUL)                /*!< RTC ADCUCALK: UCAL_K1 (Bitfield-Mask: 0xffff)         */
#define RTC_ADCUCALK_UCAL_K1              RTC_ADCUCALK_UCAL_K1_Msk
/* =======================================================  ADCMACTL  ======================================================== */
#define RTC_ADCMACTL_ADCSREF_CAL_Pos      (24UL)                    /*!< RTC ADCMACTL: ADCSREF_CAL (Bit 24)                    */
#define RTC_ADCMACTL_ADCSREF_CAL_Msk      (0x7000000UL)             /*!< RTC ADCMACTL: ADCSREF_CAL (Bitfield-Mask: 0x07)       */
#define RTC_ADCMACTL_ADCSREF_CAL          RTC_ADCMACTL_ADCSREF_CAL_Msk
#define RTC_ADCMACTL_SKIP_SAMPLE_Pos      (20UL)                    /*!< RTC ADCMACTL: SKIP_SAMPLE (Bit 20)                    */
#define RTC_ADCMACTL_SKIP_SAMPLE_Msk      (0xf00000UL)              /*!< RTC ADCMACTL: SKIP_SAMPLE (Bitfield-Mask: 0x0f)       */
#define RTC_ADCMACTL_SKIP_SAMPLE          RTC_ADCMACTL_SKIP_SAMPLE_Msk
#define RTC_ADCMACTL_AVERAGE_SAMPLE_Pos   (16UL)                    /*!< RTC ADCMACTL: AVERAGE_SAMPLE (Bit 16)                 */
#define RTC_ADCMACTL_AVERAGE_SAMPLE_Msk   (0x70000UL)               /*!< RTC ADCMACTL: AVERAGE_SAMPLE (Bitfield-Mask: 0x07)    */
#define RTC_ADCMACTL_AVERAGE_SAMPLE       RTC_ADCMACTL_AVERAGE_SAMPLE_Msk
#define RTC_ADCMACTL_AVERAGE_CHx_Pos      (0UL)                     /*!< RTC ADCMACTL: AVERAGE_CHx (Bit 0)                     */
#define RTC_ADCMACTL_AVERAGE_CHx_Msk      (0xffffUL)                /*!< RTC ADCMACTL: AVERAGE_CHx (Bitfield-Mask: 0xffff)     */
#define RTC_ADCMACTL_AVERAGE_CHx          RTC_ADCMACTL_AVERAGE_CHx_Msk


/* =========================================================================================================================== */
/* ================                                            SPI                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  CTRL  ========================================================== */
#define SPI_CTRL_EN_Pos                   (15UL)                    /*!< SPI CTRL: EN (Bit 15)                                 */
#define SPI_CTRL_EN_Msk                   (0x8000UL)                /*!< SPI CTRL: EN (Bitfield-Mask: 0x01)                    */
#define SPI_CTRL_EN                       SPI_CTRL_EN_Msk
#define SPI_CTRL_LSBF_Pos                 (12UL)                    /*!< SPI CTRL: LSBF (Bit 12)                               */
#define SPI_CTRL_LSBF_Msk                 (0x1000UL)                /*!< SPI CTRL: LSBF (Bitfield-Mask: 0x01)                  */
#define SPI_CTRL_LSBF                     SPI_CTRL_LSBF_Msk
#define SPI_CTRL_RST_Pos                  (11UL)                    /*!< SPI CTRL: RST (Bit 11)                                */
#define SPI_CTRL_RST_Msk                  (0x800UL)                 /*!< SPI CTRL: RST (Bitfield-Mask: 0x01)                   */
#define SPI_CTRL_RST                      SPI_CTRL_RST_Msk
#define SPI_CTRL_CSGPIO_Pos               (10UL)                    /*!< SPI CTRL: CSGPIO (Bit 10)                             */
#define SPI_CTRL_CSGPIO_Msk               (0x400UL)                 /*!< SPI CTRL: CSGPIO (Bitfield-Mask: 0x01)                */
#define SPI_CTRL_CSGPIO                   SPI_CTRL_CSGPIO_Msk
#define SPI_CTRL_SWAP_Pos                 (9UL)                     /*!< SPI CTRL: SWAP (Bit 9)                                */
#define SPI_CTRL_SWAP_Msk                 (0x200UL)                 /*!< SPI CTRL: SWAP (Bitfield-Mask: 0x01)                  */
#define SPI_CTRL_SWAP                     SPI_CTRL_SWAP_Msk
#define SPI_CTRL_MOD_Pos                  (8UL)                     /*!< SPI CTRL: MOD (Bit 8)                                 */
#define SPI_CTRL_MOD_Msk                  (0x100UL)                 /*!< SPI CTRL: MOD (Bitfield-Mask: 0x01)                   */
#define SPI_CTRL_MOD                      SPI_CTRL_MOD_Msk
#define SPI_CTRL_SCKPHA_Pos               (5UL)                     /*!< SPI CTRL: SCKPHA (Bit 5)                              */
#define SPI_CTRL_SCKPHA_Msk               (0x20UL)                  /*!< SPI CTRL: SCKPHA (Bitfield-Mask: 0x01)                */
#define SPI_CTRL_SCKPHA                   SPI_CTRL_SCKPHA_Msk
#define SPI_CTRL_SCKPOL_Pos               (4UL)                     /*!< SPI CTRL: SCKPOL (Bit 4)                              */
#define SPI_CTRL_SCKPOL_Msk               (0x10UL)                  /*!< SPI CTRL: SCKPOL (Bitfield-Mask: 0x01)                */
#define SPI_CTRL_SCKPOL                   SPI_CTRL_SCKPOL_Msk
#define SPI_CTRL_SCKSEL_Pos               (0UL)                     /*!< SPI CTRL: SCKSEL (Bit 0)                              */
#define SPI_CTRL_SCKSEL_Msk               (0x7UL)                   /*!< SPI CTRL: SCKSEL (Bitfield-Mask: 0x07)                */
#define SPI_CTRL_SCKSEL                   SPI_CTRL_SCKSEL_Msk
/* =========================================================  TXSTS  ========================================================= */
#define SPI_TXSTS_TXIF_Pos                (15UL)                    /*!< SPI TXSTS: TXIF (Bit 15)                              */
#define SPI_TXSTS_TXIF_Msk                (0x8000UL)                /*!< SPI TXSTS: TXIF (Bitfield-Mask: 0x01)                 */
#define SPI_TXSTS_TXIF                    SPI_TXSTS_TXIF_Msk
#define SPI_TXSTS_TXIEN_Pos               (14UL)                    /*!< SPI TXSTS: TXIEN (Bit 14)                             */
#define SPI_TXSTS_TXIEN_Msk               (0x4000UL)                /*!< SPI TXSTS: TXIEN (Bitfield-Mask: 0x01)                */
#define SPI_TXSTS_TXIEN                   SPI_TXSTS_TXIEN_Msk
#define SPI_TXSTS_TXEMPTY_Pos             (9UL)                     /*!< SPI TXSTS: TXEMPTY (Bit 9)                            */
#define SPI_TXSTS_TXEMPTY_Msk             (0x200UL)                 /*!< SPI TXSTS: TXEMPTY (Bitfield-Mask: 0x01)              */
#define SPI_TXSTS_TXEMPTY                 SPI_TXSTS_TXEMPTY_Msk
#define SPI_TXSTS_TXFUR_Pos               (8UL)                     /*!< SPI TXSTS: TXFUR (Bit 8)                              */
#define SPI_TXSTS_TXFUR_Msk               (0x100UL)                 /*!< SPI TXSTS: TXFUR (Bitfield-Mask: 0x01)                */
#define SPI_TXSTS_TXFUR                   SPI_TXSTS_TXFUR_Msk
#define SPI_TXSTS_TXFLEV_Pos              (4UL)                     /*!< SPI TXSTS: TXFLEV (Bit 4)                             */
#define SPI_TXSTS_TXFLEV_Msk              (0x70UL)                  /*!< SPI TXSTS: TXFLEV (Bitfield-Mask: 0x07)               */
#define SPI_TXSTS_TXFLEV                  SPI_TXSTS_TXFLEV_Msk
#define SPI_TXSTS_DMATXDONE_Pos           (3UL)                     /*!< SPI TXSTS: DMATXDONE (Bit 3)                          */
#define SPI_TXSTS_DMATXDONE_Msk           (0x8UL)                   /*!< SPI TXSTS: DMATXDONE (Bitfield-Mask: 0x01)            */
#define SPI_TXSTS_DMATXDONE               SPI_TXSTS_DMATXDONE_Msk
#define SPI_TXSTS_TXFFLAG_Pos             (0UL)                     /*!< SPI TXSTS: TXFFLAG (Bit 0)                            */
#define SPI_TXSTS_TXFFLAG_Msk             (0x7UL)                   /*!< SPI TXSTS: TXFFLAG (Bitfield-Mask: 0x07)              */
#define SPI_TXSTS_TXFFLAG                 SPI_TXSTS_TXFFLAG_Msk
/* =========================================================  TXDAT  ========================================================= */
#define SPI_TXDAT_TXD_Pos                 (0UL)                     /*!< SPI TXDAT: TXD (Bit 0)                                */
#define SPI_TXDAT_TXD_Msk                 (0xffUL)                  /*!< SPI TXDAT: TXD (Bitfield-Mask: 0xff)                  */
#define SPI_TXDAT_TXD                     SPI_TXDAT_TXD_Msk
/* =========================================================  RXSTS  ========================================================= */
#define SPI_RXSTS_RXIF_Pos                (15UL)                    /*!< SPI RXSTS: RXIF (Bit 15)                              */
#define SPI_RXSTS_RXIF_Msk                (0x8000UL)                /*!< SPI RXSTS: RXIF (Bitfield-Mask: 0x01)                 */
#define SPI_RXSTS_RXIF                    SPI_RXSTS_RXIF_Msk
#define SPI_RXSTS_RXIEN_Pos               (14UL)                    /*!< SPI RXSTS: RXIEN (Bit 14)                             */
#define SPI_RXSTS_RXIEN_Msk               (0x4000UL)                /*!< SPI RXSTS: RXIEN (Bitfield-Mask: 0x01)                */
#define SPI_RXSTS_RXIEN                   SPI_RXSTS_RXIEN_Msk
#define SPI_RXSTS_RXFULL_Pos              (9UL)                     /*!< SPI RXSTS: RXFULL (Bit 9)                             */
#define SPI_RXSTS_RXFULL_Msk              (0x200UL)                 /*!< SPI RXSTS: RXFULL (Bitfield-Mask: 0x01)               */
#define SPI_RXSTS_RXFULL                  SPI_RXSTS_RXFULL_Msk
#define SPI_RXSTS_RXFOV_Pos               (8UL)                     /*!< SPI RXSTS: RXFOV (Bit 8)                              */
#define SPI_RXSTS_RXFOV_Msk               (0x100UL)                 /*!< SPI RXSTS: RXFOV (Bitfield-Mask: 0x01)                */
#define SPI_RXSTS_RXFOV                   SPI_RXSTS_RXFOV_Msk
#define SPI_RXSTS_RXFLEV_Pos              (4UL)                     /*!< SPI RXSTS: RXFLEV (Bit 4)                             */
#define SPI_RXSTS_RXFLEV_Msk              (0x70UL)                  /*!< SPI RXSTS: RXFLEV (Bitfield-Mask: 0x07)               */
#define SPI_RXSTS_RXFLEV                  SPI_RXSTS_RXFLEV_Msk
#define SPI_RXSTS_RXFFLAG_Pos             (0UL)                     /*!< SPI RXSTS: RXFFLAG (Bit 0)                            */
#define SPI_RXSTS_RXFFLAG_Msk             (0x7UL)                   /*!< SPI RXSTS: RXFFLAG (Bitfield-Mask: 0x07)              */
#define SPI_RXSTS_RXFFLAG                 SPI_RXSTS_RXFFLAG_Msk
/* =========================================================  RXDAT  ========================================================= */
#define SPI_RXDAT_RXD_Pos                 (0UL)                     /*!< SPI RXDAT: RXD (Bit 0)                                */
#define SPI_RXDAT_RXD_Msk                 (0xffUL)                  /*!< SPI RXDAT: RXD (Bitfield-Mask: 0xff)                  */
#define SPI_RXDAT_RXD                     SPI_RXDAT_RXD_Msk
/* =========================================================  MISC  ========================================================== */
#define SPI_MISC_OVER_Pos                 (9UL)                     /*!< SPI MISC: OVER (Bit 9)                                */
#define SPI_MISC_OVER_Msk                 (0x200UL)                 /*!< SPI MISC: OVER (Bitfield-Mask: 0x01)                  */
#define SPI_MISC_OVER                     SPI_MISC_OVER_Msk
#define SPI_MISC_SMART_Pos                (8UL)                     /*!< SPI MISC: SMART (Bit 8)                               */
#define SPI_MISC_SMART_Msk                (0x100UL)                 /*!< SPI MISC: SMART (Bitfield-Mask: 0x01)                 */
#define SPI_MISC_SMART                    SPI_MISC_SMART_Msk
#define SPI_MISC_BSY_Pos                  (4UL)                     /*!< SPI MISC: BSY (Bit 4)                                 */
#define SPI_MISC_BSY_Msk                  (0x10UL)                  /*!< SPI MISC: BSY (Bitfield-Mask: 0x01)                   */
#define SPI_MISC_BSY                      SPI_MISC_BSY_Msk
#define SPI_MISC_RFF_Pos                  (3UL)                     /*!< SPI MISC: RFF (Bit 3)                                 */
#define SPI_MISC_RFF_Msk                  (0x8UL)                   /*!< SPI MISC: RFF (Bitfield-Mask: 0x01)                   */
#define SPI_MISC_RFF                      SPI_MISC_RFF_Msk
#define SPI_MISC_RNE_Pos                  (2UL)                     /*!< SPI MISC: RNE (Bit 2)                                 */
#define SPI_MISC_RNE_Msk                  (0x4UL)                   /*!< SPI MISC: RNE (Bitfield-Mask: 0x01)                   */
#define SPI_MISC_RNE                      SPI_MISC_RNE_Msk
#define SPI_MISC_TNF_Pos                  (1UL)                     /*!< SPI MISC: TNF (Bit 1)                                 */
#define SPI_MISC_TNF_Msk                  (0x2UL)                   /*!< SPI MISC: TNF (Bitfield-Mask: 0x01)                   */
#define SPI_MISC_TNF                      SPI_MISC_TNF_Msk
#define SPI_MISC_TFE_Pos                  (0UL)                     /*!< SPI MISC: TFE (Bit 0)                                 */
#define SPI_MISC_TFE_Msk                  (0x1UL)                   /*!< SPI MISC: TFE (Bitfield-Mask: 0x01)                   */
#define SPI_MISC_TFE                      SPI_MISC_TFE_Msk


/* =========================================================================================================================== */
/* ================                                            TMR                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  CTRL  ========================================================== */
#define TMR_CTRL_INTEN_Pos                (3UL)                     /*!< TMR CTRL: INTEN (Bit 3)                               */
#define TMR_CTRL_INTEN_Msk                (0x8UL)                   /*!< TMR CTRL: INTEN (Bitfield-Mask: 0x01)                 */
#define TMR_CTRL_INTEN                    TMR_CTRL_INTEN_Msk
#define TMR_CTRL_EXTCLK_Pos               (2UL)                     /*!< TMR CTRL: EXTCLK (Bit 2)                              */
#define TMR_CTRL_EXTCLK_Msk               (0x4UL)                   /*!< TMR CTRL: EXTCLK (Bitfield-Mask: 0x01)                */
#define TMR_CTRL_EXTCLK                   TMR_CTRL_EXTCLK_Msk
#define TMR_CTRL_EXTEN_Pos                (1UL)                     /*!< TMR CTRL: EXTEN (Bit 1)                               */
#define TMR_CTRL_EXTEN_Msk                (0x2UL)                   /*!< TMR CTRL: EXTEN (Bitfield-Mask: 0x01)                 */
#define TMR_CTRL_EXTEN                    TMR_CTRL_EXTEN_Msk
#define TMR_CTRL_EN_Pos                   (0UL)                     /*!< TMR CTRL: EN (Bit 0)                                  */
#define TMR_CTRL_EN_Msk                   (0x1UL)                   /*!< TMR CTRL: EN (Bitfield-Mask: 0x01)                    */
#define TMR_CTRL_EN                       TMR_CTRL_EN_Msk
/* =========================================================  VALUE  ========================================================= */
#define TMR_VALUE_VALUE_Pos               (0UL)                     /*!< TMR VALUE: VALUE (Bit 0)                              */
#define TMR_VALUE_VALUE_Msk               (0xffffffffUL)            /*!< TMR VALUE: VALUE (Bitfield-Mask: 0xffffffff)          */
#define TMR_VALUE_VALUE                   TMR_VALUE_VALUE_Msk
/* ========================================================  RELOAD  ========================================================= */
#define TMR_RELOAD_RELOAD_Pos             (0UL)                     /*!< TMR RELOAD: RELOAD (Bit 0)                            */
#define TMR_RELOAD_RELOAD_Msk             (0xffffffffUL)            /*!< TMR RELOAD: RELOAD (Bitfield-Mask: 0xffffffff)        */
#define TMR_RELOAD_RELOAD                 TMR_RELOAD_RELOAD_Msk
/* ========================================================  INTSTS  ========================================================= */
#define TMR_INTSTS_INTSTS_Pos             (0UL)                     /*!< TMR INTSTS: INTSTS (Bit 0)                            */
#define TMR_INTSTS_INTSTS_Msk             (0x1UL)                   /*!< TMR INTSTS: INTSTS (Bitfield-Mask: 0x01)              */
#define TMR_INTSTS_INTSTS                 TMR_INTSTS_INTSTS_Msk


/* =========================================================================================================================== */
/* ================                                           UART                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  DATA  ========================================================== */
#define UART_DATA_DATA_Pos                (0UL)                     /*!< UART DATA: DATA (Bit 0)                               */
#define UART_DATA_DATA_Msk                (0xffUL)                  /*!< UART DATA: DATA (Bitfield-Mask: 0xff)                 */
#define UART_DATA_DATA                    UART_DATA_DATA_Msk
/* =========================================================  STATE  ========================================================= */
#define UART_STATE_DMATXDONE_Pos          (7UL)                     /*!< UART STATE: DMATXDONE (Bit 7)                         */
#define UART_STATE_DMATXDONE_Msk          (0x80UL)                  /*!< UART STATE: DMATXDONE (Bitfield-Mask: 0x01)           */
#define UART_STATE_DMATXDONE              UART_STATE_DMATXDONE_Msk
#define UART_STATE_RXPSTS_Pos             (6UL)                     /*!< UART STATE: RXPSTS (Bit 6)                            */
#define UART_STATE_RXPSTS_Msk             (0x40UL)                  /*!< UART STATE: RXPSTS (Bitfield-Mask: 0x01)              */
#define UART_STATE_RXPSTS                 UART_STATE_RXPSTS_Msk
#define UART_STATE_TXDONE_Pos             (5UL)                     /*!< UART STATE: TXDONE (Bit 5)                            */
#define UART_STATE_TXDONE_Msk             (0x20UL)                  /*!< UART STATE: TXDONE (Bitfield-Mask: 0x01)              */
#define UART_STATE_TXDONE                 UART_STATE_TXDONE_Msk
#define UART_STATE_RXPE_Pos               (4UL)                     /*!< UART STATE: RXPE (Bit 4)                              */
#define UART_STATE_RXPE_Msk               (0x10UL)                  /*!< UART STATE: RXPE (Bitfield-Mask: 0x01)                */
#define UART_STATE_RXPE                   UART_STATE_RXPE_Msk
#define UART_STATE_RXOV_Pos               (3UL)                     /*!< UART STATE: RXOV (Bit 3)                              */
#define UART_STATE_RXOV_Msk               (0x8UL)                   /*!< UART STATE: RXOV (Bitfield-Mask: 0x01)                */
#define UART_STATE_RXOV                   UART_STATE_RXOV_Msk
#define UART_STATE_TXOV_Pos               (2UL)                     /*!< UART STATE: TXOV (Bit 2)                              */
#define UART_STATE_TXOV_Msk               (0x4UL)                   /*!< UART STATE: TXOV (Bitfield-Mask: 0x01)                */
#define UART_STATE_TXOV                   UART_STATE_TXOV_Msk
#define UART_STATE_RXFULL_Pos             (1UL)                     /*!< UART STATE: RXFULL (Bit 1)                            */
#define UART_STATE_RXFULL_Msk             (0x2UL)                   /*!< UART STATE: RXFULL (Bitfield-Mask: 0x01)              */
#define UART_STATE_RXFULL                 UART_STATE_RXFULL_Msk
/* =========================================================  CTRL  ========================================================== */
#define UART_CTRL_TXDONEIE_Pos            (8UL)                     /*!< UART CTRL: TXDONEIE (Bit 8)                           */
#define UART_CTRL_TXDONEIE_Msk            (0x100UL)                 /*!< UART CTRL: TXDONEIE (Bitfield-Mask: 0x01)             */
#define UART_CTRL_TXDONEIE                UART_CTRL_TXDONEIE_Msk
#define UART_CTRL_RXPEIE_Pos              (7UL)                     /*!< UART CTRL: RXPEIE (Bit 7)                             */
#define UART_CTRL_RXPEIE_Msk              (0x80UL)                  /*!< UART CTRL: RXPEIE (Bitfield-Mask: 0x01)               */
#define UART_CTRL_RXPEIE                  UART_CTRL_RXPEIE_Msk
#define UART_CTRL_RXOVIE_Pos              (5UL)                     /*!< UART CTRL: RXOVIE (Bit 5)                             */
#define UART_CTRL_RXOVIE_Msk              (0x20UL)                  /*!< UART CTRL: RXOVIE (Bitfield-Mask: 0x01)               */
#define UART_CTRL_RXOVIE                  UART_CTRL_RXOVIE_Msk
#define UART_CTRL_TXOVIE_Pos              (4UL)                     /*!< UART CTRL: TXOVIE (Bit 4)                             */
#define UART_CTRL_TXOVIE_Msk              (0x10UL)                  /*!< UART CTRL: TXOVIE (Bitfield-Mask: 0x01)               */
#define UART_CTRL_TXOVIE                  UART_CTRL_TXOVIE_Msk
#define UART_CTRL_RXIE_Pos                (3UL)                     /*!< UART CTRL: RXIE (Bit 3)                               */
#define UART_CTRL_RXIE_Msk                (0x8UL)                   /*!< UART CTRL: RXIE (Bitfield-Mask: 0x01)                 */
#define UART_CTRL_RXIE                    UART_CTRL_RXIE_Msk
#define UART_CTRL_RXEN_Pos                (1UL)                     /*!< UART CTRL: RXEN (Bit 1)                               */
#define UART_CTRL_RXEN_Msk                (0x2UL)                   /*!< UART CTRL: RXEN (Bitfield-Mask: 0x01)                 */
#define UART_CTRL_RXEN                    UART_CTRL_RXEN_Msk
#define UART_CTRL_TXEN_Pos                (0UL)                     /*!< UART CTRL: TXEN (Bit 0)                               */
#define UART_CTRL_TXEN_Msk                (0x1UL)                   /*!< UART CTRL: TXEN (Bitfield-Mask: 0x01)                 */
#define UART_CTRL_TXEN                    UART_CTRL_TXEN_Msk
/* ========================================================  INTSTS  ========================================================= */
#define UART_INTSTS_TXDONEIF_Pos          (5UL)                     /*!< UART INTSTS: TXDONEIF (Bit 5)                         */
#define UART_INTSTS_TXDONEIF_Msk          (0x20UL)                  /*!< UART INTSTS: TXDONEIF (Bitfield-Mask: 0x01)           */
#define UART_INTSTS_TXDONEIF              UART_INTSTS_TXDONEIF_Msk
#define UART_INTSTS_RXPEIF_Pos            (4UL)                     /*!< UART INTSTS: RXPEIF (Bit 4)                           */
#define UART_INTSTS_RXPEIF_Msk            (0x10UL)                  /*!< UART INTSTS: RXPEIF (Bitfield-Mask: 0x01)             */
#define UART_INTSTS_RXPEIF                UART_INTSTS_RXPEIF_Msk
#define UART_INTSTS_RXOVIF_Pos            (3UL)                     /*!< UART INTSTS: RXOVIF (Bit 3)                           */
#define UART_INTSTS_RXOVIF_Msk            (0x8UL)                   /*!< UART INTSTS: RXOVIF (Bitfield-Mask: 0x01)             */
#define UART_INTSTS_RXOVIF                UART_INTSTS_RXOVIF_Msk
#define UART_INTSTS_TXOVIF_Pos            (2UL)                     /*!< UART INTSTS: TXOVIF (Bit 2)                           */
#define UART_INTSTS_TXOVIF_Msk            (0x4UL)                   /*!< UART INTSTS: TXOVIF (Bitfield-Mask: 0x01)             */
#define UART_INTSTS_TXOVIF                UART_INTSTS_TXOVIF_Msk
#define UART_INTSTS_RXIF_Pos              (1UL)                     /*!< UART INTSTS: RXIF (Bit 1)                             */
#define UART_INTSTS_RXIF_Msk              (0x2UL)                   /*!< UART INTSTS: RXIF (Bitfield-Mask: 0x01)               */
#define UART_INTSTS_RXIF                  UART_INTSTS_RXIF_Msk
/* ========================================================  BAUDDIV  ======================================================== */
#define UART_BAUDDIV_BAUDDIV_Pos          (0UL)                     /*!< UART BAUDDIV: BAUDDIV (Bit 0)                         */
#define UART_BAUDDIV_BAUDDIV_Msk          (0xfffffUL)               /*!< UART BAUDDIV: BAUDDIV (Bitfield-Mask: 0xfffff)        */
#define UART_BAUDDIV_BAUDDIV              UART_BAUDDIV_BAUDDIV_Msk
/* =========================================================  CTRL2  ========================================================= */
#define UART_CTRL2_PMODE_Pos              (1UL)                     /*!< UART CTRL2: PMODE (Bit 1)                             */
#define UART_CTRL2_PMODE_Msk              (0xeUL)                   /*!< UART CTRL2: PMODE (Bitfield-Mask: 0x07)               */
#define UART_CTRL2_PMODE                  UART_CTRL2_PMODE_Msk
#define UART_CTRL2_MSB_Pos                (0UL)                     /*!< UART CTRL2: MSB (Bit 0)                               */
#define UART_CTRL2_MSB_Msk                (0x1UL)                   /*!< UART CTRL2: MSB (Bitfield-Mask: 0x01)                 */
#define UART_CTRL2_MSB                    UART_CTRL2_MSB_Msk


/* =========================================================================================================================== */
/* ================                                           U32K                                            ================ */
/* =========================================================================================================================== */

/* =========================================================  CTRL0  ========================================================= */
#define U32K_CTRL0_WKUMODE_Pos            (8UL)                     /*!< U32K CTRL0: WKUMODE (Bit 8)                           */
#define U32K_CTRL0_WKUMODE_Msk            (0x100UL)                 /*!< U32K CTRL0: WKUMODE (Bitfield-Mask: 0x01)             */
#define U32K_CTRL0_WKUMODE                U32K_CTRL0_WKUMODE_Msk
#define U32K_CTRL0_DEBSEL_Pos             (6UL)                     /*!< U32K CTRL0: DEBSEL (Bit 6)                            */
#define U32K_CTRL0_DEBSEL_Msk             (0xc0UL)                  /*!< U32K CTRL0: DEBSEL (Bitfield-Mask: 0x03)              */
#define U32K_CTRL0_DEBSEL                 U32K_CTRL0_DEBSEL_Msk
#define U32K_CTRL0_PMODE_Pos              (3UL)                     /*!< U32K CTRL0: PMODE (Bit 3)                             */
#define U32K_CTRL0_PMODE_Msk              (0x38UL)                  /*!< U32K CTRL0: PMODE (Bitfield-Mask: 0x07)               */
#define U32K_CTRL0_PMODE                  U32K_CTRL0_PMODE_Msk
#define U32K_CTRL0_MSB_Pos                (2UL)                     /*!< U32K CTRL0: MSB (Bit 2)                               */
#define U32K_CTRL0_MSB_Msk                (0x4UL)                   /*!< U32K CTRL0: MSB (Bitfield-Mask: 0x01)                 */
#define U32K_CTRL0_MSB                    U32K_CTRL0_MSB_Msk
#define U32K_CTRL0_ACOFF_Pos              (1UL)                     /*!< U32K CTRL0: ACOFF (Bit 1)                             */
#define U32K_CTRL0_ACOFF_Msk              (0x2UL)                   /*!< U32K CTRL0: ACOFF (Bitfield-Mask: 0x01)               */
#define U32K_CTRL0_ACOFF                  U32K_CTRL0_ACOFF_Msk
#define U32K_CTRL0_EN_Pos                 (0UL)                     /*!< U32K CTRL0: EN (Bit 0)                                */
#define U32K_CTRL0_EN_Msk                 (0x1UL)                   /*!< U32K CTRL0: EN (Bitfield-Mask: 0x01)                  */
#define U32K_CTRL0_EN                     U32K_CTRL0_EN_Msk
/* =========================================================  CTRL1  ========================================================= */
#define U32K_CTRL1_RXSEL_Pos              (4UL)                     /*!< U32K CTRL1: RXSEL (Bit 4)                             */
#define U32K_CTRL1_RXSEL_Msk              (0x30UL)                  /*!< U32K CTRL1: RXSEL (Bitfield-Mask: 0x03)               */
#define U32K_CTRL1_RXSEL                  U32K_CTRL1_RXSEL_Msk
#define U32K_CTRL1_RXOVIE_Pos             (2UL)                     /*!< U32K CTRL1: RXOVIE (Bit 2)                            */
#define U32K_CTRL1_RXOVIE_Msk             (0x4UL)                   /*!< U32K CTRL1: RXOVIE (Bitfield-Mask: 0x01)              */
#define U32K_CTRL1_RXOVIE                 U32K_CTRL1_RXOVIE_Msk
#define U32K_CTRL1_RXPEIE_Pos             (1UL)                     /*!< U32K CTRL1: RXPEIE (Bit 1)                            */
#define U32K_CTRL1_RXPEIE_Msk             (0x2UL)                   /*!< U32K CTRL1: RXPEIE (Bitfield-Mask: 0x01)              */
#define U32K_CTRL1_RXPEIE                 U32K_CTRL1_RXPEIE_Msk
#define U32K_CTRL1_RXIE_Pos               (0UL)                     /*!< U32K CTRL1: RXIE (Bit 0)                              */
#define U32K_CTRL1_RXIE_Msk               (0x1UL)                   /*!< U32K CTRL1: RXIE (Bitfield-Mask: 0x01)                */
#define U32K_CTRL1_RXIE                   U32K_CTRL1_RXIE_Msk
/* ========================================================  BAUDDIV  ======================================================== */
#define U32K_BAUDDIV_BAUDDIV_Pos          (0UL)                     /*!< U32K BAUDDIV: BAUDDIV (Bit 0)                         */
#define U32K_BAUDDIV_BAUDDIV_Msk          (0xffffUL)                /*!< U32K BAUDDIV: BAUDDIV (Bitfield-Mask: 0xffff)         */
#define U32K_BAUDDIV_BAUDDIV              U32K_BAUDDIV_BAUDDIV_Msk
/* =========================================================  DATA  ========================================================== */
#define U32K_DATA_DATA_Pos                (0UL)                     /*!< U32K DATA: DATA (Bit 0)                               */
#define U32K_DATA_DATA_Msk                (0xffUL)                  /*!< U32K DATA: DATA (Bitfield-Mask: 0xff)                 */
#define U32K_DATA_DATA                    U32K_DATA_DATA_Msk
/* ==========================================================  STS  ========================================================== */
#define U32K_STS_RXOV_Pos                 (2UL)                     /*!< U32K STS: RXOV (Bit 2)                                */
#define U32K_STS_RXOV_Msk                 (0x4UL)                   /*!< U32K STS: RXOV (Bitfield-Mask: 0x01)                  */
#define U32K_STS_RXOV                     U32K_STS_RXOV_Msk
#define U32K_STS_RXPE_Pos                 (1UL)                     /*!< U32K STS: RXPE (Bit 1)                                */
#define U32K_STS_RXPE_Msk                 (0x2UL)                   /*!< U32K STS: RXPE (Bitfield-Mask: 0x01)                  */
#define U32K_STS_RXPE                     U32K_STS_RXPE_Msk
#define U32K_STS_RXIF_Pos                 (0UL)                     /*!< U32K STS: RXIF (Bit 0)                                */
#define U32K_STS_RXIF_Msk                 (0x1UL)                   /*!< U32K STS: RXIF (Bitfield-Mask: 0x01)                  */
#define U32K_STS_RXIF                     U32K_STS_RXIF_Msk

/** @} */ /* End of group PosMask_peripherals */
#include "system_target.h"                      /*!< target System                                                             */


#ifdef __cplusplus
}
#endif

#endif /* TARGET_H */


/** @} */ /* End of group target */

/** @} */ /* End of group Vango */
