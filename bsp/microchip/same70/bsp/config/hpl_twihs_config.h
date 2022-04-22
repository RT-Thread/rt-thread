/* Auto-generated config file hpl_twihs_config.h */
#ifndef HPL_TWIHS_CONFIG_H
#define HPL_TWIHS_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

#include <peripheral_clk_config.h>

/* TWI0 peripheral clock frequency */
#ifndef CONF_TWIHS0_FREQUENCY
#define CONF_TWIHS0_FREQUENCY (CONF_TWIHS0_FREQUENCY)
#endif

// <h> Standard configuration

// <o> I2C Bus clock speed (Hz) <1-400000>
// <i> I2C Bus clock (SCL) speed measured in Hz
// <id> i2c_master_baud_rate
#ifndef CONF_TWIHS0_BAUD
#define CONF_TWIHS0_BAUD 100000
#endif

// </h>

// <e> Advanced configuration
// <id> i2c_master_advanced
#ifndef CONF_TWIHS0_ADVANCED_CONFIG
#define CONF_TWIHS0_ADVANCED_CONFIG 1
#endif

// <q> SMBus Mode Enabled
// <i> Determine if the SMBus mode enabled
// <id> i2c_master_smbus_enable
#ifndef CONF_TWIHS0_SMBEN
#define CONF_TWIHS0_SMBEN 0
#endif

// <q> Packet Error Checking
// <i> SMBus PEC (CRC) generation and check enabled
// <id> i2c_master_packet_error_check
#ifndef CONF_TWIHS0_PECEN
#define CONF_TWIHS0_PECEN 0
#endif

// <o> SMBus Clock Prescaler
// <0=> Divide by 2
// <1=> Divide by 4
// <2=> Divide by 8
// <3=> Divide by 16
// <4=> Divide by 32
// <5=> Divide by 64
// <6=> Divide by 128
// <7=> Divide by 256
// <8=> Divide by 512
// <9=> Divide by 1024
// <10=> Divide by 2048
// <11=> Divide by 4096
// <12=> Divide by 8192
// <13=> Divide by 16384
// <14=> Divide by 32768
// <15=> Divide by 65536
// <i> Used to specify how to prescale the TLOWS, TLOWM and THMAX counters in SMBTR
// <id> i2c_master_smbus_clock_prescaler
#ifndef CONF_TWIHS0_SMBTR_PRESC
#define CONF_TWIHS0_SMBTR_PRESC 0
#endif

// <o> Master Clock Stretch Maximum Cycles <0-255>
// <i> Clock cycles in master maximum clock stretch count. Prescaled by PRESC.
// <i> Used to time TLOW:MEXT. If 0, timeout check disabled.
// <id> i2c_master_tlow_mext
#ifndef CONF_TWIHS0_SMBTR_TLOWM
#define CONF_TWIHS0_SMBTR_TLOWM 0
#endif

// <o> Slave Clock Stretch Maximum Cycles <0-255>
// <i> Clock cycles in slave maximum clock stretch count. Prescaled by PRESC.
// <i> Used to time TLOW:SEXT. If 0, timeout check disabled.
// <id> i2c_master_tlow_sext
#ifndef CONF_TWIHS0_SMBTR_TLOWS
#define CONF_TWIHS0_SMBTR_TLOWS 0
#endif

// <o> Clock High Maximum Cycles <0-255>
// <i> Clock cycles in clock high maximum count. Prescaled by PRESC. Used for
// <i> bus free detection. Used to time THIGH:MAX.
// <id> i2c_master_thigh_max
#ifndef CONF_TWIHS0_SMBTR_THMAX
#define CONF_TWIHS0_SMBTR_THMAX 0
#endif

// <q> RX Digital Filter Enable
// <i> TWIHS input filtering is active (only in Standard and Fast modes)
// <id> i2c_master_digital_filter_enable
#ifndef CONF_TWIHS0_FILTR_FILT
#define CONF_TWIHS0_FILTR_FILT 1
#endif

