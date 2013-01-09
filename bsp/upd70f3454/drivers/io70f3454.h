/*-------------------------------------------------------------------------
 *      Declarations of Peripheral I/O registers, I/O register bits,
 *      Interrupt/Exeption vectors, Trap vectors and, V850E only, Callt
 *      vectors for V850E microcontroller uPD70F3454.
 *
 *      This header file can be used by both the V850 assembler, AV850,
 *      and the V850 C/C++ compiler, ICCV850.
 *
 *      This header file is generated from the device file:
 *          DF3454.800
 *          Format version 2.20, File version 1.00 
 *
 *-------------------------------------------------------------------------*/

#ifndef __IO70F3454_H__
#define __IO70F3454_H__

#if ((__TID__ >> 8) & 0x7F) != 85
#error "IO70F3454.H file for use with AV850 / ICCV850 only"
#endif

#if ((__TID__ >> 4) & 0x0F) != 1
#error "IO70F3454.H file for use with AV850 / ICCV850 option -v1 only"
#endif

#pragma language=extended
#pragma system_include

/***********************************************
 *       I/O register macros
 ***********************************************/

#include "io_macros.h"

/***********************************************
 *       Peripheral I/O register declarations
 ***********************************************/


__IO_REG16(     PDL,             0xFFFFF004,  __READ_WRITE )
__IO_REG8_BIT(  PDLL,            0xFFFFF004,  __READ_WRITE )
__IO_REG8_BIT(  PDLH,            0xFFFFF005,  __READ_WRITE )

__IO_REG16(     PMDL,            0xFFFFF024,  __READ_WRITE )
__IO_REG8_BIT(  PMDLL,           0xFFFFF024,  __READ_WRITE )
__IO_REG8_BIT(  PMDLH,           0xFFFFF025,  __READ_WRITE )

__IO_REG16(     PMCDL,           0xFFFFF044,  __READ_WRITE )
__IO_REG8_BIT(  PMCDLL,          0xFFFFF044,  __READ_WRITE )
__IO_REG8_BIT(  PMCDLH,          0xFFFFF045,  __READ_WRITE )

__IO_REG16(     BSC,             0xFFFFF066,  __READ_WRITE )

__IO_REG8(      VSWC,            0xFFFFF06E,  __READ_WRITE )

__IO_REG16(     DSA0L,           0xFFFFF080,  __READ_WRITE )
__IO_REG16(     DSA0H,           0xFFFFF082,  __READ_WRITE )
__IO_REG16(     DDA0L,           0xFFFFF084,  __READ_WRITE )
__IO_REG16(     DDA0H,           0xFFFFF086,  __READ_WRITE )
__IO_REG16(     DSA1L,           0xFFFFF088,  __READ_WRITE )
__IO_REG16(     DSA1H,           0xFFFFF08A,  __READ_WRITE )
__IO_REG16(     DDA1L,           0xFFFFF08C,  __READ_WRITE )
__IO_REG16(     DDA1H,           0xFFFFF08E,  __READ_WRITE )
__IO_REG16(     DSA2L,           0xFFFFF090,  __READ_WRITE )
__IO_REG16(     DSA2H,           0xFFFFF092,  __READ_WRITE )
__IO_REG16(     DDA2L,           0xFFFFF094,  __READ_WRITE )
__IO_REG16(     DDA2H,           0xFFFFF096,  __READ_WRITE )
__IO_REG16(     DSA3L,           0xFFFFF098,  __READ_WRITE )
__IO_REG16(     DSA3H,           0xFFFFF09A,  __READ_WRITE )
__IO_REG16(     DDA3L,           0xFFFFF09C,  __READ_WRITE )
__IO_REG16(     DDA3H,           0xFFFFF09E,  __READ_WRITE )

__IO_REG16(     DBC0,            0xFFFFF0C0,  __READ_WRITE )
__IO_REG16(     DBC1,            0xFFFFF0C2,  __READ_WRITE )
__IO_REG16(     DBC2,            0xFFFFF0C4,  __READ_WRITE )
__IO_REG16(     DBC3,            0xFFFFF0C6,  __READ_WRITE )

__IO_REG16(     DADC0,           0xFFFFF0D0,  __READ_WRITE )
__IO_REG16(     DADC1,           0xFFFFF0D2,  __READ_WRITE )
__IO_REG16(     DADC2,           0xFFFFF0D4,  __READ_WRITE )
__IO_REG16(     DADC3,           0xFFFFF0D6,  __READ_WRITE )

__IO_REG8_BIT(  DCHC0,           0xFFFFF0E0,  __READ_WRITE )
__IO_REG8_BIT(  DCHC1,           0xFFFFF0E2,  __READ_WRITE )
__IO_REG8_BIT(  DCHC2,           0xFFFFF0E4,  __READ_WRITE )
__IO_REG8_BIT(  DCHC3,           0xFFFFF0E6,  __READ_WRITE )

__IO_REG16(     IMR0,            0xFFFFF100,  __READ_WRITE )
__IO_REG8_BIT(  IMR0L,           0xFFFFF100,  __READ_WRITE )
__IO_REG8_BIT(  IMR0H,           0xFFFFF101,  __READ_WRITE )
__IO_REG16(     IMR1,            0xFFFFF102,  __READ_WRITE )
__IO_REG8_BIT(  IMR1L,           0xFFFFF102,  __READ_WRITE )
__IO_REG8_BIT(  IMR1H,           0xFFFFF103,  __READ_WRITE )
__IO_REG16(     IMR2,            0xFFFFF104,  __READ_WRITE )
__IO_REG8_BIT(  IMR2L,           0xFFFFF104,  __READ_WRITE )
__IO_REG8_BIT(  IMR2H,           0xFFFFF105,  __READ_WRITE )
__IO_REG16(     IMR3,            0xFFFFF106,  __READ_WRITE )
__IO_REG8_BIT(  IMR3L,           0xFFFFF106,  __READ_WRITE )
__IO_REG8_BIT(  IMR3H,           0xFFFFF107,  __READ_WRITE )
__IO_REG16(     IMR4,            0xFFFFF108,  __READ_WRITE )
__IO_REG8_BIT(  IMR4L,           0xFFFFF108,  __READ_WRITE )
__IO_REG8_BIT(  IMR4H,           0xFFFFF109,  __READ_WRITE )
__IO_REG16(     IMR5,            0xFFFFF10A,  __READ_WRITE )
__IO_REG8_BIT(  IMR5L,           0xFFFFF10A,  __READ_WRITE )
__IO_REG8_BIT(  IMR5H,           0xFFFFF10B,  __READ_WRITE )

__IO_REG8_BIT(  LVILIC,          0xFFFFF110,  __READ_WRITE )
__IO_REG8_BIT(  LVIHIC,          0xFFFFF112,  __READ_WRITE )
__IO_REG8_BIT(  PIC00,           0xFFFFF114,  __READ_WRITE )
__IO_REG8_BIT(  PIC01,           0xFFFFF116,  __READ_WRITE )
__IO_REG8_BIT(  PIC02,           0xFFFFF118,  __READ_WRITE )
__IO_REG8_BIT(  PIC03,           0xFFFFF11A,  __READ_WRITE )
__IO_REG8_BIT(  PIC04,           0xFFFFF11C,  __READ_WRITE )
__IO_REG8_BIT(  PIC05,           0xFFFFF11E,  __READ_WRITE )
__IO_REG8_BIT(  PIC06,           0xFFFFF120,  __READ_WRITE )
__IO_REG8_BIT(  PIC07,           0xFFFFF122,  __READ_WRITE )
__IO_REG8_BIT(  PIC08,           0xFFFFF124,  __READ_WRITE )
__IO_REG8_BIT(  PIC09,           0xFFFFF126,  __READ_WRITE )
__IO_REG8_BIT(  PIC10,           0xFFFFF128,  __READ_WRITE )
__IO_REG8_BIT(  PIC11,           0xFFFFF12A,  __READ_WRITE )
__IO_REG8_BIT(  PIC12,           0xFFFFF12C,  __READ_WRITE )
__IO_REG8_BIT(  PIC13,           0xFFFFF12E,  __READ_WRITE )
__IO_REG8_BIT(  PIC14,           0xFFFFF130,  __READ_WRITE )
__IO_REG8_BIT(  PIC15,           0xFFFFF132,  __READ_WRITE )
__IO_REG8_BIT(  PIC16,           0xFFFFF134,  __READ_WRITE )
__IO_REG8_BIT(  PIC17,           0xFFFFF136,  __READ_WRITE )
__IO_REG8_BIT(  PIC18,           0xFFFFF138,  __READ_WRITE )
__IO_REG8_BIT(  CMPIC0L,         0xFFFFF13A,  __READ_WRITE )
__IO_REG8_BIT(  CMPIC0F,         0xFFFFF13C,  __READ_WRITE )
__IO_REG8_BIT(  CMPIC1L,         0xFFFFF13E,  __READ_WRITE )
__IO_REG8_BIT(  CMPIC1F,         0xFFFFF140,  __READ_WRITE )
__IO_REG8_BIT(  TB0OVIC,         0xFFFFF142,  __READ_WRITE )
__IO_REG8_BIT(  TB0CCIC0,        0xFFFFF144,  __READ_WRITE )
__IO_REG8_BIT(  TB0CCIC1,        0xFFFFF146,  __READ_WRITE )
__IO_REG8_BIT(  TB0CCIC2,        0xFFFFF148,  __READ_WRITE )
__IO_REG8_BIT(  TB0CCIC3,        0xFFFFF14A,  __READ_WRITE )
__IO_REG8_BIT(  TB1OVIC,         0xFFFFF14C,  __READ_WRITE )
__IO_REG8_BIT(  TB1CCIC0,        0xFFFFF14E,  __READ_WRITE )
__IO_REG8_BIT(  TB1CCIC1,        0xFFFFF150,  __READ_WRITE )
__IO_REG8_BIT(  TB1CCIC2,        0xFFFFF152,  __READ_WRITE )
__IO_REG8_BIT(  TB1CCIC3,        0xFFFFF154,  __READ_WRITE )
__IO_REG8_BIT(  TT0OVIC,         0xFFFFF156,  __READ_WRITE )
__IO_REG8_BIT(  TT0CCIC0,        0xFFFFF158,  __READ_WRITE )
__IO_REG8_BIT(  TT0CCIC1,        0xFFFFF15A,  __READ_WRITE )
__IO_REG8_BIT(  TT0IECIC,        0xFFFFF15C,  __READ_WRITE )
__IO_REG8_BIT(  TT1OVIC,         0xFFFFF15E,  __READ_WRITE )
__IO_REG8_BIT(  TT1CCIC0,        0xFFFFF160,  __READ_WRITE )
__IO_REG8_BIT(  TT1CCIC1,        0xFFFFF162,  __READ_WRITE )
__IO_REG8_BIT(  TT1IECIC,        0xFFFFF164,  __READ_WRITE )
__IO_REG8_BIT(  TA0OVIC,         0xFFFFF166,  __READ_WRITE )
__IO_REG8_BIT(  TA0CCIC0,        0xFFFFF168,  __READ_WRITE )
__IO_REG8_BIT(  TA0CCIC1,        0xFFFFF16A,  __READ_WRITE )
__IO_REG8_BIT(  TA1OVIC,         0xFFFFF16C,  __READ_WRITE )
__IO_REG8_BIT(  TA1CCIC0,        0xFFFFF16E,  __READ_WRITE )
__IO_REG8_BIT(  TA1CCIC1,        0xFFFFF170,  __READ_WRITE )
__IO_REG8_BIT(  TA2OVIC,         0xFFFFF172,  __READ_WRITE )
__IO_REG8_BIT(  TA2CCIC0,        0xFFFFF174,  __READ_WRITE )
__IO_REG8_BIT(  TA2CCIC1,        0xFFFFF176,  __READ_WRITE )
__IO_REG8_BIT(  TA3OVIC,         0xFFFFF178,  __READ_WRITE )
__IO_REG8_BIT(  TA3CCIC0,        0xFFFFF17A,  __READ_WRITE )
__IO_REG8_BIT(  TA3CCIC1,        0xFFFFF17C,  __READ_WRITE )
__IO_REG8_BIT(  TA4OVIC,         0xFFFFF17E,  __READ_WRITE )
__IO_REG8_BIT(  TA4CCIC0,        0xFFFFF180,  __READ_WRITE )
__IO_REG8_BIT(  TA4CCIC1,        0xFFFFF182,  __READ_WRITE )
__IO_REG8_BIT(  DMAIC0,          0xFFFFF184,  __READ_WRITE )
__IO_REG8_BIT(  DMAIC1,          0xFFFFF186,  __READ_WRITE )
__IO_REG8_BIT(  DMAIC2,          0xFFFFF188,  __READ_WRITE )
__IO_REG8_BIT(  DMAIC3,          0xFFFFF18A,  __READ_WRITE )
__IO_REG8_BIT(  UREIC,           0xFFFFF18C,  __READ_WRITE )
__IO_REG8_BIT(  URIC,            0xFFFFF18E,  __READ_WRITE )
__IO_REG8_BIT(  UTIC,            0xFFFFF190,  __READ_WRITE )
__IO_REG8_BIT(  UIFIC,           0xFFFFF192,  __READ_WRITE )
__IO_REG8_BIT(  UTOIC,           0xFFFFF194,  __READ_WRITE )
__IO_REG8_BIT(  UA0REIC,         0xFFFFF196,  __READ_WRITE )
__IO_REG8_BIT(  UA0RIC,          0xFFFFF198,  __READ_WRITE )
__IO_REG8_BIT(  UA0TIC,          0xFFFFF19A,  __READ_WRITE )
__IO_REG8_BIT(  CB0REIC,         0xFFFFF19C,  __READ_WRITE )
__IO_REG8_BIT(  CB0RIC,          0xFFFFF19E,  __READ_WRITE )
__IO_REG8_BIT(  CB0TIC,          0xFFFFF1A0,  __READ_WRITE )
__IO_REG8_BIT(  UA1REIC,         0xFFFFF1A2,  __READ_WRITE )
__IO_REG8_BIT(  UA1RIC,          0xFFFFF1A4,  __READ_WRITE )
__IO_REG8_BIT(  UA1TIC,          0xFFFFF1A6,  __READ_WRITE )
__IO_REG8_BIT(  CB1REIC,         0xFFFFF1A8,  __READ_WRITE )
__IO_REG8_BIT(  CB1RIC,          0xFFFFF1AA,  __READ_WRITE )
__IO_REG8_BIT(  CB1TIC,          0xFFFFF1AC,  __READ_WRITE )
__IO_REG8_BIT(  UA2REIC,         0xFFFFF1AE,  __READ_WRITE )
__IO_REG8_BIT(  UA2RIC,          0xFFFFF1B0,  __READ_WRITE )
__IO_REG8_BIT(  UA2TIC,          0xFFFFF1B2,  __READ_WRITE )
__IO_REG8_BIT(  CB2REIC,         0xFFFFF1B4,  __READ_WRITE )
__IO_REG8_BIT(  CB2RIC,          0xFFFFF1B6,  __READ_WRITE )
__IO_REG8_BIT(  CB2TIC,          0xFFFFF1B8,  __READ_WRITE )
__IO_REG8_BIT(  IICIC,           0xFFFFF1BA,  __READ_WRITE )
__IO_REG8_BIT(  AD0IC,           0xFFFFF1BC,  __READ_WRITE )
__IO_REG8_BIT(  AD1IC,           0xFFFFF1BE,  __READ_WRITE )
__IO_REG8_BIT(  AD2IC,           0xFFFFF1C0,  __READ_WRITE )
__IO_REG8_BIT(  TM0EQIC0,        0xFFFFF1C2,  __READ_WRITE )
__IO_REG8_BIT(  TM1EQIC0,        0xFFFFF1C4,  __READ_WRITE )
__IO_REG8_BIT(  TM2EQIC0,        0xFFFFF1C6,  __READ_WRITE )
__IO_REG8_BIT(  TM3EQIC0,        0xFFFFF1C8,  __READ_WRITE )
__IO_REG8_BIT(  ADT0IC,          0xFFFFF1CA,  __READ_WRITE )
__IO_REG8_BIT(  ADT1IC,          0xFFFFF1CC,  __READ_WRITE )

