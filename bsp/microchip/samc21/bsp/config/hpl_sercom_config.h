/* Auto-generated config file hpl_sercom_config.h */
#ifndef HPL_SERCOM_CONFIG_H
#define HPL_SERCOM_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

#include <peripheral_clk_config.h>

#ifndef SERCOM_I2CM_CTRLA_MODE_I2C_MASTER
#define SERCOM_I2CM_CTRLA_MODE_I2C_MASTER (5 << 2)
#endif

#ifndef CONF_SERCOM_0_I2CM_ENABLE
#define CONF_SERCOM_0_I2CM_ENABLE 1
#endif

// <h> Basic

// <o> I2C Bus clock speed (Hz) <1-400000>
// <i> I2C Bus clock (SCL) speed measured in Hz
// <id> i2c_master_baud_rate
#ifndef CONF_SERCOM_0_I2CM_BAUD
#define CONF_SERCOM_0_I2CM_BAUD 100000
#endif

// </h>

// <e> Advanced
// <id> i2c_master_advanced
#ifndef CONF_SERCOM_0_I2CM_ADVANCED_CONFIG
#define CONF_SERCOM_0_I2CM_ADVANCED_CONFIG 1
#endif

// <o> TRise (ns) <0-300>
// <i> Determined by the bus impedance, check electric characteristics in the datasheet
// <i> Standard Fast Mode: typical 215ns, max 300ns
// <i> Fast Mode +: typical 60ns, max 100ns
// <i> High Speed Mode: typical 20ns, max 40ns
// <id> i2c_master_arch_trise

#ifndef CONF_SERCOM_0_I2CM_TRISE
#define CONF_SERCOM_0_I2CM_TRISE 215
#endif

// <q> Master SCL Low Extended Time-Out (MEXTTOEN)
// <i> This enables the master SCL low extend time-out
// <id> i2c_master_arch_mexttoen
#ifndef CONF_SERCOM_0_I2CM_MEXTTOEN
#define CONF_SERCOM_0_I2CM_MEXTTOEN 1
#endif

// <q> Slave SCL Low Extend Time-Out (SEXTTOEN)
// <i> Enables the slave SCL low extend time-out. If SCL is cumulatively held low for greater than 25ms from the initial START to a STOP, the slave will release its clock hold if enabled and reset the internal state machine
// <id> i2c_master_arch_sexttoen
#ifndef CONF_SERCOM_0_I2CM_SEXTTOEN
#define CONF_SERCOM_0_I2CM_SEXTTOEN 0
#endif

// <q> SCL Low Time-Out (LOWTOUT)
// <i> Enables SCL low time-out. If SCL is held low for 25ms-35ms, the master will release it's clock hold
// <id> i2c_master_arch_lowtout
#ifndef CONF_SERCOM_0_I2CM_LOWTOUT
#define CONF_SERCOM_0_I2CM_LOWTOUT 1
#endif

// <o> Inactive Time-Out (INACTOUT)
// <0x0=>Disabled
// <0x1=>5-6 SCL cycle time-out(50-60us)
// <0x2=>10-11 SCL cycle time-out(100-110us)
// <0x3=>20-21 SCL cycle time-out(200-210us)
// <i> Defines if inactivity time-out should be enabled, and how long the time-out should be
// <id> i2c_master_arch_inactout
#ifndef CONF_SERCOM_0_I2CM_INACTOUT
#define CONF_SERCOM_0_I2CM_INACTOUT 0x3
#endif

// <o> SDA Hold Time (SDAHOLD)
// <0=>Disabled
// <1=>50-100ns hold time
// <2=>300-600ns hold time
// <3=>400-800ns hold time
// <i> Defines the SDA hold time with respect to the negative edge of SCL
// <id> i2c_master_arch_sdahold
#ifndef CONF_SERCOM_0_I2CM_SDAHOLD
#define CONF_SERCOM_0_I2CM_SDAHOLD 0x2
#endif

// <q> Run in stand-by
// <i> Determine if the module shall run in standby sleep mode
// <id> i2c_master_arch_runstdby
#ifndef CONF_SERCOM_0_I2CM_RUNSTDBY
#define CONF_SERCOM_0_I2CM_RUNSTDBY 0
#endif

// <o> Debug Stop Mode
// <i> Behavior of the baud-rate generator when CPU is halted by external debugger.
// <0=>Keep running
// <1=>Halt
// <id> i2c_master_arch_dbgstop
#ifndef CONF_SERCOM_0_I2CM_DEBUG_STOP_MODE
#define CONF_SERCOM_0_I2CM_DEBUG_STOP_MODE 0
#endif

// </e>

