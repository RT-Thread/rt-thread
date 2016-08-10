/*
** ###################################################################
**     Version:             rev. 1.0, 2014-05-15
**     Build:               b141209
**
**     Abstract:
**         Common include file for CMSIS register access layer headers.
**
**     Copyright (c) 2015 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2014-05-15)
**         Customer release.
**
** ###################################################################
*/

#ifndef __FSL_DEVICE_REGISTERS_H__
#define __FSL_DEVICE_REGISTERS_H__

/*
 * Include the cpu specific register header files.
 *
 * The CPU macro should be declared in the project or makefile.
 */
#if (defined(CPU_MK02FN128VFM10) || defined(CPU_MK02FN64VFM10) || defined(CPU_MK02FN128VLF10) || \
    defined(CPU_MK02FN64VLF10) || defined(CPU_MK02FN128VLH10) || defined(CPU_MK02FN64VLH10))

    #define K02F12810_SERIES

    /* CMSIS-style register definitions */
    #include "MK02F12810/include/MK02F12810.h"
    /* Extension register definitions */
    #include "MK02F12810/include/MK02F12810_extension.h"
    /* CPU specific feature definitions */
    #include "MK02F12810/include/MK02F12810_features.h"

#elif (defined(CPU_MK10DN512VLK10) || defined(CPU_MK10DN512VLL10) || defined(CPU_MK10DX128VLQ10) || \
    defined(CPU_MK10DX256VLQ10) || defined(CPU_MK10DN512VLQ10) || defined(CPU_MK10DN512VMC10) || \
    defined(CPU_MK10DX128VMD10) || defined(CPU_MK10DX256VMD10) || defined(CPU_MK10DN512VMD10))

    #define K10D10_SERIES

    /* CMSIS-style register definitions */
    #include "MK10D10/include/MK10D10.h"
    /* Extension register definitions */
    #include "MK10D10/include/MK10D10_extension.h"
    /* CPU specific feature definitions */
    #include "MK10D10/include/MK10D10_features.h"

#elif (defined(CPU_MK11DX128AVLK5) || defined(CPU_MK11DX256AVLK5) || defined(CPU_MK11DN512AVLK5) || \
    defined(CPU_MK11DX128AVMC5) || defined(CPU_MK11DX256AVMC5) || defined(CPU_MK11DN512AVMC5))

    #define K11DA5_SERIES

    /* CMSIS-style register definitions */
    #include "MK11DA5/include/MK11DA5.h"
    /* Extension register definitions */
    #include "MK11DA5/include/MK11DA5_extension.h"
    /* CPU specific feature definitions */
    #include "MK11DA5/include/MK11DA5_features.h"

#elif (defined(CPU_MK20DN512VLK10) || defined(CPU_MK20DX256VLK10) || defined(CPU_MK20DN512VLL10) || \
    defined(CPU_MK20DX256VLL10) || defined(CPU_MK20DX128VLQ10) || defined(CPU_MK20DX256VLQ10) || \
    defined(CPU_MK20DN512VLQ10) || defined(CPU_MK20DX256VMC10) || defined(CPU_MK20DN512VMC10) || \
    defined(CPU_MK20DX128VMD10) || defined(CPU_MK20DX256VMD10) || defined(CPU_MK20DN512VMD10))

    #define K20D10_SERIES

    /* CMSIS-style register definitions */
    #include "MK20D10/include/MK20D10.h"
    /* Extension register definitions */
    #include "MK20D10/include/MK20D10_extension.h"
    /* CPU specific feature definitions */
    #include "MK20D10/include/MK20D10_features.h"

#elif (defined(CPU_MK20DX128VMP5) || defined(CPU_MK20DN128VMP5) || defined(CPU_MK20DX64VMP5) || \
    defined(CPU_MK20DN64VMP5) || defined(CPU_MK20DX32VMP5) || defined(CPU_MK20DN32VMP5) || \
    defined(CPU_MK20DX128VLH5) || defined(CPU_MK20DN128VLH5) || defined(CPU_MK20DX64VLH5) || \
    defined(CPU_MK20DN64VLH5) || defined(CPU_MK20DX32VLH5) || defined(CPU_MK20DN32VLH5) || \
    defined(CPU_MK20DX128VFM5) || defined(CPU_MK20DN128VFM5) || defined(CPU_MK20DX64VFM5) || \
    defined(CPU_MK20DN64VFM5) || defined(CPU_MK20DX32VFM5) || defined(CPU_MK20DN32VFM5) || \
    defined(CPU_MK20DX128VFT5) || defined(CPU_MK20DN128VFT5) || defined(CPU_MK20DX64VFT5) || \
    defined(CPU_MK20DN64VFT5) || defined(CPU_MK20DX32VFT5) || defined(CPU_MK20DN32VFT5) || \
    defined(CPU_MK20DX128VLF5) || defined(CPU_MK20DN128VLF5) || defined(CPU_MK20DX64VLF5) || \
    defined(CPU_MK20DN64VLF5) || defined(CPU_MK20DX32VLF5) || defined(CPU_MK20DN32VLF5))

    #define K20D5_SERIES

    /* CMSIS-style register definitions */
    #include "MK20D5/include/MK20D5.h"
    /* Extension register definitions */
    #include "MK20D5/include/MK20D5_extension.h"
    /* CPU specific feature definitions */
    #include "MK20D5/include/MK20D5_features.h"

#elif (defined(CPU_MK21DX128AVLK5) || defined(CPU_MK21DX256AVLK5) || defined(CPU_MK21DN512AVLK5) || \
    defined(CPU_MK21DX128AVMC5) || defined(CPU_MK21DX256AVMC5) || defined(CPU_MK21DN512AVMC5))

    #define K21DA5_SERIES

    /* CMSIS-style register definitions */
    #include "MK21DA5/include/MK21DA5.h"
    /* Extension register definitions */
    #include "MK21DA5/include/MK21DA5_extension.h"
    /* CPU specific feature definitions */
    #include "MK21DA5/include/MK21DA5_features.h"

#elif (defined(CPU_MK21FX512AVLQ12) || defined(CPU_MK21FN1M0AVLQ12) || defined(CPU_MK21FX512AVMC12) || \
    defined(CPU_MK21FN1M0AVMC12) || defined(CPU_MK21FX512AVMD12) || defined(CPU_MK21FN1M0AVMD12))

    #define K21FA12_SERIES

    /* CMSIS-style register definitions */
    #include "MK21FA12/include/MK21FA12.h"
    /* Extension register definitions */
    #include "MK21FA12/include/MK21FA12_extension.h"
    /* CPU specific feature definitions */
    #include "MK21FA12/include/MK21FA12_features.h"

