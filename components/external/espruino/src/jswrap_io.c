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
 * JavaScript Hardware IO Functions
 * ----------------------------------------------------------------------------
 */
#include "jswrap_io.h"
#include "jsvar.h"


/*JSON{ "type":"function", "name" : "peek8",
         "description" : [ "Read 8 bits of memory at the given location - DANGEROUS!" ],
         "generate_full" : "(JsVarInt)*(unsigned char*)jsvGetInteger(addr)",
         "params" : [ [ "addr", "int", "The address in memory to read"] ],
         "return" : ["int", "The value of memory at the given location"]
}*/
/*JSON{ "type":"function", "name" : "poke8",
         "description" : [ "Write 8 bits of memory at the given location - VERY DANGEROUS!" ],
         "generate_full" : "(*(unsigned char*)jsvGetInteger(addr)) = (unsigned char)jsvGetInteger(value)",
         "params" : [ [ "addr", "int", "The address in memory to write"],
                      [ "value", "int", "The value to write"] ]
}*/
/*JSON{ "type":"function", "name" : "peek16",
         "description" : [ "Read 16 bits of memory at the given location - DANGEROUS!" ],
         "generate_full" : "(JsVarInt)*(unsigned short*)jsvGetInteger(addr)",
         "params" : [ [ "addr", "int", "The address in memory to read"] ],
         "return" : ["int", "The value of memory at the given location"]
}*/
/*JSON{ "type":"function", "name" : "poke16",
         "description" : [ "Write 16 bits of memory at the given location - VERY DANGEROUS!" ],
         "generate_full" : "(*(unsigned short*)jsvGetInteger(addr)) = (unsigned short)jsvGetInteger(value)",
         "params" : [ [ "addr", "int", "The address in memory to write"],
                      [ "value", "int", "The value to write"] ]
}*/
/*JSON{ "type":"function", "name" : "peek32",
         "description" : [ "Read 32 bits of memory at the given location - DANGEROUS!" ],
         "generate_full" : "(JsVarInt)*(unsigned int*)jsvGetInteger(addr)",
         "params" : [ [ "addr", "int", "The address in memory to read"] ],
         "return" : ["int", "The value of memory at the given location"]
}*/
/*JSON{ "type":"function", "name" : "poke32",
         "description" : [ "Write 32 bits of memory at the given location - VERY DANGEROUS!" ],
         "generate_full" : "(*(unsigned int*)jsvGetInteger(addr)) = (unsigned int)jsvGetInteger(value)",
         "params" : [ [ "addr", "int", "The address in memory to write"],
                      [ "value", "int", "The value to write"] ]
}*/

/*JSON{ "type":"function", "name" : "analogRead",
         "description" : ["Get the analog value of the given pin",
                          "This is different to Arduino which only returns an integer between 0 and 1023",
                          "However only pins connected to an ADC will work (see the datasheet)"],
         "generate" : "jshPinAnalog",
         "params" : [ [ "pin", "pin", "The pin to use"] ],
         "return" : ["float", "The analog Value of the Pin between 0 and 1"]
}*/
/*JSON{ "type":"function", "name" : "analogWrite",
         "description" : "Set the analog Value of a pin. It will be output using PWM",
         "generate" : "jswrap_io_analogWrite",
         "params" : [ [ "pin", "pin", "The pin to use"],
                      [ "value", "float", "A value between 0 and 1"],
                      [ "options", "JsVar", ["An object containing options.",
                                            "Currently only freq (pulse frequency in Hz) is available: ```analogWrite(LED1,0.5,{ freq : 10 });``` ",
                                            "Note that specifying a frequency will force PWM output, even if the pin has a DAC"] ]  ]
}*/
void jswrap_io_analogWrite(Pin pin, JsVarFloat value, JsVar *options) {
  JsVarFloat freq = 0;
  if (jsvIsObject(options)) {
    freq = jsvGetFloatAndUnLock(jsvObjectGetChild(options, "freq", 0));
  }

  jshPinAnalogOutput(pin, value, freq);
}

