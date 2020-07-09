/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_LCDC_H__
#define __FSL_LCDC_H__

#include "fsl_common.h"

/*!
 * @addtogroup lpc_lcdc
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief LCDC driver version 2.0.0. */
#define LPC_LCDC_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*!@brief How many hardware cursors supports. */
#define LCDC_CURSOR_COUNT 4

/*!@brief LCD cursor image bits per pixel. */
#define LCDC_CURSOR_IMG_BPP 2

/*!@brief LCD 32x32 cursor image size in word(32-bit). */
#define LCDC_CURSOR_IMG_32X32_WORDS (32 * 32 * LCDC_CURSOR_IMG_BPP / (8 * sizeof(uint32_t)))

/*!@brief LCD 64x64 cursor image size in word(32-bit). */
#define LCDC_CURSOR_IMG_64X64_WORDS (64 * 64 * LCDC_CURSOR_IMG_BPP / (8 * sizeof(uint32_t)))

/*!@brief LCD palette size in words(32-bit). */
#define LCDC_PALETTE_SIZE_WORDS (ARRAY_SIZE(((LCD_Type *)0)->PAL))

/*!
 * @brief LCD sigal polarity flags.
 */
enum _lcdc_polarity_flags
{
    kLCDC_InvertVsyncPolarity = LCD_POL_IVS_MASK, /*!< Invert the VSYNC polarity, set to active low. */
    kLCDC_InvertHsyncPolarity = LCD_POL_IHS_MASK, /*!< Invert the HSYNC polarity, set to active low. */
    kLCDC_InvertClkPolarity = LCD_POL_IPC_MASK,   /*!< Invert the panel clock polarity, set to
                                                      drive data on falling edge. */
    kLCDC_InvertDePolarity = LCD_POL_IOE_MASK,    /*!< Invert the data enable (DE) polarity, set to active low. */
};

/*!
 * @brief LCD bits per pixel.
 */
typedef enum _lcdc_bpp
{
    kLCDC_1BPP = 0U,     /*!< 1 bpp. */
    kLCDC_2BPP = 1U,     /*!< 2 bpp. */
    kLCDC_4BPP = 2U,     /*!< 4 bpp. */
    kLCDC_8BPP = 3U,     /*!< 8 bpp. */
    kLCDC_16BPP = 4U,    /*!< 16 bpp. */
    kLCDC_24BPP = 5U,    /*!< 24 bpp, TFT panel only. */
    kLCDC_16BPP565 = 6U, /*!< 16 bpp, 5:6:5 mode. */
    kLCDC_12BPP = 7U,    /*!< 12 bpp, 4:4:4 mode. */
} lcdc_bpp_t;

/*!
 * @brief The types of display panel.
 */
typedef enum _lcdc_display
{
    kLCDC_DisplayTFT = LCD_CTRL_LCDTFT_MASK, /*!< Active matrix TFT panels with up to 24-bit bus interface. */
    kLCDC_DisplaySingleMonoSTN4Bit = LCD_CTRL_LCDBW_MASK, /*!< Single-panel monochrome STN (4-bit bus interface). */
    kLCDC_DisplaySingleMonoSTN8Bit =
        LCD_CTRL_LCDBW_MASK | LCD_CTRL_LCDMONO8_MASK, /*!< Single-panel monochrome STN (8-bit bus interface). */
    kLCDC_DisplayDualMonoSTN4Bit =
        LCD_CTRL_LCDBW_MASK | LCD_CTRL_LCDDUAL_MASK, /*!< Dual-panel monochrome STN (4-bit bus interface). */
    kLCDC_DisplayDualMonoSTN8Bit = LCD_CTRL_LCDBW_MASK | LCD_CTRL_LCDMONO8_MASK |
                                  LCD_CTRL_LCDDUAL_MASK,  /*!< Dual-panel monochrome STN (8-bit bus interface). */
    kLCDC_DisplaySingleColorSTN8Bit = 0U,                  /*!< Single-panel color STN (8-bit bus interface). */
    kLCDC_DisplayDualColorSTN8Bit = LCD_CTRL_LCDDUAL_MASK, /*!< Dual-panel coor STN (8-bit bus interface). */
} lcdc_display_t;

/*!
 * @brief LCD panel buffer data format.
 */
typedef enum _lcdc_data_format
{
    kLCDC_LittleEndian = 0U,                                   /*!< Little endian byte, little endian pixel. */
    kLCDC_BigEndian = LCD_CTRL_BEPO_MASK | LCD_CTRL_BEBO_MASK, /*!< Big endian byte, big endian pixel. */
    kLCDC_WinCeMode = LCD_CTRL_BEPO_MASK, /*!< little-endian byte, big-endian pixel for Windows CE mode. */
} lcdc_data_format_t;