__IO_REG8_BIT(  ISPR,            0xFFFFF1FA,  __READ       )
__IO_REG8(      PRCMD,           0xFFFFF1FC,  __WRITE      )
__IO_REG8_BIT(  PSC,             0xFFFFF1FE,  __READ_WRITE )
__IO_REG16(     AD0CR0,          0xFFFFF200,  __READ       )
__IO_REG8(      AD0CR0H,         0xFFFFF201,  __READ       )
__IO_REG16(     AD0CR1,          0xFFFFF202,  __READ       )
__IO_REG8(      AD0CR1H,         0xFFFFF203,  __READ       )
__IO_REG16(     AD0CR2,          0xFFFFF204,  __READ       )
__IO_REG8(      AD0CR2H,         0xFFFFF205,  __READ       )
__IO_REG16(     AD0CR3,          0xFFFFF206,  __READ       )
__IO_REG8(      AD0CR3H,         0xFFFFF207,  __READ       )
__IO_REG16(     AD0CR4,          0xFFFFF208,  __READ       )
__IO_REG8(      AD0CR4H,         0xFFFFF209,  __READ       )
__IO_REG16(     AD0CR5,          0xFFFFF20A,  __READ       )
__IO_REG8(      AD0CR5H,         0xFFFFF20B,  __READ       )
__IO_REG16(     AD0CR6,          0xFFFFF20C,  __READ       )
__IO_REG8(      AD0CR6H,         0xFFFFF20D,  __READ       )
__IO_REG16(     AD0CR7,          0xFFFFF20E,  __READ       )
__IO_REG8(      AD0CR7H,         0xFFFFF20F,  __READ       )
__IO_REG16(     AD0CR8,          0xFFFFF210,  __READ       )
__IO_REG8(      AD0CR8H,         0xFFFFF211,  __READ       )
__IO_REG16(     AD0CR9,          0xFFFFF212,  __READ       )
__IO_REG8(      AD0CR9H,         0xFFFFF213,  __READ       )
__IO_REG16(     AD0CR10,         0xFFFFF214,  __READ       )
__IO_REG8(      AD0CR10H,        0xFFFFF215,  __READ       )
__IO_REG16(     AD0CR11,         0xFFFFF216,  __READ       )
__IO_REG8(      AD0CR11H,        0xFFFFF217,  __READ       )
__IO_REG16(     AD0CR12,         0xFFFFF218,  __READ       )
__IO_REG8(      AD0CR12H,        0xFFFFF219,  __READ       )
__IO_REG16(     AD0CR13,         0xFFFFF21A,  __READ       )
__IO_REG8(      AD0CR13H,        0xFFFFF21B,  __READ       )
__IO_REG16(     AD0CR14,         0xFFFFF21C,  __READ       )
__IO_REG8(      AD0CR14H,        0xFFFFF21D,  __READ       )
__IO_REG16(     AD0CR15,         0xFFFFF21E,  __READ       )
__IO_REG8(      AD0CR15H,        0xFFFFF21F,  __READ       )
__IO_REG16(     AD0SCM,          0xFFFFF220,  __READ_WRITE )
__IO_REG8_BIT(  AD0SCML,         0xFFFFF220,  __READ_WRITE )
__IO_REG8_BIT(  AD0SCMH,         0xFFFFF221,  __READ_WRITE )
__IO_REG8_BIT(  AD0CTC,          0xFFFFF222,  __READ_WRITE )
__IO_REG16(     AD0CHEN,         0xFFFFF224,  __READ_WRITE )
__IO_REG8_BIT(  AD0CHENL,        0xFFFFF224,  __READ_WRITE )
__IO_REG8_BIT(  AD0CHENH,        0xFFFFF225,  __READ_WRITE )

__IO_REG8_BIT(  AD0CTL0,         0xFFFFF230,  __READ_WRITE )
__IO_REG8_BIT(  AD0TSEL,         0xFFFFF231,  __READ_WRITE )
__IO_REG8_BIT(  AD0CH1,          0xFFFFF232,  __READ_WRITE )
__IO_REG8_BIT(  AD0CH2,          0xFFFFF233,  __READ_WRITE )

__IO_REG16(     AD0ECR0,         0xFFFFF240,  __READ       )
__IO_REG8(      AD0ECR0H,        0xFFFFF241,  __READ       )
__IO_REG16(     AD0ECR1,         0xFFFFF242,  __READ       )
__IO_REG8(      AD0ECR1H,        0xFFFFF243,  __READ       )
__IO_REG16(     AD0ECR2,         0xFFFFF244,  __READ       )
__IO_REG8(      AD0ECR2H,        0xFFFFF245,  __READ       )
__IO_REG16(     AD0ECR3,         0xFFFFF246,  __READ       )
__IO_REG8(      AD0ECR3H,        0xFFFFF247,  __READ       )
__IO_REG16(     AD0ECR4,         0xFFFFF248,  __READ       )
__IO_REG8(      AD0ECR4H,        0xFFFFF249,  __READ       )

__IO_REG8(      AD0FLG,          0xFFFFF254,  __READ       )
__IO_REG8(      AD0FLGB,         0xFFFFF255,  __READ       )

__IO_REG8(      OP0CTL0,         0xFFFFF260,  __READ_WRITE )
__IO_REG8(      CMP0CTL0,        0xFFFFF261,  __READ_WRITE )
__IO_REG8(      CMP0CTL1,        0xFFFFF262,  __READ       )
__IO_REG8(      CMP0CTL2,        0xFFFFF263,  __READ_WRITE )
__IO_REG8(      CMP0CTL3,        0xFFFFF264,  __READ_WRITE )

__IO_REG8(      AD0OCKS,         0xFFFFF270,  __READ_WRITE )

__IO_REG8(      AD1OCKS,         0xFFFFF274,  __READ_WRITE )

