module Mod =
  struct
    let xxx = 1
    let zzz = 2
    class testClass =
      object (this)
        inherit  myOtherClass1 as super1
        inherit  myOtherClass2 as super2
        method name = "<<<<<wilton>>>>"
      end[@@lang.class ]
  end