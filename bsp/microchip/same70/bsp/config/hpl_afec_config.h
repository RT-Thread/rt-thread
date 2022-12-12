/* Auto-generated config file hpl_afec_config.h */
#ifndef HPL_AFEC_CONFIG_H
#define HPL_AFEC_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef CONF_AFEC_0_ENABLE
#define CONF_AFEC_0_ENABLE 1
#endif

// <h> Basic Configuration

// <o> Conversion Result Resolution
// <0x0=>12-bit
// <0x2=>13-bit
// <0x3=>14-bit
// <0x4=>15-bit
// <0x5=>16-bit
// <i>  Defines the bit resolution for the AFEC sample values (RES)
// <id> afec_resolution
#ifndef CONF_AFEC_0_RES
#define CONF_AFEC_0_RES 0x5
#endif

// <o> Prescaler Rate Selection <1-255>
// <i> PRESCAL = fperipheral clock/ fAFE_clock - 1
// <id> afec_prescaler
#ifndef CONF_AFEC_0_PRESCAL
#define CONF_AFEC_0_PRESCAL 0x31
#endif

// <q> Free Running Mode
// <i> When enabled, the ADC is in free running mode and a new conversion will be initiated when a previous conversion completes. (FREERUN)
// <id> afec_freerunning_mode
#ifndef CONF_AFEC_0_FREERUN
#define CONF_AFEC_0_FREERUN 0
#endif

// <q> TAG of the AFEC_LDCR
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_tag
#ifndef CONF_AFEC_0_TAG
#define CONF_AFEC_0_TAG 1
#endif

// <q> Single Trigger Mode
// <i> When enabled, only a single trigger is required to get an averaged value
// <id> afec_stm
#ifndef CONF_AFEC_0_STM
#define CONF_AFEC_0_STM 1
#endif

// <o> Sign Mode Selection
// <0x0=>Single-Ended channels: Unsigned. Differential channels: Signed.
// <0x1=>Single-Ended channels: Signed. Differential channels: Unsigned.
// <0x2=>All channels: Unsigned.
// <0x3=>All channels: Signed.
// <i>  Defines the bit resolution for the AFEC sample values (RES)
// <id> afec_sign_mode
#ifndef CONF_AFEC_0_SIGNMODE
#define CONF_AFEC_0_SIGNMODE 0x0
#endif

// <e> Trigger Enable
// <i> Hardware triggers are disabled. Starting a conversion is only possible by software.
// <id> afec_trigger_enable
#ifndef CONF_AFEC_0_TRGEN
#define CONF_AFEC_0_TRGEN 0
#endif

// <o> Trigger Selection
// <0x0=>AFE0_ADTRG for AFEC0 / AFE1_ADTRG for AFEC1
// <0x1=>TIOA Output of the TC Channel 0 for AFEC0/TIOA Output of the TC Channel 3 for AFEC1
// <0x2=>TIOA Output of the TC Channel 1 for AFEC0/TIOA Output of the TC Channel 4 for AFEC1
// <0x3=>TIOA Output of the TC Channel 2 for AFEC0/TIOA Output of the TC Channel 5 for AFEC1
// <0x4=>PWM0 event line 0 for AFEC0 / PWM1 event line 0 for AFEC1
// <0x5=>PWM0 event line 1 for AFEC0 / PWM1 event line 1 for AFEC1
// <0x6=>Analog Comparator
// <i> These bits define the trigger selection.
// <id> afec_trigger_selection
#ifndef CONF_AFEC_0_TRGSEL
#define CONF_AFEC_0_TRGSEL 0x0
#endif
// </e>

// </h>

// <h> Channel Configuration

// <e> User Sequence Mode
// <i> When enabled, the sequence respects what is defined
// <id> afec_useq
#ifndef CONF_AFEC_0_USEQ
#define CONF_AFEC_0_USEQ 0x0
#endif

// <o> User Sequence Number 0
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch0
#ifndef CONF_AFEC_0_USCH0
#define CONF_AFEC_0_USCH0 0xf
#endif

// <o> User Sequence Number 1
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch1
#ifndef CONF_AFEC_0_USCH1
#define CONF_AFEC_0_USCH1 0xf
#endif

// <o> User Sequence Number 2
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch2
#ifndef CONF_AFEC_0_USCH2
#define CONF_AFEC_0_USCH2 0xf
#endif

// <o> User Sequence Number 3
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch3
#ifndef CONF_AFEC_0_USCH3
#define CONF_AFEC_0_USCH3 0xf
#endif

