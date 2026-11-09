#pragma once
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
#include <climits>
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
        exit(-(1));
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
    bool add_entry(gram_symbol_t s, int nonterm, gram_rule_t* r){
      if (((int)(s).kind) == (2)) {
        printf("invalid gram symbol for rule table: it is Nonterminal\n");
        exit(-(1));
      }
      int i;
      i = 0;
      while ((i) < (_n_nonterms)) {
        pairlist table;
        table = tables[i];
        int j;
        j = 0;
        while ((j) < ((table).len())) {
          gram_symbol_t s2;
          s2 = ((table).ith(j)).s;
          if (((s2).includes(s)) || ((s).includes(s2))) {
            printf("conflicting entry in the parsing table\n");
            exit(-(1));
          }
          j = (j) + (1);
        }
        i = (i) + (1);
      }
      sym_rule_pair pair;
      (pair).s = s;
      (pair).r = r;
      (tables[nonterm]).push(pair);
    }
    gram_rule_t* lookup(token t, int nonterm){
      int i;
      i = 0;
      pairlist tab;
      tab = tables[nonterm];
      while ((i) < ((tab).len())) {
        if ((((tab).ith(i)).s).match_tok(t)) {
          return ((tab).ith(i)).r;
        }
      }
      return nullptr;
    }
    void init_build(gram_rules rules, string_list nonterm_symbs){
      init_empty((nonterm_symbs).len());
    }
    void del(){
      int i;
      i = 0;
      while ((i) < (_n_nonterms)) {
        (tables[i]).del();
      }
    }
  };
  symlist pattern;
  int result;
  anyptr (*result_function)(clist_anyptr);
  struct parsed_ast {
    enum { Leaf, Node, Unknown } kind;
    union {
      struct {
        token t;
      } Leaf_dat;
      struct {
        clist_voidptr childrens;
        anyptr (*joining_function)(clist_anyptr);
      } Node_dat;
     } dat;
    void init_unknown(){
      kind = Unknown;
    }
    void init_node(anyptr (*joining_function)(clist_anyptr)){
      kind = Node;
      ((dat).Node_dat).joining_function = joining_function;
      (((dat).Node_dat).childrens).init();
    }
    void init_leaf(token t){
      kind = Leaf;
      ((dat).Leaf_dat).t = t;
    }
    void add_child(parsed_ast* child){
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
        anyptr res;
        res = ((dat).Node_dat).joining_function(args);
        (args).del();
        return res;
      } else {
        printf("tried to evaluate unknown ast node\n");
        exit(-(1));
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
    parsed_ast* ast_loc;
    gram_symbol_t sym;
    void update_tok_ast(token t){
      (ast_loc)->init_leaf(t);
    }
    void init(gram_symbol_t symb, parsed_ast* ast){
      sym = symb;
      ast_loc = ast_loc;
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
  void init(int rule_result, anyptr (*rule_result_function)(clist_anyptr)){
    result = rule_result;
    result_function = rule_result_function;
    (pattern).init();
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
  static
  anyptr parse_with_rules(toklist* l, int goal_nonterm, gram_symbol_t stop_symbol, gram_rules rules, string_list nonterm_symbs){
    if (((int)(stop_symbol).kind) == (2)) {
      printf("invalid stop symbol: it is Nonterminal\n");
      exit(-(1));
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
    parsing_table table;
    (table).init_build(rules, nonterm_symbs);
    while (((l)->len()) && (!((stop_symbol).match_tok((l)->ith(0))))) {
      symbol_dat stacktop;
      stacktop = (stack).pop();
      token inptop;
      inptop = (l)->ith(0);
      l[0] = (l)->tail();
      if (((int)((stacktop).sym).kind) != (2)) {
        if (!(((stacktop).sym).match_tok(inptop))) {
          printf("failed to parse: got token id %d\n", (int)(inptop).kind);
          exit(-(1));
        }
        (stacktop).update_tok_ast(inptop);
      } else {
        int nt;
        nt = ((((stacktop).sym).dat).NonTerm_dat).symb;
        gram_rule_t* rule;
        rule = (table).lookup(inptop, nt);
        if ((rule) == (nullptr)) {
          printf("failed to parse: no rule found for nonterminal %s with token kind %d\n", (nonterm_symbs).ith(nt), (int)(inptop).kind);
          exit(-(1));
        }
        parsed_ast* ast_loc;
        ast_loc = (stacktop).ast_loc;
        (ast_loc)->init_node((rule)->result_function);
        parsed_ast* first_child;
        first_child = (parsed_ast*)malloc(sizeof(parsed_ast));
        (first_child)->init_leaf(inptop);
        int i;
        i = (((rule)->pattern).len()) - (2);
        while ((i) >= (0)) {
          parsed_ast* child_ast;
          child_ast = (parsed_ast*)malloc(sizeof(parsed_ast));
          (child_ast)->init_unknown();
          (ast_loc)->add_child(child_ast);
          symbol_dat sym_dat;
          (sym_dat).init(((rule)->pattern).ith(i), child_ast);
          (stack).push(sym_dat);
          i = (i) - (1);
        }
        (ast_loc)->add_child(first_child);
        ((((ast_loc)->dat).Node_dat).childrens).reverse();
      }
    }
    (table).del();
    anyptr final_res;
    final_res = (ast).evaluate_ast();
    return final_res;
  }
};
gram_rule_t* make_rule(const char* str, anyptr (*rule_result_function)(clist_anyptr), string_list* nonterm_symbs){
  char* tmp;
  if (((str[0]) != (36)) || ((str[1]) == (36))) {
    printf("rule initial symbol must be a nonterminal\n");
    exit(-(1));
  }
  str = (str) + (1);
  gram_rule_t ret;
  (ret).init(string_list_thingy(nonterm_symbs, copy_string_until_char(&(str), 32)), rule_result_function);
  while ((str[0]) && ((str[0]) == (32))) {
    str = (str) + (1);
  }
  if (((str[0]) != (45)) || ((str[1]) != (62))) {
    printf("expected \"->\" after initial symbol of rule\n");
    exit(-(1));
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
