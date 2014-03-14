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
 * JavaScript methods and functions for the interactive shell
 * ----------------------------------------------------------------------------
 */
#include "jswrap_interactive.h"
#include "jsinteractive.h"

/*JSON{ "type":"function", "name" : "setBusyIndicator",
         "description" : "When Espruino is busy, set the pin specified here high. Set this to undefined to disable the feature.",
         "generate" : "jswrap_interface_setBusyIndicator",
         "params" : [ [ "pin", "JsVar", ""] ]
}*/
void jswrap_interface_setBusyIndicator(JsVar *pinVar) {
  Pin oldPin = pinBusyIndicator;
  pinBusyIndicator = jshGetPinFromVar(pinVar);
  // we should be busy right now anyway, so set stuff up right
  if (pinBusyIndicator!=oldPin) {
    if (oldPin!=PIN_UNDEFINED) jshPinOutput(oldPin, 0);
    if (pinBusyIndicator!=PIN_UNDEFINED) jshPinOutput(pinBusyIndicator, 1);
  }
}

/*JSON{ "type":"function", "name" : "setSleepIndicator",
         "description" : "When Espruino is asleep, set the pin specified here high. Set this to undefined to disable the feature.",
         "generate" : "jswrap_interface_setSleepIndicator",
         "params" : [ [ "pin", "JsVar", ""] ]
}*/
void jswrap_interface_setSleepIndicator(JsVar *pinVar) {
  pinSleepIndicator = jshGetPinFromVar(pinVar);
}

/*JSON{ "type":"function", "name" : "setDeepSleep",
         "description" : [ "Set whether we can enter deep sleep mode, which reduces power consumption to around 1mA. This only works on the Espruino Board.",
                           "Deep Sleep is currently beta. Espruino will only enter Deep Sleep when there are no timers and it is not connected to USB. USB will not wake Espruino from Deep Sleep, nor will Serial comms (only setWatch will wake it). The System Timer will also pause." ],
         "generate" : "jswrap_interface_setDeepSleep",
         "params" : [ [ "sleep", "bool", ""] ]
}*/
void jswrap_interface_setDeepSleep(bool sleep) {
  allowDeepSleep = sleep;
}


/*JSON{ "type":"function", "name" : "trace", "ifndef" : "SAVE_ON_FLASH",
         "description" : "Output debugging information",
         "generate" : "jswrap_interface_trace",
         "params" : [ [ "root", "JsVarName", "The symbol to output (optional). If nothing is specified, everything will be output"] ]
}*/
void jswrap_interface_trace(JsVar *root) {
  if (jsvIsUndefined(root)) {
    jsvTrace(jsvGetRef(jsiGetParser()->root), 0);
  } else {
    jsvTrace(jsvGetRef(root), 0);
  }
}

/*XXX{ "type":"function", "name" : "dotty",
         "description" : "Output dotty-format graph of debugging information",
         "generate_full" : "jsvDottyOutput()"
}*/
/*JSON{ "type":"function", "name" : "dump",
         "description" : ["Output current interpreter state in a text form such that it can be copied to a new device",
                          "Note: 'Internal' functions are currently not handled correctly. You will need to recreate these in the onInit function."],
         "generate_full" : "jsiDumpState()"
}*/
/*JSON{ "type":"function", "name" : "load",
         "description" : ["Load program memory out of flash",
                          "This command only executes when the Interpreter returns to the Idle state - for instance ```a=1;load();a=2;``` will still leave 'a' as undefined (or what it was set to in the saved program)."],
         "generate_full" : "jsiSetTodo(TODO_FLASH_LOAD)"
}*/
/*JSON{ "type":"function", "name" : "save",
         "description" : ["Save program memory into flash. It will then be loaded automatically every time Espruino powers on or is hard-reset.",
                          "This command only executes when the Interpreter returns to the Idle state - for instance ```a=1;save();a=2;``` will save 'a' as 2.",
                          "In order to stop the program saved with this command being loaded automatically, hold down Button 1 while also pressing reset. On some boards, Button 1 enters bootloader mode, so you will need to press Reset with Button 1 raised, and then hold Button 1 down a fraction of a second later."],
         "generate_full" : "jsiSetTodo(TODO_FLASH_SAVE)"
}*/
/*JSON{ "type":"function", "name" : "reset",
         "description" : ["Reset the interpreter - clear program memory, and do not load a saved program from flash. This does NOT reset the underlying hardware (which allows you to reset the device without it disconnecting from USB).",
           "This command only executes when the Interpreter returns to the Idle state - for instance ```a=1;reset();a=2;``` will still leave 'a' as undefined.",
           "The safest way to do a full reset is to hit the reset button."],
         "generate_full" : "jsiSetTodo(TODO_RESET)"
}*/
/*JSON{ "type":"function", "name" : "print",
         "description" : "Print the supplied string",
         "generate" : "jswrap_interface_print",
         "params" : [ [ "text", "JsVarArray", ""] ]
}*/
/*JSON{ "type":"staticmethod", "class":"console", "name" : "log",
         "description" : "Print the supplied string(s)",
         "generate" : "jswrap_interface_print",
         "params" : [ [ "text", "JsVarArray", "One or more arguments to print"] ]
}*/
void jswrap_interface_print(JsVar *v) {
  assert(jsvIsArray(v));
  JsArrayIterator it;
  jsvArrayIteratorNew(&it, v);
  while (jsvArrayIteratorHasElement(&it)) {
    JsVar *v = jsvAsString(jsvArrayIteratorGetElement(&it), true);
    jsiConsoleRemoveInputLine();
    jsiConsolePrintStringVar(v);
    jsvUnLock(v);
    jsvArrayIteratorNext(&it);
    if (jsvArrayIteratorHasElement(&it))
      jsiConsolePrint(" ");
  }
  jsvArrayIteratorFree(&it);
  jsiConsolePrint("\n");
}

