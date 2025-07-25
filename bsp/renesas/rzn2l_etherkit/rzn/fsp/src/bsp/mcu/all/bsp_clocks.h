/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef BSP_CLOCKS_H
#define BSP_CLOCKS_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_clock_cfg.h"
#include "bsp_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Startup clock frequency of each system clock. These macros are only helpful if the system clock and dividers have
 * not changed since startup. These macros are not used in FSP modules except for the clock startup code. */

/* xSPI unit0 clock options. */
#define BSP_CLOCKS_XSPI0_CLOCK_DIV0_133_3_MHZ               (0x02) // xSPI0 base clock 800MHz and xSPI0 clock 133.3MHz.
#define BSP_CLOCKS_XSPI0_CLOCK_DIV0_100_0_MHZ               (0x03) // xSPI0 base clock 800MHz and xSPI0 clock 100.0 MHz.
#define BSP_CLOCKS_XSPI0_CLOCK_DIV0_50_0_MHZ                (0x04) // xSPI0 base clock 800MHz and xSPI0 clock 50.0 MHz.
#define BSP_CLOCKS_XSPI0_CLOCK_DIV0_25_0_MHZ                (0x05) // xSPI0 base clock 800MHz and xSPI0 clock 25.0 MHz.
#define BSP_CLOCKS_XSPI0_CLOCK_DIV0_12_5_MHZ                (0x06) // xSPI0 base clock 800MHz and xSPI0 clock 12.5 MHz.
#define BSP_CLOCKS_XSPI0_CLOCK_DIV1_75_0_MHZ                (0x43) // xSPI0 base clock 600MHz and xSPI0 clock 75.0 MHz.
#define BSP_CLOCKS_XSPI0_CLOCK_DIV1_37_5_MHZ                (0x44) // xSPI0 base clock 600MHz and xSPI0 clock 37.5 MHz.

/* xSPI unit1 clock options. */
#define BSP_CLOCKS_XSPI1_CLOCK_DIV0_133_3_MHZ               (0x02) // xSPI1 base clock 800MHz and xSPI1 clock 133.3MHz.
#define BSP_CLOCKS_XSPI1_CLOCK_DIV0_100_0_MHZ               (0x03) // xSPI1 base clock 800MHz and xSPI1 clock 100.0 MHz.
#define BSP_CLOCKS_XSPI1_CLOCK_DIV0_50_0_MHZ                (0x04) // xSPI1 base clock 800MHz and xSPI1 clock 50.0 MHz.
#define BSP_CLOCKS_XSPI1_CLOCK_DIV0_25_0_MHZ                (0x05) // xSPI1 base clock 800MHz and xSPI1 clock 25.0 MHz.
#define BSP_CLOCKS_XSPI1_CLOCK_DIV0_12_5_MHZ                (0x06) // xSPI1 base clock 800MHz and xSPI1 clock 12.5 MHz.
#define BSP_CLOCKS_XSPI1_CLOCK_DIV1_75_0_MHZ                (0x43) // xSPI1 base clock 600MHz and xSPI1 clock 75.0 MHz.
#define BSP_CLOCKS_XSPI1_CLOCK_DIV1_37_5_MHZ                (0x44) // xSPI1 base clock 600MHz and xSPI1 clock 37.5 MHz.

/* CKIO clock options. */
#define BSP_CLOCKS_CKIO_ICLK_DIV2                           (0)    // CKIO clock 100.0 MHz  (when SCKCR2.DIVSELSUB = 0),
                                                                   // or 75.0 MHz  (when SCKCR2.DIVSELSUB = 1).
#define BSP_CLOCKS_CKIO_ICLK_DIV3                           (1)    // CKIO clock 66.7 MHz  (when SCKCR2.DIVSELSUB = 0),
                                                                   // or 50.0 MHz  (when SCKCR2.DIVSELSUB = 1).
#define BSP_CLOCKS_CKIO_ICLK_DIV4                           (2)    // CKIO clock 50.0 MHz  (when SCKCR2.DIVSELSUB = 0),
                                                                   // or 37.5 MHz  (when SCKCR2.DIVSELSUB = 1).
#define BSP_CLOCKS_CKIO_ICLK_DIV5                           (3)    // CKIO clock 40.0 MHz  (when SCKCR2.DIVSELSUB = 0),
                                                                   // or 30.0 MHz  (when SCKCR2.DIVSELSUB = 1).