__IO_REG8(      CMPNFC0L,        0xFFFFF278,  __READ_WRITE )
__IO_REG8(      CMPNFC0F,        0xFFFFF27A,  __READ_WRITE )
__IO_REG8(      CMPNFC1L,        0xFFFFF27C,  __READ_WRITE )
__IO_REG8(      CMPNFC1F,        0xFFFFF27E,  __READ_WRITE )
__IO_REG16(     AD1CR0,          0xFFFFF280,  __READ       )
__IO_REG8(      AD1CR0H,         0xFFFFF281,  __READ       )
__IO_REG16(     AD1CR1,          0xFFFFF282,  __READ       )
__IO_REG8(      AD1CR1H,         0xFFFFF283,  __READ       )
__IO_REG16(     AD1CR2,          0xFFFFF284,  __READ       )
__IO_REG8(      AD1CR2H,         0xFFFFF285,  __READ       )
__IO_REG16(     AD1CR3,          0xFFFFF286,  __READ       )
__IO_REG8(      AD1CR3H,         0xFFFFF287,  __READ       )
__IO_REG16(     AD1CR4,          0xFFFFF288,  __READ       )
__IO_REG8(      AD1CR4H,         0xFFFFF289,  __READ       )
__IO_REG16(     AD1CR5,          0xFFFFF28A,  __READ       )
__IO_REG8(      AD1CR5H,         0xFFFFF28B,  __READ       )
__IO_REG16(     AD1CR6,          0xFFFFF28C,  __READ       )
__IO_REG8(      AD1CR6H,         0xFFFFF28D,  __READ       )
__IO_REG16(     AD1CR7,          0xFFFFF28E,  __READ       )
__IO_REG8(      AD1CR7H,         0xFFFFF28F,  __READ       )
__IO_REG16(     AD1CR8,          0xFFFFF290,  __READ       )
__IO_REG8(      AD1CR8H,         0xFFFFF291,  __READ       )
__IO_REG16(     AD1CR9,          0xFFFFF292,  __READ       )
__IO_REG8(      AD1CR9H,         0xFFFFF293,  __READ       )
__IO_REG16(     AD1CR10,         0xFFFFF294,  __READ       )
__IO_REG8(      AD1CR10H,        0xFFFFF295,  __READ       )
__IO_REG16(     AD1CR11,         0xFFFFF296,  __READ       )
__IO_REG8(      AD1CR11H,        0xFFFFF297,  __READ       )
__IO_REG16(     AD1CR12,         0xFFFFF298,  __READ       )
__IO_REG8(      AD1CR12H,        0xFFFFF299,  __READ       )
__IO_REG16(     AD1CR13,         0xFFFFF29A,  __READ       )
__IO_REG8(      AD1CR13H,        0xFFFFF29B,  __READ       )
__IO_REG16(     AD1CR14,         0xFFFFF29C,  __READ       )
__IO_REG8(      AD1CR14H,        0xFFFFF29D,  __READ       )
__IO_REG16(     AD1CR15,         0xFFFFF29E,  __READ       )
__IO_REG8(      AD1CR15H,        0xFFFFF29F,  __READ       )
__IO_REG16(     AD1SCM,          0xFFFFF2A0,  __READ_WRITE )
__IO_REG8_BIT(  AD1SCML,         0xFFFFF2A0,  __READ_WRITE )
__IO_REG8_BIT(  AD1SCMH,         0xFFFFF2A1,  __READ_WRITE )
__IO_REG8_BIT(  AD1CTC,          0xFFFFF2A2,  __READ_WRITE )
__IO_REG16(     AD1CHEN,         0xFFFFF2A4,  __READ_WRITE )
__IO_REG8_BIT(  AD1CHENL,        0xFFFFF2A4,  __READ_WRITE )
__IO_REG8_BIT(  AD1CHENH,        0xFFFFF2A5,  __READ_WRITE )

__IO_REG8_BIT(  AD1CTL0,         0xFFFFF2B0,  __READ_WRITE )
__IO_REG8_BIT(  AD1TSEL,         0xFFFFF2B1,  __READ_WRITE )
__IO_REG8_BIT(  AD1CH1,          0xFFFFF2B2,  __READ_WRITE )
__IO_REG8_BIT(  AD1CH2,          0xFFFFF2B3,  __READ_WRITE )

__IO_REG16(     AD1ECR0,         0xFFFFF2C0,  __READ       )
__IO_REG8(      AD1ECR0H,        0xFFFFF2C1,  __READ       )
__IO_REG16(     AD1ECR1,         0xFFFFF2C2,  __READ       )
__IO_REG8(      AD1ECR1H,        0xFFFFF2C3,  __READ       )
__IO_REG16(     AD1ECR2,         0xFFFFF2C4,  __READ       )
__IO_REG8(      AD1ECR2H,        0xFFFFF2C5,  __READ       )
__IO_REG16(     AD1ECR3,         0xFFFFF2C6,  __READ       )
__IO_REG8(      AD1ECR3H,        0xFFFFF2C7,  __READ       )
__IO_REG16(     AD1ECR4,         0xFFFFF2C8,  __READ       )

__IO_REG8(      AD1ECB4H,        0xFFFFF2D3,  __READ       )
__IO_REG8(      AD1FLG,          0xFFFFF2D4,  __READ       )
__IO_REG8(      AD1FLGB,         0xFFFFF2D5,  __READ       )

__IO_REG8(      OP1CTL0,         0xFFFFF2E0,  __READ_WRITE )
__IO_REG8(      CMP1CTL0,        0xFFFFF2E1,  __READ_WRITE )
__IO_REG8(      CMP1CTL1,        0xFFFFF2E2,  __READ       )
__IO_REG8(      CMP1CTL2,        0xFFFFF2E3,  __READ_WRITE )
__IO_REG8(      CMP1CTL3,        0xFFFFF2E4,  __READ_WRITE )

__IO_REG8_BIT(  ADTF,            0xFFFFF2F0,  __READ_WRITE )
__IO_REG8_BIT(  ADTR,            0xFFFFF2F2,  __READ_WRITE )
__IO_REG8_BIT(  CMPOF,           0xFFFFF2F4,  __READ_WRITE )
__IO_REG8_BIT(  CMPOR,           0xFFFFF2F6,  __READ_WRITE )
__IO_REG8(      ADLTS1,          0xFFFFF2F8,  __READ_WRITE )
__IO_REG8(      ADLTS2,          0xFFFFF2FA,  __READ_WRITE )

__IO_REG8(      INTNFC14,        0xFFFFF310,  __READ_WRITE )
__IO_REG8(      INTNFC15,        0xFFFFF312,  __READ_WRITE )
__IO_REG8(      INTNFC16,        0xFFFFF314,  __READ_WRITE )

__IO_REG8_BIT(  P0,              0xFFFFF400,  __READ_WRITE )
__IO_REG8_BIT(  P1,              0xFFFFF402,  __READ_WRITE )
__IO_REG8_BIT(  P2,              0xFFFFF404,  __READ_WRITE )
__IO_REG8_BIT(  P3,              0xFFFFF406,  __READ_WRITE )
__IO_REG8_BIT(  P4,              0xFFFFF408,  __READ_WRITE )

__IO_REG8_BIT(  PM0,             0xFFFFF420,  __READ_WRITE )
__IO_REG8_BIT(  PM1,             0xFFFFF422,  __READ_WRITE )
__IO_REG8_BIT(  PM2,             0xFFFFF424,  __READ_WRITE )
__IO_REG8_BIT(  PM3,             0xFFFFF426,  __READ_WRITE )
__IO_REG8_BIT(  PM4,             0xFFFFF428,  __READ_WRITE )

__IO_REG8_BIT(  PMC0,            0xFFFFF440,  __READ_WRITE )
__IO_REG8_BIT(  PMC1,            0xFFFFF442,  __READ_WRITE )
__IO_REG8_BIT(  PMC2,            0xFFFFF444,  __READ_WRITE )
__IO_REG8_BIT(  PMC3,            0xFFFFF446,  __READ_WRITE )
__IO_REG8_BIT(  PMC4,            0xFFFFF448,  __READ_WRITE )

__IO_REG8_BIT(  PFC0,            0xFFFFF460,  __READ_WRITE )
__IO_REG8_BIT(  PFC1,            0xFFFFF462,  __READ_WRITE )
__IO_REG8_BIT(  PFC2,            0xFFFFF464,  __READ_WRITE )
__IO_REG8_BIT(  PFC3,            0xFFFFF466,  __READ_WRITE )
__IO_REG8_BIT(  PFC4,            0xFFFFF468,  __READ_WRITE )

__IO_REG16(     BCT0,            0xFFFFF480,  __READ_WRITE )

__IO_REG16(     DWC0,            0xFFFFF484,  __READ_WRITE )

__IO_REG16(     AWC,             0xFFFFF488,  __READ_WRITE )
__IO_REG16(     BCC,             0xFFFFF48A,  __READ_WRITE )

__IO_REG8(      DVC,             0xFFFFF48E,  __READ_WRITE )

__IO_REG8_BIT(  TM0CTL0,         0xFFFFF540,  __READ_WRITE )

__IO_REG16(     TM0CMP0,         0xFFFFF544,  __READ_WRITE )

__IO_REG8_BIT(  TM1CTL0,         0xFFFFF550,  __READ_WRITE )

__IO_REG16(     TM1CMP0,         0xFFFFF554,  __READ_WRITE )

__IO_REG8_BIT(  TM2CTL0,         0xFFFFF560,  __READ_WRITE )

__IO_REG16(     TM2CMP0,         0xFFFFF564,  __READ_WRITE )

__IO_REG8_BIT(  TM3CTL0,         0xFFFFF570,  __READ_WRITE )

__IO_REG16(     TM3CMP0,         0xFFFFF574,  __READ_WRITE )

__IO_REG8_BIT(  TT0CTL0,         0xFFFFF580,  __READ_WRITE )
__IO_REG8_BIT(  TT0CTL1,         0xFFFFF581,  __READ_WRITE )
__IO_REG8_BIT(  TT0CTL2,         0xFFFFF582,  __READ_WRITE )
__IO_REG8_BIT(  TT0IOC0,         0xFFFFF583,  __READ_WRITE )
__IO_REG8_BIT(  TT0IOC1,         0xFFFFF584,  __READ_WRITE )
__IO_REG8_BIT(  TT0IOC2,         0xFFFFF585,  __READ_WRITE )
__IO_REG8_BIT(  TT0IOC3,         0xFFFFF586,  __READ_WRITE )
__IO_REG8_BIT(  TT0OPT0,         0xFFFFF587,  __READ_WRITE )
__IO_REG8_BIT(  TT0OPT1,         0xFFFFF588,  __READ_WRITE )
__IO_REG16(     TT0CCR0,         0xFFFFF58A,  __READ_WRITE )
__IO_REG16(     TT0CCR1,         0xFFFFF58C,  __READ_WRITE )
__IO_REG16(     TT0CNT,          0xFFFFF58E,  __READ       )
__IO_REG16(     TT0TCW,          0xFFFFF590,  __READ_WRITE )

__IO_REG8(      TTNFC0,          0xFFFFF5A0,  __READ_WRITE )
__IO_REG8(      TTNFC1,          0xFFFFF5A2,  __READ_WRITE )
__IO_REG8(      TTISL0,          0xFFFFF5A4,  __READ_WRITE )
__IO_REG8(      TTISL1,          0xFFFFF5A6,  __READ_WRITE )

__IO_REG8_BIT(  TT1CTL0,         0xFFFFF5C0,  __READ_WRITE )
__IO_REG8_BIT(  TT1CTL1,         0xFFFFF5C1,  __READ_WRITE )
__IO_REG8_BIT(  TT1CTL2,         0xFFFFF5C2,  __READ_WRITE )
__IO_REG8_BIT(  TT1IOC0,         0xFFFFF5C3,  __READ_WRITE )
__IO_REG8_BIT(  TT1IOC1,         0xFFFFF5C4,  __READ_WRITE )
__IO_REG8_BIT(  TT1IOC2,         0xFFFFF5C5,  __READ_WRITE )
__IO_REG8_BIT(  TT1IOC3,         0xFFFFF5C6,  __READ_WRITE )
__IO_REG8_BIT(  TT1OPT0,         0xFFFFF5C7,  __READ_WRITE )
__IO_REG8_BIT(  TT1OPT1,         0xFFFFF5C8,  __READ_WRITE )
__IO_REG16(     TT1CCR0,         0xFFFFF5CA,  __READ_WRITE )
__IO_REG16(     TT1CCR1,         0xFFFFF5CC,  __READ_WRITE )
__IO_REG16(     TT1CNT,          0xFFFFF5CE,  __READ       )
__IO_REG16(     TT1TCW,          0xFFFFF5D0,  __READ_WRITE )