/*JSON{ "type":"function", "name" : "edit",
        "description" : ["Fill the console with the contents of the given function, so you can edit it.",
                         "NOTE: This is a convenience function - it will not edit 'inner functions'. For that, you must edit the 'outer function' and re-execute it."],
        "generate" : "jswrap_interface_edit",
        "params" : [ [ "funcName", "JsVarName", "The name of the function to edit (either a string or just the unquoted name)"] ]
}*/
void jswrap_interface_edit(JsVar *funcName) {
  if (jsvIsString(funcName)) {
    JsVar *func = 0;
    if (jsvIsName(funcName))
      func = jsvSkipName(funcName);
    else
      func = jsvSkipNameAndUnLock(jsvFindChildFromVar(jsiGetParser()->root, funcName, 0));
    if (jsvIsFunction(func)) {
      JsVar *scopeVar = jsvFindChildFromString(func, JSPARSE_FUNCTION_SCOPE_NAME, false);
      JsVarRef scope = jsvGetRef(scopeVar);
      jsvUnLock(scopeVar);
      JsVar *newLine = jsvNewFromEmptyString();
      if (newLine) { // could be out of memory
        jsvAppendStringVarComplete(newLine, funcName);
        if (scope) {
          // If we have a scope, it's an internal function so we will need to write different code
          jsvAppendString(newLine, ".replaceWith(");
        } else {
          jsvAppendString(newLine, " = ");
        }
        JsVar *funcData = jsvAsString(func, false);
        if (funcData)
          jsvAppendStringVarComplete(newLine, funcData);
        jsvUnLock(funcData);
        if (scope) {
          jsvAppendString(newLine, ");");
        } else {
          jsvAppendString(newLine, ";");
        }
        jsiReplaceInputLine(newLine);
        jsvUnLock(newLine);
      }
    } else {
      jsError("Edit should be called with the name of a function");
    }
    jsvUnLock(func);
  } else {
    jsError("Edit should be called with edit(funcName) or edit('funcName')");
  }
}


/*JSON{ "type":"function", "name" : "echo",
         "description" : "Should TinyJS echo what you type back to you? true = yes (Default), false = no. When echo is off, the result of executing a command is not returned. Instead, you must use 'print' to send output.",
         "generate" : "jswrap_interface_echo",
         "params" : [ [ "echoOn", "bool", ""] ]
}*/
void jswrap_interface_echo(bool echoOn) {
  echo = echoOn;
}

/*JSON{ "type":"function", "name" : "getTime",
         "description" : "Return the current system time in Seconds (as a floating point number)",
         "generate_full" : "(JsVarFloat)jshGetSystemTime() / (JsVarFloat)jshGetTimeFromMilliseconds(1000)",
         "return" : ["float", ""]
}*/


/*JSON{ "type":"function", "name" : "getSerial",
         "description" : "Get the serial number of this board",
         "generate" : "jswrap_interface_getSerial",
         "return" : ["JsVar", "The board's serial number"]
}*/
JsVar *jswrap_interface_getSerial() {
  char buf[8];
  unsigned char serial[32];
  int i, serialSize = jshGetSerialNumber(serial, sizeof(serial));

  JsVar *str = jsvNewFromEmptyString();
  if (!str) return 0;

  for (i=0;i<serialSize;i++) {
    if ((i&3)==0 && i) jsvAppendString(str, "-");
    itoa(serial[i] | 0x100, buf, 16);
    jsvAppendString(str, &buf[1]);
  }
  return str;
}