// <q> PAD Filter Enable
// <i> PAD analog filter is enabled (The analog filter must be enabled if High-speed mode is enabled)
// <id> i2c_master_pad_filter_enable
#ifndef CONF_TWIHS0_FILTR_PADFEN
#define CONF_TWIHS0_FILTR_PADFEN 1
#endif

// <o> Digital Filter Threshold
// <0=> Disabled
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <6=> 7
// <i> Maximum pulse width of spikes to be suppressed by the input filter, defined in peripheral clock cycles.
// <id> i2c_master_filter_threshold
#ifndef CONF_TWIHS0_FILTR_THRES
#define CONF_TWIHS0_FILTR_THRES 2
#endif

// </e>

/* Configuration for CR (Control Register) */
#ifndef CONF_TWIHS0_CR_REG
#define CONF_TWIHS0_CR_REG                                                                                             \
	(TWIHS_CR_SVDIS | (CONF_TWIHS0_SMBEN << TWIHS_CR_SMBEN_Pos) | (CONF_TWIHS0_PECEN << TWIHS_CR_PECEN_Pos))
#endif

/* Configuration for SMBTR(TWI SMBus Timing Register Register) */
#ifndef CONF_TWIHS0_SMBTR_REG
#define CONF_TWIHS0_SMBTR_REG                                                                                          \
	((CONF_TWIHS0_SMBTR_PRESC << TWIHS_SMBTR_PRESC_Pos) | (CONF_TWIHS0_SMBTR_TLOWM << TWIHS_SMBTR_TLOWM_Pos)           \
	 | (CONF_TWIHS0_SMBTR_TLOWS << TWIHS_SMBTR_TLOWS_Pos) | (CONF_TWIHS0_SMBTR_THMAX << TWIHS_SMBTR_THMAX_Pos))
#endif

/* Configuration for FILTR(TWI Filter Register Register) */
#ifndef CONF_TWIHS0_FILTR_REG
#define CONF_TWIHS0_FILTR_REG                                                                                          \
	((CONF_TWIHS0_FILTR_FILT << TWIHS_FILTR_FILT_Pos) | (CONF_TWIHS0_FILTR_PADFEN << TWIHS_FILTR_PADFEN_Pos)           \
	 | (CONF_TWIHS0_FILTR_THRES << TWIHS_FILTR_THRES_Pos))
#endif

/* The peripheral clock is the source clock for the bit rate generation when
 * CONF_TWIHS0_CWGR_BRSRCCLK == 0
 *                 1          (CLDIV * CKDIV_val + 3)
 * Tlow = --------------- = ------------------------------
 *         baudrate * 2       PeripheralFrequency(HZ)
 */
#define CONF_TWIHS0_CWGR_CLDIV_CALC(freq, baud, ckdiv) (((freq / (baud * 2)) - 3) / ckdiv)

