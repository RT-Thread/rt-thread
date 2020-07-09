/*
 * \file
 *
 * \brief ATSHA204 header file for the command marshaling layer for the device
 *
   <table>
     <caption>Command Packet Structure</caption>
     <tr>
       <th width=25%>Byte #</th> <th width=25%>Name</th> <th>Meaning</th>
     </tr>
     <tr>
       <td>0</td>
       <td>Count</td>
       <td>Number of bytes in the packet, includes the count byte, body and the checksum</td>
     </tr>
     <tr>
       <td>1</td>
       <td>Ordinal</td>
       <td>Command Opcode (Ordinal)</td>
     </tr>
     <tr>
       <td>2 to n</td>
       <td>Parameters</td>
       <td>Parameters for specific command</td>
     </tr>
     <tr>
       <td>n+1 to n+2</td>
       <td>Checksum</td>
       <td>Checksum of the command packet</td>
     </tr>
   </table>
 *
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef SHA204_COMMAND_MARSHALING_H
#   define SHA204_COMMAND_MARSHALING_H

#include "sha204_comm.h"

/** \todo Create doxygen groups. */

//////////////////////////////////////////////////////////////////////
// command op-code definitions
#define SHA204_CHECKMAC                 ((uint8_t) 0x28)       //!< CheckMac command op-code
#define SHA204_DERIVE_KEY               ((uint8_t) 0x1C)       //!< DeriveKey command op-code
#define SHA204_DEVREV                   ((uint8_t) 0x30)       //!< DevRev command op-code
#define SHA204_GENDIG                   ((uint8_t) 0x15)       //!< GenDig command op-code
#define SHA204_HMAC                     ((uint8_t) 0x11)       //!< HMAC command op-code
#define SHA204_LOCK                     ((uint8_t) 0x17)       //!< Lock command op-code
#define SHA204_MAC                      ((uint8_t) 0x08)       //!< MAC command op-code
#define SHA204_NONCE                    ((uint8_t) 0x16)       //!< Nonce command op-code
#define SHA204_PAUSE                    ((uint8_t) 0x01)       //!< Pause command op-code
#define SHA204_RANDOM                   ((uint8_t) 0x1B)       //!< Random command op-code
#define SHA204_READ                     ((uint8_t) 0x02)       //!< Read command op-code
#define SHA204_UPDATE_EXTRA             ((uint8_t) 0x20)       //!< UpdateExtra command op-code
#define SHA204_WRITE                    ((uint8_t) 0x12)       //!< Write command op-code


//////////////////////////////////////////////////////////////////////
// packet size definitions
#define SHA204_RSP_SIZE_VAL             ((uint8_t)  7)         //!< size of response packet containing four bytes of data

//////////////////////////////////////////////////////////////////////
// parameter range definitions
#define SHA204_KEY_ID_MAX               ((uint8_t) 15)         //!< maximum value for key id
#define SHA204_OTP_BLOCK_MAX            ((uint8_t)  1)         //!< maximum value for OTP block

//////////////////////////////////////////////////////////////////////
// definitions for command packet indexes common to all commands
#define SHA204_COUNT_IDX                ( 0)                   //!< command packet index for count
#define SHA204_OPCODE_IDX               ( 1)                   //!< command packet index for op-code
#define SHA204_PARAM1_IDX               ( 2)                   //!< command packet index for first parameter
#define SHA204_PARAM2_IDX               ( 3)                   //!< command packet index for second parameter
#define SHA204_DATA_IDX                 ( 5)                   //!< command packet index for second parameter

//////////////////////////////////////////////////////////////////////
// zone definitions
#define SHA204_ZONE_CONFIG              ((uint8_t)  0x00)      //!< Configuration zone
#define SHA204_ZONE_OTP                 ((uint8_t)  0x01)      //!< OTP (One Time Programming) zone
#define SHA204_ZONE_DATA                ((uint8_t)  0x02)      //!< Data zone
#define SHA204_ZONE_MASK                ((uint8_t)  0x03)      //!< Zone mask
#define SHA204_ZONE_COUNT_FLAG          ((uint8_t)  0x80)      //!< Zone bit 7 set: Access 32 bytes, otherwise 4 bytes.
#define SHA204_ZONE_ACCESS_4            ((uint8_t)     4)      //!< Read or write 4 bytes.
#define SHA204_ZONE_ACCESS_32           ((uint8_t)    32)      //!< Read or write 32 bytes.
#define SHA204_ADDRESS_MASK_CONFIG      (         0x001F)      //!< Address bits 5 to 7 are 0 for Configuration zone.
#define SHA204_ADDRESS_MASK_OTP         (         0x000F)      //!< Address bits 4 to 7 are 0 for OTP zone.
#define SHA204_ADDRESS_MASK             (         0x007F)    //!< Address bit 7 to 15 are always 0.

