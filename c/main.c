#include <stdio.h>
#include <string.h>

const char* encrypt(char text[255], short int key) {
    for (char i = 0; i < strlen(text)-1; i++) {
        text[i] += key;
    }
    return text;
}

void revstr(char text[255], char reversed_string[255]) {
    for (char i = 0; i < strlen(text)-1; i++) {
        reversed_string[i] = text[strlen(text)-1-i];
    }
}

int main() {
    char user_text[255];
    char user_key[255];
    char reversed_string[255];
    const char LATIN[5][6] = {
        {'a', 'b', 'c', 'd', 'e', 'f'},
        {'g', 'h', 'i', 'j', 'k', 'l'},
        {'m', 'n', 'o', 'p', 'q', 'r'},
        {'s', 't', 'u', 'v', 'w', 'x'},
        {'y', 'z', '!', '?', ':', ' '},
    };

    // third index is 4 because it stores utf8 chars
    const char GALACTIC[5][6][4] = {
        {"ᔑ", "ʖ", "ᓵ", "↸", "Ŀ", "⎓"},
        {"ㅓ", "〒", "╎", "፧", "ꖌ", "ꖎ"},
        {"ᒲ", "リ", "フ", "¡", "ᑑ", "።"},
        {"ነ", "ﬧ", "⚍", "⍊", "∴", "/"},
        {"॥", "Λ", "ʗ", "˨", "ᚴ", "ᚌ"},
    };

    printf("Enter text to be encrypted\n");
    fgets(user_text, 255, stdin);
    revstr(user_text, reversed_string);
    printf("%s\n", reversed_string);

    printf("Enter key (number or string)\n");
    fgets(user_key, 255, stdin);

    printf("%s", encrypt(reversed_string, 3));
}