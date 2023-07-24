; ModuleID = 'example_2.bc'
source_filename = "arithmetics"

define i32 @sum(i32 %0, i32 %1) {
entry:
  %tmp = add i32 %0, %1
  ret i32 %tmp
}