#ifndef CONF_SERCOM_0_I2CM_SPEED
#define CONF_SERCOM_0_I2CM_SPEED 0x00 // Speed: Standard/Fast mode
#endif
#if CONF_SERCOM_0_I2CM_TRISE < 215 || CONF_SERCOM_0_I2CM_TRISE > 300
#warning Bad I2C Rise time for Standard/Fast mode, reset to 215ns
#undef CONF_SERCOM_0_I2CM_TRISE
#define CONF_SERCOM_0_I2CM_TRISE 215U
#endif

//                  gclk_freq - (i2c_scl_freq * 10) - (gclk_freq * i2c_scl_freq * Trise)
// BAUD + BAUDLOW = --------------------------------------------------------------------
//                  i2c_scl_freq
// BAUD:    register value low  [7:0]
// BAUDLOW: register value high [15:8], only used for odd BAUD + BAUDLOW
#define CONF_SERCOM_0_I2CM_BAUD_BAUDLOW                                                                                \
	(((CONF_GCLK_SERCOM0_CORE_FREQUENCY - (CONF_SERCOM_0_I2CM_BAUD * 10U)                                              \
	   - (CONF_SERCOM_0_I2CM_TRISE * (CONF_SERCOM_0_I2CM_BAUD / 100U) * (CONF_GCLK_SERCOM0_CORE_FREQUENCY / 10000U)    \
	      / 1000U))                                                                                                    \
	      * 10U                                                                                                        \
	  + 5U)                                                                                                            \
	 / (CONF_SERCOM_0_I2CM_BAUD * 10U))
#ifndef CONF_SERCOM_0_I2CM_BAUD_RATE
#if CONF_SERCOM_0_I2CM_BAUD_BAUDLOW > (0xFF * 2)
#warning Requested I2C baudrate too low, please check
#define CONF_SERCOM_0_I2CM_BAUD_RATE 0xFF
#elif CONF_SERCOM_0_I2CM_BAUD_BAUDLOW <= 1
#warning Requested I2C baudrate too high, please check
#define CONF_SERCOM_0_I2CM_BAUD_RATE 1
#else
#define CONF_SERCOM_0_I2CM_BAUD_RATE                                                                                   \
	((CONF_SERCOM_0_I2CM_BAUD_BAUDLOW & 0x1)                                                                           \
	     ? (CONF_SERCOM_0_I2CM_BAUD_BAUDLOW / 2) + ((CONF_SERCOM_0_I2CM_BAUD_BAUDLOW / 2 + 1) << 8)                    \
	     : (CONF_SERCOM_0_I2CM_BAUD_BAUDLOW / 2))
#endif
#endif

#include <peripheral_clk_config.h>

#ifndef CONF_SERCOM_4_USART_ENABLE
#define CONF_SERCOM_4_USART_ENABLE 1
#endif

// <h> Basic Configuration

// <q> Receive buffer enable
// <i> Enable input buffer in SERCOM module
// <id> usart_rx_enable
#ifndef CONF_SERCOM_4_USART_RXEN
#define CONF_SERCOM_4_USART_RXEN 1
#endif

// <q> Transmitt buffer enable
// <i> Enable output buffer in SERCOM module
// <id> usart_tx_enable
#ifndef CONF_SERCOM_4_USART_TXEN
#define CONF_SERCOM_4_USART_TXEN 1
#endif

// <o> Frame parity
// <0x0=>No parity
// <0x1=>Even parity
// <0x2=>Odd parity
// <i> Parity bit mode for USART frame
// <id> usart_parity
#ifndef CONF_SERCOM_4_USART_PARITY
#define CONF_SERCOM_4_USART_PARITY 0x0
#endif

// <o> Character Size
// <0x0=>8 bits
// <0x1=>9 bits
// <0x5=>5 bits
// <0x6=>6 bits
// <0x7=>7 bits
// <i> Data character size in USART frame
// <id> usart_character_size
#ifndef CONF_SERCOM_4_USART_CHSIZE
#define CONF_SERCOM_4_USART_CHSIZE 0x0
#endif

// <o> Stop Bit
// <0=>One stop bit
// <1=>Two stop bits
// <i> Number of stop bits in USART frame
// <id> usart_stop_bit
#ifndef CONF_SERCOM_4_USART_SBMODE
#define CONF_SERCOM_4_USART_SBMODE 0
#endif

// <o> Baud rate <1-3000000>
// <i> USART baud rate setting
// <id> usart_baud_rate
#ifndef CONF_SERCOM_4_USART_BAUD
#define CONF_SERCOM_4_USART_BAUD 115200
#endif

// </h>

