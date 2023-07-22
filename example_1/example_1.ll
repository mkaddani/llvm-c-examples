; ModuleID = 'example_1.bc'
source_filename = "my_answer"

define i32 @answer() {
entry:
  %vogsphere = alloca i32, align 4
  store i32 42, i32* %vogsphere, align 4
  %vogsphere1 = load i32, i32* %vogsphere, align 4
  ret i32 %vogsphere1
}
