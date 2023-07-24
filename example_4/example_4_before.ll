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
