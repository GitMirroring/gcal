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
    #define TESTFILE_READ_LINE "test_file-io-read_line.output"
    #define LINE1 "hurzilein"
    #define LINE2 "blubber opt blah"
    char *inputtext;

    // prepare testfile
    f=fopen(TESTFILE_READ_LINE, "w");
    sprintf (s1, _(LINE1));
    print_text (f, s1);
    sprintf (s1, _(LINE2));
    print_text (f, s1);
    fclose(f);

    //read file again
    printf("XXX read line\n");
    f=fopen(TESTFILE_READ_LINE, "r");
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

START_TEST(test_insert_response_line)
{
    FILE *f;
    #define TESTFILE_INSERT_RESPONSE_LINE "test_file-io-insert_response_line.output"
    #define LINE1 "hurzilein"
    #define LINE2 "blubber opt blah"
    char *inputtext;

    // prepare testfile
    f=fopen(TESTFILE_INSERT_RESPONSE_LINE, "w");
    sprintf (s1, _(LINE1));
    print_text (f, s1);
    sprintf (s1, _(LINE2));
    print_text (f, s1);
    fclose(f);

/*XXX what is this??
char **insert_response_file (FILE *fp, char *filename, const char *opt_list, Uint *my_argc_max, int *my_argc,
                               char *my_argv[])
/ *!
   Tries to manage a response file @FILE argument given in the command line.
     Inserts the options and commands found in file @FILE (name delivered
     in `filename' and its file pointer in `fp') into `my_argv[]' and sets
     delivered `&my_argc' and perhaps `&my_argc_max' to according "new"
     values.  Uses the global text buffer `s1' internally.  Returns the
     build `my_argv[]' ptr vector.
* /
*/
}

END_TEST

START_TEST(test_write_log_file)
{
    FILE *f;
    #define TESTFILE_WRITE_LOG_FILE "test_file-io-write_log_file.output"
    #define LINE1 "hurzilein"
    #define LINE2 "blubber opt blah"
    char *inputtext;

    // prepare testfile
    f=fopen(TESTFILE_WRITE_LOG_FILE, "w");
    sprintf (s1, _(LINE1));
    print_text (f, s1);
    sprintf (s1, _(LINE2));
    print_text (f, s1);
    fclose(f);

/*XXX what is this??
  void 
    write_log_file (const char *filename, const Fmode_enum mode, const char *mode_txt, const char *created_txt, const int argc, char *argv[]) 
/ *! 
   Writes the contents of the environment variable $GCAL, which is already 
     stored in `argc' and the arguments of command line either into a 
     response file (MODE==REsponse) or into a shell script (MODE==SCript); 
     other settings to `mode' will `abort()' the program immediately. 
* / 
*/
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
    tcase_add_test(tc_core, test_insert_response_line);
    tcase_add_test(tc_core, test_write_log_file);

    suite_add_tcase(s, tc_core);

    return s;
}

