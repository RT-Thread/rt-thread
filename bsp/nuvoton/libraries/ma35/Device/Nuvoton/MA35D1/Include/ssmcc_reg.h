/**************************************************************************//**
 * @file     ssmcc_reg.h
 * @brief    SSMCC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SSMCC_REG_H__
#define __SSMCC_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/

typedef struct
{
    /**
     * @var FAIL_T::ADDRESS_LOW
     * Offset: 0x20  Contains the lower 32 bits of the address of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |addr_status_low|If a region permission check fails or a region overlap occurs, this field returns the ACE-Lite address bits [31:0] of the first f. You must clear the associated interrupt status before this field can return the address of accesses of subsequent permission checks or region overlap failures.  This occurs even if the ACTION register does not enable the interrupt.  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var FAIL_T::ADDRESS_HIGH
     * Offset: 0x24  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var FAIL_T::CONTROL
     * Offset: 0x28  Contains the control status information of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[20]    |Privileged|If a region permission check fails or a region overlap occurs, this field indicates whether it was an unprivileged or privileged access attempt  You must clear the associated interrupt status before this field can return the values of accesses of subsequent permission checks or region overlap failures  0 Unprivileged access 1 Privileged access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[21]    |Non_secure|If a region permission check fails or a region overlap occurs, this field indicates whether it was a Secure or Non- secure access attempt  You must clear the associated interrupt status before this field can return the direction of accesses of subsequent permission checks or region overlap failures  0 Secure access 1 Non-secure access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[24]    |Direction |If a region permission check fails or a region overlap occurs, this field indicates whether the failed access was a read or write access attempt  You must clear the associated interrupt status before this field can return the direction of accesses of subsequent permission checks or region overlap failures  0 Read access 1 Write access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var FAIL_T::ID
     * Offset: 0x2C  Contains the master ACE-Lite ARID or AWID of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |id        |If a region permission check fails or a region overlap occurs, this field returns the ACE-Lite ID values of the first failed access If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[27:24] |vnet      |If a region permission check fails or a region overlap occurs, this field returns the VN number of the first failed access, from either ARVNET<x> or AWVNET<x> as appropriate If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     */
    __I  uint32_t ADDRESS_LOW;    /*!< [0x0000] Contains the lower 32 bits of the address of the first access that failed a region permission check in the associated filter unit. */
    __IO uint32_t ADDRESS_HIGH;   /*!< [0x0004] Reserved                                                         */
    __I  uint32_t CONTROL;        /*!< [0x0008] Contains the control status information of the first access that failed a region permission check in the associated filter unit. */
    __I  uint32_t ID;             /*!< [0x000c] Contains the master ACE-Lite ARID or AWID of the first access that failed a region permission check in the associated filter unit. */
} FAIL_STS_T;

typedef struct
{
    __IO uint32_t BASE_LOW;            /*!< [0x0000] */
    __IO uint32_t BASE_HIGH;           /*!< [0x0004] */
    __IO uint32_t TOP_LOW;             /*!< [0x0008] */
    __IO uint32_t TOP_HIGH;            /*!< [0x000c] */
    __IO uint32_t ATTRIBUTES;          /*!< [0x0010] */
    __IO uint32_t ID_ACCESS;           /*!< [0x0014] */
    __I  uint32_t RESERVE2[2];         /*!< [0x0018] */
} REGION_T;

/*---------------------- System Security Memory Configuration Controller -------------------------*/
/**
    @addtogroup SSMCC System Security Memory Configuration Controller(SSMCC)
    Memory Mapped Structure for SSMCC Controller
@{ */

typedef struct
{


    /**
     * @var SSMCC_T::SCWP
     * Offset: 0x00  Security Configuration Write Protect Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ENABLE    |Write Protection Enable Bit
     * |        |          |0 = Security Configuration Write Protection Disabled.
     * |        |          |1 = Security Configuration Write Protection Enabled.
     * |[1]     |LOCK      |Write Protection Enable and Lock Bit (Write 1 to Set)
     * |        |          |0 = Security Configuration Write Protection Disabled.
     * |        |          |1 = Security Configuration Write Protection Enabled.
     * |        |          |Note: This bit can only be cleared by system reset.
     * |[31:16] |WVCODE    |Write Verify Code
     * |        |          |Read operation:
     * |        |          |Reserved, all zeros.
     * |        |          |Write operation:
     * |        |          |0x475A = The write verify code, 0x475A, is needed to do a valid write to SSMCC_SCWP.
     * |        |          |Others = Invalid write verify code.
     */
    __IO uint32_t SCWP;                  /*!< [0x0000] Security Configuration Write Protect Register                    */

} SSMCC_T;

/**
    @addtogroup SSMCC_CONST SSMCC Bit Field Definition
    Constant Definitions for SSMCC Controller
@{ */

#define SSMCC_SCWP_ENABLE_Pos            (0)                                               /*!< SSMCC_T::SCWP: ENABLE Position         */
#define SSMCC_SCWP_ENABLE_Msk            (0x1ul << SSMCC_SCWP_ENABLE_Pos)                  /*!< SSMCC_T::SCWP: ENABLE Mask             */

#define SSMCC_SCWP_LOCK_Pos              (1)                                               /*!< SSMCC_T::SCWP: LOCK Position           */
#define SSMCC_SCWP_LOCK_Msk              (0x1ul << SSMCC_SCWP_LOCK_Pos)                    /*!< SSMCC_T::SCWP: LOCK Mask               */

#define SSMCC_SCWP_WVCODE_Pos            (16)                                              /*!< SSMCC_T::SCWP: WVCODE Position         */
#define SSMCC_SCWP_WVCODE_Msk            (0xfffful << SSMCC_SCWP_WVCODE_Pos)               /*!< SSMCC_T::SCWP: WVCODE Mask             */

/**@}*/ /* SSMCC_CONST */
/**@}*/ /* end of SSMCC register group */


/*---------------------- TrustZone Address Space Controller -------------------------*/
/**
    @addtogroup TZC TrustZone Address Space Controller(TZC)
    Memory Mapped Structure for TZC Controller
@{ */

