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
 * JavaScript Pin Object Functions
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"
#include "jsinteractive.h"

bool jswrap_pin_read(JsVar *parent);
void jswrap_pin_set(JsVar *parent);
void jswrap_pin_reset(JsVar *parent);
void jswrap_pin_write(JsVar *parent, bool value);
void jswrap_pin_writeAtTime(JsVar *parent, bool value, JsVarFloat time);
