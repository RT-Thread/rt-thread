/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file menu.c
 * @brief Menu Framework for application UI.
 * @ingroup diag_utility
 */

#include <stdio.h>
#include <string.h>
#include "sdk.h"
#include "text_color.h"
#include "menu.h"

////////////////////////////////////////////////////////////////////////////////
// Private Menu Framework Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Specialized menu_key_find() return values.
//@{
static const int MenuKeyFindNone = -2;         //!< menu_key_find() did not find any menuitems with a matching key.
static const int MenuKeyFindMoreThanOne = -1;  //!< menu_key_find() found more than one menuitem with a matching key.
static char MenuIndent[MENU_INDENT_MAX+1] = {0};
//@}

////////////////////////////////////////////////////////////////////////////////
// Private Menu Framework Utility Functions
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Returns the number of menuitems in the menu.
 *
 * Counts all menuitems including MENUITEM_GROUP menuitems which are not
 * selectable. The count does not include the terminating MENUITEM_NULL element.
 *
 * @param   menu A pointer to the menu structure holding the menuitems to be counted.
 * @return  Number of menuitems.
 */
static int menu_get_size(const menu_t* menu)
{
    int menuitem_count = 0;

    const menuitem_t* menuitem = menu->menuitems;
    while (menuitem->type != MenuItem_Null)
    {
        ++menuitem_count;
        ++menuitem;
    }

    return menuitem_count;
}

/*!
 * @brief Searches the menu for menuitems that start with the key parameter.
 *
 * @note Search is not case sensitive.
 *
 * @param   menu A pointer to the menu structure holding the menuitems to be searched.
 * @param   key A pointer to search string used to identify a menuitem.
 * @retval  Index of the only menuitem that starts with the key parameter.
 * @retval  MenuKeyFindNone(-2) if a matching menuitem was not found.
 * @return  MenuKeyFindMoreThanOne(-1) if more than one matching menuitem was found.
 *          Call menu_key_find_first() to get the first matching index.
 */
static int menu_key_find(const menu_t* menu, const char* key)
{
    int menuitem_found = MenuKeyFindNone;
    int num_found = 0;
    int menu_size = menu_get_size(menu);
    int index = 0;

    for (index = 0; index < menu_size; ++index)
    {
        // Only consider selectable menuitems
        if (menu->menuitems[index].key == NULL)
            continue;

        // Search is not case sensitive.
        if (strncasecmp(key, menu->menuitems[index].key, strlen(key)) == 0)
        {
            if (menuitem_found == MenuKeyFindNone)
                menuitem_found = index;

            ++num_found;
        }
    }

    return num_found == 0 ? MenuKeyFindNone :
           num_found > 1 ? MenuKeyFindMoreThanOne : menuitem_found;
}

/*!
 * @brief Returns the index of the first menuitem that starts with the key parameter.
 *
 * @note Search is not case sensitive.
 * @note This function would typically be called after menu_find_key() returned MenuKeyFindMoreThanOne.
 *
 * @param   menu A pointer to the menu structure holding the menuitems to be searched.
 * @param   key A pointer to search string used to identify a menuitem.
 * @retval  Index of the first menuitem that starts with the key parameter.
 * @retval  MenuKeyFindNone(-2) if a matching menuitem was not found.
 */
static int menu_key_find_first(const menu_t* menu, const char* key)
{
    int menuitem_found = MenuKeyFindNone;
    int menu_size = menu_get_size(menu);
    int index = 0;

    for (index = 0; index < menu_size; ++index)
    {
        // Only consider selectable menuitems
        if (menu->menuitems[index].key == NULL)
            continue;

        // Search is not case sensitive.
        if (strncasecmp(key, menu->menuitems[index].key, strlen(key)) == 0)
        {
            menuitem_found = index;
            break;
        }
    }

    return menuitem_found;

}

/*!
 * @brief Print the menu description (header), all of the menuitems, and instructions to the user (footer).
 *
 * @param   indent String used to align text for the current menu level.
 * @param   menu Pointer to the menu to print.
 */
