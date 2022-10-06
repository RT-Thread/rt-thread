/**
 * \file  vpif.h
 *
 * \brief This file contains the driver API prototypes and macro definitions
 *        for the VPIF module.
 */
 
/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef _VPIF_H_
#define _VPIF_H__

#include "hw_vpif.h"


#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*                           MACRO DEFINITIONS
*******************************************************************************/
/***************************************************************************/
/*
** Constants that represent VPIF channel
** Channel 0 & 1 are capture channels; channel 2 & 3 are display channels 
** Used in most APIs
*/

#define VPIF_CHANNEL_0                          0
#define VPIF_CHANNEL_1                          1
#define VPIF_CHANNEL_2                          2
#define VPIF_CHANNEL_3                          3

/***************************************************************************/
/*
** Values that represent top/bottom field 
** Used in all the FBConfig (frame buffer config) APIs
*/

#define VPIF_TOP_FIELD                          0
#define VPIF_BOTTOM_FIELD                       1

/***************************************************************************/
/*
** Values that represent horizontal/vertical blanking
** Used in VBI (blanking) APIS
*/

#define VPIF_HORIZONTAL                         0
#define VPIF_VERTICAL                           1

/***************************************************************************/
/*
** Values that represent luma/chroma data of the active video
** Used in all the FBConfig (frame buffer config) APIs
*/

#define VPIF_LUMA                               0
#define VPIF_CHROMA                             1

/***************************************************************************/
/*
** Values that can be passed to VPIFCaptureModeConfig/VPIFDisplayModeConfig
** API to select mode of capture/display 
** More supported modes will be added
*/

#define VPIF_RAW                                0
#define VPIF_NONSTANDARD                        1
#define VPIF_480I                               2

/***************************************************************************/
/*
** Values that represent different VPIF interrupts 
** Used in all the interrupt APIs
*/

#define VPIF_ERROR_INT                          (1 << VPIF_INTSET_ERROR_SHIFT)
#define VPIF_FRAMEINT_CH3                       (1 << VPIF_INTSET_FRAME3_SHIFT)
#define VPIF_FRAMEINT_CH2                       (1 << VPIF_INTSET_FRAME2_SHIFT)
#define VPIF_FRAMEINT_CH1                       (1 << VPIF_INTSET_FRAME1_SHIFT)
#define VPIF_FRAMEINT_CH0                       (1 << VPIF_INTSET_FRAME0_SHIFT)

/***************************************************************************/
/*
** Values that represent different errors
** Used in the ErrorStatus APIs
*/

 /* Underflow error for channel 3 */ 
#define VPIF_UNDERFLOW3                         (1 << VPIF_ERRSTAT_UNDERFLOW3_SHIFT)
 /* Underflow error for channel 2 */ 
#define VPIF_UNDERFLOW2                         (1 << VPIF_ERRSTAT_UNDERFLOW2_SHIFT)
 /* Overflow error for channel 1 */ 
#define VPIF_OVERFLOW1                          (1 << VPIF_ERRSTAT_OVERFLOW1_SHIFT)
 /* Overflow error for channel 0 */ 
#define VPIF_OVERFLOW0                          (1 << VPIF_ERRSTAT_OVERFLOW0_SHIFT)
 /* Synchronization error for channel 1 (mismatch EAV2SAV/SAV2EAV) */ 
#define VPIF_SYNCDISTERR1                       (1 << VPIF_ERRSTAT_SYNCDISTERR1_SHIFT)
 /* Synchronization error for channel 0 (mismatch EAV2SAV/SAV2EAV) */ 
#define VPIF_SYNCDISTERR0                       (1 << VPIF_ERRSTAT_SYNCDISTERR0_SHIFT)
 /* Error in EAV2SAV/SAV2EAV code for channel 1 */ 
#define VPIF_BITERR1                            (1 << VPIF_ERRSTAT_BITERR1_SHIFT)
 /* Error in EAV2SAV/SAV2EAV code for channel 1 */ 
#define VPIF_BITERR0                            (1 << VPIF_ERRSTAT_BITERR0_SHIFT)

/***************************************************************************/
/*
** Values that represent different VPIF DMA request sizes
** Used in the VPIFDMARequestSizeConfig API
*/
#define VPIF_REQSIZE_THIRTY_TWO                 (VPIF_REQSIZE_BYTES_THIRTY_TWO << VPIF_REQSIZE_BYTES_SHIFT)
#define VPIF_REQSIZE_SIXTY_FOUR                 (VPIF_REQSIZE_BYTES_SIXTY_FOUR << VPIF_REQSIZE_BYTES_SHIFT)
#define VPIF_REQSIZE_ONE_TWENTY_EIGHT           (VPIF_REQSIZE_BYTES_ONE_TWENTY_EIGHT << VPIF_REQSIZE_BYTES_SHIFT)
#define VPIF_REQSIZE_TWO_FIFTY_SIX              (VPIF_REQSIZE_BYTES_TWO_FIFTY_SIX << VPIF_REQSIZE_BYTES_SHIFT)