__IO_REG8_BIT(  TAB0CTL0,        0xFFFFF5E0,  __READ_WRITE )
__IO_REG8_BIT(  TAB0CTL1,        0xFFFFF5E1,  __READ_WRITE )
__IO_REG8_BIT(  TAB0IOC0,        0xFFFFF5E2,  __READ_WRITE )
__IO_REG8_BIT(  TAB0IOC1,        0xFFFFF5E3,  __READ_WRITE )
__IO_REG8_BIT(  TAB0IOC2,        0xFFFFF5E4,  __READ_WRITE )
__IO_REG8_BIT(  TAB0OPT0,        0xFFFFF5E5,  __READ_WRITE )
__IO_REG16(     TAB0CCR0,        0xFFFFF5E6,  __READ_WRITE )
__IO_REG16(     TAB0CCR1,        0xFFFFF5E8,  __READ_WRITE )
__IO_REG16(     TAB0CCR2,        0xFFFFF5EA,  __READ_WRITE )
__IO_REG16(     TAB0CCR3,        0xFFFFF5EC,  __READ_WRITE )
__IO_REG16(     TAB0CNT,         0xFFFFF5EE,  __READ       )

__IO_REG8_BIT(  TAB0OPT1,        0xFFFFF600,  __READ_WRITE )
__IO_REG8_BIT(  TAB0OPT2,        0xFFFFF601,  __READ_WRITE )
__IO_REG8_BIT(  TAB0IOC3,        0xFFFFF602,  __READ_WRITE )
__IO_REG8_BIT(  TAB0OPT3,        0xFFFFF603,  __READ_WRITE )
__IO_REG16(     TAB0DTC,         0xFFFFF604,  __READ_WRITE )

__IO_REG8_BIT(  HZA0CTL0,        0xFFFFF610,  __READ_WRITE )
__IO_REG8_BIT(  HZA0CTL1,        0xFFFFF611,  __READ_WRITE )

__IO_REG8_BIT(  HZA1CTL0,        0xFFFFF618,  __READ_WRITE )
__IO_REG8_BIT(  HZA1CTL1,        0xFFFFF619,  __READ_WRITE )

__IO_REG8_BIT(  TAB1CTL0,        0xFFFFF620,  __READ_WRITE )
__IO_REG8_BIT(  TAB1CTL1,        0xFFFFF621,  __READ_WRITE )
__IO_REG8_BIT(  TAB1IOC0,        0xFFFFF622,  __READ_WRITE )
__IO_REG8_BIT(  TAB1IOC1,        0xFFFFF623,  __READ_WRITE )
__IO_REG8_BIT(  TAB1IOC2,        0xFFFFF624,  __READ_WRITE )
__IO_REG8_BIT(  TAB1OPT0,        0xFFFFF625,  __READ_WRITE )
__IO_REG16(     TAB1CCR0,        0xFFFFF626,  __READ_WRITE )
__IO_REG16(     TAB1CCR1,        0xFFFFF628,  __READ_WRITE )
__IO_REG16(     TAB1CCR2,        0xFFFFF62A,  __READ_WRITE )
__IO_REG16(     TAB1CCR3,        0xFFFFF62C,  __READ_WRITE )
__IO_REG16(     TAB1CNT,         0xFFFFF62E,  __READ       )

__IO_REG8_BIT(  TAB1OPT1,        0xFFFFF640,  __READ_WRITE )
__IO_REG8_BIT(  TAB1OPT2,        0xFFFFF641,  __READ_WRITE )
__IO_REG8_BIT(  TAB1IOC3,        0xFFFFF642,  __READ_WRITE )
__IO_REG8_BIT(  TAB1OPT3,        0xFFFFF643,  __READ_WRITE )
__IO_REG16(     TAB1DTC,         0xFFFFF644,  __READ_WRITE )

__IO_REG8_BIT(  HZA2CTL0,        0xFFFFF650,  __READ_WRITE )
__IO_REG8_BIT(  HZA2CTL1,        0xFFFFF651,  __READ_WRITE )

__IO_REG8_BIT(  HZA3CTL0,        0xFFFFF658,  __READ_WRITE )
__IO_REG8_BIT(  HZA3CTL1,        0xFFFFF659,  __READ_WRITE )

__IO_REG8_BIT(  TAA0CTL0,        0xFFFFF660,  __READ_WRITE )
__IO_REG8_BIT(  TAA0CTL1,        0xFFFFF661,  __READ_WRITE )

__IO_REG8_BIT(  TAA0OPT0,        0xFFFFF665,  __READ_WRITE )
__IO_REG16(     TAA0CCR0,        0xFFFFF666,  __READ_WRITE )
__IO_REG16(     TAA0CCR1,        0xFFFFF668,  __READ_WRITE )
__IO_REG16(     TAA0CNT,         0xFFFFF66A,  __READ       )

__IO_REG8_BIT(  TAA1CTL0,        0xFFFFF680,  __READ_WRITE )
__IO_REG8_BIT(  TAA1CTL1,        0xFFFFF681,  __READ_WRITE )

__IO_REG8_BIT(  TAA1OPT0,        0xFFFFF685,  __READ_WRITE )
__IO_REG16(     TAA1CCR0,        0xFFFFF686,  __READ_WRITE )
__IO_REG16(     TAA1CCR1,        0xFFFFF688,  __READ_WRITE )
__IO_REG16(     TAA1CNT,         0xFFFFF68A,  __READ       )

__IO_REG8_BIT(  TAA2CTL0,        0xFFFFF6A0,  __READ_WRITE )
__IO_REG8_BIT(  TAA2CTL1,        0xFFFFF6A1,  __READ_WRITE )
__IO_REG8_BIT(  TAA2IOC0,        0xFFFFF6A2,  __READ_WRITE )
__IO_REG8_BIT(  TAA2IOC1,        0xFFFFF6A3,  __READ_WRITE )
__IO_REG8_BIT(  TAA2IOC2,        0xFFFFF6A4,  __READ_WRITE )
__IO_REG8_BIT(  TAA2OPT0,        0xFFFFF6A5,  __READ_WRITE )
__IO_REG16(     TAA2CCR0,        0xFFFFF6A6,  __READ_WRITE )
__IO_REG16(     TAA2CCR1,        0xFFFFF6A8,  __READ_WRITE )
__IO_REG16(     TAA2CNT,         0xFFFFF6AA,  __READ       )

__IO_REG8(      OSTS,            0xFFFFF6C0,  __READ_WRITE )

__IO_REG8_BIT(  WDTM,            0xFFFFF6D0,  __READ_WRITE )
__IO_REG8(      WDTE,            0xFFFFF6D1,  __READ_WRITE )

__IO_REG8_BIT(  PFCE0,           0xFFFFF700,  __READ_WRITE )
__IO_REG8_BIT(  PFCE1,           0xFFFFF702,  __READ_WRITE )
__IO_REG8_BIT(  PFCE2,           0xFFFFF704,  __READ_WRITE )
__IO_REG8_BIT(  PFCE3,           0xFFFFF706,  __READ_WRITE )
__IO_REG8_BIT(  PFCE4,           0xFFFFF708,  __READ_WRITE )

__IO_REG8_BIT(  SYS,             0xFFFFF802,  __READ_WRITE )

__IO_REG8_BIT(  DTFR0,           0xFFFFF810,  __READ_WRITE )
__IO_REG8_BIT(  DTFR1,           0xFFFFF812,  __READ_WRITE )
__IO_REG8_BIT(  DTFR2,           0xFFFFF814,  __READ_WRITE )
__IO_REG8_BIT(  DTFR3,           0xFFFFF816,  __READ_WRITE )

__IO_REG8_BIT(  PSMR,            0xFFFFF820,  __READ_WRITE )

__IO_REG8_BIT(  PCC,             0xFFFFF828,  __READ_WRITE )

__IO_REG8_BIT(  PLLCTL,          0xFFFFF82C,  __READ_WRITE )

__IO_REG8_BIT(  CLM,             0xFFFFF870,  __READ_WRITE )

__IO_REG8_BIT(  RESF,            0xFFFFF888,  __READ_WRITE )

__IO_REG8_BIT(  LVIM,            0xFFFFF890,  __READ_WRITE )
__IO_REG8(      LVIS,            0xFFFFF891,  __READ_WRITE )

__IO_REG8_BIT(  UA0CTL0,         0xFFFFFA00,  __READ_WRITE )
__IO_REG8(      UA0CTL1,         0xFFFFFA01,  __READ_WRITE )
__IO_REG8(      UA0CTL2,         0xFFFFFA02,  __READ_WRITE )
__IO_REG8_BIT(  UA0OPT0,         0xFFFFFA03,  __READ_WRITE )
__IO_REG8_BIT(  UA0STR,          0xFFFFFA04,  __READ_WRITE )
__IO_REG8(      UA0RX,           0xFFFFFA06,  __READ       )
__IO_REG8(      UA0TX,           0xFFFFFA07,  __READ_WRITE )

__IO_REG8_BIT(  UA1CTL0,         0xFFFFFA10,  __READ_WRITE )
__IO_REG8(      UA1CTL1,         0xFFFFFA11,  __READ_WRITE )
__IO_REG8(      UA1CTL2,         0xFFFFFA12,  __READ_WRITE )
__IO_REG8_BIT(  UA1OPT0,         0xFFFFFA13,  __READ_WRITE )
__IO_REG8_BIT(  UA1STR,          0xFFFFFA14,  __READ_WRITE )
__IO_REG8(      UA1RX,           0xFFFFFA16,  __READ       )
__IO_REG8(      UA1TX,           0xFFFFFA17,  __READ_WRITE )

__IO_REG8_BIT(  UA2CTL0,         0xFFFFFA20,  __READ_WRITE )
__IO_REG8(      UA2CTL1,         0xFFFFFA21,  __READ_WRITE )
__IO_REG8(      UA2CTL2,         0xFFFFFA22,  __READ_WRITE )
__IO_REG8_BIT(  UA2OPT0,         0xFFFFFA23,  __READ_WRITE )
__IO_REG8_BIT(  UA2STR,          0xFFFFFA24,  __READ_WRITE )
__IO_REG8(      UA2RX,           0xFFFFFA26,  __READ       )
__IO_REG8(      UA2TX,           0xFFFFFA27,  __READ_WRITE )

