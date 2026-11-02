
#include "lexer.cpp"
#include "parser.cpp"


int main(int argc, char const *argv[])
{
    if (argc < 2) {
        printf("usage: main FILE [-o out_file]\n");
        return -1;
    }
    

    printf("%s\n", argv[1]);
    // return 0;
    
    clist toks = lex_file(argv[1]);

    print_tokens(toks);
    
    ast a = parse(toks);

    if (argc >= 4 && !strcmp(argv[argc-2], "-o")) {
        FILE* fptr = fopen(argv[argc-1], "w");
        if (!fptr) {
            printf("cannot open destination file\n");
        }
        a.print_to_file(fptr);
    }

    return 0;
}

