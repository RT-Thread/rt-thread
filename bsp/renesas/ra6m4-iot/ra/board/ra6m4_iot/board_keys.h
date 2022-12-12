/***********************************************************************************************************************
 * File Name    : board_keys.h
 * Description  : This module has information about the keys on this board.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup BOARD_RA6M4
 * @defgroup BSP_RA6M4_IOT_KEYS Board keys
 * @brief key information for this board.
 *
 * This is code specific to the BSP_RA6M4_IOT board.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BOARD_KEYS_H
#define BOARD_KEYS_H

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Information on how many keys and what pins they are on. */
typedef struct st_bsp_keys
{
    uint16_t         key_count;        ///< The number of keys on this board
    uint16_t const * p_keys;           ///< Pointer to an array of IOPORT pins for controlling keys
} bsp_keys_t;

/** Available user-controllable keys on this board. These enums can be can be used to index into the array of key pins
 * found in the bsp_keys_t structure. */
typedef enum e_bsp_key
{
    BSP_KEY_KEY1=0,                  ///< TB KEY1
    BSP_KEY_KEY2=0,                  ///< TB KEY2
} bsp_key_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Public Functions
 **********************************************************************************************************************/
void key_sample (void);
/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER
#endif                                 /* BOARD_KEYS_H */

/** @} (end defgroup BSP_RA6M4_IOT_KEYS) */