typedef struct
{
    /**
     * @var TZC_T::BUILD_CONFIG
     * Offset: 0x00  Provides information about the configuration of the TZC-400.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |no_of_regions|Defines the number of regions that the TZC-400 provides: 0b01000 Nine regions All other values Reserved.
     * |[13:8]  |address_width|Defines the width of the ACE-Lite address bus: 0b011111 32 bits 0b100011 36 bits 0b100111 40 bits 0b101111 48 bits 0b111111 64 bits All other values Reserved.
     * |[25:24] |no_of_filters|Defines the number of filter units in the design implementation: 0b00 One filter unit 0b01 Two filter units 0b10 Reserved 0b11 Four filter units.
     * @var TZC_T::ACTION
     * Offset: 0x04  Controls the interrupt and bus response signaling behavior of the TZC-400 when region permission failures occur.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |reaction_value|Controls how the TZC-400 uses the BRESPS[1:0], RRESPS[1:0], and TZCINT signals when a region permission failure occurs, excluding region overlap errors The settings for these bits are: 0b00 Sets TZCINT LOW and issues an OKAY response 0b01 Sets TZCINT LOW and issues a DECERR response 0b10 Sets TZCINT HIGH and issues an OKAY response 0b11 Sets TZCINT HIGH and issues a DECERR response  When a region overlap for region 1 and higher occurs, this field also determines how TZCINT is set The settings are: 0b00, 0b01 TZCINT LOW 0b10, 0b11 TZCINT HIGH.
     * @var TZC_T::GATE_KEEPER
     * Offset: 0x08  Provides control and status for the gate keeper in each filter unit implemented
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |open_request|Each bit in this field requests the gate of the associated filter unit to be open or closed Each bit is  associated as follows:  bit 0 Filter 0  bit 1 Filter 1  bit 2 Filter 2  bit 3 Filter 3.  Set the open_request bit to 1, to request the gate to be open  Set the open_request bit to 0, to request the gate to be closed If any of the associated filter units are not implemented, the corresponding open_request bits are unused,
     * |[19:16] |open_status|The current state of the gate keeper in each filter unit The bit associations are as follows:  bit 16 Filter 0 gate keeper status  bit 17 Filter 1 gate keeper status  bit 18 Filter 2 gate keeper status  bit 19 Filter 3 gate keeper status  When a bit is set to 1, the gate keeper permits access to its associated filter, that is, it is open  When a bit is set to 0, the gate keeper no longer permits access to its associated filter, that is, it is closed  This bit is set to 0 when both of the following conditions are fulfilled:This means that the gate keeper  always waits for outstanding accesses to complete &#8226; The gate keeper no longer permits access to its associated filter &#8226; All outstanding accesses through the filter unit are complete  If any of the associated filter units are not implemented, the corresponding gate keeper bits are unused,
     * @var TZC_T::SPECULATION_CTRL
     * Offset: 0x0C  Controls the read access speculation and write access speculation.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |read_spec_disable|Controls read access speculation Note This bit is ignored and assumed to be zero at a filter unit if the corresponding QVNENABLE<x> signal is HIGH   You can set this bit as follows:  0 Enables read access speculation This is the default setting 1 Disables read access speculation.
     * |[1]     |write_spec_disable|Controls write acc. Note This bit is ignored and assumed to be zero at a filter unit if the corresponding QVNENABLE<x> signal is HIGH.   Set this bit as follows:  0 Enables write access speculation. This is the default setting. 1 Disables write access speculation.
     * @var TZC_T::INT_STATUS
     * Offset: 0x10  Contains the status of the interrupt signal, TZCINT, that reports access security violations or region overlap errors.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |status    |Each bit is associated as follows:  bit 0 Filter 0  bit 1 Filter 1  bit 2 Filter 2  bit 3 Filter 3.  Each bit in this field indicates the status of the interrupt from each filter unit as follows:  0 Interrupt is not asserted 1 Interrupt is asserted and waiting to be cleared  This bit is set even if the ACTION register is set to not drive the interrupt output TZCINT HIGH  Therefore, the status acts as an indicator that a region permission check failure or an overlap error has occurred at a particular filter unit.
     * |[11:8]  |overrun   |The bit associations are as follows:  bit 8 Filter 0  bit 9 Filter 1  bit 10 Filter 2  bit 11 Filter 3.  When a bit is set to 1, it indicates the occurrence of two or more region permission or region overlapping failures at the associated filter unit after the interrupt was cleared by the associated bit  This bit is set even if the ACTION register is set to not drive the interrupt  Clear the interrupt status of the associated bit in the INT_CLEAR register to also clear this field.
     * |[19:16] |overlap   |The bit associations are as follows:  bit 16 Filter 0  bit 17 Filter 1  bit 18 Filter 2  bit 19 Filter 3  When a bit is set to 1, it indicates a violation of the overlap region configuration rules for the associated filter unit This occurs when an access matches with two enabled regions at the same time unless the overlap is only with Region 0.  This bit is set even if the ACTION register is set to not drive the interrupt When this bit is 1, the interrupt status bit is also set to 1. Clear the interrupt status of the associated bit to also clear this field
     * @var TZC_T::INT_CLEAR
     * Offset: 0x14  Clears the interrupt.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |clear     |Contains the control bits to clear interrupts The bit associations are as follows:  bit 0 Filter 0  bit 1 Filter 1  bit 2 Filter 2  bit 3 Filter 3.  Write a 1 to any of these bits to clear the associated status, overrun, and overlap bits in the INT_STATUS register.
     * @var TZC_T::FAIL_ADDRESS_LOW_0
     * Offset: 0x20  Contains the lower 32 bits of the address of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |addr_status_low|If a region permission check fails or a region overlap occurs, this field returns the ACE-Lite address bits [31:0] of the first f. You must clear the associated interrupt status before this field can return the address of accesses of subsequent permission checks or region overlap failures.  This occurs even if the ACTION register does not enable the interrupt.  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var TZC_T::FAIL_ADDRESS_HIGH_0
     * Offset: 0x24  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::FAIL_CONTROL_0
     * Offset: 0x28  Contains the control status information of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[20]    |Privileged|If a region permission check fails or a region overlap occurs, this field indicates whether it was an unprivileged or privileged access attempt  You must clear the associated interrupt status before this field can return the values of accesses of subsequent permission checks or region overlap failures  0 Unprivileged access 1 Privileged access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[21]    |Non_secure|If a region permission check fails or a region overlap occurs, this field indicates whether it was a Secure or Non- secure access attempt  You must clear the associated interrupt status before this field can return the direction of accesses of subsequent permission checks or region overlap failures  0 Secure access 1 Non-secure access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[24]    |Direction |If a region permission check fails or a region overlap occurs, this field indicates whether the failed access was a read or write access attempt  You must clear the associated interrupt status before this field can return the direction of accesses of subsequent permission checks or region overlap failures  0 Read access 1 Write access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var TZC_T::FAIL_ID_0
     * Offset: 0x2C  Contains the master ACE-Lite ARID or AWID of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |id        |If a region permission check fails or a region overlap occurs, this field returns the ACE-Lite ID values of the first failed access If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[27:24] |vnet      |If a region permission check fails or a region overlap occurs, this field returns the VN number of the first failed access, from either ARVNET<x> or AWVNET<x> as appropriate If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var TZC_T::FAIL_ADDRESS_LOW_1
     * Offset: 0x30  Contains the lower 32 bits of the address of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |addr_status_low|If a region permission check fails or a region overlap occurs, this field returns the ACE-Lite address bits [31:0] of the first f. You must clear the associated interrupt status before this field can return the address of accesses of subsequent permission checks or region overlap failures.  This occurs even if the ACTION register does not enable the interrupt.  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var TZC_T::FAIL_ADDRESS_HIGH_1
     * Offset: 0x34  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::FAIL_CONTROL_1
     * Offset: 0x38  Contains the control status information of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[20]    |Privileged|If a region permission check fails or a region overlap occurs, this field indicates whether it was an unprivileged or privileged access attempt  You must clear the associated interrupt status before this field can return the values of accesses of subsequent permission checks or region overlap failures  0 Unprivileged access 1 Privileged access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[21]    |Non_secure|If a region permission check fails or a region overlap occurs, this field indicates whether it was a Secure or Non- secure access attempt  You must clear the associated interrupt status before this field can return the direction of accesses of subsequent permission checks or region overlap failures  0 Secure access 1 Non-secure access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[24]    |Direction |If a region permission check fails or a region overlap occurs, this field indicates whether the failed access was a read or write access attempt  You must clear the associated interrupt status before this field can return the direction of accesses of subsequent permission checks or region overlap failures  0 Read access 1 Write access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var TZC_T::FAIL_ID_1
     * Offset: 0x3C  Contains the master ACE-Lite ARID or AWID of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |id        |If a region permission check fails or a region overlap occurs, this field returns the ACE-Lite ID values of the first failed access If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[27:24] |vnet      |If a region permission check fails or a region overlap occurs, this field returns the VN number of the first failed access, from either ARVNET<x> or AWVNET<x> as appropriate If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var TZC_T::FAIL_ADDRESS_LOW_2
     * Offset: 0x40  Contains the lower 32 bits of the address of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |addr_status_low|If a region permission check fails or a region overlap occurs, this field returns the ACE-Lite address bits [31:0] of the first f. You must clear the associated interrupt status before this field can return the address of accesses of subsequent permission checks or region overlap failures.  This occurs even if the ACTION register does not enable the interrupt.  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var TZC_T::FAIL_ADDRESS_HIGH_2
     * Offset: 0x44  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::FAIL_CONTROL_2
     * Offset: 0x48  Contains the control status information of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[20]    |Privileged|If a region permission check fails or a region overlap occurs, this field indicates whether it was an unprivileged or privileged access attempt  You must clear the associated interrupt status before this field can return the values of accesses of subsequent permission checks or region overlap failures  0 Unprivileged access 1 Privileged access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[21]    |Non_secure|If a region permission check fails or a region overlap occurs, this field indicates whether it was a Secure or Non- secure access attempt  You must clear the associated interrupt status before this field can return the direction of accesses of subsequent permission checks or region overlap failures  0 Secure access 1 Non-secure access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[24]    |Direction |If a region permission check fails or a region overlap occurs, this field indicates whether the failed access was a read or write access attempt  You must clear the associated interrupt status before this field can return the direction of accesses of subsequent permission checks or region overlap failures  0 Read access 1 Write access  If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var TZC_T::FAIL_ID_2
     * Offset: 0x4C  Contains the master ACE-Lite ARID or AWID of the first access that failed a region permission check in the associated filter unit.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |id        |If a region permission check fails or a region overlap occurs, this field returns the ACE-Lite ID values of the first failed access If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * |[27:24] |vnet      |If a region permission check fails or a region overlap occurs, this field returns the VN number of the first failed access, from either ARVNET<x> or AWVNET<x> as appropriate If the status flag for the filter unit in the INT_STATUS register is already set, new region permission check failures in the same filter unit do not update the associated fail status group of registers.
     * @var TZC_T::REGION_BASE_LOW_0
     * Offset: 0x100  This register is read-only and is hard-wired to all zeros.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |base_address_low_n_|Controls the base address bits[31:12] of Region <n>
     * |        |          |For Region 0, this field is read-only. The TZC-400 sets the base address of Region 0 to 0x0.
     * @var TZC_T::REGION_BASE_HIGH_0
     * Offset: 0x104  This register is read-only and is hard-wired to all zeros.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_TOP_LOW_0
     * Offset: 0x108  This register is read-only and is hard-wired to all 1.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |top_address_low_n_|Controls the region top address bits[31:12] of region <n>
     * |        |          |For Region 0, this field is read-only and all bits are set HIGH.
     * |        |          |.
     * @var TZC_T::REGION_TOP_HIGH_0
     * Offset: 0x10C  This register is read-only and is hard-wired to all zeros.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_ATTRIBUTES_0
     * Offset: 0x110  Controls the permissions for Region 0.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |filter_en |Independent region enable for each filter unit Each bit is associated with a filter unit Set these bits as follows:  Bit 0 For Filter 0  Bit 1 For Filter 1  Bit 2 For Filter 2  Bit 3 For Filter 3. When set HIGH, it enables the use of the current region programming for the associated filter For Region 0, all bits are set HIGH and cannot be modified.
     * |[30]    |s_rd_en   |Secure global read enable This control bit defines the permissions for the Secure reads in the region  Set this bit as follows:  0 Secure read to the region is not permitted 1 Permits Secure read to the region.
     * |[31]    |s_wr_en   |Secure global write enable This control bit defines the permissions for the Secure writes in the region  Set this bit as follows:  0 Secure write to the region is not permitted 1 Permits Secure write to the region.
     * @var TZC_T::REGION_ID_ACCESS_0
     * Offset: 0x114  Controls the Non-secure access based on the NSAID inputs for Region 0.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |nsaid_rd_en|NSAID read enables
     * |        |          |This enables NSAID inputs to define Non-secure read access permission Each bit of the nsaid_rd_en register field is associated with a value on the NSAIDR<x> signal as follows:  Bit 0 Associated with NSAIDR<x> = 0
     * |        |          |Bit 1 Associated with NSAIDR<x> = 1
     * |        |          |Bit 2 Associated with NSAIDR<x> = 2
     * |        |          |Bit 15 Associated with NSAIDR<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set HIGH, TZC-400 permits Non-secure read access to any access with the associated NSAIDR<x> value
     * |        |          |For example, if NSAIDR<x> is 3 and the corresponding nsaid_rd_en[3] bit is set HIGH then TZC-400 permits the Non-secure read access to progress.
     * |[31:16] |nsaid_wr_en|NSAID write enables
     * |        |          |This enables NSAID inputs to define Non-secure write access permission Each bit of the nsaid_wr_en register field is associated with a value on the NSAIDW<x> signal as follows:  Bit 16 Associated with NSAIDW<x> = 0
     * |        |          |Bit 17 Associated with NSAIDW<x> = 1
     * |        |          |Bit 18 Associated with NSAIDW<x> = 2
     * |        |          |Bit 31 Associated with NSAIDW<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set to 1, TZC-400 permits Non-secure write access to any access with the associated NSAIDW<x> value
     * |        |          |For example, if NSAIDW<x> is 3 and the corresponding nsaid_wr_en[3] bit is set HIGH then TZC-400 permits the Non-secure write access to progress.
     * @var TZC_T::REGION_BASE_LOW_1
     * Offset: 0x120  Controls the base address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |base_address_low_n_|Controls the base address bits[31:12] of Region <n>  For Region 0, this field is read-only The TZC-400 sets the base address of Region 0 to 0x0  The TZC-400 only permits a region to start at a 4KB aligned address and address bits[11:0] are zeros.
     * @var TZC_T::REGION_BASE_HIGH_1
     * Offset: 0x124  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_TOP_LOW_1
     * Offset: 0x128  Controls the region top address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |top_address_low_n_|Controls the region top address bits[31:12] of region <n>  This address points to the start of the next 4KB aligned address immediately outside the region.
     * @var TZC_T::REGION_TOP_HIGH_1
     * Offset: 0x12C  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_ATTRIBUTES_1
     * Offset: 0x130  Controls the permissions and target filter region enables.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |filter_en |Independent region enable for each filter unit Each bit is associated with a filter unit Set these bits as follows:  Bit 0 For Filter 0  Bit 1 For Filter 1  Bit 2 For Filter 2  Bit 3 For Filter 3. When set HIGH, it enables the use of the current region programming for the associated filter For Region 0, all bits are set HIGH and cannot be modified.
     * |[30]    |s_rd_en   |Secure global read enable This control bit defines the permissions for the Secure reads in the region  Set this bit as follows:  0 Secure read to the region is not permitted 1 Permits Secure read to the region.
     * |[31]    |s_wr_en   |Secure global write enable This control bit defines the permissions for the Secure writes in the region  Set this bit as follows:  0 Secure write to the region is not permitted 1 Permits Secure write to the region.
     * @var TZC_T::REGION_ID_ACCESS_1
     * Offset: 0x134  Controls the Non-secure access based on the NSAID inputs.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |nsaid_rd_en|NSAID read enables
     * |        |          |This enables NSAID inputs to define Non-secure read access permission Each bit of the nsaid_rd_en register field is associated with a value on the NSAIDR<x> signal as follows:  Bit 0 Associated with NSAIDR<x> = 0
     * |        |          |Bit 1 Associated with NSAIDR<x> = 1
     * |        |          |Bit 2 Associated with NSAIDR<x> = 2
     * |        |          |Bit 15 Associated with NSAIDR<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set HIGH, TZC-400 permits Non-secure read access to any access with the associated NSAIDR<x> value
     * |        |          |For example, if NSAIDR<x> is 3 and the corresponding nsaid_rd_en[3] bit is set HIGH then TZC-400 permits the Non-secure read access to progress.
     * |[31:16] |nsaid_wr_en|NSAID write enables
     * |        |          |This enables NSAID inputs to define Non-secure write access permission Each bit of the nsaid_wr_en register field is associated with a value on the NSAIDW<x> signal as follows:  Bit 16 Associated with NSAIDW<x> = 0
     * |        |          |Bit 17 Associated with NSAIDW<x> = 1
     * |        |          |Bit 18 Associated with NSAIDW<x> = 2
     * |        |          |Bit 31 Associated with NSAIDW<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set to 1, TZC-400 permits Non-secure write access to any access with the associated NSAIDW<x> value
     * |        |          |For example, if NSAIDW<x> is 3 and the corresponding nsaid_wr_en[3] bit is set HIGH then TZC-400 permits the Non-secure write access to progress.
     * @var TZC_T::REGION_BASE_LOW_2
     * Offset: 0x140  Controls the base address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |base_address_low_n_|Controls the base address bits[31:12] of Region <n>  For Region 0, this field is read-only The TZC-400 sets the base address of Region 0 to 0x0  The TZC-400 only permits a region to start at a 4KB aligned address and address bits[11:0] are zeros.
     * @var TZC_T::REGION_BASE_HIGH_2
     * Offset: 0x144  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_TOP_LOW_2
     * Offset: 0x148  Controls the region top address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |top_address_low_n_|Controls the region top address bits[31:12] of region <n>  This address points to the start of the next 4KB aligned address immediately outside the region.
     * @var TZC_T::REGION_TOP_HIGH_2
     * Offset: 0x14C  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_ATTRIBUTES_2
     * Offset: 0x150  Controls the permissions and target filter region enables.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |filter_en |Independent region enable for each filter unit Each bit is associated with a filter unit Set these bits as follows:  Bit 0 For Filter 0  Bit 1 For Filter 1  Bit 2 For Filter 2  Bit 3 For Filter 3. When set HIGH, it enables the use of the current region programming for the associated filter For Region 0, all bits are set HIGH and cannot be modified.
     * |[30]    |s_rd_en   |Secure global read enable This control bit defines the permissions for the Secure reads in the region  Set this bit as follows:  0 Secure read to the region is not permitted 1 Permits Secure read to the region.
     * |[31]    |s_wr_en   |Secure global write enable This control bit defines the permissions for the Secure writes in the region  Set this bit as follows:  0 Secure write to the region is not permitted 1 Permits Secure write to the region.
     * @var TZC_T::REGION_ID_ACCESS_2
     * Offset: 0x154  Controls the Non-secure access based on the NSAID inputs.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |nsaid_rd_en|NSAID read enables
     * |        |          |This enables NSAID inputs to define Non-secure read access permission Each bit of the nsaid_rd_en register field is associated with a value on the NSAIDR<x> signal as follows:  Bit 0 Associated with NSAIDR<x> = 0
     * |        |          |Bit 1 Associated with NSAIDR<x> = 1
     * |        |          |Bit 2 Associated with NSAIDR<x> = 2
     * |        |          |Bit 15 Associated with NSAIDR<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set HIGH, TZC-400 permits Non-secure read access to any access with the associated NSAIDR<x> value
     * |        |          |For example, if NSAIDR<x> is 3 and the corresponding nsaid_rd_en[3] bit is set HIGH then TZC-400 permits the Non-secure read access to progress.
     * |[31:16] |nsaid_wr_en|NSAID write enables
     * |        |          |This enables NSAID inputs to define Non-secure write access permission Each bit of the nsaid_wr_en register field is associated with a value on the NSAIDW<x> signal as follows:  Bit 16 Associated with NSAIDW<x> = 0
     * |        |          |Bit 17 Associated with NSAIDW<x> = 1
     * |        |          |Bit 18 Associated with NSAIDW<x> = 2
     * |        |          |Bit 31 Associated with NSAIDW<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set to 1, TZC-400 permits Non-secure write access to any access with the associated NSAIDW<x> value
     * |        |          |For example, if NSAIDW<x> is 3 and the corresponding nsaid_wr_en[3] bit is set HIGH then TZC-400 permits the Non-secure write access to progress.
     * @var TZC_T::REGION_BASE_LOW_3
     * Offset: 0x160  Controls the base address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |base_address_low_n_|Controls the base address bits[31:12] of Region <n>  For Region 0, this field is read-only The TZC-400 sets the base address of Region 0 to 0x0  The TZC-400 only permits a region to start at a 4KB aligned address and address bits[11:0] are zeros.
     * @var TZC_T::REGION_BASE_HIGH_3
     * Offset: 0x164  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_TOP_LOW_3
     * Offset: 0x168  Controls the region top address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |top_address_low_n_|Controls the region top address bits[31:12] of region <n>  This address points to the start of the next 4KB aligned address immediately outside the region.
     * @var TZC_T::REGION_TOP_HIGH_3
     * Offset: 0x16C  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_ATTRIBUTES_3
     * Offset: 0x170  Controls the permissions and target filter region enables.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |filter_en |Independent region enable for each filter unit Each bit is associated with a filter unit Set these bits as follows:  Bit 0 For Filter 0  Bit 1 For Filter 1  Bit 2 For Filter 2  Bit 3 For Filter 3. When set HIGH, it enables the use of the current region programming for the associated filter For Region 0, all bits are set HIGH and cannot be modified.
     * |[30]    |s_rd_en   |Secure global read enable This control bit defines the permissions for the Secure reads in the region  Set this bit as follows:  0 Secure read to the region is not permitted 1 Permits Secure read to the region.
     * |[31]    |s_wr_en   |Secure global write enable This control bit defines the permissions for the Secure writes in the region  Set this bit as follows:  0 Secure write to the region is not permitted 1 Permits Secure write to the region.
     * @var TZC_T::REGION_ID_ACCESS_3
     * Offset: 0x174  Controls the Non-secure access based on the NSAID inputs.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |nsaid_rd_en|NSAID read enables
     * |        |          |This enables NSAID inputs to define Non-secure read access permission Each bit of the nsaid_rd_en register field is associated with a value on the NSAIDR<x> signal as follows:  Bit 0 Associated with NSAIDR<x> = 0
     * |        |          |Bit 1 Associated with NSAIDR<x> = 1
     * |        |          |Bit 2 Associated with NSAIDR<x> = 2
     * |        |          |Bit 15 Associated with NSAIDR<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set HIGH, TZC-400 permits Non-secure read access to any access with the associated NSAIDR<x> value
     * |        |          |For example, if NSAIDR<x> is 3 and the corresponding nsaid_rd_en[3] bit is set HIGH then TZC-400 permits the Non-secure read access to progress.
     * |[31:16] |nsaid_wr_en|NSAID write enables
     * |        |          |This enables NSAID inputs to define Non-secure write access permission Each bit of the nsaid_wr_en register field is associated with a value on the NSAIDW<x> signal as follows:  Bit 16 Associated with NSAIDW<x> = 0
     * |        |          |Bit 17 Associated with NSAIDW<x> = 1
     * |        |          |Bit 18 Associated with NSAIDW<x> = 2
     * |        |          |Bit 31 Associated with NSAIDW<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set to 1, TZC-400 permits Non-secure write access to any access with the associated NSAIDW<x> value
     * |        |          |For example, if NSAIDW<x> is 3 and the corresponding nsaid_wr_en[3] bit is set HIGH then TZC-400 permits the Non-secure write access to progress.
     * @var TZC_T::REGION_BASE_LOW_4
     * Offset: 0x180  Controls the base address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |base_address_low_n_|Controls the base address bits[31:12] of Region <n>  For Region 0, this field is read-only The TZC-400 sets the base address of Region 0 to 0x0  The TZC-400 only permits a region to start at a 4KB aligned address and address bits[11:0] are zeros.
     * @var TZC_T::REGION_BASE_HIGH_4
     * Offset: 0x184  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_TOP_LOW_4
     * Offset: 0x188  Controls the region top address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |top_address_low_n_|Controls the region top address bits[31:12] of region <n>  This address points to the start of the next 4KB aligned address immediately outside the region.
     * @var TZC_T::REGION_TOP_HIGH_4
     * Offset: 0x18C  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_ATTRIBUTES_4
     * Offset: 0x190  Controls the permissions and target filter region enables.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |filter_en |Independent region enable for each filter unit Each bit is associated with a filter unit Set these bits as follows:  Bit 0 For Filter 0  Bit 1 For Filter 1  Bit 2 For Filter 2  Bit 3 For Filter 3. When set HIGH, it enables the use of the current region programming for the associated filter For Region 0, all bits are set HIGH and cannot be modified.
     * |[30]    |s_rd_en   |Secure global read enable This control bit defines the permissions for the Secure reads in the region  Set this bit as follows:  0 Secure read to the region is not permitted 1 Permits Secure read to the region.
     * |[31]    |s_wr_en   |Secure global write enable This control bit defines the permissions for the Secure writes in the region  Set this bit as follows:  0 Secure write to the region is not permitted 1 Permits Secure write to the region.
     * @var TZC_T::REGION_ID_ACCESS_4
     * Offset: 0x194  Controls the Non-secure access based on the NSAID inputs.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |nsaid_rd_en|NSAID read enables
     * |        |          |This enables NSAID inputs to define Non-secure read access permission Each bit of the nsaid_rd_en register field is associated with a value on the NSAIDR<x> signal as follows:  Bit 0 Associated with NSAIDR<x> = 0
     * |        |          |Bit 1 Associated with NSAIDR<x> = 1
     * |        |          |Bit 2 Associated with NSAIDR<x> = 2
     * |        |          |Bit 15 Associated with NSAIDR<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set HIGH, TZC-400 permits Non-secure read access to any access with the associated NSAIDR<x> value
     * |        |          |For example, if NSAIDR<x> is 3 and the corresponding nsaid_rd_en[3] bit is set HIGH then TZC-400 permits the Non-secure read access to progress.
     * |[31:16] |nsaid_wr_en|NSAID write enables
     * |        |          |This enables NSAID inputs to define Non-secure write access permission Each bit of the nsaid_wr_en register field is associated with a value on the NSAIDW<x> signal as follows:  Bit 16 Associated with NSAIDW<x> = 0
     * |        |          |Bit 17 Associated with NSAIDW<x> = 1
     * |        |          |Bit 18 Associated with NSAIDW<x> = 2
     * |        |          |Bit 31 Associated with NSAIDW<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set to 1, TZC-400 permits Non-secure write access to any access with the associated NSAIDW<x> value
     * |        |          |For example, if NSAIDW<x> is 3 and the corresponding nsaid_wr_en[3] bit is set HIGH then TZC-400 permits the Non-secure write access to progress.
     * @var TZC_T::REGION_BASE_LOW_5
     * Offset: 0x1A0  Controls the base address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |base_address_low_n_|Controls the base address bits[31:12] of Region <n>  For Region 0, this field is read-only The TZC-400 sets the base address of Region 0 to 0x0  The TZC-400 only permits a region to start at a 4KB aligned address and address bits[11:0] are zeros.
     * @var TZC_T::REGION_BASE_HIGH_5
     * Offset: 0x1A4  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_TOP_LOW_5
     * Offset: 0x1A8  Controls the region top address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |top_address_low_n_|Controls the region top address bits[31:12] of region <n>  This address points to the start of the next 4KB aligned address immediately outside the region.
     * @var TZC_T::REGION_TOP_HIGH_5
     * Offset: 0x1AC  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_ATTRIBUTES_5
     * Offset: 0x1B0  Controls the permissions and target filter region enables.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |filter_en |Independent region enable for each filter unit Each bit is associated with a filter unit Set these bits as follows:  Bit 0 For Filter 0  Bit 1 For Filter 1  Bit 2 For Filter 2  Bit 3 For Filter 3. When set HIGH, it enables the use of the current region programming for the associated filter For Region 0, all bits are set HIGH and cannot be modified.
     * |[30]    |s_rd_en   |Secure global read enable This control bit defines the permissions for the Secure reads in the region  Set this bit as follows:  0 Secure read to the region is not permitted 1 Permits Secure read to the region.
     * |[31]    |s_wr_en   |Secure global write enable This control bit defines the permissions for the Secure writes in the region  Set this bit as follows:  0 Secure write to the region is not permitted 1 Permits Secure write to the region.
     * @var TZC_T::REGION_ID_ACCESS_5
     * Offset: 0x1B4  Controls the Non-secure access based on the NSAID inputs.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |nsaid_rd_en|NSAID read enables
     * |        |          |This enables NSAID inputs to define Non-secure read access permission Each bit of the nsaid_rd_en register field is associated with a value on the NSAIDR<x> signal as follows:  Bit 0 Associated with NSAIDR<x> = 0
     * |        |          |Bit 1 Associated with NSAIDR<x> = 1
     * |        |          |Bit 2 Associated with NSAIDR<x> = 2
     * |        |          |Bit 15 Associated with NSAIDR<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set HIGH, TZC-400 permits Non-secure read access to any access with the associated NSAIDR<x> value
     * |        |          |For example, if NSAIDR<x> is 3 and the corresponding nsaid_rd_en[3] bit is set HIGH then TZC-400 permits the Non-secure read access to progress.
     * |[31:16] |nsaid_wr_en|NSAID write enables
     * |        |          |This enables NSAID inputs to define Non-secure write access permission Each bit of the nsaid_wr_en register field is associated with a value on the NSAIDW<x> signal as follows:  Bit 16 Associated with NSAIDW<x> = 0
     * |        |          |Bit 17 Associated with NSAIDW<x> = 1
     * |        |          |Bit 18 Associated with NSAIDW<x> = 2
     * |        |          |Bit 31 Associated with NSAIDW<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set to 1, TZC-400 permits Non-secure write access to any access with the associated NSAIDW<x> value
     * |        |          |For example, if NSAIDW<x> is 3 and the corresponding nsaid_wr_en[3] bit is set HIGH then TZC-400 permits the Non-secure write access to progress.
     * @var TZC_T::REGION_BASE_LOW_6
     * Offset: 0x1C0  Controls the base address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |base_address_low_n_|Controls the base address bits[31:12] of Region <n>  For Region 0, this field is read-only The TZC-400 sets the base address of Region 0 to 0x0  The TZC-400 only permits a region to start at a 4KB aligned address and address bits[11:0] are zeros.
     * @var TZC_T::REGION_BASE_HIGH_6
     * Offset: 0x1C4  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_TOP_LOW_6
     * Offset: 0x1C8  Controls the region top address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |top_address_low_n_|Controls the region top address bits[31:12] of region <n>  This address points to the start of the next 4KB aligned address immediately outside the region.
     * @var TZC_T::REGION_TOP_HIGH_6
     * Offset: 0x1CC  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_ATTRIBUTES_6
     * Offset: 0x1D0  Controls the permissions and target filter region enables.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |filter_en |Independent region enable for each filter unit Each bit is associated with a filter unit Set these bits as follows:  Bit 0 For Filter 0  Bit 1 For Filter 1  Bit 2 For Filter 2  Bit 3 For Filter 3. When set HIGH, it enables the use of the current region programming for the associated filter For Region 0, all bits are set HIGH and cannot be modified.
     * |[30]    |s_rd_en   |Secure global read enable This control bit defines the permissions for the Secure reads in the region  Set this bit as follows:  0 Secure read to the region is not permitted 1 Permits Secure read to the region.
     * |[31]    |s_wr_en   |Secure global write enable This control bit defines the permissions for the Secure writes in the region  Set this bit as follows:  0 Secure write to the region is not permitted 1 Permits Secure write to the region.
     * @var TZC_T::REGION_ID_ACCESS_6
     * Offset: 0x1D4  Controls the Non-secure access based on the NSAID inputs.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |nsaid_rd_en|NSAID read enables
     * |        |          |This enables NSAID inputs to define Non-secure read access permission Each bit of the nsaid_rd_en register field is associated with a value on the NSAIDR<x> signal as follows:  Bit 0 Associated with NSAIDR<x> = 0
     * |        |          |Bit 1 Associated with NSAIDR<x> = 1
     * |        |          |Bit 2 Associated with NSAIDR<x> = 2
     * |        |          |Bit 15 Associated with NSAIDR<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set HIGH, TZC-400 permits Non-secure read access to any access with the associated NSAIDR<x> value
     * |        |          |For example, if NSAIDR<x> is 3 and the corresponding nsaid_rd_en[3] bit is set HIGH then TZC-400 permits the Non-secure read access to progress.
     * |[31:16] |nsaid_wr_en|NSAID write enables
     * |        |          |This enables NSAID inputs to define Non-secure write access permission Each bit of the nsaid_wr_en register field is associated with a value on the NSAIDW<x> signal as follows:  Bit 16 Associated with NSAIDW<x> = 0
     * |        |          |Bit 17 Associated with NSAIDW<x> = 1
     * |        |          |Bit 18 Associated with NSAIDW<x> = 2
     * |        |          |Bit 31 Associated with NSAIDW<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set to 1, TZC-400 permits Non-secure write access to any access with the associated NSAIDW<x> value
     * |        |          |For example, if NSAIDW<x> is 3 and the corresponding nsaid_wr_en[3] bit is set HIGH then TZC-400 permits the Non-secure write access to progress.
     * @var TZC_T::REGION_BASE_LOW_7
     * Offset: 0x1E0  Controls the base address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |base_address_low_n_|Controls the base address bits[31:12] of Region <n>  For Region 0, this field is read-only The TZC-400 sets the base address of Region 0 to 0x0  The TZC-400 only permits a region to start at a 4KB aligned address and address bits[11:0] are zeros.
     * @var TZC_T::REGION_BASE_HIGH_7
     * Offset: 0x1E4  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_TOP_LOW_7
     * Offset: 0x1E8  Controls the region top address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |top_address_low_n_|Controls the region top address bits[31:12] of region <n>  This address points to the start of the next 4KB aligned address immediately outside the region.
     * @var TZC_T::REGION_TOP_HIGH_7
     * Offset: 0x1EC  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_ATTRIBUTES_7
     * Offset: 0x1F0  Controls the permissions and target filter region enables.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |filter_en |Independent region enable for each filter unit Each bit is associated with a filter unit Set these bits as follows:  Bit 0 For Filter 0  Bit 1 For Filter 1  Bit 2 For Filter 2  Bit 3 For Filter 3. When set HIGH, it enables the use of the current region programming for the associated filter For Region 0, all bits are set HIGH and cannot be modified.
     * |[30]    |s_rd_en   |Secure global read enable This control bit defines the permissions for the Secure reads in the region  Set this bit as follows:  0 Secure read to the region is not permitted 1 Permits Secure read to the region.
     * |[31]    |s_wr_en   |Secure global write enable This control bit defines the permissions for the Secure writes in the region  Set this bit as follows:  0 Secure write to the region is not permitted 1 Permits Secure write to the region.
     * @var TZC_T::REGION_ID_ACCESS_7
     * Offset: 0x1F4  Controls the Non-secure access based on the NSAID inputs.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |nsaid_rd_en|NSAID read enables
     * |        |          |This enables NSAID inputs to define Non-secure read access permission Each bit of the nsaid_rd_en register field is associated with a value on the NSAIDR<x> signal as follows:  Bit 0 Associated with NSAIDR<x> = 0
     * |        |          |Bit 1 Associated with NSAIDR<x> = 1
     * |        |          |Bit 2 Associated with NSAIDR<x> = 2
     * |        |          |Bit 15 Associated with NSAIDR<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set HIGH, TZC-400 permits Non-secure read access to any access with the associated NSAIDR<x> value
     * |        |          |For example, if NSAIDR<x> is 3 and the corresponding nsaid_rd_en[3] bit is set HIGH then TZC-400 permits the Non-secure read access to progress.
     * |[31:16] |nsaid_wr_en|NSAID write enables
     * |        |          |This enables NSAID inputs to define Non-secure write access permission Each bit of the nsaid_wr_en register field is associated with a value on the NSAIDW<x> signal as follows:  Bit 16 Associated with NSAIDW<x> = 0
     * |        |          |Bit 17 Associated with NSAIDW<x> = 1
     * |        |          |Bit 18 Associated with NSAIDW<x> = 2
     * |        |          |Bit 31 Associated with NSAIDW<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set to 1, TZC-400 permits Non-secure write access to any access with the associated NSAIDW<x> value
     * |        |          |For example, if NSAIDW<x> is 3 and the corresponding nsaid_wr_en[3] bit is set HIGH then TZC-400 permits the Non-secure write access to progress.
     * @var TZC_T::REGION_BASE_LOW_8
     * Offset: 0x200  Controls the base address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |base_address_low_n_|Controls the base address bits[31:12] of Region <n>  For Region 0, this field is read-only The TZC-400 sets the base address of Region 0 to 0x0  The TZC-400 only permits a region to start at a 4KB aligned address and address bits[11:0] are zeros.
     * @var TZC_T::REGION_BASE_HIGH_8
     * Offset: 0x204  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_TOP_LOW_8
     * Offset: 0x208  Controls the region top address bits[31:12] of Region <n>.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |top_address_low_n_|Controls the region top address bits[31:12] of region <n>  This address points to the start of the next 4KB aligned address immediately outside the region.
     * @var TZC_T::REGION_TOP_HIGH_8
     * Offset: 0x20C  Reserved
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var TZC_T::REGION_ATTRIBUTES_8
     * Offset: 0x210  Controls the permissions and target filter region enables.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |filter_en |Independent region enable for each filter unit Each bit is associated with a filter unit Set these bits as follows:  Bit 0 For Filter 0  Bit 1 For Filter 1  Bit 2 For Filter 2  Bit 3 For Filter 3. When set HIGH, it enables the use of the current region programming for the associated filter For Region 0, all bits are set HIGH and cannot be modified.
     * |[30]    |s_rd_en   |Secure global read enable This control bit defines the permissions for the Secure reads in the region  Set this bit as follows:  0 Secure read to the region is not permitted 1 Permits Secure read to the region.
     * |[31]    |s_wr_en   |Secure global write enable This control bit defines the permissions for the Secure writes in the region  Set this bit as follows:  0 Secure write to the region is not permitted 1 Permits Secure write to the region.
     * @var TZC_T::REGION_ID_ACCESS_8
     * Offset: 0x214  Controls the Non-secure access based on the NSAID inputs.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |nsaid_rd_en|NSAID read enables
     * |        |          |This enables NSAID inputs to define Non-secure read access permission Each bit of the nsaid_rd_en register field is associated with a value on the NSAIDR<x> signal as follows:  Bit 0 Associated with NSAIDR<x> = 0
     * |        |          |Bit 1 Associated with NSAIDR<x> = 1
     * |        |          |Bit 2 Associated with NSAIDR<x> = 2
     * |        |          |Bit 15 Associated with NSAIDR<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set HIGH, TZC-400 permits Non-secure read access to any access with the associated NSAIDR<x> value
     * |        |          |For example, if NSAIDR<x> is 3 and the corresponding nsaid_rd_en[3] bit is set HIGH then TZC-400 permits the Non-secure read access to progress.
     * |[31:16] |nsaid_wr_en|NSAID write enables
     * |        |          |This enables NSAID inputs to define Non-secure write access permission Each bit of the nsaid_wr_en register field is associated with a value on the NSAIDW<x> signal as follows:  Bit 16 Associated with NSAIDW<x> = 0
     * |        |          |Bit 17 Associated with NSAIDW<x> = 1
     * |        |          |Bit 18 Associated with NSAIDW<x> = 2
     * |        |          |Bit 31 Associated with NSAIDW<x> = 15
     * |        |          |<x> is the filter unit number
     * |        |          |When any bit in this field is set to 1, TZC-400 permits Non-secure write access to any access with the associated NSAIDW<x> value
     * |        |          |For example, if NSAIDW<x> is 3 and the corresponding nsaid_wr_en[3] bit is set HIGH then TZC-400 permits the Non-secure write access to progress.
     * @var TZC_T::PID4
     * Offset: 0xFD0  Provides the following information about the peripheral configurationu2022 4KB_count.u2022 Jep106_c_code.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |jep106_c_code|The JEP106 continuation code value represents how many 0x7F continuation characters occur in the manufacturer identity code These bits read back as 0x4 For information on the JEP106 standard, see the Additional reading section.
     * |[7:4]   |4KB_count |The number of 4KB address blocks required to access the registers, expressed in powers of 2 These bits read back as 0x0 This means that the TZC-400 occupies a single 4KB address block.
     * @var TZC_T::PID0
     * Offset: 0xFE0  The PID0 register provides the following information about the peripheral configuration:u2022 part_number_0.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |part_number_0|These bits read back as 0x60
     * @var TZC_T::PID1
     * Offset: 0xFE4  The PID1 register provides the following information about the peripheral configuration:u2022 part_number_1.u2022 Jep106_id_3_0.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |part_number_1|These bits read back as 0x4.
     * |[7:4]   |jep106_id_3_0|JEP106 identity code [3:0] See the JEP106, Standard Manufacturer Identification Code These bits read back as 0xB because ARM is the peripheral designer.
     * @var TZC_T::PID2
     * Offset: 0xFE8  The PID2 register provides the following information about the peripheral configuration:u2022 Jep106_id_6_4.u2022 Revision number.u2022 JEDEC use flag.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |jep106_id_6_4|JEP106 identity code [6:4] See the JEP106, Standard Manufacturer Identification Code These bits read back as 0b011 because ARM is the peripheral designer.
     * |[3]     |jedec_used|This indicates that the TZC-400 uses a manufacturer identity code that was allocated by JEDEC according to JEP106 This bit always reads back as 0x1.
     * |[7:4]   |revision  |Identifies the revision of the TZC-400 For revision r0p1, this field is set to 0x2.
     * @var TZC_T::PID3
     * Offset: 0xFEC  The PID3 register provides the following information about the peripheral configuration:u2022 Mod Number.u2022 RevAnd.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |mod_number|This is set to 0x0.
     * |[7:4]   |RevAnd    |The top-level RTL provides a 4-bit input, USERPID3REVAND, that is normally tied LOW and provides a read value of 0x0 When silicon is available, and if metal fixes are required, the manufacturer can modify the tie-offs to indicate a revision of the silicon.
     * @var TZC_T::CID0
     * Offset: 0xFF0  This is one of four 8-bit registers that together hold a 32-bit component ID value.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |comp_id_0 |These bits read back as 0x0D
     * @var TZC_T::CID1
     * Offset: 0xFF4  This is one of four 8-bit registers, that together hold a 32-bit component ID value.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |comp_id_0 |These bits read back as 0xF0
     * @var TZC_T::CID2
     * Offset: 0xFF8  This is one of four 8-bit registers, that together hold a 32-bit component ID value.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |comp_id_2 |These bits read back as 0x05
     * @var TZC_T::CID3
     * Offset: 0xFFC  This is one of four 8-bit registers that together hold a 32-bit component ID value.
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |comp_id_3 |These bits read back as 0xB1
     */
    __I  uint32_t BUILD_CONFIG;          /*!< [0x0000] Provides information about the configuration of the TZC-400.     */
    __IO uint32_t ACTION;                /*!< [0x0004] Controls the interrupt and bus response signaling behavior of the TZC-400 when region permission failures occur. */
    __IO uint32_t GATE_KEEPER;           /*!< [0x0008] Provides control and status for the gate keeper in each filter unit implemented */
    __IO uint32_t SPECULATION_CTRL;      /*!< [0x000c] Controls the read access speculation and write access speculation. */
    __I  uint32_t INT_STATUS;            /*!< [0x0010] Contains the status of the interrupt signal, TZCINT, that reports access security violations or region overlap errors. */
    __O  uint32_t INT_CLEAR;             /*!< [0x0014] Clears the interrupt.                                            */
    __I  uint32_t RESERVE0[2];
    FAIL_STS_T FAIL[3];                 /*!< [0x0020] Failed regions                                                   */
    __I  uint32_t RESERVE1[44];

    /*!< [0x0100] This register is read-only and is hard-wired to all zeros.       */
    REGION_T REGION[9];                  /*!< [0x0100] All structure regions in TZC.                                    */
    __I  uint32_t RESERVE10[876];
    __I  uint32_t PID4;                  /*!< [0x0fd0] Provides the following information about the peripheral configurationu2022 4KB_count.u2022 Jep106_c_code. */
    __I  uint32_t RESERVE11[3];
    __I  uint32_t PID0;                  /*!< [0x0fe0] The PID0 register provides the following information about the peripheral configuration:u2022 part_number_0. */
    __I  uint32_t PID1;                  /*!< [0x0fe4] The PID1 register provides the following information about the peripheral configuration:u2022 part_number_1.u2022 Jep106_id_3_0. */
    __I  uint32_t PID2;                  /*!< [0x0fe8] The PID2 register provides the following information about the peripheral configuration:u2022 Jep106_id_6_4.u2022 Revision number.u2022 JEDEC use flag. */
    __I  uint32_t PID3;                  /*!< [0x0fec] The PID3 register provides the following information about the peripheral configuration:u2022 Mod Number.u2022 RevAnd. */
    __I  uint32_t CID0;                  /*!< [0x0ff0] This is one of four 8-bit registers that together hold a 32-bit component ID value. */
    __I  uint32_t CID1;                  /*!< [0x0ff4] This is one of four 8-bit registers, that together hold a 32-bit component ID value. */
    __I  uint32_t CID2;                  /*!< [0x0ff8] This is one of four 8-bit registers, that together hold a 32-bit component ID value. */
    __I  uint32_t CID3;                  /*!< [0x0ffc] This is one of four 8-bit registers that together hold a 32-bit component ID value. */

} TZC_T;

