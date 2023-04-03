/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 *the the People's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.
 *
 * DISCLAIMER
 * THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
 * IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
 * IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
 * ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
 * ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
 * COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
 * YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
 * PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
 * THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
 * OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __CCU_H__
#define __CCU_H__

#include <hal_clk.h>
#include <limits.h>
#include <aw_list.h>
#include <hal_log.h>
#include <sunxi_hal_common.h>
#include <hal_atomic.h>

struct clk;
struct clk_hw;
struct clk_core;
struct clk_ops;

#undef BIT
#define BIT(x) (1UL << (x))

#define BITS_PER_LONGS 32
#define GENMASK(h, l) \
    (((~(0)) - ((1) << (l)) + 1) & \
     (0x00ffffffff >> (BITS_PER_LONGS - 1 - (h))))
#define DIV_ROUND_UP_ULL(n, d) (((n) + (d) - 1) / (d))
/*
 * flags used across common struct clk.  these flags should only affect the
 * top-level framework.  custom flags for dealing with hardware specifics
 * belong in struct clk_foo
 *
 * Please update clk_flags[] in drivers/clk/clk.c when making changes here!
 */
#define CLK_SET_RATE_GATE   BIT(0) /* must be gated across rate change */
#define CLK_SET_PARENT_GATE BIT(1) /* must be gated across re-parent */
#define CLK_SET_RATE_PARENT BIT(2) /* propagate rate change up one level */
#define CLK_IGNORE_UNUSED   BIT(3) /* do not gate even if unused */
/* unused */
/* unused */
#define CLK_GET_RATE_NOCACHE    BIT(6) /* do not use the cached clk rate */
#define CLK_SET_RATE_NO_REPARENT BIT(7) /* don't re-parent on rate change */
#define CLK_GET_ACCURACY_NOCACHE BIT(8) /* do not use the cached clk accuracy */
#define CLK_RECALC_NEW_RATES    BIT(9) /* recalc rates after notifications */
#define CLK_SET_RATE_UNGATE BIT(10) /* clock needs to run to set rate */
#define CLK_IS_CRITICAL     BIT(11) /* do not gate, ever */
/* parents need enable during gate/ungate, set rate and re-parent */
#define CLK_OPS_PARENT_ENABLE   BIT(12)
/* duty cycle call may be forwarded to the parent clock */
#define CLK_DUTY_CYCLE_PARENT   BIT(13)
#define CLK_DONT_HOLD_STATE BIT(14) /* Don't hold state */

/**
 * struct clk_duty - Struture encoding the duty cycle ratio of a clock
 *
 * @num:    Numerator of the duty cycle ratio
 * @den:    Denominator of the duty cycle ratio
 */
struct clk_duty
{
    unsigned int num;
    unsigned int den;
};


struct clk_parent_map
{
    const struct clk_hw *hw;
    struct clk_core     *core;
    const char      *fw_name;
    const char      *name;
    int         index;
};

struct clk_core
{
    const char          *name;
    const struct clk_ops    *ops;
    struct clk_hw       *hw;
    struct clk          *clk;
    struct clk_core     *parent;
    struct clk_parent_map   *parents;
    u8          num_parents;
    u32         p_rate;
    unsigned long       rate;
    unsigned long       flags;
    unsigned int        enable_count;
    unsigned long       min_rate;
    unsigned long       max_rate;
    unsigned long       accuracy;
    struct list_head    node;
};

struct clk
{
    struct clk_core *core;
    const char *name;
    u8  count;  //the number that clk_get
};

/**
 * struct clk_rate_request - Structure encoding the clk constraints that
 * a clock user might require.
 *
 * @rate:       Requested clock rate. This field will be adjusted by
 *          clock drivers according to hardware capabilities.
 * @min_rate:       Minimum rate imposed by clk users.
 * @max_rate:       Maximum rate imposed by clk users.
 * @best_parent_rate:   The best parent rate a parent can provide to fulfill the
 *          requested constraints.
 * @best_parent_hw: The most appropriate parent clock that fulfills the
 *          requested constraints.
 *
 */
