//*****************************************************************************
//
//  am_hal_pdm.h
//! @file
//!
//! @brief Functions for accessing and configuring the PDM module
//!
//! @addtogroup pdm2 Pulse Density Modulation (PDM) Input Module.
//! @ingroup apollo2hal
//! @{

//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#ifndef AM_HAL_PDM_H
#define AM_HAL_PDM_H

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Macro definitions
//
//*****************************************************************************

//*****************************************************************************
//
//! @name PDM Left Right Swap Control
//! @brief Macro definitions for the PDM LRSWAP bit field
//!
//! These macros may be used with the am_hal_pdm_config_t structure to set the
//! left right swap bit.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_PCFG_LRSWAP_ENABLE                                         \
              AM_REG_PDM_PCFG_LRSWAP_EN
#define AM_HAL_PDM_PCFG_LRSWAP_DISABLE                                        \
              AM_REG_PDM_PCFG_LRSWAP_NOSWAP
//! @}

//*****************************************************************************
//
//! @name PDM Right Gain Setting
//! @brief Macro definitions for the PDM Right Gain Setting.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to set the
//! right gain value.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_PCFG_RIGHT_PGA_M15DB   AM_REG_PDM_PCFG_PGARIGHT_M15DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_M300DB  AM_REG_PDM_PCFG_PGARIGHT_M300DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_M45DB   AM_REG_PDM_PCFG_PGARIGHT_M45DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_M60DB   AM_REG_PDM_PCFG_PGARIGHT_M60DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_M75DB   AM_REG_PDM_PCFG_PGARIGHT_M75DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_M90DB   AM_REG_PDM_PCFG_PGARIGHT_M90DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_M105DB  AM_REG_PDM_PCFG_PGARIGHT_M105DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_M120DB  AM_REG_PDM_PCFG_PGARIGHT_M120DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_P105DB  AM_REG_PDM_PCFG_PGARIGHT_P105DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_P90DB   AM_REG_PDM_PCFG_PGARIGHT_P90DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_P75DB   AM_REG_PDM_PCFG_PGARIGHT_P75DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_P60DB   AM_REG_PDM_PCFG_PGARIGHT_P60DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_P45DB   AM_REG_PDM_PCFG_PGARIGHT_P45DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_P300DB  AM_REG_PDM_PCFG_PGARIGHT_P300DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_P15DB   AM_REG_PDM_PCFG_PGARIGHT_P15DB
#define AM_HAL_PDM_PCFG_RIGHT_PGA_0DB     AM_REG_PDM_PCFG_PGARIGHT_0DB
//! @}

//*****************************************************************************
//
//! @name PDM Left Gain Setting
//! @brief Macro definitions for the PDM Left Gain Setting.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to set the
//! left gain value.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_PCFG_LEFT_PGA_M15DB   AM_REG_PDM_PCFG_PGALEFT_M15DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_M300DB  AM_REG_PDM_PCFG_PGALEFT_M300DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_M45DB   AM_REG_PDM_PCFG_PGALEFT_M45DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_M60DB   AM_REG_PDM_PCFG_PGALEFT_M60DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_M75DB   AM_REG_PDM_PCFG_PGALEFT_M75DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_M90DB   AM_REG_PDM_PCFG_PGALEFT_M90DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_M105DB  AM_REG_PDM_PCFG_PGALEFT_M105DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_M120DB  AM_REG_PDM_PCFG_PGALEFT_M120DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_P105DB  AM_REG_PDM_PCFG_PGALEFT_P105DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_P90DB   AM_REG_PDM_PCFG_PGALEFT_P90DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_P75DB   AM_REG_PDM_PCFG_PGALEFT_P75DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_P60DB   AM_REG_PDM_PCFG_PGALEFT_P60DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_P45DB   AM_REG_PDM_PCFG_PGALEFT_P45DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_P300DB  AM_REG_PDM_PCFG_PGALEFT_P300DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_P15DB   AM_REG_PDM_PCFG_PGALEFT_P15DB
#define AM_HAL_PDM_PCFG_LEFT_PGA_0DB     AM_REG_PDM_PCFG_PGALEFT_0DB
//! @}

