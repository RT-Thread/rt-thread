/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2009 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ******************************************************************************
 *
 * THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
 * IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************//*!
 *
 * @file phdc_com_model.h
 *
 * @author
 *
 * @version
 *
 * @date May-28-2009
 *
 * @brief The file contains Macro's and functions needed by IEEE 11073 layer
 *
 *****************************************************************************/
#ifndef _PHD_COM_MODEL_H
#define _PHD_COM_MODEL_H

#include "types.h"
#include "user_config.h"
#if (defined LITTLE_ENDIAN)
#include "ieee11073_phd_types_kinetis.h"    /* IEEE11073 Data Structures */
#else
#include "ieee11073_phd_types.h"    /* IEEE11073 Data Structures */
#endif
#include "ieee11073_nom_codes.h"

/******************************************************************************
 * Constants - None
 *****************************************************************************/

/******************************************************************************
 * Macro's
 *****************************************************************************/
#define SEND_DATA_QOS                                   (0x88)
/* Agent states */
#define  PHD_AG_STATE_DISCONNECTED                      0x00
#define  PHD_AG_STATE_CON_UNASSOCIATED                  0x11
#define  PHD_AG_STATE_CON_ASSOCIATING                   0x12
#define  PHD_AG_STATE_CON_ASSOC_CFG_SENDING_CONFIG      0x73
#define  PHD_AG_STATE_CON_ASSOC_CFG_WAITING_APPROVAL    0x74
#define  PHD_AG_STATE_CON_ASSOC_OPERATING               0x35
#define  PHD_AG_STATE_CON_DISASSOCIATING                0x16

/* Agent event */
#define  PHD_AG_EVT_TRANSPORT_DISCONNECTED       0x00
#define  PHD_AG_EVT_TRANSPORT_CONNECTED          0x01

/* apdu received events */
#define  PHD_AG_EVT_ASSOC_REQ_RECIVED            0x02
#define  PHD_AG_EVT_ASSOC_RES_RECIVED            0x03
#define  PHD_AG_EVT_ASSOC_REL_REQ_RECIVED        0x04
#define  PHD_AG_EVT_ASSOC_REL_RES_RECIVED        0x05
#define  PHD_AG_EVT_ASSOC_ABRT_RECIVED           0x06
#define  PHD_AG_EVT_PRESENTATION_RECIVED         0x07

/* transport send/receive event */
#define  PHD_AG_EVT_TRANSPORT_APDU_RECEIVED      0x80
#define  PHD_AG_EVT_TRANSPORT_SENT_COMPLETED     0x81

#define  AG_MAX_STATES						7
#define  AG_MAX_EVENTS						0x08
#define PHD_ASSOC_RETRY_COUNT               3

#define  AG_PHD_STATE_MASK					0x0f


/* Events sent to application layer */
#define APP_PHD_UNINITIALISED               0
#define APP_PHD_INITIALISED                 1
#define APP_PHD_CONNECTED_TO_HOST           2
#define APP_PHD_DISCONNECTED_FROM_HOST      3
#define APP_PHD_MEASUREMENT_SENT            4
#define APP_PHD_MEASUREMENT_SENDING         5
#define APP_PHD_ASSOCIATION_TIMEDOUT        6
#define APP_PHD_ERROR                       7
#define APP_PHD_INITIATED                   8
#define APP_PHD_SELECT_TIMER_STARTED        9
#define APP_PHD_DISCONNECTING               10
#define APP_PHD_SELECT_TIMER_OFF            11
#define INVALID_TIMER_VALUE                 0xFF

/* PHD Timeouts */
#define PHD_ASSOCIATION_TIMEOUT				10000	/* 10 sec Timeout */
#define PHD_CONFIGURATION_TIMEOUT			10000	/* 10 sec Timeout */
#define PHD_ASSOC_RELEASE_TIMEOUT			3000	/* 3 sec Timeout */
#define PHD_DEFAULT_RESPONSE_TIMEOUT		3000	/* 3 sec Timeout */	

/* Request/Response Sizes */
#define ASSOC_REQ_SIZE                      54
#define REL_REQ_SIZE                        6
#define REL_RES_SIZE                        6
#define ABRT_SIZE                           6

#if (defined __MK_xxx_H__)
#define UPPER_BYTE_SHIFT                    0
#else
#define UPPER_BYTE_SHIFT                    8
#endif

#define LOW_NIBBLE_MASK                     0x0f
#define LOW_BYTE_MASK                       0xff

/* APDU Header Size */
#define APDU_HEADER_SIZE                    4

/*****************************************************************************
 * Types
 *****************************************************************************/
#pragma pack(1)

/* callback function pointer structure for Application to handle events */
typedef void(_CODE_PTR_ PHD_STATE_MC_FUNC)(uint_8, APDU*);

/* callback function pointer structure for Application to handle events */
typedef void(_CODE_PTR_ PHD_CALLBACK)(uint_8, uint_8);

typedef void (_CODE_PTR_ USB_PHD_SEND_MEASUREMENTS)(uint_8, void*, void*);

typedef struct _phd_cnf_param
{
	uint_8_ptr AssociationReq;
	uint_8_ptr ConfigEvntRpt;
	uint_32 ConfigEvntRptSize;
	uint_8_ptr AssociationRelReq;
	uint_8_ptr AssociationRelRes;
	uint_8_ptr DimGetAttrRes;
	uint_32 DimGetAttrResSize;
	uint_16 ConfigurationVal;
	USB_PHD_SEND_MEASUREMENTS usb_phd_send_msr;
}PHD_CNF_PARAM, *PHD_CNF_PARAM_PTR;

#if defined(__CWCC__)
	#pragma align_array_members off
	#pragma options align=reset
#elif defined(__IAR_SYSTEMS_ICC__)
	#pragma pack()
#endif

/*****************************************************************************
 * Global variables
 *****************************************************************************/
extern PHD_CNF_PARAM const g_phd_cnf_param[MAX_DEV_SPEC_SUPPORTED];
/*****************************************************************************
 * Global Functions
 *****************************************************************************/
extern uint_8 PHD_Transport_Init(
    uint_8 controller_ID,
    PHD_CALLBACK phd_callback);
extern void PHD_Connect_to_Manager(uint_8 controller_ID);
extern void PHD_Disconnect_from_Manager(uint_8 controller_ID);
extern void PHD_Send_Measurements_to_Manager(uint_8 controller_ID);
extern void PHD_Send_Abort_to_Manager (
    uint_8 controller_ID,   
    uint_16 abort_reason);

#endif