//////////////////////////////////////////////////////////////////////
// CheckMAC command definitions
#define CHECKMAC_MODE_IDX               SHA204_PARAM1_IDX      //!< CheckMAC command index for mode
#define CHECKMAC_KEYID_IDX              SHA204_PARAM2_IDX      //!< CheckMAC command index for key identifier
#define CHECKMAC_CLIENT_CHALLENGE_IDX   SHA204_DATA_IDX        //!< CheckMAC command index for client challenge
#define CHECKMAC_CLIENT_RESPONSE_IDX    (37)                   //!< CheckMAC command index for client response
#define CHECKMAC_DATA_IDX               (69)                   //!< CheckMAC command index for other data
#define CHECKMAC_COUNT                  (84)                   //!< CheckMAC command packet size
#define CHECKMAC_MODE_MASK              ((uint8_t) 0x27)       //!< CheckMAC mode bits 3, 4, 6, and 7 are 0.
#define CHECKMAC_CLIENT_CHALLENGE_SIZE  (32)                   //!< CheckMAC size of client challenge
#define CHECKMAC_CLIENT_RESPONSE_SIZE   (32)                   //!< CheckMAC size of client response
#define CHECKMAC_OTHER_DATA_SIZE        (13)                   //!< CheckMAC size of "other data"
#define CHECKMAC_CLIENT_COMMAND_SIZE    ( 4)                   //!< CheckMAC size of client command header size inside "other data"

//////////////////////////////////////////////////////////////////////
// DeriveKey command definitions
#define DERIVE_KEY_RANDOM_IDX           SHA204_PARAM1_IDX      //!< DeriveKey command index for random bit
#define DERIVE_KEY_TARGETKEY_IDX        SHA204_PARAM2_IDX      //!< DeriveKey command index for target slot
#define DERIVE_KEY_MAC_IDX              SHA204_DATA_IDX        //!< DeriveKey command index for optional MAC
#define DERIVE_KEY_COUNT_SMALL          SHA204_CMD_SIZE_MIN    //!< DeriveKey command packet size without MAC
#define DERIVE_KEY_COUNT_LARGE          (39)                   //!< DeriveKey command packet size with MAC
#define DERIVE_KEY_RANDOM_FLAG          ((uint8_t) 4)          //!< DeriveKey 1. parameter
#define DERIVE_KEY_MAC_SIZE             (32)                   //!< DeriveKey MAC size

//////////////////////////////////////////////////////////////////////
// DevRev command definitions
#define DEVREV_PARAM1_IDX               SHA204_PARAM1_IDX      //!< DevRev command index for 1. parameter (ignored)
#define DEVREV_PARAM2_IDX               SHA204_PARAM2_IDX      //!< DevRev command index for 2. parameter (ignored)
#define DEVREV_COUNT                    SHA204_CMD_SIZE_MIN    //!< DevRev command packet size

//////////////////////////////////////////////////////////////////////
// GenDig command definitions
#define GENDIG_ZONE_IDX                 SHA204_PARAM1_IDX      //!< GenDig command index for zone
#define GENDIG_KEYID_IDX                SHA204_PARAM2_IDX      //!< GenDig command index for key id
#define GENDIG_DATA_IDX                 SHA204_DATA_IDX        //!< GenDig command index for optional data
#define GENDIG_COUNT                    SHA204_CMD_SIZE_MIN    //!< GenDig command packet size without "other data"
#define GENDIG_COUNT_DATA               (11)                   //!< GenDig command packet size with "other data"
#define GENDIG_OTHER_DATA_SIZE          (4)                    //!< GenDig size of "other data"
#define GENDIG_ZONE_OTP                 ((uint8_t) 1)          //!< GenDig zone id OTP
#define GENDIG_ZONE_DATA                ((uint8_t) 2)          //!< GenDig zone id data

//////////////////////////////////////////////////////////////////////
// HMAC command definitions
#define HMAC_MODE_IDX                   SHA204_PARAM1_IDX      //!< HMAC command index for mode
#define HMAC_KEYID_IDX                  SHA204_PARAM2_IDX      //!< HMAC command index for key id
#define HMAC_COUNT                      SHA204_CMD_SIZE_MIN    //!< HMAC command packet size
#define HMAC_MODE_MASK                  ((uint8_t) 0x74)       //!< HMAC mode bits 0, 1, 3, and 7 are 0.