// <e> Advanced configuration
// <id> usart_advanced
#ifndef CONF_SERCOM_4_USART_ADVANCED_CONFIG
#define CONF_SERCOM_4_USART_ADVANCED_CONFIG 1
#endif

// <q> Run in stand-by
// <i> Keep the module running in standby sleep mode
// <id> usart_arch_runstdby
#ifndef CONF_SERCOM_4_USART_RUNSTDBY
#define CONF_SERCOM_4_USART_RUNSTDBY 0
#endif

// <q> Immediate Buffer Overflow Notification
// <i> Controls when the BUFOVF status bit is asserted
// <id> usart_arch_ibon
#ifndef CONF_SERCOM_4_USART_IBON
#define CONF_SERCOM_4_USART_IBON 0
#endif

// <q> Start of Frame Detection Enable
// <i> Will wake the device from any sleep mode if usart_init and usart_enable was run priort to going to sleep. (receive buffer must be enabled)
// <id> usart_arch_sfde
#ifndef CONF_SERCOM_4_USART_SFDE
#define CONF_SERCOM_4_USART_SFDE 0
#endif

// <q> Collision Detection Enable
// <i> Collision detection enable
// <id> usart_arch_cloden
#ifndef CONF_SERCOM_4_USART_CLODEN
#define CONF_SERCOM_4_USART_CLODEN 0
#endif

// <o> Operating Mode
// <0x0=>USART with external clock
// <0x1=>USART with internal clock
// <i> Drive the shift register by an internal clock generated by the baud rate generator or an external clock supplied on the XCK pin.
// <id> usart_arch_clock_mode
#ifndef CONF_SERCOM_4_USART_MODE
#define CONF_SERCOM_4_USART_MODE 0x1
#endif

// <o> Sample Rate
// <0x0=>16x arithmetic
// <0x1=>16x fractional
// <0x2=>8x arithmetic
// <0x3=>8x fractional
// <0x4=>3x arithmetic
// <i> How many over-sampling bits used when sampling data state
// <id> usart_arch_sampr
#ifndef CONF_SERCOM_4_USART_SAMPR
#define CONF_SERCOM_4_USART_SAMPR 0x0
#endif

// <o> Sample Adjustment
// <0x0=>7-8-9 (3-4-5 8-bit over-sampling)
// <0x1=>9-10-11 (4-5-6 8-bit over-sampling)
// <0x2=>11-12-13 (5-6-7 8-bit over-sampling)
// <0x3=>13-14-15 (6-7-8 8-bit over-sampling)
// <i> Adjust which samples to use for data sampling in asynchronous mode
// <id> usart_arch_sampa
#ifndef CONF_SERCOM_4_USART_SAMPA
#define CONF_SERCOM_4_USART_SAMPA 0x0
#endif

// <o> Fractional Part <0-7>
// <i> Fractional part of the baud rate if baud rate generator is in fractional mode
// <id> usart_arch_fractional
#ifndef CONF_SERCOM_4_USART_FRACTIONAL
#define CONF_SERCOM_4_USART_FRACTIONAL 0x0
#endif

// <o> Data Order
// <0=>MSB is transmitted first
// <1=>LSB is transmitted first
// <i> Data order of the data bits in the frame
// <id> usart_arch_dord
#ifndef CONF_SERCOM_4_USART_DORD
#define CONF_SERCOM_4_USART_DORD 1
#endif

// Does not do anything in UART mode
#define CONF_SERCOM_4_USART_CPOL 0

// <o> Encoding Format
// <0=>No encoding
// <1=>IrDA encoded
// <id> usart_arch_enc
#ifndef CONF_SERCOM_4_USART_ENC
#define CONF_SERCOM_4_USART_ENC 0
#endif

// <o> LIN Slave Enable
// <i> Break Character Detection and Auto-Baud/LIN Slave Enable.
// <i> Additional setting needed: 16x sample rate using fractional baud rate generation (CTRLA.SAMPR = 1).
// <0=>Disable
// <1=>Enable
// <id> usart_arch_lin_slave_enable
#ifndef CONF_SERCOM_4_USART_LIN_SLAVE_ENABLE
#define CONF_SERCOM_4_USART_LIN_SLAVE_ENABLE 0
#endif

// <o> Debug Stop Mode
// <i> Behavior of the baud-rate generator when CPU is halted by external debugger.
// <0=>Keep running
// <1=>Halt
// <id> usart_arch_dbgstop
#ifndef CONF_SERCOM_4_USART_DEBUG_STOP_MODE
#define CONF_SERCOM_4_USART_DEBUG_STOP_MODE 0
#endif

// </e>

#ifndef CONF_SERCOM_4_USART_CMODE
#define CONF_SERCOM_4_USART_CMODE 0
#endif

