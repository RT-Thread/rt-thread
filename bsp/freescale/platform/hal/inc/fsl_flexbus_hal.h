/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#ifndef __FSL_FLEXBUS_HAL_H__
#define __FSL_FLEXBUS_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_FB_COUNT

/*!
 * @addtogroup flexbus_hal
 * @{
 */

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Flexbus status return codes.*/
typedef enum _flexbus_status
{
    kStatus_FLEXBUS_Success = 0x00U,
    kStatus_FLEXBUS_OutOfRange,
    kStatus_FLEXBUS_InvalidArgument,
    kStatus_FLEXBUS_Failed,
} flexbus_status_t;

/*! @brief Defines port size for Flexbus peripheral.*/
typedef enum _flexbus_port_size
{
    kFlexbus4bytes  = 0x00U, /*!< 32-bit port size */
    kFlexbus1byte   = 0x01U, /*!< 8-bit port size */
    kFlexbus2bytes  = 0x02U  /*!< 16-bit port size */
} flexbus_port_size_t;

/*! @brief Defines number of cycles to hold address and attributes for Flexbus peripheral.*/
typedef enum _flexbus_write_address_hold
{
    kFlexbusHold1cycle  = 0x00U, /*!< Hold address and attributes one cycle after FB_CSn negates on writes. @internal gui name="One cycle" */
    kFlexbusHold2cycles = 0x01U, /*!< Hold address and attributes two cycle after FB_CSn negates on writes. @internal gui name="Two cycle" */
    kFlexbusHold3cycles = 0x02U, /*!< Hold address and attributes three cycle after FB_CSn negates on writes. @internal gui name="Three cycle" */
    kFlexbusHold4cycles = 0x03U  /*!< Hold address and attributes four cycle after FB_CSn negates on writes. @internal gui name="Four cycle" */
} flexbus_write_address_hold_t;


/*! @brief Defines number of cycles to hold address and attributes for Flexbus peripheral.*/
typedef enum _flexbus_read_address_hold
{
    kFlexbusHold4or3cycles = 0x03U,    /*!< Hold address and attributes 4 or 3 cycles on reads. @internal gui name="4 or 3 cycles" */
    kFlexbusHold3or2cycles = 0x02U,    /*!< Hold address and attributes 3 or 2 cycles on reads. @internal gui name="3 or 2 cycles" */
    kFlexbusHold2or1cycle  = 0x01U,    /*!< Hold address and attributes 2 or 1 cycles on reads. @internal gui name="2 or 1 cycles" */
    kFlexbusHold1or0cycle  = 0x00U     /*!< Hold address and attributes 1 or 0 cycles on reads. @internal gui name="1 or 0 cycles" */
} flexbus_read_address_hold_t;


/*! @brief Address setup for Flexbus peripheral.*/
typedef enum _flexbus_address_setup
{
    kFlexbusFirstRisingEdge  = 0x00U, /*!< Assert FB_CSn on first rising clock edge after address is asserted. @internal gui name="First rising clock edge" */
    kFlexbusSecondRisingEdge = 0x01U, /*!< Assert FB_CSn on second rising clock edge after address is asserted. @internal gui name="Second rising clock edge" */
    kFlexbusThirdRisingEdge  = 0x02U, /*!< Assert FB_CSn on third rising clock edge after address is asserted. @internal gui name="Third rising clock edge" */
    kFlexbusFourthRisingEdge = 0x03U, /*!< Assert FB_CSn on fourth rising clock edge after address is asserted. @internal gui name="Fourth rising clock edge" */
} flexbus_address_setup_t;

/*! @brief Defines byte-lane shift for Flexbus peripheral.*/
typedef enum _flexbus_bytelane_shift
{
    kFlexbusNotShifted = 0x00U, /*!< Not shifted. Data is left-justfied on FB_AD. @internal gui name="Not shifted" */
    kFlexbusShifted    = 0x01U, /*!< Shifted. Data is right justified on FB_AD. @internal gui name="Shifted" */
} flexbus_bytelane_shift_t;

