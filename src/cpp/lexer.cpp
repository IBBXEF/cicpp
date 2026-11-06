
#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.cpp"
#include "parser.c"


void pop_token_stack(int* cou, toklist* l, char* str) {
    if (!*cou) { return; }
    str[*cou] = '\0';
    
    token tok;
    if (!strncmp("void", str, *cou) && *cou == 4) {
        tok.kind = token::TVoid;
    } else if (!strncmp("int", str, *cou) && *cou == 3) {
        tok.kind = token::TInt;
    } else if (!strncmp("char", str, *cou) && *cou == 4) {
        tok.kind = token::TChar;
    } else if (!strncmp("if", str, *cou) && *cou == 2) {
        tok.kind = token::If;
    } else if (!strncmp("elif", str, *cou) && *cou == 4) {
        tok.kind = token::Elif;
    } else if (!strncmp("else", str, *cou) && *cou == 4) {
        tok.kind = token::Else;
    } else if (!strncmp("return", str, *cou) && *cou == 6) {
        tok.kind = token::Return;
    } else if (!strncmp("while", str, *cou) && *cou == 5) {
        tok.kind = token::While;
    } else if (!strncmp("type", str, *cou) && *cou == 4) {
        tok.kind = token::Type;
    } else if (!strncmp("func", str, *cou) && *cou == 4) {
        tok.kind = token::Func;
    } else if (!strncmp("static", str, *cou) && *cou == 6) {
        tok.kind = token::Static;
    } else if (!strncmp("specialize", str, *cou) && *cou == 10) {
        tok.kind = token::Specialize;
    } else if (!strncmp("typeof", str, *cou) && *cou == 6) {
        tok.kind = token::Typeof;
    } else if (!strncmp("const", str, *cou) && *cou == 5) {
        tok.kind = token::Const;
    } else if (!strncmp("as", str, *cou) && *cou == 2) {
        tok.kind = token::As;
    } else if (!strncmp("include", str, *cou) && *cou == 7) {
        tok.kind = token::Include;
    } else if (!strncmp("include_C", str, *cou) && *cou == 9) {
        tok.kind = token::Include_C;
    } else if (!strncmp("include_c", str, *cou) && *cou == 9) {
        tok.kind = token::Include_C;
    } else if (*str >= '0' && *str <= '9') {
        tok.kind = token::VInt;
        char* end;
        tok.dat.VInt_dat.dat = strtol(str, &end, 10);
        if (end != str + *cou) {
            printf("invalid integer: %s\n", str);
            exit(-1);
        }
    } else {
        tok.kind = token::Ident;
        char* tmp = (char*)malloc(*cou+1);
        strncpy(tmp, str, *cou);
        tmp[*cou] = '\0';
        tok.dat.Ident_dat.str = tmp;
    }

    l->append(tok);
    *cou = 0;
}


// details of the state machine used to do the lexing
struct lexing_state { enum T {
    LEXING_IDENT_OR_INT,
    LEXING_STRING,
    LEXING_STRING_SPECIAL,
    LINE_COMMENT,
    LEXING_CHAR,
    LEXING_CHAR_SPECIAL,
}; };