#elif (defined(CPU_MK22FN128VDC10) || defined(CPU_MK22FN128VLH10) || defined(CPU_MK22FN128VLL10) || \
    defined(CPU_MK22FN128VMP10))

    #define K22F12810_SERIES

    /* CMSIS-style register definitions */
    #include "MK22F12810/include/MK22F12810.h"
    /* Extension register definitions */
    #include "MK22F12810/include/MK22F12810_extension.h"
    /* CPU specific feature definitions */
    #include "MK22F12810/include/MK22F12810_features.h"

#elif (defined(CPU_MK22FX512AVLH12) || defined(CPU_MK22FN1M0AVLH12) || defined(CPU_MK22FX512AVLK12) || \
    defined(CPU_MK22FN1M0AVLK12) || defined(CPU_MK22FX512AVLL12) || defined(CPU_MK22FN1M0AVLL12) || \
    defined(CPU_MK22FX512AVLQ12) || defined(CPU_MK22FN1M0AVLQ12) || defined(CPU_MK22FX512AVMC12) || \
    defined(CPU_MK22FN1M0AVMC12) || defined(CPU_MK22FX512AVMD12) || defined(CPU_MK22FN1M0AVMD12))

    #define K22FA12_SERIES

    /* CMSIS-style register definitions */
    #include "MK22FA12/include/MK22FA12.h"
    /* Extension register definitions */
    #include "MK22FA12/include/MK22FA12_extension.h"
    /* CPU specific feature definitions */
    #include "MK22FA12/include/MK22FA12_features.h"

#elif (defined(CPU_MK22FN256CAH12) || defined(CPU_MK22FN128CAH12) || defined(CPU_MK22FN256VDC12) || \
    defined(CPU_MK22FN256VLH12) || defined(CPU_MK22FN256VLL12) || defined(CPU_MK22FN256VMP12))

    #define K22F25612_SERIES

    /* CMSIS-style register definitions */
    #include "MK22F25612/include/MK22F25612.h"
    /* Extension register definitions */
    #include "MK22F25612/include/MK22F25612_extension.h"
    /* CPU specific feature definitions */
    #include "MK22F25612/include/MK22F25612_features.h"

#elif (defined(CPU_MK22FN512CAP12) || defined(CPU_MK22FN512VDC12) || defined(CPU_MK22FN512VLH12) || \
    defined(CPU_MK22FN512VLL12) || defined(CPU_MK22FN512VMP12))

    #define K22F51212_SERIES

    /* CMSIS-style register definitions */
    #include "MK22F51212/include/MK22F51212.h"
    /* Extension register definitions */
    #include "MK22F51212/include/MK22F51212_extension.h"
    /* CPU specific feature definitions */
    #include "MK22F51212/include/MK22F51212_features.h"

#elif (defined(CPU_MK24FN1M0VDC12) || defined(CPU_MK24FN1M0VLL12) || defined(CPU_MK24FN1M0VLQ12))

    #define K24F12_SERIES

    /* CMSIS-style register definitions */
    #include "MK24F12/include/MK24F12.h"
    /* Extension register definitions */
    #include "MK24F12/include/MK24F12_extension.h"
    /* CPU specific feature definitions */
    #include "MK24F12/include/MK24F12_features.h"

#elif (defined(CPU_MK24FN256VDC12))

    #define K24F25612_SERIES

    /* CMSIS-style register definitions */
    #include "MK24F25612/include/MK24F25612.h"
    /* Extension register definitions */
    #include "MK24F25612/include/MK24F25612_extension.h"
    /* CPU specific feature definitions */
    #include "MK24F25612/include/MK24F25612_features.h"

#elif (defined(CPU_MK26FN2M0CAC18) || defined(CPU_MK26FN2M0VLQ18) || defined(CPU_MK26FN2M0VMD18) || \
    defined(CPU_MK26FN2M0VMI18))

    #define K26F18_SERIES

    /* CMSIS-style register definitions */
    #include "MK26F18/include/MK26F18.h"
    /* Extension register definitions */
    #include "MK26F18/include/MK26F18_extension.h"
    /* CPU specific feature definitions */
    #include "MK26F18/include/MK26F18_features.h"

#elif (defined(CPU_MK30DN512VLK10) || defined(CPU_MK30DN512VLL10) || defined(CPU_MK30DX128VLQ10) || \
    defined(CPU_MK30DX256VLQ10) || defined(CPU_MK30DN512VLQ10) || defined(CPU_MK30DN512VMC10) || \
    defined(CPU_MK30DX128VMD10) || defined(CPU_MK30DX256VMD10) || defined(CPU_MK30DN512VMD10))

    #define K30D10_SERIES

    /* CMSIS-style register definitions */
    #include "MK30D10/include/MK30D10.h"
    /* Extension register definitions */
    #include "MK30D10/include/MK30D10_extension.h"
    /* CPU specific feature definitions */
    #include "MK30D10/include/MK30D10_features.h"

#elif (defined(CPU_MK40DN512VLK10) || defined(CPU_MK40DN512VLL10) || defined(CPU_MK40DX128VLQ10) || \
    defined(CPU_MK40DX256VLQ10) || defined(CPU_MK40DN512VLQ10) || defined(CPU_MK40DN512VMC10) || \
    defined(CPU_MK40DX128VMD10) || defined(CPU_MK40DX256VMD10) || defined(CPU_MK40DN512VMD10))

    #define K40D10_SERIES

    /* CMSIS-style register definitions */
    #include "MK40D10/include/MK40D10.h"
    /* Extension register definitions */
    #include "MK40D10/include/MK40D10_extension.h"
    /* CPU specific feature definitions */
    #include "MK40D10/include/MK40D10_features.h"

#elif (defined(CPU_MK50DX256CLL10) || defined(CPU_MK50DN512CLL10) || defined(CPU_MK50DN512CLQ10) || \
    defined(CPU_MK50DX256CMC10) || defined(CPU_MK50DN512CMC10) || defined(CPU_MK50DN512CMD10) || \
    defined(CPU_MK50DX256CMD10) || defined(CPU_MK50DX256CLK10))

    #define K50D10_SERIES

    /* CMSIS-style register definitions */
    #include "MK50D10/include/MK50D10.h"
    /* Extension register definitions */
    #include "MK50D10/include/MK50D10_extension.h"
    /* CPU specific feature definitions */
    #include "MK50D10/include/MK50D10_features.h"

