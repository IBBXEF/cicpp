
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


decl* parse_decl(clist* toks) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->t = parse_typ(toks);
    token* n = (token*)toks->ith(0);
    if (n->kind != token::Ident) {
        printf("expected identifier after type in declaration");
        exit(-1);
    }
    *toks = toks->tail();
    ret->name = n->dat.ident_dat;

    n = (token*)toks->ith(0);
    if (n->kind == token::Set) {
        *toks = toks->tail();
        ret->v = parse_rval(toks);
    } else {
        ret->v = nullptr;
    }
    
    
    n = (token*)toks->ith(0);
    if (n->kind != token::Semicol) {
        printf("expected semicolon after declaration\n");
        exit(-1);
    }
    *toks = toks->tail();

    printf("parsed declaration of %s.\n", ret->name);

    return ret;
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
