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
  enum { TVoid, TInt, TChar, TBool, If, Elif, Else, Return, While, Match, With, Const, Typeof, As, Type, Func, Static, Specialize, Include, Include_C, LPAREN, RPAREN, LSQUAR, RSQUAR, LBRACK, RBRACK, Binop, Unop, Comma, Semicol, Set, Colon, TwoColon, Hashtag, Dot, Arrow, Implies, VInt, VString, Ident, EndOfInput } kind;
  union {
    struct {
      binop op;
    } Binop_dat;
    struct {
      unop op;
    } Unop_dat;
    struct {
      int i;
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
    auto _unique_0 = *(this);
    switch (_unique_0.kind) {
    case token::Binop : {
      auto op = _unique_0.dat.Binop_dat.op;
      return ((op).kind) == (((((b).dat).Binop_dat).op).kind);
      break;}
    case token::Unop : {
      auto op = _unique_0.dat.Unop_dat.op;
      return ((op).kind) == (((((b).dat).Unop_dat).op).kind);
      break;}
    case token::VInt : {
      auto i = _unique_0.dat.VInt_dat.i;
      return (i) == ((((b).dat).VInt_dat).i);
      break;}
    case token::VString : {
      auto str = _unique_0.dat.VString_dat.str;
      return !(strcmp(str, (((b).dat).VString_dat).str));
      break;}
    case token::Ident : {
      auto str = _unique_0.dat.Ident_dat.str;
      return !(strcmp(str, (((b).dat).Ident_dat).str));
      break;}
    default: {
      return true;
      break;}
    }
  }
  void print(){
    auto _unique_1 = *(this);
    switch (_unique_1.kind) {
    case token::LPAREN : {
      printf("(");
      break;}
    case token::RPAREN : {
      printf(")");
      break;}
    case token::LSQUAR : {
      printf("[");
      break;}
    case token::RSQUAR : {
      printf("]");
      break;}
    case token::LBRACK : {
      printf("{");
      break;}
    case token::RBRACK : {
      printf("}");
      break;}
    case token::TInt : {
      printf("int");
      break;}
    case token::TVoid : {
      printf("void");
      break;}
    case token::TChar : {
      printf("char");
      break;}
    case token::TBool : {
      printf("bool");
      break;}
    case token::Const : {
      printf("const");
      break;}
    case token::Static : {
      printf("static");
      break;}
    case token::Func : {
      printf("func");
      break;}
    case token::As : {
      printf("as");
      break;}
    case token::Specialize : {
      printf("specialize");
      break;}
    case token::Type : {
      printf("type");
      break;}
    case token::While : {
      printf("while");
      break;}
    case token::If : {
      printf("if");
      break;}
    case token::Else : {
      printf("else");
      break;}
    case token::Elif : {
      printf("elif");
      break;}
    case token::Match : {
      printf("match");
      break;}
    case token::With : {
      printf("match");
      break;}
    case token::Return : {
      printf("return");
      break;}
    case token::Hashtag : {
      printf("#");
      break;}
    case token::Set : {
      printf("=");
      break;}
    case token::Dot : {
      printf(".");
      break;}
    case token::Arrow : {
      printf("->");
      break;}
    case token::Implies : {
      printf("=>");
      break;}
    case token::Comma : {
      printf(",");
      break;}
    case token::Semicol : {
      printf(";");
      break;}
    case token::Ident : {
      auto str = _unique_1.dat.Ident_dat.str;
      printf("%s", str);
      break;}
    case token::VInt : {
      auto i = _unique_1.dat.VInt_dat.i;
      printf("%d", i);
      break;}
    case token::VString : {
      auto str = _unique_1.dat.VString_dat.str;
      printf("\"%s\"", str);
      break;}
    case token::Binop : {
      auto op = _unique_1.dat.Binop_dat.op;
      (op).print();
      break;}
    case token::Unop : {
      auto op = _unique_1.dat.Unop_dat.op;
      (op).print();
      break;}
    case token::Typeof : {
      printf("typeof");
      break;}
    default: {
      printf("kind:%d", (int)kind);
      break;}
    }
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
