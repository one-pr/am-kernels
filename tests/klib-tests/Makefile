.PHONY: all run gdb clean latest $(ALL)

RESULT = .result
$(shell > $(RESULT))

COLOR_RED   = \033[1;31m
COLOR_GREEN = \033[1;32m
COLOR_NONE  = \033[0m

# NOTE: 默认 RV32
ARCH ?= riscv32-nemu
MAKE_TARGET := run
KLIB_NATIVE ?=
ALL = $(basename $(notdir $(shell find tests/. -name "*.c")))

all: $(addprefix Makefile., $(ALL))
	@echo "" $(ALL)

$(ALL): %: Makefile.%

Makefile.%: tests/%.c latest
	@/bin/echo -e "NAME = $*\nSRCS = $<\ninclude $${AM_HOME}/Makefile" > $@
	@if make -s -f $@ ARCH=$(ARCH) GCOV=$(GCOV) KLIB_NATIVE=$(KLIB_NATIVE) $(MAKE_TARGET); then \
		printf "[%14s] $(COLOR_GREEN)PASS!$(COLOR_NONE)\n" $* >> $(RESULT); \
	else \
		printf "[%14s] $(COLOR_RED)FAIL!$(COLOR_NONE)\n" $* >> $(RESULT); \
	fi
	-@rm -f Makefile.$*

run: MAKE_TARGET:=run
run: all
	@cat $(RESULT)
	@rm $(RESULT)

gdb: MAKE_TARGET:=gdb
gdb: all


rrv: ARCH:=riscv32-nemu
rrv: run

rnative: ARCH:=native
rnative: clean-klib run

rknative: ARCH:=native
rknative: KLIB_NATIVE:=1
rknative: clean-klib run
	@printf "Test with native+$(COLOR_GREEN)klib$(COLOR_NONE)\n"

clean-klib:
	make -C ${AM_HOME}/klib clean
clean: clean-klib
	rm -rf Makefile.* build/

latest:
