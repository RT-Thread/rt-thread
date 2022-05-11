/* Auto-generated config file hpl_pmc_config.h */
#ifndef HPL_PMC_CONFIG_H
#define HPL_PMC_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

#include <peripheral_clk_config.h>

#define CLK_SRC_OPTION_OSC32K 0
#define CLK_SRC_OPTION_XOSC32K 1
#define CLK_SRC_OPTION_OSC12M 2
#define CLK_SRC_OPTION_XOSC20M 3

#define CLK_SRC_OPTION_SLCK 0
#define CLK_SRC_OPTION_MAINCK 1
#define CLK_SRC_OPTION_PLLACK 2
#define CLK_SRC_OPTION_UPLLCKDIV 3
#define CLK_SRC_OPTION_MCK 4

#define CLK_SRC_OPTION_UPLLCK 3

#define CONF_RC_4M 0
#define CONF_RC_8M 1
#define CONF_RC_12M 2

#define CONF_XOSC32K_NO_BYPASS 0
#define CONF_XOSC32K_BYPASS 1

#define CONF_XOSC20M_NO_BYPASS 0
#define CONF_XOSC20M_BYPASS 1

// <e> Clock_SLCK configuration
// <i> Indicates whether SLCK configuration is enabled or not
// <id> enable_clk_gen_slck
#ifndef CONF_CLK_SLCK_CONFIG
#define CONF_CLK_SLCK_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator SLCK source

// <CLK_SRC_OPTION_OSC32K"> 32kHz High Accuracy Internal Oscillator (OSC32K)

// <CLK_SRC_OPTION_XOSC32K"> 32kHz External Crystal Oscillator (XOSC32K)

// <i> This defines the clock source for SLCK
// <id> clk_gen_slck_oscillator
#ifndef CONF_CLK_GEN_SLCK_SRC
#define CONF_CLK_GEN_SLCK_SRC CLK_SRC_OPTION_OSC32K
#endif

// <q> Enable Clock_SLCK
// <i> Indicates whether SLCK is enabled or disable
// <id> clk_gen_slck_arch_enable
#ifndef CONF_CLK_SLCK_ENABLE
#define CONF_CLK_SLCK_ENABLE 1
#endif

// </h>

// <h>

// </h>
// </e>// <e> Clock_MAINCK configuration
// <i> Indicates whether MAINCK configuration is enabled or not
// <id> enable_clk_gen_mainck
#ifndef CONF_CLK_MAINCK_CONFIG
#define CONF_CLK_MAINCK_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator MAINCK source

// <CLK_SRC_OPTION_OSC12M"> Embedded 4/8/12MHz RC Oscillator (OSC12M)

// <CLK_SRC_OPTION_XOSC20M"> External 3-20MHz Oscillator (XOSC20M)

// <i> This defines the clock source for MAINCK
// <id> clk_gen_mainck_oscillator
#ifndef CONF_CLK_GEN_MAINCK_SRC
#define CONF_CLK_GEN_MAINCK_SRC CLK_SRC_OPTION_XOSC20M
#endif

// <q> Enable Clock_MAINCK
// <i> Indicates whether MAINCK is enabled or disable
// <id> clk_gen_mainck_arch_enable
#ifndef CONF_CLK_MAINCK_ENABLE
#define CONF_CLK_MAINCK_ENABLE 1
#endif

// <q> Enable Main Clock Failure Detection
// <i> Indicates whether Main Clock Failure Detection is enabled or disable.
// <i> The 4/8/12 MHz RC oscillator must be selected as the source of MAINCK.
// <id> clk_gen_cfden_enable
#ifndef CONF_CLK_CFDEN_ENABLE
#define CONF_CLK_CFDEN_ENABLE 0
#endif

// </h>

// <h>

// </h>
// </e>// <e> Clock_MCKR configuration
// <i> Indicates whether MCKR configuration is enabled or not
// <id> enable_clk_gen_mckr
#ifndef CONF_CLK_MCKR_CONFIG
#define CONF_CLK_MCKR_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator MCKR source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <CLK_SRC_OPTION_MAINCK"> Main Clock (MAINCK)

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_UPLLCKDIV"> UDPLL with Divider (MCKR UPLLDIV2)

