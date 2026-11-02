
#pragma once

#include <stdio.h>

int ident_lvl = 2;
void print_n_spaces(int n, FILE* fptr) {
    for (int i = 0; i < n; i++) {
        fprintf(fptr, " ");
    }
}

struct rval;

struct lval
{
    enum {
        Var,
        Index
    } kind;

    union
    {
        const char* var_dat;
        struct { rval* arr; rval* ind; } ind_dat;
    } dat;

    void print_to_file(FILE* fptr);
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
        } else if (kind == Lval) {
            dat.lval_dat->print_to_file(fptr);
        }
    }
};

void lval::print_to_file(FILE* fptr) {
    if (kind == Var) {
        fprintf(fptr, "%s", dat.var_dat);
    } else if (kind == Index) {
        dat.ind_dat.arr->print_to_file(fptr);
        fprintf(fptr, "[");
        dat.ind_dat.ind->print_to_file(fptr);
        fprintf(fptr, "]");
    }
}

struct typ
{
    enum {
        TVoid,
        TInt,
        TChar,
        TPtr,
        TConst
    } kind;

    union {
        typ* ptr_dat;
        typ* const_dat;
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
        } else if (kind == TConst) {
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "const ");
            dat.const_dat->print_to_file(fptr, 0);
        }
    }
};


struct instr
{
    enum { Set } kind;

    union {
        struct { lval* l; rval* r; } set_dat;
    } dat;

    void print_to_file(FILE* fptr, int ident) {
        if (kind == Set) {
            print_n_spaces(ident * ident_lvl, fptr);
            dat.set_dat.l->print_to_file(fptr);
            fprintf(fptr, " = ");
            dat.set_dat.r->print_to_file(fptr);
            fprintf(fptr, ";\n");
        }
    }
};


struct decl
{
    struct type_constr {
        const char* name;
        clist fields; // list of declarations
    };
    

    enum { Var, Func, Type, Include } kind;

    union {
        struct { const char* name; typ* t; rval* v; } var_dat;
        struct { const char* name; typ* ret_t;
                 clist args_decls; clist* instrs; }  func_dat; // if instrs is nullptr, it is a function prototype
        struct { const char* name; clist constrs;
                 clist other_decls;               }  type_dat;
        struct { const char* file; }              include_dat;
    } dat;

    void print_to_file(FILE* fptr, int ident, bool print_decl_end = true) {
        if (kind == Include) {
            print_n_spaces(ident * ident_lvl, fptr);
            if (dat.include_dat.file[0] == '.' && dat.include_dat.file[1] == '/') {
                fprintf(fptr, "#include \"%s\"\n", dat.include_dat.file+2);
            } else {
                fprintf(fptr, "#include <%s>\n", dat.include_dat.file);
            }
        } else if (kind == Var) {
            dat.var_dat.t->print_to_file(fptr, ident);
            fprintf(fptr, " %s", dat.var_dat.name);
            if (dat.var_dat.v) {
                fprintf(fptr, " = ");
                dat.var_dat.v->print_to_file(fptr);
            }
            if (print_decl_end) {
                fprintf(fptr, ";\n");
            }
        } else if (kind == Func) {
            print_n_spaces(ident * ident_lvl, fptr);
            dat.func_dat.ret_t->print_to_file(fptr, ident);
            fprintf(fptr, " %s(", dat.func_dat.name);
            for (int i = 0; i < dat.func_dat.args_decls.len(); i++) {
                decl* d = (decl*)dat.func_dat.args_decls.ith(i);
                d->print_to_file(fptr, 0, false);
                if (i != dat.func_dat.args_decls.len() - 1) {
                    fprintf(fptr, ", ");
                }
            }
            fprintf(fptr, ")");
            
            if (dat.func_dat.instrs) {
                fprintf(fptr, "{\n");
                for (int i = 0; i < dat.func_dat.instrs->len(); i++) {
                    instr* ins = (instr*)dat.func_dat.instrs->ith(i);
                    ins->print_to_file(fptr, ident+1);
                }
                fprintf(fptr, "}\n");
            } else {
                fprintf(fptr, ";\n");
            }
        } else if (kind == Type) {
            print_n_spaces(ident * ident_lvl, fptr);
            if (dat.type_dat.name) {
                fprintf(fptr, "struct %s {\n", dat.type_dat.name);
            } else {
                fprintf(fptr, "struct {\n");
            }

            if (dat.type_dat.constrs.len() != 1)
            {
                print_n_spaces((ident+1) * ident_lvl, fptr);
                fprintf(fptr, "enum { ");
                for (int i = 0; i < dat.type_dat.constrs.len(); i++) {
                    fprintf(fptr, "%s", ((type_constr*)dat.type_dat.constrs.ith(i))->name);
                    if (i < dat.type_dat.constrs.len()-1) {
                        fprintf(fptr, ", ");
                    }                    
                }
                fprintf(fptr, " } kind;\n");
            }
            bool has_nonempty_constrs = false;
            for (int i = 0; i < dat.type_dat.constrs.len(); i++) {
                type_constr* constr = (type_constr*)dat.type_dat.constrs.ith(i);
                if (constr->fields.len()) {
                    has_nonempty_constrs = true;
                }
            }

            if (has_nonempty_constrs) {
                print_n_spaces((ident+1) * ident_lvl, fptr);
                fprintf(fptr, "union {\n");
                for (int i = 0; i < dat.type_dat.constrs.len(); i++) {
                    type_constr* constr = (type_constr*)dat.type_dat.constrs.ith(i);
                    if (constr->fields.len()) {
                        print_n_spaces((ident+2) * ident_lvl, fptr);
                        fprintf(fptr, "struct {\n");
                        for (int i = 0; i < constr->fields.len(); i++) {
                            decl* d = (decl*)constr->fields.ith(i);
                            d->print_to_file(fptr, ident + 3);
                        }
                        print_n_spaces((ident+2) * ident_lvl, fptr);
                        fprintf(fptr, "} %s_dat;\n", constr->name);
                    }
                }
                print_n_spaces((ident+1) * ident_lvl, fptr);
                fprintf(fptr, " } dat;\n");
            }
            
            for (int i = 0; i < dat.type_dat.other_decls.len(); i++)
            {
                decl* d = (decl*)dat.type_dat.other_decls.ith(i);
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

