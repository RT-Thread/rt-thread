/*!
*******************************************************************************
**
** \file      gd_audio.h
**
** \brief     audio.
**
**            Copyright:   2012 - 2013 (C) GoKe Microelectronics ShangHai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \note      Do not modify this file as it is generated automatically.
**
******************************************************************************/
#ifndef _GD_AUDIO_H_
#define _GD_AUDIO_H_

#include "gmodids.h"

#define GD_AUDIO_ERR_BASE   (GD_AUDIO_MODULE_ID << 16)


/*!
*******************************************************************************
**
** \brief I2S driver error codes.
**
*******************************************************************************
*/
enum
{
    GD_ERR_AUDIO_NOT_SUPPORTED = GD_AUDIO_ERR_BASE, //!< Device not supported.
    GD_ERR_AUDIO_NOT_OPEN,
    GD_ERR_AUDIO_DEV_BUSY,
    GD_ERR_AUDIO_DEV_WAIT,
};

typedef enum  /* 2dB per level */
{
    GAIN_LEVEL_0,
    GAIN_LEVEL_1,
    GAIN_LEVEL_2,
    GAIN_LEVEL_3,
    GAIN_LEVEL_4,
    GAIN_LEVEL_5,
    GAIN_LEVEL_6,
    GAIN_LEVEL_7,
    GAIN_LEVEL_8,
    GAIN_LEVEL_9,
    GAIN_LEVEL_10,
    GAIN_LEVEL_11,
    GAIN_LEVEL_12,
    GAIN_LEVEL_13,
    GAIN_LEVEL_14,
    GAIN_LEVEL_15,
    GAIN_LEVEL_MAX,
}GD_AUDIO_GAIN_E;

typedef enum
{
    VOL_LEVEL_0  = 0xaf,
    VOL_LEVEL_1  = 0xad,
    VOL_LEVEL_2  = 0xab,
    VOL_LEVEL_3  = 0xa9,
    VOL_LEVEL_4  = 0xa7,
    VOL_LEVEL_5  = 0xa5,
    VOL_LEVEL_6  = 0xa3,
    VOL_LEVEL_7  = 0xa1,
    VOL_LEVEL_8  = 0xa0,
    VOL_LEVEL_9  = 0xbe,
    VOL_LEVEL_10 = 0xb9,
    VOL_LEVEL_11 = 0xb4,
    VOL_LEVEL_12 = 0xb0,
}GD_AUDIO_VOLUME_E;

typedef enum
{
    AUDIO_SOUND_MODE_LEFT   = 0,
    AUDIO_SOUND_MODE_RIGHT  = 1,
    AUDIO_SOUND_MODE_STEREO = 2,
    AUDIO_SOUND_MODE_MONO   = 3,
    AUDIO_SOUND_MODE_SINGLE = 4,
}GD_AUDIO_SOUND_MODE_E;

typedef enum
{
    AUDIO_SAMPLE_RATE_8000  = 8000,
    AUDIO_SAMPLE_RATE_11025 = 11025,
    AUDIO_SAMPLE_RATE_12000 = 12000,
    AUDIO_SAMPLE_RATE_16000 = 16000,
    AUDIO_SAMPLE_RATE_22050 = 22050,
    AUDIO_SAMPLE_RATE_24000 = 24000,
    AUDIO_SAMPLE_RATE_32000 = 32000,
    AUDIO_SAMPLE_RATE_44100 = 44100,
    AUDIO_SAMPLE_RATE_48000 = 48000,
}GD_AUDIO_SAMPLE_RATE_E;

typedef enum
{
    AUDIO_BIT_WIDTH_16 = 16,
}GD_AUDIO_BIT_WIDTH_E;

enum
{
	AUDIO_EVENT_FRAME          = 1, /* received one audio frame or send finished one audio frame */
    AUDIO_EVENT_WILL_OVERFLOW  = 2,
	AUDIO_EVENT_WILL_UNDERFLOW = 3,	
    AUDIO_EVENT_ALREADY_OVERFLOW  = 4,
	AUDIO_EVENT_ALREADY_UNDERFLOW = 5,	
	AUDIO_EVENT_UNDEFINED         = 6,
};

typedef void (*GD_AUDIO_Notifier)(U32 event);

typedef struct
{
    GD_AUDIO_SAMPLE_RATE_E         sampleRate;
    GD_AUDIO_SOUND_MODE_E          soundMode;
}GD_AUDIO_ATTR_S;

typedef struct
{
    GD_AUDIO_SAMPLE_RATE_E         sampleRate;
    GD_AUDIO_BIT_WIDTH_E           bitWidth;
    GD_AUDIO_SOUND_MODE_E          soundMode;
    U32                            sampleNumber;
	GD_AUDIO_Notifier              notifier;
}GD_AUDIO_OPEN_PARAM_S;


typedef struct
{
    GD_AUDIO_BIT_WIDTH_E      bitWidth;
    GD_AUDIO_SOUND_MODE_E     soundMode;
	GD_AUDIO_SAMPLE_RATE_E    sampleRate;
    U32                       frameAddr;
	U32                       frameSize;
    U32                       timeStamp;
    U32                       seqNumber;
	U32                       aecSeq;     /* audio echo cancellation seque number */
}GD_AUDIO_FRAME_S;



#ifdef __cplusplus
extern "C" {
#endif

GERR GD_AUDIO_Init(void);
GERR GD_AUDIO_Exit(void);
GERR GD_AUDIO_Bind_Ai2Ao(void);
GERR GD_AUDIO_Unbind_Ai2Ao(void);
GERR GD_AUDIO_AI_Open(GD_AUDIO_OPEN_PARAM_S *openParamPtr);
GERR GD_AUDIO_AI_Close(void);
GERR GD_AUDIO_AI_Enable(void);
GERR GD_AUDIO_AI_Disable(void);
GERR GD_AUDIO_AI_Read_Frame(GD_AUDIO_FRAME_S *frame);
GERR GD_AUDIO_AI_Set_Attr(GD_AUDIO_ATTR_S *pattr);
GERR GD_AUDIO_AI_Get_Attr(GD_AUDIO_ATTR_S *pattr);
GERR GD_AUDIO_AI_Set_Gain(GD_AUDIO_GAIN_E gain);
GD_AUDIO_GAIN_E GD_AUDIO_AI_Get_Gain(void);
GERR GD_AUDIO_AO_Open(GD_AUDIO_OPEN_PARAM_S *openParamPtr);
GERR GD_AUDIO_AO_Close(void);
GERR GD_AUDIO_AO_Enable(void);
GERR GD_AUDIO_AO_Disable(void);
GERR GD_AUDIO_AO_Write_Frame(GD_AUDIO_FRAME_S *frame);
GERR GD_AUDIO_AO_Set_Attr(GD_AUDIO_ATTR_S *pattr);
GERR GD_AUDIO_AO_Get_Attr(GD_AUDIO_ATTR_S *pattr);
GERR GD_AUDIO_AO_Set_Volume(GD_AUDIO_VOLUME_E volume);
GD_AUDIO_VOLUME_E GD_AUDIO_AO_Get_Volume(void);
GERR GD_AUDIO_AO_Mute(void);
GERR GD_AUDIO_AO_Unmute(void);
U32 GD_AUDIO_AI_Get_RecFrameNum(void);
U32 GD_AUDIO_AO_Get_RecFrameNum(void);


#ifdef __cplusplus
}
#endif



#endif /* _GD_AUDIO_H_ */


/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

