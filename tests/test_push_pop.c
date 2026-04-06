#include <stdarg.h>
#include <stddef.h>

#include <setjmp.h>
#include <cmocka.h>
#include "../yastk.h"

static void test_push_pop(void **state) {
    (void)state;

    yastk_t* st = new_yastk(0);
    assert_non_null(st);

    int x = 123;
    push_yastk(st, &x, 0);

    int* out = pop_yastk(st, 0);
    assert_ptr_equal(out, &x);

    free_yastk(st);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_push_pop),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
