/**************************************************************************//**
 * @file     trng_reg.h
 * @brief    True Random Number Generator register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __TRNG_REG_H__
#define __TRNG_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/*---------------------- True Random Number Generator -------------------------*/
/**
    @addtogroup TRNG True Random Number Generator(TRNG)
    Memory Mapped Structure for TRNG Controller
@{ */

typedef struct
{
    /**
     * @var TRNG_T::CTL
     * Offset: 0x00  The CTRL register is used to cause the TRNG NIST to execute one of a number of actions.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |CMD       |Execute a Command
     * |        |          |Enumerated values not listed are 'reserved'.
     * |        |          |0000 = (NOP): Execute a NOP.
     * |        |          |0001 = (GEN_NOISE): Generate full-entropy seed from noise.
     * |        |          |0010 = (GEN_NONCE): Generate seed from host-written nonce.
     * |        |          |0011 = (CREATE_STATE): Move DRBG to create state.
     * |        |          |0100 = (RENEW_STATE): Move DRBG to renew state.
     * |        |          |0101 = (REFRESH_ADDIN): Move DRBG to refresh addin.
     * |        |          |0110 = (GEN_RANDOM): Generate a random number.
     * |        |          |0111 = (ADVANCE_STATE): Advance DRBG state.
     * |        |          |1000 = (RUN_KAT): Run KAT on DRBG or entropy source.
     * |        |          |1111 = (ZEROIZE): Zeroize.
     * @var TRNG_T::MODE
     * Offset: 0x04  The MODE register is used to enable or disable certain run-time features within the TRNG NIST.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SEC_ALG   |Select Security Strength in DRBG
     * |        |          |0 = (SEC_128): AES-128.
     * |        |          |1 = (SEC_256): AES-256.
     * |[3]     |PRED_RESIST|Prediction Resistance
     * |        |          |0 = (PRED_DISABLE): Prediction resistance is not required.
     * |        |          |1 = (PRED_ENABLED): Prediction resistance is required.
     * |[4]     |ADDIN_PRESENT|Availability of the Additional Input
     * |        |          |0 = (ADDIN_NOT_REQ): No Additional Input required from host.
     * |        |          |1 = (ADDIN_REQ): Additional input must be provided by host.
     * |[6:5]   |KAT_VEC   |Select Test Vectors for Known-answer Test
     * |        |          |00 = (KAT_VEC0): KAT vector 0.
     * |        |          |01 = (KAT_VEC1): KAT vector 1.
     * |        |          |10 = (KAT_VEC2): KAT vector 2.
     * |        |          |11 = (KAT_ALL): Run all 3 KAT vectors.
     * |[8:7]   |KAT_SEL   |Select Test Component for Known-answer Test
     * |        |          |00 = (KAT_DRBG): KAT on DRBG.
     * |        |          |01 = (KAT_DF): KAT on conditioning component (Derivation Function).
     * |        |          |10 = (KAT_BOTH): KAT on both DRBG and DF.
     * |        |          |11 = Reserved.
     * @var TRNG_T::SMODE
     * Offset: 0x08  The SMODE register is used to enable or disable certain MISSION mode run-time features.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |NONCE     |Set the Core in Nonce Seeding Mode
     * |        |          |0 = (NONCE_DISABLED): Disable nonce mode.
     * |        |          |1 = (NONCE_ENABLED): Enable nonce mode.
     * |[1]     |MISSION_MODE|Operating Mode
     * |        |          |0 = (RST_TEST_MODE): test mode.
     * |        |          |1 = (RST_MISSION_MODE): mission mode.
     * |        |          |Note: Any change to the state of this field (1 to 0 or 0 to 1) causes the TRNG NIST to zeroize itself.
     * |[9:2]   |MAX_REJECTS|Maximum Number of Consecutive Bit Rejections Before Issuing Ring Tweak
     * |        |          |Default is to 10 (0xa).
     * |[23:16] |INDIV_HT_DISABLE|Statistical Health Tests Individually
     * |        |          |0 = Disable.
     * |        |          |1 = Enable.
     * |        |          |INDIV_HT_DISABLE[0] = Repetition Count test on raw entropy.
     * |        |          |INDIV_HT_DISABLE[1] = Adaptive Proportion test on raw entropy.
     * |        |          |INDIV_HT_DISABLE[2] = Monobit test on raw entropy.
     * |        |          |INDIV_HT_DISABLE[3] = Poker test on raw entropy.
     * |        |          |INDIV_HT_DISABLE[4] = Run test on raw entropy.
     * |        |          |INDIV_HT_DISABLE[5] = Long Run test on raw entropy.
     * |        |          |INDIV_HT_DISABLE[6] = Auto-correlation test on raw entropy.
     * |        |          |INDIV_HT_DISABLE[7] = Repetition Count test on entropy source output.
     * |        |          |Note: Users only can enable/disable statistical health test in TEST mode
     * |        |          |This field cannot change in MISSION mode and its value is always 0 in MISSION mode.
     * |[31]    |NOISE_COLLECT|Raw Noise Collection Mode
     * |        |          |0 = Disable.
     * |        |          |1 = Enable.
     * |        |          |Note: Users only can enable/disable raw noise collection in TEST mode
     * |        |          |This bit cannot be set to 1 in MISSION mode.
     * @var TRNG_T::STAT
     * Offset: 0x0C  The STAT register allows the user to monitor the internal status of the TRNG NIST.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |LAST_CMD  |Last Command
     * |        |          |0000 = (NOP).
     * |        |          |0001 = (GEN_NOISE).
     * |        |          |0011 = (GEN_NONCE).
     * |        |          |0011 = (CREATE_STATE).
     * |        |          |0100 = (RENEW_STATE).
     * |        |          |0101 = (REFRESH_ADDIN).
     * |        |          |0110 = (GEN_RANDOM).
     * |        |          |0111 = (ADVANCE_STATE).
     * |        |          |1000 = (RUN_KAT).
     * |        |          |1111 = (ZEROIZE).
     * |        |          |Others = Reserved.
     * |[4]     |SEC_ALG   |Reflects State of MODE.SEC_ALG
     * |        |          |0 = (SEC_ALG_0): Maximum security strength set to 128.
     * |        |          |1 =(SEC_ALG_1): Maximum security strength set to 256.
     * |[5]     |NONCE_MODE|Reflects State of SMODE.NONCE
     * |        |          |0 = (NONCE_DISABLE): Nonce mode disabled.
     * |        |          |1 = (NONCE_ENABLE): Nonce mode enabled (allows CTRL.CMD value of 2).
     * |[6]     |MISSION_MODE|Reflects State of SMODE.MISSION_MODE
     * |        |          |0 = (SEC_MODE_MISSION): Core is in TEST mode.
     * |        |          |1 = (SEC_MODE_TEST): Core is in MISSION mode.
     * |[8:7]   |DRBG_STATE|Reflects How a DRBG State Is Instantiated
     * |        |          |00 = (DRBG_NOT_INIT): State is not instantiated.
     * |        |          |01 = (DRBG_NS): State is instantiated using the built-in noise source.
     * |        |          |10 = (DRBG_HOST): State is instantiated using the host-provided nonce.
     * |        |          |11 = Reserved.
     * |[9]     |STARTUP_TEST_STUCK|Indicates Whether the Startup Test Is Stuck
     * |        |          |0 = (STARTUP_TEST_NOT_STUCK): Startup test is not stuck (yet).
     * |        |          |1 = (STARTUP_TEST_IS_STUCK): Startup test is highly likely stuck.
     * |        |          |Note: Only valid when sticky startup test feature Is enabled.
     * |[10]    |STARTUP_TEST_IN_PROG|Indicates Whether the Startup Test Is in Progress
     * |        |          |0 = (STARTUP_TEST_NOT_STUCK): Startup test is finished.
     * |        |          |1 = (STARTUP_TEST_IS_STUCK): Startup test is in progress.
     * |[31]    |BUSY      |State of the Core
     * |        |          |0 = (BUSY_NOT): Idle.
     * |        |          |1 = (BUSY_EXEC): Currently executing a command.
     * @var TRNG_T::IE
     * Offset: 0x10  The IE register is used to enable or disable interrupts within the TRNG NIST.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ZEROIZED  |Include or Exclude ZEROIZED Interrupt Contribution
     * |        |          |0 = (ZEROIZED_DIS): Disable ZEROIZED interrupt contribution.
     * |        |          |1 = (ZEROIZED_EN): Enable ZEROIZED interrupt contribution.
     * |[1]     |KAT_COMPLETED|Include or Exclude KAT_COMPLETED Interrupt Contribution
     * |        |          |0 = (KAT_COMPLETED_DIS): Disable KAT_COMPLETED interrupt contribution.
     * |        |          |1 = (KAT_COMPLETED_EN): Enable KAT_COMPLETED interrupt contribution.
     * |[2]     |NOISE_RDY |Include or Exclude NOISE_RDY Interrupt Contribution
     * |        |          |0 = (NOISE_RDY_DIS): Disable NOISE_RDY interrupt contribution.
     * |        |          |1 = (NOISE_RDY_EN): Enable NOISE_RDY interrupt contribution.
     * |[3]     |ALARMS    |Include or Exclude ALARMS Interrupt Contribution
     * |        |          |0 = (ALARMS_DIS): Disable ALARMS interrupt contribution.
     * |        |          |1 = (ALARMS_EN): Enable ALARMS interrupt contribution.
     * |[4]     |DONE      |Include or Exclude DONE Interrupt Contribution
     * |        |          |0 = (DONE_DIS): Disable DONE interrupt contribution.
     * |        |          |1 = (DONE_EN): Enable DONE interrupt contribution.
     * |[31]    |GLBL      |Global Interrupt Enable Signal for the TRNG NIST
     * |        |          |0 = (GLBL_DIS): Disable GLBL interrupt contribution.
     * |        |          |1 = (GLBL_EN): Enable GLBL interrupt contribution.
     * @var TRNG_T::ISTAT
     * Offset: 0x14  The ISTAT register allows the user to monitor the interrupt contributions of the TRNG NIST.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ZEROIZED  |ZEROIZED Flag
     * |        |          |Indicates the Completion of the ZEROIZE Operation
     * |        |          |0 = (ZEROIZED_R0): R0: No unacknowledged ZEROIZED.
     * |        |          | (ZEROIZED_W0): W0: NOP.
     * |        |          |1 = (ZEROIZED_R1): R1: Unacknowledged ZEROIZED.
     * |        |          | (ZEROIZED_W1): W1: Clear ZEROIZED flag.
     * |[1]     |KAT_COMPLETED|KAT_COMPLETED Flag
     * |        |          |Indicates the Completion of the RUN_KAT Command
     * |        |          |0 = (KAT_COMPLETED_R0): R0: No unacknowledged KAT_COMPLETED.
     * |        |          | (KAT_COMPLETED_W0): W0: NOP.
     * |        |          |1 = (KAT_COMPLETED_R1): R1: Unacknowledged KAT_COMPLETED.
     * |        |          | (KAT_COMPLETED_W1): W1: Clear KAT_COMPLETED flag.
     * |[2]     |NOISE_RDY |NOISE_RDY Flag
     * |        |          |When TRNG NIST is generating a full-entropy seed in the self-seeding mode, MISSION_MODE(TRNG_SMODE[1]) is 0 (TEST mode) and SMODE.NOISE_COLLECT is set to 1, the NOISE_RDY bit informs the user when 512 bits of noise have been generated
     * |        |          |This interrupt never happens in the MISSION mode of operation.
     * |        |          |0 = (NOISE_RDY_R0): R0: No unacknowledged noise generation completion.
     * |        |          | (NOISE_RDY_W0): W0: NOP.
     * |        |          |1 = (NOISE_RDY_R1): R1: Unacknowledged noise generation completion.
     * |        |          | (NOISE_RDY_W1): W1: Clear NOISE_RDY flag.
     * |[3]     |ALARMS    |ALARMS Flag
     * |        |          |The ALARMS bit allows the user to poll failures
     * |        |          |When an alarm occurs, an automatic zeroize happens
     * |        |          |Clearing this interrupt also clears the O_alarm pin.
     * |        |          |0 = (ALARMS_R0): R0: No unacknowledged ALARMS.
     * |        |          | (ALARMS_W0): W0: NOP.
     * |        |          |1 = (ALARMS_R1): R1: Unacknowledged ALARMS.
     * |        |          | (ALARMS_W1): W1: Clear ALARMS flag.
     * |[4]     |DONE      |DONE Flag
     * |        |          |The DONE bit allows the user to poll the completion of all commands except RUN_KAT and ZEROIZE which have their own interrupt.
     * |        |          |0 = (DONE_R0): R0: No unacknowledged command completion.
     * |        |          | (DONE_W0): W0: NOP.
     * |        |          |1 = (DONE_R1): R1: Unacknowledged command completion.
     * |        |          | (DONE_W1): W1: Clear DONE flag.
     * @var TRNG_T::ALARMS
     * Offset: 0x18  The ALARMS register allows the user to monitor the source of critical alarms.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |FAILED_TEST_ID|FAILED_TEST_ID Error Flag
     * |        |          |When an alarm is issued, the FAILED_TEST_ID field shows which test has failed
     * |        |          |This fields only shows the first detected failed test and it should not be assumed that the remaining statistical tests are passed.
     * |        |          |0000 = (FAILED_TEST_ID_0): no failure.
     * |        |          |0001 = (FAILED_TEST_ID_1): failure in both KAT and statistical tests.
     * |        |          |0010 = (FAILED_TEST_ID_2): KAT test failure.
     * |        |          |0011 = (FAILED_TEST_ID_3): Monobit test failure.
     * |        |          |0100 = (FAILED_TEST_ID_4): Run test failure.
     * |        |          |0101 = (FAILED_TEST_ID_5): Long Run test failure.
     * |        |          |0110 = (FAILED_TEST_ID_6): Auto-correlation test failure.
     * |        |          |0111 = (FAILED_TEST_ID_7): Poker test failure.
     * |        |          |1000 = (FAILED_TEST_ID_8): Repetition Count test failure.
     * |        |          |1001 = (FAILED_TEST_ID_9): Adaptive Proportion test failure.
     * |        |          |Others = Reserved.
     * |[4]     |ILLEGAL_CMD_SEQ|ILLEGAL_CMD_SEQ Error Flag
     * |        |          |The ILLEGAL_CMD_SEQ field indicates that the SOFTWARE Driver has executed an illegal command sequence.
     * |        |          |0 = (ILLEGAL_CMD_SEQ _0): no failure.
     * |        |          |1 = (ILLEGAL_CMD_SEQ _1): Executed an illegal command sequence.
     * |[5]     |FAILED_SEED_ST_HT|FAILED_SEED_ST_HT Error Flag
     * |        |          |The FAILED_SEED_ST_HT field indicates that the statistical tests applied on the entropy source output is failed (Only valid when entropy source output statistical health test feature is included).
     * |        |          |0 = (FAILED_SEED_ST_HT_0): no failure.
     * |        |          |1 = (FAILED_SEED_ST_HT_1): Entropy source health test is failed.
     * @var TRNG_T::COREKIT_REL
     * Offset: 0x1C  Contains the static coreKit release information.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |REL_NUM   |The CoreKit Release Version In Pseudo-BCD
     * |        |          |For example, release '2.35e-lca04' is encoded as 0x235e.
     * |        |          |This TRNG version is 0x300a.
     * |[23:16] |EXT_VER   |The CoreKit Release Extension Version Number
     * |        |          |For example, release '2.35e-lp04' is encoded as 0x4.
     * |        |          |GA releases has a value of 0.
     * |[31:28] |EXT_ENUM  |The CoreKit Release Extension Type
     * |        |          |For example, release '2.35e-lca04' is encoded as 0x1.
     * |        |          |0000 = (EXT_ENUM_GA): GA release.
     * |        |          |0001 = (EXT_ENUM_LCA): LCA release.
     * |        |          |0010 = (EXT_ENUM_EA): EA release.
     * |        |          |0011 = (EXT_ENUM_LP): LP release.
     * |        |          |0100 = (EXT_ENUM_LPC): LPC release.
     * |        |          |0101 = (EXT_ENUM_SOW): SOW release.
     * |        |          |Others = Reserved.
     * @var TRNG_T::FEATURES
     * Offset: 0x20  The FEATURES register returns the state of various build-time parameter values.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SECURE_RST_STATE|The Core Resets to MISSION or TEST Mode
     * |        |          |0 = test mode.
     * |        |          |1 = mission mode.
     * |[3:1]   |DIAG_LEVEL_ST_HLT|Level Of Diagnostic Circuitry For The Health Test
     * |[6:4]   |DIAG_LEVEL_CLP800|Level Of Diagnostic Circuitry For TRNG When Noise Source
     * |[7]     |DIAG_LEVEL_NS|Level Of Diagnostic Circuitry For Noise Source Output Registers
     * |[8]     |PS_PRESENT|The NPA_DATAx Registers Is used As A Personalization String During The Create_State Command
     * |        |          |0 = No.
     * |        |          |1 = Yes.
     * |[9]     |AES_256   |The Instantiated AES
     * |        |          |0 = AES-128.
     * |        |          |1 = AES-256.
     * @var TRNG_T::RAND0
     * Offset: 0x24  The RAND0 register is used by the host to read bits [31:0] of the newly generated 128-bit random data.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |RAND      |Random Data Word
     * @var TRNG_T::RAND1
     * Offset: 0x28  The RAND1 register is used by the host to read bits [63:32] of the newly generated 128-bit random data.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |RAND      |Random Data Word
     * @var TRNG_T::RAND2
     * Offset: 0x2C  The RAND2 register is used by the host to read bits [95:64] of the newly generated 128-bit random data.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |RAND      |Random Data Word
     * @var TRNG_T::RAND3
     * Offset: 0x30  The RAND3 register is used by the host to read bits [127:96] of the newly generated 128-bit random data.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |RAND      |Random Data Word
     * @var TRNG_T::NPA_DATA0
     * Offset: 0x34  The NPA_DATA0 register holds Noise/Nonce/Personalization String/Additional Input - bits [31:0].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA1
     * Offset: 0x38  The NPA_DATA1 register holds Noise/Nonce/Personalization String/Additional Input - bits [63:32].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA2
     * Offset: 0x3C  The NPA_DATA2 register holds Noise/Nonce/Personalization String/Additional Input - bits [95:64].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA3
     * Offset: 0x40  The NPA_DATA3 register holds Noise/Nonce/Personalization String/Additional Input - bits [127:96].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA4
     * Offset: 0x44  The NPA_DATA4 register holds Noise/Nonce/Personalization String/Additional Input - bits [159:128].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA5
     * Offset: 0x48  The NPA_DATA5 register holds Noise/Nonce/Personalization String/Additional Input - bits [191:160].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA6
     * Offset: 0x4C  The NPA_DATA6 register holds Noise/Nonce/Personalization String/Additional Input - bits [223:192].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA7
     * Offset: 0x50  The NPA_DATA7 register holds Noise/Nonce/Personalization String/Additional Input - bits [255:224].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA8
     * Offset: 0x54  The NPA_DATA8 register holds Noise/Nonce/Personalization String/Additional Input - bits [287:256].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA9
     * Offset: 0x58  The NPA_DATA9 register holds Noise/Nonce/Personalization String/Additional Input - bits [319:288].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA10
     * Offset: 0x5C  The NPA_DATA10 register holds Noise/Nonce/Personalization String/Additional Input - bits [351:320].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA11
     * Offset: 0x60  The NPA_DATA11 register holds Noise/Nonce/Personalization String/Additional Input - bits [383:352].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA12
     * Offset: 0x64  The NPA_DATA12 register holds Noise/Nonce - bits [415:384].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA13
     * Offset: 0x68  The NPA_DATA13 register holds Noise/Nonce - bits [447:416].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA14
     * Offset: 0x6C  The NPA_DATA14 register holds Noise/Nonce - bits [479:448].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::NPA_DATA15
     * Offset: 0x70  The NPA_DATA15 register holds Noise/Nonce - bits [511:480].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |NPA_DATA  |NPA data word
     * |        |          |Noise/Nonce can be stored in register NPA_DATA0 ~ NPA_DATA15.
     * |        |          |Personalization String/Additional Input can be stored in register NPA_DATA0 ~ NPA_DATA11.
     * @var TRNG_T::SEED0
     * Offset: 0x74  The SEED0 register holds seed value used in the DRBG - bits [31:0].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED1
     * Offset: 0x78  The SEED1 register holds seed value used in the DRBG - bits [63:32].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED2
     * Offset: 0x7C  The SEED2 register holds seed value used in the DRBG - bits [95:64].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED3
     * Offset: 0x80  The SEED3 register holds seed value used in the DRBG - bits [127:96].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED4
     * Offset: 0x84  The SEED4 register holds seed value used in the DRBG - bits [159:128].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED5
     * Offset: 0x88  The SEED5 register holds seed value used in the DRBG - bits [191:160].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED6
     * Offset: 0x8C  The SEED6 register holds seed value used in the DRBG - bits [223:192].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED7
     * Offset: 0x90  The SEED7 register holds seed value used in the DRBG - bits [255:224].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED8
     * Offset: 0x94  The SEED8 register holds seed value used in the DRBG - bits [287:256].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED9
     * Offset: 0x98  The SEED9 register holds seed value used in the DRBG - bits [319:288].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED10
     * Offset: 0x9C  The SEED10 register holds seed value used in the DRBG - bits [351:320].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::SEED11
     * Offset: 0xA0  The SEED11 register holds seed value used in the DRBG - bits [383:352].
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |SEED data word
     * @var TRNG_T::TIME_TO_SEED
     * Offset: 0xD0  The Time-to-Seed (TTS) register records the number of clock cycles taken to collect the set of raw noise bits used by the previous GEN_NOISE command.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |TTS       |TRNG Time To Seed Shows the number of system clock cycles taken to generate raw noise for the last GEN_NOISE command.
     * @var TRNG_T::BUILD_CFG0
     * Offset: 0xF0  Contains build-time TRNG NIST parameter settings.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |CORE_TYPE |Core Type
     * |        |          |00 = (CORE_TYPE_BASE_TRNG): TRNG.
     * |        |          |01 = (CORE_TYPE_BASE_TRNG_WITH_ESM_NONCE): TRNG with ESM nonce I/O.
     * |        |          |10 = (CORE_TYPE_NIST_TRNG): TRNG NIST.
     * |        |          |11 = (CORE_TYPE_NIST_TRNG_WITH_EDU): TRNG NIST with EDU.
     * |[7]     |BG8       |Indicates Number Of Bit Generators Present
     * |        |          |0 = (SIX_BGS): 6 Bit Generators present.
     * |        |          |1 = (EIGHT_BGS): 8 Bit Generators present..
     * |[9:8]   |CDC_SYNC_DEPTH|Depth Of The CDC Resynchronizer Chains
     * |        |          |00 = (CDC_RESYNC_4): CDC resynchronizer depth 4.
     * |        |          |01 = Reserved.
     * |        |          |10 = (CDC_RESYNC_2): CDC resynchronizer depth 2.
     * |        |          |11 = (CDC_RESYNC_3): CDC resynchronizer depth 3.
     * |[10]    |BACKGROUND_NOISE|Indicates Background Noise Collection Is Present
     * |        |          |0 = (BACKGROUND_NOISE _NOT_PRESENT): not present.
     * |        |          |1 = (BACKGROUND_NOISE_PRESENT): present..
     * |[11]    |EDU_PRESENT|Indicates EDU Is Present
     * |        |          |0 = (EDU_PRESENT_NOT_PRESENT): not present.
     * |        |          |1 = (EDU_PRESENT_PRESENT): present..
     * |[12]    |AES_DATAPATH|AES Datapath Width
     * |        |          |0 = (AES_DATAPATH_32): 32-bit datapath.
     * |        |          |1 = (AES_DATAPATH_128): 128-bit datapath.
     * |[13]    |AES_MAX_KEY_SIZE|AES Max Key Size
     * |        |          |0 = (AES_MAX_KEY_SIZE_128): 128-bit key.
     * |        |          |1 = (AES_MAX_KEY_SIZE_256): 256-bit key.
     * |[14]    |PERSONALIZATION_STR|Personalization String Used
     * |        |          |0 = (PS_NOT_PRESENT): not present.
     * |        |          |1 = (PS_PRESENT): present.
     * @var TRNG_T::BUILD_CFG1
     * Offset: 0xF4  Contains additional build-time TRNG NIST parameter settings.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |NUM_RAW_NOISE_BLKS|Number of Raw Noise Blocks Used for Start-up Test
     * |[8]     |STICKY_STARTUP|Sticky-startup Test Present
     * |        |          |0 = (STICKY_STARTUP_TEST_NOT_PRESENT): not present.
     * |        |          |1 = (STICKY_STARTUP_TEST_PRESENT): present.
     * |[12]    |AUTO_CORRELATION_TEST|Auto-correlation Test Present
     * |        |          |0 = (AUTO_CORRELATION_TEST_NOT_PRESENT): not present.
     * |        |          |1 = (AUTO_CORRELATION_TEST_PRESENT): present.
     * |[13]    |MONOBIT_TEST|Monobit Test Present
     * |        |          |0 = (MONOBIT_TEST_NOT_PRESENT): not present.
     * |        |          |1 = (MONOBIT_TEST_PRESENT): present.
     * |[14]    |RUN_TEST  |Run Test Present
     * |        |          |0 = (RUN_TEST_NOT_PRESENT): not present.
     * |        |          |1 = (RUN_TEST_PRESENT): present.
     * |[15]    |POKER_TEST|Poker Test Present
     * |        |          |0 = (POKER_TEST_NOT_PRESENT): not present.
     * |        |          |1 = (POKER_TEST_PRESENT): present.
     * |[18:16] |RAW_HT_ADAP_TEST|Raw Health Adaptive Proportion Test
     * |        |          |000 = (RAW_HT_ADAP_TEST_NOT_PRESENT): not present.
     * |        |          |001 = (RAW_HT_ADAP_TEST_1K_SAMPLES): 1k samples per window.
     * |        |          |010 = (RAW_HT_ADAP_TEST_2K_SAMPLES): 2k samples per window.
     * |        |          |011 = (RAW_HT_ADAP_TEST_4K_SAMPLES): 4k samples per window.
     * |        |          |100 = (RAW_HT_ADAP_TEST_8K_SAMPLES): 8k samples per window.
     * |        |          |101 = (RAW_HT_ADAP_TEST_16K_SAMPLES): 16k samples per window.
     * |        |          |110 = (RAW_HT_ADAP_TEST_32K_SAMPLES): 32k samples per window.
     * |        |          |111 = (RAW_HT_ADAP_TEST_64K_SAMPLES): 64k samples per window.
     * |[19]    |RAW_HT_REP_TEST|Raw Health Repetition Test Present
     * |        |          |0 = (RAW_HT_REP_TEST_NOT_PRESENT): not present.
     * |        |          |1 = (RAW_HT_REP_TEST_PRESENT): present.
     * |[22:20] |ENT_SRC_REP_SMPL_SIZE|Entropy Source: Sample Size
     * |        |          |000 = (ENT_SRC_REP_SMPL_SIZE_1): Sample size 1.
     * |        |          |001 = (ENT_SRC_REP_SMPL_SIZE_2): Sample size 2.
     * |        |          |010 = (ENT_SRC_REP_SMPL_SIZE_4): Sample size 4.
     * |        |          |011 = (ENT_SRC_REP_SMPL_SIZE_8): Sample size 8.
     * |        |          |100 = (ENT_SRC_REP_SMPL_SIZE_16): Sample size 16.
     * |        |          |101 = (ENT_SRC_REP_SMPL_SIZE_32): Sample size 32.
     * |        |          |110 = (ENT_SRC_REP_SMPL_SIZE_64): Sample size 64.
     * |        |          |111 = (ENT_SRC_REP_SMPL_SIZE_128): Sample size 128.
     * |[23]    |ENT_SRC_REP_TEST|Entropy Source Repetition Test Present
     * |        |          |0 = (ENT_SRC_REP_TEST_NOT_PRESENT): not present.
     * |        |          |1 = (ENT_SRC_REP_TEST_PRESENT): present.
     * |[30:24] |ENT_SRC_REP_MIN_ENTROPY|Entropy Source Repetition Minimum Entropy Per Bit
     */
    __O  uint32_t CTL;                   /*!< [0x0000] The CTRL register is used to cause the TRNG NIST to execute one of a number of actions. */
    __IO uint32_t MODE;                  /*!< [0x0004] The MODE register is used to enable or disable certain run-time features within the TRNG NIST. */
    __IO uint32_t SMODE;                 /*!< [0x0008] The SMODE register is used to enable or disable certain MISSION mode run-time features. */
    __I  uint32_t STAT;                  /*!< [0x000c] The STAT register allows the user to monitor the internal status of the TRNG NIST. */
    __IO uint32_t IE;                    /*!< [0x0010] The IE register is used to enable or disable interrupts within the TRNG NIST. */
    __IO uint32_t ISTAT;                 /*!< [0x0014] The ISTAT register allows the user to monitor the interrupt contributions of the TRNG NIST. */
    __IO uint32_t ALARMS;                /*!< [0x0018] The ALARMS register allows the user to monitor the source of critical alarms. */
    __I  uint32_t COREKIT_REL;           /*!< [0x001c] Contains the static coreKit release information.                 */
    __I  uint32_t FEATURES;              /*!< [0x0020] The FEATURES register returns the state of various build-time parameter values. */
    __I  uint32_t RAND0;                 /*!< [0x0024] The RAND0 register is used by the host to read bits [31:0] of the newly generated 128-bit random data. */
    __I  uint32_t RAND1;                 /*!< [0x0028] The RAND1 register is used by the host to read bits [63:32] of the newly generated 128-bit random data. */
    __I  uint32_t RAND2;                 /*!< [0x002c] The RAND2 register is used by the host to read bits [95:64] of the newly generated 128-bit random data. */
    __I  uint32_t RAND3;                 /*!< [0x0030] The RAND3 register is used by the host to read bits [127:96] of the newly generated 128-bit random data. */
    __IO uint32_t NPA_DATA0;             /*!< [0x0034] The NPA_DATA0 register holds Noise/Nonce/Personalization String/Additional Input - bits [31:0]. */
    __IO uint32_t NPA_DATA1;             /*!< [0x0038] The NPA_DATA1 register holds Noise/Nonce/Personalization String/Additional Input - bits [63:32]. */
    __IO uint32_t NPA_DATA2;             /*!< [0x003c] The NPA_DATA2 register holds Noise/Nonce/Personalization String/Additional Input - bits [95:64]. */
    __IO uint32_t NPA_DATA3;             /*!< [0x0040] The NPA_DATA3 register holds Noise/Nonce/Personalization String/Additional Input - bits [127:96]. */
    __IO uint32_t NPA_DATA4;             /*!< [0x0044] The NPA_DATA4 register holds Noise/Nonce/Personalization String/Additional Input - bits [159:128]. */
    __IO uint32_t NPA_DATA5;             /*!< [0x0048] The NPA_DATA5 register holds Noise/Nonce/Personalization String/Additional Input - bits [191:160]. */
    __IO uint32_t NPA_DATA6;             /*!< [0x004c] The NPA_DATA6 register holds Noise/Nonce/Personalization String/Additional Input - bits [223:192]. */
    __IO uint32_t NPA_DATA7;             /*!< [0x0050] The NPA_DATA7 register holds Noise/Nonce/Personalization String/Additional Input - bits [255:224]. */
    __IO uint32_t NPA_DATA8;             /*!< [0x0054] The NPA_DATA8 register holds Noise/Nonce/Personalization String/Additional Input - bits [287:256]. */
    __IO uint32_t NPA_DATA9;             /*!< [0x0058] The NPA_DATA9 register holds Noise/Nonce/Personalization String/Additional Input - bits [319:288]. */
    __IO uint32_t NPA_DATA10;            /*!< [0x005c] The NPA_DATA10 register holds Noise/Nonce/Personalization String/Additional Input - bits [351:320]. */
    __IO uint32_t NPA_DATA11;            /*!< [0x0060] The NPA_DATA11 register holds Noise/Nonce/Personalization String/Additional Input - bits [383:352]. */
    __IO uint32_t NPA_DATA12;            /*!< [0x0064] The NPA_DATA12 register holds Noise/Nonce - bits [415:384].      */
    __IO uint32_t NPA_DATA13;            /*!< [0x0068] The NPA_DATA13 register holds Noise/Nonce - bits [447:416].      */
    __IO uint32_t NPA_DATA14;            /*!< [0x006c] The NPA_DATA14 register holds Noise/Nonce - bits [479:448].      */
    __IO uint32_t NPA_DATA15;            /*!< [0x0070] The NPA_DATA15 register holds Noise/Nonce - bits [511:480].      */
    __IO uint32_t SEED0;                 /*!< [0x0074] The SEED0 register holds seed value used in the DRBG - bits [31:0]. */
    __IO uint32_t SEED1;                 /*!< [0x0078] The SEED1 register holds seed value used in the DRBG - bits [63:32]. */
    __IO uint32_t SEED2;                 /*!< [0x007c] The SEED2 register holds seed value used in the DRBG - bits [95:64]. */
    __IO uint32_t SEED3;                 /*!< [0x0080] The SEED3 register holds seed value used in the DRBG - bits [127:96]. */
    __IO uint32_t SEED4;                 /*!< [0x0084] The SEED4 register holds seed value used in the DRBG - bits [159:128]. */
    __IO uint32_t SEED5;                 /*!< [0x0088] The SEED5 register holds seed value used in the DRBG - bits [191:160]. */
    __IO uint32_t SEED6;                 /*!< [0x008c] The SEED6 register holds seed value used in the DRBG - bits [223:192]. */
    __IO uint32_t SEED7;                 /*!< [0x0090] The SEED7 register holds seed value used in the DRBG - bits [255:224]. */
    __IO uint32_t SEED8;                 /*!< [0x0094] The SEED8 register holds seed value used in the DRBG - bits [287:256]. */
    __IO uint32_t SEED9;                 /*!< [0x0098] The SEED9 register holds seed value used in the DRBG - bits [319:288]. */
    __IO uint32_t SEED10;                /*!< [0x009c] The SEED10 register holds seed value used in the DRBG - bits [351:320]. */
    __IO uint32_t SEED11;                /*!< [0x00a0] The SEED11 register holds seed value used in the DRBG - bits [383:352]. */
    __I  uint32_t RESERVE0[11];
    __I  uint32_t TIME_TO_SEED;          /*!< [0x00d0] The Time-to-Seed (TTS) register records the number of clock cycles taken to collect the set of raw noise bits used by the previous GEN_NOISE command. */
    __I  uint32_t RESERVE1[7];
    __I  uint32_t BUILD_CFG0;            /*!< [0x00f0] Contains build-time TRNG NIST parameter settings.                */
    __I  uint32_t BUILD_CFG1;            /*!< [0x00f4] Contains additional build-time TRNG NIST parameter settings.     */

} TRNG_T;

