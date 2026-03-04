/**
 ****************************************************************************************
 *
 * @file attm.h
 *
 * @brief Header file - ATTM.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef ATTM_H_
#define ATTM_H_

/**
 ****************************************************************************************
 * @addtogroup ATTM Attribute Manager
 * @ingroup ATT
 * @brief Attribute Manager
 *
 * The ATTM is the attribute manager of the Attribute Profile block and
 * is responsible for managing messages and providing generic attribute
 * functionalities to @ref ATTC "ATTC" and @ref ATTS "ATTS".
 *
 *
 * @{
 *
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#include <string.h>
#include <stdbool.h>

#include "co_error.h"
#include "att.h"
#include "ke_task.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/// update attribute permission on specific handle
#define ATTMDB_UPDATE_PERM(handle, access, right)\
    attm_att_update_perm(handle, (PERM_MASK_ ## access), PERM(access, right))

#define ATTMDB_UPDATE_PERM_VAL(handle, access, val)\
    attm_att_update_perm(handle, (PERM_MASK_ ## access), ((val) << (PERM_POS_ ## access)))



/*
 * DATA STRUCTURES
 ****************************************************************************************
 */

/// Internal 16bits UUID service description
struct attm_desc
{
    /// 16 bits UUID LSB First
    uint16_t uuid;
    /// Attribute Permissions (@see enum attm_perm_mask)
    uint16_t perm;
    /// Attribute Extended Permissions (@see enum attm_value_perm_mask)
    uint16_t ext_perm;
    /// Attribute Max Size
    /// note: for characteristic declaration contains handle offset
    /// note: for included service, contains target service handle
    uint16_t max_size;
};


/// Internal 128bits UUID service description
struct attm_desc_128
{
    /// 128 bits UUID LSB First
    uint8_t uuid[ATT_UUID_128_LEN];
    /// Attribute Permissions (@see enum attm_perm_mask)
    uint16_t perm;
    /// Attribute Extended Permissions (@see enum attm_value_perm_mask)
    uint16_t ext_perm;
    /// Attribute Max Size
    /// note: for characteristic declaration contains handle offset
    /// note: for included service, contains target service handle
    uint16_t max_size;
};



#if (BLE_CENTRAL || BLE_PERIPHERAL)
/*
 * GLOBAL VARIABLE DECLARATIONS
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/**
 ****************************************************************************************
 * @brief Compare if two UUIDs matches
 *
 * @param[in]  uuid_a      UUID A value
 * @param[in]  uuid_a_len  UUID A length
 * @param[in]  uuid_b      UUID B value
 * @param[in]  uuid_b_len  UUID B length
 *
 * @return true if UUIDs matches, false otherwise
 ****************************************************************************************
 */
bool attm_uuid_comp(const uint8_t *uuid_a, uint8_t uuid_a_len,
                      const uint8_t *uuid_b, uint8_t uuid_b_len);


/**
 ****************************************************************************************
 * @brief Check if two UUIDs matches (2nd UUID is a 16 bits UUID with LSB First)
 *
 * @param[in]  uuid_a      UUID A value
 * @param[in]  uuid_a_len  UUID A length
 * @param[in]  uuid_b      UUID B 16 bit value
 *
 * @return true if UUIDs matches, false otherwise
 ****************************************************************************************
 */
bool attm_uuid16_comp(uint8_t *uuid_a, uint8_t uuid_a_len, uint16_t uuid_b);


/**
 ****************************************************************************************
 * @brief Convert UUID value to 128 bit UUID
 *
 * @param[out] uuid128   converted 32-bit Bluetooth UUID to 128-bit UUID
 * @param[in]  uuid      UUID to convert to 128-bit UUID
 * @param[in]  uuid_len  UUID length
 *
 ****************************************************************************************
 */
void attm_convert_to128(uint8_t *uuid128, const uint8_t *uuid, uint8_t uuid_len);

/**
 ****************************************************************************************
 * @brief Check if it's a Bluetooth 16-bits UUID for 128-bit input
 *
 * @param[in]  uuid      128-bit UUID
 *
 * @return true if uuid  is a Bluetooth 16-bit UUID, false else.
 ****************************************************************************************
 */
bool attm_is_bt16_uuid(uint8_t *uuid);

/**
 ****************************************************************************************
 * @brief Check if it's a Bluetooth 32 bits UUID for 128-bit input
 *
 * @param[in]  uuid      128-bit UUID
 *
 * @return true if uuid  is a Bluetooth 32-bits UUID, false else.
 ****************************************************************************************
 */
bool attm_is_bt32_uuid(uint8_t *uuid);