#ifndef CONF_SERCOM_4_USART_RXPO
#define CONF_SERCOM_4_USART_RXPO 3 /* RX is on PIN_PB11 */
#endif

#ifndef CONF_SERCOM_4_USART_TXPO
#define CONF_SERCOM_4_USART_TXPO 1 /* TX is on PIN_PB10 */
#endif

/* Set correct parity settings in register interface based on PARITY setting */
#if CONF_SERCOM_4_USART_LIN_SLAVE_ENABLE == 1
#if CONF_SERCOM_4_USART_PARITY == 0
#define CONF_SERCOM_4_USART_PMODE 0
#define CONF_SERCOM_4_USART_FORM 4
#else
#define CONF_SERCOM_4_USART_PMODE CONF_SERCOM_4_USART_PARITY - 1
#define CONF_SERCOM_4_USART_FORM 5
#endif
#else /* #if CONF_SERCOM_4_USART_LIN_SLAVE_ENABLE == 0 */
#if CONF_SERCOM_4_USART_PARITY == 0
#define CONF_SERCOM_4_USART_PMODE 0
#define CONF_SERCOM_4_USART_FORM 0
#else
#define CONF_SERCOM_4_USART_PMODE CONF_SERCOM_4_USART_PARITY - 1
#define CONF_SERCOM_4_USART_FORM 1
#endif
#endif

// Calculate BAUD register value in UART mode
#if CONF_SERCOM_4_USART_SAMPR == 0
#ifndef CONF_SERCOM_4_USART_BAUD_RATE
#define CONF_SERCOM_4_USART_BAUD_RATE                                                                                  \
	65536 - ((65536 * 16.0f * CONF_SERCOM_4_USART_BAUD) / CONF_GCLK_SERCOM4_CORE_FREQUENCY)
#endif
#ifndef CONF_SERCOM_4_USART_RECEIVE_PULSE_LENGTH
#define CONF_SERCOM_4_USART_RECEIVE_PULSE_LENGTH 0
#endif
#elif CONF_SERCOM_4_USART_SAMPR == 1
#ifndef CONF_SERCOM_4_USART_BAUD_RATE
#define CONF_SERCOM_4_USART_BAUD_RATE                                                                                  \
	((CONF_GCLK_SERCOM4_CORE_FREQUENCY) / (CONF_SERCOM_4_USART_BAUD * 16)) - (CONF_SERCOM_4_USART_FRACTIONAL / 8)
#endif
#ifndef CONF_SERCOM_4_USART_RECEIVE_PULSE_LENGTH
#define CONF_SERCOM_4_USART_RECEIVE_PULSE_LENGTH 0
#endif
#elif CONF_SERCOM_4_USART_SAMPR == 2
#ifndef CONF_SERCOM_4_USART_BAUD_RATE
#define CONF_SERCOM_4_USART_BAUD_RATE                                                                                  \
	65536 - ((65536 * 8.0f * CONF_SERCOM_4_USART_BAUD) / CONF_GCLK_SERCOM4_CORE_FREQUENCY)
#endif
#ifndef CONF_SERCOM_4_USART_RECEIVE_PULSE_LENGTH
#define CONF_SERCOM_4_USART_RECEIVE_PULSE_LENGTH 0
#endif
#elif CONF_SERCOM_4_USART_SAMPR == 3
#ifndef CONF_SERCOM_4_USART_BAUD_RATE
#define CONF_SERCOM_4_USART_BAUD_RATE                                                                                  \
	((CONF_GCLK_SERCOM4_CORE_FREQUENCY) / (CONF_SERCOM_4_USART_BAUD * 8)) - (CONF_SERCOM_4_USART_FRACTIONAL / 8)
#endif
#ifndef CONF_SERCOM_4_USART_RECEIVE_PULSE_LENGTH
#define CONF_SERCOM_4_USART_RECEIVE_PULSE_LENGTH 0
#endif
#elif CONF_SERCOM_4_USART_SAMPR == 4
#ifndef CONF_SERCOM_4_USART_BAUD_RATE
#define CONF_SERCOM_4_USART_BAUD_RATE                                                                                  \
	65536 - ((65536 * 3.0f * CONF_SERCOM_4_USART_BAUD) / CONF_GCLK_SERCOM4_CORE_FREQUENCY)
#endif
#ifndef CONF_SERCOM_4_USART_RECEIVE_PULSE_LENGTH
#define CONF_SERCOM_4_USART_RECEIVE_PULSE_LENGTH 0
#endif
#endif

// <<< end of configuration section >>>

#endif // HPL_SERCOM_CONFIG_H