// <i> This defines the clock source for MCKR
// <id> clk_gen_mckr_oscillator
#ifndef CONF_CLK_GEN_MCKR_SRC
#define CONF_CLK_GEN_MCKR_SRC CLK_SRC_OPTION_PLLACK
#endif

// <q> Enable Clock_MCKR
// <i> Indicates whether MCKR is enabled or disable
// <id> clk_gen_mckr_arch_enable
#ifndef CONF_CLK_MCKR_ENABLE
#define CONF_CLK_MCKR_ENABLE 1
#endif

// </h>

// <h>

// <o> Master Clock Prescaler
// <0=> 1
// <1=> 2
// <2=> 4
// <3=> 8
// <4=> 16
// <5=> 32
// <6=> 64
// <7=> 3
// <i> Select the clock prescaler.
// <id> mckr_presc
#ifndef CONF_MCKR_PRESC
#define CONF_MCKR_PRESC 0
#endif

// </h>
// </e>// <e> Clock_MCK configuration
// <i> Indicates whether MCK configuration is enabled or not
// <id> enable_clk_gen_mck
#ifndef CONF_CLK_MCK_CONFIG
#define CONF_CLK_MCK_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator MCK source

// <CLK_SRC_OPTION_MCKR"> Master Clock Controller (PMC_MCKR)

// <i> This defines the clock source for MCK
// <id> clk_gen_mck_oscillator
#ifndef CONF_CLK_GEN_MCK_SRC
#define CONF_CLK_GEN_MCK_SRC CLK_SRC_OPTION_MCKR
#endif

// </h>

// <h>

//<o> Master Clock Controller Divider MCK divider
// <0=> 1
// <1=> 2
// <3=> 3
// <2=> 4
// <i> Select the master clock divider.
// <id> mck_div
#ifndef CONF_MCK_DIV
#define CONF_MCK_DIV 1
#endif

// </h>
// </e>// <e> Clock_SYSTICK configuration
// <i> Indicates whether SYSTICK configuration is enabled or not
// <id> enable_clk_gen_systick
#ifndef CONF_CLK_SYSTICK_CONFIG
#define CONF_CLK_SYSTICK_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator SYSTICK source

// <CLK_SRC_OPTION_MCKR"> Master Clock Controller (PMC_MCKR)

// <i> This defines the clock source for SYSTICK
// <id> clk_gen_systick_oscillator
#ifndef CONF_CLK_GEN_SYSTICK_SRC
#define CONF_CLK_GEN_SYSTICK_SRC CLK_SRC_OPTION_MCKR
#endif

// </h>

// <h>

// <o> Systick clock divider
// <8=> 8
// <i> Select systick clock divider
// <id> systick_clock_div
#ifndef CONF_SYSTICK_DIV
#define CONF_SYSTICK_DIV 8
#endif

// </h>
// </e>// <e> Clock_FCLK configuration
// <i> Indicates whether FCLK configuration is enabled or not
// <id> enable_clk_gen_fclk
#ifndef CONF_CLK_FCLK_CONFIG
#define CONF_CLK_FCLK_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator FCLK source

// <CLK_SRC_OPTION_MCKR"> Master Clock Controller (PMC_MCKR)

// <i> This defines the clock source for FCLK
// <id> clk_gen_fclk_oscillator
#ifndef CONF_CLK_GEN_FCLK_SRC
#define CONF_CLK_GEN_FCLK_SRC CLK_SRC_OPTION_MCKR
#endif

// </h>

// <h>

// </h>
// </e>// <e> Clock_GCLK0 configuration
// <i> Indicates whether GCLK0 configuration is enabled or not
// <id> enable_clk_gen_gclk0
#ifndef CONF_CLK_GCLK0_CONFIG
#define CONF_CLK_GCLK0_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator GCLK0 source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <CLK_SRC_OPTION_MAINCK"> Main Clock (MAINCK)

// <CLK_SRC_OPTION_UPLLCK"> USB 480M Clock (UPLLCK)

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_MCK"> Master Clock (MCK)

// <i> This defines the clock source for GCLK0
// <id> clk_gen_gclk0_oscillator
#ifndef CONF_CLK_GEN_GCLK0_SRC
#define CONF_CLK_GEN_GCLK0_SRC CLK_SRC_OPTION_MCK
#endif

