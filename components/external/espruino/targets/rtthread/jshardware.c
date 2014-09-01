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
 * Platform Specific part of Hardware interface Layer
 * ----------------------------------------------------------------------------
 */
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <sys/time.h>
 #include <signal.h>
 #include <inttypes.h>

#include "jshardware.h"
#include "jsutils.h"
#include "jsparse.h"
#include "jsinteractive.h"
#include "jspininfo.h"

#include <rtthread.h>

// ----------------------------------------------------------------------------
// for non-blocking IO

void reset_terminal_mode()
{
}

void set_conio_terminal_mode()
{
}

struct
{
    struct rt_semaphore sem;
    rt_device_t device;
} dev4js;

rt_err_t es_rx_ind(rt_device_t dev, rt_size_t size)
{
    rt_sem_release(&dev4js.sem);

    return RT_EOK;
}

static int kbhit(void)
{
    while (rt_sem_take(&dev4js.sem, RT_WAITING_FOREVER) != RT_EOK);

    return 1;
}

static char getch()
{
    unsigned char c;

    if (rt_device_read(dev4js.device, 0, &c, 1) == 1) {
        if (c=='\3') exit(0); // ctrl-c
        return c;
    }
}

void jshInit() {
    rt_sem_init(&dev4js.sem, "jssem", 0, RT_IPC_FLAG_PRIO);
}

void jshKill() {
}

void jshIdle() {
  //while (kbhit()) {
  //  jshPushIOCharEvent(EV_USBSERIAL, (char)getch());
  //}
}

// ----------------------------------------------------------------------------

int jshGetSerialNumber(unsigned char *data, int maxChars) {
  long initialSerial = 0;
  long long serial = 0xDEADDEADDEADDEADL;

  memcpy(&data[0], &initialSerial, 4);
  memcpy(&data[4], &serial, 8);
  return 12;
}

unsigned int jshGetRegistrationCode() {
  unsigned int code = 0xFFFFFFFF;
  return code;
}

void jshSetRegistrationCode(unsigned int code) {
}

// ----------------------------------------------------------------------------

void jshInterruptOff() {
}

void jshInterruptOn() {
}

void jshDelayMicroseconds(int microsec) {
  int ms = (microsec + 999) / 1000;

  rt_thread_sleep(rt_tick_from_millisecond(ms)); // don't sleep much if we have watches - we need to keep polling them
}

bool jshGetPinStateIsManual(Pin pin) {
  return false;
}

void jshSetPinStateIsManual(Pin pin, bool manual) {
}

void jshPinSetState(Pin pin, JshPinState state) {
}

JshPinState jshPinGetState(Pin pin) {
  return JSHPINSTATE_UNDEFINED;
}

void jshPinSetValue(Pin pin, bool value) {
}

bool jshPinGetValue(Pin pin) {

  return false;
}

bool jshIsDeviceInitialised(IOEventFlags device) { return true; }

bool jshIsUSBSERIALConnected() {
  return false;
}

JsSysTime jshGetTimeFromMilliseconds(JsVarFloat ms) {
  return (JsSysTime)(ms*1000);
}

JsVarFloat jshGetMillisecondsFromTime(JsSysTime time) {
  return ((JsVarFloat)time)/1000;
}


JsSysTime jshGetSystemTime() {
  //struct timeval tm;
  //gettimeofday(&tm, 0);
  //return tm.tv_sec*1000000L + tm.tv_usec;
  return rt_tick_get() * (1000 / RT_TICK_PER_SECOND) * 1000;
}

// ----------------------------------------------------------------------------

bool jshPinInput(Pin pin) {
  bool value = false;

  jsError("Invalid pin!");
  return value;
}

JsVarFloat jshPinAnalog(Pin pin) {
  JsVarFloat value = 0;
  jsError("Analog is not supported on this device.");
  return value;
}


void jshPinOutput(Pin pin, bool value) {
}

bool jshPinOutputAtTime(JsSysTime time, Pin pin, bool value) {
 // FIXME
}

void jshPinAnalogOutput(Pin pin, JsVarFloat value, JsVarFloat freq) { // if freq<=0, the default is used
}

void jshPinPulse(Pin pin, bool value, JsVarFloat time) {
}

void jshPinWatch(Pin pin, bool shouldWatch) {
}

bool jshGetWatchedPinState(IOEventFlags device) {
  return false;
}

bool jshIsEventForPin(IOEvent *event, Pin pin) {
  return false;
}

void jshUSARTSetup(IOEventFlags device, JshUSARTInfo *inf) {
}

/** Kick a device into action (if required). For instance we may need
 * to set up interrupts */
void jshUSARTKick(IOEventFlags device) {
}

void jshSPISetup(IOEventFlags device, JshSPIInfo *inf) {
}

/** Send data through the given SPI device (if data>=0), and return the result
 * of the previous send (or -1). If data<0, no data is sent and the function
 * waits for data to be returned */
int jshSPISend(IOEventFlags device, int data) {
}

/** Send 16 bit data through the given SPI device. */
void jshSPISend16(IOEventFlags device, int data) {
}

/** Set whether to send 16 bits or 8 over SPI */
void jshSPISet16(IOEventFlags device, bool is16) {
}

void jshI2CSetup(IOEventFlags device, JshI2CInfo *inf) {
}

void jshI2CWrite(IOEventFlags device, unsigned char address, int nBytes, const unsigned char *data) {
}

void jshI2CRead(IOEventFlags device, unsigned char address, int nBytes, unsigned char *data) {
}


void jshSaveToFlash() {

}

void jshLoadFromFlash() {

}

bool jshFlashContainsCode() {

}

/// Enter simple sleep mode (can be woken up by interrupts). Returns true on success
bool jshSleep(JsSysTime timeUntilWake) {
  bool hasWatches = false;
  int ms = (hasWatches ? 1000 : (10*1000)) / 1000;

  rt_thread_sleep(rt_tick_from_millisecond(ms)); // don't sleep much if we have watches - we need to keep polling them
  return true;
}
