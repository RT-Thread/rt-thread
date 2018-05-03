/***************************************************************************//**
 * @file
 * @brief Dot matrix display Direct Driver for TFT SSD2119 "Generic" mode
 * @author Energy Micro AS
 * @version 2.0.1
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
#include <stdint.h>
#include "graphics/em_types.h"
#include "dmdif_ssd2119_ebi.h"
#include "dmd_ssd2119_registers.h"
#include "dmd_ssd2119.h"
#include "efm32.h"
#include "em_usart.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "tftspi.h"

/** Dimensions of the display */
DMD_DisplayGeometry dimensions =
{
  .xSize = 320,
  .ySize = 240,
  .xClipStart = 0,
  .yClipStart = 0,
  .clipWidth = 320,
  .clipHeight = 240,
};

/** FramePointer base address */
static volatile uint16_t *frameBuffer;

/* Local variables */
static uint32_t initialized = 0;
static uint16_t rcDriverOutputControl = 0;

/* Local function prototypes */
static uint16_t colorTransform24ToRGB565(uint8_t red, uint8_t green, uint8_t blue);

#if 0
static void colorTransformRGB565To24bpp(uint16_t color, uint8_t *red, uint8_t *green, uint8_t *blue);
#endif

/**************************************************************************//**
*  @brief
*  Transforms a 24bpp pixel data into an RGB565 pixel
*
*  @param red
*    8-bit red component of the pixel
*  @param green
*    8-bit green component of the pixel
*  @param blue
*    8-bit blue component of the pixel
*  @return
*    16-bit RGB565 value of pixel
******************************************************************************/
static uint16_t colorTransform24ToRGB565(uint8_t red, uint8_t green, uint8_t blue)
{
  /* Transform each color into 6 bits by dropping the 2 LSB */
  red   = red >> 3;
  green = green >> 2;
  blue  = blue >> 3;

  /* Put it together to one 18bpp color number */
  return (red << 11) | (green << 5) | blue;
}


/**************************************************************************//**
*  @brief
*  Transforms an 16-bit RGB565 pixel into a 24bpp pixel
*
*  @param[in] color
*    RGB565 16-bit color pixel
*  @param red
*    return value for red component of 24bpp pixel
*  @param green
*    return value for green component of 24bpp pixel
*  @param blue
*    return value for blue component of 24bpp pixel
******************************************************************************/
#if 0
static void colorTransformRGB565To24bpp(uint16_t color, uint8_t *red,
                                        uint8_t *green, uint8_t *blue)
{
  /* Get the individual colors out of the 18bpp number */
  uint8_t redValue   = (color & 0x0003F000) >> 12;
  uint8_t greenValue = (color & 0x00000FC0) >> 6;
  uint8_t blueValue  = (color & 0x0000003F);

  /* Convert each color to 8-bit */
  redValue   <<= 2;
  greenValue <<= 2;
  blueValue  <<= 2;

  *red   = redValue;
  *green = greenValue;
  *blue  = blueValue;

  return;
}
#endif

/**************************************************************************//**
*  @brief
*  Writes a value to a control register in the LCD controller
*
*  @param reg
*  The register that will be written to
*  @param data
*  The value to write to the register
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMDIF_writeReg(uint8_t reg, uint16_t data)
{
  SPI_TFT_WriteRegister(reg, data);

  return DMD_OK;
}


/**************************************************************************//**
*  @brief
*  Initializes the LCD display
*
*  @param cmdRegAddr
*     If set to 0, initialize SSD2119 for direct drive, if set to 1 update
*     frame buffer base pointer (offset to EBI bank) only
*  @param dataRegAddr
*     Address in memory for frame buffer base pointer
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMD_init(uint32_t cmdRegAddr, uint32_t dataRegAddr)
{
  uint16_t data;
  volatile uint32_t i;
  (void) cmdRegAddr;
  (void) dataRegAddr;

  /* Use data reg addr as pointer to frame buffer */
  frameBuffer = (uint16_t *) dataRegAddr;

  if(cmdRegAddr==1) return DMD_OK;

  SPI_TFT_Init();

  DMDIF_writeReg(DMD_SSD2119_VCOM_OTP_1, 0x0006);

  /* Oscillation driven DCLK */
