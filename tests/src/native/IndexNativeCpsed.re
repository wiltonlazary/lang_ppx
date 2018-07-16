[@ocaml.ppx.context {cookies: []}];
module Lang = {
  module type AnyClassType = {let id: string; let name: string; let inheritance: Hashtbl.t(string, string);};

  module Any = {
    module ClassType = {
      let id = __LOC__;
      let name = __MODULE__;
      let inheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
      Hashtbl.add(inheritance, id, name);

      class t = {
        as (this: 'this);
        pub classInheritance = inheritance;
        pub classId = id;
        pub className = name;
        pub is = (classType: (module AnyClassType)) => {
          module ClassType = (val (classType: (module AnyClassType)));

          try (
            {
              this#classInheritance |. Hashtbl.find(ClassType.id) |. ignore;
              true;
            }
          ) {
          | _ => false
          };
        };
      };
    };

    class t = class ClassType.t;
  };
};

module Person = {
  module ClassType = {
    let id = __LOC__;
    let name = __MODULE__;
    let inheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(inheritance, id, name);
    class t = {
      as (this: 'this);
      inherit class Lang.Any.t as super;
      pub! classInheritance = inheritance;
      pub! classId = id;
      pub! className = name;
    };
  };
  Hashtbl.iter((k, v) => Hashtbl.add(ClassType.inheritance, k, v), Lang.Any.ClassType.inheritance);

  class t = class ClassType.t;
};

module TestClass = {
  module ClassType = {
    let id = __LOC__;
    let name = __MODULE__;
    let inheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(inheritance, id, name);
    class t = {
      inherit class Lang.Any.t as super;
      pub name = "<<<<<wilton>>>>";
      pub! classInheritance = inheritance;
      pub! classId = id;
      pub! className = name;
    };
  };
  Hashtbl.iter((k, v) => Hashtbl.add(ClassType.inheritance, k, v), Lang.Any.ClassType.inheritance);

  class t = class ClassType.t;
};

print_endline(Person.ClassType.id);