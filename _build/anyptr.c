#pragma once
struct anyptr {
  void* ptr;
  void (*free_func)(void*);
  static
  void make(void* _ptr, void (*_free_func)(void*)){
    anyptr ret;
    ret = _ptr;
    ret = _free_func;
  }
  void* get(){
    return ptr;
  }
  void del(){
    free_func(ptr);
  }
};