// <o> User Sequence Number 4
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch4
#ifndef CONF_AFEC_0_USCH4
#define CONF_AFEC_0_USCH4 0xf
#endif

// <o> User Sequence Number 5
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch5
#ifndef CONF_AFEC_0_USCH5
#define CONF_AFEC_0_USCH5 0xf
#endif

// <o> User Sequence Number 6
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch6
#ifndef CONF_AFEC_0_USCH6
#define CONF_AFEC_0_USCH6 0xf
#endif

// <o> User Sequence Number 7
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch7
#ifndef CONF_AFEC_0_USCH7
#define CONF_AFEC_0_USCH7 0xf
#endif

// <o> User Sequence Number 8
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch8
#ifndef CONF_AFEC_0_USCH8
#define CONF_AFEC_0_USCH8 0xf
#endif

// <o> User Sequence Number 9
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch9
#ifndef CONF_AFEC_0_USCH9
#define CONF_AFEC_0_USCH9 0xf
#endif

// <o> User Sequence Number 10
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch10
#ifndef CONF_AFEC_0_USCH10
#define CONF_AFEC_0_USCH10 0xf
#endif

// <o> User Sequence Number 11
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <0xF=>None
// <i>  Defines the bit user sequence.
// <id> afec_usch11
#ifndef CONF_AFEC_0_USCH11
#define CONF_AFEC_0_USCH11 0xf
#endif

// </e>

// <e> Channel 0 Enable
// <id> afec_channel0_enable
#ifndef CONF_AFEC_0_CHANNEL0_ENABLE
#define CONF_AFEC_0_CHANNEL0_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain0
#ifndef CONF_AFEC_0_GAIN0
#define CONF_AFEC_0_GAIN0 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset0
#ifndef CONF_AFEC_0_AOFF0
#define CONF_AFEC_0_AOFF0 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff0
#ifndef CONF_AFEC_0_DIFF0
#define CONF_AFEC_0_DIFF0 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual0
#ifndef CONF_AFEC_0_DUAL0
#define CONF_AFEC_0_DUAL0 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr0
#ifndef CONF_AFEC_0_ECORR0
#define CONF_AFEC_0_ECORR0 0
#endif
// </e>

// <e> Channel 1 Enable
// <id> afec_channel1_enable
#ifndef CONF_AFEC_0_CHANNEL1_ENABLE
#define CONF_AFEC_0_CHANNEL1_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain1
#ifndef CONF_AFEC_0_GAIN1
#define CONF_AFEC_0_GAIN1 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset1
#ifndef CONF_AFEC_0_AOFF1
#define CONF_AFEC_0_AOFF1 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff1
#ifndef CONF_AFEC_0_DIFF1
#define CONF_AFEC_0_DIFF1 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual1
#ifndef CONF_AFEC_0_DUAL1
#define CONF_AFEC_0_DUAL1 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr1
#ifndef CONF_AFEC_0_ECORR1
#define CONF_AFEC_0_ECORR1 0
#endif
// </e>

// <e> Channel 2 Enable
// <id> afec_channel2_enable
#ifndef CONF_AFEC_0_CHANNEL2_ENABLE
#define CONF_AFEC_0_CHANNEL2_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain2
#ifndef CONF_AFEC_0_GAIN2
#define CONF_AFEC_0_GAIN2 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset2
#ifndef CONF_AFEC_0_AOFF2
#define CONF_AFEC_0_AOFF2 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff2
#ifndef CONF_AFEC_0_DIFF2
#define CONF_AFEC_0_DIFF2 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual2
#ifndef CONF_AFEC_0_DUAL2
#define CONF_AFEC_0_DUAL2 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr2
#ifndef CONF_AFEC_0_ECORR2
#define CONF_AFEC_0_ECORR2 0
#endif
// </e>

// <e> Channel 3 Enable
// <id> afec_channel3_enable
#ifndef CONF_AFEC_0_CHANNEL3_ENABLE
#define CONF_AFEC_0_CHANNEL3_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain3
#ifndef CONF_AFEC_0_GAIN3
#define CONF_AFEC_0_GAIN3 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset3
#ifndef CONF_AFEC_0_AOFF3
#define CONF_AFEC_0_AOFF3 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff3
#ifndef CONF_AFEC_0_DIFF3
#define CONF_AFEC_0_DIFF3 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual3
#ifndef CONF_AFEC_0_DUAL3
#define CONF_AFEC_0_DUAL3 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr3
#ifndef CONF_AFEC_0_ECORR3
#define CONF_AFEC_0_ECORR3 0
#endif
// </e>

