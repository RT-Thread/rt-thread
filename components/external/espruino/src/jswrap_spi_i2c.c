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
 * JavaScript SPI and I2C Functions
 * ----------------------------------------------------------------------------
 */
#include "jswrap_spi_i2c.h"
#include "jsdevices.h"
#include "jsinteractive.h"
#include "jswrap_arraybuffer.h"

/*JSON{ "type":"class",
        "class" : "SPI",
        "description" : ["This class allows use of the built-in SPI ports. Currently it is SPI master only." ]
}*/

/*JSON{ "type":"object", "name":"SPI1", "instanceof" : "SPI",
        "description" : ["The first SPI port" ],
        "#if" : "SPIS>=1"
}*/
/*JSON{ "type":"object", "name":"SPI2", "instanceof" : "SPI",
        "description" : ["The second SPI port" ],
        "#if" : "SPIS>=2"
}*/
/*JSON{ "type":"object", "name":"SPI3", "instanceof" : "SPI",
        "description" : ["The third SPI port" ],
        "#if" : "SPIS>=3"
}*/


typedef unsigned char (*unsigned_char_map_function)(IOEventFlags device, unsigned char data);

JsVar *map_var_as_unsigned_char(JsVar *src, IOEventFlags device, unsigned_char_map_function map) {
  if (jsvIsNumeric(src)) {
    return jsvNewFromInteger(map(device, (unsigned char)jsvGetInteger(src)));
  } else if (jsvIsString(src)) {
    JsVar *dst = jsvNewFromEmptyString();
    JsvStringIterator it;
    jsvStringIteratorNew(&it, src, 0);
    while (jsvStringIteratorHasChar(&it)) {
      unsigned char in = (unsigned char)jsvStringIteratorGetChar(&it);
      unsigned char out = map(device, in);
      jsvAppendStringBuf(dst, (char*)&out, 1);
      jsvStringIteratorNext(&it);
    }
    jsvStringIteratorFree(&it);
    return dst;
  } else if (jsvIsIterable(src)) {
    // OPT: could use ArrayBuffer for return values
    JsVar *dst = jsvNewWithFlags(JSV_ARRAY);
    JsvIterator it;
    jsvIteratorNew(&it, src);
    while (jsvIteratorHasElement(&it)) {
      unsigned char in = (unsigned char)jsvIteratorGetIntegerValue(&it);
      unsigned char out = map(device, in);
      JsVar *outVar = jsvNewFromInteger(out);
      jsvArrayPushAndUnLock(dst, outVar);
      jsvIteratorNext(&it);
    }
    jsvIteratorFree(&it);
    return dst;
  } else  {
    jsError("Variable type not suited to transmit operation");
    return 0;
  }
}


/*JSON{ "type":"method", "class": "SPI", "name" : "setup",
         "description" : "Set up this SPI port. Master, MSB first, no checksum",
         "generate" : "jswrap_spi_setup",
         "params" : [ [ "options", "JsVar", ["An optional structure containing extra information on initialising the SPI port",
                                              "Please note that baud rate is set to the nearest that can be managed - which may be -+ 50%",
                                              "```{sck:pin, miso:pin, mosi:pin, baud:integer, mode:integer=0 }```",
                                              "If sck,miso and mosi are left out, they will automatically be chosen. However if one or more is specified then the unspecified pins will not be set up.",
                                              "The SPI ```mode``` is between 0 and 3 - see http://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus#Clock_polarity_and_phase",
                                              "On STM32F1-based parts, you cannot mix AF and non-AF pins (SPI pins are usually grouped on the chip - and you can't mix pins from two groups). Espruino will not warn you about this." ] ] ]
}*/
void jswrap_spi_setup(JsVar *parent, JsVar *options) {
  IOEventFlags device = jsiGetDeviceFromClass(parent);
  JshSPIInfo inf;
  jshSPIInitInfo(&inf);
  if (jsvIsObject(options)) {
    inf.pinSCK = jshGetPinFromVarAndUnLock(jsvObjectGetChild(options, "sck", 0));
    inf.pinMISO = jshGetPinFromVarAndUnLock(jsvObjectGetChild(options, "miso", 0));
    inf.pinMOSI = jshGetPinFromVarAndUnLock(jsvObjectGetChild(options, "mosi", 0));
    JsVar *v;
    v = jsvObjectGetChild(options, "baud", 0);
    if (jsvIsNumeric(v))
      inf.baudRate = (int)jsvGetInteger(v);
    v = jsvObjectGetChild(options, "mode", 0);
    if (jsvIsNumeric(v))
      inf.spiMode = ((int)jsvGetInteger(v))&3;;
    jsvUnLock(v);
  }
  jshSPISetup(device, &inf);
  // Set up options, so we can initialise it on startup
  if (options)
    jsvUnLock(jsvSetNamedChild(parent, options, DEVICE_OPTIONS_NAME));
  else
    jsvRemoveNamedChild(parent, DEVICE_OPTIONS_NAME);
}


