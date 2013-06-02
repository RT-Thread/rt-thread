/** @file std_nhet.h
*   @brief NHET Instruction Definition File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   (c) Texas Instruments 2009-2013, All rights reserved.
*/

#ifndef __STD_NHET_H__
#define __STD_NHET_H__

#include "sys_common.h"

#if defined(_TMS470_BIG) || defined(__big_endian__)

#ifndef HET_v2
#   define HET_v2 0
#endif

#ifndef HETBYTE
#   define HETBYTE uint8
#endif

typedef struct memory_format
{
  uint32 program_word  ;
  uint32 control_word  ;
  uint32 data_word     ;
  uint32 reserved_word ;
} HET_MEMORY  ;
 

/*---------------------------------------------*/
/* ACMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct acmp_format
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32                      : 9 ;

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32 coutprv              : 1 ;
  uint32                      : 2 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32 ext_reg              : 1 ;
  uint32                      : 2 ; 
  uint32 pin_action           : 1 ;
  uint32                      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  uint32 data                 : 25 ;
  uint32                      : 7  ;
 
} ACMP_FIELDS;
 
typedef union
{
  ACMP_FIELDS  acmp   ;
  HET_MEMORY   memory ;
} ACMP_INSTRUCTION;


/*---------------------------------------------*/
/* ECMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct ecmp_format   
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;          
  uint32 next_program_address : 9 ;          
  uint32 op_code              : 4 ;
  uint32 hr_lr                : 1 ;
  uint32 angle_compare        : 1 ;
  uint32                      : 7 ;

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 3 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 sub_opcode           : 2 ;
  uint32 pin_action           : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;

} ECMP_FIELDS;

typedef union 
{
  ECMP_FIELDS  ecmp   ;
  HET_MEMORY   memory ;
} ECMP_INSTRUCTION;


/*---------------------------------------------*/
/* SCMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct scmp_format     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;          
  uint32 next_program_address : 9 ;          
  uint32 op_code              : 4 ;
  uint32                      : 2 ;
  uint32                      : 2 ;
  uint32                      : 5 ;

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32 coutprv              : 1 ;
  uint32                      : 2 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 compare_mode         : 2 ;
  uint32 pin_action           : 1 ;
  uint32                      : 2 ;
  uint32 restart_en           : 1 ;
  uint32 interrupt_enable     : 1 ;

  
  uint32 data                 : 25 ;
  uint32                      : 7 ;

} SCMP_FIELDS ;

typedef union 
{
  SCMP_FIELDS  scmp   ;
  HET_MEMORY   memory ;
} SCMP_INSTRUCTION;


/*---------------------------------------------*/
/* MCMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct mcmp_format                     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 hr_lr                : 1 ;
  uint32 angle_compare        : 1 ;
  uint32                      : 1 ;
  uint32 save_subtract        : 1 ;
  uint32                      : 5 ;
 
  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 3 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 sub_opcode           : 1 ; 
  uint32 order                : 1 ; 
  uint32 pin_action           : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} MCMP_FIELDS ; 

typedef union 
{
  MCMP_FIELDS  mcmp   ;
  HET_MEMORY   memory ;
} MCMP_INSTRUCTION;


/*---------------------------------------------*/
/* MOV64 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct mov64_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;          
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 3 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 compare_mode         : 2 ;
  uint32 pin_action           : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;

} MOV64_FIELDS ; 

typedef union 
{
  MOV64_FIELDS  mov64  ;
  HET_MEMORY    memory ;
} MOV64_INSTRUCTION;


/*---------------------------------------------*/
/* DADM64 INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct dadm64_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 3 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 compare_mode         : 2 ;
  uint32 pin_action           : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} DADM64_FIELDS ; 

typedef union 
{
  DADM64_FIELDS  dadm64 ;
  HET_MEMORY     memory ;
} DADM64_INSTRUCTION;


/*---------------------------------------------*/
/* RADM64 INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct RADM64_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 3 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 compare_mode         : 2 ;
  uint32 pin_action           : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} RADM64_FIELDS ; 


typedef union 
{
  RADM64_FIELDS  radm64 ;
  HET_MEMORY     memory ;
} RADM64_INSTRUCTION;


/*---------------------------------------------*/
/* MOV32 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct MOV32_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 5 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 3 ;
  uint32 z_flag               : 1 ;
  uint32                      : 15 ;
  uint32 init_flag            : 1 ;
  uint32 sub_opcode           : 1 ;   
  uint32 move_type            : 2 ;     
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32                      : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} MOV32_FIELDS ; 


typedef union 
{
  MOV32_FIELDS  mov32  ;
  HET_MEMORY    memory ;
} MOV32_INSTRUCTION;


/*---------------------------------------------*/
/* ADM32 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct ADM32_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 5 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 19 ;
  uint32 init_flag            : 1 ;
  uint32 sub_opcode           : 1 ;
  uint32 move_type            : 2 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32                      : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} ADM32_FIELDS ; 


typedef union 
{
  ADM32_FIELDS  adm32  ;
  HET_MEMORY    memory ;
} ADM32_INSTRUCTION;


/*---------------------------------------------*/
/* ADCNST INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct ADCNST_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 5 ;
  uint32 control              : 1 ;  /* pk */
  uint32                      : 1 ;
  uint32 constant             : 25 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} ADCNST_FIELDS ;


