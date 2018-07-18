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

  let default =
    t(~language="gremlin-groovy", ~session=false, ~op="eval", ~processor="", ~accept="application/json", ());
};

OptionsParams.(print_endline(default |. accept |. Belt.Option.getWithDefault("---")));

/* let testVariance = (p0:TestClass.ClassType.variant) =>{
     ();

     print_endline("testVariance: ok");
   };

   testVariance(Person.ClassType.PersonClass(person)); */

module VariantTypeFunctor1 = (SubjectVariant: Lang.VariantType) => {
  type Lang.Type.variant +=
    | Variance1(int);

  class xx = {
    pub name = "000";
  };
};

module VariantTypeFunctor2 = (SubjectVariant: Lang.VariantType) => {
  include VariantTypeFunctor1(SubjectVariant);

  class zz = {
    pub name = "000";
  };

  type Lang.Any.ClassType.variant +=
    | Variance2(string);
};

module TestGenerativeFununctor = (()) => {
  include VariantTypeFunctor2({
    type variant = ..;
    type variant  += | Variance3 ;

    class t = {
      pub namez = "kkk";
      pub name1 = "kkk";
    };
  });

  type Lang.Any.ClassType.variant +=
    | Variance3(int);
};

module TestFun =
  TestGenerativeFununctor({});

/* let xx = TestFun.Variance3(new TestFun.t); */

type xx('a) = ..;

type xx('a) +=
  | V1('a)
  | V2(string)
  | V3(xx('a));

type xx('a) +=
  | V4;

type pp = xx(Person.t);

let x = V3(V3(V1(person)));

let tc = V3(V3(V1(testClass)));

let proc = (a: pp) => a;

let z = proc(x);

/* type cc = ..; */
type cc = [ | `V];