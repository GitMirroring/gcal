#include <check.h>
#include <stdlib.h>

START_TEST(test_gcal_base_start)
{
    uint8_t bytes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 170};
    ck_assert_int_eq(bytes[0], 1);
    ck_assert_int_eq(bytes[1], 1);
}
END_TEST


START_TEST(test_gcal_base_end)
{
    ck_assert_int_eq(253, 254);
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

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = gcal_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
