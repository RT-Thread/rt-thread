#ifndef _I2S_CONFIG_H
#define _I2S_CONFIG_H

#define I2S_ADUIO_PLL_DEFAULT AUDIO_PLL_12288000_HZ
#define I2S_DATA_ENDIAN       I2S_DATA_ENDIAN_MSB
#define I2S_MONO_CHANNEL      I2S_RX_MONO_MODE_LEFT_CHANNEL
#define I2S_LR_EXCHANGE       DISABLE /*The position of L/R channel data within each entry is exchanged if enabled*/
#define I2S_FS_INVERT         DISABLE
#define I2S_BCLK_INVERT       DISABLE

#endif