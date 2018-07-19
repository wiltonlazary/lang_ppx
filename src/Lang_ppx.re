[@ocaml.ppx.context {cookies: []}];
open Parsetree;
open Ast_mapper;
open Ast_helper;
open Asttypes;
open Longident;

let getSome = opt =>
  switch (opt) {
  | Some(x) => x
  | _ => raise(Failure("getSome returned: None"))
  };

let debugln = print_endline;

let fail = (~loc=?, txt) => raise(Location.Error(Location.error(~loc?, txt)));

let patternFail = (~loc=?, tag) =>
  switch (loc) {
  | None => raise(Failure(tag ++ ": pattern not implemented yet!"))
  | Some(loc) => raise(Location.Error(Location.error(~loc, tag ++ ": pattern not implemented yet!")))
  };

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
    | _ => fail(~loc, "getExpr: must contain an expression")
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

let mkTypeStri = (loc, ident, constructor, kindIdent) => {
  pstr_desc:
    Pstr_typext({
      ptyext_path: {
        txt: ident,
        loc,
      },
      ptyext_params: [],
      ptyext_constructors: [
        {
          pext_name: {
            txt: constructor,
            loc,
          },
          pext_kind:
            [@implicit_arity]
            Pext_decl(
              [
                {
                  ptyp_desc: [@implicit_arity] Ptyp_constr({txt: kindIdent, loc}, []),
                  ptyp_loc: loc,
                  ptyp_attributes: [],
                },
              ],
              None,
            ),
          pext_loc: loc,
          pext_attributes: [],
        },
      ],
      ptyext_private: Public,
      ptyext_attributes: [],
    }),
  pstr_loc: loc,
};

let mkModuleStri = (name, loc, structure) => {
  pstr_loc: loc,
  pstr_desc:
    Pstr_module({
      pmb_loc: loc,
      pmb_attributes: [],
      pmb_name: {
        txt: name,
        loc,
      },
      pmb_expr: {
        pmod_loc: loc,
        pmod_attributes: [],
        pmod_desc: Pmod_structure(structure),
      },
    }),
};

let mkClassStri = (virt, params, name, loc, construction, self, fields) => {
  let pclDesc =
    if (List.length(construction) == 0) {
      Pcl_structure({pcstr_self: self, pcstr_fields: fields});
    } else {
      let rec construct = (rest, expr) =>
        switch (rest) {
        | [] => expr
        | [head] =>
          let (p0, p1, p2) = head;
          Pcl_fun(p0, p1, p2, {pcl_desc: expr, pcl_loc: loc, pcl_attributes: []});
        | [head, ...tail] =>
          let (p0, p1, p2) = head;
          construct(tail, Pcl_fun(p0, p1, p2, {pcl_desc: expr, pcl_loc: loc, pcl_attributes: []}));
        };

      construct(construction, Pcl_structure({pcstr_self: self, pcstr_fields: fields}));
    };

  {
    pstr_desc:
      Pstr_class([
        {
          pci_virt: virt,
          pci_params: params,
          pci_name: {
            txt: name,
            loc,
          },
          pci_expr: {
            pcl_desc: pclDesc,
            pcl_loc: loc,
            pcl_attributes: [],
          },
          pci_loc: loc,
          pci_attributes: [],
        },
      ]),
    pstr_loc: loc,
  };
};

let mkMethodOverrideSimpleStri = (name, lident, loc) => {
  pcf_desc:
    [@implicit_arity]
    Pcf_method(
      {txt: name, loc},
      Public,
      Cfk_concrete(
        Override,
        {
          pexp_desc:
            Pexp_poly({pexp_desc: Pexp_ident({txt: lident, loc}), pexp_loc: loc, pexp_attributes: []}, None),
          pexp_loc: loc,
          pexp_attributes: [],
        },
      ),
    ),
  pcf_loc: loc,
  pcf_attributes: [],
};

let mkInheritLangAny = loc => {
  pcf_desc:
    [@implicit_arity]
    Pcf_inherit(
      Fresh,
      {
        pcl_desc: Pcl_constr({txt: Ldot(Ldot(Lident("Lang"), "Any"), "t"), loc}, []),
        pcl_loc: loc,
        pcl_attributes: [],
      },
      Some("super"),
    ),
  pcf_loc: loc,
  pcf_attributes: [],
};

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

let listToIdent = list => {
  let rec buildLdot = (list, sum) =>
    switch (list) {
    | [] => sum
    | [head] => Ldot(sum, head)
    | [head, ...tail] => buildLdot(tail, Ldot(sum, head))
    };

  let ident = Lident(List.hd(list));
  buildLdot(List.tl(list), ident);
};