//*****************************************************************************
//
//! @name PDM Configuration MCLK Divider
//! @brief Macro definitions for the PDM MCLK Divider
//!
//! These macros may be used with the am_hal_pdm_config_t structure to set the
//! sinc decimation rate relative to the PDM sample clock (OSR).
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_PCFG_MCLKDIV_DIV1    AM_REG_PDM_PCFG_MCLKDIV_MCKDIV1
#define AM_HAL_PDM_PCFG_MCLKDIV_DIV2    AM_REG_PDM_PCFG_MCLKDIV_MCKDIV2
#define AM_HAL_PDM_PCFG_MCLKDIV_DIV3    AM_REG_PDM_PCFG_MCLKDIV_MCKDIV3
#define AM_HAL_PDM_PCFG_MCLKDIV_DIV4    AM_REG_PDM_PCFG_MCLKDIV_MCKDIV4

#define AM_HAL_PDM_PCFG_MCLKDIV(DIV)    AM_REG_PDM_PCFG_MCLKDIV(DIV)
//! @}

//*****************************************************************************
//
//! @name PDM Configuration SINC Decimation Rate
//! @brief Macro definitions for the PDM SINC decimation rate
//!
//! These macros may be used with the am_hal_pdm_config_t structure to set the
//! sinc decimation rate relative to the PDM sample clock (OSR).
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_PCFG_SINC_RATE(OSR)                                        \
              AM_REG_PDM_PCFG_SINCRATE(OSR)
//! @}

//*****************************************************************************
//
//! @name PDM Configuration High Pass Filter Enable
//! @brief Macro definitions for the PDM ADCHPD
//!
//! These macros may be used with the am_hal_pdm_config_t structure to enable
//! the high pass filter.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_PCFG_ADCHPD_ENABLE  AM_REG_PDM_PCFG_ADCHPD_EN
#define AM_HAL_PDM_PCFG_ADCHPD_DISABLE AM_REG_PDM_PCFG_ADCHPD_DIS
//! @}

//*****************************************************************************
//
//! @name PDM Configuration HPCUTOFF
//! @brief Macro definitions for the PDM High Pass Filter Cutoff Selector.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to set the
//! high pass filter cutoff frequency. Valid range is 0 to 7.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_PCFG_HPCUTOFF(HPSEL)                                       \
              AM_REG_PDM_PCFG_HPCUTOFF(HPSEL)
//! @}

//*****************************************************************************
//
//! @name PDM Configuration Gain Set Change Clock Delay
//! @brief Macro definitions for the PDM clock delay for gain set changes.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to set the
//! number of clocks for spreading gain setting changes. Valid range is 0 to 7.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_PCFG_CYCLES(CLOCKS)                                        \
              AM_REG_PDM_PCFG_CYCLES(CLOCKS)
//! @}

//*****************************************************************************
//
//! @name PDM Configuration SOFTMUTE enable/disable.
//! @brief Macro definitions for the PDM PCFG register mute controls.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to enable
//! or disable the SOFTMUTE option.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_PCFG_SOFTMUTE_ENABLE  AM_REG_PDM_PCFG_SOFTMUTE_EN
#define AM_HAL_PDM_PCFG_SOFTMUTE_DISABLE AM_REG_PDM_PCFG_SOFTMUTE_DIS
//! @}

//*****************************************************************************
//
//! @name PDM Configuration PDM Core enable/disable.
//! @brief Macro definitions for the PDM PCFG register filter engine enable.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to enable
//! or disable the PDM filter engine core.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_PCFG_PDMCORE_ENABLE  AM_REG_PDM_PCFG_PDMCORE_EN
#define AM_HAL_PDM_PCFG_PDMCORE_DISABLE AM_REG_PDM_PCFG_PDMCORE_DIS
//! @}

//*****************************************************************************
//
//! @name PDM Clock Frequencies
//! @brief Macro definitions for the PDM clock (from clkgen) frequencies.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to set the
//! source clock frequency of the PDM interface.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_IOCLK_12MHZ                                              \
        (AM_REG_PDM_VCFG_PDMCLKSEL_12MHz | AM_REG_PDM_VCFG_IOCLKEN_EN)
