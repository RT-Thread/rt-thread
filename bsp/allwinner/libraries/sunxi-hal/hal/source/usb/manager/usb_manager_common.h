#ifndef __USB_MANAGER_COMMON_H__
#define __USB_MANAGER_COMMON_H__
//#define USB_MANAGER_DEBUG
#if (defined USB_MANAGER_DEBUG) && (CONFIG_LOG_DEFAULT_LEVEL != 0)
#define Usb_Manager_Debug(...) do { \
                                printf("DEBUG %s %d %s :", __FILE__, __LINE__, __func__);                 \
                                printf(__VA_ARGS__); \
                            } while(0)
#define Usb_Manager_Err(...) do { \
                                printf("ERR %s %d %s :", __FILE__, __LINE__, __func__);                 \
                                printf(__VA_ARGS__); \
                            } while(0)
#define Usb_Manager_INFO(...) do { \
                                    printf("INFO %s %d %s :", __FILE__, __LINE__, __func__);                \
                                    printf(__VA_ARGS__); \
                                } while(0)
#else
#define Usb_Manager_Debug(...)
#define Usb_Manager_Err(...)
#define Usb_Manager_INFO(...)
#endif
#endif
