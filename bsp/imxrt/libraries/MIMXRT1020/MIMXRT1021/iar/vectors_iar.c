/*******************************************************************************
*
* Copyright 2013 - 2016, Freescale Semiconductor, Inc.
* Copyright 2016-2019 NXP
*
* This software is owned or controlled by NXP and may only be used
* strictly in accordance with the applicable license terms.  By expressly
* accepting such terms or by downloading, installing, activating and/or
* otherwise using the software, you are agreeing that you have read, and
* that you agree to comply with and are bound by, such license terms.  If
* you do not agree to be bound by the applicable license terms, then you
* may not retain, install, activate or otherwise use the software.
*
*
*******************************************************************************/

#include "isr.h"
#include "vectors_iar.h"

/*******************************************************************************
* Definitions
******************************************************************************/
typedef void (*vector_entry)(void);

#pragma location = ".intvec"
const vector_entry  __vector_table[] =
{
    VECTOR_000,           /* Initial SP           */
    VECTOR_001,           /* Initial PC           */
    VECTOR_002,
    VECTOR_003,
    VECTOR_004,
    VECTOR_005,
    VECTOR_006,
    VECTOR_007,
    VECTOR_008,
    VECTOR_009,
    VECTOR_010,
    VECTOR_011,
    VECTOR_012,
    VECTOR_013,
    VECTOR_014,
    VECTOR_015,
    VECTOR_016,
    VECTOR_017,
    VECTOR_018,
    VECTOR_019,
    VECTOR_020,
    VECTOR_021,
    VECTOR_022,
    VECTOR_023,
    VECTOR_024,
    VECTOR_025,
    VECTOR_026,
    VECTOR_027,
    VECTOR_028,
    VECTOR_029,
    VECTOR_030,
    VECTOR_031,
    VECTOR_032,
    VECTOR_033,
    VECTOR_034,
    VECTOR_035,
    VECTOR_036,
    VECTOR_037,
    VECTOR_038,
    VECTOR_039,
    VECTOR_040,
    VECTOR_041,
    VECTOR_042,
    VECTOR_043,
    VECTOR_044,
    VECTOR_045,
    VECTOR_046,
    VECTOR_047,
    VECTOR_048,
    VECTOR_049,
    VECTOR_050,
    VECTOR_051,
    VECTOR_052,
    VECTOR_053,
    VECTOR_054,
    VECTOR_055,
    VECTOR_056,
    VECTOR_057,
    VECTOR_058,
    VECTOR_059,
    VECTOR_060,
    VECTOR_061,
    VECTOR_062,
    VECTOR_063,
    VECTOR_064,
    VECTOR_065,
    VECTOR_066,
    VECTOR_067,
    VECTOR_068,
    VECTOR_069,
    VECTOR_070,
    VECTOR_071,
    VECTOR_072,
    VECTOR_073,
    VECTOR_074,
    VECTOR_075,
    VECTOR_076,
    VECTOR_077,
    VECTOR_078,
    VECTOR_079,
    VECTOR_080,
    VECTOR_081,
    VECTOR_082,
    VECTOR_083,
    VECTOR_084,
    VECTOR_085,
    VECTOR_086,
    VECTOR_087,
    VECTOR_088,
    VECTOR_089,
    VECTOR_090,
    VECTOR_091,
    VECTOR_092,
    VECTOR_093,
    VECTOR_094,
    VECTOR_095,
    VECTOR_096,
    VECTOR_097,
    VECTOR_098,
    VECTOR_099,
    VECTOR_100,
    VECTOR_101,
    VECTOR_102,
    VECTOR_103,
    VECTOR_104,
    VECTOR_105,
    VECTOR_106,
    VECTOR_107,
    VECTOR_108,
    VECTOR_109,
    VECTOR_110,
    VECTOR_111,
    VECTOR_112,
    VECTOR_113,
    VECTOR_114,
    VECTOR_115,
    VECTOR_116,
    VECTOR_117,
    VECTOR_118,
    VECTOR_119,
    VECTOR_120,
    VECTOR_121,
    VECTOR_122,
    VECTOR_123,
    VECTOR_124,
    VECTOR_125,
    VECTOR_126,
    VECTOR_127,
    VECTOR_128,
    VECTOR_129,
    VECTOR_130,
    VECTOR_131,
    VECTOR_132,
    VECTOR_133,
    VECTOR_134,
    VECTOR_135,
    VECTOR_136,
    VECTOR_137,
    VECTOR_138,
    VECTOR_139,
    VECTOR_140,
    VECTOR_141,
    VECTOR_142,
    VECTOR_143,
    VECTOR_144,
    VECTOR_145,
    VECTOR_146,
    VECTOR_147,
    VECTOR_148,
    VECTOR_149,
    VECTOR_150,
    VECTOR_151,
    VECTOR_152,
    VECTOR_153,
    VECTOR_154,
    VECTOR_155,
    VECTOR_156,
    VECTOR_157,
    VECTOR_158,
    VECTOR_159,
    VECTOR_160,
    VECTOR_161,
    VECTOR_162,
    VECTOR_163,
    VECTOR_164,
    VECTOR_165,
    VECTOR_166,
    VECTOR_167,
    VECTOR_168,
    VECTOR_169,
    VECTOR_170,
    VECTOR_171,
    VECTOR_172,
    VECTOR_173,
    VECTOR_174,
    VECTOR_175,
    VECTOR_176,
    VECTOR_177,
    VECTOR_178,
    VECTOR_179,
    VECTOR_180,
    VECTOR_181,
    VECTOR_182,
    VECTOR_183,
    VECTOR_184,
    VECTOR_185,
    VECTOR_186,
    VECTOR_187,
    VECTOR_188,
    VECTOR_189,
    VECTOR_190,
    VECTOR_191,
    VECTOR_192,
    VECTOR_193,
    VECTOR_194,
    VECTOR_195,
    VECTOR_196,
    VECTOR_197,
    VECTOR_198,
    VECTOR_199,
    VECTOR_200,
    VECTOR_201,
    VECTOR_202,
    VECTOR_203,
    VECTOR_204,
    VECTOR_205,
    VECTOR_206,
    VECTOR_207,
    VECTOR_208,
    VECTOR_209,
    VECTOR_210,
    VECTOR_211,
    VECTOR_212,
    VECTOR_213,
    VECTOR_214,
    VECTOR_215,
    VECTOR_216,
    VECTOR_217,
    VECTOR_218,
    VECTOR_219,
    VECTOR_220,
    VECTOR_221,
    VECTOR_222,
    VECTOR_223,
    VECTOR_224,
    VECTOR_225,
    VECTOR_226,
    VECTOR_227,
    VECTOR_228,
    VECTOR_229,
    VECTOR_230,
    VECTOR_231,
    VECTOR_232,
    VECTOR_233,
    VECTOR_234,
    VECTOR_235,
    VECTOR_236,
    VECTOR_237,
    VECTOR_238,
    VECTOR_239,
    VECTOR_240,
    VECTOR_241,
    VECTOR_242,
    VECTOR_243,
    VECTOR_244,
    VECTOR_245,
    VECTOR_246,
    VECTOR_247,
    VECTOR_248,
    VECTOR_249,
    VECTOR_250,
    VECTOR_251,
    VECTOR_252,
    VECTOR_253,
    VECTOR_254,
    VECTOR_255
};

/*******************************************************************************
* Code
******************************************************************************/

/*!
* default_isr(void)
*
* Default ISR definition.
*
* In:  n/a
* Out: n/a
*/
void default_isr(void)
{
#define VECTORNUM                     (*(volatile uint8_t*)(0xE000ED04))
    return;
}

/*
* NMI_isr(void)
*
* Non-maskable Interrupt (NMI)ISR definition.
*
* In:  n/a
* Out: n/a
*/
void NMI_isr(void)
{
}

/*
* Exception frame without floating-point storage
* hard fault handler in C,
* with stack frame location as input parameter
*/
void hard_fault_handler_c(unsigned int * hardfault_args)
{
}