/*JSON{ "type":"method", "class": "SPI", "name" : "send",
         "description" : [ "Send data down SPI, and return the result",
                           "Sending multiple bytes in one call to send is preferable as they can then be transmitted end to end. Using multiple calls to send() will result in significantly slower transmission speeds." ],
         "generate" : "jswrap_spi_send",
         "params" : [ [ "data", "JsVar", "The data to send - either an integer, array, or string (which is the most efficient)" ],
                      [ "nss_pin", "pin", "An nSS pin - this will be lowered before SPI output and raised afterwards (optional). There will be a small delay between when this is lowered and when sending starts, and also between sending finishing and it being raised." ] ],
         "return" : [ "JsVar", "The data that was returned" ]

}*/
JsVar *jswrap_spi_send(JsVar *parent, JsVar *srcdata, Pin nss_pin) {
  NOT_USED(parent);
  IOEventFlags device = jsiGetDeviceFromClass(parent);

  if (!jshIsDeviceInitialised(device)) {
    JshSPIInfo inf;
    jshSPIInitInfo(&inf);
    jshSPISetup(device, &inf);
  }

  JsVar *dst = 0;

  // assert NSS
  if (nss_pin!=PIN_UNDEFINED) jshPinOutput(nss_pin, false);

  // send data
  if (jsvIsNumeric(srcdata)) {
      jshSPISend(device, (unsigned char)jsvGetInteger(srcdata));
      dst = jsvNewFromInteger(jshSPISend(device, -1)); // retrieve the byte (no send!)
  } else if (jsvIsArray(srcdata)) {
    dst = jsvNewWithFlags(JSV_ARRAY);
    JsArrayIterator it;
    jsvArrayIteratorNew(&it, srcdata);
    int incount = 0, outcount = 0;
    while (jsvArrayIteratorHasElement(&it)) {
      unsigned char in = (unsigned char)jsvGetIntegerAndUnLock(jsvArrayIteratorGetElement(&it));
      incount++;
      int out = jshSPISend(device, in); // this returns -1 only if no data (so if -1 gets in an array it is an error!)
      if (out>=0) {
        outcount++;
        JsVar *outVar = jsvNewFromInteger(out);
        jsvArrayPushAndUnLock(dst, outVar);
      }
      jsvArrayIteratorNext(&it);
    }
    jsvArrayIteratorFree(&it);
    // finally add the remaining bytes  (no send!)
    while (outcount < incount) {
      outcount++;
      int out = jshSPISend(device, -1);
      JsVar *outVar = jsvNewFromInteger(out);
      jsvArrayPushAndUnLock(dst, outVar);
    }
  } else if (jsvIsString(srcdata)) {
    dst = jsvNewFromEmptyString();
    JsvStringIterator it;
    jsvStringIteratorNew(&it, srcdata, 0);
    int incount = 0, outcount = 0;
    while (jsvStringIteratorHasChar(&it)) {
      unsigned char in = (unsigned char)jsvStringIteratorGetChar(&it);
      incount++;
      int out = jshSPISend(device, in);
      if (out>=0) {
        outcount++;
        char outc = (char)out;
        jsvAppendStringBuf(dst, (char*)&outc, 1);
      }
      jsvStringIteratorNext(&it);
    }
    jsvStringIteratorFree(&it);
    // finally add the remaining bytes  (no send!)
    while (outcount < incount) {
      outcount++;
      unsigned char out = (unsigned char)jshSPISend(device, -1);
      jsvAppendStringBuf(dst, (char*)&out, 1);
    }
  } else if (jsvIsIterable(srcdata)) {
    JsVar *lenVar = jsvNewFromInteger(jsvGetLength(srcdata));
    dst = jswrap_typedarray_constructor(ARRAYBUFFERVIEW_UINT8, lenVar,0,0);
    jsvUnLock(lenVar);
    JsvIterator it;
    JsvArrayBufferIterator dstit;
    jsvIteratorNew(&it, srcdata);
    jsvArrayBufferIteratorNew(&dstit, dst, 0);
    while (jsvIteratorHasElement(&it)) {
      unsigned char in = (unsigned char)jsvIteratorGetIntegerValue(&it);
      int out = jshSPISend(device, in);
      jsvArrayBufferIteratorSetIntegerValue(&dstit, out);
      jsvIteratorNext(&it);
      jsvArrayBufferIteratorNext(&dstit);
    }
    jsvIteratorFree(&it);
    jsvArrayBufferIteratorFree(&dstit);
  } else {
    jsError("Variable type not suited to transmit operation");
    dst = 0;
  }

  // de-assert NSS
  if (nss_pin!=PIN_UNDEFINED) jshPinOutput(nss_pin, true);
  return dst;
}