#define AM_HAL_PDM_IOCLK_6MHZ                                               \
        (AM_REG_PDM_VCFG_PDMCLKSEL_6MHz | AM_REG_PDM_VCFG_IOCLKEN_EN)
#define AM_HAL_PDM_IOCLK_3MHZ                                               \
        (AM_REG_PDM_VCFG_PDMCLKSEL_3MHz | AM_REG_PDM_VCFG_IOCLKEN_EN)
#define AM_HAL_PDM_IOCLK_1_5MHZ                                             \
        (AM_REG_PDM_VCFG_PDMCLKSEL_1_5MHz | AM_REG_PDM_VCFG_IOCLKEN_EN)
#define AM_HAL_PDM_IOCLK_750KHZ                                             \
        (AM_REG_PDM_VCFG_PDMCLKSEL_750KHz | AM_REG_PDM_VCFG_IOCLKEN_EN)
#define AM_HAL_PDM_IOCLK_375KHZ                                             \
        (AM_REG_PDM_VCFG_PDMCLKSEL_375KHz | AM_REG_PDM_VCFG_IOCLKEN_EN)
#define AM_HAL_PDM_IOCLK_187KHZ                                             \
        (AM_REG_PDM_VCFG_PDMCLKSEL_187KHz | AM_REG_PDM_VCFG_IOCLKEN_EN)
//! @}

//*****************************************************************************
//
//! @name PDM Voice Configuration RSTB
//! @brief Reset the IP core.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_VCFG_RSTB_RESET      AM_REG_PDM_VCFG_RSTB_RESET
#define AM_HAL_PDM_VCFG_RSTB_NORMAL     AM_REG_PDM_VCFG_RSTB_NORM
//! @}

//*****************************************************************************
//
//! @name PDM Voice Configuration PDM Clock Enable/Disable
//! @brief Macro definitions for the PDM VCFG register PDMCLKEN.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to enable
//! or disable the PDM clock output to the pad mux and from there to the world.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_VCFG_PDMCLK_ENABLE  AM_REG_PDM_VCFG_PDMCLK_EN
#define AM_HAL_PDM_VCFG_PDMCLK_DISABLE AM_REG_PDM_VCFG_PDMCLK_DIS
//! @}

//*****************************************************************************
//
//! @name PDM Voice Configuration I2S Mode Enable/Disable
//! @brief Macro definitions for the PDM VCFG register I2SMODE.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to enable
//! or disable the PDM clock output to the pad mux and from there to the world.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_VCFG_I2SMODE_ENABLE  AM_REG_PDM_VCFG_I2SMODE_EN
#define AM_HAL_PDM_VCFG_I2SMODE_DISABLE AM_REG_PDM_VCFG_I2SMODE_DIS
//! @}

//*****************************************************************************
//
//! @name PDM Voice Configuration BCLK Inversion Enable/Disable
//! @brief Macro definitions for the PDM VCFG register BCLKINV.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to enable
//! or disable the PDM clock output to the pad mux and from there to the world.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_VCFG_BCLKINV_ENABLE  AM_REG_PDM_VCFG_BCLKINV_INV
#define AM_HAL_PDM_VCFG_BCLKINV_DISABLE AM_REG_PDM_VCFG_BCLKINV_NORM
//! @}

//*****************************************************************************
//
//! @name PDM Voice Configuration DMICDEL Enable/Disable
//! @brief Macro definitions for the PDM VCFG register Digital Mic Delay.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to enable
//! or disable the PDM digital microphone clock delay.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_VCFG_DMICDEL_1CYC    AM_REG_PDM_VCFG_DMICKDEL_1CYC
#define AM_HAL_PDM_VCFG_DMICDEL_0CYC    AM_REG_PDM_VCFG_DMICKDEL_0CYC
#define AM_HAL_PDM_VCFG_DMICDEL_ENABLE  AM_REG_PDM_VCFG_DMICKDEL_1CYC
#define AM_HAL_PDM_VCFG_DMICDEL_DISABLE AM_REG_PDM_VCFG_DMICKDEL_0CYC
//! @}

