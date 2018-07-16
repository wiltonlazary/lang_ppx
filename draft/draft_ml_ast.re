/* [
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
                         Pcf_inherit(
                           Fresh,
                           {pcl_desc: [@implicit_arity] Pcl_constr({txt: Lident("myOtherClass")}, [])},
                           Some("super"),
                         ),
                     },
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
                                   {pexp_desc: Pexp_constant([@implicit_arity] Const_string("<<<<<wilton>>>>", None))},
                                   None,
                                 ),
                             },
                           ),
                         ),
                     },
                   ],
                 }),
             },
             pci_attributes: [({txt: "lang.class"}, PStr([]))],
           },
         ]),
     },
   ]; */

[
  {
    pstr_desc:
      Pstr_module({
        pmb_name: {
          txt: "Mod",
        },
        pmb_expr: {
          pmod_desc:
            Pmod_structure([
              {
                pstr_desc:
                  [@implicit_arity]
                  Pstr_value(
                    Nonrecursive,
                    [
                      {
                        pvb_pat: {
                          ppat_desc: Ppat_var({txt: "x"}),
                        },
                        pvb_expr: {
                          pexp_desc: Pexp_constant(Const_int(1)),
                        },
                      },
                    ],
                  ),
              },
            ]),
        },
      }),
  },
];