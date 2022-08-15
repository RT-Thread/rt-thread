# Core Library Release Notes
The Core Library provides basic types and utilities that can be used between different devices. This allows different libraries to share common items between themselves to avoid reimplementation and promote consistency.

### What's Included?
* Common result type for reporting errors or status
* Common utility MACROs for
    * CY_ASSERT: Verifies a value and halts if invalid (if not NDEBUG)
    * CY_HALT: Halts the application
    * CY_UNUSED_PARAMETER: Avoid warnings if a function argument isn't used
    * CY_LO8: Gets the lower 8 bits of a 16-bit value
    * CY_HI8: Gets the upper 8 bits of a 16-bit value
    * CY_LO16: Gets the lower 16 bits of a 32-bit value
    * CY_HI16: Gets the upper 16 bits of a 32-bit value
    * CY_SWAP_ENDIAN16: Swaps the byte ordering of a 16-bit value
    * CY_SWAP_ENDIAN32: Swaps the byte ordering of a 32-bit value
    * CY_SWAP_ENDIAN64: Swaps the byte ordering of a 64-bit value
    * CY_GET_REG8: Reads the 8-bit value from the specified address
    * CY_SET_REG8: Writes an 8-bit value to the specified address
    * CY_GET_REG16: Reads the 16-bit value from the specified address
    * CY_SET_REG16: Writes the 16-bit value to the specified address
    * CY_GET_REG24:  Reads the 24-bit value from the specified address
    * CY_SET_REG24: Writes the 24-bit value to the specified address
    * CY_GET_REG32: Reads the 32-bit value from the specified register
    * CY_SET_REG32: Writes the 32-bit value to the specified register
    * _CLR_SET_FLD32U:  The macro for setting a register with a name field and value for providing get-clear-modify-write operations
    * CY_REG32_CLR_SET: Uses _CLR_SET_FLD32U macro for providing get-clear-modify-write operations with a name field and value and writes a resulting value to the 32-bit register
    * _CLR_SET_FLD16U: The macro for setting a 16-bit register with a name field and value for providing get-clear-modify-write operations
    * CY_REG16_CLR_SET: Uses _CLR_SET_FLD16U macro for providing get-clear-modify-write operations with a name field and value and writes a resulting value to the 16-bit register
    * _CLR_SET_FLD8U: The macro for setting a 8-bit register with a name field and value for providing get-clear-modify-write operations
    * CY_REG8_CLR_SET: Uses _CLR_SET_FLD8U macro for providing get-clear-modify-write operations with a name field and value and writes a resulting value to the 8-bit register
    * _BOOL2FLD: Returns a field mask if the value is not false
    * _FLD2BOOL: Returns true, if the value includes the field mask
    * CY_SYSLIB_DIV_ROUND: Calculates a / b with rounding to the nearest integer, a and b must have the same sign.
    * CY_SYSLIB_DIV_ROUNDUP: Calculates a / b with rounding up if remainder != 0, both a and b must be positive.
* MACROs to create cross compiler compatible code. Use the CY_NOINIT, CY_SECTION, CY_UNUSED, CY_ALIGN attributes at the first place of declaration/definition. For example: CY_NOINIT uint32_t noinitVar;
    * CY_NOINIT
    * CY_SECTION
    * CY_UNUSED
    * CY_NOINLINE
    * CY_ALIGN
    * CY_RAMFUNC_BEGIN
    * CY_RAMFUNC_END

### What Changed?
#### v1.3.0
* Added a new CY_RSLT_CREATE_EX to provide more options for creating error codes
#### v1.2.0
* Added a new cy_rslt_decode_t that provides better debugging experience when examining result codes
* Converted module identifiers into enums to provide better debugging experience
#### v1.1.5
* Minor updates including new module id definitions
#### v1.1.4
* Minor updates for MISRA & documentation
#### v1.1.3
* Minor update for documentation & branding
#### v1.1.2
* Added new module identifiers to cy_result.h
#### v1.1.1
* Fixed MISRA violation
#### v1.1.0
* Migrated numerous utility & cross compiler macros from psoc6pdl into here
#### v1.0.1
* Added new module IDs in cy_result.h
* Minor updates to documentation
#### v1.0.0
* Initial release

### Supported Software and Tools
This version of the Core Library was validated for compatibility with the following Software and Tools:

| Software and Tools                        | Version |
| :---                                      | :----:  |
| ModusToolbox™ Software Environment        | 2.4.0   |
| GCC Compiler                              | 10.3.1  |
| IAR Compiler                              | 8.4     |
| ARM Compiler                              | 6.11    |

Minimum required ModusToolbox™ Software Environment: v2.0

### More information
Use the following links for more information, as needed:
* [API Reference Guide](https://infineon.github.io/core-lib/html/modules.html)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Infineon GitHub](https://github.com/infineon)
* [ModusToolbox™](https://www.cypress.com/products/modustoolbox-software-environment)

---
© Cypress Semiconductor Corporation (an Infineon company) or an affiliate of Cypress Semiconductor Corporation, 2019-2021.