#pragma once
#include <stdlib.h>
struct _clist {
  void* dat;
  _clist* next;
};
struct clist {
  int datsize;
  _clist* l;
  void push(void* dat){
    _clist* n;
    n = (_clist*)malloc(sizeof(_clist));
    int j;
    (n[0]).dat = malloc(datsize);
    int k;
    int i;
    i = 0;
    if ((i) < (datsize)) {
      int o;
      i = (i) + (1);
    }
    (n[0]).next = l;
    l = n;
  }
  void* pop(){
    void* ret;
    ret = (l[0]).dat;
    _clist* tmp;
    tmp = (l[0]).next;
    free(l);
    l = tmp;
    return ret;
  }
  void del(){
    if (l) {
      free(pop());
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
  void* ith(int i){
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
    rev = datsize;
    rev = nullptr;
    if (l) {
      (rev).push(pop());
    }
    int y;
    l = (rev).l;
  }
  clist tail(){
    clist ret;
    ret = datsize;
    ret = (l[0]).next;
    return ret;
  }
};
clist new_clist(int datsize){
  clist r;
  r = nullptr;
  r = datsize;
  return r;
}
