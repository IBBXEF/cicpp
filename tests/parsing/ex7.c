
func int first(int a, int b) {
    return a;
}

func int ternary(bool b, int t, int f) {
    if b
    {
        return t;
    } else {
        return f;
    }
}

int a = 1 + 1;

int* ptr0 = 0;

func int tri_ternary(int b, int _1, int _2, int _3) {
    if b == 1 {
        return _1;
    } elif b == 2 {
        return _2;
    } else {
        b = _1 - _2;
        return _3;
    }
    ptr0[b] = _3;

    void* p;
    ptr0 = p as int*;

}

int i;

func void tet() {
    i = tri_ternary(0, 1, 2, 3);
}

func int exp(int b, int i) {
    while (i) {
        b = b * b;
        i = i - 1;
    }
    return b;
}
