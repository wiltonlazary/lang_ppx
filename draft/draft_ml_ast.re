[
  {
    pstr_desc:
      Pstr_class([
        {
          pci_virt: Concrete,
          pci_params: [],
          pci_name: {
            txt: "_Person",
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
                pos_cnum: 13
              },
              loc_ghost: false
            }
          },
          pci_expr: {
            pcl_desc:
              [@implicit_arity]
              Pcl_fun(
                "",
                None,
                {
                  ppat_desc:
                    [@implicit_arity]
                    Ppat_constraint(
                      {
                        ppat_desc:
                          Ppat_var({
                            txt: "name",
                            loc: {
                              loc_start: {
                                pos_fname: "draft/draft_ml.ml",
                                pos_lnum: 1,
                                pos_bol: 0,
                                pos_cnum: 15
                              },
                              loc_end: {
                                pos_fname: "draft/draft_ml.ml",
                                pos_lnum: 1,
                                pos_bol: 0,
                                pos_cnum: 19
                              },
                              loc_ghost: false
                            }
                          }),
                        ppat_loc: {
                          loc_start: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 1,
                            pos_bol: 0,
                            pos_cnum: 15
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 1,
                            pos_bol: 0,
                            pos_cnum: 19
                          },
                          loc_ghost: false
                        },
                        ppat_attributes: []
                      },
                      {
                        ptyp_desc:
                          [@implicit_arity]
                          Ptyp_constr(
                            {
                              txt: Lident("string"),
                              loc: {
                                loc_start: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 1,
                                  pos_bol: 0,
                                  pos_cnum: 22
                                },
                                loc_end: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 1,
                                  pos_bol: 0,
                                  pos_cnum: 28
                                },
                                loc_ghost: false
                              }
                            },
                            []
                          ),
                        ptyp_loc: {
                          loc_start: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 1,
                            pos_bol: 0,
                            pos_cnum: 22
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 1,
                            pos_bol: 0,
                            pos_cnum: 28
                          },
                          loc_ghost: false
                        },
                        ptyp_attributes: []
                      }
                    ),
                  ppat_loc: {
                    loc_start: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 1,
                      pos_bol: 0,
                      pos_cnum: 14
                    },
                    loc_end: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 1,
                      pos_bol: 0,
                      pos_cnum: 29
                    },
                    loc_ghost: false
                  },
                  ppat_attributes: []
                },
                {
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
                                      pos_bol: 32,
                                      pos_cnum: 42
                                    },
                                    loc_end: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 2,
                                      pos_bol: 32,
                                      pos_cnum: 46
                                    },
                                    loc_ghost: false
                                  }
                                }),
                              ppat_loc: {
                                loc_start: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 2,
                                  pos_bol: 32,
                                  pos_cnum: 42
                                },
                                loc_end: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 2,
                                  pos_bol: 32,
                                  pos_cnum: 46
                                },
                                loc_ghost: false
                              },
                              ppat_attributes: []
                            },
                            {
                              ptyp_desc: Ptyp_var("this"),
                              ptyp_loc: {
                                loc_start: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 2,
                                  pos_bol: 32,
                                  pos_cnum: 49
                                },
                                loc_end: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 2,
                                  pos_bol: 32,
                                  pos_cnum: 54
                                },
                                loc_ghost: false
                              },
                              ptyp_attributes: []
                            }
                          ),
                        ppat_loc: {
                          loc_start: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 2,
                            pos_bol: 32,
                            pos_cnum: 41
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 2,
                            pos_bol: 32,
                            pos_cnum: 55
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
                                        Ldot([@implicit_arity] Ldot(Lident("Lang"), "Any"), "t"),
                                      loc: {
                                        loc_start: {
                                          pos_fname: "draft/draft_ml.ml",
                                          pos_lnum: 3,
                                          pos_bol: 56,
                                          pos_cnum: 69
                                        },
                                        loc_end: {
                                          pos_fname: "draft/draft_ml.ml",
                                          pos_lnum: 3,
                                          pos_bol: 56,
                                          pos_cnum: 79
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
                                    pos_bol: 56,
                                    pos_cnum: 69
                                  },
                                  loc_end: {
                                    pos_fname: "draft/draft_ml.ml",
                                    pos_lnum: 3,
                                    pos_bol: 56,
                                    pos_cnum: 79
                                  },
                                  loc_ghost: false
                                },
                                pcl_attributes: []
                              },
                              Some("super")
                            ),
                          pcf_loc: {
                            loc_start: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 3,
                              pos_bol: 56,
                              pos_cnum: 60
                            },
                            loc_end: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 3,
                              pos_bol: 56,
                              pos_cnum: 88
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
                                txt: "personName",
                                loc: {
                                  loc_start: {
                                    pos_fname: "draft/draft_ml.ml",
                                    pos_lnum: 4,
                                    pos_bol: 89,
                                    pos_cnum: 100
                                  },
                                  loc_end: {
                                    pos_fname: "draft/draft_ml.ml",
                                    pos_lnum: 4,
                                    pos_bol: 89,
                                    pos_cnum: 110
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
                                            [@implicit_arity] Const_string("hehe name", None)
                                          ),
                                        pexp_loc: {
                                          loc_start: {
                                            pos_fname: "draft/draft_ml.ml",
                                            pos_lnum: 4,
                                            pos_bol: 89,
                                            pos_cnum: 113
                                          },
                                          loc_end: {
                                            pos_fname: "draft/draft_ml.ml",
                                            pos_lnum: 4,
                                            pos_bol: 89,
                                            pos_cnum: 124
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
                                      pos_bol: 89,
                                      pos_cnum: 100
                                    },
                                    loc_end: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 4,
                                      pos_bol: 89,
                                      pos_cnum: 124
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
                              pos_bol: 89,
                              pos_cnum: 93
                            },
                            loc_end: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 4,
                              pos_bol: 89,
                              pos_cnum: 124
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
                      pos_bol: 32,
                      pos_cnum: 34
                    },
                    loc_end: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 5,
                      pos_bol: 125,
                      pos_cnum: 130
                    },
                    loc_ghost: false
                  },
                  pcl_attributes: []
                }
              ),
            pcl_loc: {
              loc_start: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 1,
                pos_bol: 0,
                pos_cnum: 14
              },
              loc_end: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 5,
                pos_bol: 125,
                pos_cnum: 130
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
              pos_bol: 125,
              pos_cnum: 145
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
                    pos_bol: 125,
                    pos_cnum: 133
                  },
                  loc_end: {
                    pos_fname: "draft/draft_ml.ml",
                    pos_lnum: 5,
                    pos_bol: 125,
                    pos_cnum: 143
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
        pos_bol: 125,
        pos_cnum: 145
      },
      loc_ghost: false
    }
  }
];