/***************************************************************************/
/*
** Values that represent VPIF operation mode during emulation suspend
** Used in the VPIFEmulationControlSet API
*/
 /* VPIF is halted during emulation suspension */
#define VPIF_HALT                               (0 << VPIF_EMUCTRL_FREE_SHIFT)
 /* VPIF operates normally during emulation suspension */
#define VPIF_FREE                               (1 << VPIF_EMUCTRL_FREE_SHIFT)

/***************************************************************************/
/*
** Values that represent which edge of the pixel clock data changes phase on
** Used in the ClkedgeModeSelect APIs for all channels (3/2/1/0)
*/
 /* Data changes on the rising edge of the pixel */
#define VPIF_CLKEDGE_RISING                     (1 << VPIF_C0CTRL_CLKEDGE_SHIFT)
 /* Data changes on the falling edge of the pixel */
#define VPIF_CLKEDGE_FALLING                    (0 << VPIF_C0CTRL_CLKEDGE_SHIFT)

/***************************************************************************/
/*
** Values that represent width of the raw data input
** Used in the VPIFCaptureRawDatawidthConfig API
*/
#define VPIF_RAW_EIGHT_BPS                      (VPIF_C0CTRL_DATAWIDTH_EIGHT_BPS << VPIF_C0CTRL_DATAWIDTH_SHIFT)
#define VPIF_RAW_TEN_BPS                        (VPIF_C0CTRL_DATAWIDTH_TEN_BPS << VPIF_C0CTRL_DATAWIDTH_SHIFT)
#define VPIF_RAW_TWELVE_BPS                     (VPIF_C0CTRL_DATAWIDTH_TWELVE_BPS << VPIF_C0CTRL_DATAWIDTH_SHIFT)

/***************************************************************************/
/*
** Values that represent polarity of Field ID, Vblank, and Hblank are inverted
** respectively during raw capture
** Used in the invSet APIs
*/
#define VPIF_RAW_FID_INVERT                     (1 << VPIF_C0CTRL_FIDINV_SHIFT)
#define VPIF_RAW_VVALID_INVERT                  (1 << VPIF_C0CTRL_VVINV_SHIFT)
#define VPIF_RAW_HVALID_INVERT                  (1 << VPIF_C0CTRL_HVINV_SHIFT)

/***************************************************************************/
/*
** Values that represent storage mode of the data. 
** Used in the FieldframeModeSelect APIs of channel 2/0. However, setting on
** channel 2 will apply to channel 3, and setting on channel 0 will apply to
** channel 1.
*/
#define VPIF_FIELD_BASED                        (0 << VPIF_C0CTRL_FIELDFRAME_SHIFT)
#define VPIF_FRAME_BASED                        (1 << VPIF_C0CTRL_FIELDFRAME_SHIFT)

/***************************************************************************/
/*
** Values that represent format of the captured data
** Used in the VPIFCaptureIntrprogModeSelect API
*/
#define VPIF_CAPTURE_INTERLACED                 (0 << VPIF_C0CTRL_INTRPROG_SHIFT)
#define VPIF_CAPTURE_PROGRESSIVE                (1 << VPIF_C0CTRL_INTRPROG_SHIFT)
/***************************************************************************/
/*
** Values that represent format of the data to be displayed
** Used in the VPIFDisplayIntrprogModeSelect API
*/
#define VPIF_DISPLAY_INTERLACED                 (0 << VPIF_C2CTRL_INTRPROG_SHIFT)
#define VPIF_DISPLAY_PROGRESSIVE                (1 << VPIF_C3CTRL_INTRPROG_SHIFT)

/***************************************************************************/
/*
** Values that represent when frame interrupt occurs and sent to the CPU (in interlaced mode)
** Used in the IntframeConfig APIs of all channels
*/
 /* Interrupt occurs after top field is captured/displayed */
#define VPIF_FRAME_INTERRUPT_TOP                (0 << VPIF_C0CTRL_INTFRAME_SHIFT)
 /* Interrupt occurs after bottom field is captured/displayed */
#define VPIF_FRAME_INTERRUPT_BOTTOM             (1 << VPIF_C0CTRL_INTFRAME_SHIFT)
 /* Interrupt occurs after either field is captured/displayed */
