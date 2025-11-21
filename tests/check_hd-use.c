#include "../config.h"
#include <check.h>
#include <stdlib.h>

#include "../src/tailor.h"
#include <ctype.h>
#include "../src/common.h"

#include "../src/globals.h"
#include "../src/hd-astro.h"
#include "../src/hd-defs.h"
#include "../src/rc-defs.h"
#include "../src/hd-data.h"
#include "../src/tty.h"
#include "../src/utils.h"
#include "../src/hd-use.h"

START_TEST(test_eval_holiday)
{
    int eh;

    // e.g. https://www.kalender-365.eu/kalender-2011.html

    // first monday of year is 3.
    eh=eval_holiday(1, 1, 2011, 1, true);
    ck_assert_int_eq(eh, 3);
    // last monday of january in year is 3.
    eh=eval_holiday(31, 1, 2011, 1, false);
    ck_assert_int_eq(eh, 31);

    // first tuesday in february of year is 1.
    eh=eval_holiday(1, 2, 2011, 2, true);
    ck_assert_int_eq(eh, 1);
    // last tuesday in february of year is 22.
    eh=eval_holiday(28, 2, 2011, 2, false);
    ck_assert_int_eq(eh, 22);

    // first wednesday in march of year is 2.
    eh=eval_holiday(1, 3, 2011, 3, true);
    ck_assert_int_eq(eh, 2);
    // last wednesday in march of year is 3.
    eh=eval_holiday(31, 3, 2011, 3, false);
    ck_assert_int_eq(eh, 30);

    // first thursday in april of year is 7.
    eh=eval_holiday(1, 4, 2011, 4, true);
    ck_assert_int_eq(eh, 7);
    // last thursday in april of year is 28.
    eh=eval_holiday(31, 4, 2011, 4, false); // april has only 30 days, is this ok? I think so
    ck_assert_int_eq(eh, 28);

    // first friday in may of year is 6.
    eh=eval_holiday(1, 5, 2011, 5, true);
    ck_assert_int_eq(eh, 6);
    // last friday in may of year is 27.
    eh=eval_holiday(31, 5, 2011, 5, false);
    ck_assert_int_eq(eh, 27);

    // first saturday in june of year is 4.
    eh=eval_holiday(1, 6, 2011, 6, true);
    ck_assert_int_eq(eh, 4);
    // last saturday in june of year is 25.
    eh=eval_holiday(31, 6, 2011, 6, false);
    ck_assert_int_eq(eh, 25);

    // first sunday in july of year is 3.
    eh=eval_holiday(1, 7, 2011, 7, true);
    ck_assert_int_eq(eh, 3);
    // last sunday in july of year is 31.
    eh=eval_holiday(31, 7, 2011, 7, false);
    ck_assert_int_eq(eh, 31);


}
END_TEST

