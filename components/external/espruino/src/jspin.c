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
 * Utilities and definitions for handling Pins
 * ----------------------------------------------------------------------------
 */

#include "jspin.h"
#include "jspininfo.h" // auto-generated

bool jshIsPinValid(Pin pin) {
  // Note, PIN_UNDEFINED is always > JSH_PIN_COUNT
  return pin < JSH_PIN_COUNT && pinInfo[pin].port!=JSH_PORT_NONE;
}


Pin jshGetPinFromString(const char *s) {
  // built in constants

  if (s[0]=='B' && s[1]=='T' && s[2]=='N') {
#ifdef BTN1_PININDEX
    if (!s[3]) return BTN1_PININDEX;
    if (s[3]=='1' && !s[4]) return BTN1_PININDEX;
#endif
#ifdef BTN2_PININDEX
    if (s[3]=='2' && !s[4]) return BTN2_PININDEX;
#endif
#ifdef BTN3_PININDEX
    if (s[3]=='3' && !s[4]) return BTN3_PININDEX;
#endif
#ifdef BTN4_PININDEX
    if (s[3]=='4' && !s[4]) return BTN4_PININDEX;
#endif
  }
  if (s[0]=='L' && s[1]=='E' && s[2]=='D') {
#ifdef LED1_PININDEX
    if (!s[3]) return LED1_PININDEX;
    if (s[3]=='1' && !s[4]) return LED1_PININDEX;
#endif
#ifdef LED2_PININDEX
    if (s[3]=='2' && !s[4]) return LED2_PININDEX;
#endif
#ifdef LED3_PININDEX
    if (s[3]=='3' && !s[4]) return LED3_PININDEX;
#endif
#ifdef LED4_PININDEX
    if (s[3]=='4' && !s[4]) return LED4_PININDEX;
#endif
#ifdef LED5_PININDEX
    if (s[3]=='5' && !s[4]) return LED5_PININDEX;
#endif
#ifdef LED6_PININDEX
    if (s[3]=='6' && !s[4]) return LED6_PININDEX;
#endif
#ifdef LED7_PININDEX
    if (s[3]=='7' && !s[4]) return LED7_PININDEX;
#endif
#ifdef LED8_PININDEX
    if (s[3]=='8' && !s[4]) return LED8_PININDEX;
#endif
  }

  if ((s[0]>='A' && s[0]<='H') && s[1]) { // first 6 are analogs
    int port = JSH_PORTA+s[0]-'A';
    Pin pin = 127;
    if (!s[2] && (s[1]>='0' && s[1]<='9')) { // D0-D9
      pin = (Pin)(s[1]-'0');
    } else if (!s[3] && (s[1]>='1' && s[1]<='3' && s[2]>='0' && s[2]<='9')) { // D1X-D3X
      pin = (Pin)((s[1]-'0')*10 + (s[2]-'0'));
    }
    if (port == JSH_PORTA) {
      if (pin<JSH_PORTA_COUNT) return (Pin)(JSH_PORTA_OFFSET + pin);
    } else if (port == JSH_PORTB) {
      if (pin<JSH_PORTB_COUNT) return (Pin)(JSH_PORTB_OFFSET + pin);
    } else if (port == JSH_PORTC) {
      if (pin<JSH_PORTC_COUNT) return (Pin)(JSH_PORTC_OFFSET + pin);
    } else if (port == JSH_PORTD) {
      if (pin<JSH_PORTD_COUNT) return (Pin)(JSH_PORTD_OFFSET + pin);
#if JSH_PORTE_OFFSET!=-1
    } else if (port == JSH_PORTE) {
      if (pin<JSH_PORTE_COUNT) return (Pin)(JSH_PORTE_OFFSET + pin);
#endif
#if JSH_PORTF_OFFSET!=-1
    } else if (port == JSH_PORTF) {
      if (pin<JSH_PORTF_COUNT) return (Pin)(JSH_PORTF_OFFSET + pin);
#endif
#if JSH_PORTG_OFFSET!=-1
    } else if (port == JSH_PORTG) {
      if (pin<JSH_PORTG_COUNT) return (Pin)(JSH_PORTG_OFFSET + pin);
#endif
#if JSH_PORTH_OFFSET!=-1
    } else if (port == JSH_PORTH) {
      if (pin<JSH_PORTH_COUNT) return (Pin)(JSH_PORTH_OFFSET + pin);
#endif
    }
  }

  return PIN_UNDEFINED;
}

/** Write the pin name to a string. String must have at least 8 characters (to be safe) */
void jshGetPinString(char *result, Pin pin) {
  result[0] = 0; // just in case
  if (
#if JSH_PORTA_OFFSET!=0
      pin>=JSH_PORTA_OFFSET &&
#endif
      pin<JSH_PORTA_OFFSET+JSH_PORTA_COUNT) {
    result[0]='A';
    itoa(pin-JSH_PORTA_OFFSET,&result[1],10);
  } else if (pin>=JSH_PORTB_OFFSET && pin<JSH_PORTB_OFFSET+JSH_PORTB_COUNT) {
    result[0]='B';
    itoa(pin-JSH_PORTB_OFFSET,&result[1],10);
  } else if (pin>=JSH_PORTC_OFFSET && pin<JSH_PORTC_OFFSET+JSH_PORTC_COUNT) {
    result[0]='C';
    itoa(pin-JSH_PORTC_OFFSET,&result[1],10);
  } else if (pin>=JSH_PORTD_OFFSET && pin<JSH_PORTD_OFFSET+JSH_PORTD_COUNT) {
    result[0]='D';
    itoa(pin-JSH_PORTD_OFFSET,&result[1],10);
#if JSH_PORTE_OFFSET!=-1
  } else if (pin>=JSH_PORTE_OFFSET && pin<JSH_PORTE_OFFSET+JSH_PORTE_COUNT) {
    result[0]='E';
    itoa(pin-JSH_PORTE_OFFSET,&result[1],10);
#endif
#if JSH_PORTF_OFFSET!=-1
  } else if (pin>=JSH_PORTF_OFFSET && pin<JSH_PORTF_OFFSET+JSH_PORTF_COUNT) {
    result[0]='F';
    itoa(pin-JSH_PORTF_OFFSET,&result[1],10);
#endif
#if JSH_PORTG_OFFSET!=-1
  } else if (pin>=JSH_PORTG_OFFSET && pin<JSH_PORTG_OFFSET+JSH_PORTG_COUNT) {
    result[0]='G';
    itoa(pin-JSH_PORTG_OFFSET,&result[1],10);
#endif
#if JSH_PORTH_OFFSET!=-1
  } else if (pin>=JSH_PORTH_OFFSET && pin<JSH_PORTH_OFFSET+JSH_PORTH_COUNT) {
    result[0]='H';
    itoa(pin-JSH_PORTH_OFFSET,&result[1],10);
#endif
  } else {
    strncpy(result, "UNKNOWN", 8);
  }
}
