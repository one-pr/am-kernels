#ifndef __TRAP_H__
#define __TRAP_H__

#include <am.h>
#include <klib.h>
#include <klib-macros.h>

__attribute__((noinline))
void check(bool cond) {
  if (!cond) halt(1);
}

__attribute__((noinline))
void check_ctx(bool cond, int ctx) {
  if (!cond) halt(ctx);
}

#endif