/**
    @addtogroup TZC_CONST TZC Bit Field Definition
    Constant Definitions for TZC Controller
@{ */

#define TZC_BUILD_CONFIG_no_of_regions_Pos (0)                                            /*!< TZC_T::BUILD_CONFIG: no_of_regions Position*/
#define TZC_BUILD_CONFIG_no_of_regions_Msk (0x1ful << TZC_BUILD_CONFIG_no_of_regions_Pos) /*!< TZC_T::BUILD_CONFIG: no_of_regions Mask*/

#define TZC_BUILD_CONFIG_address_width_Pos (8)                                            /*!< TZC_T::BUILD_CONFIG: address_width Position*/
#define TZC_BUILD_CONFIG_address_width_Msk (0x3ful << TZC_BUILD_CONFIG_address_width_Pos) /*!< TZC_T::BUILD_CONFIG: address_width Mask*/

#define TZC_BUILD_CONFIG_no_of_filters_Pos (24)                                           /*!< TZC_T::BUILD_CONFIG: no_of_filters Position*/
#define TZC_BUILD_CONFIG_no_of_filters_Msk (0x3ul << TZC_BUILD_CONFIG_no_of_filters_Pos) /*!< TZC_T::BUILD_CONFIG: no_of_filters Mask*/

#define TZC_ACTION_reaction_value_Pos   (0)                                               /*!< TZC_T::ACTION: reaction_value Position*/
#define TZC_ACTION_reaction_value_Msk   (0x3ul << TZC_ACTION_reaction_value_Pos)         /*!< TZC_T::ACTION: reaction_value Mask    */