/*
int
orthodox_easter (const int year, int *greg_diff, const int greg_year, const int greg_month, const int greg_first_day,
                 const int greg_last_day)
*/
START_TEST(test_orthodox_easter)
{
    int oe, greg_diff=0, day, month;
    bool valid;

    oe=orthodox_easter(2024, &greg_diff, 1582, 10, 5, 15);
    printf("XXX oe: %i  diff %i\n",oe, greg_diff);
    ck_assert_int_eq(greg_diff, 14); //XXX should be 13 according to https://en.wikipedia.org/wiki/Gregorian_calendar
    valid=doy2date(oe, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 7); //XXX should be 5 according to https://www.christianity.com/wiki/holidays/orthodox-easter-origin-and-date.html
    ck_assert_int_eq(month, 5);

    oe=orthodox_easter(2025, &greg_diff, 1582, 10, 5, 15);
    printf("XXX oe: %i  diff %i\n",oe, greg_diff);
    ck_assert_int_eq(greg_diff, 14); //XXX should be 13 according to https://en.wikipedia.org/wiki/Gregorian_calendar
    valid=doy2date(oe, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 21); //XXX should be 20 according to https://www.christianity.com/wiki/holidays/orthodox-easter-origin-and-date.html
    ck_assert_int_eq(month, 4);

    oe=orthodox_easter(2026, &greg_diff, 1582, 10, 5, 15);
    printf("XXX oe: %i  diff %i\n",oe, greg_diff);
    ck_assert_int_eq(greg_diff, 14); //XXX should be 13 according to https://en.wikipedia.org/wiki/Gregorian_calendar
    valid=doy2date(oe, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 13); //XXX should be 12 according to https://www.christianity.com/wiki/holidays/orthodox-easter-origin-and-date.html
    ck_assert_int_eq(month, 4);

    oe=orthodox_easter(2027, &greg_diff, 1582, 10, 5, 15);
    printf("XXX oe: %i  diff %i\n",oe, greg_diff);
    ck_assert_int_eq(greg_diff, 14); //XXX should be 13 according to https://en.wikipedia.org/wiki/Gregorian_calendar
    valid=doy2date(oe, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 3); //XXX should be 2 according to https://www.christianity.com/wiki/holidays/orthodox-easter-origin-and-date.html
    ck_assert_int_eq(month, 5);

    oe=orthodox_easter(2028, &greg_diff, 1582, 10, 5, 15);
    printf("XXX oe: %i  diff %i\n",oe, greg_diff);
    ck_assert_int_eq(greg_diff, 14); //XXX should be 13 according to https://en.wikipedia.org/wiki/Gregorian_calendar
    valid=doy2date(oe, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 18); //XXX should be 16 according to https://www.christianity.com/wiki/holidays/orthodox-easter-origin-and-date.html
    ck_assert_int_eq(month, 4);

}
END_TEST

/*
int
tishri_1 (const int year)
/ *!
   Returns the `day_of_year' number of the (arithmetical lunisolar)
     Hebrew/Jewish Hebrew_New_Year/Rosh_Hashana/Tishri_1 for the
     given Julian/Gregorian year YEAR.
   Used formula:  John H. Conway, Guy and Berlekamp: "Winning Ways", Vol. 2.
   References:    Lot's of, but see `doc/calendar.faq' for the basics.
*/
START_TEST(test_tishri_1)
{
    int doy;
    bool valid;

    doy=tishri_1(2025);
    printf("XXX tishri_1 2025 doy: %i\n",doy);
    valid=doy2date(doy, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 23);
    ck_assert_int_eq(month, 9);

    //XXX pobably some more tests are needed here
}
END_TEST

START_TEST(test_muharram_1)
{
    int doy,doy2;
    bool valid;

    doy=muharram_1(2024, &doy2);
    printf("XXX muharram_1 2024 doy: %i   doy2: %i\n",doy,doy2);
    ck_assert_int_eq(doy2, 0);
    valid=doy2date(doy, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 9); //XXX according to https://www.calendardate.com/muharram_2025.htm this should be 9
    ck_assert_int_eq(month, 7);

    doy=muharram_1(2025, &doy2);
    printf("XXX muharram_1 2025 doy: %i   doy2: %i\n",doy,doy2);
    ck_assert_int_eq(doy2, 0);
    valid=doy2date(doy, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 27);
    ck_assert_int_eq(month, 6);

    doy=muharram_1(2026, &doy2);
    printf("XXX muharram_1 2026 doy: %i   doy2: %i\n",doy,doy2);
    ck_assert_int_eq(doy2, 0);
    valid=doy2date(doy, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 17);
    ck_assert_int_eq(month, 6);

    doy=muharram_1(2027, &doy2);
    printf("XXX muharram_1 2027 doy: %i   doy2: %i\n",doy,doy2);
    ck_assert_int_eq(doy2, 0);
    valid=doy2date(doy, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 6);
    ck_assert_int_eq(month, 6);

    doy=muharram_1(2028, &doy2);
    printf("XXX muharram_1 2028 doy: %i   doy2: %i\n",doy,doy2);
    ck_assert_int_eq(doy2, 0);
    valid=doy2date(doy, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 26); //XXX according to https://www.calendardate.com/muharram_2025.htm this should be 25
    ck_assert_int_eq(month, 5);

    doy=muharram_1(2029, &doy2);
    printf("XXX muharram_1 2029 doy: %i   doy2: %i\n",doy,doy2);
    ck_assert_int_eq(doy2, 0);
    valid=doy2date(doy, 0, &day, &month); ck_assert(valid);
    ck_assert_int_eq(day, 15); //XXX according to https://www.calendardate.com/muharram_2025.htm this should be 14
    ck_assert_int_eq(month, 5);

    //XXX find a year where doy2 is !=0
}
END_TEST

