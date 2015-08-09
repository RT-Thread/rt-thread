/******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2004-2010 Freescale Semiconductor, Inc.
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
 * @file USB_Config.h
 *
 * @author B14088
 *
 * @version
 *
 * @date Oct 31, 2010
 *
 * @brief
 *****************************************************************************/

#ifndef USB_CONFIG_H_
#define USB_CONFIG_H_

/*****************************************************************************/
/*                              Includes Section                             */
/*****************************************************************************/


/*****************************************************************************/
/*                              Typedef Section                              */
/*****************************************************************************/


/*****************************************************************************/
/* 								Function's Prototypes						 */
/*****************************************************************************/
/* PHDC class services */
extern void USB_Class_PHDC_Endpoint_Service (PTR_USB_DEV_EVENT_STRUCT event);
extern void USB_NULL_CALLBACK (PTR_USB_DEV_EVENT_STRUCT event);

/*****************************************************************************/
/*                          Defines & Macros Section                         */
/*****************************************************************************/
#define REMOTE_WAKEUP_SUPPORT            (TRUE)

/* Hardware components configuration */
#define USB_HW_VREG_EN                   TRUE
#define USB_HW_PU_EN                     TRUE

/* Event callbacks assignation */
#define  USB_EP0_CALLBACK                    USB_Control_Service
#define  USB_EP1_CALLBACK                    USB_Class_PHDC_Endpoint_Service
#define  USB_EP2_CALLBACK                    USB_Class_PHDC_Endpoint_Service
#ifndef _MC9S08JS16_H
#define  USB_EP3_CALLBACK                    USB_Class_PHDC_Endpoint_Service
#else
#define  USB_EP3_CALLBACK                    USB_NULL_CALLBACK
#endif
#define  USB_EP4_CALLBACK                    USB_NULL_CALLBACK
#define  USB_EP5_CALLBACK                    USB_NULL_CALLBACK
#define  USB_EP6_CALLBACK                    USB_NULL_CALLBACK
#define  USB_EP7_CALLBACK                    USB_NULL_CALLBACK
#define  USB_EP8_CALLBACK                    USB_NULL_CALLBACK
#define  USB_EP9_CALLBACK                    USB_NULL_CALLBACK
#define  USB_EP10_CALLBACK                   USB_NULL_CALLBACK
#define  USB_EP11_CALLBACK                   USB_NULL_CALLBACK
#define  USB_EP12_CALLBACK                   USB_NULL_CALLBACK
#define  USB_EP13_CALLBACK                   USB_NULL_CALLBACK
#define  USB_EP14_CALLBACK                   USB_NULL_CALLBACK
#define  USB_EP15_CALLBACK                   USB_NULL_CALLBACK

#define  USB_BUS_RESET_CALLBACK              USB_Reset_Service
#define  USB_SUSPEND_CALLBACK                USB_NULL_CALLBACK
#define  USB_SOF_CALLBACK                    USB_Sof_Service
#define  USB_RESUME_CALLBACK                 USB_Resume_Service
#define  USB_SLEEP_CALLBACK                  USB_Suspend_Service
#define  USB_SPEED_DETECTION_CALLBACK        USB_NULL_CALLBACK
#define  USB_ERROR_CALLBACK                  USB_Error_Service
#define  USB_STALL_CALLBACK                  USB_Stall_Service

/* Endpoints configuration */
#define USB_EP0_ENABLE              TRUE
#define USB_EP0_DIR                 EP_CTRL
#define USB_EP0_HSHK                TRUE
#define USB_EP0_SIZE                32

#define USB_EP1_ENABLE              TRUE
#define USB_EP1_DIR                 EP_IN
#define USB_EP1_HSHK                TRUE
#define USB_EP1_SIZE                8

#define USB_EP2_ENABLE              TRUE
#define USB_EP2_DIR                 EP_OUT
#define USB_EP2_HSHK                TRUE
#define USB_EP2_SIZE                4

#ifndef _MC9S08JS16_H
#define USB_EP3_ENABLE              TRUE
#define USB_EP3_DIR                 EP_IN
#define USB_EP3_HSHK                TRUE
#define USB_EP3_SIZE                8
#else
#define USB_EP3_ENABLE              FALSE
#define USB_EP3_DIR                 EP_IN
#define USB_EP3_HSHK                TRUE
#define USB_EP3_SIZE                0
#endif

#define USB_EP4_ENABLE              FALSE
#define USB_EP4_DIR                 NA
#define USB_EP4_HSHK                TRUE
#define USB_EP4_SIZE                0

#define USB_EP5_ENABLE              FALSE
#define USB_EP5_DIR                 NA
#define USB_EP5_HSHK                TRUE
#define USB_EP5_SIZE                0

#define USB_EP6_ENABLE              FALSE
#define USB_EP6_DIR                 NA
#define USB_EP6_HSHK                TRUE
#define USB_EP6_SIZE                0

#define USB_EP7_ENABLE              FALSE
#define USB_EP7_DIR                 NA
#define USB_EP7_HSHK                TRUE
#define USB_EP7_SIZE                0

#define USB_EP8_ENABLE              FALSE
#define USB_EP8_DIR                 NA
#define USB_EP8_HSHK                TRUE
#define USB_EP8_SIZE                0

#define USB_EP9_ENABLE              FALSE
#define USB_EP9_DIR                 NA
#define USB_EP9_HSHK                TRUE
#define USB_EP9_SIZE                0

#define USB_EP10_ENABLE             FALSE
#define USB_EP10_DIR                NA
#define USB_EP10_HSHK               TRUE
#define USB_EP10_SIZE               0

#define USB_EP11_ENABLE             FALSE
#define USB_EP11_DIR                NA
#define USB_EP11_HSHK               TRUE
#define USB_EP11_SIZE               0

#define USB_EP12_ENABLE             FALSE
#define USB_EP12_DIR                NA
#define USB_EP12_HSHK               TRUE
#define USB_EP12_SIZE               0

#define USB_EP13_ENABLE             FALSE
#define USB_EP13_DIR                NA
#define USB_EP13_HSHK               TRUE
#define USB_EP13_SIZE               0

#define USB_EP14_ENABLE             FALSE
#define USB_EP14_DIR                NA
#define USB_EP14_HSHK               TRUE
#define USB_EP14_SIZE               0

#define USB_EP15_ENABLE             FALSE
#define USB_EP15_DIR                NA
#define USB_EP15_HSHK               TRUE
#define USB_EP15_SIZE               0

/*****************************************************************************/
/*                          Extern Variables Section                         */
/*****************************************************************************/


/*****************************************************************************/
/*                         Function Prototypes Section                       */
/*****************************************************************************/


/*****************************************************************************/

#endif /* USB_CONFIG_H_ */
