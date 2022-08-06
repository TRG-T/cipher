#include <stdio.h>

const char *encrypt(char text[255], short int key) {
    for (char i = 0; text[i] != 10; i++) {
        text[i] += key;
    }
    return text;
}

int main() {
    char user_text[255];
    char user_key[255];
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

    printf("%s", encrypt(user_text, 3));
}