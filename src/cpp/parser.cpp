
#pragma once

#include "utils.cpp"
#include "ast.cpp"
#include "lexer.cpp"

lval* parse_lval(toklist* toks);
typ* parse_typ(toklist* toks);

rval* parse_rval(toklist* toks, bool can_fallback = true) {
    rval* ret = (rval*)malloc(sizeof(rval));
    token n = toks->ith(0);

    if (n.kind == token::VInt) {
        *toks = toks->tail();
        ret->kind = rval::Int;
        ret->dat.int_dat = n.dat.VInt_dat.dat;
    } else if (n.kind == token::VString) {
        *toks = toks->tail();
        ret->kind = rval::String;
        ret->dat.string_dat = n.dat.VString_dat.str;
    } else if (n.kind == token::Unop) {
        *toks = toks->tail();
        ret->kind = rval::Unop;
        ret->dat.unop_dat.op = n.dat.Unop_dat.op;
        ret->dat.unop_dat.v = parse_rval(toks);
    } else if (n.kind == token::LPAREN) {
        *toks = toks->tail();
        free(ret);
        ret = parse_rval(toks);
        n = toks->ith(0);
        if (n.kind != token::RPAREN) {
            printf("unmatched '(' (expected ')' at end of rvalue, got token id %d)\n", (int)n.kind);
            exit(-1);
        }
        *toks = toks->tail();
    } else if (n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Sub) { // the token for '-' is not a binop, we have to treat it separately
        *toks = toks->tail();
        ret->kind = rval::Unop;
        ret->dat.unop_dat.op.kind = unop::Neg;
        ret->dat.unop_dat.v = parse_rval(toks);
    } else if (n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Band) { // the token for '&' is not a binop, we have to treat it separately
        *toks = toks->tail();
        ret->kind = rval::Unop;
        ret->dat.unop_dat.op.kind = unop::Addr;
        ret->dat.unop_dat.v = parse_rval(toks); // yes it should be an lval but the parser will hopefully be replaced soon anyway
    } else if (can_fallback) { // we fallback to parsing an lvalue
        ret->kind = rval::Lval;
        ret->dat.lval_dat = parse_lval(toks);
    } else {
        printf("invalid rvalue (got token id %d)\n", (int)n.kind);
        exit(-1);
    }
    n = toks->ith(0);
    if (n.kind == token::LPAREN) {
        rval* fcal = (rval*)malloc(sizeof(rval));
        fcal->kind = rval::Fcall;
        fcal->dat.fcall_dat.func = ret;
        fcal->dat.fcall_dat.args = old_clist::new_clist(sizeof(rval));
        *toks = toks->tail();
        n = toks->ith(0);
        while (n.kind != token::RPAREN) {
            if (n.kind == token::Comma) {
                *toks = toks->tail(); // this will sometimes parse nonsense but it's okay
            } else {
                rval* arg = parse_rval(toks);
                fcal->dat.fcall_dat.args.push(arg);
                free(arg);
            }
            n = toks->ith(0);
        }
        fcal->dat.fcall_dat.args.reverse();
        *toks = toks->tail();
        ret = fcal;
    }
    n = toks->ith(0);
    if (n.kind == token::Binop) {
        *toks = toks->tail();
        rval* opret = (rval*)malloc(sizeof(rval));
        opret->kind = rval::Binop;
        opret->dat.binop_dat.op = n.dat.Binop_dat.op;
        opret->dat.binop_dat.v1 = ret;
        opret->dat.binop_dat.v2 = parse_rval(toks);
        ret = opret;
    }
    n = toks->ith(0);
    if (n.kind == token::As) {
        *toks = toks->tail();
        rval* opret = (rval*)malloc(sizeof(rval));
        opret->kind = rval::Typecast;
        opret->dat.typecast_dat.v = ret;
        opret->dat.typecast_dat.t = parse_typ(toks);
        ret = opret;
    }
    n = toks->ith(0);
    if (n.kind == token::Dot && can_fallback) { // our expression if a structure field access
        *toks = toks->tail();
        lval* lv = (lval*)malloc(sizeof(lv));
        lv->kind = lval::Field;
        lv->dat.field_dat.stru = ret;
        ret = (rval*)malloc(sizeof(rval));
        ret->kind = rval::Lval;
        n = toks->ith(0);
        if (n.kind != token::Ident) {
            printf("expected identifier for struct field name\n");
            exit(-1);
        }
        *toks = toks->tail();
        lv->dat.field_dat.field = n.dat.Ident_dat.str;
        ret->dat.lval_dat = lv;
    }
    
    n = toks->ith(0);
    if (n.kind == token::LPAREN) {
        rval* fcal = (rval*)malloc(sizeof(rval));
        fcal->kind = rval::Fcall;
        fcal->dat.fcall_dat.func = ret;
        fcal->dat.fcall_dat.args = old_clist::new_clist(sizeof(rval));
        *toks = toks->tail();
        n = toks->ith(0);
        while (n.kind != token::RPAREN) {
            if (n.kind == token::Comma) {
                *toks = toks->tail(); // this will sometimes parse nonsense but it's okay
            } else {
                rval* arg = parse_rval(toks);
                fcal->dat.fcall_dat.args.push(arg);
                free(arg);
            }
            n = toks->ith(0);
        }
        fcal->dat.fcall_dat.args.reverse();
        *toks = toks->tail();
        ret = fcal;
    }
    
    return ret;
}

