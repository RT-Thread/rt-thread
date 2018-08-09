/**
* \copyright
* Copyright© 2018, Infineon Technologies AG
* All rights reserved.                                                         
*
* This software is provided with terms and conditions as specified in OPTIGA™ Trust X Evaluation Kit License Agreement.
* \endcopyright
*
* \author   Infineon AG
*
* \file
*
* \brief    This file implements the prototype declarations of pal socket functionalities
* \ingroup  grPAL
* @{
*/


#ifndef _PAL_SOCKET_H_
#define _PAL_SOCKET_H_

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/

#ifndef WIN32
    #include "Datatypes.h"
	#include "DAVE.h"
	#include "udp.h"
    #include "inet.h"
#else
	#include <winsock2.h>
	#include "Datatypes.h"
#endif

#include "ErrorCodes.h"
#include "UDPErrorCodes.h"

/// @cond hidden
/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/
#ifndef WIN32 
    #define IPAddressParse(pzIpAddress, psIPAddress)      (inet_aton(pzIpAddress, psIPAddress))
#else
    #define IPAddressParse(pzIpAddress, psIPAddress)      (1)
#endif
/// @endcond
/**********************************************************************************************************************
 * ENUMS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DATA STRUCTURES
 *********************************************************************************************************************/

#ifndef WIN32  
/**
 * \brief Pointer type definition of pal socket receive event callback
 */
typedef void (*pal_socket_event_listener)(void *arg, struct udp_pcb *pcb, struct pbuf *p,
		                                  ip_addr_t *addr, u16_t port);
#endif



/**
 * \brief This structure contains socket communication data
 */
typedef enum eRecvMode_d 
{
    eBlock = 0x10,
    
    eNonBlock = 0x20
}eRecvMode_d;

/**
 * \brief This structure contains socket communication data
 */
#ifndef WIN32

typedef struct pal_socket 
{
 
    ///UDP structure Tx
    struct udp_pcb *pcbTx;
    
    ///UDP structure Rx
    struct udp_pcb *pcbRx;
    
    //Received IP address
    ip_addr_t sIPAddress;
        
    ///Function pointer to hold receive callback
    pal_socket_event_listener pfListen;

    ///Port for UDP communication
    uint16_t wPort;
        
    ///Transport Layer Timeout
    uint16_t wTimeout;
    
    ///Enumeration to indicate Blocking or Non blocking
    uint8_t bMode;
    
} pal_socket_t;

#else

typedef struct pal_socket 
{
    ///Received IP address
    char* sIPAddress;
    
    ///Port for UDP communication
    uint16_t wPort;
    
    ///Pointer to the socket for Receiving
    SOCKET SocketHdl;
    
    ///IPv4 Socket address for Receiving
    SOCKADDR_IN sSocketAddrIn;  
    
    ///Transport Layer Timeout
    uint16_t wTimeout;
   
    ///Enumeration to indicate Blocking or Non blocking
    uint8_t bMode;
    
} pal_socket_t;
#endif

/**********************************************************************************************************************
 * API Prototypes
 *********************************************************************************************************************/

/**
 * \brief Assign IP address
 */
#ifndef WIN32
int32_t pal_socket_assign_ip_address(const char* p_ip_address,void *p_input_ip_address);
#else
int32_t pal_socket_assign_ip_address(const char_t* p_ip_address,char** p_input_ip_address);
#endif

/**
 * \brief Initializes the socket communication structure
 */
int32_t pal_socket_init(pal_socket_t* p_socket);

/**
 * \brief Creates server port and bind
 */
int32_t pal_socket_open(pal_socket_t* p_socket,
                        uint16_t port);
/**
 * \brief Creates a client port and connect
 */
int32_t pal_socket_connect(pal_socket_t* p_socket,
                           uint16_t port);
/**
 * \brief Receive data from the client
 */
int32_t pal_socket_listen(pal_socket_t* p_socket, uint8_t *p_data,
                          uint32_t *p_length);
/**
 * \brief Sends the data to the the client
 */
int32_t pal_socket_send(const pal_socket_t* p_socket, uint8_t *p_data,
                        uint32_t length);
/**
 * \brief Closes the socket communication and release the udp port
 */
void pal_socket_close(pal_socket_t* p_socket);

#endif //_PAL_SOCKET_H_

/**
* @}
*/