/*!
 * @brief LCD configuration structure.
 */
typedef struct _lcdc_config
{
    uint32_t panelClock_Hz;  /*!< Panel clock in Hz. */
    uint16_t ppl;            /*!< Pixels per line, it must could be divided by 16. */
    uint8_t hsw;             /*!< HSYNC pulse width. */
    uint8_t hfp;             /*!< Horizontal front porch. */
    uint8_t hbp;             /*!< Horizontal back porch. */
    uint16_t lpp;            /*!< Lines per panal. */
    uint8_t vsw;             /*!< VSYNC pulse width. */
    uint8_t vfp;             /*!< Vrtical front porch. */
    uint8_t vbp;             /*!< Vertical back porch. */
    uint8_t acBiasFreq;      /*!< The number of line clocks between AC bias pin toggling. Only used for STN display. */
    uint16_t polarityFlags;  /*!< OR'ed value of @ref _lcdc_polarity_flags, used to contol the signal polarity. */
    bool enableLineEnd;      /*!< Enable line end or not, the line end is a positive pulse with 4 panel clock. */
    uint8_t lineEndDelay;    /*!< The panel clocks between the last pixel of line and the start of line end. */
    uint32_t upperPanelAddr; /*!< LCD upper panel base address, must be double-word(64-bit) align. */
    uint32_t lowerPanelAddr; /*!< LCD lower panel base address, must be double-word(64-bit) align. */
    lcdc_bpp_t bpp;           /*!< LCD bits per pixel. */
    lcdc_data_format_t dataFormat; /*!< Data format. */
    bool swapRedBlue;             /*!< Set true to use BGR format, set false to choose RGB format. */
    lcdc_display_t display;        /*!< The display type. */
} lcdc_config_t;

/*!
 * @brief LCD vertical compare interrupt mode.
 */
typedef enum _lcdc_vertical_compare_interrupt_mode
{
    kLCDC_StartOfVsync,       /*!< Generate vertical compare interrupt at start of VSYNC. */
    kLCDC_StartOfBackPorch,   /*!< Generate vertical compare interrupt at start of back porch. */
    kLCDC_StartOfActiveVideo, /*!< Generate vertical compare interrupt at start of active video. */
    kLCDC_StartOfFrontPorch,  /*!< Generate vertical compare interrupt at start of front porch. */
} lcdc_vertical_compare_interrupt_mode_t;

/*!
 * @brief LCD interrupts.
 */
enum _lcdc_interrupts
{
    kLCDC_CursorInterrupt = LCD_CRSR_INTMSK_CRSRIM_MASK,      /*!< Cursor image read finished interrupt. */
    kLCDC_FifoUnderflowInterrupt = LCD_INTMSK_FUFIM_MASK,     /*!< FIFO underflow interrupt. */
    kLCDC_BaseAddrUpdateInterrupt = LCD_INTMSK_LNBUIM_MASK,   /*!< Panel frame base address update interrupt. */
    kLCDC_VerticalCompareInterrupt = LCD_INTMSK_VCOMPIM_MASK, /*!< Vertical compare interrupt. */
    kLCDC_AhbErrorInterrupt = LCD_INTMSK_BERIM_MASK,          /*!< AHB master error interrupt. */
};

/*!
 * @brief LCD panel frame.
 */
typedef enum _lcdc_panel
{
    kLCDC_UpperPanel, /*!< Upper panel frame. */
    kLCDC_LowerPanel  /*!< Lower panel frame. */
} lcdc_panel_t;

/*!
 * @brief LCD hardware cursor size
 */
typedef enum _lcdc_cursor_size
{
    kLCDC_CursorSize32, /*!< 32x32 pixel cursor. */
    kLCDC_CursorSize64, /*!< 64x64 pixel cursor. */
} lcdc_cursor_size_t;

/*!
 * @brief LCD hardware cursor palette
 */
typedef struct _lcdc_cursor_palette
{
    uint8_t red;   /*!< Red color component. */
    uint8_t green; /*!< Red color component. */
    uint8_t blue;  /*!< Red color component. */
} lcdc_cursor_palette_t;

/*!
 * @brief LCD hardware cursor frame synchronization mode.
 */