static void menu_print(const char* indent, const menu_t* menu)
{
    if (menu->header)
        printf("\n%s%s\n\n", indent, menu->header);

    const menuitem_t* menuitem = menu->menuitems;
    while (menuitem->type != MenuItem_Null)
    {

        switch (menuitem->type)
        {
            case MenuItem_Submenu:
            case MenuItem_Function:
            {
                printf("%s%s%s%s%s - %s\n", indent, g_TextAttributeBold,
                        g_TextColorMagenta, menuitem->key,
                        g_TextAttributeDefault, menuitem->description);

                break;
            }

            case MenuItem_Group:
            {
                if (menuitem->description)
                    printf("\n%s%s%s%s:%s\n", indent, g_TextAttributeBold,
                            g_TextColorBlue, menuitem->description,
                            g_TextAttributeDefault);
                else
                    printf("\n");

                break;
            }

            case MenuItem_Null:
            default:
            {
                break;
            }

        } // switch(menuitem->type)

        ++menuitem;

    } // while ( menuitem->type != MENUITEM_NULL )

    if (menu->footer)
        printf("\n%s%s\n", indent, menu->footer);

} // menu_print()

/*!
 * @brief Print instructional text to help user execute the menu.
 *
 * @param   indent String used to align text for the current menu level.
 * @param   menu Pointer to the menu struct that contains the footer member to print.
 * @return  MENU_EXIT.
 */
static void menu_print_footer(const char* indent, const menu_t* menu)
{
    if (menu->footer)
        printf("\n%s%s\n", indent, menu->footer);
    else
        printf("\n");
}

////////////////////////////////////////////////////////////////////////////////
// Public Menu API Implementations
////////////////////////////////////////////////////////////////////////////////
const char* menu_get_indent() { return MenuIndent; }
menu_action_t menuitem_cmd_showmenu(void* param) { return MenuAction_Show; }
menu_action_t menuitem_cmd_exitmenu(void* param) { return MenuAction_Exit; }

int menu_append_menuitems(menuitem_t* target_menuitems, int target_size, const menuitem_t* source_menuitems)
{
//    printf("target_menuitems = 0x%08X\n", target_menuitems);
//    printf("target_size      = %d\n", target_size);
//    printf("source_menuitems = 0x%08X\n", source_menuitems);

    int target_idx = 0;
    int source_size = 0;

    // Move to the end of the target
    while(target_menuitems[target_idx].type != MenuItem_Null) ++target_idx;
//    printf("target_idx       = %d\n", target_idx);

    // Get source size
    while(source_menuitems[source_size].type != MenuItem_Null) ++source_size;
    ++source_size;
//    printf("source_size      = %d\n", source_size);

    // Check available size
    if ( (target_size - target_idx) < source_size)
        return -1; // can't do the append

    // Copy source to target
    memcpy(&target_menuitems[target_idx], source_menuitems, source_size * sizeof(menuitem_t));

//    printf("target_size      = %d\n", target_idx + source_size);
    return target_idx + source_size;
}
/*
void menu_make_menu(menu_t* menu, const char* header,
        const menuitem_t* menuitems, const char* footer)
{
    menu->header = header;
    menu->menuitems = menuitems;
    menu->footer = footer;
}

 void menu_make_menuitem(menuitem_t* menuitem, const char* key, const char* description, menu_function_t func, void* func_param)
 {
 menuitem->type              = MenuItem_Function;
 menuitem->key               = key;
 menuitem->description       = description;
 menuitem->submenu           = NULL;
 menuitem->func_ptr          = func;
 menuitem->func_param        = func_param;
 }

 void menu_make_menuitem_showmenu(menuitem_t* menuitem)
 {
 menuitem->type              = MenuItem_Function;
 menuitem->key               = "m";
 menuitem->description       = "Display menu.";
 menuitem->submenu           = NULL;
 menuitem->func_ptr          = menuitem_cmd_showmenu;
 menuitem->func_param        = NULL;
 }

 void menu_make_menuitem_exitmenu(menuitem_t* menuitem)
 {
 menuitem->type              = MenuItem_Function;
 menuitem->key               = "q";
 menuitem->description       = "Exit menu.";
 menuitem->submenu           = NULL;
 menuitem->func_ptr          = menuitem_cmd_exitmenu;
 menuitem->func_param        = NULL;
 }

 void menu_make_menuitem_submenu(menuitem_t* menuitem, const char* key, const char* description, const menu_t* menu)
 {
 menuitem->type              = MenuItem_Submenu;
 menuitem->key               = key;
 menuitem->description       = description;
 menuitem->submenu           = menu;
 }

 void menu_make_menuitem_group(menuitem_t* menuitem, const char* description)
 {
 menuitem->type              = MenuItem_Group;
 menuitem->key               = NULL;
 menuitem->description       = description;
 menuitem->submenu           = NULL;
 menuitem->func_ptr          = NULL;
 menuitem->func_param        = NULL;
 }

 void menu_make_menuitem_end(menuitem_t* menuitem)
 {
 menuitem->type              = MenuItem_Null;
 menuitem->key               = NULL;
 menuitem->description       = NULL;
 menuitem->func_ptr          = NULL;
 menuitem->func_param        = NULL;
 }
*/