__IO_REG8_BIT(  UBCTL0,          0xFFFFFA40,  __READ_WRITE )
__IO_REG16(     UBCTL2,          0xFFFFFA42,  __READ_WRITE )
__IO_REG8_BIT(  UBSTR,           0xFFFFFA44,  __READ_WRITE )
__IO_REG16(     UBRXAP,          0xFFFFFA46,  __READ       )
__IO_REG8(      UBRX,            0xFFFFFA46,  __READ       )
__IO_REG8(      UBTX,            0xFFFFFA48,  __WRITE      )
__IO_REG8_BIT(  UBFIC0,          0xFFFFFA4A,  __READ_WRITE )
__IO_REG8_BIT(  UBFIC1,          0xFFFFFA4B,  __READ_WRITE )
__IO_REG16(     UBFIC2,          0xFFFFFA4C,  __READ_WRITE )
__IO_REG8(      UBFIC2L,         0xFFFFFA4C,  __READ_WRITE )
__IO_REG8(      UBFIC2H,         0xFFFFFA4D,  __READ_WRITE )
__IO_REG8(      UBFIS0,          0xFFFFFA4E,  __READ       )
__IO_REG8(      UBFIS1,          0xFFFFFA4F,  __READ       )

__IO_REG8_BIT(  TAA3CTL0,        0xFFFFFB00,  __READ_WRITE )
__IO_REG8_BIT(  TAA3CTL1,        0xFFFFFB01,  __READ_WRITE )
__IO_REG8_BIT(  TAA3IOC0,        0xFFFFFB02,  __READ_WRITE )
__IO_REG8_BIT(  TAA3IOC1,        0xFFFFFB03,  __READ_WRITE )
__IO_REG8_BIT(  TAA3IOC2,        0xFFFFFB04,  __READ_WRITE )
__IO_REG8_BIT(  TAA3OPT0,        0xFFFFFB05,  __READ_WRITE )
__IO_REG16(     TAA3CCR0,        0xFFFFFB06,  __READ_WRITE )
__IO_REG16(     TAA3CCR1,        0xFFFFFB08,  __READ_WRITE )
__IO_REG16(     TAA3CNT,         0xFFFFFB0A,  __READ       )

__IO_REG8_BIT(  TAA4CTL0,        0xFFFFFB20,  __READ_WRITE )
__IO_REG8_BIT(  TAA4CTL1,        0xFFFFFB21,  __READ_WRITE )
__IO_REG8_BIT(  TAA4IOC0,        0xFFFFFB22,  __READ_WRITE )
__IO_REG8_BIT(  TAA4IOC1,        0xFFFFFB23,  __READ_WRITE )
__IO_REG8_BIT(  TAA4IOC2,        0xFFFFFB24,  __READ_WRITE )
__IO_REG8_BIT(  TAA4OPT0,        0xFFFFFB25,  __READ_WRITE )
__IO_REG16(     TAA4CCR0,        0xFFFFFB26,  __READ_WRITE )
__IO_REG16(     TAA4CCR1,        0xFFFFFB28,  __READ_WRITE )
__IO_REG16(     TAA4CNT,         0xFFFFFB2A,  __READ       )

__IO_REG8(      TANFC2,          0xFFFFFB40,  __READ_WRITE )
__IO_REG8(      TANFC3,          0xFFFFFB42,  __READ_WRITE )
__IO_REG8(      TANFC4,          0xFFFFFB44,  __READ_WRITE )

__IO_REG8_BIT(  AD2M0,           0xFFFFFB80,  __READ_WRITE )
__IO_REG8_BIT(  AD2M1,           0xFFFFFB81,  __READ_WRITE )
__IO_REG8_BIT(  AD2S,            0xFFFFFB82,  __READ_WRITE )

__IO_REG16(     AD2CR0,          0xFFFFFB90,  __READ       )
__IO_REG8(      AD2CR0H,         0xFFFFFB91,  __READ       )
__IO_REG16(     AD2CR1,          0xFFFFFB92,  __READ       )
__IO_REG8(      AD2CR1H,         0xFFFFFB93,  __READ       )
__IO_REG16(     AD2CR2,          0xFFFFFB94,  __READ       )
__IO_REG8(      AD2CR2H,         0xFFFFFB95,  __READ       )
__IO_REG16(     AD2CR3,          0xFFFFFB96,  __READ       )
__IO_REG8(      AD2CR3H,         0xFFFFFB97,  __READ       )
__IO_REG16(     AD2CR4,          0xFFFFFB98,  __READ       )
__IO_REG8(      AD2CR4H,         0xFFFFFB99,  __READ       )
__IO_REG16(     AD2CR5,          0xFFFFFB9A,  __READ       )
__IO_REG8(      AD2CR5H,         0xFFFFFB9B,  __READ       )
__IO_REG16(     AD2CR6,          0xFFFFFB9C,  __READ       )
__IO_REG8(      AD2CR6H,         0xFFFFFB9D,  __READ       )
__IO_REG16(     AD2CR7,          0xFFFFFB9E,  __READ       )
__IO_REG8(      AD2CR7H,         0xFFFFFB9F,  __READ       )

__IO_REG8_BIT(  P7,              0xFFFFFBB0,  __READ_WRITE )

__IO_REG8_BIT(  PMC7,            0xFFFFFBB8,  __READ_WRITE )

__IO_REG8_BIT(  INTF0,           0xFFFFFC00,  __READ_WRITE )
__IO_REG8_BIT(  INTF1,           0xFFFFFC02,  __READ_WRITE )
__IO_REG8_BIT(  INTF2,           0xFFFFFC04,  __READ_WRITE )

__IO_REG8_BIT(  INTR0,           0xFFFFFC20,  __READ_WRITE )
__IO_REG8_BIT(  INTR1,           0xFFFFFC22,  __READ_WRITE )
__IO_REG8_BIT(  INTR2,           0xFFFFFC24,  __READ_WRITE )

__IO_REG8_BIT(  PU0,             0xFFFFFC40,  __READ_WRITE )
__IO_REG8_BIT(  PU1,             0xFFFFFC42,  __READ_WRITE )
__IO_REG8_BIT(  PU2,             0xFFFFFC44,  __READ_WRITE )
__IO_REG8_BIT(  PU3,             0xFFFFFC46,  __READ_WRITE )
__IO_REG8_BIT(  PU4,             0xFFFFFC48,  __READ_WRITE )

__IO_REG8_BIT(  PF3,             0xFFFFFC66,  __READ_WRITE )

__IO_REG8_BIT(  CB0CTL0,         0xFFFFFD00,  __READ_WRITE )
__IO_REG8_BIT(  CB0CTL1,         0xFFFFFD01,  __READ_WRITE )
__IO_REG8(      CB0CTL2,         0xFFFFFD02,  __READ_WRITE )
__IO_REG8_BIT(  CB0STR,          0xFFFFFD03,  __READ_WRITE )
__IO_REG16(     CB0RX,           0xFFFFFD04,  __READ       )
__IO_REG8(      CB0RXL,          0xFFFFFD04,  __READ       )
__IO_REG16(     CB0TX,           0xFFFFFD06,  __READ_WRITE )
__IO_REG8(      CB0TXL,          0xFFFFFD06,  __READ_WRITE )

__IO_REG8_BIT(  CB1CTL0,         0xFFFFFD10,  __READ_WRITE )
__IO_REG8_BIT(  CB1CTL1,         0xFFFFFD11,  __READ_WRITE )
__IO_REG8(      CB1CTL2,         0xFFFFFD12,  __READ_WRITE )
__IO_REG8_BIT(  CB1STR,          0xFFFFFD13,  __READ_WRITE )
__IO_REG16(     CB1RX,           0xFFFFFD14,  __READ       )
__IO_REG8(      CB1RXL,          0xFFFFFD14,  __READ       )
__IO_REG16(     CB1TX,           0xFFFFFD16,  __READ_WRITE )
__IO_REG8(      CB1TXL,          0xFFFFFD16,  __READ_WRITE )

__IO_REG8_BIT(  CB2CTL0,         0xFFFFFD20,  __READ_WRITE )
__IO_REG8_BIT(  CB2CTL1,         0xFFFFFD21,  __READ_WRITE )
__IO_REG8(      CB2CTL2,         0xFFFFFD22,  __READ_WRITE )
__IO_REG8_BIT(  CB2STR,          0xFFFFFD23,  __READ_WRITE )
__IO_REG16(     CB2RX,           0xFFFFFD24,  __READ       )
__IO_REG8(      CB2RXL,          0xFFFFFD24,  __READ       )
__IO_REG16(     CB2TX,           0xFFFFFD26,  __READ_WRITE )
__IO_REG8(      CB2TXL,          0xFFFFFD26,  __READ_WRITE )

__IO_REG8(      IIC0,            0xFFFFFD80,  __READ_WRITE )
__IO_REG8_BIT(  IICC0,           0xFFFFFD82,  __READ_WRITE )
__IO_REG8(      SVA0,            0xFFFFFD83,  __READ_WRITE )
__IO_REG8_BIT(  IICCL0,          0xFFFFFD84,  __READ_WRITE )
__IO_REG8_BIT(  IICX0,           0xFFFFFD85,  __READ_WRITE )
__IO_REG8_BIT(  IICS0,           0xFFFFFD86,  __READ       )

__IO_REG8_BIT(  IICF0,           0xFFFFFD8A,  __READ_WRITE )

__IO_REG8(      IICOCKS,         0xFFFFFD90,  __READ_WRITE )

__IO_REG16(     PUDL,            0xFFFFFF44,  __READ_WRITE )
__IO_REG8_BIT(  PUDLL,           0xFFFFFF44,  __READ_WRITE )
__IO_REG8_BIT(  PUDLH,           0xFFFFFF45,  __READ_WRITE )

/***********************************************
 *       Peripheral I/O bit declarations
 ***********************************************/

#ifdef __IAR_SYSTEMS_ICC__

#define E00               DCHC0_bit.no0
#define STG0              DCHC0_bit.no1
#define INIT0             DCHC0_bit.no2
#define MLE0              DCHC0_bit.no3
#define TC0               DCHC0_bit.no7

#define E11               DCHC1_bit.no0
#define STG1              DCHC1_bit.no1
#define INIT1             DCHC1_bit.no2
#define MLE1              DCHC1_bit.no3
#define TC1               DCHC1_bit.no7

#define E22               DCHC2_bit.no0
#define STG2              DCHC2_bit.no1
#define INIT2             DCHC2_bit.no2
#define MLE2              DCHC2_bit.no3
#define TC2               DCHC2_bit.no7

#define E33               DCHC3_bit.no0
#define STG3              DCHC3_bit.no1
#define INIT3             DCHC3_bit.no2
#define MLE3              DCHC3_bit.no3
#define TC3               DCHC3_bit.no7

#define LVILMK            LVILIC_bit.no6
#define LVILIF            LVILIC_bit.no7

#define LVIHMK            LVIHIC_bit.no6
#define LVIHIF            LVIHIC_bit.no7

#define PMK00             PIC00_bit.no6
#define PIF00             PIC00_bit.no7

#define PMK01             PIC01_bit.no6
#define PIF01             PIC01_bit.no7

#define PMK02             PIC02_bit.no6
#define PIF02             PIC02_bit.no7

#define PMK03             PIC03_bit.no6
#define PIF03             PIC03_bit.no7

#define PMK04             PIC04_bit.no6
#define PIF04             PIC04_bit.no7

#define PMK05             PIC05_bit.no6
#define PIF05             PIC05_bit.no7

#define PMK06             PIC06_bit.no6
#define PIF06             PIC06_bit.no7

#define PMK07             PIC07_bit.no6
#define PIF07             PIC07_bit.no7

#define PMK08             PIC08_bit.no6
#define PIF08             PIC08_bit.no7

#define PMK09             PIC09_bit.no6
#define PIF09             PIC09_bit.no7

#define PMK10             PIC10_bit.no6
#define PIF10             PIC10_bit.no7

#define PMK11             PIC11_bit.no6
#define PIF11             PIC11_bit.no7