typedef union 
{
  ADCNST_FIELDS  adcnst ;
  HET_MEMORY     memory ;
} ADCNST_INSTRUCTION;


/*----------------------------------------------*/
/* ADD INSTRUCTION				  	*/
/*----------------------------------------------*/

typedef struct ADD_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 5 ;
  uint32 control              : 1;
  uint32 sub_opcode3          : 3 ;
  uint32 src_1                : 4 ;
  uint32 src_2                : 3 ;
  uint32 shft_mode            : 3 ;
  uint32 shft_cnt             : 5 ;
  uint32 reg_ext              : 1 ;
  uint32 init_flag            : 1 ;
  uint32 sub_opcode1          : 1 ;
  uint32 rem_dest             : 2 ;
  uint32 reg	                : 2 ;
  uint32                      : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} ADD_FIELDS ;


typedef union 
{
  ADD_FIELDS  add ;
  HET_MEMORY  memory ;
} ADD_INSTRUCTION;



/*----------------------------------------------*/
/* ADC INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct ADC_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 5 ;
  uint32 control              : 1;
  uint32 sub_opcode3          : 3 ;
  uint32 src_1                : 4 ;
  uint32 src_2                : 3 ;
  uint32 shft_mode            : 3 ;
  uint32 shft_cnt             : 5 ;
  uint32 reg_ext              : 1 ;
  uint32 init_flag            : 1 ;
  uint32 sub_opcode1          : 1 ;
  uint32 rem_dest             : 2 ;
  uint32 reg	                : 2 ;
  uint32                      : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} ADC_FIELDS ;


typedef union 
{
  ADC_FIELDS  adc ;
  HET_MEMORY  memory ;
} ADC_INSTRUCTION;



/*----------------------------------------------*/
/* SUB INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct SUB_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 5 ;
  uint32 control              : 1;
  uint32 sub_opcode3          : 3 ;
  uint32 src_1                : 4 ;
  uint32 src_2                : 3 ;
  uint32 shft_mode            : 3 ;
  uint32 shft_cnt             : 5 ;
  uint32 reg_ext              : 1 ;
  uint32 init_flag            : 1 ;
  uint32 sub_opcode1          : 1 ;
  uint32 rem_dest             : 2 ;
  uint32 reg	                : 2 ;
  uint32                      : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} SUB_FIELDS ;


typedef union 
{
  SUB_FIELDS  sub ;
  HET_MEMORY  memory ;
} SUB_INSTRUCTION;



/*----------------------------------------------*/
/* SBB INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct SBB_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 5 ;
  uint32 control              : 1;
  uint32 sub_opcode3          : 3 ;
  uint32 src_1                : 4 ;
  uint32 src_2                : 3 ;
  uint32 shft_mode            : 3 ;
  uint32 shft_cnt             : 5 ;
  uint32 reg_ext              : 1 ;
  uint32 init_flag            : 1 ;
  uint32 sub_opcode1          : 1 ;
  uint32 rem_dest             : 2 ;
  uint32 reg	                : 2 ;
  uint32                      : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} SBB_FIELDS ;


typedef union 
{
  SBB_FIELDS  sbb ;
  HET_MEMORY  memory ;
} SBB_INSTRUCTION;



/*----------------------------------------------*/
/* AND INSTRUCTION				      */
/*----------------------------------------------*/

typedef struct AND_format
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 5 ;
  uint32 control              : 1;
  uint32 sub_opcode3          : 3 ;
  uint32 src_1                : 4 ;
  uint32 src_2                : 3 ;
  uint32 shft_mode            : 3 ;
  uint32 shft_cnt             : 5 ;
  uint32 reg_ext              : 1 ;
  uint32 init_flag            : 1 ;
  uint32 sub_opcode1          : 1 ;
  uint32 rem_dest             : 2 ;
  uint32 reg	                : 2 ;
  uint32                      : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} AND_FIELDS ;


typedef union 
{
  AND_FIELDS  and ;
  HET_MEMORY  memory ;
} AND_INSTRUCTION;



/*----------------------------------------------*/
/* OR INSTRUCTION					      */
/*----------------------------------------------*/


typedef struct OR_format
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 5 ;
  uint32 control              : 1;
  uint32 sub_opcode3          : 3 ;
  uint32 src_1                : 4 ;
  uint32 src_2                : 3 ;
  uint32 shft_mode            : 3 ;
  uint32 shft_cnt             : 5 ;
  uint32 reg_ext              : 1 ;
  uint32 init_flag            : 1 ;
  uint32 sub_opcode1          : 1 ;
  uint32 rem_dest             : 2 ;
  uint32 reg	                : 2 ;
  uint32                      : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} OR_FIELDS ;


typedef union 
{
  OR_FIELDS  or ;
  HET_MEMORY  memory ;
} OR_INSTRUCTION;



