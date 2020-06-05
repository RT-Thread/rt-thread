/*******************************************************************************
 * (c) Copyright 2012-2016 Microsemi SoC Products Group.  All rights reserved.
 *
 * SmartFusion2 MSS System Services bare metal software driver public API.
 *
 * SVN $Revision: 8680 $
 * SVN $Date: 2016-11-25 14:18:13 +0530 (Fri, 25 Nov 2016) $
 */

/*=========================================================================*//**
  @mainpage SmartFusion2 MSS System Services Bare Metal Driver.

  @section intro_sec Introduction
  The SmartFusion2 microcontroller subsystem (MSS) includes a communication
  block (COMM_BLK) allowing it to communicate with the SmartFusion2 System
  Controller. The SmartFusion2 System Controller performs a variety of system
  wide services. This software driver provides a set of functions to access
  these System Services. The driver can be adapted for use as part of an
  operating system, but the implementation of the adaptation layer between the
  driver and the operating system's driver model is outside the scope of the
  driver.
  
  @section hw_dependencies Hardware Flow Dependencies
  The MSS System Services driver does not require any configuration. It relies
  on the SmartFusion2 communication block (MSS_COMM_BLK) to communicate with the
  System Controller. The MSS_COMM_BLK is always enabled.
  The base address, register addresses and interrupt number assignment for the
  MSS_COMM_BLK are defined as constants in the SmartFusion2 CMSIS HAL. You must
  ensure that the latest SmartFusion2 CMSIS HAL is included in the project
  settings of the software tool chain used to build your project and that it is
  generated into your project.
  
  @section theory_op Theory of Operation
  The System Services driver provides access to the SmartFusion2 System
  Controller services. These system services are loosely grouped into the
  following features:
    - Reading system information
    - Cryptography
    - Non-deterministic random bit generator
    - Flash*Freeze
    - Zeroization
    - Asynchronous Messages
    - Programming Services
    - Digest Check Service
  Note: Refer to the function descriptions for further details about the
        features of each individual service.

  Reading System Information
  The System Services driver can be used to read information about the
  SmartFusion2 device and the design programmed into it using the following
  functions:
    - MSS_SYS_get_serial_number()
    - MSS_SYS_get_user_code()
    - MSS_SYS_get_design_version()
    - MSS_SYS_get_device_certificate()
    - MSS_SYS_get_secondary_device_certificate()

  Cryptography Services
  The System Services driver provides cryptographic services using the following
  functions:
    - MSS_SYS_128bit_aes()
    - MSS_SYS_256bit_aes()
    - MSS_SYS_sha256()
    - MSS_SYS_hmac()
    - MSS_SYS_challenge_response()
    - MSS_SYS_key_tree()

  Non-Deterministic Random Bit Generator
  The System Services driver provides random number generation services using
  the following functions:
    - MSS_SYS_nrbg_instantiate()
    - MSS_SYS_nrbg_self_test()
    - MSS_SYS_nrbg_generate()
    - MSS_SYS_nrbg_reseed()
    - MSS_SYS_nrbg_uninstantiate()
    - MSS_SYS_nrbg_reset()
    
  Flash*Freeze
  The System Services driver can be used to request the system to enter
  Flash*Freeze mode using the following function:
    - MSS_SYS_flash_freeze()
  The System Controller sends an asynchronous message to the MSS COMM_BLK when
  the device is either about to enter or has exited Flash*Freeze mode. The
  MSS_SYS_init() function can register a callback function with the System
  Services driver to handle these asynchronous messages.

  Zeroization
  The System Service driver can be used to destroy sensitive information on the
  SmartFusion2 device using the following function.
    - MSS_SYS_zeroize_device()
  The zeroization system service erases all user configuration data, user keys,
  user security settings, NVM, SRAM, FPGA flip-flops, System Controller memory,
  and crypto-engine registers. The zeroization system service is enabled and
  configured in the Libero hardware flow.
  Note: The zeroization system service can render the SmartFusion2 device 
        permanently and irrevocably disabled depending on the configuration
        selected in the Libero hardware flow.
  
  Asynchronous Messages
  The System Controller sends asynchronous messages to the MSS COMM_BLK when
  certain events are detected during the execution of the following system 
  services:
    •Flash*Freeze
    •Power-on-reset (POR) digest check
    •Tamper detect events
  The MSS_SYS_init() function can register a callback function with the System
  Services driver to handle these asynchronous messages allowing the user
  application code to take remedial or defensive action. If the application
  code does not provide an asynchronous event handler function then the driver
  simply reads and discards these asynchronous messages.
    Flash*Freeze Entry and Exit
  The System Controller sends a Flash*Freeze entry or exit message to the MSS
  COMM_BLK when the SmartFusion2 device is either about to enter or has exited
  Flash*Freeze mode. The driver passes the entry/exit message opcode as a 
  parameter to the event handler callback function.
    Power-on Reset (POR) Digest Error
  The POR digest check service is enabled in the Libero hardware flow and if 
  enabled is automatically performed as part of the device’s power up sequence.
  The System Controller sends a POR digest check error message to the MSS 
  COMM_BLK when the result of the POR digest check is a mismatch between the
  original stored digest and the current digest. The driver passes the command
  byte and the error flags byte from the error message as parameters to the
  event handler callback function.
    Tamper detect events
  The System Controller sends tamper message to the MSS COMM_BLK when the 
  tamper event is detected. This tamper message is of one byte contain only
  command opcode. The driver pass the tamper message opcode as a parameter 
  to the event handler callback function.
  
  Programming Service
  The In-System Programming (ISP) system service can be used for field upgrades
  of the hardware design programmed in the FPGA fabric. The application program
  running on the Cortex-M3 controls the ISP operations, it must retrieve the
  programming file from memory or from a communication port and feed it to 
  the System Controller through the ISP system service. The System Controller
  performs the actual programming of the FPGA (fabric and eNVM) using the
  programming data it receives from the Cortex-M3 as part of the ISP system
  service.
  Programming files are large and cannot always be entirely retrieved by the
  application before starting the ISP operation. The ISP system service is
  designed to work around this issue by handling programming one page at a
  time. The application initiates the ISP operation through a call to
  MSS_SYS_start_isp(), passing two function pointers as parameters. These two
  function pointers point to a page read handler function and an ISP completion
  handler function that must be implemented as part of the application. The
  system services driver will call the application’s page read handler
  function every time it is ready to program the FPGA with a new page of
  programming data. The page read handler function is responsible for splitting
  the programming file into suitably sized pages. The page size is not fixed
  and can be chosen to suit the application. The system services driver will
  call the ISP completion handler function once the last page has been
  programmed.
  The application must keep track of the pages of programming data is has 
  passed to the ISP system service. It must provide the location of the next 
  programming page by writing the address of the page into the location
  pointed to by the pp_next_page pointer passed as parameter to the page read
  handler function. The page read handler must return the size of the page or
  zero if the last page has already been given to the ISP system service.
    
  The In-Application Programming (IAP) system service provides another field
  upgrade method of the hardware design programmed in FPGA fabric. Using this
  method, the user application first writes the FPGA fabric design into the SPI
  Flash connected to MSS SPI-0 before invoking the IAP system service. The FPGA
  fabric is then programmed under control of the SmartFusion2 system controller
  without intervention of the Cortex-M3 processor. The application must
  configure the SPI peripheral and provide exclusive access to the IAP service
  before invoking the IAP system service.
  When the IAP service is invoked, the system controller will send the SPI 
  command 0Bh i.e. single read operation command to the SPI flash to retrieve 
  the FPGA fabric design. The system controller will perform one of the 
  following operations based on the mode selected when invoking the service:
    a) Authenticate the fabric design.
    b) Program the fabric design into FPGA.
    c) Verify that the programming was successful.
  The system controller will take 2 to 3 minutes to complete each operation.
  The application must provide the starting location address of the new FPGA
  fabric design present in SPI Flash when invoking the IAP service.
  The system controller will return a response indicating the status of the 
  operation on completing the execution of the IAP service except in the case
  of successful programming. The system controller will reset the device and
  start execution of the new FPGA fabric design after successfully programming
  the device. The system controller will not return any response information 
  when a successful programming operation completes.

  Digest Check Service
  The System Service driver can be used to recalculate and compare digests of
  selected components using the following function.
    - MSS_SYS_check_digest()
  Note: This function is not used for the power-on-reset (POR) digest check
        service. An asynchronous event handler registered with the
        MSS_SYS_init() function is used to support the POR digest check
        service.
   
  Elliptic Curve services
  The System Service driver can be used to perform elliptic curve cryptography
  (ECC) mathematical operations over the field defined by the NIST P-384
  curve. point addition and point multiplication using the following functions
   are provided:
    - MSS_SYS_ecc_point_multiplication()
    - MSS_SYS_ecc_point_addition()
    - MSS_SYS_ecc_get_base_point()
  One example use of these functions is the elliptic curve Diffie-Hellman
  (ECDH) key establishment protocol. In this protocol, a public key is computed
  by performing a point multiplication of a 384-bit private key with the base
  point for the NIST P-384 curve. Both parties involved in the key
  establishment compute their public keys and send them to each other. A shared
  secret is established by point multiplication of each party’s private key
  with the remote party’s public key. The elliptic curve mathematical
  properties ensure that the private key point multiplication with the remote
  party’s public key results in the same point on the curve for both parties.
  The coordinates of this point on the curve is used as the shared secret for
  further cryptographic operations.
  Note: There is no checking done to see if the given input point or points
  are valid points on the elliptic curve.  Supplying illegal X-Y coordinates 
  for a point will result in a garbage output.  However, if a valid point or 
  points are given, then the resulting output point is guaranteed to be valid.
  
  PUF Services
  The SRAM-PUF system services provide a Physically Unclonable Function (PUF) 
  that can be used for key generation and storage as well as device
  authentication.
  The large SmartFusion2 devices starting from the M2S060 include an SRAM-PUF 
  hardware block as part of the System Controller. This hardware block makes 
  use of a 16Kbit SRAM block to determine an intrinsic secret unique to each 
  device. This intrinsic secret is in turn used to regenerate keys enrolled
  with the SRAM-PUF hardware block. 
  The SRAM-PUF is also used in design security. Although the system services
  are not used for design security, it is possible to retrieve the design
  security ECC public key for device authentication purpose.
  The SRAM-PUF start-up value can also be used to generate a random number
  generator seed.
  Note: PUF service should be executed from DDR/SRAM/eNVM-0 except for the 
        M2S060 device. On the M2S060 device, PUF service should be executed
        from DDR/SRAM.
        
  Activation Code
  An activation code is required by the SRAM-PUF to regenerate the intrinsic
  secret from the SRAM-PUF start-up value. The start-up value of the PUF’s SRAM
  block is slightly different from one power-up to the next. Some processing is
  performed on the PUF’s SRAM start-up value to eliminate randomness and 
  retrieve the exact same intrinsic secret on each power-up cycle. This 
  processing is performed using the activation code, which can be thought of as
  parity bits that are used to reconstruct the same PUF intrinsic secret each 
  time, in spite of the fact that some SRAM bits are flipped compared to the 
  original snapshot used when the activation code was first enrolled.
  The devices are shipped with one activation code that was enrolled during 
  the manufacturing process. The PUF secret computed from this enrollment is
  used to protect a 376-bit ECC private key that may be used for design 
  security purposes as described elsewhere. The user may optionally enroll a
  second activation code in special “S” -suffix (i.e., security enabled) 
  devices. The activation code is usually generated only once, typically when
  the system containing the SmartFusion2 device is being commissioned, using a
  JTAG or SPI programming command. Alternatively, the activation code is 
  created using the following system service function:

    - MSS_SYS_puf_create_activation_code()
  This might be used if the first user activation code were intentionally
  deleted and a new one was desired. The activation code is stored the System
  Controller’s private eNVM after being created. Its value is never exported in
  clear text from the System Controller. Because of the inherent noise in each 
  SRAM start-up, there is a negligible probability two activation codes or the 
  associated PUF intrinsic secret are ever the same, even if the same device is
  repeatedly re-enrolled.
  The activation code can later be destroyed using the following function:
    - MSS_SYS_puf_delete_activation_code()
  This function would typically only be used when the system containing 
  SmartFusion2 is being decommissioned or repurposed.
  
  Enrolling Keys
  The SRAM-PUF can be used to store cryptographic keys. The keys are stored in 
  such a way that the key’s actual value never appears in the system unless it
  is retrieved by the user. A so-called "Key Code" is stored in the System 
  Controller’s private eNVM instead of the key’s value. The key code is 
  generated when a key is enrolled. The key code value is created from the 
  enrolled key’s value and the intrinsic secret value. The key’s value can then
  later be regenerated from the key code value and intrinsic secret value upon 
  user request.
  NOTE:Note: Key #0 and key #1 are used for design security and are not 
             accessible to the user. Key Code #2 may be used to store a user 
             data security key, but has an important optional use in JTAG- or
             SPI-based key validation, as will be described below.
  
  The enrolled keys can be intrinsic keys or extrinsic keys. The value of an 
  intrinsic key is a random number generated from the SRAM-PUF start-up value.
  Intrinsic keys are useful where a security protocol executing on SmartFusion2
  needs to generate a key’s value and store it for later use. For example, the
  user could request a 384-bit long intrinsic key to be enrolled and use it as
  private key in an elliptic curve Diffie-Hellman key exchange.
  The value of an extrinsic key is specified by the user. For example, the user
  could request a symmetric key obtained from a key exchange protocol to be
  enrolled for later use.
  The following functions are used for key enrollment:
    - MSS_SYS_puf_get_number_of_keys()
    - MSS_SYS_puf_enroll_key()
    - MSS_SYS_puf_fetch_key()
    - MSS_SYS_puf_delete_key()
  
  Keys are identified by a number and must be enrolled sequentially. Key codes 
  #0 and #1 are reserved as a 256-bit symmetric extrinsic key and a 384-bit 
  private (asymmetric) intrinsic key, both used for design security only, and 
  are enrolled by JTAG (or SPI) programming commands. These commands also 
  enroll the user activation code and key code #2, a 256-bit value that has a 
  special use in key validation, and which is enrolled at the same time as key 
  code #1, as will be described below.
  The first step in enrolling a new key is to determine how many keys are 
  already enrolled. This is achieved by a call to function 
  MSS_SYS_puf_get_number_of_keys() which returns the number of enrolled keys.
  Keys are numbered from 0 up to 57 (the maximum number of keys assuming all 
  user keys are less than or equal to 256 bits in length). For example, 
  assuming only the first three key codes mentioned above have been enrolled 
  using the JTAG programming commands, the value returned would be ‘3’. The 
  number of keys returned by MSS_SYS_puf_get_number_of_keys() can then be used
  as the newly enrolled key identification number since key numbering is zero 
  based. Thus, the first data security key enrolled by the user would generate
  key code #3.
  
  A key is enrolled through a call to function MSS_SYS_puf_enroll_key(). This
  function takes the following parameters:
    • The key identification number that will be used to later retrieve the
      key’s value. This is the value returned by a call to
      MSS_SYS_puf_get_number_of_keys().
    • The key size.
    • A pointer to the buffer containing the value of the key to enroll. The
      value of this pointer must be NULL if enrolling an intrinsic key where
      the SRAM-PUF will generate the actual key value.
    • A pointer to the buffer where the enrolled key will be regenerated when
      later fetched by the user.

  The value of the enrolled keys can be regenerated through a call to function
  MSS_SYS_puf_fetch_key(). The identification number of the key to fetch is
  passed as parameter to this function. The requested key’s value will be
  regenerated and copied to the buffer specified during key enrollment. The
  key’s value is then available for use until it is no further required and
  wiped, by the user’s application, from the memory buffer it was fetched into.
  
  Note: It is not possible to fetch a key if the key codes have been exported
        and not re-imported.
  
  A key can be removed from the system through a call to function
  MSS_SYS_puf_delete_key(). This function only requires the key identification
  number to specify which key should be removed from the SRAM-PUF.
  
  Note: If a new key is enrolled in a key-slot where a key was previously 
        enrolled and deleted and which is not the highest key number enrolled,
        it must be the same size as the key it replaced or an error will be 
        reported.
        
  Exporting and Importing Key Codes
  The activation code and key codes used to regenerate the enrolled keys can be
  exported out of the SRAM-PUF. The exported activation code and key codes are
  encrypted using a one-time pad. The one-time pad is stored in the System
  Controller’s private eNVM and is never exported. This means that the exported
  activation and key codes can only be decrypted by the unique device that
  exported them.
  The activation and key code values stored in eNVM are replaced with hash
  values of themselves as part of the export procedure. This means that 
  enrolled keys cannot be regenerated anymore after the activation and key 
  codes have been exported. The enrolled keys will only be regenerated
  successfully if the exported activation and key codes for that unique
  SmartFusion2 device are imported back.
  
  The activation and all the key codes are exported in one single operation
  using the following function:
    - MSS_SYS_puf_export_keycodes()
  The MSS_SYS_puf_export_keycodes() function can only be called once since the
  activation and key codes are not present anymore in the device after this
  function completes. The activation and key codes must be imported back
  before they can be exported again.
  The activation and all the key codes are imported back in one single 
  operation using the following function:
    - MSS_SYS_puf_import_keycodes()
  It is only possible to import activation and key codes exported from the
  same unique device. The imported activation and key codes are decrypted
  using the one-time pad stored in eNVM used during the export procedure.
  The decrypted activation and key codes are then checked again the hash
  values stored in place of the activation and key codes. The activation
  and key codes will only be successfully imported back if the hash values
  for the imported activation and key codes match the hash values stored in
  eNVM during the export procedure. Imported activation and key codes are 
  never again restored to non-volatile memory; rather, they are imported to
  volatile scratch-pad memory, used to regenerate a key, and then deleted. 
  Therefore, they must be re-imported each time a key is needed.
  
  Retrieving the Design Security ECC Public Key
  When the 384 bit user design security private ECC key is intrinsically
  generated and key code #1 is stored using the JTAG or SPI programming 
  commands, the associated 768 bit public key is also generated and stored 
  in the system controller’s private eNVM. At the same time, the256 bit SHA-256
  hash of the ECC public key is enrolled to key code #2.
  The 768 bit design security ECC public key can be retrieved using the following
  system service function:
    - MSS_SYS_puf_fetch_ecc_public_key()
   Note that the public key is also exported via JTAG (or SPI) programming 
   commands when it is used in ECDH design security operations such as 
   bitstream encryption or device authentication.
   
  In order to mitigate man-in-the-middle attacks on the public key when it is 
  exported and used, it is recommended that the ECC public key is validated 
  using an already trusted key. This could be a user design security key, for 
  example. Perhaps the most convenient keys to use are one of the Microsemi 
  certified ECC key pairs, which are trusted because of the verifiable 
  Microsemi signatures on the X.509 public key certificates. This is why when
  the 384 bit user ECC private key was generated and stored using key code #1,
  the 256 bit hash of the associated 768 bit public key was stored using key 
  code #2. The JTAG (or SPI) key verification protocol has a special option 
  which includes the value stored in key code #2 in the computation. Thus, 
  besides also validating the device really “knows” the already trusted key,
  with this option selected, the 256-bit value stored using key code #2 is also
  validated. If this is the hash of the user ECC public key, then it is proved 
  that the public key is the authentic public key as stored in the device, and 
  not one supplied by an adversary in a man-in-the-middle attack on this key. 
  After the user ECC public key has been thus validated, key code #2 can be 
  deleted and replaced with another 256-bit value the user wishes to validate,
  such as the hash of user data security key. It is recommended that key code 
  #2 only be used to store hashes of critical security parameters such as 
  secret or private keys, and not the actual secrets, themselves.
  Note: The user's application need to reserve a defined block of SRAM when 
        using PUF system services, to prevent the compiler from using the SRAM
        memory range from address 0x2000800 to 0x2000802F inclusive. This is 
        the default location used by the system controller to automatically 
        enroll KC#2, when KC#1 is enrolled.
  
  Random Number Generator Seed
  The PUF’s SRAM start-up value randomness can be harvested to generate a 
  256-bit full entropy true random seed. A random seed can be obtained using
  function:
    - MSS_SYS_puf_get_random_seed()
  Note: Random seeds can only be generated after the SRAM-PUF has been powered
        -down for 250 msec. Thus, if the PUF has been used more recently than 
        that, there may be a delay before the seed is generated.

  Tamper control service
  The tamper control system services provide the following services:
    - Enable/disable clock monitoring
    - Control power to PUF
    - Clear mesh short tamper
    -  Clear lock parity tamper
    
  The tamper control services are accessed using the following functions:
    - MSS_SYS_start_clock_monitor()
    - MSS_SYS_stop_clock_monitor()
    - MSS_SYS_enable_puf_power_down()
    - MSS_SYS_disable_puf_power_down()
    - MSS_SYS_clear_lock_parity()
    - MSS_SYS_clear_mesh_short()
    
 *//*=========================================================================*/

