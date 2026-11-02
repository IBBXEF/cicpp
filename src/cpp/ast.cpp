
#pragma once
#include <stdio.h>

void print_n_spaces(int n, FILE* fptr) {
    for (int i = 0; i < n; i++) {
        fprintf(fptr, " ");
    }
}
int ident_lvl = 2;

struct rval;

struct lval
{
    enum {
        Var,
        Index
    } kind;

    union
    {
        char* var_dat;
        struct { rval* arr; rval* ind; } ind_dat;
    } dat;
    
};

struct binop
{
    enum T {Add, Mul, Sub, Div, Band, Bor, Eq, Leq, Lt};
};


struct rval
{
    enum {
        Lval,
        Int,
        Binop
    } kind;

    union {
        lval* lval_dat;
        int int_dat;
        struct { rval* v1; binop::T op; rval* v2; } ind_dat;
    } dat;

    void print_to_file(FILE* fptr) {
        if (kind == Int) {
            fprintf(fptr, "%i", dat.int_dat);
        }
    }
};


struct typ
{
    enum {
        TVoid,
        TInt,
        TChar,
        TPtr
    } kind;

    union {
        typ* ptr_dat;
    } dat;

    void print_to_file(FILE* fptr, int ident) {
        if (kind == TInt) {
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "int");
        } else if (kind == TChar) {
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "char");
        } else if (kind == TVoid) {
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "void");
        } else if (kind == TPtr) {
            dat.ptr_dat->print_to_file(fptr, ident);
            fprintf(fptr, "*");
        }
    }
};


struct decl
{
    enum {Var, Func, Struct, Enum, Union} kind;

    union {
        struct { const char* name; typ* t; rval* v; } var_dat;
        struct { const char* name; clist decls; }  struct_dat;
        struct { const char* name; clist decls; }  union_dat;
        struct { const char* name; clist vlues; }  enum_dat;
    } dat;

    void print_to_file(FILE* fptr, int ident) {
        if (kind == Var) {
            dat.var_dat.t->print_to_file(fptr, ident);
            fprintf(fptr, " %s", dat.var_dat.name);
            if (dat.var_dat.v) {
                fprintf(fptr, " = ");
                dat.var_dat.v->print_to_file(fptr);
            }
            fprintf(fptr, ";\n");
        } else if (kind == Struct) {
            print_n_spaces(ident * ident_lvl, fptr);
            if (dat.struct_dat.name) {
                fprintf(fptr, "struct %s {\n", dat.struct_dat.name);
            } else {
                fprintf(fptr, "struct {\n");
            }
            
            for (int i = 0; i < dat.struct_dat.decls.len(); i++)
            {
                decl* d = (decl*)dat.struct_dat.decls.ith(i);
                d->print_to_file(fptr, ident + 1);
            }
            
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "};\n");
        } else if (kind == Union) {
            print_n_spaces(ident * ident_lvl, fptr);
            if (dat.union_dat.name) {
                fprintf(fptr, "union %s {\n", dat.union_dat.name);
            } else {
                fprintf(fptr, "union {\n");
            }
            
            for (int i = 0; i < dat.union_dat.decls.len(); i++)
            {
                decl* d = (decl*)dat.union_dat.decls.ith(i);
                d->print_to_file(fptr, ident + 1);
            }
            
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "};\n");
        }
    }
};



struct ast
{
    clist decls; // list of declarations
    void print_to_file(FILE* fptr) {
        for (int i = 0; i < decls.len(); i++)
        {
            decl* d = (decl*)decls.ith(i);
            d->print_to_file(fptr, 0);
        }
    }
};

