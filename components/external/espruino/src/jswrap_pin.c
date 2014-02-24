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
 * JavaScript Pin Object Functions
 * ----------------------------------------------------------------------------
 */
#include "jswrap_pin.h"

/*JSON{ "type":"class",
        "class" : "Pin",
        "check" : "jsvIsPin(var)",
        "description" : ["This is the built-in class for Pins, such as D0,D1,LED1, or BTN",
                         "You can call the methods on Pin, or you can use Wiring-style functions such as digitalWrite" ]
}*/

/*JSON{ "type":"method", "class": "Pin", "name" : "read",
         "description" : "Returns the input state of the pin as a boolean",
         "generate" : "jswrap_pin_read",
         "return" : ["bool", "Whether pin is a logical 1 or 0"]
}*/
bool jswrap_pin_read(JsVar *parent) {
  Pin pin = jshGetPinFromVar(parent);
  return jshPinInput(pin);
}

/*JSON{ "type":"method", "class": "Pin", "name" : "set",
         "description" : "Sets the output state of the pin to a 1",
         "generate" : "jswrap_pin_set"
}*/
void jswrap_pin_set(JsVar *parent) {
  Pin pin = jshGetPinFromVar(parent);
  jshPinOutput(pin, 1);
}

/*JSON{ "type":"method", "class": "Pin", "name" : "reset",
         "description" : "Sets the output state of the pin to a 0",
         "generate" : "jswrap_pin_reset"
}*/
void jswrap_pin_reset(JsVar *parent) {
  Pin pin = jshGetPinFromVar(parent);
  jshPinOutput(pin, 0);
}

/*JSON{ "type":"method", "class": "Pin", "name" : "write",
         "description" : "Sets the output state of the pin to the parameter given",
         "generate" : "jswrap_pin_write",
         "params" : [ [ "value", "bool", "Whether to set output high (true/1) or low (false/0)"] ]
}*/
void jswrap_pin_write(JsVar *parent, bool value) {
  Pin pin = jshGetPinFromVar(parent);
  jshPinOutput(pin, value);
}

/*JSON{ "type":"method", "class": "Pin", "name" : "writeAtTime", "ifndef" : "SAVE_ON_FLASH",
         "description" : "Sets the output state of the pin to the parameter given at the specified time",
         "generate" : "jswrap_pin_writeAtTime",
         "params" : [ [ "value", "bool", "Whether to set output high (true/1) or low (false/0)"],
                      ["time", "float", "Time at which to write"] ]
}*/
void jswrap_pin_writeAtTime(JsVar *parent, bool value, JsVarFloat time) {
  Pin pin = jshGetPinFromVar(parent);
  JsSysTime sTime = jshGetTimeFromMilliseconds(time*1000);
  jshPinOutputAtTime(sTime, pin, value);
}
