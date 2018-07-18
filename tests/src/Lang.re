external identity : 'a => 'b = "%identity";
include Belt;

module type VariantType = {type t;};

module type AnyClassType = {
  type variant = ..;
  type t;
  let classId: string;
  let className: string;
  let classInheritance: Hashtbl.t(string, string);
};

module Type = {
  type variant = ..;
};

module Any = {
  module ClassType = {
    let classId = "Any | 7a2d25ba-4e76-4144-b28e-7a41f3661d90 | " ++ __LOC__;
    let className = "Any";
    let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(classInheritance, classId, className);

    class t = {
      as (this: 'this);
      pub classInheritance = classInheritance;
      pub classId = classId;
      pub className = className;
      pub is =
        [@lang.safeis]
        (
          (classType: (module AnyClassType)) => {
            module ClassType = (val (classType: (module AnyClassType)));

            try (
              {
                this#classInheritance |. Hashtbl.find(ClassType.classId) |. ignore;
                true;
              }
            ) {
            | _ => false
            };
          }
        );
      pub check =
        [@lang.safeis]
        (
          (classType: (module AnyClassType)) => {
            module ClassType = (val (classType: (module AnyClassType)));

            try (
              {
                this#classInheritance |. Hashtbl.find(ClassType.classId) |. ignore;
                true;
              }
            ) {
            | _ => raise(Failure("@lang.class cast failure:\n" ++ this#classId ++ "\n => \n" ++ ClassType.classId))
            };
          }
        );
      pub cast = [@lang.safecast] (() => ());
    };

    /* extensible variant type */
    type variant = ..;

    type Type.variant +=
      | AnyClass(t);

    type variant +=
      | AnyClass(t);
  };

  let classType: (module AnyClassType) = (module ClassType);

  class t = class ClassType.t;
};

module VariantTypeFunctor1 = (SubjectVariant: VariantType) => {
  type Type.variant +=
    | Variance1(SubjectVariant.t);
 

  class xx = {
    pub name = "000";
  };
};

module VariantTypeFunctor2 = (SubjectVariant: VariantType) => {
  include VariantTypeFunctor1(SubjectVariant);

  class zz = {
    pub name = "000";
  };

  type Any.ClassType.variant +=
    | Variance2(SubjectVariant.t);
};

module TestGenerativeFununctor = (()) => {
  class t = {
    pub namez = "kkk";
  };

  type Any.ClassType.variant +=
    | Variance3(t);

  include VariantTypeFunctor2({
    class tx = class t;
    class t = class tx;
  });
};

module TestFun =
  TestGenerativeFununctor({});

let xx = TestFun.Variance2(new TestFun.t);