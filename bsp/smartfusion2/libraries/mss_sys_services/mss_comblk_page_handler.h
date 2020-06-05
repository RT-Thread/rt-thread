/*******************************************************************************
 * (c) Copyright 2012-2016 Microsemi SoC Products Group.  All rights reserved.
 *
 * SmartFusion2 MSS COM block driver, page handler callback function prototype.
 *
 * SVN $Revision: 8345 $
 * SVN $Date: 2016-03-23 11:53:04 +0530 (Wed, 23 Mar 2016) $
 */

#ifndef __MSS_COMBLK_PAGE_HANDLER_H_
#define __MSS_COMBLK_PAGE_HANDLER_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------*//**
  The comblk_page_handler_t typedef specifies the function prototype of a COMBLK
  page handler callback function. This callback is used by the system services
  and COMBLK drivers as part of in-system programming (ISP) to retrieve the next
  page of programming information to send to the SmartFusion2 System Controller
  via the COMBLK.
  The COMBLK page handler must be implemented by the application layer to return
  the address of the next page of programming data to be sent to the
  SmartFusion2 system controller. It must return the number of bytes contained
  in the next page. Returning a value of zero indicates that all programming
  data has been passed to the system services/COMBLK drivers.
  
  @code
    #define PAGE_LENGTH 512
    
    uint8_t programming_data[PROG_DATA_LENGTH];
    uint32_t prog_data_index = 0;
    
    uint32_t page_read_handler
    (
        uint8_t const ** pp_next_page
    )
    {
        uint32_t returned_page_length;
        uint32_t remaining_length;

        *pp_next_page = &programming_data[prog_data_index];
        remaining_length = PROG_DATA_LENGTH - prog_data_index
        if(remaining_length > PAGE_LENGTH)
        {
            returned_page_length = PAGE_LENGTH;
        }
        else
        {
            returned_page_length = remaining_length;
            prog_data_index = PROG_DATA_LENGTH;
        }
        
        return returned_page_length;
    }

  @endcode
 */
typedef uint32_t (*comblk_page_handler_t)(uint8_t const ** pp_next_page);

#ifdef __cplusplus
}
#endif

#endif  /* __MSS_COMBLK_PAGE_HANDLER_H_ */