// <e> Channel 4 Enable
// <id> afec_channel4_enable
#ifndef CONF_AFEC_0_CHANNEL4_ENABLE
#define CONF_AFEC_0_CHANNEL4_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain4
#ifndef CONF_AFEC_0_GAIN4
#define CONF_AFEC_0_GAIN4 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset4
#ifndef CONF_AFEC_0_AOFF4
#define CONF_AFEC_0_AOFF4 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff4
#ifndef CONF_AFEC_0_DIFF4
#define CONF_AFEC_0_DIFF4 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual4
#ifndef CONF_AFEC_0_DUAL4
#define CONF_AFEC_0_DUAL4 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr4
#ifndef CONF_AFEC_0_ECORR4
#define CONF_AFEC_0_ECORR4 0
#endif
// </e>

// <e> Channel 5 Enable
// <id> afec_channel5_enable
#ifndef CONF_AFEC_0_CHANNEL5_ENABLE
#define CONF_AFEC_0_CHANNEL5_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain5
#ifndef CONF_AFEC_0_GAIN5
#define CONF_AFEC_0_GAIN5 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset5
#ifndef CONF_AFEC_0_AOFF5
#define CONF_AFEC_0_AOFF5 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff5
#ifndef CONF_AFEC_0_DIFF5
#define CONF_AFEC_0_DIFF5 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual5
#ifndef CONF_AFEC_0_DUAL5
#define CONF_AFEC_0_DUAL5 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr5
#ifndef CONF_AFEC_0_ECORR5
#define CONF_AFEC_0_ECORR5 0
#endif
// </e>

// <e> Channel 6 Enable
// <id> afec_channel6_enable
#ifndef CONF_AFEC_0_CHANNEL6_ENABLE
#define CONF_AFEC_0_CHANNEL6_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain6
#ifndef CONF_AFEC_0_GAIN6
#define CONF_AFEC_0_GAIN6 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset6
#ifndef CONF_AFEC_0_AOFF6
#define CONF_AFEC_0_AOFF6 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff6
#ifndef CONF_AFEC_0_DIFF6
#define CONF_AFEC_0_DIFF6 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual6
#ifndef CONF_AFEC_0_DUAL6
#define CONF_AFEC_0_DUAL6 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr6
#ifndef CONF_AFEC_0_ECORR6
#define CONF_AFEC_0_ECORR6 0
#endif
// </e>

// <e> Channel 7 Enable
// <id> afec_channel7_enable
#ifndef CONF_AFEC_0_CHANNEL7_ENABLE
#define CONF_AFEC_0_CHANNEL7_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain7
#ifndef CONF_AFEC_0_GAIN7
#define CONF_AFEC_0_GAIN7 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset7
#ifndef CONF_AFEC_0_AOFF7
#define CONF_AFEC_0_AOFF7 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff7
#ifndef CONF_AFEC_0_DIFF7
#define CONF_AFEC_0_DIFF7 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual7
#ifndef CONF_AFEC_0_DUAL7
#define CONF_AFEC_0_DUAL7 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr7
#ifndef CONF_AFEC_0_ECORR7
#define CONF_AFEC_0_ECORR7 0
#endif
// </e>

// <e> Channel 8 Enable
// <id> afec_channel8_enable
#ifndef CONF_AFEC_0_CHANNEL8_ENABLE
#define CONF_AFEC_0_CHANNEL8_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain8
#ifndef CONF_AFEC_0_GAIN8
#define CONF_AFEC_0_GAIN8 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset8
#ifndef CONF_AFEC_0_AOFF8
#define CONF_AFEC_0_AOFF8 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff8
#ifndef CONF_AFEC_0_DIFF8
#define CONF_AFEC_0_DIFF8 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual8
#ifndef CONF_AFEC_0_DUAL8
#define CONF_AFEC_0_DUAL8 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr8
#ifndef CONF_AFEC_0_ECORR8
#define CONF_AFEC_0_ECORR8 0
#endif
// </e>

// <e> Channel 9 Enable
// <id> afec_channel9_enable
#ifndef CONF_AFEC_0_CHANNEL9_ENABLE
#define CONF_AFEC_0_CHANNEL9_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain9
#ifndef CONF_AFEC_0_GAIN9
#define CONF_AFEC_0_GAIN9 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset9
#ifndef CONF_AFEC_0_AOFF9
#define CONF_AFEC_0_AOFF9 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff9
#ifndef CONF_AFEC_0_DIFF9
#define CONF_AFEC_0_DIFF9 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual9
#ifndef CONF_AFEC_0_DUAL9
#define CONF_AFEC_0_DUAL9 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr9
#ifndef CONF_AFEC_0_ECORR9
#define CONF_AFEC_0_ECORR9 0
#endif
// </e>