// used by jswrap_spi_send4bit
void spi_send4bit(IOEventFlags device, unsigned char data, int bit0, int bit1) {
  unsigned char lookup[] = {
      (unsigned char)((bit0<<4) | bit0),
      (unsigned char)((bit0<<4) | bit1),
      (unsigned char)((bit1<<4) | bit0),
      (unsigned char)((bit1<<4) | bit1),
  };
  // Send each bit as 4 bits, MSB first
  /*jshSPISend(device, lookup[(data>>6)&3]);
  jshSPISend(device, lookup[(data>>4)&3]);
  jshSPISend(device, lookup[(data>>2)&3]);
  jshSPISend(device, lookup[(data   )&3]);*/
  jshSPISend16(device, (lookup[(data>>6)&3]<<8) | lookup[(data>>4)&3]);
  jshSPISend16(device, (lookup[(data>>2)&3]<<8) | lookup[(data   )&3]);
}

// used by jswrap_spi_send8bit
void spi_send8bit(IOEventFlags device, unsigned char data, int bit0, int bit1) {
  // Send each bit as 8 bits, MSB first
  /*int i;
  for (i=7;i>=0;i--)
    jshSPISend(device, (unsigned char)(((data>>i)&1) ? bit1 : bit0));*/
  jshSPISend(device, ((((data>>7)&1) ? bit1 : bit0)<<8) | (((data>>6)&1) ? bit1 : bit0));
  jshSPISend(device, ((((data>>5)&1) ? bit1 : bit0)<<8) | (((data>>4)&1) ? bit1 : bit0));
  jshSPISend(device, ((((data>>3)&1) ? bit1 : bit0)<<8) | (((data>>2)&1) ? bit1 : bit0));
  jshSPISend(device, ((((data>>1)&1) ? bit1 : bit0)<<8) | (((data>>0)&1) ? bit1 : bit0));
}

/*JSON{ "type":"method", "class": "SPI", "name" : "send4bit",
         "description" : ["Send data down SPI, using 4 bits for each 'real' bit (MSB first). This can be useful for faking one-wire style protocols",
                          "Sending multiple bytes in one call to send is preferable as they can then be transmitted end to end. Using multiple calls to send() will result in significantly slower transmission speeds."],
         "generate" : "jswrap_spi_send4bit",
         "params" : [ [ "data", "JsVar", "The data to send - either an integer, array, or string" ],
                      [ "bit0", "int", "The 4 bits to send for a 0 (MSB first)" ],
                      [ "bit1", "int", "The 4 bits to send for a 1 (MSB first)" ],
                      [ "nss_pin", "pin", "An nSS pin - this will be lowered before SPI output and raised afterwards (optional). There will be a small delay between when this is lowered and when sending starts, and also between sending finishing and it being raised." ] ]
}*/
void jswrap_spi_send4bit(JsVar *parent, JsVar *srcdata, int bit0, int bit1, Pin nss_pin) {
  NOT_USED(parent);
  IOEventFlags device = jsiGetDeviceFromClass(parent);
  jshSPISet16(device, true); // 16 bit output

  if (bit0==0 && bit1==0) {
    bit0 = 0x01;
    bit1 = 0x03;
  }
  bit0 = bit0 & 0x0F;
  bit1 = bit1 & 0x0F;

  if (!jshIsDeviceInitialised(device)) {
    JshSPIInfo inf;
    jshSPIInitInfo(&inf);
    jshSPISetup(device, &inf);
  }

  // assert NSS
  if (nss_pin!=PIN_UNDEFINED) jshPinOutput(nss_pin, false);

  // send data
  if (jsvIsNumeric(srcdata)) {
    spi_send4bit(device, (unsigned char)jsvGetInteger(srcdata), bit0, bit1);
  } else if (jsvIsIterable(srcdata)) {
    jshInterruptOff();
    JsvIterator it;
    jsvIteratorNew(&it, srcdata);
    while (jsvIteratorHasElement(&it)) {
      unsigned char in = (unsigned char)jsvIteratorGetIntegerValue(&it);
      spi_send4bit(device, in, bit0, bit1);
      jsvIteratorNext(&it);
    }
    jsvIteratorFree(&it);
    jshInterruptOn();
  } else {
    jsError("Variable type not suited to transmit operation");
  }

  // de-assert NSS
  if (nss_pin!=PIN_UNDEFINED) jshPinOutput(nss_pin, true);
  jshSPISet16(device, false); // back to 8 bit
}

