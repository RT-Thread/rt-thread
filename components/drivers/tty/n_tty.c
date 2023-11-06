/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021.12.07     linzhenxing      first version
 */
#include <stddef.h>
#include <ctype.h>
#include <tty.h>
#include <lwp.h>
#if defined(RT_USING_POSIX_TERMIOS)
#include <termios.h>
#endif
#include <sys/errno.h>

#define DBG_TAG               "N_TTY"
#ifdef RT_TTY_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_TTY_DEBUG */
#include <rtdbg.h>

/* number of characters left in xmit buffer before select has we have room */
#define WAKEUP_CHARS 256

/*
 * This defines the low- and high-watermarks for throttling and
 * unthrottling the TTY driver.  These watermarks are used for
 * controlling the space in the read buffer.
 */
#define TTY_THRESHOLD_THROTTLE      128 /* now based on remaining room */
#define TTY_THRESHOLD_UNTHROTTLE    128

/*
 * Special byte codes used in the echo buffer to represent operations
 * or special handling of characters.  Bytes in the echo buffer that
 * are not part of such special blocks are treated as normal character
 * codes.
 */
#define ECHO_OP_START 0xff
#define ECHO_OP_MOVE_BACK_COL 0x80
#define ECHO_OP_SET_CANON_COL 0x81
#define ECHO_OP_ERASE_TAB 0x82

#define ECHO_COMMIT_WATERMARK   256
#define ECHO_BLOCK      256
#define ECHO_DISCARD_WATERMARK  RT_TTY_BUF - (ECHO_BLOCK + 32)

static struct rt_spinlock _spinlock = RT_SPINLOCK_INIT;

struct n_tty_data
{
    /* producer-published */
    size_t read_head;
    size_t commit_head;
    size_t canon_head;
    size_t echo_head;
    size_t echo_commit;
    size_t echo_mark;
    unsigned long char_map[256];

    /* non-atomic */
    rt_bool_t no_room;
    /* must hold exclusive termios_rwsem to reset these */
    unsigned char lnext:1, erasing:1, raw:1, real_raw:1, icanon:1;
    unsigned char push:1;

    /* shared by producer and consumer */
    char read_buf[RT_TTY_BUF];
    unsigned long read_flags[RT_TTY_BUF];
    unsigned char echo_buf[RT_TTY_BUF];

    /* consumer-published */
    size_t read_tail;
    size_t line_start;

    /* protected by output lock */
    unsigned int column;
    unsigned int canon_column;
    size_t echo_tail;

    rt_mutex_t atomic_read_lock;
    rt_mutex_t output_lock;
};

rt_inline int set_bit(int nr,int *addr)
{
    int mask, retval;
    rt_base_t level;

    addr += nr >> 5;
    mask = 1 << (nr & 0x1f);
    level = rt_spin_lock_irqsave(&_spinlock);
    retval = (mask & *addr) != 0;
    *addr |= mask;
    rt_spin_unlock_irqrestore(&_spinlock, level);
    return retval;
}

rt_inline int clear_bit(int nr, int *addr)
{
    int mask, retval;
    rt_base_t level;

    addr += nr >> 5;
    mask = 1 << (nr & 0x1f);
    level = rt_spin_lock_irqsave(&_spinlock);
    retval = (mask & *addr) != 0;
    *addr &= ~mask;
    rt_spin_unlock_irqrestore(&_spinlock, level);
    return retval;
}

rt_inline int test_bit(int nr, int *addr)
{
    int mask;

    addr += nr >> 5;
    mask = 1 << (nr & 0x1f);
    return ((mask & *addr) != 0);
}

rt_inline int test_and_clear_bit(int nr, volatile void *addr)
{
    int mask, retval;
    rt_base_t level;
    volatile unsigned int *a = addr;

    a += nr >> 5;
    mask = 1 << (nr & 0x1f);
    level = rt_spin_lock_irqsave(&_spinlock);
    retval = (mask & *a) != 0;
    *a &= ~mask;
    rt_spin_unlock_irqrestore(&_spinlock, level);

    return retval;
}

#ifdef __GNUC__
rt_inline unsigned long __ffs(unsigned long word)
{
    return __builtin_ffsl(word);
}
#else
rt_inline unsigned long __ffs(unsigned long word)
{
    int num = 0;

#if BITS_PER_LONG == 64
    if ((word & 0xffffffff) == 0)
    {
        num += 32;
        word >>= 32;
    }
#endif
    if ((word & 0xffff) == 0)
    {
        num += 16;
        word >>= 16;
    }
    if ((word & 0xff) == 0)
    {
        num += 8;
        word >>= 8;
    }
    if ((word & 0xf) == 0)
    {
        num += 4;
        word >>= 4;
    }
    if ((word & 0x3) == 0)
    {
        num += 2;
        word >>= 2;
    }
    if ((word & 0x1) == 0)
    {
        num += 1;
    }

    return num;
}
#endif

#define BITS_PER_LONG       32
#define BITOP_WORD(nr)      ((nr) / BITS_PER_LONG)

/*
 * Find the next set bit in a memory region.
 */
rt_inline unsigned long find_next_bit(const unsigned long *addr, unsigned long size,
                unsigned long offset)
{
    const unsigned long *p = addr + BITOP_WORD(offset);
    unsigned long result = offset & ~(BITS_PER_LONG-1);
    unsigned long tmp;

    if (offset >= size)
    {
        return size;
    }

    size -= result;
    offset %= BITS_PER_LONG;
    if (offset)
    {
        tmp = *(p++);
        tmp &= (~0UL << offset);
        if (size < BITS_PER_LONG)
        {
            goto found_first;
        }

        if (tmp)
        {
            goto found_middle;
        }

        size -= BITS_PER_LONG;
        result += BITS_PER_LONG;
    }

    while (size & ~(BITS_PER_LONG-1))
    {
        if ((tmp = *(p++)))
        {
            goto found_middle;
        }

        result += BITS_PER_LONG;
        size -= BITS_PER_LONG;
    }

    if (!size)
    {
        return result;
    }

    tmp = *p;

found_first:
    tmp &= (~0UL >> (BITS_PER_LONG - size));
    if (tmp == 0UL)     /* Are any bits set? */
    {
        return result + size;   /* Nope. */
    }

found_middle:
    return result + __ffs(tmp);
}

rt_inline void tty_sigaddset(lwp_sigset_t *set, int _sig)
{
    unsigned long sig = _sig - 1;

    if (_LWP_NSIG_WORDS == 1)
    {
        set->sig[0] |= 1UL << sig;
    }
    else
    {
        set->sig[sig / _LWP_NSIG_BPW] |= 1UL << (sig % _LWP_NSIG_BPW);
    }
}

rt_inline size_t read_cnt(struct n_tty_data *ldata)
{
    return ldata->read_head - ldata->read_tail;
}

rt_inline char read_buf(struct n_tty_data *ldata, size_t i)
{
    return ldata->read_buf[i & (RT_TTY_BUF - 1)];
}

rt_inline char *read_buf_addr(struct n_tty_data *ldata, size_t i)
{
    return &ldata->read_buf[i & (RT_TTY_BUF - 1)];
}

