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
                pos_cnum: 6
              },
              loc_end: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 1,
                pos_bol: 0,
                pos_cnum: 16
              },
              loc_ghost: false
            }
          },
          pci_expr: {
            pcl_desc:
              Pcl_structure({
                pcstr_self: {
                  ppat_desc:
                    Ppat_var({
                      txt: "this",
                      loc: {
                        loc_start: {
                          pos_fname: "draft/draft_ml.ml",
                          pos_lnum: 2,
                          pos_bol: 19,
                          pos_cnum: 29
                        },
                        loc_end: {
                          pos_fname: "draft/draft_ml.ml",
                          pos_lnum: 2,
                          pos_bol: 19,
                          pos_cnum: 33
                        },
                        loc_ghost: false
                      }
                    }),
                  ppat_loc: {
                    loc_start: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 2,
                      pos_bol: 19,
                      pos_cnum: 28
                    },
                    loc_end: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 2,
                      pos_bol: 19,
                      pos_cnum: 34
                    },
                    loc_ghost: false
                  },
                  ppat_attributes: []
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
                                  [@implicit_arity]
                                  Ldot([@implicit_arity] Ldot(Lident("MyClass1"), "Mod1"), "t"),
                                loc: {
                                  loc_start: {
                                    pos_fname: "draft/draft_ml.ml",
                                    pos_lnum: 3,
                                    pos_bol: 35,
                                    pos_cnum: 48
                                  },
                                  loc_end: {
                                    pos_fname: "draft/draft_ml.ml",
                                    pos_lnum: 3,
                                    pos_bol: 35,
                                    pos_cnum: 63
                                  },
                                  loc_ghost: false
                                }
                              },
                              []
                            ),
                          pcl_loc: {
                            loc_start: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 3,
                              pos_bol: 35,
                              pos_cnum: 48
                            },
                            loc_end: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 3,
                              pos_bol: 35,
                              pos_cnum: 63
                            },
                            loc_ghost: false
                          },
                          pcl_attributes: []
                        },
                        Some("super1")
                      ),
                    pcf_loc: {
                      loc_start: {
                        pos_fname: "draft/draft_ml.ml",
                        pos_lnum: 3,
                        pos_bol: 35,
                        pos_cnum: 39
                      },
                      loc_end: {
                        pos_fname: "draft/draft_ml.ml",
                        pos_lnum: 3,
                        pos_bol: 35,
                        pos_cnum: 73
                      },
                      loc_ghost: false
                    },
                    pcf_attributes: []
                  },
                  {
                    pcf_desc:
                      [@implicit_arity]
                      Pcf_method(
                        {
                          txt: "name",
                          loc: {
                            loc_start: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 4,
                              pos_bol: 74,
                              pos_cnum: 85
                            },
                            loc_end: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 4,
                              pos_bol: 74,
                              pos_cnum: 89
                            },
                            loc_ghost: false
                          }
                        },
                        Public,
                        [@implicit_arity]
                        Cfk_concrete(
                          Fresh,
                          {
                            pexp_desc:
                              [@implicit_arity]
                              Pexp_poly(
                                {
                                  pexp_desc:
                                    Pexp_constant(
                                      [@implicit_arity] Const_string("<<<<<wilton>>>>", None)
                                    ),
                                  pexp_loc: {
                                    loc_start: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 4,
                                      pos_bol: 74,
                                      pos_cnum: 92
                                    },
                                    loc_end: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 4,
                                      pos_bol: 74,
                                      pos_cnum: 109
                                    },
                                    loc_ghost: false
                                  },
                                  pexp_attributes: []
                                },
                                None
                              ),
                            pexp_loc: {
                              loc_start: {
                                pos_fname: "draft/draft_ml.ml",
                                pos_lnum: 4,
                                pos_bol: 74,
                                pos_cnum: 85
                              },
                              loc_end: {
                                pos_fname: "draft/draft_ml.ml",
                                pos_lnum: 4,
                                pos_bol: 74,
                                pos_cnum: 109
                              },
                              loc_ghost: true
                            },
                            pexp_attributes: []
                          }
                        )
                      ),
                    pcf_loc: {
                      loc_start: {
                        pos_fname: "draft/draft_ml.ml",
                        pos_lnum: 4,
                        pos_bol: 74,
                        pos_cnum: 78
                      },
                      loc_end: {
                        pos_fname: "draft/draft_ml.ml",
                        pos_lnum: 4,
                        pos_bol: 74,
                        pos_cnum: 109
                      },
                      loc_ghost: false
                    },
                    pcf_attributes: []
                  }
                ]
              }),
            pcl_loc: {
              loc_start: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 2,
                pos_bol: 19,
                pos_cnum: 21
              },
              loc_end: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 5,
                pos_bol: 110,
                pos_cnum: 115
              },
              loc_ghost: false
            },
            pcl_attributes: []
          },
          pci_loc: {
            loc_start: {
              pos_fname: "draft/draft_ml.ml",
              pos_lnum: 1,
              pos_bol: 0,
              pos_cnum: 0
            },
            loc_end: {
              pos_fname: "draft/draft_ml.ml",
              pos_lnum: 5,
              pos_bol: 110,
              pos_cnum: 130
            },
            loc_ghost: false
          },
          pci_attributes: [
            (
              {
                txt: "lang.class",
                loc: {
                  loc_start: {
                    pos_fname: "draft/draft_ml.ml",
                    pos_lnum: 5,
                    pos_bol: 110,
                    pos_cnum: 118
                  },
                  loc_end: {
                    pos_fname: "draft/draft_ml.ml",
                    pos_lnum: 5,
                    pos_bol: 110,
                    pos_cnum: 128
                  },
                  loc_ghost: false
                }
              },
              PStr([])
            )
          ]
        }
      ]),
    pstr_loc: {
      loc_start: {
        pos_fname: "draft/draft_ml.ml",
        pos_lnum: 1,
        pos_bol: 0,
        pos_cnum: 0
      },
      loc_end: {
        pos_fname: "draft/draft_ml.ml",
        pos_lnum: 5,
        pos_bol: 110,
        pos_cnum: 130
      },
      loc_ghost: false
    }
  }
];