#define PMK12             PIC12_bit.no6
#define PIF12             PIC12_bit.no7

#define PMK13             PIC13_bit.no6
#define PIF13             PIC13_bit.no7

#define PMK14             PIC14_bit.no6
#define PIF14             PIC14_bit.no7

#define PMK15             PIC15_bit.no6
#define PIF15             PIC15_bit.no7

#define PMK16             PIC16_bit.no6
#define PIF16             PIC16_bit.no7

#define PMK17             PIC17_bit.no6
#define PIF17             PIC17_bit.no7

#define PMK18             PIC18_bit.no6
#define PIF18             PIC18_bit.no7

#define CMPMK0L           CMPIC0L_bit.no6
#define CMPIF0L           CMPIC0L_bit.no7

#define CMPMK0F           CMPIC0F_bit.no6
#define CMPIF0F           CMPIC0F_bit.no7

#define CMPMK1L           CMPIC1L_bit.no6
#define CMPIF1L           CMPIC1L_bit.no7

#define CMPMK1F           CMPIC1F_bit.no6
#define CMPIF1F           CMPIC1F_bit.no7

#define TB0OVMK           TB0OVIC_bit.no6
#define TB0OVIF           TB0OVIC_bit.no7

#define TB0CCMK0          TB0CCIC0_bit.no6
#define TB0CCIF0          TB0CCIC0_bit.no7

#define TB0CCMK1          TB0CCIC1_bit.no6
#define TB0CCIF1          TB0CCIC1_bit.no7

#define TB0CCMK2          TB0CCIC2_bit.no6
#define TB0CCIF2          TB0CCIC2_bit.no7

#define TB0CCMK3          TB0CCIC3_bit.no6
#define TB0CCIF3          TB0CCIC3_bit.no7

#define TB1OVMK           TB1OVIC_bit.no6
#define TB1OVIF           TB1OVIC_bit.no7

#define TB1CCMK0          TB1CCIC0_bit.no6
#define TB1CCIF0          TB1CCIC0_bit.no7

#define TB1CCMK1          TB1CCIC1_bit.no6
#define TB1CCIF1          TB1CCIC1_bit.no7

#define TB1CCMK2          TB1CCIC2_bit.no6
#define TB1CCIF2          TB1CCIC2_bit.no7

#define TB1CCMK3          TB1CCIC3_bit.no6
#define TB1CCIF3          TB1CCIC3_bit.no7

#define TT0OVMK           TT0OVIC_bit.no6
#define TT0OVIF           TT0OVIC_bit.no7

#define TT0CCMK0          TT0CCIC0_bit.no6
#define TT0CCIF0          TT0CCIC0_bit.no7

#define TT0CCMK1          TT0CCIC1_bit.no6
#define TT0CCIF1          TT0CCIC1_bit.no7

#define TT0IECMK          TT0IECIC_bit.no6
#define TT0IECIF          TT0IECIC_bit.no7

#define TT1OVMK           TT1OVIC_bit.no6
#define TT1OVIF           TT1OVIC_bit.no7

#define TT1CCMK0          TT1CCIC0_bit.no6
#define TT1CCIF0          TT1CCIC0_bit.no7

#define TT1CCMK1          TT1CCIC1_bit.no6
#define TT1CCIF1          TT1CCIC1_bit.no7

#define TT1IECMK          TT1IECIC_bit.no6
#define TT1IECIF          TT1IECIC_bit.no7

#define TA0OVMK           TA0OVIC_bit.no6
#define TA0OVIF           TA0OVIC_bit.no7

#define TA0CCMK0          TA0CCIC0_bit.no6
#define TA0CCIF0          TA0CCIC0_bit.no7

#define TA0CCMK1          TA0CCIC1_bit.no6
#define TA0CCIF1          TA0CCIC1_bit.no7

#define TA1OVMK           TA1OVIC_bit.no6
#define TA1OVIF           TA1OVIC_bit.no7

#define TA1CCMK0          TA1CCIC0_bit.no6
#define TA1CCIF0          TA1CCIC0_bit.no7

#define TA1CCMK1          TA1CCIC1_bit.no6
#define TA1CCIF1          TA1CCIC1_bit.no7

#define TA2OVMK           TA2OVIC_bit.no6
#define TA2OVIF           TA2OVIC_bit.no7

#define TA2CCMK0          TA2CCIC0_bit.no6
#define TA2CCIF0          TA2CCIC0_bit.no7

#define TA2CCMK1          TA2CCIC1_bit.no6
#define TA2CCIF1          TA2CCIC1_bit.no7

#define TA3OVMK           TA3OVIC_bit.no6
#define TA3OVIF           TA3OVIC_bit.no7

#define TA3CCMK0          TA3CCIC0_bit.no6
#define TA3CCIF0          TA3CCIC0_bit.no7

#define TA3CCMK1          TA3CCIC1_bit.no6
#define TA3CCIF1          TA3CCIC1_bit.no7

#define TA4OVMK           TA4OVIC_bit.no6
#define TA4OVIF           TA4OVIC_bit.no7

#define TA4CCMK0          TA4CCIC0_bit.no6
#define TA4CCIF0          TA4CCIC0_bit.no7

#define TA4CCMK1          TA4CCIC1_bit.no6
#define TA4CCIF1          TA4CCIC1_bit.no7

#define DMAMK0            DMAIC0_bit.no6
#define DMAIF0            DMAIC0_bit.no7

#define DMAMK1            DMAIC1_bit.no6
#define DMAIF1            DMAIC1_bit.no7

#define DMAMK2            DMAIC2_bit.no6
#define DMAIF2            DMAIC2_bit.no7

#define DMAMK3            DMAIC3_bit.no6
#define DMAIF3            DMAIC3_bit.no7

#define UREMK             UREIC_bit.no6
#define UREIF             UREIC_bit.no7

#define URMK              URIC_bit.no6
#define URIF              URIC_bit.no7

#define UTMK              UTIC_bit.no6
#define UTIF              UTIC_bit.no7

#define UIFMK             UIFIC_bit.no6
#define UIFIF             UIFIC_bit.no7

#define UTOMK             UTOIC_bit.no6
#define UTOIF             UTOIC_bit.no7

#define UA0REMK           UA0REIC_bit.no6
#define UA0REIF           UA0REIC_bit.no7

#define UA0RMK            UA0RIC_bit.no6
#define UA0RIF            UA0RIC_bit.no7

#define UA0TMK            UA0TIC_bit.no6
#define UA0TIF            UA0TIC_bit.no7

#define CB0REMK           CB0REIC_bit.no6
#define CB0REIF           CB0REIC_bit.no7

#define CB0RMK            CB0RIC_bit.no6
#define CB0RIF            CB0RIC_bit.no7

#define CB0TMK            CB0TIC_bit.no6
#define CB0TIF            CB0TIC_bit.no7

#define UA1REMK           UA1REIC_bit.no6
#define UA1REIF           UA1REIC_bit.no7

#define UA1RMK            UA1RIC_bit.no6
#define UA1RIF            UA1RIC_bit.no7

#define UA1TMK            UA1TIC_bit.no6
#define UA1TIF            UA1TIC_bit.no7

#define CB1REMK           CB1REIC_bit.no6
#define CB1REIF           CB1REIC_bit.no7

#define CB1RMK            CB1RIC_bit.no6
#define CB1RIF            CB1RIC_bit.no7

#define CB1TMK            CB1TIC_bit.no6
#define CB1TIF            CB1TIC_bit.no7

#define UA2REMK           UA2REIC_bit.no6
#define UA2REIF           UA2REIC_bit.no7

#define UA2RMK            UA2RIC_bit.no6
#define UA2RIF            UA2RIC_bit.no7

#define UA2TMK            UA2TIC_bit.no6
#define UA2TIF            UA2TIC_bit.no7

#define CB2REMK           CB2REIC_bit.no6
#define CB2REIF           CB2REIC_bit.no7

#define CB2RMK            CB2RIC_bit.no6
#define CB2RIF            CB2RIC_bit.no7

#define CB2TMK            CB2TIC_bit.no6
#define CB2TIF            CB2TIC_bit.no7

#define IICMK             IICIC_bit.no6
#define IICIF             IICIC_bit.no7

#define AD0MK             AD0IC_bit.no6
#define AD0IF             AD0IC_bit.no7

#define AD1MK             AD1IC_bit.no6
#define AD1IF             AD1IC_bit.no7

#define AD2MK             AD2IC_bit.no6
#define AD2IF             AD2IC_bit.no7

#define TM0EQMK0          TM0EQIC0_bit.no6
#define TM0EQIF0          TM0EQIC0_bit.no7

#define TM1EQMK0          TM1EQIC0_bit.no6
#define TM1EQIF0          TM1EQIC0_bit.no7

#define TM2EQMK0          TM2EQIC0_bit.no6
#define TM2EQIF0          TM2EQIC0_bit.no7

#define TM3EQMK0          TM3EQIC0_bit.no6
#define TM3EQIF0          TM3EQIC0_bit.no7

#define ADT0MK            ADT0IC_bit.no6
#define ADT0IF            ADT0IC_bit.no7

#define ADT1MK            ADT1IC_bit.no6
#define ADT1IF            ADT1IC_bit.no7

#define ISPR0             ISPR_bit.no0
#define ISPR1             ISPR_bit.no1
#define ISPR2             ISPR_bit.no2
#define ISPR3             ISPR_bit.no3
#define ISPR4             ISPR_bit.no4
#define ISPR5             ISPR_bit.no5
#define ISPR6             ISPR_bit.no6
#define ISPR7             ISPR_bit.no7

#define STB               PSC_bit.no1
#define INTM              PSC_bit.no4
#define NMI0M             PSC_bit.no5

#define AD0CE             AD0SCMH_bit.no7

#define AD1CE             AD1SCMH_bit.no7

#define TM0CE             TM0CTL0_bit.no7

#define TM1CE             TM1CTL0_bit.no7

#define TM2CE             TM2CTL0_bit.no7

#define TM3CE             TM3CTL0_bit.no7

#define TT0CE             TT0CTL0_bit.no7

#define TT0OE0            TT0IOC0_bit.no0
#define TT0OE1            TT0IOC0_bit.no2

#define TT0OVF            TT0OPT0_bit.no0

#define TT0ESF            TT0OPT1_bit.no0
#define TT0EOF            TT0OPT1_bit.no1
#define TT0EUF            TT0OPT1_bit.no2

#define TT1CE             TT1CTL0_bit.no7

#define TT1OE0            TT1IOC0_bit.no0
#define TT1OE1            TT1IOC0_bit.no2

#define TT1OVF            TT1OPT0_bit.no0

#define TT1ESF            TT1OPT1_bit.no0
#define TT1EOF            TT1OPT1_bit.no1
#define TT1EUF            TT1OPT1_bit.no2

#define TAB0CE            TAB0CTL0_bit.no7

#define TAB0OE0           TAB0IOC0_bit.no0
#define TAB0OE1           TAB0IOC0_bit.no2
#define TAB0OE2           TAB0IOC0_bit.no4
#define TAB0OE3           TAB0IOC0_bit.no6

#define TAB0OVF           TAB0OPT0_bit.no0
#define TAB0CUF           TAB0OPT0_bit.no1
#define TAB0CMS           TAB0OPT0_bit.no2
#define TAB0CCS0          TAB0OPT0_bit.no4
#define TAB0CCS1          TAB0OPT0_bit.no5
#define TAB0CCS2          TAB0OPT0_bit.no6
#define TAB0CCS3          TAB0OPT0_bit.no7

