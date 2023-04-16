/***************************************************************************//**
* \file cy_seglcd.h
* \version 1.10.1
*
* \brief
* Provides an API declaration of the Segment LCD driver.
*
********************************************************************************
* \copyright
* Copyright 2019-2020 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_seglcd
* \{
* The Segment LCD Driver provides an API to configure and operate the MXLCD hardware block.
* The MXLCD block can be flexibly configured to drive a variety of LCD glass
* at different voltage levels with multiplex ratios.
*
* Features:
* * Digital Correlation and PWM at 1/2, 1/3, 1/4 and at 1/5 bias modes are supported
* * Drives STN/TN LCD-glass with up to eight COMs (device specific)
* * 30 to 150 Hz refresh rate
* * Supports both type A (standard) and type B (low-power) waveforms
* * The display pixel state can be inverted for a negative image
* * Operation in Deep Sleep Mode from ILO/MFO
* * All-digital contrast control using "Dead Period" digital modulation
* * A set of basic standard displays and fonts
* * The customizable display and font structures.
*
* \section group_seglcd_glossary Glossary
* * LCD - Liquid Crystal Display
* * Glass - An LCD glass with one or more displays
*   (e.g. one 7-segment display and one bar-graph display).
* * TN - A twisted nematic LCD glass.
* * STN - A super-twisted nematic LCD glass.
* * Display - A block of the same type of symbols on an LCD glass to indicate a multi-digital
*   number or character string. There may be one or more displays on a single LCD glass.
* * Symbol - A block of pixels on an LCD glass to indicate a single digit or character.
* * Pixel - A basic displaying item. This can be a segment of a 7-segment symbol (thus called a "segment"),
*   a pixel of a dot-matrix display, or a stand-alone arbitrarily-shaped display element.
*   Each pixel has a unique set of common and segment lines within one LCD glass.
*   The API offers pixel identifiers - the 32-bit items of the display pixel map
*   (to use in the display structure definition, see \ref cy_stc_seglcd_disp_t),
*   created by the \ref CY_SEGLCD_PIXEL macro.
* * Common line (Com/COM for short) - A common wire/signal from the PSoC chip to the LCD glass.
*   The API offers common line identifiers - the 32-bit items of the commons array
*   (to use in \ref Cy_SegLCD_ClrFrame and \ref Cy_SegLCD_InvFrame),
*   created by the \ref CY_SEGLCD_COMMON macro.
* * Segment line (Seg/SEG for short) - A segment wire/signal from the PSoC chip to the LCD glass.
* * Octet - A bunch of subsequent eight MXLCD terminals. Octets may not match GPIO ports.
* * Frame buffer - An array of registers to control the MXLCD signal generation for all the MXLCD terminals.
*
* \section group_seglcd_solution SegLCD Solution
* The Segment LCD Driver can be used either as a standalone library
* to manage the MXLCD hardware or as a part of the more complex software solution
* delivered within ModusToolbox:
* the Device Configurator SegLCD personality and the SegLCD Configurator tools.
*
* The SegLCD solution provides an easy method to configure
* an MXLCD block to drive your standard or custom LCD glass:
* \image html seglcd_solution.png
* The SegLCD solution includes:
* * The SegLCD Configurator tool, which is a display configuration wizard to create and
*   configure displays and generate commons array and display structures \ref cy_stc_seglcd_disp_t.
* * The ModusToolbox Device Configurator contains a SegLCD personality, which is an MXLCD block
*   configuration wizard. It helps to easily tune all the timing settings, operation modes,
*   provides a flexible GPIO pin assignment capability and generates the \ref cy_stc_seglcd_config_t
*   structure and the rest of accompanying definitions.
* * The SegLCD Driver API itself, which uses all the mentioned above generated code.
*
* \section group_seglcd_configuration Configuration Considerations
* To start working with an LCD, first initialize the MXLCD block, then initialize
* the frame buffer, and then enable the block:
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Config
* \note If you use ModusToolbox Device Configurator, a SegLCD configuration structure
* is generated automatically into the GeneratedSource/cycfg_peripherals.h/.c files.
* All you need is just to call \ref Cy_SegLCD_Init with a pointer to the structure.
*
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Init
*
* Contrast vs. Frame Rate (\ref cy_stc_seglcd_config_t.contrast vs. \ref cy_stc_seglcd_config_t.frRate)\n
* Some combinations of a frame rate and input frequency can restrict the valid contrast range
* because of the limited dividers size (for Low Speed mode - 8 bit, and for High Speed mode - 16 bit).
* For small values of contrast at small frame rates, the required divider values
* may be beyond permissible limits of the dividers size.
* For large High Speed clock frequencies, certain ratios between the contrast and frame
* rate cannot be achieved due to the limited divider size. The \ref Cy_SegLCD_Init function
* automatically restricts such incorrect combinations (returns \ref CY_SEGLCD_BAD_PARAM).
* The peripheral clock divider can be adjusted to clock the LCD block with proper clock frequency:
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Clock
*
* Speed Mode Switching (\ref cy_stc_seglcd_config_t.speed)\n
* The High Speed and Low Speed generators mostly duplicate each other,
* except that for MXLCD_ver1, the High Speed version has larger frequency dividers to generate
* the frame and sub-frame periods. This is because the clock of the High Speed block
* typically has a frequency 30-100 times bigger than the 32 KHz clock fed to the Low Speed block.
* For MXLCD_ver2, both High Speed and Low Speed generators have similar 16-bit dividers,
* because a possibility exists to source a Low Speed generator with a Medium Frequency clock
* (see \ref group_sysclk_mf_funcs) that may be much higher than 32 KHz ILO:
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_MF_Clock
* Switching between High Speed and Low Speed modes via the \ref Cy_SegLCD_Init function
* causes the dividers to reconfigure.
* Under possible restrictions related to certain ratios between contrast and frame rates
* (see Contrast vs. Frame Rate section above), switching between High Speed and the Low Speed modes
* via the \ref Cy_SegLCD_Init function may set new dividers values that don't give the same contrast value.
*
* Driving Modes (\ref cy_stc_seglcd_config_t.drive)\n
* SegLCD supports the following operating modes:
* * Digital Correlation - preferred for low clock speeds, low common lines count and low supply voltages.
* * PWM at 1/2, 1/3, 1/4 or 1/5 Bias - preferred for high clock speeds (e.g. over 1MHz), many common lines (e.g. over 4), and high voltages (e.g. 3.3V or higher).
* More precise preferences depend on a certain set of an LCD glass, power modes, the number of terminals, desired contrast/frame rate settings, etc.
*
* Conventional Waveforms (\ref cy_stc_seglcd_config_t.wave)\n
* Conventional LCD drivers apply waveforms to COM and SEG electrodes generated by switching
* between multiple different voltages. The following terms are used to define these waveforms:
* * Duty:  A driver operates in the 1/M-th duty when it drives M COM electrodes. Each COM electrode is effectively driven for the 1/M of the frame time.
* * Bias:  A driver uses the 1/B-th bias when its waveforms use the voltage steps of (1/B)*VDRV.
* * Frame: A frame is the time length to address all segments.
*   During a frame, the driver cycles through the commons in sequence.
*   All segments receive 0V DC when measured over the length of an entire frame.
* * Type-A Waveform:  The driver structures the frame into M sub-frames. COMi is addressed in sub-frame i.
* * Type-B Waveform:  The driver structures the frame into 2M sub-frames. COMi is addressed in sub-frames i and M+i.
*   The two sub-frames are inverse of each other.  Typically, type-B waveforms are slightly more power-efficient because they contain fewer transitions.
*
* The following figures show the conventional waveforms for COM and SEG electrodes for the 1/3rd bias and 1/4th duty. Only COM0/COM1 and SEG0/SEG1 are drawn.
* Conventional Type-A Waveform Example:
* \image html seglcd_waveA.png
* Conventional Type-B Waveform Example:
* \image html seglcd_waveB.png
* The generalized waveforms for individual sub-frames for any duty and bias are illustrated in the following figure.
* Note that these use 6 different voltages at most(including VSS and VDRV).
* Conventional Waveforms - Generalized:
* \image html seglcd_waveGen.png
* The effective RMS voltage for on and off segments can be calculated using these waveforms:
* \image html seglcd_Voff.png
* \image html seglcd_Von.png
* The resulting Discrimination Ratio (D) for various bias and duty combinations is illustrated in the following table.
* The bias choice (B) for each duty (M) with the highest possible value for D is colored green:
* \image html seglcd_descr.png
*
* Digital Correlation (\ref CY_SEGLCD_CORRELATION)\n
* The principles of operation are illustrated by the example waveforms shown in the following figures.
* Digital Correlation Example - Type-A:
* \image html seglcd_DCA.png
* Digital Correlation Example - Type-B:
* \image html seglcd_DCB.png
* As illustrated, instead of generating bias voltages between the rails, this approach takes advantage of the LCD displays characteristic:
* the LCD segments' on-ness and off-ness degree is determined by the RMS voltage across the segments. In this approach, the correlation
* coefficient between any given pair of COM and SEG signals determines whether the corresponding LCD segment is On or Off.
* Thus, by doubling the base drive frequency of the COM signals in their inactive sub-frame intervals, the phase relationship of the COM and SEG
* drive signals can be varied to turn segments on and off - rather than varying the DC levels of the signals as is used in the conventional approaches.
*
* PWM Drive (\ref CY_SEGLCD_PWM)\n
* This approach duplicates the multi-voltage drive signals of the conventional method with bias B using a PWM output signal together
* with the intrinsic resistance and capacitance of the LCD display to create a simple PWM DAC.
* This is illustrated in the following figure:
* \image html seglcd_PWM.png
* To drive a low-capacitance display with an acceptable ripple and rise/fall time, using a 32-kHz PWM an additional external
* series resistance of 100 k - 1 M ohm is required. External Resistors are not required for PWM frequencies of greater than ~1 MHz.
* The exact frequency depends on the display capacitance, the internal ITO resistance of the ITO routing traces,
* and the drive impedance of the I/O pins.
* The PWM method works for any bias value (B). NOTE As B gets higher, a higher PWM step frequency is required to maintain the
* same PWM output frequency (the RC response of the LCD depends on the PWM output frequency, NOT the step frequency).
* The PWM approach may also be used to drive a 1/2-bias display. This has the advantage that PWM is only required on the COM signals,
* as SEG signals of a 1/2-bias display use only logic levels. Therefore, PWM 1/2-bias can be supported at 32 kHz using just
* four external resistors.
* The power consumption of the approach (even for 1/2 bias) is substantially higher than that of other methods. Therefore, it is recommended
* power-sensitive customers use Digital Correlation drive in Deep Sleep mode, and change to PWM mode to gain the advantage of
* better contrast/viewing angle on TN displays in Active or Sleep mode.
*
* PWM1/2 LCD drive waveform:
* \image html seglcd_PWM2.png
* PWM1/3 LCD drive waveform:
* \image html seglcd_PWM3.png
*
* Digital Contrast Control\n
* In all modes, digital contrast control is available using the duty cycle/dead time method illustrated in the following figure:
* \image html seglcd_contrast.png
* This illustration shows the principle for 1/3 bias and 1/4 duty implementation, but the general approach of reducing contrast
* by reducing the percentage of time the glass is driven can be generalized and applied to any drive method.
* In all cases, during the dead time, all COM and SEG signals are set to a logic "1" state.
*
* When the block is configured, for further work with display, a display structure is needed:
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Display
* \note Using the SegLCD Configurator, display structures and the commons array are generated automatically into the
* GeneratedSource/cycfg_seglcd.h/.c files. All you need is just to include cycfg_seglcd.h into your application code.
*
* And now you can write multi-digit decimal and hexadecimal numbers and strings onto the initiated 7-segment display:
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_DecNum
* after which the next image on the glass appears:
* \image html seglcd_12.png
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_HexNum
* \image html seglcd_oooc.png
*
* Or even manage separate LCD pixels:
* \snippet seglcd/snippet/SegLCD_Snpt.h snippet_Cy_SegLCD_DefPixel
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_SetPixel
* after which the next image on the glass appears:
* \image html seglcd_heart.png
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_ClrPixel
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_InvPixel
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_ActPixel
*
* The basic use case of the bar-graph display type:
* \snippet seglcd/snippet/SegLCD_Snpt.h snippet_Cy_SegLCD_DefFrame
* \snippet seglcd/snippet/SegLCD_Snpt.h snippet_Cy_SegLCD_BarLength
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_BarGraphDisplay
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_BarGraphValue
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_SetFrame
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_BarGraph
* after which the next image on the glass appears:
* \image html seglcd_bargraph.png
*
* Also, you can customize basic fonts, for example:
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_CustomAsciiFont7seg
* And now you can write characters and strings on a standard 7-segment display:
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Char
* after which the next image on the glass appears:
* \image html seglcd_char.png
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_String
* \image html seglcd_font.png
*
* Also, you can customize or create your own displays, for example:
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Custom3x5
* And also different fonts for them:
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_CustomFont3x5
* And now use all that together:
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_Custom3x5_WriteNumber
* \image html seglcd_3x5.png
*
* There are LCD-GPIO terminal mapping definitions for different device families
* used in the mentioned above commons and display pixel arrays:
* \snippet seglcd/snippet/SegLCD_Snpt.h snippet_Cy_SegLCD_connectionRemapping
*
* \section group_seglcd_more_information More Information
* Refer to the technical reference manual (TRM) and the device datasheet.
*
* \section group_seglcd_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Fixed a misprint in the documentation.</td>
*     <td>Improving user experience.</td>
*   </tr>
*   <tr>
*     <td>1.10</td>
*     <td>Fixed/Documented MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.0.1</td>
*     <td>Code snippets are extended to support the CY8C62x5 device family</td>
*     <td>User experience improvement</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_seglcd_macros    Macros
* \defgroup group_seglcd_functions Functions
* \{
*   \defgroup group_seglcd_functions_config  Block Configuration Functions
*   \defgroup group_seglcd_functions_frame   Frame/Pixel Management Functions
*   \defgroup group_seglcd_functions_display Display/Character Management Functions
* \}
* \defgroup group_seglcd_data_structures  Data Structures
* \defgroup group_seglcd_globals Global   Data
* \defgroup group_seglcd_enums Enumerated Types
*/

