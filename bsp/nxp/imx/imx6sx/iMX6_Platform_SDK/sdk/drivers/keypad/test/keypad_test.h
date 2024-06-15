/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file keypad_test.h
 * @brief Keypad unit tests header file.
 *
 * @ingroup diag_keypad
 */

#ifndef __KEYPAD_TEST_H__
#define __KEYPAD_TEST_H__

#include "sdk.h"

#define NO_KEY "NOT VALID"

static const char* KEYPAD_MAP[8][8] = {
    /* COL0    COL1    COL2    COL3    COL4    COL5    COL6    COL7 */
    { NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY }, /* ROW0 */
    { NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY }, /* ROW1 */
    { NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY }, /* ROW2 */
    { NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY, NO_KEY }, /* ROW3 */
    { NO_KEY, NO_KEY, NO_KEY, NO_KEY, "SW4" , "SW6" , "SW5" , "SW7"  }, /* ROW4 */
    { NO_KEY, NO_KEY, NO_KEY, NO_KEY, "SW8" , "SW10", "SW9" , "SW11" }, /* ROW5 */
    { NO_KEY, NO_KEY, NO_KEY, NO_KEY, "SW12", "SW14", "SW13", "SW15" }, /* ROW6 */
    { NO_KEY, NO_KEY, NO_KEY, NO_KEY, "SW16", "SW18", "SW17", "SW19" }, /* ROW7 */
};

#endif /* __KEYPAD_TEST_H__ */