#define TZC_GATE_KEEPER_open_request_Pos (0)                                              /*!< TZC_T::GATE_KEEPER: open_request Position*/
#define TZC_GATE_KEEPER_open_request_Msk (0xful << TZC_GATE_KEEPER_open_request_Pos)     /*!< TZC_T::GATE_KEEPER: open_request Mask */

#define TZC_GATE_KEEPER_open_status_Pos (16)                                              /*!< TZC_T::GATE_KEEPER: open_status Position*/
#define TZC_GATE_KEEPER_open_status_Msk (0xful << TZC_GATE_KEEPER_open_status_Pos)       /*!< TZC_T::GATE_KEEPER: open_status Mask  */

#define TZC_SPECULATION_CTRL_read_spec_disable_Pos (0)                                    /*!< TZC_T::SPECULATION_CTRL: read_spec_disable Position*/
#define TZC_SPECULATION_CTRL_read_spec_disable_Msk (0x1ul << TZC_SPECULATION_CTRL_read_spec_disable_Pos) /*!< TZC_T::SPECULATION_CTRL: read_spec_disable Mask*/

#define TZC_SPECULATION_CTRL_write_spec_disable_Pos (1)                                   /*!< TZC_T::SPECULATION_CTRL: write_spec_disable Position*/
#define TZC_SPECULATION_CTRL_write_spec_disable_Msk (0x1ul << TZC_SPECULATION_CTRL_write_spec_disable_Pos) /*!< TZC_T::SPECULATION_CTRL: write_spec_disable Mask*/