#define TAB0IOE           TAB0OPT1_bit.no6
#define TAB0ICE           TAB0OPT1_bit.no7

#define TAB0AT0           TAB0OPT2_bit.no0
#define TAB0AT1           TAB0OPT2_bit.no1
#define TAB0AT2           TAB0OPT2_bit.no2
#define TAB0AT3           TAB0OPT2_bit.no3
#define TAB0ATM2          TAB0OPT2_bit.no4
#define TAB0ATM3          TAB0OPT2_bit.no5
#define TAB0DTM           TAB0OPT2_bit.no6
#define TAB0RDE           TAB0OPT2_bit.no7

#define TAB0OEB1          TAB0IOC3_bit.no2
#define TAB0OLB1          TAB0IOC3_bit.no3
#define TAB0OEB2          TAB0IOC3_bit.no4
#define TAB0OLB2          TAB0IOC3_bit.no5
#define TAB0OEB3          TAB0IOC3_bit.no6
#define TAB0OLB3          TAB0IOC3_bit.no7

#define TAB0AT4           TAB0OPT3_bit.no0
#define TAB0AT5           TAB0OPT3_bit.no1
#define TAB0AT6           TAB0OPT3_bit.no2
#define TAB0AT7           TAB0OPT3_bit.no3
#define TAB0ATM6          TAB0OPT3_bit.no4
#define TAB0ATM7          TAB0OPT3_bit.no5

#define HZA0DCF0          HZA0CTL0_bit.no0
#define HZA0DCC0          HZA0CTL0_bit.no2
#define HZA0DCT0          HZA0CTL0_bit.no3
#define HZA0DCM0          HZA0CTL0_bit.no6
#define HZA0DCE0          HZA0CTL0_bit.no7

#define HZA0DCF1          HZA0CTL1_bit.no0
#define HZA0DCC1          HZA0CTL1_bit.no2
#define HZA0DCT1          HZA0CTL1_bit.no3
#define HZA0DCM1          HZA0CTL1_bit.no6
#define HZA0DCE1          HZA0CTL1_bit.no7

#define HZA1DCF0          HZA1CTL0_bit.no0
#define HZA1DCC0          HZA1CTL0_bit.no2
#define HZA1DCT0          HZA1CTL0_bit.no3
#define HZA1DCM0          HZA1CTL0_bit.no6
#define HZA1DCE0          HZA1CTL0_bit.no7

#define HZA1DCF1          HZA1CTL1_bit.no0
#define HZA1DCC1          HZA1CTL1_bit.no2
#define HZA1DCT1          HZA1CTL1_bit.no3
#define HZA1DCM1          HZA1CTL1_bit.no6
#define HZA1DCE1          HZA1CTL1_bit.no7

#define TAB1CE            TAB1CTL0_bit.no7

#define TAB1OE0           TAB1IOC0_bit.no0
#define TAB1OE1           TAB1IOC0_bit.no2
#define TAB1OE2           TAB1IOC0_bit.no4
#define TAB1OE3           TAB1IOC0_bit.no6

#define TAB1OVF           TAB1OPT0_bit.no0
#define TAB1CUF           TAB1OPT0_bit.no1
#define TAB1CMS           TAB1OPT0_bit.no2
#define TAB1CCS0          TAB1OPT0_bit.no4
#define TAB1CCS1          TAB1OPT0_bit.no5
#define TAB1CCS2          TAB1OPT0_bit.no6
#define TAB1CCS3          TAB1OPT0_bit.no7

#define TAB1IOE           TAB1OPT1_bit.no6
#define TAB1ICE           TAB1OPT1_bit.no7

#define TAB1AT0           TAB1OPT2_bit.no0
#define TAB1AT1           TAB1OPT2_bit.no1
#define TAB1AT2           TAB1OPT2_bit.no2
#define TAB1AT3           TAB1OPT2_bit.no3
#define TAB1ATM2          TAB1OPT2_bit.no4
#define TAB1ATM3          TAB1OPT2_bit.no5
#define TAB1DTM           TAB1OPT2_bit.no6
#define TAB1RDE           TAB1OPT2_bit.no7

#define TAB1OEB1          TAB1IOC3_bit.no2
#define TAB1OLB1          TAB1IOC3_bit.no3
#define TAB1OEB2          TAB1IOC3_bit.no4
#define TAB1OLB2          TAB1IOC3_bit.no5
#define TAB1OEB3          TAB1IOC3_bit.no6
#define TAB1OLB3          TAB1IOC3_bit.no7

#define TAB1AT4           TAB1OPT3_bit.no0
#define TAB1AT5           TAB1OPT3_bit.no1
#define TAB1AT6           TAB1OPT3_bit.no2
#define TAB1AT7           TAB1OPT3_bit.no3
#define TAB1ATM6          TAB1OPT3_bit.no4
#define TAB1ATM7          TAB1OPT3_bit.no5

#define HZA2DCF0          HZA2CTL0_bit.no0
#define HZA2DCC0          HZA2CTL0_bit.no2
#define HZA2DCT0          HZA2CTL0_bit.no3
#define HZA2DCM0          HZA2CTL0_bit.no6
#define HZA2DCE0          HZA2CTL0_bit.no7

#define HZA2DCF1          HZA2CTL1_bit.no0
#define HZA2DCC1          HZA2CTL1_bit.no2
#define HZA2DCT1          HZA2CTL1_bit.no3
#define HZA2DCM1          HZA2CTL1_bit.no6
#define HZA2DCE1          HZA2CTL1_bit.no7

#define HZA3DCF0          HZA3CTL0_bit.no0
#define HZA3DCC0          HZA3CTL0_bit.no2
#define HZA3DCT0          HZA3CTL0_bit.no3
#define HZA3DCM0          HZA3CTL0_bit.no6
#define HZA3DCE0          HZA3CTL0_bit.no7

#define HZA3DCF1          HZA3CTL1_bit.no0
#define HZA3DCC1          HZA3CTL1_bit.no2
#define HZA3DCT1          HZA3CTL1_bit.no3
#define HZA3DCM1          HZA3CTL1_bit.no6
#define HZA3DCE1          HZA3CTL1_bit.no7

#define TAA0CE            TAA0CTL0_bit.no7

#define TAA0OVF           TAA0OPT0_bit.no0

#define TAA1CE            TAA1CTL0_bit.no7

#define TAA1OVF           TAA1OPT0_bit.no0

#define TAA2CE            TAA2CTL0_bit.no7

#define TAA2OE0           TAA2IOC0_bit.no0
#define TAA2OE1           TAA2IOC0_bit.no2

#define TAA2OVF           TAA2OPT0_bit.no0

#define PRERR             SYS_bit.no0

#define DF0               DTFR0_bit.no7

#define DF1               DTFR1_bit.no7

#define DF2               DTFR2_bit.no7

#define DF3               DTFR3_bit.no7

#define PSM0              PSMR_bit.no0

#define PLLON             PLLCTL_bit.no0
#define SELPLL            PLLCTL_bit.no1

#define LVIF              LVIM_bit.no0
#define LVIMD             LVIM_bit.no1
#define LVION             LVIM_bit.no7

#define UA0DIR            UA0CTL0_bit.no4
#define UA0RXE            UA0CTL0_bit.no5
#define UA0TXE            UA0CTL0_bit.no6
#define UA0PWR            UA0CTL0_bit.no7

#define UA0OVE            UA0STR_bit.no0
#define UA0FE             UA0STR_bit.no1
#define UA0PE             UA0STR_bit.no2
#define UA0TSF            UA0STR_bit.no7

#define UA1DIR            UA1CTL0_bit.no4
#define UA1RXE            UA1CTL0_bit.no5
#define UA1TXE            UA1CTL0_bit.no6
#define UA1PWR            UA1CTL0_bit.no7

#define UA1OVE            UA1STR_bit.no0
#define UA1FE             UA1STR_bit.no1
#define UA1PE             UA1STR_bit.no2
#define UA1TSF            UA1STR_bit.no7

#define UA2DIR            UA2CTL0_bit.no4
#define UA2RXE            UA2CTL0_bit.no5
#define UA2TXE            UA2CTL0_bit.no6
#define UA2PWR            UA2CTL0_bit.no7

#define UA2OVE            UA2STR_bit.no0
#define UA2FE             UA2STR_bit.no1
#define UA2PE             UA2STR_bit.no2
#define UA2TSF            UA2STR_bit.no7

#define UBDIR             UBCTL0_bit.no4
#define UBRXE             UBCTL0_bit.no5
#define UBTXE             UBCTL0_bit.no6
#define UBPWR             UBCTL0_bit.no7

#define UBOVE             UBSTR_bit.no0
#define UBFE              UBSTR_bit.no1
#define UBPE              UBSTR_bit.no2
#define UBTSF             UBSTR_bit.no7

#define TAA3CE            TAA3CTL0_bit.no7

#define TAA3OE0           TAA3IOC0_bit.no0
#define TAA3OE1           TAA3IOC0_bit.no2

#define TAA3OVF           TAA3OPT0_bit.no0

#define TAA4CE            TAA4CTL0_bit.no7

#define TAA4OE0           TAA4IOC0_bit.no0
#define TAA4OE1           TAA4IOC0_bit.no2

#define TAA4OVF           TAA4OPT0_bit.no0

#define AD2CE             AD2M0_bit.no7

#define INTF00            INTF0_bit.no0
#define INTF01            INTF0_bit.no1
#define INTF02            INTF0_bit.no2
#define INTF03            INTF0_bit.no3
#define INTF04            INTF0_bit.no4
#define INTF05            INTF0_bit.no5
#define INTF06            INTF0_bit.no6
#define INTF07            INTF0_bit.no7

#define INTF08            INTF1_bit.no0
#define INTF09            INTF1_bit.no1
#define INTF10            INTF1_bit.no2
#define INTF11            INTF1_bit.no3
#define INTF12            INTF1_bit.no4
#define INTF13            INTF1_bit.no5
#define INTF17            INTF1_bit.no6
#define INTF18            INTF1_bit.no7

#define INTF14            INTF2_bit.no0
#define INTF15            INTF2_bit.no1
#define INTF16            INTF2_bit.no2

#define INTR00            INTR0_bit.no0
#define INTR01            INTR0_bit.no1
#define INTR02            INTR0_bit.no2
#define INTR03            INTR0_bit.no3
#define INTR04            INTR0_bit.no4
#define INTR05            INTR0_bit.no5
#define INTR06            INTR0_bit.no6
#define INTR07            INTR0_bit.no7

#define INTR08            INTR1_bit.no0
#define INTR09            INTR1_bit.no1
#define INTR10            INTR1_bit.no2
#define INTR11            INTR1_bit.no3
#define INTR12            INTR1_bit.no4
#define INTR13            INTR1_bit.no5
#define INTR17            INTR1_bit.no6
#define INTR18            INTR1_bit.no7

#define INTR14            INTR2_bit.no0
#define INTR15            INTR2_bit.no1
#define INTR16            INTR2_bit.no2

#define CB0SCE            CB0CTL0_bit.no0
#define CB0DIR            CB0CTL0_bit.no4
#define CB0RXE            CB0CTL0_bit.no5
#define CB0TXE            CB0CTL0_bit.no6
#define CB0PWR            CB0CTL0_bit.no7

#define CB0OVE            CB0STR_bit.no0
#define CB0TSF            CB0STR_bit.no7