//*****************************************************************************
//
//! @name PDM Voice Configuration Select Apps Processor (AP) versus Internal
//! @brief Macro definitions for the PDM VCFG register Digital Mic Delay.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to select
//! the Application Processor (I2S slave) mode or the Internal FIFO interface
//! to the Apollo Cortex M4.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_VCFG_SELAP_I2S       AM_REG_PDM_VCFG_SELAP_I2S
#define AM_HAL_PDM_VCFG_SELAP_INTERNAL  AM_REG_PDM_VCFG_SELAP_INTERNAL
#define AM_HAL_PDM_VCFG_SELAP_AP_I2S    AM_REG_PDM_VCFG_SELAP_I2S
#define AM_HAL_PDM_VCFG_SELAP_CM4_FIFO  AM_REG_PDM_VCFG_SELAP_INTERNAL
//! @}

//*****************************************************************************
//
//! @name PDM Voice Configuration PACK Enable/Disable
//! @brief Macro definitions for the PDM VCFG register sample packing mode.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to enable
//! or disable the PDM sample packing mode. This mode puts two 16-bit samples
//! per 32-bit FIFO word. The following packed modes are available:
//!
//!   mono left:            LEFT_NEW, LEFT_OLD
//!   mono right:           RIGHT_NEW,RIGHT_OLD
//!   stereo right:         LEFT,     RIGHT
//!   stereo right(LRSWAP): RIGHT,    LEFT
//!
//!
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_VCFG_PACK_ENABLE  AM_REG_PDM_VCFG_PCMPACK_EN
#define AM_HAL_PDM_VCFG_PACK_DISABLE AM_REG_PDM_VCFG_PCMPACK_DIS
//! @}

//*****************************************************************************
//
//! @name PDM Channel Selects
//! @brief Macro definitions for the PDM Channel Selection.
//!
//! These macros may be used with the am_hal_pdm_config_t structure to set the
//! channel selection for the PDM interface.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_VCFG_CHANNEL_LEFT   AM_REG_PDM_VCFG_CHSET_LEFT
#define AM_HAL_PDM_VCFG_CHANNEL_RIGHT  AM_REG_PDM_VCFG_CHSET_RIGHT
#define AM_HAL_PDM_VCFG_CHANNEL_STEREO AM_REG_PDM_VCFG_CHSET_STEREO
//! @}

//*****************************************************************************
//
//! @name PDM Interrupts
//! @brief Macro definitions for the PDM interrupt status bits.
//!
//! These macros correspond to the bits in the PDM interrupt status register.
//! They may be used for any of the am_hal_pdm_int_x() functions.
//!
//! @{
//
//*****************************************************************************
#define AM_HAL_PDM_INT_UNDFL AM_REG_PDM_INTEN_UNDFL_M
#define AM_HAL_PDM_INT_OVF   AM_REG_PDM_INTEN_OVF_M
#define AM_HAL_PDM_INT_FIFO  AM_REG_PDM_INTEN_THR_M
//! @}