#if (BLE_ATTS)
/**
 ****************************************************************************************
 * @brief Function use to ease service database creation.
 * Use @see attmdb_add_service function of attmdb module to create service database,
 * then use @see attmdb_add_attribute function of attmdb module to create attributes
 * according to database description array given in parameter.
 *
 * @note: database description array shall be const to reduce memory consumption (only ROM)
 * @note: It supports only 16 bits UUIDs
 *
 * @note: If shdl = 0, it return handle using first available handle (shdl is
 * modified); else it verifies if start handle given can be used to allocates handle range.
 *
 * @param[in|out] shdl          Service start handle.
 * @param[in]     uuid          Service UUID
 * @param[in|out] cfg_flag      Configuration Flag, each bit matches with an attribute of
 *                              att_db (Max: 32 attributes); if the bit is set to 1, the
 *                              attribute will be added in the service.
 * @param[in]     max_nb_att    Number of attributes in the service
 * @param[in|out] att_tbl       Array which will be fulfilled with the difference between
 *                              each characteristic handle and the service start handle.
 *                              This array is useful if several characteristics are optional
 *                              within the service, can be set to NULL if not needed.
 * @param[in]     dest_id       Task ID linked to the service. This task will be notified
 *                              each time the service content is modified by a peer device.
 * @param[in|out] att_db        Table containing all attributes information
 * @param[in]     svc_perm      Service permission (@see enum attm_svc_perm_mask)
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If database creation succeeds.
 *  - @ref ATT_ERR_INVALID_HANDLE: If start_hdl given in parameter + nb of attribute override
 *                            some existing services handles.
 *  - @ref ATT_ERR_INSUFF_RESOURCE: There is not enough memory to allocate service buffer.
 *                           or of new attribute cannot be added because all expected
 *                           attributes already added or buffer overflow detected during
 *                           allocation
 ****************************************************************************************
 */
uint8_t attm_svc_create_db(uint16_t *shdl, uint16_t uuid, uint8_t *cfg_flag, uint8_t max_nb_att,
                           uint8_t *att_tbl, ke_task_id_t const dest_id,
                           const struct attm_desc *att_db, uint8_t svc_perm);



/**
 ****************************************************************************************
 * @brief Function use to ease service database creation.
 * Use @see attmdb_add_service function of attmdb module to create service database,
 * then use @see attmdb_add_attribute function of attmdb module to create attributes
 * according to database description array given in parameter.
 *
 * @note: database description array shall be const to reduce memory consumption (only ROM)
 * @note: It supports 128, 32 and 16 bits UUIDs
 *
 * @note: If shdl = 0, it return handle using first available handle (shdl is
 * modified); else it verifies if start handle given can be used to allocates handle range.
 *
 * @param[in|out] shdl          Service start handle.
 * @param[in]     uuid          Service UUID
 * @param[in|out] cfg_flag      Configuration Flag, each bit matches with an attribute of
 *                              att_db (Max: 32 attributes); if the bit is set to 1, the
 *                              attribute will be added in the service.
 * @param[in]     max_nb_att    Number of attributes in the service
 * @param[in|out] att_tbl       Array which will be fulfilled with the difference between
 *                              each characteristic handle and the service start handle.
 *                              This array is useful if several characteristics are optional
 *                              within the service, can be set to NULL if not needed.
 * @param[in]     dest_id       Task ID linked to the service. This task will be notified
 *                              each time the service content is modified by a peer device.
 * @param[in|out] att_db        Table containing all attributes information
 * @param[in]     svc_perm      Service permission (@see enum attm_svc_perm_mask)
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If database creation succeeds.
 *  - @ref ATT_ERR_INVALID_HANDLE: If start_hdl given in parameter + nb of attribute override
 *                            some existing services handles.
 *  - @ref ATT_ERR_INSUFF_RESOURCE: There is not enough memory to allocate service buffer.
 *                           or of new attribute cannot be added because all expected
 *                           attributes already added or buffer overflow detected during
 *                           allocation
 ****************************************************************************************
 */
uint8_t attm_svc_create_db_128(uint16_t *shdl, const uint8_t* uuid, uint8_t *cfg_flag, uint8_t max_nb_att,
                               uint8_t *att_tbl, ke_task_id_t const dest_id,
                               const struct attm_desc_128 *att_db, uint8_t svc_perm);

/**
 ****************************************************************************************
 * @brief Function use to verify if several services can be allocated on a contiguous
 * handle range. If this command succeed, it means that service allocation will succeed.
 *
 * If start_hdl = 0, it return handle using first available handle (start_hdl is
 * modified); else it verifies if start handle given can be used to allocates handle range.
 *
 * @param[in|out] start_hdl     Service start handle.
 * @param[in]     nb_att        Number of handle to allocate (containing service handles)
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If service allocation succeeds.
 *  - @ref ATT_ERR_INVALID_HANDLE: If start_hdl given in parameter or UUIDs value invalid
 ****************************************************************************************
 */
