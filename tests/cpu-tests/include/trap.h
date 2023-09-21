#ifndef __TRAP_H__
#define __TRAP_H__

#include <am.h>
#include <klib.h>
#include <klib-macros.h>

// 标记函数为非内联
#define __FUNC_NO_INLINE    __attribute__((noinline))


__FUNC_NO_INLINE
void check(bool cond) {
  if (!cond) halt(1);
}

__FUNC_NO_INLINE
void check_ctx(bool cond, int ctx) {
  if (!cond) halt(ctx);
}

#endif // !__TRAP_H__
