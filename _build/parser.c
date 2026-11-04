#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct binop {
  enum { Add, Mul, Sub, Div, Band, Bor, Land, Lor, Eq, Leq, Lt, Neq, Geq, Gt, Arrow } kind;
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
    ret = (l)->dat;
    _clist* tmp;
    tmp = (l)->next;
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
      t = (t)->next;
    }
    return ret;
  }
  dat_t* ith_ref(int i){
    _clist* t;
    t = l;
    while ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", i, len());
        exit(0);
      }
      t = (t)->next;
      i = (i) - (1);
    }
    if (!(t)) {
      printf("out of range in list: index %d while len is %d\n", i, len());
      exit(0);
    }
    dat_t* ret;
    ret = &((t)->dat);
    return ret;
  }
  dat_t ith(int i){
    return ith_ref(i)[0];
  }
  void reverse(){
    clist rev;
    (rev).init();
    while (l) {
      (rev).push(pop());
    }
    l = (rev).l;
  }
  clist tail(){
    clist ret;
    (ret).l = (l)->next;
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
    ret = (l)->dat;
    _clist* tmp;
    tmp = (l)->next;
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
      t = (t)->next;
    }
    return ret;
  }
  dat_t* ith_ref(int i){
    _clist* t;
    t = l;
    while ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", i, len());
        exit(0);
      }
      t = (t)->next;
      i = (i) - (1);
    }
    if (!(t)) {
      printf("out of range in list: index %d while len is %d\n", i, len());
      exit(0);
    }
    dat_t* ret;
    ret = &((t)->dat);
    return ret;
  }
  dat_t ith(int i){
    return ith_ref(i)[0];
  }
  void reverse(){
    clist rev;
    (rev).init();
    while (l) {
      (rev).push(pop());
    }
    l = (rev).l;
  }
  clist tail(){
    clist ret;
    (ret).l = (l)->next;
    return ret;
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
struct nonterm_symb {
  enum { Rval0, Rval1, Rval2, Lval0 } kind;
};
struct gram_rule_t {
  #define dat_t gram_rule_t*
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
      ret = (l)->dat;
      _clist* tmp;
      tmp = (l)->next;
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
        t = (t)->next;
      }
      return ret;
    }
    dat_t* ith_ref(int i){
      _clist* t;
      t = l;
      while ((i) > (0)) {
        if (!(t)) {
          printf("out of range in list: index %d while len is %d\n", i, len());
          exit(0);
        }
        t = (t)->next;
        i = (i) - (1);
      }
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", i, len());
        exit(0);
      }
      dat_t* ret;
      ret = &((t)->dat);
      return ret;
    }
    dat_t ith(int i){
      return ith_ref(i)[0];
    }
    void reverse(){
      clist rev;
      (rev).init();
      while (l) {
        (rev).push(pop());
      }
      l = (rev).l;
    }
    clist tail(){
      clist ret;
      (ret).l = (l)->next;
      return ret;
    }
    void init(){
      l = nullptr;
    }
  };
  #undef dat_t
  #undef clist
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
    bool match_ok(toklist* l, int max_depth, gram_rules rules){
      return (match_symb(l, max_depth, rules)) != (nullptr);
    }
    void* match_symb(toklist* l, int max_depth, gram_rules rules){
      if ((kind) == (Term)) {
        if ((((l[0]).ith(0)).kind) != ((((dat).Term_dat).tok).kind)) {
          return nullptr;
        }
        l[0] = (l[0]).tail();
        char tmp;
        void* ret;
        return (void*)&(tmp);
      } else {
        if ((((l[0]).ith(0)).kind) != ((((dat).Term_dat).tok).kind)) {
          return nullptr;
        }
        l[0] = (l[0]).tail();
        char tmp;
        void* ret;
        return (void*)&(tmp);
      }
    }
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
      ret = (l)->dat;
      _clist* tmp;
      tmp = (l)->next;
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
        t = (t)->next;
      }
      return ret;
    }
    dat_t* ith_ref(int i){
      _clist* t;
      t = l;
      while ((i) > (0)) {
        if (!(t)) {
          printf("out of range in list: index %d while len is %d\n", i, len());
          exit(0);
        }
        t = (t)->next;
        i = (i) - (1);
      }
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", i, len());
        exit(0);
      }
      dat_t* ret;
      ret = &((t)->dat);
      return ret;
    }
    dat_t ith(int i){
      return ith_ref(i)[0];
    }
    void reverse(){
      clist rev;
      (rev).init();
      while (l) {
        (rev).push(pop());
      }
      l = (rev).l;
    }
    clist tail(){
      clist ret;
      (ret).l = (l)->next;
      return ret;
    }
    void init(){
      l = nullptr;
    }
  };
  #undef dat_t
  #undef clist
  symlist pattern;
  nonterm_symb result;
  void* (*result_function)(clist_voidptr);
  bool parse_ok(toklist* l, int max_depth, gram_rules rules){
    return ((this[0]).parse(l, max_depth, rules)) != (nullptr);
  }
  void* parse(toklist* l, int max_depth, gram_rules rules){
    int i;
    i = 0;
    clist_voidptr vlues;
    (vlues).init();
    while ((i) < ((pattern).len())) {
      gram_symbol_t sym;
      sym = (pattern).ith(i);
      if (!((sym).match_ok(l, (max_depth) - (1), rules))) {
        return nullptr;
      }
      void* vals;
      vals = (sym).match_symb(l, (max_depth) - (1), rules);
      (vlues).push(vals);
    }
    (vlues).reverse();
    void* ret;
    ret = result_function(vlues);
    (vlues).del();
    return ret;
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
    ret = (l)->dat;
    _clist* tmp;
    tmp = (l)->next;
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
      t = (t)->next;
    }
    return ret;
  }
  dat_t* ith_ref(int i){
    _clist* t;
    t = l;
    while ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", i, len());
        exit(0);
      }
      t = (t)->next;
      i = (i) - (1);
    }
    if (!(t)) {
      printf("out of range in list: index %d while len is %d\n", i, len());
      exit(0);
    }
    dat_t* ret;
    ret = &((t)->dat);
    return ret;
  }
  dat_t ith(int i){
    return ith_ref(i)[0];
  }
  void reverse(){
    clist rev;
    (rev).init();
    while (l) {
      (rev).push(pop());
    }
    l = (rev).l;
  }
  clist tail(){
    clist ret;
    (ret).l = (l)->next;
    return ret;
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
