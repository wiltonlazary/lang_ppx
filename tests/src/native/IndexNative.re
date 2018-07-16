module Lang = {
  module type AnyClassTypeBody = {
    let classId : string;
    let className : string;
    let classInheritance: Hashtbl.t(string, string)  ; 
  };

  module type AnyClassType = {
    include AnyClassTypeBody;

    class type t = {
      pub classInheritance: Hashtbl.t(string, string);
      pub className: string;
      pub is : (module AnyClassTypeBody) => bool;
    }
  };

  module Any = {
    let classId = __LOC__;
    let className = __MODULE__;
    let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
    Hashtbl.add(classInheritance, classId, className);

    class t = {
      as (this: 'this);
      pub classInheritance = classInheritance;
      pub className = className;
      pub is = (classType:(module AnyClassTypeBody)) =>{
        module ClassType = (val (classType: (module AnyClassTypeBody)));

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