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
 * This file is designed to be parsed during the build process
 *
 * JavaScript OneWire Functions
 * ----------------------------------------------------------------------------
 */
#include "jswrap_onewire.h"
#include "jsdevices.h"
#include "jsinteractive.h"

/*JSON{ "type":"class",
        "class" : "OneWire",
        "description" : ["This class provides a software-defined OneWire master. It is designed to be similar to Arduino's OneWire library." ]
}*/

static inline Pin onewire_getpin(JsVar *parent) {
  return jshGetPinFromVarAndUnLock(jsvObjectGetChild(parent, "pin", 0));
}


/** Reset one-wire, return true if a device was present */
static bool NO_INLINE OneWireReset(Pin pin) {
  jshPinSetState(pin, JSHPINSTATE_GPIO_OUT_OPENDRAIN);
  //jshInterruptOff();
  jshPinSetValue(pin, 0);
  jshDelayMicroseconds(500);
  jshPinSetValue(pin, 1);
  jshDelayMicroseconds(80);
  bool hasDevice = !jshPinGetValue(pin);
  //jshInterruptOn();
  jshDelayMicroseconds(420);
  return hasDevice;
}

/** Write 'bits' bits, and return what was read (to read, you must send all 1s) */
static JsVarInt NO_INLINE OneWireRead(Pin pin, int bits) {
  jshPinSetState(pin, JSHPINSTATE_GPIO_OUT_OPENDRAIN);
  JsVarInt result = 0;
  JsVarInt mask = 1;
  while (bits-- > 0) {
    jshInterruptOff();
    jshPinSetValue(pin, 0);
    jshDelayMicroseconds(3);
    jshPinSetValue(pin, 1);
    jshDelayMicroseconds(10); // leave time to let it rise
    if (jshPinGetValue(pin))
      result = result | mask;
    jshInterruptOn();
    jshDelayMicroseconds(53);
    mask = mask << 1;
  }

  return result;
}

/** Write 'bits' bits, and return what was read (to read, you must send all 1s) */
static void NO_INLINE OneWireWrite(Pin pin, int bits, JsVarInt data) {
  jshPinSetState(pin, JSHPINSTATE_GPIO_OUT_OPENDRAIN);
  JsVarInt mask = 1;
  while (bits-- > 0) {
    if (data & mask) { // short pulse
      jshInterruptOff();
      jshPinSetValue(pin, 0);
      jshDelayMicroseconds(10);
      jshPinSetValue(pin, 1);
      jshInterruptOn();
      jshDelayMicroseconds(55);
    } else {  // long pulse
      jshInterruptOff();
      jshPinSetValue(pin, 0);
      jshDelayMicroseconds(65);
      jshPinSetValue(pin, 1);
      jshInterruptOn();
      jshDelayMicroseconds(5);
    }
    mask = mask << 1;
  }
}

/*JSON{ "type":"constructor", "class": "OneWire",  "name": "OneWire",
         "description" : "Create a software OneWire implementation on the given pin",
         "generate" : "jswrap_onewire_constructor",
         "params" : [ [ "pin", "pin", "The pin to implement OneWire on" ] ],
         "return" : [ "JsVar", "A OneWire object" ]

}*/
JsVar *jswrap_onewire_constructor(Pin pin) {
  JsVar *ow = jspNewObject(jsiGetParser(), 0, "OneWire");
  if (ow) {
    JsVar *pinVar = jsvFindChildFromString(ow, "pin", true);
    if (pinVar) {
      JsVar *pv = jsvNewFromPin(pin);
      jsvSetValueOfName(pinVar, pv);
      jsvUnLock(pv);
    }
    jsvUnLock(pinVar);
  }
  return ow;
}


/*JSON{ "type":"method", "class": "OneWire", "name" : "reset",
         "description" : "Perform a reset cycle",
         "generate" : "jswrap_onewire_reset",
         "return" : [ "bool", "True is a device was present (it held the bus low)" ]
}*/
bool jswrap_onewire_reset(JsVar *parent) {
  Pin pin = onewire_getpin(parent);
  if (!jshIsPinValid(pin)) return 0;
  return OneWireReset(pin);
}

/*JSON{ "type":"method", "class": "OneWire", "name" : "select",
         "description" : "Select a ROM - reset needs to be done first",
         "generate" : "jswrap_onewire_select",
         "params" : [ [ "rom", "int", "The rom to select" ] ]
}*/
void jswrap_onewire_select(JsVar *parent, JsVarInt rom) {
  Pin pin = onewire_getpin(parent);
  if (!jshIsPinValid(pin)) return;
  OneWireWrite(pin, 8, 0x55);
  OneWireWrite(pin, 64, rom);
}

/*JSON{ "type":"method", "class": "OneWire", "name" : "skip",
         "description" : "Skip a ROM",
         "generate" : "jswrap_onewire_skip"
}*/
void jswrap_onewire_skip(JsVar *parent) {
  Pin pin = onewire_getpin(parent);
  if (!jshIsPinValid(pin)) return;
  OneWireWrite(pin, 8, 0xCC);
}

/*JSON{ "type":"method", "class": "OneWire", "name" : "write",
         "description" : "Write a byte",
         "generate" : "jswrap_onewire_write",
         "params" : [ [ "data", "int", "A byte to write" ],
                      [ "power", "bool", "Whether to leave power on after write (default is false)" ] ]
}*/
void jswrap_onewire_write(JsVar *parent, int data, bool leavePowerOn) {
  Pin pin = onewire_getpin(parent);
  if (!jshIsPinValid(pin)) return;
  OneWireWrite(pin, 8, data);

  if (!leavePowerOn) {
    jshPinSetState(pin, JSHPINSTATE_GPIO_IN);
    jshPinSetValue(pin, 0);
  }
}