// <q> Enable Clock_GCLK0
// <i> Indicates whether GCLK0 is enabled or disable
// <id> clk_gen_gclk0_arch_enable
#ifndef CONF_CLK_GCLK0_ENABLE
#define CONF_CLK_GCLK0_ENABLE 1
#endif

// </h>

// <h>
// <q> Enable GCLK0 GCLKEN
// <i> Indicates whether GCLK0 GCLKEN is enabled or disable
// <id> gclk0_gclken_enable
#ifndef CONF_GCLK0_GCLKEN_ENABLE
#define CONF_GCLK0_GCLKEN_ENABLE 0
#endif

// <o> Generic Clock GCLK0 divider <1-256>
// <i> Select the clock divider (divider = GCLKDIV + 1).
// <id> gclk0_div
#ifndef CONF_GCLK0_DIV
#define CONF_GCLK0_DIV 2
#endif

// </h>
// </e>// <e> Clock_GCLK1 configuration
// <i> Indicates whether GCLK1 configuration is enabled or not
// <id> enable_clk_gen_gclk1
#ifndef CONF_CLK_GCLK1_CONFIG
#define CONF_CLK_GCLK1_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator GCLK1 source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <CLK_SRC_OPTION_MAINCK"> Main Clock (MAINCK)

// <CLK_SRC_OPTION_UPLLCK"> USB 480M Clock (UPLLCK)

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_MCK"> Master Clock (MCK)

// <i> This defines the clock source for GCLK1
// <id> clk_gen_gclk1_oscillator
#ifndef CONF_CLK_GEN_GCLK1_SRC
#define CONF_CLK_GEN_GCLK1_SRC CLK_SRC_OPTION_PLLACK
#endif

// <q> Enable Clock_GCLK1
// <i> Indicates whether GCLK1 is enabled or disable
// <id> clk_gen_gclk1_arch_enable
#ifndef CONF_CLK_GCLK1_ENABLE
#define CONF_CLK_GCLK1_ENABLE 1
#endif

// </h>

// <h>
// <q> Enable GCLK1 GCLKEN
// <i> Indicates whether GCLK1 GCLKEN is enabled or disable
// <id> gclk1_gclken_enable
#ifndef CONF_GCLK1_GCLKEN_ENABLE
#define CONF_GCLK1_GCLKEN_ENABLE 0
#endif

// <o> Generic Clock GCLK1 divider <1-256>
// <i> Select the clock divider (divider = GCLKDIV + 1).
// <id> gclk1_div
#ifndef CONF_GCLK1_DIV
#define CONF_GCLK1_DIV 3
#endif

// </h>
// </e>// <e> Clock_PCK0 configuration
// <i> Indicates whether PCK0 configuration is enabled or not
// <id> enable_clk_gen_pck0
#ifndef CONF_CLK_PCK0_CONFIG
#define CONF_CLK_PCK0_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator PCK0 source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <CLK_SRC_OPTION_MAINCK"> Main Clock (MAINCK)

// <CLK_SRC_OPTION_UPLLCKDIV"> UDPLL with Divider (MCKR UPLLDIV2)

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_MCK"> Master Clock (MCK)

// <i> This defines the clock source for PCK0
// <id> clk_gen_pck0_oscillator
#ifndef CONF_CLK_GEN_PCK0_SRC
#define CONF_CLK_GEN_PCK0_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> Enable Clock_PCK0
// <i> Indicates whether PCK0 is enabled or disable
// <id> clk_gen_pck0_arch_enable
#ifndef CONF_CLK_PCK0_ENABLE
#define CONF_CLK_PCK0_ENABLE 0
#endif

// </h>

// <h>

// <o> Programmable Clock Controller Prescaler <1-256>
// <i> Select the clock prescaler (prescaler = PRESC + 1).
// <id> pck0_presc
#ifndef CONF_PCK0_PRESC
#define CONF_PCK0_PRESC 1
#endif

// </h>
// </e>// <e> Clock_PCK1 configuration
// <i> Indicates whether PCK1 configuration is enabled or not
// <id> enable_clk_gen_pck1
#ifndef CONF_CLK_PCK1_CONFIG
#define CONF_CLK_PCK1_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator PCK1 source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <CLK_SRC_OPTION_MAINCK"> Main Clock (MAINCK)

