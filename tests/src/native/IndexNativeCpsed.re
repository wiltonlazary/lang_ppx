[@ocaml.ppx.context {cookies: []}];
module PersonClass = {
  module Type = {
    type variant = Lang.AnyClass.Type.variant = ..;
    let classId = "Person | 38540d6d-2d63-4858-a163-89108de73eef | " ++ __LOC__;
    let className = "Person";
    let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(classInheritance, classId, className);
    Hashtbl.iter((k, v) => Hashtbl.add(classInheritance, k, v), Lang.AnyClass.Type.classInheritance);
    class t (name: string, surName: string) = {
      inherit class Lang.AnyClass.t as super;
      pub personName = name;
      pub! classInheritance = classInheritance;
      pub! classId = classId;
      pub! className = className;
    };
    type Lang.AnyClass.Type.variant +=
      | PersonClassVariant(t);
  };
  let classType: (module Lang.AnyClassType) = (module Type);
  class t = class Type.t;
};

module TestClass = {
  module Type = {
    type variant = Lang.AnyClass.Type.variant = ..;
    let classId = "Test | 42b59fe0-680e-4d75-beca-d1d92f87922c | " ++ __LOC__;
    let className = "Test";
    let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(classInheritance, classId, className);
    Hashtbl.iter((k, v) => Hashtbl.add(classInheritance, k, v), PersonClass.Type.classInheritance);

    class t = {
      as (this: 'this);
      inherit (class PersonClass.t)("wilton", "lazary") as super;
      pub personName2 = "<<<<<wilton>>>>";
      pub test = (a: Lang.AnyClass.t) => {
        ();
        print_endline(a#is(Lang.AnyClass.classType) |> string_of_bool);
      };
      pub! classInheritance = classInheritance;
      pub! classId = classId;
      pub! className = className;
    };
    type Lang.AnyClass.Type.variant +=
      | TestClassVariant(t);
  };
  let classType: (module Lang.AnyClassType) = (module Type);
  class t = class Type.t;
};

let person = (new PersonClass.t)("wilton", "lazary");
let testClass = new TestClass.t;
let person2 =
  if (testClass#check(PersonClass.classType)) {
    let it: PersonClass.t = Lang.identity(testClass);
    it;
  } else {
    raise(Failure("@lang.class cast failed: PersonClass.t" ++ " | " ++ __LOC__));
  };

let () = {
  print_endline((Lang.identity(person2): TestClass.t)#personName2);
  testClass#test((person :> Lang.AnyClass.t));
};