/*----------------------------------------------*/
/* XOR INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct XOR_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 remote_address       : 9 ;
 
  uint32                      : 5 ;
  uint32 control              : 1;
  uint32 sub_opcode3          : 3 ;
  uint32 src_1                : 4 ;
  uint32 src_2                : 3 ;
  uint32 shft_mode            : 3 ;
  uint32 shft_cnt             : 5 ;
  uint32 reg_ext              : 1 ;
  uint32 init_flag            : 1 ;
  uint32 sub_opcode1          : 1 ;
  uint32 rem_dest             : 2 ;
  uint32 reg	                : 2 ;
  uint32                      : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} XOR_FIELDS ;


typedef union 
{
  XOR_FIELDS  xor ;
  HET_MEMORY  memory ;
} XOR_INSTRUCTION;



/*---------------------------------------------*/
/* CNT INSTRUCTION                             */
/*---------------------------------------------*/
typedef struct CNT_format                     
{
  uint32                      : 9 ;        
  uint32 brk                  : 1 ;          
  uint32 next_program_address : 9 ;          
  uint32 op_code              : 4 ;
  uint32 angle_cnt            : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32                      : 4 ;
  uint32 interrupt_enable     : 1 ;
 

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 1 ;
  uint32 max                  : 25 ;

  
  uint32 data                 : 25 ;
  uint32                      : 7 ;

} CNT_FIELDS ; 

typedef union 
{
  CNT_FIELDS   cnt    ; 
  HET_MEMORY   memory ;
} CNT_INSTRUCTION;


/*---------------------------------------------*/
/* APCNT INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct apcnt_format
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 interrupt_enable     : 1 ;
  uint32 edge_select          : 2 ;
  uint32                      : 6 ;

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32 previous_bit         : 1 ;
  uint32 count                : 25 ;
 
  
  uint32 data                 : 25 ;
  uint32                      : 7 ;
 
} APCNT_FIELDS ;
 
typedef union
{
  APCNT_FIELDS  apcnt   ;
  HET_MEMORY   memory ;
} APCNT_INSTRUCTION;
 
 

/*---------------------------------------------*/
/* PCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct pcnt_format                     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;          
  uint32 next_program_address : 9 ;          
  uint32 op_code              : 4 ;
  uint32 interrupt_enable     : 1 ;
  uint32 period_pulse_select  : 2 ;
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32 previous_bit         : 1 ;
  uint32 count                : 25 ;

  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;

} PCNT_FIELDS ;      

typedef union 
{
  PCNT_FIELDS  pcnt   ; 
  HET_MEMORY   memory ;
} PCNT_INSTRUCTION;


/*---------------------------------------------*/
/* SCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct scnt_format                     
{
  uint32                      : 9 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32                      : 1 ;
  uint32 count_mode           : 2 ;
  uint32 step_width           : 2 ;
  uint32                      : 4 ;

  uint32                      : 5 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 1 ;
  uint32 gap_start            : 25 ;

  
  uint32 data                 : 25 ;
  uint32                      : 7 ;

} SCNT_FIELDS ;      

typedef union 
{
  SCNT_FIELDS  scnt   ; 
  HET_MEMORY   memory ;
} SCNT_INSTRUCTION;



/*---------------------------------------------*/
/* ACNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct acnt_format                     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;          
  uint32 op_code              : 4 ;
  uint32 edge_select          : 1 ;
  uint32                      : 7 ;
  uint32 interrupt_enable     : 1 ; 

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32 previous_bit         : 1 ;
  uint32 gap_end              : 25 ;
 
  
  uint32 data                 : 25 ;
  uint32                      : 7 ;

} ACNT_FIELDS ;      

typedef union 
{
  ACNT_FIELDS  acnt   ; 
  HET_MEMORY   memory ;
} ACNT_INSTRUCTION;


/*---------------------------------------------*/
/* ECNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct ecnt_format
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32                      : 1 ;
  uint32 count_mode           : 2 ;
  uint32                      : 6 ;
 
  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32 previous_bit         : 1 ;
  uint32                      : 3 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 count_cond           : 3 ;
  uint32                      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  
  uint32 data                 : 25 ;
  uint32                      : 7 ;
 
} ECNT_FIELDS ;
 
typedef union
{
  ECNT_FIELDS  ecnt   ;
  HET_MEMORY   memory ;
} ECNT_INSTRUCTION;



/*---------------------------------------------*/
/* RCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct rcnt_format
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32                      : 1 ;
  uint32 count_mode           : 2 ;
  uint32                      : 5 ;
  uint32 count_mode1          : 1 ;
 
  uint32                      : 3 ;
  uint32                      : 2 ;
  uint32 control              : 1 ;
  uint32                      : 1 ;
  uint32 divisor              : 25 ;

  
  uint32 data                 : 25 ;
  uint32                      : 7 ;
 
} RCNT_FIELDS ;
 
typedef union
{
  RCNT_FIELDS  rcnt   ;
  HET_MEMORY   memory ;
} RCNT_INSTRUCTION;


/*---------------------------------------------*/
/* DJNZ INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct djnz_format                     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;          
  uint32 op_code              : 4 ;
  uint32                      : 1 ;
  uint32 sub_opcode           : 2 ;
  uint32                      : 6 ;

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 4 ;
  uint32 cond_addr            : 9 ;
  uint32                      : 10 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  
  uint32 data                 : 25 ;
  uint32                      : 7 ;

} DJNZ_FIELDS ;      

typedef union 
{
  DJNZ_FIELDS  djnz   ; 
  HET_MEMORY   memory ;
} DJNZ_INSTRUCTION;


/*---------------------------------------------*/
/* DJZ INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct djz_format                     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;          
  uint32 op_code              : 4 ;
  uint32                      : 1 ;
  uint32 sub_opcode           : 2 ;
  uint32                      : 6 ;

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 4 ;
  uint32 cond_addr            : 9 ;
  uint32                      : 10 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  
  uint32 data                 : 25 ;
  uint32                      : 7 ;

} DJZ_FIELDS ;      

typedef union 
{
  DJZ_FIELDS  djz   ; 
  HET_MEMORY   memory ;
} DJZ_INSTRUCTION;

/*---------------------------------------------*/
/* PWCNT INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct pwcnt_format                     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 hr_lr                : 1 ;
  uint32 count_mode           : 2 ;
  uint32                      : 6 ;

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 3 ;
  uint32 en_pin_action        : 1 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 3 ;
  uint32 pin_action           : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} PWCNT_FIELDS ;      

typedef union 
{
  PWCNT_FIELDS  pwcnt ;
  HET_MEMORY   memory ;
} PWCNT_INSTRUCTION;


/*---------------------------------------------*/
/* WCAP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct wcap_format                     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32 hr_lr                : 1 ;
  uint32                      : 8 ;
  
  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32 previous_bit         : 1 ;
  uint32                      : 3 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 capture_condition    : 2 ;
  uint32                      : 2 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;

} WCAP_FIELDS ;      

typedef union 
{
  WCAP_FIELDS  wcap   ; 
  HET_MEMORY   memory ;
} WCAP_INSTRUCTION;
 
/*----------------------------------------------*/
/* WCAPE INSTRUCTION                            */
/*----------------------------------------------*/
typedef struct wcape_format                     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32                      : 9 ;
  
  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32 previous_bit         : 1 ;
  uint32                      : 3 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 capture_condition    : 2 ;
  uint32                      : 2 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  
  uint32 ts_data              : 25 ;
  uint32 ec_data              : 7 ;

} WCAPE_FIELDS ;      

