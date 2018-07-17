[@ocaml.ppx.context {cookies: []}];
module Person = {
  module ClassType = {
    let classId = __LOC__ ++ " | 8a79e298-74c9-49fe-9873-b0504b89efb4";
    let className = "Person";
    let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(classInheritance, classId, className);
    class t (name: string, surName: string) = {
      inherit class Lang.Any.t as super;
      pub personName = name;
      pub! classInheritance = classInheritance;
      pub! classId = classId;
      pub! className = className;
    };
  };
  Hashtbl.iter((k, v) => Hashtbl.add(ClassType.classInheritance, k, v), Lang.Any.ClassType.classInheritance);
  let classType: (module Lang.AnyClassType) = (module ClassType);
  class t = class ClassType.t;
};

module TestClass = {
  module ClassType = {
    let classId = __LOC__ ++ " | df7c2533-2097-4ac3-83ed-02cd6de391d3";
    let className = "TestClass";
    let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(classInheritance, classId, className);
    class t = {
      as (this: 'this);
      inherit class Lang.Any.t as super;
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
  };
  Hashtbl.iter((k, v) => Hashtbl.add(ClassType.classInheritance, k, v), Lang.Any.ClassType.classInheritance);

  let classType: (module Lang.AnyClassType) = (module ClassType);
  class t = class ClassType.t;
};

let person = (new Person.t)("wilton", "lazary");
let testClass = new TestClass.t;
let person2 =
  if (person#is(TestClass.classType)) {
    let it: TestClass.t = Lang.identity(person);
    it;
  } else {
    raise(Failure("@lang.class cast failed: TestClass.t" ++ " | " ++ __LOC__));
  };

let () = {
  print_endline((Lang.identity(person2): TestClass.t)#personName2);
  testClass#test((person :> Lang.Any.t));
};
