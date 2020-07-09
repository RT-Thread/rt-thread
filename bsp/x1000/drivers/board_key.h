#ifndef BOARD_KEY_H__
#define BOARD_KEY_H__

#ifndef RT_USING_AUDIO_PLAYER
enum KEY_VALUE
{
    KEY_VOLINC,
    KEY_VOLDEC,
    KEY_NEXT,
    KEY_PREV,

    KEY_PAUSE,
    KEY_PLAY,
    KEY_PLAY_PAUSE,

    KEY_MUTE,

    KEY_MIC,
    KEY_EQ,
    KEY_MENU,
    KEY_CHANNEL,
    KEY_FAVORITE,

    //system shutdown, wifi config...
    KEY_PWROFF,
    KEY_CONFIG,
    KEY_NETWORK_MODE,

    KEY_SOURCE,
    KEY_UNKNOWN,
};
#endif

struct keyboard_io_def
{
    enum gpio_port  port;
    enum gpio_pin   pin;

    int  longKey;
    int  shortKey;
};

typedef void (*keyboard_event_handler_t)(uint32_t event);

void rt_hw_keyboard_init(void);
void rt_hw_keyboard_set_handler(keyboard_event_handler_t handler);

#endif
