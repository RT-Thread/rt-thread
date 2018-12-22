/**
 * \file
 *
 * \brief SENSORS_XPLAINED_BOARD board header file.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */


#ifndef _sensors_xplained_h_
#define _sensors_xplained_h_

/**
 * \defgroup group_common_boards_sensors_xplained Sensors Xplained Extension Boards
 *
 * This file contains definitions and services related to the features of the
 * SENSORS_XPLAINED_XXX Xplained boards.
 *
 * To use these boards, define EXT_BOARD=SENSORS_XPLAINED_XXX, where \c 'XXX'
 * is a place holder for the specific sensor extension board as defined in
 * the board.h file.  For example, \ref SENSORS_XPLAINED_INERTIAL_1 selects a
 * configuration supporting the Atmel Inertial Sensor Board #1.
 *
 * When this header file is included in a platform build, the
 * \ref SENSORS_XPLAINED_BOARD configuration constant will be defined so
 * that conditionally built pieces of platform functionality can be invoked
 * to make the sensor board usable to the system.  For example, the
 * platform board_init() routine can conditionally compile calls to
 * sensor_board_init().
 *
 * \{
 */

#include "xplained_headers.h"
#include "conf_board.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup atavrsb_config Sensors Xplained Extension Board Configuration
 * @brief
 * The extension board configuration defines constants identifying the sensors,
 * bus interface, I/O pin mappings, and sensor device signals from an Atmel
 * Sensor board (\p ATAVRSBPR1, \p ATAVARSBIN1, \p ATAVARSBIN2, and so on)
 * to the development platform.
 *
 * @sa atavrpb_config
 * @{
 */


/**
 * \name Common Sensor Service Configuration Constants
 *
 * \brief
 * This module defines \ref mems_sensor_api configuration constants based
 * upon a user-specified \b EXT_BOARD value.  The Sensor Service determines
 * which drivers and bus interface modules to use based upon these definitions.
 * When \b EXT_BOARD defines a valid Sensors Xplained board constant, a
 * catch-all constant named SENSORS_XPLAINED_BOARD is defined so that platform,
 * service, and other code can be conditionally configured without testing for
 * every particular Sensors Xplained board constant.
 *
 * All of the following boards are compatible with the Atmel Xplained MCU
 * boards provided the required I/O peripheral pin mapping has been added
 * and a call to the sensor_board_init() routine has been included in the
 * board_init() routine.
 *
 * \par ATAVRSBIN1 Inertial Sensor Board No. 1
 *
 *  This sensor board includes an InvenSense 3-axis gyro (ITG-3200), Bosch
 *  3-axis accelerometer (BMA150), and AKM 3-axis magnetometer (AK8975).
 *  These sensors are interfaced via a TWI master bus mapped to pins on the
 *  J1 I/O expansion header on an Xplained development platform.  When the
 *  EXT_BOARD value is set to \ref SENSORS_XPLAINED_INERTIAL_1, the following
 *  are defined:
 *
 *  - \c CONF_SENSOR_BUS_TWI
 *  - \c INCLUDE_AK8975
 *  - \c INCLUDE_BMA150
 *  - \c INCLUDE_ITG3200
 *
 * \par ATAVRSBIN2 Inertial Sensor Board No. 2
 *
 *  This sensor board includes an InvenSense 3-axis gyro (IMU-3000), Kionix
 *  3-axis accelerometer (KXTF9), and Honeywell 3-axis magnetometer (HMC5883).
 *  These sensors are interfaced via a TWI master bus mapped to pins on the
 *  J1 I/O expansion header on an Xplained development platform.  When the
 *  EXT_BOARD value is set to \ref SENSORS_XPLAINED_INERTIAL_2, the following
 *  are defined:
 *
 *  - \c CONF_SENSOR_BUS_TWI
 *  - \c INCLUDE_HMC5883L
 *  - \c INCLUDE_IMU3000
 *  - \c INCLUDE_KXTF9
 *
 * \par ATAVRSBPR1 Barometric Pressure Sensor Board No. 1
 *
 *  This sensor board includes a Bosch barometric pressure sensor (BMP085).
 *  This sensor is interfaced via a TWI master bus mapped to pins on the
 *  J1 I/O expansion header on an Xplained development platform.  When the
 *  EXT_BOARD value is set to \ref SENSORS_XPLAINED_PRESSURE_1, the following
 *  are defined:
 *
 *  - \c CONF_SENSOR_BUS_TWI
 *  - \c INCLUDE_BMP085
 *
 * \par ATAVRSBLP1 Ambient Light & IR Proximity Sensor Board No. 1
 *
 *  This sensor board includes an Osram IR light/proximity sensor (SFH7770).
 *  This sensor is interfaced via a TWI master bus mapped to pins on the
 *  J1 I/O expansion header on an Xplained development platform.  When the
 *  EXT_BOARD value is set to \ref SENSORS_XPLAINED_LIGHTPROX_1, the following
 *  are defined:
 *
 *  - \c CONF_SENSOR_BUS_TWI
 *  - \c INCLUDE_SFH7770
 *
 *  The following list summarizes available sensor service configuration
 *  constants that are specified by board configurations defined in this
 *  module.
 *  @{
 */
#define SENSORS_XPLAINED_BOARD

#if (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_1)
#   define CONF_SENSOR_BUS_TWI
#   define INCLUDE_AK8975
#   define INCLUDE_BMA150
#   define INCLUDE_ITG3200
#elif (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_2)
#   define CONF_SENSOR_BUS_TWI
#   define INCLUDE_HMC5883L
#   define INCLUDE_IMU3000
#   define INCLUDE_KXTF9
#elif (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_A1)
#   define CONF_SENSOR_BUS_TWI
#   define INCLUDE_AK8975
#   define INCLUDE_IMU3000
#   define INCLUDE_KXTF9
#elif (EXT_BOARD == SENSORS_XPLAINED_PRESSURE_1)
#   define CONF_SENSOR_BUS_TWI
#   define INCLUDE_BMP085
#elif (EXT_BOARD == SENSORS_XPLAINED_LIGHTPROX_1)
#   define CONF_SENSOR_BUS_TWI
#   define INCLUDE_SFH7770
#elif (EXT_BOARD == SENSORS_XPLAINED_BREADBOARD)
#   define CONF_SENSOR_BUS_TWI
#   define INCLUDE_BMA222
#else
#   undef SENSORS_XPLAINED_BOARD
#   warning "The EXT_BOARD constant does not define a Sensors Xplained board."
#endif
// @}


/*! \name Xplained Board J1 Connector Pin Mapping
 *
 * \internal
 * These constants map AVR & AVR32 ports to pins on the Xplained board J1
 * connector where pins on the 10-pin header correspond to the following
 * functions:
 *
 * \code

	      10-pin Header           Function
	  -------------------------------------------
	      Pin 1                   SDA
	      Pin 2                   SCL
	      Pin 3                   RXD
	      Pin 4                   TXD
	      Pin 5                   SS
	      Pin 6                   MOSI
	      Pin 7                   MISO
	      Pin 8                   SCK

\endcode
 * @{
 */
#define SENSOR_BOARD_PIN1           XPLD_HEADER_J1_PIN1
#define SENSOR_BOARD_PIN2           XPLD_HEADER_J1_PIN2
#define SENSOR_BOARD_PIN3           XPLD_HEADER_J1_PIN3
#define SENSOR_BOARD_PIN4           XPLD_HEADER_J1_PIN4
#define SENSOR_BOARD_PIN5           XPLD_HEADER_J1_PIN5
#define SENSOR_BOARD_PIN6           XPLD_HEADER_J1_PIN6
#define SENSOR_BOARD_PIN7           XPLD_HEADER_J1_PIN7
#define SENSOR_BOARD_PIN8           XPLD_HEADER_J1_PIN8

#if XMEGA
#   define SENSOR_BOARD_PORT        XPLD_HEADER_J1_PORT
#   define SENSOR_BOARD_PORT_vect   XPLD_HEADER_J1_INT0_vect
#endif
// @}


/*! \name Sensor Device Interrupt Routing
 *
 * \internal
 * The following constants map I/O expansion header pins that are used as
 * sensor event signal inputs to the MCU interrupt controller lines and IRQ
 * numbers.
 *
 * These definitions are provided as a board-level description for the
 * sensor drivers and are not used directly in sensor service client
 * applications.
 * @{
 */
#define INVALID_IRQ_NUMBER          ((unsigned int) -1)

#if UC3
#    define SENSOR_PIN1_IRQ         (AVR32_GPIO_IRQ_0 + (SENSOR_BOARD_PIN1 / 8))
#    define SENSOR_PIN2_IRQ         (AVR32_GPIO_IRQ_0 + (SENSOR_BOARD_PIN2 / 8))
#    define SENSOR_PIN3_IRQ         (AVR32_GPIO_IRQ_0 + (SENSOR_BOARD_PIN3 / 8))
#    define SENSOR_PIN4_IRQ         (AVR32_GPIO_IRQ_0 + (SENSOR_BOARD_PIN4 / 8))
#    define SENSOR_PIN5_IRQ         (AVR32_GPIO_IRQ_0 + (SENSOR_BOARD_PIN5 / 8))
#    define SENSOR_PIN6_IRQ         (AVR32_GPIO_IRQ_0 + (SENSOR_BOARD_PIN6 / 8))
#    define SENSOR_PIN7_IRQ         (AVR32_GPIO_IRQ_0 + (SENSOR_BOARD_PIN7 / 8))
#    define SENSOR_PIN8_IRQ         (AVR32_GPIO_IRQ_0 + (SENSOR_BOARD_PIN8 / 8))
#else
#    define SENSOR_PIN1_IRQ         (INVALID_IRQ_NUMBER)
#    define SENSOR_PIN2_IRQ         (INVALID_IRQ_NUMBER)
#    define SENSOR_PIN3_IRQ         (INVALID_IRQ_NUMBER)
#    define SENSOR_PIN4_IRQ         (INVALID_IRQ_NUMBER)
#    define SENSOR_PIN5_IRQ         (INVALID_IRQ_NUMBER)
#    define SENSOR_PIN6_IRQ         (INVALID_IRQ_NUMBER)
#    define SENSOR_PIN7_IRQ         (INVALID_IRQ_NUMBER)
#    define SENSOR_PIN8_IRQ         (INVALID_IRQ_NUMBER)
#endif

#ifdef XPLD_HEADER_J1_PIN1_EIC_LINE
#    define SENSOR_PIN1_EIC_LINE    XPLD_HEADER_J1_PIN1_EIC_LINE
#    define SENSOR_PIN1_EIC_IRQ     XPLD_HEADER_J1_PIN1_EIC_IRQ
#    define SENSOR_PIN1_EIC_PIN     XPLD_HEADER_J1_PIN1_EIC_PIN
#    define SENSOR_PIN1_EIC_FUNC    XPLD_HEADER_J1_PIN1_EIC_FUNC
#endif

#ifdef XPLD_HEADER_J1_PIN2_EIC_LINE
#    define SENSOR_PIN2_EIC_LINE    XPLD_HEADER_J1_PIN2_EIC_LINE
#    define SENSOR_PIN2_EIC_IRQ     XPLD_HEADER_J1_PIN2_EIC_IRQ
#    define SENSOR_PIN2_EIC_PIN     XPLD_HEADER_J1_PIN2_EIC_PIN
#    define SENSOR_PIN2_EIC_FUNC    XPLD_HEADER_J1_PIN2_EIC_FUNC
#endif

#ifdef XPLD_HEADER_J1_PIN3_EIC_LINE
#    define SENSOR_PIN3_EIC_LINE    XPLD_HEADER_J1_PIN3_EIC_LINE
#    define SENSOR_PIN3_EIC_IRQ     XPLD_HEADER_J1_PIN3_EIC_IRQ
#    define SENSOR_PIN3_EIC_PIN     XPLD_HEADER_J1_PIN3_EIC_PIN
#    define SENSOR_PIN3_EIC_FUNC    XPLD_HEADER_J1_PIN3_EIC_FUNC
#endif

#ifdef XPLD_HEADER_J1_PIN4_EIC_LINE
#    define SENSOR_PIN4_EIC_LINE    XPLD_HEADER_J1_PIN4_EIC_LINE
#    define SENSOR_PIN4_EIC_IRQ     XPLD_HEADER_J1_PIN4_EIC_IRQ
#    define SENSOR_PIN4_EIC_PIN     XPLD_HEADER_J1_PIN4_EIC_PIN
#    define SENSOR_PIN4_EIC_FUNC    XPLD_HEADER_J1_PIN4_EIC_FUNC
#endif

#ifdef XPLD_HEADER_J1_PIN5_EIC_LINE
#    define SENSOR_PIN5_EIC_LINE    XPLD_HEADER_J1_PIN5_EIC_LINE
#    define SENSOR_PIN5_EIC_IRQ     XPLD_HEADER_J1_PIN5_EIC_IRQ
#    define SENSOR_PIN5_EIC_PIN     XPLD_HEADER_J1_PIN5_EIC_PIN
#    define SENSOR_PIN5_EIC_FUNC    XPLD_HEADER_J1_PIN5_EIC_FUNC
#endif

#ifdef XPLD_HEADER_J1_PIN6_EIC_LINE
#    define SENSOR_PIN6_EIC_LINE    XPLD_HEADER_J1_PIN6_EIC_LINE
#    define SENSOR_PIN6_EIC_IRQ     XPLD_HEADER_J1_PIN6_EIC_IRQ
#    define SENSOR_PIN6_EIC_PIN     XPLD_HEADER_J1_PIN6_EIC_PIN
#    define SENSOR_PIN6_EIC_FUNC    XPLD_HEADER_J1_PIN6_EIC_FUNC
#endif

#ifdef XPLD_HEADER_J1_PIN7_EIC_LINE
#    define SENSOR_PIN7_EIC_LINE    XPLD_HEADER_J1_PIN7_EIC_LINE
#    define SENSOR_PIN7_EIC_IRQ     XPLD_HEADER_J1_PIN7_EIC_IRQ
#    define SENSOR_PIN7_EIC_PIN     XPLD_HEADER_J1_PIN7_EIC_PIN
#    define SENSOR_PIN7_EIC_FUNC    XPLD_HEADER_J1_PIN7_EIC_FUNC
#endif

#ifdef XPLD_HEADER_J1_PIN8_EIC_LINE
#    define SENSOR_PIN8_EIC_LINE    XPLD_HEADER_J1_PIN8_EIC_LINE
#    define SENSOR_PIN8_EIC_IRQ     XPLD_HEADER_J1_PIN8_EIC_IRQ
#    define SENSOR_PIN8_EIC_PIN     XPLD_HEADER_J1_PIN8_EIC_PIN
#    define SENSOR_PIN8_EIC_FUNC    XPLD_HEADER_J1_PIN8_EIC_FUNC
#endif
// @}


/*! \name Sensor Device I/O Pins
 *
 * \internal
 * The following constants specify I/O expansion header pins that are used as
 * sensor event signal inputs to the MCU and, in some cases, control signal
 * outputs from the MCU to the sensor device.  For example, the \c BMP085
 * pressure sensor on the \c ATAVRSBPR1 board provides a pressure sample
 * End-of-Conversion (EOC) input signal to the MCU and a device "master clear"
 * and reset signal (XCLR) output from the MCU to the sensor.
 *
 * These definitions are provided as a board-level description for the
 * sensor drivers and are not used directly in sensor service client
 * applications.
 * @{
 */
#if (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_1)
#   define ak8975_sigint            (SENSOR_BOARD_PIN3)
#   define bma150_sigint            (SENSOR_BOARD_PIN4)
#   define itg3200_sigint           (SENSOR_BOARD_PIN5)
#   define ak8975_sigout            (INVALID_PIN_NUMBER)
#   define bma150_sigout            (INVALID_PIN_NUMBER)
#   define itg3200_sigout           (INVALID_PIN_NUMBER)
#elif (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_2)
#   define hmc5883l_sigint          (SENSOR_BOARD_PIN3)
#   define kxtf9_sigint             (SENSOR_BOARD_PIN4)
#   define imu3000_sigint           (SENSOR_BOARD_PIN5)
#   define hmc5883l_sigout          (INVALID_PIN_NUMBER)
#   define kxtf9_sigout             (INVALID_PIN_NUMBER)
#   define imu3000_sigout           (INVALID_PIN_NUMBER)
#elif (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_A1)
#   define ak8975_sigint            (SENSOR_BOARD_PIN3)
#   define kxtf9_sigint             (SENSOR_BOARD_PIN4)
#   define imu3000_sigint           (SENSOR_BOARD_PIN5)
#   define ak8975_sigout            (INVALID_PIN_NUMBER)
#   define kxtf9_sigout             (INVALID_PIN_NUMBER)
#   define imu3000_sigout           (INVALID_PIN_NUMBER)
#elif (EXT_BOARD == SENSORS_XPLAINED_PRESSURE_1)
#   define bmp085_sigint            (SENSOR_BOARD_PIN4)
#   define bmp085_sigout            (SENSOR_BOARD_PIN3)
#elif (EXT_BOARD == SENSORS_XPLAINED_LIGHTPROX_1)
#   define sfh7770_sigint           (SENSOR_BOARD_PIN3)
#   define sfh7770_sigout           (INVALID_PIN_NUMBER)
#elif (EXT_BOARD == SENSORS_XPLAINED_BREADBOARD)
#   define bma222_sigint            (SENSOR_BOARD_PIN4)
#   define bma222_sigout            (INVALID_PIN_NUMBER)
#endif
// @}


/*! \name Sensor Physical Orientation
 *
 * \internal
 * The following constants describe the physical orientation of multi-axis
 * sensor devices, relative to the standardized axes of the sensors API.
 * This allows for devices to be mounted in different configurations but
 * provide consistent output to applications in terms of each axis.
 * For each sensor device, the orientation description consists of a set
 * of three values in X, Y, Z order, which specify which sensor axis and sign
 * corresponds to the standard axis positive direction.
 *
 * These definitions are provided as a board-level description for the
 * sensor drivers and are not used directly in sensor service client
 * applications.
 * @{
 */
#define NON_DIRECTIONAL_DEV         {AXIS_NONE, AXIS_NONE, AXIS_NONE}

#if (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_1)
#   define ak8975_orientation       {AXIS_X_NEG, AXIS_Y_POS, AXIS_Z_NEG}
#   define bma150_orientation       {AXIS_X_POS, AXIS_Y_POS, AXIS_Z_POS}
#   define itg3200_orientation      {AXIS_X_POS, AXIS_Y_POS, AXIS_Z_POS}
#elif (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_2)
#   define hmc5883l_orientation     {AXIS_X_POS, AXIS_Y_POS, AXIS_Z_POS}
#   define kxtf9_orientation        {AXIS_X_POS, AXIS_Y_POS, AXIS_Z_POS}
#   define imu3000_orientation      {AXIS_X_POS, AXIS_Y_POS, AXIS_Z_POS}
#elif (EXT_BOARD == SENSORS_XPLAINED_INERTIAL_A1)
#   define ak8975_orientation       {AXIS_X_NEG, AXIS_Y_POS, AXIS_Z_NEG}
#   define kxtf9_orientation        {AXIS_X_POS, AXIS_Y_POS, AXIS_Z_POS}
#   define imu3000_orientation      {AXIS_X_POS, AXIS_Y_POS, AXIS_Z_POS}
#elif (EXT_BOARD == SENSORS_XPLAINED_PRESSURE_1)
#   define bmp085_orientation       NON_DIRECTIONAL_DEV
#elif (EXT_BOARD == SENSORS_XPLAINED_LIGHTPROX_1)
#   define sfh7770_orientation      NON_DIRECTIONAL_DEV
#elif (EXT_BOARD == SENSORS_XPLAINED_BREADBOARD)
#   define bma222_orientation       {AXIS_X_POS, AXIS_Y_POS, AXIS_Z_POS}
#endif
// @}

/** @} */ // atavrsb_config group


//! \brief Sensor Pin Interrupt Handler Callback Type

typedef void (*SENSOR_IRQ_HANDLER)(volatile void *);


/*! \brief Initialize sensor board target resources
 *
 * This function is called to ensure proper initialization
 * of sensor hardware connected to an Atmel AVR32 or XMEGA platform.
 *
 * \return  Nothing.
 */
extern void sensor_board_init(void);

/*! \brief Install a sensor interrupt handler
 *
 * The Sensors Xplained add-on boards route sensor device I/O pins to GPIO
 * pins for the MCU installed on an Xplained platform board.  Some sensor
 * devices can be configured to generate interrupts on these pins to indicate
 * the availability of new sensor data or the occurrence of configurable
 * events related to sensor data thresholds, for example.
 *
 * This routine will enable interrupts on the GPIO pin specified by the
 * \c gpio_pin parameter and call a user-defined callback \c handler when an
 * interrupt is detected.  The \c arg parameter is used to pass the address
 * of user-defined input and output storage for the callback handler.  Calling
 * the routine with the \c handler parameter set to 0 (the NULL pointer) will
 * fail with \c false returned to the caller.
 *
 * \param   gpio_pin    Board-specific GPIO pin interface to the MCU.
 * \param   handler     The address of a driver-defined interrupt handler.
 * \param   arg         An optional address passed to the interrupt handler.
 *
 * \return  bool        true if the call succeeds, else false.
 */
extern bool sensor_board_irq_connect
	(uint32_t gpio_pin, SENSOR_IRQ_HANDLER handler, void *arg);


#ifdef __cplusplus
}
#endif

/**
 * \}
 */

#endif /* _sensors_xplained_h_ */