/*
int
find_chinese_leap_month (Ulint *conjunction_vector, Ulint *nh_ws_prev_year, const int year, const int hour, const int min)
/!
   Calculates the leap month of the Chinese calendar (based on the method
     used since AD 1645, which implemented the use of true -- astronomically
     detected -- Sun), which occurs in the given Julian/Gregorian year YEAR.
     * If the computation of the leap month fails by any reason,
       SPECIAL_VALUE is returned.
     * If there is no leap month in the YEAR,
       0 is returned.
     * If there is a leap month and it belongs to the YEAR,
       +1...+12 is returned.
     * If there is a leap month and it belongs to the previous YEAR,
       -11...-12 is returned.
   The date of the winter solstice (major solar term/Zhong-Qi 11) of the
     previous YEAR is returned via the address of NH_WS_PREV_YEAR.  All
     conjunction dates (starting on the date of NH_WS_PREV_YEAR or later)
     which are necessary to calculate the Chinese calendar for the YEAR,
     are returned via the address of CONJUNCTION_VECTOR.  The caller has to
     guarantee that the CONJUNCTION_VECTOR has 16 elements!
   Calculations are done for a line at a definite meridian expressed as
     a time value in HOUR and MIN.  If HOUR and MIN are set to zero,
     calculations are done for UTC/GMT.  If HOUR and MIN have a positive
     sign, calculations are done for meridians East of Greenwich, otherwise
     for meridians West of Greenwich.
   For a good and detailed reference of the Chinese calendar, see:
     "The Mathematics of the Chinese Calendar" by Helmer Aslaksen,
     <http://www.math.nus.edu.sg/aslaksen/>.
*/
START_TEST(test_find_chinese_leap_month)
{
    int leap_month;
    Ulint nh_ws_prev_year=0;
    Ulint conjunction_vector[MONTH_MAX + 4];
    Ulint *ptr_conjunction_vector = conjunction_vector;

    leap_month=find_chinese_leap_month_with_length(ptr_conjunction_vector, MONTH_MAX+4, &nh_ws_prev_year, 2025, 0, 0);
    ck_assert_int_eq(leap_month, 7); //XXX according to https://www.chinahighlights.com/travelguide/guidebook/chinese-calendar.htm this should be 6

    leap_month=find_chinese_leap_month_with_length(ptr_conjunction_vector, MONTH_MAX+4, &nh_ws_prev_year, 2028, 0, 0);
    ck_assert_int_eq(leap_month, 5);

    leap_month=find_chinese_leap_month_with_length(ptr_conjunction_vector, MONTH_MAX+4, &nh_ws_prev_year, 2031, 0, 0);
    ck_assert_int_eq(leap_month, 3);

    leap_month=find_chinese_leap_month_with_length(ptr_conjunction_vector, MONTH_MAX+4, &nh_ws_prev_year, 2033, 0, 0);
    ck_assert_int_eq(leap_month, 8); //XXX according to https://www.chinahighlights.com/travelguide/guidebook/chinese-calendar.htm this should be 11

    leap_month=find_chinese_leap_month_with_length(ptr_conjunction_vector, MONTH_MAX+4, &nh_ws_prev_year, 2036, 0, 0);
    ck_assert_int_eq(leap_month, 6);

    //XXX maybe add some checks from https://www.chinesefortunecalendar.com/clc/LeapMonth.htm
    //XXX there are different leap month in different time zones!?

    leap_month=find_chinese_leap_month_with_length(ptr_conjunction_vector, MONTH_MAX+4, &nh_ws_prev_year, 2026, 0, 0);
    ck_assert_int_eq(leap_month, 0);
    leap_month=find_chinese_leap_month_with_length(ptr_conjunction_vector, MONTH_MAX+4, &nh_ws_prev_year, 2027, 0, 0);
    ck_assert_int_eq(leap_month, 0);
    leap_month=find_chinese_leap_month_with_length(ptr_conjunction_vector, MONTH_MAX+4, &nh_ws_prev_year, 2029, 0, 0);
    ck_assert_int_eq(leap_month, 0);
    leap_month=find_chinese_leap_month_with_length(ptr_conjunction_vector, MONTH_MAX+4, &nh_ws_prev_year, 2030, 0, 0);
    ck_assert_int_eq(leap_month, 0);

    //XXX maybe add more tests for special values
}
END_TEST

