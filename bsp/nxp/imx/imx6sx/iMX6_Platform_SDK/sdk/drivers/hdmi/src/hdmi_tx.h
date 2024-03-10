/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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

#ifndef __HDMI_COMMON_H__
#define __HDMI_COMMON_H__

#include "sdk.h"

//! @addtogroup diag_hdmi
//! @{

//////////////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////////////

//! @brief Enumeration of variable pixel format for HDMI transmitter
enum hdmi_datamap {
    RGB444_8B = 0x01,
    RGB444_10B = 0x03,
    RGB444_12B = 0x05,
    RGB444_16B = 0x07,
    YCbCr444_8B = 0x09,
    YCbCr444_10B = 0x0B,
    YCbCr444_12B = 0x0D,
    YCbCr444_16B = 0x0F,
    YCbCr422_8B = 0x16,
    YCbCr422_10B = 0x14,
    YCbCr422_12B = 0x12,
};

//! @brief Enumeration of HDMI CSC encode format
enum hdmi_csc_enc_format {
    eRGB = 0x0,
    eYCC444 = 0x01,
    eYCC422 = 0x2,
    eExtended = 0x3,
};

//! @brief HDMI colorimetry defined by ITU
enum hdmi_colorimetry {
    eITU601,
    eITU709,
};

//! @brief HDMI video mode structure
//
//! this is used to set the timming of HDMI output
//! must follow the VESA standard or EDID information embedded in the display
typedef struct hdmi_vmode {
    unsigned int mCode;
    unsigned int mHdmiDviSel;
    unsigned int mRVBlankInOSC;
    unsigned int mRefreshRate;
    unsigned int mHImageSize;
    unsigned int mVImageSize;
    unsigned int mHActive;
    unsigned int mVActive;
    unsigned int mHBlanking;
    unsigned int mVBlanking;
    unsigned int mHSyncOffset;
    unsigned int mVSyncOffset;
    unsigned int mHSyncPulseWidth;
    unsigned int mVSyncPulseWidth;
    unsigned int mHSyncPolarity;
    unsigned int mVSyncPolarity;
    unsigned int mDataEnablePolarity;
    unsigned int mInterlaced;
    unsigned int mPixelClock;
    unsigned int mHBorder;
    unsigned int mVBorder;
    unsigned int mPixelRepetitionInput;
} hdmi_vmode_s;

//! @brief HDMI input and output data information
typedef struct hdmi_data_info {
    unsigned int enc_in_format;
    unsigned int enc_out_format;
    unsigned int enc_color_depth;
    unsigned int colorimetry;
    unsigned int pix_repet_factor;
    unsigned int hdcp_enable;
    hdmi_vmode_s *video_mode;
} hdmi_data_info_s;

//! @brief HDMI audio params
typedef struct hdmi_AudioParam {
    unsigned char IecCgmsA;
    int IecCopyright;
    unsigned char IecCategoryCode;
    unsigned char IecPcmMode;
    unsigned char IecSourceNumber;
    unsigned char IecClockAccuracy;
    unsigned int OriginalSamplingFrequency;
    unsigned char ChannelAllocation;
    unsigned int SamplingFrequency;
    unsigned char SampleSize;
} hdmi_audioparam_s;

//! @brief Enumeration of HDMI audio data codec format
typedef enum {
    PCM = 1,
    AC3,
    MPEG1,
    MP3,
    MPEG2,
    AAC,
    DTS,
    ATRAC,
    ONE_BIT_AUDIO,
    DOLBY_DIGITAL_PLUS,
    DTS_HD,
    MAT,
    DST,
    WMAPRO
} codingType_t;

//! @brief Enumeration of HDMI data packet type
typedef enum {
    AUDIO_SAMPLE = 1,
    HBR_STREAM
} packet_t;