struct clk_rate_request
{
    unsigned long rate;
    unsigned long min_rate;
    unsigned long max_rate;
    unsigned long best_parent_rate;
    struct clk_hw *best_parent_hw;
};

/**
 * struct clk_ops -  Callback operations for hardware clocks; these are to
 * be provided by the clock implementation, and will be called by drivers
 * through the clk_* api.
 *
 * @prepare:    Prepare the clock for enabling. This must not return until
 *      the clock is fully prepared, and it's safe to call clk_enable.
 *      This callback is intended to allow clock implementations to
 *      do any initialisation that may sleep. Called with
 *      prepare_lock held.
 *
 * @unprepare:  Release the clock from its prepared state. This will typically
 *      undo any work done in the @prepare callback. Called with
 *      prepare_lock held.
 *
 * @is_prepared: Queries the hardware to determine if the clock is prepared.
 *      This function is allowed to sleep. Optional, if this op is not
 *      set then the prepare count will be used.
 *
 * @unprepare_unused: Unprepare the clock atomically.  Only called from
 *      clk_disable_unused for prepare clocks with special needs.
 *      Called with prepare mutex held. This function may sleep.
 *
 * @enable: Enable the clock atomically. This must not return until the
 *      clock is generating a valid clock signal, usable by consumer
 *      devices. Called with enable_lock held. This function must not
 *      sleep.
 *
 * @disable:    Disable the clock atomically. Called with enable_lock held.
 *      This function must not sleep.
 *
 * @is_enabled: Queries the hardware to determine if the clock is enabled.
 *      This function must not sleep. Optional, if this op is not
 *      set then the enable count will be used.
 *
 * @disable_unused: Disable the clock atomically.  Only called from
 *      clk_disable_unused for gate clocks with special needs.
 *      Called with enable_lock held.  This function must not
 *      sleep.
 *
 * @save_context: Save the context of the clock in prepration for poweroff.
 *
 * @restore_context: Restore the context of the clock after a restoration
 *      of power.
 *
 * @recalc_rate Recalculate the rate of this clock, by querying hardware. The
 *      parent rate is an input parameter.  It is up to the caller to
 *      ensure that the prepare_mutex is held across this call.
 *      Returns the calculated rate.  Optional, but recommended - if
 *      this op is not set then clock rate will be initialized to 0.
 *
 * @round_rate: Given a target rate as input, returns the closest rate actually
 *      supported by the clock. The parent rate is an input/output
 *      parameter.
 *
 * @determine_rate: Given a target rate as input, returns the closest rate
 *      actually supported by the clock, and optionally the parent clock
 *      that should be used to provide the clock rate.
 *
 * @set_parent: Change the input source of this clock; for clocks with multiple
 *      possible parents specify a new parent by passing in the index
 *      as a u8 corresponding to the parent in either the .parent_names
 *      or .parents arrays.  This function in affect translates an
 *      array index into the value programmed into the hardware.
 *      Returns 0 on success, -EERROR otherwise.
 *
 * @get_parent: Queries the hardware to determine the parent of a clock.  The
 *      return value is a u8 which specifies the index corresponding to
 *      the parent clock.  This index can be applied to either the
 *      .parent_names or .parents arrays.  In short, this function
 *      translates the parent value read from hardware into an array
 *      index.  Currently only called when the clock is initialized by
 *      __clk_init.  This callback is mandatory for clocks with
 *      multiple parents.  It is optional (and unnecessary) for clocks
 *      with 0 or 1 parents.
 *
 * @set_rate:   Change the rate of this clock. The requested rate is specified
 *      by the second argument, which should typically be the return
 *      of .round_rate call.  The third argument gives the parent rate
 *      which is likely helpful for most .set_rate implementation.
 *      Returns 0 on success, -EERROR otherwise.
 *
 * @set_rate_and_parent: Change the rate and the parent of this clock. The
 *      requested rate is specified by the second argument, which
 *      should typically be the return of .round_rate call.  The
 *      third argument gives the parent rate which is likely helpful
 *      for most .set_rate_and_parent implementation. The fourth
 *      argument gives the parent index. This callback is optional (and
 *      unnecessary) for clocks with 0 or 1 parents as well as
 *      for clocks that can tolerate switching the rate and the parent
 *      separately via calls to .set_parent and .set_rate.
 *      Returns 0 on success, -EERROR otherwise.
 *
 * @recalc_accuracy: Recalculate the accuracy of this clock. The clock accuracy
 *      is expressed in ppb (parts per billion). The parent accuracy is
 *      an input parameter.
 *      Returns the calculated accuracy.  Optional - if this op is not
 *      set then clock accuracy will be initialized to parent accuracy
 *      or 0 (perfect clock) if clock has no parent.
 *
 * @get_phase:  Queries the hardware to get the current phase of a clock.
 *      Returned values are 0-359 degrees on success, negative
 *      error codes on failure.
 *
 * @set_phase:  Shift the phase this clock signal in degrees specified
 *      by the second argument. Valid values for degrees are
 *      0-359. Return 0 on success, otherwise -EERROR.
 *
 * @get_duty_cycle: Queries the hardware to get the current duty cycle ratio
 *              of a clock. Returned values denominator cannot be 0 and must be
 *              superior or equal to the numerator.
 *
 * @set_duty_cycle: Apply the duty cycle ratio to this clock signal specified by
 *              the numerator (2nd argurment) and denominator (3rd  argument).
 *              Argument must be a valid ratio (denominator > 0
 *              and >= numerator) Return 0 on success, otherwise -EERROR.
 *
 * @init:   Perform platform-specific initialization magic.
 *      This is not not used by any of the basic clock types.
 *      Please consider other ways of solving initialization problems
 *      before using this callback, as its use is discouraged.
 *
 * @debug_init: Set up type-specific debugfs entries for this clock.  This
 *      is called once, after the debugfs directory entry for this
 *      clock has been created.  The dentry pointer representing that
 *      directory is provided as an argument.  Called with
 *      prepare_lock held.  Returns 0 on success, -EERROR otherwise.
 *
 * @pre_rate_change: Optional callback for a clock to fulfill its rate
 *      change requirements before any rate change has occurred in
 *      its clock tree. Returns 0 on success, -EERROR otherwise.
 *
 * @post_rate_change: Optional callback for a clock to clean up any
 *      requirements that were needed while the clock and its tree
 *      was changing states. Returns 0 on success, -EERROR otherwise.
 *
 * The clk_enable/clk_disable and clk_prepare/clk_unprepare pairs allow
 * implementations to split any work between atomic (enable) and sleepable
 * (prepare) contexts.  If enabling a clock requires code that might sleep,
 * this must be done in clk_prepare.  Clock enable code that will never be
 * called in a sleepable context may be implemented in clk_enable.
 *
 * Typically, drivers will call clk_prepare when a clock may be needed later
 * (eg. when a device is opened), and clk_enable when the clock is actually
 * required (eg. from an interrupt). Note that clk_prepare MUST have been
 * called before clk_enable.
 */
