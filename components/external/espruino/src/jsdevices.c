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
#include "jsdevices.h"
#include "jsparse.h"
#include "jsinteractive.h"

#ifdef LINUX
 #include <signal.h>
#endif//LINUX
#ifdef USE_TRIGGER
#include "trigger.h"
#endif
#ifdef USE_CC3000
#include "board_spi.h"
#endif
// ----------------------------------------------------------------------------
//                                                                     BUFFERS

// ----------------------------------------------------------------------------
//                                                         DATA TRANSMIT BUFFER
typedef struct {
  IOEventFlags flags; // Where this data should be transmitted
  unsigned char data;         // data to transmit
} PACKED_FLAGS TxBufferItem;

TxBufferItem txBuffer[TXBUFFERMASK+1];
volatile unsigned char txHead=0, txTail=0;
// ----------------------------------------------------------------------------

// Queue a character for transmission
void jshTransmit(IOEventFlags device, unsigned char data) {
#ifdef RT_USING_JS
    rt_device_write(rt_console_get_device(), 0, &data, 1);
#else
#ifndef LINUX
#ifdef USB
  if (device==EV_USBSERIAL && !jshIsUSBSERIALConnected()) {
    jshTransmitClearDevice(EV_USBSERIAL); // clear out stuff already waiting
    return;
  }
#endif
  if (device==EV_NONE) return;
  unsigned char txHeadNext = (txHead+1)&TXBUFFERMASK;
  if (txHeadNext==txTail) {
    jsiSetBusy(BUSY_TRANSMIT, true);
    while (txHeadNext==txTail) {
      // wait for send to finish as buffer is about to overflow
#ifdef USB
      // just in case USB was unplugged while we were waiting!
      if (!jshIsUSBSERIALConnected()) jshTransmitClearDevice(EV_USBSERIAL);
#endif
    }
    jsiSetBusy(BUSY_TRANSMIT, false);
  }
  txBuffer[txHead].flags = device;
  txBuffer[txHead].data = (char)data;
  txHead = txHeadNext;

  jshUSARTKick(device); // set up interrupts if required

#else // if PC, just put to stdout
  if (device==DEFAULT_CONSOLE_DEVICE) {
    fputc(data, stdout);
    fflush(stdout);
  }
#endif
#endif
}

// Try and get a character for transmission - could just return -1 if nothing
int jshGetCharToTransmit(IOEventFlags device) {
  unsigned char ptr = txTail;
  while (txHead != ptr) {
    if (IOEVENTFLAGS_GETTYPE(txBuffer[ptr].flags) == device) {
      unsigned char data = txBuffer[ptr].data;
      if (ptr != txTail) { // so we weren't right at the back of the queue
        // we need to work back from ptr (until we hit tail), shifting everything forwards
        unsigned char this = ptr;
        unsigned char last = (unsigned char)((this+TXBUFFERMASK)&TXBUFFERMASK);
        while (this!=txTail) { // if this==txTail, then last is before it, so stop here
          txBuffer[this] = txBuffer[last];
          this = last;
          last = (unsigned char)((this+TXBUFFERMASK)&TXBUFFERMASK);
        }
      }
      txTail = (unsigned char)((txTail+1)&TXBUFFERMASK); // advance the tail
      return data; // return data
    }
    ptr = (unsigned char)((ptr+1)&TXBUFFERMASK);
  }
  return -1; // no data :(
}

void jshTransmitFlush() {
  jsiSetBusy(BUSY_TRANSMIT, true);
  while (jshHasTransmitData()) ; // wait for send to finish
  jsiSetBusy(BUSY_TRANSMIT, false);
}

// Clear everything from a device
void jshTransmitClearDevice(IOEventFlags device) {
  while (jshGetCharToTransmit(device)>=0);
}

bool jshHasTransmitData() {
#ifndef LINUX
  return txHead != txTail;
#else
  return false;
#endif
}

// ----------------------------------------------------------------------------
//                                                              IO EVENT BUFFER
IOEvent ioBuffer[IOBUFFERMASK+1];
volatile unsigned char ioHead=0, ioTail=0;
// ----------------------------------------------------------------------------


