[
  {
    pstr_desc:
      Pstr_class([
        {
          pci_virt: Concrete,
          pci_params: [
            (
              {
                ptyp_desc: Ptyp_var("a"),
                ptyp_loc: {
                  loc_start: {
                    pos_fname: "draft/draft_ml.ml",
                    pos_lnum: 1,
                    pos_bol: 0,
                    pos_cnum: 7
                  },
                  loc_end: {
                    pos_fname: "draft/draft_ml.ml",
                    pos_lnum: 1,
                    pos_bol: 0,
                    pos_cnum: 9
                  },
                  loc_ghost: false
                },
                ptyp_attributes: []
              },
              Invariant
            )
          ],
          pci_name: {
            txt: "_Person",
            loc: {
              loc_start: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 1,
                pos_bol: 0,
                pos_cnum: 11
              },
              loc_end: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 1,
                pos_bol: 0,
                pos_cnum: 18
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
                                pos_cnum: 20
                              },
                              loc_end: {
                                pos_fname: "draft/draft_ml.ml",
                                pos_lnum: 1,
                                pos_bol: 0,
                                pos_cnum: 24
                              },
                              loc_ghost: false
                            }
                          }),
                        ppat_loc: {
                          loc_start: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 1,
                            pos_bol: 0,
                            pos_cnum: 20
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 1,
                            pos_bol: 0,
                            pos_cnum: 24
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
                                  pos_cnum: 27
                                },
                                loc_end: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 1,
                                  pos_bol: 0,
                                  pos_cnum: 33
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
                            pos_cnum: 27
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 1,
                            pos_bol: 0,
                            pos_cnum: 33
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
                      pos_cnum: 19
                    },
                    loc_end: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 1,
                      pos_bol: 0,
                      pos_cnum: 34
                    },
                    loc_ghost: false
                  },
                  ppat_attributes: []
                },
                {
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
                                  txt: "surName",
                                  loc: {
                                    loc_start: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 1,
                                      pos_bol: 0,
                                      pos_cnum: 37
                                    },
                                    loc_end: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 1,
                                      pos_bol: 0,
                                      pos_cnum: 44
                                    },
                                    loc_ghost: false
                                  }
                                }),
                              ppat_loc: {
                                loc_start: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 1,
                                  pos_bol: 0,
                                  pos_cnum: 37
                                },
                                loc_end: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 1,
                                  pos_bol: 0,
                                  pos_cnum: 44
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
                                        pos_cnum: 47
                                      },
                                      loc_end: {
                                        pos_fname: "draft/draft_ml.ml",
                                        pos_lnum: 1,
                                        pos_bol: 0,
                                        pos_cnum: 53
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
                                  pos_cnum: 47
                                },
                                loc_end: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 1,
                                  pos_bol: 0,
                                  pos_cnum: 53
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
                            pos_cnum: 36
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 1,
                            pos_bol: 0,
                            pos_cnum: 54
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
                                Ppat_var({
                                  txt: "this",
                                  loc: {
                                    loc_start: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 2,
                                      pos_bol: 57,
                                      pos_cnum: 67
                                    },
                                    loc_end: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 2,
                                      pos_bol: 57,
                                      pos_cnum: 71
                                    },
                                    loc_ghost: false
                                  }
                                }),
                              ppat_loc: {
                                loc_start: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 2,
                                  pos_bol: 57,
                                  pos_cnum: 66
                                },
                                loc_end: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 2,
                                  pos_bol: 57,
                                  pos_cnum: 72
                                },
                                loc_ghost: false
                              },
                              ppat_attributes: []
                            },
                            pcstr_fields: [
                              {
                                pcf_desc:
                                  [@implicit_arity]
                                  Pcf_method(
                                    {
                                      txt: "personName",
                                      loc: {
                                        loc_start: {
                                          pos_fname: "draft/draft_ml.ml",
                                          pos_lnum: 2,
                                          pos_bol: 57,
                                          pos_cnum: 80
                                        },
                                        loc_end: {
                                          pos_fname: "draft/draft_ml.ml",
                                          pos_lnum: 2,
                                          pos_bol: 57,
                                          pos_cnum: 90
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
                                                Pexp_ident({
                                                  txt: Lident("name"),
                                                  loc: {
                                                    loc_start: {
                                                      pos_fname: "draft/draft_ml.ml",
                                                      pos_lnum: 2,
                                                      pos_bol: 57,
                                                      pos_cnum: 93
                                                    },
                                                    loc_end: {
                                                      pos_fname: "draft/draft_ml.ml",
                                                      pos_lnum: 2,
                                                      pos_bol: 57,
                                                      pos_cnum: 97
                                                    },
                                                    loc_ghost: false
                                                  }
                                                }),
                                              pexp_loc: {
                                                loc_start: {
                                                  pos_fname: "draft/draft_ml.ml",
                                                  pos_lnum: 2,
                                                  pos_bol: 57,
                                                  pos_cnum: 93
                                                },
                                                loc_end: {
                                                  pos_fname: "draft/draft_ml.ml",
                                                  pos_lnum: 2,
                                                  pos_bol: 57,
                                                  pos_cnum: 97
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
                                            pos_lnum: 2,
                                            pos_bol: 57,
                                            pos_cnum: 80
                                          },
                                          loc_end: {
                                            pos_fname: "draft/draft_ml.ml",
                                            pos_lnum: 2,
                                            pos_bol: 57,
                                            pos_cnum: 97
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
                                    pos_lnum: 2,
                                    pos_bol: 57,
                                    pos_cnum: 73
                                  },
                                  loc_end: {
                                    pos_fname: "draft/draft_ml.ml",
                                    pos_lnum: 2,
                                    pos_bol: 57,
                                    pos_cnum: 97
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
                            pos_bol: 57,
                            pos_cnum: 59
                          },
                          loc_end: {
                            pos_fname: "draft/draft_ml.ml",
                            pos_lnum: 2,
                            pos_bol: 57,
                            pos_cnum: 101
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
                      pos_cnum: 36
                    },
                    loc_end: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 2,
                      pos_bol: 57,
                      pos_cnum: 101
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
                pos_cnum: 19
              },
              loc_end: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 2,
                pos_bol: 57,
                pos_cnum: 101
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
              pos_lnum: 2,
              pos_bol: 57,
              pos_cnum: 101
            },
            loc_ghost: false
          },
          pci_attributes: []
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
        pos_lnum: 2,
        pos_bol: 57,
        pos_cnum: 101
      },
      loc_ghost: false
    }
  }
];
