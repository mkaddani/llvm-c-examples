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
```c
// --------------------------------------------- MINUS FUNCTION ------------------------------------------------------------------
    LLVMValueRef minus_function = LLVMAddFunction(mod, "minus", func_type);
    LLVMBasicBlockRef entry_minus = LLVMAppendBasicBlock(minus_function, "entry_minus");
    LLVMPositionBuilderAtEnd(builder, entry_minus);
    tmp = LLVMBuildSub(builder, LLVMGetParam(minus_function, 0), LLVMGetParam(minus_function, 1), "tmp");
    LLVMBuildRet(builder, tmp);
```
```llvm
; ModuleID = 'example_2.bc'
source_filename = "arithmetics"

define i32 @sum(i32 %0, i32 %1) {
entry:
  %tmp = add i32 %0, %1
  ret i32 %tmp
}

define i32 @minus(i32 %0, i32 %1) {
entry_minus:
  %tmp = sub i32 %0, %1
  ret i32 %tmp
}

```
```bash
$ clang main.c example_2.bc  
$ ./a.out
>sum is 84
>minus is 0
```
### Other Builder Arithmetics
You can find [here](https://llvm.org/doxygen/group__LLVMCCoreInstructionBuilder.html) More functions.
```c
LLVMValueRef 	LLVMBuildAdd (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildNSWAdd (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildNUWAdd (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildFAdd (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildSub (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildNSWSub (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildNUWSub (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildFSub (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildMul (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildNSWMul (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildNUWMul (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildFMul (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildUDiv (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildExactUDiv (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildSDiv (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
 
LLVMValueRef 	LLVMBuildExactSDiv (LLVMBuilderRef, LLVMValueRef LHS, LLVMValueRef RHS, const char *Name)
```