#elif (defined(CPU_MK51DX256CLL10) || defined(CPU_MK51DN512CLL10) || defined(CPU_MK51DN256CLQ10) || \
    defined(CPU_MK51DN512CLQ10) || defined(CPU_MK51DX256CMC10) || defined(CPU_MK51DN512CMC10) || \
    defined(CPU_MK51DN256CMD10) || defined(CPU_MK51DN512CMD10) || defined(CPU_MK51DX256CLK10))

    #define K51D10_SERIES

    /* CMSIS-style register definitions */
    #include "MK51D10/include/MK51D10.h"
    /* Extension register definitions */
    #include "MK51D10/include/MK51D10_extension.h"
    /* CPU specific feature definitions */
    #include "MK51D10/include/MK51D10_features.h"

#elif (defined(CPU_MK52DN512CLQ10) || defined(CPU_MK52DN512CMD10))

    #define K52D10_SERIES

    /* CMSIS-style register definitions */
    #include "MK52D10/include/MK52D10.h"
    /* Extension register definitions */
    #include "MK52D10/include/MK52D10_extension.h"
    /* CPU specific feature definitions */
    #include "MK52D10/include/MK52D10_features.h"

#elif (defined(CPU_MK53DN512CLQ10) || defined(CPU_MK53DX256CLQ10) || defined(CPU_MK53DN512CMD10) || \
    defined(CPU_MK53DX256CMD10))

    #define K53D10_SERIES

    /* CMSIS-style register definitions */
    #include "MK53D10/include/MK53D10.h"
    /* Extension register definitions */
    #include "MK53D10/include/MK53D10_extension.h"
    /* CPU specific feature definitions */
    #include "MK53D10/include/MK53D10_features.h"

#elif (defined(CPU_MK60DN256VLL10) || defined(CPU_MK60DX256VLL10) || defined(CPU_MK60DN512VLL10) || \
    defined(CPU_MK60DN256VLQ10) || defined(CPU_MK60DX256VLQ10) || defined(CPU_MK60DN512VLQ10) || \
    defined(CPU_MK60DN256VMC10) || defined(CPU_MK60DX256VMC10) || defined(CPU_MK60DN512VMC10) || \
    defined(CPU_MK60DN256VMD10) || defined(CPU_MK60DX256VMD10) || defined(CPU_MK60DN512VMD10))

    #define K60D10_SERIES

    /* CMSIS-style register definitions */
    #include "MK60D10/include/MK60D10.h"
    /* Extension register definitions */
    #include "MK60D10/include/MK60D10_extension.h"
    /* CPU specific feature definitions */
    #include "MK60D10/include/MK60D10_features.h"

#elif (defined(CPU_MK63FN1M0VLQ12) || defined(CPU_MK63FN1M0VMD12))

    #define K63F12_SERIES

    /* CMSIS-style register definitions */
    #include "MK63F12/include/MK63F12.h"
    /* Extension register definitions */
    #include "MK63F12/include/MK63F12_extension.h"
    /* CPU specific feature definitions */
    #include "MK63F12/include/MK63F12_features.h"

#elif (defined(CPU_MK64FX512VDC12) || defined(CPU_MK64FN1M0VDC12) || defined(CPU_MK64FX512VLL12) || \
    defined(CPU_MK64FN1M0VLL12) || defined(CPU_MK64FX512VLQ12) || defined(CPU_MK64FN1M0VLQ12) || \
    defined(CPU_MK64FX512VMD12) || defined(CPU_MK64FN1M0VMD12))


    #define K64F12_SERIES
    /* CMSIS-style register definitions */
    #include "MK64F12/include/MK64F12.h"
    /* Extension register definitions */
    #include "MK64F12/include/MK64F12_extension.h"
    /* CPU specific feature definitions */
    #include "MK64F12/include/MK64F12_features.h"

#elif (defined(CPU_MK65FN2M0CAC18) || defined(CPU_MK65FX1M0CAC18) || defined(CPU_MK65FN2M0VMI18) || \
    defined(CPU_MK65FX1M0VMI18))

    #define K65F18_SERIES

    /* CMSIS-style register definitions */
    #include "MK65F18/include/MK65F18.h"
    /* Extension register definitions */
    #include "MK65F18/include/MK65F18_extension.h"
    /* CPU specific feature definitions */
    #include "MK65F18/include/MK65F18_features.h"

#elif (defined(CPU_MK66FN2M0VLQ18) || defined(CPU_MK66FX1M0VLQ18) || defined(CPU_MK66FN2M0VMD18) || \
    defined(CPU_MK66FX1M0VMD18))

    #define K66F18_SERIES

    /* CMSIS-style register definitions */
    #include "MK66F18/include/MK66F18.h"
    /* Extension register definitions */
    #include "MK66F18/include/MK66F18_extension.h"
    /* CPU specific feature definitions */
    #include "MK66F18/include/MK66F18_features.h"

#elif (defined(CPU_MK70FN1M0VMJ12) || defined(CPU_MK70FX512VMJ12))

    #define K70F12_SERIES

    /* CMSIS-style register definitions */
    #include "MK70F12/include/MK70F12.h"
    /* Extension register definitions */
    #include "MK70F12/include/MK70F12_extension.h"
    /* CPU specific feature definitions */
    #include "MK70F12/include/MK70F12_features.h"

#elif (defined(CPU_MK70FN1M0VMJ15) || defined(CPU_MK70FX512VMJ15))

    #define K70F15_SERIES

    /* CMSIS-style register definitions */
    #include "MK70F15/include/MK70F15.h"
    /* Extension register definitions */
    #include "MK70F15/include/MK70F15_extension.h"
    /* CPU specific feature definitions */
    #include "MK70F15/include/MK70F15_features.h"

#elif (defined(CPU_MK80FN256CAx15) || defined(CPU_MK80FN256VDC15) || defined(CPU_MK80FN256VLL15) || \
    defined(CPU_MK80FN256VLQ15))

    #define K80F25615_SERIES

    /* CMSIS-style register definitions */
    #include "MK80F25615/include/MK80F25615.h"
    /* Extension register definitions */
    #include "MK80F25615/include/MK80F25615_extension.h"
    /* CPU specific feature definitions */
    #include "MK80F25615/include/MK80F25615_features.h"

