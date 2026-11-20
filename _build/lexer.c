#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct binop {
  enum { Add, Mul, Sub, Div, Band, Bor, Land, Lor, Eq, Leq, Lt, Neq, Geq, Gt } kind;
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
    }
  }
  void print(){
    fprint(stdout);
  }
};
struct unop {
  enum { Lnot, Neg, Addr, Deref } kind;
  void fprint(FILE* fptr){
    if ((kind) == (Lnot)) {
      fprintf(fptr, "!");
    } else
    if ((kind) == (Neg)) {
      fprintf(fptr, "-");
    } else
    if ((kind) == (Addr)) {
      fprintf(fptr, "&");
    } else
    if ((kind) == (Deref)) {
      fprintf(fptr, "*");
    }
  }
  void print(){
    fprint(stdout);
  }
};
struct token {
  enum { TVoid, TInt, TChar, TBool, If, Elif, Else, Return, While, Const, Typeof, As, Type, Func, Static, Specialize, Include, Include_C, LPAREN, RPAREN, LSQUAR, RSQUAR, LBRACK, RBRACK, Binop, Unop, Comma, Semicol, Set, Colon, TwoColon, Hashtag, Dot, Arrow, Implies, VInt, VString, Ident, EndOfInput } kind;
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
    if ((kind) == (LBRACK)) {
      printf("{");
    } else
    if ((kind) == (RBRACK)) {
      printf("}");
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
    if ((kind) == (TBool)) {
      printf("bool");
    } else
    if ((kind) == (Const)) {
      printf("const");
    } else
    if ((kind) == (Static)) {
      printf("static");
    } else
    if ((kind) == (Func)) {
      printf("func");
    } else
    if ((kind) == (As)) {
      printf("as");
    } else
    if ((kind) == (Specialize)) {
      printf("specialize");
    } else
    if ((kind) == (Type)) {
      printf("type");
    } else
    if ((kind) == (While)) {
      printf("while");
    } else
    if ((kind) == (If)) {
      printf("if");
    } else
    if ((kind) == (Else)) {
      printf("else");
    } else
    if ((kind) == (Elif)) {
      printf("elif");
    } else
    if ((kind) == (Return)) {
      printf("return");
    } else
    if ((kind) == (Hashtag)) {
      printf("#");
    } else
    if ((kind) == (Set)) {
      printf("=");
    } else
    if ((kind) == (Dot)) {
      printf(".");
    } else
    if ((kind) == (Arrow)) {
      printf("->");
    } else
    if ((kind) == (Implies)) {
      printf("=>");
    } else
    if ((kind) == (Comma)) {
      printf(",");
    } else
    if ((kind) == (Semicol)) {
      printf(";");
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
    if ((kind) == (Typeof)) {
      printf("typeof");
    } else
    printf("kind:%d", (int)kind);
  }
};
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
    _clist* n = (_clist*)malloc(sizeof(_clist));
    (n)->dat = dat;
    (n)->next = l;
    l = n;
  }
  dat_t pop(){
    dat_t ret = (l)->dat;
    _clist* tmp = (l)->next;
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
    int ret = 0;
    _clist* t;
    t = l;
    while (t) {
      ret = (ret) + (1);
      t = (t)->next;
    }
    return ret;
  }
  dat_t* ith_ref(int ind){
    _clist* t = l;
    int i = ind;
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
    dat_t* ret = &((t)->dat);
    return ret;
  }
  dat_t ith(int i){
    return *(ith_ref(i));
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
    int i = 0;
    while ((i) < (len())) {
      (ret).push(ith(((len()) - (i)) - (1)));
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
      clist tmp = tail();
      (tmp).append(dat);
      (l)->next = (tmp).l;
    }
  }
  void fuse(clist other){
    if ((l) == (nullptr)) {
      l = (other).l;
    } else {
      clist tmp = tail();
      (tmp).fuse(other);
      (l)->next = (tmp).l;
    }
  }
  dat_t remove(int i){
    if ((i) == (0)) {
      return pop();
    } else {
      clist tmp = tail();
      dat_t ret = (tmp).remove((i) - (1));
      (l)->next = (tmp).l;
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
    _clist* n = (_clist*)malloc(sizeof(_clist));
    (n)->dat = dat;
    (n)->next = l;
    l = n;
  }
  dat_t pop(){
    dat_t ret = (l)->dat;
    _clist* tmp = (l)->next;
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
    int ret = 0;
    _clist* t;
    t = l;
    while (t) {
      ret = (ret) + (1);
      t = (t)->next;
    }
    return ret;
  }
  dat_t* ith_ref(int ind){
    _clist* t = l;
    int i = ind;
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
    dat_t* ret = &((t)->dat);
    return ret;
  }
  dat_t ith(int i){
    return *(ith_ref(i));
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
    int i = 0;
    while ((i) < (len())) {
      (ret).push(ith(((len()) - (i)) - (1)));
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
      clist tmp = tail();
      (tmp).append(dat);
      (l)->next = (tmp).l;
    }
  }
  void fuse(clist other){
    if ((l) == (nullptr)) {
      l = (other).l;
    } else {
      clist tmp = tail();
      (tmp).fuse(other);
      (l)->next = (tmp).l;
    }
  }
  dat_t remove(int i){
    if ((i) == (0)) {
      return pop();
    } else {
      clist tmp = tail();
      dat_t ret = (tmp).remove((i) - (1));
      (l)->next = (tmp).l;
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
  int i = 0;
  while ((i) < ((l).len())) {
    if (!(strcmp((l).ith(i), str))) {
      return i;
    }
    i = (i) + (1);
  }
  return -(1);
}
#define dat_t token
#define clist toklist
struct clist {
  struct _clist {
    dat_t dat;
    _clist* next;
  };
  _clist* l;
  void push(dat_t dat){
    _clist* n = (_clist*)malloc(sizeof(_clist));
    (n)->dat = dat;
    (n)->next = l;
    l = n;
  }
  dat_t pop(){
    dat_t ret = (l)->dat;
    _clist* tmp = (l)->next;
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
    int ret = 0;
    _clist* t;
    t = l;
    while (t) {
      ret = (ret) + (1);
      t = (t)->next;
    }
    return ret;
  }
  dat_t* ith_ref(int ind){
    _clist* t = l;
    int i = ind;
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
    dat_t* ret = &((t)->dat);
    return ret;
  }
  dat_t ith(int i){
    return *(ith_ref(i));
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
    int i = 0;
    while ((i) < (len())) {
      (ret).push(ith(((len()) - (i)) - (1)));
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
      clist tmp = tail();
      (tmp).append(dat);
      (l)->next = (tmp).l;
    }
  }
  void fuse(clist other){
    if ((l) == (nullptr)) {
      l = (other).l;
    } else {
      clist tmp = tail();
      (tmp).fuse(other);
      (l)->next = (tmp).l;
    }
  }
  dat_t remove(int i){
    if ((i) == (0)) {
      return pop();
    } else {
      clist tmp = tail();
      dat_t ret = (tmp).remove((i) - (1));
      (l)->next = (tmp).l;
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
