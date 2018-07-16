module Lang = {
  module type AnyClassType = {
    let id : string;
    let name : string;
    let inheritance: Hashtbl.t(string, string)  ; 
  };

  module Any = {
    module ClassType = {
      let id = __LOC__;
      let name = __MODULE__;
      let inheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
      Hashtbl.add(inheritance, id, name);
    };

    /* let classType : ( module AnyClassType) = (val ClassType); */

    class t = {
      as (this: 'this);
      pub classInheritance = ClassType.inheritance;
      pub className = ClassType.name;
      pub is = (classType:(module AnyClassType)) =>{
        module ClassType = (val (classType: (module AnyClassType)));

        try (
          {
            this#classInheritance |. Hashtbl.find(ClassType.id) |. ignore;
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

print_endline(Person.ClassType.id);