uint8_t attm_reserve_handle_range(uint16_t* start_hdl, uint8_t nb_att);



/**
 ****************************************************************************************
 * @brief Update attribute value
 *
 * Updating attribute value do not trigger any notification or indication, this shall be
 * handled by GATT task.
 *
 * @param[in] handle Attribute handle.
 * @param[in] length Size of new attribute value
 * @param[in] offset Data offset of in the payload to set
 * @param[in] value  Attribute value payload
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If attribute value update succeeds
 *  - @ref ATT_ERR_INVALID_HANDLE: If handle doesn't exist in database
 *  - @ref ATT_ERR_REQUEST_NOT_SUPPORTED: If attribute data not present in database or
 *                                        cannot be modified
 *  - @ref ATT_ERR_INVALID_ATTRIBUTE_VAL_LEN: If new value length exceeds maximum attribute
 *                              value length.
 *
 ****************************************************************************************
 */
uint8_t attm_att_set_value(uint16_t handle, att_size_t length, att_size_t offset, uint8_t* value);

/**
 ****************************************************************************************
 * @brief Retrieve attribute value

 *
 * @param[in]  handle Attribute handle.
 * @param[out] length Size of attribute value
 * @param[out] value  Pointer to attribute value payload
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If request succeeds
 *  - @ref ATT_ERR_INVALID_HANDLE: If handle doesn't exist in database
 *  - @ref ATT_ERR_REQUEST_NOT_SUPPORTED: If attribute data not present in database
 ****************************************************************************************
 */
uint8_t attm_get_value(uint16_t handle, att_size_t* length, uint8_t** value);


/**
 ****************************************************************************************
 * @brief Update attribute permission
 *
 * @param[in] handle Attribute handle.
 *  - @ref ATT_ERR_REQUEST_NOT_SUPPORTED: If attribute data not present in database
 * @param[in] perm       New attribute permission
 * @param[in] ext_perm   New attribute extended permission
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If request succeeds
 *  - @ref ATT_ERR_INVALID_HANDLE: If handle doesn't exist in database
 *  - @ref ATT_ERR_REQUEST_NOT_SUPPORTED: If attribute permission is fixed
 ****************************************************************************************
 */
uint8_t attm_att_set_permission(uint16_t handle, uint16_t perm, uint16_t ext_perm);


/**
 ****************************************************************************************
 * @brief Reset some permissions bit in the Handle passed as parameter.
 *
 * @param[in] handle      Attribute handle.
 * @param[in] access_mask Access mask of permission to update
 * @param[in] perm        New value of the permission to update
 *
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If request succeeds
 *  - @ref ATT_ERR_INVALID_HANDLE: If handle doesn't exist in database
 *  - @ref ATT_ERR_REQUEST_NOT_SUPPORTED: If attribute permission is fixed
 ****************************************************************************************
 */
uint8_t attm_att_update_perm(uint16_t handle, uint16_t access_mask, uint16_t perm);

/**
 ****************************************************************************************
 * @brief Update attribute service permission
 *
 * @param[in] handle Attribute handle.
 * @param[in] perm   New attribute permission
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If request succeeds
 *  - @ref ATT_ERR_INVALID_HANDLE: If handle doesn't exist in database
 ****************************************************************************************
 */
uint8_t attm_svc_set_permission(uint16_t handle, uint8_t perm);


/**
 ****************************************************************************************
 * @brief Retrieve attribute service permission
 *
 * @param[in]  handle Attribute handle.
 * @param[out] perm   Permission value to return
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If request succeeds
 *  - @ref ATT_ERR_INVALID_HANDLE: If handle doesn't exist in database
 ****************************************************************************************
 */
uint8_t attm_svc_get_permission(uint16_t handle, uint8_t* perm);


/**
 ****************************************************************************************
 * @brief Clear database
 *
 * For debug purpose only, this function clear the database and unalloc all services
 * within database.
 *
 * This function shall be used only for qualification and tests in order to manually
 * change database without modifying software.
 ****************************************************************************************
 */
void attmdb_destroy(void);

/**
 ****************************************************************************************
 * @brief Initialize Attribute Database (clear it)
 *
 * @param[in] reset  true if it's requested by a reset; false if it's boot initialization
 ****************************************************************************************
 */
void attm_init(bool reset);
#endif // (BLE_ATTS)

#endif // #if (BLE_CENTRAL || BLE_PERIPHERAL)
/// @} ATTM
#endif // ATTM_H_