//*****************************************************************************
//
//! @brief Configuration structure for the PDM module.
//
//*****************************************************************************
typedef struct
{
    //
    //! @brief Set the PDM configuration reg with the values in this member.
    //! Choose from AM_HAL_PDM_PCFG macros.
    //!     AM_HAL_PDM_PCFG_LRSWAP_xxx
    //!     AM_HAL_PDM_PCFG_RIGHT_PGA_xxx
    //!     AM_HAL_PDM_PCFG_LEFT_PGA_xxx
    //!     AM_HAL_PDM_PCFG_MCLKDIV_xxx
    //!     AM_HAL_PDM_PCFG_SINC_RATE()
    //!     AM_HAL_PDM_PCFG_ADCHPD_xxx
    //!     AM_HAL_PDM_PCFG_HPCUTOFF()
    //!     AM_HAL_PDM_PCFG_CYCLES()
    //!     AM_HAL_PDM_PCFG_SOFTMUTE_xxx
    //!   * AM_HAL_PDM_PCFG_PDMCORE_EN
    //!     AM_HAL_PDM_PCFG_PDMCORE_DISABLE
    //
    uint32_t ui32PDMConfigReg;

    //
    //! @brief Set the Voice Configuration reg with the values in this member.
    //! Choose from AM_HAL_PDM_VCFG macros.
    //!     AM_HAL_PDM_IOCLK_xxx (also sets AM_REG_PDM_VCFG_IOCLKEN_EN)
    //!   * AM_REG_PDM_VCFG_IOCLKEN_EN
    //!   * AM_HAL_PDM_VCFG_RSTB_RESET
    //!     AM_HAL_PDM_VCFG_RSTB_NORMAL
    //!   * AM_HAL_PDM_VCFG_PDMCLK_EN
    //!     AM_HAL_PDM_VCFG_PDMCLK_DIS
    //!     AM_HAL_PDM_VCFG_I2SMODE_xxx
    //!     AM_HAL_PDM_VCFG_BCLKINV_xxx
    //!     AM_HAL_PDM_VCFG_DMICDEL_xxx
    //!     AM_HAL_PDM_VCFG_SELAP_xxx
    //!     AM_HAL_PDM_VCFG_PACK_xxx
    //!     AM_HAL_PDM_VCFG_CHANNEL_xxx
    //!
    //! * = These bits are set or cleared by the HAL PDM functions
    //!     am_hal_pdm_enable() or am_hal_pdm_disable().
    //
    uint32_t ui32VoiceConfigReg;

    //
    //! @brief Select the FIFO PCM sample threshold.
    //!
    //! The PDM controller will generate a processor interrupt when the number
    //! of entries in the FIFO goes *above* this number.
    //
    uint32_t ui32FIFOThreshold;
} am_hal_pdm_config_t;

//*****************************************************************************
//
// Define function-like macros.
//
//*****************************************************************************

//*****************************************************************************
//
//! @brief Read the FIFO depth information as an in-line macro
//
//*****************************************************************************
#define am_hal_pdm_fifo_depth_read()    (AM_REG(PDM, FR))

//*****************************************************************************
//
//! @brief Read the FIFO READ DATA as an in-line macro
//
//*****************************************************************************
#define am_hal_pdm_fifo_data_read()     (AM_REG(PDM, FRD))

//*****************************************************************************
//
//! @brief Flush the FIFO as an in-line macro
//
//*****************************************************************************
#define am_hal_pdm_fifo_flush()         (AM_REG(PDM, FLUSH) = 0)

//*****************************************************************************
//
//! @brief Set the PDM Configuration (PCFG) Register
//!
//! This function sets the PDM configuration register
//
//*****************************************************************************
#define am_hal_pdm_pcfg_set(Value)      (AM_REG(PDM, PCFG) = Value)

//*****************************************************************************
//
//! @brief Get the PCFG register value from PDM module.
//
//*****************************************************************************
#define am_hal_pdm_pcfg_get()           (AM_REG(PDM, PCFG))

//*****************************************************************************
//
//! @brief Set the Voice Configuration (VCFG) Register
//
//*****************************************************************************
#define am_hal_pdm_vcfg_set(Value)      (AM_REG(PDM, VCFG) = Value)

//*****************************************************************************
//
//! @brief Get the VCFG register value from PDM module.
//
//*****************************************************************************
#define am_hal_pdm_vcfg_get()           (AM_REG(PDM, VCFG))

//*****************************************************************************
//
//! @brief Set the FIFO Threshold
//
//*****************************************************************************
#define am_hal_pdm_thresh_set(thresh)   (AM_REG(PDM, FTHR) = thresh)

//*****************************************************************************
//
//! @brief Get the FIFO Threshold register value from PDM module.
//
//*****************************************************************************
#define am_hal_pdm_thresh_get()         (AM_REG(PDM, FTHR))

//*****************************************************************************
//
//! @brief Set the left microphone PGA gain.
//!
//*****************************************************************************
#define am_hal_pdm_left_gain_set(gain)  (AM_BFW(PDM, PCFG, PGALEFT, gain))

