#ifndef __OS_EXCEPT_H__
#define __OS_EXCEPT_H__

/***********************************
        TYPES OF GENERAL EXCEPTION
 ***********************************/
#define GE_ALIGN_CHECK                          0
#define GE_RESERVED_INST                        1
#define GE_TRAP                                 2
#define GE_ARITHMETIC                           3
#define GE_PRECISE_BUS_ERR                      4
#define GE_INPRECISE_BUS_ERR                    5
#define GE_COPROCESSOR                          6
#define GE_PRIVILEGE_INST                       7
#define GE_RESERVED_VALUE                       8
#define GE_NON_EXIST_LOCAL_MEM                  9
#define GE_MPZIU_CTRL                           10

void *General_Exception_Handler_Table[16];

inline void register_exception_handler(int genneral_except_num, void (*handler)(unsigned int ipc));

#endif