// <CLK_SRC_OPTION_UPLLCKDIV"> UDPLL with Divider (MCKR UPLLDIV2)

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_MCK"> Master Clock (MCK)

// <i> This defines the clock source for PCK1
// <id> clk_gen_pck1_oscillator
#ifndef CONF_CLK_GEN_PCK1_SRC
#define CONF_CLK_GEN_PCK1_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> Enable Clock_PCK1
// <i> Indicates whether PCK1 is enabled or disable
// <id> clk_gen_pck1_arch_enable
#ifndef CONF_CLK_PCK1_ENABLE
#define CONF_CLK_PCK1_ENABLE 0
#endif

// </h>

// <h>

// <o> Programmable Clock Controller Prescaler <1-256>
// <i> Select the clock prescaler (prescaler = PRESC + 1).
// <id> pck1_presc
#ifndef CONF_PCK1_PRESC
#define CONF_PCK1_PRESC 2
#endif

// </h>
// </e>// <e> Clock_PCK2 configuration
// <i> Indicates whether PCK2 configuration is enabled or not
// <id> enable_clk_gen_pck2
#ifndef CONF_CLK_PCK2_CONFIG
#define CONF_CLK_PCK2_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator PCK2 source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <CLK_SRC_OPTION_MAINCK"> Main Clock (MAINCK)

// <CLK_SRC_OPTION_UPLLCKDIV"> UDPLL with Divider (MCKR UPLLDIV2)

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_MCK"> Master Clock (MCK)

// <i> This defines the clock source for PCK2
// <id> clk_gen_pck2_oscillator
#ifndef CONF_CLK_GEN_PCK2_SRC
#define CONF_CLK_GEN_PCK2_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> Enable Clock_PCK2
// <i> Indicates whether PCK2 is enabled or disable
// <id> clk_gen_pck2_arch_enable
#ifndef CONF_CLK_PCK2_ENABLE
#define CONF_CLK_PCK2_ENABLE 0
#endif

// </h>

// <h>

// <o> Programmable Clock Controller Prescaler <1-256>
// <i> Select the clock prescaler (prescaler = PRESC + 1).
// <id> pck2_presc
#ifndef CONF_PCK2_PRESC
#define CONF_PCK2_PRESC 3
#endif

// </h>
// </e>// <e> Clock_PCK3 configuration
// <i> Indicates whether PCK3 configuration is enabled or not
// <id> enable_clk_gen_pck3
#ifndef CONF_CLK_PCK3_CONFIG
#define CONF_CLK_PCK3_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator PCK3 source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <CLK_SRC_OPTION_MAINCK"> Main Clock (MAINCK)

// <CLK_SRC_OPTION_UPLLCKDIV"> UDPLL with Divider (MCKR UPLLDIV2)

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_MCK"> Master Clock (MCK)

// <i> This defines the clock source for PCK3
// <id> clk_gen_pck3_oscillator
#ifndef CONF_CLK_GEN_PCK3_SRC
#define CONF_CLK_GEN_PCK3_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> Enable Clock_PCK3
// <i> Indicates whether PCK3 is enabled or disable
// <id> clk_gen_pck3_arch_enable
#ifndef CONF_CLK_PCK3_ENABLE
#define CONF_CLK_PCK3_ENABLE 0
#endif

// </h>

// <h>

// <o> Programmable Clock Controller Prescaler <1-256>
// <i> Select the clock prescaler (prescaler = PRESC + 1).
// <id> pck3_presc
#ifndef CONF_PCK3_PRESC
#define CONF_PCK3_PRESC 4
#endif

// </h>
// </e>// <e> Clock_PCK4 configuration
// <i> Indicates whether PCK4 configuration is enabled or not
// <id> enable_clk_gen_pck4
#ifndef CONF_CLK_PCK4_CONFIG
#define CONF_CLK_PCK4_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator PCK4 source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <CLK_SRC_OPTION_MAINCK"> Main Clock (MAINCK)

// <CLK_SRC_OPTION_UPLLCKDIV"> UDPLL with Divider (MCKR UPLLDIV2)

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_MCK"> Master Clock (MCK)

// <i> This defines the clock source for PCK4
// <id> clk_gen_pck4_oscillator
#ifndef CONF_CLK_GEN_PCK4_SRC
#define CONF_CLK_GEN_PCK4_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> Enable Clock_PCK4
// <i> Indicates whether PCK4 is enabled or disable
// <id> clk_gen_pck4_arch_enable
#ifndef CONF_CLK_PCK4_ENABLE
#define CONF_CLK_PCK4_ENABLE 0
#endif

