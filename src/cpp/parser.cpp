
#pragma once

#include "utils.cpp"
#include "ast.cpp"
#include "parser.c"

ast parse_file(const char* path);
string_list included_files;

void* gram_rule_elt_n0(clist_voidptr l) {
    if (l.len() > 0) {
        return l.ith(0);
    }
    return nullptr;
}
void* gram_rule_elt_n1(clist_voidptr l) {
    if (l.len() > 1) {
        return l.ith(1);
    }
    return nullptr;
}
void* gram_rule_elt_n2(clist_voidptr l) {
    if (l.len() > 2) {
        return l.ith(2);
    }
    return nullptr;
}
void* gram_rule_binop(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Binop;
    ret->dat.binop_dat.op = ((token*)l.ith(1))->dat.Binop_dat.op;
    ret->dat.binop_dat.v1 = (expr*)l.ith(0);
    ret->dat.binop_dat.v2 = (expr*)l.ith(2);
    return ret;
}
void* gram_rule_unop(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Unop;
    ret->dat.unop_dat.op = ((token*)l.ith(0))->dat.Unop_dat.op;
    ret->dat.unop_dat.v = (expr*)l.ith(1);
    return ret;
}
void* gram_rule_neg(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Unop;
    ret->dat.unop_dat.op.kind = unop::Neg;
    ret->dat.unop_dat.v = (expr*)l.ith(1);
    return ret;
}
void* gram_rule_dot(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Field;
    ret->dat.field_dat.stru = (expr*)l.ith(0);
    ret->dat.field_dat.field = ((token*)l.ith(2))->dat.Ident_dat.str;
    return ret;
}
void* gram_rule_arrow(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Arrow;
    ret->dat.arrow_dat.stru = (expr*)l.ith(0);
    ret->dat.arrow_dat.field = ((token*)l.ith(2))->dat.Ident_dat.str;
    return ret;
}
void* gram_rule_deref(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Unop;
    ret->dat.unop_dat.op.kind = unop::Deref;
    ret->dat.unop_dat.v = (expr*)l.ith(1);
    return ret;
}
void* gram_rule_addr(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Unop;
    ret->dat.unop_dat.op.kind = unop::Addr;
    ret->dat.unop_dat.v = (expr*)l.ith(1);
    return ret;
}
void* gram_rule_int(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Int;
    ret->dat.int_dat = ((token*)l.ith(0))->dat.VInt_dat.i;
    return ret;
}
void* gram_rule_string(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::String;
    ret->dat.string_dat = ((token*)l.ith(0))->dat.VString_dat.str;
    return ret;
}
void* gram_rule_var(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Var;
    ret->dat.var_dat = ((token*)l.ith(0))->dat.Ident_dat.str;
    return ret;
}
void* gram_rule_array(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Index;
    ret->dat.ind_dat.arr = (expr*)l.ith(0);
    ret->dat.ind_dat.ind = (expr*)l.ith(2);
    return ret;
}
void* gram_rule_func(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Fcall;
    ret->dat.fcall_dat.func = (expr*)l.ith(0);
    ret->dat.fcall_dat.args = (clist_voidptr*)l.ith(2);

    return ret;
}
void* gram_rule_list_push_2nd(clist_voidptr l) {
    clist_voidptr* ret = (clist_voidptr*)l.ith(2);
    ret->push(l.ith(0));
    return l.ith(2);
}
void* gram_rule_strlist_push(clist_voidptr l) {
    string_list* ret = (string_list*)l.ith(2);
    ret->push(((token*)l.ith(0))->dat.VString_dat.str);
    return ret;
}
void* gram_rule_strlist_base(clist_voidptr l) {
    string_list* ret = (string_list*)malloc(sizeof(string_list));
    ret->init();
    ret->push(((token*)l.ith(0))->dat.VString_dat.str);
    return ret;
}
void* gram_rule_list_push_1st(clist_voidptr l) {
    clist_voidptr* ret = (clist_voidptr*)l.ith(1);
    ret->push(l.ith(0));
    return l.ith(1);
}
void* gram_rule_list_base(clist_voidptr l) {
    clist_voidptr* ret = (clist_voidptr*)malloc(sizeof(clist_voidptr));
    ret->init();
    ret->append(l.ith(0));
    return ret;
}
void* gram_rule_list_empty(clist_voidptr l) {
    clist_voidptr* ret = (clist_voidptr*)malloc(sizeof(clist_voidptr));
    ret->init();
    return ret;
}
void* gram_rule_typecast(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Typecast;
    ret->dat.typecast_dat.v = (expr*)l.ith(0);
    ret->dat.typecast_dat.t = (typ*)l.ith(2);
    return ret;
}
void* gram_rule_lambda(clist_voidptr l) {
    // expr* ret = (expr*)malloc(sizeof(expr));
    // ret->kind = expr::Typecast;
    // ret->dat.typecast_dat.v = (expr*)l.ith(0);
    // ret->dat.typecast_dat.t = (typ*)l.ith(2);
    return nullptr;
}
void* gram_rule_constr0(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Constr;
    ret->dat.constr_dat.t = (typ*)l.ith(1);
    ret->dat.constr_dat.constr = ((token*)l.ith(2))->dat.Ident_dat.str;
    ret->dat.constr_dat.args.init();
    return ret;
}
void* gram_rule_constr(clist_voidptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Constr;
    ret->dat.constr_dat.t = (typ*)l.ith(1);
    ret->dat.constr_dat.constr = ((token*)l.ith(2))->dat.Ident_dat.str;
    ret->dat.constr_dat.args = *(string_list*)l.ith(4);
    free(l.ith(4));
    return ret;
}
void* gram_rule_typ_base(clist_voidptr l) {
    typ* ret = (typ*)malloc(sizeof(typ));
    token n = *(token*)l.ith(0);
    if (n.kind == token::TVoid) {
        ret->kind = typ::TVoid;
    } else if (n.kind == token::TInt) {
        ret->kind = typ::TInt;
    } else if (n.kind == token::TChar) {
        ret->kind = typ::TChar;
    } else if (n.kind == token::TBool) {
        ret->kind = typ::TBool;
    } else if (n.kind == token::Ident) {
        ret->kind = typ::TIdent;
        ret->dat.TIdent_dat = n.dat.Ident_dat.str;
    } else {
        printf("impossible token kind\n");
        exit(-1);
    }
    return ret;
}
void* gram_rule_typ_ptr(clist_voidptr l) {
    typ* ret = (typ*)malloc(sizeof(typ));
    ret->kind = typ::TPtr;
    ret->dat.ptr_dat = (typ*)l.ith(0);
    return ret;
}
void* gram_rule_typ_fptr(clist_voidptr l) {
    typ* ret = (typ*)malloc(sizeof(typ));
    ret->kind = typ::Tfunptr;
    ret->dat.tfunptr_dat.ret_t = (typ*)l.ith(2);
    ret->dat.tfunptr_dat.args_t.init();
    ret->dat.tfunptr_dat.args_t.push((typ*)l.ith(0));
    return ret;
}
void* gram_rule_typ_cst(clist_voidptr l) {
    typ* ret = (typ*)malloc(sizeof(typ));
    ret->kind = typ::TConst;
    ret->dat.const_dat = (typ*)l.ith(1);
    return ret;
}
void* gram_rule_typ_cstpar(clist_voidptr l) {
    typ* ret = (typ*)malloc(sizeof(typ));
    ret->kind = typ::TConst;
    ret->dat.const_dat = (typ*)l.ith(2);
    return ret;
}
void* gram_rule_typeof(clist_voidptr l) {
    typ* ret = (typ*)malloc(sizeof(typ));
    ret->kind = typ::Typeof;
    ret->dat.typeof_dat = (expr*)l.ith(2);
    return ret;
}
void* gram_rule_instr_decl(clist_voidptr l) {
    instr* ret = (instr*)malloc(sizeof(instr));
    ret->kind = instr::Decl;
    ret->dat.decl_dat.d = (decl*)l.ith(0);
    return ret;
}
void* gram_rule_instr_assign(clist_voidptr l) {
    instr* ret = (instr*)malloc(sizeof(instr));
    ret->kind = instr::Set;
    ret->dat.set_dat.l = (expr*)l.ith(0);
    ret->dat.set_dat.r = (expr*)l.ith(2);
    return ret;
}
void* gram_rule_instr_ret_smth(clist_voidptr l) {
    instr* ret = (instr*)malloc(sizeof(instr));
    ret->kind = instr::Return;
    ret->dat.ret_dat.v = (expr*)l.ith(1);
    return ret;
}
void* gram_rule_instr_ret_no(clist_voidptr l) {
    instr* ret = (instr*)malloc(sizeof(instr));
    ret->kind = instr::Return;
    ret->dat.ret_dat.v = nullptr;
    return ret;
}
void* gram_rule_instr_fcall(clist_voidptr l) {
    instr* ret = (instr*)malloc(sizeof(instr));
    ret->kind = instr::Fcall;
    ret->dat.fcall_dat.call = (expr*)l.ith(0);
    return ret;
}
void* gram_rule_instr_while(clist_voidptr l) {
    instr* ret = (instr*)malloc(sizeof(instr));
    ret->kind = instr::While;
    ret->dat.while_dat.b = (expr*)l.ith(1);
    ret->dat.while_dat.instrs = *(clist_voidptr*)l.ith(3);
    free(l.ith(3));
    return ret;
}
void* gram_rule_instr_if(clist_voidptr l) {
    instr* ret = (instr*)malloc(sizeof(instr));
    ret->kind = instr::If;
    ret->dat.if_dat.b = (expr*)l.ith(1);
    ret->dat.if_dat.truebrc = *(clist_voidptr*)l.ith(3);
    free(l.ith(3));
    ret->dat.if_dat.falsebrc = *(clist_voidptr*)l.ith(5);
    free(l.ith(5));
    return ret;
}
void* gram_rule_instr_elif(clist_voidptr l) {
    instr* instr_ret = (instr*)malloc(sizeof(instr));
    instr_ret->kind = instr::If;
    instr_ret->dat.if_dat.b = (expr*)l.ith(1);
    instr_ret->dat.if_dat.truebrc = *(clist_voidptr*)l.ith(3);
    free(l.ith(3));
    instr_ret->dat.if_dat.falsebrc = *(clist_voidptr*)l.ith(5);
    free(l.ith(5));

    clist_voidptr* ret = (clist_voidptr*)malloc(sizeof(clist_voidptr));
    ret->init();
    ret->push(instr_ret);
    return ret;
}
void* gram_rule_instr_match(clist_voidptr l) {
    instr* ret = (instr*)malloc(sizeof(instr));
    ret->kind = instr::Match;
    ret->dat.match_dat.e = (expr*)l.ith(1);
    ret->dat.match_dat.t = (typ*)l.ith(3);
    ret->dat.match_dat.branches = *(clist_voidptr*)l.ith(5);
    free(l.ith(5));
    return ret;
}
void* gram_rule_instr_match_tl(clist_voidptr l) {
    instr::match_branch* brch = (instr::match_branch*)malloc(sizeof(instr::match_branch));
    brch->fields.init();
    brch->matched_symb = ((token*)l.ith(1))->dat.Ident_dat.str;
    brch->instrs = *(clist_voidptr*)l.ith(4);
    free(l.ith(4));

    ((clist_voidptr*)l.ith(6))->push(brch);
    return l.ith(6);
}
void* gram_rule_instr_match_tl2(clist_voidptr l) {
    instr::match_branch* brch = (instr::match_branch*)malloc(sizeof(instr::match_branch));
    brch->matched_symb = ((token*)l.ith(1))->dat.Ident_dat.str;
    brch->fields = *(string_list*)l.ith(3);
    free(l.ith(3));
    brch->instrs = *(clist_voidptr*)l.ith(7);
    free(l.ith(7));

    ((clist_voidptr*)l.ith(9))->push(brch);
    return l.ith(9);
}
void* gram_rule_vardecl(clist_voidptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Var;
    ret->dat.var_dat.name = ((token*)l.ith(1))->dat.Ident_dat.str;
    ret->dat.var_dat.t = (typ*)l.ith(0);
    ret->dat.var_dat.v = nullptr;
    return ret;
}
void* gram_rule_vardecl_vlue(clist_voidptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Var;
    ret->dat.var_dat.name = ((token*)l.ith(1))->dat.Ident_dat.str;
    ret->dat.var_dat.t = (typ*)l.ith(0);
    ret->dat.var_dat.v = (expr*)l.ith(3);
    return ret;
}
void* gram_rule_funcdecl(clist_voidptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Func;
    ret->dat.func_dat.name = ((token*)l.ith(2))->dat.Ident_dat.str;
    ret->dat.func_dat.ret_t = (typ*)l.ith(1);
    ret->dat.func_dat.args_decls = *(clist_voidptr*)l.ith(4);
    free((clist_voidptr*)l.ith(4));
    ret->dat.func_dat.instrs = (clist_voidptr*)l.ith(7);
    return ret;
}
void* gram_rule_funcprot(clist_voidptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Func;
    ret->dat.func_dat.name = ((token*)l.ith(2))->dat.Ident_dat.str;
    ret->dat.func_dat.ret_t = (typ*)l.ith(1);
    ret->dat.func_dat.args_decls = *(clist_voidptr*)l.ith(4);
    free((clist_voidptr*)l.ith(4));
    ret->dat.func_dat.instrs = nullptr;
    return ret;
}
void* gram_rule_type(clist_voidptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Type;
    ret->dat.type_dat.name = ((token*)l.ith(1))->dat.Ident_dat.str;
    clist_voidptr* tmp = (clist_voidptr*)l.ith(3);
    ret->dat.type_dat.constrs = tmp[0];
    ret->dat.type_dat.other_decls = tmp[1];
    if (!ret->dat.type_dat.constrs.len()) {
        decl::type_constr* unit = (decl::type_constr*)malloc(sizeof(decl::type_constr));
        unit->fields.init();
        unit->name = "_";
        ret->dat.type_dat.constrs.push(unit);
    }
    return ret;
}
void* gram_rule_type_templ(clist_voidptr l) {
    decl* tdecl = (decl*)malloc(sizeof(decl));
    tdecl->kind = decl::Type;
    tdecl->dat.type_dat.name = ((token*)l.ith(4))->dat.Ident_dat.str;
    clist_voidptr* tmp = (clist_voidptr*)l.ith(6);
    tdecl->dat.type_dat.constrs = tmp[0];
    tdecl->dat.type_dat.other_decls = tmp[1];
    if (!tdecl->dat.type_dat.constrs.len()) {
        decl::type_constr* unit = (decl::type_constr*)malloc(sizeof(decl::type_constr));
        unit->fields.init();
        unit->name = "_";
        tdecl->dat.type_dat.constrs.push(unit);
    }
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Templated;
    ret->dat.templated_dat.d = tdecl;
    ret->dat.templated_dat.name = tdecl->dat.type_dat.name;
    ret->dat.templated_dat.param_names = *(string_list*)l.ith(2);
    free(l.ith(2));
    return ret;
}
void* gram_rule_specialize(clist_voidptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Specialize;
    ret->dat.specialize_dat.params = *(clist_voidptr*)l.ith(3);
    ret->dat.specialize_dat.templated_t = ((token*)l.ith(1))->dat.VString_dat.str;
    ret->dat.specialize_dat.newname = ((token*)l.ith(6))->dat.VString_dat.str;
    free((clist_voidptr*)l.ith(3));
    return ret;
}
void* gram_rule_locdecl_empty(clist_voidptr l) {
    clist_voidptr* ret = (clist_voidptr*)malloc(2*sizeof(clist_voidptr));
    ret[0].init();
    ret[1].init();
    return ret;
}
void* gram_rule_locdecl_decl(clist_voidptr l) {
    clist_voidptr* tmp = (clist_voidptr*)l.ith(1);
    tmp[1].push((decl*)l.ith(0));
    return l.ith(1);
}
void* gram_rule_decl_static(clist_voidptr l) {
    decl* d = (decl*)malloc(sizeof(decl));
    d->kind = decl::Static;
    d->dat.static_dat.d = (decl*)l.ith(1);
    clist_voidptr* tmp = (clist_voidptr*)l.ith(2);
    tmp[1].push(d);
    return l.ith(2);
}
void* gram_rule_locdecl_enum(clist_voidptr l) {
    decl::type_constr* cstr = (decl::type_constr*)malloc(sizeof(decl::type_constr));
    cstr->fields.init();
    cstr->name = ((token*)l.ith(0))->dat.Ident_dat.str;
    clist_voidptr* tmp = (clist_voidptr*)l.ith(2);
    tmp[0].push(cstr);
    return l.ith(2);
}
void* gram_rule_locdecl_cstr(clist_voidptr l) {
    decl::type_constr* cstr = (decl::type_constr*)malloc(sizeof(decl::type_constr));
    cstr->fields = *(clist_voidptr*)l.ith(2);
    free(l.ith(2));
    cstr->name = ((token*)l.ith(0))->dat.Ident_dat.str;
    clist_voidptr* tmp = (clist_voidptr*)l.ith(5);
    tmp[0].push(cstr);
    return l.ith(5);
}
void* gram_rule_include_c(clist_voidptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Include_C;
    ret->dat.include_dat.file = ((token*)l.ith(2))->dat.VString_dat.str;
    return ret;
}
void* gram_rule_include(clist_voidptr l) {
    clist_voidptr* prog = (clist_voidptr*)l.ith(3);
    const char* path = ((token*)l.ith(2))->dat.VString_dat.str;
    if (string_list_find(included_files, path) < 0) {
        included_files.push(path);
        ast included_ast = parse_file(path);
        included_ast.decls.fuse(*prog);
        *prog = included_ast.decls;
    }
    return l.ith(3);
}


string_list nonterm_symbs;
gram_rule_t::parsing_table prog_table;

gram_rule_t::gram_rules make_rules() {
    nonterm_symbs.init();
    gram_rule_t::gram_rules ret;
    ret.init();

    ret.append( make_rule("$ExprAtom   -> @ident"                , gram_rule_var           , &nonterm_symbs) );
    ret.append( make_rule("$ExprAtom   -> ( $Expr )"             , gram_rule_elt_n1        , &nonterm_symbs) );
    ret.append( make_rule("$ExprAtom   -> @0"                    , gram_rule_int           , &nonterm_symbs) );
    ret.append( make_rule("$ExprAtom   -> @\"string\""           , gram_rule_string        , &nonterm_symbs) );

    ret.append( make_rule("$ExprStru   -> $ExprAtom"             , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$ExprStru   -> $ExprStru . @ident"    , gram_rule_dot           , &nonterm_symbs) );
    ret.append( make_rule("$ExprStru   -> $ExprStru -> @ident"   , gram_rule_arrow         , &nonterm_symbs) );
    ret.append( make_rule("$ExprStru   -> $ExprStru [ $Expr ]"   , gram_rule_array         , &nonterm_symbs) );
    ret.append( make_rule("$ExprStru   -> $ExprStru ( $Arglist )", gram_rule_func          , &nonterm_symbs) );

    ret.append( make_rule("$ExprUnary  -> $ExprStru"             , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$ExprUnary  -> @! $ExprUnary"         , gram_rule_unop          , &nonterm_symbs) );
    ret.append( make_rule("$ExprUnary  -> -  $ExprUnary"         , gram_rule_neg           , &nonterm_symbs) );
    ret.append( make_rule("$ExprUnary  -> & $ExprUnary"          , gram_rule_addr          , &nonterm_symbs) );
    ret.append( make_rule("$ExprUnary  -> * $ExprUnary"          , gram_rule_deref         , &nonterm_symbs) );

    ret.append( make_rule("$ExprMul    -> $ExprUnary"            , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$ExprMul    -> $ExprMul * $ExprUnary" , gram_rule_binop         , &nonterm_symbs) );
    ret.append( make_rule("$ExprMul    -> $ExprMul / $ExprUnary" , gram_rule_binop         , &nonterm_symbs) );

    ret.append( make_rule("$ExprAdd    -> $ExprMul"              , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$ExprAdd    -> $ExprAdd + $ExprMul"   , gram_rule_binop         , &nonterm_symbs) );
    ret.append( make_rule("$ExprAdd    -> $ExprAdd - $ExprMul"   , gram_rule_binop         , &nonterm_symbs) );

    // Comparisons cannot be chained without parentheses
    ret.append( make_rule("$ExprCmp    -> $ExprAdd"              , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$ExprCmp    -> $ExprAdd < $ExprAdd"   , gram_rule_binop         , &nonterm_symbs) );
    ret.append( make_rule("$ExprCmp    -> $ExprAdd <= $ExprAdd"  , gram_rule_binop         , &nonterm_symbs) );
    ret.append( make_rule("$ExprCmp    -> $ExprAdd > $ExprAdd"   , gram_rule_binop         , &nonterm_symbs) );
    ret.append( make_rule("$ExprCmp    -> $ExprAdd >= $ExprAdd"  , gram_rule_binop         , &nonterm_symbs) );
    ret.append( make_rule("$ExprCmp    -> $ExprAdd == $ExprAdd"  , gram_rule_binop         , &nonterm_symbs) );
    ret.append( make_rule("$ExprCmp    -> $ExprAdd != $ExprAdd"  , gram_rule_binop         , &nonterm_symbs) );

    // This order is a bit unoptimal, but results in much fewer rules in the parser. Eventually, optimisations in the parser will make the better order better.
    ret.append( make_rule("$ExprLop    -> $ExprCmp"              , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$ExprLop    -> $ExprLop || $ExprCmp"  , gram_rule_binop         , &nonterm_symbs) );
    ret.append( make_rule("$ExprLop    -> $ExprLop && $ExprCmp"  , gram_rule_binop         , &nonterm_symbs) );

    ret.append( make_rule("$Expr       -> $ExprLop"              , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$Expr       -> $Expr as $Type"        , gram_rule_typecast      , &nonterm_symbs) );
    ret.append( make_rule("$Expr       -> fun ( $FargDecl ) => \
                                  { $InstrList } : $Type"        , gram_rule_lambda        , &nonterm_symbs) );
    ret.append( make_rule("$Expr       -> { $Type @ident : $IdtList }", gram_rule_constr   , &nonterm_symbs) );
    ret.append( make_rule("$Expr       -> { $Type @ident }"      , gram_rule_constr0       , &nonterm_symbs) );

    ret.append( make_rule("$Arglist    -> $Expr , $Arglist"      , gram_rule_list_push_2nd , &nonterm_symbs) );
    ret.append( make_rule("$Arglist    -> $Expr"                 , gram_rule_list_base     , &nonterm_symbs) );
    ret.append( make_rule("$Arglist    ->"                       , gram_rule_list_empty    , &nonterm_symbs) );


    // TODO: add a builtin bool type
    ret.append( make_rule("$TypeAtom   -> void"                  , gram_rule_typ_base      , &nonterm_symbs) );
    ret.append( make_rule("$TypeAtom   -> char"                  , gram_rule_typ_base      , &nonterm_symbs) );
    ret.append( make_rule("$TypeAtom   -> int"                   , gram_rule_typ_base      , &nonterm_symbs) );
    ret.append( make_rule("$TypeAtom   -> bool"                  , gram_rule_typ_base      , &nonterm_symbs) );
    ret.append( make_rule("$TypeAtom   -> @ident"                , gram_rule_typ_base      , &nonterm_symbs) );
    ret.append( make_rule("$TypeAtom   -> typeof ( $Expr )"      , gram_rule_typeof        , &nonterm_symbs) );

    ret.append( make_rule("$TypeNof    -> $TypeAtom"             , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$TypeNof    -> $TypeNof *"            , gram_rule_typ_ptr       , &nonterm_symbs) );
    ret.append( make_rule("$TypeNof    -> const $TypeAtom"       , gram_rule_typ_cst       , &nonterm_symbs) );
    ret.append( make_rule("$TypeNof    -> const ( $Type )"       , gram_rule_typ_cstpar    , &nonterm_symbs) );

    ret.append( make_rule("$Type       -> $TypeNof"              , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$Type       -> $TypeNof => $Type"     , gram_rule_typ_fptr      , &nonterm_symbs) );


    ret.append( make_rule("$Instr      -> $Decl"                 , gram_rule_instr_decl    , &nonterm_symbs) );
    ret.append( make_rule("$Instr      -> $ExprUnary = $Expr ;"  , gram_rule_instr_assign  , &nonterm_symbs) ); // not using full $Expr creates fewer rules and makes the conflict solver happy
    ret.append( make_rule("$Instr      -> $ExprStru ;"           , gram_rule_instr_fcall   , &nonterm_symbs) );
    ret.append( make_rule("$Instr      -> return ;"              , gram_rule_instr_ret_no  , &nonterm_symbs) );
    ret.append( make_rule("$Instr      -> return $Expr ;"        , gram_rule_instr_ret_smth, &nonterm_symbs) );
    ret.append( make_rule("$Instr      -> while $Expr { $InstrList }" , gram_rule_instr_while, &nonterm_symbs) );
    ret.append( make_rule("$Instr      -> if $Expr { $InstrList } \
                                                        $If_Tail", gram_rule_instr_if     , &nonterm_symbs) );

    ret.append( make_rule("$If_Tail    ->"                       , gram_rule_list_empty   , &nonterm_symbs) );
    ret.append( make_rule("$If_Tail    -> elif $Expr { $InstrList } \
                                                        $If_Tail", gram_rule_instr_elif   , &nonterm_symbs) );
    ret.append( make_rule("$If_Tail    -> else { $InstrList }"   , gram_rule_elt_n2       , &nonterm_symbs) );

    ret.append( make_rule("$Instr      -> match $Expr : $Type with \
                                                    $Match_Tail" , gram_rule_instr_match   , &nonterm_symbs) );

    ret.append( make_rule("$Match_Tail -> | @ident -> \
                                   { $InstrList } $Match_Tail"   , gram_rule_instr_match_tl, &nonterm_symbs) );
    ret.append( make_rule("$Match_Tail -> | @ident ( $IdtList ) -> \
                                   { $InstrList } $Match_Tail"   ,gram_rule_instr_match_tl2, &nonterm_symbs) );
    ret.append( make_rule("$Match_Tail ->"                       , gram_rule_list_empty    , &nonterm_symbs) );
    

    ret.append( make_rule("$InstrList  ->"                       , gram_rule_list_empty    , &nonterm_symbs) );
    ret.append( make_rule("$InstrList  -> $Instr $InstrList"     , gram_rule_list_push_1st , &nonterm_symbs) );


    ret.append( make_rule("$VarDecl    -> $Type @ident"          , gram_rule_vardecl       , &nonterm_symbs) );    
    ret.append( make_rule("$VarDecl    -> $Type @ident = $Expr"  , gram_rule_vardecl_vlue  , &nonterm_symbs) );    

    ret.append( make_rule("$Decl       -> $VarDecl ;"            , gram_rule_elt_n0        , &nonterm_symbs) );    
    ret.append( make_rule("$Decl       -> fun $Type @ident \
                                   ( $FargDecl ) { $InstrList }" , gram_rule_funcdecl      , &nonterm_symbs) );    
    ret.append( make_rule("$Decl       -> fun $Type @ident \
                                   ( $FargDecl ) ;"              , gram_rule_funcprot      , &nonterm_symbs) );    
    ret.append( make_rule("$Decl       -> type < $IdtList > \
                                           @ident { $LocDecls }" , gram_rule_type_templ    , &nonterm_symbs) );    
    ret.append( make_rule("$Decl       -> type @ident { $LocDecls }", gram_rule_type       , &nonterm_symbs) );    
    ret.append( make_rule("$Decl       -> specialize @ident \
                                        < $TargList > as @ident" , gram_rule_specialize    , &nonterm_symbs) );    

    ret.append( make_rule("$LocDecls   ->"                       , gram_rule_locdecl_empty , &nonterm_symbs) );    
    ret.append( make_rule("$LocDecls   -> $Decl $LocDecls"       , gram_rule_locdecl_decl  , &nonterm_symbs) );    
    ret.append( make_rule("$LocDecls   -> static $Decl $LocDecls", gram_rule_decl_static   , &nonterm_symbs) );    
    ret.append( make_rule("$LocDecls   -> @ident ; $LocDecls"    , gram_rule_locdecl_enum  , &nonterm_symbs) );    
    ret.append( make_rule("$LocDecls   -> @ident { $DeclList } ; \
                                                   $LocDecls"    , gram_rule_locdecl_cstr  , &nonterm_symbs) );    

    ret.append( make_rule("$DeclList   ->"                       , gram_rule_list_empty    , &nonterm_symbs) );    
    ret.append( make_rule("$DeclList   -> $Decl $DeclList"       , gram_rule_list_push_1st , &nonterm_symbs) );    

    ret.append( make_rule("$IdtList    -> @ident , $IdtList"     , gram_rule_strlist_push  , &nonterm_symbs) );
    ret.append( make_rule("$IdtList    -> @ident"                , gram_rule_strlist_base  , &nonterm_symbs) );
    ret.append( make_rule("$IdtList    ->"                       , gram_rule_list_empty    , &nonterm_symbs) ); // the function is technically incorrect, but clist_voidptr and string_list are basically identical so it works.

    ret.append( make_rule("$TargList   -> $Type , $TargList"     , gram_rule_list_push_2nd , &nonterm_symbs) );
    ret.append( make_rule("$TargList   -> $Type"                 , gram_rule_list_base     , &nonterm_symbs) );
    ret.append( make_rule("$TargList   ->"                       , gram_rule_list_empty    , &nonterm_symbs) );

    ret.append( make_rule("$FargDecl   -> $VarDecl , $FargDecl"  , gram_rule_list_push_2nd , &nonterm_symbs) );
    ret.append( make_rule("$FargDecl   -> $VarDecl"              , gram_rule_list_base     , &nonterm_symbs) );
    ret.append( make_rule("$FargDecl   ->"                       , gram_rule_list_empty    , &nonterm_symbs) );


    
    ret.append( make_rule("$Prog       ->"                       , gram_rule_list_empty    , &nonterm_symbs) );
    ret.append( make_rule("$Prog       -> $Decl $Prog"           , gram_rule_list_push_1st , &nonterm_symbs) );
    ret.append( make_rule("$Prog       -> $IncDecl $Prog"        , gram_rule_list_push_1st , &nonterm_symbs) );
    ret.append( make_rule("$IncDecl    -> # @include_C @\"string\"", gram_rule_include_c   , &nonterm_symbs) );
    ret.append( make_rule("$Prog       -> #include @\"string\" $Prog", gram_rule_include   , &nonterm_symbs) );

    // printf("rules:\n");
    // for (int i = 0; i < ret.len(); i++) {
    //     ret.ith(i)->print(nonterm_symbs);
    // }
    // gram_rule_t::remove_direct_left_recursion(&ret, &nonterm_symbs);
    gram_rule_t::remove_all_left_recursion(&ret, &nonterm_symbs);
    gram_rule_t::remove_useless_rules(&ret, nonterm_symbs);
    // printf("with left recursion eliminated:\nrules:\n");
    // for (int i = 0; i < ret.len(); i++) {
    //     ret.ith(i)->print(nonterm_symbs);
    // }
    // gram_rule_t::apply_direct_left_factoring(&ret, &nonterm_symbs);
    gram_rule_t::fix_factoring_conflicts(&ret, &nonterm_symbs);
    // gram_rule_t::fuse_identical_nonterms(&ret, &nonterm_symbs);
    // gram_rule_t::remove_useless_rules(&ret, nonterm_symbs);
    // printf("with left factoring applied:\nrules:\n");
    // for (int i = 0; i < ret.len(); i++) {
    //     ret.ith(i)->print(nonterm_symbs);
    // }

    bool ignore_conflicts = false;

    gram_rule_t::gram_symbol_t end = {.kind=gram_rule_t::gram_symbol_t::Exact};
    end.dat.Exact_dat.tok.kind = token::EndOfInput;
    int goal = string_list_find(nonterm_symbs, "Prog");
    prog_table = gram_rule_t::make_parsing_table(ret, nonterm_symbs, goal, end, ignore_conflicts);
    return ret;
}

gram_rule_t::gram_rules parsing_rules = make_rules();

ast parse_prog(toklist* toks) {
    printf("parsing program\n");
    int goal = string_list_find(nonterm_symbs, "Prog");
    gram_rule_t::gram_symbol_t end = {.kind=gram_rule_t::gram_symbol_t::Exact};
    gram_rule_t::parsing_table table = prog_table;
    end.dat.Exact_dat.tok.kind = token::EndOfInput;
    void* ret_decls = gram_rule_t::parse_with_rules(toks, goal, end, nonterm_symbs, table);
    if (!ret_decls) {
        printf("failed to parse a program\n");
        exit(-1);
    }
    printf("parsed program!\n");
    ast ret;
    ret.decls = *(clist_voidptr*)ret_decls;
    free(ret_decls);
    return ret;
}

void parser_init() {
    included_files.init();
}

ast parse(toklist toks) {
    ast ret = parse_prog(&toks);
    // parse_aux(toks, &ret, &included_files);
    return ret;
}

ast parse_file(const char* path) {
    toklist l = lex_file(path);
    return parse(l);
}
