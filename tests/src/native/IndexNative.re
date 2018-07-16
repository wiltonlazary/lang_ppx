module Mod = {
  let xxx = 1;
  let zzz = 2;

  [@lang.class]
  class testClass = {
    inherit class myOtherClass1 as super1;
    inherit class myOtherClass2 as super2;
    pub name = "<<<<<wilton>>>>";
  };
};