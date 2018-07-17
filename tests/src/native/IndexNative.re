module Lang = {
  external identity : 'a => 'b = "%identity";
  module type AnyClassType = {let id: string; let name: string; let inheritance: Hashtbl.t(string, string);};

  module Any = {
    module ClassType = {
      let id = __LOC__ ++ " | 7a2d25ba-4e76-4144-b28e-7a41f3661d90";
      let name = "Any";
      let inheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
      Hashtbl.add(inheritance, id, name);

      class t = {
        as (this: 'this);
        pub classInheritance = inheritance;
        pub classId = id;
        pub className = name;
        pub is =
          [@lang.safeis]
          (
            (classType: (module AnyClassType)) => {
              module ClassType = (val (classType: (module AnyClassType)));

              try (
                {
                  this#classInheritance |. Hashtbl.find(ClassType.id) |. ignore;
                  true;
                }
              ) {
              | _ => false
              };
            }
          );
        pub cast = [@lang.safecast] (() => ());
      };
    };

    let classType: (module AnyClassType) = (module ClassType);
    class t = class ClassType.t;
  };
};

[@lang.class]
class _Person (name: string, surName: string) = {
  inherit class Lang.Any.t as super;
  pub personName = name;
};

[@lang.class]
class _TestClass = {
  as (this: 'this);
  inherit (class Person.t)("wilton", "lazary") as super;
  pub personName2 = "<<<<<wilton>>>>";
  pub test = (a: Lang.Any.t) => {
    ();
    print_endline(a#is(Lang.Any.classType) |> string_of_bool);
  };
};

let person = (new Person.t)("wilton", "lazary");
let testClass = new TestClass.t;
let person2: Lang.Any.t = Lang.identity(testClass);

let () = {
  print_endline((Lang.identity(person2): TestClass.t)#personName2);
  testClass#test(person :> Lang.Any.t);
};