// </h>

// <h>

// <o> Programmable Clock Controller Prescaler <1-256>
// <i> Select the clock prescaler (prescaler = PRESC + 1).
// <id> pck4_presc
#ifndef CONF_PCK4_PRESC
#define CONF_PCK4_PRESC 5
#endif

// </h>
// </e>// <e> Clock_PCK5 configuration
// <i> Indicates whether PCK5 configuration is enabled or not
// <id> enable_clk_gen_pck5
#ifndef CONF_CLK_PCK5_CONFIG
#define CONF_CLK_PCK5_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator PCK5 source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <CLK_SRC_OPTION_MAINCK"> Main Clock (MAINCK)

// <CLK_SRC_OPTION_UPLLCKDIV"> UDPLL with Divider (MCKR UPLLDIV2)

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_MCK"> Master Clock (MCK)

// <i> This defines the clock source for PCK5
// <id> clk_gen_pck5_oscillator
#ifndef CONF_CLK_GEN_PCK5_SRC
#define CONF_CLK_GEN_PCK5_SRC CLK_SRC_OPTION_UPLLCKDIV
#endif

// <q> Enable Clock_PCK5
// <i> Indicates whether PCK5 is enabled or disable
// <id> clk_gen_pck5_arch_enable
#ifndef CONF_CLK_PCK5_ENABLE
#define CONF_CLK_PCK5_ENABLE 1
#endif

// </h>

// <h>

// <o> Programmable Clock Controller Prescaler <1-256>
// <i> Select the clock prescaler (prescaler = PRESC + 1).
// <id> pck5_presc
#ifndef CONF_PCK5_PRESC
#define CONF_PCK5_PRESC 6
#endif

// </h>
// </e>// <e> Clock_PCK6 configuration
// <i> Indicates whether PCK6 configuration is enabled or not
// <id> enable_clk_gen_pck6
#ifndef CONF_CLK_PCK6_CONFIG
#define CONF_CLK_PCK6_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator PCK6 source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <CLK_SRC_OPTION_MAINCK"> Main Clock (MAINCK)

// <CLK_SRC_OPTION_UPLLCKDIV"> UDPLL with Divider (MCKR UPLLDIV2)

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_MCK"> Master Clock (MCK)

// <i> This defines the clock source for PCK6
// <id> clk_gen_pck6_oscillator
#ifndef CONF_CLK_GEN_PCK6_SRC
#define CONF_CLK_GEN_PCK6_SRC CLK_SRC_OPTION_MAINCK
#endif

// <q> Enable Clock_PCK6
// <i> Indicates whether PCK6 is enabled or disable
// <id> clk_gen_pck6_arch_enable
#ifndef CONF_CLK_PCK6_ENABLE
#define CONF_CLK_PCK6_ENABLE 0
#endif

// </h>

// <h>

// <o> Programmable Clock Controller Prescaler <1-256>
// <i> Select the clock prescaler (prescaler = PRESC + 1).
// <id> pck6_presc
#ifndef CONF_PCK6_PRESC
#define CONF_PCK6_PRESC 7
#endif

// </h>
// </e>// <e> Clock_USB_480M configuration
// <i> Indicates whether USB_480M configuration is enabled or not
// <id> enable_clk_gen_usb_480m
#ifndef CONF_CLK_USB_480M_CONFIG
#define CONF_CLK_USB_480M_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator USB_480M source

// <CLK_SRC_OPTION_UPLLCK"> USB 480M Clock (UPLLCK)

// <i> This defines the clock source for USB_480M
// <id> clk_gen_usb_480m_oscillator
#ifndef CONF_CLK_GEN_USB_480M_SRC
#define CONF_CLK_GEN_USB_480M_SRC CLK_SRC_OPTION_UPLLCK
#endif

// </h>

// <h>

// </h>
// </e>// <e> Clock_USB_48M configuration
// <i> Indicates whether USB_48M configuration is enabled or not
// <id> enable_clk_gen_usb_48m
#ifndef CONF_CLK_USB_48M_CONFIG
#define CONF_CLK_USB_48M_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator USB_48M source

