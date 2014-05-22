#include "user_mb_app.h"
/*------------------------Slave mode use these variables----------------------*/
//Slave mode:DiscreteInputs variables
USHORT   usSDiscInStart                               = S_DISCRETE_INPUT_START;
#if S_DISCRETE_INPUT_NDISCRETES%8
UCHAR    ucSDiscInBuf[S_DISCRETE_INPUT_NDISCRETES/8+1];
#else
UCHAR    ucSDiscInBuf[S_DISCRETE_INPUT_NDISCRETES/8]  ;
#endif
//Slave mode:Coils variables
USHORT   usSCoilStart                                 = S_COIL_START;
#if S_COIL_NCOILS%8
UCHAR    ucSCoilBuf[S_COIL_NCOILS/8+1]                ;
#else
UCHAR    ucSCoilBuf[S_COIL_NCOILS/8]                  ;
#endif
//Slave mode:InputRegister variables
USHORT   usSRegInStart                                = S_REG_INPUT_START;
USHORT   usSRegInBuf[S_REG_INPUT_NREGS]               ;
//Slave mode:HoldingRegister variables
USHORT   usSRegHoldStart                              = S_REG_HOLDING_START;
USHORT   usSRegHoldBuf[S_REG_HOLDING_NREGS]           ;
/*-----------------------Master mode use these variables----------------------*/
#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0
//Master mode:DiscreteInputs variables
USHORT   usMDiscInStart                             = M_DISCRETE_INPUT_START;
#if      M_DISCRETE_INPUT_NDISCRETES%8
UCHAR    ucMDiscInBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_DISCRETE_INPUT_NDISCRETES/8+1];
#else
UCHAR    ucMDiscInBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_DISCRETE_INPUT_NDISCRETES/8];
#endif
//Master mode:Coils variables
USHORT   usMCoilStart                               = M_COIL_START;
#if      M_COIL_NCOILS%8
UCHAR    ucMCoilBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_COIL_NCOILS/8+1];
#else
UCHAR    ucMCoilBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_COIL_NCOILS/8];
#endif
//Master mode:InputRegister variables
USHORT   usMRegInStart                              = M_REG_INPUT_START;
USHORT   usMRegInBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_REG_INPUT_NREGS];
//Master mode:HoldingRegister variables
USHORT   usMRegHoldStart                            = M_REG_HOLDING_START;
USHORT   usMRegHoldBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_REG_HOLDING_NREGS];
#endif
//******************************����Ĵ����ص�����**********************************
//��������: eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
//��    ��������Ĵ�����صĹ��ܣ�������������
//��ڲ�����pucRegBuffer : �ص�������Modbus�Ĵ����ĵ�ǰֵд��Ļ�����
//			usAddress    : �Ĵ�������ʼ��ַ������Ĵ����ĵ�ַ��Χ��1-65535��
//			usNRegs      : �Ĵ�������
//���ڲ�����eMBErrorCode : ������������صĴ�����
//��    ע��Editor��Armink 2010-10-31    Company: BXXJS
//**********************************************************************************
eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;
    USHORT *        pusRegInputBuf;
    UCHAR           REG_INPUT_START;
    UCHAR           REG_INPUT_NREGS;
    USHORT           usRegInStart;

    //Determine the master or slave
    if (xMBMasterGetCBRunInMasterMode())
    {
    	pusRegInputBuf = usMRegInBuf[ucMBMasterGetDestAddress()];
    	REG_INPUT_START = M_REG_INPUT_START;
    	REG_INPUT_NREGS = M_REG_INPUT_NREGS;
    	usRegInStart = usMRegInStart;
    }
    else
    {
    	pusRegInputBuf = usSRegInBuf;
    	REG_INPUT_START = S_REG_INPUT_START;
    	REG_INPUT_NREGS = S_REG_INPUT_NREGS;
    	usRegInStart = usSRegInStart;
    }

    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegInStart );
        while( usNRegs > 0 )
        {
            //Determine the master or slave
            if (xMBMasterGetCBRunInMasterMode())
            {
            	pusRegInputBuf[iRegIndex] = *pucRegBuffer++ << 8;
                pusRegInputBuf[iRegIndex] |= *pucRegBuffer++;
            }
            else
            {
				*pucRegBuffer++ = ( unsigned char )( pusRegInputBuf[iRegIndex] >> 8 );
				*pucRegBuffer++ = ( unsigned char )( pusRegInputBuf[iRegIndex] & 0xFF );
            }
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}
//******************************���ּĴ����ص�����**********************************
//��������: eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
//��    �������ּĴ�����صĹ��ܣ�������������д������д��
//��ڲ�����pucRegBuffer : �����Ҫ�����û��Ĵ�����ֵ���������������ָ���µļĴ�����ֵ��
//                         ���Э��ջ��֪����ǰ����ֵ���ص��������뽫��ǰֵд�����������
//			usAddress    : �Ĵ�������ʼ��ַ��
//			usNRegs      : �Ĵ�������
//          eMode        : ����ò���ΪeMBRegisterMode::MB_REG_WRITE���û���Ӧ����ֵ����pucRegBuffer�еõ����¡�
//                         ����ò���ΪeMBRegisterMode::MB_REG_READ���û���Ҫ����ǰ��Ӧ�����ݴ洢��pucRegBuffer��
//���ڲ�����eMBErrorCode : ������������صĴ�����
//��    ע��Editor��Armink 2010-10-31    Company: BXXJS
//**********************************************************************************
eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;
    USHORT *        pusRegHoldingBuf;
    UCHAR           REG_HOLDING_START;
    UCHAR           REG_HOLDING_NREGS;
    USHORT           usRegHoldStart;

    //Determine the master or slave
    if (xMBMasterGetCBRunInMasterMode())
    {
    	pusRegHoldingBuf = usMRegHoldBuf[ucMBMasterGetDestAddress()];
    	REG_HOLDING_START = M_REG_HOLDING_START;
    	REG_HOLDING_NREGS = M_REG_HOLDING_NREGS;
    	usRegHoldStart = usMRegHoldStart;
    	//If mode is read,the master will wirte the received date to bufffer.
    	eMode = MB_REG_WRITE;
    }
    else
    {
    	pusRegHoldingBuf = usSRegHoldBuf;
    	REG_HOLDING_START = S_REG_HOLDING_START;
    	REG_HOLDING_NREGS = S_REG_HOLDING_NREGS;
    	usRegHoldStart = usSRegHoldStart;
    }

    if( ( usAddress >= REG_HOLDING_START ) &&
        ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - usRegHoldStart );
        switch ( eMode )
        {
            /* Pass current register values to the protocol stack. */
        case MB_REG_READ:
            while( usNRegs > 0 )
            {
				*pucRegBuffer++ = ( unsigned char )( pusRegHoldingBuf[iRegIndex] >> 8 );
				*pucRegBuffer++ = ( unsigned char )( pusRegHoldingBuf[iRegIndex] & 0xFF );
                iRegIndex++;
                usNRegs--;
            }
            break;

            /* Update current register values with new values from the
             * protocol stack. */
        case MB_REG_WRITE:
            while( usNRegs > 0 )
            {
                pusRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                pusRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
                iRegIndex++;
                usNRegs--;
            }
            break;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}
