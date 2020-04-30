/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-05-01     Jonne        first version for s3c2440 USB host controller
 */

#include <rtthread.h>
#include <drivers/usb_host.h>
#include <s3c24x0.h>
#include <rtdevice.h>
#include <rthw.h>
#include <mmu.h>

#define     REG_HcRevision              (*(volatile unsigned long *)0x49000000)
#define     REG_HcControl               (*(volatile unsigned long *)0x49000004)
#define     REG_HcCommandStatus         (*(volatile unsigned long *)0x49000008)
#define     REG_HcInterruptStatus       (*(volatile unsigned long *)0x4900000c)
#define     REG_HcInterruptEnable       (*(volatile unsigned long *)0x49000010)
#define     REG_HcInterruptDisable      (*(volatile unsigned long *)0x49000014)

#define     REG_HcHCCA                  (*(volatile unsigned long *)0x49000018)
#define     REG_HcPeriodCuttentED       (*(volatile unsigned long *)0x4900001c)
#define     REG_HcControlHeadED         (*(volatile unsigned long *)0x49000020)
#define     REG_HcControlCurrentED      (*(volatile unsigned long *)0x49000024)
#define     REG_HcBulkHeadED            (*(volatile unsigned long *)0x49000028)
#define     REG_HcBulkCurrentED         (*(volatile unsigned long *)0x4900002c)
#define     REG_HcDoneHead              (*(volatile unsigned long *)0x49000030)

#define     REG_HcFmInterval            (*(volatile unsigned long *)0x49000034)
#define     REG_HcFmRemaining           (*(volatile unsigned long *)0x49000038)
#define     REG_HcFmNumber              (*(volatile unsigned long *)0x4900003c)
#define     REG_HcPeriodicStart         (*(volatile unsigned long *)0x49000040)
#define     REG_HcLSThreshold           (*(volatile unsigned long *)0x49000044)

#define     REG_HcRhDescriptorA         (*(volatile unsigned long *)0x49000048)
#define     REG_HcRhDescriptorB         (*(volatile unsigned long *)0x4900004c)
#define     REG_HcRhStatus              (*(volatile unsigned long *)0x49000050)
#define     REG_HcRhPortStatus1         (*(volatile unsigned long *)0x49000054)
#define     REG_HcRhPortStatus2         (*(volatile unsigned long *)0x49000058)

#define     OHCI_INTR_SO    (1 << 0)    /* scheduling overrun */
#define     OHCI_INTR_WDH   (1 << 1)    /* writeback of done_head */
#define     OHCI_INTR_SF    (1 << 2)    /* start frame */
#define     OHCI_INTR_RD    (1 << 3)    /* resume detect */
#define     OHCI_INTR_UE    (1 << 4)    /* unrecoverable error */
#define     OHCI_INTR_FNO   (1 << 5)    /* frame number overflow */
#define     OHCI_INTR_RHSC  (1 << 6)    /* root hub status change */
#define     OHCI_INTR_OC    (1 << 30)   /* ownership change */
#define     OHCI_INTR_MIE   (1 << 31)   /* master interrupt enable */

#define     PID_SETUP    0
#define     PID_OUT      1
#define     PID_IN       2

#define     DATA0        2
#define     DATA1        3

#define     TD_CONTROL(R,DP,DI,T)            (((R)<<18)|((DP)<<19)|((DI)<<21)|((T)<<24)|(2<<26))
#define     ED_CONTROL(FA,EN,S,K,F,MPS)      ((FA)|((EN)<<7)|(0<<11)|((S)<<13)|((K)<<14)|((F)<<15)|((MPS)<<16)) 


struct ohci_hcca                        
{
    volatile rt_uint32_t int_table[32];         /* Interrupt ED table */
    volatile rt_uint16_t frame_no;              /* current frame number */
    volatile rt_uint16_t pad1;                  /* set to 0 on each frame_no change */
    volatile rt_uint32_t done_head;             /* info returned for an interrupt */
    volatile rt_uint8_t  reserved_for_hc[116];     
    volatile rt_uint8_t  unknown[4];
}; 

