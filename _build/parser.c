#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.cpp"
struct binop {
  enum { Add, Mul, Sub, Div, Band, Bor, Land, Lor, Eq, Leq, Lt, Neq, Geq, Gt } kind;
};
struct unop {
  enum { Lnot, Neg, Addr } kind;
};
struct token {
  enum { Nothing, TVoid, TInt, TChar, If, Elif, Else, Return, While, Const, Typeof, As, Type, Func, Static, Specialize, Include, Include_C, LPAREN, RPAREN, LSQUAR, RSQUAR, LBRACK, RBRACK, Binop, Unop, Comma, Semicol, Set, Colon, TwoColon, Hashtag, Dot, VInt, VString, Ident } kind;
  union {
    struct {
      binop op;
    } Binop_dat;
    struct {
      unop op;
    } Unop_dat;
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
#include <stdlib.h>
#define dat_t void*
#define clist clist_voidptr
struct clist {
  struct _clist {
    dat_t dat;
    _clist* next;
  };
  _clist* l;
  void push(dat_t dat){
    _clist* n;
    n = (_clist*)malloc(sizeof(_clist));
    (n[0]).dat = dat;
    (n[0]).next = l;
    l = n;
  }
  dat_t pop(){
    dat_t ret;
    ret = (l[0]).dat;
    _clist* tmp;
    tmp = (l[0]).next;
    free(l);
    l = tmp;
    return ret;
  }
  void del(){
    while (l) {
      pop();
    }
  }
  int len(){
    int ret;
    ret = 0;
    _clist* t;
    t = l;
    while (t) {
      ret = (ret) + (1);
      t = (t[0]).next;
    }
    return ret;
  }
  dat_t ith(int i){
    _clist* t;
    t = l;
    while ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d\n", i);
        exit(0);
      }
      t = (t[0]).next;
      i = (i) - (1);
    }
    return (t[0]).dat;
  }
  void reverse(){
    clist rev;
    (rev).l = nullptr;
    while (l) {
      (rev).push(pop());
    }
    l = (rev).l;
  }
  clist tail(){
    clist ret;
    (ret).l = (l[0]).next;
    return ret;
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
#define dat_t token
#define clist toklist
struct clist {
  struct _clist {
    dat_t dat;
    _clist* next;
  };
  _clist* l;
  void push(dat_t dat){
    _clist* n;
    n = (_clist*)malloc(sizeof(_clist));
    (n[0]).dat = dat;
    (n[0]).next = l;
    l = n;
  }
  dat_t pop(){
    dat_t ret;
    ret = (l[0]).dat;
    _clist* tmp;
    tmp = (l[0]).next;
    free(l);
    l = tmp;
    return ret;
  }
  void del(){
    while (l) {
      pop();
    }
  }
  int len(){
    int ret;
    ret = 0;
    _clist* t;
    t = l;
    while (t) {
      ret = (ret) + (1);
      t = (t[0]).next;
    }
    return ret;
  }
  dat_t ith(int i){
    _clist* t;
    t = l;
    while ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d\n", i);
        exit(0);
      }
      t = (t[0]).next;
      i = (i) - (1);
    }
    return (t[0]).dat;
  }
  void reverse(){
    clist rev;
    (rev).l = nullptr;
    while (l) {
      (rev).push(pop());
    }
    l = (rev).l;
  }
  clist tail(){
    clist ret;
    (ret).l = (l[0]).next;
    return ret;
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
struct nonterm_symb {
  enum { Rval0, Rval1 } kind;
};
struct gram_rule_t {
  struct gram_symbol_t {
    enum { Term, NonTerm } kind;
    union {
      struct {
        token tok;
      } Term_dat;
      struct {
        nonterm_symb symb;
      } NonTerm_dat;
     } dat;
  };
  #define dat_t gram_symbol_t
  #define clist symlist
  struct clist {
    struct _clist {
      dat_t dat;
      _clist* next;
    };
    _clist* l;
    void push(dat_t dat){
      _clist* n;
      n = (_clist*)malloc(sizeof(_clist));
      (n[0]).dat = dat;
      (n[0]).next = l;
      l = n;
    }
    dat_t pop(){
      dat_t ret;
      ret = (l[0]).dat;
      _clist* tmp;
      tmp = (l[0]).next;
      free(l);
      l = tmp;
      return ret;
    }
    void del(){
      while (l) {
        pop();
      }
    }
    int len(){
      int ret;
      ret = 0;
      _clist* t;
      t = l;
      while (t) {
        ret = (ret) + (1);
        t = (t[0]).next;
      }
      return ret;
    }
    dat_t ith(int i){
      _clist* t;
      t = l;
      while ((i) > (0)) {
        if (!(t)) {
          printf("out of range in list: index %d\n", i);
          exit(0);
        }
        t = (t[0]).next;
        i = (i) - (1);
      }
      return (t[0]).dat;
    }
    void reverse(){
      clist rev;
      (rev).l = nullptr;
      while (l) {
        (rev).push(pop());
      }
      l = (rev).l;
    }
    clist tail(){
      clist ret;
      (ret).l = (l[0]).next;
      return ret;
    }
    void init(){
      l = nullptr;
    }
  };
  #undef dat_t
  #undef clist
  symlist pattern;
  gram_symbol_t result;
  void* dummy(clist_voidptr res);
  typeof(dummy) result;
  void* parse(toklist l){
    return nullptr;
  }
};
#define dat_t gram_rule_t
#define clist gram_rules
struct clist {
  struct _clist {
    dat_t dat;
    _clist* next;
  };
  _clist* l;
  void push(dat_t dat){
    _clist* n;
    n = (_clist*)malloc(sizeof(_clist));
    (n[0]).dat = dat;
    (n[0]).next = l;
    l = n;
  }
  dat_t pop(){
    dat_t ret;
    ret = (l[0]).dat;
    _clist* tmp;
    tmp = (l[0]).next;
    free(l);
    l = tmp;
    return ret;
  }
  void del(){
    while (l) {
      pop();
    }
  }
  int len(){
    int ret;
    ret = 0;
    _clist* t;
    t = l;
    while (t) {
      ret = (ret) + (1);
      t = (t[0]).next;
    }
    return ret;
  }
  dat_t ith(int i){
    _clist* t;
    t = l;
    while ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d\n", i);
        exit(0);
      }
      t = (t[0]).next;
      i = (i) - (1);
    }
    return (t[0]).dat;
  }
  void reverse(){
    clist rev;
    (rev).l = nullptr;
    while (l) {
      (rev).push(pop());
    }
    l = (rev).l;
  }
  clist tail(){
    clist ret;
    (ret).l = (l[0]).next;
    return ret;
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