rt_inline unsigned char echo_buf(struct n_tty_data *ldata, size_t i)
{
    return ldata->echo_buf[i & (RT_TTY_BUF - 1)];
}

rt_inline unsigned char *echo_buf_addr(struct n_tty_data *ldata, size_t i)
{
    return &ldata->echo_buf[i & (RT_TTY_BUF - 1)];
}

/**
 *  put_tty_queue       -   add character to tty
 *  @c: character
 *  @ldata: n_tty data
 *
 *  Add a character to the tty read_buf queue.
 *
 *  n_tty_receive_buf()/producer path:
 *      caller holds non-exclusive termios_rwsem
 */
rt_inline void put_tty_queue(unsigned char c, struct n_tty_data *ldata)
{
    *read_buf_addr(ldata, ldata->read_head) = c;
    ldata->read_head++;
}

/**
 *  reset_buffer_flags  -   reset buffer state
 *  @tty: terminal to reset
 *
 *  Reset the read buffer counters and clear the flags.
 *  Called from n_tty_open() and n_tty_flush_buffer().
 *
 *  Locking: caller holds exclusive termios_rwsem
 *       (or locking is not required)
 */

static void reset_buffer_flags(struct n_tty_data *ldata)
{
    ldata->read_head = ldata->canon_head = ldata->read_tail = 0;
    ldata->echo_head = ldata->echo_tail = ldata->echo_commit = 0;
    ldata->commit_head = 0;
    ldata->echo_mark = 0;
    ldata->line_start = 0;

    ldata->erasing = 0;
    rt_memset(ldata->read_flags, 0, RT_TTY_BUF);
    ldata->push = 0;
}

/**
 *  add_echo_byte   -   add a byte to the echo buffer
 *  @c: unicode byte to echo
 *  @ldata: n_tty data
 *
 *  Add a character or operation byte to the echo buffer.
 */

rt_inline void add_echo_byte(unsigned char c, struct n_tty_data *ldata)
{
    *echo_buf_addr(ldata, ldata->echo_head++) = c;
}

/**
 *  echo_move_back_col  -   add operation to move back a column
 *  @ldata: n_tty data
 *
 *  Add an operation to the echo buffer to move back one column.
 */

static void echo_move_back_col(struct n_tty_data *ldata)
{
    add_echo_byte(ECHO_OP_START, ldata);
    add_echo_byte(ECHO_OP_MOVE_BACK_COL, ldata);
}

/**
 *  echo_set_canon_col  -   add operation to set the canon column
 *  @ldata: n_tty data
 *
 *  Add an operation to the echo buffer to set the canon column
 *  to the current column.
 */

static void echo_set_canon_col(struct n_tty_data *ldata)
{
    add_echo_byte(ECHO_OP_START, ldata);
    add_echo_byte(ECHO_OP_SET_CANON_COL, ldata);
}

/**
 *  echo_erase_tab  -   add operation to erase a tab
 *  @num_chars: number of character columns already used
 *  @after_tab: true if num_chars starts after a previous tab
 *  @ldata: n_tty data
 *
 *  Add an operation to the echo buffer to erase a tab.
 *
 *  Called by the eraser function, which knows how many character
 *  columns have been used since either a previous tab or the start
 *  of input.  This information will be used later, along with
 *  canon column (if applicable), to go back the correct number
 *  of columns.
 */

static void echo_erase_tab(unsigned int num_chars, int after_tab,
               struct n_tty_data *ldata)
{
    add_echo_byte(ECHO_OP_START, ldata);
    add_echo_byte(ECHO_OP_ERASE_TAB, ldata);

    /* We only need to know this modulo 8 (tab spacing) */
    num_chars &= 7;

    /* Set the high bit as a flag if num_chars is after a previous tab */
    if (after_tab)
    {
        num_chars |= 0x80;
    }

    add_echo_byte(num_chars, ldata);
}

/**
 *  echo_char_raw   -   echo a character raw
 *  @c: unicode byte to echo
 *  @tty: terminal device
 *
 *  Echo user input back onto the screen. This must be called only when
 *  L_ECHO(tty) is true. Called from the driver receive_buf path.
 *
 *  This variant does not treat control characters specially.
 */

static void echo_char_raw(unsigned char c, struct n_tty_data *ldata)
{
    if (c == ECHO_OP_START)
    {
        add_echo_byte(ECHO_OP_START, ldata);
        add_echo_byte(ECHO_OP_START, ldata);
    }
    else
    {
        add_echo_byte(c, ldata);
    }
}

/**
 *  echo_char   -   echo a character
 *  @c: unicode byte to echo
 *  @tty: terminal device
 *
 *  Echo user input back onto the screen. This must be called only when
 *  L_ECHO(tty) is true. Called from the driver receive_buf path.
 *
 *  This variant tags control characters to be echoed as "^X"
 *  (where X is the letter representing the control char).
 */

static void echo_char(unsigned char c, struct tty_struct *tty)
{
    struct n_tty_data *ldata = tty->disc_data;

    if (c == ECHO_OP_START)
    {
        add_echo_byte(ECHO_OP_START, ldata);
        add_echo_byte(ECHO_OP_START, ldata);
    }
    else
    {
        if (L_ECHOCTL(tty) && iscntrl(c) && c != '\t')
        {
            add_echo_byte(ECHO_OP_START, ldata);
        }
        add_echo_byte(c, ldata);
    }
}

/**
 *  finish_erasing      -   complete erase
 *  @ldata: n_tty data
 */

rt_inline void finish_erasing(struct n_tty_data *ldata)
{
    if (ldata->erasing)
    {
        echo_char_raw('/', ldata);
        ldata->erasing = 0;
    }
}

/**
 *  is_utf8_continuation    -   utf8 multibyte check
 *  @c: byte to check
 *
 *  Returns true if the utf8 character 'c' is a multibyte continuation
 *  character. We use this to correctly compute the on screen size
 *  of the character when printing
 */

rt_inline int is_utf8_continuation(unsigned char c)
{
    return (c & 0xc0) == 0x80;
}

/**
 *  is_continuation     -   multibyte check
 *  @c: byte to check
 *
 *  Returns true if the utf8 character 'c' is a multibyte continuation
 *  character and the terminal is in unicode mode.
 */

rt_inline int is_continuation(unsigned char c, struct tty_struct *tty)
{
    return I_IUTF8(tty) && is_utf8_continuation(c);
}

/**
 *  eraser      -   handle erase function
 *  @c: character input
 *  @tty: terminal device
 *
 *  Perform erase and necessary output when an erase character is
 *  present in the stream from the driver layer. Handles the complexities
 *  of UTF-8 multibyte symbols.
 *
 *  n_tty_receive_buf()/producer path:
 *      caller holds non-exclusive termios_rwsem
 */

