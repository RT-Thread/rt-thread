/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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
 * @file    text_color.c
 * @brief   This file has the function to print out text in color used in printf
 *
 * @ingroup diag_util
 */

#include <stdio.h>
#include <string.h>
#include "sdk.h"
#include "text_color.h"

int is_color_supported = INVALID_PARAMETER;

const char* const g_TextAttributeDefault   = "\033[00m";
const char* const g_TextAttributeBold      = "\033[01m";
const char* const g_TextAttributeDim       = "\033[02m";
const char* const g_TextAttributeUnderline = "\033[03m";
const char* const g_TextAttributeBlink     = "\033[05m";
const char* const g_TextAttributeReverse   = "\033[07m";
const char* const g_TextAttributeHidden    = "\033[08m";

const char* const g_TextColorBlack         = "\033[30m";
const char* const g_TextColorRed           = "\033[31m";
const char* const g_TextColorGreen         = "\033[32m";
const char* const g_TextColorYellow        = "\033[33m";
const char* const g_TextColorBlue          = "\033[34m";
const char* const g_TextColorMagenta       = "\033[35m";
const char* const g_TextColorCyan          = "\033[36m";
const char* const g_TextColorWhite         = "\033[37m";
const char* const g_TextColorOrange        = "\033[38;5;172m";
const char* const g_TextColorLightBlue     = "\033[38;5;039m";
const char* const g_TextColorGray          = "\033[38;5;008m";
const char* const g_TextColorPurple        = "\033[38;5;097m";

void printf_color(const char* const attrib, const char* const color, const char* format, ...)
{
    if ( is_color_supported )
    {
		if (attrib)
			printf(attrib);
		if (color)
			printf(color);
    }

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    if ( is_color_supported )
    	printf(g_TextAttributeDefault);
}

int get_color_supported()
{
	if ( is_color_supported == INVALID_PARAMETER )
	{
//		<http://invisible-island.net/xterm/ctlseqs/ctlseqs.html>
//
//		Search for "Send Device Attributes" in the page above.
//
//		Send this to query: "\033[>0c"
//
//		A terminal emulator should respond with one of:
//		CSI ? 1 ; 2 c (‘‘VT100 with Advanced Video Option’’)
//		CSI ? 1 ; 0 c (‘‘VT101 with No Options’’)
//		CSI ? 6 c (‘‘VT102’’)
//		CSI ? 6 0 ; 1 ; 2 ; 6 ; 8 ; 9 ; 1 5 ; c (‘‘VT220’’)
//
//		The first response is what I get from Terminal.app on OS X. The equivalent string in C is "\033[?1;2c". (CSI is "ESC[".)
//
//		But basically any response is good enough.
		is_color_supported = TRUE;
	}

  return is_color_supported;
}