lval* parse_lval(toklist* toks) {
    lval* ret = (lval*)malloc(sizeof(lval));
    token n = toks->ith(0);

    if (n.kind == token::Ident) {
        *toks = toks->tail();
        ret->kind = lval::Var;
        ret->dat.var_dat = n.dat.Ident_dat.str;
        n = toks->ith(0);
        if (n.kind == token::LSQUAR) { // we are parsing an array set
            *toks = toks->tail();
            rval* arr = (rval*)malloc(sizeof(rval));
            arr->kind = rval::Lval;
            arr->dat.lval_dat = ret;
            ret = (lval*)malloc(sizeof(lval));
            ret->kind = lval::Index;
            ret->dat.ind_dat.arr = arr;
            ret->dat.ind_dat.ind = parse_rval(toks);
            n = toks->ith(0);
            if (n.kind != token::RSQUAR) {
                printf("expected ']' for array index lvalue");
                exit(-1);
            }
            *toks = toks->tail();
        }
        return ret;
    } else if (n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Mul) { // we are parsing a pointer dereference
        *toks = toks->tail();
        ret->kind = lval::Index;
        ret->dat.ind_dat.ind = (rval*)malloc(sizeof(rval));
        ret->dat.ind_dat.ind->kind = rval::Int;
        ret->dat.ind_dat.ind->dat.int_dat = 0; // we parse *p as p[0]
        ret->dat.ind_dat.arr = parse_rval(toks);
        return ret;
    }
    // we try to parse an array index / a struct field access
    rval* mai = parse_rval(toks, false);
    n = toks->ith(0);
    if (n.kind == token::Dot) {
        *toks = toks->tail();
        ret->kind = lval::Field;
        ret->dat.field_dat.stru = mai;
        n = toks->ith(0);
        if (n.kind != token::Ident) {
            printf("expected identifier for struct field name\n");
            exit(-1);
        }
        *toks = toks->tail();
        ret->dat.field_dat.field = n.dat.Ident_dat.str;
        printf("parsed access of field %s\n", n.dat.Ident_dat.str);
        return ret;
    }
    if (n.kind != token::LSQUAR) {
        printf("expected '[' for array index lvalue\n");
        exit(-1);
    }
    ret->kind = lval::Index;
    ret->dat.ind_dat.arr = mai;
    *toks = toks->tail();
    ret->dat.ind_dat.ind = parse_rval(toks);
    n = toks->ith(0);
    if (n.kind != token::RSQUAR) {
        printf("expected ']' for array index lvalue");
        exit(-1);
    }
    *toks = toks->tail();
    return ret;
}