/*! @brief Defines multiplex group1 valid signals.*/
typedef enum _flexbus_multiplex_group1_signal
{
    kFlexbusMultiplexGroup1_FB_ALE = 0x00U, /*!< FB_ALE */
    kFlexbusMultiplexGroup1_FB_CS1 = 0x01U, /*!< FB_CS1 */
    kFlexbusMultiplexGroup1_FB_TS  = 0x02U, /*!< FB_TS */
} flexbus_multiplex_group1_t;

/*! @brief Defines multiplex group2 valid signals.*/
typedef enum _flexbus_multiplex_group2_signal
{
    kFlexbusMultiplexGroup2_FB_CS4      = 0x00U, /*!< FB_CS4 */
    kFlexbusMultiplexGroup2_FB_TSIZ0    = 0x01U, /*!< FB_TSIZ0 */
    kFlexbusMultiplexGroup2_FB_BE_31_24 = 0x02U, /*!< FB_BE_31_24 */
} flexbus_multiplex_group2_t;

/*! @brief Defines multiplex group3 valid signals.*/
typedef enum _flexbus_multiplex_group3_signal
{
    kFlexbusMultiplexGroup3_FB_CS5      = 0x00U, /*!< FB_CS5 */
    kFlexbusMultiplexGroup3_FB_TSIZ1    = 0x01U, /*!< FB_TSIZ1 */
    kFlexbusMultiplexGroup3_FB_BE_23_16 = 0x02U, /*!< FB_BE_23_16 */
} flexbus_multiplex_group3_t;

/*! @brief Defines multiplex group4 valid signals.*/
typedef enum _flexbus_multiplex_group4_signal
{
    kFlexbusMultiplexGroup4_FB_TBST    = 0x00U, /*!< FB_TBST */
    kFlexbusMultiplexGroup4_FB_CS2     = 0x01U, /*!< FB_CS2 */
    kFlexbusMultiplexGroup4_FB_BE_15_8 = 0x02U, /*!< FB_BE_15_8 */
} flexbus_multiplex_group4_t;

/*! @brief Defines multiplex group5 valid signals.*/
typedef enum _flexbus_multiplex_group5_signal
{
    kFlexbusMultiplexGroup5_FB_TA     = 0x00U, /*!< FB_TA */
    kFlexbusMultiplexGroup5_FB_CS3    = 0x01U, /*!< FB_CS3 */
    kFlexbusMultiplexGroup5_FB_BE_7_0 = 0x02U, /*!< FB_BE_7_0 */
} flexbus_multiplex_group5_t;

/*! @brief Configuration structure that the user needs to set 
 * @internal gui name="FlexBus configuration" id="fbCfg"
 */