/*JSON{ "type":"function", "name" : "digitalPulse",
         "description" : ["Pulse the pin with the value for the given time in milliseconds",
                          "eg. ```pulse(A0,1,5);``` pulses A0 high for 5ms",
                          "digitalPulse is for SHORT pulses that need to be very accurate. If you're doing anything over a few milliseconds, use setTimeout instead" ],
         "generate" : "jswrap_io_digitalPulse",
         "params" : [ [ "pin", "pin", "The pin to use"],
                      [ "value", "bool", "Whether to pulse high (true) or low (false)"],
                      [ "time", "float", "A time in milliseconds"] ]
}*/
void jswrap_io_digitalPulse(Pin pin, bool value, JsVarFloat time) {
  if (time<=0) {
    jsWarn("Pulse Time given for digitalPulse is less that or equal to 0");
  } else {
    //jsPrintInt((JsVarInt)(time*1000));
    jshPinPulse(pin, value, time);
  }
}

/*JSON{ "type":"function", "name" : "digitalWrite",
         "description" : ["Set the digital value of the given pin",
                          "If pin is an array of pins, eg. ```[A2,A1,A0]``` the value will be treated as an integer where the first array element is the MSB" ],
         "generate" : "jswrap_io_digitalWrite",
         "params" : [ [ "pin", "JsVar", "The pin to use"],
                      [ "value", "int", "Whether to pulse high (true) or low (false)"] ]
}*/
void jswrap_io_digitalWrite(JsVar *pinVar, JsVarInt value) {
  if (jsvIsArray(pinVar)) {
    JsVarRef pinName = pinVar->lastChild; // NOTE: start at end and work back!
    while (pinName) {
      JsVar *pinNamePtr = jsvLock(pinName);
      JsVar *pinPtr = jsvSkipName(pinNamePtr);
      jshPinOutput(jshGetPinFromVar(pinPtr), value&1);
      jsvUnLock(pinPtr);
      pinName = pinNamePtr->prevSibling;
      jsvUnLock(pinNamePtr);
      value = value>>1; // next bit down
    }
  } else {
    Pin pin = jshGetPinFromVar(pinVar);
    jshPinOutput(pin, value!=0);
  }
}


/*JSON{ "type":"function", "name" : "digitalRead",
         "description" : ["Get the digital value of the given pin",
                          "If pin is an array of pins, eg. ```[A2,A1,A0]``` the value will be treated as an integer where the first array element is the MSB" ],
         "generate" : "jswrap_io_digitalRead",
         "params" : [ [ "pin", "JsVar", "The pin to use"] ],
         "return" : ["int", "The digital Value of the Pin"]
}*/
JsVarInt jswrap_io_digitalRead(JsVar *pinVar) {
  if (jsvIsArray(pinVar)) {
    int pins = 0;
    JsVarInt value = 0;
    JsVarRef pinName = pinVar->firstChild;
    while (pinName) {
      JsVar *pinNamePtr = jsvLock(pinName);
      JsVar *pinPtr = jsvSkipName(pinNamePtr);
      value = (value<<1) | jshPinInput(jshGetPinFromVar(pinPtr));
      jsvUnLock(pinPtr);
      pinName = pinNamePtr->nextSibling;
      jsvUnLock(pinNamePtr);
      pins++;
    }
    if (pins==0) return 0; // return undefined if array empty
    return value;
  } else {
    Pin pin = jshGetPinFromVar(pinVar);
    return jshPinInput(pin);
  }
}

