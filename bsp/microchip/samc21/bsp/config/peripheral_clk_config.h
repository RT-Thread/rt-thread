/* Auto-generated config file peripheral_clk_config.h */
#ifndef PERIPHERAL_CLK_CONFIG_H
#define PERIPHERAL_CLK_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <y> ADC Clock Source
// <id> adc_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <i> Select the clock source for ADC.
#ifndef CONF_GCLK_ADC0_SRC
#define CONF_GCLK_ADC0_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

/**
 * \def CONF_GCLK_ADC0_FREQUENCY
 * \brief ADC0's Clock frequency
 */
#ifndef CONF_GCLK_ADC0_FREQUENCY
#define CONF_GCLK_ADC0_FREQUENCY 40001536
#endif

/**
 * \def CONF_CPU_FREQUENCY
 * \brief CPU's Clock frequency
 */
#ifndef CONF_CPU_FREQUENCY
#define CONF_CPU_FREQUENCY 40001536
#endif

// <y> Core Clock Source
// <id> core_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <i> Select the clock source for CORE.
#ifndef CONF_GCLK_SERCOM0_CORE_SRC
#define CONF_GCLK_SERCOM0_CORE_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

// <y> Slow Clock Source
// <id> slow_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <i> Select the slow clock source.
#ifndef CONF_GCLK_SERCOM0_SLOW_SRC
#define CONF_GCLK_SERCOM0_SLOW_SRC GCLK_PCHCTRL_GEN_GCLK1_Val
#endif

/**
 * \def CONF_GCLK_SERCOM0_CORE_FREQUENCY
 * \brief SERCOM0's Core Clock frequency
 */
#ifndef CONF_GCLK_SERCOM0_CORE_FREQUENCY
#define CONF_GCLK_SERCOM0_CORE_FREQUENCY 40001536
#endif

/**
 * \def CONF_GCLK_SERCOM0_SLOW_FREQUENCY
 * \brief SERCOM0's Slow Clock frequency
 */
#ifndef CONF_GCLK_SERCOM0_SLOW_FREQUENCY
#define CONF_GCLK_SERCOM0_SLOW_FREQUENCY 4000000
#endif

// <y> Core Clock Source
// <id> core_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <i> Select the clock source for CORE.
#ifndef CONF_GCLK_SERCOM4_CORE_SRC
#define CONF_GCLK_SERCOM4_CORE_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

// <y> Slow Clock Source
// <id> slow_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <i> Select the slow clock source.
#ifndef CONF_GCLK_SERCOM4_SLOW_SRC
#define CONF_GCLK_SERCOM4_SLOW_SRC GCLK_PCHCTRL_GEN_GCLK1_Val
#endif

/**
 * \def CONF_GCLK_SERCOM4_CORE_FREQUENCY
 * \brief SERCOM4's Core Clock frequency
 */
#ifndef CONF_GCLK_SERCOM4_CORE_FREQUENCY
#define CONF_GCLK_SERCOM4_CORE_FREQUENCY 40001536
#endif

/**
 * \def CONF_GCLK_SERCOM4_SLOW_FREQUENCY
 * \brief SERCOM4's Slow Clock frequency
 */
#ifndef CONF_GCLK_SERCOM4_SLOW_FREQUENCY
#define CONF_GCLK_SERCOM4_SLOW_FREQUENCY 4000000
#endif

// <y> CAN0 Clock Source
// <id> can_gclk_selection

// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

// <i> Select the clock source for CAN0.
#ifndef CONF_GCLK_CAN0_SRC
#define CONF_GCLK_CAN0_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

/**
 * \def CONF_GCLK_CAN0_FREQUENCY
 * \brief CAN0's Clock frequency
 */
#ifndef CONF_GCLK_CAN0_FREQUENCY
#define CONF_GCLK_CAN0_FREQUENCY 40001536
#endif

// <<< end of configuration section >>>

#endif // PERIPHERAL_CLK_CONFIG_H