void jshIOEventOverflowed() {
  // Error here - just light LED as we can't do much else right now
}


void jshPushIOCharEvent(IOEventFlags channel, char charData) {
  if (charData==3 && channel==jsiGetConsoleDevice()) {
    // Ctrl-C - force interrupt
#ifdef LINUX
    raise(SIGINT);
#endif
    jspSetInterrupted(true);
    return;
  }
  if (DEVICE_IS_USART(channel) && jshGetEventsUsed() > IOBUFFER_XOFF)
    jshSetFlowControlXON(channel, false);
  // Check for existing buffer (we must have at least 2 in the queue to avoid dropping chars though!)
  unsigned char nextTail = (unsigned char)((ioTail+1) & IOBUFFERMASK);
  if (ioHead!=ioTail && ioHead!=nextTail) {
    // we can do this because we only read in main loop, and we're in an interrupt here
    unsigned char lastHead = (unsigned char)((ioHead+IOBUFFERMASK) & IOBUFFERMASK); // one behind head
    if (IOEVENTFLAGS_GETTYPE(ioBuffer[lastHead].flags) == channel &&
        IOEVENTFLAGS_GETCHARS(ioBuffer[lastHead].flags) < IOEVENT_MAXCHARS) {
      // last event was for this event type, and it has chars left
      unsigned char c = (unsigned char)IOEVENTFLAGS_GETCHARS(ioBuffer[lastHead].flags);
      ioBuffer[lastHead].data.chars[c] = charData;
      IOEVENTFLAGS_SETCHARS(ioBuffer[lastHead].flags, c+1);
      return;
    }
  }
  // Make new buffer
  unsigned char nextHead = (unsigned char)((ioHead+1) & IOBUFFERMASK);
  if (ioTail == nextHead) {
    jshIOEventOverflowed();
    return; // queue full - dump this event!
  }
  ioBuffer[ioHead].flags = channel;
  IOEVENTFLAGS_SETCHARS(ioBuffer[ioHead].flags, 1);
  ioBuffer[ioHead].data.chars[0] = charData;
  ioHead = nextHead;
}

void jshPushIOWatchEvent(IOEventFlags channel) {
 JsSysTime time = jshGetSystemTime();
 bool state = jshGetWatchedPinState(channel);

/* // This is some simple debounce code - however it requires that the event
   // is not taken out of ioBuffer by the main thread, which will require
   // a bit of fiddling in jsinteractive.c. In fact it might be worth just
   // doing debounce outside of the interrupt
   if (true) { // debounce
   // scan back and see if we have an event for this pin
   unsigned char prevHead = ioHead;
   while (prevHead!=ioTail && (IOEVENTFLAGS_GETTYPE(ioBuffer[prevHead].flags)!=channel))
     prevHead = (unsigned char)((prevHead+IOBUFFERMASK) & IOBUFFERMASK); // step back
   // if we have an event
   if (prevHead!=ioTail  && (IOEVENTFLAGS_GETTYPE(ioBuffer[prevHead].flags)==channel)) {
     // just use it (with the same timestamp)...
     ioBuffer[prevHead].flags = channel | (state?EV_EXTI_IS_HIGH:0);
     return;
   }
 }*/

#ifdef USE_TRIGGER
  if (trigHandleEXTI(channel | (state?EV_EXTI_IS_HIGH:0), time))
    return;
#endif
#ifdef USE_CC3000
  IOEvent event;
  event.flags = channel;
  if (!state && jshIsEventForPin(&event, WLAN_IRQ_PIN)) {
    cc3000_irq_handler();
  }
#endif
 // Otherwise add this event
 jshPushIOEvent(channel | (state?EV_EXTI_IS_HIGH:0), time);
}

void jshPushIOEvent(IOEventFlags channel, JsSysTime time) {

  unsigned char nextHead = (unsigned char)((ioHead+1) & IOBUFFERMASK);
  if (ioTail == nextHead) {
    jshIOEventOverflowed();
    return; // queue full - dump this event!
  }
  ioBuffer[ioHead].flags = channel;
  ioBuffer[ioHead].data.time = time;
  ioHead = nextHead;
}

