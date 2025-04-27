#include "doctest/doctest.h"

#include <cstring>
#include <string>

struct ci_char_traits : public std::char_traits<char>
// inherit all other functions, because we don't want to write them
{
    static bool eq(char c1, char c2){
        return toupper(c1) == toupper(c2);
    }
    static bool lt(char c1, char c2){
        return toupper(c1) < toupper(c2);
    }
    static int compare(const char * s1, const char * s2, size_t n){
        return memicmp(s1, s2, n);
    }
    static const char * find(const char * s, int n, char a){
        while(n-- > 0 && toupper(*s) != toupper(a)){
            ++s;
        }
        return n >= 0 ? s : 0;
    }
};


typedef std::basic_string<char, ci_char_traits> ci_string;


TEST_CASE("case-insensitive string tests"){

    ci_string s("AbCdE");
    // case-insensitive
    CHECK(s == "abcde");
    CHECK(s == "ABCDE");
    // should stay case-sensitive
    CHECK(strcmp(s.c_str(), "AbCdE") == 0);
    CHECK(strcmp(s.c_str(), "abcde") != 0);

}