/**
    @addtogroup TRNG_CONST TRNG Bit Field Definition
    Constant Definitions for TRNG Controller
@{ */

#define TRNG_CTL_CMD_Pos                 (0)                                               /*!< TRNG_T::CTL: CMD Position              */
#define TRNG_CTL_CMD_Msk                 (0xful << TRNG_CTL_CMD_Pos)                       /*!< TRNG_T::CTL: CMD Mask                  */

#define TRNG_MODE_SEC_ALG_Pos            (0)                                               /*!< TRNG_T::MODE: SEC_ALG Position         */
#define TRNG_MODE_SEC_ALG_Msk            (0x1ul << TRNG_MODE_SEC_ALG_Pos)                  /*!< TRNG_T::MODE: SEC_ALG Mask             */

#define TRNG_MODE_PRED_RESIST_Pos        (3)                                               /*!< TRNG_T::MODE: PRED_RESIST Position     */
#define TRNG_MODE_PRED_RESIST_Msk        (0x1ul << TRNG_MODE_PRED_RESIST_Pos)              /*!< TRNG_T::MODE: PRED_RESIST Mask         */

#define TRNG_MODE_ADDIN_PRESENT_Pos      (4)                                               /*!< TRNG_T::MODE: ADDIN_PRESENT Position   */
#define TRNG_MODE_ADDIN_PRESENT_Msk      (0x1ul << TRNG_MODE_ADDIN_PRESENT_Pos)            /*!< TRNG_T::MODE: ADDIN_PRESENT Mask       */

