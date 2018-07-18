external identity : 'a => 'b = "%identity";
include Belt;

module type VariantType = {type variant = ..;};

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

    type variant +=
      | AnyClass(t);

    type Type.variant +=
      | AnyClass(t);

    module VariantTypeFunctor = (SubjectVariant: VariantType, SubjectClassType:AnyClassType) => {
       
    };
  };

  let classType: (module AnyClassType) = (module ClassType);

  class t = class ClassType.t;
};