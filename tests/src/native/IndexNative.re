module Lang = {
  module type AnyClassType = {
    let classId : string;
    let className : string;
    let classInheritance: Hashtbl.t(string, string)  ; 
  };

  module Any = {
    module ClassType = {
      let classId = __LOC__;
      let className = __MODULE__;
      let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
      Hashtbl.add(classInheritance, classId, className);
    };

    let classType : ( module AnyClassType) = val ClassType;

    class t = {
      as (this: 'this);
      pub classInheritance = classInheritance;
      pub className = className;
      pub is = (classType:(module AnyClassType)) =>{
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
    };
  };
};

[@lang.class]
class _Person = {
  as (this: 'this);
};

[@lang.class]
class _TestClass = {
  inherit class Lang.Any.t as super;
  pub name = "<<<<<wilton>>>>";
};

print_endline(Person.classId);