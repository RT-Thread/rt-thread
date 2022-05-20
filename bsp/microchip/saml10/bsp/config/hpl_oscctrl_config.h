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

// <o> Oscillator Gain
// <i> The listed maximum frequencies are recommendations
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

// <e> 16MHz Internal Oscillator Configuration
// <i> Indicates whether configuration for OSC8M is enabled or not
// <id> enable_osc16m
#ifndef CONF_OSC16M_CONFIG
#define CONF_OSC16M_CONFIG 1
#endif

// <h> 16MHz Internal Oscillator Control
// <q> Enable
// <i> Indicates whether 16MHz Internal Oscillator is enabled or not
// <id> osc16m_arch_enable
#ifndef CONF_OSC16M_ENABLE
#define CONF_OSC16M_ENABLE 1
#endif

// <q> On Demand Control
// <i> Indicates whether On Demand Control is enabled or not
// <id> osc16m_arch_ondemand
#ifndef CONF_OSC16M_ONDEMAND
#define CONF_OSC16M_ONDEMAND 1
#endif

// <q> Run in Standby
// <i> Indicates whether Run in Standby is enabled or not
// <id> osc16m_arch_runstdby
#ifndef CONF_OSC16M_RUNSTDBY
#define CONF_OSC16M_RUNSTDBY 0
#endif

// <y> Oscillator Frequency Selection(Mhz)
// <OSCCTRL_OSC16MCTRL_FSEL_4_Val"> 4
// <OSCCTRL_OSC16MCTRL_FSEL_8_Val"> 8
// <OSCCTRL_OSC16MCTRL_FSEL_12_Val"> 12
// <OSCCTRL_OSC16MCTRL_FSEL_16_Val"> 16
// <i> This defines the oscillator frequency (Mhz)
// <id> osc16m_freq
#ifndef CONF_OSC16M_FSEL
#define CONF_OSC16M_FSEL OSCCTRL_OSC16MCTRL_FSEL_4_Val
#endif

//</h>
//</e>

// <e> DFLL Configuration
// <i> Indicates whether configuration for DFLL is enabled or not
// <id> enable_dfllulp
#ifndef CONF_DFLL_CONFIG
#define CONF_DFLL_CONFIG 1
#endif

// <y> Reference Clock Source
// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0
// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1
// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2
// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3
// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4
// <i> Select the clock source.
// <id> dfllulp_ref_clock
#ifndef CONF_DFLL_GCLK
#define CONF_DFLL_GCLK GCLK_PCHCTRL_GEN_GCLK1_Val
#endif

// <h> Digital Frequency Locked Loop Control
// <q> DFLL Enable
// <i> Indicates whether DFLL is enabled or not
// <id> dfllulp_arch_enable
#ifndef CONF_DFLL_ENABLE
#define CONF_DFLL_ENABLE 1
#endif

// <q> On Demand Control
// <i> Indicates whether On Demand Control is enabled or not
// <id> dfllulp_arch_ondemand
#ifndef CONF_DFLL_ONDEMAND
#define CONF_DFLL_ONDEMAND 1
#endif

// <q> Run in Standby
// <i> Indicates whether Run in Standby is enabled or not
// <id> dfllulp_arch_runstdby
#ifndef CONF_DFLL_RUNSTDBY
#define CONF_DFLL_RUNSTDBY 0
#endif

// <q> Tuner Dither Mode
// <i> Indicates whether dither mode is enabled or not
// <id> dfllulp_arch_dither
#ifndef CONF_DFLL_DITHER
#define CONF_DFLL_DITHER 0
#endif

// <q> Tuner Safe Mode
// <i> Indicates whether tuner safe mode is enabled or not
// <id> dfllulp_arch_safe
#ifndef CONF_DFLL_SAFE
#define CONF_DFLL_SAFE 0
#endif

// <q> Binary Search Enable
// <i> Indicates whether binary search tuning is enabled or not
// <id> dfllulp_arch_binse
#ifndef CONF_DFLL_BINSE
#define CONF_DFLL_BINSE 0
#endif

