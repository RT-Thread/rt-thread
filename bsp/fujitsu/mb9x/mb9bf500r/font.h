/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __FONT_H
#define __FONT_H

/*  Font definition  */
#define ________    0x00
#define _______X    0x01
#define ______X_    0x02
#define ______XX    0x03
#define _____X__    0x04
#define _____X_X    0x05
#define _____XX_    0x06
#define _____XXX    0x07
#define ____X___    0x08
#define ____X__X    0x09
#define ____X_X_    0x0a
#define ____X_XX    0x0b
#define ____XX__    0x0c
#define ____XX_X    0x0d
#define ____XXX_    0x0e
#define ____XXXX    0x0f
#define ___X____    0x10
#define ___X___X    0x11
#define ___X__X_    0x12
#define ___X__XX    0x13
#define ___X_X__    0x14
#define ___X_X_X    0x15
#define ___X_XX_    0x16
#define ___X_XXX    0x17
#define ___XX___    0x18
#define ___XX__X    0x19
#define ___XX_X_    0x1a
#define ___XX_XX    0x1b
#define ___XXX__    0x1c
#define ___XXX_X    0x1d
#define ___XXXX_    0x1e
#define ___XXXXX    0x1f
#define __X_____    0x20
#define __X____X    0x21
#define __X___X_    0x22
#define __X___XX    0x23
#define __X__X__    0x24
#define __X__X_X    0x25
#define __X__XX_    0x26
#define __X__XXX    0x27
#define __X_X___    0x28
#define __X_X__X    0x29
#define __X_X_X_    0x2a
#define __X_X_XX    0x2b
#define __X_XX__    0x2c
#define __X_XX_X    0x2d
#define __X_XXX_    0x2e
#define __X_XXXX    0x2f
#define __XX____    0x30
#define __XX___X    0x31
#define __XX__X_    0x32
#define __XX__XX    0x33
#define __XX_X__    0x34
#define __XX_X_X    0x35
#define __XX_XX_    0x36
#define __XX_XXX    0x37
#define __XXX___    0x38
#define __XXX__X    0x39
#define __XXX_X_    0x3a
#define __XXX_XX    0x3b
#define __XXXX__    0x3c
#define __XXXX_X    0x3d
#define __XXXXX_    0x3e
#define __XXXXXX    0x3f
#define _X______    0x40
#define _X_____X    0x41
#define _X____X_    0x42
#define _X____XX    0x43
#define _X___X__    0x44
#define _X___X_X    0x45
#define _X___XX_    0x46
#define _X___XXX    0x47
#define _X__X___    0x48
#define _X__X__X    0x49
#define _X__X_X_    0x4a
#define _X__X_XX    0x4b
#define _X__XX__    0x4c
#define _X__XX_X    0x4d
#define _X__XXX_    0x4e
#define _X__XXXX    0x4f
#define _X_X____    0x50
#define _X_X___X    0x51
#define _X_X__X_    0x52
#define _X_X__XX    0x53
#define _X_X_X__    0x54
#define _X_X_X_X    0x55
#define _X_X_XX_    0x56
#define _X_X_XXX    0x57
#define _X_XX___    0x58
#define _X_XX__X    0x59
#define _X_XX_X_    0x5a
#define _X_XX_XX    0x5b
#define _X_XXX__    0x5c
#define _X_XXX_X    0x5d
#define _X_XXXX_    0x5e
#define _X_XXXXX    0x5f
#define _XX_____    0x60
#define _XX____X    0x61
#define _XX___X_    0x62
#define _XX___XX    0x63
#define _XX__X__    0x64
#define _XX__X_X    0x65
#define _XX__XX_    0x66
#define _XX__XXX    0x67
#define _XX_X___    0x68
#define _XX_X__X    0x69
#define _XX_X_X_    0x6a
#define _XX_X_XX    0x6b
#define _XX_XX__    0x6c
#define _XX_XX_X    0x6d
#define _XX_XXX_    0x6e
#define _XX_XXXX    0x6f
#define _XXX____    0x70
#define _XXX___X    0x71
#define _XXX__X_    0x72
#define _XXX__XX    0x73
#define _XXX_X__    0x74
#define _XXX_X_X    0x75
#define _XXX_XX_    0x76
#define _XXX_XXX    0x77
#define _XXXX___    0x78
#define _XXXX__X    0x79
#define _XXXX_X_    0x7a
#define _XXXX_XX    0x7b
#define _XXXXX__    0x7c
#define _XXXXX_X    0x7d
#define _XXXXXX_    0x7e
#define _XXXXXXX    0x7f
#define X_______    0x80
#define X______X    0x81
#define X_____X_    0x82
#define X_____XX    0x83
#define X____X__    0x84
#define X____X_X    0x85
#define X____XX_    0x86
#define X____XXX    0x87
#define X___X___    0x88
#define X___X__X    0x89
#define X___X_X_    0x8a
#define X___X_XX    0x8b
#define X___XX__    0x8c
#define X___XX_X    0x8d
#define X___XXX_    0x8e
#define X___XXXX    0x8f
#define X__X____    0x90
#define X__X___X    0x91
#define X__X__X_    0x92
#define X__X__XX    0x93
#define X__X_X__    0x94
#define X__X_X_X    0x95
#define X__X_XX_    0x96
#define X__X_XXX    0x97
#define X__XX___    0x98
#define X__XX__X    0x99
#define X__XX_X_    0x9a
#define X__XX_XX    0x9b
#define X__XXX__    0x9c
#define X__XXX_X    0x9d
#define X__XXXX_    0x9e
#define X__XXXXX    0x9f
#define X_X_____    0xa0
#define X_X____X    0xa1
#define X_X___X_    0xa2
#define X_X___XX    0xa3
#define X_X__X__    0xa4
#define X_X__X_X    0xa5
#define X_X__XX_    0xa6
#define X_X__XXX    0xa7
#define X_X_X___    0xa8
#define X_X_X__X    0xa9
#define X_X_X_X_    0xaa
#define X_X_X_XX    0xab
#define X_X_XX__    0xac
#define X_X_XX_X    0xad
#define X_X_XXX_    0xae
#define X_X_XXXX    0xaf
#define X_XX____    0xb0
#define X_XX___X    0xb1
#define X_XX__X_    0xb2
#define X_XX__XX    0xb3
#define X_XX_X__    0xb4
#define X_XX_X_X    0xb5
#define X_XX_XX_    0xb6
#define X_XX_XXX    0xb7
#define X_XXX___    0xb8
#define X_XXX__X    0xb9
#define X_XXX_X_    0xba
#define X_XXX_XX    0xbb
#define X_XXXX__    0xbc
#define X_XXXX_X    0xbd
#define X_XXXXX_    0xbe
#define X_XXXXXX    0xbf
#define XX______    0xc0
#define XX_____X    0xc1
#define XX____X_    0xc2
#define XX____XX    0xc3
#define XX___X__    0xc4
#define XX___X_X    0xc5
#define XX___XX_    0xc6
#define XX___XXX    0xc7
#define XX__X___    0xc8
#define XX__X__X    0xc9
#define XX__X_X_    0xca
#define XX__X_XX    0xcb
#define XX__XX__    0xcc
#define XX__XX_X    0xcd
#define XX__XXX_    0xce
#define XX__XXXX    0xcf
#define XX_X____    0xd0
#define XX_X___X    0xd1
#define XX_X__X_    0xd2
#define XX_X__XX    0xd3
#define XX_X_X__    0xd4
#define XX_X_X_X    0xd5
#define XX_X_XX_    0xd6
#define XX_X_XXX    0xd7
#define XX_XX___    0xd8
#define XX_XX__X    0xd9
#define XX_XX_X_    0xda
#define XX_XX_XX    0xdb
#define XX_XXX__    0xdc
#define XX_XXX_X    0xdd
#define XX_XXXX_    0xde
#define XX_XXXXX    0xdf
#define XXX_____    0xe0
#define XXX____X    0xe1
#define XXX___X_    0xe2
#define XXX___XX    0xe3
#define XXX__X__    0xe4
#define XXX__X_X    0xe5
#define XXX__XX_    0xe6
#define XXX__XXX    0xe7
#define XXX_X___    0xe8
#define XXX_X__X    0xe9
#define XXX_X_X_    0xea
#define XXX_X_XX    0xeb
#define XXX_XX__    0xec
#define XXX_XX_X    0xed
#define XXX_XXX_    0xee
#define XXX_XXXX    0xef
#define XXXX____    0xf0
#define XXXX___X    0xf1
#define XXXX__X_    0xf2
#define XXXX__XX    0xf3
#define XXXX_X__    0xf4
#define XXXX_X_X    0xf5
#define XXXX_XX_    0xf6
#define XXXX_XXX    0xf7
#define XXXXX___    0xf8
#define XXXXX__X    0xf9
#define XXXXX_X_    0xfa
#define XXXXX_XX    0xfb
#define XXXXXX__    0xfc
#define XXXXXX_X    0xfd
#define XXXXXXX_    0xfe
#define XXXXXXXX    0xff




