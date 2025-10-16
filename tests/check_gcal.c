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

Suite *gcal_suite_file_io(char *testname);
Suite *gcal_suite_hd_astro(char *testname);
Suite *gcal_suite_hd_data(char *testname);
Suite *gcal_suite_hd_use(char *testname);
Suite *gcal_suite_help(char *testname);
Suite *gcal_suite_print(char *testname);
Suite *gcal_suite_rc_astro(char *testname);
Suite *gcal_suite_rc_check(char *testname);
Suite *gcal_suite_rc_insert(char *testname);
Suite *gcal_suite_rc_use(char *testname);
Suite *gcal_suite_rc_utils(char *testname);
Suite *gcal_suite_tcal(char *testname);
Suite *gcal_suite_tty(char *testname);
Suite *gcal_suite_utils(char *testname);


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
    int number_failed, total_number_failed=0;
    SRunner *sr; /* only one runner could be used to handle everything */

    init_global_variables();

    sr = srunner_create(gcal_suite_file_io("file_io"));
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    total_number_failed+=number_failed;
    srunner_free(sr);

    sr = srunner_create(gcal_suite_hd_astro("hd"));
    srunner_add_suite(sr, gcal_suite_hd_data("hd"));
    srunner_add_suite(sr, gcal_suite_hd_use("hd"));
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    total_number_failed+=number_failed;
    srunner_free(sr);

    sr = srunner_create(gcal_suite_rc_astro("rc"));
    srunner_add_suite(sr, gcal_suite_rc_check("rc"));
    srunner_add_suite(sr, gcal_suite_rc_insert("rc"));
    srunner_add_suite(sr, gcal_suite_rc_use("rc"));
    srunner_add_suite(sr, gcal_suite_rc_utils("rc"));
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    total_number_failed+=number_failed;
    srunner_free(sr);

    sr = srunner_create(gcal_suite_help("stuff"));
    srunner_add_suite(sr, gcal_suite_tty("stuff"));
    srunner_add_suite(sr, gcal_suite_utils("stuff"));
    srunner_add_suite(sr, gcal_suite_rc_utils("stuff"));
    srunner_add_suite(sr, gcal_suite_print("stuff")); // freopen(stdout) is needed, so lets doit last
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    total_number_failed+=number_failed;
    srunner_free(sr);


    return (total_number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
