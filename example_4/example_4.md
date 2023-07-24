# LLVM-C API
## Optimization Passes
### Prototype:
```c
int     dummy(void)
{
    int i = 0;
    int j = 10;
    for (int k = 0; k < 10; k++)
    {
        i++;
    }
    return (j + 32);
}
```
### LLVM-C API example:
Check this [code](/example_4/example_4.c)

before we add optimization this [IR](/example_4/example_4_before.ll) the code generate
```llvm
; ModuleID = 'example_4.bc'
source_filename = "my_module"

define i32 @dummy() {
entry:
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4
  %j = alloca i32, align 4
  store i32 10, i32* %j, align 4
  br label %loop_cond

loop_cond:                                        ; preds = %loop_body, %entry
  %k = load i32, i32* %i, align 4
  %loop_condition = icmp ult i32 %k, 10
  br i1 %loop_condition, label %loop_body, label %loop_exit

loop_body:                                        ; preds = %loop_cond
  %current_value = load i32, i32* %i, align 4
  %new_value = add i32 %current_value, 1
  store i32 %new_value, i32* %i, align 4
  br label %loop_cond

loop_exit:                                        ; preds = %loop_cond
  %j_value = load i32, i32* %j, align 4
  %result = add i32 %j_value, 32
  ret i32 %result
}

```
Compiling
```bash
$ clang main.c example_4.bc ; ./a.out
42
```
### Adding Optimization passes:
after the optimization bloc we get this [LLVM IR](/example_4/example_4.ll)
```LLVM
; ModuleID = 'example_4.bc'
source_filename = "my_module"

; Function Attrs: nofree norecurse nosync nounwind readnone
define i32 @dummy() local_unnamed_addr #0 {
entry:
  ret i32 42
}

attributes #0 = { nofree norecurse nosync nounwind readnone }

```