/*JSON{ "type":"function", "name" : "pinMode",
         "description" : ["Set the mode of the given pin - note that digitalRead/digitalWrite/etc set this automatically unless pinMode has been called first. If you want digitalRead/etc to set the pin mode automatically after you have called pinMode, simply call it again with no mode argument: ```pinMode(pin)```" ],
         "generate" : "jswrap_io_pinMode",
         "params" : [ [ "pin", "pin", "The pin to use"], [ "mode", "JsVar", "The mode - a string that is either 'input', 'output', 'input_pullup', or 'input_pulldown'. Do not include this argument if you want to revert to automatic pin mode setting."] ]
}*/
void jswrap_io_pinMode(Pin pin, JsVar *mode) {
  if (!jshIsPinValid(pin)) {
    jsError("Invalid pin");
    return;
  }
  JshPinState m = JSHPINSTATE_UNDEFINED;
  if (jsvIsString(mode)) {
    if (jsvIsStringEqual(mode, "input")) m = JSHPINSTATE_GPIO_IN;
    if (jsvIsStringEqual(mode, "input_pullup")) m = JSHPINSTATE_GPIO_IN_PULLUP;
    if (jsvIsStringEqual(mode, "input_pulldown")) m = JSHPINSTATE_GPIO_IN_PULLDOWN;
    if (jsvIsStringEqual(mode, "output")) m = JSHPINSTATE_GPIO_OUT;
  }
  if (m != JSHPINSTATE_UNDEFINED) {
    jshSetPinStateIsManual(pin, true);
    jshPinSetState(pin, m);
  } else {
    jshSetPinStateIsManual(pin, false);
    if (!jsvIsUndefined(mode)) {
      jsError("Unknown pin mode");
    }
  }
}


/*XXXX{ "type":"function", "name" : "bitBang",
         "description" : ["bitBang out a message in a one-wire style BROKEN CURRENTLY" ],
         "generate" : "jshBitBang",
         "params" : [ [ "pin", "pin", "The pin to use"],
                      [ "t0h", "float", "The time (in milliseconds) to spend high for a 0"],
                      [ "t0l", "float", "The time (in milliseconds) to spend low for a 0"],
                      [ "t1h", "float", "The time (in milliseconds) to spend high for a 1"],
                      [ "t1l", "float", "The time (in milliseconds) to spend low for a 1"],
                      [ "data", "JsVar", "A string representing the data"] ]
}*/