#ifndef __MSS_SYS_SERVICES_H_
#define __MSS_SYS_SERVICES_H_ 1

#include "../../CMSIS/m2sxxx.h"
#include "mss_comblk_page_handler.h"

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
 * Status codes:
 */
/*-------------------------------------------------------------------------*//**
  These constants are used by multiple services to communicate the outcome of a
  system services request. These status codes are used across all types of
  services.
  
  - MSS_SYS_SUCCESS:
      Indicates that the system services completed successfully. 
      
  - MSS_SYS_UNEXPECTED_ERROR:
      Indicates that the system failed in an unexpected way.
      
  - MSS_SYS_MEM_ACCESS_ERROR:
      Indicates that the System Controller could not access the memory used to
      pass parameters to the System Controller or to return a service result to
      the Cortex-M3.
      
  - MSS_SYS_SERVICE_DISABLED_BY_FACTORY:
      Indicates that the requested system service is not available on the
      SmartFusion2 device.
      
  - MSS_SYS_SERVICE_DISABLED_BY_USER:
      Indicates that the requested system service has been disabled as part of
      the hardware design.
  
  - MSS_SYS_SERVICE_NOT_LICENSED
      Indicates that the license is not available in SmartFusion2 device for 
      this service.
  
  - MSS_SYS_CLK_DIVISOR_ERROR
      Indicates that on 060 device the divisor values for fclk, pclk0, pclk1, 
      clk_fic64 are not equal to each other or the divisor values is set to 
      divide by 32.
 */
#define MSS_SYS_SUCCESS                         0u
#define MSS_SYS_UNEXPECTED_ERROR                200u
#define MSS_SYS_CLK_DIVISOR_ERROR               201u

#define MSS_SYS_MEM_ACCESS_ERROR                127u
#define MSS_SYS_SERVICE_NOT_LICENSED            253u
#define MSS_SYS_SERVICE_DISABLED_BY_FACTORY     254u
#define MSS_SYS_SERVICE_DISABLED_BY_USER        255u