// <e> Channel 10 Enable
// <id> afec_channel10_enable
#ifndef CONF_AFEC_0_CHANNEL10_ENABLE
#define CONF_AFEC_0_CHANNEL10_ENABLE 1
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain10
#ifndef CONF_AFEC_0_GAIN10
#define CONF_AFEC_0_GAIN10 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset10
#ifndef CONF_AFEC_0_AOFF10
#define CONF_AFEC_0_AOFF10 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff10
#ifndef CONF_AFEC_0_DIFF10
#define CONF_AFEC_0_DIFF10 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual10
#ifndef CONF_AFEC_0_DUAL10
#define CONF_AFEC_0_DUAL10 1
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr10
#ifndef CONF_AFEC_0_ECORR10
#define CONF_AFEC_0_ECORR10 1
#endif
// </e>

// <e> Channel 11 Enable
// <id> afec_channel11_enable
#ifndef CONF_AFEC_0_CHANNEL11_ENABLE
#define CONF_AFEC_0_CHANNEL11_ENABLE 0
#endif

// <o> Gain
// <0x0=>1
// <0x1=>2
// <0x2=>4
// <i>  Defines the bit gain for channel.
// <id> afec_channel_gain11
#ifndef CONF_AFEC_0_GAIN11
#define CONF_AFEC_0_GAIN11 0x0
#endif

// <o> Offset Compensation <0-1023>
// <i> Defines the analog offset. This value is used as an input value for the DAC included in the AFE.
// <id> afec_channel_offset11
#ifndef CONF_AFEC_0_AOFF11
#define CONF_AFEC_0_AOFF11 0x200
#endif

// <q> Differential Inputs Mode Enable
// <i> When enabled, appends the channel number to the conversion result.
// <id> afec_channel_diff11
#ifndef CONF_AFEC_0_DIFF11
#define CONF_AFEC_0_DIFF11 0
#endif

// <q> Dual Sample & Hold Enable
// <i> If enabled, dual Sample-and-Hold mode. Else, single Sample-and-Hold mode.
// <id> afec_channel_dual11
#ifndef CONF_AFEC_0_DUAL11
#define CONF_AFEC_0_DUAL11 0
#endif

// <q> Error Correction Enable
// <i> If enabled, automatic error correction.
// <id> afec_channel_ecorr11
#ifndef CONF_AFEC_0_ECORR11
#define CONF_AFEC_0_ECORR11 0
#endif
// </e>

// </h>

// <e> Advanced Configuration
// <id> afec_advanced_settings
#ifndef CONF_AFEC_0_ADVANCED
#define CONF_AFEC_0_ADVANCED 1
#endif

// <q> Sleep Mode
// <i> When enabled, the AFE and reference voltage circuitry are OFF between conversions.
// <id> afec_sleep_mode
#ifndef CONF_AFEC_0_SLEEP
#define CONF_AFEC_0_SLEEP 0
#endif

// <q> Fast Wake-up Mode
// <i> When enabled, the voltage reference is ON between conversions and AFE is OFF.
// <id> afec_fast_wakeup_mode
#ifndef CONF_AFEC_0_FWUP
#define CONF_AFEC_0_FWUP 0
#endif

// <o> Start-up Time
// <0x0=>0 periods of AFE clock
// <0x1=>8 periods of AFE clock
// <0x2=>16 periods of AFE clock
// <0x3=>24 periods of AFE clock
// <0x4=>64 periods of AFE clock
// <0x5=>80 periods of AFE clock
// <0x6=>96 periods of AFE clock
// <0x7=>112 periods of AFE clock
// <0x8=>512 periods of AFE clock
// <0x9=>576 periods of AFE clock
// <0xA=>640 periods of AFE clock
// <0xB=>704 periods of AFE clock
// <0xC=>768 periods of AFE clock
// <0xD=>832 periods of AFE clock
// <0xE=>896 periods of AFE clock
// <0xF=>960 periods of AFE clock
// <i>  Defines the bit start-up time.
// <id> afec_startup_time
#ifndef CONF_AFEC_0_STARTUP
#define CONF_AFEC_0_STARTUP 0x4
#endif

// <hidden>
// <o> Tracking Time <0-16>
// <i> Inherent tracking time is always 15 AFE clock cycles. Do not modify this field.
// <id> afec_tracktim
#ifndef CONF_AFEC_0_TRACKTIM
#define CONF_AFEC_0_TRACKTIM 15
#endif
// <o> Transfer Period <0-3>
// <i> Set to 2 to optimize transfer time. Do not modify this field.
// <id> afec_transfer
#ifndef CONF_AFEC_0_TRANSFER
#define CONF_AFEC_0_TRANSFER 2
#endif
// </hidden>