#define TZC_INT_STATUS_status_Pos       (0)                                               /*!< TZC_T::INT_STATUS: status Position    */
#define TZC_INT_STATUS_status_Msk       (0xful << TZC_INT_STATUS_status_Pos)             /*!< TZC_T::INT_STATUS: status Mask        */

#define TZC_INT_STATUS_overrun_Pos      (8)                                               /*!< TZC_T::INT_STATUS: overrun Position   */
#define TZC_INT_STATUS_overrun_Msk      (0xful << TZC_INT_STATUS_overrun_Pos)            /*!< TZC_T::INT_STATUS: overrun Mask       */

#define TZC_INT_STATUS_overlap_Pos      (16)                                              /*!< TZC_T::INT_STATUS: overlap Position   */
#define TZC_INT_STATUS_overlap_Msk      (0xful << TZC_INT_STATUS_overlap_Pos)            /*!< TZC_T::INT_STATUS: overlap Mask       */

#define TZC_INT_CLEAR_clear_Pos         (0)                                               /*!< TZC_T::INT_CLEAR: clear Position      */
#define TZC_INT_CLEAR_clear_Msk         (0xful << TZC_INT_CLEAR_clear_Pos)               /*!< TZC_T::INT_CLEAR: clear Mask          */

#define TZC_FAIL_ADDRESS_LOW_addr_status_low_Pos (0)                                      /*!< TZC_T::FAIL_ADDRESS_LOW: addr_status_low Position*/
#define TZC_FAIL_ADDRESS_LOW_addr_status_low_Msk (0xfffffffful << TZC_FAIL_ADDRESS_LOW_addr_status_low_Pos) /*!< TZC_T::FAIL_ADDRESS_LOW: addr_status_low Mask*/

