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
    ret = (l[0]).dat;
    _clist* tmp;
    tmp = (l[0]).next;
    free(l);
    l = tmp;
    return ret;
  }
  void del(){
    if (l) {
      pop();
    }
  }
  int len(){
    int ret;
    ret = 0;
    _clist* t;
    t = l;
    if (t) {
      ret = (ret) + (1);
      t = (t[0]).next;
    }
    return ret;
  }
  dat_t ith(int i){
    _clist* t;
    t = l;
    if ((i) > (0)) {
      if (!(t)) {
        printf("out of range in list: index %d\n", i);
        exit(0);
      }
      t = (t[0]).next;
      i = (i) - (1);
    }
    return (t[0]).dat;
  }
  void reverse(){
    clist rev;
    (rev).l = nullptr;
    if (l) {
      (rev).push(pop());
    }
    l = (rev).l;
  }
  clist tail(){
    clist ret;
    (ret).l = (l[0]).next;
    return ret;
  }
  void init(){
    l = nullptr;
  }
};
#undef dat_t
#undef clist