//////////////////////////////////////////////////////////////////////
// Lock command definitions
#define LOCK_ZONE_IDX                   SHA204_PARAM1_IDX      //!< Lock command index for zone
#define LOCK_SUMMARY_IDX                SHA204_PARAM2_IDX      //!< Lock command index for summary
#define LOCK_COUNT                      SHA204_CMD_SIZE_MIN    //!< Lock command packet size
#define LOCK_ZONE_NO_CONFIG             ((uint8_t) 0x01)       //!< Lock zone is OTP or Data
#define LOCK_ZONE_NO_CRC                ((uint8_t) 0x80)       //!< Lock command: Ignore summary.
#define LOCK_ZONE_MASK                  (0x81)                 //!< Lock parameter 1 bits 2 to 6 are 0.

//////////////////////////////////////////////////////////////////////
// Mac command definitions
#define MAC_MODE_IDX                    SHA204_PARAM1_IDX      //!< MAC command index for mode
#define MAC_KEYID_IDX                   SHA204_PARAM2_IDX      //!< MAC command index for key id
#define MAC_CHALLENGE_IDX               SHA204_DATA_IDX        //!< MAC command index for optional challenge
#define MAC_COUNT_SHORT                 SHA204_CMD_SIZE_MIN    //!< MAC command packet size without challenge
#define MAC_COUNT_LONG                  (39)                   //!< MAC command packet size with challenge
#define MAC_MODE_BLOCK2_TEMPKEY         ((uint8_t) 0x01)       //!< MAC mode bit   0: second SHA block from TempKey
#define MAC_MODE_BLOCK1_TEMPKEY         ((uint8_t) 0x02)       //!< MAC mode bit   1: first SHA block from TempKey
#define MAC_MODE_SOURCE_FLAG_MATCH      ((uint8_t) 0x04)       //!< MAC mode bit   2: match TempKey.SourceFlag
#define MAC_MODE_PASSTHROUGH            ((uint8_t) 0x07)       //!< MAC mode bit 0-2: pass-through mode
#define MAC_MODE_INCLUDE_OTP_88         ((uint8_t) 0x10)       //!< MAC mode bit   4: include first 88 OTP bits
#define MAC_MODE_INCLUDE_OTP_64         ((uint8_t) 0x20)       //!< MAC mode bit   5: include first 64 OTP bits
#define MAC_MODE_INCLUDE_SN             ((uint8_t) 0x50)       //!< MAC mode bit   6: include serial number
#define MAC_CHALLENGE_SIZE              (32)                   //!< MAC size of challenge
#define MAC_MODE_MASK                   ((uint8_t) 0x77)       //!< MAC mode bits 3 and 7 are 0.


//////////////////////////////////////////////////////////////////////
// Nonce command definitions
#define NONCE_MODE_IDX                  SHA204_PARAM1_IDX      //!< Nonce command index for mode
#define NONCE_PARAM2_IDX                SHA204_PARAM2_IDX      //!< Nonce command index for 2. parameter
#define NONCE_INPUT_IDX                 SHA204_DATA_IDX        //!< Nonce command index for input data
#define NONCE_COUNT_SHORT               (27)                   //!< Nonce command packet size for 20 bytes of data
#define NONCE_COUNT_LONG                (39)                   //!< Nonce command packet size for 32 bytes of data
#define NONCE_MODE_MASK                 ((uint8_t) 3)          //!< Nonce mode bits 2 to 7 are 0.
#define NONCE_MODE_SEED_UPDATE          ((uint8_t) 0x00)       //!< Nonce mode: update seed
#define NONCE_MODE_NO_SEED_UPDATE       ((uint8_t) 0x01)       //!< Nonce mode: do not update seed
#define NONCE_MODE_INVALID              ((uint8_t) 0x02)       //!< Nonce mode 2 is invalid.
#define NONCE_MODE_PASSTHROUGH          ((uint8_t) 0x03)       //!< Nonce mode: pass-through
#define NONCE_NUMIN_SIZE                (20)                   //!< Nonce data length
#define NONCE_NUMIN_SIZE_PASSTHROUGH    (32)                   //!< Nonce data length in pass-through mode (mode = 3)

