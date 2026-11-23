/*
 * Regression test for the DHCP server lease and lifecycle paths.
 *
 * The test compiles the production implementation (../dhcp_server_raw.c)
 * against the lwIP / RT-Thread stubs in ./mock, so every assertion below runs
 * through the real dhcp_client_find(), dhcp_client_alloc(),
 * dhcp_client_remove_expired(), dhcp_server_periodic_recycle() and the
 * dhcpd_start()/dhcpd_stop() marshalling.  Nothing here re-implements the
 * matching, the expiry rule or the timer bookkeeping.
 *
 * The mock runs sys_timeout()/sys_untimeout() and tcpip_callback() like the
 * lwIP tcpip thread does, so the cases below also fail if start/stop stop
 * registering, cancel or re-arm the periodic recycle timer correctly.
 *
 * Build and run (host, no board required):
 *
 *   cd components/net/lwip-dhcpd/test
 *   make run
 *
 * or directly:
 *
 *   cc -std=c99 -Wall -Wextra -Wno-unused-function -Wno-unused-parameter \
 *      -I mock test_dhcpd_lease.c -o /tmp/dhcpd_lease_test
 *   /tmp/dhcpd_lease_test
 */

#include "../dhcp_server_raw.c"

#define LEASE_MS DHCP_DEFAULT_LEASE_TIME_MS

/* build an address in lwIP's network byte order */
#define IP4(a, b, c, d)                                         \
    ((u32_t)htonl((((u32_t)(a)) << 24) | (((u32_t)(b)) << 16) | \
                  (((u32_t)(c)) << 8) | ((u32_t)(d))))

static int test_failures;

#define CHECK(expr)                                                  \
    do                                                               \
    {                                                                \
        if (!(expr))                                                 \
        {                                                            \
            printf("  FAIL %s:%d: %s\n", __FILE__, __LINE__, #expr); \
            test_failures++;                                         \
        }                                                            \
    } while (0)

static const u8_t mac_owner[6] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
static const u8_t mac_other[6] = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };
static const u8_t mac_third[6] = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x01 };

/* ------------------------------------------------------------ fixtures */

/* forget every timer, including entries a failed case left behind */
static void mock_clear_timers(void)
{
    struct mock_timer *timer = mock_timers;
    struct mock_timer *next;

    while (timer != NULL)
    {
        next = timer->next;
        free(timer);
        timer = next;
    }

    mock_timers = NULL;
    mock_timer_live = 0;
}

/*
 * Reset the fake world: no server, no timer, no callback, an empty "tcpip"
 * mailbox and a caller thread that is not the tcpip thread.
 */
static void mock_world_reset(u32_t now_ms)
{
    mock_reset_clock(now_ms);
    mock_set_caller_name("main");
    mock_udp_used = 0;
    mock_tcpip_queued = 0;
    mock_tcpip_callbacks = 0;
    mock_timer_fires = 0;
    netif_list = NULL;
    mock_clear_timers();
}

static void netif_fixture_init(struct netif *netif, const char *name)
{
    memset(netif, 0, sizeof(*netif));
    netif->name[0] = name[0];
    netif->name[1] = name[1];
    netif->next = NULL;
}

static void lease_server_init(struct dhcp_server *server)
{
    memset(server, 0, sizeof(*server));
}

/* fixture only: put a lease node in the list, as dhcp_client_alloc() would */
static struct dhcp_client_node *lease_add(struct dhcp_server *server,
                                          const u8_t *chaddr, u32_t ipaddr,
                                          u32_t lease_end)
{
    struct dhcp_client_node *node;

    node = mem_malloc(sizeof(*node));
    if (node == NULL)
    {
        printf("out of memory while building the test fixture\n");
        exit(1);
    }

    memset(node, 0, sizeof(*node));
    SMEMCPY(node->chaddr, chaddr, DHCP_MAX_HLEN);
    node->ipaddr.addr = ipaddr;
    node->lease_end = lease_end;

    node->next = server->node_list;
    server->node_list = node;

    return node;
}

static void lease_list_free(struct dhcp_server *server)
{
    struct dhcp_client_node *node = server->node_list;
    struct dhcp_client_node *next;

    while (node != NULL)
    {
        next = node->next;
        mem_free(node);
        node = next;
    }

    server->node_list = NULL;
}

