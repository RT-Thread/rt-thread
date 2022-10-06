/**
 * \file      mailbox.c
 *
 * \brief     This file contains the device abstraction layer APIs for the
 *            mailbox module. These are used for IPC communication.
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

#include "hw_types.h"
#include "mailbox.h"

/**************************************************************************
  API FUNCTION DEFINITIONS
***************************************************************************/

/**
 *  \brief   This function resets the mailbox
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \return 	  None
 */
 
void MBresetMailbox(unsigned int baseAdd)
{
	/*	Start the soft reset sequence	*/
	HWREG(baseAdd + MAILBOX_SYSCONFIG) = 
		(MAILBOX_SYSCONFIG_SOFTRESET_MANUAL << 
					MAILBOX_SYSCONFIG_SOFTRESET_SHIFT);
					
	/*	Wait till the reset is complete	*/
	while(HWREG(baseAdd + MAILBOX_SYSCONFIG) & 
	(MAILBOX_SYSCONFIG_SOFTRESET << MAILBOX_SYSCONFIG_SOFTRESET_SHIFT));
}


/**
 *  \brief   This function configures the idle mode of the mailbox
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     idleMode	Idle mode to be configured. Possible values are
 *						0x0: Force-idle. An idle request is acknowledged unconditionally
 *						0x1: No-idle. An idle request is never acknowledged
 *						0x2: Smart-idle. Acknowledgement to an idle request is given based 
 *						on the internal activity of the module
 * \return 	  None
 */
 
void MBconfigIdleMode(unsigned int baseAdd, unsigned int idleMode)
{
	/*	Configure idle mode	*/
	HWREG(baseAdd + MAILBOX_SYSCONFIG) = 
		(idleMode << MAILBOX_SYSCONFIG_SIDLEMODE_SHIFT);
}


/**
 *  \brief   This function gets the first message in the queue
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     queueId	Queue to be read
 * \param     *msgPtr	Message pointer in which the message will be returned
 *
 * \return 	  Validity	The return value indicates whether the message is valid
 */
 
unsigned int MBgetMessage(unsigned int baseAdd, unsigned int queueId, unsigned int *msgPtr)
{
	/*	Check if queue is not empty	*/
	if((HWREG(baseAdd + MAILBOX_MESSAGESTATUS(queueId)) & 
		(MAILBOX_MESSAGESTATUS_NBOFMSGMBM << 
			MAILBOX_MESSAGESTATUS_NBOFMSGMBM_SHIFT)) > 0)
	{
		/*	Read message	*/
		*msgPtr = HWREG(baseAdd + MAILBOX_MESSAGE(queueId));
		return MESSAGE_VALID;
	}
	else
	{
		/*	Queue empty*/
		return MESSAGE_INVALID;
	}
}


/**
 *  \brief   This function writes message in the queue
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     queueId	Queue to be written
 * \param     msg		Message which has to be sent
 *
 * \return 	  status	The return value indicates whether the message is 
 *			  			written to the queue. Possible values are,
 *							0	-	Written successfully
 *							0	-	Queue full
 */
 
unsigned int MBsendMessage(unsigned int baseAdd, unsigned int queueId, unsigned int msg)
{

	unsigned int fifoFullMask = (MAILBOX_FIFOSTATUS_FIFOFULLMBM << 
							MAILBOX_FIFOSTATUS_FIFOFULLMBM_SHIFT);

	/*	Check if queue is not full	*/
	if((HWREG(baseAdd + MAILBOX_FIFOSTATUS(queueId)) & fifoFullMask)  != fifoFullMask)
	{
		/*	Write message	*/
		HWREG(baseAdd + MAILBOX_MESSAGE(queueId)) = msg;
		return (!fifoFullMask);
	}
	else
	{	
		/*	Queue full	*/
		return (fifoFullMask);
	}
}


/**
 *  \brief   This function enables the new message interrupt for a user for given queue
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     userId	User for whom the new meaasge should be intimated
 * \param     queueId	Queue to be monitored for new message
 *
 * \return 	  None
 */
 
void MBenableNewMsgInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId)
{
	HWREG(baseAdd + MAILBOX_IRQENABLE_SET(userId)) = 
			(MAILBOX_IRQENABLE_SET_NEWMSGSTATUSUUMB(queueId) <<
				MAILBOX_IRQENABLE_SET_NEWMSGSTATUSUUMB_SHIFT(queueId));
}


/**
 *  \brief   This function enables the queue not full interrupt for a user for given queue
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     userId	User for whom the event should be intimated
 * \param     queueId	Queue to be monitored for non-full condition
 *
 * \return 	  None
 */
 
void MBenableQueueNotFullInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId)
{
	HWREG(baseAdd + MAILBOX_IRQENABLE_SET(userId)) = 
			(MAILBOX_IRQENABLE_SET_NOTFULLSTATUSUUMB(queueId) <<
				MAILBOX_IRQENABLE_SET_NOTFULLSTATUSUUMB_SHIFT(queueId));
}


/**
 *  \brief   This function disables the new message interrupt for a user for given queue
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     userId	User for whom the new meaasge event should be disabled
 * \param     queueId	Queue to be monitored for new message
 *
 * \return 	  None
 */
 
void MBdisableNewMsgInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId)
{
	HWREG(baseAdd + MAILBOX_IRQENABLE_CLR(userId)) = 
			(MAILBOX_IRQENABLE_CLR_NEWMSGSTATUSUUMB(queueId) <<
				MAILBOX_IRQENABLE_CLR_NEWMSGSTATUSUUMB_SHIFT(queueId));
}


/**
 *  \brief   This function disables the queue not full interrupt for a user for given queue
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     userId	User for whom the event should be disabled
 * \param     queueId	Queue for  which the non-full event to be disabled
 *
 * \return 	  None
 */
 
void MBdisableQueueNotFullInt(unsigned int baseAdd, unsigned int userId, unsigned int queueId)
{
	HWREG(baseAdd + MAILBOX_IRQENABLE_CLR(userId)) = 
			(MAILBOX_IRQENABLE_CLR_NOTFULLSTATUSUUMB(queueId) <<
				MAILBOX_IRQENABLE_CLR_NOTFULLSTATUSUUMB_SHIFT(queueId));
}

/**
 *  \brief   This function gets the new message status
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     userId	User for whom the event should be checked
 * \param     queueId	Queue for  which the event should be checked
 *
 * \return 	  status	status of new message
 */
 
unsigned int MBgetNewMsgStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId)
{
	return ((HWREG(baseAdd + MAILBOX_IRQSTATUS_CLR(userId)) & 
				MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSUUMB(queueId)) >>	
					MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSUUMB_SHIFT(queueId));
}


/**
 *  \brief   This function gets the queue not-full status
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     userId	User for whom the event should be checked
 * \param     queueId	Queue for  which the event should be checked
 *
 * \return 	  status	Queue not full status
 */
 
unsigned int MBgetQueueNotFullStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId)
{
	return ((HWREG(baseAdd + MAILBOX_IRQSTATUS_CLR(userId)) & 
				MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSUUMB(queueId)) >>	
					MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSUUMB_SHIFT(queueId));
}


/**
 *  \brief   This function clears the queue not-full status
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     userId	User for whom the event should be cleared
 * \param     queueId	Queue for  which the event should be cleared
 *
 * \return 	  None
 */
 
void MBclrNewMsgStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId)
{
	HWREG(baseAdd + MAILBOX_IRQSTATUS_CLR(userId)) = 
							(MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSUUMB(queueId) <<
								MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSUUMB_SHIFT(queueId));
}


/**
 *  \brief   This function clears the queue not-full status
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     userId	User for whom the event should be cleared
 * \param     queueId	Queue for  which the event should be cleared
 *
 * \return 	  None
 */
 
void MBclrQueueNotFullStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId)
{
	HWREG(baseAdd + MAILBOX_IRQSTATUS_CLR(userId)) = 
							(MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSUUMB(queueId) <<
								MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSUUMB_SHIFT(queueId));
}


/**
 *  \brief   This function gets the raw new message status
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     userId	User for whom the event should be checked
 * \param     queueId	Queue for  which the event should be checked
 *
 * \return 	  status	status of new message
 */
 
unsigned int MBgetRawNewMsgStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId)
{
	return ((HWREG(baseAdd + MAILBOX_IRQSTATUS_CLR(userId)) & 
				MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSUUMB(queueId)) >>	
					MAILBOX_IRQSTATUS_CLR_NEWMSGSTATUSUUMB_SHIFT(queueId));
}


/**
 *  \brief   This function gets the raw queue not-full status
 *
 * \param     baseAdd	Memory address of the mailbox instance used.
 * \param     userId	User for whom the event should be checked
 * \param     queueId	Queue for  which the event should be checked
 *
 * \return 	  status	Queue not full status
 */
 
unsigned int MBgetRawQueueNotFullStatus(unsigned int baseAdd, unsigned int userId, unsigned int queueId)
{
	return ((HWREG(baseAdd + MAILBOX_IRQSTATUS_CLR(userId)) & 
				MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSUUMB(queueId)) >>	
					MAILBOX_IRQSTATUS_CLR_NOTFULLSTATUSUUMB_SHIFT(queueId));
}
