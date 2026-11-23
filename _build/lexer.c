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
  enum { TVoid, TInt, TChar, TBool, If, Elif, Else, Return, While, Match, With, Const, Typeof, As, Type, Fun, Static, Specialize, Include, Include_C, LPAREN, RPAREN, LSQUAR, RSQUAR, LBRACK, RBRACK, Binop, Unop, Comma, Semicol, Set, Colon, TwoColon, Hashtag, Dot, Arrow, Implies, VInt, VString, Ident, EndOfInput } kind;
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
    case token::Fun : {
      printf("fun");
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
void pop_token_stack(int* cou, toklist* l, char* stack){
  if (!(*(cou))) {
    return;
  }
  stack[*(cou)] = 0;
  token tok;
  if ((!(strncmp("void", stack, *(cou)))) && ((*(cou)) == (4))) {
    tok = (token){.kind=token::TVoid};
  } else
  if ((!(strncmp("int", stack, *(cou)))) && ((*(cou)) == (3))) {
    tok = (token){.kind=token::TInt};
  } else
  if ((!(strncmp("char", stack, *(cou)))) && ((*(cou)) == (4))) {
    tok = (token){.kind=token::TChar};
  } else
  if ((!(strncmp("bool", stack, *(cou)))) && ((*(cou)) == (4))) {
    tok = (token){.kind=token::TBool};
  } else
  if ((!(strncmp("if", stack, *(cou)))) && ((*(cou)) == (2))) {
    tok = (token){.kind=token::If};
  } else
  if ((!(strncmp("elif", stack, *(cou)))) && ((*(cou)) == (4))) {
    tok = (token){.kind=token::Elif};
  } else
  if ((!(strncmp("else", stack, *(cou)))) && ((*(cou)) == (4))) {
    tok = (token){.kind=token::Else};
  } else
  if ((!(strncmp("return", stack, *(cou)))) && ((*(cou)) == (6))) {
    tok = (token){.kind=token::Return};
  } else
  if ((!(strncmp("while", stack, *(cou)))) && ((*(cou)) == (5))) {
    tok = (token){.kind=token::While};
  } else
  if ((!(strncmp("match", stack, *(cou)))) && ((*(cou)) == (5))) {
    tok = (token){.kind=token::Match};
  } else
  if ((!(strncmp("with", stack, *(cou)))) && ((*(cou)) == (4))) {
    tok = (token){.kind=token::With};
  } else
  if ((!(strncmp("type", stack, *(cou)))) && ((*(cou)) == (4))) {
    tok = (token){.kind=token::Type};
  } else
  if ((!(strncmp("fun", stack, *(cou)))) && ((*(cou)) == (3))) {
    tok = (token){.kind=token::Fun};
  } else
  if ((!(strncmp("static", stack, *(cou)))) && ((*(cou)) == (6))) {
    tok = (token){.kind=token::Static};
  } else
  if ((!(strncmp("specialize", stack, *(cou)))) && ((*(cou)) == (10))) {
    tok = (token){.kind=token::Specialize};
  } else
  if ((!(strncmp("typeof", stack, *(cou)))) && ((*(cou)) == (6))) {
    tok = (token){.kind=token::Typeof};
  } else
  if ((!(strncmp("const", stack, *(cou)))) && ((*(cou)) == (5))) {
    tok = (token){.kind=token::Const};
  } else
  if ((!(strncmp("as", stack, *(cou)))) && ((*(cou)) == (2))) {
    tok = (token){.kind=token::As};
  } else
  if ((!(strncmp("include", stack, *(cou)))) && ((*(cou)) == (7))) {
    tok = (token){.kind=token::Include};
  } else
  if ((!(strncmp("include_C", stack, *(cou)))) && ((*(cou)) == (9))) {
    tok = (token){.kind=token::Include_C};
  } else
  if ((!(strncmp("include_c", stack, *(cou)))) && ((*(cou)) == (9))) {
    tok = (token){.kind=token::Include_C};
  } else
  if (((*(stack)) >= (48)) && ((*(stack)) <= (57))) {
    char* end;
    int i = strtol(stack, &(end), 10);
    if ((end) != ((stack) + (*(cou)))) {
      printf("invalid integer: %s\n", stack);
      exit(-(1));
    }
    tok = (token){.kind=token::VInt, .dat={.VInt_dat={.i=i}}};
  } else {
    char* str = (char*)malloc((*(cou)) + (1));
    strncpy(str, stack, *(cou));
    str[*(cou)] = 0;
    tok = (token){.kind=token::Ident, .dat={.Ident_dat={.str=str}}};
  }
  (l)->append(tok);
  *(cou) = 0;
}
struct lexing_state {
  enum { LEXING_IDENT_OR_INT, LEXING_STRING, LEXING_STRING_SPECIAL, LINE_COMMENT, LEXING_CHAR, LEXING_CHAR_SPECIAL } kind;
};
void lexing_step(int* cou, toklist* ret, char c, char* last_buffer, lexing_state* state){
  auto _unique_2 = *(state);
  switch (_unique_2.kind) {
  case lexing_state::LEXING_STRING : {
    last_buffer[*(cou)] = c;
    *(cou) = (*(cou)) + (1);
    if ((c) == (92)) {
      *(state) = (lexing_state){.kind=lexing_state::LEXING_STRING_SPECIAL};
    } else
    if ((c) == (34)) {
      char* str = (char*)malloc(*(cou));
      strncpy(str, last_buffer, (*(cou)) - (1));
      str[(*(cou)) - (1)] = 0;
      token tok = (token){.kind=token::VString, .dat={.VString_dat={.str=str}}};
      (ret)->append(tok);
      *(cou) = 0;
      *(state) = (lexing_state){.kind=lexing_state::LEXING_IDENT_OR_INT};
    }
    return;
   break;}
  case lexing_state::LEXING_STRING_SPECIAL : {
    last_buffer[*(cou)] = c;
    *(cou) = (*(cou)) + (1);
    *(state) = (lexing_state){.kind=lexing_state::LEXING_STRING};
    return;
   break;}
  case lexing_state::LINE_COMMENT : {
    if ((c) == (10)) {
      *(state) = (lexing_state){.kind=lexing_state::LEXING_IDENT_OR_INT};
    }
    return;
   break;}
  case lexing_state::LEXING_CHAR : {
    if ((c) == (92)) {
      *(cou) = 0;
      *(state) = (lexing_state){.kind=lexing_state::LEXING_CHAR_SPECIAL};
    } else
    if ((*(cou)) == (1)) {
      if ((c) != (39)) {
        printf("immediate character value must be exactly one character long: found %c instead of '\n", c);
        exit(-(1));
      }
      int i = last_buffer[0];
      token tok = (token){.kind=token::VInt, .dat={.VInt_dat={.i=i}}};
      (ret)->append(tok);
      *(cou) = 0;
      *(state) = (lexing_state){.kind=lexing_state::LEXING_IDENT_OR_INT};
    } else {
      last_buffer[*(cou)] = c;
      *(cou) = (*(cou)) + (1);
    }
    return;
   break;}
  case lexing_state::LEXING_CHAR_SPECIAL : {
    if ((*(cou)) == (1)) {
      if ((c) != (39)) {
        printf("special immediate character value must be exactly one character long: found %c instead of '\n", c);
        exit(-(1));
      }
      int i;
      if ((last_buffer[0]) == (110)) {
        i = 10;
      } else
      if ((last_buffer[0]) == (116)) {
        i = 9;
      } else
      if ((last_buffer[0]) == (48)) {
        i = 0;
      } else
      i = last_buffer[0];
      token tok = (token){.kind=token::VInt, .dat={.VInt_dat={.i=i}}};
      (ret)->append(tok);
      *(cou) = 0;
      *(state) = (lexing_state){.kind=lexing_state::LEXING_IDENT_OR_INT};
    } else {
      last_buffer[*(cou)] = c;
      *(cou) = (*(cou)) + (1);
    }
    return;
   break;}
  default: {
   break;}
  }
  token* n;
  if ((((c) == (32)) || ((c) == (10))) || ((c) == (9))) {
    pop_token_stack(cou, ret, last_buffer);
  } else
  if ((((((c) >= (48)) && ((c) <= (57))) || (((c) >= (97)) && ((c) <= (122)))) || (((c) >= (65)) && ((c) <= (90)))) || ((c) == (95))) {
    last_buffer[*(cou)] = c;
    *(cou) = (*(cou)) + (1);
  } else
  if ((c) == (59)) {
    pop_token_stack(cou, ret, last_buffer);
    (ret)->append((token){.kind=token::Semicol});
  } else
  if ((c) == (44)) {
    pop_token_stack(cou, ret, last_buffer);
    (ret)->append((token){.kind=token::Comma});
  } else
  if ((c) == (46)) {
    pop_token_stack(cou, ret, last_buffer);
    (ret)->append((token){.kind=token::Dot});
  } else
  if ((c) == (35)) {
    pop_token_stack(cou, ret, last_buffer);
    (ret)->append((token){.kind=token::Hashtag});
  } else
  if ((c) == (60)) {
    pop_token_stack(cou, ret, last_buffer);
    binop op = (binop){.kind=binop::Lt};
    (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
  } else
  if ((c) == (62)) {
    pop_token_stack(cou, ret, last_buffer);
    n = (ret)->ith_ref(((ret)->len()) - (1));
    auto _unique_3 = *(n);
    switch (_unique_3.kind) {
    case token::Binop : {
      auto op = _unique_3.dat.Binop_dat.op;
      auto _unique_4 = op;
      switch (_unique_4.kind) {
      case binop::Sub : {
        *(n) = (token){.kind=token::Arrow};
         break;}
      default: {
        binop op = (binop){.kind=binop::Gt};
        (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
         break;}
      }
      break;}
    case token::Set : {
      *(n) = (token){.kind=token::Implies};
      break;}
    default: {
      binop op = (binop){.kind=binop::Gt};
      (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
      break;}
    }
  } else
  if ((c) == (40)) {
    pop_token_stack(cou, ret, last_buffer);
    (ret)->append((token){.kind=token::LPAREN});
  } else
  if ((c) == (41)) {
    pop_token_stack(cou, ret, last_buffer);
    (ret)->append((token){.kind=token::RPAREN});
  } else
  if ((c) == (91)) {
    pop_token_stack(cou, ret, last_buffer);
    (ret)->append((token){.kind=token::LSQUAR});
  } else
  if ((c) == (93)) {
    pop_token_stack(cou, ret, last_buffer);
    (ret)->append((token){.kind=token::RSQUAR});
  } else
  if ((c) == (123)) {
    pop_token_stack(cou, ret, last_buffer);
    (ret)->append((token){.kind=token::LBRACK});
  } else
  if ((c) == (125)) {
    pop_token_stack(cou, ret, last_buffer);
    (ret)->append((token){.kind=token::RBRACK});
  } else
  if ((c) == (61)) {
    pop_token_stack(cou, ret, last_buffer);
    n = (ret)->ith_ref(((ret)->len()) - (1));
    auto _unique_5 = *(n);
    switch (_unique_5.kind) {
    case token::Set : {
      binop op = (binop){.kind=binop::Eq};
      *(n) = (token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}};
      break;}
    case token::Unop : {
      auto op = _unique_5.dat.Unop_dat.op;
      auto _unique_6 = op;
      switch (_unique_6.kind) {
      case unop::Lnot : {
        binop op = (binop){.kind=binop::Neq};
        *(n) = (token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}};
         break;}
      default: {
        (ret)->append((token){.kind=token::Set});
         break;}
      }
      break;}
    case token::Binop : {
      auto op = _unique_5.dat.Binop_dat.op;
      auto _unique_7 = op;
      switch (_unique_7.kind) {
      case binop::Lt : {
        binop op = (binop){.kind=binop::Leq};
        *(n) = (token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}};
         break;}
      case binop::Gt : {
        binop op = (binop){.kind=binop::Geq};
        *(n) = (token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}};
         break;}
      default: {
        (ret)->append((token){.kind=token::Set});
         break;}
      }
      break;}
    default: {
      (ret)->append((token){.kind=token::Set});
      break;}
    }
  } else
  if ((c) == (58)) {
    pop_token_stack(cou, ret, last_buffer);
    n = (ret)->ith_ref(((ret)->len()) - (1));
    auto _unique_8 = *(n);
    switch (_unique_8.kind) {
    case token::Colon : {
      *(n) = (token){.kind=token::TwoColon};
      break;}
    default: {
      (ret)->append((token){.kind=token::Colon});
      break;}
    }
  } else
  if ((c) == (38)) {
    pop_token_stack(cou, ret, last_buffer);
    n = (ret)->ith_ref(((ret)->len()) - (1));
    auto _unique_9 = *(n);
    switch (_unique_9.kind) {
    case token::Binop : {
      auto op = _unique_9.dat.Binop_dat.op;
      auto _unique_10 = op;
      switch (_unique_10.kind) {
      case binop::Band : {
        binop op = (binop){.kind=binop::Land};
        *(n) = (token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}};
         break;}
      default: {
        binop op = (binop){.kind=binop::Band};
        (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
         break;}
      }
      break;}
    default: {
      binop op = (binop){.kind=binop::Band};
      (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
      break;}
    }
  } else
  if ((c) == (124)) {
    pop_token_stack(cou, ret, last_buffer);
    n = (ret)->ith_ref(((ret)->len()) - (1));
    auto _unique_11 = *(n);
    switch (_unique_11.kind) {
    case token::Binop : {
      auto op = _unique_11.dat.Binop_dat.op;
      auto _unique_12 = op;
      switch (_unique_12.kind) {
      case binop::Bor : {
        binop op = (binop){.kind=binop::Lor};
        *(n) = (token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}};
         break;}
      default: {
        binop op = (binop){.kind=binop::Bor};
        (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
         break;}
      }
      break;}
    default: {
      binop op = (binop){.kind=binop::Bor};
      (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
      break;}
    }
  } else
  if ((c) == (33)) {
    pop_token_stack(cou, ret, last_buffer);
    unop op = (unop){.kind=unop::Lnot};
    (ret)->append((token){.kind=token::Unop, .dat={.Unop_dat={.op=op}}});
  } else
  if ((c) == (43)) {
    pop_token_stack(cou, ret, last_buffer);
    binop op = (binop){.kind=binop::Add};
    (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
  } else
  if ((c) == (45)) {
    pop_token_stack(cou, ret, last_buffer);
    binop op = (binop){.kind=binop::Sub};
    (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
  } else
  if ((c) == (42)) {
    pop_token_stack(cou, ret, last_buffer);
    binop op = (binop){.kind=binop::Mul};
    (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
  } else
  if ((c) == (47)) {
    pop_token_stack(cou, ret, last_buffer);
    n = (ret)->ith_ref(((ret)->len()) - (1));
    auto _unique_13 = *(n);
    switch (_unique_13.kind) {
    case token::Binop : {
      auto op = _unique_13.dat.Binop_dat.op;
      auto _unique_14 = op;
      switch (_unique_14.kind) {
      case binop::Div : {
        (ret)->remove(((ret)->len()) - (1));
        *(state) = (lexing_state){.kind=lexing_state::LINE_COMMENT};
         break;}
      default: {
        binop op = (binop){.kind=binop::Div};
        (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
         break;}
      }
      break;}
    default: {
      binop op = (binop){.kind=binop::Div};
      (ret)->append((token){.kind=token::Binop, .dat={.Binop_dat={.op=op}}});
      break;}
    }
  } else
  if ((c) == (34)) {
    pop_token_stack(cou, ret, last_buffer);
    *(state) = (lexing_state){.kind=lexing_state::LEXING_STRING};
  } else
  if ((c) == (39)) {
    pop_token_stack(cou, ret, last_buffer);
    *(state) = (lexing_state){.kind=lexing_state::LEXING_CHAR};
  } else {
    printf("unexpected character: %c (code: %d).\n", c, (int)c);
    exit(-(1));
  }
}
toklist lex_string(const char* str){
  toklist ret;
  (ret).init();
  token no = (token){.kind=token::EndOfInput};
  (ret).append(no);
  int cou = 0;
  lexing_state state = (lexing_state){.kind=lexing_state::LEXING_IDENT_OR_INT};
  char* last_buffer = (char*)malloc(100);
  char c;
  c = *(str);
  while ((c) && ((c) != (EOF))) {
    lexing_step(&(cou), &(ret), c, last_buffer, &(state));
    str = (str) + (1);
    c = *(str);
  }
  pop_token_stack(&(cou), &(ret), last_buffer);
  (ret).pop();
  free(last_buffer);
  return ret;
}
toklist lex_file(const char* path){
  FILE* fptr = fopen(path, "r");
  if (!(fptr)) {
    printf("%s file failed to open.\n", path);
    exit(-(1));
  }
  toklist ret;
  (ret).init();
  token no = (token){.kind=token::EndOfInput};
  (ret).append(no);
  int cou = 0;
  lexing_state state = (lexing_state){.kind=lexing_state::LEXING_IDENT_OR_INT};
  char* last_buffer = (char*)malloc(100);
  char c;
  c = fgetc(fptr);
  while ((c) && ((c) != (EOF))) {
    lexing_step(&(cou), &(ret), c, last_buffer, &(state));
    c = fgetc(fptr);
  }
  pop_token_stack(&(cou), &(ret), last_buffer);
  (ret).pop();
  free(last_buffer);
  return ret;
}
void print_tokens(toklist toks){
  int i = 0;
  while ((i) < ((toks).len())) {
    printf("    ");
    ((toks).ith(i)).print();
    printf("\n");
    i = (i) + (1);
  }
}