#define TRNG_MODE_KAT_VEC_Pos            (5)                                               /*!< TRNG_T::MODE: KAT_VEC Position         */
#define TRNG_MODE_KAT_VEC_Msk            (0x3ul << TRNG_MODE_KAT_VEC_Pos)                  /*!< TRNG_T::MODE: KAT_VEC Mask             */

#define TRNG_MODE_KAT_SEL_Pos            (7)                                               /*!< TRNG_T::MODE: KAT_SEL Position         */
#define TRNG_MODE_KAT_SEL_Msk            (0x3ul << TRNG_MODE_KAT_SEL_Pos)                  /*!< TRNG_T::MODE: KAT_SEL Mask             */

#define TRNG_SMODE_NONCE_Pos             (0)                                               /*!< TRNG_T::SMODE: NONCE Position          */
#define TRNG_SMODE_NONCE_Msk             (0x1ul << TRNG_SMODE_NONCE_Pos)                   /*!< TRNG_T::SMODE: NONCE Mask              */

#define TRNG_SMODE_MISSION_MODE_Pos      (1)                                               /*!< TRNG_T::SMODE: MISSION_MODE Position   */
#define TRNG_SMODE_MISSION_MODE_Msk      (0x1ul << TRNG_SMODE_MISSION_MODE_Pos)            /*!< TRNG_T::SMODE: MISSION_MODE Mask       */