typedef union 
{
  WCAPE_FIELDS  wcape   ; 
  HET_MEMORY   memory ;
} WCAPE_INSTRUCTION;
 

/*---------------------------------------------*/
/* BR   INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct br_format                     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32                      : 9 ;

  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32 previous_bit         : 1 ;
  uint32                      : 3 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;

#if HET_v2
  uint32 branch_condition     : 5 ;
#else 
  uint32 branch_condition     : 3 ;
  uint32                      : 1 ;
  uint32                      : 1 ;
#endif 

  uint32                      : 2 ;
  uint32 interrupt_enable     : 1 ;
 
  
  uint32 data                 : 25 ;
  uint32 hr_data              : 7 ;
 
} BR_FIELDS ;      

typedef union 
{
  BR_FIELDS  br     ; 
  HET_MEMORY memory ;
} BR_INSTRUCTION;

 
/*---------------------------------------------*/
/* SHFT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct shft_format                     
{
  uint32                      : 6 ;
  uint32 reqnum               : 3 ;
  uint32 brk                  : 1 ;
  uint32 next_program_address : 9 ;
  uint32 op_code              : 4 ;
  uint32                      : 5 ;
  uint32 shift_mode           : 4 ;
 
  uint32                      : 3 ;
  uint32 request              : 2 ;
  uint32 auto_read_clear      : 1 ;
  uint32 previous_bit         : 1 ;
  uint32                      : 3 ;
  uint32 cond_addr            : 9 ;
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 shift_condition      : 2 ;
  uint32                      : 2 ;
  uint32 t_register_select    : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 interrupt_enable     : 1 ;

  
  uint32 data                 : 25 ;
  uint32                      : 7 ;

} SHFT_FIELDS ;      

typedef union 
{
  SHFT_FIELDS  shft   ; 
  HET_MEMORY   memory ;
} SHFT_INSTRUCTION;

/* ---------------------------------------------------------------------------------------------------- */

#elif defined(_TMS470_LITTLE) || defined(__little_endian__)

#ifndef HETBYTE
#   define HETBYTE uint8
#endif

typedef struct memory_format
{
  uint32 program_word  ;
  uint32 control_word  ;
  uint32 data_word     ;
  uint32 reserved_word ;
} HET_MEMORY  ;
 