//////////////////////////////////////////////////////////////////////
// Pause command definitions
#define PAUSE_SELECT_IDX                SHA204_PARAM1_IDX      //!< Pause command index for Selector
#define PAUSE_PARAM2_IDX                SHA204_PARAM2_IDX      //!< Pause command index for 2. parameter
#define PAUSE_COUNT                     SHA204_CMD_SIZE_MIN    //!< Pause command packet size

//////////////////////////////////////////////////////////////////////
// Random command definitions
#define RANDOM_MODE_IDX                 SHA204_PARAM1_IDX      //!< Random command index for mode
#define RANDOM_PARAM2_IDX               SHA204_PARAM2_IDX      //!< Random command index for 2. parameter
#define RANDOM_COUNT                    SHA204_CMD_SIZE_MIN    //!< Random command packet size
#define RANDOM_SEED_UPDATE              ((uint8_t) 0x00)       //!< Random mode for automatic seed update
#define RANDOM_NO_SEED_UPDATE           ((uint8_t) 0x01)       //!< Random mode for no seed update

//////////////////////////////////////////////////////////////////////
// Read command definitions
#define READ_ZONE_IDX                   SHA204_PARAM1_IDX      //!< Read command index for zone
#define READ_ADDR_IDX                   SHA204_PARAM2_IDX      //!< Read command index for address
#define READ_COUNT                      SHA204_CMD_SIZE_MIN    //!< Read command packet size
#define READ_ZONE_MASK                  ((uint8_t) 0x83)       //!< Read zone bits 2 to 6 are 0.
#define READ_ZONE_MODE_32_BYTES         ((uint8_t) 0x80)       //!< Read mode: 32 bytes

//////////////////////////////////////////////////////////////////////
// UpdateExtra command definitions
#define UPDATE_MODE_IDX                  SHA204_PARAM1_IDX     //!< UpdateExtra command index for mode
#define UPDATE_VALUE_IDX                 SHA204_PARAM2_IDX     //!< UpdateExtra command index for new value
#define UPDATE_COUNT                     SHA204_CMD_SIZE_MIN   //!< UpdateExtra command packet size
#define UPDATE_CONFIG_BYTE_86            ((uint8_t) 0x01)      //!< UpdateExtra mode: update Config byte 86

//////////////////////////////////////////////////////////////////////
// Write command definitions
#define WRITE_ZONE_IDX                  SHA204_PARAM1_IDX      //!< Write command index for zone
#define WRITE_ADDR_IDX                  SHA204_PARAM2_IDX      //!< Write command index for address
#define WRITE_VALUE_IDX                 SHA204_DATA_IDX        //!< Write command index for data
#define WRITE_MAC_VS_IDX                ( 9)                   //!< Write command index for MAC following short data
#define WRITE_MAC_VL_IDX                (37)                   //!< Write command index for MAC following long data
#define WRITE_COUNT_SHORT               (11)                   //!< Write command packet size with short data and no MAC
#define WRITE_COUNT_LONG                (39)                   //!< Write command packet size with long data and no MAC
#define WRITE_COUNT_SHORT_MAC           (43)                   //!< Write command packet size with short data and MAC
#define WRITE_COUNT_LONG_MAC            (71)                   //!< Write command packet size with long data and MAC
#define WRITE_MAC_SIZE                  (32)                   //!< Write MAC size
#define WRITE_ZONE_MASK                 ((uint8_t) 0xC1)       //!< Write zone bits 2 to 5 are 0.
#define WRITE_ZONE_WITH_MAC             ((uint8_t) 0x40)       //!< Write zone bit 6: write encrypted with MAC

//////////////////////////////////////////////////////////////////////
// Response size definitions
#define CHECKMAC_RSP_SIZE               SHA204_RSP_SIZE_MIN    //!< response size of DeriveKey command
#define DERIVE_KEY_RSP_SIZE             SHA204_RSP_SIZE_MIN    //!< response size of DeriveKey command
#define DEVREV_RSP_SIZE                 SHA204_RSP_SIZE_VAL    //!< response size of DevRev command returns 4 bytes
#define GENDIG_RSP_SIZE                 SHA204_RSP_SIZE_MIN    //!< response size of GenDig command
#define HMAC_RSP_SIZE                   SHA204_RSP_SIZE_MAX    //!< response size of HMAC command
#define LOCK_RSP_SIZE                   SHA204_RSP_SIZE_MIN    //!< response size of Lock command
#define MAC_RSP_SIZE                    SHA204_RSP_SIZE_MAX    //!< response size of MAC command
#define NONCE_RSP_SIZE_SHORT            SHA204_RSP_SIZE_MIN    //!< response size of Nonce command with mode[0:1] = 3
#define NONCE_RSP_SIZE_LONG             SHA204_RSP_SIZE_MAX    //!< response size of Nonce command
#define PAUSE_RSP_SIZE                  SHA204_RSP_SIZE_MIN    //!< response size of Pause command
#define RANDOM_RSP_SIZE                 SHA204_RSP_SIZE_MAX    //!< response size of Random command
#define READ_4_RSP_SIZE                 SHA204_RSP_SIZE_VAL    //!< response size of Read command when reading 4 bytes
#define READ_32_RSP_SIZE                SHA204_RSP_SIZE_MAX    //!< response size of Read command when reading 32 bytes
#define UPDATE_RSP_SIZE                 SHA204_RSP_SIZE_MIN    //!< response size of UpdateExtra command
#define WRITE_RSP_SIZE                  SHA204_RSP_SIZE_MIN    //!< response size of Write command

