#ifndef PKG_AD7730_H__
#define PKG_AD7730_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
	Communication Register Values
*/
/* Read/Write Mode Bits */
#define CR_SINGLE_WRITE 0x00 // Single Write to Specified Register
#define CR_SINGLE_READ 0x10 // Single Read of Specified Register
#define CR_CONTINUOUS_READ_START 0x20 // Start Continuous Read of Specified Register
#define CR_CONTINUOUS_READ_STOP 0x30 // Stop Continuous Read Mode

/* Register Selection Bits */
#define CR_COMMUNICATION_REGISTER 0x00 // Communications Register (Write Operation) 8Bits
#define CR_STATUS_REGISTER 0x00 // Status Register (Read Operation) 8Bits
#define CR_DATA_REGISTER 0x01 // Data Register 16/24bit(WL=1)
#define CR_MODE_REGISTER 0x02 // Mode Register 16bit
#define CR_FILTER_REGISTER 0x03 // Filter Register 24bit
#define CR_DAC_REGISTER 0x04 // DAC Register 8bit
#define CR_OFFSET_REGISTER 0x05 // Offset Register 24bit
#define CR_GAIN_REGISTER 0x06 // Gain Register 24bit
#define CR_TEST_REGISTER 0x07 // Test Register 24bit

/*
	Mode Register Values
*/
#define MR1_MODE_IDLE 0x00 // Sync (Idle) Mode Power-On/Reset Default
#define MR1_MODE_CONTINUOUS 0x20 // Continuous Conversion Mode
#define MR1_MODE_SINGLE 0x40 // Single Conversion Mode
#define MR1_MODE_STANDBY 0x60 // Power-Down (Standby) Mode
#define MR1_MODE_INTERNAL_ZERO_CALIBRATION 0x80 // Internal Zero-Scale Calibration
#define MR1_MODE_INTERNAL_FULL_CALIBRATION 0xA0 // Internal Full-Scale Calibration
#define MR1_MODE_SYSTEM_ZERO_CALIBRATION 0xC0 // System Zero-Scale Calibration
#define MR1_MODE_SYSTEM_FULL_CALIBRATION 0xE0 // System Full-Scale Calibration
#define MR1_BU_BIPOLAR 0x00 // +- voltage defined by MR0_RANGE
#define MR1_BU_UNIPOLAR 0x10 // 0 to voltage deifined by MRO_RANGE
#define MR1_WL_24_BIT 0x01 // 16-bit word length when reading from the data register
#define MR1_WL_16_BIT 0x00 // 24-bit word length when reading from the data register

#define MR0_HIREF_5V 0x80 // High Reference Bit(5V)
#define MR0_HIREF_2P5V 0x00 // High Reference Bit(2.5V)
#define MR0_RANGE_10MV 0x00 // Input Range Bits(0-10mv or +-10mv)
#define MR0_RANGE_20MV 0x10 // Input Range Bits(0-20mv or +-20mv)
#define MR0_RANGE_40MV 0x20 // Input Range Bits(0-40mv or +-40mv)
#define MR0_RANGE_80MV 0x30 // Input Range Bits(0-80mv or +-80mv)
#define MR0_CHANNEL_1 0x00 // Channel Selection Bits(CH1)
#define MR0_CHANNEL_2 0x01 // Channel Selection Bits(CH2)
#define MR0_CHANNEL_SHORT_1 0x02 // Used for internal noise check
#define MR0_CHANNEL_NEGATIVE_1_2 0x03 // Unknown use
#define MRO_BURNOUT_ON 0x04 // Advanced, to check if loadcell is burnt out

/* 
	Filter Register (RS2-RS0 = 0, 1, 1); Power-On/Reset Status: 200010 Hex 
*/
#define FR2_SINC_AVERAGING_2048 0x80  //Base sample rate of 50 Hz
#define FR2_SINC_AVERAGING_1024 0x40  //Base sample rate of 100 Hz
#define FR2_SINC_AVERAGING_512 0x20   //Base sample rate of 200 Hz
#define FR2_SINC_AVERAGING_256 0x10   //Base sample rate of 400 Hz

#define FR1_SKIP_ON 0x02 //the FIR filter on the part is bypassed
#define FR1_SKIP_OFF 0x00
#define FR1_FAST_ON 0x01 //FIR is replaced with moving average on large step, sinc filter averages are used to compensate
#define FR1_FAST_OFF 0x00

#define FR0_AC_ON 0x20 //AC Excitation Bit. If the signal source to the AD7730 is ac-excited, a 1 must be placed in this bit
#define FR0_AC_OFF 0x00

#define FR0_CHOP_ON 0x10 //When the chop mode is enabled, the part is effectively chopped at its input and output to remove all offset and offset drift errors on the part.
#define FR0_CHOP_OFF 0x00 //Increases sample rate by x3

