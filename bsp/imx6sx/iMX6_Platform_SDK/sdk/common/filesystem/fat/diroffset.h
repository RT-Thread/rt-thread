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
/* Fields of Directory Record and their offset in Byte */

#define DIR_NAMEOFFSET					0

#define DIR_EXTOFFSET					8

#define DIR_ATTRIBUTEOFFSET				11

#define DIR_CRTTIMEOFFSET				14

#define DIR_CRTDATEOFFSET				16

#define DIR_LSTACCDATEOFFSET			18

#define DIR_FSTCLUSHIOFFSET				20

#define DIR_WRTTIMEOFFSET				22

#define DIR_WRTDATEOFFSET				24

#define DIR_FSTCLUSLOOFFSET				26

#define DIR_FILESIZEOFFSET				28

/* Fields of Long Directory record and their offset in byte */

#define    LDIRORDOFFSET				0

#define    LDIRNAME1OFFSET				1

#define    LDIRATTRIOFFSET				11

#define    LDIRTYPEOFFSET				12

#define    LDIRCHKSUMOFFSET				13

#define    LDIRNAME2OFFSET				14

#define    LDIRFSTCLUSNOOFFSET			26

#define    LDIRNAME3OFFSET				28

#define DIRRECORDSIZE					32

#define LDIRNAME1SIZE					10

#define LDIRNAME2SIZE					14

#define LDIRNAME3SIZE					 4

#define DIR_NAME_SIZE					11

#define DELETEDDIRRECORDCHARA			0xE5

#define FIRSTSUBDIRNAME                 0x20202E

#define SECONDSUBDIRNAME                0x202E2E

#define DIR_RECORD_PERSECTOR			16

#define LONGDIRATTRIBUTE				0x0F

#define LONGDIRCH_PER_RECORD		   	13