//////////////////////////////////////////////////////////////////////
// command timing definitions for typical execution times (ms)
//! CheckMAC typical command delay
#define CHECKMAC_DELAY                  (12)

//! DeriveKey typical command delay
#define DERIVE_KEY_DELAY                (14)

//! DevRev typical command delay
#define DEVREV_DELAY                    ( 1)  // 0.4 rounded up

//! GenDig typical command delay
#define GENDIG_DELAY                    (11)

//! HMAC typical command delay
#define HMAC_DELAY                      (27)

//! Lock typical command delay
#define LOCK_DELAY                      ( 5)

//! MAC typical command delay
#define MAC_DELAY                       (12)

//! Nonce typical command delay
#define NONCE_DELAY                     (22)

//! Pause typical command delay
#define PAUSE_DELAY                     ( 1)  // 0.4 rounded up

//! Random typical command delay
#define RANDOM_DELAY                    (11)

//! Read typical command delay
#define READ_DELAY                      ( 1)  // 0.4 rounded up

//! UpdateExtra typical command delay
#define UPDATE_DELAY                    ( 8)

//! Write typical command delay
#define WRITE_DELAY                     ( 4)

//////////////////////////////////////////////////////////////////////
// command timing definitions for maximum execution times (ms)
//! CheckMAC maximum execution time
#define CHECKMAC_EXEC_MAX                (38)

//! DeriveKey maximum execution time
#define DERIVE_KEY_EXEC_MAX              (62)

//! DevRev maximum execution time
#define DEVREV_EXEC_MAX                  ( 2)

//! GenDig maximum execution time
#define GENDIG_EXEC_MAX                  (43)

//! HMAC maximum execution time
#define HMAC_EXEC_MAX                    (69)

//! Lock maximum execution time
#define LOCK_EXEC_MAX                    (24)

//! MAC maximum execution time
#define MAC_EXEC_MAX                     (35)

//! Nonce maximum execution time
#define NONCE_EXEC_MAX                   (60)

//! Pause maximum execution time
#define PAUSE_EXEC_MAX                   ( 2)

//! Random maximum execution time
#define RANDOM_EXEC_MAX                  (50)

//! Read maximum execution time
#define READ_EXEC_MAX                    ( 4)

//! UpdateExtra maximum execution time
#define UPDATE_EXEC_MAX                  (12)

//! Write maximum execution time
#define WRITE_EXEC_MAX                   (42)

//////////////////////////////////////////////////////////////////////

/** 
 * \brief This structure contains the parameters for the \ref sha204m_check_mac function.
 */
struct sha204_check_mac_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t mode;              //!< what to include in the MAC calculation
   uint8_t key_id;            //!< what key to use for the MAC calculation
   uint8_t *client_challenge; //!< pointer to challenge that host had sent to client
   uint8_t *client_response;  //!< pointer to challenge response received from client 
   uint8_t *other_data;       //!< pointer to 13 bytes of data that were used by client to calculate MAC
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_derive_key function.
 */
