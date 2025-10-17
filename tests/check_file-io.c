#include "../config.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "../src/tailor.h"
#include "../src/common.h"
#include "../src/globals.h"
#include "../src/utils.h"
#include "../src/file-io.h"
#include "../src/tty.h"

START_TEST(test_read_line)
{
    FILE *f;
    #define TESTFILE "test_file-io-read_line.output"
    #define LINE1 "hurzilein"
    #define LINE2 "blubber opt blah"
    char *inputtext;

    // prepare testfile
    f=fopen(TESTFILE, "w");
    sprintf (s1, _(LINE1));
    print_text (f, s1);
    sprintf (s1, _(LINE2));
    print_text (f, s1);
    fclose(f);

    //read file again
    printf("XXX read line\n");
    f=fopen(TESTFILE, "r");
/*
char *file_read_line (FILE *fp, char **line_buffer, int *in_pool, char *pool, char *ptr_pool, const char *filename,
                        long *line_number, int *line_length, const Fmode_enum mode, Bool *is_include, Bool *is_dvar,
                        Bool *is_tvar)
/ *!
   Reads a line of a delivered resource/response file into `&line_buffer'
     using the delivered char vector `pool', which must be allocated by caller
     with size BUF_LEN+1 (BUF_LEN should be "A POWER OF 2", e.g., 4096).
     Returns the position in buffer of the character managed in next call
     by char pointer `ptr_pool', which must be defined by caller; or NULL
     if EOF is detected.
* /

   inputtext=file_read_line(f, 
*/
    fclose(f);
}

END_TEST

Suite *gcal_suite_file_io(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_read_line);

    suite_add_tcase(s, tc_core);

    return s;
}