/*JSON{ "type":"method", "class": "OneWire", "name" : "read",
         "description" : "Read a byte",
         "generate" : "jswrap_onewire_read",
         "return" : [ "int", "The byte that was read" ]
}*/
JsVarInt jswrap_onewire_read(JsVar *parent) {
  Pin pin = onewire_getpin(parent);
  if (!jshIsPinValid(pin)) return -1;
  return OneWireRead(pin, 8);
}


/*JSON{ "type":"method", "class": "OneWire", "name" : "search",
         "description" : "Search for devices",
         "generate" : "jswrap_onewire_search",
         "return" : [ "JsVar", "An array of devices that were found" ]
}*/
JsVar *jswrap_onewire_search(JsVar *parent) {
  // search - code from http://www.maximintegrated.com/app-notes/index.mvp/id/187
  Pin pin = onewire_getpin(parent);
  if (!jshIsPinValid(pin)) return 0;

  JsVar *array = jsvNewWithFlags(JSV_ARRAY);
  if (!array) return 0;

  // global search state
  unsigned char ROM_NO[8];
  int LastDiscrepancy;
  int LastFamilyDiscrepancy;
  int LastDeviceFlag;

  // reset the search state
  LastDiscrepancy = 0;
  LastDeviceFlag = FALSE;
  LastFamilyDiscrepancy = 0;

  int search_result = true;

  while (search_result) {

    int id_bit_number;
    int last_zero, rom_byte_number;
    unsigned char id_bit, cmp_id_bit;
    unsigned char rom_byte_mask, search_direction;

    // initialize for search
    id_bit_number = 1;
    last_zero = 0;
    rom_byte_number = 0;
    rom_byte_mask = 1;
    search_result = 0;

    // if the last call was not the last one
    if (!LastDeviceFlag)
    {
       // 1-Wire reset
       if (!OneWireReset(pin))
       {
          // reset the search
          LastDiscrepancy = 0;
          LastDeviceFlag = FALSE;
          LastFamilyDiscrepancy = 0;
          return array;
       }

       // issue the search command
       OneWireWrite(pin, 8, 0xF0);

       // loop to do the search
       do
       {
          // read a bit and its complement
          id_bit = (unsigned char)OneWireRead(pin, 1);
          cmp_id_bit = (unsigned char)OneWireRead(pin, 1);

          // check for no devices on 1-wire
          if ((id_bit == 1) && (cmp_id_bit == 1))
             break;
          else
          {
             // all devices coupled have 0 or 1
             if (id_bit != cmp_id_bit)
                search_direction = id_bit;  // bit write value for search
             else
             {
                // if this discrepancy if before the Last Discrepancy
                // on a previous next then pick the same as last time
                if (id_bit_number < LastDiscrepancy)
                   search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
                else
                   // if equal to last pick 1, if not then pick 0
                   search_direction = (id_bit_number == LastDiscrepancy);

                // if 0 was picked then record its position in LastZero
                if (search_direction == 0)
                {
                   last_zero = id_bit_number;

                   // check for Last discrepancy in family
                   if (last_zero < 9)
                      LastFamilyDiscrepancy = last_zero;
                }
             }

             // set or clear the bit in the ROM byte rom_byte_number
             // with mask rom_byte_mask
             if (search_direction == 1)
               ROM_NO[rom_byte_number] |= rom_byte_mask;
             else
               ROM_NO[rom_byte_number] &= (unsigned char)~rom_byte_mask;

             // serial number search direction write bit
             OneWireWrite(pin, 1, search_direction);

             // increment the byte counter id_bit_number
             // and shift the mask rom_byte_mask
             id_bit_number++;
             rom_byte_mask = (unsigned char)(rom_byte_mask << 1);

             // if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
             if (rom_byte_mask == 0)
             {
                 rom_byte_number++;
                 rom_byte_mask = 1;
             }
          }
       }
       while(rom_byte_number < 8);  // loop until through all ROM bytes 0-7

       // if the search was successful then
       if (!((id_bit_number < 65)))
       {
          // search successful so set LastDiscrepancy,LastDeviceFlag,search_result
          LastDiscrepancy = last_zero;

          // check for last device
          if (LastDiscrepancy == 0)
             LastDeviceFlag = TRUE;

          search_result = TRUE;
       }
    }

    // if no device found then reset counters so next 'search' will be like a first
    if (!search_result || !ROM_NO[0])
    {
       LastDiscrepancy = 0;
       LastDeviceFlag = FALSE;
       LastFamilyDiscrepancy = 0;
       search_result = FALSE;
    }

    if (search_result) {
      JsVar *val = jsvNewFromInteger(
          (((JsVarInt)ROM_NO[7])<<(7*8)) |
          (((JsVarInt)ROM_NO[6])<<(6*8)) |
          (((JsVarInt)ROM_NO[5])<<(5*8)) |
          (((JsVarInt)ROM_NO[4])<<(4*8)) |
          (((JsVarInt)ROM_NO[3])<<(3*8)) |
          (((JsVarInt)ROM_NO[2])<<(2*8)) |
          (((JsVarInt)ROM_NO[1])<<(1*8)) |
           ((JsVarInt)ROM_NO[0])
          );
      if (val) jsvArrayPushAndUnLock(array, val);
    }

    NOT_USED(LastFamilyDiscrepancy);
  }

  return array;
}

