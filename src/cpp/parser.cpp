
#pragma once

#include "utils.cpp"
#include "ast.cpp"
#include "lexer.cpp"

rval* parse_rval(clist* toks) {
    rval* ret = (rval*)malloc(sizeof(rval));
    token* curr = (token*)toks->ith(0);

    if (curr->kind == token::VInt) {
        *toks = toks->tail();
        ret->kind = rval::Int;
        ret->dat.int_dat = curr->dat.vint_dat;
    } else {
        printf("unexpected token when parsing rvalue\n");
        exit(-1);
    }
    
    

    return ret;
}

lval* parse_lval(clist* toks) {
    return nullptr;
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

decl* parse_var_decl(clist* toks) {
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
    
    
    n = (token*)toks->ith(0);
    if (n->kind != token::Semicol) {
        printf("expected semicolon after declaration\n");
        exit(-1);
    }
    *toks = toks->tail();

    printf("parsed declaration of variable %s.\n", ret->dat.var_dat.name);

    return ret;

}

decl* parse_decl(clist* toks);

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
    }

    
    return parse_var_decl(toks);
}


ast parse(clist toks) {
    ast ret = {.decls = clist::new_clist(sizeof(decl))};
    while (toks.len()) {
        printf("r:%d\n", toks.len());
        decl* d = parse_decl(&toks);
        ret.decls.push(d);
        free(d);
    }
    return ret;
}
