## Another functions
Lets create more functions
### sum function
#### prototype
```c
int     sum(int, int);
```
#### LLVM-C code
Check the [file](/example_2/example_2.c)
```c

LLVMValueRef tmp = LLVMBuildAdd(builder, LLVMGetParam(sum_function, 0), LLVMGetParam(sum_function, 1), "tmp");
LLVMBuildRet(builder, tmp);

```
- The LLVM IR
```LLVM
; ModuleID = 'example_2.bc'
source_filename = "arithmetics"

define i32 @sum(i32 %0, i32 %1) {
entry:
  %tmp = add i32 %0, %1
  ret i32 %tmp
}

```
- Compiling :
```bash
$  python ../llvm_tool.py -filename example_2.c 
$  ./example_2.exec
$  clang main.c example_1.bc
$  llvm-dis-14 example_1.bc
$  ./a.out
>sum is 84
```

### minus function