// <CLK_SRC_OPTION_PLLACK"> PLLA Clock (PLLACK)

// <CLK_SRC_OPTION_UPLLCKDIV"> UDPLL with Divider (MCKR UPLLDIV2)

// <i> This defines the clock source for USB_48M
// <id> clk_gen_usb_48m_oscillator
#ifndef CONF_CLK_GEN_USB_48M_SRC
#define CONF_CLK_GEN_USB_48M_SRC CLK_SRC_OPTION_PLLACK
#endif

// <q> Enable Clock_USB_48M
// <i> Indicates whether USB_48M is enabled or disable
// <id> clk_gen_usb_48m_arch_enable
#ifndef CONF_CLK_USB_48M_ENABLE
#define CONF_CLK_USB_48M_ENABLE 0
#endif

// </h>

// <h>

// <o> USB Clock Controller Divider <1-16>
// <i> Select the USB clock divider (divider = USBDIV + 1).
// <id> usb_48m_div
#ifndef CONF_USB_48M_DIV
#define CONF_USB_48M_DIV 1
#endif

// </h>
// </e>// <e> Clock_SLCK2 configuration
// <i> Indicates whether SLCK2 configuration is enabled or not
// <id> enable_clk_gen_slck2
#ifndef CONF_CLK_SLCK2_CONFIG
#define CONF_CLK_SLCK2_CONFIG 1
#endif

//<h> Clock Generator
// <y> clock generator SLCK2 source

// <CLK_SRC_OPTION_SLCK"> Slow Clock (SLCK)

// <i> This defines the clock source for SLCK2
// <id> clk_gen_slck2_oscillator
#ifndef CONF_CLK_GEN_SLCK2_SRC
#define CONF_CLK_GEN_SLCK2_SRC CLK_SRC_OPTION_SLCK
#endif

// </h>

// <h>

// </h>
// </e>

// <e> System Configuration
// <i> Indicates whether configuration for system is enabled or not
// <id> enable_hclk_clock
#ifndef CONF_SYSTEM_CONFIG
#define CONF_SYSTEM_CONFIG 1
#endif

// <h> Processor Clock Settings
// <y> Processor Clock source
// <MCKR"> Master Clock Controller (PMC_MCKR)
// <i> This defines the clock source for the HCLK (Processor clock)
// <id> hclk_clock_source
#ifndef CONF_HCLK_SRC
#define CONF_HCLK_SRC MCKR
#endif

// <o> Flash Wait State
// <0=> 1 cycle
// <1=> 2 cycles
// <2=> 3 cycles
// <3=> 4 cycles
// <4=> 5 cycles
// <5=> 6 cycles
// <6=> 7 cycles
// <i> This field defines the number of wait states for read and write operations.
// <id> efc_fws
#ifndef CONF_EFC_WAIT_STATE
#define CONF_EFC_WAIT_STATE 5
#endif

// </h>
// </e>

// <e> SysTick Clock
// <id> enable_systick_clk_clock
#ifndef CONF_SYSTICK_CLK_CONFIG
#define CONF_SYSTICK_CLK_CONFIG 1
#endif

// <y> SysTick Clock source
// <MCKR"> Master Clock Controller (PMC_MCKR)
// <i> This defines the clock source for the SysTick Clock
// <id> systick_clk_clock_source
#ifndef CONF_SYSTICK_CLK_SRC
#define CONF_SYSTICK_CLK_SRC MCKR
#endif

// <o> SysTick Clock Divider
// <8=> 8
// <i> Fixed to 8 if Systick is not using Processor clock
// <id> systick_clk_clock_div
#ifndef CONF_SYSTICK_CLK_DIV
#define CONF_SYSTICK_CLK_DIV 8
#endif

// </e>

// <e> OSC32K Oscillator Configuration
// <i> Indicates whether configuration for OSC32K is enabled or not
// <id> enable_osc32k
#ifndef CONF_OSC32K_CONFIG
#define CONF_OSC32K_CONFIG 1
#endif

// <h> OSC32K Oscillator Control
// <q> OSC32K Oscillator Enable
// <i> Indicates whether OSC32K Oscillator is enabled or not
// <id> osc32k_arch_enable
#ifndef CONF_OSC32K_ENABLE
#define CONF_OSC32K_ENABLE 0
#endif
// </h>
// </e>