/*-------------------------------------------------------------------------*//**
  These constants are used by PUF services to communicate the outcome of a 
  system services request. These status codes are only used by PUF services.
  
  - MSS_SYS_ENVM_ERROR:
      Indicates that a eNVM error occurred for both create and delete user
      activation code sub command.
      
  - MSS_SYS_PUF_ERROR_WHEN_CREATING:
      Indicates that PUF error occur while creating new user activation code.
      
  - MSS_SYS_INVALID_SUBCMD:
      Indicates that the sub command is invalid.
      
  - MSS_SYS_INVALID_REQUEST_OR_KC:
      Indicates that request or Key code is invalid, when exporting or
      importing.
      
  - MSS_SYS_INVALID_KEYNUM_OR_ARGUMENT
      Indicates that the supplied key number or argument is invalid.
      
  - MSS_SYS_NO_VALID_PUBLIC_KEY
      Indicates that no valid public key present in eNVM.
      
  - MSS_SYS_INVALID_MEMORY_ADDRESS:
      Indicates that memory address is invalid.
      
  - MSS_SYS_ENVM_PROGRAM_ERROR
      Indicates that the eNVM program error occur when writing to the private eNVM
      for both create and delete user activation code sub command.
      
  - MSS_SYS_INVALID_HASH:
      Indicates that 32 byte hash is invalid.
      
  - MSS_SYS_INVALID_USER_AC1:
      Indicates that invalid user activation code has been imported.
      
  - MSS_SYS_ENVM_VERIFY_ERROR:
      Indicates that the eNVM verify error occur when writing to the private eNVM
      for both create and delete user activation code sub command.
      
  - MSS_SYS_INCORRECT_KEYSIZE_FOR_RENEWING_A_KC:
      Indicates that the supplied key size is incorrect while renewing the key
      code.
      
  - MSS_SYS_PRIVATE_ENVM_USER_DIGEST_MISMATCH:
      Indicates that digest mismatch occurs for private eNVM.
      
  - MSS_SYS_USER_KEY_CODE_INVALID_SUBCMD:
      Indicate that the sub command is invalid.
      
  - MSS_SYS_DRBG_ERROR:
      Indicates that DRBG error occurred while populating one time pad reminder
      by random bits.
*/
#define MSS_SYS_ENVM_ERROR                              1u
#define MSS_SYS_PUF_ERROR_WHEN_CREATING                 2u
#define MSS_SYS_INVALID_SUBCMD                          3u
#define MSS_SYS_INVALID_REQUEST_OR_KC                   3u
#define MSS_SYS_INVALID_KEYNUM_OR_ARGUMENT              3u
#define MSS_SYS_NO_VALID_PUBLIC_KEY                     3u
#define MSS_SYS_INVALID_MEMORY_ADDRESS                  4u
#define MSS_SYS_ENVM_PROGRAM_ERROR                      4u
#define MSS_SYS_INVALID_HASH                            5u
#define MSS_SYS_INVALID_USER_AC1                        6u
#define MSS_SYS_ENVM_VERIFY_ERROR                       7u
#define MSS_SYS_INCORRECT_KEYSIZE_FOR_RENEWING_A_KC     8u
#define MSS_SYS_PRIVATE_ENVM_USER_DIGEST_MISMATCH       10u
#define MSS_SYS_USER_KEY_CODE_INVALID_SUBCMD            11u
#define MSS_SYS_DRBG_ERROR                              12u

/*-------------------------------------------------------------------------*//**
 * Programming services specific status codes:
 */
#define MSS_SYS_CHAINING_MISMATCH                   1u
#define MSS_SYS_UNEXPECTED_DATA_RECEIVED            2u
#define MSS_SYS_INVALID_ENCRYPTION_KEY              3u
#define MSS_SYS_INVALID_COMPONENT_HEADER            4u
#define MSS_SYS_BACK_LEVEL_NOT_SATISFIED            5u
#define MSS_SYS_DSN_BINDING_MISMATCH                7u
#define MSS_SYS_ILLEGAL_COMPONENT_SEQUENCE          8u
#define MSS_SYS_INSUFFICIENT_DEV_CAPABILITIES       9u
#define MSS_SYS_INCORRECT_DEVICE_ID                 10u
#define MSS_SYS_UNSUPPORTED_BITSTREAM_PROT_VER      11u
#define MSS_SYS_VERIFY_NOT_PERMITTED_ON_BITSTR      12u
#define MSS_SYS_INVALID_DEVICE_CERTIFICATE          13u
#define MSS_SYS_ABORT                               127u
#define MSS_SYS_NVM_VERIFY_FAILED                   129u
#define MSS_SYS_DEVICE_SECURITY_PROTECTED           130u
#define MSS_SYS_PROGRAMMING_MODE_NOT_ENABLED        131u
#define MSS_SYS_ENVM_PROGRAMMING_OPERATION_FAIL     132u
#define MSS_SYS_ENVM_VERIFY_OPERATION_FAIL          133u
#define MSS_SYS_ACCESS_ERROR                        134u
#define MSS_SYS_PUF_ACCESS_ERROR                    135u
#define MSS_SYS_BAD_COMPONENT                       136u

/*-------------------------------------------------------------------------*//**
  These constants are used to specify the event_opcode parameter for the
  event_handler() function registered with the MSS_SYS_init() function. They are
  used to specify which asynchronous event is notified to the Cortex-M3 software
  by the System Controller. Asynchronous events are sent by the System
  Controller to the Cortex-M3 when some system events of interest occur.
  
  - FLASH_FREEZE_SHUTDOWN_OPCODE:
      Indicates that the system is being shutdown as a result of entering the
      Flash*Freeze mode.
      
  - FLASH_FREEZE_EXIT_OPCODE:
      Indicates that the system is exiting Flash*Freeze mode.
  
  - POR_DIGEST_ERROR_OPCODE
      Indicates that the MSS has received the POR Digest Check message.

  - TAMPER_ATTEMPT_BOUNDARY_SCAN_OPCODE
      Indicates that the MSS has received the tamper boundary scan attempt 
      detected.
  
  - TAMPER_ATTEMPT_BUFFER_ACCESS_OPCODE
      Indicates that the MSS has received the tamper buffer access attempt 
      detected.

  - TAMPER_ATTEMPT_DEBUG_OPCODE
      Indicates that the MSS has received the tamper debug attempt detected.

  - TAMPER_ATTEMPT_CHECK_DIGESTS_OPCODE
      Indicates that the MSS has received the tamper check digest attempt 
      detected.

  - TAMPER_ATTEMPT_ECC_SETUP_INSTRUCTION_OPCODE
      Indicates that the MSS has received the tamper ECC setup instruction 
      attempt detected.

  - TAMPER_ATTEMPT_FACTORY_PRIVATE_OPCODE
      Indicates that the MSS has received the tamper factory private attempt 
      detected.

  - TAMPER_ATTEMPT_KEY_VALIDATION_OPCODE
      Indicates that the MSS has received the tamper key validation attempt 
      detected.
  
  - TAMPER_ATTEMPT_MISC_OPCODE
      Indicates that the MSS has received the tamper misc attempt detected.
  
  - TAMPER_ATTEMPT_PASSCODE_MATCH_OPCODE
      Indicates that the MSS has received the tamper passcode match attempt 
      detected.

  - TAMPER_ATTEMPT_PASSCODE_SETUP_INSTRUCTION_OPCODE
      Indicates that the MSS has received the tamper passcode setup instruction
      attempt detected.

  - TAMPER_ATTEMPT_PROGRAMMING_OPCODE
      Indicates that the MSS has received the tamper programming attempt detected.

  - TAMPER_ATTEMPT_PUBLIC_INFORMATION_OPCODE
      Indicates that the MSS has received the tamper public information attempt 
      detected.

  - TAMPER_ATTEMPT_PUF_KEY_MANAGEMENT_OPCODE
      Indicates that the MSS has received the tamper PUF key management attempt 
      detected.

  - TAMPER_ATTEMPT_UNUSED_OPCODE
      Indicates that the MSS has received the tamper unused attempt detected.

  - TAMPER_ATTEMPT_USER_JTAG_OPCODE
      Indicates that the MSS has received the tamper user JTAG attempt detected.

  - TAMPER_ATTEMPT_ZEROIZATION_RECOVERY_OPCODE
      Indicates that the MSS has received the tamper zeroization recovery 
      attempt detected.

  - TAMPER_FAILURE_BOUNDARY_SCAN_OPCODE
      Indicates that the MSS has received the tamper boundary scan failure 
      detected.

  - TAMPER_FAILURE_BUFFER_ACCESS_OPCODE
      Indicates that the MSS has received the tamper  buffer access 
      failure detected.

  - TAMPER_FAILURE_DEBUG_OPCODE
      Indicates that the MSS has received the tamper debug failure detected.

  - TAMPER_FAILURE_CHECK_DIGESTS_OPCODE
      Indicates that the MSS has received the tamper check digest failure
      detected.

  - TAMPER_FAILURE_ECC_SETUP_INSTRUCTION_OPCODE
      Indicates that the MSS has received the tamper ECC setup instruction 
      failure detected.

  - TAMPER_FAILURE_FACTORY_PRIVATE_OPCODE
      Indicates that the MSS has received the tamper factory private failure 
      detected.

  - TAMPER_FAILURE_KEY_VALIDATION_OPCODE
      Indicates that the MSS has received the tamper key validation failure
      detected.

  - TAMPER_FAILURE_MISC_OPCODE
      Indicates that the MSS has received the tamper misc failure detected.

  - TAMPER_FAILURE_PASSCODE_MATCH_OPCODE
      Indicates that the MSS has received the tamper passcode match failure
      detected.

  - TAMPER_FAILURE_PASSCODE_SETUP_INSTRUCTION_OPCODE
      Indicates that the MSS has received the tamper passcode setup instruction 
      failure detected.

  - TAMPER_FAILURE_PROGRAMMING_OPCODE
      Indicates that the MSS has received the tamper programming failure detected.

  - TAMPER_FAILURE_PUBLIC_INFORMATION_OPCODE
      Indicates that the MSS has received the tamper public information failure
      detected.

  - TAMPER_FAILURE_PUF_KEY_MANAGEMENT_OPCODE
      Indicates that the MSS has received the tamper PUF key management failure
      detected.

  - TAMPER_FAILURE_UNUSED_OPCODE
      Indicates that the MSS has received the tamper unused failure detected.

  - TAMPER_FAILURE_USER_JTAG_OPCODE
      Indicates that the MSS has received the tamper user jtag failure detected.

  - TAMPER_FAILURE_ZEROIZATION_RECOVERY_OPCODE
      Indicates that the MSS has received the tamper zeroization recovery 
      failure detected.

  - TAMPER_CLOCK_ERROR_DETECT_OPCODE0
      Indicates that the MSS has received the tamper clock monitor error detected.

  - TAMPER_HARDWARE_MONITOR_JTAGACTIVE_ERROR_OPCODE
      Indicates that the MSS has received the tamper jtag active hardware 
      monitor error detected.

  - TAMPER_HARDWARE_MONITOR_LOCKPARITY_ERROR_OPCODE
      Indicates that the MSS has received the tamper lock parity hardware 
      monitor error detected.

  - TAMPER_HARDWARE_MONITOR_MESHSHORT_ERROR_OPCODE
      Indicates that the MSS has received the tamper mesh short hardware monitor
      error detected.
*/
#define FLASH_FREEZE_SHUTDOWN_OPCODE                            0xE0u
#define FLASH_FREEZE_EXIT_OPCODE                                0xE1u
#define POR_DIGEST_ERROR_OPCODE                                 0xF1u
#define TAMPER_ATTEMPT_BOUNDARY_SCAN_OPCODE                     0x80u
#define TAMPER_ATTEMPT_BUFFER_ACCESS_OPCODE                     0x81u
#define TAMPER_ATTEMPT_DEBUG_OPCODE                             0x82u
#define TAMPER_ATTEMPT_CHECK_DIGESTS_OPCODE                     0x83u
#define TAMPER_ATTEMPT_ECC_SETUP_INSTRUCTION_OPCODE             0x84u
#define TAMPER_ATTEMPT_FACTORY_PRIVATE_OPCODE                   0x85u
#define TAMPER_ATTEMPT_KEY_VALIDATION_OPCODE                    0x86u
#define TAMPER_ATTEMPT_MISC_OPCODE                              0x87u
#define TAMPER_ATTEMPT_PASSCODE_MATCH_OPCODE                    0x88u
#define TAMPER_ATTEMPT_PASSCODE_SETUP_INSTRUCTION_OPCODE        0x89u
#define TAMPER_ATTEMPT_PROGRAMMING_OPCODE                       0x8Au
#define TAMPER_ATTEMPT_PUBLIC_INFORMATION_OPCODE                0x8Bu
#define TAMPER_ATTEMPT_PUF_KEY_MANAGEMENT_OPCODE                0x8Cu
#define TAMPER_ATTEMPT_UNUSED_OPCODE                            0x8Du
#define TAMPER_ATTEMPT_USER_JTAG_OPCODE                         0x8Eu
#define TAMPER_ATTEMPT_ZEROIZATION_RECOVERY_OPCODE              0x8Fu
#define TAMPER_FAILURE_BOUNDARY_SCAN_OPCODE                     0x90u
#define TAMPER_FAILURE_BUFFER_ACCESS_OPCODE                     0x91u
#define TAMPER_FAILURE_DEBUG_OPCODE                             0x92u
#define TAMPER_FAILURE_CHECK_DIGESTS_OPCODE                     0x93u
#define TAMPER_FAILURE_ECC_SETUP_INSTRUCTION_OPCODE             0x94u
#define TAMPER_FAILURE_FACTORY_PRIVATE_OPCODE                   0x95u
#define TAMPER_FAILURE_KEY_VALIDATION_OPCODE                    0x96u
#define TAMPER_FAILURE_MISC_OPCODE                              0x97u
#define TAMPER_FAILURE_PASSCODE_MATCH_OPCODE                    0x98u
#define TAMPER_FAILURE_PASSCODE_SETUP_INSTRUCTION_OPCODE        0x99u
#define TAMPER_FAILURE_PROGRAMMING_OPCODE                       0x9Au
#define TAMPER_FAILURE_PUBLIC_INFORMATION_OPCODE                0x9Bu
#define TAMPER_FAILURE_PUF_KEY_MANAGEMENT_OPCODE                0x9Cu
#define TAMPER_FAILURE_UNUSED_OPCODE                            0x9Du
#define TAMPER_FAILURE_USER_JTAG_OPCODE                         0x9Eu
#define TAMPER_FAILURE_ZEROIZATION_RECOVERY_OPCODE              0x9Fu
#define TAMPER_CLOCK_ERROR_DETECT_OPCODE                        0xA0u
#define TAMPER_HARDWARE_MONITOR_JTAGACTIVE_ERROR_OPCODE         0xB1u
#define TAMPER_HARDWARE_MONITOR_LOCKPARITY_ERROR_OPCODE         0xB2u
#define TAMPER_HARDWARE_MONITOR_MESHSHORT_ERROR_OPCODE          0xB4u  
  
