#include "../config.h"
#include <stdlib.h>
#include <stdio.h>

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
    SRunner *sr;

    init_global_variables();

    sr = srunner_create(gcal_suite_file_io("file_io"));
    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    total_number_failed+=number_failed;
    srunner_free(sr);

    return (total_number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