typedef struct _flexbus_user_config {
    uint8_t chip;                                               /*!< Chip FlexBus for validation @internal gui name="Chip" range="0..5" */
    uint8_t waitStates;                                         /*!< Value of wait states @internal gui name="WaitStates" range="0..63" */
    uint32_t baseAddress;                                       /*!< Base address for using FlexBus @internal gui name="Base address" */
    uint32_t baseAddressMask;                                   /*!< Base address mask @internal gui name="Base address mask" range="0..65535" */
    bool writeProtect;                                          /*!< Write protected @internal gui name="Write protect" */
    bool burstWrite;                                            /*!< Burst-Write enable @internal gui name="Burst write" */
    bool burstRead;                                             /*!< Burst-Read enable @internal gui name="Burst read" */
    bool byteEnableMode;                                        /*!< Byte-enable mode support @internal gui name="Byte-enable mode" */
    bool autoAcknowledge;                                       /*!< Auto acknowledge setting @internal gui name="Auto ACK" */
    bool extendTransferAddress;                                 /*!< Extend transfer start/extend address latch enable @internal gui name="Address latch enable" */
    bool secondaryWaitStates;                                   /*!< Secondary wait states number @internal gui name="Secondary wait states" */
    flexbus_port_size_t portSize;                               /*!< Port size of transfer @internal gui name="Port size" */
    flexbus_bytelane_shift_t byteLaneShift;                     /*!< Byte-lane shift enable @internal gui name="Byte-lane shift" */
    flexbus_write_address_hold_t writeAddressHold;              /*!< Write address hold or deselect option @internal gui name="Write address hold" */
    flexbus_read_address_hold_t readAddressHold;                /*!< Read address hold or deselect option @internal gui name="Read address hold" */
    flexbus_address_setup_t addressSetup;                       /*!< Address setup setting @internal gui name="Address setup" */
    flexbus_multiplex_group1_t group1MultiplexControl;          /*!< FlexBus Signal Group 1 Multiplex control @internal gui name="Signal Multiplex Group 1" */
    flexbus_multiplex_group2_t group2MultiplexControl;          /*!< FlexBus Signal Group 2 Multiplex control @internal gui name="Signal Multiplex Group 2"*/
    flexbus_multiplex_group3_t group3MultiplexControl;          /*!< FlexBus Signal Group 3 Multiplex control @internal gui name="Signal Multiplex Group 3" */
    flexbus_multiplex_group4_t group4MultiplexControl;          /*!< FlexBus Signal Group 4 Multiplex control @internal gui name="Signal Multiplex Group 4" */
    flexbus_multiplex_group5_t group5MultiplexControl;          /*!< FlexBus Signal Group 5 Multiplex control @internal gui name="Signal Multiplex Group 5" */
} flexbus_user_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Configuration
 * @{
 */

/*!
 * @brief Initialization to default values.
 *
 * Only chip 0 validated and set to known values. Other chips disabled.
 *
 * @param   base Flexbus module base number.
*/
void FLEXBUS_HAL_Init(FB_Type* base);

/*!
 * @brief Configure to a known values.
 *
 * @param   base Flexbus module base number.
 * @param   userConfigPtr Flexbus input user configuration
*/
void FLEXBUS_HAL_Configure(FB_Type* base, const flexbus_user_config_t* userConfigPtr);

/*!
 * @brief Write chip-select base address.
 *
 * The CSARn registers specify the chip-select base addresses.
 * NOTE: Because the FlexBus module is one of the slaves connected to the crossbar switch, it is only
 * accessible within a certain memory range. Refer to the device memory map for the applicable
 * FlexBus "expansion" address range for which the chip-selects can be active. Set the CSARn
 * registers appropriately.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   addr chip-select base address.
 * @param   addrMask chip-select base address mask.
*/
static inline void FLEXBUS_HAL_WriteAddr(FB_Type* base, uint8_t chip, uint16_t addr, uint16_t addrMask)
{
    assert(chip < FB_CSAR_COUNT);
    FB_BWR_CSAR_BA(base, chip, addr);
    FB_BWR_CSMR_BAM(base, chip, addrMask);
}

/*!
 * @brief Sets chip-selects valid bit or not.
 *
 * Indicates whether the corresponding CSAR, CSMR, and CSCR contents are valid.
 * NOTE: At reset, no chip-select other than FB_CS0 can be used until the CSMR0[V]
 * is set. Afterward, FB_CS[5:0] functions as programmed.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   valid Validation for chip-selects or not.
 *          - true: chip-select is valid
 *          - false: chip-select is invalid
*/
static inline void FLEXBUS_HAL_SetChipSelectValidCmd(FB_Type* base, uint8_t chip, bool valid)
{
    assert(chip < FB_CSMR_COUNT);
    FB_BWR_CSMR_V(base, chip, valid);
}

/*!
 * @brief Enables or disables write protection function for Flexbus.
 *
 * Controls write accesses to the address range in the corresponding CSAR.
 * 0: Read and write accesses are allowed
 * 1: Only read accesses are allowed
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   enable Enables or disables write protection.
*/
static inline void FLEXBUS_HAL_SetWriteProtectionCmd(FB_Type* base, uint8_t chip, bool enable)
{
    assert(chip < FB_CSMR_COUNT);
    FB_BWR_CSMR_WP(base, chip, enable);
}

/*!
 * @brief Enables or disables burst-write on Flexbus.
 *
 * Specifies whether burst writes are used for memory associated with each FB_CSn.
 *
 * 0: Break data larger than the specified port size into individual, port-sized,
 *    non-burst writes. For example, a longword write to an 8-bit port takes four
 *    byte writes.
 * 1: Enables burst write of data larger than the specified port size, including
 *    longword writes to 8 and 16-bit ports, word writes to 8-bit ports, and line
 *    writes to 8-, 16-, and 32-bit ports.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   enable Enables or disables burst-write.
*/
static inline void FLEXBUS_HAL_SetBurstWriteCmd(FB_Type* base, uint8_t chip, bool enable)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_BSTW(base, chip, enable);
}