#define CB1SCE            CB1CTL0_bit.no0
#define CB1DIR            CB1CTL0_bit.no4
#define CB1RXE            CB1CTL0_bit.no5
#define CB1TXE            CB1CTL0_bit.no6
#define CB1PWR            CB1CTL0_bit.no7

#define CB1OVE            CB1STR_bit.no0
#define CB1TSF            CB1STR_bit.no7

#define CB2SCE            CB2CTL0_bit.no0
#define CB2DIR            CB2CTL0_bit.no4
#define CB2RXE            CB2CTL0_bit.no5
#define CB2TXE            CB2CTL0_bit.no6
#define CB2PWR            CB2CTL0_bit.no7

#define CB2OVE            CB2STR_bit.no0
#define CB2TSF            CB2STR_bit.no7

#define SPT0              IICC0_bit.no0
#define STT0              IICC0_bit.no1
#define ACKE0             IICC0_bit.no2
#define WTIM0             IICC0_bit.no3
#define SPIE0             IICC0_bit.no4
#define WREL0             IICC0_bit.no5
#define LREL0             IICC0_bit.no6
#define IICE0             IICC0_bit.no7

#define DAD0              IICCL0_bit.no4
#define CLD0              IICCL0_bit.no5

#define CLX0              IICX0_bit.no0

#define SPD0              IICS0_bit.no0
#define STD0              IICS0_bit.no1
#define ACKD0             IICS0_bit.no2
#define TRC0              IICS0_bit.no3
#define COI0              IICS0_bit.no4
#define EXC0              IICS0_bit.no5
#define ALD0              IICS0_bit.no6
#define MSTS0             IICS0_bit.no7

#define IICRSV0           IICF0_bit.no0
#define STCEN0            IICF0_bit.no1
#define IICBSY0           IICF0_bit.no6
#define STCF0             IICF0_bit.no7

#endif /* __IAR_SYSTEMS_ICC__ */

/***********************************************
 *       Interrupt/Exeption table declarations
 ***********************************************/

#define RESET_vector             (0x0000)
#define INTWDT_vector            (0x0010)
#define DBG0_vector              (0x0060)
#define ILGOP_vector             (0x0060)
#define SECURITY_ID_vector       (0x0070)
#define INTLVIL_vector           (0x0080)
#define INTLVIH_vector           (0x0090)
#define INTP00_vector            (0x00A0)
#define INTP01_vector            (0x00B0)
#define INTP02_vector            (0x00C0)
#define INTP03_vector            (0x00D0)
#define INTP04_vector            (0x00E0)
#define INTP05_vector            (0x00F0)
#define INTP06_vector            (0x0100)
#define INTP07_vector            (0x0110)
#define INTP08_vector            (0x0120)
#define INTP09_vector            (0x0130)
#define INTP10_vector            (0x0140)
#define INTP11_vector            (0x0150)
#define INTP12_vector            (0x0160)
#define INTP13_vector            (0x0170)
#define INTP14_vector            (0x0180)
#define INTP15_vector            (0x0190)
#define INTP16_vector            (0x01A0)
#define INTP17_vector            (0x01B0)
#define INTP18_vector            (0x01C0)
#define INTCMP0L_vector          (0x01D0)
#define INTCMP0F_vector          (0x01E0)
#define INTCMP1L_vector          (0x01F0)
#define INTCMP1F_vector          (0x0200)
#define INTTB0OV_vector          (0x0210)
#define INTTB0CC0_vector         (0x0220)
#define INTTB0CC1_vector         (0x0230)
#define INTTB0CC2_vector         (0x0240)
#define INTTB0CC3_vector         (0x0250)
#define INTTB1OV_vector          (0x0260)
#define INTTB1CC0_vector         (0x0270)
#define INTTB1CC1_vector         (0x0280)
#define INTTB1CC2_vector         (0x0290)
#define INTTB1CC3_vector         (0x02A0)
#define INTTTIOV0_vector         (0x02B0)
#define INTTTEQC00_vector        (0x02C0)
#define INTTTEQC01_vector        (0x02D0)
#define INTTIEC0_vector          (0x02E0)
#define INTTTIOV1_vector         (0x02F0)
#define INTTTEQC10_vector        (0x0300)
#define INTTTEQC11_vector        (0x0310)
#define INTTIEC1_vector          (0x0320)
#define INTTA0OV_vector          (0x0330)
#define INTTA0CC0_vector         (0x0340)
#define INTTA0CC1_vector         (0x0350)
#define INTTA1OV_vector          (0x0360)
#define INTTA1CC0_vector         (0x0370)
#define INTTA1CC1_vector         (0x0380)
#define INTTA2OV_vector          (0x0390)
#define INTTA2CC0_vector         (0x03A0)
#define INTTA2CC1_vector         (0x03B0)
#define INTTA3OV_vector          (0x03C0)
#define INTTA3CC0_vector         (0x03D0)
#define INTTA3CC1_vector         (0x03E0)
#define INTTA4OV_vector          (0x03F0)
#define INTTA4CC0_vector         (0x0400)
#define INTTA4CC1_vector         (0x0410)
#define INTDMA0_vector           (0x0420)
#define INTDMA1_vector           (0x0430)
#define INTDMA2_vector           (0x0440)
#define INTDMA3_vector           (0x0450)
#define INTUBTIRE_vector         (0x0460)
#define INTUBTIR_vector          (0x0470)
#define INTUBTIT_vector          (0x0480)
#define INTUBTIF_vector          (0x0490)
#define INTUBTITO_vector         (0x04A0)
#define INTUA0RE_vector          (0x04B0)
#define INTUA0R_vector           (0x04C0)
#define INTUA0T_vector           (0x04D0)
#define INTCB0RE_vector          (0x04E0)
#define INTCB0R_vector           (0x04F0)
#define INTCB0T_vector           (0x0500)
#define INTUA1RE_vector          (0x0510)
#define INTUA1R_vector           (0x0520)
#define INTUA1T_vector           (0x0530)
#define INTCB1RE_vector          (0x0540)
#define INTCB1R_vector           (0x0550)
#define INTCB1T_vector           (0x0560)
#define INTUA2RE_vector          (0x0570)
#define INTUA2R_vector           (0x0580)
#define INTUA2T_vector           (0x0590)
#define INTCB2RE_vector          (0x05A0)
#define INTCB2R_vector           (0x05B0)
#define INTCB2T_vector           (0x05C0)
#define INTIIC_vector            (0x05D0)
#define INTAD0_vector            (0x05E0)
#define INTAD1_vector            (0x05F0)
#define INTAD2_vector            (0x0600)
#define INTTM0EQ0_vector         (0x0610)
#define INTTM1EQ0_vector         (0x0620)
#define INTTM2EQ0_vector         (0x0630)
#define INTTM3EQ0_vector         (0x0640)
#define INTADT0_vector           (0x0650)
#define INTADT1_vector           (0x0660)
#define INTWARE_vector           (0x0790)
#define INTWAR_vector            (0x07A0)
#define INTWAT_vector            (0x07B0)
#define INTECCER_vector          (0x07C0)

/***********************************************
 *       Trap vectors
 ***********************************************/

#define TRAP00_vector      (0x00)
#define TRAP01_vector      (0x01)
#define TRAP02_vector      (0x02)
#define TRAP03_vector      (0x03)
#define TRAP04_vector      (0x04)
#define TRAP05_vector      (0x05)
#define TRAP06_vector      (0x06)
#define TRAP07_vector      (0x07)
#define TRAP08_vector      (0x08)
#define TRAP09_vector      (0x09)
#define TRAP0A_vector      (0x0A)
#define TRAP0B_vector      (0x0B)
#define TRAP0C_vector      (0x0C)
#define TRAP0D_vector      (0x0D)
#define TRAP0E_vector      (0x0E)
#define TRAP0F_vector      (0x0F)
#define TRAP10_vector      (0x10)
#define TRAP11_vector      (0x11)
#define TRAP12_vector      (0x12)
#define TRAP13_vector      (0x13)
#define TRAP14_vector      (0x14)
#define TRAP15_vector      (0x15)
#define TRAP16_vector      (0x16)
#define TRAP17_vector      (0x17)
#define TRAP18_vector      (0x18)
#define TRAP19_vector      (0x19)
#define TRAP1A_vector      (0x1A)
#define TRAP1B_vector      (0x1B)
#define TRAP1C_vector      (0x1C)
#define TRAP1D_vector      (0x1D)
#define TRAP1E_vector      (0x1E)
#define TRAP1F_vector      (0x1F)

/***********************************************
 *       Callt vectors
 ***********************************************/

#define CALLT00_vector     (0x00)
#define CALLT01_vector     (0x01)
#define CALLT02_vector     (0x02)
#define CALLT03_vector     (0x03)
#define CALLT04_vector     (0x04)
#define CALLT05_vector     (0x05)
#define CALLT06_vector     (0x06)
#define CALLT07_vector     (0x07)
#define CALLT08_vector     (0x08)
#define CALLT09_vector     (0x09)
#define CALLT0A_vector     (0x0A)
#define CALLT0B_vector     (0x0B)
#define CALLT0C_vector     (0x0C)
#define CALLT0D_vector     (0x0D)
#define CALLT0E_vector     (0x0E)
#define CALLT0F_vector     (0x0F)
#define CALLT10_vector     (0x10)
#define CALLT11_vector     (0x11)
#define CALLT12_vector     (0x12)
#define CALLT13_vector     (0x13)
#define CALLT14_vector     (0x14)
#define CALLT15_vector     (0x15)
#define CALLT16_vector     (0x16)
#define CALLT17_vector     (0x17)
#define CALLT18_vector     (0x18)
#define CALLT19_vector     (0x19)
#define CALLT1A_vector     (0x1A)
#define CALLT1B_vector     (0x1B)
#define CALLT1C_vector     (0x1C)
#define CALLT1D_vector     (0x1D)
#define CALLT1E_vector     (0x1E)
#define CALLT1F_vector     (0x1F)
#define CALLT20_vector     (0x20)
#define CALLT21_vector     (0x21)
#define CALLT22_vector     (0x22)
#define CALLT23_vector     (0x23)
#define CALLT24_vector     (0x24)
#define CALLT25_vector     (0x25)
#define CALLT26_vector     (0x26)
#define CALLT27_vector     (0x27)
#define CALLT28_vector     (0x28)
#define CALLT29_vector     (0x29)
#define CALLT2A_vector     (0x2A)
#define CALLT2B_vector     (0x2B)
#define CALLT2C_vector     (0x2C)
#define CALLT2D_vector     (0x2D)
#define CALLT2E_vector     (0x2E)
#define CALLT2F_vector     (0x2F)
#define CALLT30_vector     (0x30)
#define CALLT31_vector     (0x31)
#define CALLT32_vector     (0x32)
#define CALLT33_vector     (0x33)
#define CALLT34_vector     (0x34)
#define CALLT35_vector     (0x35)
#define CALLT36_vector     (0x36)
#define CALLT37_vector     (0x37)
#define CALLT38_vector     (0x38)
#define CALLT39_vector     (0x39)
#define CALLT3A_vector     (0x3A)
#define CALLT3B_vector     (0x3B)
#define CALLT3C_vector     (0x3C)
#define CALLT3D_vector     (0x3D)
#define CALLT3E_vector     (0x3E)
#define CALLT3F_vector     (0x3F)

#pragma language=default

#endif /* __IO70F3454_H__ */