/*JSON{ "type":"method", "class": "SPI", "name" : "send8bit",
         "description" : ["Send data down SPI, using 8 bits for each 'real' bit (MSB first). This can be useful for faking one-wire style protocols",
"Sending multiple bytes in one call to send is preferable as they can then be transmitted end to end. Using multiple calls to send() will result in significantly slower transmission speeds."],
         "generate" : "jswrap_spi_send8bit",
         "params" : [ [ "data", "JsVar", "The data to send - either an integer, array, or string" ],
                      [ "bit0", "int", "The 8 bits to send for a 0 (MSB first)" ],
                      [ "bit1", "int", "The 8 bits to send for a 1 (MSB first)" ],
                      [ "nss_pin", "pin", "An nSS pin - this will be lowered before SPI output and raised afterwards (optional). There will be a small delay between when this is lowered and when sending starts, and also between sending finishing and it being raised" ] ]
}*/
void jswrap_spi_send8bit(JsVar *parent, JsVar *srcdata, int bit0, int bit1, Pin nss_pin) {
  NOT_USED(parent);
  IOEventFlags device = jsiGetDeviceFromClass(parent);
  jshSPISet16(device, true); // 16 bit output

  if (bit0==0 && bit1==0) {
    bit0 = 0x03;
    bit1 = 0x0F;
  }
  bit0 = bit0 & 0xFF;
  bit1 = bit1 & 0xFF;

  if (!jshIsDeviceInitialised(device)) {
    JshSPIInfo inf;
    jshSPIInitInfo(&inf);
    jshSPISetup(device, &inf);
  }

  // assert NSS
  if (nss_pin!=PIN_UNDEFINED) jshPinOutput(nss_pin, false);

  // send data
  if (jsvIsNumeric(srcdata)) {
    spi_send8bit(device, (unsigned char)jsvGetInteger(srcdata), bit0, bit1);
  } else if (jsvIsIterable(srcdata)) {
    jshInterruptOff();
    JsvIterator it;
    jsvIteratorNew(&it, srcdata);
    while (jsvIteratorHasElement(&it)) {
      unsigned char in = (unsigned char)jsvIteratorGetIntegerValue(&it);
      spi_send8bit(device, in, bit0, bit1);
      jsvIteratorNext(&it);
    }
    jsvIteratorFree(&it);
    jshInterruptOn();
  } else {
    jsError("Variable type not suited to transmit operation");
  }

  // de-assert NSS
  if (nss_pin!=PIN_UNDEFINED) jshPinOutput(nss_pin, true);
  jshSPISet16(device, false); // back to 8 bit
}

/*JSON{ "type":"class",
        "class" : "I2C",
        "description" : ["This class allows use of the built-in I2C ports. Currently it allows I2C Master mode only.",
                         "All addresses are in 7 bit format. If you have an 8 bit address then you need to shift it one bit to the right." ]
}*/

/*JSON{ "type":"object", "name":"I2C1", "instanceof" : "I2C",
        "description" : ["The first I2C port" ],
        "#if" : "I2CS>=1"
}*/
/*JSON{ "type":"object", "name":"I2C2", "instanceof" : "I2C",
        "description" : ["The second I2C port" ],
        "#if" : "I2CS>=2"
}*/
/*JSON{ "type":"object", "name":"I2C3", "instanceof" : "I2C",
        "description" : ["The third I2C port" ],
        "#if" : "I2CS>=3"
}*/



