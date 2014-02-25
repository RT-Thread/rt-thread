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
 * JavaScript Hardware IO Functions
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"
#include "jsinteractive.h"

void jswrap_io_analogWrite(Pin pin, JsVarFloat value, JsVar *options);
void jswrap_io_digitalPulse(Pin pin, bool value, JsVarFloat time);
void jswrap_io_digitalWrite(JsVar *pinVar, JsVarInt value);
JsVarInt jswrap_io_digitalRead(JsVar *pinVar);
void jswrap_io_pinMode(Pin pin, JsVar *mode);

JsVar *jswrap_interface_setInterval(JsVar *func, JsVarFloat timeout);
JsVar *jswrap_interface_setTimeout(JsVar *func, JsVarFloat timeout);
JsVar *jswrap_interface_setWatch(JsVar *funcVar, Pin pin, JsVar *repeatOrObject);
void jswrap_interface_clearInterval(JsVar *idVar);
void jswrap_interface_clearTimeout(JsVar *idVar);
void jswrap_interface_changeInterval(JsVar *idVar, JsVarFloat interval);
void jswrap_interface_clearWatch(JsVar *idVar);
