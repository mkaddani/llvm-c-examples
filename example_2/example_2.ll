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

define i32 @mult(i32 %0, i32 %1) {
entry_mult:
  %tmp = mul i32 %0, %1
  ret i32 %tmp
}
