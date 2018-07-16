[@ocaml.ppx.context {cookies: []}];
module Lang = {
  external cast : 'a => 'b = "%identity";
  module type AnyClassType = {let id: string; let name: string; let inheritance: Hashtbl.t(string, string);};

  module Any = {
    module ClassType = {
      let id = __LOC__;
      let name = "Any";
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

    let classType: (module AnyClassType) = (module ClassType);
    class t = class ClassType.t;
  };
};

module Person = {
  module ClassType = {
    let id = __LOC__;
    let name = "Person";
    let inheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(inheritance, id, name);
    class t = {
      as (this: 'this);
      inherit class Lang.Any.t as super;
      pub personName = name;
      pub! classInheritance = inheritance;
      pub! classId = id;
      pub! className = name;
    };
  };
  Hashtbl.iter((k, v) => Hashtbl.add(ClassType.inheritance, k, v), Lang.Any.ClassType.inheritance);

  let classType: (module Lang.AnyClassType) = (module ClassType);
  class t = class ClassType.t;
};

module TestClass = {
  module ClassType = {
    let id = __LOC__;
    let name = "TestClass";
    let inheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(inheritance, id, name);
    class t = {
      as (this: 'this);
      inherit class Person.t as super;
      pub personName2 = "<<<<<wilton>>>>";
      pub! classInheritance = inheritance;
      pub! classId = id;
      pub! className = name;
    };
  };
  Hashtbl.iter((k, v) => Hashtbl.add(ClassType.inheritance, k, v), Person.ClassType.inheritance);

  let classType: (module Lang.AnyClassType) = (module ClassType);
  class t = class ClassType.t;
};

let person = (new Person.t :> Lang.Any.t);
let testClass = new TestClass.t;
let person: TestClass.t = Lang.cast(testClass);

print_endline(person#personName2);
print_endline(person#is(Person.classType) |> string_of_bool);