/*JSON{ "type":"function", "name" : "setInterval",
         "description" : ["Call the function specified REPEATEDLY after the timeout in milliseconds.",
                          "The function that is being called may also take an argument, which is an object containing a field called 'time' (the time in seconds at which the timer happened)",
                          "for example: ```setInterval(function (e) { print(e.time); }, 1000);```",
                          "This can also be removed using clearInterval" ],
         "generate" : "jswrap_interface_setInterval",
         "params" : [ [ "function", "JsVarName", "A Function or String to be executed"],
                      [ "timeout", "float", "The time between calls to the function" ] ],
         "return" : ["JsVar", "An ID that can be passed to clearInterval"]
}*/
/*JSON{ "type":"function", "name" : "setTimeout",
         "description" : ["Call the function specified ONCE after the timeout in milliseconds.",
                          "The function that is being called may also take an argument, which is an object containing a field called 'time' (the time in seconds at which the timer happened)",
                          "for example: ```setTimeout(function (e) { print(e.time); }, 1000);```",
                          "This can also be removed using clearTimeout" ],
         "generate" : "jswrap_interface_setTimeout",
         "params" : [ [ "function", "JsVarName", "A Function or String to be executed"],
                      [ "timeout", "float", "The time until the function will be executed" ] ],
         "return" : ["JsVar", "An ID that can be passed to clearTimeout"]
}*/
JsVar *_jswrap_interface_setTimeoutOrInterval(JsVar *func, JsVarFloat interval, bool isTimeout) {
  JsVar *skippedFunc = jsvSkipName(func);
  JsVar *itemIndex = 0;
  if (!jsvIsFunction(skippedFunc) && !jsvIsString(skippedFunc)) {
    jsError("Function or String not supplied!");
  } else {
    // Create a new timer
    JsVar *timerPtr = jsvNewWithFlags(JSV_OBJECT);
    if (interval<TIMER_MIN_INTERVAL) interval=TIMER_MIN_INTERVAL;
    JsVar *v;
    v = jsvNewFromInteger(jshGetSystemTime() + jshGetTimeFromMilliseconds(interval));
    jsvUnLock(jsvAddNamedChild(timerPtr, v, "time"));
    jsvUnLock(v);
    v = jsvNewFromFloat(interval);
    jsvUnLock(jsvAddNamedChild(timerPtr, v, "interval"));
    jsvUnLock(v);
    v = jsvNewFromBool(!isTimeout);
    jsvUnLock(jsvAddNamedChild(timerPtr, v, "recur"));
    jsvUnLock(v);
    jsvUnLock(jsvAddNamedChild(timerPtr, func, "callback"));
    //jsPrint("TIMER BEFORE ADD\n"); jsvTrace(timerArray,5);
    JsVar *timerArrayPtr = jsvLock(timerArray);
    itemIndex = jsvNewFromInteger(jsvArrayPushWithInitialSize(timerArrayPtr, timerPtr, 1) - 1);
    //jsPrint("TIMER AFTER ADD\n"); jsvTrace(timerArray,5);
    jsvUnLock(timerArrayPtr);
    jsvUnLock(timerPtr);
  }
  jsvUnLock(skippedFunc);
  //jsvTrace(jsiGetParser()->root, 0);
  return itemIndex;
}
JsVar *jswrap_interface_setInterval(JsVar *func, JsVarFloat timeout) {
  return _jswrap_interface_setTimeoutOrInterval(func, timeout, false);
}
JsVar *jswrap_interface_setTimeout(JsVar *func, JsVarFloat timeout) {
  return _jswrap_interface_setTimeoutOrInterval(func, timeout, true);
}

/*JSON{ "type":"function", "name" : "setWatch",
         "description" : ["Call the function specified when the pin changes",
                          "The function may also take an argument, which is an object containing a field called 'time', which is the time in seconds at which the pin changed state, and 'state', which is the current state of the pin",
                          " This can also be removed using clearWatch" ],
         "generate" : "jswrap_interface_setWatch",
         "params" : [ [ "function", "JsVarName", "A Function or String to be executed"],
                      [ "pin", "pin", "The pin to watch" ],
                      [ "options", "JsVar", ["If this is a boolean or integer, it determines whether to call this once (false = default) or every time a change occurs (true)",
                                             "If this is an object, it can contain the following information: ```{ repeat: true/false(default), edge:'rising'/'falling'/'both'(default)}```" ] ]  ],
         "return" : ["JsVar", "An ID that can be passed to clearWatch"]
}*/
JsVar *jswrap_interface_setWatch(JsVar *funcVar, Pin pin, JsVar *repeatOrObject) {
  bool repeat = false;
  int edge = 0;
  if (jsvIsObject(repeatOrObject)) {
    JsVar *v;
    repeat = jsvGetBoolAndUnLock(jsvObjectGetChild(repeatOrObject, "repeat", 0));
    v = jsvObjectGetChild(repeatOrObject, "edge", 0);
    if (jsvIsString(v)) {
      if (jsvIsStringEqual(v, "rising")) edge=1;
      else if (jsvIsStringEqual(v, "falling")) edge=-1;
      else if (jsvIsStringEqual(v, "both")) edge=0;
      else jsWarn("'edge' in setWatch should be a string - either 'rising', 'falling' or 'both'");
    } else if (!jsvIsUndefined(v))
      jsWarn("'edge' in setWatch should be a string - either 'rising', 'falling' or 'both'");
    jsvUnLock(v);
  } else
    repeat = jsvGetBool(repeatOrObject);

  JsVarInt itemIndex = -1;
  JsVar *skippedFunc = jsvSkipName(funcVar);
  if (!jsvIsFunction(skippedFunc) && !jsvIsString(skippedFunc)) {
    jsError("Function or String not supplied!");
  } else {
    // Create a new watch
    JsVar *watchPtr = jsvNewWithFlags(JSV_OBJECT);
    JsVar *v;
    v = jsvNewFromPin(pin);
    jsvUnLock(jsvAddNamedChild(watchPtr, v, "pin"));
    jsvUnLock(v);
    v = jsvNewFromBool(repeat);
    jsvUnLock(jsvAddNamedChild(watchPtr, v, "recur"));
    jsvUnLock(v);
    v = jsvNewFromInteger(edge);
    jsvUnLock(jsvAddNamedChild(watchPtr, v, "edge"));
    jsvUnLock(v);
    jsvUnLock(jsvAddNamedChild(watchPtr, funcVar, "callback"));
    JsVar *watchArrayPtr = jsvLock(watchArray);
    itemIndex = jsvArrayPushWithInitialSize(watchArrayPtr, watchPtr, 1) - 1;
    jsvUnLock(watchArrayPtr);
    jsvUnLock(watchPtr);
    jshPinWatch(pin, true);
  }
  jsvUnLock(skippedFunc);
  return (itemIndex>=0) ? jsvNewFromInteger(itemIndex) : 0/*undefined*/;
}

