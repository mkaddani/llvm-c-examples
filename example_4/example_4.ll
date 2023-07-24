; ModuleID = 'example_4.bc'
source_filename = "my_module"

; Function Attrs: nofree norecurse nosync nounwind readnone
define i32 @dummy() local_unnamed_addr #0 {
entry:
  ret i32 42
}

attributes #0 = { nofree norecurse nosync nounwind readnone }