#define VPIF_FRAME_INTERRUPT_TOP_BOTTOM         (2 << VPIF_C0CTRL_INTFRAME_SHIFT)

/***************************************************************************/
/*
** Values that represent the particular field being processed (in interlaced mode)
** Value read in the FidModeRead APIs of all channels 
*/
#define VPIF_FIELD_IDENTIFICATION_TOP           (0 << VPIF_C0CTRL_FID_SHIFT)
#define VPIF_FIELD_IDENTIFICATION_BOTTOM        (1 << VPIF_C0CTRL_FID_SHIFT)

/***************************************************************************/
/*
** Values that represent the data format
** Value used in the YcmuxModeSelect APIs of all channels 
*/
 /* Y & C data are non-muxed, parallel over a 16-bit bus */
#define VPIF_YC_NONMUXED                        (0 << VPIF_C0CTRL_YCMUX_SHIFT)
 /* Y & C data are muxed over a 8-bit bus */
#define VPIF_YC_MUXED                           (1 << VPIF_C0CTRL_YCMUX_SHIFT)

/***************************************************************************/
/*
** Values that represent the capture mode. 
** (Raw w/ external sync, or BT w/ embedded sync)
** Value used in the VPIFCaptureCapmodeModeSelect API
*/
#define VPIF_CAPTURE_BT                         (0 << VPIF_C0CTRL_CAPMODE_SHIFT)
#define VPIF_CAPTURE_RAW                        (1 << VPIF_C0CTRL_CAPMODE_SHIFT)

/***************************************************************************/
/*
** Structures and Variables
*/

/***************************************************************************/
/*
** The elements of the vbufParam structure defines the structures of a video frame
** Used mainly in nonstandard BT mode.
*/
typedef struct vbufParam
{
    unsigned int sav2eav;
    unsigned int eav2sav;
    unsigned int vsize;
    unsigned int l1;
    unsigned int l3;    
    unsigned int l5;
    unsigned int l7;
    unsigned int l9;
    unsigned int l11;
} VPIFVbufParam;

/***************************************************************************/
/*
** Function Prototypes
*/
extern void VPIFErrorStatusClear(unsigned int baseAddr, unsigned int err);
extern unsigned int VPIFErrorStatus(unsigned int baseAddr, unsigned int err);
extern void VPIFDMARequestSizeConfig(unsigned int baseAddr, unsigned int size);
extern void VPIFEmulationControlSet(unsigned int baseAddr, unsigned int mode);
extern void VPIFInterruptEnable(unsigned int baseAddr, unsigned int intr);
extern void VPIFInterruptDisable(unsigned int baseAddr, unsigned int intr);
extern void VPIFInterruptEnableSet(unsigned int baseAddr, unsigned int intr);
extern void VPIFInterruptEnableClear(unsigned int baseAddr, unsigned int intr);
extern void VPIFInterruptStatusClear(unsigned int baseAddr, unsigned int intr);
extern unsigned int VPIFInterruptStatus(unsigned int baseAddr, unsigned int intr);

/* C0CTRL & C1CTRL */
extern void VPIFCaptureClkedgeModeSelect(unsigned int baseAddr, unsigned int channel, unsigned int mode);
extern void VPIFCaptureRawDatawidthConfig(unsigned int baseAddr, unsigned int width); 
extern void VPIFCaptureRawIntlineConfig(unsigned int baseAddr, unsigned int interval);
extern void VPIFCaptureRawFidinvSet(unsigned int baseAddr, unsigned int mode);
extern void VPIFCaptureRawVvinvSet(unsigned int baseAddr, unsigned int mode);
extern void VPIFCaptureRawHvinvSet(unsigned int baseAddr, unsigned int mode);
extern void VPIFCaptureFieldframeModeSelect(unsigned int baseAddr, unsigned int mode);
extern void VPIFCaptureIntrprogModeSelect(unsigned int baseAddr, unsigned int channel, unsigned int mode);
extern void VPIFCaptureVancEnable(unsigned int baseAddr, unsigned int channel);
extern void VPIFCaptureVancDisable(unsigned int baseAddr, unsigned int channel);
extern void VPIFCaptureHancEnable(unsigned int baseAddr, unsigned int channel);
extern void VPIFCaptureHancDisable(unsigned int baseAddr, unsigned int channel);
extern void VPIFCaptureIntframeConfig(unsigned int baseAddr, unsigned int channel, unsigned int mode);
extern unsigned int VPIFCaptureFidModeRead(unsigned int baseAddr, unsigned int channel);
extern void VPIFCaptureYcmuxModeSelect(unsigned int baseAddr, unsigned int channel, unsigned int mode);
extern void VPIFCaptureCapmodeModeSelect(unsigned int baseAddr, unsigned int channel, unsigned int mode);
extern void VPIFCaptureChanenEnable(unsigned int baseAddr, unsigned int channel);
extern void VPIFCaptureChanenDisable(unsigned int baseAddr, unsigned int channel);

