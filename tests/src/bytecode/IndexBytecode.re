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
    print_endline(a#is(Lang.Any.t) |> string_of_bool);
  };
};

let person = (new Person.t)("wilton", "lazary");
let testClass = new TestClass.t;
let person2 = testClass#cast(Person.t);

let () = {
  print_endline((Lang.identity(person2): TestClass.t)#personName2);
  testClass#test((person :> Lang.Any.t));
};