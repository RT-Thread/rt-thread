/**
  ******************************************************************************
  * @file   openamp.h
  * @brief  Header for openamp applications
  * @author  MCD Application Team
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __openamp_H
#define __openamp_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "openamp/open_amp.h"
#include "openamp_conf.h"

#define OPENAMP_send  rpmsg_send
#define OPENAMP_destroy_ept rpmsg_destroy_ept

/* Initialize the openamp framework*/
int MX_OPENAMP_Init(int RPMsgRole, rpmsg_ns_bind_cb ns_bind_cb);

/* Deinitialize the openamp framework*/
void OPENAMP_DeInit(void);

/* Initialize the endpoint struct*/
void OPENAMP_init_ept(struct rpmsg_endpoint *ept);

/* Create and register the endpoint */
int OPENAMP_create_endpoint(struct rpmsg_endpoint *ept, const char *name,
                            uint32_t dest, rpmsg_ept_cb cb,
                            rpmsg_ns_unbind_cb unbind_cb);

/* Check for new rpmsg reception */
void OPENAMP_check_for_message(void);

/* Wait loop on endpoint ready ( message dest address is know)*/
void OPENAMP_Wait_EndPointready(struct rpmsg_endpoint *rp_ept);

#ifdef __cplusplus
}
#endif
#endif /*__openamp_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