// returns true on success
bool jshPopIOEvent(IOEvent *result) {
  if (ioHead==ioTail) return false;
  *result = ioBuffer[ioTail];
  ioTail = (unsigned char)((ioTail+1) & IOBUFFERMASK);
  return true;
}

bool jshHasEvents() {
  return ioHead!=ioTail;
}

int jshGetEventsUsed() {
  int spaceUsed = (ioHead >= ioTail) ? ((int)ioHead-(int)ioTail) : /*or rolled*/((int)ioHead+IOBUFFERMASK+1-(int)ioTail);
  return spaceUsed;
}

bool jshHasEventSpaceForChars(int n) {
  int spacesNeeded = 4 + (n/IOEVENT_MAXCHARS); // be sensible - leave a little spare
  int spaceUsed = jshGetEventsUsed();
  int spaceLeft = IOBUFFERMASK+1-spaceUsed;
  return spaceLeft > spacesNeeded;
}

// ----------------------------------------------------------------------------
//                                                                      DEVICES
const char *jshGetDeviceString(IOEventFlags device) {
  switch (device) {
#ifdef USB
  case EV_USBSERIAL: return "USB";
#endif
  case EV_SERIAL1: return "Serial1";
  case EV_SERIAL2: return "Serial2";
  case EV_SERIAL3: return "Serial3";
#if USARTS>=4
  case EV_SERIAL4: return "Serial4";
#endif
#if USARTS>=5
  case EV_SERIAL5: return "Serial5";
#endif
#if USARTS>=6
  case EV_SERIAL6: return "Serial6";
#endif
#if SPIS>=1
  case EV_SPI1: return "SPI1";
#endif
#if SPIS>=2
  case EV_SPI2: return "SPI2";
#endif
#if SPIS>=3
  case EV_SPI3: return "SPI3";
#endif
#if I2CS>=1
  case EV_I2C1: return "I2C1";
#endif
#if I2CS>=2
  case EV_I2C2: return "I2C2";
#endif
#if I2CS>=3
  case EV_I2C3: return "I2C3";
#endif
  default: return "";
  }
}

IOEventFlags jshFromDeviceString(const char *device) {
  if (device[0]=='U') {
#ifdef USB
    if (strcmp(device, "USB")==0) return EV_USBSERIAL;
#endif
  }
  else if (device[0]=='S') {
    if (device[1]=='e' && device[2]=='r' && device[3]=='i' && device[4]=='a' && device[5]=='l') {
      if (strcmp(device, "Serial1")==0) return EV_SERIAL1;
      if (strcmp(device, "Serial2")==0) return EV_SERIAL2;
      if (strcmp(device, "Serial3")==0) return EV_SERIAL3;
#if USARTS>=4
      if (strcmp(device, "Serial4")==0) return EV_SERIAL4;
#endif
#if USARTS>=5
      if (strcmp(device, "Serial5")==0) return EV_SERIAL5;
#endif
#if USARTS>=6
      if (strcmp(device, "Serial6")==0) return EV_SERIAL6;
#endif
    }
    if (device[1]=='P' && device[2]=='I') {
#if SPIS>=1
      if (strcmp(device, "SPI1")==0) return EV_SPI1;
#endif
#if SPIS>=2
      if (strcmp(device, "SPI2")==0) return EV_SPI2;
#endif
#if SPIS>=3
      if (strcmp(device, "SPI3")==0) return EV_SPI3;
#endif
    }
  }
  else if (device[0]=='I' && device[1]=='2' && device[2]=='C') {
#if I2CS>=1
    if (strcmp(device, "I2C1")==0) return EV_I2C1;
#endif
#if I2CS>=2
    if (strcmp(device, "I2C2")==0) return EV_I2C2;
#endif
#if I2CS>=3
    if (strcmp(device, "I2C3")==0) return EV_I2C3;
#endif
  }
  return EV_NONE;
}

/// Set whether the host should transmit or not
void jshSetFlowControlXON(IOEventFlags device, bool hostShouldTransmit) {
}

