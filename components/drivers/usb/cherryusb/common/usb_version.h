/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USB_VERSION_H
#define USB_VERSION_H

#ifdef CHERRYUSB_VERSION
#warning "Please do not define CHERRYUSB_VERSION in usb_config.h"
#undef CHERRYUSB_VERSION
#endif
#ifdef CHERRYUSB_VERSION_STR
#warning "Please do not define CHERRYUSB_VERSION_STR in usb_config.h"
#undef CHERRYUSB_VERSION_STR
#endif

#define CHERRYUSB_VERSION     0x010400
#define CHERRYUSB_VERSION_STR "v1.4.0"

#endif