#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.cpp"
struct token {
  enum { TVoid, TInt, TChar, If, Else, Return, While, Const, Type, Func, Include, LPAREN, RPAREN, LSQUAR, RSQUAR, LBRACK, RBRACK, BAnd, BOr, LAnd, LOr, LNot, Star, Plus, Minus, Div, Eq, Leq, Geq, Lt, Gt, Comma, Semicol, Set, Colon, TwoColon, Hashtag, Dot, VInt, VString, Ident } kind;
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
