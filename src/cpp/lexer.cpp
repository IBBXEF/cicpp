
#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.cpp"

struct token
{
    enum {
        TVoid,
        TInt,
        TChar,

        If,
        Else,
        Return,
        While,

        Const,
        Type,
        Func,

        Include,

        LPAREN,
        RPAREN,
        LSQUAR,
        RSQUAR,
        LBRACK,
        RBRACK,
        
        BAnd,
        BOr,
        LAnd,
        LOr,
        LNot,
        Star,
        Plus,
        Minus,
        Div,

        Eq,
        Leq,
        Geq,
        Lt,
        Gt,

        Comma,
        Semicol,
        Set,
        Colon,
        TwoColon,
        Hashtag,
        Dot,

        VInt,
        VString,

        Ident
    } kind;

    union {
        const char* ident_dat;
        const char* string_dat;
        int vint_dat;
    } dat;
};



void pop_token_stack(int* cou, clist* l, const char* str) {
    if (!*cou) { return; }
    
    token tok;
    if (!strncmp("void", str, *cou) && *cou == 4) {
        tok.kind = token::TVoid;
    } else if (!strncmp("int", str, *cou) && *cou == 3) {
        tok.kind = token::TInt;
    } else if (!strncmp("char", str, *cou) && *cou == 4) {
        tok.kind = token::TChar;
    } else if (!strncmp("if", str, *cou) && *cou == 2) {
        tok.kind = token::If;
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
    } else if (!strncmp("const", str, *cou) && *cou == 5) {
        tok.kind = token::Const;
    } else if (!strncmp("include", str, *cou) && *cou == 7) {
        tok.kind = token::Include;
    } else if (*str >= '0' && *str <= '9') {
        tok.kind = token::VInt;
        char* end;
        tok.dat.vint_dat = strtol(str, &end, 10);
        if (end != str + *cou) {
            printf("invalid integer: %s\n", str);
            exit(-1);
        }
    } else {
        tok.kind = token::Ident;
        char* tmp = (char*)malloc(*cou+1);
        strncpy(tmp, str, *cou);
        tmp[*cou] = '\0';
        tok.dat.ident_dat = tmp;
    }

    l->push(&tok);
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


void lexing_step(int* cou, clist* ret, char c, char* last_buffer, lexing_state::T* state) {
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
            tok.dat.string_dat = tmp;

            ret->push(&tok);

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
            tok.dat.vint_dat = last_buffer[0];

            ret->push(&tok);

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
                tok.dat.vint_dat = '\n';
            } else if (last_buffer[0] == 't') {
                tok.dat.vint_dat = '\t';
            } else if (last_buffer[0] == '0') {
                tok.dat.vint_dat = '\0';
            } else {
                tok.dat.vint_dat = last_buffer[0];
            }

            ret->push(&tok);

            *cou = 0;
            *state = lexing_state::LEXING_IDENT_OR_INT;
        } else {
            last_buffer[*cou] = c;
            *cou = *cou + 1;
        }
        return;
    }
    
    

    if (c == ' ' || c == '\n' || c == '\t') {
        pop_token_stack(cou, ret, last_buffer);
    } else if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
        last_buffer[*cou] = c; // buffer overflow protection is for losers
        *cou = *cou + 1;
    } else if (c == ';') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Semicol};
        ret->push(&tok);
    } else if (c == ',') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Comma};
        ret->push(&tok);
    } else if (c == '.') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Dot};
        ret->push(&tok);
    } else if (c == '#') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Hashtag};
        ret->push(&tok);
    } else if (c == '<') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Lt};
        ret->push(&tok);
    } else if (c == '>') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Gt};
        ret->push(&tok);
    } else if (c == '(') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::LPAREN};
        ret->push(&tok);
    } else if (c == ')') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::RPAREN};
        ret->push(&tok);
    } else if (c == '[') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::LSQUAR};
        ret->push(&tok);
    } else if (c == ']') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::RSQUAR};
        ret->push(&tok);
    } else if (c == '{') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::LBRACK};
        ret->push(&tok);
    } else if (c == '}') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::RBRACK};
        ret->push(&tok);
    } else if (c == '=') {
        pop_token_stack(cou, ret, last_buffer);
        if (ret->len() && ((token*)ret->ith(0))->kind == token::Set) { // last token was an '='
            ((token*)ret->ith(0))->kind = token::Eq;
        } else {
            token tok = {.kind = token::Set};
            ret->push(&tok);
        }
    } else if (c == ':') {
        pop_token_stack(cou, ret, last_buffer);
        if (ret->len() && ((token*)ret->ith(0))->kind == token::Colon) { // last token was an ':'
            ((token*)ret->ith(0))->kind = token::TwoColon;
        } else {
            token tok = {.kind = token::Colon};
            ret->push(&tok);
        }
    } else if (c == '&') {
        pop_token_stack(cou, ret, last_buffer);
        if (ret->len() && ((token*)ret->ith(0))->kind == token::BAnd) { // last token was an '&'
            ((token*)ret->ith(0))->kind = token::LAnd;
        } else {
            token tok = {.kind = token::BAnd};
            ret->push(&tok);
        }
    } else if (c == '|') {
        pop_token_stack(cou, ret, last_buffer);
        if (ret->len() && ((token*)ret->ith(0))->kind == token::BOr) { // last token was an '|'
            ((token*)ret->ith(0))->kind = token::LOr;
        } else {
            token tok = {.kind = token::BOr};
            ret->push(&tok);
        }
    } else if (c == '!') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::LNot};
        ret->push(&tok);
    } else if (c == '+') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Plus};
        ret->push(&tok);
    } else if (c == '-') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Minus};
        ret->push(&tok);
    } else if (c == '*') {
        pop_token_stack(cou, ret, last_buffer);
        token tok = {.kind = token::Star};
        ret->push(&tok);
    } else if (c == '/') {
        pop_token_stack(cou, ret, last_buffer);
        if (ret->len() && ((token*)ret->ith(0))->kind == token::Div) { // last token was an ':'
            free(ret->pop());
            *state = lexing_state::LINE_COMMENT;
        } else {
            token tok = {.kind = token::Div};
            ret->push(&tok);
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


clist lex_file(const char* path) {
    FILE* fptr = fopen(path, "r");
    if (!fptr) {
        printf("%s file failed to open.\n", path);
        exit(-1);
    }

    clist ret = clist::new_clist(sizeof(token));
    
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
    ret.reverse();
    return ret;
}


void print_tokens(clist toks) {
    for (int i = 0; i < toks.len(); i++) {
        token tok = *(token*)toks.ith(i);

        printf("token kind: %d\n", (int)tok.kind);

        if (tok.kind == token::Ident) {
            printf("    identifier: %s\n", tok.dat.ident_dat);
        } else if (tok.kind == token::VInt) {
            printf("    integer: %d\n", tok.dat.vint_dat);
        } else if (tok.kind == token::VString) {
            printf("    string: %s\n", tok.dat.string_dat);
        }
    }
}
