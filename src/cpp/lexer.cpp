
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

        Struct,
        Enum,
        Union,

        LPAREN,
        RPAREN,
        LSQUAR,
        RSQUAR,
        LBRACK,
        RBRACK,
        
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




// details of the state machine used to do the lexing


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
    } else if (!strncmp("struct", str, *cou) && *cou == 6) {
        tok.kind = token::Struct;
    } else if (!strncmp("enum", str, *cou) && *cou == 4) {
        tok.kind = token::Enum;
    } else if (!strncmp("union", str, *cou) && *cou == 5) {
        tok.kind = token::Union;
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



struct lexing_state { enum T {
    LEXING_IDENT_OR_INT,
    LEXING_STRING,
    LEXING_STRING_SPECIAL
}; };


void lexing_step(int* cou, clist* ret, char c, char* last_buffer, lexing_state::T* state) {
    if (*state == lexing_state::LEXING_STRING) {
        last_buffer[*cou] = c;
        *cou = *cou + 1;
        if (c == '\\') {
            *state = lexing_state::LEXING_STRING_SPECIAL;
        } else if (c == '"')
        {
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
    } else if (c == '"') {
        pop_token_stack(cou, ret, last_buffer);
        *state = lexing_state::LEXING_STRING;
    } else {
        printf("unexpected character: %c (code: %d).\n", c, (int)c);
        exit(-1);
    }
}


clist lex_file(const char* path) {
    FILE* fptr = fopen(path, "r");
    if (!fptr) {
        printf("file.txt file failed to open.\n");
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