//! @brief HDMI DMA access type
typedef enum {
    DMA_4_BEAT_INCREMENT = 0,
    DMA_8_BEAT_INCREMENT,
    DMA_16_BEAT_INCREMENT,
    DMA_UNUSED_BEAT_INCREMENT,
    DMA_UNSPECIFIED_INCREMENT
} dmaIncrement_t;

//! @brief HDMI audio params
typedef struct {
    codingType_t mCodingType; /** (audioParams_t *params, see InfoFrame) */

    unsigned char mChannelAllocation;
                                    /** channel allocation (audioParams_t *params, 
						   see InfoFrame) */
    unsigned char mSampleSize;
                             /**  sample size (audioParams_t *params, 16 to 24) */

    unsigned int mSamplingFrequency;
                                   /** sampling frequency (audioParams_t *params, Hz) */

    unsigned char mLevelShiftValue;
                                  /** level shift value (audioParams_t *params, 
						 see InfoFrame) */
    unsigned char mDownMixInhibitFlag;
                                     /** down-mix inhibit flag (audioParams_t *params, 
							see InfoFrame) */
    unsigned int mOriginalSamplingFrequency; /** Original sampling frequency */
    unsigned char mIecCopyright; /** IEC copyright */
    unsigned char mIecCgmsA; /** IEC CGMS-A */
    unsigned char mIecPcmMode; /** IEC PCM mode */
    unsigned char mIecCategoryCode; /** IEC category code */
    unsigned char mIecSourceNumber; /** IEC source number */
    unsigned char mIecClockAccuracy; /** IEC clock accuracy */
    packet_t mPacketType; /** packet type. currently only Audio Sample (AUDS) 
						  and High Bit Rate (HBR) are supported */
    unsigned short mClockFsFactor; /** Input audio clock Fs factor used at the audop 
						packetizer to calculate the CTS value and ACR packet
						insertion rate */
    dmaIncrement_t mDmaBeatIncrement; /** Incremental burst modes: unspecified
									lengths (upper limit is 1kB boundary) and
									INCR4, INCR8, and INCR16 fixed-beat burst */
    unsigned char mDmaThreshold; /** When the number of samples in the Audio FIFO is lower
						than the threshold, the DMA engine requests a new burst
						request to the AHB master interface */
    unsigned char mDmaHlock; /** Master burst lock mechanism */
} audioParams_t;

//////////////////////////////////////////////////////////////////////////////
// API
//////////////////////////////////////////////////////////////////////////////

/*!
 * @brief This submodule is responsible for the video/audio data composition
 *
 * @param vmode Video mode parameters
 */
void hdmi_set_video_mode(hdmi_vmode_s * vmode);

/*!
 * @brief Check if color space conversion is needed
 *
 * @param hdmi_instance HDMI instance information containing all the parameters 
 * of input and output
 */
int isColorSpaceConversion(hdmi_data_info_s hdmi_instance);

/*!
 * @brief Check if color space decimition is needed
 *
 * @param hdmi_instance HDMI instance information containing all the parameters 
 * of input and output
 */
int isColorSpaceDecimation(hdmi_data_info_s hdmi_instance);

/*!
 * @brief Check if color space interpolation is needed
 *
 * @param hdmi_instance HDMI instance information containing all the parameters 
 * of input and output
 */
int isColorSpaceInterpolation(hdmi_data_info_s hdmi_instance);

/*!
 * @brief Check if pixel repetition is needed
 *
 * @param hdmi_instance HDMI instance information containing all the parameters 
 * of input and output
 */
int isPixelRepetition(hdmi_data_info_s hdmi_instance);

/*! 
 * @brief program the input source mux for the hdmi input
 * this is set up in IOMUXC_GPR3 register
 * 
 * @param mux_value HDMI input source slection between the mux options
 */
void hdmi_config_input_source(uint32_t mux_value);

/*!
 * @brief This is responsible for the video data synchronization.
 * for example, for RGB 4:4:4 input, the data map is defined as
 * 			pin{47~40} <==> R[7:0]
 * 			pin{31~24} <==> G[7:0]
 * 			pin{15~8}  <==> B[7:0]
 *
 * @param hdmi_instance Instance of the HDMI
 */
