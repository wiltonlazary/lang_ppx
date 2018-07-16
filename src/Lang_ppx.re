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

let buildLongident = list => {
  let rec buildLdot = (list, sum) =>
    switch (list) {
    | [] => sum
    | [head] => Ldot(sum, head)
    | [head, ...tail] => buildLdot(tail, Ldot(sum, head))
    };

  let ident = Lident(List.hd(list));
  buildLdot(List.tl(list), ident);
};

let buildIdentExpr = (list, loc) => Exp.ident({txt: buildLongident(list), loc});

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

let rec identPathToList = (identPath, acc) =>
  switch (identPath) {
  | Lident(txt) => [txt, ...acc]
  | Ldot(path, txt) => identPathToList(path, [txt, ...acc])
  | _ => raise(Failure("Pattern not implemented yet!"))
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
          pci_name: {txt: name, loc: nameLoc},
          pci_expr: classExpr,
          pci_attributes: [({txt: "lang.class"}, payload)],
        } as _classDeclaration =>
        String.(
          if (name |> length < 2 || name.[0] != '_' || name.[1] != (name.[1] |> Char.uppercase)) {
            raise(
              fail(
                nameLoc,
                "@lang.class: class name must have length >= 2 and start with underscore _ followed by uppercase char. EX:\nclass _MyClass = {};",
              ),
            );
          }
        );

        print_endline("class_declaration: " ++ name);
        let fieldsRef = ref([]);
        let selfRef = ref(None);

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

        let inheritances =
          switch (classExpr) {
          | {pcl_desc: Pcl_structure({pcstr_self: self, pcstr_fields: list})} =>
            fieldsRef := list;
            selfRef := Some(self);
            procInheritance(list, []);
          |{pcl_desc:(Pcl_constr (_, _)|Pcl_fun (_, _, _, _)|Pcl_apply (_, _)|
            Pcl_let (_, _, _)|Pcl_constraint (_, _)|Pcl_extension _)} =>
           
          };

        let name = name.[0] == '_' ? String.sub(name, 1, String.length(name) - 1) : name;

        let (inheritances, implicitInheritanceFields) =
          if (inheritances |> List.length == 0) {
            let res = [mkInheritLangAny(nameLoc)];
            ([["Lang", "Any", "t"]], res);
          } else {
            (inheritances, []);
          };

        let inheritanceAdd =
          inheritances
          |> List.map(it => {
               let classTypePath = (it |> List.rev |> List.tl |> List.rev) @ ["ClassType"];
               let inheritanceIdent = buildIdentExpr(classTypePath @ ["inheritance"], nameLoc);

               %str
               Hashtbl.iter((k, v) => Hashtbl.add(ClassType.inheritance, k, v), [%e inheritanceIdent]);
             })
          |> List.flatten;

        let inheritanceClassFields = [
          mkMethodOverrideSimpleStri("classInheritance", buildLongident(["inheritance"]), nameLoc),
          mkMethodOverrideSimpleStri("classId", buildLongident(["id"]), nameLoc),
          mkMethodOverrideSimpleStri("className", buildLongident(["name"]), nameLoc),
        ];

        let beginPart =
          [@metaloc nameLoc]
          [%str
            let id = __LOC__;
            let name = [%e stringToExpr(name)];
            let inheritance: Hashtbl.t(string, string) = Hashtbl.create(10);
            Hashtbl.add(inheritance, id, name)
          ];

        let classDeclItem = [
          mkClassStri(
            virt,
            params,
            "t",
            nameLoc,
            getSome(selfRef^),
            implicitInheritanceFields @ fieldsRef^ @ inheritanceClassFields,
          ),
        ];

        let classTypePart = [mkModuleStri("ClassType", nameLoc, List.concat([beginPart, classDeclItem]))];

        let endPart =
          [@metaloc nameLoc]
          [%str
            let classType: (module Lang.AnyClassType) = (module ClassType);
            class t = class ClassType.t
          ];

        mkModuleStri(String.capitalize(name), nameLoc, List.concat([classTypePart, inheritanceAdd, endPart]));
      | _ => default_mapper.structure_item(mapper, structure_item)
      }
    | _ => default_mapper.structure_item(mapper, structure_item)
    },
};

let () = {
  print_endline("lang_ppx: started");
  register("lang_ppx", langMapper);
};