struct clk_ops
{
    int (*prepare)(struct clk_hw *hw);
    void (*unprepare)(struct clk_hw *hw);
    int (*is_prepared)(struct clk_hw *hw);
    void (*unprepare_unused)(struct clk_hw *hw);
    int (*enable)(struct clk_hw *hw);
    void (*disable)(struct clk_hw *hw);
    int (*is_enabled)(struct clk_hw *hw);
    void (*disable_unused)(struct clk_hw *hw);
    unsigned long (*recalc_rate)(struct clk_hw *hw,
                                 unsigned long parent_rate);
    long (*round_rate)(struct clk_hw *hw, unsigned long rate,
                       unsigned long *parent_rate);
    int (*determine_rate)(struct clk_hw *hw,
                          struct clk_rate_request *req);
    int (*set_parent)(struct clk_hw *hw, u8 index);
    u8(*get_parent)(struct clk_hw *hw);
    int (*set_rate)(struct clk_hw *hw, unsigned long rate,
                    unsigned long parent_rate);
    int (*set_rate_and_parent)(struct clk_hw *hw,
                               unsigned long rate,
                               unsigned long parent_rate, u8 index);
    unsigned long (*recalc_accuracy)(struct clk_hw *hw,
                                     unsigned long parent_accuracy);
    void (*init)(struct clk_hw *hw);
};