void hdmi_video_sample(hdmi_data_info_s hdmi_instance);

/*!
 * @brief Update the color space conversion coefficients.
 *
 * @param hdmi_instance Instance of the HDMI
 */
void update_csc_coeffs(hdmi_data_info_s hdmi_instance);

/*!
 * @brief Set HDMI color space conversion module.
 *
 * @param hdmi_instance Instance of the HDMI
 */
void hdmi_video_csc(hdmi_data_info_s hdmi_instance);

/*!
 * @brief HDMI video packetizer is used to packetize the data.
 * for example, if input is YCC422 mode or repeater is used, data should be repacked
 * this module can be bypassed.
 *
 * @param hdmi_instance Instance of the HDMI
 */
void hdmi_video_packetize(hdmi_data_info_s hdmi_instance);

/*!
 * @brief Preamble filter setting. this is used to indicate whether the 
 * upcoming data period is a VDP(video data period) or DI(data island)
 *
 * @param	value Data value for configuration
 * @param	channel Channel number, 0~2
 */
void preamble_filter_set(uint8_t value, uint8_t channel);

/*!
 * @brief This function is responsible for the video/audio data composition.
 * video mode is set here, but the actual flow is determined by the input.
 *
 * @param hdmi_instance Instance of the HDMI
 */
void hdmi_av_frame_composer(hdmi_data_info_s * hdmi_instance);

/*!
 * @brief Mute or un-mute the audio of HDMI output
 *
 * @param en Enable or Disable
 * @return TRUE
 */
uint32_t hdmi_audio_mute(uint32_t en);

/*!
 * @brief Get the audio channel count according to the channel allocation
 *
 * @param mChannelAllocation Channel allocation for audio
 * @return channel numbers
 */
uint8_t Audio_ChannelCount(uint8_t mChannelAllocation);

/*!
 * @brief Audio information configuration
 */
void audio_info_config(void);

/*!
 * @brief Configure the audio submodule
 *
 * @param hdmi_audioparam_insttance Audio instance containing all the parameters
 * @param pixelClk HDMI output pixel clock
 * @param ratioClk Ratio clock
 * @return TRUE
 */
int audio_Configure(hdmi_audioparam_s hdmi_audioparam_instance, uint16_t pixelClk,
                    unsigned ratioClk);

/*!
 * @brief Configure the audio DMA
 *
 * @param startAddr Transfer start address
 * @param stopAddr Transfer stop address
 * @param hlockEn Lock enable bit
 * @param incrType DMA addressing increment type
 * @param audioChnl Audio channle
 * @param intMask Interrupt mask
 */
void audio_Configure_DMA(uint32_t startAddr, uint32_t stopAddr, uint8_t hlockEn, uint8_t incrType,
                         uint8_t threshold, uint32_t audioChnl, uint8_t intMask);

/*!
 * @brief HDCP configuration, disabled here
 *
 * @param de Data enable polarity
 */
void hdmi_tx_hdcp_config(uint32_t de);

/*!
 * @brief HDMI phy initialization
 *
 * @param	de Data enable polarity, 1 for positive and 0 for negative
 * @param	pclk Pixel clock
 */
void hdmi_phy_init(uint8_t de, uint16_t pclk);

/*!
 * @brief Force the HDMI video output to be fixed value! from FC_DBGTMDSx registers
 * 
 * @param force True/false or enable/disable, if true enabled force video setting, if false disable it
 */
void hdmi_config_force_video(uint8_t force);

/*! 
 * configure the RGB pixel settings to be used when fixed video mode is enabled
 * 
 * @param red Pixel settings for red component.
 * @param green Pixel settings for green component.
 * @param blue Pixel settings for blue component.
 */
void hdmi_config_forced_pixels(uint8_t red, uint8_t green, uint8_t blue);

//! @}

#endif

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