#define TRNG_SMODE_MAX_REJECTS_Pos       (2)                                               /*!< TRNG_T::SMODE: MAX_REJECTS Position    */
#define TRNG_SMODE_MAX_REJECTS_Msk       (0xfful << TRNG_SMODE_MAX_REJECTS_Pos)            /*!< TRNG_T::SMODE: MAX_REJECTS Mask        */

#define TRNG_SMODE_INDIV_HT_DISABLE_Pos  (16)                                              /*!< TRNG_T::SMODE: INDIV_HT_DISABLE Position*/
#define TRNG_SMODE_INDIV_HT_DISABLE_Msk  (0xfful << TRNG_SMODE_INDIV_HT_DISABLE_Pos)       /*!< TRNG_T::SMODE: INDIV_HT_DISABLE Mask   */

#define TRNG_SMODE_NOISE_COLLECT_Pos     (31)                                              /*!< TRNG_T::SMODE: NOISE_COLLECT Position  */
#define TRNG_SMODE_NOISE_COLLECT_Msk     (0x1ul << TRNG_SMODE_NOISE_COLLECT_Pos)           /*!< TRNG_T::SMODE: NOISE_COLLECT Mask      */

#define TRNG_STAT_LAST_CMD_Pos           (0)                                               /*!< TRNG_T::STAT: LAST_CMD Position        */
#define TRNG_STAT_LAST_CMD_Msk           (0xful << TRNG_STAT_LAST_CMD_Pos)                 /*!< TRNG_T::STAT: LAST_CMD Mask            */

