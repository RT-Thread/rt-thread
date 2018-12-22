/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
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

#include <stdio.h>
#include <string.h>

#include "sdk.h"
#include "usdhc_test.h"
#include "usdhc/usdhc_ifc.h"
#include "registers/regsusdhc.h"
#include "utility/menu.h"

static int usdhc_test_pio(void);
static int usdhc_test_adma(void);
static int usdhc_test_adma_intr(void);
static int usdhc_test_emmc(void);
static int emmc_test_dump(void);
static int emmc_test_boot(void);
static int emmc_test_width(void);
static int emmc_test_ack(void);
static test_return_t mmc_test(unsigned int bus_width, uint32_t instance);

static usdhc_test_t usdhc_tests[] = {
    {"usdhc polling IO", usdhc_test_pio},
    {"usdhc ADMA polling", usdhc_test_adma},
    {"usdhc ADMA interrupt", usdhc_test_adma_intr},
    {"**emmc special", usdhc_test_emmc},
};

static usdhc_test_t emmc_tests[] = {
    {"dump configure info", emmc_test_dump},
    {"set boot partition", emmc_test_boot},
    {"set bus width", emmc_test_width},
    {"set boot ack", emmc_test_ack},
};

static char *emmc_partition[] = {
    "user partition",
    "boot partition #1",
    "boot partition #2",
};

static char *emmc_bus_width[] = {
    "1 bit SDR",
    "4 bit SDR",
    "8 bit SDR",
    "4 bit DDR",
    "8 bit DDR",
};

static char *emmc_boot_ack[] = {
    "enable",
    "disable",
};

//static uint32_t emmc_base_addr;

/* Buffer Definition */
static int mmc_test_src[MMC_TEST_BUF_SIZE + MMC_CARD_SECTOR_BUFFER];
static int mmc_test_dst[MMC_TEST_BUF_SIZE + MMC_CARD_SECTOR_BUFFER];
static int mmc_test_tmp[MMC_TEST_BUF_SIZE + MMC_CARD_SECTOR_BUFFER];

/********************************************* Global Function ******************************************/
test_return_t mmc_sd_test(unsigned int bus_width, uint32_t instance)
{
    return mmc_test(bus_width, instance);
}

int usdhc_test(void)
{
    int retv = SUCCESS, idx;
    char sel;

    printf("\n---- Running uSDHC test, type 'x' to exit.\n");

    do {
        printf("Make sure to insert an MMC/SD card into SD slot #3\n");

        printf("Please select test:\n");
        for (idx = 0; idx < (sizeof(usdhc_tests) / sizeof(usdhc_test_t)); idx++) {
            printf("\t%d - %s\n", idx, usdhc_tests[idx].name);
        }
        printf("\tx - to exit.\n");

        do {
            sel = getchar();
        } while (sel == (char)0xFF);

        if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        idx = sel - '0';

        if ((idx >= 0) && (idx < (sizeof(usdhc_tests) / sizeof(usdhc_test_t)))) {
            printf("\n");
            retv = usdhc_tests[idx].test();
            if (retv == TRUE) {
                printf("\n%s test PASSED.\n\n", usdhc_tests[idx].name);
            } else {
                printf("\n%s test FAILED.\n\n", usdhc_tests[idx].name);
            }
        }
    } while (TRUE);

    return retv;
}

/********************************************* Static Function ******************************************/

static int usdhc_test_pio(void)
{
    int retv = TRUE;

    /* MMC - 8 bit, SD - 4 bit  */
//    retv = mmc_test(8, USDHC3_BASE_ADDR);
    retv = mmc_test(8, HW_USDHC3);

    return retv;
}

static int usdhc_test_adma(void)
{
    int retv = TRUE;

//    SDHC_ADMA_mode = TRUE;
    set_card_access_mode(1, 0);
    /* MMC - 8 bit, SD - 4 bit  */
//    retv = mmc_test(8, USDHC3_BASE_ADDR);    
    retv = mmc_test(8, HW_USDHC3);

//    SDHC_ADMA_mode = FALSE;

    return retv;
}