// <e> XOSC32K Oscillator Configuration
// <i> Indicates whether configuration for XOSC32K is enabled or not
// <id> enable_xosc32k
#ifndef CONF_XOSC32K_CONFIG
#define CONF_XOSC32K_CONFIG 0
#endif

// <h> XOSC32K Oscillator Control
// <y> Oscillator Bypass Select
// <CONF_XOSC32K_NO_BYPASS"> The 32kHz crystal oscillator is not bypassed.
// <CONF_XOSC32K_BYPASS"> The 32kHz crystal oscillator is bypassed.
// <i> Indicates whether XOSC32K is bypassed.
// <id> xosc32k_bypass
#ifndef CONF_XOSC32K
#define CONF_XOSC32K CONF_XOSC32K_NO_BYPASS
#endif

// <q> XOSC32K Oscillator Enable
// <i> Indicates whether XOSC32K Oscillator is enabled or not
// <id> xosc32k_arch_enable
#ifndef CONF_XOSC32K_ENABLE
#define CONF_XOSC32K_ENABLE 0
#endif
// </h>
// </e>

// <e> OSC12M Oscillator Configuration
// <i> Indicates whether configuration for OSC12M is enabled or not
// <id> enable_osc12m
#ifndef CONF_OSC12M_CONFIG
#define CONF_OSC12M_CONFIG 0
#endif

// <h> OSC12M Oscillator Control
// <q> OSC12M Oscillator Enable
// <i> Indicates whether OSC12M Oscillator is enabled or not.
// <id> osc12m_arch_enable
#ifndef CONF_OSC12M_ENABLE
#define CONF_OSC12M_ENABLE 0
#endif

// <o> OSC12M selector
//  <0=> 4000000
//  <1=> 8000000
//  <2=> 12000000
// <i> Select the frequency of embedded fast RC oscillator.
// <id> osc12m_selector
#ifndef CONF_OSC12M_SELECTOR
#define CONF_OSC12M_SELECTOR 2
#endif
// </h>
// </e>

// <e> XOSC20M Oscillator Configuration
// <i> Indicates whether configuration for XOSC20M is enabled or not.
// <id> enable_xosc20m
#ifndef CONF_XOSC20M_CONFIG
#define CONF_XOSC20M_CONFIG 1
#endif

// <h> XOSC20M Oscillator Control
// <o> XOSC20M selector <3000000-20000000>
// <i> Select the frequency of crystal or ceramic resonator oscillator.
// <id> xosc20m_selector
#ifndef CONF_XOSC20M_SELECTOR
#define CONF_XOSC20M_SELECTOR 12000000
#endif

// <o> Start up time for the external oscillator (ms): <0-256>
// <i> Select start-up time.
// <id> xosc20m_startup_time
#ifndef CONF_XOSC20M_STARTUP_TIME
#define CONF_XOSC20M_STARTUP_TIME 62
#endif

// <y> Oscillator Bypass Select
// <CONF_XOSC20M_NO_BYPASS"> The external crystal oscillator is not bypassed.
// <CONF_XOSC20M_BYPASS"> The external crystal oscillator is bypassed.
// <i> Indicates whether XOSC20M is bypassed.
// <id> xosc20m_bypass
#ifndef CONF_XOSC20M
#define CONF_XOSC20M CONF_XOSC20M_NO_BYPASS
#endif

// <q> XOSC20M Oscillator Enable
// <i> Indicates whether XOSC20M Oscillator is enabled or not
// <id> xosc20m_arch_enable
#ifndef CONF_XOSC20M_ENABLE
#define CONF_XOSC20M_ENABLE 1
#endif
// </h>
// </e>

// <e> PLLACK Oscillator Configuration
// <i> Indicates whether configuration for PLLACK is enabled or not
// <id> enable_pllack
#ifndef CONF_PLLACK_CONFIG
#define CONF_PLLACK_CONFIG 1
#endif

// <y> PLLACK Reference Clock Source
// <MAINCK"> Main Clock (MAINCK)
// <i> Select the clock source.
// <id> pllack_ref_clock
#ifndef CONF_PLLACK_CLK
#define CONF_PLLACK_CLK MAINCK
#endif