#define TRNG_STAT_SEC_ALG_Pos            (4)                                               /*!< TRNG_T::STAT: SEC_ALG Position         */
#define TRNG_STAT_SEC_ALG_Msk            (0x1ul << TRNG_STAT_SEC_ALG_Pos)                  /*!< TRNG_T::STAT: SEC_ALG Mask             */

#define TRNG_STAT_NONCE_MODE_Pos         (5)                                               /*!< TRNG_T::STAT: NONCE_MODE Position      */
#define TRNG_STAT_NONCE_MODE_Msk         (0x1ul << TRNG_STAT_NONCE_MODE_Pos)               /*!< TRNG_T::STAT: NONCE_MODE Mask          */

#define TRNG_STAT_MISSION_MODE_Pos       (6)                                               /*!< TRNG_T::STAT: MISSION_MODE Position    */
#define TRNG_STAT_MISSION_MODE_Msk       (0x1ul << TRNG_STAT_MISSION_MODE_Pos)             /*!< TRNG_T::STAT: MISSION_MODE Mask        */

#define TRNG_STAT_DRBG_STATE_Pos         (7)                                               /*!< TRNG_T::STAT: DRBG_STATE Position      */
#define TRNG_STAT_DRBG_STATE_Msk         (0x3ul << TRNG_STAT_DRBG_STATE_Pos)               /*!< TRNG_T::STAT: DRBG_STATE Mask          */

#define TRNG_STAT_STARTUP_TEST_STUCK_Pos (9)                                               /*!< TRNG_T::STAT: STARTUP_TEST_STUCK Position*/
#define TRNG_STAT_STARTUP_TEST_STUCK_Msk (0x1ul << TRNG_STAT_STARTUP_TEST_STUCK_Pos)       /*!< TRNG_T::STAT: STARTUP_TEST_STUCK Mask  */

#define TRNG_STAT_STARTUP_TEST_IN_PROG_Pos (10)                                            /*!< TRNG_T::STAT: STARTUP_TEST_IN_PROG Position*/
#define TRNG_STAT_STARTUP_TEST_IN_PROG_Msk (0x1ul << TRNG_STAT_STARTUP_TEST_IN_PROG_Pos)   /*!< TRNG_T::STAT: STARTUP_TEST_IN_PROG Mask*/

#define TRNG_STAT_BUSY_Pos               (31)                                              /*!< TRNG_T::STAT: BUSY Position            */
#define TRNG_STAT_BUSY_Msk               (0x1ul << TRNG_STAT_BUSY_Pos)                     /*!< TRNG_T::STAT: BUSY Mask                */

#define TRNG_IE_ZEROIZED_Pos             (0)                                               /*!< TRNG_T::IE: ZEROIZED Position          */
#define TRNG_IE_ZEROIZED_Msk             (0x1ul << TRNG_IE_ZEROIZED_Pos)                   /*!< TRNG_T::IE: ZEROIZED Mask              */

#define TRNG_IE_KAT_COMPLETED_Pos        (1)                                               /*!< TRNG_T::IE: KAT_COMPLETED Position     */
#define TRNG_IE_KAT_COMPLETED_Msk        (0x1ul << TRNG_IE_KAT_COMPLETED_Pos)              /*!< TRNG_T::IE: KAT_COMPLETED Mask         */

#define TRNG_IE_NOISE_RDY_Pos            (2)                                               /*!< TRNG_T::IE: NOISE_RDY Position         */
#define TRNG_IE_NOISE_RDY_Msk            (0x1ul << TRNG_IE_NOISE_RDY_Pos)                  /*!< TRNG_T::IE: NOISE_RDY Mask             */

#define TRNG_IE_ALARMS_Pos               (3)                                               /*!< TRNG_T::IE: ALARMS Position            */
#define TRNG_IE_ALARMS_Msk               (0x1ul << TRNG_IE_ALARMS_Pos)                     /*!< TRNG_T::IE: ALARMS Mask                */

#define TRNG_IE_DONE_Pos                 (4)                                               /*!< TRNG_T::IE: DONE Position              */
#define TRNG_IE_DONE_Msk                 (0x1ul << TRNG_IE_DONE_Pos)                       /*!< TRNG_T::IE: DONE Mask                  */

#define TRNG_IE_GLBL_Pos                 (31)                                              /*!< TRNG_T::IE: GLBL Position              */
#define TRNG_IE_GLBL_Msk                 (0x1ul << TRNG_IE_GLBL_Pos)                       /*!< TRNG_T::IE: GLBL Mask                  */

#define TRNG_ISTAT_ZEROIZED_Pos          (0)                                               /*!< TRNG_T::ISTAT: ZEROIZED Position       */
#define TRNG_ISTAT_ZEROIZED_Msk          (0x1ul << TRNG_ISTAT_ZEROIZED_Pos)                /*!< TRNG_T::ISTAT: ZEROIZED Mask           */