static void eraser(unsigned char c, struct tty_struct *tty)
{
    struct n_tty_data *ldata = tty->disc_data;
    enum { KERASE, WERASE, KILL } kill_type;
    size_t head = 0;
    size_t cnt = 0;
    int seen_alnums = 0;

    if (ldata->read_head == ldata->canon_head)
    {
        /* process_output('\a', tty); */ /* what do you think? */
        return;
    }

    if (c == ERASE_CHAR(tty))
    {
        kill_type = KERASE;
    }
    else if (c == WERASE_CHAR(tty))
    {
        kill_type = WERASE;
    }
    else
    {
        if (!L_ECHO(tty))
        {
            ldata->read_head = ldata->canon_head;
            return;
        }

        if (!L_ECHOK(tty) || !L_ECHOKE(tty) || !L_ECHOE(tty))
        {
            ldata->read_head = ldata->canon_head;
            finish_erasing(ldata);
            echo_char(KILL_CHAR(tty), tty);
            /* Add a newline if ECHOK is on and ECHOKE is off. */
            if (L_ECHOK(tty))
            {
                echo_char_raw('\n', ldata);
            }
            return;
        }
        kill_type = KILL;
    }

    seen_alnums = 0;
    while (ldata->read_head != ldata->canon_head)
    {
        head = ldata->read_head;

        /* erase a single possibly multibyte character */
        do
        {
            head--;
            c = read_buf(ldata, head);
        } while (is_continuation(c, tty) && head != ldata->canon_head);

        /* do not partially erase */
        if (is_continuation(c, tty))
        {
            break;
        }

        if (kill_type == WERASE)
        {
            /* Equivalent to BSD's ALTWERASE. */
            if (isalnum(c) || c == '_')
            {
                seen_alnums++;
            }
            else if (seen_alnums)
            {
                break;
            }
        }
        cnt = ldata->read_head - head;
        ldata->read_head = head;
        if (L_ECHO(tty))
        {
            if (L_ECHOPRT(tty))
            {
                if (!ldata->erasing)
                {
                    echo_char_raw('\\', ldata);
                    ldata->erasing = 1;
                }
                /* if cnt > 1, output a multi-byte character */
                echo_char(c, tty);
                while (--cnt > 0)
                {
                    head++;
                    echo_char_raw(read_buf(ldata, head), ldata);
                    echo_move_back_col(ldata);
                }
            }
            else if (kill_type == KERASE && !L_ECHOE(tty))
            {
                echo_char(ERASE_CHAR(tty), tty);
            }
            else if (c == '\t')
            {
                unsigned int num_chars = 0;
                int after_tab = 0;
                size_t tail = ldata->read_head;

                /*
                 * Count the columns used for characters
                 * since the start of input or after a
                 * previous tab.
                 * This info is used to go back the correct
                 * number of columns.
                 */
                while (tail != ldata->canon_head)
                {
                    tail--;
                    c = read_buf(ldata, tail);
                    if (c == '\t')
                    {
                        after_tab = 1;
                        break;
                    }
                    else if (iscntrl(c))
                    {
                        if (L_ECHOCTL(tty))
                        {
                            num_chars += 2;
                        }
                    }
                    else if (!is_continuation(c, tty))
                    {
                        num_chars++;
                    }
                }
                echo_erase_tab(num_chars, after_tab, ldata);
            }
            else
            {
                if (iscntrl(c) && L_ECHOCTL(tty))
                {
                    echo_char_raw('\b', ldata);
                    echo_char_raw(' ', ldata);
                    echo_char_raw('\b', ldata);
                }
                if (!iscntrl(c) || L_ECHOCTL(tty))
                {
                    echo_char_raw('\b', ldata);
                    echo_char_raw(' ', ldata);
                    echo_char_raw('\b', ldata);
                }
            }
        }
        if (kill_type == KERASE)
        {
            break;
        }
    }
    if (ldata->read_head == ldata->canon_head && L_ECHO(tty))
    {
        finish_erasing(ldata);
    }
}

/**
 *  isig        -   handle the ISIG optio
 *  @sig: signal
 *  @tty: terminal
 *
 *  Called when a signal is being sent due to terminal input.
 *  Called from the driver receive_buf path so serialized.
 *
 *  Performs input and output flush if !NOFLSH. In this context, the echo
 *  buffer is 'output'. The signal is processed first to alert any current
 *  readers or writers to discontinue and exit their i/o loops.
 *
 *  Locking: ctrl_lock
 */

static void __isig(int sig, struct tty_struct *tty)
{
    struct rt_lwp *lwp = tty->foreground;
    struct tty_ldisc *ld = RT_NULL;
    struct termios old_termios;
    struct termios *new_termios = get_old_termios();

    if (lwp)
    {
        if (sig == SIGTSTP)
        {
            struct rt_lwp *old_lwp;

            rt_memcpy(&old_termios, &(tty->init_termios), sizeof(struct termios));
            tty->init_termios = *new_termios;
            ld = tty->ldisc;
            if (ld != RT_NULL)
            {
                if (ld->ops->set_termios)
                {
                    ld->ops->set_termios(tty, &old_termios);
                }
            }
            lwp_signal_kill(lwp, SIGTTOU, SI_USER, 0);
            old_lwp = tty_pop(&tty->head, RT_NULL);
            tty->foreground = old_lwp;
        }
        else
        {
            lwp_signal_kill(lwp, sig, SI_USER, 0);
        }
    }
}

static void isig(int sig, struct tty_struct *tty)
{
    struct n_tty_data *ldata = tty->disc_data;

    if (L_NOFLSH(tty))
    {
        /* signal only */
        __isig(sig, tty);

    }
    else
    { /* signal and flush */
        __isig(sig, tty);

        /* clear echo buffer */
        ldata->echo_head = ldata->echo_tail = 0;
        ldata->echo_mark = ldata->echo_commit = 0;

        /* clear input buffer */
        reset_buffer_flags(tty->disc_data);
    }
}

/**
 *  do_output_char          -   output one character
 *  @c: character (or partial unicode symbol)
 *  @tty: terminal device
 *  @space: space available in tty driver write buffer
 *
 *  This is a helper function that handles one output character
 *  (including special characters like TAB, CR, LF, etc.),
 *  doing OPOST processing and putting the results in the
 *  tty driver's write buffer.
 *
 *  Note that Linux currently ignores TABDLY, CRDLY, VTDLY, FFDLY
 *  and NLDLY.  They simply aren't relevant in the world today.
 *  If you ever need them, add them here.
 *
 *  Returns the number of bytes of buffer space used or -1 if
 *  no space left.
 *
 *  Locking: should be called under the output_lock to protect
 *       the column state and space left in the buffer
 */

static int do_output_char(unsigned char c, struct tty_struct *tty)
{
    struct n_tty_data *ldata = tty->disc_data;
    int spaces = 0;
    char *ch = RT_NULL;

    switch (c)
    {
    case '\n':
        if (O_ONLRET(tty))
        {
            ldata->column = 0;
        }

        if (O_ONLCR(tty))
        {
            ldata->canon_column = ldata->column = 0;
            ch = "\r\n";
            rt_device_write((rt_device_t)tty, -1, ch, 2);
            return 2;
        }
        ldata->canon_column = ldata->column;
        break;
    case '\r':
        if (O_ONOCR(tty) && ldata->column == 0)
        {
            return 0;
        }

        if (O_OCRNL(tty))
        {
            c = '\n';
            if (O_ONLRET(tty))
            {
                ldata->canon_column = ldata->column = 0;
            }
            break;
        }
        ldata->canon_column = ldata->column = 0;
        break;
    case '\t':
        spaces = 8 - (ldata->column & 7);
        if (O_TABDLY(tty) == XTABS)
        {
            ldata->column += spaces;
            ch = "        ";
            rt_device_write((rt_device_t)tty, -1, &ch, spaces);
            return spaces;
        }
        ldata->column += spaces;
        break;
    case '\b':
        if (ldata->column > 0)
        {
            ldata->column--;
        }
        ch = "\b \b";
        rt_device_write((rt_device_t)tty, -1, ch, strlen(ch));
        return 1;
    default:
        if (!iscntrl(c))
        {
            if (O_OLCUC(tty))
            {
                c = toupper(c);
            }

            if (!is_continuation(c, tty))
            {
                ldata->column++;
            }
        }
        break;
    }

    rt_device_write((rt_device_t)tty, -1, &c, 1);
    return 1;
}

