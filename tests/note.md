
## riscv-tests
https://github.com/riscv-software-src/riscv-tests

```
cd am-kernels/tests/riscv-tests/
make -s -f testset.mk ARCH=riscv32e-nemu run ALL=add

# Run all tests
make -s -f testset.mk ARCH=riscv32e-nemu run
make -s -f testset.mk ARCH=riscv32e-npc run
```