// <y> Dither Period
// <OSCCTRL_DFLLULPDITHER_PER_PER1_Val"> Dither over 1 reference clock period
// <OSCCTRL_DFLLULPDITHER_PER_PER2_Val"> Dither over 2 reference clock period
// <OSCCTRL_DFLLULPDITHER_PER_PER4_Val"> Dither over 4 reference clock period
// <OSCCTRL_DFLLULPDITHER_PER_PER8_Val"> Dither over 8 reference clock period
// <OSCCTRL_DFLLULPDITHER_PER_PER16_Val"> Dither over 16 reference clock period
// <OSCCTRL_DFLLULPDITHER_PER_PER32_Val"> Dither over 32 reference clock period
// <i> Define the number of reference clock periods over which dithering is applied.
// <id> dfllulp_arch_dither_per
#ifndef CONF_DFLL_DITHER_PER
#define CONF_DFLL_DITHER_PER OSCCTRL_DFLLULPDITHER_PER_PER1_Val
#endif

// <y> Dither Step
// <OSCCTRL_DFLLULPDITHER_STEP_STEP1"> Dither step is 1
// <OSCCTRL_DFLLULPDITHER_STEP_STEP2"> Dither step is 2
// <OSCCTRL_DFLLULPDITHER_STEP_STEP4"> Dither step is 4
// <OSCCTRL_DFLLULPDITHER_STEP_STEP8"> Dither step is 8
// <i> Define the dithering step size.
// <id> dfllulp_arch_dither_step
#ifndef CONF_DFLL_DITHER_STEP
#define CONF_DFLL_DITHER_STEP OSCCTRL_DFLLULPDITHER_STEP_STEP1
#endif

// <o> Delay Value <0x0-0xFF>
// <i> Delay Value (0x0-0xFF)
// <id> dfllulp_arch_delay
#ifndef CONF_DFLL_DELAY
#define CONF_DFLL_DELAY (0x80)
#endif

// <o> Target Ratio Value <0x0-0x7FF>
// <i> Target Ratio Value (0x0-0x7FF)
// <id> dfllulp_arch_ratio
#ifndef CONF_DFLL_RATIO
#define CONF_DFLL_RATIO (0x80)
#endif

// <o> Operating Mode Selection
// <1=>Closed Loop Mode
// <id> dfllulp_mode
#ifndef CONF_DFLL_MODE
#define CONF_DFLL_MODE 1
#endif

//</h>
//</e>

// <e> DFLL as Main Clock Source Configuration
// <i> Indicates whether enable DFLLUPL as main clock source or not
// <id> enable_dfllulp_as_mclk_source
#ifndef CONF_ENABLE_DFLL_AS_MCLK_SOURCE
#define CONF_ENABLE_DFLL_AS_MCLK_SOURCE 0
#endif

// <y> DFLL Clock Source Selection
// <GCLK_GENCTRL_SRC_DFLLULP"> Digital Frequency Locked Loop (DFLLULP)
// <i> This defines the clock source for DFLL
// <id> dfllulp_source_oscillator
#ifndef CONF_DFLL_SRC
#define CONF_DFLL_SRC GCLK_GENCTRL_SRC_DFLLULP
#endif
//</e>

// <e> DPLL Configuration
// <i> Indicates whether configuration for DPLL is enabled or not
// <id> enable_fdpll96m
#ifndef CONF_DPLL_CONFIG
#define CONF_DPLL_CONFIG 1
#endif

// <y> Reference Clock Source
// <GCLK_GENCTRL_SRC_XOSC32K"> 32kHz External Crystal Oscillator (XOSC32K)
// <GCLK_GENCTRL_SRC_XOSC"> External Crystal Oscillator 0.4-32MHz (XOSC)
// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0
// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1
// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2
// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3
// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4
// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5
// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6
// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7
// <i> Select the clock source.
// <id> fdpll96m_ref_clock
#ifndef CONF_DPLL_GCLK
#define CONF_DPLL_GCLK GCLK_PCHCTRL_GEN_GCLK1_Val
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
#define CONF_DPLL_LDRFRAC 0x9
#endif

// <o> Loop Divider Ratio Integer Part <0x0-0xFFF>
// <i> Value of LDR is calculated using Fclk_dpll=Fckr*(LDR+1+LDRFRAC/16)/(2^presc) formula as given in datasheet. This value is directly written in to DPLLRATIO register
// <id> fdpll96m_ldr
#ifndef CONF_DPLL_LDR
#define CONF_DPLL_LDR 0x3cf
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

// <o> Reference Clock Selection
// <0=>XOSC32K clock reference
// <1=>XOSC clock reference
// <2=>GCLK clock reference
// <id> fdpll96m_arch_refclk
#ifndef CONF_DPLL_REFCLK
#define CONF_DPLL_REFCLK 0
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
// <0=>Default filter mode
// <1=>Low bandwidth filter
// <2=>High bandwidth filter
// <3=>High damping filter
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