/**
 * struct clk_init_data - holds init data that's common to all clocks and is
 * shared between the clock provider and the common clock framework.
 *
 * @name: clock name
 * @ops: operations this clock supports
 * @parent_names: array of string names for all possible parents
 * @parent_data: array of parent data for all possible parents (when some
 *               parents are external to the clk controller)
 * @parent_hws: array of pointers to all possible parents (when all parents
 *              are internal to the clk controller)
 * @num_parents: number of possible parents
 * @flags: framework-level hints and quirks
 */
struct clk_init_data
{
    const char          *name;
    const struct clk_ops    *ops;
    /* Only one of the following three should be assigned */
    const char  *const      *parent_names;
    const struct clk_parent_data    *parent_data;
    const struct clk_hw      **parent_hws;
    u8          num_parents;
    unsigned long       flags;
};

/**
 * struct clk_hw - handle for traversing from a struct clk to its corresponding
 * hardware-specific structure.  struct clk_hw should be declared within struct
 * clk_foo and then referenced by the struct clk instance that uses struct
 * clk_foo's clk_ops
 *
 * @core: pointer to the struct clk_core instance that points back to this
 * struct clk_hw instance
 *
 * @clk: pointer to the per-user struct clk instance that can be used to call
 * into the clk API
 *
 * @init: pointer to struct clk_init_data that contains the init data shared
 * with the common clock framework. This pointer will be set to NULL once
 * a clk_register() variant is called on this clk_hw pointer.
 */
struct clk_hw
{
    struct clk_core *core;
    hal_clk_id_t id;
    hal_clk_type_t type;
    struct clk_init_data *init;
};

/**
 * struct clk_parent_data - clk parent information
 * @hw: parent clk_hw pointer (used for clk providers with internal clks)
 * @fw_name: parent name local to provider registering clk
 * @name: globally unique parent name (used as a fallback)
 * @index: parent index local to provider registering clk (if @fw_name absent)
 */
struct clk_parent_data
{
    const struct clk_hw *hw;
    const char      *fw_name;
    const char      *name;
    int         index;
};

/**
 * struct clk_fixed_rate - fixed-rate clock
 * @hw:     handle between common and hardware-specific interfaces
 * @fixed_rate: constant frequency of clock
 */
struct clk_fixed_rate
{
    struct      clk_hw hw;
    unsigned long   fixed_rate;
    unsigned long   fixed_accuracy;
};

#define to_clk_fixed_rate(_hw) container_of(_hw, struct clk_fixed_rate, hw)
/**
 * struct clk_gate - gating clock
 *
 * @hw:     handle between common and hardware-specific interfaces
 * @reg:    register controlling gate
 * @bit_idx:    single bit controlling gate
 * @flags:  hardware-specific flags
 * @lock:   register lock
 *
 * Clock which can gate its output.  Implements .enable & .disable
 *
 * Flags:
 * CLK_GATE_SET_TO_DISABLE - by default this clock sets the bit at bit_idx to
 *  enable the clock.  Setting this flag does the opposite: setting the bit
 *  disable the clock and clearing it enables the clock
 * CLK_GATE_HIWORD_MASK - The gate settings are only in lower 16-bit
 *  of this register, and mask of gate bits are in higher 16-bit of this
 *  register.  While setting the gate bits, higher 16-bit should also be
 *  updated to indicate changing gate bits.
 * CLK_GATE_BIG_ENDIAN - by default little endian register accesses are used for
 *  the gate register.  Setting this flag makes the register accesses big
 *  endian.
 */
struct clk_gate
{
    struct clk_hw hw;
    u32     reg;
    u8      bit_idx;
    u8      flags;
};

#define to_clk_gate(_hw) container_of(_hw, struct clk_gate, hw)

