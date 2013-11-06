/*
 * app_task.c
 *
 *  Created on: 2013-11-06
 *      Author: Armink
 *  
 *  Note:This file is test modbus master and slave.Before you use it.
 *       1.You must have an complete project for RT-Thread.
 *       2.And add "rt-thread/examples/kernel/cpuusage.c" to your project.
 *       3.Then initalize and start the thread which in this file.
 *       4.Next you can use "modbus poll" or "modbus slave" to observe result.
 */

#include "app_task.h"

uint8_t CpuUsageMajor, CpuUsageMinor; //CPU usage
USHORT  usModbusUserData[MB_PDU_SIZE_MAX];
UCHAR   ucModbusUserData[MB_PDU_SIZE_MAX];
/* thread priority */
#define thread_SysMonitor_Prio		    	11
#define thread_ModbusSlavePoll_Prio      	10
#define thread_ModbusMasterPoll_Prio      	 9
ALIGN(RT_ALIGN_SIZE)
/* thread stack */
static rt_uint8_t thread_SysMonitor_stack[256];
static rt_uint8_t thread_ModbusSlavePoll_stack[512];
static rt_uint8_t thread_ModbusMasterPoll_stack[512];
/* all thread */
struct rt_thread thread_SysMonitor;
struct rt_thread thread_ModbusSlavePoll;
struct rt_thread thread_ModbusMasterPoll;

/** system monitor thread,send modbus master request */
void thread_entry_SysMonitor(void* parameter)
{
	while (1)
	{
		cpu_usage_get(&CpuUsageMajor, &CpuUsageMinor);
		usSRegHoldBuf[S_HD_CPU_USAGE_MAJOR] = CpuUsageMajor;
		usSRegHoldBuf[S_HD_CPU_USAGE_MINOR] = CpuUsageMinor;
		usModbusUserData[0] = (USHORT)(rt_tick_get()/10);
		usModbusUserData[1] = (USHORT)(rt_tick_get()%10);
		/* you can open a comment to test modbus master request Note:master busy process */
		eMBMasterReqReadDiscreteInputs(1,3,8);
//		eMBMasterReqWriteMultipleCoils(1,3,5,ucModbusUserData);
//		eMBMasterReqWriteCoil(1,8,0xFF00);
//		eMBMasterReqReadCoils(1,3,8);
//		eMBMasterReqReadInputRegister(1,3,2);
//		eMBMasterReqWriteHoldingRegister(1,3,usModbusUserData[0]);
//		eMBMasterReqWriteMultipleHoldingRegister(1,3,2,usModbusUserData);
//		eMBMasterReqReadHoldingRegister(1,3,2);
//		eMBMasterReqReadWriteMultipleHoldingRegister(1,3,2,usModbusUserData,5,2);

		rt_thread_delay(DELAY_SYS_MONITOR);
	}
}

/* modbus slave poll thread */
void thread_entry_ModbusSlavePoll(void* parameter)
{
	eMBInit(MB_RTU, 0x01, 1, 115200,  MB_PAR_EVEN);
	eMBEnable();
	while (1)
	{
		eMBPoll();
		rt_thread_delay(DELAY_MB_SLAVE_POLL);
	}
}
/* modbus master poll thread */
void thread_entry_ModbusMasterPoll(void* parameter)
{
	eMBMasterInit(MB_RTU, 2, 115200,  MB_PAR_EVEN);
	eMBMasterEnable();
	while (1)
	{
		eMBMasterPoll();
		rt_thread_delay(DELAY_MB_MASTER_POLL);
	}
}



