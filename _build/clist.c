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
