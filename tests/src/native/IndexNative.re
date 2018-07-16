module Mod1 = {
  let classId = __LOC__;
  let className = __MODULE__;
  let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
  classInheritance |. Hashtbl.add(classId, className);

  class t = {};
};

[@lang.class]
class _TestClass = {
  inherit class Mod1.t as super1;
  pub name = "<<<<<wilton>>>>";
};

/* module TestClass2 = {
  let classId = __LOC__;
  let className = __MODULE__;
  let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
  Hashtbl.add(classInheritance, classId, className);
  Hashtbl.iter((k, v) => Hashtbl.add(classInheritance, k, v), MyClass1.Mod1.classInheritance);
  Hashtbl.add(classInheritance, MyClass1.Mod1.classId, MyClass1.Mod1.className);

  class t = {
    inherit class MyClass1.Mod1.t as super1;
    pub name = "<<<<<wilton>>>>";
  };
}; */