/**
 *  process_output          -   output post processor
 *  @c: character (or partial unicode symbol)
 *  @tty: terminal device
 *
 *  Output one character with OPOST processing.
 *  Returns -1 when the output device is full and the character
 *  must be retried.
 *
 *  Locking: output_lock to protect column state and space left
 *       (also, this is called from n_tty_write under the
 *        tty layer write lock)
 */

static int process_output(unsigned char c, struct tty_struct *tty)
{
    int retval = 0;

    retval = do_output_char(c, tty);
    if (retval < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/**
 *  process_output_block        -   block post processor
 *  @tty: terminal device
 *  @buf: character buffer
 *  @nr: number of bytes to output
 *
 *  Output a block of characters with OPOST processing.
 *  Returns the number of characters output.
 *
 *  This path is used to speed up block console writes, among other
 *  things when processing blocks of output data. It handles only
 *  the simple cases normally found and helps to generate blocks of
 *  symbols for the console driver and thus improve performance.
 *
 *  Locking: output_lock to protect column state and space left
 *       (also, this is called from n_tty_write under the
 *        tty layer write lock)
 */

static ssize_t process_output_block(struct tty_struct *tty,
                    const char *buf, unsigned int nr)
{
    struct n_tty_data *ldata = tty->disc_data;
    int i = 0;
    ssize_t size = 0;
    const char *cp = RT_NULL;

    for (i = 0, cp = buf; i < nr; i++, cp++)
    {
        char c = *cp;

        switch (c)
        {
        case '\n':
            if (O_ONLRET(tty))
            {
                ldata->column = 0;
            }

            if (O_ONLCR(tty))
            {
                goto break_out;
            }
            ldata->canon_column = ldata->column;
            break;
        case '\r':
            if (O_ONOCR(tty) && ldata->column == 0)
            {
                goto break_out;
            }

            if (O_OCRNL(tty))
            {
                goto break_out;
            }

            ldata->canon_column = ldata->column = 0;
            break;
        case '\t':
            goto break_out;
        case '\b':
            if (ldata->column > 0)
            {
                ldata->column--;
            }
            break;
        default:
            if (!iscntrl(c))
            {
                if (O_OLCUC(tty))
                {
                    goto break_out;
                }

                if (!is_continuation(c, tty))
                {
                    ldata->column++;
                }
            }
            break;
        }
    }
break_out:
    size = rt_device_write((rt_device_t)tty, -1, buf, i);
    return size;
}

static size_t __process_echoes(struct tty_struct *tty)
{
    struct n_tty_data *ldata = tty->disc_data;
    size_t tail = 0;
    unsigned char c = 0;
    char ch = 0;
    unsigned char num_chars = 0, num_bs = 0;

    tail = ldata->echo_tail;
    while (ldata->echo_commit != tail)
    {
        c = echo_buf(ldata, tail);
        if (c == ECHO_OP_START)
        {
            unsigned char op = 0;

            /*
             * If the buffer byte is the start of a multi-byte
             * operation, get the next byte, which is either the
             * op code or a control character value.
             */
            op = echo_buf(ldata, tail + 1);

            switch (op)
            {
            case ECHO_OP_ERASE_TAB:
                num_chars = echo_buf(ldata, tail + 2);

                /*
                 * Determine how many columns to go back
                 * in order to erase the tab.
                 * This depends on the number of columns
                 * used by other characters within the tab
                 * area.  If this (modulo 8) count is from
                 * the start of input rather than from a
                 * previous tab, we offset by canon column.
                 * Otherwise, tab spacing is normal.
                 */
                if (!(num_chars & 0x80))
                {
                    num_chars += ldata->canon_column;
                }
                num_bs = 8 - (num_chars & 7);

                while (num_bs--)
                {
                    ch = '\b';
                    rt_device_write((rt_device_t)tty, -1, &ch, 1);
                    if (ldata->column > 0)
                    {
                        ldata->column--;
                    }
                }
                tail += 3;
                break;

            case ECHO_OP_SET_CANON_COL:
                ldata->canon_column = ldata->column;
                tail += 2;
                break;

            case ECHO_OP_MOVE_BACK_COL:
                if (ldata->column > 0)
                {
                    ldata->column--;
                }
                tail += 2;
                break;

            case ECHO_OP_START:
                ch = ECHO_OP_START;
                rt_device_write((rt_device_t)tty, -1, &ch, 1);
                ldata->column++;
                tail += 2;
                break;

            default:
                /*
                 * If the op is not a special byte code,
                 * it is a ctrl char tagged to be echoed
                 * as "^X" (where X is the letter
                 * representing the control char).
                 * Note that we must ensure there is
                 * enough space for the whole ctrl pair.
                 *
                 */
                ch = '^';
                rt_device_write((rt_device_t)tty, -1, &ch, 1);
                ch = op ^ 0100;
                rt_device_write((rt_device_t)tty, -1, &ch, 1);
                ldata->column += 2;
                tail += 2;
            }
        }
        else
        {
            if (O_OPOST(tty))
            {
                int retval = do_output_char(c, tty);
                if (retval < 0)
                {
                    break;
                }
            }
            else
            {
                rt_device_write((rt_device_t)tty, -1, &c, 1);
            }
            tail += 1;
        }
    }

    /* If the echo buffer is nearly full (so that the possibility exists
     * of echo overrun before the next commit), then discard enough
     * data at the tail to prevent a subsequent overrun */
    while (ldata->echo_commit - tail >= ECHO_DISCARD_WATERMARK)
    {
        if (echo_buf(ldata, tail) == ECHO_OP_START)
        {
            if (echo_buf(ldata, tail + 1) == ECHO_OP_ERASE_TAB)
            {
                tail += 3;
            }
            else
            {
                tail += 2;
            }
        }
        else
        {
            tail++;
        }
    }

    ldata->echo_tail = tail;
    return 0;
}

static void commit_echoes(struct tty_struct *tty)
{
    struct n_tty_data *ldata = tty->disc_data;
    size_t nr = 0, old = 0;
    size_t head = 0;

    head = ldata->echo_head;
    ldata->echo_mark = head;
    old = ldata->echo_commit - ldata->echo_tail;

    /* Process committed echoes if the accumulated # of bytes
     * is over the threshold (and try again each time another
     * block is accumulated) */
    nr = head - ldata->echo_tail;
    if (nr < ECHO_COMMIT_WATERMARK || (nr % ECHO_BLOCK > old % ECHO_BLOCK))
    {
        return;
    }

    ldata->echo_commit = head;
    __process_echoes(tty);
}

static void process_echoes(struct tty_struct *tty)
{
    struct n_tty_data *ldata = tty->disc_data;

    if (ldata->echo_mark == ldata->echo_tail)
    {
        return;
    }

    ldata->echo_commit = ldata->echo_mark;
    __process_echoes(tty);
}

/* NB: echo_mark and echo_head should be equivalent here */
static void flush_echoes(struct tty_struct *tty)
{
    struct n_tty_data *ldata = tty->disc_data;

    if ((!L_ECHO(tty) && !L_ECHONL(tty)) ||
        ldata->echo_commit == ldata->echo_head)
    {
        return;
    }

    ldata->echo_commit = ldata->echo_head;
    __process_echoes(tty);
}
/**
 *  n_tty_set_termios   -   termios data changed
 *  @tty: terminal
 *  @old: previous data
 *
 *  Called by the tty layer when the user changes termios flags so
 *  that the line discipline can plan ahead. This function cannot sleep
 *  and is protected from re-entry by the tty layer. The user is
 *  guaranteed that this function will not be re-entered or in progress
 *  when the ldisc is closed.
 *
 *  Locking: Caller holds tty->termios_rwsem
 */

static void n_tty_set_termios(struct tty_struct *tty, struct termios *old)
{
    struct n_tty_data *ldata = tty->disc_data;

    if (!old || (old->c_lflag ^ tty->init_termios.c_lflag) & (ICANON | EXTPROC))
    {
        rt_memset(ldata->read_flags, 0, RT_TTY_BUF);
        ldata->line_start = ldata->read_tail;
        if (!L_ICANON(tty) || !read_cnt(ldata))
        {
            ldata->canon_head = ldata->read_tail;
            ldata->push = 0;
        }
        else
        {
            set_bit((ldata->read_head - 1) & (RT_TTY_BUF - 1),(int *)ldata->read_flags);
            ldata->canon_head = ldata->read_head;
            ldata->push = 1;
        }
        ldata->commit_head = ldata->read_head;
        ldata->erasing = 0;
        ldata->lnext = 0;
    }

    ldata->icanon = (L_ICANON(tty) != 0);

    if (I_ISTRIP(tty) || I_IUCLC(tty) || I_IGNCR(tty) ||
        I_ICRNL(tty) || I_INLCR(tty) || L_ICANON(tty) ||
        I_IXON(tty) || L_ISIG(tty) || L_ECHO(tty) ||
        I_PARMRK(tty))
    {
        rt_memset(ldata->char_map, 0, 256);
        if (I_IGNCR(tty) || I_ICRNL(tty))
        {
            set_bit('\r', (int *)ldata->char_map);
        }

        if (I_INLCR(tty))
        {
            set_bit('\n', (int *)ldata->char_map);
        }

        if (L_ICANON(tty))
        {
            set_bit(ERASE_CHAR(tty), (int *)ldata->char_map);
            set_bit(KILL_CHAR(tty),(int *) ldata->char_map);
            set_bit(EOF_CHAR(tty), (int *)ldata->char_map);
            set_bit('\n',(int *) ldata->char_map);
            set_bit(EOL_CHAR(tty),(int *) ldata->char_map);
            if (L_IEXTEN(tty))
            {
                set_bit(WERASE_CHAR(tty), (int *)ldata->char_map);
                set_bit(LNEXT_CHAR(tty), (int *)ldata->char_map);
                set_bit(EOL2_CHAR(tty), (int *)ldata->char_map);
                if (L_ECHO(tty))
                {
                    set_bit(REPRINT_CHAR(tty),
                        (int *)ldata->char_map);
                }
            }
        }
        if (I_IXON(tty))
        {
            set_bit(START_CHAR(tty), (int *)ldata->char_map);
            set_bit(STOP_CHAR(tty), (int *)ldata->char_map);
        }
        if (L_ISIG(tty))
        {
            set_bit(INTR_CHAR(tty), (int *)ldata->char_map);
            set_bit(QUIT_CHAR(tty), (int *)ldata->char_map);
            set_bit(SUSP_CHAR(tty), (int *)ldata->char_map);
        }
        clear_bit(__DISABLED_CHAR, (int *)ldata->char_map);
        ldata->raw = 0;
        ldata->real_raw = 0;
    }
    else
    {
        ldata->raw = 1;
        if ((I_IGNBRK(tty) || (!I_BRKINT(tty) && !I_PARMRK(tty))) &&
            (I_IGNPAR(tty) || !I_INPCK(tty))/* &&
            (tty->driver->flags & TTY_DRIVER_REAL_RAW)*/)
        {
            ldata->real_raw = 1;
        }
        else
        {
            ldata->real_raw = 0;
        }
    }
}

void console_ldata_init(struct tty_struct *tty)
{
    struct n_tty_data *ldata = RT_NULL;

    ldata = rt_malloc(sizeof(struct n_tty_data));
    if (ldata == RT_NULL)
    {
        LOG_E("console_ldata_init ldata malloc fail");
        return;
    }
    tty->disc_data = ldata;
    reset_buffer_flags(ldata);
    ldata->column = 0;
    ldata->canon_column = 0;
    ldata->no_room = 0;
    ldata->lnext = 0;
    n_tty_set_termios(tty, RT_NULL);
    return;
}

static int n_tty_open(struct dfs_file *fd)
{
    int ret = 0;
    struct n_tty_data *ldata = RT_NULL;
    struct tty_struct *tty = (struct tty_struct*)fd->vnode->data;

    ldata = rt_malloc(sizeof(struct n_tty_data));
    if (ldata == RT_NULL)
    {
        LOG_E("n_tty_open ldata malloc fail");
        return -1;
    }

    ldata->atomic_read_lock = rt_mutex_create("atomic_read_lock",RT_IPC_FLAG_FIFO);
    if(ldata->atomic_read_lock == RT_NULL)
    {
        LOG_E("n_tty_open atomic_read_lock create fail");
        return -1;
    }

    ldata->output_lock = rt_mutex_create("output_lock",RT_IPC_FLAG_FIFO);
    if(ldata->output_lock == RT_NULL)
    {
        LOG_E("n_tty_open output_lock create fail");
        return -1;
    }

    tty->disc_data = ldata;
    reset_buffer_flags(ldata);
    ldata->column = 0;
    ldata->canon_column = 0;
    ldata->lnext = 0;
    n_tty_set_termios(tty, RT_NULL);
    return ret;
}

rt_inline int input_available_p(struct tty_struct *tty, int poll)
{
    struct n_tty_data *ldata = tty->disc_data;
    int amt = poll && !TIME_CHAR(tty) && MIN_CHAR(tty) ? MIN_CHAR(tty) : 1;

    if (ldata->icanon && !L_EXTPROC(tty))
    {
        return ldata->canon_head != ldata->read_tail;
    }
    else
    {
        return ldata->commit_head - ldata->read_tail >= amt;
    }
}

/**
 *  copy_from_read_buf  -   copy read data directly
 *  @tty: terminal device
 *  @b: user data
 *  @nr: size of data
 *
 *  Helper function to speed up n_tty_read.  It is only called when
 *  ICANON is off; it copies characters straight from the tty queue to
 *  user space directly.  It can be profitably called twice; once to
 *  drain the space from the tail pointer to the (physical) end of the
 *  buffer, and once to drain the space from the (physical) beginning of
 *  the buffer to head pointer.
 *
 *  Called under the ldata->atomic_read_lock sem
 *
 *  n_tty_read()/consumer path:
 *      caller holds non-exclusive termios_rwsem
 *      read_tail published
 */

static int copy_from_read_buf(struct tty_struct *tty,char *b,size_t nr)
{
    struct n_tty_data *ldata = tty->disc_data;
    size_t n = 0;
    rt_bool_t is_eof = 0;
    size_t head = ldata->commit_head;
    size_t tail = ldata->read_tail & (RT_TTY_BUF - 1);

    n = min(head - ldata->read_tail, RT_TTY_BUF - tail);
    n = min(nr, n);
    if (n)
    {
        const char *from = read_buf_addr(ldata, tail);
        memcpy(b, from, n);
        is_eof = n == 1 && *from == EOF_CHAR(tty);
        ldata->read_tail += n;
        /* Turn single EOF into zero-length read */
        if (L_EXTPROC(tty) && ldata->icanon && is_eof &&
            (head == ldata->read_tail))
        {
            n = 0;
        }

    }
    return n;
}

/**
 *  canon_copy_from_read_buf    -   copy read data in canonical mode
 *  @tty: terminal device
 *  @b: user data
 *  @nr: size of data
 *
 *  Helper function for n_tty_read.  It is only called when ICANON is on;
 *  it copies one line of input up to and including the line-delimiting
 *  character into the user-space buffer.
 *
 *  NB: When termios is changed from non-canonical to canonical mode and
 *  the read buffer contains data, n_tty_set_termios() simulates an EOF
 *  push (as if C-d were input) _without_ the DISABLED_CHAR in the buffer.
 *  This causes data already processed as input to be immediately available
 *  as input although a newline has not been received.
 *
 *  Called under the atomic_read_lock mutex
 *
 *  n_tty_read()/consumer path:
 *      caller holds non-exclusive termios_rwsem
 *      read_tail published
 */

static int canon_copy_from_read_buf(struct tty_struct *tty, char *b, size_t nr)
{
    struct n_tty_data *ldata = tty->disc_data;
    size_t n = 0, size = 0, more = 0, c = 0;
    size_t eol = 0;
    size_t tail = 0;
    int found = 0;

    /* N.B. avoid overrun if nr == 0 */
    if (nr == 0)
    {
        return 0;
    }

    n = min(nr + 1, ldata->canon_head - ldata->read_tail);

    tail = ldata->read_tail & (RT_TTY_BUF - 1);
    size = min(tail + n, RT_TTY_BUF);

    eol = find_next_bit(ldata->read_flags, size, tail);
    more = n - (size - tail);
    if (eol == RT_TTY_BUF && more)
    {
        /* scan wrapped without finding set bit */
        eol = find_next_bit(ldata->read_flags, more, 0);
        found = eol != more;
    }
    else
    {
        found = eol != size;
    }

    n = eol - tail;
    if (n > RT_TTY_BUF)
    {
        n += RT_TTY_BUF;
    }
    c = n + found;

    if (!found || read_buf(ldata, eol) != __DISABLED_CHAR)
    {
        c = min(nr, c);
        n = c;
    }

    size_t buf_size = RT_TTY_BUF - tail;
    const void *from = read_buf_addr(ldata, tail);
    size_t temp_n = n;
    if (n > buf_size)
    {
        memcpy(b, from, buf_size);
        b += buf_size;
        temp_n -= buf_size;
        from = ldata->read_buf;
    }
    memcpy(b, from, temp_n);

    if (found)
    {
        clear_bit(eol, (int *)ldata->read_flags);
    }
    ldata->read_tail = ldata->read_tail + c;

    if (found)
    {
        if (!ldata->push)
        {
            ldata->line_start = ldata->read_tail;
        }
        else
        {
            ldata->push = 0;
        }
    }
    return n;
}


static int n_tty_close(struct tty_struct *tty)
{
    int ret = 0;
    struct n_tty_data *ldata = RT_NULL;
    struct tty_struct *o_tty = RT_NULL;

    RT_ASSERT(tty != RT_NULL);
    if (tty->type == TTY_DRIVER_TYPE_PTY && tty->subtype == PTY_TYPE_MASTER)
    {
        o_tty = tty->other_struct;
    }
    else
    {
        o_tty = tty;
    }

    ldata = o_tty->disc_data;
    rt_free(ldata);
    o_tty->disc_data = RT_NULL;
    return ret;
}

static int n_tty_ioctl(struct dfs_file *fd, int cmd, void *args)
{
    int ret = 0;
    struct tty_struct *real_tty = RT_NULL;
    struct tty_struct *tty = RT_NULL;

    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);
    if (tty->type == TTY_DRIVER_TYPE_PTY && tty->subtype == PTY_TYPE_MASTER)
    {
        real_tty = tty->other_struct;
    }
    else
    {
        real_tty = tty;
    }

    switch(cmd)
    {

    default:
        ret = n_tty_ioctl_extend(real_tty, cmd, args);
        if (ret != -ENOIOCTLCMD)
        {
            return ret;
        }
    }

    ret = rt_device_control((rt_device_t)real_tty, cmd, args);
    if (ret != -ENOIOCTLCMD)
    {
        return ret;
    }
    return ret;
}

static void
n_tty_receive_signal_char(struct tty_struct *tty, int signal, unsigned char c)
{
    isig(signal, tty);
    if (L_ECHO(tty))
    {
        echo_char(c, tty);
        commit_echoes(tty);
    }
    else
    {
        process_echoes(tty);
    }
    return;
}

/**
 *  n_tty_receive_char  -   perform processing
 *  @tty: terminal device
 *  @c: character
 *
 *  Process an individual character of input received from the driver.
 *  This is serialized with respect to itself by the rules for the
 *  driver above.
 *
 *  n_tty_receive_buf()/producer path:
 *      caller holds non-exclusive termios_rwsem
 *      publishes canon_head if canonical mode is active
 *
 *  Returns 1 if LNEXT was received, else returns 0
 */

static int n_tty_receive_char_special(struct tty_struct *tty, unsigned char c)
{
    struct n_tty_data *ldata = tty->disc_data;

    if (I_IXON(tty))
    {
        if (c == START_CHAR(tty)) /*ctrl + p realize missing*/
        {
            process_echoes(tty);
            return 0;
        }
        if (c == STOP_CHAR(tty)) /*ctrl + s realize missing*/
        {
            return 0;
        }
    }

    if (L_ISIG(tty))
    {
        if (c == INTR_CHAR(tty)) /*ctrl + c realize missing*/
        {
            n_tty_receive_signal_char(tty, SIGINT, c);
            return 0;
        }
        else if (c == QUIT_CHAR(tty)) /*ctrl + d realize missing*/
        {
            n_tty_receive_signal_char(tty, SIGQUIT, c);
            return 0;
        }
        else if (c == SUSP_CHAR(tty)) /*ctrl + z realize missing*/
        {
            n_tty_receive_signal_char(tty, SIGTSTP, c);
            return 0;
        }
    }

    if (c == '\r')
    {
        if (I_IGNCR(tty))
        {
            return 0;
        }

        if (I_ICRNL(tty))
        {
            c = '\n';
        }
    }
    else if (c == '\n' && I_INLCR(tty))
    {
        c = '\r';
    }

    if (ldata->icanon)
    {
        if (c == ERASE_CHAR(tty) || c == KILL_CHAR(tty) ||
            (c == WERASE_CHAR(tty) && L_IEXTEN(tty)))
        {
            eraser(c, tty);
            commit_echoes(tty);
            return 0;
        }
        if (c == LNEXT_CHAR(tty) && L_IEXTEN(tty))
        {
            ldata->lnext = 1;
            if (L_ECHO(tty))
            {
                finish_erasing(ldata);
                if (L_ECHOCTL(tty))
                {
                    echo_char_raw('^', ldata);
                    echo_char_raw('\b', ldata);
                    commit_echoes(tty);
                }
            }
            return 1;
        }
        if (c == REPRINT_CHAR(tty) && L_ECHO(tty) && L_IEXTEN(tty))
        {
            size_t tail = ldata->canon_head;

            finish_erasing(ldata);
            echo_char(c, tty);
            echo_char_raw('\n', ldata);
            while (tail != ldata->read_head)
            {
                echo_char(read_buf(ldata, tail), tty);
                tail++;
            }
            commit_echoes(tty);
            return 0;
        }
        if (c == '\n')
        {
            if (L_ECHO(tty) || L_ECHONL(tty))
            {
                echo_char_raw('\n', ldata);
                commit_echoes(tty);
            }
            goto handle_newline;
        }
        if (c == EOF_CHAR(tty))
        {
            c = __DISABLED_CHAR;
            goto handle_newline;
        }
        if ((c == EOL_CHAR(tty)) ||
            (c == EOL2_CHAR(tty) && L_IEXTEN(tty)))
        {
            /*
             * XXX are EOL_CHAR and EOL2_CHAR echoed?!?
             */
            if (L_ECHO(tty))
            {
                /* Record the column of first canon char. */
                if (ldata->canon_head == ldata->read_head)
                {
                    echo_set_canon_col(ldata);
                }

                echo_char(c, tty);
                commit_echoes(tty);
            }
            /*
             * XXX does PARMRK doubling happen for
             * EOL_CHAR and EOL2_CHAR?
             */
            if (c == (unsigned char) '\377' && I_PARMRK(tty))
            {
                put_tty_queue(c, ldata);
            }

handle_newline:
            set_bit(ldata->read_head & (RT_TTY_BUF - 1), (int *)ldata->read_flags);
            put_tty_queue(c, ldata);
            ldata->canon_head = ldata->read_head;
            tty_wakeup_check(tty);
            return 0;
        }
    }

    if (L_ECHO(tty))
    {
        finish_erasing(ldata);
        if (c == '\n')
        {
            echo_char_raw('\n', ldata);
        }
        else
        {
            /* Record the column of first canon char. */
            if (ldata->canon_head == ldata->read_head)
            {
                echo_set_canon_col(ldata);
            }
            echo_char(c, tty);
        }
        commit_echoes(tty);
    }

    /* PARMRK doubling check */
    if (c == (unsigned char) '\377' && I_PARMRK(tty))
    {
        put_tty_queue(c, ldata);
    }

    put_tty_queue(c, ldata);
    return 0;
}

rt_inline void n_tty_receive_char_inline(struct tty_struct *tty, unsigned char c)
{
    struct n_tty_data *ldata = tty->disc_data;

    if (L_ECHO(tty))
    {
        finish_erasing(ldata);
        /* Record the column of first canon char. */
        if (ldata->canon_head == ldata->read_head)
        {
            echo_set_canon_col(ldata);
        }

        echo_char(c, tty);
        commit_echoes(tty);
    }
    /* PARMRK doubling check */
    if (c == (unsigned char) '\377' && I_PARMRK(tty))
    {
        put_tty_queue(c, ldata);
    }

    put_tty_queue(c, ldata);
}

static void n_tty_receive_char(struct tty_struct *tty, unsigned char c)
{
    n_tty_receive_char_inline(tty, c);
}

static void n_tty_receive_char_lnext(struct tty_struct *tty, unsigned char c, char flag)
{
    struct n_tty_data *ldata = tty->disc_data;

    ldata->lnext = 0;
    if (flag == TTY_NORMAL)
    {
        if (I_ISTRIP(tty))
        {
            c &= 0x7f;
        }

        if (I_IUCLC(tty) && L_IEXTEN(tty))
        {
            c = tolower(c);
        }

        n_tty_receive_char(tty, c);
    }
    else
    {
        //n_tty_receive_char_flagged(tty, c, flag);
    }

}

static void n_tty_receive_buf_real_raw(struct tty_struct *tty, char *cp, int count)
{
    struct n_tty_data *ldata = tty->disc_data;
    size_t n = 0, head = 0;

    head = ldata->read_head & (RT_TTY_BUF - 1);
    n = min(count, RT_TTY_BUF - head);
    rt_memcpy(read_buf_addr(ldata, head), cp, n);
    ldata->read_head += n;
    cp += n;
    count -= n;

    head = ldata->read_head & (RT_TTY_BUF - 1);
    n = min(count, RT_TTY_BUF - head);
    rt_memcpy(read_buf_addr(ldata, head), cp, n);
    ldata->read_head += n;
}

static void n_tty_receive_buf_raw(struct tty_struct *tty, char *cp, int count)
{
    struct n_tty_data *ldata = tty->disc_data;
    char flag = TTY_NORMAL;

    while (count--)
    {
        if (flag == TTY_NORMAL)
        {
            put_tty_queue(*cp++, ldata);
        }
    }
}

static void n_tty_receive_buf_standard(struct tty_struct *tty, char *cp, int count)
{
    struct n_tty_data *ldata = tty->disc_data;
    char flag = TTY_NORMAL;

    while (count--)
    {
        char c = *cp++;

        if (I_ISTRIP(tty))
        {
            c &= 0x7f;
        }

        if (I_IUCLC(tty) && L_IEXTEN(tty))
        {
            c = tolower(c);
        }

        if (L_EXTPROC(tty))
        {
            put_tty_queue(c, ldata);
            continue;
        }

        if (!test_bit(c, (int *)ldata->char_map))
        {
            n_tty_receive_char_inline(tty, c);
        }
        else if (n_tty_receive_char_special(tty, c) && count)
        {
            n_tty_receive_char_lnext(tty, *cp++, flag);
            count--;
        }
    }
}

rt_inline void n_tty_receive_char_fast(struct tty_struct *tty, unsigned char c)
{
    struct n_tty_data *ldata = tty->disc_data;

    if (L_ECHO(tty))
    {
        finish_erasing(ldata);
        /* Record the column of first canon char. */
        if (ldata->canon_head == ldata->read_head)
        {
            echo_set_canon_col(ldata);
        }

        echo_char(c, tty);
        commit_echoes(tty);
    }
    put_tty_queue(c, ldata);
}

static void n_tty_receive_buf_fast(struct tty_struct *tty, char *cp, int count)
{
    struct n_tty_data *ldata = tty->disc_data;
    char flag = TTY_NORMAL;

    while (count--)
    {
        unsigned char c = *cp++;

        if (!test_bit(c, (int *)ldata->char_map))
        {
            n_tty_receive_char_fast(tty, c);
        }
        else if (n_tty_receive_char_special(tty, c) && count)
        {
            n_tty_receive_char_lnext(tty, *cp++, flag);
            count--;
        }
    }
}

static void __receive_buf(struct tty_struct *tty, char *cp, int count)
{
    struct n_tty_data *ldata = tty->disc_data;
    rt_bool_t preops = I_ISTRIP(tty) || (I_IUCLC(tty) && L_IEXTEN(tty));

    if (ldata->real_raw)
    {
        n_tty_receive_buf_real_raw(tty, cp, count);
    }

    else if (ldata->raw || (L_EXTPROC(tty) && !preops))
    {
        n_tty_receive_buf_raw(tty, cp, count);
    }
    else
    {
        if (!preops && !I_PARMRK(tty))
        {
            n_tty_receive_buf_fast(tty, cp, count);
        }
        else
        {
            n_tty_receive_buf_standard(tty, cp, count);
        }
        flush_echoes(tty);
    }

    if (ldata->icanon && !L_EXTPROC(tty))
        return;

    /* publish read_head to consumer */
    ldata->commit_head = ldata->read_head;

    if (read_cnt(ldata))
    {
        tty_wakeup_check(tty);
    }
}

int n_tty_receive_buf(struct tty_struct *tty,char *cp, int count)
{
    int size = 0;
    struct n_tty_data *ldata = tty->disc_data;
    int room = 0, n = 0, rcvd = 0, overflow = 0;

    size = count;
    while(1)
    {
        size_t tail = ldata->read_tail;

        room = RT_TTY_BUF - (ldata->read_head - tail);

        if (I_PARMRK(tty))
        {
            room = (room +2)/3;
        }
        room--;
        if (room <= 0)
        {
            overflow = ldata->icanon && ldata->canon_head == tail;
            if (overflow && room < 0)
            {
                ldata->read_head--;
            }

            room = overflow;
        }
        else
        {
            overflow = 0;
        }

        n =  min(size, room);

        if (!n)
        {
            break;
        }

        if (!overflow)
        {
            __receive_buf(tty, cp, n);
        }

        cp += n;
        size -= n;
        rcvd += n;
    }
    return count - size;
}

/**
 *  job_control     -   check job control
 *  @tty: tty
 *  @file: file handle
 *
 *  Perform job control management checks on this file/tty descriptor
 *  and if appropriate send any needed signals and return a negative
 *  error code if action should be taken.
 *
 *  Locking: redirected write test is safe
 *       current->signal->tty check is safe
 *       ctrl_lock to safely reference tty->pgrp
 */

static int job_control(struct tty_struct *tty)
{
    return __tty_check_change(tty, SIGTTIN);
}

static struct rt_wqueue *_wait_queue_current_get(struct tty_struct *tty)
{
    struct rt_lwp *lwp;

    lwp = lwp_self();
    if (!lwp || !lwp->tty)
        lwp = RT_NULL;

    return wait_queue_get(lwp, tty);
}

static int n_tty_read(struct dfs_file *fd, void *buf, size_t count)
{
    rt_base_t level = 0;
    char *b = (char *)buf;
    struct tty_struct *tty = RT_NULL;
    struct rt_wqueue *wq = RT_NULL;
    int wait_ret = 0;
    int retval = 0;
    int c = 0;

    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);
    c = job_control(tty);
    if (c < 0)
    {
        return c;
    }

    struct n_tty_data *ldata = tty->disc_data;

    wq = _wait_queue_current_get(tty);

    while(count)
    {
        if ((!input_available_p(tty, 0)))
        {
            if (fd->flags & O_NONBLOCK)
            {
                retval = -EAGAIN;
                break;
            }

            wait_ret = rt_wqueue_wait_interruptible(wq, 0, RT_WAITING_FOREVER);

            if (wait_ret != 0)
            {
                break;
            }
        }

        level = rt_spin_lock_irqsave(&tty->spinlock);
        if (ldata->icanon && !L_EXTPROC(tty))
        {
            retval = canon_copy_from_read_buf(tty, b, count);
        }
        else
        {
            retval = copy_from_read_buf(tty, b, count);
        }
        rt_spin_unlock_irqrestore(&tty->spinlock, level);

        if (retval >= 1)
        {
            break;
        }
    }

    return retval;
}

