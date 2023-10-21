#include <am.h>
#include <klib.h>
#include <klib-macros.h>

// 4K*8=32KB 的堆栈
#define STACK_SIZE (4096 * 8)

// 进程控制块 (PCB, process control block)
typedef union {
  uint8_t stack[STACK_SIZE];
  struct { Context *cp; };
} PCB;

static PCB pcb[2], pcb_boot, *current = &pcb_boot;


// 测试函数
static void f(void *arg) {
  while (1) {
    putch("?AB"[(uintptr_t)arg > 2 ? 0 : (uintptr_t)arg]);
    for (int volatile i = 0; i < 100000; i++) ;

    yield();
  }
}

/* 在进行上下文切换的时候, 只需要把PCB中的cp指针返回给CTE的__am_irq_handle()函数即可 */
static Context *schedule(Event ev, Context *prev) {
  assert(prev != NULL);
  assert(pcb[0].cp != NULL);
  assert_with_ctx(pcb[1].cp != NULL,
    printf("current->cp is NULL: \n"
           "  ev.event = %d\n"
           "  ev.msg   = %s\n"
           "  current  = &pcb[%d]\n",
            ev.event, ev.msg,
            (current == &pcb[0] ? 0 : 1)));

  current->cp = prev;
  current = (current == &pcb[0] ? &pcb[1] : &pcb[0]);
  assert(current != NULL);

  assert(current->cp != NULL);
  return current->cp;
}

/* 创建了两个执行流, 在CTE的支撑下交替输出A和B */
int main() {
  cte_init(schedule);

  // 为每一个进程维护一个PCB
  pcb[0].cp = kcontext((Area) { pcb[0].stack, &pcb[0] + 1 }, f, (void *)1L);
  assert(pcb[0].cp != NULL);
  pcb[1].cp = kcontext((Area) { pcb[1].stack, &pcb[1] + 1 }, f, (void *)2L);
  assert(pcb[1].cp != NULL);
  yield();

  panic("Should not reach here!");
}