static int lease_count(struct dhcp_server *server)
{
    struct dhcp_client_node *node;
    int count = 0;

    for (node = server->node_list; node != NULL; node = node->next)
    {
        count++;
    }

    return count;
}

/* build a DHCP request the production code has to judge */
static void lease_msg_build(struct dhcp_msg *msg, u8_t *opt, u16_t *len,
                            const u8_t *chaddr, u32_t requested_ip, u8_t hlen)
{
    memset(msg, 0, sizeof(*msg));
    msg->op = DHCP_BOOTREQUEST;
    msg->htype = 1;
    msg->cookie = PP_HTONL(DHCP_MAGIC_COOKIE);
    msg->hlen = hlen;
    SMEMCPY(msg->chaddr, chaddr, DHCP_MAX_HLEN);

    *len = 0;
    if (requested_ip != 0)
    {
        opt[0] = DHCP_OPTION_REQUESTED_IP;
        opt[1] = 4;
        SMEMCPY(&opt[2], &requested_ip, 4);
        *len = 6;
    }
}

/* let the production dhcp_client_find() answer a request of the given hlen */
static struct dhcp_client_node *lease_find_hlen(struct dhcp_server *server,
                                                const u8_t *chaddr,
                                                u32_t requested_ip, u8_t hlen)
{
    struct dhcp_msg msg;
    u8_t opt[6] = { 0 };
    u16_t len;

    lease_msg_build(&msg, opt, &len, chaddr, requested_ip, hlen);

    return dhcp_client_find(server, &msg, opt, len);
}

/* let the production dhcp_client_alloc() answer a request of the given hlen */
static struct dhcp_client_node *lease_alloc_hlen(struct dhcp_server *server,
                                                 const u8_t *chaddr,
                                                 u32_t requested_ip, u8_t hlen)
{
    struct dhcp_msg msg;
    u8_t opt[6] = { 0 };
    u16_t len;

    lease_msg_build(&msg, opt, &len, chaddr, requested_ip, hlen);

    return dhcp_client_alloc(server, &msg, opt, len);
}

/* build a DHCP message and let the production dhcp_client_find() answer it */
static struct dhcp_client_node *lease_find(struct dhcp_server *server,
                                           const u8_t *chaddr,
                                           u32_t requested_ip)
{
    return lease_find_hlen(server, chaddr, requested_ip, DHCP_MAX_HLEN);
}

/* build a DHCP message and let the production dhcp_client_alloc() answer it */
static struct dhcp_client_node *lease_alloc(struct dhcp_server *server,
                                            const u8_t *chaddr,
                                            u32_t requested_ip)
{
    return lease_alloc_hlen(server, chaddr, requested_ip, DHCP_MAX_HLEN);
}

/* ------------------------------------------------------- lease behaviour */

/*
 * REQUESTED_IP ownership: dhcp_client_find() may only hand a lease back to the
 * client that owns it.
 */
static void test_requested_ip_ownership(void)
{
    struct dhcp_server server;
    struct dhcp_client_node *owner;
    u32_t owner_ip = IP4(192, 168, 169, 10);

    printf("[case] requested-ip ownership via dhcp_client_find()\n");

    mock_world_reset(1000);
    lease_server_init(&server);
    owner = lease_add(&server, mac_owner, owner_ip, sys_now() + LEASE_MS);

    /* the owner gets its lease back, by MAC and via REQUESTED_IP */
    CHECK(lease_find(&server, mac_owner, 0) == owner);
    CHECK(lease_find(&server, mac_owner, owner_ip) == owner);

    /* another client must not inherit a lease that belongs to someone else */
    CHECK(lease_find(&server, mac_other, owner_ip) == NULL);
    CHECK(lease_find(&server, mac_other, 0) == NULL);

    /* the rejected requests left the owner's lease in place */
    CHECK(lease_count(&server) == 1);
    CHECK(lease_find(&server, mac_owner, owner_ip) == owner);
    CHECK(owner->ipaddr.addr == owner_ip);

    lease_list_free(&server);
}

/*
 * A foreign REQUESTED_IP must not be handed out through the allocation path
 * either: the requester gets a free pool address and the owner keeps its node.
 */