/*
int
decode_date_format (char *format_txt, char **result_txt, int day, int month, const int year, const int doy,
                    const Bool hls1_set, const Bool hls2_set, const Bool fixed_length_names)
/!
   Concatenates the elements of a date (inclusive highlighting) in formatted
     manner to `&result_txt' according to the order of format specifiers, which
     are given in the `format_txt.  The core area of the string vector
     `&result_txt' must be allocated and "filled" properly by the caller.
     "Filled" either means `&result_txt' contains a ZERO terminated text at
     function startup or a previous "*result_txt = '\0';" statement was
     performed by the caller before entering this function.
     If `day' is not zero but `doy' is zero:
       Use day of month and all other GROUPS.
     If `day' is zero but `doy' is not zero:
       Use day of year, insert a "day" text, use all other GROUPS except the month GROUP.
     If `day' is not zero and `doy' is not zero:
       Use both day of month and day of year and all other GROUPS.
     If `day' is zero and `doy' is zero:
       This results to an unmanaged internal error, because this
       case is unchecked due to faster internal processing speed.
     If `hls1_set' is TRUE and `hls2_set' is FALSE:
       Use `ehls1' highlighting sequences/marking characters.
     If `hls1_set' is FALSE and `hls2_set' is TRUE:
       Use `ehls2' highlighting sequences/marking characters.
     If `hls1_set' is FALSE and `hls2_set' is FALSE:
       Use no highlighting sequences/marking characters.
     If `hls1_set' is TRUE and `hls2_set' is TRUE:
       This case is unchecked due to faster internal processing speed
       but doesn't result to an unmanaged internal error, because
       the `ehls1' sequence is used by default.
     If `fixed_length_names' is set to TRUE, the texts returned by the
       `day_name()' and `month_name()' functions are set to a fixed length
       of `len_???name_max' characters (means trailing spaces), otherwise
       these texts are used as is.
     The `format_txt' must have exactly ONE day and year format specifier,
       exactly ONE format specifier from the month GROUP, BOTH format
       specifiers from the highlighting GROUP (%1 must be given before %2),
       and may have ONE weekday name format specifier.
     All format specifiers -- except the ones from the highlighting group --
       may be lead by an optional format instruction, which template is
       `[ ALIGNMENT [SIGN] [LZERO] WIDTH [STYLE] [SUFFIX] FORMAT ]', (see the
       `decode_format()' function for a more brief description of the
       format instruction), which will be evaluated and respected in case
       it is stated correctly:
     Day:
       %[FORMAT]D
     Year:
       %[FORMAT]Y
     Weekday name:
       %[FORMAT]K
     Month GROUP:
       %[FORMAT]M
       %[FORMAT]U
     Highlighting GROUP:
       %1 - Starting highlighting sequence
       %2 - Ending highlighting sequence
     Other (no group):
       _  - Blank (' ') character
       \_ - Underscore ('_') character
       \% - Percent ('%') character
       \\ - Backslash ('\') character
   The function return value is the text length of the "real" highlighting
   sequence pair if "real" highlighting must be performed, otherwise zero.
*/
START_TEST(test_decode_date_format)
{
     char *format_txt;
     int result;
     char **result_txt;
     int i, number_of_lines=8;

     result_txt = malloc(sizeof(char*)*number_of_lines);
     for(i=0;i<number_of_lines; i++) {
        result_txt[i] = malloc(sizeof(char)*64);  
        result_txt[i][0] = '\0';
     }

     format_txt="%D";
     result=decode_date_format(format_txt, result_txt, 31, 12, 2025, 365, false, false, false);
     ck_assert_int_eq(result, 0);
     ck_assert_str_eq(result_txt[0], "31(365)");

     //XXX this is just a template how things might work
     //    lots of things for different formats need to be added
     //    probably coverage helps
}
END_TEST

