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
  enum { TVoid, TInt, TChar, If, Elif, Else, Return, While, Const, Typeof, As, Type, Func, Static, Specialize, Include, Include_C, LPAREN, RPAREN, LSQUAR, RSQUAR, LBRACK, RBRACK, Binop, Unop, Comma, Semicol, Set, Colon, TwoColon, Hashtag, Dot, VInt, VString, Ident } kind;
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
  bool eq(token b){
    if ((kind) != ((b).kind)) {
      return false;
    }
    if ((kind) == (Binop)) {
      return ((((dat).Binop_dat).op).kind) == (((((b).dat).Binop_dat).op).kind);
    } else
    if ((kind) == (Unop)) {
      return ((((dat).Unop_dat).op).kind) == (((((b).dat).Unop_dat).op).kind);
    } else
    if ((kind) == (VInt)) {
      return (((dat).VInt_dat).dat) == ((((b).dat).VInt_dat).dat);
    } else
    if ((kind) == (VString)) {
      return !(strcmp(((dat).VString_dat).str, (((b).dat).VString_dat).str));
    } else
    if ((kind) == (Ident)) {
      return !(strcmp(((dat).Ident_dat).str, (((b).dat).Ident_dat).str));
    }
    return true;
  }
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
  void append(dat_t dat){
    if ((l) == (nullptr)) {
      push(dat);
    } else {
      clist tmp;
      tmp = tail();
      (tmp).append(dat);
      (l[0]).next = (tmp).l;
    }
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
  void append(dat_t dat){
    if ((l) == (nullptr)) {
      push(dat);
    } else {
      clist tmp;
      tmp = tail();
      (tmp).append(dat);
      (l[0]).next = (tmp).l;
    }
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
toklist lex_string(const char* str);
struct nonterm_symb {
  enum { Rval, Rvalop, RvalI, Lval } kind;
  const char* to_string(){
    if ((kind) == (Rval)) {
      return "Rval";
    } else
    if ((kind) == (Rvalop)) {
      return "Rvalop";
    } else
    if ((kind) == (RvalI)) {
      return "RvalI";
    } else
    if ((kind) == (Lval)) {
      return "Lval";
    }
    printf("invalid nonterminal symbol\n");
    exit(-(1));
  }
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
    void append(dat_t dat){
      if ((l) == (nullptr)) {
        push(dat);
      } else {
        clist tmp;
        tmp = tail();
        (tmp).append(dat);
        (l[0]).next = (tmp).l;
      }
    }
    void init(){
      l = nullptr;
    }
  };
  #undef dat_t
  #undef clist
  struct gram_symbol_t {
    enum { Term, Exact, NonTerm } kind;
    union {
      struct {
        token tok;
      } Term_dat;
      struct {
        token tok;
      } Exact_dat;
      struct {
        nonterm_symb symb;
      } NonTerm_dat;
     } dat;
    bool match_ok(toklist* l, int max_depth, gram_rules rules){
      return (match_symb(l, max_depth, rules)) != (nullptr);
    }
    void* match_symb(toklist* l, int max_depth, gram_rules rules){
      if ((max_depth) < (0)) {
        return nullptr;
      }
      if ((kind) == (Term)) {
        if ((((l[0]).ith(0)).kind) != ((((dat).Term_dat).tok).kind)) {
          return nullptr;
        }
        l[0] = (l[0]).tail();
        return (void*)(l[0]).ith_ref(0);
      } else
      if ((kind) == (Exact)) {
        if (!(((l[0]).ith(0)).eq(((dat).Exact_dat).tok))) {
          return nullptr;
        }
        l[0] = (l[0]).tail();
        return (void*)(l[0]).ith_ref(0);
      } else {
        int i;
        int chosen;
        int chosen_len;
        chosen_len = (l)->len();
        i = 0;
        toklist base;
        base = l[0];
        while ((i) < ((rules).len())) {
          gram_rule_t rule;
          rule = (rules).ith(i)[0];
          if ((((rule).result).kind) == ((((dat).NonTerm_dat).symb).kind)) {
            if ((rule).parse_ok(l, max_depth, rules)) {
              int curlen;
              curlen = (l)->len();
              if ((curlen) < (chosen_len)) {
                chosen_len = curlen;
                chosen = i;
              }
            }
            l[0] = base;
          }
          i = (i) + (1);
        }
        if ((chosen_len) < ((l)->len())) {
          gram_rule_t rule;
          rule = (rules).ith(chosen)[0];
          void* ret;
          ret = (rule).parse(l, max_depth, rules);
          return ret;
        }
        return nullptr;
      }
    }
    void set_Term(){
      kind = Term;
    }
    void set_NonTerm(){
      kind = NonTerm;
    }
    void set_Exact(){
      kind = Exact;
    }
    void print(){
      if ((kind) == (Term)) {
        printf("Term (id %d)", (int)(((dat).Term_dat).tok).kind);
      } else
      if ((kind) == (Exact)) {
        printf("Exact (id %d)", (int)(((dat).Term_dat).tok).kind);
      } else
      printf("NonTerm %s", (((dat).NonTerm_dat).symb).to_string());
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
    void append(dat_t dat){
      if ((l) == (nullptr)) {
        push(dat);
      } else {
        clist tmp;
        tmp = tail();
        (tmp).append(dat);
        (l[0]).next = (tmp).l;
      }
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
    toklist base;
    base = l[0];
    while ((i) < ((pattern).len())) {
      gram_symbol_t sym;
      sym = (pattern).ith(i);
      l[0] = base;
      if (!((sym).match_ok(l, (max_depth) - (1), rules))) {
        l[0] = base;
        (vlues).del();
        return nullptr;
      }
      void* vals;
      l[0] = base;
      vals = (sym).match_symb(l, (max_depth) - (1), rules);
      base = l[0];
      (vlues).push(vals);
      i = (i) + (1);
    }
    (vlues).reverse();
    void* ret;
    ret = result_function(vlues);
    (vlues).del();
    return ret;
  }
  void init(nonterm_symb rule_result, void* (*rule_result_function)(clist_voidptr)){
    result = rule_result;
    result_function = rule_result_function;
    (pattern).init();
  }
  void add_nonterm(nonterm_symb nt){
    gram_symbol_t sym;
    (sym).set_NonTerm();
    (((sym).dat).NonTerm_dat).symb = nt;
    (pattern).append(sym);
  }
  void add_term(const char* str){
    toklist l;
    l = lex_string(str);
    while ((l).len()) {
      gram_symbol_t sym;
      (sym).set_Term();
      (((sym).dat).Term_dat).tok = (l).pop();
      (pattern).append(sym);
    }
  }
  void add_exact(const char* str){
    toklist l;
    l = lex_string(str);
    while ((l).len()) {
      gram_symbol_t sym;
      (sym).set_Exact();
      (((sym).dat).Exact_dat).tok = (l).pop();
      (pattern).append(sym);
    }
  }
  void print(){
    printf("rule: %s -> ", (result).to_string());
    int i;
    i = 0;
    while ((i) < ((pattern).len())) {
      if (i) {
        printf(" ");
      }
      ((pattern).ith(i)).print();
      i = (i) + (1);
    }
    printf("\n");
  }
};