/*---------------------------------------------*/
/* ACMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct acmp_format
{
  uint32                      : 9 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;

  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32                      : 1 ;
  uint32 pin_action           : 1 ;
  uint32                      : 3 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ; 
  uint32 en_pin_action        : 1 ;
  uint32                      : 2 ;
  uint32 coutprv              : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ; 

  uint32                      : 7  ;
  uint32 data                 : 25 ;
 
} ACMP_FIELDS;
 
typedef union
{
  ACMP_FIELDS  acmp   ;
  HET_MEMORY   memory ;
} ACMP_INSTRUCTION;


/*---------------------------------------------*/
/* ECMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct ecmp_format   
{
  uint32                      : 7 ;
  uint32 angle_compare        : 1 ;
  uint32 hr_lr                : 1 ;         
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ; 
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;

  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 pin_action           : 1 ;
  uint32 sub_opcode           : 2 ;
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32 en_pin_action        : 1 ;
  uint32                      : 3 ;
  uint32 auto_read_clear      : 1 ; 
  uint32 request              : 2 ;
  uint32                      : 3 ;
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ;

} ECMP_FIELDS;

typedef union 
{
  ECMP_FIELDS  ecmp   ;
  HET_MEMORY   memory ;
} ECMP_INSTRUCTION;


/*---------------------------------------------*/
/* SCMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct scmp_format     
{
  uint32                      : 5 ;
  uint32                      : 2 ;
  uint32                      : 2 ;         
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ; 
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;

  uint32 interrupt_enable     : 1 ;
  uint32 restart_en           : 1 ;
  uint32                      : 2 ;
  uint32 pin_action           : 1 ;
  uint32 compare_mode         : 2 ;
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32 en_pin_action        : 1 ;
  uint32                      : 2 ;
  uint32 coutprv              : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
  
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} SCMP_FIELDS ;

typedef union 
{
  SCMP_FIELDS  scmp   ;
  HET_MEMORY   memory ;
} SCMP_INSTRUCTION;


/*---------------------------------------------*/
/* MCMP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct mcmp_format                     
{
  uint32                      : 5 ;
  uint32 save_subtract        : 1 ;
  uint32                      : 1 ;
  uint32 angle_compare        : 1 ;
  uint32 hr_lr                : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;
 
  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 pin_action           : 1 ;
  uint32 order                : 1 ; 
  uint32 sub_opcode           : 1 ;  
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32 en_pin_action        : 1 ;
  uint32                      : 3 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
 
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ; 

} MCMP_FIELDS ; 

typedef union 
{
  MCMP_FIELDS  mcmp   ;
  HET_MEMORY   memory ;
} MCMP_INSTRUCTION;

/*---------------------------------------------*/
/* MOV64 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct mov64_format                     
{
  uint32 remote_address       : 9 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;          
  uint32 brk                  : 1 ;
  uint32                      : 9 ;

  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 pin_action           : 1 ;
  uint32 compare_mode         : 2 ;
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32 en_pin_action        : 1 ;
  uint32                      : 3 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ; 
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ;

} MOV64_FIELDS ; 

typedef union 
{
  MOV64_FIELDS  mov64  ;
  HET_MEMORY    memory ;
} MOV64_INSTRUCTION;


/*---------------------------------------------*/
/* DADM64 INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct dadm64_format                     
{
  uint32 remote_address       : 9 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32                      : 9 ; 

  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 pin_action           : 1 ;
  uint32 compare_mode         : 2 ;
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32 en_pin_action        : 1 ;
  uint32                      : 3 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ; 
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ;
 
} DADM64_FIELDS ; 

typedef union 
{
  DADM64_FIELDS  dadm64 ;
  HET_MEMORY     memory ;
} DADM64_INSTRUCTION;


/*---------------------------------------------*/
/* RADM64 INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct RADM64_format                     
{
  uint32 remote_address       : 9 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32                      : 9 ; 

  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 pin_action           : 1 ;
  uint32 compare_mode         : 2 ;
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32 en_pin_action        : 1 ;
  uint32                      : 3 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ; 
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ; 

} RADM64_FIELDS ; 


typedef union 
{
  RADM64_FIELDS  radm64 ;
  HET_MEMORY     memory ;
} RADM64_INSTRUCTION;


/*---------------------------------------------*/
/* MOV32 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct MOV32_format                     
{
  uint32 remote_address       : 9 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32                      : 9 ;
 
  uint32                      : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 move_type            : 2 ;
  uint32 sub_opcode           : 1 ;
  uint32 init_flag            : 1 ;
  uint32                      : 15 ;
  uint32 z_flag               : 1 ;
  uint32                      : 3 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 5 ; 
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ;
 
} MOV32_FIELDS ; 


typedef union 
{
  MOV32_FIELDS  mov32  ;
  HET_MEMORY    memory ;
} MOV32_INSTRUCTION;


/*---------------------------------------------*/
/* ADM32 INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct ADM32_format                     
{
  uint32 remote_address       : 9 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32                      : 9 ; 

  uint32                      : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 move_type            : 2 ;
  uint32 sub_opcode           : 1 ;
  uint32 init_flag            : 1 ;
  uint32                      : 19 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 5 ; 
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ;
   
} ADM32_FIELDS ; 


typedef union 
{
  ADM32_FIELDS  adm32  ;
  HET_MEMORY    memory ;
} ADM32_INSTRUCTION;


/*---------------------------------------------*/
/* ADCNST INSTRUCTION                          */
/*---------------------------------------------*/
typedef struct ADCNST_format                     
{
  uint32 remote_address       : 9 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32                      : 9 ;
 
  uint32 constant             : 25 ;
  uint32                      : 1 ;
  uint32                      : 5 ; 
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ; 

} ADCNST_FIELDS ;


typedef union 
{
  ADCNST_FIELDS  adcnst ;
  HET_MEMORY     memory ;
} ADCNST_INSTRUCTION;