/*
int
decode_format (char *format_txt, int pos, Bool *is_cformat, Bool *is_lformat, Bool *is_sign,
               Bool *is_lzero, Bool *is_suffix, Bool *is_fformat, int *fstyle, int *fwidth)
/!
   Checks for an optional format instruction which can either be used
     in case a TVAR or a `%...' special text is referenced.  The template
     of such a format is:  [ ALIGNMENT [SIGN] [LZERO] WIDTH [STYLE] [SUFFIX] FORMAT ],
     e.g., $[<|:|>[+][0]N[u|U|l|L|w|W][&]*|#]TVAR, resp., %[<|:|>[+][0]N[u|U|l|L|w|W][&]*|#]?,
     like `$:+010u&#a' or `%>20l&*Y'.
     ALIGNMENT: '<' == adjusts field contents at the left margin using width WIDTH.
                ':' == adjusts field contents in centered manner using width WIDTH.
                '>' == ajdusts field contents at the right margin using width WIDTH.
     SIGN     : '+' == leads a numerical value always by its sign.
     LZERO    : '0' == fills a numerical value up to WIDTH leading zeroes
                       inclusivly a possibly leading explicit SIGN or
                       an implicitly leading negative sign.
     WIDTH    : FWIDTH_MIN...FWIDTH_MAX == is the width of the field.
     STYLE    : 'u' == converts field contents to upper-case letters.
                'l' == converts field contents to lower-case letters.
                'w' == converts field contents to capitalized words.
     SUFFIX   : '&' == provides a numerical value with an ordinal number suffix.
     FORMAT   : '*' == does not cut the field contents after
                       position WIDTH if it is longer than WIDTH.
                '#' == cuts the field contents after
                       position WIDTH if it is longer than WIDTH.
   On success, this function returns the position `pos' at which the format
     instruction ends in the `format_txt' and the width of the field in `&fwidth'.
     `&is_cformat', `&is_lformat', `&is_sign', `&is_lzero', `&is_suffix' and
     `&is_fformat' are set to TRUE if the according directive characters are
     found in proper order in `format_txt', otherwise they are set to FALSE;
     and `&fstyle' is set to the according style value, otherwise to FSTYLE_NONE.
   `&fwidth' is set to SPECIAL_VALUE and the unchanged position `pos' is
     returned in case an error occurs during the scan of the format instruction,
     which either means that it was not defined, or it contained a wrong
     or misplaced or misspelled element.
*/
START_TEST(test_decode_format)
{
     char *format_txt;
     int result, fstyle, fwidth;
     Bool is_cformat, is_lformat, is_sign, is_lzero, is_suffix, is_fformat;

     format_txt="%>20l&*Y";
     /* pos = 0 and 7 should give an error */
     result=decode_format(format_txt, 0, &is_cformat, &is_lformat, &is_sign, &is_lzero, &is_suffix, &is_fformat, &fstyle, &fwidth);
     ck_assert_int_eq(fstyle, FSTYLE_NONE);
     ck_assert_int_eq(fwidth, SPECIAL_VALUE);
     ck_assert_int_eq(result, 0);

     result=decode_format(format_txt, 7, &is_cformat, &is_lformat, &is_sign, &is_lzero, &is_suffix, &is_fformat, &fstyle, &fwidth);
     ck_assert_int_eq(fstyle, FSTYLE_NONE);
     ck_assert_int_eq(fwidth, SPECIAL_VALUE);
     ck_assert_int_eq(result, 7);

     result=decode_format(format_txt, 1, &is_cformat, &is_lformat, &is_sign, &is_lzero, &is_suffix, &is_fformat, &fstyle, &fwidth);
     ck_assert_int_eq(result, 7);
     ck_assert(!is_cformat); ck_assert(!is_lformat); ck_assert(!is_sign); ck_assert(!is_lzero); ck_assert(is_suffix); ck_assert(!is_fformat);
     ck_assert_int_eq(fstyle, FSTYLE_LOWER);
     ck_assert_int_eq(fwidth, 20);
     ck_assert_int_eq(result, 7);
     //XXX create more tests to get full coverage
}
END_TEST