let buildIdentExpr = (list, loc) => Exp.ident({txt: listToIdent(list), loc});

let rec identToList = (identPath, acc) =>
  switch (identPath) {
  | Lident(txt) => [txt, ...acc]
  | Ldot(path, txt) => identToList(path, [txt, ...acc])
  | _ => raise(Failure("identToList: Pattern not implemented yet!"))
  };

let langMapper = argv => {
  ...default_mapper,
  expr: (mapper, expr) =>
    switch (expr) {
    | {
        pexp_desc:
          Pexp_apply(
            {pexp_desc: Pexp_send(p0, "is"), pexp_loc: applyLoc, pexp_attributes: applyAttributes},
            expressions,
          ),
        pexp_loc: exprLoc,
        pexp_attributes: expAttributes,
      } =>
      switch (List.hd(expressions) |> snd) {
      | {
          pexp_desc: Pexp_ident({txt: classTypeIdent, loc: identLoc}),
          pexp_loc: identExprLoc,
          pexp_attributes: identExprAttributes,
        } as _classTypeIdentExpr =>
        let classTypeIdentPath = identToList(classTypeIdent, []);
        let moduleTypeIdent = listToIdent((classTypeIdentPath |> List.rev |> List.tl |> List.rev) @ ["classType"]);

        let identExpr = {
          pexp_desc: Pexp_ident({txt: moduleTypeIdent, loc: identLoc}),
          pexp_loc: identExprLoc,
          pexp_attributes: identExprAttributes,
        };

        let expr =
          Exp.mk(
            ~loc=exprLoc,
            ~attrs=expAttributes,
            Pexp_apply(
              {pexp_desc: Pexp_send(p0, "is"), pexp_loc: applyLoc, pexp_attributes: applyAttributes},
              [("", identExpr), ...List.tl(expressions)],
            ),
          );

        default_mapper.expr(mapper, expr);
      | other => patternFail(~exprLoc, "@lang.class check any#is")
      }
    | {
        pexp_desc:
          Pexp_apply(
            {pexp_desc: Pexp_send(p0, "cast"), pexp_loc: applyLoc, pexp_attributes: applyAttributes},
            expressions,
          ),
        pexp_loc: exprLoc,
        pexp_attributes: expAttributes,
      } =>
      switch (List.hd(expressions) |> snd) {
      | {
          pexp_desc: Pexp_ident({txt: classTypeIdent, loc: identLoc}),
          pexp_loc: identExprLoc,
          pexp_attributes: identExprAttributes,
        } as classTypeIdentExpr =>
        let classTypeIdentPath = identToList(classTypeIdent, []);
        let moduleTypeIdent = listToIdent((classTypeIdentPath |> List.rev |> List.tl |> List.rev) @ ["classType"]);

        let identExpr = {
          pexp_desc: Pexp_ident({txt: moduleTypeIdent, loc: identLoc}),
          pexp_loc: identExprLoc,
          pexp_attributes: identExprAttributes,
        };

        let checkExpr =
          Exp.mk(
            ~loc=exprLoc,
            ~attrs=expAttributes,
            Pexp_apply(
              {pexp_desc: Pexp_send(p0, "check"), pexp_loc: applyLoc, pexp_attributes: applyAttributes},
              [("", identExpr)],
            ),
          );

        let letExpr =
          mkLetExpr(
            Nonrecursive,
            "it",
            exprLoc,
            [%expr Lang.identity([%e p0])],
            Some({
              ptyp_desc: Ptyp_constr({txt: classTypeIdent, loc: identLoc}, []),
              ptyp_loc: identLoc,
              ptyp_attributes: [],
            }),
            [%expr it],
          );

        [@metaloc exprLoc]
        (
          if%expr ([%e checkExpr]) {
            %e
            letExpr;
          } else {
            raise(
              Failure(
                [%e stringToExpr("@lang.class cast failed: " ++ String.concat(".", classTypeIdentPath))]
                ++ " | "
                ++ __LOC__,
              ),
            );
          }
        );
      | other => patternFail(~loc=exprLoc, "@lang.class check any#cast")
      }
    | other => default_mapper.expr(mapper, other)
    },
  structure_item: (mapper, structure_item) =>
    switch (structure_item) {
    | {pstr_desc: Pstr_class(list)} =>
      switch (List.hd(list)) {
      | {
          pci_virt: virt,
          pci_params: params,
          pci_name: {txt: classNameStr, loc: nameLoc},
          pci_expr: classExpr,
          pci_attributes: [({txt: "lang.class"}, payload)],
        } as _classDeclaration =>
        String.(
          if (classNameStr
              |> length < 2
              || classNameStr.[0] != '_'
              || classNameStr.[1] != (classNameStr.[1] |> Char.uppercase)) {
            raise(
              fail(
                ~loc=nameLoc,
                "@lang.class: class name must have length >= 2 and start with underscore _ followed by uppercase char. EX:\nclass _MyClass = {};",
              ),
            );
          }
        );

        let classNameStr =
          classNameStr.[0] == '_' ? String.sub(classNameStr, 1, String.length(classNameStr) - 1) : classNameStr;
        print_endline("class_declaration: " ++ classNameStr);

        let rec procInheritance = (list, acc) =>
          switch (list) {
          | [] => acc
          | [
              {
                pcf_desc:
                  Pcf_inherit(
                    _,
                    {
                      pcl_desc:
                        Pcl_constr({txt: identPath}, []) |
                        Pcl_apply({pcl_desc: Pcl_constr({txt: identPath}, [])}, _),
                    },
                    _,
                  ),
              },
              ...tail,
            ] =>
            let identPaths = identToList(identPath, []);
            let inheritClass = String.concat(".", identPaths);
            print_endline("inherit: " ++ inheritClass);
            procInheritance(tail, [identPaths, ...acc]);
          | [head, ...tail] => procInheritance(tail, acc)
          };

        let rec procStructure = (expr, acc) =>
          switch (expr) {
          | {pcl_desc: Pcl_structure({pcstr_self: self, pcstr_fields: list})} => (
              acc,
              self,
              list,
              procInheritance(list, []),
            )
          | {pcl_desc: Pcl_fun(p0, p1, p2, expr)} => procStructure(expr, [(p0, p1, p2), ...acc])
          | _ => patternFail(~loc=nameLoc, "procStructure")
          };

        let (classConstruction, classSelf, classFields, classInheritance) = procStructure(classExpr, []);

        let (classInheritance, implicitInheritanceFields) =
          if (classInheritance |> List.length == 0) {
            ([["Lang", "AnyClass", "t"]], [mkInheritLangAny(nameLoc)]);
          } else {
            (classInheritance, []);
          };

        let inheritanceAdd =
          classInheritance
          |> List.map(it => {
               let classTypePath = (it |> List.rev |> List.tl |> List.rev) @ ["Type"];
               let inheritanceIdent = buildIdentExpr(classTypePath @ ["classInheritance"], nameLoc);

               %str
               Hashtbl.iter((k, v) => Hashtbl.add(classInheritance, k, v), [%e inheritanceIdent]);
             })
          |> List.flatten;

        let inheritanceClassFields = [
          mkMethodOverrideSimpleStri("classInheritance", listToIdent(["classInheritance"]), nameLoc),
          mkMethodOverrideSimpleStri("classId", listToIdent(["classId"]), nameLoc),
          mkMethodOverrideSimpleStri("className", listToIdent(["className"]), nameLoc),
        ];

        let beginPart =
          [@metaloc nameLoc]
          [%str
            type variant = Lang.AnyClass.Type.variant = ..;
            let classId = [%e stringToExpr(classNameStr ++ " | " ++ UUID.makeV4() ++ " | ")] ++ __LOC__;
            let className = [%e stringToExpr(classNameStr)];
            let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
            Hashtbl.add(classInheritance, classId, className)
          ];

        let moduleName = String.capitalize(classNameStr) ++ "Class";
        let variantConstructorName = moduleName ++ "Variant";

        let variantTypeAddPart = [
          mkTypeStri(
            nameLoc,
            listToIdent(["Lang", "AnyClass", "Type", "variant"]),
            variantConstructorName,
            listToIdent(["t"]),
          ),
        ];

        let classDeclItem = [
          mkClassStri(
            virt,
            params,
            "t",
            nameLoc,
            classConstruction,
            classSelf,
            implicitInheritanceFields @ classFields @ inheritanceClassFields,
          ),
        ];

        let classTypePart = [
          mkModuleStri(
            "Type",
            nameLoc,
            List.concat([beginPart, inheritanceAdd, classDeclItem, variantTypeAddPart]),
          ),
        ];

        let classBindPart =
          [@metaloc nameLoc]
          [%str
            let classType: (module Lang.AnyClassType) = (module Type);
            class t = class Type.t
          ];

        let structure_item = mkModuleStri(moduleName, nameLoc, List.concat([classTypePart, classBindPart]));
        default_mapper.structure_item(mapper, structure_item);
      | _ => default_mapper.structure_item(mapper, structure_item)
      }
    | _ => default_mapper.structure_item(mapper, structure_item)
    },
};

let () = {
  print_endline("lang_ppx: started");
  register("lang_ppx", langMapper);
};