void lexing_step(int* cou, toklist* ret, char c, char* last_buffer, lexing_state::T* state) {
    if (*state == lexing_state::LEXING_STRING) {
        last_buffer[*cou] = c;
        *cou = *cou + 1;
        if (c == '\\') {
            *state = lexing_state::LEXING_STRING_SPECIAL;
        } else if (c == '"') {
            char* tmp = (char*)malloc(*cou);
            strncpy(tmp, last_buffer, *cou-1);
            tmp[*cou-1] = '\0';
            token tok {.kind=token::VString};
            tok.dat.VString_dat.str = tmp;

            ret->append(tok);

            *cou = 0;
            *state = lexing_state::LEXING_IDENT_OR_INT;
        }
        return;
    } else if (*state == lexing_state::LEXING_STRING_SPECIAL) {
        last_buffer[*cou] = c;
        *cou = *cou + 1;
        *state = lexing_state::LEXING_STRING;
        return;
    } else if (*state == lexing_state::LINE_COMMENT) {
        if (c == '\n') {
            *state = lexing_state::LEXING_IDENT_OR_INT;
        }
        return;
    } else if (*state == lexing_state::LEXING_CHAR) {
        if (c == '\\') {
            *cou = 0;
            *state = lexing_state::LEXING_CHAR_SPECIAL;
        } else if (*cou == 1) {
            if (c != '\'')
            {
                printf("immediate character value must be exactly one character long: found %c instead of '\n", c);
                exit(-1);
            }
            
            token tok {.kind=token::VInt}; // we lex chars as ints
            tok.dat.VInt_dat.dat = last_buffer[0];

            ret->append(tok);

            *cou = 0;
            *state = lexing_state::LEXING_IDENT_OR_INT;
        } else {
            last_buffer[*cou] = c;
            *cou = *cou + 1;
        }
        return;
    } else if (*state == lexing_state::LEXING_CHAR_SPECIAL) {
        if (*cou == 1) {
            if (c != '\'')
            {
                printf("special immediate character value must be exactly one character long: found %c instead of '\n", c);
                exit(-1);
            }
            
            token tok {.kind=token::VInt}; // we lex chars as ints

            if (last_buffer[0] == 'n') {
                tok.dat.VInt_dat.dat = '\n';
            } else if (last_buffer[0] == 't') {
                tok.dat.VInt_dat.dat = '\t';
            } else if (last_buffer[0] == '0') {
                tok.dat.VInt_dat.dat = '\0';
            } else {
                tok.dat.VInt_dat.dat = last_buffer[0];
            }

            ret->append(tok);

            *cou = 0;
            *state = lexing_state::LEXING_IDENT_OR_INT;
        } else {
            last_buffer[*cou] = c;
            *cou = *cou + 1;
        }
        return;
    }
    
    
    token* n;
    if (c == ' ' || c == '\n' || c == '\t') {
        pop_token_stack(cou, ret, last_buffer);
    } else if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
        last_buffer[*cou] = c; // buffer overflow protection is for losers
        *cou = *cou + 1;
    } else if (c == ';') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Semicol};
        ret->append(tok);
    } else if (c == ',') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Comma};
        ret->append(tok);
    } else if (c == '.') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Dot};
        ret->append(tok);
    } else if (c == '#') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Hashtag};
        ret->append(tok);
    } else if (c == '<') {
        pop_token_stack(cou, ret, last_buffer);
        token tok;
        tok.kind = token::Binop;
        tok.dat.Binop_dat.op.kind = binop::Lt;
        ret->append(tok);
    } else if (c == '>') {
        pop_token_stack(cou, ret, last_buffer);
        n = ret->ith_ref(ret->len()-1);
        if (n->kind == token::Binop && n->dat.Binop_dat.op.kind == binop::Sub) { // last token was an '-'
            n->dat.Binop_dat.op.kind = binop::Arrow;
        } else {
            token tok;
            tok.kind = token::Binop;
            tok.dat.Binop_dat.op.kind = binop::Gt;
            ret->append(tok);
        }
    } else if (c == '(') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::LPAREN};
        ret->append(tok);
    } else if (c == ')') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::RPAREN};
        ret->append(tok);
    } else if (c == '[') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::LSQUAR};
        ret->append(tok);
    } else if (c == ']') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::RSQUAR};
        ret->append(tok);
    } else if (c == '{') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::LBRACK};
        ret->append(tok);
    } else if (c == '}') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::RBRACK};
        ret->append(tok);
    } else if (c == '=') {
        pop_token_stack(cou, ret, last_buffer);
        n = ret->ith_ref(ret->len()-1);
        if (n->kind == token::Set) { // last token was an '='
            n->kind = token::Binop;
            n->dat.Binop_dat.op.kind = binop::Eq;
        } else if (n->kind == token::Unop && n->dat.Unop_dat.op.kind == unop::Lnot) { // last token was an '!'
            n->kind = token::Binop;
            n->dat.Binop_dat.op.kind = binop::Neq;
        } else if (n->kind == token::Binop && n->dat.Binop_dat.op.kind == binop::Lt) { // last token was an '<'
            n->dat.Binop_dat.op.kind = binop::Leq;
        } else if (n->kind == token::Binop && n->dat.Binop_dat.op.kind == binop::Gt) { // last token was an '>'
            n->dat.Binop_dat.op.kind = binop::Geq;
        } else {
            token tok = {.kind = token::Set};
            ret->append(tok);
        }
    } else if (c == ':') {
        pop_token_stack(cou, ret, last_buffer);
        n = ret->ith_ref(ret->len()-1);
        if (n->kind == token::Colon) { // last token was an ':'
            n->kind = token::TwoColon;
        } else {
            token tok = {.kind = token::Colon};
            ret->append(tok);
        }
    } else if (c == '&') {
        pop_token_stack(cou, ret, last_buffer);
        n = ret->ith_ref(ret->len()-1);
        if (n->kind == token::Binop && n->dat.Binop_dat.op.kind == binop::Band) { // last token was an '&'
            n->dat.Binop_dat.op.kind = binop::Land;
        } else {
            token tok;
            tok.kind = token::Binop;
            tok.dat.Binop_dat.op.kind = binop::Band;
            ret->append(tok);
        }
    } else if (c == '|') {
        pop_token_stack(cou, ret, last_buffer);
        n = ret->ith_ref(ret->len()-1);
        if (n->kind == token::Binop && n->dat.Binop_dat.op.kind == binop::Bor) { // last token was an '|'
            n->dat.Binop_dat.op.kind = binop::Lor;
        } else {
            token tok;
            tok.kind = token::Binop;
            tok.dat.Binop_dat.op.kind = binop::Bor;
            ret->append(tok);
        }
    } else if (c == '!') {
        pop_token_stack(cou, ret, last_buffer);
        token tok;
        tok.kind = token::Unop;
        tok.dat.Unop_dat.op.kind = unop::Lnot;
        ret->append(tok);
    } else if (c == '+') {
        pop_token_stack(cou, ret, last_buffer);
        token tok;
        tok.kind = token::Binop;
        tok.dat.Binop_dat.op.kind = binop::Add;
        ret->append(tok);
    } else if (c == '-') {
        pop_token_stack(cou, ret, last_buffer);
        token tok;
        tok.kind = token::Binop;
        tok.dat.Binop_dat.op.kind = binop::Sub;
        ret->append(tok);
    } else if (c == '*') {
        pop_token_stack(cou, ret, last_buffer);
        token tok;
        tok.kind = token::Binop;
        tok.dat.Binop_dat.op.kind = binop::Mul;
        ret->append(tok);
    } else if (c == '/') {
        pop_token_stack(cou, ret, last_buffer);
        n = ret->ith_ref(ret->len()-1);
        if (n->kind == token::Binop && n->dat.Binop_dat.op.kind == binop::Div) { // last token was an '/'
            ret->reverse(); // we currently don't have a del operation
            ret->pop();
            ret->reverse();
            *state = lexing_state::LINE_COMMENT;
        } else {
            token tok;
            tok.kind = token::Binop;
            tok.dat.Binop_dat.op.kind = binop::Div;
            ret->append(tok);
        }
    } else if (c == '"') {
        pop_token_stack(cou, ret, last_buffer);
        *state = lexing_state::LEXING_STRING;
    } else if (c == '\'') {
        pop_token_stack(cou, ret, last_buffer);
        *state = lexing_state::LEXING_CHAR;
    } else {
        printf("unexpected character: %c (code: %d).\n", c, (int)c);
        exit(-1);
    }
}


