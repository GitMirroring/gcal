/*!
*  \file global-variables.h
*  \brief this file contains all global definitions that are also used in tests
*/
/*
*  Copyright (c) 1994, 95, 96, 1997, 2000, 2011 Thomas Esken
*  Copyright (c) 2010, 2011, 2013, 2014 Free Software Foundation, Inc.
*
*  This software doesn't claim completeness, correctness or usability.
*  On principle I will not be liable for ANY damages or losses (implicit
*  or explicit), which result from using or handling my software.
*  If you use this software, you agree without any exception to this
*  agreement, which binds you LEGALLY !!
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the `GNU General Public License' as published by
*  the `Free Software Foundation'; either version 3, or (at your option)
*  any later version.
*
*  You should have received a copy of the `GNU General Public License'
*  along with this program; if not, write to the:
*
*/


/*
*  Include header files.
*/
#include "tailor.h"
#if HAVE_ASSERT_H
# include <assert.h>
#endif
#if HAVE_CTYPE_H
# include <ctype.h>
#endif
#if HAVE_LIMITS_H
# include <limits.h>
#endif
#if HAVE_UNISTD_H
# include <unistd.h>
#endif
//#if (!HAVE_SIGNAL_H || !HAVE_SIGNAL) && HAVE_SYS_TYPES_H
///* Otherwise "gcal.h" includes <sys/types.h>. */
//# include <sys/types.h>
//#endif
#if HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif
#ifdef GCAL_EPAGER
# include <fcntl.h>
# if !HAVE_DUP
#  define dup(old)        (fcntl(old, F_DUPFD, 0))
# endif
# if !HAVE_DUP2
#  define dup2(old, new)  (close(new), fcntl(old, F_DUPFD, new))
# endif
# if HAVE_SYS_WAIT_H
#  include <sys/wait.h>
# endif
#endif /* GCAL_EPAGER */
#include "common.h"
#if USE_RC
# include "rc-defs.h"
#endif /* USE_RC */
#include "globals.h"
#include "file-io.h"
#include "hd-defs.h"
#include "hd-data.h"
#include "hd-use.h"
#include "help.h"
#include "print.h"
#if USE_RC
# include "rc-use.h"
# include "rc-utils.h"
#endif /* USE_RC */
#include "tty.h"
#include "utils.h"
//#include "gcal.h"



/*
*  Set Borland/Turbo-C specific MSDOS stack length in case USE_RC is defined  ;<
*/
#if USE_RC
# if defined(MSDOS) && defined(__TURBOC__)
#  include <dos.h>
extern Uint _stklen = 0x4000;
# endif
#endif



/*
*  static functions prototypes.
*/
__BEGIN_DECLARATIONS
/*
************************************************** Defined in `gcal.c'.
*/
static Bool
  is_correct_date_format __P_ ((char *format_txt,
				Bool * use_day_suffix,
				Bool * use_short3_day_name,
				Bool * use_day_zeroleaded,
				Bool * use_year_zeroleaded));
static void
  rearrange_argv __P_ ((const char *opt_list, int *argc, char *argv[]));
static void check_command_line __P_ ((int argc, char *argv[]));
static void build_month_list __P_ ((char *argv[]));
static void eliminate_invalid_data __P_ ((void));
static void pseudo_blank_conversion __P_ ((char **text));
#if USE_RC
static int further_check __P_ ((char **option));
#endif
__END_DECLARATIONS
/*
*  GLOBAL variables definitions.
*/