typedef enum _lcdc_cursor_sync_mode
{
    kLCDC_CursorAsync, /*!< Cursor change will be displayed immediately. */
    kLCDC_CursorSync,  /*!< Cursor change will be displayed in next frame. */
} lcdc_cursor_sync_mode_t;

/*!
 * @brief LCD hardware cursor configuration structure.
 */
typedef struct _lcdc_cursor_config
{
    lcdc_cursor_size_t size;            /*!< Cursor size. */
    lcdc_cursor_sync_mode_t syncMode;   /*!< Cursor synchronization mode. */
    lcdc_cursor_palette_t palette0;     /*!< Cursor palette 0. */
    lcdc_cursor_palette_t palette1;     /*!< Cursor palette 1. */
    uint32_t *image[LCDC_CURSOR_COUNT]; /*!< Pointer to cursor image data. */
} lcdc_cursor_config_t;

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @name Initialization and Deinitialization
 * @{
 */

/*!
 * @brief Initialize the LCD module.
 *
 * @param base LCD peripheral base address.
 * @param config Pointer to configuration structure, see to @ref lcdc_config_t.
 * @param srcClock_Hz The LCD input clock (LCDCLK) frequency in Hz.
 * @retval kStatus_Success LCD is initialized successfully.
 * @retval kStatus_InvalidArgument Initlialize failed because of invalid argument.
 */
status_t LCDC_Init(LCD_Type *base, const lcdc_config_t *config, uint32_t srcClock_Hz);

/*!
 * @brief Deinitialize the LCD module.
 *
 * @param base LCD peripheral base address.
 */
void LCDC_Deinit(LCD_Type *base);

/*!
 * @brief Gets default pre-defined settings for initial configuration.
 *
 * This function initializes the configuration structure. The default values are:
 *
   @code
    config->panelClock_Hz = 0U;
    config->ppl = 0U;
    config->hsw = 0U;
    config->hfp = 0U;
    config->hbp = 0U;
    config->lpp = 0U;
    config->vsw = 0U;
    config->vfp = 0U;
    config->vbp = 0U;
    config->acBiasFreq = 1U;
    config->polarityFlags = 0U;
    config->enableLineEnd = false;
    config->lineEndDelay = 0U;
    config->upperPanelAddr = 0U;
    config->lowerPanelAddr = 0U;
    config->bpp = kLCDC_1BPP;
    config->dataFormat = kLCDC_LittleEndian;
    config->swapRedBlue = false;
    config->display = kLCDC_DisplayTFT;
   @endcode
 *
 * @param config Pointer to configuration structure.
 */
void LCDC_GetDefaultConfig(lcdc_config_t *config);

/* @} */

/*!
 * @name Start and stop
 * @{
 */

/*!
 * @brief Start to output LCD timing signal.
 *
 * The LCD power up sequence should be:
 * 1. Apply power to LCD, here all output signals are held low.
 * 2. When LCD power stablized, call @ref LCDC_Start to output the timing signals.
 * 3. Apply contrast voltage to LCD panel. Delay if the display requires.
 * 4. Call @ref LCDC_PowerUp.
 *
 * @param base LCD peripheral base address.
 */
static inline void LCDC_Start(LCD_Type *base)
{
    base->CTRL |= LCD_CTRL_LCDEN_MASK;
}

/*!
 * @brief Stop the LCD timing signal.
 *
 * The LCD power down sequence should be:
 * 1. Call @ref LCDC_PowerDown.
 * 2. Delay if the display requires. Disable contrast voltage to LCD panel.
 * 3. Call @ref LCDC_Stop to disable the timing signals.
 * 4. Disable power to LCD.
 *
 * @param base LCD peripheral base address.
 */
static inline void LCDC_Stop(LCD_Type *base)
{
    base->CTRL &= ~LCD_CTRL_LCDEN_MASK;
}

/*!
 * @brief Power up the LCD and output the pixel signal.
 *
 * @param base LCD peripheral base address.
 */
static inline void LCDC_PowerUp(LCD_Type *base)
{
    base->CTRL |= LCD_CTRL_LCDPWR_MASK;
}

/*!
 * @brief Power down the LCD and disable the output pixel signal.
 *
 * @param base LCD peripheral base address.
 */
static inline void LCDC_PowerDown(LCD_Type *base)
{
    base->CTRL &= ~LCD_CTRL_LCDPWR_MASK;
}

/* @} */

/*!
 * @name LCD control
 * @{
 */

/*!
 * @brief Sets panel frame base address
 *
 * @param base LCD peripheral base address.
 * @param panel Which panel to set.
 * @param addr Frame base address, must be doubleword(64-bit) aligned.
 */
void LCDC_SetPanelAddr(LCD_Type *base, lcdc_panel_t panel, uint32_t addr);

/*!
 * @brief Sets palette
 *
 * @param base LCD peripheral base address.
 * @param palette Pointer to the palette array.
 * @param count_words Length of the palette array to set (how many words), it should
 * not be larger than LCDC_PALETTE_SIZE_WORDS.
 */
void LCDC_SetPalette(LCD_Type *base, const uint32_t *palette, uint8_t count_words);

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Sets the vertical compare interrupt mode.
 *
 * @param base LCD peripheral base address.
 * @param mode The vertical compare interrupt mode.
 */
static inline void LCDC_SetVerticalInterruptMode(LCD_Type *base, lcdc_vertical_compare_interrupt_mode_t mode)
{
    base->CTRL = (base->CTRL & ~LCD_CTRL_LCDVCOMP_MASK) | LCD_CTRL_LCDVCOMP(mode);
}

/*!
 * @brief Enable LCD interrupts.
 *
 * Example to enable LCD base address update interrupt and vertical compare
 * interrupt:
 *
 * @code
   LCDC_EnableInterrupts(LCD, kLCDC_BaseAddrUpdateInterrupt | kLCDC_VerticalCompareInterrupt);
   @endcode
 *
 * @param base LCD peripheral base address.
 * @param mask Interrupts to enable, it is OR'ed value of @ref _lcdc_interrupts.
 */
void LCDC_EnableInterrupts(LCD_Type *base, uint32_t mask);

/*!
 * @brief Disable LCD interrupts.
 *
 * Example to disable LCD base address update interrupt and vertical compare
 * interrupt:
 *
 * @code
   LCDC_DisableInterrupts(LCD, kLCDC_BaseAddrUpdateInterrupt | kLCDC_VerticalCompareInterrupt);
   @endcode
 *
 * @param base LCD peripheral base address.
 * @param mask Interrupts to disable, it is OR'ed value of @ref _lcdc_interrupts.
 */
void LCDC_DisableInterrupts(LCD_Type *base, uint32_t mask);

/*!
 * @brief Get LCD interrupt pending status.
 *
 * Example:
 *
 * @code
   uint32_t status;

   status = LCDC_GetInterruptsPendingStatus(LCD);

   if (kLCDC_BaseAddrUpdateInterrupt & status)
   {
       // LCD base address update interrupt occurred.
   }

   if (kLCDC_VerticalCompareInterrupt & status)
   {
       // LCD vertical compare interrupt occurred.
   }
   @endcode
 *
 * @param base LCD peripheral base address.
 * @return Interrupts pending status, it is OR'ed value of @ref _lcdc_interrupts.
 */
uint32_t LCDC_GetInterruptsPendingStatus(LCD_Type *base);

/*!
 * @brief Get LCD enabled interrupt pending status.
 *
 * This function is similar with @ref LCDC_GetInterruptsPendingStatus, the only
 * difference is, this function only returns the pending status of the
 * interrupts that have been enabled using @ref LCDC_EnableInterrupts.
 *
 * @param base LCD peripheral base address.
 * @return Interrupts pending status, it is OR'ed value of @ref _lcdc_interrupts.
 */
uint32_t LCDC_GetEnabledInterruptsPendingStatus(LCD_Type *base);

/*!
 * @brief Clear LCD interrupts pending status.
 *
 * Example to clear LCD base address update interrupt and vertical compare
 * interrupt pending status:
 *
 * @code
   LCDC_ClearInterruptsStatus(LCD, kLCDC_BaseAddrUpdateInterrupt | kLCDC_VerticalCompareInterrupt);
   @endcode
 *
 * @param base LCD peripheral base address.
 * @param mask Interrupts to disable, it is OR'ed value of @ref _lcdc_interrupts.
 */
void LCDC_ClearInterruptsStatus(LCD_Type *base, uint32_t mask);

/* @} */

/*!
 * @name Hardware cursor
 * @{
 */

/*!
 * @brief Set the hardware cursor configuration
 *
 * This function should be called before enabling the hardware cursor.
 * It supports initializing multiple cursor images at a time when using
 * 32x32 pixels cursor.
 *
 * For example:
 *
 * @code
   uint32_t cursor0Img[LCDC_CURSOR_IMG_32X32_WORDS] = {...};
   uint32_t cursor2Img[LCDC_CURSOR_IMG_32X32_WORDS] = {...};

   lcdc_cursor_config_t cursorConfig;

   LCDC_CursorGetDefaultConfig(&cursorConfig);

   cursorConfig.image[0] = cursor0Img;
   cursorConfig.image[2] = cursor2Img;

   LCDC_SetCursorConfig(LCD, &cursorConfig);

   LCDC_ChooseCursor(LCD, 0);
   LCDC_SetCursorPosition(LCD, 0, 0);

   LCDC_EnableCursor(LCD);
   @endcode
 *
 * In this example, cursor 0 and cursor 2 image data are initialized, but cursor 1
 * and cursor 3 image data are not initialized because image[1] and image[2] are
 * all NULL. With this, application could initializes all cursor images it will
 * use at the beginning and call @ref LCDC_SetCursorImage directly to display the
 * one which it needs.
 *
 * @param base LCD peripheral base address.
 * @param config Pointer to the hardware cursor configuration structure.
 */
void LCDC_SetCursorConfig(LCD_Type *base, const lcdc_cursor_config_t *config);

/*!
 * @brief Get the hardware cursor default configuration
 *
 * The default configuration values are:
 *
 * @code
    config->size = kLCDC_CursorSize32;
    config->syncMode = kLCDC_CursorAsync;
    config->palette0.red = 0U;
    config->palette0.green = 0U;
    config->palette0.blue = 0U;
    config->palette1.red = 255U;
    config->palette1.green = 255U;
    config->palette1.blue = 255U;
    config->image[0] = (uint32_t *)0;
    config->image[1] = (uint32_t *)0;
    config->image[2] = (uint32_t *)0;
    config->image[3] = (uint32_t *)0;
   @endcode
 *
 * @param config Pointer to the hardware cursor configuration structure.
 */
void LCDC_CursorGetDefaultConfig(lcdc_cursor_config_t *config);

/*!
 * @brief Enable or disable the cursor.
 *
 * @param base LCD peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void LCDC_EnableCursor(LCD_Type *base, bool enable)
{
    if (enable)
    {
        base->CRSR_CTRL |= LCD_CRSR_CTRL_CRSRON_MASK;
    }
    else
    {
        base->CRSR_CTRL &= ~LCD_CRSR_CTRL_CRSRON_MASK;
    }
}

/*!
 * @brief Choose which cursor to display.
 *
 * When using 32x32 cursor, the number of cursors supports is @ref LCDC_CURSOR_COUNT.
 * When using 64x64 cursor, the LCD only supports one cursor.
 * This function selects which cursor to display when using 32x32 cursor.
 * When synchronization mode is @ref kLCDC_CursorSync, the change effects in the
 * next frame. When synchronization mode is @ref * kLCDC_CursorAsync, change effects
 * immediately.
 *
 * @param base LCD peripheral base address.
 * @param index Index of the cursor to display.
 * @note The function @ref LCDC_SetCursorPosition must be called after this function
 * to show the new cursor.
 */
static inline void LCDC_ChooseCursor(LCD_Type *base, uint8_t index)
{
    base->CRSR_CTRL = (base->CRSR_CTRL & ~LCD_CRSR_CTRL_CRSRNUM1_0_MASK) | LCD_CRSR_CTRL_CRSRNUM1_0(index);
}

/*!
 * @brief Set the position of cursor
 *
 * When synchronization mode is @ref kLCDC_CursorSync, position change effects
 * in the next frame. When synchronization mode is @ref kLCDC_CursorAsync,
 * position change effects immediately.
 *
 * @param base LCD peripheral base address.
 * @param positionX X ordinate of the cursor top-left measured in pixels
 * @param positionY Y ordinate of the cursor top-left measured in pixels
 */
void LCDC_SetCursorPosition(LCD_Type *base, int32_t positionX, int32_t positionY);

/*!
 * @brief Set the cursor image.
 *
 * The interrupt @ref kLCDC_CursorInterrupt indicates that last cursor pixel is
 * displayed. When the hardware cursor is enabled,
 *
 * @param base LCD peripheral base address.
 * @param size The cursor size.
 * @param index Index of the cursor to set when using 32x32 cursor.
 * @param image Pointer to the cursor image. When using 32x32 cursor, the image
 * size should be LCDC_CURSOR_IMG_32X32_WORDS. When using 64x64 cursor, the image
 * size should be LCDC_CURSOR_IMG_64X64_WORDS.
 */
void LCDC_SetCursorImage(LCD_Type *base, lcdc_cursor_size_t size, uint8_t index, const uint32_t *image);

/* @} */

#if defined(__cplusplus)
}
#endif

#endif /* __FSL_LCDC_H__ */
