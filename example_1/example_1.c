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