#if !defined(CY_SEGLCD_H)
#define CY_SEGLCD_H

#include "cy_device.h"

#if defined (CY_IP_MXLCD)

#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_seglcd_macros
* \{
*/

/** Driver major version */
#define CY_SEGLCD_DRV_VERSION_MAJOR         1

/** Driver minor version */
#define CY_SEGLCD_DRV_VERSION_MINOR         10

/** SegLCD driver ID */
#define CY_SEGLCD_ID                        (CY_PDL_DRV_ID(0x40u))

/** Specifies the pixel in the display pixel map array which is not connected */
#define CY_SEGLCD_NOT_CON                   (0xFFFFFFFFUL)

/** \cond internal */
#define CY_SEGLCD_OCTET                     (8UL)
#define CY_SEGLCD_COM_Pos                   (16U)
#define CY_SEGLCD_COM_Msk                   ((uint32_t) 0xFUL << CY_SEGLCD_COM_Pos)
#define CY_SEGLCD_OCT_Pos                   (8U)
#define CY_SEGLCD_OCT_Msk                   ((uint32_t) 0x7UL << CY_SEGLCD_OCT_Pos)
#define CY_SEGLCD_NBL_Pos                   (0U)
#define CY_SEGLCD_NBL_Msk                   ((uint32_t) 0x7UL << CY_SEGLCD_NBL_Pos)

#define CY_SEGLCD_ITEM(trmNum, comLine)     (_VAL2FLD(CY_SEGLCD_COM, (comLine))                  | \
                                             _VAL2FLD(CY_SEGLCD_OCT, (trmNum) / CY_SEGLCD_OCTET) | \
                                             _VAL2FLD(CY_SEGLCD_NBL, (trmNum) % CY_SEGLCD_OCTET))