/*
	Delay Selection Bits. These four bits program the delay (in modulator cycles) to be inserted after each chop edge when the CHP bit is 1.
	One modulator cycle is MCLK IN/16 and is 3.25us at MCLK IN = 4.9152 MHz. A delay should only be required when in ac mode. Its purpose is to
	cater for external delays between the switching signals (ACX and ACX) and when the analog inputs are actually switched and settled.
*/
#define FR0_DL_0 0x00 // 0us
#define FR0_DL_1 0x01 // 3.25us
#define FR0_DL_2 0x02 // 6.5us
#define FR0_DL_3 0x03 // 9.75us
#define FR0_DL_4 0x04 // 13us
#define FR0_DL_5 0x05 // 16.25us
#define FR0_DL_6 0x06 // 19.5us
#define FR0_DL_7 0x07 // 22.75us
#define FR0_DL_8 0x08 // 26us
#define FR0_DL_9 0x09 // 29.25us
#define FR0_DL_10 0x0A // 32.5us
#define FR0_DL_11 0x0B // 35.75us
#define FR0_DL_12 0x0C // 39us
#define FR0_DL_13 0x0D // 42.25us
#define FR0_DL_14 0x0E // 45.5us
#define FR0_DL_15 0x0F // 48.75us

/* 
	DAC Register (RS2–RS0 = 1, 0, 0); Power On/Reset Status: 20 Hex,
	for a 5 V reference applied across the REF IN pins, the DAC resolution is 2.5 mV
 */
#define DACR_OFFSET_SIGN_POSITIVE 0x00 // +
#define DACR_OFFSET_SIGN_NEGATIVE 0x20 // -
#define DACR_OFFSET_77P5MV 	0x1F // 77.5mv
#define DACR_OFFSET_75MV 	0x1E // 75mv
#define DACR_OFFSET_72P5MV 	0x1D // 72.5mv
#define DACR_OFFSET_70MV 	0x1C // 70mv
#define DACR_OFFSET_67P5MV 	0x1B // 67.5mv
#define DACR_OFFSET_65MV 	0x1A // 65mv
#define DACR_OFFSET_62P5MV 	0x19 // 62.5mv
#define DACR_OFFSET_60MV 	0x18 // 60mv
#define DACR_OFFSET_57P5MV 	0x17 // 57.5mv
#define DACR_OFFSET_55MV 	0x16 // 55mv
#define DACR_OFFSET_52P5MV 	0x15 // 52.5mv
#define DACR_OFFSET_50MV 	0x14 // 50mv
#define DACR_OFFSET_47P5MV 	0x13 // 47.5mv
#define DACR_OFFSET_45MV 	0x12 // 45mv
#define DACR_OFFSET_42P5MV 	0x11 // 42.5mv
#define DACR_OFFSET_40MV 	0x10 // 40mv
#define DACR_OFFSET_37P5MV 	0x0F // 37.5mv
#define DACR_OFFSET_35MV 	0x0E // 35mv
#define DACR_OFFSET_32P5MV 	0x0D // 32.5mv
#define DACR_OFFSET_30MV 	0x0C // 30mv
#define DACR_OFFSET_27P5MV 	0x0B // 27.5mv
#define DACR_OFFSET_25MV 	0x0A // 25mv
#define DACR_OFFSET_22P5MV 	0x09 // 22.5mv
#define DACR_OFFSET_20MV 	0x08 // 20mv
#define DACR_OFFSET_17P5MV 	0x07 // 17.5mv
#define DACR_OFFSET_15MV 	0x06 // 15mv
#define DACR_OFFSET_12P5MV 	0x05 // 12.5mv
#define DACR_OFFSET_10MV 	0x04 // 10mv
#define DACR_OFFSET_7P5MV 	0x03 // 7.5mv
#define DACR_OFFSET_5MV 	0x02 // 5mv
#define DACR_OFFSET_2P5MV 	0x01 // 2.5mv
#define DACR_OFFSET_NONE 	0x00 // 0mv

//current settings
#define CURRENT_MODE_1_SETTINGS_CAL (MR1_BU_BIPOLAR | MR1_WL_24_BIT)
#define CURRENT_MODE_0_SETTINGS_CAL_FULL (MR0_HIREF_5V | MR0_RANGE_80MV) // datasheet recommends calibrating with 80mV range regardless
#define CURRENT_MODE_0_SETTINGS_CAL_ZERO (MR0_HIREF_5V | MR0_RANGE_20MV) // This zero-scale calibration should be performed at the operating input range

#define CURRENT_MODE_1_SETTINGS_READ (MR1_BU_BIPOLAR | MR1_WL_24_BIT)
#define CURRENT_MODE_0_SETTINGS_READ (MR0_HIREF_5V | MR0_RANGE_20MV)

enum ad7730_state
{
	AD7730_IDLE = 0,
	AD7730_SINGLE_READ,
	AD7730_CONT_READ
};

struct ad7730_device
{
    /* inherit from rt_device */
    struct rt_device parent;

    /* spi device */
    struct rt_spi_device* spi_device;
	/* rdy pin */
	rt_base_t rdy_pin;
	/* standby pin */
	rt_base_t standby_pin;
	/* reset pin */
	rt_base_t reset_pin;
	/* ref_sleep pin */
	rt_base_t ref_sleep_pin;
	/* read mode */
	volatile enum ad7730_state work_state;
	/* lock */
	struct rt_mutex lock;
};

#define AD7730_DEVICE_NAME "ad7730"

/* rt_device_control cmd code */
#define AD7730_DUMP_REG (0x01)
#define AD7730_START_CONT_READ (0x02)
#define AD7730_STOP_CONT_READ (0x03)
#define AD7730_START_SINGLE_READ (0x04)
#define AD7730_DO_CALIBRATION (0x05)

#ifdef __cplusplus
}
#endif

#endif
