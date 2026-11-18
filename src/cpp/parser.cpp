
#pragma once

#include "utils.cpp"
#include "ast.cpp"
#include "lexer.cpp"

ast parse_file(const char* path);
string_list included_files;

anyptr gram_rule_elt_n0(clist_anyptr l) {
    if (l.len() > 0) {
        return l.ith(0);
    }
    anyptr ret;
    ret.init_null();
    return ret;
}
anyptr gram_rule_elt_n1(clist_anyptr l) {
    if (l.len() > 1) {
        return l.ith(1);
    }
    anyptr ret;
    ret.init_null();
    return ret;
}
anyptr gram_rule_binop(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Binop;
    ret->dat.binop_dat.op = ((token*)l.ith(1).ptr)->dat.Binop_dat.op;
    ret->dat.binop_dat.v1 = (expr*)l.ith(0).ptr;
    ret->dat.binop_dat.v2 = (expr*)l.ith(2).ptr;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_unop(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Unop;
    ret->dat.unop_dat.op = ((token*)l.ith(0).ptr)->dat.Unop_dat.op;
    ret->dat.unop_dat.v = (expr*)l.ith(1).ptr;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_neg(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Unop;
    ret->dat.unop_dat.op.kind = unop::Neg;
    ret->dat.unop_dat.v = (expr*)l.ith(1).ptr;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_dot(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Field;
    ret->dat.field_dat.stru = (expr*)l.ith(0).ptr;
    ret->dat.field_dat.field = ((token*)l.ith(2).ptr)->dat.Ident_dat.str;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_arrow(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Arrow;
    ret->dat.arrow_dat.stru = (expr*)l.ith(0).ptr;
    ret->dat.arrow_dat.field = ((token*)l.ith(2).ptr)->dat.Ident_dat.str;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_deref(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Unop;
    ret->dat.unop_dat.op.kind = unop::Deref;
    ret->dat.unop_dat.v = (expr*)l.ith(1).ptr;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_addr(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Unop;
    ret->dat.unop_dat.op.kind = unop::Addr;
    ret->dat.unop_dat.v = (expr*)l.ith(1).ptr;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_int(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Int;
    ret->dat.int_dat = ((token*)l.ith(0).ptr)->dat.VInt_dat.dat;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_string(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::String;
    ret->dat.string_dat = ((token*)l.ith(0).ptr)->dat.VString_dat.str;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_var(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Var;
    ret->dat.var_dat = ((token*)l.ith(0).ptr)->dat.Ident_dat.str;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_array(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Index;
    ret->dat.ind_dat.arr = (expr*)l.ith(0).ptr;
    ret->dat.ind_dat.ind = (expr*)l.ith(2).ptr;
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_func(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Fcall;
    ret->dat.fcall_dat.func = (expr*)l.ith(0).ptr;
    ret->dat.fcall_dat.args = (clist_voidptr*)l.ith(2).ptr;

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_list_push_2nd(clist_anyptr l) {
    clist_voidptr* ret = (clist_voidptr*)l.ith(2).ptr;
    ret->push(l.ith(0).ptr);

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_list_push_1st(clist_anyptr l) {
    clist_voidptr* ret = (clist_voidptr*)l.ith(1).ptr;
    ret->push(l.ith(0).ptr);

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_list_base(clist_anyptr l) {
    clist_voidptr* ret = (clist_voidptr*)malloc(sizeof(clist_voidptr));
    ret->init();
    ret->append(l.ith(0).ptr);

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_list_empty(clist_anyptr l) {
    clist_voidptr* ret = (clist_voidptr*)malloc(sizeof(clist_voidptr));
    ret->init();
    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_typecast(clist_anyptr l) {
    expr* ret = (expr*)malloc(sizeof(expr));
    ret->kind = expr::Typecast;
    ret->dat.typecast_dat.v = (expr*)l.ith(0).ptr;
    ret->dat.typecast_dat.t = (typ*)l.ith(2).ptr;

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_typ_base(clist_anyptr l) {
    typ* ret = (typ*)malloc(sizeof(typ));
    token n = *(token*)l.ith(0).ptr;
    if (n.kind == token::TVoid) {
        ret->kind = typ::TVoid;
    } else if (n.kind == token::TInt) {
        ret->kind = typ::TInt;
    } else if (n.kind == token::TChar) {
        ret->kind = typ::TChar;
    } else if (n.kind == token::Ident) {
        ret->kind = typ::TIdent;
        ret->dat.TIdent_dat = n.dat.Ident_dat.str;
    } else {
        printf("impossible token kind\n");
        exit(-1);
    }

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_typ_ptr(clist_anyptr l) {
    typ* ret = (typ*)malloc(sizeof(typ));
    ret->kind = typ::TPtr;
    ret->dat.ptr_dat = (typ*)l.ith(0).ptr;

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_typ_cst(clist_anyptr l) {
    typ* ret = (typ*)malloc(sizeof(typ));
    ret->kind = typ::TConst;
    ret->dat.const_dat = (typ*)l.ith(0).ptr;

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_typeof(clist_anyptr l) {
    typ* ret = (typ*)malloc(sizeof(typ));
    ret->kind = typ::Typeof;
    ret->dat.typeof_dat = (expr*)l.ith(2).ptr;

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_instr_decl(clist_anyptr l) {
    instr* ret = (instr*)malloc(sizeof(instr));
    ret->kind = instr::Decl;
    ret->dat.decl_dat.d = (decl*)l.ith(0).ptr;

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_vardecl(clist_anyptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Var;
    ret->dat.var_dat.name = ((token*)l.ith(1).ptr)->dat.Ident_dat.str;
    ret->dat.var_dat.t = (typ*)l.ith(0).ptr;
    ret->dat.var_dat.v = nullptr;

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_vardecl_vlue(clist_anyptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Var;
    ret->dat.var_dat.name = ((token*)l.ith(1).ptr)->dat.Ident_dat.str;
    ret->dat.var_dat.t = (typ*)l.ith(0).ptr;
    ret->dat.var_dat.v = (expr*)l.ith(3).ptr;

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_type(clist_anyptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Type;
    ret->dat.type_dat.name = ((token*)l.ith(1).ptr)->dat.Ident_dat.str;
    clist_voidptr* tmp = (clist_voidptr*)l.ith(3).ptr;
    tmp[0].reverse();
    tmp[1].reverse();
    ret->dat.type_dat.constrs = tmp[0];
    ret->dat.type_dat.other_decls = tmp[1];
    if (!ret->dat.type_dat.constrs.len()) {
        decl::type_constr* unit = (decl::type_constr*)malloc(sizeof(decl::type_constr));
        unit->fields.init();
        unit->name = "_";
        ret->dat.type_dat.constrs.push(unit);
    }

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_locdecl_empty(clist_anyptr l) {
    clist_voidptr* ret = (clist_voidptr*)malloc(2*sizeof(clist_voidptr));
    ret[0].init();
    ret[1].init();

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_locdecl_decl(clist_anyptr l) {
    clist_voidptr* tmp = (clist_voidptr*)l.ith(1).ptr;
    tmp[1].push((decl*)l.ith(0).ptr);
    return l.ith(1);
}
anyptr gram_rule_locdecl_enum(clist_anyptr l) {
    decl::type_constr* cstr = (decl::type_constr*)malloc(sizeof(decl::type_constr));
    cstr->fields.init();
    cstr->name = ((token*)l.ith(0).ptr)->dat.Ident_dat.str;
    clist_voidptr* tmp = (clist_voidptr*)l.ith(2).ptr;
    tmp[0].push(cstr);
    return l.ith(2);
}
anyptr gram_rule_locdecl_cstr(clist_anyptr l) {
    decl::type_constr* cstr = (decl::type_constr*)malloc(sizeof(decl::type_constr));
    cstr->fields = *(clist_voidptr*)l.ith(2).ptr;
    free(l.ith(2).ptr);
    cstr->name = ((token*)l.ith(0).ptr)->dat.Ident_dat.str;
    clist_voidptr* tmp = (clist_voidptr*)l.ith(5).ptr;
    tmp[0].push(cstr);
    return l.ith(5);
}
anyptr gram_rule_include_c(clist_anyptr l) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Include_C;
    ret->dat.include_dat.file = ((token*)l.ith(2).ptr)->dat.VString_dat.str;

    anyptr r;
    r.init_view(ret);
    return r;
}
anyptr gram_rule_include(clist_anyptr l) {
    clist_voidptr* prog = (clist_voidptr*)l.ith(3).ptr;
    const char* path = ((token*)l.ith(2).ptr)->dat.VString_dat.str;
    if (string_list_find(included_files, path) < 0)
    {
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

    ret.append( make_rule("$Arglist    -> $Expr , $Arglist"      , gram_rule_list_push_2nd , &nonterm_symbs) );
    ret.append( make_rule("$Arglist    -> $Expr"                 , gram_rule_list_base     , &nonterm_symbs) );
    ret.append( make_rule("$Arglist    ->"                       , gram_rule_list_empty    , &nonterm_symbs) );


    // TODO: add a builtin bool type
    ret.append( make_rule("$TypeAtom   -> void"                  , gram_rule_typ_base      , &nonterm_symbs) );
    ret.append( make_rule("$TypeAtom   -> char"                  , gram_rule_typ_base      , &nonterm_symbs) );
    ret.append( make_rule("$TypeAtom   -> int"                   , gram_rule_typ_base      , &nonterm_symbs) );
    ret.append( make_rule("$TypeAtom   -> @ident"                , gram_rule_typ_base      , &nonterm_symbs) );
    ret.append( make_rule("$TypeAtom   -> typeof ( $Expr )"      , gram_rule_typeof        , &nonterm_symbs) );

    ret.append( make_rule("$TypeNof    -> $TypeAtom"             , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$TypeNof    -> $TypeNof *"            , gram_rule_typ_ptr       , &nonterm_symbs) );
    ret.append( make_rule("$TypeNof    -> const $TypeAtom"       , gram_rule_typ_cst       , &nonterm_symbs) );
    ret.append( make_rule("$TypeNof    -> const ( $Type )"       , nullptr                 , &nonterm_symbs) );

    ret.append( make_rule("$Type       -> $TypeNof"              , gram_rule_elt_n0        , &nonterm_symbs) );
    ret.append( make_rule("$Type       -> $TypeNof => $Type"     , nullptr                 , &nonterm_symbs) );


    ret.append( make_rule("$Instr      -> $Decl"                 , gram_rule_instr_decl    , &nonterm_symbs) );
    ret.append( make_rule("$Instr      -> $ExprUnary = $Expr ;"  , nullptr                 , &nonterm_symbs) ); // not using full $Expr creates fewer rules and makes the conflict solver happy
    ret.append( make_rule("$Instr      -> $ExprStru ;"           , nullptr                 , &nonterm_symbs) );
    ret.append( make_rule("$Instr      -> return ;"              , nullptr                 , &nonterm_symbs) );
    ret.append( make_rule("$Instr      -> return $Expr ;"        , nullptr                 , &nonterm_symbs) );
    ret.append( make_rule("$Instr      -> while $Expr { $InstrList }" , nullptr            , &nonterm_symbs) );
    ret.append( make_rule("$Instr      -> if $Expr { $InstrList } \
                                                        $If_Tail", nullptr                , &nonterm_symbs) );

    ret.append( make_rule("$If_Tail    ->"                       , nullptr                , &nonterm_symbs) );
    ret.append( make_rule("$If_Tail    -> elif $Expr { $InstrList } \
                                                        $If_Tail", nullptr                , &nonterm_symbs) );
    ret.append( make_rule("$If_Tail    -> else { $InstrList }"   , nullptr                , &nonterm_symbs) );


    ret.append( make_rule("$InstrList  ->"                       , nullptr                 , &nonterm_symbs) );
    ret.append( make_rule("$InstrList  -> $Instr $InstrList"     , nullptr                 , &nonterm_symbs) );


    ret.append( make_rule("$VarDecl    -> $Type @ident"          , gram_rule_vardecl       , &nonterm_symbs) );    
    ret.append( make_rule("$VarDecl    -> $Type @ident = $Expr"  , gram_rule_vardecl_vlue  , &nonterm_symbs) );    

    ret.append( make_rule("$Decl       -> $VarDecl ;"            , gram_rule_elt_n0        , &nonterm_symbs) );    
    ret.append( make_rule("$Decl       -> func $Type @ident \
                                   ( $FargDecl ) { $InstrList }" , nullptr                 , &nonterm_symbs) );    
    ret.append( make_rule("$Decl       -> func $Type @ident \
                                   ( $FargDecl ) ;"              , nullptr                 , &nonterm_symbs) );    
    ret.append( make_rule("$Decl       -> type < $Targdcl > \
                                           @ident { $LocDecls }" , nullptr                 , &nonterm_symbs) );    
    ret.append( make_rule("$Decl       -> type @ident { $LocDecls }", gram_rule_type       , &nonterm_symbs) );    
    ret.append( make_rule("$Decl       -> specialize @ident \
                                        < $TargList > as @ident" , nullptr                 , &nonterm_symbs) );    

    ret.append( make_rule("$LocDecls   ->"                       , gram_rule_locdecl_empty , &nonterm_symbs) );    
    ret.append( make_rule("$LocDecls   -> $Decl $LocDecls"       , gram_rule_locdecl_decl  , &nonterm_symbs) );    
    ret.append( make_rule("$LocDecls   -> static $Decl $LocDecls", nullptr                 , &nonterm_symbs) );    
    ret.append( make_rule("$LocDecls   -> @ident ; $LocDecls"    , gram_rule_locdecl_enum  , &nonterm_symbs) );    
    ret.append( make_rule("$LocDecls   -> @ident { $DeclList } ; \
                                                   $LocDecls"    , gram_rule_locdecl_cstr  , &nonterm_symbs) );    

    ret.append( make_rule("$DeclList   ->"                       , gram_rule_list_empty    , &nonterm_symbs) );    
    ret.append( make_rule("$DeclList   -> $Decl $DeclList"       , gram_rule_list_push_1st , &nonterm_symbs) );    

    ret.append( make_rule("$Targdcl    -> @ident , $Targdcl"     , gram_rule_list_push_2nd , &nonterm_symbs) );
    ret.append( make_rule("$Targdcl    -> @ident"                , gram_rule_list_base     , &nonterm_symbs) );
    ret.append( make_rule("$Targdcl    ->"                       , gram_rule_list_empty    , &nonterm_symbs) );

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
    anyptr ret_decls = gram_rule_t::parse_with_rules(toks, goal, end, parsing_rules, nonterm_symbs, table);
    if (!ret_decls.ptr) {
        printf("failed to parse a program\n");
        exit(-1);
    }
    printf("parsed program!\n");
    ast ret;
    ret.decls = *(clist_voidptr*)ret_decls.ptr;
    free(ret_decls.ptr);
    free(ret_decls.n_refs);
    return ret;
}

// typ* parse_typ(toklist* toks) {
//     token n = toks->ith(0);
//     typ* t = (typ*)malloc(sizeof(typ));
//     if (n.kind == token::TVoid) {
//         t->kind = typ::TVoid;
//         *toks = toks->tail();
//     } else if (n.kind == token::TInt) {
//         t->kind = typ::TInt;
//         *toks = toks->tail();
//     } else if (n.kind == token::TChar) {
//         t->kind = typ::TChar;
//         *toks = toks->tail();
//     } else if (n.kind == token::Ident) {
//         t->kind = typ::TIdent;
//         t->dat.TIdent_dat = n.dat.Ident_dat.str;
//         *toks = toks->tail();
//     } else if (n.kind == token::Const) {
//         t->kind = typ::TConst;
//         *toks = toks->tail();
//         t->dat.const_dat = parse_typ(toks);
//     } else if (n.kind == token::Typeof) {
//         t->kind = typ::Typeof;
//         *toks = toks->tail();
//         n = toks->ith(0);
//         if (n.kind != token::LPAREN) {
//             printf("expected '(' after typeof\n");
//             exit(-1);
//         }
//         *toks = toks->tail();
//         t->dat.typeof_dat = parse_expr(toks, token::RPAREN);
//         n = toks->ith(0);
//         if (n.kind != token::RPAREN) {
//             printf("expected ')' after typeof\n");
//             exit(-1);
//         }
//         *toks = toks->tail();
//     } else {
//         printf("invalid type identifier\n");
//         exit(-1);
//     }
//     n = toks->ith(0);
//     while (n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Mul) {
//         *toks = toks->tail();
//         typ* p = (typ*)malloc(sizeof(typ));
//         p->kind = typ::TPtr;
//         p->dat.ptr_dat = t;
//         t = p;
//         n = toks->ith(0);
//     }
//     if (n.kind == token::Implies) {
//         *toks = toks->tail();
//         typ* p = (typ*)malloc(sizeof(typ));
//         p->kind = typ::Tfunptr;
//         p->dat.tfunptr_dat.args_t = old_clist::new_clist(sizeof(typ));
//         p->dat.tfunptr_dat.ret_t = parse_typ(toks);
//         p->dat.tfunptr_dat.args_t.push(t);
//         t = p;
//         n = toks->ith(0);
//     }   
//     return t;
// }

// decl* parse_var_decl(toklist* toks, bool check_semicolon) {
//     decl* ret = (decl*)malloc(sizeof(decl));
//     ret->kind = decl::Var;
//     ret->dat.var_dat.t = parse_typ(toks);
//     token n = toks->ith(0);
//     if (n.kind != token::Ident) {
//         printf("expected identifier after type in declaration\n");
//         exit(-1);
//     }
//     *toks = toks->tail();
//     ret->dat.var_dat.name = n.dat.Ident_dat.str;
//     n = toks->ith(0);
//     if (n.kind == token::Set) {
//         *toks = toks->tail();
//         ret->dat.var_dat.v = parse_expr(toks, token::Semicol); // we ignore that function declaration exists
//     } else {
//         ret->dat.var_dat.v = nullptr;
//     }
//     if (check_semicolon) {
//         n = toks->ith(0);
//         if (n.kind != token::Semicol) {
//             printf("expected semicolon after declaration\n");
//             exit(-1);
//         }
//         *toks = toks->tail();
//     }
//     printf("parsed declaration of variable %s.\n", ret->dat.var_dat.name);
//     return ret;
// }

// decl* parse_decl(toklist* toks);

// instr* parse_instr(toklist* toks);

// old_clist parse_instr_block(toklist* toks) {
//     old_clist ret = old_clist::new_clist(sizeof(instr));
//     token n = toks->ith(0);
//     if (n.kind != token::LBRACK) {
//         printf("expected '{' to start a code block, got token id %d\n", (int)n.kind);
//         exit(-1);
//     }
//     *toks = toks->tail();
//     n = toks->ith(0);
//     while (n.kind != token::RBRACK) {
//         instr* instrs = parse_instr(toks);
//         if (instrs) {
//             ret.push(instrs);
//             free(instrs);
//         }
//         n = toks->ith(0);
//     }
//     ret.reverse();
//     *toks = toks->tail();
//     return ret;
// }


// instr* parse_instr(toklist* toks) {
//     token n = toks->ith(0);
//     if (n.kind == token::Return) {
//         *toks = toks->tail();
//         instr* ret = (instr*)malloc(sizeof(instr));
//         ret->kind = instr::Return;
//         ret->dat.ret_dat.v = parse_expr(toks, token::Semicol);
//         n = toks->ith(0);
//         if (n.kind != token::Semicol) {
//             printf("expected ';' after return instruction; got token %i\n", (int)n.kind);
//             exit(-1);
//         }
//         *toks = toks->tail();
//         return ret;
//     } else if (n.kind == token::If) {
//         *toks = toks->tail();
//         instr* ret = (instr*)malloc(sizeof(instr));
//         ret->kind = instr::If;
//         ret->dat.if_dat.b = parse_expr(toks, token::LBRACK);
//         ret->dat.if_dat.truebrc = parse_instr_block(toks);
//         ret->dat.if_dat.falsebrc = old_clist::new_clist(sizeof(instr));
//         instr* curr = ret;
//         n = toks->ith(0);
//         while (n.kind == token::Elif) {
//             *toks = toks->tail();
//             instr cif;
//             cif.kind = instr::If;
//             cif.dat.if_dat.b = parse_expr(toks, token::LBRACK);
//             cif.dat.if_dat.truebrc = parse_instr_block(toks);
//             cif.dat.if_dat.falsebrc = old_clist::new_clist(sizeof(instr));
//             curr->dat.if_dat.falsebrc.push(&cif);
//             curr = (instr*)curr->dat.if_dat.falsebrc.ith(0);
//             n = toks->ith(0);
//         }
//         if (n.kind == token::Else) {
//             *toks = toks->tail();
//             old_clist block = parse_instr_block(toks);
//             curr->dat.if_dat.falsebrc.del();
//             curr->dat.if_dat.falsebrc = block;
//         }
//         return ret;
//     } else if (n.kind == token::While) {
//         *toks = toks->tail();
//         instr* ret = (instr*)malloc(sizeof(instr));
//         ret->kind = instr::While;
//         ret->dat.while_dat.b = parse_expr(toks, token::LBRACK);
//         ret->dat.while_dat.instrs = parse_instr_block(toks);
//         return ret;
//     }
//     toklist left = *toks;
//     toklist base = *toks;
//     bool found_par = false;
//     while (toks->len()) {
//         n = toks->ith(0);
//         if (n.kind == token::Semicol) {
//             if (left.l == toks->l) {
//                 return nullptr; // empty intruction
//             } else if (found_par) { // found parentheses and no '=', so a function call
//                 *toks = left;
//                 // we parse function calls as an rvalue
//                 instr* ist = (instr*)malloc(sizeof(instr));
//                 ist->kind = instr::Fcall;
//                 ist->dat.fcall_dat.call = parse_expr(toks, token::Semicol);
//                 n = toks->ith(0);
//                 if (n.kind != token::Semicol) {
//                     printf("expected ';' after instruction; got token %i\n", (int)n.kind);
//                     exit(-1);
//                 }
//                 *toks = toks->tail();
//                 return ist;
//             }
//             // we have found neither '=' or '(' tokens in our instruction, to it is a declaration
//             instr* ist = (instr*)malloc(sizeof(instr));
//             ist->kind = instr::Decl;
//             ist->dat.decl_dat.d = parse_var_decl(&left, true);
//             *toks = left;
//             return ist;
//         } else if (n.kind == token::Set) { // we have an '=' in our instruction, so it is a set operation (not always true but almost)
//             instr* ist = (instr*)malloc(sizeof(instr));
//             ist->kind = instr::Set;
//             ist->dat.set_dat.l = parse_expr(&left, token::Set);
//             if (left.len() != toks->len()) {
//                 printf("impossible to parse lval for assignment operation (able to parse %d/%d tokens)\n", (int)(base.len() - left.len()), (int)(base.len() - toks->len()));
//                 exit(-1);
//             }
//             *toks = toks->tail();
//             ist->dat.set_dat.r = parse_expr(toks, token::Semicol);
//             n = toks->ith(0);
//             if (n.kind != token::Semicol) {
//                 printf("expected ';' after instruction; got token %i\n", (int)n.kind);
//                 exit(-1);
//             }
//             *toks = toks->tail();
//             return ist;
//         } else if (n.kind == token::LPAREN) {
//             found_par = true;
//         }
//         *toks = toks->tail();
//     }
//     printf("instruction not terminated by a semicolon\n");
//     exit(-1);
// }

// decl* parse_fun_decl(toklist* toks) {
//     decl* ret = (decl*)malloc(sizeof(decl));
//     ret->kind = decl::Func;
//     ret->dat.func_dat.ret_t = parse_typ(toks);
//     ret->dat.func_dat.args_decls = old_clist::new_clist(sizeof(decl));
//     token n = toks->ith(0);
//     if (n.kind != token::Ident) {
//         printf("expected identifier after type in function declaration");
//         exit(-1);
//     }
//     *toks = toks->tail();
//     ret->dat.func_dat.name = n.dat.Ident_dat.str;
//     n = toks->ith(0);
//     if (n.kind != token::LPAREN) {
//         printf("expected identifier after type in function declaration");
//         exit(-1);
//     }
//     *toks = toks->tail();
//     n = toks->ith(0);
//     while (n.kind != token::RPAREN)
//     { // this is absolutely horrendous and will sometime parse nonsense, but it will parse correct function argument
//         if (n.kind != token::Comma) {
//             decl* arg = parse_var_decl(toks, false);
//             ret->dat.func_dat.args_decls.push(arg);
//             free(arg);
//         } else {
//             *toks = toks->tail();
//         }
//         n = toks->ith(0);
//     }
//     ret->dat.func_dat.args_decls.reverse();
//     *toks = toks->tail();
//     n = toks->ith(0);
//     if (n.kind == token::Semicol) {
//         *toks = toks->tail();
//         ret->dat.func_dat.instrs = nullptr;
//         return ret;
//     }
//     ret->dat.func_dat.instrs = (old_clist*)malloc(sizeof(old_clist));
//     *ret->dat.func_dat.instrs = parse_instr_block(toks);
//     return ret;
// }

// decl::type_constr parse_type_constructor(toklist* toks) {
//     decl::type_constr ret;
//     ret.fields = old_clist::new_clist(sizeof(decl));
//     token n = toks->ith(0);
//     if (n.kind != token::Ident) {
//         printf("expected identifier for type constructor declaration\n");
//         exit(-1);
//     }
//     ret.name = n.dat.Ident_dat.str;
//     *toks = toks->tail();
//     n = toks->ith(0);
//     if (n.kind == token::Semicol) {
//         *toks = toks->tail();
//         return ret;
//     }
//     if (n.kind != token::LBRACK) {
//         printf("expected '{' for type constructor declaration\n");
//         exit(-1);
//     }
//     *toks = toks->tail();
//     n = toks->ith(0);
//     while (toks->ith(0).kind != token::RBRACK)
//     {
//         n = toks->ith(0);
//         decl* d = parse_decl(toks);
//         ret.fields.push(d);
//         free(d);
//         n = toks->ith(0);
//     }
//     *toks = toks->tail();
//     n = toks->ith(0);
//     if (n.kind != token::Semicol) {
//         printf("expected ';' at end of type constructor declaration\n");
//         exit(-1);
//     }
//     *toks = toks->tail();
//     ret.fields.reverse();
//     return ret;
// }

// decl* parse_type_decl(toklist* toks) {
//     decl* ret = (decl*)malloc(sizeof(decl));
//     ret->kind = decl::Type;
//     ret->dat.type_dat.constrs = old_clist::new_clist(sizeof(decl::type_constr));
//     ret->dat.type_dat.other_decls = old_clist::new_clist(sizeof(decl));
//     token n = toks->ith(0);
//     if (n.kind == token::Ident) {
//         ret->dat.type_dat.name = n.dat.Ident_dat.str;
//         *toks = toks->tail();
//     } else if (n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Lt) {
//         // declaration is a templated type
//         *toks = toks->tail();
//         ret->kind = decl::Templated;
//         n = toks->ith(0);
//         if (n.kind != token::Ident) {
//             printf("expected identifier as template parameter, got token id %d\n", (int)n.kind);
//             exit(-1);
//         }
//         ret->dat.templated_dat.param_name = n.dat.Ident_dat.str;
//         *toks = toks->tail();
//         n = toks->ith(0);
//         if (!(n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Gt)) {
//             printf("expected '>' after template parameter, got token id %d\n", (int)n.kind);
//             exit(-1);
//         }
//         *toks = toks->tail();
//         ret->dat.templated_dat.d = parse_type_decl(toks);
//         if (ret->dat.templated_dat.d->kind == decl::Type) {
//             ret->dat.templated_dat.name = ret->dat.templated_dat.d->dat.type_dat.name;
//         } else if (ret->dat.templated_dat.d->kind == decl::Templated) {
//             ret->dat.templated_dat.name = ret->dat.templated_dat.d->dat.templated_dat.name;
//         } else {
//             printf("kind of templated type unsupported (id %d)\n", (int)ret->dat.templated_dat.d->kind);
//             exit(-1);
//         }
//         printf("templated type %s parsed\n", ret->dat.templated_dat.name);
//         return ret;
//     } else {
//         ret->dat.type_dat.name = nullptr;
//     }
//     n = toks->ith(0);
//     if (n.kind != token::LBRACK) {
//         printf("expected '{' for type declaration\n");
//         exit(-1);
//     }
//     *toks = toks->tail();
//     n = toks->ith(0);
//     while (toks->ith(0).kind != token::RBRACK)
//     {
//         n = toks->ith(0);
//         token n2 = toks->ith(1);
//         if (n2.kind != token::Semicol && n2.kind != token::LBRACK) { // declaration inside our type
//             decl* d = parse_decl(toks);
//             ret->dat.type_dat.other_decls.push(d);
//             free(d);
//         } else {
//             decl::type_constr constr = parse_type_constructor(toks);
//             ret->dat.type_dat.constrs.push(&constr);
//         }
//         n = toks->ith(0);
//     }
//     *toks = toks->tail();
//     ret->dat.type_dat.constrs.reverse();
//     ret->dat.type_dat.other_decls.reverse();
//     if (!ret->dat.type_dat.constrs.len()) {
//         decl::type_constr unit;
//         unit.fields = old_clist::new_clist(sizeof(decl));
//         unit.name = "_";
//         ret->dat.type_dat.constrs.push(&unit);
//     }
//     return ret;
// }

// decl* parse_decl(toklist* toks) {
//     token n = toks->ith(0);
//     if (n.kind == token::Static) {
//         *toks = toks->tail();
//         decl* ret = (decl*)malloc(sizeof(decl));
//         ret->kind = decl::Static;
//         ret->dat.static_dat.d = parse_decl(toks);
//         return ret;
//     } else if (n.kind == token::Type) {
//         *toks = toks->tail();
//         return parse_type_decl(toks);
//     } else if (n.kind == token::Func) {
//         *toks = toks->tail();
//         return parse_fun_decl(toks);
//     } else if (n.kind == token::Specialize) {
//         decl* ret = (decl*)malloc(sizeof(decl));
//         // declaration of a specialization
//         *toks = toks->tail();
//         ret->kind = decl::Specialize;
//         n = toks->ith(0);
//         if (n.kind != token::Ident) {
//             printf("expected identifier for specialized type, got token id %d\n", (int)n.kind);
//             exit(-1);
//         }
//         ret->dat.specialize_dat.templated_t = n.dat.Ident_dat.str;
//         *toks = toks->tail();
//         n = toks->ith(0);
//         if (!(n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Lt)) {
//             printf("expected '<' for template specialization, got token id %d\n", (int)n.kind);
//             exit(-1);
//         }
//         *toks = toks->tail();
//         ret->dat.specialize_dat.param = parse_typ(toks);
//         n = toks->ith(0);
//         if (!(n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Gt)) {
//             printf("expected '>' after template parameter, got token id %d\n", (int)n.kind);
//             exit(-1);
//         }
//         *toks = toks->tail();
//         n = toks->ith(0);
//         if (!(n.kind == token::As)) {
//             printf("expected 'as' after template specialization, got token id %d\n", (int)n.kind);
//             exit(-1);
//         }
//         *toks = toks->tail();
//         n = toks->ith(0);
//         if (n.kind != token::Ident) {
//             printf("expected identifier for specialized type new name, got token id %d\n", (int)n.kind);
//             exit(-1);
//         }
//         ret->dat.specialize_dat.newname = n.dat.Ident_dat.str;
//         *toks = toks->tail();
//         return ret;
//     }
//     return parse_var_decl(toks, true);
// }

// void parse_aux(toklist toks, ast* ret, string_list* included_files) {
//     while (toks.len()) {
//         printf("r:%d\n", toks.len());
//         token tok = toks.ith(0);
//         if (tok.kind == token::Hashtag) {
//             toks = toks.tail();
//             tok = toks.ith(0);
//             if (tok.kind == token::Include) {
//                 toks = toks.tail();
//                 tok = toks.ith(0);
//                 if (tok.kind != token::VString) {
//                     printf("expected string after '#include'\n");
//                     exit(-1);
//                 }
//                 toks = toks.tail();
//                 if (string_list_find(*included_files, tok.dat.VString_dat.str) < 0) { // this test is maybe a bit too simple, but i'll work for now
//                     // we parse the file as if it was copy-pasted in this one
//                     included_files->push(tok.dat.VString_dat.str);
//                     toklist toks = lex_file(tok.dat.VString_dat.str);
//                     parse_aux(toks, ret, included_files);
//                     toks.del(); // yes this is a memory leak
//                 }
//             } else {
//                 if (tok.kind != token::Include_C) {
//                     printf("expected include_C after '#'\n");
//                     exit(-1);
//                 }
//                 toks = toks.tail();
//                 tok = toks.ith(0);
//                 decl* d = (decl*)malloc(sizeof(decl));
//                 d->kind = decl::Include_C;
//                 if (tok.kind != token::VString) {
//                     printf("expected string after '#include_C'\n");
//                     exit(-1);
//                 }
//                 d->dat.include_dat.file = tok.dat.VString_dat.str;
//                 toks = toks.tail();
//                 ret->decls.push(d);
//             }
//         } else {
//             decl* d = parse_decl(&toks);
//             ret->decls.push(d);
//             free(d);
//         }
//     }
// }

ast parse(toklist toks) {
    included_files.init();
    ast ret = parse_prog(&toks);
    // parse_aux(toks, &ret, &included_files);
    return ret;
}

ast parse_file(const char* path) {
    toklist l = lex_file(path);
    return parse(l);
}
