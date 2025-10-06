#include "../config.h"
#include <check.h>
#include <stdlib.h>

#include "../src/tailor.h"
#include "../src/common.h"
#include "../src/globals.h"
#include "../src/utils.h"

#include "../src/rc-defs.h"
#include "../src/rc-utils.h"

START_TEST(test_valid_day)
{
    Bool rc;

    rc=rc_valid_day("", 1, 1, 2025); ck_assert(rc); 	// no exclusion
    rc=rc_valid_day("",30, 2, 2025); ck_assert(rc);     // no exclusion
    rc=rc_valid_day("V", 1, 1, 2025); ck_assert(rc); 
    rc=rc_valid_day("v", 1, 1, 2025); ck_assert(!rc); 
    rc=rc_valid_day("C",24, 9, 2025); ck_assert(rc); 

}
END_TEST

START_TEST(test_clean_flag)
{
    rc_tomorrow_flag = rc_week_flag = rc_month_flag = rc_year_flag = rc_week_year_flag = rc_forwards_flag = rc_backwards_flag = rc_period_flag = TRUE;

    ck_assert(rc_tomorrow_flag);
    ck_assert(rc_week_flag);
    ck_assert(rc_month_flag);
    ck_assert(rc_year_flag);
    ck_assert(rc_week_year_flag);
    ck_assert(rc_forwards_flag);
    ck_assert(rc_backwards_flag);
    ck_assert(rc_period_flag);

    rc_clean_flags();

    ck_assert(!rc_tomorrow_flag);
    ck_assert(!rc_week_flag);
    ck_assert(!rc_month_flag);
    ck_assert(!rc_year_flag);
    ck_assert(!rc_week_year_flag);
    ck_assert(!rc_forwards_flag);
    ck_assert(!rc_backwards_flag);
    ck_assert(!rc_period_flag);
}
END_TEST

START_TEST(test_get_date)
{
    //XXX TODO has to be done
    bool flag=true;
    ck_assert(flag);

}
END_TEST

START_TEST(test_precomp_date)
{
    //XXX TODO has to be done
    bool flag=true;
    ck_assert(flag);

}
END_TEST

START_TEST(test_set_dvar)
{
    //XXX TODO has to be done
    bool flag=true;
    ck_assert(flag);

}
END_TEST

START_TEST(test_set_tvar)
{
    //XXX TODO has to be done
    bool flag=true;
    ck_assert(flag);

}
END_TEST

START_TEST(test_nth_weekday_of_month)
{
    //XXX TODO has to be done
    bool flag=true;
    ck_assert(flag);

}
END_TEST

START_TEST(test_d_between)
{
    //XXX TODO has to be done
    bool flag=true;
    ck_assert(flag);

}
END_TEST

START_TEST(test_w_between)
{
    //XXX TODO has to be done
    bool flag=true;
    ck_assert(flag);

}
END_TEST

START_TEST(test_m_between)
{
    //XXX TODO has to be done
    bool flag=true;
    ck_assert(flag);

}
END_TEST

START_TEST(test_biorythm)
{
    //XXX TODO has to be done
    bool flag=true;
    ck_assert(flag);

}
END_TEST

/*
 typedef struct coor_type
 {
  int lon_deg;
  int lon_min;
  int lon_sec;
  int lat_deg;
  int lat_min;
  int lat_sec;
  int the_mode;
  int meters_above_sea_level;
  int time_zone_in_mins;
 }
 Coor_struct;
*/
START_TEST(test_compute_distance)
{
    //XXX use 0 1 2 for the_mode
    Coor_struct p1, p2;
    double distance, compare;

    p1.lon_deg=12; p1.lon_min=34; p1.lon_sec=45;
    p1.lat_deg=34; p1.lat_min=56; p1.lat_sec=00;
    p1.the_mode=0;
    p1.meters_above_sea_level=0;
    p1.time_zone_in_mins=0;

    p2.lon_deg=00; p2.lon_min=56; p2.lon_sec=34;
    p2.lat_deg=45; p2.lat_min=34; p2.lat_sec=12;
    p2.the_mode=0;
    p2.meters_above_sea_level=0;
    p2.time_zone_in_mins=0;

    compare=1537.872518;
    distance=compute_distance(&p1, &p2);
    printf("XXX distance: %lf <-> %lf\n",distance,compare);
    ck_assert_double_eq_tol(distance, compare, 1e-5);
}
END_TEST

Suite *gcal_suite_rc_utils(char *testname)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create(testname);

    /* Core test case */
    tc_core = tcase_create(testname);

    tcase_add_test(tc_core, test_valid_day);
    tcase_add_test(tc_core, test_clean_flag);
    tcase_add_test(tc_core, test_get_date);
    tcase_add_test(tc_core, test_precomp_date);
    tcase_add_test(tc_core, test_set_dvar);
    tcase_add_test(tc_core, test_set_tvar);
    tcase_add_test(tc_core, test_nth_weekday_of_month);
    tcase_add_test(tc_core, test_d_between);
    tcase_add_test(tc_core, test_w_between);
    tcase_add_test(tc_core, test_m_between);
    tcase_add_test(tc_core, test_biorythm);
    tcase_add_test(tc_core, test_compute_distance);

    suite_add_tcase(s, tc_core);

    return s;
}

