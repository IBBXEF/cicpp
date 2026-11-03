
#include "./utils.cpp"

type regex_match_state {
    const char* regex;
    clist pos_pos; // possible positions
}

func int try_match_regex(const char* regex, const char* string, int regpos = 0) {
    if regex[regpos] == '\0' {
        return 0;
    } elif regex[regpos] == '\\' {
        if regex[regpos+1] != *string {
            return -1;
        }
        int ret;
        ret = 0;
        try_match_regex(regex, string+1, regpos+1);
        if ret >= 0 {ret = ret + 1;}
        return ret;
    }
    return -1;
}
