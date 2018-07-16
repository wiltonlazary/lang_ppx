module Mod0 = {
  module Mod1 = {
    let classId = __LOC__;
    let className = __MODULE__;
    let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    classInheritance |. Hashtbl.add(classId, className);

    class t = {};
  };
};

[@lang.class]
class _TestClass = {
  inherit class Mod0.Mod1.t as super1;
  pub name = "<<<<<wilton>>>>";
};