#if 0
  data = DMD_SSD2119_OSCILLATION_START_OSCEN;
  DMDIF_writeReg(DMD_SSD2119_OSCILLATION_START, data);
#endif

  /* Display control */
  data = 0;
  // data |= DMD_SSD2119_DISPLAY_CONTROL_DTE;
  data |= DMD_SSD2119_DISPLAY_CONTROL_GON;
  data |= DMD_SSD2119_DISPLAY_CONTROL_D1;
  data |= DMD_SSD2119_DISPLAY_CONTROL_D0;
  DMDIF_writeReg(DMD_SSD2119_DISPLAY_CONTROL, data);

  /* Exit sleep mode */
  data = 0;
  DMDIF_writeReg(DMD_SSD2119_SLEEP_MODE_1, data);

  /* Wait */
  for (i = 0; i < 100000; i++);

  /* Display control */
  DMDIF_writeReg(DMD_SSD2119_DISPLAY_CONTROL, 0x33);

  /* Entry mode */

  data  = DMD_SSD2119_ENTRY_MODE_DFM_65K << DMD_SSD2119_ENTRY_MODE_DFM_SHIFT;
  data |= DMD_SSD2119_ENTRY_MODE_WMODE;
  data |= DMD_SSD2119_ENTRY_MODE_NOSYNC;
  data |= DMD_SSD2119_ENTRY_MODE_DMODE;
  data |= DMD_SSD2119_ENTRY_MODE_ID1;
  data |= DMD_SSD2119_ENTRY_MODE_ID0;

  DMDIF_writeReg(DMD_SSD2119_ENTRY_MODE, data);

  // DMDIF_writeReg(DMD_SSD2119_DRIVER_OUTPUT_CONTROL, 0x3aef);

  /* Generic Interface Control */
  // data  = DMD_SSD2119_GENERIC_INTERFACE_CONTROL_INVDEN;
  // DMDIF_writeReg(DMD_SSD2119_GENERIC_INTERFACE_CONTROL, data);

  /* Driver output control */
  data = 0;
  data                 |= DMD_SSD2119_DRIVER_OUTPUT_CONTROL_REV;
  data                 |= DMD_SSD2119_DRIVER_OUTPUT_CONTROL_GD;
  // data                 |= DMD_SSD2119_DRIVER_OUTPUT_CONTROL_TB;
  // data                 |= DMD_SSD2119_DRIVER_OUTPUT_CONTROL_SM;
  // data                 |= DMD_SSD2119_DRIVER_OUTPUT_CONTROL_RL;
  data                 |= ((DMD_VERTICAL_SIZE - 1) << DMD_SSD2119_DRIVER_OUTPUT_CONTROL_MUX_SHIFT);
  DMDIF_writeReg(DMD_SSD2119_DRIVER_OUTPUT_CONTROL, data);

  /* LCD AC control */
  data  = DMD_SSD2119_LCD_AC_CONTROL_BC;
  data |= DMD_SSD2119_LCD_AC_CONTROL_EOR;
  /* data |= DMD_SSD2119_LCD_AC_CONTROL_FLC; */
  DMDIF_writeReg(DMD_SSD2119_LCD_AC_CONTROL, data);

  /* RAM data write */
  data  = 0xff;
  DMDIF_writeReg(DMD_SSD2119_ACCESS_DATA, data);

  /* Mark graphics as initialized */
  initialized = 1;

  return DMD_OK;
}


/**************************************************************************//**
*  @brief
*  Get the dimensions of the display and of the current clipping area
*
*  @return
*  DMD_Dimensions structure containing the size of the display and the
*  clipping area
******************************************************************************/
EMSTATUS DMD_getDisplayGeometry(DMD_DisplayGeometry **geometry)
{
  if (!initialized)
  {
    return DMD_ERROR_DRIVER_NOT_INITIALIZED;
  }
  *geometry = &dimensions;

  return DMD_OK;
}