#define BSP_CLOCKS_CKIO_ICLK_DIV6                           (4)    // CKIO clock 33.3 MHz  (when SCKCR2.DIVSELSUB = 0),
                                                                   // or 25.0 MHz  (when SCKCR2.DIVSELSUB = 1).
#define BSP_CLOCKS_CKIO_ICLK_DIV7                           (5)    // CKIO clock 28.6 MHz  (when SCKCR2.DIVSELSUB = 0),
                                                                   // or 21.4 MHz  (when SCKCR2.DIVSELSUB = 1).
#define BSP_CLOCKS_CKIO_ICLK_DIV8                           (6)    // CKIO clock 25.0 MHz  (when SCKCR2.DIVSELSUB = 0),
                                                                   // or 18.75 MHz (when SCKCR2.DIVSELSUB = 1).

/* CANFD clock options. */
#define BSP_CLOCKS_CANFD_CLOCK_80_MHZ                       (0)    // CANFD clock 80 MHz.
#define BSP_CLOCKS_CANFD_CLOCK_40_MHZ                       (1)    // CANFD clock 40 MHz.

/* Ethernet PHY reference clock (ETHn_REFCLK : n = 0 to 2) options. */
#define BSP_CLOCKS_PHYSEL_PLL1_DIV                          (0)    // PLL1 devider clock.
#define BSP_CLOCKS_PHYSEL_MAINOSC_DIV                       (1)    // Main clock oscillator.

/* Alternative clock options when main clock abnormal oscillation is detected in CLMA3. */
#define BSP_CLOCKS_CLMASEL_LOCO                             (0)    // LOCO clock.
#define BSP_CLOCKS_CLMASEL_PLL                              (1)    // PLL clock.

/* SPI clock options. */
#define BSP_CLOCKS_SPI0_ASYNCHRONOUS_SERIAL_CLOCK_75_MHZ    (0)    // SPI0 asynchronous serial clock 75.0 MHz.
#define BSP_CLOCKS_SPI0_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ    (1)    // SPI0 asynchronous serial clock 96.0 MHz.
#define BSP_CLOCKS_SPI1_ASYNCHRONOUS_SERIAL_CLOCK_75_MHZ    (0)    // SPI1 asynchronous serial clock 75.0 MHz.
#define BSP_CLOCKS_SPI1_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ    (1)    // SPI1 asynchronous serial clock 96.0 MHz.
#define BSP_CLOCKS_SPI2_ASYNCHRONOUS_SERIAL_CLOCK_75_MHZ    (0)    // SPI2 asynchronous serial clock 75.0 MHz.
#define BSP_CLOCKS_SPI2_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ    (1)    // SPI2 asynchronous serial clock 96.0 MHz.
#define BSP_CLOCKS_SPI3_ASYNCHRONOUS_SERIAL_CLOCK_75_MHZ    (0)    // SPI3 asynchronous serial clock 75.0 MHz.
#define BSP_CLOCKS_SPI3_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ    (1)    // SPI3 asynchronous serial clock 96.0 MHz.

/* SCI clock options. */
#define BSP_CLOCKS_SCI0_ASYNCHRONOUS_SERIAL_CLOCK_75_MHZ    (0)    // SCI0 asynchronous serial clock 75.0 MHz.
#define BSP_CLOCKS_SCI0_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ    (1)    // SCI0 asynchronous serial clock 96.0 MHz.
#define BSP_CLOCKS_SCI1_ASYNCHRONOUS_SERIAL_CLOCK_75_MHZ    (0)    // SCI1 asynchronous serial clock 75.0 MHz.
#define BSP_CLOCKS_SCI1_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ    (1)    // SCI1 asynchronous serial clock 96.0 MHz.
#define BSP_CLOCKS_SCI2_ASYNCHRONOUS_SERIAL_CLOCK_75_MHZ    (0)    // SCI2 asynchronous serial clock 75.0 MHz.
#define BSP_CLOCKS_SCI2_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ    (1)    // SCI2 asynchronous serial clock 96.0 MHz.
#define BSP_CLOCKS_SCI3_ASYNCHRONOUS_SERIAL_CLOCK_75_MHZ    (0)    // SCI3 asynchronous serial clock 75.0 MHz.
#define BSP_CLOCKS_SCI3_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ    (1)    // SCI3 asynchronous serial clock 96.0 MHz.
#define BSP_CLOCKS_SCI4_ASYNCHRONOUS_SERIAL_CLOCK_75_MHZ    (0)    // SCI4 asynchronous serial clock 75.0 MHz.
#define BSP_CLOCKS_SCI4_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ    (1)    // SCI4 asynchronous serial clock 96.0 MHz.
#define BSP_CLOCKS_SCI5_ASYNCHRONOUS_SERIAL_CLOCK_75_MHZ    (0)    // SCI5 asynchronous serial clock 75.0 MHz.
#define BSP_CLOCKS_SCI5_ASYNCHRONOUS_SERIAL_CLOCK_96_MHZ    (1)    // SCI5 asynchronous serial clock 96.0 MHz.

