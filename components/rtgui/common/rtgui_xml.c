#include <rtgui/rtgui_xml.h>
#include <rtgui/rtgui_system.h>

/* Internal states that the parser can be in at any given time. */
enum
{
    STAT_START = 0,         /* starting base state, default state */
    STAT_TEXT,              /* text state */
    STAT_START_TAG,         /* start tag state */
    STAT_START_TAGNAME,     /* start tagname state */
    STAT_START_TAGNAME_END, /* start tagname ending state */
    STAT_END_TAG,           /* end tag state */
    STAT_END_TAGNAME,       /* end tag tagname state */
    STAT_END_TAGNAME_END,   /* end tag tagname ending */
    STAT_EMPTY_TAG,         /* empty tag state */
    STAT_SPACE,             /* linear whitespace state */
    STAT_ATTR_NAME,         /* attribute name state */
    STAT_ATTR_NAME_END,     /* attribute name ending state */
    STAT_ATTR_VAL,          /* attribute value starting state */
    STAT_ATTR_VAL2,         /* attribute value state */
    STAT_ERROR              /* error state */
};

/* character classes that we will match against; This could be expanded if
   need be, however, we are aiming for simple. */
enum
{
    CLASS_TYPE_NONE = 0,       /* matches nothing, a base state */
    CLASS_TYPE_LEFT_ANGLE,     /* matches start tag '<' */
    CLASS_TYPE_SLASH,          /* matches forward slash */
    CLASS_TYPE_RIGHT_ANGLE,    /* matches end tag '>' */
    CLASS_TYPE_EQUALS,         /* matches equals sign */
    CLASS_TYPE_QUOTE,          /* matches double-quotes */
    CLASS_TYPE_LETTERS,        /* matches a-zA-Z letters and digits 0-9 */
    CLASS_TYPE_SPACE,          /* matches whitespace */
    CLASS_TYPE_ANY             /* matches any ASCII character; will match all
                                above classes */
};

/* xml state transition table */
struct rtgui_xml_state
{
    rt_uint8_t state;
    rt_uint8_t class_type;
    rt_uint8_t next_state;
    rt_uint8_t event;
};

