[@lang.class]
class testClass = {
  as this;
  inherit (class myOtherClass) as super;
  pub name = "<<<<<wilton>>>>";
};

print_endline((new MyMod.t)#name);