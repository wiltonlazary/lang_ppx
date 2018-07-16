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

[@lang.class]
class _Person (name:string) = {
  as (this: 'this);
  inherit class Lang.Any.t as super;
  pub personName = name;
};

[@lang.class]
class _TestClass = {
  as (this: 'this);
  inherit class Person.t as super;
  pub personName2 = "<<<<<wilton>>>>";
};

let person = (new Person.t :> Lang.Any.t);
let testClass = new TestClass.t;
let person: TestClass.t = Lang.cast(testClass);

print_endline(person#personName2);
print_endline(person#is(Person.classType) |> string_of_bool);