/* Find a valid CWGR_CKDIV value and Check if the CONF_TWIHS0_CKDIV will overflow */
#ifndef CONF_TWIHS0_CWGR_CKDIV
#if CONF_TWIHS0_CWGR_CLDIV_CALC(CONF_TWIHS0_FREQUENCY, CONF_TWIHS0_BAUD, 1) <= 255
#define CONF_TWIHS0_CWGR_CKDIV 0
#elif CONF_TWIHS0_CWGR_CLDIV_CALC(CONF_TWIHS0_FREQUENCY, CONF_TWIHS0_BAUD, 2) <= 255
#define CONF_TWIHS0_CWGR_CKDIV 1
#elif CONF_TWIHS0_CWGR_CLDIV_CALC(CONF_TWIHS0_FREQUENCY, CONF_TWIHS0_BAUD, 4) <= 255
#define CONF_TWIHS0_CWGR_CKDIV 2
#elif CONF_TWIHS0_CWGR_CLDIV_CALC(CONF_TWIHS0_FREQUENCY, CONF_TWIHS0_BAUD, 8) <= 255
#define CONF_TWIHS0_CWGR_CKDIV 3
#elif CONF_TWIHS0_CWGR_CLDIV_CALC(CONF_TWIHS0_FREQUENCY, CONF_TWIHS0_BAUD, 16) <= 255
#define CONF_TWIHS0_CWGR_CKDIV 4
#elif CONF_TWIHS0_CWGR_CLDIV_CALC(CONF_TWIHS0_FREQUENCY, CONF_TWIHS0_BAUD, 32) <= 255
#define CONF_TWIHS0_CWGR_CKDIV 5
#elif CONF_TWIHS0_CWGR_CLDIV_CALC(CONF_TWIHS0_FREQUENCY, CONF_TWIHS0_BAUD, 64) <= 255
#define CONF_TWIHS0_CWGR_CKDIV 6
#elif CONF_TWIHS0_CWGR_CLDIV_CALC(CONF_TWIHS0_FREQUENCY, CONF_TWIHS0_BAUD, 128) <= 255
#define CONF_TWIHS0_CWGR_CKDIV 7
#else
#error Failed to generate TWI0 I2C baudrate, please check settings.
#endif
#endif /* end ifndef CONF_TWIHS0_CWGR_CKDIV */

/* TWIHS_CWGR_CKDIV Result value for calc CWGR_CLDIV and CWGR_CHDIV */
#if CONF_TWIHS0_CWGR_CKDIV == 0
#define CONF_TWIHS0_CWGR_CKDIV_val 1
#elif CONF_TWIHS0_CWGR_CKDIV == 1
#define CONF_TWIHS0_CWGR_CKDIV_val 2
#elif CONF_TWIHS0_CWGR_CKDIV == 2
#define CONF_TWIHS0_CWGR_CKDIV_val 4
#elif CONF_TWIHS0_CWGR_CKDIV == 3
#define CONF_TWIHS0_CWGR_CKDIV_val 8
#elif CONF_TWIHS0_CWGR_CKDIV == 4
#define CONF_TWIHS0_CWGR_CKDIV_val 16
#elif CONF_TWIHS0_CWGR_CKDIV == 5
#define CONF_TWIHS0_CWGR_CKDIV_val 32
#elif CONF_TWIHS0_CWGR_CKDIV == 6
#define CONF_TWIHS0_CWGR_CKDIV_val 64
#elif CONF_TWIHS0_CWGR_CKDIV == 7
#define CONF_TWIHS0_CWGR_CKDIV_val 128
#endif

/* Clock Waveform Generator Register Clock Divider */
#ifndef CONF_TWIHS0_CWGR_CLDIV
#define CONF_TWIHS0_CWGR_CLDIV                                                                                         \
	(CONF_TWIHS0_CWGR_CLDIV_CALC(CONF_TWIHS0_FREQUENCY, CONF_TWIHS0_BAUD, CONF_TWIHS0_CWGR_CKDIV_val))
#endif

/* CHDIV same as CLDIV for generator a 50 duty cycle clock */
#ifndef CONF_TWIHS0_CWGR_CHDIV
#define CONF_TWIHS0_CWGR_CHDIV CONF_TWIHS0_CWGR_CLDIV
#endif /* endif CONF_TWIHS0_CWGR_BRSRCCLK == 1 */

/* Configuration for CWGR(TWI Clock Waveform Generator Register) */
#ifndef CONF_TWIHS0_CWGR_REG
#define CONF_TWIHS0_CWGR_REG                                                                                           \
	(TWIHS_CWGR_CKDIV(CONF_TWIHS0_CWGR_CKDIV) | TWIHS_CWGR_CHDIV(CONF_TWIHS0_CWGR_CHDIV)                               \
	 | TWIHS_CWGR_CLDIV(CONF_TWIHS0_CWGR_CLDIV))
#endif

// <<< end of configuration section >>>

#endif // HPL_TWIHS_CONFIG_H