/*JSON{ "type":"function", "name" : "clearInterval",
         "description" : ["Clear the Interval that was created with setInterval, for example:",
                          "```var id = setInterval(function () { print('foo'); }, 1000);```",
                          "```clearInterval(id);```",
                          "If no argument is supplied, all timers and intervals are stopped" ],
         "generate" : "jswrap_interface_clearInterval",
         "params" : [ [ "id", "JsVar", "The id returned by a previous call to setInterval"] ]
}*/
/*JSON{ "type":"function", "name" : "clearTimeout",
         "description" : ["Clear the Timeout that was created with setTimeout, for example:",
                          "```var id = setTimeout(function () { print('foo'); }, 1000);```",
                          "```clearTimeout(id);```",
                          "If no argument is supplied, all timers and intervals are stopped" ],
         "generate" : "jswrap_interface_clearTimeout",
         "params" : [ [ "id", "JsVar", "The id returned by a previous call to setTimeout"] ]
}*/
void _jswrap_interface_clearTimeoutOrInterval(JsVar *idVar, bool isTimeout) {
  if (jsvIsUndefined(idVar)) {
    JsVar *timerArrayPtr = jsvLock(timerArray);
    jsvRemoveAllChildren(timerArrayPtr);
    jsvUnLock(timerArrayPtr);
  } else {
    JsVar *child = jsvIsBasic(idVar) ? jsvFindChildFromVarRef(timerArray, idVar, false) : 0;
    if (child) {
      JsVar *timerArrayPtr = jsvLock(timerArray);
      jsvRemoveChild(timerArrayPtr, child);
      jsvUnLock(child);
      jsvUnLock(timerArrayPtr);
    } else {
      jsError(isTimeout ? "Unknown Timeout" : "Unknown Interval");
    }
  }
}
void jswrap_interface_clearInterval(JsVar *idVar) {
  _jswrap_interface_clearTimeoutOrInterval(idVar, false);
}
void jswrap_interface_clearTimeout(JsVar *idVar) {
  _jswrap_interface_clearTimeoutOrInterval(idVar, true);
}

