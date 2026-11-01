
#include "lexer.cpp"


int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("usage: main FILE\n");
        return -1;
    }
    

    printf("%s\n", argv[1]);
    // return 0;
    
    clist toks = lex_file(argv[1]);

    for (int i = 0; i < toks.len(); i++)
    {
        token tok = *(token*)toks.ith(toks.len() - i -1);

        printf("token kind: %i\n", (int)tok.kind);

        if (tok.kind == token::Ident) {
            printf("    identifier: %s\n", tok.dat.ident_dat);
        } else if (tok.kind == token::VInt) {
            printf("    integer: %i\n", tok.dat.vint_dat);
        }
    }
    

    return 0;
}