struct clk_div_table
{
    unsigned int    val;
    unsigned int    div;
};

/**
 * struct clk_divider - adjustable divider clock
 *
 * @hw:     handle between common and hardware-specific interfaces
 * @reg:    register containing the divider
 * @shift:  shift to the divider bit field
 * @width:  width of the divider bit field
 * @table:  array of value/divider pairs, last entry should have div = 0
 * @lock:   register lock
 *
 * Clock with an adjustable divider affecting its output frequency.  Implements
 * .recalc_rate, .set_rate and .round_rate
 *
 * Flags:
 * CLK_DIVIDER_ONE_BASED - by default the divisor is the value read from the
 *  register plus one.  If CLK_DIVIDER_ONE_BASED is set then the divider is
 *  the raw value read from the register, with the value of zero considered
 *  invalid, unless CLK_DIVIDER_ALLOW_ZERO is set.
 * CLK_DIVIDER_POWER_OF_TWO - clock divisor is 2 raised to the value read from
 *  the hardware register
 * CLK_DIVIDER_ALLOW_ZERO - Allow zero divisors.  For dividers which have
 *  CLK_DIVIDER_ONE_BASED set, it is possible to end up with a zero divisor.
 *  Some hardware implementations gracefully handle this case and allow a
 *  zero divisor by not modifying their input clock
 *  (divide by one / bypass).
 * CLK_DIVIDER_HIWORD_MASK - The divider settings are only in lower 16-bit
 *  of this register, and mask of divider bits are in higher 16-bit of this
 *  register.  While setting the divider bits, higher 16-bit should also be
 *  updated to indicate changing divider bits.
 * CLK_DIVIDER_ROUND_CLOSEST - Makes the best calculated divider to be rounded
 *  to the closest integer instead of the up one.
 * CLK_DIVIDER_READ_ONLY - The divider settings are preconfigured and should
 *  not be changed by the clock framework.
 * CLK_DIVIDER_MAX_AT_ZERO - For dividers which are like CLK_DIVIDER_ONE_BASED
 *  except when the value read from the register is zero, the divisor is
 *  2^width of the field.
 * CLK_DIVIDER_BIG_ENDIAN - By default little endian register accesses are used
 *  for the divider register.  Setting this flag makes the register accesses
 *  big endian.
 */
struct clk_divider
{
    struct clk_hw   hw;
    unsigned long   reg;
    u8      shift;
    u8      width;
    u8      flags;
    hal_spinlock_t lock;
    const struct clk_div_table  *table;
};

extern const struct clk_ops clk_divider_ops;
extern const struct clk_ops clk_divider_ro_ops;

#define CLK_DIVIDER_ONE_BASED       BIT(0)
#define CLK_DIVIDER_POWER_OF_TWO    BIT(1)
#define CLK_DIVIDER_ALLOW_ZERO      BIT(2)
#define CLK_DIVIDER_HIWORD_MASK     BIT(3)
#define CLK_DIVIDER_ROUND_CLOSEST   BIT(4)
#define CLK_DIVIDER_READ_ONLY       BIT(5)
#define CLK_DIVIDER_MAX_AT_ZERO     BIT(6)
#define CLK_DIVIDER_BIG_ENDIAN      BIT(7)

unsigned long divider_recalc_rate(struct clk_hw *hw, unsigned long parent_rate,
                                  unsigned int val, const struct clk_div_table *table,
                                  unsigned long flags, unsigned long width);
long divider_ro_round_rate_parent(struct clk_hw *hw, struct clk_hw *parent,
                                  unsigned long rate, unsigned long *prate,
                                  const struct clk_div_table *table, u8 width,
                                  unsigned long flags, unsigned int val);
long divider_round_rate_parent(struct clk_hw *hw, struct clk_hw *parent,
                               unsigned long rate, unsigned long *prate,
                               const struct clk_div_table *table,
                               u8 width, unsigned long flags);

int divider_get_val(unsigned long rate, unsigned long parent_rate,
                    const struct clk_div_table *table, u8 width,
                    unsigned long flags);