/* Extract the LCD common line number from the pixel value */
#define CY_SEGLCD_EXTR_COM(pixel)           (_FLD2VAL(CY_SEGLCD_COM, (pixel)))
/* Extract the LCD terminal octet number from the pixel value */
#define CY_SEGLCD_EXTR_OCT(pixel)           (_FLD2VAL(CY_SEGLCD_OCT, (pixel)))
/* Extract the LCD terminal nibble number from the pixel value */
#define CY_SEGLCD_EXTR_NBL(pixel)           (_FLD2VAL(CY_SEGLCD_NBL, (pixel)))
/* Extract the LCD terminal number from the pixel value */
#define CY_SEGLCD_EXTR_TRM(pixel)           ((CY_SEGLCD_EXTR_OCT(pixel) * CY_SEGLCD_OCTET) + \
                                              CY_SEGLCD_EXTR_NBL(pixel))
/* Convert the locComNum from the machine range (0-14) into the natural range (2-16). */
#define CY_SEGLCD_COM_NUM(base)             (_FLD2VAL(LCD_CONTROL_COM_NUM, LCD_CONTROL(base)) + 2UL)
/** \endcond */


/**
* Makes the pixel identifier from the LCD segment terminal number and the user defined common line number.
* It should be used to display pixel map (pixMap) array definitions for \ref cy_stc_seglcd_disp_t.
*/
#define CY_SEGLCD_PIXEL(segNum, comLine)    (CY_SEGLCD_ITEM(segNum, comLine))