struct sha204_derive_key_parameters {
   uint8_t *tx_buffer;   	//!< pointer to send buffer
   uint8_t *rx_buffer;   	//!< pointer to receive buffer
   uint8_t use_random;   	//!< true if source for TempKey was random number
   uint8_t target_key;   	//!< slot where derived key should be stored
   uint8_t *mac;	     	   //!< pointer to MAC for this command
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_dev_rev function.
 */
struct sha204_dev_rev_parameters {
   uint8_t *tx_buffer;   	//!< pointer to send buffer
   uint8_t *rx_buffer;		//!< pointer to receive buffer
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_gen_dig function.
 */
struct sha204_gen_dig_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t zone;              //!< what zone (config, OTP, or data) to use in the digest calculation
   uint8_t key_id;            //!< what key or OTP block to use for the digest calculation
   uint8_t *other_data;       //!< pointer to four bytes of data to use for the digest calculation, only needed when key is CheckMac only key 
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_hmac function.
 */
struct sha204_hmac_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t mode;              //!< what to include in the HMAC calculation
   uint16_t key_id;           //!< what key to use for the HMAC calculation
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_lock function.
 */
struct sha204_lock_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t zone;              //!< what zone (config, OTP, or data) to lock
   uint16_t summary;          //!< CRC over the zone to be locked
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_mac function.
 */
struct sha204_mac_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t mode;              //!< what to include in the MAC calculation
   uint16_t key_id;           //!< what key to use for the MAC calculation
   uint8_t *challenge;        //!< pointer to 32 bytes of challenge data to be sent to client
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_nonce function.
 */
struct sha204_nonce_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t mode;              //!< what TempKey should be loaded with
   uint8_t *num_in;           //!< pointer to 20 bytes of input or 32 bytes of pass-through data
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_pause function.
 */
struct sha204_pause_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t selector;          //!< which device not to set into Idle mode (single-wire interface only)
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_random function.
 */
struct sha204_random_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t mode;              //!< true if existing EEPROM seed should be used
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_read function.
 */
struct sha204_read_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t zone;              //!< what zone (config, OTP, or data) to read from and how many bytes (4 or 32)
   uint16_t address;          //!< what address to read from
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_update_extra function.
 */
struct sha204_update_extra_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t mode;              //!< config byte address = 84 + mode (0 or 1)
   uint8_t new_value;         //!< value to write
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_write function.
 */
struct sha204_write_parameters {
   uint8_t *tx_buffer;        //!< pointer to send buffer
   uint8_t *rx_buffer;        //!< pointer to receive buffer
   uint8_t zone;              //!< what zone (config, OTP, or data) to write to, how many bytes (4 or 32), and whether data are encrypted
   uint16_t address;          //!< what address to write to
   uint8_t *new_value;        //!< pointer to 4 or 32 bytes of data to be written
   uint8_t *mac;              //!< pointer to MAC of this command (null if zone is unlocked) 
};

/** 
 * \brief This structure contains the parameters for the \ref sha204m_execute function.
 */
struct sha204_command_parameters {
	uint8_t op_code;      //!< command code
	uint8_t param_1;      //!< parameter 1
	uint16_t param_2;     //!< parameter 2
	uint8_t data_len_1;   //!< length of data field 1
	uint8_t data_len_2;   //!< length of data field 2
	uint8_t data_len_3;   //!< length of data field 3
	uint8_t *data_1;      //!< pointer to data field 1
	uint8_t *data_2;      //!< pointer to data field 2
	uint8_t *data_3;      //!< pointer to data field 3
	uint8_t *tx_buffer;   //!< pointer to send buffer
	uint8_t *rx_buffer;   //!< pointer to receive buffer
	uint8_t tx_size;      //!< size of supplied send buffer
	uint8_t rx_size;      //!< size of supplied receive buffer
};
	
/**
 * \defgroup sha204_command_marshaling_group SHA204 Service - command marshaling functions
 *
 * @{
 */
uint8_t sha204m_check_mac(struct sha204_check_mac_parameters *args);
uint8_t sha204m_derive_key(struct sha204_derive_key_parameters *args);
uint8_t sha204m_dev_rev(struct sha204_dev_rev_parameters *args);
uint8_t sha204m_gen_dig(struct sha204_gen_dig_parameters *args);
uint8_t sha204m_hmac(struct sha204_hmac_parameters *args);
uint8_t sha204m_lock(struct sha204_lock_parameters *args);
uint8_t sha204m_mac(struct sha204_mac_parameters *args);
uint8_t sha204m_nonce(struct sha204_nonce_parameters *args);
uint8_t sha204m_pause(struct sha204_pause_parameters *args);
uint8_t sha204m_random(struct sha204_random_parameters *args);
uint8_t sha204m_read(struct sha204_read_parameters *args);
uint8_t sha204m_update_extra(struct sha204_update_extra_parameters *args);
uint8_t sha204m_write(struct sha204_write_parameters *args);
uint8_t sha204m_execute(struct sha204_command_parameters *args);
//! @}

#endif
