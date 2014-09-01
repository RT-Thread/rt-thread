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
 * Interactive Shell implementation
 * ----------------------------------------------------------------------------
 */
#ifndef JSINTERACTIVE_H_
#define JSINTERACTIVE_H_

#include "jsparse.h"
#include "jshardware.h"

#define JSI_WATCHES_NAME ">watches"
#define JSI_TIMERS_NAME ">timers"
#define JSI_HISTORY_NAME ">history"
#define JSI_INIT_CODE_NAME ">init"
#define JSI_ONINIT_NAME "onInit"

/// autoLoad = do we load the current state if it exists?
void jsiInit(bool autoLoad);
void jsiKill();

void jsiLoop();

/// Tries to get rid of some memory (by clearing command history). Returns true if it got rid of something, false if it didn't.
bool jsiFreeMoreMemory();

bool jsiHasTimers(); // are there timers still left to run?
JsParse *jsiGetParser();

/// Queue up callbacks for other things (touchscreen? network?)
void jsiQueueObjectCallbacks(JsVar *object, const char *callbackName, JsVar *arg0, JsVar *arg1);


IOEventFlags jsiGetDeviceFromClass(JsVar *deviceClass);
JsVar *jsiGetClassNameFromDevice(IOEventFlags device);

/// Change the console to a new location
void jsiSetConsoleDevice(IOEventFlags device);
/// Get the device that the console is currently on
IOEventFlags jsiGetConsoleDevice();
/// Transmit a byte
void jsiConsolePrintChar(char data);
/// Transmit a string
void jsiConsolePrint(const char *str);
/// Write the formatted string to the console (see vcbprintf)
void jsiConsolePrintf(const char *fmt, ...);
/// Print the contents of a string var - directly
void jsiConsolePrintStringVar(JsVar *v);
/// Transmit an integer
void jsiConsolePrintInt(JsVarInt d);
/// Transmit a position in the lexer (for reporting errors)
void jsiConsolePrintPosition(struct JsLex *lex, int tokenPos);
/// Transmit the current line, along with a marker of where the error was (for reporting errors)
void jsiConsolePrintTokenLineMarker(struct JsLex *lex, int tokenPos);
/// Print the contents of a string var to a device - directly
void jsiTransmitStringVar(IOEventFlags device, JsVar *v);
/// If the input line was shown in the console, remove it
void jsiConsoleRemoveInputLine();
/// Change what is in the inputline into something else (and update the console)
void jsiReplaceInputLine(JsVar *newLine);

/// Flags for jsiSetBusy - THESE SHOULD BE 2^N
typedef enum {
  BUSY_INTERACTIVE = 1,
  BUSY_TRANSMIT    = 2,
  // ???           = 4
} JsiBusyDevice;
/// Shows a busy indicator, if one is set up
void jsiSetBusy(JsiBusyDevice device, bool isBusy);
/// Shows a sleep indicator, if one is set up
void jsiSetSleep(bool isSleep);


// for jswrap_interactive/io.c ----------------------------------------------------
typedef enum {
 TODO_NOTHING = 0,
 TODO_FLASH_SAVE = 1,
 TODO_FLASH_LOAD = 2,
 TODO_RESET = 4,
} TODOFlags;
#define USART_CALLBACK_NAME "_callback"
#define USART_BAUDRATE_NAME "_baudrate"
#define DEVICE_OPTIONS_NAME "_options"

extern Pin pinBusyIndicator;
extern Pin pinSleepIndicator;
extern bool echo;
extern bool allowDeepSleep;
void jsiDumpState();
void jsiSetTodo(TODOFlags newTodo);
#define TIMER_MIN_INTERVAL 0.1 // in milliseconds
extern JsVarRef timerArray; // Linked List of timers to check and run
extern JsVarRef watchArray; // Linked List of input watches to check and run
// end for jswrap_interactive/io.c ------------------------------------------------


#endif /* JSINTERACTIVE_H_ */