#define TZC_FAIL_CONTROL_Privileged_Pos (20)                                              /*!< TZC_T::FAIL_CONTROL: Privileged Position*/
#define TZC_FAIL_CONTROL_Privileged_Msk (0x1ul << TZC_FAIL_CONTROL_Privileged_Pos)        /*!< TZC_T::FAIL_CONTROL: Privileged Mask*/

#define TZC_FAIL_CONTROL_Non_secure_Pos (21)                                              /*!< TZC_T::FAIL_CONTROL: Non_secure Position*/
#define TZC_FAIL_CONTROL_Non_secure_Msk (0x1ul << TZC_FAIL_CONTROL_Non_secure_Pos)        /*!< TZC_T::FAIL_CONTROL: Non_secure Mask*/

#define TZC_FAIL_CONTROL_Direction_Pos (24)                                               /*!< TZC_T::FAIL_CONTROL: Direction Position*/
#define TZC_FAIL_CONTROL_Direction_Msk (0x1ul << TZC_FAIL_CONTROL_Direction_Pos)          /*!< TZC_T::FAIL_CONTROL: Direction Mask */

#define TZC_FAIL_ID_id_Pos            (0)                                                 /*!< TZC_T::FAIL_ID: id Position         */
#define TZC_FAIL_ID_id_Msk            (0x3ful << TZC_FAIL_ID_id_Pos)                      /*!< TZC_T::FAIL_ID: id Mask             */