/* CPU0 clock options. */
#define BSP_CLOCKS_FSELCPU0_ICLK_MUL2                       (1)    // CPU0 clock 400 MHz (when SCKCR2.DIVSELSUB = 0),
                                                                   // or 300 MHz (when SCKCR2.DIVSELSUB = 1).
#define BSP_CLOCKS_FSELCPU0_ICLK_MUL1                       (0)    // CPU0 clock 200 MHz (when SCKCR2.DIVSELSUB = 0),
                                                                   // or 150 MHz (when SCKCR2.DIVSELSUB = 1).

/* Peripheral module base clock options. */
#define BSP_CLOCKS_DIVSELSUB_0                              (0)    // ICLK:200MHz, PCLKH:200MHz, PCLKM:100MHz,
                                                                   // PCLKL:50MHz, PCLKADC:25MHz, PCLKGPTL:400MHz.
#define BSP_CLOCKS_DIVSELSUB_1                              (1)    // ICLK:150MHz, PCLKH:150MHz, PCLKM:75 MHz,
                                                                   // PCLKL:37.5MHz, PCLKADC:18.75MHz, PCLKGPTL:300MHz.

/* LOCO enable options. */
#define BSP_CLOCKS_LOCO_DISABLE                             (0)    // LOCO Stop
#define BSP_CLOCKS_LOCO_ENABLE                              (1)    // LOCO Run

/* PLL1 enable options. */
#define BSP_CLOCKS_PLL1_INITIAL                             (0xFF) // Initial (This value should not be reflected in the register)
#define BSP_CLOCKS_PLL1_STANDBY                             (0)    // PLL1 is standby state.
#define BSP_CLOCKS_PLL1_NORMAL                              (1)    // PLL1 is normal state.

/* CLMA error mask options. */
#define BSP_CLOCKS_CLMA0_ERROR_MASK                         (0)    // CLMA0 error is not transferred to POE3 and POEG.
#define BSP_CLOCKS_CLMA0_ERROR_NOT_MASK                     (1)    // CLMA0 error is transferred to POE3 and POEG.
#define BSP_CLOCKS_CLMA1_ERROR_MASK                         (0)    // CLMA1 error is not transferred to POE3 and POEG.
#define BSP_CLOCKS_CLMA1_ERROR_NOT_MASK                     (1)    // CLMA1 error is transferred to POE3 and POEG.
#define BSP_CLOCKS_CLMA3_ERROR_MASK                         (0)    // CLMA3 error is not transferred to POE3 and POEG.
#define BSP_CLOCKS_CLMA3_ERROR_NOT_MASK                     (1)    // CLMA3 error is transferred to POE3 and POEG.

/* CLMA enable options. */
#define BSP_CLOCKS_CLMA0_DISABLE                            (0)    // Disable CLMA0 operation.
#define BSP_CLOCKS_CLMA0_ENABLE                             (1)    // Enable CLMA0 operation.
#define BSP_CLOCKS_CLMA1_DISABLE                            (0)    // Disable CLMA1 operation.
#define BSP_CLOCKS_CLMA1_ENABLE                             (1)    // Enable CLMA1 operation.
#define BSP_CLOCKS_CLMA2_DISABLE                            (0)    // Disable CLMA2 operation.
#define BSP_CLOCKS_CLMA2_ENABLE                             (1)    // Enable CLMA2 operation.
#define BSP_CLOCKS_CLMA3_DISABLE                            (0)    // Disable CLMA3 operation.
#define BSP_CLOCKS_CLMA3_ENABLE                             (1)    // Enable CLMA3 operation.