typ* parse_typ(toklist* toks) {
    token n = toks->ith(0);

    typ* t = (typ*)malloc(sizeof(typ));
    if (n.kind == token::TVoid) {
        t->kind = typ::TVoid;
        *toks = toks->tail();
    } else if (n.kind == token::TInt) {
        t->kind = typ::TInt;
        *toks = toks->tail();
    } else if (n.kind == token::TChar) {
        t->kind = typ::TChar;
        *toks = toks->tail();
    } else if (n.kind == token::Ident) {
        t->kind = typ::TIdent;
        t->dat.TIdent_dat = n.dat.Ident_dat.str;
        *toks = toks->tail();
    } else if (n.kind == token::Const) {
        t->kind = typ::TConst;
        *toks = toks->tail();
        t->dat.const_dat = parse_typ(toks);
    } else if (n.kind == token::Typeof) {
        t->kind = typ::Typeof;
        *toks = toks->tail();
        n = toks->ith(0);
        if (n.kind != token::LPAREN) {
            printf("expected '(' after typeof\n");
            exit(-1);
        }
        *toks = toks->tail();
        t->dat.typeof_dat = parse_rval(toks);
        n = toks->ith(0);
        if (n.kind != token::RPAREN) {
            printf("expected ')' after typeof\n");
            exit(-1);
        }
        *toks = toks->tail();
    } else {
        printf("invalid type identifier\n");
        exit(-1);
    }

    n = toks->ith(0);
    while (n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Mul) {
        *toks = toks->tail();
        typ* p = (typ*)malloc(sizeof(typ));
        p->kind = typ::TPtr;
        p->dat.ptr_dat = t;
        t = p;
        n = toks->ith(0);
    }
    if (n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Arrow) {
        *toks = toks->tail();
        typ* p = (typ*)malloc(sizeof(typ));
        p->kind = typ::Tfunptr;
        p->dat.tfunptr_dat.args_t = old_clist::new_clist(sizeof(typ));
        p->dat.tfunptr_dat.ret_t = parse_typ(toks);
        p->dat.tfunptr_dat.args_t.push(t);
        t = p;
        n = toks->ith(0);
    }
    
    return t;
}

decl* parse_var_decl(toklist* toks, bool check_semicolon) {
    decl* ret = (decl*)malloc(sizeof(decl));

    ret->kind = decl::Var;
    ret->dat.var_dat.t = parse_typ(toks);

    token n = toks->ith(0);
    if (n.kind != token::Ident) {
        printf("expected identifier after type in declaration\n");
        exit(-1);
    }
    *toks = toks->tail();
    ret->dat.var_dat.name = n.dat.Ident_dat.str;

    n = toks->ith(0);
    if (n.kind == token::Set) {
        *toks = toks->tail();
        ret->dat.var_dat.v = parse_rval(toks);
    } else {
        ret->dat.var_dat.v = nullptr;
    }
    
    if (check_semicolon) {
        n = toks->ith(0);
        if (n.kind != token::Semicol) {
            printf("expected semicolon after declaration\n");
            exit(-1);
        }
        *toks = toks->tail();
    }
    printf("parsed declaration of variable %s.\n", ret->dat.var_dat.name);

    return ret;

}

decl* parse_decl(toklist* toks);

instr* parse_instr(toklist* toks);

old_clist parse_instr_block(toklist* toks) {
    old_clist ret = old_clist::new_clist(sizeof(instr));
    
    token n = toks->ith(0);
    if (n.kind != token::LBRACK) {
        printf("expected '{' to start a code block, got token id %d\n", (int)n.kind);
        exit(-1);
    }
    *toks = toks->tail();

    n = toks->ith(0);
    while (n.kind != token::RBRACK) {
        instr* instrs = parse_instr(toks);
        if (instrs) {
            ret.push(instrs);
            free(instrs);
        }
        n = toks->ith(0);
    }
    ret.reverse();
    *toks = toks->tail();
    return ret;
}