#define TZC_FAIL_ID_vnet_Pos          (24)                                                /*!< TZC_T::FAIL_ID: vnet Position       */
#define TZC_FAIL_ID_vnet_Msk          (0xful << TZC_FAIL_ID_vnet_Pos)                     /*!< TZC_T::FAIL_ID: vnet Mask           */

#define TZC_REGION_BASE_LOW_base_address_low_n_Pos (12)                                   /*!< TZC_T::REGION_BASE_LOW: base_address_low_n_ Position*/
#define TZC_REGION_BASE_LOW_base_address_low_n_Msk (0xffffful << TZC_REGION_BASE_LOW_base_address_low_n_Pos) /*!< TZC_T::REGION_BASE_LOW: base_address_low_n_ Mask*/

#define TZC_REGION_TOP_LOW_top_address_low_n_Pos (12)                                     /*!< TZC_T::REGION_TOP_LOW: top_address_low_n_ Position*/
#define TZC_REGION_TOP_LOW_top_address_low_n_Msk (0xffffful << TZC_REGION_TOP_LOW_top_address_low_n_Pos) /*!< TZC_T::REGION_TOP_LOW: top_address_low_n_ Mask*/

#define TZC_REGION_ATTRIBUTES_filter_en_Pos (0)                                           /*!< TZC_T::REGION_ATTRIBUTES: filter_en Position*/
#define TZC_REGION_ATTRIBUTES_filter_en_Msk (0xful << TZC_REGION_ATTRIBUTES_filter_en_Pos) /*!< TZC_T::REGION_ATTRIBUTES: filter_en Mask*/

