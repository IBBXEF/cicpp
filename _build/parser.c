#pragma once
#include <stdlib.h>
#include <stdio.h>
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
  dat_t* ith_ref(int ind){
    _clist* t;
    t = l;
    int i;
    i = ind;
    while ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", ind, len());
        exit(-(1));
      }
      t = (t)->next;
      i = (i) - (1);
    }
    if (!(t)) {
      printf("out of range in list: index %d while len is %d\n", ind, len());
      exit(-(1));
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
  dat_t remove(int i){
    if ((i) == (0)) {
      return pop();
    } else {
      clist tmp;
      tmp = tail();
      dat_t ret;
      ret = (tmp).remove((i) - (1));
      (l[0]).next = (tmp).l;
      return ret;
    }
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
#define dat_t const char*
#define clist string_list
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
  dat_t* ith_ref(int ind){
    _clist* t;
    t = l;
    int i;
    i = ind;
    while ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", ind, len());
        exit(-(1));
      }
      t = (t)->next;
      i = (i) - (1);
    }
    if (!(t)) {
      printf("out of range in list: index %d while len is %d\n", ind, len());
      exit(-(1));
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
  dat_t remove(int i){
    if ((i) == (0)) {
      return pop();
    } else {
      clist tmp;
      tmp = tail();
      dat_t ret;
      ret = (tmp).remove((i) - (1));
      (l[0]).next = (tmp).l;
      return ret;
    }
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
#include <string.h>
int string_list_find(string_list l, const char* str){
  int i;
  i = 0;
  while ((i) < ((l).len())) {
    if (!(strcmp((l).ith(i), str))) {
      return i;
    }
    i = (i) + (1);
  }
  return -(1);
}
#include <climits>
struct anyptr {
  void* ptr;
  void (*free_func)(void*);
  int* n_refs;
  static
  void do_nothing(void* p){
    p = p;
  }
  void init(void* _ptr, void (*_free_func)(void*)){
    ptr = _ptr;
    free_func = _free_func;
    n_refs = (int*)malloc(4);
    n_refs[0] = 1;
  }
  void init_view(void* _ptr){
    ptr = _ptr;
    free_func = do_nothing;
    n_refs = (int*)malloc(4);
    n_refs[0] = INT_MAX;
  }
  anyptr get_view(){
    anyptr ret;
    (ret).init_view(ptr);
    return ret;
  }
  anyptr get_copy(){
    anyptr ret;
    ret = this[0];
    if ((n_refs[0]) < (INT_MAX)) {
      n_refs[0] = (n_refs[0]) + (1);
    }
    return ret;
  }
  void init_null(){
    init_view(nullptr);
  }
  void* get(){
    return ptr;
  }
  void del(){
    n_refs[0] = (n_refs[0]) - (1);
    if (!(n_refs[0])) {
      free_func(ptr);
      free(n_refs);
      ptr = nullptr;
    } else
    if ((n_refs[0]) < (0)) {
      printf("error: a freed shared pointer has been dereferenced\n");
      exit(-(1));
    }
  }
};
#define dat_t anyptr
#define clist clist_anyptr
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
  dat_t* ith_ref(int ind){
    _clist* t;
    t = l;
    int i;
    i = ind;
    while ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", ind, len());
        exit(-(1));
      }
      t = (t)->next;
      i = (i) - (1);
    }
    if (!(t)) {
      printf("out of range in list: index %d while len is %d\n", ind, len());
      exit(-(1));
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
  dat_t remove(int i){
    if ((i) == (0)) {
      return pop();
    } else {
      clist tmp;
      tmp = tail();
      dat_t ret;
      ret = (tmp).remove((i) - (1));
      (l[0]).next = (tmp).l;
      return ret;
    }
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
void clist_anyptr_free(clist_anyptr l){
  while ((l).len()) {
    ((l).pop()).del();
  }
}
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
  enum { TVoid, TInt, TChar, If, Elif, Else, Return, While, Const, Typeof, As, Type, Func, Static, Specialize, Include, Include_C, LPAREN, RPAREN, LSQUAR, RSQUAR, LBRACK, RBRACK, Binop, Unop, Comma, Semicol, Set, Colon, TwoColon, Hashtag, Dot, VInt, VString, Ident, EndOfInput } kind;
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
  void init_EOI(){
    kind = EndOfInput;
  }
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
  dat_t* ith_ref(int ind){
    _clist* t;
    t = l;
    int i;
    i = ind;
    while ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", ind, len());
        exit(-(1));
      }
      t = (t)->next;
      i = (i) - (1);
    }
    if (!(t)) {
      printf("out of range in list: index %d while len is %d\n", ind, len());
      exit(-(1));
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
  dat_t remove(int i){
    if ((i) == (0)) {
      return pop();
    } else {
      clist tmp;
      tmp = tail();
      dat_t ret;
      ret = (tmp).remove((i) - (1));
      (l[0]).next = (tmp).l;
      return ret;
    }
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
toklist lex_string(const char* str);
#include <limits.h>
#include <stdio.h>
#include <string.h>
int string_list_thingy(string_list* l, char* str){
  int i;
  i = string_list_find(l[0], str);
  if ((i) < (0)) {
    (l[0]).append(str);
    return ((l)->len()) - (1);
  }
  free(str);
  return i;
}
char* copy_string_until_char(const char** str, char c){
  const char* base;
  base = str[0];
  while ((str[0][0]) && ((str[0][0]) != (c))) {
    str[0] = (str[0]) + (1);
  }
  int len;
  len = (str[0]) - (base);
  char* ret;
  ret = (char*)malloc((len) + (1));
  ret[len] = 0;
  int i;
  i = 0;
  while ((i) < (len)) {
    ret[i] = base[i];
    i = (i) + (1);
  }
  return ret;
}
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
    dat_t* ith_ref(int ind){
      _clist* t;
      t = l;
      int i;
      i = ind;
      while ((i) > (0)) {
        if (!(t)) {
          printf("out of range in list: index %d while len is %d\n", ind, len());
          exit(-(1));
        }
        t = (t)->next;
        i = (i) - (1);
      }
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", ind, len());
        exit(-(1));
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
    dat_t remove(int i){
      if ((i) == (0)) {
        return pop();
      } else {
        clist tmp;
        tmp = tail();
        dat_t ret;
        ret = (tmp).remove((i) - (1));
        (l[0]).next = (tmp).l;
        return ret;
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
        int symb;
      } NonTerm_dat;
     } dat;
    void set_nonterm(int i){
      kind = NonTerm;
      ((dat).NonTerm_dat).symb = i;
    }
    void set_term(token t){
      kind = Term;
      ((dat).Term_dat).tok = t;
    }
    void set_exact(token t){
      kind = Exact;
      ((dat).Term_dat).tok = t;
    }
    bool match_tok(token t){
      if ((kind) == (Exact)) {
        return (t).eq(((dat).Exact_dat).tok);
      } else
      if ((kind) == (Term)) {
        return ((((dat).Exact_dat).tok).kind) == ((t).kind);
      } else
      return false;
    }
    bool includes(gram_symbol_t s){
      if (((kind) == (NonTerm)) || (((s).kind) == (NonTerm))) {
        printf("invalid inclusion test of gram_symbol_t\n");
        exit(EXIT_FAILURE);
      }
      if ((((s).kind) == (Exact)) || ((kind) == (Term))) {
        return match_tok((((s).dat).Exact_dat).tok);
      }
      return false;
    }
    bool eq(gram_symbol_t b){
      if ((kind) != ((b).kind)) {
        return false;
      }
      if ((kind) == (NonTerm)) {
        return (((dat).NonTerm_dat).symb) == ((((b).dat).NonTerm_dat).symb);
      } else
      if ((kind) == (Exact)) {
        return (((dat).Exact_dat).tok).eq((((b).dat).Exact_dat).tok);
      } else
      return ((((dat).Term_dat).tok).kind) == (((((b).dat).Term_dat).tok).kind);
    }
    void print(string_list nonterm_symbs){
      if ((kind) == (Term)) {
        printf("Term (id %d)", (int)(((dat).Term_dat).tok).kind);
      } else
      if ((kind) == (Exact)) {
        printf("Exact (id %d)", (int)(((dat).Term_dat).tok).kind);
      } else
      printf("$%s", (nonterm_symbs).ith(((dat).NonTerm_dat).symb));
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
    dat_t* ith_ref(int ind){
      _clist* t;
      t = l;
      int i;
      i = ind;
      while ((i) > (0)) {
        if (!(t)) {
          printf("out of range in list: index %d while len is %d\n", ind, len());
          exit(-(1));
        }
        t = (t)->next;
        i = (i) - (1);
      }
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", ind, len());
        exit(-(1));
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
    dat_t remove(int i){
      if ((i) == (0)) {
        return pop();
      } else {
        clist tmp;
        tmp = tail();
        dat_t ret;
        ret = (tmp).remove((i) - (1));
        (l[0]).next = (tmp).l;
        return ret;
      }
    }
    void init(){
      l = nullptr;
    }
  };
  #undef dat_t
  #undef clist
  struct parsing_table {
    struct sym_rule_pair {
      gram_symbol_t s;
      gram_rule_t* r;
    };
    #define dat_t sym_rule_pair
    #define clist pairlist
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
      dat_t* ith_ref(int ind){
        _clist* t;
        t = l;
        int i;
        i = ind;
        while ((i) > (0)) {
          if (!(t)) {
            printf("out of range in list: index %d while len is %d\n", ind, len());
            exit(-(1));
          }
          t = (t)->next;
          i = (i) - (1);
        }
        if (!(t)) {
          printf("out of range in list: index %d while len is %d\n", ind, len());
          exit(-(1));
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
      dat_t remove(int i){
        if ((i) == (0)) {
          return pop();
        } else {
          clist tmp;
          tmp = tail();
          dat_t ret;
          ret = (tmp).remove((i) - (1));
          (l[0]).next = (tmp).l;
          return ret;
        }
      }
      void init(){
        l = nullptr;
      }
    };
    #undef dat_t
    #undef clist
    pairlist* tables;
    int _n_nonterms;
    void init_empty(int n_nonterms){
      tables = (pairlist*)malloc((sizeof(pairlist)) * (n_nonterms));
      int i;
      i = 0;
      while ((i) < (n_nonterms)) {
        (tables[i]).init();
        i = (i) + (1);
      }
      _n_nonterms = n_nonterms;
    }
    void add_entry(gram_symbol_t s, int nonterm, gram_rule_t* r){
      if (((int)(s).kind) == (2)) {
        printf("invalid gram symbol for rule table: it is Nonterminal\n");
        exit(EXIT_FAILURE);
      }
      if (((nonterm) < (0)) || ((nonterm) >= (_n_nonterms))) {
        printf("invalid nonterminal index %d in parsing table\n", nonterm);
        exit(EXIT_FAILURE);
      }
      int i;
      i = 0;
      pairlist table;
      table = tables[nonterm];
      while ((i) < ((table).len())) {
        gram_symbol_t s2;
        s2 = ((table).ith(i)).s;
        if (((s2).includes(s)) || ((s).includes(s2))) {
          if (!((r)->eq(((table).ith(i)).r[0]))) {
            string_list empty;
            (empty).init();
            printf("conflicting entry in the parsing table for nonterm %d and symbol ", nonterm);
            (s).print(empty);
            printf("\n");
            exit(EXIT_FAILURE);
          }
        }
        i = (i) + (1);
      }
      sym_rule_pair pair;
      (pair).s = s;
      (pair).r = r;
      (tables[nonterm]).push(pair);
    }
    gram_rule_t* lookup(token t, int nonterm){
      if (((nonterm) < (0)) || ((nonterm) >= (_n_nonterms))) {
        printf("invalid nonterminal index %d in parsing table\n", nonterm);
        exit(EXIT_FAILURE);
      }
      int i;
      i = 0;
      pairlist tab;
      tab = tables[nonterm];
      while ((i) < ((tab).len())) {
        if ((((tab).ith(i)).s).match_tok(t)) {
          return ((tab).ith(i)).r;
        }
        i = (i) + (1);
      }
      return nullptr;
    }
    void del(){
      int i;
      i = 0;
      while ((i) < (_n_nonterms)) {
        (tables[i]).del();
        i = (i) + (1);
      }
    }
  };
  symlist pattern;
  int result;
  anyptr (*result_function)(clist_anyptr);
  void* func_bonus_dat;
  struct parsed_ast {
    enum { Leaf, Node, Unknown } kind;
    union {
      struct {
        token t;
      } Leaf_dat;
      struct {
        clist_voidptr childrens;
        gram_rule_t* origin_rule;
      } Node_dat;
     } dat;
    void init_unknown(){
      kind = Unknown;
    }
    void init_node(gram_rule_t* origin_rule){
      kind = Node;
      ((dat).Node_dat).origin_rule = origin_rule;
      (((dat).Node_dat).childrens).init();
    }
    void init_leaf(token t){
      kind = Leaf;
      ((dat).Leaf_dat).t = t;
    }
    void push_child(parsed_ast* child){
      (((dat).Node_dat).childrens).push(child);
    }
    void append_child(parsed_ast* child){
      (((dat).Node_dat).childrens).append(child);
    }
    anyptr evaluate_ast(){
      anyptr ret;
      if ((kind) == (Leaf)) {
        (ret).init_view(&(((dat).Leaf_dat).t));
        return ret;
      } else
      if ((kind) == (Node)) {
        clist_anyptr args;
        (args).init();
        int i;
        i = 0;
        clist_voidptr kids;
        kids = ((dat).Node_dat).childrens;
        while ((i) < ((kids).len())) {
          parsed_ast* child;
          child = (parsed_ast*)(kids).ith(i);
          (args).append((child)->evaluate_ast());
          i = (i) + (1);
        }
        anyptr tmp;
        (tmp).init_view((((dat).Node_dat).origin_rule)->func_bonus_dat);
        (args).append(tmp);
        anyptr res;
        res = (((dat).Node_dat).origin_rule)->result_function(args);
        (args).del();
        return res;
      } else {
        printf("tried to evaluate unknown ast node\n");
        exit(EXIT_FAILURE);
      }
    }
  };
  struct symbol_dat {
    #define dat_t symbol_dat*
    #define clist symdatptrlist
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
      dat_t* ith_ref(int ind){
        _clist* t;
        t = l;
        int i;
        i = ind;
        while ((i) > (0)) {
          if (!(t)) {
            printf("out of range in list: index %d while len is %d\n", ind, len());
            exit(-(1));
          }
          t = (t)->next;
          i = (i) - (1);
        }
        if (!(t)) {
          printf("out of range in list: index %d while len is %d\n", ind, len());
          exit(-(1));
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
      dat_t remove(int i){
        if ((i) == (0)) {
          return pop();
        } else {
          clist tmp;
          tmp = tail();
          dat_t ret;
          ret = (tmp).remove((i) - (1));
          (l[0]).next = (tmp).l;
          return ret;
        }
      }
      void init(){
        l = nullptr;
      }
    };
    #undef dat_t
    #undef clist
    parsed_ast* ast_loc;
    gram_symbol_t sym;
    void update_tok_ast(token t){
      (ast_loc)->init_leaf(t);
    }
    void init(gram_symbol_t symb, parsed_ast* ast){
      sym = symb;
      ast_loc = ast;
    }
  };
  #define dat_t symbol_dat
  #define clist symdatlist
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
    dat_t* ith_ref(int ind){
      _clist* t;
      t = l;
      int i;
      i = ind;
      while ((i) > (0)) {
        if (!(t)) {
          printf("out of range in list: index %d while len is %d\n", ind, len());
          exit(-(1));
        }
        t = (t)->next;
        i = (i) - (1);
      }
      if (!(t)) {
        printf("out of range in list: index %d while len is %d\n", ind, len());
        exit(-(1));
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
    dat_t remove(int i){
      if ((i) == (0)) {
        return pop();
      } else {
        clist tmp;
        tmp = tail();
        dat_t ret;
        ret = (tmp).remove((i) - (1));
        (l[0]).next = (tmp).l;
        return ret;
      }
    }
    void init(){
      l = nullptr;
    }
  };
  #undef dat_t
  #undef clist
  void init(int rule_result, anyptr (*rule_result_function)(clist_anyptr)){
    result = rule_result;
    result_function = rule_result_function;
    func_bonus_dat = nullptr;
    (pattern).init();
  }
  void init_bonus_func_data(int rule_result, anyptr (*rule_result_function)(clist_anyptr), void* result_func_bonus_dat){
    init(rule_result, rule_result_function);
    func_bonus_dat = result_func_bonus_dat;
  }
  void del(){
    (pattern).del();
  }
  bool eq(gram_rule_t r){
    printf("test: ");
    if ((result) != ((r).result)) {
      printf("f3\n");
      return false;
    }
    if (((pattern).len()) != (((r).pattern).len())) {
      printf("f4\n");
      return false;
    }
    int i;
    i = 0;
    while ((i) < ((pattern).len())) {
      gram_symbol_t s1;
      gram_symbol_t s2;
      s1 = (pattern).ith(i);
      s2 = ((r).pattern).ith(i);
      if (!(((s1).includes(s2)) && ((s2).includes(s1)))) {
        printf("f5\n");
        return false;
      }
      i = (i) + (1);
    }
    if ((result_function) != ((r).result_function)) {
      printf("f1\n");
      return false;
    }
    if ((func_bonus_dat) != ((r).func_bonus_dat)) {
      printf("f2\n");
      return false;
    }
    printf("f0\n");
    return true;
  }
  void add_nonterm(int nt){
    gram_symbol_t sym;
    (sym).set_nonterm(nt);
    (pattern).push(sym);
  }
  void add_term(const char* str){
    toklist l;
    l = lex_string(str);
    while ((l).len()) {
      gram_symbol_t sym;
      (sym).set_term((l).pop());
      (pattern).push(sym);
    }
  }
  void add_exact(const char* str){
    toklist l;
    l = lex_string(str);
    while ((l).len()) {
      gram_symbol_t sym;
      (sym).set_exact((l).pop());
      (pattern).push(sym);
    }
  }
  void print(string_list nonterm_symbs){
    printf("rule: $%s -> ", (nonterm_symbs).ith(result));
    int i;
    i = 0;
    while ((i) < ((pattern).len())) {
      if (i) {
        printf(" ");
      }
      ((pattern).ith(((pattern).len()) - ((i) + (1)))).print(nonterm_symbs);
      i = (i) + (1);
    }
    printf("\n");
  }
  #define dat_t gram_symbol_t
  #define comparable_ptr term_ptr
  struct comparable_ptr {
    dat_t* ptr;
    void init_null(){
      ptr = nullptr;
    }
    void init_ptr(dat_t* p){
      ptr = p;
    }
    bool eq(comparable_ptr p2){
      if ((!(ptr)) || (!((p2).ptr))) {
        return (ptr) == ((p2).ptr);
      }
      return (ptr)->eq((p2).ptr[0]);
    }
  };
  #undef dat_t
  #undef comparable_ptr
  #define set_dat_t term_ptr
  #define set term_set
  struct set {
    #define dat_t set_dat_t
    #define clist datlist
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
      dat_t* ith_ref(int ind){
        _clist* t;
        t = l;
        int i;
        i = ind;
        while ((i) > (0)) {
          if (!(t)) {
            printf("out of range in list: index %d while len is %d\n", ind, len());
            exit(-(1));
          }
          t = (t)->next;
          i = (i) - (1);
        }
        if (!(t)) {
          printf("out of range in list: index %d while len is %d\n", ind, len());
          exit(-(1));
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
      dat_t remove(int i){
        if ((i) == (0)) {
          return pop();
        } else {
          clist tmp;
          tmp = tail();
          dat_t ret;
          ret = (tmp).remove((i) - (1));
          (l[0]).next = (tmp).l;
          return ret;
        }
      }
      void init(){
        l = nullptr;
      }
    };
    #undef dat_t
    #undef clist
    datlist elts;
    void init(){
      (elts).init();
    }
    void del(){
      (elts).del();
    }
    bool contains(set_dat_t s){
      int i;
      i = 0;
      while ((i) < ((elts).len())) {
        if ((s).eq((elts).ith(i))) {
          return true;
        }
        i = (i) + (1);
      }
      return false;
    }
    bool remove(set_dat_t s){
      int i;
      i = 0;
      while ((i) < ((elts).len())) {
        if ((s).eq((elts).ith(i))) {
          (elts).remove(i);
          return true;
        }
        i = (i) + (1);
      }
      return false;
    }
    bool add(set_dat_t s){
      if (!(contains(s))) {
        (elts).push(s);
        return true;
      }
      return false;
    }
    bool union_with(set other){
      bool ret;
      ret = false;
      int i;
      i = 0;
      while ((i) < (((other).elts).len())) {
        ret = (add(((other).elts).ith(i))) || (ret);
        i = (i) + (1);
      }
      return ret;
    }
  };
  #undef set_dat_t
  #undef set
  static
  parsing_table make_parsing_table(gram_rules rules, string_list nonterm_symbs, int goal_nonterm, gram_symbol_t* stop_symbol){
    term_set* Fi;
    Fi = (term_set*)malloc((sizeof(term_set)) * ((nonterm_symbs).len()));
    term_set* FiRules;
    FiRules = (term_set*)malloc((sizeof(term_set)) * ((rules).len()));
    term_ptr tmp_ptr;
    term_ptr epsilon;
    (tmp_ptr).init_null();
    (epsilon).init_null();
    int i;
    i = 0;
    while ((i) < ((nonterm_symbs).len())) {
      (Fi[i]).init();
      i = (i) + (1);
    }
    i = 0;
    while ((i) < ((rules).len())) {
      (FiRules[i]).init();
      i = (i) + (1);
    }
    bool not_finished;
    not_finished = true;
    while (not_finished) {
      not_finished = false;
      i = 0;
      while ((i) < ((rules).len())) {
        gram_rule_t* rule;
        rule = (rules).ith(i);
        term_set* cFi;
        cFi = (Fi) + ((rule)->result);
        term_set addFi;
        (addFi).init();
        int j;
        j = (((rule)->pattern).len()) - (1);
        while ((0) <= (j)) {
          gram_symbol_t* sy;
          sy = ((rule)->pattern).ith_ref(j);
          if (((int)(sy)->kind) != (2)) {
            (tmp_ptr).init_ptr(sy);
            (addFi).add(tmp_ptr);
            j = -(2);
          } else {
            term_set* oFi;
            oFi = (Fi) + ((((sy)->dat).NonTerm_dat).symb);
            if ((oFi)->contains(epsilon)) {
              (tmp_ptr).init_null();
              (oFi)->remove(epsilon);
              (addFi).union_with(oFi[0]);
              (oFi)->add(epsilon);
            } else {
              (addFi).union_with(oFi[0]);
              j = -(2);
            }
          }
          j = (j) - (1);
        }
        if ((j) == (-(1))) {
          (addFi).add(epsilon);
        }
        (FiRules[i]).del();
        FiRules[i] = addFi;
        not_finished = ((cFi)->union_with(addFi)) || (not_finished);
        i = (i) + (1);
      }
    }
    term_set* Fo;
    Fo = (term_set*)malloc((sizeof(term_set)) * ((nonterm_symbs).len()));
    i = 0;
    while ((i) < ((nonterm_symbs).len())) {
      (Fo[i]).init();
      i = (i) + (1);
    }
    (tmp_ptr).init_ptr(stop_symbol);
    (Fo[goal_nonterm]).add(tmp_ptr);
    not_finished = true;
    while (not_finished) {
      not_finished = false;
      i = 0;
      while ((i) < ((rules).len())) {
        gram_rule_t* rule;
        rule = (rules).ith(i);
        term_set* cFo;
        cFo = (Fo) + ((rule)->result);
        term_set wFi;
        (wFi).init();
        (wFi).add(epsilon);
        int j;
        j = 0;
        while ((j) < (((rule)->pattern).len())) {
          gram_symbol_t* sy;
          sy = ((rule)->pattern).ith_ref(j);
          if (((int)(sy)->kind) != (2)) {
            (wFi).del();
            (wFi).init();
            (tmp_ptr).init_ptr(sy);
            (wFi).add(tmp_ptr);
          } else {
            term_set* oFo;
            oFo = (Fo) + ((((sy)->dat).NonTerm_dat).symb);
            if ((wFi).contains(epsilon)) {
              not_finished = ((oFo)->union_with(cFo[0])) || (not_finished);
            }
            not_finished = ((oFo)->union_with(wFi)) || (not_finished);
            term_set* oFi;
            oFi = (Fi) + ((((sy)->dat).NonTerm_dat).symb);
            if ((oFi)->contains(epsilon)) {
              (oFi)->remove(epsilon);
              (wFi).union_with(oFi[0]);
              (oFi)->add(epsilon);
            } else {
              (wFi).del();
              (wFi).init();
              (wFi).union_with(oFi[0]);
            }
          }
          j = (j) + (1);
        }
        i = (i) + (1);
      }
    }
    parsing_table ret;
    (ret).init_empty((nonterm_symbs).len());
    i = 0;
    while ((i) < ((nonterm_symbs).len())) {
      term_set cFo;
      cFo = Fo[i];
      (cFo).remove(epsilon);
      int j;
      j = 0;
      while ((j) < ((rules).len())) {
        if ((((rules).ith(j))->result) == (i)) {
          term_set cFi;
          cFi = FiRules[j];
          term_set tmp;
          (tmp).init();
          (tmp).union_with(cFi);
          (tmp).remove(epsilon);
          if ((cFi).contains(epsilon)) {
            (tmp).union_with(cFo);
          }
          int k;
          k = 0;
          while ((k) < (((tmp).elts).len())) {
            gram_symbol_t* s;
            s = (((tmp).elts).ith(k)).ptr;
            (ret).add_entry(s[0], i, (rules).ith(j));
            k = (k) + (1);
          }
        }
        j = (j) + (1);
      }
      (cFo).del();
      (Fi[i]).del();
      i = (i) + (1);
    }
    i = 0;
    while ((i) < ((rules).len())) {
      (FiRules[i]).del();
      i = (i) + (1);
    }
    free(Fi);
    free(FiRules);
    free(Fo);
    return ret;
  }
  static
  anyptr parse_with_rules(toklist* l, int goal_nonterm, gram_symbol_t stop_symbol, gram_rules rules, string_list nonterm_symbs){
    if (((int)(stop_symbol).kind) == (2)) {
      printf("invalid stop symbol: it is Nonterminal\n");
      exit(EXIT_FAILURE);
    }
    symdatlist stack;
    parsed_ast ast;
    (stack).init();
    (ast).init_unknown();
    gram_symbol_t sym_tmp;
    (sym_tmp).set_nonterm(goal_nonterm);
    symbol_dat sym_dat_tmp;
    (sym_dat_tmp).init(sym_tmp, &(ast));
    (stack).push(sym_dat_tmp);
    token stop_token;
    if (((int)(stop_symbol).kind) == (1)) {
      stop_token = (((stop_symbol).dat).Exact_dat).tok;
    } else
    stop_token = (((stop_symbol).dat).Term_dat).tok;
    parsing_table table;
    table = make_parsing_table(rules, nonterm_symbs, goal_nonterm, &(stop_symbol));
    while (((stack).len()) > (0)) {
      symbol_dat stacktop;
      stacktop = (stack).pop();
      token inptop;
      if (((l)->len()) && (!((stop_symbol).match_tok((l)->ith(0))))) {
        inptop = (l)->ith(0);
      } else
      inptop = stop_token;
      if (((int)((stacktop).sym).kind) != (2)) {
        if (!(((stacktop).sym).match_tok(inptop))) {
          printf("failed to parse: got token id %d\n", (int)(inptop).kind);
          exit(EXIT_FAILURE);
        }
        (stacktop).update_tok_ast(inptop);
        l[0] = (l)->tail();
        printf("parse tok ok\n");
      } else {
        int nt;
        nt = ((((stacktop).sym).dat).NonTerm_dat).symb;
        gram_rule_t* rule;
        rule = (table).lookup(inptop, nt);
        if ((rule) == (nullptr)) {
          printf("failed to parse: no rule found for nonterminal %s with token kind %d\n", (nonterm_symbs).ith(nt), (int)(inptop).kind);
          exit(EXIT_FAILURE);
        }
        parsed_ast* ast_loc;
        ast_loc = (stacktop).ast_loc;
        (ast_loc)->init_node(rule);
        int i;
        i = 0;
        while ((i) < (((rule)->pattern).len())) {
          parsed_ast* child_ast;
          child_ast = (parsed_ast*)malloc(sizeof(parsed_ast));
          (child_ast)->init_unknown();
          (ast_loc)->push_child(child_ast);
          symbol_dat sym_dat;
          (sym_dat).init(((rule)->pattern).ith(i), child_ast);
          (stack).push(sym_dat);
          i = (i) + (1);
        }
        printf("parse nt ok\n");
      }
    }
    (table).del();
    anyptr final_res;
    final_res = (ast).evaluate_ast();
    return final_res;
  }
  static
  anyptr _gram_rule_ret_lrec_elim_notail(clist_anyptr l){
    anyptr r;
    (r).init_null();
    return r;
  }
  static
  anyptr _gram_rule_ret_lrec_elim_lrec(clist_anyptr l){
    void** tmp;
    void* old_bonus_dat;
    anyptr (*old_res_func)(clist_anyptr);
    void* tail_dat;
    tmp = (void**)((l).remove(((l).len()) - (1))).ptr;
    old_res_func = (decltype(old_res_func))tmp[0];
    old_bonus_dat = tmp[1];
    tail_dat = ((l).remove(((l).len()) - (1))).ptr;
    anyptr tmp2;
    (tmp2).init_view(old_bonus_dat);
    (l).append(tmp2);
    anyptr normal_output;
    normal_output = old_res_func(l);
    return _gram_rule_ret_lrec_elim_nlrec_closure(normal_output, tail_dat);
  }
  static
  anyptr _gram_rule_ret_lrec_elim_nlrec_closure(anyptr prev_out, void* tail_dat){
    if (!(tail_dat)) {
      return prev_out;
    }
  }
  static
  anyptr _gram_rule_ret_lrec_elim_nlrec(clist_anyptr l){
    void** tmp;
    tmp = (void**)((l).ith(((l).len()) - (1))).ptr;
    anyptr (*old_res_func)(clist_anyptr);
    anyptr old_bonus_dat;
    old_res_func = (decltype(old_res_func))tmp[0];
    (old_bonus_dat).init_view(tmp[1]);
    clist_anyptr lcopy;
    (lcopy).init();
    int i;
    i = 0;
    while ((i) < ((l).len())) {
      (lcopy).append((l).ith(i));
    }
    (lcopy).append(old_bonus_dat);
  }
  static
  void remove_left_recursion(gram_rules* rules, string_list* nonterm_symbs){
    int i;
    int ntlen;
    i = 0;
    ntlen = (nonterm_symbs)->len();
    gram_rules new_rules;
    (new_rules).init();
    while ((i) < (ntlen)) {
      gram_rules lrec_rules;
      gram_rules nlrec_rules;
      (lrec_rules).init();
      (nlrec_rules).init();
      int j;
      j = 0;
      while ((j) < ((rules)->len())) {
        gram_rule_t* rule;
        rule = (rules)->ith(j);
        if (((rule)->result) == (i)) {
          if (((rule)->pattern).len()) {
            gram_symbol_t first_sym;
            first_sym = ((rule)->pattern).ith((((rule)->pattern).len()) - (1));
            if ((((int)(first_sym).kind) == (2)) && (((((first_sym).dat).NonTerm_dat).symb) == ((rule)->result))) {
              if ((((rule)->pattern).len()) == (1)) {
                (rule)->del();
                free(rule);
              } else
              (lrec_rules).append(rule);
            } else
            (nlrec_rules).append(rule);
          } else
          (nlrec_rules).append(rule);
        }
        j = (j) + (1);
      }
      if ((lrec_rules).len()) {
        char* new_nonterm_str;
        new_nonterm_str = (char*)malloc((strlen((nonterm_symbs)->ith(i))) + ((1) + (10)));
        sprintf(new_nonterm_str, "lrec_elim_%s", (nonterm_symbs)->ith(i));
        int new_nonterm;
        new_nonterm = string_list_thingy(nonterm_symbs, new_nonterm_str);
        gram_symbol_t new_sym;
        (new_sym).set_nonterm(new_nonterm);
        j = 0;
        while ((j) < ((nlrec_rules).len())) {
          gram_rule_t* rule;
          rule = (nlrec_rules).ith(j);
          (rule)->add_nonterm(new_nonterm);
          void** tmp;
          tmp = (void**)malloc(sizeof(tmp[0]));
          tmp[0] = (void*)(rule)->result_function;
          tmp[1] = (rule)->func_bonus_dat;
          (rule[0]).func_bonus_dat = (void*)tmp;
          (rule[0]).result_function = _gram_rule_ret_lrec_elim_nlrec;
          j = (j) + (1);
        }
        j = 0;
        while ((j) < ((lrec_rules).len())) {
          gram_rule_t* rule;
          rule = (lrec_rules).ith(j);
          ((rule)->pattern).remove((((rule)->pattern).len()) - (1));
          (rule)->add_nonterm(new_nonterm);
          void** tmp;
          tmp = (void**)malloc(sizeof(tmp[0]));
          tmp[0] = (void*)(rule)->result_function;
          tmp[1] = (rule)->func_bonus_dat;
          (rule[0]).func_bonus_dat = (void*)tmp;
          (rule[0]).result = new_nonterm;
          (rule[0]).result_function = _gram_rule_ret_lrec_elim_lrec;
          j = (j) + (1);
        }
        gram_rule_t* epsrule;
        epsrule = (gram_rule_t*)malloc(sizeof(gram_rule_t));
        (epsrule)->init(new_nonterm, _gram_rule_ret_lrec_elim_notail);
        (lrec_rules).append(epsrule);
      }
      while ((nlrec_rules).len()) {
        (new_rules).append((nlrec_rules).pop());
      }
      while ((lrec_rules).len()) {
        (new_rules).append((lrec_rules).pop());
      }
      i = (i) + (1);
    }
    (rules)->del();
    rules[0] = new_rules;
  }
};
gram_rule_t* make_rule(const char* str, anyptr (*rule_result_function)(clist_anyptr), string_list* nonterm_symbs){
  char* tmp;
  if (((str[0]) != (36)) || ((str[1]) == (36))) {
    printf("rule initial symbol must be a nonterminal\n");
    exit(EXIT_FAILURE);
  }
  str = (str) + (1);
  gram_rule_t ret;
  (ret).init(string_list_thingy(nonterm_symbs, copy_string_until_char(&(str), 32)), rule_result_function);
  while ((str[0]) && ((str[0]) == (32))) {
    str = (str) + (1);
  }
  if (((str[0]) != (45)) || ((str[1]) != (62))) {
    printf("expected \"->\" after initial symbol of rule\n");
    exit(EXIT_FAILURE);
  }
  str = (str) + (2);
  while (str[0]) {
    while ((str[0]) && ((str[0]) == (32))) {
      str = (str) + (1);
    }
    if ((str[0]) == ((36) && ((str[1]) == (123)))) {
      str = (str) + (2);
      tmp = copy_string_until_char(&(str), 125);
      (ret).add_exact(tmp);
      free(tmp);
      tmp = nullptr;
    } else
    if ((str[0]) == ((36) && ((str[1]) == (123)))) {
      str = (str) + (2);
      tmp = copy_string_until_char(&(str), 125);
      (ret).add_term(tmp);
      free(tmp);
      tmp = nullptr;
    } else
    if ((str[0]) == (36)) {
      str = (str) + (1);
      (ret).add_nonterm(string_list_thingy(nonterm_symbs, copy_string_until_char(&(str), 32)));
    } else
    if ((str[0]) == (64)) {
      str = (str) + (1);
      tmp = copy_string_until_char(&(str), 32);
      (ret).add_term(tmp);
      free(tmp);
      tmp = nullptr;
    } else {
      tmp = copy_string_until_char(&(str), 32);
      (ret).add_exact(tmp);
      free(tmp);
      tmp = nullptr;
    }
  }
  gram_rule_t* ptrret;
  ptrret = (gram_rule_t*)malloc(sizeof(gram_rule_t));
  ptrret[0] = ret;
  return ptrret;
}