instr* parse_instr(toklist* toks) {
    token n = toks->ith(0);
    if (n.kind == token::Return) {
        *toks = toks->tail();
        instr* ret = (instr*)malloc(sizeof(instr));
        ret->kind = instr::Return;
        ret->dat.ret_dat.v = parse_rval(toks);
        n = toks->ith(0);
        if (n.kind != token::Semicol) {
            printf("expected ';' after return instruction; got token %i\n", (int)n.kind);
            exit(-1);
        }
        *toks = toks->tail();
        return ret;
    } else if (n.kind == token::If) {
        *toks = toks->tail();
        instr* ret = (instr*)malloc(sizeof(instr));
        ret->kind = instr::If;
        ret->dat.if_dat.b = parse_rval(toks);
        ret->dat.if_dat.truebrc = parse_instr_block(toks);
        ret->dat.if_dat.falsebrc = old_clist::new_clist(sizeof(instr));
        instr* curr = ret;
        n = toks->ith(0);
        while (n.kind == token::Elif) {
            *toks = toks->tail();
            instr cif;
            cif.kind = instr::If;
            cif.dat.if_dat.b = parse_rval(toks);
            cif.dat.if_dat.truebrc = parse_instr_block(toks);
            cif.dat.if_dat.falsebrc = old_clist::new_clist(sizeof(instr));
            curr->dat.if_dat.falsebrc.push(&cif);
            curr = (instr*)curr->dat.if_dat.falsebrc.ith(0);
            n = toks->ith(0);
        }
        if (n.kind == token::Else) {
            *toks = toks->tail();
            old_clist block = parse_instr_block(toks);
            curr->dat.if_dat.falsebrc.del();
            curr->dat.if_dat.falsebrc = block;
        }
        return ret;
    } else if (n.kind == token::While) {
        *toks = toks->tail();
        instr* ret = (instr*)malloc(sizeof(instr));
        ret->kind = instr::While;
        ret->dat.while_dat.b = parse_rval(toks);
        ret->dat.while_dat.instrs = parse_instr_block(toks);
        return ret;
    }

    toklist left = *toks;
    bool found_par = false;
    while (toks->len()) {
        n = toks->ith(0);
        if (n.kind == token::Semicol) {
            if (left.l == toks->l) {
                return nullptr; // empty intruction
            } else if (found_par) { // found parentheses and no '=', so a function call
                *toks = left;
                // we parse function calls as an rvalue
                instr* ist = (instr*)malloc(sizeof(instr));
                ist->kind = instr::Fcall;
                ist->dat.fcall_dat.call = parse_rval(toks);
                n = toks->ith(0);
                if (n.kind != token::Semicol) {
                    printf("expected ';' after instruction; got token %i\n", (int)n.kind);
                    exit(-1);
                }
                *toks = toks->tail();
                return ist;
            }
            // we have found neither '=' or '(' tokens in our instruction, to it is a declaration
            instr* ist = (instr*)malloc(sizeof(instr));
            ist->kind = instr::Decl;
            ist->dat.decl_dat.d = parse_var_decl(&left, true);
            *toks = left;
            return ist;
        } else if (n.kind == token::Set) { // we have an '=' in our instruction, so it is a set operation (not always true but almost)
            instr* ist = (instr*)malloc(sizeof(instr));
            ist->kind = instr::Set;
            ist->dat.set_dat.l = parse_lval(&left);
            *toks = toks->tail();
            ist->dat.set_dat.r = parse_rval(toks);
            n = toks->ith(0);
            if (n.kind != token::Semicol) {
                printf("expected ';' after instruction; got token %i\n", (int)n.kind);
                exit(-1);
            }
            *toks = toks->tail();
            return ist;
        } else if (n.kind == token::LPAREN) {
            found_par = true;
        }
        *toks = toks->tail();
    }
    printf("instruction not terminated by a semicolon\n");
    exit(-1);
}

decl* parse_fun_decl(toklist* toks) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Func;
    ret->dat.func_dat.ret_t = parse_typ(toks);
    ret->dat.func_dat.args_decls = old_clist::new_clist(sizeof(decl));

    token n = toks->ith(0);
    if (n.kind != token::Ident) {
        printf("expected identifier after type in function declaration");
        exit(-1);
    }
    *toks = toks->tail();
    ret->dat.func_dat.name = n.dat.Ident_dat.str;

    n = toks->ith(0);
    if (n.kind != token::LPAREN) {
        printf("expected identifier after type in function declaration");
        exit(-1);
    }
    *toks = toks->tail();

    n = toks->ith(0);
    while (n.kind != token::RPAREN)
    { // this is absolutely horrendous and will sometime parse nonsense, but it will parse correct function argument
        if (n.kind != token::Comma) {
            decl* arg = parse_var_decl(toks, false);
            ret->dat.func_dat.args_decls.push(arg);
            free(arg);
        } else {
            *toks = toks->tail();
        }
        n = toks->ith(0);
    }
    ret->dat.func_dat.args_decls.reverse();
    *toks = toks->tail();
    n = toks->ith(0);

    if (n.kind == token::Semicol) {
        *toks = toks->tail();
        ret->dat.func_dat.instrs = nullptr;
        return ret;
    }
    ret->dat.func_dat.instrs = (old_clist*)malloc(sizeof(old_clist));
    *ret->dat.func_dat.instrs = parse_instr_block(toks);

    return ret;
}

