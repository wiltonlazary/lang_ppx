[
  pstr_desc =
    Pstr_class([
      {
        pci_virt = Concrete;
        pci_params = [];
        pci_name = txt = "testClass";
        pci_expr =
          pcl_desc =
            Pcl_structure(
              {
                pcstr_self = ppat_desc = Ppat_var(txt = "this");
                pcstr_fields = [
                  pcf_desc =
                    Pcf_method((
                      txt = "name",
                      Public,
                      Cfk_concrete((
                        Fresh,
                        pexp_desc = Pexp_poly((pexp_desc = Pexp_constant(Const_string(("wilton", None))), None)),
                      )),
                    )),
                ];
              },
            );
        pci_attributes = [(txt = "xxclass", PStr([]))];
      },
    ]),
];