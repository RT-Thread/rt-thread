/* Auto-generated config file hpl_oscctrl_config.h */
#ifndef HPL_OSCCTRL_CONFIG_H
#define HPL_OSCCTRL_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <e> External Multipurpose Crystal Oscillator Configuration
// <i> Indicates whether configuration for XOSC is enabled or not
// <id> enable_xosc
#ifndef CONF_XOSC_CONFIG
#define CONF_XOSC_CONFIG 0
#endif

// <o> Frequency <400000-32000000>
// <i> Oscillation frequency of the resonator connected to the External Multipurpose Crystal Oscillator.
// <id> xosc_frequency
#ifndef CONF_XOSC_FREQUENCY
#define CONF_XOSC_FREQUENCY 400000
#endif

// <h> External Multipurpose Crystal Oscillator Control
// <q> Oscillator enable
// <i> Indicates whether External Multipurpose Crystal Oscillator is enabled or not
// <id> xosc_arch_enable
#ifndef CONF_XOSC_ENABLE
#define CONF_XOSC_ENABLE 0
#endif

// <o> Start-Up Time
// <0x0=>31us
// <0x1=>61us
// <0x2=>122us
// <0x3=>244us
// <0x4=>488us
// <0x5=>977us
// <0x6=>1953us
// <0x7=>3906us
// <0x8=>7813us
// <0x9=>15625us
// <0xA=>31250us
// <0xB=>62500us
// <0xC=>125000us
// <0xD=>250000us
// <0xE=>500000us
// <0xF=>1000000us
// <id> xosc_arch_startup
#ifndef CONF_XOSC_STARTUP
#define CONF_XOSC_STARTUP 0x0
#endif

// <q> Automatic Amplitude Gain Control
// <i> Indicates whether Automatic Amplitude Gain Control is enabled or not
// <id> xosc_arch_ampgc
#ifndef CONF_XOSC_AMPGC
#define CONF_XOSC_AMPGC 0
#endif

// <o> External Multipurpose Crystal Oscillator Gain
// <0x0=>2MHz
// <0x1=>4MHz
// <0x2=>8MHz
// <0x3=>16MHz
// <0x4=>30MHz
// <id> xosc_arch_gain
#ifndef CONF_XOSC_GAIN
#define CONF_XOSC_GAIN 0x0
#endif

// <q> On Demand Control
// <i> Indicates whether On Demand Control is enabled or not
// <id> xosc_arch_ondemand
#ifndef CONF_XOSC_ONDEMAND
#define CONF_XOSC_ONDEMAND 1
#endif

// <q> Run in Standby
// <i> Indicates whether Run in Standby is enabled or not
// <id> xosc_arch_runstdby
#ifndef CONF_XOSC_RUNSTDBY
#define CONF_XOSC_RUNSTDBY 0
#endif

// <q> Clock Switch Back
// <i> Indicates whether Clock Switch Back is enabled or not
// <id> xosc_arch_swben
#ifndef CONF_XOSC_SWBEN
#define CONF_XOSC_SWBEN 0
#endif

// <q> Clock Failure Detector
// <i> Indicates whether Clock Failure Detector is enabled or not
// <id> xosc_arch_cfden
#ifndef CONF_XOSC_CFDEN
#define CONF_XOSC_CFDEN 0
#endif

// <q> Clock Failure Detector Event Out
// <i> Indicates whether Clock Failure Detector Event Out is enabled or not
// <id> xosc_arch_cfdeo
#ifndef CONF_XOSC_CFDEO
#define CONF_XOSC_CFDEO 0
#endif

// <q> Crystal connected to XIN/XOUT Enable
// <i> Indicates whether the connections between the I/O pads and the external clock or crystal oscillator is enabled or not
// <id> xosc_arch_xtalen
#ifndef CONF_XOSC_XTALEN
#define CONF_XOSC_XTALEN 0
#endif
//</h>
//</e>

// <e> 48MHz Internal Oscillator Configuration
// <i> Indicates whether configuration for OSC48M is enabled or not
// <id> enable_osc48m
#ifndef CONF_OSC48M_CONFIG
#define CONF_OSC48M_CONFIG 1
#endif

// <h> 48MHz Internal Oscillator Control
// <q> Enable
// <i> Indicates whether 48MHz Internal Oscillator is enabled or not
// <id> osc48m_arch_enable
#ifndef CONF_OSC48M_ENABLE
#define CONF_OSC48M_ENABLE 1
#endif

