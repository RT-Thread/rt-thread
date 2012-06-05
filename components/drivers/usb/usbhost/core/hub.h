/*
 * File      : hub.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-12     Yi Qiu      first version
 */

#ifndef __HUB_H__
#define __HUB_H__

#include <rtthread.h>

typedef struct uhubinst* uhubinst_t;
struct uhubinst
{
	struct uhub_descriptor hub_desc;
	rt_uint8_t num_ports;
	rt_uint32_t port_status[PORT_NUM];
	struct uinstance* child[PORT_NUM];		

	rt_bool_t is_roothub;
	upipe_t pipe_in;
	rt_uint8_t buffer[8];	
	struct uinstance* self;
	struct uhcd *hcd;	
};	

#define RH_GET_PORT_STATUS			0
#define RH_SET_PORT_STATUS			1
#define RH_CLEAR_PORT_FEATURE		2
#define RH_SET_PORT_FEATURE			3

/*
 * Port feature numbers
 */
#define PORT_FEAT_CONNECTION		0
#define PORT_FEAT_ENABLE			1
#define PORT_FEAT_SUSPEND			2
#define PORT_FEAT_OVER_CURRENT		3
#define PORT_FEAT_RESET				4
#define PORT_FEAT_POWER				8
#define PORT_FEAT_LOWSPEED			9
#define PORT_FEAT_HIGHSPEED			10
#define PORT_FEAT_C_CONNECTION		16
#define PORT_FEAT_C_ENABLE			17
#define PORT_FEAT_C_SUSPEND			18
#define PORT_FEAT_C_OVER_CURRENT	19
#define PORT_FEAT_C_RESET			20

/*
	The HcRhPortStatus[1:NDP] register is used to control and report port events on a per-port
	basis. NumberDownstreamPorts represents the number of HcRhPortStatus registers that are
	implemented in hardware.  The lower word is used to reflect the port status, whereas the upper
	word reflects the status change bits.  Some status bits are implemented with special write behavior
	(see below).  If a transaction (token through handshake) is in progress when a write to change
	port status occurs, the resulting port status change must be postponed until the transaction
	completes.  Reserved bits should always be written '0'.
*/
#define PORT_CCS    			0x00000001UL	/* R:CurrentConnectStatus - W:ClearPortEnable	*/
#define PORT_PES        		0x00000002UL	/* R:PortEnableStatus - W:SetPortEnable 			*/
#define PORT_PSS       			0x00000004UL	/* R:PortSuspendStatus - W:SetPortSuspend		*/
#define PORT_POCI   			0x00000008UL	/* R:PortOverCurrentIndicator - W:ClearSuspendStatus	*/
#define PORT_PRS         		0x00000010UL	/* R:PortResetStatus - W: SetPortReset			*/
#define PORT_PPS         		0x00000100UL	/* R:PortPowerStatus - W: SetPortPower			*/
#define PORT_LSDA     			0x00000200UL	/* R:LowSpeedDeviceAttached - W:ClearPortPower	*/
#define PORT_CCSC				0x00010000UL
#define PORT_PESC				0x00020000UL
#define PORT_PSSC				0x00040000UL
#define PORT_POCIC				0x00080000UL
#define PORT_PRSC				0x00100000UL

/*
 *Hub Status & Hub Change bit masks
 */
#define HUB_STATUS_LOCAL_POWER		0x0001
#define HUB_STATUS_OVERCURRENT		0x0002

#define HUB_CHANGE_LOCAL_POWER		0x0001
#define HUB_CHANGE_OVERCURRENT		0x0002

rt_err_t rt_usb_hub_get_descriptor(uinst_t uinst, rt_uint8_t *buffer, 
	rt_size_t size);
rt_err_t rt_usb_hub_get_status(uinst_t uinst, rt_uint8_t* buffer);
rt_err_t rt_usb_hub_get_port_status(uhubinst_t uhub, rt_uint16_t port, 
	rt_uint8_t* buffer);
rt_err_t rt_usb_hub_clear_port_feature(uhubinst_t uhub, rt_uint16_t port, 
	rt_uint16_t feature);
rt_err_t rt_usb_hub_set_port_feature(uhubinst_t uhub, rt_uint16_t port, 
	rt_uint16_t feature);
rt_err_t rt_usb_hub_reset_port(uhubinst_t uhub, rt_uint16_t port);
rt_err_t rt_usb_post_event(struct umsg* msg, rt_size_t size);

#endif

