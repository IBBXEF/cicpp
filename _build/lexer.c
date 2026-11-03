#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.cpp"
struct binop {
  enum { Add, Mul, Sub, Div, Band, Bor, Land, Lor, Eq, Leq, Lt, Neq, Geq, Gt } kind;
};
struct token {
  enum { Nothing, TVoid, TInt, TChar, If, Elif, Else, Return, While, Const, Type, Func, Include, LPAREN, RPAREN, LSQUAR, RSQUAR, LBRACK, RBRACK, Binop, LNot, Comma, Semicol, Set, Colon, TwoColon, Hashtag, Dot, VInt, VString, Ident } kind;
  union {
    struct {
      binop op;
    } Binop_dat;
    struct {
      int dat;
    } VInt_dat;
    struct {
      const char* str;
    } VString_dat;
    struct {
      const char* str;
    } Ident_dat;
   } dat;
};
