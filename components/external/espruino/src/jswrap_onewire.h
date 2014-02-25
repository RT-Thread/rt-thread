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
 * JavaScript OneWire Functions
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"
#include "jspin.h"

JsVar *jswrap_onewire_constructor(Pin pin);
bool jswrap_onewire_reset(JsVar *parent);
void jswrap_onewire_select(JsVar *parent, JsVarInt rom);
void jswrap_onewire_skip(JsVar *parent);
void jswrap_onewire_write(JsVar *parent, int data, bool leavePowerOn);
JsVarInt jswrap_onewire_read(JsVar *parent);
JsVar *jswrap_onewire_search(JsVar *parent);
