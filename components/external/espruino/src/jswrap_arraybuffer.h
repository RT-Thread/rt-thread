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
 * JavaScript methods and functions in the global namespace
 * ----------------------------------------------------------------------------
 */
#include "jsvar.h"

JsVar *jswrap_arraybuffer_constructor(JsVarInt byteLength);
JsVar *jswrap_typedarray_constructor(JsVarDataArrayBufferViewType type, JsVar *arr, JsVarInt byteOffset, JsVarInt length);
JsVarFloat jswrap_arraybufferview_interpolate(JsVar *parent, JsVarFloat index);
JsVarFloat jswrap_arraybufferview_interpolate2d(JsVar *parent, JsVarInt width, JsVarFloat x, JsVarFloat y);
