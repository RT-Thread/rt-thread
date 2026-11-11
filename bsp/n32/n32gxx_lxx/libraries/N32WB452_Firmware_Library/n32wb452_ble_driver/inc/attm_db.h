/**
 ****************************************************************************************
 *
 * @file attm_db.h
 *
 * @brief Header file - ATTM.
 *
 * Copyright (C) RivieraWaves 2009-2016
 *
 *
 ****************************************************************************************
 */

#ifndef ATTM_DB_H_
#define ATTM_DB_H_

/**
 ****************************************************************************************
 * @addtogroup ATTDB Database
 * @ingroup ATTM
 * @brief Attribute Protocol Database
 *
 * The ATTDB module is responsible for providing different sets of attribute databases
 * for Attribute Profile server.
 *
 * This module can be tailored by client, to match the requirement of the desired database.
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
#if (BLE_ATTS)
#include <string.h>
#include "rwip_config.h"
#include "ke_task.h"
#include "attm.h"
#include "gattm_task.h"

/*
 * DEFINES
 ****************************************************************************************
 */


/*
 * TYPE DEFINITION
 ****************************************************************************************
 */
#if (BLE_ATTS)

/**
 * Attribute Description
 */
struct attm_att_desc
{
    /**
     * 16 bits UUID or data offset used to retrieve 32 or 128 bits UUID in service memory block
     */
    uint16_t uuid;

    /**
     *  Attribute Permission (@see attm_perm_mask)
     */
    uint16_t perm;

    /**
     * value information (@see attm_value_perm_mask)
     */
    union att_info
    {
        /// attribute max length (RI = 1)
        uint16_t max_length;

        /// attribute value offset pointer (RI = 0)
        uint16_t offset;
    } info;
};

/// attribute value if present in database
struct attm_att_value
{
    /// Maximum attribute length
    uint16_t max_length;
    /// currrent attribute length that can be read.
    uint16_t length;
    ///value data pointer
    uint8_t  value[__ARRAY_EMPTY];
};

/// service description
struct attm_svc_desc
{
    /// Service Start Handle
    uint16_t start_hdl;
    /// Service End Handle
    uint16_t end_hdl;
    /// Task identifier that manages service
    uint16_t task_id;

    /**
     * Service Permission (@see attm_svc_perm_mask)
     */
    uint8_t perm;

    /// number of attributes present in service (end_hdl - start_hdl - 1)
    uint8_t nb_att;

    /// Service 16 bits UUID (LSB First) or data offset used to retrieve 32 or 128 bits
    /// UUID in service memory block
    uint16_t uuid;
};

/**
 * Service description present in attribute database
 */
struct attm_svc
{
    /// Next Service
    struct attm_svc* next;

    /// service description
    struct attm_svc_desc svc;

    /**
     * List of attribute description present in service.
     */
    struct attm_att_desc atts[__ARRAY_EMPTY];
};

/// Attribute element information
struct attm_elmt
{
    /// element info
    union elem_info
    {
        /// attribute info pointer
        struct attm_att_desc* att;

        /// service info pointer
        struct attm_svc_desc* svc;
    } info;

    /// use to know if current element is a service or an attribute
    bool service;
};

/// ATTM General Information Manager
struct attm_db
{
    /**
     * **************************************************************************************
     * @brief Attribute database
     *
     * The Attribute database is a list of attribute services sorted by handle number.
     * This database shall be initiate by GAP, GATT, profiles and application process at
     * startup and must not change during runtime.
     *
     * Database initialization shall be deterministic in order to always have service handle
     * at same position in database during all product life-cycle. This is required since
     * database client can save position of services in database to not perform service
     * discovery at each connection.
     ***************************************************************************************
     */
    struct attm_svc * svcs;

    /**
     ***************************************************************************************
     * Last attribute service searched.
     *
     * Used as a cached variable, it's used to reduce handle search duration.
     ***************************************************************************************
     */
    struct attm_svc * cache;

    /**
     * Temporary value used for read operation on service and characteristics attributes
     */
    uint8_t  temp_val[ATT_UUID_128_LEN + ATT_HANDLE_LEN + ATT_HANDLE_LEN];
};





#endif //(BLE_ATTS)

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 * Check if Service handle Range can be allocated in Database, and if handle should be
 * dynamically allocated, calculate first available handle range.
 *
 * @param[in|out] svc_desc Service information to add in DB
 *
 * @return status of operation
 */
uint8_t attmdb_svc_check_hdl(struct gattm_svc_desc* svc_desc);

/**
 ****************************************************************************************
 * @brief Add a service in database.
 *
 * According to service start handle and number of attribute, ATTM DB allocate a set of
 * attribute handles, then using other parameters it allocate a buffer used to describe
 * service, and allocate attributes + their values.
 *
 * If start_hdl = 0, it allocated service using first available handle (start_hdl is
 * modified); else it will allocate service according to given start handle.
 *
 *
 * @param[in|out] svc_desc Service description.
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If service allocation succeeds.
 *  - @ref ATT_ERR_INVALID_HANDLE: If start_hdl given in parameter or UUIDs value invalid
 *  - @ref ATT_ERR_INSUFF_RESOURCE: There is not enough memory to allocate service buffer.
 ****************************************************************************************
 */
