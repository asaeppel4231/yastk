#include <stdarg.h>
#include <stddef.h>

#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>
#include "../yastk.h"

// Test basic allocation
static void test_new_and_free(void **state) {
    (void)state;
    
    yastk_t* st = new_yastk(0);
    assert_non_null(st);
    
    // Should start empty
    assert_int_equal(get_size_yastk(st), 0);
    
    free_yastk(st);
}

// Test NULL safety
static void test_null_safety(void **state) {
    (void)state;
    
    // Should handle NULL gracefully
    free_yastk(NULL);  // Should not crash
    
    assert_int_equal(get_size_yastk(NULL), 0);
    assert_null(pop_yastk(NULL, 0));
    assert_int_equal(push_yastk(NULL, NULL, 0), -1);
}

// Test single push and pop
static void test_push_pop_single(void **state) {
    (void)state;

    yastk_t* st = new_yastk(0);
    assert_non_null(st);

    int x = 123;
    int ret = push_yastk(st, &x, 0);
    assert_int_equal(ret, 0);
    
    // Size should be 1
    assert_int_equal(get_size_yastk(st), 1);

    void* out = pop_yastk(st, 0);
    assert_ptr_equal(out, &x);
    
    // Size should be 0 again
    assert_int_equal(get_size_yastk(st), 0);

    free_yastk(st);
}

// Test multiple pushes and pops
static void test_push_pop_multiple(void **state) {
    (void)state;

    yastk_t* st = new_yastk(0);
    assert_non_null(st);
    
    int values[5] = {10, 20, 30, 40, 50};
    
    // Push 5 values
    for (int i = 0; i < 5; i++) {
        int ret = push_yastk(st, &values[i], 0);
        assert_int_equal(ret, 0);
    }
    
    // Size should be 5
    assert_int_equal(get_size_yastk(st), 5);
    
    // Pop in reverse order (LIFO)
    for (int i = 4; i >= 0; i--) {
        void* out = pop_yastk(st, 0);
        assert_ptr_equal(out, &values[i]);
        assert_int_equal(get_size_yastk(st), i);
    }
    
    // Stack should be empty
    assert_int_equal(get_size_yastk(st), 0);
    assert_null(pop_yastk(st, 0));

    free_yastk(st);
}

// Test LIFO semantics (Last In, First Out)
static void test_lifo_semantics(void **state) {
    (void)state;

    yastk_t* st = new_yastk(0);
    assert_non_null(st);
    
    int a = 1, b = 2, c = 3;
    
    push_yastk(st, &a, 0);
    push_yastk(st, &b, 0);
    push_yastk(st, &c, 0);
    
    // Last in should be first out
    int* first = (int*)pop_yastk(st, 0);
    assert_ptr_equal(first, &c);
    
    int* second = (int*)pop_yastk(st, 0);
    assert_ptr_equal(second, &b);
    
    int* third = (int*)pop_yastk(st, 0);
    assert_ptr_equal(third, &a);

    free_yastk(st);
}

// Test push with NULL data
static void test_push_null_data(void **state) {
    (void)state;

    yastk_t* st = new_yastk(0);
    assert_non_null(st);
    
    // Should allow pushing NULL
    int ret = push_yastk(st, NULL, 0);
    assert_int_equal(ret, 0);
    assert_int_equal(get_size_yastk(st), 1);
    
    void* out = pop_yastk(st, 0);
    assert_null(out);
    assert_int_equal(get_size_yastk(st), 0);

    free_yastk(st);
}

// Test size tracking
static void test_size_tracking(void **state) {
    (void)state;

    yastk_t* st = new_yastk(0);
    assert_non_null(st);
    
    int value = 42;
    
    for (int i = 0; i < 10; i++) {
        push_yastk(st, &value, 0);
        assert_int_equal(get_size_yastk(st), i + 1);
    }
    
    for (int i = 10; i > 0; i--) {
        pop_yastk(st, 0);
        assert_int_equal(get_size_yastk(st), i - 1);
    }

    free_yastk(st);
}

// Test info function
static void test_info(void **state) {
    (void)state;
    
    char* info = info_yastk();
    assert_non_null(info);
    
    // Should contain version info
    assert_true(strstr(info, "yastk") != NULL);
    assert_true(strstr(info, "version") != NULL);
    
    free(info);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_and_free),
        cmocka_unit_test(test_null_safety),
        cmocka_unit_test(test_push_pop_single),
        cmocka_unit_test(test_push_pop_multiple),
        cmocka_unit_test(test_lifo_semantics),
        cmocka_unit_test(test_push_null_data),
        cmocka_unit_test(test_size_tracking),
        cmocka_unit_test(test_info),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