extern void VPIFCaptureVBIFBConfig(unsigned int baseAddr, unsigned int channel, unsigned field, unsigned hv, unsigned int addr, unsigned int offset);
extern unsigned int VPIFCaptureVBIFBExchange(unsigned int baseAddr, unsigned int channel, unsigned field, unsigned hv, unsigned int addr, unsigned int offset);
extern void VPIFCaptureModeConfig(unsigned int baseAddr, unsigned int mode, unsigned int sdChannel, unsigned int rawWidth, VPIFVbufParam* buf);
extern void VPIFCaptureFBConfig(unsigned int baseAddr, unsigned int channel, unsigned int field, unsigned yc, unsigned int addr, unsigned int offset);
extern unsigned int VPIFCaptureFBExchange(unsigned int baseAddr, unsigned int channel, unsigned int field, unsigned yc, unsigned int addr, unsigned int offset);

/* C2CTRL & C3CTRL */
extern void VPIFDisplayClkedgeModeSelect(unsigned int baseAddr, unsigned int channel, unsigned int mode);
extern void VPIFDisplayClipancEnable(unsigned int baseAddr, unsigned int channel); 
extern void VPIFDisplayClipancDisable(unsigned int baseAddr, unsigned int channel); 
extern void VPIFDisplayClipvidEnable(unsigned int baseAddr, unsigned int channel); 
extern void VPIFDisplayClipvidDisable(unsigned int baseAddr, unsigned int channel); 
extern void VPIFDisplayFieldframeModeSelect(unsigned int baseAddr, unsigned int mode);
extern void VPIFDisplayIntrprogModeSelect(unsigned int baseAddr, unsigned int channel, unsigned int mode);
extern void VPIFDisplayPixelEnable(unsigned int baseAddr, unsigned int channel); 
extern void VPIFDisplayPixelDisable(unsigned int baseAddr, unsigned int channel); 
extern void VPIFDisplayVancEnable(unsigned int baseAddr, unsigned int channel);
extern void VPIFDisplayVancDisable(unsigned int baseAddr, unsigned int channel);
extern void VPIFDisplayHancEnable(unsigned int baseAddr, unsigned int channel);
extern void VPIFDisplayHancDisable(unsigned int baseAddr, unsigned int channel);
extern void VPIFDisplayIntframeConfig(unsigned int baseAddr, unsigned int channel, unsigned int mode);
extern unsigned int VPIFDisplayFidModeRead(unsigned int baseAddr, unsigned int channel);
extern void VPIFDisplayYcmuxModeSelect(unsigned int baseAddr, unsigned int channel, unsigned int mode);
extern void VPIFDisplayClkenEnable(unsigned int baseAddr, unsigned int channel); 
extern void VPIFDisplayClkenDisable(unsigned int baseAddr, unsigned int channel);
extern void VPIFDisplayChanenEnable(unsigned int baseAddr, unsigned int channel);
extern void VPIFDisplayChanenDisable(unsigned int baseAddr, unsigned int channel);

extern void VPIFDisplayVBIFBConfig(unsigned int baseAddr, unsigned int channel, unsigned field, unsigned hv, unsigned int addr, unsigned int offset);
extern unsigned int VPIFDisplayVBIFBExchange(unsigned int baseAddr, unsigned int channel, unsigned field, unsigned hv, unsigned int addr, unsigned int offset);
extern void VPIFDisplayVBIFBSizeConfig(unsigned int baseAddr, unsigned int channel, unsigned field, unsigned hv, unsigned int vpos, unsigned int hpos, unsigned int vsize, unsigned int hsize);
extern void VPIFDisplayModeConfig(unsigned int baseAddr, unsigned int mode, unsigned int sdChannel, VPIFVbufParam* buf);
extern void VPIFDisplayFBConfig(unsigned int baseAddr, unsigned int channel, unsigned int field, unsigned yc, unsigned int addr, unsigned int offset);
extern unsigned int VPIFDisplayFBExchange(unsigned int baseAddr, unsigned int channel, unsigned int field, unsigned yc, unsigned int addr, unsigned int offset);

#ifdef __cplusplus
}
#endif
#endif