#elif (defined(CPU_MK81FN256CAx15) || defined(CPU_MK81FN256VDC15) || defined(CPU_MK81FN256VLL15) || \
    defined(CPU_MK81FN256VLQ15))

    #define K81F25615_SERIES

    /* CMSIS-style register definitions */
    #include "MK81F25615/include/MK81F25615.h"
    /* Extension register definitions */
    #include "MK81F25615/include/MK81F25615_extension.h"
    /* CPU specific feature definitions */
    #include "MK81F25615/include/MK81F25615_features.h"

#elif (defined(CPU_MK82FN256CAx15) || defined(CPU_MK82FN256VDC15) || defined(CPU_MK82FN256VLL15) || \
    defined(CPU_MK82FN256VLQ15))

    #define K82F25615_SERIES

    /* CMSIS-style register definitions */
    #include "MK82F25615/include/MK82F25615.h"
    /* Extension register definitions */
    #include "MK82F25615/include/MK82F25615_extension.h"
    /* CPU specific feature definitions */
    #include "MK82F25615/include/MK82F25615_features.h"

#elif (defined(CPU_MKE02Z64VLC2) || defined(CPU_MKE02Z32VLC2) || defined(CPU_MKE02Z16VLC2) || \
    defined(CPU_MKE02Z64VLD2) || defined(CPU_MKE02Z32VLD2) || defined(CPU_MKE02Z16VLD2) || \
    defined(CPU_MKE02Z64VLH2) || defined(CPU_MKE02Z64VQH2) || defined(CPU_MKE02Z32VLH2) || \
    defined(CPU_MKE02Z32VQH2))

    #define KE02Z2_SERIES

    /* CMSIS-style register definitions */
    #include "MKE02Z2/include/MKE02Z2.h"
    /* Extension register definitions */
    #include "MKE02Z2/include/MKE02Z2_extension.h"
    /* CPU specific feature definitions */
    #include "MKE02Z2/include/MKE02Z2_features.h"

#elif (defined(CPU_SKEAZN64MLC2) || defined(CPU_SKEAZN32MLC2) || defined(CPU_SKEAZN16MLC2) || \
    defined(CPU_SKEAZN64MLD2) || defined(CPU_SKEAZN32MLD2) || defined(CPU_SKEAZN16MLD2) || \
    defined(CPU_SKEAZN64MLH2) || defined(CPU_SKEAZN32MLH2))

    #define SKEAZN642_SERIES

    /* CMSIS-style register definitions */
    #include "SKEAZN642/include/SKEAZN642.h"
    /* Extension register definitions */
    #include "SKEAZN642/include/SKEAZN642_extension.h"
    /* CPU specific feature definitions */
    #include "SKEAZN642/include/SKEAZN642_features.h"

#elif (defined(CPU_MKE02Z64VLC4) || defined(CPU_MKE02Z32VLC4) || defined(CPU_MKE02Z16VLC4) || \
    defined(CPU_MKE02Z64VLD4) || defined(CPU_MKE02Z32VLD4) || defined(CPU_MKE02Z16VLD4) || \
    defined(CPU_MKE02Z64VLH4) || defined(CPU_MKE02Z64VQH4) || defined(CPU_MKE02Z32VLH4) || \
    defined(CPU_MKE02Z32VQH4))

    #define KE02Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKE02Z4/include/MKE02Z4.h"
    /* Extension register definitions */
    #include "MKE02Z4/include/MKE02Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKE02Z4/include/MKE02Z4_features.h"

#elif (defined(CPU_MKE04Z128VLD4) || defined(CPU_MKE04Z64VLD4) || defined(CPU_MKE04Z128VLK4) || \
    defined(CPU_MKE04Z64VLK4) || defined(CPU_MKE04Z128VQH4) || defined(CPU_MKE04Z64VQH4) || \
    defined(CPU_MKE04Z128VLH4) || defined(CPU_MKE04Z64VLH4))

    #define KE04Z1284_SERIES

    /* CMSIS-style register definitions */
    #include "MKE04Z1284/include/MKE04Z1284.h"
    /* Extension register definitions */
    #include "MKE04Z1284/include/MKE04Z1284_extension.h"
    /* CPU specific feature definitions */
    #include "MKE04Z1284/include/MKE04Z1284_features.h"

#elif (defined(CPU_MKE04Z8VFK4) || defined(CPU_MKE04Z8VTG4) || defined(CPU_MKE04Z8VWJ4))

    #define KE04Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKE04Z4/include/MKE04Z4.h"
    /* Extension register definitions */
    #include "MKE04Z4/include/MKE04Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKE04Z4/include/MKE04Z4_features.h"

#elif (defined(CPU_SKEAZN8MFK) || defined(CPU_SKEAZN8MTG))

    #define SKEAZN84_SERIES

    /* CMSIS-style register definitions */
    #include "SKEAZN84/include/SKEAZN84.h"
    /* Extension register definitions */
    #include "SKEAZN84/include/SKEAZN84_extension.h"
    /* CPU specific feature definitions */
    #include "SKEAZN84/include/SKEAZN84_features.h"

#elif (defined(CPU_MKE06Z128VLD4) || defined(CPU_MKE06Z64VLD4) || defined(CPU_MKE06Z128VLK4) || \
    defined(CPU_MKE06Z64VLK4) || defined(CPU_MKE06Z128VQH4) || defined(CPU_MKE06Z64VQH4) || \
    defined(CPU_MKE06Z128VLH4) || defined(CPU_MKE06Z64VLH4))

    #define KE06Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKE06Z4/include/MKE06Z4.h"
    /* Extension register definitions */
    #include "MKE06Z4/include/MKE06Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKE06Z4/include/MKE06Z4_features.h"

#elif (defined(CPU_MKL02Z32CAF4) || defined(CPU_MKL02Z8VFG4) || defined(CPU_MKL02Z16VFG4) || \
    defined(CPU_MKL02Z32VFG4) || defined(CPU_MKL02Z16VFK4) || defined(CPU_MKL02Z32VFK4) || \
    defined(CPU_MKL02Z16VFM4) || defined(CPU_MKL02Z32VFM4))

    #define KL02Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL02Z4/include/MKL02Z4.h"
    /* Extension register definitions */
    #include "MKL02Z4/include/MKL02Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL02Z4/include/MKL02Z4_features.h"

