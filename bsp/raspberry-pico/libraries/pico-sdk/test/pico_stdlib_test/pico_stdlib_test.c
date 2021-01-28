/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <inttypes.h>
#include "pico/stdlib.h"
#include "pico/bit_ops.h"

int main() {
    setup_default_uart();

    puts("Hellox, worlxxcd!");
    printf("Hello world %d\n", 2);
#if PICO_NO_HARDWARE
    puts("This is native");
#endif
#if PICO_NO_FLASH
    puts("This is no flash");
#endif

    for (int i = 0; i < 64; i++) {
        uint32_t x = 1 << i;
        uint64_t xl = 1ull << i;
//        printf("%d %u %u %u %u \n", i, (uint)(x%10u), (uint)(x%16u), (uint)(xl %10u), (uint)(xl%16u));
        printf("%08x %08x %016llx %016llx\n", (uint) x, (uint) __rev(x), (unsigned long long) xl,
               (unsigned long long) __revll(xl));
    }

    for (int i = 0; i < 8; i++) {
        sleep_ms(500);
        printf( "%" PRIu64 "\n", to_us_since_boot(get_absolute_time()));
    }
    absolute_time_t until = delayed_by_us(get_absolute_time(), 500000);
    printf("\n");
    for (int i = 0; i < 8; i++) {
        sleep_until(until);
        printf("%" PRIu64 "\n", to_us_since_boot(get_absolute_time()));
        until = delayed_by_us(until, 500000);
    }
    puts("DONE");
}

void test1() {
    uint32_t x = 0;
    for (int i = 0; i < 1000; i++) {
        x += __builtin_popcount(i);
        x += __builtin_popcountl(i);
        x += __builtin_popcountll(i * 1234567ll);
        x += __builtin_clz(i);
        x += __builtin_clzl(i);
        x += __builtin_clzll(i * 1234567ll);
        x += __builtin_ctz(i);
        x += __builtin_ctzl(i);
        x += __builtin_ctzll(i * 1234567ll);
    }
    if (x > 12345677) {
        puts("ok");
    }
}

#if 0
struct event {

};

// something might be asyncrhonous.. it communicates the result via the event
void do_something(struct event *e, int a, unsigned int b, char *c) {
    if (a == b) puts(c);
}

int32_t event_result_timeout_ms(struct event *e, int32_t timeout_ms);
int32_t event_result_timeout_us(struct event *e, int32_t timeout_us);
bool is_event_done(struct event *e);
// asserts if not done
int32_t event_result(struct event *e);
void event_set_callback(struct event *e, void (*callback)(struct event *e));
void init_multi_event(struct event *target, struct event **events, uint event_count);

#define timeout_ms_result(f, timeout) ({ \
    struct event __event; \
    struct event *event = &__event; \
    (f); \
    event_result_timeout_ms(event, timeout); \
    })

#define blocking_result(f) timeout_ms_result(f, -1)
#define on_complete(f, cb) ({ \
    static struct event __event; \
    struct event *event = &__event; \
    (f); \
    event_set_callback(event, my_callback); \
    })

void test2() {
    // just playing with blocking syntax
    struct event e;
    do_something(&e, 1, 1, "Hello");
    uint32_t result = event_result_timeout_ms(&e, -1);
}

void test3() {
    uint32_t result = blocking_result(do_something(event, 1, 1, "Hello"));
}

void test4() {
    struct event e;
    do_something(&e, 1, 1, "Hello");
    // this would poll (down to hardware if there is no asynchronous mechanism)
    while (!is_event_done(&e)) {
        puts("waiting");
    }
    int32_t result = event_result(&e);
}

void my_callback(struct event *event) {
    puts("Its done");
    int32_t result = event_result(event);
}

void test5() {
    static struct event e;
    do_something(&e, 1, 1, "Hello");
    event_set_callback(&e, my_callback);
}

void test6() {
    on_complete(do_something(event, 1, 1, "Hello"), my_callback);
}

static struct event e1;
static struct event e2;
static struct event *events[2] = {&e1, &e2};
static struct event multi;

void test7() {
    init_multi_event(&multi,events, count_of(events));
    do_something(&e1, 1, 1, "Hello");
    do_something(&e2, 1, 3, "Hello");
    // something like this
}

struct dimpl {
    uint8_t type;
};

struct doodad {
    struct dimpl *type;
    uint32_t param;
};

struct dimpl indefinite_waiter = {
        .type = 1
};

extern struct dimpl INDEFINITE_WAIT;

struct dimpl ms_waiter = {
        .type = 1
};

struct doodad blocking_with_timeout_ms(uint32_t ms) {
    struct doodad rc = {
        .type = &ms_waiter,
        .param = ms
    };
    return rc;
}

struct result {

};

struct result my_api_call(int arg, float x, struct doodad behavior) {

}
#endif