/* Note: States must be grouped in match order AND grouped together! */
static const struct rtgui_xml_state RTGUI_XML_STATES [] =
{
    /* [0-2] starting state, which also serves as the default state in case
      of error */
    { STAT_START,         CLASS_TYPE_SPACE,        STAT_SPACE,             EVENT_NONE },
    { STAT_START,         CLASS_TYPE_LEFT_ANGLE,   STAT_START_TAG,         EVENT_NONE },
    { STAT_START,         CLASS_TYPE_ANY,          STAT_TEXT,              EVENT_COPY },

    /* [3-5] space state handles linear white space */
    { STAT_SPACE,         CLASS_TYPE_SPACE,        STAT_SPACE,             EVENT_NONE },
    { STAT_SPACE,         CLASS_TYPE_LEFT_ANGLE,   STAT_START_TAG,         EVENT_TEXT },
    { STAT_SPACE,         CLASS_TYPE_ANY,          STAT_TEXT,              EVENT_COPY },

    /* [6-8] handle start tag */
    { STAT_START_TAG,     CLASS_TYPE_LETTERS,      STAT_START_TAGNAME,     EVENT_COPY },
    { STAT_START_TAG,     CLASS_TYPE_SLASH,        STAT_END_TAG,           EVENT_COPY },
    /* below added since some individuals get a little carried away with
      spacing around tag names, e.g. < tag > */
    { STAT_START_TAG,     CLASS_TYPE_SPACE,        STAT_START_TAG,         EVENT_NONE },

    /* [9-12] handle start tag name */
    { STAT_START_TAGNAME, CLASS_TYPE_LETTERS,      STAT_START_TAGNAME,     EVENT_NONE },
    { STAT_START_TAGNAME, CLASS_TYPE_SPACE,        STAT_START_TAGNAME_END, EVENT_START },
    /* below added for tags without any space between tag and ending
      slash, e.g., <br/> */
    { STAT_START_TAGNAME, CLASS_TYPE_SLASH,        STAT_EMPTY_TAG,         EVENT_END },
    { STAT_START_TAGNAME, CLASS_TYPE_RIGHT_ANGLE,  STAT_START,             EVENT_START },

    /* [13-16] handle start tag name end */
    { STAT_START_TAGNAME_END,  CLASS_TYPE_LETTERS, STAT_ATTR_NAME,         EVENT_COPY },
    /* below added to handle additional space in between attribute value
      pairs in start tags, e.g., <tag attr="2" attr2="test" > */
    { STAT_START_TAGNAME_END,  CLASS_TYPE_SPACE,   STAT_START_TAGNAME_END, EVENT_NONE },
    { STAT_START_TAGNAME_END,  CLASS_TYPE_RIGHT_ANGLE, STAT_START,         EVENT_START },
    /* below supports tags that are self-closing, e.g., <br /> */
    { STAT_START_TAGNAME_END,  CLASS_TYPE_SLASH,   STAT_EMPTY_TAG,         EVENT_COPY },

    /* [17] handle empty tags, e.g., <br /> */
    { STAT_EMPTY_TAG,     CLASS_TYPE_RIGHT_ANGLE,  STAT_START,             EVENT_END },

    /* [18] handle end tag, e.g., <tag /> */
    { STAT_END_TAG,       CLASS_TYPE_LETTERS,      STAT_END_TAGNAME,       EVENT_NONE },

    /* [19-21] handle end tag name */
    { STAT_END_TAGNAME,   CLASS_TYPE_LETTERS,      STAT_END_TAGNAME,       EVENT_NONE },
    { STAT_END_TAGNAME,   CLASS_TYPE_RIGHT_ANGLE,  STAT_START,             EVENT_END },
    /* below adds support for spaces at the end of an end tag (before
      closing bracket) */
    { STAT_END_TAGNAME,   CLASS_TYPE_SPACE,        STAT_END_TAGNAME_END,   EVENT_END },

    /* [22] handle ending of end tag name */
    { STAT_END_TAGNAME_END, CLASS_TYPE_SPACE,      STAT_END_TAGNAME_END,   EVENT_NONE },
    { STAT_END_TAGNAME_END, CLASS_TYPE_RIGHT_ANGLE, STAT_START,             EVENT_NONE },

    /* [23-25] handle text */
    { STAT_TEXT,          CLASS_TYPE_SPACE,        STAT_SPACE,             EVENT_NONE },
    { STAT_TEXT,          CLASS_TYPE_LEFT_ANGLE,   STAT_START_TAG,         EVENT_TEXT },
    { STAT_TEXT,          CLASS_TYPE_ANY,          STAT_TEXT,              EVENT_NONE },

    /* [26-30] handle attribute names */
    { STAT_ATTR_NAME,     CLASS_TYPE_LETTERS,      STAT_ATTR_NAME,         EVENT_COPY },
    /* below add support for space before the equals sign, e.g, <tag
      attr ="2"> */
    { STAT_ATTR_NAME,     CLASS_TYPE_SPACE,        STAT_ATTR_NAME_END,     EVENT_NAME },
    { STAT_ATTR_NAME,     CLASS_TYPE_EQUALS,       STAT_ATTR_VAL,          EVENT_NAME },

    /* [31-33] attribute name end */
    { STAT_ATTR_NAME_END, CLASS_TYPE_SPACE,        STAT_ATTR_NAME_END,     EVENT_NONE },
    { STAT_ATTR_NAME_END, CLASS_TYPE_LETTERS,      STAT_ATTR_NAME,         EVENT_COPY },
    { STAT_ATTR_NAME_END, CLASS_TYPE_EQUALS,       STAT_ATTR_VAL,          EVENT_NONE },

    /* [34-35] handle attribute values, initial quote and spaces */
    { STAT_ATTR_VAL,      CLASS_TYPE_QUOTE,        STAT_ATTR_VAL2,         EVENT_NONE },
    /* below handles initial spaces before quoted attribute value */
    { STAT_ATTR_VAL,      CLASS_TYPE_SPACE,        STAT_ATTR_VAL,          EVENT_NONE },

    /* [36-37] handle actual attribute values */
    { STAT_ATTR_VAL2,     CLASS_TYPE_QUOTE,        STAT_START_TAGNAME_END, EVENT_VAL  },
    { STAT_ATTR_VAL2,     CLASS_TYPE_LETTERS,      STAT_ATTR_VAL2,         EVENT_COPY },
    { STAT_ATTR_VAL2,     CLASS_TYPE_SLASH,        STAT_ATTR_VAL2,         EVENT_NONE },

    /* End of table marker */
    { STAT_ERROR,         CLASS_TYPE_NONE,         STAT_ERROR,             EVENT_NONE }
};

struct rtgui_xml
{
    /* event handler */
    rtgui_xml_event_handler_t event_handler;
    void *user;

