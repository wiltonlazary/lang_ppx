[@ocaml.ppx.context {cookies: []}];
module Mod = {
  let xxx = 1;
  let zzz = 2;

  module TestClass = {
    class t = {
      inherit class myOtherClass1 as super1;
      inherit class myOtherClass2 as super2;
      pub name = "<<<<<wilton>>>>";
    };
  };
};
