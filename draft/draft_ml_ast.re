[
  {
    pstr_desc:
      Pstr_class([
        {
          pci_virt: Concrete,
          pci_params: [],
          pci_name: {
            txt: "_TestClass",
            loc: {
              loc_start: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 1,
                pos_bol: 0,
                pos_cnum: 6,
              },
              loc_end: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 1,
                pos_bol: 0,
                pos_cnum: 16,
              },
              loc_ghost: false,
            },
          },
          pci_expr: {
            pcl_desc:
              Pcl_structure({
                pcstr_self: {
                  ppat_desc:
                    [@implicit_arity]
                    Ppat_constraint(
                      {
                        ppat_desc:
                          Ppat_var({
                            txt: "this",
                            loc: {
                              loc_start: {
                                pos_fname: "draft/draft_ml.ml",
                                pos_lnum: 2,
                                pos_bol: 19,
                                pos_cnum: 29,
                              },
                              loc_end: {
                                pos_fname: "draft/draft_ml.ml",
                                pos_lnum: 2,
                                pos_bol: 19,
                                pos_cnum: 33,
                              },
                              loc_ghost: false,
                            },
                          }),
                        ppat_loc: {
                          loc_start: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 2,
                            pos_bol: 19,
                            pos_cnum: 29,
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 2,
                            pos_bol: 19,
                            pos_cnum: 33,
                          },
                          loc_ghost: false,
                        },
                        ppat_attributes: [],
                      },
                      {
                        ptyp_desc: Ptyp_var("this"),
                        ptyp_loc: {
                          loc_start: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 2,
                            pos_bol: 19,
                            pos_cnum: 36,
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 2,
                            pos_bol: 19,
                            pos_cnum: 41,
                          },
                          loc_ghost: false,
                        },
                        ptyp_attributes: [],
                      },
                    ),
                  ppat_loc: {
                    loc_start: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 2,
                      pos_bol: 19,
                      pos_cnum: 28,
                    },
                    loc_end: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 2,
                      pos_bol: 19,
                      pos_cnum: 42,
                    },
                    loc_ghost: false,
                  },
                  ppat_attributes: [],
                },
                pcstr_fields: [
                  {
                    pcf_desc:
                      [@implicit_arity]
                      Pcf_inherit(
                        Fresh,
                        {
                          pcl_desc:
                            [@implicit_arity]
                            Pcl_apply(
                              {
                                pcl_desc:
                                  [@implicit_arity]
                                  Pcl_constr(
                                    {
                                      txt: [@implicit_arity] Ldot(Lident("Person"), "t"),
                                      loc: {
                                        loc_start: {
                                          pos_fname: "draft/draft_ml.ml",
                                          pos_lnum: 2,
                                          pos_bol: 19,
                                          pos_cnum: 53,
                                        },
                                        loc_end: {
                                          pos_fname: "draft/draft_ml.ml",
                                          pos_lnum: 2,
                                          pos_bol: 19,
                                          pos_cnum: 61,
                                        },
                                        loc_ghost: false,
                                      },
                                    },
                                    [],
                                  ),
                                pcl_loc: {
                                  loc_start: {
                                    pos_fname: "draft/draft_ml.ml",
                                    pos_lnum: 2,
                                    pos_bol: 19,
                                    pos_cnum: 53,
                                  },
                                  loc_end: {
                                    pos_fname: "draft/draft_ml.ml",
                                    pos_lnum: 2,
                                    pos_bol: 19,
                                    pos_cnum: 61,
                                  },
                                  loc_ghost: false,
                                },
                                pcl_attributes: [],
                              },
                              [
                                (
                                  "",
                                  {
                                    pexp_desc: Pexp_constant([@implicit_arity] Const_string("wilton", None)),
                                    pexp_loc: {
                                      loc_start: {
                                        pos_fname: "draft/draft_ml.ml",
                                        pos_lnum: 2,
                                        pos_bol: 19,
                                        pos_cnum: 62,
                                      },
                                      loc_end: {
                                        pos_fname: "draft/draft_ml.ml",
                                        pos_lnum: 2,
                                        pos_bol: 19,
                                        pos_cnum: 70,
                                      },
                                      loc_ghost: false,
                                    },
                                    pexp_attributes: [],
                                  },
                                ),
                                (
                                  "",
                                  {
                                    pexp_desc: Pexp_constant([@implicit_arity] Const_string("lazary", None)),
                                    pexp_loc: {
                                      loc_start: {
                                        pos_fname: "draft/draft_ml.ml",
                                        pos_lnum: 2,
                                        pos_bol: 19,
                                        pos_cnum: 71,
                                      },
                                      loc_end: {
                                        pos_fname: "draft/draft_ml.ml",
                                        pos_lnum: 2,
                                        pos_bol: 19,
                                        pos_cnum: 79,
                                      },
                                      loc_ghost: false,
                                    },
                                    pexp_attributes: [],
                                  },
                                ),
                              ],
                            ),
                          pcl_loc: {
                            loc_start: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 2,
                              pos_bol: 19,
                              pos_cnum: 53,
                            },
                            loc_end: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 2,
                              pos_bol: 19,
                              pos_cnum: 79,
                            },
                            loc_ghost: false,
                          },
                          pcl_attributes: [],
                        },
                        Some("super"),
                      ),
                    pcf_loc: {
                      loc_start: {
                        pos_fname: "draft/draft_ml.ml",
                        pos_lnum: 2,
                        pos_bol: 19,
                        pos_cnum: 43,
                      },
                      loc_end: {
                        pos_fname: "draft/draft_ml.ml",
                        pos_lnum: 2,
                        pos_bol: 19,
                        pos_cnum: 89,
                      },
                      loc_ghost: false,
                    },
                    pcf_attributes: [],
                  },
                ],
              }),
            pcl_loc: {
              loc_start: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 2,
                pos_bol: 19,
                pos_cnum: 21,
              },
              loc_end: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 2,
                pos_bol: 19,
                pos_cnum: 93,
              },
              loc_ghost: false,
            },
            pcl_attributes: [],
          },
          pci_loc: {
            loc_start: {
              pos_fname: "draft/draft_ml.ml",
              pos_lnum: 1,
              pos_bol: 0,
              pos_cnum: 0,
            },
            loc_end: {
              pos_fname: "draft/draft_ml.ml",
              pos_lnum: 3,
              pos_bol: 94,
              pos_cnum: 109,
            },
            loc_ghost: false,
          },
          pci_attributes: [
            (
              {
                txt: "lang.class",
                loc: {
                  loc_start: {
                    pos_fname: "draft/draft_ml.ml",
                    pos_lnum: 3,
                    pos_bol: 94,
                    pos_cnum: 97,
                  },
                  loc_end: {
                    pos_fname: "draft/draft_ml.ml",
                    pos_lnum: 3,
                    pos_bol: 94,
                    pos_cnum: 107,
                  },
                  loc_ghost: false,
                },
              },
              PStr([]),
            ),
          ],
        },
      ]),
    pstr_loc: {
      loc_start: {
        pos_fname: "draft/draft_ml.ml",
        pos_lnum: 1,
        pos_bol: 0,
        pos_cnum: 0,
      },
      loc_end: {
        pos_fname: "draft/draft_ml.ml",
        pos_lnum: 3,
        pos_bol: 94,
        pos_cnum: 109,
      },
      loc_ghost: false,
    },
  },
];
