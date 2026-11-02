
#pragma once

#include "utils.cpp"
#include "ast.cpp"
#include "lexer.cpp"

lval* parse_lval(clist* toks);

rval* parse_rval(clist* toks) {
    rval* ret = (rval*)malloc(sizeof(rval));
    token* curr = (token*)toks->ith(0);

    if (curr->kind == token::VInt) {
        *toks = toks->tail();
        ret->kind = rval::Int;
        ret->dat.int_dat = curr->dat.VInt_dat.dat;
    } else { // we fallback to parsing an lvalue
        ret->kind = rval::Lval;
        ret->dat.lval_dat = parse_lval(toks);
    }
    return ret;
}

lval* parse_lval(clist* toks) {
    lval* ret = (lval*)malloc(sizeof(lval));
    token* curr = (token*)toks->ith(0);

    if (curr->kind == token::Ident) {
        *toks = toks->tail();
        ret->kind = lval::Var;
        ret->dat.var_dat = curr->dat.Ident_dat.str;
        return ret;
    }
    printf("invalid lvalue\n");
    exit(-1);
}

typ* parse_typ(clist* toks) {
    token* curr = (token*)toks->ith(0);

    typ* t = (typ*)malloc(sizeof(typ));
    if (curr->kind == token::TVoid) {
        t->kind = typ::TVoid;
        *toks = toks->tail();
    } else if (curr->kind == token::TInt) {
        t->kind = typ::TInt;
        *toks = toks->tail();
    } else if (curr->kind == token::TChar) {
        t->kind = typ::TChar;
        *toks = toks->tail();
    } else if (curr->kind == token::Const) {
        t->kind = typ::TConst;
        *toks = toks->tail();
        t->dat.const_dat = parse_typ(toks);
    } else {
        printf("invalid type identifier\n");
        exit(-1);
    }

    while (((token*)toks->ith(0))->kind == token::Star) {
        typ* p = (typ*)malloc(sizeof(typ));
        p->kind = typ::TPtr;
        p->dat.ptr_dat = t;
        t = p;
        *toks = toks->tail();
    }
    
    return t;
}

decl* parse_var_decl(clist* toks, bool check_semicolon) {
    decl* ret = (decl*)malloc(sizeof(decl));

    ret->kind = decl::Var;
    ret->dat.var_dat.t = parse_typ(toks);

    token* n = (token*)toks->ith(0);
    if (n->kind != token::Ident) {
        printf("expected identifier after type in declaration");
        exit(-1);
    }
    *toks = toks->tail();
    ret->dat.var_dat.name = n->dat.Ident_dat.str;

    n = (token*)toks->ith(0);
    if (n->kind == token::Set) {
        *toks = toks->tail();
        ret->dat.var_dat.v = parse_rval(toks);
    } else {
        ret->dat.var_dat.v = nullptr;
    }
    
    if (check_semicolon) {
        n = (token*)toks->ith(0);
        if (n->kind != token::Semicol) {
            printf("expected semicolon after declaration\n");
            exit(-1);
        }
        *toks = toks->tail();
    }
    printf("parsed declaration of variable %s.\n", ret->dat.var_dat.name);

    return ret;

}

decl* parse_decl(clist* toks);

instr* parse_instr(clist* toks) {
    token* n = (token*)toks->ith(0);
    if (n->kind == token::Return) {
        *toks = toks->tail();
        instr* ret = (instr*)malloc(sizeof(instr));
        ret->kind = instr::Return;
        ret->dat.ret_dat.v = parse_rval(toks);
        n = (token*)toks->ith(0);
        if (n->kind != token::Semicol) {
            printf("expected ';' after return instruction; got token %i\n", (int)n->kind);
            exit(-1);
        }
        *toks = toks->tail();
        return ret;
    }
    

    clist left = *toks;
    while (toks->len()) {
        n = (token*)toks->ith(0);
        if (n->kind == token::Semicol) {
            if (left.l == toks->l) {
                return nullptr;
            } // we have not found an '=' token in our instruction, to it is a function call
            printf("function calls not supported\n");
            exit(-1);
        } else if (n->kind == token::Set) { // we have an '=' in our instruction, so it is a set operation (not always true but almost)
            instr* ist = (instr*)malloc(sizeof(instr));
            ist->kind = instr::Set;
            ist->dat.set_dat.l = parse_lval(&left);
            *toks = toks->tail();
            ist->dat.set_dat.r = parse_rval(toks);
            n = (token*)toks->ith(0);
            if (n->kind != token::Semicol) {
                printf("expected ';' after instruction; got token %i\n", (int)n->kind);
                exit(-1);
            }
            *toks = toks->tail();
            return ist;
        }
        *toks = toks->tail();
    }
    printf("instruction not terminated by a semicolon\n");
    exit(-1);
}

