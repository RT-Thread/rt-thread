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
 * JavaScript Functions for handling Modules
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"

JsVar *jswrap_require(JsVar *modulename);

JsVar *jswrap_modules_getCached();
void jswrap_modules_removeCached(JsVar *id);
void jswrap_modules_removeAllCached();
void jswrap_modules_addCached(JsVar *id, JsVar *sourceCode);