#define TRNG_ISTAT_KAT_COMPLETED_Pos     (1)                                               /*!< TRNG_T::ISTAT: KAT_COMPLETED Position  */
#define TRNG_ISTAT_KAT_COMPLETED_Msk     (0x1ul << TRNG_ISTAT_KAT_COMPLETED_Pos)           /*!< TRNG_T::ISTAT: KAT_COMPLETED Mask      */

#define TRNG_ISTAT_NOISE_RDY_Pos         (2)                                               /*!< TRNG_T::ISTAT: NOISE_RDY Position      */
#define TRNG_ISTAT_NOISE_RDY_Msk         (0x1ul << TRNG_ISTAT_NOISE_RDY_Pos)               /*!< TRNG_T::ISTAT: NOISE_RDY Mask          */

#define TRNG_ISTAT_ALARMS_Pos            (3)                                               /*!< TRNG_T::ISTAT: ALARMS Position         */
#define TRNG_ISTAT_ALARMS_Msk            (0x1ul << TRNG_ISTAT_ALARMS_Pos)                  /*!< TRNG_T::ISTAT: ALARMS Mask             */

#define TRNG_ISTAT_DONE_Pos              (4)                                               /*!< TRNG_T::ISTAT: DONE Position           */
#define TRNG_ISTAT_DONE_Msk              (0x1ul << TRNG_ISTAT_DONE_Pos)                    /*!< TRNG_T::ISTAT: DONE Mask               */

#define TRNG_ALARMS_FAILED_TEST_ID_Pos   (0)                                               /*!< TRNG_T::ALARMS: FAILED_TEST_ID Position*/
#define TRNG_ALARMS_FAILED_TEST_ID_Msk   (0xful << TRNG_ALARMS_FAILED_TEST_ID_Pos)         /*!< TRNG_T::ALARMS: FAILED_TEST_ID Mask    */

#define TRNG_ALARMS_ILLEGAL_CMD_SEQ_Pos  (4)                                               /*!< TRNG_T::ALARMS: ILLEGAL_CMD_SEQ Position*/
#define TRNG_ALARMS_ILLEGAL_CMD_SEQ_Msk  (0x1ul << TRNG_ALARMS_ILLEGAL_CMD_SEQ_Pos)        /*!< TRNG_T::ALARMS: ILLEGAL_CMD_SEQ Mask   */

#define TRNG_ALARMS_FAILED_SEED_ST_HT_Pos (5)                                              /*!< TRNG_T::ALARMS: FAILED_SEED_ST_HT Position*/
#define TRNG_ALARMS_FAILED_SEED_ST_HT_Msk (0x1ul << TRNG_ALARMS_FAILED_SEED_ST_HT_Pos)     /*!< TRNG_T::ALARMS: FAILED_SEED_ST_HT Mask */

#define TRNG_COREKIT_REL_REL_NUM_Pos     (0)                                               /*!< TRNG_T::COREKIT_REL: REL_NUM Position  */
#define TRNG_COREKIT_REL_REL_NUM_Msk     (0xfffful << TRNG_COREKIT_REL_REL_NUM_Pos)        /*!< TRNG_T::COREKIT_REL: REL_NUM Mask      */

#define TRNG_COREKIT_REL_EXT_VER_Pos     (16)                                              /*!< TRNG_T::COREKIT_REL: EXT_VER Position  */
#define TRNG_COREKIT_REL_EXT_VER_Msk     (0xfful << TRNG_COREKIT_REL_EXT_VER_Pos)          /*!< TRNG_T::COREKIT_REL: EXT_VER Mask      */

#define TRNG_COREKIT_REL_EXT_ENUM_Pos    (28)                                              /*!< TRNG_T::COREKIT_REL: EXT_ENUM Position */
#define TRNG_COREKIT_REL_EXT_ENUM_Msk    (0xful << TRNG_COREKIT_REL_EXT_ENUM_Pos)          /*!< TRNG_T::COREKIT_REL: EXT_ENUM Mask     */

#define TRNG_FEATURES_SECURE_RST_STATE_Pos (0)                                             /*!< TRNG_T::FEATURES: SECURE_RST_STATE Position*/
#define TRNG_FEATURES_SECURE_RST_STATE_Msk (0x1ul << TRNG_FEATURES_SECURE_RST_STATE_Pos)   /*!< TRNG_T::FEATURES: SECURE_RST_STATE Mask*/

#define TRNG_FEATURES_DIAG_LEVEL_ST_HLT_Pos (1)                                            /*!< TRNG_T::FEATURES: DIAG_LEVEL_ST_HLT Position*/
#define TRNG_FEATURES_DIAG_LEVEL_ST_HLT_Msk (0x7ul << TRNG_FEATURES_DIAG_LEVEL_ST_HLT_Pos) /*!< TRNG_T::FEATURES: DIAG_LEVEL_ST_HLT Mask*/

#define TRNG_FEATURES_DIAG_LEVEL_CLP800_Pos (4)                                            /*!< TRNG_T::FEATURES: DIAG_LEVEL_CLP800 Position*/
#define TRNG_FEATURES_DIAG_LEVEL_CLP800_Msk (0x7ul << TRNG_FEATURES_DIAG_LEVEL_CLP800_Pos) /*!< TRNG_T::FEATURES: DIAG_LEVEL_CLP800 Mask*/

#define TRNG_FEATURES_DIAG_LEVEL_NS_Pos  (7)                                               /*!< TRNG_T::FEATURES: DIAG_LEVEL_NS Position*/
#define TRNG_FEATURES_DIAG_LEVEL_NS_Msk  (0x1ul << TRNG_FEATURES_DIAG_LEVEL_NS_Pos)        /*!< TRNG_T::FEATURES: DIAG_LEVEL_NS Mask   */

#define TRNG_FEATURES_PS_PRESENT_Pos     (8)                                               /*!< TRNG_T::FEATURES: PS_PRESENT Position  */
#define TRNG_FEATURES_PS_PRESENT_Msk     (0x1ul << TRNG_FEATURES_PS_PRESENT_Pos)           /*!< TRNG_T::FEATURES: PS_PRESENT Mask      */

#define TRNG_FEATURES_AES_256_Pos        (9)                                               /*!< TRNG_T::FEATURES: AES_256 Position     */
#define TRNG_FEATURES_AES_256_Msk        (0x1ul << TRNG_FEATURES_AES_256_Pos)              /*!< TRNG_T::FEATURES: AES_256 Mask         */

#define TRNG_RAND0_RAND_Pos              (0)                                               /*!< TRNG_T::RAND0: RAND Position           */
#define TRNG_RAND0_RAND_Msk              (0xfffffffful << TRNG_RAND0_RAND_Pos)             /*!< TRNG_T::RAND0: RAND Mask               */

#define TRNG_RAND1_RAND_Pos              (0)                                               /*!< TRNG_T::RAND1: RAND Position           */
#define TRNG_RAND1_RAND_Msk              (0xfffffffful << TRNG_RAND1_RAND_Pos)             /*!< TRNG_T::RAND1: RAND Mask               */

#define TRNG_RAND2_RAND_Pos              (0)                                               /*!< TRNG_T::RAND2: RAND Position           */
#define TRNG_RAND2_RAND_Msk              (0xfffffffful << TRNG_RAND2_RAND_Pos)             /*!< TRNG_T::RAND2: RAND Mask               */

#define TRNG_RAND3_RAND_Pos              (0)                                               /*!< TRNG_T::RAND3: RAND Position           */
#define TRNG_RAND3_RAND_Msk              (0xfffffffful << TRNG_RAND3_RAND_Pos)             /*!< TRNG_T::RAND3: RAND Mask               */

#define TRNG_NPA_DATA0_NPA_DATA_Pos      (0)                                               /*!< TRNG_T::NPA_DATA0: NPA_DATA Position   */
#define TRNG_NPA_DATA0_NPA_DATA_Msk      (0xfffffffful << TRNG_NPA_DATA0_NPA_DATA_Pos)     /*!< TRNG_T::NPA_DATA0: NPA_DATA Mask       */

#define TRNG_NPA_DATA1_NPA_DATA_Pos      (0)                                               /*!< TRNG_T::NPA_DATA1: NPA_DATA Position   */
#define TRNG_NPA_DATA1_NPA_DATA_Msk      (0xfffffffful << TRNG_NPA_DATA1_NPA_DATA_Pos)     /*!< TRNG_T::NPA_DATA1: NPA_DATA Mask       */

#define TRNG_NPA_DATA2_NPA_DATA_Pos      (0)                                               /*!< TRNG_T::NPA_DATA2: NPA_DATA Position   */
#define TRNG_NPA_DATA2_NPA_DATA_Msk      (0xfffffffful << TRNG_NPA_DATA2_NPA_DATA_Pos)     /*!< TRNG_T::NPA_DATA2: NPA_DATA Mask       */

#define TRNG_NPA_DATA3_NPA_DATA_Pos      (0)                                               /*!< TRNG_T::NPA_DATA3: NPA_DATA Position   */
#define TRNG_NPA_DATA3_NPA_DATA_Msk      (0xfffffffful << TRNG_NPA_DATA3_NPA_DATA_Pos)     /*!< TRNG_T::NPA_DATA3: NPA_DATA Mask       */

