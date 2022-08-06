#include <stdio.h>
#include <string.h>

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

const char* encrypt(char text[255], unsigned short key) {
    for (char i = 0; i < strlen(text)-1; i++) {
        text[i] += key;
    }
    return text;
}

void revstr(char text[255], char reversed_string[255]) {
    for (char i = 0; i < strlen(text)-1; i++) {
        reversed_string[i] = text[strlen(text)-2-i];
    }
}

unsigned short user_key_to_key(char user_key[]) {
    static unsigned short key;
    for (char i = 0; i < strlen(user_key) - 1; i++) {
        key += user_key[i];
    }
    return key;
}

int main() {
    char user_text[255];
    char user_key[255];
    char reversed_string[255];
    unsigned short key;

    printf("Enter text to be encrypted\n");
    fgets(user_text, 255, stdin);
    revstr(user_text, reversed_string);
    printf("%s\n", reversed_string);

    printf("Enter key (number or text)\n");
    fgets(user_key, 255, stdin);

    key = user_key_to_key(user_key);
    printf("key - %hu\n", key);

    printf("%s", encrypt(reversed_string, key));
}