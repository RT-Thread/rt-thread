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
 * JavaScript String Functions
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"

JsVar *jswrap_string_constructor(JsVar *a);
JsVar *jswrap_string_fromCharCode(JsVarInt code);
JsVar *jswrap_string_charAt(JsVar *parent, JsVarInt idx);
JsVarInt jswrap_string_charCodeAt(JsVar *parent, JsVarInt idx);
JsVarInt jswrap_string_indexOf(JsVar *parent, JsVar *v);
JsVar *jswrap_string_substring(JsVar *parent, JsVarInt pStart, JsVar *vEnd);
JsVar *jswrap_string_substr(JsVar *parent, JsVarInt pStart, JsVar *vLen);
JsVar *jswrap_string_split(JsVar *parent, JsVar *split);