#define TRNG_NPA_DATA4_NPA_DATA_Pos      (0)                                               /*!< TRNG_T::NPA_DATA4: NPA_DATA Position   */
#define TRNG_NPA_DATA4_NPA_DATA_Msk      (0xfffffffful << TRNG_NPA_DATA4_NPA_DATA_Pos)     /*!< TRNG_T::NPA_DATA4: NPA_DATA Mask       */

#define TRNG_NPA_DATA5_NPA_DATA_Pos      (0)                                               /*!< TRNG_T::NPA_DATA5: NPA_DATA Position   */
#define TRNG_NPA_DATA5_NPA_DATA_Msk      (0xfffffffful << TRNG_NPA_DATA5_NPA_DATA_Pos)     /*!< TRNG_T::NPA_DATA5: NPA_DATA Mask       */

#define TRNG_NPA_DATA6_NPA_DATA_Pos      (0)                                               /*!< TRNG_T::NPA_DATA6: NPA_DATA Position   */
#define TRNG_NPA_DATA6_NPA_DATA_Msk      (0xfffffffful << TRNG_NPA_DATA6_NPA_DATA_Pos)     /*!< TRNG_T::NPA_DATA6: NPA_DATA Mask       */

#define TRNG_NPA_DATA7_NPA_DATA_Pos      (0)                                               /*!< TRNG_T::NPA_DATA7: NPA_DATA Position   */
#define TRNG_NPA_DATA7_NPA_DATA_Msk      (0xfffffffful << TRNG_NPA_DATA7_NPA_DATA_Pos)     /*!< TRNG_T::NPA_DATA7: NPA_DATA Mask       */

#define TRNG_NPA_DATA8_NPA_DATA_Pos      (0)                                               /*!< TRNG_T::NPA_DATA8: NPA_DATA Position   */
#define TRNG_NPA_DATA8_NPA_DATA_Msk      (0xfffffffful << TRNG_NPA_DATA8_NPA_DATA_Pos)     /*!< TRNG_T::NPA_DATA8: NPA_DATA Mask       */

#define TRNG_NPA_DATA9_NPA_DATA_Pos      (0)                                               /*!< TRNG_T::NPA_DATA9: NPA_DATA Position   */
#define TRNG_NPA_DATA9_NPA_DATA_Msk      (0xfffffffful << TRNG_NPA_DATA9_NPA_DATA_Pos)     /*!< TRNG_T::NPA_DATA9: NPA_DATA Mask       */

#define TRNG_NPA_DATA10_NPA_DATA_Pos     (0)                                               /*!< TRNG_T::NPA_DATA10: NPA_DATA Position  */
#define TRNG_NPA_DATA10_NPA_DATA_Msk     (0xfffffffful << TRNG_NPA_DATA10_NPA_DATA_Pos)    /*!< TRNG_T::NPA_DATA10: NPA_DATA Mask      */

#define TRNG_NPA_DATA11_NPA_DATA_Pos     (0)                                               /*!< TRNG_T::NPA_DATA11: NPA_DATA Position  */
#define TRNG_NPA_DATA11_NPA_DATA_Msk     (0xfffffffful << TRNG_NPA_DATA11_NPA_DATA_Pos)    /*!< TRNG_T::NPA_DATA11: NPA_DATA Mask      */

#define TRNG_NPA_DATA12_NPA_DATA_Pos     (0)                                               /*!< TRNG_T::NPA_DATA12: NPA_DATA Position  */
#define TRNG_NPA_DATA12_NPA_DATA_Msk     (0xfffffffful << TRNG_NPA_DATA12_NPA_DATA_Pos)    /*!< TRNG_T::NPA_DATA12: NPA_DATA Mask      */

#define TRNG_NPA_DATA13_NPA_DATA_Pos     (0)                                               /*!< TRNG_T::NPA_DATA13: NPA_DATA Position  */
#define TRNG_NPA_DATA13_NPA_DATA_Msk     (0xfffffffful << TRNG_NPA_DATA13_NPA_DATA_Pos)    /*!< TRNG_T::NPA_DATA13: NPA_DATA Mask      */

#define TRNG_NPA_DATA14_NPA_DATA_Pos     (0)                                               /*!< TRNG_T::NPA_DATA14: NPA_DATA Position  */
#define TRNG_NPA_DATA14_NPA_DATA_Msk     (0xfffffffful << TRNG_NPA_DATA14_NPA_DATA_Pos)    /*!< TRNG_T::NPA_DATA14: NPA_DATA Mask      */

#define TRNG_NPA_DATA15_NPA_DATA_Pos     (0)                                               /*!< TRNG_T::NPA_DATA15: NPA_DATA Position  */
#define TRNG_NPA_DATA15_NPA_DATA_Msk     (0xfffffffful << TRNG_NPA_DATA15_NPA_DATA_Pos)    /*!< TRNG_T::NPA_DATA15: NPA_DATA Mask      */

#define TRNG_SEED0_SEED_Pos              (0)                                               /*!< TRNG_T::SEED0: SEED Position           */
#define TRNG_SEED0_SEED_Msk              (0xfffffffful << TRNG_SEED0_SEED_Pos)             /*!< TRNG_T::SEED0: SEED Mask               */

#define TRNG_SEED1_SEED_Pos              (0)                                               /*!< TRNG_T::SEED1: SEED Position           */
#define TRNG_SEED1_SEED_Msk              (0xfffffffful << TRNG_SEED1_SEED_Pos)             /*!< TRNG_T::SEED1: SEED Mask               */

#define TRNG_SEED2_SEED_Pos              (0)                                               /*!< TRNG_T::SEED2: SEED Position           */
#define TRNG_SEED2_SEED_Msk              (0xfffffffful << TRNG_SEED2_SEED_Pos)             /*!< TRNG_T::SEED2: SEED Mask               */

#define TRNG_SEED3_SEED_Pos              (0)                                               /*!< TRNG_T::SEED3: SEED Position           */
#define TRNG_SEED3_SEED_Msk              (0xfffffffful << TRNG_SEED3_SEED_Pos)             /*!< TRNG_T::SEED3: SEED Mask               */

#define TRNG_SEED4_SEED_Pos              (0)                                               /*!< TRNG_T::SEED4: SEED Position           */
#define TRNG_SEED4_SEED_Msk              (0xfffffffful << TRNG_SEED4_SEED_Pos)             /*!< TRNG_T::SEED4: SEED Mask               */

#define TRNG_SEED5_SEED_Pos              (0)                                               /*!< TRNG_T::SEED5: SEED Position           */
#define TRNG_SEED5_SEED_Msk              (0xfffffffful << TRNG_SEED5_SEED_Pos)             /*!< TRNG_T::SEED5: SEED Mask               */

#define TRNG_SEED6_SEED_Pos              (0)                                               /*!< TRNG_T::SEED6: SEED Position           */
#define TRNG_SEED6_SEED_Msk              (0xfffffffful << TRNG_SEED6_SEED_Pos)             /*!< TRNG_T::SEED6: SEED Mask               */

#define TRNG_SEED7_SEED_Pos              (0)                                               /*!< TRNG_T::SEED7: SEED Position           */
#define TRNG_SEED7_SEED_Msk              (0xfffffffful << TRNG_SEED7_SEED_Pos)             /*!< TRNG_T::SEED7: SEED Mask               */

#define TRNG_SEED8_SEED_Pos              (0)                                               /*!< TRNG_T::SEED8: SEED Position           */
#define TRNG_SEED8_SEED_Msk              (0xfffffffful << TRNG_SEED8_SEED_Pos)             /*!< TRNG_T::SEED8: SEED Mask               */

#define TRNG_SEED9_SEED_Pos              (0)                                               /*!< TRNG_T::SEED9: SEED Position           */
#define TRNG_SEED9_SEED_Msk              (0xfffffffful << TRNG_SEED9_SEED_Pos)             /*!< TRNG_T::SEED9: SEED Mask               */

#define TRNG_SEED10_SEED_Pos             (0)                                               /*!< TRNG_T::SEED10: SEED Position          */
#define TRNG_SEED10_SEED_Msk             (0xfffffffful << TRNG_SEED10_SEED_Pos)            /*!< TRNG_T::SEED10: SEED Mask              */

#define TRNG_SEED11_SEED_Pos             (0)                                               /*!< TRNG_T::SEED11: SEED Position          */
#define TRNG_SEED11_SEED_Msk             (0xfffffffful << TRNG_SEED11_SEED_Pos)            /*!< TRNG_T::SEED11: SEED Mask              */

#define TRNG_TIME_TO_SEED_TTS_Pos        (0)                                               /*!< TRNG_T::TIME_TO_SEED: TTS Position     */
#define TRNG_TIME_TO_SEED_TTS_Msk        (0xfffffffful << TRNG_TIME_TO_SEED_TTS_Pos)       /*!< TRNG_T::TIME_TO_SEED: TTS Mask         */

