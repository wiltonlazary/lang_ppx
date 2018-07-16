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
        print_endline("class_declaration: " ++ className);
        let fieldsRef = ref([]);
        let selfRef = ref(None);

        switch (classExpr) {
        | {pcl_desc: Pcl_structure({pcstr_self: self, pcstr_fields: list})} =>
          fieldsRef := list;
          selfRef := Some(self);

          let rec procInheritance = (list, acc) =>
            switch (list) {
            | [] => acc
            | [
                {
                  pcf_desc:
                    Pcf_inherit(
                      _,
                      {pcl_desc: [@implicit_arity] Pcl_constr({txt: Lident(inheritClassName)}, [])},
                      _,
                    ),
                },
                ...tail,
              ] =>
              print_endline("inherit: " ++ inheritClassName);
              procInheritance(tail, [inheritClassName, ...acc]);
            | [head, ...tail] => procInheritance(tail, acc)
            };

          let inherites = procInheritance(list, []);
          print_endline("inherit declaration: " ++ string_of_int(List.length(inherites)));
        | _ => ()
        };

        [@metaloc classNameLoc]
        [%stri
          module M = {
            class t = {
              pub name = "<<<<<zzzzzz>>>>";
            };
          }
        ];

        mkModuleStri(
          String.capitalize(className),
          classNameLoc,
          [mkClassStri(virt, params, "t", classNameLoc, getSome(selfRef^), fieldsRef^)],
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