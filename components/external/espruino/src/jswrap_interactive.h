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
 * JavaScript methods and functions for the interactive shell
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"
#include "jsinteractive.h"

void jswrap_interface_setBusyIndicator(JsVar *pinVar);
void jswrap_interface_setSleepIndicator(JsVar *pinVar);
void jswrap_interface_setDeepSleep(bool sleep);
void jswrap_interface_trace(JsVar *root);
void jswrap_interface_print(JsVar *v);
void jswrap_interface_edit(JsVar *funcName);
void jswrap_interface_echo(bool echoOn);
JsVar *jswrap_interface_getSerial();