/*JSON{ "type":"method", "class": "I2C", "name" : "setup",
         "description" : "Set up this I2C port",
         "generate" : "jswrap_i2c_setup",
         "params" : [ [ "options", "JsVar", ["An optional structure containing extra information on initialising the I2C port",
                                             "{scl:pin, sda:pin}" ] ] ]
}*/
void jswrap_i2c_setup(JsVar *parent, JsVar *options) {
  IOEventFlags device = jsiGetDeviceFromClass(parent);
  JshI2CInfo inf;
  jshI2CInitInfo(&inf);
  if (jsvIsObject(options)) {
    inf.pinSCL = jshGetPinFromVarAndUnLock(jsvObjectGetChild(options, "scl", 0));
    inf.pinSDA = jshGetPinFromVarAndUnLock(jsvObjectGetChild(options, "sda", 0));
  }
  jshI2CSetup(device, &inf);
  // Set up options, so we can initialise it on startup
  if (options)
    jsvUnLock(jsvSetNamedChild(parent, options, DEVICE_OPTIONS_NAME));
  else
    jsvRemoveNamedChild(parent, DEVICE_OPTIONS_NAME);
}




/*JSON{ "type":"method", "class": "I2C", "name" : "writeTo",
         "description" : "Transmit to the slave device with the given address. This is like Arduino's beginTransmission, write, and endTransmission rolled up into one.",
         "generate" : "jswrap_i2c_writeTo",
         "params" : [ [ "address", "int", "The 7 bit address of the device to transmit to" ],
                      [ "data", "JsVar", "The Data to send - either a byte, an array of bytes, or a string" ]]
}*/
#define I2C_BUFSIZE 32
void jswrap_i2c_writeTo(JsVar *parent, int address, JsVar *data) {
  IOEventFlags device = jsiGetDeviceFromClass(parent);

  if (jsvIsNumeric(data)) {
    unsigned char buf[1];
    buf[0] = (unsigned char)jsvGetInteger(data);
    jshI2CWrite(device, (unsigned char)address, 1, buf);
  } else if (jsvIsIterable(data)) {
    unsigned char buf[I2C_BUFSIZE];
    int i=0;
    JsvIterator it;
    jsvIteratorNew(&it, data);
    while (jsvIteratorHasElement(&it)) {
      if (i<I2C_BUFSIZE) buf[i++] = (unsigned char)jsvIteratorGetIntegerValue(&it);
      jsvIteratorNext(&it);
    }
    jsvIteratorFree(&it);
    if (i>=I2C_BUFSIZE) jsError("Too many bytes to write - truncating");
    jshI2CWrite(device, (unsigned char)address, i, buf);
  } else {
    jsError("Variable type not suited to writeTo operation");
  }
}

/*JSON{ "type":"method", "class": "I2C", "name" : "readFrom",
         "description" : "Request bytes from the given slave device, and return them as an array. This is like using Arduino Wire's requestFrom, available and read functions.  Sends a STOP",
         "generate" : "jswrap_i2c_readFrom",
         "params" : [ [ "address", "int", "The 7 bit address of the device to request bytes from" ],
                      [ "quantity", "int", "The number of bytes to request" ] ],
         "return" : [ "JsVar", "The data that was returned - an array of bytes" ]
}*/
JsVar *jswrap_i2c_readFrom(JsVar *parent, int address, int nBytes) {
  unsigned char buf[I2C_BUFSIZE];
  if (nBytes>I2C_BUFSIZE) {
    jsError("Too many bytes to read - truncating");
    nBytes = I2C_BUFSIZE;
  }

  IOEventFlags device = jsiGetDeviceFromClass(parent);
  jshI2CRead(device, (unsigned char)address, nBytes, buf);

  // OPT: could use ArrayBuffer for return values
  JsVar *array = jsvNewWithFlags(JSV_ARRAY);
  if (array) {
    int i;
    for (i=0;i<nBytes;i++) {
      JsVar *v = jsvNewFromInteger(buf[i]);
      jsvArrayPushAndUnLock(array, v);
    }
  }
  return array;
}
