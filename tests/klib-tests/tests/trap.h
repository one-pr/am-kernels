#ifndef __TRAP_H__
#define __TRAP_H__

#include <am.h>
#include <klib.h>
#include <klib-macros.h>

__attribute__((noinline))
void check(bool cond) {
  if (!cond) halt(1);
}

#define TEST_WARP(__ref_val, __eval_expr) \
  assert_equals_with_ctx((__ref_val), \
    (__eval_expr), \
    printf("\tFUNC : %s\n" \
           "\twant = '%d'\n" \
           "\tgot  = '%d'\n", \
            #__eval_expr, \
            (__ref_val), \
            (__eval_expr)))
// TEST_WARP

#endif