/**
* Makes the common line identifier from the LCD common terminal number and the user defined common line number.
* It should be used for commons array definitions for \ref Cy_SegLCD_ClrFrame and \ref Cy_SegLCD_InvFrame.
*/
#define CY_SEGLCD_COMMON(comNum, comLine)   (CY_SEGLCD_ITEM(comNum, comLine))

/** Space/blank/empty symbol code for the numeric type of fonts */
#define CY_SEGLCD_NUM_BLANK                 ((char_t)16)

/** \} group_seglcd_macros */


/**
* \addtogroup group_seglcd_enums
* \{
*/

/** SegLCD driver error codes */
typedef enum
{
    CY_SEGLCD_SUCCESS   = 0x0UL,                                         /**< Returned successful */
    CY_SEGLCD_BAD_PARAM = CY_SEGLCD_ID | CY_PDL_STATUS_ERROR | 0x01UL,   /**< A bad parameter was passed (display/font pointer is NULL,
                                                                          *   position is out of display area, etc.)
                                                                          */
    CY_SEGLCD_BAD_PIXEL = CY_SEGLCD_ID | CY_PDL_STATUS_ERROR | 0x02UL,   /**< The specified pixel value is wrong or the pixel is
                                                                          *   specified as 'not connected' in the display pixMap array.
                                                                          */
    CY_SEGLCD_BAD_CHAR  = CY_SEGLCD_ID | CY_PDL_STATUS_ERROR | 0x04UL,   /**< The specified character (or at least one of characters in the
                                                                          *   specified string) is not supported by the specified font.
                                                                          */
    CY_SEGLCD_EXCEED    = CY_SEGLCD_ID | CY_PDL_STATUS_WARNING | 0x08UL, /**< The string (length) or number (amount of dec/hex digits)
                                                                          *   exceeds the display limits.
                                                                          */
    CY_SEGLCD_CUSTOM    = CY_SEGLCD_ID | CY_PDL_STATUS_INFO | 0x10UL,    /**< The display/font type is custom
                                                                          *   (not defined by the \ref cy_en_seglcd_disp_t).
                                                                          */
} cy_en_seglcd_status_t;

