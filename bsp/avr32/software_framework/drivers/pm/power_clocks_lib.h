/*****************************************************************************
 *
 * \file
 *
 * \brief High-level library abstracting features such as oscillators/pll/dfll
 *        configuration, clock configuration, System-sensible parameters
 *        configuration, buses clocks configuration, sleep mode, reset.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 *****************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef _POWER_CLOCKS_LIB_H_
#define _POWER_CLOCKS_LIB_H_

/**
 * \defgroup group_avr32_drivers_pm_power_clocks_lib Power Clocks Library
 * \ingroup group_avr32_drivers_pm
 *
 * \{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <avr32/io.h>
#include "compiler.h"

#ifndef AVR32_PM_VERSION_RESETVALUE
// Support for UC3A, UC3A3, UC3B parts.
  #include "pm.h"
#else
//! Device-specific data
#if UC3L
  #include "pm_uc3l.h"
  #include "scif_uc3l.h"
  #include "flashcdw.h"
#elif UC3C
  #include "pm_uc3c.h"
  #include "scif_uc3c.h"
  #include "flashc.h"
#elif UC3D
  #include "pm_uc3d.h"
  #include "scif_uc3d.h"
  #include "flashcdw.h"
#endif
  #endif

/*! \name Clocks Management
 */
//! @{

//! The different oscillators
typedef enum
{
  PCL_OSC0  = 0,
  PCL_OSC1  = 1
} pcl_osc_t;

//! The different DFLLs
typedef enum
{
  PCL_DFLL0  = 0,
  PCL_DFLL1  = 1
} pcl_dfll_t;

//! Possible Main Clock Sources
typedef enum
{
  PCL_MC_RCSYS,      // Default main clock source, supported by all (aka Slow Clock)
  PCL_MC_OSC0,       // Supported by all
  PCL_MC_OSC1,       // Supported by UC3C only
  PCL_MC_OSC0_PLL0,  // Supported by UC3A, UC3B, UC3A3, UC3C (the main clock source is PLL0 with OSC0 as reference)
  PCL_MC_OSC1_PLL0,  // Supported by UC3A, UC3B, UC3A3, UC3C (the main clock source is PLL0 with OSC1 as reference)
  PCL_MC_OSC0_PLL1,  // Supported by UC3C  (the main clock source is PLL1 with OSC0 as reference)
  PCL_MC_OSC1_PLL1,  // Supported by UC3C  (the main clock source is PLL1 with OSC1 as reference)
  PCL_MC_DFLL0,      // Supported by UC3L
  PCL_MC_DFLL1,      // Not supported yet
  PCL_MC_RC120M,     // Supported by UC3L, UC3C
  PCL_MC_RC8M,       // Supported by UC3C
  PCL_MC_CRIPOSC     // Supported by UC3C
} pcl_mainclk_t;

//! Input and output parameters to configure clocks with pcl_configure_clocks().
// NOTE: regarding the frequency settings, always abide by the datasheet rules and min & max supported frequencies.
#ifndef AVR32_PM_VERSION_RESETVALUE
// Support for UC3A, UC3A3, UC3B parts.
#define pcl_freq_param_t  pm_freq_param_t // See pm.h
#else
// Support for UC3C, UC3L parts.
typedef struct
{
  //! Main clock source selection (input argument).
  pcl_mainclk_t main_clk_src;

  //! Target CPU frequency (input/output argument).
  unsigned long cpu_f;

  //! Target PBA frequency (input/output argument).
  unsigned long pba_f;

  //! Target PBB frequency (input/output argument).
  unsigned long pbb_f;

  //! Target PBC frequency (input/output argument).
  unsigned long pbc_f;

  //! Oscillator 0's external crystal(or external clock) frequency (board dependant) (input argument).
  unsigned long osc0_f;

  //! Oscillator 0's external crystal(or external clock) startup time: AVR32_PM_OSCCTRL0_STARTUP_x_RCOSC (input argument).
  unsigned long osc0_startup;

  //! DFLL target frequency (input/output argument) (NOTE: the bigger, the most stable the frequency)
  unsigned long dfll_f;

  //! Other parameters that might be necessary depending on the device (implementation-dependent).
  // For the UC3L DFLL setup, this parameter should be pointing to a structure of
  // type (scif_gclk_opt_t *).
  void *pextra_params;
} pcl_freq_param_t;
#endif

//! Define "not supported" for the lib.
#define PCL_NOT_SUPPORTED (-10000)

