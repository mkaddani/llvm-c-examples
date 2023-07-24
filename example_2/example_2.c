#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>




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




    if (LLVMWriteBitcodeToFile(mod, "example_2.bc") != 0)
    {
        fprintf(stderr, "error writing bitcode to file, skipping\n");
    }

}