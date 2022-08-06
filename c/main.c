#include <stdio.h>

int main() {
    char user_text[255];
    unsigned char user_key[255];
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

    printf("Enter text to be encrypted\n");
    fgets(user_text, 255, stdin);

    printf("Enter key (number or string)\n");
    fgets(user_key, 255, stdin);
}