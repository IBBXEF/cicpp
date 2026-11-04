
#pragma once

#include <stdio.h>
#include "utils.cpp"

const int ident_lvl = 2;
void print_n_spaces(int n, FILE* fptr) {
    for (int i = 0; i < n; i++) {
        fprintf(fptr, " ");
    }
}



struct rval;
struct typ;

struct lval
{
    enum {
        Var,
        Index,
        Field
    } kind;

    union
    {
        const char* var_dat;
        struct { rval* arr; rval* ind; } ind_dat;
        struct { rval* stru; const char* field; } field_dat;
    } dat;

    void print_to_file(FILE* fptr);
};


struct rval
{
    enum {
        Lval,
        Int,
        String,
        Binop,
        Unop,
        Fcall,
        Typecast
    } kind;

    union {
        lval* lval_dat;
        int int_dat;
        const char* string_dat;
        struct { rval* v1; binop op; rval* v2; } binop_dat;
        struct { unop op; rval* v; } unop_dat;
        struct { rval* func; old_clist args; } fcall_dat;
        struct { typ* t; rval* v; } typecast_dat;
    } dat;

    void print_to_file(FILE* fptr);
};


struct typ
{
    enum {
        TVoid,
        TInt,
        TChar,
        TPtr,
        TConst,
        TIdent,
        Typeof,
        Tfunptr
    } kind;

    union {
        typ* ptr_dat;
        typ* const_dat;
        const char* TIdent_dat;
        rval* typeof_dat;
        struct { typ* ret_t; old_clist args_t; } tfunptr_dat;
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
        } else if (kind == Typeof) {
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "typeof(");
            dat.typeof_dat->print_to_file(fptr);
            fprintf(fptr, ")");
        } else if (kind == TIdent) {
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "%s", dat.TIdent_dat);
        } else if (kind == TConst) {
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "const ");
            dat.const_dat->print_to_file(fptr, 0);
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
    } else if (kind == Field) {
        fprintf(fptr, "(");
        dat.field_dat.stru->print_to_file(fptr);
        fprintf(fptr, ").%s", dat.field_dat.field);
    }
}

void rval::print_to_file(FILE* fptr) {
    if (kind == Int) {
        fprintf(fptr, "%i", dat.int_dat);
    } else if (kind == String) {
        fprintf(fptr, "\"%s\"", dat.string_dat);
    } else if (kind == Typecast) {
        fprintf(fptr, "(");
        dat.typecast_dat.t->print_to_file(fptr, 0);
        fprintf(fptr, ")");
        dat.typecast_dat.v->print_to_file(fptr);
    } else if (kind == Lval) {
        dat.lval_dat->print_to_file(fptr);
    } else if (kind == Binop) {
        fprintf(fptr, "(");
        dat.binop_dat.v1->print_to_file(fptr);
        fprintf(fptr, ")");
        if (dat.binop_dat.op.kind == binop::Eq) {
            fprintf(fptr, " == ");
        } else if (dat.binop_dat.op.kind == binop::Neq) {
            fprintf(fptr, " != ");
        } else if (dat.binop_dat.op.kind == binop::Lt) {
            fprintf(fptr, " < ");
        } else if (dat.binop_dat.op.kind == binop::Leq) {
            fprintf(fptr, " <= ");
        } else if (dat.binop_dat.op.kind == binop::Gt) {
            fprintf(fptr, " > ");
        } else if (dat.binop_dat.op.kind == binop::Geq) {
            fprintf(fptr, " >= ");
        } else if (dat.binop_dat.op.kind == binop::Div) {
            fprintf(fptr, " / ");
        } else if (dat.binop_dat.op.kind == binop::Mul) {
            fprintf(fptr, " * ");
        } else if (dat.binop_dat.op.kind == binop::Sub) {
            fprintf(fptr, " - ");
        } else if (dat.binop_dat.op.kind == binop::Add) {
            fprintf(fptr, " + ");
        }
        if (dat.binop_dat.op.kind == binop::Arrow) {
            fprintf(fptr, "->");
            dat.binop_dat.v2->print_to_file(fptr);
        } else {
            fprintf(fptr, "(");
            dat.binop_dat.v2->print_to_file(fptr);
            fprintf(fptr, ")");
        }
    } else if (kind == Unop) {
        if (dat.unop_dat.op.kind == unop::Lnot) {
            fprintf(fptr, "!(");
        } else if (dat.unop_dat.op.kind == unop::Neg) {
            fprintf(fptr, "-(");
        } else if (dat.unop_dat.op.kind == unop::Addr) {
            fprintf(fptr, "&(");
        }
        dat.unop_dat.v->print_to_file(fptr);
        fprintf(fptr, ")");
    } else if (kind == Fcall) {
        dat.fcall_dat.func->print_to_file(fptr);
        fprintf(fptr, "(");
        for (int i = 0; i < dat.fcall_dat.args.len(); i++) {
            if (i) {
                fprintf(fptr, ", ");
            }
            ((rval*)dat.fcall_dat.args.ith(i))->print_to_file(fptr);
        }
        fprintf(fptr, ")");
    }
}

