[@ocaml.ppx.context {cookies: []}];
module Person = {
  module ClassType = {
    type variant = Lang.Any.ClassType.variant = ..;
    let classId = "Person | 3aa53a77-37f1-4594-8d40-c97869bd9346 | " ++ __LOC__;
    let className = "Person";
    let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(classInheritance, classId, className);
    Hashtbl.iter((k, v) => Hashtbl.add(classInheritance, k, v), Lang.Any.ClassType.classInheritance);
    class t (name: string, surName: string) = {
      inherit class Lang.Any.t as super;
      pub personName = name;
      pub! classInheritance = classInheritance;
      pub! classId = classId;
      pub! className = className;
    };
    type variant +=
      | PersonClass(t);
  };
  let classType: (module Lang.AnyClassType) = (module ClassType);
  class t = class ClassType.t;
};

module TestClass = {
  module ClassType = {
    type variant = Lang.Any.ClassType.variant = ..;
    let classId = "TestClass | f7471e5c-9558-4181-8e0b-803c2649db5e | " ++ __LOC__;
    let className = "TestClass";
    let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(classInheritance, classId, className);
    Hashtbl.iter((k, v) => Hashtbl.add(classInheritance, k, v), Person.ClassType.classInheritance);

    class t = {
      as (this: 'this);
      inherit (class Person.t)("wilton", "lazary") as super;
      pub personName2 = "<<<<<wilton>>>>";
      pub test = (a: Lang.Any.t) => {
        ();
        print_endline(a#is(Lang.Any.classType) |> string_of_bool);
      };
      pub! classInheritance = classInheritance;
      pub! classId = classId;
      pub! className = className;
    };
    type variant +=
      | TestClassClass(t);
  };
  let classType: (module Lang.AnyClassType) = (module ClassType);
  class t = class ClassType.t;
};

let person = (new Person.t)("wilton", "lazary");
let testClass = new TestClass.t;
let person2 =
  if (testClass#check(Person.classType)) {
    let it: Person.t = Lang.identity(testClass);
    it;
  } else {
    raise(Failure("@lang.class cast failed: Person.t" ++ " | " ++ __LOC__));
  };

let () = {
  print_endline((Lang.identity(person2): TestClass.t)#personName2);
  testClass#test((person :> Lang.Any.t));
};

module OptionsParams = {
  [@bs.deriving abstract]
  type t = {
    [@bs.optional]
    language: string,
    [@bs.optional]
    session: bool,
    [@bs.optional]
    op: string,
    [@bs.optional]
    processor: string,
    [@bs.optional]
    accept: string,
  };

  let default = t(~language="gremlin-groovy", ~session=false, ~op="eval", ~processor="", ~accept="application/json", ());
};

OptionsParams.(print_endline(default |. accept |. Belt.Option.getWithDefault("---")));