/** SegLCD block speed mode */
typedef enum
{
    CY_SEGLCD_SPEED_LOW  = 0x0UL, /**< Low Speed mode, works in Active, Sleep and DeepSleep power modes */
    CY_SEGLCD_SPEED_HIGH = 0x1UL  /**< High Speed mode, works in Active and Sleep power modes */
} cy_en_seglcd_speed_t;

/** SegLCD block low speed mode clock source selection  */
typedef enum
{
    CY_SEGLCD_LSCLK_LF = 0x0UL, /**< Low Frequency source, usually connected to ILO */
    CY_SEGLCD_LSCLK_MF = 0x1UL  /**< Middle Frequency source, usually connected to CLK_MF, \ref group_sysclk_mf_funcs */
} cy_en_seglcd_lsclk_t;

/** SegLCD driving waveform type */
typedef enum
{
    CY_SEGLCD_TYPE_A = 0x0UL, /**< Type A - Each frame addresses each COM pin only once with a balanced (DC=0) waveform. */
    CY_SEGLCD_TYPE_B = 0x1UL  /**< Type B - Each frame addresses each COM pin twice in a sequence with a positive
                               *            and negative waveform that together are balanced (DC=0).
                               */
} cy_en_seglcd_wave_t;

/** SegLCD driving mode configuration */
typedef enum
{
    CY_SEGLCD_PWM         = 0x0UL, /**< PWM mode. */
    CY_SEGLCD_CORRELATION = 0x1UL  /**< Digital Correlation mode. */
} cy_en_seglcd_drive_t;