struct ast;

struct decl
{
    struct type_constr {
        const char* name;
        old_clist fields; // list of declarations
    };
    

    enum { Var, Func, Type, Include_C, Static, Templated, Specialize } kind;

    union {
        struct { const char* name; typ* t; rval* v; } var_dat;
        struct { const char* name; typ* ret_t;
                 old_clist args_decls; old_clist* instrs; }  func_dat; // if instrs is nullptr, it is a function prototype
        struct { const char* name; old_clist constrs;
                 old_clist other_decls;               }  type_dat;
        struct { const char* file; }              include_dat;
        struct { decl* d; }              static_dat;
        struct { decl* d; const char* param_name; const char* name; } templated_dat;
        struct { const char* templated_t; typ* param; const char* newname; } specialize_dat;
    } dat;

    void print_to_file(FILE* fptr, int ident, ast* prog, bool print_decl_end);
};


struct ast
{
    old_clist decls; // list of declarations
    void print_to_file(FILE* fptr);
};


struct instr
{
    enum { Set, Return, If, While, Decl, Fcall } kind;

    union {
        struct { lval* l; rval* r; }                      set_dat;
        struct { rval* v; }                               ret_dat;
        struct { rval* b; old_clist truebrc; old_clist falsebrc; } if_dat;
        struct { rval* b; old_clist instrs; }               while_dat;
        struct { decl* d; }                              decl_dat;
        struct { rval* call; }                          fcall_dat;
    } dat;

    void print_to_file(FILE* fptr, int ident, ast* prog) {
        if (kind == Set) {
            print_n_spaces(ident * ident_lvl, fptr);
            dat.set_dat.l->print_to_file(fptr);
            fprintf(fptr, " = ");
            dat.set_dat.r->print_to_file(fptr);
            fprintf(fptr, ";\n");
        } else if (kind == Return) {
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "return ");
            dat.ret_dat.v->print_to_file(fptr);
            fprintf(fptr, ";\n");
        } else if (kind == Decl) {
            dat.decl_dat.d->print_to_file(fptr, ident, prog, true);
        } else if (kind == Fcall) {
            print_n_spaces(ident * ident_lvl, fptr);
            dat.fcall_dat.call->print_to_file(fptr);
            fprintf(fptr, ";\n");
        } else if (kind == If) {
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "if (");
            dat.if_dat.b->print_to_file(fptr);
            fprintf(fptr, ") {\n");
            for (int i = 0; i < dat.if_dat.truebrc.len(); i++) {
                instr* ist = (instr*)dat.if_dat.truebrc.ith(i);
                ist->print_to_file(fptr, ident+1, prog);
            }
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "}");
            if (dat.if_dat.falsebrc.len() == 1) {
                fprintf(fptr, " else\n");
                ((instr*)dat.if_dat.falsebrc.ith(0))->print_to_file(fptr, ident+1, prog);
            } else if (dat.if_dat.falsebrc.len() > 1) {
                fprintf(fptr, " else {\n");
                for (int i = 0; i < dat.if_dat.truebrc.len(); i++) {
                    instr* ist = (instr*)dat.if_dat.truebrc.ith(i);
                    ist->print_to_file(fptr, ident+1, prog);
                }
                print_n_spaces(ident * ident_lvl, fptr);
                fprintf(fptr, "}\n");
            } else {
                fprintf(fptr, "\n");
            }
        } else if (kind == While) {
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "while (");
            dat.while_dat.b->print_to_file(fptr);
            fprintf(fptr, ") {\n");
            for (int i = 0; i < dat.while_dat.instrs.len(); i++) {
                instr* ist = (instr*)dat.while_dat.instrs.ith(i);
                ist->print_to_file(fptr, ident+1, prog);
            }
            print_n_spaces(ident * ident_lvl, fptr);
            fprintf(fptr, "}\n");
        }
        
    }
};

