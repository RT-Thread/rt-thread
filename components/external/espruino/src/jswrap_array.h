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
 * JavaScript methods for Arrays
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"

JsVar *jswrap_array_constructor(JsVar *args);
bool jswrap_array_contains(JsVar *parent, JsVar *value);
JsVar *jswrap_array_indexOf(JsVar *parent, JsVar *value);
JsVar *jswrap_array_join(JsVar *parent, JsVar *filler);
JsVar *jswrap_array_map(JsVar *parent, JsVar *funcVar, JsVar *thisVar);
JsVar *jswrap_array_slice(JsVar *parent, JsVar *startVar, JsVar *endVar);
JsVar *jswrap_array_splice(JsVar *parent, JsVarInt index, JsVar *howManyVar, JsVar *element1, JsVar *element2, JsVar *element3, JsVar *element4, JsVar *element5, JsVar *element6);
void jswrap_array_forEach(JsVar *parent, JsVar *funcVar, JsVar *thisVar);
