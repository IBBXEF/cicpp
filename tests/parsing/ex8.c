
#include "./utils.cpp"

type regex_match_state {
    const char* regex;
    clist pos_pos; // possible positions
}

func bool try_match_regex(regex_match_state* state, const char* string) {
    clist newlist;
    // newlist = clist::new_clist(sizeof(int));
    int i;
    i = 0;
    // while i < 
    if regex[regpos] == '\0' {
        return 0;
    }
    char k;
    if *string == '\0' {
        return -1;
    }
    char j;
    if regex[regpos] == '\\' {
        if regex[regpos+1] != *string {
            return -1;
        }
        int ret;
        ret = 0;
        try_match_regex(regex, (string+1), regpos+1);
        if ret >= 0 {ret = ret + 1;}
        return ret;
    }
    return -1;
}