/** SegLCD PWM bias selection */
typedef enum
{
    CY_SEGLCD_BIAS_HALF   = 0x0UL, /**< 1/2 Bias. */
    CY_SEGLCD_BIAS_THIRD  = 0x1UL, /**< 1/3 Bias. */
    CY_SEGLCD_BIAS_FOURTH = 0x2UL, /**< 1/4 Bias (not supported for \ref CY_SEGLCD_SPEED_LOW mode in MXLCD_ver1). */
    CY_SEGLCD_BIAS_FIFTH  = 0x3UL, /**< 1/5 Bias (not supported for \ref CY_SEGLCD_SPEED_LOW mode in MXLCD_ver1). */
} cy_en_seglcd_bias_t;

/** SegLCD segment display types */
typedef enum
{
    CY_SEGLCD_BAR   = 1U,  /**< Bar Graph / Dial display */
    CY_SEGLCD_7SEG  = 7U,  /**< Seven-segment display */
    CY_SEGLCD_14SEG = 14U, /**< Fourteen-segment display */
    CY_SEGLCD_16SEG = 16U, /**< Sixteen-segment display */
    CY_SEGLCD_5X8DM = 40U  /**< Five-by-eight dot matrix display */
} cy_en_seglcd_disp_t;

/** \} group_seglcd_enums */


/** \addtogroup group_seglcd_macros
* \{
*/

/* Font map array symbol sizes in bytes. Used for the basic font definitions (\ref group_seglcd_globals) and also can be used for custom font definitions */
#define CY_SEGLCD_14SEG_FONTMAP_SIZE       (CY_SYSLIB_DIV_ROUNDUP(CY_SEGLCD_14SEG, CY_SEGLCD_OCTET)) /**< 14-segment fontMap array item size (in bytes) */
#define CY_SEGLCD_16SEG_FONTMAP_SIZE       (CY_SYSLIB_DIV_ROUNDUP(CY_SEGLCD_16SEG, CY_SEGLCD_OCTET)) /**< 16-segment fontMap array item size (in bytes) */
#define CY_SEGLCD_5X8DM_FONTMAP_SIZE       (CY_SYSLIB_DIV_ROUNDUP(CY_SEGLCD_5X8DM, CY_SEGLCD_OCTET)) /**< 5x8 dot matrix fontMap array item size (in bytes) */

/** \} group_seglcd_macros */


/***************************************
*       Configuration Structures
***************************************/


/**
* \addtogroup group_seglcd_data_structures
* \{
*/