#define clk_div_mask(width) ((1 << (width)) - 1)
#define to_clk_divider(_hw) container_of(_hw, struct clk_divider, hw)

struct clk_hw *clk_hw_register_divider(const char *name,
                                       const char *parent_name, unsigned long flags,
                                       u32 reg, u8 shift, u8 width,
                                       u8 clk_divider_flags, hal_spinlock_t lock);
struct clk_hw *clk_hw_register_divider_table(const char *name,
        const char *parent_name, unsigned long flags,
        u32 reg, u8 shift, u8 width,
        u8 clk_divider_flags, const struct clk_div_table *table,
        hal_spinlock_t lock);
void clk_unregister_divider(struct clk *clk);
void clk_hw_unregister_divider(struct clk_hw *hw);

/**
 * struct clk_mux - multiplexer clock
 *
 * @hw:     handle between common and hardware-specific interfaces
 * @reg:    register controlling multiplexer
 * @table:  array of register values corresponding to the parent index
 * @shift:  shift to multiplexer bit field
 * @mask:   mask of mutliplexer bit field
 * @flags:  hardware-specific flags
 * @lock:   register lock
 *
 * Clock with multiple selectable parents.  Implements .get_parent, .set_parent
 * and .recalc_rate
 *
 * Flags:
 * CLK_MUX_INDEX_ONE - register index starts at 1, not 0
 * CLK_MUX_INDEX_BIT - register index is a single bit (power of two)
 * CLK_MUX_HIWORD_MASK - The mux settings are only in lower 16-bit of this
 *  register, and mask of mux bits are in higher 16-bit of this register.
 *  While setting the mux bits, higher 16-bit should also be updated to
 *  indicate changing mux bits.
 * CLK_MUX_READ_ONLY - The mux registers can't be written, only read in the
 *  .get_parent clk_op.
 * CLK_MUX_ROUND_CLOSEST - Use the parent rate that is closest to the desired
 *  frequency.
 * CLK_MUX_BIG_ENDIAN - By default little endian register accesses are used for
 *  the mux register.  Setting this flag makes the register accesses big
 *  endian.
 */
struct clk_mux
{
    struct clk_hw   hw;
    u32     reg;
    u32     *table;
    u32     mask;
    u8      shift;
    u8      flags;
};

#define to_clk_mux(_hw) container_of(_hw, struct clk_mux, hw)

#define CLK_MUX_INDEX_ONE       BIT(0)
#define CLK_MUX_INDEX_BIT       BIT(1)
#define CLK_MUX_HIWORD_MASK     BIT(2)
#define CLK_MUX_READ_ONLY       BIT(3) /* mux can't be changed */
#define CLK_MUX_ROUND_CLOSEST   BIT(4)
#define CLK_MUX_BIG_ENDIAN      BIT(5)

extern const struct clk_ops clk_mux_ops;
extern const struct clk_ops clk_mux_ro_ops;

/**
 * struct clk_fixed_factor - fixed multiplier and divider clock
 *
 * @hw:     handle between common and hardware-specific interfaces
 * @mult:   multiplier
 * @div:    divider
 *
 * Clock with a fixed multiplier and divider. The output frequency is the
 * parent clock rate divided by div and multiplied by mult.
 * Implements .recalc_rate, .set_rate and .round_rate
 */

struct clk_fixed_factor
{
    struct clk_hw   hw;
    unsigned int    mult;
    unsigned int    div;
};

#define to_clk_fixed_factor(_hw) container_of(_hw, struct clk_fixed_factor, hw)

extern const struct clk_ops clk_fixed_factor_ops;

#define CLK_OF_DECLARE(name, compat, fn) OF_DECLARE_1(clk, name, compat, fn)

/*
 * Use this macro when you have a driver that requires two initialization
 * routines, one at of_clk_init(), and one at platform device probe
 */