#elif (defined(CPU_MKL03Z32CAF4) || defined(CPU_MKL03Z8VFG4) || defined(CPU_MKL03Z16VFG4) || \
    defined(CPU_MKL03Z32VFG4) || defined(CPU_MKL03Z8VFK4) || defined(CPU_MKL03Z16VFK4) || \
    defined(CPU_MKL03Z32VFK4))

    #define KL03Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL03Z4/include/MKL03Z4.h"
    /* Extension register definitions */
    #include "MKL03Z4/include/MKL03Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL03Z4/include/MKL03Z4_features.h"

#elif (defined(CPU_MKL04Z8VFK4) || defined(CPU_MKL04Z16VFK4) || defined(CPU_MKL04Z32VFK4) || \
    defined(CPU_MKL04Z8VLC4) || defined(CPU_MKL04Z16VLC4) || defined(CPU_MKL04Z32VLC4) || \
    defined(CPU_MKL04Z8VFM4) || defined(CPU_MKL04Z16VFM4) || defined(CPU_MKL04Z32VFM4) || \
    defined(CPU_MKL04Z16VLF4) || defined(CPU_MKL04Z32VLF4))

    #define KL04Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL04Z4/include/MKL04Z4.h"
    /* Extension register definitions */
    #include "MKL04Z4/include/MKL04Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL04Z4/include/MKL04Z4_features.h"

#elif (defined(CPU_MKL05Z8VFK4) || defined(CPU_MKL05Z16VFK4) || defined(CPU_MKL05Z32VFK4) || \
    defined(CPU_MKL05Z8VLC4) || defined(CPU_MKL05Z16VLC4) || defined(CPU_MKL05Z32VLC4) || \
    defined(CPU_MKL05Z8VFM4) || defined(CPU_MKL05Z16VFM4) || defined(CPU_MKL05Z32VFM4) || \
    defined(CPU_MKL05Z16VLF4) || defined(CPU_MKL05Z32VLF4))

    #define KL05Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL05Z4/include/MKL05Z4.h"
    /* Extension register definitions */
    #include "MKL05Z4/include/MKL05Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL05Z4/include/MKL05Z4_features.h"

#elif (defined(CPU_MKL13Z32VFM4) || defined(CPU_MKL13Z64VFM4) || defined(CPU_MKL13Z32VFT4) || \
    defined(CPU_MKL13Z64VFT4) || defined(CPU_MKL13Z32VLH4) || defined(CPU_MKL13Z64VLH4) || \
    defined(CPU_MKL13Z32VLK4) || defined(CPU_MKL13Z64VLK4) || defined(CPU_MKL13Z32VMP4) || \
    defined(CPU_MKL13Z64VMP4))

    #define KL13Z644_SERIES

    /* CMSIS-style register definitions */
    #include "MKL13Z644/include/MKL13Z644.h"
    /* Extension register definitions */
    #include "MKL13Z644/include/MKL13Z644_extension.h"
    /* CPU specific feature definitions */
    #include "MKL13Z644/include/MKL13Z644_features.h"

#elif (defined(CPU_MKL14Z32VFM4) || defined(CPU_MKL14Z64VFM4) || defined(CPU_MKL14Z32VFT4) || \
    defined(CPU_MKL14Z64VFT4) || defined(CPU_MKL14Z32VLH4) || defined(CPU_MKL14Z64VLH4) || \
    defined(CPU_MKL14Z32VLK4) || defined(CPU_MKL14Z64VLK4))

    #define KL14Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL14Z4/include/MKL14Z4.h"
    /* Extension register definitions */
    #include "MKL14Z4/include/MKL14Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL14Z4/include/MKL14Z4_features.h"

#elif (defined(CPU_MKL15Z128CAD4) || defined(CPU_MKL15Z32VFM4) || defined(CPU_MKL15Z64VFM4) || \
    defined(CPU_MKL15Z128VFM4) || defined(CPU_MKL15Z32VFT4) || defined(CPU_MKL15Z64VFT4) || \
    defined(CPU_MKL15Z128VFT4) || defined(CPU_MKL15Z32VLH4) || defined(CPU_MKL15Z64VLH4) || \
    defined(CPU_MKL15Z128VLH4) || defined(CPU_MKL15Z32VLK4) || defined(CPU_MKL15Z64VLK4) || \
    defined(CPU_MKL15Z128VLK4))

    #define KL15Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL15Z4/include/MKL15Z4.h"
    /* Extension register definitions */
    #include "MKL15Z4/include/MKL15Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL15Z4/include/MKL15Z4_features.h"

#elif (defined(CPU_MKL16Z32VFM4) || defined(CPU_MKL16Z64VFM4) || defined(CPU_MKL16Z128VFM4) || \
    defined(CPU_MKL16Z32VFT4) || defined(CPU_MKL16Z64VFT4) || defined(CPU_MKL16Z128VFT4) || \
    defined(CPU_MKL16Z32VLH4) || defined(CPU_MKL16Z64VLH4) || defined(CPU_MKL16Z128VLH4) || \
    defined(CPU_MKL16Z256VLH4) || defined(CPU_MKL16Z256VMP4))

    #define KL16Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL16Z4/include/MKL16Z4.h"
    /* Extension register definitions */
    #include "MKL16Z4/include/MKL16Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL16Z4/include/MKL16Z4_features.h"

#elif (defined(CPU_MKL17Z128VFM4) || defined(CPU_MKL17Z256VFM4) || defined(CPU_MKL17Z128VFT4) || \
    defined(CPU_MKL17Z256VFT4) || defined(CPU_MKL17Z128VLH4) || defined(CPU_MKL17Z256VLH4) || \
    defined(CPU_MKL17Z128VMP4) || defined(CPU_MKL17Z256VMP4))

    #define KL17Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL17Z4/include/MKL17Z4.h"
    /* Extension register definitions */
    #include "MKL17Z4/include/MKL17Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL17Z4/include/MKL17Z4_features.h"

#elif (defined(CPU_MKL17Z32VDA4) || defined(CPU_MKL17Z64VDA4) || defined(CPU_MKL17Z32VFM4) || \
    defined(CPU_MKL17Z64VFM4) || defined(CPU_MKL17Z32VFT4) || defined(CPU_MKL17Z64VFT4) || \
    defined(CPU_MKL17Z32VLH4) || defined(CPU_MKL17Z64VLH4) || defined(CPU_MKL17Z32VMP4) || \
    defined(CPU_MKL17Z64VMP4))

    #define KL17Z644_SERIES

    /* CMSIS-style register definitions */
    #include "MKL17Z644/include/MKL17Z644.h"
    /* Extension register definitions */
    #include "MKL17Z644/include/MKL17Z644_extension.h"
    /* CPU specific feature definitions */
    #include "MKL17Z644/include/MKL17Z644_features.h"