/*! \brief Automatically configure the CPU, PBA, PBB, and HSB clocks
 *
 * This function needs some parameters stored in a pcl_freq_param_t structure:
 *  - main_clk_src is the id of the main clock source to use,
 *  - cpu_f and pba_f and pbb_f are the wanted frequencies,
 *  - osc0_f is the oscillator 0's external crystal (or external clock) on-board frequency (e.g. FOSC0),
 *  - osc0_startup is the oscillator 0's external crystal (or external clock) startup time (e.g. OSC0_STARTUP).
 *  - dfll_f is the target DFLL frequency to set-up if main_clk_src is the dfll.
 *
 * The CPU, HSB and PBA frequencies programmed after configuration are stored back into cpu_f and pba_f.
 *
 * \note: since it is dynamically computing the appropriate field values of the
 * configuration registers from the parameters structure, this function is not
 * optimal in terms of code size. For a code size optimal solution, it is better
 * to create a new function from pcl_configure_clocks() and modify it to use
 * preprocessor computation from pre-defined target frequencies.
 *
 * \param param    pointer on the configuration structure.
 *
 * \retval 0   Success.
 * \retval <0  The configuration cannot be performed.
 */
extern long int pcl_configure_clocks(pcl_freq_param_t *param);

/*! \brief Automatically configure the CPU, PBA, PBB, and HSB clocks using the RCSYS osc as main source clock.
 *
 * This function needs some parameters stored in a pcl_freq_param_t structure:
 *  - cpu_f and pba_f and pbb_f are the wanted frequencies
 *
 * Supported main clock sources: PCL_MC_RCSYS
 *
 * Supported synchronous clocks frequencies:
 * 115200Hz, 57600Hz, 28800Hz, 14400Hz, 7200Hz, 3600Hz, 1800Hz, 900Hz, 450Hz.
 *
 * \note: by default, this implementation doesn't perform thorough checks on the
 *        input parameters. To enable the checks, define AVR32SFW_INPUT_CHECK.
 *
 * \note: since it is dynamically computing the appropriate field values of the
 * configuration registers from the parameters structure, this function is not
 * optimal in terms of code size. For a code size optimal solution, it is better
 * to create a new function from pcl_configure_clocks_rcsys() and modify it to use
 * preprocessor computation from pre-defined target frequencies.
 *
 * \param param    pointer on the configuration structure.
 *
 * \retval 0   Success.
 * \retval <0  The configuration cannot be performed.
 */
extern long int pcl_configure_clocks_rcsys(pcl_freq_param_t *param);

/*! \brief Automatically configure the CPU, PBA, PBB, and HSB clocks using the RC120M osc as main source clock.
 *
 * This function needs some parameters stored in a pcl_freq_param_t structure:
 *  - cpu_f and pba_f and pbb_f are the wanted frequencies
 *
 * Supported main clock sources: PCL_MC_RC120M
 *
 * Supported synchronous clocks frequencies:
 * 30MHz, 15MHz, 7.5MHz, 3.75MHz, 1.875MHz, 937.5kHz, 468.75kHz.
 *
 * \note: by default, this implementation doesn't perform thorough checks on the
 *        input parameters. To enable the checks, define AVR32SFW_INPUT_CHECK.
 *
 * \note: since it is dynamically computing the appropriate field values of the
 * configuration registers from the parameters structure, this function is not
 * optimal in terms of code size. For a code size optimal solution, it is better
 * to create a new function from pcl_configure_clocks_rc120m() and modify it to
 * use preprocessor computation from pre-defined target frequencies.
 *
 * \param param    pointer on the configuration structure.
 *
 * \retval 0   Success.
 * \retval <0  The configuration cannot be performed.
 */
extern long int pcl_configure_clocks_rc120m(pcl_freq_param_t *param);

/*! \brief Automatically configure the CPU, PBA, PBB, and HSB clocks using the OSC0 osc as main source clock
 *
 * This function needs some parameters stored in a pcl_freq_param_t structure:
 *  - cpu_f and pba_f and pbb_f are the wanted frequencies,
 *  - osc0_f is the oscillator 0's external crystal (or external clock) on-board frequency (e.g. FOSC0),
 *  - osc0_startup is the oscillator 0's external crystal (or external clock) startup time (e.g. OSC0_STARTUP).
 *
 * Supported main clock sources: PCL_MC_OSC0
 *
 * Supported synchronous clocks frequencies:
 * (these obviously depend on the OSC0 frequency; we'll take 16MHz as an example)
 * 16MHz, 8MHz, 4MHz, 2MHz, 1MHz, 500kHz, 250kHz, 125kHz, 62.5kHz.
 *
 * \note: by default, this implementation doesn't perform thorough checks on the
 *        input parameters. To enable the checks, define AVR32SFW_INPUT_CHECK.
 *
 * \note: since it is dynamically computing the appropriate field values of the
 * configuration registers from the parameters structure, this function is not
 * optimal in terms of code size. For a code size optimal solution, it is better
 * to create a new function from pcl_configure_clocks_osc0() and modify it to use
 * preprocessor computation from pre-defined target frequencies.
 *
 * \param param    pointer on the configuration structure.
 *
 * \retval 0   Success.
 * \retval <0  The configuration cannot be performed.
 */