toklist lex_string(const char* str) {
    toklist ret;
    ret.init();
    token no;
    no.kind = token::As; // we place a placeholder token that we will remove later
    ret.append(no);
    
    int cou = 0;
    lexing_state::T state = lexing_state::LEXING_IDENT_OR_INT;

    char last_buffer[100];

    char c;
    c = *str;
    while (c && c != EOF)
    {
        lexing_step(&cou, &ret, c, last_buffer, &state);
        str = str + 1;
        c = *str;
    }
    pop_token_stack(&cou, &ret, last_buffer);

    ret.pop(); // we remove the first token, our placeholder
    return ret;
}

toklist lex_file(const char* path) {
    FILE* fptr = fopen(path, "r");
    if (!fptr) {
        printf("%s file failed to open.\n", path);
        exit(-1);
    }

    toklist ret;
    ret.init();
    token no;
    no.kind = token::As; // we place a placeholder token that we will remove later
    ret.append(no);
    
    int cou = 0;
    lexing_state::T state = lexing_state::LEXING_IDENT_OR_INT;

    char last_buffer[100];

    char c;
    c = fgetc(fptr);
    while (c && c != EOF)
    {
        lexing_step(&cou, &ret, c, last_buffer, &state);
        c = fgetc(fptr);
    }
    pop_token_stack(&cou, &ret, last_buffer);

    ret.pop(); // we remove the first token, our placeholder
    return ret;
}


void print_tokens(toklist toks) {
    for (int i = 0; i < toks.len(); i++) {
        token tok = toks.ith(i);

        printf("token kind: %d\n", (int)tok.kind);

        if (tok.kind == token::Ident) {
            printf("    identifier: %s\n", tok.dat.Ident_dat.str);
        } else if (tok.kind == token::VInt) {
            printf("    integer: %d\n", tok.dat.VInt_dat.dat);
        } else if (tok.kind == token::VString) {
            printf("    string: %s\n", tok.dat.VString_dat.str);
        }
    }
}