#elif (defined(CPU_MKL24Z32VFM4) || defined(CPU_MKL24Z64VFM4) || defined(CPU_MKL24Z32VFT4) || \
    defined(CPU_MKL24Z64VFT4) || defined(CPU_MKL24Z32VLH4) || defined(CPU_MKL24Z64VLH4) || \
    defined(CPU_MKL24Z32VLK4) || defined(CPU_MKL24Z64VLK4))

    #define KL24Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL24Z4/include/MKL24Z4.h"
    /* Extension register definitions */
    #include "MKL24Z4/include/MKL24Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL24Z4/include/MKL24Z4_features.h"

#elif (defined(CPU_MKL25Z32VFM4) || defined(CPU_MKL25Z64VFM4) || defined(CPU_MKL25Z128VFM4) || \
    defined(CPU_MKL25Z32VFT4) || defined(CPU_MKL25Z64VFT4) || defined(CPU_MKL25Z128VFT4) || \
    defined(CPU_MKL25Z32VLH4) || defined(CPU_MKL25Z64VLH4) || defined(CPU_MKL25Z128VLH4) || \
    defined(CPU_MKL25Z32VLK4) || defined(CPU_MKL25Z64VLK4) || defined(CPU_MKL25Z128VLK4))

    #define KL25Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL25Z4/include/MKL25Z4.h"
    /* Extension register definitions */
    #include "MKL25Z4/include/MKL25Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL25Z4/include/MKL25Z4_features.h"


#elif (defined(CPU_MKL26Z128CAL4) || defined(CPU_MKL26Z32VFM4) || defined(CPU_MKL26Z64VFM4) || \
    defined(CPU_MKL26Z128VFM4) || defined(CPU_MKL26Z32VFT4) || defined(CPU_MKL26Z64VFT4) || \
    defined(CPU_MKL26Z128VFT4) || defined(CPU_MKL26Z32VLH4) || defined(CPU_MKL26Z64VLH4) || \
    defined(CPU_MKL26Z128VLH4) || defined(CPU_MKL26Z256VLH4) || defined(CPU_MKL26Z128VLL4) || \
    defined(CPU_MKL26Z256VLL4) || defined(CPU_MKL26Z128VMC4) || defined(CPU_MKL26Z256VMC4) || \
    defined(CPU_MKL26Z256VMP4))

    #define KL26Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL26Z4/include/MKL26Z4.h"
    /* Extension register definitions */
    #include "MKL26Z4/include/MKL26Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL26Z4/include/MKL26Z4_features.h"

#elif (defined(CPU_MKL27Z128VFM4) || defined(CPU_MKL27Z256VFM4) || defined(CPU_MKL27Z128VFT4) || \
    defined(CPU_MKL27Z256VFT4) || defined(CPU_MKL27Z128VLH4) || defined(CPU_MKL27Z256VLH4) || \
    defined(CPU_MKL27Z128VMP4) || defined(CPU_MKL27Z256VMP4))

    #define KL27Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL27Z4/include/MKL27Z4.h"
    /* Extension register definitions */
    #include "MKL27Z4/include/MKL27Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL27Z4/include/MKL27Z4_features.h"

#elif (defined(CPU_MKL27Z32VDA4) || defined(CPU_MKL27Z64VDA4) || defined(CPU_MKL27Z32VFM4) || \
    defined(CPU_MKL27Z64VFM4) || defined(CPU_MKL27Z32VFT4) || defined(CPU_MKL27Z64VFT4) || \
    defined(CPU_MKL27Z32VLH4) || defined(CPU_MKL27Z64VLH4) || defined(CPU_MKL27Z32VMP4) || \
    defined(CPU_MKL27Z64VMP4))

    #define KL27Z644_SERIES

    /* CMSIS-style register definitions */
    #include "MKL27Z644/include/MKL27Z644.h"
    /* Extension register definitions */
    #include "MKL27Z644/include/MKL27Z644_extension.h"
    /* CPU specific feature definitions */
    #include "MKL27Z644/include/MKL27Z644_features.h"

#elif (defined(CPU_MKL33Z128VLH4) || defined(CPU_MKL33Z256VLH4) || defined(CPU_MKL33Z128VMP4) || \
    defined(CPU_MKL33Z256VMP4))

    #define KL33Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL33Z4/include/MKL33Z4.h"
    /* Extension register definitions */
    #include "MKL33Z4/include/MKL33Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL33Z4/include/MKL33Z4_features.h"

#elif (defined(CPU_MKL33Z32VFT4) || defined(CPU_MKL33Z64VFT4) || defined(CPU_MKL33Z32VLH4) || \
    defined(CPU_MKL33Z64VLH4) || defined(CPU_MKL33Z32VLK4) || defined(CPU_MKL33Z64VLK4) || \
    defined(CPU_MKL33Z32VMP4) || defined(CPU_MKL33Z64VMP4))

    #define KL33Z644_SERIES

    /* CMSIS-style register definitions */
    #include "MKL33Z644/include/MKL33Z644.h"
    /* Extension register definitions */
    #include "MKL33Z644/include/MKL33Z644_extension.h"
    /* CPU specific feature definitions */
    #include "MKL33Z644/include/MKL33Z644_features.h"

#elif (defined(CPU_MKL34Z64VLH4) || defined(CPU_MKL34Z64VLL4))

    #define KL34Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL34Z4/include/MKL34Z4.h"
    /* Extension register definitions */
    #include "MKL34Z4/include/MKL34Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL34Z4/include/MKL34Z4_features.h"

#elif (defined(CPU_MKL36Z64VLH4) || defined(CPU_MKL36Z128VLH4) || defined(CPU_MKL36Z256VLH4) || \
    defined(CPU_MKL36Z64VLL4) || defined(CPU_MKL36Z128VLL4) || defined(CPU_MKL36Z256VLL4) || \
    defined(CPU_MKL36Z128VMC4) || defined(CPU_MKL36Z256VMC4) || defined(CPU_MKL36Z256VMP4))

    #define KL36Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL36Z4/include/MKL36Z4.h"
    /* Extension register definitions */
    #include "MKL36Z4/include/MKL36Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL36Z4/include/MKL36Z4_features.h"