#define CLK_OF_DECLARE_DRIVER(name, compat, fn) \
    static void __init name##_of_clk_init_driver(struct device_node *np) \
    {                               \
        of_node_clear_flag(np, OF_POPULATED);           \
        fn(np);                         \
    }                               \
    OF_DECLARE_1(clk, name, compat, name##_of_clk_init_driver)

#define CLK_HW_INIT(_name, _parent, _ops, _flags)       \
    (&(struct clk_init_data) {              \
        .flags      = _flags,           \
                      .name       = _name,            \
        .parent_names   = (const char *[]) { _parent }, \
        .num_parents    = 1,                \
                          .ops        = _ops,             \
    })

#define CLK_HW_INIT_HW(_name, _parent, _ops, _flags)            \
    (&(struct clk_init_data) {                  \
        .flags      = _flags,               \
                      .name       = _name,                \
        .parent_hws = (const struct clk_hw*[]) { _parent }, \
        .num_parents    = 1,                    \
                          .ops        = _ops,                 \
    })

/*
 * This macro is intended for drivers to be able to share the otherwise
 * individual struct clk_hw[] compound literals created by the compiler
 * when using CLK_HW_INIT_HW. It does NOT support multiple parents.
 */
#define CLK_HW_INIT_HWS(_name, _parent, _ops, _flags)           \
    (&(struct clk_init_data) {                  \
        .flags      = _flags,               \
                      .name       = _name,                \
                                    .parent_hws = _parent,              \
                                            .num_parents    = 1,                    \
                                                    .ops        = _ops,                 \
    })

#define CLK_HW_INIT_FW_NAME(_name, _parent, _ops, _flags)       \
    (&(struct clk_init_data) {                  \
        .flags      = _flags,               \
                      .name       = _name,                \
        .parent_data    = (const struct clk_parent_data[]) {    \
            { .fw_name = _parent },     \
        },                    \
        .num_parents    = 1,                    \
                          .ops        = _ops,                 \
    })

#define CLK_HW_INIT_PARENTS(_name, _parents, _ops, _flags)  \
    (&(struct clk_init_data) {              \
        .flags      = _flags,           \
                      .name       = _name,            \
                                    .parent_names   = _parents,         \
                                            .num_parents    = ARRAY_SIZE(_parents),     \
                                                    .ops        = _ops,             \
    })

#define CLK_HW_INIT_PARENTS_HW(_name, _parents, _ops, _flags)   \
    (&(struct clk_init_data) {              \
        .flags      = _flags,           \
                      .name       = _name,            \
                                    .parent_hws = _parents,         \
                                            .num_parents    = ARRAY_SIZE(_parents),     \
                                                    .ops        = _ops,             \
    })

#define CLK_HW_INIT_PARENTS_DATA(_name, _parents, _ops, _flags) \
    (&(struct clk_init_data) {              \
        .flags      = _flags,           \
                      .name       = _name,            \
                                    .parent_data    = _parents,         \
                                            .num_parents    = ARRAY_SIZE(_parents),     \
                                                    .ops        = _ops,             \
    })

#define CLK_HW_INIT_NO_PARENT(_name, _ops, _flags)  \
    (&(struct clk_init_data) {          \
        .flags          = _flags,       \
                          .name           = _name,        \
                                            .parent_names   = NULL,         \
                                                    .num_parents    = 0,            \
                                                            .ops            = _ops,         \
    })

#define CLK_FIXED_FACTOR(_struct, _name, _parent,           \
                         _div, _mult, _flags)                \
struct clk_fixed_factor _struct = {             \
    .div        = _div,                 \
                  .mult       = _mult,                \
                                .hw.init    = CLK_HW_INIT(_name,            \
                                        _parent,          \
                                        &clk_fixed_factor_ops,    \
                                        _flags),          \
}

#define CLK_FIXED_FACTOR_HW(_struct, _name, _parent,            \
                            _div, _mult, _flags)            \
struct clk_fixed_factor _struct = {             \
    .div        = _div,                 \
                  .mult       = _mult,                \
                                .hw.init    = CLK_HW_INIT_HW(_name,         \
                                        _parent,       \
                                        &clk_fixed_factor_ops, \
                                        _flags),       \
}

/*
 * This macro allows the driver to reuse the _parent array for multiple
 * fixed factor clk declarations.
 */