/** Configuration structure */
typedef struct
{
    cy_en_seglcd_speed_t speed; /**< Speed mode selection, see: #cy_en_seglcd_speed_t. */
    cy_en_seglcd_wave_t   wave; /**< Waveform type configuration, see: #cy_en_seglcd_wave_t. */
    cy_en_seglcd_drive_t drive; /**< Driving mode configuration, see: #cy_en_seglcd_drive_t. */
    cy_en_seglcd_bias_t   bias; /**< PWM bias selection, see: #cy_en_seglcd_bias_t. */
    cy_en_seglcd_lsclk_t lsClk; /**< Low Speed Mode clock selection, see: #cy_en_seglcd_lsclk_t.
                                 *   This is effective for MXLCD_ver2,
                                 *   for MXLCD_ver1 it is ignored.
                                 */
    uint8_t             comNum; /**< The number of Common connections, the valid range is 2...16
                                 *   however the maximum is dependent on PSoC device family -
                                 *   there could be limitation to 4 or 8 commons, see the device TRM.
                                 */
    uint8_t             frRate; /**< The LCD frame rate, the valid range is 30...150 */
    uint8_t           contrast; /**< The LCD contrast, the valid range is 0...100 */
    uint32_t           clkFreq; /**< The LCD clock frequency (ignored for \ref CY_SEGLCD_LSCLK_LF mode,
                                 *   or in \ref CY_SEGLCD_SPEED_LOW mode for MXLCD_ver1),
                                 *   the valid range is 10000...100000000 (Hz)
                                 */
} cy_stc_seglcd_config_t;

/** Font structure */
typedef struct
{
    char_t            first; /**< The first character code in the fontMap array */
    char_t             last; /**< The last character code in the fontMap array */
    bool              ascii; /**< Specifies whether the font map is indexed accordingly to ASCII character codes:
                              *   true - the font is ASCII-coded alphanumeric (e.g. a basic set "space" (ASCII 0x20) - "tilde"(ASCII 0x7E));
                              *   false - the font is e.g. pure numeric (0x0...0xF only), or any other custom character set.
                              */
    uint8_t const * fontMap; /**< The pointer to the font segment/pixel map array. */
} cy_stc_seglcd_font_t;

/** Display structure */
typedef struct
{
    uint16_t                     type; /**< The display type, one of \ref cy_en_seglcd_disp_t or custom. */
    uint16_t                   symNum; /**< The number of symbols (digits, characters). */
    bool                       invert; /**< Specifies whether the display is inverted or not. */
    uint32_t           const * pixMap; /**< The pointer to the display pixel map array:
                                        *   The array dimension is: uint32_t pixMap[symNum][type].
                                        *   Each array item should be made using the \ref CY_SEGLCD_PIXEL macro.
                                        */
    cy_stc_seglcd_font_t const * font; /**< The pointer to the font structure suitable for this display.
                                        *   Note that for the \ref CY_SEGLCD_BAR displays font is not used, so can be NULL.
                                        */
} cy_stc_seglcd_disp_t;

/** \} group_seglcd_data_structures */


/** \addtogroup group_seglcd_globals
* \{
*/

extern const cy_stc_seglcd_font_t cy_segLCD_7SegFont;  /**< Basic 7-segment font */
extern const cy_stc_seglcd_font_t cy_segLCD_14SegFont; /**< Basic 14-segment font */
extern const cy_stc_seglcd_font_t cy_segLCD_16SegFont; /**< Basic 16-segment font */
extern const cy_stc_seglcd_font_t cy_segLCD_5x8DmFont; /**< Basic 5x8 dot matrix font */

/** \} group_seglcd_globals */


/***************************************
*        Function Prototypes
***************************************/


/**
* \addtogroup group_seglcd_functions
* \{
*/


/**
* \addtogroup group_seglcd_functions_config
* \{
*/
cy_en_seglcd_status_t Cy_SegLCD_Init    (LCD_Type * base,                    cy_stc_seglcd_config_t const * config);
cy_en_seglcd_status_t Cy_SegLCD_Contrast(LCD_Type * base, uint32_t contrast, cy_stc_seglcd_config_t       * config);
                 void Cy_SegLCD_Deinit  (LCD_Type * base);
                 void Cy_SegLCD_Enable  (LCD_Type * base);
                 void Cy_SegLCD_Disable (LCD_Type * base);
/** \} group_seglcd_functions_config */