struct ohci_td {  
        volatile  rt_uint32_t  Control;
        volatile  rt_uint32_t  CurrBufP;
        volatile  rt_uint32_t  NextTD;
        volatile  rt_uint32_t  BufEnd;
};

struct ohci_ed {
    volatile rt_uint32_t  Control;
    volatile rt_uint32_t  TailP; 
    volatile rt_uint32_t  HeadP;
    volatile rt_uint32_t  NextED;
};

struct pipe_info {
    rt_uint8_t data_toggle;
};

static  volatile struct  ohci_hcca __attribute__((aligned(256))) ghcca;
static  volatile struct  ohci_ed __attribute__((aligned(16))) gED[1];
static  volatile struct  ohci_td __attribute__((aligned(16))) gTD[16];

static rt_uint8_t ctrl_data_toggle;
static struct rt_completion xfer_completion;

static void ohci_s3c_dump_reg()
{

    rt_kprintf("rHcRevision:0x%08x\n", REG_HcRevision);
    rt_kprintf("rHcControl :0x%08x\n", REG_HcControl);
    rt_kprintf("rHcCommandStatus:0x%08x\n", REG_HcCommandStatus);
    rt_kprintf("rHcInterruptStatus:0x%08x\n", REG_HcInterruptStatus);
    rt_kprintf("rHcInterruptEnable:0x%08x\n", REG_HcInterruptEnable);
    rt_kprintf("rHcInterruptDisable:0x%08x\n", REG_HcInterruptDisable);
    rt_kprintf("rHcHCCA:0x%08x\n", REG_HcHCCA); 
    rt_kprintf("rHcPeriodCuttendED:0x%08x\n", REG_HcPeriodCuttentED);
    rt_kprintf("rHcControlHeadED:0x%08x\n", REG_HcControlHeadED);
    rt_kprintf("rHcControlCurrentED:0x%08x\n", REG_HcControlCurrentED);
    rt_kprintf("rHcBulkHeadED:0x%08x\n", REG_HcBulkHeadED);
    rt_kprintf("rHcBulkCurrentED:0x%08x\n", REG_HcBulkCurrentED);
    rt_kprintf("rHcDoneHead:0x%08x\n", REG_HcDoneHead);
    rt_kprintf("rHcFmInterval:0x%08x\n", REG_HcFmInterval);
    rt_kprintf("rHcFmRemaining:0x%08x\n", REG_HcFmRemaining);
    rt_kprintf("rHcFmNumber:0x%08x\n", REG_HcFmNumber);
    rt_kprintf("rHcPeriodicStart:0x%08x\n", REG_HcPeriodicStart);
    rt_kprintf("rHcLSThreshold:0x%08x\n", REG_HcLSThreshold);
    rt_kprintf("rHcRhDescriptorA:0x%08x\n", REG_HcRhDescriptorA);
    rt_kprintf("rHcRhDescriptorB:0x%08x\n", REG_HcRhDescriptorB);
    rt_kprintf("rHcRhStatus:0x%08x\n", REG_HcRhStatus);
    rt_kprintf("rHcRhPortStatus1:0x%08x\n", REG_HcRhPortStatus1);
    rt_kprintf("rHcRhPortStatus2:0x%08x\n", REG_HcRhPortStatus2);
}

static void ohci_s3c_create_ed(struct ohci_ed * pED, 
                rt_uint32_t Control,
                rt_uint32_t TDQueTailP,
                rt_uint32_t TDQueHeadP,
                rt_uint32_t NextED,
                rt_uint32_t Toggle)
{

    pED->Control = Control;
    pED->TailP = TDQueTailP;
    pED->HeadP = (TDQueHeadP)|((Toggle&1)<<1);
    pED->NextED = NextED;

}

static void ohci_s3c_create_td(struct ohci_td *pTD,
                rt_uint32_t Control,
                rt_uint32_t CurBufPtr,
                rt_uint32_t NextTD,
                rt_uint32_t BuffSize)
{
    pTD->Control = Control;
    pTD->CurrBufP = CurBufPtr;
    pTD->NextTD = NextTD;
    pTD->BufEnd = (BuffSize) ? (CurBufPtr + BuffSize - 1) : CurBufPtr;
}

