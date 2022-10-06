
/**
 * \file     mailbox.h
 *
 * \brief    This file contains the function prototypes for Mail box access
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
 
#ifndef      __MAIL_BOX_H__
#define      __MAIL_BOX_H__

#include "hw_control_AM335x.h"
#include "hw_mailbox.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************** MACROS ***************************/

/*	User Id's	*/
#define MAILBOX_USER_A8 		0
#define MAILBOX_USER_PRU0 		1
#define MAILBOX_USER_PRU1 		2
#define MAILBOX_USER_CM3WKUP 	3

/*	Mailbox Queue's	*/
#define	MAILBOX_QUEUE_0			0
#define	MAILBOX_QUEUE_1			1
#define	MAILBOX_QUEUE_2			2
#define	MAILBOX_QUEUE_3			3
#define	MAILBOX_QUEUE_4			4
#define	MAILBOX_QUEUE_5			5
#define	MAILBOX_QUEUE_6			6
#define	MAILBOX_QUEUE_7			7
	
#define MESSAGE_VALID			0
#define MESSAGE_INVALID			1


/*****************************************************************************
**                   FUNCTION DECLARATIONS                                   
*****************************************************************************/

/*	Queue Access API's	*/

void MBresetMailbox(unsigned int baseAdd);

void MBconfigIdleMode(unsigned int baseAdd, unsigned int idleMode);

unsigned int MBgetMessage(unsigned int baseAdd, unsigned int queueId, unsigned int *msgPtr);

unsigned int MBsendMessage(unsigned int baseAdd, unsigned int queueId, unsigned int msg);


/*	Mailbox user(hw using mailbox) access API's	*/
void MBenableNewMsgInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId);
void MBenableQueueNotFullInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId);

void MBdisableNewMsgInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId);
void MBdisableQueueNotFullInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId);

unsigned int MBgetNewMsgStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);
unsigned int MBgetQueueNotFullStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);

void MBclrNewMsgStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);
void MBclrQueueNotFullStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);

unsigned int MBgetRawNewMsgStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);
unsigned int MBgetRawQueueNotFullStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId);


#ifdef __cplusplus
}
#endif

#endif