/*-------------------------------------------------------------------------*//**
  These constants are used to specify the options parameter for the
  MSS_SYS_flash_freeze() function.
  
  - MSS_SYS_FPGA_POWER_DOWN:
      Indicates that the MSS_SYS_flash_freeze() function should request the FPGA
      fabric to enter Flash*Freeze mode.
      
  - MSS_SYS_MPLL_POWER_DOWN:
      Indicates that the MSS_SYS_flash_freeze() function should request the MSS
      PLL to enter Flash*Freeze mode.
 */
#define MSS_SYS_FPGA_POWER_DOWN     0x00u
#define MSS_SYS_MPLL_POWER_DOWN     0x04u

/*-------------------------------------------------------------------------*//**
  These constants are used to specify the mode parameter for the
  MSS_SYS_128aes() and MSS_SYS_256bit_aes() functions.
  
  - MSS_SYS_ECB_ENCRYPT:
      Indicates that the cryptography function should perform encryption using
      the Electronic Codebook (ECB) mode.
      
  - MSS_SYS_ECB_DECRYPT:
      Indicates that the cryptography function should perform decryption using
      the Electronic Codebook (ECB) mode.
      
  - MSS_SYS_CBC_ENCRYPT:
      Indicates that the cryptography function should perform encryption using
      the Cipher-Block Chaining (CBC) mode.
      
  - MSS_SYS_CBC_DECRYPT:
      Indicates that the cryptography function should perform decryption using
      the Cipher-Block Chaining (CBC) mode.
      
  - MSS_SYS_OFB_ENCRYPT:
      Indicates that the cryptography function should perform encryption using
      the Output Feedback (OFB) mode.
      
  - MSS_SYS_OFB_DECRYPT:
      Indicates that the cryptography function should perform decryption using
      the Output Feedback (OFB) mode.
      
  - MSS_SYS_CTR_ENCRYPT:
      Indicates that the cryptography function should perform encryption using
      the Counter (CTR) mode.
      
  - MSS_SYS_CTR_DECRYPT:
      Indicates that the cryptography function should perform decryption using
      the Counter (CTR) mode.
 */
#define MSS_SYS_ECB_ENCRYPT     0x00u
#define MSS_SYS_ECB_DECRYPT     0x80u
#define MSS_SYS_CBC_ENCRYPT     0x01u
#define MSS_SYS_CBC_DECRYPT     0x81u
#define MSS_SYS_OFB_ENCRYPT     0x02u
#define MSS_SYS_OFB_DECRYPT     0x82u
#define MSS_SYS_CTR_ENCRYPT     0x03u
#define MSS_SYS_CTR_DECRYPT     0x83u

/*------------------------------------------------------------------------------
  These constants are used by non deterministic random bit generator (NDRBG)
  services to communicate the outcome of a system services request. These status
  codes are only used by NDRBG services.
  
  - MSS_SYS_NRBG_CATASTROPHIC_ERROR:
      Indicates that a catastrophic error occurred. 
      
  - MSS_SYS_NRBG_MAX_INST_EXCEEDED:
      Indicates that the maximum number of NDRBG instances has been exceeded.
      You need to release already instantiated NDRBG instances using the
      MSS_SYS_ndrbg_uninstantiate() function.
      
  - MSS_SYS_NRBG_INVALID_HANDLE:
      Indicates that the handle parameter has an invalid value.
      
  - MSS_SYS_NRBG_GEN_REQ_TOO_BIG:
      Indicates that the requested random number is too long. The requested
      length is larger than the maximum number of digits that can be generated.
      
  - MSS_SYS_NRBG_MAX_LENGTH_EXCEEDED:
      Indicates that the supplied additional data length is exceeded.
 */
#define MSS_SYS_NRBG_CATASTROPHIC_ERROR     1u
#define MSS_SYS_NRBG_MAX_INST_EXCEEDED      2u
#define MSS_SYS_NRBG_INVALID_HANDLE         3u
#define MSS_SYS_NRBG_GEN_REQ_TOO_BIG        4u
#define MSS_SYS_NRBG_MAX_LENGTH_EXCEEDED    5u

/*-------------------------------------------------------------------------*//**
  The sys_serv_isp_complete_handler_t typedef specifies the function prototype
  of the in-system programming (ISP) completion handler that is passed as a
  parameter to the MSS_SYS_start_isp() function. The ISP completion handler
  function must be implemented by the application program and it is called by
  the System Services driver when an ISP operation initiated by a call to
  MSS_SYS_start_isp() completes. The ISP completion handler function receives
  a status parameter indicating the outcome of the ISP operation. Refer to the
  description of the MSS_SYS_start_isp() function for more details.
 */
typedef void (*sys_serv_isp_complete_handler_t)(uint32_t status);

/*-------------------------------------------------------------------------*//**
  The sys_serv_async_event_handler_t type specifies the function prototype of
  an asynchronous event handler that can be implemented by the application to
  handle asynchronous messages from the System Controller. The System
  Controller sends asynchronous messages to the MSS COMM_BLK when certain
  events such as Flash*Freeze shutdown, Flash*Freeze exit and power-on-reset
  (POR) digest check errors are detected during the execution of the following
  system services:
    - Flash*Freeze
    - Power-on-reset (POR) digest check
  The asynchronous event handler function is registered with the System
  Services driver through the MSS_SYS_init() function. The driver calls the
  asynchronous event handler when the MSS COMM_BLK receives an asynchronous message.
 */
typedef void (*sys_serv_async_event_handler_t)(uint8_t event_opcode, uint8_t response);
 
/*-------------------------------------------------------------------------*//**
  This constant is used as parameter to the MSS_SYS_init() function to indicate
  that the application code does not supply an asynchronous event handler
  function.
 */
#define MSS_SYS_NO_EVENT_HANDLER    ((sys_serv_async_event_handler_t)0)

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_init function initializes the system services communication with
  the System Controller.
   
  @param
    The event_handler parameter specifies an optional asynchronous event
    handler function. This event handler function is provided by the
    application. It will be called by the System Services driver whenever an
    asynchronous event is received from the SmartFusion2 System controller.
    This event handler is typically used to handle entry and exit of
    Flash*Freeze mode.
    
  @return
    This function does not return a value.
 */
void MSS_SYS_init
(
    sys_serv_async_event_handler_t event_handler
);

/*==============================================================================
 * Device and Design Information Services.
 */
 
/*-------------------------------------------------------------------------*//**
  The MSS_SYS_get_serial_number function fetches the 128-bit Device Serial
  Number (DSN).
  
  @param p_serial_number
    The p_serial_number parameter is a pointer to the 16-bytes buffer where the
    serial number will be written by this system service.
  
  @return
    The MSS_SYS_get_serial_number function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_UNEXPECTED_ERROR
 */
