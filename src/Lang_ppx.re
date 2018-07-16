[@ocaml.ppx.context {cookies: []}];
open Parsetree;
open Ast_mapper;
open Ast_helper;
open Asttypes;
open Longident;

let debugln = print_endline;

let fail = (loc, txt) => raise(Location.Error(Location.error(~loc, txt)));

let emptyPstr = PStr([]);

let unitExpr = [%expr ()];

let exprToPayload = expr => PStr([Str.mk(Pstr_eval(expr, []))]);

let stringToExpr = s => Exp.mk(Pexp_constant(Const_string(s, None)));

let stringToPayload = s => PStr([Str.mk(Pstr_eval(stringToExpr(s), []))]);

let printExpr = expr => {
  Pprintast.expression(Format.str_formatter, expr);
  debugln(Format.flush_str_formatter());
};

let getExpr = (payload, loc) =>
  Parsetree.(
    switch (payload) {
    | PStr([{pstr_desc: Pstr_eval(expr, _)}]) => expr
    | _ => fail(loc, "must contain an expression")
    }
  );

let endsWith = (fragment, self) => {
  let len = String.length(self);
  len >= String.length(fragment) && String.sub(self, len - 3, 3) == fragment;
};

let skipExpr = expr => Exp.attr(expr, ({txt: "langskipped", loc: default_loc^}, emptyPstr));

let leafExpr = (expr, tag) => Exp.attr(expr, ({txt: "langleaf", loc: default_loc^}, stringToPayload(tag)));

let continuationExpr = expr => Exp.attr(expr, ({txt: "langcontinuation", loc: default_loc^}, emptyPstr));

let matchesCpsApply = id =>
  id == "await" || id == "delay" || id |> endsWith("Cps") || id |> endsWith("Await") || id |> endsWith("Delay");

let mkLetExpr = (recFlag, varName, varNameLoc, expr, constraintType, inExpr) =>
  Exp.mk(
    Pexp_let(
      recFlag,
      [
        {
          pvb_pat: {
            ppat_desc: Ppat_var({txt: varName, loc: varNameLoc}),
            ppat_loc: varNameLoc,
            ppat_attributes: [],
          },
          pvb_attributes: [],
          pvb_loc: varNameLoc,
          pvb_expr:
            switch (constraintType) {
            | Some(constraintType) => {
                pexp_desc: Pexp_constraint(expr, constraintType),
                pexp_loc: varNameLoc,
                pexp_attributes: [],
              }
            | None => expr
            },
        },
      ],
      inExpr,
    ),
  );

let mkLetIdentExpr = (recFlag, varName, varNameLoc, identName, constraintType, inExpr) =>
  Exp.mk(
    Pexp_let(
      recFlag,
      [
        {
          pvb_pat: {
            ppat_desc: Ppat_var({txt: varName, loc: varNameLoc}),
            ppat_loc: varNameLoc,
            ppat_attributes: [],
          },
          pvb_attributes: [],
          pvb_loc: varNameLoc,
          pvb_expr:
            switch (constraintType) {
            | Some(constraintType) => {
                pexp_desc:
                  Pexp_constraint(
                    {
                      pexp_desc: Pexp_ident({txt: Lident(identName), loc: varNameLoc}),
                      pexp_loc: varNameLoc,
                      pexp_attributes: [],
                    },
                    constraintType,
                  ),
                pexp_loc: varNameLoc,
                pexp_attributes: [],
              }
            | None => {
                pexp_desc: Pexp_ident({txt: Lident(identName), loc: varNameLoc}),
                pexp_loc: varNameLoc,
                pexp_attributes: [],
              }
            },
        },
      ],
      inExpr,
    ),
  );

let mkTryExpr = (expr, caseExprs) => Exp.try_(expr, caseExprs);