/*!
 * @brief Enables or disables burst-read bit on Flexbus.
 *
 * Specifies whether burst reads are used for memory associated with each FB_CSn.
 *
 * 0: Data exceeding the specified port size is broken into individual, port-sized,
 *    non-burst reads. For example, a longword read from an 8-bit port is broken into
 *    four 8-bit reads.
 * 1: Enables data burst reads larger than the specified port size, including longword
 *    reads from 8- and 16-bit ports, word reads from 8-bit ports, and line reads from 8,
 *    16-, and 32-bit ports.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   enable Enables or disables burst-read.
*/
static inline void FLEXBUS_HAL_SetBurstReadCmd(FB_Type* base, uint8_t chip, bool enable)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_BSTR(base, chip, enable);
}

/*!
 * @brief Enables or disables byte-enable support on Flexbus.
 *
 * Specifies the byte enable operation. Certain memories have byte enables that must
 * be asserted during reads and writes. BEM can be set in the relevant CSCR to provide
 * the appropriate mode of byte enable support for these SRAMs.
 *
 * The FB_BEn signals are asserted for read and write accesses.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   enable Enables or disables byte-enable support
*/
static inline void FLEXBUS_HAL_SetByteModeCmd(FB_Type* base, uint8_t chip, bool enable)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_BEM(base, chip, enable);
}

/*!
 * @brief Sets port size on Flexbus.
 *
 * Specifies the data port width associated with each chip-select. It determines where
 * data is driven during write cycles and where data is sampled during read cycles.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   size Size of port.
*/
static inline void FLEXBUS_HAL_SetPortSize(FB_Type* base, uint8_t chip, flexbus_port_size_t size)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_PS(base, chip, size);
}

/*!
 * @brief Enables auto-acknowledge on Flexbus.
 *
 * Determines the assertion of the internal transfer acknowledge for accesses specified by the
 * chip-select address.
 *
 * NOTE: If AA is set for a corresponding FB_CSn and the external system asserts an external FB_TA
 * before the wait-state countdown asserts the internal FB_TA, the cycle is terminated. Burst cycles
 * increment the address bus between each internal termination.
 * NOTE: This bit must be set if CSPMCR disables FB_TA.
 *
 * enable value:
 * 0: No internal FB_TA is asserted. Cycle is terminated externally
 * 1: Internal transfer acknowledge is asserted as specified by WS
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   enable Enables or disables Auto-acknowledge.
*/
static inline void FLEXBUS_HAL_SetAutoAcknowledgeCmd(FB_Type* base, uint8_t chip, bool enable)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_AA(base, chip, enable);
}

/*!
 * @brief Enables byte-lane shift on Flexbus.
 *
 * Determines if data on FB_AD appears left-justified or right-justified during the data phase
 * of a FlexBus access.
 *
 * 0: Not shifted. Data is left-justfied on FB_AD.
 * 1: Shifted. Data is right justified on FB_AD.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   shift Selects left-justified or right-justified data
*/
static inline void FLEXBUS_HAL_SetByteLaneShift(FB_Type* base, uint8_t chip, flexbus_bytelane_shift_t shift)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_BLS(base, chip, shift);
}

/*!
 * @brief Sets number of wait states on Flexbus.
 *
 * The number of wait states inserted after FB_CSn asserts and before an internal transfer
 * acknowledge is generated (WS = 0 inserts zero wait states, WS = 0x3F inserts 63 wait states).
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   waitStates Defines value of wait states
*/
static inline void FLEXBUS_HAL_SetWaitStates(FB_Type* base, uint8_t chip, uint8_t waitStates)
{
    assert(chip < FB_CSCR_COUNT);
    assert(waitStates <= 0x3F);
    FB_BWR_CSCR_WS(base, chip, waitStates);
}

/*!
 * @brief Sets write address hold or deselect.
 *
 * Write address hold or deselect. This field controls the address, data, and attribute hold time
 * after the termination of a write cycle that hits in the chip-select address space.
 * NOTE: The hold time applies only at the end of a transfer. Therefore, during a burst transfer
 * or a transfer to a port size smaller than the transfer size, the hold time is only added after
 * the last bus cycle.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   addrHold Value of cycles to hold write address.
*/
static inline void FLEXBUS_HAL_SetWriteAddrHoldOrDeselect(FB_Type* base, uint8_t chip, flexbus_write_address_hold_t addrHold)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_WRAH(base, chip, addrHold);
}

