/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * Common low-level device handling (Events, IO buffers)
 * ----------------------------------------------------------------------------
 */
#ifndef JSDEVICES_H_
#define JSDEVICES_H_

#include "jsutils.h"
#include "platform_config.h"

typedef enum {
 // device type
 EV_NONE,
 EV_EXTI0,
 EV_EXTI1,
 EV_EXTI2,
 EV_EXTI3,
 EV_EXTI4,
 EV_EXTI5,
 EV_EXTI6,
 EV_EXTI7,
 EV_EXTI8,
 EV_EXTI9,
 EV_EXTI10,
 EV_EXTI11,
 EV_EXTI12,
 EV_EXTI13,
 EV_EXTI14,
 EV_EXTI15,
 EV_EXTI_MAX = EV_EXTI15,
 EV_USBSERIAL,
 EV_SERIAL1,
 EV_SERIAL2,
 EV_SERIAL3,
 EV_SERIAL4,
 EV_SERIAL5,
 EV_SERIAL6,
 EV_SERIAL_MAX = EV_SERIAL6,
 EV_SPI1,
 EV_SPI2,
 EV_SPI3,
 EV_SPI_MAX = EV_SPI3,
 EV_I2C1,
 EV_I2C2,
 EV_I2C3,
 EV_I2C_MAX = EV_I2C3,
 EV_DEVICE_MAX = EV_I2C_MAX,
 // EV_DEVICE_MAX should not be >64 - see DEVICE_INITIALISED_FLAGS
 // Also helps if we're under 32 so we can fit IOEventFlags into a byte
 EV_TYPE_MASK = NEXT_POWER_2(EV_DEVICE_MAX) - 1,
 EV_CHARS_MASK = 7 * NEXT_POWER_2(EV_DEVICE_MAX),
 // -----------------------------------------
 // if the pin we're watching is high, the handler sets this
 EV_EXTI_IS_HIGH = NEXT_POWER_2(EV_DEVICE_MAX),
} PACKED_FLAGS IOEventFlags;

#define DEVICE_IS_USART(X) (((X)>=EV_USBSERIAL)&& ((X)<=EV_SERIAL_MAX))
#define DEVICE_IS_SPI(X) (((X)>=EV_SPI1) || ((X)<=EV_SPI_MAX))
#define DEVICE_IS_I2C(X) (((X)>=EV_I2C1) || ((X)<=EV_I2C_MAX))
#define DEVICE_IS_EXTI(X) (((X)>=EV_EXTI0) || ((X)<=EV_EXTI_MAX))

#define IOEVENTFLAGS_GETTYPE(X) ((X)&EV_TYPE_MASK)
#define IOEVENTFLAGS_GETCHARS(X) ((((X)&EV_CHARS_MASK)>>5)+1)
#define IOEVENTFLAGS_SETCHARS(X,CHARS) ((X)=(((X)&(IOEventFlags)~EV_CHARS_MASK) | (((CHARS)-1)<<5)))
#define IOEVENT_MAXCHARS 8

typedef union {
  JsSysTime time; // time event occurred
  char chars[IOEVENT_MAXCHARS];
} PACKED_FLAGS IOEventData;

// IO Events - these happen when a pin changes
typedef struct IOEvent {
  IOEventFlags flags; // where this came from, and # of chars in it
  IOEventData data;
} PACKED_FLAGS IOEvent;

void jshPushIOEvent(IOEventFlags channel, JsSysTime time);
void jshPushIOWatchEvent(IOEventFlags channel); // push an even when a pin changes state
/// Push a single character event (for example USART RX)
void jshPushIOCharEvent(IOEventFlags channel, char charData);
/// Push many character events at once (for example USB RX)
static inline void jshPushIOCharEvents(IOEventFlags channel, char *data, unsigned int count) {
  // TODO: optimise me!
  unsigned int i;
  for (i=0;i<count;i++) jshPushIOCharEvent(channel, data[i]);
}
bool jshPopIOEvent(IOEvent *result); ///< returns true on success
/// Do we have any events pending? Will jshPopIOEvent return true?
bool jshHasEvents();

/// How many event blocks are left? compare this to IOBUFFERMASK
int jshGetEventsUsed();

/// Do we have enough space for N characters?
bool jshHasEventSpaceForChars(int n);

const char *jshGetDeviceString(IOEventFlags device);
IOEventFlags jshFromDeviceString(const char *device);

// ----------------------------------------------------------------------------
//                                                         DATA TRANSMIT BUFFER
/// Queue a character for transmission
void jshTransmit(IOEventFlags device, unsigned char data);
/// Wait for transmit to finish
void jshTransmitFlush();
/// Clear everything from a device
void jshTransmitClearDevice(IOEventFlags device);
/// Do we have anything we need to send?
bool jshHasTransmitData();
/// Try and get a character for transmission - could just return -1 if nothing
int jshGetCharToTransmit(IOEventFlags device);


/// Set whether the host should transmit or not
void jshSetFlowControlXON(IOEventFlags device, bool hostShouldTransmit);

#endif /* JSDEVICES_H_ */
