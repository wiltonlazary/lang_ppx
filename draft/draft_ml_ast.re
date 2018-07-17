[
  {
    pstr_desc:
      [@implicit_arity]
      Pstr_value(
        Nonrecursive,
        [
          {
            pvb_pat: {
              ppat_desc:
                Ppat_var({
                  txt: "xxx",
                  loc: {
                    loc_start: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 1,
                      pos_bol: 0,
                      pos_cnum: 4
                    },
                    loc_end: {
                      pos_fname: "draft/draft_ml.ml",
                      pos_lnum: 1,
                      pos_bol: 0,
                      pos_cnum: 7
                    },
                    loc_ghost: false
                  }
                }),
              ppat_loc: {
                loc_start: {
                  pos_fname: "draft/draft_ml.ml",
                  pos_lnum: 1,
                  pos_bol: 0,
                  pos_cnum: 4
                },
                loc_end: {
                  pos_fname: "draft/draft_ml.ml",
                  pos_lnum: 1,
                  pos_bol: 0,
                  pos_cnum: 7
                },
                loc_ghost: false
              },
              ppat_attributes: []
            },
            pvb_expr: {
              pexp_desc:
                [@implicit_arity]
                Pexp_constraint(
                  {
                    pexp_desc:
                      [@implicit_arity]
                      Pexp_apply(
                        {
                          pexp_desc:
                            [@implicit_arity]
                            Pexp_send(
                              {
                                pexp_desc:
                                  Pexp_ident({
                                    txt: Lident("person"),
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
                                        pos_cnum: 26
                                      },
                                      loc_ghost: false
                                    }
                                  }),
                                pexp_loc: {
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
                                    pos_cnum: 26
                                  },
                                  loc_ghost: false
                                },
                                pexp_attributes: []
                              },
                              "cast"
                            ),
                          pexp_loc: {
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
                              pos_cnum: 31
                            },
                            loc_ghost: false
                          },
                          pexp_attributes: []
                        },
                        [
                          (
                            "",
                            {
                              pexp_desc:
                                Pexp_ident({
                                  txt:
                                    [@implicit_arity]
                                    Ldot([@implicit_arity] Ldot(Lident("Lang"), "Any"), "t"),
                                  loc: {
                                    loc_start: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 1,
                                      pos_bol: 0,
                                      pos_cnum: 32
                                    },
                                    loc_end: {
                                      pos_fname: "draft/draft_ml.ml",
                                      pos_lnum: 1,
                                      pos_bol: 0,
                                      pos_cnum: 42
                                    },
                                    loc_ghost: false
                                  }
                                }),
                              pexp_loc: {
                                loc_start: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 1,
                                  pos_bol: 0,
                                  pos_cnum: 32
                                },
                                loc_end: {
                                  pos_fname: "draft/draft_ml.ml",
                                  pos_lnum: 1,
                                  pos_bol: 0,
                                  pos_cnum: 42
                                },
                                loc_ghost: false
                              },
                              pexp_attributes: []
                            }
                          )
                        ]
                      ),
                    pexp_loc: {
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
                        pos_cnum: 42
                      },
                      loc_ghost: false
                    },
                    pexp_attributes: []
                  },
                  {
                    ptyp_desc:
                      [@implicit_arity]
                      Ptyp_constr(
                        {
                          txt: Lident("lagarto"),
                          loc: {
                            loc_start: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 1,
                              pos_bol: 0,
                              pos_cnum: 10
                            },
                            loc_end: {
                              pos_fname: "draft/draft_ml.ml",
                              pos_lnum: 1,
                              pos_bol: 0,
                              pos_cnum: 17
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
                        pos_cnum: 10
                      },
                      loc_end: {
                        pos_fname: "draft/draft_ml.ml",
                        pos_lnum: 1,
                        pos_bol: 0,
                        pos_cnum: 17
                      },
                      loc_ghost: false
                    },
                    ptyp_attributes: []
                  }
                ),
              pexp_loc: {
                loc_start: {
                  pos_fname: "draft/draft_ml.ml",
                  pos_lnum: 1,
                  pos_bol: 0,
                  pos_cnum: 8
                },
                loc_end: {
                  pos_fname: "draft/draft_ml.ml",
                  pos_lnum: 1,
                  pos_bol: 0,
                  pos_cnum: 42
                },
                loc_ghost: true
              },
              pexp_attributes: []
            },
            pvb_attributes: [],
            pvb_loc: {
              loc_start: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 1,
                pos_bol: 0,
                pos_cnum: 0
              },
              loc_end: {
                pos_fname: "draft/draft_ml.ml",
                pos_lnum: 1,
                pos_bol: 0,
                pos_cnum: 42
              },
              loc_ghost: false
            }
          }
        ]
      ),
    pstr_loc: {
      loc_start: {
        pos_fname: "draft/draft_ml.ml",
        pos_lnum: 1,
        pos_bol: 0,
        pos_cnum: 0
      },
      loc_end: {
        pos_fname: "draft/draft_ml.ml",
        pos_lnum: 1,
        pos_bol: 0,
        pos_cnum: 42
      },
      loc_ghost: false
    }
  }
];
