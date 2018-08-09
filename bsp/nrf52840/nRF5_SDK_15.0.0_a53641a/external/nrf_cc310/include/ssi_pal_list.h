/**************************************************************************************
* Copyright (c) 2016-2017, ARM Limited or its affiliates. All rights reserved         *
*                                                                                     *
* This file and the related binary are licensed under the following license:          *
*                                                                                     *
* ARM Object Code and Header Files License, v1.0 Redistribution.                      *
*                                                                                     *
* Redistribution and use of object code, header files, and documentation, without     *
* modification, are permitted provided that the following conditions are met:         *
*                                                                                     *
* 1) Redistributions must reproduce the above copyright notice and the                *
*    following disclaimer in the documentation and/or other materials                 *
*    provided with the distribution.                                                  *
*                                                                                     *
* 2) Unless to the extent explicitly permitted by law, no reverse                     *
*    engineering, decompilation, or disassembly of is permitted.                      *
*                                                                                     *
* 3) Redistribution and use is permitted solely for the purpose of                    *
*    developing or executing applications that are targeted for use                   *
*    on an ARM-based product.                                                         *
*                                                                                     *
* DISCLAIMER. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                  *
* CONTRIBUTORS "AS IS." ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT             *
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT,        *
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED            *
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR              *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF              *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                  *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                        *
**************************************************************************************/


#ifndef  _SSI_PAL_LIST_H
#define  _SSI_PAL_LIST_H


typedef struct SaSi_PalListItem {
    struct SaSi_PalListItem *prev;
    struct SaSi_PalListItem *next;
} SaSi_PalListItem_s;

/*!
 * Initializes a list. Prev/Next points to the same head object.
 *
 * \param head The head of the list.
 */
static inline void SaSi_PalListInit(SaSi_PalListItem_s *head)
{
    head->prev = head;
    head->next = head;
}

/*!
 * Add a new list item after head of list.
 *
 * \param new New entry to be added
 * \param head List head to add it after
 */
static inline void SaSi_PalListAdd(SaSi_PalListItem_s *new, SaSi_PalListItem_s *head)
{
    SaSi_PalListItem_s *next = head->next;

    next->prev = new;
    new->next = next;
    new->prev = head;
    head->next = new;
}

/*!
 * Add a new list item after head of list.
 *
 * \param new New entry to be added
 * \param head List head to add it after
 */
static inline void SaSi_PalListAddTail(SaSi_PalListItem_s *new, SaSi_PalListItem_s *head)
{
    SaSi_PalListItem_s *prev = head->prev;

    prev->next = new;
    new->next = head;
    new->prev = prev;
    head->prev = new;
}

/*!
 * Deletes entry from list.
 *
 * \param item The item to delete from the list.
 */
static inline void SaSi_PalListDel(SaSi_PalListItem_s *item)
{
    SaSi_PalListItem_s *prev = item->prev;
    SaSi_PalListItem_s *next = item->next;

    prev->next = next;
    next->prev = prev;

    item->next = item;
    item->prev = item;
}

/*!
 * Checks whether a list is empty.
 *
 * \param head The list's head
 *
 * \return int True if empty list, False otherwise.
 */
static inline int SaSi_PalIsListEmpty(const SaSi_PalListItem_s *head)
{
    return (head->next == head);
}

#endif

