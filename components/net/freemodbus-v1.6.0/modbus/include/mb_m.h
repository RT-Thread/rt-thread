/* 
 * FreeModbus Libary: A portable Modbus implementation for Modbus ASCII/RTU.
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * File: $Id: mb_m.h,v 1.60 2013/09/03 10:20:05 Armink Add Master Functions $
 */

#ifndef _MB_M_H
#define _MB_M_H

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif

/*! \defgroup modbus Modbus
 * \code #include "mb_m.h" \endcode
 *
 * This module defines the interface for the application. It contains
 * the basic functions and types required to use the Modbus Master protocol stack.
 * A typical application will want to call eMBMasterInit() first. If the device
 * is ready to answer network requests it must then call eMBEnable() to activate
 * the protocol stack. In the main loop the function eMBMasterPoll() must be called
 * periodically. The time interval between pooling depends on the configured
 * Modbus timeout. If an RTOS is available a separate task should be created
 * and the task should always call the function eMBMasterPoll().
 *
 * \code
 * // Initialize protocol stack in RTU mode for a Master
 * eMBMasterInit( MB_RTU, 38400, MB_PAR_EVEN );
 * // Enable the Modbus Protocol Stack.
 * eMBMasterEnable(  );
 * for( ;; )
 * {
 *     // Call the main polling loop of the Modbus Master protocol stack.
 *     eMBMasterPoll(  );
 *     ...
 * }
 * \endcode
 */

/* ----------------------- Defines ------------------------------------------*/

/*! \ingroup modbus
 * \brief Use the default Modbus Master TCP port (502)
 */
#define MB_MASTER_TCP_PORT_USE_DEFAULT 0

/* ----------------------- Type definitions ---------------------------------*/
/*! \ingroup modbus
 * \brief Errorcodes used by all function in the Master request.
 */
typedef enum
{
    MB_MRE_NO_ERR,                  /*!< no error. */
    MB_MRE_NO_REG,                  /*!< illegal register address. */
    MB_MRE_ILL_ARG,                 /*!< illegal argument. */
    MB_MRE_PORT_ERR,                /*!< porting layer error. */
    MB_MRE_NO_RES,                  /*!< insufficient resources. */
    MB_MRE_IO,                      /*!< I/O error. */
    MB_MRE_ILL_STATE,               /*!< protocol stack in illegal state. */
    MB_MRE_TIMEDOUT,                /*!< timeout error occurred. */
    MB_MRE_MASTER_BUSY,             /*!< master is busy now. */
    MB_MRE_SLAVE_EXCE               /*!< slave has exception. */
} eMBMasterReqErrCode;
/*! \ingroup modbus
 *  \brief TimerMode is Master 3 kind of Timer modes.
 */
typedef enum
{
	MB_TMODE_T35,                   /*!< Master receive frame T3.5 timeout. */
	MB_TMODE_RESPOND_TIMEOUT,       /*!< Master wait respond for slave. */
	MB_TMODE_CONVERT_DELAY          /*!< Master sent broadcast ,then delay sometime.*/
}eMBMasterTimerMode;

/* ----------------------- Function prototypes ------------------------------*/
/*! \ingroup modbus
 * \brief Initialize the Modbus Master protocol stack.
 *
 * This functions initializes the ASCII or RTU module and calls the
 * init functions of the porting layer to prepare the hardware. Please
 * note that the receiver is still disabled and no Modbus frames are
 * processed until eMBMasterEnable( ) has been called.
 *
 * \param eMode If ASCII or RTU mode should be used.
 * \param ucPort The port to use. E.g. 1 for COM1 on windows. This value
 *   is platform dependent and some ports simply choose to ignore it.
 * \param ulBaudRate The baudrate. E.g. 19200. Supported baudrates depend
 *   on the porting layer.
 * \param eParity Parity used for serial transmission.
 *
 * \return If no error occurs the function returns eMBErrorCode::MB_ENOERR.
 *   The protocol is then in the disabled state and ready for activation
 *   by calling eMBMasterEnable( ). Otherwise one of the following error codes
 *   is returned:
 *    - eMBErrorCode::MB_EPORTERR IF the porting layer returned an error.
 */
eMBErrorCode    eMBMasterInit( eMBMode eMode, UCHAR ucPort,
		                 ULONG ulBaudRate, eMBParity eParity );

/*! \ingroup modbus
 * \brief Initialize the Modbus Master protocol stack for Modbus TCP.
 *
 * This function initializes the Modbus TCP Module. Please note that
 * frame processing is still disabled until eMBEnable( ) is called.
 *
 * \param usTCPPort The TCP port to listen on.
 * \return If the protocol stack has been initialized correctly the function
 *   returns eMBErrorCode::MB_ENOERR. Otherwise one of the following error
 *   codes is returned:
 *    - eMBErrorCode::MB_EINVAL If the slave address was not valid. Valid
 *        slave addresses are in the range 1 - 247.
 *    - eMBErrorCode::MB_EPORTERR IF the porting layer returned an error.
 */
eMBErrorCode    eMBMasterTCPInit( USHORT usTCPPort );