static void ohci_s3c_start_control_process(void)

{

    REG_HcControlHeadED = (rt_uint32_t)&gED[0];
    REG_HcControlCurrentED = (rt_uint32_t)&gED[0];       

    REG_HcCommandStatus |= 0x02;
    REG_HcControl |= 0x90;

}

static void ohci_s3c_start_bulk_process()
{
    REG_HcBulkHeadED = (rt_uint32_t)&gED[0];
    REG_HcBulkCurrentED = (rt_uint32_t)&gED[0];    

    REG_HcCommandStatus |= 0x04;           
    REG_HcControl |= 0xA0;

}

static void ohci_s3c_poll_rh_status(uhcd_t uhcd)
{
    rt_uint32_t portStatus;

    portStatus = REG_HcRhPortStatus1;

    if(portStatus & (1<<16))
    {
        if(portStatus & (1<<0))
        {
            rt_usbh_root_hub_connect_handler(uhcd, 1, (portStatus & (1<<9)) ? RT_FALSE : RT_TRUE);

        }
        else
        {
            rt_usbh_root_hub_disconnect_handler(uhcd, 1);
        }

        REG_HcRhPortStatus1 = (1<<16);
    }
    
    if(portStatus & (1<<17))
    {
        REG_HcRhPortStatus1 = (1<<17);
    }

}

static void ohci_s3c_hc_isr(int irqno, void *param)
{
    uhcd_t uhcd = param;

    if(REG_HcInterruptStatus & OHCI_INTR_RHSC)
    {
        ohci_s3c_poll_rh_status(uhcd);
        REG_HcInterruptStatus = OHCI_INTR_RHSC;
    }

    if(REG_HcInterruptStatus & OHCI_INTR_WDH)
    {
        REG_HcInterruptStatus = OHCI_INTR_WDH;
        rt_completion_done(&xfer_completion); 
    }
}