decl::type_constr parse_type_constructor(toklist* toks) {
    decl::type_constr ret;
    ret.fields = old_clist::new_clist(sizeof(decl));

    token n = toks->ith(0);
    if (n.kind != token::Ident) {
        printf("expected identifier for type constructor declaration\n");
        exit(-1);
    }
    ret.name = n.dat.Ident_dat.str;
    *toks = toks->tail();
    
    n = toks->ith(0);
    if (n.kind == token::Semicol) {
        *toks = toks->tail();
        return ret;
    }

    if (n.kind != token::LBRACK) {
        printf("expected '{' for type constructor declaration\n");
        exit(-1);
    }
    *toks = toks->tail();

    n = toks->ith(0);
    while (toks->ith(0).kind != token::RBRACK)
    {
        n = toks->ith(0);
        decl* d = parse_decl(toks);
        ret.fields.push(d);
        free(d);
        n = toks->ith(0);
    }
    *toks = toks->tail();
    n = toks->ith(0);
    if (n.kind != token::Semicol) {
        printf("expected ';' at end of type constructor declaration\n");
        exit(-1);
    }
    *toks = toks->tail();
    ret.fields.reverse();
    return ret;
}

decl* parse_type_decl(toklist* toks) {
    decl* ret = (decl*)malloc(sizeof(decl));
    ret->kind = decl::Type;
    ret->dat.type_dat.constrs = old_clist::new_clist(sizeof(decl::type_constr));
    ret->dat.type_dat.other_decls = old_clist::new_clist(sizeof(decl));
    token n = toks->ith(0);
    if (n.kind == token::Ident) {
        ret->dat.type_dat.name = n.dat.Ident_dat.str;
        *toks = toks->tail();
    } else if (n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Lt) {
        // declaration is a templated type
        *toks = toks->tail();
        ret->kind = decl::Templated;
        n = toks->ith(0);
        if (n.kind != token::Ident) {
            printf("expected identifier as template parameter, got token id %d\n", (int)n.kind);
            exit(-1);
        }
        ret->dat.templated_dat.param_name = n.dat.Ident_dat.str;
        *toks = toks->tail();
        n = toks->ith(0);
        if (!(n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Gt)) {
            printf("expected '>' after template parameter, got token id %d\n", (int)n.kind);
            exit(-1);
        }
        *toks = toks->tail();
        ret->dat.templated_dat.d = parse_type_decl(toks);
        if (ret->dat.templated_dat.d->kind == decl::Type) {
            ret->dat.templated_dat.name = ret->dat.templated_dat.d->dat.type_dat.name;
        } else if (ret->dat.templated_dat.d->kind == decl::Templated) {
            ret->dat.templated_dat.name = ret->dat.templated_dat.d->dat.templated_dat.name;
        } else {
            printf("kind of templated type unsupported (id %d)\n", (int)ret->dat.templated_dat.d->kind);
            exit(-1);
        }
        printf("templated type %s parsed\n", ret->dat.templated_dat.name);
        return ret;
    } else {
        ret->dat.type_dat.name = nullptr;
    }
    n = toks->ith(0);
    if (n.kind != token::LBRACK) {
        printf("expected '{' for type declaration\n");
        exit(-1);
    }
    *toks = toks->tail();
    n = toks->ith(0);
    while (toks->ith(0).kind != token::RBRACK)
    {
        n = toks->ith(0);
        token n2 = toks->ith(1);
        if (n2.kind != token::Semicol && n2.kind != token::LBRACK) { // declaration inside our type
            decl* d = parse_decl(toks);
            ret->dat.type_dat.other_decls.push(d);
            free(d);
        } else {
            decl::type_constr constr = parse_type_constructor(toks);
            ret->dat.type_dat.constrs.push(&constr);
        }
        n = toks->ith(0);
    }
    *toks = toks->tail();
    ret->dat.type_dat.constrs.reverse();
    ret->dat.type_dat.other_decls.reverse();

    if (!ret->dat.type_dat.constrs.len()) {
        decl::type_constr unit;
        unit.fields = old_clist::new_clist(sizeof(decl));
        unit.name = "_";
        ret->dat.type_dat.constrs.push(&unit);
    }

    return ret;
}