menu_action_t menu_present(const menu_t* menu)
{
    menu_action_t ret_val = MenuAction_Exit;
    static int depth = -1;
    memset(MenuIndent, ' ', MENU_INDENT_MAX + 1);

    ++depth;

    int indent_idx = MENU_INDENT * depth + 2;
    if (indent_idx > MENU_INDENT_MAX)
    {
        printf_color(g_TextAttributeBold, g_TextColorRed, "\nERROR: MENU depth is to large. Exiting menu_present().");
        return MenuAction_Exit;
    }
    MenuIndent[indent_idx] = '\0';

    menu_print(MenuIndent, menu);

    while (1) // processing menu selections
    {
        while (getchar() != NONE_CHAR); // empty key buffer
        char key[MENU_KEY_MAX];
        memset(key, 0, MENU_KEY_MAX);
        int key_idx = 0;
        char key_pressed = NONE_CHAR;
        int menu_idx = MenuKeyFindNone;

        while (1) // getting user input to specify which menu_idx to run
        {
            // get a key press
            while ((key_pressed = getchar()) == NONE_CHAR);

            if (key_pressed == '\n' || key_pressed == '\r')
            {
                ///
                /// User hit ENTER_KEY
                ///

                // if previously MenuKeyFindMoreThanOne
                // then run 1st matching menuitem
                if (menu_idx == MenuKeyFindMoreThanOne)
                {
                    // we need to run menu_idx
                    menu_idx = menu_key_find_first(menu, key);
                    break;
                }
                else
                {
                    printf_color(NULL, g_TextColorYellow, "\n%sInvalid key.\n", MenuIndent);
                    menu_print_footer(MenuIndent, menu);

                    // start over with user input
                    key[key_idx] = '\0';
                    while (key_idx > 0)
                        key[--key_idx] = '\0';
                    continue;
                }
            }
            else
            {
                ///
                /// User hit something other than ENTER_KEY
                ///

                // Echo the key
                fputc(key_pressed, stdout);

                key[key_idx++] = key_pressed;

                menu_idx = menu_key_find(menu, key);

                if (menu_idx == MenuKeyFindNone)
                {
                    printf_color(NULL, g_TextColorYellow, "\n%sInvalid key.\n", MenuIndent);
                    menu_print_footer(MenuIndent, menu);

                    // start over with user input
                    while (key_idx > 0)
                        key[--key_idx] = '\0';
                    continue;
                }
                else if (menu_idx == MenuKeyFindMoreThanOne)
                {
                    // we need more input
                    continue;
                }
                else
                {
                    // we need to run menu_idx
                    break;
                }

            } // user hit something other than ENTER_KEY

        } // while (1) - getting user input to specify which menu item to run

        printf("\n");

        ///
        /// Execute the menu item.
        ///
        const menuitem_t* menuitem = &menu->menuitems[menu_idx];

        if (menuitem->type == MenuItem_Submenu)
        {
            ret_val = menu_present(menuitem->submenu);
        }
        else if (menuitem->type == MenuItem_Function)
        {
            ret_val = (*menuitem->func_ptr)(menuitem->func_param);
        }

        ///
        /// Evaluate the response.
        ///
        if (ret_val == MenuAction_Show)
        {
            menu_print(MenuIndent, menu);
        }
        else if (ret_val == MenuAction_Continue)
        {
            menu_print_footer(MenuIndent, menu);
        }
        else if (ret_val == MenuAction_ContinuePrint)
        {
            menu_print(MenuIndent, menu);
        }
        else if (ret_val == MenuAction_Back)
        {
            ret_val = MenuAction_ContinuePrint;
            break;
        }
        else if (ret_val == MenuAction_Exit)
        {
            if (depth == 0)
                printf_color(NULL, g_TextColorYellow, "\n%sExiting menu.\n", MenuIndent);
            break;
        }

    } // while (1) - process menu items

    --depth;

    return ret_val;

} // menu_action_t menu_present(const menu_t* menu)

void menu_print_menuitem(menuitem_t* menuitem)
{
    printf("menuitem->type        = %d\n", menuitem->type);
    printf("menuitem->key         = %s\n", menuitem->key);
    printf("menuitem->description = %s\n", *menuitem->description);
    printf("menuitem->submenu     = 0x%08X\n", menuitem->submenu);
    printf("menuitem->func_ptr    = 0x%08X\n", menuitem->func_ptr);
    printf("menuitem->func_param  = 0x%08X\n", menuitem->func_param);
}

