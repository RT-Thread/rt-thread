
//#ifdef UDISK
#include "usb_lib.h"
extern void (*pEpInt_IN[7])(void);    /*  Handles IN  interrupts   */

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : USB_Init
* Description    : USB system initialization
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void udisk_EP1_IN_Callback(void);
void udisk_USB_Init(void)
{
	pEpInt_IN[0]=udisk_EP1_IN_Callback;
  pInformation = &Device_Info;
  pInformation->ControlState = 2;
  pProperty = &udisk_Device_Property;
  pUser_Standard_Requests = &udisk_User_Standard_Requests;
  /* Initialize devices one by one */
  pProperty->Init();
}

//#endif