// <h> PLLACK Oscillator Control
// <q> PLLACK Oscillator Enable
// <i> Indicates whether PLLACK Oscillator is enabled or not
// <id> pllack_arch_enable
#ifndef CONF_PLLACK_ENABLE
#define CONF_PLLACK_ENABLE 1
#endif

// <o> PLLA Frontend Divider (DIVA)  <1-255>
// <i> Select the clock divider
// <id> pllack_div
#ifndef CONF_PLLACK_DIV
#define CONF_PLLACK_DIV 1
#endif

// <o> PLLACK Muliplier <1-62>
// <i> Indicates PLLA multiplier (multiplier = MULA + 1).
// <id> pllack_mul
#ifndef CONF_PLLACK_MUL
#define CONF_PLLACK_MUL 25
#endif
// </h>
// </e>

// <e> UPLLCK Oscillator Configuration
// <i> Indicates whether configuration for UPLLCK is enabled or not
// <id> enable_upllck
#ifndef CONF_UPLLCK_CONFIG
#define CONF_UPLLCK_CONFIG 1
#endif

// <y> UPLLCK Reference Clock Source
// <XOSC20M"> External 3-20MHz Oscillator (XOSC20M)
// <i> Select the clock source,only when the input frequency is 12M or 16M, the upllck output is 480M.
// <id> upllck_ref_clock
#ifndef CONF_UPLLCK_CLK
#define CONF_UPLLCK_CLK XOSC20M
#endif

// <h> UPLLCK Oscillator Control
// <q> UPLLCK Oscillator Enable
// <i> Indicates whether UPLLCK Oscillator is enabled or not
// <id> upllck_arch_enable
#ifndef CONF_UPLLCK_ENABLE
#define CONF_UPLLCK_ENABLE 1
#endif
// </h>
// </e>

// <e> UPLLCKDIV Oscillator Configuration
// <i> Indicates whether configuration for UPLLCKDIV is enabled or not
// <id> enable_upllckdiv
#ifndef CONF_UPLLCKDIV_CONFIG
#define CONF_UPLLCKDIV_CONFIG 1
#endif

// <y> UPLLCKDIV Reference Clock Source
// <UPLLCK"> USB 480M Clock (UPLLCK)
// <i> Select the clock source.
// <id> upllckdiv_ref_clock
#ifndef CONF_UPLLCKDIV_CLK
#define CONF_UPLLCKDIV_CLK UPLLCK
#endif

// <h> UPLLCKDIV Oscillator Control
// <o> UPLLCKDIV Clock Divider
// <0=> 1
// <1=> 2
// <i> Select the clock divider.
// <id> upllckdiv_div
#ifndef CONF_UPLLCKDIV_DIV
#define CONF_UPLLCKDIV_DIV 1
#endif
// </h>
// </e>

// <e> MCK/8
// <id> enable_mck_div_8
#ifndef CONF_MCK_DIV_8_CONFIG
#define CONF_MCK_DIV_8_CONFIG 0
#endif

// <o> MCK/8 Source
// <0=> Master Clock (MCK)
// <id> mck_div_8_src
#ifndef CONF_MCK_DIV_8_SRC
#define CONF_MCK_DIV_8_SRC 0
#endif
// </e>

// <e> External Clock Input Configuration
// <id> enable_dummy_ext
#ifndef CONF_DUMMY_EXT_CONFIG
#define CONF_DUMMY_EXT_CONFIG 1
#endif

// <o> External Clock Input Source
// <i> All here are dummy values
// <i> Refer to the peripherals settings for actual input information
// <0=> Specific clock input from specific pin
// <id> dummy_ext_src
#ifndef CONF_DUMMY_EXT_SRC
#define CONF_DUMMY_EXT_SRC 0
#endif
// </e>

// <e> External Clock Configuration
// <id> enable_dummy_ext_clk
#ifndef CONF_DUMMY_EXT_CLK_CONFIG
#define CONF_DUMMY_EXT_CLK_CONFIG 1
#endif

// <o> External Clock Source
// <i> All here are dummy values
// <i> Refer to the peripherals settings for actual input information
// <0=> External Clock Input
// <id> dummy_ext_clk_src
#ifndef CONF_DUMMY_EXT_CLK_SRC
#define CONF_DUMMY_EXT_CLK_SRC 0
#endif
// </e>

// <<< end of configuration section >>>

#endif // HPL_PMC_CONFIG_H
