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

let mkClassStri = (virt, params, name, loc, self, fields) => {
  pstr_desc:
    Pstr_class([
      {
        pci_virt: virt,
        pci_params: [],
        pci_name: {
          txt: name,
          loc,
        },
        pci_expr: {
          pcl_desc: Pcl_structure({pcstr_self: self, pcstr_fields: fields}),
          pcl_loc: loc,
          pcl_attributes: [],
        },
        pci_loc: loc,
        pci_attributes: [],
      },
    ]),
  pstr_loc: loc,
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

let rec identPathToList = (identPath, acc) =>
  switch (identPath) {
  | Lident(txt) => [txt, ...acc]
  | Ldot(path, txt) => identPathToList(path, [txt, ...acc])
  | _ => raise(Failure("Pattern not implementd yet!"))
  };

let langMapper = argv => {
  ...default_mapper,
  structure_item: (mapper, structure_item) =>
    switch (structure_item) {
    | {pstr_desc: Pstr_class(list)} =>
      switch (List.hd(list)) {
      | {
          pci_virt: virt,
          pci_params: params,
          pci_name: {txt: className, loc: classNameLoc},
          pci_expr: classExpr,
          pci_attributes: [({txt: "lang.class"}, payload)],
        } as classDeclaration =>
        String.(
          if (className |> length < 2 || className.[0] != '_' || className.[1] != (className.[1] |> Char.uppercase)) {
            raise(
              fail(
                classNameLoc,
                "@lang.class: class name must have length >= 2 and start with underscore _ followed by uppercase char. EX:\nclass _MyClass = {};",
              ),
            );
          }
        );

        print_endline("class_declaration: " ++ className);
        let fieldsRef = ref([]);
        let selfRef = ref(None);

        let inheritances =
          switch (classExpr) {
          | {pcl_desc: Pcl_structure({pcstr_self: self, pcstr_fields: list})} =>
            fieldsRef := list;
            selfRef := Some(self);

            let rec procInheritance = (list, acc) =>
              switch (list) {
              | [] => acc
              | [{pcf_desc: Pcf_inherit(_, {pcl_desc: Pcl_constr({txt: identPath}, [])}, _)}, ...tail] =>
                let identPaths = identPathToList(identPath, []);
                let inheritClass = String.concat(".", identPaths);
                print_endline("inherit: " ++ inheritClass);
                procInheritance(tail, [identPaths, ...acc]);
              | [head, ...tail] => procInheritance(tail, acc)
              };

            procInheritance(list, []);
          | _ => []
          };

        let className = className.[0] == '_' ? String.sub(className, 1, String.length(className) - 1) : className;

        let buildIdentPath = list => {
          let rec buildLdot = (list, sum) =>
            switch (list) {
            | [] => sum
            | [head] => Ldot(sum, head)
            | [head, ...tail] => buildLdot(tail, Ldot(sum, head))
            };

          let ident = Lident(List.hd(list));
          buildLdot(List.tl(list), ident);
        };

        let beginPart =
          [@metaloc classNameLoc]
          [%str
            let classId = __LOC__;
            let className = __MODULE__;
            let classInheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
            Hashtbl.add(classInheritance, classId, className)
          ];

        let classInheritanceAdd =
          inheritances
          |> List.map(it => {
               let modulePath = it |> List.rev |> List.tl |> List.rev;
               let classInheritanceIdent =
                 Exp.ident({txt: buildIdentPath(modulePath @ ["classInheritance"]), loc: classNameLoc});
               let classIdIdent = Exp.ident({txt: buildIdentPath(modulePath @ ["classId"]), loc: classNameLoc});
               let classNameIdent = Exp.ident({txt: buildIdentPath(modulePath @ ["className"]), loc: classNameLoc});
               [%str
                 Hashtbl.iter((k, v) => Hashtbl.add(classInheritance, k, v), [%e classInheritanceIdent]);
                 Hashtbl.add(classInheritance, [%e classIdIdent], [%e classNameIdent])
               ];
             })
          |> List.flatten;

        let endPart = [mkClassStri(virt, params, "t", classNameLoc, getSome(selfRef^), fieldsRef^)];

        mkModuleStri(
          String.capitalize(className),
          classNameLoc,
          List.concat([beginPart, classInheritanceAdd, endPart]),
        );
      | _ => default_mapper.structure_item(mapper, structure_item)
      }
    | _ => default_mapper.structure_item(mapper, structure_item)
    },
};

let () = {
  print_endline("lang_ppx: started");
  register("lang_ppx", langMapper);
};