/*! \ingroup modbus
 * \brief Release resources used by the protocol stack.
 *
 * This function disables the Modbus Master protocol stack and release all
 * hardware resources. It must only be called when the protocol stack 
 * is disabled. 
 *
 * \note Note all ports implement this function. A port which wants to 
 *   get an callback must define the macro MB_PORT_HAS_CLOSE to 1.
 *
 * \return If the resources where released it return eMBErrorCode::MB_ENOERR.
 *   If the protocol stack is not in the disabled state it returns
 *   eMBErrorCode::MB_EILLSTATE.
 */
eMBErrorCode    eMBMasterClose( void );

/*! \ingroup modbus
 * \brief Enable the Modbus Master protocol stack.
 *
 * This function enables processing of Modbus Master frames. Enabling the protocol
 * stack is only possible if it is in the disabled state.
 *
 * \return If the protocol stack is now in the state enabled it returns 
 *   eMBErrorCode::MB_ENOERR. If it was not in the disabled state it 
 *   return eMBErrorCode::MB_EILLSTATE.
 */
eMBErrorCode    eMBMasterEnable( void );

/*! \ingroup modbus
 * \brief Disable the Modbus Master protocol stack.
 *
 * This function disables processing of Modbus frames.
 *
 * \return If the protocol stack has been disabled it returns 
 *  eMBErrorCode::MB_ENOERR. If it was not in the enabled state it returns
 *  eMBErrorCode::MB_EILLSTATE.
 */
eMBErrorCode    eMBMasterDisable( void );

/*! \ingroup modbus
 * \brief The main pooling loop of the Modbus Master protocol stack.
 *
 * This function must be called periodically. The timer interval required
 * is given by the application dependent Modbus slave timeout. Internally the
 * function calls xMBMasterPortEventGet() and waits for an event from the receiver or
 * transmitter state machines. 
 *
 * \return If the protocol stack is not in the enabled state the function
 *   returns eMBErrorCode::MB_EILLSTATE. Otherwise it returns 
 *   eMBErrorCode::MB_ENOERR.
 */
eMBErrorCode    eMBMasterPoll( void );


/*! \ingroup modbus
 *\brief These Modbus functions are called for user when Modbus run in Master Mode.
 */
eMBMasterReqErrCode
eMBMasterReqReadInputRegister( UCHAR ucSndAddr, USHORT usRegAddr, USHORT usNRegs );
eMBMasterReqErrCode
eMBMasterReqWriteHoldingRegister( UCHAR ucSndAddr, USHORT usRegAddr, USHORT usRegData );
eMBMasterReqErrCode
eMBMasterReqWriteMultipleHoldingRegister( UCHAR ucSndAddr, USHORT usRegAddr, USHORT usNRegs, USHORT * pusDataBuffer );
eMBMasterReqErrCode
eMBMasterReqReadHoldingRegister( UCHAR ucSndAddr, USHORT usRegAddr, USHORT usNRegs );
eMBMasterReqErrCode
eMBMasterReqReadWriteMultipleHoldingRegister( UCHAR ucSndAddr,
		USHORT usReadRegAddr, USHORT usNReadRegs, USHORT * pusDataBuffer,
		USHORT usWriteRegAddr, USHORT usNWriteRegs );
eMBMasterReqErrCode
eMBMasterReqReadCoils( UCHAR ucSndAddr, USHORT usCoilAddr, USHORT usNCoils );
eMBMasterReqErrCode
eMBMasterReqWriteCoil( UCHAR ucSndAddr, USHORT usCoilAddr, USHORT usCoilData );
eMBMasterReqErrCode
eMBMasterReqWriteMultipleCoils( UCHAR ucSndAddr,
		USHORT usCoilAddr, USHORT usNCoils, UCHAR * pucDataBuffer );
eMBMasterReqErrCode
eMBMasterReqReadDiscreteInputs( UCHAR ucSndAddr, USHORT usDiscreteAddr, USHORT usNDiscreteIn );

eMBException
eMBMasterFuncReportSlaveID( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncReadInputRegister( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncReadHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncWriteHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncReadCoils( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncWriteCoil( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncWriteMultipleCoils( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncReadDiscreteInputs( UCHAR * pucFrame, USHORT * usLen );
eMBException
eMBMasterFuncReadWriteMultipleHoldingRegister( UCHAR * pucFrame, USHORT * usLen );

/*£¡ \ingroup modbus
 *\brief These functions are interface for Modbus Master
 */
BOOL xMBMasterGetIsBusy( void );
void vMBMasterGetPDUSndBuf( UCHAR ** pucFrame );
UCHAR ucMBMasterGetDestAddress( void );
void vMBMasterSetDestAddress( UCHAR Address );
void vMBMasterSetIsBusy( BOOL IsBusy );
BOOL xMBMasterGetCBRunInMasterMode( void );
void vMBMasterSetCBRunInMasterMode( BOOL IsMasterMode );
UCHAR ucMBMasterGetPDUSndLength( void );
void vMBMasterSetPDUSndLength( UCHAR SendPDULength );
void vMBMasterSetCurTimerMode( eMBMasterTimerMode eMBTimerMode );

/* ----------------------- Callback -----------------------------------------*/

#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif
