# Eclipse Paho MQTT C/C++ client for Embedded platforms

This repository contains the source code for the [Eclipse Paho](http://eclipse.org/paho) MQTT C/C++ client library for Embedded platorms.

It is dual licensed under the EPL and EDL (see about.html and notice.html for more details).  You can choose which of these licenses you want to use the code under.  The EDL allows you to embed the code into your application, and distribute your application in binary or source form without contributing any of your code, or any changes you make back to Paho.  See the EDL for the exact conditions.

The MQTTPacket directory contains the lowest level C library with the smallest requirements.  This supplies simple serialization 
and deserialization routines.  It is mainly up to you to write and read to and from the network.


## 编译

* 在rtconfig.h中添加 `#define RT_USING_PAHOMQTT`
* 开启LWIP组件

## 使用方法

参见 `rt-thread\examples\network\mqttclient.c`

## 关于MQTT

参见 [MQTT community site](http://mqtt.org).