/*JSON{ "type":"function", "name" : "changeInterval",
         "description" : ["Change the Interval on a callback created with setInterval, for example:",
                          "```var id = setInterval(function () { print('foo'); }, 1000); // every second```",
                          "```changeInterval(id, 1500); // now runs every 1.5 seconds```",
                          "This takes effect the text time the callback is called (so it is not immediate)."],
         "generate" : "jswrap_interface_changeInterval",
         "params" : [ [ "id", "JsVar", "The id returned by a previous call to setInterval"],
                      [ "time","float","The new time period in ms" ] ]
}*/
void jswrap_interface_changeInterval(JsVar *idVar, JsVarFloat interval) {
  if (interval<TIMER_MIN_INTERVAL) interval=TIMER_MIN_INTERVAL;
  JsVar *timerName = jsvIsBasic(idVar) ? jsvFindChildFromVarRef(timerArray, idVar, false) : 0;

  if (timerName) {
    JsVar *timer = jsvSkipNameAndUnLock(timerName);
    JsVar *v;
    v = jsvNewFromFloat(interval);
    jsvUnLock(jsvSetNamedChild(timer, v, "interval"));
    jsvUnLock(v);
    v = jsvNewFromInteger(jshGetSystemTime() + jshGetTimeFromMilliseconds(interval));
    jsvUnLock(jsvSetNamedChild(timer, v, "time"));
    jsvUnLock(v);
    jsvUnLock(timer);
    // timerName already unlocked
  } else {
    jsError("Unknown Interval");
  }
}

/*JSON{ "type":"function", "name" : "clearWatch",
         "description" : [ "Clear the Watch that was created with setWatch. If no parameter is supplied, all watches will be removed." ],
         "generate" : "jswrap_interface_clearWatch",
         "params" : [ [ "id", "JsVar", "The id returned by a previous call to setWatch"] ]
}*/
void jswrap_interface_clearWatch(JsVar *idVar) {
  if (jsvIsUndefined(idVar)) {
    JsVar *watchArrayPtr = jsvLock(watchArray);
    // unwatch all pins
    JsVarRef watch = watchArrayPtr->firstChild;
    while (watch) {
      JsVar *watchNamePtr = jsvLock(watch); // effectively the array index
      JsVar *pinVar = jsvSkipNameAndUnLock(jsvFindChildFromStringRef(watchNamePtr->firstChild, "pin", false));
      jshPinWatch(jshGetPinFromVar(pinVar), false); // 'unwatch' pin because we know that we're removing ALL watches
      jsvUnLock(pinVar);
      watch = watchNamePtr->nextSibling;
      jsvUnLock(watchNamePtr);
    }
    // remove all items
    jsvRemoveAllChildren(watchArrayPtr);
    jsvUnLock(watchArrayPtr);
  } else {
    JsVar *watchNamePtr = jsvFindChildFromVarRef(watchArray, idVar, false);
    if (watchNamePtr) { // child is a 'name'
      JsVar *pinVar = jsvSkipNameAndUnLock(jsvFindChildFromStringRef(watchNamePtr->firstChild, "pin", false));
      Pin pin = jshGetPinFromVar(pinVar);
      jsvUnLock(pinVar);

      JsVar *watchArrayPtr = jsvLock(watchArray);
      jsvRemoveChild(watchArrayPtr, watchNamePtr);
      jsvUnLock(watchNamePtr);

      // Now check if this pin is still being watched
      bool stillWatched = false;
      JsArrayIterator it;
      jsvArrayIteratorNew(&it, watchArrayPtr);
      while (jsvArrayIteratorHasElement(&it)) {
        JsVar *watchPtr = jsvArrayIteratorGetElement(&it);
        JsVar *pinVar = jsvObjectGetChild(watchPtr, "pin", 0);
        if (jshGetPinFromVar(pinVar) == pin)
          stillWatched = true;
        jsvUnLock(pinVar);
        jsvUnLock(watchPtr);
        jsvArrayIteratorNext(&it);
      }
      jsvArrayIteratorFree(&it);
      jsvUnLock(watchArrayPtr);

      if (!stillWatched)
        jshPinWatch(pin, false); // 'unwatch' pin
    } else {
      jsError("Unknown Watch");
    }
  }
}