/**
* \addtogroup group_seglcd_functions_display
* \{
*/
cy_en_seglcd_status_t Cy_SegLCD_WriteChar  (LCD_Type * base, char_t      character, uint32_t position, cy_stc_seglcd_disp_t const * display);
cy_en_seglcd_status_t Cy_SegLCD_WriteString(LCD_Type * base, char_t const * string, uint32_t position, cy_stc_seglcd_disp_t const * display);
cy_en_seglcd_status_t Cy_SegLCD_WriteNumber(LCD_Type * base, uint32_t        value, uint32_t position, cy_stc_seglcd_disp_t const * display, bool zeroes, bool hex);
cy_en_seglcd_status_t Cy_SegLCD_BarGraph   (LCD_Type * base, uint32_t        value, uint32_t position, cy_stc_seglcd_disp_t const * display);
/** \} group_seglcd_functions_display */


/**
* \addtogroup group_seglcd_functions_frame
* \{
*/
                cy_en_seglcd_status_t Cy_SegLCD_ClrFrame  (LCD_Type * base, uint32_t const * commons);
                cy_en_seglcd_status_t Cy_SegLCD_InvFrame  (LCD_Type * base, uint32_t const * commons);
                cy_en_seglcd_status_t Cy_SegLCD_WritePixel(LCD_Type * base, uint32_t pixel, bool value);
                                 bool Cy_SegLCD_ReadPixel (LCD_Type * base, uint32_t pixel);
__STATIC_INLINE cy_en_seglcd_status_t Cy_SegLCD_SetPixel  (LCD_Type * base, uint32_t pixel);
__STATIC_INLINE cy_en_seglcd_status_t Cy_SegLCD_ClrPixel  (LCD_Type * base, uint32_t pixel);
__STATIC_INLINE cy_en_seglcd_status_t Cy_SegLCD_InvPixel  (LCD_Type * base, uint32_t pixel);


/*******************************************************************************
* Function Name: Cy_SegLCD_SetPixel
****************************************************************************//**
*
* Sets (turns on) the specified pixel.
*
* \param base The base pointer to the LCD instance registers.
* \param pixel The predefined packed number that points to the pixel location
*              in the frame buffer.
* \return \ref cy_en_seglcd_status_t.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.h snippet_Cy_SegLCD_DefPixel
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_SetPixel
*
*******************************************************************************/
__STATIC_INLINE cy_en_seglcd_status_t Cy_SegLCD_SetPixel(LCD_Type * base, uint32_t pixel)
{
    return (Cy_SegLCD_WritePixel(base, pixel, true));
}


/*******************************************************************************
* Function Name: Cy_SegLCD_ClrPixel
****************************************************************************//**
*
* Clears (turns off) the specified pixel.
*
* \param base The base pointer to the LCD instance registers.
* \param pixel The predefined packed number that points to the pixel location
*              in the frame buffer.
* \return \ref cy_en_seglcd_status_t.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.h snippet_Cy_SegLCD_DefPixel
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_ClrPixel
*
*******************************************************************************/
__STATIC_INLINE cy_en_seglcd_status_t Cy_SegLCD_ClrPixel(LCD_Type * base, uint32_t pixel)
{
    return (Cy_SegLCD_WritePixel(base, pixel, false));
}


/*******************************************************************************
* Function Name: Cy_SegLCD_InvPixel
****************************************************************************//**
*
* Inverts the state of the specified pixel.
*
* \param base The base pointer to the LCD instance registers.
* \param pixel The predefined packed number that points to the pixel location
*              in the frame buffer.
* \return \ref cy_en_seglcd_status_t.
*
* \funcusage
* \snippet seglcd/snippet/SegLCD_Snpt.h snippet_Cy_SegLCD_DefPixel
* \snippet seglcd/snippet/SegLCD_Snpt.c snippet_Cy_SegLCD_InvPixel
*
*******************************************************************************/
__STATIC_INLINE cy_en_seglcd_status_t Cy_SegLCD_InvPixel(LCD_Type * base, uint32_t pixel)
{
    return (Cy_SegLCD_WritePixel(base, pixel, !Cy_SegLCD_ReadPixel(base, pixel)));
}

/** \} group_seglcd_functions_frame */

/** \} group_seglcd_functions */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXLCD */

#endif /* CY_SEGLCD_H */

/** \} group_seglcd */

/* [] END OF FILE */