/**************************************************************************//**
*  @brief
*  Sets the clipping area. All coordinates given to writeData/writeColor/readData
*  are relative to this clipping area.
*
*  @param xStart
*  X coordinate of the upper left corner of the clipping area
*  @param yStart
*  Y coordinate of the upper left corner of the clipping area
*  @param width
*  Width of the clipping area
*  @param height
*  Height of the clipping area
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMD_setClippingArea(uint16_t xStart, uint16_t yStart,
uint16_t width, uint16_t height)
{
  if (!initialized)
  {
    return DMD_ERROR_DRIVER_NOT_INITIALIZED;
  }

  /* Check parameters */
  if (xStart + width > dimensions.xSize ||
      yStart + height > dimensions.ySize)
  {
    return DMD_ERROR_PIXEL_OUT_OF_BOUNDS;
  }

  if (width == 0 || height == 0)
  {
    return DMD_ERROR_EMPTY_CLIPPING_AREA;
  }

  /* Update the dimensions structure */
  dimensions.xClipStart = xStart;
  dimensions.yClipStart = yStart;
  dimensions.clipWidth  = width;
  dimensions.clipHeight = height;

  return DMD_OK;
}

/**************************************************************************//**
*  @brief
*  Draws pixels to the display
*
*  @param x
*  X coordinate of the first pixel to be written, relative to the clipping area
*  @param y
*  Y coordinate of the first pixel to be written, relative to the clipping area
*  @param data
*  Array containing the pixel data. Each 8-bit element in the array are one color
*  component of the pixel, so that 3 bytes represent one pixel. The pixels are
*  ordered by increasing x coordinate, after the last pixel of a row, the next
*  pixel will be the first pixel on the next row.
*  @param numPixels
*  Number of pixels to be written
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMD_writeData(uint16_t x, uint16_t y, const uint8_t data[],
                       uint32_t numPixels)
{
  uint8_t *dest = (uint8_t *)((uint32_t) frameBuffer +
                              (uint32_t) (y*dimensions.xSize*sizeof(uint16_t)) +
                              (uint32_t) (x*sizeof(uint16_t)));

  while(numPixels--)
  {
    *dest++ = *data++;
  }


  return DMD_OK;
}


/**************************************************************************//**
*  @brief
*  Reads data from display memory
*  DOESN'T WORK yet - TIMING ISSUE?
*
*  @param x
*  X coordinate of the first pixel to be read, relative to the clipping area
*  @param y
*  Y coordinate of the first pixel to be read, relative to the clipping area
*  @param data
*  Pointer to where the pixel data will be stored
*  @param numPixels
*  Number of pixels to be read
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMD_readData(uint16_t x, uint16_t y,
                      uint8_t data[], uint32_t numPixels)
{
  uint8_t *source = (uint8_t *)((uint32_t) frameBuffer +
                                (uint32_t) (y*dimensions.xSize*sizeof(uint16_t)) +
                                (uint32_t) (x*sizeof(uint16_t)));
  if (y > dimensions.ySize) return DMD_ERROR_PIXEL_OUT_OF_BOUNDS;

  while(numPixels--)
  {
    *data++ = *source++;
  }

  return DMD_OK;
}


/**************************************************************************//**
*  \brief
*  Draws a number of pixels of the same color to the display
*
*  @param x
*  X coordinate of the first pixel to be written, relative to the clipping area
*  @param y
*  Y coordinate of the first pixel to be written, relative to the clipping area
*  @param red
*  Red component of the color
*  @param green
*  Green component of the color
*  @param blue
*  Blue component of the color
*  @param numPixels
*  Number of pixels to be written
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMD_writeColor(uint16_t x, uint16_t y,
                        uint8_t red, uint8_t green, uint8_t blue, uint32_t numPixels)
{
  uint16_t color;
  uint16_t xStart = x;
  uint16_t *pixelPointer = (uint16_t *)
    ((uint32_t) frameBuffer +
     (uint32_t) ((y+dimensions.yClipStart)*dimensions.xSize*sizeof(uint16_t)) +
     (uint32_t) ((x+dimensions.xClipStart)*sizeof(uint16_t)));
  color = colorTransform24ToRGB565(red,green,blue);

  /* Draw the requied number of pixels */
  while(numPixels--)
  {
    x++;
    *pixelPointer++ = color;
    /* Increment line, start at the right x position inside clipping region */
    if (x>=dimensions.clipWidth)
    {
      x = xStart;
      pixelPointer = (uint16_t *)
        ((uint32_t) frameBuffer +
         (uint32_t) (((++y)+dimensions.yClipStart)*dimensions.xSize*sizeof(uint16_t)) +
         (uint32_t) ((xStart+dimensions.xClipStart)*sizeof(uint16_t)));
    }
  }

  return DMD_OK;
}


