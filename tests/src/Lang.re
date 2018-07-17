external identity : 'a => 'b = "%identity";

module type AnyClassType = {
  let classId: string;
  let className: string;
  let classInheritance: Hashtbl.t(string, string);
};

module Any = {
  module ClassType = {
    let classId = __LOC__ ++ " | 7a2d25ba-4e76-4144-b28e-7a41f3661d90";
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
      pub cast = [@lang.safecast] (() => ());
    };
  };

  let classType: (module AnyClassType) = (module ClassType);
  class t = class ClassType.t;
};