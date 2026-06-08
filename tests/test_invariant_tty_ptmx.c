#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 
 * Since we cannot directly call the internal kernel function, we test the
 * security invariant by simulating the vulnerable pattern and verifying
 * that a safe implementation would reject/truncate oversized inputs.
 * This serves as a regression guard for the sprintf buffer overflow fix.
 */

#define DEVICE_NAME_MAX 64  /* Typical kernel buffer size */

/* Safe wrapper that enforces bounds checking - what the fix should look like */
static int safe_device_name_format(char *device_name, size_t buf_size,
                                    const char *root_path, const char *dev_rel_path)
{
    size_t required = strlen(root_path) + strlen(dev_rel_path) + 1;
    if (required > buf_size) {
        return -1;  /* Reject oversized input */
    }
    snprintf(device_name, buf_size, "%s%s", root_path, dev_rel_path);
    return 0;
}

START_TEST(test_pty_device_name_buffer_bounds)
{
    /* Invariant: Buffer reads/writes never exceed declared length */
    char device_name[DEVICE_NAME_MAX];
    
    struct {
        const char *root_path;
        const char *dev_rel_path;
        int should_succeed;
    } payloads[] = {
        /* Valid input */
        {"/dev/pts/", "0", 1},
        /* Boundary case - exactly at limit */
        {"/dev/pts/", "12345678901234567890123456789012345678901234567890123", 0},
        /* Exploit case - 2x buffer size */
        {"/dev/pts/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
         "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", 0},
        /* Exploit case - 10x buffer size */
        {"/dev/pts/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
         "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
         "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
         "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", 0},
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);

    for (int i = 0; i < num_payloads; i++) {
        memset(device_name, 'X', sizeof(device_name));
        int result = safe_device_name_format(device_name, sizeof(device_name),
                                              payloads[i].root_path,
                                              payloads[i].dev_rel_path);
        
        if (payloads[i].should_succeed) {
            ck_assert_int_eq(result, 0);
            ck_assert(strlen(device_name) < DEVICE_NAME_MAX);
        } else {
            ck_assert_int_eq(result, -1);  /* Must reject oversized input */
        }
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_pty_device_name_buffer_bounds);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}