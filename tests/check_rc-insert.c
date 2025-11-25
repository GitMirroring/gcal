#include "../config.h"
#include <check.h>
#include <stdlib.h>

#include "../src/tailor.h"
#include "../src/common.h"
#include "../src/rc-defs.h"
#include "../src/globals.h"
#include "../src/hd-use.h"
#include "../src/rc-utils.h"
#include "../src/rc-insert.h"

int length_of_rc_elems_table()
{
    int i = 0;
    if (rc_elems_table==NULL) return 0;
    while (rc_elems_table[i] != (char *) NULL) i++;
    return i;
}

/*
void
insert_line_into_table (char *line_buffer, const char *filename, const long line_number, int *rc_elems,
                        int len_date, int print_twice)
/!
   Inserts a line into `rc_elems_table[]',
     but before this the line is checked and evaluated first
     for TVAR text variables and then for %?... special texts.
*/
START_TEST(test_insert_line_into_table)
{
    int lengthOfTable;
    int rc_elems;
    char *line_buffer;
    const char *filename="IamHere";

    lengthOfTable=length_of_rc_elems_table();
    ck_assert_int_eq(lengthOfTable, 0);

    line_buffer="-c";
    insert_line_into_table (line_buffer, _("`Internal'"), (long) SPECIAL_VALUE, &rc_elems, 1, 1);
    printf("XXX rc_elems: %i\n",rc_elems);

}
END_TEST

Suite *gcal_suite_rc_insert(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_insert_line_into_table);

    suite_add_tcase(s, tc_core);

    return s;
}