#elif (defined(CPU_MKL43Z128VLH4) || defined(CPU_MKL43Z256VLH4) || defined(CPU_MKL43Z128VMP4) || \
    defined(CPU_MKL43Z256VMP4))

    #define KL43Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL43Z4/include/MKL43Z4.h"
    /* Extension register definitions */
    #include "MKL43Z4/include/MKL43Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL43Z4/include/MKL43Z4_features.h"

#elif (defined(CPU_MKL46Z128VLH4) || defined(CPU_MKL46Z256VLH4) || defined(CPU_MKL46Z128VLL4) || \
    defined(CPU_MKL46Z256VLL4) || defined(CPU_MKL46Z128VMC4) || defined(CPU_MKL46Z256VMC4) || \
    defined(CPU_MKL46Z256VMP4))

    #define KL46Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKL46Z4/include/MKL46Z4.h"
    /* Extension register definitions */
    #include "MKL46Z4/include/MKL46Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKL46Z4/include/MKL46Z4_features.h"

#elif (defined(CPU_MKM14Z128AHH5) || defined(CPU_MKM14Z64AHH5))

    #define KM14ZA5_SERIES

    /* CMSIS-style register definitions */
    #include "MKM14ZA5/include/MKM14ZA5.h"
    /* Extension register definitions */
    #include "MKM14ZA5/include/MKM14ZA5_extension.h"
    /* CPU specific feature definitions */
    #include "MKM14ZA5/include/MKM14ZA5_features.h"

#elif (defined(CPU_MKM33Z128ALH5) || defined(CPU_MKM33Z64ALH5) || defined(CPU_MKM33Z128ALL5) || \
    defined(CPU_MKM33Z64ALL5))

    #define KM33ZA5_SERIES

    /* CMSIS-style register definitions */
    #include "MKM33ZA5/include/MKM33ZA5.h"
    /* Extension register definitions */
    #include "MKM33ZA5/include/MKM33ZA5_extension.h"
    /* CPU specific feature definitions */
    #include "MKM33ZA5/include/MKM33ZA5_features.h"

#elif (defined(CPU_MKM34Z128ALL5))

    #define KM34ZA5_SERIES

    /* CMSIS-style register definitions */
    #include "MKM34ZA5/include/MKM34ZA5.h"
    /* Extension register definitions */
    #include "MKM34ZA5/include/MKM34ZA5_extension.h"
    /* CPU specific feature definitions */
    #include "MKM34ZA5/include/MKM34ZA5_features.h"

#elif (defined(CPU_MKM34Z256VLL7) || defined(CPU_MKM34Z256VLQ7))

    #define KM34Z7_SERIES

    /* CMSIS-style register definitions */
    #include "MKM34Z7/include/MKM34Z7.h"
    /* Extension register definitions */
    #include "MKM34Z7/include/MKM34Z7_extension.h"
    /* CPU specific feature definitions */
    #include "MKM34Z7/include/MKM34Z7_features.h"

#elif (defined(CPU_MKV10Z16VFM7) || defined(CPU_MKV10Z16VLC7) || defined(CPU_MKV10Z16VLF7) || \
    defined(CPU_MKV10Z32VFM7) || defined(CPU_MKV10Z32VLC7) || defined(CPU_MKV10Z32VLF7))

    #define KV10Z7_SERIES

    /* CMSIS-style register definitions */
    #include "MKV10Z7/include/MKV10Z7.h"
    /* Extension register definitions */
    #include "MKV10Z7/include/MKV10Z7_extension.h"
    /* CPU specific feature definitions */
    #include "MKV10Z7/include/MKV10Z7_features.h"

#elif (defined(CPU_MKV10Z128VFM7) || defined(CPU_MKV10Z128VLC7) || defined(CPU_MKV10Z128VLF7) || \
    defined(CPU_MKV10Z128VLH7) || defined(CPU_MKV10Z64VFM7) || defined(CPU_MKV10Z64VLC7) || \
    defined(CPU_MKV10Z64VLF7) || defined(CPU_MKV10Z64VLH7))

    #define KV10Z1287_SERIES

    /* CMSIS-style register definitions */
    #include "MKV10Z1287/include/MKV10Z1287.h"
    /* Extension register definitions */
    #include "MKV10Z1287/include/MKV10Z1287_extension.h"
    /* CPU specific feature definitions */
    #include "MKV10Z1287/include/MKV10Z1287_features.h"

#elif (defined(CPU_MKV11Z128VFM7) || defined(CPU_MKV11Z128VLC7) || defined(CPU_MKV11Z128VLF7) || \
    defined(CPU_MKV11Z128VLH7) || defined(CPU_MKV11Z64VFM7) || defined(CPU_MKV11Z64VLC7) || \
    defined(CPU_MKV11Z64VLF7) || defined(CPU_MKV11Z64VLH7))

    #define KV11Z7_SERIES

    /* CMSIS-style register definitions */
    #include "MKV11Z7/include/MKV11Z7.h"
    /* Extension register definitions */
    #include "MKV11Z7/include/MKV11Z7_extension.h"
    /* CPU specific feature definitions */
    #include "MKV11Z7/include/MKV11Z7_features.h"

#elif (defined(CPU_MKV30F128VFM10) || defined(CPU_MKV30F64VFM10) || defined(CPU_MKV30F128VLF10) || \
    defined(CPU_MKV30F64VLF10) || defined(CPU_MKV30F128VLH10) || defined(CPU_MKV30F64VLH10))

    #define KV30F12810_SERIES

    /* CMSIS-style register definitions */
    #include "MKV30F12810/include/MKV30F12810.h"
    /* Extension register definitions */
    #include "MKV30F12810/include/MKV30F12810_extension.h"
    /* CPU specific feature definitions */
    #include "MKV30F12810/include/MKV30F12810_features.h"

#elif (defined(CPU_MKV31F128VLH10) || defined(CPU_MKV31F128VLL10))

    #define KV31F12810_SERIES

    /* CMSIS-style register definitions */
    #include "MKV31F12810/include/MKV31F12810.h"
    /* Extension register definitions */
    #include "MKV31F12810/include/MKV31F12810_extension.h"
    /* CPU specific feature definitions */
    #include "MKV31F12810/include/MKV31F12810_features.h"