static int usdhc_test_adma_intr(void)
{
    int retv;

//    SDHC_INTR_mode = SDHC_ADMA_mode = TRUE;
    set_card_access_mode(1, 0);
    /* MMC - 8 bit, SD - 4 bit  */
//    retv = mmc_test(8, USDHC3_BASE_ADDR);
    retv = mmc_test(8, HW_USDHC3);
    
//    SDHC_INTR_mode = SDHC_ADMA_mode = FALSE;

    return retv;
}

static int emmc_test_dump(void)
{
//    emmc_print_cfg_info(emmc_base_addr);
    emmc_print_cfg_info(HW_USDHC3);
    
    return TRUE;
}

static int emmc_test_boot(void)
{
    int idx;
    char sel;

    do {
        printf("Please select:\n");

        for (idx = 0; idx < (sizeof(emmc_partition) / sizeof(char *)); idx++) {
            printf("\t%d - %s\n", idx, emmc_partition[idx]);
        }
        printf("\tx - to exit.\n");

        do {
            sel = getchar();
        } while (sel == (char)0xFF);

        if (sel == 'x') {
            break;
        }

        idx = sel - '0';

        if ((idx >= 0) && (idx < (sizeof(emmc_partition) / sizeof(char *)))) {
            mmc_set_boot_partition(HW_USDHC3, idx);
            break;
        }
    } while (TRUE);

    return TRUE;
}

static int emmc_test_width(void)
{
    int idx;
    char sel;

    do {
        printf("Please select:\n");

        for (idx = 0; idx < (sizeof(emmc_bus_width) / sizeof(char *)); idx++) {
            printf("\t%d - %s\n", idx, emmc_bus_width[idx]);
        }
        printf("\tx - to exit.\n");

        do {
            sel = getchar();
        } while (sel == (char)0xFF);

        if (sel == 'x') {
            break;
        }

        idx = sel - '0';

        if ((idx >= 0) && (idx < (sizeof(emmc_bus_width) / sizeof(char *)))) {
            mmc_set_boot_bus_width(HW_USDHC3, idx);
            break;
        }
    } while (TRUE);

    return TRUE;
}

/*!
 * @brief Run eMMC Card Test - Initialize the card, read/write data from/to card
 * 
 * @return             0 if successful; 1 otherwise
 */
static int emmc_test_ack(void)
{
    int idx;
    char sel;

    do {
        printf("Please select:\n");

        for (idx = 0; idx < (sizeof(emmc_boot_ack) / sizeof(char *)); idx++) {
            printf("\t%d - %s\n", idx, emmc_boot_ack[idx]);
        }
        printf("\tx - to exit.\n");

        do {
            sel = getchar();
        } while (sel == (char)0xFF);

        if (sel == 'x') {
            break;
        }

        idx = sel - '0';

        if ((idx >= 0) && (idx < (sizeof(emmc_boot_ack) / sizeof(char *)))) {
            mmc_set_boot_ack(HW_USDHC3, !idx);
            break;
        }
    } while (TRUE);

    return TRUE;
}

/*!
 * @brief Run eMMC Card Test - Initialize the card, read/write data from/to card
 * 
 * @return             0 if successful; 1 otherwise
 */
static int usdhc_test_emmc(void)
{
    int idx;
    char sel;
    uint32_t instance = HW_USDHC3;
    printf("\n\tInitializing eMMC chip.\n");
     
//    emmc_base_addr = USDHC3_BASE_ADDR;

    if (FAIL == card_emmc_init(instance)) {
        printf("Initialize eMMC failed.\n");
        return FALSE;
    }

    do {
        printf("Please select function:\n");
        for (idx = 0; idx < (sizeof(emmc_tests) / sizeof(usdhc_test_t)); idx++) {
            printf("\t%d - %s\n", idx, emmc_tests[idx].name);
        }
        printf("\tx - to exit.\n");

        do {
            sel = getchar();
        } while (sel == (char)0xFF);

        if (sel == 'x') {
            printf("\nTest exit.\n");
            break;
        }

        idx = sel - '0';

        if ((idx >= 0) && (idx < (sizeof(emmc_tests) / sizeof(usdhc_test_t)))) {
            printf("\n");
            emmc_tests[idx].test();
        }

    } while (TRUE);

    return TRUE;
}

/*!
 * @brief Run eMMC Card Test - Initialize the card, read/write data from/to card
 *
 * @param bus_width    Bus width
 * @param instance     Instance number of the uSDHC module.
 * 
 * @return             TEST_PASSED if successful; TEST_FAILED otherwise
 */