// <q> On Demand Control
// <i> Indicates whether On Demand Control is enabled or not
// <id> osc48m_arch_ondemand
#ifndef CONF_OSC48M_ONDEMAND
#define CONF_OSC48M_ONDEMAND 1
#endif

// <q> Run in Standby
// <i> Indicates whether Run in Standby is enabled or not
// <id> osc48m_arch_runstdby
#ifndef CONF_OSC48M_RUNSTDBY
#define CONF_OSC48M_RUNSTDBY 0
#endif

// <o> Oscillator Division Selection <0x0-0xF>
// <i> Indicates OSC48M division value
// <id> osc48m_div
#ifndef CONF_OSC48M_DIV
#define CONF_OSC48M_DIV 11
#endif

// <o> Start-Up Time
// <0x0=> 166ns
// <0x1=> 333ns
// <0x2=> 667ns
// <0x3=> 1.333us
// <0x4=> 2.667us
// <0x5=> 5.333us
// <0x6=> 10.667us
// <0x7=> 21.333us
// <id> osc48m_arch_startup
#ifndef CONF_OSC48M_STARTUP
#define CONF_OSC48M_STARTUP 0x7
#endif

//</h>
//</e>

// <e> DPLL Configuration
// <i> Indicates whether configuration for DPLL is enabled or not
// <id> enable_fdpll96m
#ifndef CONF_DPLL_CONFIG
#define CONF_DPLL_CONFIG 1
#endif

#define CONF_OSCCTRL_DPLL_REFCLK_XOSC32K 0
#define CONF_OSCCTRL_DPLL_REFCLK_XOSC 1
#define CONF_OSCCTRL_DPLL_REFCLK_GCLK 2
#define CONF_OSCCTRL_DPLL_REFCLK_GCLK0 CONF_OSCCTRL_DPLL_REFCLK_GCLK
#define CONF_OSCCTRL_DPLL_REFCLK_GCLK1 3
#define CONF_OSCCTRL_DPLL_REFCLK_GCLK2 4
#define CONF_OSCCTRL_DPLL_REFCLK_GCLK3 5
#define CONF_OSCCTRL_DPLL_REFCLK_GCLK4 6
#define CONF_OSCCTRL_DPLL_REFCLK_GCLK5 7
#define CONF_OSCCTRL_DPLL_REFCLK_GCLK6 8
#define CONF_OSCCTRL_DPLL_REFCLK_GCLK7 9

// <y> Reference Clock Source
// <CONF_OSCCTRL_DPLL_REFCLK_XOSC32K"> 32kHz External Crystal Oscillator (XOSC32K)
// <CONF_OSCCTRL_DPLL_REFCLK_XOSC"> External Crystal Oscillator 0.4-32MHz (XOSC)
// <CONF_OSCCTRL_DPLL_REFCLK_GCLK0"> Generic clock generator 0
// <CONF_OSCCTRL_DPLL_REFCLK_GCLK1"> Generic clock generator 1
// <CONF_OSCCTRL_DPLL_REFCLK_GCLK2"> Generic clock generator 2
// <CONF_OSCCTRL_DPLL_REFCLK_GCLK3"> Generic clock generator 3
// <CONF_OSCCTRL_DPLL_REFCLK_GCLK4"> Generic clock generator 4
// <CONF_OSCCTRL_DPLL_REFCLK_GCLK5"> Generic clock generator 5
// <CONF_OSCCTRL_DPLL_REFCLK_GCLK6"> Generic clock generator 6
// <CONF_OSCCTRL_DPLL_REFCLK_GCLK7"> Generic clock generator 7
// <i> Select the clock source.
// <id> fdpll96m_ref_clock
#ifndef CONF_DPLL_REFCLK_VAL
#define CONF_DPLL_REFCLK_VAL CONF_OSCCTRL_DPLL_REFCLK_XOSC32K
#endif

#if (CONF_DPLL_REFCLK_VAL <= CONF_OSCCTRL_DPLL_REFCLK_GCLK0)
#define CONF_DPLL_REFCLK CONF_DPLL_REFCLK_VAL
#endif
#if (CONF_DPLL_REFCLK_VAL > CONF_OSCCTRL_DPLL_REFCLK_GCLK0)
#define CONF_DPLL_REFCLK CONF_OSCCTRL_DPLL_REFCLK_GCLK
#define CONF_DPLL_GCLK (CONF_DPLL_REFCLK_VAL - CONF_OSCCTRL_DPLL_REFCLK_GCLK0)
#endif