const unsigned char  FONTTYPE8_8[][8] = {
/* blank */
  {
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}

/*  0  */
 ,{
   __XXX___,
   _XX_XX__,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XX_XX__,
   __XXX___,
   ________}

/*  1  */
 ,{
   ___XX___,
   __XXX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   _XXXXXX_,
   ________}

/*  2  */
 ,{
   _XXXXX__,
   XX___XX_,
   _____XX_,
   ___XXX__,
   __XX____,
   _XX__XX_,
   XXXXXXX_,
   ________}

/*  3  */
 ,{
   _XXXXX__,
   XX___XX_,
   _____XX_,
   __XXXX__,
   _____XX_,
   XX___XX_,
   _XXXXX__,
   ________}

/*  4  */
 ,{
   ___XXX__,
   __XXXX__,
   _XX_XX__,
   XX__XX__,
   XXXXXXX_,
   ____XX__,
   ___XXXX_,
   ________}

/*  5  */
 ,{
   XXXXXXX_,
   XX______,
   XX______,
   XXXXXX__,
   _____XX_,
   XX___XX_,
   _XXXXX__,
   ________}

/*  6  */
 ,{
   __XXX___,
   _XX_____,
   XX______,
   XXXXXX__,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}

/*  7  */
 ,{
   XXXXXXX_,
   XX___XX_,
   ____XX__,
   ___XX___,
   __XX____,
   __XX____,
   __XX____,
   ________}

/*  8  */
 ,{
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}

/*  9  */
 ,{
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   _XXXXXX_,
   _____XX_,
   ____XX__,
   _XXXX___,
   ________}

/*  A  */
 ,{
   __XXX___,
   _XX_XX__,
   XX___XX_,
   XXXXXXX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   ________}

/*  B  */
 ,{
   XXXXXX__,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   _XX__XX_,
   _XX__XX_,
   XXXXXX__,
   ________}

/*  C  */
 ,{
   __XXXX__,
   _XX__XX_,
   XX______,
   XX______,
   XX______,
   _XX__XX_,
   __XXXX__,
   ________}

/*  D  */
 ,{
   XXXXX___,
   _XX_XX__,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   _XX_XX__,
   XXXXX___,
   ________}

/*  E  */
 ,{
   XXXXXXX_,
   _XX___X_,
   _XX_X___,
   _XXXX___,
   _XX_X___,
   _XX___X_,
   XXXXXXX_,
   ________}

/*  F  */
 ,{
   XXXXXXX_,
   _XX___X_,
   _XX_X___,
   _XXXX___,
   _XX_X___,
   _XX_____,
   XXXX____,
   ________}

/*  G  */
 ,{
   __XXXX__,
   _XX__XX_,
   XX______,
   XX______,
   XX__XXX_,
   _XX__XX_,
   __XXX_X_,
   ________}

/*  H  */
 ,{
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XXXXXXX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   ________}

/*  I  */
 ,{
   __XXXX__,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}

/*  J  */
 ,{
   ___XXXX_,
   ____XX__,
   ____XX__,
   ____XX__,
   XX__XX__,
   XX__XX__,
   _XXXX___,
   ________}

/*  K  */
 ,{
   XXX__XX_,
   _XX__XX_,
   _XX_XX__,
   _XXXX___,
   _XX_XX__,
   _XX__XX_,
   XXX__XX_,
   ________}

/*  L  */
 ,{
   XXXX____,
   _XX_____,
   _XX_____,
   _XX_____,
   _XX___X_,
   _XX__XX_,
   XXXXXXX_,
   ________}

/*  M  */
 ,{
   XX___XX_,
   XXX_XXX_,
   XXXXXXX_,
   XXXXXXX_,
   XX_X_XX_,
   XX___XX_,
   XX___XX_,
   ________}

/*  N  */
 ,{
   XX___XX_,
   XXX__XX_,
   XXXX_XX_,
   XX_XXXX_,
   XX__XXX_,
   XX___XX_,
   XX___XX_,
   ________}

/*  O  */
 ,{
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}

/*  P  */
 ,{
   XXXXXX__,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   _XX_____,
   _XX_____,
   XXXX____,
   ________}

/*  Q  */
 ,{
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX__XXX_,
   _XXXXX__,
   ____XXX_}

/*  R  */
 ,{
   XXXXXX__,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   _XX_XX__,
   _XX__XX_,
   XXX__XX_,
   ________}

/*  S  */
 ,{
   __XXXX__,
   _XX__XX_,
   __XX____,
   ___XX___,
   ____XX__,
   _XX__XX_,
   __XXXX__,
   ________}

/*  T  */
 ,{
   _XXXXXX_,
   _XXXXXX_,
   _X_XX_X_,
   ___XX___,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}

/*  U  */
 ,{
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}

/*  V  */
 ,{
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XX_XX__,
   __XXX___,
   ________}

/*  W  */
 ,{
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX_X_XX_,
   XX_X_XX_,
   XXXXXXX_,
   _XX_XX__,
   ________}

/*  X  */
 ,{
   XX___XX_,
   XX___XX_,
   _XX_XX__,
   __XXX___,
   _XX_XX__,
   XX___XX_,
   XX___XX_,
   ________}

/*  Y  */
 ,{
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   __XXXX__,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}

/*  Z  */
 ,{
   XXXXXXX_,
   XX___XX_,
   X___XX__,
   ___XX___,
   __XX__X_,
   _XX__XX_,
   XXXXXXX_,
   ________}

/*  a  */
 ,{
   ________,
   ________,
   _XXXX___,
   ____XX__,
   _XXXXX__,
   XX__XX__,
   _XXX_XX_,
   ________}

/*  b  */
 ,{
   XXX_____,
   _XX_____,
   _XXXXX__,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   XX_XXX__,
   ________}

/*  c  */
 ,{
   ________,
   ________,
   _XXXXX__,
   XX___XX_,
   XX______,
   XX___XX_,
   _XXXXX__,
   ________}

/*  d  */
 ,{
   ___XXX__,
   ____XX__,
   _XXXXX__,
   XX__XX__,
   XX__XX__,
   XX__XX__,
   _XXX_XX_,
   ________}

/*  e  */
 ,{
   ________,
   ________,
   _XXXXX__,
   XX___XX_,
   XXXXXXX_,
   XX______,
   _XXXXX__,
   ________}

/*  f  */
 ,{
   __XXXX__,
   _XX__XX_,
   _XX_____,
   XXXXX___,
   _XX_____,
   _XX_____,
   XXXX____,
   ________}

/*  g  */
 ,{
   ________,
   ________,
   _XXX_XX_,
   XX__XX__,
   XX__XX__,
   _XXXXX__,
   ____XX__,
   XXXXX___}

/*  h  */
 ,{
   XXX_____,
   _XX_____,
   _XX_XX__,
   _XXX_XX_,
   _XX__XX_,
   _XX__XX_,
   XXX__XX_,
   ________}

/*  i  */
 ,{
   ___XX___,
   ________,
   __XXX___,
   ___XX___,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}

/*  j  */
 ,{
   _____XX_,
   ________,
   _____XX_,
   _____XX_,
   _____XX_,
   _XX__XX_,
   _XX__XX_,
   __XXXX__}

/*  k  */
 ,{
   XXX_____,
   _XX_____,
   _XX__XX_,
   _XX_XX__,
   _XXXX___,
   _XX_XX__,
   XXX__XX_,
   ________}

/*  l  */
 ,{
   __XXX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}

/*  m  */
 ,{
   ________,
   ________,
   XXX_XX__,
   XXXXXXX_,
   XX_X_XX_,
   XX_X_XX_,
   XX_X_XX_,
   ________}

/*  n  */
 ,{
   ________,
   ________,
   XX_XXX__,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   ________}

/*  o  */
 ,{
   ________,
   ________,
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}

/*  p  */
 ,{
   ________,
   ________,
   XX_XXX__,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   _XX_____,
   XXXX____}

/*  q  */
 ,{
   ________,
   ________,
   _XXX_XX_,
   XX__XX__,
   XX__XX__,
   _XXXXX__,
   ____XX__,
   ___XXXX_}

/*  r  */
 ,{
   ________,
   ________,
   XX_XXX__,
   _XXX_XX_,
   _XX_____,
   _XX_____,
   XXXX____,
   ________}

/*  s  */
 ,{
   ________,
   ________,
   _XXXXXX_,
   XX______,
   _XXXXX__,
   _____XX_,
   XXXXXX__,
   ________}

/*  t  */
 ,{
   __XX____,
   __XX____,
   XXXXXX__,
   __XX____,
   __XX____,
   __XX_XX_,
   ___XXX__,
   ________}

/*  u  */
 ,{
   ________,
   ________,
   XX__XX__,
   XX__XX__,
   XX__XX__,
   XX__XX__,
   _XXX_XX_,
   ________}

/*  v  */
 ,{
   ________,
   ________,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XX_XX__,
   __XXX___,
   ________}

/*  w  */
 ,{
   ________,
   ________,
   XX___XX_,
   XX_X_XX_,
   XX_X_XX_,
   XXXXXXX_,
   _XX_XX__,
   ________}

/*  x  */
 ,{
   ________,
   ________,
   XX___XX_,
   _XX_XX__,
   __XXX___,
   _XX_XX__,
   XX___XX_,
   ________}

/*  y  */
 ,{
   ________,
   ________,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XXXXXX_,
   _____XX_,
   XXXXXX__}

/*  z  */
 ,{
   ________,
   ________,
   _XXXXXX_,
   _X__XX__,
   ___XX___,
   __XX__X_,
   _XXXXXX_,
   ________}

};

#endif /* __FONT_H */