/*! Number of days in Julian/Gregorian month. */
const int dvec[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/*! Number of past days of Julian/Gregorian month. */
const int mvec[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

/*!
   The long option table is a vector of `Lopt_struct' terminated by an element
     containing a `long_name' which is zero!
   All initialization strings of the structure member `long_name' CAN be
     entered case insensitive (it is recommended to use them in lower-case
     letters only),  but in an ascending lexical sort order, and the table
     MUST be initialized by distinguishable texts given to the structure
     member `long_name'.
   The table structure is as follows:
     `symbolic_name': The symbolic name of the long option (a distingushable
                        number [int]).
     `long_name':     The full name of the long option (case insensitive.)
     `short_name':    A list of short options (maximum 5 (==LARG_MAX-1))
                        terminated by NULL, its order corresponds to the order
                        of the field `largs' (case sensitive), means "a" is
                        another option than "A".
     `larg_mode':     States whether an option requires an argument or not.
                        LARG_NO or 0 means:
                          Option may not have an argument, e.g. `--foo'
                        LARG_NO_OR_ONE or 1 means:
                          Option may have an argument,
                          which is either SPECIAL or GIVEN, e.g. `--foo'
                          or `--foo=BAR' or `--foo=ARG'
                        LARG_ONE or 2 means:
                          Option must have an argument,
                          which must be either SPECIAL if one or more `largs'
                          are defined, or which must be GIVEN if no `largs'
                          are defined, e.g. `--foo=BAR' or `--foo=ARG'
                        LARG_ONE_OR_ARG or 3 means:
                          Option must have an argument,
                          which could be either SPECIAL if one or more `largs'
                          are defined, or which could be GIVEN if one ore more
                          `largs' are defined, but none of these `largs' match
                          the GIVEN argument, e.g. `--foo=BAR' or `--foo=ARG'
                        If this field is set to LARG_NO_OR_ONE and NO argument
                        trails the option, the `short_name[0]' contains
                        the default value of the argument and is returned!
                        It's an ILLEGAL case to set this field to
                        LARG_ONE_OR_ARG and NO `largs' are defined in the
                        `lopt[]' table, but one or more `short_name' entries!
     `largs':         A list of possible SPECIAL arguments (maximum 5
                        (==LARG_MAX-1)) terminated by NULL, from which only
                        one may be selected at a time.
                      If its first element is set to NULL, any GIVEN argument
                        is allowed, otherwise only one of the listed SPECIAL
                        arguments.
                      The SPECIAL arguments may be abbreviated in case this
                        is done unambigously; and they can be given case
                        insensitive.
*/
const Lopt_struct lopt[] = {
/*
  { int symbolic_name, char *long_name, char *short_name[LARG_MAX], int larg_mode, char *largs[LARG_MAX] }
*/
#if USE_RC
  {
   SYM_ADJUST_VALUE,
   "adjust-value",
   {NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_ALTERNATIVE_FORMAT,
   "alternative-format",
   {"A", NULL},
   LARG_NO,
   {NULL}
   },
#endif
  {
   SYM_ASTRONOMICAL_HDY,
   "astronomical-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_ATMOSPHERE,
   "atmosphere",
   {NULL},
   LARG_ONE,
   {NULL}
   },
#endif
  {
   SYM_BAHAI_HDY,
   "bahai-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_BAHAI_MTH,
   "bahai-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_BIORHYTHM_AXIS_LEN,
   "biorhythm-axis",
   {NULL},
   LARG_ONE,
   {NULL}
   },
#endif
  {
   SYM_BLOCKS,
   "blocks",
   {"b", NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_CALENDAR_DATES,
   "calendar-dates",
   {"j", "jb", NULL},
   LARG_ONE,
   {"special", "both", NULL}
   },
  {
   SYM_CC_HDY,
   "cc-holidays",
   {"q", NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_CELTIC_HDY,
   "celtic-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_CHINESE_FLEXIBLE_HDY,
   "chinese-flexible-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_CHINESE_FLEXIBLE_MTH,
   "chinese-flexible-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_CHINESE_HDY,
   "chinese-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_CHINESE_MTH,
   "chinese-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_CHRISTIAN_HDY,
   "christian-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_COPTIC_MTH,
   "coptic-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_LICENSE2,
   "copyleft",
   {"L", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_LICENSE3,
   "copyright",
   {"L", NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_CYCLE_END,
   "cycle-end",
   {NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_CYCLE_STEP,
   "cycle-step",
   {NULL},
   LARG_ONE,
   {NULL}
   },
#endif
  {
   SYM_DATE_FORMAT,
   "date-format",
   {"!\001", "!\002", "!\003", /* e.g.: "!\004", */ "!", NULL},
   LARG_ONE_OR_ARG,
   {CC_DE, CC_US, CC_GB,	/* e.g.: "OTHER", */
    /*
     *** Translators, please translate this as a fixed 3-character text.
     *** This text should be a proper abbreviation of "ARGUMENT".
     */
    N_("ARG"), NULL}
   },
#if USE_RC
  {
   SYM_DATE_VARIABLE,
   "date-variable",
   {"v", NULL},
   LARG_ONE,
   {NULL}
   },
#endif
  {
   SYM_DEBUG,
   "debug",
   {"0", "1", "2", "3", "4", NULL},
   LARG_NO_OR_ONE,
   {"internal", "handled", "unhandled", "all", "abort", NULL}
   },
#if USE_RC
  {
   SYM_DESC_FIXED_DATES_LIST,
   "descending-fixed-dates",
   {"c-", "C-", NULL},
   LARG_NO_OR_ONE,
   {"short", "long", NULL}
   },
#endif
  {
   SYM_DESC_HOLIDAY_LIST,
   "descending-holiday-list",
   {"n-", "N-", NULL},
   LARG_NO_OR_ONE,
   {"long", "short", NULL}
   },
  {
   SYM_DISABLE_HIGHLIGHTING,
   "disable-highlighting",
   {"Hno", NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_END_OF_MONTH,
   "end-of-month",
   {"m+", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_END_OF_WEEK,
   "end-of-week",
   {"w+", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_END_OF_YEAR,
   "end-of-year",
   {"y+", NULL},
   LARG_NO,
   {NULL}
   },
#endif
  {
   SYM_ETHIOPIC_MTH,
   "ethiopic-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_EXCLUDE_RC_TITLE,
   "exclude-fixed-dates-list-title",
   {"x", NULL},
   LARG_NO,
   {NULL}
   },
#endif
  {
   SYM_EXCLUDE_HD_TITLE,
   "exclude-holiday-list-title",
   {"X", NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_EXECUTE_COMMAND,
   "execute-command",
   {NULL},
   LARG_NO,
   {NULL}
   },
#endif
  {
   SYM_EXIT_STAT_HELP_NON_ZERO,
   "exit-status-help-non-zero",
   {NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_extern_static_DVARS,
   "export-date-variables",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_extern_static_TVARS,
   "export-text-variables",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_FILTER_DAY,
   "filter-day",
   {"D", NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_FILTER_PERIOD,
   "filter-period",
   {"P", NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_FILTER_TEXT,
   "filter-text",
   {"I", NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_FIXED_DATES,
   "fixed-dates",
   {"jc", "jcb", NULL},
   LARG_ONE,
   {"special", "both", NULL}
   },
#endif
  {
   SYM_FORCE_HIGHLIGHTING,
   "force-highlighting",
   {"Hyes", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_FRENCH_REVOLUTIONARY_MTH,
   "french-revolutionary-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_GREG_REFORM,
   "gregorian-reform",
   {"$\001", "$\002", "$\003", "$\004", "$", NULL},
   LARG_ONE_OR_ARG,
   {"1582", "1700", "1752", "1753",
    /*
     *** Translators, please translate this as a fixed 3-character text.
     *** This text should be a proper abbreviation of "ARGUMENT".
     */
    N_("ARG"), NULL}
   },
#if USE_RC
  {
   SYM_GROUPING_TEXT,
   "grouping-text",
   {"g", NULL},
   LARG_NO_OR_ONE,
   {NULL}
   },
  {
   SYM_HEADING_TEXT,
   "heading-text",
   {NULL},
   LARG_ONE,
   {NULL}
   },
#endif
  {
   SYM_HEBREW_HDY,
   "hebrew-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_HEBREW_MTH,
   "hebrew-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_LONG_HELP1,
   "help",
   {"h", NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_HERE_FILE,
   "here",
   {"#", NULL},
   LARG_ONE,
   {NULL}
   },
#endif
  {
   SYM_HIGHLIGHTING,
   "highlighting",
   {"H", NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_HOLIDAY_DATES,
   "holiday-dates",
   {"jn", "jnb", NULL},
   LARG_ONE,
   {"special", "both", NULL}
   },
  {
   SYM_HOLIDAY_LIST,
   "holiday-list",
   {"n", "N", NULL},
   LARG_NO_OR_ONE,
   {"long", "short", NULL}
   },
#if USE_RC
  {
   SYM_IGNORE_CASE,
   "ignore-case",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_INCLUDE_CONS_NUMBER,
   "include-consecutive-number",
   {"z", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_INCLUDE_HOLIDAY,
   "include-holidays",
   {"e", "E", NULL},
   LARG_NO_OR_ONE,
   {"long", "short", NULL}
   },
  {
   SYM_INCLUDE_FILENAME,
   "include-resource-file-name",
   {"a", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_INCLUDE_TODAY,
   "include-today",
   {"d", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_INCLUDE_WEEK_NUMBER,
   "include-week-number",
   {"k", NULL},
   LARG_NO,
   {NULL}
   },
#endif
  {
   SYM_INDIAN_CIVIL_MTH,
   "indian-civil-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_ISLAMIC_HDY,
   "islamic-civil-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_ISLAMIC_MTH,
   "islamic-civil-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_ISO_WEEK_NUMBER,
   "iso-week-number",
   {"y", "n", NULL},
   LARG_ONE,
   {"yes", "no", NULL}
   },
  {
   SYM_JAPANESE_FLEXIBLE_HDY,
   "japanese-flexible-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_JAPANESE_FLEXIBLE_MTH,
   "japanese-flexible-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_JAPANESE_HDY,
   "japanese-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_JAPANESE_MTH,
   "japanese-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_LEAP_DAY,
   "leap-day",
   {"f", "m", NULL},
   LARG_ONE,
   {"february", "march", NULL}
   },
#endif
  {
   SYM_LICENSE1,
   "license",
   {"L", NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_LIMIT,
   "limit",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_LIST_MODE,
   "list-mode",
   {"l", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_FIXED_DATES_LIST,
   "list-of-fixed-dates",
   {"c", "C", NULL},
   LARG_NO_OR_ONE,
   {"short", "long", NULL}
   },
#endif
  {
   SYM_LONG_HELP1,
   "long-help",
   {"hh", NULL},
   LARG_NO_OR_ONE,
   {NULL}
   },
#ifdef GCAL_EMAIL
  {
   SYM_MAIL,
   "mail",
   {NULL},
   LARG_NO_OR_ONE,
   {NULL}
   },
#endif
#if USE_RC
  {
   SYM_MONTH,
   "month",
   {"m", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_MOONIMAGE_LINES,
   "moonimage-lines",
   {NULL},
   LARG_ONE,
   {NULL}
   },
#endif
  {
   SYM_MULTICULTURAL_NEW_YEAR_HDY,
   "multicultural-new-year-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_OLD_ARMENIC_MTH,
   "old-armenic-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_OLD_EGYPTIC_MTH,
   "old-egyptic-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_OMIT_DATE_PART,
   "omit-multiple-date-part",
   {"o", NULL},
   LARG_NO,
   {NULL}
   },
#endif
  {
   SYM_ORTHODOX_CALENDAR,
   "orthodox-calendar",
   {"O", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_ORTHODOX_NEW_HDY,
   "orthodox-new-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_ORTHODOX_OLD_HDY,
   "orthodox-old-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
#if USE_PAGER
  {
   SYM_PAGER,
   "pager",
   {"p", NULL},
   LARG_NO,
   {NULL}
   },
#endif
#if USE_RC
  {
   SYM_PERIOD,
   "period-of-fixed-dates",
   {"c", NULL},
   LARG_ONE,
   {NULL}
   },
#endif
  {
   SYM_PERSIAN_HDY,
   "persian-jalaali-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_PERSIAN_MTH,
   "persian-jalaali-months",
   {NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_PRECISE,
   "precise",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_RESOURCE_FILE,
   "resource-file",
   {"f", NULL},
   LARG_ONE,
   {NULL}
   },
#endif
  {
   SYM_RESPONSE_FILE,
   "response-file",
   {"R", NULL},
   LARG_ONE,
   {NULL}
   },
#if USE_RC
  {
   SYM_REVERT_MATCH,
   "revert-match",
   {NULL},
   LARG_NO,
   {NULL}
   },
#endif
#ifdef GCAL_SHELL
  {
   SYM_SCRIPT_FILE,
   "shell-script",
   {"S", NULL},
   LARG_ONE,
   {NULL}
   },
#endif
#if USE_RC
  {
   SYM_START_OF_MONTH,
   "start-of-month",
   {"m-", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_START_OF_WEEK,
   "start-of-week",
   {"w-", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_START_OF_YEAR,
   "start-of-year",
   {"y-", NULL},
   LARG_NO,
   {NULL}
   },
#endif
  {
   SYM_STARTING_DAY,
   "starting-day",
   {"s", NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_SUPPRESS_CALENDAR,
   "suppress-calendar",
   {"u", NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_SUPPRESS_DATE_PART,
   "suppress-date-part",
   {"U", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_SUPPRESS_FDLIST_SEP,
   "suppress-fixed-dates-list-separator",
   {"Q", NULL},
   LARG_NO,
   {NULL}
   },
#endif /* USE_RC */
  {
   SYM_SUPPRESS_HDLIST_SEP,
   "suppress-holiday-list-separator",
   {"G", NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_SUPPRESS_TEXT_PART,
   "suppress-text-part",
   {"J", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_TEXT_VARIABLE,
   "text-variable",
   {"r", NULL},
   LARG_ONE,
   {NULL}
   },
#endif
  {
   SYM_TIME_OFFSET,
   "time-offset",
   {NULL},
   LARG_ONE,
   {NULL}
   },
#if USE_RC
  {
   SYM_TODAY,
   "today",
   {"c", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_TOMORROW,
   "tomorrow",
   {"t", NULL},
   LARG_NO,
   {NULL}
   },
#endif
  {
   SYM_TRANSFORM_YEAR,
   "transform-year",
   {NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_TRANSLATE_STRING,
   "translate-string",
   {NULL},
   LARG_ONE,
   {NULL}
   },
  {
   SYM_TYPE_OF_CALENDAR,
   "type",
   {"i", "i-", NULL},
   LARG_ONE,
   {"special", "standard", NULL}
   },
  {
   SYM_LONG_HELP2,
   "usage",
   {"hh", NULL},
   LARG_NO_OR_ONE,
   {NULL}
   },
  {
   SYM_VERSION,
   "version",
   {"V", NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_WEEK,
   "week",
   {"w", NULL},
   LARG_NO,
   {NULL}
   },
#endif
  {
   SYM_CALENDAR_WITH_WEEK_NUMBER,
   "with-week-number",
   {"K", NULL},
   LARG_NO,
   {NULL}
   },
#if USE_RC
  {
   SYM_YEAR,
   "year",
   {"y", NULL},
   LARG_NO,
   {NULL}
   },
  {
   SYM_ZERO_DATES,
   "zero-dates-only",
   {"Z", NULL},
   LARG_NO,
   {NULL}
   },
#endif
  {
   SYM_ZODIACAL_MARKER_HDY,
   "zodiacal-marker-holidays",
   {NULL},
   LARG_NO,
   {NULL}
   },
  {SYM_NIL, NULL, {NULL}, LARG_NO, {NULL}}
};

/*!
   The supported date formats table is a vector of `Df_struct'
     terminated by an element containing a `df_info' which is zero!
   If you extend this table by some more date formats, please extend the
     according `lopt[]' table entry for the `--date-format' long-style option,
     too!  If you do so, remember that each new entry in the `lopt[]' table
     for SYM_DATE_FORMAT must have a new `short_name' text
     "!\NEXT-CONSECUTIVE-OCTAL-NUMBER-OF-THIS-NEW-INDEX" and a corresponding
     identifying text in `largs' (with a length of less than 6 characters).
     The simple "!" text in the `short_name' member and its corresponding
     LARG_TXT must always trail any new entry, which will be possibly added
     in future.
*/
Df_struct supported_date_format[LARG_MAX - 1] = {
/*
  { char *df_id, char *df_info, char *df_format },
*/
  {CC_DE, N_("Germany"), "%<2#K,  %1%>2*D%2 %<3#U %>04*Y"},
  {CC_US, N_("U.S.A."), "%<3#K,  %<3#U %1%>2&*D%2 %>04*Y"},
  {CC_GB, N_("Great Britain"), "%<3#K,  %1%>2&*D%2 %<3#U %>04*Y"},
/*
   The next table field can be provided with further data!
   If more "burned-in" data is needed, LARG_MAX must be increased accordingly,
   because it's necessary to respect the data of this fields in the functions,
   which manage the long-style arguments!
*/
  {NULL, NULL, NULL},
/*
   This next "empty" table field must be kept UNTOUCHED,
     because it marks the end of the table!
*/
  {NULL, NULL, NULL}
};

/* Points to the used date format. */
Df_struct *date_format = supported_date_format;

/*
   The Gregorian Reformation dates table is a vector of `Greg_struct'
     terminated by an element containing a `year' which is zero!
   If you extend this table by some more dates, please extend the according
     `lopt[]' table entry for the `--gregorian-reform' long-style option, too!
     If you do so, remember that each new entry in the `lopt[]' table for
     SYM_GREG_REFORM must have a new `short_name' text
     "$\NEXT-CONSECUTIVE-OCTAL-NUMBER-OF-THIS-NEW-INDEX" and a corresponding
     year of Gregorian Reformation text in `largs'.  The simple "$" text in
     the `short_name' member and its corresponding LARG_TXT must always
     trail any new entry, which will be possibly added in future.
*/
Greg_struct greg_reform_date[LARG_MAX - 1] = {
/*
  { int year, int month, int f_day, int l_day },
*/
  {1582, 10, 5, 14},
  {1700, 2, 19, 28},
  {1752, 9, 3, 13},
  {1753, 2, 18, 28},
/*
   This next "empty" table field must be kept UNTOUCHED,
     because it marks the end of the table!
*/
  {0, 0, 0, 0}
};

/*! Points to the used Gregorian Reformation date. */
Greg_struct *greg = greg_reform_date;

/*! User defined Gregorian Reformation date. */
Greg_struct users_greg;

#ifdef GCAL_EMAIL
/*! Temporary file which is send by the mailer. */
FILE *tfp = (FILE *) NULL;
#endif

/*! Used if a list/range of months/years is given. */
Ml_struct *month_list = (Ml_struct *) NULL;

/*! Effective hls 1 start (current day). */
Hls_struct ehls1s;

/*! Effective hls 1 end (current day). */
Hls_struct ehls1e;

/*! Effective hls 2 start (holiday). */
Hls_struct ehls2s;

/*! Effective hls 2 end (holiday). */
Hls_struct ehls2e;

#ifdef DJG
/*! Set to SHRT_MAX for checking the maximum table range. */
Usint testval = (Usint) 0;
#else
/*! Set to INT_MAX for checking the maximum table range. */
Uint testval = (Uint) 0;
#endif

/*! Actual size of all string vectors. */
Uint maxlen_max = MAXLEN_MAX;

/*! String length of the maximum year able to compute. */
int len_year_max = 0;

/*! Maximum string length of a textual day_name(). */
int len_dayname_max = 0;

/*! Maximum string length of a textual month_name(). */
int len_monthname_max = 0;

/*! Maximum string length of a textual day_suffix() [if any]. */
int len_suffix_max = 0;

/*! `--debug[=0...WARN_LVL_MAX]', SPECIAL VALUE at startup. */
int warning_level = SPECIAL_VALUE;

/*! `-s<0,1...7|day name>'. */
int start_day = 0;

/*! `--transform-year=BASE_YEAR'. */
int transform_year = 0;

/*! `--time-offset=t|@|[t|@][+|-]MMMM|HH:[MM]' for correcting astronomically based data. */
int time_hour_offset = 0;

/*! `--time-offset=t|@|[t|@][+|-]MMMM|HH:[MM]' for correcting astronomically based data. */
int time_min_offset = 0;

/*! Current day. */
int day = 0;

/*! Current month. */
int month = 0;

/*! Current year. */
int year = 0;

/*! Actual second. */
int act_sec = 0;

/*! Actual minute. */
int act_min = 0;

/*! Actual hour. */
int act_hour = 0;

/*! Actual day. */
int act_day = 0;

/*! Actual month. */
int act_month = 0;

/*! Actual year. */
int act_year = 0;

/*! Buffer of actual day. */
int buf_ad = 0;

/*! Buffer of actual month. */
int buf_am = 0;

/*! Buffer of actual year. */
int buf_ay = 0;

/*! True actual day as reported by the operating system. */
int true_day = 0;

/*! True actual month as reported by the operating system. */
int true_month = 0;

/*! True actual year as reported by the operating system. */
int true_year = 0;

/*! Starting month of a fiscal year. */
int fiscal_month = MONTH_MIN;

/*! Is output displayed on a terminal? */
int is_tty = 0;

/*! Is output directed to channel 1? */
int is_tty1 = 0;

/*! Is output directed to channel 2? */
int is_tty2 = 0;

#if USE_PAGER
/*! Number of tty rows, SPECIAL_VALUE at startup. */
int tty_rows = SPECIAL_VALUE;

/*! Number of tty columns, SPECIAL_VALUE at startup. */
int tty_cols = SPECIAL_VALUE;
#endif

/*! Number of month rows of a year calendar. */
int out_rows = 0;

/*! Number of month columns of a year calendar. */
int out_cols = 0;

/*! Format length of a standard/special/both day. */
int format_len = 0;

/*! Is current year a leap year? */
int is_leap_year = 0;

#ifdef GCAL_EMAIL
/*! Name of tempfile used by the mailer. */
char *tfn = (char *) NULL;

/*! Email address Gcal's output is send to. */
char *email_adr = (char *) NULL;
#endif

/*! `--cc-holidays=CC[+CC+...]'. */
char *cc = (char *) NULL;

/*! The "YY" text. */
char *yy_lit = (char *) NULL;

/*! The "YYYY" text. */
char *yyyy_lit = (char *) NULL;

/*! The "MM" text. */
char *mm_lit = (char *) NULL;

/*! The "WWW" text. */
char *www_lit = (char *) NULL;

/*! The "DD" text. */
char *dd_lit = (char *) NULL;

/*! The "ARG" text. */
char *larg_lit = (char *) NULL;

/*! General purpose text buffer 1. */
char *s1 = (char *) NULL;

/*! General purpose text buffer 2. */
char *s2 = (char *) NULL;

/*! General purpose text buffer 3. */
char *s3 = (char *) NULL;

/*! General purpose text buffer 4. */
char *s4 = (char *) NULL;

/*! Stores the actual program name. */
char *prgr_name = (char *) NULL;

/*! Character for separating HH:MM time values. */
char *time_sep = (char *) NULL;

/*! `--translate-string=CHARACTER_PAIR...'. */
char *translate_string = (char *) NULL;

/*! Pointer to the $TZ (timezone) environment variable. */
char *tz = (char *) NULL;

#ifdef GCAL_EPAGER
/*! Name of external pager program. */
char *ext_pager = (char *) NULL;
#endif

/*! Day suffix format specifier given in date format?. */
Bool use_day_suffix = FALSE;

/*! 3 char day name format specifier given in date format? */
Bool use_short3_day_name = FALSE;

/*! Day number leaded with zeroes format specifier given in date format? */
Bool use_day_zeroleaded = FALSE;

/*! Year number leaded with zeroes format specifier given in date format? */
Bool use_year_zeroleaded = FALSE;

/*! Don't use Astronomical holidays by default. */
Bool hdy_astronomical = FALSE;

/*! Don't use Bahai calendar holidays by default. */
Bool hdy_bahai = FALSE;

/*! Don't use Celtic calendar holidays by default. */
Bool hdy_celtic = FALSE;

/*! Don't use Chinese calendar holidays by default. */
Bool hdy_chinese = FALSE;

/*! Don't use Chinese flexible calendar holidays by default. */
Bool hdy_chinese_flexible = FALSE;

/*! Don't use Christian Western churches calendar holidays by default. */
Bool hdy_christian = FALSE;

/*! Don't use Hebrew calendar holidays by default. */
Bool hdy_hebrew = FALSE;

/*! Don't use Islamic CIVIL calendar holidays by default. */
Bool hdy_islamic = FALSE;

/*! Don't use Japanese calendar holidays by default. */
Bool hdy_japanese = FALSE;

/*! Don't use Japanese flexible calendar holidays by default. */
Bool hdy_japanese_flexible = FALSE;

/*! Don't use Multicultural New_Year's_Day holidays by default. */
Bool hdy_multicultural_new_year = FALSE;

/*! Don't use Orthodox Christian Eastern churches NEW calendar holidays by default. */
Bool hdy_orthodox_new = FALSE;

/*! Don't use Orthodox Christian Eastern churches OLD calendar holidays by default. */
Bool hdy_orthodox_old = FALSE;

/*! Don't use Persian Jalaali calendar holidays by default. */
Bool hdy_persian = FALSE;

/*! Don't use Zodiacal Marker holidays by default. */
Bool hdy_zodiacal_marker = FALSE;

/*! Don't use Bahai calendar months by default. */
Bool mth_bahai = FALSE;

/*! Don't use Chinese calendar months by default. */
Bool mth_chinese = FALSE;

/*! Don't use Chinese flexible calendar months by default. */
Bool mth_chinese_flexible = FALSE;

/*! Don't use Coptic calendar months by default. */
Bool mth_coptic = FALSE;

/*! Don't use Ethiopic calendar months by default. */
Bool mth_ethiopic = FALSE;

/*! Don't use French Revolutionary calendar months by default. */
Bool mth_french_revolutionary = FALSE;

/*! Don't use Hebrew calendar months by default. */
Bool mth_hebrew = FALSE;

/*! Don't use Indian CIVIL calendar months by default. */
Bool mth_indian_civil = FALSE;

/*! Don't use Islamic CIVIL calendar months by default. */
Bool mth_islamic = FALSE;

/*! Don't use Japanese calendar months by default. */
Bool mth_japanese = FALSE;

/*! Don't use Japanese flexible calendar months by default. */
Bool mth_japanese_flexible = FALSE;

/*! Don't use Old-Armenic calendar months by default. */
Bool mth_old_armenic = FALSE;

/*! Don't use Old-Egyptic calendar months by default. */
Bool mth_old_egyptic = FALSE;

/*! Don't use Persian Jalaali calendar months by default. */
Bool mth_persian = FALSE;

/*! `-O' (compute leap years as done by Eastern churches). */
Bool orthodox_calendar = FALSE;

/*! `-u'. */
Bool suppr_cal_flag = FALSE;

/*! `-H<yes>|<no>'. */
Bool highlight_flag = TRUE;

/*! `--iso-week-number=<yes>|<no>'. */
Bool iso_week_number = FALSE;

/*! `-K'. */
Bool cal_with_week_number = FALSE;

/*! `-j'. */
Bool cal_special_flag = FALSE;

/*! `-jb'. */
Bool cal_both_dates_flag = FALSE;

/*! `-n|N'. */
Bool holiday_flag = FALSE;

/*! `-N'. */
Bool hd_legal_days_only = FALSE;

/*! `-n|N-'. */
Bool hd_sort_des_flag = FALSE;

/*! `-jn'. */
Bool hd_special_flag = FALSE;

/*! `-jnb'. */
Bool hd_both_dates_flag = FALSE;

/*! `-G'. */
Bool hd_suppr_list_sep_flag = FALSE;

/*! `-X'. */
Bool hd_title_flag = TRUE;

/*! ':' char found in argument (MM:YYYY). */
Bool is_fiscal_year = FALSE;

/*! Argument is `.' or `.+' or `.-'. */
Bool is_3month_mode = FALSE;

/*! Argument is `..' -> current quarter of actual year. */
Bool is_3month_mode2 = FALSE;

/*! Is an extended list/range of years given? */
Bool is_ext_year = FALSE;

/*! Is an extended list of months/years given? */
Bool is_ext_list = FALSE;

/*! Is an extended range of months/years given? */
Bool is_ext_range = FALSE;

/*! Is a special range of a selected month of years given? */
Bool is_special_range = FALSE;

/*! Is a special range of selected months of years given? */
Bool is_multi_range = FALSE;

#ifdef GCAL_NLS
/*! Support of English language? */
Bool is_en = FALSE;
#endif

/*! `-i[-]'. */
Bool special_calsheet_flag = FALSE;

#if USE_HLS
/*! Must we emulate the highlighting sequences? */
Bool emu_hls = FALSE;
#else /* !USE_HLS */
/*! Must we emulate the highlighting sequences? */
Bool emu_hls = TRUE;
#endif /* !USE_HLS */

#if USE_PAGER
/*! `-p'. */
Bool pager_flag = FALSE;
#endif



/*
*  static variables definitions.
*/
#ifdef GCAL_EPAGER
/*! Child process id of external pager. */
static pid_t child_pid;

/*! Pipe file descriptors. */
static int pipe_fd[2];

/*! Buffer of system file descriptors 0 and 1. */
static int sys_fd[2];
#endif

/*! User defined date format. */
static Df_struct users_date_format;

/*! Maximum number of `month_list[]' table elems. */
static Uint month_list_max = MONTH_MAX + 1;

/*! The index value of a long option. */
static int lopt_id = 0;

/*! Termination status on `--help', `--version' etc... */
static int exit_stat_help = EXIT_STAT_HELP;

/*! Buffers default value of `-s<ARG>' option. */
static int buf_start_day = 0;

#ifdef GCAL_EPAGER
/*!
   Possible options passed to the $PAGER external pager program.
*/
static char **pg_argv = (char **) NULL;

/*!
   The external pager program names table is a vector of char pointer
     elements, which must be terminated by a NULL element!
*/
static char *pagers[] = { PAGER1_PROG, PAGER2_PROG, PAGER3_PROG, NULL };
#endif


#ifdef GCAL_SHELL
/*! File name of shell script to write `-S<NAME>'. */
static char *shl_filename = (char *) NULL;
#endif

/*! Name of response file to read (@FILE) or write (-R<NAME>). */
static char *rsp_filename = (char *) NULL;

/*! Text containing user defined highlighting sequences `-H<>'. */
static char *hl_seq = (char *) NULL;

/*! Points to "date format error location" description text. */
static char *errtxt_dformat = (char *) NULL;

/*! `-b<1|2|3|4|6|12>'. */
static Bool year_flag = FALSE;