/*!
 * @brief Sets read address hold or deselect.
 *
 * This field controls the address and attribute hold time after the termination during a read cycle
 * that hits in the chip-select address space.
 * NOTE: The hold time applies only at the end of a transfer. Therefore, during a burst transfer
 * or a transfer to a port size smaller than the transfer size, the hold time is only added after
 * the last bus cycle.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   addrHold Value of cycles to hold read address.
*/
static inline void FLEXBUS_HAL_SetReadAddrHoldOrDeselect(FB_Type* base, uint8_t chip, flexbus_read_address_hold_t addrHold)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_RDAH(base, chip, addrHold);
}

/*!
 * @brief Set address setup
 *
 * Controls the assertion of the chip-select with respect to assertion of a valid address and
 * attributes. The address and attributes are considered valid at the same time FB_TS/FB_ALE asserts.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   delay Value of delay.
*/
static inline void FLEXBUS_HAL_SetAddrSetup(FB_Type* base, uint8_t chip, flexbus_address_setup_t delay)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_ASET(base, chip, delay);
}

/*!
 * @brief Enables extended address latch.
 *
 * Extended address latch enable
 *
 * 0: FB_TS/FB_ALE asserts for one bus clock cycle.
 * 1: FB_TS/FB_ALE remains asserted until the first positive clock edge after FB_CSn asserts.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   enable Enables or disables extended address latch.
*/
static inline void FLEXBUS_HAL_SetExtendedAddrLatchCmd(FB_Type* base, uint8_t chip, bool enable)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_EXTS(base, chip, enable);
}

/*!
 * @brief Enables secondary wait state.
 *
 * Secondary wait state enable.
 *
 * 0: The WS value inserts wait states before an internal transfer acknowledge is generated
 *    for all transfers.
 * 1: The SWS value inserts wait states before an internal transfer acknowledge is generated
 *    for burst transfer secondary terminations.
 *
 * @param   base Flexbus module base number.
 * @param   chip Flexbus chip for validation.
 * @param   enable Enables or disables wait state
*/
static inline void FLEXBUS_HAL_SetSecondaryWaitStateCmd(FB_Type* base, uint8_t chip, bool enable)
{
    assert(chip < FB_CSCR_COUNT);
    FB_BWR_CSCR_SWSEN(base, chip, enable);
}

/*!
 * @brief Multiplex group1 set
 *
 * GROUP1 Controls the multiplexing of the FB_ALE, FB_CS1 , and FB_TS signals.
 *
 * @param   base Flexbus module base number.
 * @param   controls Flexbus multiplex settings for Group1.
 *
 * @return  Flexbus status.
*/
static inline void FLEXBUS_HAL_SetMultiplexControlGroup1(FB_Type* base, flexbus_multiplex_group1_t controls)
{
    FB_BWR_CSPMCR_GROUP1(base, controls);
}

/*!
 * @brief Multiplex group1 get
 *
 * GROUP1 Controls the multiplexing of the FB_ALE, FB_CS1 , and FB_TS signals.
 *
 * @param   base Flexbus module base number.
 *
 * @return  Flexbus multiplex settings for Group1.
*/
static inline flexbus_multiplex_group1_t FLEXBUS_HAL_GetMultiplexControlGroup1(FB_Type* base)
{
    return (flexbus_multiplex_group1_t)FB_BRD_CSPMCR_GROUP1(base);
}

/*!
 * @brief Multiplex group2 set
 *
 * GROUP2 Controls the multiplexing of the FB_TA , FB_CS3 , and FB_BE_7_0 signals. When
 *        GROUP5 is not 0000b, you must write 1b to the CSCR[AA] bit. Otherwise, the
 *        bus hangs during a transfer.
 *
 * @param   base Flexbus module base number.
 * @param   controls Flexbus multiplex settings for Group2.
 *
 * @return  Flexbus status.
 *
*/
static inline void FLEXBUS_HAL_SetMultiplexControlGroup2(FB_Type* base, flexbus_multiplex_group2_t controls)
{
    FB_BWR_CSPMCR_GROUP2(base, controls);
}