static void test_alloc_rejects_foreign_requested_ip(void)
{
    struct dhcp_server server;
    struct dhcp_client_node *owner;
    struct dhcp_client_node *other;
    u32_t pool_first = IP4(192, 168, 169, 2);
    u32_t pool_last = IP4(192, 168, 169, 3);

    printf("[case] allocation rejects a foreign REQUESTED_IP\n");

    mock_world_reset(2000);
    lease_server_init(&server);
    server.start.addr = pool_first;
    server.end.addr = pool_last;
    server.current.addr = pool_first;

    owner = lease_add(&server, mac_owner, pool_first, sys_now() + LEASE_MS);

    /* mac_other asks for the address the owner already holds */
    other = lease_alloc(&server, mac_other, pool_first);

    CHECK(other != NULL);
    CHECK(other != owner);
    CHECK(other != NULL && other->ipaddr.addr != owner->ipaddr.addr);
    CHECK(other != NULL && other->ipaddr.addr == pool_last);
    CHECK(lease_count(&server) == 2);

    /* both leases stay reachable through the production lookup */
    CHECK(lease_find(&server, mac_owner, pool_first) == owner);
    CHECK(lease_find(&server, mac_other, 0) == other);

    lease_list_free(&server);
}

/*
 * Expired-lease reclaim: dhcp_client_remove_expired() must unlink and free the
 * expired nodes, keep the live ones, and be idempotent.
 */
static void test_remove_expired(void)
{
    struct dhcp_server server;
    struct dhcp_client_node *live;
    u32_t live_ip = IP4(192, 168, 169, 21);

    printf("[case] expired leases are recycled by dhcp_client_remove_expired()\n");

    mock_world_reset(100000);
    lease_server_init(&server);

    /* list order, newest first: expired tail -> live -> expired head */
    lease_add(&server, mac_owner, IP4(192, 168, 169, 20), sys_now() - 1);
    live = lease_add(&server, mac_other, live_ip, sys_now() + LEASE_MS);
    lease_add(&server, mac_third, IP4(192, 168, 169, 22), sys_now() - LEASE_MS - 1);

    CHECK(lease_count(&server) == 3);
    CHECK(mock_mem_live_count() == 3);

    dhcp_client_remove_expired(&server);

    /* both expired nodes are gone (head and tail), the live one is kept */
    CHECK(lease_count(&server) == 1);
    CHECK(server.node_list == live);
    CHECK(mock_mem_live_count() == 1);
    CHECK(lease_find(&server, mac_owner, 0) == NULL);
    CHECK(lease_find(&server, mac_third, 0) == NULL);
    CHECK(lease_find(&server, mac_other, live_ip) == live);

    /* nothing left to reclaim */
    dhcp_client_remove_expired(&server);
    CHECK(lease_count(&server) == 1);
    CHECK(server.node_list == live);

    lease_list_free(&server);
}

/*
 * The allocation path must reclaim an expired lease before handing out pool
 * addresses: with a single-address pool an un-reclaimed expired node would
 * make the next allocation fail.
 */
static void test_alloc_reclaims_expired(void)
{
    struct dhcp_server server;
    struct dhcp_client_node *node;
    u32_t pool_ip = IP4(192, 168, 169, 2);

    printf("[case] allocation reclaims an expired lease first\n");

    mock_world_reset(300000);
    lease_server_init(&server);
    server.start.addr = pool_ip;
    server.end.addr = pool_ip;
    server.current.addr = pool_ip;

    lease_add(&server, mac_owner, pool_ip, sys_now() - 1);

    node = lease_alloc(&server, mac_other, pool_ip);

    CHECK(node != NULL);
    CHECK(node != NULL && node->ipaddr.addr == pool_ip);
    CHECK(lease_count(&server) == 1);
    CHECK(mock_mem_live_count() == 1);
    CHECK(lease_find(&server, mac_other, pool_ip) == node);
    CHECK(lease_find(&server, mac_owner, 0) == NULL);

    lease_list_free(&server);
}

/*
 * Expiry arithmetic: sys_now() wraps every ~49.7 days, the check must stay
 * correct across the wrap instead of reporting a live lease as expired.
 */
