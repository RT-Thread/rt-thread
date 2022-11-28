/*
********************************************************************************
*                                USB Hid Driver
*
*                (c) Copyright 2006-2010, All winners Co,Ld.
*                        All Right Reserved
*
* FileName      :  HidProtocol.h
*
* Author        :  Javen
*
* Date          :  2010/06/02
*
* Description   :  Hid Ð­Òé
*
* Others        :  NULL
*
* History:
*       <time>          <author>     <version >     <desc>
*      2010.06.02       Javen           1.0         build this file
*
********************************************************************************
*/
#ifndef  __HIDPROTOCOL_H__
#define  __HIDPROTOCOL_H__

//----------------------------------------------------------------------
//
//
//----------------------------------------------------------------------
int HidGetClassDescriptor(HidDev_t *HidDev,
                             unsigned int InterfaceNo,
                             unsigned int DescriptorType,
                             void *Buffer,
                             unsigned int TransferLength);
int HidGetIdle(HidDev_t *HidDev,
                 unsigned int InterfaceNo,
                 unsigned int ReportId,
                 void *IdleRate);
int HidSetIlde(HidDev_t *HidDev,
                 unsigned int InterfaceNo,
                 unsigned int Duration,
                 unsigned int ReportId);
int HidGetReport(HidDev_t *HidDev,
                   unsigned int InterfaceNo,
                   unsigned int ReportType,
                   unsigned int ReportId,
                   unsigned int ReportLength,
                   void  *ReportData);
int HidSetReport(HidDev_t *HidDev,
                   unsigned int InterfaceNo,
                   unsigned int ReportType,
                   unsigned int ReportId,
                   unsigned int ReportLength,
                   void *ReportData);
int HidGetProtocol(HidDev_t *HidDev, unsigned int InterfaceNo, void *ProtocolData);
int HidSetProtocol(HidDev_t *HidDev, unsigned int InterfaceNo, unsigned int Protocoltype);

int HidParseReport(unsigned char *ReportData, unsigned int ReportSize, HidDev_t *HidDev);
int HidFreeReport(HidDev_t *HidDev);

#endif   //__HIDPROTOCOL_H__