let parsers = {
  pri processMatchBranch = (~from="_", branched, matchExpr, caseExprs, nextExpr) => {
    let resumeExprsBranched = ref(0);
    let (resumeExprs, hasResumeExprs) =
      switch (nextExpr) {
      | Some(nextExpr) => (this#descendantParser(~from=__LOC__, nextExpr, resumeExprsBranched), true)
      | None => (unitExpr, false)
      };

    let matchExprBranched = ref(0);
    let matchExpr = this#descendantParser(~from=__LOC__, matchExpr, matchExprBranched);

    let lasCasePattern = ref(None);
    let caseExprsBranched = ref(0);

    let caseExprsComputed =
      caseExprs
      |> List.map(it =>
           switch (it) {
           | {pc_lhs: pattern, pc_guard: guard, pc_rhs: expr} =>
             lasCasePattern := Some(pattern);
             let caseExprBranchedLocal = ref(0);
             let caseExpr = this#descendantParser(~from=__LOC__, expr, caseExprBranchedLocal);
             caseExprsBranched := caseExprsBranched^ + caseExprBranchedLocal^;
             (Exp.case(pattern, ~guard?, caseExpr), caseExprBranchedLocal^ > 0);
           }
         );

    branched := branched^ + resumeExprsBranched^ + matchExprBranched^ + caseExprsBranched^;

    let matchLoc =
      switch (lasCasePattern^) {
      | None => default_loc^
      | Some(pattern) =>
        switch (pattern) {
        | {ppat_loc: loc} => loc
        }
      };

    if (branched^ > 0) {
      let caseExprs =
        caseExprsComputed
        |> List.map(it =>
             switch (it |> fst) {
             | {pc_lhs: pattern, pc_guard: guard, pc_rhs: expr} =>
               if (it |> snd) {
                 Exp.case(
                   pattern,
                   ~guard?,
                   try%expr ([%e expr]) {
                   | error =>
                     _lang_branch_error_(error);
                     _lang_resumed_^ ? `Continued : `Suspended;
                   },
                 );
               } else {
                 Exp.case(
                   pattern,
                   ~guard?,
                   try%expr (
                     {
                       let _lang_result_ = [%e expr];
                       _lang_branch_resume_(_lang_result_);
                       _lang_resumed_^ ? `Continued : `Suspended;
                     }
                   ) {
                   | error =>
                     _lang_branch_error_(error);
                     _lang_resumed_^ ? `Continued : `Suspended;
                   },
                 );
               }
             }
           );

      let%expr _lang_resumed_ = ref(false);
      let _dbg_lang_from = [%e stringToExpr(from)];
      let _lang_branch_resume_ = _lang_result_ =>
        if (_lang_resumed_^) {
          raise(Failure("match lang already resumed: " ++ __LOC__));
        } else {
          _lang_resumed_ := true;
          /*          debugln("match lang resumed: " ++ __LOC__);*/
          if%e (resumeExprsBranched^ == 0) {
            %expr
            if%e (hasResumeExprs) {
              let%expr _lang_result_ = [%e leafExpr(resumeExprs, "r")];
              _lang_branch_resume_(_lang_result_);
            } else {
              %expr
              _lang_branch_resume_(_lang_result_);
            };
          } else {
            continuationExpr(resumeExprs);
          };
          ();
        };
      let _lang_resumed_ = ref(false);
      let _lang_branch_resume_ = _lang_result_ =>
        if (_lang_resumed_^) {
          raise(Failure("match branch lang already resumed: " ++ __LOC__));
        } else {
          _lang_resumed_ := true;
          /*          debugln("match branch lang resumed: " ++ __LOC__);*/
          %e
          Exp.match(~loc=matchLoc, [%expr _lang_result_], caseExprs);
          ();
        };
      if%e (matchExprBranched^ > 0) {
        matchExpr;
      } else {
        let%expr _lang_result_ = [%e matchExpr];
        _lang_branch_resume_(_lang_result_);
        _lang_resumed_^ ? `Continued : `Suspended;
      };
    } else {
      %expr
      if%e (hasResumeExprs) {
        let%expr _lang_result_ = [%e Exp.match(~loc=matchLoc, matchExpr, caseExprs)];
        %e
        resumeExprs;
      } else {
        let%expr _lang_result_ = [%e Exp.match(~loc=matchLoc, matchExpr, caseExprs)];
        _lang_result_;
      };
    };
  };
  pri processIfthenelseBranch = (~from="_", branched, ifExpr, thenExpr, elseExpr, nextExpr) => {
    let resumeExprsBranched = ref(0);
    let (resumeExprs, hasResumeExprs) =
      switch (nextExpr) {
      | Some(nextExpr) => (this#descendantParser(~from=__LOC__, nextExpr, resumeExprsBranched), true)
      | None => (unitExpr, false)
      };

    let ifExprBranched = ref(0);
    let ifExpr = this#descendantParser(~from=__LOC__, ifExpr, ifExprBranched);

    let thenExprBranched = ref(0);
    let thenExpr = this#descendantParser(~from=__LOC__, thenExpr, thenExprBranched);

    let elseExprBranched = ref(0);
    let elseExpr =
      switch (elseExpr) {
      | Some(elseExpr) => this#descendantParser(~from=__LOC__, elseExpr, elseExprBranched)
      | None => unitExpr
      };

    branched := branched^ + resumeExprsBranched^ + ifExprBranched^ + thenExprBranched^ + elseExprBranched^;

    if (branched^ > 0) {
      let thenExpr =
        thenExprBranched^ > 0 ?
          thenExpr :
          {
            let%expr _lang_result_ = [%e thenExpr];
            _lang_branch_resume_(_lang_result_);
            _lang_resumed_^ ? `Continued : `Suspended;
          };

      let elseExpr =
        elseExprBranched^ > 0 ?
          elseExpr :
          {
            let%expr _lang_result_ = [%e elseExpr];
            _lang_branch_resume_(_lang_result_);
            _lang_resumed_^ ? `Continued : `Suspended;
          };

      let%expr _lang_resumed_ = ref(false);
      let _dbg_lang_from = [%e stringToExpr(from)];
      let _lang_branch_resume_ = _lang_result_ =>
        if (_lang_resumed_^) {
          raise(Failure("Ifthenelse lang already resumed: " ++ __LOC__));
        } else {
          _lang_resumed_ := true;
          /*          debugln("Ifthenelse lang branched resumed: " ++ __LOC__);*/

          if%e (resumeExprsBranched^ == 0) {
            %expr
            if%e (hasResumeExprs) {
              let%expr _lang_result_ = [%e leafExpr(resumeExprs, "r")];
              _lang_branch_resume_(_lang_result_);
            } else {
              %expr
              _lang_branch_resume_(_lang_result_);
            };
          } else {
            continuationExpr(resumeExprs);
          };
          ();
        };
      let _lang_resumed_ = ref(false);
      let _lang_branch_resume_ = _lang_result_ =>
        if (_lang_resumed_^) {
          raise(Failure("Ifthenelse branch lang already resumed: " ++ __LOC__));
        } else {
          _lang_resumed_ := true;
          /*          debugln("match branch lang resumed: " ++ __LOC__);*/
          if (_lang_result_) {
            %e
            thenExpr;
          } else {
            %e
            elseExpr;
          };
          ();
        };
      if%e (ifExprBranched^ > 0) {
        ifExpr;
      } else {
        let%expr _lang_result_ = [%e ifExpr];
        _lang_branch_resume_(_lang_result_);
        _lang_resumed_^ ? `Continued : `Suspended;
      };
    } else {
      %expr
      if%e (hasResumeExprs) {
        let%expr _lang_result_ =
          if ([%e ifExpr]) {
            %e
            thenExpr;
          } else {
            %e
            elseExpr;
          };
        %e
        resumeExprs;
      } else {
        let%expr _lang_result_ =
          if ([%e ifExpr]) {
            %e
            thenExpr;
          } else {
            %e
            elseExpr;
          };
        _lang_result_;
      };
    };
  };
  pri processTryBranch = (~from="_", branched, tryExpr, caseExprs, nextExpr) => {
    let resumeExprsBranched = ref(0);
    let (resumeExprs, hasResumeExprs) =
      switch (nextExpr) {
      | Some(nextExpr) => (this#descendantParser(~from=__LOC__, nextExpr, resumeExprsBranched), true)
      | None => (unitExpr, false)
      };

    let tryExprBranched = ref(0);
    let tryExpr = this#descendantParser(~from=__LOC__, tryExpr, tryExprBranched);

    let lasCasePattern = ref(None);
    let caseExprsBranched = ref(0);

    let caseExprsComputed =
      caseExprs
      |> List.map(it =>
           switch (it) {
           | {pc_lhs: pattern, pc_guard: guard, pc_rhs: expr} =>
             lasCasePattern := Some(pattern);
             let caseExprBranchedLocal = ref(0);
             let caseExpr = this#descendantParser(~from=__LOC__, expr, caseExprBranchedLocal);
             caseExprsBranched := caseExprsBranched^ + caseExprBranchedLocal^;
             (Exp.case(pattern, ~guard?, caseExpr), caseExprBranchedLocal^ > 0);
           }
         );

    branched := branched^ + resumeExprsBranched^ + tryExprBranched^ + caseExprsBranched^;

    if (branched^ > 0) {
      let matchLoc =
        switch (lasCasePattern^) {
        | None => default_loc^
        | Some(pattern) =>
          switch (pattern) {
          | {ppat_loc: loc} => loc
          }
        };

      let caseExprs =
        caseExprsComputed
        |> List.map(it =>
             switch (it |> fst) {
             | {pc_lhs: pattern, pc_guard: guard, pc_rhs: expr} =>
               if (it |> snd) {
                 Exp.case(
                   pattern,
                   ~guard?,
                   try%expr ([%e expr]) {
                   | error =>
                     _lang_branch_error_(error);
                     _lang_resumed_^ ? `Continued : `Suspended;
                   },
                 );
               } else {
                 Exp.case(
                   pattern,
                   ~guard?,
                   try%expr (
                     {
                       let _lang_result_ = [%e expr];
                       _lang_branch_resume_(_lang_result_);
                       _lang_resumed_^ ? `Continued : `Suspended;
                     }
                   ) {
                   | error =>
                     _lang_branch_error_(error);
                     _lang_resumed_^ ? `Continued : `Suspended;
                   },
                 );
               }
             }
           );

      let tryExpr =
        tryExprBranched^ > 0 ?
          tryExpr :
          {
            let%expr _lang_result_ = [%e tryExpr];
            _lang_branch_resume_(_lang_result_);
          };

      let%expr _lang_resumed_ = ref(false);
      let _dbg_lang_from = [%e stringToExpr(from)];
      let _lang_branch_resume_ = _lang_result_ =>
        if (_lang_resumed_^) {
          raise(Failure("try lang already resumed: " ++ __LOC__));
        } else {
          _lang_resumed_ := true;
          /*          debugln("try lang resumed: " ++ __LOC__);*/
          if%e (resumeExprsBranched^ == 0) {
            %expr
            if%e (hasResumeExprs) {
              let%expr _lang_result_ = [%e leafExpr(resumeExprs, "r")];
              _lang_branch_resume_(_lang_result_);
            } else {
              %expr
              _lang_branch_resume_(_lang_result_);
            };
          } else {
            continuationExpr(resumeExprs);
          };
          ();
        };
      let _lang_branch_error_ = _lang_error_ =>
        if (_lang_resumed_^) {
          raise(Failure("try lang error already resumed: " ++ __LOC__));
        } else {
          /*          debugln("try lang error resumed: " ++ __LOC__);*/
          %e
          Exp.match(~loc=matchLoc, [%expr _lang_error_], caseExprs);
          ();
        };
      try ([%e tryExpr]) {
      | error =>
        _lang_branch_error_(error);
        _lang_resumed_^ ? `Continued : `Suspended;
      };
    } else {
      %expr
      if%e (hasResumeExprs) {
        let%expr _lang_result_ = [%e mkTryExpr(tryExpr, caseExprs)];
        %e
        resumeExprs;
      } else {
        let%expr _lang_result_ = [%e mkTryExpr(tryExpr, caseExprs)];
        _lang_result_;
      };
    };
  };
  pri processSequenceBranch = (branched, actualSequenceExpr, nextSequenceExpr) =>
    switch (actualSequenceExpr) {
    | {pexp_attributes: [({txt: "defer", loc}, payload)]} =>
      let resumeExprsBranched = ref(0);
      let resumeExprs = this#descendantParser(~from=__LOC__, nextSequenceExpr, resumeExprsBranched);
      this#parseCpsDeferExpr(
        ~from=__LOC__,
        branched,
        actualSequenceExpr,
        loc,
        resumeExprs,
        resumeExprsBranched^,
        false,
      );
    | {pexp_attributes: [({txt: "nolang", loc}, payload)]} => actualSequenceExpr
    | {pexp_attributes: [({txt: "lang", loc}, payload)]} =>
      this#parseLangClassExpr(actualSequenceExpr, payload, loc)
    | {pexp_desc: Pexp_extension(({txt: "lang", loc}, payload))} =>
      this#parseLangClassExpr(getExpr(payload, loc), payload, loc)
    | {pexp_desc: Pexp_let(recFlag, bindings, inExpr)} =>
      /*      debugln("WARNING: *********processLetBranch actualSequenceExpr:*********");*/
      this#processLetBranch(branched, recFlag, bindings, inExpr, Some(nextSequenceExpr))
    | {pexp_desc: Pexp_apply({pexp_desc: Pexp_ident({txt: Lident(id), loc})}, expressions)}
        when matchesCpsApply(id) =>
      let resumeExprsBranched = ref(0);
      let resumeExprs = this#descendantParser(~from=__LOC__, nextSequenceExpr, resumeExprsBranched);
      this#parseCpsApplyExp(~from=__LOC__, branched, id, expressions, loc, resumeExprs, resumeExprsBranched^, false);
    | {pexp_desc: Pexp_ifthenelse(ifExpr, thenExpr, elseExpr)} =>
      this#processIfthenelseBranch(branched, ifExpr, thenExpr, elseExpr, Some(nextSequenceExpr))
    | {pexp_desc: Pexp_try(tryExpr, caseExprs)} =>
      this#processTryBranch(branched, tryExpr, caseExprs, Some(nextSequenceExpr))
    | {pexp_desc: Pexp_match(matchExpr, caseExprs)} =>
      this#processMatchBranch(branched, matchExpr, caseExprs, Some(nextSequenceExpr))
    | other => Exp.mk(Pexp_sequence(other, this#descendantParser(~from=__LOC__, nextSequenceExpr, branched)))
    };
  pri processLetBranch = (branched, recFlag, bindings, inExpr, nextSequenceExpr) =>
    if (List.length(bindings) == 1) {
      let processBindingExpr = (varName, varNameLoc, bindingExpr, constraintType) =>
        switch (bindingExpr) {
        | {pexp_attributes: [({txt: "defer", loc}, payload)]} =>
          let resumeExprsBranched = ref(0);
          let resumeExprs =
            mkLetIdentExpr(
              recFlag,
              varName,
              varNameLoc,
              "_lang_result_",
              constraintType,
              this#descendantParser(~from=__LOC__, inExpr, resumeExprsBranched),
            );
          this#parseCpsDeferExpr(~from=__LOC__, branched, bindingExpr, loc, resumeExprs, resumeExprsBranched^, false);
        | {pexp_attributes: [({txt: "nolang", loc}, payload)]} =>
          mkLetExpr(
            recFlag,
            varName,
            varNameLoc,
            bindingExpr,
            constraintType,
            this#descendantParser(~from=__LOC__, inExpr, branched),
          )
        | {pexp_attributes: [({txt: "lang", loc}, payload)]} =>
          mkLetExpr(
            recFlag,
            varName,
            varNameLoc,
            this#parseLangClassExpr(bindingExpr, payload, loc),
            constraintType,
            this#descendantParser(~from=__LOC__, inExpr, branched),
          )
        | {pexp_desc: Pexp_extension(({txt: "lang", loc}, payload))} =>
          mkLetExpr(
            recFlag,
            varName,
            varNameLoc,
            this#parseLangClassExpr(getExpr(payload, loc), payload, loc),
            constraintType,
            this#descendantParser(~from=__LOC__, inExpr, branched),
          )
        | {pexp_desc: Pexp_apply({pexp_desc: Pexp_ident({txt: Lident(id), loc})}, expressions)}
            when matchesCpsApply(id) =>
          /*          debugln("processLetBranch pvb_pat apply lang single binding: varName = " ++ varName);*/
          let resumeExprsBranched = ref(0);
          let resumeExprs =
            mkLetIdentExpr(
              recFlag,
              varName,
              varNameLoc,
              "_lang_result_",
              constraintType,
              this#descendantParser(~from=__LOC__, inExpr, resumeExprsBranched),
            );
          this#parseCpsApplyExp(
            ~from=__LOC__,
            branched,
            id,
            expressions,
            loc,
            resumeExprs,
            resumeExprsBranched^,
            false,
          );
        | {pexp_desc: Pexp_ifthenelse(ifExpr, thenExpr, elseExpr)} =>
          /*          debugln("processLetBranch pvb_pat ifthenelse lang single binding: varName = " ++ varName);*/
          let nextExprs = mkLetIdentExpr(recFlag, varName, varNameLoc, "_lang_result_", constraintType, inExpr);
          this#processIfthenelseBranch(branched, ifExpr, thenExpr, elseExpr, Some(nextExprs));
        | {pexp_desc: Pexp_try(tryExpr, caseExprs)} =>
          let nextExprs = mkLetIdentExpr(recFlag, varName, varNameLoc, "_lang_result_", constraintType, inExpr);
          this#processTryBranch(branched, tryExpr, caseExprs, Some(nextExprs));
        | {pexp_desc: Pexp_match(matchExpr, caseExprs)} =>
          let nextExprs = mkLetIdentExpr(recFlag, varName, varNameLoc, "_lang_result_", constraintType, inExpr);
          this#processMatchBranch(branched, matchExpr, caseExprs, Some(nextExprs));
        | other =>
          let bindingExprBranched = ref(0);
          let bindingExpr = this#descendantParser(~from=__LOC__, bindingExpr, bindingExprBranched);

          if (bindingExprBranched^ == 0) {
            /*            debugln("processLetBranch bindingExprBranched == 0, pvb_pat other single binding: varName = " ++ varName);*/
            Exp.mk(
              Pexp_let(recFlag, bindings, this#descendantParser(~from=__LOC__, inExpr, branched)),
            );
          } else {
            /*            debugln("processLetBranch bindingExprBranched > 0, pvb_pat other single binding: varName = " ++ varName);*/
            let resumeExprsBranched = ref(0);
            let resumeExprs =
              mkLetIdentExpr(
                recFlag,
                varName,
                varNameLoc,
                "_lang_result_",
                constraintType,
                this#descendantParser(~from=__LOC__, inExpr, resumeExprsBranched),
              );

            branched := branched^ + bindingExprBranched^ + resumeExprsBranched^;

            if (resumeExprsBranched^ == 0) {
              [@metaloc varNameLoc]
              {
                let%expr _lang_branch_resume_ = {
                  let _lang_resumed_ = ref(false);
                  (
                    _lang_result_ =>
                      if (_lang_resumed_^) {
                        raise(Failure("binding lang direct already resumed: " ++ __LOC__));
                      } else {
                        _lang_resumed_ := true;
                        /*                        debugln("binding lang direct resumed: " ++ __LOC__);*/
                        let _lang_result_ = [%e resumeExprs];
                        _lang_branch_resume_(_lang_result_);
                        ();
                      }
                  );
                };
                %e
                bindingExpr;
              };
            } else {
              [@metaloc varNameLoc]
              {
                let%expr _lang_branch_resume_ = {
                  let _lang_resumed_ = ref(false);
                  (
                    _lang_result_ =>
                      if (_lang_resumed_^) {
                        raise(Failure("binding lang branched already resumed: " ++ __LOC__));
                      } else {
                        _lang_resumed_ := true;
                        /*                        debugln("binding lang branched resumed: " ++ __LOC__);*/
                        %e
                        resumeExprs;
                        ();
                      }
                  );
                };
                %e
                bindingExpr;
              };
            };
          };
        };

      switch (List.hd(bindings)) {
      | {pvb_pat: {ppat_desc: Ppat_var({txt: varName, loc: varNameLoc})}, pvb_expr: bindingExpr} =>
        switch (bindingExpr) {
        | {pexp_desc: Pexp_constraint(bindingExpr, constraintType)} =>
          processBindingExpr(varName, varNameLoc, bindingExpr, Some(constraintType))
        | other => processBindingExpr(varName, varNameLoc, other, None)
        }
      | other =>
        /*        debugln("processLetBranch other single binding:");*/
        skipExpr(Exp.mk(Pexp_let(recFlag, bindings, this#descendantParser(~from=__LOC__, inExpr, branched))))
      };
    } else {
      /*      debugln("processLetBranch multi bindings:");*/
      skipExpr(
        Exp.mk(Pexp_let(recFlag, bindings, this#descendantParser(~from=__LOC__, inExpr, branched))),
      );
    };
  pri parseCpsApplyExp = (~from="_", branched, id, expressions, loc, resumeExprs, resumeExprsBranched, terminator) => {
    /*    debugln("ppx apply lang:");*/
    branched := branched^ + 1 + resumeExprsBranched;

    let expressions =
      expressions
      |> List.map(it => {
           let expr = snd(it);
           switch (expr) {
           | {pexp_attributes: [({txt: "lang", loc}, payload)]} => (
               fst(it),
               this#parseLangClassExpr(expr, payload, loc),
             )
           | {pexp_desc: Pexp_extension(({txt: "lang", loc}, payload))} => (
               fst(it),
               this#parseLangClassExpr(getExpr(payload, loc), payload, loc),
             )
           | other => it
           };
         })
      |> List.append(_, [("", [%expr _lang_continuation_])]);

    let applyExpr =
      Exp.attr(
        Exp.mk(Pexp_apply(Exp.ident({txt: Lident(id), loc}), expressions)),
        ({txt: "langapply", loc}, emptyPstr),
      );

    [@metaloc loc]
    {
      let%expr _lang_resumed_ = ref(false);
      let _dbg_lang_from = [%e stringToExpr(from)];
      let _lang_branch_resume_ = _lang_result_ =>
        if (_lang_resumed_^) {
          raise(Failure("apply lang branched already resumed: " ++ __LOC__));
        } else {
          _lang_resumed_ := true;
          /*          debugln("apply lang branched resumed: " ++ __LOC__);*/
          if%e (terminator) {
            try%expr ([%e leafExpr(resumeExprs, "t")]) {
            | error => _lang_branch_error_(error)
            };
          } else if (resumeExprsBranched == 0) {
            try%expr (
              {
                let _lang_result_ = [%e leafExpr(resumeExprs, "r")];
                _lang_branch_resume_(_lang_result_);
              }
            ) {
            | error => _lang_branch_error_(error)
            };
          } else {
            try%expr ([%e continuationExpr(resumeExprs)]) {
            | error =>
              _lang_branch_error_(error);
              _lang_resumed_^ ? `Continued : `Suspended;
            };
          };
          ();
        };
      let _lang_continuation_ = {
        as _;
        pub resumed = () => _lang_resumed_^;
        pub resume = _lang_branch_resume_;
        pub error = _lang_branch_error_;
        pub onDefer = _lang_continuation_#onDefer;
        pub onResume = _lang_continuation_#onResume;
        pub onError = _lang_continuation_#onError
      };
      try ([%e applyExpr]) {
      | error =>
        _lang_branch_error_(error);
        _lang_resumed_^ ? `Continued : `Suspended;
      };
    };
  };
  pri parseCpsDeferExpr = (~from="_", branched, deferExpr, loc, resumeExprs, resumeExprsBranched, terminator) => {
    /*    debugln("ppx defer lang:");*/
    branched := branched^ + 1 + resumeExprsBranched;
    let deferExpr = Exp.attr(deferExpr, ({txt: "langdefered", loc}, emptyPstr));

    [@metaloc loc]
    {
      let%expr _lang_resumed_ = ref(false);
      let _dbg_lang_from = [%e stringToExpr(from)];
      let _lang_branch_resume_ = _lang_result_ =>
        if (_lang_resumed_^) {
          raise(Failure("defer lang already resumed: " ++ __LOC__));
        } else {
          _lang_continuation_#onResume(__LOC__);
          _lang_resumed_ := true;
          /*          debugln("defer lang resumed: " ++ __LOC__);*/

          if%e (terminator) {
            try%expr ([%e leafExpr(resumeExprs, "t")]) {
            | error => _lang_branch_error_(error)
            };
          } else if (resumeExprsBranched == 0) {
            try%expr (
              {
                let _lang_result_ = [%e leafExpr(resumeExprs, "r")];
                _lang_branch_resume_(_lang_result_);
              }
            ) {
            | error => _lang_branch_error_(error)
            };
          } else {
            try%expr ([%e continuationExpr(resumeExprs)]) {
            | error =>
              _lang_branch_error_(error);
              _lang_resumed_^ ? `Continued : `Suspended;
            };
          };

          ();
        };
      let continuation = {
        as _;
        pub resumed = () => _lang_resumed_^;
        pub resume = _lang_branch_resume_;
        pub error = _lang_branch_error_
      };
      _lang_continuation_#onDefer(__LOC__);
      try (
        {
          %e
          deferExpr;
          _lang_resumed_^ ? `Continued : `Suspended;
        }
      ) {
      | error =>
        _lang_branch_error_(error);
        _lang_resumed_^ ? `Continued : `Suspended;
      };
    };
  };
  pri descendantParser = (~from="_", expr, branched) =>
    switch (expr) {
    | {pexp_attributes: [({txt: "defer", loc}, payload)]} =>
      this#parseCpsDeferExpr(
        ~from=__LOC__,
        branched,
        expr,
        loc,
        [%expr _lang_branch_resume_(_lang_result_)],
        0,
        true,
      )
    | {pexp_attributes: [({txt: "nolang", loc}, payload)]} => expr
    | {pexp_attributes: [({txt: "lang", loc}, payload)]} => this#parseLangClassExpr(expr, payload, loc)
    | {pexp_desc: Pexp_extension(({txt: "lang", loc}, payload))} =>
      this#parseLangClassExpr(getExpr(payload, loc), payload, loc)
    | {pexp_desc: Pexp_sequence(actualSequenceExpr, nextSequenceExpr)} =>
      this#processSequenceBranch(branched, actualSequenceExpr, nextSequenceExpr)
    | {pexp_desc: Pexp_let(recFlag, bindings, inExpr)} =>
      this#processLetBranch(branched, recFlag, bindings, inExpr, None)
    | {pexp_desc: Pexp_apply({pexp_desc: Pexp_ident({txt: Lident(id), loc})}, expressions)}
        when matchesCpsApply(id) =>
      this#parseCpsApplyExp(
        ~from=__LOC__,
        branched,
        id,
        expressions,
        loc,
        [%expr _lang_branch_resume_(_lang_result_)],
        0,
        true,
      )
    | {pexp_desc: Pexp_ifthenelse(ifExpr, thenExpr, elseExpr)} =>
      this#processIfthenelseBranch(branched, ifExpr, thenExpr, elseExpr, None)
    | {pexp_desc: Pexp_try(tryExpr, caseExprs)} => this#processTryBranch(branched, tryExpr, caseExprs, None)
    | {pexp_desc: Pexp_match(matchExpr, caseExprs)} => this#processMatchBranch(branched, matchExpr, caseExprs, None)
    | other =>
      switch (other) {
      | {pexp_desc: Pexp_constant(constant)} => other
      | other => skipExpr(other)
      }
    };
  pri parseLangClassExprBk = (expr, payload, loc) => {
    /*    debugln("ppx parseLangClassExpr:");*/

    let parseCpsFuncBodyExpr = (expr, loc) => {
      let branched = ref(0);
      let expr = this#descendantParser(~from=__LOC__, expr, branched);

      if (branched^ == 0) {
        [@metaloc loc]
        {
          let%expr _lang_result_ = [%e expr];
          _lang_continuation_#resume(_lang_result_);
          `Continued;
        };
      } else {
        [@metaloc loc]
        {
          let%expr _lang_resumed_ = ref(false);
          let _lang_branch_error_ = _lang_error_ =>
            if (_lang_resumed_^) {
              raise(Failure("langfun error already resumed: " ++ __LOC__));
            } else {
              _lang_resumed_ := true;
              /*              debugln("langfun error resumed: " ++ __LOC__);*/
              _lang_continuation_#error(_lang_error_);
              ();
            };
          let _lang_branch_resume_ = _lang_result_ =>
            if (_lang_resumed_^) {
              raise(Failure("langfun already resumed: " ++ __LOC__));
            } else {
              _lang_resumed_ := true;
              /*              debugln("langfun resumed: " ++ __LOC__);*/
              _lang_continuation_#resume(_lang_result_);
              ();
            };
          %e
          expr;
        };
      };
    };

    let rec buildFunExp = (bodyExp, patDescs) =>
      switch (patDescs) {
      | [] => bodyExp
      | [head, ...tail] => buildFunExp([%expr ([%p head]) => [%e bodyExp]], tail)
      };

    let rec accFunExprs = (expr, patDescs) =>
      switch (expr) {
      | {pexp_desc: Pexp_fun(label, _, patDesc, pexpDesc)} => accFunExprs(pexpDesc, [patDesc, ...patDescs])
      | other => buildFunExp([%expr _lang_continuation_ => [%e parseCpsFuncBodyExpr(other, loc)]], patDescs)
      };

    let resExpr = Exp.attr([@metaloc loc] [%expr [%e accFunExprs(expr, [])]], ({txt: "langfun", loc}, emptyPstr));
    printExpr(resExpr);
    resExpr;
  };
  /* -------------------------------------------------------------------------------------------------------------------------------- */
  pri parseLangClassExpr = (expr, payload, loc) => {
    print_endline("parseLangClassExpr");
    printExpr(expr);
    expr;
  };
  pub parseNode = (mapper, expr) =>
    switch (expr) {
    | {pexp_attributes: [({txt: "xxclass", loc}, payload)]} =>
      print_endline("parseLangClassExpr: xxclass");
      this#parseLangClassExpr(expr, payload, loc);
    | {pexp_desc: Pexp_extension(({txt: "xxclass", loc}, payload))} =>
      this#parseLangClassExpr(getExpr(payload, loc), payload, loc)
    | other =>
      print_endline("parseLangClassExpr: other");
      printExpr(expr);
      default_mapper.expr(mapper, other);
    }
};

let langMapper = argv => {
  ...default_mapper,
  /* expr: (mapper, expr) => parsers#parseNode(mapper, expr), */
  /* class_declaration: (mapper, declaration) =>
     switch (declaration) {
     | {pci_virt: virt, pci_params: params, pci_name: {txt, loc}, pci_expr: expr} =>
       print_endline("parseLangClassExpr: class_declaration " ++ txt);
       default_mapper.class_declaration(mapper, declaration);
     }, */
  structure_item: (mapper, structure_item) =>
    switch (structure_item) {
    | {pstr_desc: Pstr_class(list)} =>
      switch (List.hd(list)) {
      | {
          pci_virt: virt,
          pci_params: params,
          pci_name: {txt, loc},
          pci_expr: expr,
          pci_attributes: [({txt: "lang.class"}, payload)],
        } =>
        print_endline("class_declaration: " ++ txt);

        [%stri
          module MyMod = {
            class t = {
              pub name = "<<<<<zzzzzz>>>>";
            };
          }
        ];
      }
    | _ => default_mapper.structure_item(mapper, structure_item)
    },
};

let () = {
  print_endline("lang_ppx: started");
  register("lang_ppx", langMapper);
};

/* let rec parseAttr = list =>
   switch (list) {
   | [] => None
   | [head, ...tail] =>
     switch (head) {
     | {pexp_attributes: [({txt: "xxclass", loc}, payload)]} =>
       print_endline("parseLangClassExpr: xxclass");
       None;
     | other => None
     };

     parseAttr(tail);
   }; */