extern long int pcl_configure_clocks_osc0(pcl_freq_param_t *param);

/*! \brief Automatically configure the CPU, PBA, PBB, and HSB clocks using the DFLL0 as main source clock
 *
 * This function needs some parameters stored in a pcl_freq_param_t structure:
 *  - cpu_f and pba_f and pbb_f are the wanted frequencies,
 *  - dfll_f is the target DFLL frequency to set-up
 *
 * \note: when the DFLL0 is to be used as main source clock for the synchronous clocks,
 *  the target frequency of the DFLL should be chosen to be as high as possible
 *  within the specification range (for stability reasons); the target cpu and pbx
 *  frequencies will then be reached by appropriate division ratio.
 *
 * Supported main clock sources: PCL_MC_DFLL0
 *
 * Supported synchronous clocks frequencies:
 * (these obviously depend on the DFLL target frequency; we'll take 100MHz as an example)
 * 50MHz, 25MHz, 12.5MHz, 6.25MHz, 3.125MHz, 1562.5kHz, 781.25kHz, 390.625kHz.
 *
 * \note: by default, this implementation doesn't perform thorough checks on the
 *        input parameters. To enable the checks, define AVR32SFW_INPUT_CHECK.
 *
 * \note: since it is dynamically computing the appropriate field values of the
 * configuration registers from the parameters structure, this function is not
 * optimal in terms of code size. For a code size optimal solution, it is better
 * to create a new function from pcl_configure_clocks_dfll0() and modify it to
 * use preprocessor computation from pre-defined target frequencies.
 *
 * \param param    pointer on the configuration structure.
 *
 * \retval 0   Success.
 * \retval <0  The configuration cannot be performed.
 */
extern long int pcl_configure_clocks_dfll0(pcl_freq_param_t *param);

/*! \brief Switch the main clock source to Osc0 configured in crystal mode
 *
 * \param osc The oscillator to enable and switch to.
 * \param fcrystal Oscillator external crystal frequency (Hz)
 * \param startup Oscillator startup time.
 *
 * \return Status.
 *   \retval 0  Success.
 *   \retval <0 An error occurred.
 */
extern long int pcl_switch_to_osc(pcl_osc_t osc, unsigned int fcrystal, unsigned int startup);

/*! \brief Enable the clock of a module.
 *
 * \param module The module to clock (use one of the defines in the part-specific
 * header file under "toolchain folder"/avr32/inc(lude)/avr32/; depending on the
 * clock domain, look for the sections "CPU clocks", "HSB clocks", "PBx clocks"
 * or look in the module section).
 *
 * \return Status.
 *   \retval 0  Success.
 *   \retval <0 An error occurred.
 */
#ifndef AVR32_PM_VERSION_RESETVALUE
// Implementation for UC3A, UC3A3, UC3B parts.
#define pcl_enable_module(module) pm_enable_module(&AVR32_PM, module)
#else
// Implementation for UC3C, UC3L parts.
#define pcl_enable_module(module) pm_enable_module(module)
#endif

/*! \brief Disable the clock of a module.
 *
 * \param module The module to shut down (use one of the defines in the part-specific
 * header file under "toolchain folder"/avr32/inc(lude)/avr32/; depending on the
 * clock domain, look for the sections "CPU clocks", "HSB clocks", "PBx clocks"
 * or look in the module section).
 *
 * \return Status.
 *   \retval 0  Success.
 *   \retval <0 An error occurred.
 */
#ifndef AVR32_PM_VERSION_RESETVALUE
// Implementation for UC3A, UC3A3, UC3B parts.
#define pcl_disable_module(module)  pm_disable_module(&AVR32_PM, module)
#else
// Implementation for UC3C, UC3L parts.
#define pcl_disable_module(module)  pm_disable_module(module)
#endif

/*! \brief Configure the USB Clock
 *
 * \return Status.
 *   \retval 0  Success.
 *   \retval <0 An error occurred.
 */
extern long int pcl_configure_usb_clock(void);

//! @}

/*! \name Power Management
 */
//! @{
/*!
 * \brief Read the content of the GPLP registers
 * \param gplp GPLP register index (0,1,... depending on the number of GPLP registers for a given part)
 *
 * \return The content of the chosen GPLP register.
 */
extern unsigned long pcl_read_gplp(unsigned long gplp);


/*!
 * \brief Write into the GPLP registers
 * \param gplp GPLP register index (0,1,... depending on the number of GPLP registers for a given part)
 * \param value Value to write
 */
extern void pcl_write_gplp(unsigned long gplp, unsigned long value);

//! @}

#ifdef __cplusplus
}
#endif

/**
 * \}
 */

#endif  // _POWER_CLOCKS_LIB_H_
