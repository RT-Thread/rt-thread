/* Auto-generated config file hpl_mclk_config.h */
#ifndef HPL_MCLK_CONFIG_H
#define HPL_MCLK_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

#include <peripheral_clk_config.h>

// <e> System Configuration
// <i> Indicates whether configuration for system is enabled or not
// <id> enable_cpu_clock
#ifndef CONF_SYSTEM_CONFIG
#define CONF_SYSTEM_CONFIG 1
#endif

// <h> Basic settings
// <y> CPU Clock source
// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0
// <MCLK_CTRLA_CKSEL"> DFLLULP clock
// <i> This defines the clock source for the CPU
// <id> cpu_clock_source
#ifndef CONF_CPU_SRC
#define CONF_CPU_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

// <y> CPU Clock Division Factor
// <MCLK_CPUDIV_CPUDIV_DIV1_Val"> 1
// <MCLK_CPUDIV_CPUDIV_DIV2_Val"> 2
// <MCLK_CPUDIV_CPUDIV_DIV4_Val"> 4
// <MCLK_CPUDIV_CPUDIV_DIV8_Val"> 8
// <MCLK_CPUDIV_CPUDIV_DIV16_Val"> 16
// <MCLK_CPUDIV_CPUDIV_DIV32_Val"> 32
// <MCLK_CPUDIV_CPUDIV_DIV64_Val"> 64
// <MCLK_CPUDIV_CPUDIV_DIV128_Val"> 128
// <i> Prescalar for CPU clock
// <id> cpu_div
#ifndef CONF_MCLK_CPUDIV
#define CONF_MCLK_CPUDIV MCLK_CPUDIV_CPUDIV_DIV1_Val
#endif

// </h>

// <h> Performance Level (PL) Settings
// <o> Performance Level
// <i> Select the performance level (PL)
// <i> Performance Level 0 (PL0) provides the maximum energy efficiency configuration.
// <i> Performance level 2 (PL2) provides the maximum operating frequency.
// <0=> Performance Level 0 (PL0)
// <2=> Performance Level 2 (PL2)
// <id> performance_level
#ifndef CONF_PERFORMANCE_LEVEL
#define CONF_PERFORMANCE_LEVEL 0
#endif
// </h>

// <h> NVM Settings
// <o> NVM Wait States
// <i> These bits select the number of wait states for a read operation.
// <0=> 0
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7
// <8=> 8
// <9=> 9
// <10=> 10
// <11=> 11
// <12=> 12
// <13=> 13
// <14=> 14
// <15=> 15
// <id> nvm_wait_states
#ifndef CONF_NVM_WAIT_STATE
#define CONF_NVM_WAIT_STATE 3
#endif

// </h>

// </e>

// <<< end of configuration section >>>

#endif // HPL_MCLK_CONFIG_H