uint8_t MSS_SYS_get_serial_number
(
    uint8_t * p_serial_number
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_get_user_code functions fetches the 32-bit USERCODE.
  
  @param p_user_code
    The p_user_code parameter is a pointer to the 4-bytes buffer where the
    USERCODE will be written by this system service.
  
  @return
    The MSS_SYS_get_user_code function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_UNEXPECTED_ERROR
 */
uint8_t MSS_SYS_get_user_code
(
    uint8_t * p_user_code
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_get_design_version function fetches the design version.
  
  @param p_design_version
    The p_design_version parameter is a pointer to the 2-bytes buffer where the
    design version will be written by this system service.
  
  @return
    The MSS_SYS_get_design_version function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_UNEXPECTED_ERROR
 */
uint8_t MSS_SYS_get_design_version
(
    uint8_t * p_design_version
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_get_device_certificate function fetches the device certificate.
  
  @param p_device_certificate
    The p_device_certificate parameter is a pointer to the 512-bytes buffer
    where the device certificate will be written by this system service.
  
  @return
    The MSS_SYS_get_device_certificate function returns one of following status
    codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_UNEXPECTED_ERROR
 */
uint8_t MSS_SYS_get_device_certificate
(
    uint8_t * p_device_certificate
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_get_secondary_device_certificate function fetches the secondary 
  device certificate. The secondary device certificate is second ECC Key 
  Certificate which is a 640-byte digitally-signed X-509 certificate programmed 
  during manufacturing. This certificate only contains the public key for the 
  ECC key and is otherwise unused by the device.
  
  @param p_secondary_device_certificate
    The p_secondary_device_certificate parameter is a pointer to the 640-bytes 
    buffer where the secondary device certificate will be written by this system
    service.
  
  @return
    The MSS_SYS_get_secondary_device_certificate function returns one of 
    following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_UNEXPECTED_ERROR
 */
uint8_t MSS_SYS_get_secondary_device_certificate
(
    uint8_t * p_secondary_device_certificate
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_flash_freeze function requests the FPGA to enter the Flash*Freeze
  mode.
  
  @param options
    The options parameter can be used to power down additional parts of
    SmartFusion2 when the FPGA fabric enters Flash*Freeze mode. This parameter
    is a bit mask of the following options:
        - MSS_SYS_FPGA_POWER_DOWN
        - MSS_SYS_MPLL_POWER_DOWN
    MSS_SYS_FPGA_POWER_DOWN on its own will only power down the FPGA fabric.
    MSS_SYS_MPLL_POWER_DOWN specifies that the MSS PLL is powered down during
    the Flash*Freeze period.
    
  @return
    The MSS_SYS_flash_freeze function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
        - MSS_SYS_CLK_DIVISOR_ERROR
        
  The following example demonstrates how to request the FPGA fabric to enter 
  the Flash*Freeze mode:
  @code
    MSS_SYS_flash_freeze(MSS_SYS_FPGA_POWER_DOWN | MSS_SYS_MPLL_POWER_DOWN);
  @endcode
 */
uint8_t MSS_SYS_flash_freeze(uint8_t options);

/*==============================================================================
 * Cryptographic Services.
 */

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_128bit_aes function provides access to the SmartFusion2 AES-128
  cryptography service.
  
  @param key
    The key parameter is a pointer to a 16-bytes array containing the key to use
    for the requested encryption/decryption operation.
  
  @param iv
    The iv parameter is a pointer to a 16-bytes array containing the
    initialization vector that will be used as part of the requested 
    encryption/decryption operation. Its use is different depending on the mode.
        -----------------------------------------
        | Mode |             Usage              |
        -----------------------------------------
        | ECB  | Ignored.                       |
        -----------------------------------------
        | CBC  | Randomization.                 |
        -----------------------------------------
        | OFB  | Randomization.                 |
        -----------------------------------------
        | CTR  | Used as initial counter value. |
        -----------------------------------------
  
  @param nb_blocks
    The nb_blocks parameter specifies the number of 128-bit blocks of
    plaintext/ciphertext to be processed by the AES-128 system service.
  
  @param mode
    The mode parameter specifies the cipher mode of operation and whether the
    source text must be encrypted or decrypted. The modes of operation are:
        - Electronic Codebook (ECB)
        - Cipher-Block Chaining (CBC)
        - Output Feedback (OFB)
        - Counter (CTR)
    The CTR mode uses the content of the initialization vector as its initial
    counter value. The counter increment is 2^64.
    Allowed values for the mode parameter are:
        - MSS_SYS_ECB_ENCRYPT
        - MSS_SYS_ECB_DECRYPT
        - MSS_SYS_CBC_ENCRYPT
        - MSS_SYS_CBC_DECRYPT
        - MSS_SYS_OFB_ENCRYPT
        - MSS_SYS_OFB_DECRYPT
        - MSS_SYS_CTR_ENCRYPT
        - MSS_SYS_CTR_DECRYPT
    
  @param dest_addr
    The dest_addr parameter is a pointer to the memory buffer where the result
    of the encryption/decryption operation will be stored.
  
  @param src_addr
    The src_addr parameter is a pointer to the memory buffer containing the source
    plaintext/ciphertext to be encrypted/decrypted.
  
  @return
    The MSS_SYS_128bit_aes function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
 */
uint8_t MSS_SYS_128bit_aes
(
    const uint8_t * key,
    const uint8_t * iv,
    uint16_t nb_blocks,
    uint8_t mode,
    uint8_t * dest_addr,
    const uint8_t * src_addr
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_256bit_aes function provides access to the SmartFusion2 AES-256
  cryptography service.
  
  @param key
    The key parameter is a pointer to a 32-bytes array containing the key to use
    for the requested encryption/decryption operation.
  
  @param iv
    The iv parameter is a pointer to a 16-bytes array containing the
    initialization vector that will be used as part of the requested 
    encryption/decryption operation. Its use is different depending on the mode.
        -----------------------------------------
        | Mode |             Usage              |
        -----------------------------------------
        | ECB  | Ignored.                       |
        -----------------------------------------
        | CBC  | Randomization.                 |
        -----------------------------------------
        | OFB  | Randomization.                 |
        -----------------------------------------
        | CTR  | Used as initial counter value. |
        -----------------------------------------
  
  @param nb_blocks
    The nb_blocks parameter specifies the number of 128-bit blocks of
    plaintext/ciphertext requested to be processed by the AES-128 system service.
  
  @param mode
    The mode parameter specifies the cipher mode of operation and whether the
    source text must be encrypted or decrypted. The modes of operation are:
        - Electronic Codebook (ECB)
        - Cypher-Block Chaining (CBC)
        - Output Feedback (OFB)
        - Counter (CTR)
    The CTR mode uses the content of the initialization vector as its initial
    counter value. The counter increment is 2^64.
    Allowed values for the mode parameter are:
        - MSS_SYS_ECB_ENCRYPT
        - MSS_SYS_ECB_DECRYPT
        - MSS_SYS_CBC_ENCRYPT
        - MSS_SYS_CBC_DECRYPT
        - MSS_SYS_OFB_ENCRYPT
        - MSS_SYS_OFB_DECRYPT
        - MSS_SYS_CTR_ENCRYPT
        - MSS_SYS_CTR_DECRYPT
    
  @param dest_addr
    The dest_addr parameter is a pointer to the memory buffer where the result
    of the encryption/decryption operation will be stored.
  
  @param src_addr
    The src_addr parameter is a pointer to the memory buffer containing the source
    plaintext/ciphertext to be encrypted/decrypted.
  
  @return
    The MSS_SYS_256bit_aes function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
 */
uint8_t MSS_SYS_256bit_aes
( 
    const uint8_t * key,
    const uint8_t * iv,
    uint16_t nb_blocks,
    uint8_t mode,
    uint8_t * dest_addr,
    const uint8_t * src_addr
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_sha256 function provides access to the SmartFusion2 SHA-256
  cryptography service.
  
  @param p_data_in
    The p_data_in parameter is a pointer to the memory location containing the
    data that will be hashed using the SHA-256 system service.
  
  @param length
    The length parameter specifies the length in bits of the data to hash.
  
  @param result
    The result parameter is a pointer to a 32 bytes buffer where the hash result
    will be stored.
  
  @return
    The MSS_SYS_sha256 function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
 */
uint8_t MSS_SYS_sha256
(
    const uint8_t * p_data_in,
    uint32_t length,
    uint8_t * result
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_hmac function provides access to the SmartFusion2 HMAC
  cryptography service. The HMAC system service generates message authentication
  codes using the SHA-256 hash function.
  
  @param key
    The key parameter is a pointer to a 32 bytes array containing the key used
    to generate the message authentication code.
  
  @param p_data_in
    The p_data_in parameter is a pointer to the data to be authenticated.
  
  @param length
    The length parameter specifies the number of data bytes for which to generate
    the authentication code. It is the size of the data pointed to by the
    p_data_in parameter.
  
  @param p_result
    The p_result parameter is a pointer to a 32 bytes buffer where the
    authentication code generated by the HMAC system service will be stored.
  
  @return
    The MSS_SYS_hmac function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
 */
uint8_t MSS_SYS_hmac
(
    const uint8_t * key,
    const uint8_t * p_data_in,
    uint32_t length,
    uint8_t * p_result
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_key_tree() function provides access to a SHA-256 based key-tree 
  cryptography algorithm. The key-tree service begins with a user-supplied root
  key and derives an output key based on a 7-bit parameter which can be used to
  create uniqueness for different applications using the same root key, and a
  128-bit path variable. Both the 7-bit input parameter and the 128-bit path
  variable are assumed to be publicly known. One common use for the output key
  is as a keyed validator, similar to a message authentication code tag.

  @param p_key
    The p_key parameter is a pointer to a 32 bytes array containing root key
    used to generate derived key by Key Tree service and also used to store the
    derived key.
    
  @param op_type
    The op_type parameter specifies the operational parameter to be used to
    generate the output key.
    
  @param path
    The path parameter specifies the 128-bit path to be used to generate the
    output key.
    
  @return
    The MSS_SYS_key_tree function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_DISABLED_BY_USER
 */
uint8_t MSS_SYS_key_tree
(
    uint8_t* p_key,
    uint8_t op_type,
    const uint8_t* path
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_challenge_response function...
  
  The MSS_SYS_challenge_response() function accept a challenge comprising a
  7-bit optype and 128-bit path and return a 256-bit response unique to the 
  given challenge and the device.

  @param p_key
    The key parameter is a pointer to a 32 bytes array containing 256 bit 
    unique response to the given challenge.

  @param op_type
    The op_type parameter specifies the operational parameter to be used to
    generate the unique 256-bits unique response.

  @param path
    The path parameter specifies the 128-bit path to be used to generate the 
    unique 256-bits unique response.

  @return
    The MSS_SYS_challenge_response function returns one of following status
    codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
 */
uint8_t MSS_SYS_challenge_response
(
    uint8_t* p_key,
    uint8_t op_type,
    const uint8_t* path
);

/*==============================================================================
 * Non Deterministic Random Bit Generator Services.
 */
 /*-------------------------------------------------------------------------*//**
   The MSS_SYS_nrbg_reset() function is used to reset the
  non-deterministic random bit generator (NRBG).

  @return
    The MSS_SYS_nrbg_self_test function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_NRBG_CATASTROPHIC_ERROR
        - MSS_SYS_NRBG_MAX_INST_EXCEEDED
        - MSS_SYS_NRBG_INVALID_HANDLE
        - MSS_SYS_NRBG_GEN_REQ_TOO_BIG
        - MSS_SYS_NRBG_MAX_LENGTH_EXCEEDED
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_nrbg_reset(void);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_nrbg_self_test() function performs a self test of the
  non-deterministic random bit generator (NRBG).
  
  @return
    The MSS_SYS_nrbg_self_test function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_NRBG_CATASTROPHIC_ERROR
        - MSS_SYS_NRBG_MAX_INST_EXCEEDED
        - MSS_SYS_NRBG_INVALID_HANDLE
        - MSS_SYS_NRBG_GEN_REQ_TOO_BIG
        - MSS_SYS_NRBG_MAX_LENGTH_EXCEEDED
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
 */
uint8_t MSS_SYS_nrbg_self_test(void);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_nrbg_instantiate() function instantiates a non-deterministic
  random bit generator (NRBG) instance. A maximum of two concurrent instances
  are available.
  
  @param personalization_str
    The personalization_str parameter is a pointer to a buffer containing a
    random bit generator personalization string. The personalization string
    can be up to 128 bytes long.
  
  @param personalization_str_length
    The personalization_str_length parameter specifies the byte length of the
    personalization string pointed to by personalization_str.
  
  @param p_nrbg_handle
    The p_nrbg_handle parameter is a pointer to a byte that will contain the
    handle of the instantiated NRBG if this function call succeeds.
  
  @return
    The MSS_SYS_nrbg_instantiate function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_NRBG_CATASTROPHIC_ERROR
        - MSS_SYS_NRBG_MAX_INST_EXCEEDED
        - MSS_SYS_NRBG_INVALID_HANDLE
        - MSS_SYS_NRBG_GEN_REQ_TOO_BIG
        - MSS_SYS_NRBG_MAX_LENGTH_EXCEEDED
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
 */
uint8_t MSS_SYS_nrbg_instantiate
(
    const uint8_t * personalization_str,
    uint16_t personalization_str_length,
    uint8_t * p_nrbg_handle
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_nrbg_generate function generates a random bit sequence up to
  128 bytes long.
  
  @param p_requested_data
    The p_requested_data parameter is a pointer to the buffer where the requested
    random data will be stored on completion of this system service.
  
  @param p_additional_input
    The p_additional_input parameter is a pointer to the buffer containing
    additional input data for the random bit generation.
  
  @param requested_length
    The requested_length parameter specifies the number of random data bytes
    requested to be generated. The maximum generated data length is 128 bytes.
  
  @param additional_input_length
    The additional_input_length parameter specifies the number of additional
    input bytes to use in the random data generation.
  
  @param pr_req
    The pr_req parameter specifies if prediction resistance is requested.
  
  @param nrbg_handle
    The nrbg_handle parameter specifies which non-deterministic random bit
    generator (NRBG) instance will be used to generate the random data. The
    value of nrbg_handle is obtained as a result of a previous call to the
    MSS_SYS_nrbg_instantiate() function.
  
  @return
    The MSS_SYS_nrbg_generate function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_NRBG_CATASTROPHIC_ERROR
        - MSS_SYS_NRBG_MAX_INST_EXCEEDED
        - MSS_SYS_NRBG_INVALID_HANDLE
        - MSS_SYS_NRBG_GEN_REQ_TOO_BIG
        - MSS_SYS_NRBG_MAX_LENGTH_EXCEEDED
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
 */
uint8_t MSS_SYS_nrbg_generate
(
    const uint8_t * p_requested_data,
    const uint8_t * p_additional_input,
    uint8_t requested_length,
    uint8_t additional_input_length,
    uint8_t pr_req,
    uint8_t nrbg_handle
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_nrbg_reseed() function is used to reseed the non-deterministic
  random bit generator (NRBG) identified by the nrbg_handle parameter.
  
  @param p_additional_input
    The additional_input_length parameter specifies the number of additional
    input bytes used to reseed the NRBG identified by the nrbg_handle parameter.
  
  @param additional_input_length
    The additional_input_length parameter specifies the number of additional
    input bytes used to reseed the NRBG.
  
  @param nrbg_handle
    The nrbg_handle parameter specifies which NRBG instance to reseed. The value
    of nrbg_handle is obtained as a result of a previous call to the
    MSS_SYS_nrbg_instantiate() function.
  
  @return
    The MSS_SYS_nrbg_reseed function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_NRBG_CATASTROPHIC_ERROR
        - MSS_SYS_NRBG_MAX_INST_EXCEEDED
        - MSS_SYS_NRBG_INVALID_HANDLE
        - MSS_SYS_NRBG_GEN_REQ_TOO_BIG
        - MSS_SYS_NRBG_MAX_LENGTH_EXCEEDED
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
   
 */
uint8_t MSS_SYS_nrbg_reseed
(
    const uint8_t * p_additional_input,
    uint8_t additional_input_length,
    uint8_t nrbg_handle
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_nrbg_uninstantiate() function releases the non-deterministic
  random bit generator (NRBG) identified by the nrbg_handle parameter.
  
  @param nrbg_handle
    The nrbg_handle parameter specifies which NRBG instance will be released.
    The value of nrbg_handle is obtained as a result of a previous call to the
    MSS_SYS_nrbg_instantiate() function.
  
  @return
    The MSS_SYS_nrbg_uninstantiate function returns one of following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_NRBG_CATASTROPHIC_ERROR
        - MSS_SYS_NRBG_MAX_INST_EXCEEDED
        - MSS_SYS_NRBG_INVALID_HANDLE
        - MSS_SYS_NRBG_GEN_REQ_TOO_BIG
        - MSS_SYS_NRBG_MAX_LENGTH_EXCEEDED
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
 */
uint8_t MSS_SYS_nrbg_uninstantiate
(
    uint8_t nrbg_handle
);

/*==============================================================================
 * Zeroization Services.
 */
/*-------------------------------------------------------------------------*//**
  The MSS_SYS_zeroize_device() function destroys sensitive information stored on
  the device. Zeroization system services driver will destroy all user configuration
  data, user keys, user security settings, NVM, SRAM, FPGA fabric, system
  controller memory, and crypto-engine registers are erased. The level of
  information destroyed by this function is configured as part of the hardware
  flow of the design programmed into the device.

  @param
    This function does not take any parameters

  @return
    This function does not return any value.
*/
void MSS_SYS_zeroize_device
(
    void
);

/*==============================================================================
 * Programming Services.
 */

#define MSS_SYS_PROG_AUTHENTICATE    0u
#define MSS_SYS_PROG_PROGRAM         1u
#define MSS_SYS_PROG_VERIFY          2u

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_start_isp() function starts the In-System Programming (ISP) 
  system service which allows the Cortex-M3 processor to directly provide a 
  bitstream for programming the SmartFusion2 device.
  The ISP system service can perform these services:
    • Authenticate a programming bitstream
    • Program the device with a programming bitstream
    • Verify that a programming bitstream has been correctly programmed
  The mode parameter specifies the ISP system service to perform. The 
  application must also provide two functions as parameters to the 
  MSS_SYS_start_isp() function. The first function is used by the ISP system
  service to read the programming bitstream. The second function is used by 
  the ISP system service to notify the application that the ISP system service
  has completed.
  
  @param mode
    The mode parameter specifies ISP service to perform. It can be one of:
        - MSS_SYS_PROG_AUTHENTICATE
        - MSS_SYS_PROG_PROGRAM
        - MSS_SYS_PROG_VERIFY
 
  @param page_read_handler
    The page_read_handler parameter is a pointer to a function with the
    following prototype:
        uint32_t page_read_handler(uint8 const ** pp_next_page);
    The page_read_handler function must be implemented by the application
    program to provide the System Services driver with the address of the 
    next page of programming data to be sent to the System Controller and 
    the number of bytes contained in the next page. Refer to the description 
    of the comblk_page_handler_t type for details of the page_read_handler 
    function’s parameters and return values.
 
  @param isp_completion_handler
    The isp_completion_handler parameter is a pointer to a function with the
    following prototype. 
        void (*sys_serv_isp_complete_handler_t)(uint32_t status);
    The isp_completion_handler function must be implemented by the application
    program and it is called by the System Services driver when an ISP 
    operation initiated by a call to MSS_SYS_start_isp() completes. 
    
    The isp_completion_handler function receives one of the following status
    codes through its status parameter indicating the outcome of the ISP 
    operation:
        - MSS_SYS_SUCCESS
        - MSS_SYS_CHAINING_MISMATCH
        - MSS_SYS_UNEXPECTED_DATA_RECEIVED
        - MSS_SYS_INVALID_ENCRYPTION_KEY
        - MSS_SYS_INVALID_COMPONENT_HEADER
        - MSS_SYS_BACK_LEVEL_NOT_SATISFIED
        - MSS_SYS_DSN_BINDING_MISMATCH
        - MSS_SYS_ILLEGAL_COMPONENT_SEQUENCE
        - MSS_SYS_INSUFFICIENT_DEV_CAPABILITIES
        - MSS_SYS_INCORRECT_DEVICE_ID
        - MSS_SYS_UNSUPPORTED_BITSTREAM_PROT_VER
        - MSS_SYS_VERIFY_NOT_PERMITTED_ON_BITSTR
        - MSS_SYS_ABORT
        - MSS_SYS_NVM_VERIFY_FAILED
        - MSS_SYS_DEVICE_SECURITY_PROTECTED
        - MSS_SYS_PROGRAMMING_MODE_NOT_ENABLED
        - MSS_SYS_SERVICE_DISABLED_BY_USER
    
  @return
    This function return status as MSS_SYS_CLK_DIVISOR_ERROR, if fclk, pclk0, 
    pclk1 and clk_fic64 divisor are not equal to each other or set to divide by 
    32 on 060 device.
 */
uint8_t MSS_SYS_start_isp
(
    uint8_t mode,
    comblk_page_handler_t page_read_handler,
    sys_serv_isp_complete_handler_t isp_completion_handler
);


/*-------------------------------------------------------------------------*//**
  The MSS_SYS_initiate_iap() function invokes the In application programming 
  system service by sending the request to System Controller to reprogram the 
  device using a bitstream present in SPI FLASH connected to MSS SPI-0. The 
  IAP Service is initiated by a call to MSS_SYS_initiate_iap(). The IAP 
  Service can perform these services:
    - authenticate a programming bitstream
    - program a bitstream
    - verify that a programming bitstream has been correctly programmed

  @param mode
    The mode parameter specifies IAP service to perform. It can be one of:
        - MSS_SYS_PROG_AUTHENTICATE
        - MSS_SYS_PROG_PROGRAM
        - MSS_SYS_PROG_VERIFY
  
  @param bitstream_spi_addr
    The bitstream_spi_addr parameter specifies the starting location address of
    the programmed bitstream present in SPI flash connected to MSS SPI 0.
    User should copy the programming bitstream into SPI Flash before calling 
    IAP system service.
  
  @return
    The MSS_SYS_initiate_iap function will receive one of the following status
    codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_CHAINING_MISMATCH
        - MSS_SYS_UNEXPECTED_DATA_RECEIVED
        - MSS_SYS_INVALID_ENCRYPTION_KEY
        - MSS_SYS_INVALID_COMPONENT_HEADER
        - MSS_SYS_BACK_LEVEL_NOT_SATISFIED
        - MSS_SYS_DSN_BINDING_MISMATCH
        - MSS_SYS_ILLEGAL_COMPONENT_SEQUENCE
        - MSS_SYS_INSUFFICIENT_DEV_CAPABILITIES
        - MSS_SYS_INCORRECT_DEVICE_ID
        - MSS_SYS_UNSUPPORTED_BITSTREAM_PROT_VER
        - MSS_SYS_VERIFY_NOT_PERMITTED_ON_BITSTR
        - MSS_SYS_INVALID_DEVICE_CERTIFICATE
        - MSS_SYS_ABORT
        - MSS_SYS_NVM_VERIFY_FAILED
        - MSS_SYS_DEVICE_SECURITY_PROTECTED
        - MSS_SYS_PROGRAMMING_MODE_NOT_ENABLED
        - MSS_SYS_ENVM_PROGRAMMING_OPERATION_FAIL
        - MSS_SYS_ENVM_VERIFY_OPERATION_FAIL
        - MSS_SYS_ACCESS_ERROR
        - MSS_SYS_PUF_ACCESS_ERROR
        - MSS_SYS_BAD_COMPONENT
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_CLK_DIVISOR_ERROR
*/
uint8_t MSS_SYS_initiate_iap
(
    uint8_t mode,
    uint32_t bitstream_spi_addr
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_check_digest() function is used to recalculate and compare 
  cryptographic digests of selected NVM component(s) – FPGA fabric, eNVM0, and 
  eNVM1 – to those previously computed and saved in NVM.
  Note: The FPGA fabric will enter the Flash*Freeze state if it is powered up 
  when its digest is checked.

  @param options
    The options parameter specifies which components' digest will be recalculated
    and checked. The allowed values for the options parameter are any one of the 
    following bitmask constants or a bitwise OR of more than one:
    • MSS_SYS_DIGEST_CHECK_FABRIC  (bit mask = 0x01)
    • MSS_SYS_DIGEST_CHECK_ENVM0   (bit mask = 0x02)
    • MSS_SYS_DIGEST_CHECK_ENVM1   (bit mask = 0x04)
    • MSS_SYS_DIGEST_CHECK_SYS     (bit mask = 0x08)
    • MSS_SYS_DIGEST_CHECK_ENVMFP  (bit mask = 0x10)
    • MSS_SYS_DIGEST_CHECK_ENVMUP  (bit mask = 0x20)
    NOTE: Private factory eNVM and private user eNVM digest checks are only 
          available on the M2S060 and larger devices.
  @return
    The MSS_SYS_check_digest function returns the result of the digest check as
    an 8-bit unsigned integer. The meaning of the digest check return value is
    as follows:
        bit 0: Fabric digest error
        bit 1: ENVM0 digest error
        bit 2: ENVM1 digest error
        bit 3: System Controller ROM digest error
        bit 4: Private eNVM factory digest error
        bit 5: Private eNVM user digest error
        bit 7: Service Disable by user lock.
    A '1' in one of the above bits indicates a digest mismatch. The return 
    value can be compared to the bitmask constants specified as allowed values
    for the options parameter to discover which of the NVM components produced
    a digest check error.
    On 060 device, the MSS_SYS_check_digest function returns 
    MSS_SYS_CLK_DIVISOR_ERROR, if the the divisor values of fclk, pclk0, pclk1 
    and clk_fic64 divisor are not equal to each other or set to divide by 32.
 */
#define MSS_SYS_DIGEST_CHECK_FABRIC     0x01u
#define MSS_SYS_DIGEST_CHECK_ENVM0      0x02u
#define MSS_SYS_DIGEST_CHECK_ENVM1      0x04u
#define MSS_SYS_DIGEST_CHECK_SYS        0x08u
#define MSS_SYS_DIGEST_CHECK_ENVMFP     0x10u
#define MSS_SYS_DIGEST_CHECK_ENVMUP     0x20u

#define MSS_SYS_DIGEST_CHECK_SVCDISABLED     0x80u

uint8_t MSS_SYS_check_digest
(
    uint8_t options
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_puf_create_activation_code() function is used to create the 
  SRAM-PUF user activation code. This function is typically only used once when 
  enrolling the device into the overall system it operates in. It creates an 
  activation code which will be used to regenerate the SRAM-PUF secret key after
  each power-up of the SRAM-PUF. The activation code is used to eliminate the 
  randomness of the SRAM-PUF power-up content in order to retrieve the device’s 
  unique PUF secret key.
  Note: This system service is only available on large SmartFusion2 devices
        starting with the M2S060.
  
  @param
    This function does not take any parameters.
        
  @return
    The MSS_SYS_puf_create_activation_code() function returns one of the 
    following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_ENVM_ERROR
        - MSS_SYS_PUF_ERROR_WHEN_CREATING
        - MSS_SYS_INVALID_SUBCMD
        - MSS_SYS_ENVM_PROGRAM_ERROR
        - MSS_SYS_ENVM_VERIFY_ERROR
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_puf_create_activation_code
(
    void
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_puf_delete_activation_code() function is used to delete the user 
  activation code. This function would typically be used only once when 
  decommissioning the device.
  Note: This system services is only available on large SmartFusion2 devices
        starting with the M2S060.
  
  @param
    This function does not take any parameters.

  @return
    The MSS_SYS_puf_delete_activation_code() function returns one of the 
    following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_ENVM_ERROR
        - MSS_SYS_PUF_ERROR_WHEN_CREATING
        - MSS_SYS_INVALID_SUBCMD
        - MSS_SYS_ENVM_PROGRAM_ERROR
        - MSS_SYS_ENVM_VERIFY_ERROR
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_puf_delete_activation_code
(
    void
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_puf_get_number_of_keys() function is used to retrieve the number
  of user keys enrolled with the SRAM-PUF service. The number of enrolled keys
  is also the key identification number to use for the next key to enroll since
  keys must be enrolled sequentially and the key numbering starts at zero. Up
  to 58 keys can be enrolled. Keys number 0 and 1 are used for design security
  and are not available to the user.
  Note: This system service is only available on large SmartFusion2 devices
  starting with the M2S060.

  @param p_number_of_user_keys
    The p_user_key parameter is a pointer to the byte in which the number of 
    keys will be written on successful completion of the system service.

  @return
    The MSS_SYS_puf_get_number_of_user_keys() function returns one of the 
    following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_ENVM_ERROR
        - MSS_SYS_PUF_ERROR_WHEN_CREATING
        - MSS_SYS_ENVM_PROGRAM_ERROR
        - MSS_SYS_INVALID_HASH
        - MSS_SYS_INVALID_USER_AC1
        - MSS_SYS_ENVM_VERIFY_ERROR
        - MSS_SYS_PRIVATE_ENVM_USER_DIGEST_MISMATCH
        - MSS_SYS_DRBG_ERROR
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_puf_get_number_of_keys
(
    uint8_t* p_number_of_keys
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_puf_enroll_key() function is used to enroll keys into the 
  SRAM-PUF hardware block. Keys can be either intrinsic keys or extrinsic keys. 
  An intrinsic key’s value is randomly generated by the SRAM-PUF hardware block
  during key enrollment. An extrinsic key’s value is supplied by the user. A key
  code is created and stored in the System Controller’s private eNVM during key 
  enrollment. The key code along with the activation code created as part of the
  call to MSS_SYS_puf_create_activation_code()  and the SRAM-PUF start-up value 
  can then be used later to regenerate the enrolled key’s value. Enrolled keys 
  can be later reconstructed and retrieved using the MSS_SYS_puf_fetch_key() 
  function. The value of the key is protected until it is fetched since its 
  actual value is not stored anywhere in the system.
  Note: This system service is only available on large SmartFusion2 devices
        starting with the M2S060.
  
  @param key_number 
    The key_number parameter specifies the key number that will be used to 
    identify the key in later use after enrollment. The key number will be used 
    to identify which key to retrieve in subsequent calls to function 
    MSS_SYS_puf_fetch_key().
    Keys must be enrolled sequentially. Therefore, an arbitrary value cannot be 
    used for key_number when enrolling a new key. The value for key_number must
    be derived from a call to MSS_SYS_puf_get_number_of_keys() to find the 
    number of keys currently enrolled and derive the next key number in the 
    sequence.
    Note: Valid values for key identification numbers are 2 to 57. Keys number
          0 and 1 are used for design security and not available to the user.
  
  @param key_size 
    The key_size parameter specifies the size of the key to enroll. The key size
    is a multiple of 64-bit up to 4096-bit.

  @param p_key_value
    The p_key_value parameter is a pointer to the buffer containing the value of
    the key to enroll. The buffer pointed to by p_key_value contains the value 
    of the extrinsic key specified by the user.
    Setting this pointer’s value to zero specifies that an intrinsic key is to 
    be enrolled. In this case, a random value is generated using the SRAM-PUF as
    the key value.

  @param p_key_location
    The p_key_location parameter is a pointer to the buffer where the key will 
    be copied when it is fetched through a call to MSS_SYS_puf_fetch_key().

  @return
    The MSS_SYS_puf_enroll_key() function returns one of the following status 
    codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_ENVM_ERROR
        - MSS_SYS_PUF_ERROR_WHEN_CREATING
        - MSS_SYS_INVALID_REQUEST_OR_KC
        - MSS_SYS_ENVM_PROGRAM_ERROR
        - MSS_SYS_INVALID_HASH
        - MSS_SYS_INVALID_USER_AC1
        - MSS_SYS_ENVM_VERIFY_ERROR
        - MSS_SYS_INCORRECT_KEYSIZE_FOR_RENEWING_A_KC
        - MSS_SYS_PRIVATE_ENVM_USER_DIGEST_MISMATCH
        - MSS_SYS_USER_KEY_CODE_INVALID_SUBCMD
        - MSS_SYS_DRBG_ERROR
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_puf_enroll_key
(
    uint8_t key_number,
    uint16_t key_size,
    uint8_t* p_key_value,
    uint8_t* p_key_location
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_puf_delete_key() function is used to delete a previously enrolled
  key from the SRAM-PUF.
  Note: This system service is only available on large SmartFusion2 devices
        starting with the M2S060.
  
  @param key_number
    The key_number parameter specifies the key number of the key to delete.

  @return
    The MSS_SYS_puf_delete_key() function returns one of the following status 
    codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_ENVM_ERROR
        - MSS_SYS_PUF_ERROR_WHEN_CREATING
        - MSS_SYS_INVALID_REQUEST_OR_KC
        - MSS_SYS_ENVM_PROGRAM_ERROR
        - MSS_SYS_INVALID_HASH
        - MSS_SYS_INVALID_USER_AC1
        - MSS_SYS_ENVM_VERIFY_ERROR
        - MSS_SYS_INCORRECT_KEYSIZE_FOR_RENEWING_A_KC
        - MSS_SYS_PRIVATE_ENVM_USER_DIGEST_MISMATCH
        - MSS_SYS_USER_KEY_CODE_INVALID_SUBCMD
        - MSS_SYS_DRBG_ERROR
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_puf_delete_key
(
    uint8_t key_number
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_puf_fetch_key() function is used to retrieve a user PUF key from 
  the SRAM-PUF hardware block. The key must have been previously enrolled using
  the MSS_SYS_puf_enroll_key() function. The key to retrieve is identified 
  through the key number used at key enrollment time. The key value is copied 
  into the buffer location specified at key enrollment time. The location of 
  this buffer is returned through function argument pp_key.
  The key value is reconstructed based on the SRAM-PUF power-on value, the 
  activation code created when the device was commissioned using the 
  MSS_SYS_puf_create_activation_code() function and the key code stored in the 
  SRAM-PUF hardware block’s  private eNVM at key enrollment time. The key value 
  does not exist anywhere in the system until it is retrieved by a call to 
  MSS_SYS_puf_fetch_key(). Care must be taken to destroy the key value returned 
  by MSS_SYS_puf_fetch_key() once it is not required anymore.
  Note: This system service is only available on large SmartFusion2 devices
        starting with the M2S060.
        
  @param key_number
    The key_number parameter specifies the key number identifying the user key 
    to fetch. The valid range of key numbers is from 2 to 57.

  @param pp_key
    The pp_key parameter is a pointer to a pointer to the buffer that will 
    contain the user key value on successful completion of the system service. 
    The pp_key parameter can be set to zero if your application keeps track of 
    the location of the key specified though the call to function 
    MSS_SYS_puf_enroll_key() at key enrollment time.

  @return
    The MSS_SYS_puf_fetch_key() function returns one of the following status 
    codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_PUF_ERROR_WHEN_CREATING
        - MSS_SYS_INVALID_KEYNUM_OR_ARGUMENT
        - MSS_SYS_INVALID_HASH
        - MSS_SYS_PRIVATE_ENVM_USER_DIGEST_MISMATCH
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_puf_fetch_key
(
    uint8_t key_number,
    uint8_t ** pp_key
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_puf_export_keycodes() function is used to export an encrypted 
  copy of all the key codes used internally by the SRAM-PUF hardware block to
  reconstruct the enrolled keys. Up to 3894 bytes of data can be exported
  depending on the number and size of keys enrolled.
  Keys cannot be fetched any more after calling MSS_SYS_puf_export_keycodes()
  until a subsequent call to function MSS_SYS_puf_import_keycodes() is made
  with the exported encrypted key codes.
  Calling MSS_SYS_puf_export_keycodes() and moving the exported data off chip
  is similar to removing the enrolled keys from the device. The enrolled keys
  will only be available again if the exported key codes are imported back into
  the device.
  A SmartFusion2 device will only accept imported key codes generated from the
  last set of enrolled keys on that specific device. This makes the exported
  key codes data specific to one unique SmartFuson2 device. Key codes cannot 
  be exported from one SmartFusion2 device and imported into another 
  SmartFusion2 device. The exported key codes data is specific to the unique 
  SmartFusion2 device it was exported from.
  Keys cannot be reconstructed from the exported key codes data since the 
  intrinsic secret of the SRAM-PUF is required to reconstruct the keys from 
  the key codes. Furthermore, the key codes data is also encrypted using a 
  random key generated from the SRAM-PUF thus preventing an attacker from 
  deriving useful information from the exported key codes data.
  Note: This system service is only available on large SmartFusion2 devices
        starting with the M2S060.
  
  @param p_keycodes
    The p_keycodes parameter is a pointer to the buffer where the PUF key codes
    will be exported.
    
  @return
    The MSS_SYS_puf_export_keycodes() function returns one of the following 
    status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_ENVM_ERROR
        - MSS_SYS_PUF_ERROR_WHEN_CREATING
        - MSS_SYS_INVALID_REQUEST_OR_KC
        - MSS_SYS_ENVM_PROGRAM_ERROR
        - MSS_SYS_INVALID_HASH
        - MSS_SYS_INVALID_USER_AC1
        - MSS_SYS_ENVM_VERIFY_ERROR
        - MSS_SYS_INCORRECT_KEYSIZE_FOR_RENEWING_A_KC
        - MSS_SYS_PRIVATE_ENVM_USER_DIGEST_MISMATCH
        - MSS_SYS_USER_KEY_CODE_INVALID_SUBCMD
        - MSS_SYS_DRBG_ERROR
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
 */
uint8_t MSS_SYS_puf_export_keycodes
(
    uint8_t * p_keycodes
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_puf_import_keycodes() function is used to import a set of PUF
  key codes that was previously exported using the MSS_SYS_puf_export_keycodes()
  function. Importing the exported key codes allows the enrolled keys to be
  regenerated. Enrolled keys cannot be regenerated while the key codes have
  been exported and not imported back.
  Importing back the key codes results in all keys being regenerated and copied
  to the memory locations specified during key enrollment. The content of the
  buffer holding the imported key codes is modified by function
  MSS_SYS_puf_import_keycodes() to contain the list of pointers to the
  locations where the keys have been regenerated. This list starts with the
  address where key number 2 has been regenerated. The location for keys 0 and
  1 are not contained in that list because these keys are used for design
  security and are not accessible to the user.
  Note: This system service is only available on large SmartFusion2 devices
  starting with the M2S060.

  @param p_keycodes
    The p_keycodes parameter is a pointer to the buffer containing the PUF key
    codes to import.
    
  @return
    The MSS_SYS_puf_import_keycodes() function returns one of the following status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_ENVM_ERROR
        - MSS_SYS_PUF_ERROR_WHEN_CREATING
        - MSS_SYS_INVALID_REQUEST_OR_KC
        - MSS_SYS_ENVM_PROGRAM_ERROR
        - MSS_SYS_INVALID_HASH
        - MSS_SYS_INVALID_USER_AC1
        - MSS_SYS_ENVM_VERIFY_ERROR
        - MSS_SYS_INCORRECT_KEYSIZE_FOR_RENEWING_A_KC
        - MSS_SYS_PRIVATE_ENVM_USER_DIGEST_MISMATCH
        - MSS_SYS_USER_KEY_CODE_INVALID_SUBCMD
        - MSS_SYS_DRBG_ERROR
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
  */
uint8_t MSS_SYS_puf_import_keycodes
(
    uint8_t * p_keycodes
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_puf_fetch_ecc_public_key() function is used to fetch PUF ECC 
  public key from eNVM.

  @param p_puf_public_key
    The p_puf_public_key parameter is a pointer to buffer where the PUF ECC 
    public key will be stored on successful completion of system service.
    Note: This system service is only available on large SmartFusion2 devices
          starting with the M2S060.

  @return
    The MSS_SYS_puf_fetch_ecc_public_key() function returns one of the following
    status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_NO_VALID_PUBLIC_KEY
        - MSS_SYS_PRIVATE_ENVM_USER_DIGEST_MISMATCH
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_puf_fetch_ecc_public_key
(
    uint8_t* p_puf_public_key
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_puf_get_random_seed() function is used to generate a 256-bit true 
  random number seed using the SmartFusion2 SRAM-PUF.

  @param p_puf_seed
    The p_puf_seed parameter is a pointer to the buffer where the PUF seed will 
    be stored on successful completion of the system service.
    Note: This system service is only available on large SmartFusion2 devices
          starting with the M2S060.
  
  @return
    The MSS_SYS_puf_get_random_seed()  function returns one of the following 
    status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_PUF_ERROR_WHEN_CREATING
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_puf_get_random_seed
(
    uint8_t* p_puf_seed
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_ecc_point_multiplication() function provides access to the
  SmartFusion2 System Controller’s Elliptic Curve Cryptography (ECC) point
  multiplication system service. The MSS_SYS_ecc_point_multiplication() function
  computes the point multiplication of a point P on the NIST-384 curve by a
  scalar value d. The point multiplication results in point Q as follows:
    d * P = Q
  The points are defined by their x and y coordinates as follows:
    P = (x1, y1)
    Q = (x2, y2)
  Each x and y coordinate and the scalar d are 384-bit long big-endian numbers.
  Note: The point at infinity is specified using point x =0, y = 0.
  Note: This system service is only available on large SmartFusion2 devices 
        starting with the M2S060.

  @param p_scalar_d
    The p_scalar_d parameter is a pointer to a buffer containing the 384-bit
    scalar d. The scalar d is 384-bit long meaning that p_scalar_d should point
    to a 96 bytes buffer.
    
  @param p_point_p
    The p_point_p parameter is a pointer to a buffer containing the (x1, y1)
    coordinates of input point P. Each x and y coordinate is 384-bit long
    meaning that p_point_p should point to a 96 bytes buffer.
    
  @param p_point_q
    The p_point_q parameter is a pointer to a buffer where the (x2, y2)
    coordinates of result Q will be stored. Each x and y coordinate is 384-bit
    long meaning that p_point_q should point to a 96 bytes buffer.
    
  @return
    The MSS_SYS_ecc_point_multiplication function returns one of the following
    status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_ecc_point_multiplication
(
    uint8_t* p_scalar_d,
    uint8_t* p_point_p,
    uint8_t* p_point_q
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_ecc_point_addition() function provides access to the SmartFusion2
  System Controller’s Elliptic Curve Cryptography (ECC) point addition system
  service. The MSS_SYS_ecc_point_addition() function computes the addition of
  two points, P and Q, on the NIST P-384 curve. The point addition results in
  point R as follows:
    P + Q = R
  The points are defined by their x and y coordinates as follows:
    P = (x1, y1)
    Q = (x2, y2)
    R = (x3, y3)
  Each x and y coordinate are 384-bit long big-endian numbers.
  Note: The point at infinity is specified using point x =0, y = 0.
  Note: This system service is only available on large SmartFusion2 devices
        starting with the M2S060.

  @param p_point_p
    The p_point_p parameter is a pointer to a buffer containing the (x1, y1)
    coordinates of input point P. Each x and y coordinate is 384-bit long
    meaning that p_point_p should point to a 96 bytes buffer.
    
  @param p_point_q
    The p_point_q parameter is a pointer to a buffer containing the (x2, y2)
    coordinates of input point Q. Each x and y coordinate is 384-bit long
    meaning that p_point_q should point to a 96 bytes buffer.
    
  @param p_point_r
    The p_point_r parameter is a pointer to a buffer where the (x3, y3)
    coordinates of result R will be stored. Each x and y coordinate is 384-bit
    long meaning that p_point_r should point to a 96 bytes buffer.
    
  @return
    The MSS_SYS_ecc_point_addition() function returns one of the following
    status codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_MEM_ACCESS_ERROR
        - MSS_SYS_SERVICE_NOT_LICENSED
        - MSS_SYS_SERVICE_DISABLED_BY_FACTORY
        - MSS_SYS_SERVICE_DISABLED_BY_USER
        - MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_ecc_point_addition
(
    uint8_t* p_point_p,
    uint8_t* p_point_q,
    uint8_t* p_point_r
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_ecc_get_base_point() function provides the value of the base
  point G for NIST elliptic curve P-384. The value of the base point can then
  be used to generate a public key by multiplying the base point G with a 
  private key using function MSS_SYS_ecc_point_multiplication().
  Note: This system service is only available on large SmartFusion2 devices
        starting with the M2S060.
        
  @param p_point_p
    The p_point_g parameter is a pointer to a buffer where the coordinate of 
    base point G (xG, yG) for curve P-384 will be stored. Each x and y 
    coordinate is 384-bit long meaning that p_point_g should point to a 96 
    bytes buffer.
    
  @return
    This function does not return a value.
*/
void MSS_SYS_ecc_get_base_point
(
    uint8_t* p_point_g
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_start_clock_monitor() function enables clock monitoring based on
  user configuration. The system controller will start monitoring the 50MHz
  clock timing reference for four 1MHz clock cycle. The expected count is 200 
  +/- tolerance. If the clock fall outside the tolerance limits, interrupt will
  be generated and system controller will send clock monitor tamper detect 
  event through COMBLK. MSS should inform to the application about clock 
  monitoring tamper detect event though call back function.
  NOTE: Do not enable both start clock monitoring and stop clock monitoring at 
        the same time.
  Note: This system service is only available on large SmartFusion2 devices
  starting with the M2S060.
 
  @param 
    This function does not take any parameters

  @return
    The MSS_SYS_start_clock_monitor() function returns one of the following
    status codes:
        • MSS_SYS_SUCCESS
        • MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_start_clock_monitor
(
    void
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_stop_clock_monitor() function is used to stop the clock monitoring.
  System controller will disable 50 MHZ timing clock monitoring and clock 
  monitor tamper detect interrupt.
  NOTE: Do not enable both start clock monitoring and stop clock monitoring at 
        the same time.
  NOTE: This system service is only available on large SmartFusion2 devices 
        starting with the M2S060.
        
  @param 
    This function does not take any parameters

  @return
    The MSS_SYS_stop_clock_monitor() function returns one of the following
    status codes:
        • MSS_SYS_SUCCESS
        • MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_stop_clock_monitor
(
    void
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_enable_puf_power_down() function is used to instruct the system
  controller to power down the PUF after each of the following operations:
    • key fetch
    • key creation
    • key import
    • random seed generation
  Powering down the PUF after these operations is the default PUF behaviour.
  Note: This system service is only available on large SmartFusion2 devices
        starting with the M2S060.
        
  @param 
    This function does not take any parameters.

  @return
    The MSS_SYS_enable_puf_power_down() function returns one of the following
    status codes:
        • MSS_SYS_SUCCESS
        • MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_enable_puf_power_down
(
    void
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_disable_puf_power_down() function is used to retain PUF power 
  after the following operations:
    • key fetch
    • key creation
    • key import
    • random seed generation
  Note: This system service is only available on large SmartFusion2 devices
      starting with the M2S060.
      
  @param 
    This function does not take any parameters

  @return
    The MSS_SYS_disable_puf_power_down() function returns one of the following
    status codes:
        • MSS_SYS_SUCCESS
        • MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_disable_puf_power_down
(
    void
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_clear_lock_parity() function is used to clear the previously set 
  Lock Parity tamper flag. System controller will set this flag on detection of 
  parity error on internal lock data. To clear lock parity flag, use tamper 
  control service with bit 4 of Option set to 1, then the LOCKPARITY tamper flag
  is cleared provided the hardware conditions are no longer present to raise 
  this flag.
  Note: This system service is only available on large SmartFusion2 devices
      starting with the M2S060.
      
  @param 
    This function does not take any parameters

  @return
    The MSS_SYS_clear_lock_parity() function returns one of the following
    status codes:
        • MSS_SYS_SUCCESS
        • MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_clear_lock_parity
(
    void
);

/*-------------------------------------------------------------------------*//**
  The MSS_SYS_clear_mesh_short() function is used to clear the previously mesh 
  short tamper flag. System Controller monitors the security flash array for 
  invasive tampering using an active mesh. This mesh is driven by LFSR and the 
  return value is monitored for discrepancies against the expected value generated
  by the LFSR. When a tamper event is detected the MESHSHORT tamper flag is set,
  generating a tamper interrupt. To clear mesh short tamper flag, use tamper 
  control service with bit 5 of Options set to 1. The MESHSHORT tamper flag is 
  cleared provided the hardware conditions are no longer present to raise this 
  flag. 
  Note: This system service is only available on large SmartFusion2 devices
      starting with the M2S060.
      
  @param 
    This function does not take any parameters

  @return
    The MSS_SYS_clear_mesh_short() function returns one of the following
    status codes:
        • MSS_SYS_SUCCESS
        • MSS_SYS_UNEXPECTED_ERROR
*/
uint8_t MSS_SYS_clear_mesh_short
(
    void
);

/*-------------------------------------------------------------------------*//**
  The IAP Service requests the System Controller to reprogram the device using
  a bitstream already programmed into MSS SPI 0. The IAP Service is initiated by
  a call to MSS_SYS_initiate_IAP(). The IAP Service can:
    - authenticate a programming bitstream
    - program a bitstream
    - verify that a programming bitstream has been correctly programmed

  @param mode
    The mode parameter specifies IAP service to perform. It can be one of:
        - MSS_SYS_PROG_AUTHENTICATE
        - MSS_SYS_PROG_PROGRAM
        - MSS_SYS_PROG_VERIFY
  
  @param bitstream_spi_addr
    The bitstream_spi_addr parameter specifies the address of the programming
    bitstream within the SPI flash connected to MSS SPI 0.
  
  @return
    The MSS_SYS_initiate_IAP function will receive one of the following status
    codes:
        - MSS_SYS_SUCCESS
        - MSS_SYS_CHAINING_MISMATCH
        - MSS_SYS_UNEXPECTED_DATA_RECEIVED
        - MSS_SYS_INVALID_ENCRYPTION_KEY
        - MSS_SYS_INVALID_COMPONENT_HEADER
        - MSS_SYS_BACK_LEVEL_NOT_SATISFIED
        - MSS_SYS_DSN_BINDING_MISMATCH
        - MSS_SYS_ILLEGAL_COMPONENT_SEQUENCE
        - MSS_SYS_INSUFFICIENT_DEV_CAPABILITIES
        - MSS_SYS_INCORRECT_DEVICE_ID
        - MSS_SYS_UNSUPPORTED_BITSTREAM_PROT_VER
        - MSS_SYS_VERIFY_NOT_PERMITTED_ON_BITSTR
        - MSS_SYS_INVALID_DEVICE_CERTIFICATE
        - MSS_SYS_ABORT
        - MSS_SYS_NVM_VERIFY_FAILED
        - MSS_SYS_DEVICE_SECURITY_PROTECTED
        - MSS_SYS_PROGRAMMING_MODE_NOT_ENABLED
        - MSS_SYS_ENVM_PROGRAMMING_OPERATION_FAIL
        - MSS_SYS_ENVM_VERIFY_OPERATION_FAIL
        - MSS_SYS_ACCESS_ERROR
        - MSS_SYS_PUF_ACCESS_ERROR
        - MSS_SYS_BAD_COMPONENT
        - MSS_SYS_SERVICE_DISABLED_BY_USER
*/
uint8_t MSS_SYS_initiate_IAP
(
    uint8_t mode,
    uint32_t bitstream_spi_addr
);

#ifdef __cplusplus
}
#endif

#endif /* __MSS_SYS_SERVICES_H_ */
