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
    n = nullptr;
    n = (n) + (0);
    char yyyy;
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
  clist deepcopy(){
    clist ret;
    (ret).init();
    int i;
    i = 0;
    while ((i) < (len())) {
      (ret).push(ith((len()) - ((i) + (1))));
      i = (i) + (1);
    }
    return ret;
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
    n = nullptr;
    n = (n) + (0);
    char yyyy;
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
  clist deepcopy(){
    clist ret;
    (ret).init();
    int i;
    i = 0;
    while ((i) < (len())) {
      (ret).push(ith((len()) - ((i) + (1))));
      i = (i) + (1);
    }
    return ret;
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
    n = nullptr;
    n = (n) + (0);
    char yyyy;
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
  clist deepcopy(){
    clist ret;
    (ret).init();
    int i;
    i = 0;
    while ((i) < (len())) {
      (ret).push(ith((len()) - ((i) + (1))));
      i = (i) + (1);
    }
    return ret;
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
  void fprint(FILE* fptr){
    if ((kind) == (Eq)) {
      fprintf(fptr, "==");
    } else
    if ((kind) == (Neq)) {
      fprintf(fptr, "!=");
    } else
    if ((kind) == (Lt)) {
      fprintf(fptr, "<");
    } else
    if ((kind) == (Leq)) {
      fprintf(fptr, "<=");
    } else
    if ((kind) == (Land)) {
      fprintf(fptr, "&&");
    } else
    if ((kind) == (Lor)) {
      fprintf(fptr, "||");
    } else
    if ((kind) == (Band)) {
      fprintf(fptr, "&");
    } else
    if ((kind) == (Bor)) {
      fprintf(fptr, "|");
    } else
    if ((kind) == (Gt)) {
      fprintf(fptr, ">");
    } else
    if ((kind) == (Geq)) {
      fprintf(fptr, ">=");
    } else
    if ((kind) == (Div)) {
      fprintf(fptr, "/");
    } else
    if ((kind) == (Mul)) {
      fprintf(fptr, "*");
    } else
    if ((kind) == (Sub)) {
      fprintf(fptr, "-");
    } else
    if ((kind) == (Add)) {
      fprintf(fptr, "+");
    } else
    if ((kind) == (Arrow)) {
      fprintf(fptr, "->");
    }
  }
  void print(){
    fprint(stdout);
  }
};
struct unop {
  enum { Lnot, Neg, Addr } kind;
  void fprint(FILE* fptr){
    if ((kind) == (Lnot)) {
      fprintf(fptr, "!");
    } else
    if ((kind) == (Neg)) {
      fprintf(fptr, "-");
    } else
    if ((kind) == (Addr)) {
      fprintf(fptr, "&");
    }
  }
  void print(){
    fprint(stdout);
  }
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
  void print(){
    if ((kind) == (LPAREN)) {
      printf("(");
    } else
    if ((kind) == (RPAREN)) {
      printf(")");
    } else
    if ((kind) == (LSQUAR)) {
      printf("[");
    } else
    if ((kind) == (RSQUAR)) {
      printf("]");
    } else
    if ((kind) == (TInt)) {
      printf("int");
    } else
    if ((kind) == (TVoid)) {
      printf("void");
    } else
    if ((kind) == (TChar)) {
      printf("char");
    } else
    if ((kind) == (Const)) {
      printf("const");
    } else
    if ((kind) == (As)) {
      printf("as");
    } else
    if ((kind) == (Set)) {
      printf("=");
    } else
    if ((kind) == (Dot)) {
      printf(".");
    } else
    if ((kind) == (Comma)) {
      printf(",");
    } else
    if ((kind) == (Ident)) {
      printf("%s", ((dat).Ident_dat).str);
    } else
    if ((kind) == (VInt)) {
      printf("%d", ((dat).VInt_dat).dat);
    } else
    if ((kind) == (VString)) {
      printf("\"%s\"", ((dat).VString_dat).str);
    } else
    if ((kind) == (Binop)) {
      (((dat).Binop_dat).op).print();
    } else
    if ((kind) == (Unop)) {
      (((dat).Unop_dat).op).print();
    } else
    printf("kind:%d", (int)kind);
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
    n = nullptr;
    n = (n) + (0);
    char yyyy;
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
  clist deepcopy(){
    clist ret;
    (ret).init();
    int i;
    i = 0;
    while ((i) < (len())) {
      (ret).push(ith((len()) - ((i) + (1))));
      i = (i) + (1);
    }
    return ret;
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
      n = nullptr;
      n = (n) + (0);
      char yyyy;
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
    clist deepcopy(){
      clist ret;
      (ret).init();
      int i;
      i = 0;
      while ((i) < (len())) {
        (ret).push(ith((len()) - ((i) + (1))));
        i = (i) + (1);
      }
      return ret;
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
        printf("@");
        (((dat).Term_dat).tok).print();
      } else
      if ((kind) == (Exact)) {
        (((dat).Exact_dat).tok).print();
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
      n = nullptr;
      n = (n) + (0);
      char yyyy;
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
    clist deepcopy(){
      clist ret;
      (ret).init();
      int i;
      i = 0;
      while ((i) < (len())) {
        (ret).push(ith((len()) - ((i) + (1))));
        i = (i) + (1);
      }
      return ret;
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
        n = nullptr;
        n = (n) + (0);
        char yyyy;
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
      clist deepcopy(){
        clist ret;
        (ret).init();
        int i;
        i = 0;
        while ((i) < (len())) {
          (ret).push(ith((len()) - ((i) + (1))));
          i = (i) + (1);
        }
        return ret;
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
    void add_entry(gram_symbol_t s, int nonterm, gram_rule_t* r, bool ignore_conflicts, const char* nonterm_name){
      if (((int)(s).kind) == (2)) {
        printf("invalid gram symbol for rule table: it is Nonterminal %s\n", nonterm_name);
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
            printf("conflicting entry in the parsing table for nonterm $%s and symbol ", nonterm_name);
            (s).print(empty);
            if (ignore_conflicts) {
              printf(", conflict ignored\n");
            } else {
              printf("\n");
              exit(EXIT_FAILURE);
            }
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
        n = nullptr;
        n = (n) + (0);
        char yyyy;
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
      clist deepcopy(){
        clist ret;
        (ret).init();
        int i;
        i = 0;
        while ((i) < (len())) {
          (ret).push(ith((len()) - ((i) + (1))));
          i = (i) + (1);
        }
        return ret;
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
      n = nullptr;
      n = (n) + (0);
      char yyyy;
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
    clist deepcopy(){
      clist ret;
      (ret).init();
      int i;
      i = 0;
      while ((i) < (len())) {
        (ret).push(ith((len()) - ((i) + (1))));
        i = (i) + (1);
      }
      return ret;
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
    if ((result) != ((r).result)) {
      return false;
    }
    if (((pattern).len()) != (((r).pattern).len())) {
      return false;
    }
    int i;
    i = 0;
    while ((i) < ((pattern).len())) {
      gram_symbol_t s1;
      gram_symbol_t s2;
      s1 = (pattern).ith(i);
      s2 = ((r).pattern).ith(i);
      if (!((s1).eq(s2))) {
        return false;
      }
      i = (i) + (1);
    }
    if ((result_function) != ((r).result_function)) {
    }
    if ((func_bonus_dat) != ((r).func_bonus_dat)) {
    }
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
        n = nullptr;
        n = (n) + (0);
        char yyyy;
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
      clist deepcopy(){
        clist ret;
        (ret).init();
        int i;
        i = 0;
        while ((i) < (len())) {
          (ret).push(ith((len()) - ((i) + (1))));
          i = (i) + (1);
        }
        return ret;
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
    bool test_intersect(set other){
      int i;
      i = 0;
      while ((i) < ((elts).len())) {
        if ((other).contains((elts).ith(i))) {
          return true;
        }
        i = (i) + (1);
      }
      return false;
    }
  };
  #undef set_dat_t
  #undef set
  static
  term_set* compute_first_sets(gram_rules rules, string_list nonterm_symbs, bool only_direct_first = false){
    term_set* ret;
    ret = (term_set*)malloc((sizeof(term_set)) * (((nonterm_symbs).len()) + ((rules).len())));
    term_set* Fi;
    term_set* FiRules;
    Fi = ret;
    FiRules = (ret) + ((nonterm_symbs).len());
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
          } else
          if (!(only_direct_first)) {
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
          } else
          j = -(2);
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
    return ret;
  }
  static
  parsing_table make_parsing_table(gram_rules rules, string_list nonterm_symbs, int goal_nonterm, gram_symbol_t stop_symbol, bool ignore_conflicts){
    printf("making parsing table for %d rules\n", (rules).len());
    term_set* Fi;
    term_set* FiRules;
    Fi = compute_first_sets(rules, nonterm_symbs);
    FiRules = (Fi) + ((nonterm_symbs).len());
    term_ptr tmp_ptr;
    term_ptr epsilon;
    (tmp_ptr).init_null();
    (epsilon).init_null();
    term_set* Fo;
    Fo = (term_set*)malloc((sizeof(term_set)) * ((nonterm_symbs).len()));
    int i;
    i = 0;
    while ((i) < ((nonterm_symbs).len())) {
      (Fo[i]).init();
      i = (i) + (1);
    }
    (tmp_ptr).init_ptr(&(stop_symbol));
    (Fo[goal_nonterm]).add(tmp_ptr);
    bool not_finished;
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
            (ret).add_entry(s[0], i, (rules).ith(j), ignore_conflicts, (nonterm_symbs).ith(i));
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
    free(Fo);
    return ret;
  }
  static
  anyptr parse_with_rules(toklist* l, int goal_nonterm, gram_symbol_t stop_symbol, gram_rules rules, string_list nonterm_symbs, parsing_table table){
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
          printf("failed to parse: got token ");
          (inptop).print();
          printf("\n");
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
          printf("failed to parse: no rule found for nonterminal %s with token ", (nonterm_symbs).ith(nt));
          (inptop).print();
          printf("\n");
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
    anyptr old_bonus_dat;
    anyptr old_res_func;
    anyptr tail_dat;
    tmp = (void**)((l).remove(((l).len()) - (1))).ptr;
    (old_res_func).init_view(tmp[0]);
    (old_bonus_dat).init_view(tmp[1]);
    tail_dat = (l).remove(((l).len()) - (1));
    clist_anyptr* lcopy;
    lcopy = (clist_anyptr*)malloc(sizeof(clist_anyptr));
    (lcopy)->init();
    int i;
    i = 0;
    while ((i) < ((l).len())) {
      (lcopy)->append((l).ith(i));
      i = (i) + (1);
    }
    (lcopy)->append(old_bonus_dat);
    (lcopy)->append(old_res_func);
    (lcopy)->append(tail_dat);
    anyptr ret;
    (ret).init_view(lcopy);
    return ret;
  }
  static
  anyptr _gram_rule_ret_lrec_elim_nlrec_closure(anyptr prev_out, clist_anyptr* tail_dat){
    if (!(tail_dat)) {
      return prev_out;
    }
    anyptr other_tail_dat;
    other_tail_dat = (tail_dat)->remove(((tail_dat)->len()) - (1));
    anyptr (*old_res_func)(clist_anyptr);
    old_res_func = (decltype(old_res_func))((tail_dat)->remove(((tail_dat)->len()) - (1))).ptr;
    anyptr old_bonus_dat;
    old_bonus_dat = (tail_dat)->remove(((tail_dat)->len()) - (1));
    (tail_dat)->append(old_bonus_dat);
    (tail_dat)->push(prev_out);
    anyptr combined_out;
    combined_out = old_res_func(tail_dat[0]);
    anyptr ret;
    ret = _gram_rule_ret_lrec_elim_nlrec_closure(combined_out, (decltype(tail_dat))(other_tail_dat).ptr);
    (tail_dat)->del();
    free(tail_dat);
    return ret;
  }
  static
  anyptr _gram_rule_ret_lrec_elim_nlrec(clist_anyptr l){
    clist_anyptr lcopy;
    (lcopy).init();
    int i;
    i = 0;
    while ((i) < ((l).len())) {
      (lcopy).append((l).ith(i));
      i = (i) + (1);
    }
    void** tmp;
    tmp = (void**)((lcopy).remove(((lcopy).len()) - (1))).ptr;
    clist_anyptr* tail_dat;
    tail_dat = (clist_anyptr*)((lcopy).remove(((lcopy).len()) - (1))).ptr;
    anyptr (*old_res_func)(clist_anyptr);
    anyptr old_bonus_dat;
    old_res_func = (decltype(old_res_func))tmp[0];
    (old_bonus_dat).init_view(tmp[1]);
    (lcopy).append(old_bonus_dat);
    anyptr normal_output;
    normal_output = old_res_func(lcopy);
    (lcopy).del();
    anyptr ret;
    ret = _gram_rule_ret_lrec_elim_nlrec_closure(normal_output, tail_dat);
    return ret;
  }
  static
  anyptr _gram_rule_ret_lrec_any_uninline(clist_anyptr l){
    void** tmp;
    anyptr old_bonus_dat1;
    anyptr (*old_res_func1)(clist_anyptr);
    anyptr old_bonus_dat2;
    anyptr (*old_res_func2)(clist_anyptr);
    int* old1_len;
    tmp = (void**)((l).remove(((l).len()) - (1))).ptr;
    old_res_func1 = (decltype(old_res_func1))tmp[0];
    (old_bonus_dat1).init_view(tmp[1]);
    old_res_func2 = (decltype(old_res_func2))tmp[2];
    (old_bonus_dat2).init_view(tmp[3]);
    old1_len = (int*)tmp[4];
    clist_anyptr lcopy1;
    (lcopy1).init();
    clist_anyptr lcopy2;
    (lcopy2).init();
    int i;
    i = 0;
    while ((i) < (old1_len[0])) {
      (lcopy1).append((l).ith(i));
      i = (i) + (1);
    }
    while ((i) < ((l).len())) {
      (lcopy2).append((l).ith(i));
      i = (i) + (1);
    }
    (lcopy1).append(old_bonus_dat1);
    anyptr res1;
    res1 = old_res_func1(lcopy1);
    (lcopy1).del();
    (lcopy2).push(res1);
    (lcopy2).append(old_bonus_dat2);
    res1 = old_res_func2(lcopy2);
    (lcopy2).del();
    return res1;
  }
  static
  anyptr _gram_rule_ret_factor_accu(clist_anyptr l){
    clist_anyptr* lcopy;
    lcopy = (clist_anyptr*)malloc(sizeof(clist_anyptr));
    lcopy[0] = (l).deepcopy();
    anyptr ret;
    (ret).init_view(lcopy);
    return ret;
  }
  static
  anyptr _gram_rule_ret_factor_join(clist_anyptr l){
    if (((l).remove(((l).len()) - (1))).ptr) {
      printf("Impossible error: join bonus data not null\n");
      exit(EXIT_FAILURE);
    }
    clist_anyptr* acc;
    acc = (clist_anyptr*)((l).remove(((l).len()) - (1))).ptr;
    while ((acc)->len()) {
      (l).append((acc)->pop());
    }
    free(acc);
    void** tmp;
    tmp = (void**)((l).remove(((l).len()) - (1))).ptr;
    anyptr (*old_res_func)(clist_anyptr);
    anyptr old_bonus_dat;
    old_res_func = (decltype(old_res_func))tmp[0];
    (old_bonus_dat).init_view(tmp[1]);
    (l).append(old_bonus_dat);
    anyptr ret;
    ret = old_res_func(l);
    return ret;
  }
  static
  void remove_direct_left_recursion(gram_rules* rules, string_list* nonterm_symbs){
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
        new_nonterm_str = (char*)malloc((strlen((nonterm_symbs)->ith(i))) + ((1) + (50)));
        sprintf(new_nonterm_str, "tail%x_%s", (nonterm_symbs)->len(), (nonterm_symbs)->ith(i));
        int new_nonterm;
        new_nonterm = string_list_thingy(nonterm_symbs, new_nonterm_str);
        if (((new_nonterm) + (1)) != ((nonterm_symbs)->len())) {
          printf("name conflict!!!\n");
          exit(EXIT_FAILURE);
        }
        gram_symbol_t new_sym;
        (new_sym).set_nonterm(new_nonterm);
        j = 0;
        while ((j) < ((nlrec_rules).len())) {
          gram_rule_t* rule;
          rule = (nlrec_rules).ith(j);
          (rule)->add_nonterm(new_nonterm);
          void** tmp;
          tmp = (void**)malloc((sizeof(tmp[0])) * (2));
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
          tmp = (void**)malloc((sizeof(tmp[0])) * (2));
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
  static
  void inline_rule(gram_rule_t* rule1, gram_rule_t* rule2){
    gram_symbol_t first_sym;
    first_sym = ((rule2)->pattern).ith((((rule2)->pattern).len()) - (1));
    if ((((int)(first_sym).kind) != (2)) || (((((first_sym).dat).NonTerm_dat).symb) != ((rule1)->result))) {
      printf("incompatible rules for inlining\n");
      exit(EXIT_FAILURE);
    }
    ((rule2)->pattern).remove((((rule2)->pattern).len()) - (1));
    void** tmp;
    tmp = (void**)malloc((sizeof(tmp[0])) * (5));
    tmp[0] = (void*)(rule1)->result_function;
    tmp[1] = (void*)(rule1)->func_bonus_dat;
    tmp[2] = (void*)(rule2)->result_function;
    tmp[3] = (void*)(rule2)->func_bonus_dat;
    int* tmpint;
    tmpint = (int*)malloc(sizeof(tmpint[0]));
    tmpint[0] = ((rule1)->pattern).len();
    tmp[4] = (void*)tmpint;
    (rule2[0]).result_function = _gram_rule_ret_lrec_any_uninline;
    (rule2[0]).func_bonus_dat = (void*)tmp;
    int k;
    k = 0;
    while ((k) < (((rule1)->pattern).len())) {
      ((rule2)->pattern).append(((rule1)->pattern).ith(k));
      k = (k) + (1);
    }
  }
  static
  void remove_all_left_recursion(gram_rules* rules, string_list* nonterm_symbs){
    bool has_changed;
    has_changed = true;
    while (has_changed) {
      has_changed = false;
      int i;
      i = 0;
      while ((i) < ((rules)->len())) {
        gram_rule_t* rule;
        rule = (rules)->ith(i);
        if (((rule)->pattern).len()) {
          gram_symbol_t first_sym;
          first_sym = ((rule)->pattern).ith((((rule)->pattern).len()) - (1));
          if ((((int)(first_sym).kind) == (2)) && (((((first_sym).dat).NonTerm_dat).symb) < ((rule)->result))) {
            int j;
            j = 0;
            while ((j) < ((rules)->len())) {
              gram_rule_t rule2;
              rule2 = (rules)->ith(j)[0];
              if (((rule2).result) == ((((first_sym).dat).NonTerm_dat).symb)) {
                gram_rule_t* newrule;
                newrule = (gram_rule_t*)malloc(sizeof(gram_rule_t));
                newrule[0] = rule[0];
                (newrule[0]).pattern = ((rule)->pattern).deepcopy();
                inline_rule(&(rule2), newrule);
                (rules)->append(newrule);
              }
              j = (j) + (1);
            }
            (rule)->del();
            free(rule);
            (rules)->remove(i);
            has_changed = true;
            i = (i) - (1);
          }
        }
        remove_direct_left_recursion(rules, nonterm_symbs);
        i = (i) + (1);
      }
    }
  }
  static
  void remove_useless_rules(gram_rules* rules, string_list nonterm_symbs){
    int i;
    i = 0;
    while ((i) < ((rules)->len())) {
      gram_rule_t* rule1;
      rule1 = (rules)->ith(i);
      int j;
      j = (i) + (1);
      while ((j) < ((rules)->len())) {
        gram_rule_t* rule2;
        rule2 = (rules)->ith(j);
        if ((rule1) == (rule2)) {
          printf("WARNING: found shadow copy of following rule:");
          (rule2)->print(nonterm_symbs);
          exit(-(1));
          (rules)->remove(j);
          j = (j) - (1);
        }
        j = (j) + (1);
      }
      i = (i) + (1);
    }
    i = 0;
    while ((i) < ((rules)->len())) {
      gram_rule_t* rule1;
      rule1 = (rules)->ith(i);
      int j;
      j = (i) + (1);
      while ((j) < ((rules)->len())) {
        gram_rule_t* rule2;
        rule2 = (rules)->ith(j);
        if ((rule1)->eq(rule2[0])) {
          (rules)->remove(j);
          (rule2)->del();
          free(rule2);
          j = (j) - (1);
        }
        j = (j) + (1);
      }
      i = (i) + (1);
    }
    i = 0;
    while ((i) < ((rules)->len())) {
      gram_rule_t* rule1;
      rule1 = (rules)->ith(i);
      symlist sl;
      sl = (rule1)->pattern;
      if ((((sl).len()) == (1)) && ((((int)((sl).ith(0)).kind) == (2)) && ((((((sl).ith(0)).dat).NonTerm_dat).symb) == ((rule1)->result)))) {
        (rules)->remove(i);
        (rule1)->del();
        free(rule1);
        i = (i) - (1);
      }
      i = (i) + (1);
    }
  }
  static
  bool _nonterm_inclusion(gram_rules* rules, int nt1, int nt2){
    bool ret;
    ret = true;
    int i;
    i = 0;
    while ((i) < ((rules)->len())) {
      gram_rule_t rule1;
      rule1 = (rules)->ith(i)[0];
      if (((rule1).result) == (nt1)) {
        bool found_match;
        found_match = false;
        int j;
        j = (i) + (1);
        while ((j) < ((rules)->len())) {
          gram_rule_t rule2;
          rule2 = (rules)->ith(j)[0];
          if (((rule2).result) == (nt2)) {
            (rule2).pattern = ((rule2).pattern).deepcopy();
            int k;
            k = 0;
            while ((k) < (((rule2).pattern).len())) {
              gram_symbol_t* s;
              s = ((rule2).pattern).ith_ref(k);
              if ((((int)(s)->kind) == (2)) && (((((s)->dat).NonTerm_dat).symb) == (nt2))) {
                (((s)->dat).NonTerm_dat).symb = nt1;
              }
              k = (k) + (1);
            }
            (rule2).result = nt1;
            found_match = (found_match) || ((rule1).eq(rule2));
            ((rule2).pattern).del();
          }
          j = (j) + (1);
        }
        ret = (ret) && (found_match);
      }
      i = (i) + (1);
    }
    return ret;
  }
  static
  void fuse_identical_nonterms(gram_rules* rules, string_list* nonterm_symbs){
    int n1;
    n1 = 0;
    while ((n1) < ((nonterm_symbs)->len())) {
      int n2;
      n2 = (n1) + (1);
      while ((n2) < ((nonterm_symbs)->len())) {
        if ((_nonterm_inclusion(rules, n1, n2)) && (_nonterm_inclusion(rules, n2, n1))) {
          if (((n2) + (1)) == ((nonterm_symbs)->len())) {
            (nonterm_symbs)->remove(n2);
          }
          int i;
          i = 0;
          while ((i) < ((rules)->len())) {
            gram_rule_t* rule;
            rule = (rules)->ith(i);
            if (((rule)->result) == (n2)) {
              (rules)->remove(i);
              (rule)->del();
              free(rule);
              i = (i) - (1);
            } else {
              int k;
              k = 0;
              while ((k) < (((rule)->pattern).len())) {
                gram_symbol_t* s;
                s = ((rule)->pattern).ith_ref(k);
                if ((((int)(s)->kind) == (2)) && (((((s)->dat).NonTerm_dat).symb) == (n2))) {
                  (((s)->dat).NonTerm_dat).symb = n1;
                }
                k = (k) + (1);
              }
            }
            i = (i) + (1);
          }
        }
        n2 = (n2) + (1);
      }
      n1 = (n1) + (1);
    }
  }
  static
  void order_rules_by_nonterm(gram_rules* rules, string_list nonterm_symbs){
    int i;
    i = 0;
    gram_rules new_rules;
    (new_rules).init();
    while ((i) < ((nonterm_symbs).len())) {
      int j;
      j = 0;
      while ((j) < ((rules)->len())) {
        gram_rule_t* rule;
        rule = (rules)->ith(j);
        if (((rule)->result) == (i)) {
          (new_rules).append(rule);
        }
        j = (j) + (1);
      }
      i = (i) + (1);
    }
    (rules)->del();
    rules[0] = new_rules;
  }
  static
  bool apply_direct_left_factoring(gram_rules* rules, string_list* nonterm_symbs, int max_iter = INT_MAX){
    bool changed;
    changed = false;
    int nt;
    nt = 0;
    while ((nt) < ((nonterm_symbs)->len())) {
      int i;
      i = 0;
      while ((i) < ((rules)->len())) {
        gram_rule_t* rule1;
        int r1_pt_len;
        rule1 = (rules)->ith(i);
        r1_pt_len = ((rule1)->pattern).len();
        if ((((rule1)->result) == (nt)) && (((rule1)->pattern).len())) {
          bool do_factorize;
          do_factorize = false;
          int j;
          j = (i) + (1);
          while ((j) < ((rules)->len())) {
            gram_rule_t* rule2;
            int r2_pt_len;
            rule2 = (rules)->ith(j);
            r2_pt_len = ((rule2)->pattern).len();
            if ((((rule2)->result) == (nt)) && (((rule2)->pattern).len())) {
              if ((((rule1)->pattern).ith((r1_pt_len) - (1))).eq(((rule2)->pattern).ith((r2_pt_len) - (1)))) {
                do_factorize = true;
                j = (INT_MAX) - (1);
              }
            }
            j = (j) + (1);
          }
          if (do_factorize) {
            changed = true;
            char* new_nonterm_str;
            new_nonterm_str = (char*)malloc((strlen((nonterm_symbs)->ith(nt))) + ((1) + (10)));
            sprintf(new_nonterm_str, "lf%x_%s", (nonterm_symbs)->len(), (nonterm_symbs)->ith(nt));
            int new_nonterm;
            new_nonterm = string_list_thingy(nonterm_symbs, new_nonterm_str);
            if (((new_nonterm) + (1)) != ((nonterm_symbs)->len())) {
              printf("name conflict!\n");
              exit(EXIT_FAILURE);
            }
            gram_rule_t* newrule;
            newrule = (gram_rule_t*)malloc(sizeof(gram_rule_t));
            (newrule)->init_bonus_func_data(nt, _gram_rule_ret_factor_join, nullptr);
            ((newrule)->pattern).push(((rule1)->pattern).ith((r1_pt_len) - (1)));
            (newrule)->add_nonterm(new_nonterm);
            printf("factorizing $%s on ", (nonterm_symbs)->ith(nt));
            (((rule1)->pattern).ith((r1_pt_len) - (1))).print(nonterm_symbs[0]);
            printf("\n");
            int j;
            j = 0;
            while ((j) < ((rules)->len())) {
              gram_rule_t* rule2;
              int r2_pt_len;
              rule2 = (rules)->ith(j);
              r2_pt_len = ((rule2)->pattern).len();
              if ((((rule2)->result) == (nt)) && (((rule2)->pattern).len())) {
                if ((((newrule)->pattern).ith(1)).eq(((rule2)->pattern).ith((r2_pt_len) - (1)))) {
                  void** tmp;
                  tmp = (void**)malloc((sizeof(tmp[0])) * (2));
                  tmp[0] = (void*)(rule2)->result_function;
                  tmp[1] = (rule2)->func_bonus_dat;
                  (rule2[0]).result = new_nonterm;
                  (rule2[0]).result_function = _gram_rule_ret_factor_accu;
                  (rule2[0]).func_bonus_dat = (void*)tmp;
                  ((rule2)->pattern).remove((r2_pt_len) - (1));
                }
              }
              j = (j) + (1);
            }
            (rules)->append(newrule);
            i = (INT_MAX) - (1);
          }
        }
        i = (i) + (1);
      }
      nt = (nt) + (1);
    }
    if ((!(changed)) || ((max_iter) <= (1))) {
      return changed;
    } else {
      apply_direct_left_factoring(rules, nonterm_symbs, (max_iter) - (1));
      return true;
    }
  }
  static
  void fix_factoring_conflicts(gram_rules* rules, string_list* nonterm_symbs, int max_iter = 50){
    max_iter = (max_iter) - (1);
    bool has_changed;
    has_changed = apply_direct_left_factoring(rules, nonterm_symbs, 1);
    order_rules_by_nonterm(rules, nonterm_symbs[0]);
    term_set* Fi;
    Fi = compute_first_sets(rules[0], nonterm_symbs[0]);
    term_set* Fi_direct;
    Fi_direct = compute_first_sets(rules[0], nonterm_symbs[0], true);
    int i;
    i = 0;
    while ((i) < ((rules)->len())) {
      gram_rule_t* rule;
      rule = (rules)->ith(i);
      if ((((rule)->pattern).len()) > (1)) {
        gram_symbol_t first_sym;
        first_sym = ((rule)->pattern).ith((((rule)->pattern).len()) - (1));
        if ((((int)(first_sym).kind) == (2)) && ((Fi_direct[(rule)->result]).test_intersect(Fi[(((first_sym).dat).NonTerm_dat).symb]))) {
          printf("inlining on ");
          (rule)->print(nonterm_symbs[0]);
          has_changed = true;
          (rules)->remove(i);
          int j;
          j = 0;
          while ((j) < ((rules)->len())) {
            gram_rule_t* rule2;
            rule2 = (rules)->ith(j);
            if (((rule2)->result) == ((((first_sym).dat).NonTerm_dat).symb)) {
              gram_rule_t* newrule;
              newrule = (gram_rule_t*)malloc(sizeof(gram_rule_t));
              newrule[0] = rule[0];
              (newrule[0]).pattern = ((rule)->pattern).deepcopy();
              inline_rule(rule2, newrule);
              (rules)->append(newrule);
            }
            j = (j) + (1);
          }
          i = (INT_MAX) - (1);
        }
      }
      i = (i) + (1);
    }
    free(Fi);
    free(Fi_direct);
    if ((max_iter) <= (0)) {
      has_changed = false;
      printf("fix_factoring_conflicts reached max iteration count\n");
    }
    if (has_changed) {
      fix_factoring_conflicts(rules, nonterm_symbs, max_iter);
    }
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
    if (((str[0]) == (36)) && ((str[1]) == (123))) {
      str = (str) + (2);
      tmp = copy_string_until_char(&(str), 125);
      (ret).add_exact(tmp);
      free(tmp);
      tmp = nullptr;
    } else
    if (((str[0]) == (36)) && ((str[1]) == (91))) {
      str = (str) + (2);
      tmp = copy_string_until_char(&(str), 93);
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