#elif (defined(CPU_MKV31F256VLH12) || defined(CPU_MKV31F256VLL12))

    #define KV31F25612_SERIES

    /* CMSIS-style register definitions */
    #include "MKV31F25612/include/MKV31F25612.h"
    /* Extension register definitions */
    #include "MKV31F25612/include/MKV31F25612_extension.h"
    /* CPU specific feature definitions */
    #include "MKV31F25612/include/MKV31F25612_features.h"

#elif (defined(CPU_MKV31F512VLH12) || defined(CPU_MKV31F512VLL12))

    #define KV31F51212_SERIES

    /* CMSIS-style register definitions */
    #include "MKV31F51212/include/MKV31F51212.h"
    /* Extension register definitions */
    #include "MKV31F51212/include/MKV31F51212_extension.h"
    /* CPU specific feature definitions */
    #include "MKV31F51212/include/MKV31F51212_features.h"

#elif (defined(CPU_MKV40F128VLH15) || defined(CPU_MKV40F128VLL15) || defined(CPU_MKV40F256VLH15) || \
    defined(CPU_MKV40F256VLL15) || defined(CPU_MKV40F64VLH15))

    #define KV40F15_SERIES

    /* CMSIS-style register definitions */
    #include "MKV40F15/include/MKV40F15.h"
    /* Extension register definitions */
    #include "MKV40F15/include/MKV40F15_extension.h"
    /* CPU specific feature definitions */
    #include "MKV40F15/include/MKV40F15_features.h"

#elif (defined(CPU_MKV43F128VLH15) || defined(CPU_MKV43F128VLL15) || defined(CPU_MKV43F64VLH15))

    #define KV43F15_SERIES

    /* CMSIS-style register definitions */
    #include "MKV43F15/include/MKV43F15.h"
    /* Extension register definitions */
    #include "MKV43F15/include/MKV43F15_extension.h"
    /* CPU specific feature definitions */
    #include "MKV43F15/include/MKV43F15_features.h"

#elif (defined(CPU_MKV44F128VLH15) || defined(CPU_MKV44F128VLL15) || defined(CPU_MKV44F64VLH15))

    #define KV44F15_SERIES

    /* CMSIS-style register definitions */
    #include "MKV44F15/include/MKV44F15.h"
    /* Extension register definitions */
    #include "MKV44F15/include/MKV44F15_extension.h"
    /* CPU specific feature definitions */
    #include "MKV44F15/include/MKV44F15_features.h"

#elif (defined(CPU_MKV45F128VLH15) || defined(CPU_MKV45F128VLL15) || defined(CPU_MKV45F256VLH15) || \
    defined(CPU_MKV45F256VLL15))

    #define KV45F15_SERIES

    /* CMSIS-style register definitions */
    #include "MKV45F15/include/MKV45F15.h"
    /* Extension register definitions */
    #include "MKV45F15/include/MKV45F15_extension.h"
    /* CPU specific feature definitions */
    #include "MKV45F15/include/MKV45F15_features.h"

#elif (defined(CPU_MKV46F128VLH15) || defined(CPU_MKV46F128VLL15) || defined(CPU_MKV46F256VLH15) || \
    defined(CPU_MKV46F256VLL15))

    #define KV46F15_SERIES

    /* CMSIS-style register definitions */
    #include "MKV46F15/include/MKV46F15.h"
    /* Extension register definitions */
    #include "MKV46F15/include/MKV46F15_extension.h"
    /* CPU specific feature definitions */
    #include "MKV46F15/include/MKV46F15_features.h"

#elif (defined(CPU_MKW01Z128CHN4))

    #define KW01Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKW01Z4/include/MKW01Z4.h"
    /* Extension register definitions */
    #include "MKW01Z4/include/MKW01Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKW01Z4/include/MKW01Z4_features.h"

#elif (defined(CPU_MKW20Z160VHT4))

    #define KW20Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKW20Z4/include/MKW20Z4.h"
    /* Extension register definitions */
    #include "MKW20Z4/include/MKW20Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKW20Z4/include/MKW20Z4_features.h"

#elif (defined(CPU_MKW21D256VHA5) || defined(CPU_MKW21D512VHA5))

    #define KW21D5_SERIES

    /* CMSIS-style register definitions */
    #include "MKW21D5/include/MKW21D5.h"
    /* Extension register definitions */
    #include "MKW21D5/include/MKW21D5_extension.h"
    /* CPU specific feature definitions */
    #include "MKW21D5/include/MKW21D5_features.h"

#elif (defined(CPU_MKW22D512VHA5))

    #define KW22D5_SERIES

    /* CMSIS-style register definitions */
    #include "MKW22D5/include/MKW22D5.h"
    /* Extension register definitions */
    #include "MKW22D5/include/MKW22D5_extension.h"
    /* CPU specific feature definitions */
    #include "MKW22D5/include/MKW22D5_features.h"

#elif (defined(CPU_MKW24D512VHA5))

    #define KW24D5_SERIES

    /* CMSIS-style register definitions */
    #include "MKW24D5/include/MKW24D5.h"
    /* Extension register definitions */
    #include "MKW24D5/include/MKW24D5_extension.h"
    /* CPU specific feature definitions */
    #include "MKW24D5/include/MKW24D5_features.h"

#elif (defined(CPU_MKW30Z160VHM4))

    #define KW30Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKW30Z4/include/MKW30Z4.h"
    /* Extension register definitions */
    #include "MKW30Z4/include/MKW30Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKW30Z4/include/MKW30Z4_features.h"

#elif (defined(CPU_MKW40Z160VHT4))

    #define KW40Z4_SERIES

    /* CMSIS-style register definitions */
    #include "MKW40Z4/include/MKW40Z4.h"
    /* Extension register definitions */
    #include "MKW40Z4/include/MKW40Z4_extension.h"
    /* CPU specific feature definitions */
    #include "MKW40Z4/include/MKW40Z4_features.h"

#elif (defined(CPU_SKEAZ128MLH) || defined(CPU_SKEAZ64MLH) || defined(CPU_SKEAZ128MLK) || \
    defined(CPU_SKEAZ64MLK))

    #define SKEAZ1284_SERIES

    /* CMSIS-style register definitions */
    #include "SKEAZ1284/include/SKEAZ1284.h"
    /* Extension register definitions */
    #include "SKEAZ1284/include/SKEAZ1284_extension.h"
    /* CPU specific feature definitions */
    #include "SKEAZ1284/include/SKEAZ1284_features.h"

#else
    #error "No valid CPU defined!"
#endif

#endif /* __FSL_DEVICE_REGISTERS_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
