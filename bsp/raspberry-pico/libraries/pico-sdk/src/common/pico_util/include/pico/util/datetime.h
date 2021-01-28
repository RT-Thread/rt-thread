/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_DATETIME_H
#define _PICO_DATETIME_H

#include "pico.h"

/** \file datetime.h
 * \defgroup util_datetime datetime
 * \brief Date/Time formatting
 * \ingroup pico_util
 */

/*! \brief  Convert a datetime_t structure to a string
 *  \ingroup util_datetime
 *
 * \param buf character buffer to accept generated string
 * \param buf_size The size of the passed in buffer
 * \param t The datetime to be converted.
 */
void datetime_to_str(char *buf, uint buf_size, const datetime_t *t);

#endif
