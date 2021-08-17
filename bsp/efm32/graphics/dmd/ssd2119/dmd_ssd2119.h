 /*************************************************************************//**
 * @file dmd_ssd2119.h
 * @brief Dot matrix display driver for LCD controller SSD2119
 * @author Energy Micro AS
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
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

#ifndef __DMD_SSD2119_H
#define __DMD_SSD2119_H

#include <stdint.h>
#include "graphics/em_types.h"
/* TODO: remove this and replace with include types and ecodes */
#define ECODE_DMD_BASE    0x00000000


/* Error codes */
/** Successful call */
#define DMD_OK                                  0x00000000
/** Driver not initialized correctly */
#define DMD_ERROR_DRIVER_NOT_INITIALIZED        (ECODE_DMD_BASE | 0x0001)
/** Driver is already initialized */
#define DMD_ERROR_DRIVER_ALREADY_INITIALIZED    (ECODE_DMD_BASE | 0x0002)
/** Length of data is larger than size of clip */
#define DMD_ERROR_TOO_MUCH_DATA                 (ECODE_DMD_BASE | 0x0003)
/** Pixel is outside current clipping area */
#define DMD_ERROR_PIXEL_OUT_OF_BOUNDS           (ECODE_DMD_BASE | 0x0004)
/** Clipping area is empty */
#define DMD_ERROR_EMPTY_CLIPPING_AREA           (ECODE_DMD_BASE | 0x0005)
/** Wrong device code */
#define DMD_ERROR_WRONG_DEVICE_CODE             (ECODE_DMD_BASE | 0x0006)
/** Memory error */
#define DMD_ERROR_MEMORY_ERROR                  (ECODE_DMD_BASE | 0x0007)
/** Error code expected, but didn't happen */
#define DMD_ERROR_NO_ERROR_CODE                 (ECODE_DMD_BASE | 0x0008)
/** Test run failed */
#define DMD_ERROR_TEST_FAILED                   (ECODE_DMD_BASE | 0x0009)


/** Frame update frequency of display */
#define DMD_FRAME_FREQUENCY    80
/** Horizontal size of the display */
#define DMD_HORIZONTAL_SIZE    320
/** Vertical size of the display */
#define DMD_VERTICAL_SIZE      240

/* Tests */
/** Device code test */
#define DMD_TEST_DEVICE_CODE         0x00000001
/** Memory test */
#define DMD_TEST_MEMORY              0x00000002
/** Parameter checks test */
#define DMD_TEST_PARAMETER_CHECKS    0x00000004
/** Color test */
#define DMD_TEST_COLORS              0x00000008
/** Clipping test */
#define DMD_TEST_CLIPPING            0x00000010

#define DMD_MEMORY_TEST_WIDTH        4
#define DMD_MEMORY_TEST_HEIGHT       3

/** @struct __DMD_DisplayGeometry
 *  @brief Dimensions of the display
 */
typedef struct __DMD_DisplayGeometry
{
  /** Horizontal size of the display, in pixels */
  uint16_t xSize;
  /** Vertical size of the display, in pixels */
  uint16_t ySize;
  /** X coordinate of the top left corner of the clipping area */
  uint16_t xClipStart;
  /** Y coordinate of the top left corner of the clipping area */
  uint16_t yClipStart;
  /** Width of the clipping area */
  uint16_t clipWidth;
  /** Height of the clipping area */
  uint16_t clipHeight;
} DMD_DisplayGeometry; /**< Typedef for display dimensions */

/** @struct __DMD_MemoryError
 *  @brief Information about a memory error
 */
typedef struct __DMD_MemoryError
{
  /** X coordinate of the address where the error happened */
  uint16_t x;
  /** Y coordinate of the address where the error happened */
  uint16_t y;
  /** The color that was written to the memory address */
  uint8_t  writtenColor[3];
  /** The color that was read from the memory address */
  uint8_t  readColor[3];
} DMD_MemoryError; /**< Typedef for memory error information */

/* Module prototypes */
EMSTATUS DMD_init(uint32_t cmdRegAddr, uint32_t dataRegAddr);
EMSTATUS DMD_getDisplayGeometry(DMD_DisplayGeometry **geometry);
EMSTATUS DMD_setClippingArea(uint16_t xStart, uint16_t yStart,
                             uint16_t width, uint16_t height);
EMSTATUS DMD_writeData(uint16_t x, uint16_t y,
                       const uint8_t data[], uint32_t numPixels);
EMSTATUS DMD_writeDataRLE(uint16_t x, uint16_t y, uint16_t xlen, uint16_t ylen,
                          const uint8_t *data);
EMSTATUS DMD_writeDataRLEFade(uint16_t x, uint16_t y, uint16_t xlen, uint16_t ylen,
                  const uint8_t *data,
                  int red, int green, int blue, int weight);
EMSTATUS DMD_readData(uint16_t x, uint16_t y,
                      uint8_t data[], uint32_t numPixels);
EMSTATUS DMD_writeColor(uint16_t x, uint16_t y, uint8_t red,
                        uint8_t green, uint8_t blue, uint32_t numPixels);
EMSTATUS DMD_writePixel(uint16_t x, uint16_t y, uint16_t color,
                        uint32_t numPixels);
EMSTATUS DMD_readPixel(uint16_t x, uint16_t y, uint16_t *color);
EMSTATUS DMD_sleep(void);
EMSTATUS DMD_wakeUp(void);

/* Test functions */
EMSTATUS DMD_testParameterChecks(void);
EMSTATUS DMD_testMemory(uint16_t x, uint16_t y,
                        uint32_t useClipWrite, uint32_t useClipRead,
                        DMD_MemoryError *memoryError);
EMSTATUS DMD_testMemory2(uint16_t x, uint16_t y,
                         uint32_t useClipWrite);
EMSTATUS DMD_testDeviceCode(void);
EMSTATUS DMD_testColors(uint32_t delay);
EMSTATUS DMD_testClipping(void);
EMSTATUS DMD_runTests(uint32_t tests, uint32_t *result);

EMSTATUS DMD_flipDisplay(int horizontal, int vertical);

#endif
