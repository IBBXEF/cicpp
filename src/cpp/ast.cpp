
struct rval;

struct lval
{
    enum {
        Var,
        Index
    } kind;

    union
    {
        char* var_dat;
        struct { rval* arr; rval* ind; } ind_dat;
    } dat;
    
};

struct binop
{
    enum T {Add, Mul, Sub, Div, Band, Bor, Eq, Leq, Lt};
};


struct rval
{
    enum {
        Lval,
        Int,
        Binop
    } kind;

    union {
        lval* lval_dat;
        int int_dat;
        struct { rval* v1; binop::T op; rval* v2; } ind_dat;
    } dat;
};


struct typ
{
    enum {
        TVoid,
        TInt,
        TChar,
        TPtr
    } kind;

    union {
        typ* ptr_dat;
    } dat;
};



struct ast
{
    enum {
        
    } kind;
};