static int n_tty_write(struct dfs_file *fd, const void *buf, size_t count)
{
    int retval = 0;
    char *b = (char *)buf;
    int c = 0;
    struct tty_struct *tty = RT_NULL;

    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);
    retval = tty_check_change(tty);
    if (retval)
    {
        return retval;
    }

    process_echoes(tty);
    retval = count;
    while(1)
    {
        if (O_OPOST(tty))
        {
            while (count > 0)
            {
                ssize_t num = process_output_block(tty, b, count);
                if (num < 0)
                {
                    if (num == -EAGAIN)
                    {
                        break;
                    }

                    retval = num;
                    goto break_out;
                }
                b += num;
                count -= num;
                if (count == 0)
                {
                    break;
                }

                c = *b;
                if (process_output(c, tty) < 0)
                {
                    break;
                }

                b++;
                count--;
            }
            retval -= count;
        }
        else
        {
            while (count > 0)
            {
                c = rt_device_write((rt_device_t)tty, -1, b, count);
                if (c < 0)
                {
                    retval = c;
                    goto break_out;
                }
                b += c;
                count -= c;
            }
            retval -= count;
        }

        if (!count)
        {
            break;
        }
        if (fd->flags & O_NONBLOCK)
        {
            break;
        }
    }
break_out:
    return retval;
}

