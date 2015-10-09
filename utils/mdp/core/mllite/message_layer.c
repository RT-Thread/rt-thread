/*
 $License:
    Copyright (C) 2011-2012 InvenSense Corporation, All Rights Reserved.
    See included License.txt for License information.
 $
 */
/**
 *   @defgroup  Message_Layer message_layer
 *   @brief     Motion Library - Message Layer
 *              Holds Low Occurance messages
 *
 *   @{
 *       @file message_layer.c
 *       @brief Holds Low Occurance Messages.
 */
#include "message_layer.h"
#include "log.h"

struct message_holder_t {
    long message;
};

static struct message_holder_t mh;

/** Sets a message.
* @param[in] set The flags to set.
* @param[in] clear Before setting anything this will clear these messages,
*                  which is useful for mutually exclusive messages such
*                  a motion or no motion message.
* @param[in] level Level of the messages. It starts at 0, and may increase
*            in the future to allow more messages if the bit storage runs out.
*/
void inv_set_message(long set, long clear, int level)
{
    if (level == 0) {
        mh.message &= ~clear;
        mh.message |= set;
    }
}

/** Returns Message Flags for Level 0 Messages.
* Levels are to allow expansion of more messages in the future.
* @param[in] clear If set, will clear the message. Typically this will be set
*  for one reader, so that you don't get the same message over and over.
* @return bit field to corresponding message.
*/
long inv_get_message_level_0(int clear)
{
    long msg;
    msg = mh.message;
    if (clear) {
        mh.message = 0;
    }
    return msg;
}

/**
 * @}
 */