decl* parse_decl(toklist* toks) {
    token n = toks->ith(0);
    if (n.kind == token::Static) {
        *toks = toks->tail();
        decl* ret = (decl*)malloc(sizeof(decl));
        ret->kind = decl::Static;
        ret->dat.static_dat.d = parse_decl(toks);
        return ret;
    } else if (n.kind == token::Type) {
        *toks = toks->tail();
        return parse_type_decl(toks);
    } else if (n.kind == token::Func) {
        *toks = toks->tail();
        return parse_fun_decl(toks);
    } else if (n.kind == token::Specialize) {
        decl* ret = (decl*)malloc(sizeof(decl));
        // declaration of a specialization
        *toks = toks->tail();
        ret->kind = decl::Specialize;
        n = toks->ith(0);
        if (n.kind != token::Ident) {
            printf("expected identifier for specialized type, got token id %d\n", (int)n.kind);
            exit(-1);
        }
        ret->dat.specialize_dat.templated_t = n.dat.Ident_dat.str;
        *toks = toks->tail();
        n = toks->ith(0);
        if (!(n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Lt)) {
            printf("expected '<' for template specialization, got token id %d\n", (int)n.kind);
            exit(-1);
        }
        *toks = toks->tail();
        ret->dat.specialize_dat.param = parse_typ(toks);
        n = toks->ith(0);
        if (!(n.kind == token::Binop && n.dat.Binop_dat.op.kind == binop::Gt)) {
            printf("expected '>' after template parameter, got token id %d\n", (int)n.kind);
            exit(-1);
        }
        *toks = toks->tail();
        n = toks->ith(0);
        if (!(n.kind == token::As)) {
            printf("expected 'as' after template specialization, got token id %d\n", (int)n.kind);
            exit(-1);
        }
        *toks = toks->tail();
        n = toks->ith(0);
        if (n.kind != token::Ident) {
            printf("expected identifier for specialized type new name, got token id %d\n", (int)n.kind);
            exit(-1);
        }
        ret->dat.specialize_dat.newname = n.dat.Ident_dat.str;
        *toks = toks->tail();
        return ret;
    }
    return parse_var_decl(toks, true);
}

ast parse_file(const char* path);

void parse_aux(toklist toks, ast* ret) {
    while (toks.len()) {
        printf("r:%d\n", toks.len());

        token tok = toks.ith(0);
        if (tok.kind == token::Hashtag) {
            toks = toks.tail();
            tok = toks.ith(0);
            if (tok.kind == token::Include) {
                toks = toks.tail();
                tok = toks.ith(0);
                if (tok.kind != token::VString) {
                    printf("expected string after '#include'\n");
                    exit(-1);
                }
                toks = toks.tail();
                // we parse the file as if it was copy-pasted in this one
                toklist toks = lex_file(tok.dat.VString_dat.str);
                parse_aux(toks, ret);
                toks.del(); // yes this is a memory leak
            } else {
                if (tok.kind != token::Include_C) {
                    printf("expected include_C after '#'\n");
                    exit(-1);
                }
                toks = toks.tail();
                tok = toks.ith(0);
                decl* d = (decl*)malloc(sizeof(decl));
                d->kind = decl::Include_C;
                if (tok.kind != token::VString) {
                    printf("expected string after '#include_C'\n");
                    exit(-1);
                }
                d->dat.include_dat.file = tok.dat.VString_dat.str;
                toks = toks.tail();
                ret->decls.push(d);
            }
        } else if (tok.kind == token::Nothing) {
            toks = toks.tail();
        } else {
            decl* d = parse_decl(&toks);
            ret->decls.push(d);
            free(d);
        }
    }
}

ast parse(toklist toks) {
    ast ret = {.decls = old_clist::new_clist(sizeof(decl))};
    parse_aux(toks, &ret);
    ret.decls.reverse();
    return ret;
}