static void test_lease_expiry_across_wrap(void)
{
    struct dhcp_client_node node;

    printf("[case] lease expiry survives the sys_now() wrap\n");

    memset(&node, 0, sizeof(node));

    mock_reset_clock(0xfffff000U);
    node.lease_end = sys_now() + LEASE_MS; /* lease_end wraps past 0 */

    CHECK(node.lease_end < 0xfffff000U);
    CHECK(!dhcp_client_lease_expired(&node));

    mock_reset_clock(0xfffff000U + LEASE_MS - 1);
    CHECK(!dhcp_client_lease_expired(&node));

    mock_reset_clock(0xfffff000U + LEASE_MS);
    CHECK(dhcp_client_lease_expired(&node));

    /*
     * A lease that was never renewed is expired even when the elapsed time
     * passed 2^31 ms (~24.8 days): the check must not fall back to a signed
     * comparison, which would report it as still valid.
     */
    node.lease_end = LEASE_MS; /* lease_start == 0 */
    mock_reset_clock(0x80000000U + LEASE_MS);
    CHECK(dhcp_client_lease_expired(&node));
}

/*
 * The server only serves Ethernet clients: the entry gate must drop a frame
 * whose hardware address length is not 6 instead of comparing it by prefix.
 */
static void test_entry_requires_ethernet_hlen(void)
{
    struct dhcp_msg msg;
    u8_t opt[6] = { 0 };
    u16_t len;
    static const u8_t hlen_cases[] = { 0, 1, 5, 6, 16, 255 };
    size_t i;

    printf("[case] the DHCP entry only accepts Ethernet hardware addresses\n");

    CHECK(DHCP_MAX_HLEN == 6);

    for (i = 0; i < sizeof(hlen_cases); i++)
    {
        lease_msg_build(&msg, opt, &len, mac_owner, 0, hlen_cases[i]);
        CHECK(dhcp_msg_usable(&msg) == (hlen_cases[i] == DHCP_MAX_HLEN));
    }

    lease_msg_build(&msg, opt, &len, mac_owner, 0, DHCP_MAX_HLEN);
    msg.op = DHCP_BOOTREPLY;
    CHECK(!dhcp_msg_usable(&msg));

    lease_msg_build(&msg, opt, &len, mac_owner, 0, DHCP_MAX_HLEN);
    msg.cookie = 0;
    CHECK(!dhcp_msg_usable(&msg));
}

/*
 * A hardware address shorter than an Ethernet address must not hit a stored
 * lease, and must not create one either: both paths run through the production
 * lookup/allocation code.
 */
static void test_short_hlen_never_matches(void)
{
    struct dhcp_server server;
    struct dhcp_client_node *owner;
    u32_t owner_ip = IP4(192, 168, 169, 30);
    u32_t pool_ip = IP4(192, 168, 169, 31);
    u8_t prefix_only[DHCP_MAX_HLEN] = { 0 };
    u8_t hlen;

    printf("[case] a short hardware address never owns a lease\n");

    mock_world_reset(400000);
    lease_server_init(&server);
    server.start.addr = pool_ip;
    server.end.addr = pool_ip;
    server.current.addr = pool_ip;
    owner = lease_add(&server, mac_owner, owner_ip, sys_now() + LEASE_MS);

    /* only the first bytes of the owner's address are present */
    SMEMCPY(prefix_only, mac_owner, sizeof(prefix_only));

    for (hlen = 0; hlen < DHCP_MAX_HLEN; hlen++)
    {
        CHECK(lease_find_hlen(&server, prefix_only, 0, hlen) == NULL);
        CHECK(lease_find_hlen(&server, prefix_only, owner_ip, hlen) == NULL);
        CHECK(lease_alloc_hlen(&server, prefix_only, owner_ip, hlen) == NULL);
        CHECK(lease_count(&server) == 1);
        CHECK(server.node_list == owner);
    }

    /* with the full addresses the same calls do match again */
    CHECK(lease_find(&server, mac_owner, 0) == owner);
    CHECK(lease_find(&server, mac_owner, owner_ip) == owner);

    lease_list_free(&server);
}

/* ------------------------------------------------------- timer lifecycle */

/*
 * start must register exactly one periodic recycle timeout, a repeated start
 * must not stack a second one, and stop must cancel it again.
 */
