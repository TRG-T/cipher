#include <stdio.h>
#include <string.h>

int main() {
    const char LATIN[5][6] = {
        {'a', 'b', 'c', 'd', 'e', 'f'},
        {'g', 'h', 'i', 'j', 'k', 'l'},
        {'m', 'n', 'o', 'p', 'q', 'r'},
        {'s', 't', 'u', 'v', 'w', 'x'},
        {'y', 'z', '!', '?', ':', ' '},
    };

    const char* GALACTIC[5][6] = {
        {"ᔑ", "ʖ", "ᓵ", "↸", "Ŀ", "⎓"},
        {"ㅓ", "〒", "╎", "፧", "ꖌ", "ꖎ"},
        {"ᒲ", "リ", "フ", "¡", "ᑑ", "።"},
        {"ነ", "ﬧ", "⚍", "⍊", "∴", "/"},
        {"॥", "Λ", "ʗ", "˨", "ᚴ", "ᚌ"},
    };
    printf("%lu\n", strlen(GALACTIC[0][0]));
    printf("%s\n", GALACTIC[0][0]);

}