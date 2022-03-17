/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "Driver_Common.h"

#define ARM_GPIO_API_VERSION ARM_DRIVER_VERSION_MAJOR_MINOR(1,0)  /* API version */

/*----- GPIO Logic Value -----*/
#define ARM_GPIO_LOGIC_ZERO                       0
#define ARM_GPIO_LOGIC_ONE                        1

/*----- GPIO Interrupt Type -----*/
#define ARM_GPIO_INTERRUPT_NONE                   0x00U   /* Disable Interrupt */
#define ARM_GPIO_INTERRUPT_RISING_EDGE            0x01U   /* Interrupt on Rising Edge */
#define ARM_GPIO_INTERRUPT_FALLING_EDGE           0x02U   /* Interrupt on Falling Edge */
#define ARM_GPIO_INTERRUPT_RISING_FALLING_EDGE    0x03U   /* Interrupt on Rising or Falling edge */
#define ARM_GPIO_INTERRUPT_LOGIC_ONE              0x04U   /* Interrupt on Logic Level One */
#define ARM_GPIO_INTERRUPT_LOGIC_ZERO             0x05U   /* Interrupt on Logic Level Zero */
#define ARM_GPIO_INTERRUPT_MAX_CONFIG_PARA        0x06U   /* Internal use and not used by user */

/*----- GPIO Control Codes: Interrupt -----*/
#define ARM_GPIO_CONTROL_INTERRUPT                (0x01U)
#define ARM_GPIO_INTERRUPT_DISABLE                (0x00U)
#define ARM_GPIO_INTERRUPT_ENABLE                 (0x01U)

typedef void (*ARM_GPIO_SignalEvent_t) (uint32_t pin);  ///< Pointer to \ref ARM_GPIO_SignalEvent : Signal GPIO Event.

/**
\brief GPIO Driver Capabilities.
*/
typedef struct _ARM_GPIO_CAPABILITIES {
  uint32_t irq            :  1;         ///< supports IRQ
  uint32_t reserved       : 31;         ///< Reserved (must be zero)
} ARM_GPIO_CAPABILITIES;

/**
\brief Access structure of the GPIO Driver.
*/
typedef struct _ARM_DRIVER_GPIO {
  ARM_DRIVER_VERSION    (*GetVersion)     (void);
  ARM_GPIO_CAPABILITIES (*GetCapabilities)(void);
  int32_t               (*Initialize)     (void);
  int32_t               (*Uninitialize)   (void);
  int32_t               (*PowerControl)   (ARM_POWER_STATE state);
  /// Init Pin As Output
  int32_t               (*InitPinAsOutput)(uint32_t pin, uint32_t output_logic);
  /// Init Pin as Input with or without interrupt enabled , with or without callback if interrupt is requested
  int32_t               (*InitPinAsInput)(uint32_t pin, uint32_t irq_type, ARM_GPIO_SignalEvent_t cb_event);
  /// Write pin with ARM_GPIO_LOGIC_[ONE|ZERO]
  int32_t               (*PinWrite) (uint32_t pin, uint32_t logic_value);
  /// Toggle specified Pin
  int32_t               (*PinToggle) (uint32_t pin);
  /// Read Logic value from pin. false stands for logic zero, true stands for logic one.
  bool                  (*PinRead) (uint32_t pin);
  /// Write selected pins with logic one or zero.  Example, pin0 and pin 4,  ored_pins = (0x01U << 0U) | (0x01 << 4U)
  int32_t               (*PortWrite) (uint32_t ored_pins, uint32_t logic_value);
  /// Toggle selected pins. Example, pin0 and pin 4,  ored_pins = (0x01U << 0U) | (0x01 << 4U)
  int32_t               (*PortToggle) (uint32_t ored_pins);
  /// Read all pins status for this GPIO interface.  use (read_value & (0x01U << 4)) to decide whether pin4 is logic one or logic zero
  uint32_t              (*PortRead)(void);
  /// Configuare the pin with field ARM_GPIO_CONTROL_[INTERRUPT] with value filled into arg.  values are defined following the ARM_GPIO_CONTROL_XXX.
  int32_t               (*Control)(uint32_t pin, uint32_t control, uint32_t arg);
} const ARM_DRIVER_GPIO;


#ifdef  __cplusplus
}
#endif

#endif /* DRIVER_GPIO_H_ */