/* Create a mask of valid bits in SCKCR. */
#define BSP_PRV_SCKCR_FSELXSPI0_MASK                        (7U << 0)
#define BSP_PRV_SCKCR_DIVSELXSPI0_MASK                      (1U << 6)
#define BSP_PRV_SCKCR_FSELXSPI1_MASK                        (7U << 8)
#define BSP_PRV_SCKCR_DIVSELXSPI1_MASK                      (1U << 14)
#define BSP_PRV_SCKCR_CKIO_MASK                             (7U << 16)
#define BSP_PRV_SCKCR_FSELCANFD_MASK                        (1U << 20)
#define BSP_PRV_SCKCR_PHYSEL_MASK                           (1U << 21)
#define BSP_PRV_SCKCR_CLMASEL_MASK                          (1U << 22)
#define BSP_PRV_SCKCR_SPI0ASYNCSEL_MASK                     (1U << 24)
#define BSP_PRV_SCKCR_SPI1ASYNCSEL_MASK                     (1U << 25)
#define BSP_PRV_SCKCR_SPI2ASYNCSEL_MASK                     (1U << 26)
#define BSP_PRV_SCKCR_SCI0ASYNCSEL_MASK                     (1U << 27)
#define BSP_PRV_SCKCR_SCI1ASYNCSEL_MASK                     (1U << 28)
#define BSP_PRV_SCKCR_SCI2ASYNCSEL_MASK                     (1U << 29)
#define BSP_PRV_SCKCR_SCI3ASYNCSEL_MASK                     (1U << 30)
#define BSP_PRV_SCKCR_SCI4ASYNCSEL_MASK                     (1U << 31)
#define BSP_PRV_SCKCR_MASK                                  (((((((((((((((BSP_PRV_SCKCR_FSELXSPI0_MASK |    \
                                                                           BSP_PRV_SCKCR_DIVSELXSPI0_MASK) | \
                                                                          BSP_PRV_SCKCR_FSELXSPI1_MASK) |    \
                                                                         BSP_PRV_SCKCR_DIVSELXSPI1_MASK) |   \
                                                                        BSP_PRV_SCKCR_CKIO_MASK) |           \
                                                                       BSP_PRV_SCKCR_FSELCANFD_MASK) |       \
                                                                      BSP_PRV_SCKCR_PHYSEL_MASK) |           \
                                                                     BSP_PRV_SCKCR_CLMASEL_MASK) |           \
                                                                    BSP_PRV_SCKCR_SPI0ASYNCSEL_MASK) |       \
                                                                   BSP_PRV_SCKCR_SPI1ASYNCSEL_MASK) |        \
                                                                  BSP_PRV_SCKCR_SPI2ASYNCSEL_MASK) |         \
                                                                 BSP_PRV_SCKCR_SCI0ASYNCSEL_MASK) |          \
                                                                BSP_PRV_SCKCR_SCI1ASYNCSEL_MASK) |           \
                                                               BSP_PRV_SCKCR_SCI2ASYNCSEL_MASK) |            \
                                                              BSP_PRV_SCKCR_SCI3ASYNCSEL_MASK) |             \
                                                             BSP_PRV_SCKCR_SCI4ASYNCSEL_MASK)
#define BSP_PRV_SCKCR_DIVSELXSPI_MASK                       (BSP_PRV_SCKCR_DIVSELXSPI0_MASK | \
                                                             BSP_PRV_SCKCR_DIVSELXSPI1_MASK)

/* Create a mask of valid bits in SCKCR2. */
#define BSP_PRV_SCKCR2_FSELCPU0_MASK                        (3U << 0)
#define BSP_PRV_SCKCR2_RESERVED_BIT4_MASK                   (1U << 4)
#define BSP_PRV_SCKCR2_DIVSELSUB_MASK                       (1U << 5)
#define BSP_PRV_SCKCR2_SPI3ASYNCSEL_MASK                    (1U << 24)
#define BSP_PRV_SCKCR2_SCI5ASYNCSEL_MASK                    (1U << 25)
#define BSP_PRV_SCKCR2_MASK                                 ((((BSP_PRV_SCKCR2_FSELCPU0_MASK |       \
                                                                BSP_PRV_SCKCR2_RESERVED_BIT4_MASK) | \
                                                               BSP_PRV_SCKCR2_DIVSELSUB_MASK) |      \
                                                              BSP_PRV_SCKCR2_SPI3ASYNCSEL_MASK) |    \
                                                             BSP_PRV_SCKCR2_SCI5ASYNCSEL_MASK)

#define BSP_PRV_FSELCPU0_INIT                               (0x02U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/* Public functions defined in bsp.h */
void bsp_clock_init(void);             // Used internally by BSP

/* Used internally by CGC */

void bsp_prv_clock_set(uint32_t sckcr, uint32_t sckcr2);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