#define TZC_REGION_ATTRIBUTES_s_rd_en_Pos (30)                                            /*!< TZC_T::REGION_ATTRIBUTES: s_rd_en Position*/
#define TZC_REGION_ATTRIBUTES_s_rd_en_Msk (0x1ul << TZC_REGION_ATTRIBUTES_s_rd_en_Pos)    /*!< TZC_T::REGION_ATTRIBUTES: s_rd_en Mask*/

#define TZC_REGION_ATTRIBUTES_s_wr_en_Pos (31)                                            /*!< TZC_T::REGION_ATTRIBUTES: s_wr_en Position*/
#define TZC_REGION_ATTRIBUTES_s_wr_en_Msk (0x1ul << TZC_REGION_ATTRIBUTES_s_wr_en_Pos)    /*!< TZC_T::REGION_ATTRIBUTES: s_wr_en Mask*/

#define TZC_REGION_ID_ACCESS_nsaid_rd_en_Pos (0)                                          /*!< TZC_T::REGION_ID_ACCESS: nsaid_rd_en Position*/
#define TZC_REGION_ID_ACCESS_nsaid_rd_en_Msk (0xfffful << TZC_REGION_ID_ACCESS_nsaid_rd_en_Pos) /*!< TZC_T::REGION_ID_ACCESS: nsaid_rd_en Mask*/

#define TZC_REGION_ID_ACCESS_nsaid_wr_en_Pos (16)                                         /*!< TZC_T::REGION_ID_ACCESS: nsaid_wr_en Position*/
#define TZC_REGION_ID_ACCESS_nsaid_wr_en_Msk (0xfffful << TZC_REGION_ID_ACCESS_nsaid_wr_en_Pos) /*!< TZC_T::REGION_ID_ACCESS: nsaid_wr_en Mask*/

#define TZC_PID4_jep106_c_code_Pos      (0)                                               /*!< TZC_T::PID4: jep106_c_code Position   */
#define TZC_PID4_jep106_c_code_Msk      (0xful << TZC_PID4_jep106_c_code_Pos)            /*!< TZC_T::PID4: jep106_c_code Mask       */

#define TZC_PID4_4KB_count_Pos          (4)                                               /*!< TZC_T::PID4: 4KB_count Position       */
#define TZC_PID4_4KB_count_Msk          (0xful << TZC_PID4_4KB_count_Pos)                /*!< TZC_T::PID4: 4KB_count Mask           */

#define TZC_PID0_part_number_0_Pos      (0)                                               /*!< TZC_T::PID0: part_number_0 Position   */
#define TZC_PID0_part_number_0_Msk      (0xfful << TZC_PID0_part_number_0_Pos)           /*!< TZC_T::PID0: part_number_0 Mask       */

#define TZC_PID1_part_number_1_Pos      (0)                                               /*!< TZC_T::PID1: part_number_1 Position   */
#define TZC_PID1_part_number_1_Msk      (0xful << TZC_PID1_part_number_1_Pos)            /*!< TZC_T::PID1: part_number_1 Mask       */

#define TZC_PID1_jep106_id_3_0_Pos      (4)                                               /*!< TZC_T::PID1: jep106_id_3_0 Position   */
#define TZC_PID1_jep106_id_3_0_Msk      (0xful << TZC_PID1_jep106_id_3_0_Pos)            /*!< TZC_T::PID1: jep106_id_3_0 Mask       */

#define TZC_PID2_jep106_id_6_4_Pos      (0)                                               /*!< TZC_T::PID2: jep106_id_6_4 Position   */
#define TZC_PID2_jep106_id_6_4_Msk      (0x7ul << TZC_PID2_jep106_id_6_4_Pos)            /*!< TZC_T::PID2: jep106_id_6_4 Mask       */

#define TZC_PID2_jedec_used_Pos         (3)                                               /*!< TZC_T::PID2: jedec_used Position      */
#define TZC_PID2_jedec_used_Msk         (0x1ul << TZC_PID2_jedec_used_Pos)               /*!< TZC_T::PID2: jedec_used Mask          */

#define TZC_PID2_revision_Pos           (4)                                               /*!< TZC_T::PID2: revision Position        */
#define TZC_PID2_revision_Msk           (0xful << TZC_PID2_revision_Pos)                 /*!< TZC_T::PID2: revision Mask            */

#define TZC_PID3_mod_number_Pos         (0)                                               /*!< TZC_T::PID3: mod_number Position      */
#define TZC_PID3_mod_number_Msk         (0xful << TZC_PID3_mod_number_Pos)               /*!< TZC_T::PID3: mod_number Mask          */

#define TZC_PID3_RevAnd_Pos             (4)                                               /*!< TZC_T::PID3: RevAnd Position          */
#define TZC_PID3_RevAnd_Msk             (0xful << TZC_PID3_RevAnd_Pos)                   /*!< TZC_T::PID3: RevAnd Mask              */

#define TZC_CID0_comp_id_0_Pos          (0)                                               /*!< TZC_T::CID0: comp_id_0 Position       */
#define TZC_CID0_comp_id_0_Msk          (0xfful << TZC_CID0_comp_id_0_Pos)               /*!< TZC_T::CID0: comp_id_0 Mask           */

#define TZC_CID1_comp_id_0_Pos          (0)                                               /*!< TZC_T::CID1: comp_id_0 Position       */
#define TZC_CID1_comp_id_0_Msk          (0xfful << TZC_CID1_comp_id_0_Pos)               /*!< TZC_T::CID1: comp_id_0 Mask           */

#define TZC_CID2_comp_id_2_Pos          (0)                                               /*!< TZC_T::CID2: comp_id_2 Position       */
#define TZC_CID2_comp_id_2_Msk          (0xfful << TZC_CID2_comp_id_2_Pos)               /*!< TZC_T::CID2: comp_id_2 Mask           */

#define TZC_CID3_comp_id_3_Pos          (0)                                               /*!< TZC_T::CID3: comp_id_3 Position       */
#define TZC_CID3_comp_id_3_Msk          (0xfful << TZC_CID3_comp_id_3_Pos)               /*!< TZC_T::CID3: comp_id_3 Mask           */

/**@}*/ /* TZC_CONST */
/**@}*/ /* end of TZC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __SSMCC_REG_H__ */