#define CLK_FIXED_FACTOR_HWS(_struct, _name, _parent,           \
                             _div, _mult, _flags)           \
struct clk_fixed_factor _struct = {             \
    .div        = _div,                 \
                  .mult       = _mult,                \
                                .hw.init    = CLK_HW_INIT_HWS(_name,        \
                                        _parent,      \
                                        &clk_fixed_factor_ops, \
                                        _flags),  \
}

#define CLK_FIXED_FACTOR_FW_NAME(_struct, _name, _parent,       \
                                 _div, _mult, _flags)           \
struct clk_fixed_factor _struct = {             \
    .div        = _div,                 \
                  .mult       = _mult,                \
                                .hw.init    = CLK_HW_INIT_FW_NAME(_name,        \
                                        _parent,      \
                                        &clk_fixed_factor_ops, \
                                        _flags),      \
}

const char *clk_hw_get_name(const struct clk_hw *hw);
u32 clk_hw_get_rate(const struct clk_hw *hw);
unsigned long clk_hw_get_flags(const struct clk_hw *hw);
struct clk_core *clk_hw_get_core(const struct clk_hw *hw);
#define clk_hw_can_set_rate_parent(hw) \
    (clk_hw_get_flags((hw)) & CLK_SET_RATE_PARENT)

/*
* FIXME clock api without lock protection
*/
unsigned long clk_hw_round_rate(struct clk_hw *hw, unsigned long rate);

struct clk_hw_onecell_data
{
    unsigned int num;
    struct clk_hw *hws[];
};

#define CLK_OF_DECLARE(name, compat, fn) OF_DECLARE_1(clk, name, compat, fn)

unsigned int clk_hw_get_num_parents(const struct clk_hw *hw);
struct clk_hw *clk_hw_get_parent(const struct clk_hw *hw);
struct clk_hw *clk_hw_get_parent_by_index(const struct clk_hw *hw,
        unsigned int index);

static inline long divider_round_rate(struct clk_hw *hw, unsigned long rate,
                                      unsigned long *prate,
                                      const struct clk_div_table *table,
                                      u8 width, unsigned long flags)
{
    return divider_round_rate_parent(hw, clk_hw_get_parent(hw),
                                     rate, prate, table, width, flags);
}

static inline long divider_ro_round_rate(struct clk_hw *hw, unsigned long rate,
        unsigned long *prate,
        const struct clk_div_table *table,
        u8 width, unsigned long flags,
        unsigned int val)
{
    return divider_ro_round_rate_parent(hw, clk_hw_get_parent(hw),
                                        rate, prate, table, width, flags,
                                        val);
}

int __clk_determine_rate(struct clk_hw *core, struct clk_rate_request *req);
int __clk_mux_determine_rate(struct clk_hw *hw,
                             struct clk_rate_request *req);

int hw_clks_register(struct clk_hw_onecell_data *hw_clock_clks);

int hw_clks_init(struct clk_hw *hw);

int clk_hw_register(struct clk_hw *hw);

int clk_hw_unregister(struct clk_hw *hw);

hal_clk_status_t clk_hw_set_rate(struct clk_hw *hw, unsigned long rate);

struct clk_core *clk_core_get(hal_clk_type_t type, hal_clk_id_t id);

hal_clk_status_t clk_core_is_enabled(struct clk_core *core);

hal_clk_status_t clk_core_enable(struct clk_core *core);

hal_clk_status_t clk_core_disable(struct clk_core *core);

struct clk_core *clk_core_get_parent(struct clk_core *core);

hal_clk_status_t clk_core_set_parent(struct clk_core *core, struct clk_core *parent);

u32 clk_core_get_rate(struct clk_core *core);

hal_clk_status_t clk_core_set_rate(struct clk_core *core, struct clk_core *p_core, unsigned long rate);

u32 clk_core_recalc_rate(struct clk_core *core, struct clk_core *p_core);

u32 clk_core_round_rate(struct clk_core *core, u32 rate);

#endif /* __HAL_CLOCK_H__ */

