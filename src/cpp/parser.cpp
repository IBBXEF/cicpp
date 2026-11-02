
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
        ret->dat.int_dat = curr->dat.vint_dat;
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
        ret->dat.var_dat = curr->dat.ident_dat;
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
    } else if (curr->kind == token::TInt) {
        t->kind = typ::TInt;
    } else if (curr->kind == token::TChar) {
        t->kind = typ::TChar;
    } else {
        printf("invalid type identifier\n");
        exit(-1);
    }

    *toks = toks->tail();
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
    ret->dat.var_dat.name = n->dat.ident_dat;

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
    clist left = *toks;
    while (toks->len()) {
        token* tok = (token*)toks->ith(0);
        if (tok->kind == token::Semicol) {
            if (left.l == toks->l) {
                return nullptr;
            } // we have not found an '=' token in our instruction, to it is a function call
            printf("function calls not supported");
            exit(-1);
        } else if (tok->kind == token::Set) { // we have an '=' in our instruction, so it is a set operation (not always true but almost)
            instr* ist = (instr*)malloc(sizeof(instr));
            ist->kind = instr::Set;
            ist->dat.set_dat.l = parse_lval(&left);
            *toks = toks->tail();
            ist->dat.set_dat.r = parse_rval(toks);
            token* tok = (token*)toks->ith(0);
            if (tok->kind != token::Semicol) {
                printf("expected ';' after instruction; got token %i\n", (int)tok->kind);
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
    ret->dat.func_dat.name = n->dat.ident_dat;

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

clist parse_container_decl(clist* toks, const char** name) {
    clist ret = clist::new_clist(sizeof(decl));
    token* n = (token*)toks->ith(0);
    if (n->kind == token::Ident) {
        *name = n->dat.ident_dat;
        *toks = toks->tail();
    } else {
        *name = nullptr;
    }
    n = (token*)toks->ith(0);
    if (n->kind != token::LBRACK) {
        printf("expected '{' for container declaration\n");
        exit(-1);
    }
    *toks = toks->tail();
    while (((token*)toks->ith(0))->kind != token::RBRACK)
    {
        decl* d = parse_decl(toks);
        ret.push(d);
        free(d);
    }
    *toks = toks->tail();
    n = (token*)toks->ith(0);
    if (n->kind != token::Semicol) {
        printf("expected ';' at end of enum declaration\n");
        exit(-1);
    }
    *toks = toks->tail();
    ret.reverse();
    return ret;
}

decl* parse_decl(clist* toks) {
    decl* ret = (decl*)malloc(sizeof(decl));

    token* n = (token*)toks->ith(0);
    if (n->kind == token::Struct) {
        ret->kind = decl::Struct;
        *toks = toks->tail();
        ret->dat.struct_dat.decls = parse_container_decl(toks, &ret->dat.struct_dat.name);
        return ret;
    } else if (n->kind == token::Union) {
        ret->kind = decl::Union;
        *toks = toks->tail();
        ret->dat.union_dat.decls = parse_container_decl(toks, &ret->dat.union_dat.name);
        return ret;
    } else if (n->kind == token::Enum) {
        ret->kind == decl::Enum;
        ret->dat.enum_dat.vlues = clist::new_clist(sizeof(char*));
        *toks = toks->tail();

        n = (token*)toks->ith(0);
        if (n->kind == token::Ident) {
            ret->dat.enum_dat.name = n->dat.ident_dat;
            *toks = toks->tail();
        } else {
            ret->dat.enum_dat.name = nullptr;
        }
        n = (token*)toks->ith(0);
        if (n->kind != token::LBRACK) {
            printf("expected '{' for enum declaration\n");
            exit(-1);
        }
        *toks = toks->tail();

        n = (token*)toks->ith(0);
        while (n->kind != token::RBRACK)
        { // this is absolutely horrendous and will sometime parse nonsense, but it will parse correct enums
            if (n->kind != token::Comma)
            {
                if (n->kind != token::Ident)
                {
                    printf("expected ident in enum declaration\n");
                    exit(-1);
                }
                ret->dat.enum_dat.vlues.push(&n->dat.ident_dat);
            }
            *toks = toks->tail();
            n = (token*)toks->ith(0);
        }
        *toks = toks->tail();

        n = (token*)toks->ith(0);
        if (n->kind != token::Semicol) {
            printf("expected ';' at end of enum declaration\n");
            exit(-1);
        }
        *toks = toks->tail();
        ret->dat.enum_dat.vlues.reverse();
        return ret;
    } else if (n->kind == token::Func) {
        ret->kind = decl::Func;
        *toks = toks->tail();
        free(ret);
        ret = parse_fun_decl(toks);
        return ret;
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
            d->dat.include_dat.file = tok->dat.string_dat;
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