    char *buffer;               /* xml buffer */
    rt_size_t buffer_size;      /* buffer size */
    rt_size_t position;         /* current position in buffer */
    rt_uint16_t state, event;   /* current state and event */

    rt_bool_t copy;             /* copy text into tmp buffer */
    rt_bool_t halt;             /* halt parsing of document */
};

rtgui_xml_t *rtgui_xml_create(rt_size_t buffer_size, rtgui_xml_event_handler_t handler,
                              void *user)
{
    rtgui_xml_t *xml = (rtgui_xml_t *) rtgui_malloc(sizeof(struct rtgui_xml));
    rt_memset(xml, 0, sizeof(rtgui_xml_t));

    xml->event_handler = handler;
    xml->user = user;

    /* create buffer */
    xml->buffer_size = buffer_size;
    xml->buffer = (char *)rtgui_malloc(xml->buffer_size);
    return xml;
}

void rtgui_xml_destroy(rtgui_xml_t *xml)
{
    if (xml)
    {
        rtgui_free(xml->buffer);
        rtgui_free(xml);
    }
}

const char *rtgui_xml_event_str(rt_uint8_t event)
{
    switch (event)
    {
    case EVENT_START:
        return "start tag";
    case EVENT_END:
        return "end tag";
    case EVENT_TEXT:
        return "text";
    case EVENT_NAME:
        return "attr name";
    case EVENT_VAL:
        return "attr val";
    case EVENT_END_DOC:
        return "end document";
    default:
        break;
    }
    return "err";
}

int rtgui_xml_parse(rtgui_xml_t *xml, const char *buf, rt_size_t len)
{
    int i, j, c, match;

#define is_space(ch)    \
    ((rt_uint32_t)(ch - 9) < 5u  ||  ch == ' ')
#define is_alpha(ch)    \
    ((rt_uint32_t)((ch | 0x20) - 'a') < 26u)
#define is_digit(ch)    \
    ((rt_uint32_t)(ch - '0') < 10u)
#define is_letters(ch)  \
    (is_alpha(ch) || is_digit(ch) || (ch == '.'))

    for (i = 0; i < len; i++)
    {
        if (xml->halt) break;

        c = buf[i] & 0xff;

        /* search in state table */
        for (j = 0, match = 0; RTGUI_XML_STATES[j].state != STAT_ERROR; j++)
        {
            if (RTGUI_XML_STATES[j].state != xml->state)
                continue;

            switch (RTGUI_XML_STATES[j].class_type)
            {
            case CLASS_TYPE_LETTERS:
                match = is_letters(c);
                break;
            case CLASS_TYPE_LEFT_ANGLE:
                match = (c == '<');
                break;
            case CLASS_TYPE_SLASH:
                match = (c == '/');
                break;
            case CLASS_TYPE_RIGHT_ANGLE:
                match = (c == '>');
                break;
            case CLASS_TYPE_EQUALS:
                match = (c == '=');
                break;
            case CLASS_TYPE_QUOTE:
                match = (c == '"');
                break;
            case CLASS_TYPE_SPACE:
                match = is_space(c);
                break;
            case CLASS_TYPE_ANY:
                match = 1;
                break;
            default:
                break;
            }

            /* we matched a character class */
            if (match)
            {
                if (RTGUI_XML_STATES[j].event == EVENT_COPY)
                {
                    xml->copy = RT_TRUE;
                }
                else if (RTGUI_XML_STATES[j].event != EVENT_NONE)
                {
                    if (xml->copy == RT_TRUE)
                    {
                        /* basically we are guaranteed never to have an event of
                           type EVENT_COPY or EVENT_NONE here. */
                        xml->event = RTGUI_XML_STATES[j].event;
                        xml->buffer[xml->position] = 0; /* make a string */

                        if (!xml->event_handler(RTGUI_XML_STATES[j].event,
                                                xml->buffer, xml->position ,
                                                xml->user))
                        {
                            xml->halt = 1; /* stop parsing from here out */
                        }
                        xml->position = 0;
                        xml->copy = RT_FALSE;
                    }
                }
                if (xml->copy == RT_TRUE)
                {
                    /* check to see if we have room; one less for trailing
                       nul */
                    if (xml->position < xml->buffer_size - 1)
                    {
                        xml->buffer[xml->position] = buf[i];
                        xml->position++;
                    }
                }
                xml->state = RTGUI_XML_STATES[j].next_state; /* change state */
                break; /* break out of loop though state search */
            }
        }
    }

    return !xml->halt;
}