//*****************************************************************************
//
//! @brief Set the right microphone PGA gain.
//
//*****************************************************************************
#define am_hal_pdm_right_gain_set(gain) (AM_BFW(PDM, PCFG, PGARIGHT, gain))

//*****************************************************************************
//
//! @brief Get the left microphone PGA gain value.
//
//*****************************************************************************
#define am_hal_pdm_left_gain_get()      (AM_BFR(PDM, PCFG, PGALEFT))

//*****************************************************************************
//
//! @brief Get the right microphone PGA gain value.
//
//*****************************************************************************
#define am_hal_pdm_right_gain_get()     (AM_BFR(PDM, PCFG, PGARIGHT))

//*****************************************************************************
//
//! @brief Enable the Soft Mute functionality.
//
//*****************************************************************************
#define am_hal_pdm_soft_mute_enable()   (AM_BFWe(PDM, PCFG, SOFTMUTE, EN))

//*****************************************************************************
//
//! @brief Disable the Soft Mute functionality.
//
//*****************************************************************************
#define am_hal_pdm_soft_mute_disable()  (AM_BFWe(PDM, PCFG, SOFTMUTE, DIS))

//*****************************************************************************
//
//! @brief Enable selected PDM Interrupts.
//!
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_pdm.h\n
//!     AM_HAL_PDM_INT_UNDFL\n
//!     AM_HAL_PDM_INT_OVF\n
//!     AM_HAL_PDM_INT_FIFO\n
//
//*****************************************************************************
#define am_hal_pdm_int_enable(intrpt)   (AM_REG(PDM, INTEN) |= intrpt)

//*****************************************************************************
//
//! @brief Return the enabled PDM Interrupts.
//!
//! Use this function to return all enabled PDM interrupts.
//!
//! @return all enabled PDM interrupts as a mask.\n
//!     AM_HAL_PDM_INT_UNDFL\n
//!     AM_HAL_PDM_INT_OVF\n
//!     AM_HAL_PDM_INT_FIFO\n
//
//*****************************************************************************
#define am_hal_pdm_int_enable_get()     (AM_REG(PDM, INTEN))

//*****************************************************************************
//
//! @brief Disable selected PDM Interrupts.
//!
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_pdm.h\n
//!     AM_HAL_PDM_INT_UNDFL\n
//!     AM_HAL_PDM_INT_OVF\n
//!     AM_HAL_PDM_INT_FIFO\n
//
//*****************************************************************************
#define am_hal_pdm_int_disable(intrpt)  (AM_REG(PDM, INTEN) &= ~intrpt)

//*****************************************************************************
//
//! @brief Clear selected PDM Interrupts.
//!
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_pdm.h\n
//!     AM_HAL_PDM_INT_UNDFL\n
//!     AM_HAL_PDM_INT_OVF\n
//!     AM_HAL_PDM_INT_FIFO\n
//
//*****************************************************************************
#define am_hal_pdm_int_clear(intrpt)    (AM_REG(PDM, INTCLR) = intrpt)

//*****************************************************************************
//
//! @brief Set selected PDM Interrupts.
//!
//! Use this function to set the PDM interrupts.
//!
//! @param ui32Interrupt - Use the macro bit fields provided in am_hal_pdm.h\n
//!     AM_HAL_PDM_INT_UNDFL\n
//!     AM_HAL_PDM_INT_OVF\n
//!     AM_HAL_PDM_INT_FIFO\n
//
//*****************************************************************************
#define am_hal_pdm_int_set(intrpt)      (AM_REG(PDM, INTSET) = intrpt)

//*****************************************************************************
//
// External function definitions
//
//*****************************************************************************
extern void am_hal_pdm_config(am_hal_pdm_config_t * cfg);
extern void am_hal_pdm_enable(void);
extern void am_hal_pdm_disable(void);

extern uint32_t am_hal_pdm_int_status_get(bool bEnabledOnly);

#ifdef __cplusplus
}
#endif

#endif // AM_HAL_PDM_H

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