/*
void
print_all_holidays (Bool init_data, const Bool detected)
/!
   Generate and display all holidays (global `hd_table') in sorted manner.
*/
START_TEST(test_print_all_holidays)
{
  //XXX print_all_holidays() prints to stdout
  //    maybe introduce a new FD parameter to make testing easier?
}
END_TEST

int length_of_hd_table()
{
    int i = 0;
    while ((hd_table[i] != (char *) NULL) && (i < HD_ELEMS_MAX)) i++;
    return i;
}

int length_of_cc_holidays_table()
{
    int i = 0;
    while (cc_holidays[i].cc_id != (char *) NULL) i++;
    return i;
}

/*
void
holiday (Bool init_data, const Bool detected, const char *holiday_name, const char *country_code, const char *holiday_prefix,
         int day, int month, const int year, int *hd_elems, const int fday, const int count)
/!
   Generates a single holiday date text in formatted manner and stores the
     result into global `hd_table[]'.
     ONLY if `holiday_prefix' is a '-' (DIS_HLS_PREF) or '*' (DIS_HLS_PREF2)
     character, this holiday is not stored into global `hd_ldays' and
     will not be highlighted in the generated list, but is stored into
     global `hd_mdays'!
     If `holiday_prefix' is a '#' character, this marks the case the
     holiday is only valid in some parts of the country, but is stored
     into global `hd_ldays' and will be highlighted in the generated list.
     If `holiday_prefix' is a '\0' or any other character, the same rules
     concerning to '#' character applies.
     If `month' is set to zero, it's assumed that the delivered date is a
     date relative to the Easter Sunday's date (`day' contains the according
     day_of_year number), otherwise the date is an absolute date of the `year'.
*/
START_TEST(test_holiday)
{
    //XXX test handling of hd_table[] and cc_holidays[] here

    int tableLength, hd_elems=0;
    int cc_holidays_length = length_of_cc_holidays_table();
    ck_assert_int_ne(cc_holidays_length, 0); // cc_holidays_length should be around 354

    tableLength=length_of_hd_table(); ck_assert_int_eq(tableLength, 0);

    holiday(true, true, "Blubber", "DE", "pre", 23, 10, 2025, &hd_elems, 0, 0);
    printf("XXX hd_elems %i %i\n",hd_elems, HD_ELEMS_MAX); 
    printf("XXX 0 %s\n", hd_table[0]);
    printf("XXX 1 %s\n", hd_table[1]);
    tableLength=length_of_hd_table(); ck_assert_int_eq(tableLength, 0);

    holiday(false, true, "Blubber2", "DE", "pre", 10, 10, 2025, &hd_elems, 0, 0);
    printf("XXX hd_elems %i %i\n",hd_elems, HD_ELEMS_MAX); 
    printf("XXX 0 %s\n", hd_table[0]);
    printf("XXX 1 %s\n", hd_table[1]);
    tableLength=length_of_hd_table(); ck_assert_int_eq(tableLength, 0);

    //XXX ck_assert_int_le(hd_elems, HD_ELEMS_MAX);
}
END_TEST

Suite *gcal_suite_hd_use(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_eval_holiday);
    tcase_add_test(tc_core, test_orthodox_easter);
    tcase_add_test(tc_core, test_tishri_1);
    tcase_add_test(tc_core, test_muharram_1);
    tcase_add_test(tc_core, test_find_chinese_leap_month);
    tcase_add_test(tc_core, test_decode_date_format);
    tcase_add_test(tc_core, test_decode_format);
    tcase_add_test(tc_core, test_print_all_holidays);
    tcase_add_test(tc_core, test_holiday);

    suite_add_tcase(s, tc_core);

    return s;
}

