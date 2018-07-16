[
  {
    pstr_desc:
      Pstr_class([
        {
          pci_virt: Concrete,
          pci_params: [],
          pci_name: {
            txt: "testClass",
          },
          pci_expr: {
            pcl_desc:
              Pcl_structure({
                pcstr_self: {
                  ppat_desc: Ppat_var({txt: "this"}),
                },
                pcstr_fields: [
                  {
                    pcf_desc:
                      [@implicit_arity]
                      Pcf_method(
                        {txt: "name"},
                        Public,
                        [@implicit_arity]
                        Cfk_concrete(
                          Fresh,
                          {
                            pexp_desc:
                              [@implicit_arity]
                              Pexp_poly(
                                {pexp_desc: Pexp_constant([@implicit_arity] Const_string("wilton", None))},
                                None,
                              ),
                          },
                        ),
                      ),
                  },
                ],
              }),
          },
          pci_attributes: [({txt: "xxclass"}, PStr([]))],
        },
      ]),
  },
];