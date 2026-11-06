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
struct anyptr {
  void* ptr;
  void (*free_func)(void*);
  static
  void do_nothing(void* p){
    p = p;
  }
  void init(void* _ptr, void (*_free_func)(void*)){
    ptr = _ptr;
    free_func = _free_func;
  }
  void init_view(void* _ptr){
    ptr = _ptr;
    free_func = do_nothing;
  }
  void init_null(){
    init_view(nullptr);
  }
  void* get(){
    return ptr;
  }
  void del(){
    free_func(ptr);
    ptr = nullptr;
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
        token* last_failure;
        int last_failure_depth;
      } NonTerm_dat;
     } dat;
    anyptr match_symb(toklist* l, int max_depth, gram_rules rules, gram_symbol_t* next_tok){
      anyptr ret;
      (ret).init_null();
      if (((max_depth) < (0)) || (((l[0]).len()) == (0))) {
        return ret;
      }
      if ((kind) == (Term)) {
        if ((((l[0]).ith(0)).kind) != ((((dat).Term_dat).tok).kind)) {
          return ret;
        }
        (ret).init_view((l[0]).ith_ref(0));
        l[0] = (l[0]).tail();
        return ret;
      } else
      if ((kind) == (Exact)) {
        if (!(((l[0]).ith(0)).eq(((dat).Exact_dat).tok))) {
          return ret;
        }
        (ret).init_view((l[0]).ith_ref(0));
        l[0] = (l[0]).tail();
        return ret;
      } else {
        if (((((dat).NonTerm_dat).last_failure) == ((l)->ith_ref(0))) && ((((dat).NonTerm_dat).last_failure_depth) >= (max_depth))) {
          return ret;
        }
        int i;
        int chosen_len;
        chosen_len = (l)->len();
        i = 0;
        toklist base;
        toklist chosen_end;
        base = l[0];
        chosen_end = l[0];
        while ((i) < ((rules).len())) {
          gram_rule_t rule;
          rule = (rules).ith(i)[0];
          if (((rule).result) == (((dat).NonTerm_dat).symb)) {
            anyptr tmp;
            tmp = (rule).parse(l, max_depth, rules);
            if ((tmp).ptr) {
              int curlen;
              curlen = (l)->len();
              if ((next_tok) && (((next_tok)->kind) != (NonTerm))) {
                anyptr tmp2;
                tmp2 = (next_tok)->match_symb(l, (max_depth) - (1), rules, nullptr);
                if (!((tmp2).ptr)) {
                  curlen = INT_MAX;
                }
                (tmp2).del();
              }
              if ((curlen) < (chosen_len)) {
                chosen_len = curlen;
                (ret).del();
                ret = tmp;
                chosen_end = l[0];
              } else
              (tmp).del();
            }
            l[0] = base;
          }
          i = (i) + (1);
        }
        l[0] = chosen_end;
        if ((!((ret).ptr)) && ((((dat).NonTerm_dat).last_failure_depth) <= (max_depth))) {
          int yyyy;
          ((dat).NonTerm_dat).last_failure = (l)->ith_ref(0);
          ((dat).NonTerm_dat).last_failure_depth = max_depth;
          return ret;
        }
        return ret;
      }
    }
    void set_nonterm(int i){
      kind = NonTerm;
      ((dat).NonTerm_dat).symb = i;
      ((dat).NonTerm_dat).last_failure = nullptr;
      ((dat).NonTerm_dat).last_failure_depth = -(2);
    }
    void set_term(token t){
      kind = Term;
      ((dat).Term_dat).tok = t;
    }
    void set_exact(token t){
      kind = Exact;
      ((dat).Term_dat).tok = t;
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
  symlist pattern;
  int result;
  anyptr (*result_function)(clist_anyptr);
  anyptr parse(toklist* l, int max_depth, gram_rules rules){
    int i;
    i = 0;
    clist_anyptr vlues;
    (vlues).init();
    toklist base;
    base = l[0];
    anyptr ret;
    while ((i) < ((pattern).len())) {
      gram_symbol_t sym;
      gram_symbol_t* next;
      sym = (pattern).ith(i);
      next = nullptr;
      if (((i) + (1)) < ((pattern).len())) {
        next = (pattern).ith_ref(i);
      }
      anyptr vals;
      vals = (sym).match_symb(l, (max_depth) - (1), rules, next);
      if (!((vals).ptr)) {
        l[0] = base;
        clist_anyptr_free(vlues);
        (ret).init_null();
        return ret;
      }
      (vlues).append(vals);
      i = (i) + (1);
    }
    ret = result_function(vlues);
    (vlues).del();
    return ret;
  }
  void init(int rule_result, anyptr (*rule_result_function)(clist_anyptr)){
    result = rule_result;
    result_function = rule_result_function;
    (pattern).init();
  }
  void add_nonterm(int nt){
    gram_symbol_t sym;
    (sym).set_nonterm(nt);
    (pattern).append(sym);
  }
  void add_term(const char* str){
    toklist l;
    l = lex_string(str);
    while ((l).len()) {
      gram_symbol_t sym;
      (sym).set_term((l).pop());
      (pattern).append(sym);
    }
  }
  void add_exact(const char* str){
    toklist l;
    l = lex_string(str);
    while ((l).len()) {
      gram_symbol_t sym;
      (sym).set_exact((l).pop());
      (pattern).append(sym);
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
      ((pattern).ith(i)).print(nonterm_symbs);
      i = (i) + (1);
    }
    printf("\n");
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