static int n_tty_flush(struct dfs_file *fd)
{
    return 0;
}

static int n_tty_lseek(struct dfs_file *fd, off_t offset)
{
    return 0;
}

static int n_tty_getdents(struct dfs_file *fd, struct dirent *dirp, uint32_t count)
{
    return 0;
}

static int n_tty_poll(struct dfs_file *fd, struct rt_pollreq *req)
{
    rt_base_t level = 0;
    int mask = POLLOUT;
    struct tty_struct *tty = RT_NULL;
    struct rt_wqueue *wq = RT_NULL;

    tty = (struct tty_struct *)fd->vnode->data;
    RT_ASSERT(tty != RT_NULL);

    RT_ASSERT(tty->init_flag == TTY_INIT_FLAG_INITED);

    wq = _wait_queue_current_get(tty);
    rt_poll_add(wq, req);

    level = rt_spin_lock_irqsave(&tty->spinlock);
    if (input_available_p(tty, 1))
    {
        mask |= POLLIN;
    }
    rt_spin_unlock_irqrestore(&tty->spinlock, level);

    return mask;
}

struct tty_ldisc_ops n_tty_ops = {
    "n_tty",
    0,
    n_tty_open,
    n_tty_close,
    n_tty_ioctl,
    n_tty_read,
    n_tty_write,
    n_tty_flush,
    n_tty_lseek,
    n_tty_getdents,
    n_tty_poll,
    n_tty_set_termios,
    n_tty_receive_buf,
    0,
};