//****************************��Ȧ״̬�Ĵ����ص�����********************************
//��������: eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
//��    ������Ȧ״̬�Ĵ�����صĹ��ܣ�������������д������д��
//��ڲ�����pucRegBuffer : λ���һ���ֽڣ���ʼ�Ĵ�����Ӧ��λ���ڸ��ֽ�pucRegBuffer�����λLSB��
//                         ����ص�����Ҫд�����������û���õ�����Ȧ�����粻��8��һ�����Ȧ״̬����Ӧ��λ����ֵ��������λ0��
//			usAddress    : ��һ����Ȧ��ַ��
//			usNCoils     : �������Ȧ����
//          eMode        ������ò���ΪeMBRegisterMode::MB_REG_WRITE���û���Ӧ����ֵ����pucRegBuffer�еõ����¡�
//                         ����ò���ΪeMBRegisterMode::MB_REG_READ���û���Ҫ����ǰ��Ӧ�����ݴ洢��pucRegBuffer��
//���ڲ�����eMBErrorCode : ������������صĴ�����
//��    ע��Editor��Armink 2010-10-31    Company: BXXJS
//**********************************************************************************
eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex , iRegBitIndex , iNReg;
	UCHAR *         pucCoilBuf;
    USHORT           COIL_START;
    UCHAR           COIL_NCOILS;
    USHORT           usCoilStart;
    iNReg =  usNCoils / 8 + 1;        //ռ�üĴ�������


    //Determine the master or slave
    if (xMBMasterGetCBRunInMasterMode())
    {
    	pucCoilBuf = ucMCoilBuf[ucMBMasterGetDestAddress()];
    	COIL_START = M_COIL_START;
    	COIL_NCOILS = M_COIL_NCOILS;
    	usCoilStart = usMCoilStart;
    	//If mode is read,the master will wirte the received date to bufffer.
    	eMode = MB_REG_WRITE;
    }
    else
    {
    	pucCoilBuf = ucSCoilBuf;
    	COIL_START = S_COIL_START;
    	COIL_NCOILS = S_COIL_NCOILS;
    	usCoilStart = usSCoilStart;
    }

    if( ( usAddress >= COIL_START ) &&
        ( usAddress + usNCoils <= COIL_START + COIL_NCOILS ) )
    {
        iRegIndex    = ( int )( usAddress - usCoilStart ) / 8 ;    //ÿ���Ĵ�����8��
		iRegBitIndex = ( int )( usAddress - usCoilStart ) % 8 ;	   //����ڼĴ����ڲ���λ��ַ
        switch ( eMode )
        {
            /* Pass current coil values to the protocol stack. */
        case MB_REG_READ:
            while( iNReg > 0 )
            {
				*pucRegBuffer++ = xMBUtilGetBits(&pucCoilBuf[iRegIndex++] , iRegBitIndex , 8);
                iNReg --;
            }
			pucRegBuffer --;
			usNCoils = usNCoils % 8;                        //���µ���Ȧ��	
			*pucRegBuffer = *pucRegBuffer <<(8 - usNCoils); //��λ����
			*pucRegBuffer = *pucRegBuffer >>(8 - usNCoils);
            break;

            /* Update current coil values with new values from the
             * protocol stack. */
        case MB_REG_WRITE:
            while(iNReg > 1)									 //���������������������
            {
				xMBUtilSetBits(&pucCoilBuf[iRegIndex++] , iRegBitIndex  , 8 , *pucRegBuffer++);
                iNReg--;
            }
			usNCoils = usNCoils % 8;                            //���µ���Ȧ��
			if (usNCoils != 0)                                  //xMBUtilSetBits���� �ڲ���λ����Ϊ0ʱ����bug
			{
				xMBUtilSetBits(&pucCoilBuf[iRegIndex++], iRegBitIndex, usNCoils,
						*pucRegBuffer++);
			}
			break;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}
//****************************��ɢ����Ĵ����ص�����********************************
//��������: eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
//��    ������ɢ����Ĵ�����صĹ��ܣ�������������
//��ڲ�����pucRegBuffer : �õ�ǰ����Ȧ���ݸ�������Ĵ�������ʼ�Ĵ�����Ӧ��λ���ڸ��ֽ�pucRegBuffer�����λLSB��
//                         ����ص�����Ҫд�����������û���õ�����Ȧ�����粻��8��һ�����Ȧ״̬����Ӧ��λ����ֵ��������Ϊ0��
//			usAddress    : ��ɢ�������ʼ��ַ
//			usNDiscrete  : ��ɢ���������
//���ڲ�����eMBErrorCode : ������������صĴ�����
//��    ע��Editor��Armink 2010-10-31    Company: BXXJS
//**********************************************************************************
eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    eMBErrorCode    eStatus = MB_ENOERR;
	int             iRegIndex , iRegBitIndex , iNReg;
	UCHAR *         pucDiscreteInputBuf;
    USHORT           DISCRETE_INPUT_START;
    UCHAR           DISCRETE_INPUT_NDISCRETES;
    USHORT           usDiscreteInputStart;
	iNReg =  usNDiscrete / 8 + 1;        //ռ�üĴ�������

    //Determine the master or slave
    if (xMBMasterGetCBRunInMasterMode())
    {
    	pucDiscreteInputBuf = ucMDiscInBuf[ucMBMasterGetDestAddress()];
    	DISCRETE_INPUT_START = M_DISCRETE_INPUT_START;
    	DISCRETE_INPUT_NDISCRETES = M_DISCRETE_INPUT_NDISCRETES;
    	usDiscreteInputStart = usMDiscInStart;
    }
    else
    {
    	pucDiscreteInputBuf = ucSDiscInBuf;
    	DISCRETE_INPUT_START = S_DISCRETE_INPUT_START;
    	DISCRETE_INPUT_NDISCRETES = S_DISCRETE_INPUT_NDISCRETES;
    	usDiscreteInputStart = usSDiscInStart;
    }

    if( ( usAddress >= DISCRETE_INPUT_START )
        && ( usAddress + usNDiscrete <= DISCRETE_INPUT_START + DISCRETE_INPUT_NDISCRETES ) )
    {
        iRegIndex    = ( int )( usAddress - usDiscreteInputStart ) / 8 ;    //ÿ���Ĵ�����8��
		iRegBitIndex = ( int )( usAddress - usDiscreteInputStart ) % 8 ;	   //����ڼĴ����ڲ���λ��ַ

	    //Determine the master or slave
	    if (xMBMasterGetCBRunInMasterMode())
	    {
			/* Update current coil values with new values from the
			 * protocol stack. */
			while(iNReg > 1)									 //���������������������
			{
				xMBUtilSetBits(&pucDiscreteInputBuf[iRegIndex++] , iRegBitIndex  , 8 , *pucRegBuffer++);
				iNReg--;
			}
			usNDiscrete = usNDiscrete % 8;                        //���µ���Ȧ��
			if (usNDiscrete != 0)                                 //xMBUtilSetBits���� �ڲ���λ����Ϊ0ʱ����bug
			{
				xMBUtilSetBits(&pucDiscreteInputBuf[iRegIndex++], iRegBitIndex,
						usNDiscrete, *pucRegBuffer++);
			}
	    }
	    else
	    {
			while( iNReg > 0 )
			{
				*pucRegBuffer++ = xMBUtilGetBits(&pucDiscreteInputBuf[iRegIndex++] , iRegBitIndex , 8);
				iNReg --;
			}
			pucRegBuffer --;
			usNDiscrete = usNDiscrete % 8;                     //���µ���Ȧ��
			*pucRegBuffer = *pucRegBuffer <<(8 - usNDiscrete); //��λ����
			*pucRegBuffer = *pucRegBuffer >>(8 - usNDiscrete);
	    }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}