decl* parse_fun_decl(clist* toks) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Func;
    ret->dat.func_dat.ret_t = parse_typ(toks);
    ret->dat.func_dat.args_decls = clist::new_clist(sizeof(decl));

    token* n = (token*)toks->ith(0);
    if (n->kind != token::Ident) {
        printf("expected identifier after type in function declaration");
        exit(-1);
    }
    *toks = toks->tail();
    ret->dat.func_dat.name = n->dat.Ident_dat.str;

    n = (token*)toks->ith(0);
    if (n->kind != token::LPAREN) {
        printf("expected identifier after type in function declaration");
        exit(-1);
    }
    *toks = toks->tail();

    n = (token*)toks->ith(0);
    while (n->kind != token::RPAREN)
    { // this is absolutely horrendous and will sometime parse nonsense, but it will parse correct function argument
        if (n->kind != token::Comma) {
            decl* arg = parse_var_decl(toks, false);
            ret->dat.func_dat.args_decls.push(arg);
            free(arg);
        } else {
            *toks = toks->tail();
        }
        n = (token*)toks->ith(0);
    }
    ret->dat.func_dat.args_decls.reverse();
    *toks = toks->tail();
    n = (token*)toks->ith(0);

    if (n->kind == token::Semicol) {
        *toks = toks->tail();
        ret->dat.func_dat.instrs = nullptr;
        return ret;
    }
    ret->dat.func_dat.instrs = (clist*)malloc(sizeof(clist));
    *ret->dat.func_dat.instrs = clist::new_clist(sizeof(instr));
    
    if (n->kind != token::LBRACK) {
        printf("expected '{' after arguments in function declaration");
        exit(-1);
    }
    *toks = toks->tail();

    n = (token*)toks->ith(0);
    while (n->kind != token::RBRACK) {
        instr* instrs = parse_instr(toks);
        if (instrs) {
            ret->dat.func_dat.instrs->push(instrs);
            free(instrs);
        }
        n = (token*)toks->ith(0);
    }
    ret->dat.func_dat.instrs->reverse();
    *toks = toks->tail();

    return ret;
}

decl::type_constr parse_type_constructor(clist* toks) {
    decl::type_constr ret;
    ret.fields = clist::new_clist(sizeof(decl));

    token* n = (token*)toks->ith(0);
    if (n->kind != token::Ident) {
        printf("expected identifier for type constructor declaration\n");
        exit(-1);
    }
    ret.name = n->dat.Ident_dat.str;
    *toks = toks->tail();
    
    n = (token*)toks->ith(0);
    if (n->kind == token::Semicol) {
        *toks = toks->tail();
        return ret;
    }

    if (n->kind != token::LBRACK) {
        printf("expected '{' for type constructor declaration\n");
        exit(-1);
    }
    *toks = toks->tail();

    n = (token*)toks->ith(0);
    while (((token*)toks->ith(0))->kind != token::RBRACK)
    {
        n = (token*)toks->ith(0);
        decl* d = parse_decl(toks);
        ret.fields.push(d);
        free(d);
        n = (token*)toks->ith(0);
    }
    *toks = toks->tail();
    n = (token*)toks->ith(0);
    if (n->kind != token::Semicol) {
        printf("expected ';' at end of type constructor declaration\n");
        exit(-1);
    }
    *toks = toks->tail();
    ret.fields.reverse();
    return ret;
}

decl* parse_type_decl(clist* toks) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Type;
    ret->dat.type_dat.constrs = clist::new_clist(sizeof(decl::type_constr));
    ret->dat.type_dat.other_decls = clist::new_clist(sizeof(decl));
    token* n = (token*)toks->ith(0);
    if (n->kind == token::Ident) {
        ret->dat.type_dat.name = n->dat.Ident_dat.str;
        *toks = toks->tail();
    } else {
        ret->dat.type_dat.name = nullptr;
    }
    n = (token*)toks->ith(0);
    if (n->kind != token::LBRACK) {
        printf("expected '{' for type declaration\n");
        exit(-1);
    }
    *toks = toks->tail();
    n = (token*)toks->ith(0);
    while (((token*)toks->ith(0))->kind != token::RBRACK)
    {
        n = (token*)toks->ith(0);
        token* n2 = (token*)toks->ith(1);
        if (n2->kind != token::Semicol && n2->kind != token::LBRACK) { // declaration inside our type
            decl* d = parse_decl(toks);
            ret->dat.type_dat.other_decls.push(d);
            free(d);
        } else {
            decl::type_constr constr = parse_type_constructor(toks);
            ret->dat.type_dat.constrs.push(&constr);
        }
        n = (token*)toks->ith(0);
    }
    *toks = toks->tail();
    n = (token*)toks->ith(0);
    if (n->kind != token::Semicol) {
        printf("expected ';' at end of type declaration\n");
        exit(-1);
    }
    *toks = toks->tail();
    ret->dat.type_dat.constrs.reverse();
    ret->dat.type_dat.other_decls.reverse();

    if (!ret->dat.type_dat.constrs.len()) {
        decl::type_constr unit;
        unit.fields = clist::new_clist(sizeof(decl));
        unit.name = "unit";
        ret->dat.type_dat.constrs.push(&unit);
    }

    return ret;
}

decl* parse_decl(clist* toks) {
    token* n = (token*)toks->ith(0);
    if (n->kind == token::Type) {
        *toks = toks->tail();
        return parse_type_decl(toks);
    } else if (n->kind == token::Func) {
        *toks = toks->tail();
        return parse_fun_decl(toks);
    }

    return parse_var_decl(toks, true);
}


ast parse(clist toks) {
    ast ret = {.decls = clist::new_clist(sizeof(decl))};
    while (toks.len()) {
        printf("r:%d\n", toks.len());

        token* tok = (token*)toks.ith(0);
        if (tok->kind == token::Hashtag) {
            toks = toks.tail();
            tok = (token*)toks.ith(0);
            if (tok->kind != token::Include) {
                printf("expected include after '#'\n");
                exit(-1);
            }
            toks = toks.tail();
            tok = (token*)toks.ith(0);
            decl* d = (decl*)malloc(sizeof(decl));
            d->kind = decl::Include;
            if (tok->kind != token::VString) {
                printf("expected string after '#include'\n");
                exit(-1);
            }
            d->dat.include_dat.file = tok->dat.VString_dat.str;
            toks = toks.tail();
            ret.decls.push(d);
        } else {
            decl* d = parse_decl(&toks);
            ret.decls.push(d);
            free(d);
        }
    }
    ret.decls.reverse();
    return ret;
}
