#define UNUSED(x)               ((void)x)

#define __HAL_LOCK(__HANDLE__)  do{                                        \
                                    if((__HANDLE__)->Lock == HAL_LOCKED)   \
                                    {                                      \
                                        return HAL_BUSY;                   \
                                    }                                      \
                                    else                                   \
                                    {                                      \
                                        (__HANDLE__)->Lock = HAL_LOCKED;   \
                                    }                                      \
                                }while (0)


#define __HAL_UNLOCK(__HANDLE__) do{                                       \
                                    (__HANDLE__)->Lock = HAL_UNLOCKED;     \
                                }while (0)

#define USE_HAL_PCD_REGISTER_CALLBACKS      0

#define HAL_Delay                           ARCH_Delay_US