/**************************************************************************//**
*  @brief
*  Turns off the display and puts it into sleep mode
*  Does not turn off backlight
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMD_sleep(void)
{
  uint16_t data;

  if (!initialized)
  {
    return DMD_ERROR_DRIVER_NOT_INITIALIZED;
  }

  /* Put into sleep mode */
  data = DMD_SSD2119_SLEEP_MODE_1_SLP;
  DMDIF_writeReg(DMD_SSD2119_SLEEP_MODE_1, data);

  /* Turn off display */
  data = 0;
  DMDIF_writeReg(DMD_SSD2119_DISPLAY_CONTROL, 0x0000);

  /* Delay 1.5 frame */
  /*DMDIF_delay((1000 / DMD_FRAME_FREQUENCY) * 3 / 2);*/

  return DMD_OK;
}


/**************************************************************************//**
*  @brief
*  Wakes up the display from sleep mode
*
*  @return
*  DMD_OK on success, otherwise error code
******************************************************************************/
EMSTATUS DMD_wakeUp(void)
{
  uint16_t data;

  if (!initialized)
  {
    return DMD_ERROR_DRIVER_NOT_INITIALIZED;
  }

  /* Get out of sleep mode */
  data = 0;
  DMDIF_writeReg(DMD_SSD2119_SLEEP_MODE_1, data);

  /* Turn on display */
  data  = DMD_SSD2119_DISPLAY_CONTROL_DTE;
  data |= DMD_SSD2119_DISPLAY_CONTROL_GON;
  data |= DMD_SSD2119_DISPLAY_CONTROL_D1;
  data |= DMD_SSD2119_DISPLAY_CONTROL_D0;
  DMDIF_writeReg(DMD_SSD2119_DISPLAY_CONTROL, data);

  /* Delay 10 frames */
  /*DMDIF_delay((1000 / DMD_FRAME_FREQUENCY) * 10);*/

  return DMD_OK;
}


/**************************************************************************//**
*  @brief
*  Set horizontal and vertical flip mode of display controller
*
*  @param hor
*  Set to flip display horizontally
*
*  @param ver
*  Set to flip display vertically
*
*  @return
*  Returns DMD_OK is successful, error otherwise.
******************************************************************************/
EMSTATUS DMD_flipDisplay(int horizontal, int vertical)
{
  uint16_t reg;

  reg = rcDriverOutputControl;

  if (horizontal) reg &= ~DMD_SSD2119_DRIVER_OUTPUT_CONTROL_RL;
  else reg |= DMD_SSD2119_DRIVER_OUTPUT_CONTROL_RL;

  if (vertical) reg &= ~DMD_SSD2119_DRIVER_OUTPUT_CONTROL_TB;
  else reg |= DMD_SSD2119_DRIVER_OUTPUT_CONTROL_TB;

  rcDriverOutputControl = reg;
  DMDIF_writeReg(DMD_SSD2119_DRIVER_OUTPUT_CONTROL, rcDriverOutputControl);

  return DMD_OK;
}
