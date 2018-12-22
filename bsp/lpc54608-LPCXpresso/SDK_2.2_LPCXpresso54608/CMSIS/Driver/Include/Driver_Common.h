/* -----------------------------------------------------------------------------
 * Copyright (c) 2013-2014 ARM Ltd.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * $Date:        2. Jan 2014
 * $Revision:    V2.00
 *
 * Project:      Common Driver definitions
 * -------------------------------------------------------------------------- */

/* History:
 *  Version 2.00
 *    Changed prefix ARM_DRV -> ARM_DRIVER
 *    Added General return codes definitions
 *  Version 1.10
 *    Namespace prefix ARM_ added
 *  Version 1.00
 *    Initial release
 */

#ifndef __DRIVER_COMMON_H
#define __DRIVER_COMMON_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define ARM_DRIVER_VERSION_MAJOR_MINOR(major,minor) (((major) << 8) | (minor))

/**
\brief Driver Version
*/
typedef struct _ARM_DRIVER_VERSION {
  uint16_t api;                         ///< API version
  uint16_t drv;                         ///< Driver version
} ARM_DRIVER_VERSION;

/* General return codes */
#define ARM_DRIVER_OK                 0 ///< Operation succeeded 
#define ARM_DRIVER_ERROR             -1 ///< Unspecified error
#define ARM_DRIVER_ERROR_BUSY        -2 ///< Driver is busy
#define ARM_DRIVER_ERROR_TIMEOUT     -3 ///< Timeout occurred
#define ARM_DRIVER_ERROR_UNSUPPORTED -4 ///< Operation not supported
#define ARM_DRIVER_ERROR_PARAMETER   -5 ///< Parameter error
#define ARM_DRIVER_ERROR_SPECIFIC    -6 ///< Start of driver specific errors 

/**
\brief General power states
*/ 
typedef enum _ARM_POWER_STATE {
  ARM_POWER_OFF,                        ///< Power off: no operation possible
  ARM_POWER_LOW,                        ///< Low Power mode: retain state, detect and signal wake-up events
  ARM_POWER_FULL                        ///< Power on: full operation at maximum performance
} ARM_POWER_STATE;

#endif /* __DRIVER_COMMON_H */