// <o> AFE Bias Current Control <0-3>
// <i> Adapts performance versus power consumption.
// <id> afec_ibctl
#ifndef CONF_AFEC_0_IBCTL
#define CONF_AFEC_0_IBCTL 0x1
#endif

// <e> Sample & Hold unit Correction Enable
// <i> If enabled, selects the Sample & Hold unit will be displayed
// <id> afec_cosr_csel
#ifndef CONF_AFEC_0_COSR_CSEL
#define CONF_AFEC_0_COSR_CSEL 0
#endif

// <o> Offset Correction <0-4095>
// <i> These bits define Offset correction. The offset is signed (2's complement), only bits 0 to 11 are relevant.
// <id> afec_offsetcorr
#ifndef CONF_AFEC_0_OFFSETCORR
#define CONF_AFEC_0_OFFSETCORR 0
#endif

// <o> Gain Correction <0-4095>
// <i> These bits define gain correction. Only bits 0 to 11 are relevant.
// <id> afec_gaincorr
#ifndef CONF_AFEC_0_GAINCORR
#define CONF_AFEC_0_GAINCORR 0
#endif

// </e>

// <e> Comparison Mode Configuration
// <i> Comparison mode configuration
// <id> afec_comparison_settings
#ifndef CONF_AFEC_0_COMPARISON
#define CONF_AFEC_0_COMPARISON 0
#endif

// <o> Comparison Mode
// <0x0=>The converted data is lower than the low threshold of the window.
// <0x1=>the converted data is higher than the high threshold of the window.
// <0x2=>the converted data is in the comparison window.
// <0x3=>the converted data is out of the comparison window.
// <i>  Defines the bit comparison mode.
// <id> afec_cmpmode
#ifndef CONF_AFEC_0_CMPMODE
#define CONF_AFEC_0_CMPMODE 0x0
#endif

// <o> Compare Window Lower Threshold <0-65535>
// <i> These bits define the lower threshold value.
// <id> afec_lowthres
#ifndef CONF_AFEC_0_LOWTHRES
#define CONF_AFEC_0_LOWTHRES 0
#endif

// <o> Compare Window Upper Threshold <0-65535>
// <i> These bits define the lower threshold value.
// <id> afec_highthres
#ifndef CONF_AFEC_0_HIGHTHRES
#define CONF_AFEC_0_HIGHTHRES 0
#endif

// <e> Compare All Channels
// <i> If enabled, all channels are compared. Else, only the channel indicated in CMPSEL field is compared.
// <id> afec_compare_all_channels
#ifndef CONF_AFEC_0_CMPALL
#define CONF_AFEC_0_CMPALL 0
#endif

// <o> Comparison Selected Channel
// <0x0=>Channel 0
// <0x1=>Channel 1
// <0x2=>Channel 2
// <0x3=>Channel 3
// <0x4=>Channel 4
// <0x5=>Channel 5
// <0x6=>Channel 6
// <0x7=>Channel 7
// <0x8=>Channel 8
// <0x9=>Channel 9
// <0xA=>Channel 10
// <0xB=>Channel 11
// <i>  Defines the bit indicates which channel has to be compared.
// <id> afec_cmpsel
#ifndef CONF_AFEC_0_CMPSEL
#define CONF_AFEC_0_CMPSEL 0x0
#endif
// </e>

// </e>

// </e>

#if ((0 || CONF_AFEC_0_CHANNEL0_ENABLE || CONF_AFEC_0_CHANNEL1_ENABLE || CONF_AFEC_0_CHANNEL2_ENABLE                   \
      || CONF_AFEC_0_CHANNEL3_ENABLE || CONF_AFEC_0_CHANNEL4_ENABLE || CONF_AFEC_0_CHANNEL5_ENABLE                     \
      || CONF_AFEC_0_CHANNEL6_ENABLE || CONF_AFEC_0_CHANNEL7_ENABLE || CONF_AFEC_0_CHANNEL8_ENABLE                     \
      || CONF_AFEC_0_CHANNEL9_ENABLE || CONF_AFEC_0_CHANNEL10_ENABLE || CONF_AFEC_0_CHANNEL11_ENABLE)                  \
     == 0)
#warning Select one channel at least, check your configuration!
#endif

// <<< end of configuration section >>>

#endif // HPL_AFEC_CONFIG_H
