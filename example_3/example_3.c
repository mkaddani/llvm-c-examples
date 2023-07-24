#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


typedef int (*funcPtr_t)(int , int);


int main()
{
    //Create a new, empty module in the global context.
    //Every invocation should be paired with LLVMDisposeModule() or memory will be leaked.
    LLVMModuleRef mod = LLVMModuleCreateWithName("arithmetics");
    LLVMBuilderRef builder = LLVMCreateBuilder();



// --------------------------------------------- SUM FUNCTION ------------------------------------------------------------------
    LLVMTypeRef param_types[] = {LLVMInt32Type(), LLVMInt32Type()}; // this mean that out function take as a parameter two ints
    LLVMTypeRef func_type = LLVMFunctionType(LLVMInt32Type(), param_types, 2, 0);

    LLVMValueRef sum_function = LLVMAddFunction(mod, "sum", func_type);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(sum_function, "entry");

    LLVMPositionBuilderAtEnd(builder, entry);


    LLVMValueRef tmp = LLVMBuildAdd(builder, LLVMGetParam(sum_function, 0), LLVMGetParam(sum_function, 1), "tmp");
    LLVMBuildRet(builder, tmp);
// --------------------------------------------- MINUS FUNCTION ------------------------------------------------------------------
    LLVMValueRef minus_function = LLVMAddFunction(mod, "minus", func_type);
    LLVMBasicBlockRef entry_minus = LLVMAppendBasicBlock(minus_function, "entry_minus");
    LLVMPositionBuilderAtEnd(builder, entry_minus);
    tmp = LLVMBuildSub(builder, LLVMGetParam(minus_function, 0), LLVMGetParam(minus_function, 1), "tmp");
    LLVMBuildRet(builder, tmp);
// --------------------------------------------- MULTIPLICATION FUNCTION ------------------------------------------------------------------
    LLVMValueRef mult_function = LLVMAddFunction(mod, "mult", func_type);
    LLVMBasicBlockRef entry_mult = LLVMAppendBasicBlock(mult_function, "entry_mult");
    LLVMPositionBuilderAtEnd(builder, entry_mult);
    tmp = LLVMBuildMul(builder, LLVMGetParam(mult_function, 0), LLVMGetParam(mult_function, 1), "tmp");
    LLVMBuildRet(builder, tmp);

// -------------------------------------------------- JIT -------------------------------------------------------------------------------
    char *error = NULL;
    LLVMVerifyModule(mod, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage(error);
    fprintf(stderr, "Module verified\n");

    LLVMExecutionEngineRef engine;
    error = NULL;
    LLVMLinkInMCJIT();
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeAsmParser();

    if (LLVMCreateExecutionEngineForModule(&engine, mod, &error) != 0) {
        fprintf(stderr, "failed to create execution engine\n");
        abort();
    }
    if (error) {
        fprintf(stderr, "error: %s\n", error);
        LLVMDisposeMessage(error);
        exit(EXIT_FAILURE);
    }
    {
        funcPtr_t funcSumPtr = (funcPtr_t)LLVMGetPointerToGlobal(engine, sum_function);
        funcPtr_t funcSubPtr = (funcPtr_t)LLVMGetPointerToGlobal(engine, minus_function);
        funcPtr_t funcMultPtr = (funcPtr_t)LLVMGetPointerToGlobal(engine, mult_function);


        fprintf(stderr, "sum is %d\n",funcSumPtr(42, 42));
        fprintf(stderr, "sub is %d\n",funcSubPtr(42, 42));
        fprintf(stderr, "mult is %d\n",funcMultPtr(5, 5));

    }
    LLVMDisposeBuilder(builder);
    LLVMDisposeExecutionEngine(engine);
}