// <h> Digital Phase Locked Loop Control
// <q> Enable
// <i> Indicates whether Digital Phase Locked Loop is enabled or not
// <id> fdpll96m_arch_enable
#ifndef CONF_DPLL_ENABLE
#define CONF_DPLL_ENABLE 1
#endif

// <q> On Demand Control
// <i> Indicates whether On Demand Control is enabled or not
// <id> fdpll96m_arch_ondemand
#ifndef CONF_DPLL_ONDEMAND
#define CONF_DPLL_ONDEMAND 1
#endif

// <q> Run in Standby
// <i> Indicates whether Run in Standby is enabled or not
// <id> fdpll96m_arch_runstdby
#ifndef CONF_DPLL_RUNSTDBY
#define CONF_DPLL_RUNSTDBY 0
#endif

// <o> Loop Divider Ratio Fractional Part <0x0-0xF>
// <i> Value of LDRFRAC is calculated using Fclk_dpll=Fckr*(LDR+1+LDRFRAC/16)/(2^presc) formula as given in datasheet. This value is directly written in to DPLLRATIO register
// <id> fdpll96m_ldrfrac
#ifndef CONF_DPLL_LDRFRAC
#define CONF_DPLL_LDRFRAC 0xc
#endif

// <o> Loop Divider Ratio Integer Part <0x0-0xFFF>
// <i> Value of LDR is calculated using Fclk_dpll=Fckr*(LDR+1+LDRFRAC/16)/(2^presc) formula as given in datasheet. This value is directly written in to DPLLRATIO register
// <id> fdpll96m_ldr
#ifndef CONF_DPLL_LDR
#define CONF_DPLL_LDR 0x4c3
#endif

// <o> Clock Divider <0x0-0x3FF>
// <i> This Clock divider is only for XOSC clock input to DPLL
// <id> fdpll96m_clock_div
#ifndef CONF_DPLL_DIV
#define CONF_DPLL_DIV 0
#endif

// <q> Lock Bypass
// <i> Indicates whether Lock Bypass is enabled or not
// <id> fdpll96m_arch_lbypass
#ifndef CONF_DPLL_LBYPASS
#define CONF_DPLL_LBYPASS 0
#endif

// <o> Lock Time
// <0=>No time-out, automatic lock
// <4=>The Time-out if no lock within 8 ms
// <5=>The Time-out if no lock within 9 ms
// <6=>The Time-out if no lock within 10 ms
// <7=>The Time-out if no lock within 11 ms
// <id> fdpll96m_arch_ltime
#ifndef CONF_DPLL_LTIME
#define CONF_DPLL_LTIME 0
#endif

// <q> Wake Up Fast
// <i> Indicates whether Wake Up Fast is enabled or not
// <id> fdpll96m_arch_wuf
#ifndef CONF_DPLL_WUF
#define CONF_DPLL_WUF 0
#endif

// <q> Low-Power Enable
// <i> Indicates whether Low-Power Enable is enabled or not
// <id> fdpll96m_arch_lpen
#ifndef CONF_DPLL_LPEN
#define CONF_DPLL_LPEN 0
#endif

// <o> Reference Clock Selection
// <0x0=>Default filter mode
// <0x1=>Low bandwidth filter
// <0x2=>High bandwidth filter
// <0x3=>High damping filter
// <id> fdpll96m_arch_filter
#ifndef CONF_DPLL_FILTER
#define CONF_DPLL_FILTER 0
#endif

// <y> Output Clock Prescaler
// <OSCCTRL_DPLLPRESC_PRESC_DIV1_Val"> 1
// <OSCCTRL_DPLLPRESC_PRESC_DIV2_Val"> 2
// <OSCCTRL_DPLLPRESC_PRESC_DIV4_Val"> 4
// <id> fdpll96m_presc
#ifndef CONF_DPLL_PRESC
#define CONF_DPLL_PRESC OSCCTRL_DPLLPRESC_PRESC_DIV1_Val
#endif
//</h>
//</e>

// <<< end of configuration section >>>

#endif // HPL_OSCCTRL_CONFIG_H