static test_return_t mmc_test(unsigned int bus_width, uint32_t instance)
{
    int status, idx, result;
    const char* indent = menu_get_indent();

    printf("%s1. Init card.\n", indent);

    /* Initialize card */
    status = card_init(instance, bus_width);

    if (status == FAIL) {
        printf("%sSD/MMC initialize failed.\n", indent);
        return TEST_FAILED;
    }

    printf("%s2. Card -> TMP.\n", indent);

    /* Initialize buffer */
    memset(mmc_test_src, 0x5A, MMC_TEST_BUF_SIZE);
    memset(mmc_test_dst, 0xA5, MMC_TEST_BUF_SIZE);

    /* Store card data to temporary buffer */
    status = card_data_read(instance, mmc_test_tmp, MMC_TEST_BUF_SIZE * sizeof(int), MMC_TEST_OFFSET);
    if (status == FAIL) {
        printf("%s%d: SD/MMC data read failed.\n", indent, __LINE__);
        return TEST_FAILED;
    }

    /* Wait for transfer complete */
    if (read_usdhc_intr_mode() == TRUE) {
//    if (SDHC_INTR_mode == TRUE) {
        do {
            card_xfer_result(instance, &result);
        } while (result == 0);

        if (result == 2) {
            printf("%s%d: Error status caught.\n", indent, __LINE__);
            return TEST_FAILED;
        }
    }

    printf("%s3. SRC -> Card.\n", indent);

    /* Copy from source to Card */
    status =
        card_data_write(instance, mmc_test_src, MMC_TEST_BUF_SIZE * sizeof(int),
                        MMC_TEST_OFFSET);
    if (status == FAIL) {
        printf("%s%d: SD/MMC data write failed.\n", indent, __LINE__);
        return TEST_FAILED;
    }

    /* Wait for transfer complete */
    if (read_usdhc_intr_mode() == TRUE) {
//    if (SDHC_INTR_mode == TRUE) {
        do {
            card_xfer_result(instance, &result);
        } while (result == 0);

        if (result == 2) {
            printf("%s%d: Error status caught.\n", indent, __LINE__);
            return TEST_FAILED;
        }
    }

    printf("%s4. Card -> DST.\n", indent);

    /* Copy from card to destination */
    status =
        card_data_read(instance, mmc_test_dst, MMC_TEST_BUF_SIZE * sizeof(int),
                       MMC_TEST_OFFSET);
    if (status == FAIL) {
        printf("%s%d: SD/MMC data read failed.\n", indent, __LINE__);
        return TEST_FAILED;
    }

    /* Wait for transfer complete */
    if (read_usdhc_intr_mode() == TRUE) {
//    if (SDHC_INTR_mode == TRUE) {
        do {
            card_xfer_result(instance, &result);
        } while (result == 0);

        if (result == 2) {
            printf("%s%d: Error status caught.\n", indent, __LINE__);
            return TEST_FAILED;
        }
    }

    printf("%s5. TMP -> Card.\n", indent);

    /* Restore from temporary buffer to card */
    status =
        card_data_write(instance, mmc_test_tmp, MMC_TEST_BUF_SIZE * sizeof(int),
                        MMC_TEST_OFFSET);
    if (status == FAIL) {
        printf("%s%d: SD/MMC data write failed.\n", indent, __LINE__);
        return TEST_FAILED;
    }

    /* Wait for transfer complete */
    if (read_usdhc_intr_mode() == TRUE) {
//    if (SDHC_INTR_mode == TRUE) {
        do {
            card_xfer_result(instance, &result);
        } while (result == 0);

        if (result == 2) {
            printf("%s%d: Error status caught.\n", indent, __LINE__);
            return TEST_FAILED;
        }
    }

    printf("%s6. Compare SRC & DST.\n", indent);

    /* Compare loopback data */
    for (idx = 0; idx < MMC_TEST_BUF_SIZE; idx++) {
        if (mmc_test_src[idx] != mmc_test_dst[idx]) {
            printf("%sWord %d mismatch: source - 0x%x, destination - 0x%x\n", indent, idx + 1,
                   mmc_test_src[idx], mmc_test_dst[idx]);
            return TEST_FAILED;
        }
    }

    return TEST_PASSED;
}
