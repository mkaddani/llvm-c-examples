#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include <llvm-c/Transforms/PassManagerBuilder.h>


#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>




int main()
{
    LLVMModuleRef mod = LLVMModuleCreateWithName("my_module");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMTypeRef function_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
    LLVMValueRef function = LLVMAddFunction(mod, "dummy", function_type);
    LLVMBasicBlockRef entry_block = LLVMAppendBasicBlock(function, "entry");

    LLVMPositionBuilderAtEnd(builder, entry_block);

    // Create an i32 variable 'i' and initialize it to 0
    LLVMTypeRef i32_type = LLVMInt32Type();
    LLVMValueRef i = LLVMBuildAlloca(builder, i32_type, "i");
    LLVMBuildStore(builder, LLVMConstInt(i32_type, 0, 0), i);

    // Create an i32 variable 'j' and initialize it to 10
    LLVMValueRef j = LLVMBuildAlloca(builder, i32_type, "j");
    LLVMBuildStore(builder, LLVMConstInt(i32_type, 10, 0), j);

    // Create the loop condition block
    LLVMBasicBlockRef loop_cond_block = LLVMAppendBasicBlock(function, "loop_cond");
    LLVMBasicBlockRef loop_body_block = LLVMAppendBasicBlock(function, "loop_body");
    LLVMBasicBlockRef loop_exit_block = LLVMAppendBasicBlock(function, "loop_exit");

    LLVMBuildBr(builder, loop_cond_block);
    LLVMPositionBuilderAtEnd(builder, loop_cond_block);

    // Load the current value of 'k'
    LLVMValueRef k = LLVMBuildLoad2(builder, i32_type, i, "k");

    // Create the loop condition: k < 10
    LLVMValueRef loop_condition = LLVMBuildICmp(builder, LLVMIntULT, k, LLVMConstInt(i32_type, 10, 0), "loop_condition");

    // Create the conditional branch based on the loop condition
    LLVMBuildCondBr(builder, loop_condition, loop_body_block, loop_exit_block);

    // Build the loop body
    LLVMPositionBuilderAtEnd(builder, loop_body_block);

    // Load the current value of 'i'
    LLVMValueRef current_value = LLVMBuildLoad2(builder, i32_type, i, "current_value");

    // Increment the value of 'i'
    LLVMValueRef new_value = LLVMBuildAdd(builder, current_value, LLVMConstInt(i32_type, 1, 0), "new_value");
    LLVMBuildStore(builder, new_value, i);

    // Jump back to the loop condition block to check for the next iteration
    LLVMBuildBr(builder, loop_cond_block);

    // Build the loop exit block
    LLVMPositionBuilderAtEnd(builder, loop_exit_block);

    // Load the values of 'j' and 32
    LLVMValueRef j_value = LLVMBuildLoad2(builder, i32_type, j, "j_value");
    LLVMValueRef constant_32 = LLVMConstInt(i32_type, 32, 0);

    // Add 'j' and 32
    LLVMValueRef result = LLVMBuildAdd(builder, j_value, constant_32, "result");

    // Return the result
    LLVMBuildRet(builder, result);
    // ---------------------------------- Optimization Passes ---------------------------------
    LLVMPassManagerBuilderRef llvm_pmb;
    LLVMPassManagerRef llvm_mpm;
    LLVMPassManagerRef llvm_fpm;

    llvm_pmb = LLVMPassManagerBuilderCreate();
    LLVMPassManagerBuilderSetOptLevel(llvm_pmb, 3);
    llvm_mpm = LLVMCreatePassManager();
    llvm_fpm = LLVMCreateFunctionPassManagerForModule(mod);
    LLVMPassManagerBuilderPopulateFunctionPassManager(llvm_pmb, llvm_fpm);
    LLVMInitializeFunctionPassManager(llvm_fpm);
    LLVMPassManagerBuilderPopulateModulePassManager(llvm_pmb,
                                                    llvm_mpm);
    LLVMRunPassManager(llvm_mpm, mod);
    LLVMDisposePassManager(llvm_mpm);

    LLVMPassManagerBuilderDispose(llvm_pmb);


    if (LLVMWriteBitcodeToFile(mod, "example_4.bc") != 0)
    {
        fprintf(stderr, "error writing bitcode to file, skipping\n");
    }

}