/*----------------------------------------------*/
/* ADD INSTRUCTION					*/
/*----------------------------------------------*/
typedef struct ADD_format                     
{

  uint32 remote_address       : 9 ;	
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;	
  uint32                      : 9 ;

  uint32                      : 1 ;  
  uint32 reg	                : 2 ;
  uint32 rem_dest             : 2 ;
  uint32 sub_opcode1          : 1 ;
  uint32 init_flag            : 1 ;
  uint32 reg_ext              : 1 ;
  uint32 shft_cnt             : 5 ;
  uint32 shft_mode            : 3 ;
  uint32 src_2                : 3 ;
  uint32 src_1                : 4 ;
  uint32 sub_opcode3          : 3 ;
  uint32 control              : 1 ;
  uint32                      : 5 ;

  uint32 hr_data              : 7 ; 
  uint32 data                 : 25 ;
 
 
} ADD_FIELDS ;


typedef union 
{
  ADD_FIELDS  add ;
  HET_MEMORY  memory ;
} ADD_INSTRUCTION;




/*----------------------------------------------*/
/* ADC INSTRUCTION					*/
/*----------------------------------------------*/


typedef struct ADC_format                     
{

  uint32 remote_address       : 9 ;	
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;	
  uint32                      : 9 ;

  uint32                      : 1 ;  
  uint32 reg	                : 2 ;
  uint32 rem_dest             : 2 ;
  uint32 sub_opcode1          : 1 ;
  uint32 init_flag            : 1 ;
  uint32 reg_ext              : 1 ;
  uint32 shft_cnt             : 5 ;
  uint32 shft_mode            : 3 ;
  uint32 src_2                : 3 ;
  uint32 src_1                : 4 ;
  uint32 sub_opcode3          : 3 ;
  uint32 control              : 1 ;
  uint32                      : 5 ;

  uint32 hr_data              : 7 ; 
  uint32 data                 : 25 ;
 
 
} ADC_FIELDS ;


typedef union 
{
  ADC_FIELDS  adc ;
  HET_MEMORY  memory ;
} ADC_INSTRUCTION;




/*----------------------------------------------*/
/* SUB INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct SUB_format                     
{

  uint32 remote_address       : 9 ;	
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;	
  uint32                      : 9 ;

  uint32                      : 1 ;  
  uint32 reg	                : 2 ;
  uint32 rem_dest             : 2 ;
  uint32 sub_opcode1          : 1 ;
  uint32 init_flag            : 1 ;
  uint32 reg_ext              : 1 ;
  uint32 shft_cnt             : 5 ;
  uint32 shft_mode            : 3 ;
  uint32 src_2                : 3 ;
  uint32 src_1                : 4 ;
  uint32 sub_opcode3          : 3 ;
  uint32 control              : 1 ;
  uint32                      : 5 ;

  uint32 hr_data              : 7 ; 
  uint32 data                 : 25 ;
 
 
} SUB_FIELDS ;


typedef union 
{
  SUB_FIELDS  sub ;
  HET_MEMORY  memory ;
} SUB_INSTRUCTION;





/*----------------------------------------------*/
/* SBB INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct SBB_format
{

  uint32 remote_address       : 9 ;	
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;	
  uint32                      : 9 ;

  uint32                      : 1 ;  
  uint32 reg	                : 2 ;
  uint32 rem_dest             : 2 ;
  uint32 sub_opcode1          : 1 ;
  uint32 init_flag            : 1 ;
  uint32 reg_ext              : 1 ;
  uint32 shft_cnt             : 5 ;
  uint32 shft_mode            : 3 ;
  uint32 src_2                : 3 ;
  uint32 src_1                : 4 ;
  uint32 sub_opcode3          : 3 ;
  uint32 control              : 1 ;
  uint32                      : 5 ;

  uint32 hr_data              : 7 ; 
  uint32 data                 : 25 ;
 
 
} SBB_FIELDS ;


typedef union 
{
  SBB_FIELDS  sbb ;
  HET_MEMORY  memory ;
} SBB_INSTRUCTION;




/*----------------------------------------------*/
/* AND INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct AND_format
{

  uint32 remote_address       : 9 ;	
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;	
  uint32                      : 9 ;

  uint32                      : 1 ;  
  uint32 reg	                : 2 ;
  uint32 rem_dest             : 2 ;
  uint32 sub_opcode1          : 1 ;
  uint32 init_flag            : 1 ;
  uint32 reg_ext              : 1 ;
  uint32 shft_cnt             : 5 ;
  uint32 shft_mode            : 3 ;
  uint32 src_2                : 3 ;
  uint32 src_1                : 4 ;
  uint32 sub_opcode3          : 3 ;
  uint32 control              : 1 ;
  uint32                      : 5 ;

  uint32 hr_data              : 7 ; 
  uint32 data                 : 25 ;
 
 
} AND_FIELDS ;


typedef union 
{
  AND_FIELDS  and ;
  HET_MEMORY  memory ;
} AND_INSTRUCTION;



/*----------------------------------------------*/
/* OR INSTRUCTION						*/
/*----------------------------------------------*/

