[
  {
    pstr_desc:
      Pstr_class([
        {
          pci_virt: Concrete,
          pci_params: [],
          pci_name: {
            txt: "person",
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
                pos_cnum: 12,
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
                                pos_bol: 15,
                                pos_cnum: 25,
                              },
                              loc_end: {
                                pos_fname: "draft/draft_ml.ml",
                                pos_lnum: 2,
                                pos_bol: 15,
                                pos_cnum: 29,
                              },
                              loc_ghost: false,
                            },
                          }),
                        ppat_loc: {
                          loc_start: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 2,
                            pos_bol: 15,
                            pos_cnum: 25,
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 2,
                            pos_bol: 15,
                            pos_cnum: 29,
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
                            pos_bol: 15,
                            pos_cnum: 32,
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 2,
                            pos_bol: 15,
                            pos_cnum: 37,
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
                      pos_bol: 15,
                      pos_cnum: 24,
                    },
                    loc_end: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 2,
                      pos_bol: 15,
                      pos_cnum: 38,
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
                            Pcl_constr(
                              {
                                txt:
                                  [@implicit_arity] Ldot(Lident("Any"), "t"),
                                loc: {
                                  loc_start: {
                                    pos_fname: "draft/draft_ml.ml",
                                    pos_lnum: 3,
                                    pos_bol: 39,
                                    pos_cnum: 52,
                                  },
                                  loc_end: {
                                    pos_fname: "draft/draft_ml.ml",
                                    pos_lnum: 3,
                                    pos_bol: 39,
                                    pos_cnum: 57,
                                  },
                                  loc_ghost: false,
                                },
                              },
                              [],
                            ),
                          pcl_loc: {
                            loc_start: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 3,
                              pos_bol: 39,
                              pos_cnum: 52,
                            },
                            loc_end: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 3,
                              pos_bol: 39,
                              pos_cnum: 57,
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
                        pos_lnum: 3,
                        pos_bol: 39,
                        pos_cnum: 43,
                      },
                      loc_end: {
                        pos_fname: "draft/draft_ml.ml",
                        pos_lnum: 3,
                        pos_bol: 39,
                        pos_cnum: 66,
                      },
                      loc_ghost: false,
                    },
                    pcf_attributes: [],
                  },
                  {
                    pcf_desc:
                      [@implicit_arity]
                      Pcf_method(
                        {
                          txt: "classInheritance",
                          loc: {
                            loc_start: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 4,
                              pos_bol: 67,
                              pos_cnum: 79,
                            },
                            loc_end: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 4,
                              pos_bol: 67,
                              pos_cnum: 95,
                            },
                            loc_ghost: false,
                          },
                        },
                        Public,
                        [@implicit_arity]
                        Cfk_concrete(
                          Override,
                          {
                            pexp_desc:
                              [@implicit_arity]
                              Pexp_poly(
                                {
                                  pexp_desc:
                                    Pexp_ident({
                                      txt: Lident("classInheritance"),
                                      loc: {
                                        loc_start: {
                                          pos_fname: "draft/draft_ml.ml",
                                          pos_lnum: 4,
                                          pos_bol: 67,
                                          pos_cnum: 98,
                                        },
                                        loc_end: {
                                          pos_fname: "draft/draft_ml.ml",
                                          pos_lnum: 4,
                                          pos_bol: 67,
                                          pos_cnum: 114,
                                        },
                                        loc_ghost: false,
                                      },
                                    }),
                                  pexp_loc: {
                                    loc_start: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 4,
                                      pos_bol: 67,
                                      pos_cnum: 98,
                                    },
                                    loc_end: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 4,
                                      pos_bol: 67,
                                      pos_cnum: 114,
                                    },
                                    loc_ghost: false,
                                  },
                                  pexp_attributes: [],
                                },
                                None,
                              ),
                            pexp_loc: {
                              loc_start: {
                                pos_fname: "draft/draft_ml.ml",
                                pos_lnum: 4,
                                pos_bol: 67,
                                pos_cnum: 77,
                              },
                              loc_end: {
                                pos_fname: "draft/draft_ml.ml",
                                pos_lnum: 4,
                                pos_bol: 67,
                                pos_cnum: 114,
                              },
                              loc_ghost: true,
                            },
                            pexp_attributes: [],
                          },
                        ),
                      ),
                    pcf_loc: {
                      loc_start: {
                        pos_fname: "draft/draft_ml.ml",
                        pos_lnum: 4,
                        pos_bol: 67,
                        pos_cnum: 71,
                      },
                      loc_end: {
                        pos_fname: "draft/draft_ml.ml",
                        pos_lnum: 4,
                        pos_bol: 67,
                        pos_cnum: 114,
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
                pos_bol: 15,
                pos_cnum: 17,
              },
              loc_end: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 5,
                pos_bol: 115,
                pos_cnum: 120,
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
              pos_lnum: 5,
              pos_bol: 115,
              pos_cnum: 120,
            },
            loc_ghost: false,
          },
          pci_attributes: [],
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
        pos_lnum: 5,
        pos_bol: 115,
        pos_cnum: 120,
      },
      loc_ghost: false,
    },
  },
];
