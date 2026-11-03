
#pragma once

#include <stdlib.h>

struct _old_clist
{
    void* dat;
    _old_clist* next;
};

struct old_clist
{
    int datsize;
    _old_clist* l;

    static old_clist new_clist(int datsize) {
        old_clist r;
        r.l = nullptr;
        r.datsize = datsize;
        return r;
    }

    void push(void* dat) {
        _old_clist* n = (_old_clist*)malloc(sizeof(_old_clist));
        n->dat = malloc(datsize);
        for (int i = 0; i < datsize; i++)
        {
            ((char*)n->dat)[i] = ((char*)dat)[i];
        }
        n->next = l;
        l = n;
    }

    void* pop() {
        void* ret = l->dat;
        _old_clist* tmp = l ->next;
        free(l);
        l = tmp;
        return ret;
    }

    void del() {
        while (l)
        {
            free(pop());
        }
    }

    int len() {
        int ret = 0;
        _old_clist* t = l;
        while (t)
        {
            ret = ret + 1;
            t = t->next;
        }
        return ret;
    }

    void* ith(int i) {
        _old_clist* t = l;
        while (i > 0)
        {
            if (!t) {
                printf("out of range in list: index %d\n", i);
                exit(0);
            }
            t = t->next;
            i = i - 1;
        }
        return t->dat;
    }

    void reverse() {
        old_clist rev = {.datsize = datsize, .l = nullptr};
        while (l)
        {
            rev.push(pop());
        }
        l = rev.l;
    }

    old_clist tail() {
        return {.datsize = datsize, .l = l->next};
    }
};
