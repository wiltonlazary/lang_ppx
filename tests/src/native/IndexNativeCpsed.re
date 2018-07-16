[@ocaml.ppx.context {cookies: []}];
module Mod1 = {
  let classId = __LOC__;
  let className = __MODULE__;
  let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
  classInheritance |. Hashtbl.add(classId, className);

  class t = {};
};

module TestClass = {
  let classId = __LOC__;
  let className = __MODULE__;
  let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
  Hashtbl.add(classInheritance, classId, className);
  Hashtbl.iter((k, v) => Hashtbl.add(classInheritance, k, v), Mod1.classInheritance);
  Hashtbl.add(classInheritance, Mod1.classId, Mod1.className);

  class t = {
    inherit class Mod1.t as super1;
    pub name = "<<<<<wilton>>>>";
  };
};