typedef struct OR_format
{

  uint32 remote_address       : 9 ;	
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;	
  uint32                      : 9 ;

  uint32                      : 1 ;  
  uint32 reg	                : 2 ;
  uint32 rem_dest             : 2 ;
  uint32 sub_opcode1          : 1 ;
  uint32 init_flag            : 1 ;
  uint32 reg_ext              : 1 ;
  uint32 shft_cnt             : 5 ;
  uint32 shft_mode            : 3 ;
  uint32 src_2                : 3 ;
  uint32 src_1                : 4 ;
  uint32 sub_opcode3          : 3 ;
  uint32 control              : 1 ;
  uint32                      : 5 ;

  uint32 hr_data              : 7 ; 
  uint32 data                 : 25 ;
 
 
} OR_FIELDS ;


typedef union 
{
  OR_FIELDS  or ;
  HET_MEMORY  memory ;
} OR_INSTRUCTION;



/*----------------------------------------------*/
/* XOR INSTRUCTION					*/
/*----------------------------------------------*/

typedef struct XOR_format
{

  uint32 remote_address       : 9 ;	
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;	
  uint32                      : 9 ;

  uint32                      : 1 ;  
  uint32 reg	                : 2 ;
  uint32 rem_dest             : 2 ;
  uint32 sub_opcode1          : 1 ;
  uint32 init_flag            : 1 ;
  uint32 reg_ext              : 1 ;
  uint32 shft_cnt             : 5 ;
  uint32 shft_mode            : 3 ;
  uint32 src_2                : 3 ;
  uint32 src_1                : 4 ;
  uint32 sub_opcode3          : 3 ;
  uint32 control              : 1 ;
  uint32                      : 5 ;

  uint32 hr_data              : 7 ; 
  uint32 data                 : 25 ;
 
 
} XOR_FIELDS ;


typedef union 
{
  XOR_FIELDS  xor ;
  HET_MEMORY  memory ;
} XOR_INSTRUCTION;




/*---------------------------------------------*/
/* CNT INSTRUCTION                             */
/*---------------------------------------------*/
typedef struct CNT_format                     
{
  uint32 interrupt_enable     : 1 ;         
  uint32                      : 4 ;        
  uint32 ab_register_select   : 1 ;          
  uint32 t_register_select    : 1 ;
  uint32 angle_cnt            : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;  
  uint32                      : 9 ;  

  uint32 max                  : 25 ;
  uint32                      : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
  
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} CNT_FIELDS ; 

typedef union 
{
  CNT_FIELDS   cnt    ; 
  HET_MEMORY   memory ;
} CNT_INSTRUCTION;


/*---------------------------------------------*/
/* APCNT INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct apcnt_format
{
  uint32                      : 6 ;
  uint32 edge_select          : 2 ;
  uint32 interrupt_enable     : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;

  uint32 count                : 25 ;
  uint32 previous_bit         : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ; 
  
  uint32                      : 7 ;
  uint32 data                 : 25 ; 

} APCNT_FIELDS ;
 
typedef union
{
  APCNT_FIELDS  apcnt   ;
  HET_MEMORY   memory ;
} APCNT_INSTRUCTION;
 
 

/*---------------------------------------------*/
/* PCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct pcnt_format                     
{
  uint32 pin_select           : 5 ;
  uint32                      : 1 ;
  uint32 period_pulse_select  : 2 ;          
  uint32 interrupt_enable     : 1 ;          
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;

  uint32 count                : 25 ;
  uint32 previous_bit         : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ;

} PCNT_FIELDS ;      

typedef union 
{
  PCNT_FIELDS  pcnt   ; 
  HET_MEMORY   memory ;
} PCNT_INSTRUCTION;


/*---------------------------------------------*/
/* SCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct scnt_format                     
{
  uint32                      : 4 ;
  uint32 step_width           : 2 ;
  uint32 count_mode           : 2 ;
  uint32                      : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32                      : 9 ;

  uint32 gap_start            : 25 ;
  uint32                      : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32                      : 5 ;
  
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} SCNT_FIELDS ;      

typedef union 
{
  SCNT_FIELDS  scnt   ; 
  HET_MEMORY   memory ;
} SCNT_INSTRUCTION;

/*---------------------------------------------*/
/* ACNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct acnt_format                     
{
  uint32 interrupt_enable     : 1 ; 
  uint32                      : 7 ;
  uint32 edge_select          : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;

  uint32 gap_end              : 25 ;
  uint32 previous_bit         : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ; 
  
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} ACNT_FIELDS ;      

typedef union 
{
  ACNT_FIELDS  acnt   ; 
  HET_MEMORY   memory ;
} ACNT_INSTRUCTION;


/*---------------------------------------------*/
/* ECNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct ecnt_format
{
  uint32                      : 6 ;
  uint32 count_mode           : 2 ;
  uint32                      : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;
 
  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32                      : 1 ;
  uint32 count_cond           : 3 ;
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32                      : 3 ;
  uint32 previous_bit         : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
  
  uint32                      : 7 ;
  uint32 data                 : 25 ; 
 

} ECNT_FIELDS ;
 
typedef union
{
  ECNT_FIELDS  ecnt   ;
  HET_MEMORY   memory ;
} ECNT_INSTRUCTION;

/*---------------------------------------------*/
/* RCNT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct rcnt_format
{

  uint32 count_mode1          : 1 ;
  uint32                      : 5 ;
  uint32 count_mode           : 2 ;
  uint32                      : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;


  uint32 divisor              : 25 ;  
  uint32                      : 1 ;
  uint32 control              : 1 ;
  uint32                      : 2 ;
  uint32                      : 3 ;

  uint32                      : 7 ;  
  uint32 data                 : 25 ;

 
} RCNT_FIELDS ;
 
typedef union
{
  RCNT_FIELDS  rcnt   ;
  HET_MEMORY   memory ;
} RCNT_INSTRUCTION;


/*---------------------------------------------*/
/* DJNZ INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct djnz_format                     
{
  uint32                      : 6 ;
  uint32 sub_opcode           : 2 ;
  uint32                      : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ; 
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;

  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32                      : 10 ;
  uint32 cond_addr            : 9 ;
  uint32                      : 4 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
  
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} DJNZ_FIELDS ;      

typedef union 
{
  DJNZ_FIELDS  djnz   ; 
  HET_MEMORY   memory ;
} DJNZ_INSTRUCTION;


/*---------------------------------------------*/
/* DJZ INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct djz_format                     
{
  uint32                      : 6 ;
  uint32 sub_opcode           : 2 ;
  uint32                      : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ; 
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;

  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32                      : 10 ;
  uint32 cond_addr            : 9 ;
  uint32                      : 4 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
  
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} DJZ_FIELDS ;      

typedef union 
{
  DJZ_FIELDS  djz   ; 
  HET_MEMORY   memory ;
} DJZ_INSTRUCTION;

/*---------------------------------------------*/
/* PWCNT INSTRUCTION                           */
/*---------------------------------------------*/
typedef struct pwcnt_format                     
{
  uint32                      : 6 ;
  uint32 count_mode           : 2 ;
  uint32 hr_lr                : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;

  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32 opposite_action      : 1 ;
  uint32 pin_action           : 1 ;
  uint32                      : 3 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32 en_pin_action        : 1 ;
  uint32                      : 3 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
  

  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ;  
 
} PWCNT_FIELDS ;      

