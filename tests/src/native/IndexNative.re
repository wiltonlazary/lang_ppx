[@lang.class]
class _Person (name: string, surName: string) = {
  inherit class Lang.AnyClass.t as super;
  pub personName = name;
};

[@lang.class]
class _Test = {
  as (this: 'this);
  inherit (class PersonClass.t)("wilton", "lazary") as super;
  pub personName2 = "<<<<<wilton>>>>";
  pub test = (a: Lang.AnyClass.t) => {
    ();
    print_endline(a#is(Lang.AnyClass.t) |> string_of_bool);
  };
};

let person = (new PersonClass.t)("wilton", "lazary");
let testClass = new TestClass.t;
let person2 = testClass#cast(PersonClass.t);

let () = {
  print_endline((Lang.identity(person2): TestClass.t)#personName2);
  testClass#test((person :> Lang.AnyClass.t));
};