static rt_err_t ohci_s3c_hc_reset()
{
    rt_uint32_t timeout = 50;

    if(REG_HcControl & (1<<8))
    {
        REG_HcCommandStatus = (1<<3);

        while(REG_HcControl & (1<<8))
        {
            rt_thread_mdelay(10);
            if(--timeout == 0) 
            {
                rt_kprintf("USB HC TakeOver failed!");
                return -RT_ERROR;
            }
        }
    }

    REG_HcInterruptDisable = (1<<31); // disable interrupt

    REG_HcControl = 0;
    REG_HcCommandStatus = (1<<0); // reset

    timeout = 30;
    while((REG_HcCommandStatus & (1<<0)) != 0)
    {
        rt_thread_mdelay(1);
        if(--timeout == 0)
        {
            rt_kprintf("USB HC reset timed out!");
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

static rt_err_t ohci_s3c_hc_start()
{
    rt_uint32_t fminterval;
    rt_uint32_t mask;
    rt_uint32_t val;

    REG_HcControlHeadED = 0;
    REG_HcBulkHeadED = 0;

    REG_HcHCCA = (rt_uint32_t)&ghcca;
    ghcca.done_head = 0;
    REG_HcDoneHead = 0;

    fminterval = 0x2edf;
    REG_HcPeriodicStart = (fminterval * 9) / 10;

    fminterval |= ((((fminterval - 210) * 6) / 7) << 16);
    REG_HcFmInterval = fminterval;
    REG_HcLSThreshold = 0x628;

    REG_HcControl = (3<<0) | (1<<2) | (1<<3) | (2<<6);
    
    mask = (OHCI_INTR_SO | OHCI_INTR_WDH | OHCI_INTR_SF | OHCI_INTR_RD |
                OHCI_INTR_UE | OHCI_INTR_FNO | OHCI_INTR_RHSC |
                    OHCI_INTR_OC | OHCI_INTR_MIE);
    REG_HcInterruptDisable = mask;

    mask &= ~OHCI_INTR_MIE;
    REG_HcInterruptStatus = mask;

    mask = (OHCI_INTR_RHSC | OHCI_INTR_WDH | OHCI_INTR_MIE);
    REG_HcInterruptEnable = mask;

    val = REG_HcRhDescriptorA;
    val |= (1<<9);
    val &= ~(1<<8);
    REG_HcRhDescriptorA = val;

    REG_HcRhStatus = 0x00010000;
    
    return RT_EOK;
}

static rt_err_t rt_hcd_reset_port(rt_uint8_t port)
{
    rt_uint32_t try_cnt0;
    rt_uint32_t try_cnt1;

    REG_HcInterruptDisable = (1<<31);
    try_cnt0 = 5;
    while(try_cnt0--) 
    {
        try_cnt1 = 10;
        while(try_cnt1--)
        {
            if((REG_HcRhPortStatus1 & (1<<4)) == 0)
            {
                break;
            }
            rt_thread_mdelay(1);
        }

        if(try_cnt1 == 0)
        {
            rt_kprintf("Port reset timeout try_cnt0:%d try_cnt1:%d\n", try_cnt0, try_cnt1);
            break;
        }

        if((REG_HcRhPortStatus1 & (1<<0)) == 0)
        {
            break;
        }

        if(REG_HcRhPortStatus1 & (1<<20))
        {
            REG_HcRhPortStatus1 = (1<<20);
        }

        if(try_cnt0 == 1)
        {
            break;
        }

        REG_HcRhPortStatus1 = (1<<4);
        
        rt_thread_mdelay(10);
    }

    REG_HcInterruptEnable = (1<<31);

    return RT_EOK;
}
static int rt_hcd_pipe_xfer(upipe_t pipe, rt_uint8_t token, void* buffer, int nbytes, int timeout)
{
    struct pipe_info * p_info;

    p_info = pipe->user_data;
    if(p_info == RT_NULL)
    {
        rt_kprintf("Error pipe\n");
        return -RT_ERROR;
    }
 
    if(buffer)
    {
        mmu_clean_dcache((rt_uint32_t)buffer, nbytes);
    }

    rt_completion_init(&xfer_completion); 

    if(USBH_PID_SETUP == token)
    {
        if(nbytes != 8) 
        {
            rt_kprintf("Setup size error\n");
            return -RT_ERROR;
        }
        ohci_s3c_create_td((struct ohci_td *)&gTD[0], 
                                TD_CONTROL(1,PID_SETUP,2,DATA0), 
                                (rt_uint32_t)buffer,
                                (rt_uint32_t)NULL,    
                                nbytes);

        ohci_s3c_create_ed((struct ohci_ed *)&gED[0],
                                ED_CONTROL(pipe->inst->address, pipe->ep.bEndpointAddress & 0x0F, pipe->inst->speed, 0, 0, pipe->ep.wMaxPacketSize),
                                (rt_uint32_t)NULL,
                                (rt_uint32_t)&gTD[0],
                                (rt_uint32_t)NULL, 
                                1);
        ohci_s3c_start_control_process();

        ctrl_data_toggle = DATA1;

    }
    else if(USBH_PID_DATA == token) 
    {
        unsigned char *p = buffer;
        rt_uint8_t td_dp;
        rt_uint8_t cur_data_toggle;
    
        if((pipe->ep.bmAttributes & 0x3) == 0x00)
        {
            if(nbytes == 0)
            {
                cur_data_toggle = DATA1;
            }
            else 
            {
                cur_data_toggle = ctrl_data_toggle;
            }
            
            if((pipe->ep.bEndpointAddress & 0x80))
            {
                td_dp = PID_IN; 
            }
            else
            {
                td_dp = PID_OUT;
            }
        }
        else
        {
            
            cur_data_toggle = p_info->data_toggle;
            if((pipe->ep.bEndpointAddress & 0x80))
            {
                td_dp = PID_IN; 
            }
            else
            {
                td_dp = PID_OUT;
            }
        }
        
        ohci_s3c_create_td((struct ohci_td *)&gTD[0],
                                TD_CONTROL(1,td_dp,2,cur_data_toggle),         
                                (rt_uint32_t)buffer,                     
                                (rt_uint32_t)NULL,                       
                                nbytes);

        ohci_s3c_create_ed((struct ohci_ed *)&gED[0],
                                ED_CONTROL(pipe->inst->address, pipe->ep.bEndpointAddress & 0x0F, pipe->inst->speed, 0, 0, pipe->ep.wMaxPacketSize),
                                (rt_uint32_t)NULL,                       
                                (rt_uint32_t)&gTD[0],                    
                                (rt_uint32_t)NULL,                       
                                1);

        if((pipe->ep.bmAttributes & 0x3) == 0x00)
        {
            ohci_s3c_start_control_process();
            ctrl_data_toggle = (cur_data_toggle == DATA0 ? DATA1 : DATA0);
        }
        else 
        {
            ohci_s3c_start_bulk_process();
            p_info->data_toggle = (cur_data_toggle == DATA0 ? DATA1 : DATA0);
        }


    }
    else 
    {
        rt_kprintf("Token :%d not support\n", token);
        return -RT_ERROR;
    }

    rt_completion_wait(&xfer_completion, timeout);

    if(buffer)
    {
        mmu_invalidate_dcache((rt_uint32_t)buffer, nbytes);
    }

    if(ghcca.done_head != (rt_uint32_t)&gTD[0])
    {
        rt_kprintf("USB transfer failed \n");
        return -RT_ERROR;
    }

    return nbytes;
}
static rt_err_t rt_hcd_open_pipe(upipe_t pipe)
{
    struct pipe_info * pipe_data;

    if(pipe == RT_NULL)
    {
        rt_kprintf("pipe is null\n");
        return -RT_ERROR;
    }
   
    pipe_data = rt_malloc(sizeof(struct pipe_info));
    if(pipe_data == RT_NULL)
    {
        rt_kprintf("No memory\n");
        return -RT_ERROR;
    }

    pipe_data->data_toggle = DATA0;

    pipe->user_data = pipe_data;

    return RT_EOK;
}
static rt_err_t rt_hcd_close_pipe(upipe_t pipe)
{
    if(pipe == RT_NULL || pipe->user_data == RT_NULL)
    {
        return RT_EOK;
    }
    rt_free(pipe->user_data);
    pipe->user_data = RT_NULL;

    return RT_EOK;
}

static struct uhcd_ops _uhcd_ops = {
    .reset_port = rt_hcd_reset_port,
    .pipe_xfer = rt_hcd_pipe_xfer,
    .open_pipe = rt_hcd_open_pipe,
    .close_pipe = rt_hcd_close_pipe
};

static rt_err_t rt_hcd_init(rt_device_t device)                                                                                                                                                          
{
    uhcd_t uhcd;    

    CLKDIVN |= (1<<3);

    uhcd = device->user_data;

    ohci_s3c_hc_reset();

    ohci_s3c_hc_start();

    rt_hw_interrupt_install(INTUSBH, ohci_s3c_hc_isr, uhcd, "usbh");
    rt_hw_interrupt_umask(INTUSBH);

    return RT_EOK;
}

int rt_usbh_register(void)
{
    rt_err_t res = -RT_ERROR;

    uhcd_t uhcd = (uhcd_t)rt_malloc(sizeof(struct uhcd));
    if (uhcd == RT_NULL)
    {
        rt_kprintf("uhcd malloc failed\r\n");    
        return -RT_ERROR;
    }

    rt_memset((void *)uhcd, 0, sizeof(struct uhcd));                                                                                                                                                        

    uhcd->parent.type = RT_Device_Class_USBHost;
    uhcd->parent.init = rt_hcd_init;
    uhcd->parent.user_data = uhcd;                                                                                                                                                                

    uhcd->ops = &_uhcd_ops;
    uhcd->num_ports = 1;

    res = rt_device_register(&uhcd->parent, "usbh", RT_DEVICE_FLAG_DEACTIVATE);                                                                                                                             
    if (res != RT_EOK)
    {
        rt_kprintf("register usb host failed res = %d\r\n", res);
        return -RT_ERROR;
    }

    rt_usb_host_init();

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_usbh_register);