uint8_t attmdb_add_service(struct gattm_svc_desc* svc_desc);




/**
 ****************************************************************************************
 *  @brief Search in database from which service attribute handle comes from.
 *
 * @param[in] handle Attribute handle.
 *
 * @return Services that contains attribute handle; NULL if handle not available in
 *         database.
 ****************************************************************************************
 */
struct attm_svc * attmdb_get_service(uint16_t handle);

/**
 ****************************************************************************************
 *  @brief Search in database Attribute pointer using attribute handle.
 *
 * @param[in]  handle   Attribute handle.
 * @param[out] elmt     Attribute element to fill
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If attribute found.
 *  - @ref ATT_ERR_INVALID_HANDLE: If No Attribute found
 ****************************************************************************************
 */
uint8_t attmdb_get_attribute(uint16_t handle, struct attm_elmt*elmt);

/**
 ****************************************************************************************
 * @brief Retrieve attribute at or after specified handle
 *
 * Retrieve first attribute with handle >= parameter handle.
 * Parameter handle is updated according found attribute.
 *
 * @param[in|out] handle   Attribute handle.
 * @param[out]    elmt     Attribute element to fill
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If attribute found.
 *  - @ref ATT_ERR_INVALID_HANDLE: If No Attribute found
 ****************************************************************************************
 */
uint8_t attmdb_get_next_att(uint16_t * handle, struct attm_elmt*elmt);

/**
 ****************************************************************************************
 * Check if attribute element UUID is equals to uuid given in parameter.
 *
 * @param elmt     Attribute element that can be a UUID 16 or 128 bits
 * @param uuid16   UUID 16 bits to compare
 *
 * @return True if UUIDs matches, False else.
 ****************************************************************************************
 */
bool attmdb_uuid16_comp(struct attm_elmt *elmt, uint16_t uuid16);

/**
 ****************************************************************************************
 * @brief Retrieve attribute value Max Length
 *
 * @param[in]  elmt    Attribute element information
 * @param[out] length  Max length Size of attribute value
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If request succeeds
 *  - @ref ATT_ERR_REQUEST_NOT_SUPPORTED: If attribute is read only
 ****************************************************************************************
 */
uint8_t attmdb_get_max_len(struct attm_elmt* elmt, att_size_t* length);


/**
 ****************************************************************************************
 * @brief Retrieve attribute UUID
 *
 * @param[in]  elmt     Attribute information.
 * @param[out] uuid_len Size of attribute UUID
 * @param[out] uuid     UUID value to update
 * @param[in]  srv_uuid For a service, if set, return service UUID
 * @param[in]  air      Prepare UUID for the air (For a 32 bit UUID, returns a 128 bit UUID)
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If request succeeds
 *  - @ref ATT_ERR_INVALID_HANDLE: If handle doesn't exist in database
 ****************************************************************************************
 */
uint8_t attmdb_get_uuid(struct attm_elmt *elmt, uint8_t* uuid_len, uint8_t* uuid, bool srv_uuid, bool air);

/**
 ****************************************************************************************
 * @brief Retrieve attribute permission
 * If access mask is set, service authentication or encryption key size value can be loaded.
 *
 * @param[in]  handle      Attribute handle.
 * @param[out] perm        Permission value to return
 * @param[in]  mode_mask   Mode Access mask to check type of access
 *                         parameter (0 return full attribute permission)
 * @param[in]  perm_mask   Permission Access mask to check only specific permission
 * @param[in|out] elmt     Attribute information
 *
 * @return Command status code:
 *  - @ref ATT_ERR_NO_ERROR: If request succeeds
 *  - @ref ATT_ERR_INVALID_HANDLE: If handle doesn't exist in database.
 *  - @ref ATT_ERR_REQUEST_NOT_SUPPORTED: If mode is disabled.
 *  - @ref ATT_ERR_INSUFF_AUTHOR: when service is disabled.
 *  - @ref ATT_ERR_INSUFF_ENC_KEY_SIZE:
 ****************************************************************************************
 */
uint8_t attmdb_att_get_permission(uint16_t handle, uint16_t* perm, uint16_t mode_mask,
                                  uint16_t perm_mask, struct attm_elmt *elmt);


#if (BLE_DEBUG)

/**
 ****************************************************************************************
 * @brief Retrieve number of services.
 *
 * @return number of services
 ****************************************************************************************
 */
uint8_t attmdb_get_nb_svc(void);

/**
 ****************************************************************************************
 * @brief Retrieve services informations
 *
 * @param[in] svc_info Services information array to update
 ****************************************************************************************
 */
void attmdb_get_svc_info(struct gattm_svc_info* svc_info);
#endif /* (BLE_DEBUG) */

#endif // #if (BLE_ATTS)

/// @} ATTDB
#endif // ATTM_DB_H_