typedef union 
{
  PWCNT_FIELDS  pwcnt ;
  HET_MEMORY   memory ;
} PWCNT_INSTRUCTION;


/*---------------------------------------------*/
/* WCAP INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct wcap_format                     
{
  uint32                      : 8 ;
  uint32 hr_lr                : 1 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ; 
  
  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32                      : 2 ;
  uint32 capture_condition    : 2 ;
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32                      : 3 ;
  uint32 previous_bit         : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ;

} WCAP_FIELDS ;      

typedef union 
{
  WCAP_FIELDS  wcap   ; 
  HET_MEMORY   memory ;
} WCAP_INSTRUCTION;
 
/*----------------------------------------------*/
/* WCAPE INSTRUCTION                            */
/*----------------------------------------------*/
typedef struct wcape_format                     
{
  uint32                      : 9 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;  

  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32                      : 2 ;
  uint32 capture_condition    : 2 ;
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32 previous_bit         : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
  
  uint32 ec_data              : 7 ;
  uint32 ts_data              : 25 ;

} WCAPE_FIELDS ;      

typedef union 
{
  WCAPE_FIELDS  wcape   ; 
  HET_MEMORY   memory ;
} WCAPE_INSTRUCTION;
 

/*---------------------------------------------*/
/* BR   INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct br_format                     
{
  uint32                      : 9 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ;

  uint32 interrupt_enable     : 1 ;
  uint32                      : 2 ;
  uint32                      : 1 ;
  uint32                      : 1 ;
  uint32 branch_condition     : 3 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32                      : 3 ;
  uint32 previous_bit         : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ; 
  
  uint32 hr_data              : 7 ;
  uint32 data                 : 25 ;

} BR_FIELDS ;      

typedef union 
{
  BR_FIELDS  br     ; 
  HET_MEMORY memory ;
} BR_INSTRUCTION;

 
/*---------------------------------------------*/
/* SHFT INSTRUCTION                            */
/*---------------------------------------------*/
typedef struct shft_format                     
{
  uint32 shift_mode           : 4 ;
  uint32                      : 5 ;
  uint32 op_code              : 4 ;
  uint32 next_program_address : 9 ;
  uint32 brk                  : 1 ;
  uint32 reqnum               : 3 ;
  uint32                      : 6 ; 

  uint32 interrupt_enable     : 1 ;
  uint32 ab_register_select   : 1 ;
  uint32 t_register_select    : 1 ;
  uint32                      : 2 ;
  uint32 shift_condition      : 2 ;
  uint32                      : 1 ;
  uint32 pin_select           : 5 ;
  uint32 cond_addr            : 9 ;
  uint32                      : 3 ;
  uint32 previous_bit         : 1 ;
  uint32 auto_read_clear      : 1 ;
  uint32 request              : 2 ;
  uint32                      : 3 ;
  
  uint32                      : 7 ;
  uint32 data                 : 25 ;

} SHFT_FIELDS ;      

typedef union 
{
  SHFT_FIELDS  shft   ; 
  HET_MEMORY   memory ;
} SHFT_INSTRUCTION;

#endif

#endif
/*--------------------------- End Of File ----------------------------------*/
