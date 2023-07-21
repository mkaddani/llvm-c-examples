#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include <llvm-c/Transforms/PassManagerBuilder.h>

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/*
    size_t      ft_strlen(const char *s)
    {
        size_t	i;

        i = 0;
        while (s[i])
            i++;
        return (i);
    }
*/
/*
    size_t      ft_strlen(const char *s)
    {
        size_t	i = 4;
        return (i);
    }
*/
typedef size_t (*funcPtr_t)(const char*);


int main()
{
      fprintf(stderr, "ALL STARTED\n");

    // the module name 
  LLVMModuleRef mod = LLVMModuleCreateWithName("my_ft_strlen");
    // the paramteres of function ft_strlen (char *str)
  LLVMTypeRef param_types[] = { LLVMPointerType(LLVMInt8Type(), 0) };
    // here we define the return type of our ft_strlen which is size_t
  LLVMTypeRef ret_type = LLVMFunctionType(LLVMInt64Type(), param_types, 1, 0);

  LLVMValueRef ft_strlen = LLVMAddFunction(mod, "ft_strlen", ret_type);
  LLVMBasicBlockRef entry = LLVMAppendBasicBlock(ft_strlen, "entry");

  LLVMBuilderRef builder = LLVMCreateBuilder();
  LLVMPositionBuilderAtEnd(builder, entry);
 
    fprintf(stderr, "Builder created\n");

  LLVMTypeRef i64_type = LLVMInt64Type();
  LLVMValueRef local_var = LLVMBuildAlloca(builder, i64_type, "my_local_var");
  LLVMBuildStore(builder, LLVMConstInt(i64_type, 4, 0), local_var);

  //lets increment the variable
  LLVMValueRef current_value = LLVMBuildLoad2(builder, LLVMInt64Type() ,local_var, "my_local_var");
  LLVMValueRef increment_value = LLVMConstInt(LLVMTypeOf(current_value), 40, 0);
  LLVMValueRef new_value = LLVMBuildAdd(builder, current_value , increment_value, "new_value");
  // the local varible = new variable
  LLVMBuildStore(builder, new_value, local_var);


  LLVMValueRef returned_value = LLVMBuildLoad2(builder, LLVMInt64Type() ,local_var, "my_local_var");
  LLVMBuildRet(builder, returned_value);

    // lets Optimize
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
        fprintf(stderr, "ONE\n");
        fprintf(stderr, "failed to create execution engine\n");
        abort();
    }
    if (error) {
        fprintf(stderr, "TWO\n");
        fprintf(stderr, "error: %s\n", error);
        LLVMDisposeMessage(error);
        exit(EXIT_FAILURE);
    }


    {
        funcPtr_t funcPtr = (funcPtr_t)LLVMGetPointerToGlobal(engine, ft_strlen);
        int j = funcPtr("sss");
        fprintf(stderr, "j is %d\n",j);

    }

    // Write out bitcode to file
    if (LLVMWriteBitcodeToFile(mod, "bill.bc") != 0) {
        fprintf(stderr, "THREE\n");
        fprintf(stderr, "error writing bitcode to file, skipping\n");
    }
    fprintf(stderr, "ALL DONE\n");
    LLVMDisposeBuilder(builder);
    LLVMDisposeExecutionEngine(engine);

}