static void test_start_stop_timer_lifecycle(void)
{
    struct netif netif;

    printf("[case] start/stop register and cancel exactly one recycle timer\n");

    mock_world_reset(1000);
    netif_fixture_init(&netif, "e0");
    netif_list = &netif;

    dhcpd_start("e0");
    CHECK(mock_tcpip_callback_count() == 1); /* marshalled to the tcpip thread */
    CHECK(lw_dhcp_server != NULL);
    CHECK(lw_dhcp_server != NULL && lw_dhcp_server->netif == &netif);
    CHECK(mock_timer_count() == 1);
    CHECK(mock_timer_registered(dhcp_server_periodic_recycle));

    /* the same netif: only the pool is updated, no second timeout */
    dhcpd_start("e0");
    CHECK(mock_tcpip_callback_count() == 2);
    CHECK(mock_timer_count() == 1);

    dhcpd_stop("e0");
    CHECK(mock_tcpip_callback_count() == 3);
    CHECK(lw_dhcp_server == NULL);
    CHECK(mock_timer_count() == 0);
    CHECK(!mock_timer_registered(dhcp_server_periodic_recycle));
    CHECK(mock_mem_live_count() == 0);

    /* stopping again must not crash or double-cancel */
    dhcpd_stop("e0");
    CHECK(mock_tcpip_callback_count() == 4);
    CHECK(mock_timer_count() == 0);

    /* and the server can come back with exactly one timer */
    dhcpd_start("e0");
    CHECK(mock_timer_count() == 1);
    dhcpd_stop("e0");
    CHECK(mock_timer_count() == 0);
    CHECK(!mock_timer_registered(dhcp_server_periodic_recycle));
    CHECK(mock_mem_live_count() == 0);
}

/*
 * The lifecycle entry points may also be reached from the tcpip thread itself
 * (a recv callback, a timeout handler).  Marshalling must detect that and run
 * in place instead of posting a callback that only this thread could run.
 */
static void test_lifecycle_from_tcpip_thread_is_direct(void)
{
    struct netif netif;
    ip4_addr_t pool_start;
    ip4_addr_t pool_end;
    err_t err;

    printf("[case] lifecycle calls on the tcpip thread run in place\n");

    mock_world_reset(500);
    netif_fixture_init(&netif, "e1");
    netif_list = &netif;

    mock_set_caller_name(TCPIP_THREAD_NAME);

    dhcpd_start("e1");
    CHECK(mock_tcpip_callback_count() == 0);
    CHECK(lw_dhcp_server != NULL);
    CHECK(mock_timer_count() == 1);

    dhcpd_stop("e1");
    CHECK(mock_tcpip_callback_count() == 0);
    CHECK(mock_timer_count() == 0);
    CHECK(mock_mem_live_count() == 0);

    /* dhcp_server_start() is a public entry point of its own */
    ip4addr_aton("192.168.169.2", &pool_start);
    ip4addr_aton("192.168.169.10", &pool_end);
    err = dhcp_server_start(&netif, &pool_start, &pool_end);
    CHECK(err == ERR_OK);
    CHECK(mock_tcpip_callback_count() == 0);
    CHECK(mock_timer_count() == 1);

    dhcpd_stop("e1");
    CHECK(mock_timer_count() == 0);

    mock_set_caller_name("main");
}

/*
 * With every pool address held by a live lease, allocation fails (the #11878
 * symptom).  Once the leases expire the periodic timer reclaims them without
 * any incoming packet, and allocation succeeds again.
 */
static void test_pool_exhausted_then_recycled(void)
{
    struct netif netif;
    struct dhcp_server *server;
    struct dhcp_client_node *node;
    u32_t pool_first = IP4(192, 168, 169, 2);
    u32_t pool_last = IP4(192, 168, 169, 3);

    printf("[case] a full pool rejects allocation until leases expire\n");

    mock_world_reset(1000);
    netif_fixture_init(&netif, "e0");
    netif_list = &netif;

    dhcpd_start("e0");
    server = lw_dhcp_server;
    CHECK(server != NULL);
    if (server == NULL)
    {
        return;
    }

    server->start.addr = pool_first;
    server->end.addr = pool_last;
    server->current.addr = pool_first;

    lease_add(server, mac_owner, pool_first, sys_now() + LEASE_MS / 2);
    lease_add(server, mac_other, pool_last, sys_now() + LEASE_MS / 2);

    CHECK(lease_alloc(server, mac_third, 0) == NULL);
    CHECK(lease_count(server) == 2);

    /* time passes, no DHCP packet arrives, only the recycle timer runs */
    mock_advance_clock(LEASE_MS / 2 + DHCPD_RECYCLE_INTERVAL_MS);
    CHECK(lease_count(server) == 0);
    CHECK(mock_timer_count() == 1); /* the handler re-armed exactly once */

    node = lease_alloc(server, mac_third, 0);
    CHECK(node != NULL);
    CHECK(node != NULL && node->ipaddr.addr == pool_first);
    CHECK(lease_count(server) == 1);

    dhcpd_stop("e0");
    CHECK(mock_timer_count() == 0);
    CHECK(mock_mem_live_count() == 0);
}