void decl::print_to_file(FILE* fptr, int ident, ast* prog, bool print_decl_end = true) {
    if (kind == Templated) {
        // we do nothing, a template alone does not count as a type
    } else if (kind == Specialize) {
        decl* templated_decl = nullptr;
        for (int i = 0; i < prog->decls.len(); i++) {
            decl* cur = (decl*)prog->decls.ith(i);
            if (cur->kind == decl::Templated) {
                if (!strcmp(cur->dat.templated_dat.name, dat.specialize_dat.templated_t)) {
                    templated_decl = cur;
                }
            }
        }
        if (!templated_decl) {
            printf("templated type \"%s\" is not defined\n", dat.specialize_dat.templated_t);
            exit(-1);
        }
        print_n_spaces(ident * ident_lvl, fptr);
        fprintf(fptr, "#define %s ", templated_decl->dat.templated_dat.param_name);
        dat.specialize_dat.param->print_to_file(fptr, 0);
        fprintf(fptr, "\n");

        print_n_spaces(ident * ident_lvl, fptr);
        fprintf(fptr, "#define %s %s\n", templated_decl->dat.templated_dat.name, dat.specialize_dat.newname);


        templated_decl->dat.templated_dat.d->print_to_file(fptr, ident, prog);

        print_n_spaces(ident * ident_lvl, fptr);
        fprintf(fptr, "#undef %s\n", templated_decl->dat.templated_dat.param_name);
        print_n_spaces(ident * ident_lvl, fptr);
        fprintf(fptr, "#undef %s\n", templated_decl->dat.templated_dat.name);
    } else if (kind == Include_C) {
        print_n_spaces(ident * ident_lvl, fptr);
        if (dat.include_dat.file[0] == '.' && dat.include_dat.file[1] == '/') {
            fprintf(fptr, "#include \"%s\"\n", dat.include_dat.file+2);
        } else {
            fprintf(fptr, "#include <%s>\n", dat.include_dat.file);
        }
    } else if (kind == Static) {
        print_n_spaces(ident * ident_lvl, fptr);
        fprintf(fptr, "static\n");
        dat.static_dat.d->print_to_file(fptr, ident, prog);
    } else if (kind == Var) {
        if (dat.var_dat.t->kind == typ::Tfunptr) { // our variable is a function pointer
            dat.var_dat.t->dat.tfunptr_dat.ret_t->print_to_file(fptr, ident);
            fprintf(fptr, " (*%s)(", dat.var_dat.name);
            for (int i = 0; i < dat.var_dat.t->dat.tfunptr_dat.args_t.len(); i++) {
                if (i) {
                    fprintf(fptr, ", ");
                }
                typ* t = (typ*)dat.var_dat.t->dat.tfunptr_dat.args_t.ith(i);
                t->print_to_file(fptr, 0);
            }
            fprintf(fptr, ");\n");
        } else {
            dat.var_dat.t->print_to_file(fptr, ident);
            fprintf(fptr, " %s", dat.var_dat.name);
            if (dat.var_dat.v) {
                fprintf(fptr, " = ");
                dat.var_dat.v->print_to_file(fptr);
            }
            if (print_decl_end) {
                fprintf(fptr, ";\n");
            }
        }
    } else if (kind == Func) {
        print_n_spaces(ident * ident_lvl, fptr);
        dat.func_dat.ret_t->print_to_file(fptr, 0);
        fprintf(fptr, " %s(", dat.func_dat.name);
        for (int i = 0; i < dat.func_dat.args_decls.len(); i++) {
            decl* d = (decl*)dat.func_dat.args_decls.ith(i);
            d->print_to_file(fptr, 0, prog, false);
            if (i != dat.func_dat.args_decls.len() - 1) {
                fprintf(fptr, ", ");
            }
        }
        fprintf(fptr, ")");
        
        if (dat.func_dat.instrs) {
            fprintf(fptr, "{\n");
            for (int i = 0; i < dat.func_dat.instrs->len(); i++) {
                instr* ins = (instr*)dat.func_dat.instrs->ith(i);
                ins->print_to_file(fptr, ident+1, prog);
            }
            print_n_spaces(ident * ident_lvl, fptr);
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

        if (!(dat.type_dat.constrs.len() == 1 && !strcmp(((type_constr*)dat.type_dat.constrs.ith(0))->name, "_")))
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
                        d->print_to_file(fptr, ident + 3, prog);
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
            d->print_to_file(fptr, ident + 1, prog);
        }
        
        print_n_spaces(ident * ident_lvl, fptr);
        fprintf(fptr, "};\n");
    }
}



void ast::print_to_file(FILE* fptr) {
    fprintf(fptr, "#pragma once\n");

    for (int i = 0; i < decls.len(); i++)
    {
        decl* d = (decl*)decls.ith(i);
        d->print_to_file(fptr, 0, this);
    }
}
