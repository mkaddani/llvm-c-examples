# LLVM-C API
## Resources

- [LLVM C API Documentation](https://llvm.org/doxygen/group__LLVMC.html)
- [LLVM Project Website](https://llvm.org/)
- [LLVM GitHub Repository](https://github.com/llvm/llvm-project)
- [LLVM Hello](https://github.com/MWGuy/llvm-hello)
- [LLVM C examples](https://github.com/wickedchicken/llvm-c-example)

## Compiling
- Check [this file](/llvm_tool.py) to get compiling commands and instructions.

## Important Headers.
```c
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
```
## First LLVM-C API example
**Goal**: writing an LLVM-IR representation of a function that return ***int***.
### 1: C prototype:
```c
int answer(void)
{
    return (42);
}
```
### 2: Function pointer
```c
typedef int (*funcPtr_t)(void);
``` 

### 3: Lets describe the function using LLVM-C API
```c
int main()
{
    //Create a new, empty module in the global context.
    //Every invocation should be paired with LLVMDisposeModule() or memory will be leaked.
    LLVMModuleRef mod = LLVMModuleCreateWithName("my_answer");

    /*
        The function is defined as a tuple of a return Type, a list of
        parameter types, and whether the function is variadic.
        LLVMTypeRef LLVMFunctionType(LLVMTypeRef ReturnType,
                                    LLVMTypeRef *ParamTypes, unsigned ParamCount,
                                    LLVMBool IsVarArg);
    */
    LLVMTypeRef param_types[] = {LLVMVoidType()}; // this mean that out function take as a parameter void
    LLVMTypeRef func_type = LLVMFunctionType(LLVMInt32Type(), param_types, 0, 0);
    /**
     * Add a function to a module under a specified name.
     *
     * @see llvm::Function::Create()
     
    LLVMValueRef LLVMAddFunction(LLVMModuleRef M, const char *Name,
                                LLVMTypeRef FunctionTy);
    */
    LLVMValueRef answer = LLVMAddFunction(mod, "answer", func_type);
    /**
     * Append a basic block to the end of a function using the global
     * context.
     */
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(answer, "entry");

    // Write out bitcode to file
    if (LLVMWriteBitcodeToFile(mod, "example_1.bc") != 0)
    {
        fprintf(stderr, "error writing bitcode to file, skipping\n");
    }

}

```
Compiling this code
```bash
$ python ../llvm_tool.py -filename example_1.c 
$ ./example_1.exec
$ llvm-dis-14 example_1.bc 
```
we get [example_1.ll](/example_1/example_1.ll) an LLVM IR representation of our ``answer`` function.

```llvm
; ModuleID = 'example_1.bc'
source_filename = "my_answer"

define i32 @answer() {
entry:
}

```