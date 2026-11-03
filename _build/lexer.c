#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.cpp"
struct binop {
  enum { Add, Mul, Sub, Div, Band, Bor, Eq, Leq, Lt, Neq, Geq, Gt } kind;
};
struct token {
  enum { TVoid, TInt, TChar, If, Elif, Else, Return, While, Const, Type, Func, Include, LPAREN, RPAREN, LSQUAR, RSQUAR, LBRACK, RBRACK, BAnd, BOr, LAnd, LOr, LNot, Star, Plus, Minus, Div, Eq, Leq, Geq, Lt, Gt, Comma, Semicol, Set, Colon, TwoColon, Hashtag, Dot, VInt, VString, Ident } kind;
  union {
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
struct regex_match_state {
  const char* regex;
  clist pos_pos;
};
