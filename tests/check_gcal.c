#include "../config.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "../src/tailor.h"
#include "../src/common.h"
#if USE_RC
# include "../src/rc-defs.h"
#endif /* USE_RC */
#include "../src/globals.h"
#include "../src/hd-defs.h"
#include "../src/hd-use.h"
#if USE_RC
# include "../src/rc-utils.h"
#endif /* USE_RC */
#include "../src/utils.h"

#include "../src/global-variables.h"
#include <check.h>

Suite *gcal_suite_file_io(void);
Suite *gcal_suite_gcal2txt(void);
Suite *gcal_suite_hd_astro(void);
Suite *gcal_suite_hd_data(void);
Suite *gcal_suite_hd_use(void);
Suite *gcal_suite_help(void);
Suite *gcal_suite_print(void);
Suite *gcal_suite_rc_astro(void);
Suite *gcal_suite_rc_check(void);
Suite *gcal_suite_rc_insert(void);
Suite *gcal_suite_rc_use(void);
Suite *gcal_suite_rc_utils(void);
Suite *gcal_suite_tcal(void);
Suite *gcal_suite_tty(void);
Suite *gcal_suite_txt2gcal(void);
Suite *gcal_suite_utils(void);


START_TEST(test_gcal_base_start)
{
    uint8_t bytes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 170};
    ck_assert_int_eq(bytes[1], 2);
}
END_TEST


START_TEST(test_gcal_base_end)
{
    ck_assert_int_eq(254, 254);
}
END_TEST


static Suite *gcal_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("GCAL");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_gcal_base_start);
    tcase_add_test(tc_core, test_gcal_base_end);

    suite_add_tcase(s, tc_core);

    return s;
}

/* dumy function (normally defined in gcal.c) to make linking possible */
int
eval_longopt (char *longopt, int *longopt_symbolic)
{
 return 0;
}

/* initialize some global variables */
void init_global_variables()
{
  testval = INT_MAX;
  allocate_all_strings (2048, __FILE__, (long) __LINE__);

  sprintf (s1, "%d", YEAR_MAX);
  len_year_max = (int) strlen (s1);
}

int main(void)
{
    int number_failed;
    SRunner *sr;

    init_global_variables();

    sr = srunner_create(gcal_suite());
    srunner_add_suite(sr, gcal_suite_file_io());
    srunner_add_suite(sr, gcal_suite_gcal2txt());
    srunner_add_suite(sr, gcal_suite_hd_astro());
    srunner_add_suite(sr, gcal_suite_hd_data());
    srunner_add_suite(sr, gcal_suite_hd_use());
    srunner_add_suite(sr, gcal_suite_help());
    srunner_add_suite(sr, gcal_suite_print());
    srunner_add_suite(sr, gcal_suite_rc_astro());
    srunner_add_suite(sr, gcal_suite_rc_check());
    srunner_add_suite(sr, gcal_suite_rc_insert());
    srunner_add_suite(sr, gcal_suite_rc_use());
    srunner_add_suite(sr, gcal_suite_rc_utils());
    srunner_add_suite(sr, gcal_suite_tcal());
    srunner_add_suite(sr, gcal_suite_tty());
    srunner_add_suite(sr, gcal_suite_txt2gcal());
    srunner_add_suite(sr, gcal_suite_utils());


    //not really needed: srunner_set_log (sr, "test.log");

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