/*
 * The reported field failure: a client leases an address, disappears, and no
 * DHCP packet arrives for longer than the whole 32-bit millisecond period.
 * The periodic recycle timer alone must keep the pool usable; the unsigned
 * expiry check must also keep a lease valid while the clock wraps.
 */
static void test_periodic_recycle_across_full_clock_wrap(void)
{
    struct netif netif;
    struct dhcp_server *server;
    struct dhcp_client_node *node;
    u32_t pool_ip = IP4(192, 168, 169, 9);
    unsigned long long idle_ms = 0;
    unsigned long fires_before;

    printf("[case] periodic recycle survives a full 2^32 ms idle period\n");

    /* start one tick before the clock wraps so the next lease crosses it */
    mock_world_reset(0xffff0000U - DHCPD_RECYCLE_INTERVAL_MS);
    netif_fixture_init(&netif, "e0");
    netif_list = &netif;

    dhcpd_start("e0");
    server = lw_dhcp_server;
    CHECK(server != NULL);
    if (server == NULL)
    {
        return;
    }

    server->start.addr = pool_ip;
    server->end.addr = pool_ip;
    server->current.addr = pool_ip;

    /* a lease that expired before the server even got a packet again */
    lease_add(server, mac_owner, pool_ip, sys_now() - LEASE_MS - 1);
    CHECK(lease_count(server) == 1);

    mock_advance_clock(DHCPD_RECYCLE_INTERVAL_MS);
    CHECK(lease_count(server) == 0); /* reclaimed by the timer alone */
    CHECK(mock_timer_count() == 1);

    /* a lease issued just before the wrap ends after it: it must stay valid */
    node = lease_add(server, mac_third, pool_ip, sys_now() + LEASE_MS);
    CHECK(node->lease_end < sys_now());
    mock_advance_clock(2 * DHCPD_RECYCLE_INTERVAL_MS);
    CHECK(lease_count(server) == 1);
    CHECK(lease_find(server, mac_third, 0) == node);

    /* now stay idle for more than one whole 32-bit millisecond period */
    fires_before = mock_timer_fires;
    while (idle_ms <= 0x100000000ULL)
    {
        mock_advance_clock(DHCPD_RECYCLE_INTERVAL_MS);
        idle_ms += DHCPD_RECYCLE_INTERVAL_MS;
    }

    CHECK(mock_timer_fires > fires_before);
    CHECK(mock_timer_count() == 1);  /* still one registration, no pile-up */
    CHECK(lease_count(server) == 0); /* the long-idle lease was reclaimed */

    /* the reclaimed address is allocatable again, with no packet ever seen */
    node = lease_alloc(server, mac_other, 0);
    CHECK(node != NULL);
    CHECK(node != NULL && node->ipaddr.addr == pool_ip);

    dhcpd_stop("e0");
    CHECK(mock_timer_count() == 0);
    CHECK(mock_mem_live_count() == 0);
}

int main(void)
{
    test_requested_ip_ownership();
    test_alloc_rejects_foreign_requested_ip();
    test_remove_expired();
    test_alloc_reclaims_expired();
    test_lease_expiry_across_wrap();
    test_entry_requires_ethernet_hlen();
    test_short_hlen_never_matches();
    test_start_stop_timer_lifecycle();
    test_lifecycle_from_tcpip_thread_is_direct();
    test_pool_exhausted_then_recycled();
    test_periodic_recycle_across_full_clock_wrap();

    CHECK(mock_mem_live_count() == 0);
    CHECK(mock_timer_count() == 0);

    if (test_failures != 0)
    {
        printf("%d check(s) failed\n", test_failures);
        return 1;
    }

    printf("All dhcpd lease regression tests passed!\n");

    return 0;
}