/*!
 * @brief Multiplex group2 get
 *
 * GROUP2 Controls the multiplexing of the FB_TA , FB_CS3 , and FB_BE_7_0 signals. When
 *        GROUP5 is not 0000b, you must write 1b to the CSCR[AA] bit. Otherwise, the
 *        bus hangs during a transfer.
 *
 * @param   base Flexbus module base number.
 *
 * @return  Flexbus multiplex settings for Group2.
*/
static inline flexbus_multiplex_group2_t FLEXBUS_HAL_GetMultiplexControlGroup2(FB_Type* base)
{
    return (flexbus_multiplex_group2_t)FB_BRD_CSPMCR_GROUP2(base);
}

/*!
 * @brief Multiplex group3 set
 *
 * GROUP3 Controls the multiplexing of the FB_CS4 , FB_TSIZ0, and FB_BE_31_24 signals.
 *
 * @param   base Flexbus module base number.
 * @param   controls Flexbus multiplex settings for Group3.
 *
 * @return  Flexbus status.
 *
*/
static inline void FLEXBUS_HAL_SetMultiplexControlGroup3(FB_Type* base, flexbus_multiplex_group3_t controls)
{
    FB_BWR_CSPMCR_GROUP3(base, controls);
}

/*!
 * @brief Multiplex group3 get
 *
 * GROUP3 Controls the multiplexing of the FB_CS4 , FB_TSIZ0, and FB_BE_31_24 signals.
 *
 * @param   base Flexbus module base number.
 *
 * @return  Flexbus multiplex settings for Group3.
 *
*/
static inline flexbus_multiplex_group3_t FLEXBUS_HAL_GetMultiplexControlGroup3(FB_Type* base)
{
    return (flexbus_multiplex_group3_t)FB_BRD_CSPMCR_GROUP3(base);
}

/*!
 * @brief Multiplex group4 set
 *
 * GROUP4 Controls the multiplexing of the FB_TBST, FB_CS2, and FB_BE_15_8 signals.
 *
 * @param   base Flexbus module base number.
 * @param   controls Flexbus multiplex settings for Group4.
 *
 * @return  Flexbus status.
 *
*/
static inline void FLEXBUS_HAL_SetMultiplexControlGroup4(FB_Type* base, flexbus_multiplex_group4_t controls)
{
    FB_BWR_CSPMCR_GROUP4(base, controls);
}

/*!
 * @brief Multiplex group4 get
 *
 * GROUP4 Controls the multiplexing of the FB_TBST, FB_CS2, and FB_BE_15_8 signals.
 *
 * @param   base Flexbus module base number.
 *
 * @return  Flexbus multiplex settings for Group4.
 *
*/
static inline flexbus_multiplex_group4_t FLEXBUS_HAL_GetMultiplexControlGroup4(FB_Type* base)
{
    return (flexbus_multiplex_group4_t)FB_BRD_CSPMCR_GROUP4(base);
}

/*!
 * @brief Multiplex group5 set
 *
 * GROUP5 Controls the multiplexing of the FB_TA, FB_CS3, and FB_BE_7_0 signals.
 *
 * @param   base Flexbus module base number.
 * @param   controls Flexbus multiplex settings for Group5.
 *
 * @return  Flexbus status.
 *
*/
static inline void FLEXBUS_HAL_SetMultiplexControlGroup5(FB_Type* base, flexbus_multiplex_group5_t controls)
{
    FB_BWR_CSPMCR_GROUP5(base, controls);
}

/*!
 * @brief Multiplex group5 get
 *
 * GROUP5 Controls the multiplexing of the FB_TA, FB_CS3, and FB_BE_7_0 signals.
 *
 * @param   base Flexbus module base number.
 *
 * @return  Flexbus multiplex settings for Group5.
 *
*/
static inline flexbus_multiplex_group5_t FLEXBUS_HAL_GetMultiplexControlGroup5(FB_Type* base)
{
    return (flexbus_multiplex_group5_t)FB_BRD_CSPMCR_GROUP5(base);
}

/*! @}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_FLEXCAN_HAL_H__*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

