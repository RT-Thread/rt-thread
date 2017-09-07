/*
 * Copyright (c) 2009-2012, Freescale Semiconductor, Inc.
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
#include <stdarg.h>

#ifndef __TEXT_COLOR_H__
#define __TEXT_COLOR_H__

extern const char* const g_TextAttributeDefault;
extern const char* const g_TextAttributeBold;
extern const char* const g_TextAttributeDim;
extern const char* const g_TextAttributeUnderline;
extern const char* const g_TextAttributeBlink;
extern const char* const g_TextAttributeReverse;
extern const char* const g_TextAttributeHidden;

extern const char* const g_TextColorBlack;
extern const char* const g_TextColorRed;
extern const char* const g_TextColorGreen;
extern const char* const g_TextColorYellow;
extern const char* const g_TextColorBlue;
extern const char* const g_TextColorMagenta;
extern const char* const g_TextColorCyan;
extern const char* const g_TextColorWhite;
extern const char* const g_TextColorOrange;
extern const char* const g_TextColorLightBlue;
extern const char* const g_TextColorGray;
extern const char* const g_TextColorPurple;

void printf_color(const char* const attrib, const char* const color, const char* format, ...);

#endif // __TEXT_COLOR_H__
