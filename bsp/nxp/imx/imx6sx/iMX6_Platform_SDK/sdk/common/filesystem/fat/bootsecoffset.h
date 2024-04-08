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

/* Fields of BootSector and their offset in Byte*/

#define BYTESPERSECTOROFFSET  11

#define SECPERCLUSTEROFFSET   13

#define RSVDSECOFFSET         14

#define NOFATSOFFSET          16

#define ROOTDIRENTRYOFFSET    17

#define TOTSECTOROFFSET       19

#define MEDIAOFFSET           21

#define FATSIZEOFFSET         22

#define SECPERTRACKOFFSET     24

#define NUMHEADSOFFSET        26

#define HIDSECOFFSET          28

#define TOTBIGSECOFFSET       32

#define DRIVEROOFFSET         36

#define RSVDOFFSET            37

#define BOOTSIGOFFSET         38

#define VOLIDOFFSET           39

#define VOLLABOFFSET          43

#define FILSYSTYPEOFFSET      54

/* FOR FAT32 FILESYSTEM ONLY , NOT DEFINED FOR FAT12 OF FAT16 TYPE OF FILESYSTEM */

#define FAT32SIZEOFFSET      36

#define FAT32FLAGOFFSET      40

#define FAT32FSVERSIONOFFSET 42

#define FAT32ROOTCLUSOFFSET  44

#define FAT32FSINFOOFFSET    48

#define FAT32BKBOOTSECOFFSET 50

#define FAT32DRIVEROOFFSET   64

#define FAT32RSVDOFFSET      65

#define FAT32BOOTSIGOFFSET   66

#define FAT32VOLIDOFFSET     67

#define FAT32VOLLABOFFSET    71

#define FAT32FSTYPEOFFSET    82

  /* FAT32 FSINFO Offset */

#define FAT32FSIFREECOUNTOFFSET		488
#define FAT32FSINXTFREEOFFSET		492