#define TRNG_BUILD_CFG0_CORE_TYPE_Pos    (0)                                               /*!< TRNG_T::BUILD_CFG0: CORE_TYPE Position */
#define TRNG_BUILD_CFG0_CORE_TYPE_Msk    (0x3ul << TRNG_BUILD_CFG0_CORE_TYPE_Pos)          /*!< TRNG_T::BUILD_CFG0: CORE_TYPE Mask     */

#define TRNG_BUILD_CFG0_BG8_Pos          (7)                                               /*!< TRNG_T::BUILD_CFG0: BG8 Position       */
#define TRNG_BUILD_CFG0_BG8_Msk          (0x1ul << TRNG_BUILD_CFG0_BG8_Pos)                /*!< TRNG_T::BUILD_CFG0: BG8 Mask           */

#define TRNG_BUILD_CFG0_CDC_SYNC_DEPTH_Pos (8)                                             /*!< TRNG_T::BUILD_CFG0: CDC_SYNC_DEPTH Position*/
#define TRNG_BUILD_CFG0_CDC_SYNC_DEPTH_Msk (0x3ul << TRNG_BUILD_CFG0_CDC_SYNC_DEPTH_Pos)   /*!< TRNG_T::BUILD_CFG0: CDC_SYNC_DEPTH Mask*/

#define TRNG_BUILD_CFG0_BACKGROUND_NOISE_Pos (10)                                          /*!< TRNG_T::BUILD_CFG0: BACKGROUND_NOISE Position*/
#define TRNG_BUILD_CFG0_BACKGROUND_NOISE_Msk (0x1ul << TRNG_BUILD_CFG0_BACKGROUND_NOISE_Pos) /*!< TRNG_T::BUILD_CFG0: BACKGROUND_NOISE Mask*/

#define TRNG_BUILD_CFG0_EDU_PRESENT_Pos  (11)                                              /*!< TRNG_T::BUILD_CFG0: EDU_PRESENT Position*/
#define TRNG_BUILD_CFG0_EDU_PRESENT_Msk  (0x1ul << TRNG_BUILD_CFG0_EDU_PRESENT_Pos)        /*!< TRNG_T::BUILD_CFG0: EDU_PRESENT Mask   */

#define TRNG_BUILD_CFG0_AES_DATAPATH_Pos (12)                                              /*!< TRNG_T::BUILD_CFG0: AES_DATAPATH Position*/
#define TRNG_BUILD_CFG0_AES_DATAPATH_Msk (0x1ul << TRNG_BUILD_CFG0_AES_DATAPATH_Pos)       /*!< TRNG_T::BUILD_CFG0: AES_DATAPATH Mask  */

#define TRNG_BUILD_CFG0_AES_MAX_KEY_SIZE_Pos (13)                                          /*!< TRNG_T::BUILD_CFG0: AES_MAX_KEY_SIZE Position*/
#define TRNG_BUILD_CFG0_AES_MAX_KEY_SIZE_Msk (0x1ul << TRNG_BUILD_CFG0_AES_MAX_KEY_SIZE_Pos) /*!< TRNG_T::BUILD_CFG0: AES_MAX_KEY_SIZE Mask*/

#define TRNG_BUILD_CFG0_PERSONALIZATION_STR_Pos (14)                                       /*!< TRNG_T::BUILD_CFG0: PERSONALIZATION_STR Position*/
#define TRNG_BUILD_CFG0_PERSONALIZATION_STR_Msk (0x1ul << TRNG_BUILD_CFG0_PERSONALIZATION_STR_Pos) /*!< TRNG_T::BUILD_CFG0: PERSONALIZATION_STR Mask*/

#define TRNG_BUILD_CFG1_NUM_RAW_NOISE_BLKS_Pos (0)                                         /*!< TRNG_T::BUILD_CFG1: NUM_RAW_NOISE_BLKS Position*/
#define TRNG_BUILD_CFG1_NUM_RAW_NOISE_BLKS_Msk (0xfful << TRNG_BUILD_CFG1_NUM_RAW_NOISE_BLKS_Pos) /*!< TRNG_T::BUILD_CFG1: NUM_RAW_NOISE_BLKS Mask*/

#define TRNG_BUILD_CFG1_STICKY_STARTUP_Pos (8)                                             /*!< TRNG_T::BUILD_CFG1: STICKY_STARTUP Position*/
#define TRNG_BUILD_CFG1_STICKY_STARTUP_Msk (0x1ul << TRNG_BUILD_CFG1_STICKY_STARTUP_Pos)   /*!< TRNG_T::BUILD_CFG1: STICKY_STARTUP Mask*/

#define TRNG_BUILD_CFG1_AUTO_CORRELATION_TEST_Pos (12)                                     /*!< TRNG_T::BUILD_CFG1: AUTO_CORRELATION_TEST Position*/
#define TRNG_BUILD_CFG1_AUTO_CORRELATION_TEST_Msk (0x1ul << TRNG_BUILD_CFG1_AUTO_CORRELATION_TEST_Pos) /*!< TRNG_T::BUILD_CFG1: AUTO_CORRELATION_TEST Mask*/

#define TRNG_BUILD_CFG1_MONOBIT_TEST_Pos (13)                                              /*!< TRNG_T::BUILD_CFG1: MONOBIT_TEST Position*/
#define TRNG_BUILD_CFG1_MONOBIT_TEST_Msk (0x1ul << TRNG_BUILD_CFG1_MONOBIT_TEST_Pos)       /*!< TRNG_T::BUILD_CFG1: MONOBIT_TEST Mask  */

#define TRNG_BUILD_CFG1_RUN_TEST_Pos     (14)                                              /*!< TRNG_T::BUILD_CFG1: RUN_TEST Position  */
#define TRNG_BUILD_CFG1_RUN_TEST_Msk     (0x1ul << TRNG_BUILD_CFG1_RUN_TEST_Pos)           /*!< TRNG_T::BUILD_CFG1: RUN_TEST Mask      */

#define TRNG_BUILD_CFG1_POKER_TEST_Pos   (15)                                              /*!< TRNG_T::BUILD_CFG1: POKER_TEST Position*/
#define TRNG_BUILD_CFG1_POKER_TEST_Msk   (0x1ul << TRNG_BUILD_CFG1_POKER_TEST_Pos)         /*!< TRNG_T::BUILD_CFG1: POKER_TEST Mask    */

#define TRNG_BUILD_CFG1_RAW_HT_ADAP_TEST_Pos (16)                                          /*!< TRNG_T::BUILD_CFG1: RAW_HT_ADAP_TEST Position*/
#define TRNG_BUILD_CFG1_RAW_HT_ADAP_TEST_Msk (0x7ul << TRNG_BUILD_CFG1_RAW_HT_ADAP_TEST_Pos) /*!< TRNG_T::BUILD_CFG1: RAW_HT_ADAP_TEST Mask*/

#define TRNG_BUILD_CFG1_RAW_HT_REP_TEST_Pos (19)                                           /*!< TRNG_T::BUILD_CFG1: RAW_HT_REP_TEST Position*/
#define TRNG_BUILD_CFG1_RAW_HT_REP_TEST_Msk (0x1ul << TRNG_BUILD_CFG1_RAW_HT_REP_TEST_Pos) /*!< TRNG_T::BUILD_CFG1: RAW_HT_REP_TEST Mask*/

#define TRNG_BUILD_CFG1_ENT_SRC_REP_SMPL_SIZE_Pos (20)                                     /*!< TRNG_T::BUILD_CFG1: ENT_SRC_REP_SMPL_SIZE Position*/
#define TRNG_BUILD_CFG1_ENT_SRC_REP_SMPL_SIZE_Msk (0x7ul << TRNG_BUILD_CFG1_ENT_SRC_REP_SMPL_SIZE_Pos) /*!< TRNG_T::BUILD_CFG1: ENT_SRC_REP_SMPL_SIZE Mask*/

#define TRNG_BUILD_CFG1_ENT_SRC_REP_TEST_Pos (23)                                          /*!< TRNG_T::BUILD_CFG1: ENT_SRC_REP_TEST Position*/
#define TRNG_BUILD_CFG1_ENT_SRC_REP_TEST_Msk (0x1ul << TRNG_BUILD_CFG1_ENT_SRC_REP_TEST_Pos) /*!< TRNG_T::BUILD_CFG1: ENT_SRC_REP_TEST Mask*/

#define TRNG_BUILD_CFG1_ENT_SRC_REP_MIN_ENTROPY_Pos (24)                                   /*!< TRNG_T::BUILD_CFG1: ENT_SRC_REP_MIN_ENTROPY Position*/
#define TRNG_BUILD_CFG1_ENT_SRC_REP_MIN_ENTROPY_Msk (0x7ful << TRNG_BUILD_CFG1_ENT_SRC_REP_MIN_ENTROPY_Pos) /*!< TRNG_T::BUILD_CFG1: ENT_SRC_REP_MIN_ENTROPY Mask*/

/**@}*/ /* TRNG_CONST */
/**@}*/ /* end of TRNG register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __TRNG_REG_H__ */
